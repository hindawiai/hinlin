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

पूर्णांक rxe_cq_chk_attr(काष्ठा rxe_dev *rxe, काष्ठा rxe_cq *cq,
		    पूर्णांक cqe, पूर्णांक comp_vector)
अणु
	पूर्णांक count;

	अगर (cqe <= 0) अणु
		pr_warn("cqe(%d) <= 0\n", cqe);
		जाओ err1;
	पूर्ण

	अगर (cqe > rxe->attr.max_cqe) अणु
		pr_warn("cqe(%d) > max_cqe(%d)\n",
			cqe, rxe->attr.max_cqe);
		जाओ err1;
	पूर्ण

	अगर (cq) अणु
		count = queue_count(cq->queue);
		अगर (cqe < count) अणु
			pr_warn("cqe(%d) < current # elements in queue (%d)",
				cqe, count);
			जाओ err1;
		पूर्ण
	पूर्ण

	वापस 0;

err1:
	वापस -EINVAL;
पूर्ण

अटल व्योम rxe_send_complete(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा rxe_cq *cq = from_tasklet(cq, t, comp_task);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cq->cq_lock, flags);
	अगर (cq->is_dying) अणु
		spin_unlock_irqrestore(&cq->cq_lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&cq->cq_lock, flags);

	cq->ibcq.comp_handler(&cq->ibcq, cq->ibcq.cq_context);
पूर्ण

पूर्णांक rxe_cq_from_init(काष्ठा rxe_dev *rxe, काष्ठा rxe_cq *cq, पूर्णांक cqe,
		     पूर्णांक comp_vector, काष्ठा ib_udata *udata,
		     काष्ठा rxe_create_cq_resp __user *uresp)
अणु
	पूर्णांक err;

	cq->queue = rxe_queue_init(rxe, &cqe,
				   माप(काष्ठा rxe_cqe));
	अगर (!cq->queue) अणु
		pr_warn("unable to create cq\n");
		वापस -ENOMEM;
	पूर्ण

	err = करो_mmap_info(rxe, uresp ? &uresp->mi : शून्य, udata,
			   cq->queue->buf, cq->queue->buf_size, &cq->queue->ip);
	अगर (err) अणु
		vमुक्त(cq->queue->buf);
		kमुक्त(cq->queue);
		वापस err;
	पूर्ण

	अगर (uresp)
		cq->is_user = 1;

	cq->is_dying = false;

	tasklet_setup(&cq->comp_task, rxe_send_complete);

	spin_lock_init(&cq->cq_lock);
	cq->ibcq.cqe = cqe;
	वापस 0;
पूर्ण

पूर्णांक rxe_cq_resize_queue(काष्ठा rxe_cq *cq, पूर्णांक cqe,
			काष्ठा rxe_resize_cq_resp __user *uresp,
			काष्ठा ib_udata *udata)
अणु
	पूर्णांक err;

	err = rxe_queue_resize(cq->queue, (अचिन्हित पूर्णांक *)&cqe,
			       माप(काष्ठा rxe_cqe), udata,
			       uresp ? &uresp->mi : शून्य, शून्य, &cq->cq_lock);
	अगर (!err)
		cq->ibcq.cqe = cqe;

	वापस err;
पूर्ण

पूर्णांक rxe_cq_post(काष्ठा rxe_cq *cq, काष्ठा rxe_cqe *cqe, पूर्णांक solicited)
अणु
	काष्ठा ib_event ev;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cq->cq_lock, flags);

	अगर (unlikely(queue_full(cq->queue))) अणु
		spin_unlock_irqrestore(&cq->cq_lock, flags);
		अगर (cq->ibcq.event_handler) अणु
			ev.device = cq->ibcq.device;
			ev.element.cq = &cq->ibcq;
			ev.event = IB_EVENT_CQ_ERR;
			cq->ibcq.event_handler(&ev, cq->ibcq.cq_context);
		पूर्ण

		वापस -EBUSY;
	पूर्ण

	स_नकल(producer_addr(cq->queue), cqe, माप(*cqe));

	advance_producer(cq->queue);
	spin_unlock_irqrestore(&cq->cq_lock, flags);

	अगर ((cq->notअगरy == IB_CQ_NEXT_COMP) ||
	    (cq->notअगरy == IB_CQ_SOLICITED && solicited)) अणु
		cq->notअगरy = 0;
		tasklet_schedule(&cq->comp_task);
	पूर्ण

	वापस 0;
पूर्ण

व्योम rxe_cq_disable(काष्ठा rxe_cq *cq)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&cq->cq_lock, flags);
	cq->is_dying = true;
	spin_unlock_irqrestore(&cq->cq_lock, flags);
पूर्ण

व्योम rxe_cq_cleanup(काष्ठा rxe_pool_entry *arg)
अणु
	काष्ठा rxe_cq *cq = container_of(arg, typeof(*cq), pelem);

	अगर (cq->queue)
		rxe_queue_cleanup(cq->queue);
पूर्ण
