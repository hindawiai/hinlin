<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
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
#समावेश "df_v1_7.h"

#समावेश "df/df_1_7_default.h"
#समावेश "df/df_1_7_offset.h"
#समावेश "df/df_1_7_sh_mask.h"

अटल u32 df_v1_7_channel_number[] = अणु1, 2, 0, 4, 0, 8, 0, 16, 2पूर्ण;

अटल व्योम df_v1_7_sw_init(काष्ठा amdgpu_device *adev)
अणु
	adev->df.hash_status.hash_64k = false;
	adev->df.hash_status.hash_2m = false;
	adev->df.hash_status.hash_1g = false;
पूर्ण

अटल व्योम df_v1_7_sw_fini(काष्ठा amdgpu_device *adev)
अणु
पूर्ण

अटल व्योम df_v1_7_enable_broadcast_mode(काष्ठा amdgpu_device *adev,
					  bool enable)
अणु
	u32 पंचांगp;

	अगर (enable) अणु
		पंचांगp = RREG32_SOC15(DF, 0, mmFabricConfigAccessControl);
		पंचांगp &= ~FabricConfigAccessControl__CfgRegInstAccEn_MASK;
		WREG32_SOC15(DF, 0, mmFabricConfigAccessControl, पंचांगp);
	पूर्ण अन्यथा
		WREG32_SOC15(DF, 0, mmFabricConfigAccessControl,
			     mmFabricConfigAccessControl_DEFAULT);
पूर्ण

अटल u32 df_v1_7_get_fb_channel_number(काष्ठा amdgpu_device *adev)
अणु
	u32 पंचांगp;

	पंचांगp = RREG32_SOC15(DF, 0, mmDF_CS_AON0_DramBaseAddress0);
	पंचांगp &= DF_CS_AON0_DramBaseAddress0__IntLvNumChan_MASK;
	पंचांगp >>= DF_CS_AON0_DramBaseAddress0__IntLvNumChan__SHIFT;

	वापस पंचांगp;
पूर्ण

अटल u32 df_v1_7_get_hbm_channel_number(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक fb_channel_number;

	fb_channel_number = adev->df.funcs->get_fb_channel_number(adev);

	वापस df_v1_7_channel_number[fb_channel_number];
पूर्ण

अटल व्योम df_v1_7_update_medium_grain_घड़ी_gating(काष्ठा amdgpu_device *adev,
						     bool enable)
अणु
	u32 पंचांगp;

	/* Put DF on broadcast mode */
	adev->df.funcs->enable_broadcast_mode(adev, true);

	अगर (enable && (adev->cg_flags & AMD_CG_SUPPORT_DF_MGCG)) अणु
		पंचांगp = RREG32_SOC15(DF, 0, mmDF_PIE_AON0_DfGlobalClkGater);
		पंचांगp &= ~DF_PIE_AON0_DfGlobalClkGater__MGCGMode_MASK;
		पंचांगp |= DF_V1_7_MGCG_ENABLE_15_CYCLE_DELAY;
		WREG32_SOC15(DF, 0, mmDF_PIE_AON0_DfGlobalClkGater, पंचांगp);
	पूर्ण अन्यथा अणु
		पंचांगp = RREG32_SOC15(DF, 0, mmDF_PIE_AON0_DfGlobalClkGater);
		पंचांगp &= ~DF_PIE_AON0_DfGlobalClkGater__MGCGMode_MASK;
		पंचांगp |= DF_V1_7_MGCG_DISABLE;
		WREG32_SOC15(DF, 0, mmDF_PIE_AON0_DfGlobalClkGater, पंचांगp);
	पूर्ण

	/* Exit boradcast mode */
	adev->df.funcs->enable_broadcast_mode(adev, false);
पूर्ण

अटल व्योम df_v1_7_get_घड़ीgating_state(काष्ठा amdgpu_device *adev,
					  u32 *flags)
अणु
	u32 पंचांगp;

	/* AMD_CG_SUPPORT_DF_MGCG */
	पंचांगp = RREG32_SOC15(DF, 0, mmDF_PIE_AON0_DfGlobalClkGater);
	अगर (पंचांगp & DF_V1_7_MGCG_ENABLE_15_CYCLE_DELAY)
		*flags |= AMD_CG_SUPPORT_DF_MGCG;
पूर्ण

अटल व्योम df_v1_7_enable_ecc_क्रमce_par_wr_rmw(काष्ठा amdgpu_device *adev,
						bool enable)
अणु
	WREG32_FIELD15(DF, 0, DF_CS_AON0_CoherentSlaveModeCtrlA0,
		       ForceParWrRMW, enable);
पूर्ण

स्थिर काष्ठा amdgpu_df_funcs df_v1_7_funcs = अणु
	.sw_init = df_v1_7_sw_init,
	.sw_fini = df_v1_7_sw_fini,
	.enable_broadcast_mode = df_v1_7_enable_broadcast_mode,
	.get_fb_channel_number = df_v1_7_get_fb_channel_number,
	.get_hbm_channel_number = df_v1_7_get_hbm_channel_number,
	.update_medium_grain_घड़ी_gating = df_v1_7_update_medium_grain_घड़ी_gating,
	.get_घड़ीgating_state = df_v1_7_get_घड़ीgating_state,
	.enable_ecc_क्रमce_par_wr_rmw = df_v1_7_enable_ecc_क्रमce_par_wr_rmw,
पूर्ण;
