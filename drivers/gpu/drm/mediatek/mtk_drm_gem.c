<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 MediaTek Inc.
 */

#समावेश <linux/dma-buf.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_prime.h>

#समावेश "mtk_drm_drv.h"
#समावेश "mtk_drm_gem.h"

अटल स्थिर काष्ठा drm_gem_object_funcs mtk_drm_gem_object_funcs = अणु
	.मुक्त = mtk_drm_gem_मुक्त_object,
	.get_sg_table = mtk_gem_prime_get_sg_table,
	.vmap = mtk_drm_gem_prime_vmap,
	.vunmap = mtk_drm_gem_prime_vunmap,
	.vm_ops = &drm_gem_cma_vm_ops,
पूर्ण;

अटल काष्ठा mtk_drm_gem_obj *mtk_drm_gem_init(काष्ठा drm_device *dev,
						अचिन्हित दीर्घ size)
अणु
	काष्ठा mtk_drm_gem_obj *mtk_gem_obj;
	पूर्णांक ret;

	size = round_up(size, PAGE_SIZE);

	mtk_gem_obj = kzalloc(माप(*mtk_gem_obj), GFP_KERNEL);
	अगर (!mtk_gem_obj)
		वापस ERR_PTR(-ENOMEM);

	mtk_gem_obj->base.funcs = &mtk_drm_gem_object_funcs;

	ret = drm_gem_object_init(dev, &mtk_gem_obj->base, size);
	अगर (ret < 0) अणु
		DRM_ERROR("failed to initialize gem object\n");
		kमुक्त(mtk_gem_obj);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस mtk_gem_obj;
पूर्ण

काष्ठा mtk_drm_gem_obj *mtk_drm_gem_create(काष्ठा drm_device *dev,
					   माप_प्रकार size, bool alloc_kmap)
अणु
	काष्ठा mtk_drm_निजी *priv = dev->dev_निजी;
	काष्ठा mtk_drm_gem_obj *mtk_gem;
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret;

	mtk_gem = mtk_drm_gem_init(dev, size);
	अगर (IS_ERR(mtk_gem))
		वापस ERR_CAST(mtk_gem);

	obj = &mtk_gem->base;

	mtk_gem->dma_attrs = DMA_ATTR_WRITE_COMBINE;

	अगर (!alloc_kmap)
		mtk_gem->dma_attrs |= DMA_ATTR_NO_KERNEL_MAPPING;

	mtk_gem->cookie = dma_alloc_attrs(priv->dma_dev, obj->size,
					  &mtk_gem->dma_addr, GFP_KERNEL,
					  mtk_gem->dma_attrs);
	अगर (!mtk_gem->cookie) अणु
		DRM_ERROR("failed to allocate %zx byte dma buffer", obj->size);
		ret = -ENOMEM;
		जाओ err_gem_मुक्त;
	पूर्ण

	अगर (alloc_kmap)
		mtk_gem->kvaddr = mtk_gem->cookie;

	DRM_DEBUG_DRIVER("cookie = %p dma_addr = %pad size = %zu\n",
			 mtk_gem->cookie, &mtk_gem->dma_addr,
			 size);

	वापस mtk_gem;

err_gem_मुक्त:
	drm_gem_object_release(obj);
	kमुक्त(mtk_gem);
	वापस ERR_PTR(ret);
पूर्ण

व्योम mtk_drm_gem_मुक्त_object(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा mtk_drm_gem_obj *mtk_gem = to_mtk_gem_obj(obj);
	काष्ठा mtk_drm_निजी *priv = obj->dev->dev_निजी;

	अगर (mtk_gem->sg)
		drm_prime_gem_destroy(obj, mtk_gem->sg);
	अन्यथा
		dma_मुक्त_attrs(priv->dma_dev, obj->size, mtk_gem->cookie,
			       mtk_gem->dma_addr, mtk_gem->dma_attrs);

	/* release file poपूर्णांकer to gem object. */
	drm_gem_object_release(obj);

	kमुक्त(mtk_gem);
पूर्ण

पूर्णांक mtk_drm_gem_dumb_create(काष्ठा drm_file *file_priv, काष्ठा drm_device *dev,
			    काष्ठा drm_mode_create_dumb *args)
अणु
	काष्ठा mtk_drm_gem_obj *mtk_gem;
	पूर्णांक ret;

	args->pitch = DIV_ROUND_UP(args->width * args->bpp, 8);
	args->size = args->pitch * args->height;

	mtk_gem = mtk_drm_gem_create(dev, args->size, false);
	अगर (IS_ERR(mtk_gem))
		वापस PTR_ERR(mtk_gem);

	/*
	 * allocate a id of idr table where the obj is रेजिस्टरed
	 * and handle has the id what user can see.
	 */
	ret = drm_gem_handle_create(file_priv, &mtk_gem->base, &args->handle);
	अगर (ret)
		जाओ err_handle_create;

	/* drop reference from allocate - handle holds it now. */
	drm_gem_object_put(&mtk_gem->base);

	वापस 0;

err_handle_create:
	mtk_drm_gem_मुक्त_object(&mtk_gem->base);
	वापस ret;
पूर्ण

अटल पूर्णांक mtk_drm_gem_object_mmap(काष्ठा drm_gem_object *obj,
				   काष्ठा vm_area_काष्ठा *vma)

अणु
	पूर्णांक ret;
	काष्ठा mtk_drm_gem_obj *mtk_gem = to_mtk_gem_obj(obj);
	काष्ठा mtk_drm_निजी *priv = obj->dev->dev_निजी;

	/*
	 * dma_alloc_attrs() allocated a काष्ठा page table क्रम mtk_gem, so clear
	 * VM_PFNMAP flag that was set by drm_gem_mmap_obj()/drm_gem_mmap().
	 */
	vma->vm_flags &= ~VM_PFNMAP;

	ret = dma_mmap_attrs(priv->dma_dev, vma, mtk_gem->cookie,
			     mtk_gem->dma_addr, obj->size, mtk_gem->dma_attrs);
	अगर (ret)
		drm_gem_vm_बंद(vma);

	वापस ret;
पूर्ण

पूर्णांक mtk_drm_gem_mmap_buf(काष्ठा drm_gem_object *obj, काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक ret;

	ret = drm_gem_mmap_obj(obj, obj->size, vma);
	अगर (ret)
		वापस ret;

	वापस mtk_drm_gem_object_mmap(obj, vma);
पूर्ण

पूर्णांक mtk_drm_gem_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret;

	ret = drm_gem_mmap(filp, vma);
	अगर (ret)
		वापस ret;

	obj = vma->vm_निजी_data;

	/*
	 * Set vm_pgoff (used as a fake buffer offset by DRM) to 0 and map the
	 * whole buffer from the start.
	 */
	vma->vm_pgoff = 0;

	वापस mtk_drm_gem_object_mmap(obj, vma);
पूर्ण

/*
 * Allocate a sg_table क्रम this GEM object.
 * Note: Both the table's contents, and the sg_table itself must be मुक्तd by
 *       the caller.
 * Returns a poपूर्णांकer to the newly allocated sg_table, or an ERR_PTR() error.
 */
काष्ठा sg_table *mtk_gem_prime_get_sg_table(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा mtk_drm_gem_obj *mtk_gem = to_mtk_gem_obj(obj);
	काष्ठा mtk_drm_निजी *priv = obj->dev->dev_निजी;
	काष्ठा sg_table *sgt;
	पूर्णांक ret;

	sgt = kzalloc(माप(*sgt), GFP_KERNEL);
	अगर (!sgt)
		वापस ERR_PTR(-ENOMEM);

	ret = dma_get_sgtable_attrs(priv->dma_dev, sgt, mtk_gem->cookie,
				    mtk_gem->dma_addr, obj->size,
				    mtk_gem->dma_attrs);
	अगर (ret) अणु
		DRM_ERROR("failed to allocate sgt, %d\n", ret);
		kमुक्त(sgt);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस sgt;
पूर्ण

काष्ठा drm_gem_object *mtk_gem_prime_import_sg_table(काष्ठा drm_device *dev,
			काष्ठा dma_buf_attachment *attach, काष्ठा sg_table *sg)
अणु
	काष्ठा mtk_drm_gem_obj *mtk_gem;

	/* check अगर the entries in the sg_table are contiguous */
	अगर (drm_prime_get_contiguous_size(sg) < attach->dmabuf->size) अणु
		DRM_ERROR("sg_table is not contiguous");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	mtk_gem = mtk_drm_gem_init(dev, attach->dmabuf->size);
	अगर (IS_ERR(mtk_gem))
		वापस ERR_CAST(mtk_gem);

	mtk_gem->dma_addr = sg_dma_address(sg->sgl);
	mtk_gem->sg = sg;

	वापस &mtk_gem->base;
पूर्ण

पूर्णांक mtk_drm_gem_prime_vmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map)
अणु
	काष्ठा mtk_drm_gem_obj *mtk_gem = to_mtk_gem_obj(obj);
	काष्ठा sg_table *sgt = शून्य;
	अचिन्हित पूर्णांक npages;

	अगर (mtk_gem->kvaddr)
		जाओ out;

	sgt = mtk_gem_prime_get_sg_table(obj);
	अगर (IS_ERR(sgt))
		वापस PTR_ERR(sgt);

	npages = obj->size >> PAGE_SHIFT;
	mtk_gem->pages = kसुस्मृति(npages, माप(*mtk_gem->pages), GFP_KERNEL);
	अगर (!mtk_gem->pages) अणु
		kमुक्त(sgt);
		वापस -ENOMEM;
	पूर्ण

	drm_prime_sg_to_page_array(sgt, mtk_gem->pages, npages);

	mtk_gem->kvaddr = vmap(mtk_gem->pages, npages, VM_MAP,
			       pgprot_ग_लिखोcombine(PAGE_KERNEL));

out:
	kमुक्त(sgt);
	dma_buf_map_set_vaddr(map, mtk_gem->kvaddr);

	वापस 0;
पूर्ण

व्योम mtk_drm_gem_prime_vunmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map)
अणु
	काष्ठा mtk_drm_gem_obj *mtk_gem = to_mtk_gem_obj(obj);
	व्योम *vaddr = map->vaddr;

	अगर (!mtk_gem->pages)
		वापस;

	vunmap(vaddr);
	mtk_gem->kvaddr = 0;
	kमुक्त(mtk_gem->pages);
पूर्ण
