<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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
#समावेश "athub_v2_0.h"

#समावेश "athub/athub_2_0_0_offset.h"
#समावेश "athub/athub_2_0_0_sh_mask.h"
#समावेश "athub/athub_2_0_0_default.h"

#समावेश "soc15_common.h"

अटल व्योम
athub_v2_0_update_medium_grain_घड़ी_gating(काष्ठा amdgpu_device *adev,
					    bool enable)
अणु
	uपूर्णांक32_t def, data;

	def = data = RREG32_SOC15(ATHUB, 0, mmATHUB_MISC_CNTL);

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_MC_MGCG))
		data |= ATHUB_MISC_CNTL__CG_ENABLE_MASK;
	अन्यथा
		data &= ~ATHUB_MISC_CNTL__CG_ENABLE_MASK;

	अगर (def != data)
		WREG32_SOC15(ATHUB, 0, mmATHUB_MISC_CNTL, data);
पूर्ण

अटल व्योम
athub_v2_0_update_medium_grain_light_sleep(काष्ठा amdgpu_device *adev,
					   bool enable)
अणु
	uपूर्णांक32_t def, data;

	def = data = RREG32_SOC15(ATHUB, 0, mmATHUB_MISC_CNTL);

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_MC_LS) &&
	    (adev->cg_flags & AMD_CG_SUPPORT_HDP_LS))
		data |= ATHUB_MISC_CNTL__CG_MEM_LS_ENABLE_MASK;
	अन्यथा
		data &= ~ATHUB_MISC_CNTL__CG_MEM_LS_ENABLE_MASK;

	अगर (def != data)
		WREG32_SOC15(ATHUB, 0, mmATHUB_MISC_CNTL, data);
पूर्ण

पूर्णांक athub_v2_0_set_घड़ीgating(काष्ठा amdgpu_device *adev,
			       क्रमागत amd_घड़ीgating_state state)
अणु
	अगर (amdgpu_sriov_vf(adev))
		वापस 0;

	चयन (adev->asic_type) अणु
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI14:
	हाल CHIP_NAVI12:
		athub_v2_0_update_medium_grain_घड़ी_gating(adev,
				state == AMD_CG_STATE_GATE);
		athub_v2_0_update_medium_grain_light_sleep(adev,
				state == AMD_CG_STATE_GATE);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

व्योम athub_v2_0_get_घड़ीgating(काष्ठा amdgpu_device *adev, u32 *flags)
अणु
	पूर्णांक data;

	/* AMD_CG_SUPPORT_ATHUB_MGCG */
	data = RREG32_SOC15(ATHUB, 0, mmATHUB_MISC_CNTL);
	अगर (data & ATHUB_MISC_CNTL__CG_ENABLE_MASK)
		*flags |= AMD_CG_SUPPORT_ATHUB_MGCG;

	/* AMD_CG_SUPPORT_ATHUB_LS */
	अगर (data & ATHUB_MISC_CNTL__CG_MEM_LS_ENABLE_MASK)
		*flags |= AMD_CG_SUPPORT_ATHUB_LS;
पूर्ण
