<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 HGST, a Western Digital Company.
 */
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <rdma/ib_verbs.h>

#समावेश "core_priv.h"

#समावेश <trace/events/rdma_core.h>
/* Max size क्रम shared CQ, may require tuning */
#घोषणा IB_MAX_SHARED_CQ_SZ		4096U

/* # of WCs to poll क्रम with a single call to ib_poll_cq */
#घोषणा IB_POLL_BATCH			16
#घोषणा IB_POLL_BATCH_सूचीECT		8

/* # of WCs to iterate over beक्रमe yielding */
#घोषणा IB_POLL_BUDGET_IRQ		256
#घोषणा IB_POLL_BUDGET_WORKQUEUE	65536

#घोषणा IB_POLL_FLAGS \
	(IB_CQ_NEXT_COMP | IB_CQ_REPORT_MISSED_EVENTS)

अटल स्थिर काष्ठा dim_cq_moder
rdma_dim_prof[RDMA_DIM_PARAMS_NUM_PROखाताS] = अणु
	अणु1,   0, 1,  0पूर्ण,
	अणु1,   0, 4,  0पूर्ण,
	अणु2,   0, 4,  0पूर्ण,
	अणु2,   0, 8,  0पूर्ण,
	अणु4,   0, 8,  0पूर्ण,
	अणु16,  0, 8,  0पूर्ण,
	अणु16,  0, 16, 0पूर्ण,
	अणु32,  0, 16, 0पूर्ण,
	अणु32,  0, 32, 0पूर्ण,
पूर्ण;

अटल व्योम ib_cq_rdma_dim_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा dim *dim = container_of(w, काष्ठा dim, work);
	काष्ठा ib_cq *cq = dim->priv;

	u16 usec = rdma_dim_prof[dim->profile_ix].usec;
	u16 comps = rdma_dim_prof[dim->profile_ix].comps;

	dim->state = DIM_START_MEASURE;

	trace_cq_modअगरy(cq, comps, usec);
	cq->device->ops.modअगरy_cq(cq, comps, usec);
पूर्ण

अटल व्योम rdma_dim_init(काष्ठा ib_cq *cq)
अणु
	काष्ठा dim *dim;

	अगर (!cq->device->ops.modअगरy_cq || !cq->device->use_cq_dim ||
	    cq->poll_ctx == IB_POLL_सूचीECT)
		वापस;

	dim = kzalloc(माप(काष्ठा dim), GFP_KERNEL);
	अगर (!dim)
		वापस;

	dim->state = DIM_START_MEASURE;
	dim->tune_state = DIM_GOING_RIGHT;
	dim->profile_ix = RDMA_DIM_START_PROखाता;
	dim->priv = cq;
	cq->dim = dim;

	INIT_WORK(&dim->work, ib_cq_rdma_dim_work);
पूर्ण

अटल व्योम rdma_dim_destroy(काष्ठा ib_cq *cq)
अणु
	अगर (!cq->dim)
		वापस;

	cancel_work_sync(&cq->dim->work);
	kमुक्त(cq->dim);
पूर्ण

अटल पूर्णांक __poll_cq(काष्ठा ib_cq *cq, पूर्णांक num_entries, काष्ठा ib_wc *wc)
अणु
	पूर्णांक rc;

	rc = ib_poll_cq(cq, num_entries, wc);
	trace_cq_poll(cq, num_entries, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक __ib_process_cq(काष्ठा ib_cq *cq, पूर्णांक budget, काष्ठा ib_wc *wcs,
			   पूर्णांक batch)
अणु
	पूर्णांक i, n, completed = 0;

	trace_cq_process(cq);

	/*
	 * budget might be (-1) अगर the caller करोes not
	 * want to bound this call, thus we need अचिन्हित
	 * minimum here.
	 */
	जबतक ((n = __poll_cq(cq, min_t(u32, batch,
					budget - completed), wcs)) > 0) अणु
		क्रम (i = 0; i < n; i++) अणु
			काष्ठा ib_wc *wc = &wcs[i];

			अगर (wc->wr_cqe)
				wc->wr_cqe->करोne(cq, wc);
			अन्यथा
				WARN_ON_ONCE(wc->status == IB_WC_SUCCESS);
		पूर्ण

		completed += n;

		अगर (n != batch || (budget != -1 && completed >= budget))
			अवरोध;
	पूर्ण

	वापस completed;
पूर्ण

/**
 * ib_process_cq_direct - process a CQ in caller context
 * @cq:		CQ to process
 * @budget:	number of CQEs to poll क्रम
 *
 * This function is used to process all outstanding CQ entries.
 * It करोes not offload CQ processing to a dअगरferent context and करोes
 * not ask क्रम completion पूर्णांकerrupts from the HCA.
 * Using direct processing on CQ with non IB_POLL_सूचीECT type may trigger
 * concurrent processing.
 *
 * Note: करो not pass -1 as %budget unless it is guaranteed that the number
 * of completions that will be processed is small.
 */
पूर्णांक ib_process_cq_direct(काष्ठा ib_cq *cq, पूर्णांक budget)
अणु
	काष्ठा ib_wc wcs[IB_POLL_BATCH_सूचीECT];

	वापस __ib_process_cq(cq, budget, wcs, IB_POLL_BATCH_सूचीECT);
पूर्ण
EXPORT_SYMBOL(ib_process_cq_direct);

अटल व्योम ib_cq_completion_direct(काष्ठा ib_cq *cq, व्योम *निजी)
अणु
	WARN_ONCE(1, "got unsolicited completion for CQ 0x%p\n", cq);
पूर्ण

अटल पूर्णांक ib_poll_handler(काष्ठा irq_poll *iop, पूर्णांक budget)
अणु
	काष्ठा ib_cq *cq = container_of(iop, काष्ठा ib_cq, iop);
	काष्ठा dim *dim = cq->dim;
	पूर्णांक completed;

	completed = __ib_process_cq(cq, budget, cq->wc, IB_POLL_BATCH);
	अगर (completed < budget) अणु
		irq_poll_complete(&cq->iop);
		अगर (ib_req_notअगरy_cq(cq, IB_POLL_FLAGS) > 0) अणु
			trace_cq_reschedule(cq);
			irq_poll_sched(&cq->iop);
		पूर्ण
	पूर्ण

	अगर (dim)
		rdma_dim(dim, completed);

	वापस completed;
पूर्ण

अटल व्योम ib_cq_completion_softirq(काष्ठा ib_cq *cq, व्योम *निजी)
अणु
	trace_cq_schedule(cq);
	irq_poll_sched(&cq->iop);
पूर्ण

अटल व्योम ib_cq_poll_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ib_cq *cq = container_of(work, काष्ठा ib_cq, work);
	पूर्णांक completed;

	completed = __ib_process_cq(cq, IB_POLL_BUDGET_WORKQUEUE, cq->wc,
				    IB_POLL_BATCH);
	अगर (completed >= IB_POLL_BUDGET_WORKQUEUE ||
	    ib_req_notअगरy_cq(cq, IB_POLL_FLAGS) > 0)
		queue_work(cq->comp_wq, &cq->work);
	अन्यथा अगर (cq->dim)
		rdma_dim(cq->dim, completed);
पूर्ण

अटल व्योम ib_cq_completion_workqueue(काष्ठा ib_cq *cq, व्योम *निजी)
अणु
	trace_cq_schedule(cq);
	queue_work(cq->comp_wq, &cq->work);
पूर्ण

/**
 * __ib_alloc_cq - allocate a completion queue
 * @dev:		device to allocate the CQ क्रम
 * @निजी:		driver निजी data, accessible from cq->cq_context
 * @nr_cqe:		number of CQEs to allocate
 * @comp_vector:	HCA completion vectors क्रम this CQ
 * @poll_ctx:		context to poll the CQ from.
 * @caller:		module owner name.
 *
 * This is the proper पूर्णांकerface to allocate a CQ क्रम in-kernel users. A
 * CQ allocated with this पूर्णांकerface will स्वतःmatically be polled from the
 * specअगरied context. The ULP must use wr->wr_cqe instead of wr->wr_id
 * to use this CQ असलtraction.
 */
काष्ठा ib_cq *__ib_alloc_cq(काष्ठा ib_device *dev, व्योम *निजी, पूर्णांक nr_cqe,
			    पूर्णांक comp_vector, क्रमागत ib_poll_context poll_ctx,
			    स्थिर अक्षर *caller)
अणु
	काष्ठा ib_cq_init_attr cq_attr = अणु
		.cqe		= nr_cqe,
		.comp_vector	= comp_vector,
	पूर्ण;
	काष्ठा ib_cq *cq;
	पूर्णांक ret = -ENOMEM;

	cq = rdma_zalloc_drv_obj(dev, ib_cq);
	अगर (!cq)
		वापस ERR_PTR(ret);

	cq->device = dev;
	cq->cq_context = निजी;
	cq->poll_ctx = poll_ctx;
	atomic_set(&cq->usecnt, 0);
	cq->comp_vector = comp_vector;

	cq->wc = kदो_स्मृति_array(IB_POLL_BATCH, माप(*cq->wc), GFP_KERNEL);
	अगर (!cq->wc)
		जाओ out_मुक्त_cq;

	rdma_restrack_new(&cq->res, RDMA_RESTRACK_CQ);
	rdma_restrack_set_name(&cq->res, caller);

	ret = dev->ops.create_cq(cq, &cq_attr, शून्य);
	अगर (ret)
		जाओ out_मुक्त_wc;

	rdma_dim_init(cq);

	चयन (cq->poll_ctx) अणु
	हाल IB_POLL_सूचीECT:
		cq->comp_handler = ib_cq_completion_direct;
		अवरोध;
	हाल IB_POLL_SOFTIRQ:
		cq->comp_handler = ib_cq_completion_softirq;

		irq_poll_init(&cq->iop, IB_POLL_BUDGET_IRQ, ib_poll_handler);
		ib_req_notअगरy_cq(cq, IB_CQ_NEXT_COMP);
		अवरोध;
	हाल IB_POLL_WORKQUEUE:
	हाल IB_POLL_UNBOUND_WORKQUEUE:
		cq->comp_handler = ib_cq_completion_workqueue;
		INIT_WORK(&cq->work, ib_cq_poll_work);
		ib_req_notअगरy_cq(cq, IB_CQ_NEXT_COMP);
		cq->comp_wq = (cq->poll_ctx == IB_POLL_WORKQUEUE) ?
				ib_comp_wq : ib_comp_unbound_wq;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ out_destroy_cq;
	पूर्ण

	rdma_restrack_add(&cq->res);
	trace_cq_alloc(cq, nr_cqe, comp_vector, poll_ctx);
	वापस cq;

out_destroy_cq:
	rdma_dim_destroy(cq);
	cq->device->ops.destroy_cq(cq, शून्य);
out_मुक्त_wc:
	rdma_restrack_put(&cq->res);
	kमुक्त(cq->wc);
out_मुक्त_cq:
	kमुक्त(cq);
	trace_cq_alloc_error(nr_cqe, comp_vector, poll_ctx, ret);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL(__ib_alloc_cq);

/**
 * __ib_alloc_cq_any - allocate a completion queue
 * @dev:		device to allocate the CQ क्रम
 * @निजी:		driver निजी data, accessible from cq->cq_context
 * @nr_cqe:		number of CQEs to allocate
 * @poll_ctx:		context to poll the CQ from
 * @caller:		module owner name
 *
 * Attempt to spपढ़ो ULP Completion Queues over each device's पूर्णांकerrupt
 * vectors. A simple best-efक्रमt mechanism is used.
 */
काष्ठा ib_cq *__ib_alloc_cq_any(काष्ठा ib_device *dev, व्योम *निजी,
				पूर्णांक nr_cqe, क्रमागत ib_poll_context poll_ctx,
				स्थिर अक्षर *caller)
अणु
	अटल atomic_t counter;
	पूर्णांक comp_vector = 0;

	अगर (dev->num_comp_vectors > 1)
		comp_vector =
			atomic_inc_वापस(&counter) %
			min_t(पूर्णांक, dev->num_comp_vectors, num_online_cpus());

	वापस __ib_alloc_cq(dev, निजी, nr_cqe, comp_vector, poll_ctx,
			     caller);
पूर्ण
EXPORT_SYMBOL(__ib_alloc_cq_any);

/**
 * ib_मुक्त_cq - मुक्त a completion queue
 * @cq:		completion queue to मुक्त.
 */
व्योम ib_मुक्त_cq(काष्ठा ib_cq *cq)
अणु
	पूर्णांक ret;

	अगर (WARN_ON_ONCE(atomic_पढ़ो(&cq->usecnt)))
		वापस;
	अगर (WARN_ON_ONCE(cq->cqe_used))
		वापस;

	चयन (cq->poll_ctx) अणु
	हाल IB_POLL_सूचीECT:
		अवरोध;
	हाल IB_POLL_SOFTIRQ:
		irq_poll_disable(&cq->iop);
		अवरोध;
	हाल IB_POLL_WORKQUEUE:
	हाल IB_POLL_UNBOUND_WORKQUEUE:
		cancel_work_sync(&cq->work);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण

	rdma_dim_destroy(cq);
	trace_cq_मुक्त(cq);
	ret = cq->device->ops.destroy_cq(cq, शून्य);
	WARN_ONCE(ret, "Destroy of kernel CQ shouldn't fail");
	rdma_restrack_del(&cq->res);
	kमुक्त(cq->wc);
	kमुक्त(cq);
पूर्ण
EXPORT_SYMBOL(ib_मुक्त_cq);

व्योम ib_cq_pool_cleanup(काष्ठा ib_device *dev)
अणु
	काष्ठा ib_cq *cq, *n;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dev->cq_pools); i++) अणु
		list_क्रम_each_entry_safe(cq, n, &dev->cq_pools[i],
					 pool_entry) अणु
			WARN_ON(cq->cqe_used);
			list_del(&cq->pool_entry);
			cq->shared = false;
			ib_मुक्त_cq(cq);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ib_alloc_cqs(काष्ठा ib_device *dev, अचिन्हित पूर्णांक nr_cqes,
			क्रमागत ib_poll_context poll_ctx)
अणु
	LIST_HEAD(पंचांगp_list);
	अचिन्हित पूर्णांक nr_cqs, i;
	काष्ठा ib_cq *cq, *n;
	पूर्णांक ret;

	अगर (poll_ctx > IB_POLL_LAST_POOL_TYPE) अणु
		WARN_ON_ONCE(poll_ctx > IB_POLL_LAST_POOL_TYPE);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Allocate at least as many CQEs as requested, and otherwise
	 * a reasonable batch size so that we can share CQs between
	 * multiple users instead of allocating a larger number of CQs.
	 */
	nr_cqes = min_t(अचिन्हित पूर्णांक, dev->attrs.max_cqe,
			max(nr_cqes, IB_MAX_SHARED_CQ_SZ));
	nr_cqs = min_t(अचिन्हित पूर्णांक, dev->num_comp_vectors, num_online_cpus());
	क्रम (i = 0; i < nr_cqs; i++) अणु
		cq = ib_alloc_cq(dev, शून्य, nr_cqes, i, poll_ctx);
		अगर (IS_ERR(cq)) अणु
			ret = PTR_ERR(cq);
			जाओ out_मुक्त_cqs;
		पूर्ण
		cq->shared = true;
		list_add_tail(&cq->pool_entry, &पंचांगp_list);
	पूर्ण

	spin_lock_irq(&dev->cq_pools_lock);
	list_splice(&पंचांगp_list, &dev->cq_pools[poll_ctx]);
	spin_unlock_irq(&dev->cq_pools_lock);

	वापस 0;

out_मुक्त_cqs:
	list_क्रम_each_entry_safe(cq, n, &पंचांगp_list, pool_entry) अणु
		cq->shared = false;
		ib_मुक्त_cq(cq);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * ib_cq_pool_get() - Find the least used completion queue that matches
 *   a given cpu hपूर्णांक (or least used क्रम wild card affinity) and fits
 *   nr_cqe.
 * @dev: rdma device
 * @nr_cqe: number of needed cqe entries
 * @comp_vector_hपूर्णांक: completion vector hपूर्णांक (-1) क्रम the driver to assign
 *   a comp vector based on पूर्णांकernal counter
 * @poll_ctx: cq polling context
 *
 * Finds a cq that satisfies @comp_vector_hपूर्णांक and @nr_cqe requirements and
 * claim entries in it क्रम us.  In हाल there is no available cq, allocate
 * a new cq with the requirements and add it to the device pool.
 * IB_POLL_सूचीECT cannot be used क्रम shared cqs so it is not a valid value
 * क्रम @poll_ctx.
 */
काष्ठा ib_cq *ib_cq_pool_get(काष्ठा ib_device *dev, अचिन्हित पूर्णांक nr_cqe,
			     पूर्णांक comp_vector_hपूर्णांक,
			     क्रमागत ib_poll_context poll_ctx)
अणु
	अटल अचिन्हित पूर्णांक शेष_comp_vector;
	अचिन्हित पूर्णांक vector, num_comp_vectors;
	काष्ठा ib_cq *cq, *found = शून्य;
	पूर्णांक ret;

	अगर (poll_ctx > IB_POLL_LAST_POOL_TYPE) अणु
		WARN_ON_ONCE(poll_ctx > IB_POLL_LAST_POOL_TYPE);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	num_comp_vectors =
		min_t(अचिन्हित पूर्णांक, dev->num_comp_vectors, num_online_cpus());
	/* Project the affपूर्णांकy to the device completion vector range */
	अगर (comp_vector_hपूर्णांक < 0) अणु
		comp_vector_hपूर्णांक =
			(READ_ONCE(शेष_comp_vector) + 1) % num_comp_vectors;
		WRITE_ONCE(शेष_comp_vector, comp_vector_hपूर्णांक);
	पूर्ण
	vector = comp_vector_hपूर्णांक % num_comp_vectors;

	/*
	 * Find the least used CQ with correct affinity and
	 * enough मुक्त CQ entries
	 */
	जबतक (!found) अणु
		spin_lock_irq(&dev->cq_pools_lock);
		list_क्रम_each_entry(cq, &dev->cq_pools[poll_ctx],
				    pool_entry) अणु
			/*
			 * Check to see अगर we have found a CQ with the
			 * correct completion vector
			 */
			अगर (vector != cq->comp_vector)
				जारी;
			अगर (cq->cqe_used + nr_cqe > cq->cqe)
				जारी;
			found = cq;
			अवरोध;
		पूर्ण

		अगर (found) अणु
			found->cqe_used += nr_cqe;
			spin_unlock_irq(&dev->cq_pools_lock);

			वापस found;
		पूर्ण
		spin_unlock_irq(&dev->cq_pools_lock);

		/*
		 * Didn't find a match or ran out of CQs in the device
		 * pool, allocate a new array of CQs.
		 */
		ret = ib_alloc_cqs(dev, nr_cqe, poll_ctx);
		अगर (ret)
			वापस ERR_PTR(ret);
	पूर्ण

	वापस found;
पूर्ण
EXPORT_SYMBOL(ib_cq_pool_get);

/**
 * ib_cq_pool_put - Return a CQ taken from a shared pool.
 * @cq: The CQ to वापस.
 * @nr_cqe: The max number of cqes that the user had requested.
 */
व्योम ib_cq_pool_put(काष्ठा ib_cq *cq, अचिन्हित पूर्णांक nr_cqe)
अणु
	अगर (WARN_ON_ONCE(nr_cqe > cq->cqe_used))
		वापस;

	spin_lock_irq(&cq->device->cq_pools_lock);
	cq->cqe_used -= nr_cqe;
	spin_unlock_irq(&cq->device->cq_pools_lock);
पूर्ण
EXPORT_SYMBOL(ib_cq_pool_put);
