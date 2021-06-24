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
#समावेश <linux/pagemap.h>
#समावेश <linux/pci.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <linux/swap.h>
#समावेश <linux/swiotlb.h>

#समावेश <drm/drm_agpsupport.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_prime.h>
#समावेश <drm/radeon_drm.h>
#समावेश <drm/tपंचांग/tपंचांग_bo_api.h>
#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>
#समावेश <drm/tपंचांग/tपंचांग_placement.h>

#समावेश "radeon_reg.h"
#समावेश "radeon.h"
#समावेश "radeon_ttm.h"

अटल व्योम radeon_tपंचांग_debugfs_init(काष्ठा radeon_device *rdev);

अटल पूर्णांक radeon_tपंचांग_tt_bind(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग,
			      काष्ठा tपंचांग_resource *bo_mem);
अटल व्योम radeon_tपंचांग_tt_unbind(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग);

काष्ठा radeon_device *radeon_get_rdev(काष्ठा tपंचांग_device *bdev)
अणु
	काष्ठा radeon_mman *mman;
	काष्ठा radeon_device *rdev;

	mman = container_of(bdev, काष्ठा radeon_mman, bdev);
	rdev = container_of(mman, काष्ठा radeon_device, mman);
	वापस rdev;
पूर्ण

अटल पूर्णांक radeon_tपंचांग_init_vram(काष्ठा radeon_device *rdev)
अणु
	वापस tपंचांग_range_man_init(&rdev->mman.bdev, TTM_PL_VRAM,
				  false, rdev->mc.real_vram_size >> PAGE_SHIFT);
पूर्ण

अटल पूर्णांक radeon_tपंचांग_init_gtt(काष्ठा radeon_device *rdev)
अणु
	वापस tपंचांग_range_man_init(&rdev->mman.bdev, TTM_PL_TT,
				  true, rdev->mc.gtt_size >> PAGE_SHIFT);
पूर्ण

अटल व्योम radeon_evict_flags(काष्ठा tपंचांग_buffer_object *bo,
				काष्ठा tपंचांग_placement *placement)
अणु
	अटल स्थिर काष्ठा tपंचांग_place placements = अणु
		.fpfn = 0,
		.lpfn = 0,
		.mem_type = TTM_PL_SYSTEM,
		.flags = 0
	पूर्ण;

	काष्ठा radeon_bo *rbo;

	अगर (!radeon_tपंचांग_bo_is_radeon_bo(bo)) अणु
		placement->placement = &placements;
		placement->busy_placement = &placements;
		placement->num_placement = 1;
		placement->num_busy_placement = 1;
		वापस;
	पूर्ण
	rbo = container_of(bo, काष्ठा radeon_bo, tbo);
	चयन (bo->mem.mem_type) अणु
	हाल TTM_PL_VRAM:
		अगर (rbo->rdev->ring[radeon_copy_ring_index(rbo->rdev)].पढ़ोy == false)
			radeon_tपंचांग_placement_from_करोमुख्य(rbo, RADEON_GEM_DOMAIN_CPU);
		अन्यथा अगर (rbo->rdev->mc.visible_vram_size < rbo->rdev->mc.real_vram_size &&
			 bo->mem.start < (rbo->rdev->mc.visible_vram_size >> PAGE_SHIFT)) अणु
			अचिन्हित fpfn = rbo->rdev->mc.visible_vram_size >> PAGE_SHIFT;
			पूर्णांक i;

			/* Try evicting to the CPU inaccessible part of VRAM
			 * first, but only set GTT as busy placement, so this
			 * BO will be evicted to GTT rather than causing other
			 * BOs to be evicted from VRAM
			 */
			radeon_tपंचांग_placement_from_करोमुख्य(rbo, RADEON_GEM_DOMAIN_VRAM |
							 RADEON_GEM_DOMAIN_GTT);
			rbo->placement.num_busy_placement = 0;
			क्रम (i = 0; i < rbo->placement.num_placement; i++) अणु
				अगर (rbo->placements[i].mem_type == TTM_PL_VRAM) अणु
					अगर (rbo->placements[i].fpfn < fpfn)
						rbo->placements[i].fpfn = fpfn;
				पूर्ण अन्यथा अणु
					rbo->placement.busy_placement =
						&rbo->placements[i];
					rbo->placement.num_busy_placement = 1;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा
			radeon_tपंचांग_placement_from_करोमुख्य(rbo, RADEON_GEM_DOMAIN_GTT);
		अवरोध;
	हाल TTM_PL_TT:
	शेष:
		radeon_tपंचांग_placement_from_करोमुख्य(rbo, RADEON_GEM_DOMAIN_CPU);
	पूर्ण
	*placement = rbo->placement;
पूर्ण

अटल पूर्णांक radeon_verअगरy_access(काष्ठा tपंचांग_buffer_object *bo, काष्ठा file *filp)
अणु
	काष्ठा radeon_bo *rbo = container_of(bo, काष्ठा radeon_bo, tbo);
	काष्ठा radeon_device *rdev = radeon_get_rdev(bo->bdev);

	अगर (radeon_tपंचांग_tt_has_userptr(rdev, bo->tपंचांग))
		वापस -EPERM;
	वापस drm_vma_node_verअगरy_access(&rbo->tbo.base.vma_node,
					  filp->निजी_data);
पूर्ण

अटल पूर्णांक radeon_move_blit(काष्ठा tपंचांग_buffer_object *bo,
			bool evict,
			काष्ठा tपंचांग_resource *new_mem,
			काष्ठा tपंचांग_resource *old_mem)
अणु
	काष्ठा radeon_device *rdev;
	uपूर्णांक64_t old_start, new_start;
	काष्ठा radeon_fence *fence;
	अचिन्हित num_pages;
	पूर्णांक r, ridx;

	rdev = radeon_get_rdev(bo->bdev);
	ridx = radeon_copy_ring_index(rdev);
	old_start = (u64)old_mem->start << PAGE_SHIFT;
	new_start = (u64)new_mem->start << PAGE_SHIFT;

	चयन (old_mem->mem_type) अणु
	हाल TTM_PL_VRAM:
		old_start += rdev->mc.vram_start;
		अवरोध;
	हाल TTM_PL_TT:
		old_start += rdev->mc.gtt_start;
		अवरोध;
	शेष:
		DRM_ERROR("Unknown placement %d\n", old_mem->mem_type);
		वापस -EINVAL;
	पूर्ण
	चयन (new_mem->mem_type) अणु
	हाल TTM_PL_VRAM:
		new_start += rdev->mc.vram_start;
		अवरोध;
	हाल TTM_PL_TT:
		new_start += rdev->mc.gtt_start;
		अवरोध;
	शेष:
		DRM_ERROR("Unknown placement %d\n", old_mem->mem_type);
		वापस -EINVAL;
	पूर्ण
	अगर (!rdev->ring[ridx].पढ़ोy) अणु
		DRM_ERROR("Trying to move memory with ring turned off.\n");
		वापस -EINVAL;
	पूर्ण

	BUILD_BUG_ON((PAGE_SIZE % RADEON_GPU_PAGE_SIZE) != 0);

	num_pages = new_mem->num_pages * (PAGE_SIZE / RADEON_GPU_PAGE_SIZE);
	fence = radeon_copy(rdev, old_start, new_start, num_pages, bo->base.resv);
	अगर (IS_ERR(fence))
		वापस PTR_ERR(fence);

	r = tपंचांग_bo_move_accel_cleanup(bo, &fence->base, evict, false, new_mem);
	radeon_fence_unref(&fence);
	वापस r;
पूर्ण

अटल पूर्णांक radeon_bo_move(काष्ठा tपंचांग_buffer_object *bo, bool evict,
			  काष्ठा tपंचांग_operation_ctx *ctx,
			  काष्ठा tपंचांग_resource *new_mem,
			  काष्ठा tपंचांग_place *hop)
अणु
	काष्ठा radeon_device *rdev;
	काष्ठा radeon_bo *rbo;
	काष्ठा tपंचांग_resource *old_mem = &bo->mem;
	पूर्णांक r;

	अगर (new_mem->mem_type == TTM_PL_TT) अणु
		r = radeon_tपंचांग_tt_bind(bo->bdev, bo->tपंचांग, new_mem);
		अगर (r)
			वापस r;
	पूर्ण

	r = tपंचांग_bo_रुको_ctx(bo, ctx);
	अगर (r)
		वापस r;

	/* Can't move a pinned BO */
	rbo = container_of(bo, काष्ठा radeon_bo, tbo);
	अगर (WARN_ON_ONCE(rbo->tbo.pin_count > 0))
		वापस -EINVAL;

	rdev = radeon_get_rdev(bo->bdev);
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
		radeon_tपंचांग_tt_unbind(bo->bdev, bo->tपंचांग);
		tपंचांग_resource_मुक्त(bo, &bo->mem);
		tपंचांग_bo_assign_mem(bo, new_mem);
		जाओ out;
	पूर्ण
	अगर (rdev->ring[radeon_copy_ring_index(rdev)].पढ़ोy &&
	    rdev->asic->copy.copy != शून्य) अणु
		अगर ((old_mem->mem_type == TTM_PL_SYSTEM &&
		     new_mem->mem_type == TTM_PL_VRAM) ||
		    (old_mem->mem_type == TTM_PL_VRAM &&
		     new_mem->mem_type == TTM_PL_SYSTEM)) अणु
			hop->fpfn = 0;
			hop->lpfn = 0;
			hop->mem_type = TTM_PL_TT;
			hop->flags = 0;
			वापस -EMULTIHOP;
		पूर्ण

		r = radeon_move_blit(bo, evict, new_mem, old_mem);
	पूर्ण अन्यथा अणु
		r = -ENODEV;
	पूर्ण

	अगर (r) अणु
		r = tपंचांग_bo_move_स_नकल(bo, ctx, new_mem);
		अगर (r)
			वापस r;
	पूर्ण

out:
	/* update statistics */
	atomic64_add(bo->base.size, &rdev->num_bytes_moved);
	radeon_bo_move_notअगरy(bo, evict, new_mem);
	वापस 0;
पूर्ण

अटल पूर्णांक radeon_tपंचांग_io_mem_reserve(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_resource *mem)
अणु
	काष्ठा radeon_device *rdev = radeon_get_rdev(bdev);
	माप_प्रकार bus_size = (माप_प्रकार)mem->num_pages << PAGE_SHIFT;

	चयन (mem->mem_type) अणु
	हाल TTM_PL_SYSTEM:
		/* प्रणाली memory */
		वापस 0;
	हाल TTM_PL_TT:
#अगर IS_ENABLED(CONFIG_AGP)
		अगर (rdev->flags & RADEON_IS_AGP) अणु
			/* RADEON_IS_AGP is set only अगर AGP is active */
			mem->bus.offset = (mem->start << PAGE_SHIFT) +
				rdev->mc.agp_base;
			mem->bus.is_iomem = !rdev->ddev->agp->cant_use_aperture;
			mem->bus.caching = tपंचांग_ग_लिखो_combined;
		पूर्ण
#पूर्ण_अगर
		अवरोध;
	हाल TTM_PL_VRAM:
		mem->bus.offset = mem->start << PAGE_SHIFT;
		/* check अगर it's visible */
		अगर ((mem->bus.offset + bus_size) > rdev->mc.visible_vram_size)
			वापस -EINVAL;
		mem->bus.offset += rdev->mc.aper_base;
		mem->bus.is_iomem = true;
		mem->bus.caching = tपंचांग_ग_लिखो_combined;
#अगर_घोषित __alpha__
		/*
		 * Alpha: use bus.addr to hold the ioremap() वापस,
		 * so we can modअगरy bus.base below.
		 */
		mem->bus.addr = ioremap_wc(mem->bus.offset, bus_size);
		अगर (!mem->bus.addr)
			वापस -ENOMEM;

		/*
		 * Alpha: Use just the bus offset plus
		 * the hose/करोमुख्य memory base क्रम bus.base.
		 * It then can be used to build PTEs क्रम VRAM
		 * access, as करोne in tपंचांग_bo_vm_fault().
		 */
		mem->bus.offset = (mem->bus.offset & 0x0ffffffffUL) +
			rdev->hose->dense_mem_base;
#पूर्ण_अगर
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * TTM backend functions.
 */
काष्ठा radeon_tपंचांग_tt अणु
	काष्ठा tपंचांग_tt		tपंचांग;
	u64				offset;

	uपूर्णांक64_t			userptr;
	काष्ठा mm_काष्ठा		*usermm;
	uपूर्णांक32_t			userflags;
	bool bound;
पूर्ण;

/* prepare the sg table with the user pages */
अटल पूर्णांक radeon_tपंचांग_tt_pin_userptr(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा radeon_device *rdev = radeon_get_rdev(bdev);
	काष्ठा radeon_tपंचांग_tt *gtt = (व्योम *)tपंचांग;
	अचिन्हित pinned = 0;
	पूर्णांक r;

	पूर्णांक ग_लिखो = !(gtt->userflags & RADEON_GEM_USERPTR_READONLY);
	क्रमागत dma_data_direction direction = ग_लिखो ?
		DMA_BIसूचीECTIONAL : DMA_TO_DEVICE;

	अगर (current->mm != gtt->usermm)
		वापस -EPERM;

	अगर (gtt->userflags & RADEON_GEM_USERPTR_ANONONLY) अणु
		/* check that we only pin करोwn anonymous memory
		   to prevent problems with ग_लिखोback */
		अचिन्हित दीर्घ end = gtt->userptr + (u64)tपंचांग->num_pages * PAGE_SIZE;
		काष्ठा vm_area_काष्ठा *vma;
		vma = find_vma(gtt->usermm, gtt->userptr);
		अगर (!vma || vma->vm_file || vma->vm_end < end)
			वापस -EPERM;
	पूर्ण

	करो अणु
		अचिन्हित num_pages = tपंचांग->num_pages - pinned;
		uपूर्णांक64_t userptr = gtt->userptr + pinned * PAGE_SIZE;
		काष्ठा page **pages = tपंचांग->pages + pinned;

		r = get_user_pages(userptr, num_pages, ग_लिखो ? FOLL_WRITE : 0,
				   pages, शून्य);
		अगर (r < 0)
			जाओ release_pages;

		pinned += r;

	पूर्ण जबतक (pinned < tपंचांग->num_pages);

	r = sg_alloc_table_from_pages(tपंचांग->sg, tपंचांग->pages, tपंचांग->num_pages, 0,
				      (u64)tपंचांग->num_pages << PAGE_SHIFT,
				      GFP_KERNEL);
	अगर (r)
		जाओ release_sg;

	r = dma_map_sgtable(rdev->dev, tपंचांग->sg, direction, 0);
	अगर (r)
		जाओ release_sg;

	drm_prime_sg_to_dma_addr_array(tपंचांग->sg, gtt->tपंचांग.dma_address,
				       tपंचांग->num_pages);

	वापस 0;

release_sg:
	kमुक्त(tपंचांग->sg);

release_pages:
	release_pages(tपंचांग->pages, pinned);
	वापस r;
पूर्ण

अटल व्योम radeon_tपंचांग_tt_unpin_userptr(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा radeon_device *rdev = radeon_get_rdev(bdev);
	काष्ठा radeon_tपंचांग_tt *gtt = (व्योम *)tपंचांग;
	काष्ठा sg_page_iter sg_iter;

	पूर्णांक ग_लिखो = !(gtt->userflags & RADEON_GEM_USERPTR_READONLY);
	क्रमागत dma_data_direction direction = ग_लिखो ?
		DMA_BIसूचीECTIONAL : DMA_TO_DEVICE;

	/* द्विगुन check that we करोn't मुक्त the table twice */
	अगर (!tपंचांग->sg || !tपंचांग->sg->sgl)
		वापस;

	/* मुक्त the sg table and pages again */
	dma_unmap_sgtable(rdev->dev, tपंचांग->sg, direction, 0);

	क्रम_each_sgtable_page(tपंचांग->sg, &sg_iter, 0) अणु
		काष्ठा page *page = sg_page_iter_page(&sg_iter);
		अगर (!(gtt->userflags & RADEON_GEM_USERPTR_READONLY))
			set_page_dirty(page);

		mark_page_accessed(page);
		put_page(page);
	पूर्ण

	sg_मुक्त_table(tपंचांग->sg);
पूर्ण

अटल bool radeon_tपंचांग_backend_is_bound(काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा radeon_tपंचांग_tt *gtt = (व्योम*)tपंचांग;

	वापस (gtt->bound);
पूर्ण

अटल पूर्णांक radeon_tपंचांग_backend_bind(काष्ठा tपंचांग_device *bdev,
				   काष्ठा tपंचांग_tt *tपंचांग,
				   काष्ठा tपंचांग_resource *bo_mem)
अणु
	काष्ठा radeon_tपंचांग_tt *gtt = (व्योम*)tपंचांग;
	काष्ठा radeon_device *rdev = radeon_get_rdev(bdev);
	uपूर्णांक32_t flags = RADEON_GART_PAGE_VALID | RADEON_GART_PAGE_READ |
		RADEON_GART_PAGE_WRITE;
	पूर्णांक r;

	अगर (gtt->bound)
		वापस 0;

	अगर (gtt->userptr) अणु
		radeon_tपंचांग_tt_pin_userptr(bdev, tपंचांग);
		flags &= ~RADEON_GART_PAGE_WRITE;
	पूर्ण

	gtt->offset = (अचिन्हित दीर्घ)(bo_mem->start << PAGE_SHIFT);
	अगर (!tपंचांग->num_pages) अणु
		WARN(1, "nothing to bind %u pages for mreg %p back %p!\n",
		     tपंचांग->num_pages, bo_mem, tपंचांग);
	पूर्ण
	अगर (tपंचांग->caching == tपंचांग_cached)
		flags |= RADEON_GART_PAGE_SNOOP;
	r = radeon_gart_bind(rdev, gtt->offset, tपंचांग->num_pages,
			     tपंचांग->pages, gtt->tपंचांग.dma_address, flags);
	अगर (r) अणु
		DRM_ERROR("failed to bind %u pages at 0x%08X\n",
			  tपंचांग->num_pages, (अचिन्हित)gtt->offset);
		वापस r;
	पूर्ण
	gtt->bound = true;
	वापस 0;
पूर्ण

अटल व्योम radeon_tपंचांग_backend_unbind(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा radeon_tपंचांग_tt *gtt = (व्योम *)tपंचांग;
	काष्ठा radeon_device *rdev = radeon_get_rdev(bdev);

	अगर (gtt->userptr)
		radeon_tपंचांग_tt_unpin_userptr(bdev, tपंचांग);

	अगर (!gtt->bound)
		वापस;

	radeon_gart_unbind(rdev, gtt->offset, tपंचांग->num_pages);

	gtt->bound = false;
पूर्ण

अटल व्योम radeon_tपंचांग_backend_destroy(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा radeon_tपंचांग_tt *gtt = (व्योम *)tपंचांग;

	radeon_tपंचांग_backend_unbind(bdev, tपंचांग);
	tपंचांग_tt_destroy_common(bdev, tपंचांग);

	tपंचांग_tt_fini(&gtt->tपंचांग);
	kमुक्त(gtt);
पूर्ण

अटल काष्ठा tपंचांग_tt *radeon_tपंचांग_tt_create(काष्ठा tपंचांग_buffer_object *bo,
					   uपूर्णांक32_t page_flags)
अणु
	काष्ठा radeon_tपंचांग_tt *gtt;
	क्रमागत tपंचांग_caching caching;
	काष्ठा radeon_bo *rbo;
#अगर IS_ENABLED(CONFIG_AGP)
	काष्ठा radeon_device *rdev = radeon_get_rdev(bo->bdev);

	अगर (rdev->flags & RADEON_IS_AGP) अणु
		वापस tपंचांग_agp_tt_create(bo, rdev->ddev->agp->bridge,
					 page_flags);
	पूर्ण
#पूर्ण_अगर
	rbo = container_of(bo, काष्ठा radeon_bo, tbo);

	gtt = kzalloc(माप(काष्ठा radeon_tपंचांग_tt), GFP_KERNEL);
	अगर (gtt == शून्य) अणु
		वापस शून्य;
	पूर्ण

	अगर (rbo->flags & RADEON_GEM_GTT_UC)
		caching = tपंचांग_uncached;
	अन्यथा अगर (rbo->flags & RADEON_GEM_GTT_WC)
		caching = tपंचांग_ग_लिखो_combined;
	अन्यथा
		caching = tपंचांग_cached;

	अगर (tपंचांग_sg_tt_init(&gtt->tपंचांग, bo, page_flags, caching)) अणु
		kमुक्त(gtt);
		वापस शून्य;
	पूर्ण
	वापस &gtt->tपंचांग;
पूर्ण

अटल काष्ठा radeon_tपंचांग_tt *radeon_tपंचांग_tt_to_gtt(काष्ठा radeon_device *rdev,
						  काष्ठा tपंचांग_tt *tपंचांग)
अणु
#अगर IS_ENABLED(CONFIG_AGP)
	अगर (rdev->flags & RADEON_IS_AGP)
		वापस शून्य;
#पूर्ण_अगर

	अगर (!tपंचांग)
		वापस शून्य;
	वापस container_of(tपंचांग, काष्ठा radeon_tपंचांग_tt, tपंचांग);
पूर्ण

अटल पूर्णांक radeon_tपंचांग_tt_populate(काष्ठा tपंचांग_device *bdev,
				  काष्ठा tपंचांग_tt *tपंचांग,
				  काष्ठा tपंचांग_operation_ctx *ctx)
अणु
	काष्ठा radeon_device *rdev = radeon_get_rdev(bdev);
	काष्ठा radeon_tपंचांग_tt *gtt = radeon_tपंचांग_tt_to_gtt(rdev, tपंचांग);
	bool slave = !!(tपंचांग->page_flags & TTM_PAGE_FLAG_SG);

	अगर (gtt && gtt->userptr) अणु
		tपंचांग->sg = kzalloc(माप(काष्ठा sg_table), GFP_KERNEL);
		अगर (!tपंचांग->sg)
			वापस -ENOMEM;

		tपंचांग->page_flags |= TTM_PAGE_FLAG_SG;
		वापस 0;
	पूर्ण

	अगर (slave && tपंचांग->sg) अणु
		drm_prime_sg_to_dma_addr_array(tपंचांग->sg, gtt->tपंचांग.dma_address,
					       tपंचांग->num_pages);
		वापस 0;
	पूर्ण

	वापस tपंचांग_pool_alloc(&rdev->mman.bdev.pool, tपंचांग, ctx);
पूर्ण

अटल व्योम radeon_tपंचांग_tt_unpopulate(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा radeon_device *rdev = radeon_get_rdev(bdev);
	काष्ठा radeon_tपंचांग_tt *gtt = radeon_tपंचांग_tt_to_gtt(rdev, tपंचांग);
	bool slave = !!(tपंचांग->page_flags & TTM_PAGE_FLAG_SG);

	अगर (gtt && gtt->userptr) अणु
		kमुक्त(tपंचांग->sg);
		tपंचांग->page_flags &= ~TTM_PAGE_FLAG_SG;
		वापस;
	पूर्ण

	अगर (slave)
		वापस;

	वापस tपंचांग_pool_मुक्त(&rdev->mman.bdev.pool, tपंचांग);
पूर्ण

पूर्णांक radeon_tपंचांग_tt_set_userptr(काष्ठा radeon_device *rdev,
			      काष्ठा tपंचांग_tt *tपंचांग, uपूर्णांक64_t addr,
			      uपूर्णांक32_t flags)
अणु
	काष्ठा radeon_tपंचांग_tt *gtt = radeon_tपंचांग_tt_to_gtt(rdev, tपंचांग);

	अगर (gtt == शून्य)
		वापस -EINVAL;

	gtt->userptr = addr;
	gtt->usermm = current->mm;
	gtt->userflags = flags;
	वापस 0;
पूर्ण

bool radeon_tपंचांग_tt_is_bound(काष्ठा tपंचांग_device *bdev,
			    काष्ठा tपंचांग_tt *tपंचांग)
अणु
#अगर IS_ENABLED(CONFIG_AGP)
	काष्ठा radeon_device *rdev = radeon_get_rdev(bdev);
	अगर (rdev->flags & RADEON_IS_AGP)
		वापस tपंचांग_agp_is_bound(tपंचांग);
#पूर्ण_अगर
	वापस radeon_tपंचांग_backend_is_bound(tपंचांग);
पूर्ण

अटल पूर्णांक radeon_tपंचांग_tt_bind(काष्ठा tपंचांग_device *bdev,
			      काष्ठा tपंचांग_tt *tपंचांग,
			      काष्ठा tपंचांग_resource *bo_mem)
अणु
#अगर IS_ENABLED(CONFIG_AGP)
	काष्ठा radeon_device *rdev = radeon_get_rdev(bdev);
#पूर्ण_अगर

	अगर (!bo_mem)
		वापस -EINVAL;
#अगर IS_ENABLED(CONFIG_AGP)
	अगर (rdev->flags & RADEON_IS_AGP)
		वापस tपंचांग_agp_bind(tपंचांग, bo_mem);
#पूर्ण_अगर

	वापस radeon_tपंचांग_backend_bind(bdev, tपंचांग, bo_mem);
पूर्ण

अटल व्योम radeon_tपंचांग_tt_unbind(काष्ठा tपंचांग_device *bdev,
				 काष्ठा tपंचांग_tt *tपंचांग)
अणु
#अगर IS_ENABLED(CONFIG_AGP)
	काष्ठा radeon_device *rdev = radeon_get_rdev(bdev);

	अगर (rdev->flags & RADEON_IS_AGP) अणु
		tपंचांग_agp_unbind(tपंचांग);
		वापस;
	पूर्ण
#पूर्ण_अगर
	radeon_tपंचांग_backend_unbind(bdev, tपंचांग);
पूर्ण

अटल व्योम radeon_tपंचांग_tt_destroy(काष्ठा tपंचांग_device *bdev,
				  काष्ठा tपंचांग_tt *tपंचांग)
अणु
#अगर IS_ENABLED(CONFIG_AGP)
	काष्ठा radeon_device *rdev = radeon_get_rdev(bdev);

	अगर (rdev->flags & RADEON_IS_AGP) अणु
		tपंचांग_agp_unbind(tपंचांग);
		tपंचांग_tt_destroy_common(bdev, tपंचांग);
		tपंचांग_agp_destroy(tपंचांग);
		वापस;
	पूर्ण
#पूर्ण_अगर
	radeon_tपंचांग_backend_destroy(bdev, tपंचांग);
पूर्ण

bool radeon_tपंचांग_tt_has_userptr(काष्ठा radeon_device *rdev,
			       काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा radeon_tपंचांग_tt *gtt = radeon_tपंचांग_tt_to_gtt(rdev, tपंचांग);

	अगर (gtt == शून्य)
		वापस false;

	वापस !!gtt->userptr;
पूर्ण

bool radeon_tपंचांग_tt_is_पढ़ोonly(काष्ठा radeon_device *rdev,
			       काष्ठा tपंचांग_tt *tपंचांग)
अणु
	काष्ठा radeon_tपंचांग_tt *gtt = radeon_tपंचांग_tt_to_gtt(rdev, tपंचांग);

	अगर (gtt == शून्य)
		वापस false;

	वापस !!(gtt->userflags & RADEON_GEM_USERPTR_READONLY);
पूर्ण

अटल व्योम
radeon_bo_delete_mem_notअगरy(काष्ठा tपंचांग_buffer_object *bo)
अणु
	radeon_bo_move_notअगरy(bo, false, शून्य);
पूर्ण

अटल काष्ठा tपंचांग_device_funcs radeon_bo_driver = अणु
	.tपंचांग_tt_create = &radeon_tपंचांग_tt_create,
	.tपंचांग_tt_populate = &radeon_tपंचांग_tt_populate,
	.tपंचांग_tt_unpopulate = &radeon_tपंचांग_tt_unpopulate,
	.tपंचांग_tt_destroy = &radeon_tपंचांग_tt_destroy,
	.eviction_valuable = tपंचांग_bo_eviction_valuable,
	.evict_flags = &radeon_evict_flags,
	.move = &radeon_bo_move,
	.verअगरy_access = &radeon_verअगरy_access,
	.delete_mem_notअगरy = &radeon_bo_delete_mem_notअगरy,
	.io_mem_reserve = &radeon_tपंचांग_io_mem_reserve,
पूर्ण;

पूर्णांक radeon_tपंचांग_init(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	/* No others user of address space so set it to 0 */
	r = tपंचांग_device_init(&rdev->mman.bdev, &radeon_bo_driver, rdev->dev,
			       rdev->ddev->anon_inode->i_mapping,
			       rdev->ddev->vma_offset_manager,
			       rdev->need_swiotlb,
			       dma_addressing_limited(&rdev->pdev->dev));
	अगर (r) अणु
		DRM_ERROR("failed initializing buffer object driver(%d).\n", r);
		वापस r;
	पूर्ण
	rdev->mman.initialized = true;

	r = radeon_tपंचांग_init_vram(rdev);
	अगर (r) अणु
		DRM_ERROR("Failed initializing VRAM heap.\n");
		वापस r;
	पूर्ण
	/* Change the size here instead of the init above so only lpfn is affected */
	radeon_tपंचांग_set_active_vram_size(rdev, rdev->mc.visible_vram_size);

	r = radeon_bo_create(rdev, 256 * 1024, PAGE_SIZE, true,
			     RADEON_GEM_DOMAIN_VRAM, 0, शून्य,
			     शून्य, &rdev->stolen_vga_memory);
	अगर (r) अणु
		वापस r;
	पूर्ण
	r = radeon_bo_reserve(rdev->stolen_vga_memory, false);
	अगर (r)
		वापस r;
	r = radeon_bo_pin(rdev->stolen_vga_memory, RADEON_GEM_DOMAIN_VRAM, शून्य);
	radeon_bo_unreserve(rdev->stolen_vga_memory);
	अगर (r) अणु
		radeon_bo_unref(&rdev->stolen_vga_memory);
		वापस r;
	पूर्ण
	DRM_INFO("radeon: %uM of VRAM memory ready\n",
		 (अचिन्हित) (rdev->mc.real_vram_size / (1024 * 1024)));

	r = radeon_tपंचांग_init_gtt(rdev);
	अगर (r) अणु
		DRM_ERROR("Failed initializing GTT heap.\n");
		वापस r;
	पूर्ण
	DRM_INFO("radeon: %uM of GTT memory ready.\n",
		 (अचिन्हित)(rdev->mc.gtt_size / (1024 * 1024)));

	radeon_tपंचांग_debugfs_init(rdev);

	वापस 0;
पूर्ण

व्योम radeon_tपंचांग_fini(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक r;

	अगर (!rdev->mman.initialized)
		वापस;

	अगर (rdev->stolen_vga_memory) अणु
		r = radeon_bo_reserve(rdev->stolen_vga_memory, false);
		अगर (r == 0) अणु
			radeon_bo_unpin(rdev->stolen_vga_memory);
			radeon_bo_unreserve(rdev->stolen_vga_memory);
		पूर्ण
		radeon_bo_unref(&rdev->stolen_vga_memory);
	पूर्ण
	tपंचांग_range_man_fini(&rdev->mman.bdev, TTM_PL_VRAM);
	tपंचांग_range_man_fini(&rdev->mman.bdev, TTM_PL_TT);
	tपंचांग_device_fini(&rdev->mman.bdev);
	radeon_gart_fini(rdev);
	rdev->mman.initialized = false;
	DRM_INFO("radeon: ttm finalized\n");
पूर्ण

/* this should only be called at bootup or when userspace
 * isn't running */
व्योम radeon_tपंचांग_set_active_vram_size(काष्ठा radeon_device *rdev, u64 size)
अणु
	काष्ठा tपंचांग_resource_manager *man;

	अगर (!rdev->mman.initialized)
		वापस;

	man = tपंचांग_manager_type(&rdev->mman.bdev, TTM_PL_VRAM);
	/* this just adjusts TTM size idea, which sets lpfn to the correct value */
	man->size = size >> PAGE_SHIFT;
पूर्ण

अटल vm_fault_t radeon_tपंचांग_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा tपंचांग_buffer_object *bo = vmf->vma->vm_निजी_data;
	काष्ठा radeon_device *rdev = radeon_get_rdev(bo->bdev);
	vm_fault_t ret;

	करोwn_पढ़ो(&rdev->pm.mclk_lock);

	ret = tपंचांग_bo_vm_reserve(bo, vmf);
	अगर (ret)
		जाओ unlock_mclk;

	ret = radeon_bo_fault_reserve_notअगरy(bo);
	अगर (ret)
		जाओ unlock_resv;

	ret = tपंचांग_bo_vm_fault_reserved(vmf, vmf->vma->vm_page_prot,
				       TTM_BO_VM_NUM_PREFAULT, 1);
	अगर (ret == VM_FAULT_RETRY && !(vmf->flags & FAULT_FLAG_RETRY_NOWAIT))
		जाओ unlock_mclk;

unlock_resv:
	dma_resv_unlock(bo->base.resv);

unlock_mclk:
	up_पढ़ो(&rdev->pm.mclk_lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा radeon_tपंचांग_vm_ops = अणु
	.fault = radeon_tपंचांग_fault,
	.खोलो = tपंचांग_bo_vm_खोलो,
	.बंद = tपंचांग_bo_vm_बंद,
	.access = tपंचांग_bo_vm_access
पूर्ण;

पूर्णांक radeon_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक r;
	काष्ठा drm_file *file_priv = filp->निजी_data;
	काष्ठा radeon_device *rdev = file_priv->minor->dev->dev_निजी;

	अगर (rdev == शून्य)
		वापस -EINVAL;

	r = tपंचांग_bo_mmap(filp, vma, &rdev->mman.bdev);
	अगर (unlikely(r != 0))
		वापस r;

	vma->vm_ops = &radeon_tपंचांग_vm_ops;
	वापस 0;
पूर्ण

#अगर defined(CONFIG_DEBUG_FS)

अटल पूर्णांक radeon_mm_vram_dump_table_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा radeon_device *rdev = (काष्ठा radeon_device *)m->निजी;
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(&rdev->mman.bdev,
							    TTM_PL_VRAM);
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	man->func->debug(man, &p);
	वापस 0;
पूर्ण

अटल पूर्णांक radeon_tपंचांग_page_pool_show(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा radeon_device *rdev = (काष्ठा radeon_device *)m->निजी;

	वापस tपंचांग_pool_debugfs(&rdev->mman.bdev.pool, m);
पूर्ण

अटल पूर्णांक radeon_mm_gtt_dump_table_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा radeon_device *rdev = (काष्ठा radeon_device *)m->निजी;
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(&rdev->mman.bdev,
							    TTM_PL_TT);
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	man->func->debug(man, &p);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(radeon_mm_vram_dump_table);
DEFINE_SHOW_ATTRIBUTE(radeon_mm_gtt_dump_table);
DEFINE_SHOW_ATTRIBUTE(radeon_tपंचांग_page_pool);

अटल पूर्णांक radeon_tपंचांग_vram_खोलो(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा radeon_device *rdev = inode->i_निजी;
	i_size_ग_लिखो(inode, rdev->mc.mc_vram_size);
	filep->निजी_data = inode->i_निजी;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार radeon_tपंचांग_vram_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
				    माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा radeon_device *rdev = f->निजी_data;
	sमाप_प्रकार result = 0;
	पूर्णांक r;

	अगर (size & 0x3 || *pos & 0x3)
		वापस -EINVAL;

	जबतक (size) अणु
		अचिन्हित दीर्घ flags;
		uपूर्णांक32_t value;

		अगर (*pos >= rdev->mc.mc_vram_size)
			वापस result;

		spin_lock_irqsave(&rdev->mmio_idx_lock, flags);
		WREG32(RADEON_MM_INDEX, ((uपूर्णांक32_t)*pos) | 0x80000000);
		अगर (rdev->family >= CHIP_CEDAR)
			WREG32(EVERGREEN_MM_INDEX_HI, *pos >> 31);
		value = RREG32(RADEON_MM_DATA);
		spin_unlock_irqrestore(&rdev->mmio_idx_lock, flags);

		r = put_user(value, (uपूर्णांक32_t __user *)buf);
		अगर (r)
			वापस r;

		result += 4;
		buf += 4;
		*pos += 4;
		size -= 4;
	पूर्ण

	वापस result;
पूर्ण

अटल स्थिर काष्ठा file_operations radeon_tपंचांग_vram_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = radeon_tपंचांग_vram_खोलो,
	.पढ़ो = radeon_tपंचांग_vram_पढ़ो,
	.llseek = शेष_llseek
पूर्ण;

अटल पूर्णांक radeon_tपंचांग_gtt_खोलो(काष्ठा inode *inode, काष्ठा file *filep)
अणु
	काष्ठा radeon_device *rdev = inode->i_निजी;
	i_size_ग_लिखो(inode, rdev->mc.gtt_size);
	filep->निजी_data = inode->i_निजी;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार radeon_tपंचांग_gtt_पढ़ो(काष्ठा file *f, अक्षर __user *buf,
				   माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा radeon_device *rdev = f->निजी_data;
	sमाप_प्रकार result = 0;
	पूर्णांक r;

	जबतक (size) अणु
		loff_t p = *pos / PAGE_SIZE;
		अचिन्हित off = *pos & ~PAGE_MASK;
		माप_प्रकार cur_size = min_t(माप_प्रकार, size, PAGE_SIZE - off);
		काष्ठा page *page;
		व्योम *ptr;

		अगर (p >= rdev->gart.num_cpu_pages)
			वापस result;

		page = rdev->gart.pages[p];
		अगर (page) अणु
			ptr = kmap(page);
			ptr += off;

			r = copy_to_user(buf, ptr, cur_size);
			kunmap(rdev->gart.pages[p]);
		पूर्ण अन्यथा
			r = clear_user(buf, cur_size);

		अगर (r)
			वापस -EFAULT;

		result += cur_size;
		buf += cur_size;
		*pos += cur_size;
		size -= cur_size;
	पूर्ण

	वापस result;
पूर्ण

अटल स्थिर काष्ठा file_operations radeon_tपंचांग_gtt_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = radeon_tपंचांग_gtt_खोलो,
	.पढ़ो = radeon_tपंचांग_gtt_पढ़ो,
	.llseek = शेष_llseek
पूर्ण;

#पूर्ण_अगर

अटल व्योम radeon_tपंचांग_debugfs_init(काष्ठा radeon_device *rdev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा drm_minor *minor = rdev->ddev->primary;
	काष्ठा dentry *root = minor->debugfs_root;

	debugfs_create_file("radeon_vram", 0444, root, rdev,
			    &radeon_tपंचांग_vram_fops);

	debugfs_create_file("radeon_gtt", 0444, root, rdev,
			    &radeon_tपंचांग_gtt_fops);

	debugfs_create_file("radeon_vram_mm", 0444, root, rdev,
			    &radeon_mm_vram_dump_table_fops);
	debugfs_create_file("radeon_gtt_mm", 0444, root, rdev,
			    &radeon_mm_gtt_dump_table_fops);
	debugfs_create_file("ttm_page_pool", 0444, root, rdev,
			    &radeon_tपंचांग_page_pool_fops);
#पूर्ण_अगर
पूर्ण
