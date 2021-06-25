<शैली गुरु>
/*
 * Copyright 2011 Red Hat Inc.
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
 */

#समावेश <linux/dma-buf.h>

#समावेश "nouveau_drv.h"
#समावेश "nouveau_gem.h"

काष्ठा sg_table *nouveau_gem_prime_get_sg_table(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा nouveau_bo *nvbo = nouveau_gem_object(obj);

	वापस drm_prime_pages_to_sg(obj->dev, nvbo->bo.tपंचांग->pages,
				     nvbo->bo.tपंचांग->num_pages);
पूर्ण

काष्ठा drm_gem_object *nouveau_gem_prime_import_sg_table(काष्ठा drm_device *dev,
							 काष्ठा dma_buf_attachment *attach,
							 काष्ठा sg_table *sg)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	काष्ठा drm_gem_object *obj;
	काष्ठा nouveau_bo *nvbo;
	काष्ठा dma_resv *robj = attach->dmabuf->resv;
	u64 size = attach->dmabuf->size;
	पूर्णांक align = 0;
	पूर्णांक ret;

	dma_resv_lock(robj, शून्य);
	nvbo = nouveau_bo_alloc(&drm->client, &size, &align,
				NOUVEAU_GEM_DOMAIN_GART, 0, 0);
	अगर (IS_ERR(nvbo)) अणु
		obj = ERR_CAST(nvbo);
		जाओ unlock;
	पूर्ण

	nvbo->valid_करोमुख्यs = NOUVEAU_GEM_DOMAIN_GART;

	nvbo->bo.base.funcs = &nouveau_gem_object_funcs;

	/* Initialize the embedded gem-object. We वापस a single gem-reference
	 * to the caller, instead of a normal nouveau_bo tपंचांग reference. */
	ret = drm_gem_object_init(dev, &nvbo->bo.base, size);
	अगर (ret) अणु
		nouveau_bo_ref(शून्य, &nvbo);
		obj = ERR_PTR(-ENOMEM);
		जाओ unlock;
	पूर्ण

	ret = nouveau_bo_init(nvbo, size, align, NOUVEAU_GEM_DOMAIN_GART,
			      sg, robj);
	अगर (ret) अणु
		nouveau_bo_ref(शून्य, &nvbo);
		obj = ERR_PTR(ret);
		जाओ unlock;
	पूर्ण

	obj = &nvbo->bo.base;

unlock:
	dma_resv_unlock(robj);
	वापस obj;
पूर्ण

पूर्णांक nouveau_gem_prime_pin(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा nouveau_bo *nvbo = nouveau_gem_object(obj);
	पूर्णांक ret;

	/* pin buffer पूर्णांकo GTT */
	ret = nouveau_bo_pin(nvbo, NOUVEAU_GEM_DOMAIN_GART, false);
	अगर (ret)
		वापस -EINVAL;

	वापस 0;
पूर्ण

व्योम nouveau_gem_prime_unpin(काष्ठा drm_gem_object *obj)
अणु
	काष्ठा nouveau_bo *nvbo = nouveau_gem_object(obj);

	nouveau_bo_unpin(nvbo);
पूर्ण
