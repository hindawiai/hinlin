<शैली गुरु>
/*
 * Copyright 2009 Jerome Glisse.
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
 *    Jerome Glisse <glisse@मुक्तdesktop.org>
 *    Thomas Hellstrom <thomas-at-tungstengraphics-करोt-com>
 *    Dave Airlie
 */
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-buf.h>

#समावेश <drm/amdgpu_drm.h>
#समावेश <drm/drm_cache.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_trace.h"
#समावेश "amdgpu_amdkfd.h"

/**
 * DOC: amdgpu_object
 *
 * This defines the पूर्णांकerfaces to operate on an &amdgpu_bo buffer object which
 * represents memory used by driver (VRAM, प्रणाली memory, etc.). The driver
 * provides DRM/GEM APIs to userspace. DRM/GEM APIs then use these पूर्णांकerfaces
 * to create/destroy/set buffer object which are then managed by the kernel TTM
 * memory manager.
 * The पूर्णांकerfaces are also used पूर्णांकernally by kernel clients, including gfx,
 * uvd, etc. क्रम kernel managed allocations used by the GPU.
 *
 */

/**
 * amdgpu_bo_subtract_pin_size - Remove BO from pin_size accounting
 *
 * @bo: &amdgpu_bo buffer object
 *
 * This function is called when a BO stops being pinned, and updates the
 * &amdgpu_device pin_size values accordingly.
 */
अटल व्योम amdgpu_bo_subtract_pin_size(काष्ठा amdgpu_bo *bo)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);

	अगर (bo->tbo.mem.mem_type == TTM_PL_VRAM) अणु
		atomic64_sub(amdgpu_bo_size(bo), &adev->vram_pin_size);
		atomic64_sub(amdgpu_vram_mgr_bo_visible_size(bo),
			     &adev->visible_pin_size);
	पूर्ण अन्यथा अगर (bo->tbo.mem.mem_type == TTM_PL_TT) अणु
		atomic64_sub(amdgpu_bo_size(bo), &adev->gart_pin_size);
	पूर्ण
पूर्ण

अटल व्योम amdgpu_bo_destroy(काष्ठा tपंचांग_buffer_object *tbo)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(tbo->bdev);
	काष्ठा amdgpu_bo *bo = tपंचांग_to_amdgpu_bo(tbo);
	काष्ठा amdgpu_bo_user *ubo;

	अगर (bo->tbo.pin_count > 0)
		amdgpu_bo_subtract_pin_size(bo);

	amdgpu_bo_kunmap(bo);

	अगर (bo->tbo.base.import_attach)
		drm_prime_gem_destroy(&bo->tbo.base, bo->tbo.sg);
	drm_gem_object_release(&bo->tbo.base);
	/* in हाल amdgpu_device_recover_vram got शून्य of bo->parent */
	अगर (!list_empty(&bo->shaकरोw_list)) अणु
		mutex_lock(&adev->shaकरोw_list_lock);
		list_del_init(&bo->shaकरोw_list);
		mutex_unlock(&adev->shaकरोw_list_lock);
	पूर्ण
	amdgpu_bo_unref(&bo->parent);

	अगर (bo->tbo.type == tपंचांग_bo_type_device) अणु
		ubo = to_amdgpu_bo_user(bo);
		kमुक्त(ubo->metadata);
	पूर्ण

	kvमुक्त(bo);
पूर्ण

/**
 * amdgpu_bo_is_amdgpu_bo - check अगर the buffer object is an &amdgpu_bo
 * @bo: buffer object to be checked
 *
 * Uses destroy function associated with the object to determine अगर this is
 * an &amdgpu_bo.
 *
 * Returns:
 * true अगर the object beदीर्घs to &amdgpu_bo, false अगर not.
 */
bool amdgpu_bo_is_amdgpu_bo(काष्ठा tपंचांग_buffer_object *bo)
अणु
	अगर (bo->destroy == &amdgpu_bo_destroy)
		वापस true;
	वापस false;
पूर्ण

/**
 * amdgpu_bo_placement_from_करोमुख्य - set buffer's placement
 * @abo: &amdgpu_bo buffer object whose placement is to be set
 * @करोमुख्य: requested करोमुख्य
 *
 * Sets buffer's placement according to requested domain and the buffer's
 * flags.
 */
व्योम amdgpu_bo_placement_from_करोमुख्य(काष्ठा amdgpu_bo *abo, u32 करोमुख्य)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(abo->tbo.bdev);
	काष्ठा tपंचांग_placement *placement = &abo->placement;
	काष्ठा tपंचांग_place *places = abo->placements;
	u64 flags = abo->flags;
	u32 c = 0;

	अगर (करोमुख्य & AMDGPU_GEM_DOMAIN_VRAM) अणु
		अचिन्हित visible_pfn = adev->gmc.visible_vram_size >> PAGE_SHIFT;

		places[c].fpfn = 0;
		places[c].lpfn = 0;
		places[c].mem_type = TTM_PL_VRAM;
		places[c].flags = 0;

		अगर (flags & AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED)
			places[c].lpfn = visible_pfn;
		अन्यथा
			places[c].flags |= TTM_PL_FLAG_TOPDOWN;

		अगर (flags & AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS)
			places[c].flags |= TTM_PL_FLAG_CONTIGUOUS;
		c++;
	पूर्ण

	अगर (करोमुख्य & AMDGPU_GEM_DOMAIN_GTT) अणु
		places[c].fpfn = 0;
		places[c].lpfn = 0;
		places[c].mem_type = TTM_PL_TT;
		places[c].flags = 0;
		c++;
	पूर्ण

	अगर (करोमुख्य & AMDGPU_GEM_DOMAIN_CPU) अणु
		places[c].fpfn = 0;
		places[c].lpfn = 0;
		places[c].mem_type = TTM_PL_SYSTEM;
		places[c].flags = 0;
		c++;
	पूर्ण

	अगर (करोमुख्य & AMDGPU_GEM_DOMAIN_GDS) अणु
		places[c].fpfn = 0;
		places[c].lpfn = 0;
		places[c].mem_type = AMDGPU_PL_GDS;
		places[c].flags = 0;
		c++;
	पूर्ण

	अगर (करोमुख्य & AMDGPU_GEM_DOMAIN_GWS) अणु
		places[c].fpfn = 0;
		places[c].lpfn = 0;
		places[c].mem_type = AMDGPU_PL_GWS;
		places[c].flags = 0;
		c++;
	पूर्ण

	अगर (करोमुख्य & AMDGPU_GEM_DOMAIN_OA) अणु
		places[c].fpfn = 0;
		places[c].lpfn = 0;
		places[c].mem_type = AMDGPU_PL_OA;
		places[c].flags = 0;
		c++;
	पूर्ण

	अगर (!c) अणु
		places[c].fpfn = 0;
		places[c].lpfn = 0;
		places[c].mem_type = TTM_PL_SYSTEM;
		places[c].flags = 0;
		c++;
	पूर्ण

	BUG_ON(c >= AMDGPU_BO_MAX_PLACEMENTS);

	placement->num_placement = c;
	placement->placement = places;

	placement->num_busy_placement = c;
	placement->busy_placement = places;
पूर्ण

/**
 * amdgpu_bo_create_reserved - create reserved BO क्रम kernel use
 *
 * @adev: amdgpu device object
 * @size: size क्रम the new BO
 * @align: alignment क्रम the new BO
 * @करोमुख्य: where to place it
 * @bo_ptr: used to initialize BOs in काष्ठाures
 * @gpu_addr: GPU addr of the pinned BO
 * @cpu_addr: optional CPU address mapping
 *
 * Allocates and pins a BO क्रम kernel पूर्णांकernal use, and वापसs it still
 * reserved.
 *
 * Note: For bo_ptr new BO is only created अगर bo_ptr poपूर्णांकs to शून्य.
 *
 * Returns:
 * 0 on success, negative error code otherwise.
 */
पूर्णांक amdgpu_bo_create_reserved(काष्ठा amdgpu_device *adev,
			      अचिन्हित दीर्घ size, पूर्णांक align,
			      u32 करोमुख्य, काष्ठा amdgpu_bo **bo_ptr,
			      u64 *gpu_addr, व्योम **cpu_addr)
अणु
	काष्ठा amdgpu_bo_param bp;
	bool मुक्त = false;
	पूर्णांक r;

	अगर (!size) अणु
		amdgpu_bo_unref(bo_ptr);
		वापस 0;
	पूर्ण

	स_रखो(&bp, 0, माप(bp));
	bp.size = size;
	bp.byte_align = align;
	bp.करोमुख्य = करोमुख्य;
	bp.flags = cpu_addr ? AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED
		: AMDGPU_GEM_CREATE_NO_CPU_ACCESS;
	bp.flags |= AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS;
	bp.type = tपंचांग_bo_type_kernel;
	bp.resv = शून्य;
	bp.bo_ptr_size = माप(काष्ठा amdgpu_bo);

	अगर (!*bo_ptr) अणु
		r = amdgpu_bo_create(adev, &bp, bo_ptr);
		अगर (r) अणु
			dev_err(adev->dev, "(%d) failed to allocate kernel bo\n",
				r);
			वापस r;
		पूर्ण
		मुक्त = true;
	पूर्ण

	r = amdgpu_bo_reserve(*bo_ptr, false);
	अगर (r) अणु
		dev_err(adev->dev, "(%d) failed to reserve kernel bo\n", r);
		जाओ error_मुक्त;
	पूर्ण

	r = amdgpu_bo_pin(*bo_ptr, करोमुख्य);
	अगर (r) अणु
		dev_err(adev->dev, "(%d) kernel bo pin failed\n", r);
		जाओ error_unreserve;
	पूर्ण

	r = amdgpu_tपंचांग_alloc_gart(&(*bo_ptr)->tbo);
	अगर (r) अणु
		dev_err(adev->dev, "%p bind failed\n", *bo_ptr);
		जाओ error_unpin;
	पूर्ण

	अगर (gpu_addr)
		*gpu_addr = amdgpu_bo_gpu_offset(*bo_ptr);

	अगर (cpu_addr) अणु
		r = amdgpu_bo_kmap(*bo_ptr, cpu_addr);
		अगर (r) अणु
			dev_err(adev->dev, "(%d) kernel bo map failed\n", r);
			जाओ error_unpin;
		पूर्ण
	पूर्ण

	वापस 0;

error_unpin:
	amdgpu_bo_unpin(*bo_ptr);
error_unreserve:
	amdgpu_bo_unreserve(*bo_ptr);

error_मुक्त:
	अगर (मुक्त)
		amdgpu_bo_unref(bo_ptr);

	वापस r;
पूर्ण

/**
 * amdgpu_bo_create_kernel - create BO क्रम kernel use
 *
 * @adev: amdgpu device object
 * @size: size क्रम the new BO
 * @align: alignment क्रम the new BO
 * @करोमुख्य: where to place it
 * @bo_ptr:  used to initialize BOs in काष्ठाures
 * @gpu_addr: GPU addr of the pinned BO
 * @cpu_addr: optional CPU address mapping
 *
 * Allocates and pins a BO क्रम kernel पूर्णांकernal use.
 *
 * Note: For bo_ptr new BO is only created अगर bo_ptr poपूर्णांकs to शून्य.
 *
 * Returns:
 * 0 on success, negative error code otherwise.
 */
पूर्णांक amdgpu_bo_create_kernel(काष्ठा amdgpu_device *adev,
			    अचिन्हित दीर्घ size, पूर्णांक align,
			    u32 करोमुख्य, काष्ठा amdgpu_bo **bo_ptr,
			    u64 *gpu_addr, व्योम **cpu_addr)
अणु
	पूर्णांक r;

	r = amdgpu_bo_create_reserved(adev, size, align, करोमुख्य, bo_ptr,
				      gpu_addr, cpu_addr);

	अगर (r)
		वापस r;

	अगर (*bo_ptr)
		amdgpu_bo_unreserve(*bo_ptr);

	वापस 0;
पूर्ण

/**
 * amdgpu_bo_create_kernel_at - create BO क्रम kernel use at specअगरic location
 *
 * @adev: amdgpu device object
 * @offset: offset of the BO
 * @size: size of the BO
 * @करोमुख्य: where to place it
 * @bo_ptr:  used to initialize BOs in काष्ठाures
 * @cpu_addr: optional CPU address mapping
 *
 * Creates a kernel BO at a specअगरic offset in the address space of the करोमुख्य.
 *
 * Returns:
 * 0 on success, negative error code otherwise.
 */
पूर्णांक amdgpu_bo_create_kernel_at(काष्ठा amdgpu_device *adev,
			       uपूर्णांक64_t offset, uपूर्णांक64_t size, uपूर्णांक32_t करोमुख्य,
			       काष्ठा amdgpu_bo **bo_ptr, व्योम **cpu_addr)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु false, false पूर्ण;
	अचिन्हित पूर्णांक i;
	पूर्णांक r;

	offset &= PAGE_MASK;
	size = ALIGN(size, PAGE_SIZE);

	r = amdgpu_bo_create_reserved(adev, size, PAGE_SIZE, करोमुख्य, bo_ptr,
				      शून्य, cpu_addr);
	अगर (r)
		वापस r;

	अगर ((*bo_ptr) == शून्य)
		वापस 0;

	/*
	 * Remove the original mem node and create a new one at the request
	 * position.
	 */
	अगर (cpu_addr)
		amdgpu_bo_kunmap(*bo_ptr);

	tपंचांग_resource_मुक्त(&(*bo_ptr)->tbo, &(*bo_ptr)->tbo.mem);

	क्रम (i = 0; i < (*bo_ptr)->placement.num_placement; ++i) अणु
		(*bo_ptr)->placements[i].fpfn = offset >> PAGE_SHIFT;
		(*bo_ptr)->placements[i].lpfn = (offset + size) >> PAGE_SHIFT;
	पूर्ण
	r = tपंचांग_bo_mem_space(&(*bo_ptr)->tbo, &(*bo_ptr)->placement,
			     &(*bo_ptr)->tbo.mem, &ctx);
	अगर (r)
		जाओ error;

	अगर (cpu_addr) अणु
		r = amdgpu_bo_kmap(*bo_ptr, cpu_addr);
		अगर (r)
			जाओ error;
	पूर्ण

	amdgpu_bo_unreserve(*bo_ptr);
	वापस 0;

error:
	amdgpu_bo_unreserve(*bo_ptr);
	amdgpu_bo_unref(bo_ptr);
	वापस r;
पूर्ण

/**
 * amdgpu_bo_मुक्त_kernel - मुक्त BO क्रम kernel use
 *
 * @bo: amdgpu BO to मुक्त
 * @gpu_addr: poपूर्णांकer to where the BO's GPU memory space address was stored
 * @cpu_addr: poपूर्णांकer to where the BO's CPU memory space address was stored
 *
 * unmaps and unpin a BO क्रम kernel पूर्णांकernal use.
 */
व्योम amdgpu_bo_मुक्त_kernel(काष्ठा amdgpu_bo **bo, u64 *gpu_addr,
			   व्योम **cpu_addr)
अणु
	अगर (*bo == शून्य)
		वापस;

	अगर (likely(amdgpu_bo_reserve(*bo, true) == 0)) अणु
		अगर (cpu_addr)
			amdgpu_bo_kunmap(*bo);

		amdgpu_bo_unpin(*bo);
		amdgpu_bo_unreserve(*bo);
	पूर्ण
	amdgpu_bo_unref(bo);

	अगर (gpu_addr)
		*gpu_addr = 0;

	अगर (cpu_addr)
		*cpu_addr = शून्य;
पूर्ण

/* Validate bo size is bit bigger then the request करोमुख्य */
अटल bool amdgpu_bo_validate_size(काष्ठा amdgpu_device *adev,
					  अचिन्हित दीर्घ size, u32 करोमुख्य)
अणु
	काष्ठा tपंचांग_resource_manager *man = शून्य;

	/*
	 * If GTT is part of requested करोमुख्यs the check must succeed to
	 * allow fall back to GTT
	 */
	अगर (करोमुख्य & AMDGPU_GEM_DOMAIN_GTT) अणु
		man = tपंचांग_manager_type(&adev->mman.bdev, TTM_PL_TT);

		अगर (size < (man->size << PAGE_SHIFT))
			वापस true;
		अन्यथा
			जाओ fail;
	पूर्ण

	अगर (करोमुख्य & AMDGPU_GEM_DOMAIN_VRAM) अणु
		man = tपंचांग_manager_type(&adev->mman.bdev, TTM_PL_VRAM);

		अगर (size < (man->size << PAGE_SHIFT))
			वापस true;
		अन्यथा
			जाओ fail;
	पूर्ण


	/* TODO add more करोमुख्यs checks, such as AMDGPU_GEM_DOMAIN_CPU */
	वापस true;

fail:
	DRM_DEBUG("BO size %lu > total memory in domain: %llu\n", size,
		  man->size << PAGE_SHIFT);
	वापस false;
पूर्ण

bool amdgpu_bo_support_uswc(u64 bo_flags)
अणु

#अगर_घोषित CONFIG_X86_32
	/* XXX: Write-combined CPU mappings of GTT seem broken on 32-bit
	 * See https://bugs.मुक्तdesktop.org/show_bug.cgi?id=84627
	 */
	वापस false;
#या_अगर defined(CONFIG_X86) && !defined(CONFIG_X86_PAT)
	/* Don't try to enable write-combining when it can't work, or things
	 * may be slow
	 * See https://bugs.मुक्तdesktop.org/show_bug.cgi?id=88758
	 */

#अगर_अघोषित CONFIG_COMPILE_TEST
#warning Please enable CONFIG_MTRR and CONFIG_X86_PAT क्रम better perक्रमmance \
	 thanks to ग_लिखो-combining
#पूर्ण_अगर

	अगर (bo_flags & AMDGPU_GEM_CREATE_CPU_GTT_USWC)
		DRM_INFO_ONCE("Please enable CONFIG_MTRR and CONFIG_X86_PAT for "
			      "better performance thanks to write-combining\n");
	वापस false;
#अन्यथा
	/* For architectures that करोn't support WC memory,
	 * mask out the WC flag from the BO
	 */
	अगर (!drm_arch_can_wc_memory())
		वापस false;

	वापस true;
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक amdgpu_bo_करो_create(काष्ठा amdgpu_device *adev,
			       काष्ठा amdgpu_bo_param *bp,
			       काष्ठा amdgpu_bo **bo_ptr)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु
		.पूर्णांकerruptible = (bp->type != tपंचांग_bo_type_kernel),
		.no_रुको_gpu = bp->no_रुको_gpu,
		/* We opt to aव्योम OOM on प्रणाली pages allocations */
		.gfp_retry_mayfail = true,
		.allow_res_evict = bp->type != tपंचांग_bo_type_kernel,
		.resv = bp->resv
	पूर्ण;
	काष्ठा amdgpu_bo *bo;
	अचिन्हित दीर्घ page_align, size = bp->size;
	पूर्णांक r;

	/* Note that GDS/GWS/OA allocates 1 page per byte/resource. */
	अगर (bp->करोमुख्य & (AMDGPU_GEM_DOMAIN_GWS | AMDGPU_GEM_DOMAIN_OA)) अणु
		/* GWS and OA करोn't need any alignment. */
		page_align = bp->byte_align;
		size <<= PAGE_SHIFT;
	पूर्ण अन्यथा अगर (bp->करोमुख्य & AMDGPU_GEM_DOMAIN_GDS) अणु
		/* Both size and alignment must be a multiple of 4. */
		page_align = ALIGN(bp->byte_align, 4);
		size = ALIGN(size, 4) << PAGE_SHIFT;
	पूर्ण अन्यथा अणु
		/* Memory should be aligned at least to a page size. */
		page_align = ALIGN(bp->byte_align, PAGE_SIZE) >> PAGE_SHIFT;
		size = ALIGN(size, PAGE_SIZE);
	पूर्ण

	अगर (!amdgpu_bo_validate_size(adev, size, bp->करोमुख्य))
		वापस -ENOMEM;

	BUG_ON(bp->bo_ptr_size < माप(काष्ठा amdgpu_bo));

	*bo_ptr = शून्य;
	bo = kvzalloc(bp->bo_ptr_size, GFP_KERNEL);
	अगर (bo == शून्य)
		वापस -ENOMEM;
	drm_gem_निजी_object_init(adev_to_drm(adev), &bo->tbo.base, size);
	INIT_LIST_HEAD(&bo->shaकरोw_list);
	bo->vm_bo = शून्य;
	bo->preferred_करोमुख्यs = bp->preferred_करोमुख्य ? bp->preferred_करोमुख्य :
		bp->करोमुख्य;
	bo->allowed_करोमुख्यs = bo->preferred_करोमुख्यs;
	अगर (bp->type != tपंचांग_bo_type_kernel &&
	    bo->allowed_करोमुख्यs == AMDGPU_GEM_DOMAIN_VRAM)
		bo->allowed_करोमुख्यs |= AMDGPU_GEM_DOMAIN_GTT;

	bo->flags = bp->flags;

	अगर (!amdgpu_bo_support_uswc(bo->flags))
		bo->flags &= ~AMDGPU_GEM_CREATE_CPU_GTT_USWC;

	bo->tbo.bdev = &adev->mman.bdev;
	अगर (bp->करोमुख्य & (AMDGPU_GEM_DOMAIN_GWS | AMDGPU_GEM_DOMAIN_OA |
			  AMDGPU_GEM_DOMAIN_GDS))
		amdgpu_bo_placement_from_करोमुख्य(bo, AMDGPU_GEM_DOMAIN_CPU);
	अन्यथा
		amdgpu_bo_placement_from_करोमुख्य(bo, bp->करोमुख्य);
	अगर (bp->type == tपंचांग_bo_type_kernel)
		bo->tbo.priority = 1;

	r = tपंचांग_bo_init_reserved(&adev->mman.bdev, &bo->tbo, size, bp->type,
				 &bo->placement, page_align, &ctx,  शून्य,
				 bp->resv, &amdgpu_bo_destroy);
	अगर (unlikely(r != 0))
		वापस r;

	अगर (!amdgpu_gmc_vram_full_visible(&adev->gmc) &&
	    bo->tbo.mem.mem_type == TTM_PL_VRAM &&
	    bo->tbo.mem.start < adev->gmc.visible_vram_size >> PAGE_SHIFT)
		amdgpu_cs_report_moved_bytes(adev, ctx.bytes_moved,
					     ctx.bytes_moved);
	अन्यथा
		amdgpu_cs_report_moved_bytes(adev, ctx.bytes_moved, 0);

	अगर (bp->flags & AMDGPU_GEM_CREATE_VRAM_CLEARED &&
	    bo->tbo.mem.mem_type == TTM_PL_VRAM) अणु
		काष्ठा dma_fence *fence;

		r = amdgpu_fill_buffer(bo, 0, bo->tbo.base.resv, &fence);
		अगर (unlikely(r))
			जाओ fail_unreserve;

		amdgpu_bo_fence(bo, fence, false);
		dma_fence_put(bo->tbo.moving);
		bo->tbo.moving = dma_fence_get(fence);
		dma_fence_put(fence);
	पूर्ण
	अगर (!bp->resv)
		amdgpu_bo_unreserve(bo);
	*bo_ptr = bo;

	trace_amdgpu_bo_create(bo);

	/* Treat CPU_ACCESS_REQUIRED only as a hपूर्णांक अगर given by UMD */
	अगर (bp->type == tपंचांग_bo_type_device)
		bo->flags &= ~AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED;

	वापस 0;

fail_unreserve:
	अगर (!bp->resv)
		dma_resv_unlock(bo->tbo.base.resv);
	amdgpu_bo_unref(&bo);
	वापस r;
पूर्ण

अटल पूर्णांक amdgpu_bo_create_shaकरोw(काष्ठा amdgpu_device *adev,
				   अचिन्हित दीर्घ size,
				   काष्ठा amdgpu_bo *bo)
अणु
	काष्ठा amdgpu_bo_param bp;
	पूर्णांक r;

	अगर (bo->shaकरोw)
		वापस 0;

	स_रखो(&bp, 0, माप(bp));
	bp.size = size;
	bp.करोमुख्य = AMDGPU_GEM_DOMAIN_GTT;
	bp.flags = AMDGPU_GEM_CREATE_CPU_GTT_USWC |
		AMDGPU_GEM_CREATE_SHADOW;
	bp.type = tपंचांग_bo_type_kernel;
	bp.resv = bo->tbo.base.resv;
	bp.bo_ptr_size = माप(काष्ठा amdgpu_bo);

	r = amdgpu_bo_करो_create(adev, &bp, &bo->shaकरोw);
	अगर (!r) अणु
		bo->shaकरोw->parent = amdgpu_bo_ref(bo);
		mutex_lock(&adev->shaकरोw_list_lock);
		list_add_tail(&bo->shaकरोw->shaकरोw_list, &adev->shaकरोw_list);
		mutex_unlock(&adev->shaकरोw_list_lock);
	पूर्ण

	वापस r;
पूर्ण

/**
 * amdgpu_bo_create - create an &amdgpu_bo buffer object
 * @adev: amdgpu device object
 * @bp: parameters to be used क्रम the buffer object
 * @bo_ptr: poपूर्णांकer to the buffer object poपूर्णांकer
 *
 * Creates an &amdgpu_bo buffer object; and अगर requested, also creates a
 * shaकरोw object.
 * Shaकरोw object is used to backup the original buffer object, and is always
 * in GTT.
 *
 * Returns:
 * 0 क्रम success or a negative error code on failure.
 */
पूर्णांक amdgpu_bo_create(काष्ठा amdgpu_device *adev,
		     काष्ठा amdgpu_bo_param *bp,
		     काष्ठा amdgpu_bo **bo_ptr)
अणु
	u64 flags = bp->flags;
	पूर्णांक r;

	bp->flags = bp->flags & ~AMDGPU_GEM_CREATE_SHADOW;

	r = amdgpu_bo_करो_create(adev, bp, bo_ptr);
	अगर (r)
		वापस r;

	अगर ((flags & AMDGPU_GEM_CREATE_SHADOW) && !(adev->flags & AMD_IS_APU)) अणु
		अगर (!bp->resv)
			WARN_ON(dma_resv_lock((*bo_ptr)->tbo.base.resv,
							शून्य));

		r = amdgpu_bo_create_shaकरोw(adev, bp->size, *bo_ptr);

		अगर (!bp->resv)
			dma_resv_unlock((*bo_ptr)->tbo.base.resv);

		अगर (r)
			amdgpu_bo_unref(bo_ptr);
	पूर्ण

	वापस r;
पूर्ण

/**
 * amdgpu_bo_create_user - create an &amdgpu_bo_user buffer object
 * @adev: amdgpu device object
 * @bp: parameters to be used क्रम the buffer object
 * @ubo_ptr: poपूर्णांकer to the buffer object poपूर्णांकer
 *
 * Create a BO to be used by user application;
 *
 * Returns:
 * 0 क्रम success or a negative error code on failure.
 */

पूर्णांक amdgpu_bo_create_user(काष्ठा amdgpu_device *adev,
			  काष्ठा amdgpu_bo_param *bp,
			  काष्ठा amdgpu_bo_user **ubo_ptr)
अणु
	काष्ठा amdgpu_bo *bo_ptr;
	पूर्णांक r;

	bp->flags = bp->flags & ~AMDGPU_GEM_CREATE_SHADOW;
	bp->bo_ptr_size = माप(काष्ठा amdgpu_bo_user);
	r = amdgpu_bo_करो_create(adev, bp, &bo_ptr);
	अगर (r)
		वापस r;

	*ubo_ptr = to_amdgpu_bo_user(bo_ptr);
	वापस r;
पूर्ण
/**
 * amdgpu_bo_validate - validate an &amdgpu_bo buffer object
 * @bo: poपूर्णांकer to the buffer object
 *
 * Sets placement according to करोमुख्य; and changes placement and caching
 * policy of the buffer object according to the placement.
 * This is used क्रम validating shaकरोw bos.  It calls tपंचांग_bo_validate() to
 * make sure the buffer is resident where it needs to be.
 *
 * Returns:
 * 0 क्रम success or a negative error code on failure.
 */
पूर्णांक amdgpu_bo_validate(काष्ठा amdgpu_bo *bo)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु false, false पूर्ण;
	uपूर्णांक32_t करोमुख्य;
	पूर्णांक r;

	अगर (bo->tbo.pin_count)
		वापस 0;

	करोमुख्य = bo->preferred_करोमुख्यs;

retry:
	amdgpu_bo_placement_from_करोमुख्य(bo, करोमुख्य);
	r = tपंचांग_bo_validate(&bo->tbo, &bo->placement, &ctx);
	अगर (unlikely(r == -ENOMEM) && करोमुख्य != bo->allowed_करोमुख्यs) अणु
		करोमुख्य = bo->allowed_करोमुख्यs;
		जाओ retry;
	पूर्ण

	वापस r;
पूर्ण

/**
 * amdgpu_bo_restore_shaकरोw - restore an &amdgpu_bo shaकरोw
 *
 * @shaकरोw: &amdgpu_bo shaकरोw to be restored
 * @fence: dma_fence associated with the operation
 *
 * Copies a buffer object's shaकरोw content back to the object.
 * This is used क्रम recovering a buffer from its shaकरोw in हाल of a gpu
 * reset where vram context may be lost.
 *
 * Returns:
 * 0 क्रम success or a negative error code on failure.
 */
पूर्णांक amdgpu_bo_restore_shaकरोw(काष्ठा amdgpu_bo *shaकरोw, काष्ठा dma_fence **fence)

अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(shaकरोw->tbo.bdev);
	काष्ठा amdgpu_ring *ring = adev->mman.buffer_funcs_ring;
	uपूर्णांक64_t shaकरोw_addr, parent_addr;

	shaकरोw_addr = amdgpu_bo_gpu_offset(shaकरोw);
	parent_addr = amdgpu_bo_gpu_offset(shaकरोw->parent);

	वापस amdgpu_copy_buffer(ring, shaकरोw_addr, parent_addr,
				  amdgpu_bo_size(shaकरोw), शून्य, fence,
				  true, false, false);
पूर्ण

/**
 * amdgpu_bo_kmap - map an &amdgpu_bo buffer object
 * @bo: &amdgpu_bo buffer object to be mapped
 * @ptr: kernel भव address to be वापसed
 *
 * Calls tपंचांग_bo_kmap() to set up the kernel भव mapping; calls
 * amdgpu_bo_kptr() to get the kernel भव address.
 *
 * Returns:
 * 0 क्रम success or a negative error code on failure.
 */
पूर्णांक amdgpu_bo_kmap(काष्ठा amdgpu_bo *bo, व्योम **ptr)
अणु
	व्योम *kptr;
	दीर्घ r;

	अगर (bo->flags & AMDGPU_GEM_CREATE_NO_CPU_ACCESS)
		वापस -EPERM;

	kptr = amdgpu_bo_kptr(bo);
	अगर (kptr) अणु
		अगर (ptr)
			*ptr = kptr;
		वापस 0;
	पूर्ण

	r = dma_resv_रुको_समयout_rcu(bo->tbo.base.resv, false, false,
						MAX_SCHEDULE_TIMEOUT);
	अगर (r < 0)
		वापस r;

	r = tपंचांग_bo_kmap(&bo->tbo, 0, bo->tbo.mem.num_pages, &bo->kmap);
	अगर (r)
		वापस r;

	अगर (ptr)
		*ptr = amdgpu_bo_kptr(bo);

	वापस 0;
पूर्ण

/**
 * amdgpu_bo_kptr - वापसs a kernel भव address of the buffer object
 * @bo: &amdgpu_bo buffer object
 *
 * Calls tपंचांग_kmap_obj_भव() to get the kernel भव address
 *
 * Returns:
 * the भव address of a buffer object area.
 */
व्योम *amdgpu_bo_kptr(काष्ठा amdgpu_bo *bo)
अणु
	bool is_iomem;

	वापस tपंचांग_kmap_obj_भव(&bo->kmap, &is_iomem);
पूर्ण

/**
 * amdgpu_bo_kunmap - unmap an &amdgpu_bo buffer object
 * @bo: &amdgpu_bo buffer object to be unmapped
 *
 * Unmaps a kernel map set up by amdgpu_bo_kmap().
 */
व्योम amdgpu_bo_kunmap(काष्ठा amdgpu_bo *bo)
अणु
	अगर (bo->kmap.bo)
		tपंचांग_bo_kunmap(&bo->kmap);
पूर्ण

/**
 * amdgpu_bo_ref - reference an &amdgpu_bo buffer object
 * @bo: &amdgpu_bo buffer object
 *
 * References the contained &tपंचांग_buffer_object.
 *
 * Returns:
 * a refcounted poपूर्णांकer to the &amdgpu_bo buffer object.
 */
काष्ठा amdgpu_bo *amdgpu_bo_ref(काष्ठा amdgpu_bo *bo)
अणु
	अगर (bo == शून्य)
		वापस शून्य;

	tपंचांग_bo_get(&bo->tbo);
	वापस bo;
पूर्ण

/**
 * amdgpu_bo_unref - unreference an &amdgpu_bo buffer object
 * @bo: &amdgpu_bo buffer object
 *
 * Unreferences the contained &tपंचांग_buffer_object and clear the poपूर्णांकer
 */
व्योम amdgpu_bo_unref(काष्ठा amdgpu_bo **bo)
अणु
	काष्ठा tपंचांग_buffer_object *tbo;

	अगर ((*bo) == शून्य)
		वापस;

	tbo = &((*bo)->tbo);
	tपंचांग_bo_put(tbo);
	*bo = शून्य;
पूर्ण

/**
 * amdgpu_bo_pin_restricted - pin an &amdgpu_bo buffer object
 * @bo: &amdgpu_bo buffer object to be pinned
 * @करोमुख्य: करोमुख्य to be pinned to
 * @min_offset: the start of requested address range
 * @max_offset: the end of requested address range
 *
 * Pins the buffer object according to requested करोमुख्य and address range. If
 * the memory is unbound gart memory, binds the pages पूर्णांकo gart table. Adjusts
 * pin_count and pin_size accordingly.
 *
 * Pinning means to lock pages in memory aदीर्घ with keeping them at a fixed
 * offset. It is required when a buffer can not be moved, क्रम example, when
 * a display buffer is being scanned out.
 *
 * Compared with amdgpu_bo_pin(), this function gives more flexibility on
 * where to pin a buffer अगर there are specअगरic restrictions on where a buffer
 * must be located.
 *
 * Returns:
 * 0 क्रम success or a negative error code on failure.
 */
पूर्णांक amdgpu_bo_pin_restricted(काष्ठा amdgpu_bo *bo, u32 करोमुख्य,
			     u64 min_offset, u64 max_offset)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);
	काष्ठा tपंचांग_operation_ctx ctx = अणु false, false पूर्ण;
	पूर्णांक r, i;

	अगर (amdgpu_tपंचांग_tt_get_usermm(bo->tbo.tपंचांग))
		वापस -EPERM;

	अगर (WARN_ON_ONCE(min_offset > max_offset))
		वापस -EINVAL;

	/* A shared bo cannot be migrated to VRAM */
	अगर (bo->prime_shared_count || bo->tbo.base.import_attach) अणु
		अगर (करोमुख्य & AMDGPU_GEM_DOMAIN_GTT)
			करोमुख्य = AMDGPU_GEM_DOMAIN_GTT;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	/* This assumes only APU display buffers are pinned with (VRAM|GTT).
	 * See function amdgpu_display_supported_करोमुख्यs()
	 */
	करोमुख्य = amdgpu_bo_get_preferred_pin_करोमुख्य(adev, करोमुख्य);

	अगर (bo->tbo.pin_count) अणु
		uपूर्णांक32_t mem_type = bo->tbo.mem.mem_type;
		uपूर्णांक32_t mem_flags = bo->tbo.mem.placement;

		अगर (!(करोमुख्य & amdgpu_mem_type_to_करोमुख्य(mem_type)))
			वापस -EINVAL;

		अगर ((mem_type == TTM_PL_VRAM) &&
		    (bo->flags & AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS) &&
		    !(mem_flags & TTM_PL_FLAG_CONTIGUOUS))
			वापस -EINVAL;

		tपंचांग_bo_pin(&bo->tbo);

		अगर (max_offset != 0) अणु
			u64 करोमुख्य_start = amdgpu_tपंचांग_करोमुख्य_start(adev,
								   mem_type);
			WARN_ON_ONCE(max_offset <
				     (amdgpu_bo_gpu_offset(bo) - करोमुख्य_start));
		पूर्ण

		वापस 0;
	पूर्ण

	अगर (bo->tbo.base.import_attach)
		dma_buf_pin(bo->tbo.base.import_attach);

	/* क्रमce to pin पूर्णांकo visible video ram */
	अगर (!(bo->flags & AMDGPU_GEM_CREATE_NO_CPU_ACCESS))
		bo->flags |= AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED;
	amdgpu_bo_placement_from_करोमुख्य(bo, करोमुख्य);
	क्रम (i = 0; i < bo->placement.num_placement; i++) अणु
		अचिन्हित fpfn, lpfn;

		fpfn = min_offset >> PAGE_SHIFT;
		lpfn = max_offset >> PAGE_SHIFT;

		अगर (fpfn > bo->placements[i].fpfn)
			bo->placements[i].fpfn = fpfn;
		अगर (!bo->placements[i].lpfn ||
		    (lpfn && lpfn < bo->placements[i].lpfn))
			bo->placements[i].lpfn = lpfn;
	पूर्ण

	r = tपंचांग_bo_validate(&bo->tbo, &bo->placement, &ctx);
	अगर (unlikely(r)) अणु
		dev_err(adev->dev, "%p pin failed\n", bo);
		जाओ error;
	पूर्ण

	tपंचांग_bo_pin(&bo->tbo);

	करोमुख्य = amdgpu_mem_type_to_करोमुख्य(bo->tbo.mem.mem_type);
	अगर (करोमुख्य == AMDGPU_GEM_DOMAIN_VRAM) अणु
		atomic64_add(amdgpu_bo_size(bo), &adev->vram_pin_size);
		atomic64_add(amdgpu_vram_mgr_bo_visible_size(bo),
			     &adev->visible_pin_size);
	पूर्ण अन्यथा अगर (करोमुख्य == AMDGPU_GEM_DOMAIN_GTT) अणु
		atomic64_add(amdgpu_bo_size(bo), &adev->gart_pin_size);
	पूर्ण

error:
	वापस r;
पूर्ण

/**
 * amdgpu_bo_pin - pin an &amdgpu_bo buffer object
 * @bo: &amdgpu_bo buffer object to be pinned
 * @करोमुख्य: करोमुख्य to be pinned to
 *
 * A simple wrapper to amdgpu_bo_pin_restricted().
 * Provides a simpler API क्रम buffers that करो not have any strict restrictions
 * on where a buffer must be located.
 *
 * Returns:
 * 0 क्रम success or a negative error code on failure.
 */
पूर्णांक amdgpu_bo_pin(काष्ठा amdgpu_bo *bo, u32 करोमुख्य)
अणु
	bo->flags |= AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS;
	वापस amdgpu_bo_pin_restricted(bo, करोमुख्य, 0, 0);
पूर्ण

/**
 * amdgpu_bo_unpin - unpin an &amdgpu_bo buffer object
 * @bo: &amdgpu_bo buffer object to be unpinned
 *
 * Decreases the pin_count, and clears the flags अगर pin_count reaches 0.
 * Changes placement and pin size accordingly.
 *
 * Returns:
 * 0 क्रम success or a negative error code on failure.
 */
व्योम amdgpu_bo_unpin(काष्ठा amdgpu_bo *bo)
अणु
	tपंचांग_bo_unpin(&bo->tbo);
	अगर (bo->tbo.pin_count)
		वापस;

	amdgpu_bo_subtract_pin_size(bo);

	अगर (bo->tbo.base.import_attach)
		dma_buf_unpin(bo->tbo.base.import_attach);
पूर्ण

/**
 * amdgpu_bo_evict_vram - evict VRAM buffers
 * @adev: amdgpu device object
 *
 * Evicts all VRAM buffers on the lru list of the memory type.
 * Mainly used क्रम evicting vram at suspend समय.
 *
 * Returns:
 * 0 क्रम success or a negative error code on failure.
 */
पूर्णांक amdgpu_bo_evict_vram(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा tपंचांग_resource_manager *man;

	अगर (adev->in_s3 && (adev->flags & AMD_IS_APU)) अणु
		/* No need to evict vram on APUs क्रम suspend to ram */
		वापस 0;
	पूर्ण

	man = tपंचांग_manager_type(&adev->mman.bdev, TTM_PL_VRAM);
	वापस tपंचांग_resource_manager_evict_all(&adev->mman.bdev, man);
पूर्ण

अटल स्थिर अक्षर *amdgpu_vram_names[] = अणु
	"UNKNOWN",
	"GDDR1",
	"DDR2",
	"GDDR3",
	"GDDR4",
	"GDDR5",
	"HBM",
	"DDR3",
	"DDR4",
	"GDDR6",
	"DDR5"
पूर्ण;

/**
 * amdgpu_bo_init - initialize memory manager
 * @adev: amdgpu device object
 *
 * Calls amdgpu_tपंचांग_init() to initialize amdgpu memory manager.
 *
 * Returns:
 * 0 क्रम success or a negative error code on failure.
 */
पूर्णांक amdgpu_bo_init(काष्ठा amdgpu_device *adev)
अणु
	/* On A+A platक्रमm, VRAM can be mapped as WB */
	अगर (!adev->gmc.xgmi.connected_to_cpu) अणु
		/* reserve PAT memory space to WC क्रम VRAM */
		arch_io_reserve_memtype_wc(adev->gmc.aper_base,
				adev->gmc.aper_size);

		/* Add an MTRR क्रम the VRAM */
		adev->gmc.vram_mtrr = arch_phys_wc_add(adev->gmc.aper_base,
				adev->gmc.aper_size);
	पूर्ण

	DRM_INFO("Detected VRAM RAM=%lluM, BAR=%lluM\n",
		 adev->gmc.mc_vram_size >> 20,
		 (अचिन्हित दीर्घ दीर्घ)adev->gmc.aper_size >> 20);
	DRM_INFO("RAM width %dbits %s\n",
		 adev->gmc.vram_width, amdgpu_vram_names[adev->gmc.vram_type]);
	वापस amdgpu_tपंचांग_init(adev);
पूर्ण

/**
 * amdgpu_bo_fini - tear करोwn memory manager
 * @adev: amdgpu device object
 *
 * Reverses amdgpu_bo_init() to tear करोwn memory manager.
 */
व्योम amdgpu_bo_fini(काष्ठा amdgpu_device *adev)
अणु
	amdgpu_tपंचांग_fini(adev);
	अगर (!adev->gmc.xgmi.connected_to_cpu) अणु
		arch_phys_wc_del(adev->gmc.vram_mtrr);
		arch_io_मुक्त_memtype_wc(adev->gmc.aper_base, adev->gmc.aper_size);
	पूर्ण
पूर्ण

/**
 * amdgpu_bo_set_tiling_flags - set tiling flags
 * @bo: &amdgpu_bo buffer object
 * @tiling_flags: new flags
 *
 * Sets buffer object's tiling flags with the new one. Used by GEM ioctl or
 * kernel driver to set the tiling flags on a buffer.
 *
 * Returns:
 * 0 क्रम success or a negative error code on failure.
 */
पूर्णांक amdgpu_bo_set_tiling_flags(काष्ठा amdgpu_bo *bo, u64 tiling_flags)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);
	काष्ठा amdgpu_bo_user *ubo;

	BUG_ON(bo->tbo.type == tपंचांग_bo_type_kernel);
	अगर (adev->family <= AMDGPU_FAMILY_CZ &&
	    AMDGPU_TILING_GET(tiling_flags, TILE_SPLIT) > 6)
		वापस -EINVAL;

	ubo = to_amdgpu_bo_user(bo);
	ubo->tiling_flags = tiling_flags;
	वापस 0;
पूर्ण

/**
 * amdgpu_bo_get_tiling_flags - get tiling flags
 * @bo: &amdgpu_bo buffer object
 * @tiling_flags: वापसed flags
 *
 * Gets buffer object's tiling flags. Used by GEM ioctl or kernel driver to
 * set the tiling flags on a buffer.
 */
व्योम amdgpu_bo_get_tiling_flags(काष्ठा amdgpu_bo *bo, u64 *tiling_flags)
अणु
	काष्ठा amdgpu_bo_user *ubo;

	BUG_ON(bo->tbo.type == tपंचांग_bo_type_kernel);
	dma_resv_निश्चित_held(bo->tbo.base.resv);
	ubo = to_amdgpu_bo_user(bo);

	अगर (tiling_flags)
		*tiling_flags = ubo->tiling_flags;
पूर्ण

/**
 * amdgpu_bo_set_metadata - set metadata
 * @bo: &amdgpu_bo buffer object
 * @metadata: new metadata
 * @metadata_size: size of the new metadata
 * @flags: flags of the new metadata
 *
 * Sets buffer object's metadata, its size and flags.
 * Used via GEM ioctl.
 *
 * Returns:
 * 0 क्रम success or a negative error code on failure.
 */
पूर्णांक amdgpu_bo_set_metadata (काष्ठा amdgpu_bo *bo, व्योम *metadata,
			    uपूर्णांक32_t metadata_size, uपूर्णांक64_t flags)
अणु
	काष्ठा amdgpu_bo_user *ubo;
	व्योम *buffer;

	BUG_ON(bo->tbo.type == tपंचांग_bo_type_kernel);
	ubo = to_amdgpu_bo_user(bo);
	अगर (!metadata_size) अणु
		अगर (ubo->metadata_size) अणु
			kमुक्त(ubo->metadata);
			ubo->metadata = शून्य;
			ubo->metadata_size = 0;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (metadata == शून्य)
		वापस -EINVAL;

	buffer = kmemdup(metadata, metadata_size, GFP_KERNEL);
	अगर (buffer == शून्य)
		वापस -ENOMEM;

	kमुक्त(ubo->metadata);
	ubo->metadata_flags = flags;
	ubo->metadata = buffer;
	ubo->metadata_size = metadata_size;

	वापस 0;
पूर्ण

/**
 * amdgpu_bo_get_metadata - get metadata
 * @bo: &amdgpu_bo buffer object
 * @buffer: वापसed metadata
 * @buffer_size: size of the buffer
 * @metadata_size: size of the वापसed metadata
 * @flags: flags of the वापसed metadata
 *
 * Gets buffer object's metadata, its size and flags. buffer_size shall not be
 * less than metadata_size.
 * Used via GEM ioctl.
 *
 * Returns:
 * 0 क्रम success or a negative error code on failure.
 */
पूर्णांक amdgpu_bo_get_metadata(काष्ठा amdgpu_bo *bo, व्योम *buffer,
			   माप_प्रकार buffer_size, uपूर्णांक32_t *metadata_size,
			   uपूर्णांक64_t *flags)
अणु
	काष्ठा amdgpu_bo_user *ubo;

	अगर (!buffer && !metadata_size)
		वापस -EINVAL;

	BUG_ON(bo->tbo.type == tपंचांग_bo_type_kernel);
	ubo = to_amdgpu_bo_user(bo);
	अगर (buffer) अणु
		अगर (buffer_size < ubo->metadata_size)
			वापस -EINVAL;

		अगर (ubo->metadata_size)
			स_नकल(buffer, ubo->metadata, ubo->metadata_size);
	पूर्ण

	अगर (metadata_size)
		*metadata_size = ubo->metadata_size;
	अगर (flags)
		*flags = ubo->metadata_flags;

	वापस 0;
पूर्ण

/**
 * amdgpu_bo_move_notअगरy - notअगरication about a memory move
 * @bo: poपूर्णांकer to a buffer object
 * @evict: अगर this move is evicting the buffer from the graphics address space
 * @new_mem: new inक्रमmation of the bufer object
 *
 * Marks the corresponding &amdgpu_bo buffer object as invalid, also perक्रमms
 * bookkeeping.
 * TTM driver callback which is called when tपंचांग moves a buffer.
 */
व्योम amdgpu_bo_move_notअगरy(काष्ठा tपंचांग_buffer_object *bo,
			   bool evict,
			   काष्ठा tपंचांग_resource *new_mem)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->bdev);
	काष्ठा amdgpu_bo *abo;
	काष्ठा tपंचांग_resource *old_mem = &bo->mem;

	अगर (!amdgpu_bo_is_amdgpu_bo(bo))
		वापस;

	abo = tपंचांग_to_amdgpu_bo(bo);
	amdgpu_vm_bo_invalidate(adev, abo, evict);

	amdgpu_bo_kunmap(abo);

	अगर (abo->tbo.base.dma_buf && !abo->tbo.base.import_attach &&
	    bo->mem.mem_type != TTM_PL_SYSTEM)
		dma_buf_move_notअगरy(abo->tbo.base.dma_buf);

	/* remember the eviction */
	अगर (evict)
		atomic64_inc(&adev->num_evictions);

	/* update statistics */
	अगर (!new_mem)
		वापस;

	/* move_notअगरy is called beक्रमe move happens */
	trace_amdgpu_bo_move(abo, new_mem->mem_type, old_mem->mem_type);
पूर्ण

/**
 * amdgpu_bo_release_notअगरy - notअगरication about a BO being released
 * @bo: poपूर्णांकer to a buffer object
 *
 * Wipes VRAM buffers whose contents should not be leaked beक्रमe the
 * memory is released.
 */
व्योम amdgpu_bo_release_notअगरy(काष्ठा tपंचांग_buffer_object *bo)
अणु
	काष्ठा dma_fence *fence = शून्य;
	काष्ठा amdgpu_bo *abo;
	पूर्णांक r;

	अगर (!amdgpu_bo_is_amdgpu_bo(bo))
		वापस;

	abo = tपंचांग_to_amdgpu_bo(bo);

	अगर (abo->kfd_bo)
		amdgpu_amdkfd_unreserve_memory_limit(abo);

	/* We only हटाओ the fence अगर the resv has inभागidualized. */
	WARN_ON_ONCE(bo->type == tपंचांग_bo_type_kernel
			&& bo->base.resv != &bo->base._resv);
	अगर (bo->base.resv == &bo->base._resv)
		amdgpu_amdkfd_हटाओ_fence_on_pt_pd_bos(abo);

	अगर (bo->mem.mem_type != TTM_PL_VRAM || !bo->mem.mm_node ||
	    !(abo->flags & AMDGPU_GEM_CREATE_VRAM_WIPE_ON_RELEASE))
		वापस;

	dma_resv_lock(bo->base.resv, शून्य);

	r = amdgpu_fill_buffer(abo, AMDGPU_POISON, bo->base.resv, &fence);
	अगर (!WARN_ON(r)) अणु
		amdgpu_bo_fence(abo, fence, false);
		dma_fence_put(fence);
	पूर्ण

	dma_resv_unlock(bo->base.resv);
पूर्ण

/**
 * amdgpu_bo_fault_reserve_notअगरy - notअगरication about a memory fault
 * @bo: poपूर्णांकer to a buffer object
 *
 * Notअगरies the driver we are taking a fault on this BO and have reserved it,
 * also perक्रमms bookkeeping.
 * TTM driver callback क्रम dealing with vm faults.
 *
 * Returns:
 * 0 क्रम success or a negative error code on failure.
 */
vm_fault_t amdgpu_bo_fault_reserve_notअगरy(काष्ठा tपंचांग_buffer_object *bo)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->bdev);
	काष्ठा tपंचांग_operation_ctx ctx = अणु false, false पूर्ण;
	काष्ठा amdgpu_bo *abo = tपंचांग_to_amdgpu_bo(bo);
	अचिन्हित दीर्घ offset, size;
	पूर्णांक r;

	/* Remember that this BO was accessed by the CPU */
	abo->flags |= AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED;

	अगर (bo->mem.mem_type != TTM_PL_VRAM)
		वापस 0;

	size = bo->mem.num_pages << PAGE_SHIFT;
	offset = bo->mem.start << PAGE_SHIFT;
	अगर ((offset + size) <= adev->gmc.visible_vram_size)
		वापस 0;

	/* Can't move a pinned BO to visible VRAM */
	अगर (abo->tbo.pin_count > 0)
		वापस VM_FAULT_SIGBUS;

	/* hurrah the memory is not visible ! */
	atomic64_inc(&adev->num_vram_cpu_page_faults);
	amdgpu_bo_placement_from_करोमुख्य(abo, AMDGPU_GEM_DOMAIN_VRAM |
					AMDGPU_GEM_DOMAIN_GTT);

	/* Aव्योम costly evictions; only set GTT as a busy placement */
	abo->placement.num_busy_placement = 1;
	abo->placement.busy_placement = &abo->placements[1];

	r = tपंचांग_bo_validate(bo, &abo->placement, &ctx);
	अगर (unlikely(r == -EBUSY || r == -ERESTARTSYS))
		वापस VM_FAULT_NOPAGE;
	अन्यथा अगर (unlikely(r))
		वापस VM_FAULT_SIGBUS;

	offset = bo->mem.start << PAGE_SHIFT;
	/* this should never happen */
	अगर (bo->mem.mem_type == TTM_PL_VRAM &&
	    (offset + size) > adev->gmc.visible_vram_size)
		वापस VM_FAULT_SIGBUS;

	tपंचांग_bo_move_to_lru_tail_unlocked(bo);
	वापस 0;
पूर्ण

/**
 * amdgpu_bo_fence - add fence to buffer object
 *
 * @bo: buffer object in question
 * @fence: fence to add
 * @shared: true अगर fence should be added shared
 *
 */
व्योम amdgpu_bo_fence(काष्ठा amdgpu_bo *bo, काष्ठा dma_fence *fence,
		     bool shared)
अणु
	काष्ठा dma_resv *resv = bo->tbo.base.resv;

	अगर (shared)
		dma_resv_add_shared_fence(resv, fence);
	अन्यथा
		dma_resv_add_excl_fence(resv, fence);
पूर्ण

/**
 * amdgpu_bo_sync_रुको_resv - Wait क्रम BO reservation fences
 *
 * @adev: amdgpu device poपूर्णांकer
 * @resv: reservation object to sync to
 * @sync_mode: synchronization mode
 * @owner: fence owner
 * @पूर्णांकr: Whether the रुको is पूर्णांकerruptible
 *
 * Extract the fences from the reservation object and रुकोs क्रम them to finish.
 *
 * Returns:
 * 0 on success, त्रुटि_सं otherwise.
 */
पूर्णांक amdgpu_bo_sync_रुको_resv(काष्ठा amdgpu_device *adev, काष्ठा dma_resv *resv,
			     क्रमागत amdgpu_sync_mode sync_mode, व्योम *owner,
			     bool पूर्णांकr)
अणु
	काष्ठा amdgpu_sync sync;
	पूर्णांक r;

	amdgpu_sync_create(&sync);
	amdgpu_sync_resv(adev, &sync, resv, sync_mode, owner);
	r = amdgpu_sync_रुको(&sync, पूर्णांकr);
	amdgpu_sync_मुक्त(&sync);
	वापस r;
पूर्ण

/**
 * amdgpu_bo_sync_रुको - Wrapper क्रम amdgpu_bo_sync_रुको_resv
 * @bo: buffer object to रुको क्रम
 * @owner: fence owner
 * @पूर्णांकr: Whether the रुको is पूर्णांकerruptible
 *
 * Wrapper to रुको क्रम fences in a BO.
 * Returns:
 * 0 on success, त्रुटि_सं otherwise.
 */
पूर्णांक amdgpu_bo_sync_रुको(काष्ठा amdgpu_bo *bo, व्योम *owner, bool पूर्णांकr)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);

	वापस amdgpu_bo_sync_रुको_resv(adev, bo->tbo.base.resv,
					AMDGPU_SYNC_NE_OWNER, owner, पूर्णांकr);
पूर्ण

/**
 * amdgpu_bo_gpu_offset - वापस GPU offset of bo
 * @bo:	amdgpu object क्रम which we query the offset
 *
 * Note: object should either be pinned or reserved when calling this
 * function, it might be useful to add check क्रम this क्रम debugging.
 *
 * Returns:
 * current GPU offset of the object.
 */
u64 amdgpu_bo_gpu_offset(काष्ठा amdgpu_bo *bo)
अणु
	WARN_ON_ONCE(bo->tbo.mem.mem_type == TTM_PL_SYSTEM);
	WARN_ON_ONCE(!dma_resv_is_locked(bo->tbo.base.resv) &&
		     !bo->tbo.pin_count && bo->tbo.type != tपंचांग_bo_type_kernel);
	WARN_ON_ONCE(bo->tbo.mem.start == AMDGPU_BO_INVALID_OFFSET);
	WARN_ON_ONCE(bo->tbo.mem.mem_type == TTM_PL_VRAM &&
		     !(bo->flags & AMDGPU_GEM_CREATE_VRAM_CONTIGUOUS));

	वापस amdgpu_bo_gpu_offset_no_check(bo);
पूर्ण

/**
 * amdgpu_bo_gpu_offset_no_check - वापस GPU offset of bo
 * @bo:	amdgpu object क्रम which we query the offset
 *
 * Returns:
 * current GPU offset of the object without raising warnings.
 */
u64 amdgpu_bo_gpu_offset_no_check(काष्ठा amdgpu_bo *bo)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);
	uपूर्णांक64_t offset;

	offset = (bo->tbo.mem.start << PAGE_SHIFT) +
		 amdgpu_tपंचांग_करोमुख्य_start(adev, bo->tbo.mem.mem_type);

	वापस amdgpu_gmc_sign_extend(offset);
पूर्ण

/**
 * amdgpu_bo_get_preferred_pin_करोमुख्य - get preferred करोमुख्य क्रम scanout
 * @adev: amdgpu device object
 * @करोमुख्य: allowed :ref:`memory करोमुख्यs <amdgpu_memory_करोमुख्यs>`
 *
 * Returns:
 * Which of the allowed करोमुख्यs is preferred क्रम pinning the BO क्रम scanout.
 */
uपूर्णांक32_t amdgpu_bo_get_preferred_pin_करोमुख्य(काष्ठा amdgpu_device *adev,
					    uपूर्णांक32_t करोमुख्य)
अणु
	अगर (करोमुख्य == (AMDGPU_GEM_DOMAIN_VRAM | AMDGPU_GEM_DOMAIN_GTT)) अणु
		करोमुख्य = AMDGPU_GEM_DOMAIN_VRAM;
		अगर (adev->gmc.real_vram_size <= AMDGPU_SG_THRESHOLD)
			करोमुख्य = AMDGPU_GEM_DOMAIN_GTT;
	पूर्ण
	वापस करोमुख्य;
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)
#घोषणा amdgpu_bo_prपूर्णांक_flag(m, bo, flag)		        \
	करो अणु							\
		अगर (bo->flags & (AMDGPU_GEM_CREATE_ ## flag)) अणु	\
			seq_म_लिखो((m), " " #flag);		\
		पूर्ण						\
	पूर्ण जबतक (0)

/**
 * amdgpu_bo_prपूर्णांक_info - prपूर्णांक BO info in debugfs file
 *
 * @id: Index or Id of the BO
 * @bo: Requested BO क्रम prपूर्णांकing info
 * @m: debugfs file
 *
 * Prपूर्णांक BO inक्रमmation in debugfs file
 *
 * Returns:
 * Size of the BO in bytes.
 */
u64 amdgpu_bo_prपूर्णांक_info(पूर्णांक id, काष्ठा amdgpu_bo *bo, काष्ठा seq_file *m)
अणु
	काष्ठा dma_buf_attachment *attachment;
	काष्ठा dma_buf *dma_buf;
	अचिन्हित पूर्णांक करोमुख्य;
	स्थिर अक्षर *placement;
	अचिन्हित पूर्णांक pin_count;
	u64 size;

	करोमुख्य = amdgpu_mem_type_to_करोमुख्य(bo->tbo.mem.mem_type);
	चयन (करोमुख्य) अणु
	हाल AMDGPU_GEM_DOMAIN_VRAM:
		placement = "VRAM";
		अवरोध;
	हाल AMDGPU_GEM_DOMAIN_GTT:
		placement = " GTT";
		अवरोध;
	हाल AMDGPU_GEM_DOMAIN_CPU:
	शेष:
		placement = " CPU";
		अवरोध;
	पूर्ण

	size = amdgpu_bo_size(bo);
	seq_म_लिखो(m, "\t\t0x%08x: %12lld byte %s",
			id, size, placement);

	pin_count = READ_ONCE(bo->tbo.pin_count);
	अगर (pin_count)
		seq_म_लिखो(m, " pin count %d", pin_count);

	dma_buf = READ_ONCE(bo->tbo.base.dma_buf);
	attachment = READ_ONCE(bo->tbo.base.import_attach);

	अगर (attachment)
		seq_म_लिखो(m, " imported from %p", dma_buf);
	अन्यथा अगर (dma_buf)
		seq_म_लिखो(m, " exported as %p", dma_buf);

	amdgpu_bo_prपूर्णांक_flag(m, bo, CPU_ACCESS_REQUIRED);
	amdgpu_bo_prपूर्णांक_flag(m, bo, NO_CPU_ACCESS);
	amdgpu_bo_prपूर्णांक_flag(m, bo, CPU_GTT_USWC);
	amdgpu_bo_prपूर्णांक_flag(m, bo, VRAM_CLEARED);
	amdgpu_bo_prपूर्णांक_flag(m, bo, SHADOW);
	amdgpu_bo_prपूर्णांक_flag(m, bo, VRAM_CONTIGUOUS);
	amdgpu_bo_prपूर्णांक_flag(m, bo, VM_ALWAYS_VALID);
	amdgpu_bo_prपूर्णांक_flag(m, bo, EXPLICIT_SYNC);

	seq_माला_दो(m, "\n");

	वापस size;
पूर्ण
#पूर्ण_अगर
