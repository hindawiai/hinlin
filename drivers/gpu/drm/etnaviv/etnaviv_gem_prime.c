<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014-2018 Etnaviv Project
 */

#समावेश <drm/drm_prime.h>
#समावेश <linux/dma-buf.h>

#समावेश "etnaviv_drv.h"
#समावेश "etnaviv_gem.h"

अटल काष्ठा lock_class_key etnaviv_prime_lock_class;

काष्ठा sg_table *etnaviv_gem_prime_get_sg_table(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);
	पूर्णांक npages = obj->size >> PAGE_SHIFT;

	अगर (WARN_ON(!etnaviv_obj->pages))  /* should have alपढ़ोy pinned! */
		वापस ERR_PTR(-EINVAL);

	वापस drm_prime_pages_to_sg(obj->dev, etnaviv_obj->pages, npages);
पूर्ण

पूर्णांक etnaviv_gem_prime_vmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map)
अणु
	व्योम *vaddr;

	vaddr = etnaviv_gem_vmap(obj);
	अगर (!vaddr)
		वापस -ENOMEM;
	dma_buf_map_set_vaddr(map, vaddr);

	वापस 0;
पूर्ण

पूर्णांक etnaviv_gem_prime_mmap(काष्ठा drm_gem_object *obj,
			   काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);
	पूर्णांक ret;

	ret = drm_gem_mmap_obj(obj, obj->size, vma);
	अगर (ret < 0)
		वापस ret;

	वापस etnaviv_obj->ops->mmap(etnaviv_obj, vma);
पूर्ण

पूर्णांक etnaviv_gem_prime_pin(काष्ठा drm_gem_object *obj)
अणु
	अगर (!obj->import_attach) अणु
		काष्ठा etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);

		mutex_lock(&etnaviv_obj->lock);
		etnaviv_gem_get_pages(etnaviv_obj);
		mutex_unlock(&etnaviv_obj->lock);
	पूर्ण
	वापस 0;
पूर्ण

व्योम etnaviv_gem_prime_unpin(काष्ठा drm_gem_object *obj)
अणु
	अगर (!obj->import_attach) अणु
		काष्ठा etnaviv_gem_object *etnaviv_obj = to_etnaviv_bo(obj);

		mutex_lock(&etnaviv_obj->lock);
		etnaviv_gem_put_pages(to_etnaviv_bo(obj));
		mutex_unlock(&etnaviv_obj->lock);
	पूर्ण
पूर्ण

अटल व्योम etnaviv_gem_prime_release(काष्ठा etnaviv_gem_object *etnaviv_obj)
अणु
	काष्ठा dma_buf_map map = DMA_BUF_MAP_INIT_VADDR(etnaviv_obj->vaddr);

	अगर (etnaviv_obj->vaddr)
		dma_buf_vunmap(etnaviv_obj->base.import_attach->dmabuf, &map);

	/* Don't drop the pages क्रम imported dmabuf, as they are not
	 * ours, just मुक्त the array we allocated:
	 */
	अगर (etnaviv_obj->pages)
		kvमुक्त(etnaviv_obj->pages);

	drm_prime_gem_destroy(&etnaviv_obj->base, etnaviv_obj->sgt);
पूर्ण

अटल व्योम *etnaviv_gem_prime_vmap_impl(काष्ठा etnaviv_gem_object *etnaviv_obj)
अणु
	काष्ठा dma_buf_map map;
	पूर्णांक ret;

	lockdep_निश्चित_held(&etnaviv_obj->lock);

	ret = dma_buf_vmap(etnaviv_obj->base.import_attach->dmabuf, &map);
	अगर (ret)
		वापस शून्य;
	वापस map.vaddr;
पूर्ण

अटल पूर्णांक etnaviv_gem_prime_mmap_obj(काष्ठा etnaviv_gem_object *etnaviv_obj,
		काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस dma_buf_mmap(etnaviv_obj->base.dma_buf, vma, 0);
पूर्ण

अटल स्थिर काष्ठा etnaviv_gem_ops etnaviv_gem_prime_ops = अणु
	/* .get_pages should never be called */
	.release = etnaviv_gem_prime_release,
	.vmap = etnaviv_gem_prime_vmap_impl,
	.mmap = etnaviv_gem_prime_mmap_obj,
पूर्ण;

काष्ठा drm_gem_object *etnaviv_gem_prime_import_sg_table(काष्ठा drm_device *dev,
	काष्ठा dma_buf_attachment *attach, काष्ठा sg_table *sgt)
अणु
	काष्ठा etnaviv_gem_object *etnaviv_obj;
	माप_प्रकार size = PAGE_ALIGN(attach->dmabuf->size);
	पूर्णांक ret, npages;

	ret = etnaviv_gem_new_निजी(dev, size, ETNA_BO_WC,
				      &etnaviv_gem_prime_ops, &etnaviv_obj);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	lockdep_set_class(&etnaviv_obj->lock, &etnaviv_prime_lock_class);

	npages = size / PAGE_SIZE;

	etnaviv_obj->sgt = sgt;
	etnaviv_obj->pages = kvदो_स्मृति_array(npages, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!etnaviv_obj->pages) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	ret = drm_prime_sg_to_page_array(sgt, etnaviv_obj->pages, npages);
	अगर (ret)
		जाओ fail;

	etnaviv_gem_obj_add(dev, &etnaviv_obj->base);

	वापस &etnaviv_obj->base;

fail:
	drm_gem_object_put(&etnaviv_obj->base);

	वापस ERR_PTR(ret);
पूर्ण
