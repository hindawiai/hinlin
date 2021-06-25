<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2020 Intel Corporation
 */

#समावेश <linux/stop_machine.h>

#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/smp.h>

#समावेश <drm/i915_drm.h>

#समावेश "gem/i915_gem_lmem.h"

#समावेश "intel_gt.h"
#समावेश "i915_drv.h"
#समावेश "i915_scatterlist.h"
#समावेश "i915_vgpu.h"

#समावेश "intel_gtt.h"

अटल पूर्णांक
i915_get_ggtt_vma_pages(काष्ठा i915_vma *vma);

अटल व्योम i915_ggtt_color_adjust(स्थिर काष्ठा drm_mm_node *node,
				   अचिन्हित दीर्घ color,
				   u64 *start,
				   u64 *end)
अणु
	अगर (i915_node_color_dअगरfers(node, color))
		*start += I915_GTT_PAGE_SIZE;

	/*
	 * Also leave a space between the unallocated reserved node after the
	 * GTT and any objects within the GTT, i.e. we use the color adjusपंचांगent
	 * to insert a guard page to prevent prefetches crossing over the
	 * GTT boundary.
	 */
	node = list_next_entry(node, node_list);
	अगर (node->color != color)
		*end -= I915_GTT_PAGE_SIZE;
पूर्ण

अटल पूर्णांक ggtt_init_hw(काष्ठा i915_ggtt *ggtt)
अणु
	काष्ठा drm_i915_निजी *i915 = ggtt->vm.i915;

	i915_address_space_init(&ggtt->vm, VM_CLASS_GGTT);

	ggtt->vm.is_ggtt = true;

	/* Only VLV supports पढ़ो-only GGTT mappings */
	ggtt->vm.has_पढ़ो_only = IS_VALLEYVIEW(i915);

	अगर (!HAS_LLC(i915) && !HAS_PPGTT(i915))
		ggtt->vm.mm.color_adjust = i915_ggtt_color_adjust;

	अगर (ggtt->mappable_end) अणु
		अगर (!io_mapping_init_wc(&ggtt->iomap,
					ggtt->gmadr.start,
					ggtt->mappable_end)) अणु
			ggtt->vm.cleanup(&ggtt->vm);
			वापस -EIO;
		पूर्ण

		ggtt->mtrr = arch_phys_wc_add(ggtt->gmadr.start,
					      ggtt->mappable_end);
	पूर्ण

	पूर्णांकel_ggtt_init_fences(ggtt);

	वापस 0;
पूर्ण

/**
 * i915_ggtt_init_hw - Initialize GGTT hardware
 * @i915: i915 device
 */
पूर्णांक i915_ggtt_init_hw(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांक ret;

	/*
	 * Note that we use page colouring to enक्रमce a guard page at the
	 * end of the address space. This is required as the CS may prefetch
	 * beyond the end of the batch buffer, across the page boundary,
	 * and beyond the end of the GTT अगर we करो not provide a guard.
	 */
	ret = ggtt_init_hw(&i915->ggtt);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/*
 * Certain Gen5 chipsets require idling the GPU beक्रमe
 * unmapping anything from the GTT when VT-d is enabled.
 */
अटल bool needs_idle_maps(काष्ठा drm_i915_निजी *i915)
अणु
	/*
	 * Query पूर्णांकel_iommu to see अगर we need the workaround. Presumably that
	 * was loaded first.
	 */
	अगर (!पूर्णांकel_vtd_active())
		वापस false;

	अगर (IS_GEN(i915, 5) && IS_MOBILE(i915))
		वापस true;

	अगर (IS_GEN(i915, 12))
		वापस true; /* XXX DMAR fault reason 7 */

	वापस false;
पूर्ण

व्योम i915_ggtt_suspend(काष्ठा i915_ggtt *ggtt)
अणु
	काष्ठा i915_vma *vma, *vn;
	पूर्णांक खोलो;

	mutex_lock(&ggtt->vm.mutex);

	/* Skip rewriting PTE on VMA unbind. */
	खोलो = atomic_xchg(&ggtt->vm.खोलो, 0);

	list_क्रम_each_entry_safe(vma, vn, &ggtt->vm.bound_list, vm_link) अणु
		GEM_BUG_ON(!drm_mm_node_allocated(&vma->node));
		i915_vma_रुको_क्रम_bind(vma);

		अगर (i915_vma_is_pinned(vma))
			जारी;

		अगर (!i915_vma_is_bound(vma, I915_VMA_GLOBAL_BIND)) अणु
			__i915_vma_evict(vma);
			drm_mm_हटाओ_node(&vma->node);
		पूर्ण
	पूर्ण

	ggtt->vm.clear_range(&ggtt->vm, 0, ggtt->vm.total);
	ggtt->invalidate(ggtt);
	atomic_set(&ggtt->vm.खोलो, खोलो);

	mutex_unlock(&ggtt->vm.mutex);

	पूर्णांकel_gt_check_and_clear_faults(ggtt->vm.gt);
पूर्ण

व्योम gen6_ggtt_invalidate(काष्ठा i915_ggtt *ggtt)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = ggtt->vm.gt->uncore;

	spin_lock_irq(&uncore->lock);
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GFX_FLSH_CNTL_GEN6, GFX_FLSH_CNTL_EN);
	पूर्णांकel_uncore_पढ़ो_fw(uncore, GFX_FLSH_CNTL_GEN6);
	spin_unlock_irq(&uncore->lock);
पूर्ण

अटल व्योम gen8_ggtt_invalidate(काष्ठा i915_ggtt *ggtt)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = ggtt->vm.gt->uncore;

	/*
	 * Note that as an uncached mmio ग_लिखो, this will flush the
	 * WCB of the ग_लिखोs पूर्णांकo the GGTT beक्रमe it triggers the invalidate.
	 */
	पूर्णांकel_uncore_ग_लिखो_fw(uncore, GFX_FLSH_CNTL_GEN6, GFX_FLSH_CNTL_EN);
पूर्ण

अटल व्योम guc_ggtt_invalidate(काष्ठा i915_ggtt *ggtt)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = ggtt->vm.gt->uncore;
	काष्ठा drm_i915_निजी *i915 = ggtt->vm.i915;

	gen8_ggtt_invalidate(ggtt);

	अगर (INTEL_GEN(i915) >= 12)
		पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN12_GUC_TLB_INV_CR,
				      GEN12_GUC_TLB_INV_CR_INVALIDATE);
	अन्यथा
		पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN8_GTCR, GEN8_GTCR_INVALIDATE);
पूर्ण

अटल व्योम gmch_ggtt_invalidate(काष्ठा i915_ggtt *ggtt)
अणु
	पूर्णांकel_gtt_chipset_flush();
पूर्ण

अटल u64 gen8_ggtt_pte_encode(dma_addr_t addr,
				क्रमागत i915_cache_level level,
				u32 flags)
अणु
	gen8_pte_t pte = addr | _PAGE_PRESENT;

	अगर (flags & PTE_LM)
		pte |= GEN12_GGTT_PTE_LM;

	वापस pte;
पूर्ण

अटल व्योम gen8_set_pte(व्योम __iomem *addr, gen8_pte_t pte)
अणु
	ग_लिखोq(pte, addr);
पूर्ण

अटल व्योम gen8_ggtt_insert_page(काष्ठा i915_address_space *vm,
				  dma_addr_t addr,
				  u64 offset,
				  क्रमागत i915_cache_level level,
				  u32 flags)
अणु
	काष्ठा i915_ggtt *ggtt = i915_vm_to_ggtt(vm);
	gen8_pte_t __iomem *pte =
		(gen8_pte_t __iomem *)ggtt->gsm + offset / I915_GTT_PAGE_SIZE;

	gen8_set_pte(pte, gen8_ggtt_pte_encode(addr, level, flags));

	ggtt->invalidate(ggtt);
पूर्ण

अटल व्योम gen8_ggtt_insert_entries(काष्ठा i915_address_space *vm,
				     काष्ठा i915_vma *vma,
				     क्रमागत i915_cache_level level,
				     u32 flags)
अणु
	स्थिर gen8_pte_t pte_encode = gen8_ggtt_pte_encode(0, level, flags);
	काष्ठा i915_ggtt *ggtt = i915_vm_to_ggtt(vm);
	gen8_pte_t __iomem *gte;
	gen8_pte_t __iomem *end;
	काष्ठा sgt_iter iter;
	dma_addr_t addr;

	/*
	 * Note that we ignore PTE_READ_ONLY here. The caller must be careful
	 * not to allow the user to override access to a पढ़ो only page.
	 */

	gte = (gen8_pte_t __iomem *)ggtt->gsm;
	gte += vma->node.start / I915_GTT_PAGE_SIZE;
	end = gte + vma->node.size / I915_GTT_PAGE_SIZE;

	क्रम_each_sgt_daddr(addr, iter, vma->pages)
		gen8_set_pte(gte++, pte_encode | addr);
	GEM_BUG_ON(gte > end);

	/* Fill the allocated but "unused" space beyond the end of the buffer */
	जबतक (gte < end)
		gen8_set_pte(gte++, vm->scratch[0]->encode);

	/*
	 * We want to flush the TLBs only after we're certain all the PTE
	 * updates have finished.
	 */
	ggtt->invalidate(ggtt);
पूर्ण

अटल व्योम gen6_ggtt_insert_page(काष्ठा i915_address_space *vm,
				  dma_addr_t addr,
				  u64 offset,
				  क्रमागत i915_cache_level level,
				  u32 flags)
अणु
	काष्ठा i915_ggtt *ggtt = i915_vm_to_ggtt(vm);
	gen6_pte_t __iomem *pte =
		(gen6_pte_t __iomem *)ggtt->gsm + offset / I915_GTT_PAGE_SIZE;

	ioग_लिखो32(vm->pte_encode(addr, level, flags), pte);

	ggtt->invalidate(ggtt);
पूर्ण

/*
 * Binds an object पूर्णांकo the global gtt with the specअगरied cache level.
 * The object will be accessible to the GPU via commands whose opeअक्रमs
 * reference offsets within the global GTT as well as accessible by the GPU
 * through the GMADR mapped BAR (i915->mm.gtt->gtt).
 */
अटल व्योम gen6_ggtt_insert_entries(काष्ठा i915_address_space *vm,
				     काष्ठा i915_vma *vma,
				     क्रमागत i915_cache_level level,
				     u32 flags)
अणु
	काष्ठा i915_ggtt *ggtt = i915_vm_to_ggtt(vm);
	gen6_pte_t __iomem *gte;
	gen6_pte_t __iomem *end;
	काष्ठा sgt_iter iter;
	dma_addr_t addr;

	gte = (gen6_pte_t __iomem *)ggtt->gsm;
	gte += vma->node.start / I915_GTT_PAGE_SIZE;
	end = gte + vma->node.size / I915_GTT_PAGE_SIZE;

	क्रम_each_sgt_daddr(addr, iter, vma->pages)
		ioग_लिखो32(vm->pte_encode(addr, level, flags), gte++);
	GEM_BUG_ON(gte > end);

	/* Fill the allocated but "unused" space beyond the end of the buffer */
	जबतक (gte < end)
		ioग_लिखो32(vm->scratch[0]->encode, gte++);

	/*
	 * We want to flush the TLBs only after we're certain all the PTE
	 * updates have finished.
	 */
	ggtt->invalidate(ggtt);
पूर्ण

अटल व्योम nop_clear_range(काष्ठा i915_address_space *vm,
			    u64 start, u64 length)
अणु
पूर्ण

अटल व्योम gen8_ggtt_clear_range(काष्ठा i915_address_space *vm,
				  u64 start, u64 length)
अणु
	काष्ठा i915_ggtt *ggtt = i915_vm_to_ggtt(vm);
	अचिन्हित पूर्णांक first_entry = start / I915_GTT_PAGE_SIZE;
	अचिन्हित पूर्णांक num_entries = length / I915_GTT_PAGE_SIZE;
	स्थिर gen8_pte_t scratch_pte = vm->scratch[0]->encode;
	gen8_pte_t __iomem *gtt_base =
		(gen8_pte_t __iomem *)ggtt->gsm + first_entry;
	स्थिर पूर्णांक max_entries = ggtt_total_entries(ggtt) - first_entry;
	पूर्णांक i;

	अगर (WARN(num_entries > max_entries,
		 "First entry = %d; Num entries = %d (max=%d)\n",
		 first_entry, num_entries, max_entries))
		num_entries = max_entries;

	क्रम (i = 0; i < num_entries; i++)
		gen8_set_pte(&gtt_base[i], scratch_pte);
पूर्ण

अटल व्योम bxt_vtd_ggtt_wa(काष्ठा i915_address_space *vm)
अणु
	/*
	 * Make sure the पूर्णांकernal GAM fअगरo has been cleared of all GTT
	 * ग_लिखोs beक्रमe निकासing stop_machine(). This guarantees that
	 * any aperture accesses रुकोing to start in another process
	 * cannot back up behind the GTT ग_लिखोs causing a hang.
	 * The रेजिस्टर can be any arbitrary GAM रेजिस्टर.
	 */
	पूर्णांकel_uncore_posting_पढ़ो_fw(vm->gt->uncore, GFX_FLSH_CNTL_GEN6);
पूर्ण

काष्ठा insert_page अणु
	काष्ठा i915_address_space *vm;
	dma_addr_t addr;
	u64 offset;
	क्रमागत i915_cache_level level;
पूर्ण;

अटल पूर्णांक bxt_vtd_ggtt_insert_page__cb(व्योम *_arg)
अणु
	काष्ठा insert_page *arg = _arg;

	gen8_ggtt_insert_page(arg->vm, arg->addr, arg->offset, arg->level, 0);
	bxt_vtd_ggtt_wa(arg->vm);

	वापस 0;
पूर्ण

अटल व्योम bxt_vtd_ggtt_insert_page__BKL(काष्ठा i915_address_space *vm,
					  dma_addr_t addr,
					  u64 offset,
					  क्रमागत i915_cache_level level,
					  u32 unused)
अणु
	काष्ठा insert_page arg = अणु vm, addr, offset, level पूर्ण;

	stop_machine(bxt_vtd_ggtt_insert_page__cb, &arg, शून्य);
पूर्ण

काष्ठा insert_entries अणु
	काष्ठा i915_address_space *vm;
	काष्ठा i915_vma *vma;
	क्रमागत i915_cache_level level;
	u32 flags;
पूर्ण;

अटल पूर्णांक bxt_vtd_ggtt_insert_entries__cb(व्योम *_arg)
अणु
	काष्ठा insert_entries *arg = _arg;

	gen8_ggtt_insert_entries(arg->vm, arg->vma, arg->level, arg->flags);
	bxt_vtd_ggtt_wa(arg->vm);

	वापस 0;
पूर्ण

अटल व्योम bxt_vtd_ggtt_insert_entries__BKL(काष्ठा i915_address_space *vm,
					     काष्ठा i915_vma *vma,
					     क्रमागत i915_cache_level level,
					     u32 flags)
अणु
	काष्ठा insert_entries arg = अणु vm, vma, level, flags पूर्ण;

	stop_machine(bxt_vtd_ggtt_insert_entries__cb, &arg, शून्य);
पूर्ण

अटल व्योम gen6_ggtt_clear_range(काष्ठा i915_address_space *vm,
				  u64 start, u64 length)
अणु
	काष्ठा i915_ggtt *ggtt = i915_vm_to_ggtt(vm);
	अचिन्हित पूर्णांक first_entry = start / I915_GTT_PAGE_SIZE;
	अचिन्हित पूर्णांक num_entries = length / I915_GTT_PAGE_SIZE;
	gen6_pte_t scratch_pte, __iomem *gtt_base =
		(gen6_pte_t __iomem *)ggtt->gsm + first_entry;
	स्थिर पूर्णांक max_entries = ggtt_total_entries(ggtt) - first_entry;
	पूर्णांक i;

	अगर (WARN(num_entries > max_entries,
		 "First entry = %d; Num entries = %d (max=%d)\n",
		 first_entry, num_entries, max_entries))
		num_entries = max_entries;

	scratch_pte = vm->scratch[0]->encode;
	क्रम (i = 0; i < num_entries; i++)
		ioग_लिखो32(scratch_pte, &gtt_base[i]);
पूर्ण

अटल व्योम i915_ggtt_insert_page(काष्ठा i915_address_space *vm,
				  dma_addr_t addr,
				  u64 offset,
				  क्रमागत i915_cache_level cache_level,
				  u32 unused)
अणु
	अचिन्हित पूर्णांक flags = (cache_level == I915_CACHE_NONE) ?
		AGP_USER_MEMORY : AGP_USER_CACHED_MEMORY;

	पूर्णांकel_gtt_insert_page(addr, offset >> PAGE_SHIFT, flags);
पूर्ण

अटल व्योम i915_ggtt_insert_entries(काष्ठा i915_address_space *vm,
				     काष्ठा i915_vma *vma,
				     क्रमागत i915_cache_level cache_level,
				     u32 unused)
अणु
	अचिन्हित पूर्णांक flags = (cache_level == I915_CACHE_NONE) ?
		AGP_USER_MEMORY : AGP_USER_CACHED_MEMORY;

	पूर्णांकel_gtt_insert_sg_entries(vma->pages, vma->node.start >> PAGE_SHIFT,
				    flags);
पूर्ण

अटल व्योम i915_ggtt_clear_range(काष्ठा i915_address_space *vm,
				  u64 start, u64 length)
अणु
	पूर्णांकel_gtt_clear_range(start >> PAGE_SHIFT, length >> PAGE_SHIFT);
पूर्ण

अटल व्योम ggtt_bind_vma(काष्ठा i915_address_space *vm,
			  काष्ठा i915_vm_pt_stash *stash,
			  काष्ठा i915_vma *vma,
			  क्रमागत i915_cache_level cache_level,
			  u32 flags)
अणु
	काष्ठा drm_i915_gem_object *obj = vma->obj;
	u32 pte_flags;

	अगर (i915_vma_is_bound(vma, ~flags & I915_VMA_BIND_MASK))
		वापस;

	/* Applicable to VLV (gen8+ करो not support RO in the GGTT) */
	pte_flags = 0;
	अगर (i915_gem_object_is_पढ़ोonly(obj))
		pte_flags |= PTE_READ_ONLY;
	अगर (i915_gem_object_is_lmem(obj))
		pte_flags |= PTE_LM;

	vm->insert_entries(vm, vma, cache_level, pte_flags);
	vma->page_sizes.gtt = I915_GTT_PAGE_SIZE;
पूर्ण

अटल व्योम ggtt_unbind_vma(काष्ठा i915_address_space *vm, काष्ठा i915_vma *vma)
अणु
	vm->clear_range(vm, vma->node.start, vma->size);
पूर्ण

अटल पूर्णांक ggtt_reserve_guc_top(काष्ठा i915_ggtt *ggtt)
अणु
	u64 size;
	पूर्णांक ret;

	अगर (!पूर्णांकel_uc_uses_guc(&ggtt->vm.gt->uc))
		वापस 0;

	GEM_BUG_ON(ggtt->vm.total <= GUC_GGTT_TOP);
	size = ggtt->vm.total - GUC_GGTT_TOP;

	ret = i915_gem_gtt_reserve(&ggtt->vm, &ggtt->uc_fw, size,
				   GUC_GGTT_TOP, I915_COLOR_UNEVICTABLE,
				   PIN_NOEVICT);
	अगर (ret)
		drm_dbg(&ggtt->vm.i915->drm,
			"Failed to reserve top of GGTT for GuC\n");

	वापस ret;
पूर्ण

अटल व्योम ggtt_release_guc_top(काष्ठा i915_ggtt *ggtt)
अणु
	अगर (drm_mm_node_allocated(&ggtt->uc_fw))
		drm_mm_हटाओ_node(&ggtt->uc_fw);
पूर्ण

अटल व्योम cleanup_init_ggtt(काष्ठा i915_ggtt *ggtt)
अणु
	ggtt_release_guc_top(ggtt);
	अगर (drm_mm_node_allocated(&ggtt->error_capture))
		drm_mm_हटाओ_node(&ggtt->error_capture);
	mutex_destroy(&ggtt->error_mutex);
पूर्ण

अटल पूर्णांक init_ggtt(काष्ठा i915_ggtt *ggtt)
अणु
	/*
	 * Let GEM Manage all of the aperture.
	 *
	 * However, leave one page at the end still bound to the scratch page.
	 * There are a number of places where the hardware apparently prefetches
	 * past the end of the object, and we've seen multiple hangs with the
	 * GPU head poपूर्णांकer stuck in a batchbuffer bound at the last page of the
	 * aperture.  One page should be enough to keep any prefetching inside
	 * of the aperture.
	 */
	अचिन्हित दीर्घ hole_start, hole_end;
	काष्ठा drm_mm_node *entry;
	पूर्णांक ret;

	/*
	 * GuC requires all resources that we're sharing with it to be placed in
	 * non-WOPCM memory. If GuC is not present or not in use we still need a
	 * small bias as ring wraparound at offset 0 someबार hangs. No idea
	 * why.
	 */
	ggtt->pin_bias = max_t(u32, I915_GTT_PAGE_SIZE,
			       पूर्णांकel_wopcm_guc_size(&ggtt->vm.i915->wopcm));

	ret = पूर्णांकel_vgt_balloon(ggtt);
	अगर (ret)
		वापस ret;

	mutex_init(&ggtt->error_mutex);
	अगर (ggtt->mappable_end) अणु
		/*
		 * Reserve a mappable slot क्रम our lockless error capture.
		 *
		 * We strongly prefer taking address 0x0 in order to protect
		 * other critical buffers against accidental overग_लिखोs,
		 * as writing to address 0 is a very common mistake.
		 *
		 * Since 0 may alपढ़ोy be in use by the प्रणाली (e.g. the BIOS
		 * framebuffer), we let the reservation fail quietly and hope
		 * 0 reमुख्यs reserved always.
		 *
		 * If we fail to reserve 0, and then fail to find any space
		 * क्रम an error-capture, reमुख्य silent. We can afक्रमd not
		 * to reserve an error_capture node as we have fallback
		 * paths, and we trust that 0 will reमुख्य reserved. However,
		 * the only likely reason क्रम failure to insert is a driver
		 * bug, which we expect to cause other failures...
		 */
		ggtt->error_capture.size = I915_GTT_PAGE_SIZE;
		ggtt->error_capture.color = I915_COLOR_UNEVICTABLE;
		अगर (drm_mm_reserve_node(&ggtt->vm.mm, &ggtt->error_capture))
			drm_mm_insert_node_in_range(&ggtt->vm.mm,
						    &ggtt->error_capture,
						    ggtt->error_capture.size, 0,
						    ggtt->error_capture.color,
						    0, ggtt->mappable_end,
						    DRM_MM_INSERT_LOW);
	पूर्ण
	अगर (drm_mm_node_allocated(&ggtt->error_capture))
		drm_dbg(&ggtt->vm.i915->drm,
			"Reserved GGTT:[%llx, %llx] for use by error capture\n",
			ggtt->error_capture.start,
			ggtt->error_capture.start + ggtt->error_capture.size);

	/*
	 * The upper portion of the GuC address space has a sizeable hole
	 * (several MB) that is inaccessible by GuC. Reserve this range within
	 * GGTT as it can comक्रमtably hold GuC/HuC firmware images.
	 */
	ret = ggtt_reserve_guc_top(ggtt);
	अगर (ret)
		जाओ err;

	/* Clear any non-pपुनः_स्मृतिated blocks */
	drm_mm_क्रम_each_hole(entry, &ggtt->vm.mm, hole_start, hole_end) अणु
		drm_dbg(&ggtt->vm.i915->drm,
			"clearing unused GTT space: [%lx, %lx]\n",
			hole_start, hole_end);
		ggtt->vm.clear_range(&ggtt->vm, hole_start,
				     hole_end - hole_start);
	पूर्ण

	/* And finally clear the reserved guard page */
	ggtt->vm.clear_range(&ggtt->vm, ggtt->vm.total - PAGE_SIZE, PAGE_SIZE);

	वापस 0;

err:
	cleanup_init_ggtt(ggtt);
	वापस ret;
पूर्ण

अटल व्योम aliasing_gtt_bind_vma(काष्ठा i915_address_space *vm,
				  काष्ठा i915_vm_pt_stash *stash,
				  काष्ठा i915_vma *vma,
				  क्रमागत i915_cache_level cache_level,
				  u32 flags)
अणु
	u32 pte_flags;

	/* Currently applicable only to VLV */
	pte_flags = 0;
	अगर (i915_gem_object_is_पढ़ोonly(vma->obj))
		pte_flags |= PTE_READ_ONLY;

	अगर (flags & I915_VMA_LOCAL_BIND)
		ppgtt_bind_vma(&i915_vm_to_ggtt(vm)->alias->vm,
			       stash, vma, cache_level, flags);

	अगर (flags & I915_VMA_GLOBAL_BIND)
		vm->insert_entries(vm, vma, cache_level, pte_flags);
पूर्ण

अटल व्योम aliasing_gtt_unbind_vma(काष्ठा i915_address_space *vm,
				    काष्ठा i915_vma *vma)
अणु
	अगर (i915_vma_is_bound(vma, I915_VMA_GLOBAL_BIND))
		vm->clear_range(vm, vma->node.start, vma->size);

	अगर (i915_vma_is_bound(vma, I915_VMA_LOCAL_BIND))
		ppgtt_unbind_vma(&i915_vm_to_ggtt(vm)->alias->vm, vma);
पूर्ण

अटल पूर्णांक init_aliasing_ppgtt(काष्ठा i915_ggtt *ggtt)
अणु
	काष्ठा i915_vm_pt_stash stash = अणुपूर्ण;
	काष्ठा i915_ppgtt *ppgtt;
	पूर्णांक err;

	ppgtt = i915_ppgtt_create(ggtt->vm.gt);
	अगर (IS_ERR(ppgtt))
		वापस PTR_ERR(ppgtt);

	अगर (GEM_WARN_ON(ppgtt->vm.total < ggtt->vm.total)) अणु
		err = -ENODEV;
		जाओ err_ppgtt;
	पूर्ण

	err = i915_vm_alloc_pt_stash(&ppgtt->vm, &stash, ggtt->vm.total);
	अगर (err)
		जाओ err_ppgtt;

	i915_gem_object_lock(ppgtt->vm.scratch[0], शून्य);
	err = i915_vm_pin_pt_stash(&ppgtt->vm, &stash);
	i915_gem_object_unlock(ppgtt->vm.scratch[0]);
	अगर (err)
		जाओ err_stash;

	/*
	 * Note we only pre-allocate as far as the end of the global
	 * GTT. On 48b / 4-level page-tables, the dअगरference is very,
	 * very signअगरicant! We have to pपुनः_स्मृतिate as GVT/vgpu करोes
	 * not like the page directory disappearing.
	 */
	ppgtt->vm.allocate_va_range(&ppgtt->vm, &stash, 0, ggtt->vm.total);

	ggtt->alias = ppgtt;
	ggtt->vm.bind_async_flags |= ppgtt->vm.bind_async_flags;

	GEM_BUG_ON(ggtt->vm.vma_ops.bind_vma != ggtt_bind_vma);
	ggtt->vm.vma_ops.bind_vma = aliasing_gtt_bind_vma;

	GEM_BUG_ON(ggtt->vm.vma_ops.unbind_vma != ggtt_unbind_vma);
	ggtt->vm.vma_ops.unbind_vma = aliasing_gtt_unbind_vma;

	i915_vm_मुक्त_pt_stash(&ppgtt->vm, &stash);
	वापस 0;

err_stash:
	i915_vm_मुक्त_pt_stash(&ppgtt->vm, &stash);
err_ppgtt:
	i915_vm_put(&ppgtt->vm);
	वापस err;
पूर्ण

अटल व्योम fini_aliasing_ppgtt(काष्ठा i915_ggtt *ggtt)
अणु
	काष्ठा i915_ppgtt *ppgtt;

	ppgtt = fetch_and_zero(&ggtt->alias);
	अगर (!ppgtt)
		वापस;

	i915_vm_put(&ppgtt->vm);

	ggtt->vm.vma_ops.bind_vma   = ggtt_bind_vma;
	ggtt->vm.vma_ops.unbind_vma = ggtt_unbind_vma;
पूर्ण

पूर्णांक i915_init_ggtt(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांक ret;

	ret = init_ggtt(&i915->ggtt);
	अगर (ret)
		वापस ret;

	अगर (INTEL_PPGTT(i915) == INTEL_PPGTT_ALIASING) अणु
		ret = init_aliasing_ppgtt(&i915->ggtt);
		अगर (ret)
			cleanup_init_ggtt(&i915->ggtt);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ggtt_cleanup_hw(काष्ठा i915_ggtt *ggtt)
अणु
	काष्ठा i915_vma *vma, *vn;

	atomic_set(&ggtt->vm.खोलो, 0);

	rcu_barrier(); /* flush the RCU'ed__i915_vm_release */
	flush_workqueue(ggtt->vm.i915->wq);

	mutex_lock(&ggtt->vm.mutex);

	list_क्रम_each_entry_safe(vma, vn, &ggtt->vm.bound_list, vm_link)
		WARN_ON(__i915_vma_unbind(vma));

	अगर (drm_mm_node_allocated(&ggtt->error_capture))
		drm_mm_हटाओ_node(&ggtt->error_capture);
	mutex_destroy(&ggtt->error_mutex);

	ggtt_release_guc_top(ggtt);
	पूर्णांकel_vgt_deballoon(ggtt);

	ggtt->vm.cleanup(&ggtt->vm);

	mutex_unlock(&ggtt->vm.mutex);
	i915_address_space_fini(&ggtt->vm);
	dma_resv_fini(&ggtt->vm.resv);

	arch_phys_wc_del(ggtt->mtrr);

	अगर (ggtt->iomap.size)
		io_mapping_fini(&ggtt->iomap);
पूर्ण

/**
 * i915_ggtt_driver_release - Clean up GGTT hardware initialization
 * @i915: i915 device
 */
व्योम i915_ggtt_driver_release(काष्ठा drm_i915_निजी *i915)
अणु
	काष्ठा i915_ggtt *ggtt = &i915->ggtt;

	fini_aliasing_ppgtt(ggtt);

	पूर्णांकel_ggtt_fini_fences(ggtt);
	ggtt_cleanup_hw(ggtt);
पूर्ण

अटल अचिन्हित पूर्णांक gen6_get_total_gtt_size(u16 snb_gmch_ctl)
अणु
	snb_gmch_ctl >>= SNB_GMCH_GGMS_SHIFT;
	snb_gmch_ctl &= SNB_GMCH_GGMS_MASK;
	वापस snb_gmch_ctl << 20;
पूर्ण

अटल अचिन्हित पूर्णांक gen8_get_total_gtt_size(u16 bdw_gmch_ctl)
अणु
	bdw_gmch_ctl >>= BDW_GMCH_GGMS_SHIFT;
	bdw_gmch_ctl &= BDW_GMCH_GGMS_MASK;
	अगर (bdw_gmch_ctl)
		bdw_gmch_ctl = 1 << bdw_gmch_ctl;

#अगर_घोषित CONFIG_X86_32
	/* Limit 32b platक्रमms to a 2GB GGTT: 4 << 20 / pte size * I915_GTT_PAGE_SIZE */
	अगर (bdw_gmch_ctl > 4)
		bdw_gmch_ctl = 4;
#पूर्ण_अगर

	वापस bdw_gmch_ctl << 20;
पूर्ण

अटल अचिन्हित पूर्णांक chv_get_total_gtt_size(u16 gmch_ctrl)
अणु
	gmch_ctrl >>= SNB_GMCH_GGMS_SHIFT;
	gmch_ctrl &= SNB_GMCH_GGMS_MASK;

	अगर (gmch_ctrl)
		वापस 1 << (20 + gmch_ctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक ggtt_probe_common(काष्ठा i915_ggtt *ggtt, u64 size)
अणु
	काष्ठा drm_i915_निजी *i915 = ggtt->vm.i915;
	काष्ठा pci_dev *pdev = to_pci_dev(i915->drm.dev);
	phys_addr_t phys_addr;
	u32 pte_flags;
	पूर्णांक ret;

	/* For Modern GENs the PTEs and रेजिस्टर space are split in the BAR */
	phys_addr = pci_resource_start(pdev, 0) + pci_resource_len(pdev, 0) / 2;

	/*
	 * On BXT+/CNL+ ग_लिखोs larger than 64 bit to the GTT pagetable range
	 * will be dropped. For WC mappings in general we have 64 byte burst
	 * ग_लिखोs when the WC buffer is flushed, so we can't use it, but have to
	 * resort to an uncached mapping. The WC issue is easily caught by the
	 * पढ़ोback check when writing GTT PTE entries.
	 */
	अगर (IS_GEN9_LP(i915) || INTEL_GEN(i915) >= 10)
		ggtt->gsm = ioremap(phys_addr, size);
	अन्यथा
		ggtt->gsm = ioremap_wc(phys_addr, size);
	अगर (!ggtt->gsm) अणु
		drm_err(&i915->drm, "Failed to map the ggtt page table\n");
		वापस -ENOMEM;
	पूर्ण

	ret = setup_scratch_page(&ggtt->vm);
	अगर (ret) अणु
		drm_err(&i915->drm, "Scratch setup failed\n");
		/* iounmap will also get called at हटाओ, but meh */
		iounmap(ggtt->gsm);
		वापस ret;
	पूर्ण

	pte_flags = 0;
	अगर (i915_gem_object_is_lmem(ggtt->vm.scratch[0]))
		pte_flags |= PTE_LM;

	ggtt->vm.scratch[0]->encode =
		ggtt->vm.pte_encode(px_dma(ggtt->vm.scratch[0]),
				    I915_CACHE_NONE, pte_flags);

	वापस 0;
पूर्ण

पूर्णांक ggtt_set_pages(काष्ठा i915_vma *vma)
अणु
	पूर्णांक ret;

	GEM_BUG_ON(vma->pages);

	ret = i915_get_ggtt_vma_pages(vma);
	अगर (ret)
		वापस ret;

	vma->page_sizes = vma->obj->mm.page_sizes;

	वापस 0;
पूर्ण

अटल व्योम gen6_gmch_हटाओ(काष्ठा i915_address_space *vm)
अणु
	काष्ठा i915_ggtt *ggtt = i915_vm_to_ggtt(vm);

	iounmap(ggtt->gsm);
	मुक्त_scratch(vm);
पूर्ण

अटल काष्ठा resource pci_resource(काष्ठा pci_dev *pdev, पूर्णांक bar)
अणु
	वापस (काष्ठा resource)DEFINE_RES_MEM(pci_resource_start(pdev, bar),
					       pci_resource_len(pdev, bar));
पूर्ण

अटल पूर्णांक gen8_gmch_probe(काष्ठा i915_ggtt *ggtt)
अणु
	काष्ठा drm_i915_निजी *i915 = ggtt->vm.i915;
	काष्ठा pci_dev *pdev = to_pci_dev(i915->drm.dev);
	अचिन्हित पूर्णांक size;
	u16 snb_gmch_ctl;

	/* TODO: We're not aware of mappable स्थिरraपूर्णांकs on gen8 yet */
	अगर (!HAS_LMEM(i915)) अणु
		ggtt->gmadr = pci_resource(pdev, 2);
		ggtt->mappable_end = resource_size(&ggtt->gmadr);
	पूर्ण

	pci_पढ़ो_config_word(pdev, SNB_GMCH_CTRL, &snb_gmch_ctl);
	अगर (IS_CHERRYVIEW(i915))
		size = chv_get_total_gtt_size(snb_gmch_ctl);
	अन्यथा
		size = gen8_get_total_gtt_size(snb_gmch_ctl);

	ggtt->vm.alloc_pt_dma = alloc_pt_dma;

	ggtt->vm.total = (size / माप(gen8_pte_t)) * I915_GTT_PAGE_SIZE;
	ggtt->vm.cleanup = gen6_gmch_हटाओ;
	ggtt->vm.insert_page = gen8_ggtt_insert_page;
	ggtt->vm.clear_range = nop_clear_range;
	अगर (पूर्णांकel_scanout_needs_vtd_wa(i915))
		ggtt->vm.clear_range = gen8_ggtt_clear_range;

	ggtt->vm.insert_entries = gen8_ggtt_insert_entries;

	/* Serialize GTT updates with aperture access on BXT अगर VT-d is on. */
	अगर (पूर्णांकel_ggtt_update_needs_vtd_wa(i915) ||
	    IS_CHERRYVIEW(i915) /* fails with concurrent use/update */) अणु
		ggtt->vm.insert_entries = bxt_vtd_ggtt_insert_entries__BKL;
		ggtt->vm.insert_page    = bxt_vtd_ggtt_insert_page__BKL;
		ggtt->vm.bind_async_flags =
			I915_VMA_GLOBAL_BIND | I915_VMA_LOCAL_BIND;
	पूर्ण

	ggtt->invalidate = gen8_ggtt_invalidate;

	ggtt->vm.vma_ops.bind_vma    = ggtt_bind_vma;
	ggtt->vm.vma_ops.unbind_vma  = ggtt_unbind_vma;
	ggtt->vm.vma_ops.set_pages   = ggtt_set_pages;
	ggtt->vm.vma_ops.clear_pages = clear_pages;

	ggtt->vm.pte_encode = gen8_ggtt_pte_encode;

	setup_निजी_pat(ggtt->vm.gt->uncore);

	वापस ggtt_probe_common(ggtt, size);
पूर्ण

अटल u64 snb_pte_encode(dma_addr_t addr,
			  क्रमागत i915_cache_level level,
			  u32 flags)
अणु
	gen6_pte_t pte = GEN6_PTE_ADDR_ENCODE(addr) | GEN6_PTE_VALID;

	चयन (level) अणु
	हाल I915_CACHE_L3_LLC:
	हाल I915_CACHE_LLC:
		pte |= GEN6_PTE_CACHE_LLC;
		अवरोध;
	हाल I915_CACHE_NONE:
		pte |= GEN6_PTE_UNCACHED;
		अवरोध;
	शेष:
		MISSING_CASE(level);
	पूर्ण

	वापस pte;
पूर्ण

अटल u64 ivb_pte_encode(dma_addr_t addr,
			  क्रमागत i915_cache_level level,
			  u32 flags)
अणु
	gen6_pte_t pte = GEN6_PTE_ADDR_ENCODE(addr) | GEN6_PTE_VALID;

	चयन (level) अणु
	हाल I915_CACHE_L3_LLC:
		pte |= GEN7_PTE_CACHE_L3_LLC;
		अवरोध;
	हाल I915_CACHE_LLC:
		pte |= GEN6_PTE_CACHE_LLC;
		अवरोध;
	हाल I915_CACHE_NONE:
		pte |= GEN6_PTE_UNCACHED;
		अवरोध;
	शेष:
		MISSING_CASE(level);
	पूर्ण

	वापस pte;
पूर्ण

अटल u64 byt_pte_encode(dma_addr_t addr,
			  क्रमागत i915_cache_level level,
			  u32 flags)
अणु
	gen6_pte_t pte = GEN6_PTE_ADDR_ENCODE(addr) | GEN6_PTE_VALID;

	अगर (!(flags & PTE_READ_ONLY))
		pte |= BYT_PTE_WRITEABLE;

	अगर (level != I915_CACHE_NONE)
		pte |= BYT_PTE_SNOOPED_BY_CPU_CACHES;

	वापस pte;
पूर्ण

अटल u64 hsw_pte_encode(dma_addr_t addr,
			  क्रमागत i915_cache_level level,
			  u32 flags)
अणु
	gen6_pte_t pte = HSW_PTE_ADDR_ENCODE(addr) | GEN6_PTE_VALID;

	अगर (level != I915_CACHE_NONE)
		pte |= HSW_WB_LLC_AGE3;

	वापस pte;
पूर्ण

अटल u64 iris_pte_encode(dma_addr_t addr,
			   क्रमागत i915_cache_level level,
			   u32 flags)
अणु
	gen6_pte_t pte = HSW_PTE_ADDR_ENCODE(addr) | GEN6_PTE_VALID;

	चयन (level) अणु
	हाल I915_CACHE_NONE:
		अवरोध;
	हाल I915_CACHE_WT:
		pte |= HSW_WT_ELLC_LLC_AGE3;
		अवरोध;
	शेष:
		pte |= HSW_WB_ELLC_LLC_AGE3;
		अवरोध;
	पूर्ण

	वापस pte;
पूर्ण

अटल पूर्णांक gen6_gmch_probe(काष्ठा i915_ggtt *ggtt)
अणु
	काष्ठा drm_i915_निजी *i915 = ggtt->vm.i915;
	काष्ठा pci_dev *pdev = to_pci_dev(i915->drm.dev);
	अचिन्हित पूर्णांक size;
	u16 snb_gmch_ctl;

	ggtt->gmadr = pci_resource(pdev, 2);
	ggtt->mappable_end = resource_size(&ggtt->gmadr);

	/*
	 * 64/512MB is the current min/max we actually know of, but this is
	 * just a coarse sanity check.
	 */
	अगर (ggtt->mappable_end < (64<<20) || ggtt->mappable_end > (512<<20)) अणु
		drm_err(&i915->drm, "Unknown GMADR size (%pa)\n",
			&ggtt->mappable_end);
		वापस -ENXIO;
	पूर्ण

	pci_पढ़ो_config_word(pdev, SNB_GMCH_CTRL, &snb_gmch_ctl);

	size = gen6_get_total_gtt_size(snb_gmch_ctl);
	ggtt->vm.total = (size / माप(gen6_pte_t)) * I915_GTT_PAGE_SIZE;

	ggtt->vm.alloc_pt_dma = alloc_pt_dma;

	ggtt->vm.clear_range = nop_clear_range;
	अगर (!HAS_FULL_PPGTT(i915) || पूर्णांकel_scanout_needs_vtd_wa(i915))
		ggtt->vm.clear_range = gen6_ggtt_clear_range;
	ggtt->vm.insert_page = gen6_ggtt_insert_page;
	ggtt->vm.insert_entries = gen6_ggtt_insert_entries;
	ggtt->vm.cleanup = gen6_gmch_हटाओ;

	ggtt->invalidate = gen6_ggtt_invalidate;

	अगर (HAS_EDRAM(i915))
		ggtt->vm.pte_encode = iris_pte_encode;
	अन्यथा अगर (IS_HASWELL(i915))
		ggtt->vm.pte_encode = hsw_pte_encode;
	अन्यथा अगर (IS_VALLEYVIEW(i915))
		ggtt->vm.pte_encode = byt_pte_encode;
	अन्यथा अगर (INTEL_GEN(i915) >= 7)
		ggtt->vm.pte_encode = ivb_pte_encode;
	अन्यथा
		ggtt->vm.pte_encode = snb_pte_encode;

	ggtt->vm.vma_ops.bind_vma    = ggtt_bind_vma;
	ggtt->vm.vma_ops.unbind_vma  = ggtt_unbind_vma;
	ggtt->vm.vma_ops.set_pages   = ggtt_set_pages;
	ggtt->vm.vma_ops.clear_pages = clear_pages;

	वापस ggtt_probe_common(ggtt, size);
पूर्ण

अटल व्योम i915_gmch_हटाओ(काष्ठा i915_address_space *vm)
अणु
	पूर्णांकel_gmch_हटाओ();
पूर्ण

अटल पूर्णांक i915_gmch_probe(काष्ठा i915_ggtt *ggtt)
अणु
	काष्ठा drm_i915_निजी *i915 = ggtt->vm.i915;
	phys_addr_t gmadr_base;
	पूर्णांक ret;

	ret = पूर्णांकel_gmch_probe(i915->bridge_dev, to_pci_dev(i915->drm.dev), शून्य);
	अगर (!ret) अणु
		drm_err(&i915->drm, "failed to set up gmch\n");
		वापस -EIO;
	पूर्ण

	पूर्णांकel_gtt_get(&ggtt->vm.total, &gmadr_base, &ggtt->mappable_end);

	ggtt->gmadr =
		(काष्ठा resource)DEFINE_RES_MEM(gmadr_base, ggtt->mappable_end);

	ggtt->vm.alloc_pt_dma = alloc_pt_dma;

	अगर (needs_idle_maps(i915)) अणु
		drm_notice(&i915->drm,
			   "Flushing DMA requests before IOMMU unmaps; performance may be degraded\n");
		ggtt->करो_idle_maps = true;
	पूर्ण

	ggtt->vm.insert_page = i915_ggtt_insert_page;
	ggtt->vm.insert_entries = i915_ggtt_insert_entries;
	ggtt->vm.clear_range = i915_ggtt_clear_range;
	ggtt->vm.cleanup = i915_gmch_हटाओ;

	ggtt->invalidate = gmch_ggtt_invalidate;

	ggtt->vm.vma_ops.bind_vma    = ggtt_bind_vma;
	ggtt->vm.vma_ops.unbind_vma  = ggtt_unbind_vma;
	ggtt->vm.vma_ops.set_pages   = ggtt_set_pages;
	ggtt->vm.vma_ops.clear_pages = clear_pages;

	अगर (unlikely(ggtt->करो_idle_maps))
		drm_notice(&i915->drm,
			   "Applying Ironlake quirks for intel_iommu\n");

	वापस 0;
पूर्ण

अटल पूर्णांक ggtt_probe_hw(काष्ठा i915_ggtt *ggtt, काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	पूर्णांक ret;

	ggtt->vm.gt = gt;
	ggtt->vm.i915 = i915;
	ggtt->vm.dma = i915->drm.dev;
	dma_resv_init(&ggtt->vm.resv);

	अगर (INTEL_GEN(i915) <= 5)
		ret = i915_gmch_probe(ggtt);
	अन्यथा अगर (INTEL_GEN(i915) < 8)
		ret = gen6_gmch_probe(ggtt);
	अन्यथा
		ret = gen8_gmch_probe(ggtt);
	अगर (ret) अणु
		dma_resv_fini(&ggtt->vm.resv);
		वापस ret;
	पूर्ण

	अगर ((ggtt->vm.total - 1) >> 32) अणु
		drm_err(&i915->drm,
			"We never expected a Global GTT with more than 32bits"
			" of address space! Found %lldM!\n",
			ggtt->vm.total >> 20);
		ggtt->vm.total = 1ULL << 32;
		ggtt->mappable_end =
			min_t(u64, ggtt->mappable_end, ggtt->vm.total);
	पूर्ण

	अगर (ggtt->mappable_end > ggtt->vm.total) अणु
		drm_err(&i915->drm,
			"mappable aperture extends past end of GGTT,"
			" aperture=%pa, total=%llx\n",
			&ggtt->mappable_end, ggtt->vm.total);
		ggtt->mappable_end = ggtt->vm.total;
	पूर्ण

	/* GMADR is the PCI mmio aperture पूर्णांकo the global GTT. */
	drm_dbg(&i915->drm, "GGTT size = %lluM\n", ggtt->vm.total >> 20);
	drm_dbg(&i915->drm, "GMADR size = %lluM\n",
		(u64)ggtt->mappable_end >> 20);
	drm_dbg(&i915->drm, "DSM size = %lluM\n",
		(u64)resource_size(&पूर्णांकel_graphics_stolen_res) >> 20);

	वापस 0;
पूर्ण

/**
 * i915_ggtt_probe_hw - Probe GGTT hardware location
 * @i915: i915 device
 */
पूर्णांक i915_ggtt_probe_hw(काष्ठा drm_i915_निजी *i915)
अणु
	पूर्णांक ret;

	ret = ggtt_probe_hw(&i915->ggtt, &i915->gt);
	अगर (ret)
		वापस ret;

	अगर (पूर्णांकel_vtd_active())
		drm_info(&i915->drm, "VT-d active for gfx access\n");

	वापस 0;
पूर्ण

पूर्णांक i915_ggtt_enable_hw(काष्ठा drm_i915_निजी *i915)
अणु
	अगर (INTEL_GEN(i915) < 6 && !पूर्णांकel_enable_gtt())
		वापस -EIO;

	वापस 0;
पूर्ण

व्योम i915_ggtt_enable_guc(काष्ठा i915_ggtt *ggtt)
अणु
	GEM_BUG_ON(ggtt->invalidate != gen8_ggtt_invalidate);

	ggtt->invalidate = guc_ggtt_invalidate;

	ggtt->invalidate(ggtt);
पूर्ण

व्योम i915_ggtt_disable_guc(काष्ठा i915_ggtt *ggtt)
अणु
	/* XXX Temporary parकरोn क्रम error unload */
	अगर (ggtt->invalidate == gen8_ggtt_invalidate)
		वापस;

	/* We should only be called after i915_ggtt_enable_guc() */
	GEM_BUG_ON(ggtt->invalidate != guc_ggtt_invalidate);

	ggtt->invalidate = gen8_ggtt_invalidate;

	ggtt->invalidate(ggtt);
पूर्ण

व्योम i915_ggtt_resume(काष्ठा i915_ggtt *ggtt)
अणु
	काष्ठा i915_vma *vma;
	bool flush = false;
	पूर्णांक खोलो;

	पूर्णांकel_gt_check_and_clear_faults(ggtt->vm.gt);

	/* First fill our portion of the GTT with scratch pages */
	ggtt->vm.clear_range(&ggtt->vm, 0, ggtt->vm.total);

	/* Skip rewriting PTE on VMA unbind. */
	खोलो = atomic_xchg(&ggtt->vm.खोलो, 0);

	/* clflush objects bound पूर्णांकo the GGTT and rebind them. */
	list_क्रम_each_entry(vma, &ggtt->vm.bound_list, vm_link) अणु
		काष्ठा drm_i915_gem_object *obj = vma->obj;
		अचिन्हित पूर्णांक was_bound =
			atomic_पढ़ो(&vma->flags) & I915_VMA_BIND_MASK;

		GEM_BUG_ON(!was_bound);
		vma->ops->bind_vma(&ggtt->vm, शून्य, vma,
				   obj ? obj->cache_level : 0,
				   was_bound);
		अगर (obj) अणु /* only used during resume => exclusive access */
			flush |= fetch_and_zero(&obj->ग_लिखो_करोमुख्य);
			obj->पढ़ो_करोमुख्यs |= I915_GEM_DOMAIN_GTT;
		पूर्ण
	पूर्ण

	atomic_set(&ggtt->vm.खोलो, खोलो);
	ggtt->invalidate(ggtt);

	अगर (flush)
		wbinvd_on_all_cpus();

	अगर (INTEL_GEN(ggtt->vm.i915) >= 8)
		setup_निजी_pat(ggtt->vm.gt->uncore);

	पूर्णांकel_ggtt_restore_fences(ggtt);
पूर्ण

अटल काष्ठा scatterlist *
rotate_pages(काष्ठा drm_i915_gem_object *obj, अचिन्हित पूर्णांक offset,
	     अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
	     अचिन्हित पूर्णांक src_stride, अचिन्हित पूर्णांक dst_stride,
	     काष्ठा sg_table *st, काष्ठा scatterlist *sg)
अणु
	अचिन्हित पूर्णांक column, row;
	अचिन्हित पूर्णांक src_idx;

	क्रम (column = 0; column < width; column++) अणु
		अचिन्हित पूर्णांक left;

		src_idx = src_stride * (height - 1) + column + offset;
		क्रम (row = 0; row < height; row++) अणु
			st->nents++;
			/*
			 * We करोn't need the pages, but need to initialize
			 * the entries so the sg list can be happily traversed.
			 * The only thing we need are DMA addresses.
			 */
			sg_set_page(sg, शून्य, I915_GTT_PAGE_SIZE, 0);
			sg_dma_address(sg) =
				i915_gem_object_get_dma_address(obj, src_idx);
			sg_dma_len(sg) = I915_GTT_PAGE_SIZE;
			sg = sg_next(sg);
			src_idx -= src_stride;
		पूर्ण

		left = (dst_stride - height) * I915_GTT_PAGE_SIZE;

		अगर (!left)
			जारी;

		st->nents++;

		/*
		 * The DE ignores the PTEs क्रम the padding tiles, the sg entry
		 * here is just a conenience to indicate how many padding PTEs
		 * to insert at this spot.
		 */
		sg_set_page(sg, शून्य, left, 0);
		sg_dma_address(sg) = 0;
		sg_dma_len(sg) = left;
		sg = sg_next(sg);
	पूर्ण

	वापस sg;
पूर्ण

अटल noअंतरभूत काष्ठा sg_table *
पूर्णांकel_rotate_pages(काष्ठा पूर्णांकel_rotation_info *rot_info,
		   काष्ठा drm_i915_gem_object *obj)
अणु
	अचिन्हित पूर्णांक size = पूर्णांकel_rotation_info_size(rot_info);
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	काष्ठा sg_table *st;
	काष्ठा scatterlist *sg;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक i;

	/* Allocate target SG list. */
	st = kदो_स्मृति(माप(*st), GFP_KERNEL);
	अगर (!st)
		जाओ err_st_alloc;

	ret = sg_alloc_table(st, size, GFP_KERNEL);
	अगर (ret)
		जाओ err_sg_alloc;

	st->nents = 0;
	sg = st->sgl;

	क्रम (i = 0 ; i < ARRAY_SIZE(rot_info->plane); i++)
		sg = rotate_pages(obj, rot_info->plane[i].offset,
				  rot_info->plane[i].width, rot_info->plane[i].height,
				  rot_info->plane[i].src_stride,
				  rot_info->plane[i].dst_stride,
				  st, sg);

	वापस st;

err_sg_alloc:
	kमुक्त(st);
err_st_alloc:

	drm_dbg(&i915->drm, "Failed to create rotated mapping for object size %zu! (%ux%u tiles, %u pages)\n",
		obj->base.size, rot_info->plane[0].width,
		rot_info->plane[0].height, size);

	वापस ERR_PTR(ret);
पूर्ण

अटल काष्ठा scatterlist *
remap_pages(काष्ठा drm_i915_gem_object *obj, अचिन्हित पूर्णांक offset,
	    अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height,
	    अचिन्हित पूर्णांक src_stride, अचिन्हित पूर्णांक dst_stride,
	    काष्ठा sg_table *st, काष्ठा scatterlist *sg)
अणु
	अचिन्हित पूर्णांक row;

	क्रम (row = 0; row < height; row++) अणु
		अचिन्हित पूर्णांक left = width * I915_GTT_PAGE_SIZE;

		जबतक (left) अणु
			dma_addr_t addr;
			अचिन्हित पूर्णांक length;

			/*
			 * We करोn't need the pages, but need to initialize
			 * the entries so the sg list can be happily traversed.
			 * The only thing we need are DMA addresses.
			 */

			addr = i915_gem_object_get_dma_address_len(obj, offset, &length);

			length = min(left, length);

			st->nents++;

			sg_set_page(sg, शून्य, length, 0);
			sg_dma_address(sg) = addr;
			sg_dma_len(sg) = length;
			sg = sg_next(sg);

			offset += length / I915_GTT_PAGE_SIZE;
			left -= length;
		पूर्ण

		offset += src_stride - width;

		left = (dst_stride - width) * I915_GTT_PAGE_SIZE;

		अगर (!left)
			जारी;

		st->nents++;

		/*
		 * The DE ignores the PTEs क्रम the padding tiles, the sg entry
		 * here is just a conenience to indicate how many padding PTEs
		 * to insert at this spot.
		 */
		sg_set_page(sg, शून्य, left, 0);
		sg_dma_address(sg) = 0;
		sg_dma_len(sg) = left;
		sg = sg_next(sg);
	पूर्ण

	वापस sg;
पूर्ण

अटल noअंतरभूत काष्ठा sg_table *
पूर्णांकel_remap_pages(काष्ठा पूर्णांकel_remapped_info *rem_info,
		  काष्ठा drm_i915_gem_object *obj)
अणु
	अचिन्हित पूर्णांक size = पूर्णांकel_remapped_info_size(rem_info);
	काष्ठा drm_i915_निजी *i915 = to_i915(obj->base.dev);
	काष्ठा sg_table *st;
	काष्ठा scatterlist *sg;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक i;

	/* Allocate target SG list. */
	st = kदो_स्मृति(माप(*st), GFP_KERNEL);
	अगर (!st)
		जाओ err_st_alloc;

	ret = sg_alloc_table(st, size, GFP_KERNEL);
	अगर (ret)
		जाओ err_sg_alloc;

	st->nents = 0;
	sg = st->sgl;

	क्रम (i = 0 ; i < ARRAY_SIZE(rem_info->plane); i++) अणु
		sg = remap_pages(obj, rem_info->plane[i].offset,
				 rem_info->plane[i].width, rem_info->plane[i].height,
				 rem_info->plane[i].src_stride, rem_info->plane[i].dst_stride,
				 st, sg);
	पूर्ण

	i915_sg_trim(st);

	वापस st;

err_sg_alloc:
	kमुक्त(st);
err_st_alloc:

	drm_dbg(&i915->drm, "Failed to create remapped mapping for object size %zu! (%ux%u tiles, %u pages)\n",
		obj->base.size, rem_info->plane[0].width,
		rem_info->plane[0].height, size);

	वापस ERR_PTR(ret);
पूर्ण

अटल noअंतरभूत काष्ठा sg_table *
पूर्णांकel_partial_pages(स्थिर काष्ठा i915_ggtt_view *view,
		    काष्ठा drm_i915_gem_object *obj)
अणु
	काष्ठा sg_table *st;
	काष्ठा scatterlist *sg, *iter;
	अचिन्हित पूर्णांक count = view->partial.size;
	अचिन्हित पूर्णांक offset;
	पूर्णांक ret = -ENOMEM;

	st = kदो_स्मृति(माप(*st), GFP_KERNEL);
	अगर (!st)
		जाओ err_st_alloc;

	ret = sg_alloc_table(st, count, GFP_KERNEL);
	अगर (ret)
		जाओ err_sg_alloc;

	iter = i915_gem_object_get_sg_dma(obj, view->partial.offset, &offset, true);
	GEM_BUG_ON(!iter);

	sg = st->sgl;
	st->nents = 0;
	करो अणु
		अचिन्हित पूर्णांक len;

		len = min(sg_dma_len(iter) - (offset << PAGE_SHIFT),
			  count << PAGE_SHIFT);
		sg_set_page(sg, शून्य, len, 0);
		sg_dma_address(sg) =
			sg_dma_address(iter) + (offset << PAGE_SHIFT);
		sg_dma_len(sg) = len;

		st->nents++;
		count -= len >> PAGE_SHIFT;
		अगर (count == 0) अणु
			sg_mark_end(sg);
			i915_sg_trim(st); /* Drop any unused tail entries. */

			वापस st;
		पूर्ण

		sg = __sg_next(sg);
		iter = __sg_next(iter);
		offset = 0;
	पूर्ण जबतक (1);

err_sg_alloc:
	kमुक्त(st);
err_st_alloc:
	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक
i915_get_ggtt_vma_pages(काष्ठा i915_vma *vma)
अणु
	पूर्णांक ret;

	/*
	 * The vma->pages are only valid within the lअगरespan of the borrowed
	 * obj->mm.pages. When the obj->mm.pages sg_table is regenerated, so
	 * must be the vma->pages. A simple rule is that vma->pages must only
	 * be accessed when the obj->mm.pages are pinned.
	 */
	GEM_BUG_ON(!i915_gem_object_has_pinned_pages(vma->obj));

	चयन (vma->ggtt_view.type) अणु
	शेष:
		GEM_BUG_ON(vma->ggtt_view.type);
		fallthrough;
	हाल I915_GGTT_VIEW_NORMAL:
		vma->pages = vma->obj->mm.pages;
		वापस 0;

	हाल I915_GGTT_VIEW_ROTATED:
		vma->pages =
			पूर्णांकel_rotate_pages(&vma->ggtt_view.rotated, vma->obj);
		अवरोध;

	हाल I915_GGTT_VIEW_REMAPPED:
		vma->pages =
			पूर्णांकel_remap_pages(&vma->ggtt_view.remapped, vma->obj);
		अवरोध;

	हाल I915_GGTT_VIEW_PARTIAL:
		vma->pages = पूर्णांकel_partial_pages(&vma->ggtt_view, vma->obj);
		अवरोध;
	पूर्ण

	ret = 0;
	अगर (IS_ERR(vma->pages)) अणु
		ret = PTR_ERR(vma->pages);
		vma->pages = शून्य;
		drm_err(&vma->vm->i915->drm,
			"Failed to get pages for VMA view type %u (%d)!\n",
			vma->ggtt_view.type, ret);
	पूर्ण
	वापस ret;
पूर्ण
