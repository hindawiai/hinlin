<शैली गुरु>
/*
 * Copyright 2012 Advanced Micro Devices, Inc.
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
 * based on nouveau_prime.c
 *
 * Authors: Alex Deucher
 */

#समावेश <linux/dma-buf.h>

#समावेश <drm/drm_prime.h>
#समावेश <drm/radeon_drm.h>

#समावेश "radeon.h"
#समावेश "radeon_prime.h"

काष्ठा sg_table *radeon_gem_prime_get_sg_table(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा radeon_bo *bo = gem_to_radeon_bo(obj);

	वापस drm_prime_pages_to_sg(obj->dev, bo->tbo.tपंचांग->pages,
				     bo->tbo.tपंचांग->num_pages);
पूर्ण

काष्ठा drm_gem_object *radeon_gem_prime_import_sg_table(काष्ठा drm_device *dev,
							काष्ठा dma_buf_attachment *attach,
							काष्ठा sg_table *sg)
अणु
	काष्ठा dma_resv *resv = attach->dmabuf->resv;
	काष्ठा radeon_device *rdev = dev->dev_निजी;
	काष्ठा radeon_bo *bo;
	पूर्णांक ret;

	dma_resv_lock(resv, शून्य);
	ret = radeon_bo_create(rdev, attach->dmabuf->size, PAGE_SIZE, false,
			       RADEON_GEM_DOMAIN_GTT, 0, sg, resv, &bo);
	dma_resv_unlock(resv);
	अगर (ret)
		वापस ERR_PTR(ret);

	bo->tbo.base.funcs = &radeon_gem_object_funcs;

	mutex_lock(&rdev->gem.mutex);
	list_add_tail(&bo->list, &rdev->gem.objects);
	mutex_unlock(&rdev->gem.mutex);

	bo->prime_shared_count = 1;
	वापस &bo->tbo.base;
पूर्ण

पूर्णांक radeon_gem_prime_pin(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा radeon_bo *bo = gem_to_radeon_bo(obj);
	पूर्णांक ret = 0;

	ret = radeon_bo_reserve(bo, false);
	अगर (unlikely(ret != 0))
		वापस ret;

	/* pin buffer पूर्णांकo GTT */
	ret = radeon_bo_pin(bo, RADEON_GEM_DOMAIN_GTT, शून्य);
	अगर (likely(ret == 0))
		bo->prime_shared_count++;

	radeon_bo_unreserve(bo);
	वापस ret;
पूर्ण

व्योम radeon_gem_prime_unpin(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा radeon_bo *bo = gem_to_radeon_bo(obj);
	पूर्णांक ret = 0;

	ret = radeon_bo_reserve(bo, false);
	अगर (unlikely(ret != 0))
		वापस;

	radeon_bo_unpin(bo);
	अगर (bo->prime_shared_count)
		bo->prime_shared_count--;
	radeon_bo_unreserve(bo);
पूर्ण


काष्ठा dma_buf *radeon_gem_prime_export(काष्ठा drm_gem_object *gobj,
					पूर्णांक flags)
अणु
	काष्ठा radeon_bo *bo = gem_to_radeon_bo(gobj);
	अगर (radeon_tपंचांग_tt_has_userptr(bo->rdev, bo->tbo.tपंचांग))
		वापस ERR_PTR(-EPERM);
	वापस drm_gem_prime_export(gobj, flags);
पूर्ण
