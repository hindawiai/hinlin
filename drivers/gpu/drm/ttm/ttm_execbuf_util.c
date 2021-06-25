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

#समावेश <drm/tपंचांग/tपंचांग_execbuf_util.h>
#समावेश <drm/tपंचांग/tपंचांग_bo_driver.h>
#समावेश <drm/tपंचांग/tपंचांग_placement.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>
#समावेश <linux/module.h>

अटल व्योम tपंचांग_eu_backoff_reservation_reverse(काष्ठा list_head *list,
					      काष्ठा tपंचांग_validate_buffer *entry)
अणु
	list_क्रम_each_entry_जारी_reverse(entry, list, head) अणु
		काष्ठा tपंचांग_buffer_object *bo = entry->bo;

		dma_resv_unlock(bo->base.resv);
	पूर्ण
पूर्ण

व्योम tपंचांग_eu_backoff_reservation(काष्ठा ww_acquire_ctx *ticket,
				काष्ठा list_head *list)
अणु
	काष्ठा tपंचांग_validate_buffer *entry;

	अगर (list_empty(list))
		वापस;

	list_क्रम_each_entry(entry, list, head) अणु
		काष्ठा tपंचांग_buffer_object *bo = entry->bo;

		tपंचांग_bo_move_to_lru_tail_unlocked(bo);
		dma_resv_unlock(bo->base.resv);
	पूर्ण

	अगर (ticket)
		ww_acquire_fini(ticket);
पूर्ण
EXPORT_SYMBOL(tपंचांग_eu_backoff_reservation);

/*
 * Reserve buffers क्रम validation.
 *
 * If a buffer in the list is marked क्रम CPU access, we back off and
 * रुको क्रम that buffer to become मुक्त क्रम GPU access.
 *
 * If a buffer is reserved क्रम another validation, the validator with
 * the highest validation sequence backs off and रुकोs क्रम that buffer
 * to become unreserved. This prevents deadlocks when validating multiple
 * buffers in dअगरferent orders.
 */

पूर्णांक tपंचांग_eu_reserve_buffers(काष्ठा ww_acquire_ctx *ticket,
			   काष्ठा list_head *list, bool पूर्णांकr,
			   काष्ठा list_head *dups)
अणु
	काष्ठा tपंचांग_validate_buffer *entry;
	पूर्णांक ret;

	अगर (list_empty(list))
		वापस 0;

	अगर (ticket)
		ww_acquire_init(ticket, &reservation_ww_class);

	list_क्रम_each_entry(entry, list, head) अणु
		काष्ठा tपंचांग_buffer_object *bo = entry->bo;

		ret = tपंचांग_bo_reserve(bo, पूर्णांकr, (ticket == शून्य), ticket);
		अगर (ret == -EALREADY && dups) अणु
			काष्ठा tपंचांग_validate_buffer *safe = entry;
			entry = list_prev_entry(entry, head);
			list_del(&safe->head);
			list_add(&safe->head, dups);
			जारी;
		पूर्ण

		अगर (!ret) अणु
			अगर (!entry->num_shared)
				जारी;

			ret = dma_resv_reserve_shared(bo->base.resv,
								entry->num_shared);
			अगर (!ret)
				जारी;
		पूर्ण

		/* uh oh, we lost out, drop every reservation and try
		 * to only reserve this buffer, then start over अगर
		 * this succeeds.
		 */
		tपंचांग_eu_backoff_reservation_reverse(list, entry);

		अगर (ret == -EDEADLK) अणु
			ret = tपंचांग_bo_reserve_slowpath(bo, पूर्णांकr, ticket);
		पूर्ण

		अगर (!ret && entry->num_shared)
			ret = dma_resv_reserve_shared(bo->base.resv,
								entry->num_shared);

		अगर (unlikely(ret != 0)) अणु
			अगर (ticket) अणु
				ww_acquire_करोne(ticket);
				ww_acquire_fini(ticket);
			पूर्ण
			वापस ret;
		पूर्ण

		/* move this item to the front of the list,
		 * क्रमces correct iteration of the loop without keeping track
		 */
		list_del(&entry->head);
		list_add(&entry->head, list);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(tपंचांग_eu_reserve_buffers);

व्योम tपंचांग_eu_fence_buffer_objects(काष्ठा ww_acquire_ctx *ticket,
				 काष्ठा list_head *list,
				 काष्ठा dma_fence *fence)
अणु
	काष्ठा tपंचांग_validate_buffer *entry;

	अगर (list_empty(list))
		वापस;

	list_क्रम_each_entry(entry, list, head) अणु
		काष्ठा tपंचांग_buffer_object *bo = entry->bo;

		अगर (entry->num_shared)
			dma_resv_add_shared_fence(bo->base.resv, fence);
		अन्यथा
			dma_resv_add_excl_fence(bo->base.resv, fence);
		tपंचांग_bo_move_to_lru_tail_unlocked(bo);
		dma_resv_unlock(bo->base.resv);
	पूर्ण
	अगर (ticket)
		ww_acquire_fini(ticket);
पूर्ण
EXPORT_SYMBOL(tपंचांग_eu_fence_buffer_objects);
