<शैली गुरु>
/*
 * Copyright 2010 Advanced Micro Devices, Inc.
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
 * Authors: Alex Deucher
 */

#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "evergreen.h"
#समावेश "evergreend.h"

/**
 * evergreen_dma_fence_ring_emit - emit a fence on the DMA ring
 *
 * @rdev: radeon_device poपूर्णांकer
 * @fence: radeon fence object
 *
 * Add a DMA fence packet to the ring to ग_लिखो
 * the fence seq number and DMA trap packet to generate
 * an पूर्णांकerrupt अगर needed (evergreen-SI).
 */
व्योम evergreen_dma_fence_ring_emit(काष्ठा radeon_device *rdev,
				   काष्ठा radeon_fence *fence)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[fence->ring];
	u64 addr = rdev->fence_drv[fence->ring].gpu_addr;
	/* ग_लिखो the fence */
	radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_FENCE, 0, 0));
	radeon_ring_ग_लिखो(ring, addr & 0xfffffffc);
	radeon_ring_ग_लिखो(ring, (upper_32_bits(addr) & 0xff));
	radeon_ring_ग_लिखो(ring, fence->seq);
	/* generate an पूर्णांकerrupt */
	radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_TRAP, 0, 0));
	/* flush HDP */
	radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_SRBM_WRITE, 0, 0));
	radeon_ring_ग_लिखो(ring, (0xf << 16) | (HDP_MEM_COHERENCY_FLUSH_CNTL >> 2));
	radeon_ring_ग_लिखो(ring, 1);
पूर्ण

/**
 * evergreen_dma_ring_ib_execute - schedule an IB on the DMA engine
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ib: IB object to schedule
 *
 * Schedule an IB in the DMA ring (evergreen).
 */
व्योम evergreen_dma_ring_ib_execute(काष्ठा radeon_device *rdev,
				   काष्ठा radeon_ib *ib)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[ib->ring];

	अगर (rdev->wb.enabled) अणु
		u32 next_rptr = ring->wptr + 4;
		जबतक ((next_rptr & 7) != 5)
			next_rptr++;
		next_rptr += 3;
		radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_WRITE, 0, 1));
		radeon_ring_ग_लिखो(ring, ring->next_rptr_gpu_addr & 0xfffffffc);
		radeon_ring_ग_लिखो(ring, upper_32_bits(ring->next_rptr_gpu_addr) & 0xff);
		radeon_ring_ग_लिखो(ring, next_rptr);
	पूर्ण

	/* The indirect buffer packet must end on an 8 DW boundary in the DMA ring.
	 * Pad as necessary with NOPs.
	 */
	जबतक ((ring->wptr & 7) != 5)
		radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_NOP, 0, 0));
	radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_INसूचीECT_BUFFER, 0, 0));
	radeon_ring_ग_लिखो(ring, (ib->gpu_addr & 0xFFFFFFE0));
	radeon_ring_ग_लिखो(ring, (ib->length_dw << 12) | (upper_32_bits(ib->gpu_addr) & 0xFF));

पूर्ण

/**
 * evergreen_copy_dma - copy pages using the DMA engine
 *
 * @rdev: radeon_device poपूर्णांकer
 * @src_offset: src GPU address
 * @dst_offset: dst GPU address
 * @num_gpu_pages: number of GPU pages to xfer
 * @resv: reservation object with embedded fence
 *
 * Copy GPU paging using the DMA engine (evergreen-cayman).
 * Used by the radeon tपंचांग implementation to move pages अगर
 * रेजिस्टरed as the asic copy callback.
 */
काष्ठा radeon_fence *evergreen_copy_dma(काष्ठा radeon_device *rdev,
					uपूर्णांक64_t src_offset,
					uपूर्णांक64_t dst_offset,
					अचिन्हित num_gpu_pages,
					काष्ठा dma_resv *resv)
अणु
	काष्ठा radeon_fence *fence;
	काष्ठा radeon_sync sync;
	पूर्णांक ring_index = rdev->asic->copy.dma_ring_index;
	काष्ठा radeon_ring *ring = &rdev->ring[ring_index];
	u32 size_in_dw, cur_size_in_dw;
	पूर्णांक i, num_loops;
	पूर्णांक r = 0;

	radeon_sync_create(&sync);

	size_in_dw = (num_gpu_pages << RADEON_GPU_PAGE_SHIFT) / 4;
	num_loops = DIV_ROUND_UP(size_in_dw, 0xfffff);
	r = radeon_ring_lock(rdev, ring, num_loops * 5 + 11);
	अगर (r) अणु
		DRM_ERROR("radeon: moving bo (%d).\n", r);
		radeon_sync_मुक्त(rdev, &sync, शून्य);
		वापस ERR_PTR(r);
	पूर्ण

	radeon_sync_resv(rdev, &sync, resv, false);
	radeon_sync_rings(rdev, &sync, ring->idx);

	क्रम (i = 0; i < num_loops; i++) अणु
		cur_size_in_dw = size_in_dw;
		अगर (cur_size_in_dw > 0xFFFFF)
			cur_size_in_dw = 0xFFFFF;
		size_in_dw -= cur_size_in_dw;
		radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_COPY, 0, cur_size_in_dw));
		radeon_ring_ग_लिखो(ring, dst_offset & 0xfffffffc);
		radeon_ring_ग_लिखो(ring, src_offset & 0xfffffffc);
		radeon_ring_ग_लिखो(ring, upper_32_bits(dst_offset) & 0xff);
		radeon_ring_ग_लिखो(ring, upper_32_bits(src_offset) & 0xff);
		src_offset += cur_size_in_dw * 4;
		dst_offset += cur_size_in_dw * 4;
	पूर्ण

	r = radeon_fence_emit(rdev, &fence, ring->idx);
	अगर (r) अणु
		radeon_ring_unlock_unकरो(rdev, ring);
		radeon_sync_मुक्त(rdev, &sync, शून्य);
		वापस ERR_PTR(r);
	पूर्ण

	radeon_ring_unlock_commit(rdev, ring, false);
	radeon_sync_मुक्त(rdev, &sync, fence);

	वापस fence;
पूर्ण

/**
 * evergreen_dma_is_lockup - Check अगर the DMA engine is locked up
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 *
 * Check अगर the async DMA engine is locked up.
 * Returns true अगर the engine appears to be locked up, false अगर not.
 */
bool evergreen_dma_is_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	u32 reset_mask = evergreen_gpu_check_soft_reset(rdev);

	अगर (!(reset_mask & RADEON_RESET_DMA)) अणु
		radeon_ring_lockup_update(rdev, ring);
		वापस false;
	पूर्ण
	वापस radeon_ring_test_lockup(rdev, ring);
पूर्ण


