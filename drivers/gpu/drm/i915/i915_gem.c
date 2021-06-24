<शैली गुरु>
/*
 * Copyright तऊ 2008-2015 Intel Corporation
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
 *
 */

#समावेश <drm/drm_vma_manager.h>
#समावेश <linux/dma-fence-array.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/dma-resv.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/swap.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/mman.h>

#समावेश "display/intel_display.h"
#समावेश "display/intel_frontbuffer.h"

#समावेश "gem/i915_gem_clflush.h"
#समावेश "gem/i915_gem_context.h"
#समावेश "gem/i915_gem_ioctls.h"
#समावेश "gem/i915_gem_mman.h"
#समावेश "gem/i915_gem_region.h"
#समावेश "gt/intel_engine_user.h"
#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_gt_pm.h"
#समावेश "gt/intel_workarounds.h"

#समावेश "i915_drv.h"
#समावेश "i915_trace.h"
#समावेश "i915_vgpu.h"

#समावेश "intel_pm.h"

अटल पूर्णांक
insert_mappable_node(काष्ठा i915_ggtt *ggtt, काष्ठा drm_mm_node *node, u32 size)
अणु
	पूर्णांक err;

	err = mutex_lock_पूर्णांकerruptible(&ggtt->vm.mutex);
	अगर (err)
		वापस err;

	स_रखो(node, 0, माप(*node));
	err = drm_mm_insert_node_in_range(&ggtt->vm.mm, node,
					  size, 0, I915_COLOR_UNEVICTABLE,
					  0, ggtt->mappable_end,
					  DRM_MM_INSERT_LOW);

	mutex_unlock(&ggtt->vm.mutex);

	वापस err;
पूर्ण

अटल व्योम
हटाओ_mappable_node(काष्ठा i915_ggtt *ggtt, काष्ठा drm_mm_node *node)
अणु
	mutex_lock(&ggtt->vm.mutex);
	drm_mm_हटाओ_node(node);
	mutex_unlock(&ggtt->vm.mutex);
पूर्ण

पूर्णांक
i915_gem_get_aperture_ioctl(काष्ठा drm_device *dev, व्योम *data,
			    काष्ठा drm_file *file)
अणु
	काष्ठा i915_ggtt *ggtt = &to_i915(dev)->ggtt;
	काष्ठा drm_i915_gem_get_aperture *args = data;
	काष्ठा i915_vma *vma;
	u64 pinned;

	अगर (mutex_lock_पूर्णांकerruptible(&ggtt->vm.mutex))
		वापस -EINTR;

	pinned = ggtt->vm.reserved;
	list_क्रम_each_entry(vma, &ggtt->vm.bound_list, vm_link)
		अगर (i915_vma_is_pinned(vma))
			pinned += vma->node.size;

	mutex_unlock(&ggtt->vm.mutex);

	args->aper_size = ggtt->vm.total;
	args->aper_available_size = args->aper_size - pinned;

	वापस 0;
पूर्ण

पूर्णांक i915_gem_object_unbind(काष्ठा drm_i915_gem_object *obj,
			   अचिन्हित दीर्घ flags)
अणु
	काष्ठा पूर्णांकel_runसमय_pm *rpm = &to_i915(obj->base.dev)->runसमय_pm;
	LIST_HEAD(still_in_list);
	पूर्णांकel_wakeref_t wakeref;
	काष्ठा i915_vma *vma;
	पूर्णांक ret;

	अगर (list_empty(&obj->vma.list))
		वापस 0;

	/*
	 * As some machines use ACPI to handle runसमय-resume callbacks, and
	 * ACPI is quite kदो_स्मृति happy, we cannot resume beneath the vm->mutex
	 * as they are required by the shrinker. Ergo, we wake the device up
	 * first just in हाल.
	 */
	wakeref = पूर्णांकel_runसमय_pm_get(rpm);

try_again:
	ret = 0;
	spin_lock(&obj->vma.lock);
	जबतक (!ret && (vma = list_first_entry_or_null(&obj->vma.list,
						       काष्ठा i915_vma,
						       obj_link))) अणु
		काष्ठा i915_address_space *vm = vma->vm;

		list_move_tail(&vma->obj_link, &still_in_list);
		अगर (!i915_vma_is_bound(vma, I915_VMA_BIND_MASK))
			जारी;

		अगर (flags & I915_GEM_OBJECT_UNBIND_TEST) अणु
			ret = -EBUSY;
			अवरोध;
		पूर्ण

		ret = -EAGAIN;
		अगर (!i915_vm_tryखोलो(vm))
			अवरोध;

		/* Prevent vma being मुक्तd by i915_vma_parked as we unbind */
		vma = __i915_vma_get(vma);
		spin_unlock(&obj->vma.lock);

		अगर (vma) अणु
			ret = -EBUSY;
			अगर (flags & I915_GEM_OBJECT_UNBIND_ACTIVE ||
			    !i915_vma_is_active(vma))
				ret = i915_vma_unbind(vma);

			__i915_vma_put(vma);
		पूर्ण

		i915_vm_बंद(vm);
		spin_lock(&obj->vma.lock);
	पूर्ण
	list_splice_init(&still_in_list, &obj->vma.list);
	spin_unlock(&obj->vma.lock);

	अगर (ret == -EAGAIN && flags & I915_GEM_OBJECT_UNBIND_BARRIER) अणु
		rcu_barrier(); /* flush the i915_vm_release() */
		जाओ try_again;
	पूर्ण

	पूर्णांकel_runसमय_pm_put(rpm, wakeref);

	वापस ret;
पूर्ण

अटल पूर्णांक
shmem_pपढ़ो(काष्ठा page *page, पूर्णांक offset, पूर्णांक len, अक्षर __user *user_data,
	    bool needs_clflush)
अणु
	अक्षर *vaddr;
	पूर्णांक ret;

	vaddr = kmap(page);

	अगर (needs_clflush)
		drm_clflush_virt_range(vaddr + offset, len);

	ret = __copy_to_user(user_data, vaddr + offset, len);

	kunmap(page);

	वापस ret ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक
i915_gem_shmem_pपढ़ो(काष्ठा drm_i915_gem_object *obj,
		     काष्ठा drm_i915_gem_pपढ़ो *args)
अणु
	अचिन्हित पूर्णांक needs_clflush;
	अचिन्हित पूर्णांक idx, offset;
	अक्षर __user *user_data;
	u64 reमुख्य;
	पूर्णांक ret;

	ret = i915_gem_object_lock_पूर्णांकerruptible(obj, शून्य);
	अगर (ret)
		वापस ret;

	ret = i915_gem_object_pin_pages(obj);
	अगर (ret)
		जाओ err_unlock;

	ret = i915_gem_object_prepare_पढ़ो(obj, &needs_clflush);
	अगर (ret)
		जाओ err_unpin;

	i915_gem_object_finish_access(obj);
	i915_gem_object_unlock(obj);

	reमुख्य = args->size;
	user_data = u64_to_user_ptr(args->data_ptr);
	offset = offset_in_page(args->offset);
	क्रम (idx = args->offset >> PAGE_SHIFT; reमुख्य; idx++) अणु
		काष्ठा page *page = i915_gem_object_get_page(obj, idx);
		अचिन्हित पूर्णांक length = min_t(u64, reमुख्य, PAGE_SIZE - offset);

		ret = shmem_pपढ़ो(page, offset, length, user_data,
				  needs_clflush);
		अगर (ret)
			अवरोध;

		reमुख्य -= length;
		user_data += length;
		offset = 0;
	पूर्ण

	i915_gem_object_unpin_pages(obj);
	वापस ret;

err_unpin:
	i915_gem_object_unpin_pages(obj);
err_unlock:
	i915_gem_object_unlock(obj);
	वापस ret;
पूर्ण

अटल अंतरभूत bool
gtt_user_पढ़ो(काष्ठा io_mapping *mapping,
	      loff_t base, पूर्णांक offset,
	      अक्षर __user *user_data, पूर्णांक length)
अणु
	व्योम __iomem *vaddr;
	अचिन्हित दीर्घ unwritten;

	/* We can use the cpu mem copy function because this is X86. */
	vaddr = io_mapping_map_atomic_wc(mapping, base);
	unwritten = __copy_to_user_inatomic(user_data,
					    (व्योम __क्रमce *)vaddr + offset,
					    length);
	io_mapping_unmap_atomic(vaddr);
	अगर (unwritten) अणु
		vaddr = io_mapping_map_wc(mapping, base, PAGE_SIZE);
		unwritten = copy_to_user(user_data,
					 (व्योम __क्रमce *)vaddr + offset,
					 length);
		io_mapping_unmap(vaddr);
	पूर्ण
	वापस unwritten;
पूर्ण

अटल काष्ठा i915_vma *i915_gem_gtt_prepare(काष्ठा drm_i915_gem_object *obj,
					     काष्ठा drm_mm_node *node,
					     bool ग_लिखो)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	काष्ठा i915_ggtt *ggtt = &i915->ggtt;
	काष्ठा i915_vma *vma;
	काष्ठा i915_gem_ww_ctx ww;
	पूर्णांक ret;

	i915_gem_ww_ctx_init(&ww, true);
retry:
	vma = ERR_PTR(-ENODEV);
	ret = i915_gem_object_lock(obj, &ww);
	अगर (ret)
		जाओ err_ww;

	ret = i915_gem_object_set_to_gtt_करोमुख्य(obj, ग_लिखो);
	अगर (ret)
		जाओ err_ww;

	अगर (!i915_gem_object_is_tiled(obj))
		vma = i915_gem_object_ggtt_pin_ww(obj, &ww, शून्य, 0, 0,
						  PIN_MAPPABLE |
						  PIN_NONBLOCK /* NOWARN */ |
						  PIN_NOEVICT);
	अगर (vma == ERR_PTR(-EDEADLK)) अणु
		ret = -EDEADLK;
		जाओ err_ww;
	पूर्ण अन्यथा अगर (!IS_ERR(vma)) अणु
		node->start = i915_ggtt_offset(vma);
		node->flags = 0;
	पूर्ण अन्यथा अणु
		ret = insert_mappable_node(ggtt, node, PAGE_SIZE);
		अगर (ret)
			जाओ err_ww;
		GEM_BUG_ON(!drm_mm_node_allocated(node));
		vma = शून्य;
	पूर्ण

	ret = i915_gem_object_pin_pages(obj);
	अगर (ret) अणु
		अगर (drm_mm_node_allocated(node)) अणु
			ggtt->vm.clear_range(&ggtt->vm, node->start, node->size);
			हटाओ_mappable_node(ggtt, node);
		पूर्ण अन्यथा अणु
			i915_vma_unpin(vma);
		पूर्ण
	पूर्ण

err_ww:
	अगर (ret == -EDEADLK) अणु
		ret = i915_gem_ww_ctx_backoff(&ww);
		अगर (!ret)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);

	वापस ret ? ERR_PTR(ret) : vma;
पूर्ण

अटल व्योम i915_gem_gtt_cleanup(काष्ठा drm_i915_gem_object *obj,
				 काष्ठा drm_mm_node *node,
				 काष्ठा i915_vma *vma)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	काष्ठा i915_ggtt *ggtt = &i915->ggtt;

	i915_gem_object_unpin_pages(obj);
	अगर (drm_mm_node_allocated(node)) अणु
		ggtt->vm.clear_range(&ggtt->vm, node->start, node->size);
		हटाओ_mappable_node(ggtt, node);
	पूर्ण अन्यथा अणु
		i915_vma_unpin(vma);
	पूर्ण
पूर्ण

अटल पूर्णांक
i915_gem_gtt_pपढ़ो(काष्ठा drm_i915_gem_object *obj,
		   स्थिर काष्ठा drm_i915_gem_pपढ़ो *args)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	काष्ठा i915_ggtt *ggtt = &i915->ggtt;
	पूर्णांकel_wakeref_t wakeref;
	काष्ठा drm_mm_node node;
	व्योम __user *user_data;
	काष्ठा i915_vma *vma;
	u64 reमुख्य, offset;
	पूर्णांक ret = 0;

	wakeref = पूर्णांकel_runसमय_pm_get(&i915->runसमय_pm);

	vma = i915_gem_gtt_prepare(obj, &node, false);
	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		जाओ out_rpm;
	पूर्ण

	user_data = u64_to_user_ptr(args->data_ptr);
	reमुख्य = args->size;
	offset = args->offset;

	जबतक (reमुख्य > 0) अणु
		/* Operation in this page
		 *
		 * page_base = page offset within aperture
		 * page_offset = offset within page
		 * page_length = bytes to copy क्रम this page
		 */
		u32 page_base = node.start;
		अचिन्हित page_offset = offset_in_page(offset);
		अचिन्हित page_length = PAGE_SIZE - page_offset;
		page_length = reमुख्य < page_length ? reमुख्य : page_length;
		अगर (drm_mm_node_allocated(&node)) अणु
			ggtt->vm.insert_page(&ggtt->vm,
					     i915_gem_object_get_dma_address(obj, offset >> PAGE_SHIFT),
					     node.start, I915_CACHE_NONE, 0);
		पूर्ण अन्यथा अणु
			page_base += offset & PAGE_MASK;
		पूर्ण

		अगर (gtt_user_पढ़ो(&ggtt->iomap, page_base, page_offset,
				  user_data, page_length)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		reमुख्य -= page_length;
		user_data += page_length;
		offset += page_length;
	पूर्ण

	i915_gem_gtt_cleanup(obj, &node, vma);
out_rpm:
	पूर्णांकel_runसमय_pm_put(&i915->runसमय_pm, wakeref);
	वापस ret;
पूर्ण

/**
 * Reads data from the object referenced by handle.
 * @dev: drm device poपूर्णांकer
 * @data: ioctl data blob
 * @file: drm file poपूर्णांकer
 *
 * On error, the contents of *data are undefined.
 */
पूर्णांक
i915_gem_pपढ़ो_ioctl(काष्ठा drm_device *dev, व्योम *data,
		     काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dev);
	काष्ठा drm_i915_gem_pपढ़ो *args = data;
	काष्ठा drm_i915_gem_object *obj;
	पूर्णांक ret;

	/* PREAD is disallowed क्रम all platक्रमms after TGL-LP.  This also
	 * covers all platक्रमms with local memory.
	 */
	अगर (INTEL_GEN(i915) >= 12 && !IS_TIGERLAKE(i915))
		वापस -EOPNOTSUPP;

	अगर (args->size == 0)
		वापस 0;

	अगर (!access_ok(u64_to_user_ptr(args->data_ptr),
		       args->size))
		वापस -EFAULT;

	obj = i915_gem_object_lookup(file, args->handle);
	अगर (!obj)
		वापस -ENOENT;

	/* Bounds check source.  */
	अगर (range_overflows_t(u64, args->offset, args->size, obj->base.size)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	trace_i915_gem_object_pपढ़ो(obj, args->offset, args->size);
	ret = -ENODEV;
	अगर (obj->ops->pपढ़ो)
		ret = obj->ops->pपढ़ो(obj, args);
	अगर (ret != -ENODEV)
		जाओ out;

	ret = -ENODEV;
	अगर (obj->ops->pपढ़ो)
		ret = obj->ops->pपढ़ो(obj, args);
	अगर (ret != -ENODEV)
		जाओ out;

	ret = i915_gem_object_रुको(obj,
				   I915_WAIT_INTERRUPTIBLE,
				   MAX_SCHEDULE_TIMEOUT);
	अगर (ret)
		जाओ out;

	ret = i915_gem_shmem_pपढ़ो(obj, args);
	अगर (ret == -EFAULT || ret == -ENODEV)
		ret = i915_gem_gtt_pपढ़ो(obj, args);

out:
	i915_gem_object_put(obj);
	वापस ret;
पूर्ण

/* This is the fast ग_लिखो path which cannot handle
 * page faults in the source data
 */

अटल अंतरभूत bool
ggtt_ग_लिखो(काष्ठा io_mapping *mapping,
	   loff_t base, पूर्णांक offset,
	   अक्षर __user *user_data, पूर्णांक length)
अणु
	व्योम __iomem *vaddr;
	अचिन्हित दीर्घ unwritten;

	/* We can use the cpu mem copy function because this is X86. */
	vaddr = io_mapping_map_atomic_wc(mapping, base);
	unwritten = __copy_from_user_inatomic_nocache((व्योम __क्रमce *)vaddr + offset,
						      user_data, length);
	io_mapping_unmap_atomic(vaddr);
	अगर (unwritten) अणु
		vaddr = io_mapping_map_wc(mapping, base, PAGE_SIZE);
		unwritten = copy_from_user((व्योम __क्रमce *)vaddr + offset,
					   user_data, length);
		io_mapping_unmap(vaddr);
	पूर्ण

	वापस unwritten;
पूर्ण

/**
 * This is the fast pग_लिखो path, where we copy the data directly from the
 * user पूर्णांकo the GTT, uncached.
 * @obj: i915 GEM object
 * @args: pग_लिखो arguments काष्ठाure
 */
अटल पूर्णांक
i915_gem_gtt_pग_लिखो_fast(काष्ठा drm_i915_gem_object *obj,
			 स्थिर काष्ठा drm_i915_gem_pग_लिखो *args)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	काष्ठा i915_ggtt *ggtt = &i915->ggtt;
	काष्ठा पूर्णांकel_runसमय_pm *rpm = &i915->runसमय_pm;
	पूर्णांकel_wakeref_t wakeref;
	काष्ठा drm_mm_node node;
	काष्ठा i915_vma *vma;
	u64 reमुख्य, offset;
	व्योम __user *user_data;
	पूर्णांक ret = 0;

	अगर (i915_gem_object_has_काष्ठा_page(obj)) अणु
		/*
		 * Aव्योम waking the device up अगर we can fallback, as
		 * waking/resuming is very slow (worst-हाल 10-100 ms
		 * depending on PCI sleeps and our own resume समय).
		 * This easily dwarfs any perक्रमmance advantage from
		 * using the cache bypass of indirect GGTT access.
		 */
		wakeref = पूर्णांकel_runसमय_pm_get_अगर_in_use(rpm);
		अगर (!wakeref)
			वापस -EFAULT;
	पूर्ण अन्यथा अणु
		/* No backing pages, no fallback, we must क्रमce GGTT access */
		wakeref = पूर्णांकel_runसमय_pm_get(rpm);
	पूर्ण

	vma = i915_gem_gtt_prepare(obj, &node, true);
	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		जाओ out_rpm;
	पूर्ण

	i915_gem_object_invalidate_frontbuffer(obj, ORIGIN_CPU);

	user_data = u64_to_user_ptr(args->data_ptr);
	offset = args->offset;
	reमुख्य = args->size;
	जबतक (reमुख्य) अणु
		/* Operation in this page
		 *
		 * page_base = page offset within aperture
		 * page_offset = offset within page
		 * page_length = bytes to copy क्रम this page
		 */
		u32 page_base = node.start;
		अचिन्हित पूर्णांक page_offset = offset_in_page(offset);
		अचिन्हित पूर्णांक page_length = PAGE_SIZE - page_offset;
		page_length = reमुख्य < page_length ? reमुख्य : page_length;
		अगर (drm_mm_node_allocated(&node)) अणु
			/* flush the ग_लिखो beक्रमe we modअगरy the GGTT */
			पूर्णांकel_gt_flush_ggtt_ग_लिखोs(ggtt->vm.gt);
			ggtt->vm.insert_page(&ggtt->vm,
					     i915_gem_object_get_dma_address(obj, offset >> PAGE_SHIFT),
					     node.start, I915_CACHE_NONE, 0);
			wmb(); /* flush modअगरications to the GGTT (insert_page) */
		पूर्ण अन्यथा अणु
			page_base += offset & PAGE_MASK;
		पूर्ण
		/* If we get a fault जबतक copying data, then (presumably) our
		 * source page isn't available.  Return the error and we'll
		 * retry in the slow path.
		 * If the object is non-shmem backed, we retry again with the
		 * path that handles page fault.
		 */
		अगर (ggtt_ग_लिखो(&ggtt->iomap, page_base, page_offset,
			       user_data, page_length)) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		reमुख्य -= page_length;
		user_data += page_length;
		offset += page_length;
	पूर्ण

	पूर्णांकel_gt_flush_ggtt_ग_लिखोs(ggtt->vm.gt);
	i915_gem_object_flush_frontbuffer(obj, ORIGIN_CPU);

	i915_gem_gtt_cleanup(obj, &node, vma);
out_rpm:
	पूर्णांकel_runसमय_pm_put(rpm, wakeref);
	वापस ret;
पूर्ण

/* Per-page copy function क्रम the shmem pग_लिखो fastpath.
 * Flushes invalid cachelines beक्रमe writing to the target अगर
 * needs_clflush_beक्रमe is set and flushes out any written cachelines after
 * writing अगर needs_clflush is set.
 */
अटल पूर्णांक
shmem_pग_लिखो(काष्ठा page *page, पूर्णांक offset, पूर्णांक len, अक्षर __user *user_data,
	     bool needs_clflush_beक्रमe,
	     bool needs_clflush_after)
अणु
	अक्षर *vaddr;
	पूर्णांक ret;

	vaddr = kmap(page);

	अगर (needs_clflush_beक्रमe)
		drm_clflush_virt_range(vaddr + offset, len);

	ret = __copy_from_user(vaddr + offset, user_data, len);
	अगर (!ret && needs_clflush_after)
		drm_clflush_virt_range(vaddr + offset, len);

	kunmap(page);

	वापस ret ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक
i915_gem_shmem_pग_लिखो(काष्ठा drm_i915_gem_object *obj,
		      स्थिर काष्ठा drm_i915_gem_pग_लिखो *args)
अणु
	अचिन्हित पूर्णांक partial_cacheline_ग_लिखो;
	अचिन्हित पूर्णांक needs_clflush;
	अचिन्हित पूर्णांक offset, idx;
	व्योम __user *user_data;
	u64 reमुख्य;
	पूर्णांक ret;

	ret = i915_gem_object_lock_पूर्णांकerruptible(obj, शून्य);
	अगर (ret)
		वापस ret;

	ret = i915_gem_object_pin_pages(obj);
	अगर (ret)
		जाओ err_unlock;

	ret = i915_gem_object_prepare_ग_लिखो(obj, &needs_clflush);
	अगर (ret)
		जाओ err_unpin;

	i915_gem_object_finish_access(obj);
	i915_gem_object_unlock(obj);

	/* If we करोn't overग_लिखो a cacheline completely we need to be
	 * careful to have up-to-date data by first clflushing. Don't
	 * overcomplicate things and flush the entire patch.
	 */
	partial_cacheline_ग_लिखो = 0;
	अगर (needs_clflush & CLFLUSH_BEFORE)
		partial_cacheline_ग_लिखो = boot_cpu_data.x86_clflush_size - 1;

	user_data = u64_to_user_ptr(args->data_ptr);
	reमुख्य = args->size;
	offset = offset_in_page(args->offset);
	क्रम (idx = args->offset >> PAGE_SHIFT; reमुख्य; idx++) अणु
		काष्ठा page *page = i915_gem_object_get_page(obj, idx);
		अचिन्हित पूर्णांक length = min_t(u64, reमुख्य, PAGE_SIZE - offset);

		ret = shmem_pग_लिखो(page, offset, length, user_data,
				   (offset | length) & partial_cacheline_ग_लिखो,
				   needs_clflush & CLFLUSH_AFTER);
		अगर (ret)
			अवरोध;

		reमुख्य -= length;
		user_data += length;
		offset = 0;
	पूर्ण

	i915_gem_object_flush_frontbuffer(obj, ORIGIN_CPU);

	i915_gem_object_unpin_pages(obj);
	वापस ret;

err_unpin:
	i915_gem_object_unpin_pages(obj);
err_unlock:
	i915_gem_object_unlock(obj);
	वापस ret;
पूर्ण

/**
 * Writes data to the object referenced by handle.
 * @dev: drm device
 * @data: ioctl data blob
 * @file: drm file
 *
 * On error, the contents of the buffer that were to be modअगरied are undefined.
 */
पूर्णांक
i915_gem_pग_लिखो_ioctl(काष्ठा drm_device *dev, व्योम *data,
		      काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dev);
	काष्ठा drm_i915_gem_pग_लिखो *args = data;
	काष्ठा drm_i915_gem_object *obj;
	पूर्णांक ret;

	/* PWRITE is disallowed क्रम all platक्रमms after TGL-LP.  This also
	 * covers all platक्रमms with local memory.
	 */
	अगर (INTEL_GEN(i915) >= 12 && !IS_TIGERLAKE(i915))
		वापस -EOPNOTSUPP;

	अगर (args->size == 0)
		वापस 0;

	अगर (!access_ok(u64_to_user_ptr(args->data_ptr), args->size))
		वापस -EFAULT;

	obj = i915_gem_object_lookup(file, args->handle);
	अगर (!obj)
		वापस -ENOENT;

	/* Bounds check destination. */
	अगर (range_overflows_t(u64, args->offset, args->size, obj->base.size)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	/* Writes not allowed पूर्णांकo this पढ़ो-only object */
	अगर (i915_gem_object_is_पढ़ोonly(obj)) अणु
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	trace_i915_gem_object_pग_लिखो(obj, args->offset, args->size);

	ret = -ENODEV;
	अगर (obj->ops->pग_लिखो)
		ret = obj->ops->pग_लिखो(obj, args);
	अगर (ret != -ENODEV)
		जाओ err;

	ret = i915_gem_object_रुको(obj,
				   I915_WAIT_INTERRUPTIBLE |
				   I915_WAIT_ALL,
				   MAX_SCHEDULE_TIMEOUT);
	अगर (ret)
		जाओ err;

	ret = -EFAULT;
	/* We can only करो the GTT pग_लिखो on untiled buffers, as otherwise
	 * it would end up going through the fenced access, and we'll get
	 * dअगरferent detiling behavior between पढ़ोing and writing.
	 * pपढ़ो/pग_लिखो currently are पढ़ोing and writing from the CPU
	 * perspective, requiring manual detiling by the client.
	 */
	अगर (!i915_gem_object_has_काष्ठा_page(obj) ||
	    cpu_ग_लिखो_needs_clflush(obj))
		/* Note that the gtt paths might fail with non-page-backed user
		 * poपूर्णांकers (e.g. gtt mappings when moving data between
		 * textures). Fallback to the shmem path in that हाल.
		 */
		ret = i915_gem_gtt_pग_लिखो_fast(obj, args);

	अगर (ret == -EFAULT || ret == -ENOSPC) अणु
		अगर (i915_gem_object_has_काष्ठा_page(obj))
			ret = i915_gem_shmem_pग_लिखो(obj, args);
	पूर्ण

err:
	i915_gem_object_put(obj);
	वापस ret;
पूर्ण

/**
 * Called when user space has करोne ग_लिखोs to this buffer
 * @dev: drm device
 * @data: ioctl data blob
 * @file: drm file
 */
पूर्णांक
i915_gem_sw_finish_ioctl(काष्ठा drm_device *dev, व्योम *data,
			 काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_gem_sw_finish *args = data;
	काष्ठा drm_i915_gem_object *obj;

	obj = i915_gem_object_lookup(file, args->handle);
	अगर (!obj)
		वापस -ENOENT;

	/*
	 * Proxy objects are barred from CPU access, so there is no
	 * need to ban sw_finish as it is a nop.
	 */

	/* Pinned buffers may be scanout, so flush the cache */
	i915_gem_object_flush_अगर_display(obj);
	i915_gem_object_put(obj);

	वापस 0;
पूर्ण

व्योम i915_gem_runसमय_suspend(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा drm_i915_gem_object *obj, *on;
	पूर्णांक i;

	/*
	 * Only called during RPM suspend. All users of the userfault_list
	 * must be holding an RPM wakeref to ensure that this can not
	 * run concurrently with themselves (and use the काष्ठा_mutex क्रम
	 * protection between themselves).
	 */

	list_क्रम_each_entry_safe(obj, on,
				 &i915->ggtt.userfault_list, userfault_link)
		__i915_gem_object_release_mmap_gtt(obj);

	/*
	 * The fence will be lost when the device घातers करोwn. If any were
	 * in use by hardware (i.e. they are pinned), we should not be घातering
	 * करोwn! All other fences will be reacquired by the user upon waking.
	 */
	क्रम (i = 0; i < i915->ggtt.num_fences; i++) अणु
		काष्ठा i915_fence_reg *reg = &i915->ggtt.fence_regs[i];

		/*
		 * Ideally we want to निश्चित that the fence रेजिस्टर is not
		 * live at this poपूर्णांक (i.e. that no piece of code will be
		 * trying to ग_लिखो through fence + GTT, as that both violates
		 * our tracking of activity and associated locking/barriers,
		 * but also is illegal given that the hw is घातered करोwn).
		 *
		 * Previously we used reg->pin_count as a "liveness" indicator.
		 * That is not sufficient, and we need a more fine-grained
		 * tool अगर we want to have a sanity check here.
		 */

		अगर (!reg->vma)
			जारी;

		GEM_BUG_ON(i915_vma_has_userfault(reg->vma));
		reg->dirty = true;
	पूर्ण
पूर्ण

अटल व्योम discard_ggtt_vma(काष्ठा i915_vma *vma)
अणु
	काष्ठा drm_i915_gem_object *obj = vma->obj;

	spin_lock(&obj->vma.lock);
	अगर (!RB_EMPTY_NODE(&vma->obj_node)) अणु
		rb_erase(&vma->obj_node, &obj->vma.tree);
		RB_CLEAR_NODE(&vma->obj_node);
	पूर्ण
	spin_unlock(&obj->vma.lock);
पूर्ण

काष्ठा i915_vma *
i915_gem_object_ggtt_pin_ww(काष्ठा drm_i915_gem_object *obj,
			    काष्ठा i915_gem_ww_ctx *ww,
			    स्थिर काष्ठा i915_ggtt_view *view,
			    u64 size, u64 alignment, u64 flags)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	काष्ठा i915_ggtt *ggtt = &i915->ggtt;
	काष्ठा i915_vma *vma;
	पूर्णांक ret;

	अगर (flags & PIN_MAPPABLE &&
	    (!view || view->type == I915_GGTT_VIEW_NORMAL)) अणु
		/*
		 * If the required space is larger than the available
		 * aperture, we will not able to find a slot क्रम the
		 * object and unbinding the object now will be in
		 * vain. Worse, करोing so may cause us to ping-pong
		 * the object in and out of the Global GTT and
		 * waste a lot of cycles under the mutex.
		 */
		अगर (obj->base.size > ggtt->mappable_end)
			वापस ERR_PTR(-E2BIG);

		/*
		 * If NONBLOCK is set the caller is optimistically
		 * trying to cache the full object within the mappable
		 * aperture, and *must* have a fallback in place क्रम
		 * situations where we cannot bind the object. We
		 * can be a little more lax here and use the fallback
		 * more often to aव्योम costly migrations of ourselves
		 * and other objects within the aperture.
		 *
		 * Half-the-aperture is used as a simple heuristic.
		 * More पूर्णांकeresting would to करो search क्रम a मुक्त
		 * block prior to making the commiपंचांगent to unbind.
		 * That caters क्रम the self-harm हाल, and with a
		 * little more heuristics (e.g. NOFAULT, NOEVICT)
		 * we could try to minimise harm to others.
		 */
		अगर (flags & PIN_NONBLOCK &&
		    obj->base.size > ggtt->mappable_end / 2)
			वापस ERR_PTR(-ENOSPC);
	पूर्ण

new_vma:
	vma = i915_vma_instance(obj, &ggtt->vm, view);
	अगर (IS_ERR(vma))
		वापस vma;

	अगर (i915_vma_misplaced(vma, size, alignment, flags)) अणु
		अगर (flags & PIN_NONBLOCK) अणु
			अगर (i915_vma_is_pinned(vma) || i915_vma_is_active(vma))
				वापस ERR_PTR(-ENOSPC);

			अगर (flags & PIN_MAPPABLE &&
			    vma->fence_size > ggtt->mappable_end / 2)
				वापस ERR_PTR(-ENOSPC);
		पूर्ण

		अगर (i915_vma_is_pinned(vma) || i915_vma_is_active(vma)) अणु
			discard_ggtt_vma(vma);
			जाओ new_vma;
		पूर्ण

		ret = i915_vma_unbind(vma);
		अगर (ret)
			वापस ERR_PTR(ret);
	पूर्ण

	अगर (ww)
		ret = i915_vma_pin_ww(vma, ww, size, alignment, flags | PIN_GLOBAL);
	अन्यथा
		ret = i915_vma_pin(vma, size, alignment, flags | PIN_GLOBAL);

	अगर (ret)
		वापस ERR_PTR(ret);

	अगर (vma->fence && !i915_gem_object_is_tiled(obj)) अणु
		mutex_lock(&ggtt->vm.mutex);
		i915_vma_revoke_fence(vma);
		mutex_unlock(&ggtt->vm.mutex);
	पूर्ण

	ret = i915_vma_रुको_क्रम_bind(vma);
	अगर (ret) अणु
		i915_vma_unpin(vma);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस vma;
पूर्ण

पूर्णांक
i915_gem_madvise_ioctl(काष्ठा drm_device *dev, व्योम *data,
		       काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dev);
	काष्ठा drm_i915_gem_madvise *args = data;
	काष्ठा drm_i915_gem_object *obj;
	पूर्णांक err;

	चयन (args->madv) अणु
	हाल I915_MADV_DONTNEED:
	हाल I915_MADV_WILLNEED:
	    अवरोध;
	शेष:
	    वापस -EINVAL;
	पूर्ण

	obj = i915_gem_object_lookup(file_priv, args->handle);
	अगर (!obj)
		वापस -ENOENT;

	err = i915_gem_object_lock_पूर्णांकerruptible(obj, शून्य);
	अगर (err)
		जाओ out;

	अगर (i915_gem_object_has_pages(obj) &&
	    i915_gem_object_is_tiled(obj) &&
	    i915->quirks & QUIRK_PIN_SWIZZLED_PAGES) अणु
		अगर (obj->mm.madv == I915_MADV_WILLNEED) अणु
			GEM_BUG_ON(!i915_gem_object_has_tiling_quirk(obj));
			i915_gem_object_clear_tiling_quirk(obj);
			i915_gem_object_make_shrinkable(obj);
		पूर्ण
		अगर (args->madv == I915_MADV_WILLNEED) अणु
			GEM_BUG_ON(i915_gem_object_has_tiling_quirk(obj));
			i915_gem_object_make_unshrinkable(obj);
			i915_gem_object_set_tiling_quirk(obj);
		पूर्ण
	पूर्ण

	अगर (obj->mm.madv != __I915_MADV_PURGED)
		obj->mm.madv = args->madv;

	अगर (i915_gem_object_has_pages(obj)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&i915->mm.obj_lock, flags);
		अगर (!list_empty(&obj->mm.link)) अणु
			काष्ठा list_head *list;

			अगर (obj->mm.madv != I915_MADV_WILLNEED)
				list = &i915->mm.purge_list;
			अन्यथा
				list = &i915->mm.shrink_list;
			list_move_tail(&obj->mm.link, list);

		पूर्ण
		spin_unlock_irqrestore(&i915->mm.obj_lock, flags);
	पूर्ण

	/* अगर the object is no दीर्घer attached, discard its backing storage */
	अगर (obj->mm.madv == I915_MADV_DONTNEED &&
	    !i915_gem_object_has_pages(obj))
		i915_gem_object_truncate(obj);

	args->retained = obj->mm.madv != __I915_MADV_PURGED;

	i915_gem_object_unlock(obj);
out:
	i915_gem_object_put(obj);
	वापस err;
पूर्ण

पूर्णांक i915_gem_init(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांक ret;

	/* We need to fallback to 4K pages अगर host करोesn't support huge gtt. */
	अगर (पूर्णांकel_vgpu_active(dev_priv) && !पूर्णांकel_vgpu_has_huge_gtt(dev_priv))
		mkग_लिखो_device_info(dev_priv)->page_sizes =
			I915_GTT_PAGE_SIZE_4K;

	ret = i915_gem_init_userptr(dev_priv);
	अगर (ret)
		वापस ret;

	पूर्णांकel_uc_fetch_firmwares(&dev_priv->gt.uc);
	पूर्णांकel_wopcm_init(&dev_priv->wopcm);

	ret = i915_init_ggtt(dev_priv);
	अगर (ret) अणु
		GEM_BUG_ON(ret == -EIO);
		जाओ err_unlock;
	पूर्ण

	/*
	 * Despite its name पूर्णांकel_init_घड़ी_gating applies both display
	 * घड़ी gating workarounds; GT mmio workarounds and the occasional
	 * GT घातer context workaround. Worse, someबार it includes a context
	 * रेजिस्टर workaround which we need to apply beक्रमe we record the
	 * शेष HW state क्रम all contexts.
	 *
	 * FIXME: अवरोध up the workarounds and apply them at the right समय!
	 */
	पूर्णांकel_init_घड़ी_gating(dev_priv);

	ret = पूर्णांकel_gt_init(&dev_priv->gt);
	अगर (ret)
		जाओ err_unlock;

	वापस 0;

	/*
	 * Unwinding is complicated by that we want to handle -EIO to mean
	 * disable GPU submission but keep KMS alive. We want to mark the
	 * HW as irrevisibly wedged, but keep enough state around that the
	 * driver करोesn't explode during runसमय.
	 */
err_unlock:
	i915_gem_drain_workqueue(dev_priv);

	अगर (ret != -EIO)
		पूर्णांकel_uc_cleanup_firmwares(&dev_priv->gt.uc);

	अगर (ret == -EIO) अणु
		/*
		 * Allow engines or uC initialisation to fail by marking the GPU
		 * as wedged. But we only want to करो this when the GPU is angry,
		 * क्रम all other failure, such as an allocation failure, bail.
		 */
		अगर (!पूर्णांकel_gt_is_wedged(&dev_priv->gt)) अणु
			i915_probe_error(dev_priv,
					 "Failed to initialize GPU, declaring it wedged!\n");
			पूर्णांकel_gt_set_wedged(&dev_priv->gt);
		पूर्ण

		/* Minimal basic recovery क्रम KMS */
		ret = i915_ggtt_enable_hw(dev_priv);
		i915_ggtt_resume(&dev_priv->ggtt);
		पूर्णांकel_init_घड़ी_gating(dev_priv);
	पूर्ण

	i915_gem_drain_मुक्तd_objects(dev_priv);
	वापस ret;
पूर्ण

व्योम i915_gem_driver_रेजिस्टर(काष्ठा drm_i915_निजी *i915)
अणु
	i915_gem_driver_रेजिस्टर__shrinker(i915);

	पूर्णांकel_engines_driver_रेजिस्टर(i915);
पूर्ण

व्योम i915_gem_driver_unरेजिस्टर(काष्ठा drm_i915_निजी *i915)
अणु
	i915_gem_driver_unरेजिस्टर__shrinker(i915);
पूर्ण

व्योम i915_gem_driver_हटाओ(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांकel_wakeref_स्वतः_fini(&dev_priv->ggtt.userfault_wakeref);

	i915_gem_suspend_late(dev_priv);
	पूर्णांकel_gt_driver_हटाओ(&dev_priv->gt);
	dev_priv->uabi_engines = RB_ROOT;

	/* Flush any outstanding unpin_work. */
	i915_gem_drain_workqueue(dev_priv);

	i915_gem_drain_मुक्तd_objects(dev_priv);
पूर्ण

व्योम i915_gem_driver_release(काष्ठा drm_i915_निजी *dev_priv)
अणु
	पूर्णांकel_gt_driver_release(&dev_priv->gt);

	पूर्णांकel_wa_list_मुक्त(&dev_priv->gt_wa_list);

	पूर्णांकel_uc_cleanup_firmwares(&dev_priv->gt.uc);

	i915_gem_drain_मुक्तd_objects(dev_priv);

	drm_WARN_ON(&dev_priv->drm, !list_empty(&dev_priv->gem.contexts.list));
पूर्ण

अटल व्योम i915_gem_init__mm(काष्ठा drm_i915_निजी *i915)
अणु
	spin_lock_init(&i915->mm.obj_lock);

	init_llist_head(&i915->mm.मुक्त_list);

	INIT_LIST_HEAD(&i915->mm.purge_list);
	INIT_LIST_HEAD(&i915->mm.shrink_list);

	i915_gem_init__objects(i915);
पूर्ण

व्योम i915_gem_init_early(काष्ठा drm_i915_निजी *dev_priv)
अणु
	i915_gem_init__mm(dev_priv);
	i915_gem_init__contexts(dev_priv);

	spin_lock_init(&dev_priv->fb_tracking.lock);
पूर्ण

व्योम i915_gem_cleanup_early(काष्ठा drm_i915_निजी *dev_priv)
अणु
	i915_gem_drain_मुक्तd_objects(dev_priv);
	GEM_BUG_ON(!llist_empty(&dev_priv->mm.मुक्त_list));
	GEM_BUG_ON(atomic_पढ़ो(&dev_priv->mm.मुक्त_count));
	drm_WARN_ON(&dev_priv->drm, dev_priv->mm.shrink_count);
पूर्ण

पूर्णांक i915_gem_खोलो(काष्ठा drm_i915_निजी *i915, काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_file_निजी *file_priv;
	पूर्णांक ret;

	DRM_DEBUG("\n");

	file_priv = kzalloc(माप(*file_priv), GFP_KERNEL);
	अगर (!file_priv)
		वापस -ENOMEM;

	file->driver_priv = file_priv;
	file_priv->dev_priv = i915;
	file_priv->file = file;

	file_priv->bsd_engine = -1;
	file_priv->hang_बारtamp = jअगरfies;

	ret = i915_gem_context_खोलो(i915, file);
	अगर (ret)
		kमुक्त(file_priv);

	वापस ret;
पूर्ण

व्योम i915_gem_ww_ctx_init(काष्ठा i915_gem_ww_ctx *ww, bool पूर्णांकr)
अणु
	ww_acquire_init(&ww->ctx, &reservation_ww_class);
	INIT_LIST_HEAD(&ww->obj_list);
	ww->पूर्णांकr = पूर्णांकr;
	ww->contended = शून्य;
पूर्ण

अटल व्योम i915_gem_ww_ctx_unlock_all(काष्ठा i915_gem_ww_ctx *ww)
अणु
	काष्ठा drm_i915_gem_object *obj;

	जबतक ((obj = list_first_entry_or_null(&ww->obj_list, काष्ठा drm_i915_gem_object, obj_link))) अणु
		list_del(&obj->obj_link);
		i915_gem_object_unlock(obj);
	पूर्ण
पूर्ण

व्योम i915_gem_ww_unlock_single(काष्ठा drm_i915_gem_object *obj)
अणु
	list_del(&obj->obj_link);
	i915_gem_object_unlock(obj);
पूर्ण

व्योम i915_gem_ww_ctx_fini(काष्ठा i915_gem_ww_ctx *ww)
अणु
	i915_gem_ww_ctx_unlock_all(ww);
	WARN_ON(ww->contended);
	ww_acquire_fini(&ww->ctx);
पूर्ण

पूर्णांक __must_check i915_gem_ww_ctx_backoff(काष्ठा i915_gem_ww_ctx *ww)
अणु
	पूर्णांक ret = 0;

	अगर (WARN_ON(!ww->contended))
		वापस -EINVAL;

	i915_gem_ww_ctx_unlock_all(ww);
	अगर (ww->पूर्णांकr)
		ret = dma_resv_lock_slow_पूर्णांकerruptible(ww->contended->base.resv, &ww->ctx);
	अन्यथा
		dma_resv_lock_slow(ww->contended->base.resv, &ww->ctx);

	अगर (!ret)
		list_add_tail(&ww->contended->obj_link, &ww->obj_list);

	ww->contended = शून्य;

	वापस ret;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftests/mock_gem_device.c"
#समावेश "selftests/i915_gem.c"
#पूर्ण_अगर
