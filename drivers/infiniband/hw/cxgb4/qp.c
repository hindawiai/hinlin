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
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
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

#समावेश <linux/module.h>
#समावेश <rdma/uverbs_ioctl.h>

#समावेश "iw_cxgb4.h"

अटल पूर्णांक db_delay_usecs = 1;
module_param(db_delay_usecs, पूर्णांक, 0644);
MODULE_PARM_DESC(db_delay_usecs, "Usecs to delay awaiting db fifo to drain");

अटल पूर्णांक ocqp_support = 1;
module_param(ocqp_support, पूर्णांक, 0644);
MODULE_PARM_DESC(ocqp_support, "Support on-chip SQs (default=1)");

पूर्णांक db_fc_threshold = 1000;
module_param(db_fc_threshold, पूर्णांक, 0644);
MODULE_PARM_DESC(db_fc_threshold,
		 "QP count/threshold that triggers"
		 " automatic db flow control mode (default = 1000)");

पूर्णांक db_coalescing_threshold;
module_param(db_coalescing_threshold, पूर्णांक, 0644);
MODULE_PARM_DESC(db_coalescing_threshold,
		 "QP count/threshold that triggers"
		 " disabling db coalescing (default = 0)");

अटल पूर्णांक max_fr_immd = T4_MAX_FR_IMMD;
module_param(max_fr_immd, पूर्णांक, 0644);
MODULE_PARM_DESC(max_fr_immd, "fastreg threshold for using DSGL instead of immediate");

अटल पूर्णांक alloc_ird(काष्ठा c4iw_dev *dev, u32 ird)
अणु
	पूर्णांक ret = 0;

	xa_lock_irq(&dev->qps);
	अगर (ird <= dev->avail_ird)
		dev->avail_ird -= ird;
	अन्यथा
		ret = -ENOMEM;
	xa_unlock_irq(&dev->qps);

	अगर (ret)
		dev_warn(&dev->rdev.lldi.pdev->dev,
			 "device IRD resources exhausted\n");

	वापस ret;
पूर्ण

अटल व्योम मुक्त_ird(काष्ठा c4iw_dev *dev, पूर्णांक ird)
अणु
	xa_lock_irq(&dev->qps);
	dev->avail_ird += ird;
	xa_unlock_irq(&dev->qps);
पूर्ण

अटल व्योम set_state(काष्ठा c4iw_qp *qhp, क्रमागत c4iw_qp_state state)
अणु
	अचिन्हित दीर्घ flag;
	spin_lock_irqsave(&qhp->lock, flag);
	qhp->attr.state = state;
	spin_unlock_irqrestore(&qhp->lock, flag);
पूर्ण

अटल व्योम dealloc_oc_sq(काष्ठा c4iw_rdev *rdev, काष्ठा t4_sq *sq)
अणु
	c4iw_ocqp_pool_मुक्त(rdev, sq->dma_addr, sq->memsize);
पूर्ण

अटल व्योम dealloc_host_sq(काष्ठा c4iw_rdev *rdev, काष्ठा t4_sq *sq)
अणु
	dma_मुक्त_coherent(&(rdev->lldi.pdev->dev), sq->memsize, sq->queue,
			  dma_unmap_addr(sq, mapping));
पूर्ण

अटल व्योम dealloc_sq(काष्ठा c4iw_rdev *rdev, काष्ठा t4_sq *sq)
अणु
	अगर (t4_sq_onchip(sq))
		dealloc_oc_sq(rdev, sq);
	अन्यथा
		dealloc_host_sq(rdev, sq);
पूर्ण

अटल पूर्णांक alloc_oc_sq(काष्ठा c4iw_rdev *rdev, काष्ठा t4_sq *sq)
अणु
	अगर (!ocqp_support || !ocqp_supported(&rdev->lldi))
		वापस -ENOSYS;
	sq->dma_addr = c4iw_ocqp_pool_alloc(rdev, sq->memsize);
	अगर (!sq->dma_addr)
		वापस -ENOMEM;
	sq->phys_addr = rdev->oc_mw_pa + sq->dma_addr -
			rdev->lldi.vr->ocq.start;
	sq->queue = (__क्रमce जोड़ t4_wr *)(rdev->oc_mw_kva + sq->dma_addr -
					    rdev->lldi.vr->ocq.start);
	sq->flags |= T4_SQ_ONCHIP;
	वापस 0;
पूर्ण

अटल पूर्णांक alloc_host_sq(काष्ठा c4iw_rdev *rdev, काष्ठा t4_sq *sq)
अणु
	sq->queue = dma_alloc_coherent(&(rdev->lldi.pdev->dev), sq->memsize,
				       &(sq->dma_addr), GFP_KERNEL);
	अगर (!sq->queue)
		वापस -ENOMEM;
	sq->phys_addr = virt_to_phys(sq->queue);
	dma_unmap_addr_set(sq, mapping, sq->dma_addr);
	वापस 0;
पूर्ण

अटल पूर्णांक alloc_sq(काष्ठा c4iw_rdev *rdev, काष्ठा t4_sq *sq, पूर्णांक user)
अणु
	पूर्णांक ret = -ENOSYS;
	अगर (user)
		ret = alloc_oc_sq(rdev, sq);
	अगर (ret)
		ret = alloc_host_sq(rdev, sq);
	वापस ret;
पूर्ण

अटल पूर्णांक destroy_qp(काष्ठा c4iw_rdev *rdev, काष्ठा t4_wq *wq,
		      काष्ठा c4iw_dev_ucontext *uctx, पूर्णांक has_rq)
अणु
	/*
	 * uP clears EQ contexts when the connection निकासs rdma mode,
	 * so no need to post a RESET WR क्रम these EQs.
	 */
	dealloc_sq(rdev, &wq->sq);
	kमुक्त(wq->sq.sw_sq);
	c4iw_put_qpid(rdev, wq->sq.qid, uctx);

	अगर (has_rq) अणु
		dma_मुक्त_coherent(&rdev->lldi.pdev->dev,
				  wq->rq.memsize, wq->rq.queue,
				  dma_unmap_addr(&wq->rq, mapping));
		c4iw_rqtpool_मुक्त(rdev, wq->rq.rqt_hwaddr, wq->rq.rqt_size);
		kमुक्त(wq->rq.sw_rq);
		c4iw_put_qpid(rdev, wq->rq.qid, uctx);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Determine the BAR2 भव address and qid. If pbar2_pa is not शून्य,
 * then this is a user mapping so compute the page-aligned physical address
 * क्रम mapping.
 */
व्योम __iomem *c4iw_bar2_addrs(काष्ठा c4iw_rdev *rdev, अचिन्हित पूर्णांक qid,
			      क्रमागत cxgb4_bar2_qtype qtype,
			      अचिन्हित पूर्णांक *pbar2_qid, u64 *pbar2_pa)
अणु
	u64 bar2_qoffset;
	पूर्णांक ret;

	ret = cxgb4_bar2_sge_qregs(rdev->lldi.ports[0], qid, qtype,
				   pbar2_pa ? 1 : 0,
				   &bar2_qoffset, pbar2_qid);
	अगर (ret)
		वापस शून्य;

	अगर (pbar2_pa)
		*pbar2_pa = (rdev->bar2_pa + bar2_qoffset) & PAGE_MASK;

	अगर (is_t4(rdev->lldi.adapter_type))
		वापस शून्य;

	वापस rdev->bar2_kva + bar2_qoffset;
पूर्ण

अटल पूर्णांक create_qp(काष्ठा c4iw_rdev *rdev, काष्ठा t4_wq *wq,
		     काष्ठा t4_cq *rcq, काष्ठा t4_cq *scq,
		     काष्ठा c4iw_dev_ucontext *uctx,
		     काष्ठा c4iw_wr_रुको *wr_रुकोp,
		     पूर्णांक need_rq)
अणु
	पूर्णांक user = (uctx != &rdev->uctx);
	काष्ठा fw_ri_res_wr *res_wr;
	काष्ठा fw_ri_res *res;
	पूर्णांक wr_len;
	काष्ठा sk_buff *skb;
	पूर्णांक ret = 0;
	पूर्णांक eqsize;

	wq->sq.qid = c4iw_get_qpid(rdev, uctx);
	अगर (!wq->sq.qid)
		वापस -ENOMEM;

	अगर (need_rq) अणु
		wq->rq.qid = c4iw_get_qpid(rdev, uctx);
		अगर (!wq->rq.qid) अणु
			ret = -ENOMEM;
			जाओ मुक्त_sq_qid;
		पूर्ण
	पूर्ण

	अगर (!user) अणु
		wq->sq.sw_sq = kसुस्मृति(wq->sq.size, माप(*wq->sq.sw_sq),
				       GFP_KERNEL);
		अगर (!wq->sq.sw_sq) अणु
			ret = -ENOMEM;
			जाओ मुक्त_rq_qid;//FIXME
		पूर्ण

		अगर (need_rq) अणु
			wq->rq.sw_rq = kसुस्मृति(wq->rq.size,
					       माप(*wq->rq.sw_rq),
					       GFP_KERNEL);
			अगर (!wq->rq.sw_rq) अणु
				ret = -ENOMEM;
				जाओ मुक्त_sw_sq;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (need_rq) अणु
		/*
		 * RQT must be a घातer of 2 and at least 16 deep.
		 */
		wq->rq.rqt_size =
			roundup_घात_of_two(max_t(u16, wq->rq.size, 16));
		wq->rq.rqt_hwaddr = c4iw_rqtpool_alloc(rdev, wq->rq.rqt_size);
		अगर (!wq->rq.rqt_hwaddr) अणु
			ret = -ENOMEM;
			जाओ मुक्त_sw_rq;
		पूर्ण
	पूर्ण

	ret = alloc_sq(rdev, &wq->sq, user);
	अगर (ret)
		जाओ मुक्त_hwaddr;
	स_रखो(wq->sq.queue, 0, wq->sq.memsize);
	dma_unmap_addr_set(&wq->sq, mapping, wq->sq.dma_addr);

	अगर (need_rq) अणु
		wq->rq.queue = dma_alloc_coherent(&rdev->lldi.pdev->dev,
						  wq->rq.memsize,
						  &wq->rq.dma_addr,
						  GFP_KERNEL);
		अगर (!wq->rq.queue) अणु
			ret = -ENOMEM;
			जाओ मुक्त_sq;
		पूर्ण
		pr_debug("sq base va 0x%p pa 0x%llx rq base va 0x%p pa 0x%llx\n",
			 wq->sq.queue,
			 (अचिन्हित दीर्घ दीर्घ)virt_to_phys(wq->sq.queue),
			 wq->rq.queue,
			 (अचिन्हित दीर्घ दीर्घ)virt_to_phys(wq->rq.queue));
		dma_unmap_addr_set(&wq->rq, mapping, wq->rq.dma_addr);
	पूर्ण

	wq->db = rdev->lldi.db_reg;

	wq->sq.bar2_va = c4iw_bar2_addrs(rdev, wq->sq.qid,
					 CXGB4_BAR2_QTYPE_EGRESS,
					 &wq->sq.bar2_qid,
					 user ? &wq->sq.bar2_pa : शून्य);
	अगर (need_rq)
		wq->rq.bar2_va = c4iw_bar2_addrs(rdev, wq->rq.qid,
						 CXGB4_BAR2_QTYPE_EGRESS,
						 &wq->rq.bar2_qid,
						 user ? &wq->rq.bar2_pa : शून्य);

	/*
	 * User mode must have bar2 access.
	 */
	अगर (user && (!wq->sq.bar2_pa || (need_rq && !wq->rq.bar2_pa))) अणु
		pr_warn("%s: sqid %u or rqid %u not in BAR2 range\n",
			pci_name(rdev->lldi.pdev), wq->sq.qid, wq->rq.qid);
		जाओ मुक्त_dma;
	पूर्ण

	wq->rdev = rdev;
	wq->rq.msn = 1;

	/* build fw_ri_res_wr */
	wr_len = माप(*res_wr) + 2 * माप(*res);
	अगर (need_rq)
		wr_len += माप(*res);
	skb = alloc_skb(wr_len, GFP_KERNEL);
	अगर (!skb) अणु
		ret = -ENOMEM;
		जाओ मुक्त_dma;
	पूर्ण
	set_wr_txq(skb, CPL_PRIORITY_CONTROL, 0);

	res_wr = __skb_put_zero(skb, wr_len);
	res_wr->op_nres = cpu_to_be32(
			FW_WR_OP_V(FW_RI_RES_WR) |
			FW_RI_RES_WR_NRES_V(need_rq ? 2 : 1) |
			FW_WR_COMPL_F);
	res_wr->len16_pkd = cpu_to_be32(DIV_ROUND_UP(wr_len, 16));
	res_wr->cookie = (uपूर्णांकptr_t)wr_रुकोp;
	res = res_wr->res;
	res->u.sqrq.restype = FW_RI_RES_TYPE_SQ;
	res->u.sqrq.op = FW_RI_RES_OP_WRITE;

	/*
	 * eqsize is the number of 64B entries plus the status page size.
	 */
	eqsize = wq->sq.size * T4_SQ_NUM_SLOTS +
		rdev->hw_queue.t4_eq_status_entries;

	res->u.sqrq.fetchszm_to_iqid = cpu_to_be32(
		FW_RI_RES_WR_HOSTFCMODE_V(0) |	/* no host cidx updates */
		FW_RI_RES_WR_CPRIO_V(0) |	/* करोn't keep in chip cache */
		FW_RI_RES_WR_PCIECHN_V(0) |	/* set by uP at ri_init समय */
		(t4_sq_onchip(&wq->sq) ? FW_RI_RES_WR_ONCHIP_F : 0) |
		FW_RI_RES_WR_IQID_V(scq->cqid));
	res->u.sqrq.dcaen_to_eqsize = cpu_to_be32(
		FW_RI_RES_WR_DCAEN_V(0) |
		FW_RI_RES_WR_DCACPU_V(0) |
		FW_RI_RES_WR_FBMIN_V(2) |
		(t4_sq_onchip(&wq->sq) ? FW_RI_RES_WR_FBMAX_V(2) :
					 FW_RI_RES_WR_FBMAX_V(3)) |
		FW_RI_RES_WR_CIDXFTHRESHO_V(0) |
		FW_RI_RES_WR_CIDXFTHRESH_V(0) |
		FW_RI_RES_WR_EQSIZE_V(eqsize));
	res->u.sqrq.eqid = cpu_to_be32(wq->sq.qid);
	res->u.sqrq.eqaddr = cpu_to_be64(wq->sq.dma_addr);

	अगर (need_rq) अणु
		res++;
		res->u.sqrq.restype = FW_RI_RES_TYPE_RQ;
		res->u.sqrq.op = FW_RI_RES_OP_WRITE;

		/*
		 * eqsize is the number of 64B entries plus the status page size
		 */
		eqsize = wq->rq.size * T4_RQ_NUM_SLOTS +
			rdev->hw_queue.t4_eq_status_entries;
		res->u.sqrq.fetchszm_to_iqid =
			/* no host cidx updates */
			cpu_to_be32(FW_RI_RES_WR_HOSTFCMODE_V(0) |
			/* करोn't keep in chip cache */
			FW_RI_RES_WR_CPRIO_V(0) |
			/* set by uP at ri_init समय */
			FW_RI_RES_WR_PCIECHN_V(0) |
			FW_RI_RES_WR_IQID_V(rcq->cqid));
		res->u.sqrq.dcaen_to_eqsize =
			cpu_to_be32(FW_RI_RES_WR_DCAEN_V(0) |
			FW_RI_RES_WR_DCACPU_V(0) |
			FW_RI_RES_WR_FBMIN_V(2) |
			FW_RI_RES_WR_FBMAX_V(3) |
			FW_RI_RES_WR_CIDXFTHRESHO_V(0) |
			FW_RI_RES_WR_CIDXFTHRESH_V(0) |
			FW_RI_RES_WR_EQSIZE_V(eqsize));
		res->u.sqrq.eqid = cpu_to_be32(wq->rq.qid);
		res->u.sqrq.eqaddr = cpu_to_be64(wq->rq.dma_addr);
	पूर्ण

	c4iw_init_wr_रुको(wr_रुकोp);
	ret = c4iw_ref_send_रुको(rdev, skb, wr_रुकोp, 0, wq->sq.qid, __func__);
	अगर (ret)
		जाओ मुक्त_dma;

	pr_debug("sqid 0x%x rqid 0x%x kdb 0x%p sq_bar2_addr %p rq_bar2_addr %p\n",
		 wq->sq.qid, wq->rq.qid, wq->db,
		 wq->sq.bar2_va, wq->rq.bar2_va);

	वापस 0;
मुक्त_dma:
	अगर (need_rq)
		dma_मुक्त_coherent(&rdev->lldi.pdev->dev,
				  wq->rq.memsize, wq->rq.queue,
				  dma_unmap_addr(&wq->rq, mapping));
मुक्त_sq:
	dealloc_sq(rdev, &wq->sq);
मुक्त_hwaddr:
	अगर (need_rq)
		c4iw_rqtpool_मुक्त(rdev, wq->rq.rqt_hwaddr, wq->rq.rqt_size);
मुक्त_sw_rq:
	अगर (need_rq)
		kमुक्त(wq->rq.sw_rq);
मुक्त_sw_sq:
	kमुक्त(wq->sq.sw_sq);
मुक्त_rq_qid:
	अगर (need_rq)
		c4iw_put_qpid(rdev, wq->rq.qid, uctx);
मुक्त_sq_qid:
	c4iw_put_qpid(rdev, wq->sq.qid, uctx);
	वापस ret;
पूर्ण

अटल पूर्णांक build_immd(काष्ठा t4_sq *sq, काष्ठा fw_ri_immd *immdp,
		      स्थिर काष्ठा ib_send_wr *wr, पूर्णांक max, u32 *plenp)
अणु
	u8 *dstp, *srcp;
	u32 plen = 0;
	पूर्णांक i;
	पूर्णांक rem, len;

	dstp = (u8 *)immdp->data;
	क्रम (i = 0; i < wr->num_sge; i++) अणु
		अगर ((plen + wr->sg_list[i].length) > max)
			वापस -EMSGSIZE;
		srcp = (u8 *)(अचिन्हित दीर्घ)wr->sg_list[i].addr;
		plen += wr->sg_list[i].length;
		rem = wr->sg_list[i].length;
		जबतक (rem) अणु
			अगर (dstp == (u8 *)&sq->queue[sq->size])
				dstp = (u8 *)sq->queue;
			अगर (rem <= (u8 *)&sq->queue[sq->size] - dstp)
				len = rem;
			अन्यथा
				len = (u8 *)&sq->queue[sq->size] - dstp;
			स_नकल(dstp, srcp, len);
			dstp += len;
			srcp += len;
			rem -= len;
		पूर्ण
	पूर्ण
	len = roundup(plen + माप(*immdp), 16) - (plen + माप(*immdp));
	अगर (len)
		स_रखो(dstp, 0, len);
	immdp->op = FW_RI_DATA_IMMD;
	immdp->r1 = 0;
	immdp->r2 = 0;
	immdp->immdlen = cpu_to_be32(plen);
	*plenp = plen;
	वापस 0;
पूर्ण

अटल पूर्णांक build_isgl(__be64 *queue_start, __be64 *queue_end,
		      काष्ठा fw_ri_isgl *isglp, काष्ठा ib_sge *sg_list,
		      पूर्णांक num_sge, u32 *plenp)

अणु
	पूर्णांक i;
	u32 plen = 0;
	__be64 *flitp;

	अगर ((__be64 *)isglp == queue_end)
		isglp = (काष्ठा fw_ri_isgl *)queue_start;

	flitp = (__be64 *)isglp->sge;

	क्रम (i = 0; i < num_sge; i++) अणु
		अगर ((plen + sg_list[i].length) < plen)
			वापस -EMSGSIZE;
		plen += sg_list[i].length;
		*flitp = cpu_to_be64(((u64)sg_list[i].lkey << 32) |
				     sg_list[i].length);
		अगर (++flitp == queue_end)
			flitp = queue_start;
		*flitp = cpu_to_be64(sg_list[i].addr);
		अगर (++flitp == queue_end)
			flitp = queue_start;
	पूर्ण
	*flitp = (__क्रमce __be64)0;
	isglp->op = FW_RI_DATA_ISGL;
	isglp->r1 = 0;
	isglp->nsge = cpu_to_be16(num_sge);
	isglp->r2 = 0;
	अगर (plenp)
		*plenp = plen;
	वापस 0;
पूर्ण

अटल पूर्णांक build_rdma_send(काष्ठा t4_sq *sq, जोड़ t4_wr *wqe,
			   स्थिर काष्ठा ib_send_wr *wr, u8 *len16)
अणु
	u32 plen;
	पूर्णांक size;
	पूर्णांक ret;

	अगर (wr->num_sge > T4_MAX_SEND_SGE)
		वापस -EINVAL;
	चयन (wr->opcode) अणु
	हाल IB_WR_SEND:
		अगर (wr->send_flags & IB_SEND_SOLICITED)
			wqe->send.senकरोp_pkd = cpu_to_be32(
				FW_RI_SEND_WR_SENDOP_V(FW_RI_SEND_WITH_SE));
		अन्यथा
			wqe->send.senकरोp_pkd = cpu_to_be32(
				FW_RI_SEND_WR_SENDOP_V(FW_RI_SEND));
		wqe->send.stag_inv = 0;
		अवरोध;
	हाल IB_WR_SEND_WITH_INV:
		अगर (wr->send_flags & IB_SEND_SOLICITED)
			wqe->send.senकरोp_pkd = cpu_to_be32(
				FW_RI_SEND_WR_SENDOP_V(FW_RI_SEND_WITH_SE_INV));
		अन्यथा
			wqe->send.senकरोp_pkd = cpu_to_be32(
				FW_RI_SEND_WR_SENDOP_V(FW_RI_SEND_WITH_INV));
		wqe->send.stag_inv = cpu_to_be32(wr->ex.invalidate_rkey);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण
	wqe->send.r3 = 0;
	wqe->send.r4 = 0;

	plen = 0;
	अगर (wr->num_sge) अणु
		अगर (wr->send_flags & IB_SEND_INLINE) अणु
			ret = build_immd(sq, wqe->send.u.immd_src, wr,
					 T4_MAX_SEND_INLINE, &plen);
			अगर (ret)
				वापस ret;
			size = माप(wqe->send) + माप(काष्ठा fw_ri_immd) +
			       plen;
		पूर्ण अन्यथा अणु
			ret = build_isgl((__be64 *)sq->queue,
					 (__be64 *)&sq->queue[sq->size],
					 wqe->send.u.isgl_src,
					 wr->sg_list, wr->num_sge, &plen);
			अगर (ret)
				वापस ret;
			size = माप(wqe->send) + माप(काष्ठा fw_ri_isgl) +
			       wr->num_sge * माप(काष्ठा fw_ri_sge);
		पूर्ण
	पूर्ण अन्यथा अणु
		wqe->send.u.immd_src[0].op = FW_RI_DATA_IMMD;
		wqe->send.u.immd_src[0].r1 = 0;
		wqe->send.u.immd_src[0].r2 = 0;
		wqe->send.u.immd_src[0].immdlen = 0;
		size = माप(wqe->send) + माप(काष्ठा fw_ri_immd);
		plen = 0;
	पूर्ण
	*len16 = DIV_ROUND_UP(size, 16);
	wqe->send.plen = cpu_to_be32(plen);
	वापस 0;
पूर्ण

अटल पूर्णांक build_rdma_ग_लिखो(काष्ठा t4_sq *sq, जोड़ t4_wr *wqe,
			    स्थिर काष्ठा ib_send_wr *wr, u8 *len16)
अणु
	u32 plen;
	पूर्णांक size;
	पूर्णांक ret;

	अगर (wr->num_sge > T4_MAX_SEND_SGE)
		वापस -EINVAL;

	/*
	 * iWARP protocol supports 64 bit immediate data but rdma api
	 * limits it to 32bit.
	 */
	अगर (wr->opcode == IB_WR_RDMA_WRITE_WITH_IMM)
		wqe->ग_लिखो.iw_imm_data.ib_imm_data.imm_data32 = wr->ex.imm_data;
	अन्यथा
		wqe->ग_लिखो.iw_imm_data.ib_imm_data.imm_data32 = 0;
	wqe->ग_लिखो.stag_sink = cpu_to_be32(rdma_wr(wr)->rkey);
	wqe->ग_लिखो.to_sink = cpu_to_be64(rdma_wr(wr)->remote_addr);
	अगर (wr->num_sge) अणु
		अगर (wr->send_flags & IB_SEND_INLINE) अणु
			ret = build_immd(sq, wqe->ग_लिखो.u.immd_src, wr,
					 T4_MAX_WRITE_INLINE, &plen);
			अगर (ret)
				वापस ret;
			size = माप(wqe->ग_लिखो) + माप(काष्ठा fw_ri_immd) +
			       plen;
		पूर्ण अन्यथा अणु
			ret = build_isgl((__be64 *)sq->queue,
					 (__be64 *)&sq->queue[sq->size],
					 wqe->ग_लिखो.u.isgl_src,
					 wr->sg_list, wr->num_sge, &plen);
			अगर (ret)
				वापस ret;
			size = माप(wqe->ग_लिखो) + माप(काष्ठा fw_ri_isgl) +
			       wr->num_sge * माप(काष्ठा fw_ri_sge);
		पूर्ण
	पूर्ण अन्यथा अणु
		wqe->ग_लिखो.u.immd_src[0].op = FW_RI_DATA_IMMD;
		wqe->ग_लिखो.u.immd_src[0].r1 = 0;
		wqe->ग_लिखो.u.immd_src[0].r2 = 0;
		wqe->ग_लिखो.u.immd_src[0].immdlen = 0;
		size = माप(wqe->ग_लिखो) + माप(काष्ठा fw_ri_immd);
		plen = 0;
	पूर्ण
	*len16 = DIV_ROUND_UP(size, 16);
	wqe->ग_लिखो.plen = cpu_to_be32(plen);
	वापस 0;
पूर्ण

अटल व्योम build_immd_cmpl(काष्ठा t4_sq *sq, काष्ठा fw_ri_immd_cmpl *immdp,
			    काष्ठा ib_send_wr *wr)
अणु
	स_नकल((u8 *)immdp->data, (u8 *)(uपूर्णांकptr_t)wr->sg_list->addr, 16);
	स_रखो(immdp->r1, 0, 6);
	immdp->op = FW_RI_DATA_IMMD;
	immdp->immdlen = 16;
पूर्ण

अटल व्योम build_rdma_ग_लिखो_cmpl(काष्ठा t4_sq *sq,
				  काष्ठा fw_ri_rdma_ग_लिखो_cmpl_wr *wcwr,
				  स्थिर काष्ठा ib_send_wr *wr, u8 *len16)
अणु
	u32 plen;
	पूर्णांक size;

	/*
	 * This code assumes the काष्ठा fields preceding the ग_लिखो isgl
	 * fit in one 64B WR slot.  This is because the WQE is built
	 * directly in the dma queue, and wrapping is only handled
	 * by the code buildling sgls.  IE the "fixed part" of the wr
	 * काष्ठाs must all fit in 64B.  The WQE build code should probably be
	 * redeचिन्हित to aव्योम this restriction, but क्रम now just add
	 * the BUILD_BUG_ON() to catch अगर this WQE काष्ठा माला_लो too big.
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा fw_ri_rdma_ग_लिखो_cmpl_wr, u) > 64);

	wcwr->stag_sink = cpu_to_be32(rdma_wr(wr)->rkey);
	wcwr->to_sink = cpu_to_be64(rdma_wr(wr)->remote_addr);
	अगर (wr->next->opcode == IB_WR_SEND)
		wcwr->stag_inv = 0;
	अन्यथा
		wcwr->stag_inv = cpu_to_be32(wr->next->ex.invalidate_rkey);
	wcwr->r2 = 0;
	wcwr->r3 = 0;

	/* SEND_INV SGL */
	अगर (wr->next->send_flags & IB_SEND_INLINE)
		build_immd_cmpl(sq, &wcwr->u_cmpl.immd_src, wr->next);
	अन्यथा
		build_isgl((__be64 *)sq->queue, (__be64 *)&sq->queue[sq->size],
			   &wcwr->u_cmpl.isgl_src, wr->next->sg_list, 1, शून्य);

	/* WRITE SGL */
	build_isgl((__be64 *)sq->queue, (__be64 *)&sq->queue[sq->size],
		   wcwr->u.isgl_src, wr->sg_list, wr->num_sge, &plen);

	size = माप(*wcwr) + माप(काष्ठा fw_ri_isgl) +
		wr->num_sge * माप(काष्ठा fw_ri_sge);
	wcwr->plen = cpu_to_be32(plen);
	*len16 = DIV_ROUND_UP(size, 16);
पूर्ण

अटल पूर्णांक build_rdma_पढ़ो(जोड़ t4_wr *wqe, स्थिर काष्ठा ib_send_wr *wr,
			   u8 *len16)
अणु
	अगर (wr->num_sge > 1)
		वापस -EINVAL;
	अगर (wr->num_sge && wr->sg_list[0].length) अणु
		wqe->पढ़ो.stag_src = cpu_to_be32(rdma_wr(wr)->rkey);
		wqe->पढ़ो.to_src_hi = cpu_to_be32((u32)(rdma_wr(wr)->remote_addr
							>> 32));
		wqe->पढ़ो.to_src_lo = cpu_to_be32((u32)rdma_wr(wr)->remote_addr);
		wqe->पढ़ो.stag_sink = cpu_to_be32(wr->sg_list[0].lkey);
		wqe->पढ़ो.plen = cpu_to_be32(wr->sg_list[0].length);
		wqe->पढ़ो.to_sink_hi = cpu_to_be32((u32)(wr->sg_list[0].addr
							 >> 32));
		wqe->पढ़ो.to_sink_lo = cpu_to_be32((u32)(wr->sg_list[0].addr));
	पूर्ण अन्यथा अणु
		wqe->पढ़ो.stag_src = cpu_to_be32(2);
		wqe->पढ़ो.to_src_hi = 0;
		wqe->पढ़ो.to_src_lo = 0;
		wqe->पढ़ो.stag_sink = cpu_to_be32(2);
		wqe->पढ़ो.plen = 0;
		wqe->पढ़ो.to_sink_hi = 0;
		wqe->पढ़ो.to_sink_lo = 0;
	पूर्ण
	wqe->पढ़ो.r2 = 0;
	wqe->पढ़ो.r5 = 0;
	*len16 = DIV_ROUND_UP(माप(wqe->पढ़ो), 16);
	वापस 0;
पूर्ण

अटल व्योम post_ग_लिखो_cmpl(काष्ठा c4iw_qp *qhp, स्थिर काष्ठा ib_send_wr *wr)
अणु
	bool send_संकेतed = (wr->next->send_flags & IB_SEND_SIGNALED) ||
			     qhp->sq_sig_all;
	bool ग_लिखो_संकेतed = (wr->send_flags & IB_SEND_SIGNALED) ||
			      qhp->sq_sig_all;
	काष्ठा t4_swsqe *swsqe;
	जोड़ t4_wr *wqe;
	u16 ग_लिखो_wrid;
	u8 len16;
	u16 idx;

	/*
	 * The sw_sq entries still look like a WRITE and a SEND and consume
	 * 2 slots. The FW WR, however, will be a single uber-WR.
	 */
	wqe = (जोड़ t4_wr *)((u8 *)qhp->wq.sq.queue +
	       qhp->wq.sq.wq_pidx * T4_EQ_ENTRY_SIZE);
	build_rdma_ग_लिखो_cmpl(&qhp->wq.sq, &wqe->ग_लिखो_cmpl, wr, &len16);

	/* WRITE swsqe */
	swsqe = &qhp->wq.sq.sw_sq[qhp->wq.sq.pidx];
	swsqe->opcode = FW_RI_RDMA_WRITE;
	swsqe->idx = qhp->wq.sq.pidx;
	swsqe->complete = 0;
	swsqe->संकेतed = ग_लिखो_संकेतed;
	swsqe->flushed = 0;
	swsqe->wr_id = wr->wr_id;
	अगर (c4iw_wr_log) अणु
		swsqe->sge_ts =
			cxgb4_पढ़ो_sge_बारtamp(qhp->rhp->rdev.lldi.ports[0]);
		swsqe->host_समय = kसमय_get();
	पूर्ण

	ग_लिखो_wrid = qhp->wq.sq.pidx;

	/* just bump the sw_sq */
	qhp->wq.sq.in_use++;
	अगर (++qhp->wq.sq.pidx == qhp->wq.sq.size)
		qhp->wq.sq.pidx = 0;

	/* SEND_WITH_INV swsqe */
	swsqe = &qhp->wq.sq.sw_sq[qhp->wq.sq.pidx];
	अगर (wr->next->opcode == IB_WR_SEND)
		swsqe->opcode = FW_RI_SEND;
	अन्यथा
		swsqe->opcode = FW_RI_SEND_WITH_INV;
	swsqe->idx = qhp->wq.sq.pidx;
	swsqe->complete = 0;
	swsqe->संकेतed = send_संकेतed;
	swsqe->flushed = 0;
	swsqe->wr_id = wr->next->wr_id;
	अगर (c4iw_wr_log) अणु
		swsqe->sge_ts =
			cxgb4_पढ़ो_sge_बारtamp(qhp->rhp->rdev.lldi.ports[0]);
		swsqe->host_समय = kसमय_get();
	पूर्ण

	wqe->ग_लिखो_cmpl.flags_send = send_संकेतed ? FW_RI_COMPLETION_FLAG : 0;
	wqe->ग_लिखो_cmpl.wrid_send = qhp->wq.sq.pidx;

	init_wr_hdr(wqe, ग_लिखो_wrid, FW_RI_RDMA_WRITE_CMPL_WR,
		    ग_लिखो_संकेतed ? FW_RI_COMPLETION_FLAG : 0, len16);
	t4_sq_produce(&qhp->wq, len16);
	idx = DIV_ROUND_UP(len16 * 16, T4_EQ_ENTRY_SIZE);

	t4_ring_sq_db(&qhp->wq, idx, wqe);
पूर्ण

अटल पूर्णांक build_rdma_recv(काष्ठा c4iw_qp *qhp, जोड़ t4_recv_wr *wqe,
			   स्थिर काष्ठा ib_recv_wr *wr, u8 *len16)
अणु
	पूर्णांक ret;

	ret = build_isgl((__be64 *)qhp->wq.rq.queue,
			 (__be64 *)&qhp->wq.rq.queue[qhp->wq.rq.size],
			 &wqe->recv.isgl, wr->sg_list, wr->num_sge, शून्य);
	अगर (ret)
		वापस ret;
	*len16 = DIV_ROUND_UP(
		माप(wqe->recv) + wr->num_sge * माप(काष्ठा fw_ri_sge), 16);
	वापस 0;
पूर्ण

अटल पूर्णांक build_srq_recv(जोड़ t4_recv_wr *wqe, स्थिर काष्ठा ib_recv_wr *wr,
			  u8 *len16)
अणु
	पूर्णांक ret;

	ret = build_isgl((__be64 *)wqe, (__be64 *)(wqe + 1),
			 &wqe->recv.isgl, wr->sg_list, wr->num_sge, शून्य);
	अगर (ret)
		वापस ret;
	*len16 = DIV_ROUND_UP(माप(wqe->recv) +
			      wr->num_sge * माप(काष्ठा fw_ri_sge), 16);
	वापस 0;
पूर्ण

अटल व्योम build_tpte_memreg(काष्ठा fw_ri_fr_nsmr_tpte_wr *fr,
			      स्थिर काष्ठा ib_reg_wr *wr, काष्ठा c4iw_mr *mhp,
			      u8 *len16)
अणु
	__be64 *p = (__be64 *)fr->pbl;

	fr->r2 = cpu_to_be32(0);
	fr->stag = cpu_to_be32(mhp->ibmr.rkey);

	fr->tpte.valid_to_pdid = cpu_to_be32(FW_RI_TPTE_VALID_F |
		FW_RI_TPTE_STAGKEY_V((mhp->ibmr.rkey & FW_RI_TPTE_STAGKEY_M)) |
		FW_RI_TPTE_STAGSTATE_V(1) |
		FW_RI_TPTE_STAGTYPE_V(FW_RI_STAG_NSMR) |
		FW_RI_TPTE_PDID_V(mhp->attr.pdid));
	fr->tpte.locपढ़ो_to_qpid = cpu_to_be32(
		FW_RI_TPTE_PERM_V(c4iw_ib_to_tpt_access(wr->access)) |
		FW_RI_TPTE_ADDRTYPE_V(FW_RI_VA_BASED_TO) |
		FW_RI_TPTE_PS_V(ilog2(wr->mr->page_size) - 12));
	fr->tpte.nosnoop_pbladdr = cpu_to_be32(FW_RI_TPTE_PBLADDR_V(
		PBL_OFF(&mhp->rhp->rdev, mhp->attr.pbl_addr)>>3));
	fr->tpte.dca_mwbcnt_pstag = cpu_to_be32(0);
	fr->tpte.len_hi = cpu_to_be32(0);
	fr->tpte.len_lo = cpu_to_be32(mhp->ibmr.length);
	fr->tpte.va_hi = cpu_to_be32(mhp->ibmr.iova >> 32);
	fr->tpte.va_lo_fbo = cpu_to_be32(mhp->ibmr.iova & 0xffffffff);

	p[0] = cpu_to_be64((u64)mhp->mpl[0]);
	p[1] = cpu_to_be64((u64)mhp->mpl[1]);

	*len16 = DIV_ROUND_UP(माप(*fr), 16);
पूर्ण

अटल पूर्णांक build_memreg(काष्ठा t4_sq *sq, जोड़ t4_wr *wqe,
			स्थिर काष्ठा ib_reg_wr *wr, काष्ठा c4iw_mr *mhp,
			u8 *len16, bool dsgl_supported)
अणु
	काष्ठा fw_ri_immd *imdp;
	__be64 *p;
	पूर्णांक i;
	पूर्णांक pbllen = roundup(mhp->mpl_len * माप(u64), 32);
	पूर्णांक rem;

	अगर (mhp->mpl_len > t4_max_fr_depth(dsgl_supported && use_dsgl))
		वापस -EINVAL;

	wqe->fr.qpbinde_to_dcacpu = 0;
	wqe->fr.pgsz_shअगरt = ilog2(wr->mr->page_size) - 12;
	wqe->fr.addr_type = FW_RI_VA_BASED_TO;
	wqe->fr.mem_perms = c4iw_ib_to_tpt_access(wr->access);
	wqe->fr.len_hi = 0;
	wqe->fr.len_lo = cpu_to_be32(mhp->ibmr.length);
	wqe->fr.stag = cpu_to_be32(wr->key);
	wqe->fr.va_hi = cpu_to_be32(mhp->ibmr.iova >> 32);
	wqe->fr.va_lo_fbo = cpu_to_be32(mhp->ibmr.iova &
					0xffffffff);

	अगर (dsgl_supported && use_dsgl && (pbllen > max_fr_immd)) अणु
		काष्ठा fw_ri_dsgl *sglp;

		क्रम (i = 0; i < mhp->mpl_len; i++)
			mhp->mpl[i] = (__क्रमce u64)cpu_to_be64((u64)mhp->mpl[i]);

		sglp = (काष्ठा fw_ri_dsgl *)(&wqe->fr + 1);
		sglp->op = FW_RI_DATA_DSGL;
		sglp->r1 = 0;
		sglp->nsge = cpu_to_be16(1);
		sglp->addr0 = cpu_to_be64(mhp->mpl_addr);
		sglp->len0 = cpu_to_be32(pbllen);

		*len16 = DIV_ROUND_UP(माप(wqe->fr) + माप(*sglp), 16);
	पूर्ण अन्यथा अणु
		imdp = (काष्ठा fw_ri_immd *)(&wqe->fr + 1);
		imdp->op = FW_RI_DATA_IMMD;
		imdp->r1 = 0;
		imdp->r2 = 0;
		imdp->immdlen = cpu_to_be32(pbllen);
		p = (__be64 *)(imdp + 1);
		rem = pbllen;
		क्रम (i = 0; i < mhp->mpl_len; i++) अणु
			*p = cpu_to_be64((u64)mhp->mpl[i]);
			rem -= माप(*p);
			अगर (++p == (__be64 *)&sq->queue[sq->size])
				p = (__be64 *)sq->queue;
		पूर्ण
		जबतक (rem) अणु
			*p = 0;
			rem -= माप(*p);
			अगर (++p == (__be64 *)&sq->queue[sq->size])
				p = (__be64 *)sq->queue;
		पूर्ण
		*len16 = DIV_ROUND_UP(माप(wqe->fr) + माप(*imdp)
				      + pbllen, 16);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक build_inv_stag(जोड़ t4_wr *wqe, स्थिर काष्ठा ib_send_wr *wr,
			  u8 *len16)
अणु
	wqe->inv.stag_inv = cpu_to_be32(wr->ex.invalidate_rkey);
	wqe->inv.r2 = 0;
	*len16 = DIV_ROUND_UP(माप(wqe->inv), 16);
	वापस 0;
पूर्ण

व्योम c4iw_qp_add_ref(काष्ठा ib_qp *qp)
अणु
	pr_debug("ib_qp %p\n", qp);
	refcount_inc(&to_c4iw_qp(qp)->qp_refcnt);
पूर्ण

व्योम c4iw_qp_rem_ref(काष्ठा ib_qp *qp)
अणु
	pr_debug("ib_qp %p\n", qp);
	अगर (refcount_dec_and_test(&to_c4iw_qp(qp)->qp_refcnt))
		complete(&to_c4iw_qp(qp)->qp_rel_comp);
पूर्ण

अटल व्योम add_to_fc_list(काष्ठा list_head *head, काष्ठा list_head *entry)
अणु
	अगर (list_empty(entry))
		list_add_tail(entry, head);
पूर्ण

अटल पूर्णांक ring_kernel_sq_db(काष्ठा c4iw_qp *qhp, u16 inc)
अणु
	अचिन्हित दीर्घ flags;

	xa_lock_irqsave(&qhp->rhp->qps, flags);
	spin_lock(&qhp->lock);
	अगर (qhp->rhp->db_state == NORMAL)
		t4_ring_sq_db(&qhp->wq, inc, शून्य);
	अन्यथा अणु
		add_to_fc_list(&qhp->rhp->db_fc_list, &qhp->db_fc_entry);
		qhp->wq.sq.wq_pidx_inc += inc;
	पूर्ण
	spin_unlock(&qhp->lock);
	xa_unlock_irqrestore(&qhp->rhp->qps, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक ring_kernel_rq_db(काष्ठा c4iw_qp *qhp, u16 inc)
अणु
	अचिन्हित दीर्घ flags;

	xa_lock_irqsave(&qhp->rhp->qps, flags);
	spin_lock(&qhp->lock);
	अगर (qhp->rhp->db_state == NORMAL)
		t4_ring_rq_db(&qhp->wq, inc, शून्य);
	अन्यथा अणु
		add_to_fc_list(&qhp->rhp->db_fc_list, &qhp->db_fc_entry);
		qhp->wq.rq.wq_pidx_inc += inc;
	पूर्ण
	spin_unlock(&qhp->lock);
	xa_unlock_irqrestore(&qhp->rhp->qps, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक ib_to_fw_opcode(पूर्णांक ib_opcode)
अणु
	पूर्णांक opcode;

	चयन (ib_opcode) अणु
	हाल IB_WR_SEND_WITH_INV:
		opcode = FW_RI_SEND_WITH_INV;
		अवरोध;
	हाल IB_WR_SEND:
		opcode = FW_RI_SEND;
		अवरोध;
	हाल IB_WR_RDMA_WRITE:
		opcode = FW_RI_RDMA_WRITE;
		अवरोध;
	हाल IB_WR_RDMA_WRITE_WITH_IMM:
		opcode = FW_RI_WRITE_IMMEDIATE;
		अवरोध;
	हाल IB_WR_RDMA_READ:
	हाल IB_WR_RDMA_READ_WITH_INV:
		opcode = FW_RI_READ_REQ;
		अवरोध;
	हाल IB_WR_REG_MR:
		opcode = FW_RI_FAST_REGISTER;
		अवरोध;
	हाल IB_WR_LOCAL_INV:
		opcode = FW_RI_LOCAL_INV;
		अवरोध;
	शेष:
		opcode = -EINVAL;
	पूर्ण
	वापस opcode;
पूर्ण

अटल पूर्णांक complete_sq_drain_wr(काष्ठा c4iw_qp *qhp,
				स्थिर काष्ठा ib_send_wr *wr)
अणु
	काष्ठा t4_cqe cqe = अणुपूर्ण;
	काष्ठा c4iw_cq *schp;
	अचिन्हित दीर्घ flag;
	काष्ठा t4_cq *cq;
	पूर्णांक opcode;

	schp = to_c4iw_cq(qhp->ibqp.send_cq);
	cq = &schp->cq;

	opcode = ib_to_fw_opcode(wr->opcode);
	अगर (opcode < 0)
		वापस opcode;

	cqe.u.drain_cookie = wr->wr_id;
	cqe.header = cpu_to_be32(CQE_STATUS_V(T4_ERR_SWFLUSH) |
				 CQE_OPCODE_V(opcode) |
				 CQE_TYPE_V(1) |
				 CQE_SWCQE_V(1) |
				 CQE_DRAIN_V(1) |
				 CQE_QPID_V(qhp->wq.sq.qid));

	spin_lock_irqsave(&schp->lock, flag);
	cqe.bits_type_ts = cpu_to_be64(CQE_GENBIT_V((u64)cq->gen));
	cq->sw_queue[cq->sw_pidx] = cqe;
	t4_swcq_produce(cq);
	spin_unlock_irqrestore(&schp->lock, flag);

	अगर (t4_clear_cq_armed(&schp->cq)) अणु
		spin_lock_irqsave(&schp->comp_handler_lock, flag);
		(*schp->ibcq.comp_handler)(&schp->ibcq,
					   schp->ibcq.cq_context);
		spin_unlock_irqrestore(&schp->comp_handler_lock, flag);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक complete_sq_drain_wrs(काष्ठा c4iw_qp *qhp,
				 स्थिर काष्ठा ib_send_wr *wr,
				 स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	पूर्णांक ret = 0;

	जबतक (wr) अणु
		ret = complete_sq_drain_wr(qhp, wr);
		अगर (ret) अणु
			*bad_wr = wr;
			अवरोध;
		पूर्ण
		wr = wr->next;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम complete_rq_drain_wr(काष्ठा c4iw_qp *qhp,
				 स्थिर काष्ठा ib_recv_wr *wr)
अणु
	काष्ठा t4_cqe cqe = अणुपूर्ण;
	काष्ठा c4iw_cq *rchp;
	अचिन्हित दीर्घ flag;
	काष्ठा t4_cq *cq;

	rchp = to_c4iw_cq(qhp->ibqp.recv_cq);
	cq = &rchp->cq;

	cqe.u.drain_cookie = wr->wr_id;
	cqe.header = cpu_to_be32(CQE_STATUS_V(T4_ERR_SWFLUSH) |
				 CQE_OPCODE_V(FW_RI_SEND) |
				 CQE_TYPE_V(0) |
				 CQE_SWCQE_V(1) |
				 CQE_DRAIN_V(1) |
				 CQE_QPID_V(qhp->wq.sq.qid));

	spin_lock_irqsave(&rchp->lock, flag);
	cqe.bits_type_ts = cpu_to_be64(CQE_GENBIT_V((u64)cq->gen));
	cq->sw_queue[cq->sw_pidx] = cqe;
	t4_swcq_produce(cq);
	spin_unlock_irqrestore(&rchp->lock, flag);

	अगर (t4_clear_cq_armed(&rchp->cq)) अणु
		spin_lock_irqsave(&rchp->comp_handler_lock, flag);
		(*rchp->ibcq.comp_handler)(&rchp->ibcq,
					   rchp->ibcq.cq_context);
		spin_unlock_irqrestore(&rchp->comp_handler_lock, flag);
	पूर्ण
पूर्ण

अटल व्योम complete_rq_drain_wrs(काष्ठा c4iw_qp *qhp,
				  स्थिर काष्ठा ib_recv_wr *wr)
अणु
	जबतक (wr) अणु
		complete_rq_drain_wr(qhp, wr);
		wr = wr->next;
	पूर्ण
पूर्ण

पूर्णांक c4iw_post_send(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_send_wr *wr,
		   स्थिर काष्ठा ib_send_wr **bad_wr)
अणु
	पूर्णांक err = 0;
	u8 len16 = 0;
	क्रमागत fw_wr_opcodes fw_opcode = 0;
	क्रमागत fw_ri_wr_flags fw_flags;
	काष्ठा c4iw_qp *qhp;
	काष्ठा c4iw_dev *rhp;
	जोड़ t4_wr *wqe = शून्य;
	u32 num_wrs;
	काष्ठा t4_swsqe *swsqe;
	अचिन्हित दीर्घ flag;
	u16 idx = 0;

	qhp = to_c4iw_qp(ibqp);
	rhp = qhp->rhp;
	spin_lock_irqsave(&qhp->lock, flag);

	/*
	 * If the qp has been flushed, then just insert a special
	 * drain cqe.
	 */
	अगर (qhp->wq.flushed) अणु
		spin_unlock_irqrestore(&qhp->lock, flag);
		err = complete_sq_drain_wrs(qhp, wr, bad_wr);
		वापस err;
	पूर्ण
	num_wrs = t4_sq_avail(&qhp->wq);
	अगर (num_wrs == 0) अणु
		spin_unlock_irqrestore(&qhp->lock, flag);
		*bad_wr = wr;
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Fastpath क्रम NVMe-oF target WRITE + SEND_WITH_INV wr chain which is
	 * the response क्रम small NVMEe-oF READ requests.  If the chain is
	 * exactly a WRITE->SEND_WITH_INV or a WRITE->SEND and the sgl depths
	 * and lengths meet the requirements of the fw_ri_ग_लिखो_cmpl_wr work
	 * request, then build and post the ग_लिखो_cmpl WR. If any of the tests
	 * below are not true, then we जारी on with the tradtional WRITE
	 * and SEND WRs.
	 */
	अगर (qhp->rhp->rdev.lldi.ग_लिखो_cmpl_support &&
	    CHELSIO_CHIP_VERSION(qhp->rhp->rdev.lldi.adapter_type) >=
	    CHELSIO_T5 &&
	    wr && wr->next && !wr->next->next &&
	    wr->opcode == IB_WR_RDMA_WRITE &&
	    wr->sg_list[0].length && wr->num_sge <= T4_WRITE_CMPL_MAX_SGL &&
	    (wr->next->opcode == IB_WR_SEND ||
	    wr->next->opcode == IB_WR_SEND_WITH_INV) &&
	    wr->next->sg_list[0].length == T4_WRITE_CMPL_MAX_CQE &&
	    wr->next->num_sge == 1 && num_wrs >= 2) अणु
		post_ग_लिखो_cmpl(qhp, wr);
		spin_unlock_irqrestore(&qhp->lock, flag);
		वापस 0;
	पूर्ण

	जबतक (wr) अणु
		अगर (num_wrs == 0) अणु
			err = -ENOMEM;
			*bad_wr = wr;
			अवरोध;
		पूर्ण
		wqe = (जोड़ t4_wr *)((u8 *)qhp->wq.sq.queue +
		      qhp->wq.sq.wq_pidx * T4_EQ_ENTRY_SIZE);

		fw_flags = 0;
		अगर (wr->send_flags & IB_SEND_SOLICITED)
			fw_flags |= FW_RI_SOLICITED_EVENT_FLAG;
		अगर (wr->send_flags & IB_SEND_SIGNALED || qhp->sq_sig_all)
			fw_flags |= FW_RI_COMPLETION_FLAG;
		swsqe = &qhp->wq.sq.sw_sq[qhp->wq.sq.pidx];
		चयन (wr->opcode) अणु
		हाल IB_WR_SEND_WITH_INV:
		हाल IB_WR_SEND:
			अगर (wr->send_flags & IB_SEND_FENCE)
				fw_flags |= FW_RI_READ_FENCE_FLAG;
			fw_opcode = FW_RI_SEND_WR;
			अगर (wr->opcode == IB_WR_SEND)
				swsqe->opcode = FW_RI_SEND;
			अन्यथा
				swsqe->opcode = FW_RI_SEND_WITH_INV;
			err = build_rdma_send(&qhp->wq.sq, wqe, wr, &len16);
			अवरोध;
		हाल IB_WR_RDMA_WRITE_WITH_IMM:
			अगर (unlikely(!rhp->rdev.lldi.ग_लिखो_w_imm_support)) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण
			fw_flags |= FW_RI_RDMA_WRITE_WITH_IMMEDIATE;
			fallthrough;
		हाल IB_WR_RDMA_WRITE:
			fw_opcode = FW_RI_RDMA_WRITE_WR;
			swsqe->opcode = FW_RI_RDMA_WRITE;
			err = build_rdma_ग_लिखो(&qhp->wq.sq, wqe, wr, &len16);
			अवरोध;
		हाल IB_WR_RDMA_READ:
		हाल IB_WR_RDMA_READ_WITH_INV:
			fw_opcode = FW_RI_RDMA_READ_WR;
			swsqe->opcode = FW_RI_READ_REQ;
			अगर (wr->opcode == IB_WR_RDMA_READ_WITH_INV) अणु
				c4iw_invalidate_mr(rhp, wr->sg_list[0].lkey);
				fw_flags = FW_RI_RDMA_READ_INVALIDATE;
			पूर्ण अन्यथा अणु
				fw_flags = 0;
			पूर्ण
			err = build_rdma_पढ़ो(wqe, wr, &len16);
			अगर (err)
				अवरोध;
			swsqe->पढ़ो_len = wr->sg_list[0].length;
			अगर (!qhp->wq.sq.oldest_पढ़ो)
				qhp->wq.sq.oldest_पढ़ो = swsqe;
			अवरोध;
		हाल IB_WR_REG_MR: अणु
			काष्ठा c4iw_mr *mhp = to_c4iw_mr(reg_wr(wr)->mr);

			swsqe->opcode = FW_RI_FAST_REGISTER;
			अगर (rhp->rdev.lldi.fr_nsmr_tpte_wr_support &&
			    !mhp->attr.state && mhp->mpl_len <= 2) अणु
				fw_opcode = FW_RI_FR_NSMR_TPTE_WR;
				build_tpte_memreg(&wqe->fr_tpte, reg_wr(wr),
						  mhp, &len16);
			पूर्ण अन्यथा अणु
				fw_opcode = FW_RI_FR_NSMR_WR;
				err = build_memreg(&qhp->wq.sq, wqe, reg_wr(wr),
				       mhp, &len16,
				       rhp->rdev.lldi.ulptx_memग_लिखो_dsgl);
				अगर (err)
					अवरोध;
			पूर्ण
			mhp->attr.state = 1;
			अवरोध;
		पूर्ण
		हाल IB_WR_LOCAL_INV:
			अगर (wr->send_flags & IB_SEND_FENCE)
				fw_flags |= FW_RI_LOCAL_FENCE_FLAG;
			fw_opcode = FW_RI_INV_LSTAG_WR;
			swsqe->opcode = FW_RI_LOCAL_INV;
			err = build_inv_stag(wqe, wr, &len16);
			c4iw_invalidate_mr(rhp, wr->ex.invalidate_rkey);
			अवरोध;
		शेष:
			pr_warn("%s post of type=%d TBD!\n", __func__,
				wr->opcode);
			err = -EINVAL;
		पूर्ण
		अगर (err) अणु
			*bad_wr = wr;
			अवरोध;
		पूर्ण
		swsqe->idx = qhp->wq.sq.pidx;
		swsqe->complete = 0;
		swsqe->संकेतed = (wr->send_flags & IB_SEND_SIGNALED) ||
				  qhp->sq_sig_all;
		swsqe->flushed = 0;
		swsqe->wr_id = wr->wr_id;
		अगर (c4iw_wr_log) अणु
			swsqe->sge_ts = cxgb4_पढ़ो_sge_बारtamp(
					rhp->rdev.lldi.ports[0]);
			swsqe->host_समय = kसमय_get();
		पूर्ण

		init_wr_hdr(wqe, qhp->wq.sq.pidx, fw_opcode, fw_flags, len16);

		pr_debug("cookie 0x%llx pidx 0x%x opcode 0x%x read_len %u\n",
			 (अचिन्हित दीर्घ दीर्घ)wr->wr_id, qhp->wq.sq.pidx,
			 swsqe->opcode, swsqe->पढ़ो_len);
		wr = wr->next;
		num_wrs--;
		t4_sq_produce(&qhp->wq, len16);
		idx += DIV_ROUND_UP(len16*16, T4_EQ_ENTRY_SIZE);
	पूर्ण
	अगर (!rhp->rdev.status_page->db_off) अणु
		t4_ring_sq_db(&qhp->wq, idx, wqe);
		spin_unlock_irqrestore(&qhp->lock, flag);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&qhp->lock, flag);
		ring_kernel_sq_db(qhp, idx);
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक c4iw_post_receive(काष्ठा ib_qp *ibqp, स्थिर काष्ठा ib_recv_wr *wr,
		      स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	पूर्णांक err = 0;
	काष्ठा c4iw_qp *qhp;
	जोड़ t4_recv_wr *wqe = शून्य;
	u32 num_wrs;
	u8 len16 = 0;
	अचिन्हित दीर्घ flag;
	u16 idx = 0;

	qhp = to_c4iw_qp(ibqp);
	spin_lock_irqsave(&qhp->lock, flag);

	/*
	 * If the qp has been flushed, then just insert a special
	 * drain cqe.
	 */
	अगर (qhp->wq.flushed) अणु
		spin_unlock_irqrestore(&qhp->lock, flag);
		complete_rq_drain_wrs(qhp, wr);
		वापस err;
	पूर्ण
	num_wrs = t4_rq_avail(&qhp->wq);
	अगर (num_wrs == 0) अणु
		spin_unlock_irqrestore(&qhp->lock, flag);
		*bad_wr = wr;
		वापस -ENOMEM;
	पूर्ण
	जबतक (wr) अणु
		अगर (wr->num_sge > T4_MAX_RECV_SGE) अणु
			err = -EINVAL;
			*bad_wr = wr;
			अवरोध;
		पूर्ण
		wqe = (जोड़ t4_recv_wr *)((u8 *)qhp->wq.rq.queue +
					   qhp->wq.rq.wq_pidx *
					   T4_EQ_ENTRY_SIZE);
		अगर (num_wrs)
			err = build_rdma_recv(qhp, wqe, wr, &len16);
		अन्यथा
			err = -ENOMEM;
		अगर (err) अणु
			*bad_wr = wr;
			अवरोध;
		पूर्ण

		qhp->wq.rq.sw_rq[qhp->wq.rq.pidx].wr_id = wr->wr_id;
		अगर (c4iw_wr_log) अणु
			qhp->wq.rq.sw_rq[qhp->wq.rq.pidx].sge_ts =
				cxgb4_पढ़ो_sge_बारtamp(
						qhp->rhp->rdev.lldi.ports[0]);
			qhp->wq.rq.sw_rq[qhp->wq.rq.pidx].host_समय =
				kसमय_get();
		पूर्ण

		wqe->recv.opcode = FW_RI_RECV_WR;
		wqe->recv.r1 = 0;
		wqe->recv.wrid = qhp->wq.rq.pidx;
		wqe->recv.r2[0] = 0;
		wqe->recv.r2[1] = 0;
		wqe->recv.r2[2] = 0;
		wqe->recv.len16 = len16;
		pr_debug("cookie 0x%llx pidx %u\n",
			 (अचिन्हित दीर्घ दीर्घ)wr->wr_id, qhp->wq.rq.pidx);
		t4_rq_produce(&qhp->wq, len16);
		idx += DIV_ROUND_UP(len16*16, T4_EQ_ENTRY_SIZE);
		wr = wr->next;
		num_wrs--;
	पूर्ण
	अगर (!qhp->rhp->rdev.status_page->db_off) अणु
		t4_ring_rq_db(&qhp->wq, idx, wqe);
		spin_unlock_irqrestore(&qhp->lock, flag);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&qhp->lock, flag);
		ring_kernel_rq_db(qhp, idx);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम defer_srq_wr(काष्ठा t4_srq *srq, जोड़ t4_recv_wr *wqe,
			 u64 wr_id, u8 len16)
अणु
	काष्ठा t4_srq_pending_wr *pwr = &srq->pending_wrs[srq->pending_pidx];

	pr_debug("%s cidx %u pidx %u wq_pidx %u in_use %u ooo_count %u wr_id 0x%llx pending_cidx %u pending_pidx %u pending_in_use %u\n",
		 __func__, srq->cidx, srq->pidx, srq->wq_pidx,
		 srq->in_use, srq->ooo_count,
		 (अचिन्हित दीर्घ दीर्घ)wr_id, srq->pending_cidx,
		 srq->pending_pidx, srq->pending_in_use);
	pwr->wr_id = wr_id;
	pwr->len16 = len16;
	स_नकल(&pwr->wqe, wqe, len16 * 16);
	t4_srq_produce_pending_wr(srq);
पूर्ण

पूर्णांक c4iw_post_srq_recv(काष्ठा ib_srq *ibsrq, स्थिर काष्ठा ib_recv_wr *wr,
		       स्थिर काष्ठा ib_recv_wr **bad_wr)
अणु
	जोड़ t4_recv_wr *wqe, lwqe;
	काष्ठा c4iw_srq *srq;
	अचिन्हित दीर्घ flag;
	u8 len16 = 0;
	u16 idx = 0;
	पूर्णांक err = 0;
	u32 num_wrs;

	srq = to_c4iw_srq(ibsrq);
	spin_lock_irqsave(&srq->lock, flag);
	num_wrs = t4_srq_avail(&srq->wq);
	अगर (num_wrs == 0) अणु
		spin_unlock_irqrestore(&srq->lock, flag);
		वापस -ENOMEM;
	पूर्ण
	जबतक (wr) अणु
		अगर (wr->num_sge > T4_MAX_RECV_SGE) अणु
			err = -EINVAL;
			*bad_wr = wr;
			अवरोध;
		पूर्ण
		wqe = &lwqe;
		अगर (num_wrs)
			err = build_srq_recv(wqe, wr, &len16);
		अन्यथा
			err = -ENOMEM;
		अगर (err) अणु
			*bad_wr = wr;
			अवरोध;
		पूर्ण

		wqe->recv.opcode = FW_RI_RECV_WR;
		wqe->recv.r1 = 0;
		wqe->recv.wrid = srq->wq.pidx;
		wqe->recv.r2[0] = 0;
		wqe->recv.r2[1] = 0;
		wqe->recv.r2[2] = 0;
		wqe->recv.len16 = len16;

		अगर (srq->wq.ooo_count ||
		    srq->wq.pending_in_use ||
		    srq->wq.sw_rq[srq->wq.pidx].valid) अणु
			defer_srq_wr(&srq->wq, wqe, wr->wr_id, len16);
		पूर्ण अन्यथा अणु
			srq->wq.sw_rq[srq->wq.pidx].wr_id = wr->wr_id;
			srq->wq.sw_rq[srq->wq.pidx].valid = 1;
			c4iw_copy_wr_to_srq(&srq->wq, wqe, len16);
			pr_debug("%s cidx %u pidx %u wq_pidx %u in_use %u wr_id 0x%llx\n",
				 __func__, srq->wq.cidx,
				 srq->wq.pidx, srq->wq.wq_pidx,
				 srq->wq.in_use,
				 (अचिन्हित दीर्घ दीर्घ)wr->wr_id);
			t4_srq_produce(&srq->wq, len16);
			idx += DIV_ROUND_UP(len16 * 16, T4_EQ_ENTRY_SIZE);
		पूर्ण
		wr = wr->next;
		num_wrs--;
	पूर्ण
	अगर (idx)
		t4_ring_srq_db(&srq->wq, idx, len16, wqe);
	spin_unlock_irqrestore(&srq->lock, flag);
	वापस err;
पूर्ण

अटल अंतरभूत व्योम build_term_codes(काष्ठा t4_cqe *err_cqe, u8 *layer_type,
				    u8 *ecode)
अणु
	पूर्णांक status;
	पूर्णांक tagged;
	पूर्णांक opcode;
	पूर्णांक rqtype;
	पूर्णांक send_inv;

	अगर (!err_cqe) अणु
		*layer_type = LAYER_RDMAP|DDP_LOCAL_CATA;
		*ecode = 0;
		वापस;
	पूर्ण

	status = CQE_STATUS(err_cqe);
	opcode = CQE_OPCODE(err_cqe);
	rqtype = RQ_TYPE(err_cqe);
	send_inv = (opcode == FW_RI_SEND_WITH_INV) ||
		   (opcode == FW_RI_SEND_WITH_SE_INV);
	tagged = (opcode == FW_RI_RDMA_WRITE) ||
		 (rqtype && (opcode == FW_RI_READ_RESP));

	चयन (status) अणु
	हाल T4_ERR_STAG:
		अगर (send_inv) अणु
			*layer_type = LAYER_RDMAP|RDMAP_REMOTE_OP;
			*ecode = RDMAP_CANT_INV_STAG;
		पूर्ण अन्यथा अणु
			*layer_type = LAYER_RDMAP|RDMAP_REMOTE_PROT;
			*ecode = RDMAP_INV_STAG;
		पूर्ण
		अवरोध;
	हाल T4_ERR_PDID:
		*layer_type = LAYER_RDMAP|RDMAP_REMOTE_PROT;
		अगर ((opcode == FW_RI_SEND_WITH_INV) ||
		    (opcode == FW_RI_SEND_WITH_SE_INV))
			*ecode = RDMAP_CANT_INV_STAG;
		अन्यथा
			*ecode = RDMAP_STAG_NOT_ASSOC;
		अवरोध;
	हाल T4_ERR_QPID:
		*layer_type = LAYER_RDMAP|RDMAP_REMOTE_PROT;
		*ecode = RDMAP_STAG_NOT_ASSOC;
		अवरोध;
	हाल T4_ERR_ACCESS:
		*layer_type = LAYER_RDMAP|RDMAP_REMOTE_PROT;
		*ecode = RDMAP_ACC_VIOL;
		अवरोध;
	हाल T4_ERR_WRAP:
		*layer_type = LAYER_RDMAP|RDMAP_REMOTE_PROT;
		*ecode = RDMAP_TO_WRAP;
		अवरोध;
	हाल T4_ERR_BOUND:
		अगर (tagged) अणु
			*layer_type = LAYER_DDP|DDP_TAGGED_ERR;
			*ecode = DDPT_BASE_BOUNDS;
		पूर्ण अन्यथा अणु
			*layer_type = LAYER_RDMAP|RDMAP_REMOTE_PROT;
			*ecode = RDMAP_BASE_BOUNDS;
		पूर्ण
		अवरोध;
	हाल T4_ERR_INVALIDATE_SHARED_MR:
	हाल T4_ERR_INVALIDATE_MR_WITH_MW_BOUND:
		*layer_type = LAYER_RDMAP|RDMAP_REMOTE_OP;
		*ecode = RDMAP_CANT_INV_STAG;
		अवरोध;
	हाल T4_ERR_ECC:
	हाल T4_ERR_ECC_PSTAG:
	हाल T4_ERR_INTERNAL_ERR:
		*layer_type = LAYER_RDMAP|RDMAP_LOCAL_CATA;
		*ecode = 0;
		अवरोध;
	हाल T4_ERR_OUT_OF_RQE:
		*layer_type = LAYER_DDP|DDP_UNTAGGED_ERR;
		*ecode = DDPU_INV_MSN_NOBUF;
		अवरोध;
	हाल T4_ERR_PBL_ADDR_BOUND:
		*layer_type = LAYER_DDP|DDP_TAGGED_ERR;
		*ecode = DDPT_BASE_BOUNDS;
		अवरोध;
	हाल T4_ERR_CRC:
		*layer_type = LAYER_MPA|DDP_LLP;
		*ecode = MPA_CRC_ERR;
		अवरोध;
	हाल T4_ERR_MARKER:
		*layer_type = LAYER_MPA|DDP_LLP;
		*ecode = MPA_MARKER_ERR;
		अवरोध;
	हाल T4_ERR_PDU_LEN_ERR:
		*layer_type = LAYER_DDP|DDP_UNTAGGED_ERR;
		*ecode = DDPU_MSG_TOOBIG;
		अवरोध;
	हाल T4_ERR_DDP_VERSION:
		अगर (tagged) अणु
			*layer_type = LAYER_DDP|DDP_TAGGED_ERR;
			*ecode = DDPT_INV_VERS;
		पूर्ण अन्यथा अणु
			*layer_type = LAYER_DDP|DDP_UNTAGGED_ERR;
			*ecode = DDPU_INV_VERS;
		पूर्ण
		अवरोध;
	हाल T4_ERR_RDMA_VERSION:
		*layer_type = LAYER_RDMAP|RDMAP_REMOTE_OP;
		*ecode = RDMAP_INV_VERS;
		अवरोध;
	हाल T4_ERR_OPCODE:
		*layer_type = LAYER_RDMAP|RDMAP_REMOTE_OP;
		*ecode = RDMAP_INV_OPCODE;
		अवरोध;
	हाल T4_ERR_DDP_QUEUE_NUM:
		*layer_type = LAYER_DDP|DDP_UNTAGGED_ERR;
		*ecode = DDPU_INV_QN;
		अवरोध;
	हाल T4_ERR_MSN:
	हाल T4_ERR_MSN_GAP:
	हाल T4_ERR_MSN_RANGE:
	हाल T4_ERR_IRD_OVERFLOW:
		*layer_type = LAYER_DDP|DDP_UNTAGGED_ERR;
		*ecode = DDPU_INV_MSN_RANGE;
		अवरोध;
	हाल T4_ERR_TBIT:
		*layer_type = LAYER_DDP|DDP_LOCAL_CATA;
		*ecode = 0;
		अवरोध;
	हाल T4_ERR_MO:
		*layer_type = LAYER_DDP|DDP_UNTAGGED_ERR;
		*ecode = DDPU_INV_MO;
		अवरोध;
	शेष:
		*layer_type = LAYER_RDMAP|DDP_LOCAL_CATA;
		*ecode = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम post_terminate(काष्ठा c4iw_qp *qhp, काष्ठा t4_cqe *err_cqe,
			   gfp_t gfp)
अणु
	काष्ठा fw_ri_wr *wqe;
	काष्ठा sk_buff *skb;
	काष्ठा terminate_message *term;

	pr_debug("qhp %p qid 0x%x tid %u\n", qhp, qhp->wq.sq.qid,
		 qhp->ep->hwtid);

	skb = skb_dequeue(&qhp->ep->com.ep_skb_list);
	अगर (WARN_ON(!skb))
		वापस;

	set_wr_txq(skb, CPL_PRIORITY_DATA, qhp->ep->txq_idx);

	wqe = __skb_put_zero(skb, माप(*wqe));
	wqe->op_compl = cpu_to_be32(FW_WR_OP_V(FW_RI_INIT_WR));
	wqe->flowid_len16 = cpu_to_be32(
		FW_WR_FLOWID_V(qhp->ep->hwtid) |
		FW_WR_LEN16_V(DIV_ROUND_UP(माप(*wqe), 16)));

	wqe->u.terminate.type = FW_RI_TYPE_TERMINATE;
	wqe->u.terminate.immdlen = cpu_to_be32(माप(*term));
	term = (काष्ठा terminate_message *)wqe->u.terminate.termmsg;
	अगर (qhp->attr.layer_etype == (LAYER_MPA|DDP_LLP)) अणु
		term->layer_etype = qhp->attr.layer_etype;
		term->ecode = qhp->attr.ecode;
	पूर्ण अन्यथा
		build_term_codes(err_cqe, &term->layer_etype, &term->ecode);
	c4iw_ofld_send(&qhp->rhp->rdev, skb);
पूर्ण

/*
 * Assumes qhp lock is held.
 */
अटल व्योम __flush_qp(काष्ठा c4iw_qp *qhp, काष्ठा c4iw_cq *rchp,
		       काष्ठा c4iw_cq *schp)
अणु
	पूर्णांक count;
	पूर्णांक rq_flushed = 0, sq_flushed;
	अचिन्हित दीर्घ flag;

	pr_debug("qhp %p rchp %p schp %p\n", qhp, rchp, schp);

	/* locking hierarchy: cqs lock first, then qp lock. */
	spin_lock_irqsave(&rchp->lock, flag);
	अगर (schp != rchp)
		spin_lock(&schp->lock);
	spin_lock(&qhp->lock);

	अगर (qhp->wq.flushed) अणु
		spin_unlock(&qhp->lock);
		अगर (schp != rchp)
			spin_unlock(&schp->lock);
		spin_unlock_irqrestore(&rchp->lock, flag);
		वापस;
	पूर्ण
	qhp->wq.flushed = 1;
	t4_set_wq_in_error(&qhp->wq, 0);

	c4iw_flush_hw_cq(rchp, qhp);
	अगर (!qhp->srq) अणु
		c4iw_count_rcqes(&rchp->cq, &qhp->wq, &count);
		rq_flushed = c4iw_flush_rq(&qhp->wq, &rchp->cq, count);
	पूर्ण

	अगर (schp != rchp)
		c4iw_flush_hw_cq(schp, qhp);
	sq_flushed = c4iw_flush_sq(qhp);

	spin_unlock(&qhp->lock);
	अगर (schp != rchp)
		spin_unlock(&schp->lock);
	spin_unlock_irqrestore(&rchp->lock, flag);

	अगर (schp == rchp) अणु
		अगर ((rq_flushed || sq_flushed) &&
		    t4_clear_cq_armed(&rchp->cq)) अणु
			spin_lock_irqsave(&rchp->comp_handler_lock, flag);
			(*rchp->ibcq.comp_handler)(&rchp->ibcq,
						   rchp->ibcq.cq_context);
			spin_unlock_irqrestore(&rchp->comp_handler_lock, flag);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (rq_flushed && t4_clear_cq_armed(&rchp->cq)) अणु
			spin_lock_irqsave(&rchp->comp_handler_lock, flag);
			(*rchp->ibcq.comp_handler)(&rchp->ibcq,
						   rchp->ibcq.cq_context);
			spin_unlock_irqrestore(&rchp->comp_handler_lock, flag);
		पूर्ण
		अगर (sq_flushed && t4_clear_cq_armed(&schp->cq)) अणु
			spin_lock_irqsave(&schp->comp_handler_lock, flag);
			(*schp->ibcq.comp_handler)(&schp->ibcq,
						   schp->ibcq.cq_context);
			spin_unlock_irqrestore(&schp->comp_handler_lock, flag);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम flush_qp(काष्ठा c4iw_qp *qhp)
अणु
	काष्ठा c4iw_cq *rchp, *schp;
	अचिन्हित दीर्घ flag;

	rchp = to_c4iw_cq(qhp->ibqp.recv_cq);
	schp = to_c4iw_cq(qhp->ibqp.send_cq);

	अगर (qhp->ibqp.uobject) अणु

		/* क्रम user qps, qhp->wq.flushed is रक्षित by qhp->mutex */
		अगर (qhp->wq.flushed)
			वापस;

		qhp->wq.flushed = 1;
		t4_set_wq_in_error(&qhp->wq, 0);
		t4_set_cq_in_error(&rchp->cq);
		spin_lock_irqsave(&rchp->comp_handler_lock, flag);
		(*rchp->ibcq.comp_handler)(&rchp->ibcq, rchp->ibcq.cq_context);
		spin_unlock_irqrestore(&rchp->comp_handler_lock, flag);
		अगर (schp != rchp) अणु
			t4_set_cq_in_error(&schp->cq);
			spin_lock_irqsave(&schp->comp_handler_lock, flag);
			(*schp->ibcq.comp_handler)(&schp->ibcq,
					schp->ibcq.cq_context);
			spin_unlock_irqrestore(&schp->comp_handler_lock, flag);
		पूर्ण
		वापस;
	पूर्ण
	__flush_qp(qhp, rchp, schp);
पूर्ण

अटल पूर्णांक rdma_fini(काष्ठा c4iw_dev *rhp, काष्ठा c4iw_qp *qhp,
		     काष्ठा c4iw_ep *ep)
अणु
	काष्ठा fw_ri_wr *wqe;
	पूर्णांक ret;
	काष्ठा sk_buff *skb;

	pr_debug("qhp %p qid 0x%x tid %u\n", qhp, qhp->wq.sq.qid, ep->hwtid);

	skb = skb_dequeue(&ep->com.ep_skb_list);
	अगर (WARN_ON(!skb))
		वापस -ENOMEM;

	set_wr_txq(skb, CPL_PRIORITY_DATA, ep->txq_idx);

	wqe = __skb_put_zero(skb, माप(*wqe));
	wqe->op_compl = cpu_to_be32(
		FW_WR_OP_V(FW_RI_INIT_WR) |
		FW_WR_COMPL_F);
	wqe->flowid_len16 = cpu_to_be32(
		FW_WR_FLOWID_V(ep->hwtid) |
		FW_WR_LEN16_V(DIV_ROUND_UP(माप(*wqe), 16)));
	wqe->cookie = (uपूर्णांकptr_t)ep->com.wr_रुकोp;

	wqe->u.fini.type = FW_RI_TYPE_FINI;

	ret = c4iw_ref_send_रुको(&rhp->rdev, skb, ep->com.wr_रुकोp,
				 qhp->ep->hwtid, qhp->wq.sq.qid, __func__);

	pr_debug("ret %d\n", ret);
	वापस ret;
पूर्ण

अटल व्योम build_rtr_msg(u8 p2p_type, काष्ठा fw_ri_init *init)
अणु
	pr_debug("p2p_type = %d\n", p2p_type);
	स_रखो(&init->u, 0, माप(init->u));
	चयन (p2p_type) अणु
	हाल FW_RI_INIT_P2PTYPE_RDMA_WRITE:
		init->u.ग_लिखो.opcode = FW_RI_RDMA_WRITE_WR;
		init->u.ग_लिखो.stag_sink = cpu_to_be32(1);
		init->u.ग_लिखो.to_sink = cpu_to_be64(1);
		init->u.ग_लिखो.u.immd_src[0].op = FW_RI_DATA_IMMD;
		init->u.ग_लिखो.len16 = DIV_ROUND_UP(
			माप(init->u.ग_लिखो) + माप(काष्ठा fw_ri_immd), 16);
		अवरोध;
	हाल FW_RI_INIT_P2PTYPE_READ_REQ:
		init->u.ग_लिखो.opcode = FW_RI_RDMA_READ_WR;
		init->u.पढ़ो.stag_src = cpu_to_be32(1);
		init->u.पढ़ो.to_src_lo = cpu_to_be32(1);
		init->u.पढ़ो.stag_sink = cpu_to_be32(1);
		init->u.पढ़ो.to_sink_lo = cpu_to_be32(1);
		init->u.पढ़ो.len16 = DIV_ROUND_UP(माप(init->u.पढ़ो), 16);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक rdma_init(काष्ठा c4iw_dev *rhp, काष्ठा c4iw_qp *qhp)
अणु
	काष्ठा fw_ri_wr *wqe;
	पूर्णांक ret;
	काष्ठा sk_buff *skb;

	pr_debug("qhp %p qid 0x%x tid %u ird %u ord %u\n", qhp,
		 qhp->wq.sq.qid, qhp->ep->hwtid, qhp->ep->ird, qhp->ep->ord);

	skb = alloc_skb(माप(*wqe), GFP_KERNEL);
	अगर (!skb) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	ret = alloc_ird(rhp, qhp->attr.max_ird);
	अगर (ret) अणु
		qhp->attr.max_ird = 0;
		kमुक्त_skb(skb);
		जाओ out;
	पूर्ण
	set_wr_txq(skb, CPL_PRIORITY_DATA, qhp->ep->txq_idx);

	wqe = __skb_put_zero(skb, माप(*wqe));
	wqe->op_compl = cpu_to_be32(
		FW_WR_OP_V(FW_RI_INIT_WR) |
		FW_WR_COMPL_F);
	wqe->flowid_len16 = cpu_to_be32(
		FW_WR_FLOWID_V(qhp->ep->hwtid) |
		FW_WR_LEN16_V(DIV_ROUND_UP(माप(*wqe), 16)));

	wqe->cookie = (uपूर्णांकptr_t)qhp->ep->com.wr_रुकोp;

	wqe->u.init.type = FW_RI_TYPE_INIT;
	wqe->u.init.mpareqbit_p2ptype =
		FW_RI_WR_MPAREQBIT_V(qhp->attr.mpa_attr.initiator) |
		FW_RI_WR_P2PTYPE_V(qhp->attr.mpa_attr.p2p_type);
	wqe->u.init.mpa_attrs = FW_RI_MPA_IETF_ENABLE;
	अगर (qhp->attr.mpa_attr.recv_marker_enabled)
		wqe->u.init.mpa_attrs |= FW_RI_MPA_RX_MARKER_ENABLE;
	अगर (qhp->attr.mpa_attr.xmit_marker_enabled)
		wqe->u.init.mpa_attrs |= FW_RI_MPA_TX_MARKER_ENABLE;
	अगर (qhp->attr.mpa_attr.crc_enabled)
		wqe->u.init.mpa_attrs |= FW_RI_MPA_CRC_ENABLE;

	wqe->u.init.qp_caps = FW_RI_QP_RDMA_READ_ENABLE |
			    FW_RI_QP_RDMA_WRITE_ENABLE |
			    FW_RI_QP_BIND_ENABLE;
	अगर (!qhp->ibqp.uobject)
		wqe->u.init.qp_caps |= FW_RI_QP_FAST_REGISTER_ENABLE |
				     FW_RI_QP_STAG0_ENABLE;
	wqe->u.init.nrqe = cpu_to_be16(t4_rqes_posted(&qhp->wq));
	wqe->u.init.pdid = cpu_to_be32(qhp->attr.pd);
	wqe->u.init.qpid = cpu_to_be32(qhp->wq.sq.qid);
	wqe->u.init.sq_eqid = cpu_to_be32(qhp->wq.sq.qid);
	अगर (qhp->srq) अणु
		wqe->u.init.rq_eqid = cpu_to_be32(FW_RI_INIT_RQEQID_SRQ |
						  qhp->srq->idx);
	पूर्ण अन्यथा अणु
		wqe->u.init.rq_eqid = cpu_to_be32(qhp->wq.rq.qid);
		wqe->u.init.hwrqsize = cpu_to_be32(qhp->wq.rq.rqt_size);
		wqe->u.init.hwrqaddr = cpu_to_be32(qhp->wq.rq.rqt_hwaddr -
						   rhp->rdev.lldi.vr->rq.start);
	पूर्ण
	wqe->u.init.scqid = cpu_to_be32(qhp->attr.scq);
	wqe->u.init.rcqid = cpu_to_be32(qhp->attr.rcq);
	wqe->u.init.ord_max = cpu_to_be32(qhp->attr.max_ord);
	wqe->u.init.ird_max = cpu_to_be32(qhp->attr.max_ird);
	wqe->u.init.iss = cpu_to_be32(qhp->ep->snd_seq);
	wqe->u.init.irs = cpu_to_be32(qhp->ep->rcv_seq);
	अगर (qhp->attr.mpa_attr.initiator)
		build_rtr_msg(qhp->attr.mpa_attr.p2p_type, &wqe->u.init);

	ret = c4iw_ref_send_रुको(&rhp->rdev, skb, qhp->ep->com.wr_रुकोp,
				 qhp->ep->hwtid, qhp->wq.sq.qid, __func__);
	अगर (!ret)
		जाओ out;

	मुक्त_ird(rhp, qhp->attr.max_ird);
out:
	pr_debug("ret %d\n", ret);
	वापस ret;
पूर्ण

पूर्णांक c4iw_modअगरy_qp(काष्ठा c4iw_dev *rhp, काष्ठा c4iw_qp *qhp,
		   क्रमागत c4iw_qp_attr_mask mask,
		   काष्ठा c4iw_qp_attributes *attrs,
		   पूर्णांक पूर्णांकernal)
अणु
	पूर्णांक ret = 0;
	काष्ठा c4iw_qp_attributes newattr = qhp->attr;
	पूर्णांक disconnect = 0;
	पूर्णांक terminate = 0;
	पूर्णांक पात = 0;
	पूर्णांक मुक्त = 0;
	काष्ठा c4iw_ep *ep = शून्य;

	pr_debug("qhp %p sqid 0x%x rqid 0x%x ep %p state %d -> %d\n",
		 qhp, qhp->wq.sq.qid, qhp->wq.rq.qid, qhp->ep, qhp->attr.state,
		 (mask & C4IW_QP_ATTR_NEXT_STATE) ? attrs->next_state : -1);

	mutex_lock(&qhp->mutex);

	/* Process attr changes अगर in IDLE */
	अगर (mask & C4IW_QP_ATTR_VALID_MODIFY) अणु
		अगर (qhp->attr.state != C4IW_QP_STATE_IDLE) अणु
			ret = -EIO;
			जाओ out;
		पूर्ण
		अगर (mask & C4IW_QP_ATTR_ENABLE_RDMA_READ)
			newattr.enable_rdma_पढ़ो = attrs->enable_rdma_पढ़ो;
		अगर (mask & C4IW_QP_ATTR_ENABLE_RDMA_WRITE)
			newattr.enable_rdma_ग_लिखो = attrs->enable_rdma_ग_लिखो;
		अगर (mask & C4IW_QP_ATTR_ENABLE_RDMA_BIND)
			newattr.enable_bind = attrs->enable_bind;
		अगर (mask & C4IW_QP_ATTR_MAX_ORD) अणु
			अगर (attrs->max_ord > c4iw_max_पढ़ो_depth) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			newattr.max_ord = attrs->max_ord;
		पूर्ण
		अगर (mask & C4IW_QP_ATTR_MAX_IRD) अणु
			अगर (attrs->max_ird > cur_max_पढ़ो_depth(rhp)) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			newattr.max_ird = attrs->max_ird;
		पूर्ण
		qhp->attr = newattr;
	पूर्ण

	अगर (mask & C4IW_QP_ATTR_SQ_DB) अणु
		ret = ring_kernel_sq_db(qhp, attrs->sq_db_inc);
		जाओ out;
	पूर्ण
	अगर (mask & C4IW_QP_ATTR_RQ_DB) अणु
		ret = ring_kernel_rq_db(qhp, attrs->rq_db_inc);
		जाओ out;
	पूर्ण

	अगर (!(mask & C4IW_QP_ATTR_NEXT_STATE))
		जाओ out;
	अगर (qhp->attr.state == attrs->next_state)
		जाओ out;

	चयन (qhp->attr.state) अणु
	हाल C4IW_QP_STATE_IDLE:
		चयन (attrs->next_state) अणु
		हाल C4IW_QP_STATE_RTS:
			अगर (!(mask & C4IW_QP_ATTR_LLP_STREAM_HANDLE)) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			अगर (!(mask & C4IW_QP_ATTR_MPA_ATTR)) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			qhp->attr.mpa_attr = attrs->mpa_attr;
			qhp->attr.llp_stream_handle = attrs->llp_stream_handle;
			qhp->ep = qhp->attr.llp_stream_handle;
			set_state(qhp, C4IW_QP_STATE_RTS);

			/*
			 * Ref the endpoपूर्णांक here and deref when we
			 * disassociate the endpoपूर्णांक from the QP.  This
			 * happens in CLOSING->IDLE transition or *->ERROR
			 * transition.
			 */
			c4iw_get_ep(&qhp->ep->com);
			ret = rdma_init(rhp, qhp);
			अगर (ret)
				जाओ err;
			अवरोध;
		हाल C4IW_QP_STATE_ERROR:
			set_state(qhp, C4IW_QP_STATE_ERROR);
			flush_qp(qhp);
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		अवरोध;
	हाल C4IW_QP_STATE_RTS:
		चयन (attrs->next_state) अणु
		हाल C4IW_QP_STATE_CLOSING:
			t4_set_wq_in_error(&qhp->wq, 0);
			set_state(qhp, C4IW_QP_STATE_CLOSING);
			ep = qhp->ep;
			अगर (!पूर्णांकernal) अणु
				पात = 0;
				disconnect = 1;
				c4iw_get_ep(&qhp->ep->com);
			पूर्ण
			ret = rdma_fini(rhp, qhp, ep);
			अगर (ret)
				जाओ err;
			अवरोध;
		हाल C4IW_QP_STATE_TERMINATE:
			t4_set_wq_in_error(&qhp->wq, 0);
			set_state(qhp, C4IW_QP_STATE_TERMINATE);
			qhp->attr.layer_etype = attrs->layer_etype;
			qhp->attr.ecode = attrs->ecode;
			ep = qhp->ep;
			अगर (!पूर्णांकernal) अणु
				c4iw_get_ep(&ep->com);
				terminate = 1;
				disconnect = 1;
			पूर्ण अन्यथा अणु
				terminate = qhp->attr.send_term;
				ret = rdma_fini(rhp, qhp, ep);
				अगर (ret)
					जाओ err;
			पूर्ण
			अवरोध;
		हाल C4IW_QP_STATE_ERROR:
			t4_set_wq_in_error(&qhp->wq, 0);
			set_state(qhp, C4IW_QP_STATE_ERROR);
			अगर (!पूर्णांकernal) अणु
				पात = 1;
				disconnect = 1;
				ep = qhp->ep;
				c4iw_get_ep(&qhp->ep->com);
			पूर्ण
			जाओ err;
			अवरोध;
		शेष:
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		अवरोध;
	हाल C4IW_QP_STATE_CLOSING:

		/*
		 * Allow kernel users to move to ERROR क्रम qp draining.
		 */
		अगर (!पूर्णांकernal && (qhp->ibqp.uobject || attrs->next_state !=
				  C4IW_QP_STATE_ERROR)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		चयन (attrs->next_state) अणु
		हाल C4IW_QP_STATE_IDLE:
			flush_qp(qhp);
			set_state(qhp, C4IW_QP_STATE_IDLE);
			qhp->attr.llp_stream_handle = शून्य;
			c4iw_put_ep(&qhp->ep->com);
			qhp->ep = शून्य;
			wake_up(&qhp->रुको);
			अवरोध;
		हाल C4IW_QP_STATE_ERROR:
			जाओ err;
		शेष:
			ret = -EINVAL;
			जाओ err;
		पूर्ण
		अवरोध;
	हाल C4IW_QP_STATE_ERROR:
		अगर (attrs->next_state != C4IW_QP_STATE_IDLE) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		अगर (!t4_sq_empty(&qhp->wq) || !t4_rq_empty(&qhp->wq)) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		set_state(qhp, C4IW_QP_STATE_IDLE);
		अवरोध;
	हाल C4IW_QP_STATE_TERMINATE:
		अगर (!पूर्णांकernal) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		जाओ err;
		अवरोध;
	शेष:
		pr_err("%s in a bad state %d\n", __func__, qhp->attr.state);
		ret = -EINVAL;
		जाओ err;
		अवरोध;
	पूर्ण
	जाओ out;
err:
	pr_debug("disassociating ep %p qpid 0x%x\n", qhp->ep,
		 qhp->wq.sq.qid);

	/* disassociate the LLP connection */
	qhp->attr.llp_stream_handle = शून्य;
	अगर (!ep)
		ep = qhp->ep;
	qhp->ep = शून्य;
	set_state(qhp, C4IW_QP_STATE_ERROR);
	मुक्त = 1;
	पात = 1;
	flush_qp(qhp);
	wake_up(&qhp->रुको);
out:
	mutex_unlock(&qhp->mutex);

	अगर (terminate)
		post_terminate(qhp, शून्य, पूर्णांकernal ? GFP_ATOMIC : GFP_KERNEL);

	/*
	 * If disconnect is 1, then we need to initiate a disconnect
	 * on the EP.  This can be a normal बंद (RTS->CLOSING) or
	 * an abnormal बंद (RTS/CLOSING->ERROR).
	 */
	अगर (disconnect) अणु
		c4iw_ep_disconnect(ep, पात, पूर्णांकernal ? GFP_ATOMIC :
							 GFP_KERNEL);
		c4iw_put_ep(&ep->com);
	पूर्ण

	/*
	 * If मुक्त is 1, then we've disassociated the EP from the QP
	 * and we need to dereference the EP.
	 */
	अगर (मुक्त)
		c4iw_put_ep(&ep->com);
	pr_debug("exit state %d\n", qhp->attr.state);
	वापस ret;
पूर्ण

पूर्णांक c4iw_destroy_qp(काष्ठा ib_qp *ib_qp, काष्ठा ib_udata *udata)
अणु
	काष्ठा c4iw_dev *rhp;
	काष्ठा c4iw_qp *qhp;
	काष्ठा c4iw_ucontext *ucontext;
	काष्ठा c4iw_qp_attributes attrs;

	qhp = to_c4iw_qp(ib_qp);
	rhp = qhp->rhp;
	ucontext = qhp->ucontext;

	attrs.next_state = C4IW_QP_STATE_ERROR;
	अगर (qhp->attr.state == C4IW_QP_STATE_TERMINATE)
		c4iw_modअगरy_qp(rhp, qhp, C4IW_QP_ATTR_NEXT_STATE, &attrs, 1);
	अन्यथा
		c4iw_modअगरy_qp(rhp, qhp, C4IW_QP_ATTR_NEXT_STATE, &attrs, 0);
	रुको_event(qhp->रुको, !qhp->ep);

	xa_lock_irq(&rhp->qps);
	__xa_erase(&rhp->qps, qhp->wq.sq.qid);
	अगर (!list_empty(&qhp->db_fc_entry))
		list_del_init(&qhp->db_fc_entry);
	xa_unlock_irq(&rhp->qps);
	मुक्त_ird(rhp, qhp->attr.max_ird);

	c4iw_qp_rem_ref(ib_qp);

	रुको_क्रम_completion(&qhp->qp_rel_comp);

	pr_debug("ib_qp %p qpid 0x%0x\n", ib_qp, qhp->wq.sq.qid);
	pr_debug("qhp %p ucontext %p\n", qhp, ucontext);

	destroy_qp(&rhp->rdev, &qhp->wq,
		   ucontext ? &ucontext->uctx : &rhp->rdev.uctx, !qhp->srq);

	c4iw_put_wr_रुको(qhp->wr_रुकोp);

	kमुक्त(qhp);
	वापस 0;
पूर्ण

काष्ठा ib_qp *c4iw_create_qp(काष्ठा ib_pd *pd, काष्ठा ib_qp_init_attr *attrs,
			     काष्ठा ib_udata *udata)
अणु
	काष्ठा c4iw_dev *rhp;
	काष्ठा c4iw_qp *qhp;
	काष्ठा c4iw_pd *php;
	काष्ठा c4iw_cq *schp;
	काष्ठा c4iw_cq *rchp;
	काष्ठा c4iw_create_qp_resp uresp;
	अचिन्हित पूर्णांक sqsize, rqsize = 0;
	काष्ठा c4iw_ucontext *ucontext = rdma_udata_to_drv_context(
		udata, काष्ठा c4iw_ucontext, ibucontext);
	पूर्णांक ret;
	काष्ठा c4iw_mm_entry *sq_key_mm, *rq_key_mm = शून्य, *sq_db_key_mm;
	काष्ठा c4iw_mm_entry *rq_db_key_mm = शून्य, *ma_sync_key_mm = शून्य;

	pr_debug("ib_pd %p\n", pd);

	अगर (attrs->qp_type != IB_QPT_RC || attrs->create_flags)
		वापस ERR_PTR(-EOPNOTSUPP);

	php = to_c4iw_pd(pd);
	rhp = php->rhp;
	schp = get_chp(rhp, ((काष्ठा c4iw_cq *)attrs->send_cq)->cq.cqid);
	rchp = get_chp(rhp, ((काष्ठा c4iw_cq *)attrs->recv_cq)->cq.cqid);
	अगर (!schp || !rchp)
		वापस ERR_PTR(-EINVAL);

	अगर (attrs->cap.max_अंतरभूत_data > T4_MAX_SEND_INLINE)
		वापस ERR_PTR(-EINVAL);

	अगर (!attrs->srq) अणु
		अगर (attrs->cap.max_recv_wr > rhp->rdev.hw_queue.t4_max_rq_size)
			वापस ERR_PTR(-E2BIG);
		rqsize = attrs->cap.max_recv_wr + 1;
		अगर (rqsize < 8)
			rqsize = 8;
	पूर्ण

	अगर (attrs->cap.max_send_wr > rhp->rdev.hw_queue.t4_max_sq_size)
		वापस ERR_PTR(-E2BIG);
	sqsize = attrs->cap.max_send_wr + 1;
	अगर (sqsize < 8)
		sqsize = 8;

	qhp = kzalloc(माप(*qhp), GFP_KERNEL);
	अगर (!qhp)
		वापस ERR_PTR(-ENOMEM);

	qhp->wr_रुकोp = c4iw_alloc_wr_रुको(GFP_KERNEL);
	अगर (!qhp->wr_रुकोp) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_qhp;
	पूर्ण

	qhp->wq.sq.size = sqsize;
	qhp->wq.sq.memsize =
		(sqsize + rhp->rdev.hw_queue.t4_eq_status_entries) *
		माप(*qhp->wq.sq.queue) + 16 * माप(__be64);
	qhp->wq.sq.flush_cidx = -1;
	अगर (!attrs->srq) अणु
		qhp->wq.rq.size = rqsize;
		qhp->wq.rq.memsize =
			(rqsize + rhp->rdev.hw_queue.t4_eq_status_entries) *
			माप(*qhp->wq.rq.queue);
	पूर्ण

	अगर (ucontext) अणु
		qhp->wq.sq.memsize = roundup(qhp->wq.sq.memsize, PAGE_SIZE);
		अगर (!attrs->srq)
			qhp->wq.rq.memsize =
				roundup(qhp->wq.rq.memsize, PAGE_SIZE);
	पूर्ण

	ret = create_qp(&rhp->rdev, &qhp->wq, &schp->cq, &rchp->cq,
			ucontext ? &ucontext->uctx : &rhp->rdev.uctx,
			qhp->wr_रुकोp, !attrs->srq);
	अगर (ret)
		जाओ err_मुक्त_wr_रुको;

	attrs->cap.max_recv_wr = rqsize - 1;
	attrs->cap.max_send_wr = sqsize - 1;
	attrs->cap.max_अंतरभूत_data = T4_MAX_SEND_INLINE;

	qhp->rhp = rhp;
	qhp->attr.pd = php->pdid;
	qhp->attr.scq = ((काष्ठा c4iw_cq *) attrs->send_cq)->cq.cqid;
	qhp->attr.rcq = ((काष्ठा c4iw_cq *) attrs->recv_cq)->cq.cqid;
	qhp->attr.sq_num_entries = attrs->cap.max_send_wr;
	qhp->attr.sq_max_sges = attrs->cap.max_send_sge;
	qhp->attr.sq_max_sges_rdma_ग_लिखो = attrs->cap.max_send_sge;
	अगर (!attrs->srq) अणु
		qhp->attr.rq_num_entries = attrs->cap.max_recv_wr;
		qhp->attr.rq_max_sges = attrs->cap.max_recv_sge;
	पूर्ण
	qhp->attr.state = C4IW_QP_STATE_IDLE;
	qhp->attr.next_state = C4IW_QP_STATE_IDLE;
	qhp->attr.enable_rdma_पढ़ो = 1;
	qhp->attr.enable_rdma_ग_लिखो = 1;
	qhp->attr.enable_bind = 1;
	qhp->attr.max_ord = 0;
	qhp->attr.max_ird = 0;
	qhp->sq_sig_all = attrs->sq_sig_type == IB_SIGNAL_ALL_WR;
	spin_lock_init(&qhp->lock);
	mutex_init(&qhp->mutex);
	init_रुकोqueue_head(&qhp->रुको);
	init_completion(&qhp->qp_rel_comp);
	refcount_set(&qhp->qp_refcnt, 1);

	ret = xa_insert_irq(&rhp->qps, qhp->wq.sq.qid, qhp, GFP_KERNEL);
	अगर (ret)
		जाओ err_destroy_qp;

	अगर (udata && ucontext) अणु
		sq_key_mm = kदो_स्मृति(माप(*sq_key_mm), GFP_KERNEL);
		अगर (!sq_key_mm) अणु
			ret = -ENOMEM;
			जाओ err_हटाओ_handle;
		पूर्ण
		अगर (!attrs->srq) अणु
			rq_key_mm = kदो_स्मृति(माप(*rq_key_mm), GFP_KERNEL);
			अगर (!rq_key_mm) अणु
				ret = -ENOMEM;
				जाओ err_मुक्त_sq_key;
			पूर्ण
		पूर्ण
		sq_db_key_mm = kदो_स्मृति(माप(*sq_db_key_mm), GFP_KERNEL);
		अगर (!sq_db_key_mm) अणु
			ret = -ENOMEM;
			जाओ err_मुक्त_rq_key;
		पूर्ण
		अगर (!attrs->srq) अणु
			rq_db_key_mm =
				kदो_स्मृति(माप(*rq_db_key_mm), GFP_KERNEL);
			अगर (!rq_db_key_mm) अणु
				ret = -ENOMEM;
				जाओ err_मुक्त_sq_db_key;
			पूर्ण
		पूर्ण
		स_रखो(&uresp, 0, माप(uresp));
		अगर (t4_sq_onchip(&qhp->wq.sq)) अणु
			ma_sync_key_mm = kदो_स्मृति(माप(*ma_sync_key_mm),
						 GFP_KERNEL);
			अगर (!ma_sync_key_mm) अणु
				ret = -ENOMEM;
				जाओ err_मुक्त_rq_db_key;
			पूर्ण
			uresp.flags = C4IW_QPF_ONCHIP;
		पूर्ण
		अगर (rhp->rdev.lldi.ग_लिखो_w_imm_support)
			uresp.flags |= C4IW_QPF_WRITE_W_IMM;
		uresp.qid_mask = rhp->rdev.qpmask;
		uresp.sqid = qhp->wq.sq.qid;
		uresp.sq_size = qhp->wq.sq.size;
		uresp.sq_memsize = qhp->wq.sq.memsize;
		अगर (!attrs->srq) अणु
			uresp.rqid = qhp->wq.rq.qid;
			uresp.rq_size = qhp->wq.rq.size;
			uresp.rq_memsize = qhp->wq.rq.memsize;
		पूर्ण
		spin_lock(&ucontext->mmap_lock);
		अगर (ma_sync_key_mm) अणु
			uresp.ma_sync_key = ucontext->key;
			ucontext->key += PAGE_SIZE;
		पूर्ण
		uresp.sq_key = ucontext->key;
		ucontext->key += PAGE_SIZE;
		अगर (!attrs->srq) अणु
			uresp.rq_key = ucontext->key;
			ucontext->key += PAGE_SIZE;
		पूर्ण
		uresp.sq_db_gts_key = ucontext->key;
		ucontext->key += PAGE_SIZE;
		अगर (!attrs->srq) अणु
			uresp.rq_db_gts_key = ucontext->key;
			ucontext->key += PAGE_SIZE;
		पूर्ण
		spin_unlock(&ucontext->mmap_lock);
		ret = ib_copy_to_udata(udata, &uresp, माप(uresp));
		अगर (ret)
			जाओ err_मुक्त_ma_sync_key;
		sq_key_mm->key = uresp.sq_key;
		sq_key_mm->addr = qhp->wq.sq.phys_addr;
		sq_key_mm->len = PAGE_ALIGN(qhp->wq.sq.memsize);
		insert_mmap(ucontext, sq_key_mm);
		अगर (!attrs->srq) अणु
			rq_key_mm->key = uresp.rq_key;
			rq_key_mm->addr = virt_to_phys(qhp->wq.rq.queue);
			rq_key_mm->len = PAGE_ALIGN(qhp->wq.rq.memsize);
			insert_mmap(ucontext, rq_key_mm);
		पूर्ण
		sq_db_key_mm->key = uresp.sq_db_gts_key;
		sq_db_key_mm->addr = (u64)(अचिन्हित दीर्घ)qhp->wq.sq.bar2_pa;
		sq_db_key_mm->len = PAGE_SIZE;
		insert_mmap(ucontext, sq_db_key_mm);
		अगर (!attrs->srq) अणु
			rq_db_key_mm->key = uresp.rq_db_gts_key;
			rq_db_key_mm->addr =
				(u64)(अचिन्हित दीर्घ)qhp->wq.rq.bar2_pa;
			rq_db_key_mm->len = PAGE_SIZE;
			insert_mmap(ucontext, rq_db_key_mm);
		पूर्ण
		अगर (ma_sync_key_mm) अणु
			ma_sync_key_mm->key = uresp.ma_sync_key;
			ma_sync_key_mm->addr =
				(pci_resource_start(rhp->rdev.lldi.pdev, 0) +
				PCIE_MA_SYNC_A) & PAGE_MASK;
			ma_sync_key_mm->len = PAGE_SIZE;
			insert_mmap(ucontext, ma_sync_key_mm);
		पूर्ण

		qhp->ucontext = ucontext;
	पूर्ण
	अगर (!attrs->srq) अणु
		qhp->wq.qp_errp =
			&qhp->wq.rq.queue[qhp->wq.rq.size].status.qp_err;
	पूर्ण अन्यथा अणु
		qhp->wq.qp_errp =
			&qhp->wq.sq.queue[qhp->wq.sq.size].status.qp_err;
		qhp->wq.srqidxp =
			&qhp->wq.sq.queue[qhp->wq.sq.size].status.srqidx;
	पूर्ण

	qhp->ibqp.qp_num = qhp->wq.sq.qid;
	अगर (attrs->srq)
		qhp->srq = to_c4iw_srq(attrs->srq);
	INIT_LIST_HEAD(&qhp->db_fc_entry);
	pr_debug("sq id %u size %u memsize %zu num_entries %u rq id %u size %u memsize %zu num_entries %u\n",
		 qhp->wq.sq.qid, qhp->wq.sq.size, qhp->wq.sq.memsize,
		 attrs->cap.max_send_wr, qhp->wq.rq.qid, qhp->wq.rq.size,
		 qhp->wq.rq.memsize, attrs->cap.max_recv_wr);
	वापस &qhp->ibqp;
err_मुक्त_ma_sync_key:
	kमुक्त(ma_sync_key_mm);
err_मुक्त_rq_db_key:
	अगर (!attrs->srq)
		kमुक्त(rq_db_key_mm);
err_मुक्त_sq_db_key:
	kमुक्त(sq_db_key_mm);
err_मुक्त_rq_key:
	अगर (!attrs->srq)
		kमुक्त(rq_key_mm);
err_मुक्त_sq_key:
	kमुक्त(sq_key_mm);
err_हटाओ_handle:
	xa_erase_irq(&rhp->qps, qhp->wq.sq.qid);
err_destroy_qp:
	destroy_qp(&rhp->rdev, &qhp->wq,
		   ucontext ? &ucontext->uctx : &rhp->rdev.uctx, !attrs->srq);
err_मुक्त_wr_रुको:
	c4iw_put_wr_रुको(qhp->wr_रुकोp);
err_मुक्त_qhp:
	kमुक्त(qhp);
	वापस ERR_PTR(ret);
पूर्ण

पूर्णांक c4iw_ib_modअगरy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
		      पूर्णांक attr_mask, काष्ठा ib_udata *udata)
अणु
	काष्ठा c4iw_dev *rhp;
	काष्ठा c4iw_qp *qhp;
	क्रमागत c4iw_qp_attr_mask mask = 0;
	काष्ठा c4iw_qp_attributes attrs = अणुपूर्ण;

	pr_debug("ib_qp %p\n", ibqp);

	अगर (attr_mask & ~IB_QP_ATTR_STANDARD_BITS)
		वापस -EOPNOTSUPP;

	/* iwarp करोes not support the RTR state */
	अगर ((attr_mask & IB_QP_STATE) && (attr->qp_state == IB_QPS_RTR))
		attr_mask &= ~IB_QP_STATE;

	/* Make sure we still have something left to करो */
	अगर (!attr_mask)
		वापस 0;

	qhp = to_c4iw_qp(ibqp);
	rhp = qhp->rhp;

	attrs.next_state = c4iw_convert_state(attr->qp_state);
	attrs.enable_rdma_पढ़ो = (attr->qp_access_flags &
			       IB_ACCESS_REMOTE_READ) ?  1 : 0;
	attrs.enable_rdma_ग_लिखो = (attr->qp_access_flags &
				IB_ACCESS_REMOTE_WRITE) ? 1 : 0;
	attrs.enable_bind = (attr->qp_access_flags & IB_ACCESS_MW_BIND) ? 1 : 0;


	mask |= (attr_mask & IB_QP_STATE) ? C4IW_QP_ATTR_NEXT_STATE : 0;
	mask |= (attr_mask & IB_QP_ACCESS_FLAGS) ?
			(C4IW_QP_ATTR_ENABLE_RDMA_READ |
			 C4IW_QP_ATTR_ENABLE_RDMA_WRITE |
			 C4IW_QP_ATTR_ENABLE_RDMA_BIND) : 0;

	/*
	 * Use SQ_PSN and RQ_PSN to pass in IDX_INC values क्रम
	 * ringing the queue db when we're in DB_FULL mode.
	 * Only allow this on T4 devices.
	 */
	attrs.sq_db_inc = attr->sq_psn;
	attrs.rq_db_inc = attr->rq_psn;
	mask |= (attr_mask & IB_QP_SQ_PSN) ? C4IW_QP_ATTR_SQ_DB : 0;
	mask |= (attr_mask & IB_QP_RQ_PSN) ? C4IW_QP_ATTR_RQ_DB : 0;
	अगर (!is_t4(to_c4iw_qp(ibqp)->rhp->rdev.lldi.adapter_type) &&
	    (mask & (C4IW_QP_ATTR_SQ_DB|C4IW_QP_ATTR_RQ_DB)))
		वापस -EINVAL;

	वापस c4iw_modअगरy_qp(rhp, qhp, mask, &attrs, 0);
पूर्ण

काष्ठा ib_qp *c4iw_get_qp(काष्ठा ib_device *dev, पूर्णांक qpn)
अणु
	pr_debug("ib_dev %p qpn 0x%x\n", dev, qpn);
	वापस (काष्ठा ib_qp *)get_qhp(to_c4iw_dev(dev), qpn);
पूर्ण

व्योम c4iw_dispatch_srq_limit_reached_event(काष्ठा c4iw_srq *srq)
अणु
	काष्ठा ib_event event = अणुपूर्ण;

	event.device = &srq->rhp->ibdev;
	event.element.srq = &srq->ibsrq;
	event.event = IB_EVENT_SRQ_LIMIT_REACHED;
	ib_dispatch_event(&event);
पूर्ण

पूर्णांक c4iw_modअगरy_srq(काष्ठा ib_srq *ib_srq, काष्ठा ib_srq_attr *attr,
		    क्रमागत ib_srq_attr_mask srq_attr_mask,
		    काष्ठा ib_udata *udata)
अणु
	काष्ठा c4iw_srq *srq = to_c4iw_srq(ib_srq);
	पूर्णांक ret = 0;

	/*
	 * XXX 0 mask == a SW पूर्णांकerrupt क्रम srq_limit reached...
	 */
	अगर (udata && !srq_attr_mask) अणु
		c4iw_dispatch_srq_limit_reached_event(srq);
		जाओ out;
	पूर्ण

	/* no support क्रम this yet */
	अगर (srq_attr_mask & IB_SRQ_MAX_WR) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!udata && (srq_attr_mask & IB_SRQ_LIMIT)) अणु
		srq->armed = true;
		srq->srq_limit = attr->srq_limit;
	पूर्ण
out:
	वापस ret;
पूर्ण

पूर्णांक c4iw_ib_query_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_qp_attr *attr,
		     पूर्णांक attr_mask, काष्ठा ib_qp_init_attr *init_attr)
अणु
	काष्ठा c4iw_qp *qhp = to_c4iw_qp(ibqp);

	स_रखो(attr, 0, माप(*attr));
	स_रखो(init_attr, 0, माप(*init_attr));
	attr->qp_state = to_ib_qp_state(qhp->attr.state);
	init_attr->cap.max_send_wr = qhp->attr.sq_num_entries;
	init_attr->cap.max_recv_wr = qhp->attr.rq_num_entries;
	init_attr->cap.max_send_sge = qhp->attr.sq_max_sges;
	init_attr->cap.max_recv_sge = qhp->attr.rq_max_sges;
	init_attr->cap.max_अंतरभूत_data = T4_MAX_SEND_INLINE;
	init_attr->sq_sig_type = qhp->sq_sig_all ? IB_SIGNAL_ALL_WR : 0;
	वापस 0;
पूर्ण

अटल व्योम मुक्त_srq_queue(काष्ठा c4iw_srq *srq, काष्ठा c4iw_dev_ucontext *uctx,
			   काष्ठा c4iw_wr_रुको *wr_रुकोp)
अणु
	काष्ठा c4iw_rdev *rdev = &srq->rhp->rdev;
	काष्ठा sk_buff *skb = srq->destroy_skb;
	काष्ठा t4_srq *wq = &srq->wq;
	काष्ठा fw_ri_res_wr *res_wr;
	काष्ठा fw_ri_res *res;
	पूर्णांक wr_len;

	wr_len = माप(*res_wr) + माप(*res);
	set_wr_txq(skb, CPL_PRIORITY_CONTROL, 0);

	res_wr = (काष्ठा fw_ri_res_wr *)__skb_put(skb, wr_len);
	स_रखो(res_wr, 0, wr_len);
	res_wr->op_nres = cpu_to_be32(FW_WR_OP_V(FW_RI_RES_WR) |
			FW_RI_RES_WR_NRES_V(1) |
			FW_WR_COMPL_F);
	res_wr->len16_pkd = cpu_to_be32(DIV_ROUND_UP(wr_len, 16));
	res_wr->cookie = (uपूर्णांकptr_t)wr_रुकोp;
	res = res_wr->res;
	res->u.srq.restype = FW_RI_RES_TYPE_SRQ;
	res->u.srq.op = FW_RI_RES_OP_RESET;
	res->u.srq.srqid = cpu_to_be32(srq->idx);
	res->u.srq.eqid = cpu_to_be32(wq->qid);

	c4iw_init_wr_रुको(wr_रुकोp);
	c4iw_ref_send_रुको(rdev, skb, wr_रुकोp, 0, 0, __func__);

	dma_मुक्त_coherent(&rdev->lldi.pdev->dev,
			  wq->memsize, wq->queue,
			dma_unmap_addr(wq, mapping));
	c4iw_rqtpool_मुक्त(rdev, wq->rqt_hwaddr, wq->rqt_size);
	kमुक्त(wq->sw_rq);
	c4iw_put_qpid(rdev, wq->qid, uctx);
पूर्ण

अटल पूर्णांक alloc_srq_queue(काष्ठा c4iw_srq *srq, काष्ठा c4iw_dev_ucontext *uctx,
			   काष्ठा c4iw_wr_रुको *wr_रुकोp)
अणु
	काष्ठा c4iw_rdev *rdev = &srq->rhp->rdev;
	पूर्णांक user = (uctx != &rdev->uctx);
	काष्ठा t4_srq *wq = &srq->wq;
	काष्ठा fw_ri_res_wr *res_wr;
	काष्ठा fw_ri_res *res;
	काष्ठा sk_buff *skb;
	पूर्णांक wr_len;
	पूर्णांक eqsize;
	पूर्णांक ret = -ENOMEM;

	wq->qid = c4iw_get_qpid(rdev, uctx);
	अगर (!wq->qid)
		जाओ err;

	अगर (!user) अणु
		wq->sw_rq = kसुस्मृति(wq->size, माप(*wq->sw_rq),
				    GFP_KERNEL);
		अगर (!wq->sw_rq)
			जाओ err_put_qpid;
		wq->pending_wrs = kसुस्मृति(srq->wq.size,
					  माप(*srq->wq.pending_wrs),
					  GFP_KERNEL);
		अगर (!wq->pending_wrs)
			जाओ err_मुक्त_sw_rq;
	पूर्ण

	wq->rqt_size = wq->size;
	wq->rqt_hwaddr = c4iw_rqtpool_alloc(rdev, wq->rqt_size);
	अगर (!wq->rqt_hwaddr)
		जाओ err_मुक्त_pending_wrs;
	wq->rqt_असल_idx = (wq->rqt_hwaddr - rdev->lldi.vr->rq.start) >>
		T4_RQT_ENTRY_SHIFT;

	wq->queue = dma_alloc_coherent(&rdev->lldi.pdev->dev, wq->memsize,
				       &wq->dma_addr, GFP_KERNEL);
	अगर (!wq->queue)
		जाओ err_मुक्त_rqtpool;

	dma_unmap_addr_set(wq, mapping, wq->dma_addr);

	wq->bar2_va = c4iw_bar2_addrs(rdev, wq->qid, CXGB4_BAR2_QTYPE_EGRESS,
				      &wq->bar2_qid,
			user ? &wq->bar2_pa : शून्य);

	/*
	 * User mode must have bar2 access.
	 */

	अगर (user && !wq->bar2_va) अणु
		pr_warn(MOD "%s: srqid %u not in BAR2 range.\n",
			pci_name(rdev->lldi.pdev), wq->qid);
		ret = -EINVAL;
		जाओ err_मुक्त_queue;
	पूर्ण

	/* build fw_ri_res_wr */
	wr_len = माप(*res_wr) + माप(*res);

	skb = alloc_skb(wr_len, GFP_KERNEL);
	अगर (!skb)
		जाओ err_मुक्त_queue;
	set_wr_txq(skb, CPL_PRIORITY_CONTROL, 0);

	res_wr = (काष्ठा fw_ri_res_wr *)__skb_put(skb, wr_len);
	स_रखो(res_wr, 0, wr_len);
	res_wr->op_nres = cpu_to_be32(FW_WR_OP_V(FW_RI_RES_WR) |
			FW_RI_RES_WR_NRES_V(1) |
			FW_WR_COMPL_F);
	res_wr->len16_pkd = cpu_to_be32(DIV_ROUND_UP(wr_len, 16));
	res_wr->cookie = (uपूर्णांकptr_t)wr_रुकोp;
	res = res_wr->res;
	res->u.srq.restype = FW_RI_RES_TYPE_SRQ;
	res->u.srq.op = FW_RI_RES_OP_WRITE;

	/*
	 * eqsize is the number of 64B entries plus the status page size.
	 */
	eqsize = wq->size * T4_RQ_NUM_SLOTS +
		rdev->hw_queue.t4_eq_status_entries;
	res->u.srq.eqid = cpu_to_be32(wq->qid);
	res->u.srq.fetchszm_to_iqid =
						/* no host cidx updates */
		cpu_to_be32(FW_RI_RES_WR_HOSTFCMODE_V(0) |
		FW_RI_RES_WR_CPRIO_V(0) |       /* करोn't keep in chip cache */
		FW_RI_RES_WR_PCIECHN_V(0) |     /* set by uP at ri_init समय */
		FW_RI_RES_WR_FETCHRO_V(0));     /* relaxed_ordering */
	res->u.srq.dcaen_to_eqsize =
		cpu_to_be32(FW_RI_RES_WR_DCAEN_V(0) |
		FW_RI_RES_WR_DCACPU_V(0) |
		FW_RI_RES_WR_FBMIN_V(2) |
		FW_RI_RES_WR_FBMAX_V(3) |
		FW_RI_RES_WR_CIDXFTHRESHO_V(0) |
		FW_RI_RES_WR_CIDXFTHRESH_V(0) |
		FW_RI_RES_WR_EQSIZE_V(eqsize));
	res->u.srq.eqaddr = cpu_to_be64(wq->dma_addr);
	res->u.srq.srqid = cpu_to_be32(srq->idx);
	res->u.srq.pdid = cpu_to_be32(srq->pdid);
	res->u.srq.hwsrqsize = cpu_to_be32(wq->rqt_size);
	res->u.srq.hwsrqaddr = cpu_to_be32(wq->rqt_hwaddr -
			rdev->lldi.vr->rq.start);

	c4iw_init_wr_रुको(wr_रुकोp);

	ret = c4iw_ref_send_रुको(rdev, skb, wr_रुकोp, 0, wq->qid, __func__);
	अगर (ret)
		जाओ err_मुक्त_queue;

	pr_debug("%s srq %u eqid %u pdid %u queue va %p pa 0x%llx\n"
			" bar2_addr %p rqt addr 0x%x size %d\n",
			__func__, srq->idx, wq->qid, srq->pdid, wq->queue,
			(u64)virt_to_phys(wq->queue), wq->bar2_va,
			wq->rqt_hwaddr, wq->rqt_size);

	वापस 0;
err_मुक्त_queue:
	dma_मुक्त_coherent(&rdev->lldi.pdev->dev,
			  wq->memsize, wq->queue,
			dma_unmap_addr(wq, mapping));
err_मुक्त_rqtpool:
	c4iw_rqtpool_मुक्त(rdev, wq->rqt_hwaddr, wq->rqt_size);
err_मुक्त_pending_wrs:
	अगर (!user)
		kमुक्त(wq->pending_wrs);
err_मुक्त_sw_rq:
	अगर (!user)
		kमुक्त(wq->sw_rq);
err_put_qpid:
	c4iw_put_qpid(rdev, wq->qid, uctx);
err:
	वापस ret;
पूर्ण

व्योम c4iw_copy_wr_to_srq(काष्ठा t4_srq *srq, जोड़ t4_recv_wr *wqe, u8 len16)
अणु
	u64 *src, *dst;

	src = (u64 *)wqe;
	dst = (u64 *)((u8 *)srq->queue + srq->wq_pidx * T4_EQ_ENTRY_SIZE);
	जबतक (len16) अणु
		*dst++ = *src++;
		अगर (dst >= (u64 *)&srq->queue[srq->size])
			dst = (u64 *)srq->queue;
		*dst++ = *src++;
		अगर (dst >= (u64 *)&srq->queue[srq->size])
			dst = (u64 *)srq->queue;
		len16--;
	पूर्ण
पूर्ण

पूर्णांक c4iw_create_srq(काष्ठा ib_srq *ib_srq, काष्ठा ib_srq_init_attr *attrs,
			       काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_pd *pd = ib_srq->pd;
	काष्ठा c4iw_dev *rhp;
	काष्ठा c4iw_srq *srq = to_c4iw_srq(ib_srq);
	काष्ठा c4iw_pd *php;
	काष्ठा c4iw_create_srq_resp uresp;
	काष्ठा c4iw_ucontext *ucontext;
	काष्ठा c4iw_mm_entry *srq_key_mm, *srq_db_key_mm;
	पूर्णांक rqsize;
	पूर्णांक ret;
	पूर्णांक wr_len;

	अगर (attrs->srq_type != IB_SRQT_BASIC)
		वापस -EOPNOTSUPP;

	pr_debug("%s ib_pd %p\n", __func__, pd);

	php = to_c4iw_pd(pd);
	rhp = php->rhp;

	अगर (!rhp->rdev.lldi.vr->srq.size)
		वापस -EINVAL;
	अगर (attrs->attr.max_wr > rhp->rdev.hw_queue.t4_max_rq_size)
		वापस -E2BIG;
	अगर (attrs->attr.max_sge > T4_MAX_RECV_SGE)
		वापस -E2BIG;

	/*
	 * SRQ RQT and RQ must be a घातer of 2 and at least 16 deep.
	 */
	rqsize = attrs->attr.max_wr + 1;
	rqsize = roundup_घात_of_two(max_t(u16, rqsize, 16));

	ucontext = rdma_udata_to_drv_context(udata, काष्ठा c4iw_ucontext,
					     ibucontext);

	srq->wr_रुकोp = c4iw_alloc_wr_रुको(GFP_KERNEL);
	अगर (!srq->wr_रुकोp)
		वापस -ENOMEM;

	srq->idx = c4iw_alloc_srq_idx(&rhp->rdev);
	अगर (srq->idx < 0) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_wr_रुको;
	पूर्ण

	wr_len = माप(काष्ठा fw_ri_res_wr) + माप(काष्ठा fw_ri_res);
	srq->destroy_skb = alloc_skb(wr_len, GFP_KERNEL);
	अगर (!srq->destroy_skb) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_srq_idx;
	पूर्ण

	srq->rhp = rhp;
	srq->pdid = php->pdid;

	srq->wq.size = rqsize;
	srq->wq.memsize =
		(rqsize + rhp->rdev.hw_queue.t4_eq_status_entries) *
		माप(*srq->wq.queue);
	अगर (ucontext)
		srq->wq.memsize = roundup(srq->wq.memsize, PAGE_SIZE);

	ret = alloc_srq_queue(srq, ucontext ? &ucontext->uctx :
			&rhp->rdev.uctx, srq->wr_रुकोp);
	अगर (ret)
		जाओ err_मुक्त_skb;
	attrs->attr.max_wr = rqsize - 1;

	अगर (CHELSIO_CHIP_VERSION(rhp->rdev.lldi.adapter_type) > CHELSIO_T6)
		srq->flags = T4_SRQ_LIMIT_SUPPORT;

	अगर (udata) अणु
		srq_key_mm = kदो_स्मृति(माप(*srq_key_mm), GFP_KERNEL);
		अगर (!srq_key_mm) अणु
			ret = -ENOMEM;
			जाओ err_मुक्त_queue;
		पूर्ण
		srq_db_key_mm = kदो_स्मृति(माप(*srq_db_key_mm), GFP_KERNEL);
		अगर (!srq_db_key_mm) अणु
			ret = -ENOMEM;
			जाओ err_मुक्त_srq_key_mm;
		पूर्ण
		स_रखो(&uresp, 0, माप(uresp));
		uresp.flags = srq->flags;
		uresp.qid_mask = rhp->rdev.qpmask;
		uresp.srqid = srq->wq.qid;
		uresp.srq_size = srq->wq.size;
		uresp.srq_memsize = srq->wq.memsize;
		uresp.rqt_असल_idx = srq->wq.rqt_असल_idx;
		spin_lock(&ucontext->mmap_lock);
		uresp.srq_key = ucontext->key;
		ucontext->key += PAGE_SIZE;
		uresp.srq_db_gts_key = ucontext->key;
		ucontext->key += PAGE_SIZE;
		spin_unlock(&ucontext->mmap_lock);
		ret = ib_copy_to_udata(udata, &uresp, माप(uresp));
		अगर (ret)
			जाओ err_मुक्त_srq_db_key_mm;
		srq_key_mm->key = uresp.srq_key;
		srq_key_mm->addr = virt_to_phys(srq->wq.queue);
		srq_key_mm->len = PAGE_ALIGN(srq->wq.memsize);
		insert_mmap(ucontext, srq_key_mm);
		srq_db_key_mm->key = uresp.srq_db_gts_key;
		srq_db_key_mm->addr = (u64)(अचिन्हित दीर्घ)srq->wq.bar2_pa;
		srq_db_key_mm->len = PAGE_SIZE;
		insert_mmap(ucontext, srq_db_key_mm);
	पूर्ण

	pr_debug("%s srq qid %u idx %u size %u memsize %lu num_entries %u\n",
		 __func__, srq->wq.qid, srq->idx, srq->wq.size,
			(अचिन्हित दीर्घ)srq->wq.memsize, attrs->attr.max_wr);

	spin_lock_init(&srq->lock);
	वापस 0;

err_मुक्त_srq_db_key_mm:
	kमुक्त(srq_db_key_mm);
err_मुक्त_srq_key_mm:
	kमुक्त(srq_key_mm);
err_मुक्त_queue:
	मुक्त_srq_queue(srq, ucontext ? &ucontext->uctx : &rhp->rdev.uctx,
		       srq->wr_रुकोp);
err_मुक्त_skb:
	kमुक्त_skb(srq->destroy_skb);
err_मुक्त_srq_idx:
	c4iw_मुक्त_srq_idx(&rhp->rdev, srq->idx);
err_मुक्त_wr_रुको:
	c4iw_put_wr_रुको(srq->wr_रुकोp);
	वापस ret;
पूर्ण

पूर्णांक c4iw_destroy_srq(काष्ठा ib_srq *ibsrq, काष्ठा ib_udata *udata)
अणु
	काष्ठा c4iw_dev *rhp;
	काष्ठा c4iw_srq *srq;
	काष्ठा c4iw_ucontext *ucontext;

	srq = to_c4iw_srq(ibsrq);
	rhp = srq->rhp;

	pr_debug("%s id %d\n", __func__, srq->wq.qid);
	ucontext = rdma_udata_to_drv_context(udata, काष्ठा c4iw_ucontext,
					     ibucontext);
	मुक्त_srq_queue(srq, ucontext ? &ucontext->uctx : &rhp->rdev.uctx,
		       srq->wr_रुकोp);
	c4iw_मुक्त_srq_idx(&rhp->rdev, srq->idx);
	c4iw_put_wr_रुको(srq->wr_रुकोp);
	वापस 0;
पूर्ण
