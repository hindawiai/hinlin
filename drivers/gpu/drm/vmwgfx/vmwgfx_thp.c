<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/*
 * Huge page-table-entry support क्रम IO memory.
 *
 * Copyright (C) 2007-2019 Vmware, Inc. All rights reservedd.
 */
#समावेश "vmwgfx_drv.h"
#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>
#समावेश <drm/tपंचांग/tपंचांग_placement.h>

/**
 * काष्ठा vmw_thp_manager - Range manager implementing huge page alignment
 *
 * @manager: TTM resource manager.
 * @mm: The underlying range manager. Protected by @lock.
 * @lock: Manager lock.
 */
काष्ठा vmw_thp_manager अणु
	काष्ठा tपंचांग_resource_manager manager;
	काष्ठा drm_mm mm;
	spinlock_t lock;
पूर्ण;

अटल काष्ठा vmw_thp_manager *to_thp_manager(काष्ठा tपंचांग_resource_manager *man)
अणु
	वापस container_of(man, काष्ठा vmw_thp_manager, manager);
पूर्ण

अटल स्थिर काष्ठा tपंचांग_resource_manager_func vmw_thp_func;

अटल पूर्णांक vmw_thp_insert_aligned(काष्ठा drm_mm *mm, काष्ठा drm_mm_node *node,
				  अचिन्हित दीर्घ align_pages,
				  स्थिर काष्ठा tपंचांग_place *place,
				  काष्ठा tपंचांग_resource *mem,
				  अचिन्हित दीर्घ lpfn,
				  क्रमागत drm_mm_insert_mode mode)
अणु
	अगर (align_pages >= mem->page_alignment &&
	    (!mem->page_alignment || align_pages % mem->page_alignment == 0)) अणु
		वापस drm_mm_insert_node_in_range(mm, node,
						   mem->num_pages,
						   align_pages, 0,
						   place->fpfn, lpfn, mode);
	पूर्ण

	वापस -ENOSPC;
पूर्ण

अटल पूर्णांक vmw_thp_get_node(काष्ठा tपंचांग_resource_manager *man,
			    काष्ठा tपंचांग_buffer_object *bo,
			    स्थिर काष्ठा tपंचांग_place *place,
			    काष्ठा tपंचांग_resource *mem)
अणु
	काष्ठा vmw_thp_manager *rman = to_thp_manager(man);
	काष्ठा drm_mm *mm = &rman->mm;
	काष्ठा drm_mm_node *node;
	अचिन्हित दीर्घ align_pages;
	अचिन्हित दीर्घ lpfn;
	क्रमागत drm_mm_insert_mode mode = DRM_MM_INSERT_BEST;
	पूर्णांक ret;

	node = kzalloc(माप(*node), GFP_KERNEL);
	अगर (!node)
		वापस -ENOMEM;

	lpfn = place->lpfn;
	अगर (!lpfn)
		lpfn = man->size;

	mode = DRM_MM_INSERT_BEST;
	अगर (place->flags & TTM_PL_FLAG_TOPDOWN)
		mode = DRM_MM_INSERT_HIGH;

	spin_lock(&rman->lock);
	अगर (IS_ENABLED(CONFIG_HAVE_ARCH_TRANSPARENT_HUGEPAGE_PUD)) अणु
		align_pages = (HPAGE_PUD_SIZE >> PAGE_SHIFT);
		अगर (mem->num_pages >= align_pages) अणु
			ret = vmw_thp_insert_aligned(mm, node, align_pages,
						     place, mem, lpfn, mode);
			अगर (!ret)
				जाओ found_unlock;
		पूर्ण
	पूर्ण

	align_pages = (HPAGE_PMD_SIZE >> PAGE_SHIFT);
	अगर (mem->num_pages >= align_pages) अणु
		ret = vmw_thp_insert_aligned(mm, node, align_pages, place, mem,
					     lpfn, mode);
		अगर (!ret)
			जाओ found_unlock;
	पूर्ण

	ret = drm_mm_insert_node_in_range(mm, node, mem->num_pages,
					  mem->page_alignment, 0,
					  place->fpfn, lpfn, mode);
found_unlock:
	spin_unlock(&rman->lock);

	अगर (unlikely(ret)) अणु
		kमुक्त(node);
	पूर्ण अन्यथा अणु
		mem->mm_node = node;
		mem->start = node->start;
	पूर्ण

	वापस ret;
पूर्ण



अटल व्योम vmw_thp_put_node(काष्ठा tपंचांग_resource_manager *man,
			     काष्ठा tपंचांग_resource *mem)
अणु
	काष्ठा vmw_thp_manager *rman = to_thp_manager(man);

	अगर (mem->mm_node) अणु
		spin_lock(&rman->lock);
		drm_mm_हटाओ_node(mem->mm_node);
		spin_unlock(&rman->lock);

		kमुक्त(mem->mm_node);
		mem->mm_node = शून्य;
	पूर्ण
पूर्ण

पूर्णांक vmw_thp_init(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा vmw_thp_manager *rman;

	rman = kzalloc(माप(*rman), GFP_KERNEL);
	अगर (!rman)
		वापस -ENOMEM;

	tपंचांग_resource_manager_init(&rman->manager,
				  dev_priv->vram_size >> PAGE_SHIFT);

	rman->manager.func = &vmw_thp_func;
	drm_mm_init(&rman->mm, 0, rman->manager.size);
	spin_lock_init(&rman->lock);

	tपंचांग_set_driver_manager(&dev_priv->bdev, TTM_PL_VRAM, &rman->manager);
	tपंचांग_resource_manager_set_used(&rman->manager, true);
	वापस 0;
पूर्ण

व्योम vmw_thp_fini(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(&dev_priv->bdev, TTM_PL_VRAM);
	काष्ठा vmw_thp_manager *rman = to_thp_manager(man);
	काष्ठा drm_mm *mm = &rman->mm;
	पूर्णांक ret;

	tपंचांग_resource_manager_set_used(man, false);

	ret = tपंचांग_resource_manager_evict_all(&dev_priv->bdev, man);
	अगर (ret)
		वापस;
	spin_lock(&rman->lock);
	drm_mm_clean(mm);
	drm_mm_takeकरोwn(mm);
	spin_unlock(&rman->lock);
	tपंचांग_resource_manager_cleanup(man);
	tपंचांग_set_driver_manager(&dev_priv->bdev, TTM_PL_VRAM, शून्य);
	kमुक्त(rman);
पूर्ण

अटल व्योम vmw_thp_debug(काष्ठा tपंचांग_resource_manager *man,
			  काष्ठा drm_prपूर्णांकer *prपूर्णांकer)
अणु
	काष्ठा vmw_thp_manager *rman = to_thp_manager(man);

	spin_lock(&rman->lock);
	drm_mm_prपूर्णांक(&rman->mm, prपूर्णांकer);
	spin_unlock(&rman->lock);
पूर्ण

अटल स्थिर काष्ठा tपंचांग_resource_manager_func vmw_thp_func = अणु
	.alloc = vmw_thp_get_node,
	.मुक्त = vmw_thp_put_node,
	.debug = vmw_thp_debug
पूर्ण;
