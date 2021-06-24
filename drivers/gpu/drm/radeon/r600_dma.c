<शैली गुरु>
/*
 * Copyright 2013 Advanced Micro Devices, Inc.
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
#समावेश "r600.h"
#समावेश "r600d.h"

/*
 * DMA
 * Starting with R600, the GPU has an asynchronous
 * DMA engine.  The programming model is very similar
 * to the 3D engine (ring buffer, IBs, etc.), but the
 * DMA controller has it's own packet क्रमmat that is
 * dअगरferent क्रमm the PM4 क्रमmat used by the 3D engine.
 * It supports copying data, writing embedded data,
 * solid fills, and a number of other things.  It also
 * has support क्रम tiling/detiling of buffers.
 */

/**
 * r600_dma_get_rptr - get the current पढ़ो poपूर्णांकer
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon ring poपूर्णांकer
 *
 * Get the current rptr from the hardware (r6xx+).
 */
uपूर्णांक32_t r600_dma_get_rptr(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_ring *ring)
अणु
	u32 rptr;

	अगर (rdev->wb.enabled)
		rptr = rdev->wb.wb[ring->rptr_offs/4];
	अन्यथा
		rptr = RREG32(DMA_RB_RPTR);

	वापस (rptr & 0x3fffc) >> 2;
पूर्ण

/**
 * r600_dma_get_wptr - get the current ग_लिखो poपूर्णांकer
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon ring poपूर्णांकer
 *
 * Get the current wptr from the hardware (r6xx+).
 */
uपूर्णांक32_t r600_dma_get_wptr(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_ring *ring)
अणु
	वापस (RREG32(DMA_RB_WPTR) & 0x3fffc) >> 2;
पूर्ण

/**
 * r600_dma_set_wptr - commit the ग_लिखो poपूर्णांकer
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon ring poपूर्णांकer
 *
 * Write the wptr back to the hardware (r6xx+).
 */
व्योम r600_dma_set_wptr(काष्ठा radeon_device *rdev,
		       काष्ठा radeon_ring *ring)
अणु
	WREG32(DMA_RB_WPTR, (ring->wptr << 2) & 0x3fffc);
पूर्ण

/**
 * r600_dma_stop - stop the async dma engine
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Stop the async dma engine (r6xx-evergreen).
 */
व्योम r600_dma_stop(काष्ठा radeon_device *rdev)
अणु
	u32 rb_cntl = RREG32(DMA_RB_CNTL);

	अगर (rdev->asic->copy.copy_ring_index == R600_RING_TYPE_DMA_INDEX)
		radeon_tपंचांग_set_active_vram_size(rdev, rdev->mc.visible_vram_size);

	rb_cntl &= ~DMA_RB_ENABLE;
	WREG32(DMA_RB_CNTL, rb_cntl);

	rdev->ring[R600_RING_TYPE_DMA_INDEX].पढ़ोy = false;
पूर्ण

/**
 * r600_dma_resume - setup and start the async dma engine
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Set up the DMA ring buffer and enable it. (r6xx-evergreen).
 * Returns 0 क्रम success, error क्रम failure.
 */
पूर्णांक r600_dma_resume(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[R600_RING_TYPE_DMA_INDEX];
	u32 rb_cntl, dma_cntl, ib_cntl;
	u32 rb_bufsz;
	पूर्णांक r;

	WREG32(DMA_SEM_INCOMPLETE_TIMER_CNTL, 0);
	WREG32(DMA_SEM_WAIT_FAIL_TIMER_CNTL, 0);

	/* Set ring buffer size in dwords */
	rb_bufsz = order_base_2(ring->ring_size / 4);
	rb_cntl = rb_bufsz << 1;
#अगर_घोषित __BIG_ENDIAN
	rb_cntl |= DMA_RB_SWAP_ENABLE | DMA_RPTR_WRITEBACK_SWAP_ENABLE;
#पूर्ण_अगर
	WREG32(DMA_RB_CNTL, rb_cntl);

	/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
	WREG32(DMA_RB_RPTR, 0);
	WREG32(DMA_RB_WPTR, 0);

	/* set the wb address whether it's enabled or not */
	WREG32(DMA_RB_RPTR_ADDR_HI,
	       upper_32_bits(rdev->wb.gpu_addr + R600_WB_DMA_RPTR_OFFSET) & 0xFF);
	WREG32(DMA_RB_RPTR_ADDR_LO,
	       ((rdev->wb.gpu_addr + R600_WB_DMA_RPTR_OFFSET) & 0xFFFFFFFC));

	अगर (rdev->wb.enabled)
		rb_cntl |= DMA_RPTR_WRITEBACK_ENABLE;

	WREG32(DMA_RB_BASE, ring->gpu_addr >> 8);

	/* enable DMA IBs */
	ib_cntl = DMA_IB_ENABLE;
#अगर_घोषित __BIG_ENDIAN
	ib_cntl |= DMA_IB_SWAP_ENABLE;
#पूर्ण_अगर
	WREG32(DMA_IB_CNTL, ib_cntl);

	dma_cntl = RREG32(DMA_CNTL);
	dma_cntl &= ~CTXEMPTY_INT_ENABLE;
	WREG32(DMA_CNTL, dma_cntl);

	अगर (rdev->family >= CHIP_RV770)
		WREG32(DMA_MODE, 1);

	ring->wptr = 0;
	WREG32(DMA_RB_WPTR, ring->wptr << 2);

	WREG32(DMA_RB_CNTL, rb_cntl | DMA_RB_ENABLE);

	ring->पढ़ोy = true;

	r = radeon_ring_test(rdev, R600_RING_TYPE_DMA_INDEX, ring);
	अगर (r) अणु
		ring->पढ़ोy = false;
		वापस r;
	पूर्ण

	अगर (rdev->asic->copy.copy_ring_index == R600_RING_TYPE_DMA_INDEX)
		radeon_tपंचांग_set_active_vram_size(rdev, rdev->mc.real_vram_size);

	वापस 0;
पूर्ण

/**
 * r600_dma_fini - tear करोwn the async dma engine
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Stop the async dma engine and मुक्त the ring (r6xx-evergreen).
 */
व्योम r600_dma_fini(काष्ठा radeon_device *rdev)
अणु
	r600_dma_stop(rdev);
	radeon_ring_fini(rdev, &rdev->ring[R600_RING_TYPE_DMA_INDEX]);
पूर्ण

/**
 * r600_dma_is_lockup - Check अगर the DMA engine is locked up
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 *
 * Check अगर the async DMA engine is locked up.
 * Returns true अगर the engine appears to be locked up, false अगर not.
 */
bool r600_dma_is_lockup(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	u32 reset_mask = r600_gpu_check_soft_reset(rdev);

	अगर (!(reset_mask & RADEON_RESET_DMA)) अणु
		radeon_ring_lockup_update(rdev, ring);
		वापस false;
	पूर्ण
	वापस radeon_ring_test_lockup(rdev, ring);
पूर्ण


/**
 * r600_dma_ring_test - simple async dma engine test
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 *
 * Test the DMA engine by writing using it to ग_लिखो an
 * value to memory. (r6xx-SI).
 * Returns 0 क्रम success, error क्रम failure.
 */
पूर्णांक r600_dma_ring_test(काष्ठा radeon_device *rdev,
		       काष्ठा radeon_ring *ring)
अणु
	अचिन्हित i;
	पूर्णांक r;
	अचिन्हित index;
	u32 पंचांगp;
	u64 gpu_addr;

	अगर (ring->idx == R600_RING_TYPE_DMA_INDEX)
		index = R600_WB_DMA_RING_TEST_OFFSET;
	अन्यथा
		index = CAYMAN_WB_DMA1_RING_TEST_OFFSET;

	gpu_addr = rdev->wb.gpu_addr + index;

	पंचांगp = 0xCAFEDEAD;
	rdev->wb.wb[index/4] = cpu_to_le32(पंचांगp);

	r = radeon_ring_lock(rdev, ring, 4);
	अगर (r) अणु
		DRM_ERROR("radeon: dma failed to lock ring %d (%d).\n", ring->idx, r);
		वापस r;
	पूर्ण
	radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_WRITE, 0, 0, 1));
	radeon_ring_ग_लिखो(ring, lower_32_bits(gpu_addr));
	radeon_ring_ग_लिखो(ring, upper_32_bits(gpu_addr) & 0xff);
	radeon_ring_ग_लिखो(ring, 0xDEADBEEF);
	radeon_ring_unlock_commit(rdev, ring, false);

	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		पंचांगp = le32_to_cpu(rdev->wb.wb[index/4]);
		अगर (पंचांगp == 0xDEADBEEF)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (i < rdev->usec_समयout) अणु
		DRM_INFO("ring test on %d succeeded in %d usecs\n", ring->idx, i);
	पूर्ण अन्यथा अणु
		DRM_ERROR("radeon: ring %d test failed (0x%08X)\n",
			  ring->idx, पंचांगp);
		r = -EINVAL;
	पूर्ण
	वापस r;
पूर्ण

/**
 * r600_dma_fence_ring_emit - emit a fence on the DMA ring
 *
 * @rdev: radeon_device poपूर्णांकer
 * @fence: radeon fence object
 *
 * Add a DMA fence packet to the ring to ग_लिखो
 * the fence seq number and DMA trap packet to generate
 * an पूर्णांकerrupt अगर needed (r6xx-r7xx).
 */
व्योम r600_dma_fence_ring_emit(काष्ठा radeon_device *rdev,
			      काष्ठा radeon_fence *fence)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[fence->ring];
	u64 addr = rdev->fence_drv[fence->ring].gpu_addr;

	/* ग_लिखो the fence */
	radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_FENCE, 0, 0, 0));
	radeon_ring_ग_लिखो(ring, addr & 0xfffffffc);
	radeon_ring_ग_लिखो(ring, (upper_32_bits(addr) & 0xff));
	radeon_ring_ग_लिखो(ring, lower_32_bits(fence->seq));
	/* generate an पूर्णांकerrupt */
	radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_TRAP, 0, 0, 0));
पूर्ण

/**
 * r600_dma_semaphore_ring_emit - emit a semaphore on the dma ring
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 * @semaphore: radeon semaphore object
 * @emit_रुको: रुको or संकेत semaphore
 *
 * Add a DMA semaphore packet to the ring रुको on or संकेत
 * other rings (r6xx-SI).
 */
bool r600_dma_semaphore_ring_emit(काष्ठा radeon_device *rdev,
				  काष्ठा radeon_ring *ring,
				  काष्ठा radeon_semaphore *semaphore,
				  bool emit_रुको)
अणु
	u64 addr = semaphore->gpu_addr;
	u32 s = emit_रुको ? 0 : 1;

	radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_SEMAPHORE, 0, s, 0));
	radeon_ring_ग_लिखो(ring, addr & 0xfffffffc);
	radeon_ring_ग_लिखो(ring, upper_32_bits(addr) & 0xff);

	वापस true;
पूर्ण

/**
 * r600_dma_ib_test - test an IB on the DMA engine
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring काष्ठाure holding ring inक्रमmation
 *
 * Test a simple IB in the DMA ring (r6xx-SI).
 * Returns 0 on success, error on failure.
 */
पूर्णांक r600_dma_ib_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	काष्ठा radeon_ib ib;
	अचिन्हित i;
	अचिन्हित index;
	पूर्णांक r;
	u32 पंचांगp = 0;
	u64 gpu_addr;

	अगर (ring->idx == R600_RING_TYPE_DMA_INDEX)
		index = R600_WB_DMA_RING_TEST_OFFSET;
	अन्यथा
		index = CAYMAN_WB_DMA1_RING_TEST_OFFSET;

	gpu_addr = rdev->wb.gpu_addr + index;

	r = radeon_ib_get(rdev, ring->idx, &ib, शून्य, 256);
	अगर (r) अणु
		DRM_ERROR("radeon: failed to get ib (%d).\n", r);
		वापस r;
	पूर्ण

	ib.ptr[0] = DMA_PACKET(DMA_PACKET_WRITE, 0, 0, 1);
	ib.ptr[1] = lower_32_bits(gpu_addr);
	ib.ptr[2] = upper_32_bits(gpu_addr) & 0xff;
	ib.ptr[3] = 0xDEADBEEF;
	ib.length_dw = 4;

	r = radeon_ib_schedule(rdev, &ib, शून्य, false);
	अगर (r) अणु
		radeon_ib_मुक्त(rdev, &ib);
		DRM_ERROR("radeon: failed to schedule ib (%d).\n", r);
		वापस r;
	पूर्ण
	r = radeon_fence_रुको_समयout(ib.fence, false, usecs_to_jअगरfies(
		RADEON_USEC_IB_TEST_TIMEOUT));
	अगर (r < 0) अणु
		DRM_ERROR("radeon: fence wait failed (%d).\n", r);
		वापस r;
	पूर्ण अन्यथा अगर (r == 0) अणु
		DRM_ERROR("radeon: fence wait timed out.\n");
		वापस -ETIMEDOUT;
	पूर्ण
	r = 0;
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		पंचांगp = le32_to_cpu(rdev->wb.wb[index/4]);
		अगर (पंचांगp == 0xDEADBEEF)
			अवरोध;
		udelay(1);
	पूर्ण
	अगर (i < rdev->usec_समयout) अणु
		DRM_INFO("ib test on ring %d succeeded in %u usecs\n", ib.fence->ring, i);
	पूर्ण अन्यथा अणु
		DRM_ERROR("radeon: ib test failed (0x%08X)\n", पंचांगp);
		r = -EINVAL;
	पूर्ण
	radeon_ib_मुक्त(rdev, &ib);
	वापस r;
पूर्ण

/**
 * r600_dma_ring_ib_execute - Schedule an IB on the DMA engine
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ib: IB object to schedule
 *
 * Schedule an IB in the DMA ring (r6xx-r7xx).
 */
व्योम r600_dma_ring_ib_execute(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[ib->ring];

	अगर (rdev->wb.enabled) अणु
		u32 next_rptr = ring->wptr + 4;
		जबतक ((next_rptr & 7) != 5)
			next_rptr++;
		next_rptr += 3;
		radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_WRITE, 0, 0, 1));
		radeon_ring_ग_लिखो(ring, ring->next_rptr_gpu_addr & 0xfffffffc);
		radeon_ring_ग_लिखो(ring, upper_32_bits(ring->next_rptr_gpu_addr) & 0xff);
		radeon_ring_ग_लिखो(ring, next_rptr);
	पूर्ण

	/* The indirect buffer packet must end on an 8 DW boundary in the DMA ring.
	 * Pad as necessary with NOPs.
	 */
	जबतक ((ring->wptr & 7) != 5)
		radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_NOP, 0, 0, 0));
	radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_INसूचीECT_BUFFER, 0, 0, 0));
	radeon_ring_ग_लिखो(ring, (ib->gpu_addr & 0xFFFFFFE0));
	radeon_ring_ग_लिखो(ring, (ib->length_dw << 16) | (upper_32_bits(ib->gpu_addr) & 0xFF));

पूर्ण

/**
 * r600_copy_dma - copy pages using the DMA engine
 *
 * @rdev: radeon_device poपूर्णांकer
 * @src_offset: src GPU address
 * @dst_offset: dst GPU address
 * @num_gpu_pages: number of GPU pages to xfer
 * @resv: reservation object to sync to
 *
 * Copy GPU paging using the DMA engine (r6xx).
 * Used by the radeon tपंचांग implementation to move pages अगर
 * रेजिस्टरed as the asic copy callback.
 */
काष्ठा radeon_fence *r600_copy_dma(काष्ठा radeon_device *rdev,
				   uपूर्णांक64_t src_offset, uपूर्णांक64_t dst_offset,
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
	num_loops = DIV_ROUND_UP(size_in_dw, 0xFFFE);
	r = radeon_ring_lock(rdev, ring, num_loops * 4 + 8);
	अगर (r) अणु
		DRM_ERROR("radeon: moving bo (%d).\n", r);
		radeon_sync_मुक्त(rdev, &sync, शून्य);
		वापस ERR_PTR(r);
	पूर्ण

	radeon_sync_resv(rdev, &sync, resv, false);
	radeon_sync_rings(rdev, &sync, ring->idx);

	क्रम (i = 0; i < num_loops; i++) अणु
		cur_size_in_dw = size_in_dw;
		अगर (cur_size_in_dw > 0xFFFE)
			cur_size_in_dw = 0xFFFE;
		size_in_dw -= cur_size_in_dw;
		radeon_ring_ग_लिखो(ring, DMA_PACKET(DMA_PACKET_COPY, 0, 0, cur_size_in_dw));
		radeon_ring_ग_लिखो(ring, dst_offset & 0xfffffffc);
		radeon_ring_ग_लिखो(ring, src_offset & 0xfffffffc);
		radeon_ring_ग_लिखो(ring, (((upper_32_bits(dst_offset) & 0xff) << 16) |
					 (upper_32_bits(src_offset) & 0xff)));
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
