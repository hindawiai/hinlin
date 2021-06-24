<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __DRM_GEM_CMA_HELPER_H__
#घोषणा __DRM_GEM_CMA_HELPER_H__

#समावेश <drm/drm_file.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_gem.h>

काष्ठा drm_mode_create_dumb;

/**
 * काष्ठा drm_gem_cma_object - GEM object backed by CMA memory allocations
 * @base: base GEM object
 * @paddr: physical address of the backing memory
 * @sgt: scatter/gather table क्रम imported PRIME buffers. The table can have
 *       more than one entry but they are guaranteed to have contiguous
 *       DMA addresses.
 * @vaddr: kernel भव address of the backing memory
 */
काष्ठा drm_gem_cma_object अणु
	काष्ठा drm_gem_object base;
	dma_addr_t paddr;
	काष्ठा sg_table *sgt;

	/* For objects with DMA memory allocated by GEM CMA */
	व्योम *vaddr;
पूर्ण;

#घोषणा to_drm_gem_cma_obj(gem_obj) \
	container_of(gem_obj, काष्ठा drm_gem_cma_object, base)

#अगर_अघोषित CONFIG_MMU
#घोषणा DRM_GEM_CMA_UNMAPPED_AREA_FOPS \
	.get_unmapped_area	= drm_gem_cma_get_unmapped_area,
#अन्यथा
#घोषणा DRM_GEM_CMA_UNMAPPED_AREA_FOPS
#पूर्ण_अगर

/**
 * DEFINE_DRM_GEM_CMA_FOPS() - macro to generate file operations क्रम CMA drivers
 * @name: name क्रम the generated काष्ठाure
 *
 * This macro स्वतःgenerates a suitable &काष्ठा file_operations क्रम CMA based
 * drivers, which can be asचिन्हित to &drm_driver.fops. Note that this काष्ठाure
 * cannot be shared between drivers, because it contains a reference to the
 * current module using THIS_MODULE.
 *
 * Note that the declaration is alपढ़ोy marked as अटल - अगर you need a
 * non-अटल version of this you're probably करोing it wrong and will अवरोध the
 * THIS_MODULE reference by accident.
 */
#घोषणा DEFINE_DRM_GEM_CMA_FOPS(name) \
	अटल स्थिर काष्ठा file_operations name = अणु\
		.owner		= THIS_MODULE,\
		.खोलो		= drm_खोलो,\
		.release	= drm_release,\
		.unlocked_ioctl	= drm_ioctl,\
		.compat_ioctl	= drm_compat_ioctl,\
		.poll		= drm_poll,\
		.पढ़ो		= drm_पढ़ो,\
		.llseek		= noop_llseek,\
		.mmap		= drm_gem_mmap,\
		DRM_GEM_CMA_UNMAPPED_AREA_FOPS \
	पूर्ण

/* मुक्त GEM object */
व्योम drm_gem_cma_मुक्त_object(काष्ठा drm_gem_object *gem_obj);

/* create memory region क्रम DRM framebuffer */
पूर्णांक drm_gem_cma_dumb_create_पूर्णांकernal(काष्ठा drm_file *file_priv,
				     काष्ठा drm_device *drm,
				     काष्ठा drm_mode_create_dumb *args);

/* create memory region क्रम DRM framebuffer */
पूर्णांक drm_gem_cma_dumb_create(काष्ठा drm_file *file_priv,
			    काष्ठा drm_device *drm,
			    काष्ठा drm_mode_create_dumb *args);

/* allocate physical memory */
काष्ठा drm_gem_cma_object *drm_gem_cma_create(काष्ठा drm_device *drm,
					      माप_प्रकार size);

बाह्य स्थिर काष्ठा vm_operations_काष्ठा drm_gem_cma_vm_ops;

#अगर_अघोषित CONFIG_MMU
अचिन्हित दीर्घ drm_gem_cma_get_unmapped_area(काष्ठा file *filp,
					    अचिन्हित दीर्घ addr,
					    अचिन्हित दीर्घ len,
					    अचिन्हित दीर्घ pgoff,
					    अचिन्हित दीर्घ flags);
#पूर्ण_अगर

व्योम drm_gem_cma_prपूर्णांक_info(काष्ठा drm_prपूर्णांकer *p, अचिन्हित पूर्णांक indent,
			    स्थिर काष्ठा drm_gem_object *obj);

काष्ठा sg_table *drm_gem_cma_get_sg_table(काष्ठा drm_gem_object *obj);
काष्ठा drm_gem_object *
drm_gem_cma_prime_import_sg_table(काष्ठा drm_device *dev,
				  काष्ठा dma_buf_attachment *attach,
				  काष्ठा sg_table *sgt);
पूर्णांक drm_gem_cma_vmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map);
पूर्णांक drm_gem_cma_mmap(काष्ठा drm_gem_object *obj, काष्ठा vm_area_काष्ठा *vma);

/**
 * DRM_GEM_CMA_DRIVER_OPS_WITH_DUMB_CREATE - CMA GEM driver operations
 * @dumb_create_func: callback function क्रम .dumb_create
 *
 * This macro provides a लघुcut क्रम setting the शेष GEM operations in the
 * &drm_driver काष्ठाure.
 *
 * This macro is a variant of DRM_GEM_CMA_DRIVER_OPS क्रम drivers that
 * override the शेष implementation of &काष्ठा rm_driver.dumb_create. Use
 * DRM_GEM_CMA_DRIVER_OPS अगर possible. Drivers that require a भव address
 * on imported buffers should use
 * DRM_GEM_CMA_DRIVER_OPS_VMAP_WITH_DUMB_CREATE() instead.
 */
#घोषणा DRM_GEM_CMA_DRIVER_OPS_WITH_DUMB_CREATE(dumb_create_func) \
	.dumb_create		= (dumb_create_func), \
	.prime_handle_to_fd	= drm_gem_prime_handle_to_fd, \
	.prime_fd_to_handle	= drm_gem_prime_fd_to_handle, \
	.gem_prime_import_sg_table = drm_gem_cma_prime_import_sg_table, \
	.gem_prime_mmap		= drm_gem_prime_mmap

/**
 * DRM_GEM_CMA_DRIVER_OPS - CMA GEM driver operations
 *
 * This macro provides a लघुcut क्रम setting the शेष GEM operations in the
 * &drm_driver काष्ठाure.
 *
 * Drivers that come with their own implementation of
 * &काष्ठा drm_driver.dumb_create should use
 * DRM_GEM_CMA_DRIVER_OPS_WITH_DUMB_CREATE() instead. Use
 * DRM_GEM_CMA_DRIVER_OPS अगर possible. Drivers that require a भव address
 * on imported buffers should use DRM_GEM_CMA_DRIVER_OPS_VMAP instead.
 */
#घोषणा DRM_GEM_CMA_DRIVER_OPS \
	DRM_GEM_CMA_DRIVER_OPS_WITH_DUMB_CREATE(drm_gem_cma_dumb_create)

/**
 * DRM_GEM_CMA_DRIVER_OPS_VMAP_WITH_DUMB_CREATE - CMA GEM driver operations
 *                                                ensuring a भव address
 *                                                on the buffer
 * @dumb_create_func: callback function क्रम .dumb_create
 *
 * This macro provides a लघुcut क्रम setting the शेष GEM operations in the
 * &drm_driver काष्ठाure क्रम drivers that need the भव address also on
 * imported buffers.
 *
 * This macro is a variant of DRM_GEM_CMA_DRIVER_OPS_VMAP क्रम drivers that
 * override the शेष implementation of &काष्ठा drm_driver.dumb_create. Use
 * DRM_GEM_CMA_DRIVER_OPS_VMAP अगर possible. Drivers that करो not require a
 * भव address on imported buffers should use
 * DRM_GEM_CMA_DRIVER_OPS_WITH_DUMB_CREATE() instead.
 */
#घोषणा DRM_GEM_CMA_DRIVER_OPS_VMAP_WITH_DUMB_CREATE(dumb_create_func) \
	.dumb_create		= dumb_create_func, \
	.prime_handle_to_fd	= drm_gem_prime_handle_to_fd, \
	.prime_fd_to_handle	= drm_gem_prime_fd_to_handle, \
	.gem_prime_import_sg_table = drm_gem_cma_prime_import_sg_table_vmap, \
	.gem_prime_mmap		= drm_gem_prime_mmap

/**
 * DRM_GEM_CMA_DRIVER_OPS_VMAP - CMA GEM driver operations ensuring a भव
 *                               address on the buffer
 *
 * This macro provides a लघुcut क्रम setting the शेष GEM operations in the
 * &drm_driver काष्ठाure क्रम drivers that need the भव address also on
 * imported buffers.
 *
 * Drivers that come with their own implementation of
 * &काष्ठा drm_driver.dumb_create should use
 * DRM_GEM_CMA_DRIVER_OPS_VMAP_WITH_DUMB_CREATE() instead. Use
 * DRM_GEM_CMA_DRIVER_OPS_VMAP अगर possible. Drivers that करो not require a
 * भव address on imported buffers should use DRM_GEM_CMA_DRIVER_OPS
 * instead.
 */
#घोषणा DRM_GEM_CMA_DRIVER_OPS_VMAP \
	DRM_GEM_CMA_DRIVER_OPS_VMAP_WITH_DUMB_CREATE(drm_gem_cma_dumb_create)

काष्ठा drm_gem_object *
drm_gem_cma_prime_import_sg_table_vmap(काष्ठा drm_device *drm,
				       काष्ठा dma_buf_attachment *attach,
				       काष्ठा sg_table *sgt);

#पूर्ण_अगर /* __DRM_GEM_CMA_HELPER_H__ */
