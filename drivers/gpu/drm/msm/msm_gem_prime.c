<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/dma-buf.h>

#समावेश <drm/drm_prime.h>

#समावेश "msm_drv.h"
#समावेश "msm_gem.h"

काष्ठा sg_table *msm_gem_prime_get_sg_table(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा msm_gem_object *msm_obj = to_msm_bo(obj);
	पूर्णांक npages = obj->size >> PAGE_SHIFT;

	अगर (WARN_ON(!msm_obj->pages))  /* should have alपढ़ोy pinned! */
		वापस शून्य;

	वापस drm_prime_pages_to_sg(obj->dev, msm_obj->pages, npages);
पूर्ण

पूर्णांक msm_gem_prime_vmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map)
अणु
	व्योम *vaddr;

	vaddr = msm_gem_get_vaddr(obj);
	अगर (IS_ERR(vaddr))
		वापस PTR_ERR(vaddr);
	dma_buf_map_set_vaddr(map, vaddr);

	वापस 0;
पूर्ण

व्योम msm_gem_prime_vunmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map)
अणु
	msm_gem_put_vaddr(obj);
पूर्ण

पूर्णांक msm_gem_prime_mmap(काष्ठा drm_gem_object *obj, काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक ret;

	ret = drm_gem_mmap_obj(obj, obj->size, vma);
	अगर (ret < 0)
		वापस ret;

	वापस msm_gem_mmap_obj(vma->vm_निजी_data, vma);
पूर्ण

काष्ठा drm_gem_object *msm_gem_prime_import_sg_table(काष्ठा drm_device *dev,
		काष्ठा dma_buf_attachment *attach, काष्ठा sg_table *sg)
अणु
	वापस msm_gem_import(dev, attach->dmabuf, sg);
पूर्ण

पूर्णांक msm_gem_prime_pin(काष्ठा drm_gem_object *obj)
अणु
	अगर (!obj->import_attach)
		msm_gem_get_pages(obj);
	वापस 0;
पूर्ण

व्योम msm_gem_prime_unpin(काष्ठा drm_gem_object *obj)
अणु
	अगर (!obj->import_attach)
		msm_gem_put_pages(obj);
पूर्ण
