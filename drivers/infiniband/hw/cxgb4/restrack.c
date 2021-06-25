<शैली गुरु>
/*
 * Copyright (c) 2018 Chelsio, Inc. All rights reserved.
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

#समावेश <rdma/rdma_cm.h>

#समावेश "iw_cxgb4.h"
#समावेश <rdma/restrack.h>
#समावेश <uapi/rdma/rdma_netlink.h>

अटल पूर्णांक fill_sq(काष्ठा sk_buff *msg, काष्ठा t4_wq *wq)
अणु
	/* WQ+SQ */
	अगर (rdma_nl_put_driver_u32(msg, "sqid", wq->sq.qid))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "flushed", wq->flushed))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "memsize", wq->sq.memsize))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "cidx", wq->sq.cidx))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "pidx", wq->sq.pidx))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "wq_pidx", wq->sq.wq_pidx))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "flush_cidx", wq->sq.flush_cidx))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "in_use", wq->sq.in_use))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "size", wq->sq.size))
		जाओ err;
	अगर (rdma_nl_put_driver_u32_hex(msg, "flags", wq->sq.flags))
		जाओ err;
	वापस 0;
err:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fill_rq(काष्ठा sk_buff *msg, काष्ठा t4_wq *wq)
अणु
	/* RQ */
	अगर (rdma_nl_put_driver_u32(msg, "rqid", wq->rq.qid))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "memsize", wq->rq.memsize))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "cidx", wq->rq.cidx))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "pidx", wq->rq.pidx))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "wq_pidx", wq->rq.wq_pidx))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "msn", wq->rq.msn))
		जाओ err;
	अगर (rdma_nl_put_driver_u32_hex(msg, "rqt_hwaddr", wq->rq.rqt_hwaddr))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "rqt_size", wq->rq.rqt_size))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "in_use", wq->rq.in_use))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "size", wq->rq.size))
		जाओ err;
	वापस 0;
err:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fill_swsqe(काष्ठा sk_buff *msg, काष्ठा t4_sq *sq, u16 idx,
		      काष्ठा t4_swsqe *sqe)
अणु
	अगर (rdma_nl_put_driver_u32(msg, "idx", idx))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "opcode", sqe->opcode))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "complete", sqe->complete))
		जाओ err;
	अगर (sqe->complete &&
	    rdma_nl_put_driver_u32(msg, "cqe_status", CQE_STATUS(&sqe->cqe)))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "signaled", sqe->संकेतed))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "flushed", sqe->flushed))
		जाओ err;
	वापस 0;
err:
	वापस -EMSGSIZE;
पूर्ण

/*
 * Dump the first and last pending sqes.
 */
अटल पूर्णांक fill_swsqes(काष्ठा sk_buff *msg, काष्ठा t4_sq *sq,
		       u16 first_idx, काष्ठा t4_swsqe *first_sqe,
		       u16 last_idx, काष्ठा t4_swsqe *last_sqe)
अणु
	अगर (!first_sqe)
		जाओ out;
	अगर (fill_swsqe(msg, sq, first_idx, first_sqe))
		जाओ err;
	अगर (!last_sqe)
		जाओ out;
	अगर (fill_swsqe(msg, sq, last_idx, last_sqe))
		जाओ err;
out:
	वापस 0;
err:
	वापस -EMSGSIZE;
पूर्ण

पूर्णांक c4iw_fill_res_qp_entry(काष्ठा sk_buff *msg, काष्ठा ib_qp *ibqp)
अणु
	काष्ठा t4_swsqe *fsp = शून्य, *lsp = शून्य;
	काष्ठा c4iw_qp *qhp = to_c4iw_qp(ibqp);
	u16 first_sq_idx = 0, last_sq_idx = 0;
	काष्ठा t4_swsqe first_sqe, last_sqe;
	काष्ठा nlattr *table_attr;
	काष्ठा t4_wq wq;

	/* User qp state is not available, so करोn't dump user qps */
	अगर (qhp->ucontext)
		वापस 0;

	table_attr = nla_nest_start_noflag(msg, RDMA_NLDEV_ATTR_DRIVER);
	अगर (!table_attr)
		जाओ err;

	/* Get a consistent snapshot */
	spin_lock_irq(&qhp->lock);
	wq = qhp->wq;

	/* If there are any pending sqes, copy the first and last */
	अगर (wq.sq.cidx != wq.sq.pidx) अणु
		first_sq_idx = wq.sq.cidx;
		first_sqe = qhp->wq.sq.sw_sq[first_sq_idx];
		fsp = &first_sqe;
		last_sq_idx = wq.sq.pidx;
		अगर (last_sq_idx-- == 0)
			last_sq_idx = wq.sq.size - 1;
		अगर (last_sq_idx != first_sq_idx) अणु
			last_sqe = qhp->wq.sq.sw_sq[last_sq_idx];
			lsp = &last_sqe;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&qhp->lock);

	अगर (fill_sq(msg, &wq))
		जाओ err_cancel_table;

	अगर (fill_swsqes(msg, &wq.sq, first_sq_idx, fsp, last_sq_idx, lsp))
		जाओ err_cancel_table;

	अगर (fill_rq(msg, &wq))
		जाओ err_cancel_table;

	nla_nest_end(msg, table_attr);
	वापस 0;

err_cancel_table:
	nla_nest_cancel(msg, table_attr);
err:
	वापस -EMSGSIZE;
पूर्ण

जोड़ जोड़_ep अणु
	काष्ठा c4iw_listen_ep lep;
	काष्ठा c4iw_ep ep;
पूर्ण;

पूर्णांक c4iw_fill_res_cm_id_entry(काष्ठा sk_buff *msg,
			      काष्ठा rdma_cm_id *cm_id)
अणु
	काष्ठा nlattr *table_attr;
	काष्ठा c4iw_ep_common *epcp;
	काष्ठा c4iw_listen_ep *listen_ep = शून्य;
	काष्ठा c4iw_ep *ep = शून्य;
	काष्ठा iw_cm_id *iw_cm_id;
	जोड़ जोड़_ep *uep;

	iw_cm_id = rdma_iw_cm_id(cm_id);
	अगर (!iw_cm_id)
		वापस 0;
	epcp = (काष्ठा c4iw_ep_common *)iw_cm_id->provider_data;
	अगर (!epcp)
		वापस 0;
	uep = kzalloc(माप(*uep), GFP_KERNEL);
	अगर (!uep)
		वापस 0;

	table_attr = nla_nest_start_noflag(msg, RDMA_NLDEV_ATTR_DRIVER);
	अगर (!table_attr)
		जाओ err_मुक्त_uep;

	/* Get a consistent snapshot */
	mutex_lock(&epcp->mutex);
	अगर (epcp->state == LISTEN) अणु
		uep->lep = *(काष्ठा c4iw_listen_ep *)epcp;
		mutex_unlock(&epcp->mutex);
		listen_ep = &uep->lep;
		epcp = &listen_ep->com;
	पूर्ण अन्यथा अणु
		uep->ep = *(काष्ठा c4iw_ep *)epcp;
		mutex_unlock(&epcp->mutex);
		ep = &uep->ep;
		epcp = &ep->com;
	पूर्ण

	अगर (rdma_nl_put_driver_u32(msg, "state", epcp->state))
		जाओ err_cancel_table;
	अगर (rdma_nl_put_driver_u64_hex(msg, "flags", epcp->flags))
		जाओ err_cancel_table;
	अगर (rdma_nl_put_driver_u64_hex(msg, "history", epcp->history))
		जाओ err_cancel_table;

	अगर (epcp->state == LISTEN) अणु
		अगर (rdma_nl_put_driver_u32(msg, "stid", listen_ep->stid))
			जाओ err_cancel_table;
		अगर (rdma_nl_put_driver_u32(msg, "backlog", listen_ep->backlog))
			जाओ err_cancel_table;
	पूर्ण अन्यथा अणु
		अगर (rdma_nl_put_driver_u32(msg, "hwtid", ep->hwtid))
			जाओ err_cancel_table;
		अगर (rdma_nl_put_driver_u32(msg, "ord", ep->ord))
			जाओ err_cancel_table;
		अगर (rdma_nl_put_driver_u32(msg, "ird", ep->ird))
			जाओ err_cancel_table;
		अगर (rdma_nl_put_driver_u32(msg, "emss", ep->emss))
			जाओ err_cancel_table;

		अगर (!ep->parent_ep && rdma_nl_put_driver_u32(msg, "atid",
							     ep->atid))
			जाओ err_cancel_table;
	पूर्ण
	nla_nest_end(msg, table_attr);
	kमुक्त(uep);
	वापस 0;

err_cancel_table:
	nla_nest_cancel(msg, table_attr);
err_मुक्त_uep:
	kमुक्त(uep);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fill_cq(काष्ठा sk_buff *msg, काष्ठा t4_cq *cq)
अणु
	अगर (rdma_nl_put_driver_u32(msg, "cqid", cq->cqid))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "memsize", cq->memsize))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "size", cq->size))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "cidx", cq->cidx))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "cidx_inc", cq->cidx_inc))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "sw_cidx", cq->sw_cidx))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "sw_pidx", cq->sw_pidx))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "sw_in_use", cq->sw_in_use))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "vector", cq->vector))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "gen", cq->gen))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "error", cq->error))
		जाओ err;
	अगर (rdma_nl_put_driver_u64_hex(msg, "bits_type_ts",
					 be64_to_cpu(cq->bits_type_ts)))
		जाओ err;
	अगर (rdma_nl_put_driver_u64_hex(msg, "flags", cq->flags))
		जाओ err;

	वापस 0;

err:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fill_cqe(काष्ठा sk_buff *msg, काष्ठा t4_cqe *cqe, u16 idx,
		    स्थिर अक्षर *qstr)
अणु
	अगर (rdma_nl_put_driver_u32(msg, qstr, idx))
		जाओ err;
	अगर (rdma_nl_put_driver_u32_hex(msg, "header",
					 be32_to_cpu(cqe->header)))
		जाओ err;
	अगर (rdma_nl_put_driver_u32(msg, "len", be32_to_cpu(cqe->len)))
		जाओ err;
	अगर (rdma_nl_put_driver_u32_hex(msg, "wrid_hi",
					 be32_to_cpu(cqe->u.gen.wrid_hi)))
		जाओ err;
	अगर (rdma_nl_put_driver_u32_hex(msg, "wrid_low",
					 be32_to_cpu(cqe->u.gen.wrid_low)))
		जाओ err;
	अगर (rdma_nl_put_driver_u64_hex(msg, "bits_type_ts",
					 be64_to_cpu(cqe->bits_type_ts)))
		जाओ err;

	वापस 0;

err:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fill_hwcqes(काष्ठा sk_buff *msg, काष्ठा t4_cq *cq,
		       काष्ठा t4_cqe *cqes)
अणु
	u16 idx;

	idx = (cq->cidx > 0) ? cq->cidx - 1 : cq->size - 1;
	अगर (fill_cqe(msg, cqes, idx, "hwcq_idx"))
		जाओ err;
	idx = cq->cidx;
	अगर (fill_cqe(msg, cqes + 1, idx, "hwcq_idx"))
		जाओ err;

	वापस 0;
err:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक fill_swcqes(काष्ठा sk_buff *msg, काष्ठा t4_cq *cq,
		       काष्ठा t4_cqe *cqes)
अणु
	u16 idx;

	अगर (!cq->sw_in_use)
		वापस 0;

	idx = cq->sw_cidx;
	अगर (fill_cqe(msg, cqes, idx, "swcq_idx"))
		जाओ err;
	अगर (cq->sw_in_use == 1)
		जाओ out;
	idx = (cq->sw_pidx > 0) ? cq->sw_pidx - 1 : cq->size - 1;
	अगर (fill_cqe(msg, cqes + 1, idx, "swcq_idx"))
		जाओ err;
out:
	वापस 0;
err:
	वापस -EMSGSIZE;
पूर्ण

पूर्णांक c4iw_fill_res_cq_entry(काष्ठा sk_buff *msg, काष्ठा ib_cq *ibcq)
अणु
	काष्ठा c4iw_cq *chp = to_c4iw_cq(ibcq);
	काष्ठा nlattr *table_attr;
	काष्ठा t4_cqe hwcqes[2];
	काष्ठा t4_cqe swcqes[2];
	काष्ठा t4_cq cq;
	u16 idx;

	/* User cq state is not available, so करोn't dump user cqs */
	अगर (ibcq->uobject)
		वापस 0;

	table_attr = nla_nest_start_noflag(msg, RDMA_NLDEV_ATTR_DRIVER);
	अगर (!table_attr)
		जाओ err;

	/* Get a consistent snapshot */
	spin_lock_irq(&chp->lock);

	/* t4_cq काष्ठा */
	cq = chp->cq;

	/* get 2 hw cqes: cidx-1, and cidx */
	idx = (cq.cidx > 0) ? cq.cidx - 1 : cq.size - 1;
	hwcqes[0] = chp->cq.queue[idx];

	idx = cq.cidx;
	hwcqes[1] = chp->cq.queue[idx];

	/* get first and last sw cqes */
	अगर (cq.sw_in_use) अणु
		swcqes[0] = chp->cq.sw_queue[cq.sw_cidx];
		अगर (cq.sw_in_use > 1) अणु
			idx = (cq.sw_pidx > 0) ? cq.sw_pidx - 1 : cq.size - 1;
			swcqes[1] = chp->cq.sw_queue[idx];
		पूर्ण
	पूर्ण

	spin_unlock_irq(&chp->lock);

	अगर (fill_cq(msg, &cq))
		जाओ err_cancel_table;

	अगर (fill_swcqes(msg, &cq, swcqes))
		जाओ err_cancel_table;

	अगर (fill_hwcqes(msg, &cq, hwcqes))
		जाओ err_cancel_table;

	nla_nest_end(msg, table_attr);
	वापस 0;

err_cancel_table:
	nla_nest_cancel(msg, table_attr);
err:
	वापस -EMSGSIZE;
पूर्ण

पूर्णांक c4iw_fill_res_mr_entry(काष्ठा sk_buff *msg, काष्ठा ib_mr *ibmr)
अणु
	काष्ठा c4iw_mr *mhp = to_c4iw_mr(ibmr);
	काष्ठा c4iw_dev *dev = mhp->rhp;
	u32 stag = mhp->attr.stag;
	काष्ठा nlattr *table_attr;
	काष्ठा fw_ri_tpte tpte;
	पूर्णांक ret;

	अगर (!stag)
		वापस 0;

	table_attr = nla_nest_start_noflag(msg, RDMA_NLDEV_ATTR_DRIVER);
	अगर (!table_attr)
		जाओ err;

	ret = cxgb4_पढ़ो_tpte(dev->rdev.lldi.ports[0], stag, (__be32 *)&tpte);
	अगर (ret) अणु
		dev_err(&dev->rdev.lldi.pdev->dev,
			"%s cxgb4_read_tpte err %d\n", __func__, ret);
		वापस 0;
	पूर्ण

	अगर (rdma_nl_put_driver_u32_hex(msg, "idx", stag >> 8))
		जाओ err_cancel_table;
	अगर (rdma_nl_put_driver_u32(msg, "valid",
			FW_RI_TPTE_VALID_G(ntohl(tpte.valid_to_pdid))))
		जाओ err_cancel_table;
	अगर (rdma_nl_put_driver_u32_hex(msg, "key", stag & 0xff))
		जाओ err_cancel_table;
	अगर (rdma_nl_put_driver_u32(msg, "state",
			FW_RI_TPTE_STAGSTATE_G(ntohl(tpte.valid_to_pdid))))
		जाओ err_cancel_table;
	अगर (rdma_nl_put_driver_u32(msg, "pdid",
			FW_RI_TPTE_PDID_G(ntohl(tpte.valid_to_pdid))))
		जाओ err_cancel_table;
	अगर (rdma_nl_put_driver_u32_hex(msg, "perm",
			FW_RI_TPTE_PERM_G(ntohl(tpte.locपढ़ो_to_qpid))))
		जाओ err_cancel_table;
	अगर (rdma_nl_put_driver_u32(msg, "ps",
			FW_RI_TPTE_PS_G(ntohl(tpte.locपढ़ो_to_qpid))))
		जाओ err_cancel_table;
	अगर (rdma_nl_put_driver_u64(msg, "len",
		      ((u64)ntohl(tpte.len_hi) << 32) | ntohl(tpte.len_lo)))
		जाओ err_cancel_table;
	अगर (rdma_nl_put_driver_u32_hex(msg, "pbl_addr",
			FW_RI_TPTE_PBLADDR_G(ntohl(tpte.nosnoop_pbladdr))))
		जाओ err_cancel_table;

	nla_nest_end(msg, table_attr);
	वापस 0;

err_cancel_table:
	nla_nest_cancel(msg, table_attr);
err:
	वापस -EMSGSIZE;
पूर्ण
