<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Fence mechanism क्रम dma-buf and to allow क्रम asynchronous dma access
 *
 * Copyright (C) 2012 Canonical Ltd
 * Copyright (C) 2012 Texas Instruments
 *
 * Authors:
 * Rob Clark <robdclark@gmail.com>
 * Maarten Lankhorst <maarten.lankhorst@canonical.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/atomic.h>
#समावेश <linux/dma-fence.h>
#समावेश <linux/sched/संकेत.स>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/dma_fence.h>

EXPORT_TRACEPOINT_SYMBOL(dma_fence_emit);
EXPORT_TRACEPOINT_SYMBOL(dma_fence_enable_संकेत);
EXPORT_TRACEPOINT_SYMBOL(dma_fence_संकेतed);

अटल DEFINE_SPINLOCK(dma_fence_stub_lock);
अटल काष्ठा dma_fence dma_fence_stub;

/*
 * fence context counter: each execution context should have its own
 * fence context, this allows checking अगर fences beदीर्घ to the same
 * context or not. One device can have multiple separate contexts,
 * and they're used अगर some engine can run independently of another.
 */
अटल atomic64_t dma_fence_context_counter = ATOMIC64_INIT(1);

/**
 * DOC: DMA fences overview
 *
 * DMA fences, represented by &काष्ठा dma_fence, are the kernel पूर्णांकernal
 * synchronization primitive क्रम DMA operations like GPU rendering, video
 * encoding/decoding, or displaying buffers on a screen.
 *
 * A fence is initialized using dma_fence_init() and completed using
 * dma_fence_संकेत(). Fences are associated with a context, allocated through
 * dma_fence_context_alloc(), and all fences on the same context are
 * fully ordered.
 *
 * Since the purposes of fences is to facilitate cross-device and
 * cross-application synchronization, there's multiple ways to use one:
 *
 * - Inभागidual fences can be exposed as a &sync_file, accessed as a file
 *   descriptor from userspace, created by calling sync_file_create(). This is
 *   called explicit fencing, since userspace passes around explicit
 *   synchronization poपूर्णांकs.
 *
 * - Some subप्रणालीs also have their own explicit fencing primitives, like
 *   &drm_syncobj. Compared to &sync_file, a &drm_syncobj allows the underlying
 *   fence to be updated.
 *
 * - Then there's also implicit fencing, where the synchronization poपूर्णांकs are
 *   implicitly passed around as part of shared &dma_buf instances. Such
 *   implicit fences are stored in &काष्ठा dma_resv through the
 *   &dma_buf.resv poपूर्णांकer.
 */

/**
 * DOC: fence cross-driver contract
 *
 * Since &dma_fence provide a cross driver contract, all drivers must follow the
 * same rules:
 *
 * * Fences must complete in a reasonable समय. Fences which represent kernels
 *   and shaders submitted by userspace, which could run क्रमever, must be backed
 *   up by समयout and gpu hang recovery code. Minimally that code must prevent
 *   further command submission and क्रमce complete all in-flight fences, e.g.
 *   when the driver or hardware करो not support gpu reset, or अगर the gpu reset
 *   failed क्रम some reason. Ideally the driver supports gpu recovery which only
 *   affects the offending userspace context, and no other userspace
 *   submissions.
 *
 * * Drivers may have dअगरferent ideas of what completion within a reasonable
 *   समय means. Some hang recovery code uses a fixed समयout, others a mix
 *   between observing क्रमward progress and increasingly strict समयouts.
 *   Drivers should not try to second guess समयout handling of fences from
 *   other drivers.
 *
 * * To ensure there's no deadlocks of dma_fence_रुको() against other locks
 *   drivers should annotate all code required to reach dma_fence_संकेत(),
 *   which completes the fences, with dma_fence_begin_संकेतling() and
 *   dma_fence_end_संकेतling().
 *
 * * Drivers are allowed to call dma_fence_रुको() जबतक holding dma_resv_lock().
 *   This means any code required क्रम fence completion cannot acquire a
 *   &dma_resv lock. Note that this also pulls in the entire established
 *   locking hierarchy around dma_resv_lock() and dma_resv_unlock().
 *
 * * Drivers are allowed to call dma_fence_रुको() from their &shrinker
 *   callbacks. This means any code required क्रम fence completion cannot
 *   allocate memory with GFP_KERNEL.
 *
 * * Drivers are allowed to call dma_fence_रुको() from their &mmu_notअगरier
 *   respectively &mmu_पूर्णांकerval_notअगरier callbacks. This means any code required
 *   क्रम fence completeion cannot allocate memory with GFP_NOFS or GFP_NOIO.
 *   Only GFP_ATOMIC is permissible, which might fail.
 *
 * Note that only GPU drivers have a reasonable excuse क्रम both requiring
 * &mmu_पूर्णांकerval_notअगरier and &shrinker callbacks at the same समय as having to
 * track asynchronous compute work using &dma_fence. No driver outside of
 * drivers/gpu should ever call dma_fence_रुको() in such contexts.
 */

अटल स्थिर अक्षर *dma_fence_stub_get_name(काष्ठा dma_fence *fence)
अणु
        वापस "stub";
पूर्ण

अटल स्थिर काष्ठा dma_fence_ops dma_fence_stub_ops = अणु
	.get_driver_name = dma_fence_stub_get_name,
	.get_समयline_name = dma_fence_stub_get_name,
पूर्ण;

/**
 * dma_fence_get_stub - वापस a संकेतed fence
 *
 * Return a stub fence which is alपढ़ोy संकेतed. The fence's
 * बारtamp corresponds to the first समय after boot this
 * function is called.
 */
काष्ठा dma_fence *dma_fence_get_stub(व्योम)
अणु
	spin_lock(&dma_fence_stub_lock);
	अगर (!dma_fence_stub.ops) अणु
		dma_fence_init(&dma_fence_stub,
			       &dma_fence_stub_ops,
			       &dma_fence_stub_lock,
			       0, 0);
		dma_fence_संकेत_locked(&dma_fence_stub);
	पूर्ण
	spin_unlock(&dma_fence_stub_lock);

	वापस dma_fence_get(&dma_fence_stub);
पूर्ण
EXPORT_SYMBOL(dma_fence_get_stub);

/**
 * dma_fence_allocate_निजी_stub - वापस a निजी, संकेतed fence
 *
 * Return a newly allocated and संकेतed stub fence.
 */
काष्ठा dma_fence *dma_fence_allocate_निजी_stub(व्योम)
अणु
	काष्ठा dma_fence *fence;

	fence = kzalloc(माप(*fence), GFP_KERNEL);
	अगर (fence == शून्य)
		वापस ERR_PTR(-ENOMEM);

	dma_fence_init(fence,
		       &dma_fence_stub_ops,
		       &dma_fence_stub_lock,
		       0, 0);
	dma_fence_संकेत(fence);

	वापस fence;
पूर्ण
EXPORT_SYMBOL(dma_fence_allocate_निजी_stub);

/**
 * dma_fence_context_alloc - allocate an array of fence contexts
 * @num: amount of contexts to allocate
 *
 * This function will वापस the first index of the number of fence contexts
 * allocated.  The fence context is used क्रम setting &dma_fence.context to a
 * unique number by passing the context to dma_fence_init().
 */
u64 dma_fence_context_alloc(अचिन्हित num)
अणु
	WARN_ON(!num);
	वापस atomic64_fetch_add(num, &dma_fence_context_counter);
पूर्ण
EXPORT_SYMBOL(dma_fence_context_alloc);

/**
 * DOC: fence संकेतling annotation
 *
 * Proving correctness of all the kernel code around &dma_fence through code
 * review and testing is tricky क्रम a few reasons:
 *
 * * It is a cross-driver contract, and thereक्रमe all drivers must follow the
 *   same rules क्रम lock nesting order, calling contexts क्रम various functions
 *   and anything अन्यथा signअगरicant क्रम in-kernel पूर्णांकerfaces. But it is also
 *   impossible to test all drivers in a single machine, hence brute-क्रमce N vs.
 *   N testing of all combinations is impossible. Even just limiting to the
 *   possible combinations is infeasible.
 *
 * * There is an enormous amount of driver code involved. For render drivers
 *   there's the tail of command submission, after fences are published,
 *   scheduler code, पूर्णांकerrupt and workers to process job completion,
 *   and समयout, gpu reset and gpu hang recovery code. Plus क्रम पूर्णांकegration
 *   with core mm with have &mmu_notअगरier, respectively &mmu_पूर्णांकerval_notअगरier,
 *   and &shrinker. For modesetting drivers there's the commit tail functions
 *   between when fences क्रम an atomic modeset are published, and when the
 *   corresponding vblank completes, including any पूर्णांकerrupt processing and
 *   related workers. Auditing all that code, across all drivers, is not
 *   feasible.
 *
 * * Due to how many other subप्रणालीs are involved and the locking hierarchies
 *   this pulls in there is extremely thin wiggle-room क्रम driver-specअगरic
 *   dअगरferences. &dma_fence पूर्णांकeracts with almost all of the core memory
 *   handling through page fault handlers via &dma_resv, dma_resv_lock() and
 *   dma_resv_unlock(). On the other side it also पूर्णांकeracts through all
 *   allocation sites through &mmu_notअगरier and &shrinker.
 *
 * Furthermore lockdep करोes not handle cross-release dependencies, which means
 * any deadlocks between dma_fence_रुको() and dma_fence_संकेत() can't be caught
 * at runसमय with some quick testing. The simplest example is one thपढ़ो
 * रुकोing on a &dma_fence जबतक holding a lock::
 *
 *     lock(A);
 *     dma_fence_रुको(B);
 *     unlock(A);
 *
 * जबतक the other thपढ़ो is stuck trying to acquire the same lock, which
 * prevents it from संकेतling the fence the previous thपढ़ो is stuck रुकोing
 * on::
 *
 *     lock(A);
 *     unlock(A);
 *     dma_fence_संकेत(B);
 *
 * By manually annotating all code relevant to संकेतling a &dma_fence we can
 * teach lockdep about these dependencies, which also helps with the validation
 * headache since now lockdep can check all the rules क्रम us::
 *
 *    cookie = dma_fence_begin_संकेतling();
 *    lock(A);
 *    unlock(A);
 *    dma_fence_संकेत(B);
 *    dma_fence_end_संकेतling(cookie);
 *
 * For using dma_fence_begin_संकेतling() and dma_fence_end_संकेतling() to
 * annotate critical sections the following rules need to be observed:
 *
 * * All code necessary to complete a &dma_fence must be annotated, from the
 *   poपूर्णांक where a fence is accessible to other thपढ़ोs, to the poपूर्णांक where
 *   dma_fence_संकेत() is called. Un-annotated code can contain deadlock issues,
 *   and due to the very strict rules and many corner हालs it is infeasible to
 *   catch these just with review or normal stress testing.
 *
 * * &काष्ठा dma_resv deserves a special note, since the पढ़ोers are only
 *   रक्षित by rcu. This means the संकेतling critical section starts as soon
 *   as the new fences are installed, even beक्रमe dma_resv_unlock() is called.
 *
 * * The only exception are fast paths and opportunistic संकेतling code, which
 *   calls dma_fence_संकेत() purely as an optimization, but is not required to
 *   guarantee completion of a &dma_fence. The usual example is a रुको IOCTL
 *   which calls dma_fence_संकेत(), जबतक the mandatory completion path goes
 *   through a hardware पूर्णांकerrupt and possible job completion worker.
 *
 * * To aid composability of code, the annotations can be मुक्तly nested, as दीर्घ
 *   as the overall locking hierarchy is consistent. The annotations also work
 *   both in पूर्णांकerrupt and process context. Due to implementation details this
 *   requires that callers pass an opaque cookie from
 *   dma_fence_begin_संकेतling() to dma_fence_end_संकेतling().
 *
 * * Validation against the cross driver contract is implemented by priming
 *   lockdep with the relevant hierarchy at boot-up. This means even just
 *   testing with a single device is enough to validate a driver, at least as
 *   far as deadlocks with dma_fence_रुको() against dma_fence_संकेत() are
 *   concerned.
 */
#अगर_घोषित CONFIG_LOCKDEP
अटल काष्ठा lockdep_map dma_fence_lockdep_map = अणु
	.name = "dma_fence_map"
पूर्ण;

/**
 * dma_fence_begin_संकेतling - begin a critical DMA fence संकेतling section
 *
 * Drivers should use this to annotate the beginning of any code section
 * required to eventually complete &dma_fence by calling dma_fence_संकेत().
 *
 * The end of these critical sections are annotated with
 * dma_fence_end_संकेतling().
 *
 * Returns:
 *
 * Opaque cookie needed by the implementation, which needs to be passed to
 * dma_fence_end_संकेतling().
 */
bool dma_fence_begin_संकेतling(व्योम)
अणु
	/* explicitly nesting ... */
	अगर (lock_is_held_type(&dma_fence_lockdep_map, 1))
		वापस true;

	/* rely on might_sleep check क्रम soft/hardirq locks */
	अगर (in_atomic())
		वापस true;

	/* ... and non-recursive पढ़ोlock */
	lock_acquire(&dma_fence_lockdep_map, 0, 0, 1, 1, शून्य, _RET_IP_);

	वापस false;
पूर्ण
EXPORT_SYMBOL(dma_fence_begin_संकेतling);

/**
 * dma_fence_end_संकेतling - end a critical DMA fence संकेतling section
 * @cookie: opaque cookie from dma_fence_begin_संकेतling()
 *
 * Closes a critical section annotation खोलोed by dma_fence_begin_संकेतling().
 */
व्योम dma_fence_end_संकेतling(bool cookie)
अणु
	अगर (cookie)
		वापस;

	lock_release(&dma_fence_lockdep_map, _RET_IP_);
पूर्ण
EXPORT_SYMBOL(dma_fence_end_संकेतling);

व्योम __dma_fence_might_रुको(व्योम)
अणु
	bool पंचांगp;

	पंचांगp = lock_is_held_type(&dma_fence_lockdep_map, 1);
	अगर (पंचांगp)
		lock_release(&dma_fence_lockdep_map, _THIS_IP_);
	lock_map_acquire(&dma_fence_lockdep_map);
	lock_map_release(&dma_fence_lockdep_map);
	अगर (पंचांगp)
		lock_acquire(&dma_fence_lockdep_map, 0, 0, 1, 1, शून्य, _THIS_IP_);
पूर्ण
#पूर्ण_अगर


/**
 * dma_fence_संकेत_बारtamp_locked - संकेत completion of a fence
 * @fence: the fence to संकेत
 * @बारtamp: fence संकेत बारtamp in kernel's CLOCK_MONOTONIC समय करोमुख्य
 *
 * Signal completion क्रम software callbacks on a fence, this will unblock
 * dma_fence_रुको() calls and run all the callbacks added with
 * dma_fence_add_callback(). Can be called multiple बार, but since a fence
 * can only go from the unसंकेतed to the संकेतed state and not back, it will
 * only be effective the first समय. Set the बारtamp provided as the fence
 * संकेत बारtamp.
 *
 * Unlike dma_fence_संकेत_बारtamp(), this function must be called with
 * &dma_fence.lock held.
 *
 * Returns 0 on success and a negative error value when @fence has been
 * संकेतled alपढ़ोy.
 */
पूर्णांक dma_fence_संकेत_बारtamp_locked(काष्ठा dma_fence *fence,
				      kसमय_प्रकार बारtamp)
अणु
	काष्ठा dma_fence_cb *cur, *पंचांगp;
	काष्ठा list_head cb_list;

	lockdep_निश्चित_held(fence->lock);

	अगर (unlikely(test_and_set_bit(DMA_FENCE_FLAG_SIGNALED_BIT,
				      &fence->flags)))
		वापस -EINVAL;

	/* Stash the cb_list beक्रमe replacing it with the बारtamp */
	list_replace(&fence->cb_list, &cb_list);

	fence->बारtamp = बारtamp;
	set_bit(DMA_FENCE_FLAG_TIMESTAMP_BIT, &fence->flags);
	trace_dma_fence_संकेतed(fence);

	list_क्रम_each_entry_safe(cur, पंचांगp, &cb_list, node) अणु
		INIT_LIST_HEAD(&cur->node);
		cur->func(fence, cur);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(dma_fence_संकेत_बारtamp_locked);

/**
 * dma_fence_संकेत_बारtamp - संकेत completion of a fence
 * @fence: the fence to संकेत
 * @बारtamp: fence संकेत बारtamp in kernel's CLOCK_MONOTONIC समय करोमुख्य
 *
 * Signal completion क्रम software callbacks on a fence, this will unblock
 * dma_fence_रुको() calls and run all the callbacks added with
 * dma_fence_add_callback(). Can be called multiple बार, but since a fence
 * can only go from the unसंकेतed to the संकेतed state and not back, it will
 * only be effective the first समय. Set the बारtamp provided as the fence
 * संकेत बारtamp.
 *
 * Returns 0 on success and a negative error value when @fence has been
 * संकेतled alपढ़ोy.
 */
पूर्णांक dma_fence_संकेत_बारtamp(काष्ठा dma_fence *fence, kसमय_प्रकार बारtamp)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!fence)
		वापस -EINVAL;

	spin_lock_irqsave(fence->lock, flags);
	ret = dma_fence_संकेत_बारtamp_locked(fence, बारtamp);
	spin_unlock_irqrestore(fence->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dma_fence_संकेत_बारtamp);

/**
 * dma_fence_संकेत_locked - संकेत completion of a fence
 * @fence: the fence to संकेत
 *
 * Signal completion क्रम software callbacks on a fence, this will unblock
 * dma_fence_रुको() calls and run all the callbacks added with
 * dma_fence_add_callback(). Can be called multiple बार, but since a fence
 * can only go from the unसंकेतed to the संकेतed state and not back, it will
 * only be effective the first समय.
 *
 * Unlike dma_fence_संकेत(), this function must be called with &dma_fence.lock
 * held.
 *
 * Returns 0 on success and a negative error value when @fence has been
 * संकेतled alपढ़ोy.
 */
पूर्णांक dma_fence_संकेत_locked(काष्ठा dma_fence *fence)
अणु
	वापस dma_fence_संकेत_बारtamp_locked(fence, kसमय_get());
पूर्ण
EXPORT_SYMBOL(dma_fence_संकेत_locked);

/**
 * dma_fence_संकेत - संकेत completion of a fence
 * @fence: the fence to संकेत
 *
 * Signal completion क्रम software callbacks on a fence, this will unblock
 * dma_fence_रुको() calls and run all the callbacks added with
 * dma_fence_add_callback(). Can be called multiple बार, but since a fence
 * can only go from the unसंकेतed to the संकेतed state and not back, it will
 * only be effective the first समय.
 *
 * Returns 0 on success and a negative error value when @fence has been
 * संकेतled alपढ़ोy.
 */
पूर्णांक dma_fence_संकेत(काष्ठा dma_fence *fence)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	bool पंचांगp;

	अगर (!fence)
		वापस -EINVAL;

	पंचांगp = dma_fence_begin_संकेतling();

	spin_lock_irqsave(fence->lock, flags);
	ret = dma_fence_संकेत_बारtamp_locked(fence, kसमय_get());
	spin_unlock_irqrestore(fence->lock, flags);

	dma_fence_end_संकेतling(पंचांगp);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dma_fence_संकेत);

/**
 * dma_fence_रुको_समयout - sleep until the fence माला_लो संकेतed
 * or until समयout elapses
 * @fence: the fence to रुको on
 * @पूर्णांकr: अगर true, करो an पूर्णांकerruptible रुको
 * @समयout: समयout value in jअगरfies, or MAX_SCHEDULE_TIMEOUT
 *
 * Returns -ERESTARTSYS अगर पूर्णांकerrupted, 0 अगर the रुको समयd out, or the
 * reमुख्यing समयout in jअगरfies on success. Other error values may be
 * वापसed on custom implementations.
 *
 * Perक्रमms a synchronous रुको on this fence. It is assumed the caller
 * directly or indirectly (buf-mgr between reservation and committing)
 * holds a reference to the fence, otherwise the fence might be
 * मुक्तd beक्रमe वापस, resulting in undefined behavior.
 *
 * See also dma_fence_रुको() and dma_fence_रुको_any_समयout().
 */
चिन्हित दीर्घ
dma_fence_रुको_समयout(काष्ठा dma_fence *fence, bool पूर्णांकr, चिन्हित दीर्घ समयout)
अणु
	चिन्हित दीर्घ ret;

	अगर (WARN_ON(समयout < 0))
		वापस -EINVAL;

	might_sleep();

	__dma_fence_might_रुको();

	trace_dma_fence_रुको_start(fence);
	अगर (fence->ops->रुको)
		ret = fence->ops->रुको(fence, पूर्णांकr, समयout);
	अन्यथा
		ret = dma_fence_शेष_रुको(fence, पूर्णांकr, समयout);
	trace_dma_fence_रुको_end(fence);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dma_fence_रुको_समयout);

/**
 * dma_fence_release - शेष relese function क्रम fences
 * @kref: &dma_fence.recfount
 *
 * This is the शेष release functions क्रम &dma_fence. Drivers shouldn't call
 * this directly, but instead call dma_fence_put().
 */
व्योम dma_fence_release(काष्ठा kref *kref)
अणु
	काष्ठा dma_fence *fence =
		container_of(kref, काष्ठा dma_fence, refcount);

	trace_dma_fence_destroy(fence);

	अगर (WARN(!list_empty(&fence->cb_list) &&
		 !test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags),
		 "Fence %s:%s:%llx:%llx released with pending signals!\n",
		 fence->ops->get_driver_name(fence),
		 fence->ops->get_समयline_name(fence),
		 fence->context, fence->seqno)) अणु
		अचिन्हित दीर्घ flags;

		/*
		 * Failed to संकेत beक्रमe release, likely a refcounting issue.
		 *
		 * This should never happen, but अगर it करोes make sure that we
		 * करोn't leave chains dangling. We set the error flag first
		 * so that the callbacks know this संकेत is due to an error.
		 */
		spin_lock_irqsave(fence->lock, flags);
		fence->error = -EDEADLK;
		dma_fence_संकेत_locked(fence);
		spin_unlock_irqrestore(fence->lock, flags);
	पूर्ण

	अगर (fence->ops->release)
		fence->ops->release(fence);
	अन्यथा
		dma_fence_मुक्त(fence);
पूर्ण
EXPORT_SYMBOL(dma_fence_release);

/**
 * dma_fence_मुक्त - शेष release function क्रम &dma_fence.
 * @fence: fence to release
 *
 * This is the शेष implementation क्रम &dma_fence_ops.release. It calls
 * kमुक्त_rcu() on @fence.
 */
व्योम dma_fence_मुक्त(काष्ठा dma_fence *fence)
अणु
	kमुक्त_rcu(fence, rcu);
पूर्ण
EXPORT_SYMBOL(dma_fence_मुक्त);

अटल bool __dma_fence_enable_संकेतing(काष्ठा dma_fence *fence)
अणु
	bool was_set;

	lockdep_निश्चित_held(fence->lock);

	was_set = test_and_set_bit(DMA_FENCE_FLAG_ENABLE_SIGNAL_BIT,
				   &fence->flags);

	अगर (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags))
		वापस false;

	अगर (!was_set && fence->ops->enable_संकेतing) अणु
		trace_dma_fence_enable_संकेत(fence);

		अगर (!fence->ops->enable_संकेतing(fence)) अणु
			dma_fence_संकेत_locked(fence);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

/**
 * dma_fence_enable_sw_संकेतing - enable संकेतing on fence
 * @fence: the fence to enable
 *
 * This will request क्रम sw संकेतing to be enabled, to make the fence
 * complete as soon as possible. This calls &dma_fence_ops.enable_संकेतing
 * पूर्णांकernally.
 */
व्योम dma_fence_enable_sw_संकेतing(काष्ठा dma_fence *fence)
अणु
	अचिन्हित दीर्घ flags;

	अगर (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags))
		वापस;

	spin_lock_irqsave(fence->lock, flags);
	__dma_fence_enable_संकेतing(fence);
	spin_unlock_irqrestore(fence->lock, flags);
पूर्ण
EXPORT_SYMBOL(dma_fence_enable_sw_संकेतing);

/**
 * dma_fence_add_callback - add a callback to be called when the fence
 * is संकेतed
 * @fence: the fence to रुको on
 * @cb: the callback to रेजिस्टर
 * @func: the function to call
 *
 * @cb will be initialized by dma_fence_add_callback(), no initialization
 * by the caller is required. Any number of callbacks can be रेजिस्टरed
 * to a fence, but a callback can only be रेजिस्टरed to one fence at a समय.
 *
 * Note that the callback can be called from an atomic context.  If
 * fence is alपढ़ोy संकेतed, this function will वापस -ENOENT (and
 * *not* call the callback).
 *
 * Add a software callback to the fence. Same restrictions apply to
 * refcount as it करोes to dma_fence_रुको(), however the caller करोesn't need to
 * keep a refcount to fence afterward dma_fence_add_callback() has वापसed:
 * when software access is enabled, the creator of the fence is required to keep
 * the fence alive until after it संकेतs with dma_fence_संकेत(). The callback
 * itself can be called from irq context.
 *
 * Returns 0 in हाल of success, -ENOENT अगर the fence is alपढ़ोy संकेतed
 * and -EINVAL in हाल of error.
 */
पूर्णांक dma_fence_add_callback(काष्ठा dma_fence *fence, काष्ठा dma_fence_cb *cb,
			   dma_fence_func_t func)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (WARN_ON(!fence || !func))
		वापस -EINVAL;

	अगर (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags)) अणु
		INIT_LIST_HEAD(&cb->node);
		वापस -ENOENT;
	पूर्ण

	spin_lock_irqsave(fence->lock, flags);

	अगर (__dma_fence_enable_संकेतing(fence)) अणु
		cb->func = func;
		list_add_tail(&cb->node, &fence->cb_list);
	पूर्ण अन्यथा अणु
		INIT_LIST_HEAD(&cb->node);
		ret = -ENOENT;
	पूर्ण

	spin_unlock_irqrestore(fence->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dma_fence_add_callback);

/**
 * dma_fence_get_status - वापसs the status upon completion
 * @fence: the dma_fence to query
 *
 * This wraps dma_fence_get_status_locked() to वापस the error status
 * condition on a संकेतed fence. See dma_fence_get_status_locked() क्रम more
 * details.
 *
 * Returns 0 अगर the fence has not yet been संकेतed, 1 अगर the fence has
 * been संकेतed without an error condition, or a negative error code
 * अगर the fence has been completed in err.
 */
पूर्णांक dma_fence_get_status(काष्ठा dma_fence *fence)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक status;

	spin_lock_irqsave(fence->lock, flags);
	status = dma_fence_get_status_locked(fence);
	spin_unlock_irqrestore(fence->lock, flags);

	वापस status;
पूर्ण
EXPORT_SYMBOL(dma_fence_get_status);

/**
 * dma_fence_हटाओ_callback - हटाओ a callback from the संकेतing list
 * @fence: the fence to रुको on
 * @cb: the callback to हटाओ
 *
 * Remove a previously queued callback from the fence. This function वापसs
 * true अगर the callback is successfully हटाओd, or false अगर the fence has
 * alपढ़ोy been संकेतed.
 *
 * *WARNING*:
 * Cancelling a callback should only be करोne अगर you really know what you're
 * करोing, since deadlocks and race conditions could occur all too easily. For
 * this reason, it should only ever be करोne on hardware lockup recovery,
 * with a reference held to the fence.
 *
 * Behaviour is undefined अगर @cb has not been added to @fence using
 * dma_fence_add_callback() beक्रमehand.
 */
bool
dma_fence_हटाओ_callback(काष्ठा dma_fence *fence, काष्ठा dma_fence_cb *cb)
अणु
	अचिन्हित दीर्घ flags;
	bool ret;

	spin_lock_irqsave(fence->lock, flags);

	ret = !list_empty(&cb->node);
	अगर (ret)
		list_del_init(&cb->node);

	spin_unlock_irqrestore(fence->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dma_fence_हटाओ_callback);

काष्ठा शेष_रुको_cb अणु
	काष्ठा dma_fence_cb base;
	काष्ठा task_काष्ठा *task;
पूर्ण;

अटल व्योम
dma_fence_शेष_रुको_cb(काष्ठा dma_fence *fence, काष्ठा dma_fence_cb *cb)
अणु
	काष्ठा शेष_रुको_cb *रुको =
		container_of(cb, काष्ठा शेष_रुको_cb, base);

	wake_up_state(रुको->task, TASK_NORMAL);
पूर्ण

/**
 * dma_fence_शेष_रुको - शेष sleep until the fence माला_लो संकेतed
 * or until समयout elapses
 * @fence: the fence to रुको on
 * @पूर्णांकr: अगर true, करो an पूर्णांकerruptible रुको
 * @समयout: समयout value in jअगरfies, or MAX_SCHEDULE_TIMEOUT
 *
 * Returns -ERESTARTSYS अगर पूर्णांकerrupted, 0 अगर the रुको समयd out, or the
 * reमुख्यing समयout in jअगरfies on success. If समयout is zero the value one is
 * वापसed अगर the fence is alपढ़ोy संकेतed क्रम consistency with other
 * functions taking a jअगरfies समयout.
 */
चिन्हित दीर्घ
dma_fence_शेष_रुको(काष्ठा dma_fence *fence, bool पूर्णांकr, चिन्हित दीर्घ समयout)
अणु
	काष्ठा शेष_रुको_cb cb;
	अचिन्हित दीर्घ flags;
	चिन्हित दीर्घ ret = समयout ? समयout : 1;

	अगर (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags))
		वापस ret;

	spin_lock_irqsave(fence->lock, flags);

	अगर (पूर्णांकr && संकेत_pending(current)) अणु
		ret = -ERESTARTSYS;
		जाओ out;
	पूर्ण

	अगर (!__dma_fence_enable_संकेतing(fence))
		जाओ out;

	अगर (!समयout) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	cb.base.func = dma_fence_शेष_रुको_cb;
	cb.task = current;
	list_add(&cb.base.node, &fence->cb_list);

	जबतक (!test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags) && ret > 0) अणु
		अगर (पूर्णांकr)
			__set_current_state(TASK_INTERRUPTIBLE);
		अन्यथा
			__set_current_state(TASK_UNINTERRUPTIBLE);
		spin_unlock_irqrestore(fence->lock, flags);

		ret = schedule_समयout(ret);

		spin_lock_irqsave(fence->lock, flags);
		अगर (ret > 0 && पूर्णांकr && संकेत_pending(current))
			ret = -ERESTARTSYS;
	पूर्ण

	अगर (!list_empty(&cb.base.node))
		list_del(&cb.base.node);
	__set_current_state(TASK_RUNNING);

out:
	spin_unlock_irqrestore(fence->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(dma_fence_शेष_रुको);

अटल bool
dma_fence_test_संकेतed_any(काष्ठा dma_fence **fences, uपूर्णांक32_t count,
			    uपूर्णांक32_t *idx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; ++i) अणु
		काष्ठा dma_fence *fence = fences[i];
		अगर (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &fence->flags)) अणु
			अगर (idx)
				*idx = i;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

/**
 * dma_fence_रुको_any_समयout - sleep until any fence माला_लो संकेतed
 * or until समयout elapses
 * @fences: array of fences to रुको on
 * @count: number of fences to रुको on
 * @पूर्णांकr: अगर true, करो an पूर्णांकerruptible रुको
 * @समयout: समयout value in jअगरfies, or MAX_SCHEDULE_TIMEOUT
 * @idx: used to store the first संकेतed fence index, meaningful only on
 *	positive वापस
 *
 * Returns -EINVAL on custom fence रुको implementation, -ERESTARTSYS अगर
 * पूर्णांकerrupted, 0 अगर the रुको समयd out, or the reमुख्यing समयout in jअगरfies
 * on success.
 *
 * Synchronous रुकोs क्रम the first fence in the array to be संकेतed. The
 * caller needs to hold a reference to all fences in the array, otherwise a
 * fence might be मुक्तd beक्रमe वापस, resulting in undefined behavior.
 *
 * See also dma_fence_रुको() and dma_fence_रुको_समयout().
 */
चिन्हित दीर्घ
dma_fence_रुको_any_समयout(काष्ठा dma_fence **fences, uपूर्णांक32_t count,
			   bool पूर्णांकr, चिन्हित दीर्घ समयout, uपूर्णांक32_t *idx)
अणु
	काष्ठा शेष_रुको_cb *cb;
	चिन्हित दीर्घ ret = समयout;
	अचिन्हित i;

	अगर (WARN_ON(!fences || !count || समयout < 0))
		वापस -EINVAL;

	अगर (समयout == 0) अणु
		क्रम (i = 0; i < count; ++i)
			अगर (dma_fence_is_संकेतed(fences[i])) अणु
				अगर (idx)
					*idx = i;
				वापस 1;
			पूर्ण

		वापस 0;
	पूर्ण

	cb = kसुस्मृति(count, माप(काष्ठा शेष_रुको_cb), GFP_KERNEL);
	अगर (cb == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_cb;
	पूर्ण

	क्रम (i = 0; i < count; ++i) अणु
		काष्ठा dma_fence *fence = fences[i];

		cb[i].task = current;
		अगर (dma_fence_add_callback(fence, &cb[i].base,
					   dma_fence_शेष_रुको_cb)) अणु
			/* This fence is alपढ़ोy संकेतed */
			अगर (idx)
				*idx = i;
			जाओ fence_rm_cb;
		पूर्ण
	पूर्ण

	जबतक (ret > 0) अणु
		अगर (पूर्णांकr)
			set_current_state(TASK_INTERRUPTIBLE);
		अन्यथा
			set_current_state(TASK_UNINTERRUPTIBLE);

		अगर (dma_fence_test_संकेतed_any(fences, count, idx))
			अवरोध;

		ret = schedule_समयout(ret);

		अगर (ret > 0 && पूर्णांकr && संकेत_pending(current))
			ret = -ERESTARTSYS;
	पूर्ण

	__set_current_state(TASK_RUNNING);

fence_rm_cb:
	जबतक (i-- > 0)
		dma_fence_हटाओ_callback(fences[i], &cb[i].base);

err_मुक्त_cb:
	kमुक्त(cb);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dma_fence_रुको_any_समयout);

/**
 * dma_fence_init - Initialize a custom fence.
 * @fence: the fence to initialize
 * @ops: the dma_fence_ops क्रम operations on this fence
 * @lock: the irqsafe spinlock to use क्रम locking this fence
 * @context: the execution context this fence is run on
 * @seqno: a linear increasing sequence number क्रम this context
 *
 * Initializes an allocated fence, the caller करोesn't have to keep its
 * refcount after committing with this fence, but it will need to hold a
 * refcount again अगर &dma_fence_ops.enable_संकेतing माला_लो called.
 *
 * context and seqno are used क्रम easy comparison between fences, allowing
 * to check which fence is later by simply using dma_fence_later().
 */
व्योम
dma_fence_init(काष्ठा dma_fence *fence, स्थिर काष्ठा dma_fence_ops *ops,
	       spinlock_t *lock, u64 context, u64 seqno)
अणु
	BUG_ON(!lock);
	BUG_ON(!ops || !ops->get_driver_name || !ops->get_समयline_name);

	kref_init(&fence->refcount);
	fence->ops = ops;
	INIT_LIST_HEAD(&fence->cb_list);
	fence->lock = lock;
	fence->context = context;
	fence->seqno = seqno;
	fence->flags = 0UL;
	fence->error = 0;

	trace_dma_fence_init(fence);
पूर्ण
EXPORT_SYMBOL(dma_fence_init);
