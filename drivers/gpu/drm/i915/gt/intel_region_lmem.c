<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 */

#समावेश "i915_drv.h"
#समावेश "intel_memory_region.h"
#समावेश "gem/i915_gem_lmem.h"
#समावेश "gem/i915_gem_region.h"
#समावेश "intel_region_lmem.h"

अटल पूर्णांक init_fake_lmem_bar(काष्ठा पूर्णांकel_memory_region *mem)
अणु
	काष्ठा drm_i915_निजी *i915 = mem->i915;
	काष्ठा i915_ggtt *ggtt = &i915->ggtt;
	अचिन्हित दीर्घ n;
	पूर्णांक ret;

	/* We want to 1:1 map the mappable aperture to our reserved region */

	mem->fake_mappable.start = 0;
	mem->fake_mappable.size = resource_size(&mem->region);
	mem->fake_mappable.color = I915_COLOR_UNEVICTABLE;

	ret = drm_mm_reserve_node(&ggtt->vm.mm, &mem->fake_mappable);
	अगर (ret)
		वापस ret;

	mem->remap_addr = dma_map_resource(i915->drm.dev,
					   mem->region.start,
					   mem->fake_mappable.size,
					   PCI_DMA_BIसूचीECTIONAL,
					   DMA_ATTR_FORCE_CONTIGUOUS);
	अगर (dma_mapping_error(i915->drm.dev, mem->remap_addr)) अणु
		drm_mm_हटाओ_node(&mem->fake_mappable);
		वापस -EINVAL;
	पूर्ण

	क्रम (n = 0; n < mem->fake_mappable.size >> PAGE_SHIFT; ++n) अणु
		ggtt->vm.insert_page(&ggtt->vm,
				     mem->remap_addr + (n << PAGE_SHIFT),
				     n << PAGE_SHIFT,
				     I915_CACHE_NONE, 0);
	पूर्ण

	mem->region = (काष्ठा resource)DEFINE_RES_MEM(mem->remap_addr,
						      mem->fake_mappable.size);

	वापस 0;
पूर्ण

अटल व्योम release_fake_lmem_bar(काष्ठा पूर्णांकel_memory_region *mem)
अणु
	अगर (!drm_mm_node_allocated(&mem->fake_mappable))
		वापस;

	drm_mm_हटाओ_node(&mem->fake_mappable);

	dma_unmap_resource(mem->i915->drm.dev,
			   mem->remap_addr,
			   mem->fake_mappable.size,
			   PCI_DMA_BIसूचीECTIONAL,
			   DMA_ATTR_FORCE_CONTIGUOUS);
पूर्ण

अटल व्योम
region_lmem_release(काष्ठा पूर्णांकel_memory_region *mem)
अणु
	release_fake_lmem_bar(mem);
	io_mapping_fini(&mem->iomap);
	पूर्णांकel_memory_region_release_buddy(mem);
पूर्ण

अटल पूर्णांक
region_lmem_init(काष्ठा पूर्णांकel_memory_region *mem)
अणु
	पूर्णांक ret;

	अगर (mem->i915->params.fake_lmem_start) अणु
		ret = init_fake_lmem_bar(mem);
		GEM_BUG_ON(ret);
	पूर्ण

	अगर (!io_mapping_init_wc(&mem->iomap,
				mem->io_start,
				resource_size(&mem->region)))
		वापस -EIO;

	ret = पूर्णांकel_memory_region_init_buddy(mem);
	अगर (ret)
		io_mapping_fini(&mem->iomap);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा पूर्णांकel_memory_region_ops पूर्णांकel_region_lmem_ops = अणु
	.init = region_lmem_init,
	.release = region_lmem_release,
	.init_object = __i915_gem_lmem_object_init,
पूर्ण;

काष्ठा पूर्णांकel_memory_region *
पूर्णांकel_gt_setup_fake_lmem(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा pci_dev *pdev = to_pci_dev(i915->drm.dev);
	काष्ठा पूर्णांकel_memory_region *mem;
	resource_माप_प्रकार mappable_end;
	resource_माप_प्रकार io_start;
	resource_माप_प्रकार start;

	अगर (!HAS_LMEM(i915))
		वापस ERR_PTR(-ENODEV);

	अगर (!i915->params.fake_lmem_start)
		वापस ERR_PTR(-ENODEV);

	GEM_BUG_ON(i915_ggtt_has_aperture(&i915->ggtt));

	/* Your mappable aperture beदीर्घs to me now! */
	mappable_end = pci_resource_len(pdev, 2);
	io_start = pci_resource_start(pdev, 2);
	start = i915->params.fake_lmem_start;

	mem = पूर्णांकel_memory_region_create(i915,
					 start,
					 mappable_end,
					 PAGE_SIZE,
					 io_start,
					 &पूर्णांकel_region_lmem_ops);
	अगर (!IS_ERR(mem)) अणु
		drm_info(&i915->drm, "Intel graphics fake LMEM: %pR\n",
			 &mem->region);
		drm_info(&i915->drm,
			 "Intel graphics fake LMEM IO start: %llx\n",
			(u64)mem->io_start);
		drm_info(&i915->drm, "Intel graphics fake LMEM size: %llx\n",
			 (u64)resource_size(&mem->region));
	पूर्ण

	वापस mem;
पूर्ण

अटल bool get_legacy_lowmem_region(काष्ठा पूर्णांकel_uncore *uncore,
				     u64 *start, u32 *size)
अणु
	अगर (!IS_DG1_REVID(uncore->i915, DG1_REVID_A0, DG1_REVID_B0))
		वापस false;

	*start = 0;
	*size = SZ_1M;

	drm_dbg(&uncore->i915->drm, "LMEM: reserved legacy low-memory [0x%llx-0x%llx]\n",
		*start, *start + *size);

	वापस true;
पूर्ण

अटल पूर्णांक reserve_lowmem_region(काष्ठा पूर्णांकel_uncore *uncore,
				 काष्ठा पूर्णांकel_memory_region *mem)
अणु
	u64 reserve_start;
	u32 reserve_size;
	पूर्णांक ret;

	अगर (!get_legacy_lowmem_region(uncore, &reserve_start, &reserve_size))
		वापस 0;

	ret = पूर्णांकel_memory_region_reserve(mem, reserve_start, reserve_size);
	अगर (ret)
		drm_err(&uncore->i915->drm, "LMEM: reserving low memory region failed\n");

	वापस ret;
पूर्ण

अटल काष्ठा पूर्णांकel_memory_region *setup_lmem(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_निजी *i915 = gt->i915;
	काष्ठा पूर्णांकel_uncore *uncore = gt->uncore;
	काष्ठा pci_dev *pdev = i915->drm.pdev;
	काष्ठा पूर्णांकel_memory_region *mem;
	resource_माप_प्रकार io_start;
	resource_माप_प्रकार lmem_size;
	पूर्णांक err;

	अगर (!IS_DGFX(i915))
		वापस ERR_PTR(-ENODEV);

	/* Stolen starts from GSMBASE on DG1 */
	lmem_size = पूर्णांकel_uncore_पढ़ो64(uncore, GEN12_GSMBASE);

	io_start = pci_resource_start(pdev, 2);
	अगर (GEM_WARN_ON(lmem_size > pci_resource_len(pdev, 2)))
		वापस ERR_PTR(-ENODEV);

	mem = पूर्णांकel_memory_region_create(i915,
					 0,
					 lmem_size,
					 I915_GTT_PAGE_SIZE_4K,
					 io_start,
					 &पूर्णांकel_region_lmem_ops);
	अगर (IS_ERR(mem))
		वापस mem;

	err = reserve_lowmem_region(uncore, mem);
	अगर (err)
		जाओ err_region_put;

	drm_dbg(&i915->drm, "Local memory: %pR\n", &mem->region);
	drm_dbg(&i915->drm, "Local memory IO start: %pa\n",
		&mem->io_start);
	drm_info(&i915->drm, "Local memory available: %pa\n",
		 &lmem_size);

	वापस mem;

err_region_put:
	पूर्णांकel_memory_region_put(mem);
	वापस ERR_PTR(err);
पूर्ण

काष्ठा पूर्णांकel_memory_region *पूर्णांकel_gt_setup_lmem(काष्ठा पूर्णांकel_gt *gt)
अणु
	वापस setup_lmem(gt);
पूर्ण
