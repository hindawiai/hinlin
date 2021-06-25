<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/**************************************************************************
 *
 * Copyright 2009-2015 VMware, Inc., Palo Alto, CA., USA
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

#अगर_अघोषित _VMWGFX_DRV_H_
#घोषणा _VMWGFX_DRV_H_

#समावेश <linux/suspend.h>
#समावेश <linux/sync_file.h>

#समावेश <drm/drm_auth.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_file.h>
#समावेश <drm/drm_hashtab.h>
#समावेश <drm/drm_rect.h>

#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>
#समावेश <drm/tपंचांग/tपंचांग_execbuf_util.h>

#समावेश "ttm_lock.h"
#समावेश "ttm_object.h"

#समावेश "vmwgfx_fence.h"
#समावेश "vmwgfx_reg.h"
#समावेश "vmwgfx_validation.h"

/*
 * FIXME: vmwgfx_drm.h needs to be last due to dependencies.
 * uapi headers should not depend on header files outside uapi/.
 */
#समावेश <drm/vmwgfx_drm.h>


#घोषणा VMWGFX_DRIVER_NAME "vmwgfx"
#घोषणा VMWGFX_DRIVER_DATE "20210218"
#घोषणा VMWGFX_DRIVER_MAJOR 2
#घोषणा VMWGFX_DRIVER_MINOR 18
#घोषणा VMWGFX_DRIVER_PATCHLEVEL 1
#घोषणा VMWGFX_FIFO_STATIC_SIZE (1024*1024)
#घोषणा VMWGFX_MAX_RELOCATIONS 2048
#घोषणा VMWGFX_MAX_VALIDATIONS 2048
#घोषणा VMWGFX_MAX_DISPLAYS 16
#घोषणा VMWGFX_CMD_BOUNCE_INIT_SIZE 32768
#घोषणा VMWGFX_ENABLE_SCREEN_TARGET_OTABLE 1

#घोषणा VMWGFX_PCI_ID_SVGA2              0x0405

/*
 * Perhaps we should have sysfs entries क्रम these.
 */
#घोषणा VMWGFX_NUM_GB_CONTEXT 256
#घोषणा VMWGFX_NUM_GB_SHADER 20000
#घोषणा VMWGFX_NUM_GB_SURFACE 32768
#घोषणा VMWGFX_NUM_GB_SCREEN_TARGET VMWGFX_MAX_DISPLAYS
#घोषणा VMWGFX_NUM_DXCONTEXT 256
#घोषणा VMWGFX_NUM_DXQUERY 512
#घोषणा VMWGFX_NUM_MOB (VMWGFX_NUM_GB_CONTEXT +\
			VMWGFX_NUM_GB_SHADER +\
			VMWGFX_NUM_GB_SURFACE +\
			VMWGFX_NUM_GB_SCREEN_TARGET)

#घोषणा VMW_PL_GMR (TTM_PL_PRIV + 0)
#घोषणा VMW_PL_MOB (TTM_PL_PRIV + 1)

#घोषणा VMW_RES_CONTEXT tपंचांग_driver_type0
#घोषणा VMW_RES_SURFACE tपंचांग_driver_type1
#घोषणा VMW_RES_STREAM tपंचांग_driver_type2
#घोषणा VMW_RES_FENCE tपंचांग_driver_type3
#घोषणा VMW_RES_SHADER tपंचांग_driver_type4

काष्ठा vmw_fpriv अणु
	काष्ठा tपंचांग_object_file *tfile;
	bool gb_aware; /* user-space is guest-backed aware */
पूर्ण;

/**
 * काष्ठा vmw_buffer_object - TTM buffer object with vmwgfx additions
 * @base: The TTM buffer object
 * @res_tree: RB tree of resources using this buffer object as a backing MOB
 * @cpu_ग_लिखोrs: Number of synccpu ग_लिखो grअसल. Protected by reservation when
 * increased. May be decreased without reservation.
 * @dx_query_ctx: DX context अगर this buffer object is used as a DX query MOB
 * @map: Kmap object क्रम semi-persistent mappings
 * @res_prios: Eviction priority counts क्रम attached resources
 * @dirty: काष्ठाure क्रम user-space dirty-tracking
 */
काष्ठा vmw_buffer_object अणु
	काष्ठा tपंचांग_buffer_object base;
	काष्ठा rb_root res_tree;
	atomic_t cpu_ग_लिखोrs;
	/* Not ref-counted.  Protected by binding_mutex */
	काष्ठा vmw_resource *dx_query_ctx;
	/* Protected by reservation */
	काष्ठा tपंचांग_bo_kmap_obj map;
	u32 res_prios[TTM_MAX_BO_PRIORITY];
	काष्ठा vmw_bo_dirty *dirty;
पूर्ण;

/**
 * काष्ठा vmw_validate_buffer - Carries validation info about buffers.
 *
 * @base: Validation info क्रम TTM.
 * @hash: Hash entry क्रम quick lookup of the TTM buffer object.
 *
 * This काष्ठाure contains also driver निजी validation info
 * on top of the info needed by TTM.
 */
काष्ठा vmw_validate_buffer अणु
	काष्ठा tपंचांग_validate_buffer base;
	काष्ठा drm_hash_item hash;
	bool validate_as_mob;
पूर्ण;

काष्ठा vmw_res_func;


/**
 * काष्ठा vmw-resource - base class क्रम hardware resources
 *
 * @kref: For refcounting.
 * @dev_priv: Poपूर्णांकer to the device निजी क्रम this resource. Immutable.
 * @id: Device id. Protected by @dev_priv::resource_lock.
 * @backup_size: Backup buffer size. Immutable.
 * @res_dirty: Resource contains data not yet in the backup buffer. Protected
 * by resource reserved.
 * @backup_dirty: Backup buffer contains data not yet in the HW resource.
 * Protected by resource reserved.
 * @coherent: Emulate coherency by tracking vm accesses.
 * @backup: The backup buffer अगर any. Protected by resource reserved.
 * @backup_offset: Offset पूर्णांकo the backup buffer अगर any. Protected by resource
 * reserved. Note that only a few resource types can have a @backup_offset
 * dअगरferent from zero.
 * @pin_count: The pin count क्रम this resource. A pinned resource has a
 * pin-count greater than zero. It is not on the resource LRU lists and its
 * backup buffer is pinned. Hence it can't be evicted.
 * @func: Method vtable क्रम this resource. Immutable.
 * @mob_node; Node क्रम the MOB backup rbtree. Protected by @backup reserved.
 * @lru_head: List head क्रम the LRU list. Protected by @dev_priv::resource_lock.
 * @binding_head: List head क्रम the context binding list. Protected by
 * the @dev_priv::binding_mutex
 * @res_मुक्त: The resource deकाष्ठाor.
 * @hw_destroy: Callback to destroy the resource on the device, as part of
 * resource deकाष्ठाion.
 */
काष्ठा vmw_resource_dirty;
काष्ठा vmw_resource अणु
	काष्ठा kref kref;
	काष्ठा vmw_निजी *dev_priv;
	पूर्णांक id;
	u32 used_prio;
	अचिन्हित दीर्घ backup_size;
	u32 res_dirty : 1;
	u32 backup_dirty : 1;
	u32 coherent : 1;
	काष्ठा vmw_buffer_object *backup;
	अचिन्हित दीर्घ backup_offset;
	अचिन्हित दीर्घ pin_count;
	स्थिर काष्ठा vmw_res_func *func;
	काष्ठा rb_node mob_node;
	काष्ठा list_head lru_head;
	काष्ठा list_head binding_head;
	काष्ठा vmw_resource_dirty *dirty;
	व्योम (*res_मुक्त) (काष्ठा vmw_resource *res);
	व्योम (*hw_destroy) (काष्ठा vmw_resource *res);
पूर्ण;


/*
 * Resources that are managed using ioctls.
 */
क्रमागत vmw_res_type अणु
	vmw_res_context,
	vmw_res_surface,
	vmw_res_stream,
	vmw_res_shader,
	vmw_res_dx_context,
	vmw_res_cotable,
	vmw_res_view,
	vmw_res_streamoutput,
	vmw_res_max
पूर्ण;

/*
 * Resources that are managed using command streams.
 */
क्रमागत vmw_cmdbuf_res_type अणु
	vmw_cmdbuf_res_shader,
	vmw_cmdbuf_res_view,
	vmw_cmdbuf_res_streamoutput
पूर्ण;

काष्ठा vmw_cmdbuf_res_manager;

काष्ठा vmw_cursor_snooper अणु
	माप_प्रकार age;
	uपूर्णांक32_t *image;
पूर्ण;

काष्ठा vmw_framebuffer;
काष्ठा vmw_surface_offset;

/**
 * काष्ठा vmw_surface_metadata - Metadata describing a surface.
 *
 * @flags: Device flags.
 * @क्रमmat: Surface SVGA3D_x क्रमmat.
 * @mip_levels: Mip level क्रम each face. For GB first index is used only.
 * @multisample_count: Sample count.
 * @multisample_pattern: Sample patterns.
 * @quality_level: Quality level.
 * @स्वतःgen_filter: Filter क्रम स्वतःmatically generated mipmaps.
 * @array_size: Number of array elements क्रम a 1D/2D texture. For cubemap
                texture number of faces * array_size. This should be 0 क्रम pre
		SM4 device.
 * @buffer_byte_stride: Buffer byte stride.
 * @num_sizes: Size of @sizes. For GB surface this should always be 1.
 * @base_size: Surface dimension.
 * @sizes: Array representing mip sizes. Legacy only.
 * @scanout: Whether this surface will be used क्रम scanout.
 *
 * This tracks metadata क्रम both legacy and guest backed surface.
 */
काष्ठा vmw_surface_metadata अणु
	u64 flags;
	u32 क्रमmat;
	u32 mip_levels[DRM_VMW_MAX_SURFACE_FACES];
	u32 multisample_count;
	u32 multisample_pattern;
	u32 quality_level;
	u32 स्वतःgen_filter;
	u32 array_size;
	u32 num_sizes;
	u32 buffer_byte_stride;
	काष्ठा drm_vmw_size base_size;
	काष्ठा drm_vmw_size *sizes;
	bool scanout;
पूर्ण;

/**
 * काष्ठा vmw_surface: Resource काष्ठाure क्रम a surface.
 *
 * @res: The base resource क्रम this surface.
 * @metadata: Metadata क्रम this surface resource.
 * @snooper: Cursor data. Legacy surface only.
 * @offsets: Legacy surface only.
 * @view_list: List of views bound to this surface.
 */
काष्ठा vmw_surface अणु
	काष्ठा vmw_resource res;
	काष्ठा vmw_surface_metadata metadata;
	काष्ठा vmw_cursor_snooper snooper;
	काष्ठा vmw_surface_offset *offsets;
	काष्ठा list_head view_list;
पूर्ण;

काष्ठा vmw_fअगरo_state अणु
	अचिन्हित दीर्घ reserved_size;
	u32 *dynamic_buffer;
	u32 *अटल_buffer;
	अचिन्हित दीर्घ अटल_buffer_size;
	bool using_bounce_buffer;
	uपूर्णांक32_t capabilities;
	काष्ठा mutex fअगरo_mutex;
	काष्ठा rw_semaphore rwsem;
	bool dx;
पूर्ण;

/**
 * काष्ठा vmw_res_cache_entry - resource inक्रमmation cache entry
 * @handle: User-space handle of a resource.
 * @res: Non-ref-counted poपूर्णांकer to the resource.
 * @valid_handle: Whether the @handle member is valid.
 * @valid: Whether the entry is valid, which also implies that the execbuf
 * code holds a reference to the resource, and it's placed on the
 * validation list.
 *
 * Used to aव्योम frequent repeated user-space handle lookups of the
 * same resource.
 */
काष्ठा vmw_res_cache_entry अणु
	uपूर्णांक32_t handle;
	काष्ठा vmw_resource *res;
	व्योम *निजी;
	अचिन्हित लघु valid_handle;
	अचिन्हित लघु valid;
पूर्ण;

/**
 * क्रमागत vmw_dma_map_mode - indicate how to perक्रमm TTM page dma mappings.
 */
क्रमागत vmw_dma_map_mode अणु
	vmw_dma_phys,           /* Use physical page addresses */
	vmw_dma_alloc_coherent, /* Use TTM coherent pages */
	vmw_dma_map_populate,   /* Unmap from DMA just after unpopulate */
	vmw_dma_map_bind,       /* Unmap from DMA just beक्रमe unbind */
	vmw_dma_map_max
पूर्ण;

/**
 * काष्ठा vmw_sg_table - Scatter/gather table क्रम binding, with additional
 * device-specअगरic inक्रमmation.
 *
 * @sgt: Poपूर्णांकer to a काष्ठा sg_table with binding inक्रमmation
 * @num_regions: Number of regions with device-address contiguous pages
 */
काष्ठा vmw_sg_table अणु
	क्रमागत vmw_dma_map_mode mode;
	काष्ठा page **pages;
	स्थिर dma_addr_t *addrs;
	काष्ठा sg_table *sgt;
	अचिन्हित दीर्घ num_regions;
	अचिन्हित दीर्घ num_pages;
पूर्ण;

/**
 * काष्ठा vmw_piter - Page iterator that iterates over a list of pages
 * and DMA addresses that could be either a scatter-gather list or
 * arrays
 *
 * @pages: Array of page poपूर्णांकers to the pages.
 * @addrs: DMA addresses to the pages अगर coherent pages are used.
 * @iter: Scatter-gather page iterator. Current position in SG list.
 * @i: Current position in arrays.
 * @num_pages: Number of pages total.
 * @next: Function to advance the iterator. Returns false अगर past the list
 * of pages, true otherwise.
 * @dma_address: Function to वापस the DMA address of the current page.
 */
काष्ठा vmw_piter अणु
	काष्ठा page **pages;
	स्थिर dma_addr_t *addrs;
	काष्ठा sg_dma_page_iter iter;
	अचिन्हित दीर्घ i;
	अचिन्हित दीर्घ num_pages;
	bool (*next)(काष्ठा vmw_piter *);
	dma_addr_t (*dma_address)(काष्ठा vmw_piter *);
	काष्ठा page *(*page)(काष्ठा vmw_piter *);
पूर्ण;

/*
 * क्रमागत vmw_display_unit_type - Describes the display unit
 */
क्रमागत vmw_display_unit_type अणु
	vmw_du_invalid = 0,
	vmw_du_legacy,
	vmw_du_screen_object,
	vmw_du_screen_target
पूर्ण;

काष्ठा vmw_validation_context;
काष्ठा vmw_ctx_validation_info;

/**
 * काष्ठा vmw_sw_context - Command submission context
 * @res_ht: Poपूर्णांकer hash table used to find validation duplicates
 * @kernel: Whether the command buffer originates from kernel code rather
 * than from user-space
 * @fp: If @kernel is false, poपूर्णांकs to the file of the client. Otherwise
 * शून्य
 * @cmd_bounce: Command bounce buffer used क्रम command validation beक्रमe
 * copying to fअगरo space
 * @cmd_bounce_size: Current command bounce buffer size
 * @cur_query_bo: Current buffer object used as query result buffer
 * @bo_relocations: List of buffer object relocations
 * @res_relocations: List of resource relocations
 * @buf_start: Poपूर्णांकer to start of memory where command validation takes
 * place
 * @res_cache: Cache of recently looked up resources
 * @last_query_ctx: Last context that submitted a query
 * @needs_post_query_barrier: Whether a query barrier is needed after
 * command submission
 * @staged_bindings: Cached per-context binding tracker
 * @staged_bindings_inuse: Whether the cached per-context binding tracker
 * is in use
 * @staged_cmd_res: List of staged command buffer managed resources in this
 * command buffer
 * @ctx_list: List of context resources referenced in this command buffer
 * @dx_ctx_node: Validation metadata of the current DX context
 * @dx_query_mob: The MOB used क्रम DX queries
 * @dx_query_ctx: The DX context used क्रम the last DX query
 * @man: Poपूर्णांकer to the command buffer managed resource manager
 * @ctx: The validation context
 */
काष्ठा vmw_sw_contextअणु
	काष्ठा drm_खोलो_hash res_ht;
	bool res_ht_initialized;
	bool kernel;
	काष्ठा vmw_fpriv *fp;
	uपूर्णांक32_t *cmd_bounce;
	uपूर्णांक32_t cmd_bounce_size;
	काष्ठा vmw_buffer_object *cur_query_bo;
	काष्ठा list_head bo_relocations;
	काष्ठा list_head res_relocations;
	uपूर्णांक32_t *buf_start;
	काष्ठा vmw_res_cache_entry res_cache[vmw_res_max];
	काष्ठा vmw_resource *last_query_ctx;
	bool needs_post_query_barrier;
	काष्ठा vmw_ctx_binding_state *staged_bindings;
	bool staged_bindings_inuse;
	काष्ठा list_head staged_cmd_res;
	काष्ठा list_head ctx_list;
	काष्ठा vmw_ctx_validation_info *dx_ctx_node;
	काष्ठा vmw_buffer_object *dx_query_mob;
	काष्ठा vmw_resource *dx_query_ctx;
	काष्ठा vmw_cmdbuf_res_manager *man;
	काष्ठा vmw_validation_context *ctx;
पूर्ण;

काष्ठा vmw_legacy_display;
काष्ठा vmw_overlay;

काष्ठा vmw_vga_topology_state अणु
	uपूर्णांक32_t width;
	uपूर्णांक32_t height;
	uपूर्णांक32_t primary;
	uपूर्णांक32_t pos_x;
	uपूर्णांक32_t pos_y;
पूर्ण;


/*
 * काष्ठा vmw_otable - Guest Memory OBject table metadata
 *
 * @size:           Size of the table (page-aligned).
 * @page_table:     Poपूर्णांकer to a काष्ठा vmw_mob holding the page table.
 */
काष्ठा vmw_otable अणु
	अचिन्हित दीर्घ size;
	काष्ठा vmw_mob *page_table;
	bool enabled;
पूर्ण;

काष्ठा vmw_otable_batch अणु
	अचिन्हित num_otables;
	काष्ठा vmw_otable *otables;
	काष्ठा vmw_resource *context;
	काष्ठा tपंचांग_buffer_object *otable_bo;
पूर्ण;

क्रमागत अणु
	VMW_IRQTHREAD_FENCE,
	VMW_IRQTHREAD_CMDBUF,
	VMW_IRQTHREAD_MAX
पूर्ण;

/**
 * क्रमागत vmw_sm_type - Graphics context capability supported by device.
 * @VMW_SM_LEGACY: Pre DX context.
 * @VMW_SM_4: Context support upto SM4.
 * @VMW_SM_4_1: Context support upto SM4_1.
 * @VMW_SM_5: Context support up to SM5.
 * @VMW_SM_MAX: Should be the last.
 */
क्रमागत vmw_sm_type अणु
	VMW_SM_LEGACY = 0,
	VMW_SM_4,
	VMW_SM_4_1,
	VMW_SM_5,
	VMW_SM_MAX
पूर्ण;

काष्ठा vmw_निजी अणु
	काष्ठा drm_device drm;
	काष्ठा tपंचांग_device bdev;

	काष्ठा vmw_fअगरo_state fअगरo;

	काष्ठा drm_vma_offset_manager vma_manager;
	u32 vmw_chipset;
	resource_माप_प्रकार io_start;
	resource_माप_प्रकार vram_start;
	resource_माप_प्रकार vram_size;
	resource_माप_प्रकार prim_bb_mem;
	u32 *fअगरo_mem;
	resource_माप_प्रकार fअगरo_mem_size;
	uपूर्णांक32_t fb_max_width;
	uपूर्णांक32_t fb_max_height;
	uपूर्णांक32_t texture_max_width;
	uपूर्णांक32_t texture_max_height;
	uपूर्णांक32_t stdu_max_width;
	uपूर्णांक32_t stdu_max_height;
	uपूर्णांक32_t initial_width;
	uपूर्णांक32_t initial_height;
	uपूर्णांक32_t capabilities;
	uपूर्णांक32_t capabilities2;
	uपूर्णांक32_t max_gmr_ids;
	uपूर्णांक32_t max_gmr_pages;
	uपूर्णांक32_t max_mob_pages;
	uपूर्णांक32_t max_mob_size;
	uपूर्णांक32_t memory_size;
	bool has_gmr;
	bool has_mob;
	spinlock_t hw_lock;
	spinlock_t cap_lock;
	bool assume_16bpp;

	क्रमागत vmw_sm_type sm_type;

	/*
	 * Framebuffer info.
	 */

	व्योम *fb_info;
	क्रमागत vmw_display_unit_type active_display_unit;
	काष्ठा vmw_legacy_display *ldu_priv;
	काष्ठा vmw_overlay *overlay_priv;
	काष्ठा drm_property *hotplug_mode_update_property;
	काष्ठा drm_property *implicit_placement_property;
	spinlock_t cursor_lock;
	काष्ठा drm_atomic_state *suspend_state;

	/*
	 * Context and surface management.
	 */

	spinlock_t resource_lock;
	काष्ठा idr res_idr[vmw_res_max];

	/*
	 * A resource manager क्रम kernel-only surfaces and
	 * contexts.
	 */

	काष्ठा tपंचांग_object_device *tdev;

	/*
	 * Fencing and IRQs.
	 */

	atomic_t marker_seq;
	रुको_queue_head_t fence_queue;
	रुको_queue_head_t fअगरo_queue;
	spinlock_t रुकोer_lock;
	पूर्णांक fence_queue_रुकोers; /* Protected by रुकोer_lock */
	पूर्णांक goal_queue_रुकोers; /* Protected by रुकोer_lock */
	पूर्णांक cmdbuf_रुकोers; /* Protected by रुकोer_lock */
	पूर्णांक error_रुकोers; /* Protected by रुकोer_lock */
	पूर्णांक fअगरo_queue_रुकोers; /* Protected by रुकोer_lock */
	uपूर्णांक32_t last_पढ़ो_seqno;
	काष्ठा vmw_fence_manager *fman;
	uपूर्णांक32_t irq_mask; /* Updates रक्षित by रुकोer_lock */

	/*
	 * Device state
	 */

	uपूर्णांक32_t traces_state;
	uपूर्णांक32_t enable_state;
	uपूर्णांक32_t config_करोne_state;

	/**
	 * Execbuf
	 */
	/**
	 * Protected by the cmdbuf mutex.
	 */

	काष्ठा vmw_sw_context ctx;
	काष्ठा mutex cmdbuf_mutex;
	काष्ठा mutex binding_mutex;

	bool enable_fb;

	/**
	 * PM management.
	 */
	काष्ठा notअगरier_block pm_nb;
	bool refuse_hibernation;
	bool suspend_locked;

	atomic_t num_fअगरo_resources;

	/*
	 * Replace this with an rwsem as soon as we have करोwn_xx_पूर्णांकerruptible()
	 */
	काष्ठा tपंचांग_lock reservation_sem;

	/*
	 * Query processing. These members
	 * are रक्षित by the cmdbuf mutex.
	 */

	काष्ठा vmw_buffer_object *dummy_query_bo;
	काष्ठा vmw_buffer_object *pinned_bo;
	uपूर्णांक32_t query_cid;
	uपूर्णांक32_t query_cid_valid;
	bool dummy_query_bo_pinned;

	/*
	 * Surface swapping. The "surface_lru" list is रक्षित by the
	 * resource lock in order to be able to destroy a surface and take
	 * it off the lru atomically. "used_memory_size" is currently
	 * रक्षित by the cmdbuf mutex क्रम simplicity.
	 */

	काष्ठा list_head res_lru[vmw_res_max];
	uपूर्णांक32_t used_memory_size;

	/*
	 * DMA mapping stuff.
	 */
	क्रमागत vmw_dma_map_mode map_mode;

	/*
	 * Guest Backed stuff
	 */
	काष्ठा vmw_otable_batch otable_batch;

	काष्ठा vmw_cmdbuf_man *cman;
	DECLARE_BITMAP(irqthपढ़ो_pending, VMW_IRQTHREAD_MAX);

	/* Validation memory reservation */
	काष्ठा vmw_validation_mem vvm;
पूर्ण;

अटल अंतरभूत काष्ठा vmw_surface *vmw_res_to_srf(काष्ठा vmw_resource *res)
अणु
	वापस container_of(res, काष्ठा vmw_surface, res);
पूर्ण

अटल अंतरभूत काष्ठा vmw_निजी *vmw_priv(काष्ठा drm_device *dev)
अणु
	वापस (काष्ठा vmw_निजी *)dev->dev_निजी;
पूर्ण

अटल अंतरभूत काष्ठा vmw_fpriv *vmw_fpriv(काष्ठा drm_file *file_priv)
अणु
	वापस (काष्ठा vmw_fpriv *)file_priv->driver_priv;
पूर्ण

/*
 * The locking here is fine-grained, so that it is perक्रमmed once
 * क्रम every पढ़ो- and ग_लिखो operation. This is of course costly, but we
 * करोn't perक्रमm much रेजिस्टर access in the timing critical paths anyway.
 * Instead we have the extra benefit of being sure that we करोn't क्रमget
 * the hw lock around रेजिस्टर accesses.
 */
अटल अंतरभूत व्योम vmw_ग_लिखो(काष्ठा vmw_निजी *dev_priv,
			     अचिन्हित पूर्णांक offset, uपूर्णांक32_t value)
अणु
	spin_lock(&dev_priv->hw_lock);
	outl(offset, dev_priv->io_start + VMWGFX_INDEX_PORT);
	outl(value, dev_priv->io_start + VMWGFX_VALUE_PORT);
	spin_unlock(&dev_priv->hw_lock);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t vmw_पढ़ो(काष्ठा vmw_निजी *dev_priv,
				अचिन्हित पूर्णांक offset)
अणु
	u32 val;

	spin_lock(&dev_priv->hw_lock);
	outl(offset, dev_priv->io_start + VMWGFX_INDEX_PORT);
	val = inl(dev_priv->io_start + VMWGFX_VALUE_PORT);
	spin_unlock(&dev_priv->hw_lock);

	वापस val;
पूर्ण

/**
 * has_sm4_context - Does the device support SM4 context.
 * @dev_priv: Device निजी.
 *
 * Return: Bool value अगर device support SM4 context or not.
 */
अटल अंतरभूत bool has_sm4_context(स्थिर काष्ठा vmw_निजी *dev_priv)
अणु
	वापस (dev_priv->sm_type >= VMW_SM_4);
पूर्ण

/**
 * has_sm4_1_context - Does the device support SM4_1 context.
 * @dev_priv: Device निजी.
 *
 * Return: Bool value अगर device support SM4_1 context or not.
 */
अटल अंतरभूत bool has_sm4_1_context(स्थिर काष्ठा vmw_निजी *dev_priv)
अणु
	वापस (dev_priv->sm_type >= VMW_SM_4_1);
पूर्ण

/**
 * has_sm5_context - Does the device support SM5 context.
 * @dev_priv: Device निजी.
 *
 * Return: Bool value अगर device support SM5 context or not.
 */
अटल अंतरभूत bool has_sm5_context(स्थिर काष्ठा vmw_निजी *dev_priv)
अणु
	वापस (dev_priv->sm_type >= VMW_SM_5);
पूर्ण

बाह्य व्योम vmw_svga_enable(काष्ठा vmw_निजी *dev_priv);
बाह्य व्योम vmw_svga_disable(काष्ठा vmw_निजी *dev_priv);


/**
 * GMR utilities - vmwgfx_gmr.c
 */

बाह्य पूर्णांक vmw_gmr_bind(काष्ठा vmw_निजी *dev_priv,
			स्थिर काष्ठा vmw_sg_table *vsgt,
			अचिन्हित दीर्घ num_pages,
			पूर्णांक gmr_id);
बाह्य व्योम vmw_gmr_unbind(काष्ठा vmw_निजी *dev_priv, पूर्णांक gmr_id);

/**
 * Resource utilities - vmwgfx_resource.c
 */
काष्ठा vmw_user_resource_conv;

बाह्य व्योम vmw_resource_unreference(काष्ठा vmw_resource **p_res);
बाह्य काष्ठा vmw_resource *vmw_resource_reference(काष्ठा vmw_resource *res);
बाह्य काष्ठा vmw_resource *
vmw_resource_reference_unless_करोomed(काष्ठा vmw_resource *res);
बाह्य पूर्णांक vmw_resource_validate(काष्ठा vmw_resource *res, bool पूर्णांकr,
				 bool dirtying);
बाह्य पूर्णांक vmw_resource_reserve(काष्ठा vmw_resource *res, bool पूर्णांकerruptible,
				bool no_backup);
बाह्य bool vmw_resource_needs_backup(स्थिर काष्ठा vmw_resource *res);
बाह्य पूर्णांक vmw_user_lookup_handle(काष्ठा vmw_निजी *dev_priv,
				  काष्ठा tपंचांग_object_file *tfile,
				  uपूर्णांक32_t handle,
				  काष्ठा vmw_surface **out_surf,
				  काष्ठा vmw_buffer_object **out_buf);
बाह्य पूर्णांक vmw_user_resource_lookup_handle(
	काष्ठा vmw_निजी *dev_priv,
	काष्ठा tपंचांग_object_file *tfile,
	uपूर्णांक32_t handle,
	स्थिर काष्ठा vmw_user_resource_conv *converter,
	काष्ठा vmw_resource **p_res);
बाह्य काष्ठा vmw_resource *
vmw_user_resource_noref_lookup_handle(काष्ठा vmw_निजी *dev_priv,
				      काष्ठा tपंचांग_object_file *tfile,
				      uपूर्णांक32_t handle,
				      स्थिर काष्ठा vmw_user_resource_conv *
				      converter);
बाह्य पूर्णांक vmw_stream_claim_ioctl(काष्ठा drm_device *dev, व्योम *data,
				  काष्ठा drm_file *file_priv);
बाह्य पूर्णांक vmw_stream_unref_ioctl(काष्ठा drm_device *dev, व्योम *data,
				  काष्ठा drm_file *file_priv);
बाह्य पूर्णांक vmw_user_stream_lookup(काष्ठा vmw_निजी *dev_priv,
				  काष्ठा tपंचांग_object_file *tfile,
				  uपूर्णांक32_t *inout_id,
				  काष्ठा vmw_resource **out);
बाह्य व्योम vmw_resource_unreserve(काष्ठा vmw_resource *res,
				   bool dirty_set,
				   bool dirty,
				   bool चयन_backup,
				   काष्ठा vmw_buffer_object *new_backup,
				   अचिन्हित दीर्घ new_backup_offset);
बाह्य व्योम vmw_query_move_notअगरy(काष्ठा tपंचांग_buffer_object *bo,
				  काष्ठा tपंचांग_resource *old_mem,
				  काष्ठा tपंचांग_resource *new_mem);
बाह्य पूर्णांक vmw_query_पढ़ोback_all(काष्ठा vmw_buffer_object *dx_query_mob);
बाह्य व्योम vmw_resource_evict_all(काष्ठा vmw_निजी *dev_priv);
बाह्य व्योम vmw_resource_unbind_list(काष्ठा vmw_buffer_object *vbo);
व्योम vmw_resource_mob_attach(काष्ठा vmw_resource *res);
व्योम vmw_resource_mob_detach(काष्ठा vmw_resource *res);
व्योम vmw_resource_dirty_update(काष्ठा vmw_resource *res, pgoff_t start,
			       pgoff_t end);
पूर्णांक vmw_resources_clean(काष्ठा vmw_buffer_object *vbo, pgoff_t start,
			pgoff_t end, pgoff_t *num_prefault);

/**
 * vmw_resource_mob_attached - Whether a resource currently has a mob attached
 * @res: The resource
 *
 * Return: true अगर the resource has a mob attached, false otherwise.
 */
अटल अंतरभूत bool vmw_resource_mob_attached(स्थिर काष्ठा vmw_resource *res)
अणु
	वापस !RB_EMPTY_NODE(&res->mob_node);
पूर्ण

/**
 * vmw_user_resource_noref_release - release a user resource poपूर्णांकer looked up
 * without reference
 */
अटल अंतरभूत व्योम vmw_user_resource_noref_release(व्योम)
अणु
	tपंचांग_base_object_noref_release();
पूर्ण

/**
 * Buffer object helper functions - vmwgfx_bo.c
 */
बाह्य पूर्णांक vmw_bo_pin_in_placement(काष्ठा vmw_निजी *vmw_priv,
				   काष्ठा vmw_buffer_object *bo,
				   काष्ठा tपंचांग_placement *placement,
				   bool पूर्णांकerruptible);
बाह्य पूर्णांक vmw_bo_pin_in_vram(काष्ठा vmw_निजी *dev_priv,
			      काष्ठा vmw_buffer_object *buf,
			      bool पूर्णांकerruptible);
बाह्य पूर्णांक vmw_bo_pin_in_vram_or_gmr(काष्ठा vmw_निजी *dev_priv,
				     काष्ठा vmw_buffer_object *buf,
				     bool पूर्णांकerruptible);
बाह्य पूर्णांक vmw_bo_pin_in_start_of_vram(काष्ठा vmw_निजी *vmw_priv,
				       काष्ठा vmw_buffer_object *bo,
				       bool पूर्णांकerruptible);
बाह्य पूर्णांक vmw_bo_unpin(काष्ठा vmw_निजी *vmw_priv,
			काष्ठा vmw_buffer_object *bo,
			bool पूर्णांकerruptible);
बाह्य व्योम vmw_bo_get_guest_ptr(स्थिर काष्ठा tपंचांग_buffer_object *buf,
				 SVGAGuestPtr *ptr);
बाह्य व्योम vmw_bo_pin_reserved(काष्ठा vmw_buffer_object *bo, bool pin);
बाह्य व्योम vmw_bo_bo_मुक्त(काष्ठा tपंचांग_buffer_object *bo);
बाह्य पूर्णांक vmw_bo_create_kernel(काष्ठा vmw_निजी *dev_priv,
				अचिन्हित दीर्घ size,
				काष्ठा tपंचांग_placement *placement,
				काष्ठा tपंचांग_buffer_object **p_bo);
बाह्य पूर्णांक vmw_bo_init(काष्ठा vmw_निजी *dev_priv,
		       काष्ठा vmw_buffer_object *vmw_bo,
		       माप_प्रकार size, काष्ठा tपंचांग_placement *placement,
		       bool पूर्णांकerruptible, bool pin,
		       व्योम (*bo_मुक्त)(काष्ठा tपंचांग_buffer_object *bo));
बाह्य पूर्णांक vmw_user_bo_verअगरy_access(काष्ठा tपंचांग_buffer_object *bo,
				     काष्ठा tपंचांग_object_file *tfile);
बाह्य पूर्णांक vmw_user_bo_alloc(काष्ठा vmw_निजी *dev_priv,
			     काष्ठा tपंचांग_object_file *tfile,
			     uपूर्णांक32_t size,
			     bool shareable,
			     uपूर्णांक32_t *handle,
			     काष्ठा vmw_buffer_object **p_dma_buf,
			     काष्ठा tपंचांग_base_object **p_base);
बाह्य पूर्णांक vmw_user_bo_reference(काष्ठा tपंचांग_object_file *tfile,
				 काष्ठा vmw_buffer_object *dma_buf,
				 uपूर्णांक32_t *handle);
बाह्य पूर्णांक vmw_bo_alloc_ioctl(काष्ठा drm_device *dev, व्योम *data,
			      काष्ठा drm_file *file_priv);
बाह्य पूर्णांक vmw_bo_unref_ioctl(काष्ठा drm_device *dev, व्योम *data,
			      काष्ठा drm_file *file_priv);
बाह्य पूर्णांक vmw_user_bo_synccpu_ioctl(काष्ठा drm_device *dev, व्योम *data,
				     काष्ठा drm_file *file_priv);
बाह्य पूर्णांक vmw_user_bo_lookup(काष्ठा tपंचांग_object_file *tfile,
			      uपूर्णांक32_t id, काष्ठा vmw_buffer_object **out,
			      काष्ठा tपंचांग_base_object **base);
बाह्य व्योम vmw_bo_fence_single(काष्ठा tपंचांग_buffer_object *bo,
				काष्ठा vmw_fence_obj *fence);
बाह्य व्योम *vmw_bo_map_and_cache(काष्ठा vmw_buffer_object *vbo);
बाह्य व्योम vmw_bo_unmap(काष्ठा vmw_buffer_object *vbo);
बाह्य व्योम vmw_bo_move_notअगरy(काष्ठा tपंचांग_buffer_object *bo,
			       काष्ठा tपंचांग_resource *mem);
बाह्य व्योम vmw_bo_swap_notअगरy(काष्ठा tपंचांग_buffer_object *bo);
बाह्य काष्ठा vmw_buffer_object *
vmw_user_bo_noref_lookup(काष्ठा tपंचांग_object_file *tfile, u32 handle);

/**
 * vmw_user_bo_noref_release - release a buffer object poपूर्णांकer looked up
 * without reference
 */
अटल अंतरभूत व्योम vmw_user_bo_noref_release(व्योम)
अणु
	tपंचांग_base_object_noref_release();
पूर्ण

/**
 * vmw_bo_adjust_prio - Adjust the buffer object eviction priority
 * according to attached resources
 * @vbo: The काष्ठा vmw_buffer_object
 */
अटल अंतरभूत व्योम vmw_bo_prio_adjust(काष्ठा vmw_buffer_object *vbo)
अणु
	पूर्णांक i = ARRAY_SIZE(vbo->res_prios);

	जबतक (i--) अणु
		अगर (vbo->res_prios[i]) अणु
			vbo->base.priority = i;
			वापस;
		पूर्ण
	पूर्ण

	vbo->base.priority = 3;
पूर्ण

/**
 * vmw_bo_prio_add - Notअगरy a buffer object of a newly attached resource
 * eviction priority
 * @vbo: The काष्ठा vmw_buffer_object
 * @prio: The resource priority
 *
 * After being notअगरied, the code assigns the highest resource eviction priority
 * to the backing buffer object (mob).
 */
अटल अंतरभूत व्योम vmw_bo_prio_add(काष्ठा vmw_buffer_object *vbo, पूर्णांक prio)
अणु
	अगर (vbo->res_prios[prio]++ == 0)
		vmw_bo_prio_adjust(vbo);
पूर्ण

/**
 * vmw_bo_prio_del - Notअगरy a buffer object of a resource with a certain
 * priority being हटाओd
 * @vbo: The काष्ठा vmw_buffer_object
 * @prio: The resource priority
 *
 * After being notअगरied, the code assigns the highest resource eviction priority
 * to the backing buffer object (mob).
 */
अटल अंतरभूत व्योम vmw_bo_prio_del(काष्ठा vmw_buffer_object *vbo, पूर्णांक prio)
अणु
	अगर (--vbo->res_prios[prio] == 0)
		vmw_bo_prio_adjust(vbo);
पूर्ण

/**
 * Misc Ioctl functionality - vmwgfx_ioctl.c
 */

बाह्य पूर्णांक vmw_getparam_ioctl(काष्ठा drm_device *dev, व्योम *data,
			      काष्ठा drm_file *file_priv);
बाह्य पूर्णांक vmw_get_cap_3d_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *file_priv);
बाह्य पूर्णांक vmw_present_ioctl(काष्ठा drm_device *dev, व्योम *data,
			     काष्ठा drm_file *file_priv);
बाह्य पूर्णांक vmw_present_पढ़ोback_ioctl(काष्ठा drm_device *dev, व्योम *data,
				      काष्ठा drm_file *file_priv);
बाह्य __poll_t vmw_fops_poll(काष्ठा file *filp,
				  काष्ठा poll_table_काष्ठा *रुको);
बाह्य sमाप_प्रकार vmw_fops_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
			     माप_प्रकार count, loff_t *offset);

/**
 * Fअगरo utilities - vmwgfx_fअगरo.c
 */

बाह्य पूर्णांक vmw_fअगरo_init(काष्ठा vmw_निजी *dev_priv,
			 काष्ठा vmw_fअगरo_state *fअगरo);
बाह्य व्योम vmw_fअगरo_release(काष्ठा vmw_निजी *dev_priv,
			     काष्ठा vmw_fअगरo_state *fअगरo);
बाह्य व्योम *
vmw_cmd_ctx_reserve(काष्ठा vmw_निजी *dev_priv, uपूर्णांक32_t bytes, पूर्णांक ctx_id);
बाह्य व्योम vmw_cmd_commit(काष्ठा vmw_निजी *dev_priv, uपूर्णांक32_t bytes);
बाह्य व्योम vmw_cmd_commit_flush(काष्ठा vmw_निजी *dev_priv, uपूर्णांक32_t bytes);
बाह्य पूर्णांक vmw_cmd_send_fence(काष्ठा vmw_निजी *dev_priv, uपूर्णांक32_t *seqno);
बाह्य bool vmw_supports_3d(काष्ठा vmw_निजी *dev_priv);
बाह्य व्योम vmw_fअगरo_ping_host(काष्ठा vmw_निजी *dev_priv, uपूर्णांक32_t reason);
बाह्य bool vmw_fअगरo_have_pitchlock(काष्ठा vmw_निजी *dev_priv);
बाह्य पूर्णांक vmw_cmd_emit_dummy_query(काष्ठा vmw_निजी *dev_priv,
				    uपूर्णांक32_t cid);
बाह्य पूर्णांक vmw_cmd_flush(काष्ठा vmw_निजी *dev_priv,
			 bool पूर्णांकerruptible);

#घोषणा VMW_CMD_CTX_RESERVE(__priv, __bytes, __ctx_id)                        \
(अणु                                                                            \
	vmw_cmd_ctx_reserve(__priv, __bytes, __ctx_id) ? : (अणु                 \
		DRM_ERROR("FIFO reserve failed at %s for %u bytes\n",         \
			  __func__, (अचिन्हित पूर्णांक) __bytes);                  \
		शून्य;                                                         \
	पूर्ण);                                                                   \
पूर्ण)

#घोषणा VMW_CMD_RESERVE(__priv, __bytes)                                     \
	VMW_CMD_CTX_RESERVE(__priv, __bytes, SVGA3D_INVALID_ID)

/**
 * TTM glue - vmwgfx_tपंचांग_glue.c
 */

बाह्य पूर्णांक vmw_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma);

बाह्य व्योम vmw_validation_mem_init_tपंचांग(काष्ठा vmw_निजी *dev_priv,
					माप_प्रकार gran);

/**
 * TTM buffer object driver - vmwgfx_tपंचांग_buffer.c
 */

बाह्य स्थिर माप_प्रकार vmw_tt_size;
बाह्य काष्ठा tपंचांग_placement vmw_vram_placement;
बाह्य काष्ठा tपंचांग_placement vmw_vram_sys_placement;
बाह्य काष्ठा tपंचांग_placement vmw_vram_gmr_placement;
बाह्य काष्ठा tपंचांग_placement vmw_sys_placement;
बाह्य काष्ठा tपंचांग_placement vmw_evictable_placement;
बाह्य काष्ठा tपंचांग_placement vmw_srf_placement;
बाह्य काष्ठा tपंचांग_placement vmw_mob_placement;
बाह्य काष्ठा tपंचांग_placement vmw_nonfixed_placement;
बाह्य काष्ठा tपंचांग_device_funcs vmw_bo_driver;
बाह्य स्थिर काष्ठा vmw_sg_table *
vmw_bo_sg_table(काष्ठा tपंचांग_buffer_object *bo);
बाह्य पूर्णांक vmw_bo_create_and_populate(काष्ठा vmw_निजी *dev_priv,
				      अचिन्हित दीर्घ bo_size,
				      काष्ठा tपंचांग_buffer_object **bo_p);

बाह्य व्योम vmw_piter_start(काष्ठा vmw_piter *viter,
			    स्थिर काष्ठा vmw_sg_table *vsgt,
			    अचिन्हित दीर्घ p_offs);

/**
 * vmw_piter_next - Advance the iterator one page.
 *
 * @viter: Poपूर्णांकer to the iterator to advance.
 *
 * Returns false अगर past the list of pages, true otherwise.
 */
अटल अंतरभूत bool vmw_piter_next(काष्ठा vmw_piter *viter)
अणु
	वापस viter->next(viter);
पूर्ण

/**
 * vmw_piter_dma_addr - Return the DMA address of the current page.
 *
 * @viter: Poपूर्णांकer to the iterator
 *
 * Returns the DMA address of the page poपूर्णांकed to by @viter.
 */
अटल अंतरभूत dma_addr_t vmw_piter_dma_addr(काष्ठा vmw_piter *viter)
अणु
	वापस viter->dma_address(viter);
पूर्ण

/**
 * vmw_piter_page - Return a poपूर्णांकer to the current page.
 *
 * @viter: Poपूर्णांकer to the iterator
 *
 * Returns the DMA address of the page poपूर्णांकed to by @viter.
 */
अटल अंतरभूत काष्ठा page *vmw_piter_page(काष्ठा vmw_piter *viter)
अणु
	वापस viter->page(viter);
पूर्ण

/**
 * Command submission - vmwgfx_execbuf.c
 */

बाह्य पूर्णांक vmw_execbuf_ioctl(काष्ठा drm_device *dev, व्योम *data,
			     काष्ठा drm_file *file_priv);
बाह्य पूर्णांक vmw_execbuf_process(काष्ठा drm_file *file_priv,
			       काष्ठा vmw_निजी *dev_priv,
			       व्योम __user *user_commands,
			       व्योम *kernel_commands,
			       uपूर्णांक32_t command_size,
			       uपूर्णांक64_t throttle_us,
			       uपूर्णांक32_t dx_context_handle,
			       काष्ठा drm_vmw_fence_rep __user
			       *user_fence_rep,
			       काष्ठा vmw_fence_obj **out_fence,
			       uपूर्णांक32_t flags);
बाह्य व्योम __vmw_execbuf_release_pinned_bo(काष्ठा vmw_निजी *dev_priv,
					    काष्ठा vmw_fence_obj *fence);
बाह्य व्योम vmw_execbuf_release_pinned_bo(काष्ठा vmw_निजी *dev_priv);

बाह्य पूर्णांक vmw_execbuf_fence_commands(काष्ठा drm_file *file_priv,
				      काष्ठा vmw_निजी *dev_priv,
				      काष्ठा vmw_fence_obj **p_fence,
				      uपूर्णांक32_t *p_handle);
बाह्य व्योम vmw_execbuf_copy_fence_user(काष्ठा vmw_निजी *dev_priv,
					काष्ठा vmw_fpriv *vmw_fp,
					पूर्णांक ret,
					काष्ठा drm_vmw_fence_rep __user
					*user_fence_rep,
					काष्ठा vmw_fence_obj *fence,
					uपूर्णांक32_t fence_handle,
					पूर्णांक32_t out_fence_fd,
					काष्ठा sync_file *sync_file);
bool vmw_cmd_describe(स्थिर व्योम *buf, u32 *size, अक्षर स्थिर **cmd);

/**
 * IRQs and wating - vmwgfx_irq.c
 */

बाह्य पूर्णांक vmw_रुको_seqno(काष्ठा vmw_निजी *dev_priv, bool lazy,
			  uपूर्णांक32_t seqno, bool पूर्णांकerruptible,
			  अचिन्हित दीर्घ समयout);
बाह्य पूर्णांक vmw_irq_install(काष्ठा drm_device *dev, पूर्णांक irq);
बाह्य व्योम vmw_irq_uninstall(काष्ठा drm_device *dev);
बाह्य bool vmw_seqno_passed(काष्ठा vmw_निजी *dev_priv,
				uपूर्णांक32_t seqno);
बाह्य पूर्णांक vmw_fallback_रुको(काष्ठा vmw_निजी *dev_priv,
			     bool lazy,
			     bool fअगरo_idle,
			     uपूर्णांक32_t seqno,
			     bool पूर्णांकerruptible,
			     अचिन्हित दीर्घ समयout);
बाह्य व्योम vmw_update_seqno(काष्ठा vmw_निजी *dev_priv,
				काष्ठा vmw_fअगरo_state *fअगरo_state);
बाह्य व्योम vmw_seqno_रुकोer_add(काष्ठा vmw_निजी *dev_priv);
बाह्य व्योम vmw_seqno_रुकोer_हटाओ(काष्ठा vmw_निजी *dev_priv);
बाह्य व्योम vmw_goal_रुकोer_add(काष्ठा vmw_निजी *dev_priv);
बाह्य व्योम vmw_goal_रुकोer_हटाओ(काष्ठा vmw_निजी *dev_priv);
बाह्य व्योम vmw_generic_रुकोer_add(काष्ठा vmw_निजी *dev_priv, u32 flag,
				   पूर्णांक *रुकोer_count);
बाह्य व्योम vmw_generic_रुकोer_हटाओ(काष्ठा vmw_निजी *dev_priv,
				      u32 flag, पूर्णांक *रुकोer_count);


/**
 * Kernel framebuffer - vmwgfx_fb.c
 */

पूर्णांक vmw_fb_init(काष्ठा vmw_निजी *vmw_priv);
पूर्णांक vmw_fb_बंद(काष्ठा vmw_निजी *dev_priv);
पूर्णांक vmw_fb_off(काष्ठा vmw_निजी *vmw_priv);
पूर्णांक vmw_fb_on(काष्ठा vmw_निजी *vmw_priv);

/**
 * Kernel modesetting - vmwgfx_kms.c
 */

पूर्णांक vmw_kms_init(काष्ठा vmw_निजी *dev_priv);
पूर्णांक vmw_kms_बंद(काष्ठा vmw_निजी *dev_priv);
पूर्णांक vmw_kms_cursor_bypass_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *file_priv);
व्योम vmw_kms_cursor_post_execbuf(काष्ठा vmw_निजी *dev_priv);
व्योम vmw_kms_cursor_snoop(काष्ठा vmw_surface *srf,
			  काष्ठा tपंचांग_object_file *tfile,
			  काष्ठा tपंचांग_buffer_object *bo,
			  SVGA3dCmdHeader *header);
पूर्णांक vmw_kms_ग_लिखो_svga(काष्ठा vmw_निजी *vmw_priv,
		       अचिन्हित width, अचिन्हित height, अचिन्हित pitch,
		       अचिन्हित bpp, अचिन्हित depth);
bool vmw_kms_validate_mode_vram(काष्ठा vmw_निजी *dev_priv,
				uपूर्णांक32_t pitch,
				uपूर्णांक32_t height);
u32 vmw_get_vblank_counter(काष्ठा drm_crtc *crtc);
पूर्णांक vmw_enable_vblank(काष्ठा drm_crtc *crtc);
व्योम vmw_disable_vblank(काष्ठा drm_crtc *crtc);
पूर्णांक vmw_kms_present(काष्ठा vmw_निजी *dev_priv,
		    काष्ठा drm_file *file_priv,
		    काष्ठा vmw_framebuffer *vfb,
		    काष्ठा vmw_surface *surface,
		    uपूर्णांक32_t sid, पूर्णांक32_t destX, पूर्णांक32_t destY,
		    काष्ठा drm_vmw_rect *clips,
		    uपूर्णांक32_t num_clips);
पूर्णांक vmw_kms_update_layout_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *file_priv);
व्योम vmw_kms_legacy_hotspot_clear(काष्ठा vmw_निजी *dev_priv);
पूर्णांक vmw_kms_suspend(काष्ठा drm_device *dev);
पूर्णांक vmw_kms_resume(काष्ठा drm_device *dev);
व्योम vmw_kms_lost_device(काष्ठा drm_device *dev);

पूर्णांक vmw_dumb_create(काष्ठा drm_file *file_priv,
		    काष्ठा drm_device *dev,
		    काष्ठा drm_mode_create_dumb *args);

पूर्णांक vmw_dumb_map_offset(काष्ठा drm_file *file_priv,
			काष्ठा drm_device *dev, uपूर्णांक32_t handle,
			uपूर्णांक64_t *offset);
पूर्णांक vmw_dumb_destroy(काष्ठा drm_file *file_priv,
		     काष्ठा drm_device *dev,
		     uपूर्णांक32_t handle);
बाह्य पूर्णांक vmw_resource_pin(काष्ठा vmw_resource *res, bool पूर्णांकerruptible);
बाह्य व्योम vmw_resource_unpin(काष्ठा vmw_resource *res);
बाह्य क्रमागत vmw_res_type vmw_res_type(स्थिर काष्ठा vmw_resource *res);

/**
 * Overlay control - vmwgfx_overlay.c
 */

पूर्णांक vmw_overlay_init(काष्ठा vmw_निजी *dev_priv);
पूर्णांक vmw_overlay_बंद(काष्ठा vmw_निजी *dev_priv);
पूर्णांक vmw_overlay_ioctl(काष्ठा drm_device *dev, व्योम *data,
		      काष्ठा drm_file *file_priv);
पूर्णांक vmw_overlay_resume_all(काष्ठा vmw_निजी *dev_priv);
पूर्णांक vmw_overlay_छोड़ो_all(काष्ठा vmw_निजी *dev_priv);
पूर्णांक vmw_overlay_claim(काष्ठा vmw_निजी *dev_priv, uपूर्णांक32_t *out);
पूर्णांक vmw_overlay_unref(काष्ठा vmw_निजी *dev_priv, uपूर्णांक32_t stream_id);
पूर्णांक vmw_overlay_num_overlays(काष्ठा vmw_निजी *dev_priv);
पूर्णांक vmw_overlay_num_मुक्त_overlays(काष्ठा vmw_निजी *dev_priv);

/**
 * GMR Id manager
 */

पूर्णांक vmw_gmrid_man_init(काष्ठा vmw_निजी *dev_priv, पूर्णांक type);
व्योम vmw_gmrid_man_fini(काष्ठा vmw_निजी *dev_priv, पूर्णांक type);

/**
 * Prime - vmwgfx_prime.c
 */

बाह्य स्थिर काष्ठा dma_buf_ops vmw_prime_dmabuf_ops;
बाह्य पूर्णांक vmw_prime_fd_to_handle(काष्ठा drm_device *dev,
				  काष्ठा drm_file *file_priv,
				  पूर्णांक fd, u32 *handle);
बाह्य पूर्णांक vmw_prime_handle_to_fd(काष्ठा drm_device *dev,
				  काष्ठा drm_file *file_priv,
				  uपूर्णांक32_t handle, uपूर्णांक32_t flags,
				  पूर्णांक *prime_fd);

/*
 * MemoryOBject management -  vmwgfx_mob.c
 */
काष्ठा vmw_mob;
बाह्य पूर्णांक vmw_mob_bind(काष्ठा vmw_निजी *dev_priv, काष्ठा vmw_mob *mob,
			स्थिर काष्ठा vmw_sg_table *vsgt,
			अचिन्हित दीर्घ num_data_pages, पूर्णांक32_t mob_id);
बाह्य व्योम vmw_mob_unbind(काष्ठा vmw_निजी *dev_priv,
			   काष्ठा vmw_mob *mob);
बाह्य व्योम vmw_mob_destroy(काष्ठा vmw_mob *mob);
बाह्य काष्ठा vmw_mob *vmw_mob_create(अचिन्हित दीर्घ data_pages);
बाह्य पूर्णांक vmw_otables_setup(काष्ठा vmw_निजी *dev_priv);
बाह्य व्योम vmw_otables_takeकरोwn(काष्ठा vmw_निजी *dev_priv);

/*
 * Context management - vmwgfx_context.c
 */

बाह्य स्थिर काष्ठा vmw_user_resource_conv *user_context_converter;

बाह्य पूर्णांक vmw_context_define_ioctl(काष्ठा drm_device *dev, व्योम *data,
				    काष्ठा drm_file *file_priv);
बाह्य पूर्णांक vmw_extended_context_define_ioctl(काष्ठा drm_device *dev, व्योम *data,
					     काष्ठा drm_file *file_priv);
बाह्य पूर्णांक vmw_context_destroy_ioctl(काष्ठा drm_device *dev, व्योम *data,
				     काष्ठा drm_file *file_priv);
बाह्य काष्ठा list_head *vmw_context_binding_list(काष्ठा vmw_resource *ctx);
बाह्य काष्ठा vmw_cmdbuf_res_manager *
vmw_context_res_man(काष्ठा vmw_resource *ctx);
बाह्य काष्ठा vmw_resource *vmw_context_cotable(काष्ठा vmw_resource *ctx,
						SVGACOTableType cotable_type);
बाह्य काष्ठा list_head *vmw_context_binding_list(काष्ठा vmw_resource *ctx);
काष्ठा vmw_ctx_binding_state;
बाह्य काष्ठा vmw_ctx_binding_state *
vmw_context_binding_state(काष्ठा vmw_resource *ctx);
बाह्य व्योम vmw_dx_context_scrub_cotables(काष्ठा vmw_resource *ctx,
					  bool पढ़ोback);
बाह्य पूर्णांक vmw_context_bind_dx_query(काष्ठा vmw_resource *ctx_res,
				     काष्ठा vmw_buffer_object *mob);
बाह्य काष्ठा vmw_buffer_object *
vmw_context_get_dx_query_mob(काष्ठा vmw_resource *ctx_res);


/*
 * Surface management - vmwgfx_surface.c
 */

बाह्य स्थिर काष्ठा vmw_user_resource_conv *user_surface_converter;

बाह्य पूर्णांक vmw_surface_destroy_ioctl(काष्ठा drm_device *dev, व्योम *data,
				     काष्ठा drm_file *file_priv);
बाह्य पूर्णांक vmw_surface_define_ioctl(काष्ठा drm_device *dev, व्योम *data,
				    काष्ठा drm_file *file_priv);
बाह्य पूर्णांक vmw_surface_reference_ioctl(काष्ठा drm_device *dev, व्योम *data,
				       काष्ठा drm_file *file_priv);
बाह्य पूर्णांक vmw_gb_surface_define_ioctl(काष्ठा drm_device *dev, व्योम *data,
				       काष्ठा drm_file *file_priv);
बाह्य पूर्णांक vmw_gb_surface_reference_ioctl(काष्ठा drm_device *dev, व्योम *data,
					  काष्ठा drm_file *file_priv);
पूर्णांक vmw_surface_gb_priv_define(काष्ठा drm_device *dev,
			       uपूर्णांक32_t user_accounting_size,
			       SVGA3dSurfaceAllFlags svga3d_flags,
			       SVGA3dSurfaceFormat क्रमmat,
			       bool क्रम_scanout,
			       uपूर्णांक32_t num_mip_levels,
			       uपूर्णांक32_t multisample_count,
			       uपूर्णांक32_t array_size,
			       काष्ठा drm_vmw_size size,
			       SVGA3dMSPattern multisample_pattern,
			       SVGA3dMSQualityLevel quality_level,
			       काष्ठा vmw_surface **srf_out);
बाह्य पूर्णांक vmw_gb_surface_define_ext_ioctl(काष्ठा drm_device *dev,
					   व्योम *data,
					   काष्ठा drm_file *file_priv);
बाह्य पूर्णांक vmw_gb_surface_reference_ext_ioctl(काष्ठा drm_device *dev,
					      व्योम *data,
					      काष्ठा drm_file *file_priv);

पूर्णांक vmw_gb_surface_define(काष्ठा vmw_निजी *dev_priv,
			  uपूर्णांक32_t user_accounting_size,
			  स्थिर काष्ठा vmw_surface_metadata *req,
			  काष्ठा vmw_surface **srf_out);

/*
 * Shader management - vmwgfx_shader.c
 */

बाह्य स्थिर काष्ठा vmw_user_resource_conv *user_shader_converter;

बाह्य पूर्णांक vmw_shader_define_ioctl(काष्ठा drm_device *dev, व्योम *data,
				   काष्ठा drm_file *file_priv);
बाह्य पूर्णांक vmw_shader_destroy_ioctl(काष्ठा drm_device *dev, व्योम *data,
				    काष्ठा drm_file *file_priv);
बाह्य पूर्णांक vmw_compat_shader_add(काष्ठा vmw_निजी *dev_priv,
				 काष्ठा vmw_cmdbuf_res_manager *man,
				 u32 user_key, स्थिर व्योम *bytecode,
				 SVGA3dShaderType shader_type,
				 माप_प्रकार size,
				 काष्ठा list_head *list);
बाह्य पूर्णांक vmw_shader_हटाओ(काष्ठा vmw_cmdbuf_res_manager *man,
			     u32 user_key, SVGA3dShaderType shader_type,
			     काष्ठा list_head *list);
बाह्य पूर्णांक vmw_dx_shader_add(काष्ठा vmw_cmdbuf_res_manager *man,
			     काष्ठा vmw_resource *ctx,
			     u32 user_key,
			     SVGA3dShaderType shader_type,
			     काष्ठा list_head *list);
बाह्य व्योम vmw_dx_shader_cotable_list_scrub(काष्ठा vmw_निजी *dev_priv,
					     काष्ठा list_head *list,
					     bool पढ़ोback);

बाह्य काष्ठा vmw_resource *
vmw_shader_lookup(काष्ठा vmw_cmdbuf_res_manager *man,
		  u32 user_key, SVGA3dShaderType shader_type);

/*
 * Streamoutput management
 */
काष्ठा vmw_resource *
vmw_dx_streamoutput_lookup(काष्ठा vmw_cmdbuf_res_manager *man,
			   u32 user_key);
पूर्णांक vmw_dx_streamoutput_add(काष्ठा vmw_cmdbuf_res_manager *man,
			    काष्ठा vmw_resource *ctx,
			    SVGA3dStreamOutputId user_key,
			    काष्ठा list_head *list);
व्योम vmw_dx_streamoutput_set_size(काष्ठा vmw_resource *res, u32 size);
पूर्णांक vmw_dx_streamoutput_हटाओ(काष्ठा vmw_cmdbuf_res_manager *man,
			       SVGA3dStreamOutputId user_key,
			       काष्ठा list_head *list);
व्योम vmw_dx_streamoutput_cotable_list_scrub(काष्ठा vmw_निजी *dev_priv,
					    काष्ठा list_head *list,
					    bool पढ़ोback);

/*
 * Command buffer managed resources - vmwgfx_cmdbuf_res.c
 */

बाह्य काष्ठा vmw_cmdbuf_res_manager *
vmw_cmdbuf_res_man_create(काष्ठा vmw_निजी *dev_priv);
बाह्य व्योम vmw_cmdbuf_res_man_destroy(काष्ठा vmw_cmdbuf_res_manager *man);
बाह्य माप_प्रकार vmw_cmdbuf_res_man_size(व्योम);
बाह्य काष्ठा vmw_resource *
vmw_cmdbuf_res_lookup(काष्ठा vmw_cmdbuf_res_manager *man,
		      क्रमागत vmw_cmdbuf_res_type res_type,
		      u32 user_key);
बाह्य व्योम vmw_cmdbuf_res_revert(काष्ठा list_head *list);
बाह्य व्योम vmw_cmdbuf_res_commit(काष्ठा list_head *list);
बाह्य पूर्णांक vmw_cmdbuf_res_add(काष्ठा vmw_cmdbuf_res_manager *man,
			      क्रमागत vmw_cmdbuf_res_type res_type,
			      u32 user_key,
			      काष्ठा vmw_resource *res,
			      काष्ठा list_head *list);
बाह्य पूर्णांक vmw_cmdbuf_res_हटाओ(काष्ठा vmw_cmdbuf_res_manager *man,
				 क्रमागत vmw_cmdbuf_res_type res_type,
				 u32 user_key,
				 काष्ठा list_head *list,
				 काष्ठा vmw_resource **res);

/*
 * COTable management - vmwgfx_cotable.c
 */
बाह्य स्थिर SVGACOTableType vmw_cotable_scrub_order[];
बाह्य काष्ठा vmw_resource *vmw_cotable_alloc(काष्ठा vmw_निजी *dev_priv,
					      काष्ठा vmw_resource *ctx,
					      u32 type);
बाह्य पूर्णांक vmw_cotable_notअगरy(काष्ठा vmw_resource *res, पूर्णांक id);
बाह्य पूर्णांक vmw_cotable_scrub(काष्ठा vmw_resource *res, bool पढ़ोback);
बाह्य व्योम vmw_cotable_add_resource(काष्ठा vmw_resource *ctx,
				     काष्ठा list_head *head);

/*
 * Command buffer managerment vmwgfx_cmdbuf.c
 */
काष्ठा vmw_cmdbuf_man;
काष्ठा vmw_cmdbuf_header;

बाह्य काष्ठा vmw_cmdbuf_man *
vmw_cmdbuf_man_create(काष्ठा vmw_निजी *dev_priv);
बाह्य पूर्णांक vmw_cmdbuf_set_pool_size(काष्ठा vmw_cmdbuf_man *man, माप_प्रकार size);
बाह्य व्योम vmw_cmdbuf_हटाओ_pool(काष्ठा vmw_cmdbuf_man *man);
बाह्य व्योम vmw_cmdbuf_man_destroy(काष्ठा vmw_cmdbuf_man *man);
बाह्य पूर्णांक vmw_cmdbuf_idle(काष्ठा vmw_cmdbuf_man *man, bool पूर्णांकerruptible,
			   अचिन्हित दीर्घ समयout);
बाह्य व्योम *vmw_cmdbuf_reserve(काष्ठा vmw_cmdbuf_man *man, माप_प्रकार size,
				पूर्णांक ctx_id, bool पूर्णांकerruptible,
				काष्ठा vmw_cmdbuf_header *header);
बाह्य व्योम vmw_cmdbuf_commit(काष्ठा vmw_cmdbuf_man *man, माप_प्रकार size,
			      काष्ठा vmw_cmdbuf_header *header,
			      bool flush);
बाह्य व्योम *vmw_cmdbuf_alloc(काष्ठा vmw_cmdbuf_man *man,
			      माप_प्रकार size, bool पूर्णांकerruptible,
			      काष्ठा vmw_cmdbuf_header **p_header);
बाह्य व्योम vmw_cmdbuf_header_मुक्त(काष्ठा vmw_cmdbuf_header *header);
बाह्य पूर्णांक vmw_cmdbuf_cur_flush(काष्ठा vmw_cmdbuf_man *man,
				bool पूर्णांकerruptible);
बाह्य व्योम vmw_cmdbuf_irqthपढ़ो(काष्ठा vmw_cmdbuf_man *man);

/* CPU blit utilities - vmwgfx_blit.c */

/**
 * काष्ठा vmw_dअगरf_cpy - CPU blit inक्रमmation काष्ठाure
 *
 * @rect: The output bounding box rectangle.
 * @line: The current line of the blit.
 * @line_offset: Offset of the current line segment.
 * @cpp: Bytes per pixel (granularity inक्रमmation).
 * @स_नकल: Which स_नकल function to use.
 */
काष्ठा vmw_dअगरf_cpy अणु
	काष्ठा drm_rect rect;
	माप_प्रकार line;
	माप_प्रकार line_offset;
	पूर्णांक cpp;
	व्योम (*करो_cpy)(काष्ठा vmw_dअगरf_cpy *dअगरf, u8 *dest, स्थिर u8 *src,
		       माप_प्रकार n);
पूर्ण;

#घोषणा VMW_CPU_BLIT_INITIALIZER अणु	\
	.करो_cpy = vmw_स_नकल,		\
पूर्ण

#घोषणा VMW_CPU_BLIT_DIFF_INITIALIZER(_cpp) अणु	  \
	.line = 0,				  \
	.line_offset = 0,			  \
	.rect = अणु .x1 = पूर्णांक_उच्च/2,		  \
		  .y1 = पूर्णांक_उच्च/2,		  \
		  .x2 = पूर्णांक_न्यून/2,		  \
		  .y2 = पूर्णांक_न्यून/2		  \
	पूर्ण,					  \
	.cpp = _cpp,				  \
	.करो_cpy = vmw_dअगरf_स_नकल,		  \
पूर्ण

व्योम vmw_dअगरf_स_नकल(काष्ठा vmw_dअगरf_cpy *dअगरf, u8 *dest, स्थिर u8 *src,
		     माप_प्रकार n);

व्योम vmw_स_नकल(काष्ठा vmw_dअगरf_cpy *dअगरf, u8 *dest, स्थिर u8 *src, माप_प्रकार n);

पूर्णांक vmw_bo_cpu_blit(काष्ठा tपंचांग_buffer_object *dst,
		    u32 dst_offset, u32 dst_stride,
		    काष्ठा tपंचांग_buffer_object *src,
		    u32 src_offset, u32 src_stride,
		    u32 w, u32 h,
		    काष्ठा vmw_dअगरf_cpy *dअगरf);

/* Host messaging -vmwgfx_msg.c: */
पूर्णांक vmw_host_get_guestinfo(स्थिर अक्षर *guest_info_param,
			   अक्षर *buffer, माप_प्रकार *length);
पूर्णांक vmw_host_log(स्थिर अक्षर *log);
पूर्णांक vmw_msg_ioctl(काष्ठा drm_device *dev, व्योम *data,
		  काष्ठा drm_file *file_priv);

/* VMW logging */

/**
 * VMW_DEBUG_USER - Debug output क्रम user-space debugging.
 *
 * @fmt: म_लिखो() like क्रमmat string.
 *
 * This macro is क्रम logging user-space error and debugging messages क्रम e.g.
 * command buffer execution errors due to malक्रमmed commands, invalid context,
 * etc.
 */
#घोषणा VMW_DEBUG_USER(fmt, ...)                                              \
	DRM_DEBUG_DRIVER(fmt, ##__VA_ARGS__)

/* Resource dirtying - vmwgfx_page_dirty.c */
व्योम vmw_bo_dirty_scan(काष्ठा vmw_buffer_object *vbo);
पूर्णांक vmw_bo_dirty_add(काष्ठा vmw_buffer_object *vbo);
व्योम vmw_bo_dirty_transfer_to_res(काष्ठा vmw_resource *res);
व्योम vmw_bo_dirty_clear_res(काष्ठा vmw_resource *res);
व्योम vmw_bo_dirty_release(काष्ठा vmw_buffer_object *vbo);
व्योम vmw_bo_dirty_unmap(काष्ठा vmw_buffer_object *vbo,
			pgoff_t start, pgoff_t end);
vm_fault_t vmw_bo_vm_fault(काष्ठा vm_fault *vmf);
vm_fault_t vmw_bo_vm_mkग_लिखो(काष्ठा vm_fault *vmf);
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
vm_fault_t vmw_bo_vm_huge_fault(काष्ठा vm_fault *vmf,
				क्रमागत page_entry_size pe_size);
#पूर्ण_अगर

/* Transparent hugepage support - vmwgfx_thp.c */
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
बाह्य पूर्णांक vmw_thp_init(काष्ठा vmw_निजी *dev_priv);
व्योम vmw_thp_fini(काष्ठा vmw_निजी *dev_priv);
#पूर्ण_अगर

/**
 * VMW_DEBUG_KMS - Debug output क्रम kernel mode-setting
 *
 * This macro is क्रम debugging vmwgfx mode-setting code.
 */
#घोषणा VMW_DEBUG_KMS(fmt, ...)                                               \
	DRM_DEBUG_DRIVER(fmt, ##__VA_ARGS__)

/**
 * Inline helper functions
 */

अटल अंतरभूत व्योम vmw_surface_unreference(काष्ठा vmw_surface **srf)
अणु
	काष्ठा vmw_surface *पंचांगp_srf = *srf;
	काष्ठा vmw_resource *res = &पंचांगp_srf->res;
	*srf = शून्य;

	vmw_resource_unreference(&res);
पूर्ण

अटल अंतरभूत काष्ठा vmw_surface *vmw_surface_reference(काष्ठा vmw_surface *srf)
अणु
	(व्योम) vmw_resource_reference(&srf->res);
	वापस srf;
पूर्ण

अटल अंतरभूत व्योम vmw_bo_unreference(काष्ठा vmw_buffer_object **buf)
अणु
	काष्ठा vmw_buffer_object *पंचांगp_buf = *buf;

	*buf = शून्य;
	अगर (पंचांगp_buf != शून्य)
		tपंचांग_bo_put(&पंचांगp_buf->base);
पूर्ण

अटल अंतरभूत काष्ठा vmw_buffer_object *
vmw_bo_reference(काष्ठा vmw_buffer_object *buf)
अणु
	tपंचांग_bo_get(&buf->base);
	वापस buf;
पूर्ण

अटल अंतरभूत काष्ठा tपंचांग_mem_global *vmw_mem_glob(काष्ठा vmw_निजी *dev_priv)
अणु
	वापस &tपंचांग_mem_glob;
पूर्ण

अटल अंतरभूत व्योम vmw_fअगरo_resource_inc(काष्ठा vmw_निजी *dev_priv)
अणु
	atomic_inc(&dev_priv->num_fअगरo_resources);
पूर्ण

अटल अंतरभूत व्योम vmw_fअगरo_resource_dec(काष्ठा vmw_निजी *dev_priv)
अणु
	atomic_dec(&dev_priv->num_fअगरo_resources);
पूर्ण

/**
 * vmw_fअगरo_mem_पढ़ो - Perक्रमm a MMIO पढ़ो from the fअगरo memory
 *
 * @fअगरo_reg: The fअगरo रेजिस्टर to पढ़ो from
 *
 * This function is पूर्णांकended to be equivalent to ioपढ़ो32() on
 * memremap'd memory, but without byteswapping.
 */
अटल अंतरभूत u32 vmw_fअगरo_mem_पढ़ो(काष्ठा vmw_निजी *vmw, uपूर्णांक32 fअगरo_reg)
अणु
	वापस READ_ONCE(*(vmw->fअगरo_mem + fअगरo_reg));
पूर्ण

/**
 * vmw_fअगरo_mem_ग_लिखो - Perक्रमm a MMIO ग_लिखो to अस्थिर memory
 *
 * @addr: The fअगरo रेजिस्टर to ग_लिखो to
 *
 * This function is पूर्णांकended to be equivalent to ioग_लिखो32 on
 * memremap'd memory, but without byteswapping.
 */
अटल अंतरभूत व्योम vmw_fअगरo_mem_ग_लिखो(काष्ठा vmw_निजी *vmw, u32 fअगरo_reg,
				      u32 value)
अणु
	WRITE_ONCE(*(vmw->fअगरo_mem + fअगरo_reg), value);
पूर्ण
#पूर्ण_अगर
