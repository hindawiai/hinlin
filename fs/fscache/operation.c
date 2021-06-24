<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* FS-Cache worker operation management routines
 *
 * Copyright (C) 2008 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * See Documentation/fileप्रणालीs/caching/operations.rst
 */

#घोषणा FSCACHE_DEBUG_LEVEL OPERATION
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश "internal.h"

atomic_t fscache_op_debug_id;
EXPORT_SYMBOL(fscache_op_debug_id);

अटल व्योम fscache_operation_dummy_cancel(काष्ठा fscache_operation *op)
अणु
पूर्ण

/**
 * fscache_operation_init - Do basic initialisation of an operation
 * @op: The operation to initialise
 * @release: The release function to assign
 *
 * Do basic initialisation of an operation.  The caller must still set flags,
 * object and processor अगर needed.
 */
व्योम fscache_operation_init(काष्ठा fscache_cookie *cookie,
			    काष्ठा fscache_operation *op,
			    fscache_operation_processor_t processor,
			    fscache_operation_cancel_t cancel,
			    fscache_operation_release_t release)
अणु
	INIT_WORK(&op->work, fscache_op_work_func);
	atomic_set(&op->usage, 1);
	op->state = FSCACHE_OP_ST_INITIALISED;
	op->debug_id = atomic_inc_वापस(&fscache_op_debug_id);
	op->processor = processor;
	op->cancel = cancel ?: fscache_operation_dummy_cancel;
	op->release = release;
	INIT_LIST_HEAD(&op->pend_link);
	fscache_stat(&fscache_n_op_initialised);
	trace_fscache_op(cookie, op, fscache_op_init);
पूर्ण
EXPORT_SYMBOL(fscache_operation_init);

/**
 * fscache_enqueue_operation - Enqueue an operation क्रम processing
 * @op: The operation to enqueue
 *
 * Enqueue an operation क्रम processing by the FS-Cache thपढ़ो pool.
 *
 * This will get its own ref on the object.
 */
व्योम fscache_enqueue_operation(काष्ठा fscache_operation *op)
अणु
	काष्ठा fscache_cookie *cookie = op->object->cookie;
	
	_enter("{OBJ%x OP%x,%u}",
	       op->object->debug_id, op->debug_id, atomic_पढ़ो(&op->usage));

	ASSERT(list_empty(&op->pend_link));
	ASSERT(op->processor != शून्य);
	ASSERT(fscache_object_is_available(op->object));
	ASSERTCMP(atomic_पढ़ो(&op->usage), >, 0);
	ASSERTIFCMP(op->state != FSCACHE_OP_ST_IN_PROGRESS,
		    op->state, ==,  FSCACHE_OP_ST_CANCELLED);

	fscache_stat(&fscache_n_op_enqueue);
	चयन (op->flags & FSCACHE_OP_TYPE) अणु
	हाल FSCACHE_OP_ASYNC:
		trace_fscache_op(cookie, op, fscache_op_enqueue_async);
		_debug("queue async");
		atomic_inc(&op->usage);
		अगर (!queue_work(fscache_op_wq, &op->work))
			fscache_put_operation(op);
		अवरोध;
	हाल FSCACHE_OP_MYTHREAD:
		trace_fscache_op(cookie, op, fscache_op_enqueue_mythपढ़ो);
		_debug("queue for caller's attention");
		अवरोध;
	शेष:
		pr_err("Unexpected op type %lx", op->flags);
		BUG();
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(fscache_enqueue_operation);

/*
 * start an op running
 */
अटल व्योम fscache_run_op(काष्ठा fscache_object *object,
			   काष्ठा fscache_operation *op)
अणु
	ASSERTCMP(op->state, ==, FSCACHE_OP_ST_PENDING);

	op->state = FSCACHE_OP_ST_IN_PROGRESS;
	object->n_in_progress++;
	अगर (test_and_clear_bit(FSCACHE_OP_WAITING, &op->flags))
		wake_up_bit(&op->flags, FSCACHE_OP_WAITING);
	अगर (op->processor)
		fscache_enqueue_operation(op);
	अन्यथा
		trace_fscache_op(object->cookie, op, fscache_op_run);
	fscache_stat(&fscache_n_op_run);
पूर्ण

/*
 * report an unexpected submission
 */
अटल व्योम fscache_report_unexpected_submission(काष्ठा fscache_object *object,
						 काष्ठा fscache_operation *op,
						 स्थिर काष्ठा fscache_state *ostate)
अणु
	अटल bool once_only;
	काष्ठा fscache_operation *p;
	अचिन्हित n;

	अगर (once_only)
		वापस;
	once_only = true;

	kdebug("unexpected submission OP%x [OBJ%x %s]",
	       op->debug_id, object->debug_id, object->state->name);
	kdebug("objstate=%s [%s]", object->state->name, ostate->name);
	kdebug("objflags=%lx", object->flags);
	kdebug("objevent=%lx [%lx]", object->events, object->event_mask);
	kdebug("ops=%u inp=%u exc=%u",
	       object->n_ops, object->n_in_progress, object->n_exclusive);

	अगर (!list_empty(&object->pending_ops)) अणु
		n = 0;
		list_क्रम_each_entry(p, &object->pending_ops, pend_link) अणु
			ASSERTCMP(p->object, ==, object);
			kdebug("%p %p", op->processor, op->release);
			n++;
		पूर्ण

		kdebug("n=%u", n);
	पूर्ण

	dump_stack();
पूर्ण

/*
 * submit an exclusive operation क्रम an object
 * - other ops are excluded from running simultaneously with this one
 * - this माला_लो any extra refs it needs on an op
 */
पूर्णांक fscache_submit_exclusive_op(काष्ठा fscache_object *object,
				काष्ठा fscache_operation *op)
अणु
	स्थिर काष्ठा fscache_state *ostate;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	_enter("{OBJ%x OP%x},", object->debug_id, op->debug_id);

	trace_fscache_op(object->cookie, op, fscache_op_submit_ex);

	ASSERTCMP(op->state, ==, FSCACHE_OP_ST_INITIALISED);
	ASSERTCMP(atomic_पढ़ो(&op->usage), >, 0);

	spin_lock(&object->lock);
	ASSERTCMP(object->n_ops, >=, object->n_in_progress);
	ASSERTCMP(object->n_ops, >=, object->n_exclusive);
	ASSERT(list_empty(&op->pend_link));

	ostate = object->state;
	smp_rmb();

	op->state = FSCACHE_OP_ST_PENDING;
	flags = READ_ONCE(object->flags);
	अगर (unlikely(!(flags & BIT(FSCACHE_OBJECT_IS_LIVE)))) अणु
		fscache_stat(&fscache_n_op_rejected);
		op->cancel(op);
		op->state = FSCACHE_OP_ST_CANCELLED;
		ret = -ENOBUFS;
	पूर्ण अन्यथा अगर (unlikely(fscache_cache_is_broken(object))) अणु
		op->cancel(op);
		op->state = FSCACHE_OP_ST_CANCELLED;
		ret = -EIO;
	पूर्ण अन्यथा अगर (flags & BIT(FSCACHE_OBJECT_IS_AVAILABLE)) अणु
		op->object = object;
		object->n_ops++;
		object->n_exclusive++;	/* पढ़ोs and ग_लिखोs must रुको */

		अगर (object->n_in_progress > 0) अणु
			atomic_inc(&op->usage);
			list_add_tail(&op->pend_link, &object->pending_ops);
			fscache_stat(&fscache_n_op_pend);
		पूर्ण अन्यथा अगर (!list_empty(&object->pending_ops)) अणु
			atomic_inc(&op->usage);
			list_add_tail(&op->pend_link, &object->pending_ops);
			fscache_stat(&fscache_n_op_pend);
			fscache_start_operations(object);
		पूर्ण अन्यथा अणु
			ASSERTCMP(object->n_in_progress, ==, 0);
			fscache_run_op(object, op);
		पूर्ण

		/* need to issue a new ग_लिखो op after this */
		clear_bit(FSCACHE_OBJECT_PENDING_WRITE, &object->flags);
		ret = 0;
	पूर्ण अन्यथा अगर (flags & BIT(FSCACHE_OBJECT_IS_LOOKED_UP)) अणु
		op->object = object;
		object->n_ops++;
		object->n_exclusive++;	/* पढ़ोs and ग_लिखोs must रुको */
		atomic_inc(&op->usage);
		list_add_tail(&op->pend_link, &object->pending_ops);
		fscache_stat(&fscache_n_op_pend);
		ret = 0;
	पूर्ण अन्यथा अगर (flags & BIT(FSCACHE_OBJECT_KILLED_BY_CACHE)) अणु
		op->cancel(op);
		op->state = FSCACHE_OP_ST_CANCELLED;
		ret = -ENOBUFS;
	पूर्ण अन्यथा अणु
		fscache_report_unexpected_submission(object, op, ostate);
		op->cancel(op);
		op->state = FSCACHE_OP_ST_CANCELLED;
		ret = -ENOBUFS;
	पूर्ण

	spin_unlock(&object->lock);
	वापस ret;
पूर्ण

/*
 * submit an operation क्रम an object
 * - objects may be submitted only in the following states:
 *   - during object creation (ग_लिखो ops may be submitted)
 *   - whilst the object is active
 *   - after an I/O error incurred in one of the two above states (op rejected)
 * - this माला_लो any extra refs it needs on an op
 */
पूर्णांक fscache_submit_op(काष्ठा fscache_object *object,
		      काष्ठा fscache_operation *op)
अणु
	स्थिर काष्ठा fscache_state *ostate;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	_enter("{OBJ%x OP%x},{%u}",
	       object->debug_id, op->debug_id, atomic_पढ़ो(&op->usage));

	trace_fscache_op(object->cookie, op, fscache_op_submit);

	ASSERTCMP(op->state, ==, FSCACHE_OP_ST_INITIALISED);
	ASSERTCMP(atomic_पढ़ो(&op->usage), >, 0);

	spin_lock(&object->lock);
	ASSERTCMP(object->n_ops, >=, object->n_in_progress);
	ASSERTCMP(object->n_ops, >=, object->n_exclusive);
	ASSERT(list_empty(&op->pend_link));

	ostate = object->state;
	smp_rmb();

	op->state = FSCACHE_OP_ST_PENDING;
	flags = READ_ONCE(object->flags);
	अगर (unlikely(!(flags & BIT(FSCACHE_OBJECT_IS_LIVE)))) अणु
		fscache_stat(&fscache_n_op_rejected);
		op->cancel(op);
		op->state = FSCACHE_OP_ST_CANCELLED;
		ret = -ENOBUFS;
	पूर्ण अन्यथा अगर (unlikely(fscache_cache_is_broken(object))) अणु
		op->cancel(op);
		op->state = FSCACHE_OP_ST_CANCELLED;
		ret = -EIO;
	पूर्ण अन्यथा अगर (flags & BIT(FSCACHE_OBJECT_IS_AVAILABLE)) अणु
		op->object = object;
		object->n_ops++;

		अगर (object->n_exclusive > 0) अणु
			atomic_inc(&op->usage);
			list_add_tail(&op->pend_link, &object->pending_ops);
			fscache_stat(&fscache_n_op_pend);
		पूर्ण अन्यथा अगर (!list_empty(&object->pending_ops)) अणु
			atomic_inc(&op->usage);
			list_add_tail(&op->pend_link, &object->pending_ops);
			fscache_stat(&fscache_n_op_pend);
			fscache_start_operations(object);
		पूर्ण अन्यथा अणु
			ASSERTCMP(object->n_exclusive, ==, 0);
			fscache_run_op(object, op);
		पूर्ण
		ret = 0;
	पूर्ण अन्यथा अगर (flags & BIT(FSCACHE_OBJECT_IS_LOOKED_UP)) अणु
		op->object = object;
		object->n_ops++;
		atomic_inc(&op->usage);
		list_add_tail(&op->pend_link, &object->pending_ops);
		fscache_stat(&fscache_n_op_pend);
		ret = 0;
	पूर्ण अन्यथा अगर (flags & BIT(FSCACHE_OBJECT_KILLED_BY_CACHE)) अणु
		op->cancel(op);
		op->state = FSCACHE_OP_ST_CANCELLED;
		ret = -ENOBUFS;
	पूर्ण अन्यथा अणु
		fscache_report_unexpected_submission(object, op, ostate);
		ASSERT(!fscache_object_is_active(object));
		op->cancel(op);
		op->state = FSCACHE_OP_ST_CANCELLED;
		ret = -ENOBUFS;
	पूर्ण

	spin_unlock(&object->lock);
	वापस ret;
पूर्ण

/*
 * queue an object क्रम withdrawal on error, पातing all following asynchronous
 * operations
 */
व्योम fscache_पात_object(काष्ठा fscache_object *object)
अणु
	_enter("{OBJ%x}", object->debug_id);

	fscache_उठाओ_event(object, FSCACHE_OBJECT_EV_ERROR);
पूर्ण

/*
 * Jump start the operation processing on an object.  The caller must hold
 * object->lock.
 */
व्योम fscache_start_operations(काष्ठा fscache_object *object)
अणु
	काष्ठा fscache_operation *op;
	bool stop = false;

	जबतक (!list_empty(&object->pending_ops) && !stop) अणु
		op = list_entry(object->pending_ops.next,
				काष्ठा fscache_operation, pend_link);

		अगर (test_bit(FSCACHE_OP_EXCLUSIVE, &op->flags)) अणु
			अगर (object->n_in_progress > 0)
				अवरोध;
			stop = true;
		पूर्ण
		list_del_init(&op->pend_link);
		fscache_run_op(object, op);

		/* the pending queue was holding a ref on the object */
		fscache_put_operation(op);
	पूर्ण

	ASSERTCMP(object->n_in_progress, <=, object->n_ops);

	_debug("woke %d ops on OBJ%x",
	       object->n_in_progress, object->debug_id);
पूर्ण

/*
 * cancel an operation that's pending on an object
 */
पूर्णांक fscache_cancel_op(काष्ठा fscache_operation *op,
		      bool cancel_in_progress_op)
अणु
	काष्ठा fscache_object *object = op->object;
	bool put = false;
	पूर्णांक ret;

	_enter("OBJ%x OP%x}", op->object->debug_id, op->debug_id);

	trace_fscache_op(object->cookie, op, fscache_op_cancel);

	ASSERTCMP(op->state, >=, FSCACHE_OP_ST_PENDING);
	ASSERTCMP(op->state, !=, FSCACHE_OP_ST_CANCELLED);
	ASSERTCMP(atomic_पढ़ो(&op->usage), >, 0);

	spin_lock(&object->lock);

	ret = -EBUSY;
	अगर (op->state == FSCACHE_OP_ST_PENDING) अणु
		ASSERT(!list_empty(&op->pend_link));
		list_del_init(&op->pend_link);
		put = true;

		fscache_stat(&fscache_n_op_cancelled);
		op->cancel(op);
		op->state = FSCACHE_OP_ST_CANCELLED;
		अगर (test_bit(FSCACHE_OP_EXCLUSIVE, &op->flags))
			object->n_exclusive--;
		अगर (test_and_clear_bit(FSCACHE_OP_WAITING, &op->flags))
			wake_up_bit(&op->flags, FSCACHE_OP_WAITING);
		ret = 0;
	पूर्ण अन्यथा अगर (op->state == FSCACHE_OP_ST_IN_PROGRESS && cancel_in_progress_op) अणु
		ASSERTCMP(object->n_in_progress, >, 0);
		अगर (test_bit(FSCACHE_OP_EXCLUSIVE, &op->flags))
			object->n_exclusive--;
		object->n_in_progress--;
		अगर (object->n_in_progress == 0)
			fscache_start_operations(object);

		fscache_stat(&fscache_n_op_cancelled);
		op->cancel(op);
		op->state = FSCACHE_OP_ST_CANCELLED;
		अगर (test_bit(FSCACHE_OP_EXCLUSIVE, &op->flags))
			object->n_exclusive--;
		अगर (test_and_clear_bit(FSCACHE_OP_WAITING, &op->flags))
			wake_up_bit(&op->flags, FSCACHE_OP_WAITING);
		ret = 0;
	पूर्ण

	अगर (put)
		fscache_put_operation(op);
	spin_unlock(&object->lock);
	_leave(" = %d", ret);
	वापस ret;
पूर्ण

/*
 * Cancel all pending operations on an object
 */
व्योम fscache_cancel_all_ops(काष्ठा fscache_object *object)
अणु
	काष्ठा fscache_operation *op;

	_enter("OBJ%x", object->debug_id);

	spin_lock(&object->lock);

	जबतक (!list_empty(&object->pending_ops)) अणु
		op = list_entry(object->pending_ops.next,
				काष्ठा fscache_operation, pend_link);
		fscache_stat(&fscache_n_op_cancelled);
		list_del_init(&op->pend_link);

		trace_fscache_op(object->cookie, op, fscache_op_cancel_all);

		ASSERTCMP(op->state, ==, FSCACHE_OP_ST_PENDING);
		op->cancel(op);
		op->state = FSCACHE_OP_ST_CANCELLED;

		अगर (test_bit(FSCACHE_OP_EXCLUSIVE, &op->flags))
			object->n_exclusive--;
		अगर (test_and_clear_bit(FSCACHE_OP_WAITING, &op->flags))
			wake_up_bit(&op->flags, FSCACHE_OP_WAITING);
		fscache_put_operation(op);
		cond_resched_lock(&object->lock);
	पूर्ण

	spin_unlock(&object->lock);
	_leave("");
पूर्ण

/*
 * Record the completion or cancellation of an in-progress operation.
 */
व्योम fscache_op_complete(काष्ठा fscache_operation *op, bool cancelled)
अणु
	काष्ठा fscache_object *object = op->object;

	_enter("OBJ%x", object->debug_id);

	ASSERTCMP(op->state, ==, FSCACHE_OP_ST_IN_PROGRESS);
	ASSERTCMP(object->n_in_progress, >, 0);
	ASSERTIFCMP(test_bit(FSCACHE_OP_EXCLUSIVE, &op->flags),
		    object->n_exclusive, >, 0);
	ASSERTIFCMP(test_bit(FSCACHE_OP_EXCLUSIVE, &op->flags),
		    object->n_in_progress, ==, 1);

	spin_lock(&object->lock);

	अगर (!cancelled) अणु
		trace_fscache_op(object->cookie, op, fscache_op_completed);
		op->state = FSCACHE_OP_ST_COMPLETE;
	पूर्ण अन्यथा अणु
		op->cancel(op);
		trace_fscache_op(object->cookie, op, fscache_op_cancelled);
		op->state = FSCACHE_OP_ST_CANCELLED;
	पूर्ण

	अगर (test_bit(FSCACHE_OP_EXCLUSIVE, &op->flags))
		object->n_exclusive--;
	object->n_in_progress--;
	अगर (object->n_in_progress == 0)
		fscache_start_operations(object);

	spin_unlock(&object->lock);
	_leave("");
पूर्ण
EXPORT_SYMBOL(fscache_op_complete);

/*
 * release an operation
 * - queues pending ops अगर this is the last in-progress op
 */
व्योम fscache_put_operation(काष्ठा fscache_operation *op)
अणु
	काष्ठा fscache_object *object;
	काष्ठा fscache_cache *cache;

	_enter("{OBJ%x OP%x,%d}",
	       op->object ? op->object->debug_id : 0,
	       op->debug_id, atomic_पढ़ो(&op->usage));

	ASSERTCMP(atomic_पढ़ो(&op->usage), >, 0);

	अगर (!atomic_dec_and_test(&op->usage))
		वापस;

	trace_fscache_op(op->object ? op->object->cookie : शून्य, op, fscache_op_put);

	_debug("PUT OP");
	ASSERTIFCMP(op->state != FSCACHE_OP_ST_INITIALISED &&
		    op->state != FSCACHE_OP_ST_COMPLETE,
		    op->state, ==, FSCACHE_OP_ST_CANCELLED);

	fscache_stat(&fscache_n_op_release);

	अगर (op->release) अणु
		op->release(op);
		op->release = शून्य;
	पूर्ण
	op->state = FSCACHE_OP_ST_DEAD;

	object = op->object;
	अगर (likely(object)) अणु
		अगर (test_bit(FSCACHE_OP_DEC_READ_CNT, &op->flags))
			atomic_dec(&object->n_पढ़ोs);
		अगर (test_bit(FSCACHE_OP_UNUSE_COOKIE, &op->flags))
			fscache_unuse_cookie(object);

		/* now... we may get called with the object spinlock held, so we
		 * complete the cleanup here only अगर we can immediately acquire the
		 * lock, and defer it otherwise */
		अगर (!spin_trylock(&object->lock)) अणु
			_debug("defer put");
			fscache_stat(&fscache_n_op_deferred_release);

			cache = object->cache;
			spin_lock(&cache->op_gc_list_lock);
			list_add_tail(&op->pend_link, &cache->op_gc_list);
			spin_unlock(&cache->op_gc_list_lock);
			schedule_work(&cache->op_gc);
			_leave(" [defer]");
			वापस;
		पूर्ण

		ASSERTCMP(object->n_ops, >, 0);
		object->n_ops--;
		अगर (object->n_ops == 0)
			fscache_उठाओ_event(object, FSCACHE_OBJECT_EV_CLEARED);

		spin_unlock(&object->lock);
	पूर्ण

	kमुक्त(op);
	_leave(" [done]");
पूर्ण
EXPORT_SYMBOL(fscache_put_operation);

/*
 * garbage collect operations that have had their release deferred
 */
व्योम fscache_operation_gc(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fscache_operation *op;
	काष्ठा fscache_object *object;
	काष्ठा fscache_cache *cache =
		container_of(work, काष्ठा fscache_cache, op_gc);
	पूर्णांक count = 0;

	_enter("");

	करो अणु
		spin_lock(&cache->op_gc_list_lock);
		अगर (list_empty(&cache->op_gc_list)) अणु
			spin_unlock(&cache->op_gc_list_lock);
			अवरोध;
		पूर्ण

		op = list_entry(cache->op_gc_list.next,
				काष्ठा fscache_operation, pend_link);
		list_del(&op->pend_link);
		spin_unlock(&cache->op_gc_list_lock);

		object = op->object;
		trace_fscache_op(object->cookie, op, fscache_op_gc);

		spin_lock(&object->lock);

		_debug("GC DEFERRED REL OBJ%x OP%x",
		       object->debug_id, op->debug_id);
		fscache_stat(&fscache_n_op_gc);

		ASSERTCMP(atomic_पढ़ो(&op->usage), ==, 0);
		ASSERTCMP(op->state, ==, FSCACHE_OP_ST_DEAD);

		ASSERTCMP(object->n_ops, >, 0);
		object->n_ops--;
		अगर (object->n_ops == 0)
			fscache_उठाओ_event(object, FSCACHE_OBJECT_EV_CLEARED);

		spin_unlock(&object->lock);
		kमुक्त(op);

	पूर्ण जबतक (count++ < 20);

	अगर (!list_empty(&cache->op_gc_list))
		schedule_work(&cache->op_gc);

	_leave("");
पूर्ण

/*
 * execute an operation using fs_op_wq to provide processing context -
 * the caller holds a ref to this object, so we करोn't need to hold one
 */
व्योम fscache_op_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fscache_operation *op =
		container_of(work, काष्ठा fscache_operation, work);
	अचिन्हित दीर्घ start;

	_enter("{OBJ%x OP%x,%d}",
	       op->object->debug_id, op->debug_id, atomic_पढ़ो(&op->usage));

	trace_fscache_op(op->object->cookie, op, fscache_op_work);

	ASSERT(op->processor != शून्य);
	start = jअगरfies;
	op->processor(op);
	fscache_hist(fscache_ops_histogram, start);
	fscache_put_operation(op);

	_leave("");
पूर्ण
