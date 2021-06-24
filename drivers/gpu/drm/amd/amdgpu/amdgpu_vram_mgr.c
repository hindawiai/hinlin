<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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
 * Authors: Christian Kथघnig
 */

#समावेश <linux/dma-mapping.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_vm.h"
#समावेश "amdgpu_res_cursor.h"
#समावेश "amdgpu_atomfirmware.h"
#समावेश "atom.h"

अटल अंतरभूत काष्ठा amdgpu_vram_mgr *to_vram_mgr(काष्ठा tपंचांग_resource_manager *man)
अणु
	वापस container_of(man, काष्ठा amdgpu_vram_mgr, manager);
पूर्ण

अटल अंतरभूत काष्ठा amdgpu_device *to_amdgpu_device(काष्ठा amdgpu_vram_mgr *mgr)
अणु
	वापस container_of(mgr, काष्ठा amdgpu_device, mman.vram_mgr);
पूर्ण

/**
 * DOC: mem_info_vram_total
 *
 * The amdgpu driver provides a sysfs API क्रम reporting current total VRAM
 * available on the device
 * The file mem_info_vram_total is used क्रम this and वापसs the total
 * amount of VRAM in bytes
 */
अटल sमाप_प्रकार amdgpu_mem_info_vram_total_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);

	वापस sysfs_emit(buf, "%llu\n", adev->gmc.real_vram_size);
पूर्ण

/**
 * DOC: mem_info_vis_vram_total
 *
 * The amdgpu driver provides a sysfs API क्रम reporting current total
 * visible VRAM available on the device
 * The file mem_info_vis_vram_total is used क्रम this and वापसs the total
 * amount of visible VRAM in bytes
 */
अटल sमाप_प्रकार amdgpu_mem_info_vis_vram_total_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);

	वापस sysfs_emit(buf, "%llu\n", adev->gmc.visible_vram_size);
पूर्ण

/**
 * DOC: mem_info_vram_used
 *
 * The amdgpu driver provides a sysfs API क्रम reporting current total VRAM
 * available on the device
 * The file mem_info_vram_used is used क्रम this and वापसs the total
 * amount of currently used VRAM in bytes
 */
अटल sमाप_प्रकार amdgpu_mem_info_vram_used_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(&adev->mman.bdev, TTM_PL_VRAM);

	वापस sysfs_emit(buf, "%llu\n", amdgpu_vram_mgr_usage(man));
पूर्ण

/**
 * DOC: mem_info_vis_vram_used
 *
 * The amdgpu driver provides a sysfs API क्रम reporting current total of
 * used visible VRAM
 * The file mem_info_vis_vram_used is used क्रम this and वापसs the total
 * amount of currently used visible VRAM in bytes
 */
अटल sमाप_प्रकार amdgpu_mem_info_vis_vram_used_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(&adev->mman.bdev, TTM_PL_VRAM);

	वापस sysfs_emit(buf, "%llu\n", amdgpu_vram_mgr_vis_usage(man));
पूर्ण

अटल sमाप_प्रकार amdgpu_mem_info_vram_venकरोr(काष्ठा device *dev,
						 काष्ठा device_attribute *attr,
						 अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);

	चयन (adev->gmc.vram_venकरोr) अणु
	हाल SAMSUNG:
		वापस sysfs_emit(buf, "samsung\n");
	हाल INFINEON:
		वापस sysfs_emit(buf, "infineon\n");
	हाल ELPIDA:
		वापस sysfs_emit(buf, "elpida\n");
	हाल ETRON:
		वापस sysfs_emit(buf, "etron\n");
	हाल न_अंकYA:
		वापस sysfs_emit(buf, "nanya\n");
	हाल HYNIX:
		वापस sysfs_emit(buf, "hynix\n");
	हाल MOSEL:
		वापस sysfs_emit(buf, "mosel\n");
	हाल WINBOND:
		वापस sysfs_emit(buf, "winbond\n");
	हाल ESMT:
		वापस sysfs_emit(buf, "esmt\n");
	हाल MICRON:
		वापस sysfs_emit(buf, "micron\n");
	शेष:
		वापस sysfs_emit(buf, "unknown\n");
	पूर्ण
पूर्ण

अटल DEVICE_ATTR(mem_info_vram_total, S_IRUGO,
		   amdgpu_mem_info_vram_total_show, शून्य);
अटल DEVICE_ATTR(mem_info_vis_vram_total, S_IRUGO,
		   amdgpu_mem_info_vis_vram_total_show,शून्य);
अटल DEVICE_ATTR(mem_info_vram_used, S_IRUGO,
		   amdgpu_mem_info_vram_used_show, शून्य);
अटल DEVICE_ATTR(mem_info_vis_vram_used, S_IRUGO,
		   amdgpu_mem_info_vis_vram_used_show, शून्य);
अटल DEVICE_ATTR(mem_info_vram_venकरोr, S_IRUGO,
		   amdgpu_mem_info_vram_venकरोr, शून्य);

अटल स्थिर काष्ठा attribute *amdgpu_vram_mgr_attributes[] = अणु
	&dev_attr_mem_info_vram_total.attr,
	&dev_attr_mem_info_vis_vram_total.attr,
	&dev_attr_mem_info_vram_used.attr,
	&dev_attr_mem_info_vis_vram_used.attr,
	&dev_attr_mem_info_vram_venकरोr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा tपंचांग_resource_manager_func amdgpu_vram_mgr_func;

/**
 * amdgpu_vram_mgr_init - init VRAM manager and DRM MM
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Allocate and initialize the VRAM manager.
 */
पूर्णांक amdgpu_vram_mgr_init(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_vram_mgr *mgr = &adev->mman.vram_mgr;
	काष्ठा tपंचांग_resource_manager *man = &mgr->manager;
	पूर्णांक ret;

	tपंचांग_resource_manager_init(man, adev->gmc.real_vram_size >> PAGE_SHIFT);

	man->func = &amdgpu_vram_mgr_func;

	drm_mm_init(&mgr->mm, 0, man->size);
	spin_lock_init(&mgr->lock);
	INIT_LIST_HEAD(&mgr->reservations_pending);
	INIT_LIST_HEAD(&mgr->reserved_pages);

	/* Add the two VRAM-related sysfs files */
	ret = sysfs_create_files(&adev->dev->kobj, amdgpu_vram_mgr_attributes);
	अगर (ret)
		DRM_ERROR("Failed to register sysfs\n");

	tपंचांग_set_driver_manager(&adev->mman.bdev, TTM_PL_VRAM, &mgr->manager);
	tपंचांग_resource_manager_set_used(man, true);
	वापस 0;
पूर्ण

/**
 * amdgpu_vram_mgr_fini - मुक्त and destroy VRAM manager
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Destroy and मुक्त the VRAM manager, वापसs -EBUSY अगर ranges are still
 * allocated inside it.
 */
व्योम amdgpu_vram_mgr_fini(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_vram_mgr *mgr = &adev->mman.vram_mgr;
	काष्ठा tपंचांग_resource_manager *man = &mgr->manager;
	पूर्णांक ret;
	काष्ठा amdgpu_vram_reservation *rsv, *temp;

	tपंचांग_resource_manager_set_used(man, false);

	ret = tपंचांग_resource_manager_evict_all(&adev->mman.bdev, man);
	अगर (ret)
		वापस;

	spin_lock(&mgr->lock);
	list_क्रम_each_entry_safe(rsv, temp, &mgr->reservations_pending, node)
		kमुक्त(rsv);

	list_क्रम_each_entry_safe(rsv, temp, &mgr->reserved_pages, node) अणु
		drm_mm_हटाओ_node(&rsv->mm_node);
		kमुक्त(rsv);
	पूर्ण
	drm_mm_takeकरोwn(&mgr->mm);
	spin_unlock(&mgr->lock);

	sysfs_हटाओ_files(&adev->dev->kobj, amdgpu_vram_mgr_attributes);

	tपंचांग_resource_manager_cleanup(man);
	tपंचांग_set_driver_manager(&adev->mman.bdev, TTM_PL_VRAM, शून्य);
पूर्ण

/**
 * amdgpu_vram_mgr_vis_size - Calculate visible node size
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @node: MM node काष्ठाure
 *
 * Calculate how many bytes of the MM node are inside visible VRAM
 */
अटल u64 amdgpu_vram_mgr_vis_size(काष्ठा amdgpu_device *adev,
				    काष्ठा drm_mm_node *node)
अणु
	uपूर्णांक64_t start = node->start << PAGE_SHIFT;
	uपूर्णांक64_t end = (node->size + node->start) << PAGE_SHIFT;

	अगर (start >= adev->gmc.visible_vram_size)
		वापस 0;

	वापस (end > adev->gmc.visible_vram_size ?
		adev->gmc.visible_vram_size : end) - start;
पूर्ण

/**
 * amdgpu_vram_mgr_bo_visible_size - CPU visible BO size
 *
 * @bo: &amdgpu_bo buffer object (must be in VRAM)
 *
 * Returns:
 * How much of the given &amdgpu_bo buffer object lies in CPU visible VRAM.
 */
u64 amdgpu_vram_mgr_bo_visible_size(काष्ठा amdgpu_bo *bo)
अणु
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);
	काष्ठा tपंचांग_resource *mem = &bo->tbo.mem;
	काष्ठा drm_mm_node *nodes = mem->mm_node;
	अचिन्हित pages = mem->num_pages;
	u64 usage;

	अगर (amdgpu_gmc_vram_full_visible(&adev->gmc))
		वापस amdgpu_bo_size(bo);

	अगर (mem->start >= adev->gmc.visible_vram_size >> PAGE_SHIFT)
		वापस 0;

	क्रम (usage = 0; nodes && pages; pages -= nodes->size, nodes++)
		usage += amdgpu_vram_mgr_vis_size(adev, nodes);

	वापस usage;
पूर्ण

अटल व्योम amdgpu_vram_mgr_करो_reserve(काष्ठा tपंचांग_resource_manager *man)
अणु
	काष्ठा amdgpu_vram_mgr *mgr = to_vram_mgr(man);
	काष्ठा amdgpu_device *adev = to_amdgpu_device(mgr);
	काष्ठा drm_mm *mm = &mgr->mm;
	काष्ठा amdgpu_vram_reservation *rsv, *temp;
	uपूर्णांक64_t vis_usage;

	list_क्रम_each_entry_safe(rsv, temp, &mgr->reservations_pending, node) अणु
		अगर (drm_mm_reserve_node(mm, &rsv->mm_node))
			जारी;

		dev_dbg(adev->dev, "Reservation 0x%llx - %lld, Succeeded\n",
			rsv->mm_node.start, rsv->mm_node.size);

		vis_usage = amdgpu_vram_mgr_vis_size(adev, &rsv->mm_node);
		atomic64_add(vis_usage, &mgr->vis_usage);
		atomic64_add(rsv->mm_node.size << PAGE_SHIFT, &mgr->usage);
		list_move(&rsv->node, &mgr->reserved_pages);
	पूर्ण
पूर्ण

/**
 * amdgpu_vram_mgr_reserve_range - Reserve a range from VRAM
 *
 * @man: TTM memory type manager
 * @start: start address of the range in VRAM
 * @size: size of the range
 *
 * Reserve memory from start addess with the specअगरied size in VRAM
 */
पूर्णांक amdgpu_vram_mgr_reserve_range(काष्ठा tपंचांग_resource_manager *man,
				  uपूर्णांक64_t start, uपूर्णांक64_t size)
अणु
	काष्ठा amdgpu_vram_mgr *mgr = to_vram_mgr(man);
	काष्ठा amdgpu_vram_reservation *rsv;

	rsv = kzalloc(माप(*rsv), GFP_KERNEL);
	अगर (!rsv)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&rsv->node);
	rsv->mm_node.start = start >> PAGE_SHIFT;
	rsv->mm_node.size = size >> PAGE_SHIFT;

	spin_lock(&mgr->lock);
	list_add_tail(&mgr->reservations_pending, &rsv->node);
	amdgpu_vram_mgr_करो_reserve(man);
	spin_unlock(&mgr->lock);

	वापस 0;
पूर्ण

/**
 * amdgpu_vram_mgr_query_page_status - query the reservation status
 *
 * @man: TTM memory type manager
 * @start: start address of a page in VRAM
 *
 * Returns:
 *	-EBUSY: the page is still hold and in pending list
 *	0: the page has been reserved
 *	-ENOENT: the input page is not a reservation
 */
पूर्णांक amdgpu_vram_mgr_query_page_status(काष्ठा tपंचांग_resource_manager *man,
				      uपूर्णांक64_t start)
अणु
	काष्ठा amdgpu_vram_mgr *mgr = to_vram_mgr(man);
	काष्ठा amdgpu_vram_reservation *rsv;
	पूर्णांक ret;

	spin_lock(&mgr->lock);

	list_क्रम_each_entry(rsv, &mgr->reservations_pending, node) अणु
		अगर ((rsv->mm_node.start <= start) &&
		    (start < (rsv->mm_node.start + rsv->mm_node.size))) अणु
			ret = -EBUSY;
			जाओ out;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(rsv, &mgr->reserved_pages, node) अणु
		अगर ((rsv->mm_node.start <= start) &&
		    (start < (rsv->mm_node.start + rsv->mm_node.size))) अणु
			ret = 0;
			जाओ out;
		पूर्ण
	पूर्ण

	ret = -ENOENT;
out:
	spin_unlock(&mgr->lock);
	वापस ret;
पूर्ण

/**
 * amdgpu_vram_mgr_virt_start - update भव start address
 *
 * @mem: tपंचांग_resource to update
 * @node: just allocated node
 *
 * Calculate a भव BO start address to easily check अगर everything is CPU
 * accessible.
 */
अटल व्योम amdgpu_vram_mgr_virt_start(काष्ठा tपंचांग_resource *mem,
				       काष्ठा drm_mm_node *node)
अणु
	अचिन्हित दीर्घ start;

	start = node->start + node->size;
	अगर (start > mem->num_pages)
		start -= mem->num_pages;
	अन्यथा
		start = 0;
	mem->start = max(mem->start, start);
पूर्ण

/**
 * amdgpu_vram_mgr_new - allocate new ranges
 *
 * @man: TTM memory type manager
 * @tbo: TTM BO we need this range क्रम
 * @place: placement flags and restrictions
 * @mem: the resulting mem object
 *
 * Allocate VRAM क्रम the given BO.
 */
अटल पूर्णांक amdgpu_vram_mgr_new(काष्ठा tपंचांग_resource_manager *man,
			       काष्ठा tपंचांग_buffer_object *tbo,
			       स्थिर काष्ठा tपंचांग_place *place,
			       काष्ठा tपंचांग_resource *mem)
अणु
	काष्ठा amdgpu_vram_mgr *mgr = to_vram_mgr(man);
	काष्ठा amdgpu_device *adev = to_amdgpu_device(mgr);
	काष्ठा drm_mm *mm = &mgr->mm;
	काष्ठा drm_mm_node *nodes;
	क्रमागत drm_mm_insert_mode mode;
	अचिन्हित दीर्घ lpfn, num_nodes, pages_per_node, pages_left;
	uपूर्णांक64_t vis_usage = 0, mem_bytes, max_bytes;
	अचिन्हित i;
	पूर्णांक r;

	lpfn = place->lpfn;
	अगर (!lpfn)
		lpfn = man->size;

	max_bytes = adev->gmc.mc_vram_size;
	अगर (tbo->type != tपंचांग_bo_type_kernel)
		max_bytes -= AMDGPU_VM_RESERVED_VRAM;

	/* bail out quickly अगर there's likely not enough VRAM क्रम this BO */
	mem_bytes = (u64)mem->num_pages << PAGE_SHIFT;
	अगर (atomic64_add_वापस(mem_bytes, &mgr->usage) > max_bytes) अणु
		atomic64_sub(mem_bytes, &mgr->usage);
		वापस -ENOSPC;
	पूर्ण

	अगर (place->flags & TTM_PL_FLAG_CONTIGUOUS) अणु
		pages_per_node = ~0ul;
		num_nodes = 1;
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
		pages_per_node = HPAGE_PMD_NR;
#अन्यथा
		/* शेष to 2MB */
		pages_per_node = (2UL << (20UL - PAGE_SHIFT));
#पूर्ण_अगर
		pages_per_node = max((uपूर्णांक32_t)pages_per_node, mem->page_alignment);
		num_nodes = DIV_ROUND_UP(mem->num_pages, pages_per_node);
	पूर्ण

	nodes = kvदो_स्मृति_array((uपूर्णांक32_t)num_nodes, माप(*nodes),
			       GFP_KERNEL | __GFP_ZERO);
	अगर (!nodes) अणु
		atomic64_sub(mem_bytes, &mgr->usage);
		वापस -ENOMEM;
	पूर्ण

	mode = DRM_MM_INSERT_BEST;
	अगर (place->flags & TTM_PL_FLAG_TOPDOWN)
		mode = DRM_MM_INSERT_HIGH;

	mem->start = 0;
	pages_left = mem->num_pages;

	spin_lock(&mgr->lock);
	क्रम (i = 0; pages_left >= pages_per_node; ++i) अणु
		अचिन्हित दीर्घ pages = roundकरोwn_घात_of_two(pages_left);

		/* Limit maximum size to 2GB due to SG table limitations */
		pages = min(pages, (2UL << (30 - PAGE_SHIFT)));

		r = drm_mm_insert_node_in_range(mm, &nodes[i], pages,
						pages_per_node, 0,
						place->fpfn, lpfn,
						mode);
		अगर (unlikely(r))
			अवरोध;

		vis_usage += amdgpu_vram_mgr_vis_size(adev, &nodes[i]);
		amdgpu_vram_mgr_virt_start(mem, &nodes[i]);
		pages_left -= pages;
	पूर्ण

	क्रम (; pages_left; ++i) अणु
		अचिन्हित दीर्घ pages = min(pages_left, pages_per_node);
		uपूर्णांक32_t alignment = mem->page_alignment;

		अगर (pages == pages_per_node)
			alignment = pages_per_node;

		r = drm_mm_insert_node_in_range(mm, &nodes[i],
						pages, alignment, 0,
						place->fpfn, lpfn,
						mode);
		अगर (unlikely(r))
			जाओ error;

		vis_usage += amdgpu_vram_mgr_vis_size(adev, &nodes[i]);
		amdgpu_vram_mgr_virt_start(mem, &nodes[i]);
		pages_left -= pages;
	पूर्ण
	spin_unlock(&mgr->lock);

	atomic64_add(vis_usage, &mgr->vis_usage);

	mem->mm_node = nodes;

	वापस 0;

error:
	जबतक (i--)
		drm_mm_हटाओ_node(&nodes[i]);
	spin_unlock(&mgr->lock);
	atomic64_sub(mem->num_pages << PAGE_SHIFT, &mgr->usage);

	kvमुक्त(nodes);
	वापस r;
पूर्ण

/**
 * amdgpu_vram_mgr_del - मुक्त ranges
 *
 * @man: TTM memory type manager
 * @mem: TTM memory object
 *
 * Free the allocated VRAM again.
 */
अटल व्योम amdgpu_vram_mgr_del(काष्ठा tपंचांग_resource_manager *man,
				काष्ठा tपंचांग_resource *mem)
अणु
	काष्ठा amdgpu_vram_mgr *mgr = to_vram_mgr(man);
	काष्ठा amdgpu_device *adev = to_amdgpu_device(mgr);
	काष्ठा drm_mm_node *nodes = mem->mm_node;
	uपूर्णांक64_t usage = 0, vis_usage = 0;
	अचिन्हित pages = mem->num_pages;

	अगर (!mem->mm_node)
		वापस;

	spin_lock(&mgr->lock);
	जबतक (pages) अणु
		pages -= nodes->size;
		drm_mm_हटाओ_node(nodes);
		usage += nodes->size << PAGE_SHIFT;
		vis_usage += amdgpu_vram_mgr_vis_size(adev, nodes);
		++nodes;
	पूर्ण
	amdgpu_vram_mgr_करो_reserve(man);
	spin_unlock(&mgr->lock);

	atomic64_sub(usage, &mgr->usage);
	atomic64_sub(vis_usage, &mgr->vis_usage);

	kvमुक्त(mem->mm_node);
	mem->mm_node = शून्य;
पूर्ण

/**
 * amdgpu_vram_mgr_alloc_sgt - allocate and fill a sg table
 *
 * @adev: amdgpu device poपूर्णांकer
 * @mem: TTM memory object
 * @offset: byte offset from the base of VRAM BO
 * @length: number of bytes to export in sg_table
 * @dev: the other device
 * @dir: dma direction
 * @sgt: resulting sg table
 *
 * Allocate and fill a sg table from a VRAM allocation.
 */
पूर्णांक amdgpu_vram_mgr_alloc_sgt(काष्ठा amdgpu_device *adev,
			      काष्ठा tपंचांग_resource *mem,
			      u64 offset, u64 length,
			      काष्ठा device *dev,
			      क्रमागत dma_data_direction dir,
			      काष्ठा sg_table **sgt)
अणु
	काष्ठा amdgpu_res_cursor cursor;
	काष्ठा scatterlist *sg;
	पूर्णांक num_entries = 0;
	पूर्णांक i, r;

	*sgt = kदो_स्मृति(माप(**sgt), GFP_KERNEL);
	अगर (!*sgt)
		वापस -ENOMEM;

	/* Determine the number of DRM_MM nodes to export */
	amdgpu_res_first(mem, offset, length, &cursor);
	जबतक (cursor.reमुख्यing) अणु
		num_entries++;
		amdgpu_res_next(&cursor, cursor.size);
	पूर्ण

	r = sg_alloc_table(*sgt, num_entries, GFP_KERNEL);
	अगर (r)
		जाओ error_मुक्त;

	/* Initialize scatterlist nodes of sg_table */
	क्रम_each_sgtable_sg((*sgt), sg, i)
		sg->length = 0;

	/*
	 * Walk करोwn DRM_MM nodes to populate scatterlist nodes
	 * @note: Use iterator api to get first the DRM_MM node
	 * and the number of bytes from it. Access the following
	 * DRM_MM node(s) अगर more buffer needs to exported
	 */
	amdgpu_res_first(mem, offset, length, &cursor);
	क्रम_each_sgtable_sg((*sgt), sg, i) अणु
		phys_addr_t phys = cursor.start + adev->gmc.aper_base;
		माप_प्रकार size = cursor.size;
		dma_addr_t addr;

		addr = dma_map_resource(dev, phys, size, dir,
					DMA_ATTR_SKIP_CPU_SYNC);
		r = dma_mapping_error(dev, addr);
		अगर (r)
			जाओ error_unmap;

		sg_set_page(sg, शून्य, size, 0);
		sg_dma_address(sg) = addr;
		sg_dma_len(sg) = size;

		amdgpu_res_next(&cursor, cursor.size);
	पूर्ण

	वापस 0;

error_unmap:
	क्रम_each_sgtable_sg((*sgt), sg, i) अणु
		अगर (!sg->length)
			जारी;

		dma_unmap_resource(dev, sg->dma_address,
				   sg->length, dir,
				   DMA_ATTR_SKIP_CPU_SYNC);
	पूर्ण
	sg_मुक्त_table(*sgt);

error_मुक्त:
	kमुक्त(*sgt);
	वापस r;
पूर्ण

/**
 * amdgpu_vram_mgr_मुक्त_sgt - allocate and fill a sg table
 *
 * @dev: device poपूर्णांकer
 * @dir: data direction of resource to unmap
 * @sgt: sg table to मुक्त
 *
 * Free a previously allocate sg table.
 */
व्योम amdgpu_vram_mgr_मुक्त_sgt(काष्ठा device *dev,
			      क्रमागत dma_data_direction dir,
			      काष्ठा sg_table *sgt)
अणु
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	क्रम_each_sgtable_sg(sgt, sg, i)
		dma_unmap_resource(dev, sg->dma_address,
				   sg->length, dir,
				   DMA_ATTR_SKIP_CPU_SYNC);
	sg_मुक्त_table(sgt);
	kमुक्त(sgt);
पूर्ण

/**
 * amdgpu_vram_mgr_usage - how many bytes are used in this करोमुख्य
 *
 * @man: TTM memory type manager
 *
 * Returns how many bytes are used in this करोमुख्य.
 */
uपूर्णांक64_t amdgpu_vram_mgr_usage(काष्ठा tपंचांग_resource_manager *man)
अणु
	काष्ठा amdgpu_vram_mgr *mgr = to_vram_mgr(man);

	वापस atomic64_पढ़ो(&mgr->usage);
पूर्ण

/**
 * amdgpu_vram_mgr_vis_usage - how many bytes are used in the visible part
 *
 * @man: TTM memory type manager
 *
 * Returns how many bytes are used in the visible part of VRAM
 */
uपूर्णांक64_t amdgpu_vram_mgr_vis_usage(काष्ठा tपंचांग_resource_manager *man)
अणु
	काष्ठा amdgpu_vram_mgr *mgr = to_vram_mgr(man);

	वापस atomic64_पढ़ो(&mgr->vis_usage);
पूर्ण

/**
 * amdgpu_vram_mgr_debug - dump VRAM table
 *
 * @man: TTM memory type manager
 * @prपूर्णांकer: DRM prपूर्णांकer to use
 *
 * Dump the table content using prपूर्णांकk.
 */
अटल व्योम amdgpu_vram_mgr_debug(काष्ठा tपंचांग_resource_manager *man,
				  काष्ठा drm_prपूर्णांकer *prपूर्णांकer)
अणु
	काष्ठा amdgpu_vram_mgr *mgr = to_vram_mgr(man);

	spin_lock(&mgr->lock);
	drm_mm_prपूर्णांक(&mgr->mm, prपूर्णांकer);
	spin_unlock(&mgr->lock);

	drm_म_लिखो(prपूर्णांकer, "man size:%llu pages, ram usage:%lluMB, vis usage:%lluMB\n",
		   man->size, amdgpu_vram_mgr_usage(man) >> 20,
		   amdgpu_vram_mgr_vis_usage(man) >> 20);
पूर्ण

अटल स्थिर काष्ठा tपंचांग_resource_manager_func amdgpu_vram_mgr_func = अणु
	.alloc	= amdgpu_vram_mgr_new,
	.मुक्त	= amdgpu_vram_mgr_del,
	.debug	= amdgpu_vram_mgr_debug
पूर्ण;
