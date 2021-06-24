<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Functions related to io context handling
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/task.h>

#समावेश "blk.h"

/*
 * For io context allocations
 */
अटल काष्ठा kmem_cache *iocontext_cachep;

/**
 * get_io_context - increment reference count to io_context
 * @ioc: io_context to get
 *
 * Increment reference count to @ioc.
 */
व्योम get_io_context(काष्ठा io_context *ioc)
अणु
	BUG_ON(atomic_दीर्घ_पढ़ो(&ioc->refcount) <= 0);
	atomic_दीर्घ_inc(&ioc->refcount);
पूर्ण

अटल व्योम icq_मुक्त_icq_rcu(काष्ठा rcu_head *head)
अणु
	काष्ठा io_cq *icq = container_of(head, काष्ठा io_cq, __rcu_head);

	kmem_cache_मुक्त(icq->__rcu_icq_cache, icq);
पूर्ण

/*
 * Exit an icq. Called with ioc locked क्रम blk-mq, and with both ioc
 * and queue locked क्रम legacy.
 */
अटल व्योम ioc_निकास_icq(काष्ठा io_cq *icq)
अणु
	काष्ठा elevator_type *et = icq->q->elevator->type;

	अगर (icq->flags & ICQ_EXITED)
		वापस;

	अगर (et->ops.निकास_icq)
		et->ops.निकास_icq(icq);

	icq->flags |= ICQ_EXITED;
पूर्ण

/*
 * Release an icq. Called with ioc locked क्रम blk-mq, and with both ioc
 * and queue locked क्रम legacy.
 */
अटल व्योम ioc_destroy_icq(काष्ठा io_cq *icq)
अणु
	काष्ठा io_context *ioc = icq->ioc;
	काष्ठा request_queue *q = icq->q;
	काष्ठा elevator_type *et = q->elevator->type;

	lockdep_निश्चित_held(&ioc->lock);

	radix_tree_delete(&ioc->icq_tree, icq->q->id);
	hlist_del_init(&icq->ioc_node);
	list_del_init(&icq->q_node);

	/*
	 * Both setting lookup hपूर्णांक to and clearing it from @icq are करोne
	 * under queue_lock.  If it's not poपूर्णांकing to @icq now, it never
	 * will.  Hपूर्णांक assignment itself can race safely.
	 */
	अगर (rcu_access_poपूर्णांकer(ioc->icq_hपूर्णांक) == icq)
		rcu_assign_poपूर्णांकer(ioc->icq_hपूर्णांक, शून्य);

	ioc_निकास_icq(icq);

	/*
	 * @icq->q might have gone away by the समय RCU callback runs
	 * making it impossible to determine icq_cache.  Record it in @icq.
	 */
	icq->__rcu_icq_cache = et->icq_cache;
	icq->flags |= ICQ_DESTROYED;
	call_rcu(&icq->__rcu_head, icq_मुक्त_icq_rcu);
पूर्ण

/*
 * Slow path क्रम ioc release in put_io_context().  Perक्रमms द्विगुन-lock
 * dancing to unlink all icq's and then मुक्तs ioc.
 */
अटल व्योम ioc_release_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा io_context *ioc = container_of(work, काष्ठा io_context,
					      release_work);
	spin_lock_irq(&ioc->lock);

	जबतक (!hlist_empty(&ioc->icq_list)) अणु
		काष्ठा io_cq *icq = hlist_entry(ioc->icq_list.first,
						काष्ठा io_cq, ioc_node);
		काष्ठा request_queue *q = icq->q;

		अगर (spin_trylock(&q->queue_lock)) अणु
			ioc_destroy_icq(icq);
			spin_unlock(&q->queue_lock);
		पूर्ण अन्यथा अणु
			/* Make sure q and icq cannot be मुक्तd. */
			rcu_पढ़ो_lock();

			/* Re-acquire the locks in the correct order. */
			spin_unlock(&ioc->lock);
			spin_lock(&q->queue_lock);
			spin_lock(&ioc->lock);

			/*
			 * The icq may have been destroyed when the ioc lock
			 * was released.
			 */
			अगर (!(icq->flags & ICQ_DESTROYED))
				ioc_destroy_icq(icq);

			spin_unlock(&q->queue_lock);
			rcu_पढ़ो_unlock();
		पूर्ण
	पूर्ण

	spin_unlock_irq(&ioc->lock);

	kmem_cache_मुक्त(iocontext_cachep, ioc);
पूर्ण

/**
 * put_io_context - put a reference of io_context
 * @ioc: io_context to put
 *
 * Decrement reference count of @ioc and release it अगर the count reaches
 * zero.
 */
व्योम put_io_context(काष्ठा io_context *ioc)
अणु
	अचिन्हित दीर्घ flags;
	bool मुक्त_ioc = false;

	अगर (ioc == शून्य)
		वापस;

	BUG_ON(atomic_दीर्घ_पढ़ो(&ioc->refcount) <= 0);

	/*
	 * Releasing ioc requires reverse order द्विगुन locking and we may
	 * alपढ़ोy be holding a queue_lock.  Do it asynchronously from wq.
	 */
	अगर (atomic_दीर्घ_dec_and_test(&ioc->refcount)) अणु
		spin_lock_irqsave(&ioc->lock, flags);
		अगर (!hlist_empty(&ioc->icq_list))
			queue_work(प्रणाली_घातer_efficient_wq,
					&ioc->release_work);
		अन्यथा
			मुक्त_ioc = true;
		spin_unlock_irqrestore(&ioc->lock, flags);
	पूर्ण

	अगर (मुक्त_ioc)
		kmem_cache_मुक्त(iocontext_cachep, ioc);
पूर्ण

/**
 * put_io_context_active - put active reference on ioc
 * @ioc: ioc of पूर्णांकerest
 *
 * Unकरो get_io_context_active().  If active reference reaches zero after
 * put, @ioc can never issue further IOs and ioscheds are notअगरied.
 */
व्योम put_io_context_active(काष्ठा io_context *ioc)
अणु
	काष्ठा io_cq *icq;

	अगर (!atomic_dec_and_test(&ioc->active_ref)) अणु
		put_io_context(ioc);
		वापस;
	पूर्ण

	spin_lock_irq(&ioc->lock);
	hlist_क्रम_each_entry(icq, &ioc->icq_list, ioc_node) अणु
		अगर (icq->flags & ICQ_EXITED)
			जारी;

		ioc_निकास_icq(icq);
	पूर्ण
	spin_unlock_irq(&ioc->lock);

	put_io_context(ioc);
पूर्ण

/* Called by the निकासing task */
व्योम निकास_io_context(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा io_context *ioc;

	task_lock(task);
	ioc = task->io_context;
	task->io_context = शून्य;
	task_unlock(task);

	atomic_dec(&ioc->nr_tasks);
	put_io_context_active(ioc);
पूर्ण

अटल व्योम __ioc_clear_queue(काष्ठा list_head *icq_list)
अणु
	अचिन्हित दीर्घ flags;

	rcu_पढ़ो_lock();
	जबतक (!list_empty(icq_list)) अणु
		काष्ठा io_cq *icq = list_entry(icq_list->next,
						काष्ठा io_cq, q_node);
		काष्ठा io_context *ioc = icq->ioc;

		spin_lock_irqsave(&ioc->lock, flags);
		अगर (icq->flags & ICQ_DESTROYED) अणु
			spin_unlock_irqrestore(&ioc->lock, flags);
			जारी;
		पूर्ण
		ioc_destroy_icq(icq);
		spin_unlock_irqrestore(&ioc->lock, flags);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * ioc_clear_queue - अवरोध any ioc association with the specअगरied queue
 * @q: request_queue being cleared
 *
 * Walk @q->icq_list and निकास all io_cq's.
 */
व्योम ioc_clear_queue(काष्ठा request_queue *q)
अणु
	LIST_HEAD(icq_list);

	spin_lock_irq(&q->queue_lock);
	list_splice_init(&q->icq_list, &icq_list);
	spin_unlock_irq(&q->queue_lock);

	__ioc_clear_queue(&icq_list);
पूर्ण

पूर्णांक create_task_io_context(काष्ठा task_काष्ठा *task, gfp_t gfp_flags, पूर्णांक node)
अणु
	काष्ठा io_context *ioc;
	पूर्णांक ret;

	ioc = kmem_cache_alloc_node(iocontext_cachep, gfp_flags | __GFP_ZERO,
				    node);
	अगर (unlikely(!ioc))
		वापस -ENOMEM;

	/* initialize */
	atomic_दीर्घ_set(&ioc->refcount, 1);
	atomic_set(&ioc->nr_tasks, 1);
	atomic_set(&ioc->active_ref, 1);
	spin_lock_init(&ioc->lock);
	INIT_RADIX_TREE(&ioc->icq_tree, GFP_ATOMIC);
	INIT_HLIST_HEAD(&ioc->icq_list);
	INIT_WORK(&ioc->release_work, ioc_release_fn);

	/*
	 * Try to install.  ioc shouldn't be installed अगर someone अन्यथा
	 * alपढ़ोy did or @task, which isn't %current, is निकासing.  Note
	 * that we need to allow ioc creation on निकासing %current as निकास
	 * path may issue IOs from e.g. निकास_files().  The निकास path is
	 * responsible क्रम not issuing IO after निकास_io_context().
	 */
	task_lock(task);
	अगर (!task->io_context &&
	    (task == current || !(task->flags & PF_EXITING)))
		task->io_context = ioc;
	अन्यथा
		kmem_cache_मुक्त(iocontext_cachep, ioc);

	ret = task->io_context ? 0 : -EBUSY;

	task_unlock(task);

	वापस ret;
पूर्ण

/**
 * get_task_io_context - get io_context of a task
 * @task: task of पूर्णांकerest
 * @gfp_flags: allocation flags, used अगर allocation is necessary
 * @node: allocation node, used अगर allocation is necessary
 *
 * Return io_context of @task.  If it करोesn't exist, it is created with
 * @gfp_flags and @node.  The वापसed io_context has its reference count
 * incremented.
 *
 * This function always goes through task_lock() and it's better to use
 * %current->io_context + get_io_context() क्रम %current.
 */
काष्ठा io_context *get_task_io_context(काष्ठा task_काष्ठा *task,
				       gfp_t gfp_flags, पूर्णांक node)
अणु
	काष्ठा io_context *ioc;

	might_sleep_अगर(gfpflags_allow_blocking(gfp_flags));

	करो अणु
		task_lock(task);
		ioc = task->io_context;
		अगर (likely(ioc)) अणु
			get_io_context(ioc);
			task_unlock(task);
			वापस ioc;
		पूर्ण
		task_unlock(task);
	पूर्ण जबतक (!create_task_io_context(task, gfp_flags, node));

	वापस शून्य;
पूर्ण

/**
 * ioc_lookup_icq - lookup io_cq from ioc
 * @ioc: the associated io_context
 * @q: the associated request_queue
 *
 * Look up io_cq associated with @ioc - @q pair from @ioc.  Must be called
 * with @q->queue_lock held.
 */
काष्ठा io_cq *ioc_lookup_icq(काष्ठा io_context *ioc, काष्ठा request_queue *q)
अणु
	काष्ठा io_cq *icq;

	lockdep_निश्चित_held(&q->queue_lock);

	/*
	 * icq's are indexed from @ioc using radix tree and hपूर्णांक poपूर्णांकer,
	 * both of which are रक्षित with RCU.  All removals are करोne
	 * holding both q and ioc locks, and we're holding q lock - अगर we
	 * find a icq which poपूर्णांकs to us, it's guaranteed to be valid.
	 */
	rcu_पढ़ो_lock();
	icq = rcu_dereference(ioc->icq_hपूर्णांक);
	अगर (icq && icq->q == q)
		जाओ out;

	icq = radix_tree_lookup(&ioc->icq_tree, q->id);
	अगर (icq && icq->q == q)
		rcu_assign_poपूर्णांकer(ioc->icq_hपूर्णांक, icq);	/* allowed to race */
	अन्यथा
		icq = शून्य;
out:
	rcu_पढ़ो_unlock();
	वापस icq;
पूर्ण
EXPORT_SYMBOL(ioc_lookup_icq);

/**
 * ioc_create_icq - create and link io_cq
 * @ioc: io_context of पूर्णांकerest
 * @q: request_queue of पूर्णांकerest
 * @gfp_mask: allocation mask
 *
 * Make sure io_cq linking @ioc and @q exists.  If icq करोesn't exist, they
 * will be created using @gfp_mask.
 *
 * The caller is responsible क्रम ensuring @ioc won't go away and @q is
 * alive and will stay alive until this function वापसs.
 */
काष्ठा io_cq *ioc_create_icq(काष्ठा io_context *ioc, काष्ठा request_queue *q,
			     gfp_t gfp_mask)
अणु
	काष्ठा elevator_type *et = q->elevator->type;
	काष्ठा io_cq *icq;

	/* allocate stuff */
	icq = kmem_cache_alloc_node(et->icq_cache, gfp_mask | __GFP_ZERO,
				    q->node);
	अगर (!icq)
		वापस शून्य;

	अगर (radix_tree_maybe_preload(gfp_mask) < 0) अणु
		kmem_cache_मुक्त(et->icq_cache, icq);
		वापस शून्य;
	पूर्ण

	icq->ioc = ioc;
	icq->q = q;
	INIT_LIST_HEAD(&icq->q_node);
	INIT_HLIST_NODE(&icq->ioc_node);

	/* lock both q and ioc and try to link @icq */
	spin_lock_irq(&q->queue_lock);
	spin_lock(&ioc->lock);

	अगर (likely(!radix_tree_insert(&ioc->icq_tree, q->id, icq))) अणु
		hlist_add_head(&icq->ioc_node, &ioc->icq_list);
		list_add(&icq->q_node, &q->icq_list);
		अगर (et->ops.init_icq)
			et->ops.init_icq(icq);
	पूर्ण अन्यथा अणु
		kmem_cache_मुक्त(et->icq_cache, icq);
		icq = ioc_lookup_icq(ioc, q);
		अगर (!icq)
			prपूर्णांकk(KERN_ERR "cfq: icq link failed!\n");
	पूर्ण

	spin_unlock(&ioc->lock);
	spin_unlock_irq(&q->queue_lock);
	radix_tree_preload_end();
	वापस icq;
पूर्ण

अटल पूर्णांक __init blk_ioc_init(व्योम)
अणु
	iocontext_cachep = kmem_cache_create("blkdev_ioc",
			माप(काष्ठा io_context), 0, SLAB_PANIC, शून्य);
	वापस 0;
पूर्ण
subsys_initcall(blk_ioc_init);
