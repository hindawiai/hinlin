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
#समावेश "rv770d.h"

/**
 * uvd_v2_2_fence_emit - emit an fence & trap command
 *
 * @rdev: radeon_device poपूर्णांकer
 * @fence: fence to emit
 *
 * Write a fence and a trap command to the ring.
 */
व्योम uvd_v2_2_fence_emit(काष्ठा radeon_device *rdev,
			 काष्ठा radeon_fence *fence)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[fence->ring];
	uपूर्णांक64_t addr = rdev->fence_drv[fence->ring].gpu_addr;

	radeon_ring_ग_लिखो(ring, PACKET0(UVD_CONTEXT_ID, 0));
	radeon_ring_ग_लिखो(ring, fence->seq);
	radeon_ring_ग_लिखो(ring, PACKET0(UVD_GPCOM_VCPU_DATA0, 0));
	radeon_ring_ग_लिखो(ring, lower_32_bits(addr));
	radeon_ring_ग_लिखो(ring, PACKET0(UVD_GPCOM_VCPU_DATA1, 0));
	radeon_ring_ग_लिखो(ring, upper_32_bits(addr) & 0xff);
	radeon_ring_ग_लिखो(ring, PACKET0(UVD_GPCOM_VCPU_CMD, 0));
	radeon_ring_ग_लिखो(ring, 0);

	radeon_ring_ग_लिखो(ring, PACKET0(UVD_GPCOM_VCPU_DATA0, 0));
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, PACKET0(UVD_GPCOM_VCPU_DATA1, 0));
	radeon_ring_ग_लिखो(ring, 0);
	radeon_ring_ग_लिखो(ring, PACKET0(UVD_GPCOM_VCPU_CMD, 0));
	radeon_ring_ग_लिखो(ring, 2);
पूर्ण

/**
 * uvd_v2_2_semaphore_emit - emit semaphore command
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring poपूर्णांकer
 * @semaphore: semaphore to emit commands क्रम
 * @emit_रुको: true अगर we should emit a रुको command
 *
 * Emit a semaphore command (either रुको or संकेत) to the UVD ring.
 */
bool uvd_v2_2_semaphore_emit(काष्ठा radeon_device *rdev,
			     काष्ठा radeon_ring *ring,
			     काष्ठा radeon_semaphore *semaphore,
			     bool emit_रुको)
अणु
	uपूर्णांक64_t addr = semaphore->gpu_addr;

	radeon_ring_ग_लिखो(ring, PACKET0(UVD_SEMA_ADDR_LOW, 0));
	radeon_ring_ग_लिखो(ring, (addr >> 3) & 0x000FFFFF);

	radeon_ring_ग_लिखो(ring, PACKET0(UVD_SEMA_ADDR_HIGH, 0));
	radeon_ring_ग_लिखो(ring, (addr >> 23) & 0x000FFFFF);

	radeon_ring_ग_लिखो(ring, PACKET0(UVD_SEMA_CMD, 0));
	radeon_ring_ग_लिखो(ring, emit_रुको ? 1 : 0);

	वापस true;
पूर्ण

/**
 * uvd_v2_2_resume - memory controller programming
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Let the UVD memory controller know it's offsets
 */
पूर्णांक uvd_v2_2_resume(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक64_t addr;
	uपूर्णांक32_t chip_id, size;
	पूर्णांक r;

	/* RV770 uses V1.0 MC */
	अगर (rdev->family == CHIP_RV770)
		वापस uvd_v1_0_resume(rdev);

	r = radeon_uvd_resume(rdev);
	अगर (r)
		वापस r;

	/* program the VCPU memory controller bits 0-27 */
	addr = rdev->uvd.gpu_addr >> 3;
	size = RADEON_GPU_PAGE_ALIGN(rdev->uvd_fw->size + 4) >> 3;
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

	/* tell firmware which hardware it is running on */
	चयन (rdev->family) अणु
	शेष:
		वापस -EINVAL;
	हाल CHIP_RV710:
		chip_id = 0x01000005;
		अवरोध;
	हाल CHIP_RV730:
		chip_id = 0x01000006;
		अवरोध;
	हाल CHIP_RV740:
		chip_id = 0x01000007;
		अवरोध;
	हाल CHIP_CYPRESS:
	हाल CHIP_HEMLOCK:
		chip_id = 0x01000008;
		अवरोध;
	हाल CHIP_JUNIPER:
		chip_id = 0x01000009;
		अवरोध;
	हाल CHIP_REDWOOD:
		chip_id = 0x0100000a;
		अवरोध;
	हाल CHIP_CEDAR:
		chip_id = 0x0100000b;
		अवरोध;
	हाल CHIP_SUMO:
	हाल CHIP_SUMO2:
		chip_id = 0x0100000c;
		अवरोध;
	हाल CHIP_PALM:
		chip_id = 0x0100000e;
		अवरोध;
	हाल CHIP_CAYMAN:
		chip_id = 0x0100000f;
		अवरोध;
	हाल CHIP_BARTS:
		chip_id = 0x01000010;
		अवरोध;
	हाल CHIP_TURKS:
		chip_id = 0x01000011;
		अवरोध;
	हाल CHIP_CAICOS:
		chip_id = 0x01000012;
		अवरोध;
	हाल CHIP_TAHITI:
		chip_id = 0x01000014;
		अवरोध;
	हाल CHIP_VERDE:
		chip_id = 0x01000015;
		अवरोध;
	हाल CHIP_PITCAIRN:
	हाल CHIP_OLAND:
		chip_id = 0x01000016;
		अवरोध;
	हाल CHIP_ARUBA:
		chip_id = 0x01000017;
		अवरोध;
	पूर्ण
	WREG32(UVD_VCPU_CHIP_ID, chip_id);

	वापस 0;
पूर्ण
