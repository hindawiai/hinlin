<शैली गुरु>
/*
 * Copyright तऊ 2008-2010 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Eric Anholt <eric@anholt.net>
 *    Chris Wilson <chris@chris-wilson.co.uuk>
 *
 */

#समावेश "gem/i915_gem_context.h"
#समावेश "gt/intel_gt_requests.h"

#समावेश "i915_drv.h"
#समावेश "i915_trace.h"

I915_SELFTEST_DECLARE(अटल काष्ठा igt_evict_ctl अणु
	bool fail_अगर_busy:1;
पूर्ण igt_evict_ctl;)

अटल पूर्णांक ggtt_flush(काष्ठा पूर्णांकel_gt *gt)
अणु
	/*
	 * Not everything in the GGTT is tracked via vma (otherwise we
	 * could evict as required with minimal stalling) so we are क्रमced
	 * to idle the GPU and explicitly retire outstanding requests in
	 * the hopes that we can then हटाओ contexts and the like only
	 * bound by their active reference.
	 */
	वापस पूर्णांकel_gt_रुको_क्रम_idle(gt, MAX_SCHEDULE_TIMEOUT);
पूर्ण

अटल bool
mark_मुक्त(काष्ठा drm_mm_scan *scan,
	  काष्ठा i915_vma *vma,
	  अचिन्हित पूर्णांक flags,
	  काष्ठा list_head *unwind)
अणु
	अगर (i915_vma_is_pinned(vma))
		वापस false;

	list_add(&vma->evict_link, unwind);
	वापस drm_mm_scan_add_block(scan, &vma->node);
पूर्ण

अटल bool defer_evict(काष्ठा i915_vma *vma)
अणु
	अगर (i915_vma_is_active(vma))
		वापस true;

	अगर (i915_vma_is_scanout(vma))
		वापस true;

	वापस false;
पूर्ण

/**
 * i915_gem_evict_something - Evict vmas to make room क्रम binding a new one
 * @vm: address space to evict from
 * @min_size: size of the desired मुक्त space
 * @alignment: alignment स्थिरraपूर्णांक of the desired मुक्त space
 * @color: color क्रम the desired space
 * @start: start (inclusive) of the range from which to evict objects
 * @end: end (exclusive) of the range from which to evict objects
 * @flags: additional flags to control the eviction algorithm
 *
 * This function will try to evict vmas until a मुक्त space satisfying the
 * requirements is found. Callers must check first whether any such hole exists
 * alपढ़ोy beक्रमe calling this function.
 *
 * This function is used by the object/vma binding code.
 *
 * Since this function is only used to मुक्त up भव address space it only
 * ignores pinned vmas, and not object where the backing storage itself is
 * pinned. Hence obj->pages_pin_count करोes not protect against eviction.
 *
 * To clarअगरy: This is क्रम मुक्तing up भव address space, not क्रम मुक्तing
 * memory in e.g. the shrinker.
 */
पूर्णांक
i915_gem_evict_something(काष्ठा i915_address_space *vm,
			 u64 min_size, u64 alignment,
			 अचिन्हित दीर्घ color,
			 u64 start, u64 end,
			 अचिन्हित flags)
अणु
	काष्ठा drm_mm_scan scan;
	काष्ठा list_head eviction_list;
	काष्ठा i915_vma *vma, *next;
	काष्ठा drm_mm_node *node;
	क्रमागत drm_mm_insert_mode mode;
	काष्ठा i915_vma *active;
	पूर्णांक ret;

	lockdep_निश्चित_held(&vm->mutex);
	trace_i915_gem_evict(vm, min_size, alignment, flags);

	/*
	 * The goal is to evict objects and amalgamate space in rough LRU order.
	 * Since both active and inactive objects reside on the same list,
	 * in a mix of creation and last scanned order, as we process the list
	 * we sort it पूर्णांकo inactive/active, which keeps the active portion
	 * in a rough MRU order.
	 *
	 * The retirement sequence is thus:
	 *   1. Inactive objects (alपढ़ोy retired, अक्रमom order)
	 *   2. Active objects (will stall on unbinding, oldest scanned first)
	 */
	mode = DRM_MM_INSERT_BEST;
	अगर (flags & PIN_HIGH)
		mode = DRM_MM_INSERT_HIGH;
	अगर (flags & PIN_MAPPABLE)
		mode = DRM_MM_INSERT_LOW;
	drm_mm_scan_init_with_range(&scan, &vm->mm,
				    min_size, alignment, color,
				    start, end, mode);

	पूर्णांकel_gt_retire_requests(vm->gt);

search_again:
	active = शून्य;
	INIT_LIST_HEAD(&eviction_list);
	list_क्रम_each_entry_safe(vma, next, &vm->bound_list, vm_link) अणु
		अगर (vma == active) अणु /* now seen this vma twice */
			अगर (flags & PIN_NONBLOCK)
				अवरोध;

			active = ERR_PTR(-EAGAIN);
		पूर्ण

		/*
		 * We keep this list in a rough least-recently scanned order
		 * of active elements (inactive elements are cheap to reap).
		 * New entries are added to the end, and we move anything we
		 * scan to the end. The assumption is that the working set
		 * of applications is either steady state (and thanks to the
		 * userspace bo cache it almost always is) or अस्थिर and
		 * frequently replaced after a frame, which are self-evicting!
		 * Given that assumption, the MRU order of the scan list is
		 * fairly अटल, and keeping it in least-recently scan order
		 * is suitable.
		 *
		 * To notice when we complete one full cycle, we record the
		 * first active element seen, beक्रमe moving it to the tail.
		 */
		अगर (active != ERR_PTR(-EAGAIN) && defer_evict(vma)) अणु
			अगर (!active)
				active = vma;

			list_move_tail(&vma->vm_link, &vm->bound_list);
			जारी;
		पूर्ण

		अगर (mark_मुक्त(&scan, vma, flags, &eviction_list))
			जाओ found;
	पूर्ण

	/* Nothing found, clean up and bail out! */
	list_क्रम_each_entry_safe(vma, next, &eviction_list, evict_link) अणु
		ret = drm_mm_scan_हटाओ_block(&scan, &vma->node);
		BUG_ON(ret);
	पूर्ण

	/*
	 * Can we unpin some objects such as idle hw contents,
	 * or pending flips? But since only the GGTT has global entries
	 * such as scanouts, rinbuffers and contexts, we can skip the
	 * purge when inspecting per-process local address spaces.
	 */
	अगर (!i915_is_ggtt(vm) || flags & PIN_NONBLOCK)
		वापस -ENOSPC;

	/*
	 * Not everything in the GGTT is tracked via VMA using
	 * i915_vma_move_to_active(), otherwise we could evict as required
	 * with minimal stalling. Instead we are क्रमced to idle the GPU and
	 * explicitly retire outstanding requests which will then हटाओ
	 * the pinning क्रम active objects such as contexts and ring,
	 * enabling us to evict them on the next iteration.
	 *
	 * To ensure that all user contexts are evictable, we perक्रमm
	 * a चयन to the perma-pinned kernel context. This all also gives
	 * us a termination condition, when the last retired context is
	 * the kernel's there is no more we can evict.
	 */
	अगर (I915_SELFTEST_ONLY(igt_evict_ctl.fail_अगर_busy))
		वापस -EBUSY;

	ret = ggtt_flush(vm->gt);
	अगर (ret)
		वापस ret;

	cond_resched();

	flags |= PIN_NONBLOCK;
	जाओ search_again;

found:
	/* drm_mm करोesn't allow any other other operations जबतक
	 * scanning, thereक्रमe store to-be-evicted objects on a
	 * temporary list and take a reference क्रम all beक्रमe
	 * calling unbind (which may हटाओ the active reference
	 * of any of our objects, thus corrupting the list).
	 */
	list_क्रम_each_entry_safe(vma, next, &eviction_list, evict_link) अणु
		अगर (drm_mm_scan_हटाओ_block(&scan, &vma->node))
			__i915_vma_pin(vma);
		अन्यथा
			list_del(&vma->evict_link);
	पूर्ण

	/* Unbinding will emit any required flushes */
	ret = 0;
	list_क्रम_each_entry_safe(vma, next, &eviction_list, evict_link) अणु
		__i915_vma_unpin(vma);
		अगर (ret == 0)
			ret = __i915_vma_unbind(vma);
	पूर्ण

	जबतक (ret == 0 && (node = drm_mm_scan_color_evict(&scan))) अणु
		vma = container_of(node, काष्ठा i915_vma, node);

		/* If we find any non-objects (!vma), we cannot evict them */
		अगर (vma->node.color != I915_COLOR_UNEVICTABLE)
			ret = __i915_vma_unbind(vma);
		अन्यथा
			ret = -ENOSPC; /* XXX search failed, try again? */
	पूर्ण

	वापस ret;
पूर्ण

/**
 * i915_gem_evict_क्रम_node - Evict vmas to make room क्रम binding a new one
 * @vm: address space to evict from
 * @target: range (and color) to evict क्रम
 * @flags: additional flags to control the eviction algorithm
 *
 * This function will try to evict vmas that overlap the target node.
 *
 * To clarअगरy: This is क्रम मुक्तing up भव address space, not क्रम मुक्तing
 * memory in e.g. the shrinker.
 */
पूर्णांक i915_gem_evict_क्रम_node(काष्ठा i915_address_space *vm,
			    काष्ठा drm_mm_node *target,
			    अचिन्हित पूर्णांक flags)
अणु
	LIST_HEAD(eviction_list);
	काष्ठा drm_mm_node *node;
	u64 start = target->start;
	u64 end = start + target->size;
	काष्ठा i915_vma *vma, *next;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&vm->mutex);
	GEM_BUG_ON(!IS_ALIGNED(start, I915_GTT_PAGE_SIZE));
	GEM_BUG_ON(!IS_ALIGNED(end, I915_GTT_PAGE_SIZE));

	trace_i915_gem_evict_node(vm, target, flags);

	/*
	 * Retire beक्रमe we search the active list. Although we have
	 * reasonable accuracy in our retirement lists, we may have
	 * a stray pin (preventing eviction) that can only be resolved by
	 * retiring.
	 */
	पूर्णांकel_gt_retire_requests(vm->gt);

	अगर (i915_vm_has_cache_coloring(vm)) अणु
		/* Expand search to cover neighbouring guard pages (or lack!) */
		अगर (start)
			start -= I915_GTT_PAGE_SIZE;

		/* Always look at the page afterwards to aव्योम the end-of-GTT */
		end += I915_GTT_PAGE_SIZE;
	पूर्ण
	GEM_BUG_ON(start >= end);

	drm_mm_क्रम_each_node_in_range(node, &vm->mm, start, end) अणु
		/* If we find any non-objects (!vma), we cannot evict them */
		अगर (node->color == I915_COLOR_UNEVICTABLE) अणु
			ret = -ENOSPC;
			अवरोध;
		पूर्ण

		GEM_BUG_ON(!drm_mm_node_allocated(node));
		vma = container_of(node, typeof(*vma), node);

		/*
		 * If we are using coloring to insert guard pages between
		 * dअगरferent cache करोमुख्यs within the address space, we have
		 * to check whether the objects on either side of our range
		 * abutt and conflict. If they are in conflict, then we evict
		 * those as well to make room क्रम our guard pages.
		 */
		अगर (i915_vm_has_cache_coloring(vm)) अणु
			अगर (node->start + node->size == target->start) अणु
				अगर (node->color == target->color)
					जारी;
			पूर्ण
			अगर (node->start == target->start + target->size) अणु
				अगर (node->color == target->color)
					जारी;
			पूर्ण
		पूर्ण

		अगर (i915_vma_is_pinned(vma)) अणु
			ret = -ENOSPC;
			अवरोध;
		पूर्ण

		अगर (flags & PIN_NONBLOCK && i915_vma_is_active(vma)) अणु
			ret = -ENOSPC;
			अवरोध;
		पूर्ण

		/*
		 * Never show fear in the face of dragons!
		 *
		 * We cannot directly हटाओ this node from within this
		 * iterator and as with i915_gem_evict_something() we employ
		 * the vma pin_count in order to prevent the action of
		 * unbinding one vma from मुक्तing (by dropping its active
		 * reference) another in our eviction list.
		 */
		__i915_vma_pin(vma);
		list_add(&vma->evict_link, &eviction_list);
	पूर्ण

	list_क्रम_each_entry_safe(vma, next, &eviction_list, evict_link) अणु
		__i915_vma_unpin(vma);
		अगर (ret == 0)
			ret = __i915_vma_unbind(vma);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * i915_gem_evict_vm - Evict all idle vmas from a vm
 * @vm: Address space to cleanse
 *
 * This function evicts all vmas from a vm.
 *
 * This is used by the execbuf code as a last-ditch efक्रमt to defragment the
 * address space.
 *
 * To clarअगरy: This is क्रम मुक्तing up भव address space, not क्रम मुक्तing
 * memory in e.g. the shrinker.
 */
पूर्णांक i915_gem_evict_vm(काष्ठा i915_address_space *vm)
अणु
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&vm->mutex);
	trace_i915_gem_evict_vm(vm);

	/* Switch back to the शेष context in order to unpin
	 * the existing context objects. However, such objects only
	 * pin themselves inside the global GTT and perक्रमming the
	 * चयन otherwise is ineffective.
	 */
	अगर (i915_is_ggtt(vm)) अणु
		ret = ggtt_flush(vm->gt);
		अगर (ret)
			वापस ret;
	पूर्ण

	करो अणु
		काष्ठा i915_vma *vma, *vn;
		LIST_HEAD(eviction_list);

		list_क्रम_each_entry(vma, &vm->bound_list, vm_link) अणु
			अगर (i915_vma_is_pinned(vma))
				जारी;

			__i915_vma_pin(vma);
			list_add(&vma->evict_link, &eviction_list);
		पूर्ण
		अगर (list_empty(&eviction_list))
			अवरोध;

		ret = 0;
		list_क्रम_each_entry_safe(vma, vn, &eviction_list, evict_link) अणु
			__i915_vma_unpin(vma);
			अगर (ret == 0)
				ret = __i915_vma_unbind(vma);
			अगर (ret != -EINTR) /* "Get me out of here!" */
				ret = 0;
		पूर्ण
	पूर्ण जबतक (ret == 0);

	वापस ret;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftests/i915_gem_evict.c"
#पूर्ण_अगर
