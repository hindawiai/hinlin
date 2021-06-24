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
#समावेश <linux/slab.h>
#समावेश <linux/mman.h>
#समावेश <net/sock.h>

#समावेश "iw_cxgb4.h"

अटल व्योम prपूर्णांक_tpte(काष्ठा c4iw_dev *dev, u32 stag)
अणु
	पूर्णांक ret;
	काष्ठा fw_ri_tpte tpte;

	ret = cxgb4_पढ़ो_tpte(dev->rdev.lldi.ports[0], stag,
			      (__be32 *)&tpte);
	अगर (ret) अणु
		dev_err(&dev->rdev.lldi.pdev->dev,
			"%s cxgb4_read_tpte err %d\n", __func__, ret);
		वापस;
	पूर्ण
	pr_debug("stag idx 0x%x valid %d key 0x%x state %d pdid %d perm 0x%x ps %d len 0x%llx va 0x%llx\n",
		 stag & 0xffffff00,
		 FW_RI_TPTE_VALID_G(ntohl(tpte.valid_to_pdid)),
		 FW_RI_TPTE_STAGKEY_G(ntohl(tpte.valid_to_pdid)),
		 FW_RI_TPTE_STAGSTATE_G(ntohl(tpte.valid_to_pdid)),
		 FW_RI_TPTE_PDID_G(ntohl(tpte.valid_to_pdid)),
		 FW_RI_TPTE_PERM_G(ntohl(tpte.locपढ़ो_to_qpid)),
		 FW_RI_TPTE_PS_G(ntohl(tpte.locपढ़ो_to_qpid)),
		 ((u64)ntohl(tpte.len_hi) << 32) | ntohl(tpte.len_lo),
		 ((u64)ntohl(tpte.va_hi) << 32) | ntohl(tpte.va_lo_fbo));
पूर्ण

अटल व्योम dump_err_cqe(काष्ठा c4iw_dev *dev, काष्ठा t4_cqe *err_cqe)
अणु
	__be64 *p = (व्योम *)err_cqe;

	dev_err(&dev->rdev.lldi.pdev->dev,
		"AE qpid %d opcode %d status 0x%x "
		"type %d len 0x%x wrid.hi 0x%x wrid.lo 0x%x\n",
		CQE_QPID(err_cqe), CQE_OPCODE(err_cqe),
		CQE_STATUS(err_cqe), CQE_TYPE(err_cqe), ntohl(err_cqe->len),
		CQE_WRID_HI(err_cqe), CQE_WRID_LOW(err_cqe));

	pr_debug("%016llx %016llx %016llx %016llx - %016llx %016llx %016llx %016llx\n",
		 be64_to_cpu(p[0]), be64_to_cpu(p[1]), be64_to_cpu(p[2]),
		 be64_to_cpu(p[3]), be64_to_cpu(p[4]), be64_to_cpu(p[5]),
		 be64_to_cpu(p[6]), be64_to_cpu(p[7]));

	/*
	 * Ingress WRITE and READ_RESP errors provide
	 * the offending stag, so parse and log it.
	 */
	अगर (RQ_TYPE(err_cqe) && (CQE_OPCODE(err_cqe) == FW_RI_RDMA_WRITE ||
				 CQE_OPCODE(err_cqe) == FW_RI_READ_RESP))
		prपूर्णांक_tpte(dev, CQE_WRID_STAG(err_cqe));
पूर्ण

अटल व्योम post_qp_event(काष्ठा c4iw_dev *dev, काष्ठा c4iw_cq *chp,
			  काष्ठा c4iw_qp *qhp,
			  काष्ठा t4_cqe *err_cqe,
			  क्रमागत ib_event_type ib_event)
अणु
	काष्ठा ib_event event;
	काष्ठा c4iw_qp_attributes attrs;
	अचिन्हित दीर्घ flag;

	dump_err_cqe(dev, err_cqe);

	अगर (qhp->attr.state == C4IW_QP_STATE_RTS) अणु
		attrs.next_state = C4IW_QP_STATE_TERMINATE;
		c4iw_modअगरy_qp(qhp->rhp, qhp, C4IW_QP_ATTR_NEXT_STATE,
			       &attrs, 0);
	पूर्ण

	event.event = ib_event;
	event.device = chp->ibcq.device;
	अगर (ib_event == IB_EVENT_CQ_ERR)
		event.element.cq = &chp->ibcq;
	अन्यथा
		event.element.qp = &qhp->ibqp;
	अगर (qhp->ibqp.event_handler)
		(*qhp->ibqp.event_handler)(&event, qhp->ibqp.qp_context);

	अगर (t4_clear_cq_armed(&chp->cq)) अणु
		spin_lock_irqsave(&chp->comp_handler_lock, flag);
		(*chp->ibcq.comp_handler)(&chp->ibcq, chp->ibcq.cq_context);
		spin_unlock_irqrestore(&chp->comp_handler_lock, flag);
	पूर्ण
पूर्ण

व्योम c4iw_ev_dispatch(काष्ठा c4iw_dev *dev, काष्ठा t4_cqe *err_cqe)
अणु
	काष्ठा c4iw_cq *chp;
	काष्ठा c4iw_qp *qhp;
	u32 cqid;

	xa_lock_irq(&dev->qps);
	qhp = xa_load(&dev->qps, CQE_QPID(err_cqe));
	अगर (!qhp) अणु
		pr_err("BAD AE qpid 0x%x opcode %d status 0x%x type %d wrid.hi 0x%x wrid.lo 0x%x\n",
		       CQE_QPID(err_cqe),
		       CQE_OPCODE(err_cqe), CQE_STATUS(err_cqe),
		       CQE_TYPE(err_cqe), CQE_WRID_HI(err_cqe),
		       CQE_WRID_LOW(err_cqe));
		xa_unlock_irq(&dev->qps);
		जाओ out;
	पूर्ण

	अगर (SQ_TYPE(err_cqe))
		cqid = qhp->attr.scq;
	अन्यथा
		cqid = qhp->attr.rcq;
	chp = get_chp(dev, cqid);
	अगर (!chp) अणु
		pr_err("BAD AE cqid 0x%x qpid 0x%x opcode %d status 0x%x type %d wrid.hi 0x%x wrid.lo 0x%x\n",
		       cqid, CQE_QPID(err_cqe),
		       CQE_OPCODE(err_cqe), CQE_STATUS(err_cqe),
		       CQE_TYPE(err_cqe), CQE_WRID_HI(err_cqe),
		       CQE_WRID_LOW(err_cqe));
		xa_unlock_irq(&dev->qps);
		जाओ out;
	पूर्ण

	c4iw_qp_add_ref(&qhp->ibqp);
	atomic_inc(&chp->refcnt);
	xa_unlock_irq(&dev->qps);

	/* Bad incoming ग_लिखो */
	अगर (RQ_TYPE(err_cqe) &&
	    (CQE_OPCODE(err_cqe) == FW_RI_RDMA_WRITE)) अणु
		post_qp_event(dev, chp, qhp, err_cqe, IB_EVENT_QP_REQ_ERR);
		जाओ करोne;
	पूर्ण

	चयन (CQE_STATUS(err_cqe)) अणु

	/* Completion Events */
	हाल T4_ERR_SUCCESS:
		pr_err("AE with status 0!\n");
		अवरोध;

	हाल T4_ERR_STAG:
	हाल T4_ERR_PDID:
	हाल T4_ERR_QPID:
	हाल T4_ERR_ACCESS:
	हाल T4_ERR_WRAP:
	हाल T4_ERR_BOUND:
	हाल T4_ERR_INVALIDATE_SHARED_MR:
	हाल T4_ERR_INVALIDATE_MR_WITH_MW_BOUND:
		post_qp_event(dev, chp, qhp, err_cqe, IB_EVENT_QP_ACCESS_ERR);
		अवरोध;

	/* Device Fatal Errors */
	हाल T4_ERR_ECC:
	हाल T4_ERR_ECC_PSTAG:
	हाल T4_ERR_INTERNAL_ERR:
		post_qp_event(dev, chp, qhp, err_cqe, IB_EVENT_DEVICE_FATAL);
		अवरोध;

	/* QP Fatal Errors */
	हाल T4_ERR_OUT_OF_RQE:
	हाल T4_ERR_PBL_ADDR_BOUND:
	हाल T4_ERR_CRC:
	हाल T4_ERR_MARKER:
	हाल T4_ERR_PDU_LEN_ERR:
	हाल T4_ERR_DDP_VERSION:
	हाल T4_ERR_RDMA_VERSION:
	हाल T4_ERR_OPCODE:
	हाल T4_ERR_DDP_QUEUE_NUM:
	हाल T4_ERR_MSN:
	हाल T4_ERR_TBIT:
	हाल T4_ERR_MO:
	हाल T4_ERR_MSN_GAP:
	हाल T4_ERR_MSN_RANGE:
	हाल T4_ERR_RQE_ADDR_BOUND:
	हाल T4_ERR_IRD_OVERFLOW:
		post_qp_event(dev, chp, qhp, err_cqe, IB_EVENT_QP_FATAL);
		अवरोध;

	शेष:
		pr_err("Unknown T4 status 0x%x QPID 0x%x\n",
		       CQE_STATUS(err_cqe), qhp->wq.sq.qid);
		post_qp_event(dev, chp, qhp, err_cqe, IB_EVENT_QP_FATAL);
		अवरोध;
	पूर्ण
करोne:
	अगर (atomic_dec_and_test(&chp->refcnt))
		wake_up(&chp->रुको);
	c4iw_qp_rem_ref(&qhp->ibqp);
out:
	वापस;
पूर्ण

पूर्णांक c4iw_ev_handler(काष्ठा c4iw_dev *dev, u32 qid)
अणु
	काष्ठा c4iw_cq *chp;
	अचिन्हित दीर्घ flag;

	xa_lock_irqsave(&dev->cqs, flag);
	chp = xa_load(&dev->cqs, qid);
	अगर (chp) अणु
		atomic_inc(&chp->refcnt);
		xa_unlock_irqrestore(&dev->cqs, flag);
		t4_clear_cq_armed(&chp->cq);
		spin_lock_irqsave(&chp->comp_handler_lock, flag);
		(*chp->ibcq.comp_handler)(&chp->ibcq, chp->ibcq.cq_context);
		spin_unlock_irqrestore(&chp->comp_handler_lock, flag);
		अगर (atomic_dec_and_test(&chp->refcnt))
			wake_up(&chp->रुको);
	पूर्ण अन्यथा अणु
		pr_debug("unknown cqid 0x%x\n", qid);
		xa_unlock_irqrestore(&dev->cqs, flag);
	पूर्ण
	वापस 0;
पूर्ण
