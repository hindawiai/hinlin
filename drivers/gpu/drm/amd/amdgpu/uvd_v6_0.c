<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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

#समावेश "amdgpu.h"
#समावेश "amdgpu_uvd.h"
#समावेश "vid.h"
#समावेश "uvd/uvd_6_0_d.h"
#समावेश "uvd/uvd_6_0_sh_mask.h"
#समावेश "oss/oss_2_0_d.h"
#समावेश "oss/oss_2_0_sh_mask.h"
#समावेश "smu/smu_7_1_3_d.h"
#समावेश "smu/smu_7_1_3_sh_mask.h"
#समावेश "bif/bif_5_1_d.h"
#समावेश "gmc/gmc_8_1_d.h"
#समावेश "vi.h"
#समावेश "ivsrcid/ivsrcid_vislands30.h"

/* Polaris10/11/12 firmware version */
#घोषणा FW_1_130_16 ((1 << 24) | (130 << 16) | (16 << 8))

अटल व्योम uvd_v6_0_set_ring_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम uvd_v6_0_set_enc_ring_funcs(काष्ठा amdgpu_device *adev);

अटल व्योम uvd_v6_0_set_irq_funcs(काष्ठा amdgpu_device *adev);
अटल पूर्णांक uvd_v6_0_start(काष्ठा amdgpu_device *adev);
अटल व्योम uvd_v6_0_stop(काष्ठा amdgpu_device *adev);
अटल व्योम uvd_v6_0_set_sw_घड़ी_gating(काष्ठा amdgpu_device *adev);
अटल पूर्णांक uvd_v6_0_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state);
अटल व्योम uvd_v6_0_enable_mgcg(काष्ठा amdgpu_device *adev,
				 bool enable);

/**
* uvd_v6_0_enc_support - get encode support status
*
* @adev: amdgpu_device poपूर्णांकer
*
* Returns the current hardware encode support status
*/
अटल अंतरभूत bool uvd_v6_0_enc_support(काष्ठा amdgpu_device *adev)
अणु
	वापस ((adev->asic_type >= CHIP_POLARIS10) &&
			(adev->asic_type <= CHIP_VEGAM) &&
			(!adev->uvd.fw_version || adev->uvd.fw_version >= FW_1_130_16));
पूर्ण

/**
 * uvd_v6_0_ring_get_rptr - get पढ़ो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware पढ़ो poपूर्णांकer
 */
अटल uपूर्णांक64_t uvd_v6_0_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	वापस RREG32(mmUVD_RBC_RB_RPTR);
पूर्ण

/**
 * uvd_v6_0_enc_ring_get_rptr - get enc पढ़ो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware enc पढ़ो poपूर्णांकer
 */
अटल uपूर्णांक64_t uvd_v6_0_enc_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring == &adev->uvd.inst->ring_enc[0])
		वापस RREG32(mmUVD_RB_RPTR);
	अन्यथा
		वापस RREG32(mmUVD_RB_RPTR2);
पूर्ण
/**
 * uvd_v6_0_ring_get_wptr - get ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware ग_लिखो poपूर्णांकer
 */
अटल uपूर्णांक64_t uvd_v6_0_ring_get_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	वापस RREG32(mmUVD_RBC_RB_WPTR);
पूर्ण

/**
 * uvd_v6_0_enc_ring_get_wptr - get enc ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware enc ग_लिखो poपूर्णांकer
 */
अटल uपूर्णांक64_t uvd_v6_0_enc_ring_get_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring == &adev->uvd.inst->ring_enc[0])
		वापस RREG32(mmUVD_RB_WPTR);
	अन्यथा
		वापस RREG32(mmUVD_RB_WPTR2);
पूर्ण

/**
 * uvd_v6_0_ring_set_wptr - set ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Commits the ग_लिखो poपूर्णांकer to the hardware
 */
अटल व्योम uvd_v6_0_ring_set_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	WREG32(mmUVD_RBC_RB_WPTR, lower_32_bits(ring->wptr));
पूर्ण

/**
 * uvd_v6_0_enc_ring_set_wptr - set enc ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Commits the enc ग_लिखो poपूर्णांकer to the hardware
 */
अटल व्योम uvd_v6_0_enc_ring_set_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring == &adev->uvd.inst->ring_enc[0])
		WREG32(mmUVD_RB_WPTR,
			lower_32_bits(ring->wptr));
	अन्यथा
		WREG32(mmUVD_RB_WPTR2,
			lower_32_bits(ring->wptr));
पूर्ण

/**
 * uvd_v6_0_enc_ring_test_ring - test अगर UVD ENC ring is working
 *
 * @ring: the engine to test on
 *
 */
अटल पूर्णांक uvd_v6_0_enc_ring_test_ring(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t rptr;
	अचिन्हित i;
	पूर्णांक r;

	r = amdgpu_ring_alloc(ring, 16);
	अगर (r)
		वापस r;

	rptr = amdgpu_ring_get_rptr(ring);

	amdgpu_ring_ग_लिखो(ring, HEVC_ENC_CMD_END);
	amdgpu_ring_commit(ring);

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर (amdgpu_ring_get_rptr(ring) != rptr)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (i >= adev->usec_समयout)
		r = -ETIMEDOUT;

	वापस r;
पूर्ण

/**
 * uvd_v6_0_enc_get_create_msg - generate a UVD ENC create msg
 *
 * @ring: ring we should submit the msg to
 * @handle: session handle to use
 * @bo: amdgpu object क्रम which we query the offset
 * @fence: optional fence to वापस
 *
 * Open up a stream क्रम HW test
 */
अटल पूर्णांक uvd_v6_0_enc_get_create_msg(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t handle,
				       काष्ठा amdgpu_bo *bo,
				       काष्ठा dma_fence **fence)
अणु
	स्थिर अचिन्हित ib_size_dw = 16;
	काष्ठा amdgpu_job *job;
	काष्ठा amdgpu_ib *ib;
	काष्ठा dma_fence *f = शून्य;
	uपूर्णांक64_t addr;
	पूर्णांक i, r;

	r = amdgpu_job_alloc_with_ib(ring->adev, ib_size_dw * 4,
					AMDGPU_IB_POOL_सूचीECT, &job);
	अगर (r)
		वापस r;

	ib = &job->ibs[0];
	addr = amdgpu_bo_gpu_offset(bo);

	ib->length_dw = 0;
	ib->ptr[ib->length_dw++] = 0x00000018;
	ib->ptr[ib->length_dw++] = 0x00000001; /* session info */
	ib->ptr[ib->length_dw++] = handle;
	ib->ptr[ib->length_dw++] = 0x00010000;
	ib->ptr[ib->length_dw++] = upper_32_bits(addr);
	ib->ptr[ib->length_dw++] = addr;

	ib->ptr[ib->length_dw++] = 0x00000014;
	ib->ptr[ib->length_dw++] = 0x00000002; /* task info */
	ib->ptr[ib->length_dw++] = 0x0000001c;
	ib->ptr[ib->length_dw++] = 0x00000001;
	ib->ptr[ib->length_dw++] = 0x00000000;

	ib->ptr[ib->length_dw++] = 0x00000008;
	ib->ptr[ib->length_dw++] = 0x08000001; /* op initialize */

	क्रम (i = ib->length_dw; i < ib_size_dw; ++i)
		ib->ptr[i] = 0x0;

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

/**
 * uvd_v6_0_enc_get_destroy_msg - generate a UVD ENC destroy msg
 *
 * @ring: ring we should submit the msg to
 * @handle: session handle to use
 * @bo: amdgpu object क्रम which we query the offset
 * @fence: optional fence to वापस
 *
 * Close up a stream क्रम HW test or अगर userspace failed to करो so
 */
अटल पूर्णांक uvd_v6_0_enc_get_destroy_msg(काष्ठा amdgpu_ring *ring,
					uपूर्णांक32_t handle,
					काष्ठा amdgpu_bo *bo,
					काष्ठा dma_fence **fence)
अणु
	स्थिर अचिन्हित ib_size_dw = 16;
	काष्ठा amdgpu_job *job;
	काष्ठा amdgpu_ib *ib;
	काष्ठा dma_fence *f = शून्य;
	uपूर्णांक64_t addr;
	पूर्णांक i, r;

	r = amdgpu_job_alloc_with_ib(ring->adev, ib_size_dw * 4,
					AMDGPU_IB_POOL_सूचीECT, &job);
	अगर (r)
		वापस r;

	ib = &job->ibs[0];
	addr = amdgpu_bo_gpu_offset(bo);

	ib->length_dw = 0;
	ib->ptr[ib->length_dw++] = 0x00000018;
	ib->ptr[ib->length_dw++] = 0x00000001; /* session info */
	ib->ptr[ib->length_dw++] = handle;
	ib->ptr[ib->length_dw++] = 0x00010000;
	ib->ptr[ib->length_dw++] = upper_32_bits(addr);
	ib->ptr[ib->length_dw++] = addr;

	ib->ptr[ib->length_dw++] = 0x00000014;
	ib->ptr[ib->length_dw++] = 0x00000002; /* task info */
	ib->ptr[ib->length_dw++] = 0x0000001c;
	ib->ptr[ib->length_dw++] = 0x00000001;
	ib->ptr[ib->length_dw++] = 0x00000000;

	ib->ptr[ib->length_dw++] = 0x00000008;
	ib->ptr[ib->length_dw++] = 0x08000002; /* op बंद session */

	क्रम (i = ib->length_dw; i < ib_size_dw; ++i)
		ib->ptr[i] = 0x0;

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

/**
 * uvd_v6_0_enc_ring_test_ib - test अगर UVD ENC IBs are working
 *
 * @ring: the engine to test on
 * @समयout: समयout value in jअगरfies, or MAX_SCHEDULE_TIMEOUT
 *
 */
अटल पूर्णांक uvd_v6_0_enc_ring_test_ib(काष्ठा amdgpu_ring *ring, दीर्घ समयout)
अणु
	काष्ठा dma_fence *fence = शून्य;
	काष्ठा amdgpu_bo *bo = शून्य;
	दीर्घ r;

	r = amdgpu_bo_create_reserved(ring->adev, 128 * 1024, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &bo, शून्य, शून्य);
	अगर (r)
		वापस r;

	r = uvd_v6_0_enc_get_create_msg(ring, 1, bo, शून्य);
	अगर (r)
		जाओ error;

	r = uvd_v6_0_enc_get_destroy_msg(ring, 1, bo, &fence);
	अगर (r)
		जाओ error;

	r = dma_fence_रुको_समयout(fence, false, समयout);
	अगर (r == 0)
		r = -ETIMEDOUT;
	अन्यथा अगर (r > 0)
		r = 0;

error:
	dma_fence_put(fence);
	amdgpu_bo_unpin(bo);
	amdgpu_bo_unreserve(bo);
	amdgpu_bo_unref(&bo);
	वापस r;
पूर्ण

अटल पूर्णांक uvd_v6_0_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	adev->uvd.num_uvd_inst = 1;

	अगर (!(adev->flags & AMD_IS_APU) &&
	    (RREG32_SMC(ixCC_HARVEST_FUSES) & CC_HARVEST_FUSES__UVD_DISABLE_MASK))
		वापस -ENOENT;

	uvd_v6_0_set_ring_funcs(adev);

	अगर (uvd_v6_0_enc_support(adev)) अणु
		adev->uvd.num_enc_rings = 2;
		uvd_v6_0_set_enc_ring_funcs(adev);
	पूर्ण

	uvd_v6_0_set_irq_funcs(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक uvd_v6_0_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_ring *ring;
	पूर्णांक i, r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	/* UVD TRAP */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_UVD_SYSTEM_MESSAGE, &adev->uvd.inst->irq);
	अगर (r)
		वापस r;

	/* UVD ENC TRAP */
	अगर (uvd_v6_0_enc_support(adev)) अणु
		क्रम (i = 0; i < adev->uvd.num_enc_rings; ++i) अणु
			r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, i + VISLANDS30_IV_SRCID_UVD_ENC_GEN_PURP, &adev->uvd.inst->irq);
			अगर (r)
				वापस r;
		पूर्ण
	पूर्ण

	r = amdgpu_uvd_sw_init(adev);
	अगर (r)
		वापस r;

	अगर (!uvd_v6_0_enc_support(adev)) अणु
		क्रम (i = 0; i < adev->uvd.num_enc_rings; ++i)
			adev->uvd.inst->ring_enc[i].funcs = शून्य;

		adev->uvd.inst->irq.num_types = 1;
		adev->uvd.num_enc_rings = 0;

		DRM_INFO("UVD ENC is disabled\n");
	पूर्ण

	ring = &adev->uvd.inst->ring;
	प्र_लिखो(ring->name, "uvd");
	r = amdgpu_ring_init(adev, ring, 512, &adev->uvd.inst->irq, 0,
			     AMDGPU_RING_PRIO_DEFAULT, शून्य);
	अगर (r)
		वापस r;

	r = amdgpu_uvd_resume(adev);
	अगर (r)
		वापस r;

	अगर (uvd_v6_0_enc_support(adev)) अणु
		क्रम (i = 0; i < adev->uvd.num_enc_rings; ++i) अणु
			ring = &adev->uvd.inst->ring_enc[i];
			प्र_लिखो(ring->name, "uvd_enc%d", i);
			r = amdgpu_ring_init(adev, ring, 512,
					     &adev->uvd.inst->irq, 0,
					     AMDGPU_RING_PRIO_DEFAULT, शून्य);
			अगर (r)
				वापस r;
		पूर्ण
	पूर्ण

	r = amdgpu_uvd_entity_init(adev);

	वापस r;
पूर्ण

अटल पूर्णांक uvd_v6_0_sw_fini(व्योम *handle)
अणु
	पूर्णांक i, r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = amdgpu_uvd_suspend(adev);
	अगर (r)
		वापस r;

	अगर (uvd_v6_0_enc_support(adev)) अणु
		क्रम (i = 0; i < adev->uvd.num_enc_rings; ++i)
			amdgpu_ring_fini(&adev->uvd.inst->ring_enc[i]);
	पूर्ण

	वापस amdgpu_uvd_sw_fini(adev);
पूर्ण

/**
 * uvd_v6_0_hw_init - start and test UVD block
 *
 * @handle: handle used to pass amdgpu_device poपूर्णांकer
 *
 * Initialize the hardware, boot up the VCPU and करो some testing
 */
अटल पूर्णांक uvd_v6_0_hw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा amdgpu_ring *ring = &adev->uvd.inst->ring;
	uपूर्णांक32_t पंचांगp;
	पूर्णांक i, r;

	amdgpu_asic_set_uvd_घड़ीs(adev, 10000, 10000);
	uvd_v6_0_set_घड़ीgating_state(adev, AMD_CG_STATE_UNGATE);
	uvd_v6_0_enable_mgcg(adev, true);

	r = amdgpu_ring_test_helper(ring);
	अगर (r)
		जाओ करोne;

	r = amdgpu_ring_alloc(ring, 10);
	अगर (r) अणु
		DRM_ERROR("amdgpu: ring failed to lock UVD ring (%d).\n", r);
		जाओ करोne;
	पूर्ण

	पंचांगp = PACKET0(mmUVD_SEMA_WAIT_FAULT_TIMEOUT_CNTL, 0);
	amdgpu_ring_ग_लिखो(ring, पंचांगp);
	amdgpu_ring_ग_लिखो(ring, 0xFFFFF);

	पंचांगp = PACKET0(mmUVD_SEMA_WAIT_INCOMPLETE_TIMEOUT_CNTL, 0);
	amdgpu_ring_ग_लिखो(ring, पंचांगp);
	amdgpu_ring_ग_लिखो(ring, 0xFFFFF);

	पंचांगp = PACKET0(mmUVD_SEMA_SIGNAL_INCOMPLETE_TIMEOUT_CNTL, 0);
	amdgpu_ring_ग_लिखो(ring, पंचांगp);
	amdgpu_ring_ग_लिखो(ring, 0xFFFFF);

	/* Clear समयout status bits */
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_SEMA_TIMEOUT_STATUS, 0));
	amdgpu_ring_ग_लिखो(ring, 0x8);

	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_SEMA_CNTL, 0));
	amdgpu_ring_ग_लिखो(ring, 3);

	amdgpu_ring_commit(ring);

	अगर (uvd_v6_0_enc_support(adev)) अणु
		क्रम (i = 0; i < adev->uvd.num_enc_rings; ++i) अणु
			ring = &adev->uvd.inst->ring_enc[i];
			r = amdgpu_ring_test_helper(ring);
			अगर (r)
				जाओ करोne;
		पूर्ण
	पूर्ण

करोne:
	अगर (!r) अणु
		अगर (uvd_v6_0_enc_support(adev))
			DRM_INFO("UVD and UVD ENC initialized successfully.\n");
		अन्यथा
			DRM_INFO("UVD initialized successfully.\n");
	पूर्ण

	वापस r;
पूर्ण

/**
 * uvd_v6_0_hw_fini - stop the hardware block
 *
 * @handle: handle used to pass amdgpu_device poपूर्णांकer
 *
 * Stop the UVD block, mark ring as not पढ़ोy any more
 */
अटल पूर्णांक uvd_v6_0_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (RREG32(mmUVD_STATUS) != 0)
		uvd_v6_0_stop(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक uvd_v6_0_suspend(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = uvd_v6_0_hw_fini(adev);
	अगर (r)
		वापस r;

	वापस amdgpu_uvd_suspend(adev);
पूर्ण

अटल पूर्णांक uvd_v6_0_resume(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = amdgpu_uvd_resume(adev);
	अगर (r)
		वापस r;

	वापस uvd_v6_0_hw_init(adev);
पूर्ण

/**
 * uvd_v6_0_mc_resume - memory controller programming
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Let the UVD memory controller know it's offsets
 */
अटल व्योम uvd_v6_0_mc_resume(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक64_t offset;
	uपूर्णांक32_t size;

	/* program memory controller bits 0-27 */
	WREG32(mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW,
			lower_32_bits(adev->uvd.inst->gpu_addr));
	WREG32(mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH,
			upper_32_bits(adev->uvd.inst->gpu_addr));

	offset = AMDGPU_UVD_FIRMWARE_OFFSET;
	size = AMDGPU_UVD_FIRMWARE_SIZE(adev);
	WREG32(mmUVD_VCPU_CACHE_OFFSET0, offset >> 3);
	WREG32(mmUVD_VCPU_CACHE_SIZE0, size);

	offset += size;
	size = AMDGPU_UVD_HEAP_SIZE;
	WREG32(mmUVD_VCPU_CACHE_OFFSET1, offset >> 3);
	WREG32(mmUVD_VCPU_CACHE_SIZE1, size);

	offset += size;
	size = AMDGPU_UVD_STACK_SIZE +
	       (AMDGPU_UVD_SESSION_SIZE * adev->uvd.max_handles);
	WREG32(mmUVD_VCPU_CACHE_OFFSET2, offset >> 3);
	WREG32(mmUVD_VCPU_CACHE_SIZE2, size);

	WREG32(mmUVD_UDEC_ADDR_CONFIG, adev->gfx.config.gb_addr_config);
	WREG32(mmUVD_UDEC_DB_ADDR_CONFIG, adev->gfx.config.gb_addr_config);
	WREG32(mmUVD_UDEC_DBW_ADDR_CONFIG, adev->gfx.config.gb_addr_config);

	WREG32(mmUVD_GP_SCRATCH4, adev->uvd.max_handles);
पूर्ण

#अगर 0
अटल व्योम cz_set_uvd_घड़ी_gating_branches(काष्ठा amdgpu_device *adev,
		bool enable)
अणु
	u32 data, data1;

	data = RREG32(mmUVD_CGC_GATE);
	data1 = RREG32(mmUVD_SUVD_CGC_GATE);
	अगर (enable) अणु
		data |= UVD_CGC_GATE__SYS_MASK |
				UVD_CGC_GATE__UDEC_MASK |
				UVD_CGC_GATE__MPEG2_MASK |
				UVD_CGC_GATE__RBC_MASK |
				UVD_CGC_GATE__LMI_MC_MASK |
				UVD_CGC_GATE__IDCT_MASK |
				UVD_CGC_GATE__MPRD_MASK |
				UVD_CGC_GATE__MPC_MASK |
				UVD_CGC_GATE__LBSI_MASK |
				UVD_CGC_GATE__LRBBM_MASK |
				UVD_CGC_GATE__UDEC_RE_MASK |
				UVD_CGC_GATE__UDEC_CM_MASK |
				UVD_CGC_GATE__UDEC_IT_MASK |
				UVD_CGC_GATE__UDEC_DB_MASK |
				UVD_CGC_GATE__UDEC_MP_MASK |
				UVD_CGC_GATE__WCB_MASK |
				UVD_CGC_GATE__VCPU_MASK |
				UVD_CGC_GATE__SCPU_MASK;
		data1 |= UVD_SUVD_CGC_GATE__SRE_MASK |
				UVD_SUVD_CGC_GATE__SIT_MASK |
				UVD_SUVD_CGC_GATE__SMP_MASK |
				UVD_SUVD_CGC_GATE__SCM_MASK |
				UVD_SUVD_CGC_GATE__SDB_MASK |
				UVD_SUVD_CGC_GATE__SRE_H264_MASK |
				UVD_SUVD_CGC_GATE__SRE_HEVC_MASK |
				UVD_SUVD_CGC_GATE__SIT_H264_MASK |
				UVD_SUVD_CGC_GATE__SIT_HEVC_MASK |
				UVD_SUVD_CGC_GATE__SCM_H264_MASK |
				UVD_SUVD_CGC_GATE__SCM_HEVC_MASK |
				UVD_SUVD_CGC_GATE__SDB_H264_MASK |
				UVD_SUVD_CGC_GATE__SDB_HEVC_MASK;
	पूर्ण अन्यथा अणु
		data &= ~(UVD_CGC_GATE__SYS_MASK |
				UVD_CGC_GATE__UDEC_MASK |
				UVD_CGC_GATE__MPEG2_MASK |
				UVD_CGC_GATE__RBC_MASK |
				UVD_CGC_GATE__LMI_MC_MASK |
				UVD_CGC_GATE__LMI_UMC_MASK |
				UVD_CGC_GATE__IDCT_MASK |
				UVD_CGC_GATE__MPRD_MASK |
				UVD_CGC_GATE__MPC_MASK |
				UVD_CGC_GATE__LBSI_MASK |
				UVD_CGC_GATE__LRBBM_MASK |
				UVD_CGC_GATE__UDEC_RE_MASK |
				UVD_CGC_GATE__UDEC_CM_MASK |
				UVD_CGC_GATE__UDEC_IT_MASK |
				UVD_CGC_GATE__UDEC_DB_MASK |
				UVD_CGC_GATE__UDEC_MP_MASK |
				UVD_CGC_GATE__WCB_MASK |
				UVD_CGC_GATE__VCPU_MASK |
				UVD_CGC_GATE__SCPU_MASK);
		data1 &= ~(UVD_SUVD_CGC_GATE__SRE_MASK |
				UVD_SUVD_CGC_GATE__SIT_MASK |
				UVD_SUVD_CGC_GATE__SMP_MASK |
				UVD_SUVD_CGC_GATE__SCM_MASK |
				UVD_SUVD_CGC_GATE__SDB_MASK |
				UVD_SUVD_CGC_GATE__SRE_H264_MASK |
				UVD_SUVD_CGC_GATE__SRE_HEVC_MASK |
				UVD_SUVD_CGC_GATE__SIT_H264_MASK |
				UVD_SUVD_CGC_GATE__SIT_HEVC_MASK |
				UVD_SUVD_CGC_GATE__SCM_H264_MASK |
				UVD_SUVD_CGC_GATE__SCM_HEVC_MASK |
				UVD_SUVD_CGC_GATE__SDB_H264_MASK |
				UVD_SUVD_CGC_GATE__SDB_HEVC_MASK);
	पूर्ण
	WREG32(mmUVD_CGC_GATE, data);
	WREG32(mmUVD_SUVD_CGC_GATE, data1);
पूर्ण
#पूर्ण_अगर

/**
 * uvd_v6_0_start - start UVD block
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Setup and start the UVD block
 */
अटल पूर्णांक uvd_v6_0_start(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring = &adev->uvd.inst->ring;
	uपूर्णांक32_t rb_bufsz, पंचांगp;
	uपूर्णांक32_t lmi_swap_cntl;
	uपूर्णांक32_t mp_swap_cntl;
	पूर्णांक i, j, r;

	/* disable DPG */
	WREG32_P(mmUVD_POWER_STATUS, 0, ~UVD_POWER_STATUS__UVD_PG_MODE_MASK);

	/* disable byte swapping */
	lmi_swap_cntl = 0;
	mp_swap_cntl = 0;

	uvd_v6_0_mc_resume(adev);

	/* disable पूर्णांकerupt */
	WREG32_FIELD(UVD_MASTINT_EN, VCPU_EN, 0);

	/* stall UMC and रेजिस्टर bus beक्रमe resetting VCPU */
	WREG32_FIELD(UVD_LMI_CTRL2, STALL_ARB_UMC, 1);
	mdelay(1);

	/* put LMI, VCPU, RBC etc... पूर्णांकo reset */
	WREG32(mmUVD_SOFT_RESET,
		UVD_SOFT_RESET__LMI_SOFT_RESET_MASK |
		UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK |
		UVD_SOFT_RESET__LBSI_SOFT_RESET_MASK |
		UVD_SOFT_RESET__RBC_SOFT_RESET_MASK |
		UVD_SOFT_RESET__CSM_SOFT_RESET_MASK |
		UVD_SOFT_RESET__CXW_SOFT_RESET_MASK |
		UVD_SOFT_RESET__TAP_SOFT_RESET_MASK |
		UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK);
	mdelay(5);

	/* take UVD block out of reset */
	WREG32_FIELD(SRBM_SOFT_RESET, SOFT_RESET_UVD, 0);
	mdelay(5);

	/* initialize UVD memory controller */
	WREG32(mmUVD_LMI_CTRL,
		(0x40 << UVD_LMI_CTRL__WRITE_CLEAN_TIMER__SHIFT) |
		UVD_LMI_CTRL__WRITE_CLEAN_TIMER_EN_MASK |
		UVD_LMI_CTRL__DATA_COHERENCY_EN_MASK |
		UVD_LMI_CTRL__VCPU_DATA_COHERENCY_EN_MASK |
		UVD_LMI_CTRL__REQ_MODE_MASK |
		UVD_LMI_CTRL__DISABLE_ON_FWV_FAIL_MASK);

#अगर_घोषित __BIG_ENDIAN
	/* swap (8 in 32) RB and IB */
	lmi_swap_cntl = 0xa;
	mp_swap_cntl = 0;
#पूर्ण_अगर
	WREG32(mmUVD_LMI_SWAP_CNTL, lmi_swap_cntl);
	WREG32(mmUVD_MP_SWAP_CNTL, mp_swap_cntl);

	WREG32(mmUVD_MPC_SET_MUXA0, 0x40c2040);
	WREG32(mmUVD_MPC_SET_MUXA1, 0x0);
	WREG32(mmUVD_MPC_SET_MUXB0, 0x40c2040);
	WREG32(mmUVD_MPC_SET_MUXB1, 0x0);
	WREG32(mmUVD_MPC_SET_ALU, 0);
	WREG32(mmUVD_MPC_SET_MUX, 0x88);

	/* take all subblocks out of reset, except VCPU */
	WREG32(mmUVD_SOFT_RESET, UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);
	mdelay(5);

	/* enable VCPU घड़ी */
	WREG32(mmUVD_VCPU_CNTL, UVD_VCPU_CNTL__CLK_EN_MASK);

	/* enable UMC */
	WREG32_FIELD(UVD_LMI_CTRL2, STALL_ARB_UMC, 0);

	/* boot up the VCPU */
	WREG32(mmUVD_SOFT_RESET, 0);
	mdelay(10);

	क्रम (i = 0; i < 10; ++i) अणु
		uपूर्णांक32_t status;

		क्रम (j = 0; j < 100; ++j) अणु
			status = RREG32(mmUVD_STATUS);
			अगर (status & 2)
				अवरोध;
			mdelay(10);
		पूर्ण
		r = 0;
		अगर (status & 2)
			अवरोध;

		DRM_ERROR("UVD not responding, trying to reset the VCPU!!!\n");
		WREG32_FIELD(UVD_SOFT_RESET, VCPU_SOFT_RESET, 1);
		mdelay(10);
		WREG32_FIELD(UVD_SOFT_RESET, VCPU_SOFT_RESET, 0);
		mdelay(10);
		r = -1;
	पूर्ण

	अगर (r) अणु
		DRM_ERROR("UVD not responding, giving up!!!\n");
		वापस r;
	पूर्ण
	/* enable master पूर्णांकerrupt */
	WREG32_P(mmUVD_MASTINT_EN,
		(UVD_MASTINT_EN__VCPU_EN_MASK|UVD_MASTINT_EN__SYS_EN_MASK),
		~(UVD_MASTINT_EN__VCPU_EN_MASK|UVD_MASTINT_EN__SYS_EN_MASK));

	/* clear the bit 4 of UVD_STATUS */
	WREG32_P(mmUVD_STATUS, 0, ~(2 << UVD_STATUS__VCPU_REPORT__SHIFT));

	/* क्रमce RBC पूर्णांकo idle state */
	rb_bufsz = order_base_2(ring->ring_size);
	पंचांगp = REG_SET_FIELD(0, UVD_RBC_RB_CNTL, RB_BUFSZ, rb_bufsz);
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_BLKSZ, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_NO_FETCH, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_WPTR_POLL_EN, 0);
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_NO_UPDATE, 1);
	पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_RPTR_WR_EN, 1);
	WREG32(mmUVD_RBC_RB_CNTL, पंचांगp);

	/* set the ग_लिखो poपूर्णांकer delay */
	WREG32(mmUVD_RBC_RB_WPTR_CNTL, 0);

	/* set the wb address */
	WREG32(mmUVD_RBC_RB_RPTR_ADDR, (upper_32_bits(ring->gpu_addr) >> 2));

	/* program the RB_BASE क्रम ring buffer */
	WREG32(mmUVD_LMI_RBC_RB_64BIT_BAR_LOW,
			lower_32_bits(ring->gpu_addr));
	WREG32(mmUVD_LMI_RBC_RB_64BIT_BAR_HIGH,
			upper_32_bits(ring->gpu_addr));

	/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
	WREG32(mmUVD_RBC_RB_RPTR, 0);

	ring->wptr = RREG32(mmUVD_RBC_RB_RPTR);
	WREG32(mmUVD_RBC_RB_WPTR, lower_32_bits(ring->wptr));

	WREG32_FIELD(UVD_RBC_RB_CNTL, RB_NO_FETCH, 0);

	अगर (uvd_v6_0_enc_support(adev)) अणु
		ring = &adev->uvd.inst->ring_enc[0];
		WREG32(mmUVD_RB_RPTR, lower_32_bits(ring->wptr));
		WREG32(mmUVD_RB_WPTR, lower_32_bits(ring->wptr));
		WREG32(mmUVD_RB_BASE_LO, ring->gpu_addr);
		WREG32(mmUVD_RB_BASE_HI, upper_32_bits(ring->gpu_addr));
		WREG32(mmUVD_RB_SIZE, ring->ring_size / 4);

		ring = &adev->uvd.inst->ring_enc[1];
		WREG32(mmUVD_RB_RPTR2, lower_32_bits(ring->wptr));
		WREG32(mmUVD_RB_WPTR2, lower_32_bits(ring->wptr));
		WREG32(mmUVD_RB_BASE_LO2, ring->gpu_addr);
		WREG32(mmUVD_RB_BASE_HI2, upper_32_bits(ring->gpu_addr));
		WREG32(mmUVD_RB_SIZE2, ring->ring_size / 4);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * uvd_v6_0_stop - stop UVD block
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * stop the UVD block
 */
अटल व्योम uvd_v6_0_stop(काष्ठा amdgpu_device *adev)
अणु
	/* क्रमce RBC पूर्णांकo idle state */
	WREG32(mmUVD_RBC_RB_CNTL, 0x11010101);

	/* Stall UMC and रेजिस्टर bus beक्रमe resetting VCPU */
	WREG32_P(mmUVD_LMI_CTRL2, 1 << 8, ~(1 << 8));
	mdelay(1);

	/* put VCPU पूर्णांकo reset */
	WREG32(mmUVD_SOFT_RESET, UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);
	mdelay(5);

	/* disable VCPU घड़ी */
	WREG32(mmUVD_VCPU_CNTL, 0x0);

	/* Unstall UMC and रेजिस्टर bus */
	WREG32_P(mmUVD_LMI_CTRL2, 0, ~(1 << 8));

	WREG32(mmUVD_STATUS, 0);
पूर्ण

/**
 * uvd_v6_0_ring_emit_fence - emit an fence & trap command
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @addr: address
 * @seq: sequence number
 * @flags: fence related flags
 *
 * Write a fence and a trap command to the ring.
 */
अटल व्योम uvd_v6_0_ring_emit_fence(काष्ठा amdgpu_ring *ring, u64 addr, u64 seq,
				     अचिन्हित flags)
अणु
	WARN_ON(flags & AMDGPU_FENCE_FLAG_64BIT);

	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_CONTEXT_ID, 0));
	amdgpu_ring_ग_लिखो(ring, seq);
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GPCOM_VCPU_DATA0, 0));
	amdgpu_ring_ग_लिखो(ring, addr & 0xffffffff);
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GPCOM_VCPU_DATA1, 0));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr) & 0xff);
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GPCOM_VCPU_CMD, 0));
	amdgpu_ring_ग_लिखो(ring, 0);

	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GPCOM_VCPU_DATA0, 0));
	amdgpu_ring_ग_लिखो(ring, 0);
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GPCOM_VCPU_DATA1, 0));
	amdgpu_ring_ग_लिखो(ring, 0);
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GPCOM_VCPU_CMD, 0));
	amdgpu_ring_ग_लिखो(ring, 2);
पूर्ण

/**
 * uvd_v6_0_enc_ring_emit_fence - emit an enc fence & trap command
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @addr: address
 * @seq: sequence number
 * @flags: fence related flags
 *
 * Write enc a fence and a trap command to the ring.
 */
अटल व्योम uvd_v6_0_enc_ring_emit_fence(काष्ठा amdgpu_ring *ring, u64 addr,
			u64 seq, अचिन्हित flags)
अणु
	WARN_ON(flags & AMDGPU_FENCE_FLAG_64BIT);

	amdgpu_ring_ग_लिखो(ring, HEVC_ENC_CMD_FENCE);
	amdgpu_ring_ग_लिखो(ring, addr);
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr));
	amdgpu_ring_ग_लिखो(ring, seq);
	amdgpu_ring_ग_लिखो(ring, HEVC_ENC_CMD_TRAP);
पूर्ण

/**
 * uvd_v6_0_ring_emit_hdp_flush - skip HDP flushing
 *
 * @ring: amdgpu_ring poपूर्णांकer
 */
अटल व्योम uvd_v6_0_ring_emit_hdp_flush(काष्ठा amdgpu_ring *ring)
अणु
	/* The firmware करोesn't seem to like touching रेजिस्टरs at this poपूर्णांक. */
पूर्ण

/**
 * uvd_v6_0_ring_test_ring - रेजिस्टर ग_लिखो test
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Test अगर we can successfully ग_लिखो to the context रेजिस्टर
 */
अटल पूर्णांक uvd_v6_0_ring_test_ring(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t पंचांगp = 0;
	अचिन्हित i;
	पूर्णांक r;

	WREG32(mmUVD_CONTEXT_ID, 0xCAFEDEAD);
	r = amdgpu_ring_alloc(ring, 3);
	अगर (r)
		वापस r;

	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_CONTEXT_ID, 0));
	amdgpu_ring_ग_लिखो(ring, 0xDEADBEEF);
	amdgpu_ring_commit(ring);
	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		पंचांगp = RREG32(mmUVD_CONTEXT_ID);
		अगर (पंचांगp == 0xDEADBEEF)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (i >= adev->usec_समयout)
		r = -ETIMEDOUT;

	वापस r;
पूर्ण

/**
 * uvd_v6_0_ring_emit_ib - execute indirect buffer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @job: job to retrieve vmid from
 * @ib: indirect buffer to execute
 * @flags: unused
 *
 * Write ring commands to execute the indirect buffer
 */
अटल व्योम uvd_v6_0_ring_emit_ib(काष्ठा amdgpu_ring *ring,
				  काष्ठा amdgpu_job *job,
				  काष्ठा amdgpu_ib *ib,
				  uपूर्णांक32_t flags)
अणु
	अचिन्हित vmid = AMDGPU_JOB_GET_VMID(job);

	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_LMI_RBC_IB_VMID, 0));
	amdgpu_ring_ग_लिखो(ring, vmid);

	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_LMI_RBC_IB_64BIT_BAR_LOW, 0));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(ib->gpu_addr));
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_LMI_RBC_IB_64BIT_BAR_HIGH, 0));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr));
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_RBC_IB_SIZE, 0));
	amdgpu_ring_ग_लिखो(ring, ib->length_dw);
पूर्ण

/**
 * uvd_v6_0_enc_ring_emit_ib - enc execute indirect buffer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @job: job to retrive vmid from
 * @ib: indirect buffer to execute
 * @flags: unused
 *
 * Write enc ring commands to execute the indirect buffer
 */
अटल व्योम uvd_v6_0_enc_ring_emit_ib(काष्ठा amdgpu_ring *ring,
					काष्ठा amdgpu_job *job,
					काष्ठा amdgpu_ib *ib,
					uपूर्णांक32_t flags)
अणु
	अचिन्हित vmid = AMDGPU_JOB_GET_VMID(job);

	amdgpu_ring_ग_लिखो(ring, HEVC_ENC_CMD_IB_VM);
	amdgpu_ring_ग_लिखो(ring, vmid);
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(ib->gpu_addr));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr));
	amdgpu_ring_ग_लिखो(ring, ib->length_dw);
पूर्ण

अटल व्योम uvd_v6_0_ring_emit_wreg(काष्ठा amdgpu_ring *ring,
				    uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GPCOM_VCPU_DATA0, 0));
	amdgpu_ring_ग_लिखो(ring, reg << 2);
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GPCOM_VCPU_DATA1, 0));
	amdgpu_ring_ग_लिखो(ring, val);
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GPCOM_VCPU_CMD, 0));
	amdgpu_ring_ग_लिखो(ring, 0x8);
पूर्ण

अटल व्योम uvd_v6_0_ring_emit_vm_flush(काष्ठा amdgpu_ring *ring,
					अचिन्हित vmid, uपूर्णांक64_t pd_addr)
अणु
	amdgpu_gmc_emit_flush_gpu_tlb(ring, vmid, pd_addr);

	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GPCOM_VCPU_DATA0, 0));
	amdgpu_ring_ग_लिखो(ring, mmVM_INVALIDATE_REQUEST << 2);
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GPCOM_VCPU_DATA1, 0));
	amdgpu_ring_ग_लिखो(ring, 0);
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GP_SCRATCH8, 0));
	amdgpu_ring_ग_लिखो(ring, 1 << vmid); /* mask */
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GPCOM_VCPU_CMD, 0));
	amdgpu_ring_ग_लिखो(ring, 0xC);
पूर्ण

अटल व्योम uvd_v6_0_ring_emit_pipeline_sync(काष्ठा amdgpu_ring *ring)
अणु
	uपूर्णांक32_t seq = ring->fence_drv.sync_seq;
	uपूर्णांक64_t addr = ring->fence_drv.gpu_addr;

	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GPCOM_VCPU_DATA0, 0));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(addr));
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GPCOM_VCPU_DATA1, 0));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr));
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GP_SCRATCH8, 0));
	amdgpu_ring_ग_लिखो(ring, 0xffffffff); /* mask */
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GP_SCRATCH9, 0));
	amdgpu_ring_ग_लिखो(ring, seq);
	amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_GPCOM_VCPU_CMD, 0));
	amdgpu_ring_ग_लिखो(ring, 0xE);
पूर्ण

अटल व्योम uvd_v6_0_ring_insert_nop(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t count)
अणु
	पूर्णांक i;

	WARN_ON(ring->wptr % 2 || count % 2);

	क्रम (i = 0; i < count / 2; i++) अणु
		amdgpu_ring_ग_लिखो(ring, PACKET0(mmUVD_NO_OP, 0));
		amdgpu_ring_ग_लिखो(ring, 0);
	पूर्ण
पूर्ण

अटल व्योम uvd_v6_0_enc_ring_emit_pipeline_sync(काष्ठा amdgpu_ring *ring)
अणु
	uपूर्णांक32_t seq = ring->fence_drv.sync_seq;
	uपूर्णांक64_t addr = ring->fence_drv.gpu_addr;

	amdgpu_ring_ग_लिखो(ring, HEVC_ENC_CMD_WAIT_GE);
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(addr));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr));
	amdgpu_ring_ग_लिखो(ring, seq);
पूर्ण

अटल व्योम uvd_v6_0_enc_ring_insert_end(काष्ठा amdgpu_ring *ring)
अणु
	amdgpu_ring_ग_लिखो(ring, HEVC_ENC_CMD_END);
पूर्ण

अटल व्योम uvd_v6_0_enc_ring_emit_vm_flush(काष्ठा amdgpu_ring *ring,
					    अचिन्हित पूर्णांक vmid, uपूर्णांक64_t pd_addr)
अणु
	amdgpu_ring_ग_लिखो(ring, HEVC_ENC_CMD_UPDATE_PTB);
	amdgpu_ring_ग_लिखो(ring, vmid);
	amdgpu_ring_ग_लिखो(ring, pd_addr >> 12);

	amdgpu_ring_ग_लिखो(ring, HEVC_ENC_CMD_FLUSH_TLB);
	amdgpu_ring_ग_लिखो(ring, vmid);
पूर्ण

अटल bool uvd_v6_0_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस !(RREG32(mmSRBM_STATUS) & SRBM_STATUS__UVD_BUSY_MASK);
पूर्ण

अटल पूर्णांक uvd_v6_0_रुको_क्रम_idle(व्योम *handle)
अणु
	अचिन्हित i;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर (uvd_v6_0_is_idle(handle))
			वापस 0;
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

#घोषणा AMDGPU_UVD_STATUS_BUSY_MASK    0xfd
अटल bool uvd_v6_0_check_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 srbm_soft_reset = 0;
	u32 पंचांगp = RREG32(mmSRBM_STATUS);

	अगर (REG_GET_FIELD(पंचांगp, SRBM_STATUS, UVD_RQ_PENDING) ||
	    REG_GET_FIELD(पंचांगp, SRBM_STATUS, UVD_BUSY) ||
	    (RREG32(mmUVD_STATUS) & AMDGPU_UVD_STATUS_BUSY_MASK))
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset, SRBM_SOFT_RESET, SOFT_RESET_UVD, 1);

	अगर (srbm_soft_reset) अणु
		adev->uvd.inst->srbm_soft_reset = srbm_soft_reset;
		वापस true;
	पूर्ण अन्यथा अणु
		adev->uvd.inst->srbm_soft_reset = 0;
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक uvd_v6_0_pre_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (!adev->uvd.inst->srbm_soft_reset)
		वापस 0;

	uvd_v6_0_stop(adev);
	वापस 0;
पूर्ण

अटल पूर्णांक uvd_v6_0_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 srbm_soft_reset;

	अगर (!adev->uvd.inst->srbm_soft_reset)
		वापस 0;
	srbm_soft_reset = adev->uvd.inst->srbm_soft_reset;

	अगर (srbm_soft_reset) अणु
		u32 पंचांगp;

		पंचांगp = RREG32(mmSRBM_SOFT_RESET);
		पंचांगp |= srbm_soft_reset;
		dev_info(adev->dev, "SRBM_SOFT_RESET=0x%08X\n", पंचांगp);
		WREG32(mmSRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32(mmSRBM_SOFT_RESET);

		udelay(50);

		पंचांगp &= ~srbm_soft_reset;
		WREG32(mmSRBM_SOFT_RESET, पंचांगp);
		पंचांगp = RREG32(mmSRBM_SOFT_RESET);

		/* Wait a little क्रम things to settle करोwn */
		udelay(50);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uvd_v6_0_post_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (!adev->uvd.inst->srbm_soft_reset)
		वापस 0;

	mdelay(5);

	वापस uvd_v6_0_start(adev);
पूर्ण

अटल पूर्णांक uvd_v6_0_set_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_irq_src *source,
					अचिन्हित type,
					क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	// TODO
	वापस 0;
पूर्ण

अटल पूर्णांक uvd_v6_0_process_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_irq_src *source,
				      काष्ठा amdgpu_iv_entry *entry)
अणु
	bool पूर्णांक_handled = true;
	DRM_DEBUG("IH: UVD TRAP\n");

	चयन (entry->src_id) अणु
	हाल 124:
		amdgpu_fence_process(&adev->uvd.inst->ring);
		अवरोध;
	हाल 119:
		अगर (likely(uvd_v6_0_enc_support(adev)))
			amdgpu_fence_process(&adev->uvd.inst->ring_enc[0]);
		अन्यथा
			पूर्णांक_handled = false;
		अवरोध;
	हाल 120:
		अगर (likely(uvd_v6_0_enc_support(adev)))
			amdgpu_fence_process(&adev->uvd.inst->ring_enc[1]);
		अन्यथा
			पूर्णांक_handled = false;
		अवरोध;
	पूर्ण

	अगर (!पूर्णांक_handled)
		DRM_ERROR("Unhandled interrupt: %d %d\n",
			  entry->src_id, entry->src_data[0]);

	वापस 0;
पूर्ण

अटल व्योम uvd_v6_0_enable_घड़ी_gating(काष्ठा amdgpu_device *adev, bool enable)
अणु
	uपूर्णांक32_t data1, data3;

	data1 = RREG32(mmUVD_SUVD_CGC_GATE);
	data3 = RREG32(mmUVD_CGC_GATE);

	data1 |= UVD_SUVD_CGC_GATE__SRE_MASK |
		     UVD_SUVD_CGC_GATE__SIT_MASK |
		     UVD_SUVD_CGC_GATE__SMP_MASK |
		     UVD_SUVD_CGC_GATE__SCM_MASK |
		     UVD_SUVD_CGC_GATE__SDB_MASK |
		     UVD_SUVD_CGC_GATE__SRE_H264_MASK |
		     UVD_SUVD_CGC_GATE__SRE_HEVC_MASK |
		     UVD_SUVD_CGC_GATE__SIT_H264_MASK |
		     UVD_SUVD_CGC_GATE__SIT_HEVC_MASK |
		     UVD_SUVD_CGC_GATE__SCM_H264_MASK |
		     UVD_SUVD_CGC_GATE__SCM_HEVC_MASK |
		     UVD_SUVD_CGC_GATE__SDB_H264_MASK |
		     UVD_SUVD_CGC_GATE__SDB_HEVC_MASK;

	अगर (enable) अणु
		data3 |= (UVD_CGC_GATE__SYS_MASK       |
			UVD_CGC_GATE__UDEC_MASK      |
			UVD_CGC_GATE__MPEG2_MASK     |
			UVD_CGC_GATE__RBC_MASK       |
			UVD_CGC_GATE__LMI_MC_MASK    |
			UVD_CGC_GATE__LMI_UMC_MASK   |
			UVD_CGC_GATE__IDCT_MASK      |
			UVD_CGC_GATE__MPRD_MASK      |
			UVD_CGC_GATE__MPC_MASK       |
			UVD_CGC_GATE__LBSI_MASK      |
			UVD_CGC_GATE__LRBBM_MASK     |
			UVD_CGC_GATE__UDEC_RE_MASK   |
			UVD_CGC_GATE__UDEC_CM_MASK   |
			UVD_CGC_GATE__UDEC_IT_MASK   |
			UVD_CGC_GATE__UDEC_DB_MASK   |
			UVD_CGC_GATE__UDEC_MP_MASK   |
			UVD_CGC_GATE__WCB_MASK       |
			UVD_CGC_GATE__JPEG_MASK      |
			UVD_CGC_GATE__SCPU_MASK      |
			UVD_CGC_GATE__JPEG2_MASK);
		/* only in pg enabled, we can gate घड़ी to vcpu*/
		अगर (adev->pg_flags & AMD_PG_SUPPORT_UVD)
			data3 |= UVD_CGC_GATE__VCPU_MASK;

		data3 &= ~UVD_CGC_GATE__REGS_MASK;
	पूर्ण अन्यथा अणु
		data3 = 0;
	पूर्ण

	WREG32(mmUVD_SUVD_CGC_GATE, data1);
	WREG32(mmUVD_CGC_GATE, data3);
पूर्ण

अटल व्योम uvd_v6_0_set_sw_घड़ी_gating(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t data, data2;

	data = RREG32(mmUVD_CGC_CTRL);
	data2 = RREG32(mmUVD_SUVD_CGC_CTRL);


	data &= ~(UVD_CGC_CTRL__CLK_OFF_DELAY_MASK |
		  UVD_CGC_CTRL__CLK_GATE_DLY_TIMER_MASK);


	data |= UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK |
		(1 << REG_FIELD_SHIFT(UVD_CGC_CTRL, CLK_GATE_DLY_TIMER)) |
		(4 << REG_FIELD_SHIFT(UVD_CGC_CTRL, CLK_OFF_DELAY));

	data &= ~(UVD_CGC_CTRL__UDEC_RE_MODE_MASK |
			UVD_CGC_CTRL__UDEC_CM_MODE_MASK |
			UVD_CGC_CTRL__UDEC_IT_MODE_MASK |
			UVD_CGC_CTRL__UDEC_DB_MODE_MASK |
			UVD_CGC_CTRL__UDEC_MP_MODE_MASK |
			UVD_CGC_CTRL__SYS_MODE_MASK |
			UVD_CGC_CTRL__UDEC_MODE_MASK |
			UVD_CGC_CTRL__MPEG2_MODE_MASK |
			UVD_CGC_CTRL__REGS_MODE_MASK |
			UVD_CGC_CTRL__RBC_MODE_MASK |
			UVD_CGC_CTRL__LMI_MC_MODE_MASK |
			UVD_CGC_CTRL__LMI_UMC_MODE_MASK |
			UVD_CGC_CTRL__IDCT_MODE_MASK |
			UVD_CGC_CTRL__MPRD_MODE_MASK |
			UVD_CGC_CTRL__MPC_MODE_MASK |
			UVD_CGC_CTRL__LBSI_MODE_MASK |
			UVD_CGC_CTRL__LRBBM_MODE_MASK |
			UVD_CGC_CTRL__WCB_MODE_MASK |
			UVD_CGC_CTRL__VCPU_MODE_MASK |
			UVD_CGC_CTRL__JPEG_MODE_MASK |
			UVD_CGC_CTRL__SCPU_MODE_MASK |
			UVD_CGC_CTRL__JPEG2_MODE_MASK);
	data2 &= ~(UVD_SUVD_CGC_CTRL__SRE_MODE_MASK |
			UVD_SUVD_CGC_CTRL__SIT_MODE_MASK |
			UVD_SUVD_CGC_CTRL__SMP_MODE_MASK |
			UVD_SUVD_CGC_CTRL__SCM_MODE_MASK |
			UVD_SUVD_CGC_CTRL__SDB_MODE_MASK);

	WREG32(mmUVD_CGC_CTRL, data);
	WREG32(mmUVD_SUVD_CGC_CTRL, data2);
पूर्ण

#अगर 0
अटल व्योम uvd_v6_0_set_hw_घड़ी_gating(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t data, data1, cgc_flags, suvd_flags;

	data = RREG32(mmUVD_CGC_GATE);
	data1 = RREG32(mmUVD_SUVD_CGC_GATE);

	cgc_flags = UVD_CGC_GATE__SYS_MASK |
		UVD_CGC_GATE__UDEC_MASK |
		UVD_CGC_GATE__MPEG2_MASK |
		UVD_CGC_GATE__RBC_MASK |
		UVD_CGC_GATE__LMI_MC_MASK |
		UVD_CGC_GATE__IDCT_MASK |
		UVD_CGC_GATE__MPRD_MASK |
		UVD_CGC_GATE__MPC_MASK |
		UVD_CGC_GATE__LBSI_MASK |
		UVD_CGC_GATE__LRBBM_MASK |
		UVD_CGC_GATE__UDEC_RE_MASK |
		UVD_CGC_GATE__UDEC_CM_MASK |
		UVD_CGC_GATE__UDEC_IT_MASK |
		UVD_CGC_GATE__UDEC_DB_MASK |
		UVD_CGC_GATE__UDEC_MP_MASK |
		UVD_CGC_GATE__WCB_MASK |
		UVD_CGC_GATE__VCPU_MASK |
		UVD_CGC_GATE__SCPU_MASK |
		UVD_CGC_GATE__JPEG_MASK |
		UVD_CGC_GATE__JPEG2_MASK;

	suvd_flags = UVD_SUVD_CGC_GATE__SRE_MASK |
				UVD_SUVD_CGC_GATE__SIT_MASK |
				UVD_SUVD_CGC_GATE__SMP_MASK |
				UVD_SUVD_CGC_GATE__SCM_MASK |
				UVD_SUVD_CGC_GATE__SDB_MASK;

	data |= cgc_flags;
	data1 |= suvd_flags;

	WREG32(mmUVD_CGC_GATE, data);
	WREG32(mmUVD_SUVD_CGC_GATE, data1);
पूर्ण
#पूर्ण_अगर

अटल व्योम uvd_v6_0_enable_mgcg(काष्ठा amdgpu_device *adev,
				 bool enable)
अणु
	u32 orig, data;

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_UVD_MGCG)) अणु
		data = RREG32_UVD_CTX(ixUVD_CGC_MEM_CTRL);
		data |= 0xfff;
		WREG32_UVD_CTX(ixUVD_CGC_MEM_CTRL, data);

		orig = data = RREG32(mmUVD_CGC_CTRL);
		data |= UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK;
		अगर (orig != data)
			WREG32(mmUVD_CGC_CTRL, data);
	पूर्ण अन्यथा अणु
		data = RREG32_UVD_CTX(ixUVD_CGC_MEM_CTRL);
		data &= ~0xfff;
		WREG32_UVD_CTX(ixUVD_CGC_MEM_CTRL, data);

		orig = data = RREG32(mmUVD_CGC_CTRL);
		data &= ~UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK;
		अगर (orig != data)
			WREG32(mmUVD_CGC_CTRL, data);
	पूर्ण
पूर्ण

अटल पूर्णांक uvd_v6_0_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	bool enable = (state == AMD_CG_STATE_GATE);

	अगर (enable) अणु
		/* रुको क्रम STATUS to clear */
		अगर (uvd_v6_0_रुको_क्रम_idle(handle))
			वापस -EBUSY;
		uvd_v6_0_enable_घड़ी_gating(adev, true);
		/* enable HW gates because UVD is idle */
/*		uvd_v6_0_set_hw_घड़ी_gating(adev); */
	पूर्ण अन्यथा अणु
		/* disable HW gating and enable Sw gating */
		uvd_v6_0_enable_घड़ी_gating(adev, false);
	पूर्ण
	uvd_v6_0_set_sw_घड़ी_gating(adev);
	वापस 0;
पूर्ण

अटल पूर्णांक uvd_v6_0_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	/* This करोesn't actually घातergate the UVD block.
	 * That's करोne in the dpm code via the SMC.  This
	 * just re-inits the block as necessary.  The actual
	 * gating still happens in the dpm code.  We should
	 * revisit this when there is a cleaner line between
	 * the smc and the hw blocks
	 */
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक ret = 0;

	WREG32(mmUVD_POWER_STATUS, UVD_POWER_STATUS__UVD_PG_EN_MASK);

	अगर (state == AMD_PG_STATE_GATE) अणु
		uvd_v6_0_stop(adev);
	पूर्ण अन्यथा अणु
		ret = uvd_v6_0_start(adev);
		अगर (ret)
			जाओ out;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल व्योम uvd_v6_0_get_घड़ीgating_state(व्योम *handle, u32 *flags)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक data;

	mutex_lock(&adev->pm.mutex);

	अगर (adev->flags & AMD_IS_APU)
		data = RREG32_SMC(ixCURRENT_PG_STATUS_APU);
	अन्यथा
		data = RREG32_SMC(ixCURRENT_PG_STATUS);

	अगर (data & CURRENT_PG_STATUS__UVD_PG_STATUS_MASK) अणु
		DRM_INFO("Cannot get clockgating state when UVD is powergated.\n");
		जाओ out;
	पूर्ण

	/* AMD_CG_SUPPORT_UVD_MGCG */
	data = RREG32(mmUVD_CGC_CTRL);
	अगर (data & UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK)
		*flags |= AMD_CG_SUPPORT_UVD_MGCG;

out:
	mutex_unlock(&adev->pm.mutex);
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs uvd_v6_0_ip_funcs = अणु
	.name = "uvd_v6_0",
	.early_init = uvd_v6_0_early_init,
	.late_init = शून्य,
	.sw_init = uvd_v6_0_sw_init,
	.sw_fini = uvd_v6_0_sw_fini,
	.hw_init = uvd_v6_0_hw_init,
	.hw_fini = uvd_v6_0_hw_fini,
	.suspend = uvd_v6_0_suspend,
	.resume = uvd_v6_0_resume,
	.is_idle = uvd_v6_0_is_idle,
	.रुको_क्रम_idle = uvd_v6_0_रुको_क्रम_idle,
	.check_soft_reset = uvd_v6_0_check_soft_reset,
	.pre_soft_reset = uvd_v6_0_pre_soft_reset,
	.soft_reset = uvd_v6_0_soft_reset,
	.post_soft_reset = uvd_v6_0_post_soft_reset,
	.set_घड़ीgating_state = uvd_v6_0_set_घड़ीgating_state,
	.set_घातergating_state = uvd_v6_0_set_घातergating_state,
	.get_घड़ीgating_state = uvd_v6_0_get_घड़ीgating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs uvd_v6_0_ring_phys_funcs = अणु
	.type = AMDGPU_RING_TYPE_UVD,
	.align_mask = 0xf,
	.support_64bit_ptrs = false,
	.no_user_fence = true,
	.get_rptr = uvd_v6_0_ring_get_rptr,
	.get_wptr = uvd_v6_0_ring_get_wptr,
	.set_wptr = uvd_v6_0_ring_set_wptr,
	.parse_cs = amdgpu_uvd_ring_parse_cs,
	.emit_frame_size =
		6 + /* hdp invalidate */
		10 + /* uvd_v6_0_ring_emit_pipeline_sync */
		14, /* uvd_v6_0_ring_emit_fence x1 no user fence */
	.emit_ib_size = 8, /* uvd_v6_0_ring_emit_ib */
	.emit_ib = uvd_v6_0_ring_emit_ib,
	.emit_fence = uvd_v6_0_ring_emit_fence,
	.emit_hdp_flush = uvd_v6_0_ring_emit_hdp_flush,
	.test_ring = uvd_v6_0_ring_test_ring,
	.test_ib = amdgpu_uvd_ring_test_ib,
	.insert_nop = uvd_v6_0_ring_insert_nop,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.begin_use = amdgpu_uvd_ring_begin_use,
	.end_use = amdgpu_uvd_ring_end_use,
	.emit_wreg = uvd_v6_0_ring_emit_wreg,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs uvd_v6_0_ring_vm_funcs = अणु
	.type = AMDGPU_RING_TYPE_UVD,
	.align_mask = 0xf,
	.support_64bit_ptrs = false,
	.no_user_fence = true,
	.get_rptr = uvd_v6_0_ring_get_rptr,
	.get_wptr = uvd_v6_0_ring_get_wptr,
	.set_wptr = uvd_v6_0_ring_set_wptr,
	.emit_frame_size =
		6 + /* hdp invalidate */
		10 + /* uvd_v6_0_ring_emit_pipeline_sync */
		VI_FLUSH_GPU_TLB_NUM_WREG * 6 + 8 + /* uvd_v6_0_ring_emit_vm_flush */
		14 + 14, /* uvd_v6_0_ring_emit_fence x2 vm fence */
	.emit_ib_size = 8, /* uvd_v6_0_ring_emit_ib */
	.emit_ib = uvd_v6_0_ring_emit_ib,
	.emit_fence = uvd_v6_0_ring_emit_fence,
	.emit_vm_flush = uvd_v6_0_ring_emit_vm_flush,
	.emit_pipeline_sync = uvd_v6_0_ring_emit_pipeline_sync,
	.emit_hdp_flush = uvd_v6_0_ring_emit_hdp_flush,
	.test_ring = uvd_v6_0_ring_test_ring,
	.test_ib = amdgpu_uvd_ring_test_ib,
	.insert_nop = uvd_v6_0_ring_insert_nop,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.begin_use = amdgpu_uvd_ring_begin_use,
	.end_use = amdgpu_uvd_ring_end_use,
	.emit_wreg = uvd_v6_0_ring_emit_wreg,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs uvd_v6_0_enc_ring_vm_funcs = अणु
	.type = AMDGPU_RING_TYPE_UVD_ENC,
	.align_mask = 0x3f,
	.nop = HEVC_ENC_CMD_NO_OP,
	.support_64bit_ptrs = false,
	.no_user_fence = true,
	.get_rptr = uvd_v6_0_enc_ring_get_rptr,
	.get_wptr = uvd_v6_0_enc_ring_get_wptr,
	.set_wptr = uvd_v6_0_enc_ring_set_wptr,
	.emit_frame_size =
		4 + /* uvd_v6_0_enc_ring_emit_pipeline_sync */
		5 + /* uvd_v6_0_enc_ring_emit_vm_flush */
		5 + 5 + /* uvd_v6_0_enc_ring_emit_fence x2 vm fence */
		1, /* uvd_v6_0_enc_ring_insert_end */
	.emit_ib_size = 5, /* uvd_v6_0_enc_ring_emit_ib */
	.emit_ib = uvd_v6_0_enc_ring_emit_ib,
	.emit_fence = uvd_v6_0_enc_ring_emit_fence,
	.emit_vm_flush = uvd_v6_0_enc_ring_emit_vm_flush,
	.emit_pipeline_sync = uvd_v6_0_enc_ring_emit_pipeline_sync,
	.test_ring = uvd_v6_0_enc_ring_test_ring,
	.test_ib = uvd_v6_0_enc_ring_test_ib,
	.insert_nop = amdgpu_ring_insert_nop,
	.insert_end = uvd_v6_0_enc_ring_insert_end,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.begin_use = amdgpu_uvd_ring_begin_use,
	.end_use = amdgpu_uvd_ring_end_use,
पूर्ण;

अटल व्योम uvd_v6_0_set_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->asic_type >= CHIP_POLARIS10) अणु
		adev->uvd.inst->ring.funcs = &uvd_v6_0_ring_vm_funcs;
		DRM_INFO("UVD is enabled in VM mode\n");
	पूर्ण अन्यथा अणु
		adev->uvd.inst->ring.funcs = &uvd_v6_0_ring_phys_funcs;
		DRM_INFO("UVD is enabled in physical mode\n");
	पूर्ण
पूर्ण

अटल व्योम uvd_v6_0_set_enc_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->uvd.num_enc_rings; ++i)
		adev->uvd.inst->ring_enc[i].funcs = &uvd_v6_0_enc_ring_vm_funcs;

	DRM_INFO("UVD ENC is enabled in VM mode\n");
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs uvd_v6_0_irq_funcs = अणु
	.set = uvd_v6_0_set_पूर्णांकerrupt_state,
	.process = uvd_v6_0_process_पूर्णांकerrupt,
पूर्ण;

अटल व्योम uvd_v6_0_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	अगर (uvd_v6_0_enc_support(adev))
		adev->uvd.inst->irq.num_types = adev->uvd.num_enc_rings + 1;
	अन्यथा
		adev->uvd.inst->irq.num_types = 1;

	adev->uvd.inst->irq.funcs = &uvd_v6_0_irq_funcs;
पूर्ण

स्थिर काष्ठा amdgpu_ip_block_version uvd_v6_0_ip_block =
अणु
		.type = AMD_IP_BLOCK_TYPE_UVD,
		.major = 6,
		.minor = 0,
		.rev = 0,
		.funcs = &uvd_v6_0_ip_funcs,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version uvd_v6_2_ip_block =
अणु
		.type = AMD_IP_BLOCK_TYPE_UVD,
		.major = 6,
		.minor = 2,
		.rev = 0,
		.funcs = &uvd_v6_0_ip_funcs,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version uvd_v6_3_ip_block =
अणु
		.type = AMD_IP_BLOCK_TYPE_UVD,
		.major = 6,
		.minor = 3,
		.rev = 0,
		.funcs = &uvd_v6_0_ip_funcs,
पूर्ण;
