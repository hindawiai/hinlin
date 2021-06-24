<शैली गुरु>
/*
 *  sync fence merge tests
 *  Copyright 2015-2016 Collabora Ltd.
 *
 *  Based on the implementation from the Android Open Source Project,
 *
 *  Copyright 2012 Google, Inc
 *
 *  Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 *  copy of this software and associated करोcumentation files (the "Software"),
 *  to deal in the Software without restriction, including without limitation
 *  the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to करो so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *  OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश "sync.h"
#समावेश "sw_sync.h"
#समावेश "synctest.h"

पूर्णांक test_fence_merge_same_fence(व्योम)
अणु
	पूर्णांक fence, valid, merged;
	पूर्णांक समयline = sw_sync_समयline_create();

	valid = sw_sync_समयline_is_valid(समयline);
	ASSERT(valid, "Failure allocating timeline\n");

	fence = sw_sync_fence_create(समयline, "allocFence", 5);
	valid = sw_sync_fence_is_valid(fence);
	ASSERT(valid, "Failure allocating fence\n");

	merged = sync_merge("mergeFence", fence, fence);
	valid = sw_sync_fence_is_valid(fence);
	ASSERT(valid, "Failure merging fence\n");

	ASSERT(sync_fence_count_with_status(merged, FENCE_STATUS_SIGNALED) == 0,
	       "fence signaled too early!\n");

	sw_sync_समयline_inc(समयline, 5);
	ASSERT(sync_fence_count_with_status(merged, FENCE_STATUS_SIGNALED) == 1,
	       "fence did not signal!\n");

	sw_sync_fence_destroy(merged);
	sw_sync_fence_destroy(fence);
	sw_sync_समयline_destroy(समयline);

	वापस 0;
पूर्ण
