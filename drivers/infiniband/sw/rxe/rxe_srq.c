<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#समावेश <linux/vदो_स्मृति.h>
#समावेश "rxe.h"
#समावेश "rxe_loc.h"
#समावेश "rxe_queue.h"

पूर्णांक rxe_srq_chk_attr(काष्ठा rxe_dev *rxe, काष्ठा rxe_srq *srq,
		     काष्ठा ib_srq_attr *attr, क्रमागत ib_srq_attr_mask mask)
अणु
	अगर (srq && srq->error) अणु
		pr_warn("srq in error state\n");
		जाओ err1;
	पूर्ण

	अगर (mask & IB_SRQ_MAX_WR) अणु
		अगर (attr->max_wr > rxe->attr.max_srq_wr) अणु
			pr_warn("max_wr(%d) > max_srq_wr(%d)\n",
				attr->max_wr, rxe->attr.max_srq_wr);
			जाओ err1;
		पूर्ण

		अगर (attr->max_wr <= 0) अणु
			pr_warn("max_wr(%d) <= 0\n", attr->max_wr);
			जाओ err1;
		पूर्ण

		अगर (srq && srq->limit && (attr->max_wr < srq->limit)) अणु
			pr_warn("max_wr (%d) < srq->limit (%d)\n",
				attr->max_wr, srq->limit);
			जाओ err1;
		पूर्ण

		अगर (attr->max_wr < RXE_MIN_SRQ_WR)
			attr->max_wr = RXE_MIN_SRQ_WR;
	पूर्ण

	अगर (mask & IB_SRQ_LIMIT) अणु
		अगर (attr->srq_limit > rxe->attr.max_srq_wr) अणु
			pr_warn("srq_limit(%d) > max_srq_wr(%d)\n",
				attr->srq_limit, rxe->attr.max_srq_wr);
			जाओ err1;
		पूर्ण

		अगर (srq && (attr->srq_limit > srq->rq.queue->buf->index_mask)) अणु
			pr_warn("srq_limit (%d) > cur limit(%d)\n",
				attr->srq_limit,
				 srq->rq.queue->buf->index_mask);
			जाओ err1;
		पूर्ण
	पूर्ण

	अगर (mask == IB_SRQ_INIT_MASK) अणु
		अगर (attr->max_sge > rxe->attr.max_srq_sge) अणु
			pr_warn("max_sge(%d) > max_srq_sge(%d)\n",
				attr->max_sge, rxe->attr.max_srq_sge);
			जाओ err1;
		पूर्ण

		अगर (attr->max_sge < RXE_MIN_SRQ_SGE)
			attr->max_sge = RXE_MIN_SRQ_SGE;
	पूर्ण

	वापस 0;

err1:
	वापस -EINVAL;
पूर्ण

पूर्णांक rxe_srq_from_init(काष्ठा rxe_dev *rxe, काष्ठा rxe_srq *srq,
		      काष्ठा ib_srq_init_attr *init, काष्ठा ib_udata *udata,
		      काष्ठा rxe_create_srq_resp __user *uresp)
अणु
	पूर्णांक err;
	पूर्णांक srq_wqe_size;
	काष्ठा rxe_queue *q;

	srq->ibsrq.event_handler	= init->event_handler;
	srq->ibsrq.srq_context		= init->srq_context;
	srq->limit		= init->attr.srq_limit;
	srq->srq_num		= srq->pelem.index;
	srq->rq.max_wr		= init->attr.max_wr;
	srq->rq.max_sge		= init->attr.max_sge;

	srq_wqe_size		= rcv_wqe_size(srq->rq.max_sge);

	spin_lock_init(&srq->rq.producer_lock);
	spin_lock_init(&srq->rq.consumer_lock);

	q = rxe_queue_init(rxe, &srq->rq.max_wr,
			   srq_wqe_size);
	अगर (!q) अणु
		pr_warn("unable to allocate queue for srq\n");
		वापस -ENOMEM;
	पूर्ण

	srq->rq.queue = q;

	err = करो_mmap_info(rxe, uresp ? &uresp->mi : शून्य, udata, q->buf,
			   q->buf_size, &q->ip);
	अगर (err) अणु
		vमुक्त(q->buf);
		kमुक्त(q);
		वापस err;
	पूर्ण

	अगर (uresp) अणु
		अगर (copy_to_user(&uresp->srq_num, &srq->srq_num,
				 माप(uresp->srq_num))) अणु
			rxe_queue_cleanup(q);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक rxe_srq_from_attr(काष्ठा rxe_dev *rxe, काष्ठा rxe_srq *srq,
		      काष्ठा ib_srq_attr *attr, क्रमागत ib_srq_attr_mask mask,
		      काष्ठा rxe_modअगरy_srq_cmd *ucmd, काष्ठा ib_udata *udata)
अणु
	पूर्णांक err;
	काष्ठा rxe_queue *q = srq->rq.queue;
	काष्ठा mminfo __user *mi = शून्य;

	अगर (mask & IB_SRQ_MAX_WR) अणु
		/*
		 * This is completely screwed up, the response is supposed to
		 * be in the outbuf not like this.
		 */
		mi = u64_to_user_ptr(ucmd->mmap_info_addr);

		err = rxe_queue_resize(q, &attr->max_wr,
				       rcv_wqe_size(srq->rq.max_sge), udata, mi,
				       &srq->rq.producer_lock,
				       &srq->rq.consumer_lock);
		अगर (err)
			जाओ err2;
	पूर्ण

	अगर (mask & IB_SRQ_LIMIT)
		srq->limit = attr->srq_limit;

	वापस 0;

err2:
	rxe_queue_cleanup(q);
	srq->rq.queue = शून्य;
	वापस err;
पूर्ण
