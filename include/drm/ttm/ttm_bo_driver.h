<शैली गुरु>
/**************************************************************************
 *
 * Copyright (c) 2006-2009 Vmware, Inc., Palo Alto, CA., USA
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
#अगर_अघोषित _TTM_BO_DRIVER_H_
#घोषणा _TTM_BO_DRIVER_H_

#समावेश <drm/drm_mm.h>
#समावेश <drm/drm_vma_manager.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/fs.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/dma-resv.h>

#समावेश <drm/tपंचांग/tपंचांग_device.h>

#समावेश "ttm_bo_api.h"
#समावेश "ttm_placement.h"
#समावेश "ttm_tt.h"
#समावेश "ttm_pool.h"

/**
 * काष्ठा tपंचांग_lru_bulk_move_pos
 *
 * @first: first BO in the bulk move range
 * @last: last BO in the bulk move range
 *
 * Positions क्रम a lru bulk move.
 */
काष्ठा tपंचांग_lru_bulk_move_pos अणु
	काष्ठा tपंचांग_buffer_object *first;
	काष्ठा tपंचांग_buffer_object *last;
पूर्ण;

/**
 * काष्ठा tपंचांग_lru_bulk_move
 *
 * @tt: first/last lru entry क्रम BOs in the TT करोमुख्य
 * @vram: first/last lru entry क्रम BOs in the VRAM करोमुख्य
 * @swap: first/last lru entry क्रम BOs on the swap list
 *
 * Helper काष्ठाure क्रम bulk moves on the LRU list.
 */
काष्ठा tपंचांग_lru_bulk_move अणु
	काष्ठा tपंचांग_lru_bulk_move_pos tt[TTM_MAX_BO_PRIORITY];
	काष्ठा tपंचांग_lru_bulk_move_pos vram[TTM_MAX_BO_PRIORITY];
पूर्ण;

/*
 * tपंचांग_bo.c
 */

/**
 * tपंचांग_bo_mem_space
 *
 * @bo: Poपूर्णांकer to a काष्ठा tपंचांग_buffer_object. the data of which
 * we want to allocate space क्रम.
 * @proposed_placement: Proposed new placement क्रम the buffer object.
 * @mem: A काष्ठा tपंचांग_resource.
 * @पूर्णांकerruptible: Sleep पूर्णांकerruptible when sliping.
 * @no_रुको_gpu: Return immediately अगर the GPU is busy.
 *
 * Allocate memory space क्रम the buffer object poपूर्णांकed to by @bo, using
 * the placement flags in @mem, potentially evicting other idle buffer objects.
 * This function may sleep जबतक रुकोing क्रम space to become available.
 * Returns:
 * -EBUSY: No space available (only अगर no_रुको == 1).
 * -ENOMEM: Could not allocate memory क्रम the buffer object, either due to
 * fragmentation or concurrent allocators.
 * -ERESTARTSYS: An पूर्णांकerruptible sleep was पूर्णांकerrupted by a संकेत.
 */
पूर्णांक tपंचांग_bo_mem_space(काष्ठा tपंचांग_buffer_object *bo,
		     काष्ठा tपंचांग_placement *placement,
		     काष्ठा tपंचांग_resource *mem,
		     काष्ठा tपंचांग_operation_ctx *ctx);

/**
 * tपंचांग_bo_unmap_भव
 *
 * @bo: tear करोwn the भव mappings क्रम this BO
 */
व्योम tपंचांग_bo_unmap_भव(काष्ठा tपंचांग_buffer_object *bo);

/**
 * tपंचांग_bo_reserve:
 *
 * @bo: A poपूर्णांकer to a काष्ठा tपंचांग_buffer_object.
 * @पूर्णांकerruptible: Sleep पूर्णांकerruptible अगर रुकोing.
 * @no_रुको: Don't sleep जबतक trying to reserve, rather वापस -EBUSY.
 * @ticket: ticket used to acquire the ww_mutex.
 *
 * Locks a buffer object क्रम validation. (Or prevents other processes from
 * locking it क्रम validation), जबतक taking a number of measures to prevent
 * deadlocks.
 *
 * Returns:
 * -EDEADLK: The reservation may cause a deadlock.
 * Release all buffer reservations, रुको क्रम @bo to become unreserved and
 * try again.
 * -ERESTARTSYS: A रुको क्रम the buffer to become unreserved was पूर्णांकerrupted by
 * a संकेत. Release all buffer reservations and वापस to user-space.
 * -EBUSY: The function needed to sleep, but @no_रुको was true
 * -EALREADY: Bo alपढ़ोy reserved using @ticket. This error code will only
 * be वापसed अगर @use_ticket is set to true.
 */
अटल अंतरभूत पूर्णांक tपंचांग_bo_reserve(काष्ठा tपंचांग_buffer_object *bo,
				 bool पूर्णांकerruptible, bool no_रुको,
				 काष्ठा ww_acquire_ctx *ticket)
अणु
	पूर्णांक ret = 0;

	अगर (no_रुको) अणु
		bool success;
		अगर (WARN_ON(ticket))
			वापस -EBUSY;

		success = dma_resv_trylock(bo->base.resv);
		वापस success ? 0 : -EBUSY;
	पूर्ण

	अगर (पूर्णांकerruptible)
		ret = dma_resv_lock_पूर्णांकerruptible(bo->base.resv, ticket);
	अन्यथा
		ret = dma_resv_lock(bo->base.resv, ticket);
	अगर (ret == -EINTR)
		वापस -ERESTARTSYS;
	वापस ret;
पूर्ण

/**
 * tपंचांग_bo_reserve_slowpath:
 * @bo: A poपूर्णांकer to a काष्ठा tपंचांग_buffer_object.
 * @पूर्णांकerruptible: Sleep पूर्णांकerruptible अगर रुकोing.
 * @sequence: Set (@bo)->sequence to this value after lock
 *
 * This is called after tपंचांग_bo_reserve वापसs -EAGAIN and we backed off
 * from all our other reservations. Because there are no other reservations
 * held by us, this function cannot deadlock any more.
 */
अटल अंतरभूत पूर्णांक tपंचांग_bo_reserve_slowpath(काष्ठा tपंचांग_buffer_object *bo,
					  bool पूर्णांकerruptible,
					  काष्ठा ww_acquire_ctx *ticket)
अणु
	अगर (पूर्णांकerruptible) अणु
		पूर्णांक ret = dma_resv_lock_slow_पूर्णांकerruptible(bo->base.resv,
							   ticket);
		अगर (ret == -EINTR)
			ret = -ERESTARTSYS;
		वापस ret;
	पूर्ण
	dma_resv_lock_slow(bo->base.resv, ticket);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
tपंचांग_bo_move_to_lru_tail_unlocked(काष्ठा tपंचांग_buffer_object *bo)
अणु
	spin_lock(&bo->bdev->lru_lock);
	tपंचांग_bo_move_to_lru_tail(bo, &bo->mem, शून्य);
	spin_unlock(&bo->bdev->lru_lock);
पूर्ण

अटल अंतरभूत व्योम tपंचांग_bo_assign_mem(काष्ठा tपंचांग_buffer_object *bo,
				     काष्ठा tपंचांग_resource *new_mem)
अणु
	bo->mem = *new_mem;
	new_mem->mm_node = शून्य;
पूर्ण

/**
 * tपंचांग_bo_move_null = assign memory क्रम a buffer object.
 * @bo: The bo to assign the memory to
 * @new_mem: The memory to be asचिन्हित.
 *
 * Assign the memory from new_mem to the memory of the buffer object bo.
 */
अटल अंतरभूत व्योम tपंचांग_bo_move_null(काष्ठा tपंचांग_buffer_object *bo,
				    काष्ठा tपंचांग_resource *new_mem)
अणु
	काष्ठा tपंचांग_resource *old_mem = &bo->mem;

	WARN_ON(old_mem->mm_node != शून्य);
	tपंचांग_bo_assign_mem(bo, new_mem);
पूर्ण

/**
 * tपंचांग_bo_unreserve
 *
 * @bo: A poपूर्णांकer to a काष्ठा tपंचांग_buffer_object.
 *
 * Unreserve a previous reservation of @bo.
 */
अटल अंतरभूत व्योम tपंचांग_bo_unreserve(काष्ठा tपंचांग_buffer_object *bo)
अणु
	tपंचांग_bo_move_to_lru_tail_unlocked(bo);
	dma_resv_unlock(bo->base.resv);
पूर्ण

/*
 * tपंचांग_bo_util.c
 */
पूर्णांक tपंचांग_mem_io_reserve(काष्ठा tपंचांग_device *bdev,
		       काष्ठा tपंचांग_resource *mem);
व्योम tपंचांग_mem_io_मुक्त(काष्ठा tपंचांग_device *bdev,
		     काष्ठा tपंचांग_resource *mem);

/**
 * tपंचांग_bo_move_स_नकल
 *
 * @bo: A poपूर्णांकer to a काष्ठा tपंचांग_buffer_object.
 * @पूर्णांकerruptible: Sleep पूर्णांकerruptible अगर रुकोing.
 * @no_रुको_gpu: Return immediately अगर the GPU is busy.
 * @new_mem: काष्ठा tपंचांग_resource indicating where to move.
 *
 * Fallback move function क्रम a mappable buffer object in mappable memory.
 * The function will, अगर successful,
 * मुक्त any old aperture space, and set (@new_mem)->mm_node to शून्य,
 * and update the (@bo)->mem placement flags. If unsuccessful, the old
 * data reमुख्यs untouched, and it's up to the caller to मुक्त the
 * memory space indicated by @new_mem.
 * Returns:
 * !0: Failure.
 */

पूर्णांक tपंचांग_bo_move_स_नकल(काष्ठा tपंचांग_buffer_object *bo,
		       काष्ठा tपंचांग_operation_ctx *ctx,
		       काष्ठा tपंचांग_resource *new_mem);

/**
 * tपंचांग_bo_move_accel_cleanup.
 *
 * @bo: A poपूर्णांकer to a काष्ठा tपंचांग_buffer_object.
 * @fence: A fence object that संकेतs when moving is complete.
 * @evict: This is an evict move. Don't वापस until the buffer is idle.
 * @pipeline: evictions are to be pipelined.
 * @new_mem: काष्ठा tपंचांग_resource indicating where to move.
 *
 * Accelerated move function to be called when an accelerated move
 * has been scheduled. The function will create a new temporary buffer object
 * representing the old placement, and put the sync object on both buffer
 * objects. After that the newly created buffer object is unref'd to be
 * destroyed when the move is complete. This will help pipeline
 * buffer moves.
 */
पूर्णांक tपंचांग_bo_move_accel_cleanup(काष्ठा tपंचांग_buffer_object *bo,
			      काष्ठा dma_fence *fence, bool evict,
			      bool pipeline,
			      काष्ठा tपंचांग_resource *new_mem);

/**
 * tपंचांग_bo_pipeline_gutting.
 *
 * @bo: A poपूर्णांकer to a काष्ठा tपंचांग_buffer_object.
 *
 * Pipelined gutting a BO of its backing store.
 */
पूर्णांक tपंचांग_bo_pipeline_gutting(काष्ठा tपंचांग_buffer_object *bo);

/**
 * tपंचांग_io_prot
 *
 * bo: tपंचांग buffer object
 * res: tपंचांग resource object
 * @पंचांगp: Page protection flag क्रम a normal, cached mapping.
 *
 * Utility function that वापसs the pgprot_t that should be used क्रम
 * setting up a PTE with the caching model indicated by @c_state.
 */
pgprot_t tपंचांग_io_prot(काष्ठा tपंचांग_buffer_object *bo, काष्ठा tपंचांग_resource *res,
		     pgprot_t पंचांगp);

/**
 * tपंचांग_bo_tt_bind
 *
 * Bind the object tt to a memory resource.
 */
पूर्णांक tपंचांग_bo_tt_bind(काष्ठा tपंचांग_buffer_object *bo, काष्ठा tपंचांग_resource *mem);

/**
 * tपंचांग_bo_tt_destroy.
 */
व्योम tपंचांग_bo_tt_destroy(काष्ठा tपंचांग_buffer_object *bo);

/**
 * tपंचांग_range_man_init
 *
 * @bdev: tपंचांग device
 * @type: memory manager type
 * @use_tt: अगर the memory manager uses tt
 * @p_size: size of area to be managed in pages.
 *
 * Initialise a generic range manager क्रम the selected memory type.
 * The range manager is installed क्रम this device in the type slot.
 */
पूर्णांक tपंचांग_range_man_init(काष्ठा tपंचांग_device *bdev,
		       अचिन्हित type, bool use_tt,
		       अचिन्हित दीर्घ p_size);

/**
 * tपंचांग_range_man_fini
 *
 * @bdev: tपंचांग device
 * @type: memory manager type
 *
 * Remove the generic range manager from a slot and tear it करोwn.
 */
पूर्णांक tपंचांग_range_man_fini(काष्ठा tपंचांग_device *bdev,
		       अचिन्हित type);

#पूर्ण_अगर
