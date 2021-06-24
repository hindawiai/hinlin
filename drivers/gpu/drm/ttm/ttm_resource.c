<शैली गुरु>
/*
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

#समावेश <drm/tपंचांग/tपंचांग_resource.h>
#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>

पूर्णांक tपंचांग_resource_alloc(काष्ठा tपंचांग_buffer_object *bo,
		       स्थिर काष्ठा tपंचांग_place *place,
		       काष्ठा tपंचांग_resource *res)
अणु
	काष्ठा tपंचांग_resource_manager *man =
		tपंचांग_manager_type(bo->bdev, res->mem_type);

	res->mm_node = शून्य;
	अगर (!man->func || !man->func->alloc)
		वापस 0;

	वापस man->func->alloc(man, bo, place, res);
पूर्ण

व्योम tपंचांग_resource_मुक्त(काष्ठा tपंचांग_buffer_object *bo, काष्ठा tपंचांग_resource *res)
अणु
	काष्ठा tपंचांग_resource_manager *man =
		tपंचांग_manager_type(bo->bdev, res->mem_type);

	अगर (man->func && man->func->मुक्त)
		man->func->मुक्त(man, res);

	res->mm_node = शून्य;
	res->mem_type = TTM_PL_SYSTEM;
पूर्ण
EXPORT_SYMBOL(tपंचांग_resource_मुक्त);

/**
 * tपंचांग_resource_manager_init
 *
 * @man: memory manager object to init
 * @p_size: size managed area in pages.
 *
 * Initialise core parts of a manager object.
 */
व्योम tपंचांग_resource_manager_init(काष्ठा tपंचांग_resource_manager *man,
			       अचिन्हित दीर्घ p_size)
अणु
	अचिन्हित i;

	spin_lock_init(&man->move_lock);
	man->size = p_size;

	क्रम (i = 0; i < TTM_MAX_BO_PRIORITY; ++i)
		INIT_LIST_HEAD(&man->lru[i]);
	man->move = शून्य;
पूर्ण
EXPORT_SYMBOL(tपंचांग_resource_manager_init);

/*
 * tपंचांग_resource_manager_evict_all
 *
 * @bdev - device to use
 * @man - manager to use
 *
 * Evict all the objects out of a memory manager until it is empty.
 * Part of memory manager cleanup sequence.
 */
पूर्णांक tपंचांग_resource_manager_evict_all(काष्ठा tपंचांग_device *bdev,
				   काष्ठा tपंचांग_resource_manager *man)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु
		.पूर्णांकerruptible = false,
		.no_रुको_gpu = false,
		.क्रमce_alloc = true
	पूर्ण;
	काष्ठा dma_fence *fence;
	पूर्णांक ret;
	अचिन्हित i;

	/*
	 * Can't use standard list traversal since we're unlocking.
	 */

	spin_lock(&bdev->lru_lock);
	क्रम (i = 0; i < TTM_MAX_BO_PRIORITY; ++i) अणु
		जबतक (!list_empty(&man->lru[i])) अणु
			spin_unlock(&bdev->lru_lock);
			ret = tपंचांग_mem_evict_first(bdev, man, शून्य, &ctx,
						  शून्य);
			अगर (ret)
				वापस ret;
			spin_lock(&bdev->lru_lock);
		पूर्ण
	पूर्ण
	spin_unlock(&bdev->lru_lock);

	spin_lock(&man->move_lock);
	fence = dma_fence_get(man->move);
	spin_unlock(&man->move_lock);

	अगर (fence) अणु
		ret = dma_fence_रुको(fence, false);
		dma_fence_put(fence);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tपंचांग_resource_manager_evict_all);

/**
 * tपंचांग_resource_manager_debug
 *
 * @man: manager type to dump.
 * @p: prपूर्णांकer to use क्रम debug.
 */
व्योम tपंचांग_resource_manager_debug(काष्ठा tपंचांग_resource_manager *man,
				काष्ठा drm_prपूर्णांकer *p)
अणु
	drm_म_लिखो(p, "  use_type: %d\n", man->use_type);
	drm_म_लिखो(p, "  use_tt: %d\n", man->use_tt);
	drm_म_लिखो(p, "  size: %llu\n", man->size);
	अगर (man->func && man->func->debug)
		(*man->func->debug)(man, p);
पूर्ण
EXPORT_SYMBOL(tपंचांग_resource_manager_debug);
