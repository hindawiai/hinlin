<शैली गुरु>
/*
 * Copyright 2013 Advanced Micro Devices, Inc.
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
 * Authors: Christian Kथघnig <christian.koenig@amd.com>
 */

#समावेश <linux/firmware.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_vce.h"
#समावेश "cikd.h"
#समावेश "vce/vce_2_0_d.h"
#समावेश "vce/vce_2_0_sh_mask.h"
#समावेश "smu/smu_7_0_1_d.h"
#समावेश "smu/smu_7_0_1_sh_mask.h"
#समावेश "oss/oss_2_0_d.h"
#समावेश "oss/oss_2_0_sh_mask.h"

#घोषणा VCE_V2_0_FW_SIZE	(256 * 1024)
#घोषणा VCE_V2_0_STACK_SIZE	(64 * 1024)
#घोषणा VCE_V2_0_DATA_SIZE	(23552 * AMDGPU_MAX_VCE_HANDLES)
#घोषणा VCE_STATUS_VCPU_REPORT_FW_LOADED_MASK	0x02

अटल व्योम vce_v2_0_set_ring_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम vce_v2_0_set_irq_funcs(काष्ठा amdgpu_device *adev);

/**
 * vce_v2_0_ring_get_rptr - get पढ़ो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware पढ़ो poपूर्णांकer
 */
अटल uपूर्णांक64_t vce_v2_0_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring->me == 0)
		वापस RREG32(mmVCE_RB_RPTR);
	अन्यथा
		वापस RREG32(mmVCE_RB_RPTR2);
पूर्ण

/**
 * vce_v2_0_ring_get_wptr - get ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware ग_लिखो poपूर्णांकer
 */
अटल uपूर्णांक64_t vce_v2_0_ring_get_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring->me == 0)
		वापस RREG32(mmVCE_RB_WPTR);
	अन्यथा
		वापस RREG32(mmVCE_RB_WPTR2);
पूर्ण

/**
 * vce_v2_0_ring_set_wptr - set ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Commits the ग_लिखो poपूर्णांकer to the hardware
 */
अटल व्योम vce_v2_0_ring_set_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	अगर (ring->me == 0)
		WREG32(mmVCE_RB_WPTR, lower_32_bits(ring->wptr));
	अन्यथा
		WREG32(mmVCE_RB_WPTR2, lower_32_bits(ring->wptr));
पूर्ण

अटल पूर्णांक vce_v2_0_lmi_clean(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < 10; ++i) अणु
		क्रम (j = 0; j < 100; ++j) अणु
			uपूर्णांक32_t status = RREG32(mmVCE_LMI_STATUS);

			अगर (status & 0x337f)
				वापस 0;
			mdelay(10);
		पूर्ण
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक vce_v2_0_firmware_loaded(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < 10; ++i) अणु
		क्रम (j = 0; j < 100; ++j) अणु
			uपूर्णांक32_t status = RREG32(mmVCE_STATUS);

			अगर (status & VCE_STATUS_VCPU_REPORT_FW_LOADED_MASK)
				वापस 0;
			mdelay(10);
		पूर्ण

		DRM_ERROR("VCE not responding, trying to reset the ECPU!!!\n");
		WREG32_P(mmVCE_SOFT_RESET,
			VCE_SOFT_RESET__ECPU_SOFT_RESET_MASK,
			~VCE_SOFT_RESET__ECPU_SOFT_RESET_MASK);
		mdelay(10);
		WREG32_P(mmVCE_SOFT_RESET, 0,
			~VCE_SOFT_RESET__ECPU_SOFT_RESET_MASK);
		mdelay(10);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम vce_v2_0_disable_cg(काष्ठा amdgpu_device *adev)
अणु
	WREG32(mmVCE_CGTT_CLK_OVERRIDE, 7);
पूर्ण

अटल व्योम vce_v2_0_init_cg(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32(mmVCE_CLOCK_GATING_A);
	पंचांगp &= ~0xfff;
	पंचांगp |= ((0 << 0) | (4 << 4));
	पंचांगp |= 0x40000;
	WREG32(mmVCE_CLOCK_GATING_A, पंचांगp);

	पंचांगp = RREG32(mmVCE_UENC_CLOCK_GATING);
	पंचांगp &= ~0xfff;
	पंचांगp |= ((0 << 0) | (4 << 4));
	WREG32(mmVCE_UENC_CLOCK_GATING, पंचांगp);

	पंचांगp = RREG32(mmVCE_CLOCK_GATING_B);
	पंचांगp |= 0x10;
	पंचांगp &= ~0x100000;
	WREG32(mmVCE_CLOCK_GATING_B, पंचांगp);
पूर्ण

अटल व्योम vce_v2_0_mc_resume(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t size, offset;

	WREG32_P(mmVCE_CLOCK_GATING_A, 0, ~(1 << 16));
	WREG32_P(mmVCE_UENC_CLOCK_GATING, 0x1FF000, ~0xFF9FF000);
	WREG32_P(mmVCE_UENC_REG_CLOCK_GATING, 0x3F, ~0x3F);
	WREG32(mmVCE_CLOCK_GATING_B, 0xf7);

	WREG32(mmVCE_LMI_CTRL, 0x00398000);
	WREG32_P(mmVCE_LMI_CACHE_CTRL, 0x0, ~0x1);
	WREG32(mmVCE_LMI_SWAP_CNTL, 0);
	WREG32(mmVCE_LMI_SWAP_CNTL1, 0);
	WREG32(mmVCE_LMI_VM_CTRL, 0);

	WREG32(mmVCE_LMI_VCPU_CACHE_40BIT_BAR, (adev->vce.gpu_addr >> 8));

	offset = AMDGPU_VCE_FIRMWARE_OFFSET;
	size = VCE_V2_0_FW_SIZE;
	WREG32(mmVCE_VCPU_CACHE_OFFSET0, offset & 0x7fffffff);
	WREG32(mmVCE_VCPU_CACHE_SIZE0, size);

	offset += size;
	size = VCE_V2_0_STACK_SIZE;
	WREG32(mmVCE_VCPU_CACHE_OFFSET1, offset & 0x7fffffff);
	WREG32(mmVCE_VCPU_CACHE_SIZE1, size);

	offset += size;
	size = VCE_V2_0_DATA_SIZE;
	WREG32(mmVCE_VCPU_CACHE_OFFSET2, offset & 0x7fffffff);
	WREG32(mmVCE_VCPU_CACHE_SIZE2, size);

	WREG32_P(mmVCE_LMI_CTRL2, 0x0, ~0x100);
	WREG32_FIELD(VCE_SYS_INT_EN, VCE_SYS_INT_TRAP_INTERRUPT_EN, 1);
पूर्ण

अटल bool vce_v2_0_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	वापस !(RREG32(mmSRBM_STATUS2) & SRBM_STATUS2__VCE_BUSY_MASK);
पूर्ण

अटल पूर्णांक vce_v2_0_रुको_क्रम_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	अचिन्हित i;

	क्रम (i = 0; i < adev->usec_समयout; i++) अणु
		अगर (vce_v2_0_is_idle(handle))
			वापस 0;
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

/**
 * vce_v2_0_start - start VCE block
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Setup and start the VCE block
 */
अटल पूर्णांक vce_v2_0_start(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring;
	पूर्णांक r;

	/* set BUSY flag */
	WREG32_P(mmVCE_STATUS, 1, ~1);

	vce_v2_0_init_cg(adev);
	vce_v2_0_disable_cg(adev);

	vce_v2_0_mc_resume(adev);

	ring = &adev->vce.ring[0];
	WREG32(mmVCE_RB_RPTR, lower_32_bits(ring->wptr));
	WREG32(mmVCE_RB_WPTR, lower_32_bits(ring->wptr));
	WREG32(mmVCE_RB_BASE_LO, ring->gpu_addr);
	WREG32(mmVCE_RB_BASE_HI, upper_32_bits(ring->gpu_addr));
	WREG32(mmVCE_RB_SIZE, ring->ring_size / 4);

	ring = &adev->vce.ring[1];
	WREG32(mmVCE_RB_RPTR2, lower_32_bits(ring->wptr));
	WREG32(mmVCE_RB_WPTR2, lower_32_bits(ring->wptr));
	WREG32(mmVCE_RB_BASE_LO2, ring->gpu_addr);
	WREG32(mmVCE_RB_BASE_HI2, upper_32_bits(ring->gpu_addr));
	WREG32(mmVCE_RB_SIZE2, ring->ring_size / 4);

	WREG32_FIELD(VCE_VCPU_CNTL, CLK_EN, 1);
	WREG32_FIELD(VCE_SOFT_RESET, ECPU_SOFT_RESET, 1);
	mdelay(100);
	WREG32_FIELD(VCE_SOFT_RESET, ECPU_SOFT_RESET, 0);

	r = vce_v2_0_firmware_loaded(adev);

	/* clear BUSY flag */
	WREG32_P(mmVCE_STATUS, 0, ~1);

	अगर (r) अणु
		DRM_ERROR("VCE not responding, giving up!!!\n");
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vce_v2_0_stop(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;
	पूर्णांक status;

	अगर (vce_v2_0_lmi_clean(adev)) अणु
		DRM_INFO("vce is not idle \n");
		वापस 0;
	पूर्ण

	अगर (vce_v2_0_रुको_क्रम_idle(adev)) अणु
		DRM_INFO("VCE is busy, Can't set clock gating");
		वापस 0;
	पूर्ण

	/* Stall UMC and रेजिस्टर bus beक्रमe resetting VCPU */
	WREG32_P(mmVCE_LMI_CTRL2, 1 << 8, ~(1 << 8));

	क्रम (i = 0; i < 100; ++i) अणु
		status = RREG32(mmVCE_LMI_STATUS);
		अगर (status & 0x240)
			अवरोध;
		mdelay(1);
	पूर्ण

	WREG32_P(mmVCE_VCPU_CNTL, 0, ~0x80001);

	/* put LMI, VCPU, RBC etc... पूर्णांकo reset */
	WREG32_P(mmVCE_SOFT_RESET, 1, ~0x1);

	WREG32(mmVCE_STATUS, 0);

	वापस 0;
पूर्ण

अटल व्योम vce_v2_0_set_sw_cg(काष्ठा amdgpu_device *adev, bool gated)
अणु
	u32 पंचांगp;

	अगर (gated) अणु
		पंचांगp = RREG32(mmVCE_CLOCK_GATING_B);
		पंचांगp |= 0xe70000;
		WREG32(mmVCE_CLOCK_GATING_B, पंचांगp);

		पंचांगp = RREG32(mmVCE_UENC_CLOCK_GATING);
		पंचांगp |= 0xff000000;
		WREG32(mmVCE_UENC_CLOCK_GATING, पंचांगp);

		पंचांगp = RREG32(mmVCE_UENC_REG_CLOCK_GATING);
		पंचांगp &= ~0x3fc;
		WREG32(mmVCE_UENC_REG_CLOCK_GATING, पंचांगp);

		WREG32(mmVCE_CGTT_CLK_OVERRIDE, 0);
	पूर्ण अन्यथा अणु
		पंचांगp = RREG32(mmVCE_CLOCK_GATING_B);
		पंचांगp |= 0xe7;
		पंचांगp &= ~0xe70000;
		WREG32(mmVCE_CLOCK_GATING_B, पंचांगp);

		पंचांगp = RREG32(mmVCE_UENC_CLOCK_GATING);
		पंचांगp |= 0x1fe000;
		पंचांगp &= ~0xff000000;
		WREG32(mmVCE_UENC_CLOCK_GATING, पंचांगp);

		पंचांगp = RREG32(mmVCE_UENC_REG_CLOCK_GATING);
		पंचांगp |= 0x3fc;
		WREG32(mmVCE_UENC_REG_CLOCK_GATING, पंचांगp);
	पूर्ण
पूर्ण

अटल व्योम vce_v2_0_set_dyn_cg(काष्ठा amdgpu_device *adev, bool gated)
अणु
	u32 orig, पंचांगp;

/* LMI_MC/LMI_UMC always set in dynamic,
 * set अणुCGC_*_GATE_MODE, CGC_*_SW_GATEपूर्ण = अणु0, 0पूर्ण
 */
	पंचांगp = RREG32(mmVCE_CLOCK_GATING_B);
	पंचांगp &= ~0x00060006;

/* Exception क्रम ECPU, IH, SEM, SYS blocks needs to be turned on/off by SW */
	अगर (gated) अणु
		पंचांगp |= 0xe10000;
		WREG32(mmVCE_CLOCK_GATING_B, पंचांगp);
	पूर्ण अन्यथा अणु
		पंचांगp |= 0xe1;
		पंचांगp &= ~0xe10000;
		WREG32(mmVCE_CLOCK_GATING_B, पंचांगp);
	पूर्ण

	orig = पंचांगp = RREG32(mmVCE_UENC_CLOCK_GATING);
	पंचांगp &= ~0x1fe000;
	पंचांगp &= ~0xff000000;
	अगर (पंचांगp != orig)
		WREG32(mmVCE_UENC_CLOCK_GATING, पंचांगp);

	orig = पंचांगp = RREG32(mmVCE_UENC_REG_CLOCK_GATING);
	पंचांगp &= ~0x3fc;
	अगर (पंचांगp != orig)
		WREG32(mmVCE_UENC_REG_CLOCK_GATING, पंचांगp);

	/* set VCE_UENC_REG_CLOCK_GATING always in dynamic mode */
	WREG32(mmVCE_UENC_REG_CLOCK_GATING, 0x00);

	अगर(gated)
		WREG32(mmVCE_CGTT_CLK_OVERRIDE, 0);
पूर्ण

अटल व्योम vce_v2_0_enable_mgcg(काष्ठा amdgpu_device *adev, bool enable,
								bool sw_cg)
अणु
	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_VCE_MGCG)) अणु
		अगर (sw_cg)
			vce_v2_0_set_sw_cg(adev, true);
		अन्यथा
			vce_v2_0_set_dyn_cg(adev, true);
	पूर्ण अन्यथा अणु
		vce_v2_0_disable_cg(adev);

		अगर (sw_cg)
			vce_v2_0_set_sw_cg(adev, false);
		अन्यथा
			vce_v2_0_set_dyn_cg(adev, false);
	पूर्ण
पूर्ण

अटल पूर्णांक vce_v2_0_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->vce.num_rings = 2;

	vce_v2_0_set_ring_funcs(adev);
	vce_v2_0_set_irq_funcs(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक vce_v2_0_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_ring *ring;
	पूर्णांक r, i;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	/* VCE */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, 167, &adev->vce.irq);
	अगर (r)
		वापस r;

	r = amdgpu_vce_sw_init(adev, VCE_V2_0_FW_SIZE +
		VCE_V2_0_STACK_SIZE + VCE_V2_0_DATA_SIZE);
	अगर (r)
		वापस r;

	r = amdgpu_vce_resume(adev);
	अगर (r)
		वापस r;

	क्रम (i = 0; i < adev->vce.num_rings; i++) अणु
		ring = &adev->vce.ring[i];
		प्र_लिखो(ring->name, "vce%d", i);
		r = amdgpu_ring_init(adev, ring, 512, &adev->vce.irq, 0,
				     AMDGPU_RING_PRIO_DEFAULT, शून्य);
		अगर (r)
			वापस r;
	पूर्ण

	r = amdgpu_vce_entity_init(adev);

	वापस r;
पूर्ण

अटल पूर्णांक vce_v2_0_sw_fini(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = amdgpu_vce_suspend(adev);
	अगर (r)
		वापस r;

	वापस amdgpu_vce_sw_fini(adev);
पूर्ण

अटल पूर्णांक vce_v2_0_hw_init(व्योम *handle)
अणु
	पूर्णांक r, i;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	amdgpu_asic_set_vce_घड़ीs(adev, 10000, 10000);
	vce_v2_0_enable_mgcg(adev, true, false);

	क्रम (i = 0; i < adev->vce.num_rings; i++) अणु
		r = amdgpu_ring_test_helper(&adev->vce.ring[i]);
		अगर (r)
			वापस r;
	पूर्ण

	DRM_INFO("VCE initialized successfully.\n");

	वापस 0;
पूर्ण

अटल पूर्णांक vce_v2_0_hw_fini(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक vce_v2_0_suspend(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = vce_v2_0_hw_fini(adev);
	अगर (r)
		वापस r;

	वापस amdgpu_vce_suspend(adev);
पूर्ण

अटल पूर्णांक vce_v2_0_resume(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = amdgpu_vce_resume(adev);
	अगर (r)
		वापस r;

	वापस vce_v2_0_hw_init(adev);
पूर्ण

अटल पूर्णांक vce_v2_0_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	WREG32_FIELD(SRBM_SOFT_RESET, SOFT_RESET_VCE, 1);
	mdelay(5);

	वापस vce_v2_0_start(adev);
पूर्ण

अटल पूर्णांक vce_v2_0_set_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
					काष्ठा amdgpu_irq_src *source,
					अचिन्हित type,
					क्रमागत amdgpu_पूर्णांकerrupt_state state)
अणु
	uपूर्णांक32_t val = 0;

	अगर (state == AMDGPU_IRQ_STATE_ENABLE)
		val |= VCE_SYS_INT_EN__VCE_SYS_INT_TRAP_INTERRUPT_EN_MASK;

	WREG32_P(mmVCE_SYS_INT_EN, val, ~VCE_SYS_INT_EN__VCE_SYS_INT_TRAP_INTERRUPT_EN_MASK);
	वापस 0;
पूर्ण

अटल पूर्णांक vce_v2_0_process_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_irq_src *source,
				      काष्ठा amdgpu_iv_entry *entry)
अणु
	DRM_DEBUG("IH: VCE\n");
	चयन (entry->src_data[0]) अणु
	हाल 0:
	हाल 1:
		amdgpu_fence_process(&adev->vce.ring[entry->src_data[0]]);
		अवरोध;
	शेष:
		DRM_ERROR("Unhandled interrupt: %d %d\n",
			  entry->src_id, entry->src_data[0]);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vce_v2_0_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	bool gate = false;
	bool sw_cg = false;

	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (state == AMD_CG_STATE_GATE) अणु
		gate = true;
		sw_cg = true;
	पूर्ण

	vce_v2_0_enable_mgcg(adev, gate, sw_cg);

	वापस 0;
पूर्ण

अटल पूर्णांक vce_v2_0_set_घातergating_state(व्योम *handle,
					  क्रमागत amd_घातergating_state state)
अणु
	/* This करोesn't actually घातergate the VCE block.
	 * That's करोne in the dpm code via the SMC.  This
	 * just re-inits the block as necessary.  The actual
	 * gating still happens in the dpm code.  We should
	 * revisit this when there is a cleaner line between
	 * the smc and the hw blocks
	 */
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (state == AMD_PG_STATE_GATE)
		वापस vce_v2_0_stop(adev);
	अन्यथा
		वापस vce_v2_0_start(adev);
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs vce_v2_0_ip_funcs = अणु
	.name = "vce_v2_0",
	.early_init = vce_v2_0_early_init,
	.late_init = शून्य,
	.sw_init = vce_v2_0_sw_init,
	.sw_fini = vce_v2_0_sw_fini,
	.hw_init = vce_v2_0_hw_init,
	.hw_fini = vce_v2_0_hw_fini,
	.suspend = vce_v2_0_suspend,
	.resume = vce_v2_0_resume,
	.is_idle = vce_v2_0_is_idle,
	.रुको_क्रम_idle = vce_v2_0_रुको_क्रम_idle,
	.soft_reset = vce_v2_0_soft_reset,
	.set_घड़ीgating_state = vce_v2_0_set_घड़ीgating_state,
	.set_घातergating_state = vce_v2_0_set_घातergating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs vce_v2_0_ring_funcs = अणु
	.type = AMDGPU_RING_TYPE_VCE,
	.align_mask = 0xf,
	.nop = VCE_CMD_NO_OP,
	.support_64bit_ptrs = false,
	.no_user_fence = true,
	.get_rptr = vce_v2_0_ring_get_rptr,
	.get_wptr = vce_v2_0_ring_get_wptr,
	.set_wptr = vce_v2_0_ring_set_wptr,
	.parse_cs = amdgpu_vce_ring_parse_cs,
	.emit_frame_size = 6, /* amdgpu_vce_ring_emit_fence  x1 no user fence */
	.emit_ib_size = 4, /* amdgpu_vce_ring_emit_ib */
	.emit_ib = amdgpu_vce_ring_emit_ib,
	.emit_fence = amdgpu_vce_ring_emit_fence,
	.test_ring = amdgpu_vce_ring_test_ring,
	.test_ib = amdgpu_vce_ring_test_ib,
	.insert_nop = amdgpu_ring_insert_nop,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.begin_use = amdgpu_vce_ring_begin_use,
	.end_use = amdgpu_vce_ring_end_use,
पूर्ण;

अटल व्योम vce_v2_0_set_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adev->vce.num_rings; i++) अणु
		adev->vce.ring[i].funcs = &vce_v2_0_ring_funcs;
		adev->vce.ring[i].me = i;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs vce_v2_0_irq_funcs = अणु
	.set = vce_v2_0_set_पूर्णांकerrupt_state,
	.process = vce_v2_0_process_पूर्णांकerrupt,
पूर्ण;

अटल व्योम vce_v2_0_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->vce.irq.num_types = 1;
	adev->vce.irq.funcs = &vce_v2_0_irq_funcs;
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version vce_v2_0_ip_block =
अणु
		.type = AMD_IP_BLOCK_TYPE_VCE,
		.major = 2,
		.minor = 0,
		.rev = 0,
		.funcs = &vce_v2_0_ip_funcs,
पूर्ण;
