<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT

/*
 *  Xen para-भव DRM device
 *
 * Copyright (C) 2016-2018 EPAM Systems Inc.
 *
 * Author: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 */

#समावेश <linux/dma-buf.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/shmem_fs.h>

#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_prime.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश <xen/balloon.h>
#समावेश <xen/xen.h>

#समावेश "xen_drm_front.h"
#समावेश "xen_drm_front_gem.h"

काष्ठा xen_gem_object अणु
	काष्ठा drm_gem_object base;

	माप_प्रकार num_pages;
	काष्ठा page **pages;

	/* set क्रम buffers allocated by the backend */
	bool be_alloc;

	/* this is क्रम imported PRIME buffer */
	काष्ठा sg_table *sgt_imported;
पूर्ण;

अटल अंतरभूत काष्ठा xen_gem_object *
to_xen_gem_obj(काष्ठा drm_gem_object *gem_obj)
अणु
	वापस container_of(gem_obj, काष्ठा xen_gem_object, base);
पूर्ण

अटल पूर्णांक gem_alloc_pages_array(काष्ठा xen_gem_object *xen_obj,
				 माप_प्रकार buf_size)
अणु
	xen_obj->num_pages = DIV_ROUND_UP(buf_size, PAGE_SIZE);
	xen_obj->pages = kvदो_स्मृति_array(xen_obj->num_pages,
					माप(काष्ठा page *), GFP_KERNEL);
	वापस !xen_obj->pages ? -ENOMEM : 0;
पूर्ण

अटल व्योम gem_मुक्त_pages_array(काष्ठा xen_gem_object *xen_obj)
अणु
	kvमुक्त(xen_obj->pages);
	xen_obj->pages = शून्य;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा xen_drm_drv_vm_ops = अणु
	.खोलो           = drm_gem_vm_खोलो,
	.बंद          = drm_gem_vm_बंद,
पूर्ण;

अटल स्थिर काष्ठा drm_gem_object_funcs xen_drm_front_gem_object_funcs = अणु
	.मुक्त = xen_drm_front_gem_object_मुक्त,
	.get_sg_table = xen_drm_front_gem_get_sg_table,
	.vmap = xen_drm_front_gem_prime_vmap,
	.vunmap = xen_drm_front_gem_prime_vunmap,
	.vm_ops = &xen_drm_drv_vm_ops,
पूर्ण;

अटल काष्ठा xen_gem_object *gem_create_obj(काष्ठा drm_device *dev,
					     माप_प्रकार size)
अणु
	काष्ठा xen_gem_object *xen_obj;
	पूर्णांक ret;

	xen_obj = kzalloc(माप(*xen_obj), GFP_KERNEL);
	अगर (!xen_obj)
		वापस ERR_PTR(-ENOMEM);

	xen_obj->base.funcs = &xen_drm_front_gem_object_funcs;

	ret = drm_gem_object_init(dev, &xen_obj->base, size);
	अगर (ret < 0) अणु
		kमुक्त(xen_obj);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस xen_obj;
पूर्ण

अटल काष्ठा xen_gem_object *gem_create(काष्ठा drm_device *dev, माप_प्रकार size)
अणु
	काष्ठा xen_drm_front_drm_info *drm_info = dev->dev_निजी;
	काष्ठा xen_gem_object *xen_obj;
	पूर्णांक ret;

	size = round_up(size, PAGE_SIZE);
	xen_obj = gem_create_obj(dev, size);
	अगर (IS_ERR(xen_obj))
		वापस xen_obj;

	अगर (drm_info->front_info->cfg.be_alloc) अणु
		/*
		 * backend will allocate space क्रम this buffer, so
		 * only allocate array of poपूर्णांकers to pages
		 */
		ret = gem_alloc_pages_array(xen_obj, size);
		अगर (ret < 0)
			जाओ fail;

		/*
		 * allocate ballooned pages which will be used to map
		 * grant references provided by the backend
		 */
		ret = xen_alloc_unpopulated_pages(xen_obj->num_pages,
					          xen_obj->pages);
		अगर (ret < 0) अणु
			DRM_ERROR("Cannot allocate %zu ballooned pages: %d\n",
				  xen_obj->num_pages, ret);
			gem_मुक्त_pages_array(xen_obj);
			जाओ fail;
		पूर्ण

		xen_obj->be_alloc = true;
		वापस xen_obj;
	पूर्ण
	/*
	 * need to allocate backing pages now, so we can share those
	 * with the backend
	 */
	xen_obj->num_pages = DIV_ROUND_UP(size, PAGE_SIZE);
	xen_obj->pages = drm_gem_get_pages(&xen_obj->base);
	अगर (IS_ERR(xen_obj->pages)) अणु
		ret = PTR_ERR(xen_obj->pages);
		xen_obj->pages = शून्य;
		जाओ fail;
	पूर्ण

	वापस xen_obj;

fail:
	DRM_ERROR("Failed to allocate buffer with size %zu\n", size);
	वापस ERR_PTR(ret);
पूर्ण

काष्ठा drm_gem_object *xen_drm_front_gem_create(काष्ठा drm_device *dev,
						माप_प्रकार size)
अणु
	काष्ठा xen_gem_object *xen_obj;

	xen_obj = gem_create(dev, size);
	अगर (IS_ERR(xen_obj))
		वापस ERR_CAST(xen_obj);

	वापस &xen_obj->base;
पूर्ण

व्योम xen_drm_front_gem_मुक्त_object_unlocked(काष्ठा drm_gem_object *gem_obj)
अणु
	काष्ठा xen_gem_object *xen_obj = to_xen_gem_obj(gem_obj);

	अगर (xen_obj->base.import_attach) अणु
		drm_prime_gem_destroy(&xen_obj->base, xen_obj->sgt_imported);
		gem_मुक्त_pages_array(xen_obj);
	पूर्ण अन्यथा अणु
		अगर (xen_obj->pages) अणु
			अगर (xen_obj->be_alloc) अणु
				xen_मुक्त_unpopulated_pages(xen_obj->num_pages,
							   xen_obj->pages);
				gem_मुक्त_pages_array(xen_obj);
			पूर्ण अन्यथा अणु
				drm_gem_put_pages(&xen_obj->base,
						  xen_obj->pages, true, false);
			पूर्ण
		पूर्ण
	पूर्ण
	drm_gem_object_release(gem_obj);
	kमुक्त(xen_obj);
पूर्ण

काष्ठा page **xen_drm_front_gem_get_pages(काष्ठा drm_gem_object *gem_obj)
अणु
	काष्ठा xen_gem_object *xen_obj = to_xen_gem_obj(gem_obj);

	वापस xen_obj->pages;
पूर्ण

काष्ठा sg_table *xen_drm_front_gem_get_sg_table(काष्ठा drm_gem_object *gem_obj)
अणु
	काष्ठा xen_gem_object *xen_obj = to_xen_gem_obj(gem_obj);

	अगर (!xen_obj->pages)
		वापस ERR_PTR(-ENOMEM);

	वापस drm_prime_pages_to_sg(gem_obj->dev,
				     xen_obj->pages, xen_obj->num_pages);
पूर्ण

काष्ठा drm_gem_object *
xen_drm_front_gem_import_sg_table(काष्ठा drm_device *dev,
				  काष्ठा dma_buf_attachment *attach,
				  काष्ठा sg_table *sgt)
अणु
	काष्ठा xen_drm_front_drm_info *drm_info = dev->dev_निजी;
	काष्ठा xen_gem_object *xen_obj;
	माप_प्रकार size;
	पूर्णांक ret;

	size = attach->dmabuf->size;
	xen_obj = gem_create_obj(dev, size);
	अगर (IS_ERR(xen_obj))
		वापस ERR_CAST(xen_obj);

	ret = gem_alloc_pages_array(xen_obj, size);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	xen_obj->sgt_imported = sgt;

	ret = drm_prime_sg_to_page_array(sgt, xen_obj->pages,
					 xen_obj->num_pages);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	ret = xen_drm_front_dbuf_create(drm_info->front_info,
					xen_drm_front_dbuf_to_cookie(&xen_obj->base),
					0, 0, 0, size, sgt->sgl->offset,
					xen_obj->pages);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	DRM_DEBUG("Imported buffer of size %zu with nents %u\n",
		  size, sgt->orig_nents);

	वापस &xen_obj->base;
पूर्ण

अटल पूर्णांक gem_mmap_obj(काष्ठा xen_gem_object *xen_obj,
			काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक ret;

	/*
	 * clear the VM_PFNMAP flag that was set by drm_gem_mmap(), and set the
	 * vm_pgoff (used as a fake buffer offset by DRM) to 0 as we want to map
	 * the whole buffer.
	 */
	vma->vm_flags &= ~VM_PFNMAP;
	vma->vm_flags |= VM_MIXEDMAP;
	vma->vm_pgoff = 0;
	/*
	 * According to Xen on ARM ABI (xen/include/खुला/arch-arm.h):
	 * all memory which is shared with other entities in the प्रणाली
	 * (including the hypervisor and other guests) must reside in memory
	 * which is mapped as Normal Inner Write-Back Outer Write-Back
	 * Inner-Shareable.
	 */
	vma->vm_page_prot = vm_get_page_prot(vma->vm_flags);

	/*
	 * vm_operations_काष्ठा.fault handler will be called अगर CPU access
	 * to VM is here. For GPUs this isn't the हाल, because CPU
	 * करोesn't touch the memory. Insert pages now, so both CPU and GPU are
	 * happy.
	 * FIXME: as we insert all the pages now then no .fault handler must
	 * be called, so करोn't provide one
	 */
	ret = vm_map_pages(vma, xen_obj->pages, xen_obj->num_pages);
	अगर (ret < 0)
		DRM_ERROR("Failed to map pages into vma: %d\n", ret);

	वापस ret;
पूर्ण

पूर्णांक xen_drm_front_gem_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा xen_gem_object *xen_obj;
	काष्ठा drm_gem_object *gem_obj;
	पूर्णांक ret;

	ret = drm_gem_mmap(filp, vma);
	अगर (ret < 0)
		वापस ret;

	gem_obj = vma->vm_निजी_data;
	xen_obj = to_xen_gem_obj(gem_obj);
	वापस gem_mmap_obj(xen_obj, vma);
पूर्ण

पूर्णांक xen_drm_front_gem_prime_vmap(काष्ठा drm_gem_object *gem_obj, काष्ठा dma_buf_map *map)
अणु
	काष्ठा xen_gem_object *xen_obj = to_xen_gem_obj(gem_obj);
	व्योम *vaddr;

	अगर (!xen_obj->pages)
		वापस -ENOMEM;

	/* Please see comment in gem_mmap_obj on mapping and attributes. */
	vaddr = vmap(xen_obj->pages, xen_obj->num_pages,
		     VM_MAP, PAGE_KERNEL);
	अगर (!vaddr)
		वापस -ENOMEM;
	dma_buf_map_set_vaddr(map, vaddr);

	वापस 0;
पूर्ण

व्योम xen_drm_front_gem_prime_vunmap(काष्ठा drm_gem_object *gem_obj,
				    काष्ठा dma_buf_map *map)
अणु
	vunmap(map->vaddr);
पूर्ण

पूर्णांक xen_drm_front_gem_prime_mmap(काष्ठा drm_gem_object *gem_obj,
				 काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा xen_gem_object *xen_obj;
	पूर्णांक ret;

	ret = drm_gem_mmap_obj(gem_obj, gem_obj->size, vma);
	अगर (ret < 0)
		वापस ret;

	xen_obj = to_xen_gem_obj(gem_obj);
	वापस gem_mmap_obj(xen_obj, vma);
पूर्ण
