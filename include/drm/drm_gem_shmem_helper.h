<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __DRM_GEM_SHMEM_HELPER_H__
#घोषणा __DRM_GEM_SHMEM_HELPER_H__

#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/mutex.h>

#समावेश <drm/drm_file.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_prime.h>

काष्ठा dma_buf_attachment;
काष्ठा drm_mode_create_dumb;
काष्ठा drm_prपूर्णांकer;
काष्ठा sg_table;

/**
 * काष्ठा drm_gem_shmem_object - GEM object backed by shmem
 */
काष्ठा drm_gem_shmem_object अणु
	/**
	 * @base: Base GEM object
	 */
	काष्ठा drm_gem_object base;

	/**
	 * @pages_lock: Protects the page table and use count
	 */
	काष्ठा mutex pages_lock;

	/**
	 * @pages: Page table
	 */
	काष्ठा page **pages;

	/**
	 * @pages_use_count:
	 *
	 * Reference count on the pages table.
	 * The pages are put when the count reaches zero.
	 */
	अचिन्हित पूर्णांक pages_use_count;

	/**
	 * @madv: State क्रम madvise
	 *
	 * 0 is active/inuse.
	 * A negative value is the object is purged.
	 * Positive values are driver specअगरic and not used by the helpers.
	 */
	पूर्णांक madv;

	/**
	 * @madv_list: List entry क्रम madvise tracking
	 *
	 * Typically used by drivers to track purgeable objects
	 */
	काष्ठा list_head madv_list;

	/**
	 * @pages_mark_dirty_on_put:
	 *
	 * Mark pages as dirty when they are put.
	 */
	अचिन्हित पूर्णांक pages_mark_dirty_on_put    : 1;

	/**
	 * @pages_mark_accessed_on_put:
	 *
	 * Mark pages as accessed when they are put.
	 */
	अचिन्हित पूर्णांक pages_mark_accessed_on_put : 1;

	/**
	 * @sgt: Scatter/gather table क्रम imported PRIME buffers
	 */
	काष्ठा sg_table *sgt;

	/**
	 * @vmap_lock: Protects the vmap address and use count
	 */
	काष्ठा mutex vmap_lock;

	/**
	 * @vaddr: Kernel भव address of the backing memory
	 */
	व्योम *vaddr;

	/**
	 * @vmap_use_count:
	 *
	 * Reference count on the भव address.
	 * The address are un-mapped when the count reaches zero.
	 */
	अचिन्हित पूर्णांक vmap_use_count;

	/**
	 * @map_wc: map object ग_लिखो-combined (instead of using shmem शेषs).
	 */
	bool map_wc;
पूर्ण;

#घोषणा to_drm_gem_shmem_obj(obj) \
	container_of(obj, काष्ठा drm_gem_shmem_object, base)

काष्ठा drm_gem_shmem_object *drm_gem_shmem_create(काष्ठा drm_device *dev, माप_प्रकार size);
व्योम drm_gem_shmem_मुक्त_object(काष्ठा drm_gem_object *obj);

पूर्णांक drm_gem_shmem_get_pages(काष्ठा drm_gem_shmem_object *shmem);
व्योम drm_gem_shmem_put_pages(काष्ठा drm_gem_shmem_object *shmem);
पूर्णांक drm_gem_shmem_pin(काष्ठा drm_gem_object *obj);
व्योम drm_gem_shmem_unpin(काष्ठा drm_gem_object *obj);
पूर्णांक drm_gem_shmem_vmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map);
व्योम drm_gem_shmem_vunmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map);

पूर्णांक drm_gem_shmem_madvise(काष्ठा drm_gem_object *obj, पूर्णांक madv);

अटल अंतरभूत bool drm_gem_shmem_is_purgeable(काष्ठा drm_gem_shmem_object *shmem)
अणु
	वापस (shmem->madv > 0) &&
		!shmem->vmap_use_count && shmem->sgt &&
		!shmem->base.dma_buf && !shmem->base.import_attach;
पूर्ण

व्योम drm_gem_shmem_purge_locked(काष्ठा drm_gem_object *obj);
bool drm_gem_shmem_purge(काष्ठा drm_gem_object *obj);

काष्ठा drm_gem_shmem_object *
drm_gem_shmem_create_with_handle(काष्ठा drm_file *file_priv,
				 काष्ठा drm_device *dev, माप_प्रकार size,
				 uपूर्णांक32_t *handle);

पूर्णांक drm_gem_shmem_dumb_create(काष्ठा drm_file *file, काष्ठा drm_device *dev,
			      काष्ठा drm_mode_create_dumb *args);

पूर्णांक drm_gem_shmem_mmap(काष्ठा drm_gem_object *obj, काष्ठा vm_area_काष्ठा *vma);

व्योम drm_gem_shmem_prपूर्णांक_info(काष्ठा drm_prपूर्णांकer *p, अचिन्हित पूर्णांक indent,
			      स्थिर काष्ठा drm_gem_object *obj);

काष्ठा sg_table *drm_gem_shmem_get_sg_table(काष्ठा drm_gem_object *obj);
काष्ठा drm_gem_object *
drm_gem_shmem_prime_import_sg_table(काष्ठा drm_device *dev,
				    काष्ठा dma_buf_attachment *attach,
				    काष्ठा sg_table *sgt);

काष्ठा sg_table *drm_gem_shmem_get_pages_sgt(काष्ठा drm_gem_object *obj);

/**
 * DRM_GEM_SHMEM_DRIVER_OPS - Default shmem GEM operations
 *
 * This macro provides a लघुcut क्रम setting the shmem GEM operations in
 * the &drm_driver काष्ठाure.
 */
#घोषणा DRM_GEM_SHMEM_DRIVER_OPS \
	.prime_handle_to_fd	= drm_gem_prime_handle_to_fd, \
	.prime_fd_to_handle	= drm_gem_prime_fd_to_handle, \
	.gem_prime_import_sg_table = drm_gem_shmem_prime_import_sg_table, \
	.gem_prime_mmap		= drm_gem_prime_mmap, \
	.dumb_create		= drm_gem_shmem_dumb_create

#पूर्ण_अगर /* __DRM_GEM_SHMEM_HELPER_H__ */
