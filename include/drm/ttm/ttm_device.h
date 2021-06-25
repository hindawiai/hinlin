<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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
 * Authors: Christian Kथघnig
 */

#अगर_अघोषित _TTM_DEVICE_H_
#घोषणा _TTM_DEVICE_H_

#समावेश <linux/types.h>
#समावेश <linux/workqueue.h>
#समावेश <drm/tपंचांग/tपंचांग_resource.h>
#समावेश <drm/tपंचांग/tपंचांग_pool.h>

#घोषणा TTM_NUM_MEM_TYPES 8

काष्ठा tपंचांग_device;
काष्ठा tपंचांग_placement;
काष्ठा tपंचांग_buffer_object;
काष्ठा tपंचांग_operation_ctx;

/**
 * काष्ठा tपंचांग_global - Buffer object driver global data.
 *
 * @dummy_पढ़ो_page: Poपूर्णांकer to a dummy page used क्रम mapping requests
 * of unpopulated pages.
 * @shrink: A shrink callback object used क्रम buffer object swap.
 * @device_list_mutex: Mutex protecting the device list.
 * This mutex is held जबतक traversing the device list क्रम pm options.
 * @lru_lock: Spinlock protecting the bo subप्रणाली lru lists.
 * @device_list: List of buffer object devices.
 * @swap_lru: Lru list of buffer objects used क्रम swapping.
 */
बाह्य काष्ठा tपंचांग_global अणु

	/**
	 * Constant after init.
	 */

	काष्ठा page *dummy_पढ़ो_page;

	/**
	 * Protected by tपंचांग_global_mutex.
	 */
	काष्ठा list_head device_list;

	/**
	 * Internal protection.
	 */
	atomic_t bo_count;
पूर्ण tपंचांग_glob;

काष्ठा tपंचांग_device_funcs अणु
	/**
	 * tपंचांग_tt_create
	 *
	 * @bo: The buffer object to create the tपंचांग क्रम.
	 * @page_flags: Page flags as identअगरied by TTM_PAGE_FLAG_XX flags.
	 *
	 * Create a काष्ठा tपंचांग_tt to back data with प्रणाली memory pages.
	 * No pages are actually allocated.
	 * Returns:
	 * शून्य: Out of memory.
	 */
	काष्ठा tपंचांग_tt *(*tपंचांग_tt_create)(काष्ठा tपंचांग_buffer_object *bo,
					uपूर्णांक32_t page_flags);

	/**
	 * tपंचांग_tt_populate
	 *
	 * @tपंचांग: The काष्ठा tपंचांग_tt to contain the backing pages.
	 *
	 * Allocate all backing pages
	 * Returns:
	 * -ENOMEM: Out of memory.
	 */
	पूर्णांक (*tपंचांग_tt_populate)(काष्ठा tपंचांग_device *bdev,
			       काष्ठा tपंचांग_tt *tपंचांग,
			       काष्ठा tपंचांग_operation_ctx *ctx);

	/**
	 * tपंचांग_tt_unpopulate
	 *
	 * @tपंचांग: The काष्ठा tपंचांग_tt to contain the backing pages.
	 *
	 * Free all backing page
	 */
	व्योम (*tपंचांग_tt_unpopulate)(काष्ठा tपंचांग_device *bdev,
				  काष्ठा tपंचांग_tt *tपंचांग);

	/**
	 * tपंचांग_tt_destroy
	 *
	 * @bdev: Poपूर्णांकer to a tपंचांग device
	 * @tपंचांग: Poपूर्णांकer to a काष्ठा tपंचांग_tt.
	 *
	 * Destroy the backend. This will be call back from tपंचांग_tt_destroy so
	 * करोn't call tपंचांग_tt_destroy from the callback or infinite loop.
	 */
	व्योम (*tपंचांग_tt_destroy)(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_tt *tपंचांग);

	/**
	 * काष्ठा tपंचांग_bo_driver member eviction_valuable
	 *
	 * @bo: the buffer object to be evicted
	 * @place: placement we need room क्रम
	 *
	 * Check with the driver अगर it is valuable to evict a BO to make room
	 * क्रम a certain placement.
	 */
	bool (*eviction_valuable)(काष्ठा tपंचांग_buffer_object *bo,
				  स्थिर काष्ठा tपंचांग_place *place);
	/**
	 * काष्ठा tपंचांग_bo_driver member evict_flags:
	 *
	 * @bo: the buffer object to be evicted
	 *
	 * Return the bo flags क्रम a buffer which is not mapped to the hardware.
	 * These will be placed in proposed_flags so that when the move is
	 * finished, they'll end up in bo->mem.flags
	 * This should not cause multihop evictions, and the core will warn
	 * अगर one is proposed.
	 */

	व्योम (*evict_flags)(काष्ठा tपंचांग_buffer_object *bo,
			    काष्ठा tपंचांग_placement *placement);

	/**
	 * काष्ठा tपंचांग_bo_driver member move:
	 *
	 * @bo: the buffer to move
	 * @evict: whether this motion is evicting the buffer from
	 * the graphics address space
	 * @ctx: context क्रम this move with parameters
	 * @new_mem: the new memory region receiving the buffer
	 @ @hop: placement क्रम driver directed पूर्णांकermediate hop
	 *
	 * Move a buffer between two memory regions.
	 * Returns त्रुटि_सं -EMULTIHOP अगर driver requests a hop
	 */
	पूर्णांक (*move)(काष्ठा tपंचांग_buffer_object *bo, bool evict,
		    काष्ठा tपंचांग_operation_ctx *ctx,
		    काष्ठा tपंचांग_resource *new_mem,
		    काष्ठा tपंचांग_place *hop);

	/**
	 * काष्ठा tपंचांग_bo_driver_member verअगरy_access
	 *
	 * @bo: Poपूर्णांकer to a buffer object.
	 * @filp: Poपूर्णांकer to a काष्ठा file trying to access the object.
	 *
	 * Called from the map / ग_लिखो / पढ़ो methods to verअगरy that the
	 * caller is permitted to access the buffer object.
	 * This member may be set to शून्य, which will refuse this kind of
	 * access क्रम all buffer objects.
	 * This function should वापस 0 अगर access is granted, -EPERM otherwise.
	 */
	पूर्णांक (*verअगरy_access)(काष्ठा tपंचांग_buffer_object *bo,
			     काष्ठा file *filp);

	/**
	 * Hook to notअगरy driver about a resource delete.
	 */
	व्योम (*delete_mem_notअगरy)(काष्ठा tपंचांग_buffer_object *bo);

	/**
	 * notअगरy the driver that we're about to swap out this bo
	 */
	व्योम (*swap_notअगरy)(काष्ठा tपंचांग_buffer_object *bo);

	/**
	 * Driver callback on when mapping io memory (क्रम bo_move_स_नकल
	 * क्रम instance). TTM will take care to call io_mem_मुक्त whenever
	 * the mapping is not use anymore. io_mem_reserve & io_mem_मुक्त
	 * are balanced.
	 */
	पूर्णांक (*io_mem_reserve)(काष्ठा tपंचांग_device *bdev,
			      काष्ठा tपंचांग_resource *mem);
	व्योम (*io_mem_मुक्त)(काष्ठा tपंचांग_device *bdev,
			    काष्ठा tपंचांग_resource *mem);

	/**
	 * Return the pfn क्रम a given page_offset inside the BO.
	 *
	 * @bo: the BO to look up the pfn क्रम
	 * @page_offset: the offset to look up
	 */
	अचिन्हित दीर्घ (*io_mem_pfn)(काष्ठा tपंचांग_buffer_object *bo,
				    अचिन्हित दीर्घ page_offset);

	/**
	 * Read/ग_लिखो memory buffers क्रम ptrace access
	 *
	 * @bo: the BO to access
	 * @offset: the offset from the start of the BO
	 * @buf: poपूर्णांकer to source/destination buffer
	 * @len: number of bytes to copy
	 * @ग_लिखो: whether to पढ़ो (0) from or ग_लिखो (non-0) to BO
	 *
	 * If successful, this function should वापस the number of
	 * bytes copied, -EIO otherwise. If the number of bytes
	 * वापसed is < len, the function may be called again with
	 * the reमुख्यder of the buffer to copy.
	 */
	पूर्णांक (*access_memory)(काष्ठा tपंचांग_buffer_object *bo, अचिन्हित दीर्घ offset,
			     व्योम *buf, पूर्णांक len, पूर्णांक ग_लिखो);

	/**
	 * काष्ठा tपंचांग_bo_driver member del_from_lru_notअगरy
	 *
	 * @bo: the buffer object deleted from lru
	 *
	 * notअगरy driver that a BO was deleted from LRU.
	 */
	व्योम (*del_from_lru_notअगरy)(काष्ठा tपंचांग_buffer_object *bo);

	/**
	 * Notअगरy the driver that we're about to release a BO
	 *
	 * @bo: BO that is about to be released
	 *
	 * Gives the driver a chance to करो any cleanup, including
	 * adding fences that may क्रमce a delayed delete
	 */
	व्योम (*release_notअगरy)(काष्ठा tपंचांग_buffer_object *bo);
पूर्ण;

/**
 * काष्ठा tपंचांग_device - Buffer object driver device-specअगरic data.
 *
 * @device_list: Our entry in the global device list.
 * @funcs: Function table क्रम the device.
 * @sysman: Resource manager क्रम the प्रणाली करोमुख्य.
 * @man_drv: An array of resource_managers.
 * @vma_manager: Address space manager.
 * @pool: page pool क्रम the device.
 * @dev_mapping: A poपूर्णांकer to the काष्ठा address_space representing the
 * device address space.
 * @wq: Work queue काष्ठाure क्रम the delayed delete workqueue.
 */
काष्ठा tपंचांग_device अणु
	/*
	 * Constant after bo device init
	 */
	काष्ठा list_head device_list;
	काष्ठा tपंचांग_device_funcs *funcs;

	/*
	 * Access via tपंचांग_manager_type.
	 */
	काष्ठा tपंचांग_resource_manager sysman;
	काष्ठा tपंचांग_resource_manager *man_drv[TTM_NUM_MEM_TYPES];

	/*
	 * Protected by पूर्णांकernal locks.
	 */
	काष्ठा drm_vma_offset_manager *vma_manager;
	काष्ठा tपंचांग_pool pool;

	/*
	 * Protection क्रम the per manager LRU and ddestroy lists.
	 */
	spinlock_t lru_lock;
	काष्ठा list_head ddestroy;

	/*
	 * Protected by load / firstखोलो / lastबंद /unload sync.
	 */
	काष्ठा address_space *dev_mapping;

	/*
	 * Internal protection.
	 */
	काष्ठा delayed_work wq;
पूर्ण;

पूर्णांक tपंचांग_global_swapout(काष्ठा tपंचांग_operation_ctx *ctx, gfp_t gfp_flags);
पूर्णांक tपंचांग_device_swapout(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_operation_ctx *ctx,
		       gfp_t gfp_flags);

अटल अंतरभूत काष्ठा tपंचांग_resource_manager *
tपंचांग_manager_type(काष्ठा tपंचांग_device *bdev, पूर्णांक mem_type)
अणु
	वापस bdev->man_drv[mem_type];
पूर्ण

अटल अंतरभूत व्योम tपंचांग_set_driver_manager(काष्ठा tपंचांग_device *bdev, पूर्णांक type,
					  काष्ठा tपंचांग_resource_manager *manager)
अणु
	bdev->man_drv[type] = manager;
पूर्ण

पूर्णांक tपंचांग_device_init(काष्ठा tपंचांग_device *bdev, काष्ठा tपंचांग_device_funcs *funcs,
		    काष्ठा device *dev, काष्ठा address_space *mapping,
		    काष्ठा drm_vma_offset_manager *vma_manager,
		    bool use_dma_alloc, bool use_dma32);
व्योम tपंचांग_device_fini(काष्ठा tपंचांग_device *bdev);

#पूर्ण_अगर
