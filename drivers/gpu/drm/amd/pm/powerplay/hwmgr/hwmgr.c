<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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

#समावेश "pp_debug.h"
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <drm/amdgpu_drm.h>
#समावेश "power_state.h"
#समावेश "hwmgr.h"
#समावेश "ppsmc.h"
#समावेश "amd_acpi.h"
#समावेश "pp_psm.h"
#समावेश "vega10_hwmgr.h"

बाह्य स्थिर काष्ठा pp_smumgr_func ci_smu_funcs;
बाह्य स्थिर काष्ठा pp_smumgr_func smu8_smu_funcs;
बाह्य स्थिर काष्ठा pp_smumgr_func iceland_smu_funcs;
बाह्य स्थिर काष्ठा pp_smumgr_func tonga_smu_funcs;
बाह्य स्थिर काष्ठा pp_smumgr_func fiji_smu_funcs;
बाह्य स्थिर काष्ठा pp_smumgr_func polaris10_smu_funcs;
बाह्य स्थिर काष्ठा pp_smumgr_func vegam_smu_funcs;
बाह्य स्थिर काष्ठा pp_smumgr_func vega10_smu_funcs;
बाह्य स्थिर काष्ठा pp_smumgr_func vega12_smu_funcs;
बाह्य स्थिर काष्ठा pp_smumgr_func smu10_smu_funcs;
बाह्य स्थिर काष्ठा pp_smumgr_func vega20_smu_funcs;

बाह्य पूर्णांक smu10_init_function_poपूर्णांकers(काष्ठा pp_hwmgr *hwmgr);

अटल पूर्णांक polaris_set_asic_special_caps(काष्ठा pp_hwmgr *hwmgr);
अटल व्योम hwmgr_init_शेष_caps(काष्ठा pp_hwmgr *hwmgr);
अटल पूर्णांक hwmgr_set_user_specअगरy_caps(काष्ठा pp_hwmgr *hwmgr);
अटल पूर्णांक fiji_set_asic_special_caps(काष्ठा pp_hwmgr *hwmgr);
अटल पूर्णांक tonga_set_asic_special_caps(काष्ठा pp_hwmgr *hwmgr);
अटल पूर्णांक topaz_set_asic_special_caps(काष्ठा pp_hwmgr *hwmgr);
अटल पूर्णांक ci_set_asic_special_caps(काष्ठा pp_hwmgr *hwmgr);


अटल व्योम hwmgr_init_workload_prority(काष्ठा pp_hwmgr *hwmgr)
अणु
	hwmgr->workload_prority[PP_SMC_POWER_PROखाता_BOOTUP_DEFAULT] = 0;
	hwmgr->workload_prority[PP_SMC_POWER_PROखाता_FULLSCREEN3D] = 1;
	hwmgr->workload_prority[PP_SMC_POWER_PROखाता_POWERSAVING] = 2;
	hwmgr->workload_prority[PP_SMC_POWER_PROखाता_VIDEO] = 3;
	hwmgr->workload_prority[PP_SMC_POWER_PROखाता_VR] = 4;
	hwmgr->workload_prority[PP_SMC_POWER_PROखाता_COMPUTE] = 5;

	hwmgr->workload_setting[0] = PP_SMC_POWER_PROखाता_BOOTUP_DEFAULT;
	hwmgr->workload_setting[1] = PP_SMC_POWER_PROखाता_FULLSCREEN3D;
	hwmgr->workload_setting[2] = PP_SMC_POWER_PROखाता_POWERSAVING;
	hwmgr->workload_setting[3] = PP_SMC_POWER_PROखाता_VIDEO;
	hwmgr->workload_setting[4] = PP_SMC_POWER_PROखाता_VR;
	hwmgr->workload_setting[5] = PP_SMC_POWER_PROखाता_COMPUTE;
पूर्ण

पूर्णांक hwmgr_early_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev;

	अगर (!hwmgr)
		वापस -EINVAL;

	hwmgr->usec_समयout = AMD_MAX_USEC_TIMEOUT;
	hwmgr->pp_table_version = PP_TABLE_V1;
	hwmgr->dpm_level = AMD_DPM_FORCED_LEVEL_AUTO;
	hwmgr->request_dpm_level = AMD_DPM_FORCED_LEVEL_AUTO;
	hwmgr_init_शेष_caps(hwmgr);
	hwmgr_set_user_specअगरy_caps(hwmgr);
	hwmgr->fan_ctrl_is_in_शेष_mode = true;
	hwmgr_init_workload_prority(hwmgr);
	hwmgr->gfxoff_state_changed_by_workload = false;

	adev = hwmgr->adev;

	चयन (hwmgr->chip_family) अणु
	हाल AMDGPU_FAMILY_CI:
		adev->pm.pp_feature &= ~PP_GFXOFF_MASK;
		hwmgr->smumgr_funcs = &ci_smu_funcs;
		ci_set_asic_special_caps(hwmgr);
		hwmgr->feature_mask &= ~(PP_VBI_TIME_SUPPORT_MASK |
					 PP_ENABLE_GFX_CG_THRU_SMU |
					 PP_GFXOFF_MASK);
		hwmgr->pp_table_version = PP_TABLE_V0;
		hwmgr->od_enabled = false;
		smu7_init_function_poपूर्णांकers(hwmgr);
		अवरोध;
	हाल AMDGPU_FAMILY_CZ:
		adev->pm.pp_feature &= ~PP_GFXOFF_MASK;
		hwmgr->od_enabled = false;
		hwmgr->smumgr_funcs = &smu8_smu_funcs;
		hwmgr->feature_mask &= ~PP_GFXOFF_MASK;
		smu8_init_function_poपूर्णांकers(hwmgr);
		अवरोध;
	हाल AMDGPU_FAMILY_VI:
		adev->pm.pp_feature &= ~PP_GFXOFF_MASK;
		hwmgr->feature_mask &= ~PP_GFXOFF_MASK;
		चयन (hwmgr->chip_id) अणु
		हाल CHIP_TOPAZ:
			hwmgr->smumgr_funcs = &iceland_smu_funcs;
			topaz_set_asic_special_caps(hwmgr);
			hwmgr->feature_mask &= ~ (PP_VBI_TIME_SUPPORT_MASK |
						PP_ENABLE_GFX_CG_THRU_SMU);
			hwmgr->pp_table_version = PP_TABLE_V0;
			hwmgr->od_enabled = false;
			अवरोध;
		हाल CHIP_TONGA:
			hwmgr->smumgr_funcs = &tonga_smu_funcs;
			tonga_set_asic_special_caps(hwmgr);
			hwmgr->feature_mask &= ~PP_VBI_TIME_SUPPORT_MASK;
			अवरोध;
		हाल CHIP_FIJI:
			hwmgr->smumgr_funcs = &fiji_smu_funcs;
			fiji_set_asic_special_caps(hwmgr);
			hwmgr->feature_mask &= ~ (PP_VBI_TIME_SUPPORT_MASK |
						PP_ENABLE_GFX_CG_THRU_SMU);
			अवरोध;
		हाल CHIP_POLARIS11:
		हाल CHIP_POLARIS10:
		हाल CHIP_POLARIS12:
			hwmgr->smumgr_funcs = &polaris10_smu_funcs;
			polaris_set_asic_special_caps(hwmgr);
			hwmgr->feature_mask &= ~(PP_UVD_HANDSHAKE_MASK);
			अवरोध;
		हाल CHIP_VEGAM:
			hwmgr->smumgr_funcs = &vegam_smu_funcs;
			polaris_set_asic_special_caps(hwmgr);
			hwmgr->feature_mask &= ~(PP_UVD_HANDSHAKE_MASK);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		smu7_init_function_poपूर्णांकers(hwmgr);
		अवरोध;
	हाल AMDGPU_FAMILY_AI:
		चयन (hwmgr->chip_id) अणु
		हाल CHIP_VEGA10:
			adev->pm.pp_feature &= ~PP_GFXOFF_MASK;
			hwmgr->feature_mask &= ~PP_GFXOFF_MASK;
			hwmgr->smumgr_funcs = &vega10_smu_funcs;
			vega10_hwmgr_init(hwmgr);
			अवरोध;
		हाल CHIP_VEGA12:
			hwmgr->smumgr_funcs = &vega12_smu_funcs;
			vega12_hwmgr_init(hwmgr);
			अवरोध;
		हाल CHIP_VEGA20:
			adev->pm.pp_feature &= ~PP_GFXOFF_MASK;
			hwmgr->feature_mask &= ~PP_GFXOFF_MASK;
			hwmgr->smumgr_funcs = &vega20_smu_funcs;
			vega20_hwmgr_init(hwmgr);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल AMDGPU_FAMILY_RV:
		चयन (hwmgr->chip_id) अणु
		हाल CHIP_RAVEN:
			hwmgr->od_enabled = false;
			hwmgr->smumgr_funcs = &smu10_smu_funcs;
			smu10_init_function_poपूर्णांकers(hwmgr);
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

पूर्णांक hwmgr_sw_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (!hwmgr|| !hwmgr->smumgr_funcs || !hwmgr->smumgr_funcs->smu_init)
		वापस -EINVAL;

	phm_रेजिस्टर_irq_handlers(hwmgr);
	pr_info("hwmgr_sw_init smu backed is %s\n", hwmgr->smumgr_funcs->name);

	वापस hwmgr->smumgr_funcs->smu_init(hwmgr);
पूर्ण


पूर्णांक hwmgr_sw_fini(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (hwmgr && hwmgr->smumgr_funcs && hwmgr->smumgr_funcs->smu_fini)
		hwmgr->smumgr_funcs->smu_fini(hwmgr);

	वापस 0;
पूर्ण

पूर्णांक hwmgr_hw_init(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक ret = 0;

	hwmgr->pp_one_vf = amdgpu_sriov_is_pp_one_vf((काष्ठा amdgpu_device *)hwmgr->adev);
	hwmgr->pm_en = (amdgpu_dpm && (hwmgr->not_vf || hwmgr->pp_one_vf))
			? true : false;
	अगर (!hwmgr->pm_en)
		वापस 0;

	अगर (!hwmgr->pptable_func ||
	    !hwmgr->pptable_func->pptable_init ||
	    !hwmgr->hwmgr_func->backend_init) अणु
		hwmgr->pm_en = false;
		pr_info("dpm not supported \n");
		वापस 0;
	पूर्ण

	ret = hwmgr->pptable_func->pptable_init(hwmgr);
	अगर (ret)
		जाओ err;

	((काष्ठा amdgpu_device *)hwmgr->adev)->pm.no_fan =
				hwmgr->thermal_controller.fanInfo.bNoFan;

	ret = hwmgr->hwmgr_func->backend_init(hwmgr);
	अगर (ret)
		जाओ err1;
 /* make sure dc limits are valid */
	अगर ((hwmgr->dyn_state.max_घड़ी_voltage_on_dc.sclk == 0) ||
			(hwmgr->dyn_state.max_घड़ी_voltage_on_dc.mclk == 0))
			hwmgr->dyn_state.max_घड़ी_voltage_on_dc =
					hwmgr->dyn_state.max_घड़ी_voltage_on_ac;

	ret = psm_init_घातer_state_table(hwmgr);
	अगर (ret)
		जाओ err2;

	ret = phm_setup_asic(hwmgr);
	अगर (ret)
		जाओ err2;

	ret = phm_enable_dynamic_state_management(hwmgr);
	अगर (ret)
		जाओ err2;
	ret = phm_start_thermal_controller(hwmgr);
	ret |= psm_set_perक्रमmance_states(hwmgr);
	अगर (ret)
		जाओ err2;

	((काष्ठा amdgpu_device *)hwmgr->adev)->pm.dpm_enabled = true;

	वापस 0;
err2:
	अगर (hwmgr->hwmgr_func->backend_fini)
		hwmgr->hwmgr_func->backend_fini(hwmgr);
err1:
	अगर (hwmgr->pptable_func->pptable_fini)
		hwmgr->pptable_func->pptable_fini(hwmgr);
err:
	वापस ret;
पूर्ण

पूर्णांक hwmgr_hw_fini(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (!hwmgr || !hwmgr->pm_en || !hwmgr->not_vf)
		वापस 0;

	phm_stop_thermal_controller(hwmgr);
	psm_set_boot_states(hwmgr);
	psm_adjust_घातer_state_dynamic(hwmgr, true, शून्य);
	phm_disable_dynamic_state_management(hwmgr);
	phm_disable_घड़ी_घातer_gatings(hwmgr);

	अगर (hwmgr->hwmgr_func->backend_fini)
		hwmgr->hwmgr_func->backend_fini(hwmgr);
	अगर (hwmgr->pptable_func->pptable_fini)
		hwmgr->pptable_func->pptable_fini(hwmgr);
	वापस psm_fini_घातer_state_table(hwmgr);
पूर्ण

पूर्णांक hwmgr_suspend(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en || !hwmgr->not_vf)
		वापस 0;

	phm_disable_smc_firmware_ctf(hwmgr);
	ret = psm_set_boot_states(hwmgr);
	अगर (ret)
		वापस ret;
	ret = psm_adjust_घातer_state_dynamic(hwmgr, true, शून्य);
	अगर (ret)
		वापस ret;
	ret = phm_घातer_करोwn_asic(hwmgr);

	वापस ret;
पूर्ण

पूर्णांक hwmgr_resume(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक ret = 0;

	अगर (!hwmgr)
		वापस -EINVAL;

	अगर (!hwmgr->not_vf || !hwmgr->pm_en)
		वापस 0;

	ret = phm_setup_asic(hwmgr);
	अगर (ret)
		वापस ret;

	ret = phm_enable_dynamic_state_management(hwmgr);
	अगर (ret)
		वापस ret;
	ret = phm_start_thermal_controller(hwmgr);
	ret |= psm_set_perक्रमmance_states(hwmgr);
	अगर (ret)
		वापस ret;

	ret = psm_adjust_घातer_state_dynamic(hwmgr, false, शून्य);

	वापस ret;
पूर्ण

अटल क्रमागत PP_StateUILabel घातer_state_convert(क्रमागत amd_pm_state_type  state)
अणु
	चयन (state) अणु
	हाल POWER_STATE_TYPE_BATTERY:
		वापस PP_StateUILabel_Battery;
	हाल POWER_STATE_TYPE_BALANCED:
		वापस PP_StateUILabel_Balanced;
	हाल POWER_STATE_TYPE_PERFORMANCE:
		वापस PP_StateUILabel_Perक्रमmance;
	शेष:
		वापस PP_StateUILabel_None;
	पूर्ण
पूर्ण

पूर्णांक hwmgr_handle_task(काष्ठा pp_hwmgr *hwmgr, क्रमागत amd_pp_task task_id,
		क्रमागत amd_pm_state_type *user_state)
अणु
	पूर्णांक ret = 0;

	अगर (hwmgr == शून्य)
		वापस -EINVAL;

	चयन (task_id) अणु
	हाल AMD_PP_TASK_DISPLAY_CONFIG_CHANGE:
		अगर (!hwmgr->not_vf)
			वापस ret;
		ret = phm_pre_display_configuration_changed(hwmgr);
		अगर (ret)
			वापस ret;
		ret = phm_set_cpu_घातer_state(hwmgr);
		अगर (ret)
			वापस ret;
		ret = psm_set_perक्रमmance_states(hwmgr);
		अगर (ret)
			वापस ret;
		ret = psm_adjust_घातer_state_dynamic(hwmgr, false, शून्य);
		अवरोध;
	हाल AMD_PP_TASK_ENABLE_USER_STATE:
	अणु
		क्रमागत PP_StateUILabel requested_ui_label;
		काष्ठा pp_घातer_state *requested_ps = शून्य;

		अगर (!hwmgr->not_vf)
			वापस ret;
		अगर (user_state == शून्य) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		requested_ui_label = घातer_state_convert(*user_state);
		ret = psm_set_user_perक्रमmance_state(hwmgr, requested_ui_label, &requested_ps);
		अगर (ret)
			वापस ret;
		ret = psm_adjust_घातer_state_dynamic(hwmgr, true, requested_ps);
		अवरोध;
	पूर्ण
	हाल AMD_PP_TASK_COMPLETE_INIT:
	हाल AMD_PP_TASK_READJUST_POWER_STATE:
		ret = psm_adjust_घातer_state_dynamic(hwmgr, true, शून्य);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

व्योम hwmgr_init_शेष_caps(काष्ठा pp_hwmgr *hwmgr)
अणु
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_PCIEPerक्रमmanceRequest);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_UVDDPM);
	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_VCEDPM);

#अगर defined(CONFIG_ACPI)
	अगर (amdgpu_acpi_is_pcie_perक्रमmance_request_supported(hwmgr->adev))
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_PCIEPerक्रमmanceRequest);
#पूर्ण_अगर

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
		PHM_Platक्रमmCaps_DynamicPatchPowerState);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
		PHM_Platक्रमmCaps_EnableSMU7ThermalManagement);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_DynamicPowerManagement);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_SMC);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_DynamicUVDState);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
						PHM_Platक्रमmCaps_FanSpeedInTableIsRPM);
	वापस;
पूर्ण

पूर्णांक hwmgr_set_user_specअगरy_caps(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (hwmgr->feature_mask & PP_SCLK_DEEP_SLEEP_MASK)
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_SclkDeepSleep);
	अन्यथा
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_SclkDeepSleep);

	अगर (hwmgr->feature_mask & PP_POWER_CONTAINMENT_MASK) अणु
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			    PHM_Platक्रमmCaps_PowerContainment);
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_CAC);
	पूर्ण अन्यथा अणु
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			    PHM_Platक्रमmCaps_PowerContainment);
		phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_CAC);
	पूर्ण

	अगर (hwmgr->feature_mask & PP_OVERDRIVE_MASK)
		hwmgr->od_enabled = true;

	वापस 0;
पूर्ण

पूर्णांक polaris_set_asic_special_caps(काष्ठा pp_hwmgr *hwmgr)
अणु
	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
						PHM_Platक्रमmCaps_EVV);
	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
						PHM_Platक्रमmCaps_SQRamping);
	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
						PHM_Platक्रमmCaps_RegulatorHot);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_MemorySpपढ़ोSpectrumSupport);
	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_EngineSpपढ़ोSpectrumSupport);

	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_AutomaticDCTransition);

	अगर (((hwmgr->chip_id == CHIP_POLARIS11) && !hwmgr->is_kicker) ||
	    (hwmgr->chip_id == CHIP_POLARIS12))
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
				PHM_Platक्रमmCaps_SPLLShutकरोwnSupport);

	अगर (hwmgr->chip_id != CHIP_POLARIS11) अणु
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
							PHM_Platक्रमmCaps_DBRamping);
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
							PHM_Platक्रमmCaps_TDRamping);
		phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
							PHM_Platक्रमmCaps_TCPRamping);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक fiji_set_asic_special_caps(काष्ठा pp_hwmgr *hwmgr)
अणु
	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
						PHM_Platक्रमmCaps_EVV);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_SQRamping);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_DBRamping);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_TDRamping);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_TCPRamping);
	वापस 0;
पूर्ण

पूर्णांक tonga_set_asic_special_caps(काष्ठा pp_hwmgr *hwmgr)
अणु
	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
						PHM_Platक्रमmCaps_EVV);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_SQRamping);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_DBRamping);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_TDRamping);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_TCPRamping);

	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
		      PHM_Platक्रमmCaps_UVDPowerGating);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
		      PHM_Platक्रमmCaps_VCEPowerGating);
	वापस 0;
पूर्ण

पूर्णांक topaz_set_asic_special_caps(काष्ठा pp_hwmgr *hwmgr)
अणु
	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
						PHM_Platक्रमmCaps_EVV);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_SQRamping);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_DBRamping);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_TDRamping);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_TCPRamping);
	वापस 0;
पूर्ण

पूर्णांक ci_set_asic_special_caps(काष्ठा pp_hwmgr *hwmgr)
अणु
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_SQRamping);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_DBRamping);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_TDRamping);
	phm_cap_unset(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_TCPRamping);
	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_MemorySpपढ़ोSpectrumSupport);
	phm_cap_set(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_EngineSpपढ़ोSpectrumSupport);
	वापस 0;
पूर्ण
