<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2007 Oracle.  All rights reserved.
 * Copyright (C) 2014 Fujitsu.  All rights reserved.
 */

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मुक्तzer.h>
#समावेश "async-thread.h"
#समावेश "ctree.h"

क्रमागत अणु
	WORK_DONE_BIT,
	WORK_ORDER_DONE_BIT,
	WORK_HIGH_PRIO_BIT,
पूर्ण;

#घोषणा NO_THRESHOLD (-1)
#घोषणा DFT_THRESHOLD (32)

काष्ठा __btrfs_workqueue अणु
	काष्ठा workqueue_काष्ठा *normal_wq;

	/* File प्रणाली this workqueue services */
	काष्ठा btrfs_fs_info *fs_info;

	/* List head poपूर्णांकing to ordered work list */
	काष्ठा list_head ordered_list;

	/* Spinlock क्रम ordered_list */
	spinlock_t list_lock;

	/* Thresholding related variants */
	atomic_t pending;

	/* Up limit of concurrency workers */
	पूर्णांक limit_active;

	/* Current number of concurrency workers */
	पूर्णांक current_active;

	/* Threshold to change current_active */
	पूर्णांक thresh;
	अचिन्हित पूर्णांक count;
	spinlock_t thres_lock;
पूर्ण;

काष्ठा btrfs_workqueue अणु
	काष्ठा __btrfs_workqueue *normal;
	काष्ठा __btrfs_workqueue *high;
पूर्ण;

काष्ठा btrfs_fs_info * __pure btrfs_workqueue_owner(स्थिर काष्ठा __btrfs_workqueue *wq)
अणु
	वापस wq->fs_info;
पूर्ण

काष्ठा btrfs_fs_info * __pure btrfs_work_owner(स्थिर काष्ठा btrfs_work *work)
अणु
	वापस work->wq->fs_info;
पूर्ण

bool btrfs_workqueue_normal_congested(स्थिर काष्ठा btrfs_workqueue *wq)
अणु
	/*
	 * We could compare wq->normal->pending with num_online_cpus()
	 * to support "thresh == NO_THRESHOLD" हाल, but it requires
	 * moving up atomic_inc/dec in thresh_queue/exec_hook. Let's
	 * postpone it until someone needs the support of that हाल.
	 */
	अगर (wq->normal->thresh == NO_THRESHOLD)
		वापस false;

	वापस atomic_पढ़ो(&wq->normal->pending) > wq->normal->thresh * 2;
पूर्ण

अटल काष्ठा __btrfs_workqueue *
__btrfs_alloc_workqueue(काष्ठा btrfs_fs_info *fs_info, स्थिर अक्षर *name,
			अचिन्हित पूर्णांक flags, पूर्णांक limit_active, पूर्णांक thresh)
अणु
	काष्ठा __btrfs_workqueue *ret = kzalloc(माप(*ret), GFP_KERNEL);

	अगर (!ret)
		वापस शून्य;

	ret->fs_info = fs_info;
	ret->limit_active = limit_active;
	atomic_set(&ret->pending, 0);
	अगर (thresh == 0)
		thresh = DFT_THRESHOLD;
	/* For low threshold, disabling threshold is a better choice */
	अगर (thresh < DFT_THRESHOLD) अणु
		ret->current_active = limit_active;
		ret->thresh = NO_THRESHOLD;
	पूर्ण अन्यथा अणु
		/*
		 * For threshold-able wq, let its concurrency grow on demand.
		 * Use minimal max_active at alloc समय to reduce resource
		 * usage.
		 */
		ret->current_active = 1;
		ret->thresh = thresh;
	पूर्ण

	अगर (flags & WQ_HIGHPRI)
		ret->normal_wq = alloc_workqueue("btrfs-%s-high", flags,
						 ret->current_active, name);
	अन्यथा
		ret->normal_wq = alloc_workqueue("btrfs-%s", flags,
						 ret->current_active, name);
	अगर (!ret->normal_wq) अणु
		kमुक्त(ret);
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&ret->ordered_list);
	spin_lock_init(&ret->list_lock);
	spin_lock_init(&ret->thres_lock);
	trace_btrfs_workqueue_alloc(ret, name, flags & WQ_HIGHPRI);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
__btrfs_destroy_workqueue(काष्ठा __btrfs_workqueue *wq);

काष्ठा btrfs_workqueue *btrfs_alloc_workqueue(काष्ठा btrfs_fs_info *fs_info,
					      स्थिर अक्षर *name,
					      अचिन्हित पूर्णांक flags,
					      पूर्णांक limit_active,
					      पूर्णांक thresh)
अणु
	काष्ठा btrfs_workqueue *ret = kzalloc(माप(*ret), GFP_KERNEL);

	अगर (!ret)
		वापस शून्य;

	ret->normal = __btrfs_alloc_workqueue(fs_info, name,
					      flags & ~WQ_HIGHPRI,
					      limit_active, thresh);
	अगर (!ret->normal) अणु
		kमुक्त(ret);
		वापस शून्य;
	पूर्ण

	अगर (flags & WQ_HIGHPRI) अणु
		ret->high = __btrfs_alloc_workqueue(fs_info, name, flags,
						    limit_active, thresh);
		अगर (!ret->high) अणु
			__btrfs_destroy_workqueue(ret->normal);
			kमुक्त(ret);
			वापस शून्य;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Hook क्रम threshold which will be called in btrfs_queue_work.
 * This hook WILL be called in IRQ handler context,
 * so workqueue_set_max_active MUST NOT be called in this hook
 */
अटल अंतरभूत व्योम thresh_queue_hook(काष्ठा __btrfs_workqueue *wq)
अणु
	अगर (wq->thresh == NO_THRESHOLD)
		वापस;
	atomic_inc(&wq->pending);
पूर्ण

/*
 * Hook क्रम threshold which will be called beक्रमe executing the work,
 * This hook is called in kthपढ़ो content.
 * So workqueue_set_max_active is called here.
 */
अटल अंतरभूत व्योम thresh_exec_hook(काष्ठा __btrfs_workqueue *wq)
अणु
	पूर्णांक new_current_active;
	दीर्घ pending;
	पूर्णांक need_change = 0;

	अगर (wq->thresh == NO_THRESHOLD)
		वापस;

	atomic_dec(&wq->pending);
	spin_lock(&wq->thres_lock);
	/*
	 * Use wq->count to limit the calling frequency of
	 * workqueue_set_max_active.
	 */
	wq->count++;
	wq->count %= (wq->thresh / 4);
	अगर (!wq->count)
		जाओ  out;
	new_current_active = wq->current_active;

	/*
	 * pending may be changed later, but it's OK since we really
	 * करोn't need it so accurate to calculate new_max_active.
	 */
	pending = atomic_पढ़ो(&wq->pending);
	अगर (pending > wq->thresh)
		new_current_active++;
	अगर (pending < wq->thresh / 2)
		new_current_active--;
	new_current_active = clamp_val(new_current_active, 1, wq->limit_active);
	अगर (new_current_active != wq->current_active)  अणु
		need_change = 1;
		wq->current_active = new_current_active;
	पूर्ण
out:
	spin_unlock(&wq->thres_lock);

	अगर (need_change) अणु
		workqueue_set_max_active(wq->normal_wq, wq->current_active);
	पूर्ण
पूर्ण

अटल व्योम run_ordered_work(काष्ठा __btrfs_workqueue *wq,
			     काष्ठा btrfs_work *self)
अणु
	काष्ठा list_head *list = &wq->ordered_list;
	काष्ठा btrfs_work *work;
	spinlock_t *lock = &wq->list_lock;
	अचिन्हित दीर्घ flags;
	bool मुक्त_self = false;

	जबतक (1) अणु
		spin_lock_irqsave(lock, flags);
		अगर (list_empty(list))
			अवरोध;
		work = list_entry(list->next, काष्ठा btrfs_work,
				  ordered_list);
		अगर (!test_bit(WORK_DONE_BIT, &work->flags))
			अवरोध;

		/*
		 * we are going to call the ordered करोne function, but
		 * we leave the work item on the list as a barrier so
		 * that later work items that are करोne करोn't have their
		 * functions called beक्रमe this one वापसs
		 */
		अगर (test_and_set_bit(WORK_ORDER_DONE_BIT, &work->flags))
			अवरोध;
		trace_btrfs_ordered_sched(work);
		spin_unlock_irqrestore(lock, flags);
		work->ordered_func(work);

		/* now take the lock again and drop our item from the list */
		spin_lock_irqsave(lock, flags);
		list_del(&work->ordered_list);
		spin_unlock_irqrestore(lock, flags);

		अगर (work == self) अणु
			/*
			 * This is the work item that the worker is currently
			 * executing.
			 *
			 * The kernel workqueue code guarantees non-reentrancy
			 * of work items. I.e., अगर a work item with the same
			 * address and work function is queued twice, the second
			 * execution is blocked until the first one finishes. A
			 * work item may be मुक्तd and recycled with the same
			 * work function; the workqueue code assumes that the
			 * original work item cannot depend on the recycled work
			 * item in that हाल (see find_worker_executing_work()).
			 *
			 * Note that dअगरferent types of Btrfs work can depend on
			 * each other, and one type of work on one Btrfs
			 * fileप्रणाली may even depend on the same type of work
			 * on another Btrfs fileप्रणाली via, e.g., a loop device.
			 * Thereक्रमe, we must not allow the current work item to
			 * be recycled until we are really करोne, otherwise we
			 * अवरोध the above assumption and can deadlock.
			 */
			मुक्त_self = true;
		पूर्ण अन्यथा अणु
			/*
			 * We करोn't want to call the ordered मुक्त functions with
			 * the lock held.
			 */
			work->ordered_मुक्त(work);
			/* NB: work must not be dereferenced past this poपूर्णांक. */
			trace_btrfs_all_work_करोne(wq->fs_info, work);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(lock, flags);

	अगर (मुक्त_self) अणु
		self->ordered_मुक्त(self);
		/* NB: self must not be dereferenced past this poपूर्णांक. */
		trace_btrfs_all_work_करोne(wq->fs_info, self);
	पूर्ण
पूर्ण

अटल व्योम btrfs_work_helper(काष्ठा work_काष्ठा *normal_work)
अणु
	काष्ठा btrfs_work *work = container_of(normal_work, काष्ठा btrfs_work,
					       normal_work);
	काष्ठा __btrfs_workqueue *wq;
	पूर्णांक need_order = 0;

	/*
	 * We should not touch things inside work in the following हालs:
	 * 1) after work->func() अगर it has no ordered_मुक्त
	 *    Since the काष्ठा is मुक्तd in work->func().
	 * 2) after setting WORK_DONE_BIT
	 *    The work may be मुक्तd in other thपढ़ोs almost instantly.
	 * So we save the needed things here.
	 */
	अगर (work->ordered_func)
		need_order = 1;
	wq = work->wq;

	trace_btrfs_work_sched(work);
	thresh_exec_hook(wq);
	work->func(work);
	अगर (need_order) अणु
		set_bit(WORK_DONE_BIT, &work->flags);
		run_ordered_work(wq, work);
	पूर्ण अन्यथा अणु
		/* NB: work must not be dereferenced past this poपूर्णांक. */
		trace_btrfs_all_work_करोne(wq->fs_info, work);
	पूर्ण
पूर्ण

व्योम btrfs_init_work(काष्ठा btrfs_work *work, btrfs_func_t func,
		     btrfs_func_t ordered_func, btrfs_func_t ordered_मुक्त)
अणु
	work->func = func;
	work->ordered_func = ordered_func;
	work->ordered_मुक्त = ordered_मुक्त;
	INIT_WORK(&work->normal_work, btrfs_work_helper);
	INIT_LIST_HEAD(&work->ordered_list);
	work->flags = 0;
पूर्ण

अटल अंतरभूत व्योम __btrfs_queue_work(काष्ठा __btrfs_workqueue *wq,
				      काष्ठा btrfs_work *work)
अणु
	अचिन्हित दीर्घ flags;

	work->wq = wq;
	thresh_queue_hook(wq);
	अगर (work->ordered_func) अणु
		spin_lock_irqsave(&wq->list_lock, flags);
		list_add_tail(&work->ordered_list, &wq->ordered_list);
		spin_unlock_irqrestore(&wq->list_lock, flags);
	पूर्ण
	trace_btrfs_work_queued(work);
	queue_work(wq->normal_wq, &work->normal_work);
पूर्ण

व्योम btrfs_queue_work(काष्ठा btrfs_workqueue *wq,
		      काष्ठा btrfs_work *work)
अणु
	काष्ठा __btrfs_workqueue *dest_wq;

	अगर (test_bit(WORK_HIGH_PRIO_BIT, &work->flags) && wq->high)
		dest_wq = wq->high;
	अन्यथा
		dest_wq = wq->normal;
	__btrfs_queue_work(dest_wq, work);
पूर्ण

अटल अंतरभूत व्योम
__btrfs_destroy_workqueue(काष्ठा __btrfs_workqueue *wq)
अणु
	destroy_workqueue(wq->normal_wq);
	trace_btrfs_workqueue_destroy(wq);
	kमुक्त(wq);
पूर्ण

व्योम btrfs_destroy_workqueue(काष्ठा btrfs_workqueue *wq)
अणु
	अगर (!wq)
		वापस;
	अगर (wq->high)
		__btrfs_destroy_workqueue(wq->high);
	__btrfs_destroy_workqueue(wq->normal);
	kमुक्त(wq);
पूर्ण

व्योम btrfs_workqueue_set_max(काष्ठा btrfs_workqueue *wq, पूर्णांक limit_active)
अणु
	अगर (!wq)
		वापस;
	wq->normal->limit_active = limit_active;
	अगर (wq->high)
		wq->high->limit_active = limit_active;
पूर्ण

व्योम btrfs_set_work_high_priority(काष्ठा btrfs_work *work)
अणु
	set_bit(WORK_HIGH_PRIO_BIT, &work->flags);
पूर्ण

व्योम btrfs_flush_workqueue(काष्ठा btrfs_workqueue *wq)
अणु
	अगर (wq->high)
		flush_workqueue(wq->high->normal_wq);

	flush_workqueue(wq->normal->normal_wq);
पूर्ण
