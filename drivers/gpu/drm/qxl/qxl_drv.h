<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Dave Airlie
 *          Alon Levy
 */

#अगर_अघोषित QXL_DRV_H
#घोषणा QXL_DRV_H

/*
 * Definitions taken from spice-protocol, plus kernel driver specअगरic bits.
 */

#समावेश <linux/dma-buf-map.h>
#समावेश <linux/dma-fence.h>
#समावेश <linux/firmware.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/workqueue.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_tपंचांग_helper.h>
#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/qxl_drm.h>
#समावेश <drm/tपंचांग/tपंचांग_bo_api.h>
#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>
#समावेश <drm/tपंचांग/tपंचांग_execbuf_util.h>
#समावेश <drm/tपंचांग/tपंचांग_placement.h>

#समावेश "qxl_dev.h"

काष्ठा dma_buf_map;

#घोषणा DRIVER_AUTHOR		"Dave Airlie"

#घोषणा DRIVER_NAME		"qxl"
#घोषणा DRIVER_DESC		"RH QXL"
#घोषणा DRIVER_DATE		"20120117"

#घोषणा DRIVER_MAJOR 0
#घोषणा DRIVER_MINOR 1
#घोषणा DRIVER_PATCHLEVEL 0

#घोषणा QXL_DEBUGFS_MAX_COMPONENTS		32

बाह्य पूर्णांक qxl_num_crtc;
बाह्य पूर्णांक qxl_max_ioctls;

#घोषणा QXL_INTERRUPT_MASK (\
	QXL_INTERRUPT_DISPLAY |\
	QXL_INTERRUPT_CURSOR |\
	QXL_INTERRUPT_IO_CMD |\
	QXL_INTERRUPT_CLIENT_MONITORS_CONFIG)

काष्ठा qxl_bo अणु
	काष्ठा tपंचांग_buffer_object	tbo;

	/* Protected by gem.mutex */
	काष्ठा list_head		list;
	/* Protected by tbo.reserved */
	काष्ठा tपंचांग_place		placements[3];
	काष्ठा tपंचांग_placement		placement;
	काष्ठा dma_buf_map		map;
	व्योम				*kptr;
	अचिन्हित पूर्णांक                    map_count;
	पूर्णांक                             type;

	/* Constant after initialization */
	अचिन्हित पूर्णांक is_primary:1; /* is this now a primary surface */
	अचिन्हित पूर्णांक is_dumb:1;
	काष्ठा qxl_bo *shaकरोw;
	अचिन्हित पूर्णांक hw_surf_alloc:1;
	काष्ठा qxl_surface surf;
	uपूर्णांक32_t surface_id;
	काष्ठा qxl_release *surf_create;
पूर्ण;
#घोषणा gem_to_qxl_bo(gobj) container_of((gobj), काष्ठा qxl_bo, tbo.base)
#घोषणा to_qxl_bo(tobj) container_of((tobj), काष्ठा qxl_bo, tbo)

काष्ठा qxl_gem अणु
	काष्ठा mutex		mutex;
	काष्ठा list_head	objects;
पूर्ण;

काष्ठा qxl_bo_list अणु
	काष्ठा tपंचांग_validate_buffer tv;
पूर्ण;

काष्ठा qxl_crtc अणु
	काष्ठा drm_crtc base;
	पूर्णांक index;

	काष्ठा qxl_bo *cursor_bo;
पूर्ण;

काष्ठा qxl_output अणु
	पूर्णांक index;
	काष्ठा drm_connector base;
	काष्ठा drm_encoder enc;
पूर्ण;

#घोषणा to_qxl_crtc(x) container_of(x, काष्ठा qxl_crtc, base)
#घोषणा drm_connector_to_qxl_output(x) container_of(x, काष्ठा qxl_output, base)
#घोषणा drm_encoder_to_qxl_output(x) container_of(x, काष्ठा qxl_output, enc)

काष्ठा qxl_mman अणु
	काष्ठा tपंचांग_device		bdev;
पूर्ण;

काष्ठा qxl_memslot अणु
	पूर्णांक             index;
	स्थिर अक्षर      *name;
	uपूर्णांक8_t		generation;
	uपूर्णांक64_t	start_phys_addr;
	uपूर्णांक64_t	size;
	uपूर्णांक64_t	high_bits;
पूर्ण;

क्रमागत अणु
	QXL_RELEASE_DRAWABLE,
	QXL_RELEASE_SURFACE_CMD,
	QXL_RELEASE_CURSOR_CMD,
पूर्ण;

/* drm_ prefix to dअगरferentiate from qxl_release_info in
 * spice-protocol/qxl_dev.h */
#घोषणा QXL_MAX_RES 96
काष्ठा qxl_release अणु
	काष्ठा dma_fence base;

	पूर्णांक id;
	पूर्णांक type;
	काष्ठा qxl_bo *release_bo;
	uपूर्णांक32_t release_offset;
	uपूर्णांक32_t surface_release_id;
	काष्ठा ww_acquire_ctx ticket;
	काष्ठा list_head bos;
पूर्ण;

काष्ठा qxl_drm_chunk अणु
	काष्ठा list_head head;
	काष्ठा qxl_bo *bo;
पूर्ण;

काष्ठा qxl_drm_image अणु
	काष्ठा qxl_bo *bo;
	काष्ठा list_head chunk_list;
पूर्ण;

/*
 * Debugfs
 */
काष्ठा qxl_debugfs अणु
	काष्ठा drm_info_list	*files;
	अचिन्हित पूर्णांक num_files;
पूर्ण;

काष्ठा qxl_device अणु
	काष्ठा drm_device ddev;

	resource_माप_प्रकार vram_base, vram_size;
	resource_माप_प्रकार surfaceram_base, surfaceram_size;
	resource_माप_प्रकार rom_base, rom_size;
	काष्ठा qxl_rom *rom;

	काष्ठा qxl_mode *modes;
	काष्ठा qxl_bo *monitors_config_bo;
	काष्ठा qxl_monitors_config *monitors_config;

	/* last received client_monitors_config */
	काष्ठा qxl_monitors_config *client_monitors_config;

	पूर्णांक io_base;
	व्योम *ram;
	काष्ठा qxl_mman		mman;
	काष्ठा qxl_gem		gem;

	व्योम *ram_physical;

	काष्ठा qxl_ring *release_ring;
	काष्ठा qxl_ring *command_ring;
	काष्ठा qxl_ring *cursor_ring;

	काष्ठा qxl_ram_header *ram_header;

	काष्ठा qxl_bo *primary_bo;
	काष्ठा qxl_bo *dumb_shaकरोw_bo;
	काष्ठा qxl_head *dumb_heads;

	काष्ठा qxl_memslot मुख्य_slot;
	काष्ठा qxl_memslot surfaces_slot;

	spinlock_t	release_lock;
	काष्ठा idr	release_idr;
	uपूर्णांक32_t	release_seqno;
	atomic_t	release_count;
	रुको_queue_head_t release_event;
	spinlock_t release_idr_lock;
	काष्ठा mutex	async_io_mutex;
	अचिन्हित पूर्णांक last_sent_io_cmd;

	/* पूर्णांकerrupt handling */
	atomic_t irq_received;
	atomic_t irq_received_display;
	atomic_t irq_received_cursor;
	atomic_t irq_received_io_cmd;
	अचिन्हित पूर्णांक irq_received_error;
	रुको_queue_head_t display_event;
	रुको_queue_head_t cursor_event;
	रुको_queue_head_t io_cmd_event;
	काष्ठा work_काष्ठा client_monitors_config_work;

	/* debugfs */
	काष्ठा qxl_debugfs	debugfs[QXL_DEBUGFS_MAX_COMPONENTS];
	अचिन्हित पूर्णांक debugfs_count;

	काष्ठा mutex		update_area_mutex;

	काष्ठा idr	surf_id_idr;
	spinlock_t surf_id_idr_lock;
	पूर्णांक last_alloced_surf_id;

	काष्ठा mutex surf_evict_mutex;
	काष्ठा io_mapping *vram_mapping;
	काष्ठा io_mapping *surface_mapping;

	/* */
	काष्ठा mutex release_mutex;
	काष्ठा qxl_bo *current_release_bo[3];
	पूर्णांक current_release_bo_offset[3];

	काष्ठा work_काष्ठा gc_work;

	काष्ठा drm_property *hotplug_mode_update_property;
	पूर्णांक monitors_config_width;
	पूर्णांक monitors_config_height;
पूर्ण;

#घोषणा to_qxl(dev) container_of(dev, काष्ठा qxl_device, ddev)

पूर्णांक qxl_debugfs_fence_init(काष्ठा qxl_device *rdev);

बाह्य स्थिर काष्ठा drm_ioctl_desc qxl_ioctls[];
बाह्य पूर्णांक qxl_max_ioctl;

पूर्णांक qxl_device_init(काष्ठा qxl_device *qdev, काष्ठा pci_dev *pdev);
व्योम qxl_device_fini(काष्ठा qxl_device *qdev);

पूर्णांक qxl_modeset_init(काष्ठा qxl_device *qdev);
व्योम qxl_modeset_fini(काष्ठा qxl_device *qdev);

पूर्णांक qxl_bo_init(काष्ठा qxl_device *qdev);
व्योम qxl_bo_fini(काष्ठा qxl_device *qdev);

व्योम qxl_reinit_memslots(काष्ठा qxl_device *qdev);
पूर्णांक qxl_surf_evict(काष्ठा qxl_device *qdev);
पूर्णांक qxl_vram_evict(काष्ठा qxl_device *qdev);

काष्ठा qxl_ring *qxl_ring_create(काष्ठा qxl_ring_header *header,
				 पूर्णांक element_size,
				 पूर्णांक n_elements,
				 पूर्णांक prod_notअगरy,
				 bool set_prod_notअगरy,
				 रुको_queue_head_t *push_event);
व्योम qxl_ring_मुक्त(काष्ठा qxl_ring *ring);
व्योम qxl_ring_init_hdr(काष्ठा qxl_ring *ring);
पूर्णांक qxl_check_idle(काष्ठा qxl_ring *ring);

अटल अंतरभूत uपूर्णांक64_t
qxl_bo_physical_address(काष्ठा qxl_device *qdev, काष्ठा qxl_bo *bo,
			अचिन्हित दीर्घ offset)
अणु
	काष्ठा qxl_memslot *slot =
		(bo->tbo.mem.mem_type == TTM_PL_VRAM)
		? &qdev->मुख्य_slot : &qdev->surfaces_slot;

       /* TODO - need to hold one of the locks to पढ़ो bo->tbo.mem.start */

	वापस slot->high_bits | ((bo->tbo.mem.start << PAGE_SHIFT) + offset);
पूर्ण

/* qxl_display.c */
व्योम qxl_display_पढ़ो_client_monitors_config(काष्ठा qxl_device *qdev);
पूर्णांक qxl_create_monitors_object(काष्ठा qxl_device *qdev);
पूर्णांक qxl_destroy_monitors_object(काष्ठा qxl_device *qdev);

/* qxl_gem.c */
व्योम qxl_gem_init(काष्ठा qxl_device *qdev);
व्योम qxl_gem_fini(काष्ठा qxl_device *qdev);
पूर्णांक qxl_gem_object_create(काष्ठा qxl_device *qdev, पूर्णांक size,
			  पूर्णांक alignment, पूर्णांक initial_करोमुख्य,
			  bool discardable, bool kernel,
			  काष्ठा qxl_surface *surf,
			  काष्ठा drm_gem_object **obj);
पूर्णांक qxl_gem_object_create_with_handle(काष्ठा qxl_device *qdev,
				      काष्ठा drm_file *file_priv,
				      u32 करोमुख्य,
				      माप_प्रकार size,
				      काष्ठा qxl_surface *surf,
				      काष्ठा qxl_bo **qobj,
				      uपूर्णांक32_t *handle);
व्योम qxl_gem_object_मुक्त(काष्ठा drm_gem_object *gobj);
पूर्णांक qxl_gem_object_खोलो(काष्ठा drm_gem_object *obj, काष्ठा drm_file *file_priv);
व्योम qxl_gem_object_बंद(काष्ठा drm_gem_object *obj,
			  काष्ठा drm_file *file_priv);
व्योम qxl_bo_क्रमce_delete(काष्ठा qxl_device *qdev);

/* qxl_dumb.c */
पूर्णांक qxl_mode_dumb_create(काष्ठा drm_file *file_priv,
			 काष्ठा drm_device *dev,
			 काष्ठा drm_mode_create_dumb *args);
पूर्णांक qxl_mode_dumb_mmap(काष्ठा drm_file *filp,
		       काष्ठा drm_device *dev,
		       uपूर्णांक32_t handle, uपूर्णांक64_t *offset_p);

/* qxl tपंचांग */
पूर्णांक qxl_tपंचांग_init(काष्ठा qxl_device *qdev);
व्योम qxl_tपंचांग_fini(काष्ठा qxl_device *qdev);
पूर्णांक qxl_tपंचांग_io_mem_reserve(काष्ठा tपंचांग_device *bdev,
			   काष्ठा tपंचांग_resource *mem);

/* qxl image */

पूर्णांक qxl_image_init(काष्ठा qxl_device *qdev,
		   काष्ठा qxl_release *release,
		   काष्ठा qxl_drm_image *dimage,
		   स्थिर uपूर्णांक8_t *data,
		   पूर्णांक x, पूर्णांक y, पूर्णांक width, पूर्णांक height,
		   पूर्णांक depth, पूर्णांक stride);
पूर्णांक
qxl_image_alloc_objects(काष्ठा qxl_device *qdev,
			काष्ठा qxl_release *release,
			काष्ठा qxl_drm_image **image_ptr,
			पूर्णांक height, पूर्णांक stride);
व्योम qxl_image_मुक्त_objects(काष्ठा qxl_device *qdev, काष्ठा qxl_drm_image *dimage);

व्योम qxl_update_screen(काष्ठा qxl_device *qxl);

/* qxl io operations (qxl_cmd.c) */

व्योम qxl_io_create_primary(काष्ठा qxl_device *qdev,
			   काष्ठा qxl_bo *bo);
व्योम qxl_io_destroy_primary(काष्ठा qxl_device *qdev);
व्योम qxl_io_memslot_add(काष्ठा qxl_device *qdev, uपूर्णांक8_t id);
व्योम qxl_io_notअगरy_oom(काष्ठा qxl_device *qdev);

पूर्णांक qxl_io_update_area(काष्ठा qxl_device *qdev, काष्ठा qxl_bo *surf,
		       स्थिर काष्ठा qxl_rect *area);

व्योम qxl_io_reset(काष्ठा qxl_device *qdev);
व्योम qxl_io_monitors_config(काष्ठा qxl_device *qdev);
पूर्णांक qxl_ring_push(काष्ठा qxl_ring *ring, स्थिर व्योम *new_elt, bool पूर्णांकerruptible);
व्योम qxl_io_flush_release(काष्ठा qxl_device *qdev);
व्योम qxl_io_flush_surfaces(काष्ठा qxl_device *qdev);

जोड़ qxl_release_info *qxl_release_map(काष्ठा qxl_device *qdev,
					काष्ठा qxl_release *release);
व्योम qxl_release_unmap(काष्ठा qxl_device *qdev,
		       काष्ठा qxl_release *release,
		       जोड़ qxl_release_info *info);
पूर्णांक qxl_release_list_add(काष्ठा qxl_release *release, काष्ठा qxl_bo *bo);
पूर्णांक qxl_release_reserve_list(काष्ठा qxl_release *release, bool no_पूर्णांकr);
व्योम qxl_release_backoff_reserve_list(काष्ठा qxl_release *release);
व्योम qxl_release_fence_buffer_objects(काष्ठा qxl_release *release);

पूर्णांक qxl_alloc_surface_release_reserved(काष्ठा qxl_device *qdev,
				       क्रमागत qxl_surface_cmd_type surface_cmd_type,
				       काष्ठा qxl_release *create_rel,
				       काष्ठा qxl_release **release);
पूर्णांक qxl_alloc_release_reserved(काष्ठा qxl_device *qdev, अचिन्हित दीर्घ size,
			       पूर्णांक type, काष्ठा qxl_release **release,
			       काष्ठा qxl_bo **rbo);

पूर्णांक
qxl_push_command_ring_release(काष्ठा qxl_device *qdev, काष्ठा qxl_release *release,
			      uपूर्णांक32_t type, bool पूर्णांकerruptible);
पूर्णांक
qxl_push_cursor_ring_release(काष्ठा qxl_device *qdev, काष्ठा qxl_release *release,
			     uपूर्णांक32_t type, bool पूर्णांकerruptible);
पूर्णांक qxl_alloc_bo_reserved(काष्ठा qxl_device *qdev,
			  काष्ठा qxl_release *release,
			  अचिन्हित दीर्घ size,
			  काष्ठा qxl_bo **_bo);
/* qxl drawing commands */

व्योम qxl_draw_dirty_fb(काष्ठा qxl_device *qdev,
		       काष्ठा drm_framebuffer *fb,
		       काष्ठा qxl_bo *bo,
		       अचिन्हित पूर्णांक flags, अचिन्हित पूर्णांक color,
		       काष्ठा drm_clip_rect *clips,
		       अचिन्हित पूर्णांक num_clips, पूर्णांक inc,
		       uपूर्णांक32_t dumb_shaकरोw_offset);

व्योम qxl_release_मुक्त(काष्ठा qxl_device *qdev,
		      काष्ठा qxl_release *release);

/* used by qxl_debugfs_release */
काष्ठा qxl_release *qxl_release_from_id_locked(काष्ठा qxl_device *qdev,
						   uपूर्णांक64_t id);

bool qxl_queue_garbage_collect(काष्ठा qxl_device *qdev, bool flush);
पूर्णांक qxl_garbage_collect(काष्ठा qxl_device *qdev);

/* debugfs */

व्योम qxl_debugfs_init(काष्ठा drm_minor *minor);
व्योम qxl_tपंचांग_debugfs_init(काष्ठा qxl_device *qdev);

/* qxl_prime.c */
पूर्णांक qxl_gem_prime_pin(काष्ठा drm_gem_object *obj);
व्योम qxl_gem_prime_unpin(काष्ठा drm_gem_object *obj);
काष्ठा sg_table *qxl_gem_prime_get_sg_table(काष्ठा drm_gem_object *obj);
काष्ठा drm_gem_object *qxl_gem_prime_import_sg_table(
	काष्ठा drm_device *dev, काष्ठा dma_buf_attachment *attach,
	काष्ठा sg_table *sgt);
पूर्णांक qxl_gem_prime_vmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map);
व्योम qxl_gem_prime_vunmap(काष्ठा drm_gem_object *obj,
			  काष्ठा dma_buf_map *map);
पूर्णांक qxl_gem_prime_mmap(काष्ठा drm_gem_object *obj,
				काष्ठा vm_area_काष्ठा *vma);

/* qxl_irq.c */
पूर्णांक qxl_irq_init(काष्ठा qxl_device *qdev);
irqवापस_t qxl_irq_handler(पूर्णांक irq, व्योम *arg);

व्योम qxl_debugfs_add_files(काष्ठा qxl_device *qdev,
			   काष्ठा drm_info_list *files,
			   अचिन्हित पूर्णांक nfiles);

पूर्णांक qxl_surface_id_alloc(काष्ठा qxl_device *qdev,
			 काष्ठा qxl_bo *surf);
व्योम qxl_surface_id_dealloc(काष्ठा qxl_device *qdev,
			    uपूर्णांक32_t surface_id);
पूर्णांक qxl_hw_surface_alloc(काष्ठा qxl_device *qdev,
			 काष्ठा qxl_bo *surf);
पूर्णांक qxl_hw_surface_dealloc(काष्ठा qxl_device *qdev,
			   काष्ठा qxl_bo *surf);

पूर्णांक qxl_bo_check_id(काष्ठा qxl_device *qdev, काष्ठा qxl_bo *bo);

काष्ठा qxl_drv_surface *
qxl_surface_lookup(काष्ठा drm_device *dev, पूर्णांक surface_id);
व्योम qxl_surface_evict(काष्ठा qxl_device *qdev, काष्ठा qxl_bo *surf, bool मुक्तing);

#पूर्ण_अगर
