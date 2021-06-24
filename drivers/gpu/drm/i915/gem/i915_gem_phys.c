<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2014-2016 Intel Corporation
 */

#समावेश <linux/highस्मृति.स>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/swap.h>

#समावेश <drm/drm.h> /* क्रम drm_legacy.h! */
#समावेश <drm/drm_cache.h>

#समावेश "gt/intel_gt.h"
#समावेश "i915_drv.h"
#समावेश "i915_gem_object.h"
#समावेश "i915_gem_region.h"
#समावेश "i915_scatterlist.h"

अटल पूर्णांक i915_gem_object_get_pages_phys(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा address_space *mapping = obj->base.filp->f_mapping;
	काष्ठा scatterlist *sg;
	काष्ठा sg_table *st;
	dma_addr_t dma;
	व्योम *vaddr;
	व्योम *dst;
	पूर्णांक i;

	अगर (GEM_WARN_ON(i915_gem_object_needs_bit17_swizzle(obj)))
		वापस -EINVAL;

	/*
	 * Always aligning to the object size, allows a single allocation
	 * to handle all possible callers, and given typical object sizes,
	 * the alignment of the buddy allocation will naturally match.
	 */
	vaddr = dma_alloc_coherent(obj->base.dev->dev,
				   roundup_घात_of_two(obj->base.size),
				   &dma, GFP_KERNEL);
	अगर (!vaddr)
		वापस -ENOMEM;

	st = kदो_स्मृति(माप(*st), GFP_KERNEL);
	अगर (!st)
		जाओ err_pci;

	अगर (sg_alloc_table(st, 1, GFP_KERNEL))
		जाओ err_st;

	sg = st->sgl;
	sg->offset = 0;
	sg->length = obj->base.size;

	sg_assign_page(sg, (काष्ठा page *)vaddr);
	sg_dma_address(sg) = dma;
	sg_dma_len(sg) = obj->base.size;

	dst = vaddr;
	क्रम (i = 0; i < obj->base.size / PAGE_SIZE; i++) अणु
		काष्ठा page *page;
		व्योम *src;

		page = shmem_पढ़ो_mapping_page(mapping, i);
		अगर (IS_ERR(page))
			जाओ err_st;

		src = kmap_atomic(page);
		स_नकल(dst, src, PAGE_SIZE);
		drm_clflush_virt_range(dst, PAGE_SIZE);
		kunmap_atomic(src);

		put_page(page);
		dst += PAGE_SIZE;
	पूर्ण

	पूर्णांकel_gt_chipset_flush(&to_i915(obj->base.dev)->gt);

	/* We're no दीर्घer काष्ठा page backed */
	obj->flags &= ~I915_BO_ALLOC_STRUCT_PAGE;
	__i915_gem_object_set_pages(obj, st, sg->length);

	वापस 0;

err_st:
	kमुक्त(st);
err_pci:
	dma_मुक्त_coherent(obj->base.dev->dev,
			  roundup_घात_of_two(obj->base.size),
			  vaddr, dma);
	वापस -ENOMEM;
पूर्ण

व्योम
i915_gem_object_put_pages_phys(काष्ठा drm_i915_gem_object *obj,
			       काष्ठा sg_table *pages)
अणु
	dma_addr_t dma = sg_dma_address(pages->sgl);
	व्योम *vaddr = sg_page(pages->sgl);

	__i915_gem_object_release_shmem(obj, pages, false);

	अगर (obj->mm.dirty) अणु
		काष्ठा address_space *mapping = obj->base.filp->f_mapping;
		व्योम *src = vaddr;
		पूर्णांक i;

		क्रम (i = 0; i < obj->base.size / PAGE_SIZE; i++) अणु
			काष्ठा page *page;
			अक्षर *dst;

			page = shmem_पढ़ो_mapping_page(mapping, i);
			अगर (IS_ERR(page))
				जारी;

			dst = kmap_atomic(page);
			drm_clflush_virt_range(src, PAGE_SIZE);
			स_नकल(dst, src, PAGE_SIZE);
			kunmap_atomic(dst);

			set_page_dirty(page);
			अगर (obj->mm.madv == I915_MADV_WILLNEED)
				mark_page_accessed(page);
			put_page(page);

			src += PAGE_SIZE;
		पूर्ण
		obj->mm.dirty = false;
	पूर्ण

	sg_मुक्त_table(pages);
	kमुक्त(pages);

	dma_मुक्त_coherent(obj->base.dev->dev,
			  roundup_घात_of_two(obj->base.size),
			  vaddr, dma);
पूर्ण

पूर्णांक i915_gem_object_pग_लिखो_phys(काष्ठा drm_i915_gem_object *obj,
				स्थिर काष्ठा drm_i915_gem_pग_लिखो *args)
अणु
	व्योम *vaddr = sg_page(obj->mm.pages->sgl) + args->offset;
	अक्षर __user *user_data = u64_to_user_ptr(args->data_ptr);
	पूर्णांक err;

	err = i915_gem_object_रुको(obj,
				   I915_WAIT_INTERRUPTIBLE |
				   I915_WAIT_ALL,
				   MAX_SCHEDULE_TIMEOUT);
	अगर (err)
		वापस err;

	/*
	 * We manually control the करोमुख्य here and pretend that it
	 * reमुख्यs coherent i.e. in the GTT करोमुख्य, like shmem_pग_लिखो.
	 */
	i915_gem_object_invalidate_frontbuffer(obj, ORIGIN_CPU);

	अगर (copy_from_user(vaddr, user_data, args->size))
		वापस -EFAULT;

	drm_clflush_virt_range(vaddr, args->size);
	पूर्णांकel_gt_chipset_flush(&to_i915(obj->base.dev)->gt);

	i915_gem_object_flush_frontbuffer(obj, ORIGIN_CPU);
	वापस 0;
पूर्ण

पूर्णांक i915_gem_object_pपढ़ो_phys(काष्ठा drm_i915_gem_object *obj,
			       स्थिर काष्ठा drm_i915_gem_pपढ़ो *args)
अणु
	व्योम *vaddr = sg_page(obj->mm.pages->sgl) + args->offset;
	अक्षर __user *user_data = u64_to_user_ptr(args->data_ptr);
	पूर्णांक err;

	err = i915_gem_object_रुको(obj,
				   I915_WAIT_INTERRUPTIBLE,
				   MAX_SCHEDULE_TIMEOUT);
	अगर (err)
		वापस err;

	drm_clflush_virt_range(vaddr, args->size);
	अगर (copy_to_user(user_data, vaddr, args->size))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल पूर्णांक i915_gem_object_shmem_to_phys(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा sg_table *pages;
	पूर्णांक err;

	pages = __i915_gem_object_unset_pages(obj);

	err = i915_gem_object_get_pages_phys(obj);
	अगर (err)
		जाओ err_xfer;

	/* Perma-pin (until release) the physical set of pages */
	__i915_gem_object_pin_pages(obj);

	अगर (!IS_ERR_OR_शून्य(pages))
		i915_gem_object_put_pages_shmem(obj, pages);

	i915_gem_object_release_memory_region(obj);
	वापस 0;

err_xfer:
	अगर (!IS_ERR_OR_शून्य(pages)) अणु
		अचिन्हित पूर्णांक sg_page_sizes = i915_sg_page_sizes(pages->sgl);

		__i915_gem_object_set_pages(obj, pages, sg_page_sizes);
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक i915_gem_object_attach_phys(काष्ठा drm_i915_gem_object *obj, पूर्णांक align)
अणु
	पूर्णांक err;

	निश्चित_object_held(obj);

	अगर (align > obj->base.size)
		वापस -EINVAL;

	अगर (!i915_gem_object_is_shmem(obj))
		वापस -EINVAL;

	अगर (!i915_gem_object_has_काष्ठा_page(obj))
		वापस 0;

	err = i915_gem_object_unbind(obj, I915_GEM_OBJECT_UNBIND_ACTIVE);
	अगर (err)
		वापस err;

	अगर (obj->mm.madv != I915_MADV_WILLNEED)
		वापस -EFAULT;

	अगर (i915_gem_object_has_tiling_quirk(obj))
		वापस -EFAULT;

	अगर (obj->mm.mapping || i915_gem_object_has_pinned_pages(obj))
		वापस -EBUSY;

	अगर (unlikely(obj->mm.madv != I915_MADV_WILLNEED)) अणु
		drm_dbg(obj->base.dev,
			"Attempting to obtain a purgeable object\n");
		वापस -EFAULT;
	पूर्ण

	वापस i915_gem_object_shmem_to_phys(obj);
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftests/i915_gem_phys.c"
#पूर्ण_अगर
