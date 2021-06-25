<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 */
/*
 * Authors:
 *    Christian Kथघnig <christian.koenig@amd.com>
 */

#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <linux/mmu_notअगरier.h>

#समावेश <drm/drm.h>

#समावेश "radeon.h"

/**
 * radeon_mn_invalidate - callback to notअगरy about mm change
 *
 * @mn: our notअगरier
 * @range: the VMA under invalidation
 * @cur_seq: Value to pass to mmu_पूर्णांकerval_set_seq()
 *
 * We block क्रम all BOs between start and end to be idle and
 * unmap them by move them पूर्णांकo प्रणाली करोमुख्य again.
 */
अटल bool radeon_mn_invalidate(काष्ठा mmu_पूर्णांकerval_notअगरier *mn,
				 स्थिर काष्ठा mmu_notअगरier_range *range,
				 अचिन्हित दीर्घ cur_seq)
अणु
	काष्ठा radeon_bo *bo = container_of(mn, काष्ठा radeon_bo, notअगरier);
	काष्ठा tपंचांग_operation_ctx ctx = अणु false, false पूर्ण;
	दीर्घ r;

	अगर (!bo->tbo.tपंचांग || !radeon_tपंचांग_tt_is_bound(bo->tbo.bdev, bo->tbo.tपंचांग))
		वापस true;

	अगर (!mmu_notअगरier_range_blockable(range))
		वापस false;

	r = radeon_bo_reserve(bo, true);
	अगर (r) अणु
		DRM_ERROR("(%ld) failed to reserve user bo\n", r);
		वापस true;
	पूर्ण

	r = dma_resv_रुको_समयout_rcu(bo->tbo.base.resv, true, false,
				      MAX_SCHEDULE_TIMEOUT);
	अगर (r <= 0)
		DRM_ERROR("(%ld) failed to wait for user bo\n", r);

	radeon_tपंचांग_placement_from_करोमुख्य(bo, RADEON_GEM_DOMAIN_CPU);
	r = tपंचांग_bo_validate(&bo->tbo, &bo->placement, &ctx);
	अगर (r)
		DRM_ERROR("(%ld) failed to validate user bo\n", r);

	radeon_bo_unreserve(bo);
	वापस true;
पूर्ण

अटल स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops radeon_mn_ops = अणु
	.invalidate = radeon_mn_invalidate,
पूर्ण;

/**
 * radeon_mn_रेजिस्टर - रेजिस्टर a BO क्रम notअगरier updates
 *
 * @bo: radeon buffer object
 * @addr: userptr addr we should monitor
 *
 * Registers an MMU notअगरier क्रम the given BO at the specअगरied address.
 * Returns 0 on success, -ERRNO अगर anything goes wrong.
 */
पूर्णांक radeon_mn_रेजिस्टर(काष्ठा radeon_bo *bo, अचिन्हित दीर्घ addr)
अणु
	पूर्णांक ret;

	ret = mmu_पूर्णांकerval_notअगरier_insert(&bo->notअगरier, current->mm, addr,
					   radeon_bo_size(bo), &radeon_mn_ops);
	अगर (ret)
		वापस ret;

	/*
	 * FIXME: radeon appears to allow get_user_pages to run during
	 * invalidate_range_start/end, which is not a safe way to पढ़ो the
	 * PTEs. It should use the mmu_पूर्णांकerval_पढ़ो_begin() scheme around the
	 * get_user_pages to ensure that the PTEs are पढ़ो properly
	 */
	mmu_पूर्णांकerval_पढ़ो_begin(&bo->notअगरier);
	वापस 0;
पूर्ण

/**
 * radeon_mn_unरेजिस्टर - unरेजिस्टर a BO क्रम notअगरier updates
 *
 * @bo: radeon buffer object
 *
 * Remove any registration of MMU notअगरier updates from the buffer object.
 */
व्योम radeon_mn_unरेजिस्टर(काष्ठा radeon_bo *bo)
अणु
	अगर (!bo->notअगरier.mm)
		वापस;
	mmu_पूर्णांकerval_notअगरier_हटाओ(&bo->notअगरier);
	bo->notअगरier.mm = शून्य;
पूर्ण
