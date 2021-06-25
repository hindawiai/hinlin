<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */

/*
 * Copyright (c) 2006-2009 VMware, Inc., Palo Alto, CA., USA
 * Copyright 2020 Advanced Micro Devices, Inc.
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

#घोषणा pr_fmt(fmt) "[TTM DEVICE] " fmt

#समावेश <linux/mm.h>

#समावेश <drm/tपंचांग/tपंचांग_device.h>
#समावेश <drm/tपंचांग/tपंचांग_tt.h>
#समावेश <drm/tपंचांग/tपंचांग_placement.h>
#समावेश <drm/tपंचांग/tपंचांग_bo_api.h>

#समावेश "ttm_module.h"

/**
 * tपंचांग_global_mutex - protecting the global state
 */
DEFINE_MUTEX(tपंचांग_global_mutex);
अचिन्हित tपंचांग_glob_use_count;
काष्ठा tपंचांग_global tपंचांग_glob;
EXPORT_SYMBOL(tपंचांग_glob);

अटल व्योम tपंचांग_global_release(व्योम)
अणु
	काष्ठा tपंचांग_global *glob = &tपंचांग_glob;

	mutex_lock(&tपंचांग_global_mutex);
	अगर (--tपंचांग_glob_use_count > 0)
		जाओ out;

	tपंचांग_pool_mgr_fini();

	__मुक्त_page(glob->dummy_पढ़ो_page);
	स_रखो(glob, 0, माप(*glob));
out:
	mutex_unlock(&tपंचांग_global_mutex);
पूर्ण

अटल पूर्णांक tपंचांग_global_init(व्योम)
अणु
	काष्ठा tपंचांग_global *glob = &tपंचांग_glob;
	अचिन्हित दीर्घ num_pages, num_dma32;
	काष्ठा sysinfo si;
	पूर्णांक ret = 0;

	mutex_lock(&tपंचांग_global_mutex);
	अगर (++tपंचांग_glob_use_count > 1)
		जाओ out;

	si_meminfo(&si);

	/* Limit the number of pages in the pool to about 50% of the total
	 * प्रणाली memory.
	 */
	num_pages = ((u64)si.totalram * si.mem_unit) >> PAGE_SHIFT;
	num_pages /= 2;

	/* But क्रम DMA32 we limit ourself to only use 2GiB maximum. */
	num_dma32 = (u64)(si.totalram - si.totalhigh) * si.mem_unit
		>> PAGE_SHIFT;
	num_dma32 = min(num_dma32, 2UL << (30 - PAGE_SHIFT));

	tपंचांग_pool_mgr_init(num_pages);
	tपंचांग_tt_mgr_init(num_pages, num_dma32);

	glob->dummy_पढ़ो_page = alloc_page(__GFP_ZERO | GFP_DMA32);

	अगर (unlikely(glob->dummy_पढ़ो_page == शून्य)) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	INIT_LIST_HEAD(&glob->device_list);
	atomic_set(&glob->bo_count, 0);

	debugfs_create_atomic_t("buffer_objects", 0444, tपंचांग_debugfs_root,
				&glob->bo_count);
out:
	mutex_unlock(&tपंचांग_global_mutex);
	वापस ret;
पूर्ण

/**
 * A buffer object shrink method that tries to swap out the first
 * buffer object on the global::swap_lru list.
 */
पूर्णांक tपंचांग_global_swapout(काष्ठा tपंचांग_operation_ctx *ctx, gfp_t gfp_flags)
अणु
	काष्ठा tपंचांग_global *glob = &tपंचांग_glob;
	काष्ठा tपंचांग_device *bdev;
	पूर्णांक ret = 0;

	mutex_lock(&tपंचांग_global_mutex);
	list_क्रम_each_entry(bdev, &glob->device_list, device_list) अणु
		ret = tपंचांग_device_swapout(bdev, ctx, gfp_flags);
		अगर (ret > 0) अणु
			list_move_tail(&bdev->device_list, &glob->device_list);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&tपंचांग_global_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(tपंचांग_global_swapout);

पूर्णांक tपंचांग_device_swapout(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_operation_ctx *ctx,
		       gfp_t gfp_flags)
अणु
	काष्ठा tपंचांग_resource_manager *man;
	काष्ठा tपंचांग_buffer_object *bo;
	अचिन्हित i, j;
	पूर्णांक ret;

	spin_lock(&bdev->lru_lock);
	क्रम (i = TTM_PL_SYSTEM; i < TTM_NUM_MEM_TYPES; ++i) अणु
		man = tपंचांग_manager_type(bdev, i);
		अगर (!man || !man->use_tt)
			जारी;

		क्रम (j = 0; j < TTM_MAX_BO_PRIORITY; ++j) अणु
			list_क्रम_each_entry(bo, &man->lru[j], lru) अणु
				uपूर्णांक32_t num_pages = PFN_UP(bo->base.size);

				ret = tपंचांग_bo_swapout(bo, ctx, gfp_flags);
				/* tपंचांग_bo_swapout has dropped the lru_lock */
				अगर (!ret)
					वापस num_pages;
				अगर (ret != -EBUSY)
					वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&bdev->lru_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tपंचांग_device_swapout);

अटल व्योम tपंचांग_init_sysman(काष्ठा tपंचांग_device *bdev)
अणु
	काष्ठा tपंचांग_resource_manager *man = &bdev->sysman;

	/*
	 * Initialize the प्रणाली memory buffer type.
	 * Other types need to be driver / IOCTL initialized.
	 */
	man->use_tt = true;

	tपंचांग_resource_manager_init(man, 0);
	tपंचांग_set_driver_manager(bdev, TTM_PL_SYSTEM, man);
	tपंचांग_resource_manager_set_used(man, true);
पूर्ण

अटल व्योम tपंचांग_device_delayed_workqueue(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tपंचांग_device *bdev =
		container_of(work, काष्ठा tपंचांग_device, wq.work);

	अगर (!tपंचांग_bo_delayed_delete(bdev, false))
		schedule_delayed_work(&bdev->wq,
				      ((HZ / 100) < 1) ? 1 : HZ / 100);
पूर्ण

/**
 * tपंचांग_device_init
 *
 * @bdev: A poपूर्णांकer to a काष्ठा tपंचांग_device to initialize.
 * @funcs: Function table क्रम the device.
 * @dev: The core kernel device poपूर्णांकer क्रम DMA mappings and allocations.
 * @mapping: The address space to use क्रम this bo.
 * @vma_manager: A poपूर्णांकer to a vma manager.
 * @use_dma_alloc: If coherent DMA allocation API should be used.
 * @use_dma32: If we should use GFP_DMA32 क्रम device memory allocations.
 *
 * Initializes a काष्ठा tपंचांग_device:
 * Returns:
 * !0: Failure.
 */
पूर्णांक tपंचांग_device_init(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_device_funcs *funcs,
		    काष्ठा device *dev, काष्ठा address_space *mapping,
		    काष्ठा drm_vma_offset_manager *vma_manager,
		    bool use_dma_alloc, bool use_dma32)
अणु
	काष्ठा tपंचांग_global *glob = &tपंचांग_glob;
	पूर्णांक ret;

	अगर (WARN_ON(vma_manager == शून्य))
		वापस -EINVAL;

	ret = tपंचांग_global_init();
	अगर (ret)
		वापस ret;

	bdev->funcs = funcs;

	tपंचांग_init_sysman(bdev);
	tपंचांग_pool_init(&bdev->pool, dev, use_dma_alloc, use_dma32);

	bdev->vma_manager = vma_manager;
	INIT_DELAYED_WORK(&bdev->wq, tपंचांग_device_delayed_workqueue);
	spin_lock_init(&bdev->lru_lock);
	INIT_LIST_HEAD(&bdev->ddestroy);
	bdev->dev_mapping = mapping;
	mutex_lock(&tपंचांग_global_mutex);
	list_add_tail(&bdev->device_list, &glob->device_list);
	mutex_unlock(&tपंचांग_global_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tपंचांग_device_init);

व्योम tपंचांग_device_fini(काष्ठा tपंचांग_device *bdev)
अणु
	काष्ठा tपंचांग_resource_manager *man;
	अचिन्हित i;

	man = tपंचांग_manager_type(bdev, TTM_PL_SYSTEM);
	tपंचांग_resource_manager_set_used(man, false);
	tपंचांग_set_driver_manager(bdev, TTM_PL_SYSTEM, शून्य);

	mutex_lock(&tपंचांग_global_mutex);
	list_del(&bdev->device_list);
	mutex_unlock(&tपंचांग_global_mutex);

	cancel_delayed_work_sync(&bdev->wq);

	अगर (tपंचांग_bo_delayed_delete(bdev, true))
		pr_debug("Delayed destroy list was clean\n");

	spin_lock(&bdev->lru_lock);
	क्रम (i = 0; i < TTM_MAX_BO_PRIORITY; ++i)
		अगर (list_empty(&man->lru[0]))
			pr_debug("Swap list %d was clean\n", i);
	spin_unlock(&bdev->lru_lock);

	tपंचांग_pool_fini(&bdev->pool);
	tपंचांग_global_release();
पूर्ण
EXPORT_SYMBOL(tपंचांग_device_fini);
