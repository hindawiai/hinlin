<शैली गुरु>
/*
 * Copyright (C) 2015 Red Hat, Inc.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित VIRTIO_DRV_H
#घोषणा VIRTIO_DRV_H

#समावेश <linux/virtपन.स>
#समावेश <linux/virtio_ids.h>
#समावेश <linux/virtio_config.h>
#समावेश <linux/virtio_gpu.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_gem_shmem_helper.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/virtgpu_drm.h>

#घोषणा DRIVER_NAME "virtio_gpu"
#घोषणा DRIVER_DESC "virtio GPU"
#घोषणा DRIVER_DATE "0"

#घोषणा DRIVER_MAJOR 0
#घोषणा DRIVER_MINOR 1
#घोषणा DRIVER_PATCHLEVEL 0

#घोषणा STATE_INITIALIZING 0
#घोषणा STATE_OK 1
#घोषणा STATE_ERR 2

काष्ठा virtio_gpu_object_params अणु
	अचिन्हित दीर्घ size;
	bool dumb;
	/* 3d */
	bool virgl;
	bool blob;

	/* classic resources only */
	uपूर्णांक32_t क्रमmat;
	uपूर्णांक32_t width;
	uपूर्णांक32_t height;
	uपूर्णांक32_t target;
	uपूर्णांक32_t bind;
	uपूर्णांक32_t depth;
	uपूर्णांक32_t array_size;
	uपूर्णांक32_t last_level;
	uपूर्णांक32_t nr_samples;
	uपूर्णांक32_t flags;

	/* blob resources only */
	uपूर्णांक32_t ctx_id;
	uपूर्णांक32_t blob_mem;
	uपूर्णांक32_t blob_flags;
	uपूर्णांक64_t blob_id;
पूर्ण;

काष्ठा virtio_gpu_object अणु
	काष्ठा drm_gem_shmem_object base;
	uपूर्णांक32_t hw_res_handle;
	bool dumb;
	bool created;
	bool host3d_blob, guest_blob;
	uपूर्णांक32_t blob_mem, blob_flags;

	पूर्णांक uuid_state;
	uuid_t uuid;
पूर्ण;
#घोषणा gem_to_virtio_gpu_obj(gobj) \
	container_of((gobj), काष्ठा virtio_gpu_object, base.base)

काष्ठा virtio_gpu_object_shmem अणु
	काष्ठा virtio_gpu_object base;
	काष्ठा sg_table *pages;
	uपूर्णांक32_t mapped;
पूर्ण;

काष्ठा virtio_gpu_object_vram अणु
	काष्ठा virtio_gpu_object base;
	uपूर्णांक32_t map_state;
	uपूर्णांक32_t map_info;
	काष्ठा drm_mm_node vram_node;
पूर्ण;

#घोषणा to_virtio_gpu_shmem(virtio_gpu_object) \
	container_of((virtio_gpu_object), काष्ठा virtio_gpu_object_shmem, base)

#घोषणा to_virtio_gpu_vram(virtio_gpu_object) \
	container_of((virtio_gpu_object), काष्ठा virtio_gpu_object_vram, base)

काष्ठा virtio_gpu_object_array अणु
	काष्ठा ww_acquire_ctx ticket;
	काष्ठा list_head next;
	u32 nents, total;
	काष्ठा drm_gem_object *objs[];
पूर्ण;

काष्ठा virtio_gpu_vbuffer;
काष्ठा virtio_gpu_device;

प्रकार व्योम (*virtio_gpu_resp_cb)(काष्ठा virtio_gpu_device *vgdev,
				   काष्ठा virtio_gpu_vbuffer *vbuf);

काष्ठा virtio_gpu_fence_driver अणु
	atomic64_t       last_fence_id;
	uपूर्णांक64_t         current_fence_id;
	uपूर्णांक64_t         context;
	काष्ठा list_head fences;
	spinlock_t       lock;
पूर्ण;

काष्ठा virtio_gpu_fence अणु
	काष्ठा dma_fence f;
	uपूर्णांक64_t fence_id;
	काष्ठा virtio_gpu_fence_driver *drv;
	काष्ठा list_head node;
पूर्ण;

काष्ठा virtio_gpu_vbuffer अणु
	अक्षर *buf;
	पूर्णांक size;

	व्योम *data_buf;
	uपूर्णांक32_t data_size;

	अक्षर *resp_buf;
	पूर्णांक resp_size;
	virtio_gpu_resp_cb resp_cb;
	व्योम *resp_cb_data;

	काष्ठा virtio_gpu_object_array *objs;
	काष्ठा list_head list;
पूर्ण;

काष्ठा virtio_gpu_output अणु
	पूर्णांक index;
	काष्ठा drm_crtc crtc;
	काष्ठा drm_connector conn;
	काष्ठा drm_encoder enc;
	काष्ठा virtio_gpu_display_one info;
	काष्ठा virtio_gpu_update_cursor cursor;
	काष्ठा edid *edid;
	पूर्णांक cur_x;
	पूर्णांक cur_y;
	bool needs_modeset;
पूर्ण;
#घोषणा drm_crtc_to_virtio_gpu_output(x) \
	container_of(x, काष्ठा virtio_gpu_output, crtc)

काष्ठा virtio_gpu_framebuffer अणु
	काष्ठा drm_framebuffer base;
	काष्ठा virtio_gpu_fence *fence;
पूर्ण;
#घोषणा to_virtio_gpu_framebuffer(x) \
	container_of(x, काष्ठा virtio_gpu_framebuffer, base)

काष्ठा virtio_gpu_queue अणु
	काष्ठा virtqueue *vq;
	spinlock_t qlock;
	रुको_queue_head_t ack_queue;
	काष्ठा work_काष्ठा dequeue_work;
पूर्ण;

काष्ठा virtio_gpu_drv_capset अणु
	uपूर्णांक32_t id;
	uपूर्णांक32_t max_version;
	uपूर्णांक32_t max_size;
पूर्ण;

काष्ठा virtio_gpu_drv_cap_cache अणु
	काष्ठा list_head head;
	व्योम *caps_cache;
	uपूर्णांक32_t id;
	uपूर्णांक32_t version;
	uपूर्णांक32_t size;
	atomic_t is_valid;
पूर्ण;

काष्ठा virtio_gpu_device अणु
	काष्ठा device *dev;
	काष्ठा drm_device *ddev;

	काष्ठा virtio_device *vdev;

	काष्ठा virtio_gpu_output outमाला_दो[VIRTIO_GPU_MAX_SCANOUTS];
	uपूर्णांक32_t num_scanouts;

	काष्ठा virtio_gpu_queue ctrlq;
	काष्ठा virtio_gpu_queue cursorq;
	काष्ठा kmem_cache *vbufs;

	atomic_t pending_commands;

	काष्ठा ida	resource_ida;

	रुको_queue_head_t resp_wq;
	/* current display info */
	spinlock_t display_info_lock;
	bool display_info_pending;

	काष्ठा virtio_gpu_fence_driver fence_drv;

	काष्ठा ida	ctx_id_ida;

	bool has_virgl_3d;
	bool has_edid;
	bool has_indirect;
	bool has_resource_assign_uuid;
	bool has_resource_blob;
	bool has_host_visible;
	काष्ठा virtio_shm_region host_visible_region;
	काष्ठा drm_mm host_visible_mm;

	काष्ठा work_काष्ठा config_changed_work;

	काष्ठा work_काष्ठा obj_मुक्त_work;
	spinlock_t obj_मुक्त_lock;
	काष्ठा list_head obj_मुक्त_list;

	काष्ठा virtio_gpu_drv_capset *capsets;
	uपूर्णांक32_t num_capsets;
	काष्ठा list_head cap_cache;

	/* protects uuid state when exporting */
	spinlock_t resource_export_lock;
	/* protects map state and host_visible_mm */
	spinlock_t host_visible_lock;
पूर्ण;

काष्ठा virtio_gpu_fpriv अणु
	uपूर्णांक32_t ctx_id;
	bool context_created;
	काष्ठा mutex context_lock;
पूर्ण;

/* virtgpu_ioctl.c */
#घोषणा DRM_VIRTIO_NUM_IOCTLS 11
बाह्य काष्ठा drm_ioctl_desc virtio_gpu_ioctls[DRM_VIRTIO_NUM_IOCTLS];
व्योम virtio_gpu_create_context(काष्ठा drm_device *dev, काष्ठा drm_file *file);

/* virtgpu_kms.c */
पूर्णांक virtio_gpu_init(काष्ठा drm_device *dev);
व्योम virtio_gpu_deinit(काष्ठा drm_device *dev);
व्योम virtio_gpu_release(काष्ठा drm_device *dev);
पूर्णांक virtio_gpu_driver_खोलो(काष्ठा drm_device *dev, काष्ठा drm_file *file);
व्योम virtio_gpu_driver_postबंद(काष्ठा drm_device *dev, काष्ठा drm_file *file);

/* virtgpu_gem.c */
पूर्णांक virtio_gpu_gem_object_खोलो(काष्ठा drm_gem_object *obj,
			       काष्ठा drm_file *file);
व्योम virtio_gpu_gem_object_बंद(काष्ठा drm_gem_object *obj,
				 काष्ठा drm_file *file);
पूर्णांक virtio_gpu_mode_dumb_create(काष्ठा drm_file *file_priv,
				काष्ठा drm_device *dev,
				काष्ठा drm_mode_create_dumb *args);
पूर्णांक virtio_gpu_mode_dumb_mmap(काष्ठा drm_file *file_priv,
			      काष्ठा drm_device *dev,
			      uपूर्णांक32_t handle, uपूर्णांक64_t *offset_p);

काष्ठा virtio_gpu_object_array *virtio_gpu_array_alloc(u32 nents);
काष्ठा virtio_gpu_object_array*
virtio_gpu_array_from_handles(काष्ठा drm_file *drm_file, u32 *handles, u32 nents);
व्योम virtio_gpu_array_add_obj(काष्ठा virtio_gpu_object_array *objs,
			      काष्ठा drm_gem_object *obj);
पूर्णांक virtio_gpu_array_lock_resv(काष्ठा virtio_gpu_object_array *objs);
व्योम virtio_gpu_array_unlock_resv(काष्ठा virtio_gpu_object_array *objs);
व्योम virtio_gpu_array_add_fence(काष्ठा virtio_gpu_object_array *objs,
				काष्ठा dma_fence *fence);
व्योम virtio_gpu_array_put_मुक्त(काष्ठा virtio_gpu_object_array *objs);
व्योम virtio_gpu_array_put_मुक्त_delayed(काष्ठा virtio_gpu_device *vgdev,
				       काष्ठा virtio_gpu_object_array *objs);
व्योम virtio_gpu_array_put_मुक्त_work(काष्ठा work_काष्ठा *work);

/* virtgpu_vq.c */
पूर्णांक virtio_gpu_alloc_vbufs(काष्ठा virtio_gpu_device *vgdev);
व्योम virtio_gpu_मुक्त_vbufs(काष्ठा virtio_gpu_device *vgdev);
व्योम virtio_gpu_cmd_create_resource(काष्ठा virtio_gpu_device *vgdev,
				    काष्ठा virtio_gpu_object *bo,
				    काष्ठा virtio_gpu_object_params *params,
				    काष्ठा virtio_gpu_object_array *objs,
				    काष्ठा virtio_gpu_fence *fence);
व्योम virtio_gpu_cmd_unref_resource(काष्ठा virtio_gpu_device *vgdev,
				   काष्ठा virtio_gpu_object *bo);
व्योम virtio_gpu_cmd_transfer_to_host_2d(काष्ठा virtio_gpu_device *vgdev,
					uपूर्णांक64_t offset,
					uपूर्णांक32_t width, uपूर्णांक32_t height,
					uपूर्णांक32_t x, uपूर्णांक32_t y,
					काष्ठा virtio_gpu_object_array *objs,
					काष्ठा virtio_gpu_fence *fence);
व्योम virtio_gpu_cmd_resource_flush(काष्ठा virtio_gpu_device *vgdev,
				   uपूर्णांक32_t resource_id,
				   uपूर्णांक32_t x, uपूर्णांक32_t y,
				   uपूर्णांक32_t width, uपूर्णांक32_t height);
व्योम virtio_gpu_cmd_set_scanout(काष्ठा virtio_gpu_device *vgdev,
				uपूर्णांक32_t scanout_id, uपूर्णांक32_t resource_id,
				uपूर्णांक32_t width, uपूर्णांक32_t height,
				uपूर्णांक32_t x, uपूर्णांक32_t y);
व्योम virtio_gpu_object_attach(काष्ठा virtio_gpu_device *vgdev,
			      काष्ठा virtio_gpu_object *obj,
			      काष्ठा virtio_gpu_mem_entry *ents,
			      अचिन्हित पूर्णांक nents);
पूर्णांक virtio_gpu_attach_status_page(काष्ठा virtio_gpu_device *vgdev);
पूर्णांक virtio_gpu_detach_status_page(काष्ठा virtio_gpu_device *vgdev);
व्योम virtio_gpu_cursor_ping(काष्ठा virtio_gpu_device *vgdev,
			    काष्ठा virtio_gpu_output *output);
पूर्णांक virtio_gpu_cmd_get_display_info(काष्ठा virtio_gpu_device *vgdev);
पूर्णांक virtio_gpu_cmd_get_capset_info(काष्ठा virtio_gpu_device *vgdev, पूर्णांक idx);
पूर्णांक virtio_gpu_cmd_get_capset(काष्ठा virtio_gpu_device *vgdev,
			      पूर्णांक idx, पूर्णांक version,
			      काष्ठा virtio_gpu_drv_cap_cache **cache_p);
पूर्णांक virtio_gpu_cmd_get_edids(काष्ठा virtio_gpu_device *vgdev);
व्योम virtio_gpu_cmd_context_create(काष्ठा virtio_gpu_device *vgdev, uपूर्णांक32_t id,
				   uपूर्णांक32_t nlen, स्थिर अक्षर *name);
व्योम virtio_gpu_cmd_context_destroy(काष्ठा virtio_gpu_device *vgdev,
				    uपूर्णांक32_t id);
व्योम virtio_gpu_cmd_context_attach_resource(काष्ठा virtio_gpu_device *vgdev,
					    uपूर्णांक32_t ctx_id,
					    काष्ठा virtio_gpu_object_array *objs);
व्योम virtio_gpu_cmd_context_detach_resource(काष्ठा virtio_gpu_device *vgdev,
					    uपूर्णांक32_t ctx_id,
					    काष्ठा virtio_gpu_object_array *objs);
व्योम virtio_gpu_cmd_submit(काष्ठा virtio_gpu_device *vgdev,
			   व्योम *data, uपूर्णांक32_t data_size,
			   uपूर्णांक32_t ctx_id,
			   काष्ठा virtio_gpu_object_array *objs,
			   काष्ठा virtio_gpu_fence *fence);
व्योम virtio_gpu_cmd_transfer_from_host_3d(काष्ठा virtio_gpu_device *vgdev,
					  uपूर्णांक32_t ctx_id,
					  uपूर्णांक64_t offset, uपूर्णांक32_t level,
					  uपूर्णांक32_t stride,
					  uपूर्णांक32_t layer_stride,
					  काष्ठा drm_virtgpu_3d_box *box,
					  काष्ठा virtio_gpu_object_array *objs,
					  काष्ठा virtio_gpu_fence *fence);
व्योम virtio_gpu_cmd_transfer_to_host_3d(काष्ठा virtio_gpu_device *vgdev,
					uपूर्णांक32_t ctx_id,
					uपूर्णांक64_t offset, uपूर्णांक32_t level,
					uपूर्णांक32_t stride,
					uपूर्णांक32_t layer_stride,
					काष्ठा drm_virtgpu_3d_box *box,
					काष्ठा virtio_gpu_object_array *objs,
					काष्ठा virtio_gpu_fence *fence);
व्योम
virtio_gpu_cmd_resource_create_3d(काष्ठा virtio_gpu_device *vgdev,
				  काष्ठा virtio_gpu_object *bo,
				  काष्ठा virtio_gpu_object_params *params,
				  काष्ठा virtio_gpu_object_array *objs,
				  काष्ठा virtio_gpu_fence *fence);
व्योम virtio_gpu_ctrl_ack(काष्ठा virtqueue *vq);
व्योम virtio_gpu_cursor_ack(काष्ठा virtqueue *vq);
व्योम virtio_gpu_fence_ack(काष्ठा virtqueue *vq);
व्योम virtio_gpu_dequeue_ctrl_func(काष्ठा work_काष्ठा *work);
व्योम virtio_gpu_dequeue_cursor_func(काष्ठा work_काष्ठा *work);
व्योम virtio_gpu_dequeue_fence_func(काष्ठा work_काष्ठा *work);

व्योम virtio_gpu_notअगरy(काष्ठा virtio_gpu_device *vgdev);

पूर्णांक
virtio_gpu_cmd_resource_assign_uuid(काष्ठा virtio_gpu_device *vgdev,
				    काष्ठा virtio_gpu_object_array *objs);

पूर्णांक virtio_gpu_cmd_map(काष्ठा virtio_gpu_device *vgdev,
		       काष्ठा virtio_gpu_object_array *objs, uपूर्णांक64_t offset);

व्योम virtio_gpu_cmd_unmap(काष्ठा virtio_gpu_device *vgdev,
			  काष्ठा virtio_gpu_object *bo);

व्योम
virtio_gpu_cmd_resource_create_blob(काष्ठा virtio_gpu_device *vgdev,
				    काष्ठा virtio_gpu_object *bo,
				    काष्ठा virtio_gpu_object_params *params,
				    काष्ठा virtio_gpu_mem_entry *ents,
				    uपूर्णांक32_t nents);
व्योम
virtio_gpu_cmd_set_scanout_blob(काष्ठा virtio_gpu_device *vgdev,
				uपूर्णांक32_t scanout_id,
				काष्ठा virtio_gpu_object *bo,
				काष्ठा drm_framebuffer *fb,
				uपूर्णांक32_t width, uपूर्णांक32_t height,
				uपूर्णांक32_t x, uपूर्णांक32_t y);

/* virtgpu_display.c */
पूर्णांक virtio_gpu_modeset_init(काष्ठा virtio_gpu_device *vgdev);
व्योम virtio_gpu_modeset_fini(काष्ठा virtio_gpu_device *vgdev);

/* virtgpu_plane.c */
uपूर्णांक32_t virtio_gpu_translate_क्रमmat(uपूर्णांक32_t drm_fourcc);
काष्ठा drm_plane *virtio_gpu_plane_init(काष्ठा virtio_gpu_device *vgdev,
					क्रमागत drm_plane_type type,
					पूर्णांक index);

/* virtgpu_fence.c */
काष्ठा virtio_gpu_fence *virtio_gpu_fence_alloc(
	काष्ठा virtio_gpu_device *vgdev);
व्योम virtio_gpu_fence_emit(काष्ठा virtio_gpu_device *vgdev,
			  काष्ठा virtio_gpu_ctrl_hdr *cmd_hdr,
			  काष्ठा virtio_gpu_fence *fence);
व्योम virtio_gpu_fence_event_process(काष्ठा virtio_gpu_device *vdev,
				    u64 fence_id);

/* virtgpu_object.c */
व्योम virtio_gpu_cleanup_object(काष्ठा virtio_gpu_object *bo);
काष्ठा drm_gem_object *virtio_gpu_create_object(काष्ठा drm_device *dev,
						माप_प्रकार size);
पूर्णांक virtio_gpu_object_create(काष्ठा virtio_gpu_device *vgdev,
			     काष्ठा virtio_gpu_object_params *params,
			     काष्ठा virtio_gpu_object **bo_ptr,
			     काष्ठा virtio_gpu_fence *fence);

bool virtio_gpu_is_shmem(काष्ठा virtio_gpu_object *bo);

पूर्णांक virtio_gpu_resource_id_get(काष्ठा virtio_gpu_device *vgdev,
			       uपूर्णांक32_t *resid);
/* virtgpu_prime.c */
पूर्णांक virtio_gpu_resource_assign_uuid(काष्ठा virtio_gpu_device *vgdev,
				    काष्ठा virtio_gpu_object *bo);
काष्ठा dma_buf *virtgpu_gem_prime_export(काष्ठा drm_gem_object *obj,
					 पूर्णांक flags);
काष्ठा drm_gem_object *virtgpu_gem_prime_import(काष्ठा drm_device *dev,
						काष्ठा dma_buf *buf);
पूर्णांक virtgpu_gem_prime_get_uuid(काष्ठा drm_gem_object *obj,
			       uuid_t *uuid);
काष्ठा drm_gem_object *virtgpu_gem_prime_import_sg_table(
	काष्ठा drm_device *dev, काष्ठा dma_buf_attachment *attach,
	काष्ठा sg_table *sgt);

/* virtgpu_debugfs.c */
व्योम virtio_gpu_debugfs_init(काष्ठा drm_minor *minor);

/* virtgpu_vram.c */
bool virtio_gpu_is_vram(काष्ठा virtio_gpu_object *bo);
पूर्णांक virtio_gpu_vram_create(काष्ठा virtio_gpu_device *vgdev,
			   काष्ठा virtio_gpu_object_params *params,
			   काष्ठा virtio_gpu_object **bo_ptr);
#पूर्ण_अगर
