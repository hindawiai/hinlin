<शैली गुरु>
/*
 * Copyright(c) 2016 - 2018 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
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
 */

#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश "cq.h"
#समावेश "vt.h"
#समावेश "trace.h"

अटल काष्ठा workqueue_काष्ठा *comp_vector_wq;

/**
 * rvt_cq_enter - add a new entry to the completion queue
 * @cq: completion queue
 * @entry: work completion entry to add
 * @solicited: true अगर @entry is solicited
 *
 * This may be called with qp->s_lock held.
 *
 * Return: वापस true on success, अन्यथा वापस
 * false अगर cq is full.
 */
bool rvt_cq_enter(काष्ठा rvt_cq *cq, काष्ठा ib_wc *entry, bool solicited)
अणु
	काष्ठा ib_uverbs_wc *uqueue = शून्य;
	काष्ठा ib_wc *kqueue = शून्य;
	काष्ठा rvt_cq_wc *u_wc = शून्य;
	काष्ठा rvt_k_cq_wc *k_wc = शून्य;
	अचिन्हित दीर्घ flags;
	u32 head;
	u32 next;
	u32 tail;

	spin_lock_irqsave(&cq->lock, flags);

	अगर (cq->ip) अणु
		u_wc = cq->queue;
		uqueue = &u_wc->uqueue[0];
		head = RDMA_READ_UAPI_ATOMIC(u_wc->head);
		tail = RDMA_READ_UAPI_ATOMIC(u_wc->tail);
	पूर्ण अन्यथा अणु
		k_wc = cq->kqueue;
		kqueue = &k_wc->kqueue[0];
		head = k_wc->head;
		tail = k_wc->tail;
	पूर्ण

	/*
	 * Note that the head poपूर्णांकer might be writable by
	 * user processes.Take care to verअगरy it is a sane value.
	 */
	अगर (head >= (अचिन्हित)cq->ibcq.cqe) अणु
		head = cq->ibcq.cqe;
		next = 0;
	पूर्ण अन्यथा अणु
		next = head + 1;
	पूर्ण

	अगर (unlikely(next == tail || cq->cq_full)) अणु
		काष्ठा rvt_dev_info *rdi = cq->rdi;

		अगर (!cq->cq_full)
			rvt_pr_err_ratelimited(rdi, "CQ is full!\n");
		cq->cq_full = true;
		spin_unlock_irqrestore(&cq->lock, flags);
		अगर (cq->ibcq.event_handler) अणु
			काष्ठा ib_event ev;

			ev.device = cq->ibcq.device;
			ev.element.cq = &cq->ibcq;
			ev.event = IB_EVENT_CQ_ERR;
			cq->ibcq.event_handler(&ev, cq->ibcq.cq_context);
		पूर्ण
		वापस false;
	पूर्ण
	trace_rvt_cq_enter(cq, entry, head);
	अगर (uqueue) अणु
		uqueue[head].wr_id = entry->wr_id;
		uqueue[head].status = entry->status;
		uqueue[head].opcode = entry->opcode;
		uqueue[head].venकरोr_err = entry->venकरोr_err;
		uqueue[head].byte_len = entry->byte_len;
		uqueue[head].ex.imm_data = entry->ex.imm_data;
		uqueue[head].qp_num = entry->qp->qp_num;
		uqueue[head].src_qp = entry->src_qp;
		uqueue[head].wc_flags = entry->wc_flags;
		uqueue[head].pkey_index = entry->pkey_index;
		uqueue[head].slid = ib_lid_cpu16(entry->slid);
		uqueue[head].sl = entry->sl;
		uqueue[head].dlid_path_bits = entry->dlid_path_bits;
		uqueue[head].port_num = entry->port_num;
		/* Make sure entry is written beक्रमe the head index. */
		RDMA_WRITE_UAPI_ATOMIC(u_wc->head, next);
	पूर्ण अन्यथा अणु
		kqueue[head] = *entry;
		k_wc->head = next;
	पूर्ण

	अगर (cq->notअगरy == IB_CQ_NEXT_COMP ||
	    (cq->notअगरy == IB_CQ_SOLICITED &&
	     (solicited || entry->status != IB_WC_SUCCESS))) अणु
		/*
		 * This will cause send_complete() to be called in
		 * another thपढ़ो.
		 */
		cq->notअगरy = RVT_CQ_NONE;
		cq->triggered++;
		queue_work_on(cq->comp_vector_cpu, comp_vector_wq,
			      &cq->comptask);
	पूर्ण

	spin_unlock_irqrestore(&cq->lock, flags);
	वापस true;
पूर्ण
EXPORT_SYMBOL(rvt_cq_enter);

अटल व्योम send_complete(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rvt_cq *cq = container_of(work, काष्ठा rvt_cq, comptask);

	/*
	 * The completion handler will most likely rearm the notअगरication
	 * and poll क्रम all pending entries.  If a new completion entry
	 * is added जबतक we are in this routine, queue_work()
	 * won't call us again until we वापस so we check triggered to
	 * see अगर we need to call the handler again.
	 */
	क्रम (;;) अणु
		u8 triggered = cq->triggered;

		/*
		 * IPoIB connected mode assumes the callback is from a
		 * soft IRQ. We simulate this by blocking "bottom halves".
		 * See the implementation क्रम ipoib_cm_handle_tx_wc(),
		 * netअगर_tx_lock_bh() and netअगर_tx_lock().
		 */
		local_bh_disable();
		cq->ibcq.comp_handler(&cq->ibcq, cq->ibcq.cq_context);
		local_bh_enable();

		अगर (cq->triggered == triggered)
			वापस;
	पूर्ण
पूर्ण

/**
 * rvt_create_cq - create a completion queue
 * @ibcq: Allocated CQ
 * @attr: creation attributes
 * @udata: user data क्रम libibverbs.so
 *
 * Called by ib_create_cq() in the generic verbs code.
 *
 * Return: 0 on success
 */
पूर्णांक rvt_create_cq(काष्ठा ib_cq *ibcq, स्थिर काष्ठा ib_cq_init_attr *attr,
		  काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = ibcq->device;
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(ibdev);
	काष्ठा rvt_cq *cq = ibcq_to_rvtcq(ibcq);
	काष्ठा rvt_cq_wc *u_wc = शून्य;
	काष्ठा rvt_k_cq_wc *k_wc = शून्य;
	u32 sz;
	अचिन्हित पूर्णांक entries = attr->cqe;
	पूर्णांक comp_vector = attr->comp_vector;
	पूर्णांक err;

	अगर (attr->flags)
		वापस -EOPNOTSUPP;

	अगर (entries < 1 || entries > rdi->dparms.props.max_cqe)
		वापस -EINVAL;

	अगर (comp_vector < 0)
		comp_vector = 0;

	comp_vector = comp_vector % rdi->ibdev.num_comp_vectors;

	/*
	 * Allocate the completion queue entries and head/tail poपूर्णांकers.
	 * This is allocated separately so that it can be resized and
	 * also mapped पूर्णांकo user space.
	 * We need to use vदो_स्मृति() in order to support mmap and large
	 * numbers of entries.
	 */
	अगर (udata && udata->outlen >= माप(__u64)) अणु
		sz = माप(काष्ठा ib_uverbs_wc) * (entries + 1);
		sz += माप(*u_wc);
		u_wc = vदो_स्मृति_user(sz);
		अगर (!u_wc)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		sz = माप(काष्ठा ib_wc) * (entries + 1);
		sz += माप(*k_wc);
		k_wc = vzalloc_node(sz, rdi->dparms.node);
		अगर (!k_wc)
			वापस -ENOMEM;
	पूर्ण

	/*
	 * Return the address of the WC as the offset to mmap.
	 * See rvt_mmap() क्रम details.
	 */
	अगर (udata && udata->outlen >= माप(__u64)) अणु
		cq->ip = rvt_create_mmap_info(rdi, sz, udata, u_wc);
		अगर (IS_ERR(cq->ip)) अणु
			err = PTR_ERR(cq->ip);
			जाओ bail_wc;
		पूर्ण

		err = ib_copy_to_udata(udata, &cq->ip->offset,
				       माप(cq->ip->offset));
		अगर (err)
			जाओ bail_ip;
	पूर्ण

	spin_lock_irq(&rdi->n_cqs_lock);
	अगर (rdi->n_cqs_allocated == rdi->dparms.props.max_cq) अणु
		spin_unlock_irq(&rdi->n_cqs_lock);
		err = -ENOMEM;
		जाओ bail_ip;
	पूर्ण

	rdi->n_cqs_allocated++;
	spin_unlock_irq(&rdi->n_cqs_lock);

	अगर (cq->ip) अणु
		spin_lock_irq(&rdi->pending_lock);
		list_add(&cq->ip->pending_mmaps, &rdi->pending_mmaps);
		spin_unlock_irq(&rdi->pending_lock);
	पूर्ण

	/*
	 * ib_create_cq() will initialize cq->ibcq except क्रम cq->ibcq.cqe.
	 * The number of entries should be >= the number requested or वापस
	 * an error.
	 */
	cq->rdi = rdi;
	अगर (rdi->driver_f.comp_vect_cpu_lookup)
		cq->comp_vector_cpu =
			rdi->driver_f.comp_vect_cpu_lookup(rdi, comp_vector);
	अन्यथा
		cq->comp_vector_cpu =
			cpumask_first(cpumask_of_node(rdi->dparms.node));

	cq->ibcq.cqe = entries;
	cq->notअगरy = RVT_CQ_NONE;
	spin_lock_init(&cq->lock);
	INIT_WORK(&cq->comptask, send_complete);
	अगर (u_wc)
		cq->queue = u_wc;
	अन्यथा
		cq->kqueue = k_wc;

	trace_rvt_create_cq(cq, attr);
	वापस 0;

bail_ip:
	kमुक्त(cq->ip);
bail_wc:
	vमुक्त(u_wc);
	vमुक्त(k_wc);
	वापस err;
पूर्ण

/**
 * rvt_destroy_cq - destroy a completion queue
 * @ibcq: the completion queue to destroy.
 * @udata: user data or शून्य क्रम kernel object
 *
 * Called by ib_destroy_cq() in the generic verbs code.
 */
पूर्णांक rvt_destroy_cq(काष्ठा ib_cq *ibcq, काष्ठा ib_udata *udata)
अणु
	काष्ठा rvt_cq *cq = ibcq_to_rvtcq(ibcq);
	काष्ठा rvt_dev_info *rdi = cq->rdi;

	flush_work(&cq->comptask);
	spin_lock_irq(&rdi->n_cqs_lock);
	rdi->n_cqs_allocated--;
	spin_unlock_irq(&rdi->n_cqs_lock);
	अगर (cq->ip)
		kref_put(&cq->ip->ref, rvt_release_mmap_info);
	अन्यथा
		vमुक्त(cq->kqueue);
	वापस 0;
पूर्ण

/**
 * rvt_req_notअगरy_cq - change the notअगरication type क्रम a completion queue
 * @ibcq: the completion queue
 * @notअगरy_flags: the type of notअगरication to request
 *
 * This may be called from पूर्णांकerrupt context.  Also called by
 * ib_req_notअगरy_cq() in the generic verbs code.
 *
 * Return: 0 क्रम success.
 */
पूर्णांक rvt_req_notअगरy_cq(काष्ठा ib_cq *ibcq, क्रमागत ib_cq_notअगरy_flags notअगरy_flags)
अणु
	काष्ठा rvt_cq *cq = ibcq_to_rvtcq(ibcq);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&cq->lock, flags);
	/*
	 * Don't change IB_CQ_NEXT_COMP to IB_CQ_SOLICITED but allow
	 * any other transitions (see C11-31 and C11-32 in ch. 11.4.2.2).
	 */
	अगर (cq->notअगरy != IB_CQ_NEXT_COMP)
		cq->notअगरy = notअगरy_flags & IB_CQ_SOLICITED_MASK;

	अगर (notअगरy_flags & IB_CQ_REPORT_MISSED_EVENTS) अणु
		अगर (cq->queue) अणु
			अगर (RDMA_READ_UAPI_ATOMIC(cq->queue->head) !=
				RDMA_READ_UAPI_ATOMIC(cq->queue->tail))
				ret = 1;
		पूर्ण अन्यथा अणु
			अगर (cq->kqueue->head != cq->kqueue->tail)
				ret = 1;
		पूर्ण
	पूर्ण

	spin_unlock_irqrestore(&cq->lock, flags);

	वापस ret;
पूर्ण

/*
 * rvt_resize_cq - change the size of the CQ
 * @ibcq: the completion queue
 *
 * Return: 0 क्रम success.
 */
पूर्णांक rvt_resize_cq(काष्ठा ib_cq *ibcq, पूर्णांक cqe, काष्ठा ib_udata *udata)
अणु
	काष्ठा rvt_cq *cq = ibcq_to_rvtcq(ibcq);
	u32 head, tail, n;
	पूर्णांक ret;
	u32 sz;
	काष्ठा rvt_dev_info *rdi = cq->rdi;
	काष्ठा rvt_cq_wc *u_wc = शून्य;
	काष्ठा rvt_cq_wc *old_u_wc = शून्य;
	काष्ठा rvt_k_cq_wc *k_wc = शून्य;
	काष्ठा rvt_k_cq_wc *old_k_wc = शून्य;

	अगर (cqe < 1 || cqe > rdi->dparms.props.max_cqe)
		वापस -EINVAL;

	/*
	 * Need to use vदो_स्मृति() अगर we want to support large #s of entries.
	 */
	अगर (udata && udata->outlen >= माप(__u64)) अणु
		sz = माप(काष्ठा ib_uverbs_wc) * (cqe + 1);
		sz += माप(*u_wc);
		u_wc = vदो_स्मृति_user(sz);
		अगर (!u_wc)
			वापस -ENOMEM;
	पूर्ण अन्यथा अणु
		sz = माप(काष्ठा ib_wc) * (cqe + 1);
		sz += माप(*k_wc);
		k_wc = vzalloc_node(sz, rdi->dparms.node);
		अगर (!k_wc)
			वापस -ENOMEM;
	पूर्ण
	/* Check that we can ग_लिखो the offset to mmap. */
	अगर (udata && udata->outlen >= माप(__u64)) अणु
		__u64 offset = 0;

		ret = ib_copy_to_udata(udata, &offset, माप(offset));
		अगर (ret)
			जाओ bail_मुक्त;
	पूर्ण

	spin_lock_irq(&cq->lock);
	/*
	 * Make sure head and tail are sane since they
	 * might be user writable.
	 */
	अगर (u_wc) अणु
		old_u_wc = cq->queue;
		head = RDMA_READ_UAPI_ATOMIC(old_u_wc->head);
		tail = RDMA_READ_UAPI_ATOMIC(old_u_wc->tail);
	पूर्ण अन्यथा अणु
		old_k_wc = cq->kqueue;
		head = old_k_wc->head;
		tail = old_k_wc->tail;
	पूर्ण

	अगर (head > (u32)cq->ibcq.cqe)
		head = (u32)cq->ibcq.cqe;
	अगर (tail > (u32)cq->ibcq.cqe)
		tail = (u32)cq->ibcq.cqe;
	अगर (head < tail)
		n = cq->ibcq.cqe + 1 + head - tail;
	अन्यथा
		n = head - tail;
	अगर (unlikely((u32)cqe < n)) अणु
		ret = -EINVAL;
		जाओ bail_unlock;
	पूर्ण
	क्रम (n = 0; tail != head; n++) अणु
		अगर (u_wc)
			u_wc->uqueue[n] = old_u_wc->uqueue[tail];
		अन्यथा
			k_wc->kqueue[n] = old_k_wc->kqueue[tail];
		अगर (tail == (u32)cq->ibcq.cqe)
			tail = 0;
		अन्यथा
			tail++;
	पूर्ण
	cq->ibcq.cqe = cqe;
	अगर (u_wc) अणु
		RDMA_WRITE_UAPI_ATOMIC(u_wc->head, n);
		RDMA_WRITE_UAPI_ATOMIC(u_wc->tail, 0);
		cq->queue = u_wc;
	पूर्ण अन्यथा अणु
		k_wc->head = n;
		k_wc->tail = 0;
		cq->kqueue = k_wc;
	पूर्ण
	spin_unlock_irq(&cq->lock);

	अगर (u_wc)
		vमुक्त(old_u_wc);
	अन्यथा
		vमुक्त(old_k_wc);

	अगर (cq->ip) अणु
		काष्ठा rvt_mmap_info *ip = cq->ip;

		rvt_update_mmap_info(rdi, ip, sz, u_wc);

		/*
		 * Return the offset to mmap.
		 * See rvt_mmap() क्रम details.
		 */
		अगर (udata && udata->outlen >= माप(__u64)) अणु
			ret = ib_copy_to_udata(udata, &ip->offset,
					       माप(ip->offset));
			अगर (ret)
				वापस ret;
		पूर्ण

		spin_lock_irq(&rdi->pending_lock);
		अगर (list_empty(&ip->pending_mmaps))
			list_add(&ip->pending_mmaps, &rdi->pending_mmaps);
		spin_unlock_irq(&rdi->pending_lock);
	पूर्ण

	वापस 0;

bail_unlock:
	spin_unlock_irq(&cq->lock);
bail_मुक्त:
	vमुक्त(u_wc);
	vमुक्त(k_wc);

	वापस ret;
पूर्ण

/**
 * rvt_poll_cq - poll क्रम work completion entries
 * @ibcq: the completion queue to poll
 * @num_entries: the maximum number of entries to वापस
 * @entry: poपूर्णांकer to array where work completions are placed
 *
 * This may be called from पूर्णांकerrupt context.  Also called by ib_poll_cq()
 * in the generic verbs code.
 *
 * Return: the number of completion entries polled.
 */
पूर्णांक rvt_poll_cq(काष्ठा ib_cq *ibcq, पूर्णांक num_entries, काष्ठा ib_wc *entry)
अणु
	काष्ठा rvt_cq *cq = ibcq_to_rvtcq(ibcq);
	काष्ठा rvt_k_cq_wc *wc;
	अचिन्हित दीर्घ flags;
	पूर्णांक npolled;
	u32 tail;

	/* The kernel can only poll a kernel completion queue */
	अगर (cq->ip)
		वापस -EINVAL;

	spin_lock_irqsave(&cq->lock, flags);

	wc = cq->kqueue;
	tail = wc->tail;
	अगर (tail > (u32)cq->ibcq.cqe)
		tail = (u32)cq->ibcq.cqe;
	क्रम (npolled = 0; npolled < num_entries; ++npolled, ++entry) अणु
		अगर (tail == wc->head)
			अवरोध;
		/* The kernel करोesn't need a RMB since it has the lock. */
		trace_rvt_cq_poll(cq, &wc->kqueue[tail], npolled);
		*entry = wc->kqueue[tail];
		अगर (tail >= cq->ibcq.cqe)
			tail = 0;
		अन्यथा
			tail++;
	पूर्ण
	wc->tail = tail;

	spin_unlock_irqrestore(&cq->lock, flags);

	वापस npolled;
पूर्ण

/**
 * rvt_driver_cq_init - Init cq resources on behalf of driver
 *
 * Return: 0 on success
 */
पूर्णांक rvt_driver_cq_init(व्योम)
अणु
	comp_vector_wq = alloc_workqueue("%s", WQ_HIGHPRI | WQ_CPU_INTENSIVE,
					 0, "rdmavt_cq");
	अगर (!comp_vector_wq)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/**
 * rvt_cq_निकास - tear करोwn cq reources
 */
व्योम rvt_cq_निकास(व्योम)
अणु
	destroy_workqueue(comp_vector_wq);
	comp_vector_wq = शून्य;
पूर्ण
