<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2010 Daniel Vetter
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश <linux/slab.h> /* fault-inject.h is not standalone! */

#समावेश <linux/fault-inject.h>
#समावेश <linux/log2.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/stop_machine.h>

#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/smp.h>

#समावेश "display/intel_frontbuffer.h"
#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_gt_requests.h"

#समावेश "i915_drv.h"
#समावेश "i915_scatterlist.h"
#समावेश "i915_trace.h"
#समावेश "i915_vgpu.h"

पूर्णांक i915_gem_gtt_prepare_pages(काष्ठा drm_i915_gem_object *obj,
			       काष्ठा sg_table *pages)
अणु
	करो अणु
		अगर (dma_map_sg_attrs(obj->base.dev->dev,
				     pages->sgl, pages->nents,
				     PCI_DMA_BIसूचीECTIONAL,
				     DMA_ATTR_SKIP_CPU_SYNC |
				     DMA_ATTR_NO_KERNEL_MAPPING |
				     DMA_ATTR_NO_WARN))
			वापस 0;

		/*
		 * If the DMA remap fails, one cause can be that we have
		 * too many objects pinned in a small remapping table,
		 * such as swiotlb. Incrementally purge all other objects and
		 * try again - अगर there are no more pages to हटाओ from
		 * the DMA remapper, i915_gem_shrink will वापस 0.
		 */
		GEM_BUG_ON(obj->mm.pages == pages);
	पूर्ण जबतक (i915_gem_shrink(शून्य, to_i915(obj->base.dev),
				 obj->base.size >> PAGE_SHIFT, शून्य,
				 I915_SHRINK_BOUND |
				 I915_SHRINK_UNBOUND));

	वापस -ENOSPC;
पूर्ण

व्योम i915_gem_gtt_finish_pages(काष्ठा drm_i915_gem_object *obj,
			       काष्ठा sg_table *pages)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	काष्ठा i915_ggtt *ggtt = &i915->ggtt;

	/* XXX This करोes not prevent more requests being submitted! */
	अगर (unlikely(ggtt->करो_idle_maps))
		/* Wait a bit, in the hope it aव्योमs the hang */
		usleep_range(100, 250);

	dma_unmap_sg(i915->drm.dev, pages->sgl, pages->nents,
		     PCI_DMA_BIसूचीECTIONAL);
पूर्ण

/**
 * i915_gem_gtt_reserve - reserve a node in an address_space (GTT)
 * @vm: the &काष्ठा i915_address_space
 * @node: the &काष्ठा drm_mm_node (typically i915_vma.mode)
 * @size: how much space to allocate inside the GTT,
 *        must be #I915_GTT_PAGE_SIZE aligned
 * @offset: where to insert inside the GTT,
 *          must be #I915_GTT_MIN_ALIGNMENT aligned, and the node
 *          (@offset + @size) must fit within the address space
 * @color: color to apply to node, अगर this node is not from a VMA,
 *         color must be #I915_COLOR_UNEVICTABLE
 * @flags: control search and eviction behaviour
 *
 * i915_gem_gtt_reserve() tries to insert the @node at the exact @offset inside
 * the address space (using @size and @color). If the @node करोes not fit, it
 * tries to evict any overlapping nodes from the GTT, including any
 * neighbouring nodes अगर the colors करो not match (to ensure guard pages between
 * dअगरfering करोमुख्यs). See i915_gem_evict_क्रम_node() क्रम the gory details
 * on the eviction algorithm. #PIN_NONBLOCK may used to prevent रुकोing on
 * evicting active overlapping objects, and any overlapping node that is pinned
 * or marked as unevictable will also result in failure.
 *
 * Returns: 0 on success, -ENOSPC अगर no suitable hole is found, -EINTR अगर
 * asked to रुको क्रम eviction and पूर्णांकerrupted.
 */
पूर्णांक i915_gem_gtt_reserve(काष्ठा i915_address_space *vm,
			 काष्ठा drm_mm_node *node,
			 u64 size, u64 offset, अचिन्हित दीर्घ color,
			 अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक err;

	GEM_BUG_ON(!size);
	GEM_BUG_ON(!IS_ALIGNED(size, I915_GTT_PAGE_SIZE));
	GEM_BUG_ON(!IS_ALIGNED(offset, I915_GTT_MIN_ALIGNMENT));
	GEM_BUG_ON(range_overflows(offset, size, vm->total));
	GEM_BUG_ON(vm == &vm->i915->ggtt.alias->vm);
	GEM_BUG_ON(drm_mm_node_allocated(node));

	node->size = size;
	node->start = offset;
	node->color = color;

	err = drm_mm_reserve_node(&vm->mm, node);
	अगर (err != -ENOSPC)
		वापस err;

	अगर (flags & PIN_NOEVICT)
		वापस -ENOSPC;

	err = i915_gem_evict_क्रम_node(vm, node, flags);
	अगर (err == 0)
		err = drm_mm_reserve_node(&vm->mm, node);

	वापस err;
पूर्ण

अटल u64 अक्रमom_offset(u64 start, u64 end, u64 len, u64 align)
अणु
	u64 range, addr;

	GEM_BUG_ON(range_overflows(start, len, end));
	GEM_BUG_ON(round_up(start, align) > round_करोwn(end - len, align));

	range = round_करोwn(end - len, align) - round_up(start, align);
	अगर (range) अणु
		अगर (माप(अचिन्हित दीर्घ) == माप(u64)) अणु
			addr = get_अक्रमom_दीर्घ();
		पूर्ण अन्यथा अणु
			addr = get_अक्रमom_पूर्णांक();
			अगर (range > U32_MAX) अणु
				addr <<= 32;
				addr |= get_अक्रमom_पूर्णांक();
			पूर्ण
		पूर्ण
		भाग64_u64_rem(addr, range, &addr);
		start += addr;
	पूर्ण

	वापस round_up(start, align);
पूर्ण

/**
 * i915_gem_gtt_insert - insert a node पूर्णांकo an address_space (GTT)
 * @vm: the &काष्ठा i915_address_space
 * @node: the &काष्ठा drm_mm_node (typically i915_vma.node)
 * @size: how much space to allocate inside the GTT,
 *        must be #I915_GTT_PAGE_SIZE aligned
 * @alignment: required alignment of starting offset, may be 0 but
 *             अगर specअगरied, this must be a घातer-of-two and at least
 *             #I915_GTT_MIN_ALIGNMENT
 * @color: color to apply to node
 * @start: start of any range restriction inside GTT (0 क्रम all),
 *         must be #I915_GTT_PAGE_SIZE aligned
 * @end: end of any range restriction inside GTT (U64_MAX क्रम all),
 *       must be #I915_GTT_PAGE_SIZE aligned अगर not U64_MAX
 * @flags: control search and eviction behaviour
 *
 * i915_gem_gtt_insert() first searches क्रम an available hole पूर्णांकo which
 * is can insert the node. The hole address is aligned to @alignment and
 * its @size must then fit entirely within the [@start, @end] bounds. The
 * nodes on either side of the hole must match @color, or अन्यथा a guard page
 * will be inserted between the two nodes (or the node evicted). If no
 * suitable hole is found, first a victim is अक्रमomly selected and tested
 * क्रम eviction, otherwise then the LRU list of objects within the GTT
 * is scanned to find the first set of replacement nodes to create the hole.
 * Those old overlapping nodes are evicted from the GTT (and so must be
 * rebound beक्रमe any future use). Any node that is currently pinned cannot
 * be evicted (see i915_vma_pin()). Similar अगर the node's VMA is currently
 * active and #PIN_NONBLOCK is specअगरied, that node is also skipped when
 * searching क्रम an eviction candidate. See i915_gem_evict_something() क्रम
 * the gory details on the eviction algorithm.
 *
 * Returns: 0 on success, -ENOSPC अगर no suitable hole is found, -EINTR अगर
 * asked to रुको क्रम eviction and पूर्णांकerrupted.
 */
पूर्णांक i915_gem_gtt_insert(काष्ठा i915_address_space *vm,
			काष्ठा drm_mm_node *node,
			u64 size, u64 alignment, अचिन्हित दीर्घ color,
			u64 start, u64 end, अचिन्हित पूर्णांक flags)
अणु
	क्रमागत drm_mm_insert_mode mode;
	u64 offset;
	पूर्णांक err;

	lockdep_निश्चित_held(&vm->mutex);

	GEM_BUG_ON(!size);
	GEM_BUG_ON(!IS_ALIGNED(size, I915_GTT_PAGE_SIZE));
	GEM_BUG_ON(alignment && !is_घातer_of_2(alignment));
	GEM_BUG_ON(alignment && !IS_ALIGNED(alignment, I915_GTT_MIN_ALIGNMENT));
	GEM_BUG_ON(start >= end);
	GEM_BUG_ON(start > 0  && !IS_ALIGNED(start, I915_GTT_PAGE_SIZE));
	GEM_BUG_ON(end < U64_MAX && !IS_ALIGNED(end, I915_GTT_PAGE_SIZE));
	GEM_BUG_ON(vm == &vm->i915->ggtt.alias->vm);
	GEM_BUG_ON(drm_mm_node_allocated(node));

	अगर (unlikely(range_overflows(start, size, end)))
		वापस -ENOSPC;

	अगर (unlikely(round_up(start, alignment) > round_करोwn(end - size, alignment)))
		वापस -ENOSPC;

	mode = DRM_MM_INSERT_BEST;
	अगर (flags & PIN_HIGH)
		mode = DRM_MM_INSERT_HIGHEST;
	अगर (flags & PIN_MAPPABLE)
		mode = DRM_MM_INSERT_LOW;

	/* We only allocate in PAGE_SIZE/GTT_PAGE_SIZE (4096) chunks,
	 * so we know that we always have a minimum alignment of 4096.
	 * The drm_mm range manager is optimised to वापस results
	 * with zero alignment, so where possible use the optimal
	 * path.
	 */
	BUILD_BUG_ON(I915_GTT_MIN_ALIGNMENT > I915_GTT_PAGE_SIZE);
	अगर (alignment <= I915_GTT_MIN_ALIGNMENT)
		alignment = 0;

	err = drm_mm_insert_node_in_range(&vm->mm, node,
					  size, alignment, color,
					  start, end, mode);
	अगर (err != -ENOSPC)
		वापस err;

	अगर (mode & DRM_MM_INSERT_ONCE) अणु
		err = drm_mm_insert_node_in_range(&vm->mm, node,
						  size, alignment, color,
						  start, end,
						  DRM_MM_INSERT_BEST);
		अगर (err != -ENOSPC)
			वापस err;
	पूर्ण

	अगर (flags & PIN_NOEVICT)
		वापस -ENOSPC;

	/*
	 * No मुक्त space, pick a slot at अक्रमom.
	 *
	 * There is a pathological हाल here using a GTT shared between
	 * mmap and GPU (i.e. ggtt/aliasing_ppgtt but not full-ppgtt):
	 *
	 *    |<-- 256 MiB aperture -->||<-- 1792 MiB unmappable -->|
	 *         (64k objects)             (448k objects)
	 *
	 * Now imagine that the eviction LRU is ordered top-करोwn (just because
	 * pathology meets real lअगरe), and that we need to evict an object to
	 * make room inside the aperture. The eviction scan then has to walk
	 * the 448k list beक्रमe it finds one within range. And now imagine that
	 * it has to search क्रम a new hole between every byte inside the स_नकल,
	 * क्रम several simultaneous clients.
	 *
	 * On a full-ppgtt प्रणाली, अगर we have run out of available space, there
	 * will be lots and lots of objects in the eviction list! Again,
	 * searching that LRU list may be slow अगर we are also applying any
	 * range restrictions (e.g. restriction to low 4GiB) and so, क्रम
	 * simplicity and similarilty between dअगरferent GTT, try the single
	 * अक्रमom replacement first.
	 */
	offset = अक्रमom_offset(start, end,
			       size, alignment ?: I915_GTT_MIN_ALIGNMENT);
	err = i915_gem_gtt_reserve(vm, node, size, offset, color, flags);
	अगर (err != -ENOSPC)
		वापस err;

	अगर (flags & PIN_NOSEARCH)
		वापस -ENOSPC;

	/* Ranकरोmly selected placement is pinned, करो a search */
	err = i915_gem_evict_something(vm, size, alignment, color,
				       start, end, flags);
	अगर (err)
		वापस err;

	वापस drm_mm_insert_node_in_range(&vm->mm, node,
					   size, alignment, color,
					   start, end, DRM_MM_INSERT_EVICT);
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftests/i915_gem_gtt.c"
#पूर्ण_अगर
