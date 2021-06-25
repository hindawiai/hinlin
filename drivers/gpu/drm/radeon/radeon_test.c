<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/*
 * Copyright 2009 VMware, Inc.
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
 * Authors: Michel Dथअnzer
 */

#समावेश <drm/radeon_drm.h>
#समावेश "radeon_reg.h"
#समावेश "radeon.h"

#घोषणा RADEON_TEST_COPY_BLIT 1
#घोषणा RADEON_TEST_COPY_DMA  0


/* Test BO GTT->VRAM and VRAM->GTT GPU copies across the whole GTT aperture */
अटल व्योम radeon_करो_test_moves(काष्ठा radeon_device *rdev, पूर्णांक flag)
अणु
	काष्ठा radeon_bo *vram_obj = शून्य;
	काष्ठा radeon_bo **gtt_obj = शून्य;
	uपूर्णांक64_t gtt_addr, vram_addr;
	अचिन्हित n, size;
	पूर्णांक i, r, ring;

	चयन (flag) अणु
	हाल RADEON_TEST_COPY_DMA:
		ring = radeon_copy_dma_ring_index(rdev);
		अवरोध;
	हाल RADEON_TEST_COPY_BLIT:
		ring = radeon_copy_blit_ring_index(rdev);
		अवरोध;
	शेष:
		DRM_ERROR("Unknown copy method\n");
		वापस;
	पूर्ण

	size = 1024 * 1024;

	/* Number of tests =
	 * (Total GTT - IB pool - ग_लिखोback page - ring buffers) / test size
	 */
	n = rdev->mc.gtt_size - rdev->gart_pin_size;
	n /= size;

	gtt_obj = kसुस्मृति(n, माप(*gtt_obj), GFP_KERNEL);
	अगर (!gtt_obj) अणु
		DRM_ERROR("Failed to allocate %d pointers\n", n);
		r = 1;
		जाओ out_cleanup;
	पूर्ण

	r = radeon_bo_create(rdev, size, PAGE_SIZE, true, RADEON_GEM_DOMAIN_VRAM,
			     0, शून्य, शून्य, &vram_obj);
	अगर (r) अणु
		DRM_ERROR("Failed to create VRAM object\n");
		जाओ out_cleanup;
	पूर्ण
	r = radeon_bo_reserve(vram_obj, false);
	अगर (unlikely(r != 0))
		जाओ out_unref;
	r = radeon_bo_pin(vram_obj, RADEON_GEM_DOMAIN_VRAM, &vram_addr);
	अगर (r) अणु
		DRM_ERROR("Failed to pin VRAM object\n");
		जाओ out_unres;
	पूर्ण
	क्रम (i = 0; i < n; i++) अणु
		व्योम *gtt_map, *vram_map;
		व्योम **gtt_start, **gtt_end;
		व्योम **vram_start, **vram_end;
		काष्ठा radeon_fence *fence = शून्य;

		r = radeon_bo_create(rdev, size, PAGE_SIZE, true,
				     RADEON_GEM_DOMAIN_GTT, 0, शून्य, शून्य,
				     gtt_obj + i);
		अगर (r) अणु
			DRM_ERROR("Failed to create GTT object %d\n", i);
			जाओ out_lclean;
		पूर्ण

		r = radeon_bo_reserve(gtt_obj[i], false);
		अगर (unlikely(r != 0))
			जाओ out_lclean_unref;
		r = radeon_bo_pin(gtt_obj[i], RADEON_GEM_DOMAIN_GTT, &gtt_addr);
		अगर (r) अणु
			DRM_ERROR("Failed to pin GTT object %d\n", i);
			जाओ out_lclean_unres;
		पूर्ण

		r = radeon_bo_kmap(gtt_obj[i], &gtt_map);
		अगर (r) अणु
			DRM_ERROR("Failed to map GTT object %d\n", i);
			जाओ out_lclean_unpin;
		पूर्ण

		क्रम (gtt_start = gtt_map, gtt_end = gtt_map + size;
		     gtt_start < gtt_end;
		     gtt_start++)
			*gtt_start = gtt_start;

		radeon_bo_kunmap(gtt_obj[i]);

		अगर (ring == R600_RING_TYPE_DMA_INDEX)
			fence = radeon_copy_dma(rdev, gtt_addr, vram_addr,
						size / RADEON_GPU_PAGE_SIZE,
						vram_obj->tbo.base.resv);
		अन्यथा
			fence = radeon_copy_blit(rdev, gtt_addr, vram_addr,
						 size / RADEON_GPU_PAGE_SIZE,
						 vram_obj->tbo.base.resv);
		अगर (IS_ERR(fence)) अणु
			DRM_ERROR("Failed GTT->VRAM copy %d\n", i);
			r = PTR_ERR(fence);
			जाओ out_lclean_unpin;
		पूर्ण

		r = radeon_fence_रुको(fence, false);
		अगर (r) अणु
			DRM_ERROR("Failed to wait for GTT->VRAM fence %d\n", i);
			जाओ out_lclean_unpin;
		पूर्ण

		radeon_fence_unref(&fence);

		r = radeon_bo_kmap(vram_obj, &vram_map);
		अगर (r) अणु
			DRM_ERROR("Failed to map VRAM object after copy %d\n", i);
			जाओ out_lclean_unpin;
		पूर्ण

		क्रम (gtt_start = gtt_map, gtt_end = gtt_map + size,
		     vram_start = vram_map, vram_end = vram_map + size;
		     vram_start < vram_end;
		     gtt_start++, vram_start++) अणु
			अगर (*vram_start != gtt_start) अणु
				DRM_ERROR("Incorrect GTT->VRAM copy %d: Got 0x%p, "
					  "expected 0x%p (GTT/VRAM offset "
					  "0x%16llx/0x%16llx)\n",
					  i, *vram_start, gtt_start,
					  (अचिन्हित दीर्घ दीर्घ)
					  (gtt_addr - rdev->mc.gtt_start +
					   (व्योम*)gtt_start - gtt_map),
					  (अचिन्हित दीर्घ दीर्घ)
					  (vram_addr - rdev->mc.vram_start +
					   (व्योम*)gtt_start - gtt_map));
				radeon_bo_kunmap(vram_obj);
				जाओ out_lclean_unpin;
			पूर्ण
			*vram_start = vram_start;
		पूर्ण

		radeon_bo_kunmap(vram_obj);

		अगर (ring == R600_RING_TYPE_DMA_INDEX)
			fence = radeon_copy_dma(rdev, vram_addr, gtt_addr,
						size / RADEON_GPU_PAGE_SIZE,
						vram_obj->tbo.base.resv);
		अन्यथा
			fence = radeon_copy_blit(rdev, vram_addr, gtt_addr,
						 size / RADEON_GPU_PAGE_SIZE,
						 vram_obj->tbo.base.resv);
		अगर (IS_ERR(fence)) अणु
			DRM_ERROR("Failed VRAM->GTT copy %d\n", i);
			r = PTR_ERR(fence);
			जाओ out_lclean_unpin;
		पूर्ण

		r = radeon_fence_रुको(fence, false);
		अगर (r) अणु
			DRM_ERROR("Failed to wait for VRAM->GTT fence %d\n", i);
			जाओ out_lclean_unpin;
		पूर्ण

		radeon_fence_unref(&fence);

		r = radeon_bo_kmap(gtt_obj[i], &gtt_map);
		अगर (r) अणु
			DRM_ERROR("Failed to map GTT object after copy %d\n", i);
			जाओ out_lclean_unpin;
		पूर्ण

		क्रम (gtt_start = gtt_map, gtt_end = gtt_map + size,
		     vram_start = vram_map, vram_end = vram_map + size;
		     gtt_start < gtt_end;
		     gtt_start++, vram_start++) अणु
			अगर (*gtt_start != vram_start) अणु
				DRM_ERROR("Incorrect VRAM->GTT copy %d: Got 0x%p, "
					  "expected 0x%p (VRAM/GTT offset "
					  "0x%16llx/0x%16llx)\n",
					  i, *gtt_start, vram_start,
					  (अचिन्हित दीर्घ दीर्घ)
					  (vram_addr - rdev->mc.vram_start +
					   (व्योम*)vram_start - vram_map),
					  (अचिन्हित दीर्घ दीर्घ)
					  (gtt_addr - rdev->mc.gtt_start +
					   (व्योम*)vram_start - vram_map));
				radeon_bo_kunmap(gtt_obj[i]);
				जाओ out_lclean_unpin;
			पूर्ण
		पूर्ण

		radeon_bo_kunmap(gtt_obj[i]);

		DRM_INFO("Tested GTT->VRAM and VRAM->GTT copy for GTT offset 0x%llx\n",
			 gtt_addr - rdev->mc.gtt_start);
		जारी;

out_lclean_unpin:
		radeon_bo_unpin(gtt_obj[i]);
out_lclean_unres:
		radeon_bo_unreserve(gtt_obj[i]);
out_lclean_unref:
		radeon_bo_unref(&gtt_obj[i]);
out_lclean:
		क्रम (--i; i >= 0; --i) अणु
			radeon_bo_unpin(gtt_obj[i]);
			radeon_bo_unreserve(gtt_obj[i]);
			radeon_bo_unref(&gtt_obj[i]);
		पूर्ण
		अगर (fence && !IS_ERR(fence))
			radeon_fence_unref(&fence);
		अवरोध;
	पूर्ण

	radeon_bo_unpin(vram_obj);
out_unres:
	radeon_bo_unreserve(vram_obj);
out_unref:
	radeon_bo_unref(&vram_obj);
out_cleanup:
	kमुक्त(gtt_obj);
	अगर (r) अणु
		pr_warn("Error while testing BO move\n");
	पूर्ण
पूर्ण

व्योम radeon_test_moves(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->asic->copy.dma)
		radeon_करो_test_moves(rdev, RADEON_TEST_COPY_DMA);
	अगर (rdev->asic->copy.blit)
		radeon_करो_test_moves(rdev, RADEON_TEST_COPY_BLIT);
पूर्ण

अटल पूर्णांक radeon_test_create_and_emit_fence(काष्ठा radeon_device *rdev,
					     काष्ठा radeon_ring *ring,
					     काष्ठा radeon_fence **fence)
अणु
	uपूर्णांक32_t handle = ring->idx ^ 0xdeafbeef;
	पूर्णांक r;

	अगर (ring->idx == R600_RING_TYPE_UVD_INDEX) अणु
		r = radeon_uvd_get_create_msg(rdev, ring->idx, handle, शून्य);
		अगर (r) अणु
			DRM_ERROR("Failed to get dummy create msg\n");
			वापस r;
		पूर्ण

		r = radeon_uvd_get_destroy_msg(rdev, ring->idx, handle, fence);
		अगर (r) अणु
			DRM_ERROR("Failed to get dummy destroy msg\n");
			वापस r;
		पूर्ण

	पूर्ण अन्यथा अगर (ring->idx == TN_RING_TYPE_VCE1_INDEX ||
		   ring->idx == TN_RING_TYPE_VCE2_INDEX) अणु
		r = radeon_vce_get_create_msg(rdev, ring->idx, handle, शून्य);
		अगर (r) अणु
			DRM_ERROR("Failed to get dummy create msg\n");
			वापस r;
		पूर्ण

		r = radeon_vce_get_destroy_msg(rdev, ring->idx, handle, fence);
		अगर (r) अणु
			DRM_ERROR("Failed to get dummy destroy msg\n");
			वापस r;
		पूर्ण

	पूर्ण अन्यथा अणु
		r = radeon_ring_lock(rdev, ring, 64);
		अगर (r) अणु
			DRM_ERROR("Failed to lock ring A %d\n", ring->idx);
			वापस r;
		पूर्ण
		r = radeon_fence_emit(rdev, fence, ring->idx);
		अगर (r) अणु
			DRM_ERROR("Failed to emit fence\n");
			radeon_ring_unlock_unकरो(rdev, ring);
			वापस r;
		पूर्ण
		radeon_ring_unlock_commit(rdev, ring, false);
	पूर्ण
	वापस 0;
पूर्ण

व्योम radeon_test_ring_sync(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_ring *ringA,
			   काष्ठा radeon_ring *ringB)
अणु
	काष्ठा radeon_fence *fence1 = शून्य, *fence2 = शून्य;
	काष्ठा radeon_semaphore *semaphore = शून्य;
	पूर्णांक r;

	r = radeon_semaphore_create(rdev, &semaphore);
	अगर (r) अणु
		DRM_ERROR("Failed to create semaphore\n");
		जाओ out_cleanup;
	पूर्ण

	r = radeon_ring_lock(rdev, ringA, 64);
	अगर (r) अणु
		DRM_ERROR("Failed to lock ring A %d\n", ringA->idx);
		जाओ out_cleanup;
	पूर्ण
	radeon_semaphore_emit_रुको(rdev, ringA->idx, semaphore);
	radeon_ring_unlock_commit(rdev, ringA, false);

	r = radeon_test_create_and_emit_fence(rdev, ringA, &fence1);
	अगर (r)
		जाओ out_cleanup;

	r = radeon_ring_lock(rdev, ringA, 64);
	अगर (r) अणु
		DRM_ERROR("Failed to lock ring A %d\n", ringA->idx);
		जाओ out_cleanup;
	पूर्ण
	radeon_semaphore_emit_रुको(rdev, ringA->idx, semaphore);
	radeon_ring_unlock_commit(rdev, ringA, false);

	r = radeon_test_create_and_emit_fence(rdev, ringA, &fence2);
	अगर (r)
		जाओ out_cleanup;

	msleep(1000);

	अगर (radeon_fence_संकेतed(fence1)) अणु
		DRM_ERROR("Fence 1 signaled without waiting for semaphore.\n");
		जाओ out_cleanup;
	पूर्ण

	r = radeon_ring_lock(rdev, ringB, 64);
	अगर (r) अणु
		DRM_ERROR("Failed to lock ring B %p\n", ringB);
		जाओ out_cleanup;
	पूर्ण
	radeon_semaphore_emit_संकेत(rdev, ringB->idx, semaphore);
	radeon_ring_unlock_commit(rdev, ringB, false);

	r = radeon_fence_रुको(fence1, false);
	अगर (r) अणु
		DRM_ERROR("Failed to wait for sync fence 1\n");
		जाओ out_cleanup;
	पूर्ण

	msleep(1000);

	अगर (radeon_fence_संकेतed(fence2)) अणु
		DRM_ERROR("Fence 2 signaled without waiting for semaphore.\n");
		जाओ out_cleanup;
	पूर्ण

	r = radeon_ring_lock(rdev, ringB, 64);
	अगर (r) अणु
		DRM_ERROR("Failed to lock ring B %p\n", ringB);
		जाओ out_cleanup;
	पूर्ण
	radeon_semaphore_emit_संकेत(rdev, ringB->idx, semaphore);
	radeon_ring_unlock_commit(rdev, ringB, false);

	r = radeon_fence_रुको(fence2, false);
	अगर (r) अणु
		DRM_ERROR("Failed to wait for sync fence 1\n");
		जाओ out_cleanup;
	पूर्ण

out_cleanup:
	radeon_semaphore_मुक्त(rdev, &semaphore, शून्य);

	अगर (fence1)
		radeon_fence_unref(&fence1);

	अगर (fence2)
		radeon_fence_unref(&fence2);

	अगर (r)
		pr_warn("Error while testing ring sync (%d)\n", r);
पूर्ण

अटल व्योम radeon_test_ring_sync2(काष्ठा radeon_device *rdev,
			    काष्ठा radeon_ring *ringA,
			    काष्ठा radeon_ring *ringB,
			    काष्ठा radeon_ring *ringC)
अणु
	काष्ठा radeon_fence *fenceA = शून्य, *fenceB = शून्य;
	काष्ठा radeon_semaphore *semaphore = शून्य;
	bool sigA, sigB;
	पूर्णांक i, r;

	r = radeon_semaphore_create(rdev, &semaphore);
	अगर (r) अणु
		DRM_ERROR("Failed to create semaphore\n");
		जाओ out_cleanup;
	पूर्ण

	r = radeon_ring_lock(rdev, ringA, 64);
	अगर (r) अणु
		DRM_ERROR("Failed to lock ring A %d\n", ringA->idx);
		जाओ out_cleanup;
	पूर्ण
	radeon_semaphore_emit_रुको(rdev, ringA->idx, semaphore);
	radeon_ring_unlock_commit(rdev, ringA, false);

	r = radeon_test_create_and_emit_fence(rdev, ringA, &fenceA);
	अगर (r)
		जाओ out_cleanup;

	r = radeon_ring_lock(rdev, ringB, 64);
	अगर (r) अणु
		DRM_ERROR("Failed to lock ring B %d\n", ringB->idx);
		जाओ out_cleanup;
	पूर्ण
	radeon_semaphore_emit_रुको(rdev, ringB->idx, semaphore);
	radeon_ring_unlock_commit(rdev, ringB, false);
	r = radeon_test_create_and_emit_fence(rdev, ringB, &fenceB);
	अगर (r)
		जाओ out_cleanup;

	msleep(1000);

	अगर (radeon_fence_संकेतed(fenceA)) अणु
		DRM_ERROR("Fence A signaled without waiting for semaphore.\n");
		जाओ out_cleanup;
	पूर्ण
	अगर (radeon_fence_संकेतed(fenceB)) अणु
		DRM_ERROR("Fence B signaled without waiting for semaphore.\n");
		जाओ out_cleanup;
	पूर्ण

	r = radeon_ring_lock(rdev, ringC, 64);
	अगर (r) अणु
		DRM_ERROR("Failed to lock ring B %p\n", ringC);
		जाओ out_cleanup;
	पूर्ण
	radeon_semaphore_emit_संकेत(rdev, ringC->idx, semaphore);
	radeon_ring_unlock_commit(rdev, ringC, false);

	क्रम (i = 0; i < 30; ++i) अणु
		msleep(100);
		sigA = radeon_fence_संकेतed(fenceA);
		sigB = radeon_fence_संकेतed(fenceB);
		अगर (sigA || sigB)
			अवरोध;
	पूर्ण

	अगर (!sigA && !sigB) अणु
		DRM_ERROR("Neither fence A nor B has been signaled\n");
		जाओ out_cleanup;
	पूर्ण अन्यथा अगर (sigA && sigB) अणु
		DRM_ERROR("Both fence A and B has been signaled\n");
		जाओ out_cleanup;
	पूर्ण

	DRM_INFO("Fence %c was first signaled\n", sigA ? 'A' : 'B');

	r = radeon_ring_lock(rdev, ringC, 64);
	अगर (r) अणु
		DRM_ERROR("Failed to lock ring B %p\n", ringC);
		जाओ out_cleanup;
	पूर्ण
	radeon_semaphore_emit_संकेत(rdev, ringC->idx, semaphore);
	radeon_ring_unlock_commit(rdev, ringC, false);

	msleep(1000);

	r = radeon_fence_रुको(fenceA, false);
	अगर (r) अणु
		DRM_ERROR("Failed to wait for sync fence A\n");
		जाओ out_cleanup;
	पूर्ण
	r = radeon_fence_रुको(fenceB, false);
	अगर (r) अणु
		DRM_ERROR("Failed to wait for sync fence B\n");
		जाओ out_cleanup;
	पूर्ण

out_cleanup:
	radeon_semaphore_मुक्त(rdev, &semaphore, शून्य);

	अगर (fenceA)
		radeon_fence_unref(&fenceA);

	अगर (fenceB)
		radeon_fence_unref(&fenceB);

	अगर (r)
		pr_warn("Error while testing ring sync (%d)\n", r);
पूर्ण

अटल bool radeon_test_sync_possible(काष्ठा radeon_ring *ringA,
				      काष्ठा radeon_ring *ringB)
अणु
	अगर (ringA->idx == TN_RING_TYPE_VCE2_INDEX &&
	    ringB->idx == TN_RING_TYPE_VCE1_INDEX)
		वापस false;

	वापस true;
पूर्ण

व्योम radeon_test_syncing(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i, j, k;

	क्रम (i = 1; i < RADEON_NUM_RINGS; ++i) अणु
		काष्ठा radeon_ring *ringA = &rdev->ring[i];
		अगर (!ringA->पढ़ोy)
			जारी;

		क्रम (j = 0; j < i; ++j) अणु
			काष्ठा radeon_ring *ringB = &rdev->ring[j];
			अगर (!ringB->पढ़ोy)
				जारी;

			अगर (!radeon_test_sync_possible(ringA, ringB))
				जारी;

			DRM_INFO("Testing syncing between rings %d and %d...\n", i, j);
			radeon_test_ring_sync(rdev, ringA, ringB);

			DRM_INFO("Testing syncing between rings %d and %d...\n", j, i);
			radeon_test_ring_sync(rdev, ringB, ringA);

			क्रम (k = 0; k < j; ++k) अणु
				काष्ठा radeon_ring *ringC = &rdev->ring[k];
				अगर (!ringC->पढ़ोy)
					जारी;

				अगर (!radeon_test_sync_possible(ringA, ringC))
					जारी;

				अगर (!radeon_test_sync_possible(ringB, ringC))
					जारी;

				DRM_INFO("Testing syncing between rings %d, %d and %d...\n", i, j, k);
				radeon_test_ring_sync2(rdev, ringA, ringB, ringC);

				DRM_INFO("Testing syncing between rings %d, %d and %d...\n", i, k, j);
				radeon_test_ring_sync2(rdev, ringA, ringC, ringB);

				DRM_INFO("Testing syncing between rings %d, %d and %d...\n", j, i, k);
				radeon_test_ring_sync2(rdev, ringB, ringA, ringC);

				DRM_INFO("Testing syncing between rings %d, %d and %d...\n", j, k, i);
				radeon_test_ring_sync2(rdev, ringB, ringC, ringA);

				DRM_INFO("Testing syncing between rings %d, %d and %d...\n", k, i, j);
				radeon_test_ring_sync2(rdev, ringC, ringA, ringB);

				DRM_INFO("Testing syncing between rings %d, %d and %d...\n", k, j, i);
				radeon_test_ring_sync2(rdev, ringC, ringB, ringA);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
