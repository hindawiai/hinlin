<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2012-2014 Intel Corporation
 *
  * Based on amdgpu_mn, which bears the following notice:
 *
 * Copyright 2014 Advanced Micro Devices, Inc.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 */
/*
 * Authors:
 *    Christian Kथघnig <christian.koenig@amd.com>
 */

#समावेश <linux/mmu_context.h>
#समावेश <linux/mempolicy.h>
#समावेश <linux/swap.h>
#समावेश <linux/sched/mm.h>

#समावेश "i915_drv.h"
#समावेश "i915_gem_ioctls.h"
#समावेश "i915_gem_object.h"
#समावेश "i915_scatterlist.h"

#अगर_घोषित CONFIG_MMU_NOTIFIER

/**
 * i915_gem_userptr_invalidate - callback to notअगरy about mm change
 *
 * @mni: the range (mm) is about to update
 * @range: details on the invalidation
 * @cur_seq: Value to pass to mmu_पूर्णांकerval_set_seq()
 *
 * Block क्रम operations on BOs to finish and mark pages as accessed and
 * potentially dirty.
 */
अटल bool i915_gem_userptr_invalidate(काष्ठा mmu_पूर्णांकerval_notअगरier *mni,
					स्थिर काष्ठा mmu_notअगरier_range *range,
					अचिन्हित दीर्घ cur_seq)
अणु
	काष्ठा drm_i915_gem_object *obj = container_of(mni, काष्ठा drm_i915_gem_object, userptr.notअगरier);
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	दीर्घ r;

	अगर (!mmu_notअगरier_range_blockable(range))
		वापस false;

	spin_lock(&i915->mm.notअगरier_lock);

	mmu_पूर्णांकerval_set_seq(mni, cur_seq);

	spin_unlock(&i915->mm.notअगरier_lock);

	/*
	 * We करोn't रुको when the process is निकासing. This is valid
	 * because the object will be cleaned up anyway.
	 *
	 * This is also temporarily required as a hack, because we
	 * cannot currently क्रमce non-consistent batch buffers to preempt
	 * and reschedule by रुकोing on it, hanging processes on निकास.
	 */
	अगर (current->flags & PF_EXITING)
		वापस true;

	/* we will unbind on next submission, still have userptr pins */
	r = dma_resv_रुको_समयout_rcu(obj->base.resv, true, false,
				      MAX_SCHEDULE_TIMEOUT);
	अगर (r <= 0)
		drm_err(&i915->drm, "(%ld) failed to wait for idle\n", r);

	वापस true;
पूर्ण

अटल स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops i915_gem_userptr_notअगरier_ops = अणु
	.invalidate = i915_gem_userptr_invalidate,
पूर्ण;

अटल पूर्णांक
i915_gem_userptr_init__mmu_notअगरier(काष्ठा drm_i915_gem_object *obj)
अणु
	वापस mmu_पूर्णांकerval_notअगरier_insert(&obj->userptr.notअगरier, current->mm,
					    obj->userptr.ptr, obj->base.size,
					    &i915_gem_userptr_notअगरier_ops);
पूर्ण

अटल व्योम i915_gem_object_userptr_drop_ref(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	काष्ठा page **pvec = शून्य;

	spin_lock(&i915->mm.notअगरier_lock);
	अगर (!--obj->userptr.page_ref) अणु
		pvec = obj->userptr.pvec;
		obj->userptr.pvec = शून्य;
	पूर्ण
	GEM_BUG_ON(obj->userptr.page_ref < 0);
	spin_unlock(&i915->mm.notअगरier_lock);

	अगर (pvec) अणु
		स्थिर अचिन्हित दीर्घ num_pages = obj->base.size >> PAGE_SHIFT;

		unpin_user_pages(pvec, num_pages);
		kvमुक्त(pvec);
	पूर्ण
पूर्ण

अटल पूर्णांक i915_gem_userptr_get_pages(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	स्थिर अचिन्हित दीर्घ num_pages = obj->base.size >> PAGE_SHIFT;
	अचिन्हित पूर्णांक max_segment = i915_sg_segment_size();
	काष्ठा sg_table *st;
	अचिन्हित पूर्णांक sg_page_sizes;
	काष्ठा scatterlist *sg;
	काष्ठा page **pvec;
	पूर्णांक ret;

	st = kदो_स्मृति(माप(*st), GFP_KERNEL);
	अगर (!st)
		वापस -ENOMEM;

	spin_lock(&i915->mm.notअगरier_lock);
	अगर (GEM_WARN_ON(!obj->userptr.page_ref)) अणु
		spin_unlock(&i915->mm.notअगरier_lock);
		ret = -EFAULT;
		जाओ err_मुक्त;
	पूर्ण

	obj->userptr.page_ref++;
	pvec = obj->userptr.pvec;
	spin_unlock(&i915->mm.notअगरier_lock);

alloc_table:
	sg = __sg_alloc_table_from_pages(st, pvec, num_pages, 0,
					 num_pages << PAGE_SHIFT, max_segment,
					 शून्य, 0, GFP_KERNEL);
	अगर (IS_ERR(sg)) अणु
		ret = PTR_ERR(sg);
		जाओ err;
	पूर्ण

	ret = i915_gem_gtt_prepare_pages(obj, st);
	अगर (ret) अणु
		sg_मुक्त_table(st);

		अगर (max_segment > PAGE_SIZE) अणु
			max_segment = PAGE_SIZE;
			जाओ alloc_table;
		पूर्ण

		जाओ err;
	पूर्ण

	sg_page_sizes = i915_sg_page_sizes(st->sgl);

	__i915_gem_object_set_pages(obj, st, sg_page_sizes);

	वापस 0;

err:
	i915_gem_object_userptr_drop_ref(obj);
err_मुक्त:
	kमुक्त(st);
	वापस ret;
पूर्ण

अटल व्योम
i915_gem_userptr_put_pages(काष्ठा drm_i915_gem_object *obj,
			   काष्ठा sg_table *pages)
अणु
	काष्ठा sgt_iter sgt_iter;
	काष्ठा page *page;

	अगर (!pages)
		वापस;

	__i915_gem_object_release_shmem(obj, pages, true);
	i915_gem_gtt_finish_pages(obj, pages);

	/*
	 * We always mark objects as dirty when they are used by the GPU,
	 * just in हाल. However, अगर we set the vma as being पढ़ो-only we know
	 * that the object will never have been written to.
	 */
	अगर (i915_gem_object_is_पढ़ोonly(obj))
		obj->mm.dirty = false;

	क्रम_each_sgt_page(page, sgt_iter, pages) अणु
		अगर (obj->mm.dirty && trylock_page(page)) अणु
			/*
			 * As this may not be anonymous memory (e.g. shmem)
			 * but exist on a real mapping, we have to lock
			 * the page in order to dirty it -- holding
			 * the page reference is not sufficient to
			 * prevent the inode from being truncated.
			 * Play safe and take the lock.
			 *
			 * However...!
			 *
			 * The mmu-notअगरier can be invalidated क्रम a
			 * migrate_page, that is alपढ़ोying holding the lock
			 * on the page. Such a try_to_unmap() will result
			 * in us calling put_pages() and so recursively try
			 * to lock the page. We aव्योम that deadlock with
			 * a trylock_page() and in exchange we risk missing
			 * some page dirtying.
			 */
			set_page_dirty(page);
			unlock_page(page);
		पूर्ण

		mark_page_accessed(page);
	पूर्ण
	obj->mm.dirty = false;

	sg_मुक्त_table(pages);
	kमुक्त(pages);

	i915_gem_object_userptr_drop_ref(obj);
पूर्ण

अटल पूर्णांक i915_gem_object_userptr_unbind(काष्ठा drm_i915_gem_object *obj, bool get_pages)
अणु
	काष्ठा sg_table *pages;
	पूर्णांक err;

	err = i915_gem_object_unbind(obj, I915_GEM_OBJECT_UNBIND_ACTIVE);
	अगर (err)
		वापस err;

	अगर (GEM_WARN_ON(i915_gem_object_has_pinned_pages(obj)))
		वापस -EBUSY;

	निश्चित_object_held(obj);

	pages = __i915_gem_object_unset_pages(obj);
	अगर (!IS_ERR_OR_शून्य(pages))
		i915_gem_userptr_put_pages(obj, pages);

	अगर (get_pages)
		err = ____i915_gem_object_get_pages(obj);

	वापस err;
पूर्ण

पूर्णांक i915_gem_object_userptr_submit_init(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	स्थिर अचिन्हित दीर्घ num_pages = obj->base.size >> PAGE_SHIFT;
	काष्ठा page **pvec;
	अचिन्हित पूर्णांक gup_flags = 0;
	अचिन्हित दीर्घ notअगरier_seq;
	पूर्णांक pinned, ret;

	अगर (obj->userptr.notअगरier.mm != current->mm)
		वापस -EFAULT;

	ret = i915_gem_object_lock_पूर्णांकerruptible(obj, शून्य);
	अगर (ret)
		वापस ret;

	/* optimistically try to preserve current pages जबतक unlocked */
	अगर (i915_gem_object_has_pages(obj) &&
	    !mmu_पूर्णांकerval_check_retry(&obj->userptr.notअगरier,
				      obj->userptr.notअगरier_seq)) अणु
		spin_lock(&i915->mm.notअगरier_lock);
		अगर (obj->userptr.pvec &&
		    !mmu_पूर्णांकerval_पढ़ो_retry(&obj->userptr.notअगरier,
					     obj->userptr.notअगरier_seq)) अणु
			obj->userptr.page_ref++;

			/* We can keep using the current binding, this is the fastpath */
			ret = 1;
		पूर्ण
		spin_unlock(&i915->mm.notअगरier_lock);
	पूर्ण

	अगर (!ret) अणु
		/* Make sure userptr is unbound क्रम next attempt, so we करोn't use stale pages. */
		ret = i915_gem_object_userptr_unbind(obj, false);
	पूर्ण
	i915_gem_object_unlock(obj);
	अगर (ret < 0)
		वापस ret;

	अगर (ret > 0)
		वापस 0;

	notअगरier_seq = mmu_पूर्णांकerval_पढ़ो_begin(&obj->userptr.notअगरier);

	pvec = kvदो_स्मृति_array(num_pages, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!pvec)
		वापस -ENOMEM;

	अगर (!i915_gem_object_is_पढ़ोonly(obj))
		gup_flags |= FOLL_WRITE;

	pinned = ret = 0;
	जबतक (pinned < num_pages) अणु
		ret = pin_user_pages_fast(obj->userptr.ptr + pinned * PAGE_SIZE,
					  num_pages - pinned, gup_flags,
					  &pvec[pinned]);
		अगर (ret < 0)
			जाओ out;

		pinned += ret;
	पूर्ण
	ret = 0;

	spin_lock(&i915->mm.notअगरier_lock);

	अगर (mmu_पूर्णांकerval_पढ़ो_retry(&obj->userptr.notअगरier,
		!obj->userptr.page_ref ? notअगरier_seq :
		obj->userptr.notअगरier_seq)) अणु
		ret = -EAGAIN;
		जाओ out_unlock;
	पूर्ण

	अगर (!obj->userptr.page_ref++) अणु
		obj->userptr.pvec = pvec;
		obj->userptr.notअगरier_seq = notअगरier_seq;

		pvec = शून्य;
	पूर्ण

out_unlock:
	spin_unlock(&i915->mm.notअगरier_lock);

out:
	अगर (pvec) अणु
		unpin_user_pages(pvec, pinned);
		kvमुक्त(pvec);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक i915_gem_object_userptr_submit_करोne(काष्ठा drm_i915_gem_object *obj)
अणु
	अगर (mmu_पूर्णांकerval_पढ़ो_retry(&obj->userptr.notअगरier,
				    obj->userptr.notअगरier_seq)) अणु
		/* We collided with the mmu notअगरier, need to retry */

		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

व्योम i915_gem_object_userptr_submit_fini(काष्ठा drm_i915_gem_object *obj)
अणु
	i915_gem_object_userptr_drop_ref(obj);
पूर्ण

पूर्णांक i915_gem_object_userptr_validate(काष्ठा drm_i915_gem_object *obj)
अणु
	पूर्णांक err;

	err = i915_gem_object_userptr_submit_init(obj);
	अगर (err)
		वापस err;

	err = i915_gem_object_lock_पूर्णांकerruptible(obj, शून्य);
	अगर (!err) अणु
		/*
		 * Since we only check validity, not use the pages,
		 * it करोesn't matter अगर we collide with the mmu notअगरier,
		 * and -EAGAIN handling is not required.
		 */
		err = i915_gem_object_pin_pages(obj);
		अगर (!err)
			i915_gem_object_unpin_pages(obj);

		i915_gem_object_unlock(obj);
	पूर्ण

	i915_gem_object_userptr_submit_fini(obj);
	वापस err;
पूर्ण

अटल व्योम
i915_gem_userptr_release(काष्ठा drm_i915_gem_object *obj)
अणु
	GEM_WARN_ON(obj->userptr.page_ref);

	mmu_पूर्णांकerval_notअगरier_हटाओ(&obj->userptr.notअगरier);
	obj->userptr.notअगरier.mm = शून्य;
पूर्ण

अटल पूर्णांक
i915_gem_userptr_dmabuf_export(काष्ठा drm_i915_gem_object *obj)
अणु
	drm_dbg(obj->base.dev, "Exporting userptr no longer allowed\n");

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
i915_gem_userptr_pग_लिखो(काष्ठा drm_i915_gem_object *obj,
			स्थिर काष्ठा drm_i915_gem_pग_लिखो *args)
अणु
	drm_dbg(obj->base.dev, "pwrite to userptr no longer allowed\n");

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक
i915_gem_userptr_pपढ़ो(काष्ठा drm_i915_gem_object *obj,
		       स्थिर काष्ठा drm_i915_gem_pपढ़ो *args)
अणु
	drm_dbg(obj->base.dev, "pread from userptr no longer allowed\n");

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा drm_i915_gem_object_ops i915_gem_userptr_ops = अणु
	.name = "i915_gem_object_userptr",
	.flags = I915_GEM_OBJECT_IS_SHRINKABLE |
		 I915_GEM_OBJECT_NO_MMAP |
		 I915_GEM_OBJECT_IS_PROXY,
	.get_pages = i915_gem_userptr_get_pages,
	.put_pages = i915_gem_userptr_put_pages,
	.dmabuf_export = i915_gem_userptr_dmabuf_export,
	.pग_लिखो = i915_gem_userptr_pग_लिखो,
	.pपढ़ो = i915_gem_userptr_pपढ़ो,
	.release = i915_gem_userptr_release,
पूर्ण;

#पूर्ण_अगर

/*
 * Creates a new mm object that wraps some normal memory from the process
 * context - user memory.
 *
 * We impose several restrictions upon the memory being mapped
 * पूर्णांकo the GPU.
 * 1. It must be page aligned (both start/end addresses, i.e ptr and size).
 * 2. It must be normal प्रणाली memory, not a poपूर्णांकer पूर्णांकo another map of IO
 *    space (e.g. it must not be a GTT mmapping of another object).
 * 3. We only allow a bo as large as we could in theory map पूर्णांकo the GTT,
 *    that is we limit the size to the total size of the GTT.
 * 4. The bo is marked as being snoopable. The backing pages are left
 *    accessible directly by the CPU, but पढ़ोs and ग_लिखोs by the GPU may
 *    incur the cost of a snoop (unless you have an LLC architecture).
 *
 * Synchronisation between multiple users and the GPU is left to userspace
 * through the normal set-करोमुख्य-ioctl. The kernel will enक्रमce that the
 * GPU relinquishes the VMA beक्रमe it is वापसed back to the प्रणाली
 * i.e. upon मुक्त(), munmap() or process termination. However, the userspace
 * दो_स्मृति() library may not immediately relinquish the VMA after मुक्त() and
 * instead reuse it whilst the GPU is still पढ़ोing and writing to the VMA.
 * Caveat emptor.
 *
 * Also note, that the object created here is not currently a "first class"
 * object, in that several ioctls are banned. These are the CPU access
 * ioctls: mmap(), pग_लिखो and pपढ़ो. In practice, you are expected to use
 * direct access via your poपूर्णांकer rather than use those ioctls. Another
 * restriction is that we करो not allow userptr surfaces to be pinned to the
 * hardware and so we reject any attempt to create a framebuffer out of a
 * userptr.
 *
 * If you think this is a good पूर्णांकerface to use to pass GPU memory between
 * drivers, please use dma-buf instead. In fact, wherever possible use
 * dma-buf instead.
 */
पूर्णांक
i915_gem_userptr_ioctl(काष्ठा drm_device *dev,
		       व्योम *data,
		       काष्ठा drm_file *file)
अणु
	अटल काष्ठा lock_class_key __maybe_unused lock_class;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा drm_i915_gem_userptr *args = data;
	काष्ठा drm_i915_gem_object __maybe_unused *obj;
	पूर्णांक __maybe_unused ret;
	u32 __maybe_unused handle;

	अगर (!HAS_LLC(dev_priv) && !HAS_SNOOP(dev_priv)) अणु
		/* We cannot support coherent userptr objects on hw without
		 * LLC and broken snooping.
		 */
		वापस -ENODEV;
	पूर्ण

	अगर (args->flags & ~(I915_USERPTR_READ_ONLY |
			    I915_USERPTR_UNSYNCHRONIZED))
		वापस -EINVAL;

	अगर (i915_gem_object_size_2big(args->user_size))
		वापस -E2BIG;

	अगर (!args->user_size)
		वापस -EINVAL;

	अगर (offset_in_page(args->user_ptr | args->user_size))
		वापस -EINVAL;

	अगर (!access_ok((अक्षर __user *)(अचिन्हित दीर्घ)args->user_ptr, args->user_size))
		वापस -EFAULT;

	अगर (args->flags & I915_USERPTR_UNSYNCHRONIZED)
		वापस -ENODEV;

	अगर (args->flags & I915_USERPTR_READ_ONLY) अणु
		/*
		 * On almost all of the older hw, we cannot tell the GPU that
		 * a page is पढ़ोonly.
		 */
		अगर (!dev_priv->gt.vm->has_पढ़ो_only)
			वापस -ENODEV;
	पूर्ण

#अगर_घोषित CONFIG_MMU_NOTIFIER
	obj = i915_gem_object_alloc();
	अगर (obj == शून्य)
		वापस -ENOMEM;

	drm_gem_निजी_object_init(dev, &obj->base, args->user_size);
	i915_gem_object_init(obj, &i915_gem_userptr_ops, &lock_class,
			     I915_BO_ALLOC_STRUCT_PAGE);
	obj->पढ़ो_करोमुख्यs = I915_GEM_DOMAIN_CPU;
	obj->ग_लिखो_करोमुख्य = I915_GEM_DOMAIN_CPU;
	i915_gem_object_set_cache_coherency(obj, I915_CACHE_LLC);

	obj->userptr.ptr = args->user_ptr;
	obj->userptr.notअगरier_seq = अच_दीर्घ_उच्च;
	अगर (args->flags & I915_USERPTR_READ_ONLY)
		i915_gem_object_set_पढ़ोonly(obj);

	/* And keep a poपूर्णांकer to the current->mm क्रम resolving the user pages
	 * at binding. This means that we need to hook पूर्णांकo the mmu_notअगरier
	 * in order to detect अगर the mmu is destroyed.
	 */
	ret = i915_gem_userptr_init__mmu_notअगरier(obj);
	अगर (ret == 0)
		ret = drm_gem_handle_create(file, &obj->base, &handle);

	/* drop reference from allocate - handle holds it now */
	i915_gem_object_put(obj);
	अगर (ret)
		वापस ret;

	args->handle = handle;
	वापस 0;
#अन्यथा
	वापस -ENODEV;
#पूर्ण_अगर
पूर्ण

पूर्णांक i915_gem_init_userptr(काष्ठा drm_i915_निजी *dev_priv)
अणु
#अगर_घोषित CONFIG_MMU_NOTIFIER
	spin_lock_init(&dev_priv->mm.notअगरier_lock);
#पूर्ण_अगर

	वापस 0;
पूर्ण

व्योम i915_gem_cleanup_userptr(काष्ठा drm_i915_निजी *dev_priv)
अणु
पूर्ण
