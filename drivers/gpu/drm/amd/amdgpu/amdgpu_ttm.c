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

#समावेश <linux/dma-mapping.h>
#समावेश <linux/iommu.h>
#समावेश <linux/hmm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/swap.h>
#समावेश <linux/swiotlb.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/sizes.h>

#समावेश <drm/tपंचांग/tपंचांग_bo_api.h>
#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>
#समावेश <drm/tपंचांग/tपंचांग_placement.h>

#समावेश <drm/amdgpu_drm.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_object.h"
#समावेश "amdgpu_trace.h"
#समावेश "amdgpu_amdkfd.h"
#समावेश "amdgpu_sdma.h"
#समावेश "amdgpu_ras.h"
#समावेश "amdgpu_atomfirmware.h"
#समावेश "amdgpu_res_cursor.h"
#समावेश "bif/bif_4_1_d.h"

#घोषणा AMDGPU_TTM_VRAM_MAX_DW_READ	(माप_प्रकार)128

अटल पूर्णांक amdgpu_tपंचांग_backend_bind(काष्ठा tपंचांग_device *bdev,
				   काष्ठा tपंचांग_tt *tपंचांग,
				   काष्ठा tपंचांग_resource *bo_mem);
अटल व्योम amdgpu_tपंचांग_backend_unbind(काष्ठा tपंचांग_device *bdev,
				      काष्ठा tपंचांग_tt *tपंचांग);

अटल पूर्णांक amdgpu_tपंचांग_init_on_chip(काष्ठा amdgpu_device *adev,
				    अचिन्हित पूर्णांक type,
				    uपूर्णांक64_t size_in_page)
अणु
	वापस tपंचांग_range_man_init(&adev->mman.bdev, type,
				  false, size_in_page);
पूर्ण

/**
 * amdgpu_evict_flags - Compute placement flags
 *
 * @bo: The buffer object to evict
 * @placement: Possible destination(s) क्रम evicted BO
 *
 * Fill in placement data when tपंचांग_bo_evict() is called
 */
अटल व्योम amdgpu_evict_flags(काष्ठा tपंचांग_buffer_object *bo,
				काष्ठा tपंचांग_placement *placement)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->bdev);
	काष्ठा amdgpu_bo *abo;
	अटल स्थिर काष्ठा tपंचांग_place placements = अणु
		.fpfn = 0,
		.lpfn = 0,
		.mem_type = TTM_PL_SYSTEM,
		.flags = 0
	पूर्ण;

	/* Don't handle scatter gather BOs */
	अगर (bo->type == tपंचांग_bo_type_sg) अणु
		placement->num_placement = 0;
		placement->num_busy_placement = 0;
		वापस;
	पूर्ण

	/* Object isn't an AMDGPU object so ignore */
	अगर (!amdgpu_bo_is_amdgpu_bo(bo)) अणु
		placement->placement = &placements;
		placement->busy_placement = &placements;
		placement->num_placement = 1;
		placement->num_busy_placement = 1;
		वापस;
	पूर्ण

	abo = tपंचांग_to_amdgpu_bo(bo);
	चयन (bo->mem.mem_type) अणु
	हाल AMDGPU_PL_GDS:
	हाल AMDGPU_PL_GWS:
	हाल AMDGPU_PL_OA:
		placement->num_placement = 0;
		placement->num_busy_placement = 0;
		वापस;

	हाल TTM_PL_VRAM:
		अगर (!adev->mman.buffer_funcs_enabled) अणु
			/* Move to प्रणाली memory */
			amdgpu_bo_placement_from_करोमुख्य(abo, AMDGPU_GEM_DOMAIN_CPU);
		पूर्ण अन्यथा अगर (!amdgpu_gmc_vram_full_visible(&adev->gmc) &&
			   !(abo->flags & AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED) &&
			   amdgpu_bo_in_cpu_visible_vram(abo)) अणु

			/* Try evicting to the CPU inaccessible part of VRAM
			 * first, but only set GTT as busy placement, so this
			 * BO will be evicted to GTT rather than causing other
			 * BOs to be evicted from VRAM
			 */
			amdgpu_bo_placement_from_करोमुख्य(abo, AMDGPU_GEM_DOMAIN_VRAM |
							 AMDGPU_GEM_DOMAIN_GTT);
			abo->placements[0].fpfn = adev->gmc.visible_vram_size >> PAGE_SHIFT;
			abo->placements[0].lpfn = 0;
			abo->placement.busy_placement = &abo->placements[1];
			abo->placement.num_busy_placement = 1;
		पूर्ण अन्यथा अणु
			/* Move to GTT memory */
			amdgpu_bo_placement_from_करोमुख्य(abo, AMDGPU_GEM_DOMAIN_GTT);
		पूर्ण
		अवरोध;
	हाल TTM_PL_TT:
	शेष:
		amdgpu_bo_placement_from_करोमुख्य(abo, AMDGPU_GEM_DOMAIN_CPU);
		अवरोध;
	पूर्ण
	*placement = abo->placement;
पूर्ण

/**
 * amdgpu_verअगरy_access - Verअगरy access क्रम a mmap call
 *
 * @bo:	The buffer object to map
 * @filp: The file poपूर्णांकer from the process perक्रमming the mmap
 *
 * This is called by tपंचांग_bo_mmap() to verअगरy whether a process
 * has the right to mmap a BO to their process space.
 */
अटल पूर्णांक amdgpu_verअगरy_access(काष्ठा tपंचांग_buffer_object *bo, काष्ठा file *filp)
अणु
	काष्ठा amdgpu_bo *abo = tपंचांग_to_amdgpu_bo(bo);

	/*
	 * Don't verify access for KFD BOs. They don't have a GEM
	 * object associated with them.
	 */
	अगर (abo->kfd_bo)
		वापस 0;

	अगर (amdgpu_tपंचांग_tt_get_usermm(bo->tपंचांग))
		वापस -EPERM;
	वापस drm_vma_node_verअगरy_access(&abo->tbo.base.vma_node,
					  filp->निजी_data);
पूर्ण

/**
 * amdgpu_tपंचांग_map_buffer - Map memory पूर्णांकo the GART winकरोws
 * @bo: buffer object to map
 * @mem: memory object to map
 * @mm_cur: range to map
 * @num_pages: number of pages to map
 * @winकरोw: which GART winकरोw to use
 * @ring: DMA ring to use क्रम the copy
 * @पंचांगz: अगर we should setup a TMZ enabled mapping
 * @addr: resulting address inside the MC address space
 *
 * Setup one of the GART winकरोws to access a specअगरic piece of memory or वापस
 * the physical address क्रम local memory.
 */
अटल पूर्णांक amdgpu_tपंचांग_map_buffer(काष्ठा tपंचांग_buffer_object *bo,
				 काष्ठा tपंचांग_resource *mem,
				 काष्ठा amdgpu_res_cursor *mm_cur,
				 अचिन्हित num_pages, अचिन्हित winकरोw,
				 काष्ठा amdgpu_ring *ring, bool पंचांगz,
				 uपूर्णांक64_t *addr)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	काष्ठा amdgpu_job *job;
	अचिन्हित num_dw, num_bytes;
	काष्ठा dma_fence *fence;
	uपूर्णांक64_t src_addr, dst_addr;
	व्योम *cpu_addr;
	uपूर्णांक64_t flags;
	अचिन्हित पूर्णांक i;
	पूर्णांक r;

	BUG_ON(adev->mman.buffer_funcs->copy_max_bytes <
	       AMDGPU_GTT_MAX_TRANSFER_SIZE * 8);

	/* Map only what can't be accessed directly */
	अगर (!पंचांगz && mem->start != AMDGPU_BO_INVALID_OFFSET) अणु
		*addr = amdgpu_tपंचांग_करोमुख्य_start(adev, mem->mem_type) +
			mm_cur->start;
		वापस 0;
	पूर्ण

	*addr = adev->gmc.gart_start;
	*addr += (u64)winकरोw * AMDGPU_GTT_MAX_TRANSFER_SIZE *
		AMDGPU_GPU_PAGE_SIZE;
	*addr += mm_cur->start & ~PAGE_MASK;

	num_dw = ALIGN(adev->mman.buffer_funcs->copy_num_dw, 8);
	num_bytes = num_pages * 8 * AMDGPU_GPU_PAGES_IN_CPU_PAGE;

	r = amdgpu_job_alloc_with_ib(adev, num_dw * 4 + num_bytes,
				     AMDGPU_IB_POOL_DELAYED, &job);
	अगर (r)
		वापस r;

	src_addr = num_dw * 4;
	src_addr += job->ibs[0].gpu_addr;

	dst_addr = amdgpu_bo_gpu_offset(adev->gart.bo);
	dst_addr += winकरोw * AMDGPU_GTT_MAX_TRANSFER_SIZE * 8;
	amdgpu_emit_copy_buffer(adev, &job->ibs[0], src_addr,
				dst_addr, num_bytes, false);

	amdgpu_ring_pad_ib(ring, &job->ibs[0]);
	WARN_ON(job->ibs[0].length_dw > num_dw);

	flags = amdgpu_tपंचांग_tt_pte_flags(adev, bo->tपंचांग, mem);
	अगर (पंचांगz)
		flags |= AMDGPU_PTE_TMZ;

	cpu_addr = &job->ibs[0].ptr[num_dw];

	अगर (mem->mem_type == TTM_PL_TT) अणु
		dma_addr_t *dma_addr;

		dma_addr = &bo->tपंचांग->dma_address[mm_cur->start >> PAGE_SHIFT];
		r = amdgpu_gart_map(adev, 0, num_pages, dma_addr, flags,
				    cpu_addr);
		अगर (r)
			जाओ error_मुक्त;
	पूर्ण अन्यथा अणु
		dma_addr_t dma_address;

		dma_address = mm_cur->start;
		dma_address += adev->vm_manager.vram_base_offset;

		क्रम (i = 0; i < num_pages; ++i) अणु
			r = amdgpu_gart_map(adev, i << PAGE_SHIFT, 1,
					    &dma_address, flags, cpu_addr);
			अगर (r)
				जाओ error_मुक्त;

			dma_address += PAGE_SIZE;
		पूर्ण
	पूर्ण

	r = amdgpu_job_submit(job, &adev->mman.entity,
			      AMDGPU_FENCE_OWNER_UNDEFINED, &fence);
	अगर (r)
		जाओ error_मुक्त;

	dma_fence_put(fence);

	वापस r;

error_मुक्त:
	amdgpu_job_मुक्त(job);
	वापस r;
पूर्ण

/**
 * amdgpu_copy_tपंचांग_mem_to_mem - Helper function क्रम copy
 * @adev: amdgpu device
 * @src: buffer/address where to पढ़ो from
 * @dst: buffer/address where to ग_लिखो to
 * @size: number of bytes to copy
 * @पंचांगz: अगर a secure copy should be used
 * @resv: resv object to sync to
 * @f: Returns the last fence अगर multiple jobs are submitted.
 *
 * The function copies @size bytes from अणुsrc->mem + src->offsetपूर्ण to
 * अणुdst->mem + dst->offsetपूर्ण. src->bo and dst->bo could be same BO क्रम a
 * move and dअगरferent क्रम a BO to BO copy.
 *
 */
पूर्णांक amdgpu_tपंचांग_copy_mem_to_mem(काष्ठा amdgpu_device *adev,
			       स्थिर काष्ठा amdgpu_copy_mem *src,
			       स्थिर काष्ठा amdgpu_copy_mem *dst,
			       uपूर्णांक64_t size, bool पंचांगz,
			       काष्ठा dma_resv *resv,
			       काष्ठा dma_fence **f)
अणु
	स्थिर uपूर्णांक32_t GTT_MAX_BYTES = (AMDGPU_GTT_MAX_TRANSFER_SIZE *
					AMDGPU_GPU_PAGE_SIZE);

	काष्ठा amdgpu_ring *ring = adev->mman.buffer_funcs_ring;
	काष्ठा amdgpu_res_cursor src_mm, dst_mm;
	काष्ठा dma_fence *fence = शून्य;
	पूर्णांक r = 0;

	अगर (!adev->mman.buffer_funcs_enabled) अणु
		DRM_ERROR("Trying to move memory with ring turned off.\n");
		वापस -EINVAL;
	पूर्ण

	amdgpu_res_first(src->mem, src->offset, size, &src_mm);
	amdgpu_res_first(dst->mem, dst->offset, size, &dst_mm);

	mutex_lock(&adev->mman.gtt_winकरोw_lock);
	जबतक (src_mm.reमुख्यing) अणु
		uपूर्णांक32_t src_page_offset = src_mm.start & ~PAGE_MASK;
		uपूर्णांक32_t dst_page_offset = dst_mm.start & ~PAGE_MASK;
		काष्ठा dma_fence *next;
		uपूर्णांक32_t cur_size;
		uपूर्णांक64_t from, to;

		/* Copy size cannot exceed GTT_MAX_BYTES. So अगर src or dst
		 * begins at an offset, then adjust the size accordingly
		 */
		cur_size = max(src_page_offset, dst_page_offset);
		cur_size = min(min3(src_mm.size, dst_mm.size, size),
			       (uपूर्णांक64_t)(GTT_MAX_BYTES - cur_size));

		/* Map src to winकरोw 0 and dst to winकरोw 1. */
		r = amdgpu_tपंचांग_map_buffer(src->bo, src->mem, &src_mm,
					  PFN_UP(cur_size + src_page_offset),
					  0, ring, पंचांगz, &from);
		अगर (r)
			जाओ error;

		r = amdgpu_tपंचांग_map_buffer(dst->bo, dst->mem, &dst_mm,
					  PFN_UP(cur_size + dst_page_offset),
					  1, ring, पंचांगz, &to);
		अगर (r)
			जाओ error;

		r = amdgpu_copy_buffer(ring, from, to, cur_size,
				       resv, &next, false, true, पंचांगz);
		अगर (r)
			जाओ error;

		dma_fence_put(fence);
		fence = next;

		amdgpu_res_next(&src_mm, cur_size);
		amdgpu_res_next(&dst_mm, cur_size);
	पूर्ण
error:
	mutex_unlock(&adev->mman.gtt_winकरोw_lock);
	अगर (f)
		*f = dma_fence_get(fence);
	dma_fence_put(fence);
	वापस r;
पूर्ण

/*
 * amdgpu_move_blit - Copy an entire buffer to another buffer
 *
 * This is a helper called by amdgpu_bo_move() and amdgpu_move_vram_ram() to
 * help move buffers to and from VRAM.
 */
अटल पूर्णांक amdgpu_move_blit(काष्ठा tपंचांग_buffer_object *bo,
			    bool evict,
			    काष्ठा tपंचांग_resource *new_mem,
			    काष्ठा tपंचांग_resource *old_mem)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->bdev);
	काष्ठा amdgpu_bo *abo = tपंचांग_to_amdgpu_bo(bo);
	काष्ठा amdgpu_copy_mem src, dst;
	काष्ठा dma_fence *fence = शून्य;
	पूर्णांक r;

	src.bo = bo;
	dst.bo = bo;
	src.mem = old_mem;
	dst.mem = new_mem;
	src.offset = 0;
	dst.offset = 0;

	r = amdgpu_tपंचांग_copy_mem_to_mem(adev, &src, &dst,
				       new_mem->num_pages << PAGE_SHIFT,
				       amdgpu_bo_encrypted(abo),
				       bo->base.resv, &fence);
	अगर (r)
		जाओ error;

	/* clear the space being मुक्तd */
	अगर (old_mem->mem_type == TTM_PL_VRAM &&
	    (abo->flags & AMDGPU_GEM_CREATE_VRAM_WIPE_ON_RELEASE)) अणु
		काष्ठा dma_fence *wipe_fence = शून्य;

		r = amdgpu_fill_buffer(tपंचांग_to_amdgpu_bo(bo), AMDGPU_POISON,
				       शून्य, &wipe_fence);
		अगर (r) अणु
			जाओ error;
		पूर्ण अन्यथा अगर (wipe_fence) अणु
			dma_fence_put(fence);
			fence = wipe_fence;
		पूर्ण
	पूर्ण

	/* Always block क्रम VM page tables beक्रमe committing the new location */
	अगर (bo->type == tपंचांग_bo_type_kernel)
		r = tपंचांग_bo_move_accel_cleanup(bo, fence, true, false, new_mem);
	अन्यथा
		r = tपंचांग_bo_move_accel_cleanup(bo, fence, evict, true, new_mem);
	dma_fence_put(fence);
	वापस r;

error:
	अगर (fence)
		dma_fence_रुको(fence, false);
	dma_fence_put(fence);
	वापस r;
पूर्ण

/*
 * amdgpu_mem_visible - Check that memory can be accessed by tपंचांग_bo_move_स_नकल
 *
 * Called by amdgpu_bo_move()
 */
अटल bool amdgpu_mem_visible(काष्ठा amdgpu_device *adev,
			       काष्ठा tपंचांग_resource *mem)
अणु
	uपूर्णांक64_t mem_size = (u64)mem->num_pages << PAGE_SHIFT;
	काष्ठा amdgpu_res_cursor cursor;

	अगर (mem->mem_type == TTM_PL_SYSTEM ||
	    mem->mem_type == TTM_PL_TT)
		वापस true;
	अगर (mem->mem_type != TTM_PL_VRAM)
		वापस false;

	amdgpu_res_first(mem, 0, mem_size, &cursor);

	/* tपंचांग_resource_ioremap only supports contiguous memory */
	अगर (cursor.size != mem_size)
		वापस false;

	वापस cursor.start + cursor.size <= adev->gmc.visible_vram_size;
पूर्ण

/*
 * amdgpu_bo_move - Move a buffer object to a new memory location
 *
 * Called by tपंचांग_bo_handle_move_mem()
 */
अटल पूर्णांक amdgpu_bo_move(काष्ठा tपंचांग_buffer_object *bo, bool evict,
			  काष्ठा tपंचांग_operation_ctx *ctx,
			  काष्ठा tपंचांग_resource *new_mem,
			  काष्ठा tपंचांग_place *hop)
अणु
	काष्ठा amdgpu_device *adev;
	काष्ठा amdgpu_bo *abo;
	काष्ठा tपंचांग_resource *old_mem = &bo->mem;
	पूर्णांक r;

	अगर (new_mem->mem_type == TTM_PL_TT) अणु
		r = amdgpu_tपंचांग_backend_bind(bo->bdev, bo->tपंचांग, new_mem);
		अगर (r)
			वापस r;
	पूर्ण

	/* Can't move a pinned BO */
	abo = tपंचांग_to_amdgpu_bo(bo);
	अगर (WARN_ON_ONCE(abo->tbo.pin_count > 0))
		वापस -EINVAL;

	adev = amdgpu_tपंचांग_adev(bo->bdev);

	अगर (old_mem->mem_type == TTM_PL_SYSTEM && bo->tपंचांग == शून्य) अणु
		tपंचांग_bo_move_null(bo, new_mem);
		जाओ out;
	पूर्ण
	अगर (old_mem->mem_type == TTM_PL_SYSTEM &&
	    new_mem->mem_type == TTM_PL_TT) अणु
		tपंचांग_bo_move_null(bo, new_mem);
		जाओ out;
	पूर्ण
	अगर (old_mem->mem_type == TTM_PL_TT &&
	    new_mem->mem_type == TTM_PL_SYSTEM) अणु
		r = tपंचांग_bo_रुको_ctx(bo, ctx);
		अगर (r)
			वापस r;

		amdgpu_tपंचांग_backend_unbind(bo->bdev, bo->tपंचांग);
		tपंचांग_resource_मुक्त(bo, &bo->mem);
		tपंचांग_bo_assign_mem(bo, new_mem);
		जाओ out;
	पूर्ण

	अगर (old_mem->mem_type == AMDGPU_PL_GDS ||
	    old_mem->mem_type == AMDGPU_PL_GWS ||
	    old_mem->mem_type == AMDGPU_PL_OA ||
	    new_mem->mem_type == AMDGPU_PL_GDS ||
	    new_mem->mem_type == AMDGPU_PL_GWS ||
	    new_mem->mem_type == AMDGPU_PL_OA) अणु
		/* Nothing to save here */
		tपंचांग_bo_move_null(bo, new_mem);
		जाओ out;
	पूर्ण

	अगर (adev->mman.buffer_funcs_enabled) अणु
		अगर (((old_mem->mem_type == TTM_PL_SYSTEM &&
		      new_mem->mem_type == TTM_PL_VRAM) ||
		     (old_mem->mem_type == TTM_PL_VRAM &&
		      new_mem->mem_type == TTM_PL_SYSTEM))) अणु
			hop->fpfn = 0;
			hop->lpfn = 0;
			hop->mem_type = TTM_PL_TT;
			hop->flags = 0;
			वापस -EMULTIHOP;
		पूर्ण

		r = amdgpu_move_blit(bo, evict, new_mem, old_mem);
	पूर्ण अन्यथा अणु
		r = -ENODEV;
	पूर्ण

	अगर (r) अणु
		/* Check that all memory is CPU accessible */
		अगर (!amdgpu_mem_visible(adev, old_mem) ||
		    !amdgpu_mem_visible(adev, new_mem)) अणु
			pr_err("Move buffer fallback to memcpy unavailable\n");
			वापस r;
		पूर्ण

		r = tपंचांग_bo_move_स_नकल(bo, ctx, new_mem);
		अगर (r)
			वापस r;
	पूर्ण

	अगर (bo->type == tपंचांग_bo_type_device &&
	    new_mem->mem_type == TTM_PL_VRAM &&
	    old_mem->mem_type != TTM_PL_VRAM) अणु
		/* amdgpu_bo_fault_reserve_notअगरy will re-set this अगर the CPU
		 * accesses the BO after it's moved.
		 */
		abo->flags &= ~AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED;
	पूर्ण

out:
	/* update statistics */
	atomic64_add(bo->base.size, &adev->num_bytes_moved);
	amdgpu_bo_move_notअगरy(bo, evict, new_mem);
	वापस 0;
पूर्ण

/*
 * amdgpu_tपंचांग_io_mem_reserve - Reserve a block of memory during a fault
 *
 * Called by tपंचांग_mem_io_reserve() ultimately via tपंचांग_bo_vm_fault()
 */
अटल पूर्णांक amdgpu_tपंचांग_io_mem_reserve(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_resource *mem)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bdev);
	काष्ठा drm_mm_node *mm_node = mem->mm_node;
	माप_प्रकार bus_size = (माप_प्रकार)mem->num_pages << PAGE_SHIFT;

	चयन (mem->mem_type) अणु
	हाल TTM_PL_SYSTEM:
		/* प्रणाली memory */
		वापस 0;
	हाल TTM_PL_TT:
		अवरोध;
	हाल TTM_PL_VRAM:
		mem->bus.offset = mem->start << PAGE_SHIFT;
		/* check अगर it's visible */
		अगर ((mem->bus.offset + bus_size) > adev->gmc.visible_vram_size)
			वापस -EINVAL;
		/* Only physically contiguous buffers apply. In a contiguous
		 * buffer, size of the first mm_node would match the number of
		 * pages in tपंचांग_resource.
		 */
		अगर (adev->mman.aper_base_kaddr &&
		    (mm_node->size == mem->num_pages))
			mem->bus.addr = (u8 *)adev->mman.aper_base_kaddr +
					mem->bus.offset;

		mem->bus.offset += adev->gmc.aper_base;
		mem->bus.is_iomem = true;
		अगर (adev->gmc.xgmi.connected_to_cpu)
			mem->bus.caching = tपंचांग_cached;
		अन्यथा
			mem->bus.caching = tपंचांग_ग_लिखो_combined;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ amdgpu_tपंचांग_io_mem_pfn(काष्ठा tपंचांग_buffer_object *bo,
					   अचिन्हित दीर्घ page_offset)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->bdev);
	काष्ठा amdgpu_res_cursor cursor;

	amdgpu_res_first(&bo->mem, (u64)page_offset << PAGE_SHIFT, 0, &cursor);
	वापस (adev->gmc.aper_base + cursor.start) >> PAGE_SHIFT;
पूर्ण

/**
 * amdgpu_tपंचांग_करोमुख्य_start - Returns GPU start address
 * @adev: amdgpu device object
 * @type: type of the memory
 *
 * Returns:
 * GPU start address of a memory करोमुख्य
 */

uपूर्णांक64_t amdgpu_tपंचांग_करोमुख्य_start(काष्ठा amdgpu_device *adev, uपूर्णांक32_t type)
अणु
	चयन (type) अणु
	हाल TTM_PL_TT:
		वापस adev->gmc.gart_start;
	हाल TTM_PL_VRAM:
		वापस adev->gmc.vram_start;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * TTM backend functions.
 */
काष्ठा amdgpu_tपंचांग_tt अणु
	काष्ठा tपंचांग_tt	tपंचांग;
	काष्ठा drm_gem_object	*gobj;
	u64			offset;
	uपूर्णांक64_t		userptr;
	काष्ठा task_काष्ठा	*usertask;
	uपूर्णांक32_t		userflags;
	bool			bound;
#अगर IS_ENABLED(CONFIG_DRM_AMDGPU_USERPTR)
	काष्ठा hmm_range	*range;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_DRM_AMDGPU_USERPTR
/*
 * amdgpu_tपंचांग_tt_get_user_pages - get device accessible pages that back user
 * memory and start HMM tracking CPU page table update
 *
 * Calling function must call amdgpu_tपंचांग_tt_userptr_range_करोne() once and only
 * once afterwards to stop HMM tracking
 */
पूर्णांक amdgpu_tपंचांग_tt_get_user_pages(काष्ठा amdgpu_bo *bo, काष्ठा page **pages)
अणु
	काष्ठा tपंचांग_tt *tपंचांग = bo->tbo.tपंचांग;
	काष्ठा amdgpu_tपंचांग_tt *gtt = (व्योम *)tपंचांग;
	अचिन्हित दीर्घ start = gtt->userptr;
	काष्ठा vm_area_काष्ठा *vma;
	काष्ठा hmm_range *range;
	अचिन्हित दीर्घ समयout;
	काष्ठा mm_काष्ठा *mm;
	अचिन्हित दीर्घ i;
	पूर्णांक r = 0;

	mm = bo->notअगरier.mm;
	अगर (unlikely(!mm)) अणु
		DRM_DEBUG_DRIVER("BO is not registered?\n");
		वापस -EFAULT;
	पूर्ण

	/* Another get_user_pages is running at the same समय?? */
	अगर (WARN_ON(gtt->range))
		वापस -EFAULT;

	अगर (!mmget_not_zero(mm)) /* Happens during process shutकरोwn */
		वापस -ESRCH;

	range = kzalloc(माप(*range), GFP_KERNEL);
	अगर (unlikely(!range)) अणु
		r = -ENOMEM;
		जाओ out;
	पूर्ण
	range->notअगरier = &bo->notअगरier;
	range->start = bo->notअगरier.पूर्णांकerval_tree.start;
	range->end = bo->notअगरier.पूर्णांकerval_tree.last + 1;
	range->शेष_flags = HMM_PFN_REQ_FAULT;
	अगर (!amdgpu_tपंचांग_tt_is_पढ़ोonly(tपंचांग))
		range->शेष_flags |= HMM_PFN_REQ_WRITE;

	range->hmm_pfns = kvदो_स्मृति_array(tपंचांग->num_pages,
					 माप(*range->hmm_pfns), GFP_KERNEL);
	अगर (unlikely(!range->hmm_pfns)) अणु
		r = -ENOMEM;
		जाओ out_मुक्त_ranges;
	पूर्ण

	mmap_पढ़ो_lock(mm);
	vma = find_vma(mm, start);
	अगर (unlikely(!vma || start < vma->vm_start)) अणु
		r = -EFAULT;
		जाओ out_unlock;
	पूर्ण
	अगर (unlikely((gtt->userflags & AMDGPU_GEM_USERPTR_ANONONLY) &&
		vma->vm_file)) अणु
		r = -EPERM;
		जाओ out_unlock;
	पूर्ण
	mmap_पढ़ो_unlock(mm);
	समयout = jअगरfies + msecs_to_jअगरfies(HMM_RANGE_DEFAULT_TIMEOUT);

retry:
	range->notअगरier_seq = mmu_पूर्णांकerval_पढ़ो_begin(&bo->notअगरier);

	mmap_पढ़ो_lock(mm);
	r = hmm_range_fault(range);
	mmap_पढ़ो_unlock(mm);
	अगर (unlikely(r)) अणु
		/*
		 * FIXME: This समयout should encompass the retry from
		 * mmu_पूर्णांकerval_पढ़ो_retry() as well.
		 */
		अगर (r == -EBUSY && !समय_after(jअगरfies, समयout))
			जाओ retry;
		जाओ out_मुक्त_pfns;
	पूर्ण

	/*
	 * Due to शेष_flags, all pages are HMM_PFN_VALID or
	 * hmm_range_fault() fails. FIXME: The pages cannot be touched outside
	 * the notअगरier_lock, and mmu_पूर्णांकerval_पढ़ो_retry() must be करोne first.
	 */
	क्रम (i = 0; i < tपंचांग->num_pages; i++)
		pages[i] = hmm_pfn_to_page(range->hmm_pfns[i]);

	gtt->range = range;
	mmput(mm);

	वापस 0;

out_unlock:
	mmap_पढ़ो_unlock(mm);
out_मुक्त_pfns:
	kvमुक्त(range->hmm_pfns);
out_मुक्त_ranges:
	kमुक्त(range);
out:
	mmput(mm);
	वापस r;
पूर्ण

/*
 * amdgpu_tपंचांग_tt_userptr_range_करोne - stop HMM track the CPU page table change
 * Check अगर the pages backing this tपंचांग range have been invalidated
 *
 * Returns: true अगर pages are still valid
 */
bool amdgpu_tपंचांग_tt_get_user_pages_करोne(काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा amdgpu_tपंचांग_tt *gtt = (व्योम *)tपंचांग;
	bool r = false;

	अगर (!gtt || !gtt->userptr)
		वापस false;

	DRM_DEBUG_DRIVER("user_pages_done 0x%llx pages 0x%x\n",
		gtt->userptr, tपंचांग->num_pages);

	WARN_ONCE(!gtt->range || !gtt->range->hmm_pfns,
		"No user pages to check\n");

	अगर (gtt->range) अणु
		/*
		 * FIXME: Must always hold notअगरier_lock क्रम this, and must
		 * not ignore the वापस code.
		 */
		r = mmu_पूर्णांकerval_पढ़ो_retry(gtt->range->notअगरier,
					 gtt->range->notअगरier_seq);
		kvमुक्त(gtt->range->hmm_pfns);
		kमुक्त(gtt->range);
		gtt->range = शून्य;
	पूर्ण

	वापस !r;
पूर्ण
#पूर्ण_अगर

/*
 * amdgpu_tपंचांग_tt_set_user_pages - Copy pages in, putting old pages as necessary.
 *
 * Called by amdgpu_cs_list_validate(). This creates the page list
 * that backs user memory and will ultimately be mapped पूर्णांकo the device
 * address space.
 */
व्योम amdgpu_tपंचांग_tt_set_user_pages(काष्ठा tपंचांग_tt *tपंचांग, काष्ठा page **pages)
अणु
	अचिन्हित दीर्घ i;

	क्रम (i = 0; i < tपंचांग->num_pages; ++i)
		tपंचांग->pages[i] = pages ? pages[i] : शून्य;
पूर्ण

/*
 * amdgpu_tपंचांग_tt_pin_userptr - prepare the sg table with the user pages
 *
 * Called by amdgpu_tपंचांग_backend_bind()
 **/
अटल पूर्णांक amdgpu_tपंचांग_tt_pin_userptr(काष्ठा tपंचांग_device *bdev,
				     काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bdev);
	काष्ठा amdgpu_tपंचांग_tt *gtt = (व्योम *)tपंचांग;
	पूर्णांक ग_लिखो = !(gtt->userflags & AMDGPU_GEM_USERPTR_READONLY);
	क्रमागत dma_data_direction direction = ग_लिखो ?
		DMA_BIसूचीECTIONAL : DMA_TO_DEVICE;
	पूर्णांक r;

	/* Allocate an SG array and squash pages पूर्णांकo it */
	r = sg_alloc_table_from_pages(tपंचांग->sg, tपंचांग->pages, tपंचांग->num_pages, 0,
				      (u64)tपंचांग->num_pages << PAGE_SHIFT,
				      GFP_KERNEL);
	अगर (r)
		जाओ release_sg;

	/* Map SG to device */
	r = dma_map_sgtable(adev->dev, tपंचांग->sg, direction, 0);
	अगर (r)
		जाओ release_sg;

	/* convert SG to linear array of pages and dma addresses */
	drm_prime_sg_to_dma_addr_array(tपंचांग->sg, gtt->tपंचांग.dma_address,
				       tपंचांग->num_pages);

	वापस 0;

release_sg:
	kमुक्त(tपंचांग->sg);
	tपंचांग->sg = शून्य;
	वापस r;
पूर्ण

/*
 * amdgpu_tपंचांग_tt_unpin_userptr - Unpin and unmap userptr pages
 */
अटल व्योम amdgpu_tपंचांग_tt_unpin_userptr(काष्ठा tपंचांग_device *bdev,
					काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bdev);
	काष्ठा amdgpu_tपंचांग_tt *gtt = (व्योम *)tपंचांग;
	पूर्णांक ग_लिखो = !(gtt->userflags & AMDGPU_GEM_USERPTR_READONLY);
	क्रमागत dma_data_direction direction = ग_लिखो ?
		DMA_BIसूचीECTIONAL : DMA_TO_DEVICE;

	/* द्विगुन check that we करोn't मुक्त the table twice */
	अगर (!tपंचांग->sg || !tपंचांग->sg->sgl)
		वापस;

	/* unmap the pages mapped to the device */
	dma_unmap_sgtable(adev->dev, tपंचांग->sg, direction, 0);
	sg_मुक्त_table(tपंचांग->sg);

#अगर IS_ENABLED(CONFIG_DRM_AMDGPU_USERPTR)
	अगर (gtt->range) अणु
		अचिन्हित दीर्घ i;

		क्रम (i = 0; i < tपंचांग->num_pages; i++) अणु
			अगर (tपंचांग->pages[i] !=
			    hmm_pfn_to_page(gtt->range->hmm_pfns[i]))
				अवरोध;
		पूर्ण

		WARN((i == tपंचांग->num_pages), "Missing get_user_page_done\n");
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक amdgpu_tपंचांग_gart_bind(काष्ठा amdgpu_device *adev,
				काष्ठा tपंचांग_buffer_object *tbo,
				uपूर्णांक64_t flags)
अणु
	काष्ठा amdgpu_bo *abo = tपंचांग_to_amdgpu_bo(tbo);
	काष्ठा tपंचांग_tt *tपंचांग = tbo->tपंचांग;
	काष्ठा amdgpu_tपंचांग_tt *gtt = (व्योम *)tपंचांग;
	पूर्णांक r;

	अगर (amdgpu_bo_encrypted(abo))
		flags |= AMDGPU_PTE_TMZ;

	अगर (abo->flags & AMDGPU_GEM_CREATE_CP_MQD_GFX9) अणु
		uपूर्णांक64_t page_idx = 1;

		r = amdgpu_gart_bind(adev, gtt->offset, page_idx,
				tपंचांग->pages, gtt->tपंचांग.dma_address, flags);
		अगर (r)
			जाओ gart_bind_fail;

		/* The memory type of the first page शेषs to UC. Now
		 * modअगरy the memory type to NC from the second page of
		 * the BO onward.
		 */
		flags &= ~AMDGPU_PTE_MTYPE_VG10_MASK;
		flags |= AMDGPU_PTE_MTYPE_VG10(AMDGPU_MTYPE_NC);

		r = amdgpu_gart_bind(adev,
				gtt->offset + (page_idx << PAGE_SHIFT),
				tपंचांग->num_pages - page_idx,
				&tपंचांग->pages[page_idx],
				&(gtt->tपंचांग.dma_address[page_idx]), flags);
	पूर्ण अन्यथा अणु
		r = amdgpu_gart_bind(adev, gtt->offset, tपंचांग->num_pages,
				     tपंचांग->pages, gtt->tपंचांग.dma_address, flags);
	पूर्ण

gart_bind_fail:
	अगर (r)
		DRM_ERROR("failed to bind %u pages at 0x%08llX\n",
			  tपंचांग->num_pages, gtt->offset);

	वापस r;
पूर्ण

/*
 * amdgpu_tपंचांग_backend_bind - Bind GTT memory
 *
 * Called by tपंचांग_tt_bind() on behalf of tपंचांग_bo_handle_move_mem().
 * This handles binding GTT memory to the device address space.
 */
अटल पूर्णांक amdgpu_tपंचांग_backend_bind(काष्ठा tपंचांग_device *bdev,
				   काष्ठा tपंचांग_tt *tपंचांग,
				   काष्ठा tपंचांग_resource *bo_mem)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bdev);
	काष्ठा amdgpu_tपंचांग_tt *gtt = (व्योम*)tपंचांग;
	uपूर्णांक64_t flags;
	पूर्णांक r = 0;

	अगर (!bo_mem)
		वापस -EINVAL;

	अगर (gtt->bound)
		वापस 0;

	अगर (gtt->userptr) अणु
		r = amdgpu_tपंचांग_tt_pin_userptr(bdev, tपंचांग);
		अगर (r) अणु
			DRM_ERROR("failed to pin userptr\n");
			वापस r;
		पूर्ण
	पूर्ण
	अगर (!tपंचांग->num_pages) अणु
		WARN(1, "nothing to bind %u pages for mreg %p back %p!\n",
		     tपंचांग->num_pages, bo_mem, tपंचांग);
	पूर्ण

	अगर (bo_mem->mem_type == AMDGPU_PL_GDS ||
	    bo_mem->mem_type == AMDGPU_PL_GWS ||
	    bo_mem->mem_type == AMDGPU_PL_OA)
		वापस -EINVAL;

	अगर (!amdgpu_gtt_mgr_has_gart_addr(bo_mem)) अणु
		gtt->offset = AMDGPU_BO_INVALID_OFFSET;
		वापस 0;
	पूर्ण

	/* compute PTE flags relevant to this BO memory */
	flags = amdgpu_tपंचांग_tt_pte_flags(adev, tपंचांग, bo_mem);

	/* bind pages पूर्णांकo GART page tables */
	gtt->offset = (u64)bo_mem->start << PAGE_SHIFT;
	r = amdgpu_gart_bind(adev, gtt->offset, tपंचांग->num_pages,
		tपंचांग->pages, gtt->tपंचांग.dma_address, flags);

	अगर (r)
		DRM_ERROR("failed to bind %u pages at 0x%08llX\n",
			  tपंचांग->num_pages, gtt->offset);
	gtt->bound = true;
	वापस r;
पूर्ण

/*
 * amdgpu_tपंचांग_alloc_gart - Make sure buffer object is accessible either
 * through AGP or GART aperture.
 *
 * If bo is accessible through AGP aperture, then use AGP aperture
 * to access bo; otherwise allocate logical space in GART aperture
 * and map bo to GART aperture.
 */
पूर्णांक amdgpu_tपंचांग_alloc_gart(काष्ठा tपंचांग_buffer_object *bo)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->bdev);
	काष्ठा tपंचांग_operation_ctx ctx = अणु false, false पूर्ण;
	काष्ठा amdgpu_tपंचांग_tt *gtt = (व्योम *)bo->tपंचांग;
	काष्ठा tपंचांग_resource पंचांगp;
	काष्ठा tपंचांग_placement placement;
	काष्ठा tपंचांग_place placements;
	uपूर्णांक64_t addr, flags;
	पूर्णांक r;

	अगर (bo->mem.start != AMDGPU_BO_INVALID_OFFSET)
		वापस 0;

	addr = amdgpu_gmc_agp_addr(bo);
	अगर (addr != AMDGPU_BO_INVALID_OFFSET) अणु
		bo->mem.start = addr >> PAGE_SHIFT;
	पूर्ण अन्यथा अणु

		/* allocate GART space */
		पंचांगp = bo->mem;
		पंचांगp.mm_node = शून्य;
		placement.num_placement = 1;
		placement.placement = &placements;
		placement.num_busy_placement = 1;
		placement.busy_placement = &placements;
		placements.fpfn = 0;
		placements.lpfn = adev->gmc.gart_size >> PAGE_SHIFT;
		placements.mem_type = TTM_PL_TT;
		placements.flags = bo->mem.placement;

		r = tपंचांग_bo_mem_space(bo, &placement, &पंचांगp, &ctx);
		अगर (unlikely(r))
			वापस r;

		/* compute PTE flags क्रम this buffer object */
		flags = amdgpu_tपंचांग_tt_pte_flags(adev, bo->tपंचांग, &पंचांगp);

		/* Bind pages */
		gtt->offset = (u64)पंचांगp.start << PAGE_SHIFT;
		r = amdgpu_tपंचांग_gart_bind(adev, bo, flags);
		अगर (unlikely(r)) अणु
			tपंचांग_resource_मुक्त(bo, &पंचांगp);
			वापस r;
		पूर्ण

		tपंचांग_resource_मुक्त(bo, &bo->mem);
		bo->mem = पंचांगp;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * amdgpu_tपंचांग_recover_gart - Rebind GTT pages
 *
 * Called by amdgpu_gtt_mgr_recover() from amdgpu_device_reset() to
 * rebind GTT pages during a GPU reset.
 */
पूर्णांक amdgpu_tपंचांग_recover_gart(काष्ठा tपंचांग_buffer_object *tbo)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(tbo->bdev);
	uपूर्णांक64_t flags;
	पूर्णांक r;

	अगर (!tbo->tपंचांग)
		वापस 0;

	flags = amdgpu_tपंचांग_tt_pte_flags(adev, tbo->tपंचांग, &tbo->mem);
	r = amdgpu_tपंचांग_gart_bind(adev, tbo, flags);

	वापस r;
पूर्ण

/*
 * amdgpu_tपंचांग_backend_unbind - Unbind GTT mapped pages
 *
 * Called by tपंचांग_tt_unbind() on behalf of tपंचांग_bo_move_tपंचांग() and
 * tपंचांग_tt_destroy().
 */
अटल व्योम amdgpu_tपंचांग_backend_unbind(काष्ठा tपंचांग_device *bdev,
				      काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bdev);
	काष्ठा amdgpu_tपंचांग_tt *gtt = (व्योम *)tपंचांग;
	पूर्णांक r;

	/* अगर the pages have userptr pinning then clear that first */
	अगर (gtt->userptr)
		amdgpu_tपंचांग_tt_unpin_userptr(bdev, tपंचांग);

	अगर (!gtt->bound)
		वापस;

	अगर (gtt->offset == AMDGPU_BO_INVALID_OFFSET)
		वापस;

	/* unbind shouldn't be करोne क्रम GDS/GWS/OA in tपंचांग_bo_clean_mm */
	r = amdgpu_gart_unbind(adev, gtt->offset, tपंचांग->num_pages);
	अगर (r)
		DRM_ERROR("failed to unbind %u pages at 0x%08llX\n",
			  gtt->tपंचांग.num_pages, gtt->offset);
	gtt->bound = false;
पूर्ण

अटल व्योम amdgpu_tपंचांग_backend_destroy(काष्ठा tपंचांग_device *bdev,
				       काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा amdgpu_tपंचांग_tt *gtt = (व्योम *)tपंचांग;

	amdgpu_tपंचांग_backend_unbind(bdev, tपंचांग);
	tपंचांग_tt_destroy_common(bdev, tपंचांग);
	अगर (gtt->usertask)
		put_task_काष्ठा(gtt->usertask);

	tपंचांग_tt_fini(&gtt->tपंचांग);
	kमुक्त(gtt);
पूर्ण

/**
 * amdgpu_tपंचांग_tt_create - Create a tपंचांग_tt object क्रम a given BO
 *
 * @bo: The buffer object to create a GTT tपंचांग_tt object around
 * @page_flags: Page flags to be added to the tपंचांग_tt object
 *
 * Called by tपंचांग_tt_create().
 */
अटल काष्ठा tपंचांग_tt *amdgpu_tपंचांग_tt_create(काष्ठा tपंचांग_buffer_object *bo,
					   uपूर्णांक32_t page_flags)
अणु
	काष्ठा amdgpu_bo *abo = tपंचांग_to_amdgpu_bo(bo);
	काष्ठा amdgpu_tपंचांग_tt *gtt;
	क्रमागत tपंचांग_caching caching;

	gtt = kzalloc(माप(काष्ठा amdgpu_tपंचांग_tt), GFP_KERNEL);
	अगर (gtt == शून्य) अणु
		वापस शून्य;
	पूर्ण
	gtt->gobj = &bo->base;

	अगर (abo->flags & AMDGPU_GEM_CREATE_CPU_GTT_USWC)
		caching = tपंचांग_ग_लिखो_combined;
	अन्यथा
		caching = tपंचांग_cached;

	/* allocate space क्रम the uninitialized page entries */
	अगर (tपंचांग_sg_tt_init(&gtt->tपंचांग, bo, page_flags, caching)) अणु
		kमुक्त(gtt);
		वापस शून्य;
	पूर्ण
	वापस &gtt->tपंचांग;
पूर्ण

/*
 * amdgpu_tपंचांग_tt_populate - Map GTT pages visible to the device
 *
 * Map the pages of a tपंचांग_tt object to an address space visible
 * to the underlying device.
 */
अटल पूर्णांक amdgpu_tपंचांग_tt_populate(काष्ठा tपंचांग_device *bdev,
				  काष्ठा tपंचांग_tt *tपंचांग,
				  काष्ठा tपंचांग_operation_ctx *ctx)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bdev);
	काष्ठा amdgpu_tपंचांग_tt *gtt = (व्योम *)tपंचांग;

	/* user pages are bound by amdgpu_tपंचांग_tt_pin_userptr() */
	अगर (gtt && gtt->userptr) अणु
		tपंचांग->sg = kzalloc(माप(काष्ठा sg_table), GFP_KERNEL);
		अगर (!tपंचांग->sg)
			वापस -ENOMEM;

		tपंचांग->page_flags |= TTM_PAGE_FLAG_SG;
		वापस 0;
	पूर्ण

	अगर (tपंचांग->page_flags & TTM_PAGE_FLAG_SG) अणु
		अगर (!tपंचांग->sg) अणु
			काष्ठा dma_buf_attachment *attach;
			काष्ठा sg_table *sgt;

			attach = gtt->gobj->import_attach;
			sgt = dma_buf_map_attachment(attach, DMA_BIसूचीECTIONAL);
			अगर (IS_ERR(sgt))
				वापस PTR_ERR(sgt);

			tपंचांग->sg = sgt;
		पूर्ण

		drm_prime_sg_to_dma_addr_array(tपंचांग->sg, gtt->tपंचांग.dma_address,
					       tपंचांग->num_pages);
		वापस 0;
	पूर्ण

	वापस tपंचांग_pool_alloc(&adev->mman.bdev.pool, tपंचांग, ctx);
पूर्ण

/*
 * amdgpu_tपंचांग_tt_unpopulate - unmap GTT pages and unpopulate page arrays
 *
 * Unmaps pages of a tपंचांग_tt object from the device address space and
 * unpopulates the page array backing it.
 */
अटल व्योम amdgpu_tपंचांग_tt_unpopulate(काष्ठा tपंचांग_device *bdev,
				     काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा amdgpu_tपंचांग_tt *gtt = (व्योम *)tपंचांग;
	काष्ठा amdgpu_device *adev;

	अगर (gtt && gtt->userptr) अणु
		amdgpu_tपंचांग_tt_set_user_pages(tपंचांग, शून्य);
		kमुक्त(tपंचांग->sg);
		tपंचांग->sg = शून्य;
		tपंचांग->page_flags &= ~TTM_PAGE_FLAG_SG;
		वापस;
	पूर्ण

	अगर (tपंचांग->sg && gtt->gobj->import_attach) अणु
		काष्ठा dma_buf_attachment *attach;

		attach = gtt->gobj->import_attach;
		dma_buf_unmap_attachment(attach, tपंचांग->sg, DMA_BIसूचीECTIONAL);
		tपंचांग->sg = शून्य;
		वापस;
	पूर्ण

	अगर (tपंचांग->page_flags & TTM_PAGE_FLAG_SG)
		वापस;

	adev = amdgpu_tपंचांग_adev(bdev);
	वापस tपंचांग_pool_मुक्त(&adev->mman.bdev.pool, tपंचांग);
पूर्ण

/**
 * amdgpu_tपंचांग_tt_set_userptr - Initialize userptr GTT tपंचांग_tt क्रम the current
 * task
 *
 * @bo: The tपंचांग_buffer_object to bind this userptr to
 * @addr:  The address in the current tasks VM space to use
 * @flags: Requirements of userptr object.
 *
 * Called by amdgpu_gem_userptr_ioctl() to bind userptr pages
 * to current task
 */
पूर्णांक amdgpu_tपंचांग_tt_set_userptr(काष्ठा tपंचांग_buffer_object *bo,
			      uपूर्णांक64_t addr, uपूर्णांक32_t flags)
अणु
	काष्ठा amdgpu_tपंचांग_tt *gtt;

	अगर (!bo->tपंचांग) अणु
		/* TODO: We want a separate TTM object type क्रम userptrs */
		bo->tपंचांग = amdgpu_tपंचांग_tt_create(bo, 0);
		अगर (bo->tपंचांग == शून्य)
			वापस -ENOMEM;
	पूर्ण

	gtt = (व्योम *)bo->tपंचांग;
	gtt->userptr = addr;
	gtt->userflags = flags;

	अगर (gtt->usertask)
		put_task_काष्ठा(gtt->usertask);
	gtt->usertask = current->group_leader;
	get_task_काष्ठा(gtt->usertask);

	वापस 0;
पूर्ण

/*
 * amdgpu_tपंचांग_tt_get_usermm - Return memory manager क्रम tपंचांग_tt object
 */
काष्ठा mm_काष्ठा *amdgpu_tपंचांग_tt_get_usermm(काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा amdgpu_tपंचांग_tt *gtt = (व्योम *)tपंचांग;

	अगर (gtt == शून्य)
		वापस शून्य;

	अगर (gtt->usertask == शून्य)
		वापस शून्य;

	वापस gtt->usertask->mm;
पूर्ण

/*
 * amdgpu_tपंचांग_tt_affect_userptr - Determine अगर a tपंचांग_tt object lays inside an
 * address range क्रम the current task.
 *
 */
bool amdgpu_tपंचांग_tt_affect_userptr(काष्ठा tपंचांग_tt *tपंचांग, अचिन्हित दीर्घ start,
				  अचिन्हित दीर्घ end)
अणु
	काष्ठा amdgpu_tपंचांग_tt *gtt = (व्योम *)tपंचांग;
	अचिन्हित दीर्घ size;

	अगर (gtt == शून्य || !gtt->userptr)
		वापस false;

	/* Return false अगर no part of the tपंचांग_tt object lies within
	 * the range
	 */
	size = (अचिन्हित दीर्घ)gtt->tपंचांग.num_pages * PAGE_SIZE;
	अगर (gtt->userptr > end || gtt->userptr + size <= start)
		वापस false;

	वापस true;
पूर्ण

/*
 * amdgpu_tपंचांग_tt_is_userptr - Have the pages backing by userptr?
 */
bool amdgpu_tपंचांग_tt_is_userptr(काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा amdgpu_tपंचांग_tt *gtt = (व्योम *)tपंचांग;

	अगर (gtt == शून्य || !gtt->userptr)
		वापस false;

	वापस true;
पूर्ण

/*
 * amdgpu_tपंचांग_tt_is_पढ़ोonly - Is the tपंचांग_tt object पढ़ो only?
 */
bool amdgpu_tपंचांग_tt_is_पढ़ोonly(काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा amdgpu_tपंचांग_tt *gtt = (व्योम *)tपंचांग;

	अगर (gtt == शून्य)
		वापस false;

	वापस !!(gtt->userflags & AMDGPU_GEM_USERPTR_READONLY);
पूर्ण

/**
 * amdgpu_tपंचांग_tt_pde_flags - Compute PDE flags क्रम tपंचांग_tt object
 *
 * @tपंचांग: The tपंचांग_tt object to compute the flags क्रम
 * @mem: The memory registry backing this tपंचांग_tt object
 *
 * Figure out the flags to use क्रम a VM PDE (Page Directory Entry).
 */
uपूर्णांक64_t amdgpu_tपंचांग_tt_pde_flags(काष्ठा tपंचांग_tt *tपंचांग, काष्ठा tपंचांग_resource *mem)
अणु
	uपूर्णांक64_t flags = 0;

	अगर (mem && mem->mem_type != TTM_PL_SYSTEM)
		flags |= AMDGPU_PTE_VALID;

	अगर (mem && mem->mem_type == TTM_PL_TT) अणु
		flags |= AMDGPU_PTE_SYSTEM;

		अगर (tपंचांग->caching == tपंचांग_cached)
			flags |= AMDGPU_PTE_SNOOPED;
	पूर्ण

	अगर (mem && mem->mem_type == TTM_PL_VRAM &&
			mem->bus.caching == tपंचांग_cached)
		flags |= AMDGPU_PTE_SNOOPED;

	वापस flags;
पूर्ण

/**
 * amdgpu_tपंचांग_tt_pte_flags - Compute PTE flags क्रम tपंचांग_tt object
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @tपंचांग: The tपंचांग_tt object to compute the flags क्रम
 * @mem: The memory registry backing this tपंचांग_tt object
 *
 * Figure out the flags to use क्रम a VM PTE (Page Table Entry).
 */
uपूर्णांक64_t amdgpu_tपंचांग_tt_pte_flags(काष्ठा amdgpu_device *adev, काष्ठा tपंचांग_tt *tपंचांग,
				 काष्ठा tपंचांग_resource *mem)
अणु
	uपूर्णांक64_t flags = amdgpu_tपंचांग_tt_pde_flags(tपंचांग, mem);

	flags |= adev->gart.gart_pte_flags;
	flags |= AMDGPU_PTE_READABLE;

	अगर (!amdgpu_tपंचांग_tt_is_पढ़ोonly(tपंचांग))
		flags |= AMDGPU_PTE_WRITEABLE;

	वापस flags;
पूर्ण

/*
 * amdgpu_tपंचांग_bo_eviction_valuable - Check to see अगर we can evict a buffer
 * object.
 *
 * Return true अगर eviction is sensible. Called by tपंचांग_mem_evict_first() on
 * behalf of tपंचांग_bo_mem_क्रमce_space() which tries to evict buffer objects until
 * it can find space क्रम a new object and by tपंचांग_bo_क्रमce_list_clean() which is
 * used to clean out a memory space.
 */
अटल bool amdgpu_tपंचांग_bo_eviction_valuable(काष्ठा tपंचांग_buffer_object *bo,
					    स्थिर काष्ठा tपंचांग_place *place)
अणु
	अचिन्हित दीर्घ num_pages = bo->mem.num_pages;
	काष्ठा amdgpu_res_cursor cursor;
	काष्ठा dma_resv_list *flist;
	काष्ठा dma_fence *f;
	पूर्णांक i;

	अगर (bo->type == tपंचांग_bo_type_kernel &&
	    !amdgpu_vm_evictable(tपंचांग_to_amdgpu_bo(bo)))
		वापस false;

	/* If bo is a KFD BO, check अगर the bo beदीर्घs to the current process.
	 * If true, then वापस false as any KFD process needs all its BOs to
	 * be resident to run successfully
	 */
	flist = dma_resv_get_list(bo->base.resv);
	अगर (flist) अणु
		क्रम (i = 0; i < flist->shared_count; ++i) अणु
			f = rcu_dereference_रक्षित(flist->shared[i],
				dma_resv_held(bo->base.resv));
			अगर (amdkfd_fence_check_mm(f, current->mm))
				वापस false;
		पूर्ण
	पूर्ण

	चयन (bo->mem.mem_type) अणु
	हाल TTM_PL_TT:
		अगर (amdgpu_bo_is_amdgpu_bo(bo) &&
		    amdgpu_bo_encrypted(tपंचांग_to_amdgpu_bo(bo)))
			वापस false;
		वापस true;

	हाल TTM_PL_VRAM:
		/* Check each drm MM node inभागidually */
		amdgpu_res_first(&bo->mem, 0, (u64)num_pages << PAGE_SHIFT,
				 &cursor);
		जबतक (cursor.reमुख्यing) अणु
			अगर (place->fpfn < PFN_DOWN(cursor.start + cursor.size)
			    && !(place->lpfn &&
				 place->lpfn <= PFN_DOWN(cursor.start)))
				वापस true;

			amdgpu_res_next(&cursor, cursor.size);
		पूर्ण
		वापस false;

	शेष:
		अवरोध;
	पूर्ण

	वापस tपंचांग_bo_eviction_valuable(bo, place);
पूर्ण

/**
 * amdgpu_tपंचांग_access_memory - Read or Write memory that backs a buffer object.
 *
 * @bo:  The buffer object to पढ़ो/ग_लिखो
 * @offset:  Offset पूर्णांकo buffer object
 * @buf:  Secondary buffer to ग_लिखो/पढ़ो from
 * @len: Length in bytes of access
 * @ग_लिखो:  true अगर writing
 *
 * This is used to access VRAM that backs a buffer object via MMIO
 * access क्रम debugging purposes.
 */
अटल पूर्णांक amdgpu_tपंचांग_access_memory(काष्ठा tपंचांग_buffer_object *bo,
				    अचिन्हित दीर्घ offset, व्योम *buf, पूर्णांक len,
				    पूर्णांक ग_लिखो)
अणु
	काष्ठा amdgpu_bo *abo = tपंचांग_to_amdgpu_bo(bo);
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(abo->tbo.bdev);
	काष्ठा amdgpu_res_cursor cursor;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t value = 0;
	पूर्णांक ret = 0;

	अगर (bo->mem.mem_type != TTM_PL_VRAM)
		वापस -EIO;

	amdgpu_res_first(&bo->mem, offset, len, &cursor);
	जबतक (cursor.reमुख्यing) अणु
		uपूर्णांक64_t aligned_pos = cursor.start & ~(uपूर्णांक64_t)3;
		uपूर्णांक64_t bytes = 4 - (cursor.start & 3);
		uपूर्णांक32_t shअगरt = (cursor.start & 3) * 8;
		uपूर्णांक32_t mask = 0xffffffff << shअगरt;

		अगर (cursor.size < bytes) अणु
			mask &= 0xffffffff >> (bytes - cursor.size) * 8;
			bytes = cursor.size;
		पूर्ण

		अगर (mask != 0xffffffff) अणु
			spin_lock_irqsave(&adev->mmio_idx_lock, flags);
			WREG32_NO_KIQ(mmMM_INDEX, ((uपूर्णांक32_t)aligned_pos) | 0x80000000);
			WREG32_NO_KIQ(mmMM_INDEX_HI, aligned_pos >> 31);
			value = RREG32_NO_KIQ(mmMM_DATA);
			अगर (ग_लिखो) अणु
				value &= ~mask;
				value |= (*(uपूर्णांक32_t *)buf << shअगरt) & mask;
				WREG32_NO_KIQ(mmMM_DATA, value);
			पूर्ण
			spin_unlock_irqrestore(&adev->mmio_idx_lock, flags);
			अगर (!ग_लिखो) अणु
				value = (value & mask) >> shअगरt;
				स_नकल(buf, &value, bytes);
			पूर्ण
		पूर्ण अन्यथा अणु
			bytes = cursor.size & ~0x3ULL;
			amdgpu_device_vram_access(adev, cursor.start,
						  (uपूर्णांक32_t *)buf, bytes,
						  ग_लिखो);
		पूर्ण

		ret += bytes;
		buf = (uपूर्णांक8_t *)buf + bytes;
		amdgpu_res_next(&cursor, bytes);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम
amdgpu_bo_delete_mem_notअगरy(काष्ठा tपंचांग_buffer_object *bo)
अणु
	amdgpu_bo_move_notअगरy(bo, false, शून्य);
पूर्ण

अटल काष्ठा tपंचांग_device_funcs amdgpu_bo_driver = अणु
	.tपंचांग_tt_create = &amdgpu_tपंचांग_tt_create,
	.tपंचांग_tt_populate = &amdgpu_tपंचांग_tt_populate,
	.tपंचांग_tt_unpopulate = &amdgpu_tपंचांग_tt_unpopulate,
	.tपंचांग_tt_destroy = &amdgpu_tपंचांग_backend_destroy,
	.eviction_valuable = amdgpu_tपंचांग_bo_eviction_valuable,
	.evict_flags = &amdgpu_evict_flags,
	.move = &amdgpu_bo_move,
	.verअगरy_access = &amdgpu_verअगरy_access,
	.delete_mem_notअगरy = &amdgpu_bo_delete_mem_notअगरy,
	.release_notअगरy = &amdgpu_bo_release_notअगरy,
	.io_mem_reserve = &amdgpu_tपंचांग_io_mem_reserve,
	.io_mem_pfn = amdgpu_tपंचांग_io_mem_pfn,
	.access_memory = &amdgpu_tपंचांग_access_memory,
	.del_from_lru_notअगरy = &amdgpu_vm_del_from_lru_notअगरy
पूर्ण;

/*
 * Firmware Reservation functions
 */
/**
 * amdgpu_tपंचांग_fw_reserve_vram_fini - मुक्त fw reserved vram
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * मुक्त fw reserved vram अगर it has been reserved.
 */
अटल व्योम amdgpu_tपंचांग_fw_reserve_vram_fini(काष्ठा amdgpu_device *adev)
अणु
	amdgpu_bo_मुक्त_kernel(&adev->mman.fw_vram_usage_reserved_bo,
		शून्य, &adev->mman.fw_vram_usage_va);
पूर्ण

/**
 * amdgpu_tपंचांग_fw_reserve_vram_init - create bo vram reservation from fw
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * create bo vram reservation from fw.
 */
अटल पूर्णांक amdgpu_tपंचांग_fw_reserve_vram_init(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक64_t vram_size = adev->gmc.visible_vram_size;

	adev->mman.fw_vram_usage_va = शून्य;
	adev->mman.fw_vram_usage_reserved_bo = शून्य;

	अगर (adev->mman.fw_vram_usage_size == 0 ||
	    adev->mman.fw_vram_usage_size > vram_size)
		वापस 0;

	वापस amdgpu_bo_create_kernel_at(adev,
					  adev->mman.fw_vram_usage_start_offset,
					  adev->mman.fw_vram_usage_size,
					  AMDGPU_GEM_DOMAIN_VRAM,
					  &adev->mman.fw_vram_usage_reserved_bo,
					  &adev->mman.fw_vram_usage_va);
पूर्ण

/*
 * Memoy training reservation functions
 */

/**
 * amdgpu_tपंचांग_training_reserve_vram_fini - मुक्त memory training reserved vram
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * मुक्त memory training reserved vram अगर it has been reserved.
 */
अटल पूर्णांक amdgpu_tपंचांग_training_reserve_vram_fini(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा psp_memory_training_context *ctx = &adev->psp.mem_train_ctx;

	ctx->init = PSP_MEM_TRAIN_NOT_SUPPORT;
	amdgpu_bo_मुक्त_kernel(&ctx->c2p_bo, शून्य, शून्य);
	ctx->c2p_bo = शून्य;

	वापस 0;
पूर्ण

अटल व्योम amdgpu_tपंचांग_training_data_block_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा psp_memory_training_context *ctx = &adev->psp.mem_train_ctx;

	स_रखो(ctx, 0, माप(*ctx));

	ctx->c2p_train_data_offset =
		ALIGN((adev->gmc.mc_vram_size - adev->mman.discovery_पंचांगr_size - SZ_1M), SZ_1M);
	ctx->p2c_train_data_offset =
		(adev->gmc.mc_vram_size - GDDR6_MEM_TRAINING_OFFSET);
	ctx->train_data_size =
		GDDR6_MEM_TRAINING_DATA_SIZE_IN_BYTES;

	DRM_DEBUG("train_data_size:%llx,p2c_train_data_offset:%llx,c2p_train_data_offset:%llx.\n",
			ctx->train_data_size,
			ctx->p2c_train_data_offset,
			ctx->c2p_train_data_offset);
पूर्ण

/*
 * reserve TMR memory at the top of VRAM which holds
 * IP Discovery data and is रक्षित by PSP.
 */
अटल पूर्णांक amdgpu_tपंचांग_reserve_पंचांगr(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक ret;
	काष्ठा psp_memory_training_context *ctx = &adev->psp.mem_train_ctx;
	bool mem_train_support = false;

	अगर (!amdgpu_sriov_vf(adev)) अणु
		ret = amdgpu_mem_train_support(adev);
		अगर (ret == 1)
			mem_train_support = true;
		अन्यथा अगर (ret == -1)
			वापस -EINVAL;
		अन्यथा
			DRM_DEBUG("memory training does not support!\n");
	पूर्ण

	/*
	 * Query reserved पंचांगr size through atom firmwareinfo क्रम Sienna_Cichlid and onwards क्रम all
	 * the use हालs (IP discovery/G6 memory training/profiling/diagnostic data.etc)
	 *
	 * Otherwise, fallback to legacy approach to check and reserve पंचांगr block क्रम ip
	 * discovery data and G6 memory training data respectively
	 */
	adev->mman.discovery_पंचांगr_size =
		amdgpu_atomfirmware_get_fw_reserved_fb_size(adev);
	अगर (!adev->mman.discovery_पंचांगr_size)
		adev->mman.discovery_पंचांगr_size = DISCOVERY_TMR_OFFSET;

	अगर (mem_train_support) अणु
		/* reserve vram क्रम mem train according to TMR location */
		amdgpu_tपंचांग_training_data_block_init(adev);
		ret = amdgpu_bo_create_kernel_at(adev,
					 ctx->c2p_train_data_offset,
					 ctx->train_data_size,
					 AMDGPU_GEM_DOMAIN_VRAM,
					 &ctx->c2p_bo,
					 शून्य);
		अगर (ret) अणु
			DRM_ERROR("alloc c2p_bo failed(%d)!\n", ret);
			amdgpu_tपंचांग_training_reserve_vram_fini(adev);
			वापस ret;
		पूर्ण
		ctx->init = PSP_MEM_TRAIN_RESERVE_SUCCESS;
	पूर्ण

	ret = amdgpu_bo_create_kernel_at(adev,
				adev->gmc.real_vram_size - adev->mman.discovery_पंचांगr_size,
				adev->mman.discovery_पंचांगr_size,
				AMDGPU_GEM_DOMAIN_VRAM,
				&adev->mman.discovery_memory,
				शून्य);
	अगर (ret) अणु
		DRM_ERROR("alloc tmr failed(%d)!\n", ret);
		amdgpu_bo_मुक्त_kernel(&adev->mman.discovery_memory, शून्य, शून्य);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * amdgpu_tपंचांग_init - Init the memory management (tपंचांग) as well as various
 * gtt/vram related fields.
 *
 * This initializes all of the memory space pools that the TTM layer
 * will need such as the GTT space (प्रणाली memory mapped to the device),
 * VRAM (on-board memory), and on-chip memories (GDS, GWS, OA) which
 * can be mapped per VMID.
 */
पूर्णांक amdgpu_tपंचांग_init(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक64_t gtt_size;
	पूर्णांक r;
	u64 vis_vram_limit;

	mutex_init(&adev->mman.gtt_winकरोw_lock);

	/* No others user of address space so set it to 0 */
	r = tपंचांग_device_init(&adev->mman.bdev, &amdgpu_bo_driver, adev->dev,
			       adev_to_drm(adev)->anon_inode->i_mapping,
			       adev_to_drm(adev)->vma_offset_manager,
			       adev->need_swiotlb,
			       dma_addressing_limited(adev->dev));
	अगर (r) अणु
		DRM_ERROR("failed initializing buffer object driver(%d).\n", r);
		वापस r;
	पूर्ण
	adev->mman.initialized = true;

	/* Initialize VRAM pool with all of VRAM भागided पूर्णांकo pages */
	r = amdgpu_vram_mgr_init(adev);
	अगर (r) अणु
		DRM_ERROR("Failed initializing VRAM heap.\n");
		वापस r;
	पूर्ण

	/* Reduce size of CPU-visible VRAM अगर requested */
	vis_vram_limit = (u64)amdgpu_vis_vram_limit * 1024 * 1024;
	अगर (amdgpu_vis_vram_limit > 0 &&
	    vis_vram_limit <= adev->gmc.visible_vram_size)
		adev->gmc.visible_vram_size = vis_vram_limit;

	/* Change the size here instead of the init above so only lpfn is affected */
	amdgpu_tपंचांग_set_buffer_funcs_status(adev, false);
#अगर_घोषित CONFIG_64BIT
#अगर_घोषित CONFIG_X86
	अगर (adev->gmc.xgmi.connected_to_cpu)
		adev->mman.aper_base_kaddr = ioremap_cache(adev->gmc.aper_base,
				adev->gmc.visible_vram_size);

	अन्यथा
#पूर्ण_अगर
		adev->mman.aper_base_kaddr = ioremap_wc(adev->gmc.aper_base,
				adev->gmc.visible_vram_size);
#पूर्ण_अगर

	/*
	 *The reserved vram क्रम firmware must be pinned to the specअगरied
	 *place on the VRAM, so reserve it early.
	 */
	r = amdgpu_tपंचांग_fw_reserve_vram_init(adev);
	अगर (r) अणु
		वापस r;
	पूर्ण

	/*
	 * only NAVI10 and onwards ASIC support क्रम IP discovery.
	 * If IP discovery enabled, a block of memory should be
	 * reserved क्रम IP discovey.
	 */
	अगर (adev->mman.discovery_bin) अणु
		r = amdgpu_tपंचांग_reserve_पंचांगr(adev);
		अगर (r)
			वापस r;
	पूर्ण

	/* allocate memory as required क्रम VGA
	 * This is used क्रम VGA emulation and pre-OS scanout buffers to
	 * aव्योम display artअगरacts जबतक transitioning between pre-OS
	 * and driver.  */
	r = amdgpu_bo_create_kernel_at(adev, 0, adev->mman.stolen_vga_size,
				       AMDGPU_GEM_DOMAIN_VRAM,
				       &adev->mman.stolen_vga_memory,
				       शून्य);
	अगर (r)
		वापस r;
	r = amdgpu_bo_create_kernel_at(adev, adev->mman.stolen_vga_size,
				       adev->mman.stolen_extended_size,
				       AMDGPU_GEM_DOMAIN_VRAM,
				       &adev->mman.stolen_extended_memory,
				       शून्य);
	अगर (r)
		वापस r;

	DRM_INFO("amdgpu: %uM of VRAM memory ready\n",
		 (अचिन्हित) (adev->gmc.real_vram_size / (1024 * 1024)));

	/* Compute GTT size, either bsaed on 3/4th the size of RAM size
	 * or whatever the user passed on module init */
	अगर (amdgpu_gtt_size == -1) अणु
		काष्ठा sysinfo si;

		si_meminfo(&si);
		gtt_size = min(max((AMDGPU_DEFAULT_GTT_SIZE_MB << 20),
			       adev->gmc.mc_vram_size),
			       ((uपूर्णांक64_t)si.totalram * si.mem_unit * 3/4));
	पूर्ण
	अन्यथा
		gtt_size = (uपूर्णांक64_t)amdgpu_gtt_size << 20;

	/* Initialize GTT memory pool */
	r = amdgpu_gtt_mgr_init(adev, gtt_size);
	अगर (r) अणु
		DRM_ERROR("Failed initializing GTT heap.\n");
		वापस r;
	पूर्ण
	DRM_INFO("amdgpu: %uM of GTT memory ready.\n",
		 (अचिन्हित)(gtt_size / (1024 * 1024)));

	/* Initialize various on-chip memory pools */
	r = amdgpu_tपंचांग_init_on_chip(adev, AMDGPU_PL_GDS, adev->gds.gds_size);
	अगर (r) अणु
		DRM_ERROR("Failed initializing GDS heap.\n");
		वापस r;
	पूर्ण

	r = amdgpu_tपंचांग_init_on_chip(adev, AMDGPU_PL_GWS, adev->gds.gws_size);
	अगर (r) अणु
		DRM_ERROR("Failed initializing gws heap.\n");
		वापस r;
	पूर्ण

	r = amdgpu_tपंचांग_init_on_chip(adev, AMDGPU_PL_OA, adev->gds.oa_size);
	अगर (r) अणु
		DRM_ERROR("Failed initializing oa heap.\n");
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * amdgpu_tपंचांग_fini - De-initialize the TTM memory pools
 */
व्योम amdgpu_tपंचांग_fini(काष्ठा amdgpu_device *adev)
अणु
	अगर (!adev->mman.initialized)
		वापस;

	amdgpu_tपंचांग_training_reserve_vram_fini(adev);
	/* वापस the stolen vga memory back to VRAM */
	amdgpu_bo_मुक्त_kernel(&adev->mman.stolen_vga_memory, शून्य, शून्य);
	amdgpu_bo_मुक्त_kernel(&adev->mman.stolen_extended_memory, शून्य, शून्य);
	/* वापस the IP Discovery TMR memory back to VRAM */
	amdgpu_bo_मुक्त_kernel(&adev->mman.discovery_memory, शून्य, शून्य);
	amdgpu_tपंचांग_fw_reserve_vram_fini(adev);

	अगर (adev->mman.aper_base_kaddr)
		iounmap(adev->mman.aper_base_kaddr);
	adev->mman.aper_base_kaddr = शून्य;

	amdgpu_vram_mgr_fini(adev);
	amdgpu_gtt_mgr_fini(adev);
	tपंचांग_range_man_fini(&adev->mman.bdev, AMDGPU_PL_GDS);
	tपंचांग_range_man_fini(&adev->mman.bdev, AMDGPU_PL_GWS);
	tपंचांग_range_man_fini(&adev->mman.bdev, AMDGPU_PL_OA);
	tपंचांग_device_fini(&adev->mman.bdev);
	adev->mman.initialized = false;
	DRM_INFO("amdgpu: ttm finalized\n");
पूर्ण

/**
 * amdgpu_tपंचांग_set_buffer_funcs_status - enable/disable use of buffer functions
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @enable: true when we can use buffer functions.
 *
 * Enable/disable use of buffer functions during suspend/resume. This should
 * only be called at bootup or when userspace isn't running.
 */
व्योम amdgpu_tपंचांग_set_buffer_funcs_status(काष्ठा amdgpu_device *adev, bool enable)
अणु
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(&adev->mman.bdev, TTM_PL_VRAM);
	uपूर्णांक64_t size;
	पूर्णांक r;

	अगर (!adev->mman.initialized || amdgpu_in_reset(adev) ||
	    adev->mman.buffer_funcs_enabled == enable)
		वापस;

	अगर (enable) अणु
		काष्ठा amdgpu_ring *ring;
		काष्ठा drm_gpu_scheduler *sched;

		ring = adev->mman.buffer_funcs_ring;
		sched = &ring->sched;
		r = drm_sched_entity_init(&adev->mman.entity,
					  DRM_SCHED_PRIORITY_KERNEL, &sched,
					  1, शून्य);
		अगर (r) अणु
			DRM_ERROR("Failed setting up TTM BO move entity (%d)\n",
				  r);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		drm_sched_entity_destroy(&adev->mman.entity);
		dma_fence_put(man->move);
		man->move = शून्य;
	पूर्ण

	/* this just adjusts TTM size idea, which sets lpfn to the correct value */
	अगर (enable)
		size = adev->gmc.real_vram_size;
	अन्यथा
		size = adev->gmc.visible_vram_size;
	man->size = size >> PAGE_SHIFT;
	adev->mman.buffer_funcs_enabled = enable;
पूर्ण

अटल vm_fault_t amdgpu_tपंचांग_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा tपंचांग_buffer_object *bo = vmf->vma->vm_निजी_data;
	vm_fault_t ret;

	ret = tपंचांग_bo_vm_reserve(bo, vmf);
	अगर (ret)
		वापस ret;

	ret = amdgpu_bo_fault_reserve_notअगरy(bo);
	अगर (ret)
		जाओ unlock;

	ret = tपंचांग_bo_vm_fault_reserved(vmf, vmf->vma->vm_page_prot,
				       TTM_BO_VM_NUM_PREFAULT, 1);
	अगर (ret == VM_FAULT_RETRY && !(vmf->flags & FAULT_FLAG_RETRY_NOWAIT))
		वापस ret;

unlock:
	dma_resv_unlock(bo->base.resv);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा amdgpu_tपंचांग_vm_ops = अणु
	.fault = amdgpu_tपंचांग_fault,
	.खोलो = tपंचांग_bo_vm_खोलो,
	.बंद = tपंचांग_bo_vm_बंद,
	.access = tपंचांग_bo_vm_access
पूर्ण;

पूर्णांक amdgpu_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_file *file_priv = filp->निजी_data;
	काष्ठा amdgpu_device *adev = drm_to_adev(file_priv->minor->dev);
	पूर्णांक r;

	r = tपंचांग_bo_mmap(filp, vma, &adev->mman.bdev);
	अगर (unlikely(r != 0))
		वापस r;

	vma->vm_ops = &amdgpu_tपंचांग_vm_ops;
	वापस 0;
पूर्ण

पूर्णांक amdgpu_copy_buffer(काष्ठा amdgpu_ring *ring, uपूर्णांक64_t src_offset,
		       uपूर्णांक64_t dst_offset, uपूर्णांक32_t byte_count,
		       काष्ठा dma_resv *resv,
		       काष्ठा dma_fence **fence, bool direct_submit,
		       bool vm_needs_flush, bool पंचांगz)
अणु
	क्रमागत amdgpu_ib_pool_type pool = direct_submit ? AMDGPU_IB_POOL_सूचीECT :
		AMDGPU_IB_POOL_DELAYED;
	काष्ठा amdgpu_device *adev = ring->adev;
	काष्ठा amdgpu_job *job;

	uपूर्णांक32_t max_bytes;
	अचिन्हित num_loops, num_dw;
	अचिन्हित i;
	पूर्णांक r;

	अगर (direct_submit && !ring->sched.पढ़ोy) अणु
		DRM_ERROR("Trying to move memory with ring turned off.\n");
		वापस -EINVAL;
	पूर्ण

	max_bytes = adev->mman.buffer_funcs->copy_max_bytes;
	num_loops = DIV_ROUND_UP(byte_count, max_bytes);
	num_dw = ALIGN(num_loops * adev->mman.buffer_funcs->copy_num_dw, 8);

	r = amdgpu_job_alloc_with_ib(adev, num_dw * 4, pool, &job);
	अगर (r)
		वापस r;

	अगर (vm_needs_flush) अणु
		job->vm_pd_addr = amdgpu_gmc_pd_addr(adev->gmc.pdb0_bo ?
					adev->gmc.pdb0_bo : adev->gart.bo);
		job->vm_needs_flush = true;
	पूर्ण
	अगर (resv) अणु
		r = amdgpu_sync_resv(adev, &job->sync, resv,
				     AMDGPU_SYNC_ALWAYS,
				     AMDGPU_FENCE_OWNER_UNDEFINED);
		अगर (r) अणु
			DRM_ERROR("sync failed (%d).\n", r);
			जाओ error_मुक्त;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < num_loops; i++) अणु
		uपूर्णांक32_t cur_size_in_bytes = min(byte_count, max_bytes);

		amdgpu_emit_copy_buffer(adev, &job->ibs[0], src_offset,
					dst_offset, cur_size_in_bytes, पंचांगz);

		src_offset += cur_size_in_bytes;
		dst_offset += cur_size_in_bytes;
		byte_count -= cur_size_in_bytes;
	पूर्ण

	amdgpu_ring_pad_ib(ring, &job->ibs[0]);
	WARN_ON(job->ibs[0].length_dw > num_dw);
	अगर (direct_submit)
		r = amdgpu_job_submit_direct(job, ring, fence);
	अन्यथा
		r = amdgpu_job_submit(job, &adev->mman.entity,
				      AMDGPU_FENCE_OWNER_UNDEFINED, fence);
	अगर (r)
		जाओ error_मुक्त;

	वापस r;

error_मुक्त:
	amdgpu_job_मुक्त(job);
	DRM_ERROR("Error scheduling IBs (%d)\n", r);
	वापस r;
पूर्ण

पूर्णांक amdgpu_fill_buffer(काष्ठा amdgpu_bo *bo,
		       uपूर्णांक32_t src_data,
		       काष्ठा dma_resv *resv,
		       काष्ठा dma_fence **fence)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);
	uपूर्णांक32_t max_bytes = adev->mman.buffer_funcs->fill_max_bytes;
	काष्ठा amdgpu_ring *ring = adev->mman.buffer_funcs_ring;

	काष्ठा amdgpu_res_cursor cursor;
	अचिन्हित पूर्णांक num_loops, num_dw;
	uपूर्णांक64_t num_bytes;

	काष्ठा amdgpu_job *job;
	पूर्णांक r;

	अगर (!adev->mman.buffer_funcs_enabled) अणु
		DRM_ERROR("Trying to clear memory with ring turned off.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (bo->tbo.mem.mem_type == TTM_PL_TT) अणु
		r = amdgpu_tपंचांग_alloc_gart(&bo->tbo);
		अगर (r)
			वापस r;
	पूर्ण

	num_bytes = bo->tbo.mem.num_pages << PAGE_SHIFT;
	num_loops = 0;

	amdgpu_res_first(&bo->tbo.mem, 0, num_bytes, &cursor);
	जबतक (cursor.reमुख्यing) अणु
		num_loops += DIV_ROUND_UP_ULL(cursor.size, max_bytes);
		amdgpu_res_next(&cursor, cursor.size);
	पूर्ण
	num_dw = num_loops * adev->mman.buffer_funcs->fill_num_dw;

	/* क्रम IB padding */
	num_dw += 64;

	r = amdgpu_job_alloc_with_ib(adev, num_dw * 4, AMDGPU_IB_POOL_DELAYED,
				     &job);
	अगर (r)
		वापस r;

	अगर (resv) अणु
		r = amdgpu_sync_resv(adev, &job->sync, resv,
				     AMDGPU_SYNC_ALWAYS,
				     AMDGPU_FENCE_OWNER_UNDEFINED);
		अगर (r) अणु
			DRM_ERROR("sync failed (%d).\n", r);
			जाओ error_मुक्त;
		पूर्ण
	पूर्ण

	amdgpu_res_first(&bo->tbo.mem, 0, num_bytes, &cursor);
	जबतक (cursor.reमुख्यing) अणु
		uपूर्णांक32_t cur_size = min_t(uपूर्णांक64_t, cursor.size, max_bytes);
		uपूर्णांक64_t dst_addr = cursor.start;

		dst_addr += amdgpu_tपंचांग_करोमुख्य_start(adev, bo->tbo.mem.mem_type);
		amdgpu_emit_fill_buffer(adev, &job->ibs[0], src_data, dst_addr,
					cur_size);

		amdgpu_res_next(&cursor, cur_size);
	पूर्ण

	amdgpu_ring_pad_ib(ring, &job->ibs[0]);
	WARN_ON(job->ibs[0].length_dw > num_dw);
	r = amdgpu_job_submit(job, &adev->mman.entity,
			      AMDGPU_FENCE_OWNER_UNDEFINED, fence);
	अगर (r)
		जाओ error_मुक्त;

	वापस 0;

error_मुक्त:
	amdgpu_job_मुक्त(job);
	वापस r;
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)

अटल पूर्णांक amdgpu_mm_vram_table_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)m->निजी;
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(&adev->mman.bdev,
							    TTM_PL_VRAM);
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	man->func->debug(man, &p);
	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_tपंचांग_page_pool_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)m->निजी;

	वापस tपंचांग_pool_debugfs(&adev->mman.bdev.pool, m);
पूर्ण

अटल पूर्णांक amdgpu_mm_tt_table_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)m->निजी;
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(&adev->mman.bdev,
							    TTM_PL_TT);
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	man->func->debug(man, &p);
	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_mm_gds_table_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)m->निजी;
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(&adev->mman.bdev,
							    AMDGPU_PL_GDS);
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	man->func->debug(man, &p);
	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_mm_gws_table_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)m->निजी;
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(&adev->mman.bdev,
							    AMDGPU_PL_GWS);
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	man->func->debug(man, &p);
	वापस 0;
पूर्ण

अटल पूर्णांक amdgpu_mm_oa_table_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)m->निजी;
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(&adev->mman.bdev,
							    AMDGPU_PL_OA);
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	man->func->debug(man, &p);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(amdgpu_mm_vram_table);
DEFINE_SHOW_ATTRIBUTE(amdgpu_mm_tt_table);
DEFINE_SHOW_ATTRIBUTE(amdgpu_mm_gds_table);
DEFINE_SHOW_ATTRIBUTE(amdgpu_mm_gws_table);
DEFINE_SHOW_ATTRIBUTE(amdgpu_mm_oa_table);
DEFINE_SHOW_ATTRIBUTE(amdgpu_tपंचांग_page_pool);

/*
 * amdgpu_tपंचांग_vram_पढ़ो - Linear पढ़ो access to VRAM
 *
 * Accesses VRAM via MMIO क्रम debugging purposes.
 */
अटल sमाप_प्रकार amdgpu_tपंचांग_vram_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
				    माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = file_inode(f)->i_निजी;
	sमाप_प्रकार result = 0;

	अगर (size & 0x3 || *pos & 0x3)
		वापस -EINVAL;

	अगर (*pos >= adev->gmc.mc_vram_size)
		वापस -ENXIO;

	size = min(size, (माप_प्रकार)(adev->gmc.mc_vram_size - *pos));
	जबतक (size) अणु
		माप_प्रकार bytes = min(size, AMDGPU_TTM_VRAM_MAX_DW_READ * 4);
		uपूर्णांक32_t value[AMDGPU_TTM_VRAM_MAX_DW_READ];

		amdgpu_device_vram_access(adev, *pos, value, bytes, false);
		अगर (copy_to_user(buf, value, bytes))
			वापस -EFAULT;

		result += bytes;
		buf += bytes;
		*pos += bytes;
		size -= bytes;
	पूर्ण

	वापस result;
पूर्ण

/*
 * amdgpu_tपंचांग_vram_ग_लिखो - Linear ग_लिखो access to VRAM
 *
 * Accesses VRAM via MMIO क्रम debugging purposes.
 */
अटल sमाप_प्रकार amdgpu_tपंचांग_vram_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
				    माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = file_inode(f)->i_निजी;
	sमाप_प्रकार result = 0;
	पूर्णांक r;

	अगर (size & 0x3 || *pos & 0x3)
		वापस -EINVAL;

	अगर (*pos >= adev->gmc.mc_vram_size)
		वापस -ENXIO;

	जबतक (size) अणु
		अचिन्हित दीर्घ flags;
		uपूर्णांक32_t value;

		अगर (*pos >= adev->gmc.mc_vram_size)
			वापस result;

		r = get_user(value, (uपूर्णांक32_t *)buf);
		अगर (r)
			वापस r;

		spin_lock_irqsave(&adev->mmio_idx_lock, flags);
		WREG32_NO_KIQ(mmMM_INDEX, ((uपूर्णांक32_t)*pos) | 0x80000000);
		WREG32_NO_KIQ(mmMM_INDEX_HI, *pos >> 31);
		WREG32_NO_KIQ(mmMM_DATA, value);
		spin_unlock_irqrestore(&adev->mmio_idx_lock, flags);

		result += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	पूर्ण

	वापस result;
पूर्ण

अटल स्थिर काष्ठा file_operations amdgpu_tपंचांग_vram_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = amdgpu_tपंचांग_vram_पढ़ो,
	.ग_लिखो = amdgpu_tपंचांग_vram_ग_लिखो,
	.llseek = शेष_llseek,
पूर्ण;

/*
 * amdgpu_iomem_पढ़ो - Virtual पढ़ो access to GPU mapped memory
 *
 * This function is used to पढ़ो memory that has been mapped to the
 * GPU and the known addresses are not physical addresses but instead
 * bus addresses (e.g., what you'd put in an IB or ring buffer).
 */
अटल sमाप_प्रकार amdgpu_iomem_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
				 माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = file_inode(f)->i_निजी;
	काष्ठा iommu_करोमुख्य *करोm;
	sमाप_प्रकार result = 0;
	पूर्णांक r;

	/* retrieve the IOMMU करोमुख्य अगर any क्रम this device */
	करोm = iommu_get_करोमुख्य_क्रम_dev(adev->dev);

	जबतक (size) अणु
		phys_addr_t addr = *pos & PAGE_MASK;
		loff_t off = *pos & ~PAGE_MASK;
		माप_प्रकार bytes = PAGE_SIZE - off;
		अचिन्हित दीर्घ pfn;
		काष्ठा page *p;
		व्योम *ptr;

		bytes = bytes < size ? bytes : size;

		/* Translate the bus address to a physical address.  If
		 * the करोमुख्य is शून्य it means there is no IOMMU active
		 * and the address translation is the identity
		 */
		addr = करोm ? iommu_iova_to_phys(करोm, addr) : addr;

		pfn = addr >> PAGE_SHIFT;
		अगर (!pfn_valid(pfn))
			वापस -EPERM;

		p = pfn_to_page(pfn);
		अगर (p->mapping != adev->mman.bdev.dev_mapping)
			वापस -EPERM;

		ptr = kmap(p);
		r = copy_to_user(buf, ptr + off, bytes);
		kunmap(p);
		अगर (r)
			वापस -EFAULT;

		size -= bytes;
		*pos += bytes;
		result += bytes;
	पूर्ण

	वापस result;
पूर्ण

/*
 * amdgpu_iomem_ग_लिखो - Virtual ग_लिखो access to GPU mapped memory
 *
 * This function is used to ग_लिखो memory that has been mapped to the
 * GPU and the known addresses are not physical addresses but instead
 * bus addresses (e.g., what you'd put in an IB or ring buffer).
 */
अटल sमाप_प्रकार amdgpu_iomem_ग_लिखो(काष्ठा file *f, स्थिर अक्षर __user *buf,
				 माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा amdgpu_device *adev = file_inode(f)->i_निजी;
	काष्ठा iommu_करोमुख्य *करोm;
	sमाप_प्रकार result = 0;
	पूर्णांक r;

	करोm = iommu_get_करोमुख्य_क्रम_dev(adev->dev);

	जबतक (size) अणु
		phys_addr_t addr = *pos & PAGE_MASK;
		loff_t off = *pos & ~PAGE_MASK;
		माप_प्रकार bytes = PAGE_SIZE - off;
		अचिन्हित दीर्घ pfn;
		काष्ठा page *p;
		व्योम *ptr;

		bytes = bytes < size ? bytes : size;

		addr = करोm ? iommu_iova_to_phys(करोm, addr) : addr;

		pfn = addr >> PAGE_SHIFT;
		अगर (!pfn_valid(pfn))
			वापस -EPERM;

		p = pfn_to_page(pfn);
		अगर (p->mapping != adev->mman.bdev.dev_mapping)
			वापस -EPERM;

		ptr = kmap(p);
		r = copy_from_user(ptr + off, buf, bytes);
		kunmap(p);
		अगर (r)
			वापस -EFAULT;

		size -= bytes;
		*pos += bytes;
		result += bytes;
	पूर्ण

	वापस result;
पूर्ण

अटल स्थिर काष्ठा file_operations amdgpu_tपंचांग_iomem_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = amdgpu_iomem_पढ़ो,
	.ग_लिखो = amdgpu_iomem_ग_लिखो,
	.llseek = शेष_llseek
पूर्ण;

#पूर्ण_अगर

व्योम amdgpu_tपंचांग_debugfs_init(काष्ठा amdgpu_device *adev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा drm_minor *minor = adev_to_drm(adev)->primary;
	काष्ठा dentry *root = minor->debugfs_root;

	debugfs_create_file_size("amdgpu_vram", 0444, root, adev,
				 &amdgpu_tपंचांग_vram_fops, adev->gmc.mc_vram_size);
	debugfs_create_file("amdgpu_iomem", 0444, root, adev,
			    &amdgpu_tपंचांग_iomem_fops);
	debugfs_create_file("amdgpu_vram_mm", 0444, root, adev,
			    &amdgpu_mm_vram_table_fops);
	debugfs_create_file("amdgpu_gtt_mm", 0444, root, adev,
			    &amdgpu_mm_tt_table_fops);
	debugfs_create_file("amdgpu_gds_mm", 0444, root, adev,
			    &amdgpu_mm_gds_table_fops);
	debugfs_create_file("amdgpu_gws_mm", 0444, root, adev,
			    &amdgpu_mm_gws_table_fops);
	debugfs_create_file("amdgpu_oa_mm", 0444, root, adev,
			    &amdgpu_mm_oa_table_fops);
	debugfs_create_file("ttm_page_pool", 0444, root, adev,
			    &amdgpu_tपंचांग_page_pool_fops);
#पूर्ण_अगर
पूर्ण
