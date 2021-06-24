<शैली गुरु>
/*
 * Copyright 2011 Christian Kथघnig.
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
 *    Christian Kथघnig <deathsimple@vodafone.de>
 */

#समावेश "radeon.h"
#समावेश "radeon_trace.h"

पूर्णांक radeon_semaphore_create(काष्ठा radeon_device *rdev,
			    काष्ठा radeon_semaphore **semaphore)
अणु
	पूर्णांक r;

	*semaphore = kदो_स्मृति(माप(काष्ठा radeon_semaphore), GFP_KERNEL);
	अगर (*semaphore == शून्य) अणु
		वापस -ENOMEM;
	पूर्ण
	r = radeon_sa_bo_new(rdev, &rdev->ring_पंचांगp_bo,
			     &(*semaphore)->sa_bo, 8, 8);
	अगर (r) अणु
		kमुक्त(*semaphore);
		*semaphore = शून्य;
		वापस r;
	पूर्ण
	(*semaphore)->रुकोers = 0;
	(*semaphore)->gpu_addr = radeon_sa_bo_gpu_addr((*semaphore)->sa_bo);

	*((uपूर्णांक64_t *)radeon_sa_bo_cpu_addr((*semaphore)->sa_bo)) = 0;

	वापस 0;
पूर्ण

bool radeon_semaphore_emit_संकेत(काष्ठा radeon_device *rdev, पूर्णांक ridx,
				  काष्ठा radeon_semaphore *semaphore)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[ridx];

	trace_radeon_semaphore_संकेतe(ridx, semaphore);

	अगर (radeon_semaphore_ring_emit(rdev, ridx, ring, semaphore, false)) अणु
		--semaphore->रुकोers;

		/* क्रम debugging lockup only, used by sysfs debug files */
		ring->last_semaphore_संकेत_addr = semaphore->gpu_addr;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

bool radeon_semaphore_emit_रुको(काष्ठा radeon_device *rdev, पूर्णांक ridx,
				काष्ठा radeon_semaphore *semaphore)
अणु
	काष्ठा radeon_ring *ring = &rdev->ring[ridx];

	trace_radeon_semaphore_रुको(ridx, semaphore);

	अगर (radeon_semaphore_ring_emit(rdev, ridx, ring, semaphore, true)) अणु
		++semaphore->रुकोers;

		/* क्रम debugging lockup only, used by sysfs debug files */
		ring->last_semaphore_रुको_addr = semaphore->gpu_addr;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

व्योम radeon_semaphore_मुक्त(काष्ठा radeon_device *rdev,
			   काष्ठा radeon_semaphore **semaphore,
			   काष्ठा radeon_fence *fence)
अणु
	अगर (semaphore == शून्य || *semaphore == शून्य) अणु
		वापस;
	पूर्ण
	अगर ((*semaphore)->रुकोers > 0) अणु
		dev_err(rdev->dev, "semaphore %p has more waiters than signalers,"
			" hardware lockup imminent!\n", *semaphore);
	पूर्ण
	radeon_sa_bo_मुक्त(rdev, &(*semaphore)->sa_bo, fence);
	kमुक्त(*semaphore);
	*semaphore = शून्य;
पूर्ण
