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

#अगर_अघोषित _TTM_RESOURCE_H_
#घोषणा _TTM_RESOURCE_H_

#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/dma-fence.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/tपंचांग/tपंचांग_caching.h>

#घोषणा TTM_MAX_BO_PRIORITY	4U

काष्ठा tपंचांग_device;
काष्ठा tपंचांग_resource_manager;
काष्ठा tपंचांग_resource;
काष्ठा tपंचांग_place;
काष्ठा tपंचांग_buffer_object;

काष्ठा tपंचांग_resource_manager_func अणु
	/**
	 * काष्ठा tपंचांग_resource_manager_func member alloc
	 *
	 * @man: Poपूर्णांकer to a memory type manager.
	 * @bo: Poपूर्णांकer to the buffer object we're allocating space क्रम.
	 * @placement: Placement details.
	 * @flags: Additional placement flags.
	 * @mem: Poपूर्णांकer to a काष्ठा tपंचांग_resource to be filled in.
	 *
	 * This function should allocate space in the memory type managed
	 * by @man. Placement details अगर
	 * applicable are given by @placement. If successful,
	 * @mem::mm_node should be set to a non-null value, and
	 * @mem::start should be set to a value identअगरying the beginning
	 * of the range allocated, and the function should वापस zero.
	 * If the memory region accommodate the buffer object, @mem::mm_node
	 * should be set to शून्य, and the function should वापस 0.
	 * If a प्रणाली error occurred, preventing the request to be fulfilled,
	 * the function should वापस a negative error code.
	 *
	 * Note that @mem::mm_node will only be dereferenced by
	 * काष्ठा tपंचांग_resource_manager functions and optionally by the driver,
	 * which has knowledge of the underlying type.
	 *
	 * This function may not be called from within atomic context, so
	 * an implementation can and must use either a mutex or a spinlock to
	 * protect any data काष्ठाures managing the space.
	 */
	पूर्णांक  (*alloc)(काष्ठा tपंचांग_resource_manager *man,
		      काष्ठा tपंचांग_buffer_object *bo,
		      स्थिर काष्ठा tपंचांग_place *place,
		      काष्ठा tपंचांग_resource *mem);

	/**
	 * काष्ठा tपंचांग_resource_manager_func member मुक्त
	 *
	 * @man: Poपूर्णांकer to a memory type manager.
	 * @mem: Poपूर्णांकer to a काष्ठा tपंचांग_resource to be filled in.
	 *
	 * This function मुक्तs memory type resources previously allocated
	 * and that are identअगरied by @mem::mm_node and @mem::start. May not
	 * be called from within atomic context.
	 */
	व्योम (*मुक्त)(काष्ठा tपंचांग_resource_manager *man,
		     काष्ठा tपंचांग_resource *mem);

	/**
	 * काष्ठा tपंचांग_resource_manager_func member debug
	 *
	 * @man: Poपूर्णांकer to a memory type manager.
	 * @prपूर्णांकer: Prefix to be used in prपूर्णांकout to identअगरy the caller.
	 *
	 * This function is called to prपूर्णांक out the state of the memory
	 * type manager to aid debugging of out-of-memory conditions.
	 * It may not be called from within atomic context.
	 */
	व्योम (*debug)(काष्ठा tपंचांग_resource_manager *man,
		      काष्ठा drm_prपूर्णांकer *prपूर्णांकer);
पूर्ण;

/**
 * काष्ठा tपंचांग_resource_manager
 *
 * @use_type: The memory type is enabled.
 * @flags: TTM_MEMTYPE_XX flags identअगरying the traits of the memory
 * managed by this memory type.
 * @gpu_offset: If used, the GPU offset of the first managed page of
 * fixed memory or the first managed location in an aperture.
 * @size: Size of the managed region.
 * @func: काष्ठाure poपूर्णांकer implementing the range manager. See above
 * @move_lock: lock क्रम move fence
 * अटल inक्रमmation. bdev::driver::io_mem_मुक्त is never used.
 * @lru: The lru list क्रम this memory type.
 * @move: The fence of the last pipelined move operation.
 *
 * This काष्ठाure is used to identअगरy and manage memory types क्रम a device.
 */
काष्ठा tपंचांग_resource_manager अणु
	/*
	 * No protection. Constant from start.
	 */
	bool use_type;
	bool use_tt;
	uपूर्णांक64_t size;
	स्थिर काष्ठा tपंचांग_resource_manager_func *func;
	spinlock_t move_lock;

	/*
	 * Protected by the global->lru_lock.
	 */

	काष्ठा list_head lru[TTM_MAX_BO_PRIORITY];

	/*
	 * Protected by @move_lock.
	 */
	काष्ठा dma_fence *move;
पूर्ण;

/**
 * काष्ठा tपंचांग_bus_placement
 *
 * @addr:		mapped भव address
 * @offset:		physical addr
 * @is_iomem:		is this io memory ?
 *
 * Structure indicating the bus placement of an object.
 */
काष्ठा tपंचांग_bus_placement अणु
	व्योम			*addr;
	phys_addr_t		offset;
	bool			is_iomem;
	क्रमागत tपंचांग_caching	caching;
पूर्ण;

/**
 * काष्ठा tपंचांग_resource
 *
 * @mm_node: Memory manager node.
 * @size: Requested size of memory region.
 * @num_pages: Actual size of memory region in pages.
 * @page_alignment: Page alignment.
 * @placement: Placement flags.
 * @bus: Placement on io bus accessible to the CPU
 *
 * Structure indicating the placement and space resources used by a
 * buffer object.
 */
काष्ठा tपंचांग_resource अणु
	व्योम *mm_node;
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ num_pages;
	uपूर्णांक32_t page_alignment;
	uपूर्णांक32_t mem_type;
	uपूर्णांक32_t placement;
	काष्ठा tपंचांग_bus_placement bus;
पूर्ण;

/**
 * tपंचांग_resource_manager_set_used
 *
 * @man: A memory manager object.
 * @used: usage state to set.
 *
 * Set the manager in use flag. If disabled the manager is no दीर्घer
 * used क्रम object placement.
 */
अटल अंतरभूत व्योम
tपंचांग_resource_manager_set_used(काष्ठा tपंचांग_resource_manager *man, bool used)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < TTM_MAX_BO_PRIORITY; i++)
		WARN_ON(!list_empty(&man->lru[i]));
	man->use_type = used;
पूर्ण

/**
 * tपंचांग_resource_manager_used
 *
 * @man: Manager to get used state क्रम
 *
 * Get the in use flag क्रम a manager.
 * Returns:
 * true is used, false अगर not.
 */
अटल अंतरभूत bool tपंचांग_resource_manager_used(काष्ठा tपंचांग_resource_manager *man)
अणु
	वापस man->use_type;
पूर्ण

/**
 * tपंचांग_resource_manager_cleanup
 *
 * @man: A memory manager object.
 *
 * Cleanup the move fences from the memory manager object.
 */
अटल अंतरभूत व्योम
tपंचांग_resource_manager_cleanup(काष्ठा tपंचांग_resource_manager *man)
अणु
	dma_fence_put(man->move);
	man->move = शून्य;
पूर्ण

पूर्णांक tपंचांग_resource_alloc(काष्ठा tपंचांग_buffer_object *bo,
		       स्थिर काष्ठा tपंचांग_place *place,
		       काष्ठा tपंचांग_resource *res);
व्योम tपंचांग_resource_मुक्त(काष्ठा tपंचांग_buffer_object *bo, काष्ठा tपंचांग_resource *res);

व्योम tपंचांग_resource_manager_init(काष्ठा tपंचांग_resource_manager *man,
			       अचिन्हित दीर्घ p_size);

पूर्णांक tपंचांग_resource_manager_evict_all(काष्ठा tपंचांग_device *bdev,
				   काष्ठा tपंचांग_resource_manager *man);

व्योम tपंचांग_resource_manager_debug(काष्ठा tपंचांग_resource_manager *man,
				काष्ठा drm_prपूर्णांकer *p);

#पूर्ण_अगर
