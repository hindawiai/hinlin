<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Jerome Glisse.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Dave Airlie
 *          Alex Deucher
 *          Jerome Glisse
 */
#समावेश <linux/kसमय.स>
#समावेश <linux/module.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-buf.h>

#समावेश <drm/amdgpu_drm.h>
#समावेश <drm/drm_gem_tपंचांग_helper.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_display.h"
#समावेश "amdgpu_dma_buf.h"
#समावेश "amdgpu_xgmi.h"

अटल स्थिर काष्ठा drm_gem_object_funcs amdgpu_gem_object_funcs;

अटल व्योम amdgpu_gem_object_मुक्त(काष्ठा drm_gem_object *gobj)
अणु
	काष्ठा amdgpu_bo *robj = gem_to_amdgpu_bo(gobj);

	अगर (robj) अणु
		amdgpu_mn_unरेजिस्टर(robj);
		amdgpu_bo_unref(&robj);
	पूर्ण
पूर्ण

पूर्णांक amdgpu_gem_object_create(काष्ठा amdgpu_device *adev, अचिन्हित दीर्घ size,
			     पूर्णांक alignment, u32 initial_करोमुख्य,
			     u64 flags, क्रमागत tपंचांग_bo_type type,
			     काष्ठा dma_resv *resv,
			     काष्ठा drm_gem_object **obj)
अणु
	काष्ठा amdgpu_bo *bo;
	काष्ठा amdgpu_bo_user *ubo;
	काष्ठा amdgpu_bo_param bp;
	पूर्णांक r;

	स_रखो(&bp, 0, माप(bp));
	*obj = शून्य;

	bp.size = size;
	bp.byte_align = alignment;
	bp.type = type;
	bp.resv = resv;
	bp.preferred_करोमुख्य = initial_करोमुख्य;
	bp.flags = flags;
	bp.करोमुख्य = initial_करोमुख्य;
	bp.bo_ptr_size = माप(काष्ठा amdgpu_bo);

	r = amdgpu_bo_create_user(adev, &bp, &ubo);
	अगर (r)
		वापस r;

	bo = &ubo->bo;
	*obj = &bo->tbo.base;
	(*obj)->funcs = &amdgpu_gem_object_funcs;

	वापस 0;
पूर्ण

व्योम amdgpu_gem_क्रमce_release(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा drm_device *ddev = adev_to_drm(adev);
	काष्ठा drm_file *file;

	mutex_lock(&ddev->filelist_mutex);

	list_क्रम_each_entry(file, &ddev->filelist, lhead) अणु
		काष्ठा drm_gem_object *gobj;
		पूर्णांक handle;

		WARN_ONCE(1, "Still active user space clients!\n");
		spin_lock(&file->table_lock);
		idr_क्रम_each_entry(&file->object_idr, gobj, handle) अणु
			WARN_ONCE(1, "And also active allocations!\n");
			drm_gem_object_put(gobj);
		पूर्ण
		idr_destroy(&file->object_idr);
		spin_unlock(&file->table_lock);
	पूर्ण

	mutex_unlock(&ddev->filelist_mutex);
पूर्ण

/*
 * Call from drm_gem_handle_create which appear in both new and खोलो ioctl
 * हाल.
 */
अटल पूर्णांक amdgpu_gem_object_खोलो(काष्ठा drm_gem_object *obj,
				  काष्ठा drm_file *file_priv)
अणु
	काष्ठा amdgpu_bo *abo = gem_to_amdgpu_bo(obj);
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(abo->tbo.bdev);
	काष्ठा amdgpu_fpriv *fpriv = file_priv->driver_priv;
	काष्ठा amdgpu_vm *vm = &fpriv->vm;
	काष्ठा amdgpu_bo_va *bo_va;
	काष्ठा mm_काष्ठा *mm;
	पूर्णांक r;

	mm = amdgpu_tपंचांग_tt_get_usermm(abo->tbo.tपंचांग);
	अगर (mm && mm != current->mm)
		वापस -EPERM;

	अगर (abo->flags & AMDGPU_GEM_CREATE_VM_ALWAYS_VALID &&
	    abo->tbo.base.resv != vm->root.base.bo->tbo.base.resv)
		वापस -EPERM;

	r = amdgpu_bo_reserve(abo, false);
	अगर (r)
		वापस r;

	bo_va = amdgpu_vm_bo_find(vm, abo);
	अगर (!bo_va) अणु
		bo_va = amdgpu_vm_bo_add(adev, vm, abo);
	पूर्ण अन्यथा अणु
		++bo_va->ref_count;
	पूर्ण
	amdgpu_bo_unreserve(abo);
	वापस 0;
पूर्ण

अटल व्योम amdgpu_gem_object_बंद(काष्ठा drm_gem_object *obj,
				    काष्ठा drm_file *file_priv)
अणु
	काष्ठा amdgpu_bo *bo = gem_to_amdgpu_bo(obj);
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);
	काष्ठा amdgpu_fpriv *fpriv = file_priv->driver_priv;
	काष्ठा amdgpu_vm *vm = &fpriv->vm;

	काष्ठा amdgpu_bo_list_entry vm_pd;
	काष्ठा list_head list, duplicates;
	काष्ठा dma_fence *fence = शून्य;
	काष्ठा tपंचांग_validate_buffer tv;
	काष्ठा ww_acquire_ctx ticket;
	काष्ठा amdgpu_bo_va *bo_va;
	दीर्घ r;

	INIT_LIST_HEAD(&list);
	INIT_LIST_HEAD(&duplicates);

	tv.bo = &bo->tbo;
	tv.num_shared = 2;
	list_add(&tv.head, &list);

	amdgpu_vm_get_pd_bo(vm, &list, &vm_pd);

	r = tपंचांग_eu_reserve_buffers(&ticket, &list, false, &duplicates);
	अगर (r) अणु
		dev_err(adev->dev, "leaking bo va because "
			"we fail to reserve bo (%ld)\n", r);
		वापस;
	पूर्ण
	bo_va = amdgpu_vm_bo_find(vm, bo);
	अगर (!bo_va || --bo_va->ref_count)
		जाओ out_unlock;

	amdgpu_vm_bo_rmv(adev, bo_va);
	अगर (!amdgpu_vm_पढ़ोy(vm))
		जाओ out_unlock;

	fence = dma_resv_get_excl(bo->tbo.base.resv);
	अगर (fence) अणु
		amdgpu_bo_fence(bo, fence, true);
		fence = शून्य;
	पूर्ण

	r = amdgpu_vm_clear_मुक्तd(adev, vm, &fence);
	अगर (r || !fence)
		जाओ out_unlock;

	amdgpu_bo_fence(bo, fence, true);
	dma_fence_put(fence);

out_unlock:
	अगर (unlikely(r < 0))
		dev_err(adev->dev, "failed to clear page "
			"tables on GEM object close (%ld)\n", r);
	tपंचांग_eu_backoff_reservation(&ticket, &list);
पूर्ण

अटल स्थिर काष्ठा drm_gem_object_funcs amdgpu_gem_object_funcs = अणु
	.मुक्त = amdgpu_gem_object_मुक्त,
	.खोलो = amdgpu_gem_object_खोलो,
	.बंद = amdgpu_gem_object_बंद,
	.export = amdgpu_gem_prime_export,
	.vmap = drm_gem_tपंचांग_vmap,
	.vunmap = drm_gem_tपंचांग_vunmap,
पूर्ण;

/*
 * GEM ioctls.
 */
पूर्णांक amdgpu_gem_create_ioctl(काष्ठा drm_device *dev, व्योम *data,
			    काष्ठा drm_file *filp)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_fpriv *fpriv = filp->driver_priv;
	काष्ठा amdgpu_vm *vm = &fpriv->vm;
	जोड़ drm_amdgpu_gem_create *args = data;
	uपूर्णांक64_t flags = args->in.करोमुख्य_flags;
	uपूर्णांक64_t size = args->in.bo_size;
	काष्ठा dma_resv *resv = शून्य;
	काष्ठा drm_gem_object *gobj;
	uपूर्णांक32_t handle, initial_करोमुख्य;
	पूर्णांक r;

	/* reject invalid gem flags */
	अगर (flags & ~(AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED |
		      AMDGPU_GEM_CREATE_NO_CPU_ACCESS |
		      AMDGPU_GEM_CREATE_CPU_GTT_USWC |
		      AMDGPU_GEM_CREATE_VRAM_CLEARED |
		      AMDGPU_GEM_CREATE_VM_ALWAYS_VALID |
		      AMDGPU_GEM_CREATE_EXPLICIT_SYNC |
		      AMDGPU_GEM_CREATE_ENCRYPTED))

		वापस -EINVAL;

	/* reject invalid gem करोमुख्यs */
	अगर (args->in.करोमुख्यs & ~AMDGPU_GEM_DOMAIN_MASK)
		वापस -EINVAL;

	अगर (!amdgpu_is_पंचांगz(adev) && (flags & AMDGPU_GEM_CREATE_ENCRYPTED)) अणु
		DRM_NOTE_ONCE("Cannot allocate secure buffer since TMZ is disabled\n");
		वापस -EINVAL;
	पूर्ण

	/* create a gem object to contain this object in */
	अगर (args->in.करोमुख्यs & (AMDGPU_GEM_DOMAIN_GDS |
	    AMDGPU_GEM_DOMAIN_GWS | AMDGPU_GEM_DOMAIN_OA)) अणु
		अगर (flags & AMDGPU_GEM_CREATE_VM_ALWAYS_VALID) अणु
			/* अगर gds bo is created from user space, it must be
			 * passed to bo list
			 */
			DRM_ERROR("GDS bo cannot be per-vm-bo\n");
			वापस -EINVAL;
		पूर्ण
		flags |= AMDGPU_GEM_CREATE_NO_CPU_ACCESS;
	पूर्ण

	अगर (flags & AMDGPU_GEM_CREATE_VM_ALWAYS_VALID) अणु
		r = amdgpu_bo_reserve(vm->root.base.bo, false);
		अगर (r)
			वापस r;

		resv = vm->root.base.bo->tbo.base.resv;
	पूर्ण

	initial_करोमुख्य = (u32)(0xffffffff & args->in.करोमुख्यs);
retry:
	r = amdgpu_gem_object_create(adev, size, args->in.alignment,
				     initial_करोमुख्य,
				     flags, tपंचांग_bo_type_device, resv, &gobj);
	अगर (r) अणु
		अगर (r != -ERESTARTSYS) अणु
			अगर (flags & AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED) अणु
				flags &= ~AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED;
				जाओ retry;
			पूर्ण

			अगर (initial_करोमुख्य == AMDGPU_GEM_DOMAIN_VRAM) अणु
				initial_करोमुख्य |= AMDGPU_GEM_DOMAIN_GTT;
				जाओ retry;
			पूर्ण
			DRM_DEBUG("Failed to allocate GEM object (%llu, %d, %llu, %d)\n",
				  size, initial_करोमुख्य, args->in.alignment, r);
		पूर्ण
		वापस r;
	पूर्ण

	अगर (flags & AMDGPU_GEM_CREATE_VM_ALWAYS_VALID) अणु
		अगर (!r) अणु
			काष्ठा amdgpu_bo *abo = gem_to_amdgpu_bo(gobj);

			abo->parent = amdgpu_bo_ref(vm->root.base.bo);
		पूर्ण
		amdgpu_bo_unreserve(vm->root.base.bo);
	पूर्ण
	अगर (r)
		वापस r;

	r = drm_gem_handle_create(filp, gobj, &handle);
	/* drop reference from allocate - handle holds it now */
	drm_gem_object_put(gobj);
	अगर (r)
		वापस r;

	स_रखो(args, 0, माप(*args));
	args->out.handle = handle;
	वापस 0;
पूर्ण

पूर्णांक amdgpu_gem_userptr_ioctl(काष्ठा drm_device *dev, व्योम *data,
			     काष्ठा drm_file *filp)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु true, false पूर्ण;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा drm_amdgpu_gem_userptr *args = data;
	काष्ठा drm_gem_object *gobj;
	काष्ठा amdgpu_bo *bo;
	uपूर्णांक32_t handle;
	पूर्णांक r;

	args->addr = untagged_addr(args->addr);

	अगर (offset_in_page(args->addr | args->size))
		वापस -EINVAL;

	/* reject unknown flag values */
	अगर (args->flags & ~(AMDGPU_GEM_USERPTR_READONLY |
	    AMDGPU_GEM_USERPTR_ANONONLY | AMDGPU_GEM_USERPTR_VALIDATE |
	    AMDGPU_GEM_USERPTR_REGISTER))
		वापस -EINVAL;

	अगर (!(args->flags & AMDGPU_GEM_USERPTR_READONLY) &&
	     !(args->flags & AMDGPU_GEM_USERPTR_REGISTER)) अणु

		/* अगर we want to ग_लिखो to it we must install a MMU notअगरier */
		वापस -EACCES;
	पूर्ण

	/* create a gem object to contain this object in */
	r = amdgpu_gem_object_create(adev, args->size, 0, AMDGPU_GEM_DOMAIN_CPU,
				     0, tपंचांग_bo_type_device, शून्य, &gobj);
	अगर (r)
		वापस r;

	bo = gem_to_amdgpu_bo(gobj);
	bo->preferred_करोमुख्यs = AMDGPU_GEM_DOMAIN_GTT;
	bo->allowed_करोमुख्यs = AMDGPU_GEM_DOMAIN_GTT;
	r = amdgpu_tपंचांग_tt_set_userptr(&bo->tbo, args->addr, args->flags);
	अगर (r)
		जाओ release_object;

	अगर (args->flags & AMDGPU_GEM_USERPTR_REGISTER) अणु
		r = amdgpu_mn_रेजिस्टर(bo, args->addr);
		अगर (r)
			जाओ release_object;
	पूर्ण

	अगर (args->flags & AMDGPU_GEM_USERPTR_VALIDATE) अणु
		r = amdgpu_tपंचांग_tt_get_user_pages(bo, bo->tbo.tपंचांग->pages);
		अगर (r)
			जाओ release_object;

		r = amdgpu_bo_reserve(bo, true);
		अगर (r)
			जाओ user_pages_करोne;

		amdgpu_bo_placement_from_करोमुख्य(bo, AMDGPU_GEM_DOMAIN_GTT);
		r = tपंचांग_bo_validate(&bo->tbo, &bo->placement, &ctx);
		amdgpu_bo_unreserve(bo);
		अगर (r)
			जाओ user_pages_करोne;
	पूर्ण

	r = drm_gem_handle_create(filp, gobj, &handle);
	अगर (r)
		जाओ user_pages_करोne;

	args->handle = handle;

user_pages_करोne:
	अगर (args->flags & AMDGPU_GEM_USERPTR_VALIDATE)
		amdgpu_tपंचांग_tt_get_user_pages_करोne(bo->tbo.tपंचांग);

release_object:
	drm_gem_object_put(gobj);

	वापस r;
पूर्ण

पूर्णांक amdgpu_mode_dumb_mmap(काष्ठा drm_file *filp,
			  काष्ठा drm_device *dev,
			  uपूर्णांक32_t handle, uपूर्णांक64_t *offset_p)
अणु
	काष्ठा drm_gem_object *gobj;
	काष्ठा amdgpu_bo *robj;

	gobj = drm_gem_object_lookup(filp, handle);
	अगर (gobj == शून्य) अणु
		वापस -ENOENT;
	पूर्ण
	robj = gem_to_amdgpu_bo(gobj);
	अगर (amdgpu_tपंचांग_tt_get_usermm(robj->tbo.tपंचांग) ||
	    (robj->flags & AMDGPU_GEM_CREATE_NO_CPU_ACCESS)) अणु
		drm_gem_object_put(gobj);
		वापस -EPERM;
	पूर्ण
	*offset_p = amdgpu_bo_mmap_offset(robj);
	drm_gem_object_put(gobj);
	वापस 0;
पूर्ण

पूर्णांक amdgpu_gem_mmap_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *filp)
अणु
	जोड़ drm_amdgpu_gem_mmap *args = data;
	uपूर्णांक32_t handle = args->in.handle;
	स_रखो(args, 0, माप(*args));
	वापस amdgpu_mode_dumb_mmap(filp, dev, handle, &args->out.addr_ptr);
पूर्ण

/**
 * amdgpu_gem_समयout - calculate jअगरfies समयout from असलolute value
 *
 * @समयout_ns: समयout in ns
 *
 * Calculate the समयout in jअगरfies from an असलolute समयout in ns.
 */
अचिन्हित दीर्घ amdgpu_gem_समयout(uपूर्णांक64_t समयout_ns)
अणु
	अचिन्हित दीर्घ समयout_jअगरfies;
	kसमय_प्रकार समयout;

	/* clamp समयout अगर it's to large */
	अगर (((पूर्णांक64_t)समयout_ns) < 0)
		वापस MAX_SCHEDULE_TIMEOUT;

	समयout = kसमय_sub(ns_to_kसमय(समयout_ns), kसमय_get());
	अगर (kसमय_प्रकारo_ns(समयout) < 0)
		वापस 0;

	समयout_jअगरfies = nsecs_to_jअगरfies(kसमय_प्रकारo_ns(समयout));
	/*  clamp समयout to aव्योम अचिन्हित-> चिन्हित overflow */
	अगर (समयout_jअगरfies > MAX_SCHEDULE_TIMEOUT )
		वापस MAX_SCHEDULE_TIMEOUT - 1;

	वापस समयout_jअगरfies;
पूर्ण

पूर्णांक amdgpu_gem_रुको_idle_ioctl(काष्ठा drm_device *dev, व्योम *data,
			      काष्ठा drm_file *filp)
अणु
	जोड़ drm_amdgpu_gem_रुको_idle *args = data;
	काष्ठा drm_gem_object *gobj;
	काष्ठा amdgpu_bo *robj;
	uपूर्णांक32_t handle = args->in.handle;
	अचिन्हित दीर्घ समयout = amdgpu_gem_समयout(args->in.समयout);
	पूर्णांक r = 0;
	दीर्घ ret;

	gobj = drm_gem_object_lookup(filp, handle);
	अगर (gobj == शून्य) अणु
		वापस -ENOENT;
	पूर्ण
	robj = gem_to_amdgpu_bo(gobj);
	ret = dma_resv_रुको_समयout_rcu(robj->tbo.base.resv, true, true,
						  समयout);

	/* ret == 0 means not संकेतed,
	 * ret > 0 means संकेतed
	 * ret < 0 means पूर्णांकerrupted beक्रमe समयout
	 */
	अगर (ret >= 0) अणु
		स_रखो(args, 0, माप(*args));
		args->out.status = (ret == 0);
	पूर्ण अन्यथा
		r = ret;

	drm_gem_object_put(gobj);
	वापस r;
पूर्ण

पूर्णांक amdgpu_gem_metadata_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *filp)
अणु
	काष्ठा drm_amdgpu_gem_metadata *args = data;
	काष्ठा drm_gem_object *gobj;
	काष्ठा amdgpu_bo *robj;
	पूर्णांक r = -1;

	DRM_DEBUG("%d \n", args->handle);
	gobj = drm_gem_object_lookup(filp, args->handle);
	अगर (gobj == शून्य)
		वापस -ENOENT;
	robj = gem_to_amdgpu_bo(gobj);

	r = amdgpu_bo_reserve(robj, false);
	अगर (unlikely(r != 0))
		जाओ out;

	अगर (args->op == AMDGPU_GEM_METADATA_OP_GET_METADATA) अणु
		amdgpu_bo_get_tiling_flags(robj, &args->data.tiling_info);
		r = amdgpu_bo_get_metadata(robj, args->data.data,
					   माप(args->data.data),
					   &args->data.data_size_bytes,
					   &args->data.flags);
	पूर्ण अन्यथा अगर (args->op == AMDGPU_GEM_METADATA_OP_SET_METADATA) अणु
		अगर (args->data.data_size_bytes > माप(args->data.data)) अणु
			r = -EINVAL;
			जाओ unreserve;
		पूर्ण
		r = amdgpu_bo_set_tiling_flags(robj, args->data.tiling_info);
		अगर (!r)
			r = amdgpu_bo_set_metadata(robj, args->data.data,
						   args->data.data_size_bytes,
						   args->data.flags);
	पूर्ण

unreserve:
	amdgpu_bo_unreserve(robj);
out:
	drm_gem_object_put(gobj);
	वापस r;
पूर्ण

/**
 * amdgpu_gem_va_update_vm -update the bo_va in its VM
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @vm: vm to update
 * @bo_va: bo_va to update
 * @operation: map, unmap or clear
 *
 * Update the bo_va directly after setting its address. Errors are not
 * vital here, so they are not reported back to userspace.
 */
अटल व्योम amdgpu_gem_va_update_vm(काष्ठा amdgpu_device *adev,
				    काष्ठा amdgpu_vm *vm,
				    काष्ठा amdgpu_bo_va *bo_va,
				    uपूर्णांक32_t operation)
अणु
	पूर्णांक r;

	अगर (!amdgpu_vm_पढ़ोy(vm))
		वापस;

	r = amdgpu_vm_clear_मुक्तd(adev, vm, शून्य);
	अगर (r)
		जाओ error;

	अगर (operation == AMDGPU_VA_OP_MAP ||
	    operation == AMDGPU_VA_OP_REPLACE) अणु
		r = amdgpu_vm_bo_update(adev, bo_va, false);
		अगर (r)
			जाओ error;
	पूर्ण

	r = amdgpu_vm_update_pdes(adev, vm, false);

error:
	अगर (r && r != -ERESTARTSYS)
		DRM_ERROR("Couldn't update BO_VA (%d)\n", r);
पूर्ण

/**
 * amdgpu_gem_va_map_flags - map GEM UAPI flags पूर्णांकo hardware flags
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @flags: GEM UAPI flags
 *
 * Returns the GEM UAPI flags mapped पूर्णांकo hardware क्रम the ASIC.
 */
uपूर्णांक64_t amdgpu_gem_va_map_flags(काष्ठा amdgpu_device *adev, uपूर्णांक32_t flags)
अणु
	uपूर्णांक64_t pte_flag = 0;

	अगर (flags & AMDGPU_VM_PAGE_EXECUTABLE)
		pte_flag |= AMDGPU_PTE_EXECUTABLE;
	अगर (flags & AMDGPU_VM_PAGE_READABLE)
		pte_flag |= AMDGPU_PTE_READABLE;
	अगर (flags & AMDGPU_VM_PAGE_WRITEABLE)
		pte_flag |= AMDGPU_PTE_WRITEABLE;
	अगर (flags & AMDGPU_VM_PAGE_PRT)
		pte_flag |= AMDGPU_PTE_PRT;

	अगर (adev->gmc.gmc_funcs->map_mtype)
		pte_flag |= amdgpu_gmc_map_mtype(adev,
						 flags & AMDGPU_VM_MTYPE_MASK);

	वापस pte_flag;
पूर्ण

पूर्णांक amdgpu_gem_va_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *filp)
अणु
	स्थिर uपूर्णांक32_t valid_flags = AMDGPU_VM_DELAY_UPDATE |
		AMDGPU_VM_PAGE_READABLE | AMDGPU_VM_PAGE_WRITEABLE |
		AMDGPU_VM_PAGE_EXECUTABLE | AMDGPU_VM_MTYPE_MASK;
	स्थिर uपूर्णांक32_t prt_flags = AMDGPU_VM_DELAY_UPDATE |
		AMDGPU_VM_PAGE_PRT;

	काष्ठा drm_amdgpu_gem_va *args = data;
	काष्ठा drm_gem_object *gobj;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा amdgpu_fpriv *fpriv = filp->driver_priv;
	काष्ठा amdgpu_bo *abo;
	काष्ठा amdgpu_bo_va *bo_va;
	काष्ठा amdgpu_bo_list_entry vm_pd;
	काष्ठा tपंचांग_validate_buffer tv;
	काष्ठा ww_acquire_ctx ticket;
	काष्ठा list_head list, duplicates;
	uपूर्णांक64_t va_flags;
	uपूर्णांक64_t vm_size;
	पूर्णांक r = 0;

	अगर (args->va_address < AMDGPU_VA_RESERVED_SIZE) अणु
		dev_dbg(dev->dev,
			"va_address 0x%LX is in reserved area 0x%LX\n",
			args->va_address, AMDGPU_VA_RESERVED_SIZE);
		वापस -EINVAL;
	पूर्ण

	अगर (args->va_address >= AMDGPU_GMC_HOLE_START &&
	    args->va_address < AMDGPU_GMC_HOLE_END) अणु
		dev_dbg(dev->dev,
			"va_address 0x%LX is in VA hole 0x%LX-0x%LX\n",
			args->va_address, AMDGPU_GMC_HOLE_START,
			AMDGPU_GMC_HOLE_END);
		वापस -EINVAL;
	पूर्ण

	args->va_address &= AMDGPU_GMC_HOLE_MASK;

	vm_size = adev->vm_manager.max_pfn * AMDGPU_GPU_PAGE_SIZE;
	vm_size -= AMDGPU_VA_RESERVED_SIZE;
	अगर (args->va_address + args->map_size > vm_size) अणु
		dev_dbg(dev->dev,
			"va_address 0x%llx is in top reserved area 0x%llx\n",
			args->va_address + args->map_size, vm_size);
		वापस -EINVAL;
	पूर्ण

	अगर ((args->flags & ~valid_flags) && (args->flags & ~prt_flags)) अणु
		dev_dbg(dev->dev, "invalid flags combination 0x%08X\n",
			args->flags);
		वापस -EINVAL;
	पूर्ण

	चयन (args->operation) अणु
	हाल AMDGPU_VA_OP_MAP:
	हाल AMDGPU_VA_OP_UNMAP:
	हाल AMDGPU_VA_OP_CLEAR:
	हाल AMDGPU_VA_OP_REPLACE:
		अवरोध;
	शेष:
		dev_dbg(dev->dev, "unsupported operation %d\n",
			args->operation);
		वापस -EINVAL;
	पूर्ण

	INIT_LIST_HEAD(&list);
	INIT_LIST_HEAD(&duplicates);
	अगर ((args->operation != AMDGPU_VA_OP_CLEAR) &&
	    !(args->flags & AMDGPU_VM_PAGE_PRT)) अणु
		gobj = drm_gem_object_lookup(filp, args->handle);
		अगर (gobj == शून्य)
			वापस -ENOENT;
		abo = gem_to_amdgpu_bo(gobj);
		tv.bo = &abo->tbo;
		अगर (abo->flags & AMDGPU_GEM_CREATE_VM_ALWAYS_VALID)
			tv.num_shared = 1;
		अन्यथा
			tv.num_shared = 0;
		list_add(&tv.head, &list);
	पूर्ण अन्यथा अणु
		gobj = शून्य;
		abo = शून्य;
	पूर्ण

	amdgpu_vm_get_pd_bo(&fpriv->vm, &list, &vm_pd);

	r = tपंचांग_eu_reserve_buffers(&ticket, &list, true, &duplicates);
	अगर (r)
		जाओ error_unref;

	अगर (abo) अणु
		bo_va = amdgpu_vm_bo_find(&fpriv->vm, abo);
		अगर (!bo_va) अणु
			r = -ENOENT;
			जाओ error_backoff;
		पूर्ण
	पूर्ण अन्यथा अगर (args->operation != AMDGPU_VA_OP_CLEAR) अणु
		bo_va = fpriv->prt_va;
	पूर्ण अन्यथा अणु
		bo_va = शून्य;
	पूर्ण

	चयन (args->operation) अणु
	हाल AMDGPU_VA_OP_MAP:
		va_flags = amdgpu_gem_va_map_flags(adev, args->flags);
		r = amdgpu_vm_bo_map(adev, bo_va, args->va_address,
				     args->offset_in_bo, args->map_size,
				     va_flags);
		अवरोध;
	हाल AMDGPU_VA_OP_UNMAP:
		r = amdgpu_vm_bo_unmap(adev, bo_va, args->va_address);
		अवरोध;

	हाल AMDGPU_VA_OP_CLEAR:
		r = amdgpu_vm_bo_clear_mappings(adev, &fpriv->vm,
						args->va_address,
						args->map_size);
		अवरोध;
	हाल AMDGPU_VA_OP_REPLACE:
		va_flags = amdgpu_gem_va_map_flags(adev, args->flags);
		r = amdgpu_vm_bo_replace_map(adev, bo_va, args->va_address,
					     args->offset_in_bo, args->map_size,
					     va_flags);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (!r && !(args->flags & AMDGPU_VM_DELAY_UPDATE) && !amdgpu_vm_debug)
		amdgpu_gem_va_update_vm(adev, &fpriv->vm, bo_va,
					args->operation);

error_backoff:
	tपंचांग_eu_backoff_reservation(&ticket, &list);

error_unref:
	drm_gem_object_put(gobj);
	वापस r;
पूर्ण

पूर्णांक amdgpu_gem_op_ioctl(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *filp)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा drm_amdgpu_gem_op *args = data;
	काष्ठा drm_gem_object *gobj;
	काष्ठा amdgpu_vm_bo_base *base;
	काष्ठा amdgpu_bo *robj;
	पूर्णांक r;

	gobj = drm_gem_object_lookup(filp, args->handle);
	अगर (gobj == शून्य) अणु
		वापस -ENOENT;
	पूर्ण
	robj = gem_to_amdgpu_bo(gobj);

	r = amdgpu_bo_reserve(robj, false);
	अगर (unlikely(r))
		जाओ out;

	चयन (args->op) अणु
	हाल AMDGPU_GEM_OP_GET_GEM_CREATE_INFO: अणु
		काष्ठा drm_amdgpu_gem_create_in info;
		व्योम __user *out = u64_to_user_ptr(args->value);

		info.bo_size = robj->tbo.base.size;
		info.alignment = robj->tbo.mem.page_alignment << PAGE_SHIFT;
		info.करोमुख्यs = robj->preferred_करोमुख्यs;
		info.करोमुख्य_flags = robj->flags;
		amdgpu_bo_unreserve(robj);
		अगर (copy_to_user(out, &info, माप(info)))
			r = -EFAULT;
		अवरोध;
	पूर्ण
	हाल AMDGPU_GEM_OP_SET_PLACEMENT:
		अगर (robj->prime_shared_count && (args->value & AMDGPU_GEM_DOMAIN_VRAM)) अणु
			r = -EINVAL;
			amdgpu_bo_unreserve(robj);
			अवरोध;
		पूर्ण
		अगर (amdgpu_tपंचांग_tt_get_usermm(robj->tbo.tपंचांग)) अणु
			r = -EPERM;
			amdgpu_bo_unreserve(robj);
			अवरोध;
		पूर्ण
		क्रम (base = robj->vm_bo; base; base = base->next)
			अगर (amdgpu_xgmi_same_hive(amdgpu_tपंचांग_adev(robj->tbo.bdev),
				amdgpu_tपंचांग_adev(base->vm->root.base.bo->tbo.bdev))) अणु
				r = -EINVAL;
				amdgpu_bo_unreserve(robj);
				जाओ out;
			पूर्ण


		robj->preferred_करोमुख्यs = args->value & (AMDGPU_GEM_DOMAIN_VRAM |
							AMDGPU_GEM_DOMAIN_GTT |
							AMDGPU_GEM_DOMAIN_CPU);
		robj->allowed_करोमुख्यs = robj->preferred_करोमुख्यs;
		अगर (robj->allowed_करोमुख्यs == AMDGPU_GEM_DOMAIN_VRAM)
			robj->allowed_करोमुख्यs |= AMDGPU_GEM_DOMAIN_GTT;

		अगर (robj->flags & AMDGPU_GEM_CREATE_VM_ALWAYS_VALID)
			amdgpu_vm_bo_invalidate(adev, robj, true);

		amdgpu_bo_unreserve(robj);
		अवरोध;
	शेष:
		amdgpu_bo_unreserve(robj);
		r = -EINVAL;
	पूर्ण

out:
	drm_gem_object_put(gobj);
	वापस r;
पूर्ण

पूर्णांक amdgpu_mode_dumb_create(काष्ठा drm_file *file_priv,
			    काष्ठा drm_device *dev,
			    काष्ठा drm_mode_create_dumb *args)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा drm_gem_object *gobj;
	uपूर्णांक32_t handle;
	u64 flags = AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED |
		    AMDGPU_GEM_CREATE_CPU_GTT_USWC;
	u32 करोमुख्य;
	पूर्णांक r;

	/*
	 * The buffer वापसed from this function should be cleared, but
	 * it can only be करोne अगर the ring is enabled or we'll fail to
	 * create the buffer.
	 */
	अगर (adev->mman.buffer_funcs_enabled)
		flags |= AMDGPU_GEM_CREATE_VRAM_CLEARED;

	args->pitch = amdgpu_align_pitch(adev, args->width,
					 DIV_ROUND_UP(args->bpp, 8), 0);
	args->size = (u64)args->pitch * args->height;
	args->size = ALIGN(args->size, PAGE_SIZE);
	करोमुख्य = amdgpu_bo_get_preferred_pin_करोमुख्य(adev,
				amdgpu_display_supported_करोमुख्यs(adev, flags));
	r = amdgpu_gem_object_create(adev, args->size, 0, करोमुख्य, flags,
				     tपंचांग_bo_type_device, शून्य, &gobj);
	अगर (r)
		वापस -ENOMEM;

	r = drm_gem_handle_create(file_priv, gobj, &handle);
	/* drop reference from allocate - handle holds it now */
	drm_gem_object_put(gobj);
	अगर (r) अणु
		वापस r;
	पूर्ण
	args->handle = handle;
	वापस 0;
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)
अटल पूर्णांक amdgpu_debugfs_gem_info_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)m->निजी;
	काष्ठा drm_device *dev = adev_to_drm(adev);
	काष्ठा drm_file *file;
	पूर्णांक r;

	r = mutex_lock_पूर्णांकerruptible(&dev->filelist_mutex);
	अगर (r)
		वापस r;

	list_क्रम_each_entry(file, &dev->filelist, lhead) अणु
		काष्ठा task_काष्ठा *task;
		काष्ठा drm_gem_object *gobj;
		पूर्णांक id;

		/*
		 * Although we have a valid reference on file->pid, that करोes
		 * not guarantee that the task_काष्ठा who called get_pid() is
		 * still alive (e.g. get_pid(current) => विभाजन() => निकास()).
		 * Thereक्रमe, we need to protect this ->comm access using RCU.
		 */
		rcu_पढ़ो_lock();
		task = pid_task(file->pid, PIDTYPE_PID);
		seq_म_लिखो(m, "pid %8d command %s:\n", pid_nr(file->pid),
			   task ? task->comm : "<unknown>");
		rcu_पढ़ो_unlock();

		spin_lock(&file->table_lock);
		idr_क्रम_each_entry(&file->object_idr, gobj, id) अणु
			काष्ठा amdgpu_bo *bo = gem_to_amdgpu_bo(gobj);

			amdgpu_bo_prपूर्णांक_info(id, bo, m);
		पूर्ण
		spin_unlock(&file->table_lock);
	पूर्ण

	mutex_unlock(&dev->filelist_mutex);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(amdgpu_debugfs_gem_info);

#पूर्ण_अगर

व्योम amdgpu_debugfs_gem_init(काष्ठा amdgpu_device *adev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा drm_minor *minor = adev_to_drm(adev)->primary;
	काष्ठा dentry *root = minor->debugfs_root;

	debugfs_create_file("amdgpu_gem_info", 0444, root, adev,
			    &amdgpu_debugfs_gem_info_fops);
#पूर्ण_अगर
पूर्ण
