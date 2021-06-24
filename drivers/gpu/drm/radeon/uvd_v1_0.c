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
 * Authors: Christian Kथघnig <christian.koenig@amd.com>
 */

#समावेश <linux/firmware.h>

#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "r600d.h"

/**
 * uvd_v1_0_get_rptr - get पढ़ो poपूर्णांकer
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring poपूर्णांकer
 *
 * Returns the current hardware पढ़ो poपूर्णांकer
 */
uपूर्णांक32_t uvd_v1_0_get_rptr(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_ring *ring)
अणु
	वापस RREG32(UVD_RBC_RB_RPTR);
पूर्ण

/**
 * uvd_v1_0_get_wptr - get ग_लिखो poपूर्णांकer
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring poपूर्णांकer
 *
 * Returns the current hardware ग_लिखो poपूर्णांकer
 */
uपूर्णांक32_t uvd_v1_0_get_wptr(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_ring *ring)
अणु
	वापस RREG32(UVD_RBC_RB_WPTR);
पूर्ण

/**
 * uvd_v1_0_set_wptr - set ग_लिखो poपूर्णांकer
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring poपूर्णांकer
 *
 * Commits the ग_लिखो poपूर्णांकer to the hardware
 */
व्योम uvd_v1_0_set_wptr(काष्ठा radeon_device *rdev,
		       काष्ठा radeon_ring *ring)
अणु
	WREG32(UVD_RBC_RB_WPTR, ring->wptr);
पूर्ण

/**
 * uvd_v1_0_fence_emit - emit an fence & trap command
 *
 * @rdev: radeon_device poपूर्णांकer
 * @fence: fence to emit
 *
 * Write a fence and a trap command to the ring.
 */
व्योम uvd_v1_0_fence_emit(काष्ठा radeon_device *rdev,
			 काष्ठा radeon_fence *fence)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[fence->ring];
	uपूर्णांक64_t addr = rdev->fence_drv[fence->ring].gpu_addr;

	radeon_ring_ग_लिखो(ring, PACKET0(UVD_GPCOM_VCPU_DATA0, 0));
	radeon_ring_ग_लिखो(ring, addr & 0xffffffff);
	radeon_ring_ग_लिखो(ring, PACKET0(UVD_GPCOM_VCPU_DATA1, 0));
	radeon_ring_ग_लिखो(ring, fence->seq);
	radeon_ring_ग_लिखो(ring, PACKET0(UVD_GPCOM_VCPU_CMD, 0));
	radeon_ring_ग_लिखो(ring, 0);

	radeon_ring_ग_लिखो(ring, PACKET0(UVD_GPCOM_VCPU_DATA0, 0));
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, PACKET0(UVD_GPCOM_VCPU_DATA1, 0));
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, PACKET0(UVD_GPCOM_VCPU_CMD, 0));
	radeon_ring_ग_लिखो(ring, 2);
	वापस;
पूर्ण

/**
 * uvd_v1_0_resume - memory controller programming
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Let the UVD memory controller know it's offsets
 */
पूर्णांक uvd_v1_0_resume(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक64_t addr;
	uपूर्णांक32_t size;
	पूर्णांक r;

	r = radeon_uvd_resume(rdev);
	अगर (r)
		वापस r;

	/* program the VCPU memory controller bits 0-27 */
	addr = (rdev->uvd.gpu_addr >> 3) + 16;
	size = RADEON_GPU_PAGE_ALIGN(rdev->uvd_fw->size) >> 3;
	WREG32(UVD_VCPU_CACHE_OFFSET0, addr);
	WREG32(UVD_VCPU_CACHE_SIZE0, size);

	addr += size;
	size = RADEON_UVD_HEAP_SIZE >> 3;
	WREG32(UVD_VCPU_CACHE_OFFSET1, addr);
	WREG32(UVD_VCPU_CACHE_SIZE1, size);

	addr += size;
	size = (RADEON_UVD_STACK_SIZE +
	       (RADEON_UVD_SESSION_SIZE * rdev->uvd.max_handles)) >> 3;
	WREG32(UVD_VCPU_CACHE_OFFSET2, addr);
	WREG32(UVD_VCPU_CACHE_SIZE2, size);

	/* bits 28-31 */
	addr = (rdev->uvd.gpu_addr >> 28) & 0xF;
	WREG32(UVD_LMI_ADDR_EXT, (addr << 12) | (addr << 0));

	/* bits 32-39 */
	addr = (rdev->uvd.gpu_addr >> 32) & 0xFF;
	WREG32(UVD_LMI_EXT40_ADDR, addr | (0x9 << 16) | (0x1 << 31));

	WREG32(UVD_FW_START, *((uपूर्णांक32_t*)rdev->uvd.cpu_addr));

	वापस 0;
पूर्ण

/**
 * uvd_v1_0_init - start and test UVD block
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Initialize the hardware, boot up the VCPU and करो some testing
 */
पूर्णांक uvd_v1_0_init(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[R600_RING_TYPE_UVD_INDEX];
	uपूर्णांक32_t पंचांगp;
	पूर्णांक r;

	/* उठाओ घड़ीs जबतक booting up the VCPU */
	अगर (rdev->family < CHIP_RV740)
		radeon_set_uvd_घड़ीs(rdev, 10000, 10000);
	अन्यथा
		radeon_set_uvd_घड़ीs(rdev, 53300, 40000);

	r = uvd_v1_0_start(rdev);
	अगर (r)
		जाओ करोne;

	ring->पढ़ोy = true;
	r = radeon_ring_test(rdev, R600_RING_TYPE_UVD_INDEX, ring);
	अगर (r) अणु
		ring->पढ़ोy = false;
		जाओ करोne;
	पूर्ण

	r = radeon_ring_lock(rdev, ring, 10);
	अगर (r) अणु
		DRM_ERROR("radeon: ring failed to lock UVD ring (%d).\n", r);
		जाओ करोne;
	पूर्ण

	पंचांगp = PACKET0(UVD_SEMA_WAIT_FAULT_TIMEOUT_CNTL, 0);
	radeon_ring_ग_लिखो(ring, पंचांगp);
	radeon_ring_ग_लिखो(ring, 0xFFFFF);

	पंचांगp = PACKET0(UVD_SEMA_WAIT_INCOMPLETE_TIMEOUT_CNTL, 0);
	radeon_ring_ग_लिखो(ring, पंचांगp);
	radeon_ring_ग_लिखो(ring, 0xFFFFF);

	पंचांगp = PACKET0(UVD_SEMA_SIGNAL_INCOMPLETE_TIMEOUT_CNTL, 0);
	radeon_ring_ग_लिखो(ring, पंचांगp);
	radeon_ring_ग_लिखो(ring, 0xFFFFF);

	/* Clear समयout status bits */
	radeon_ring_ग_लिखो(ring, PACKET0(UVD_SEMA_TIMEOUT_STATUS, 0));
	radeon_ring_ग_लिखो(ring, 0x8);

	radeon_ring_ग_लिखो(ring, PACKET0(UVD_SEMA_CNTL, 0));
	radeon_ring_ग_लिखो(ring, 3);

	radeon_ring_unlock_commit(rdev, ring, false);

करोne:
	/* lower घड़ीs again */
	radeon_set_uvd_घड़ीs(rdev, 0, 0);

	अगर (!r) अणु
		चयन (rdev->family) अणु
		हाल CHIP_RV610:
		हाल CHIP_RV630:
		हाल CHIP_RV620:
			/* 64byte granularity workaround */
			WREG32(MC_CONFIG, 0);
			WREG32(MC_CONFIG, 1 << 4);
			WREG32(RS_DQ_RD_RET_CONF, 0x3f);
			WREG32(MC_CONFIG, 0x1f);

			fallthrough;
		हाल CHIP_RV670:
		हाल CHIP_RV635:

			/* ग_लिखो clean workaround */
			WREG32_P(UVD_VCPU_CNTL, 0x10, ~0x10);
			अवरोध;

		शेष:
			/* TODO: Do we need more? */
			अवरोध;
		पूर्ण

		DRM_INFO("UVD initialized successfully.\n");
	पूर्ण

	वापस r;
पूर्ण

/**
 * uvd_v1_0_fini - stop the hardware block
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Stop the UVD block, mark ring as not पढ़ोy any more
 */
व्योम uvd_v1_0_fini(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[R600_RING_TYPE_UVD_INDEX];

	uvd_v1_0_stop(rdev);
	ring->पढ़ोy = false;
पूर्ण

/**
 * uvd_v1_0_start - start UVD block
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Setup and start the UVD block
 */
पूर्णांक uvd_v1_0_start(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[R600_RING_TYPE_UVD_INDEX];
	uपूर्णांक32_t rb_bufsz;
	पूर्णांक i, j, r;

	/* disable byte swapping */
	u32 lmi_swap_cntl = 0;
	u32 mp_swap_cntl = 0;

	/* disable घड़ी gating */
	WREG32(UVD_CGC_GATE, 0);

	/* disable पूर्णांकerupt */
	WREG32_P(UVD_MASTINT_EN, 0, ~(1 << 1));

	/* Stall UMC and रेजिस्टर bus beक्रमe resetting VCPU */
	WREG32_P(UVD_LMI_CTRL2, 1 << 8, ~(1 << 8));
	WREG32_P(UVD_RB_ARB_CTRL, 1 << 3, ~(1 << 3));
	mdelay(1);

	/* put LMI, VCPU, RBC etc... पूर्णांकo reset */
	WREG32(UVD_SOFT_RESET, LMI_SOFT_RESET | VCPU_SOFT_RESET |
	       LBSI_SOFT_RESET | RBC_SOFT_RESET | CSM_SOFT_RESET |
	       CXW_SOFT_RESET | TAP_SOFT_RESET | LMI_UMC_SOFT_RESET);
	mdelay(5);

	/* take UVD block out of reset */
	WREG32_P(SRBM_SOFT_RESET, 0, ~SOFT_RESET_UVD);
	mdelay(5);

	/* initialize UVD memory controller */
	WREG32(UVD_LMI_CTRL, 0x40 | (1 << 8) | (1 << 13) |
			     (1 << 21) | (1 << 9) | (1 << 20));

#अगर_घोषित __BIG_ENDIAN
	/* swap (8 in 32) RB and IB */
	lmi_swap_cntl = 0xa;
	mp_swap_cntl = 0;
#पूर्ण_अगर
	WREG32(UVD_LMI_SWAP_CNTL, lmi_swap_cntl);
	WREG32(UVD_MP_SWAP_CNTL, mp_swap_cntl);

	WREG32(UVD_MPC_SET_MUXA0, 0x40c2040);
	WREG32(UVD_MPC_SET_MUXA1, 0x0);
	WREG32(UVD_MPC_SET_MUXB0, 0x40c2040);
	WREG32(UVD_MPC_SET_MUXB1, 0x0);
	WREG32(UVD_MPC_SET_ALU, 0);
	WREG32(UVD_MPC_SET_MUX, 0x88);

	/* take all subblocks out of reset, except VCPU */
	WREG32(UVD_SOFT_RESET, VCPU_SOFT_RESET);
	mdelay(5);

	/* enable VCPU घड़ी */
	WREG32(UVD_VCPU_CNTL,  1 << 9);

	/* enable UMC */
	WREG32_P(UVD_LMI_CTRL2, 0, ~(1 << 8));

	WREG32_P(UVD_RB_ARB_CTRL, 0, ~(1 << 3));

	/* boot up the VCPU */
	WREG32(UVD_SOFT_RESET, 0);
	mdelay(10);

	क्रम (i = 0; i < 10; ++i) अणु
		uपूर्णांक32_t status;
		क्रम (j = 0; j < 100; ++j) अणु
			status = RREG32(UVD_STATUS);
			अगर (status & 2)
				अवरोध;
			mdelay(10);
		पूर्ण
		r = 0;
		अगर (status & 2)
			अवरोध;

		DRM_ERROR("UVD not responding, trying to reset the VCPU!!!\n");
		WREG32_P(UVD_SOFT_RESET, VCPU_SOFT_RESET, ~VCPU_SOFT_RESET);
		mdelay(10);
		WREG32_P(UVD_SOFT_RESET, 0, ~VCPU_SOFT_RESET);
		mdelay(10);
		r = -1;
	पूर्ण

	अगर (r) अणु
		DRM_ERROR("UVD not responding, giving up!!!\n");
		वापस r;
	पूर्ण

	/* enable पूर्णांकerupt */
	WREG32_P(UVD_MASTINT_EN, 3<<1, ~(3 << 1));

	/* क्रमce RBC पूर्णांकo idle state */
	WREG32(UVD_RBC_RB_CNTL, 0x11010101);

	/* Set the ग_लिखो poपूर्णांकer delay */
	WREG32(UVD_RBC_RB_WPTR_CNTL, 0);

	/* program the 4GB memory segment क्रम rptr and ring buffer */
	WREG32(UVD_LMI_EXT40_ADDR, upper_32_bits(ring->gpu_addr) |
				   (0x7 << 16) | (0x1 << 31));

	/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
	WREG32(UVD_RBC_RB_RPTR, 0x0);

	ring->wptr = RREG32(UVD_RBC_RB_RPTR);
	WREG32(UVD_RBC_RB_WPTR, ring->wptr);

	/* set the ring address */
	WREG32(UVD_RBC_RB_BASE, ring->gpu_addr);

	/* Set ring buffer size */
	rb_bufsz = order_base_2(ring->ring_size);
	rb_bufsz = (0x1 << 8) | rb_bufsz;
	WREG32_P(UVD_RBC_RB_CNTL, rb_bufsz, ~0x11f1f);

	वापस 0;
पूर्ण

/**
 * uvd_v1_0_stop - stop UVD block
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * stop the UVD block
 */
व्योम uvd_v1_0_stop(काष्ठा radeon_device *rdev)
अणु
	/* क्रमce RBC पूर्णांकo idle state */
	WREG32(UVD_RBC_RB_CNTL, 0x11010101);

	/* Stall UMC and रेजिस्टर bus beक्रमe resetting VCPU */
	WREG32_P(UVD_LMI_CTRL2, 1 << 8, ~(1 << 8));
	WREG32_P(UVD_RB_ARB_CTRL, 1 << 3, ~(1 << 3));
	mdelay(1);

	/* put VCPU पूर्णांकo reset */
	WREG32(UVD_SOFT_RESET, VCPU_SOFT_RESET);
	mdelay(5);

	/* disable VCPU घड़ी */
	WREG32(UVD_VCPU_CNTL, 0x0);

	/* Unstall UMC and रेजिस्टर bus */
	WREG32_P(UVD_LMI_CTRL2, 0, ~(1 << 8));
	WREG32_P(UVD_RB_ARB_CTRL, 0, ~(1 << 3));
पूर्ण

/**
 * uvd_v1_0_ring_test - रेजिस्टर ग_लिखो test
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring poपूर्णांकer
 *
 * Test अगर we can successfully ग_लिखो to the context रेजिस्टर
 */
पूर्णांक uvd_v1_0_ring_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	uपूर्णांक32_t पंचांगp = 0;
	अचिन्हित i;
	पूर्णांक r;

	WREG32(UVD_CONTEXT_ID, 0xCAFEDEAD);
	r = radeon_ring_lock(rdev, ring, 3);
	अगर (r) अणु
		DRM_ERROR("radeon: cp failed to lock ring %d (%d).\n",
			  ring->idx, r);
		वापस r;
	पूर्ण
	radeon_ring_ग_लिखो(ring, PACKET0(UVD_CONTEXT_ID, 0));
	radeon_ring_ग_लिखो(ring, 0xDEADBEEF);
	radeon_ring_unlock_commit(rdev, ring, false);
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		पंचांगp = RREG32(UVD_CONTEXT_ID);
		अगर (पंचांगp == 0xDEADBEEF)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (i < rdev->usec_समयout) अणु
		DRM_INFO("ring test on %d succeeded in %d usecs\n",
			 ring->idx, i);
	पूर्ण अन्यथा अणु
		DRM_ERROR("radeon: ring %d test failed (0x%08X)\n",
			  ring->idx, पंचांगp);
		r = -EINVAL;
	पूर्ण
	वापस r;
पूर्ण

/**
 * uvd_v1_0_semaphore_emit - emit semaphore command
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring poपूर्णांकer
 * @semaphore: semaphore to emit commands क्रम
 * @emit_रुको: true अगर we should emit a रुको command
 *
 * Emit a semaphore command (either रुको or संकेत) to the UVD ring.
 */
bool uvd_v1_0_semaphore_emit(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_ring *ring,
			     काष्ठा radeon_semaphore *semaphore,
			     bool emit_रुको)
अणु
	/* disable semaphores क्रम UVD V1 hardware */
	वापस false;
पूर्ण

/**
 * uvd_v1_0_ib_execute - execute indirect buffer
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ib: indirect buffer to execute
 *
 * Write ring commands to execute the indirect buffer
 */
व्योम uvd_v1_0_ib_execute(काष्ठा radeon_device *rdev, काष्ठा radeon_ib *ib)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[ib->ring];

	radeon_ring_ग_लिखो(ring, PACKET0(UVD_RBC_IB_BASE, 0));
	radeon_ring_ग_लिखो(ring, ib->gpu_addr);
	radeon_ring_ग_लिखो(ring, PACKET0(UVD_RBC_IB_SIZE, 0));
	radeon_ring_ग_लिखो(ring, ib->length_dw);
पूर्ण

/**
 * uvd_v1_0_ib_test - test ib execution
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring poपूर्णांकer
 *
 * Test अगर we can successfully execute an IB
 */
पूर्णांक uvd_v1_0_ib_test(काष्ठा radeon_device *rdev, काष्ठा radeon_ring *ring)
अणु
	काष्ठा radeon_fence *fence = शून्य;
	पूर्णांक r;

	अगर (rdev->family < CHIP_RV740)
		r = radeon_set_uvd_घड़ीs(rdev, 10000, 10000);
	अन्यथा
		r = radeon_set_uvd_घड़ीs(rdev, 53300, 40000);
	अगर (r) अणु
		DRM_ERROR("radeon: failed to raise UVD clocks (%d).\n", r);
		वापस r;
	पूर्ण

	r = radeon_uvd_get_create_msg(rdev, ring->idx, 1, शून्य);
	अगर (r) अणु
		DRM_ERROR("radeon: failed to get create msg (%d).\n", r);
		जाओ error;
	पूर्ण

	r = radeon_uvd_get_destroy_msg(rdev, ring->idx, 1, &fence);
	अगर (r) अणु
		DRM_ERROR("radeon: failed to get destroy ib (%d).\n", r);
		जाओ error;
	पूर्ण

	r = radeon_fence_रुको_समयout(fence, false, usecs_to_jअगरfies(
		RADEON_USEC_IB_TEST_TIMEOUT));
	अगर (r < 0) अणु
		DRM_ERROR("radeon: fence wait failed (%d).\n", r);
		जाओ error;
	पूर्ण अन्यथा अगर (r == 0) अणु
		DRM_ERROR("radeon: fence wait timed out.\n");
		r = -ETIMEDOUT;
		जाओ error;
	पूर्ण
	r = 0;
	DRM_INFO("ib test on ring %d succeeded\n",  ring->idx);
error:
	radeon_fence_unref(&fence);
	radeon_set_uvd_घड़ीs(rdev, 0, 0);
	वापस r;
पूर्ण
