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

/**
 * DOC: MMU Notअगरier
 *
 * For coherent userptr handling रेजिस्टरs an MMU notअगरier to inक्रमm the driver
 * about updates on the page tables of a process.
 *
 * When somebody tries to invalidate the page tables we block the update until
 * all operations on the pages in question are completed, then those pages are
 * marked as accessed and also dirty अगर it wasn't a पढ़ो only access.
 *
 * New command submissions using the userptrs in question are delayed until all
 * page table invalidation are completed and we once more see a coherent process
 * address space.
 */

#समावेश <linux/firmware.h>
#समावेश <linux/module.h>
#समावेश <drm/drm.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_amdkfd.h"

/**
 * amdgpu_mn_invalidate_gfx - callback to notअगरy about mm change
 *
 * @mni: the range (mm) is about to update
 * @range: details on the invalidation
 * @cur_seq: Value to pass to mmu_पूर्णांकerval_set_seq()
 *
 * Block क्रम operations on BOs to finish and mark pages as accessed and
 * potentially dirty.
 */
अटल bool amdgpu_mn_invalidate_gfx(काष्ठा mmu_पूर्णांकerval_notअगरier *mni,
				     स्थिर काष्ठा mmu_notअगरier_range *range,
				     अचिन्हित दीर्घ cur_seq)
अणु
	काष्ठा amdgpu_bo *bo = container_of(mni, काष्ठा amdgpu_bo, notअगरier);
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);
	दीर्घ r;

	अगर (!mmu_notअगरier_range_blockable(range))
		वापस false;

	mutex_lock(&adev->notअगरier_lock);

	mmu_पूर्णांकerval_set_seq(mni, cur_seq);

	r = dma_resv_रुको_समयout_rcu(bo->tbo.base.resv, true, false,
				      MAX_SCHEDULE_TIMEOUT);
	mutex_unlock(&adev->notअगरier_lock);
	अगर (r <= 0)
		DRM_ERROR("(%ld) failed to wait for user bo\n", r);
	वापस true;
पूर्ण

अटल स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops amdgpu_mn_gfx_ops = अणु
	.invalidate = amdgpu_mn_invalidate_gfx,
पूर्ण;

/**
 * amdgpu_mn_invalidate_hsa - callback to notअगरy about mm change
 *
 * @mni: the range (mm) is about to update
 * @range: details on the invalidation
 * @cur_seq: Value to pass to mmu_पूर्णांकerval_set_seq()
 *
 * We temporarily evict the BO attached to this range. This necessitates
 * evicting all user-mode queues of the process.
 */
अटल bool amdgpu_mn_invalidate_hsa(काष्ठा mmu_पूर्णांकerval_notअगरier *mni,
				     स्थिर काष्ठा mmu_notअगरier_range *range,
				     अचिन्हित दीर्घ cur_seq)
अणु
	काष्ठा amdgpu_bo *bo = container_of(mni, काष्ठा amdgpu_bo, notअगरier);
	काष्ठा amdgpu_device *adev = amdgpu_tपंचांग_adev(bo->tbo.bdev);

	अगर (!mmu_notअगरier_range_blockable(range))
		वापस false;

	mutex_lock(&adev->notअगरier_lock);

	mmu_पूर्णांकerval_set_seq(mni, cur_seq);

	amdgpu_amdkfd_evict_userptr(bo->kfd_bo, bo->notअगरier.mm);
	mutex_unlock(&adev->notअगरier_lock);

	वापस true;
पूर्ण

अटल स्थिर काष्ठा mmu_पूर्णांकerval_notअगरier_ops amdgpu_mn_hsa_ops = अणु
	.invalidate = amdgpu_mn_invalidate_hsa,
पूर्ण;

/**
 * amdgpu_mn_रेजिस्टर - रेजिस्टर a BO क्रम notअगरier updates
 *
 * @bo: amdgpu buffer object
 * @addr: userptr addr we should monitor
 *
 * Registers a mmu_notअगरier क्रम the given BO at the specअगरied address.
 * Returns 0 on success, -ERRNO अगर anything goes wrong.
 */
पूर्णांक amdgpu_mn_रेजिस्टर(काष्ठा amdgpu_bo *bo, अचिन्हित दीर्घ addr)
अणु
	अगर (bo->kfd_bo)
		वापस mmu_पूर्णांकerval_notअगरier_insert(&bo->notअगरier, current->mm,
						    addr, amdgpu_bo_size(bo),
						    &amdgpu_mn_hsa_ops);
	वापस mmu_पूर्णांकerval_notअगरier_insert(&bo->notअगरier, current->mm, addr,
					    amdgpu_bo_size(bo),
					    &amdgpu_mn_gfx_ops);
पूर्ण

/**
 * amdgpu_mn_unरेजिस्टर - unरेजिस्टर a BO क्रम notअगरier updates
 *
 * @bo: amdgpu buffer object
 *
 * Remove any registration of mmu notअगरier updates from the buffer object.
 */
व्योम amdgpu_mn_unरेजिस्टर(काष्ठा amdgpu_bo *bo)
अणु
	अगर (!bo->notअगरier.mm)
		वापस;
	mmu_पूर्णांकerval_notअगरier_हटाओ(&bo->notअगरier);
	bo->notअगरier.mm = शून्य;
पूर्ण
