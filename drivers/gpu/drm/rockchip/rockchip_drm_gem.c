<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author:Mark Yao <mark.yao@rock-chips.com>
 */

#समावेश <linux/dma-buf.h>
#समावेश <linux/iommu.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_prime.h>
#समावेश <drm/drm_vma_manager.h>

#समावेश "rockchip_drm_drv.h"
#समावेश "rockchip_drm_gem.h"

अटल पूर्णांक rockchip_gem_iommu_map(काष्ठा rockchip_gem_object *rk_obj)
अणु
	काष्ठा drm_device *drm = rk_obj->base.dev;
	काष्ठा rockchip_drm_निजी *निजी = drm->dev_निजी;
	पूर्णांक prot = IOMMU_READ | IOMMU_WRITE;
	sमाप_प्रकार ret;

	mutex_lock(&निजी->mm_lock);
	ret = drm_mm_insert_node_generic(&निजी->mm, &rk_obj->mm,
					 rk_obj->base.size, PAGE_SIZE,
					 0, 0);
	mutex_unlock(&निजी->mm_lock);

	अगर (ret < 0) अणु
		DRM_ERROR("out of I/O virtual memory: %zd\n", ret);
		वापस ret;
	पूर्ण

	rk_obj->dma_addr = rk_obj->mm.start;

	ret = iommu_map_sgtable(निजी->करोमुख्य, rk_obj->dma_addr, rk_obj->sgt,
				prot);
	अगर (ret < rk_obj->base.size) अणु
		DRM_ERROR("failed to map buffer: size=%zd request_size=%zd\n",
			  ret, rk_obj->base.size);
		ret = -ENOMEM;
		जाओ err_हटाओ_node;
	पूर्ण

	rk_obj->size = ret;

	वापस 0;

err_हटाओ_node:
	mutex_lock(&निजी->mm_lock);
	drm_mm_हटाओ_node(&rk_obj->mm);
	mutex_unlock(&निजी->mm_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_gem_iommu_unmap(काष्ठा rockchip_gem_object *rk_obj)
अणु
	काष्ठा drm_device *drm = rk_obj->base.dev;
	काष्ठा rockchip_drm_निजी *निजी = drm->dev_निजी;

	iommu_unmap(निजी->करोमुख्य, rk_obj->dma_addr, rk_obj->size);

	mutex_lock(&निजी->mm_lock);

	drm_mm_हटाओ_node(&rk_obj->mm);

	mutex_unlock(&निजी->mm_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_gem_get_pages(काष्ठा rockchip_gem_object *rk_obj)
अणु
	काष्ठा drm_device *drm = rk_obj->base.dev;
	पूर्णांक ret, i;
	काष्ठा scatterlist *s;

	rk_obj->pages = drm_gem_get_pages(&rk_obj->base);
	अगर (IS_ERR(rk_obj->pages))
		वापस PTR_ERR(rk_obj->pages);

	rk_obj->num_pages = rk_obj->base.size >> PAGE_SHIFT;

	rk_obj->sgt = drm_prime_pages_to_sg(rk_obj->base.dev,
					    rk_obj->pages, rk_obj->num_pages);
	अगर (IS_ERR(rk_obj->sgt)) अणु
		ret = PTR_ERR(rk_obj->sgt);
		जाओ err_put_pages;
	पूर्ण

	/*
	 * Fake up the SG table so that dma_sync_sg_क्रम_device() can be used
	 * to flush the pages associated with it.
	 *
	 * TODO: Replace this by drm_clflush_sg() once it can be implemented
	 * without relying on symbols that are not exported.
	 */
	क्रम_each_sgtable_sg(rk_obj->sgt, s, i)
		sg_dma_address(s) = sg_phys(s);

	dma_sync_sgtable_क्रम_device(drm->dev, rk_obj->sgt, DMA_TO_DEVICE);

	वापस 0;

err_put_pages:
	drm_gem_put_pages(&rk_obj->base, rk_obj->pages, false, false);
	वापस ret;
पूर्ण

अटल व्योम rockchip_gem_put_pages(काष्ठा rockchip_gem_object *rk_obj)
अणु
	sg_मुक्त_table(rk_obj->sgt);
	kमुक्त(rk_obj->sgt);
	drm_gem_put_pages(&rk_obj->base, rk_obj->pages, true, true);
पूर्ण

अटल पूर्णांक rockchip_gem_alloc_iommu(काष्ठा rockchip_gem_object *rk_obj,
				    bool alloc_kmap)
अणु
	पूर्णांक ret;

	ret = rockchip_gem_get_pages(rk_obj);
	अगर (ret < 0)
		वापस ret;

	ret = rockchip_gem_iommu_map(rk_obj);
	अगर (ret < 0)
		जाओ err_मुक्त;

	अगर (alloc_kmap) अणु
		rk_obj->kvaddr = vmap(rk_obj->pages, rk_obj->num_pages, VM_MAP,
				      pgprot_ग_लिखोcombine(PAGE_KERNEL));
		अगर (!rk_obj->kvaddr) अणु
			DRM_ERROR("failed to vmap() buffer\n");
			ret = -ENOMEM;
			जाओ err_unmap;
		पूर्ण
	पूर्ण

	वापस 0;

err_unmap:
	rockchip_gem_iommu_unmap(rk_obj);
err_मुक्त:
	rockchip_gem_put_pages(rk_obj);

	वापस ret;
पूर्ण

अटल पूर्णांक rockchip_gem_alloc_dma(काष्ठा rockchip_gem_object *rk_obj,
				  bool alloc_kmap)
अणु
	काष्ठा drm_gem_object *obj = &rk_obj->base;
	काष्ठा drm_device *drm = obj->dev;

	rk_obj->dma_attrs = DMA_ATTR_WRITE_COMBINE;

	अगर (!alloc_kmap)
		rk_obj->dma_attrs |= DMA_ATTR_NO_KERNEL_MAPPING;

	rk_obj->kvaddr = dma_alloc_attrs(drm->dev, obj->size,
					 &rk_obj->dma_addr, GFP_KERNEL,
					 rk_obj->dma_attrs);
	अगर (!rk_obj->kvaddr) अणु
		DRM_ERROR("failed to allocate %zu byte dma buffer", obj->size);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_gem_alloc_buf(काष्ठा rockchip_gem_object *rk_obj,
				  bool alloc_kmap)
अणु
	काष्ठा drm_gem_object *obj = &rk_obj->base;
	काष्ठा drm_device *drm = obj->dev;
	काष्ठा rockchip_drm_निजी *निजी = drm->dev_निजी;

	अगर (निजी->करोमुख्य)
		वापस rockchip_gem_alloc_iommu(rk_obj, alloc_kmap);
	अन्यथा
		वापस rockchip_gem_alloc_dma(rk_obj, alloc_kmap);
पूर्ण

अटल व्योम rockchip_gem_मुक्त_iommu(काष्ठा rockchip_gem_object *rk_obj)
अणु
	vunmap(rk_obj->kvaddr);
	rockchip_gem_iommu_unmap(rk_obj);
	rockchip_gem_put_pages(rk_obj);
पूर्ण

अटल व्योम rockchip_gem_मुक्त_dma(काष्ठा rockchip_gem_object *rk_obj)
अणु
	काष्ठा drm_gem_object *obj = &rk_obj->base;
	काष्ठा drm_device *drm = obj->dev;

	dma_मुक्त_attrs(drm->dev, obj->size, rk_obj->kvaddr, rk_obj->dma_addr,
		       rk_obj->dma_attrs);
पूर्ण

अटल व्योम rockchip_gem_मुक्त_buf(काष्ठा rockchip_gem_object *rk_obj)
अणु
	अगर (rk_obj->pages)
		rockchip_gem_मुक्त_iommu(rk_obj);
	अन्यथा
		rockchip_gem_मुक्त_dma(rk_obj);
पूर्ण

अटल पूर्णांक rockchip_drm_gem_object_mmap_iommu(काष्ठा drm_gem_object *obj,
					      काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा rockchip_gem_object *rk_obj = to_rockchip_obj(obj);
	अचिन्हित पूर्णांक count = obj->size >> PAGE_SHIFT;
	अचिन्हित दीर्घ user_count = vma_pages(vma);

	अगर (user_count == 0)
		वापस -ENXIO;

	वापस vm_map_pages(vma, rk_obj->pages, count);
पूर्ण

अटल पूर्णांक rockchip_drm_gem_object_mmap_dma(काष्ठा drm_gem_object *obj,
					    काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा rockchip_gem_object *rk_obj = to_rockchip_obj(obj);
	काष्ठा drm_device *drm = obj->dev;

	वापस dma_mmap_attrs(drm->dev, vma, rk_obj->kvaddr, rk_obj->dma_addr,
			      obj->size, rk_obj->dma_attrs);
पूर्ण

अटल पूर्णांक rockchip_drm_gem_object_mmap(काष्ठा drm_gem_object *obj,
					काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक ret;
	काष्ठा rockchip_gem_object *rk_obj = to_rockchip_obj(obj);

	/*
	 * We allocated a काष्ठा page table क्रम rk_obj, so clear
	 * VM_PFNMAP flag that was set by drm_gem_mmap_obj()/drm_gem_mmap().
	 */
	vma->vm_flags &= ~VM_PFNMAP;

	अगर (rk_obj->pages)
		ret = rockchip_drm_gem_object_mmap_iommu(obj, vma);
	अन्यथा
		ret = rockchip_drm_gem_object_mmap_dma(obj, vma);

	अगर (ret)
		drm_gem_vm_बंद(vma);

	वापस ret;
पूर्ण

पूर्णांक rockchip_gem_mmap_buf(काष्ठा drm_gem_object *obj,
			  काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक ret;

	ret = drm_gem_mmap_obj(obj, obj->size, vma);
	अगर (ret)
		वापस ret;

	वापस rockchip_drm_gem_object_mmap(obj, vma);
पूर्ण

/* drm driver mmap file operations */
पूर्णांक rockchip_gem_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret;

	ret = drm_gem_mmap(filp, vma);
	अगर (ret)
		वापस ret;

	/*
	 * Set vm_pgoff (used as a fake buffer offset by DRM) to 0 and map the
	 * whole buffer from the start.
	 */
	vma->vm_pgoff = 0;

	obj = vma->vm_निजी_data;

	वापस rockchip_drm_gem_object_mmap(obj, vma);
पूर्ण

अटल व्योम rockchip_gem_release_object(काष्ठा rockchip_gem_object *rk_obj)
अणु
	drm_gem_object_release(&rk_obj->base);
	kमुक्त(rk_obj);
पूर्ण

अटल स्थिर काष्ठा drm_gem_object_funcs rockchip_gem_object_funcs = अणु
	.मुक्त = rockchip_gem_मुक्त_object,
	.get_sg_table = rockchip_gem_prime_get_sg_table,
	.vmap = rockchip_gem_prime_vmap,
	.vunmap	= rockchip_gem_prime_vunmap,
	.vm_ops = &drm_gem_cma_vm_ops,
पूर्ण;

अटल काष्ठा rockchip_gem_object *
	rockchip_gem_alloc_object(काष्ठा drm_device *drm, अचिन्हित पूर्णांक size)
अणु
	काष्ठा rockchip_gem_object *rk_obj;
	काष्ठा drm_gem_object *obj;

	size = round_up(size, PAGE_SIZE);

	rk_obj = kzalloc(माप(*rk_obj), GFP_KERNEL);
	अगर (!rk_obj)
		वापस ERR_PTR(-ENOMEM);

	obj = &rk_obj->base;

	obj->funcs = &rockchip_gem_object_funcs;

	drm_gem_object_init(drm, obj, size);

	वापस rk_obj;
पूर्ण

काष्ठा rockchip_gem_object *
rockchip_gem_create_object(काष्ठा drm_device *drm, अचिन्हित पूर्णांक size,
			   bool alloc_kmap)
अणु
	काष्ठा rockchip_gem_object *rk_obj;
	पूर्णांक ret;

	rk_obj = rockchip_gem_alloc_object(drm, size);
	अगर (IS_ERR(rk_obj))
		वापस rk_obj;

	ret = rockchip_gem_alloc_buf(rk_obj, alloc_kmap);
	अगर (ret)
		जाओ err_मुक्त_rk_obj;

	वापस rk_obj;

err_मुक्त_rk_obj:
	rockchip_gem_release_object(rk_obj);
	वापस ERR_PTR(ret);
पूर्ण

/*
 * rockchip_gem_मुक्त_object - (काष्ठा drm_gem_object_funcs)->मुक्त
 * callback function
 */
व्योम rockchip_gem_मुक्त_object(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_device *drm = obj->dev;
	काष्ठा rockchip_drm_निजी *निजी = drm->dev_निजी;
	काष्ठा rockchip_gem_object *rk_obj = to_rockchip_obj(obj);

	अगर (obj->import_attach) अणु
		अगर (निजी->करोमुख्य) अणु
			rockchip_gem_iommu_unmap(rk_obj);
		पूर्ण अन्यथा अणु
			dma_unmap_sgtable(drm->dev, rk_obj->sgt,
					  DMA_BIसूचीECTIONAL, 0);
		पूर्ण
		drm_prime_gem_destroy(obj, rk_obj->sgt);
	पूर्ण अन्यथा अणु
		rockchip_gem_मुक्त_buf(rk_obj);
	पूर्ण

	rockchip_gem_release_object(rk_obj);
पूर्ण

/*
 * rockchip_gem_create_with_handle - allocate an object with the given
 * size and create a gem handle on it
 *
 * वापसs a काष्ठा rockchip_gem_object* on success or ERR_PTR values
 * on failure.
 */
अटल काष्ठा rockchip_gem_object *
rockchip_gem_create_with_handle(काष्ठा drm_file *file_priv,
				काष्ठा drm_device *drm, अचिन्हित पूर्णांक size,
				अचिन्हित पूर्णांक *handle)
अणु
	काष्ठा rockchip_gem_object *rk_obj;
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret;

	rk_obj = rockchip_gem_create_object(drm, size, false);
	अगर (IS_ERR(rk_obj))
		वापस ERR_CAST(rk_obj);

	obj = &rk_obj->base;

	/*
	 * allocate a id of idr table where the obj is रेजिस्टरed
	 * and handle has the id what user can see.
	 */
	ret = drm_gem_handle_create(file_priv, obj, handle);
	अगर (ret)
		जाओ err_handle_create;

	/* drop reference from allocate - handle holds it now. */
	drm_gem_object_put(obj);

	वापस rk_obj;

err_handle_create:
	rockchip_gem_मुक्त_object(obj);

	वापस ERR_PTR(ret);
पूर्ण

/*
 * rockchip_gem_dumb_create - (काष्ठा drm_driver)->dumb_create callback
 * function
 *
 * This aligns the pitch and size arguments to the minimum required. wrap
 * this पूर्णांकo your own function अगर you need bigger alignment.
 */
पूर्णांक rockchip_gem_dumb_create(काष्ठा drm_file *file_priv,
			     काष्ठा drm_device *dev,
			     काष्ठा drm_mode_create_dumb *args)
अणु
	काष्ठा rockchip_gem_object *rk_obj;
	पूर्णांक min_pitch = DIV_ROUND_UP(args->width * args->bpp, 8);

	/*
	 * align to 64 bytes since Mali requires it.
	 */
	args->pitch = ALIGN(min_pitch, 64);
	args->size = args->pitch * args->height;

	rk_obj = rockchip_gem_create_with_handle(file_priv, dev, args->size,
						 &args->handle);

	वापस PTR_ERR_OR_ZERO(rk_obj);
पूर्ण

/*
 * Allocate a sg_table क्रम this GEM object.
 * Note: Both the table's contents, and the sg_table itself must be मुक्तd by
 *       the caller.
 * Returns a poपूर्णांकer to the newly allocated sg_table, or an ERR_PTR() error.
 */
काष्ठा sg_table *rockchip_gem_prime_get_sg_table(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा rockchip_gem_object *rk_obj = to_rockchip_obj(obj);
	काष्ठा drm_device *drm = obj->dev;
	काष्ठा sg_table *sgt;
	पूर्णांक ret;

	अगर (rk_obj->pages)
		वापस drm_prime_pages_to_sg(obj->dev, rk_obj->pages, rk_obj->num_pages);

	sgt = kzalloc(माप(*sgt), GFP_KERNEL);
	अगर (!sgt)
		वापस ERR_PTR(-ENOMEM);

	ret = dma_get_sgtable_attrs(drm->dev, sgt, rk_obj->kvaddr,
				    rk_obj->dma_addr, obj->size,
				    rk_obj->dma_attrs);
	अगर (ret) अणु
		DRM_ERROR("failed to allocate sgt, %d\n", ret);
		kमुक्त(sgt);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस sgt;
पूर्ण

अटल पूर्णांक
rockchip_gem_iommu_map_sg(काष्ठा drm_device *drm,
			  काष्ठा dma_buf_attachment *attach,
			  काष्ठा sg_table *sg,
			  काष्ठा rockchip_gem_object *rk_obj)
अणु
	rk_obj->sgt = sg;
	वापस rockchip_gem_iommu_map(rk_obj);
पूर्ण

अटल पूर्णांक
rockchip_gem_dma_map_sg(काष्ठा drm_device *drm,
			काष्ठा dma_buf_attachment *attach,
			काष्ठा sg_table *sg,
			काष्ठा rockchip_gem_object *rk_obj)
अणु
	पूर्णांक err = dma_map_sgtable(drm->dev, sg, DMA_BIसूचीECTIONAL, 0);
	अगर (err)
		वापस err;

	अगर (drm_prime_get_contiguous_size(sg) < attach->dmabuf->size) अणु
		DRM_ERROR("failed to map sg_table to contiguous linear address.\n");
		dma_unmap_sgtable(drm->dev, sg, DMA_BIसूचीECTIONAL, 0);
		वापस -EINVAL;
	पूर्ण

	rk_obj->dma_addr = sg_dma_address(sg->sgl);
	rk_obj->sgt = sg;
	वापस 0;
पूर्ण

काष्ठा drm_gem_object *
rockchip_gem_prime_import_sg_table(काष्ठा drm_device *drm,
				   काष्ठा dma_buf_attachment *attach,
				   काष्ठा sg_table *sg)
अणु
	काष्ठा rockchip_drm_निजी *निजी = drm->dev_निजी;
	काष्ठा rockchip_gem_object *rk_obj;
	पूर्णांक ret;

	rk_obj = rockchip_gem_alloc_object(drm, attach->dmabuf->size);
	अगर (IS_ERR(rk_obj))
		वापस ERR_CAST(rk_obj);

	अगर (निजी->करोमुख्य)
		ret = rockchip_gem_iommu_map_sg(drm, attach, sg, rk_obj);
	अन्यथा
		ret = rockchip_gem_dma_map_sg(drm, attach, sg, rk_obj);

	अगर (ret < 0) अणु
		DRM_ERROR("failed to import sg table: %d\n", ret);
		जाओ err_मुक्त_rk_obj;
	पूर्ण

	वापस &rk_obj->base;

err_मुक्त_rk_obj:
	rockchip_gem_release_object(rk_obj);
	वापस ERR_PTR(ret);
पूर्ण

पूर्णांक rockchip_gem_prime_vmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map)
अणु
	काष्ठा rockchip_gem_object *rk_obj = to_rockchip_obj(obj);

	अगर (rk_obj->pages) अणु
		व्योम *vaddr = vmap(rk_obj->pages, rk_obj->num_pages, VM_MAP,
				  pgprot_ग_लिखोcombine(PAGE_KERNEL));
		अगर (!vaddr)
			वापस -ENOMEM;
		dma_buf_map_set_vaddr(map, vaddr);
		वापस 0;
	पूर्ण

	अगर (rk_obj->dma_attrs & DMA_ATTR_NO_KERNEL_MAPPING)
		वापस -ENOMEM;
	dma_buf_map_set_vaddr(map, rk_obj->kvaddr);

	वापस 0;
पूर्ण

व्योम rockchip_gem_prime_vunmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map)
अणु
	काष्ठा rockchip_gem_object *rk_obj = to_rockchip_obj(obj);

	अगर (rk_obj->pages) अणु
		vunmap(map->vaddr);
		वापस;
	पूर्ण

	/* Nothing to करो अगर allocated by DMA mapping API. */
पूर्ण
