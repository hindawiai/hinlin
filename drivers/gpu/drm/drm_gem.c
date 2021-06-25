<शैली गुरु>
/*
 * Copyright तऊ 2008 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Eric Anholt <eric@anholt.net>
 *
 */

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/mm.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/module.h>
#समावेश <linux/mman.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/shmem_fs.h>
#समावेश <linux/dma-buf.h>
#समावेश <linux/dma-buf-map.h>
#समावेश <linux/mem_encrypt.h>
#समावेश <linux/pagevec.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_vma_manager.h>

#समावेश "drm_internal.h"

/** @file drm_gem.c
 *
 * This file provides some of the base ioctls and library routines क्रम
 * the graphics memory manager implemented by each device driver.
 *
 * Because various devices have dअगरferent requirements in terms of
 * synchronization and migration strategies, implementing that is left up to
 * the driver, and all that the general API provides should be generic --
 * allocating objects, पढ़ोing/writing data with the cpu, मुक्तing objects.
 * Even there, platक्रमm-dependent optimizations क्रम पढ़ोing/writing data with
 * the CPU mean we'll likely hook those out to driver-specअगरic calls.  However,
 * the DRI2 implementation wants to have at least allocate/mmap be generic.
 *
 * The goal was to have swap-backed object allocation managed through
 * काष्ठा file.  However, file descriptors as handles to a काष्ठा file have
 * two major failings:
 * - Process limits prevent more than 1024 or so being used at a समय by
 *   शेष.
 * - Inability to allocate high fds will aggravate the X Server's select()
 *   handling, and likely that of many GL client applications as well.
 *
 * This led to a plan of using our own पूर्णांकeger IDs (called handles, following
 * DRM terminology) to mimic fds, and implement the fd syscalls we need as
 * ioctls.  The objects themselves will still include the काष्ठा file so
 * that we can transition to fds अगर the required kernel infraकाष्ठाure shows
 * up at a later date, and as our पूर्णांकerface with shmfs क्रम memory allocation.
 */

अटल व्योम
drm_gem_init_release(काष्ठा drm_device *dev, व्योम *ptr)
अणु
	drm_vma_offset_manager_destroy(dev->vma_offset_manager);
पूर्ण

/**
 * drm_gem_init - Initialize the GEM device fields
 * @dev: drm_devic काष्ठाure to initialize
 */
पूर्णांक
drm_gem_init(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_vma_offset_manager *vma_offset_manager;

	mutex_init(&dev->object_name_lock);
	idr_init_base(&dev->object_name_idr, 1);

	vma_offset_manager = drmm_kzalloc(dev, माप(*vma_offset_manager),
					  GFP_KERNEL);
	अगर (!vma_offset_manager) अणु
		DRM_ERROR("out of memory\n");
		वापस -ENOMEM;
	पूर्ण

	dev->vma_offset_manager = vma_offset_manager;
	drm_vma_offset_manager_init(vma_offset_manager,
				    DRM_खाता_PAGE_OFFSET_START,
				    DRM_खाता_PAGE_OFFSET_SIZE);

	वापस drmm_add_action(dev, drm_gem_init_release, शून्य);
पूर्ण

/**
 * drm_gem_object_init - initialize an allocated shmem-backed GEM object
 * @dev: drm_device the object should be initialized क्रम
 * @obj: drm_gem_object to initialize
 * @size: object size
 *
 * Initialize an alपढ़ोy allocated GEM object of the specअगरied size with
 * shmfs backing store.
 */
पूर्णांक drm_gem_object_init(काष्ठा drm_device *dev,
			काष्ठा drm_gem_object *obj, माप_प्रकार size)
अणु
	काष्ठा file *filp;

	drm_gem_निजी_object_init(dev, obj, size);

	filp = shmem_file_setup("drm mm object", size, VM_NORESERVE);
	अगर (IS_ERR(filp))
		वापस PTR_ERR(filp);

	obj->filp = filp;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_gem_object_init);

/**
 * drm_gem_निजी_object_init - initialize an allocated निजी GEM object
 * @dev: drm_device the object should be initialized क्रम
 * @obj: drm_gem_object to initialize
 * @size: object size
 *
 * Initialize an alपढ़ोy allocated GEM object of the specअगरied size with
 * no GEM provided backing store. Instead the caller is responsible क्रम
 * backing the object and handling it.
 */
व्योम drm_gem_निजी_object_init(काष्ठा drm_device *dev,
				 काष्ठा drm_gem_object *obj, माप_प्रकार size)
अणु
	BUG_ON((size & (PAGE_SIZE - 1)) != 0);

	obj->dev = dev;
	obj->filp = शून्य;

	kref_init(&obj->refcount);
	obj->handle_count = 0;
	obj->size = size;
	dma_resv_init(&obj->_resv);
	अगर (!obj->resv)
		obj->resv = &obj->_resv;

	drm_vma_node_reset(&obj->vma_node);
पूर्ण
EXPORT_SYMBOL(drm_gem_निजी_object_init);

अटल व्योम
drm_gem_हटाओ_prime_handles(काष्ठा drm_gem_object *obj, काष्ठा drm_file *filp)
अणु
	/*
	 * Note: obj->dma_buf can't disappear as दीर्घ as we still hold a
	 * handle reference in obj->handle_count.
	 */
	mutex_lock(&filp->prime.lock);
	अगर (obj->dma_buf) अणु
		drm_prime_हटाओ_buf_handle_locked(&filp->prime,
						   obj->dma_buf);
	पूर्ण
	mutex_unlock(&filp->prime.lock);
पूर्ण

/**
 * drm_gem_object_handle_मुक्त - release resources bound to userspace handles
 * @obj: GEM object to clean up.
 *
 * Called after the last handle to the object has been बंदd
 *
 * Removes any name क्रम the object. Note that this must be
 * called beक्रमe drm_gem_object_मुक्त or we'll be touching
 * मुक्तd memory
 */
अटल व्योम drm_gem_object_handle_मुक्त(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_device *dev = obj->dev;

	/* Remove any name क्रम this object */
	अगर (obj->name) अणु
		idr_हटाओ(&dev->object_name_idr, obj->name);
		obj->name = 0;
	पूर्ण
पूर्ण

अटल व्योम drm_gem_object_exported_dma_buf_मुक्त(काष्ठा drm_gem_object *obj)
अणु
	/* Unअवरोध the reference cycle अगर we have an exported dma_buf. */
	अगर (obj->dma_buf) अणु
		dma_buf_put(obj->dma_buf);
		obj->dma_buf = शून्य;
	पूर्ण
पूर्ण

अटल व्योम
drm_gem_object_handle_put_unlocked(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_device *dev = obj->dev;
	bool final = false;

	अगर (WARN_ON(READ_ONCE(obj->handle_count) == 0))
		वापस;

	/*
	* Must bump handle count first as this may be the last
	* ref, in which हाल the object would disappear beक्रमe we
	* checked क्रम a name
	*/

	mutex_lock(&dev->object_name_lock);
	अगर (--obj->handle_count == 0) अणु
		drm_gem_object_handle_मुक्त(obj);
		drm_gem_object_exported_dma_buf_मुक्त(obj);
		final = true;
	पूर्ण
	mutex_unlock(&dev->object_name_lock);

	अगर (final)
		drm_gem_object_put(obj);
पूर्ण

/*
 * Called at device or object बंद to release the file's
 * handle references on objects.
 */
अटल पूर्णांक
drm_gem_object_release_handle(पूर्णांक id, व्योम *ptr, व्योम *data)
अणु
	काष्ठा drm_file *file_priv = data;
	काष्ठा drm_gem_object *obj = ptr;

	अगर (obj->funcs->बंद)
		obj->funcs->बंद(obj, file_priv);

	drm_gem_हटाओ_prime_handles(obj, file_priv);
	drm_vma_node_revoke(&obj->vma_node, file_priv);

	drm_gem_object_handle_put_unlocked(obj);

	वापस 0;
पूर्ण

/**
 * drm_gem_handle_delete - deletes the given file-निजी handle
 * @filp: drm file-निजी काष्ठाure to use क्रम the handle look up
 * @handle: userspace handle to delete
 *
 * Removes the GEM handle from the @filp lookup table which has been added with
 * drm_gem_handle_create(). If this is the last handle also cleans up linked
 * resources like GEM names.
 */
पूर्णांक
drm_gem_handle_delete(काष्ठा drm_file *filp, u32 handle)
अणु
	काष्ठा drm_gem_object *obj;

	spin_lock(&filp->table_lock);

	/* Check अगर we currently have a reference on the object */
	obj = idr_replace(&filp->object_idr, शून्य, handle);
	spin_unlock(&filp->table_lock);
	अगर (IS_ERR_OR_शून्य(obj))
		वापस -EINVAL;

	/* Release driver's reference and decrement refcount. */
	drm_gem_object_release_handle(handle, obj, filp);

	/* And finally make the handle available क्रम future allocations. */
	spin_lock(&filp->table_lock);
	idr_हटाओ(&filp->object_idr, handle);
	spin_unlock(&filp->table_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_gem_handle_delete);

/**
 * drm_gem_dumb_map_offset - वापस the fake mmap offset क्रम a gem object
 * @file: drm file-निजी काष्ठाure containing the gem object
 * @dev: corresponding drm_device
 * @handle: gem object handle
 * @offset: वापस location क्रम the fake mmap offset
 *
 * This implements the &drm_driver.dumb_map_offset kms driver callback क्रम
 * drivers which use gem to manage their backing storage.
 *
 * Returns:
 * 0 on success or a negative error code on failure.
 */
पूर्णांक drm_gem_dumb_map_offset(काष्ठा drm_file *file, काष्ठा drm_device *dev,
			    u32 handle, u64 *offset)
अणु
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret;

	obj = drm_gem_object_lookup(file, handle);
	अगर (!obj)
		वापस -ENOENT;

	/* Don't allow imported objects to be mapped */
	अगर (obj->import_attach) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = drm_gem_create_mmap_offset(obj);
	अगर (ret)
		जाओ out;

	*offset = drm_vma_node_offset_addr(&obj->vma_node);
out:
	drm_gem_object_put(obj);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_dumb_map_offset);

पूर्णांक drm_gem_dumb_destroy(काष्ठा drm_file *file,
			 काष्ठा drm_device *dev,
			 u32 handle)
अणु
	वापस drm_gem_handle_delete(file, handle);
पूर्ण

/**
 * drm_gem_handle_create_tail - पूर्णांकernal functions to create a handle
 * @file_priv: drm file-निजी काष्ठाure to रेजिस्टर the handle क्रम
 * @obj: object to रेजिस्टर
 * @handlep: poपूर्णांकer to वापस the created handle to the caller
 *
 * This expects the &drm_device.object_name_lock to be held alपढ़ोy and will
 * drop it beक्रमe वापसing. Used to aव्योम races in establishing new handles
 * when importing an object from either an flink name or a dma-buf.
 *
 * Handles must be release again through drm_gem_handle_delete(). This is करोne
 * when userspace बंदs @file_priv क्रम all attached handles, or through the
 * GEM_CLOSE ioctl क्रम inभागidual handles.
 */
पूर्णांक
drm_gem_handle_create_tail(काष्ठा drm_file *file_priv,
			   काष्ठा drm_gem_object *obj,
			   u32 *handlep)
अणु
	काष्ठा drm_device *dev = obj->dev;
	u32 handle;
	पूर्णांक ret;

	WARN_ON(!mutex_is_locked(&dev->object_name_lock));
	अगर (obj->handle_count++ == 0)
		drm_gem_object_get(obj);

	/*
	 * Get the user-visible handle using idr.  Preload and perक्रमm
	 * allocation under our spinlock.
	 */
	idr_preload(GFP_KERNEL);
	spin_lock(&file_priv->table_lock);

	ret = idr_alloc(&file_priv->object_idr, obj, 1, 0, GFP_NOWAIT);

	spin_unlock(&file_priv->table_lock);
	idr_preload_end();

	mutex_unlock(&dev->object_name_lock);
	अगर (ret < 0)
		जाओ err_unref;

	handle = ret;

	ret = drm_vma_node_allow(&obj->vma_node, file_priv);
	अगर (ret)
		जाओ err_हटाओ;

	अगर (obj->funcs->खोलो) अणु
		ret = obj->funcs->खोलो(obj, file_priv);
		अगर (ret)
			जाओ err_revoke;
	पूर्ण

	*handlep = handle;
	वापस 0;

err_revoke:
	drm_vma_node_revoke(&obj->vma_node, file_priv);
err_हटाओ:
	spin_lock(&file_priv->table_lock);
	idr_हटाओ(&file_priv->object_idr, handle);
	spin_unlock(&file_priv->table_lock);
err_unref:
	drm_gem_object_handle_put_unlocked(obj);
	वापस ret;
पूर्ण

/**
 * drm_gem_handle_create - create a gem handle क्रम an object
 * @file_priv: drm file-निजी काष्ठाure to रेजिस्टर the handle क्रम
 * @obj: object to रेजिस्टर
 * @handlep: poपूर्णांकer to वापस the created handle to the caller
 *
 * Create a handle क्रम this object. This adds a handle reference to the object,
 * which includes a regular reference count. Callers will likely want to
 * dereference the object afterwards.
 *
 * Since this publishes @obj to userspace it must be fully set up by this poपूर्णांक,
 * drivers must call this last in their buffer object creation callbacks.
 */
पूर्णांक drm_gem_handle_create(काष्ठा drm_file *file_priv,
			  काष्ठा drm_gem_object *obj,
			  u32 *handlep)
अणु
	mutex_lock(&obj->dev->object_name_lock);

	वापस drm_gem_handle_create_tail(file_priv, obj, handlep);
पूर्ण
EXPORT_SYMBOL(drm_gem_handle_create);


/**
 * drm_gem_मुक्त_mmap_offset - release a fake mmap offset क्रम an object
 * @obj: obj in question
 *
 * This routine मुक्तs fake offsets allocated by drm_gem_create_mmap_offset().
 *
 * Note that drm_gem_object_release() alपढ़ोy calls this function, so drivers
 * करोn't have to take care of releasing the mmap offset themselves when मुक्तing
 * the GEM object.
 */
व्योम
drm_gem_मुक्त_mmap_offset(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_device *dev = obj->dev;

	drm_vma_offset_हटाओ(dev->vma_offset_manager, &obj->vma_node);
पूर्ण
EXPORT_SYMBOL(drm_gem_मुक्त_mmap_offset);

/**
 * drm_gem_create_mmap_offset_size - create a fake mmap offset क्रम an object
 * @obj: obj in question
 * @size: the भव size
 *
 * GEM memory mapping works by handing back to userspace a fake mmap offset
 * it can use in a subsequent mmap(2) call.  The DRM core code then looks
 * up the object based on the offset and sets up the various memory mapping
 * काष्ठाures.
 *
 * This routine allocates and attaches a fake offset क्रम @obj, in हालs where
 * the भव size dअगरfers from the physical size (ie. &drm_gem_object.size).
 * Otherwise just use drm_gem_create_mmap_offset().
 *
 * This function is idempotent and handles an alपढ़ोy allocated mmap offset
 * transparently. Drivers करो not need to check क्रम this हाल.
 */
पूर्णांक
drm_gem_create_mmap_offset_size(काष्ठा drm_gem_object *obj, माप_प्रकार size)
अणु
	काष्ठा drm_device *dev = obj->dev;

	वापस drm_vma_offset_add(dev->vma_offset_manager, &obj->vma_node,
				  size / PAGE_SIZE);
पूर्ण
EXPORT_SYMBOL(drm_gem_create_mmap_offset_size);

/**
 * drm_gem_create_mmap_offset - create a fake mmap offset क्रम an object
 * @obj: obj in question
 *
 * GEM memory mapping works by handing back to userspace a fake mmap offset
 * it can use in a subsequent mmap(2) call.  The DRM core code then looks
 * up the object based on the offset and sets up the various memory mapping
 * काष्ठाures.
 *
 * This routine allocates and attaches a fake offset क्रम @obj.
 *
 * Drivers can call drm_gem_मुक्त_mmap_offset() beक्रमe मुक्तing @obj to release
 * the fake offset again.
 */
पूर्णांक drm_gem_create_mmap_offset(काष्ठा drm_gem_object *obj)
अणु
	वापस drm_gem_create_mmap_offset_size(obj, obj->size);
पूर्ण
EXPORT_SYMBOL(drm_gem_create_mmap_offset);

/*
 * Move pages to appropriate lru and release the pagevec, decrementing the
 * ref count of those pages.
 */
अटल व्योम drm_gem_check_release_pagevec(काष्ठा pagevec *pvec)
अणु
	check_move_unevictable_pages(pvec);
	__pagevec_release(pvec);
	cond_resched();
पूर्ण

/**
 * drm_gem_get_pages - helper to allocate backing pages क्रम a GEM object
 * from shmem
 * @obj: obj in question
 *
 * This पढ़ोs the page-array of the shmem-backing storage of the given gem
 * object. An array of pages is वापसed. If a page is not allocated or
 * swapped-out, this will allocate/swap-in the required pages. Note that the
 * whole object is covered by the page-array and pinned in memory.
 *
 * Use drm_gem_put_pages() to release the array and unpin all pages.
 *
 * This uses the GFP-mask set on the shmem-mapping (see mapping_set_gfp_mask()).
 * If you require other GFP-masks, you have to करो those allocations yourself.
 *
 * Note that you are not allowed to change gfp-zones during runसमय. That is,
 * shmem_पढ़ो_mapping_page_gfp() must be called with the same gfp_zone(gfp) as
 * set during initialization. If you have special zone स्थिरraपूर्णांकs, set them
 * after drm_gem_object_init() via mapping_set_gfp_mask(). shmem-core takes care
 * to keep pages in the required zone during swap-in.
 *
 * This function is only valid on objects initialized with
 * drm_gem_object_init(), but not क्रम those initialized with
 * drm_gem_निजी_object_init() only.
 */
काष्ठा page **drm_gem_get_pages(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा address_space *mapping;
	काष्ठा page *p, **pages;
	काष्ठा pagevec pvec;
	पूर्णांक i, npages;


	अगर (WARN_ON(!obj->filp))
		वापस ERR_PTR(-EINVAL);

	/* This is the shared memory object that backs the GEM resource */
	mapping = obj->filp->f_mapping;

	/* We alपढ़ोy BUG_ON() क्रम non-page-aligned sizes in
	 * drm_gem_object_init(), so we should never hit this unless
	 * driver author is करोing something really wrong:
	 */
	WARN_ON((obj->size & (PAGE_SIZE - 1)) != 0);

	npages = obj->size >> PAGE_SHIFT;

	pages = kvदो_स्मृति_array(npages, माप(काष्ठा page *), GFP_KERNEL);
	अगर (pages == शून्य)
		वापस ERR_PTR(-ENOMEM);

	mapping_set_unevictable(mapping);

	क्रम (i = 0; i < npages; i++) अणु
		p = shmem_पढ़ो_mapping_page(mapping, i);
		अगर (IS_ERR(p))
			जाओ fail;
		pages[i] = p;

		/* Make sure shmem keeps __GFP_DMA32 allocated pages in the
		 * correct region during swapin. Note that this requires
		 * __GFP_DMA32 to be set in mapping_gfp_mask(inode->i_mapping)
		 * so shmem can relocate pages during swapin अगर required.
		 */
		BUG_ON(mapping_gfp_स्थिरraपूर्णांक(mapping, __GFP_DMA32) &&
				(page_to_pfn(p) >= 0x00100000UL));
	पूर्ण

	वापस pages;

fail:
	mapping_clear_unevictable(mapping);
	pagevec_init(&pvec);
	जबतक (i--) अणु
		अगर (!pagevec_add(&pvec, pages[i]))
			drm_gem_check_release_pagevec(&pvec);
	पूर्ण
	अगर (pagevec_count(&pvec))
		drm_gem_check_release_pagevec(&pvec);

	kvमुक्त(pages);
	वापस ERR_CAST(p);
पूर्ण
EXPORT_SYMBOL(drm_gem_get_pages);

/**
 * drm_gem_put_pages - helper to मुक्त backing pages क्रम a GEM object
 * @obj: obj in question
 * @pages: pages to मुक्त
 * @dirty: अगर true, pages will be marked as dirty
 * @accessed: अगर true, the pages will be marked as accessed
 */
व्योम drm_gem_put_pages(काष्ठा drm_gem_object *obj, काष्ठा page **pages,
		bool dirty, bool accessed)
अणु
	पूर्णांक i, npages;
	काष्ठा address_space *mapping;
	काष्ठा pagevec pvec;

	mapping = file_inode(obj->filp)->i_mapping;
	mapping_clear_unevictable(mapping);

	/* We alपढ़ोy BUG_ON() क्रम non-page-aligned sizes in
	 * drm_gem_object_init(), so we should never hit this unless
	 * driver author is करोing something really wrong:
	 */
	WARN_ON((obj->size & (PAGE_SIZE - 1)) != 0);

	npages = obj->size >> PAGE_SHIFT;

	pagevec_init(&pvec);
	क्रम (i = 0; i < npages; i++) अणु
		अगर (!pages[i])
			जारी;

		अगर (dirty)
			set_page_dirty(pages[i]);

		अगर (accessed)
			mark_page_accessed(pages[i]);

		/* Unकरो the reference we took when populating the table */
		अगर (!pagevec_add(&pvec, pages[i]))
			drm_gem_check_release_pagevec(&pvec);
	पूर्ण
	अगर (pagevec_count(&pvec))
		drm_gem_check_release_pagevec(&pvec);

	kvमुक्त(pages);
पूर्ण
EXPORT_SYMBOL(drm_gem_put_pages);

अटल पूर्णांक objects_lookup(काष्ठा drm_file *filp, u32 *handle, पूर्णांक count,
			  काष्ठा drm_gem_object **objs)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा drm_gem_object *obj;

	spin_lock(&filp->table_lock);

	क्रम (i = 0; i < count; i++) अणु
		/* Check अगर we currently have a reference on the object */
		obj = idr_find(&filp->object_idr, handle[i]);
		अगर (!obj) अणु
			ret = -ENOENT;
			अवरोध;
		पूर्ण
		drm_gem_object_get(obj);
		objs[i] = obj;
	पूर्ण
	spin_unlock(&filp->table_lock);

	वापस ret;
पूर्ण

/**
 * drm_gem_objects_lookup - look up GEM objects from an array of handles
 * @filp: DRM file निजी date
 * @bo_handles: user poपूर्णांकer to array of userspace handle
 * @count: size of handle array
 * @objs_out: वापसed poपूर्णांकer to array of drm_gem_object poपूर्णांकers
 *
 * Takes an array of userspace handles and वापसs a newly allocated array of
 * GEM objects.
 *
 * For a single handle lookup, use drm_gem_object_lookup().
 *
 * Returns:
 *
 * @objs filled in with GEM object poपूर्णांकers. Returned GEM objects need to be
 * released with drm_gem_object_put(). -ENOENT is वापसed on a lookup
 * failure. 0 is वापसed on success.
 *
 */
पूर्णांक drm_gem_objects_lookup(काष्ठा drm_file *filp, व्योम __user *bo_handles,
			   पूर्णांक count, काष्ठा drm_gem_object ***objs_out)
अणु
	पूर्णांक ret;
	u32 *handles;
	काष्ठा drm_gem_object **objs;

	अगर (!count)
		वापस 0;

	objs = kvदो_स्मृति_array(count, माप(काष्ठा drm_gem_object *),
			     GFP_KERNEL | __GFP_ZERO);
	अगर (!objs)
		वापस -ENOMEM;

	*objs_out = objs;

	handles = kvदो_स्मृति_array(count, माप(u32), GFP_KERNEL);
	अगर (!handles) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (copy_from_user(handles, bo_handles, count * माप(u32))) अणु
		ret = -EFAULT;
		DRM_DEBUG("Failed to copy in GEM handles\n");
		जाओ out;
	पूर्ण

	ret = objects_lookup(filp, handles, count, objs);
out:
	kvमुक्त(handles);
	वापस ret;

पूर्ण
EXPORT_SYMBOL(drm_gem_objects_lookup);

/**
 * drm_gem_object_lookup - look up a GEM object from its handle
 * @filp: DRM file निजी date
 * @handle: userspace handle
 *
 * Returns:
 *
 * A reference to the object named by the handle अगर such exists on @filp, शून्य
 * otherwise.
 *
 * If looking up an array of handles, use drm_gem_objects_lookup().
 */
काष्ठा drm_gem_object *
drm_gem_object_lookup(काष्ठा drm_file *filp, u32 handle)
अणु
	काष्ठा drm_gem_object *obj = शून्य;

	objects_lookup(filp, &handle, 1, &obj);
	वापस obj;
पूर्ण
EXPORT_SYMBOL(drm_gem_object_lookup);

/**
 * drm_gem_dma_resv_रुको - Wait on GEM object's reservation's objects
 * shared and/or exclusive fences.
 * @filep: DRM file निजी date
 * @handle: userspace handle
 * @रुको_all: अगर true, रुको on all fences, अन्यथा रुको on just exclusive fence
 * @समयout: समयout value in jअगरfies or zero to वापस immediately
 *
 * Returns:
 *
 * Returns -ERESTARTSYS अगर पूर्णांकerrupted, 0 अगर the रुको समयd out, or
 * greater than 0 on success.
 */
दीर्घ drm_gem_dma_resv_रुको(काष्ठा drm_file *filep, u32 handle,
				    bool रुको_all, अचिन्हित दीर्घ समयout)
अणु
	दीर्घ ret;
	काष्ठा drm_gem_object *obj;

	obj = drm_gem_object_lookup(filep, handle);
	अगर (!obj) अणु
		DRM_DEBUG("Failed to look up GEM BO %d\n", handle);
		वापस -EINVAL;
	पूर्ण

	ret = dma_resv_रुको_समयout_rcu(obj->resv, रुको_all,
						  true, समयout);
	अगर (ret == 0)
		ret = -ETIME;
	अन्यथा अगर (ret > 0)
		ret = 0;

	drm_gem_object_put(obj);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_gem_dma_resv_रुको);

/**
 * drm_gem_बंद_ioctl - implementation of the GEM_CLOSE ioctl
 * @dev: drm_device
 * @data: ioctl data
 * @file_priv: drm file-निजी काष्ठाure
 *
 * Releases the handle to an mm object.
 */
पूर्णांक
drm_gem_बंद_ioctl(काष्ठा drm_device *dev, व्योम *data,
		    काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_gem_बंद *args = data;
	पूर्णांक ret;

	अगर (!drm_core_check_feature(dev, DRIVER_GEM))
		वापस -EOPNOTSUPP;

	ret = drm_gem_handle_delete(file_priv, args->handle);

	वापस ret;
पूर्ण

/**
 * drm_gem_flink_ioctl - implementation of the GEM_FLINK ioctl
 * @dev: drm_device
 * @data: ioctl data
 * @file_priv: drm file-निजी काष्ठाure
 *
 * Create a global name क्रम an object, वापसing the name.
 *
 * Note that the name करोes not hold a reference; when the object
 * is मुक्तd, the name goes away.
 */
पूर्णांक
drm_gem_flink_ioctl(काष्ठा drm_device *dev, व्योम *data,
		    काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_gem_flink *args = data;
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret;

	अगर (!drm_core_check_feature(dev, DRIVER_GEM))
		वापस -EOPNOTSUPP;

	obj = drm_gem_object_lookup(file_priv, args->handle);
	अगर (obj == शून्य)
		वापस -ENOENT;

	mutex_lock(&dev->object_name_lock);
	/* prevent races with concurrent gem_बंद. */
	अगर (obj->handle_count == 0) अणु
		ret = -ENOENT;
		जाओ err;
	पूर्ण

	अगर (!obj->name) अणु
		ret = idr_alloc(&dev->object_name_idr, obj, 1, 0, GFP_KERNEL);
		अगर (ret < 0)
			जाओ err;

		obj->name = ret;
	पूर्ण

	args->name = (uपूर्णांक64_t) obj->name;
	ret = 0;

err:
	mutex_unlock(&dev->object_name_lock);
	drm_gem_object_put(obj);
	वापस ret;
पूर्ण

/**
 * drm_gem_खोलो_ioctl - implementation of the GEM_OPEN ioctl
 * @dev: drm_device
 * @data: ioctl data
 * @file_priv: drm file-निजी काष्ठाure
 *
 * Open an object using the global name, वापसing a handle and the size.
 *
 * This handle (of course) holds a reference to the object, so the object
 * will not go away until the handle is deleted.
 */
पूर्णांक
drm_gem_खोलो_ioctl(काष्ठा drm_device *dev, व्योम *data,
		   काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_gem_खोलो *args = data;
	काष्ठा drm_gem_object *obj;
	पूर्णांक ret;
	u32 handle;

	अगर (!drm_core_check_feature(dev, DRIVER_GEM))
		वापस -EOPNOTSUPP;

	mutex_lock(&dev->object_name_lock);
	obj = idr_find(&dev->object_name_idr, (पूर्णांक) args->name);
	अगर (obj) अणु
		drm_gem_object_get(obj);
	पूर्ण अन्यथा अणु
		mutex_unlock(&dev->object_name_lock);
		वापस -ENOENT;
	पूर्ण

	/* drm_gem_handle_create_tail unlocks dev->object_name_lock. */
	ret = drm_gem_handle_create_tail(file_priv, obj, &handle);
	अगर (ret)
		जाओ err;

	args->handle = handle;
	args->size = obj->size;

err:
	drm_gem_object_put(obj);
	वापस ret;
पूर्ण

/**
 * drm_gem_खोलो - initalizes GEM file-निजी काष्ठाures at devnode खोलो समय
 * @dev: drm_device which is being खोलोed by userspace
 * @file_निजी: drm file-निजी काष्ठाure to set up
 *
 * Called at device खोलो समय, sets up the काष्ठाure क्रम handling refcounting
 * of mm objects.
 */
व्योम
drm_gem_खोलो(काष्ठा drm_device *dev, काष्ठा drm_file *file_निजी)
अणु
	idr_init_base(&file_निजी->object_idr, 1);
	spin_lock_init(&file_निजी->table_lock);
पूर्ण

/**
 * drm_gem_release - release file-निजी GEM resources
 * @dev: drm_device which is being बंदd by userspace
 * @file_निजी: drm file-निजी काष्ठाure to clean up
 *
 * Called at बंद समय when the filp is going away.
 *
 * Releases any reमुख्यing references on objects by this filp.
 */
व्योम
drm_gem_release(काष्ठा drm_device *dev, काष्ठा drm_file *file_निजी)
अणु
	idr_क्रम_each(&file_निजी->object_idr,
		     &drm_gem_object_release_handle, file_निजी);
	idr_destroy(&file_निजी->object_idr);
पूर्ण

/**
 * drm_gem_object_release - release GEM buffer object resources
 * @obj: GEM buffer object
 *
 * This releases any काष्ठाures and resources used by @obj and is the invers of
 * drm_gem_object_init().
 */
व्योम
drm_gem_object_release(काष्ठा drm_gem_object *obj)
अणु
	WARN_ON(obj->dma_buf);

	अगर (obj->filp)
		fput(obj->filp);

	dma_resv_fini(&obj->_resv);
	drm_gem_मुक्त_mmap_offset(obj);
पूर्ण
EXPORT_SYMBOL(drm_gem_object_release);

/**
 * drm_gem_object_मुक्त - मुक्त a GEM object
 * @kref: kref of the object to मुक्त
 *
 * Called after the last reference to the object has been lost.
 *
 * Frees the object
 */
व्योम
drm_gem_object_मुक्त(काष्ठा kref *kref)
अणु
	काष्ठा drm_gem_object *obj =
		container_of(kref, काष्ठा drm_gem_object, refcount);

	अगर (WARN_ON(!obj->funcs->मुक्त))
		वापस;

	obj->funcs->मुक्त(obj);
पूर्ण
EXPORT_SYMBOL(drm_gem_object_मुक्त);

/**
 * drm_gem_object_put_locked - release a GEM buffer object reference
 * @obj: GEM buffer object
 *
 * This releases a reference to @obj. Callers must hold the
 * &drm_device.काष्ठा_mutex lock when calling this function, even when the
 * driver करोesn't use &drm_device.काष्ठा_mutex क्रम anything.
 *
 * For drivers not encumbered with legacy locking use
 * drm_gem_object_put() instead.
 */
व्योम
drm_gem_object_put_locked(काष्ठा drm_gem_object *obj)
अणु
	अगर (obj) अणु
		WARN_ON(!mutex_is_locked(&obj->dev->काष्ठा_mutex));

		kref_put(&obj->refcount, drm_gem_object_मुक्त);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_gem_object_put_locked);

/**
 * drm_gem_vm_खोलो - vma->ops->खोलो implementation क्रम GEM
 * @vma: VM area काष्ठाure
 *
 * This function implements the #vm_operations_काष्ठा खोलो() callback क्रम GEM
 * drivers. This must be used together with drm_gem_vm_बंद().
 */
व्योम drm_gem_vm_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_gem_object *obj = vma->vm_निजी_data;

	drm_gem_object_get(obj);
पूर्ण
EXPORT_SYMBOL(drm_gem_vm_खोलो);

/**
 * drm_gem_vm_बंद - vma->ops->बंद implementation क्रम GEM
 * @vma: VM area काष्ठाure
 *
 * This function implements the #vm_operations_काष्ठा बंद() callback क्रम GEM
 * drivers. This must be used together with drm_gem_vm_खोलो().
 */
व्योम drm_gem_vm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_gem_object *obj = vma->vm_निजी_data;

	drm_gem_object_put(obj);
पूर्ण
EXPORT_SYMBOL(drm_gem_vm_बंद);

/**
 * drm_gem_mmap_obj - memory map a GEM object
 * @obj: the GEM object to map
 * @obj_size: the object size to be mapped, in bytes
 * @vma: VMA क्रम the area to be mapped
 *
 * Set up the VMA to prepare mapping of the GEM object using the GEM object's
 * vm_ops. Depending on their requirements, GEM objects can either
 * provide a fault handler in their vm_ops (in which हाल any accesses to
 * the object will be trapped, to perक्रमm migration, GTT binding, surface
 * रेजिस्टर allocation, or perक्रमmance monitoring), or mmap the buffer memory
 * synchronously after calling drm_gem_mmap_obj.
 *
 * This function is मुख्यly पूर्णांकended to implement the DMABUF mmap operation, when
 * the GEM object is not looked up based on its fake offset. To implement the
 * DRM mmap operation, drivers should use the drm_gem_mmap() function.
 *
 * drm_gem_mmap_obj() assumes the user is granted access to the buffer जबतक
 * drm_gem_mmap() prevents unprivileged users from mapping अक्रमom objects. So
 * callers must verअगरy access restrictions beक्रमe calling this helper.
 *
 * Return 0 or success or -EINVAL अगर the object size is smaller than the VMA
 * size, or अगर no vm_ops are provided.
 */
पूर्णांक drm_gem_mmap_obj(काष्ठा drm_gem_object *obj, अचिन्हित दीर्घ obj_size,
		     काष्ठा vm_area_काष्ठा *vma)
अणु
	पूर्णांक ret;

	/* Check क्रम valid size. */
	अगर (obj_size < vma->vm_end - vma->vm_start)
		वापस -EINVAL;

	/* Take a ref क्रम this mapping of the object, so that the fault
	 * handler can dereference the mmap offset's poपूर्णांकer to the object.
	 * This reference is cleaned up by the corresponding vm_बंद
	 * (which should happen whether the vma was created by this call, or
	 * by a vm_खोलो due to mremap or partial unmap or whatever).
	 */
	drm_gem_object_get(obj);

	vma->vm_निजी_data = obj;
	vma->vm_ops = obj->funcs->vm_ops;

	अगर (obj->funcs->mmap) अणु
		ret = obj->funcs->mmap(obj, vma);
		अगर (ret)
			जाओ err_drm_gem_object_put;
		WARN_ON(!(vma->vm_flags & VM_DONTEXPAND));
	पूर्ण अन्यथा अणु
		अगर (!vma->vm_ops) अणु
			ret = -EINVAL;
			जाओ err_drm_gem_object_put;
		पूर्ण

		vma->vm_flags |= VM_IO | VM_PFNMAP | VM_DONTEXPAND | VM_DONTDUMP;
		vma->vm_page_prot = pgprot_ग_लिखोcombine(vm_get_page_prot(vma->vm_flags));
		vma->vm_page_prot = pgprot_decrypted(vma->vm_page_prot);
	पूर्ण

	वापस 0;

err_drm_gem_object_put:
	drm_gem_object_put(obj);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_gem_mmap_obj);

/**
 * drm_gem_mmap - memory map routine क्रम GEM objects
 * @filp: DRM file poपूर्णांकer
 * @vma: VMA क्रम the area to be mapped
 *
 * If a driver supports GEM object mapping, mmap calls on the DRM file
 * descriptor will end up here.
 *
 * Look up the GEM object based on the offset passed in (vma->vm_pgoff will
 * contain the fake offset we created when the GTT map ioctl was called on
 * the object) and map it with a call to drm_gem_mmap_obj().
 *
 * If the caller is not granted access to the buffer object, the mmap will fail
 * with EACCES. Please see the vma manager क्रम more inक्रमmation.
 */
पूर्णांक drm_gem_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_file *priv = filp->निजी_data;
	काष्ठा drm_device *dev = priv->minor->dev;
	काष्ठा drm_gem_object *obj = शून्य;
	काष्ठा drm_vma_offset_node *node;
	पूर्णांक ret;

	अगर (drm_dev_is_unplugged(dev))
		वापस -ENODEV;

	drm_vma_offset_lock_lookup(dev->vma_offset_manager);
	node = drm_vma_offset_exact_lookup_locked(dev->vma_offset_manager,
						  vma->vm_pgoff,
						  vma_pages(vma));
	अगर (likely(node)) अणु
		obj = container_of(node, काष्ठा drm_gem_object, vma_node);
		/*
		 * When the object is being मुक्तd, after it hits 0-refcnt it
		 * proceeds to tear करोwn the object. In the process it will
		 * attempt to हटाओ the VMA offset and so acquire this
		 * mgr->vm_lock.  Thereक्रमe अगर we find an object with a 0-refcnt
		 * that matches our range, we know it is in the process of being
		 * destroyed and will be मुक्तd as soon as we release the lock -
		 * so we have to check क्रम the 0-refcnted object and treat it as
		 * invalid.
		 */
		अगर (!kref_get_unless_zero(&obj->refcount))
			obj = शून्य;
	पूर्ण
	drm_vma_offset_unlock_lookup(dev->vma_offset_manager);

	अगर (!obj)
		वापस -EINVAL;

	अगर (!drm_vma_node_is_allowed(node, priv)) अणु
		drm_gem_object_put(obj);
		वापस -EACCES;
	पूर्ण

	अगर (node->पढ़ोonly) अणु
		अगर (vma->vm_flags & VM_WRITE) अणु
			drm_gem_object_put(obj);
			वापस -EINVAL;
		पूर्ण

		vma->vm_flags &= ~VM_MAYWRITE;
	पूर्ण

	ret = drm_gem_mmap_obj(obj, drm_vma_node_size(node) << PAGE_SHIFT,
			       vma);

	drm_gem_object_put(obj);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_gem_mmap);

व्योम drm_gem_prपूर्णांक_info(काष्ठा drm_prपूर्णांकer *p, अचिन्हित पूर्णांक indent,
			स्थिर काष्ठा drm_gem_object *obj)
अणु
	drm_म_लिखो_indent(p, indent, "name=%d\n", obj->name);
	drm_म_लिखो_indent(p, indent, "refcount=%u\n",
			  kref_पढ़ो(&obj->refcount));
	drm_म_लिखो_indent(p, indent, "start=%08lx\n",
			  drm_vma_node_start(&obj->vma_node));
	drm_म_लिखो_indent(p, indent, "size=%zu\n", obj->size);
	drm_म_लिखो_indent(p, indent, "imported=%s\n",
			  obj->import_attach ? "yes" : "no");

	अगर (obj->funcs->prपूर्णांक_info)
		obj->funcs->prपूर्णांक_info(p, indent, obj);
पूर्ण

पूर्णांक drm_gem_pin(काष्ठा drm_gem_object *obj)
अणु
	अगर (obj->funcs->pin)
		वापस obj->funcs->pin(obj);
	अन्यथा
		वापस 0;
पूर्ण

व्योम drm_gem_unpin(काष्ठा drm_gem_object *obj)
अणु
	अगर (obj->funcs->unpin)
		obj->funcs->unpin(obj);
पूर्ण

पूर्णांक drm_gem_vmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map)
अणु
	पूर्णांक ret;

	अगर (!obj->funcs->vmap)
		वापस -EOPNOTSUPP;

	ret = obj->funcs->vmap(obj, map);
	अगर (ret)
		वापस ret;
	अन्यथा अगर (dma_buf_map_is_null(map))
		वापस -ENOMEM;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_gem_vmap);

व्योम drm_gem_vunmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map)
अणु
	अगर (dma_buf_map_is_null(map))
		वापस;

	अगर (obj->funcs->vunmap)
		obj->funcs->vunmap(obj, map);

	/* Always set the mapping to शून्य. Callers may rely on this. */
	dma_buf_map_clear(map);
पूर्ण
EXPORT_SYMBOL(drm_gem_vunmap);

/**
 * drm_gem_lock_reservations - Sets up the ww context and acquires
 * the lock on an array of GEM objects.
 *
 * Once you've locked your reservations, you'll want to set up space
 * क्रम your shared fences (अगर applicable), submit your job, then
 * drm_gem_unlock_reservations().
 *
 * @objs: drm_gem_objects to lock
 * @count: Number of objects in @objs
 * @acquire_ctx: काष्ठा ww_acquire_ctx that will be initialized as
 * part of tracking this set of locked reservations.
 */
पूर्णांक
drm_gem_lock_reservations(काष्ठा drm_gem_object **objs, पूर्णांक count,
			  काष्ठा ww_acquire_ctx *acquire_ctx)
अणु
	पूर्णांक contended = -1;
	पूर्णांक i, ret;

	ww_acquire_init(acquire_ctx, &reservation_ww_class);

retry:
	अगर (contended != -1) अणु
		काष्ठा drm_gem_object *obj = objs[contended];

		ret = dma_resv_lock_slow_पूर्णांकerruptible(obj->resv,
								 acquire_ctx);
		अगर (ret) अणु
			ww_acquire_करोne(acquire_ctx);
			वापस ret;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		अगर (i == contended)
			जारी;

		ret = dma_resv_lock_पूर्णांकerruptible(objs[i]->resv,
							    acquire_ctx);
		अगर (ret) अणु
			पूर्णांक j;

			क्रम (j = 0; j < i; j++)
				dma_resv_unlock(objs[j]->resv);

			अगर (contended != -1 && contended >= i)
				dma_resv_unlock(objs[contended]->resv);

			अगर (ret == -EDEADLK) अणु
				contended = i;
				जाओ retry;
			पूर्ण

			ww_acquire_करोne(acquire_ctx);
			वापस ret;
		पूर्ण
	पूर्ण

	ww_acquire_करोne(acquire_ctx);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_gem_lock_reservations);

व्योम
drm_gem_unlock_reservations(काष्ठा drm_gem_object **objs, पूर्णांक count,
			    काष्ठा ww_acquire_ctx *acquire_ctx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		dma_resv_unlock(objs[i]->resv);

	ww_acquire_fini(acquire_ctx);
पूर्ण
EXPORT_SYMBOL(drm_gem_unlock_reservations);

/**
 * drm_gem_fence_array_add - Adds the fence to an array of fences to be
 * रुकोed on, deduplicating fences from the same context.
 *
 * @fence_array: array of dma_fence * क्रम the job to block on.
 * @fence: the dma_fence to add to the list of dependencies.
 *
 * Returns:
 * 0 on success, or an error on failing to expand the array.
 */
पूर्णांक drm_gem_fence_array_add(काष्ठा xarray *fence_array,
			    काष्ठा dma_fence *fence)
अणु
	काष्ठा dma_fence *entry;
	अचिन्हित दीर्घ index;
	u32 id = 0;
	पूर्णांक ret;

	अगर (!fence)
		वापस 0;

	/* Deduplicate अगर we alपढ़ोy depend on a fence from the same context.
	 * This lets the size of the array of deps scale with the number of
	 * engines involved, rather than the number of BOs.
	 */
	xa_क्रम_each(fence_array, index, entry) अणु
		अगर (entry->context != fence->context)
			जारी;

		अगर (dma_fence_is_later(fence, entry)) अणु
			dma_fence_put(entry);
			xa_store(fence_array, index, fence, GFP_KERNEL);
		पूर्ण अन्यथा अणु
			dma_fence_put(fence);
		पूर्ण
		वापस 0;
	पूर्ण

	ret = xa_alloc(fence_array, &id, fence, xa_limit_32b, GFP_KERNEL);
	अगर (ret != 0)
		dma_fence_put(fence);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_gem_fence_array_add);

/**
 * drm_gem_fence_array_add_implicit - Adds the implicit dependencies tracked
 * in the GEM object's reservation object to an array of dma_fences क्रम use in
 * scheduling a rendering job.
 *
 * This should be called after drm_gem_lock_reservations() on your array of
 * GEM objects used in the job but beक्रमe updating the reservations with your
 * own fences.
 *
 * @fence_array: array of dma_fence * क्रम the job to block on.
 * @obj: the gem object to add new dependencies from.
 * @ग_लिखो: whether the job might ग_लिखो the object (so we need to depend on
 * shared fences in the reservation object).
 */
पूर्णांक drm_gem_fence_array_add_implicit(काष्ठा xarray *fence_array,
				     काष्ठा drm_gem_object *obj,
				     bool ग_लिखो)
अणु
	पूर्णांक ret;
	काष्ठा dma_fence **fences;
	अचिन्हित पूर्णांक i, fence_count;

	अगर (!ग_लिखो) अणु
		काष्ठा dma_fence *fence =
			dma_resv_get_excl_rcu(obj->resv);

		वापस drm_gem_fence_array_add(fence_array, fence);
	पूर्ण

	ret = dma_resv_get_fences_rcu(obj->resv, शून्य,
						&fence_count, &fences);
	अगर (ret || !fence_count)
		वापस ret;

	क्रम (i = 0; i < fence_count; i++) अणु
		ret = drm_gem_fence_array_add(fence_array, fences[i]);
		अगर (ret)
			अवरोध;
	पूर्ण

	क्रम (; i < fence_count; i++)
		dma_fence_put(fences[i]);
	kमुक्त(fences);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_gem_fence_array_add_implicit);
