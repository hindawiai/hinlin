<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * drm gem CMA (contiguous memory allocator) helper functions
 *
 * Copyright (C) 2012 Sascha Hauer, Pengutronix
 *
 * Based on Samsung Exynos code
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 */

#समावेश <linux/dma-buf.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_vma_manager.h>

/**
 * DOC: cma helpers
 *
 * The Contiguous Memory Allocator reserves a pool of memory at early boot
 * that is used to service requests क्रम large blocks of contiguous memory.
 *
 * The DRM GEM/CMA helpers use this allocator as a means to provide buffer
 * objects that are physically contiguous in memory. This is useful क्रम
 * display drivers that are unable to map scattered buffers via an IOMMU.
 */

अटल स्थिर काष्ठा drm_gem_object_funcs drm_gem_cma_शेष_funcs = अणु
	.मुक्त = drm_gem_cma_मुक्त_object,
	.prपूर्णांक_info = drm_gem_cma_prपूर्णांक_info,
	.get_sg_table = drm_gem_cma_get_sg_table,
	.vmap = drm_gem_cma_vmap,
	.mmap = drm_gem_cma_mmap,
	.vm_ops = &drm_gem_cma_vm_ops,
पूर्ण;

/**
 * __drm_gem_cma_create - Create a GEM CMA object without allocating memory
 * @drm: DRM device
 * @size: size of the object to allocate
 *
 * This function creates and initializes a GEM CMA object of the given size,
 * but करोesn't allocate any memory to back the object.
 *
 * Returns:
 * A काष्ठा drm_gem_cma_object * on success or an ERR_PTR()-encoded negative
 * error code on failure.
 */
अटल काष्ठा drm_gem_cma_object *
__drm_gem_cma_create(काष्ठा drm_device *drm, माप_प्रकार size)
अणु
	काष्ठा drm_gem_cma_object *cma_obj;
	काष्ठा drm_gem_object *gem_obj;
	पूर्णांक ret;

	अगर (drm->driver->gem_create_object)
		gem_obj = drm->driver->gem_create_object(drm, size);
	अन्यथा
		gem_obj = kzalloc(माप(*cma_obj), GFP_KERNEL);
	अगर (!gem_obj)
		वापस ERR_PTR(-ENOMEM);

	अगर (!gem_obj->funcs)
		gem_obj->funcs = &drm_gem_cma_शेष_funcs;

	cma_obj = container_of(gem_obj, काष्ठा drm_gem_cma_object, base);

	ret = drm_gem_object_init(drm, gem_obj, size);
	अगर (ret)
		जाओ error;

	ret = drm_gem_create_mmap_offset(gem_obj);
	अगर (ret) अणु
		drm_gem_object_release(gem_obj);
		जाओ error;
	पूर्ण

	वापस cma_obj;

error:
	kमुक्त(cma_obj);
	वापस ERR_PTR(ret);
पूर्ण

/**
 * drm_gem_cma_create - allocate an object with the given size
 * @drm: DRM device
 * @size: size of the object to allocate
 *
 * This function creates a CMA GEM object and allocates a contiguous chunk of
 * memory as backing store. The backing memory has the ग_लिखोcombine attribute
 * set.
 *
 * Returns:
 * A काष्ठा drm_gem_cma_object * on success or an ERR_PTR()-encoded negative
 * error code on failure.
 */
काष्ठा drm_gem_cma_object *drm_gem_cma_create(काष्ठा drm_device *drm,
					      माप_प्रकार size)
अणु
	काष्ठा drm_gem_cma_object *cma_obj;
	पूर्णांक ret;

	size = round_up(size, PAGE_SIZE);

	cma_obj = __drm_gem_cma_create(drm, size);
	अगर (IS_ERR(cma_obj))
		वापस cma_obj;

	cma_obj->vaddr = dma_alloc_wc(drm->dev, size, &cma_obj->paddr,
				      GFP_KERNEL | __GFP_NOWARN);
	अगर (!cma_obj->vaddr) अणु
		drm_dbg(drm, "failed to allocate buffer with size %zu\n",
			 size);
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	वापस cma_obj;

error:
	drm_gem_object_put(&cma_obj->base);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_cma_create);

/**
 * drm_gem_cma_create_with_handle - allocate an object with the given size and
 *     वापस a GEM handle to it
 * @file_priv: DRM file-निजी काष्ठाure to रेजिस्टर the handle क्रम
 * @drm: DRM device
 * @size: size of the object to allocate
 * @handle: वापस location क्रम the GEM handle
 *
 * This function creates a CMA GEM object, allocating a physically contiguous
 * chunk of memory as backing store. The GEM object is then added to the list
 * of object associated with the given file and a handle to it is वापसed.
 *
 * Returns:
 * A काष्ठा drm_gem_cma_object * on success or an ERR_PTR()-encoded negative
 * error code on failure.
 */
अटल काष्ठा drm_gem_cma_object *
drm_gem_cma_create_with_handle(काष्ठा drm_file *file_priv,
			       काष्ठा drm_device *drm, माप_प्रकार size,
			       uपूर्णांक32_t *handle)
अणु
	काष्ठा drm_gem_cma_object *cma_obj;
	काष्ठा drm_gem_object *gem_obj;
	पूर्णांक ret;

	cma_obj = drm_gem_cma_create(drm, size);
	अगर (IS_ERR(cma_obj))
		वापस cma_obj;

	gem_obj = &cma_obj->base;

	/*
	 * allocate a id of idr table where the obj is रेजिस्टरed
	 * and handle has the id what user can see.
	 */
	ret = drm_gem_handle_create(file_priv, gem_obj, handle);
	/* drop reference from allocate - handle holds it now. */
	drm_gem_object_put(gem_obj);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस cma_obj;
पूर्ण

/**
 * drm_gem_cma_मुक्त_object - मुक्त resources associated with a CMA GEM object
 * @gem_obj: GEM object to मुक्त
 *
 * This function मुक्तs the backing memory of the CMA GEM object, cleans up the
 * GEM object state and मुक्तs the memory used to store the object itself.
 * If the buffer is imported and the भव address is set, it is released.
 * Drivers using the CMA helpers should set this as their
 * &drm_gem_object_funcs.मुक्त callback.
 */
व्योम drm_gem_cma_मुक्त_object(काष्ठा drm_gem_object *gem_obj)
अणु
	काष्ठा drm_gem_cma_object *cma_obj = to_drm_gem_cma_obj(gem_obj);
	काष्ठा dma_buf_map map = DMA_BUF_MAP_INIT_VADDR(cma_obj->vaddr);

	अगर (gem_obj->import_attach) अणु
		अगर (cma_obj->vaddr)
			dma_buf_vunmap(gem_obj->import_attach->dmabuf, &map);
		drm_prime_gem_destroy(gem_obj, cma_obj->sgt);
	पूर्ण अन्यथा अगर (cma_obj->vaddr) अणु
		dma_मुक्त_wc(gem_obj->dev->dev, cma_obj->base.size,
			    cma_obj->vaddr, cma_obj->paddr);
	पूर्ण

	drm_gem_object_release(gem_obj);

	kमुक्त(cma_obj);
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_cma_मुक्त_object);

/**
 * drm_gem_cma_dumb_create_पूर्णांकernal - create a dumb buffer object
 * @file_priv: DRM file-निजी काष्ठाure to create the dumb buffer क्रम
 * @drm: DRM device
 * @args: IOCTL data
 *
 * This aligns the pitch and size arguments to the minimum required. This is
 * an पूर्णांकernal helper that can be wrapped by a driver to account क्रम hardware
 * with more specअगरic alignment requirements. It should not be used directly
 * as their &drm_driver.dumb_create callback.
 *
 * Returns:
 * 0 on success or a negative error code on failure.
 */
पूर्णांक drm_gem_cma_dumb_create_पूर्णांकernal(काष्ठा drm_file *file_priv,
				     काष्ठा drm_device *drm,
				     काष्ठा drm_mode_create_dumb *args)
अणु
	अचिन्हित पूर्णांक min_pitch = DIV_ROUND_UP(args->width * args->bpp, 8);
	काष्ठा drm_gem_cma_object *cma_obj;

	अगर (args->pitch < min_pitch)
		args->pitch = min_pitch;

	अगर (args->size < args->pitch * args->height)
		args->size = args->pitch * args->height;

	cma_obj = drm_gem_cma_create_with_handle(file_priv, drm, args->size,
						 &args->handle);
	वापस PTR_ERR_OR_ZERO(cma_obj);
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_cma_dumb_create_पूर्णांकernal);

/**
 * drm_gem_cma_dumb_create - create a dumb buffer object
 * @file_priv: DRM file-निजी काष्ठाure to create the dumb buffer क्रम
 * @drm: DRM device
 * @args: IOCTL data
 *
 * This function computes the pitch of the dumb buffer and rounds it up to an
 * पूर्णांकeger number of bytes per pixel. Drivers क्रम hardware that करोesn't have
 * any additional restrictions on the pitch can directly use this function as
 * their &drm_driver.dumb_create callback.
 *
 * For hardware with additional restrictions, drivers can adjust the fields
 * set up by userspace and pass the IOCTL data aदीर्घ to the
 * drm_gem_cma_dumb_create_पूर्णांकernal() function.
 *
 * Returns:
 * 0 on success or a negative error code on failure.
 */
पूर्णांक drm_gem_cma_dumb_create(काष्ठा drm_file *file_priv,
			    काष्ठा drm_device *drm,
			    काष्ठा drm_mode_create_dumb *args)
अणु
	काष्ठा drm_gem_cma_object *cma_obj;

	args->pitch = DIV_ROUND_UP(args->width * args->bpp, 8);
	args->size = args->pitch * args->height;

	cma_obj = drm_gem_cma_create_with_handle(file_priv, drm, args->size,
						 &args->handle);
	वापस PTR_ERR_OR_ZERO(cma_obj);
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_cma_dumb_create);

स्थिर काष्ठा vm_operations_काष्ठा drm_gem_cma_vm_ops = अणु
	.खोलो = drm_gem_vm_खोलो,
	.बंद = drm_gem_vm_बंद,
पूर्ण;
EXPORT_SYMBOL_GPL(drm_gem_cma_vm_ops);

#अगर_अघोषित CONFIG_MMU
/**
 * drm_gem_cma_get_unmapped_area - propose address क्रम mapping in noMMU हालs
 * @filp: file object
 * @addr: memory address
 * @len: buffer size
 * @pgoff: page offset
 * @flags: memory flags
 *
 * This function is used in noMMU platक्रमms to propose address mapping
 * क्रम a given buffer.
 * It's पूर्णांकended to be used as a direct handler क्रम the काष्ठा
 * &file_operations.get_unmapped_area operation.
 *
 * Returns:
 * mapping address on success or a negative error code on failure.
 */
अचिन्हित दीर्घ drm_gem_cma_get_unmapped_area(काष्ठा file *filp,
					    अचिन्हित दीर्घ addr,
					    अचिन्हित दीर्घ len,
					    अचिन्हित दीर्घ pgoff,
					    अचिन्हित दीर्घ flags)
अणु
	काष्ठा drm_gem_cma_object *cma_obj;
	काष्ठा drm_gem_object *obj = शून्य;
	काष्ठा drm_file *priv = filp->निजी_data;
	काष्ठा drm_device *dev = priv->minor->dev;
	काष्ठा drm_vma_offset_node *node;

	अगर (drm_dev_is_unplugged(dev))
		वापस -ENODEV;

	drm_vma_offset_lock_lookup(dev->vma_offset_manager);
	node = drm_vma_offset_exact_lookup_locked(dev->vma_offset_manager,
						  pgoff,
						  len >> PAGE_SHIFT);
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

	cma_obj = to_drm_gem_cma_obj(obj);

	drm_gem_object_put(obj);

	वापस cma_obj->vaddr ? (अचिन्हित दीर्घ)cma_obj->vaddr : -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_cma_get_unmapped_area);
#पूर्ण_अगर

/**
 * drm_gem_cma_prपूर्णांक_info() - Prपूर्णांक &drm_gem_cma_object info क्रम debugfs
 * @p: DRM prपूर्णांकer
 * @indent: Tab indentation level
 * @obj: GEM object
 *
 * This function can be used as the &drm_driver->gem_prपूर्णांक_info callback.
 * It prपूर्णांकs paddr and vaddr क्रम use in e.g. debugfs output.
 */
व्योम drm_gem_cma_prपूर्णांक_info(काष्ठा drm_prपूर्णांकer *p, अचिन्हित पूर्णांक indent,
			    स्थिर काष्ठा drm_gem_object *obj)
अणु
	स्थिर काष्ठा drm_gem_cma_object *cma_obj = to_drm_gem_cma_obj(obj);

	drm_म_लिखो_indent(p, indent, "paddr=%pad\n", &cma_obj->paddr);
	drm_म_लिखो_indent(p, indent, "vaddr=%p\n", cma_obj->vaddr);
पूर्ण
EXPORT_SYMBOL(drm_gem_cma_prपूर्णांक_info);

/**
 * drm_gem_cma_get_sg_table - provide a scatter/gather table of pinned
 *     pages क्रम a CMA GEM object
 * @obj: GEM object
 *
 * This function exports a scatter/gather table by
 * calling the standard DMA mapping API. Drivers using the CMA helpers should
 * set this as their &drm_gem_object_funcs.get_sg_table callback.
 *
 * Returns:
 * A poपूर्णांकer to the scatter/gather table of pinned pages or शून्य on failure.
 */
काष्ठा sg_table *drm_gem_cma_get_sg_table(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा drm_gem_cma_object *cma_obj = to_drm_gem_cma_obj(obj);
	काष्ठा sg_table *sgt;
	पूर्णांक ret;

	sgt = kzalloc(माप(*sgt), GFP_KERNEL);
	अगर (!sgt)
		वापस ERR_PTR(-ENOMEM);

	ret = dma_get_sgtable(obj->dev->dev, sgt, cma_obj->vaddr,
			      cma_obj->paddr, obj->size);
	अगर (ret < 0)
		जाओ out;

	वापस sgt;

out:
	kमुक्त(sgt);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_cma_get_sg_table);

/**
 * drm_gem_cma_prime_import_sg_table - produce a CMA GEM object from another
 *     driver's scatter/gather table of pinned pages
 * @dev: device to import पूर्णांकo
 * @attach: DMA-BUF attachment
 * @sgt: scatter/gather table of pinned pages
 *
 * This function imports a scatter/gather table exported via DMA-BUF by
 * another driver. Imported buffers must be physically contiguous in memory
 * (i.e. the scatter/gather table must contain a single entry). Drivers that
 * use the CMA helpers should set this as their
 * &drm_driver.gem_prime_import_sg_table callback.
 *
 * Returns:
 * A poपूर्णांकer to a newly created GEM object or an ERR_PTR-encoded negative
 * error code on failure.
 */
काष्ठा drm_gem_object *
drm_gem_cma_prime_import_sg_table(काष्ठा drm_device *dev,
				  काष्ठा dma_buf_attachment *attach,
				  काष्ठा sg_table *sgt)
अणु
	काष्ठा drm_gem_cma_object *cma_obj;

	/* check अगर the entries in the sg_table are contiguous */
	अगर (drm_prime_get_contiguous_size(sgt) < attach->dmabuf->size)
		वापस ERR_PTR(-EINVAL);

	/* Create a CMA GEM buffer. */
	cma_obj = __drm_gem_cma_create(dev, attach->dmabuf->size);
	अगर (IS_ERR(cma_obj))
		वापस ERR_CAST(cma_obj);

	cma_obj->paddr = sg_dma_address(sgt->sgl);
	cma_obj->sgt = sgt;

	DRM_DEBUG_PRIME("dma_addr = %pad, size = %zu\n", &cma_obj->paddr, attach->dmabuf->size);

	वापस &cma_obj->base;
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_cma_prime_import_sg_table);

/**
 * drm_gem_cma_vmap - map a CMA GEM object पूर्णांकo the kernel's भव
 *     address space
 * @obj: GEM object
 * @map: Returns the kernel भव address of the CMA GEM object's backing
 *       store.
 *
 * This function maps a buffer पूर्णांकo the kernel's
 * भव address space. Since the CMA buffers are alपढ़ोy mapped पूर्णांकo the
 * kernel भव address space this simply वापसs the cached भव
 * address. Drivers using the CMA helpers should set this as their DRM
 * driver's &drm_gem_object_funcs.vmap callback.
 *
 * Returns:
 * 0 on success, or a negative error code otherwise.
 */
पूर्णांक drm_gem_cma_vmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map)
अणु
	काष्ठा drm_gem_cma_object *cma_obj = to_drm_gem_cma_obj(obj);

	dma_buf_map_set_vaddr(map, cma_obj->vaddr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_cma_vmap);

/**
 * drm_gem_cma_mmap - memory-map an exported CMA GEM object
 * @obj: GEM object
 * @vma: VMA क्रम the area to be mapped
 *
 * This function maps a buffer पूर्णांकo a userspace process's address space.
 * In addition to the usual GEM VMA setup it immediately faults in the entire
 * object instead of using on-demand faulting. Drivers that use the CMA
 * helpers should set this as their &drm_gem_object_funcs.mmap callback.
 *
 * Returns:
 * 0 on success or a negative error code on failure.
 */
पूर्णांक drm_gem_cma_mmap(काष्ठा drm_gem_object *obj, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा drm_gem_cma_object *cma_obj;
	पूर्णांक ret;

	/*
	 * Clear the VM_PFNMAP flag that was set by drm_gem_mmap(), and set the
	 * vm_pgoff (used as a fake buffer offset by DRM) to 0 as we want to map
	 * the whole buffer.
	 */
	vma->vm_pgoff -= drm_vma_node_start(&obj->vma_node);
	vma->vm_flags &= ~VM_PFNMAP;

	cma_obj = to_drm_gem_cma_obj(obj);

	ret = dma_mmap_wc(cma_obj->base.dev->dev, vma, cma_obj->vaddr,
			  cma_obj->paddr, vma->vm_end - vma->vm_start);
	अगर (ret)
		drm_gem_vm_बंद(vma);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(drm_gem_cma_mmap);

/**
 * drm_gem_cma_prime_import_sg_table_vmap - PRIME import another driver's
 *	scatter/gather table and get the भव address of the buffer
 * @dev: DRM device
 * @attach: DMA-BUF attachment
 * @sgt: Scatter/gather table of pinned pages
 *
 * This function imports a scatter/gather table using
 * drm_gem_cma_prime_import_sg_table() and uses dma_buf_vmap() to get the kernel
 * भव address. This ensures that a CMA GEM object always has its भव
 * address set. This address is released when the object is मुक्तd.
 *
 * This function can be used as the &drm_driver.gem_prime_import_sg_table
 * callback. The &DRM_GEM_CMA_DRIVER_OPS_VMAP macro provides a लघुcut to set
 * the necessary DRM driver operations.
 *
 * Returns:
 * A poपूर्णांकer to a newly created GEM object or an ERR_PTR-encoded negative
 * error code on failure.
 */
काष्ठा drm_gem_object *
drm_gem_cma_prime_import_sg_table_vmap(काष्ठा drm_device *dev,
				       काष्ठा dma_buf_attachment *attach,
				       काष्ठा sg_table *sgt)
अणु
	काष्ठा drm_gem_cma_object *cma_obj;
	काष्ठा drm_gem_object *obj;
	काष्ठा dma_buf_map map;
	पूर्णांक ret;

	ret = dma_buf_vmap(attach->dmabuf, &map);
	अगर (ret) अणु
		DRM_ERROR("Failed to vmap PRIME buffer\n");
		वापस ERR_PTR(ret);
	पूर्ण

	obj = drm_gem_cma_prime_import_sg_table(dev, attach, sgt);
	अगर (IS_ERR(obj)) अणु
		dma_buf_vunmap(attach->dmabuf, &map);
		वापस obj;
	पूर्ण

	cma_obj = to_drm_gem_cma_obj(obj);
	cma_obj->vaddr = map.vaddr;

	वापस obj;
पूर्ण
EXPORT_SYMBOL(drm_gem_cma_prime_import_sg_table_vmap);
