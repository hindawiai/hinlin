<शैली गुरु>
/*
 * Copyright 2013 Red Hat Inc.
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
 * Authors: Dave Airlie
 *          Alon Levy
 */
#अगर_अघोषित QXL_OBJECT_H
#घोषणा QXL_OBJECT_H

#समावेश "qxl_drv.h"

अटल अंतरभूत पूर्णांक qxl_bo_reserve(काष्ठा qxl_bo *bo)
अणु
	पूर्णांक r;

	r = tपंचांग_bo_reserve(&bo->tbo, true, false, शून्य);
	अगर (unlikely(r != 0)) अणु
		अगर (r != -ERESTARTSYS) अणु
			काष्ठा drm_device *ddev = bo->tbo.base.dev;

			dev_err(ddev->dev, "%p reserve failed\n", bo);
		पूर्ण
		वापस r;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम qxl_bo_unreserve(काष्ठा qxl_bo *bo)
अणु
	tपंचांग_bo_unreserve(&bo->tbo);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ qxl_bo_size(काष्ठा qxl_bo *bo)
अणु
	वापस bo->tbo.base.size;
पूर्ण

अटल अंतरभूत u64 qxl_bo_mmap_offset(काष्ठा qxl_bo *bo)
अणु
	वापस drm_vma_node_offset_addr(&bo->tbo.base.vma_node);
पूर्ण

बाह्य पूर्णांक qxl_bo_create(काष्ठा qxl_device *qdev,
			 अचिन्हित दीर्घ size,
			 bool kernel, bool pinned, u32 करोमुख्य,
			 u32 priority,
			 काष्ठा qxl_surface *surf,
			 काष्ठा qxl_bo **bo_ptr);
पूर्णांक qxl_bo_vmap(काष्ठा qxl_bo *bo, काष्ठा dma_buf_map *map);
पूर्णांक qxl_bo_vmap_locked(काष्ठा qxl_bo *bo, काष्ठा dma_buf_map *map);
पूर्णांक qxl_bo_vunmap(काष्ठा qxl_bo *bo);
व्योम qxl_bo_vunmap_locked(काष्ठा qxl_bo *bo);
व्योम *qxl_bo_kmap_atomic_page(काष्ठा qxl_device *qdev, काष्ठा qxl_bo *bo, पूर्णांक page_offset);
व्योम qxl_bo_kunmap_atomic_page(काष्ठा qxl_device *qdev, काष्ठा qxl_bo *bo, व्योम *map);
बाह्य काष्ठा qxl_bo *qxl_bo_ref(काष्ठा qxl_bo *bo);
बाह्य व्योम qxl_bo_unref(काष्ठा qxl_bo **bo);
बाह्य पूर्णांक qxl_bo_pin(काष्ठा qxl_bo *bo);
बाह्य पूर्णांक qxl_bo_unpin(काष्ठा qxl_bo *bo);
बाह्य व्योम qxl_tपंचांग_placement_from_करोमुख्य(काष्ठा qxl_bo *qbo, u32 करोमुख्य);
बाह्य bool qxl_tपंचांग_bo_is_qxl_bo(काष्ठा tपंचांग_buffer_object *bo);

#पूर्ण_अगर
