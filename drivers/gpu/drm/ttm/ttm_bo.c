<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
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

#घोषणा pr_fmt(fmt) "[TTM] " fmt

#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>
#समावेश <drm/tपंचांग/tपंचांग_placement.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/file.h>
#समावेश <linux/module.h>
#समावेश <linux/atomic.h>
#समावेश <linux/dma-resv.h>

#समावेश "ttm_module.h"

/* शेष deकाष्ठाor */
अटल व्योम tपंचांग_bo_शेष_destroy(काष्ठा tपंचांग_buffer_object *bo)
अणु
	kमुक्त(bo);
पूर्ण

अटल व्योम tपंचांग_bo_mem_space_debug(काष्ठा tपंचांग_buffer_object *bo,
					काष्ठा tपंचांग_placement *placement)
अणु
	काष्ठा drm_prपूर्णांकer p = drm_debug_prपूर्णांकer(TTM_PFX);
	काष्ठा tपंचांग_resource_manager *man;
	पूर्णांक i, mem_type;

	drm_म_लिखो(&p, "No space for %p (%lu pages, %zuK, %zuM)\n",
		   bo, bo->mem.num_pages, bo->base.size >> 10,
		   bo->base.size >> 20);
	क्रम (i = 0; i < placement->num_placement; i++) अणु
		mem_type = placement->placement[i].mem_type;
		drm_म_लिखो(&p, "  placement[%d]=0x%08X (%d)\n",
			   i, placement->placement[i].flags, mem_type);
		man = tपंचांग_manager_type(bo->bdev, mem_type);
		tपंचांग_resource_manager_debug(man, &p);
	पूर्ण
पूर्ण

अटल व्योम tपंचांग_bo_del_from_lru(काष्ठा tपंचांग_buffer_object *bo)
अणु
	काष्ठा tपंचांग_device *bdev = bo->bdev;

	list_del_init(&bo->lru);

	अगर (bdev->funcs->del_from_lru_notअगरy)
		bdev->funcs->del_from_lru_notअगरy(bo);
पूर्ण

अटल व्योम tपंचांग_bo_bulk_move_set_pos(काष्ठा tपंचांग_lru_bulk_move_pos *pos,
				     काष्ठा tपंचांग_buffer_object *bo)
अणु
	अगर (!pos->first)
		pos->first = bo;
	pos->last = bo;
पूर्ण

व्योम tपंचांग_bo_move_to_lru_tail(काष्ठा tपंचांग_buffer_object *bo,
			     काष्ठा tपंचांग_resource *mem,
			     काष्ठा tपंचांग_lru_bulk_move *bulk)
अणु
	काष्ठा tपंचांग_device *bdev = bo->bdev;
	काष्ठा tपंचांग_resource_manager *man;

	अगर (!bo->deleted)
		dma_resv_निश्चित_held(bo->base.resv);

	अगर (bo->pin_count) अणु
		tपंचांग_bo_del_from_lru(bo);
		वापस;
	पूर्ण

	man = tपंचांग_manager_type(bdev, mem->mem_type);
	list_move_tail(&bo->lru, &man->lru[bo->priority]);

	अगर (bdev->funcs->del_from_lru_notअगरy)
		bdev->funcs->del_from_lru_notअगरy(bo);

	अगर (bulk && !bo->pin_count) अणु
		चयन (bo->mem.mem_type) अणु
		हाल TTM_PL_TT:
			tपंचांग_bo_bulk_move_set_pos(&bulk->tt[bo->priority], bo);
			अवरोध;

		हाल TTM_PL_VRAM:
			tपंचांग_bo_bulk_move_set_pos(&bulk->vram[bo->priority], bo);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_move_to_lru_tail);

व्योम tपंचांग_bo_bulk_move_lru_tail(काष्ठा tपंचांग_lru_bulk_move *bulk)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < TTM_MAX_BO_PRIORITY; ++i) अणु
		काष्ठा tपंचांग_lru_bulk_move_pos *pos = &bulk->tt[i];
		काष्ठा tपंचांग_resource_manager *man;

		अगर (!pos->first)
			जारी;

		dma_resv_निश्चित_held(pos->first->base.resv);
		dma_resv_निश्चित_held(pos->last->base.resv);

		man = tपंचांग_manager_type(pos->first->bdev, TTM_PL_TT);
		list_bulk_move_tail(&man->lru[i], &pos->first->lru,
				    &pos->last->lru);
	पूर्ण

	क्रम (i = 0; i < TTM_MAX_BO_PRIORITY; ++i) अणु
		काष्ठा tपंचांग_lru_bulk_move_pos *pos = &bulk->vram[i];
		काष्ठा tपंचांग_resource_manager *man;

		अगर (!pos->first)
			जारी;

		dma_resv_निश्चित_held(pos->first->base.resv);
		dma_resv_निश्चित_held(pos->last->base.resv);

		man = tपंचांग_manager_type(pos->first->bdev, TTM_PL_VRAM);
		list_bulk_move_tail(&man->lru[i], &pos->first->lru,
				    &pos->last->lru);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_bulk_move_lru_tail);

अटल पूर्णांक tपंचांग_bo_handle_move_mem(काष्ठा tपंचांग_buffer_object *bo,
				  काष्ठा tपंचांग_resource *mem, bool evict,
				  काष्ठा tपंचांग_operation_ctx *ctx,
				  काष्ठा tपंचांग_place *hop)
अणु
	काष्ठा tपंचांग_device *bdev = bo->bdev;
	काष्ठा tपंचांग_resource_manager *old_man = tपंचांग_manager_type(bdev, bo->mem.mem_type);
	काष्ठा tपंचांग_resource_manager *new_man = tपंचांग_manager_type(bdev, mem->mem_type);
	पूर्णांक ret;

	tपंचांग_bo_unmap_भव(bo);

	/*
	 * Create and bind a tपंचांग अगर required.
	 */

	अगर (new_man->use_tt) अणु
		/* Zero init the new TTM काष्ठाure अगर the old location should
		 * have used one as well.
		 */
		ret = tपंचांग_tt_create(bo, old_man->use_tt);
		अगर (ret)
			जाओ out_err;

		अगर (mem->mem_type != TTM_PL_SYSTEM) अणु
			ret = tपंचांग_tt_populate(bo->bdev, bo->tपंचांग, ctx);
			अगर (ret)
				जाओ out_err;
		पूर्ण
	पूर्ण

	ret = bdev->funcs->move(bo, evict, ctx, mem, hop);
	अगर (ret) अणु
		अगर (ret == -EMULTIHOP)
			वापस ret;
		जाओ out_err;
	पूर्ण

	ctx->bytes_moved += bo->base.size;
	वापस 0;

out_err:
	new_man = tपंचांग_manager_type(bdev, bo->mem.mem_type);
	अगर (!new_man->use_tt)
		tपंचांग_bo_tt_destroy(bo);

	वापस ret;
पूर्ण

/*
 * Call bo::reserved.
 * Will release GPU memory type usage on deकाष्ठाion.
 * This is the place to put in driver specअगरic hooks to release
 * driver निजी resources.
 * Will release the bo::reserved lock.
 */

अटल व्योम tपंचांग_bo_cleanup_memtype_use(काष्ठा tपंचांग_buffer_object *bo)
अणु
	अगर (bo->bdev->funcs->delete_mem_notअगरy)
		bo->bdev->funcs->delete_mem_notअगरy(bo);

	tपंचांग_bo_tt_destroy(bo);
	tपंचांग_resource_मुक्त(bo, &bo->mem);
पूर्ण

अटल पूर्णांक tपंचांग_bo_inभागidualize_resv(काष्ठा tपंचांग_buffer_object *bo)
अणु
	पूर्णांक r;

	अगर (bo->base.resv == &bo->base._resv)
		वापस 0;

	BUG_ON(!dma_resv_trylock(&bo->base._resv));

	r = dma_resv_copy_fences(&bo->base._resv, bo->base.resv);
	dma_resv_unlock(&bo->base._resv);
	अगर (r)
		वापस r;

	अगर (bo->type != tपंचांग_bo_type_sg) अणु
		/* This works because the BO is about to be destroyed and nobody
		 * reference it any more. The only tricky हाल is the trylock on
		 * the resv object जबतक holding the lru_lock.
		 */
		spin_lock(&bo->bdev->lru_lock);
		bo->base.resv = &bo->base._resv;
		spin_unlock(&bo->bdev->lru_lock);
	पूर्ण

	वापस r;
पूर्ण

अटल व्योम tपंचांग_bo_flush_all_fences(काष्ठा tपंचांग_buffer_object *bo)
अणु
	काष्ठा dma_resv *resv = &bo->base._resv;
	काष्ठा dma_resv_list *fobj;
	काष्ठा dma_fence *fence;
	पूर्णांक i;

	rcu_पढ़ो_lock();
	fobj = rcu_dereference(resv->fence);
	fence = rcu_dereference(resv->fence_excl);
	अगर (fence && !fence->ops->संकेतed)
		dma_fence_enable_sw_संकेतing(fence);

	क्रम (i = 0; fobj && i < fobj->shared_count; ++i) अणु
		fence = rcu_dereference(fobj->shared[i]);

		अगर (!fence->ops->संकेतed)
			dma_fence_enable_sw_संकेतing(fence);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

/**
 * function tपंचांग_bo_cleanup_refs
 * If bo idle, हटाओ from lru lists, and unref.
 * If not idle, block अगर possible.
 *
 * Must be called with lru_lock and reservation held, this function
 * will drop the lru lock and optionally the reservation lock beक्रमe वापसing.
 *
 * @bo:                    The buffer object to clean-up
 * @पूर्णांकerruptible:         Any sleeps should occur पूर्णांकerruptibly.
 * @no_रुको_gpu:           Never रुको क्रम gpu. Return -EBUSY instead.
 * @unlock_resv:           Unlock the reservation lock as well.
 */

अटल पूर्णांक tपंचांग_bo_cleanup_refs(काष्ठा tपंचांग_buffer_object *bo,
			       bool पूर्णांकerruptible, bool no_रुको_gpu,
			       bool unlock_resv)
अणु
	काष्ठा dma_resv *resv = &bo->base._resv;
	पूर्णांक ret;

	अगर (dma_resv_test_संकेतed_rcu(resv, true))
		ret = 0;
	अन्यथा
		ret = -EBUSY;

	अगर (ret && !no_रुको_gpu) अणु
		दीर्घ lret;

		अगर (unlock_resv)
			dma_resv_unlock(bo->base.resv);
		spin_unlock(&bo->bdev->lru_lock);

		lret = dma_resv_रुको_समयout_rcu(resv, true, पूर्णांकerruptible,
						 30 * HZ);

		अगर (lret < 0)
			वापस lret;
		अन्यथा अगर (lret == 0)
			वापस -EBUSY;

		spin_lock(&bo->bdev->lru_lock);
		अगर (unlock_resv && !dma_resv_trylock(bo->base.resv)) अणु
			/*
			 * We raced, and lost, someone अन्यथा holds the reservation now,
			 * and is probably busy in tपंचांग_bo_cleanup_memtype_use.
			 *
			 * Even अगर it's not the हाल, because we finished रुकोing any
			 * delayed deकाष्ठाion would succeed, so just वापस success
			 * here.
			 */
			spin_unlock(&bo->bdev->lru_lock);
			वापस 0;
		पूर्ण
		ret = 0;
	पूर्ण

	अगर (ret || unlikely(list_empty(&bo->ddestroy))) अणु
		अगर (unlock_resv)
			dma_resv_unlock(bo->base.resv);
		spin_unlock(&bo->bdev->lru_lock);
		वापस ret;
	पूर्ण

	tपंचांग_bo_del_from_lru(bo);
	list_del_init(&bo->ddestroy);
	spin_unlock(&bo->bdev->lru_lock);
	tपंचांग_bo_cleanup_memtype_use(bo);

	अगर (unlock_resv)
		dma_resv_unlock(bo->base.resv);

	tपंचांग_bo_put(bo);

	वापस 0;
पूर्ण

/*
 * Traverse the delayed list, and call tपंचांग_bo_cleanup_refs on all
 * encountered buffers.
 */
bool tपंचांग_bo_delayed_delete(काष्ठा tपंचांग_device *bdev, bool हटाओ_all)
अणु
	काष्ठा list_head हटाओd;
	bool empty;

	INIT_LIST_HEAD(&हटाओd);

	spin_lock(&bdev->lru_lock);
	जबतक (!list_empty(&bdev->ddestroy)) अणु
		काष्ठा tपंचांग_buffer_object *bo;

		bo = list_first_entry(&bdev->ddestroy, काष्ठा tपंचांग_buffer_object,
				      ddestroy);
		list_move_tail(&bo->ddestroy, &हटाओd);
		अगर (!tपंचांग_bo_get_unless_zero(bo))
			जारी;

		अगर (हटाओ_all || bo->base.resv != &bo->base._resv) अणु
			spin_unlock(&bdev->lru_lock);
			dma_resv_lock(bo->base.resv, शून्य);

			spin_lock(&bdev->lru_lock);
			tपंचांग_bo_cleanup_refs(bo, false, !हटाओ_all, true);

		पूर्ण अन्यथा अगर (dma_resv_trylock(bo->base.resv)) अणु
			tपंचांग_bo_cleanup_refs(bo, false, !हटाओ_all, true);
		पूर्ण अन्यथा अणु
			spin_unlock(&bdev->lru_lock);
		पूर्ण

		tपंचांग_bo_put(bo);
		spin_lock(&bdev->lru_lock);
	पूर्ण
	list_splice_tail(&हटाओd, &bdev->ddestroy);
	empty = list_empty(&bdev->ddestroy);
	spin_unlock(&bdev->lru_lock);

	वापस empty;
पूर्ण

अटल व्योम tपंचांग_bo_release(काष्ठा kref *kref)
अणु
	काष्ठा tपंचांग_buffer_object *bo =
	    container_of(kref, काष्ठा tपंचांग_buffer_object, kref);
	काष्ठा tपंचांग_device *bdev = bo->bdev;
	पूर्णांक ret;

	अगर (!bo->deleted) अणु
		ret = tपंचांग_bo_inभागidualize_resv(bo);
		अगर (ret) अणु
			/* Last resort, अगर we fail to allocate memory क्रम the
			 * fences block क्रम the BO to become idle
			 */
			dma_resv_रुको_समयout_rcu(bo->base.resv, true, false,
						  30 * HZ);
		पूर्ण

		अगर (bo->bdev->funcs->release_notअगरy)
			bo->bdev->funcs->release_notअगरy(bo);

		drm_vma_offset_हटाओ(bdev->vma_manager, &bo->base.vma_node);
		tपंचांग_mem_io_मुक्त(bdev, &bo->mem);
	पूर्ण

	अगर (!dma_resv_test_संकेतed_rcu(bo->base.resv, true) ||
	    !dma_resv_trylock(bo->base.resv)) अणु
		/* The BO is not idle, resurrect it क्रम delayed destroy */
		tपंचांग_bo_flush_all_fences(bo);
		bo->deleted = true;

		spin_lock(&bo->bdev->lru_lock);

		/*
		 * Make pinned bos immediately available to
		 * shrinkers, now that they are queued क्रम
		 * deकाष्ठाion.
		 *
		 * FIXME: QXL is triggering this. Can be हटाओd when the
		 * driver is fixed.
		 */
		अगर (WARN_ON_ONCE(bo->pin_count)) अणु
			bo->pin_count = 0;
			tपंचांग_bo_move_to_lru_tail(bo, &bo->mem, शून्य);
		पूर्ण

		kref_init(&bo->kref);
		list_add_tail(&bo->ddestroy, &bdev->ddestroy);
		spin_unlock(&bo->bdev->lru_lock);

		schedule_delayed_work(&bdev->wq,
				      ((HZ / 100) < 1) ? 1 : HZ / 100);
		वापस;
	पूर्ण

	spin_lock(&bo->bdev->lru_lock);
	tपंचांग_bo_del_from_lru(bo);
	list_del(&bo->ddestroy);
	spin_unlock(&bo->bdev->lru_lock);

	tपंचांग_bo_cleanup_memtype_use(bo);
	dma_resv_unlock(bo->base.resv);

	atomic_dec(&tपंचांग_glob.bo_count);
	dma_fence_put(bo->moving);
	अगर (!tपंचांग_bo_uses_embedded_gem_object(bo))
		dma_resv_fini(&bo->base._resv);
	bo->destroy(bo);
पूर्ण

व्योम tपंचांग_bo_put(काष्ठा tपंचांग_buffer_object *bo)
अणु
	kref_put(&bo->kref, tपंचांग_bo_release);
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_put);

पूर्णांक tपंचांग_bo_lock_delayed_workqueue(काष्ठा tपंचांग_device *bdev)
अणु
	वापस cancel_delayed_work_sync(&bdev->wq);
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_lock_delayed_workqueue);

व्योम tपंचांग_bo_unlock_delayed_workqueue(काष्ठा tपंचांग_device *bdev, पूर्णांक resched)
अणु
	अगर (resched)
		schedule_delayed_work(&bdev->wq,
				      ((HZ / 100) < 1) ? 1 : HZ / 100);
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_unlock_delayed_workqueue);

अटल पूर्णांक tपंचांग_bo_evict(काष्ठा tपंचांग_buffer_object *bo,
			काष्ठा tपंचांग_operation_ctx *ctx)
अणु
	काष्ठा tपंचांग_device *bdev = bo->bdev;
	काष्ठा tपंचांग_resource evict_mem;
	काष्ठा tपंचांग_placement placement;
	काष्ठा tपंचांग_place hop;
	पूर्णांक ret = 0;

	स_रखो(&hop, 0, माप(hop));

	dma_resv_निश्चित_held(bo->base.resv);

	placement.num_placement = 0;
	placement.num_busy_placement = 0;
	bdev->funcs->evict_flags(bo, &placement);

	अगर (!placement.num_placement && !placement.num_busy_placement) अणु
		tपंचांग_bo_रुको(bo, false, false);

		tपंचांग_bo_cleanup_memtype_use(bo);
		वापस tपंचांग_tt_create(bo, false);
	पूर्ण

	evict_mem = bo->mem;
	evict_mem.mm_node = शून्य;
	evict_mem.bus.offset = 0;
	evict_mem.bus.addr = शून्य;

	ret = tपंचांग_bo_mem_space(bo, &placement, &evict_mem, ctx);
	अगर (ret) अणु
		अगर (ret != -ERESTARTSYS) अणु
			pr_err("Failed to find memory space for buffer 0x%p eviction\n",
			       bo);
			tपंचांग_bo_mem_space_debug(bo, &placement);
		पूर्ण
		जाओ out;
	पूर्ण

	ret = tपंचांग_bo_handle_move_mem(bo, &evict_mem, true, ctx, &hop);
	अगर (unlikely(ret)) अणु
		WARN(ret == -EMULTIHOP, "Unexpected multihop in eviction - likely driver bug\n");
		अगर (ret != -ERESTARTSYS)
			pr_err("Buffer eviction failed\n");
		tपंचांग_resource_मुक्त(bo, &evict_mem);
	पूर्ण
out:
	वापस ret;
पूर्ण

bool tपंचांग_bo_eviction_valuable(काष्ठा tपंचांग_buffer_object *bo,
			      स्थिर काष्ठा tपंचांग_place *place)
अणु
	/* Don't evict this BO if it's outside of the
	 * requested placement range
	 */
	अगर (place->fpfn >= (bo->mem.start + bo->mem.num_pages) ||
	    (place->lpfn && place->lpfn <= bo->mem.start))
		वापस false;

	वापस true;
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_eviction_valuable);

/*
 * Check the target bo is allowable to be evicted or swapout, including हालs:
 *
 * a. अगर share same reservation object with ctx->resv, have assumption
 * reservation objects should alपढ़ोy be locked, so not lock again and
 * वापस true directly when either the opreation allow_reserved_eviction
 * or the target bo alपढ़ोy is in delayed मुक्त list;
 *
 * b. Otherwise, trylock it.
 */
अटल bool tपंचांग_bo_evict_swapout_allowable(काष्ठा tपंचांग_buffer_object *bo,
			काष्ठा tपंचांग_operation_ctx *ctx, bool *locked, bool *busy)
अणु
	bool ret = false;

	अगर (bo->base.resv == ctx->resv) अणु
		dma_resv_निश्चित_held(bo->base.resv);
		अगर (ctx->allow_res_evict)
			ret = true;
		*locked = false;
		अगर (busy)
			*busy = false;
	पूर्ण अन्यथा अणु
		ret = dma_resv_trylock(bo->base.resv);
		*locked = ret;
		अगर (busy)
			*busy = !ret;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * tपंचांग_mem_evict_रुको_busy - रुको क्रम a busy BO to become available
 *
 * @busy_bo: BO which couldn't be locked with trylock
 * @ctx: operation context
 * @ticket: acquire ticket
 *
 * Try to lock a busy buffer object to aव्योम failing eviction.
 */
अटल पूर्णांक tपंचांग_mem_evict_रुको_busy(काष्ठा tपंचांग_buffer_object *busy_bo,
				   काष्ठा tपंचांग_operation_ctx *ctx,
				   काष्ठा ww_acquire_ctx *ticket)
अणु
	पूर्णांक r;

	अगर (!busy_bo || !ticket)
		वापस -EBUSY;

	अगर (ctx->पूर्णांकerruptible)
		r = dma_resv_lock_पूर्णांकerruptible(busy_bo->base.resv,
							  ticket);
	अन्यथा
		r = dma_resv_lock(busy_bo->base.resv, ticket);

	/*
	 * TODO: It would be better to keep the BO locked until allocation is at
	 * least tried one more समय, but that would mean a much larger rework
	 * of TTM.
	 */
	अगर (!r)
		dma_resv_unlock(busy_bo->base.resv);

	वापस r == -EDEADLK ? -EBUSY : r;
पूर्ण

पूर्णांक tपंचांग_mem_evict_first(काष्ठा tपंचांग_device *bdev,
			काष्ठा tपंचांग_resource_manager *man,
			स्थिर काष्ठा tपंचांग_place *place,
			काष्ठा tपंचांग_operation_ctx *ctx,
			काष्ठा ww_acquire_ctx *ticket)
अणु
	काष्ठा tपंचांग_buffer_object *bo = शून्य, *busy_bo = शून्य;
	bool locked = false;
	अचिन्हित i;
	पूर्णांक ret;

	spin_lock(&bdev->lru_lock);
	क्रम (i = 0; i < TTM_MAX_BO_PRIORITY; ++i) अणु
		list_क्रम_each_entry(bo, &man->lru[i], lru) अणु
			bool busy;

			अगर (!tपंचांग_bo_evict_swapout_allowable(bo, ctx, &locked,
							    &busy)) अणु
				अगर (busy && !busy_bo && ticket !=
				    dma_resv_locking_ctx(bo->base.resv))
					busy_bo = bo;
				जारी;
			पूर्ण

			अगर (place && !bdev->funcs->eviction_valuable(bo,
								      place)) अणु
				अगर (locked)
					dma_resv_unlock(bo->base.resv);
				जारी;
			पूर्ण
			अगर (!tपंचांग_bo_get_unless_zero(bo)) अणु
				अगर (locked)
					dma_resv_unlock(bo->base.resv);
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण

		/* If the inner loop terminated early, we have our candidate */
		अगर (&bo->lru != &man->lru[i])
			अवरोध;

		bo = शून्य;
	पूर्ण

	अगर (!bo) अणु
		अगर (busy_bo && !tपंचांग_bo_get_unless_zero(busy_bo))
			busy_bo = शून्य;
		spin_unlock(&bdev->lru_lock);
		ret = tपंचांग_mem_evict_रुको_busy(busy_bo, ctx, ticket);
		अगर (busy_bo)
			tपंचांग_bo_put(busy_bo);
		वापस ret;
	पूर्ण

	अगर (bo->deleted) अणु
		ret = tपंचांग_bo_cleanup_refs(bo, ctx->पूर्णांकerruptible,
					  ctx->no_रुको_gpu, locked);
		tपंचांग_bo_put(bo);
		वापस ret;
	पूर्ण

	spin_unlock(&bdev->lru_lock);

	ret = tपंचांग_bo_evict(bo, ctx);
	अगर (locked)
		tपंचांग_bo_unreserve(bo);

	tपंचांग_bo_put(bo);
	वापस ret;
पूर्ण

/*
 * Add the last move fence to the BO and reserve a new shared slot.
 */
अटल पूर्णांक tपंचांग_bo_add_move_fence(काष्ठा tपंचांग_buffer_object *bo,
				 काष्ठा tपंचांग_resource_manager *man,
				 काष्ठा tपंचांग_resource *mem,
				 bool no_रुको_gpu)
अणु
	काष्ठा dma_fence *fence;
	पूर्णांक ret;

	spin_lock(&man->move_lock);
	fence = dma_fence_get(man->move);
	spin_unlock(&man->move_lock);

	अगर (!fence)
		वापस 0;

	अगर (no_रुको_gpu) अणु
		ret = dma_fence_is_संकेतed(fence) ? 0 : -EBUSY;
		dma_fence_put(fence);
		वापस ret;
	पूर्ण

	dma_resv_add_shared_fence(bo->base.resv, fence);

	ret = dma_resv_reserve_shared(bo->base.resv, 1);
	अगर (unlikely(ret)) अणु
		dma_fence_put(fence);
		वापस ret;
	पूर्ण

	dma_fence_put(bo->moving);
	bo->moving = fence;
	वापस 0;
पूर्ण

/*
 * Repeatedly evict memory from the LRU क्रम @mem_type until we create enough
 * space, or we've evicted everything and there isn't enough space.
 */
अटल पूर्णांक tपंचांग_bo_mem_क्रमce_space(काष्ठा tपंचांग_buffer_object *bo,
				  स्थिर काष्ठा tपंचांग_place *place,
				  काष्ठा tपंचांग_resource *mem,
				  काष्ठा tपंचांग_operation_ctx *ctx)
अणु
	काष्ठा tपंचांग_device *bdev = bo->bdev;
	काष्ठा tपंचांग_resource_manager *man = tपंचांग_manager_type(bdev, mem->mem_type);
	काष्ठा ww_acquire_ctx *ticket;
	पूर्णांक ret;

	ticket = dma_resv_locking_ctx(bo->base.resv);
	करो अणु
		ret = tपंचांग_resource_alloc(bo, place, mem);
		अगर (likely(!ret))
			अवरोध;
		अगर (unlikely(ret != -ENOSPC))
			वापस ret;
		ret = tपंचांग_mem_evict_first(bdev, man, place, ctx,
					  ticket);
		अगर (unlikely(ret != 0))
			वापस ret;
	पूर्ण जबतक (1);

	वापस tपंचांग_bo_add_move_fence(bo, man, mem, ctx->no_रुको_gpu);
पूर्ण

/**
 * tपंचांग_bo_mem_placement - check अगर placement is compatible
 * @bo: BO to find memory क्रम
 * @place: where to search
 * @mem: the memory object to fill in
 *
 * Check अगर placement is compatible and fill in mem काष्ठाure.
 * Returns -EBUSY अगर placement won't work or negative error code.
 * 0 when placement can be used.
 */
अटल पूर्णांक tपंचांग_bo_mem_placement(काष्ठा tपंचांग_buffer_object *bo,
				स्थिर काष्ठा tपंचांग_place *place,
				काष्ठा tपंचांग_resource *mem)
अणु
	काष्ठा tपंचांग_device *bdev = bo->bdev;
	काष्ठा tपंचांग_resource_manager *man;

	man = tपंचांग_manager_type(bdev, place->mem_type);
	अगर (!man || !tपंचांग_resource_manager_used(man))
		वापस -EBUSY;

	mem->mem_type = place->mem_type;
	mem->placement = place->flags;

	spin_lock(&bo->bdev->lru_lock);
	tपंचांग_bo_move_to_lru_tail(bo, mem, शून्य);
	spin_unlock(&bo->bdev->lru_lock);
	वापस 0;
पूर्ण

/*
 * Creates space क्रम memory region @mem according to its type.
 *
 * This function first searches क्रम मुक्त space in compatible memory types in
 * the priority order defined by the driver.  If मुक्त space isn't found, then
 * tपंचांग_bo_mem_क्रमce_space is attempted in priority order to evict and find
 * space.
 */
पूर्णांक tपंचांग_bo_mem_space(काष्ठा tपंचांग_buffer_object *bo,
			काष्ठा tपंचांग_placement *placement,
			काष्ठा tपंचांग_resource *mem,
			काष्ठा tपंचांग_operation_ctx *ctx)
अणु
	काष्ठा tपंचांग_device *bdev = bo->bdev;
	bool type_found = false;
	पूर्णांक i, ret;

	ret = dma_resv_reserve_shared(bo->base.resv, 1);
	अगर (unlikely(ret))
		वापस ret;

	क्रम (i = 0; i < placement->num_placement; ++i) अणु
		स्थिर काष्ठा tपंचांग_place *place = &placement->placement[i];
		काष्ठा tपंचांग_resource_manager *man;

		ret = tपंचांग_bo_mem_placement(bo, place, mem);
		अगर (ret)
			जारी;

		type_found = true;
		ret = tपंचांग_resource_alloc(bo, place, mem);
		अगर (ret == -ENOSPC)
			जारी;
		अगर (unlikely(ret))
			जाओ error;

		man = tपंचांग_manager_type(bdev, mem->mem_type);
		ret = tपंचांग_bo_add_move_fence(bo, man, mem, ctx->no_रुको_gpu);
		अगर (unlikely(ret)) अणु
			tपंचांग_resource_मुक्त(bo, mem);
			अगर (ret == -EBUSY)
				जारी;

			जाओ error;
		पूर्ण
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < placement->num_busy_placement; ++i) अणु
		स्थिर काष्ठा tपंचांग_place *place = &placement->busy_placement[i];

		ret = tपंचांग_bo_mem_placement(bo, place, mem);
		अगर (ret)
			जारी;

		type_found = true;
		ret = tपंचांग_bo_mem_क्रमce_space(bo, place, mem, ctx);
		अगर (likely(!ret))
			वापस 0;

		अगर (ret && ret != -EBUSY)
			जाओ error;
	पूर्ण

	ret = -ENOMEM;
	अगर (!type_found) अणु
		pr_err(TTM_PFX "No compatible memory type found\n");
		ret = -EINVAL;
	पूर्ण

error:
	अगर (bo->mem.mem_type == TTM_PL_SYSTEM && !bo->pin_count)
		tपंचांग_bo_move_to_lru_tail_unlocked(bo);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_mem_space);

अटल पूर्णांक tपंचांग_bo_bounce_temp_buffer(काष्ठा tपंचांग_buffer_object *bo,
				     काष्ठा tपंचांग_resource *mem,
				     काष्ठा tपंचांग_operation_ctx *ctx,
				     काष्ठा tपंचांग_place *hop)
अणु
	काष्ठा tपंचांग_placement hop_placement;
	पूर्णांक ret;
	काष्ठा tपंचांग_resource hop_mem = *mem;

	hop_mem.mm_node = शून्य;
	hop_mem.mem_type = TTM_PL_SYSTEM;
	hop_mem.placement = 0;

	hop_placement.num_placement = hop_placement.num_busy_placement = 1;
	hop_placement.placement = hop_placement.busy_placement = hop;

	/* find space in the bounce करोमुख्य */
	ret = tपंचांग_bo_mem_space(bo, &hop_placement, &hop_mem, ctx);
	अगर (ret)
		वापस ret;
	/* move to the bounce करोमुख्य */
	ret = tपंचांग_bo_handle_move_mem(bo, &hop_mem, false, ctx, शून्य);
	अगर (ret) अणु
		tपंचांग_resource_मुक्त(bo, &hop_mem);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tपंचांग_bo_move_buffer(काष्ठा tपंचांग_buffer_object *bo,
			      काष्ठा tपंचांग_placement *placement,
			      काष्ठा tपंचांग_operation_ctx *ctx)
अणु
	पूर्णांक ret = 0;
	काष्ठा tपंचांग_place hop;
	काष्ठा tपंचांग_resource mem;

	dma_resv_निश्चित_held(bo->base.resv);

	स_रखो(&hop, 0, माप(hop));

	mem.num_pages = PAGE_ALIGN(bo->base.size) >> PAGE_SHIFT;
	mem.page_alignment = bo->mem.page_alignment;
	mem.bus.offset = 0;
	mem.bus.addr = शून्य;
	mem.mm_node = शून्य;

	/*
	 * Determine where to move the buffer.
	 *
	 * If driver determines move is going to need
	 * an extra step then it will वापस -EMULTIHOP
	 * and the buffer will be moved to the temporary
	 * stop and the driver will be called to make
	 * the second hop.
	 */
	ret = tपंचांग_bo_mem_space(bo, placement, &mem, ctx);
	अगर (ret)
		वापस ret;
bounce:
	ret = tपंचांग_bo_handle_move_mem(bo, &mem, false, ctx, &hop);
	अगर (ret == -EMULTIHOP) अणु
		ret = tपंचांग_bo_bounce_temp_buffer(bo, &mem, ctx, &hop);
		अगर (ret)
			जाओ out;
		/* try and move to final place now. */
		जाओ bounce;
	पूर्ण
out:
	अगर (ret)
		tपंचांग_resource_मुक्त(bo, &mem);
	वापस ret;
पूर्ण

अटल bool tपंचांग_bo_places_compat(स्थिर काष्ठा tपंचांग_place *places,
				 अचिन्हित num_placement,
				 काष्ठा tपंचांग_resource *mem,
				 uपूर्णांक32_t *new_flags)
अणु
	अचिन्हित i;

	क्रम (i = 0; i < num_placement; i++) अणु
		स्थिर काष्ठा tपंचांग_place *heap = &places[i];

		अगर ((mem->start < heap->fpfn ||
		     (heap->lpfn != 0 && (mem->start + mem->num_pages) > heap->lpfn)))
			जारी;

		*new_flags = heap->flags;
		अगर ((mem->mem_type == heap->mem_type) &&
		    (!(*new_flags & TTM_PL_FLAG_CONTIGUOUS) ||
		     (mem->placement & TTM_PL_FLAG_CONTIGUOUS)))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

bool tपंचांग_bo_mem_compat(काष्ठा tपंचांग_placement *placement,
		       काष्ठा tपंचांग_resource *mem,
		       uपूर्णांक32_t *new_flags)
अणु
	अगर (tपंचांग_bo_places_compat(placement->placement, placement->num_placement,
				 mem, new_flags))
		वापस true;

	अगर ((placement->busy_placement != placement->placement ||
	     placement->num_busy_placement > placement->num_placement) &&
	    tपंचांग_bo_places_compat(placement->busy_placement,
				 placement->num_busy_placement,
				 mem, new_flags))
		वापस true;

	वापस false;
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_mem_compat);

पूर्णांक tपंचांग_bo_validate(काष्ठा tपंचांग_buffer_object *bo,
		    काष्ठा tपंचांग_placement *placement,
		    काष्ठा tपंचांग_operation_ctx *ctx)
अणु
	पूर्णांक ret;
	uपूर्णांक32_t new_flags;

	dma_resv_निश्चित_held(bo->base.resv);

	/*
	 * Remove the backing store अगर no placement is given.
	 */
	अगर (!placement->num_placement && !placement->num_busy_placement) अणु
		ret = tपंचांग_bo_pipeline_gutting(bo);
		अगर (ret)
			वापस ret;

		वापस tपंचांग_tt_create(bo, false);
	पूर्ण

	/*
	 * Check whether we need to move buffer.
	 */
	अगर (!tपंचांग_bo_mem_compat(placement, &bo->mem, &new_flags)) अणु
		ret = tपंचांग_bo_move_buffer(bo, placement, ctx);
		अगर (ret)
			वापस ret;
	पूर्ण
	/*
	 * We might need to add a TTM.
	 */
	अगर (bo->mem.mem_type == TTM_PL_SYSTEM) अणु
		ret = tपंचांग_tt_create(bo, true);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_validate);

पूर्णांक tपंचांग_bo_init_reserved(काष्ठा tपंचांग_device *bdev,
			 काष्ठा tपंचांग_buffer_object *bo,
			 माप_प्रकार size,
			 क्रमागत tपंचांग_bo_type type,
			 काष्ठा tपंचांग_placement *placement,
			 uपूर्णांक32_t page_alignment,
			 काष्ठा tपंचांग_operation_ctx *ctx,
			 काष्ठा sg_table *sg,
			 काष्ठा dma_resv *resv,
			 व्योम (*destroy) (काष्ठा tपंचांग_buffer_object *))
अणु
	bool locked;
	पूर्णांक ret = 0;

	bo->destroy = destroy ? destroy : tपंचांग_bo_शेष_destroy;

	kref_init(&bo->kref);
	INIT_LIST_HEAD(&bo->lru);
	INIT_LIST_HEAD(&bo->ddestroy);
	bo->bdev = bdev;
	bo->type = type;
	bo->mem.mem_type = TTM_PL_SYSTEM;
	bo->mem.num_pages = PAGE_ALIGN(size) >> PAGE_SHIFT;
	bo->mem.mm_node = शून्य;
	bo->mem.page_alignment = page_alignment;
	bo->mem.bus.offset = 0;
	bo->mem.bus.addr = शून्य;
	bo->moving = शून्य;
	bo->mem.placement = 0;
	bo->pin_count = 0;
	bo->sg = sg;
	अगर (resv) अणु
		bo->base.resv = resv;
		dma_resv_निश्चित_held(bo->base.resv);
	पूर्ण अन्यथा अणु
		bo->base.resv = &bo->base._resv;
	पूर्ण
	अगर (!tपंचांग_bo_uses_embedded_gem_object(bo)) अणु
		/*
		 * bo.base is not initialized, so we have to setup the
		 * काष्ठा elements we want use regardless.
		 */
		bo->base.size = size;
		dma_resv_init(&bo->base._resv);
		drm_vma_node_reset(&bo->base.vma_node);
	पूर्ण
	atomic_inc(&tपंचांग_glob.bo_count);

	/*
	 * For tपंचांग_bo_type_device buffers, allocate
	 * address space from the device.
	 */
	अगर (bo->type == tपंचांग_bo_type_device ||
	    bo->type == tपंचांग_bo_type_sg)
		ret = drm_vma_offset_add(bdev->vma_manager, &bo->base.vma_node,
					 bo->mem.num_pages);

	/* passed reservation objects should alपढ़ोy be locked,
	 * since otherwise lockdep will be angered in radeon.
	 */
	अगर (!resv) अणु
		locked = dma_resv_trylock(bo->base.resv);
		WARN_ON(!locked);
	पूर्ण

	अगर (likely(!ret))
		ret = tपंचांग_bo_validate(bo, placement, ctx);

	अगर (unlikely(ret)) अणु
		अगर (!resv)
			tपंचांग_bo_unreserve(bo);

		tपंचांग_bo_put(bo);
		वापस ret;
	पूर्ण

	tपंचांग_bo_move_to_lru_tail_unlocked(bo);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_init_reserved);

पूर्णांक tपंचांग_bo_init(काष्ठा tपंचांग_device *bdev,
		काष्ठा tपंचांग_buffer_object *bo,
		माप_प्रकार size,
		क्रमागत tपंचांग_bo_type type,
		काष्ठा tपंचांग_placement *placement,
		uपूर्णांक32_t page_alignment,
		bool पूर्णांकerruptible,
		काष्ठा sg_table *sg,
		काष्ठा dma_resv *resv,
		व्योम (*destroy) (काष्ठा tपंचांग_buffer_object *))
अणु
	काष्ठा tपंचांग_operation_ctx ctx = अणु पूर्णांकerruptible, false पूर्ण;
	पूर्णांक ret;

	ret = tपंचांग_bo_init_reserved(bdev, bo, size, type, placement,
				   page_alignment, &ctx, sg, resv, destroy);
	अगर (ret)
		वापस ret;

	अगर (!resv)
		tपंचांग_bo_unreserve(bo);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_init);

/*
 * buffer object vm functions.
 */

व्योम tपंचांग_bo_unmap_भव(काष्ठा tपंचांग_buffer_object *bo)
अणु
	काष्ठा tपंचांग_device *bdev = bo->bdev;

	drm_vma_node_unmap(&bo->base.vma_node, bdev->dev_mapping);
	tपंचांग_mem_io_मुक्त(bdev, &bo->mem);
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_unmap_भव);

पूर्णांक tपंचांग_bo_रुको(काष्ठा tपंचांग_buffer_object *bo,
		bool पूर्णांकerruptible, bool no_रुको)
अणु
	दीर्घ समयout = 15 * HZ;

	अगर (no_रुको) अणु
		अगर (dma_resv_test_संकेतed_rcu(bo->base.resv, true))
			वापस 0;
		अन्यथा
			वापस -EBUSY;
	पूर्ण

	समयout = dma_resv_रुको_समयout_rcu(bo->base.resv, true,
						      पूर्णांकerruptible, समयout);
	अगर (समयout < 0)
		वापस समयout;

	अगर (समयout == 0)
		वापस -EBUSY;

	dma_resv_add_excl_fence(bo->base.resv, शून्य);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(tपंचांग_bo_रुको);

पूर्णांक tपंचांग_bo_swapout(काष्ठा tपंचांग_buffer_object *bo, काष्ठा tपंचांग_operation_ctx *ctx,
		   gfp_t gfp_flags)
अणु
	bool locked;
	पूर्णांक ret;

	अगर (!tपंचांग_bo_evict_swapout_allowable(bo, ctx, &locked, शून्य))
		वापस -EBUSY;

	अगर (!bo->tपंचांग || !tपंचांग_tt_is_populated(bo->tपंचांग) ||
	    bo->tपंचांग->page_flags & TTM_PAGE_FLAG_SG ||
	    bo->tपंचांग->page_flags & TTM_PAGE_FLAG_SWAPPED ||
	    !tपंचांग_bo_get_unless_zero(bo)) अणु
		अगर (locked)
			dma_resv_unlock(bo->base.resv);
		वापस -EBUSY;
	पूर्ण

	अगर (bo->deleted) अणु
		tपंचांग_bo_cleanup_refs(bo, false, false, locked);
		tपंचांग_bo_put(bo);
		वापस 0;
	पूर्ण

	tपंचांग_bo_del_from_lru(bo);
	/* TODO: Cleanup the locking */
	spin_unlock(&bo->bdev->lru_lock);

	/*
	 * Move to प्रणाली cached
	 */
	अगर (bo->mem.mem_type != TTM_PL_SYSTEM) अणु
		काष्ठा tपंचांग_operation_ctx ctx = अणु false, false पूर्ण;
		काष्ठा tपंचांग_resource evict_mem;
		काष्ठा tपंचांग_place hop;

		स_रखो(&hop, 0, माप(hop));

		evict_mem = bo->mem;
		evict_mem.mm_node = शून्य;
		evict_mem.placement = 0;
		evict_mem.mem_type = TTM_PL_SYSTEM;

		ret = tपंचांग_bo_handle_move_mem(bo, &evict_mem, true, &ctx, &hop);
		अगर (unlikely(ret != 0)) अणु
			WARN(ret == -EMULTIHOP, "Unexpected multihop in swaput - likely driver bug.\n");
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * Make sure BO is idle.
	 */
	ret = tपंचांग_bo_रुको(bo, false, false);
	अगर (unlikely(ret != 0))
		जाओ out;

	tपंचांग_bo_unmap_भव(bo);

	/*
	 * Swap out. Buffer will be swapped in again as soon as
	 * anyone tries to access a tपंचांग page.
	 */
	अगर (bo->bdev->funcs->swap_notअगरy)
		bo->bdev->funcs->swap_notअगरy(bo);

	ret = tपंचांग_tt_swapout(bo->bdev, bo->tपंचांग, gfp_flags);
out:

	/*
	 * Unreserve without putting on LRU to aव्योम swapping out an
	 * alपढ़ोy swapped buffer.
	 */
	अगर (locked)
		dma_resv_unlock(bo->base.resv);
	tपंचांग_bo_put(bo);
	वापस ret;
पूर्ण

व्योम tपंचांग_bo_tt_destroy(काष्ठा tपंचांग_buffer_object *bo)
अणु
	अगर (bo->tपंचांग == शून्य)
		वापस;

	tपंचांग_tt_destroy(bo->bdev, bo->tपंचांग);
	bo->tपंचांग = शून्य;
पूर्ण
