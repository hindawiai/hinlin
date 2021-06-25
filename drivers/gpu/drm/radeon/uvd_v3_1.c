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

#समावेश "radeon.h"
#समावेश "radeon_asic.h"
#समावेश "nid.h"

/**
 * uvd_v3_1_semaphore_emit - emit semaphore command
 *
 * @rdev: radeon_device poपूर्णांकer
 * @ring: radeon_ring poपूर्णांकer
 * @semaphore: semaphore to emit commands क्रम
 * @emit_रुको: true अगर we should emit a रुको command
 *
 * Emit a semaphore command (either रुको or संकेत) to the UVD ring.
 */
bool uvd_v3_1_semaphore_emit(काष्ठा radeon_device *rdev,
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
	radeon_ring_ग_लिखो(ring, 0x80 | (emit_रुको ? 1 : 0));

	वापस true;
पूर्ण
