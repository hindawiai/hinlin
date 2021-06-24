<शैली गुरु>
/*
 * Copyright 2014 Advanced Micro Devices, Inc.
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
#समावेश "vid.h"
#समावेश "vce/vce_3_0_d.h"
#समावेश "vce/vce_3_0_sh_mask.h"
#समावेश "oss/oss_3_0_d.h"
#समावेश "oss/oss_3_0_sh_mask.h"
#समावेश "gca/gfx_8_0_d.h"
#समावेश "smu/smu_7_1_2_d.h"
#समावेश "smu/smu_7_1_2_sh_mask.h"
#समावेश "gca/gfx_8_0_sh_mask.h"
#समावेश "ivsrcid/ivsrcid_vislands30.h"


#घोषणा GRBM_GFX_INDEX__VCE_INSTANCE__SHIFT	0x04
#घोषणा GRBM_GFX_INDEX__VCE_INSTANCE_MASK	0x10
#घोषणा GRBM_GFX_INDEX__VCE_ALL_PIPE		0x07

#घोषणा mmVCE_LMI_VCPU_CACHE_40BIT_BAR0	0x8616
#घोषणा mmVCE_LMI_VCPU_CACHE_40BIT_BAR1	0x8617
#घोषणा mmVCE_LMI_VCPU_CACHE_40BIT_BAR2	0x8618
#घोषणा mmGRBM_GFX_INDEX_DEFAULT 0xE0000000

#घोषणा VCE_STATUS_VCPU_REPORT_FW_LOADED_MASK	0x02

#घोषणा VCE_V3_0_FW_SIZE	(384 * 1024)
#घोषणा VCE_V3_0_STACK_SIZE	(64 * 1024)
#घोषणा VCE_V3_0_DATA_SIZE	((16 * 1024 * AMDGPU_MAX_VCE_HANDLES) + (52 * 1024))

#घोषणा FW_52_8_3	((52 << 24) | (8 << 16) | (3 << 8))

#घोषणा GET_VCE_INSTANCE(i)  ((i) << GRBM_GFX_INDEX__VCE_INSTANCE__SHIFT \
					| GRBM_GFX_INDEX__VCE_ALL_PIPE)

अटल व्योम vce_v3_0_mc_resume(काष्ठा amdgpu_device *adev, पूर्णांक idx);
अटल व्योम vce_v3_0_set_ring_funcs(काष्ठा amdgpu_device *adev);
अटल व्योम vce_v3_0_set_irq_funcs(काष्ठा amdgpu_device *adev);
अटल पूर्णांक vce_v3_0_रुको_क्रम_idle(व्योम *handle);
अटल पूर्णांक vce_v3_0_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state);
/**
 * vce_v3_0_ring_get_rptr - get पढ़ो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware पढ़ो poपूर्णांकer
 */
अटल uपूर्णांक64_t vce_v3_0_ring_get_rptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	u32 v;

	mutex_lock(&adev->grbm_idx_mutex);
	अगर (adev->vce.harvest_config == 0 ||
		adev->vce.harvest_config == AMDGPU_VCE_HARVEST_VCE1)
		WREG32(mmGRBM_GFX_INDEX, GET_VCE_INSTANCE(0));
	अन्यथा अगर (adev->vce.harvest_config == AMDGPU_VCE_HARVEST_VCE0)
		WREG32(mmGRBM_GFX_INDEX, GET_VCE_INSTANCE(1));

	अगर (ring->me == 0)
		v = RREG32(mmVCE_RB_RPTR);
	अन्यथा अगर (ring->me == 1)
		v = RREG32(mmVCE_RB_RPTR2);
	अन्यथा
		v = RREG32(mmVCE_RB_RPTR3);

	WREG32(mmGRBM_GFX_INDEX, mmGRBM_GFX_INDEX_DEFAULT);
	mutex_unlock(&adev->grbm_idx_mutex);

	वापस v;
पूर्ण

/**
 * vce_v3_0_ring_get_wptr - get ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Returns the current hardware ग_लिखो poपूर्णांकer
 */
अटल uपूर्णांक64_t vce_v3_0_ring_get_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;
	u32 v;

	mutex_lock(&adev->grbm_idx_mutex);
	अगर (adev->vce.harvest_config == 0 ||
		adev->vce.harvest_config == AMDGPU_VCE_HARVEST_VCE1)
		WREG32(mmGRBM_GFX_INDEX, GET_VCE_INSTANCE(0));
	अन्यथा अगर (adev->vce.harvest_config == AMDGPU_VCE_HARVEST_VCE0)
		WREG32(mmGRBM_GFX_INDEX, GET_VCE_INSTANCE(1));

	अगर (ring->me == 0)
		v = RREG32(mmVCE_RB_WPTR);
	अन्यथा अगर (ring->me == 1)
		v = RREG32(mmVCE_RB_WPTR2);
	अन्यथा
		v = RREG32(mmVCE_RB_WPTR3);

	WREG32(mmGRBM_GFX_INDEX, mmGRBM_GFX_INDEX_DEFAULT);
	mutex_unlock(&adev->grbm_idx_mutex);

	वापस v;
पूर्ण

/**
 * vce_v3_0_ring_set_wptr - set ग_लिखो poपूर्णांकer
 *
 * @ring: amdgpu_ring poपूर्णांकer
 *
 * Commits the ग_लिखो poपूर्णांकer to the hardware
 */
अटल व्योम vce_v3_0_ring_set_wptr(काष्ठा amdgpu_ring *ring)
अणु
	काष्ठा amdgpu_device *adev = ring->adev;

	mutex_lock(&adev->grbm_idx_mutex);
	अगर (adev->vce.harvest_config == 0 ||
		adev->vce.harvest_config == AMDGPU_VCE_HARVEST_VCE1)
		WREG32(mmGRBM_GFX_INDEX, GET_VCE_INSTANCE(0));
	अन्यथा अगर (adev->vce.harvest_config == AMDGPU_VCE_HARVEST_VCE0)
		WREG32(mmGRBM_GFX_INDEX, GET_VCE_INSTANCE(1));

	अगर (ring->me == 0)
		WREG32(mmVCE_RB_WPTR, lower_32_bits(ring->wptr));
	अन्यथा अगर (ring->me == 1)
		WREG32(mmVCE_RB_WPTR2, lower_32_bits(ring->wptr));
	अन्यथा
		WREG32(mmVCE_RB_WPTR3, lower_32_bits(ring->wptr));

	WREG32(mmGRBM_GFX_INDEX, mmGRBM_GFX_INDEX_DEFAULT);
	mutex_unlock(&adev->grbm_idx_mutex);
पूर्ण

अटल व्योम vce_v3_0_override_vce_घड़ी_gating(काष्ठा amdgpu_device *adev, bool override)
अणु
	WREG32_FIELD(VCE_RB_ARB_CTRL, VCE_CGTT_OVERRIDE, override ? 1 : 0);
पूर्ण

अटल व्योम vce_v3_0_set_vce_sw_घड़ी_gating(काष्ठा amdgpu_device *adev,
					     bool gated)
अणु
	u32 data;

	/* Set Override to disable Clock Gating */
	vce_v3_0_override_vce_घड़ी_gating(adev, true);

	/* This function enables MGCG which is controlled by firmware.
	   With the घड़ीs in the gated state the core is still
	   accessible but the firmware will throttle the घड़ीs on the
	   fly as necessary.
	*/
	अगर (!gated) अणु
		data = RREG32(mmVCE_CLOCK_GATING_B);
		data |= 0x1ff;
		data &= ~0xef0000;
		WREG32(mmVCE_CLOCK_GATING_B, data);

		data = RREG32(mmVCE_UENC_CLOCK_GATING);
		data |= 0x3ff000;
		data &= ~0xffc00000;
		WREG32(mmVCE_UENC_CLOCK_GATING, data);

		data = RREG32(mmVCE_UENC_CLOCK_GATING_2);
		data |= 0x2;
		data &= ~0x00010000;
		WREG32(mmVCE_UENC_CLOCK_GATING_2, data);

		data = RREG32(mmVCE_UENC_REG_CLOCK_GATING);
		data |= 0x37f;
		WREG32(mmVCE_UENC_REG_CLOCK_GATING, data);

		data = RREG32(mmVCE_UENC_DMA_DCLK_CTRL);
		data |= VCE_UENC_DMA_DCLK_CTRL__WRDMCLK_FORCEON_MASK |
			VCE_UENC_DMA_DCLK_CTRL__RDDMCLK_FORCEON_MASK |
			VCE_UENC_DMA_DCLK_CTRL__REGCLK_FORCEON_MASK  |
			0x8;
		WREG32(mmVCE_UENC_DMA_DCLK_CTRL, data);
	पूर्ण अन्यथा अणु
		data = RREG32(mmVCE_CLOCK_GATING_B);
		data &= ~0x80010;
		data |= 0xe70008;
		WREG32(mmVCE_CLOCK_GATING_B, data);

		data = RREG32(mmVCE_UENC_CLOCK_GATING);
		data |= 0xffc00000;
		WREG32(mmVCE_UENC_CLOCK_GATING, data);

		data = RREG32(mmVCE_UENC_CLOCK_GATING_2);
		data |= 0x10000;
		WREG32(mmVCE_UENC_CLOCK_GATING_2, data);

		data = RREG32(mmVCE_UENC_REG_CLOCK_GATING);
		data &= ~0x3ff;
		WREG32(mmVCE_UENC_REG_CLOCK_GATING, data);

		data = RREG32(mmVCE_UENC_DMA_DCLK_CTRL);
		data &= ~(VCE_UENC_DMA_DCLK_CTRL__WRDMCLK_FORCEON_MASK |
			  VCE_UENC_DMA_DCLK_CTRL__RDDMCLK_FORCEON_MASK |
			  VCE_UENC_DMA_DCLK_CTRL__REGCLK_FORCEON_MASK  |
			  0x8);
		WREG32(mmVCE_UENC_DMA_DCLK_CTRL, data);
	पूर्ण
	vce_v3_0_override_vce_घड़ी_gating(adev, false);
पूर्ण

अटल पूर्णांक vce_v3_0_firmware_loaded(काष्ठा amdgpu_device *adev)
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
		WREG32_FIELD(VCE_SOFT_RESET, ECPU_SOFT_RESET, 1);
		mdelay(10);
		WREG32_FIELD(VCE_SOFT_RESET, ECPU_SOFT_RESET, 0);
		mdelay(10);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

/**
 * vce_v3_0_start - start VCE block
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Setup and start the VCE block
 */
अटल पूर्णांक vce_v3_0_start(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_ring *ring;
	पूर्णांक idx, r;

	mutex_lock(&adev->grbm_idx_mutex);
	क्रम (idx = 0; idx < 2; ++idx) अणु
		अगर (adev->vce.harvest_config & (1 << idx))
			जारी;

		WREG32(mmGRBM_GFX_INDEX, GET_VCE_INSTANCE(idx));

		/* Program instance 0 reg space क्रम two instances or instance 0 हाल
		program instance 1 reg space क्रम only instance 1 available हाल */
		अगर (idx != 1 || adev->vce.harvest_config == AMDGPU_VCE_HARVEST_VCE0) अणु
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

			ring = &adev->vce.ring[2];
			WREG32(mmVCE_RB_RPTR3, lower_32_bits(ring->wptr));
			WREG32(mmVCE_RB_WPTR3, lower_32_bits(ring->wptr));
			WREG32(mmVCE_RB_BASE_LO3, ring->gpu_addr);
			WREG32(mmVCE_RB_BASE_HI3, upper_32_bits(ring->gpu_addr));
			WREG32(mmVCE_RB_SIZE3, ring->ring_size / 4);
		पूर्ण

		vce_v3_0_mc_resume(adev, idx);
		WREG32_FIELD(VCE_STATUS, JOB_BUSY, 1);

		अगर (adev->asic_type >= CHIP_STONEY)
			WREG32_P(mmVCE_VCPU_CNTL, 1, ~0x200001);
		अन्यथा
			WREG32_FIELD(VCE_VCPU_CNTL, CLK_EN, 1);

		WREG32_FIELD(VCE_SOFT_RESET, ECPU_SOFT_RESET, 0);
		mdelay(100);

		r = vce_v3_0_firmware_loaded(adev);

		/* clear BUSY flag */
		WREG32_FIELD(VCE_STATUS, JOB_BUSY, 0);

		अगर (r) अणु
			DRM_ERROR("VCE not responding, giving up!!!\n");
			mutex_unlock(&adev->grbm_idx_mutex);
			वापस r;
		पूर्ण
	पूर्ण

	WREG32(mmGRBM_GFX_INDEX, mmGRBM_GFX_INDEX_DEFAULT);
	mutex_unlock(&adev->grbm_idx_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक vce_v3_0_stop(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक idx;

	mutex_lock(&adev->grbm_idx_mutex);
	क्रम (idx = 0; idx < 2; ++idx) अणु
		अगर (adev->vce.harvest_config & (1 << idx))
			जारी;

		WREG32(mmGRBM_GFX_INDEX, GET_VCE_INSTANCE(idx));

		अगर (adev->asic_type >= CHIP_STONEY)
			WREG32_P(mmVCE_VCPU_CNTL, 0, ~0x200001);
		अन्यथा
			WREG32_FIELD(VCE_VCPU_CNTL, CLK_EN, 0);

		/* hold on ECPU */
		WREG32_FIELD(VCE_SOFT_RESET, ECPU_SOFT_RESET, 1);

		/* clear VCE STATUS */
		WREG32(mmVCE_STATUS, 0);
	पूर्ण

	WREG32(mmGRBM_GFX_INDEX, mmGRBM_GFX_INDEX_DEFAULT);
	mutex_unlock(&adev->grbm_idx_mutex);

	वापस 0;
पूर्ण

#घोषणा ixVCE_HARVEST_FUSE_MACRO__ADDRESS     0xC0014074
#घोषणा VCE_HARVEST_FUSE_MACRO__SHIFT       27
#घोषणा VCE_HARVEST_FUSE_MACRO__MASK        0x18000000

अटल अचिन्हित vce_v3_0_get_harvest_config(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp;

	अगर ((adev->asic_type == CHIP_FIJI) ||
	    (adev->asic_type == CHIP_STONEY))
		वापस AMDGPU_VCE_HARVEST_VCE1;

	अगर (adev->flags & AMD_IS_APU)
		पंचांगp = (RREG32_SMC(ixVCE_HARVEST_FUSE_MACRO__ADDRESS) &
		       VCE_HARVEST_FUSE_MACRO__MASK) >>
			VCE_HARVEST_FUSE_MACRO__SHIFT;
	अन्यथा
		पंचांगp = (RREG32_SMC(ixCC_HARVEST_FUSES) &
		       CC_HARVEST_FUSES__VCE_DISABLE_MASK) >>
			CC_HARVEST_FUSES__VCE_DISABLE__SHIFT;

	चयन (पंचांगp) अणु
	हाल 1:
		वापस AMDGPU_VCE_HARVEST_VCE0;
	हाल 2:
		वापस AMDGPU_VCE_HARVEST_VCE1;
	हाल 3:
		वापस AMDGPU_VCE_HARVEST_VCE0 | AMDGPU_VCE_HARVEST_VCE1;
	शेष:
		अगर ((adev->asic_type == CHIP_POLARIS10) ||
		    (adev->asic_type == CHIP_POLARIS11) ||
		    (adev->asic_type == CHIP_POLARIS12) ||
		    (adev->asic_type == CHIP_VEGAM))
			वापस AMDGPU_VCE_HARVEST_VCE1;

		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक vce_v3_0_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	adev->vce.harvest_config = vce_v3_0_get_harvest_config(adev);

	अगर ((adev->vce.harvest_config &
	     (AMDGPU_VCE_HARVEST_VCE0 | AMDGPU_VCE_HARVEST_VCE1)) ==
	    (AMDGPU_VCE_HARVEST_VCE0 | AMDGPU_VCE_HARVEST_VCE1))
		वापस -ENOENT;

	adev->vce.num_rings = 3;

	vce_v3_0_set_ring_funcs(adev);
	vce_v3_0_set_irq_funcs(adev);

	वापस 0;
पूर्ण

अटल पूर्णांक vce_v3_0_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा amdgpu_ring *ring;
	पूर्णांक r, i;

	/* VCE */
	r = amdgpu_irq_add_id(adev, AMDGPU_IRQ_CLIENTID_LEGACY, VISLANDS30_IV_SRCID_VCE_TRAP, &adev->vce.irq);
	अगर (r)
		वापस r;

	r = amdgpu_vce_sw_init(adev, VCE_V3_0_FW_SIZE +
		(VCE_V3_0_STACK_SIZE + VCE_V3_0_DATA_SIZE) * 2);
	अगर (r)
		वापस r;

	/* 52.8.3 required क्रम 3 ring support */
	अगर (adev->vce.fw_version < FW_52_8_3)
		adev->vce.num_rings = 2;

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

अटल पूर्णांक vce_v3_0_sw_fini(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = amdgpu_vce_suspend(adev);
	अगर (r)
		वापस r;

	वापस amdgpu_vce_sw_fini(adev);
पूर्ण

अटल पूर्णांक vce_v3_0_hw_init(व्योम *handle)
अणु
	पूर्णांक r, i;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	vce_v3_0_override_vce_घड़ी_gating(adev, true);

	amdgpu_asic_set_vce_घड़ीs(adev, 10000, 10000);

	क्रम (i = 0; i < adev->vce.num_rings; i++) अणु
		r = amdgpu_ring_test_helper(&adev->vce.ring[i]);
		अगर (r)
			वापस r;
	पूर्ण

	DRM_INFO("VCE initialized successfully.\n");

	वापस 0;
पूर्ण

अटल पूर्णांक vce_v3_0_hw_fini(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = vce_v3_0_रुको_क्रम_idle(handle);
	अगर (r)
		वापस r;

	vce_v3_0_stop(adev);
	वापस vce_v3_0_set_घड़ीgating_state(adev, AMD_CG_STATE_GATE);
पूर्ण

अटल पूर्णांक vce_v3_0_suspend(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = vce_v3_0_hw_fini(adev);
	अगर (r)
		वापस r;

	वापस amdgpu_vce_suspend(adev);
पूर्ण

अटल पूर्णांक vce_v3_0_resume(व्योम *handle)
अणु
	पूर्णांक r;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	r = amdgpu_vce_resume(adev);
	अगर (r)
		वापस r;

	वापस vce_v3_0_hw_init(adev);
पूर्ण

अटल व्योम vce_v3_0_mc_resume(काष्ठा amdgpu_device *adev, पूर्णांक idx)
अणु
	uपूर्णांक32_t offset, size;

	WREG32_P(mmVCE_CLOCK_GATING_A, 0, ~(1 << 16));
	WREG32_P(mmVCE_UENC_CLOCK_GATING, 0x1FF000, ~0xFF9FF000);
	WREG32_P(mmVCE_UENC_REG_CLOCK_GATING, 0x3F, ~0x3F);
	WREG32(mmVCE_CLOCK_GATING_B, 0x1FF);

	WREG32(mmVCE_LMI_CTRL, 0x00398000);
	WREG32_P(mmVCE_LMI_CACHE_CTRL, 0x0, ~0x1);
	WREG32(mmVCE_LMI_SWAP_CNTL, 0);
	WREG32(mmVCE_LMI_SWAP_CNTL1, 0);
	WREG32(mmVCE_LMI_VM_CTRL, 0);
	WREG32_OR(mmVCE_VCPU_CNTL, 0x00100000);

	अगर (adev->asic_type >= CHIP_STONEY) अणु
		WREG32(mmVCE_LMI_VCPU_CACHE_40BIT_BAR0, (adev->vce.gpu_addr >> 8));
		WREG32(mmVCE_LMI_VCPU_CACHE_40BIT_BAR1, (adev->vce.gpu_addr >> 8));
		WREG32(mmVCE_LMI_VCPU_CACHE_40BIT_BAR2, (adev->vce.gpu_addr >> 8));
	पूर्ण अन्यथा
		WREG32(mmVCE_LMI_VCPU_CACHE_40BIT_BAR, (adev->vce.gpu_addr >> 8));
	offset = AMDGPU_VCE_FIRMWARE_OFFSET;
	size = VCE_V3_0_FW_SIZE;
	WREG32(mmVCE_VCPU_CACHE_OFFSET0, offset & 0x7fffffff);
	WREG32(mmVCE_VCPU_CACHE_SIZE0, size);

	अगर (idx == 0) अणु
		offset += size;
		size = VCE_V3_0_STACK_SIZE;
		WREG32(mmVCE_VCPU_CACHE_OFFSET1, offset & 0x7fffffff);
		WREG32(mmVCE_VCPU_CACHE_SIZE1, size);
		offset += size;
		size = VCE_V3_0_DATA_SIZE;
		WREG32(mmVCE_VCPU_CACHE_OFFSET2, offset & 0x7fffffff);
		WREG32(mmVCE_VCPU_CACHE_SIZE2, size);
	पूर्ण अन्यथा अणु
		offset += size + VCE_V3_0_STACK_SIZE + VCE_V3_0_DATA_SIZE;
		size = VCE_V3_0_STACK_SIZE;
		WREG32(mmVCE_VCPU_CACHE_OFFSET1, offset & 0xfffffff);
		WREG32(mmVCE_VCPU_CACHE_SIZE1, size);
		offset += size;
		size = VCE_V3_0_DATA_SIZE;
		WREG32(mmVCE_VCPU_CACHE_OFFSET2, offset & 0xfffffff);
		WREG32(mmVCE_VCPU_CACHE_SIZE2, size);
	पूर्ण

	WREG32_P(mmVCE_LMI_CTRL2, 0x0, ~0x100);
	WREG32_FIELD(VCE_SYS_INT_EN, VCE_SYS_INT_TRAP_INTERRUPT_EN, 1);
पूर्ण

अटल bool vce_v3_0_is_idle(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 mask = 0;

	mask |= (adev->vce.harvest_config & AMDGPU_VCE_HARVEST_VCE0) ? 0 : SRBM_STATUS2__VCE0_BUSY_MASK;
	mask |= (adev->vce.harvest_config & AMDGPU_VCE_HARVEST_VCE1) ? 0 : SRBM_STATUS2__VCE1_BUSY_MASK;

	वापस !(RREG32(mmSRBM_STATUS2) & mask);
पूर्ण

अटल पूर्णांक vce_v3_0_रुको_क्रम_idle(व्योम *handle)
अणु
	अचिन्हित i;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	क्रम (i = 0; i < adev->usec_समयout; i++)
		अगर (vce_v3_0_is_idle(handle))
			वापस 0;

	वापस -ETIMEDOUT;
पूर्ण

#घोषणा  VCE_STATUS_VCPU_REPORT_AUTO_BUSY_MASK  0x00000008L   /* AUTO_BUSY */
#घोषणा  VCE_STATUS_VCPU_REPORT_RB0_BUSY_MASK   0x00000010L   /* RB0_BUSY */
#घोषणा  VCE_STATUS_VCPU_REPORT_RB1_BUSY_MASK   0x00000020L   /* RB1_BUSY */
#घोषणा  AMDGPU_VCE_STATUS_BUSY_MASK (VCE_STATUS_VCPU_REPORT_AUTO_BUSY_MASK | \
				      VCE_STATUS_VCPU_REPORT_RB0_BUSY_MASK)

अटल bool vce_v3_0_check_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 srbm_soft_reset = 0;

	/* According to VCE team , we should use VCE_STATUS instead
	 * SRBM_STATUS.VCE_BUSY bit क्रम busy status checking.
	 * GRBM_GFX_INDEX.INSTANCE_INDEX is used to specअगरy which VCE
	 * instance's रेजिस्टरs are accessed
	 * (0 क्रम 1st instance, 10 क्रम 2nd instance).
	 *
	 *VCE_STATUS
	 *|UENC|ACPI|AUTO ACTIVE|RB1 |RB0 |RB2 |          |FW_LOADED|JOB |
	 *|----+----+-----------+----+----+----+----------+---------+----|
	 *|bit8|bit7|    bit6   |bit5|bit4|bit3|   bit2   |  bit1   |bit0|
	 *
	 * VCE team suggest use bit 3--bit 6 क्रम busy status check
	 */
	mutex_lock(&adev->grbm_idx_mutex);
	WREG32(mmGRBM_GFX_INDEX, GET_VCE_INSTANCE(0));
	अगर (RREG32(mmVCE_STATUS) & AMDGPU_VCE_STATUS_BUSY_MASK) अणु
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset, SRBM_SOFT_RESET, SOFT_RESET_VCE0, 1);
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset, SRBM_SOFT_RESET, SOFT_RESET_VCE1, 1);
	पूर्ण
	WREG32(mmGRBM_GFX_INDEX, GET_VCE_INSTANCE(1));
	अगर (RREG32(mmVCE_STATUS) & AMDGPU_VCE_STATUS_BUSY_MASK) अणु
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset, SRBM_SOFT_RESET, SOFT_RESET_VCE0, 1);
		srbm_soft_reset = REG_SET_FIELD(srbm_soft_reset, SRBM_SOFT_RESET, SOFT_RESET_VCE1, 1);
	पूर्ण
	WREG32(mmGRBM_GFX_INDEX, GET_VCE_INSTANCE(0));
	mutex_unlock(&adev->grbm_idx_mutex);

	अगर (srbm_soft_reset) अणु
		adev->vce.srbm_soft_reset = srbm_soft_reset;
		वापस true;
	पूर्ण अन्यथा अणु
		adev->vce.srbm_soft_reset = 0;
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक vce_v3_0_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	u32 srbm_soft_reset;

	अगर (!adev->vce.srbm_soft_reset)
		वापस 0;
	srbm_soft_reset = adev->vce.srbm_soft_reset;

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

अटल पूर्णांक vce_v3_0_pre_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (!adev->vce.srbm_soft_reset)
		वापस 0;

	mdelay(5);

	वापस vce_v3_0_suspend(adev);
पूर्ण


अटल पूर्णांक vce_v3_0_post_soft_reset(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;

	अगर (!adev->vce.srbm_soft_reset)
		वापस 0;

	mdelay(5);

	वापस vce_v3_0_resume(adev);
पूर्ण

अटल पूर्णांक vce_v3_0_set_पूर्णांकerrupt_state(काष्ठा amdgpu_device *adev,
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

अटल पूर्णांक vce_v3_0_process_पूर्णांकerrupt(काष्ठा amdgpu_device *adev,
				      काष्ठा amdgpu_irq_src *source,
				      काष्ठा amdgpu_iv_entry *entry)
अणु
	DRM_DEBUG("IH: VCE\n");

	WREG32_FIELD(VCE_SYS_INT_STATUS, VCE_SYS_INT_TRAP_INTERRUPT_INT, 1);

	चयन (entry->src_data[0]) अणु
	हाल 0:
	हाल 1:
	हाल 2:
		amdgpu_fence_process(&adev->vce.ring[entry->src_data[0]]);
		अवरोध;
	शेष:
		DRM_ERROR("Unhandled interrupt: %d %d\n",
			  entry->src_id, entry->src_data[0]);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vce_v3_0_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	bool enable = (state == AMD_CG_STATE_GATE);
	पूर्णांक i;

	अगर (!(adev->cg_flags & AMD_CG_SUPPORT_VCE_MGCG))
		वापस 0;

	mutex_lock(&adev->grbm_idx_mutex);
	क्रम (i = 0; i < 2; i++) अणु
		/* Program VCE Instance 0 or 1 अगर not harvested */
		अगर (adev->vce.harvest_config & (1 << i))
			जारी;

		WREG32(mmGRBM_GFX_INDEX, GET_VCE_INSTANCE(i));

		अगर (!enable) अणु
			/* initialize VCE_CLOCK_GATING_A: Clock ON/OFF delay */
			uपूर्णांक32_t data = RREG32(mmVCE_CLOCK_GATING_A);
			data &= ~(0xf | 0xff0);
			data |= ((0x0 << 0) | (0x04 << 4));
			WREG32(mmVCE_CLOCK_GATING_A, data);

			/* initialize VCE_UENC_CLOCK_GATING: Clock ON/OFF delay */
			data = RREG32(mmVCE_UENC_CLOCK_GATING);
			data &= ~(0xf | 0xff0);
			data |= ((0x0 << 0) | (0x04 << 4));
			WREG32(mmVCE_UENC_CLOCK_GATING, data);
		पूर्ण

		vce_v3_0_set_vce_sw_घड़ी_gating(adev, enable);
	पूर्ण

	WREG32(mmGRBM_GFX_INDEX, mmGRBM_GFX_INDEX_DEFAULT);
	mutex_unlock(&adev->grbm_idx_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक vce_v3_0_set_घातergating_state(व्योम *handle,
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
	पूर्णांक ret = 0;

	अगर (state == AMD_PG_STATE_GATE) अणु
		ret = vce_v3_0_stop(adev);
		अगर (ret)
			जाओ out;
	पूर्ण अन्यथा अणु
		ret = vce_v3_0_start(adev);
		अगर (ret)
			जाओ out;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल व्योम vce_v3_0_get_घड़ीgating_state(व्योम *handle, u32 *flags)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	पूर्णांक data;

	mutex_lock(&adev->pm.mutex);

	अगर (adev->flags & AMD_IS_APU)
		data = RREG32_SMC(ixCURRENT_PG_STATUS_APU);
	अन्यथा
		data = RREG32_SMC(ixCURRENT_PG_STATUS);

	अगर (data & CURRENT_PG_STATUS__VCE_PG_STATUS_MASK) अणु
		DRM_INFO("Cannot get clockgating state when VCE is powergated.\n");
		जाओ out;
	पूर्ण

	WREG32_FIELD(GRBM_GFX_INDEX, VCE_INSTANCE, 0);

	/* AMD_CG_SUPPORT_VCE_MGCG */
	data = RREG32(mmVCE_CLOCK_GATING_A);
	अगर (data & (0x04 << 4))
		*flags |= AMD_CG_SUPPORT_VCE_MGCG;

out:
	mutex_unlock(&adev->pm.mutex);
पूर्ण

अटल व्योम vce_v3_0_ring_emit_ib(काष्ठा amdgpu_ring *ring,
				  काष्ठा amdgpu_job *job,
				  काष्ठा amdgpu_ib *ib,
				  uपूर्णांक32_t flags)
अणु
	अचिन्हित vmid = AMDGPU_JOB_GET_VMID(job);

	amdgpu_ring_ग_लिखो(ring, VCE_CMD_IB_VM);
	amdgpu_ring_ग_लिखो(ring, vmid);
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(ib->gpu_addr));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(ib->gpu_addr));
	amdgpu_ring_ग_लिखो(ring, ib->length_dw);
पूर्ण

अटल व्योम vce_v3_0_emit_vm_flush(काष्ठा amdgpu_ring *ring,
				   अचिन्हित पूर्णांक vmid, uपूर्णांक64_t pd_addr)
अणु
	amdgpu_ring_ग_लिखो(ring, VCE_CMD_UPDATE_PTB);
	amdgpu_ring_ग_लिखो(ring, vmid);
	amdgpu_ring_ग_लिखो(ring, pd_addr >> 12);

	amdgpu_ring_ग_लिखो(ring, VCE_CMD_FLUSH_TLB);
	amdgpu_ring_ग_लिखो(ring, vmid);
	amdgpu_ring_ग_लिखो(ring, VCE_CMD_END);
पूर्ण

अटल व्योम vce_v3_0_emit_pipeline_sync(काष्ठा amdgpu_ring *ring)
अणु
	uपूर्णांक32_t seq = ring->fence_drv.sync_seq;
	uपूर्णांक64_t addr = ring->fence_drv.gpu_addr;

	amdgpu_ring_ग_लिखो(ring, VCE_CMD_WAIT_GE);
	amdgpu_ring_ग_लिखो(ring, lower_32_bits(addr));
	amdgpu_ring_ग_लिखो(ring, upper_32_bits(addr));
	amdgpu_ring_ग_लिखो(ring, seq);
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs vce_v3_0_ip_funcs = अणु
	.name = "vce_v3_0",
	.early_init = vce_v3_0_early_init,
	.late_init = शून्य,
	.sw_init = vce_v3_0_sw_init,
	.sw_fini = vce_v3_0_sw_fini,
	.hw_init = vce_v3_0_hw_init,
	.hw_fini = vce_v3_0_hw_fini,
	.suspend = vce_v3_0_suspend,
	.resume = vce_v3_0_resume,
	.is_idle = vce_v3_0_is_idle,
	.रुको_क्रम_idle = vce_v3_0_रुको_क्रम_idle,
	.check_soft_reset = vce_v3_0_check_soft_reset,
	.pre_soft_reset = vce_v3_0_pre_soft_reset,
	.soft_reset = vce_v3_0_soft_reset,
	.post_soft_reset = vce_v3_0_post_soft_reset,
	.set_घड़ीgating_state = vce_v3_0_set_घड़ीgating_state,
	.set_घातergating_state = vce_v3_0_set_घातergating_state,
	.get_घड़ीgating_state = vce_v3_0_get_घड़ीgating_state,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_ring_funcs vce_v3_0_ring_phys_funcs = अणु
	.type = AMDGPU_RING_TYPE_VCE,
	.align_mask = 0xf,
	.nop = VCE_CMD_NO_OP,
	.support_64bit_ptrs = false,
	.no_user_fence = true,
	.get_rptr = vce_v3_0_ring_get_rptr,
	.get_wptr = vce_v3_0_ring_get_wptr,
	.set_wptr = vce_v3_0_ring_set_wptr,
	.parse_cs = amdgpu_vce_ring_parse_cs,
	.emit_frame_size =
		4 + /* vce_v3_0_emit_pipeline_sync */
		6, /* amdgpu_vce_ring_emit_fence x1 no user fence */
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

अटल स्थिर काष्ठा amdgpu_ring_funcs vce_v3_0_ring_vm_funcs = अणु
	.type = AMDGPU_RING_TYPE_VCE,
	.align_mask = 0xf,
	.nop = VCE_CMD_NO_OP,
	.support_64bit_ptrs = false,
	.no_user_fence = true,
	.get_rptr = vce_v3_0_ring_get_rptr,
	.get_wptr = vce_v3_0_ring_get_wptr,
	.set_wptr = vce_v3_0_ring_set_wptr,
	.parse_cs = amdgpu_vce_ring_parse_cs_vm,
	.emit_frame_size =
		6 + /* vce_v3_0_emit_vm_flush */
		4 + /* vce_v3_0_emit_pipeline_sync */
		6 + 6, /* amdgpu_vce_ring_emit_fence x2 vm fence */
	.emit_ib_size = 5, /* vce_v3_0_ring_emit_ib */
	.emit_ib = vce_v3_0_ring_emit_ib,
	.emit_vm_flush = vce_v3_0_emit_vm_flush,
	.emit_pipeline_sync = vce_v3_0_emit_pipeline_sync,
	.emit_fence = amdgpu_vce_ring_emit_fence,
	.test_ring = amdgpu_vce_ring_test_ring,
	.test_ib = amdgpu_vce_ring_test_ib,
	.insert_nop = amdgpu_ring_insert_nop,
	.pad_ib = amdgpu_ring_generic_pad_ib,
	.begin_use = amdgpu_vce_ring_begin_use,
	.end_use = amdgpu_vce_ring_end_use,
पूर्ण;

अटल व्योम vce_v3_0_set_ring_funcs(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक i;

	अगर (adev->asic_type >= CHIP_STONEY) अणु
		क्रम (i = 0; i < adev->vce.num_rings; i++) अणु
			adev->vce.ring[i].funcs = &vce_v3_0_ring_vm_funcs;
			adev->vce.ring[i].me = i;
		पूर्ण
		DRM_INFO("VCE enabled in VM mode\n");
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < adev->vce.num_rings; i++) अणु
			adev->vce.ring[i].funcs = &vce_v3_0_ring_phys_funcs;
			adev->vce.ring[i].me = i;
		पूर्ण
		DRM_INFO("VCE enabled in physical mode\n");
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा amdgpu_irq_src_funcs vce_v3_0_irq_funcs = अणु
	.set = vce_v3_0_set_पूर्णांकerrupt_state,
	.process = vce_v3_0_process_पूर्णांकerrupt,
पूर्ण;

अटल व्योम vce_v3_0_set_irq_funcs(काष्ठा amdgpu_device *adev)
अणु
	adev->vce.irq.num_types = 1;
	adev->vce.irq.funcs = &vce_v3_0_irq_funcs;
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version vce_v3_0_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_VCE,
	.major = 3,
	.minor = 0,
	.rev = 0,
	.funcs = &vce_v3_0_ip_funcs,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version vce_v3_1_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_VCE,
	.major = 3,
	.minor = 1,
	.rev = 0,
	.funcs = &vce_v3_0_ip_funcs,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version vce_v3_4_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_VCE,
	.major = 3,
	.minor = 4,
	.rev = 0,
	.funcs = &vce_v3_0_ip_funcs,
पूर्ण;
