<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2008-2015 Intel Corporation
 */

#समावेश <linux/oom.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/swap.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "gt/intel_gt_requests.h"

#समावेश "dma_resv_utils.h"
#समावेश "i915_trace.h"

अटल bool swap_available(व्योम)
अणु
	वापस get_nr_swap_pages() > 0;
पूर्ण

अटल bool can_release_pages(काष्ठा drm_i915_gem_object *obj)
अणु
	/* Consider only shrinkable ojects. */
	अगर (!i915_gem_object_is_shrinkable(obj))
		वापस false;

	/*
	 * We can only वापस physical pages to the प्रणाली अगर we can either
	 * discard the contents (because the user has marked them as being
	 * purgeable) or अगर we can move their contents out to swap.
	 */
	वापस swap_available() || obj->mm.madv == I915_MADV_DONTNEED;
पूर्ण

अटल bool unsafe_drop_pages(काष्ठा drm_i915_gem_object *obj,
			      अचिन्हित दीर्घ shrink)
अणु
	अचिन्हित दीर्घ flags;

	flags = 0;
	अगर (shrink & I915_SHRINK_ACTIVE)
		flags = I915_GEM_OBJECT_UNBIND_ACTIVE;
	अगर (!(shrink & I915_SHRINK_BOUND))
		flags = I915_GEM_OBJECT_UNBIND_TEST;

	अगर (i915_gem_object_unbind(obj, flags) == 0)
		वापस true;

	वापस false;
पूर्ण

अटल व्योम try_to_ग_लिखोback(काष्ठा drm_i915_gem_object *obj,
			     अचिन्हित पूर्णांक flags)
अणु
	चयन (obj->mm.madv) अणु
	हाल I915_MADV_DONTNEED:
		i915_gem_object_truncate(obj);
	हाल __I915_MADV_PURGED:
		वापस;
	पूर्ण

	अगर (flags & I915_SHRINK_WRITEBACK)
		i915_gem_object_ग_लिखोback(obj);
पूर्ण

/**
 * i915_gem_shrink - Shrink buffer object caches
 * @ww: i915 gem ww acquire ctx, or शून्य
 * @i915: i915 device
 * @target: amount of memory to make available, in pages
 * @nr_scanned: optional output क्रम number of pages scanned (incremental)
 * @shrink: control flags क्रम selecting cache types
 *
 * This function is the मुख्य पूर्णांकerface to the shrinker. It will try to release
 * up to @target pages of मुख्य memory backing storage from buffer objects.
 * Selection of the specअगरic caches can be करोne with @flags. This is e.g. useful
 * when purgeable objects should be हटाओd from caches preferentially.
 *
 * Note that it's not guaranteed that released amount is actually available as
 * मुक्त प्रणाली memory - the pages might still be in-used to due to other reasons
 * (like cpu mmaps) or the mm core has reused them beक्रमe we could grab them.
 * Thereक्रमe code that needs to explicitly shrink buffer objects caches (e.g. to
 * aव्योम deadlocks in memory reclaim) must fall back to i915_gem_shrink_all().
 *
 * Also note that any kind of pinning (both per-vma address space pins and
 * backing storage pins at the buffer object level) result in the shrinker code
 * having to skip the object.
 *
 * Returns:
 * The number of pages of backing storage actually released.
 */
अचिन्हित दीर्घ
i915_gem_shrink(काष्ठा i915_gem_ww_ctx *ww,
		काष्ठा drm_i915_निजी *i915,
		अचिन्हित दीर्घ target,
		अचिन्हित दीर्घ *nr_scanned,
		अचिन्हित पूर्णांक shrink)
अणु
	स्थिर काष्ठा अणु
		काष्ठा list_head *list;
		अचिन्हित पूर्णांक bit;
	पूर्ण phases[] = अणु
		अणु &i915->mm.purge_list, ~0u पूर्ण,
		अणु
			&i915->mm.shrink_list,
			I915_SHRINK_BOUND | I915_SHRINK_UNBOUND
		पूर्ण,
		अणु शून्य, 0 पूर्ण,
	पूर्ण, *phase;
	पूर्णांकel_wakeref_t wakeref = 0;
	अचिन्हित दीर्घ count = 0;
	अचिन्हित दीर्घ scanned = 0;
	पूर्णांक err;

	trace_i915_gem_shrink(i915, target, shrink);

	/*
	 * Unbinding of objects will require HW access; Let us not wake the
	 * device just to recover a little memory. If असलolutely necessary,
	 * we will क्रमce the wake during oom-notअगरier.
	 */
	अगर (shrink & I915_SHRINK_BOUND) अणु
		wakeref = पूर्णांकel_runसमय_pm_get_अगर_in_use(&i915->runसमय_pm);
		अगर (!wakeref)
			shrink &= ~I915_SHRINK_BOUND;
	पूर्ण

	/*
	 * When shrinking the active list, we should also consider active
	 * contexts. Active contexts are pinned until they are retired, and
	 * so can not be simply unbound to retire and unpin their pages. To
	 * shrink the contexts, we must रुको until the gpu is idle and
	 * completed its चयन to the kernel context. In लघु, we करो
	 * not have a good mechanism क्रम idling a specअगरic context, but
	 * what we can करो is give them a kick so that we करो not keep idle
	 * contexts around दीर्घer than is necessary.
	 */
	अगर (shrink & I915_SHRINK_ACTIVE)
		/* Retire requests to unpin all idle contexts */
		पूर्णांकel_gt_retire_requests(&i915->gt);

	/*
	 * As we may completely reग_लिखो the (un)bound list whilst unbinding
	 * (due to retiring requests) we have to strictly process only
	 * one element of the list at the समय, and recheck the list
	 * on every iteration.
	 *
	 * In particular, we must hold a reference whilst removing the
	 * object as we may end up रुकोing क्रम and/or retiring the objects.
	 * This might release the final reference (held by the active list)
	 * and result in the object being मुक्तd from under us. This is
	 * similar to the precautions the eviction code must take whilst
	 * removing objects.
	 *
	 * Also note that although these lists करो not hold a reference to
	 * the object we can safely grab one here: The final object
	 * unreferencing and the bound_list are both रक्षित by the
	 * dev->काष्ठा_mutex and so we won't ever be able to observe an
	 * object on the bound_list with a reference count equals 0.
	 */
	क्रम (phase = phases; phase->list; phase++) अणु
		काष्ठा list_head still_in_list;
		काष्ठा drm_i915_gem_object *obj;
		अचिन्हित दीर्घ flags;

		अगर ((shrink & phase->bit) == 0)
			जारी;

		INIT_LIST_HEAD(&still_in_list);

		/*
		 * We serialize our access to unreferenced objects through
		 * the use of the काष्ठा_mutex. While the objects are not
		 * yet मुक्तd (due to RCU then a workqueue) we still want
		 * to be able to shrink their pages, so they reमुख्य on
		 * the unbound/bound list until actually मुक्तd.
		 */
		spin_lock_irqsave(&i915->mm.obj_lock, flags);
		जबतक (count < target &&
		       (obj = list_first_entry_or_null(phase->list,
						       typeof(*obj),
						       mm.link))) अणु
			list_move_tail(&obj->mm.link, &still_in_list);

			अगर (shrink & I915_SHRINK_VMAPS &&
			    !is_vदो_स्मृति_addr(obj->mm.mapping))
				जारी;

			अगर (!(shrink & I915_SHRINK_ACTIVE) &&
			    i915_gem_object_is_framebuffer(obj))
				जारी;

			अगर (!can_release_pages(obj))
				जारी;

			अगर (!kref_get_unless_zero(&obj->base.refcount))
				जारी;

			spin_unlock_irqrestore(&i915->mm.obj_lock, flags);

			err = 0;
			अगर (unsafe_drop_pages(obj, shrink)) अणु
				/* May arrive from get_pages on another bo */
				अगर (!ww) अणु
					अगर (!i915_gem_object_trylock(obj))
						जाओ skip;
				पूर्ण अन्यथा अणु
					err = i915_gem_object_lock(obj, ww);
					अगर (err)
						जाओ skip;
				पूर्ण

				अगर (!__i915_gem_object_put_pages(obj)) अणु
					try_to_ग_लिखोback(obj, shrink);
					count += obj->base.size >> PAGE_SHIFT;
				पूर्ण
				अगर (!ww)
					i915_gem_object_unlock(obj);
			पूर्ण

			dma_resv_prune(obj->base.resv);

			scanned += obj->base.size >> PAGE_SHIFT;
skip:
			i915_gem_object_put(obj);

			spin_lock_irqsave(&i915->mm.obj_lock, flags);
			अगर (err)
				अवरोध;
		पूर्ण
		list_splice_tail(&still_in_list, phase->list);
		spin_unlock_irqrestore(&i915->mm.obj_lock, flags);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (shrink & I915_SHRINK_BOUND)
		पूर्णांकel_runसमय_pm_put(&i915->runसमय_pm, wakeref);

	अगर (nr_scanned)
		*nr_scanned += scanned;
	वापस count;
पूर्ण

/**
 * i915_gem_shrink_all - Shrink buffer object caches completely
 * @i915: i915 device
 *
 * This is a simple wraper around i915_gem_shrink() to aggressively shrink all
 * caches completely. It also first रुकोs क्रम and retires all outstanding
 * requests to also be able to release backing storage क्रम active objects.
 *
 * This should only be used in code to पूर्णांकentionally quiescent the gpu or as a
 * last-ditch efक्रमt when memory seems to have run out.
 *
 * Returns:
 * The number of pages of backing storage actually released.
 */
अचिन्हित दीर्घ i915_gem_shrink_all(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांकel_wakeref_t wakeref;
	अचिन्हित दीर्घ मुक्तd = 0;

	with_पूर्णांकel_runसमय_pm(&i915->runसमय_pm, wakeref) अणु
		मुक्तd = i915_gem_shrink(शून्य, i915, -1UL, शून्य,
					I915_SHRINK_BOUND |
					I915_SHRINK_UNBOUND);
	पूर्ण

	वापस मुक्तd;
पूर्ण

अटल अचिन्हित दीर्घ
i915_gem_shrinker_count(काष्ठा shrinker *shrinker, काष्ठा shrink_control *sc)
अणु
	काष्ठा drm_i915_निजी *i915 =
		container_of(shrinker, काष्ठा drm_i915_निजी, mm.shrinker);
	अचिन्हित दीर्घ num_objects;
	अचिन्हित दीर्घ count;

	count = READ_ONCE(i915->mm.shrink_memory) >> PAGE_SHIFT;
	num_objects = READ_ONCE(i915->mm.shrink_count);

	/*
	 * Update our preferred vmscan batch size क्रम the next pass.
	 * Our rough guess क्रम an effective batch size is roughly 2
	 * available GEM objects worth of pages. That is we करोn't want
	 * the shrinker to fire, until it is worth the cost of मुक्तing an
	 * entire GEM object.
	 */
	अगर (num_objects) अणु
		अचिन्हित दीर्घ avg = 2 * count / num_objects;

		i915->mm.shrinker.batch =
			max((i915->mm.shrinker.batch + avg) >> 1,
			    128ul /* शेष SHRINK_BATCH */);
	पूर्ण

	वापस count;
पूर्ण

अटल अचिन्हित दीर्घ
i915_gem_shrinker_scan(काष्ठा shrinker *shrinker, काष्ठा shrink_control *sc)
अणु
	काष्ठा drm_i915_निजी *i915 =
		container_of(shrinker, काष्ठा drm_i915_निजी, mm.shrinker);
	अचिन्हित दीर्घ मुक्तd;

	sc->nr_scanned = 0;

	मुक्तd = i915_gem_shrink(शून्य, i915,
				sc->nr_to_scan,
				&sc->nr_scanned,
				I915_SHRINK_BOUND |
				I915_SHRINK_UNBOUND);
	अगर (sc->nr_scanned < sc->nr_to_scan && current_is_kswapd()) अणु
		पूर्णांकel_wakeref_t wakeref;

		with_पूर्णांकel_runसमय_pm(&i915->runसमय_pm, wakeref) अणु
			मुक्तd += i915_gem_shrink(शून्य, i915,
						 sc->nr_to_scan - sc->nr_scanned,
						 &sc->nr_scanned,
						 I915_SHRINK_ACTIVE |
						 I915_SHRINK_BOUND |
						 I915_SHRINK_UNBOUND |
						 I915_SHRINK_WRITEBACK);
		पूर्ण
	पूर्ण

	वापस sc->nr_scanned ? मुक्तd : SHRINK_STOP;
पूर्ण

अटल पूर्णांक
i915_gem_shrinker_oom(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा drm_i915_निजी *i915 =
		container_of(nb, काष्ठा drm_i915_निजी, mm.oom_notअगरier);
	काष्ठा drm_i915_gem_object *obj;
	अचिन्हित दीर्घ unevictable, available, मुक्तd_pages;
	पूर्णांकel_wakeref_t wakeref;
	अचिन्हित दीर्घ flags;

	मुक्तd_pages = 0;
	with_पूर्णांकel_runसमय_pm(&i915->runसमय_pm, wakeref)
		मुक्तd_pages += i915_gem_shrink(शून्य, i915, -1UL, शून्य,
					       I915_SHRINK_BOUND |
					       I915_SHRINK_UNBOUND |
					       I915_SHRINK_WRITEBACK);

	/* Because we may be allocating inside our own driver, we cannot
	 * निश्चित that there are no objects with pinned pages that are not
	 * being poपूर्णांकed to by hardware.
	 */
	available = unevictable = 0;
	spin_lock_irqsave(&i915->mm.obj_lock, flags);
	list_क्रम_each_entry(obj, &i915->mm.shrink_list, mm.link) अणु
		अगर (!can_release_pages(obj))
			unevictable += obj->base.size >> PAGE_SHIFT;
		अन्यथा
			available += obj->base.size >> PAGE_SHIFT;
	पूर्ण
	spin_unlock_irqrestore(&i915->mm.obj_lock, flags);

	अगर (मुक्तd_pages || available)
		pr_info("Purging GPU memory, %lu pages freed, "
			"%lu pages still pinned, %lu pages left available.\n",
			मुक्तd_pages, unevictable, available);

	*(अचिन्हित दीर्घ *)ptr += मुक्तd_pages;
	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक
i915_gem_shrinker_vmap(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा drm_i915_निजी *i915 =
		container_of(nb, काष्ठा drm_i915_निजी, mm.vmap_notअगरier);
	काष्ठा i915_vma *vma, *next;
	अचिन्हित दीर्घ मुक्तd_pages = 0;
	पूर्णांकel_wakeref_t wakeref;

	with_पूर्णांकel_runसमय_pm(&i915->runसमय_pm, wakeref)
		मुक्तd_pages += i915_gem_shrink(शून्य, i915, -1UL, शून्य,
					       I915_SHRINK_BOUND |
					       I915_SHRINK_UNBOUND |
					       I915_SHRINK_VMAPS);

	/* We also want to clear any cached iomaps as they wrap vmap */
	mutex_lock(&i915->ggtt.vm.mutex);
	list_क्रम_each_entry_safe(vma, next,
				 &i915->ggtt.vm.bound_list, vm_link) अणु
		अचिन्हित दीर्घ count = vma->node.size >> PAGE_SHIFT;

		अगर (!vma->iomap || i915_vma_is_active(vma))
			जारी;

		अगर (__i915_vma_unbind(vma) == 0)
			मुक्तd_pages += count;
	पूर्ण
	mutex_unlock(&i915->ggtt.vm.mutex);

	*(अचिन्हित दीर्घ *)ptr += मुक्तd_pages;
	वापस NOTIFY_DONE;
पूर्ण

व्योम i915_gem_driver_रेजिस्टर__shrinker(काष्ठा drm_i915_निजी *i915)
अणु
	i915->mm.shrinker.scan_objects = i915_gem_shrinker_scan;
	i915->mm.shrinker.count_objects = i915_gem_shrinker_count;
	i915->mm.shrinker.seeks = DEFAULT_SEEKS;
	i915->mm.shrinker.batch = 4096;
	drm_WARN_ON(&i915->drm, रेजिस्टर_shrinker(&i915->mm.shrinker));

	i915->mm.oom_notअगरier.notअगरier_call = i915_gem_shrinker_oom;
	drm_WARN_ON(&i915->drm, रेजिस्टर_oom_notअगरier(&i915->mm.oom_notअगरier));

	i915->mm.vmap_notअगरier.notअगरier_call = i915_gem_shrinker_vmap;
	drm_WARN_ON(&i915->drm,
		    रेजिस्टर_vmap_purge_notअगरier(&i915->mm.vmap_notअगरier));
पूर्ण

व्योम i915_gem_driver_unरेजिस्टर__shrinker(काष्ठा drm_i915_निजी *i915)
अणु
	drm_WARN_ON(&i915->drm,
		    unरेजिस्टर_vmap_purge_notअगरier(&i915->mm.vmap_notअगरier));
	drm_WARN_ON(&i915->drm,
		    unरेजिस्टर_oom_notअगरier(&i915->mm.oom_notअगरier));
	unरेजिस्टर_shrinker(&i915->mm.shrinker);
पूर्ण

व्योम i915_gem_shrinker_taपूर्णांकs_mutex(काष्ठा drm_i915_निजी *i915,
				    काष्ठा mutex *mutex)
अणु
	अगर (!IS_ENABLED(CONFIG_LOCKDEP))
		वापस;

	fs_reclaim_acquire(GFP_KERNEL);

	mutex_acquire(&mutex->dep_map, 0, 0, _RET_IP_);
	mutex_release(&mutex->dep_map, _RET_IP_);

	fs_reclaim_release(GFP_KERNEL);
पूर्ण

#घोषणा obj_to_i915(obj__) to_i915((obj__)->base.dev)

व्योम i915_gem_object_make_unshrinkable(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा drm_i915_निजी *i915 = obj_to_i915(obj);
	अचिन्हित दीर्घ flags;

	/*
	 * We can only be called जबतक the pages are pinned or when
	 * the pages are released. If pinned, we should only be called
	 * from a single caller under controlled conditions; and on release
	 * only one caller may release us. Neither the two may cross.
	 */
	अगर (atomic_add_unless(&obj->mm.shrink_pin, 1, 0))
		वापस;

	spin_lock_irqsave(&i915->mm.obj_lock, flags);
	अगर (!atomic_fetch_inc(&obj->mm.shrink_pin) &&
	    !list_empty(&obj->mm.link)) अणु
		list_del_init(&obj->mm.link);
		i915->mm.shrink_count--;
		i915->mm.shrink_memory -= obj->base.size;
	पूर्ण
	spin_unlock_irqrestore(&i915->mm.obj_lock, flags);
पूर्ण

अटल व्योम __i915_gem_object_make_shrinkable(काष्ठा drm_i915_gem_object *obj,
					      काष्ठा list_head *head)
अणु
	काष्ठा drm_i915_निजी *i915 = obj_to_i915(obj);
	अचिन्हित दीर्घ flags;

	GEM_BUG_ON(!i915_gem_object_has_pages(obj));
	अगर (!i915_gem_object_is_shrinkable(obj))
		वापस;

	अगर (atomic_add_unless(&obj->mm.shrink_pin, -1, 1))
		वापस;

	spin_lock_irqsave(&i915->mm.obj_lock, flags);
	GEM_BUG_ON(!kref_पढ़ो(&obj->base.refcount));
	अगर (atomic_dec_and_test(&obj->mm.shrink_pin)) अणु
		GEM_BUG_ON(!list_empty(&obj->mm.link));

		list_add_tail(&obj->mm.link, head);
		i915->mm.shrink_count++;
		i915->mm.shrink_memory += obj->base.size;

	पूर्ण
	spin_unlock_irqrestore(&i915->mm.obj_lock, flags);
पूर्ण

व्योम i915_gem_object_make_shrinkable(काष्ठा drm_i915_gem_object *obj)
अणु
	__i915_gem_object_make_shrinkable(obj,
					  &obj_to_i915(obj)->mm.shrink_list);
पूर्ण

व्योम i915_gem_object_make_purgeable(काष्ठा drm_i915_gem_object *obj)
अणु
	__i915_gem_object_make_shrinkable(obj,
					  &obj_to_i915(obj)->mm.purge_list);
पूर्ण
