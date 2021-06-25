<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
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
 */

#समावेश <linux/firmware.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_uvd.h"
#समावेश "soc15.h"
#समावेश "soc15d.h"
#समावेश "soc15_common.h"
#समावेश "mmsch_v1_0.h"

#समावेश "uvd/uvd_7_0_offset.h"
#समावेश "uvd/uvd_7_0_sh_mask.h"
#समावेश "vce/vce_4_0_offset.h"
#समावेश "vce/vce_4_0_default.h"
#समावेश "vce/vce_4_0_sh_mask.h"
#समावेश "nbif/nbif_6_1_offset.h"
#समावेश "mmhub/mmhub_1_0_offset.h"
#समावेश "mmhub/mmhub_1_0_sh_mask.h"
#समावेश "ivsrcid/uvd/irqsrcs_uvd_7_0.h"

#घोषणा mmUVD_PG0_CC_UVD_HARVESTING                                                                    0x00c7
#घोषणा mmUVD_PG0_CC_UVD_HARVESTING_BASE_IDX                                                           1
//UVD_PG0_CC_UVD_HARVESTING
#घोषणा UVD_PG0_CC_UVD_HARVESTING__UVD_DISABLE__SHIFT                                                         0x1
#घोषणा UVD_PG0_CC_UVD_HARVESTING__UVD_DISABLE_MASK                                                           0x00000002L

#घोषणा UVD7_MAX_HW_INSTANCES_VEGA20			2

अटल व्योम uvd_v7_0_set_ring_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम uvd_v7_0_set_enc_ring_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम uvd_v7_0_set_irq_funcs(काष्ठा amdgpu_device *adev);
अटल पूर्णांक uvd_v7_0_start(काष्ठा amdgpu_device *adev);
अटल व्योम uvd_v7_0_stop(काष्ठा amdgpu_device *adev);
अटल पूर्णांक uvd_v7_0_sriov_start(काष्ठा amdgpu_device *adev);

अटल पूर्णांक amdgpu_ih_clientid_uvds[] = अणु
	SOC15_IH_CLIENTID_UVD,
	SOC15_IH_CLIENTID_UVD1
पूर्ण;

/**
 * uvd_v7_0_ring_get_rptr - get पढ़ो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware पढ़ो poपूर्णांकer
 */
अटल uपूर्णांक64_t uvd_v7_0_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	वापस RREG32_SOC15(UVD, ring->me, mmUVD_RBC_RB_RPTR);
पूर्ण

/**
 * uvd_v7_0_enc_ring_get_rptr - get enc पढ़ो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware enc पढ़ो poपूर्णांकer
 */
अटल uपूर्णांक64_t uvd_v7_0_enc_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring == &adev->uvd.inst[ring->me].ring_enc[0])
		वापस RREG32_SOC15(UVD, ring->me, mmUVD_RB_RPTR);
	अन्यथा
		वापस RREG32_SOC15(UVD, ring->me, mmUVD_RB_RPTR2);
पूर्ण

/**
 * uvd_v7_0_ring_get_wptr - get ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware ग_लिखो poपूर्णांकer
 */
अटल uपूर्णांक64_t uvd_v7_0_ring_get_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	वापस RREG32_SOC15(UVD, ring->me, mmUVD_RBC_RB_WPTR);
पूर्ण

/**
 * uvd_v7_0_enc_ring_get_wptr - get enc ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware enc ग_लिखो poपूर्णांकer
 */
अटल uपूर्णांक64_t uvd_v7_0_enc_ring_get_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring->use_करोorbell)
		वापस adev->wb.wb[ring->wptr_offs];

	अगर (ring == &adev->uvd.inst[ring->me].ring_enc[0])
		वापस RREG32_SOC15(UVD, ring->me, mmUVD_RB_WPTR);
	अन्यथा
		वापस RREG32_SOC15(UVD, ring->me, mmUVD_RB_WPTR2);
पूर्ण

/**
 * uvd_v7_0_ring_set_wptr - set ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Commits the ग_लिखो poपूर्णांकer to the hardware
 */
अटल व्योम uvd_v7_0_ring_set_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	WREG32_SOC15(UVD, ring->me, mmUVD_RBC_RB_WPTR, lower_32_bits(ring->wptr));
पूर्ण

/**
 * uvd_v7_0_enc_ring_set_wptr - set enc ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Commits the enc ग_लिखो poपूर्णांकer to the hardware
 */
अटल व्योम uvd_v7_0_enc_ring_set_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring->use_करोorbell) अणु
		/* XXX check अगर swapping is necessary on BE */
		adev->wb.wb[ring->wptr_offs] = lower_32_bits(ring->wptr);
		WDOORBELL32(ring->करोorbell_index, lower_32_bits(ring->wptr));
		वापस;
	पूर्ण

	अगर (ring == &adev->uvd.inst[ring->me].ring_enc[0])
		WREG32_SOC15(UVD, ring->me, mmUVD_RB_WPTR,
			lower_32_bits(ring->wptr));
	अन्यथा
		WREG32_SOC15(UVD, ring->me, mmUVD_RB_WPTR2,
			lower_32_bits(ring->wptr));
पूर्ण

/**
 * uvd_v7_0_enc_ring_test_ring - test अगर UVD ENC ring is working
 *
 * @ring: the engine to test on
 *
 */
अटल पूर्णांक uvd_v7_0_enc_ring_test_ring(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t rptr;
	अचिन्हित i;
	पूर्णांक r;

	अगर (amdgpu_sriov_vf(adev))
		वापस 0;

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
 * uvd_v7_0_enc_get_create_msg - generate a UVD ENC create msg
 *
 * @ring: ring we should submit the msg to
 * @handle: session handle to use
 * @bo: amdgpu object क्रम which we query the offset
 * @fence: optional fence to वापस
 *
 * Open up a stream क्रम HW test
 */
अटल पूर्णांक uvd_v7_0_enc_get_create_msg(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t handle,
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
	ib->ptr[ib->length_dw++] = 0x00000000;
	ib->ptr[ib->length_dw++] = upper_32_bits(addr);
	ib->ptr[ib->length_dw++] = addr;

	ib->ptr[ib->length_dw++] = 0x00000014;
	ib->ptr[ib->length_dw++] = 0x00000002; /* task info */
	ib->ptr[ib->length_dw++] = 0x0000001c;
	ib->ptr[ib->length_dw++] = 0x00000000;
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
 * uvd_v7_0_enc_get_destroy_msg - generate a UVD ENC destroy msg
 *
 * @ring: ring we should submit the msg to
 * @handle: session handle to use
 * @bo: amdgpu object क्रम which we query the offset
 * @fence: optional fence to वापस
 *
 * Close up a stream क्रम HW test or अगर userspace failed to करो so
 */
अटल पूर्णांक uvd_v7_0_enc_get_destroy_msg(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t handle,
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
	ib->ptr[ib->length_dw++] = 0x00000001;
	ib->ptr[ib->length_dw++] = handle;
	ib->ptr[ib->length_dw++] = 0x00000000;
	ib->ptr[ib->length_dw++] = upper_32_bits(addr);
	ib->ptr[ib->length_dw++] = addr;

	ib->ptr[ib->length_dw++] = 0x00000014;
	ib->ptr[ib->length_dw++] = 0x00000002;
	ib->ptr[ib->length_dw++] = 0x0000001c;
	ib->ptr[ib->length_dw++] = 0x00000000;
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
 * uvd_v7_0_enc_ring_test_ib - test अगर UVD ENC IBs are working
 *
 * @ring: the engine to test on
 * @समयout: समयout value in jअगरfies, or MAX_SCHEDULE_TIMEOUT
 *
 */
अटल पूर्णांक uvd_v7_0_enc_ring_test_ib(काष्ठा amdgpu_ring *ring, दीर्घ समयout)
अणु
	काष्ठा dma_fence *fence = शून्य;
	काष्ठा amdgpu_bo *bo = शून्य;
	दीर्घ r;

	r = amdgpu_bo_create_reserved(ring->adev, 128 * 1024, PAGE_SIZE,
				      AMDGPU_GEM_DOMAIN_VRAM,
				      &bo, शून्य, शून्य);
	अगर (r)
		वापस r;

	r = uvd_v7_0_enc_get_create_msg(ring, 1, bo, शून्य);
	अगर (r)
		जाओ error;

	r = uvd_v7_0_enc_get_destroy_msg(ring, 1, bo, &fence);
	अगर (r)
		जाओ error;

	r = dma_fence_रुको_समयout(fence, false, समयout);
	अगर (r == 0)
		r = -ETIMEDOUT;
	अन्यथा अगर (r > 0)
		r = 0;

error:
	dma_fence_put(fence);
	amdgpu_bo_unreserve(bo);
	amdgpu_bo_unref(&bo);
	वापस r;
पूर्ण

अटल पूर्णांक uvd_v7_0_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (adev->asic_type == CHIP_VEGA20) अणु
		u32 harvest;
		पूर्णांक i;

		adev->uvd.num_uvd_inst = UVD7_MAX_HW_INSTANCES_VEGA20;
		क्रम (i = 0; i < adev->uvd.num_uvd_inst; i++) अणु
			harvest = RREG32_SOC15(UVD, i, mmUVD_PG0_CC_UVD_HARVESTING);
			अगर (harvest & UVD_PG0_CC_UVD_HARVESTING__UVD_DISABLE_MASK) अणु
				adev->uvd.harvest_config |= 1 << i;
			पूर्ण
		पूर्ण
		अगर (adev->uvd.harvest_config == (AMDGPU_UVD_HARVEST_UVD0 |
						 AMDGPU_UVD_HARVEST_UVD1))
			/* both instances are harvested, disable the block */
			वापस -ENOENT;
	पूर्ण अन्यथा अणु
		adev->uvd.num_uvd_inst = 1;
	पूर्ण

	अगर (amdgpu_sriov_vf(adev))
		adev->uvd.num_enc_rings = 1;
	अन्यथा
		adev->uvd.num_enc_rings = 2;
	uvd_v7_0_set_ring_funcs(adev);
	uvd_v7_0_set_enc_ring_funcs(adev);
	uvd_v7_0_set_irq_funcs(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक uvd_v7_0_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_ring *ring;

	पूर्णांक i, j, r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	क्रम (j = 0; j < adev->uvd.num_uvd_inst; j++) अणु
		अगर (adev->uvd.harvest_config & (1 << j))
			जारी;
		/* UVD TRAP */
		r = amdgpu_irq_add_id(adev, amdgpu_ih_clientid_uvds[j], UVD_7_0__SRCID__UVD_SYSTEM_MESSAGE_INTERRUPT, &adev->uvd.inst[j].irq);
		अगर (r)
			वापस r;

		/* UVD ENC TRAP */
		क्रम (i = 0; i < adev->uvd.num_enc_rings; ++i) अणु
			r = amdgpu_irq_add_id(adev, amdgpu_ih_clientid_uvds[j], i + UVD_7_0__SRCID__UVD_ENC_GEN_PURP, &adev->uvd.inst[j].irq);
			अगर (r)
				वापस r;
		पूर्ण
	पूर्ण

	r = amdgpu_uvd_sw_init(adev);
	अगर (r)
		वापस r;

	अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
		स्थिर काष्ठा common_firmware_header *hdr;
		hdr = (स्थिर काष्ठा common_firmware_header *)adev->uvd.fw->data;
		adev->firmware.ucode[AMDGPU_UCODE_ID_UVD].ucode_id = AMDGPU_UCODE_ID_UVD;
		adev->firmware.ucode[AMDGPU_UCODE_ID_UVD].fw = adev->uvd.fw;
		adev->firmware.fw_size +=
			ALIGN(le32_to_cpu(hdr->ucode_size_bytes), PAGE_SIZE);

		अगर (adev->uvd.num_uvd_inst == UVD7_MAX_HW_INSTANCES_VEGA20) अणु
			adev->firmware.ucode[AMDGPU_UCODE_ID_UVD1].ucode_id = AMDGPU_UCODE_ID_UVD1;
			adev->firmware.ucode[AMDGPU_UCODE_ID_UVD1].fw = adev->uvd.fw;
			adev->firmware.fw_size +=
				ALIGN(le32_to_cpu(hdr->ucode_size_bytes), PAGE_SIZE);
		पूर्ण
		DRM_INFO("PSP loading UVD firmware\n");
	पूर्ण

	क्रम (j = 0; j < adev->uvd.num_uvd_inst; j++) अणु
		अगर (adev->uvd.harvest_config & (1 << j))
			जारी;
		अगर (!amdgpu_sriov_vf(adev)) अणु
			ring = &adev->uvd.inst[j].ring;
			प्र_लिखो(ring->name, "uvd_%d", ring->me);
			r = amdgpu_ring_init(adev, ring, 512,
					     &adev->uvd.inst[j].irq, 0,
					     AMDGPU_RING_PRIO_DEFAULT, शून्य);
			अगर (r)
				वापस r;
		पूर्ण

		क्रम (i = 0; i < adev->uvd.num_enc_rings; ++i) अणु
			ring = &adev->uvd.inst[j].ring_enc[i];
			प्र_लिखो(ring->name, "uvd_enc_%d.%d", ring->me, i);
			अगर (amdgpu_sriov_vf(adev)) अणु
				ring->use_करोorbell = true;

				/* currently only use the first enconding ring क्रम
				 * sriov, so set unused location क्रम other unused rings.
				 */
				अगर (i == 0)
					ring->करोorbell_index = adev->करोorbell_index.uvd_vce.uvd_ring0_1 * 2;
				अन्यथा
					ring->करोorbell_index = adev->करोorbell_index.uvd_vce.uvd_ring2_3 * 2 + 1;
			पूर्ण
			r = amdgpu_ring_init(adev, ring, 512,
					     &adev->uvd.inst[j].irq, 0,
					     AMDGPU_RING_PRIO_DEFAULT, शून्य);
			अगर (r)
				वापस r;
		पूर्ण
	पूर्ण

	r = amdgpu_uvd_resume(adev);
	अगर (r)
		वापस r;

	r = amdgpu_uvd_entity_init(adev);
	अगर (r)
		वापस r;

	r = amdgpu_virt_alloc_mm_table(adev);
	अगर (r)
		वापस r;

	वापस r;
पूर्ण

अटल पूर्णांक uvd_v7_0_sw_fini(व्योम *handle)
अणु
	पूर्णांक i, j, r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	amdgpu_virt_मुक्त_mm_table(adev);

	r = amdgpu_uvd_suspend(adev);
	अगर (r)
		वापस r;

	क्रम (j = 0; j < adev->uvd.num_uvd_inst; ++j) अणु
		अगर (adev->uvd.harvest_config & (1 << j))
			जारी;
		क्रम (i = 0; i < adev->uvd.num_enc_rings; ++i)
			amdgpu_ring_fini(&adev->uvd.inst[j].ring_enc[i]);
	पूर्ण
	वापस amdgpu_uvd_sw_fini(adev);
पूर्ण

/**
 * uvd_v7_0_hw_init - start and test UVD block
 *
 * @handle: handle used to pass amdgpu_device poपूर्णांकer
 *
 * Initialize the hardware, boot up the VCPU and करो some testing
 */
अटल पूर्णांक uvd_v7_0_hw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा amdgpu_ring *ring;
	uपूर्णांक32_t पंचांगp;
	पूर्णांक i, j, r;

	अगर (amdgpu_sriov_vf(adev))
		r = uvd_v7_0_sriov_start(adev);
	अन्यथा
		r = uvd_v7_0_start(adev);
	अगर (r)
		जाओ करोne;

	क्रम (j = 0; j < adev->uvd.num_uvd_inst; ++j) अणु
		अगर (adev->uvd.harvest_config & (1 << j))
			जारी;
		ring = &adev->uvd.inst[j].ring;

		अगर (!amdgpu_sriov_vf(adev)) अणु
			r = amdgpu_ring_test_helper(ring);
			अगर (r)
				जाओ करोne;

			r = amdgpu_ring_alloc(ring, 10);
			अगर (r) अणु
				DRM_ERROR("amdgpu: (%d)ring failed to lock UVD ring (%d).\n", j, r);
				जाओ करोne;
			पूर्ण

			पंचांगp = PACKET0(SOC15_REG_OFFSET(UVD, j,
				mmUVD_SEMA_WAIT_FAULT_TIMEOUT_CNTL), 0);
			amdgpu_ring_ग_लिखो(ring, पंचांगp);
			amdgpu_ring_ग_लिखो(ring, 0xFFFFF);

			पंचांगp = PACKET0(SOC15_REG_OFFSET(UVD, j,
				mmUVD_SEMA_WAIT_INCOMPLETE_TIMEOUT_CNTL), 0);
			amdgpu_ring_ग_लिखो(ring, पंचांगp);
			amdgpu_ring_ग_लिखो(ring, 0xFFFFF);

			पंचांगp = PACKET0(SOC15_REG_OFFSET(UVD, j,
				mmUVD_SEMA_SIGNAL_INCOMPLETE_TIMEOUT_CNTL), 0);
			amdgpu_ring_ग_लिखो(ring, पंचांगp);
			amdgpu_ring_ग_लिखो(ring, 0xFFFFF);

			/* Clear समयout status bits */
			amdgpu_ring_ग_लिखो(ring, PACKET0(SOC15_REG_OFFSET(UVD, j,
				mmUVD_SEMA_TIMEOUT_STATUS), 0));
			amdgpu_ring_ग_लिखो(ring, 0x8);

			amdgpu_ring_ग_लिखो(ring, PACKET0(SOC15_REG_OFFSET(UVD, j,
				mmUVD_SEMA_CNTL), 0));
			amdgpu_ring_ग_लिखो(ring, 3);

			amdgpu_ring_commit(ring);
		पूर्ण

		क्रम (i = 0; i < adev->uvd.num_enc_rings; ++i) अणु
			ring = &adev->uvd.inst[j].ring_enc[i];
			r = amdgpu_ring_test_helper(ring);
			अगर (r)
				जाओ करोne;
		पूर्ण
	पूर्ण
करोne:
	अगर (!r)
		DRM_INFO("UVD and UVD ENC initialized successfully.\n");

	वापस r;
पूर्ण

/**
 * uvd_v7_0_hw_fini - stop the hardware block
 *
 * @handle: handle used to pass amdgpu_device poपूर्णांकer
 *
 * Stop the UVD block, mark ring as not पढ़ोy any more
 */
अटल पूर्णांक uvd_v7_0_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (!amdgpu_sriov_vf(adev))
		uvd_v7_0_stop(adev);
	अन्यथा अणु
		/* full access mode, so करोn't touch any UVD रेजिस्टर */
		DRM_DEBUG("For SRIOV client, shouldn't do anything.\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uvd_v7_0_suspend(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = uvd_v7_0_hw_fini(adev);
	अगर (r)
		वापस r;

	वापस amdgpu_uvd_suspend(adev);
पूर्ण

अटल पूर्णांक uvd_v7_0_resume(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = amdgpu_uvd_resume(adev);
	अगर (r)
		वापस r;

	वापस uvd_v7_0_hw_init(adev);
पूर्ण

/**
 * uvd_v7_0_mc_resume - memory controller programming
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Let the UVD memory controller know it's offsets
 */
अटल व्योम uvd_v7_0_mc_resume(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t size = AMDGPU_UVD_FIRMWARE_SIZE(adev);
	uपूर्णांक32_t offset;
	पूर्णांक i;

	क्रम (i = 0; i < adev->uvd.num_uvd_inst; ++i) अणु
		अगर (adev->uvd.harvest_config & (1 << i))
			जारी;
		अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
			WREG32_SOC15(UVD, i, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW,
				i == 0 ?
				adev->firmware.ucode[AMDGPU_UCODE_ID_UVD].पंचांगr_mc_addr_lo:
				adev->firmware.ucode[AMDGPU_UCODE_ID_UVD1].पंचांगr_mc_addr_lo);
			WREG32_SOC15(UVD, i, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH,
				i == 0 ?
				adev->firmware.ucode[AMDGPU_UCODE_ID_UVD].पंचांगr_mc_addr_hi:
				adev->firmware.ucode[AMDGPU_UCODE_ID_UVD1].पंचांगr_mc_addr_hi);
			WREG32_SOC15(UVD, i, mmUVD_VCPU_CACHE_OFFSET0, 0);
			offset = 0;
		पूर्ण अन्यथा अणु
			WREG32_SOC15(UVD, i, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW,
				lower_32_bits(adev->uvd.inst[i].gpu_addr));
			WREG32_SOC15(UVD, i, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH,
				upper_32_bits(adev->uvd.inst[i].gpu_addr));
			offset = size;
			WREG32_SOC15(UVD, i, mmUVD_VCPU_CACHE_OFFSET0,
					AMDGPU_UVD_FIRMWARE_OFFSET >> 3);
		पूर्ण

		WREG32_SOC15(UVD, i, mmUVD_VCPU_CACHE_SIZE0, size);

		WREG32_SOC15(UVD, i, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW,
				lower_32_bits(adev->uvd.inst[i].gpu_addr + offset));
		WREG32_SOC15(UVD, i, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH,
				upper_32_bits(adev->uvd.inst[i].gpu_addr + offset));
		WREG32_SOC15(UVD, i, mmUVD_VCPU_CACHE_OFFSET1, (1 << 21));
		WREG32_SOC15(UVD, i, mmUVD_VCPU_CACHE_SIZE1, AMDGPU_UVD_HEAP_SIZE);

		WREG32_SOC15(UVD, i, mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW,
				lower_32_bits(adev->uvd.inst[i].gpu_addr + offset + AMDGPU_UVD_HEAP_SIZE));
		WREG32_SOC15(UVD, i, mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH,
				upper_32_bits(adev->uvd.inst[i].gpu_addr + offset + AMDGPU_UVD_HEAP_SIZE));
		WREG32_SOC15(UVD, i, mmUVD_VCPU_CACHE_OFFSET2, (2 << 21));
		WREG32_SOC15(UVD, i, mmUVD_VCPU_CACHE_SIZE2,
				AMDGPU_UVD_STACK_SIZE + (AMDGPU_UVD_SESSION_SIZE * 40));

		WREG32_SOC15(UVD, i, mmUVD_UDEC_ADDR_CONFIG,
				adev->gfx.config.gb_addr_config);
		WREG32_SOC15(UVD, i, mmUVD_UDEC_DB_ADDR_CONFIG,
				adev->gfx.config.gb_addr_config);
		WREG32_SOC15(UVD, i, mmUVD_UDEC_DBW_ADDR_CONFIG,
				adev->gfx.config.gb_addr_config);

		WREG32_SOC15(UVD, i, mmUVD_GP_SCRATCH4, adev->uvd.max_handles);
	पूर्ण
पूर्ण

अटल पूर्णांक uvd_v7_0_mmsch_start(काष्ठा amdgpu_device *adev,
				काष्ठा amdgpu_mm_table *table)
अणु
	uपूर्णांक32_t data = 0, loop;
	uपूर्णांक64_t addr = table->gpu_addr;
	काष्ठा mmsch_v1_0_init_header *header = (काष्ठा mmsch_v1_0_init_header *)table->cpu_addr;
	uपूर्णांक32_t size;
	पूर्णांक i;

	size = header->header_size + header->vce_table_size + header->uvd_table_size;

	/* 1, ग_लिखो to vce_mmsch_vf_ctx_addr_lo/hi रेजिस्टर with GPU mc addr of memory descriptor location */
	WREG32_SOC15(VCE, 0, mmVCE_MMSCH_VF_CTX_ADDR_LO, lower_32_bits(addr));
	WREG32_SOC15(VCE, 0, mmVCE_MMSCH_VF_CTX_ADDR_HI, upper_32_bits(addr));

	/* 2, update vmid of descriptor */
	data = RREG32_SOC15(VCE, 0, mmVCE_MMSCH_VF_VMID);
	data &= ~VCE_MMSCH_VF_VMID__VF_CTX_VMID_MASK;
	data |= (0 << VCE_MMSCH_VF_VMID__VF_CTX_VMID__SHIFT); /* use करोमुख्य0 क्रम MM scheduler */
	WREG32_SOC15(VCE, 0, mmVCE_MMSCH_VF_VMID, data);

	/* 3, notअगरy mmsch about the size of this descriptor */
	WREG32_SOC15(VCE, 0, mmVCE_MMSCH_VF_CTX_SIZE, size);

	/* 4, set resp to zero */
	WREG32_SOC15(VCE, 0, mmVCE_MMSCH_VF_MAILBOX_RESP, 0);

	क्रम (i = 0; i < adev->uvd.num_uvd_inst; ++i) अणु
		अगर (adev->uvd.harvest_config & (1 << i))
			जारी;
		WDOORBELL32(adev->uvd.inst[i].ring_enc[0].करोorbell_index, 0);
		adev->wb.wb[adev->uvd.inst[i].ring_enc[0].wptr_offs] = 0;
		adev->uvd.inst[i].ring_enc[0].wptr = 0;
		adev->uvd.inst[i].ring_enc[0].wptr_old = 0;
	पूर्ण
	/* 5, kick off the initialization and रुको until VCE_MMSCH_VF_MAILBOX_RESP becomes non-zero */
	WREG32_SOC15(VCE, 0, mmVCE_MMSCH_VF_MAILBOX_HOST, 0x10000001);

	data = RREG32_SOC15(VCE, 0, mmVCE_MMSCH_VF_MAILBOX_RESP);
	loop = 1000;
	जबतक ((data & 0x10000002) != 0x10000002) अणु
		udelay(10);
		data = RREG32_SOC15(VCE, 0, mmVCE_MMSCH_VF_MAILBOX_RESP);
		loop--;
		अगर (!loop)
			अवरोध;
	पूर्ण

	अगर (!loop) अणु
		dev_err(adev->dev, "failed to init MMSCH, mmVCE_MMSCH_VF_MAILBOX_RESP = %x\n", data);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uvd_v7_0_sriov_start(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring;
	uपूर्णांक32_t offset, size, पंचांगp;
	uपूर्णांक32_t table_size = 0;
	काष्ठा mmsch_v1_0_cmd_direct_ग_लिखो direct_wt = अणु अणु0पूर्ण पूर्ण;
	काष्ठा mmsch_v1_0_cmd_direct_पढ़ो_modअगरy_ग_लिखो direct_rd_mod_wt = अणु अणु0पूर्ण पूर्ण;
	काष्ठा mmsch_v1_0_cmd_direct_polling direct_poll = अणु अणु0पूर्ण पूर्ण;
	काष्ठा mmsch_v1_0_cmd_end end = अणु अणु0पूर्ण पूर्ण;
	uपूर्णांक32_t *init_table = adev->virt.mm_table.cpu_addr;
	काष्ठा mmsch_v1_0_init_header *header = (काष्ठा mmsch_v1_0_init_header *)init_table;
	uपूर्णांक8_t i = 0;

	direct_wt.cmd_header.command_type = MMSCH_COMMAND__सूचीECT_REG_WRITE;
	direct_rd_mod_wt.cmd_header.command_type = MMSCH_COMMAND__सूचीECT_REG_READ_MODIFY_WRITE;
	direct_poll.cmd_header.command_type = MMSCH_COMMAND__सूचीECT_REG_POLLING;
	end.cmd_header.command_type = MMSCH_COMMAND__END;

	अगर (header->uvd_table_offset == 0 && header->uvd_table_size == 0) अणु
		header->version = MMSCH_VERSION;
		header->header_size = माप(काष्ठा mmsch_v1_0_init_header) >> 2;

		अगर (header->vce_table_offset == 0 && header->vce_table_size == 0)
			header->uvd_table_offset = header->header_size;
		अन्यथा
			header->uvd_table_offset = header->vce_table_size + header->vce_table_offset;

		init_table += header->uvd_table_offset;

		क्रम (i = 0; i < adev->uvd.num_uvd_inst; ++i) अणु
			अगर (adev->uvd.harvest_config & (1 << i))
				जारी;
			ring = &adev->uvd.inst[i].ring;
			ring->wptr = 0;
			size = AMDGPU_GPU_PAGE_ALIGN(adev->uvd.fw->size + 4);

			MMSCH_V1_0_INSERT_सूचीECT_RD_MOD_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_STATUS),
							   0xFFFFFFFF, 0x00000004);
			/* mc resume*/
			अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP) अणु
				MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i,
							mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW),
							adev->firmware.ucode[AMDGPU_UCODE_ID_UVD].पंचांगr_mc_addr_lo);
				MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i,
							mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH),
							adev->firmware.ucode[AMDGPU_UCODE_ID_UVD].पंचांगr_mc_addr_hi);
				MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, 0, mmUVD_VCPU_CACHE_OFFSET0), 0);
				offset = 0;
			पूर्ण अन्यथा अणु
				MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_LOW),
							    lower_32_bits(adev->uvd.inst[i].gpu_addr));
				MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_LMI_VCPU_CACHE_64BIT_BAR_HIGH),
							    upper_32_bits(adev->uvd.inst[i].gpu_addr));
				offset = size;
				MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, 0, mmUVD_VCPU_CACHE_OFFSET0),
							AMDGPU_UVD_FIRMWARE_OFFSET >> 3);

			पूर्ण

			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_VCPU_CACHE_SIZE0), size);

			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_LOW),
						    lower_32_bits(adev->uvd.inst[i].gpu_addr + offset));
			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_LMI_VCPU_CACHE1_64BIT_BAR_HIGH),
						    upper_32_bits(adev->uvd.inst[i].gpu_addr + offset));
			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_VCPU_CACHE_OFFSET1), (1 << 21));
			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_VCPU_CACHE_SIZE1), AMDGPU_UVD_HEAP_SIZE);

			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_LOW),
						    lower_32_bits(adev->uvd.inst[i].gpu_addr + offset + AMDGPU_UVD_HEAP_SIZE));
			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_LMI_VCPU_CACHE2_64BIT_BAR_HIGH),
						    upper_32_bits(adev->uvd.inst[i].gpu_addr + offset + AMDGPU_UVD_HEAP_SIZE));
			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_VCPU_CACHE_OFFSET2), (2 << 21));
			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_VCPU_CACHE_SIZE2),
						    AMDGPU_UVD_STACK_SIZE + (AMDGPU_UVD_SESSION_SIZE * 40));

			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_GP_SCRATCH4), adev->uvd.max_handles);
			/* mc resume end*/

			/* disable घड़ी gating */
			MMSCH_V1_0_INSERT_सूचीECT_RD_MOD_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_CGC_CTRL),
							   ~UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK, 0);

			/* disable पूर्णांकerupt */
			MMSCH_V1_0_INSERT_सूचीECT_RD_MOD_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_MASTINT_EN),
							   ~UVD_MASTINT_EN__VCPU_EN_MASK, 0);

			/* stall UMC and रेजिस्टर bus beक्रमe resetting VCPU */
			MMSCH_V1_0_INSERT_सूचीECT_RD_MOD_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_LMI_CTRL2),
							   ~UVD_LMI_CTRL2__STALL_ARB_UMC_MASK,
							   UVD_LMI_CTRL2__STALL_ARB_UMC_MASK);

			/* put LMI, VCPU, RBC etc... पूर्णांकo reset */
			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_SOFT_RESET),
						    (uपूर्णांक32_t)(UVD_SOFT_RESET__LMI_SOFT_RESET_MASK |
							       UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK |
							       UVD_SOFT_RESET__LBSI_SOFT_RESET_MASK |
							       UVD_SOFT_RESET__RBC_SOFT_RESET_MASK |
							       UVD_SOFT_RESET__CSM_SOFT_RESET_MASK |
							       UVD_SOFT_RESET__CXW_SOFT_RESET_MASK |
							       UVD_SOFT_RESET__TAP_SOFT_RESET_MASK |
							       UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK));

			/* initialize UVD memory controller */
			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_LMI_CTRL),
						    (uपूर्णांक32_t)((0x40 << UVD_LMI_CTRL__WRITE_CLEAN_TIMER__SHIFT) |
							       UVD_LMI_CTRL__WRITE_CLEAN_TIMER_EN_MASK |
							       UVD_LMI_CTRL__DATA_COHERENCY_EN_MASK |
							       UVD_LMI_CTRL__VCPU_DATA_COHERENCY_EN_MASK |
							       UVD_LMI_CTRL__REQ_MODE_MASK |
							       0x00100000L));

			/* take all subblocks out of reset, except VCPU */
			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_SOFT_RESET),
						    UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);

			/* enable VCPU घड़ी */
			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_VCPU_CNTL),
						    UVD_VCPU_CNTL__CLK_EN_MASK);

			/* enable master पूर्णांकerrupt */
			MMSCH_V1_0_INSERT_सूचीECT_RD_MOD_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_MASTINT_EN),
							   ~(UVD_MASTINT_EN__VCPU_EN_MASK|UVD_MASTINT_EN__SYS_EN_MASK),
							   (UVD_MASTINT_EN__VCPU_EN_MASK|UVD_MASTINT_EN__SYS_EN_MASK));

			/* clear the bit 4 of UVD_STATUS */
			MMSCH_V1_0_INSERT_सूचीECT_RD_MOD_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_STATUS),
							   ~(2 << UVD_STATUS__VCPU_REPORT__SHIFT), 0);

			/* क्रमce RBC पूर्णांकo idle state */
			size = order_base_2(ring->ring_size);
			पंचांगp = REG_SET_FIELD(0, UVD_RBC_RB_CNTL, RB_BUFSZ, size);
			पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_NO_FETCH, 1);
			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_RBC_RB_CNTL), पंचांगp);

			ring = &adev->uvd.inst[i].ring_enc[0];
			ring->wptr = 0;
			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_RB_BASE_LO), ring->gpu_addr);
			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_RB_BASE_HI), upper_32_bits(ring->gpu_addr));
			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_RB_SIZE), ring->ring_size / 4);

			/* boot up the VCPU */
			MMSCH_V1_0_INSERT_सूचीECT_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_SOFT_RESET), 0);

			/* enable UMC */
			MMSCH_V1_0_INSERT_सूचीECT_RD_MOD_WT(SOC15_REG_OFFSET(UVD, i, mmUVD_LMI_CTRL2),
											   ~UVD_LMI_CTRL2__STALL_ARB_UMC_MASK, 0);

			MMSCH_V1_0_INSERT_सूचीECT_POLL(SOC15_REG_OFFSET(UVD, i, mmUVD_STATUS), 0x02, 0x02);
		पूर्ण
		/* add end packet */
		स_नकल((व्योम *)init_table, &end, माप(काष्ठा mmsch_v1_0_cmd_end));
		table_size += माप(काष्ठा mmsch_v1_0_cmd_end) / 4;
		header->uvd_table_size = table_size;

	पूर्ण
	वापस uvd_v7_0_mmsch_start(adev, &adev->virt.mm_table);
पूर्ण

/**
 * uvd_v7_0_start - start UVD block
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Setup and start the UVD block
 */
अटल पूर्णांक uvd_v7_0_start(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring;
	uपूर्णांक32_t rb_bufsz, पंचांगp;
	uपूर्णांक32_t lmi_swap_cntl;
	uपूर्णांक32_t mp_swap_cntl;
	पूर्णांक i, j, k, r;

	क्रम (k = 0; k < adev->uvd.num_uvd_inst; ++k) अणु
		अगर (adev->uvd.harvest_config & (1 << k))
			जारी;
		/* disable DPG */
		WREG32_P(SOC15_REG_OFFSET(UVD, k, mmUVD_POWER_STATUS), 0,
				~UVD_POWER_STATUS__UVD_PG_MODE_MASK);
	पूर्ण

	/* disable byte swapping */
	lmi_swap_cntl = 0;
	mp_swap_cntl = 0;

	uvd_v7_0_mc_resume(adev);

	क्रम (k = 0; k < adev->uvd.num_uvd_inst; ++k) अणु
		अगर (adev->uvd.harvest_config & (1 << k))
			जारी;
		ring = &adev->uvd.inst[k].ring;
		/* disable घड़ी gating */
		WREG32_P(SOC15_REG_OFFSET(UVD, k, mmUVD_CGC_CTRL), 0,
				~UVD_CGC_CTRL__DYN_CLOCK_MODE_MASK);

		/* disable पूर्णांकerupt */
		WREG32_P(SOC15_REG_OFFSET(UVD, k, mmUVD_MASTINT_EN), 0,
				~UVD_MASTINT_EN__VCPU_EN_MASK);

		/* stall UMC and रेजिस्टर bus beक्रमe resetting VCPU */
		WREG32_P(SOC15_REG_OFFSET(UVD, k, mmUVD_LMI_CTRL2),
				UVD_LMI_CTRL2__STALL_ARB_UMC_MASK,
				~UVD_LMI_CTRL2__STALL_ARB_UMC_MASK);
		mdelay(1);

		/* put LMI, VCPU, RBC etc... पूर्णांकo reset */
		WREG32_SOC15(UVD, k, mmUVD_SOFT_RESET,
			UVD_SOFT_RESET__LMI_SOFT_RESET_MASK |
			UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK |
			UVD_SOFT_RESET__LBSI_SOFT_RESET_MASK |
			UVD_SOFT_RESET__RBC_SOFT_RESET_MASK |
			UVD_SOFT_RESET__CSM_SOFT_RESET_MASK |
			UVD_SOFT_RESET__CXW_SOFT_RESET_MASK |
			UVD_SOFT_RESET__TAP_SOFT_RESET_MASK |
			UVD_SOFT_RESET__LMI_UMC_SOFT_RESET_MASK);
		mdelay(5);

		/* initialize UVD memory controller */
		WREG32_SOC15(UVD, k, mmUVD_LMI_CTRL,
			(0x40 << UVD_LMI_CTRL__WRITE_CLEAN_TIMER__SHIFT) |
			UVD_LMI_CTRL__WRITE_CLEAN_TIMER_EN_MASK |
			UVD_LMI_CTRL__DATA_COHERENCY_EN_MASK |
			UVD_LMI_CTRL__VCPU_DATA_COHERENCY_EN_MASK |
			UVD_LMI_CTRL__REQ_MODE_MASK |
			0x00100000L);

#अगर_घोषित __BIG_ENDIAN
		/* swap (8 in 32) RB and IB */
		lmi_swap_cntl = 0xa;
		mp_swap_cntl = 0;
#पूर्ण_अगर
		WREG32_SOC15(UVD, k, mmUVD_LMI_SWAP_CNTL, lmi_swap_cntl);
		WREG32_SOC15(UVD, k, mmUVD_MP_SWAP_CNTL, mp_swap_cntl);

		WREG32_SOC15(UVD, k, mmUVD_MPC_SET_MUXA0, 0x40c2040);
		WREG32_SOC15(UVD, k, mmUVD_MPC_SET_MUXA1, 0x0);
		WREG32_SOC15(UVD, k, mmUVD_MPC_SET_MUXB0, 0x40c2040);
		WREG32_SOC15(UVD, k, mmUVD_MPC_SET_MUXB1, 0x0);
		WREG32_SOC15(UVD, k, mmUVD_MPC_SET_ALU, 0);
		WREG32_SOC15(UVD, k, mmUVD_MPC_SET_MUX, 0x88);

		/* take all subblocks out of reset, except VCPU */
		WREG32_SOC15(UVD, k, mmUVD_SOFT_RESET,
				UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);
		mdelay(5);

		/* enable VCPU घड़ी */
		WREG32_SOC15(UVD, k, mmUVD_VCPU_CNTL,
				UVD_VCPU_CNTL__CLK_EN_MASK);

		/* enable UMC */
		WREG32_P(SOC15_REG_OFFSET(UVD, k, mmUVD_LMI_CTRL2), 0,
				~UVD_LMI_CTRL2__STALL_ARB_UMC_MASK);

		/* boot up the VCPU */
		WREG32_SOC15(UVD, k, mmUVD_SOFT_RESET, 0);
		mdelay(10);

		क्रम (i = 0; i < 10; ++i) अणु
			uपूर्णांक32_t status;

			क्रम (j = 0; j < 100; ++j) अणु
				status = RREG32_SOC15(UVD, k, mmUVD_STATUS);
				अगर (status & 2)
					अवरोध;
				mdelay(10);
			पूर्ण
			r = 0;
			अगर (status & 2)
				अवरोध;

			DRM_ERROR("UVD(%d) not responding, trying to reset the VCPU!!!\n", k);
			WREG32_P(SOC15_REG_OFFSET(UVD, k, mmUVD_SOFT_RESET),
					UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK,
					~UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);
			mdelay(10);
			WREG32_P(SOC15_REG_OFFSET(UVD, k, mmUVD_SOFT_RESET), 0,
					~UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);
			mdelay(10);
			r = -1;
		पूर्ण

		अगर (r) अणु
			DRM_ERROR("UVD(%d) not responding, giving up!!!\n", k);
			वापस r;
		पूर्ण
		/* enable master पूर्णांकerrupt */
		WREG32_P(SOC15_REG_OFFSET(UVD, k, mmUVD_MASTINT_EN),
			(UVD_MASTINT_EN__VCPU_EN_MASK|UVD_MASTINT_EN__SYS_EN_MASK),
			~(UVD_MASTINT_EN__VCPU_EN_MASK|UVD_MASTINT_EN__SYS_EN_MASK));

		/* clear the bit 4 of UVD_STATUS */
		WREG32_P(SOC15_REG_OFFSET(UVD, k, mmUVD_STATUS), 0,
				~(2 << UVD_STATUS__VCPU_REPORT__SHIFT));

		/* क्रमce RBC पूर्णांकo idle state */
		rb_bufsz = order_base_2(ring->ring_size);
		पंचांगp = REG_SET_FIELD(0, UVD_RBC_RB_CNTL, RB_BUFSZ, rb_bufsz);
		पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_BLKSZ, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_NO_FETCH, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_WPTR_POLL_EN, 0);
		पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_NO_UPDATE, 1);
		पंचांगp = REG_SET_FIELD(पंचांगp, UVD_RBC_RB_CNTL, RB_RPTR_WR_EN, 1);
		WREG32_SOC15(UVD, k, mmUVD_RBC_RB_CNTL, पंचांगp);

		/* set the ग_लिखो poपूर्णांकer delay */
		WREG32_SOC15(UVD, k, mmUVD_RBC_RB_WPTR_CNTL, 0);

		/* set the wb address */
		WREG32_SOC15(UVD, k, mmUVD_RBC_RB_RPTR_ADDR,
				(upper_32_bits(ring->gpu_addr) >> 2));

		/* program the RB_BASE क्रम ring buffer */
		WREG32_SOC15(UVD, k, mmUVD_LMI_RBC_RB_64BIT_BAR_LOW,
				lower_32_bits(ring->gpu_addr));
		WREG32_SOC15(UVD, k, mmUVD_LMI_RBC_RB_64BIT_BAR_HIGH,
				upper_32_bits(ring->gpu_addr));

		/* Initialize the ring buffer's पढ़ो and ग_लिखो poपूर्णांकers */
		WREG32_SOC15(UVD, k, mmUVD_RBC_RB_RPTR, 0);

		ring->wptr = RREG32_SOC15(UVD, k, mmUVD_RBC_RB_RPTR);
		WREG32_SOC15(UVD, k, mmUVD_RBC_RB_WPTR,
				lower_32_bits(ring->wptr));

		WREG32_P(SOC15_REG_OFFSET(UVD, k, mmUVD_RBC_RB_CNTL), 0,
				~UVD_RBC_RB_CNTL__RB_NO_FETCH_MASK);

		ring = &adev->uvd.inst[k].ring_enc[0];
		WREG32_SOC15(UVD, k, mmUVD_RB_RPTR, lower_32_bits(ring->wptr));
		WREG32_SOC15(UVD, k, mmUVD_RB_WPTR, lower_32_bits(ring->wptr));
		WREG32_SOC15(UVD, k, mmUVD_RB_BASE_LO, ring->gpu_addr);
		WREG32_SOC15(UVD, k, mmUVD_RB_BASE_HI, upper_32_bits(ring->gpu_addr));
		WREG32_SOC15(UVD, k, mmUVD_RB_SIZE, ring->ring_size / 4);

		ring = &adev->uvd.inst[k].ring_enc[1];
		WREG32_SOC15(UVD, k, mmUVD_RB_RPTR2, lower_32_bits(ring->wptr));
		WREG32_SOC15(UVD, k, mmUVD_RB_WPTR2, lower_32_bits(ring->wptr));
		WREG32_SOC15(UVD, k, mmUVD_RB_BASE_LO2, ring->gpu_addr);
		WREG32_SOC15(UVD, k, mmUVD_RB_BASE_HI2, upper_32_bits(ring->gpu_addr));
		WREG32_SOC15(UVD, k, mmUVD_RB_SIZE2, ring->ring_size / 4);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * uvd_v7_0_stop - stop UVD block
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * stop the UVD block
 */
अटल व्योम uvd_v7_0_stop(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक8_t i = 0;

	क्रम (i = 0; i < adev->uvd.num_uvd_inst; ++i) अणु
		अगर (adev->uvd.harvest_config & (1 << i))
			जारी;
		/* क्रमce RBC पूर्णांकo idle state */
		WREG32_SOC15(UVD, i, mmUVD_RBC_RB_CNTL, 0x11010101);

		/* Stall UMC and रेजिस्टर bus beक्रमe resetting VCPU */
		WREG32_P(SOC15_REG_OFFSET(UVD, i, mmUVD_LMI_CTRL2),
				UVD_LMI_CTRL2__STALL_ARB_UMC_MASK,
				~UVD_LMI_CTRL2__STALL_ARB_UMC_MASK);
		mdelay(1);

		/* put VCPU पूर्णांकo reset */
		WREG32_SOC15(UVD, i, mmUVD_SOFT_RESET,
				UVD_SOFT_RESET__VCPU_SOFT_RESET_MASK);
		mdelay(5);

		/* disable VCPU घड़ी */
		WREG32_SOC15(UVD, i, mmUVD_VCPU_CNTL, 0x0);

		/* Unstall UMC and रेजिस्टर bus */
		WREG32_P(SOC15_REG_OFFSET(UVD, i, mmUVD_LMI_CTRL2), 0,
				~UVD_LMI_CTRL2__STALL_ARB_UMC_MASK);
	पूर्ण
पूर्ण

/**
 * uvd_v7_0_ring_emit_fence - emit an fence & trap command
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @addr: address
 * @seq: sequence number
 * @flags: fence related flags
 *
 * Write a fence and a trap command to the ring.
 */
अटल व्योम uvd_v7_0_ring_emit_fence(काष्ठा amdgpu_ring *ring, u64 addr, u64 seq,
				     अचिन्हित flags)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	WARN_ON(flags & AMDGPU_FENCE_FLAG_64BIT);

	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_CONTEXT_ID), 0));
	amdgpu_ring_ग_लिखो(ring, seq);
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_GPCOM_VCPU_DATA0), 0));
	amdgpu_ring_ग_लिखो(ring, addr & 0xffffffff);
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_GPCOM_VCPU_DATA1), 0));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr) & 0xff);
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_GPCOM_VCPU_CMD), 0));
	amdgpu_ring_ग_लिखो(ring, 0);

	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_GPCOM_VCPU_DATA0), 0));
	amdgpu_ring_ग_लिखो(ring, 0);
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_GPCOM_VCPU_DATA1), 0));
	amdgpu_ring_ग_लिखो(ring, 0);
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_GPCOM_VCPU_CMD), 0));
	amdgpu_ring_ग_लिखो(ring, 2);
पूर्ण

/**
 * uvd_v7_0_enc_ring_emit_fence - emit an enc fence & trap command
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @addr: address
 * @seq: sequence number
 * @flags: fence related flags
 *
 * Write enc a fence and a trap command to the ring.
 */
अटल व्योम uvd_v7_0_enc_ring_emit_fence(काष्ठा amdgpu_ring *ring, u64 addr,
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
 * uvd_v7_0_ring_emit_hdp_flush - skip HDP flushing
 *
 * @ring: amdgpu_ring poपूर्णांकer
 */
अटल व्योम uvd_v7_0_ring_emit_hdp_flush(काष्ठा amdgpu_ring *ring)
अणु
	/* The firmware करोesn't seem to like touching रेजिस्टरs at this poपूर्णांक. */
पूर्ण

/**
 * uvd_v7_0_ring_test_ring - रेजिस्टर ग_लिखो test
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Test अगर we can successfully ग_लिखो to the context रेजिस्टर
 */
अटल पूर्णांक uvd_v7_0_ring_test_ring(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	uपूर्णांक32_t पंचांगp = 0;
	अचिन्हित i;
	पूर्णांक r;

	WREG32_SOC15(UVD, ring->me, mmUVD_CONTEXT_ID, 0xCAFEDEAD);
	r = amdgpu_ring_alloc(ring, 3);
	अगर (r)
		वापस r;

	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_CONTEXT_ID), 0));
	amdgpu_ring_ग_लिखो(ring, 0xDEADBEEF);
	amdgpu_ring_commit(ring);
	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		पंचांगp = RREG32_SOC15(UVD, ring->me, mmUVD_CONTEXT_ID);
		अगर (पंचांगp == 0xDEADBEEF)
			अवरोध;
		udelay(1);
	पूर्ण

	अगर (i >= adev->usec_समयout)
		r = -ETIMEDOUT;

	वापस r;
पूर्ण

/**
 * uvd_v7_0_ring_patch_cs_in_place - Patch the IB क्रम command submission.
 *
 * @p: the CS parser with the IBs
 * @ib_idx: which IB to patch
 *
 */
अटल पूर्णांक uvd_v7_0_ring_patch_cs_in_place(काष्ठा amdgpu_cs_parser *p,
					   uपूर्णांक32_t ib_idx)
अणु
	काष्ठा amdgpu_ring *ring = to_amdgpu_ring(p->entity->rq->sched);
	काष्ठा amdgpu_ib *ib = &p->job->ibs[ib_idx];
	अचिन्हित i;

	/* No patching necessary क्रम the first instance */
	अगर (!ring->me)
		वापस 0;

	क्रम (i = 0; i < ib->length_dw; i += 2) अणु
		uपूर्णांक32_t reg = amdgpu_get_ib_value(p, ib_idx, i);

		reg -= p->adev->reg_offset[UVD_HWIP][0][1];
		reg += p->adev->reg_offset[UVD_HWIP][1][1];

		amdgpu_set_ib_value(p, ib_idx, i, reg);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * uvd_v7_0_ring_emit_ib - execute indirect buffer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @job: job to retrieve vmid from
 * @ib: indirect buffer to execute
 * @flags: unused
 *
 * Write ring commands to execute the indirect buffer
 */
अटल व्योम uvd_v7_0_ring_emit_ib(काष्ठा amdgpu_ring *ring,
				  काष्ठा amdgpu_job *job,
				  काष्ठा amdgpu_ib *ib,
				  uपूर्णांक32_t flags)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	अचिन्हित vmid = AMDGPU_JOB_GET_VMID(job);

	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_LMI_RBC_IB_VMID), 0));
	amdgpu_ring_ग_लिखो(ring, vmid);

	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_LMI_RBC_IB_64BIT_BAR_LOW), 0));
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(ib->gpu_addr));
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_LMI_RBC_IB_64BIT_BAR_HIGH), 0));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr));
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_RBC_IB_SIZE), 0));
	amdgpu_ring_ग_लिखो(ring, ib->length_dw);
पूर्ण

/**
 * uvd_v7_0_enc_ring_emit_ib - enc execute indirect buffer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 * @job: job to retrive vmid from
 * @ib: indirect buffer to execute
 * @flags: unused
 *
 * Write enc ring commands to execute the indirect buffer
 */
अटल व्योम uvd_v7_0_enc_ring_emit_ib(काष्ठा amdgpu_ring *ring,
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

अटल व्योम uvd_v7_0_ring_emit_wreg(काष्ठा amdgpu_ring *ring,
				    uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_GPCOM_VCPU_DATA0), 0));
	amdgpu_ring_ग_लिखो(ring, reg << 2);
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_GPCOM_VCPU_DATA1), 0));
	amdgpu_ring_ग_लिखो(ring, val);
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_GPCOM_VCPU_CMD), 0));
	amdgpu_ring_ग_लिखो(ring, 8);
पूर्ण

अटल व्योम uvd_v7_0_ring_emit_reg_रुको(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t reg,
					uपूर्णांक32_t val, uपूर्णांक32_t mask)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_GPCOM_VCPU_DATA0), 0));
	amdgpu_ring_ग_लिखो(ring, reg << 2);
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_GPCOM_VCPU_DATA1), 0));
	amdgpu_ring_ग_लिखो(ring, val);
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_GP_SCRATCH8), 0));
	amdgpu_ring_ग_लिखो(ring, mask);
	amdgpu_ring_ग_लिखो(ring,
		PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_GPCOM_VCPU_CMD), 0));
	amdgpu_ring_ग_लिखो(ring, 12);
पूर्ण

अटल व्योम uvd_v7_0_ring_emit_vm_flush(काष्ठा amdgpu_ring *ring,
					अचिन्हित vmid, uपूर्णांक64_t pd_addr)
अणु
	काष्ठा amdgpu_vmhub *hub = &ring->adev->vmhub[ring->funcs->vmhub];
	uपूर्णांक32_t data0, data1, mask;

	pd_addr = amdgpu_gmc_emit_flush_gpu_tlb(ring, vmid, pd_addr);

	/* रुको क्रम reg ग_लिखोs */
	data0 = hub->ctx0_ptb_addr_lo32 + vmid * hub->ctx_addr_distance;
	data1 = lower_32_bits(pd_addr);
	mask = 0xffffffff;
	uvd_v7_0_ring_emit_reg_रुको(ring, data0, data1, mask);
पूर्ण

अटल व्योम uvd_v7_0_ring_insert_nop(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t count)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	पूर्णांक i;

	WARN_ON(ring->wptr % 2 || count % 2);

	क्रम (i = 0; i < count / 2; i++) अणु
		amdgpu_ring_ग_लिखो(ring, PACKET0(SOC15_REG_OFFSET(UVD, ring->me, mmUVD_NO_OP), 0));
		amdgpu_ring_ग_लिखो(ring, 0);
	पूर्ण
पूर्ण

अटल व्योम uvd_v7_0_enc_ring_insert_end(काष्ठा amdgpu_ring *ring)
अणु
	amdgpu_ring_ग_लिखो(ring, HEVC_ENC_CMD_END);
पूर्ण

अटल व्योम uvd_v7_0_enc_ring_emit_reg_रुको(काष्ठा amdgpu_ring *ring,
					    uपूर्णांक32_t reg, uपूर्णांक32_t val,
					    uपूर्णांक32_t mask)
अणु
	amdgpu_ring_ग_लिखो(ring, HEVC_ENC_CMD_REG_WAIT);
	amdgpu_ring_ग_लिखो(ring,	reg << 2);
	amdgpu_ring_ग_लिखो(ring, mask);
	amdgpu_ring_ग_लिखो(ring, val);
पूर्ण

अटल व्योम uvd_v7_0_enc_ring_emit_vm_flush(काष्ठा amdgpu_ring *ring,
					    अचिन्हित पूर्णांक vmid, uपूर्णांक64_t pd_addr)
अणु
	काष्ठा amdgpu_vmhub *hub = &ring->adev->vmhub[ring->funcs->vmhub];

	pd_addr = amdgpu_gmc_emit_flush_gpu_tlb(ring, vmid, pd_addr);

	/* रुको क्रम reg ग_लिखोs */
	uvd_v7_0_enc_ring_emit_reg_रुको(ring, hub->ctx0_ptb_addr_lo32 +
					vmid * hub->ctx_addr_distance,
					lower_32_bits(pd_addr), 0xffffffff);
पूर्ण

अटल व्योम uvd_v7_0_enc_ring_emit_wreg(काष्ठा amdgpu_ring *ring,
					uपूर्णांक32_t reg, uपूर्णांक32_t val)
अणु
	amdgpu_ring_ग_लिखो(ring, HEVC_ENC_CMD_REG_WRITE);
	amdgpu_ring_ग_लिखो(ring,	reg << 2);
	amdgpu_ring_ग_लिखो(ring, val);
पूर्ण

#अगर 0
अटल bool uvd_v7_0_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस !(RREG32(mmSRBM_STATUS) & SRBM_STATUS__UVD_BUSY_MASK);
पूर्ण

अटल पूर्णांक uvd_v7_0_रुको_क्रम_idle(व्योम *handle)
अणु
	अचिन्हित i;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर (uvd_v7_0_is_idle(handle))
			वापस 0;
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

#घोषणा AMDGPU_UVD_STATUS_BUSY_MASK    0xfd
अटल bool uvd_v7_0_check_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 srbm_soft_reset = 0;
	u32 पंचांगp = RREG32(mmSRBM_STATUS);

	अगर (REG_GET_FIELD(पंचांगp, SRBM_STATUS, UVD_RQ_PENDING) ||
	    REG_GET_FIELD(पंचांगp, SRBM_STATUS, UVD_BUSY) ||
	    (RREG32_SOC15(UVD, ring->me, mmUVD_STATUS) &
		    AMDGPU_UVD_STATUS_BUSY_MASK))
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset,
				SRBM_SOFT_RESET, SOFT_RESET_UVD, 1);

	अगर (srbm_soft_reset) अणु
		adev->uvd.inst[ring->me].srbm_soft_reset = srbm_soft_reset;
		वापस true;
	पूर्ण अन्यथा अणु
		adev->uvd.inst[ring->me].srbm_soft_reset = 0;
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक uvd_v7_0_pre_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (!adev->uvd.inst[ring->me].srbm_soft_reset)
		वापस 0;

	uvd_v7_0_stop(adev);
	वापस 0;
पूर्ण

अटल पूर्णांक uvd_v7_0_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 srbm_soft_reset;

	अगर (!adev->uvd.inst[ring->me].srbm_soft_reset)
		वापस 0;
	srbm_soft_reset = adev->uvd.inst[ring->me].srbm_soft_reset;

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

अटल पूर्णांक uvd_v7_0_post_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (!adev->uvd.inst[ring->me].srbm_soft_reset)
		वापस 0;

	mdelay(5);

	वापस uvd_v7_0_start(adev);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक uvd_v7_0_set_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_irq_src *source,
					अचिन्हित type,
					क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	// TODO
	वापस 0;
पूर्ण

अटल पूर्णांक uvd_v7_0_process_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_irq_src *source,
				      काष्ठा amdgpu_iv_entry *entry)
अणु
	uपूर्णांक32_t ip_instance;

	चयन (entry->client_id) अणु
	हाल SOC15_IH_CLIENTID_UVD:
		ip_instance = 0;
		अवरोध;
	हाल SOC15_IH_CLIENTID_UVD1:
		ip_instance = 1;
		अवरोध;
	शेष:
		DRM_ERROR("Unhandled client id: %d\n", entry->client_id);
		वापस 0;
	पूर्ण

	DRM_DEBUG("IH: UVD TRAP\n");

	चयन (entry->src_id) अणु
	हाल 124:
		amdgpu_fence_process(&adev->uvd.inst[ip_instance].ring);
		अवरोध;
	हाल 119:
		amdgpu_fence_process(&adev->uvd.inst[ip_instance].ring_enc[0]);
		अवरोध;
	हाल 120:
		अगर (!amdgpu_sriov_vf(adev))
			amdgpu_fence_process(&adev->uvd.inst[ip_instance].ring_enc[1]);
		अवरोध;
	शेष:
		DRM_ERROR("Unhandled interrupt: %d %d\n",
			  entry->src_id, entry->src_data[0]);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#अगर 0
अटल व्योम uvd_v7_0_set_sw_घड़ी_gating(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t data, data1, data2, suvd_flags;

	data = RREG32_SOC15(UVD, ring->me, mmUVD_CGC_CTRL);
	data1 = RREG32_SOC15(UVD, ring->me, mmUVD_SUVD_CGC_GATE);
	data2 = RREG32_SOC15(UVD, ring->me, mmUVD_SUVD_CGC_CTRL);

	data &= ~(UVD_CGC_CTRL__CLK_OFF_DELAY_MASK |
		  UVD_CGC_CTRL__CLK_GATE_DLY_TIMER_MASK);

	suvd_flags = UVD_SUVD_CGC_GATE__SRE_MASK |
		     UVD_SUVD_CGC_GATE__SIT_MASK |
		     UVD_SUVD_CGC_GATE__SMP_MASK |
		     UVD_SUVD_CGC_GATE__SCM_MASK |
		     UVD_SUVD_CGC_GATE__SDB_MASK;

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
			UVD_CGC_CTRL__JPEG2_MODE_MASK |
			UVD_CGC_CTRL__SCPU_MODE_MASK);
	data2 &= ~(UVD_SUVD_CGC_CTRL__SRE_MODE_MASK |
			UVD_SUVD_CGC_CTRL__SIT_MODE_MASK |
			UVD_SUVD_CGC_CTRL__SMP_MODE_MASK |
			UVD_SUVD_CGC_CTRL__SCM_MODE_MASK |
			UVD_SUVD_CGC_CTRL__SDB_MODE_MASK);
	data1 |= suvd_flags;

	WREG32_SOC15(UVD, ring->me, mmUVD_CGC_CTRL, data);
	WREG32_SOC15(UVD, ring->me, mmUVD_CGC_GATE, 0);
	WREG32_SOC15(UVD, ring->me, mmUVD_SUVD_CGC_GATE, data1);
	WREG32_SOC15(UVD, ring->me, mmUVD_SUVD_CGC_CTRL, data2);
पूर्ण

अटल व्योम uvd_v7_0_set_hw_घड़ी_gating(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t data, data1, cgc_flags, suvd_flags;

	data = RREG32_SOC15(UVD, ring->me, mmUVD_CGC_GATE);
	data1 = RREG32_SOC15(UVD, ring->me, mmUVD_SUVD_CGC_GATE);

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

	WREG32_SOC15(UVD, ring->me, mmUVD_CGC_GATE, data);
	WREG32_SOC15(UVD, ring->me, mmUVD_SUVD_CGC_GATE, data1);
पूर्ण

अटल व्योम uvd_v7_0_set_bypass_mode(काष्ठा amdgpu_device *adev, bool enable)
अणु
	u32 पंचांगp = RREG32_SMC(ixGCK_DFS_BYPASS_CNTL);

	अगर (enable)
		पंचांगp |= (GCK_DFS_BYPASS_CNTL__BYPASSDCLK_MASK |
			GCK_DFS_BYPASS_CNTL__BYPASSVCLK_MASK);
	अन्यथा
		पंचांगp &= ~(GCK_DFS_BYPASS_CNTL__BYPASSDCLK_MASK |
			 GCK_DFS_BYPASS_CNTL__BYPASSVCLK_MASK);

	WREG32_SMC(ixGCK_DFS_BYPASS_CNTL, पंचांगp);
पूर्ण


अटल पूर्णांक uvd_v7_0_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	bool enable = (state == AMD_CG_STATE_GATE);

	uvd_v7_0_set_bypass_mode(adev, enable);

	अगर (!(adev->cg_flags & AMD_CG_SUPPORT_UVD_MGCG))
		वापस 0;

	अगर (enable) अणु
		/* disable HW gating and enable Sw gating */
		uvd_v7_0_set_sw_घड़ी_gating(adev);
	पूर्ण अन्यथा अणु
		/* रुको क्रम STATUS to clear */
		अगर (uvd_v7_0_रुको_क्रम_idle(handle))
			वापस -EBUSY;

		/* enable HW gates because UVD is idle */
		/* uvd_v7_0_set_hw_घड़ी_gating(adev); */
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uvd_v7_0_set_घातergating_state(व्योम *handle,
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

	अगर (!(adev->pg_flags & AMD_PG_SUPPORT_UVD))
		वापस 0;

	WREG32_SOC15(UVD, ring->me, mmUVD_POWER_STATUS, UVD_POWER_STATUS__UVD_PG_EN_MASK);

	अगर (state == AMD_PG_STATE_GATE) अणु
		uvd_v7_0_stop(adev);
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस uvd_v7_0_start(adev);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक uvd_v7_0_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	/* needed क्रम driver unload*/
	वापस 0;
पूर्ण

स्थिर काष्ठा amd_ip_funcs uvd_v7_0_ip_funcs = अणु
	.name = "uvd_v7_0",
	.early_init = uvd_v7_0_early_init,
	.late_init = शून्य,
	.sw_init = uvd_v7_0_sw_init,
	.sw_fini = uvd_v7_0_sw_fini,
	.hw_init = uvd_v7_0_hw_init,
	.hw_fini = uvd_v7_0_hw_fini,
	.suspend = uvd_v7_0_suspend,
	.resume = uvd_v7_0_resume,
	.is_idle = शून्य /* uvd_v7_0_is_idle */,
	.रुको_क्रम_idle = शून्य /* uvd_v7_0_रुको_क्रम_idle */,
	.check_soft_reset = शून्य /* uvd_v7_0_check_soft_reset */,
	.pre_soft_reset = शून्य /* uvd_v7_0_pre_soft_reset */,
	.soft_reset = शून्य /* uvd_v7_0_soft_reset */,
	.post_soft_reset = शून्य /* uvd_v7_0_post_soft_reset */,
	.set_घड़ीgating_state = uvd_v7_0_set_घड़ीgating_state,
	.set_घातergating_state = शून्य /* uvd_v7_0_set_घातergating_state */,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs uvd_v7_0_ring_vm_funcs = अणु
	.type = AMDGPU_RING_TYPE_UVD,
	.align_mask = 0xf,
	.support_64bit_ptrs = false,
	.no_user_fence = true,
	.vmhub = AMDGPU_MMHUB_0,
	.get_rptr = uvd_v7_0_ring_get_rptr,
	.get_wptr = uvd_v7_0_ring_get_wptr,
	.set_wptr = uvd_v7_0_ring_set_wptr,
	.patch_cs_in_place = uvd_v7_0_ring_patch_cs_in_place,
	.emit_frame_size =
		6 + /* hdp invalidate */
		SOC15_FLUSH_GPU_TLB_NUM_WREG * 6 +
		SOC15_FLUSH_GPU_TLB_NUM_REG_WAIT * 8 +
		8 + /* uvd_v7_0_ring_emit_vm_flush */
		14 + 14, /* uvd_v7_0_ring_emit_fence x2 vm fence */
	.emit_ib_size = 8, /* uvd_v7_0_ring_emit_ib */
	.emit_ib = uvd_v7_0_ring_emit_ib,
	.emit_fence = uvd_v7_0_ring_emit_fence,
	.emit_vm_flush = uvd_v7_0_ring_emit_vm_flush,
	.emit_hdp_flush = uvd_v7_0_ring_emit_hdp_flush,
	.test_ring = uvd_v7_0_ring_test_ring,
	.test_ib = amdgpu_uvd_ring_test_ib,
	.insert_nop = uvd_v7_0_ring_insert_nop,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.begin_use = amdgpu_uvd_ring_begin_use,
	.end_use = amdgpu_uvd_ring_end_use,
	.emit_wreg = uvd_v7_0_ring_emit_wreg,
	.emit_reg_रुको = uvd_v7_0_ring_emit_reg_रुको,
	.emit_reg_ग_लिखो_reg_रुको = amdgpu_ring_emit_reg_ग_लिखो_reg_रुको_helper,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs uvd_v7_0_enc_ring_vm_funcs = अणु
	.type = AMDGPU_RING_TYPE_UVD_ENC,
	.align_mask = 0x3f,
	.nop = HEVC_ENC_CMD_NO_OP,
	.support_64bit_ptrs = false,
	.no_user_fence = true,
	.vmhub = AMDGPU_MMHUB_0,
	.get_rptr = uvd_v7_0_enc_ring_get_rptr,
	.get_wptr = uvd_v7_0_enc_ring_get_wptr,
	.set_wptr = uvd_v7_0_enc_ring_set_wptr,
	.emit_frame_size =
		3 + 3 + /* hdp flush / invalidate */
		SOC15_FLUSH_GPU_TLB_NUM_WREG * 3 +
		SOC15_FLUSH_GPU_TLB_NUM_REG_WAIT * 4 +
		4 + /* uvd_v7_0_enc_ring_emit_vm_flush */
		5 + 5 + /* uvd_v7_0_enc_ring_emit_fence x2 vm fence */
		1, /* uvd_v7_0_enc_ring_insert_end */
	.emit_ib_size = 5, /* uvd_v7_0_enc_ring_emit_ib */
	.emit_ib = uvd_v7_0_enc_ring_emit_ib,
	.emit_fence = uvd_v7_0_enc_ring_emit_fence,
	.emit_vm_flush = uvd_v7_0_enc_ring_emit_vm_flush,
	.test_ring = uvd_v7_0_enc_ring_test_ring,
	.test_ib = uvd_v7_0_enc_ring_test_ib,
	.insert_nop = amdgpu_ring_insert_nop,
	.insert_end = uvd_v7_0_enc_ring_insert_end,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.begin_use = amdgpu_uvd_ring_begin_use,
	.end_use = amdgpu_uvd_ring_end_use,
	.emit_wreg = uvd_v7_0_enc_ring_emit_wreg,
	.emit_reg_रुको = uvd_v7_0_enc_ring_emit_reg_रुको,
	.emit_reg_ग_लिखो_reg_रुको = amdgpu_ring_emit_reg_ग_लिखो_reg_रुको_helper,
पूर्ण;

अटल व्योम uvd_v7_0_set_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->uvd.num_uvd_inst; i++) अणु
		अगर (adev->uvd.harvest_config & (1 << i))
			जारी;
		adev->uvd.inst[i].ring.funcs = &uvd_v7_0_ring_vm_funcs;
		adev->uvd.inst[i].ring.me = i;
		DRM_INFO("UVD(%d) is enabled in VM mode\n", i);
	पूर्ण
पूर्ण

अटल व्योम uvd_v7_0_set_enc_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, j;

	क्रम (j = 0; j < adev->uvd.num_uvd_inst; j++) अणु
		अगर (adev->uvd.harvest_config & (1 << j))
			जारी;
		क्रम (i = 0; i < adev->uvd.num_enc_rings; ++i) अणु
			adev->uvd.inst[j].ring_enc[i].funcs = &uvd_v7_0_enc_ring_vm_funcs;
			adev->uvd.inst[j].ring_enc[i].me = j;
		पूर्ण

		DRM_INFO("UVD(%d) ENC is enabled in VM mode\n", j);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs uvd_v7_0_irq_funcs = अणु
	.set = uvd_v7_0_set_पूर्णांकerrupt_state,
	.process = uvd_v7_0_process_पूर्णांकerrupt,
पूर्ण;

अटल व्योम uvd_v7_0_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->uvd.num_uvd_inst; i++) अणु
		अगर (adev->uvd.harvest_config & (1 << i))
			जारी;
		adev->uvd.inst[i].irq.num_types = adev->uvd.num_enc_rings + 1;
		adev->uvd.inst[i].irq.funcs = &uvd_v7_0_irq_funcs;
	पूर्ण
पूर्ण

स्थिर काष्ठा amdgpu_ip_block_version uvd_v7_0_ip_block =
अणु
		.type = AMD_IP_BLOCK_TYPE_UVD,
		.major = 7,
		.minor = 0,
		.rev = 0,
		.funcs = &uvd_v7_0_ip_funcs,
पूर्ण;
