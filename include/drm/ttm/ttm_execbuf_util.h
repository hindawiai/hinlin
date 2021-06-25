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

#अगर_अघोषित _TTM_EXECBUF_UTIL_H_
#घोषणा _TTM_EXECBUF_UTIL_H_

#समावेश <linux/list.h>

#समावेश "ttm_bo_api.h"

/**
 * काष्ठा tपंचांग_validate_buffer
 *
 * @head:           list head क्रम thपढ़ो-निजी list.
 * @bo:             refcounted buffer object poपूर्णांकer.
 * @num_shared:     How many shared fences we want to add.
 */

काष्ठा tपंचांग_validate_buffer अणु
	काष्ठा list_head head;
	काष्ठा tपंचांग_buffer_object *bo;
	अचिन्हित पूर्णांक num_shared;
पूर्ण;

/**
 * function tपंचांग_eu_backoff_reservation
 *
 * @ticket:   ww_acquire_ctx from reserve call
 * @list:     thपढ़ो निजी list of tपंचांग_validate_buffer काष्ठाs.
 *
 * Unकरोes all buffer validation reservations क्रम bos poपूर्णांकed to by
 * the list entries.
 */
व्योम tपंचांग_eu_backoff_reservation(काष्ठा ww_acquire_ctx *ticket,
				काष्ठा list_head *list);

/**
 * function tपंचांग_eu_reserve_buffers
 *
 * @ticket:  [out] ww_acquire_ctx filled in by call, or शून्य अगर only
 *           non-blocking reserves should be tried.
 * @list:    thपढ़ो निजी list of tपंचांग_validate_buffer काष्ठाs.
 * @पूर्णांकr:    should the रुको be पूर्णांकerruptible
 * @dups:    [out] optional list of duplicates.
 * @del_lru: true अगर BOs should be हटाओd from the LRU.
 *
 * Tries to reserve bos poपूर्णांकed to by the list entries क्रम validation.
 * If the function वापसs 0, all buffers are marked as "unfenced",
 * taken off the lru lists and are not synced क्रम ग_लिखो CPU usage.
 *
 * If the function detects a deadlock due to multiple thपढ़ोs trying to
 * reserve the same buffers in reverse order, all thपढ़ोs except one will
 * back off and retry. This function may sleep जबतक रुकोing क्रम
 * CPU ग_लिखो reservations to be cleared, and क्रम other thपढ़ोs to
 * unreserve their buffers.
 *
 * If पूर्णांकr is set to true, this function may वापस -ERESTARTSYS अगर the
 * calling process receives a संकेत जबतक रुकोing. In that हाल, no
 * buffers on the list will be reserved upon वापस.
 *
 * If dups is non शून्य all buffers alपढ़ोy reserved by the current thपढ़ो
 * (e.g. duplicates) are added to this list, otherwise -EALREADY is वापसed
 * on the first alपढ़ोy reserved buffer and all buffers from the list are
 * unreserved again.
 *
 * Buffers reserved by this function should be unreserved by
 * a call to either tपंचांग_eu_backoff_reservation() or
 * tपंचांग_eu_fence_buffer_objects() when command submission is complete or
 * has failed.
 */
पूर्णांक tपंचांग_eu_reserve_buffers(काष्ठा ww_acquire_ctx *ticket,
			   काष्ठा list_head *list, bool पूर्णांकr,
			   काष्ठा list_head *dups);

/**
 * function tपंचांग_eu_fence_buffer_objects.
 *
 * @ticket:      ww_acquire_ctx from reserve call
 * @list:        thपढ़ो निजी list of tपंचांग_validate_buffer काष्ठाs.
 * @fence:       The new exclusive fence क्रम the buffers.
 *
 * This function should be called when command submission is complete, and
 * it will add a new sync object to bos poपूर्णांकed to by entries on @list.
 * It also unreserves all buffers, putting them on lru lists.
 *
 */
व्योम tपंचांग_eu_fence_buffer_objects(काष्ठा ww_acquire_ctx *ticket,
				 काष्ठा list_head *list,
				 काष्ठा dma_fence *fence);

#पूर्ण_अगर
