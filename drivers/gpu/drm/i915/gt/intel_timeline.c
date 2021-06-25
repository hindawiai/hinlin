<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2016-2018 Intel Corporation
 */

#समावेश "i915_drv.h"

#समावेश "i915_active.h"
#समावेश "i915_syncmap.h"
#समावेश "intel_gt.h"
#समावेश "intel_ring.h"
#समावेश "intel_timeline.h"

#घोषणा TIMELINE_SEQNO_BYTES 8

अटल काष्ठा i915_vma *hwsp_alloc(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;

	obj = i915_gem_object_create_पूर्णांकernal(i915, PAGE_SIZE);
	अगर (IS_ERR(obj))
		वापस ERR_CAST(obj);

	i915_gem_object_set_cache_coherency(obj, I915_CACHE_LLC);

	vma = i915_vma_instance(obj, &gt->ggtt->vm, शून्य);
	अगर (IS_ERR(vma))
		i915_gem_object_put(obj);

	वापस vma;
पूर्ण

__i915_active_call
अटल व्योम __समयline_retire(काष्ठा i915_active *active)
अणु
	काष्ठा पूर्णांकel_समयline *tl =
		container_of(active, typeof(*tl), active);

	i915_vma_unpin(tl->hwsp_ggtt);
	पूर्णांकel_समयline_put(tl);
पूर्ण

अटल पूर्णांक __समयline_active(काष्ठा i915_active *active)
अणु
	काष्ठा पूर्णांकel_समयline *tl =
		container_of(active, typeof(*tl), active);

	__i915_vma_pin(tl->hwsp_ggtt);
	पूर्णांकel_समयline_get(tl);
	वापस 0;
पूर्ण

I915_SELFTEST_EXPORT पूर्णांक
पूर्णांकel_समयline_pin_map(काष्ठा पूर्णांकel_समयline *समयline)
अणु
	काष्ठा drm_i915_gem_object *obj = समयline->hwsp_ggtt->obj;
	u32 ofs = offset_in_page(समयline->hwsp_offset);
	व्योम *vaddr;

	vaddr = i915_gem_object_pin_map(obj, I915_MAP_WB);
	अगर (IS_ERR(vaddr))
		वापस PTR_ERR(vaddr);

	समयline->hwsp_map = vaddr;
	समयline->hwsp_seqno = स_रखो(vaddr + ofs, 0, TIMELINE_SEQNO_BYTES);
	clflush(vaddr + ofs);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_समयline_init(काष्ठा पूर्णांकel_समयline *समयline,
			       काष्ठा पूर्णांकel_gt *gt,
			       काष्ठा i915_vma *hwsp,
			       अचिन्हित पूर्णांक offset)
अणु
	kref_init(&समयline->kref);
	atomic_set(&समयline->pin_count, 0);

	समयline->gt = gt;

	अगर (hwsp) अणु
		समयline->hwsp_offset = offset;
		समयline->hwsp_ggtt = i915_vma_get(hwsp);
	पूर्ण अन्यथा अणु
		समयline->has_initial_bपढ़ोcrumb = true;
		hwsp = hwsp_alloc(gt);
		अगर (IS_ERR(hwsp))
			वापस PTR_ERR(hwsp);
		समयline->hwsp_ggtt = hwsp;
	पूर्ण

	समयline->hwsp_map = शून्य;
	समयline->hwsp_seqno = (व्योम *)(दीर्घ)समयline->hwsp_offset;

	GEM_BUG_ON(समयline->hwsp_offset >= hwsp->size);

	समयline->fence_context = dma_fence_context_alloc(1);

	mutex_init(&समयline->mutex);

	INIT_ACTIVE_FENCE(&समयline->last_request);
	INIT_LIST_HEAD(&समयline->requests);

	i915_syncmap_init(&समयline->sync);
	i915_active_init(&समयline->active, __समयline_active, __समयline_retire);

	वापस 0;
पूर्ण

व्योम पूर्णांकel_gt_init_समयlines(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_gt_समयlines *समयlines = &gt->समयlines;

	spin_lock_init(&समयlines->lock);
	INIT_LIST_HEAD(&समयlines->active_list);
पूर्ण

अटल व्योम पूर्णांकel_समयline_fini(काष्ठा rcu_head *rcu)
अणु
	काष्ठा पूर्णांकel_समयline *समयline =
		container_of(rcu, काष्ठा पूर्णांकel_समयline, rcu);

	अगर (समयline->hwsp_map)
		i915_gem_object_unpin_map(समयline->hwsp_ggtt->obj);

	i915_vma_put(समयline->hwsp_ggtt);
	i915_active_fini(&समयline->active);
	kमुक्त(समयline);
पूर्ण

काष्ठा पूर्णांकel_समयline *
__पूर्णांकel_समयline_create(काष्ठा पूर्णांकel_gt *gt,
			काष्ठा i915_vma *global_hwsp,
			अचिन्हित पूर्णांक offset)
अणु
	काष्ठा पूर्णांकel_समयline *समयline;
	पूर्णांक err;

	समयline = kzalloc(माप(*समयline), GFP_KERNEL);
	अगर (!समयline)
		वापस ERR_PTR(-ENOMEM);

	err = पूर्णांकel_समयline_init(समयline, gt, global_hwsp, offset);
	अगर (err) अणु
		kमुक्त(समयline);
		वापस ERR_PTR(err);
	पूर्ण

	वापस समयline;
पूर्ण

काष्ठा पूर्णांकel_समयline *
पूर्णांकel_समयline_create_from_engine(काष्ठा पूर्णांकel_engine_cs *engine,
				  अचिन्हित पूर्णांक offset)
अणु
	काष्ठा i915_vma *hwsp = engine->status_page.vma;
	काष्ठा पूर्णांकel_समयline *tl;

	tl = __पूर्णांकel_समयline_create(engine->gt, hwsp, offset);
	अगर (IS_ERR(tl))
		वापस tl;

	/* Borrow a nearby lock; we only create these समयlines during init */
	mutex_lock(&hwsp->vm->mutex);
	list_add_tail(&tl->engine_link, &engine->status_page.समयlines);
	mutex_unlock(&hwsp->vm->mutex);

	वापस tl;
पूर्ण

व्योम __पूर्णांकel_समयline_pin(काष्ठा पूर्णांकel_समयline *tl)
अणु
	GEM_BUG_ON(!atomic_पढ़ो(&tl->pin_count));
	atomic_inc(&tl->pin_count);
पूर्ण

पूर्णांक पूर्णांकel_समयline_pin(काष्ठा पूर्णांकel_समयline *tl, काष्ठा i915_gem_ww_ctx *ww)
अणु
	पूर्णांक err;

	अगर (atomic_add_unless(&tl->pin_count, 1, 0))
		वापस 0;

	अगर (!tl->hwsp_map) अणु
		err = पूर्णांकel_समयline_pin_map(tl);
		अगर (err)
			वापस err;
	पूर्ण

	err = i915_ggtt_pin(tl->hwsp_ggtt, ww, 0, PIN_HIGH);
	अगर (err)
		वापस err;

	tl->hwsp_offset =
		i915_ggtt_offset(tl->hwsp_ggtt) +
		offset_in_page(tl->hwsp_offset);
	GT_TRACE(tl->gt, "timeline:%llx using HWSP offset:%x\n",
		 tl->fence_context, tl->hwsp_offset);

	i915_active_acquire(&tl->active);
	अगर (atomic_fetch_inc(&tl->pin_count)) अणु
		i915_active_release(&tl->active);
		__i915_vma_unpin(tl->hwsp_ggtt);
	पूर्ण

	वापस 0;
पूर्ण

व्योम पूर्णांकel_समयline_reset_seqno(स्थिर काष्ठा पूर्णांकel_समयline *tl)
अणु
	u32 *hwsp_seqno = (u32 *)tl->hwsp_seqno;
	/* Must be pinned to be writable, and no requests in flight. */
	GEM_BUG_ON(!atomic_पढ़ो(&tl->pin_count));

	स_रखो(hwsp_seqno + 1, 0, TIMELINE_SEQNO_BYTES - माप(*hwsp_seqno));
	WRITE_ONCE(*hwsp_seqno, tl->seqno);
	clflush(hwsp_seqno);
पूर्ण

व्योम पूर्णांकel_समयline_enter(काष्ठा पूर्णांकel_समयline *tl)
अणु
	काष्ठा पूर्णांकel_gt_समयlines *समयlines = &tl->gt->समयlines;

	/*
	 * Pretend we are serialised by the समयline->mutex.
	 *
	 * While generally true, there are a few exceptions to the rule
	 * क्रम the engine->kernel_context being used to manage घातer
	 * transitions. As the engine_park may be called from under any
	 * समयline, it uses the घातer mutex as a global serialisation
	 * lock to prevent any other request entering its समयline.
	 *
	 * The rule is generally tl->mutex, otherwise engine->wakeref.mutex.
	 *
	 * However, पूर्णांकel_gt_retire_request() करोes not know which engine
	 * it is retiring aदीर्घ and so cannot partake in the engine-pm
	 * barrier, and there we use the tl->active_count as a means to
	 * pin the समयline in the active_list जबतक the locks are dropped.
	 * Ergo, as that is outside of the engine-pm barrier, we need to
	 * use atomic to manipulate tl->active_count.
	 */
	lockdep_निश्चित_held(&tl->mutex);

	अगर (atomic_add_unless(&tl->active_count, 1, 0))
		वापस;

	spin_lock(&समयlines->lock);
	अगर (!atomic_fetch_inc(&tl->active_count)) अणु
		/*
		 * The HWSP is अस्थिर, and may have been lost जबतक inactive,
		 * e.g. across suspend/resume. Be paranoid, and ensure that
		 * the HWSP value matches our seqno so we करोn't proclaim
		 * the next request as alपढ़ोy complete.
		 */
		पूर्णांकel_समयline_reset_seqno(tl);
		list_add_tail(&tl->link, &समयlines->active_list);
	पूर्ण
	spin_unlock(&समयlines->lock);
पूर्ण

व्योम पूर्णांकel_समयline_निकास(काष्ठा पूर्णांकel_समयline *tl)
अणु
	काष्ठा पूर्णांकel_gt_समयlines *समयlines = &tl->gt->समयlines;

	/* See पूर्णांकel_समयline_enter() */
	lockdep_निश्चित_held(&tl->mutex);

	GEM_BUG_ON(!atomic_पढ़ो(&tl->active_count));
	अगर (atomic_add_unless(&tl->active_count, -1, 1))
		वापस;

	spin_lock(&समयlines->lock);
	अगर (atomic_dec_and_test(&tl->active_count))
		list_del(&tl->link);
	spin_unlock(&समयlines->lock);

	/*
	 * Since this समयline is idle, all bariers upon which we were रुकोing
	 * must also be complete and so we can discard the last used barriers
	 * without loss of inक्रमmation.
	 */
	i915_syncmap_मुक्त(&tl->sync);
पूर्ण

अटल u32 समयline_advance(काष्ठा पूर्णांकel_समयline *tl)
अणु
	GEM_BUG_ON(!atomic_पढ़ो(&tl->pin_count));
	GEM_BUG_ON(tl->seqno & tl->has_initial_bपढ़ोcrumb);

	वापस tl->seqno += 1 + tl->has_initial_bपढ़ोcrumb;
पूर्ण

अटल noअंतरभूत पूर्णांक
__पूर्णांकel_समयline_get_seqno(काष्ठा पूर्णांकel_समयline *tl,
			   u32 *seqno)
अणु
	u32 next_ofs = offset_in_page(tl->hwsp_offset + TIMELINE_SEQNO_BYTES);

	/* w/a: bit 5 needs to be zero क्रम MI_FLUSH_DW address. */
	अगर (TIMELINE_SEQNO_BYTES <= BIT(5) && (next_ofs & BIT(5)))
		next_ofs = offset_in_page(next_ofs + BIT(5));

	tl->hwsp_offset = i915_ggtt_offset(tl->hwsp_ggtt) + next_ofs;
	tl->hwsp_seqno = tl->hwsp_map + next_ofs;
	पूर्णांकel_समयline_reset_seqno(tl);

	*seqno = समयline_advance(tl);
	GEM_BUG_ON(i915_seqno_passed(*tl->hwsp_seqno, *seqno));
	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_समयline_get_seqno(काष्ठा पूर्णांकel_समयline *tl,
			     काष्ठा i915_request *rq,
			     u32 *seqno)
अणु
	*seqno = समयline_advance(tl);

	/* Replace the HWSP on wraparound क्रम HW semaphores */
	अगर (unlikely(!*seqno && tl->has_initial_bपढ़ोcrumb))
		वापस __पूर्णांकel_समयline_get_seqno(tl, seqno);

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_समयline_पढ़ो_hwsp(काष्ठा i915_request *from,
			     काष्ठा i915_request *to,
			     u32 *hwsp)
अणु
	काष्ठा पूर्णांकel_समयline *tl;
	पूर्णांक err;

	rcu_पढ़ो_lock();
	tl = rcu_dereference(from->समयline);
	अगर (i915_request_संकेतed(from) ||
	    !i915_active_acquire_अगर_busy(&tl->active))
		tl = शून्य;

	अगर (tl) अणु
		/* hwsp_offset may wraparound, so use from->hwsp_seqno */
		*hwsp = i915_ggtt_offset(tl->hwsp_ggtt) +
			offset_in_page(from->hwsp_seqno);
	पूर्ण

	/* ensure we रुको on the right request, अगर not, we completed */
	अगर (tl && __i915_request_is_complete(from)) अणु
		i915_active_release(&tl->active);
		tl = शून्य;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (!tl)
		वापस 1;

	/* Can't करो semaphore रुकोs on kernel context */
	अगर (!tl->has_initial_bपढ़ोcrumb) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	err = i915_active_add_request(&tl->active, to);

out:
	i915_active_release(&tl->active);
	वापस err;
पूर्ण

व्योम पूर्णांकel_समयline_unpin(काष्ठा पूर्णांकel_समयline *tl)
अणु
	GEM_BUG_ON(!atomic_पढ़ो(&tl->pin_count));
	अगर (!atomic_dec_and_test(&tl->pin_count))
		वापस;

	i915_active_release(&tl->active);
	__i915_vma_unpin(tl->hwsp_ggtt);
पूर्ण

व्योम __पूर्णांकel_समयline_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा पूर्णांकel_समयline *समयline =
		container_of(kref, typeof(*समयline), kref);

	GEM_BUG_ON(atomic_पढ़ो(&समयline->pin_count));
	GEM_BUG_ON(!list_empty(&समयline->requests));
	GEM_BUG_ON(समयline->retire);

	call_rcu(&समयline->rcu, पूर्णांकel_समयline_fini);
पूर्ण

व्योम पूर्णांकel_gt_fini_समयlines(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा पूर्णांकel_gt_समयlines *समयlines = &gt->समयlines;

	GEM_BUG_ON(!list_empty(&समयlines->active_list));
पूर्ण

व्योम पूर्णांकel_gt_show_समयlines(काष्ठा पूर्णांकel_gt *gt,
			     काष्ठा drm_prपूर्णांकer *m,
			     व्योम (*show_request)(काष्ठा drm_prपूर्णांकer *m,
						  स्थिर काष्ठा i915_request *rq,
						  स्थिर अक्षर *prefix,
						  पूर्णांक indent))
अणु
	काष्ठा पूर्णांकel_gt_समयlines *समयlines = &gt->समयlines;
	काष्ठा पूर्णांकel_समयline *tl, *tn;
	LIST_HEAD(मुक्त);

	spin_lock(&समयlines->lock);
	list_क्रम_each_entry_safe(tl, tn, &समयlines->active_list, link) अणु
		अचिन्हित दीर्घ count, पढ़ोy, inflight;
		काष्ठा i915_request *rq, *rn;
		काष्ठा dma_fence *fence;

		अगर (!mutex_trylock(&tl->mutex)) अणु
			drm_म_लिखो(m, "Timeline %llx: busy; skipping\n",
				   tl->fence_context);
			जारी;
		पूर्ण

		पूर्णांकel_समयline_get(tl);
		GEM_BUG_ON(!atomic_पढ़ो(&tl->active_count));
		atomic_inc(&tl->active_count); /* pin the list element */
		spin_unlock(&समयlines->lock);

		count = 0;
		पढ़ोy = 0;
		inflight = 0;
		list_क्रम_each_entry_safe(rq, rn, &tl->requests, link) अणु
			अगर (i915_request_completed(rq))
				जारी;

			count++;
			अगर (i915_request_is_पढ़ोy(rq))
				पढ़ोy++;
			अगर (i915_request_is_active(rq))
				inflight++;
		पूर्ण

		drm_म_लिखो(m, "Timeline %llx: { ", tl->fence_context);
		drm_म_लिखो(m, "count: %lu, ready: %lu, inflight: %lu",
			   count, पढ़ोy, inflight);
		drm_म_लिखो(m, ", seqno: { current: %d, last: %d }",
			   *tl->hwsp_seqno, tl->seqno);
		fence = i915_active_fence_get(&tl->last_request);
		अगर (fence) अणु
			drm_म_लिखो(m, ", engine: %s",
				   to_request(fence)->engine->name);
			dma_fence_put(fence);
		पूर्ण
		drm_म_लिखो(m, " }\n");

		अगर (show_request) अणु
			list_क्रम_each_entry_safe(rq, rn, &tl->requests, link)
				show_request(m, rq, "", 2);
		पूर्ण

		mutex_unlock(&tl->mutex);
		spin_lock(&समयlines->lock);

		/* Resume list iteration after reacquiring spinlock */
		list_safe_reset_next(tl, tn, link);
		अगर (atomic_dec_and_test(&tl->active_count))
			list_del(&tl->link);

		/* Defer the final release to after the spinlock */
		अगर (refcount_dec_and_test(&tl->kref.refcount)) अणु
			GEM_BUG_ON(atomic_पढ़ो(&tl->active_count));
			list_add(&tl->link, &मुक्त);
		पूर्ण
	पूर्ण
	spin_unlock(&समयlines->lock);

	list_क्रम_each_entry_safe(tl, tn, &मुक्त, link)
		__पूर्णांकel_समयline_मुक्त(&tl->kref);
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "gt/selftests/mock_timeline.c"
#समावेश "gt/selftest_timeline.c"
#पूर्ण_अगर
