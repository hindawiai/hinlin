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

#समावेश "smu7_hwmgr.h"
#समावेश "smu7_clockpowergating.h"
#समावेश "smu7_common.h"

अटल पूर्णांक smu7_enable_disable_uvd_dpm(काष्ठा pp_hwmgr *hwmgr, bool enable)
अणु
	वापस smum_send_msg_to_smc(hwmgr, enable ?
			PPSMC_MSG_UVDDPM_Enable :
			PPSMC_MSG_UVDDPM_Disable,
			शून्य);
पूर्ण

अटल पूर्णांक smu7_enable_disable_vce_dpm(काष्ठा pp_hwmgr *hwmgr, bool enable)
अणु
	वापस smum_send_msg_to_smc(hwmgr, enable ?
			PPSMC_MSG_VCEDPM_Enable :
			PPSMC_MSG_VCEDPM_Disable,
			शून्य);
पूर्ण

अटल पूर्णांक smu7_update_uvd_dpm(काष्ठा pp_hwmgr *hwmgr, bool bgate)
अणु
	अगर (!bgate)
		smum_update_smc_table(hwmgr, SMU_UVD_TABLE);
	वापस smu7_enable_disable_uvd_dpm(hwmgr, !bgate);
पूर्ण

अटल पूर्णांक smu7_update_vce_dpm(काष्ठा pp_hwmgr *hwmgr, bool bgate)
अणु
	अगर (!bgate)
		smum_update_smc_table(hwmgr, SMU_VCE_TABLE);
	वापस smu7_enable_disable_vce_dpm(hwmgr, !bgate);
पूर्ण

पूर्णांक smu7_घातerकरोwn_uvd(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (phm_cf_want_uvd_घातer_gating(hwmgr))
		वापस smum_send_msg_to_smc(hwmgr,
				PPSMC_MSG_UVDPowerOFF,
				शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_घातerup_uvd(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (phm_cf_want_uvd_घातer_gating(hwmgr)) अणु
		अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				  PHM_Platक्रमmCaps_UVDDynamicPowerGating)) अणु
			वापस smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_UVDPowerON, 1, शून्य);
		पूर्ण अन्यथा अणु
			वापस smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_UVDPowerON, 0, शून्य);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu7_घातerकरोwn_vce(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (phm_cf_want_vce_घातer_gating(hwmgr))
		वापस smum_send_msg_to_smc(hwmgr,
				PPSMC_MSG_VCEPowerOFF,
				शून्य);
	वापस 0;
पूर्ण

अटल पूर्णांक smu7_घातerup_vce(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (phm_cf_want_vce_घातer_gating(hwmgr))
		वापस smum_send_msg_to_smc(hwmgr,
				PPSMC_MSG_VCEPowerON,
				शून्य);
	वापस 0;
पूर्ण

पूर्णांक smu7_disable_घड़ी_घातer_gating(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	data->uvd_घातer_gated = false;
	data->vce_घातer_gated = false;

	smu7_घातerup_uvd(hwmgr);
	smu7_घातerup_vce(hwmgr);

	वापस 0;
पूर्ण

व्योम smu7_घातergate_uvd(काष्ठा pp_hwmgr *hwmgr, bool bgate)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	data->uvd_घातer_gated = bgate;

	अगर (bgate) अणु
		amdgpu_device_ip_set_घातergating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_UVD,
						AMD_PG_STATE_GATE);
		amdgpu_device_ip_set_घड़ीgating_state(hwmgr->adev,
				AMD_IP_BLOCK_TYPE_UVD,
				AMD_CG_STATE_GATE);
		smu7_update_uvd_dpm(hwmgr, true);
		smu7_घातerकरोwn_uvd(hwmgr);
	पूर्ण अन्यथा अणु
		smu7_घातerup_uvd(hwmgr);
		amdgpu_device_ip_set_घड़ीgating_state(hwmgr->adev,
				AMD_IP_BLOCK_TYPE_UVD,
				AMD_CG_STATE_UNGATE);
		amdgpu_device_ip_set_घातergating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_UVD,
						AMD_PG_STATE_UNGATE);
		smu7_update_uvd_dpm(hwmgr, false);
	पूर्ण

पूर्ण

व्योम smu7_घातergate_vce(काष्ठा pp_hwmgr *hwmgr, bool bgate)
अणु
	काष्ठा smu7_hwmgr *data = (काष्ठा smu7_hwmgr *)(hwmgr->backend);

	data->vce_घातer_gated = bgate;

	अगर (bgate) अणु
		amdgpu_device_ip_set_घातergating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_VCE,
						AMD_PG_STATE_GATE);
		amdgpu_device_ip_set_घड़ीgating_state(hwmgr->adev,
				AMD_IP_BLOCK_TYPE_VCE,
				AMD_CG_STATE_GATE);
		smu7_update_vce_dpm(hwmgr, true);
		smu7_घातerकरोwn_vce(hwmgr);
	पूर्ण अन्यथा अणु
		smu7_घातerup_vce(hwmgr);
		amdgpu_device_ip_set_घड़ीgating_state(hwmgr->adev,
				AMD_IP_BLOCK_TYPE_VCE,
				AMD_CG_STATE_UNGATE);
		amdgpu_device_ip_set_घातergating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_VCE,
						AMD_PG_STATE_UNGATE);
		smu7_update_vce_dpm(hwmgr, false);
	पूर्ण
पूर्ण

पूर्णांक smu7_update_घड़ी_gatings(काष्ठा pp_hwmgr *hwmgr,
					स्थिर uपूर्णांक32_t *msg_id)
अणु
	PPSMC_Msg msg;
	uपूर्णांक32_t value;

	अगर (!(hwmgr->feature_mask & PP_ENABLE_GFX_CG_THRU_SMU))
		वापस 0;

	चयन ((*msg_id & PP_GROUP_MASK) >> PP_GROUP_SHIFT) अणु
	हाल PP_GROUP_GFX:
		चयन ((*msg_id & PP_BLOCK_MASK) >> PP_BLOCK_SHIFT) अणु
		हाल PP_BLOCK_GFX_CG:
			अगर (PP_STATE_SUPPORT_CG & *msg_id) अणु
				msg = ((*msg_id & PP_STATE_MASK) & PP_STATE_CG) ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_GFX_CGCG_MASK;

				अगर (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value, शून्य))
					वापस -EINVAL;
			पूर्ण
			अगर (PP_STATE_SUPPORT_LS & *msg_id) अणु
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_LS
					? PPSMC_MSG_EnableClockGatingFeature
					: PPSMC_MSG_DisableClockGatingFeature;
				value = CG_GFX_CGLS_MASK;

				अगर (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value, शून्य))
					वापस -EINVAL;
			पूर्ण
			अवरोध;

		हाल PP_BLOCK_GFX_3D:
			अगर (PP_STATE_SUPPORT_CG & *msg_id) अणु
				msg = ((*msg_id & PP_STATE_MASK) & PP_STATE_CG) ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_GFX_3DCG_MASK;

				अगर (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value, शून्य))
					वापस -EINVAL;
			पूर्ण

			अगर  (PP_STATE_SUPPORT_LS & *msg_id) अणु
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_LS ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_GFX_3DLS_MASK;

				अगर (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value, शून्य))
					वापस -EINVAL;
			पूर्ण
			अवरोध;

		हाल PP_BLOCK_GFX_RLC:
			अगर (PP_STATE_SUPPORT_LS & *msg_id) अणु
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_LS ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_GFX_RLC_LS_MASK;

				अगर (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value, शून्य))
					वापस -EINVAL;
			पूर्ण
			अवरोध;

		हाल PP_BLOCK_GFX_CP:
			अगर (PP_STATE_SUPPORT_LS & *msg_id) अणु
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_LS ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_GFX_CP_LS_MASK;

				अगर (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value, शून्य))
					वापस -EINVAL;
			पूर्ण
			अवरोध;

		हाल PP_BLOCK_GFX_MG:
			अगर (PP_STATE_SUPPORT_CG & *msg_id) अणु
				msg = ((*msg_id & PP_STATE_MASK) & PP_STATE_CG)	?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = (CG_CPF_MGCG_MASK | CG_RLC_MGCG_MASK |
						CG_GFX_OTHERS_MGCG_MASK);

				अगर (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value, शून्य))
					वापस -EINVAL;
			पूर्ण
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	हाल PP_GROUP_SYS:
		चयन ((*msg_id & PP_BLOCK_MASK) >> PP_BLOCK_SHIFT) अणु
		हाल PP_BLOCK_SYS_BIF:
			अगर (PP_STATE_SUPPORT_CG & *msg_id) अणु
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_CG ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_SYS_BIF_MGCG_MASK;

				अगर (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value, शून्य))
					वापस -EINVAL;
			पूर्ण
			अगर  (PP_STATE_SUPPORT_LS & *msg_id) अणु
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_LS ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_SYS_BIF_MGLS_MASK;

				अगर (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value, शून्य))
					वापस -EINVAL;
			पूर्ण
			अवरोध;

		हाल PP_BLOCK_SYS_MC:
			अगर (PP_STATE_SUPPORT_CG & *msg_id) अणु
				msg = ((*msg_id & PP_STATE_MASK) & PP_STATE_CG)	?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_SYS_MC_MGCG_MASK;

				अगर (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value, शून्य))
					वापस -EINVAL;
			पूर्ण

			अगर (PP_STATE_SUPPORT_LS & *msg_id) अणु
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_LS ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_SYS_MC_MGLS_MASK;

				अगर (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value, शून्य))
					वापस -EINVAL;
			पूर्ण
			अवरोध;

		हाल PP_BLOCK_SYS_DRM:
			अगर (PP_STATE_SUPPORT_CG & *msg_id) अणु
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_CG ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_SYS_DRM_MGCG_MASK;

				अगर (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value, शून्य))
					वापस -EINVAL;
			पूर्ण
			अगर (PP_STATE_SUPPORT_LS & *msg_id) अणु
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_LS ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_SYS_DRM_MGLS_MASK;

				अगर (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value, शून्य))
					वापस -EINVAL;
			पूर्ण
			अवरोध;

		हाल PP_BLOCK_SYS_HDP:
			अगर (PP_STATE_SUPPORT_CG & *msg_id) अणु
				msg = ((*msg_id & PP_STATE_MASK) & PP_STATE_CG) ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_SYS_HDP_MGCG_MASK;

				अगर (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value, शून्य))
					वापस -EINVAL;
			पूर्ण

			अगर (PP_STATE_SUPPORT_LS & *msg_id) अणु
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_LS ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_SYS_HDP_MGLS_MASK;

				अगर (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value, शून्य))
					वापस -EINVAL;
			पूर्ण
			अवरोध;

		हाल PP_BLOCK_SYS_SDMA:
			अगर (PP_STATE_SUPPORT_CG & *msg_id) अणु
				msg = ((*msg_id & PP_STATE_MASK) & PP_STATE_CG)	?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_SYS_SDMA_MGCG_MASK;

				अगर (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value, शून्य))
					वापस -EINVAL;
			पूर्ण

			अगर (PP_STATE_SUPPORT_LS & *msg_id) अणु
				msg = (*msg_id & PP_STATE_MASK) & PP_STATE_LS ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_SYS_SDMA_MGLS_MASK;

				अगर (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value, शून्य))
					वापस -EINVAL;
			पूर्ण
			अवरोध;

		हाल PP_BLOCK_SYS_ROM:
			अगर (PP_STATE_SUPPORT_CG & *msg_id) अणु
				msg = ((*msg_id & PP_STATE_MASK) & PP_STATE_CG) ?
						PPSMC_MSG_EnableClockGatingFeature :
						PPSMC_MSG_DisableClockGatingFeature;
				value = CG_SYS_ROM_MASK;

				अगर (smum_send_msg_to_smc_with_parameter(
						hwmgr, msg, value, शून्य))
					वापस -EINVAL;
			पूर्ण
			अवरोध;

		शेष:
			वापस -EINVAL;

		पूर्ण
		अवरोध;

	शेष:
		वापस -EINVAL;

	पूर्ण

	वापस 0;
पूर्ण

/* This function is क्रम Polaris11 only क्रम now,
 * Powerplay will only control the अटल per CU Power Gating.
 * Dynamic per CU Power Gating will be करोne in gfx.
 */
पूर्णांक smu7_घातergate_gfx(काष्ठा pp_hwmgr *hwmgr, bool enable)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	अगर (enable)
		वापस smum_send_msg_to_smc_with_parameter(hwmgr,
					PPSMC_MSG_GFX_CU_PG_ENABLE,
					adev->gfx.cu_info.number,
					शून्य);
	अन्यथा
		वापस smum_send_msg_to_smc(hwmgr,
				PPSMC_MSG_GFX_CU_PG_DISABLE,
				शून्य);
पूर्ण
