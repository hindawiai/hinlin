<शैली गुरु>
/*
 * Copyright 2012 Advanced Micro Devices, Inc.
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

#समावेश "radeon.h"
#समावेश "trinityd.h"
#समावेश "trinity_dpm.h"
#समावेश "ppsmc.h"

अटल पूर्णांक trinity_notअगरy_message_to_smu(काष्ठा radeon_device *rdev, u32 id)
अणु
	पूर्णांक i;
	u32 v = 0;

	WREG32(SMC_MESSAGE_0, id);
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर (RREG32(SMC_RESP_0) != 0)
			अवरोध;
		udelay(1);
	पूर्ण
	v = RREG32(SMC_RESP_0);

	अगर (v != 1) अणु
		अगर (v == 0xFF) अणु
			DRM_ERROR("SMC failed to handle the message!\n");
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (v == 0xFE) अणु
			DRM_ERROR("Unknown SMC message!\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक trinity_dpm_bapm_enable(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable)
		वापस trinity_notअगरy_message_to_smu(rdev, PPSMC_MSG_EnableBAPM);
	अन्यथा
		वापस trinity_notअगरy_message_to_smu(rdev, PPSMC_MSG_DisableBAPM);
पूर्ण

पूर्णांक trinity_dpm_config(काष्ठा radeon_device *rdev, bool enable)
अणु
	अगर (enable)
		WREG32_SMC(SMU_SCRATCH0, 1);
	अन्यथा
		WREG32_SMC(SMU_SCRATCH0, 0);

	वापस trinity_notअगरy_message_to_smu(rdev, PPSMC_MSG_DPM_Config);
पूर्ण

पूर्णांक trinity_dpm_क्रमce_state(काष्ठा radeon_device *rdev, u32 n)
अणु
	WREG32_SMC(SMU_SCRATCH0, n);

	वापस trinity_notअगरy_message_to_smu(rdev, PPSMC_MSG_DPM_ForceState);
पूर्ण

पूर्णांक trinity_dpm_n_levels_disabled(काष्ठा radeon_device *rdev, u32 n)
अणु
	WREG32_SMC(SMU_SCRATCH0, n);

	वापस trinity_notअगरy_message_to_smu(rdev, PPSMC_MSG_DPM_N_LevelsDisabled);
पूर्ण

पूर्णांक trinity_uvd_dpm_config(काष्ठा radeon_device *rdev)
अणु
	वापस trinity_notअगरy_message_to_smu(rdev, PPSMC_MSG_UVD_DPM_Config);
पूर्ण

पूर्णांक trinity_dpm_no_क्रमced_level(काष्ठा radeon_device *rdev)
अणु
	वापस trinity_notअगरy_message_to_smu(rdev, PPSMC_MSG_NoForcedLevel);
पूर्ण

पूर्णांक trinity_dce_enable_voltage_adjusपंचांगent(काष्ठा radeon_device *rdev,
					  bool enable)
अणु
	अगर (enable)
		वापस trinity_notअगरy_message_to_smu(rdev, PPSMC_MSG_DCE_AllowVoltageAdjusपंचांगent);
	अन्यथा
		वापस trinity_notअगरy_message_to_smu(rdev, PPSMC_MSG_DCE_RemoveVoltageAdjusपंचांगent);
पूर्ण

पूर्णांक trinity_gfx_dynamic_mgpg_config(काष्ठा radeon_device *rdev)
अणु
	वापस trinity_notअगरy_message_to_smu(rdev, PPSMC_MSG_PG_SIMD_Config);
पूर्ण

व्योम trinity_acquire_mutex(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक i;

	WREG32(SMC_INT_REQ, 1);
	क्रम (i = 0; i < rdev->usec_समयout; i++) अणु
		अगर ((RREG32(SMC_INT_REQ) & 0xffff) == 1)
			अवरोध;
		udelay(1);
	पूर्ण
पूर्ण

व्योम trinity_release_mutex(काष्ठा radeon_device *rdev)
अणु
	WREG32(SMC_INT_REQ, 0);
पूर्ण
