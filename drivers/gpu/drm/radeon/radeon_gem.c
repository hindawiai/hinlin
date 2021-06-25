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

#समावेश <linux/pci.h>

#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_gem_tपंचांग_helper.h>
#समावेश <drm/radeon_drm.h>

#समावेश "radeon.h"
#समावेश "radeon_prime.h"

काष्ठा dma_buf *radeon_gem_prime_export(काष्ठा drm_gem_object *gobj,
					पूर्णांक flags);
काष्ठा sg_table *radeon_gem_prime_get_sg_table(काष्ठा drm_gem_object *obj);
पूर्णांक radeon_gem_prime_pin(काष्ठा drm_gem_object *obj);
व्योम radeon_gem_prime_unpin(काष्ठा drm_gem_object *obj);

स्थिर काष्ठा drm_gem_object_funcs radeon_gem_object_funcs;

अटल व्योम radeon_gem_object_मुक्त(काष्ठा drm_gem_object *gobj)
अणु
	काष्ठा radeon_bo *robj = gem_to_radeon_bo(gobj);

	अगर (robj) अणु
		radeon_mn_unरेजिस्टर(robj);
		radeon_bo_unref(&robj);
	पूर्ण
पूर्ण

पूर्णांक radeon_gem_object_create(काष्ठा radeon_device *rdev, अचिन्हित दीर्घ size,
				पूर्णांक alignment, पूर्णांक initial_करोमुख्य,
				u32 flags, bool kernel,
				काष्ठा drm_gem_object **obj)
अणु
	काष्ठा radeon_bo *robj;
	अचिन्हित दीर्घ max_size;
	पूर्णांक r;

	*obj = शून्य;
	/* At least align on page size */
	अगर (alignment < PAGE_SIZE) अणु
		alignment = PAGE_SIZE;
	पूर्ण

	/* Maximum bo size is the unpinned gtt size since we use the gtt to
	 * handle vram to प्रणाली pool migrations.
	 */
	max_size = rdev->mc.gtt_size - rdev->gart_pin_size;
	अगर (size > max_size) अणु
		DRM_DEBUG("Allocation size %ldMb bigger than %ldMb limit\n",
			  size >> 20, max_size >> 20);
		वापस -ENOMEM;
	पूर्ण

retry:
	r = radeon_bo_create(rdev, size, alignment, kernel, initial_करोमुख्य,
			     flags, शून्य, शून्य, &robj);
	अगर (r) अणु
		अगर (r != -ERESTARTSYS) अणु
			अगर (initial_करोमुख्य == RADEON_GEM_DOMAIN_VRAM) अणु
				initial_करोमुख्य |= RADEON_GEM_DOMAIN_GTT;
				जाओ retry;
			पूर्ण
			DRM_ERROR("Failed to allocate GEM object (%ld, %d, %u, %d)\n",
				  size, initial_करोमुख्य, alignment, r);
		पूर्ण
		वापस r;
	पूर्ण
	*obj = &robj->tbo.base;
	(*obj)->funcs = &radeon_gem_object_funcs;
	robj->pid = task_pid_nr(current);

	mutex_lock(&rdev->gem.mutex);
	list_add_tail(&robj->list, &rdev->gem.objects);
	mutex_unlock(&rdev->gem.mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक radeon_gem_set_करोमुख्य(काष्ठा drm_gem_object *gobj,
			  uपूर्णांक32_t rकरोमुख्य, uपूर्णांक32_t wकरोमुख्य)
अणु
	काष्ठा radeon_bo *robj;
	uपूर्णांक32_t करोमुख्य;
	दीर्घ r;

	/* FIXME: reeimplement */
	robj = gem_to_radeon_bo(gobj);
	/* work out where to validate the buffer to */
	करोमुख्य = wकरोमुख्य;
	अगर (!करोमुख्य) अणु
		करोमुख्य = rकरोमुख्य;
	पूर्ण
	अगर (!करोमुख्य) अणु
		/* Do nothings */
		pr_warn("Set domain without domain !\n");
		वापस 0;
	पूर्ण
	अगर (करोमुख्य == RADEON_GEM_DOMAIN_CPU) अणु
		/* Asking क्रम cpu access रुको क्रम object idle */
		r = dma_resv_रुको_समयout_rcu(robj->tbo.base.resv, true, true, 30 * HZ);
		अगर (!r)
			r = -EBUSY;

		अगर (r < 0 && r != -EINTR) अणु
			pr_err("Failed to wait for object: %li\n", r);
			वापस r;
		पूर्ण
	पूर्ण
	अगर (करोमुख्य == RADEON_GEM_DOMAIN_VRAM && robj->prime_shared_count) अणु
		/* A BO that is associated with a dma-buf cannot be sensibly migrated to VRAM */
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक radeon_gem_init(काष्ठा radeon_device *rdev)
अणु
	INIT_LIST_HEAD(&rdev->gem.objects);
	वापस 0;
पूर्ण

व्योम radeon_gem_fini(काष्ठा radeon_device *rdev)
अणु
	radeon_bo_क्रमce_delete(rdev);
पूर्ण

/*
 * Call from drm_gem_handle_create which appear in both new and खोलो ioctl
 * हाल.
 */
अटल पूर्णांक radeon_gem_object_खोलो(काष्ठा drm_gem_object *obj, काष्ठा drm_file *file_priv)
अणु
	काष्ठा radeon_bo *rbo = gem_to_radeon_bo(obj);
	काष्ठा radeon_device *rdev = rbo->rdev;
	काष्ठा radeon_fpriv *fpriv = file_priv->driver_priv;
	काष्ठा radeon_vm *vm = &fpriv->vm;
	काष्ठा radeon_bo_va *bo_va;
	पूर्णांक r;

	अगर ((rdev->family < CHIP_CAYMAN) ||
	    (!rdev->accel_working)) अणु
		वापस 0;
	पूर्ण

	r = radeon_bo_reserve(rbo, false);
	अगर (r) अणु
		वापस r;
	पूर्ण

	bo_va = radeon_vm_bo_find(vm, rbo);
	अगर (!bo_va) अणु
		bo_va = radeon_vm_bo_add(rdev, vm, rbo);
	पूर्ण अन्यथा अणु
		++bo_va->ref_count;
	पूर्ण
	radeon_bo_unreserve(rbo);

	वापस 0;
पूर्ण

अटल व्योम radeon_gem_object_बंद(काष्ठा drm_gem_object *obj,
				    काष्ठा drm_file *file_priv)
अणु
	काष्ठा radeon_bo *rbo = gem_to_radeon_bo(obj);
	काष्ठा radeon_device *rdev = rbo->rdev;
	काष्ठा radeon_fpriv *fpriv = file_priv->driver_priv;
	काष्ठा radeon_vm *vm = &fpriv->vm;
	काष्ठा radeon_bo_va *bo_va;
	पूर्णांक r;

	अगर ((rdev->family < CHIP_CAYMAN) ||
	    (!rdev->accel_working)) अणु
		वापस;
	पूर्ण

	r = radeon_bo_reserve(rbo, true);
	अगर (r) अणु
		dev_err(rdev->dev, "leaking bo va because "
			"we fail to reserve bo (%d)\n", r);
		वापस;
	पूर्ण
	bo_va = radeon_vm_bo_find(vm, rbo);
	अगर (bo_va) अणु
		अगर (--bo_va->ref_count == 0) अणु
			radeon_vm_bo_rmv(rdev, bo_va);
		पूर्ण
	पूर्ण
	radeon_bo_unreserve(rbo);
पूर्ण

अटल पूर्णांक radeon_gem_handle_lockup(काष्ठा radeon_device *rdev, पूर्णांक r)
अणु
	अगर (r == -EDEADLK) अणु
		r = radeon_gpu_reset(rdev);
		अगर (!r)
			r = -EAGAIN;
	पूर्ण
	वापस r;
पूर्ण

स्थिर काष्ठा drm_gem_object_funcs radeon_gem_object_funcs = अणु
	.मुक्त = radeon_gem_object_मुक्त,
	.खोलो = radeon_gem_object_खोलो,
	.बंद = radeon_gem_object_बंद,
	.export = radeon_gem_prime_export,
	.pin = radeon_gem_prime_pin,
	.unpin = radeon_gem_prime_unpin,
	.get_sg_table = radeon_gem_prime_get_sg_table,
	.vmap = drm_gem_tपंचांग_vmap,
	.vunmap = drm_gem_tपंचांग_vunmap,
पूर्ण;

/*
 * GEM ioctls.
 */
पूर्णांक radeon_gem_info_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *filp)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_radeon_gem_info *args = data;
	काष्ठा tपंचांग_resource_manager *man;

	man = tपंचांग_manager_type(&rdev->mman.bdev, TTM_PL_VRAM);

	args->vram_size = (u64)man->size << PAGE_SHIFT;
	args->vram_visible = rdev->mc.visible_vram_size;
	args->vram_visible -= rdev->vram_pin_size;
	args->gart_size = rdev->mc.gtt_size;
	args->gart_size -= rdev->gart_pin_size;

	वापस 0;
पूर्ण

पूर्णांक radeon_gem_pपढ़ो_ioctl(काष्ठा drm_device *dev, व्योम *data,
			   काष्ठा drm_file *filp)
अणु
	/* TODO: implement */
	DRM_ERROR("unimplemented %s\n", __func__);
	वापस -ENOSYS;
पूर्ण

पूर्णांक radeon_gem_pग_लिखो_ioctl(काष्ठा drm_device *dev, व्योम *data,
			    काष्ठा drm_file *filp)
अणु
	/* TODO: implement */
	DRM_ERROR("unimplemented %s\n", __func__);
	वापस -ENOSYS;
पूर्ण

पूर्णांक radeon_gem_create_ioctl(काष्ठा drm_device *dev, व्योम *data,
			    काष्ठा drm_file *filp)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_radeon_gem_create *args = data;
	काष्ठा drm_gem_object *gobj;
	uपूर्णांक32_t handle;
	पूर्णांक r;

	करोwn_पढ़ो(&rdev->exclusive_lock);
	/* create a gem object to contain this object in */
	args->size = roundup(args->size, PAGE_SIZE);
	r = radeon_gem_object_create(rdev, args->size, args->alignment,
				     args->initial_करोमुख्य, args->flags,
				     false, &gobj);
	अगर (r) अणु
		up_पढ़ो(&rdev->exclusive_lock);
		r = radeon_gem_handle_lockup(rdev, r);
		वापस r;
	पूर्ण
	r = drm_gem_handle_create(filp, gobj, &handle);
	/* drop reference from allocate - handle holds it now */
	drm_gem_object_put(gobj);
	अगर (r) अणु
		up_पढ़ो(&rdev->exclusive_lock);
		r = radeon_gem_handle_lockup(rdev, r);
		वापस r;
	पूर्ण
	args->handle = handle;
	up_पढ़ो(&rdev->exclusive_lock);
	वापस 0;
पूर्ण

पूर्णांक radeon_gem_userptr_ioctl(काष्ठा drm_device *dev, व्योम *data,
			     काष्ठा drm_file *filp)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु true, false पूर्ण;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_radeon_gem_userptr *args = data;
	काष्ठा drm_gem_object *gobj;
	काष्ठा radeon_bo *bo;
	uपूर्णांक32_t handle;
	पूर्णांक r;

	args->addr = untagged_addr(args->addr);

	अगर (offset_in_page(args->addr | args->size))
		वापस -EINVAL;

	/* reject unknown flag values */
	अगर (args->flags & ~(RADEON_GEM_USERPTR_READONLY |
	    RADEON_GEM_USERPTR_ANONONLY | RADEON_GEM_USERPTR_VALIDATE |
	    RADEON_GEM_USERPTR_REGISTER))
		वापस -EINVAL;

	अगर (args->flags & RADEON_GEM_USERPTR_READONLY) अणु
		/* पढ़ोonly pages not tested on older hardware */
		अगर (rdev->family < CHIP_R600)
			वापस -EINVAL;

	पूर्ण अन्यथा अगर (!(args->flags & RADEON_GEM_USERPTR_ANONONLY) ||
		   !(args->flags & RADEON_GEM_USERPTR_REGISTER)) अणु

		/* अगर we want to ग_लिखो to it we must require anonymous
		   memory and install a MMU notअगरier */
		वापस -EACCES;
	पूर्ण

	करोwn_पढ़ो(&rdev->exclusive_lock);

	/* create a gem object to contain this object in */
	r = radeon_gem_object_create(rdev, args->size, 0,
				     RADEON_GEM_DOMAIN_CPU, 0,
				     false, &gobj);
	अगर (r)
		जाओ handle_lockup;

	bo = gem_to_radeon_bo(gobj);
	r = radeon_tपंचांग_tt_set_userptr(rdev, bo->tbo.tपंचांग, args->addr, args->flags);
	अगर (r)
		जाओ release_object;

	अगर (args->flags & RADEON_GEM_USERPTR_REGISTER) अणु
		r = radeon_mn_रेजिस्टर(bo, args->addr);
		अगर (r)
			जाओ release_object;
	पूर्ण

	अगर (args->flags & RADEON_GEM_USERPTR_VALIDATE) अणु
		mmap_पढ़ो_lock(current->mm);
		r = radeon_bo_reserve(bo, true);
		अगर (r) अणु
			mmap_पढ़ो_unlock(current->mm);
			जाओ release_object;
		पूर्ण

		radeon_tपंचांग_placement_from_करोमुख्य(bo, RADEON_GEM_DOMAIN_GTT);
		r = tपंचांग_bo_validate(&bo->tbo, &bo->placement, &ctx);
		radeon_bo_unreserve(bo);
		mmap_पढ़ो_unlock(current->mm);
		अगर (r)
			जाओ release_object;
	पूर्ण

	r = drm_gem_handle_create(filp, gobj, &handle);
	/* drop reference from allocate - handle holds it now */
	drm_gem_object_put(gobj);
	अगर (r)
		जाओ handle_lockup;

	args->handle = handle;
	up_पढ़ो(&rdev->exclusive_lock);
	वापस 0;

release_object:
	drm_gem_object_put(gobj);

handle_lockup:
	up_पढ़ो(&rdev->exclusive_lock);
	r = radeon_gem_handle_lockup(rdev, r);

	वापस r;
पूर्ण

पूर्णांक radeon_gem_set_करोमुख्य_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *filp)
अणु
	/* transition the BO to a करोमुख्य -
	 * just validate the BO पूर्णांकo a certain करोमुख्य */
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_radeon_gem_set_करोमुख्य *args = data;
	काष्ठा drm_gem_object *gobj;
	काष्ठा radeon_bo *robj;
	पूर्णांक r;

	/* क्रम now अगर someone requests करोमुख्य CPU -
	 * just make sure the buffer is finished with */
	करोwn_पढ़ो(&rdev->exclusive_lock);

	/* just करो a BO रुको क्रम now */
	gobj = drm_gem_object_lookup(filp, args->handle);
	अगर (gobj == शून्य) अणु
		up_पढ़ो(&rdev->exclusive_lock);
		वापस -ENOENT;
	पूर्ण
	robj = gem_to_radeon_bo(gobj);

	r = radeon_gem_set_करोमुख्य(gobj, args->पढ़ो_करोमुख्यs, args->ग_लिखो_करोमुख्य);

	drm_gem_object_put(gobj);
	up_पढ़ो(&rdev->exclusive_lock);
	r = radeon_gem_handle_lockup(robj->rdev, r);
	वापस r;
पूर्ण

पूर्णांक radeon_mode_dumb_mmap(काष्ठा drm_file *filp,
			  काष्ठा drm_device *dev,
			  uपूर्णांक32_t handle, uपूर्णांक64_t *offset_p)
अणु
	काष्ठा drm_gem_object *gobj;
	काष्ठा radeon_bo *robj;

	gobj = drm_gem_object_lookup(filp, handle);
	अगर (gobj == शून्य) अणु
		वापस -ENOENT;
	पूर्ण
	robj = gem_to_radeon_bo(gobj);
	अगर (radeon_tपंचांग_tt_has_userptr(robj->rdev, robj->tbo.tपंचांग)) अणु
		drm_gem_object_put(gobj);
		वापस -EPERM;
	पूर्ण
	*offset_p = radeon_bo_mmap_offset(robj);
	drm_gem_object_put(gobj);
	वापस 0;
पूर्ण

पूर्णांक radeon_gem_mmap_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *filp)
अणु
	काष्ठा drm_radeon_gem_mmap *args = data;

	वापस radeon_mode_dumb_mmap(filp, dev, args->handle, &args->addr_ptr);
पूर्ण

पूर्णांक radeon_gem_busy_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *filp)
अणु
	काष्ठा drm_radeon_gem_busy *args = data;
	काष्ठा drm_gem_object *gobj;
	काष्ठा radeon_bo *robj;
	पूर्णांक r;
	uपूर्णांक32_t cur_placement = 0;

	gobj = drm_gem_object_lookup(filp, args->handle);
	अगर (gobj == शून्य) अणु
		वापस -ENOENT;
	पूर्ण
	robj = gem_to_radeon_bo(gobj);

	r = dma_resv_test_संकेतed_rcu(robj->tbo.base.resv, true);
	अगर (r == 0)
		r = -EBUSY;
	अन्यथा
		r = 0;

	cur_placement = READ_ONCE(robj->tbo.mem.mem_type);
	args->करोमुख्य = radeon_mem_type_to_करोमुख्य(cur_placement);
	drm_gem_object_put(gobj);
	वापस r;
पूर्ण

पूर्णांक radeon_gem_रुको_idle_ioctl(काष्ठा drm_device *dev, व्योम *data,
			      काष्ठा drm_file *filp)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_radeon_gem_रुको_idle *args = data;
	काष्ठा drm_gem_object *gobj;
	काष्ठा radeon_bo *robj;
	पूर्णांक r = 0;
	uपूर्णांक32_t cur_placement = 0;
	दीर्घ ret;

	gobj = drm_gem_object_lookup(filp, args->handle);
	अगर (gobj == शून्य) अणु
		वापस -ENOENT;
	पूर्ण
	robj = gem_to_radeon_bo(gobj);

	ret = dma_resv_रुको_समयout_rcu(robj->tbo.base.resv, true, true, 30 * HZ);
	अगर (ret == 0)
		r = -EBUSY;
	अन्यथा अगर (ret < 0)
		r = ret;

	/* Flush HDP cache via MMIO अगर necessary */
	cur_placement = READ_ONCE(robj->tbo.mem.mem_type);
	अगर (rdev->asic->mmio_hdp_flush &&
	    radeon_mem_type_to_करोमुख्य(cur_placement) == RADEON_GEM_DOMAIN_VRAM)
		robj->rdev->asic->mmio_hdp_flush(rdev);
	drm_gem_object_put(gobj);
	r = radeon_gem_handle_lockup(rdev, r);
	वापस r;
पूर्ण

पूर्णांक radeon_gem_set_tiling_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *filp)
अणु
	काष्ठा drm_radeon_gem_set_tiling *args = data;
	काष्ठा drm_gem_object *gobj;
	काष्ठा radeon_bo *robj;
	पूर्णांक r = 0;

	DRM_DEBUG("%d \n", args->handle);
	gobj = drm_gem_object_lookup(filp, args->handle);
	अगर (gobj == शून्य)
		वापस -ENOENT;
	robj = gem_to_radeon_bo(gobj);
	r = radeon_bo_set_tiling_flags(robj, args->tiling_flags, args->pitch);
	drm_gem_object_put(gobj);
	वापस r;
पूर्ण

पूर्णांक radeon_gem_get_tiling_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *filp)
अणु
	काष्ठा drm_radeon_gem_get_tiling *args = data;
	काष्ठा drm_gem_object *gobj;
	काष्ठा radeon_bo *rbo;
	पूर्णांक r = 0;

	DRM_DEBUG("\n");
	gobj = drm_gem_object_lookup(filp, args->handle);
	अगर (gobj == शून्य)
		वापस -ENOENT;
	rbo = gem_to_radeon_bo(gobj);
	r = radeon_bo_reserve(rbo, false);
	अगर (unlikely(r != 0))
		जाओ out;
	radeon_bo_get_tiling_flags(rbo, &args->tiling_flags, &args->pitch);
	radeon_bo_unreserve(rbo);
out:
	drm_gem_object_put(gobj);
	वापस r;
पूर्ण

/**
 * radeon_gem_va_update_vm -update the bo_va in its VM
 *
 * @rdev: radeon_device poपूर्णांकer
 * @bo_va: bo_va to update
 *
 * Update the bo_va directly after setting it's address. Errors are not
 * vital here, so they are not reported back to userspace.
 */
अटल व्योम radeon_gem_va_update_vm(काष्ठा radeon_device *rdev,
				    काष्ठा radeon_bo_va *bo_va)
अणु
	काष्ठा tपंचांग_validate_buffer tv, *entry;
	काष्ठा radeon_bo_list *vm_bos;
	काष्ठा ww_acquire_ctx ticket;
	काष्ठा list_head list;
	अचिन्हित करोमुख्य;
	पूर्णांक r;

	INIT_LIST_HEAD(&list);

	tv.bo = &bo_va->bo->tbo;
	tv.num_shared = 1;
	list_add(&tv.head, &list);

	vm_bos = radeon_vm_get_bos(rdev, bo_va->vm, &list);
	अगर (!vm_bos)
		वापस;

	r = tपंचांग_eu_reserve_buffers(&ticket, &list, true, शून्य);
	अगर (r)
		जाओ error_मुक्त;

	list_क्रम_each_entry(entry, &list, head) अणु
		करोमुख्य = radeon_mem_type_to_करोमुख्य(entry->bo->mem.mem_type);
		/* अगर anything is swapped out करोn't swap it in here,
		   just पात and रुको क्रम the next CS */
		अगर (करोमुख्य == RADEON_GEM_DOMAIN_CPU)
			जाओ error_unreserve;
	पूर्ण

	mutex_lock(&bo_va->vm->mutex);
	r = radeon_vm_clear_मुक्तd(rdev, bo_va->vm);
	अगर (r)
		जाओ error_unlock;

	अगर (bo_va->it.start)
		r = radeon_vm_bo_update(rdev, bo_va, &bo_va->bo->tbo.mem);

error_unlock:
	mutex_unlock(&bo_va->vm->mutex);

error_unreserve:
	tपंचांग_eu_backoff_reservation(&ticket, &list);

error_मुक्त:
	kvमुक्त(vm_bos);

	अगर (r && r != -ERESTARTSYS)
		DRM_ERROR("Couldn't update BO_VA (%d)\n", r);
पूर्ण

पूर्णांक radeon_gem_va_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *filp)
अणु
	काष्ठा drm_radeon_gem_va *args = data;
	काष्ठा drm_gem_object *gobj;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_fpriv *fpriv = filp->driver_priv;
	काष्ठा radeon_bo *rbo;
	काष्ठा radeon_bo_va *bo_va;
	u32 invalid_flags;
	पूर्णांक r = 0;

	अगर (!rdev->vm_manager.enabled) अणु
		args->operation = RADEON_VA_RESULT_ERROR;
		वापस -ENOTTY;
	पूर्ण

	/* !! DONT REMOVE !!
	 * We करोn't support vm_id yet, to be sure we don't have have broken
	 * userspace, reject anyone trying to use non 0 value thus moving
	 * क्रमward we can use those fields without अवरोधing existant userspace
	 */
	अगर (args->vm_id) अणु
		args->operation = RADEON_VA_RESULT_ERROR;
		वापस -EINVAL;
	पूर्ण

	अगर (args->offset < RADEON_VA_RESERVED_SIZE) अणु
		dev_err(dev->dev,
			"offset 0x%lX is in reserved area 0x%X\n",
			(अचिन्हित दीर्घ)args->offset,
			RADEON_VA_RESERVED_SIZE);
		args->operation = RADEON_VA_RESULT_ERROR;
		वापस -EINVAL;
	पूर्ण

	/* करोn't हटाओ, we need to enक्रमce userspace to set the snooped flag
	 * otherwise we will endup with broken userspace and we won't be able
	 * to enable this feature without adding new पूर्णांकerface
	 */
	invalid_flags = RADEON_VM_PAGE_VALID | RADEON_VM_PAGE_SYSTEM;
	अगर ((args->flags & invalid_flags)) अणु
		dev_err(dev->dev, "invalid flags 0x%08X vs 0x%08X\n",
			args->flags, invalid_flags);
		args->operation = RADEON_VA_RESULT_ERROR;
		वापस -EINVAL;
	पूर्ण

	चयन (args->operation) अणु
	हाल RADEON_VA_MAP:
	हाल RADEON_VA_UNMAP:
		अवरोध;
	शेष:
		dev_err(dev->dev, "unsupported operation %d\n",
			args->operation);
		args->operation = RADEON_VA_RESULT_ERROR;
		वापस -EINVAL;
	पूर्ण

	gobj = drm_gem_object_lookup(filp, args->handle);
	अगर (gobj == शून्य) अणु
		args->operation = RADEON_VA_RESULT_ERROR;
		वापस -ENOENT;
	पूर्ण
	rbo = gem_to_radeon_bo(gobj);
	r = radeon_bo_reserve(rbo, false);
	अगर (r) अणु
		args->operation = RADEON_VA_RESULT_ERROR;
		drm_gem_object_put(gobj);
		वापस r;
	पूर्ण
	bo_va = radeon_vm_bo_find(&fpriv->vm, rbo);
	अगर (!bo_va) अणु
		args->operation = RADEON_VA_RESULT_ERROR;
		radeon_bo_unreserve(rbo);
		drm_gem_object_put(gobj);
		वापस -ENOENT;
	पूर्ण

	चयन (args->operation) अणु
	हाल RADEON_VA_MAP:
		अगर (bo_va->it.start) अणु
			args->operation = RADEON_VA_RESULT_VA_EXIST;
			args->offset = bo_va->it.start * RADEON_GPU_PAGE_SIZE;
			radeon_bo_unreserve(rbo);
			जाओ out;
		पूर्ण
		r = radeon_vm_bo_set_addr(rdev, bo_va, args->offset, args->flags);
		अवरोध;
	हाल RADEON_VA_UNMAP:
		r = radeon_vm_bo_set_addr(rdev, bo_va, 0, 0);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (!r)
		radeon_gem_va_update_vm(rdev, bo_va);
	args->operation = RADEON_VA_RESULT_OK;
	अगर (r) अणु
		args->operation = RADEON_VA_RESULT_ERROR;
	पूर्ण
out:
	drm_gem_object_put(gobj);
	वापस r;
पूर्ण

पूर्णांक radeon_gem_op_ioctl(काष्ठा drm_device *dev, व्योम *data,
			काष्ठा drm_file *filp)
अणु
	काष्ठा drm_radeon_gem_op *args = data;
	काष्ठा drm_gem_object *gobj;
	काष्ठा radeon_bo *robj;
	पूर्णांक r;

	gobj = drm_gem_object_lookup(filp, args->handle);
	अगर (gobj == शून्य) अणु
		वापस -ENOENT;
	पूर्ण
	robj = gem_to_radeon_bo(gobj);

	r = -EPERM;
	अगर (radeon_tपंचांग_tt_has_userptr(robj->rdev, robj->tbo.tपंचांग))
		जाओ out;

	r = radeon_bo_reserve(robj, false);
	अगर (unlikely(r))
		जाओ out;

	चयन (args->op) अणु
	हाल RADEON_GEM_OP_GET_INITIAL_DOMAIN:
		args->value = robj->initial_करोमुख्य;
		अवरोध;
	हाल RADEON_GEM_OP_SET_INITIAL_DOMAIN:
		robj->initial_करोमुख्य = args->value & (RADEON_GEM_DOMAIN_VRAM |
						      RADEON_GEM_DOMAIN_GTT |
						      RADEON_GEM_DOMAIN_CPU);
		अवरोध;
	शेष:
		r = -EINVAL;
	पूर्ण

	radeon_bo_unreserve(robj);
out:
	drm_gem_object_put(gobj);
	वापस r;
पूर्ण

पूर्णांक radeon_mode_dumb_create(काष्ठा drm_file *file_priv,
			    काष्ठा drm_device *dev,
			    काष्ठा drm_mode_create_dumb *args)
अणु
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा drm_gem_object *gobj;
	uपूर्णांक32_t handle;
	पूर्णांक r;

	args->pitch = radeon_align_pitch(rdev, args->width,
					 DIV_ROUND_UP(args->bpp, 8), 0);
	args->size = args->pitch * args->height;
	args->size = ALIGN(args->size, PAGE_SIZE);

	r = radeon_gem_object_create(rdev, args->size, 0,
				     RADEON_GEM_DOMAIN_VRAM, 0,
				     false, &gobj);
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
अटल पूर्णांक radeon_debugfs_gem_info_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा radeon_device *rdev = (काष्ठा radeon_device *)m->निजी;
	काष्ठा radeon_bo *rbo;
	अचिन्हित i = 0;

	mutex_lock(&rdev->gem.mutex);
	list_क्रम_each_entry(rbo, &rdev->gem.objects, list) अणु
		अचिन्हित करोमुख्य;
		स्थिर अक्षर *placement;

		करोमुख्य = radeon_mem_type_to_करोमुख्य(rbo->tbo.mem.mem_type);
		चयन (करोमुख्य) अणु
		हाल RADEON_GEM_DOMAIN_VRAM:
			placement = "VRAM";
			अवरोध;
		हाल RADEON_GEM_DOMAIN_GTT:
			placement = " GTT";
			अवरोध;
		हाल RADEON_GEM_DOMAIN_CPU:
		शेष:
			placement = " CPU";
			अवरोध;
		पूर्ण
		seq_म_लिखो(m, "bo[0x%08x] %8ldkB %8ldMB %s pid %8ld\n",
			   i, radeon_bo_size(rbo) >> 10, radeon_bo_size(rbo) >> 20,
			   placement, (अचिन्हित दीर्घ)rbo->pid);
		i++;
	पूर्ण
	mutex_unlock(&rdev->gem.mutex);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(radeon_debugfs_gem_info);
#पूर्ण_अगर

व्योम radeon_gem_debugfs_init(काष्ठा radeon_device *rdev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा dentry *root = rdev->ddev->primary->debugfs_root;

	debugfs_create_file("radeon_gem_info", 0444, root, rdev,
			    &radeon_debugfs_gem_info_fops);

#पूर्ण_अगर
पूर्ण
