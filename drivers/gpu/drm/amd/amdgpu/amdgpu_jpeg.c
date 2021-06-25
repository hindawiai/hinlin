<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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

#समावेश "amdgpu.h"
#समावेश "amdgpu_jpeg.h"
#समावेश "amdgpu_pm.h"
#समावेश "soc15d.h"
#समावेश "soc15_common.h"

#घोषणा JPEG_IDLE_TIMEOUT	msecs_to_jअगरfies(1000)

अटल व्योम amdgpu_jpeg_idle_work_handler(काष्ठा work_काष्ठा *work);

पूर्णांक amdgpu_jpeg_sw_init(काष्ठा amdgpu_device *adev)
अणु
	INIT_DELAYED_WORK(&adev->jpeg.idle_work, amdgpu_jpeg_idle_work_handler);
	mutex_init(&adev->jpeg.jpeg_pg_lock);
	atomic_set(&adev->jpeg.total_submission_cnt, 0);

	वापस 0;
पूर्ण

पूर्णांक amdgpu_jpeg_sw_fini(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	cancel_delayed_work_sync(&adev->jpeg.idle_work);

	क्रम (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) अणु
		अगर (adev->jpeg.harvest_config & (1 << i))
			जारी;

		amdgpu_ring_fini(&adev->jpeg.inst[i].ring_dec);
	पूर्ण

	mutex_destroy(&adev->jpeg.jpeg_pg_lock);

	वापस 0;
पूर्ण

पूर्णांक amdgpu_jpeg_suspend(काष्ठा amdgpu_device *adev)
अणु
	cancel_delayed_work_sync(&adev->jpeg.idle_work);

	वापस 0;
पूर्ण

पूर्णांक amdgpu_jpeg_resume(काष्ठा amdgpu_device *adev)
अणु
	वापस 0;
पूर्ण

अटल व्योम amdgpu_jpeg_idle_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा amdgpu_device *adev =
		container_of(work, काष्ठा amdgpu_device, jpeg.idle_work.work);
	अचिन्हित पूर्णांक fences = 0;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < adev->jpeg.num_jpeg_inst; ++i) अणु
		अगर (adev->jpeg.harvest_config & (1 << i))
			जारी;

		fences += amdgpu_fence_count_emitted(&adev->jpeg.inst[i].ring_dec);
	पूर्ण

	अगर (!fences && !atomic_पढ़ो(&adev->jpeg.total_submission_cnt))
		amdgpu_device_ip_set_घातergating_state(adev, AMD_IP_BLOCK_TYPE_JPEG,
						       AMD_PG_STATE_GATE);
	अन्यथा
		schedule_delayed_work(&adev->jpeg.idle_work, JPEG_IDLE_TIMEOUT);
पूर्ण

व्योम amdgpu_jpeg_ring_begin_use(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	atomic_inc(&adev->jpeg.total_submission_cnt);
	cancel_delayed_work_sync(&adev->jpeg.idle_work);

	mutex_lock(&adev->jpeg.jpeg_pg_lock);
	amdgpu_device_ip_set_घातergating_state(adev, AMD_IP_BLOCK_TYPE_JPEG,
						       AMD_PG_STATE_UNGATE);
	mutex_unlock(&adev->jpeg.jpeg_pg_lock);
पूर्ण

व्योम amdgpu_jpeg_ring_end_use(काष्ठा amdgpu_ring *ring)
अणु
	atomic_dec(&ring->adev->jpeg.total_submission_cnt);
	schedule_delayed_work(&ring->adev->jpeg.idle_work, JPEG_IDLE_TIMEOUT);
पूर्ण

पूर्णांक amdgpu_jpeg_dec_ring_test_ring(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t पंचांगp = 0;
	अचिन्हित i;
	पूर्णांक r;

	WREG32(adev->jpeg.inst[ring->me].बाह्यal.jpeg_pitch, 0xCAFEDEAD);
	r = amdgpu_ring_alloc(ring, 3);
	अगर (r)
		वापस r;

	amdgpu_ring_ग_लिखो(ring, PACKET0(adev->jpeg.पूर्णांकernal.jpeg_pitch, 0));
	amdgpu_ring_ग_लिखो(ring, 0xDEADBEEF);
	amdgpu_ring_commit(ring);

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		पंचांगp = RREG32(adev->jpeg.inst[ring->me].बाह्यal.jpeg_pitch);
		अगर (पंचांगp == 0xDEADBEEF)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (i >= adev->usec_समयout)
		r = -ETIMEDOUT;

	वापस r;
पूर्ण

अटल पूर्णांक amdgpu_jpeg_dec_set_reg(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t handle,
		काष्ठा dma_fence **fence)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	काष्ठा amdgpu_job *job;
	काष्ठा amdgpu_ib *ib;
	काष्ठा dma_fence *f = शून्य;
	स्थिर अचिन्हित ib_size_dw = 16;
	पूर्णांक i, r;

	r = amdgpu_job_alloc_with_ib(ring->adev, ib_size_dw * 4,
					AMDGPU_IB_POOL_सूचीECT, &job);
	अगर (r)
		वापस r;

	ib = &job->ibs[0];

	ib->ptr[0] = PACKETJ(adev->jpeg.पूर्णांकernal.jpeg_pitch, 0, 0, PACKETJ_TYPE0);
	ib->ptr[1] = 0xDEADBEEF;
	क्रम (i = 2; i < 16; i += 2) अणु
		ib->ptr[i] = PACKETJ(0, 0, 0, PACKETJ_TYPE6);
		ib->ptr[i+1] = 0;
	पूर्ण
	ib->length_dw = 16;

	r = amdgpu_job_submit_direct(job, ring, &f);
	अगर (r)
		जाओ err;

	अगर (fence)
		*fence = dma_fence_get(f);
	dma_fence_put(f);

	वापस 0;

err:
	amdgpu_job_मुक्त(job);
	वापस r;
पूर्ण

पूर्णांक amdgpu_jpeg_dec_ring_test_ib(काष्ठा amdgpu_ring *ring, दीर्घ समयout)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t पंचांगp = 0;
	अचिन्हित i;
	काष्ठा dma_fence *fence = शून्य;
	दीर्घ r = 0;

	r = amdgpu_jpeg_dec_set_reg(ring, 1, &fence);
	अगर (r)
		जाओ error;

	r = dma_fence_रुको_समयout(fence, false, समयout);
	अगर (r == 0) अणु
		r = -ETIMEDOUT;
		जाओ error;
	पूर्ण अन्यथा अगर (r < 0) अणु
		जाओ error;
	पूर्ण अन्यथा अणु
		r = 0;
	पूर्ण

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		पंचांगp = RREG32(adev->jpeg.inst[ring->me].बाह्यal.jpeg_pitch);
		अगर (पंचांगp == 0xDEADBEEF)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (i >= adev->usec_समयout)
		r = -ETIMEDOUT;

	dma_fence_put(fence);
error:
	वापस r;
पूर्ण
