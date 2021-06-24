<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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
 * based on nouveau_prime.c
 *
 * Authors: Alex Deucher
 */

/**
 * DOC: PRIME Buffer Sharing
 *
 * The following callback implementations are used क्रम :ref:`sharing GEM buffer
 * objects between dअगरferent devices via PRIME <prime_buffer_sharing>`.
 */

#समावेश "amdgpu.h"
#समावेश "amdgpu_display.h"
#समावेश "amdgpu_gem.h"
#समावेश "amdgpu_dma_buf.h"
#समावेश "amdgpu_xgmi.h"
#समावेश <drm/amdgpu_drm.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/dma-fence-array.h>
#समावेश <linux/pci-p2pdma.h>
#समावेश <linux/pm_runसमय.स>

/**
 * amdgpu_gem_prime_mmap - &drm_driver.gem_prime_mmap implementation
 * @obj: GEM BO
 * @vma: Virtual memory area
 *
 * Sets up a userspace mapping of the BO's memory in the given
 * भव memory area.
 *
 * Returns:
 * 0 on success or a negative error code on failure.
 */
पूर्णांक amdgpu_gem_prime_mmap(काष्ठा drm_gem_object *obj,
			  काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा amdgpu_bo *bo = gem_to_amdgpu_bo(obj);
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);
	अचिन्हित asize = amdgpu_bo_size(bo);
	पूर्णांक ret;

	अगर (!vma->vm_file)
		वापस -ENODEV;

	अगर (adev == शून्य)
		वापस -ENODEV;

	/* Check क्रम valid size. */
	अगर (asize < vma->vm_end - vma->vm_start)
		वापस -EINVAL;

	अगर (amdgpu_tपंचांग_tt_get_usermm(bo->tbo.tपंचांग) ||
	    (bo->flags & AMDGPU_GEM_CREATE_NO_CPU_ACCESS)) अणु
		वापस -EPERM;
	पूर्ण
	vma->vm_pgoff += amdgpu_bo_mmap_offset(bo) >> PAGE_SHIFT;

	/* prime mmap करोes not need to check access, so allow here */
	ret = drm_vma_node_allow(&obj->vma_node, vma->vm_file->निजी_data);
	अगर (ret)
		वापस ret;

	ret = tपंचांग_bo_mmap(vma->vm_file, vma, &adev->mman.bdev);
	drm_vma_node_revoke(&obj->vma_node, vma->vm_file->निजी_data);

	वापस ret;
पूर्ण

अटल पूर्णांक
__dma_resv_make_exclusive(काष्ठा dma_resv *obj)
अणु
	काष्ठा dma_fence **fences;
	अचिन्हित पूर्णांक count;
	पूर्णांक r;

	अगर (!dma_resv_get_list(obj)) /* no shared fences to convert */
		वापस 0;

	r = dma_resv_get_fences_rcu(obj, शून्य, &count, &fences);
	अगर (r)
		वापस r;

	अगर (count == 0) अणु
		/* Now that was unexpected. */
	पूर्ण अन्यथा अगर (count == 1) अणु
		dma_resv_add_excl_fence(obj, fences[0]);
		dma_fence_put(fences[0]);
		kमुक्त(fences);
	पूर्ण अन्यथा अणु
		काष्ठा dma_fence_array *array;

		array = dma_fence_array_create(count, fences,
					       dma_fence_context_alloc(1), 0,
					       false);
		अगर (!array)
			जाओ err_fences_put;

		dma_resv_add_excl_fence(obj, &array->base);
		dma_fence_put(&array->base);
	पूर्ण

	वापस 0;

err_fences_put:
	जबतक (count--)
		dma_fence_put(fences[count]);
	kमुक्त(fences);
	वापस -ENOMEM;
पूर्ण

/**
 * amdgpu_dma_buf_attach - &dma_buf_ops.attach implementation
 *
 * @dmabuf: DMA-buf where we attach to
 * @attach: attachment to add
 *
 * Add the attachment as user to the exported DMA-buf.
 */
अटल पूर्णांक amdgpu_dma_buf_attach(काष्ठा dma_buf *dmabuf,
				 काष्ठा dma_buf_attachment *attach)
अणु
	काष्ठा drm_gem_object *obj = dmabuf->priv;
	काष्ठा amdgpu_bo *bo = gem_to_amdgpu_bo(obj);
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);
	पूर्णांक r;

	अगर (pci_p2pdma_distance_many(adev->pdev, &attach->dev, 1, true) < 0)
		attach->peer2peer = false;

	अगर (attach->dev->driver == adev->dev->driver)
		वापस 0;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0)
		जाओ out;

	r = amdgpu_bo_reserve(bo, false);
	अगर (unlikely(r != 0))
		जाओ out;

	/*
	 * We only create shared fences क्रम पूर्णांकernal use, but importers
	 * of the dmabuf rely on exclusive fences क्रम implicitly
	 * tracking ग_लिखो hazards. As any of the current fences may
	 * correspond to a ग_लिखो, we need to convert all existing
	 * fences on the reservation object पूर्णांकo a single exclusive
	 * fence.
	 */
	r = __dma_resv_make_exclusive(bo->tbo.base.resv);
	अगर (r)
		जाओ out;

	bo->prime_shared_count++;
	amdgpu_bo_unreserve(bo);
	वापस 0;

out:
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
	वापस r;
पूर्ण

/**
 * amdgpu_dma_buf_detach - &dma_buf_ops.detach implementation
 *
 * @dmabuf: DMA-buf where we हटाओ the attachment from
 * @attach: the attachment to हटाओ
 *
 * Called when an attachment is हटाओd from the DMA-buf.
 */
अटल व्योम amdgpu_dma_buf_detach(काष्ठा dma_buf *dmabuf,
				  काष्ठा dma_buf_attachment *attach)
अणु
	काष्ठा drm_gem_object *obj = dmabuf->priv;
	काष्ठा amdgpu_bo *bo = gem_to_amdgpu_bo(obj);
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);

	अगर (attach->dev->driver != adev->dev->driver && bo->prime_shared_count)
		bo->prime_shared_count--;

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
पूर्ण

/**
 * amdgpu_dma_buf_pin - &dma_buf_ops.pin implementation
 *
 * @attach: attachment to pin करोwn
 *
 * Pin the BO which is backing the DMA-buf so that it can't move any more.
 */
अटल पूर्णांक amdgpu_dma_buf_pin(काष्ठा dma_buf_attachment *attach)
अणु
	काष्ठा drm_gem_object *obj = attach->dmabuf->priv;
	काष्ठा amdgpu_bo *bo = gem_to_amdgpu_bo(obj);

	/* pin buffer पूर्णांकo GTT */
	वापस amdgpu_bo_pin(bo, AMDGPU_GEM_DOMAIN_GTT);
पूर्ण

/**
 * amdgpu_dma_buf_unpin - &dma_buf_ops.unpin implementation
 *
 * @attach: attachment to unpin
 *
 * Unpin a previously pinned BO to make it movable again.
 */
अटल व्योम amdgpu_dma_buf_unpin(काष्ठा dma_buf_attachment *attach)
अणु
	काष्ठा drm_gem_object *obj = attach->dmabuf->priv;
	काष्ठा amdgpu_bo *bo = gem_to_amdgpu_bo(obj);

	amdgpu_bo_unpin(bo);
पूर्ण

/**
 * amdgpu_dma_buf_map - &dma_buf_ops.map_dma_buf implementation
 * @attach: DMA-buf attachment
 * @dir: DMA direction
 *
 * Makes sure that the shared DMA buffer can be accessed by the target device.
 * For now, simply pins it to the GTT करोमुख्य, where it should be accessible by
 * all DMA devices.
 *
 * Returns:
 * sg_table filled with the DMA addresses to use or ERR_PRT with negative error
 * code.
 */
अटल काष्ठा sg_table *amdgpu_dma_buf_map(काष्ठा dma_buf_attachment *attach,
					   क्रमागत dma_data_direction dir)
अणु
	काष्ठा dma_buf *dma_buf = attach->dmabuf;
	काष्ठा drm_gem_object *obj = dma_buf->priv;
	काष्ठा amdgpu_bo *bo = gem_to_amdgpu_bo(obj);
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);
	काष्ठा sg_table *sgt;
	दीर्घ r;

	अगर (!bo->tbo.pin_count) अणु
		/* move buffer पूर्णांकo GTT or VRAM */
		काष्ठा tपंचांग_operation_ctx ctx = अणु false, false पूर्ण;
		अचिन्हित करोमुख्यs = AMDGPU_GEM_DOMAIN_GTT;

		अगर (bo->preferred_करोमुख्यs & AMDGPU_GEM_DOMAIN_VRAM &&
		    attach->peer2peer) अणु
			bo->flags |= AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED;
			करोमुख्यs |= AMDGPU_GEM_DOMAIN_VRAM;
		पूर्ण
		amdgpu_bo_placement_from_करोमुख्य(bo, करोमुख्यs);
		r = tपंचांग_bo_validate(&bo->tbo, &bo->placement, &ctx);
		अगर (r)
			वापस ERR_PTR(r);

	पूर्ण अन्यथा अगर (!(amdgpu_mem_type_to_करोमुख्य(bo->tbo.mem.mem_type) &
		     AMDGPU_GEM_DOMAIN_GTT)) अणु
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	चयन (bo->tbo.mem.mem_type) अणु
	हाल TTM_PL_TT:
		sgt = drm_prime_pages_to_sg(obj->dev,
					    bo->tbo.tपंचांग->pages,
					    bo->tbo.tपंचांग->num_pages);
		अगर (IS_ERR(sgt))
			वापस sgt;

		अगर (dma_map_sgtable(attach->dev, sgt, dir,
				    DMA_ATTR_SKIP_CPU_SYNC))
			जाओ error_मुक्त;
		अवरोध;

	हाल TTM_PL_VRAM:
		r = amdgpu_vram_mgr_alloc_sgt(adev, &bo->tbo.mem, 0,
				bo->tbo.base.size, attach->dev, dir, &sgt);
		अगर (r)
			वापस ERR_PTR(r);
		अवरोध;
	शेष:
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस sgt;

error_मुक्त:
	sg_मुक्त_table(sgt);
	kमुक्त(sgt);
	वापस ERR_PTR(-EBUSY);
पूर्ण

/**
 * amdgpu_dma_buf_unmap - &dma_buf_ops.unmap_dma_buf implementation
 * @attach: DMA-buf attachment
 * @sgt: sg_table to unmap
 * @dir: DMA direction
 *
 * This is called when a shared DMA buffer no दीर्घer needs to be accessible by
 * another device. For now, simply unpins the buffer from GTT.
 */
अटल व्योम amdgpu_dma_buf_unmap(काष्ठा dma_buf_attachment *attach,
				 काष्ठा sg_table *sgt,
				 क्रमागत dma_data_direction dir)
अणु
	अगर (sgt->sgl->page_link) अणु
		dma_unmap_sgtable(attach->dev, sgt, dir, 0);
		sg_मुक्त_table(sgt);
		kमुक्त(sgt);
	पूर्ण अन्यथा अणु
		amdgpu_vram_mgr_मुक्त_sgt(attach->dev, dir, sgt);
	पूर्ण
पूर्ण

/**
 * amdgpu_dma_buf_begin_cpu_access - &dma_buf_ops.begin_cpu_access implementation
 * @dma_buf: Shared DMA buffer
 * @direction: Direction of DMA transfer
 *
 * This is called beक्रमe CPU access to the shared DMA buffer's memory. If it's
 * a पढ़ो access, the buffer is moved to the GTT करोमुख्य अगर possible, क्रम optimal
 * CPU पढ़ो perक्रमmance.
 *
 * Returns:
 * 0 on success or a negative error code on failure.
 */
अटल पूर्णांक amdgpu_dma_buf_begin_cpu_access(काष्ठा dma_buf *dma_buf,
					   क्रमागत dma_data_direction direction)
अणु
	काष्ठा amdgpu_bo *bo = gem_to_amdgpu_bo(dma_buf->priv);
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);
	काष्ठा tपंचांग_operation_ctx ctx = अणु true, false पूर्ण;
	u32 करोमुख्य = amdgpu_display_supported_करोमुख्यs(adev, bo->flags);
	पूर्णांक ret;
	bool पढ़ोs = (direction == DMA_BIसूचीECTIONAL ||
		      direction == DMA_FROM_DEVICE);

	अगर (!पढ़ोs || !(करोमुख्य & AMDGPU_GEM_DOMAIN_GTT))
		वापस 0;

	/* move to gtt */
	ret = amdgpu_bo_reserve(bo, false);
	अगर (unlikely(ret != 0))
		वापस ret;

	अगर (!bo->tbo.pin_count &&
	    (bo->allowed_करोमुख्यs & AMDGPU_GEM_DOMAIN_GTT)) अणु
		amdgpu_bo_placement_from_करोमुख्य(bo, AMDGPU_GEM_DOMAIN_GTT);
		ret = tपंचांग_bo_validate(&bo->tbo, &bo->placement, &ctx);
	पूर्ण

	amdgpu_bo_unreserve(bo);
	वापस ret;
पूर्ण

स्थिर काष्ठा dma_buf_ops amdgpu_dmabuf_ops = अणु
	.attach = amdgpu_dma_buf_attach,
	.detach = amdgpu_dma_buf_detach,
	.pin = amdgpu_dma_buf_pin,
	.unpin = amdgpu_dma_buf_unpin,
	.map_dma_buf = amdgpu_dma_buf_map,
	.unmap_dma_buf = amdgpu_dma_buf_unmap,
	.release = drm_gem_dmabuf_release,
	.begin_cpu_access = amdgpu_dma_buf_begin_cpu_access,
	.mmap = drm_gem_dmabuf_mmap,
	.vmap = drm_gem_dmabuf_vmap,
	.vunmap = drm_gem_dmabuf_vunmap,
पूर्ण;

/**
 * amdgpu_gem_prime_export - &drm_driver.gem_prime_export implementation
 * @gobj: GEM BO
 * @flags: Flags such as DRM_CLOEXEC and DRM_RDWR.
 *
 * The मुख्य work is करोne by the &drm_gem_prime_export helper.
 *
 * Returns:
 * Shared DMA buffer representing the GEM BO from the given device.
 */
काष्ठा dma_buf *amdgpu_gem_prime_export(काष्ठा drm_gem_object *gobj,
					पूर्णांक flags)
अणु
	काष्ठा amdgpu_bo *bo = gem_to_amdgpu_bo(gobj);
	काष्ठा dma_buf *buf;

	अगर (amdgpu_tपंचांग_tt_get_usermm(bo->tbo.tपंचांग) ||
	    bo->flags & AMDGPU_GEM_CREATE_VM_ALWAYS_VALID)
		वापस ERR_PTR(-EPERM);

	buf = drm_gem_prime_export(gobj, flags);
	अगर (!IS_ERR(buf))
		buf->ops = &amdgpu_dmabuf_ops;

	वापस buf;
पूर्ण

/**
 * amdgpu_dma_buf_create_obj - create BO क्रम DMA-buf import
 *
 * @dev: DRM device
 * @dma_buf: DMA-buf
 *
 * Creates an empty SG BO क्रम DMA-buf import.
 *
 * Returns:
 * A new GEM BO of the given DRM device, representing the memory
 * described by the given DMA-buf attachment and scatter/gather table.
 */
अटल काष्ठा drm_gem_object *
amdgpu_dma_buf_create_obj(काष्ठा drm_device *dev, काष्ठा dma_buf *dma_buf)
अणु
	काष्ठा dma_resv *resv = dma_buf->resv;
	काष्ठा amdgpu_device *adev = drm_to_adev(dev);
	काष्ठा drm_gem_object *gobj;
	काष्ठा amdgpu_bo *bo;
	uपूर्णांक64_t flags = 0;
	पूर्णांक ret;

	dma_resv_lock(resv, शून्य);

	अगर (dma_buf->ops == &amdgpu_dmabuf_ops) अणु
		काष्ठा amdgpu_bo *other = gem_to_amdgpu_bo(dma_buf->priv);

		flags |= other->flags & AMDGPU_GEM_CREATE_CPU_GTT_USWC;
	पूर्ण

	ret = amdgpu_gem_object_create(adev, dma_buf->size, PAGE_SIZE,
				       AMDGPU_GEM_DOMAIN_CPU, flags,
				       tपंचांग_bo_type_sg, resv, &gobj);
	अगर (ret)
		जाओ error;

	bo = gem_to_amdgpu_bo(gobj);
	bo->allowed_करोमुख्यs = AMDGPU_GEM_DOMAIN_GTT;
	bo->preferred_करोमुख्यs = AMDGPU_GEM_DOMAIN_GTT;
	अगर (dma_buf->ops != &amdgpu_dmabuf_ops)
		bo->prime_shared_count = 1;

	dma_resv_unlock(resv);
	वापस gobj;

error:
	dma_resv_unlock(resv);
	वापस ERR_PTR(ret);
पूर्ण

/**
 * amdgpu_dma_buf_move_notअगरy - &attach.move_notअगरy implementation
 *
 * @attach: the DMA-buf attachment
 *
 * Invalidate the DMA-buf attachment, making sure that the we re-create the
 * mapping beक्रमe the next use.
 */
अटल व्योम
amdgpu_dma_buf_move_notअगरy(काष्ठा dma_buf_attachment *attach)
अणु
	काष्ठा drm_gem_object *obj = attach->importer_priv;
	काष्ठा ww_acquire_ctx *ticket = dma_resv_locking_ctx(obj->resv);
	काष्ठा amdgpu_bo *bo = gem_to_amdgpu_bo(obj);
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);
	काष्ठा tपंचांग_operation_ctx ctx = अणु false, false पूर्ण;
	काष्ठा tपंचांग_placement placement = अणुपूर्ण;
	काष्ठा amdgpu_vm_bo_base *bo_base;
	पूर्णांक r;

	अगर (bo->tbo.mem.mem_type == TTM_PL_SYSTEM)
		वापस;

	r = tपंचांग_bo_validate(&bo->tbo, &placement, &ctx);
	अगर (r) अणु
		DRM_ERROR("Failed to invalidate DMA-buf import (%d))\n", r);
		वापस;
	पूर्ण

	क्रम (bo_base = bo->vm_bo; bo_base; bo_base = bo_base->next) अणु
		काष्ठा amdgpu_vm *vm = bo_base->vm;
		काष्ठा dma_resv *resv = vm->root.base.bo->tbo.base.resv;

		अगर (ticket) अणु
			/* When we get an error here it means that somebody
			 * अन्यथा is holding the VM lock and updating page tables
			 * So we can just जारी here.
			 */
			r = dma_resv_lock(resv, ticket);
			अगर (r)
				जारी;

		पूर्ण अन्यथा अणु
			/* TODO: This is more problematic and we actually need
			 * to allow page tables updates without holding the
			 * lock.
			 */
			अगर (!dma_resv_trylock(resv))
				जारी;
		पूर्ण

		r = amdgpu_vm_clear_मुक्तd(adev, vm, शून्य);
		अगर (!r)
			r = amdgpu_vm_handle_moved(adev, vm);

		अगर (r && r != -EBUSY)
			DRM_ERROR("Failed to invalidate VM page tables (%d))\n",
				  r);

		dma_resv_unlock(resv);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा dma_buf_attach_ops amdgpu_dma_buf_attach_ops = अणु
	.allow_peer2peer = true,
	.move_notअगरy = amdgpu_dma_buf_move_notअगरy
पूर्ण;

/**
 * amdgpu_gem_prime_import - &drm_driver.gem_prime_import implementation
 * @dev: DRM device
 * @dma_buf: Shared DMA buffer
 *
 * Import a dma_buf पूर्णांकo a the driver and potentially create a new GEM object.
 *
 * Returns:
 * GEM BO representing the shared DMA buffer क्रम the given device.
 */
काष्ठा drm_gem_object *amdgpu_gem_prime_import(काष्ठा drm_device *dev,
					       काष्ठा dma_buf *dma_buf)
अणु
	काष्ठा dma_buf_attachment *attach;
	काष्ठा drm_gem_object *obj;

	अगर (dma_buf->ops == &amdgpu_dmabuf_ops) अणु
		obj = dma_buf->priv;
		अगर (obj->dev == dev) अणु
			/*
			 * Importing dmabuf exported from out own gem increases
			 * refcount on gem itself instead of f_count of dmabuf.
			 */
			drm_gem_object_get(obj);
			वापस obj;
		पूर्ण
	पूर्ण

	obj = amdgpu_dma_buf_create_obj(dev, dma_buf);
	अगर (IS_ERR(obj))
		वापस obj;

	attach = dma_buf_dynamic_attach(dma_buf, dev->dev,
					&amdgpu_dma_buf_attach_ops, obj);
	अगर (IS_ERR(attach)) अणु
		drm_gem_object_put(obj);
		वापस ERR_CAST(attach);
	पूर्ण

	get_dma_buf(dma_buf);
	obj->import_attach = attach;
	वापस obj;
पूर्ण

/**
 * amdgpu_dmabuf_is_xgmi_accessible - Check अगर xgmi available क्रम P2P transfer
 *
 * @adev: amdgpu_device poपूर्णांकer of the importer
 * @bo: amdgpu buffer object
 *
 * Returns:
 * True अगर dmabuf accessible over xgmi, false otherwise.
 */
bool amdgpu_dmabuf_is_xgmi_accessible(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_bo *bo)
अणु
	काष्ठा drm_gem_object *obj = &bo->tbo.base;
	काष्ठा drm_gem_object *gobj;

	अगर (obj->import_attach) अणु
		काष्ठा dma_buf *dma_buf = obj->import_attach->dmabuf;

		अगर (dma_buf->ops != &amdgpu_dmabuf_ops)
			/* No XGMI with non AMD GPUs */
			वापस false;

		gobj = dma_buf->priv;
		bo = gem_to_amdgpu_bo(gobj);
	पूर्ण

	अगर (amdgpu_xgmi_same_hive(adev, amdgpu_tपंचांग_adev(bo->tbo.bdev)) &&
			(bo->preferred_करोमुख्यs & AMDGPU_GEM_DOMAIN_VRAM))
		वापस true;

	वापस false;
पूर्ण
