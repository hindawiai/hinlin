<शैली गुरु>
/*
 * Copyright 2020 Advanced Micro Devices, Inc.
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
#समावेश "amdgpu.h"
#समावेश "amdgpu_atombios.h"
#समावेश "hdp_v4_0.h"
#समावेश "amdgpu_ras.h"

#समावेश "hdp/hdp_4_0_offset.h"
#समावेश "hdp/hdp_4_0_sh_mask.h"
#समावेश <uapi/linux/kfd_ioctl.h>

/* क्रम Vega20 रेजिस्टर name change */
#घोषणा mmHDP_MEM_POWER_CTRL    0x00d4
#घोषणा HDP_MEM_POWER_CTRL__IPH_MEM_POWER_CTRL_EN_MASK  0x00000001L
#घोषणा HDP_MEM_POWER_CTRL__IPH_MEM_POWER_LS_EN_MASK    0x00000002L
#घोषणा HDP_MEM_POWER_CTRL__RC_MEM_POWER_CTRL_EN_MASK   0x00010000L
#घोषणा HDP_MEM_POWER_CTRL__RC_MEM_POWER_LS_EN_MASK     0x00020000L
#घोषणा mmHDP_MEM_POWER_CTRL_BASE_IDX   0

अटल व्योम hdp_v4_0_flush_hdp(काष्ठा amdgpu_device *adev,
				काष्ठा amdgpu_ring *ring)
अणु
	अगर (!ring || !ring->funcs->emit_wreg)
		WREG32_NO_KIQ((adev->rmmio_remap.reg_offset + KFD_MMIO_REMAP_HDP_MEM_FLUSH_CNTL) >> 2, 0);
	अन्यथा
		amdgpu_ring_emit_wreg(ring, (adev->rmmio_remap.reg_offset + KFD_MMIO_REMAP_HDP_MEM_FLUSH_CNTL) >> 2, 0);
पूर्ण

अटल व्योम hdp_v4_0_invalidate_hdp(काष्ठा amdgpu_device *adev,
				    काष्ठा amdgpu_ring *ring)
अणु
	अगर (adev->asic_type == CHIP_ALDEBARAN)
		वापस;

	अगर (!ring || !ring->funcs->emit_wreg)
		WREG32_SOC15_NO_KIQ(HDP, 0, mmHDP_READ_CACHE_INVALIDATE, 1);
	अन्यथा
		amdgpu_ring_emit_wreg(ring, SOC15_REG_OFFSET(
			HDP, 0, mmHDP_READ_CACHE_INVALIDATE), 1);
पूर्ण

अटल व्योम hdp_v4_0_reset_ras_error_count(काष्ठा amdgpu_device *adev)
अणु
	अगर (!amdgpu_ras_is_supported(adev, AMDGPU_RAS_BLOCK__HDP))
		वापस;
	/*पढ़ो back hdp ras counter to reset it to 0 */
	RREG32_SOC15(HDP, 0, mmHDP_EDC_CNT);
पूर्ण

अटल व्योम hdp_v4_0_update_घड़ी_gating(काष्ठा amdgpu_device *adev,
					 bool enable)
अणु
	uपूर्णांक32_t def, data;

	अगर (adev->asic_type == CHIP_VEGA10 ||
	    adev->asic_type == CHIP_VEGA12 ||
	    adev->asic_type == CHIP_RAVEN) अणु
		def = data = RREG32(SOC15_REG_OFFSET(HDP, 0, mmHDP_MEM_POWER_LS));

		अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_HDP_LS))
			data |= HDP_MEM_POWER_LS__LS_ENABLE_MASK;
		अन्यथा
			data &= ~HDP_MEM_POWER_LS__LS_ENABLE_MASK;

		अगर (def != data)
			WREG32(SOC15_REG_OFFSET(HDP, 0, mmHDP_MEM_POWER_LS), data);
	पूर्ण अन्यथा अणु
		def = data = RREG32(SOC15_REG_OFFSET(HDP, 0, mmHDP_MEM_POWER_CTRL));

		अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_HDP_LS))
			data |= HDP_MEM_POWER_CTRL__IPH_MEM_POWER_CTRL_EN_MASK |
				HDP_MEM_POWER_CTRL__IPH_MEM_POWER_LS_EN_MASK |
				HDP_MEM_POWER_CTRL__RC_MEM_POWER_CTRL_EN_MASK |
				HDP_MEM_POWER_CTRL__RC_MEM_POWER_LS_EN_MASK;
		अन्यथा
			data &= ~(HDP_MEM_POWER_CTRL__IPH_MEM_POWER_CTRL_EN_MASK |
				  HDP_MEM_POWER_CTRL__IPH_MEM_POWER_LS_EN_MASK |
				  HDP_MEM_POWER_CTRL__RC_MEM_POWER_CTRL_EN_MASK |
				  HDP_MEM_POWER_CTRL__RC_MEM_POWER_LS_EN_MASK);

		अगर (def != data)
			WREG32(SOC15_REG_OFFSET(HDP, 0, mmHDP_MEM_POWER_CTRL), data);
	पूर्ण
पूर्ण

अटल व्योम hdp_v4_0_get_घड़ीgating_state(काष्ठा amdgpu_device *adev,
					    u32 *flags)
अणु
	पूर्णांक data;

	/* AMD_CG_SUPPORT_HDP_LS */
	data = RREG32(SOC15_REG_OFFSET(HDP, 0, mmHDP_MEM_POWER_LS));
	अगर (data & HDP_MEM_POWER_LS__LS_ENABLE_MASK)
		*flags |= AMD_CG_SUPPORT_HDP_LS;
पूर्ण

अटल व्योम hdp_v4_0_init_रेजिस्टरs(काष्ठा amdgpu_device *adev)
अणु
	चयन (adev->asic_type) अणु
	हाल CHIP_ARCTURUS:
		WREG32_FIELD15(HDP, 0, HDP_MMHUB_CNTL, HDP_MMHUB_GCC, 1);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	WREG32_FIELD15(HDP, 0, HDP_MISC_CNTL, FLUSH_INVALIDATE_CACHE, 1);

	WREG32_SOC15(HDP, 0, mmHDP_NONSURFACE_BASE, (adev->gmc.vram_start >> 8));
	WREG32_SOC15(HDP, 0, mmHDP_NONSURFACE_BASE_HI, (adev->gmc.vram_start >> 40));
पूर्ण

स्थिर काष्ठा amdgpu_hdp_funcs hdp_v4_0_funcs = अणु
	.flush_hdp = hdp_v4_0_flush_hdp,
	.invalidate_hdp = hdp_v4_0_invalidate_hdp,
	.reset_ras_error_count = hdp_v4_0_reset_ras_error_count,
	.update_घड़ी_gating = hdp_v4_0_update_घड़ी_gating,
	.get_घड़ी_gating_state = hdp_v4_0_get_घड़ीgating_state,
	.init_रेजिस्टरs = hdp_v4_0_init_रेजिस्टरs,
पूर्ण;
