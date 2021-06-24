<शैली गुरु>
#अगर_अघोषित __DRM_GEM_H__
#घोषणा __DRM_GEM_H__

/*
 * GEM Graphics Execution Manager Driver Interfaces
 *
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, Calअगरornia.
 * Copyright (c) 2009-2010, Code Aurora Forum.
 * All rights reserved.
 * Copyright तऊ 2014 Intel Corporation
 *   Daniel Vetter <daniel.vetter@ffwll.ch>
 *
 * Author: Rickard E. (Rik) Faith <faith@valinux.com>
 * Author: Gareth Hughes <gareth@valinux.com>
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
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/kref.h>
#समावेश <linux/dma-resv.h>

#समावेश <drm/drm_vma_manager.h>

काष्ठा dma_buf_map;
काष्ठा drm_gem_object;

/**
 * काष्ठा drm_gem_object_funcs - GEM object functions
 */
काष्ठा drm_gem_object_funcs अणु
	/**
	 * @मुक्त:
	 *
	 * Deस्थिरructor क्रम drm_gem_objects.
	 *
	 * This callback is mandatory.
	 */
	व्योम (*मुक्त)(काष्ठा drm_gem_object *obj);

	/**
	 * @खोलो:
	 *
	 * Called upon GEM handle creation.
	 *
	 * This callback is optional.
	 */
	पूर्णांक (*खोलो)(काष्ठा drm_gem_object *obj, काष्ठा drm_file *file);

	/**
	 * @बंद:
	 *
	 * Called upon GEM handle release.
	 *
	 * This callback is optional.
	 */
	व्योम (*बंद)(काष्ठा drm_gem_object *obj, काष्ठा drm_file *file);

	/**
	 * @prपूर्णांक_info:
	 *
	 * If driver subclasses काष्ठा &drm_gem_object, it can implement this
	 * optional hook क्रम prपूर्णांकing additional driver specअगरic info.
	 *
	 * drm_म_लिखो_indent() should be used in the callback passing it the
	 * indent argument.
	 *
	 * This callback is called from drm_gem_prपूर्णांक_info().
	 *
	 * This callback is optional.
	 */
	व्योम (*prपूर्णांक_info)(काष्ठा drm_prपूर्णांकer *p, अचिन्हित पूर्णांक indent,
			   स्थिर काष्ठा drm_gem_object *obj);

	/**
	 * @export:
	 *
	 * Export backing buffer as a &dma_buf.
	 * If this is not set drm_gem_prime_export() is used.
	 *
	 * This callback is optional.
	 */
	काष्ठा dma_buf *(*export)(काष्ठा drm_gem_object *obj, पूर्णांक flags);

	/**
	 * @pin:
	 *
	 * Pin backing buffer in memory. Used by the drm_gem_map_attach() helper.
	 *
	 * This callback is optional.
	 */
	पूर्णांक (*pin)(काष्ठा drm_gem_object *obj);

	/**
	 * @unpin:
	 *
	 * Unpin backing buffer. Used by the drm_gem_map_detach() helper.
	 *
	 * This callback is optional.
	 */
	व्योम (*unpin)(काष्ठा drm_gem_object *obj);

	/**
	 * @get_sg_table:
	 *
	 * Returns a Scatter-Gather table representation of the buffer.
	 * Used when exporting a buffer by the drm_gem_map_dma_buf() helper.
	 * Releasing is करोne by calling dma_unmap_sg_attrs() and sg_मुक्त_table()
	 * in drm_gem_unmap_buf(), thereक्रमe these helpers and this callback
	 * here cannot be used क्रम sg tables poपूर्णांकing at driver निजी memory
	 * ranges.
	 *
	 * See also drm_prime_pages_to_sg().
	 */
	काष्ठा sg_table *(*get_sg_table)(काष्ठा drm_gem_object *obj);

	/**
	 * @vmap:
	 *
	 * Returns a भव address क्रम the buffer. Used by the
	 * drm_gem_dmabuf_vmap() helper.
	 *
	 * This callback is optional.
	 */
	पूर्णांक (*vmap)(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map);

	/**
	 * @vunmap:
	 *
	 * Releases the address previously वापसed by @vmap. Used by the
	 * drm_gem_dmabuf_vunmap() helper.
	 *
	 * This callback is optional.
	 */
	व्योम (*vunmap)(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map);

	/**
	 * @mmap:
	 *
	 * Handle mmap() of the gem object, setup vma accordingly.
	 *
	 * This callback is optional.
	 *
	 * The callback is used by both drm_gem_mmap_obj() and
	 * drm_gem_prime_mmap().  When @mmap is present @vm_ops is not
	 * used, the @mmap callback must set vma->vm_ops instead.
	 */
	पूर्णांक (*mmap)(काष्ठा drm_gem_object *obj, काष्ठा vm_area_काष्ठा *vma);

	/**
	 * @vm_ops:
	 *
	 * Virtual memory operations used with mmap.
	 *
	 * This is optional but necessary क्रम mmap support.
	 */
	स्थिर काष्ठा vm_operations_काष्ठा *vm_ops;
पूर्ण;

/**
 * काष्ठा drm_gem_object - GEM buffer object
 *
 * This काष्ठाure defines the generic parts क्रम GEM buffer objects, which are
 * mostly around handling mmap and userspace handles.
 *
 * Buffer objects are often abbreviated to BO.
 */
काष्ठा drm_gem_object अणु
	/**
	 * @refcount:
	 *
	 * Reference count of this object
	 *
	 * Please use drm_gem_object_get() to acquire and drm_gem_object_put_locked()
	 * or drm_gem_object_put() to release a reference to a GEM
	 * buffer object.
	 */
	काष्ठा kref refcount;

	/**
	 * @handle_count:
	 *
	 * This is the GEM file_priv handle count of this object.
	 *
	 * Each handle also holds a reference. Note that when the handle_count
	 * drops to 0 any global names (e.g. the id in the flink namespace) will
	 * be cleared.
	 *
	 * Protected by &drm_device.object_name_lock.
	 */
	अचिन्हित handle_count;

	/**
	 * @dev: DRM dev this object beदीर्घs to.
	 */
	काष्ठा drm_device *dev;

	/**
	 * @filp:
	 *
	 * SHMEM file node used as backing storage क्रम swappable buffer objects.
	 * GEM also supports driver निजी objects with driver-specअगरic backing
	 * storage (contiguous CMA memory, special reserved blocks). In this
	 * हाल @filp is शून्य.
	 */
	काष्ठा file *filp;

	/**
	 * @vma_node:
	 *
	 * Mapping info क्रम this object to support mmap. Drivers are supposed to
	 * allocate the mmap offset using drm_gem_create_mmap_offset(). The
	 * offset itself can be retrieved using drm_vma_node_offset_addr().
	 *
	 * Memory mapping itself is handled by drm_gem_mmap(), which also checks
	 * that userspace is allowed to access the object.
	 */
	काष्ठा drm_vma_offset_node vma_node;

	/**
	 * @size:
	 *
	 * Size of the object, in bytes.  Immutable over the object's
	 * lअगरeसमय.
	 */
	माप_प्रकार size;

	/**
	 * @name:
	 *
	 * Global name क्रम this object, starts at 1. 0 means unnamed.
	 * Access is covered by &drm_device.object_name_lock. This is used by
	 * the GEM_FLINK and GEM_OPEN ioctls.
	 */
	पूर्णांक name;

	/**
	 * @dma_buf:
	 *
	 * dma-buf associated with this GEM object.
	 *
	 * Poपूर्णांकer to the dma-buf associated with this gem object (either
	 * through importing or exporting). We अवरोध the resulting reference
	 * loop when the last gem handle क्रम this object is released.
	 *
	 * Protected by &drm_device.object_name_lock.
	 */
	काष्ठा dma_buf *dma_buf;

	/**
	 * @import_attach:
	 *
	 * dma-buf attachment backing this object.
	 *
	 * Any क्रमeign dma_buf imported as a gem object has this set to the
	 * attachment poपूर्णांक क्रम the device. This is invariant over the lअगरeसमय
	 * of a gem object.
	 *
	 * The &drm_gem_object_funcs.मुक्त callback is responsible क्रम
	 * cleaning up the dma_buf attachment and references acquired at import
	 * समय.
	 *
	 * Note that the drm gem/prime core करोes not depend upon drivers setting
	 * this field any more. So क्रम drivers where this करोesn't make sense
	 * (e.g. भव devices or a displaylink behind an usb bus) they can
	 * simply leave it as शून्य.
	 */
	काष्ठा dma_buf_attachment *import_attach;

	/**
	 * @resv:
	 *
	 * Poपूर्णांकer to reservation object associated with the this GEM object.
	 *
	 * Normally (@resv == &@_resv) except क्रम imported GEM objects.
	 */
	काष्ठा dma_resv *resv;

	/**
	 * @_resv:
	 *
	 * A reservation object क्रम this GEM object.
	 *
	 * This is unused क्रम imported GEM objects.
	 */
	काष्ठा dma_resv _resv;

	/**
	 * @funcs:
	 *
	 * Optional GEM object functions. If this is set, it will be used instead of the
	 * corresponding &drm_driver GEM callbacks.
	 *
	 * New drivers should use this.
	 *
	 */
	स्थिर काष्ठा drm_gem_object_funcs *funcs;
पूर्ण;

/**
 * DEFINE_DRM_GEM_FOPS() - macro to generate file operations क्रम GEM drivers
 * @name: name क्रम the generated काष्ठाure
 *
 * This macro स्वतःgenerates a suitable &काष्ठा file_operations क्रम GEM based
 * drivers, which can be asचिन्हित to &drm_driver.fops. Note that this काष्ठाure
 * cannot be shared between drivers, because it contains a reference to the
 * current module using THIS_MODULE.
 *
 * Note that the declaration is alपढ़ोy marked as अटल - अगर you need a
 * non-अटल version of this you're probably करोing it wrong and will अवरोध the
 * THIS_MODULE reference by accident.
 */
#घोषणा DEFINE_DRM_GEM_FOPS(name) \
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
	पूर्ण

व्योम drm_gem_object_release(काष्ठा drm_gem_object *obj);
व्योम drm_gem_object_मुक्त(काष्ठा kref *kref);
पूर्णांक drm_gem_object_init(काष्ठा drm_device *dev,
			काष्ठा drm_gem_object *obj, माप_प्रकार size);
व्योम drm_gem_निजी_object_init(काष्ठा drm_device *dev,
				 काष्ठा drm_gem_object *obj, माप_प्रकार size);
व्योम drm_gem_vm_खोलो(काष्ठा vm_area_काष्ठा *vma);
व्योम drm_gem_vm_बंद(काष्ठा vm_area_काष्ठा *vma);
पूर्णांक drm_gem_mmap_obj(काष्ठा drm_gem_object *obj, अचिन्हित दीर्घ obj_size,
		     काष्ठा vm_area_काष्ठा *vma);
पूर्णांक drm_gem_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma);

/**
 * drm_gem_object_get - acquire a GEM buffer object reference
 * @obj: GEM buffer object
 *
 * This function acquires an additional reference to @obj. It is illegal to
 * call this without alपढ़ोy holding a reference. No locks required.
 */
अटल अंतरभूत व्योम drm_gem_object_get(काष्ठा drm_gem_object *obj)
अणु
	kref_get(&obj->refcount);
पूर्ण

__attribute__((nonnull))
अटल अंतरभूत व्योम
__drm_gem_object_put(काष्ठा drm_gem_object *obj)
अणु
	kref_put(&obj->refcount, drm_gem_object_मुक्त);
पूर्ण

/**
 * drm_gem_object_put - drop a GEM buffer object reference
 * @obj: GEM buffer object
 *
 * This releases a reference to @obj.
 */
अटल अंतरभूत व्योम
drm_gem_object_put(काष्ठा drm_gem_object *obj)
अणु
	अगर (obj)
		__drm_gem_object_put(obj);
पूर्ण

व्योम drm_gem_object_put_locked(काष्ठा drm_gem_object *obj);

पूर्णांक drm_gem_handle_create(काष्ठा drm_file *file_priv,
			  काष्ठा drm_gem_object *obj,
			  u32 *handlep);
पूर्णांक drm_gem_handle_delete(काष्ठा drm_file *filp, u32 handle);


व्योम drm_gem_मुक्त_mmap_offset(काष्ठा drm_gem_object *obj);
पूर्णांक drm_gem_create_mmap_offset(काष्ठा drm_gem_object *obj);
पूर्णांक drm_gem_create_mmap_offset_size(काष्ठा drm_gem_object *obj, माप_प्रकार size);

काष्ठा page **drm_gem_get_pages(काष्ठा drm_gem_object *obj);
व्योम drm_gem_put_pages(काष्ठा drm_gem_object *obj, काष्ठा page **pages,
		bool dirty, bool accessed);

पूर्णांक drm_gem_objects_lookup(काष्ठा drm_file *filp, व्योम __user *bo_handles,
			   पूर्णांक count, काष्ठा drm_gem_object ***objs_out);
काष्ठा drm_gem_object *drm_gem_object_lookup(काष्ठा drm_file *filp, u32 handle);
दीर्घ drm_gem_dma_resv_रुको(काष्ठा drm_file *filep, u32 handle,
				    bool रुको_all, अचिन्हित दीर्घ समयout);
पूर्णांक drm_gem_lock_reservations(काष्ठा drm_gem_object **objs, पूर्णांक count,
			      काष्ठा ww_acquire_ctx *acquire_ctx);
व्योम drm_gem_unlock_reservations(काष्ठा drm_gem_object **objs, पूर्णांक count,
				 काष्ठा ww_acquire_ctx *acquire_ctx);
पूर्णांक drm_gem_fence_array_add(काष्ठा xarray *fence_array,
			    काष्ठा dma_fence *fence);
पूर्णांक drm_gem_fence_array_add_implicit(काष्ठा xarray *fence_array,
				     काष्ठा drm_gem_object *obj,
				     bool ग_लिखो);
पूर्णांक drm_gem_dumb_map_offset(काष्ठा drm_file *file, काष्ठा drm_device *dev,
			    u32 handle, u64 *offset);

#पूर्ण_अगर /* __DRM_GEM_H__ */
