<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
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
 * Authors: Dave Airlie
 *          Alon Levy
 */

#समावेश <linux/dma-buf-map.h>
#समावेश <linux/io-mapping.h>

#समावेश "qxl_drv.h"
#समावेश "qxl_object.h"

अटल पूर्णांक __qxl_bo_pin(काष्ठा qxl_bo *bo);
अटल व्योम __qxl_bo_unpin(काष्ठा qxl_bo *bo);

अटल व्योम qxl_tपंचांग_bo_destroy(काष्ठा tपंचांग_buffer_object *tbo)
अणु
	काष्ठा qxl_bo *bo;
	काष्ठा qxl_device *qdev;

	bo = to_qxl_bo(tbo);
	qdev = to_qxl(bo->tbo.base.dev);

	qxl_surface_evict(qdev, bo, false);
	WARN_ON_ONCE(bo->map_count > 0);
	mutex_lock(&qdev->gem.mutex);
	list_del_init(&bo->list);
	mutex_unlock(&qdev->gem.mutex);
	drm_gem_object_release(&bo->tbo.base);
	kमुक्त(bo);
पूर्ण

bool qxl_tपंचांग_bo_is_qxl_bo(काष्ठा tपंचांग_buffer_object *bo)
अणु
	अगर (bo->destroy == &qxl_tपंचांग_bo_destroy)
		वापस true;
	वापस false;
पूर्ण

व्योम qxl_tपंचांग_placement_from_करोमुख्य(काष्ठा qxl_bo *qbo, u32 करोमुख्य)
अणु
	u32 c = 0;
	u32 pflag = 0;
	अचिन्हित पूर्णांक i;

	अगर (qbo->tbo.base.size <= PAGE_SIZE)
		pflag |= TTM_PL_FLAG_TOPDOWN;

	qbo->placement.placement = qbo->placements;
	qbo->placement.busy_placement = qbo->placements;
	अगर (करोमुख्य == QXL_GEM_DOMAIN_VRAM) अणु
		qbo->placements[c].mem_type = TTM_PL_VRAM;
		qbo->placements[c++].flags = pflag;
	पूर्ण
	अगर (करोमुख्य == QXL_GEM_DOMAIN_SURFACE) अणु
		qbo->placements[c].mem_type = TTM_PL_PRIV;
		qbo->placements[c++].flags = pflag;
		qbo->placements[c].mem_type = TTM_PL_VRAM;
		qbo->placements[c++].flags = pflag;
	पूर्ण
	अगर (करोमुख्य == QXL_GEM_DOMAIN_CPU) अणु
		qbo->placements[c].mem_type = TTM_PL_SYSTEM;
		qbo->placements[c++].flags = pflag;
	पूर्ण
	अगर (!c) अणु
		qbo->placements[c].mem_type = TTM_PL_SYSTEM;
		qbo->placements[c++].flags = 0;
	पूर्ण
	qbo->placement.num_placement = c;
	qbo->placement.num_busy_placement = c;
	क्रम (i = 0; i < c; ++i) अणु
		qbo->placements[i].fpfn = 0;
		qbo->placements[i].lpfn = 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा drm_gem_object_funcs qxl_object_funcs = अणु
	.मुक्त = qxl_gem_object_मुक्त,
	.खोलो = qxl_gem_object_खोलो,
	.बंद = qxl_gem_object_बंद,
	.pin = qxl_gem_prime_pin,
	.unpin = qxl_gem_prime_unpin,
	.get_sg_table = qxl_gem_prime_get_sg_table,
	.vmap = qxl_gem_prime_vmap,
	.vunmap = qxl_gem_prime_vunmap,
	.mmap = drm_gem_tपंचांग_mmap,
	.prपूर्णांक_info = drm_gem_tपंचांग_prपूर्णांक_info,
पूर्ण;

पूर्णांक qxl_bo_create(काष्ठा qxl_device *qdev, अचिन्हित दीर्घ size,
		  bool kernel, bool pinned, u32 करोमुख्य, u32 priority,
		  काष्ठा qxl_surface *surf,
		  काष्ठा qxl_bo **bo_ptr)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु !kernel, false पूर्ण;
	काष्ठा qxl_bo *bo;
	क्रमागत tपंचांग_bo_type type;
	पूर्णांक r;

	अगर (kernel)
		type = tपंचांग_bo_type_kernel;
	अन्यथा
		type = tपंचांग_bo_type_device;
	*bo_ptr = शून्य;
	bo = kzalloc(माप(काष्ठा qxl_bo), GFP_KERNEL);
	अगर (bo == शून्य)
		वापस -ENOMEM;
	size = roundup(size, PAGE_SIZE);
	r = drm_gem_object_init(&qdev->ddev, &bo->tbo.base, size);
	अगर (unlikely(r)) अणु
		kमुक्त(bo);
		वापस r;
	पूर्ण
	bo->tbo.base.funcs = &qxl_object_funcs;
	bo->type = करोमुख्य;
	bo->surface_id = 0;
	INIT_LIST_HEAD(&bo->list);

	अगर (surf)
		bo->surf = *surf;

	qxl_tपंचांग_placement_from_करोमुख्य(bo, करोमुख्य);

	bo->tbo.priority = priority;
	r = tपंचांग_bo_init_reserved(&qdev->mman.bdev, &bo->tbo, size, type,
				 &bo->placement, 0, &ctx, शून्य, शून्य,
				 &qxl_tपंचांग_bo_destroy);
	अगर (unlikely(r != 0)) अणु
		अगर (r != -ERESTARTSYS)
			dev_err(qdev->ddev.dev,
				"object_init failed for (%lu, 0x%08X)\n",
				size, करोमुख्य);
		वापस r;
	पूर्ण
	अगर (pinned)
		tपंचांग_bo_pin(&bo->tbo);
	tपंचांग_bo_unreserve(&bo->tbo);
	*bo_ptr = bo;
	वापस 0;
पूर्ण

पूर्णांक qxl_bo_vmap_locked(काष्ठा qxl_bo *bo, काष्ठा dma_buf_map *map)
अणु
	पूर्णांक r;

	dma_resv_निश्चित_held(bo->tbo.base.resv);

	अगर (bo->kptr) अणु
		bo->map_count++;
		जाओ out;
	पूर्ण
	r = tपंचांग_bo_vmap(&bo->tbo, &bo->map);
	अगर (r)
		वापस r;
	bo->map_count = 1;

	/* TODO: Remove kptr in favor of map everywhere. */
	अगर (bo->map.is_iomem)
		bo->kptr = (व्योम *)bo->map.vaddr_iomem;
	अन्यथा
		bo->kptr = bo->map.vaddr;

out:
	*map = bo->map;
	वापस 0;
पूर्ण

पूर्णांक qxl_bo_vmap(काष्ठा qxl_bo *bo, काष्ठा dma_buf_map *map)
अणु
	पूर्णांक r;

	r = qxl_bo_reserve(bo);
	अगर (r)
		वापस r;

	r = __qxl_bo_pin(bo);
	अगर (r) अणु
		qxl_bo_unreserve(bo);
		वापस r;
	पूर्ण

	r = qxl_bo_vmap_locked(bo, map);
	qxl_bo_unreserve(bo);
	वापस r;
पूर्ण

व्योम *qxl_bo_kmap_atomic_page(काष्ठा qxl_device *qdev,
			      काष्ठा qxl_bo *bo, पूर्णांक page_offset)
अणु
	अचिन्हित दीर्घ offset;
	व्योम *rptr;
	पूर्णांक ret;
	काष्ठा io_mapping *map;
	काष्ठा dma_buf_map bo_map;

	अगर (bo->tbo.mem.mem_type == TTM_PL_VRAM)
		map = qdev->vram_mapping;
	अन्यथा अगर (bo->tbo.mem.mem_type == TTM_PL_PRIV)
		map = qdev->surface_mapping;
	अन्यथा
		जाओ fallback;

	offset = bo->tbo.mem.start << PAGE_SHIFT;
	वापस io_mapping_map_atomic_wc(map, offset + page_offset);
fallback:
	अगर (bo->kptr) अणु
		rptr = bo->kptr + (page_offset * PAGE_SIZE);
		वापस rptr;
	पूर्ण

	ret = qxl_bo_vmap_locked(bo, &bo_map);
	अगर (ret)
		वापस शून्य;
	rptr = bo_map.vaddr; /* TODO: Use mapping असलtraction properly */

	rptr += page_offset * PAGE_SIZE;
	वापस rptr;
पूर्ण

व्योम qxl_bo_vunmap_locked(काष्ठा qxl_bo *bo)
अणु
	dma_resv_निश्चित_held(bo->tbo.base.resv);

	अगर (bo->kptr == शून्य)
		वापस;
	bo->map_count--;
	अगर (bo->map_count > 0)
		वापस;
	bo->kptr = शून्य;
	tपंचांग_bo_vunmap(&bo->tbo, &bo->map);
पूर्ण

पूर्णांक qxl_bo_vunmap(काष्ठा qxl_bo *bo)
अणु
	पूर्णांक r;

	r = qxl_bo_reserve(bo);
	अगर (r)
		वापस r;

	qxl_bo_vunmap_locked(bo);
	__qxl_bo_unpin(bo);
	qxl_bo_unreserve(bo);
	वापस 0;
पूर्ण

व्योम qxl_bo_kunmap_atomic_page(काष्ठा qxl_device *qdev,
			       काष्ठा qxl_bo *bo, व्योम *pmap)
अणु
	अगर ((bo->tbo.mem.mem_type != TTM_PL_VRAM) &&
	    (bo->tbo.mem.mem_type != TTM_PL_PRIV))
		जाओ fallback;

	io_mapping_unmap_atomic(pmap);
	वापस;
 fallback:
	qxl_bo_vunmap_locked(bo);
पूर्ण

व्योम qxl_bo_unref(काष्ठा qxl_bo **bo)
अणु
	अगर ((*bo) == शून्य)
		वापस;

	drm_gem_object_put(&(*bo)->tbo.base);
	*bo = शून्य;
पूर्ण

काष्ठा qxl_bo *qxl_bo_ref(काष्ठा qxl_bo *bo)
अणु
	drm_gem_object_get(&bo->tbo.base);
	वापस bo;
पूर्ण

अटल पूर्णांक __qxl_bo_pin(काष्ठा qxl_bo *bo)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु false, false पूर्ण;
	काष्ठा drm_device *ddev = bo->tbo.base.dev;
	पूर्णांक r;

	अगर (bo->tbo.pin_count) अणु
		tपंचांग_bo_pin(&bo->tbo);
		वापस 0;
	पूर्ण
	qxl_tपंचांग_placement_from_करोमुख्य(bo, bo->type);
	r = tपंचांग_bo_validate(&bo->tbo, &bo->placement, &ctx);
	अगर (likely(r == 0))
		tपंचांग_bo_pin(&bo->tbo);
	अगर (unlikely(r != 0))
		dev_err(ddev->dev, "%p pin failed\n", bo);
	वापस r;
पूर्ण

अटल व्योम __qxl_bo_unpin(काष्ठा qxl_bo *bo)
अणु
	tपंचांग_bo_unpin(&bo->tbo);
पूर्ण

/*
 * Reserve the BO beक्रमe pinning the object.  If the BO was reserved
 * beक्रमehand, use the पूर्णांकernal version directly __qxl_bo_pin.
 *
 */
पूर्णांक qxl_bo_pin(काष्ठा qxl_bo *bo)
अणु
	पूर्णांक r;

	r = qxl_bo_reserve(bo);
	अगर (r)
		वापस r;

	r = __qxl_bo_pin(bo);
	qxl_bo_unreserve(bo);
	वापस r;
पूर्ण

/*
 * Reserve the BO beक्रमe pinning the object.  If the BO was reserved
 * beक्रमehand, use the पूर्णांकernal version directly __qxl_bo_unpin.
 *
 */
पूर्णांक qxl_bo_unpin(काष्ठा qxl_bo *bo)
अणु
	पूर्णांक r;

	r = qxl_bo_reserve(bo);
	अगर (r)
		वापस r;

	__qxl_bo_unpin(bo);
	qxl_bo_unreserve(bo);
	वापस 0;
पूर्ण

व्योम qxl_bo_क्रमce_delete(काष्ठा qxl_device *qdev)
अणु
	काष्ठा qxl_bo *bo, *n;

	अगर (list_empty(&qdev->gem.objects))
		वापस;
	dev_err(qdev->ddev.dev, "Userspace still has active objects !\n");
	list_क्रम_each_entry_safe(bo, n, &qdev->gem.objects, list) अणु
		dev_err(qdev->ddev.dev, "%p %p %lu %lu force free\n",
			&bo->tbo.base, bo, (अचिन्हित दीर्घ)bo->tbo.base.size,
			*((अचिन्हित दीर्घ *)&bo->tbo.base.refcount));
		mutex_lock(&qdev->gem.mutex);
		list_del_init(&bo->list);
		mutex_unlock(&qdev->gem.mutex);
		/* this should unref the tपंचांग bo */
		drm_gem_object_put(&bo->tbo.base);
	पूर्ण
पूर्ण

पूर्णांक qxl_bo_init(काष्ठा qxl_device *qdev)
अणु
	वापस qxl_tपंचांग_init(qdev);
पूर्ण

व्योम qxl_bo_fini(काष्ठा qxl_device *qdev)
अणु
	qxl_tपंचांग_fini(qdev);
पूर्ण

पूर्णांक qxl_bo_check_id(काष्ठा qxl_device *qdev, काष्ठा qxl_bo *bo)
अणु
	पूर्णांक ret;

	अगर (bo->type == QXL_GEM_DOMAIN_SURFACE && bo->surface_id == 0) अणु
		/* allocate a surface id क्रम this surface now */
		ret = qxl_surface_id_alloc(qdev, bo);
		अगर (ret)
			वापस ret;

		ret = qxl_hw_surface_alloc(qdev, bo);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक qxl_surf_evict(काष्ठा qxl_device *qdev)
अणु
	काष्ठा tपंचांग_resource_manager *man;

	man = tपंचांग_manager_type(&qdev->mman.bdev, TTM_PL_PRIV);
	वापस tपंचांग_resource_manager_evict_all(&qdev->mman.bdev, man);
पूर्ण

पूर्णांक qxl_vram_evict(काष्ठा qxl_device *qdev)
अणु
	काष्ठा tपंचांग_resource_manager *man;

	man = tपंचांग_manager_type(&qdev->mman.bdev, TTM_PL_VRAM);
	वापस tपंचांग_resource_manager_evict_all(&qdev->mman.bdev, man);
पूर्ण
