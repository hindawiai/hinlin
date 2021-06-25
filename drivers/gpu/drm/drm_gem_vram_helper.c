<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/dma-buf-map.h>
#समावेश <linux/module.h>

#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_framebuffer.h>
#समावेश <drm/drm_gem_atomic_helper.h>
#समावेश <drm/drm_gem_tपंचांग_helper.h>
#समावेश <drm/drm_gem_vram_helper.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_mode.h>
#समावेश <drm/drm_plane.h>
#समावेश <drm/drm_prime.h>
#समावेश <drm/drm_simple_kms_helper.h>

अटल स्थिर काष्ठा drm_gem_object_funcs drm_gem_vram_object_funcs;

/**
 * DOC: overview
 *
 * This library provides &काष्ठा drm_gem_vram_object (GEM VRAM), a GEM
 * buffer object that is backed by video RAM (VRAM). It can be used क्रम
 * framebuffer devices with dedicated memory.
 *
 * The data काष्ठाure &काष्ठा drm_vram_mm and its helpers implement a memory
 * manager क्रम simple framebuffer devices with dedicated video memory. GEM
 * VRAM buffer objects are either placed in the video memory or reमुख्य evicted
 * to प्रणाली memory.
 *
 * With the GEM पूर्णांकerface userspace applications create, manage and destroy
 * graphics buffers, such as an on-screen framebuffer. GEM करोes not provide
 * an implementation of these पूर्णांकerfaces. It's up to the DRM driver to
 * provide an implementation that suits the hardware. If the hardware device
 * contains dedicated video memory, the DRM driver can use the VRAM helper
 * library. Each active buffer object is stored in video RAM. Active
 * buffer are used क्रम drawing the current frame, typically something like
 * the frame's scanout buffer or the cursor image. If there's no more space
 * left in VRAM, inactive GEM objects can be moved to प्रणाली memory.
 *
 * To initialize the VRAM helper library call drmm_vram_helper_alloc_mm().
 * The function allocates and initializes an instance of &काष्ठा drm_vram_mm
 * in &काष्ठा drm_device.vram_mm . Use &DRM_GEM_VRAM_DRIVER to initialize
 * &काष्ठा drm_driver and  &DRM_VRAM_MM_खाता_OPERATIONS to initialize
 * &काष्ठा file_operations; as illustrated below.
 *
 * .. code-block:: c
 *
 *	काष्ठा file_operations fops =अणु
 *		.owner = THIS_MODULE,
 *		DRM_VRAM_MM_खाता_OPERATION
 *	पूर्ण;
 *	काष्ठा drm_driver drv = अणु
 *		.driver_feature = DRM_ ... ,
 *		.fops = &fops,
 *		DRM_GEM_VRAM_DRIVER
 *	पूर्ण;
 *
 *	पूर्णांक init_drm_driver()
 *	अणु
 *		काष्ठा drm_device *dev;
 *		uपूर्णांक64_t vram_base;
 *		अचिन्हित दीर्घ vram_size;
 *		पूर्णांक ret;
 *
 *		// setup device, vram base and size
 *		// ...
 *
 *		ret = drmm_vram_helper_alloc_mm(dev, vram_base, vram_size);
 *		अगर (ret)
 *			वापस ret;
 *		वापस 0;
 *	पूर्ण
 *
 * This creates an instance of &काष्ठा drm_vram_mm, exports DRM userspace
 * पूर्णांकerfaces क्रम GEM buffer management and initializes file operations to
 * allow क्रम accessing created GEM buffers. With this setup, the DRM driver
 * manages an area of video RAM with VRAM MM and provides GEM VRAM objects
 * to userspace.
 *
 * You करोn't have to clean up the instance of VRAM MM.
 * drmm_vram_helper_alloc_mm() is a managed पूर्णांकerface that installs a
 * clean-up handler to run during the DRM device's release.
 *
 * For drawing or scanout operations, rsp. buffer objects have to be pinned
 * in video RAM. Call drm_gem_vram_pin() with &DRM_GEM_VRAM_PL_FLAG_VRAM or
 * &DRM_GEM_VRAM_PL_FLAG_SYSTEM to pin a buffer object in video RAM or प्रणाली
 * memory. Call drm_gem_vram_unpin() to release the pinned object afterwards.
 *
 * A buffer object that is pinned in video RAM has a fixed address within that
 * memory region. Call drm_gem_vram_offset() to retrieve this value. Typically
 * it's used to program the hardware's scanout engine क्रम framebuffers, set
 * the cursor overlay's image क्रम a mouse cursor, or use it as input to the
 * hardware's draing engine.
 *
 * To access a buffer object's memory from the DRM driver, call
 * drm_gem_vram_vmap(). It maps the buffer पूर्णांकo kernel address
 * space and वापसs the memory address. Use drm_gem_vram_vunmap() to
 * release the mapping.
 */

/*
 * Buffer-objects helpers
 */

अटल व्योम drm_gem_vram_cleanup(काष्ठा drm_gem_vram_object *gbo)
अणु
	/* We got here via tपंचांग_bo_put(), which means that the
	 * TTM buffer object in 'bo' has alपढ़ोy been cleaned
	 * up; only release the GEM object.
	 */

	WARN_ON(gbo->vmap_use_count);
	WARN_ON(dma_buf_map_is_set(&gbo->map));

	drm_gem_object_release(&gbo->bo.base);
पूर्ण

अटल व्योम drm_gem_vram_destroy(काष्ठा drm_gem_vram_object *gbo)
अणु
	drm_gem_vram_cleanup(gbo);
	kमुक्त(gbo);
पूर्ण

अटल व्योम tपंचांग_buffer_object_destroy(काष्ठा tपंचांग_buffer_object *bo)
अणु
	काष्ठा drm_gem_vram_object *gbo = drm_gem_vram_of_bo(bo);

	drm_gem_vram_destroy(gbo);
पूर्ण

अटल व्योम drm_gem_vram_placement(काष्ठा drm_gem_vram_object *gbo,
				   अचिन्हित दीर्घ pl_flag)
अणु
	u32 invariant_flags = 0;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक c = 0;

	अगर (pl_flag & DRM_GEM_VRAM_PL_FLAG_TOPDOWN)
		invariant_flags = TTM_PL_FLAG_TOPDOWN;

	gbo->placement.placement = gbo->placements;
	gbo->placement.busy_placement = gbo->placements;

	अगर (pl_flag & DRM_GEM_VRAM_PL_FLAG_VRAM) अणु
		gbo->placements[c].mem_type = TTM_PL_VRAM;
		gbo->placements[c++].flags = invariant_flags;
	पूर्ण

	अगर (pl_flag & DRM_GEM_VRAM_PL_FLAG_SYSTEM || !c) अणु
		gbo->placements[c].mem_type = TTM_PL_SYSTEM;
		gbo->placements[c++].flags = invariant_flags;
	पूर्ण

	gbo->placement.num_placement = c;
	gbo->placement.num_busy_placement = c;

	क्रम (i = 0; i < c; ++i) अणु
		gbo->placements[i].fpfn = 0;
		gbo->placements[i].lpfn = 0;
	पूर्ण
पूर्ण

/**
 * drm_gem_vram_create() - Creates a VRAM-backed GEM object
 * @dev:		the DRM device
 * @size:		the buffer size in bytes
 * @pg_align:		the buffer's alignment in multiples of the page size
 *
 * GEM objects are allocated by calling काष्ठा drm_driver.gem_create_object,
 * अगर set. Otherwise kzalloc() will be used. Drivers can set their own GEM
 * object functions in काष्ठा drm_driver.gem_create_object. If no functions
 * are set, the new GEM object will use the शेष functions from GEM VRAM
 * helpers.
 *
 * Returns:
 * A new instance of &काष्ठा drm_gem_vram_object on success, or
 * an ERR_PTR()-encoded error code otherwise.
 */
काष्ठा drm_gem_vram_object *drm_gem_vram_create(काष्ठा drm_device *dev,
						माप_प्रकार size,
						अचिन्हित दीर्घ pg_align)
अणु
	काष्ठा drm_gem_vram_object *gbo;
	काष्ठा drm_gem_object *gem;
	काष्ठा drm_vram_mm *vmm = dev->vram_mm;
	काष्ठा tपंचांग_device *bdev;
	पूर्णांक ret;

	अगर (WARN_ONCE(!vmm, "VRAM MM not initialized"))
		वापस ERR_PTR(-EINVAL);

	अगर (dev->driver->gem_create_object) अणु
		gem = dev->driver->gem_create_object(dev, size);
		अगर (!gem)
			वापस ERR_PTR(-ENOMEM);
		gbo = drm_gem_vram_of_gem(gem);
	पूर्ण अन्यथा अणु
		gbo = kzalloc(माप(*gbo), GFP_KERNEL);
		अगर (!gbo)
			वापस ERR_PTR(-ENOMEM);
		gem = &gbo->bo.base;
	पूर्ण

	अगर (!gem->funcs)
		gem->funcs = &drm_gem_vram_object_funcs;

	ret = drm_gem_object_init(dev, gem, size);
	अगर (ret) अणु
		kमुक्त(gbo);
		वापस ERR_PTR(ret);
	पूर्ण

	bdev = &vmm->bdev;

	gbo->bo.bdev = bdev;
	drm_gem_vram_placement(gbo, DRM_GEM_VRAM_PL_FLAG_SYSTEM);

	/*
	 * A failing tपंचांग_bo_init will call tपंचांग_buffer_object_destroy
	 * to release gbo->bo.base and kमुक्त gbo.
	 */
	ret = tपंचांग_bo_init(bdev, &gbo->bo, size, tपंचांग_bo_type_device,
			  &gbo->placement, pg_align, false, शून्य, शून्य,
			  tपंचांग_buffer_object_destroy);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस gbo;
पूर्ण
EXPORT_SYMBOL(drm_gem_vram_create);

/**
 * drm_gem_vram_put() - Releases a reference to a VRAM-backed GEM object
 * @gbo:	the GEM VRAM object
 *
 * See tपंचांग_bo_put() क्रम more inक्रमmation.
 */
व्योम drm_gem_vram_put(काष्ठा drm_gem_vram_object *gbo)
अणु
	tपंचांग_bo_put(&gbo->bo);
पूर्ण
EXPORT_SYMBOL(drm_gem_vram_put);

/**
 * drm_gem_vram_mmap_offset() - Returns a GEM VRAM object's mmap offset
 * @gbo:	the GEM VRAM object
 *
 * See drm_vma_node_offset_addr() क्रम more inक्रमmation.
 *
 * Returns:
 * The buffer object's offset क्रम userspace mappings on success, or
 * 0 अगर no offset is allocated.
 */
u64 drm_gem_vram_mmap_offset(काष्ठा drm_gem_vram_object *gbo)
अणु
	वापस drm_vma_node_offset_addr(&gbo->bo.base.vma_node);
पूर्ण
EXPORT_SYMBOL(drm_gem_vram_mmap_offset);

अटल u64 drm_gem_vram_pg_offset(काष्ठा drm_gem_vram_object *gbo)
अणु
	/* Keep TTM behavior क्रम now, हटाओ when drivers are audited */
	अगर (WARN_ON_ONCE(!gbo->bo.mem.mm_node))
		वापस 0;

	वापस gbo->bo.mem.start;
पूर्ण

/**
 * drm_gem_vram_offset() - \
	Returns a GEM VRAM object's offset in video memory
 * @gbo:	the GEM VRAM object
 *
 * This function वापसs the buffer object's offset in the device's video
 * memory. The buffer object has to be pinned to %TTM_PL_VRAM.
 *
 * Returns:
 * The buffer object's offset in video memory on success, or
 * a negative त्रुटि_सं code otherwise.
 */
s64 drm_gem_vram_offset(काष्ठा drm_gem_vram_object *gbo)
अणु
	अगर (WARN_ON_ONCE(!gbo->bo.pin_count))
		वापस (s64)-ENODEV;
	वापस drm_gem_vram_pg_offset(gbo) << PAGE_SHIFT;
पूर्ण
EXPORT_SYMBOL(drm_gem_vram_offset);

अटल पूर्णांक drm_gem_vram_pin_locked(काष्ठा drm_gem_vram_object *gbo,
				   अचिन्हित दीर्घ pl_flag)
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु false, false पूर्ण;
	पूर्णांक ret;

	अगर (gbo->bo.pin_count)
		जाओ out;

	अगर (pl_flag)
		drm_gem_vram_placement(gbo, pl_flag);

	ret = tपंचांग_bo_validate(&gbo->bo, &gbo->placement, &ctx);
	अगर (ret < 0)
		वापस ret;

out:
	tपंचांग_bo_pin(&gbo->bo);

	वापस 0;
पूर्ण

/**
 * drm_gem_vram_pin() - Pins a GEM VRAM object in a region.
 * @gbo:	the GEM VRAM object
 * @pl_flag:	a biपंचांगask of possible memory regions
 *
 * Pinning a buffer object ensures that it is not evicted from
 * a memory region. A pinned buffer object has to be unpinned beक्रमe
 * it can be pinned to another region. If the pl_flag argument is 0,
 * the buffer is pinned at its current location (video RAM or प्रणाली
 * memory).
 *
 * Small buffer objects, such as cursor images, can lead to memory
 * fragmentation अगर they are pinned in the middle of video RAM. This
 * is especially a problem on devices with only a small amount of
 * video RAM. Fragmentation can prevent the primary framebuffer from
 * fitting in, even though there's enough memory overall. The modअगरier
 * DRM_GEM_VRAM_PL_FLAG_TOPDOWN marks the buffer object to be pinned
 * at the high end of the memory region to aव्योम fragmentation.
 *
 * Returns:
 * 0 on success, or
 * a negative error code otherwise.
 */
पूर्णांक drm_gem_vram_pin(काष्ठा drm_gem_vram_object *gbo, अचिन्हित दीर्घ pl_flag)
अणु
	पूर्णांक ret;

	ret = tपंचांग_bo_reserve(&gbo->bo, true, false, शून्य);
	अगर (ret)
		वापस ret;
	ret = drm_gem_vram_pin_locked(gbo, pl_flag);
	tपंचांग_bo_unreserve(&gbo->bo);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_gem_vram_pin);

अटल व्योम drm_gem_vram_unpin_locked(काष्ठा drm_gem_vram_object *gbo)
अणु
	tपंचांग_bo_unpin(&gbo->bo);
पूर्ण

/**
 * drm_gem_vram_unpin() - Unpins a GEM VRAM object
 * @gbo:	the GEM VRAM object
 *
 * Returns:
 * 0 on success, or
 * a negative error code otherwise.
 */
पूर्णांक drm_gem_vram_unpin(काष्ठा drm_gem_vram_object *gbo)
अणु
	पूर्णांक ret;

	ret = tपंचांग_bo_reserve(&gbo->bo, true, false, शून्य);
	अगर (ret)
		वापस ret;

	drm_gem_vram_unpin_locked(gbo);
	tपंचांग_bo_unreserve(&gbo->bo);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_gem_vram_unpin);

अटल पूर्णांक drm_gem_vram_kmap_locked(काष्ठा drm_gem_vram_object *gbo,
				    काष्ठा dma_buf_map *map)
अणु
	पूर्णांक ret;

	अगर (gbo->vmap_use_count > 0)
		जाओ out;

	/*
	 * VRAM helpers unmap the BO only on demand. So the previous
	 * page mapping might still be around. Only vmap अगर the there's
	 * no mapping present.
	 */
	अगर (dma_buf_map_is_null(&gbo->map)) अणु
		ret = tपंचांग_bo_vmap(&gbo->bo, &gbo->map);
		अगर (ret)
			वापस ret;
	पूर्ण

out:
	++gbo->vmap_use_count;
	*map = gbo->map;

	वापस 0;
पूर्ण

अटल व्योम drm_gem_vram_kunmap_locked(काष्ठा drm_gem_vram_object *gbo,
				       काष्ठा dma_buf_map *map)
अणु
	काष्ठा drm_device *dev = gbo->bo.base.dev;

	अगर (drm_WARN_ON_ONCE(dev, !gbo->vmap_use_count))
		वापस;

	अगर (drm_WARN_ON_ONCE(dev, !dma_buf_map_is_equal(&gbo->map, map)))
		वापस; /* BUG: map not mapped from this BO */

	अगर (--gbo->vmap_use_count > 0)
		वापस;

	/*
	 * Permanently mapping and unmapping buffers adds overhead from
	 * updating the page tables and creates debugging output. Thereक्रमe,
	 * we delay the actual unmap operation until the BO माला_लो evicted
	 * from memory. See drm_gem_vram_bo_driver_move_notअगरy().
	 */
पूर्ण

/**
 * drm_gem_vram_vmap() - Pins and maps a GEM VRAM object पूर्णांकo kernel address
 *                       space
 * @gbo: The GEM VRAM object to map
 * @map: Returns the kernel भव address of the VRAM GEM object's backing
 *       store.
 *
 * The vmap function pins a GEM VRAM object to its current location, either
 * प्रणाली or video memory, and maps its buffer पूर्णांकo kernel address space.
 * As pinned object cannot be relocated, you should aव्योम pinning objects
 * permanently. Call drm_gem_vram_vunmap() with the वापसed address to
 * unmap and unpin the GEM VRAM object.
 *
 * Returns:
 * 0 on success, or a negative error code otherwise.
 */
पूर्णांक drm_gem_vram_vmap(काष्ठा drm_gem_vram_object *gbo, काष्ठा dma_buf_map *map)
अणु
	पूर्णांक ret;

	ret = tपंचांग_bo_reserve(&gbo->bo, true, false, शून्य);
	अगर (ret)
		वापस ret;

	ret = drm_gem_vram_pin_locked(gbo, 0);
	अगर (ret)
		जाओ err_tपंचांग_bo_unreserve;
	ret = drm_gem_vram_kmap_locked(gbo, map);
	अगर (ret)
		जाओ err_drm_gem_vram_unpin_locked;

	tपंचांग_bo_unreserve(&gbo->bo);

	वापस 0;

err_drm_gem_vram_unpin_locked:
	drm_gem_vram_unpin_locked(gbo);
err_tपंचांग_bo_unreserve:
	tपंचांग_bo_unreserve(&gbo->bo);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_gem_vram_vmap);

/**
 * drm_gem_vram_vunmap() - Unmaps and unpins a GEM VRAM object
 * @gbo: The GEM VRAM object to unmap
 * @map: Kernel भव address where the VRAM GEM object was mapped
 *
 * A call to drm_gem_vram_vunmap() unmaps and unpins a GEM VRAM buffer. See
 * the करोcumentation क्रम drm_gem_vram_vmap() क्रम more inक्रमmation.
 */
व्योम drm_gem_vram_vunmap(काष्ठा drm_gem_vram_object *gbo, काष्ठा dma_buf_map *map)
अणु
	पूर्णांक ret;

	ret = tपंचांग_bo_reserve(&gbo->bo, false, false, शून्य);
	अगर (WARN_ONCE(ret, "ttm_bo_reserve_failed(): ret=%d\n", ret))
		वापस;

	drm_gem_vram_kunmap_locked(gbo, map);
	drm_gem_vram_unpin_locked(gbo);

	tपंचांग_bo_unreserve(&gbo->bo);
पूर्ण
EXPORT_SYMBOL(drm_gem_vram_vunmap);

/**
 * drm_gem_vram_fill_create_dumb() - \
	Helper क्रम implementing &काष्ठा drm_driver.dumb_create
 * @file:		the DRM file
 * @dev:		the DRM device
 * @pg_align:		the buffer's alignment in multiples of the page size
 * @pitch_align:	the scanline's alignment in घातers of 2
 * @args:		the arguments as provided to \
				&काष्ठा drm_driver.dumb_create
 *
 * This helper function fills &काष्ठा drm_mode_create_dumb, which is used
 * by &काष्ठा drm_driver.dumb_create. Implementations of this पूर्णांकerface
 * should क्रमwards their arguments to this helper, plus the driver-specअगरic
 * parameters.
 *
 * Returns:
 * 0 on success, or
 * a negative error code otherwise.
 */
पूर्णांक drm_gem_vram_fill_create_dumb(काष्ठा drm_file *file,
				  काष्ठा drm_device *dev,
				  अचिन्हित दीर्घ pg_align,
				  अचिन्हित दीर्घ pitch_align,
				  काष्ठा drm_mode_create_dumb *args)
अणु
	माप_प्रकार pitch, size;
	काष्ठा drm_gem_vram_object *gbo;
	पूर्णांक ret;
	u32 handle;

	pitch = args->width * DIV_ROUND_UP(args->bpp, 8);
	अगर (pitch_align) अणु
		अगर (WARN_ON_ONCE(!is_घातer_of_2(pitch_align)))
			वापस -EINVAL;
		pitch = ALIGN(pitch, pitch_align);
	पूर्ण
	size = pitch * args->height;

	size = roundup(size, PAGE_SIZE);
	अगर (!size)
		वापस -EINVAL;

	gbo = drm_gem_vram_create(dev, size, pg_align);
	अगर (IS_ERR(gbo))
		वापस PTR_ERR(gbo);

	ret = drm_gem_handle_create(file, &gbo->bo.base, &handle);
	अगर (ret)
		जाओ err_drm_gem_object_put;

	drm_gem_object_put(&gbo->bo.base);

	args->pitch = pitch;
	args->size = size;
	args->handle = handle;

	वापस 0;

err_drm_gem_object_put:
	drm_gem_object_put(&gbo->bo.base);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_gem_vram_fill_create_dumb);

/*
 * Helpers क्रम काष्ठा tपंचांग_device_funcs
 */

अटल bool drm_is_gem_vram(काष्ठा tपंचांग_buffer_object *bo)
अणु
	वापस (bo->destroy == tपंचांग_buffer_object_destroy);
पूर्ण

अटल व्योम drm_gem_vram_bo_driver_evict_flags(काष्ठा drm_gem_vram_object *gbo,
					       काष्ठा tपंचांग_placement *pl)
अणु
	drm_gem_vram_placement(gbo, DRM_GEM_VRAM_PL_FLAG_SYSTEM);
	*pl = gbo->placement;
पूर्ण

अटल व्योम drm_gem_vram_bo_driver_move_notअगरy(काष्ठा drm_gem_vram_object *gbo)
अणु
	काष्ठा tपंचांग_buffer_object *bo = &gbo->bo;
	काष्ठा drm_device *dev = bo->base.dev;

	अगर (drm_WARN_ON_ONCE(dev, gbo->vmap_use_count))
		वापस;

	tपंचांग_bo_vunmap(bo, &gbo->map);
	dma_buf_map_clear(&gbo->map); /* explicitly clear mapping क्रम next vmap call */
पूर्ण

अटल पूर्णांक drm_gem_vram_bo_driver_move(काष्ठा drm_gem_vram_object *gbo,
				       bool evict,
				       काष्ठा tपंचांग_operation_ctx *ctx,
				       काष्ठा tपंचांग_resource *new_mem)
अणु
	drm_gem_vram_bo_driver_move_notअगरy(gbo);
	वापस tपंचांग_bo_move_स_नकल(&gbo->bo, ctx, new_mem);
पूर्ण

/*
 * Helpers क्रम काष्ठा drm_gem_object_funcs
 */

/**
 * drm_gem_vram_object_मुक्त() - \
	Implements &काष्ठा drm_gem_object_funcs.मुक्त
 * @gem:       GEM object. Refers to &काष्ठा drm_gem_vram_object.gem
 */
अटल व्योम drm_gem_vram_object_मुक्त(काष्ठा drm_gem_object *gem)
अणु
	काष्ठा drm_gem_vram_object *gbo = drm_gem_vram_of_gem(gem);

	drm_gem_vram_put(gbo);
पूर्ण

/*
 * Helpers क्रम dump buffers
 */

/**
 * drm_gem_vram_driver_dumb_create() - \
	Implements &काष्ठा drm_driver.dumb_create
 * @file:		the DRM file
 * @dev:		the DRM device
 * @args:		the arguments as provided to \
				&काष्ठा drm_driver.dumb_create
 *
 * This function requires the driver to use @drm_device.vram_mm क्रम its
 * instance of VRAM MM.
 *
 * Returns:
 * 0 on success, or
 * a negative error code otherwise.
 */
पूर्णांक drm_gem_vram_driver_dumb_create(काष्ठा drm_file *file,
				    काष्ठा drm_device *dev,
				    काष्ठा drm_mode_create_dumb *args)
अणु
	अगर (WARN_ONCE(!dev->vram_mm, "VRAM MM not initialized"))
		वापस -EINVAL;

	वापस drm_gem_vram_fill_create_dumb(file, dev, 0, 0, args);
पूर्ण
EXPORT_SYMBOL(drm_gem_vram_driver_dumb_create);

/**
 * drm_gem_vram_driver_dumb_mmap_offset() - \
	Implements &काष्ठा drm_driver.dumb_mmap_offset
 * @file:	DRM file poपूर्णांकer.
 * @dev:	DRM device.
 * @handle:	GEM handle
 * @offset:	Returns the mapping's memory offset on success
 *
 * Returns:
 * 0 on success, or
 * a negative त्रुटि_सं code otherwise.
 */
पूर्णांक drm_gem_vram_driver_dumb_mmap_offset(काष्ठा drm_file *file,
					 काष्ठा drm_device *dev,
					 uपूर्णांक32_t handle, uपूर्णांक64_t *offset)
अणु
	काष्ठा drm_gem_object *gem;
	काष्ठा drm_gem_vram_object *gbo;

	gem = drm_gem_object_lookup(file, handle);
	अगर (!gem)
		वापस -ENOENT;

	gbo = drm_gem_vram_of_gem(gem);
	*offset = drm_gem_vram_mmap_offset(gbo);

	drm_gem_object_put(gem);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_gem_vram_driver_dumb_mmap_offset);

/*
 * Helpers क्रम काष्ठा drm_plane_helper_funcs
 */

/**
 * drm_gem_vram_plane_helper_prepare_fb() - \
 *	Implements &काष्ठा drm_plane_helper_funcs.prepare_fb
 * @plane:	a DRM plane
 * @new_state:	the plane's new state
 *
 * During plane updates, this function sets the plane's fence and
 * pins the GEM VRAM objects of the plane's new framebuffer to VRAM.
 * Call drm_gem_vram_plane_helper_cleanup_fb() to unpin them.
 *
 * Returns:
 *	0 on success, or
 *	a negative त्रुटि_सं code otherwise.
 */
पूर्णांक
drm_gem_vram_plane_helper_prepare_fb(काष्ठा drm_plane *plane,
				     काष्ठा drm_plane_state *new_state)
अणु
	माप_प्रकार i;
	काष्ठा drm_gem_vram_object *gbo;
	पूर्णांक ret;

	अगर (!new_state->fb)
		वापस 0;

	क्रम (i = 0; i < ARRAY_SIZE(new_state->fb->obj); ++i) अणु
		अगर (!new_state->fb->obj[i])
			जारी;
		gbo = drm_gem_vram_of_gem(new_state->fb->obj[i]);
		ret = drm_gem_vram_pin(gbo, DRM_GEM_VRAM_PL_FLAG_VRAM);
		अगर (ret)
			जाओ err_drm_gem_vram_unpin;
	पूर्ण

	ret = drm_gem_plane_helper_prepare_fb(plane, new_state);
	अगर (ret)
		जाओ err_drm_gem_vram_unpin;

	वापस 0;

err_drm_gem_vram_unpin:
	जबतक (i) अणु
		--i;
		gbo = drm_gem_vram_of_gem(new_state->fb->obj[i]);
		drm_gem_vram_unpin(gbo);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_gem_vram_plane_helper_prepare_fb);

/**
 * drm_gem_vram_plane_helper_cleanup_fb() - \
 *	Implements &काष्ठा drm_plane_helper_funcs.cleanup_fb
 * @plane:	a DRM plane
 * @old_state:	the plane's old state
 *
 * During plane updates, this function unpins the GEM VRAM
 * objects of the plane's old framebuffer from VRAM. Complements
 * drm_gem_vram_plane_helper_prepare_fb().
 */
व्योम
drm_gem_vram_plane_helper_cleanup_fb(काष्ठा drm_plane *plane,
				     काष्ठा drm_plane_state *old_state)
अणु
	माप_प्रकार i;
	काष्ठा drm_gem_vram_object *gbo;

	अगर (!old_state->fb)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(old_state->fb->obj); ++i) अणु
		अगर (!old_state->fb->obj[i])
			जारी;
		gbo = drm_gem_vram_of_gem(old_state->fb->obj[i]);
		drm_gem_vram_unpin(gbo);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(drm_gem_vram_plane_helper_cleanup_fb);

/*
 * Helpers क्रम काष्ठा drm_simple_display_pipe_funcs
 */

/**
 * drm_gem_vram_simple_display_pipe_prepare_fb() - \
 *	Implements &काष्ठा drm_simple_display_pipe_funcs.prepare_fb
 * @pipe:	a simple display pipe
 * @new_state:	the plane's new state
 *
 * During plane updates, this function pins the GEM VRAM
 * objects of the plane's new framebuffer to VRAM. Call
 * drm_gem_vram_simple_display_pipe_cleanup_fb() to unpin them.
 *
 * Returns:
 *	0 on success, or
 *	a negative त्रुटि_सं code otherwise.
 */
पूर्णांक drm_gem_vram_simple_display_pipe_prepare_fb(
	काष्ठा drm_simple_display_pipe *pipe,
	काष्ठा drm_plane_state *new_state)
अणु
	वापस drm_gem_vram_plane_helper_prepare_fb(&pipe->plane, new_state);
पूर्ण
EXPORT_SYMBOL(drm_gem_vram_simple_display_pipe_prepare_fb);

/**
 * drm_gem_vram_simple_display_pipe_cleanup_fb() - \
 *	Implements &काष्ठा drm_simple_display_pipe_funcs.cleanup_fb
 * @pipe:	a simple display pipe
 * @old_state:	the plane's old state
 *
 * During plane updates, this function unpins the GEM VRAM
 * objects of the plane's old framebuffer from VRAM. Complements
 * drm_gem_vram_simple_display_pipe_prepare_fb().
 */
व्योम drm_gem_vram_simple_display_pipe_cleanup_fb(
	काष्ठा drm_simple_display_pipe *pipe,
	काष्ठा drm_plane_state *old_state)
अणु
	drm_gem_vram_plane_helper_cleanup_fb(&pipe->plane, old_state);
पूर्ण
EXPORT_SYMBOL(drm_gem_vram_simple_display_pipe_cleanup_fb);

/*
 * PRIME helpers
 */

/**
 * drm_gem_vram_object_pin() - \
	Implements &काष्ठा drm_gem_object_funcs.pin
 * @gem:	The GEM object to pin
 *
 * Returns:
 * 0 on success, or
 * a negative त्रुटि_सं code otherwise.
 */
अटल पूर्णांक drm_gem_vram_object_pin(काष्ठा drm_gem_object *gem)
अणु
	काष्ठा drm_gem_vram_object *gbo = drm_gem_vram_of_gem(gem);

	/* Fbdev console emulation is the use हाल of these PRIME
	 * helpers. This may involve updating a hardware buffer from
	 * a shaकरोw FB. We pin the buffer to it's current location
	 * (either video RAM or प्रणाली memory) to prevent it from
	 * being relocated during the update operation. If you require
	 * the buffer to be pinned to VRAM, implement a callback that
	 * sets the flags accordingly.
	 */
	वापस drm_gem_vram_pin(gbo, 0);
पूर्ण

/**
 * drm_gem_vram_object_unpin() - \
	Implements &काष्ठा drm_gem_object_funcs.unpin
 * @gem:	The GEM object to unpin
 */
अटल व्योम drm_gem_vram_object_unpin(काष्ठा drm_gem_object *gem)
अणु
	काष्ठा drm_gem_vram_object *gbo = drm_gem_vram_of_gem(gem);

	drm_gem_vram_unpin(gbo);
पूर्ण

/**
 * drm_gem_vram_object_vmap() -
 *	Implements &काष्ठा drm_gem_object_funcs.vmap
 * @gem: The GEM object to map
 * @map: Returns the kernel भव address of the VRAM GEM object's backing
 *       store.
 *
 * Returns:
 * 0 on success, or a negative error code otherwise.
 */
अटल पूर्णांक drm_gem_vram_object_vmap(काष्ठा drm_gem_object *gem, काष्ठा dma_buf_map *map)
अणु
	काष्ठा drm_gem_vram_object *gbo = drm_gem_vram_of_gem(gem);

	वापस drm_gem_vram_vmap(gbo, map);
पूर्ण

/**
 * drm_gem_vram_object_vunmap() -
 *	Implements &काष्ठा drm_gem_object_funcs.vunmap
 * @gem: The GEM object to unmap
 * @map: Kernel भव address where the VRAM GEM object was mapped
 */
अटल व्योम drm_gem_vram_object_vunmap(काष्ठा drm_gem_object *gem, काष्ठा dma_buf_map *map)
अणु
	काष्ठा drm_gem_vram_object *gbo = drm_gem_vram_of_gem(gem);

	drm_gem_vram_vunmap(gbo, map);
पूर्ण

/*
 * GEM object funcs
 */

अटल स्थिर काष्ठा drm_gem_object_funcs drm_gem_vram_object_funcs = अणु
	.मुक्त	= drm_gem_vram_object_मुक्त,
	.pin	= drm_gem_vram_object_pin,
	.unpin	= drm_gem_vram_object_unpin,
	.vmap	= drm_gem_vram_object_vmap,
	.vunmap	= drm_gem_vram_object_vunmap,
	.mmap   = drm_gem_tपंचांग_mmap,
	.prपूर्णांक_info = drm_gem_tपंचांग_prपूर्णांक_info,
पूर्ण;

/*
 * VRAM memory manager
 */

/*
 * TTM TT
 */

अटल व्योम bo_driver_tपंचांग_tt_destroy(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tt)
अणु
	tपंचांग_tt_destroy_common(bdev, tt);
	tपंचांग_tt_fini(tt);
	kमुक्त(tt);
पूर्ण

/*
 * TTM BO device
 */

अटल काष्ठा tपंचांग_tt *bo_driver_tपंचांग_tt_create(काष्ठा tपंचांग_buffer_object *bo,
					      uपूर्णांक32_t page_flags)
अणु
	काष्ठा tपंचांग_tt *tt;
	पूर्णांक ret;

	tt = kzalloc(माप(*tt), GFP_KERNEL);
	अगर (!tt)
		वापस शून्य;

	ret = tपंचांग_tt_init(tt, bo, page_flags, tपंचांग_cached);
	अगर (ret < 0)
		जाओ err_tपंचांग_tt_init;

	वापस tt;

err_tपंचांग_tt_init:
	kमुक्त(tt);
	वापस शून्य;
पूर्ण

अटल व्योम bo_driver_evict_flags(काष्ठा tपंचांग_buffer_object *bo,
				  काष्ठा tपंचांग_placement *placement)
अणु
	काष्ठा drm_gem_vram_object *gbo;

	/* TTM may pass BOs that are not GEM VRAM BOs. */
	अगर (!drm_is_gem_vram(bo))
		वापस;

	gbo = drm_gem_vram_of_bo(bo);

	drm_gem_vram_bo_driver_evict_flags(gbo, placement);
पूर्ण

अटल व्योम bo_driver_delete_mem_notअगरy(काष्ठा tपंचांग_buffer_object *bo)
अणु
	काष्ठा drm_gem_vram_object *gbo;

	/* TTM may pass BOs that are not GEM VRAM BOs. */
	अगर (!drm_is_gem_vram(bo))
		वापस;

	gbo = drm_gem_vram_of_bo(bo);

	drm_gem_vram_bo_driver_move_notअगरy(gbo);
पूर्ण

अटल पूर्णांक bo_driver_move(काष्ठा tपंचांग_buffer_object *bo,
			  bool evict,
			  काष्ठा tपंचांग_operation_ctx *ctx,
			  काष्ठा tपंचांग_resource *new_mem,
			  काष्ठा tपंचांग_place *hop)
अणु
	काष्ठा drm_gem_vram_object *gbo;

	gbo = drm_gem_vram_of_bo(bo);

	वापस drm_gem_vram_bo_driver_move(gbo, evict, ctx, new_mem);
पूर्ण

अटल पूर्णांक bo_driver_io_mem_reserve(काष्ठा tपंचांग_device *bdev,
				    काष्ठा tपंचांग_resource *mem)
अणु
	काष्ठा drm_vram_mm *vmm = drm_vram_mm_of_bdev(bdev);

	चयन (mem->mem_type) अणु
	हाल TTM_PL_SYSTEM:	/* nothing to करो */
		अवरोध;
	हाल TTM_PL_VRAM:
		mem->bus.offset = (mem->start << PAGE_SHIFT) + vmm->vram_base;
		mem->bus.is_iomem = true;
		mem->bus.caching = tपंचांग_ग_लिखो_combined;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा tपंचांग_device_funcs bo_driver = अणु
	.tपंचांग_tt_create = bo_driver_tपंचांग_tt_create,
	.tपंचांग_tt_destroy = bo_driver_tपंचांग_tt_destroy,
	.eviction_valuable = tपंचांग_bo_eviction_valuable,
	.evict_flags = bo_driver_evict_flags,
	.move = bo_driver_move,
	.delete_mem_notअगरy = bo_driver_delete_mem_notअगरy,
	.io_mem_reserve = bo_driver_io_mem_reserve,
पूर्ण;

/*
 * काष्ठा drm_vram_mm
 */

अटल पूर्णांक drm_vram_mm_debugfs(काष्ठा seq_file *m, व्योम *data)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *) m->निजी;
	काष्ठा drm_vram_mm *vmm = node->minor->dev->vram_mm;
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(&vmm->bdev, TTM_PL_VRAM);
	काष्ठा drm_prपूर्णांकer p = drm_seq_file_prपूर्णांकer(m);

	tपंचांग_resource_manager_debug(man, &p);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_info_list drm_vram_mm_debugfs_list[] = अणु
	अणु "vram-mm", drm_vram_mm_debugfs, 0, शून्य पूर्ण,
पूर्ण;

/**
 * drm_vram_mm_debugfs_init() - Register VRAM MM debugfs file.
 *
 * @minor: drm minor device.
 *
 */
व्योम drm_vram_mm_debugfs_init(काष्ठा drm_minor *minor)
अणु
	drm_debugfs_create_files(drm_vram_mm_debugfs_list,
				 ARRAY_SIZE(drm_vram_mm_debugfs_list),
				 minor->debugfs_root, minor);
पूर्ण
EXPORT_SYMBOL(drm_vram_mm_debugfs_init);

अटल पूर्णांक drm_vram_mm_init(काष्ठा drm_vram_mm *vmm, काष्ठा drm_device *dev,
			    uपूर्णांक64_t vram_base, माप_प्रकार vram_size)
अणु
	पूर्णांक ret;

	vmm->vram_base = vram_base;
	vmm->vram_size = vram_size;

	ret = tपंचांग_device_init(&vmm->bdev, &bo_driver, dev->dev,
				 dev->anon_inode->i_mapping,
				 dev->vma_offset_manager,
				 false, true);
	अगर (ret)
		वापस ret;

	ret = tपंचांग_range_man_init(&vmm->bdev, TTM_PL_VRAM,
				 false, vram_size >> PAGE_SHIFT);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम drm_vram_mm_cleanup(काष्ठा drm_vram_mm *vmm)
अणु
	tपंचांग_range_man_fini(&vmm->bdev, TTM_PL_VRAM);
	tपंचांग_device_fini(&vmm->bdev);
पूर्ण

/*
 * Helpers क्रम पूर्णांकegration with काष्ठा drm_device
 */

/* deprecated; use drmm_vram_mm_init() */
काष्ठा drm_vram_mm *drm_vram_helper_alloc_mm(
	काष्ठा drm_device *dev, uपूर्णांक64_t vram_base, माप_प्रकार vram_size)
अणु
	पूर्णांक ret;

	अगर (WARN_ON(dev->vram_mm))
		वापस dev->vram_mm;

	dev->vram_mm = kzalloc(माप(*dev->vram_mm), GFP_KERNEL);
	अगर (!dev->vram_mm)
		वापस ERR_PTR(-ENOMEM);

	ret = drm_vram_mm_init(dev->vram_mm, dev, vram_base, vram_size);
	अगर (ret)
		जाओ err_kमुक्त;

	वापस dev->vram_mm;

err_kमुक्त:
	kमुक्त(dev->vram_mm);
	dev->vram_mm = शून्य;
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL(drm_vram_helper_alloc_mm);

व्योम drm_vram_helper_release_mm(काष्ठा drm_device *dev)
अणु
	अगर (!dev->vram_mm)
		वापस;

	drm_vram_mm_cleanup(dev->vram_mm);
	kमुक्त(dev->vram_mm);
	dev->vram_mm = शून्य;
पूर्ण
EXPORT_SYMBOL(drm_vram_helper_release_mm);

अटल व्योम drm_vram_mm_release(काष्ठा drm_device *dev, व्योम *ptr)
अणु
	drm_vram_helper_release_mm(dev);
पूर्ण

/**
 * drmm_vram_helper_init - Initializes a device's instance of
 *                         &काष्ठा drm_vram_mm
 * @dev:	the DRM device
 * @vram_base:	the base address of the video memory
 * @vram_size:	the size of the video memory in bytes
 *
 * Creates a new instance of &काष्ठा drm_vram_mm and stores it in
 * काष्ठा &drm_device.vram_mm. The instance is स्वतः-managed and cleaned
 * up as part of device cleanup. Calling this function multiple बार
 * will generate an error message.
 *
 * Returns:
 * 0 on success, or a negative त्रुटि_सं code otherwise.
 */
पूर्णांक drmm_vram_helper_init(काष्ठा drm_device *dev, uपूर्णांक64_t vram_base,
			  माप_प्रकार vram_size)
अणु
	काष्ठा drm_vram_mm *vram_mm;

	अगर (drm_WARN_ON_ONCE(dev, dev->vram_mm))
		वापस 0;

	vram_mm = drm_vram_helper_alloc_mm(dev, vram_base, vram_size);
	अगर (IS_ERR(vram_mm))
		वापस PTR_ERR(vram_mm);
	वापस drmm_add_action_or_reset(dev, drm_vram_mm_release, शून्य);
पूर्ण
EXPORT_SYMBOL(drmm_vram_helper_init);

/*
 * Mode-config helpers
 */

अटल क्रमागत drm_mode_status
drm_vram_helper_mode_valid_पूर्णांकernal(काष्ठा drm_device *dev,
				    स्थिर काष्ठा drm_display_mode *mode,
				    अचिन्हित दीर्घ max_bpp)
अणु
	काष्ठा drm_vram_mm *vmm = dev->vram_mm;
	अचिन्हित दीर्घ fbsize, fbpages, max_fbpages;

	अगर (WARN_ON(!dev->vram_mm))
		वापस MODE_BAD;

	max_fbpages = (vmm->vram_size / 2) >> PAGE_SHIFT;

	fbsize = mode->hdisplay * mode->vdisplay * max_bpp;
	fbpages = DIV_ROUND_UP(fbsize, PAGE_SIZE);

	अगर (fbpages > max_fbpages)
		वापस MODE_MEM;

	वापस MODE_OK;
पूर्ण

/**
 * drm_vram_helper_mode_valid - Tests अगर a display mode's
 *	framebuffer fits पूर्णांकo the available video memory.
 * @dev:	the DRM device
 * @mode:	the mode to test
 *
 * This function tests अगर enough video memory is available क्रम using the
 * specअगरied display mode. Atomic modesetting requires importing the
 * designated framebuffer पूर्णांकo video memory beक्रमe evicting the active
 * one. Hence, any framebuffer may consume at most half of the available
 * VRAM. Display modes that require a larger framebuffer can not be used,
 * even अगर the CRTC करोes support them. Each framebuffer is assumed to
 * have 32-bit color depth.
 *
 * Note:
 * The function can only test अगर the display mode is supported in
 * general. If there are too many framebuffers pinned to video memory,
 * a display mode may still not be usable in practice. The color depth of
 * 32-bit fits all current use हाल. A more flexible test can be added
 * when necessary.
 *
 * Returns:
 * MODE_OK अगर the display mode is supported, or an error code of type
 * क्रमागत drm_mode_status otherwise.
 */
क्रमागत drm_mode_status
drm_vram_helper_mode_valid(काष्ठा drm_device *dev,
			   स्थिर काष्ठा drm_display_mode *mode)
अणु
	अटल स्थिर अचिन्हित दीर्घ max_bpp = 4; /* DRM_FORMAT_XRGB8888 */

	वापस drm_vram_helper_mode_valid_पूर्णांकernal(dev, mode, max_bpp);
पूर्ण
EXPORT_SYMBOL(drm_vram_helper_mode_valid);

MODULE_DESCRIPTION("DRM VRAM memory-management helpers");
MODULE_LICENSE("GPL");
