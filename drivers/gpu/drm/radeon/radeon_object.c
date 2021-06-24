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

#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_cache.h>
#समावेश <drm/drm_prime.h>
#समावेश <drm/radeon_drm.h>

#समावेश "radeon.h"
#समावेश "radeon_trace.h"
#समावेश "radeon_ttm.h"

अटल व्योम radeon_bo_clear_surface_reg(काष्ठा radeon_bo *bo);

/*
 * To exclude mutual BO access we rely on bo_reserve exclusion, as all
 * function are calling it.
 */

अटल व्योम radeon_update_memory_usage(काष्ठा radeon_bo *bo,
				       अचिन्हित mem_type, पूर्णांक sign)
अणु
	काष्ठा radeon_device *rdev = bo->rdev;

	चयन (mem_type) अणु
	हाल TTM_PL_TT:
		अगर (sign > 0)
			atomic64_add(bo->tbo.base.size, &rdev->gtt_usage);
		अन्यथा
			atomic64_sub(bo->tbo.base.size, &rdev->gtt_usage);
		अवरोध;
	हाल TTM_PL_VRAM:
		अगर (sign > 0)
			atomic64_add(bo->tbo.base.size, &rdev->vram_usage);
		अन्यथा
			atomic64_sub(bo->tbo.base.size, &rdev->vram_usage);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम radeon_tपंचांग_bo_destroy(काष्ठा tपंचांग_buffer_object *tbo)
अणु
	काष्ठा radeon_bo *bo;

	bo = container_of(tbo, काष्ठा radeon_bo, tbo);

	radeon_update_memory_usage(bo, bo->tbo.mem.mem_type, -1);

	mutex_lock(&bo->rdev->gem.mutex);
	list_del_init(&bo->list);
	mutex_unlock(&bo->rdev->gem.mutex);
	radeon_bo_clear_surface_reg(bo);
	WARN_ON_ONCE(!list_empty(&bo->va));
	अगर (bo->tbo.base.import_attach)
		drm_prime_gem_destroy(&bo->tbo.base, bo->tbo.sg);
	drm_gem_object_release(&bo->tbo.base);
	kमुक्त(bo);
पूर्ण

bool radeon_tपंचांग_bo_is_radeon_bo(काष्ठा tपंचांग_buffer_object *bo)
अणु
	अगर (bo->destroy == &radeon_tपंचांग_bo_destroy)
		वापस true;
	वापस false;
पूर्ण

व्योम radeon_tपंचांग_placement_from_करोमुख्य(काष्ठा radeon_bo *rbo, u32 करोमुख्य)
अणु
	u32 c = 0, i;

	rbo->placement.placement = rbo->placements;
	rbo->placement.busy_placement = rbo->placements;
	अगर (करोमुख्य & RADEON_GEM_DOMAIN_VRAM) अणु
		/* Try placing BOs which करोn't need CPU access outside of the
		 * CPU accessible part of VRAM
		 */
		अगर ((rbo->flags & RADEON_GEM_NO_CPU_ACCESS) &&
		    rbo->rdev->mc.visible_vram_size < rbo->rdev->mc.real_vram_size) अणु
			rbo->placements[c].fpfn =
				rbo->rdev->mc.visible_vram_size >> PAGE_SHIFT;
			rbo->placements[c].mem_type = TTM_PL_VRAM;
			rbo->placements[c++].flags = 0;
		पूर्ण

		rbo->placements[c].fpfn = 0;
		rbo->placements[c].mem_type = TTM_PL_VRAM;
		rbo->placements[c++].flags = 0;
	पूर्ण

	अगर (करोमुख्य & RADEON_GEM_DOMAIN_GTT) अणु
		rbo->placements[c].fpfn = 0;
		rbo->placements[c].mem_type = TTM_PL_TT;
		rbo->placements[c++].flags = 0;
	पूर्ण

	अगर (करोमुख्य & RADEON_GEM_DOMAIN_CPU) अणु
		rbo->placements[c].fpfn = 0;
		rbo->placements[c].mem_type = TTM_PL_SYSTEM;
		rbo->placements[c++].flags = 0;
	पूर्ण
	अगर (!c) अणु
		rbo->placements[c].fpfn = 0;
		rbo->placements[c].mem_type = TTM_PL_SYSTEM;
		rbo->placements[c++].flags = 0;
	पूर्ण

	rbo->placement.num_placement = c;
	rbo->placement.num_busy_placement = c;

	क्रम (i = 0; i < c; ++i) अणु
		अगर ((rbo->flags & RADEON_GEM_CPU_ACCESS) &&
		    (rbo->placements[i].mem_type == TTM_PL_VRAM) &&
		    !rbo->placements[i].fpfn)
			rbo->placements[i].lpfn =
				rbo->rdev->mc.visible_vram_size >> PAGE_SHIFT;
		अन्यथा
			rbo->placements[i].lpfn = 0;
	पूर्ण
पूर्ण

पूर्णांक radeon_bo_create(काष्ठा radeon_device *rdev,
		     अचिन्हित दीर्घ size, पूर्णांक byte_align, bool kernel,
		     u32 करोमुख्य, u32 flags, काष्ठा sg_table *sg,
		     काष्ठा dma_resv *resv,
		     काष्ठा radeon_bo **bo_ptr)
अणु
	काष्ठा radeon_bo *bo;
	क्रमागत tपंचांग_bo_type type;
	अचिन्हित दीर्घ page_align = roundup(byte_align, PAGE_SIZE) >> PAGE_SHIFT;
	पूर्णांक r;

	size = ALIGN(size, PAGE_SIZE);

	अगर (kernel) अणु
		type = tपंचांग_bo_type_kernel;
	पूर्ण अन्यथा अगर (sg) अणु
		type = tपंचांग_bo_type_sg;
	पूर्ण अन्यथा अणु
		type = tपंचांग_bo_type_device;
	पूर्ण
	*bo_ptr = शून्य;

	bo = kzalloc(माप(काष्ठा radeon_bo), GFP_KERNEL);
	अगर (bo == शून्य)
		वापस -ENOMEM;
	drm_gem_निजी_object_init(rdev->ddev, &bo->tbo.base, size);
	bo->rdev = rdev;
	bo->surface_reg = -1;
	INIT_LIST_HEAD(&bo->list);
	INIT_LIST_HEAD(&bo->va);
	bo->initial_करोमुख्य = करोमुख्य & (RADEON_GEM_DOMAIN_VRAM |
				       RADEON_GEM_DOMAIN_GTT |
				       RADEON_GEM_DOMAIN_CPU);

	bo->flags = flags;
	/* PCI GART is always snooped */
	अगर (!(rdev->flags & RADEON_IS_PCIE))
		bo->flags &= ~(RADEON_GEM_GTT_WC | RADEON_GEM_GTT_UC);

	/* Write-combined CPU mappings of GTT cause GPU hangs with RV6xx
	 * See https://bugs.मुक्तdesktop.org/show_bug.cgi?id=91268
	 */
	अगर (rdev->family >= CHIP_RV610 && rdev->family <= CHIP_RV635)
		bo->flags &= ~(RADEON_GEM_GTT_WC | RADEON_GEM_GTT_UC);

#अगर_घोषित CONFIG_X86_32
	/* XXX: Write-combined CPU mappings of GTT seem broken on 32-bit
	 * See https://bugs.मुक्तdesktop.org/show_bug.cgi?id=84627
	 */
	bo->flags &= ~(RADEON_GEM_GTT_WC | RADEON_GEM_GTT_UC);
#या_अगर defined(CONFIG_X86) && !defined(CONFIG_X86_PAT)
	/* Don't try to enable write-combining when it can't work, or things
	 * may be slow
	 * See https://bugs.मुक्तdesktop.org/show_bug.cgi?id=88758
	 */
#अगर_अघोषित CONFIG_COMPILE_TEST
#warning Please enable CONFIG_MTRR and CONFIG_X86_PAT क्रम better perक्रमmance \
	 thanks to ग_लिखो-combining
#पूर्ण_अगर

	अगर (bo->flags & RADEON_GEM_GTT_WC)
		DRM_INFO_ONCE("Please enable CONFIG_MTRR and CONFIG_X86_PAT for "
			      "better performance thanks to write-combining\n");
	bo->flags &= ~(RADEON_GEM_GTT_WC | RADEON_GEM_GTT_UC);
#अन्यथा
	/* For architectures that करोn't support WC memory,
	 * mask out the WC flag from the BO
	 */
	अगर (!drm_arch_can_wc_memory())
		bo->flags &= ~RADEON_GEM_GTT_WC;
#पूर्ण_अगर

	radeon_tपंचांग_placement_from_करोमुख्य(bo, करोमुख्य);
	/* Kernel allocation are unपूर्णांकerruptible */
	करोwn_पढ़ो(&rdev->pm.mclk_lock);
	r = tपंचांग_bo_init(&rdev->mman.bdev, &bo->tbo, size, type,
			&bo->placement, page_align, !kernel, sg, resv,
			&radeon_tपंचांग_bo_destroy);
	up_पढ़ो(&rdev->pm.mclk_lock);
	अगर (unlikely(r != 0)) अणु
		वापस r;
	पूर्ण
	*bo_ptr = bo;

	trace_radeon_bo_create(bo);

	वापस 0;
पूर्ण

पूर्णांक radeon_bo_kmap(काष्ठा radeon_bo *bo, व्योम **ptr)
अणु
	bool is_iomem;
	पूर्णांक r;

	अगर (bo->kptr) अणु
		अगर (ptr) अणु
			*ptr = bo->kptr;
		पूर्ण
		वापस 0;
	पूर्ण
	r = tपंचांग_bo_kmap(&bo->tbo, 0, bo->tbo.mem.num_pages, &bo->kmap);
	अगर (r) अणु
		वापस r;
	पूर्ण
	bo->kptr = tपंचांग_kmap_obj_भव(&bo->kmap, &is_iomem);
	अगर (ptr) अणु
		*ptr = bo->kptr;
	पूर्ण
	radeon_bo_check_tiling(bo, 0, 0);
	वापस 0;
पूर्ण

व्योम radeon_bo_kunmap(काष्ठा radeon_bo *bo)
अणु
	अगर (bo->kptr == शून्य)
		वापस;
	bo->kptr = शून्य;
	radeon_bo_check_tiling(bo, 0, 0);
	tपंचांग_bo_kunmap(&bo->kmap);
पूर्ण

काष्ठा radeon_bo *radeon_bo_ref(काष्ठा radeon_bo *bo)
अणु
	अगर (bo == शून्य)
		वापस शून्य;

	tपंचांग_bo_get(&bo->tbo);
	वापस bo;
पूर्ण

व्योम radeon_bo_unref(काष्ठा radeon_bo **bo)
अणु
	काष्ठा tपंचांग_buffer_object *tbo;

	अगर ((*bo) == शून्य)
		वापस;
	tbo = &((*bo)->tbo);
	tपंचांग_bo_put(tbo);
	*bo = शून्य;
पूर्ण

पूर्णांक radeon_bo_pin_restricted(काष्ठा radeon_bo *bo, u32 करोमुख्य, u64 max_offset,
			     u64 *gpu_addr)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु false, false पूर्ण;
	पूर्णांक r, i;

	अगर (radeon_tपंचांग_tt_has_userptr(bo->rdev, bo->tbo.tपंचांग))
		वापस -EPERM;

	अगर (bo->tbo.pin_count) अणु
		tपंचांग_bo_pin(&bo->tbo);
		अगर (gpu_addr)
			*gpu_addr = radeon_bo_gpu_offset(bo);

		अगर (max_offset != 0) अणु
			u64 करोमुख्य_start;

			अगर (करोमुख्य == RADEON_GEM_DOMAIN_VRAM)
				करोमुख्य_start = bo->rdev->mc.vram_start;
			अन्यथा
				करोमुख्य_start = bo->rdev->mc.gtt_start;
			WARN_ON_ONCE(max_offset <
				     (radeon_bo_gpu_offset(bo) - करोमुख्य_start));
		पूर्ण

		वापस 0;
	पूर्ण
	अगर (bo->prime_shared_count && करोमुख्य == RADEON_GEM_DOMAIN_VRAM) अणु
		/* A BO shared as a dma-buf cannot be sensibly migrated to VRAM */
		वापस -EINVAL;
	पूर्ण

	radeon_tपंचांग_placement_from_करोमुख्य(bo, करोमुख्य);
	क्रम (i = 0; i < bo->placement.num_placement; i++) अणु
		/* क्रमce to pin पूर्णांकo visible video ram */
		अगर ((bo->placements[i].mem_type == TTM_PL_VRAM) &&
		    !(bo->flags & RADEON_GEM_NO_CPU_ACCESS) &&
		    (!max_offset || max_offset > bo->rdev->mc.visible_vram_size))
			bo->placements[i].lpfn =
				bo->rdev->mc.visible_vram_size >> PAGE_SHIFT;
		अन्यथा
			bo->placements[i].lpfn = max_offset >> PAGE_SHIFT;
	पूर्ण

	r = tपंचांग_bo_validate(&bo->tbo, &bo->placement, &ctx);
	अगर (likely(r == 0)) अणु
		tपंचांग_bo_pin(&bo->tbo);
		अगर (gpu_addr != शून्य)
			*gpu_addr = radeon_bo_gpu_offset(bo);
		अगर (करोमुख्य == RADEON_GEM_DOMAIN_VRAM)
			bo->rdev->vram_pin_size += radeon_bo_size(bo);
		अन्यथा
			bo->rdev->gart_pin_size += radeon_bo_size(bo);
	पूर्ण अन्यथा अणु
		dev_err(bo->rdev->dev, "%p pin failed\n", bo);
	पूर्ण
	वापस r;
पूर्ण

पूर्णांक radeon_bo_pin(काष्ठा radeon_bo *bo, u32 करोमुख्य, u64 *gpu_addr)
अणु
	वापस radeon_bo_pin_restricted(bo, करोमुख्य, 0, gpu_addr);
पूर्ण

व्योम radeon_bo_unpin(काष्ठा radeon_bo *bo)
अणु
	tपंचांग_bo_unpin(&bo->tbo);
	अगर (!bo->tbo.pin_count) अणु
		अगर (bo->tbo.mem.mem_type == TTM_PL_VRAM)
			bo->rdev->vram_pin_size -= radeon_bo_size(bo);
		अन्यथा
			bo->rdev->gart_pin_size -= radeon_bo_size(bo);
	पूर्ण
पूर्ण

पूर्णांक radeon_bo_evict_vram(काष्ठा radeon_device *rdev)
अणु
	काष्ठा tपंचांग_device *bdev = &rdev->mman.bdev;
	काष्ठा tपंचांग_resource_manager *man;

	/* late 2.6.33 fix IGP hibernate - we need pm ops to करो this correct */
#अगर_अघोषित CONFIG_HIBERNATION
	अगर (rdev->flags & RADEON_IS_IGP) अणु
		अगर (rdev->mc.igp_sideport_enabled == false)
			/* Useless to evict on IGP chips */
			वापस 0;
	पूर्ण
#पूर्ण_अगर
	man = tपंचांग_manager_type(bdev, TTM_PL_VRAM);
	अगर (!man)
		वापस 0;
	वापस tपंचांग_resource_manager_evict_all(bdev, man);
पूर्ण

व्योम radeon_bo_क्रमce_delete(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_bo *bo, *n;

	अगर (list_empty(&rdev->gem.objects)) अणु
		वापस;
	पूर्ण
	dev_err(rdev->dev, "Userspace still has active objects !\n");
	list_क्रम_each_entry_safe(bo, n, &rdev->gem.objects, list) अणु
		dev_err(rdev->dev, "%p %p %lu %lu force free\n",
			&bo->tbo.base, bo, (अचिन्हित दीर्घ)bo->tbo.base.size,
			*((अचिन्हित दीर्घ *)&bo->tbo.base.refcount));
		mutex_lock(&bo->rdev->gem.mutex);
		list_del_init(&bo->list);
		mutex_unlock(&bo->rdev->gem.mutex);
		/* this should unref the tपंचांग bo */
		drm_gem_object_put(&bo->tbo.base);
	पूर्ण
पूर्ण

पूर्णांक radeon_bo_init(काष्ठा radeon_device *rdev)
अणु
	/* reserve PAT memory space to WC क्रम VRAM */
	arch_io_reserve_memtype_wc(rdev->mc.aper_base,
				   rdev->mc.aper_size);

	/* Add an MTRR क्रम the VRAM */
	अगर (!rdev->fastfb_working) अणु
		rdev->mc.vram_mtrr = arch_phys_wc_add(rdev->mc.aper_base,
						      rdev->mc.aper_size);
	पूर्ण
	DRM_INFO("Detected VRAM RAM=%lluM, BAR=%lluM\n",
		rdev->mc.mc_vram_size >> 20,
		(अचिन्हित दीर्घ दीर्घ)rdev->mc.aper_size >> 20);
	DRM_INFO("RAM width %dbits %cDR\n",
			rdev->mc.vram_width, rdev->mc.vram_is_ddr ? 'D' : 'S');
	वापस radeon_tपंचांग_init(rdev);
पूर्ण

व्योम radeon_bo_fini(काष्ठा radeon_device *rdev)
अणु
	radeon_tपंचांग_fini(rdev);
	arch_phys_wc_del(rdev->mc.vram_mtrr);
	arch_io_मुक्त_memtype_wc(rdev->mc.aper_base, rdev->mc.aper_size);
पूर्ण

/* Returns how many bytes TTM can move per IB.
 */
अटल u64 radeon_bo_get_threshold_क्रम_moves(काष्ठा radeon_device *rdev)
अणु
	u64 real_vram_size = rdev->mc.real_vram_size;
	u64 vram_usage = atomic64_पढ़ो(&rdev->vram_usage);

	/* This function is based on the current VRAM usage.
	 *
	 * - If all of VRAM is मुक्त, allow relocating the number of bytes that
	 *   is equal to 1/4 of the size of VRAM क्रम this IB.

	 * - If more than one half of VRAM is occupied, only allow relocating
	 *   1 MB of data क्रम this IB.
	 *
	 * - From 0 to one half of used VRAM, the threshold decreases
	 *   linearly.
	 *         __________________
	 * 1/4 of -|\               |
	 * VRAM    | \              |
	 *         |  \             |
	 *         |   \            |
	 *         |    \           |
	 *         |     \          |
	 *         |      \         |
	 *         |       \________|1 MB
	 *         |----------------|
	 *    VRAM 0 %             100 %
	 *         used            used
	 *
	 * Note: It's a threshold, not a limit. The threshold must be crossed
	 * क्रम buffer relocations to stop, so any buffer of an arbitrary size
	 * can be moved as दीर्घ as the threshold isn't crossed beक्रमe
	 * the relocation takes place. We करोn't want to disable buffer
	 * relocations completely.
	 *
	 * The idea is that buffers should be placed in VRAM at creation समय
	 * and TTM should only करो a minimum number of relocations during
	 * command submission. In practice, you need to submit at least
	 * a करोzen IBs to move all buffers to VRAM अगर they are in GTT.
	 *
	 * Also, things can get pretty crazy under memory pressure and actual
	 * VRAM usage can change a lot, so playing safe even at 50% करोes
	 * consistently increase perक्रमmance.
	 */

	u64 half_vram = real_vram_size >> 1;
	u64 half_मुक्त_vram = vram_usage >= half_vram ? 0 : half_vram - vram_usage;
	u64 bytes_moved_threshold = half_मुक्त_vram >> 1;
	वापस max(bytes_moved_threshold, 1024*1024ull);
पूर्ण

पूर्णांक radeon_bo_list_validate(काष्ठा radeon_device *rdev,
			    काष्ठा ww_acquire_ctx *ticket,
			    काष्ठा list_head *head, पूर्णांक ring)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु true, false पूर्ण;
	काष्ठा radeon_bo_list *lobj;
	काष्ठा list_head duplicates;
	पूर्णांक r;
	u64 bytes_moved = 0, initial_bytes_moved;
	u64 bytes_moved_threshold = radeon_bo_get_threshold_क्रम_moves(rdev);

	INIT_LIST_HEAD(&duplicates);
	r = tपंचांग_eu_reserve_buffers(ticket, head, true, &duplicates);
	अगर (unlikely(r != 0)) अणु
		वापस r;
	पूर्ण

	list_क्रम_each_entry(lobj, head, tv.head) अणु
		काष्ठा radeon_bo *bo = lobj->robj;
		अगर (!bo->tbo.pin_count) अणु
			u32 करोमुख्य = lobj->preferred_करोमुख्यs;
			u32 allowed = lobj->allowed_करोमुख्यs;
			u32 current_करोमुख्य =
				radeon_mem_type_to_करोमुख्य(bo->tbo.mem.mem_type);

			/* Check अगर this buffer will be moved and करोn't move it
			 * अगर we have moved too many buffers क्रम this IB alपढ़ोy.
			 *
			 * Note that this allows moving at least one buffer of
			 * any size, because it करोesn't take the current "bo"
			 * पूर्णांकo account. We करोn't want to disallow buffer moves
			 * completely.
			 */
			अगर ((allowed & current_करोमुख्य) != 0 &&
			    (करोमुख्य & current_करोमुख्य) == 0 && /* will be moved */
			    bytes_moved > bytes_moved_threshold) अणु
				/* करोn't move it */
				करोमुख्य = current_करोमुख्य;
			पूर्ण

		retry:
			radeon_tपंचांग_placement_from_करोमुख्य(bo, करोमुख्य);
			अगर (ring == R600_RING_TYPE_UVD_INDEX)
				radeon_uvd_क्रमce_पूर्णांकo_uvd_segment(bo, allowed);

			initial_bytes_moved = atomic64_पढ़ो(&rdev->num_bytes_moved);
			r = tपंचांग_bo_validate(&bo->tbo, &bo->placement, &ctx);
			bytes_moved += atomic64_पढ़ो(&rdev->num_bytes_moved) -
				       initial_bytes_moved;

			अगर (unlikely(r)) अणु
				अगर (r != -ERESTARTSYS &&
				    करोमुख्य != lobj->allowed_करोमुख्यs) अणु
					करोमुख्य = lobj->allowed_करोमुख्यs;
					जाओ retry;
				पूर्ण
				tपंचांग_eu_backoff_reservation(ticket, head);
				वापस r;
			पूर्ण
		पूर्ण
		lobj->gpu_offset = radeon_bo_gpu_offset(bo);
		lobj->tiling_flags = bo->tiling_flags;
	पूर्ण

	list_क्रम_each_entry(lobj, &duplicates, tv.head) अणु
		lobj->gpu_offset = radeon_bo_gpu_offset(lobj->robj);
		lobj->tiling_flags = lobj->robj->tiling_flags;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक radeon_bo_get_surface_reg(काष्ठा radeon_bo *bo)
अणु
	काष्ठा radeon_device *rdev = bo->rdev;
	काष्ठा radeon_surface_reg *reg;
	काष्ठा radeon_bo *old_object;
	पूर्णांक steal;
	पूर्णांक i;

	dma_resv_निश्चित_held(bo->tbo.base.resv);

	अगर (!bo->tiling_flags)
		वापस 0;

	अगर (bo->surface_reg >= 0) अणु
		reg = &rdev->surface_regs[bo->surface_reg];
		i = bo->surface_reg;
		जाओ out;
	पूर्ण

	steal = -1;
	क्रम (i = 0; i < RADEON_GEM_MAX_SURFACES; i++) अणु

		reg = &rdev->surface_regs[i];
		अगर (!reg->bo)
			अवरोध;

		old_object = reg->bo;
		अगर (old_object->tbo.pin_count == 0)
			steal = i;
	पूर्ण

	/* अगर we are all out */
	अगर (i == RADEON_GEM_MAX_SURFACES) अणु
		अगर (steal == -1)
			वापस -ENOMEM;
		/* find someone with a surface reg and nuke their BO */
		reg = &rdev->surface_regs[steal];
		old_object = reg->bo;
		/* blow away the mapping */
		DRM_DEBUG("stealing surface reg %d from %p\n", steal, old_object);
		tपंचांग_bo_unmap_भव(&old_object->tbo);
		old_object->surface_reg = -1;
		i = steal;
	पूर्ण

	bo->surface_reg = i;
	reg->bo = bo;

out:
	radeon_set_surface_reg(rdev, i, bo->tiling_flags, bo->pitch,
			       bo->tbo.mem.start << PAGE_SHIFT,
			       bo->tbo.base.size);
	वापस 0;
पूर्ण

अटल व्योम radeon_bo_clear_surface_reg(काष्ठा radeon_bo *bo)
अणु
	काष्ठा radeon_device *rdev = bo->rdev;
	काष्ठा radeon_surface_reg *reg;

	अगर (bo->surface_reg == -1)
		वापस;

	reg = &rdev->surface_regs[bo->surface_reg];
	radeon_clear_surface_reg(rdev, bo->surface_reg);

	reg->bo = शून्य;
	bo->surface_reg = -1;
पूर्ण

पूर्णांक radeon_bo_set_tiling_flags(काष्ठा radeon_bo *bo,
				uपूर्णांक32_t tiling_flags, uपूर्णांक32_t pitch)
अणु
	काष्ठा radeon_device *rdev = bo->rdev;
	पूर्णांक r;

	अगर (rdev->family >= CHIP_CEDAR) अणु
		अचिन्हित bankw, bankh, mtaspect, tilesplit, stilesplit;

		bankw = (tiling_flags >> RADEON_TILING_EG_BANKW_SHIFT) & RADEON_TILING_EG_BANKW_MASK;
		bankh = (tiling_flags >> RADEON_TILING_EG_BANKH_SHIFT) & RADEON_TILING_EG_BANKH_MASK;
		mtaspect = (tiling_flags >> RADEON_TILING_EG_MACRO_TILE_ASPECT_SHIFT) & RADEON_TILING_EG_MACRO_TILE_ASPECT_MASK;
		tilesplit = (tiling_flags >> RADEON_TILING_EG_TILE_SPLIT_SHIFT) & RADEON_TILING_EG_TILE_SPLIT_MASK;
		stilesplit = (tiling_flags >> RADEON_TILING_EG_STENCIL_TILE_SPLIT_SHIFT) & RADEON_TILING_EG_STENCIL_TILE_SPLIT_MASK;
		चयन (bankw) अणु
		हाल 0:
		हाल 1:
		हाल 2:
		हाल 4:
		हाल 8:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		चयन (bankh) अणु
		हाल 0:
		हाल 1:
		हाल 2:
		हाल 4:
		हाल 8:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		चयन (mtaspect) अणु
		हाल 0:
		हाल 1:
		हाल 2:
		हाल 4:
		हाल 8:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अगर (tilesplit > 6) अणु
			वापस -EINVAL;
		पूर्ण
		अगर (stilesplit > 6) अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	r = radeon_bo_reserve(bo, false);
	अगर (unlikely(r != 0))
		वापस r;
	bo->tiling_flags = tiling_flags;
	bo->pitch = pitch;
	radeon_bo_unreserve(bo);
	वापस 0;
पूर्ण

व्योम radeon_bo_get_tiling_flags(काष्ठा radeon_bo *bo,
				uपूर्णांक32_t *tiling_flags,
				uपूर्णांक32_t *pitch)
अणु
	dma_resv_निश्चित_held(bo->tbo.base.resv);

	अगर (tiling_flags)
		*tiling_flags = bo->tiling_flags;
	अगर (pitch)
		*pitch = bo->pitch;
पूर्ण

पूर्णांक radeon_bo_check_tiling(काष्ठा radeon_bo *bo, bool has_moved,
				bool क्रमce_drop)
अणु
	अगर (!क्रमce_drop)
		dma_resv_निश्चित_held(bo->tbo.base.resv);

	अगर (!(bo->tiling_flags & RADEON_TILING_SURFACE))
		वापस 0;

	अगर (क्रमce_drop) अणु
		radeon_bo_clear_surface_reg(bo);
		वापस 0;
	पूर्ण

	अगर (bo->tbo.mem.mem_type != TTM_PL_VRAM) अणु
		अगर (!has_moved)
			वापस 0;

		अगर (bo->surface_reg >= 0)
			radeon_bo_clear_surface_reg(bo);
		वापस 0;
	पूर्ण

	अगर ((bo->surface_reg >= 0) && !has_moved)
		वापस 0;

	वापस radeon_bo_get_surface_reg(bo);
पूर्ण

व्योम radeon_bo_move_notअगरy(काष्ठा tपंचांग_buffer_object *bo,
			   bool evict,
			   काष्ठा tपंचांग_resource *new_mem)
अणु
	काष्ठा radeon_bo *rbo;

	अगर (!radeon_tपंचांग_bo_is_radeon_bo(bo))
		वापस;

	rbo = container_of(bo, काष्ठा radeon_bo, tbo);
	radeon_bo_check_tiling(rbo, 0, 1);
	radeon_vm_bo_invalidate(rbo->rdev, rbo);

	/* update statistics */
	अगर (!new_mem)
		वापस;

	radeon_update_memory_usage(rbo, bo->mem.mem_type, -1);
	radeon_update_memory_usage(rbo, new_mem->mem_type, 1);
पूर्ण

vm_fault_t radeon_bo_fault_reserve_notअगरy(काष्ठा tपंचांग_buffer_object *bo)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु false, false पूर्ण;
	काष्ठा radeon_device *rdev;
	काष्ठा radeon_bo *rbo;
	अचिन्हित दीर्घ offset, size, lpfn;
	पूर्णांक i, r;

	अगर (!radeon_tपंचांग_bo_is_radeon_bo(bo))
		वापस 0;
	rbo = container_of(bo, काष्ठा radeon_bo, tbo);
	radeon_bo_check_tiling(rbo, 0, 0);
	rdev = rbo->rdev;
	अगर (bo->mem.mem_type != TTM_PL_VRAM)
		वापस 0;

	size = bo->mem.num_pages << PAGE_SHIFT;
	offset = bo->mem.start << PAGE_SHIFT;
	अगर ((offset + size) <= rdev->mc.visible_vram_size)
		वापस 0;

	/* Can't move a pinned BO to visible VRAM */
	अगर (rbo->tbo.pin_count > 0)
		वापस VM_FAULT_SIGBUS;

	/* hurrah the memory is not visible ! */
	radeon_tपंचांग_placement_from_करोमुख्य(rbo, RADEON_GEM_DOMAIN_VRAM);
	lpfn =	rdev->mc.visible_vram_size >> PAGE_SHIFT;
	क्रम (i = 0; i < rbo->placement.num_placement; i++) अणु
		/* Force पूर्णांकo visible VRAM */
		अगर ((rbo->placements[i].mem_type == TTM_PL_VRAM) &&
		    (!rbo->placements[i].lpfn || rbo->placements[i].lpfn > lpfn))
			rbo->placements[i].lpfn = lpfn;
	पूर्ण
	r = tपंचांग_bo_validate(bo, &rbo->placement, &ctx);
	अगर (unlikely(r == -ENOMEM)) अणु
		radeon_tपंचांग_placement_from_करोमुख्य(rbo, RADEON_GEM_DOMAIN_GTT);
		r = tपंचांग_bo_validate(bo, &rbo->placement, &ctx);
	पूर्ण अन्यथा अगर (likely(!r)) अणु
		offset = bo->mem.start << PAGE_SHIFT;
		/* this should never happen */
		अगर ((offset + size) > rdev->mc.visible_vram_size)
			वापस VM_FAULT_SIGBUS;
	पूर्ण

	अगर (unlikely(r == -EBUSY || r == -ERESTARTSYS))
		वापस VM_FAULT_NOPAGE;
	अन्यथा अगर (unlikely(r))
		वापस VM_FAULT_SIGBUS;

	tपंचांग_bo_move_to_lru_tail_unlocked(bo);
	वापस 0;
पूर्ण

/**
 * radeon_bo_fence - add fence to buffer object
 *
 * @bo: buffer object in question
 * @fence: fence to add
 * @shared: true अगर fence should be added shared
 *
 */
व्योम radeon_bo_fence(काष्ठा radeon_bo *bo, काष्ठा radeon_fence *fence,
		     bool shared)
अणु
	काष्ठा dma_resv *resv = bo->tbo.base.resv;

	अगर (shared)
		dma_resv_add_shared_fence(resv, &fence->base);
	अन्यथा
		dma_resv_add_excl_fence(resv, &fence->base);
पूर्ण
