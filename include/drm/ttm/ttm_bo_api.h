<शैली गुरु>
/**************************************************************************
 *
 * Copyright (c) 2006-2009 VMware, Inc., Palo Alto, CA., USA
 * All Rights Reserved.
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
/*
 * Authors: Thomas Hellstrom <thellstrom-at-vmware-करोt-com>
 */

#अगर_अघोषित _TTM_BO_API_H_
#घोषणा _TTM_BO_API_H_

#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_hashtab.h>
#समावेश <drm/drm_vma_manager.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mm.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/dma-resv.h>

#समावेश "ttm_resource.h"

काष्ठा tपंचांग_global;

काष्ठा tपंचांग_device;

काष्ठा dma_buf_map;

काष्ठा drm_mm_node;

काष्ठा tपंचांग_placement;

काष्ठा tपंचांग_place;

काष्ठा tपंचांग_lru_bulk_move;

/**
 * क्रमागत tपंचांग_bo_type
 *
 * @tपंचांग_bo_type_device:	These are 'normal' buffers that can
 * be mmapped by user space. Each of these bos occupy a slot in the
 * device address space, that can be used क्रम normal vm operations.
 *
 * @tपंचांग_bo_type_kernel: These buffers are like tपंचांग_bo_type_device buffers,
 * but they cannot be accessed from user-space. For kernel-only use.
 *
 * @tपंचांग_bo_type_sg: Buffer made from dmabuf sg table shared with another
 * driver.
 */

क्रमागत tपंचांग_bo_type अणु
	tपंचांग_bo_type_device,
	tपंचांग_bo_type_kernel,
	tपंचांग_bo_type_sg
पूर्ण;

काष्ठा tपंचांग_tt;

/**
 * काष्ठा tपंचांग_buffer_object
 *
 * @base: drm_gem_object superclass data.
 * @bdev: Poपूर्णांकer to the buffer object device काष्ठाure.
 * @type: The bo type.
 * @destroy: Deकाष्ठाion function. If शून्य, kमुक्त is used.
 * @num_pages: Actual number of pages.
 * @kref: Reference count of this buffer object. When this refcount reaches
 * zero, the object is destroyed or put on the delayed delete list.
 * @mem: काष्ठाure describing current placement.
 * @tपंचांग: TTM काष्ठाure holding प्रणाली pages.
 * @evicted: Whether the object was evicted without user-space knowing.
 * @deleted: True अगर the object is only a zombie and alपढ़ोy deleted.
 * @lru: List head क्रम the lru list.
 * @ddestroy: List head क्रम the delayed destroy list.
 * @swap: List head क्रम swap LRU list.
 * @moving: Fence set when BO is moving
 * @offset: The current GPU offset, which can have dअगरferent meanings
 * depending on the memory type. For SYSTEM type memory, it should be 0.
 * @cur_placement: Hपूर्णांक of current placement.
 *
 * Base class क्रम TTM buffer object, that deals with data placement and CPU
 * mappings. GPU mappings are really up to the driver, but क्रम simpler GPUs
 * the driver can usually use the placement offset @offset directly as the
 * GPU भव address. For drivers implementing multiple
 * GPU memory manager contexts, the driver should manage the address space
 * in these contexts separately and use these objects to get the correct
 * placement and caching क्रम these GPU maps. This makes it possible to use
 * these objects क्रम even quite elaborate memory management schemes.
 * The destroy member, the API visibility of this object makes it possible
 * to derive driver specअगरic types.
 */

काष्ठा tपंचांग_buffer_object अणु
	काष्ठा drm_gem_object base;

	/**
	 * Members स्थिरant at init.
	 */

	काष्ठा tपंचांग_device *bdev;
	क्रमागत tपंचांग_bo_type type;
	व्योम (*destroy) (काष्ठा tपंचांग_buffer_object *);

	/**
	* Members not needing protection.
	*/
	काष्ठा kref kref;

	/**
	 * Members रक्षित by the bo::resv::reserved lock.
	 */

	काष्ठा tपंचांग_resource mem;
	काष्ठा tपंचांग_tt *tपंचांग;
	bool deleted;

	/**
	 * Members रक्षित by the bdev::lru_lock.
	 */

	काष्ठा list_head lru;
	काष्ठा list_head ddestroy;

	/**
	 * Members रक्षित by a bo reservation.
	 */

	काष्ठा dma_fence *moving;
	अचिन्हित priority;
	अचिन्हित pin_count;

	/**
	 * Special members that are रक्षित by the reserve lock
	 * and the bo::lock when written to. Can be पढ़ो with
	 * either of these locks held.
	 */

	काष्ठा sg_table *sg;
पूर्ण;

/**
 * काष्ठा tपंचांग_bo_kmap_obj
 *
 * @भव: The current kernel भव address.
 * @page: The page when kmap'ing a single page.
 * @bo_kmap_type: Type of bo_kmap.
 *
 * Object describing a kernel mapping. Since a TTM bo may be located
 * in various memory types with various caching policies, the
 * mapping can either be an ioremap, a vmap, a kmap or part of a
 * premapped region.
 */

#घोषणा TTM_BO_MAP_IOMEM_MASK 0x80
काष्ठा tपंचांग_bo_kmap_obj अणु
	व्योम *भव;
	काष्ठा page *page;
	क्रमागत अणु
		tपंचांग_bo_map_iomap        = 1 | TTM_BO_MAP_IOMEM_MASK,
		tपंचांग_bo_map_vmap         = 2,
		tपंचांग_bo_map_kmap         = 3,
		tपंचांग_bo_map_premapped    = 4 | TTM_BO_MAP_IOMEM_MASK,
	पूर्ण bo_kmap_type;
	काष्ठा tपंचांग_buffer_object *bo;
पूर्ण;

/**
 * काष्ठा tपंचांग_operation_ctx
 *
 * @पूर्णांकerruptible: Sleep पूर्णांकerruptible अगर sleeping.
 * @no_रुको_gpu: Return immediately अगर the GPU is busy.
 * @gfp_retry_mayfail: Set the __GFP_RETRY_MAYFAIL when allocation pages.
 * @allow_res_evict: Allow eviction of reserved BOs. Can be used when multiple
 * BOs share the same reservation object.
 * @क्रमce_alloc: Don't check the memory account during suspend or CPU page
 * faults. Should only be used by TTM पूर्णांकernally.
 * @resv: Reservation object to allow reserved evictions with.
 *
 * Context क्रम TTM operations like changing buffer placement or general memory
 * allocation.
 */
काष्ठा tपंचांग_operation_ctx अणु
	bool पूर्णांकerruptible;
	bool no_रुको_gpu;
	bool gfp_retry_mayfail;
	bool allow_res_evict;
	bool क्रमce_alloc;
	काष्ठा dma_resv *resv;
	uपूर्णांक64_t bytes_moved;
पूर्ण;

/**
 * tपंचांग_bo_get - reference a काष्ठा tपंचांग_buffer_object
 *
 * @bo: The buffer object.
 */
अटल अंतरभूत व्योम tपंचांग_bo_get(काष्ठा tपंचांग_buffer_object *bo)
अणु
	kref_get(&bo->kref);
पूर्ण

/**
 * tपंचांग_bo_get_unless_zero - reference a काष्ठा tपंचांग_buffer_object unless
 * its refcount has alपढ़ोy reached zero.
 * @bo: The buffer object.
 *
 * Used to reference a TTM buffer object in lookups where the object is हटाओd
 * from the lookup काष्ठाure during the deकाष्ठाor and क्रम RCU lookups.
 *
 * Returns: @bo अगर the referencing was successful, शून्य otherwise.
 */
अटल अंतरभूत __must_check काष्ठा tपंचांग_buffer_object *
tपंचांग_bo_get_unless_zero(काष्ठा tपंचांग_buffer_object *bo)
अणु
	अगर (!kref_get_unless_zero(&bo->kref))
		वापस शून्य;
	वापस bo;
पूर्ण

/**
 * tपंचांग_bo_रुको - रुको क्रम buffer idle.
 *
 * @bo:  The buffer object.
 * @पूर्णांकerruptible:  Use पूर्णांकerruptible रुको.
 * @no_रुको:  Return immediately अगर buffer is busy.
 *
 * This function must be called with the bo::mutex held, and makes
 * sure any previous rendering to the buffer is completed.
 * Note: It might be necessary to block validations beक्रमe the
 * रुको by reserving the buffer.
 * Returns -EBUSY अगर no_रुको is true and the buffer is busy.
 * Returns -ERESTARTSYS अगर पूर्णांकerrupted by a संकेत.
 */
पूर्णांक tपंचांग_bo_रुको(काष्ठा tपंचांग_buffer_object *bo, bool पूर्णांकerruptible, bool no_रुको);

अटल अंतरभूत पूर्णांक tपंचांग_bo_रुको_ctx(काष्ठा tपंचांग_buffer_object *bo, काष्ठा tपंचांग_operation_ctx *ctx)
अणु
	वापस tपंचांग_bo_रुको(bo, ctx->पूर्णांकerruptible, ctx->no_रुको_gpu);
पूर्ण

/**
 * tपंचांग_bo_mem_compat - Check अगर proposed placement is compatible with a bo
 *
 * @placement:  Return immediately अगर buffer is busy.
 * @mem:  The काष्ठा tपंचांग_resource indicating the region where the bo resides
 * @new_flags: Describes compatible placement found
 *
 * Returns true अगर the placement is compatible
 */
bool tपंचांग_bo_mem_compat(काष्ठा tपंचांग_placement *placement, काष्ठा tपंचांग_resource *mem,
		       uपूर्णांक32_t *new_flags);

/**
 * tपंचांग_bo_validate
 *
 * @bo: The buffer object.
 * @placement: Proposed placement क्रम the buffer object.
 * @ctx: validation parameters.
 *
 * Changes placement and caching policy of the buffer object
 * according proposed placement.
 * Returns
 * -EINVAL on invalid proposed placement.
 * -ENOMEM on out-of-memory condition.
 * -EBUSY अगर no_रुको is true and buffer busy.
 * -ERESTARTSYS अगर पूर्णांकerrupted by a संकेत.
 */
पूर्णांक tपंचांग_bo_validate(काष्ठा tपंचांग_buffer_object *bo,
		    काष्ठा tपंचांग_placement *placement,
		    काष्ठा tपंचांग_operation_ctx *ctx);

/**
 * tपंचांग_bo_put
 *
 * @bo: The buffer object.
 *
 * Unreference a buffer object.
 */
व्योम tपंचांग_bo_put(काष्ठा tपंचांग_buffer_object *bo);

/**
 * tपंचांग_bo_move_to_lru_tail
 *
 * @bo: The buffer object.
 * @mem: Resource object.
 * @bulk: optional bulk move काष्ठाure to remember BO positions
 *
 * Move this BO to the tail of all lru lists used to lookup and reserve an
 * object. This function must be called with काष्ठा tपंचांग_global::lru_lock
 * held, and is used to make a BO less likely to be considered क्रम eviction.
 */
व्योम tपंचांग_bo_move_to_lru_tail(काष्ठा tपंचांग_buffer_object *bo,
			     काष्ठा tपंचांग_resource *mem,
			     काष्ठा tपंचांग_lru_bulk_move *bulk);

/**
 * tपंचांग_bo_bulk_move_lru_tail
 *
 * @bulk: bulk move काष्ठाure
 *
 * Bulk move BOs to the LRU tail, only valid to use when driver makes sure that
 * BO order never changes. Should be called with tपंचांग_global::lru_lock held.
 */
व्योम tपंचांग_bo_bulk_move_lru_tail(काष्ठा tपंचांग_lru_bulk_move *bulk);

/**
 * tपंचांग_bo_lock_delayed_workqueue
 *
 * Prevent the delayed workqueue from running.
 * Returns
 * True अगर the workqueue was queued at the समय
 */
पूर्णांक tपंचांग_bo_lock_delayed_workqueue(काष्ठा tपंचांग_device *bdev);

/**
 * tपंचांग_bo_unlock_delayed_workqueue
 *
 * Allows the delayed workqueue to run.
 */
व्योम tपंचांग_bo_unlock_delayed_workqueue(काष्ठा tपंचांग_device *bdev, पूर्णांक resched);

/**
 * tपंचांग_bo_eviction_valuable
 *
 * @bo: The buffer object to evict
 * @place: the placement we need to make room क्रम
 *
 * Check अगर it is valuable to evict the BO to make room क्रम the given placement.
 */
bool tपंचांग_bo_eviction_valuable(काष्ठा tपंचांग_buffer_object *bo,
			      स्थिर काष्ठा tपंचांग_place *place);

/**
 * tपंचांग_bo_init_reserved
 *
 * @bdev: Poपूर्णांकer to a tपंचांग_device काष्ठा.
 * @bo: Poपूर्णांकer to a tपंचांग_buffer_object to be initialized.
 * @size: Requested size of buffer object.
 * @type: Requested type of buffer object.
 * @flags: Initial placement flags.
 * @page_alignment: Data alignment in pages.
 * @ctx: TTM operation context क्रम memory allocation.
 * @resv: Poपूर्णांकer to a dma_resv, or शून्य to let tपंचांग allocate one.
 * @destroy: Destroy function. Use शून्य क्रम kमुक्त().
 *
 * This function initializes a pre-allocated काष्ठा tपंचांग_buffer_object.
 * As this object may be part of a larger काष्ठाure, this function,
 * together with the @destroy function,
 * enables driver-specअगरic objects derived from a tपंचांग_buffer_object.
 *
 * On successful वापस, the caller owns an object kref to @bo. The kref and
 * list_kref are usually set to 1, but note that in some situations, other
 * tasks may alपढ़ोy be holding references to @bo as well.
 * Furthermore, अगर resv == शून्य, the buffer's reservation lock will be held,
 * and it is the caller's responsibility to call tपंचांग_bo_unreserve.
 *
 * If a failure occurs, the function will call the @destroy function, or
 * kमुक्त() अगर @destroy is शून्य. Thus, after a failure, dereferencing @bo is
 * illegal and will likely cause memory corruption.
 *
 * Returns
 * -ENOMEM: Out of memory.
 * -EINVAL: Invalid placement flags.
 * -ERESTARTSYS: Interrupted by संकेत जबतक sleeping रुकोing क्रम resources.
 */

पूर्णांक tपंचांग_bo_init_reserved(काष्ठा tपंचांग_device *bdev,
			 काष्ठा tपंचांग_buffer_object *bo,
			 माप_प्रकार size, क्रमागत tपंचांग_bo_type type,
			 काष्ठा tपंचांग_placement *placement,
			 uपूर्णांक32_t page_alignment,
			 काष्ठा tपंचांग_operation_ctx *ctx,
			 काष्ठा sg_table *sg, काष्ठा dma_resv *resv,
			 व्योम (*destroy) (काष्ठा tपंचांग_buffer_object *));

/**
 * tपंचांग_bo_init
 *
 * @bdev: Poपूर्णांकer to a tपंचांग_device काष्ठा.
 * @bo: Poपूर्णांकer to a tपंचांग_buffer_object to be initialized.
 * @size: Requested size of buffer object.
 * @type: Requested type of buffer object.
 * @flags: Initial placement flags.
 * @page_alignment: Data alignment in pages.
 * @पूर्णांकerruptible: If needing to sleep to रुको क्रम GPU resources,
 * sleep पूर्णांकerruptible.
 * pinned in physical memory. If this behaviour is not desired, this member
 * holds a poपूर्णांकer to a persistent shmem object. Typically, this would
 * poपूर्णांक to the shmem object backing a GEM object अगर TTM is used to back a
 * GEM user पूर्णांकerface.
 * @resv: Poपूर्णांकer to a dma_resv, or शून्य to let tपंचांग allocate one.
 * @destroy: Destroy function. Use शून्य क्रम kमुक्त().
 *
 * This function initializes a pre-allocated काष्ठा tपंचांग_buffer_object.
 * As this object may be part of a larger काष्ठाure, this function,
 * together with the @destroy function,
 * enables driver-specअगरic objects derived from a tपंचांग_buffer_object.
 *
 * On successful वापस, the caller owns an object kref to @bo. The kref and
 * list_kref are usually set to 1, but note that in some situations, other
 * tasks may alपढ़ोy be holding references to @bo as well.
 *
 * If a failure occurs, the function will call the @destroy function, or
 * kमुक्त() अगर @destroy is शून्य. Thus, after a failure, dereferencing @bo is
 * illegal and will likely cause memory corruption.
 *
 * Returns
 * -ENOMEM: Out of memory.
 * -EINVAL: Invalid placement flags.
 * -ERESTARTSYS: Interrupted by संकेत जबतक sleeping रुकोing क्रम resources.
 */
पूर्णांक tपंचांग_bo_init(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_buffer_object *bo,
		माप_प्रकार size, क्रमागत tपंचांग_bo_type type,
		काष्ठा tपंचांग_placement *placement,
		uपूर्णांक32_t page_alignment, bool पूर्णांकerrubtible,
		काष्ठा sg_table *sg, काष्ठा dma_resv *resv,
		व्योम (*destroy) (काष्ठा tपंचांग_buffer_object *));

/**
 * tपंचांग_kmap_obj_भव
 *
 * @map: A काष्ठा tपंचांग_bo_kmap_obj वापसed from tपंचांग_bo_kmap.
 * @is_iomem: Poपूर्णांकer to an पूर्णांकeger that on वापस indicates 1 अगर the
 * भव map is io memory, 0 अगर normal memory.
 *
 * Returns the भव address of a buffer object area mapped by tपंचांग_bo_kmap.
 * If *is_iomem is 1 on वापस, the भव address poपूर्णांकs to an io memory area,
 * that should strictly be accessed by the ioग_लिखोXX() and similar functions.
 */
अटल अंतरभूत व्योम *tपंचांग_kmap_obj_भव(काष्ठा tपंचांग_bo_kmap_obj *map,
					 bool *is_iomem)
अणु
	*is_iomem = !!(map->bo_kmap_type & TTM_BO_MAP_IOMEM_MASK);
	वापस map->भव;
पूर्ण

/**
 * tपंचांग_bo_kmap
 *
 * @bo: The buffer object.
 * @start_page: The first page to map.
 * @num_pages: Number of pages to map.
 * @map: poपूर्णांकer to a काष्ठा tपंचांग_bo_kmap_obj representing the map.
 *
 * Sets up a kernel भव mapping, using ioremap, vmap or kmap to the
 * data in the buffer object. The tपंचांग_kmap_obj_भव function can then be
 * used to obtain a भव address to the data.
 *
 * Returns
 * -ENOMEM: Out of memory.
 * -EINVAL: Invalid range.
 */
पूर्णांक tपंचांग_bo_kmap(काष्ठा tपंचांग_buffer_object *bo, अचिन्हित दीर्घ start_page,
		अचिन्हित दीर्घ num_pages, काष्ठा tपंचांग_bo_kmap_obj *map);

/**
 * tपंचांग_bo_kunmap
 *
 * @map: Object describing the map to unmap.
 *
 * Unmaps a kernel map set up by tपंचांग_bo_kmap.
 */
व्योम tपंचांग_bo_kunmap(काष्ठा tपंचांग_bo_kmap_obj *map);

/**
 * tपंचांग_bo_vmap
 *
 * @bo: The buffer object.
 * @map: poपूर्णांकer to a काष्ठा dma_buf_map representing the map.
 *
 * Sets up a kernel भव mapping, using ioremap or vmap to the
 * data in the buffer object. The parameter @map वापसs the भव
 * address as काष्ठा dma_buf_map. Unmap the buffer with tपंचांग_bo_vunmap().
 *
 * Returns
 * -ENOMEM: Out of memory.
 * -EINVAL: Invalid range.
 */
पूर्णांक tपंचांग_bo_vmap(काष्ठा tपंचांग_buffer_object *bo, काष्ठा dma_buf_map *map);

/**
 * tपंचांग_bo_vunmap
 *
 * @bo: The buffer object.
 * @map: Object describing the map to unmap.
 *
 * Unmaps a kernel map set up by tपंचांग_bo_vmap().
 */
व्योम tपंचांग_bo_vunmap(काष्ठा tपंचांग_buffer_object *bo, काष्ठा dma_buf_map *map);

/**
 * tपंचांग_bo_mmap_obj - mmap memory backed by a tपंचांग buffer object.
 *
 * @vma:       vma as input from the fbdev mmap method.
 * @bo:        The bo backing the address space.
 *
 * Maps a buffer object.
 */
पूर्णांक tपंचांग_bo_mmap_obj(काष्ठा vm_area_काष्ठा *vma, काष्ठा tपंचांग_buffer_object *bo);

/**
 * tपंचांग_bo_mmap - mmap out of the tपंचांग device address space.
 *
 * @filp:      filp as input from the mmap method.
 * @vma:       vma as input from the mmap method.
 * @bdev:      Poपूर्णांकer to the tपंचांग_device with the address space manager.
 *
 * This function is पूर्णांकended to be called by the device mmap method.
 * अगर the device address space is to be backed by the bo manager.
 */
पूर्णांक tपंचांग_bo_mmap(काष्ठा file *filp, काष्ठा vm_area_काष्ठा *vma,
		काष्ठा tपंचांग_device *bdev);

/**
 * tपंचांग_bo_io
 *
 * @bdev:      Poपूर्णांकer to the काष्ठा tपंचांग_device.
 * @filp:      Poपूर्णांकer to the काष्ठा file attempting to पढ़ो / ग_लिखो.
 * @wbuf:      User-space poपूर्णांकer to address of buffer to ग_लिखो. शून्य on पढ़ो.
 * @rbuf:      User-space poपूर्णांकer to address of buffer to पढ़ो पूर्णांकo.
 * Null on ग_लिखो.
 * @count:     Number of bytes to पढ़ो / ग_लिखो.
 * @f_pos:     Poपूर्णांकer to current file position.
 * @ग_लिखो:     1 क्रम पढ़ो, 0 क्रम ग_लिखो.
 *
 * This function implements पढ़ो / ग_लिखो पूर्णांकo tपंचांग buffer objects, and is
 * पूर्णांकended to
 * be called from the fops::पढ़ो and fops::ग_लिखो method.
 * Returns:
 * See man (2) ग_लिखो, man(2) पढ़ो. In particular,
 * the function may वापस -ERESTARTSYS अगर
 * पूर्णांकerrupted by a संकेत.
 */
sमाप_प्रकार tपंचांग_bo_io(काष्ठा tपंचांग_device *bdev, काष्ठा file *filp,
		  स्थिर अक्षर __user *wbuf, अक्षर __user *rbuf,
		  माप_प्रकार count, loff_t *f_pos, bool ग_लिखो);

पूर्णांक tपंचांग_bo_swapout(काष्ठा tपंचांग_buffer_object *bo, काष्ठा tपंचांग_operation_ctx *ctx,
		   gfp_t gfp_flags);

/**
 * tपंचांग_bo_uses_embedded_gem_object - check अगर the given bo uses the
 * embedded drm_gem_object.
 *
 * Most tपंचांग drivers are using gem too, so the embedded
 * tपंचांग_buffer_object.base will be initialized by the driver (beक्रमe
 * calling tपंचांग_bo_init).  It is also possible to use tपंचांग without gem
 * though (vmwgfx करोes that).
 *
 * This helper will figure whenever a given tपंचांग bo is a gem object too
 * or not.
 *
 * @bo: The bo to check.
 */
अटल अंतरभूत bool tपंचांग_bo_uses_embedded_gem_object(काष्ठा tपंचांग_buffer_object *bo)
अणु
	वापस bo->base.dev != शून्य;
पूर्ण

/**
 * tपंचांग_bo_pin - Pin the buffer object.
 * @bo: The buffer object to pin
 *
 * Make sure the buffer is not evicted any more during memory pressure.
 */
अटल अंतरभूत व्योम tपंचांग_bo_pin(काष्ठा tपंचांग_buffer_object *bo)
अणु
	dma_resv_निश्चित_held(bo->base.resv);
	WARN_ON_ONCE(!kref_पढ़ो(&bo->kref));
	++bo->pin_count;
पूर्ण

/**
 * tपंचांग_bo_unpin - Unpin the buffer object.
 * @bo: The buffer object to unpin
 *
 * Allows the buffer object to be evicted again during memory pressure.
 */
अटल अंतरभूत व्योम tपंचांग_bo_unpin(काष्ठा tपंचांग_buffer_object *bo)
अणु
	dma_resv_निश्चित_held(bo->base.resv);
	WARN_ON_ONCE(!kref_पढ़ो(&bo->kref));
	अगर (bo->pin_count)
		--bo->pin_count;
	अन्यथा
		WARN_ON_ONCE(true);
पूर्ण

पूर्णांक tपंचांग_mem_evict_first(काष्ठा tपंचांग_device *bdev,
			काष्ठा tपंचांग_resource_manager *man,
			स्थिर काष्ठा tपंचांग_place *place,
			काष्ठा tपंचांग_operation_ctx *ctx,
			काष्ठा ww_acquire_ctx *ticket);

/* Default number of pre-faulted pages in the TTM fault handler */
#घोषणा TTM_BO_VM_NUM_PREFAULT 16

vm_fault_t tपंचांग_bo_vm_reserve(काष्ठा tपंचांग_buffer_object *bo,
			     काष्ठा vm_fault *vmf);

vm_fault_t tपंचांग_bo_vm_fault_reserved(काष्ठा vm_fault *vmf,
				    pgprot_t prot,
				    pgoff_t num_prefault,
				    pgoff_t fault_page_size);

vm_fault_t tपंचांग_bo_vm_fault(काष्ठा vm_fault *vmf);

व्योम tपंचांग_bo_vm_खोलो(काष्ठा vm_area_काष्ठा *vma);

व्योम tपंचांग_bo_vm_बंद(काष्ठा vm_area_काष्ठा *vma);

पूर्णांक tपंचांग_bo_vm_access(काष्ठा vm_area_काष्ठा *vma, अचिन्हित दीर्घ addr,
		     व्योम *buf, पूर्णांक len, पूर्णांक ग_लिखो);
bool tपंचांग_bo_delayed_delete(काष्ठा tपंचांग_device *bdev, bool हटाओ_all);

#पूर्ण_अगर
