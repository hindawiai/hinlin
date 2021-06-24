<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2018 Noralf Trथचnnes
 */

#समावेश <linux/dma-buf.h>
#समावेश <linux/export.h>
#समावेश <linux/mutex.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_gem_shmem_helper.h>
#समावेश <drm/drm_prime.h>
#समावेश <drm/drm_prपूर्णांक.h>

/**
 * DOC: overview
 *
 * This library provides helpers क्रम GEM objects backed by shmem buffers
 * allocated using anonymous pageable memory.
 */

अटल स्थिर काष्ठा drm_gem_object_funcs drm_gem_shmem_funcs = अणु
	.मुक्त = drm_gem_shmem_मुक्त_object,
	.prपूर्णांक_info = drm_gem_shmem_prपूर्णांक_info,
	.pin = drm_gem_shmem_pin,
	.unpin = drm_gem_shmem_unpin,
	.get_sg_table = drm_gem_shmem_get_sg_table,
	.vmap = drm_gem_shmem_vmap,
	.vunmap = drm_gem_shmem_vunmap,
	.mmap = drm_gem_shmem_mmap,
पूर्ण;

अटल काष्ठा drm_gem_shmem_object *
__drm_gem_shmem_create(काष्ठा drm_device *dev, माप_प्रकार size, bool निजी)
अणु
	काष्ठा drm_gem_shmem_object *shmem;
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret = 0;

	size = PAGE_ALIGN(size);

	अगर (dev->driver->gem_create_object)
		obj = dev->driver->gem_create_object(dev, size);
	अन्यथा
		obj = kzalloc(माप(*shmem), GFP_KERNEL);
	अगर (!obj)
		वापस ERR_PTR(-ENOMEM);

	shmem = to_drm_gem_shmem_obj(obj);

	अगर (!obj->funcs)
		obj->funcs = &drm_gem_shmem_funcs;

	अगर (निजी) अणु
		drm_gem_निजी_object_init(dev, obj, size);
		shmem->map_wc = false; /* dma-buf mappings use always ग_लिखोcombine */
	पूर्ण अन्यथा अणु
		ret = drm_gem_object_init(dev, obj, size);
	पूर्ण
	अगर (ret)
		जाओ err_मुक्त;

	ret = drm_gem_create_mmap_offset(obj);
	अगर (ret)
		जाओ err_release;

	mutex_init(&shmem->pages_lock);
	mutex_init(&shmem->vmap_lock);
	INIT_LIST_HEAD(&shmem->madv_list);

	अगर (!निजी) अणु
		/*
		 * Our buffers are kept pinned, so allocating them
		 * from the MOVABLE zone is a really bad idea, and
		 * conflicts with CMA. See comments above new_inode()
		 * why this is required _and_ expected अगर you're
		 * going to pin these pages.
		 */
		mapping_set_gfp_mask(obj->filp->f_mapping, GFP_HIGHUSER |
				     __GFP_RETRY_MAYFAIL | __GFP_NOWARN);
	पूर्ण

	वापस shmem;

err_release:
	drm_gem_object_release(obj);
err_मुक्त:
	kमुक्त(obj);

	वापस ERR_PTR(ret);
पूर्ण
/**
 * drm_gem_shmem_create - Allocate an object with the given size
 * @dev: DRM device
 * @size: Size of the object to allocate
 *
 * This function creates a shmem GEM object.
 *
 * Returns:
 * A काष्ठा drm_gem_shmem_object * on success or an ERR_PTR()-encoded negative
 * error code on failure.
 */
काष्ठा drm_gem_shmem_object *drm_gem_shmem_create(काष्ठा drm_device *dev, माप_प्रकार size)
अणु
	वापस __drm_gem_shmem_create(dev, size, false);
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_shmem_create);

/**
 * drm_gem_shmem_मुक्त_object - Free resources associated with a shmem GEM object
 * @obj: GEM object to मुक्त
 *
 * This function cleans up the GEM object state and मुक्तs the memory used to
 * store the object itself. It should be used to implement
 * &drm_gem_object_funcs.मुक्त.
 */
व्योम drm_gem_shmem_मुक्त_object(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);

	WARN_ON(shmem->vmap_use_count);

	अगर (obj->import_attach) अणु
		drm_prime_gem_destroy(obj, shmem->sgt);
	पूर्ण अन्यथा अणु
		अगर (shmem->sgt) अणु
			dma_unmap_sgtable(obj->dev->dev, shmem->sgt,
					  DMA_BIसूचीECTIONAL, 0);
			sg_मुक्त_table(shmem->sgt);
			kमुक्त(shmem->sgt);
		पूर्ण
		अगर (shmem->pages)
			drm_gem_shmem_put_pages(shmem);
	पूर्ण

	WARN_ON(shmem->pages_use_count);

	drm_gem_object_release(obj);
	mutex_destroy(&shmem->pages_lock);
	mutex_destroy(&shmem->vmap_lock);
	kमुक्त(shmem);
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_shmem_मुक्त_object);

अटल पूर्णांक drm_gem_shmem_get_pages_locked(काष्ठा drm_gem_shmem_object *shmem)
अणु
	काष्ठा drm_gem_object *obj = &shmem->base;
	काष्ठा page **pages;

	अगर (shmem->pages_use_count++ > 0)
		वापस 0;

	pages = drm_gem_get_pages(obj);
	अगर (IS_ERR(pages)) अणु
		DRM_DEBUG_KMS("Failed to get pages (%ld)\n", PTR_ERR(pages));
		shmem->pages_use_count = 0;
		वापस PTR_ERR(pages);
	पूर्ण

	shmem->pages = pages;

	वापस 0;
पूर्ण

/*
 * drm_gem_shmem_get_pages - Allocate backing pages क्रम a shmem GEM object
 * @shmem: shmem GEM object
 *
 * This function makes sure that backing pages exists क्रम the shmem GEM object
 * and increases the use count.
 *
 * Returns:
 * 0 on success or a negative error code on failure.
 */
पूर्णांक drm_gem_shmem_get_pages(काष्ठा drm_gem_shmem_object *shmem)
अणु
	पूर्णांक ret;

	WARN_ON(shmem->base.import_attach);

	ret = mutex_lock_पूर्णांकerruptible(&shmem->pages_lock);
	अगर (ret)
		वापस ret;
	ret = drm_gem_shmem_get_pages_locked(shmem);
	mutex_unlock(&shmem->pages_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_gem_shmem_get_pages);

अटल व्योम drm_gem_shmem_put_pages_locked(काष्ठा drm_gem_shmem_object *shmem)
अणु
	काष्ठा drm_gem_object *obj = &shmem->base;

	अगर (WARN_ON_ONCE(!shmem->pages_use_count))
		वापस;

	अगर (--shmem->pages_use_count > 0)
		वापस;

	drm_gem_put_pages(obj, shmem->pages,
			  shmem->pages_mark_dirty_on_put,
			  shmem->pages_mark_accessed_on_put);
	shmem->pages = शून्य;
पूर्ण

/*
 * drm_gem_shmem_put_pages - Decrease use count on the backing pages क्रम a shmem GEM object
 * @shmem: shmem GEM object
 *
 * This function decreases the use count and माला_दो the backing pages when use drops to zero.
 */
व्योम drm_gem_shmem_put_pages(काष्ठा drm_gem_shmem_object *shmem)
अणु
	mutex_lock(&shmem->pages_lock);
	drm_gem_shmem_put_pages_locked(shmem);
	mutex_unlock(&shmem->pages_lock);
पूर्ण
EXPORT_SYMBOL(drm_gem_shmem_put_pages);

/**
 * drm_gem_shmem_pin - Pin backing pages क्रम a shmem GEM object
 * @obj: GEM object
 *
 * This function makes sure the backing pages are pinned in memory जबतक the
 * buffer is exported. It should only be used to implement
 * &drm_gem_object_funcs.pin.
 *
 * Returns:
 * 0 on success or a negative error code on failure.
 */
पूर्णांक drm_gem_shmem_pin(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);

	WARN_ON(shmem->base.import_attach);

	वापस drm_gem_shmem_get_pages(shmem);
पूर्ण
EXPORT_SYMBOL(drm_gem_shmem_pin);

/**
 * drm_gem_shmem_unpin - Unpin backing pages क्रम a shmem GEM object
 * @obj: GEM object
 *
 * This function हटाओs the requirement that the backing pages are pinned in
 * memory. It should only be used to implement &drm_gem_object_funcs.unpin.
 */
व्योम drm_gem_shmem_unpin(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);

	WARN_ON(shmem->base.import_attach);

	drm_gem_shmem_put_pages(shmem);
पूर्ण
EXPORT_SYMBOL(drm_gem_shmem_unpin);

अटल पूर्णांक drm_gem_shmem_vmap_locked(काष्ठा drm_gem_shmem_object *shmem, काष्ठा dma_buf_map *map)
अणु
	काष्ठा drm_gem_object *obj = &shmem->base;
	पूर्णांक ret = 0;

	अगर (shmem->vmap_use_count++ > 0) अणु
		dma_buf_map_set_vaddr(map, shmem->vaddr);
		वापस 0;
	पूर्ण

	अगर (obj->import_attach) अणु
		ret = dma_buf_vmap(obj->import_attach->dmabuf, map);
		अगर (!ret) अणु
			अगर (WARN_ON(map->is_iomem)) अणु
				ret = -EIO;
				जाओ err_put_pages;
			पूर्ण
			shmem->vaddr = map->vaddr;
		पूर्ण
	पूर्ण अन्यथा अणु
		pgprot_t prot = PAGE_KERNEL;

		ret = drm_gem_shmem_get_pages(shmem);
		अगर (ret)
			जाओ err_zero_use;

		अगर (shmem->map_wc)
			prot = pgprot_ग_लिखोcombine(prot);
		shmem->vaddr = vmap(shmem->pages, obj->size >> PAGE_SHIFT,
				    VM_MAP, prot);
		अगर (!shmem->vaddr)
			ret = -ENOMEM;
		अन्यथा
			dma_buf_map_set_vaddr(map, shmem->vaddr);
	पूर्ण

	अगर (ret) अणु
		DRM_DEBUG_KMS("Failed to vmap pages, error %d\n", ret);
		जाओ err_put_pages;
	पूर्ण

	वापस 0;

err_put_pages:
	अगर (!obj->import_attach)
		drm_gem_shmem_put_pages(shmem);
err_zero_use:
	shmem->vmap_use_count = 0;

	वापस ret;
पूर्ण

/*
 * drm_gem_shmem_vmap - Create a भव mapping क्रम a shmem GEM object
 * @shmem: shmem GEM object
 * @map: Returns the kernel भव address of the SHMEM GEM object's backing
 *       store.
 *
 * This function makes sure that a contiguous kernel भव address mapping
 * exists क्रम the buffer backing the shmem GEM object.
 *
 * This function can be used to implement &drm_gem_object_funcs.vmap. But it can
 * also be called by drivers directly, in which हाल it will hide the
 * dअगरferences between dma-buf imported and natively allocated objects.
 *
 * Acquired mappings should be cleaned up by calling drm_gem_shmem_vunmap().
 *
 * Returns:
 * 0 on success or a negative error code on failure.
 */
पूर्णांक drm_gem_shmem_vmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map)
अणु
	काष्ठा drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);
	पूर्णांक ret;

	ret = mutex_lock_पूर्णांकerruptible(&shmem->vmap_lock);
	अगर (ret)
		वापस ret;
	ret = drm_gem_shmem_vmap_locked(shmem, map);
	mutex_unlock(&shmem->vmap_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_gem_shmem_vmap);

अटल व्योम drm_gem_shmem_vunmap_locked(काष्ठा drm_gem_shmem_object *shmem,
					काष्ठा dma_buf_map *map)
अणु
	काष्ठा drm_gem_object *obj = &shmem->base;

	अगर (WARN_ON_ONCE(!shmem->vmap_use_count))
		वापस;

	अगर (--shmem->vmap_use_count > 0)
		वापस;

	अगर (obj->import_attach) अणु
		dma_buf_vunmap(obj->import_attach->dmabuf, map);
	पूर्ण अन्यथा अणु
		vunmap(shmem->vaddr);
		drm_gem_shmem_put_pages(shmem);
	पूर्ण

	shmem->vaddr = शून्य;
पूर्ण

/*
 * drm_gem_shmem_vunmap - Unmap a भव mapping fo a shmem GEM object
 * @shmem: shmem GEM object
 * @map: Kernel भव address where the SHMEM GEM object was mapped
 *
 * This function cleans up a kernel भव address mapping acquired by
 * drm_gem_shmem_vmap(). The mapping is only हटाओd when the use count drops to
 * zero.
 *
 * This function can be used to implement &drm_gem_object_funcs.vmap. But it can
 * also be called by drivers directly, in which हाल it will hide the
 * dअगरferences between dma-buf imported and natively allocated objects.
 */
व्योम drm_gem_shmem_vunmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map)
अणु
	काष्ठा drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);

	mutex_lock(&shmem->vmap_lock);
	drm_gem_shmem_vunmap_locked(shmem, map);
	mutex_unlock(&shmem->vmap_lock);
पूर्ण
EXPORT_SYMBOL(drm_gem_shmem_vunmap);

काष्ठा drm_gem_shmem_object *
drm_gem_shmem_create_with_handle(काष्ठा drm_file *file_priv,
				 काष्ठा drm_device *dev, माप_प्रकार size,
				 uपूर्णांक32_t *handle)
अणु
	काष्ठा drm_gem_shmem_object *shmem;
	पूर्णांक ret;

	shmem = drm_gem_shmem_create(dev, size);
	अगर (IS_ERR(shmem))
		वापस shmem;

	/*
	 * Allocate an id of idr table where the obj is रेजिस्टरed
	 * and handle has the id what user can see.
	 */
	ret = drm_gem_handle_create(file_priv, &shmem->base, handle);
	/* drop reference from allocate - handle holds it now. */
	drm_gem_object_put(&shmem->base);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस shmem;
पूर्ण
EXPORT_SYMBOL(drm_gem_shmem_create_with_handle);

/* Update madvise status, वापसs true अगर not purged, अन्यथा
 * false or -त्रुटि_सं.
 */
पूर्णांक drm_gem_shmem_madvise(काष्ठा drm_gem_object *obj, पूर्णांक madv)
अणु
	काष्ठा drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);

	mutex_lock(&shmem->pages_lock);

	अगर (shmem->madv >= 0)
		shmem->madv = madv;

	madv = shmem->madv;

	mutex_unlock(&shmem->pages_lock);

	वापस (madv >= 0);
पूर्ण
EXPORT_SYMBOL(drm_gem_shmem_madvise);

व्योम drm_gem_shmem_purge_locked(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_device *dev = obj->dev;
	काष्ठा drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);

	WARN_ON(!drm_gem_shmem_is_purgeable(shmem));

	dma_unmap_sgtable(obj->dev->dev, shmem->sgt, DMA_BIसूचीECTIONAL, 0);
	sg_मुक्त_table(shmem->sgt);
	kमुक्त(shmem->sgt);
	shmem->sgt = शून्य;

	drm_gem_shmem_put_pages_locked(shmem);

	shmem->madv = -1;

	drm_vma_node_unmap(&obj->vma_node, dev->anon_inode->i_mapping);
	drm_gem_मुक्त_mmap_offset(obj);

	/* Our goal here is to वापस as much of the memory as
	 * is possible back to the प्रणाली as we are called from OOM.
	 * To करो this we must inकाष्ठा the shmfs to drop all of its
	 * backing pages, *now*.
	 */
	shmem_truncate_range(file_inode(obj->filp), 0, (loff_t)-1);

	invalidate_mapping_pages(file_inode(obj->filp)->i_mapping,
			0, (loff_t)-1);
पूर्ण
EXPORT_SYMBOL(drm_gem_shmem_purge_locked);

bool drm_gem_shmem_purge(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);

	अगर (!mutex_trylock(&shmem->pages_lock))
		वापस false;
	drm_gem_shmem_purge_locked(obj);
	mutex_unlock(&shmem->pages_lock);

	वापस true;
पूर्ण
EXPORT_SYMBOL(drm_gem_shmem_purge);

/**
 * drm_gem_shmem_dumb_create - Create a dumb shmem buffer object
 * @file: DRM file काष्ठाure to create the dumb buffer क्रम
 * @dev: DRM device
 * @args: IOCTL data
 *
 * This function computes the pitch of the dumb buffer and rounds it up to an
 * पूर्णांकeger number of bytes per pixel. Drivers क्रम hardware that करोesn't have
 * any additional restrictions on the pitch can directly use this function as
 * their &drm_driver.dumb_create callback.
 *
 * For hardware with additional restrictions, drivers can adjust the fields
 * set up by userspace beक्रमe calling पूर्णांकo this function.
 *
 * Returns:
 * 0 on success or a negative error code on failure.
 */
पूर्णांक drm_gem_shmem_dumb_create(काष्ठा drm_file *file, काष्ठा drm_device *dev,
			      काष्ठा drm_mode_create_dumb *args)
अणु
	u32 min_pitch = DIV_ROUND_UP(args->width * args->bpp, 8);
	काष्ठा drm_gem_shmem_object *shmem;

	अगर (!args->pitch || !args->size) अणु
		args->pitch = min_pitch;
		args->size = args->pitch * args->height;
	पूर्ण अन्यथा अणु
		/* ensure sane minimum values */
		अगर (args->pitch < min_pitch)
			args->pitch = min_pitch;
		अगर (args->size < args->pitch * args->height)
			args->size = args->pitch * args->height;
	पूर्ण

	shmem = drm_gem_shmem_create_with_handle(file, dev, args->size, &args->handle);

	वापस PTR_ERR_OR_ZERO(shmem);
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_shmem_dumb_create);

अटल vm_fault_t drm_gem_shmem_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा drm_gem_object *obj = vma->vm_निजी_data;
	काष्ठा drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);
	loff_t num_pages = obj->size >> PAGE_SHIFT;
	vm_fault_t ret;
	काष्ठा page *page;
	pgoff_t page_offset;

	/* We करोn't use vmf->pgoff since that has the fake offset */
	page_offset = (vmf->address - vma->vm_start) >> PAGE_SHIFT;

	mutex_lock(&shmem->pages_lock);

	अगर (page_offset >= num_pages ||
	    WARN_ON_ONCE(!shmem->pages) ||
	    shmem->madv < 0) अणु
		ret = VM_FAULT_SIGBUS;
	पूर्ण अन्यथा अणु
		page = shmem->pages[page_offset];

		ret = vmf_insert_page(vma, vmf->address, page);
	पूर्ण

	mutex_unlock(&shmem->pages_lock);

	वापस ret;
पूर्ण

अटल व्योम drm_gem_shmem_vm_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_gem_object *obj = vma->vm_निजी_data;
	काष्ठा drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);
	पूर्णांक ret;

	WARN_ON(shmem->base.import_attach);

	ret = drm_gem_shmem_get_pages(shmem);
	WARN_ON_ONCE(ret != 0);

	drm_gem_vm_खोलो(vma);
पूर्ण

अटल व्योम drm_gem_shmem_vm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_gem_object *obj = vma->vm_निजी_data;
	काष्ठा drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);

	drm_gem_shmem_put_pages(shmem);
	drm_gem_vm_बंद(vma);
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा drm_gem_shmem_vm_ops = अणु
	.fault = drm_gem_shmem_fault,
	.खोलो = drm_gem_shmem_vm_खोलो,
	.बंद = drm_gem_shmem_vm_बंद,
पूर्ण;

/**
 * drm_gem_shmem_mmap - Memory-map a shmem GEM object
 * @obj: gem object
 * @vma: VMA क्रम the area to be mapped
 *
 * This function implements an augmented version of the GEM DRM file mmap
 * operation क्रम shmem objects. Drivers which employ the shmem helpers should
 * use this function as their &drm_gem_object_funcs.mmap handler.
 *
 * Returns:
 * 0 on success or a negative error code on failure.
 */
पूर्णांक drm_gem_shmem_mmap(काष्ठा drm_gem_object *obj, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_gem_shmem_object *shmem;
	पूर्णांक ret;

	अगर (obj->import_attach) अणु
		/* Drop the reference drm_gem_mmap_obj() acquired.*/
		drm_gem_object_put(obj);
		vma->vm_निजी_data = शून्य;

		वापस dma_buf_mmap(obj->dma_buf, vma, 0);
	पूर्ण

	shmem = to_drm_gem_shmem_obj(obj);

	ret = drm_gem_shmem_get_pages(shmem);
	अगर (ret) अणु
		drm_gem_vm_बंद(vma);
		वापस ret;
	पूर्ण

	vma->vm_flags |= VM_MIXEDMAP | VM_DONTEXPAND;
	vma->vm_page_prot = vm_get_page_prot(vma->vm_flags);
	अगर (shmem->map_wc)
		vma->vm_page_prot = pgprot_ग_लिखोcombine(vma->vm_page_prot);
	vma->vm_ops = &drm_gem_shmem_vm_ops;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_shmem_mmap);

/**
 * drm_gem_shmem_prपूर्णांक_info() - Prपूर्णांक &drm_gem_shmem_object info क्रम debugfs
 * @p: DRM prपूर्णांकer
 * @indent: Tab indentation level
 * @obj: GEM object
 *
 * This implements the &drm_gem_object_funcs.info callback.
 */
व्योम drm_gem_shmem_prपूर्णांक_info(काष्ठा drm_prपूर्णांकer *p, अचिन्हित पूर्णांक indent,
			      स्थिर काष्ठा drm_gem_object *obj)
अणु
	स्थिर काष्ठा drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);

	drm_म_लिखो_indent(p, indent, "pages_use_count=%u\n", shmem->pages_use_count);
	drm_म_लिखो_indent(p, indent, "vmap_use_count=%u\n", shmem->vmap_use_count);
	drm_म_लिखो_indent(p, indent, "vaddr=%p\n", shmem->vaddr);
पूर्ण
EXPORT_SYMBOL(drm_gem_shmem_prपूर्णांक_info);

/**
 * drm_gem_shmem_get_sg_table - Provide a scatter/gather table of pinned
 *                              pages क्रम a shmem GEM object
 * @obj: GEM object
 *
 * This function exports a scatter/gather table suitable क्रम PRIME usage by
 * calling the standard DMA mapping API. Drivers should not call this function
 * directly, instead it should only be used as an implementation क्रम
 * &drm_gem_object_funcs.get_sg_table.
 *
 * Drivers who need to acquire an scatter/gather table क्रम objects need to call
 * drm_gem_shmem_get_pages_sgt() instead.
 *
 * Returns:
 * A poपूर्णांकer to the scatter/gather table of pinned pages or शून्य on failure.
 */
काष्ठा sg_table *drm_gem_shmem_get_sg_table(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);

	WARN_ON(shmem->base.import_attach);

	वापस drm_prime_pages_to_sg(obj->dev, shmem->pages, obj->size >> PAGE_SHIFT);
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_shmem_get_sg_table);

/**
 * drm_gem_shmem_get_pages_sgt - Pin pages, dma map them, and वापस a
 *				 scatter/gather table क्रम a shmem GEM object.
 * @obj: GEM object
 *
 * This function वापसs a scatter/gather table suitable क्रम driver usage. If
 * the sg table करोesn't exist, the pages are pinned, dma-mapped, and a sg
 * table created.
 *
 * This is the मुख्य function क्रम drivers to get at backing storage, and it hides
 * and dअगरference between dma-buf imported and natively allocated objects.
 * drm_gem_shmem_get_sg_table() should not be directly called by drivers.
 *
 * Returns:
 * A poपूर्णांकer to the scatter/gather table of pinned pages or त्रुटि_सं on failure.
 */
काष्ठा sg_table *drm_gem_shmem_get_pages_sgt(काष्ठा drm_gem_object *obj)
अणु
	पूर्णांक ret;
	काष्ठा drm_gem_shmem_object *shmem = to_drm_gem_shmem_obj(obj);
	काष्ठा sg_table *sgt;

	अगर (shmem->sgt)
		वापस shmem->sgt;

	WARN_ON(obj->import_attach);

	ret = drm_gem_shmem_get_pages(shmem);
	अगर (ret)
		वापस ERR_PTR(ret);

	sgt = drm_gem_shmem_get_sg_table(&shmem->base);
	अगर (IS_ERR(sgt)) अणु
		ret = PTR_ERR(sgt);
		जाओ err_put_pages;
	पूर्ण
	/* Map the pages क्रम use by the h/w. */
	ret = dma_map_sgtable(obj->dev->dev, sgt, DMA_BIसूचीECTIONAL, 0);
	अगर (ret)
		जाओ err_मुक्त_sgt;

	shmem->sgt = sgt;

	वापस sgt;

err_मुक्त_sgt:
	sg_मुक्त_table(sgt);
	kमुक्त(sgt);
err_put_pages:
	drm_gem_shmem_put_pages(shmem);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_shmem_get_pages_sgt);

/**
 * drm_gem_shmem_prime_import_sg_table - Produce a shmem GEM object from
 *                 another driver's scatter/gather table of pinned pages
 * @dev: Device to import पूर्णांकo
 * @attach: DMA-BUF attachment
 * @sgt: Scatter/gather table of pinned pages
 *
 * This function imports a scatter/gather table exported via DMA-BUF by
 * another driver. Drivers that use the shmem helpers should set this as their
 * &drm_driver.gem_prime_import_sg_table callback.
 *
 * Returns:
 * A poपूर्णांकer to a newly created GEM object or an ERR_PTR-encoded negative
 * error code on failure.
 */
काष्ठा drm_gem_object *
drm_gem_shmem_prime_import_sg_table(काष्ठा drm_device *dev,
				    काष्ठा dma_buf_attachment *attach,
				    काष्ठा sg_table *sgt)
अणु
	माप_प्रकार size = PAGE_ALIGN(attach->dmabuf->size);
	काष्ठा drm_gem_shmem_object *shmem;

	shmem = __drm_gem_shmem_create(dev, size, true);
	अगर (IS_ERR(shmem))
		वापस ERR_CAST(shmem);

	shmem->sgt = sgt;

	DRM_DEBUG_PRIME("size = %zu\n", size);

	वापस &shmem->base;
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_shmem_prime_import_sg_table);
