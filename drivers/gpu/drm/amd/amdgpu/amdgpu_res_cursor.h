<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
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

#अगर_अघोषित __AMDGPU_RES_CURSOR_H__
#घोषणा __AMDGPU_RES_CURSOR_H__

#समावेश <drm/drm_mm.h>
#समावेश <drm/tपंचांग/tपंचांग_resource.h>

/* state back क्रम walking over vram_mgr and gtt_mgr allocations */
काष्ठा amdgpu_res_cursor अणु
	uपूर्णांक64_t		start;
	uपूर्णांक64_t		size;
	uपूर्णांक64_t		reमुख्यing;
	काष्ठा drm_mm_node	*node;
पूर्ण;

/**
 * amdgpu_res_first - initialize a amdgpu_res_cursor
 *
 * @res: TTM resource object to walk
 * @start: Start of the range
 * @size: Size of the range
 * @cur: cursor object to initialize
 *
 * Start walking over the range of allocations between @start and @size.
 */
अटल अंतरभूत व्योम amdgpu_res_first(काष्ठा tपंचांग_resource *res,
				    uपूर्णांक64_t start, uपूर्णांक64_t size,
				    काष्ठा amdgpu_res_cursor *cur)
अणु
	काष्ठा drm_mm_node *node;

	अगर (!res || !res->mm_node) अणु
		cur->start = start;
		cur->size = size;
		cur->reमुख्यing = size;
		cur->node = शून्य;
		वापस;
	पूर्ण

	BUG_ON(start + size > res->num_pages << PAGE_SHIFT);

	node = res->mm_node;
	जबतक (start >= node->size << PAGE_SHIFT)
		start -= node++->size << PAGE_SHIFT;

	cur->start = (node->start << PAGE_SHIFT) + start;
	cur->size = min((node->size << PAGE_SHIFT) - start, size);
	cur->reमुख्यing = size;
	cur->node = node;
पूर्ण

/**
 * amdgpu_res_next - advance the cursor
 *
 * @cur: the cursor to advance
 * @size: number of bytes to move क्रमward
 *
 * Move the cursor @size bytes क्रमwrad, walking to the next node अगर necessary.
 */
अटल अंतरभूत व्योम amdgpu_res_next(काष्ठा amdgpu_res_cursor *cur, uपूर्णांक64_t size)
अणु
	काष्ठा drm_mm_node *node = cur->node;

	BUG_ON(size > cur->reमुख्यing);

	cur->reमुख्यing -= size;
	अगर (!cur->reमुख्यing)
		वापस;

	cur->size -= size;
	अगर (cur->size) अणु
		cur->start += size;
		वापस;
	पूर्ण

	cur->node = ++node;
	cur->start = node->start << PAGE_SHIFT;
	cur->size = min(node->size << PAGE_SHIFT, cur->reमुख्यing);
पूर्ण

#पूर्ण_अगर
