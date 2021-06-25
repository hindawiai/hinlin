<शैली गुरु>
/*
 * Broadcom NetXtreme-E RoCE driver.
 *
 * Copyright (c) 2016 - 2017, Broadcom. All rights reserved.  The term
 * Broadcom refers to Broadcom Limited and/or its subsidiaries.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS
 * BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Description: Fast Path Operators
 */

#घोषणा dev_fmt(fmt) "QPLIB: " fmt

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/अगर_ether.h>

#समावेश "roce_hsi.h"

#समावेश "qplib_res.h"
#समावेश "qplib_rcfw.h"
#समावेश "qplib_sp.h"
#समावेश "qplib_fp.h"

अटल व्योम __clean_cq(काष्ठा bnxt_qplib_cq *cq, u64 qp);

अटल व्योम bnxt_qplib_cancel_phantom_processing(काष्ठा bnxt_qplib_qp *qp)
अणु
	qp->sq.condition = false;
	qp->sq.send_phantom = false;
	qp->sq.single = false;
पूर्ण

/* Flush list */
अटल व्योम __bnxt_qplib_add_flush_qp(काष्ठा bnxt_qplib_qp *qp)
अणु
	काष्ठा bnxt_qplib_cq *scq, *rcq;

	scq = qp->scq;
	rcq = qp->rcq;

	अगर (!qp->sq.flushed) अणु
		dev_dbg(&scq->hwq.pdev->dev,
			"FP: Adding to SQ Flush list = %p\n", qp);
		bnxt_qplib_cancel_phantom_processing(qp);
		list_add_tail(&qp->sq_flush, &scq->sqf_head);
		qp->sq.flushed = true;
	पूर्ण
	अगर (!qp->srq) अणु
		अगर (!qp->rq.flushed) अणु
			dev_dbg(&rcq->hwq.pdev->dev,
				"FP: Adding to RQ Flush list = %p\n", qp);
			list_add_tail(&qp->rq_flush, &rcq->rqf_head);
			qp->rq.flushed = true;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bnxt_qplib_acquire_cq_flush_locks(काष्ठा bnxt_qplib_qp *qp,
				       अचिन्हित दीर्घ *flags)
	__acquires(&qp->scq->flush_lock) __acquires(&qp->rcq->flush_lock)
अणु
	spin_lock_irqsave(&qp->scq->flush_lock, *flags);
	अगर (qp->scq == qp->rcq)
		__acquire(&qp->rcq->flush_lock);
	अन्यथा
		spin_lock(&qp->rcq->flush_lock);
पूर्ण

अटल व्योम bnxt_qplib_release_cq_flush_locks(काष्ठा bnxt_qplib_qp *qp,
				       अचिन्हित दीर्घ *flags)
	__releases(&qp->scq->flush_lock) __releases(&qp->rcq->flush_lock)
अणु
	अगर (qp->scq == qp->rcq)
		__release(&qp->rcq->flush_lock);
	अन्यथा
		spin_unlock(&qp->rcq->flush_lock);
	spin_unlock_irqrestore(&qp->scq->flush_lock, *flags);
पूर्ण

व्योम bnxt_qplib_add_flush_qp(काष्ठा bnxt_qplib_qp *qp)
अणु
	अचिन्हित दीर्घ flags;

	bnxt_qplib_acquire_cq_flush_locks(qp, &flags);
	__bnxt_qplib_add_flush_qp(qp);
	bnxt_qplib_release_cq_flush_locks(qp, &flags);
पूर्ण

अटल व्योम __bnxt_qplib_del_flush_qp(काष्ठा bnxt_qplib_qp *qp)
अणु
	अगर (qp->sq.flushed) अणु
		qp->sq.flushed = false;
		list_del(&qp->sq_flush);
	पूर्ण
	अगर (!qp->srq) अणु
		अगर (qp->rq.flushed) अणु
			qp->rq.flushed = false;
			list_del(&qp->rq_flush);
		पूर्ण
	पूर्ण
पूर्ण

व्योम bnxt_qplib_clean_qp(काष्ठा bnxt_qplib_qp *qp)
अणु
	अचिन्हित दीर्घ flags;

	bnxt_qplib_acquire_cq_flush_locks(qp, &flags);
	__clean_cq(qp->scq, (u64)(अचिन्हित दीर्घ)qp);
	qp->sq.hwq.prod = 0;
	qp->sq.hwq.cons = 0;
	__clean_cq(qp->rcq, (u64)(अचिन्हित दीर्घ)qp);
	qp->rq.hwq.prod = 0;
	qp->rq.hwq.cons = 0;

	__bnxt_qplib_del_flush_qp(qp);
	bnxt_qplib_release_cq_flush_locks(qp, &flags);
पूर्ण

अटल व्योम bnxt_qpn_cqn_sched_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा bnxt_qplib_nq_work *nq_work =
			container_of(work, काष्ठा bnxt_qplib_nq_work, work);

	काष्ठा bnxt_qplib_cq *cq = nq_work->cq;
	काष्ठा bnxt_qplib_nq *nq = nq_work->nq;

	अगर (cq && nq) अणु
		spin_lock_bh(&cq->compl_lock);
		अगर (atomic_पढ़ो(&cq->arm_state) && nq->cqn_handler) अणु
			dev_dbg(&nq->pdev->dev,
				"%s:Trigger cq  = %p event nq = %p\n",
				__func__, cq, nq);
			nq->cqn_handler(nq, cq);
		पूर्ण
		spin_unlock_bh(&cq->compl_lock);
	पूर्ण
	kमुक्त(nq_work);
पूर्ण

अटल व्योम bnxt_qplib_मुक्त_qp_hdr_buf(काष्ठा bnxt_qplib_res *res,
				       काष्ठा bnxt_qplib_qp *qp)
अणु
	काष्ठा bnxt_qplib_q *rq = &qp->rq;
	काष्ठा bnxt_qplib_q *sq = &qp->sq;

	अगर (qp->rq_hdr_buf)
		dma_मुक्त_coherent(&res->pdev->dev,
				  rq->max_wqe * qp->rq_hdr_buf_size,
				  qp->rq_hdr_buf, qp->rq_hdr_buf_map);
	अगर (qp->sq_hdr_buf)
		dma_मुक्त_coherent(&res->pdev->dev,
				  sq->max_wqe * qp->sq_hdr_buf_size,
				  qp->sq_hdr_buf, qp->sq_hdr_buf_map);
	qp->rq_hdr_buf = शून्य;
	qp->sq_hdr_buf = शून्य;
	qp->rq_hdr_buf_map = 0;
	qp->sq_hdr_buf_map = 0;
	qp->sq_hdr_buf_size = 0;
	qp->rq_hdr_buf_size = 0;
पूर्ण

अटल पूर्णांक bnxt_qplib_alloc_qp_hdr_buf(काष्ठा bnxt_qplib_res *res,
				       काष्ठा bnxt_qplib_qp *qp)
अणु
	काष्ठा bnxt_qplib_q *rq = &qp->rq;
	काष्ठा bnxt_qplib_q *sq = &qp->sq;
	पूर्णांक rc = 0;

	अगर (qp->sq_hdr_buf_size && sq->max_wqe) अणु
		qp->sq_hdr_buf = dma_alloc_coherent(&res->pdev->dev,
					sq->max_wqe * qp->sq_hdr_buf_size,
					&qp->sq_hdr_buf_map, GFP_KERNEL);
		अगर (!qp->sq_hdr_buf) अणु
			rc = -ENOMEM;
			dev_err(&res->pdev->dev,
				"Failed to create sq_hdr_buf\n");
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (qp->rq_hdr_buf_size && rq->max_wqe) अणु
		qp->rq_hdr_buf = dma_alloc_coherent(&res->pdev->dev,
						    rq->max_wqe *
						    qp->rq_hdr_buf_size,
						    &qp->rq_hdr_buf_map,
						    GFP_KERNEL);
		अगर (!qp->rq_hdr_buf) अणु
			rc = -ENOMEM;
			dev_err(&res->pdev->dev,
				"Failed to create rq_hdr_buf\n");
			जाओ fail;
		पूर्ण
	पूर्ण
	वापस 0;

fail:
	bnxt_qplib_मुक्त_qp_hdr_buf(res, qp);
	वापस rc;
पूर्ण

अटल व्योम clean_nq(काष्ठा bnxt_qplib_nq *nq, काष्ठा bnxt_qplib_cq *cq)
अणु
	काष्ठा bnxt_qplib_hwq *hwq = &nq->hwq;
	काष्ठा nq_base *nqe, **nq_ptr;
	पूर्णांक budget = nq->budget;
	u32 sw_cons, raw_cons;
	uपूर्णांकptr_t q_handle;
	u16 type;

	spin_lock_bh(&hwq->lock);
	/* Service the NQ until empty */
	raw_cons = hwq->cons;
	जबतक (budget--) अणु
		sw_cons = HWQ_CMP(raw_cons, hwq);
		nq_ptr = (काष्ठा nq_base **)hwq->pbl_ptr;
		nqe = &nq_ptr[NQE_PG(sw_cons)][NQE_IDX(sw_cons)];
		अगर (!NQE_CMP_VALID(nqe, raw_cons, hwq->max_elements))
			अवरोध;

		/*
		 * The valid test of the entry must be करोne first beक्रमe
		 * पढ़ोing any further.
		 */
		dma_rmb();

		type = le16_to_cpu(nqe->info10_type) & NQ_BASE_TYPE_MASK;
		चयन (type) अणु
		हाल NQ_BASE_TYPE_CQ_NOTIFICATION:
		अणु
			काष्ठा nq_cn *nqcne = (काष्ठा nq_cn *)nqe;

			q_handle = le32_to_cpu(nqcne->cq_handle_low);
			q_handle |= (u64)le32_to_cpu(nqcne->cq_handle_high)
						     << 32;
			अगर ((अचिन्हित दीर्घ)cq == q_handle) अणु
				nqcne->cq_handle_low = 0;
				nqcne->cq_handle_high = 0;
				cq->cnq_events++;
			पूर्ण
			अवरोध;
		पूर्ण
		शेष:
			अवरोध;
		पूर्ण
		raw_cons++;
	पूर्ण
	spin_unlock_bh(&hwq->lock);
पूर्ण

/* Wait क्रम receiving all NQEs क्रम this CQ and clean the NQEs associated with
 * this CQ.
 */
अटल व्योम __रुको_क्रम_all_nqes(काष्ठा bnxt_qplib_cq *cq, u16 cnq_events)
अणु
	u32 retry_cnt = 100;

	जबतक (retry_cnt--) अणु
		अगर (cnq_events == cq->cnq_events)
			वापस;
		usleep_range(50, 100);
		clean_nq(cq->nq, cq);
	पूर्ण
पूर्ण

अटल व्योम bnxt_qplib_service_nq(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा bnxt_qplib_nq *nq = from_tasklet(nq, t, nq_tasklet);
	काष्ठा bnxt_qplib_hwq *hwq = &nq->hwq;
	पूर्णांक num_srqne_processed = 0;
	पूर्णांक num_cqne_processed = 0;
	काष्ठा bnxt_qplib_cq *cq;
	पूर्णांक budget = nq->budget;
	u32 sw_cons, raw_cons;
	काष्ठा nq_base *nqe;
	uपूर्णांकptr_t q_handle;
	u16 type;

	spin_lock_bh(&hwq->lock);
	/* Service the NQ until empty */
	raw_cons = hwq->cons;
	जबतक (budget--) अणु
		sw_cons = HWQ_CMP(raw_cons, hwq);
		nqe = bnxt_qplib_get_qe(hwq, sw_cons, शून्य);
		अगर (!NQE_CMP_VALID(nqe, raw_cons, hwq->max_elements))
			अवरोध;

		/*
		 * The valid test of the entry must be करोne first beक्रमe
		 * पढ़ोing any further.
		 */
		dma_rmb();

		type = le16_to_cpu(nqe->info10_type) & NQ_BASE_TYPE_MASK;
		चयन (type) अणु
		हाल NQ_BASE_TYPE_CQ_NOTIFICATION:
		अणु
			काष्ठा nq_cn *nqcne = (काष्ठा nq_cn *)nqe;

			q_handle = le32_to_cpu(nqcne->cq_handle_low);
			q_handle |= (u64)le32_to_cpu(nqcne->cq_handle_high)
						     << 32;
			cq = (काष्ठा bnxt_qplib_cq *)(अचिन्हित दीर्घ)q_handle;
			अगर (!cq)
				अवरोध;
			bnxt_qplib_armen_db(&cq->dbinfo,
					    DBC_DBC_TYPE_CQ_ARMENA);
			spin_lock_bh(&cq->compl_lock);
			atomic_set(&cq->arm_state, 0);
			अगर (!nq->cqn_handler(nq, (cq)))
				num_cqne_processed++;
			अन्यथा
				dev_warn(&nq->pdev->dev,
					 "cqn - type 0x%x not handled\n", type);
			cq->cnq_events++;
			spin_unlock_bh(&cq->compl_lock);
			अवरोध;
		पूर्ण
		हाल NQ_BASE_TYPE_SRQ_EVENT:
		अणु
			काष्ठा bnxt_qplib_srq *srq;
			काष्ठा nq_srq_event *nqsrqe =
						(काष्ठा nq_srq_event *)nqe;

			q_handle = le32_to_cpu(nqsrqe->srq_handle_low);
			q_handle |= (u64)le32_to_cpu(nqsrqe->srq_handle_high)
				     << 32;
			srq = (काष्ठा bnxt_qplib_srq *)q_handle;
			bnxt_qplib_armen_db(&srq->dbinfo,
					    DBC_DBC_TYPE_SRQ_ARMENA);
			अगर (!nq->srqn_handler(nq,
					      (काष्ठा bnxt_qplib_srq *)q_handle,
					      nqsrqe->event))
				num_srqne_processed++;
			अन्यथा
				dev_warn(&nq->pdev->dev,
					 "SRQ event 0x%x not handled\n",
					 nqsrqe->event);
			अवरोध;
		पूर्ण
		हाल NQ_BASE_TYPE_DBQ_EVENT:
			अवरोध;
		शेष:
			dev_warn(&nq->pdev->dev,
				 "nqe with type = 0x%x not handled\n", type);
			अवरोध;
		पूर्ण
		raw_cons++;
	पूर्ण
	अगर (hwq->cons != raw_cons) अणु
		hwq->cons = raw_cons;
		bnxt_qplib_ring_nq_db(&nq->nq_db.dbinfo, nq->res->cctx, true);
	पूर्ण
	spin_unlock_bh(&hwq->lock);
पूर्ण

अटल irqवापस_t bnxt_qplib_nq_irq(पूर्णांक irq, व्योम *dev_instance)
अणु
	काष्ठा bnxt_qplib_nq *nq = dev_instance;
	काष्ठा bnxt_qplib_hwq *hwq = &nq->hwq;
	u32 sw_cons;

	/* Prefetch the NQ element */
	sw_cons = HWQ_CMP(hwq->cons, hwq);
	prefetch(bnxt_qplib_get_qe(hwq, sw_cons, शून्य));

	/* Fan out to CPU affinitized kthपढ़ोs? */
	tasklet_schedule(&nq->nq_tasklet);

	वापस IRQ_HANDLED;
पूर्ण

व्योम bnxt_qplib_nq_stop_irq(काष्ठा bnxt_qplib_nq *nq, bool समाप्त)
अणु
	tasklet_disable(&nq->nq_tasklet);
	/* Mask h/w पूर्णांकerrupt */
	bnxt_qplib_ring_nq_db(&nq->nq_db.dbinfo, nq->res->cctx, false);
	/* Sync with last running IRQ handler */
	synchronize_irq(nq->msix_vec);
	अगर (समाप्त)
		tasklet_समाप्त(&nq->nq_tasklet);
	अगर (nq->requested) अणु
		irq_set_affinity_hपूर्णांक(nq->msix_vec, शून्य);
		मुक्त_irq(nq->msix_vec, nq);
		nq->requested = false;
	पूर्ण
पूर्ण

व्योम bnxt_qplib_disable_nq(काष्ठा bnxt_qplib_nq *nq)
अणु
	अगर (nq->cqn_wq) अणु
		destroy_workqueue(nq->cqn_wq);
		nq->cqn_wq = शून्य;
	पूर्ण

	/* Make sure the HW is stopped! */
	bnxt_qplib_nq_stop_irq(nq, true);

	अगर (nq->nq_db.reg.bar_reg) अणु
		iounmap(nq->nq_db.reg.bar_reg);
		nq->nq_db.reg.bar_reg = शून्य;
	पूर्ण

	nq->cqn_handler = शून्य;
	nq->srqn_handler = शून्य;
	nq->msix_vec = 0;
पूर्ण

पूर्णांक bnxt_qplib_nq_start_irq(काष्ठा bnxt_qplib_nq *nq, पूर्णांक nq_indx,
			    पूर्णांक msix_vector, bool need_init)
अणु
	पूर्णांक rc;

	अगर (nq->requested)
		वापस -EFAULT;

	nq->msix_vec = msix_vector;
	अगर (need_init)
		tasklet_setup(&nq->nq_tasklet, bnxt_qplib_service_nq);
	अन्यथा
		tasklet_enable(&nq->nq_tasklet);

	snम_लिखो(nq->name, माप(nq->name), "bnxt_qplib_nq-%d", nq_indx);
	rc = request_irq(nq->msix_vec, bnxt_qplib_nq_irq, 0, nq->name, nq);
	अगर (rc)
		वापस rc;

	cpumask_clear(&nq->mask);
	cpumask_set_cpu(nq_indx, &nq->mask);
	rc = irq_set_affinity_hपूर्णांक(nq->msix_vec, &nq->mask);
	अगर (rc) अणु
		dev_warn(&nq->pdev->dev,
			 "set affinity failed; vector: %d nq_idx: %d\n",
			 nq->msix_vec, nq_indx);
	पूर्ण
	nq->requested = true;
	bnxt_qplib_ring_nq_db(&nq->nq_db.dbinfo, nq->res->cctx, true);

	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_qplib_map_nq_db(काष्ठा bnxt_qplib_nq *nq,  u32 reg_offt)
अणु
	resource_माप_प्रकार reg_base;
	काष्ठा bnxt_qplib_nq_db *nq_db;
	काष्ठा pci_dev *pdev;
	पूर्णांक rc = 0;

	pdev = nq->pdev;
	nq_db = &nq->nq_db;

	nq_db->reg.bar_id = NQ_CONS_PCI_BAR_REGION;
	nq_db->reg.bar_base = pci_resource_start(pdev, nq_db->reg.bar_id);
	अगर (!nq_db->reg.bar_base) अणु
		dev_err(&pdev->dev, "QPLIB: NQ BAR region %d resc start is 0!",
			nq_db->reg.bar_id);
		rc = -ENOMEM;
		जाओ fail;
	पूर्ण

	reg_base = nq_db->reg.bar_base + reg_offt;
	/* Unconditionally map 8 bytes to support 57500 series */
	nq_db->reg.len = 8;
	nq_db->reg.bar_reg = ioremap(reg_base, nq_db->reg.len);
	अगर (!nq_db->reg.bar_reg) अणु
		dev_err(&pdev->dev, "QPLIB: NQ BAR region %d mapping failed",
			nq_db->reg.bar_id);
		rc = -ENOMEM;
		जाओ fail;
	पूर्ण

	nq_db->dbinfo.db = nq_db->reg.bar_reg;
	nq_db->dbinfo.hwq = &nq->hwq;
	nq_db->dbinfo.xid = nq->ring_id;
fail:
	वापस rc;
पूर्ण

पूर्णांक bnxt_qplib_enable_nq(काष्ठा pci_dev *pdev, काष्ठा bnxt_qplib_nq *nq,
			 पूर्णांक nq_idx, पूर्णांक msix_vector, पूर्णांक bar_reg_offset,
			 cqn_handler_t cqn_handler,
			 srqn_handler_t srqn_handler)
अणु
	पूर्णांक rc = -1;

	nq->pdev = pdev;
	nq->cqn_handler = cqn_handler;
	nq->srqn_handler = srqn_handler;

	/* Have a task to schedule CQ notअगरiers in post send हाल */
	nq->cqn_wq  = create_singlethपढ़ो_workqueue("bnxt_qplib_nq");
	अगर (!nq->cqn_wq)
		वापस -ENOMEM;

	rc = bnxt_qplib_map_nq_db(nq, bar_reg_offset);
	अगर (rc)
		जाओ fail;

	rc = bnxt_qplib_nq_start_irq(nq, nq_idx, msix_vector, true);
	अगर (rc) अणु
		dev_err(&nq->pdev->dev,
			"Failed to request irq for nq-idx %d\n", nq_idx);
		जाओ fail;
	पूर्ण

	वापस 0;
fail:
	bnxt_qplib_disable_nq(nq);
	वापस rc;
पूर्ण

व्योम bnxt_qplib_मुक्त_nq(काष्ठा bnxt_qplib_nq *nq)
अणु
	अगर (nq->hwq.max_elements) अणु
		bnxt_qplib_मुक्त_hwq(nq->res, &nq->hwq);
		nq->hwq.max_elements = 0;
	पूर्ण
पूर्ण

पूर्णांक bnxt_qplib_alloc_nq(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_nq *nq)
अणु
	काष्ठा bnxt_qplib_hwq_attr hwq_attr = अणुपूर्ण;
	काष्ठा bnxt_qplib_sg_info sginfo = अणुपूर्ण;

	nq->pdev = res->pdev;
	nq->res = res;
	अगर (!nq->hwq.max_elements ||
	    nq->hwq.max_elements > BNXT_QPLIB_NQE_MAX_CNT)
		nq->hwq.max_elements = BNXT_QPLIB_NQE_MAX_CNT;

	sginfo.pgsize = PAGE_SIZE;
	sginfo.pgshft = PAGE_SHIFT;
	hwq_attr.res = res;
	hwq_attr.sginfo = &sginfo;
	hwq_attr.depth = nq->hwq.max_elements;
	hwq_attr.stride = माप(काष्ठा nq_base);
	hwq_attr.type = bnxt_qplib_get_hwq_type(nq->res);
	अगर (bnxt_qplib_alloc_init_hwq(&nq->hwq, &hwq_attr)) अणु
		dev_err(&nq->pdev->dev, "FP NQ allocation failed");
		वापस -ENOMEM;
	पूर्ण
	nq->budget = 8;
	वापस 0;
पूर्ण

/* SRQ */
व्योम bnxt_qplib_destroy_srq(काष्ठा bnxt_qplib_res *res,
			   काष्ठा bnxt_qplib_srq *srq)
अणु
	काष्ठा bnxt_qplib_rcfw *rcfw = res->rcfw;
	काष्ठा cmdq_destroy_srq req;
	काष्ठा creq_destroy_srq_resp resp;
	u16 cmd_flags = 0;
	पूर्णांक rc;

	RCFW_CMD_PREP(req, DESTROY_SRQ, cmd_flags);

	/* Configure the request */
	req.srq_cid = cpu_to_le32(srq->id);

	rc = bnxt_qplib_rcfw_send_message(rcfw, (काष्ठा cmdq_base *)&req,
					  (काष्ठा creq_base *)&resp, शून्य, 0);
	kमुक्त(srq->swq);
	अगर (rc)
		वापस;
	bnxt_qplib_मुक्त_hwq(res, &srq->hwq);
पूर्ण

पूर्णांक bnxt_qplib_create_srq(काष्ठा bnxt_qplib_res *res,
			  काष्ठा bnxt_qplib_srq *srq)
अणु
	काष्ठा bnxt_qplib_rcfw *rcfw = res->rcfw;
	काष्ठा bnxt_qplib_hwq_attr hwq_attr = अणुपूर्ण;
	काष्ठा creq_create_srq_resp resp;
	काष्ठा cmdq_create_srq req;
	काष्ठा bnxt_qplib_pbl *pbl;
	u16 cmd_flags = 0;
	u16 pg_sz_lvl;
	पूर्णांक rc, idx;

	hwq_attr.res = res;
	hwq_attr.sginfo = &srq->sg_info;
	hwq_attr.depth = srq->max_wqe;
	hwq_attr.stride = srq->wqe_size;
	hwq_attr.type = HWQ_TYPE_QUEUE;
	rc = bnxt_qplib_alloc_init_hwq(&srq->hwq, &hwq_attr);
	अगर (rc)
		जाओ निकास;

	srq->swq = kसुस्मृति(srq->hwq.max_elements, माप(*srq->swq),
			   GFP_KERNEL);
	अगर (!srq->swq) अणु
		rc = -ENOMEM;
		जाओ fail;
	पूर्ण

	RCFW_CMD_PREP(req, CREATE_SRQ, cmd_flags);

	/* Configure the request */
	req.dpi = cpu_to_le32(srq->dpi->dpi);
	req.srq_handle = cpu_to_le64((uपूर्णांकptr_t)srq);

	req.srq_size = cpu_to_le16((u16)srq->hwq.max_elements);
	pbl = &srq->hwq.pbl[PBL_LVL_0];
	pg_sz_lvl = ((u16)bnxt_qplib_base_pg_size(&srq->hwq) <<
		     CMDQ_CREATE_SRQ_PG_SIZE_SFT);
	pg_sz_lvl |= (srq->hwq.level & CMDQ_CREATE_SRQ_LVL_MASK) <<
		      CMDQ_CREATE_SRQ_LVL_SFT;
	req.pg_size_lvl = cpu_to_le16(pg_sz_lvl);
	req.pbl = cpu_to_le64(pbl->pg_map_arr[0]);
	req.pd_id = cpu_to_le32(srq->pd->id);
	req.eventq_id = cpu_to_le16(srq->eventq_hw_ring_id);

	rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req,
					  (व्योम *)&resp, शून्य, 0);
	अगर (rc)
		जाओ fail;

	spin_lock_init(&srq->lock);
	srq->start_idx = 0;
	srq->last_idx = srq->hwq.max_elements - 1;
	क्रम (idx = 0; idx < srq->hwq.max_elements; idx++)
		srq->swq[idx].next_idx = idx + 1;
	srq->swq[srq->last_idx].next_idx = -1;

	srq->id = le32_to_cpu(resp.xid);
	srq->dbinfo.hwq = &srq->hwq;
	srq->dbinfo.xid = srq->id;
	srq->dbinfo.db = srq->dpi->dbr;
	srq->dbinfo.max_slot = 1;
	srq->dbinfo.priv_db = res->dpi_tbl.dbr_bar_reg_iomem;
	अगर (srq->threshold)
		bnxt_qplib_armen_db(&srq->dbinfo, DBC_DBC_TYPE_SRQ_ARMENA);
	srq->arm_req = false;

	वापस 0;
fail:
	bnxt_qplib_मुक्त_hwq(res, &srq->hwq);
	kमुक्त(srq->swq);
निकास:
	वापस rc;
पूर्ण

पूर्णांक bnxt_qplib_modअगरy_srq(काष्ठा bnxt_qplib_res *res,
			  काष्ठा bnxt_qplib_srq *srq)
अणु
	काष्ठा bnxt_qplib_hwq *srq_hwq = &srq->hwq;
	u32 sw_prod, sw_cons, count = 0;

	sw_prod = HWQ_CMP(srq_hwq->prod, srq_hwq);
	sw_cons = HWQ_CMP(srq_hwq->cons, srq_hwq);

	count = sw_prod > sw_cons ? sw_prod - sw_cons :
				    srq_hwq->max_elements - sw_cons + sw_prod;
	अगर (count > srq->threshold) अणु
		srq->arm_req = false;
		bnxt_qplib_srq_arm_db(&srq->dbinfo, srq->threshold);
	पूर्ण अन्यथा अणु
		/* Deferred arming */
		srq->arm_req = true;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक bnxt_qplib_query_srq(काष्ठा bnxt_qplib_res *res,
			 काष्ठा bnxt_qplib_srq *srq)
अणु
	काष्ठा bnxt_qplib_rcfw *rcfw = res->rcfw;
	काष्ठा cmdq_query_srq req;
	काष्ठा creq_query_srq_resp resp;
	काष्ठा bnxt_qplib_rcfw_sbuf *sbuf;
	काष्ठा creq_query_srq_resp_sb *sb;
	u16 cmd_flags = 0;
	पूर्णांक rc = 0;

	RCFW_CMD_PREP(req, QUERY_SRQ, cmd_flags);
	req.srq_cid = cpu_to_le32(srq->id);

	/* Configure the request */
	sbuf = bnxt_qplib_rcfw_alloc_sbuf(rcfw, माप(*sb));
	अगर (!sbuf)
		वापस -ENOMEM;
	sb = sbuf->sb;
	rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req, (व्योम *)&resp,
					  (व्योम *)sbuf, 0);
	srq->threshold = le16_to_cpu(sb->srq_limit);
	bnxt_qplib_rcfw_मुक्त_sbuf(rcfw, sbuf);

	वापस rc;
पूर्ण

पूर्णांक bnxt_qplib_post_srq_recv(काष्ठा bnxt_qplib_srq *srq,
			     काष्ठा bnxt_qplib_swqe *wqe)
अणु
	काष्ठा bnxt_qplib_hwq *srq_hwq = &srq->hwq;
	काष्ठा rq_wqe *srqe;
	काष्ठा sq_sge *hw_sge;
	u32 sw_prod, sw_cons, count = 0;
	पूर्णांक i, rc = 0, next;

	spin_lock(&srq_hwq->lock);
	अगर (srq->start_idx == srq->last_idx) अणु
		dev_err(&srq_hwq->pdev->dev,
			"FP: SRQ (0x%x) is full!\n", srq->id);
		rc = -EINVAL;
		spin_unlock(&srq_hwq->lock);
		जाओ करोne;
	पूर्ण
	next = srq->start_idx;
	srq->start_idx = srq->swq[next].next_idx;
	spin_unlock(&srq_hwq->lock);

	sw_prod = HWQ_CMP(srq_hwq->prod, srq_hwq);
	srqe = bnxt_qplib_get_qe(srq_hwq, sw_prod, शून्य);
	स_रखो(srqe, 0, srq->wqe_size);
	/* Calculate wqe_size16 and data_len */
	क्रम (i = 0, hw_sge = (काष्ठा sq_sge *)srqe->data;
	     i < wqe->num_sge; i++, hw_sge++) अणु
		hw_sge->va_or_pa = cpu_to_le64(wqe->sg_list[i].addr);
		hw_sge->l_key = cpu_to_le32(wqe->sg_list[i].lkey);
		hw_sge->size = cpu_to_le32(wqe->sg_list[i].size);
	पूर्ण
	srqe->wqe_type = wqe->type;
	srqe->flags = wqe->flags;
	srqe->wqe_size = wqe->num_sge +
			((दुरत्व(typeof(*srqe), data) + 15) >> 4);
	srqe->wr_id[0] = cpu_to_le32((u32)next);
	srq->swq[next].wr_id = wqe->wr_id;

	srq_hwq->prod++;

	spin_lock(&srq_hwq->lock);
	sw_prod = HWQ_CMP(srq_hwq->prod, srq_hwq);
	/* retaining srq_hwq->cons क्रम this logic
	 * actually the lock is only required to
	 * पढ़ो srq_hwq->cons.
	 */
	sw_cons = HWQ_CMP(srq_hwq->cons, srq_hwq);
	count = sw_prod > sw_cons ? sw_prod - sw_cons :
				    srq_hwq->max_elements - sw_cons + sw_prod;
	spin_unlock(&srq_hwq->lock);
	/* Ring DB */
	bnxt_qplib_ring_prod_db(&srq->dbinfo, DBC_DBC_TYPE_SRQ);
	अगर (srq->arm_req == true && count > srq->threshold) अणु
		srq->arm_req = false;
		bnxt_qplib_srq_arm_db(&srq->dbinfo, srq->threshold);
	पूर्ण
करोne:
	वापस rc;
पूर्ण

/* QP */

अटल पूर्णांक bnxt_qplib_alloc_init_swq(काष्ठा bnxt_qplib_q *que)
अणु
	पूर्णांक rc = 0;
	पूर्णांक indx;

	que->swq = kसुस्मृति(que->max_wqe, माप(*que->swq), GFP_KERNEL);
	अगर (!que->swq) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	que->swq_start = 0;
	que->swq_last = que->max_wqe - 1;
	क्रम (indx = 0; indx < que->max_wqe; indx++)
		que->swq[indx].next_idx = indx + 1;
	que->swq[que->swq_last].next_idx = 0; /* Make it circular */
	que->swq_last = 0;
out:
	वापस rc;
पूर्ण

पूर्णांक bnxt_qplib_create_qp1(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_qp *qp)
अणु
	काष्ठा bnxt_qplib_hwq_attr hwq_attr = अणुपूर्ण;
	काष्ठा bnxt_qplib_rcfw *rcfw = res->rcfw;
	काष्ठा bnxt_qplib_q *sq = &qp->sq;
	काष्ठा bnxt_qplib_q *rq = &qp->rq;
	काष्ठा creq_create_qp1_resp resp;
	काष्ठा cmdq_create_qp1 req;
	काष्ठा bnxt_qplib_pbl *pbl;
	u16 cmd_flags = 0;
	u32 qp_flags = 0;
	u8 pg_sz_lvl;
	u32 tbl_indx;
	पूर्णांक rc;

	RCFW_CMD_PREP(req, CREATE_QP1, cmd_flags);

	/* General */
	req.type = qp->type;
	req.dpi = cpu_to_le32(qp->dpi->dpi);
	req.qp_handle = cpu_to_le64(qp->qp_handle);

	/* SQ */
	hwq_attr.res = res;
	hwq_attr.sginfo = &sq->sg_info;
	hwq_attr.stride = माप(काष्ठा sq_sge);
	hwq_attr.depth = bnxt_qplib_get_depth(sq);
	hwq_attr.type = HWQ_TYPE_QUEUE;
	rc = bnxt_qplib_alloc_init_hwq(&sq->hwq, &hwq_attr);
	अगर (rc)
		जाओ निकास;

	rc = bnxt_qplib_alloc_init_swq(sq);
	अगर (rc)
		जाओ fail_sq;

	req.sq_size = cpu_to_le32(bnxt_qplib_set_sq_size(sq, qp->wqe_mode));
	pbl = &sq->hwq.pbl[PBL_LVL_0];
	req.sq_pbl = cpu_to_le64(pbl->pg_map_arr[0]);
	pg_sz_lvl = (bnxt_qplib_base_pg_size(&sq->hwq) <<
		     CMDQ_CREATE_QP1_SQ_PG_SIZE_SFT);
	pg_sz_lvl |= (sq->hwq.level & CMDQ_CREATE_QP1_SQ_LVL_MASK);
	req.sq_pg_size_sq_lvl = pg_sz_lvl;
	req.sq_fwo_sq_sge =
		cpu_to_le16((sq->max_sge & CMDQ_CREATE_QP1_SQ_SGE_MASK) <<
			     CMDQ_CREATE_QP1_SQ_SGE_SFT);
	req.scq_cid = cpu_to_le32(qp->scq->id);

	/* RQ */
	अगर (rq->max_wqe) अणु
		hwq_attr.res = res;
		hwq_attr.sginfo = &rq->sg_info;
		hwq_attr.stride = माप(काष्ठा sq_sge);
		hwq_attr.depth = bnxt_qplib_get_depth(rq);
		hwq_attr.type = HWQ_TYPE_QUEUE;
		rc = bnxt_qplib_alloc_init_hwq(&rq->hwq, &hwq_attr);
		अगर (rc)
			जाओ sq_swq;
		rc = bnxt_qplib_alloc_init_swq(rq);
		अगर (rc)
			जाओ fail_rq;
		req.rq_size = cpu_to_le32(rq->max_wqe);
		pbl = &rq->hwq.pbl[PBL_LVL_0];
		req.rq_pbl = cpu_to_le64(pbl->pg_map_arr[0]);
		pg_sz_lvl = (bnxt_qplib_base_pg_size(&rq->hwq) <<
			     CMDQ_CREATE_QP1_RQ_PG_SIZE_SFT);
		pg_sz_lvl |= (rq->hwq.level & CMDQ_CREATE_QP1_RQ_LVL_MASK);
		req.rq_pg_size_rq_lvl = pg_sz_lvl;
		req.rq_fwo_rq_sge =
			cpu_to_le16((rq->max_sge &
				     CMDQ_CREATE_QP1_RQ_SGE_MASK) <<
				    CMDQ_CREATE_QP1_RQ_SGE_SFT);
	पूर्ण
	req.rcq_cid = cpu_to_le32(qp->rcq->id);
	/* Header buffer - allow hdr_buf pass in */
	rc = bnxt_qplib_alloc_qp_hdr_buf(res, qp);
	अगर (rc) अणु
		rc = -ENOMEM;
		जाओ rq_rwq;
	पूर्ण
	qp_flags |= CMDQ_CREATE_QP1_QP_FLAGS_RESERVED_LKEY_ENABLE;
	req.qp_flags = cpu_to_le32(qp_flags);
	req.pd_id = cpu_to_le32(qp->pd->id);

	rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req,
					  (व्योम *)&resp, शून्य, 0);
	अगर (rc)
		जाओ fail;

	qp->id = le32_to_cpu(resp.xid);
	qp->cur_qp_state = CMDQ_MODIFY_QP_NEW_STATE_RESET;
	qp->cctx = res->cctx;
	sq->dbinfo.hwq = &sq->hwq;
	sq->dbinfo.xid = qp->id;
	sq->dbinfo.db = qp->dpi->dbr;
	sq->dbinfo.max_slot = bnxt_qplib_set_sq_max_slot(qp->wqe_mode);
	अगर (rq->max_wqe) अणु
		rq->dbinfo.hwq = &rq->hwq;
		rq->dbinfo.xid = qp->id;
		rq->dbinfo.db = qp->dpi->dbr;
		rq->dbinfo.max_slot = bnxt_qplib_set_rq_max_slot(rq->wqe_size);
	पूर्ण
	tbl_indx = map_qp_id_to_tbl_indx(qp->id, rcfw);
	rcfw->qp_tbl[tbl_indx].qp_id = qp->id;
	rcfw->qp_tbl[tbl_indx].qp_handle = (व्योम *)qp;

	वापस 0;

fail:
	bnxt_qplib_मुक्त_qp_hdr_buf(res, qp);
rq_rwq:
	kमुक्त(rq->swq);
fail_rq:
	bnxt_qplib_मुक्त_hwq(res, &rq->hwq);
sq_swq:
	kमुक्त(sq->swq);
fail_sq:
	bnxt_qplib_मुक्त_hwq(res, &sq->hwq);
निकास:
	वापस rc;
पूर्ण

अटल व्योम bnxt_qplib_init_psn_ptr(काष्ठा bnxt_qplib_qp *qp, पूर्णांक size)
अणु
	काष्ठा bnxt_qplib_hwq *hwq;
	काष्ठा bnxt_qplib_q *sq;
	u64 fpsne, psn_pg;
	u16 indx_pad = 0;

	sq = &qp->sq;
	hwq = &sq->hwq;
	/* First psn entry */
	fpsne = (u64)bnxt_qplib_get_qe(hwq, hwq->depth, &psn_pg);
	अगर (!IS_ALIGNED(fpsne, PAGE_SIZE))
		indx_pad = (fpsne & ~PAGE_MASK) / size;
	hwq->pad_pgofft = indx_pad;
	hwq->pad_pg = (u64 *)psn_pg;
	hwq->pad_stride = size;
पूर्ण

पूर्णांक bnxt_qplib_create_qp(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_qp *qp)
अणु
	काष्ठा bnxt_qplib_rcfw *rcfw = res->rcfw;
	काष्ठा bnxt_qplib_hwq_attr hwq_attr = अणुपूर्ण;
	काष्ठा bnxt_qplib_sg_info sginfo = अणुपूर्ण;
	काष्ठा bnxt_qplib_q *sq = &qp->sq;
	काष्ठा bnxt_qplib_q *rq = &qp->rq;
	काष्ठा creq_create_qp_resp resp;
	पूर्णांक rc, req_size, psn_sz = 0;
	काष्ठा bnxt_qplib_hwq *xrrq;
	काष्ठा bnxt_qplib_pbl *pbl;
	काष्ठा cmdq_create_qp req;
	u16 cmd_flags = 0;
	u32 qp_flags = 0;
	u8 pg_sz_lvl;
	u32 tbl_indx;
	u16 nsge;

	RCFW_CMD_PREP(req, CREATE_QP, cmd_flags);

	/* General */
	req.type = qp->type;
	req.dpi = cpu_to_le32(qp->dpi->dpi);
	req.qp_handle = cpu_to_le64(qp->qp_handle);

	/* SQ */
	अगर (qp->type == CMDQ_CREATE_QP_TYPE_RC) अणु
		psn_sz = bnxt_qplib_is_chip_gen_p5(res->cctx) ?
			 माप(काष्ठा sq_psn_search_ext) :
			 माप(काष्ठा sq_psn_search);
	पूर्ण

	hwq_attr.res = res;
	hwq_attr.sginfo = &sq->sg_info;
	hwq_attr.stride = माप(काष्ठा sq_sge);
	hwq_attr.depth = bnxt_qplib_get_depth(sq);
	hwq_attr.aux_stride = psn_sz;
	hwq_attr.aux_depth = bnxt_qplib_set_sq_size(sq, qp->wqe_mode);
	hwq_attr.type = HWQ_TYPE_QUEUE;
	rc = bnxt_qplib_alloc_init_hwq(&sq->hwq, &hwq_attr);
	अगर (rc)
		जाओ निकास;

	rc = bnxt_qplib_alloc_init_swq(sq);
	अगर (rc)
		जाओ fail_sq;

	अगर (psn_sz)
		bnxt_qplib_init_psn_ptr(qp, psn_sz);

	req.sq_size = cpu_to_le32(bnxt_qplib_set_sq_size(sq, qp->wqe_mode));
	pbl = &sq->hwq.pbl[PBL_LVL_0];
	req.sq_pbl = cpu_to_le64(pbl->pg_map_arr[0]);
	pg_sz_lvl = (bnxt_qplib_base_pg_size(&sq->hwq) <<
		     CMDQ_CREATE_QP_SQ_PG_SIZE_SFT);
	pg_sz_lvl |= (sq->hwq.level & CMDQ_CREATE_QP_SQ_LVL_MASK);
	req.sq_pg_size_sq_lvl = pg_sz_lvl;
	req.sq_fwo_sq_sge =
		cpu_to_le16(((sq->max_sge & CMDQ_CREATE_QP_SQ_SGE_MASK) <<
			     CMDQ_CREATE_QP_SQ_SGE_SFT) | 0);
	req.scq_cid = cpu_to_le32(qp->scq->id);

	/* RQ */
	अगर (!qp->srq) अणु
		hwq_attr.res = res;
		hwq_attr.sginfo = &rq->sg_info;
		hwq_attr.stride = माप(काष्ठा sq_sge);
		hwq_attr.depth = bnxt_qplib_get_depth(rq);
		hwq_attr.aux_stride = 0;
		hwq_attr.aux_depth = 0;
		hwq_attr.type = HWQ_TYPE_QUEUE;
		rc = bnxt_qplib_alloc_init_hwq(&rq->hwq, &hwq_attr);
		अगर (rc)
			जाओ sq_swq;
		rc = bnxt_qplib_alloc_init_swq(rq);
		अगर (rc)
			जाओ fail_rq;

		req.rq_size = cpu_to_le32(rq->max_wqe);
		pbl = &rq->hwq.pbl[PBL_LVL_0];
		req.rq_pbl = cpu_to_le64(pbl->pg_map_arr[0]);
		pg_sz_lvl = (bnxt_qplib_base_pg_size(&rq->hwq) <<
			     CMDQ_CREATE_QP_RQ_PG_SIZE_SFT);
		pg_sz_lvl |= (rq->hwq.level & CMDQ_CREATE_QP_RQ_LVL_MASK);
		req.rq_pg_size_rq_lvl = pg_sz_lvl;
		nsge = (qp->wqe_mode == BNXT_QPLIB_WQE_MODE_STATIC) ?
			6 : rq->max_sge;
		req.rq_fwo_rq_sge =
			cpu_to_le16(((nsge &
				      CMDQ_CREATE_QP_RQ_SGE_MASK) <<
				     CMDQ_CREATE_QP_RQ_SGE_SFT) | 0);
	पूर्ण अन्यथा अणु
		/* SRQ */
		qp_flags |= CMDQ_CREATE_QP_QP_FLAGS_SRQ_USED;
		req.srq_cid = cpu_to_le32(qp->srq->id);
	पूर्ण
	req.rcq_cid = cpu_to_le32(qp->rcq->id);

	qp_flags |= CMDQ_CREATE_QP_QP_FLAGS_RESERVED_LKEY_ENABLE;
	qp_flags |= CMDQ_CREATE_QP_QP_FLAGS_FR_PMR_ENABLED;
	अगर (qp->sig_type)
		qp_flags |= CMDQ_CREATE_QP_QP_FLAGS_FORCE_COMPLETION;
	अगर (qp->wqe_mode == BNXT_QPLIB_WQE_MODE_VARIABLE)
		qp_flags |= CMDQ_CREATE_QP_QP_FLAGS_VARIABLE_SIZED_WQE_ENABLED;
	req.qp_flags = cpu_to_le32(qp_flags);

	/* ORRQ and IRRQ */
	अगर (psn_sz) अणु
		xrrq = &qp->orrq;
		xrrq->max_elements =
			ORD_LIMIT_TO_ORRQ_SLOTS(qp->max_rd_atomic);
		req_size = xrrq->max_elements *
			   BNXT_QPLIB_MAX_ORRQE_ENTRY_SIZE + PAGE_SIZE - 1;
		req_size &= ~(PAGE_SIZE - 1);
		sginfo.pgsize = req_size;
		sginfo.pgshft = PAGE_SHIFT;

		hwq_attr.res = res;
		hwq_attr.sginfo = &sginfo;
		hwq_attr.depth = xrrq->max_elements;
		hwq_attr.stride = BNXT_QPLIB_MAX_ORRQE_ENTRY_SIZE;
		hwq_attr.aux_stride = 0;
		hwq_attr.aux_depth = 0;
		hwq_attr.type = HWQ_TYPE_CTX;
		rc = bnxt_qplib_alloc_init_hwq(xrrq, &hwq_attr);
		अगर (rc)
			जाओ rq_swq;
		pbl = &xrrq->pbl[PBL_LVL_0];
		req.orrq_addr = cpu_to_le64(pbl->pg_map_arr[0]);

		xrrq = &qp->irrq;
		xrrq->max_elements = IRD_LIMIT_TO_IRRQ_SLOTS(
						qp->max_dest_rd_atomic);
		req_size = xrrq->max_elements *
			   BNXT_QPLIB_MAX_IRRQE_ENTRY_SIZE + PAGE_SIZE - 1;
		req_size &= ~(PAGE_SIZE - 1);
		sginfo.pgsize = req_size;
		hwq_attr.depth =  xrrq->max_elements;
		hwq_attr.stride = BNXT_QPLIB_MAX_IRRQE_ENTRY_SIZE;
		rc = bnxt_qplib_alloc_init_hwq(xrrq, &hwq_attr);
		अगर (rc)
			जाओ fail_orrq;

		pbl = &xrrq->pbl[PBL_LVL_0];
		req.irrq_addr = cpu_to_le64(pbl->pg_map_arr[0]);
	पूर्ण
	req.pd_id = cpu_to_le32(qp->pd->id);

	rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req,
					  (व्योम *)&resp, शून्य, 0);
	अगर (rc)
		जाओ fail;

	qp->id = le32_to_cpu(resp.xid);
	qp->cur_qp_state = CMDQ_MODIFY_QP_NEW_STATE_RESET;
	INIT_LIST_HEAD(&qp->sq_flush);
	INIT_LIST_HEAD(&qp->rq_flush);
	qp->cctx = res->cctx;
	sq->dbinfo.hwq = &sq->hwq;
	sq->dbinfo.xid = qp->id;
	sq->dbinfo.db = qp->dpi->dbr;
	sq->dbinfo.max_slot = bnxt_qplib_set_sq_max_slot(qp->wqe_mode);
	अगर (rq->max_wqe) अणु
		rq->dbinfo.hwq = &rq->hwq;
		rq->dbinfo.xid = qp->id;
		rq->dbinfo.db = qp->dpi->dbr;
		rq->dbinfo.max_slot = bnxt_qplib_set_rq_max_slot(rq->wqe_size);
	पूर्ण
	tbl_indx = map_qp_id_to_tbl_indx(qp->id, rcfw);
	rcfw->qp_tbl[tbl_indx].qp_id = qp->id;
	rcfw->qp_tbl[tbl_indx].qp_handle = (व्योम *)qp;

	वापस 0;
fail:
	bnxt_qplib_मुक्त_hwq(res, &qp->irrq);
fail_orrq:
	bnxt_qplib_मुक्त_hwq(res, &qp->orrq);
rq_swq:
	kमुक्त(rq->swq);
fail_rq:
	bnxt_qplib_मुक्त_hwq(res, &rq->hwq);
sq_swq:
	kमुक्त(sq->swq);
fail_sq:
	bnxt_qplib_मुक्त_hwq(res, &sq->hwq);
निकास:
	वापस rc;
पूर्ण

अटल व्योम __modअगरy_flags_from_init_state(काष्ठा bnxt_qplib_qp *qp)
अणु
	चयन (qp->state) अणु
	हाल CMDQ_MODIFY_QP_NEW_STATE_RTR:
		/* INIT->RTR, configure the path_mtu to the शेष
		 * 2048 अगर not being requested
		 */
		अगर (!(qp->modअगरy_flags &
		    CMDQ_MODIFY_QP_MODIFY_MASK_PATH_MTU)) अणु
			qp->modअगरy_flags |=
				CMDQ_MODIFY_QP_MODIFY_MASK_PATH_MTU;
			qp->path_mtu =
				CMDQ_MODIFY_QP_PATH_MTU_MTU_2048;
		पूर्ण
		qp->modअगरy_flags &=
			~CMDQ_MODIFY_QP_MODIFY_MASK_VLAN_ID;
		/* Bono FW require the max_dest_rd_atomic to be >= 1 */
		अगर (qp->max_dest_rd_atomic < 1)
			qp->max_dest_rd_atomic = 1;
		qp->modअगरy_flags &= ~CMDQ_MODIFY_QP_MODIFY_MASK_SRC_MAC;
		/* Bono FW 20.6.5 requires SGID_INDEX configuration */
		अगर (!(qp->modअगरy_flags &
		    CMDQ_MODIFY_QP_MODIFY_MASK_SGID_INDEX)) अणु
			qp->modअगरy_flags |=
				CMDQ_MODIFY_QP_MODIFY_MASK_SGID_INDEX;
			qp->ah.sgid_index = 0;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम __modअगरy_flags_from_rtr_state(काष्ठा bnxt_qplib_qp *qp)
अणु
	चयन (qp->state) अणु
	हाल CMDQ_MODIFY_QP_NEW_STATE_RTS:
		/* Bono FW requires the max_rd_atomic to be >= 1 */
		अगर (qp->max_rd_atomic < 1)
			qp->max_rd_atomic = 1;
		/* Bono FW करोes not allow PKEY_INDEX,
		 * DGID, FLOW_LABEL, SGID_INDEX, HOP_LIMIT,
		 * TRAFFIC_CLASS, DEST_MAC, PATH_MTU, RQ_PSN,
		 * MIN_RNR_TIMER, MAX_DEST_RD_ATOMIC, DEST_QP_ID
		 * modअगरication
		 */
		qp->modअगरy_flags &=
			~(CMDQ_MODIFY_QP_MODIFY_MASK_PKEY |
			  CMDQ_MODIFY_QP_MODIFY_MASK_DGID |
			  CMDQ_MODIFY_QP_MODIFY_MASK_FLOW_LABEL |
			  CMDQ_MODIFY_QP_MODIFY_MASK_SGID_INDEX |
			  CMDQ_MODIFY_QP_MODIFY_MASK_HOP_LIMIT |
			  CMDQ_MODIFY_QP_MODIFY_MASK_TRAFFIC_CLASS |
			  CMDQ_MODIFY_QP_MODIFY_MASK_DEST_MAC |
			  CMDQ_MODIFY_QP_MODIFY_MASK_PATH_MTU |
			  CMDQ_MODIFY_QP_MODIFY_MASK_RQ_PSN |
			  CMDQ_MODIFY_QP_MODIFY_MASK_MIN_RNR_TIMER |
			  CMDQ_MODIFY_QP_MODIFY_MASK_MAX_DEST_RD_ATOMIC |
			  CMDQ_MODIFY_QP_MODIFY_MASK_DEST_QP_ID);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम __filter_modअगरy_flags(काष्ठा bnxt_qplib_qp *qp)
अणु
	चयन (qp->cur_qp_state) अणु
	हाल CMDQ_MODIFY_QP_NEW_STATE_RESET:
		अवरोध;
	हाल CMDQ_MODIFY_QP_NEW_STATE_INIT:
		__modअगरy_flags_from_init_state(qp);
		अवरोध;
	हाल CMDQ_MODIFY_QP_NEW_STATE_RTR:
		__modअगरy_flags_from_rtr_state(qp);
		अवरोध;
	हाल CMDQ_MODIFY_QP_NEW_STATE_RTS:
		अवरोध;
	हाल CMDQ_MODIFY_QP_NEW_STATE_SQD:
		अवरोध;
	हाल CMDQ_MODIFY_QP_NEW_STATE_SQE:
		अवरोध;
	हाल CMDQ_MODIFY_QP_NEW_STATE_ERR:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक bnxt_qplib_modअगरy_qp(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_qp *qp)
अणु
	काष्ठा bnxt_qplib_rcfw *rcfw = res->rcfw;
	काष्ठा cmdq_modअगरy_qp req;
	काष्ठा creq_modअगरy_qp_resp resp;
	u16 cmd_flags = 0, pkey;
	u32 temp32[4];
	u32 bmask;
	पूर्णांक rc;

	RCFW_CMD_PREP(req, MODIFY_QP, cmd_flags);

	/* Filter out the qp_attr_mask based on the state->new transition */
	__filter_modअगरy_flags(qp);
	bmask = qp->modअगरy_flags;
	req.modअगरy_mask = cpu_to_le32(qp->modअगरy_flags);
	req.qp_cid = cpu_to_le32(qp->id);
	अगर (bmask & CMDQ_MODIFY_QP_MODIFY_MASK_STATE) अणु
		req.network_type_en_sqd_async_notअगरy_new_state =
				(qp->state & CMDQ_MODIFY_QP_NEW_STATE_MASK) |
				(qp->en_sqd_async_notअगरy ?
					CMDQ_MODIFY_QP_EN_SQD_ASYNC_NOTIFY : 0);
	पूर्ण
	req.network_type_en_sqd_async_notअगरy_new_state |= qp->nw_type;

	अगर (bmask & CMDQ_MODIFY_QP_MODIFY_MASK_ACCESS)
		req.access = qp->access;

	अगर (bmask & CMDQ_MODIFY_QP_MODIFY_MASK_PKEY) अणु
		अगर (!bnxt_qplib_get_pkey(res, &res->pkey_tbl,
					 qp->pkey_index, &pkey))
			req.pkey = cpu_to_le16(pkey);
	पूर्ण
	अगर (bmask & CMDQ_MODIFY_QP_MODIFY_MASK_QKEY)
		req.qkey = cpu_to_le32(qp->qkey);

	अगर (bmask & CMDQ_MODIFY_QP_MODIFY_MASK_DGID) अणु
		स_नकल(temp32, qp->ah.dgid.data, माप(काष्ठा bnxt_qplib_gid));
		req.dgid[0] = cpu_to_le32(temp32[0]);
		req.dgid[1] = cpu_to_le32(temp32[1]);
		req.dgid[2] = cpu_to_le32(temp32[2]);
		req.dgid[3] = cpu_to_le32(temp32[3]);
	पूर्ण
	अगर (bmask & CMDQ_MODIFY_QP_MODIFY_MASK_FLOW_LABEL)
		req.flow_label = cpu_to_le32(qp->ah.flow_label);

	अगर (bmask & CMDQ_MODIFY_QP_MODIFY_MASK_SGID_INDEX)
		req.sgid_index = cpu_to_le16(res->sgid_tbl.hw_id
					     [qp->ah.sgid_index]);

	अगर (bmask & CMDQ_MODIFY_QP_MODIFY_MASK_HOP_LIMIT)
		req.hop_limit = qp->ah.hop_limit;

	अगर (bmask & CMDQ_MODIFY_QP_MODIFY_MASK_TRAFFIC_CLASS)
		req.traffic_class = qp->ah.traffic_class;

	अगर (bmask & CMDQ_MODIFY_QP_MODIFY_MASK_DEST_MAC)
		स_नकल(req.dest_mac, qp->ah.dmac, 6);

	अगर (bmask & CMDQ_MODIFY_QP_MODIFY_MASK_PATH_MTU)
		req.path_mtu = qp->path_mtu;

	अगर (bmask & CMDQ_MODIFY_QP_MODIFY_MASK_TIMEOUT)
		req.समयout = qp->समयout;

	अगर (bmask & CMDQ_MODIFY_QP_MODIFY_MASK_RETRY_CNT)
		req.retry_cnt = qp->retry_cnt;

	अगर (bmask & CMDQ_MODIFY_QP_MODIFY_MASK_RNR_RETRY)
		req.rnr_retry = qp->rnr_retry;

	अगर (bmask & CMDQ_MODIFY_QP_MODIFY_MASK_MIN_RNR_TIMER)
		req.min_rnr_समयr = qp->min_rnr_समयr;

	अगर (bmask & CMDQ_MODIFY_QP_MODIFY_MASK_RQ_PSN)
		req.rq_psn = cpu_to_le32(qp->rq.psn);

	अगर (bmask & CMDQ_MODIFY_QP_MODIFY_MASK_SQ_PSN)
		req.sq_psn = cpu_to_le32(qp->sq.psn);

	अगर (bmask & CMDQ_MODIFY_QP_MODIFY_MASK_MAX_RD_ATOMIC)
		req.max_rd_atomic =
			ORD_LIMIT_TO_ORRQ_SLOTS(qp->max_rd_atomic);

	अगर (bmask & CMDQ_MODIFY_QP_MODIFY_MASK_MAX_DEST_RD_ATOMIC)
		req.max_dest_rd_atomic =
			IRD_LIMIT_TO_IRRQ_SLOTS(qp->max_dest_rd_atomic);

	req.sq_size = cpu_to_le32(qp->sq.hwq.max_elements);
	req.rq_size = cpu_to_le32(qp->rq.hwq.max_elements);
	req.sq_sge = cpu_to_le16(qp->sq.max_sge);
	req.rq_sge = cpu_to_le16(qp->rq.max_sge);
	req.max_अंतरभूत_data = cpu_to_le32(qp->max_अंतरभूत_data);
	अगर (bmask & CMDQ_MODIFY_QP_MODIFY_MASK_DEST_QP_ID)
		req.dest_qp_id = cpu_to_le32(qp->dest_qpn);

	req.vlan_pcp_vlan_dei_vlan_id = cpu_to_le16(qp->vlan_id);

	rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req,
					  (व्योम *)&resp, शून्य, 0);
	अगर (rc)
		वापस rc;
	qp->cur_qp_state = qp->state;
	वापस 0;
पूर्ण

पूर्णांक bnxt_qplib_query_qp(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_qp *qp)
अणु
	काष्ठा bnxt_qplib_rcfw *rcfw = res->rcfw;
	काष्ठा cmdq_query_qp req;
	काष्ठा creq_query_qp_resp resp;
	काष्ठा bnxt_qplib_rcfw_sbuf *sbuf;
	काष्ठा creq_query_qp_resp_sb *sb;
	u16 cmd_flags = 0;
	u32 temp32[4];
	पूर्णांक i, rc = 0;

	RCFW_CMD_PREP(req, QUERY_QP, cmd_flags);

	sbuf = bnxt_qplib_rcfw_alloc_sbuf(rcfw, माप(*sb));
	अगर (!sbuf)
		वापस -ENOMEM;
	sb = sbuf->sb;

	req.qp_cid = cpu_to_le32(qp->id);
	req.resp_size = माप(*sb) / BNXT_QPLIB_CMDQE_UNITS;
	rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req, (व्योम *)&resp,
					  (व्योम *)sbuf, 0);
	अगर (rc)
		जाओ bail;
	/* Extract the context from the side buffer */
	qp->state = sb->en_sqd_async_notअगरy_state &
			CREQ_QUERY_QP_RESP_SB_STATE_MASK;
	qp->en_sqd_async_notअगरy = sb->en_sqd_async_notअगरy_state &
				  CREQ_QUERY_QP_RESP_SB_EN_SQD_ASYNC_NOTIFY ?
				  true : false;
	qp->access = sb->access;
	qp->pkey_index = le16_to_cpu(sb->pkey);
	qp->qkey = le32_to_cpu(sb->qkey);

	temp32[0] = le32_to_cpu(sb->dgid[0]);
	temp32[1] = le32_to_cpu(sb->dgid[1]);
	temp32[2] = le32_to_cpu(sb->dgid[2]);
	temp32[3] = le32_to_cpu(sb->dgid[3]);
	स_नकल(qp->ah.dgid.data, temp32, माप(qp->ah.dgid.data));

	qp->ah.flow_label = le32_to_cpu(sb->flow_label);

	qp->ah.sgid_index = 0;
	क्रम (i = 0; i < res->sgid_tbl.max; i++) अणु
		अगर (res->sgid_tbl.hw_id[i] == le16_to_cpu(sb->sgid_index)) अणु
			qp->ah.sgid_index = i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == res->sgid_tbl.max)
		dev_warn(&res->pdev->dev, "SGID not found??\n");

	qp->ah.hop_limit = sb->hop_limit;
	qp->ah.traffic_class = sb->traffic_class;
	स_नकल(qp->ah.dmac, sb->dest_mac, 6);
	qp->ah.vlan_id = (le16_to_cpu(sb->path_mtu_dest_vlan_id) &
				CREQ_QUERY_QP_RESP_SB_VLAN_ID_MASK) >>
				CREQ_QUERY_QP_RESP_SB_VLAN_ID_SFT;
	qp->path_mtu = (le16_to_cpu(sb->path_mtu_dest_vlan_id) &
				    CREQ_QUERY_QP_RESP_SB_PATH_MTU_MASK) >>
				    CREQ_QUERY_QP_RESP_SB_PATH_MTU_SFT;
	qp->समयout = sb->समयout;
	qp->retry_cnt = sb->retry_cnt;
	qp->rnr_retry = sb->rnr_retry;
	qp->min_rnr_समयr = sb->min_rnr_समयr;
	qp->rq.psn = le32_to_cpu(sb->rq_psn);
	qp->max_rd_atomic = ORRQ_SLOTS_TO_ORD_LIMIT(sb->max_rd_atomic);
	qp->sq.psn = le32_to_cpu(sb->sq_psn);
	qp->max_dest_rd_atomic =
			IRRQ_SLOTS_TO_IRD_LIMIT(sb->max_dest_rd_atomic);
	qp->sq.max_wqe = qp->sq.hwq.max_elements;
	qp->rq.max_wqe = qp->rq.hwq.max_elements;
	qp->sq.max_sge = le16_to_cpu(sb->sq_sge);
	qp->rq.max_sge = le16_to_cpu(sb->rq_sge);
	qp->max_अंतरभूत_data = le32_to_cpu(sb->max_अंतरभूत_data);
	qp->dest_qpn = le32_to_cpu(sb->dest_qp_id);
	स_नकल(qp->smac, sb->src_mac, 6);
	qp->vlan_id = le16_to_cpu(sb->vlan_pcp_vlan_dei_vlan_id);
bail:
	bnxt_qplib_rcfw_मुक्त_sbuf(rcfw, sbuf);
	वापस rc;
पूर्ण

अटल व्योम __clean_cq(काष्ठा bnxt_qplib_cq *cq, u64 qp)
अणु
	काष्ठा bnxt_qplib_hwq *cq_hwq = &cq->hwq;
	काष्ठा cq_base *hw_cqe;
	पूर्णांक i;

	क्रम (i = 0; i < cq_hwq->max_elements; i++) अणु
		hw_cqe = bnxt_qplib_get_qe(cq_hwq, i, शून्य);
		अगर (!CQE_CMP_VALID(hw_cqe, i, cq_hwq->max_elements))
			जारी;
		/*
		 * The valid test of the entry must be करोne first beक्रमe
		 * पढ़ोing any further.
		 */
		dma_rmb();
		चयन (hw_cqe->cqe_type_toggle & CQ_BASE_CQE_TYPE_MASK) अणु
		हाल CQ_BASE_CQE_TYPE_REQ:
		हाल CQ_BASE_CQE_TYPE_TERMINAL:
		अणु
			काष्ठा cq_req *cqe = (काष्ठा cq_req *)hw_cqe;

			अगर (qp == le64_to_cpu(cqe->qp_handle))
				cqe->qp_handle = 0;
			अवरोध;
		पूर्ण
		हाल CQ_BASE_CQE_TYPE_RES_RC:
		हाल CQ_BASE_CQE_TYPE_RES_UD:
		हाल CQ_BASE_CQE_TYPE_RES_RAWETH_QP1:
		अणु
			काष्ठा cq_res_rc *cqe = (काष्ठा cq_res_rc *)hw_cqe;

			अगर (qp == le64_to_cpu(cqe->qp_handle))
				cqe->qp_handle = 0;
			अवरोध;
		पूर्ण
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक bnxt_qplib_destroy_qp(काष्ठा bnxt_qplib_res *res,
			  काष्ठा bnxt_qplib_qp *qp)
अणु
	काष्ठा bnxt_qplib_rcfw *rcfw = res->rcfw;
	काष्ठा cmdq_destroy_qp req;
	काष्ठा creq_destroy_qp_resp resp;
	u16 cmd_flags = 0;
	u32 tbl_indx;
	पूर्णांक rc;

	tbl_indx = map_qp_id_to_tbl_indx(qp->id, rcfw);
	rcfw->qp_tbl[tbl_indx].qp_id = BNXT_QPLIB_QP_ID_INVALID;
	rcfw->qp_tbl[tbl_indx].qp_handle = शून्य;

	RCFW_CMD_PREP(req, DESTROY_QP, cmd_flags);

	req.qp_cid = cpu_to_le32(qp->id);
	rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req,
					  (व्योम *)&resp, शून्य, 0);
	अगर (rc) अणु
		rcfw->qp_tbl[tbl_indx].qp_id = qp->id;
		rcfw->qp_tbl[tbl_indx].qp_handle = qp;
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

व्योम bnxt_qplib_मुक्त_qp_res(काष्ठा bnxt_qplib_res *res,
			    काष्ठा bnxt_qplib_qp *qp)
अणु
	bnxt_qplib_मुक्त_qp_hdr_buf(res, qp);
	bnxt_qplib_मुक्त_hwq(res, &qp->sq.hwq);
	kमुक्त(qp->sq.swq);

	bnxt_qplib_मुक्त_hwq(res, &qp->rq.hwq);
	kमुक्त(qp->rq.swq);

	अगर (qp->irrq.max_elements)
		bnxt_qplib_मुक्त_hwq(res, &qp->irrq);
	अगर (qp->orrq.max_elements)
		bnxt_qplib_मुक्त_hwq(res, &qp->orrq);

पूर्ण

व्योम *bnxt_qplib_get_qp1_sq_buf(काष्ठा bnxt_qplib_qp *qp,
				काष्ठा bnxt_qplib_sge *sge)
अणु
	काष्ठा bnxt_qplib_q *sq = &qp->sq;
	u32 sw_prod;

	स_रखो(sge, 0, माप(*sge));

	अगर (qp->sq_hdr_buf) अणु
		sw_prod = sq->swq_start;
		sge->addr = (dma_addr_t)(qp->sq_hdr_buf_map +
					 sw_prod * qp->sq_hdr_buf_size);
		sge->lkey = 0xFFFFFFFF;
		sge->size = qp->sq_hdr_buf_size;
		वापस qp->sq_hdr_buf + sw_prod * sge->size;
	पूर्ण
	वापस शून्य;
पूर्ण

u32 bnxt_qplib_get_rq_prod_index(काष्ठा bnxt_qplib_qp *qp)
अणु
	काष्ठा bnxt_qplib_q *rq = &qp->rq;

	वापस rq->swq_start;
पूर्ण

dma_addr_t bnxt_qplib_get_qp_buf_from_index(काष्ठा bnxt_qplib_qp *qp, u32 index)
अणु
	वापस (qp->rq_hdr_buf_map + index * qp->rq_hdr_buf_size);
पूर्ण

व्योम *bnxt_qplib_get_qp1_rq_buf(काष्ठा bnxt_qplib_qp *qp,
				काष्ठा bnxt_qplib_sge *sge)
अणु
	काष्ठा bnxt_qplib_q *rq = &qp->rq;
	u32 sw_prod;

	स_रखो(sge, 0, माप(*sge));

	अगर (qp->rq_hdr_buf) अणु
		sw_prod = rq->swq_start;
		sge->addr = (dma_addr_t)(qp->rq_hdr_buf_map +
					 sw_prod * qp->rq_hdr_buf_size);
		sge->lkey = 0xFFFFFFFF;
		sge->size = qp->rq_hdr_buf_size;
		वापस qp->rq_hdr_buf + sw_prod * sge->size;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम bnxt_qplib_fill_psn_search(काष्ठा bnxt_qplib_qp *qp,
				       काष्ठा bnxt_qplib_swqe *wqe,
				       काष्ठा bnxt_qplib_swq *swq)
अणु
	काष्ठा sq_psn_search_ext *psns_ext;
	काष्ठा sq_psn_search *psns;
	u32 flg_npsn;
	u32 op_spsn;

	अगर (!swq->psn_search)
		वापस;
	psns = swq->psn_search;
	psns_ext = swq->psn_ext;

	op_spsn = ((swq->start_psn << SQ_PSN_SEARCH_START_PSN_SFT) &
		    SQ_PSN_SEARCH_START_PSN_MASK);
	op_spsn |= ((wqe->type << SQ_PSN_SEARCH_OPCODE_SFT) &
		     SQ_PSN_SEARCH_OPCODE_MASK);
	flg_npsn = ((swq->next_psn << SQ_PSN_SEARCH_NEXT_PSN_SFT) &
		     SQ_PSN_SEARCH_NEXT_PSN_MASK);

	अगर (bnxt_qplib_is_chip_gen_p5(qp->cctx)) अणु
		psns_ext->opcode_start_psn = cpu_to_le32(op_spsn);
		psns_ext->flags_next_psn = cpu_to_le32(flg_npsn);
		psns_ext->start_slot_idx = cpu_to_le16(swq->slot_idx);
	पूर्ण अन्यथा अणु
		psns->opcode_start_psn = cpu_to_le32(op_spsn);
		psns->flags_next_psn = cpu_to_le32(flg_npsn);
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_qplib_put_अंतरभूत(काष्ठा bnxt_qplib_qp *qp,
				 काष्ठा bnxt_qplib_swqe *wqe,
				 u16 *idx)
अणु
	काष्ठा bnxt_qplib_hwq *hwq;
	पूर्णांक len, t_len, offt;
	bool pull_dst = true;
	व्योम *il_dst = शून्य;
	व्योम *il_src = शून्य;
	पूर्णांक t_cplen, cplen;
	पूर्णांक indx;

	hwq = &qp->sq.hwq;
	t_len = 0;
	क्रम (indx = 0; indx < wqe->num_sge; indx++) अणु
		len = wqe->sg_list[indx].size;
		il_src = (व्योम *)wqe->sg_list[indx].addr;
		t_len += len;
		अगर (t_len > qp->max_अंतरभूत_data)
			जाओ bad;
		जबतक (len) अणु
			अगर (pull_dst) अणु
				pull_dst = false;
				il_dst = bnxt_qplib_get_prod_qe(hwq, *idx);
				(*idx)++;
				t_cplen = 0;
				offt = 0;
			पूर्ण
			cplen = min_t(पूर्णांक, len, माप(काष्ठा sq_sge));
			cplen = min_t(पूर्णांक, cplen,
					(माप(काष्ठा sq_sge) - offt));
			स_नकल(il_dst, il_src, cplen);
			t_cplen += cplen;
			il_src += cplen;
			il_dst += cplen;
			offt += cplen;
			len -= cplen;
			अगर (t_cplen == माप(काष्ठा sq_sge))
				pull_dst = true;
		पूर्ण
	पूर्ण

	वापस t_len;
bad:
	वापस -ENOMEM;
पूर्ण

अटल u32 bnxt_qplib_put_sges(काष्ठा bnxt_qplib_hwq *hwq,
			       काष्ठा bnxt_qplib_sge *ssge,
			       u16 nsge, u16 *idx)
अणु
	काष्ठा sq_sge *dsge;
	पूर्णांक indx, len = 0;

	क्रम (indx = 0; indx < nsge; indx++, (*idx)++) अणु
		dsge = bnxt_qplib_get_prod_qe(hwq, *idx);
		dsge->va_or_pa = cpu_to_le64(ssge[indx].addr);
		dsge->l_key = cpu_to_le32(ssge[indx].lkey);
		dsge->size = cpu_to_le32(ssge[indx].size);
		len += ssge[indx].size;
	पूर्ण

	वापस len;
पूर्ण

अटल u16 bnxt_qplib_required_slots(काष्ठा bnxt_qplib_qp *qp,
				     काष्ठा bnxt_qplib_swqe *wqe,
				     u16 *wqe_sz, u16 *qdf, u8 mode)
अणु
	u32 ilsize, bytes;
	u16 nsge;
	u16 slot;

	nsge = wqe->num_sge;
	/* Adding sq_send_hdr is a misnomer, क्रम rq also hdr size is same. */
	bytes = माप(काष्ठा sq_send_hdr) + nsge * माप(काष्ठा sq_sge);
	अगर (wqe->flags & BNXT_QPLIB_SWQE_FLAGS_INLINE) अणु
		ilsize = bnxt_qplib_calc_ilsize(wqe, qp->max_अंतरभूत_data);
		bytes = ALIGN(ilsize, माप(काष्ठा sq_sge));
		bytes += माप(काष्ठा sq_send_hdr);
	पूर्ण

	*qdf =  __xlate_qfd(qp->sq.q_full_delta, bytes);
	slot = bytes >> 4;
	*wqe_sz = slot;
	अगर (mode == BNXT_QPLIB_WQE_MODE_STATIC)
		slot = 8;
	वापस slot;
पूर्ण

अटल व्योम bnxt_qplib_pull_psn_buff(काष्ठा bnxt_qplib_q *sq,
				     काष्ठा bnxt_qplib_swq *swq)
अणु
	काष्ठा bnxt_qplib_hwq *hwq;
	u32 pg_num, pg_indx;
	व्योम *buff;
	u32 tail;

	hwq = &sq->hwq;
	अगर (!hwq->pad_pg)
		वापस;
	tail = swq->slot_idx / sq->dbinfo.max_slot;
	pg_num = (tail + hwq->pad_pgofft) / (PAGE_SIZE / hwq->pad_stride);
	pg_indx = (tail + hwq->pad_pgofft) % (PAGE_SIZE / hwq->pad_stride);
	buff = (व्योम *)(hwq->pad_pg[pg_num] + pg_indx * hwq->pad_stride);
	swq->psn_ext = buff;
	swq->psn_search = buff;
पूर्ण

व्योम bnxt_qplib_post_send_db(काष्ठा bnxt_qplib_qp *qp)
अणु
	काष्ठा bnxt_qplib_q *sq = &qp->sq;

	bnxt_qplib_ring_prod_db(&sq->dbinfo, DBC_DBC_TYPE_SQ);
पूर्ण

पूर्णांक bnxt_qplib_post_send(काष्ठा bnxt_qplib_qp *qp,
			 काष्ठा bnxt_qplib_swqe *wqe)
अणु
	काष्ठा bnxt_qplib_nq_work *nq_work = शून्य;
	पूर्णांक i, rc = 0, data_len = 0, pkt_num = 0;
	काष्ठा bnxt_qplib_q *sq = &qp->sq;
	काष्ठा bnxt_qplib_hwq *hwq;
	काष्ठा bnxt_qplib_swq *swq;
	bool sch_handler = false;
	u16 wqe_sz, qdf = 0;
	व्योम *base_hdr;
	व्योम *ext_hdr;
	__le32 temp32;
	u32 wqe_idx;
	u32 slots;
	u16 idx;

	hwq = &sq->hwq;
	अगर (qp->state != CMDQ_MODIFY_QP_NEW_STATE_RTS &&
	    qp->state != CMDQ_MODIFY_QP_NEW_STATE_ERR) अणु
		dev_err(&hwq->pdev->dev,
			"QPLIB: FP: QP (0x%x) is in the 0x%x state",
			qp->id, qp->state);
		rc = -EINVAL;
		जाओ करोne;
	पूर्ण

	slots = bnxt_qplib_required_slots(qp, wqe, &wqe_sz, &qdf, qp->wqe_mode);
	अगर (bnxt_qplib_queue_full(sq, slots + qdf)) अणु
		dev_err(&hwq->pdev->dev,
			"prod = %#x cons = %#x qdepth = %#x delta = %#x\n",
			hwq->prod, hwq->cons, hwq->depth, sq->q_full_delta);
		rc = -ENOMEM;
		जाओ करोne;
	पूर्ण

	swq = bnxt_qplib_get_swqe(sq, &wqe_idx);
	bnxt_qplib_pull_psn_buff(sq, swq);

	idx = 0;
	swq->slot_idx = hwq->prod;
	swq->slots = slots;
	swq->wr_id = wqe->wr_id;
	swq->type = wqe->type;
	swq->flags = wqe->flags;
	swq->start_psn = sq->psn & BTH_PSN_MASK;
	अगर (qp->sig_type)
		swq->flags |= SQ_SEND_FLAGS_SIGNAL_COMP;

	अगर (qp->state == CMDQ_MODIFY_QP_NEW_STATE_ERR) अणु
		sch_handler = true;
		dev_dbg(&hwq->pdev->dev,
			"%s Error QP. Scheduling for poll_cq\n", __func__);
		जाओ queue_err;
	पूर्ण

	base_hdr = bnxt_qplib_get_prod_qe(hwq, idx++);
	ext_hdr = bnxt_qplib_get_prod_qe(hwq, idx++);
	स_रखो(base_hdr, 0, माप(काष्ठा sq_sge));
	स_रखो(ext_hdr, 0, माप(काष्ठा sq_sge));

	अगर (wqe->flags & BNXT_QPLIB_SWQE_FLAGS_INLINE)
		/* Copy the अंतरभूत data */
		data_len = bnxt_qplib_put_अंतरभूत(qp, wqe, &idx);
	अन्यथा
		data_len = bnxt_qplib_put_sges(hwq, wqe->sg_list, wqe->num_sge,
					       &idx);
	अगर (data_len < 0)
		जाओ queue_err;
	/* Specअगरics */
	चयन (wqe->type) अणु
	हाल BNXT_QPLIB_SWQE_TYPE_SEND:
		अगर (qp->type == CMDQ_CREATE_QP1_TYPE_GSI) अणु
			काष्ठा sq_send_raweth_qp1_hdr *sqe = base_hdr;
			काष्ठा sq_raw_ext_hdr *ext_sqe = ext_hdr;
			/* Assemble info क्रम Raw Ethertype QPs */

			sqe->wqe_type = wqe->type;
			sqe->flags = wqe->flags;
			sqe->wqe_size = wqe_sz;
			sqe->cfa_action = cpu_to_le16(wqe->rawqp1.cfa_action);
			sqe->lflags = cpu_to_le16(wqe->rawqp1.lflags);
			sqe->length = cpu_to_le32(data_len);
			ext_sqe->cfa_meta = cpu_to_le32((wqe->rawqp1.cfa_meta &
				SQ_SEND_RAWETH_QP1_CFA_META_VLAN_VID_MASK) <<
				SQ_SEND_RAWETH_QP1_CFA_META_VLAN_VID_SFT);

			अवरोध;
		पूर्ण
		fallthrough;
	हाल BNXT_QPLIB_SWQE_TYPE_SEND_WITH_IMM:
	हाल BNXT_QPLIB_SWQE_TYPE_SEND_WITH_INV:
	अणु
		काष्ठा sq_ud_ext_hdr *ext_sqe = ext_hdr;
		काष्ठा sq_send_hdr *sqe = base_hdr;

		sqe->wqe_type = wqe->type;
		sqe->flags = wqe->flags;
		sqe->wqe_size = wqe_sz;
		sqe->inv_key_or_imm_data = cpu_to_le32(wqe->send.inv_key);
		अगर (qp->type == CMDQ_CREATE_QP_TYPE_UD ||
		    qp->type == CMDQ_CREATE_QP_TYPE_GSI) अणु
			sqe->q_key = cpu_to_le32(wqe->send.q_key);
			sqe->length = cpu_to_le32(data_len);
			sq->psn = (sq->psn + 1) & BTH_PSN_MASK;
			ext_sqe->dst_qp = cpu_to_le32(wqe->send.dst_qp &
						      SQ_SEND_DST_QP_MASK);
			ext_sqe->avid = cpu_to_le32(wqe->send.avid &
						    SQ_SEND_AVID_MASK);
		पूर्ण अन्यथा अणु
			sqe->length = cpu_to_le32(data_len);
			अगर (qp->mtu)
				pkt_num = (data_len + qp->mtu - 1) / qp->mtu;
			अगर (!pkt_num)
				pkt_num = 1;
			sq->psn = (sq->psn + pkt_num) & BTH_PSN_MASK;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल BNXT_QPLIB_SWQE_TYPE_RDMA_WRITE:
	हाल BNXT_QPLIB_SWQE_TYPE_RDMA_WRITE_WITH_IMM:
	हाल BNXT_QPLIB_SWQE_TYPE_RDMA_READ:
	अणु
		काष्ठा sq_rdma_ext_hdr *ext_sqe = ext_hdr;
		काष्ठा sq_rdma_hdr *sqe = base_hdr;

		sqe->wqe_type = wqe->type;
		sqe->flags = wqe->flags;
		sqe->wqe_size = wqe_sz;
		sqe->imm_data = cpu_to_le32(wqe->rdma.inv_key);
		sqe->length = cpu_to_le32((u32)data_len);
		ext_sqe->remote_va = cpu_to_le64(wqe->rdma.remote_va);
		ext_sqe->remote_key = cpu_to_le32(wqe->rdma.r_key);
		अगर (qp->mtu)
			pkt_num = (data_len + qp->mtu - 1) / qp->mtu;
		अगर (!pkt_num)
			pkt_num = 1;
		sq->psn = (sq->psn + pkt_num) & BTH_PSN_MASK;
		अवरोध;
	पूर्ण
	हाल BNXT_QPLIB_SWQE_TYPE_ATOMIC_CMP_AND_SWP:
	हाल BNXT_QPLIB_SWQE_TYPE_ATOMIC_FETCH_AND_ADD:
	अणु
		काष्ठा sq_atomic_ext_hdr *ext_sqe = ext_hdr;
		काष्ठा sq_atomic_hdr *sqe = base_hdr;

		sqe->wqe_type = wqe->type;
		sqe->flags = wqe->flags;
		sqe->remote_key = cpu_to_le32(wqe->atomic.r_key);
		sqe->remote_va = cpu_to_le64(wqe->atomic.remote_va);
		ext_sqe->swap_data = cpu_to_le64(wqe->atomic.swap_data);
		ext_sqe->cmp_data = cpu_to_le64(wqe->atomic.cmp_data);
		अगर (qp->mtu)
			pkt_num = (data_len + qp->mtu - 1) / qp->mtu;
		अगर (!pkt_num)
			pkt_num = 1;
		sq->psn = (sq->psn + pkt_num) & BTH_PSN_MASK;
		अवरोध;
	पूर्ण
	हाल BNXT_QPLIB_SWQE_TYPE_LOCAL_INV:
	अणु
		काष्ठा sq_localinvalidate *sqe = base_hdr;

		sqe->wqe_type = wqe->type;
		sqe->flags = wqe->flags;
		sqe->inv_l_key = cpu_to_le32(wqe->local_inv.inv_l_key);

		अवरोध;
	पूर्ण
	हाल BNXT_QPLIB_SWQE_TYPE_FAST_REG_MR:
	अणु
		काष्ठा sq_fr_pmr_ext_hdr *ext_sqe = ext_hdr;
		काष्ठा sq_fr_pmr_hdr *sqe = base_hdr;

		sqe->wqe_type = wqe->type;
		sqe->flags = wqe->flags;
		sqe->access_cntl = wqe->frmr.access_cntl |
				   SQ_FR_PMR_ACCESS_CNTL_LOCAL_WRITE;
		sqe->zero_based_page_size_log =
			(wqe->frmr.pg_sz_log & SQ_FR_PMR_PAGE_SIZE_LOG_MASK) <<
			SQ_FR_PMR_PAGE_SIZE_LOG_SFT |
			(wqe->frmr.zero_based ? SQ_FR_PMR_ZERO_BASED : 0);
		sqe->l_key = cpu_to_le32(wqe->frmr.l_key);
		temp32 = cpu_to_le32(wqe->frmr.length);
		स_नकल(sqe->length, &temp32, माप(wqe->frmr.length));
		sqe->numlevels_pbl_page_size_log =
			((wqe->frmr.pbl_pg_sz_log <<
					SQ_FR_PMR_PBL_PAGE_SIZE_LOG_SFT) &
					SQ_FR_PMR_PBL_PAGE_SIZE_LOG_MASK) |
			((wqe->frmr.levels << SQ_FR_PMR_NUMLEVELS_SFT) &
					SQ_FR_PMR_NUMLEVELS_MASK);

		क्रम (i = 0; i < wqe->frmr.page_list_len; i++)
			wqe->frmr.pbl_ptr[i] = cpu_to_le64(
						wqe->frmr.page_list[i] |
						PTU_PTE_VALID);
		ext_sqe->pblptr = cpu_to_le64(wqe->frmr.pbl_dma_ptr);
		ext_sqe->va = cpu_to_le64(wqe->frmr.va);

		अवरोध;
	पूर्ण
	हाल BNXT_QPLIB_SWQE_TYPE_BIND_MW:
	अणु
		काष्ठा sq_bind_ext_hdr *ext_sqe = ext_hdr;
		काष्ठा sq_bind_hdr *sqe = base_hdr;

		sqe->wqe_type = wqe->type;
		sqe->flags = wqe->flags;
		sqe->access_cntl = wqe->bind.access_cntl;
		sqe->mw_type_zero_based = wqe->bind.mw_type |
			(wqe->bind.zero_based ? SQ_BIND_ZERO_BASED : 0);
		sqe->parent_l_key = cpu_to_le32(wqe->bind.parent_l_key);
		sqe->l_key = cpu_to_le32(wqe->bind.r_key);
		ext_sqe->va = cpu_to_le64(wqe->bind.va);
		ext_sqe->length_lo = cpu_to_le32(wqe->bind.length);
		अवरोध;
	पूर्ण
	शेष:
		/* Bad wqe, वापस error */
		rc = -EINVAL;
		जाओ करोne;
	पूर्ण
	swq->next_psn = sq->psn & BTH_PSN_MASK;
	bnxt_qplib_fill_psn_search(qp, wqe, swq);
queue_err:
	bnxt_qplib_swq_mod_start(sq, wqe_idx);
	bnxt_qplib_hwq_incr_prod(hwq, swq->slots);
	qp->wqe_cnt++;
करोne:
	अगर (sch_handler) अणु
		nq_work = kzalloc(माप(*nq_work), GFP_ATOMIC);
		अगर (nq_work) अणु
			nq_work->cq = qp->scq;
			nq_work->nq = qp->scq->nq;
			INIT_WORK(&nq_work->work, bnxt_qpn_cqn_sched_task);
			queue_work(qp->scq->nq->cqn_wq, &nq_work->work);
		पूर्ण अन्यथा अणु
			dev_err(&hwq->pdev->dev,
				"FP: Failed to allocate SQ nq_work!\n");
			rc = -ENOMEM;
		पूर्ण
	पूर्ण
	वापस rc;
पूर्ण

व्योम bnxt_qplib_post_recv_db(काष्ठा bnxt_qplib_qp *qp)
अणु
	काष्ठा bnxt_qplib_q *rq = &qp->rq;

	bnxt_qplib_ring_prod_db(&rq->dbinfo, DBC_DBC_TYPE_RQ);
पूर्ण

पूर्णांक bnxt_qplib_post_recv(काष्ठा bnxt_qplib_qp *qp,
			 काष्ठा bnxt_qplib_swqe *wqe)
अणु
	काष्ठा bnxt_qplib_nq_work *nq_work = शून्य;
	काष्ठा bnxt_qplib_q *rq = &qp->rq;
	काष्ठा rq_wqe_hdr *base_hdr;
	काष्ठा rq_ext_hdr *ext_hdr;
	काष्ठा bnxt_qplib_hwq *hwq;
	काष्ठा bnxt_qplib_swq *swq;
	bool sch_handler = false;
	u16 wqe_sz, idx;
	u32 wqe_idx;
	पूर्णांक rc = 0;

	hwq = &rq->hwq;
	अगर (qp->state == CMDQ_MODIFY_QP_NEW_STATE_RESET) अणु
		dev_err(&hwq->pdev->dev,
			"QPLIB: FP: QP (0x%x) is in the 0x%x state",
			qp->id, qp->state);
		rc = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (bnxt_qplib_queue_full(rq, rq->dbinfo.max_slot)) अणु
		dev_err(&hwq->pdev->dev,
			"FP: QP (0x%x) RQ is full!\n", qp->id);
		rc = -EINVAL;
		जाओ करोne;
	पूर्ण

	swq = bnxt_qplib_get_swqe(rq, &wqe_idx);
	swq->wr_id = wqe->wr_id;
	swq->slots = rq->dbinfo.max_slot;

	अगर (qp->state == CMDQ_MODIFY_QP_NEW_STATE_ERR) अणु
		sch_handler = true;
		dev_dbg(&hwq->pdev->dev,
			"%s: Error QP. Scheduling for poll_cq\n", __func__);
		जाओ queue_err;
	पूर्ण

	idx = 0;
	base_hdr = bnxt_qplib_get_prod_qe(hwq, idx++);
	ext_hdr = bnxt_qplib_get_prod_qe(hwq, idx++);
	स_रखो(base_hdr, 0, माप(काष्ठा sq_sge));
	स_रखो(ext_hdr, 0, माप(काष्ठा sq_sge));
	wqe_sz = (माप(काष्ठा rq_wqe_hdr) +
	wqe->num_sge * माप(काष्ठा sq_sge)) >> 4;
	bnxt_qplib_put_sges(hwq, wqe->sg_list, wqe->num_sge, &idx);
	अगर (!wqe->num_sge) अणु
		काष्ठा sq_sge *sge;

		sge = bnxt_qplib_get_prod_qe(hwq, idx++);
		sge->size = 0;
		wqe_sz++;
	पूर्ण
	base_hdr->wqe_type = wqe->type;
	base_hdr->flags = wqe->flags;
	base_hdr->wqe_size = wqe_sz;
	base_hdr->wr_id[0] = cpu_to_le32(wqe_idx);
queue_err:
	bnxt_qplib_swq_mod_start(rq, wqe_idx);
	bnxt_qplib_hwq_incr_prod(hwq, swq->slots);
करोne:
	अगर (sch_handler) अणु
		nq_work = kzalloc(माप(*nq_work), GFP_ATOMIC);
		अगर (nq_work) अणु
			nq_work->cq = qp->rcq;
			nq_work->nq = qp->rcq->nq;
			INIT_WORK(&nq_work->work, bnxt_qpn_cqn_sched_task);
			queue_work(qp->rcq->nq->cqn_wq, &nq_work->work);
		पूर्ण अन्यथा अणु
			dev_err(&hwq->pdev->dev,
				"FP: Failed to allocate RQ nq_work!\n");
			rc = -ENOMEM;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

/* CQ */
पूर्णांक bnxt_qplib_create_cq(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_cq *cq)
अणु
	काष्ठा bnxt_qplib_rcfw *rcfw = res->rcfw;
	काष्ठा bnxt_qplib_hwq_attr hwq_attr = अणुपूर्ण;
	काष्ठा creq_create_cq_resp resp;
	काष्ठा bnxt_qplib_pbl *pbl;
	काष्ठा cmdq_create_cq req;
	u16 cmd_flags = 0;
	u32 pg_sz_lvl;
	पूर्णांक rc;

	hwq_attr.res = res;
	hwq_attr.depth = cq->max_wqe;
	hwq_attr.stride = माप(काष्ठा cq_base);
	hwq_attr.type = HWQ_TYPE_QUEUE;
	hwq_attr.sginfo = &cq->sg_info;
	rc = bnxt_qplib_alloc_init_hwq(&cq->hwq, &hwq_attr);
	अगर (rc)
		जाओ निकास;

	RCFW_CMD_PREP(req, CREATE_CQ, cmd_flags);

	अगर (!cq->dpi) अणु
		dev_err(&rcfw->pdev->dev,
			"FP: CREATE_CQ failed due to NULL DPI\n");
		वापस -EINVAL;
	पूर्ण
	req.dpi = cpu_to_le32(cq->dpi->dpi);
	req.cq_handle = cpu_to_le64(cq->cq_handle);
	req.cq_size = cpu_to_le32(cq->hwq.max_elements);
	pbl = &cq->hwq.pbl[PBL_LVL_0];
	pg_sz_lvl = (bnxt_qplib_base_pg_size(&cq->hwq) <<
		     CMDQ_CREATE_CQ_PG_SIZE_SFT);
	pg_sz_lvl |= (cq->hwq.level & CMDQ_CREATE_CQ_LVL_MASK);
	req.pg_size_lvl = cpu_to_le32(pg_sz_lvl);
	req.pbl = cpu_to_le64(pbl->pg_map_arr[0]);
	req.cq_fco_cnq_id = cpu_to_le32(
			(cq->cnq_hw_ring_id & CMDQ_CREATE_CQ_CNQ_ID_MASK) <<
			 CMDQ_CREATE_CQ_CNQ_ID_SFT);

	rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req,
					  (व्योम *)&resp, शून्य, 0);
	अगर (rc)
		जाओ fail;

	cq->id = le32_to_cpu(resp.xid);
	cq->period = BNXT_QPLIB_QUEUE_START_PERIOD;
	init_रुकोqueue_head(&cq->रुकोq);
	INIT_LIST_HEAD(&cq->sqf_head);
	INIT_LIST_HEAD(&cq->rqf_head);
	spin_lock_init(&cq->compl_lock);
	spin_lock_init(&cq->flush_lock);

	cq->dbinfo.hwq = &cq->hwq;
	cq->dbinfo.xid = cq->id;
	cq->dbinfo.db = cq->dpi->dbr;
	cq->dbinfo.priv_db = res->dpi_tbl.dbr_bar_reg_iomem;

	bnxt_qplib_armen_db(&cq->dbinfo, DBC_DBC_TYPE_CQ_ARMENA);

	वापस 0;

fail:
	bnxt_qplib_मुक्त_hwq(res, &cq->hwq);
निकास:
	वापस rc;
पूर्ण

पूर्णांक bnxt_qplib_destroy_cq(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_cq *cq)
अणु
	काष्ठा bnxt_qplib_rcfw *rcfw = res->rcfw;
	काष्ठा cmdq_destroy_cq req;
	काष्ठा creq_destroy_cq_resp resp;
	u16 total_cnq_events;
	u16 cmd_flags = 0;
	पूर्णांक rc;

	RCFW_CMD_PREP(req, DESTROY_CQ, cmd_flags);

	req.cq_cid = cpu_to_le32(cq->id);
	rc = bnxt_qplib_rcfw_send_message(rcfw, (व्योम *)&req,
					  (व्योम *)&resp, शून्य, 0);
	अगर (rc)
		वापस rc;
	total_cnq_events = le16_to_cpu(resp.total_cnq_events);
	__रुको_क्रम_all_nqes(cq, total_cnq_events);
	bnxt_qplib_मुक्त_hwq(res, &cq->hwq);
	वापस 0;
पूर्ण

अटल पूर्णांक __flush_sq(काष्ठा bnxt_qplib_q *sq, काष्ठा bnxt_qplib_qp *qp,
		      काष्ठा bnxt_qplib_cqe **pcqe, पूर्णांक *budget)
अणु
	काष्ठा bnxt_qplib_cqe *cqe;
	u32 start, last;
	पूर्णांक rc = 0;

	/* Now complete all outstanding SQEs with FLUSHED_ERR */
	start = sq->swq_start;
	cqe = *pcqe;
	जबतक (*budget) अणु
		last = sq->swq_last;
		अगर (start == last)
			अवरोध;
		/* Skip the FENCE WQE completions */
		अगर (sq->swq[last].wr_id == BNXT_QPLIB_FENCE_WRID) अणु
			bnxt_qplib_cancel_phantom_processing(qp);
			जाओ skip_compl;
		पूर्ण
		स_रखो(cqe, 0, माप(*cqe));
		cqe->status = CQ_REQ_STATUS_WORK_REQUEST_FLUSHED_ERR;
		cqe->opcode = CQ_BASE_CQE_TYPE_REQ;
		cqe->qp_handle = (u64)(अचिन्हित दीर्घ)qp;
		cqe->wr_id = sq->swq[last].wr_id;
		cqe->src_qp = qp->id;
		cqe->type = sq->swq[last].type;
		cqe++;
		(*budget)--;
skip_compl:
		bnxt_qplib_hwq_incr_cons(&sq->hwq, sq->swq[last].slots);
		sq->swq_last = sq->swq[last].next_idx;
	पूर्ण
	*pcqe = cqe;
	अगर (!(*budget) && sq->swq_last != start)
		/* Out of budget */
		rc = -EAGAIN;

	वापस rc;
पूर्ण

अटल पूर्णांक __flush_rq(काष्ठा bnxt_qplib_q *rq, काष्ठा bnxt_qplib_qp *qp,
		      काष्ठा bnxt_qplib_cqe **pcqe, पूर्णांक *budget)
अणु
	काष्ठा bnxt_qplib_cqe *cqe;
	u32 start, last;
	पूर्णांक opcode = 0;
	पूर्णांक rc = 0;

	चयन (qp->type) अणु
	हाल CMDQ_CREATE_QP1_TYPE_GSI:
		opcode = CQ_BASE_CQE_TYPE_RES_RAWETH_QP1;
		अवरोध;
	हाल CMDQ_CREATE_QP_TYPE_RC:
		opcode = CQ_BASE_CQE_TYPE_RES_RC;
		अवरोध;
	हाल CMDQ_CREATE_QP_TYPE_UD:
	हाल CMDQ_CREATE_QP_TYPE_GSI:
		opcode = CQ_BASE_CQE_TYPE_RES_UD;
		अवरोध;
	पूर्ण

	/* Flush the rest of the RQ */
	start = rq->swq_start;
	cqe = *pcqe;
	जबतक (*budget) अणु
		last = rq->swq_last;
		अगर (last == start)
			अवरोध;
		स_रखो(cqe, 0, माप(*cqe));
		cqe->status =
		    CQ_RES_RC_STATUS_WORK_REQUEST_FLUSHED_ERR;
		cqe->opcode = opcode;
		cqe->qp_handle = (अचिन्हित दीर्घ)qp;
		cqe->wr_id = rq->swq[last].wr_id;
		cqe++;
		(*budget)--;
		bnxt_qplib_hwq_incr_cons(&rq->hwq, rq->swq[last].slots);
		rq->swq_last = rq->swq[last].next_idx;
	पूर्ण
	*pcqe = cqe;
	अगर (!*budget && rq->swq_last != start)
		/* Out of budget */
		rc = -EAGAIN;

	वापस rc;
पूर्ण

व्योम bnxt_qplib_mark_qp_error(व्योम *qp_handle)
अणु
	काष्ठा bnxt_qplib_qp *qp = qp_handle;

	अगर (!qp)
		वापस;

	/* Must block new posting of SQ and RQ */
	qp->state = CMDQ_MODIFY_QP_NEW_STATE_ERR;
	bnxt_qplib_cancel_phantom_processing(qp);
पूर्ण

/* Note: SQE is valid from sw_sq_cons up to cqe_sq_cons (exclusive)
 *       CQE is track from sw_cq_cons to max_element but valid only अगर VALID=1
 */
अटल पूर्णांक करो_wa9060(काष्ठा bnxt_qplib_qp *qp, काष्ठा bnxt_qplib_cq *cq,
		     u32 cq_cons, u32 swq_last, u32 cqe_sq_cons)
अणु
	u32 peek_sw_cq_cons, peek_raw_cq_cons, peek_sq_cons_idx;
	काष्ठा bnxt_qplib_q *sq = &qp->sq;
	काष्ठा cq_req *peek_req_hwcqe;
	काष्ठा bnxt_qplib_qp *peek_qp;
	काष्ठा bnxt_qplib_q *peek_sq;
	काष्ठा bnxt_qplib_swq *swq;
	काष्ठा cq_base *peek_hwcqe;
	पूर्णांक i, rc = 0;

	/* Normal mode */
	/* Check क्रम the psn_search marking beक्रमe completing */
	swq = &sq->swq[swq_last];
	अगर (swq->psn_search &&
	    le32_to_cpu(swq->psn_search->flags_next_psn) & 0x80000000) अणु
		/* Unmark */
		swq->psn_search->flags_next_psn = cpu_to_le32
			(le32_to_cpu(swq->psn_search->flags_next_psn)
				     & ~0x80000000);
		dev_dbg(&cq->hwq.pdev->dev,
			"FP: Process Req cq_cons=0x%x qp=0x%x sq cons sw=0x%x cqe=0x%x marked!\n",
			cq_cons, qp->id, swq_last, cqe_sq_cons);
		sq->condition = true;
		sq->send_phantom = true;

		/* TODO: Only ARM अगर the previous SQE is ARMALL */
		bnxt_qplib_ring_db(&cq->dbinfo, DBC_DBC_TYPE_CQ_ARMALL);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण
	अगर (sq->condition) अणु
		/* Peek at the completions */
		peek_raw_cq_cons = cq->hwq.cons;
		peek_sw_cq_cons = cq_cons;
		i = cq->hwq.max_elements;
		जबतक (i--) अणु
			peek_sw_cq_cons = HWQ_CMP((peek_sw_cq_cons), &cq->hwq);
			peek_hwcqe = bnxt_qplib_get_qe(&cq->hwq,
						       peek_sw_cq_cons, शून्य);
			/* If the next hwcqe is VALID */
			अगर (CQE_CMP_VALID(peek_hwcqe, peek_raw_cq_cons,
					  cq->hwq.max_elements)) अणु
			/*
			 * The valid test of the entry must be करोne first beक्रमe
			 * पढ़ोing any further.
			 */
				dma_rmb();
				/* If the next hwcqe is a REQ */
				अगर ((peek_hwcqe->cqe_type_toggle &
				    CQ_BASE_CQE_TYPE_MASK) ==
				    CQ_BASE_CQE_TYPE_REQ) अणु
					peek_req_hwcqe = (काष्ठा cq_req *)
							 peek_hwcqe;
					peek_qp = (काष्ठा bnxt_qplib_qp *)
						((अचिन्हित दीर्घ)
						 le64_to_cpu
						 (peek_req_hwcqe->qp_handle));
					peek_sq = &peek_qp->sq;
					peek_sq_cons_idx =
						((le16_to_cpu(
						  peek_req_hwcqe->sq_cons_idx)
						  - 1) % sq->max_wqe);
					/* If the hwcqe's sq's wr_id matches */
					अगर (peek_sq == sq &&
					    sq->swq[peek_sq_cons_idx].wr_id ==
					    BNXT_QPLIB_FENCE_WRID) अणु
						/*
						 *  Unअवरोध only अगर the phantom
						 *  comes back
						 */
						dev_dbg(&cq->hwq.pdev->dev,
							"FP: Got Phantom CQE\n");
						sq->condition = false;
						sq->single = true;
						rc = 0;
						जाओ out;
					पूर्ण
				पूर्ण
				/* Valid but not the phantom, so keep looping */
			पूर्ण अन्यथा अणु
				/* Not valid yet, just निकास and रुको */
				rc = -EINVAL;
				जाओ out;
			पूर्ण
			peek_sw_cq_cons++;
			peek_raw_cq_cons++;
		पूर्ण
		dev_err(&cq->hwq.pdev->dev,
			"Should not have come here! cq_cons=0x%x qp=0x%x sq cons sw=0x%x hw=0x%x\n",
			cq_cons, qp->id, swq_last, cqe_sq_cons);
		rc = -EINVAL;
	पूर्ण
out:
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_qplib_cq_process_req(काष्ठा bnxt_qplib_cq *cq,
				     काष्ठा cq_req *hwcqe,
				     काष्ठा bnxt_qplib_cqe **pcqe, पूर्णांक *budget,
				     u32 cq_cons, काष्ठा bnxt_qplib_qp **lib_qp)
अणु
	काष्ठा bnxt_qplib_swq *swq;
	काष्ठा bnxt_qplib_cqe *cqe;
	काष्ठा bnxt_qplib_qp *qp;
	काष्ठा bnxt_qplib_q *sq;
	u32 cqe_sq_cons;
	पूर्णांक rc = 0;

	qp = (काष्ठा bnxt_qplib_qp *)((अचिन्हित दीर्घ)
				      le64_to_cpu(hwcqe->qp_handle));
	अगर (!qp) अणु
		dev_err(&cq->hwq.pdev->dev,
			"FP: Process Req qp is NULL\n");
		वापस -EINVAL;
	पूर्ण
	sq = &qp->sq;

	cqe_sq_cons = le16_to_cpu(hwcqe->sq_cons_idx) % sq->max_wqe;
	अगर (qp->sq.flushed) अणु
		dev_dbg(&cq->hwq.pdev->dev,
			"%s: QP in Flush QP = %p\n", __func__, qp);
		जाओ करोne;
	पूर्ण
	/* Require to walk the sq's swq to fabricate CQEs क्रम all previously
	 * संकेतed SWQEs due to CQE aggregation from the current sq cons
	 * to the cqe_sq_cons
	 */
	cqe = *pcqe;
	जबतक (*budget) अणु
		अगर (sq->swq_last == cqe_sq_cons)
			/* Done */
			अवरोध;

		swq = &sq->swq[sq->swq_last];
		स_रखो(cqe, 0, माप(*cqe));
		cqe->opcode = CQ_BASE_CQE_TYPE_REQ;
		cqe->qp_handle = (u64)(अचिन्हित दीर्घ)qp;
		cqe->src_qp = qp->id;
		cqe->wr_id = swq->wr_id;
		अगर (cqe->wr_id == BNXT_QPLIB_FENCE_WRID)
			जाओ skip;
		cqe->type = swq->type;

		/* For the last CQE, check क्रम status.  For errors, regardless
		 * of the request being संकेतed or not, it must complete with
		 * the hwcqe error status
		 */
		अगर (swq->next_idx == cqe_sq_cons &&
		    hwcqe->status != CQ_REQ_STATUS_OK) अणु
			cqe->status = hwcqe->status;
			dev_err(&cq->hwq.pdev->dev,
				"FP: CQ Processed Req wr_id[%d] = 0x%llx with status 0x%x\n",
				sq->swq_last, cqe->wr_id, cqe->status);
			cqe++;
			(*budget)--;
			bnxt_qplib_mark_qp_error(qp);
			/* Add qp to flush list of the CQ */
			bnxt_qplib_add_flush_qp(qp);
		पूर्ण अन्यथा अणु
			/* Beक्रमe we complete, करो WA 9060 */
			अगर (करो_wa9060(qp, cq, cq_cons, sq->swq_last,
				      cqe_sq_cons)) अणु
				*lib_qp = qp;
				जाओ out;
			पूर्ण
			अगर (swq->flags & SQ_SEND_FLAGS_SIGNAL_COMP) अणु
				cqe->status = CQ_REQ_STATUS_OK;
				cqe++;
				(*budget)--;
			पूर्ण
		पूर्ण
skip:
		bnxt_qplib_hwq_incr_cons(&sq->hwq, swq->slots);
		sq->swq_last = swq->next_idx;
		अगर (sq->single)
			अवरोध;
	पूर्ण
out:
	*pcqe = cqe;
	अगर (sq->swq_last != cqe_sq_cons) अणु
		/* Out of budget */
		rc = -EAGAIN;
		जाओ करोne;
	पूर्ण
	/*
	 * Back to normal completion mode only after it has completed all of
	 * the WC क्रम this CQE
	 */
	sq->single = false;
करोne:
	वापस rc;
पूर्ण

अटल व्योम bnxt_qplib_release_srqe(काष्ठा bnxt_qplib_srq *srq, u32 tag)
अणु
	spin_lock(&srq->hwq.lock);
	srq->swq[srq->last_idx].next_idx = (पूर्णांक)tag;
	srq->last_idx = (पूर्णांक)tag;
	srq->swq[srq->last_idx].next_idx = -1;
	srq->hwq.cons++; /* Support क्रम SRQE counter */
	spin_unlock(&srq->hwq.lock);
पूर्ण

अटल पूर्णांक bnxt_qplib_cq_process_res_rc(काष्ठा bnxt_qplib_cq *cq,
					काष्ठा cq_res_rc *hwcqe,
					काष्ठा bnxt_qplib_cqe **pcqe,
					पूर्णांक *budget)
अणु
	काष्ठा bnxt_qplib_srq *srq;
	काष्ठा bnxt_qplib_cqe *cqe;
	काष्ठा bnxt_qplib_qp *qp;
	काष्ठा bnxt_qplib_q *rq;
	u32 wr_id_idx;
	पूर्णांक rc = 0;

	qp = (काष्ठा bnxt_qplib_qp *)((अचिन्हित दीर्घ)
				      le64_to_cpu(hwcqe->qp_handle));
	अगर (!qp) अणु
		dev_err(&cq->hwq.pdev->dev, "process_cq RC qp is NULL\n");
		वापस -EINVAL;
	पूर्ण
	अगर (qp->rq.flushed) अणु
		dev_dbg(&cq->hwq.pdev->dev,
			"%s: QP in Flush QP = %p\n", __func__, qp);
		जाओ करोne;
	पूर्ण

	cqe = *pcqe;
	cqe->opcode = hwcqe->cqe_type_toggle & CQ_BASE_CQE_TYPE_MASK;
	cqe->length = le32_to_cpu(hwcqe->length);
	cqe->invrkey = le32_to_cpu(hwcqe->imm_data_or_inv_r_key);
	cqe->mr_handle = le64_to_cpu(hwcqe->mr_handle);
	cqe->flags = le16_to_cpu(hwcqe->flags);
	cqe->status = hwcqe->status;
	cqe->qp_handle = (u64)(अचिन्हित दीर्घ)qp;

	wr_id_idx = le32_to_cpu(hwcqe->srq_or_rq_wr_id) &
				CQ_RES_RC_SRQ_OR_RQ_WR_ID_MASK;
	अगर (cqe->flags & CQ_RES_RC_FLAGS_SRQ_SRQ) अणु
		srq = qp->srq;
		अगर (!srq)
			वापस -EINVAL;
		अगर (wr_id_idx >= srq->hwq.max_elements) अणु
			dev_err(&cq->hwq.pdev->dev,
				"FP: CQ Process RC wr_id idx 0x%x exceeded SRQ max 0x%x\n",
				wr_id_idx, srq->hwq.max_elements);
			वापस -EINVAL;
		पूर्ण
		cqe->wr_id = srq->swq[wr_id_idx].wr_id;
		bnxt_qplib_release_srqe(srq, wr_id_idx);
		cqe++;
		(*budget)--;
		*pcqe = cqe;
	पूर्ण अन्यथा अणु
		काष्ठा bnxt_qplib_swq *swq;

		rq = &qp->rq;
		अगर (wr_id_idx > (rq->max_wqe - 1)) अणु
			dev_err(&cq->hwq.pdev->dev,
				"FP: CQ Process RC wr_id idx 0x%x exceeded RQ max 0x%x\n",
				wr_id_idx, rq->max_wqe);
			वापस -EINVAL;
		पूर्ण
		अगर (wr_id_idx != rq->swq_last)
			वापस -EINVAL;
		swq = &rq->swq[rq->swq_last];
		cqe->wr_id = swq->wr_id;
		cqe++;
		(*budget)--;
		bnxt_qplib_hwq_incr_cons(&rq->hwq, swq->slots);
		rq->swq_last = swq->next_idx;
		*pcqe = cqe;

		अगर (hwcqe->status != CQ_RES_RC_STATUS_OK) अणु
			qp->state = CMDQ_MODIFY_QP_NEW_STATE_ERR;
			/* Add qp to flush list of the CQ */
			bnxt_qplib_add_flush_qp(qp);
		पूर्ण
	पूर्ण

करोne:
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_qplib_cq_process_res_ud(काष्ठा bnxt_qplib_cq *cq,
					काष्ठा cq_res_ud *hwcqe,
					काष्ठा bnxt_qplib_cqe **pcqe,
					पूर्णांक *budget)
अणु
	काष्ठा bnxt_qplib_srq *srq;
	काष्ठा bnxt_qplib_cqe *cqe;
	काष्ठा bnxt_qplib_qp *qp;
	काष्ठा bnxt_qplib_q *rq;
	u32 wr_id_idx;
	पूर्णांक rc = 0;

	qp = (काष्ठा bnxt_qplib_qp *)((अचिन्हित दीर्घ)
				      le64_to_cpu(hwcqe->qp_handle));
	अगर (!qp) अणु
		dev_err(&cq->hwq.pdev->dev, "process_cq UD qp is NULL\n");
		वापस -EINVAL;
	पूर्ण
	अगर (qp->rq.flushed) अणु
		dev_dbg(&cq->hwq.pdev->dev,
			"%s: QP in Flush QP = %p\n", __func__, qp);
		जाओ करोne;
	पूर्ण
	cqe = *pcqe;
	cqe->opcode = hwcqe->cqe_type_toggle & CQ_BASE_CQE_TYPE_MASK;
	cqe->length = le16_to_cpu(hwcqe->length) & CQ_RES_UD_LENGTH_MASK;
	cqe->cfa_meta = le16_to_cpu(hwcqe->cfa_metadata);
	cqe->invrkey = le32_to_cpu(hwcqe->imm_data);
	cqe->flags = le16_to_cpu(hwcqe->flags);
	cqe->status = hwcqe->status;
	cqe->qp_handle = (u64)(अचिन्हित दीर्घ)qp;
	/*FIXME: Endianness fix needed क्रम smace */
	स_नकल(cqe->smac, hwcqe->src_mac, ETH_ALEN);
	wr_id_idx = le32_to_cpu(hwcqe->src_qp_high_srq_or_rq_wr_id)
				& CQ_RES_UD_SRQ_OR_RQ_WR_ID_MASK;
	cqe->src_qp = le16_to_cpu(hwcqe->src_qp_low) |
				  ((le32_to_cpu(
				  hwcqe->src_qp_high_srq_or_rq_wr_id) &
				 CQ_RES_UD_SRC_QP_HIGH_MASK) >> 8);

	अगर (cqe->flags & CQ_RES_RC_FLAGS_SRQ_SRQ) अणु
		srq = qp->srq;
		अगर (!srq)
			वापस -EINVAL;

		अगर (wr_id_idx >= srq->hwq.max_elements) अणु
			dev_err(&cq->hwq.pdev->dev,
				"FP: CQ Process UD wr_id idx 0x%x exceeded SRQ max 0x%x\n",
				wr_id_idx, srq->hwq.max_elements);
			वापस -EINVAL;
		पूर्ण
		cqe->wr_id = srq->swq[wr_id_idx].wr_id;
		bnxt_qplib_release_srqe(srq, wr_id_idx);
		cqe++;
		(*budget)--;
		*pcqe = cqe;
	पूर्ण अन्यथा अणु
		काष्ठा bnxt_qplib_swq *swq;

		rq = &qp->rq;
		अगर (wr_id_idx > (rq->max_wqe - 1)) अणु
			dev_err(&cq->hwq.pdev->dev,
				"FP: CQ Process UD wr_id idx 0x%x exceeded RQ max 0x%x\n",
				wr_id_idx, rq->max_wqe);
			वापस -EINVAL;
		पूर्ण

		अगर (rq->swq_last != wr_id_idx)
			वापस -EINVAL;
		swq = &rq->swq[rq->swq_last];
		cqe->wr_id = swq->wr_id;
		cqe++;
		(*budget)--;
		bnxt_qplib_hwq_incr_cons(&rq->hwq, swq->slots);
		rq->swq_last = swq->next_idx;
		*pcqe = cqe;

		अगर (hwcqe->status != CQ_RES_RC_STATUS_OK) अणु
			qp->state = CMDQ_MODIFY_QP_NEW_STATE_ERR;
			/* Add qp to flush list of the CQ */
			bnxt_qplib_add_flush_qp(qp);
		पूर्ण
	पूर्ण
करोne:
	वापस rc;
पूर्ण

bool bnxt_qplib_is_cq_empty(काष्ठा bnxt_qplib_cq *cq)
अणु
	काष्ठा cq_base *hw_cqe;
	u32 sw_cons, raw_cons;
	bool rc = true;

	raw_cons = cq->hwq.cons;
	sw_cons = HWQ_CMP(raw_cons, &cq->hwq);
	hw_cqe = bnxt_qplib_get_qe(&cq->hwq, sw_cons, शून्य);
	 /* Check क्रम Valid bit. If the CQE is valid, वापस false */
	rc = !CQE_CMP_VALID(hw_cqe, raw_cons, cq->hwq.max_elements);
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_qplib_cq_process_res_raweth_qp1(काष्ठा bnxt_qplib_cq *cq,
						काष्ठा cq_res_raweth_qp1 *hwcqe,
						काष्ठा bnxt_qplib_cqe **pcqe,
						पूर्णांक *budget)
अणु
	काष्ठा bnxt_qplib_qp *qp;
	काष्ठा bnxt_qplib_q *rq;
	काष्ठा bnxt_qplib_srq *srq;
	काष्ठा bnxt_qplib_cqe *cqe;
	u32 wr_id_idx;
	पूर्णांक rc = 0;

	qp = (काष्ठा bnxt_qplib_qp *)((अचिन्हित दीर्घ)
				      le64_to_cpu(hwcqe->qp_handle));
	अगर (!qp) अणु
		dev_err(&cq->hwq.pdev->dev, "process_cq Raw/QP1 qp is NULL\n");
		वापस -EINVAL;
	पूर्ण
	अगर (qp->rq.flushed) अणु
		dev_dbg(&cq->hwq.pdev->dev,
			"%s: QP in Flush QP = %p\n", __func__, qp);
		जाओ करोne;
	पूर्ण
	cqe = *pcqe;
	cqe->opcode = hwcqe->cqe_type_toggle & CQ_BASE_CQE_TYPE_MASK;
	cqe->flags = le16_to_cpu(hwcqe->flags);
	cqe->qp_handle = (u64)(अचिन्हित दीर्घ)qp;

	wr_id_idx =
		le32_to_cpu(hwcqe->raweth_qp1_payload_offset_srq_or_rq_wr_id)
				& CQ_RES_RAWETH_QP1_SRQ_OR_RQ_WR_ID_MASK;
	cqe->src_qp = qp->id;
	अगर (qp->id == 1 && !cqe->length) अणु
		/* Add workaround क्रम the length misdetection */
		cqe->length = 296;
	पूर्ण अन्यथा अणु
		cqe->length = le16_to_cpu(hwcqe->length);
	पूर्ण
	cqe->pkey_index = qp->pkey_index;
	स_नकल(cqe->smac, qp->smac, 6);

	cqe->raweth_qp1_flags = le16_to_cpu(hwcqe->raweth_qp1_flags);
	cqe->raweth_qp1_flags2 = le32_to_cpu(hwcqe->raweth_qp1_flags2);
	cqe->raweth_qp1_metadata = le32_to_cpu(hwcqe->raweth_qp1_metadata);

	अगर (cqe->flags & CQ_RES_RAWETH_QP1_FLAGS_SRQ_SRQ) अणु
		srq = qp->srq;
		अगर (!srq) अणु
			dev_err(&cq->hwq.pdev->dev,
				"FP: SRQ used but not defined??\n");
			वापस -EINVAL;
		पूर्ण
		अगर (wr_id_idx >= srq->hwq.max_elements) अणु
			dev_err(&cq->hwq.pdev->dev,
				"FP: CQ Process Raw/QP1 wr_id idx 0x%x exceeded SRQ max 0x%x\n",
				wr_id_idx, srq->hwq.max_elements);
			वापस -EINVAL;
		पूर्ण
		cqe->wr_id = srq->swq[wr_id_idx].wr_id;
		bnxt_qplib_release_srqe(srq, wr_id_idx);
		cqe++;
		(*budget)--;
		*pcqe = cqe;
	पूर्ण अन्यथा अणु
		काष्ठा bnxt_qplib_swq *swq;

		rq = &qp->rq;
		अगर (wr_id_idx > (rq->max_wqe - 1)) अणु
			dev_err(&cq->hwq.pdev->dev,
				"FP: CQ Process Raw/QP1 RQ wr_id idx 0x%x exceeded RQ max 0x%x\n",
				wr_id_idx, rq->max_wqe);
			वापस -EINVAL;
		पूर्ण
		अगर (rq->swq_last != wr_id_idx)
			वापस -EINVAL;
		swq = &rq->swq[rq->swq_last];
		cqe->wr_id = swq->wr_id;
		cqe++;
		(*budget)--;
		bnxt_qplib_hwq_incr_cons(&rq->hwq, swq->slots);
		rq->swq_last = swq->next_idx;
		*pcqe = cqe;

		अगर (hwcqe->status != CQ_RES_RC_STATUS_OK) अणु
			qp->state = CMDQ_MODIFY_QP_NEW_STATE_ERR;
			/* Add qp to flush list of the CQ */
			bnxt_qplib_add_flush_qp(qp);
		पूर्ण
	पूर्ण

करोne:
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_qplib_cq_process_terminal(काष्ठा bnxt_qplib_cq *cq,
					  काष्ठा cq_terminal *hwcqe,
					  काष्ठा bnxt_qplib_cqe **pcqe,
					  पूर्णांक *budget)
अणु
	काष्ठा bnxt_qplib_qp *qp;
	काष्ठा bnxt_qplib_q *sq, *rq;
	काष्ठा bnxt_qplib_cqe *cqe;
	u32 swq_last = 0, cqe_cons;
	पूर्णांक rc = 0;

	/* Check the Status */
	अगर (hwcqe->status != CQ_TERMINAL_STATUS_OK)
		dev_warn(&cq->hwq.pdev->dev,
			 "FP: CQ Process Terminal Error status = 0x%x\n",
			 hwcqe->status);

	qp = (काष्ठा bnxt_qplib_qp *)((अचिन्हित दीर्घ)
				      le64_to_cpu(hwcqe->qp_handle));
	अगर (!qp) अणु
		dev_err(&cq->hwq.pdev->dev,
			"FP: CQ Process terminal qp is NULL\n");
		वापस -EINVAL;
	पूर्ण

	/* Must block new posting of SQ and RQ */
	qp->state = CMDQ_MODIFY_QP_NEW_STATE_ERR;

	sq = &qp->sq;
	rq = &qp->rq;

	cqe_cons = le16_to_cpu(hwcqe->sq_cons_idx);
	अगर (cqe_cons == 0xFFFF)
		जाओ करो_rq;
	cqe_cons %= sq->max_wqe;

	अगर (qp->sq.flushed) अणु
		dev_dbg(&cq->hwq.pdev->dev,
			"%s: QP in Flush QP = %p\n", __func__, qp);
		जाओ sq_करोne;
	पूर्ण

	/* Terminal CQE can also include aggregated successful CQEs prior.
	 * So we must complete all CQEs from the current sq's cons to the
	 * cq_cons with status OK
	 */
	cqe = *pcqe;
	जबतक (*budget) अणु
		swq_last = sq->swq_last;
		अगर (swq_last == cqe_cons)
			अवरोध;
		अगर (sq->swq[swq_last].flags & SQ_SEND_FLAGS_SIGNAL_COMP) अणु
			स_रखो(cqe, 0, माप(*cqe));
			cqe->status = CQ_REQ_STATUS_OK;
			cqe->opcode = CQ_BASE_CQE_TYPE_REQ;
			cqe->qp_handle = (u64)(अचिन्हित दीर्घ)qp;
			cqe->src_qp = qp->id;
			cqe->wr_id = sq->swq[swq_last].wr_id;
			cqe->type = sq->swq[swq_last].type;
			cqe++;
			(*budget)--;
		पूर्ण
		bnxt_qplib_hwq_incr_cons(&sq->hwq, sq->swq[swq_last].slots);
		sq->swq_last = sq->swq[swq_last].next_idx;
	पूर्ण
	*pcqe = cqe;
	अगर (!(*budget) && swq_last != cqe_cons) अणु
		/* Out of budget */
		rc = -EAGAIN;
		जाओ sq_करोne;
	पूर्ण
sq_करोne:
	अगर (rc)
		वापस rc;
करो_rq:
	cqe_cons = le16_to_cpu(hwcqe->rq_cons_idx);
	अगर (cqe_cons == 0xFFFF) अणु
		जाओ करोne;
	पूर्ण अन्यथा अगर (cqe_cons > rq->max_wqe - 1) अणु
		dev_err(&cq->hwq.pdev->dev,
			"FP: CQ Processed terminal reported rq_cons_idx 0x%x exceeds max 0x%x\n",
			cqe_cons, rq->max_wqe);
		rc = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर (qp->rq.flushed) अणु
		dev_dbg(&cq->hwq.pdev->dev,
			"%s: QP in Flush QP = %p\n", __func__, qp);
		rc = 0;
		जाओ करोne;
	पूर्ण

	/* Terminal CQE requires all posted RQEs to complete with FLUSHED_ERR
	 * from the current rq->cons to the rq->prod regardless what the
	 * rq->cons the terminal CQE indicates
	 */

	/* Add qp to flush list of the CQ */
	bnxt_qplib_add_flush_qp(qp);
करोne:
	वापस rc;
पूर्ण

अटल पूर्णांक bnxt_qplib_cq_process_cutoff(काष्ठा bnxt_qplib_cq *cq,
					काष्ठा cq_cutoff *hwcqe)
अणु
	/* Check the Status */
	अगर (hwcqe->status != CQ_CUTOFF_STATUS_OK) अणु
		dev_err(&cq->hwq.pdev->dev,
			"FP: CQ Process Cutoff Error status = 0x%x\n",
			hwcqe->status);
		वापस -EINVAL;
	पूर्ण
	clear_bit(CQ_FLAGS_RESIZE_IN_PROG, &cq->flags);
	wake_up_पूर्णांकerruptible(&cq->रुकोq);

	वापस 0;
पूर्ण

पूर्णांक bnxt_qplib_process_flush_list(काष्ठा bnxt_qplib_cq *cq,
				  काष्ठा bnxt_qplib_cqe *cqe,
				  पूर्णांक num_cqes)
अणु
	काष्ठा bnxt_qplib_qp *qp = शून्य;
	u32 budget = num_cqes;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cq->flush_lock, flags);
	list_क्रम_each_entry(qp, &cq->sqf_head, sq_flush) अणु
		dev_dbg(&cq->hwq.pdev->dev, "FP: Flushing SQ QP= %p\n", qp);
		__flush_sq(&qp->sq, qp, &cqe, &budget);
	पूर्ण

	list_क्रम_each_entry(qp, &cq->rqf_head, rq_flush) अणु
		dev_dbg(&cq->hwq.pdev->dev, "FP: Flushing RQ QP= %p\n", qp);
		__flush_rq(&qp->rq, qp, &cqe, &budget);
	पूर्ण
	spin_unlock_irqrestore(&cq->flush_lock, flags);

	वापस num_cqes - budget;
पूर्ण

पूर्णांक bnxt_qplib_poll_cq(काष्ठा bnxt_qplib_cq *cq, काष्ठा bnxt_qplib_cqe *cqe,
		       पूर्णांक num_cqes, काष्ठा bnxt_qplib_qp **lib_qp)
अणु
	काष्ठा cq_base *hw_cqe;
	u32 sw_cons, raw_cons;
	पूर्णांक budget, rc = 0;

	raw_cons = cq->hwq.cons;
	budget = num_cqes;

	जबतक (budget) अणु
		sw_cons = HWQ_CMP(raw_cons, &cq->hwq);
		hw_cqe = bnxt_qplib_get_qe(&cq->hwq, sw_cons, शून्य);

		/* Check क्रम Valid bit */
		अगर (!CQE_CMP_VALID(hw_cqe, raw_cons, cq->hwq.max_elements))
			अवरोध;

		/*
		 * The valid test of the entry must be करोne first beक्रमe
		 * पढ़ोing any further.
		 */
		dma_rmb();
		/* From the device's respective CQE क्रमmat to qplib_wc*/
		चयन (hw_cqe->cqe_type_toggle & CQ_BASE_CQE_TYPE_MASK) अणु
		हाल CQ_BASE_CQE_TYPE_REQ:
			rc = bnxt_qplib_cq_process_req(cq,
						       (काष्ठा cq_req *)hw_cqe,
						       &cqe, &budget,
						       sw_cons, lib_qp);
			अवरोध;
		हाल CQ_BASE_CQE_TYPE_RES_RC:
			rc = bnxt_qplib_cq_process_res_rc(cq,
							  (काष्ठा cq_res_rc *)
							  hw_cqe, &cqe,
							  &budget);
			अवरोध;
		हाल CQ_BASE_CQE_TYPE_RES_UD:
			rc = bnxt_qplib_cq_process_res_ud
					(cq, (काष्ठा cq_res_ud *)hw_cqe, &cqe,
					 &budget);
			अवरोध;
		हाल CQ_BASE_CQE_TYPE_RES_RAWETH_QP1:
			rc = bnxt_qplib_cq_process_res_raweth_qp1
					(cq, (काष्ठा cq_res_raweth_qp1 *)
					 hw_cqe, &cqe, &budget);
			अवरोध;
		हाल CQ_BASE_CQE_TYPE_TERMINAL:
			rc = bnxt_qplib_cq_process_terminal
					(cq, (काष्ठा cq_terminal *)hw_cqe,
					 &cqe, &budget);
			अवरोध;
		हाल CQ_BASE_CQE_TYPE_CUT_OFF:
			bnxt_qplib_cq_process_cutoff
					(cq, (काष्ठा cq_cutoff *)hw_cqe);
			/* Done processing this CQ */
			जाओ निकास;
		शेष:
			dev_err(&cq->hwq.pdev->dev,
				"process_cq unknown type 0x%lx\n",
				hw_cqe->cqe_type_toggle &
				CQ_BASE_CQE_TYPE_MASK);
			rc = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (rc < 0) अणु
			अगर (rc == -EAGAIN)
				अवरोध;
			/* Error जबतक processing the CQE, just skip to the
			 * next one
			 */
			dev_err(&cq->hwq.pdev->dev,
				"process_cqe error rc = 0x%x\n", rc);
		पूर्ण
		raw_cons++;
	पूर्ण
	अगर (cq->hwq.cons != raw_cons) अणु
		cq->hwq.cons = raw_cons;
		bnxt_qplib_ring_db(&cq->dbinfo, DBC_DBC_TYPE_CQ);
	पूर्ण
निकास:
	वापस num_cqes - budget;
पूर्ण

व्योम bnxt_qplib_req_notअगरy_cq(काष्ठा bnxt_qplib_cq *cq, u32 arm_type)
अणु
	अगर (arm_type)
		bnxt_qplib_ring_db(&cq->dbinfo, arm_type);
	/* Using cq->arm_state variable to track whether to issue cq handler */
	atomic_set(&cq->arm_state, 1);
पूर्ण

व्योम bnxt_qplib_flush_cqn_wq(काष्ठा bnxt_qplib_qp *qp)
अणु
	flush_workqueue(qp->scq->nq->cqn_wq);
	अगर (qp->scq != qp->rcq)
		flush_workqueue(qp->rcq->nq->cqn_wq);
पूर्ण
