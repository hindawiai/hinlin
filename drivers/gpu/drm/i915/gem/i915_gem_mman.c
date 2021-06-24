<शैली गुरु>
/*
 * SPDX-License-Identअगरier: MIT
 *
 * Copyright तऊ 2014-2016 Intel Corporation
 */

#समावेश <linux/anon_inodes.h>
#समावेश <linux/mman.h>
#समावेश <linux/pfn_t.h>
#समावेश <linux/sizes.h>

#समावेश "gt/intel_gt.h"
#समावेश "gt/intel_gt_requests.h"

#समावेश "i915_drv.h"
#समावेश "i915_gem_gtt.h"
#समावेश "i915_gem_ioctls.h"
#समावेश "i915_gem_object.h"
#समावेश "i915_gem_mman.h"
#समावेश "i915_trace.h"
#समावेश "i915_user_extensions.h"
#समावेश "i915_vma.h"

अटल अंतरभूत bool
__vma_matches(काष्ठा vm_area_काष्ठा *vma, काष्ठा file *filp,
	      अचिन्हित दीर्घ addr, अचिन्हित दीर्घ size)
अणु
	अगर (vma->vm_file != filp)
		वापस false;

	वापस vma->vm_start == addr &&
	       (vma->vm_end - vma->vm_start) == PAGE_ALIGN(size);
पूर्ण

/**
 * i915_gem_mmap_ioctl - Maps the contents of an object, वापसing the address
 *			 it is mapped to.
 * @dev: drm device
 * @data: ioctl data blob
 * @file: drm file
 *
 * While the mapping holds a reference on the contents of the object, it करोesn't
 * imply a ref on the object itself.
 *
 * IMPORTANT:
 *
 * DRM driver ग_लिखोrs who look a this function as an example क्रम how to करो GEM
 * mmap support, please करोn't implement mmap support like here. The modern way
 * to implement DRM mmap support is with an mmap offset ioctl (like
 * i915_gem_mmap_gtt) and then using the mmap syscall on the DRM fd directly.
 * That way debug tooling like valgrind will understand what's going on, hiding
 * the mmap call in a driver निजी ioctl will अवरोध that. The i915 driver only
 * करोes cpu mmaps this way because we didn't know better.
 */
पूर्णांक
i915_gem_mmap_ioctl(काष्ठा drm_device *dev, व्योम *data,
		    काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_gem_mmap *args = data;
	काष्ठा drm_i915_gem_object *obj;
	अचिन्हित दीर्घ addr;

	अगर (args->flags & ~(I915_MMAP_WC))
		वापस -EINVAL;

	अगर (args->flags & I915_MMAP_WC && !boot_cpu_has(X86_FEATURE_PAT))
		वापस -ENODEV;

	obj = i915_gem_object_lookup(file, args->handle);
	अगर (!obj)
		वापस -ENOENT;

	/* prime objects have no backing filp to GEM mmap
	 * pages from.
	 */
	अगर (!obj->base.filp) अणु
		addr = -ENXIO;
		जाओ err;
	पूर्ण

	अगर (range_overflows(args->offset, args->size, (u64)obj->base.size)) अणु
		addr = -EINVAL;
		जाओ err;
	पूर्ण

	addr = vm_mmap(obj->base.filp, 0, args->size,
		       PROT_READ | PROT_WRITE, MAP_SHARED,
		       args->offset);
	अगर (IS_ERR_VALUE(addr))
		जाओ err;

	अगर (args->flags & I915_MMAP_WC) अणु
		काष्ठा mm_काष्ठा *mm = current->mm;
		काष्ठा vm_area_काष्ठा *vma;

		अगर (mmap_ग_लिखो_lock_समाप्तable(mm)) अणु
			addr = -EINTR;
			जाओ err;
		पूर्ण
		vma = find_vma(mm, addr);
		अगर (vma && __vma_matches(vma, obj->base.filp, addr, args->size))
			vma->vm_page_prot =
				pgprot_ग_लिखोcombine(vm_get_page_prot(vma->vm_flags));
		अन्यथा
			addr = -ENOMEM;
		mmap_ग_लिखो_unlock(mm);
		अगर (IS_ERR_VALUE(addr))
			जाओ err;
	पूर्ण
	i915_gem_object_put(obj);

	args->addr_ptr = (u64)addr;
	वापस 0;

err:
	i915_gem_object_put(obj);
	वापस addr;
पूर्ण

अटल अचिन्हित पूर्णांक tile_row_pages(स्थिर काष्ठा drm_i915_gem_object *obj)
अणु
	वापस i915_gem_object_get_tile_row_size(obj) >> PAGE_SHIFT;
पूर्ण

/**
 * i915_gem_mmap_gtt_version - report the current feature set क्रम GTT mmaps
 *
 * A history of the GTT mmap पूर्णांकerface:
 *
 * 0 - Everything had to fit पूर्णांकo the GTT. Both parties of a स_नकल had to
 *     aligned and suitable क्रम fencing, and still fit पूर्णांकo the available
 *     mappable space left by the pinned display objects. A classic problem
 *     we called the page-fault-of-करोom where we would ping-pong between
 *     two objects that could not fit inside the GTT and so the स_नकल
 *     would page one object in at the expense of the other between every
 *     single byte.
 *
 * 1 - Objects can be any size, and have any compatible fencing (X Y, or none
 *     as set via i915_gem_set_tiling() [DRM_I915_GEM_SET_TILING]). If the
 *     object is too large क्रम the available space (or simply too large
 *     क्रम the mappable aperture!), a view is created instead and faulted
 *     पूर्णांकo userspace. (This view is aligned and sized appropriately क्रम
 *     fenced access.)
 *
 * 2 - Recognise WC as a separate cache करोमुख्य so that we can flush the
 *     delayed ग_लिखोs via GTT beक्रमe perक्रमming direct access via WC.
 *
 * 3 - Remove implicit set-करोमुख्य(GTT) and synchronisation on initial
 *     pagefault; swapin reमुख्यs transparent.
 *
 * 4 - Support multiple fault handlers per object depending on object's
 *     backing storage (a.k.a. MMAP_OFFSET).
 *
 * Restrictions:
 *
 *  * snoopable objects cannot be accessed via the GTT. It can cause machine
 *    hangs on some architectures, corruption on others. An attempt to service
 *    a GTT page fault from a snoopable object will generate a SIGBUS.
 *
 *  * the object must be able to fit पूर्णांकo RAM (physical memory, though no
 *    limited to the mappable aperture).
 *
 *
 * Caveats:
 *
 *  * a new GTT page fault will synchronize rendering from the GPU and flush
 *    all data to प्रणाली memory. Subsequent access will not be synchronized.
 *
 *  * all mappings are revoked on runसमय device suspend.
 *
 *  * there are only 8, 16 or 32 fence रेजिस्टरs to share between all users
 *    (older machines require fence रेजिस्टर क्रम display and blitter access
 *    as well). Contention of the fence रेजिस्टरs will cause the previous users
 *    to be unmapped and any new access will generate new page faults.
 *
 *  * running out of memory जबतक servicing a fault may generate a SIGBUS,
 *    rather than the expected संक_अंश.
 */
पूर्णांक i915_gem_mmap_gtt_version(व्योम)
अणु
	वापस 4;
पूर्ण

अटल अंतरभूत काष्ठा i915_ggtt_view
compute_partial_view(स्थिर काष्ठा drm_i915_gem_object *obj,
		     pgoff_t page_offset,
		     अचिन्हित पूर्णांक chunk)
अणु
	काष्ठा i915_ggtt_view view;

	अगर (i915_gem_object_is_tiled(obj))
		chunk = roundup(chunk, tile_row_pages(obj) ?: 1);

	view.type = I915_GGTT_VIEW_PARTIAL;
	view.partial.offset = roundकरोwn(page_offset, chunk);
	view.partial.size =
		min_t(अचिन्हित पूर्णांक, chunk,
		      (obj->base.size >> PAGE_SHIFT) - view.partial.offset);

	/* If the partial covers the entire object, just create a normal VMA. */
	अगर (chunk >= obj->base.size >> PAGE_SHIFT)
		view.type = I915_GGTT_VIEW_NORMAL;

	वापस view;
पूर्ण

अटल vm_fault_t i915_error_to_vmf_fault(पूर्णांक err)
अणु
	चयन (err) अणु
	शेष:
		WARN_ONCE(err, "unhandled error in %s: %i\n", __func__, err);
		fallthrough;
	हाल -EIO: /* shmemfs failure from swap device */
	हाल -EFAULT: /* purged object */
	हाल -ENODEV: /* bad object, how did you get here! */
	हाल -ENXIO: /* unable to access backing store (on device) */
		वापस VM_FAULT_SIGBUS;

	हाल -ENOMEM: /* our allocation failure */
		वापस VM_FAULT_OOM;

	हाल 0:
	हाल -EAGAIN:
	हाल -ENOSPC: /* transient failure to evict? */
	हाल -ERESTARTSYS:
	हाल -EINTR:
	हाल -EBUSY:
		/*
		 * EBUSY is ok: this just means that another thपढ़ो
		 * alपढ़ोy did the job.
		 */
		वापस VM_FAULT_NOPAGE;
	पूर्ण
पूर्ण

अटल vm_fault_t vm_fault_cpu(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *area = vmf->vma;
	काष्ठा i915_mmap_offset *mmo = area->vm_निजी_data;
	काष्ठा drm_i915_gem_object *obj = mmo->obj;
	resource_माप_प्रकार iomap;
	पूर्णांक err;

	/* Sanity check that we allow writing पूर्णांकo this object */
	अगर (unlikely(i915_gem_object_is_पढ़ोonly(obj) &&
		     area->vm_flags & VM_WRITE))
		वापस VM_FAULT_SIGBUS;

	अगर (i915_gem_object_lock_पूर्णांकerruptible(obj, शून्य))
		वापस VM_FAULT_NOPAGE;

	err = i915_gem_object_pin_pages(obj);
	अगर (err)
		जाओ out;

	iomap = -1;
	अगर (!i915_gem_object_has_काष्ठा_page(obj)) अणु
		iomap = obj->mm.region->iomap.base;
		iomap -= obj->mm.region->region.start;
	पूर्ण

	/* PTEs are revoked in obj->ops->put_pages() */
	err = remap_io_sg(area,
			  area->vm_start, area->vm_end - area->vm_start,
			  obj->mm.pages->sgl, iomap);

	अगर (area->vm_flags & VM_WRITE) अणु
		GEM_BUG_ON(!i915_gem_object_has_pinned_pages(obj));
		obj->mm.dirty = true;
	पूर्ण

	i915_gem_object_unpin_pages(obj);

out:
	i915_gem_object_unlock(obj);
	वापस i915_error_to_vmf_fault(err);
पूर्ण

अटल vm_fault_t vm_fault_gtt(काष्ठा vm_fault *vmf)
अणु
#घोषणा MIN_CHUNK_PAGES (SZ_1M >> PAGE_SHIFT)
	काष्ठा vm_area_काष्ठा *area = vmf->vma;
	काष्ठा i915_mmap_offset *mmo = area->vm_निजी_data;
	काष्ठा drm_i915_gem_object *obj = mmo->obj;
	काष्ठा drm_device *dev = obj->base.dev;
	काष्ठा drm_i915_निजी *i915 = to_i915(dev);
	काष्ठा पूर्णांकel_runसमय_pm *rpm = &i915->runसमय_pm;
	काष्ठा i915_ggtt *ggtt = &i915->ggtt;
	bool ग_लिखो = area->vm_flags & VM_WRITE;
	काष्ठा i915_gem_ww_ctx ww;
	पूर्णांकel_wakeref_t wakeref;
	काष्ठा i915_vma *vma;
	pgoff_t page_offset;
	पूर्णांक srcu;
	पूर्णांक ret;

	/* We करोn't use vmf->pgoff since that has the fake offset */
	page_offset = (vmf->address - area->vm_start) >> PAGE_SHIFT;

	trace_i915_gem_object_fault(obj, page_offset, true, ग_लिखो);

	wakeref = पूर्णांकel_runसमय_pm_get(rpm);

	i915_gem_ww_ctx_init(&ww, true);
retry:
	ret = i915_gem_object_lock(obj, &ww);
	अगर (ret)
		जाओ err_rpm;

	/* Sanity check that we allow writing पूर्णांकo this object */
	अगर (i915_gem_object_is_पढ़ोonly(obj) && ग_लिखो) अणु
		ret = -EFAULT;
		जाओ err_rpm;
	पूर्ण

	ret = i915_gem_object_pin_pages(obj);
	अगर (ret)
		जाओ err_rpm;

	ret = पूर्णांकel_gt_reset_trylock(ggtt->vm.gt, &srcu);
	अगर (ret)
		जाओ err_pages;

	/* Now pin it पूर्णांकo the GTT as needed */
	vma = i915_gem_object_ggtt_pin_ww(obj, &ww, शून्य, 0, 0,
					  PIN_MAPPABLE |
					  PIN_NONBLOCK /* NOWARN */ |
					  PIN_NOEVICT);
	अगर (IS_ERR(vma) && vma != ERR_PTR(-EDEADLK)) अणु
		/* Use a partial view अगर it is bigger than available space */
		काष्ठा i915_ggtt_view view =
			compute_partial_view(obj, page_offset, MIN_CHUNK_PAGES);
		अचिन्हित पूर्णांक flags;

		flags = PIN_MAPPABLE | PIN_NOSEARCH;
		अगर (view.type == I915_GGTT_VIEW_NORMAL)
			flags |= PIN_NONBLOCK; /* aव्योम warnings क्रम pinned */

		/*
		 * Userspace is now writing through an untracked VMA, abanकरोn
		 * all hope that the hardware is able to track future ग_लिखोs.
		 */

		vma = i915_gem_object_ggtt_pin_ww(obj, &ww, &view, 0, 0, flags);
		अगर (IS_ERR(vma) && vma != ERR_PTR(-EDEADLK)) अणु
			flags = PIN_MAPPABLE;
			view.type = I915_GGTT_VIEW_PARTIAL;
			vma = i915_gem_object_ggtt_pin_ww(obj, &ww, &view, 0, 0, flags);
		पूर्ण

		/* The entire mappable GGTT is pinned? Unexpected! */
		GEM_BUG_ON(vma == ERR_PTR(-ENOSPC));
	पूर्ण
	अगर (IS_ERR(vma)) अणु
		ret = PTR_ERR(vma);
		जाओ err_reset;
	पूर्ण

	/* Access to snoopable pages through the GTT is incoherent. */
	अगर (obj->cache_level != I915_CACHE_NONE && !HAS_LLC(i915)) अणु
		ret = -EFAULT;
		जाओ err_unpin;
	पूर्ण

	ret = i915_vma_pin_fence(vma);
	अगर (ret)
		जाओ err_unpin;

	/* Finally, remap it using the new GTT offset */
	ret = remap_io_mapping(area,
			       area->vm_start + (vma->ggtt_view.partial.offset << PAGE_SHIFT),
			       (ggtt->gmadr.start + vma->node.start) >> PAGE_SHIFT,
			       min_t(u64, vma->size, area->vm_end - area->vm_start),
			       &ggtt->iomap);
	अगर (ret)
		जाओ err_fence;

	निश्चित_rpm_wakelock_held(rpm);

	/* Mark as being mmapped पूर्णांकo userspace क्रम later revocation */
	mutex_lock(&i915->ggtt.vm.mutex);
	अगर (!i915_vma_set_userfault(vma) && !obj->userfault_count++)
		list_add(&obj->userfault_link, &i915->ggtt.userfault_list);
	mutex_unlock(&i915->ggtt.vm.mutex);

	/* Track the mmo associated with the fenced vma */
	vma->mmo = mmo;

	अगर (IS_ACTIVE(CONFIG_DRM_I915_USERFAULT_AUTOSUSPEND))
		पूर्णांकel_wakeref_स्वतः(&i915->ggtt.userfault_wakeref,
				   msecs_to_jअगरfies_समयout(CONFIG_DRM_I915_USERFAULT_AUTOSUSPEND));

	अगर (ग_लिखो) अणु
		GEM_BUG_ON(!i915_gem_object_has_pinned_pages(obj));
		i915_vma_set_ggtt_ग_लिखो(vma);
		obj->mm.dirty = true;
	पूर्ण

err_fence:
	i915_vma_unpin_fence(vma);
err_unpin:
	__i915_vma_unpin(vma);
err_reset:
	पूर्णांकel_gt_reset_unlock(ggtt->vm.gt, srcu);
err_pages:
	i915_gem_object_unpin_pages(obj);
err_rpm:
	अगर (ret == -EDEADLK) अणु
		ret = i915_gem_ww_ctx_backoff(&ww);
		अगर (!ret)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);
	पूर्णांकel_runसमय_pm_put(rpm, wakeref);
	वापस i915_error_to_vmf_fault(ret);
पूर्ण

अटल पूर्णांक
vm_access(काष्ठा vm_area_काष्ठा *area, अचिन्हित दीर्घ addr,
	  व्योम *buf, पूर्णांक len, पूर्णांक ग_लिखो)
अणु
	काष्ठा i915_mmap_offset *mmo = area->vm_निजी_data;
	काष्ठा drm_i915_gem_object *obj = mmo->obj;
	काष्ठा i915_gem_ww_ctx ww;
	व्योम *vaddr;
	पूर्णांक err = 0;

	अगर (i915_gem_object_is_पढ़ोonly(obj) && ग_लिखो)
		वापस -EACCES;

	addr -= area->vm_start;
	अगर (addr >= obj->base.size)
		वापस -EINVAL;

	i915_gem_ww_ctx_init(&ww, true);
retry:
	err = i915_gem_object_lock(obj, &ww);
	अगर (err)
		जाओ out;

	/* As this is primarily क्रम debugging, let's focus on simplicity */
	vaddr = i915_gem_object_pin_map(obj, I915_MAP_FORCE_WC);
	अगर (IS_ERR(vaddr)) अणु
		err = PTR_ERR(vaddr);
		जाओ out;
	पूर्ण

	अगर (ग_लिखो) अणु
		स_नकल(vaddr + addr, buf, len);
		__i915_gem_object_flush_map(obj, addr, len);
	पूर्ण अन्यथा अणु
		स_नकल(buf, vaddr + addr, len);
	पूर्ण

	i915_gem_object_unpin_map(obj);
out:
	अगर (err == -EDEADLK) अणु
		err = i915_gem_ww_ctx_backoff(&ww);
		अगर (!err)
			जाओ retry;
	पूर्ण
	i915_gem_ww_ctx_fini(&ww);

	अगर (err)
		वापस err;

	वापस len;
पूर्ण

व्योम __i915_gem_object_release_mmap_gtt(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा i915_vma *vma;

	GEM_BUG_ON(!obj->userfault_count);

	क्रम_each_ggtt_vma(vma, obj)
		i915_vma_revoke_mmap(vma);

	GEM_BUG_ON(obj->userfault_count);
पूर्ण

/*
 * It is vital that we हटाओ the page mapping अगर we have mapped a tiled
 * object through the GTT and then lose the fence रेजिस्टर due to
 * resource pressure. Similarly अगर the object has been moved out of the
 * aperture, than pages mapped पूर्णांकo userspace must be revoked. Removing the
 * mapping will then trigger a page fault on the next user access, allowing
 * fixup by vm_fault_gtt().
 */
व्योम i915_gem_object_release_mmap_gtt(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	पूर्णांकel_wakeref_t wakeref;

	/*
	 * Serialisation between user GTT access and our code depends upon
	 * revoking the CPU's PTE whilst the mutex is held. The next user
	 * pagefault then has to रुको until we release the mutex.
	 *
	 * Note that RPM complicates somewhat by adding an additional
	 * requirement that operations to the GGTT be made holding the RPM
	 * wakeref.
	 */
	wakeref = पूर्णांकel_runसमय_pm_get(&i915->runसमय_pm);
	mutex_lock(&i915->ggtt.vm.mutex);

	अगर (!obj->userfault_count)
		जाओ out;

	__i915_gem_object_release_mmap_gtt(obj);

	/*
	 * Ensure that the CPU's PTE are revoked and there are not outstanding
	 * memory transactions from userspace beक्रमe we वापस. The TLB
	 * flushing implied above by changing the PTE above *should* be
	 * sufficient, an extra barrier here just provides us with a bit
	 * of paranoid करोcumentation about our requirement to serialise
	 * memory ग_लिखोs beक्रमe touching रेजिस्टरs / GSM.
	 */
	wmb();

out:
	mutex_unlock(&i915->ggtt.vm.mutex);
	पूर्णांकel_runसमय_pm_put(&i915->runसमय_pm, wakeref);
पूर्ण

व्योम i915_gem_object_release_mmap_offset(काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा i915_mmap_offset *mmo, *mn;

	spin_lock(&obj->mmo.lock);
	rbtree_postorder_क्रम_each_entry_safe(mmo, mn,
					     &obj->mmo.offsets, offset) अणु
		/*
		 * vma_node_unmap क्रम GTT mmaps handled alपढ़ोy in
		 * __i915_gem_object_release_mmap_gtt
		 */
		अगर (mmo->mmap_type == I915_MMAP_TYPE_GTT)
			जारी;

		spin_unlock(&obj->mmo.lock);
		drm_vma_node_unmap(&mmo->vma_node,
				   obj->base.dev->anon_inode->i_mapping);
		spin_lock(&obj->mmo.lock);
	पूर्ण
	spin_unlock(&obj->mmo.lock);
पूर्ण

अटल काष्ठा i915_mmap_offset *
lookup_mmo(काष्ठा drm_i915_gem_object *obj,
	   क्रमागत i915_mmap_type mmap_type)
अणु
	काष्ठा rb_node *rb;

	spin_lock(&obj->mmo.lock);
	rb = obj->mmo.offsets.rb_node;
	जबतक (rb) अणु
		काष्ठा i915_mmap_offset *mmo =
			rb_entry(rb, typeof(*mmo), offset);

		अगर (mmo->mmap_type == mmap_type) अणु
			spin_unlock(&obj->mmo.lock);
			वापस mmo;
		पूर्ण

		अगर (mmo->mmap_type < mmap_type)
			rb = rb->rb_right;
		अन्यथा
			rb = rb->rb_left;
	पूर्ण
	spin_unlock(&obj->mmo.lock);

	वापस शून्य;
पूर्ण

अटल काष्ठा i915_mmap_offset *
insert_mmo(काष्ठा drm_i915_gem_object *obj, काष्ठा i915_mmap_offset *mmo)
अणु
	काष्ठा rb_node *rb, **p;

	spin_lock(&obj->mmo.lock);
	rb = शून्य;
	p = &obj->mmo.offsets.rb_node;
	जबतक (*p) अणु
		काष्ठा i915_mmap_offset *pos;

		rb = *p;
		pos = rb_entry(rb, typeof(*pos), offset);

		अगर (pos->mmap_type == mmo->mmap_type) अणु
			spin_unlock(&obj->mmo.lock);
			drm_vma_offset_हटाओ(obj->base.dev->vma_offset_manager,
					      &mmo->vma_node);
			kमुक्त(mmo);
			वापस pos;
		पूर्ण

		अगर (pos->mmap_type < mmo->mmap_type)
			p = &rb->rb_right;
		अन्यथा
			p = &rb->rb_left;
	पूर्ण
	rb_link_node(&mmo->offset, rb, p);
	rb_insert_color(&mmo->offset, &obj->mmo.offsets);
	spin_unlock(&obj->mmo.lock);

	वापस mmo;
पूर्ण

अटल काष्ठा i915_mmap_offset *
mmap_offset_attach(काष्ठा drm_i915_gem_object *obj,
		   क्रमागत i915_mmap_type mmap_type,
		   काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	काष्ठा i915_mmap_offset *mmo;
	पूर्णांक err;

	mmo = lookup_mmo(obj, mmap_type);
	अगर (mmo)
		जाओ out;

	mmo = kदो_स्मृति(माप(*mmo), GFP_KERNEL);
	अगर (!mmo)
		वापस ERR_PTR(-ENOMEM);

	mmo->obj = obj;
	mmo->mmap_type = mmap_type;
	drm_vma_node_reset(&mmo->vma_node);

	err = drm_vma_offset_add(obj->base.dev->vma_offset_manager,
				 &mmo->vma_node, obj->base.size / PAGE_SIZE);
	अगर (likely(!err))
		जाओ insert;

	/* Attempt to reap some mmap space from dead objects */
	err = पूर्णांकel_gt_retire_requests_समयout(&i915->gt, MAX_SCHEDULE_TIMEOUT);
	अगर (err)
		जाओ err;

	i915_gem_drain_मुक्तd_objects(i915);
	err = drm_vma_offset_add(obj->base.dev->vma_offset_manager,
				 &mmo->vma_node, obj->base.size / PAGE_SIZE);
	अगर (err)
		जाओ err;

insert:
	mmo = insert_mmo(obj, mmo);
	GEM_BUG_ON(lookup_mmo(obj, mmap_type) != mmo);
out:
	अगर (file)
		drm_vma_node_allow(&mmo->vma_node, file);
	वापस mmo;

err:
	kमुक्त(mmo);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक
__assign_mmap_offset(काष्ठा drm_file *file,
		     u32 handle,
		     क्रमागत i915_mmap_type mmap_type,
		     u64 *offset)
अणु
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_mmap_offset *mmo;
	पूर्णांक err;

	obj = i915_gem_object_lookup(file, handle);
	अगर (!obj)
		वापस -ENOENT;

	अगर (i915_gem_object_never_mmap(obj)) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (mmap_type != I915_MMAP_TYPE_GTT &&
	    !i915_gem_object_has_काष्ठा_page(obj) &&
	    !i915_gem_object_type_has(obj, I915_GEM_OBJECT_HAS_IOMEM)) अणु
		err = -ENODEV;
		जाओ out;
	पूर्ण

	mmo = mmap_offset_attach(obj, mmap_type, file);
	अगर (IS_ERR(mmo)) अणु
		err = PTR_ERR(mmo);
		जाओ out;
	पूर्ण

	*offset = drm_vma_node_offset_addr(&mmo->vma_node);
	err = 0;
out:
	i915_gem_object_put(obj);
	वापस err;
पूर्ण

पूर्णांक
i915_gem_dumb_mmap_offset(काष्ठा drm_file *file,
			  काष्ठा drm_device *dev,
			  u32 handle,
			  u64 *offset)
अणु
	क्रमागत i915_mmap_type mmap_type;

	अगर (boot_cpu_has(X86_FEATURE_PAT))
		mmap_type = I915_MMAP_TYPE_WC;
	अन्यथा अगर (!i915_ggtt_has_aperture(&to_i915(dev)->ggtt))
		वापस -ENODEV;
	अन्यथा
		mmap_type = I915_MMAP_TYPE_GTT;

	वापस __assign_mmap_offset(file, handle, mmap_type, offset);
पूर्ण

/**
 * i915_gem_mmap_offset_ioctl - prepare an object क्रम GTT mmap'ing
 * @dev: DRM device
 * @data: GTT mapping ioctl data
 * @file: GEM object info
 *
 * Simply वापसs the fake offset to userspace so it can mmap it.
 * The mmap call will end up in drm_gem_mmap(), which will set things
 * up so we can get faults in the handler above.
 *
 * The fault handler will take care of binding the object पूर्णांकo the GTT
 * (since it may have been evicted to make room क्रम something), allocating
 * a fence रेजिस्टर, and mapping the appropriate aperture address पूर्णांकo
 * userspace.
 */
पूर्णांक
i915_gem_mmap_offset_ioctl(काष्ठा drm_device *dev, व्योम *data,
			   काष्ठा drm_file *file)
अणु
	काष्ठा drm_i915_निजी *i915 = to_i915(dev);
	काष्ठा drm_i915_gem_mmap_offset *args = data;
	क्रमागत i915_mmap_type type;
	पूर्णांक err;

	/*
	 * Historically we failed to check args.pad and args.offset
	 * and so we cannot use those fields क्रम user input and we cannot
	 * add -EINVAL क्रम them as the ABI is fixed, i.e. old userspace
	 * may be feeding in garbage in those fields.
	 *
	 * अगर (args->pad) वापस -EINVAL; is verbotten!
	 */

	err = i915_user_extensions(u64_to_user_ptr(args->extensions),
				   शून्य, 0, शून्य);
	अगर (err)
		वापस err;

	चयन (args->flags) अणु
	हाल I915_MMAP_OFFSET_GTT:
		अगर (!i915_ggtt_has_aperture(&i915->ggtt))
			वापस -ENODEV;
		type = I915_MMAP_TYPE_GTT;
		अवरोध;

	हाल I915_MMAP_OFFSET_WC:
		अगर (!boot_cpu_has(X86_FEATURE_PAT))
			वापस -ENODEV;
		type = I915_MMAP_TYPE_WC;
		अवरोध;

	हाल I915_MMAP_OFFSET_WB:
		type = I915_MMAP_TYPE_WB;
		अवरोध;

	हाल I915_MMAP_OFFSET_UC:
		अगर (!boot_cpu_has(X86_FEATURE_PAT))
			वापस -ENODEV;
		type = I915_MMAP_TYPE_UC;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस __assign_mmap_offset(file, args->handle, type, &args->offset);
पूर्ण

अटल व्योम vm_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा i915_mmap_offset *mmo = vma->vm_निजी_data;
	काष्ठा drm_i915_gem_object *obj = mmo->obj;

	GEM_BUG_ON(!obj);
	i915_gem_object_get(obj);
पूर्ण

अटल व्योम vm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा i915_mmap_offset *mmo = vma->vm_निजी_data;
	काष्ठा drm_i915_gem_object *obj = mmo->obj;

	GEM_BUG_ON(!obj);
	i915_gem_object_put(obj);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा vm_ops_gtt = अणु
	.fault = vm_fault_gtt,
	.access = vm_access,
	.खोलो = vm_खोलो,
	.बंद = vm_बंद,
पूर्ण;

अटल स्थिर काष्ठा vm_operations_काष्ठा vm_ops_cpu = अणु
	.fault = vm_fault_cpu,
	.access = vm_access,
	.खोलो = vm_खोलो,
	.बंद = vm_बंद,
पूर्ण;

अटल पूर्णांक singleton_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा drm_i915_निजी *i915 = file->निजी_data;

	cmpxchg(&i915->gem.mmap_singleton, file, शून्य);
	drm_dev_put(&i915->drm);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations singleton_fops = अणु
	.owner = THIS_MODULE,
	.release = singleton_release,
पूर्ण;

अटल काष्ठा file *mmap_singleton(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा file *file;

	rcu_पढ़ो_lock();
	file = READ_ONCE(i915->gem.mmap_singleton);
	अगर (file && !get_file_rcu(file))
		file = शून्य;
	rcu_पढ़ो_unlock();
	अगर (file)
		वापस file;

	file = anon_inode_getfile("i915.gem", &singleton_fops, i915, O_RDWR);
	अगर (IS_ERR(file))
		वापस file;

	/* Everyone shares a single global address space */
	file->f_mapping = i915->drm.anon_inode->i_mapping;

	smp_store_mb(i915->gem.mmap_singleton, file);
	drm_dev_get(&i915->drm);

	वापस file;
पूर्ण

/*
 * This overcomes the limitation in drm_gem_mmap's assignment of a
 * drm_gem_object as the vma->vm_निजी_data. Since we need to
 * be able to resolve multiple mmap offsets which could be tied
 * to a single gem object.
 */
पूर्णांक i915_gem_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_vma_offset_node *node;
	काष्ठा drm_file *priv = filp->निजी_data;
	काष्ठा drm_device *dev = priv->minor->dev;
	काष्ठा drm_i915_gem_object *obj = शून्य;
	काष्ठा i915_mmap_offset *mmo = शून्य;
	काष्ठा file *anon;

	अगर (drm_dev_is_unplugged(dev))
		वापस -ENODEV;

	rcu_पढ़ो_lock();
	drm_vma_offset_lock_lookup(dev->vma_offset_manager);
	node = drm_vma_offset_exact_lookup_locked(dev->vma_offset_manager,
						  vma->vm_pgoff,
						  vma_pages(vma));
	अगर (node && drm_vma_node_is_allowed(node, priv)) अणु
		/*
		 * Skip 0-refcnted objects as it is in the process of being
		 * destroyed and will be invalid when the vma manager lock
		 * is released.
		 */
		mmo = container_of(node, काष्ठा i915_mmap_offset, vma_node);
		obj = i915_gem_object_get_rcu(mmo->obj);
	पूर्ण
	drm_vma_offset_unlock_lookup(dev->vma_offset_manager);
	rcu_पढ़ो_unlock();
	अगर (!obj)
		वापस node ? -EACCES : -EINVAL;

	अगर (i915_gem_object_is_पढ़ोonly(obj)) अणु
		अगर (vma->vm_flags & VM_WRITE) अणु
			i915_gem_object_put(obj);
			वापस -EINVAL;
		पूर्ण
		vma->vm_flags &= ~VM_MAYWRITE;
	पूर्ण

	anon = mmap_singleton(to_i915(dev));
	अगर (IS_ERR(anon)) अणु
		i915_gem_object_put(obj);
		वापस PTR_ERR(anon);
	पूर्ण

	vma->vm_flags |= VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_निजी_data = mmo;

	/*
	 * We keep the ref on mmo->obj, not vm_file, but we require
	 * vma->vm_file->f_mapping, see vma_link(), क्रम later revocation.
	 * Our userspace is accustomed to having per-file resource cleanup
	 * (i.e. contexts, objects and requests) on their बंद(fd), which
	 * requires aव्योमing extraneous references to their filp, hence why
	 * we prefer to use an anonymous file क्रम their mmaps.
	 */
	vma_set_file(vma, anon);
	/* Drop the initial creation reference, the vma is now holding one. */
	fput(anon);

	चयन (mmo->mmap_type) अणु
	हाल I915_MMAP_TYPE_WC:
		vma->vm_page_prot =
			pgprot_ग_लिखोcombine(vm_get_page_prot(vma->vm_flags));
		vma->vm_ops = &vm_ops_cpu;
		अवरोध;

	हाल I915_MMAP_TYPE_WB:
		vma->vm_page_prot = vm_get_page_prot(vma->vm_flags);
		vma->vm_ops = &vm_ops_cpu;
		अवरोध;

	हाल I915_MMAP_TYPE_UC:
		vma->vm_page_prot =
			pgprot_noncached(vm_get_page_prot(vma->vm_flags));
		vma->vm_ops = &vm_ops_cpu;
		अवरोध;

	हाल I915_MMAP_TYPE_GTT:
		vma->vm_page_prot =
			pgprot_ग_लिखोcombine(vm_get_page_prot(vma->vm_flags));
		vma->vm_ops = &vm_ops_gtt;
		अवरोध;
	पूर्ण
	vma->vm_page_prot = pgprot_decrypted(vma->vm_page_prot);

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftests/i915_gem_mman.c"
#पूर्ण_अगर
