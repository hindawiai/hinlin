<शैली गुरु>
/*
 * Copyright 2014 Canonical
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
 * Authors: Andreas Pokorny
 */

#समावेश "qxl_drv.h"
#समावेश "qxl_object.h"

/* Empty Implementations as there should not be any other driver क्रम a भव
 * device that might share buffers with qxl */

पूर्णांक qxl_gem_prime_pin(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा qxl_bo *bo = gem_to_qxl_bo(obj);

	वापस qxl_bo_pin(bo);
पूर्ण

व्योम qxl_gem_prime_unpin(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा qxl_bo *bo = gem_to_qxl_bo(obj);

	qxl_bo_unpin(bo);
पूर्ण

काष्ठा sg_table *qxl_gem_prime_get_sg_table(काष्ठा drm_gem_object *obj)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

काष्ठा drm_gem_object *qxl_gem_prime_import_sg_table(
	काष्ठा drm_device *dev, काष्ठा dma_buf_attachment *attach,
	काष्ठा sg_table *table)
अणु
	वापस ERR_PTR(-ENOSYS);
पूर्ण

पूर्णांक qxl_gem_prime_vmap(काष्ठा drm_gem_object *obj, काष्ठा dma_buf_map *map)
अणु
	काष्ठा qxl_bo *bo = gem_to_qxl_bo(obj);
	पूर्णांक ret;

	ret = qxl_bo_vmap(bo, map);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

व्योम qxl_gem_prime_vunmap(काष्ठा drm_gem_object *obj,
			  काष्ठा dma_buf_map *map)
अणु
	काष्ठा qxl_bo *bo = gem_to_qxl_bo(obj);

	qxl_bo_vunmap(bo);
पूर्ण

पूर्णांक qxl_gem_prime_mmap(काष्ठा drm_gem_object *obj,
		       काष्ठा vm_area_काष्ठा *area)
अणु
	वापस -ENOSYS;
पूर्ण
