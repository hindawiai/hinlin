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
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/gfp.h>
#समावेश <linux/slab.h>
#समावेश <linux/firmware.h>
#समावेश "amd_shared.h"
#समावेश "amd_powerplay.h"
#समावेश "power_state.h"
#समावेश "amdgpu.h"
#समावेश "hwmgr.h"


अटल स्थिर काष्ठा amd_pm_funcs pp_dpm_funcs;

अटल पूर्णांक amd_घातerplay_create(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा pp_hwmgr *hwmgr;

	अगर (adev == शून्य)
		वापस -EINVAL;

	hwmgr = kzalloc(माप(काष्ठा pp_hwmgr), GFP_KERNEL);
	अगर (hwmgr == शून्य)
		वापस -ENOMEM;

	hwmgr->adev = adev;
	hwmgr->not_vf = !amdgpu_sriov_vf(adev);
	hwmgr->device = amdgpu_cgs_create_device(adev);
	mutex_init(&hwmgr->smu_lock);
	mutex_init(&hwmgr->msg_lock);
	hwmgr->chip_family = adev->family;
	hwmgr->chip_id = adev->asic_type;
	hwmgr->feature_mask = adev->pm.pp_feature;
	hwmgr->display_config = &adev->pm.pm_display_cfg;
	adev->घातerplay.pp_handle = hwmgr;
	adev->घातerplay.pp_funcs = &pp_dpm_funcs;
	वापस 0;
पूर्ण


अटल व्योम amd_घातerplay_destroy(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा pp_hwmgr *hwmgr = adev->घातerplay.pp_handle;

	mutex_destroy(&hwmgr->msg_lock);

	kमुक्त(hwmgr->hardcode_pp_table);
	hwmgr->hardcode_pp_table = शून्य;

	kमुक्त(hwmgr);
	hwmgr = शून्य;
पूर्ण

अटल पूर्णांक pp_early_init(व्योम *handle)
अणु
	पूर्णांक ret;
	काष्ठा amdgpu_device *adev = handle;

	ret = amd_घातerplay_create(adev);

	अगर (ret != 0)
		वापस ret;

	ret = hwmgr_early_init(adev->घातerplay.pp_handle);
	अगर (ret)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक pp_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = handle;
	काष्ठा pp_hwmgr *hwmgr = adev->घातerplay.pp_handle;
	पूर्णांक ret = 0;

	ret = hwmgr_sw_init(hwmgr);

	pr_debug("powerplay sw init %s\n", ret ? "failed" : "successfully");

	वापस ret;
पूर्ण

अटल पूर्णांक pp_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = handle;
	काष्ठा pp_hwmgr *hwmgr = adev->घातerplay.pp_handle;

	hwmgr_sw_fini(hwmgr);

	release_firmware(adev->pm.fw);
	adev->pm.fw = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक pp_hw_init(व्योम *handle)
अणु
	पूर्णांक ret = 0;
	काष्ठा amdgpu_device *adev = handle;
	काष्ठा pp_hwmgr *hwmgr = adev->घातerplay.pp_handle;

	ret = hwmgr_hw_init(hwmgr);

	अगर (ret)
		pr_err("powerplay hw init failed\n");

	वापस ret;
पूर्ण

अटल पूर्णांक pp_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = handle;
	काष्ठा pp_hwmgr *hwmgr = adev->घातerplay.pp_handle;

	hwmgr_hw_fini(hwmgr);

	वापस 0;
पूर्ण

अटल व्योम pp_reserve_vram_क्रम_smu(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक r = -EINVAL;
	व्योम *cpu_ptr = शून्य;
	uपूर्णांक64_t gpu_addr;
	काष्ठा pp_hwmgr *hwmgr = adev->घातerplay.pp_handle;

	अगर (amdgpu_bo_create_kernel(adev, adev->pm.smu_prv_buffer_size,
						PAGE_SIZE, AMDGPU_GEM_DOMAIN_GTT,
						&adev->pm.smu_prv_buffer,
						&gpu_addr,
						&cpu_ptr)) अणु
		DRM_ERROR("amdgpu: failed to create smu prv buffer\n");
		वापस;
	पूर्ण

	अगर (hwmgr->hwmgr_func->notअगरy_cac_buffer_info)
		r = hwmgr->hwmgr_func->notअगरy_cac_buffer_info(hwmgr,
					lower_32_bits((अचिन्हित दीर्घ)cpu_ptr),
					upper_32_bits((अचिन्हित दीर्घ)cpu_ptr),
					lower_32_bits(gpu_addr),
					upper_32_bits(gpu_addr),
					adev->pm.smu_prv_buffer_size);

	अगर (r) अणु
		amdgpu_bo_मुक्त_kernel(&adev->pm.smu_prv_buffer, शून्य, शून्य);
		adev->pm.smu_prv_buffer = शून्य;
		DRM_ERROR("amdgpu: failed to notify SMU buffer address\n");
	पूर्ण
पूर्ण

अटल पूर्णांक pp_late_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = handle;
	काष्ठा pp_hwmgr *hwmgr = adev->घातerplay.pp_handle;

	अगर (hwmgr && hwmgr->pm_en) अणु
		mutex_lock(&hwmgr->smu_lock);
		hwmgr_handle_task(hwmgr,
					AMD_PP_TASK_COMPLETE_INIT, शून्य);
		mutex_unlock(&hwmgr->smu_lock);
	पूर्ण
	अगर (adev->pm.smu_prv_buffer_size != 0)
		pp_reserve_vram_क्रम_smu(adev);

	वापस 0;
पूर्ण

अटल व्योम pp_late_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = handle;

	अगर (adev->pm.smu_prv_buffer)
		amdgpu_bo_मुक्त_kernel(&adev->pm.smu_prv_buffer, शून्य, शून्य);
	amd_घातerplay_destroy(adev);
पूर्ण


अटल bool pp_is_idle(व्योम *handle)
अणु
	वापस false;
पूर्ण

अटल पूर्णांक pp_रुको_क्रम_idle(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक pp_sw_reset(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक pp_set_घातergating_state(व्योम *handle,
				    क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक pp_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = handle;
	काष्ठा pp_hwmgr *hwmgr = adev->घातerplay.pp_handle;

	वापस hwmgr_suspend(hwmgr);
पूर्ण

अटल पूर्णांक pp_resume(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = handle;
	काष्ठा pp_hwmgr *hwmgr = adev->घातerplay.pp_handle;

	वापस hwmgr_resume(hwmgr);
पूर्ण

अटल पूर्णांक pp_set_घड़ीgating_state(व्योम *handle,
					  क्रमागत amd_घड़ीgating_state state)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amd_ip_funcs pp_ip_funcs = अणु
	.name = "powerplay",
	.early_init = pp_early_init,
	.late_init = pp_late_init,
	.sw_init = pp_sw_init,
	.sw_fini = pp_sw_fini,
	.hw_init = pp_hw_init,
	.hw_fini = pp_hw_fini,
	.late_fini = pp_late_fini,
	.suspend = pp_suspend,
	.resume = pp_resume,
	.is_idle = pp_is_idle,
	.रुको_क्रम_idle = pp_रुको_क्रम_idle,
	.soft_reset = pp_sw_reset,
	.set_घड़ीgating_state = pp_set_घड़ीgating_state,
	.set_घातergating_state = pp_set_घातergating_state,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version pp_smu_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_SMC,
	.major = 1,
	.minor = 0,
	.rev = 0,
	.funcs = &pp_ip_funcs,
पूर्ण;

/* This पूर्णांकerface only be supported On Vi,
 * because only smu7/8 can help to load gfx/sdma fw,
 * smu need to be enabled beक्रमe load other ip's fw.
 * so call start smu to load smu7 fw and other ip's fw
 */
अटल पूर्णांक pp_dpm_load_fw(व्योम *handle)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr || !hwmgr->smumgr_funcs || !hwmgr->smumgr_funcs->start_smu)
		वापस -EINVAL;

	अगर (hwmgr->smumgr_funcs->start_smu(hwmgr)) अणु
		pr_err("fw load failed\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pp_dpm_fw_loading_complete(व्योम *handle)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक pp_set_घड़ीgating_by_smu(व्योम *handle, uपूर्णांक32_t msg_id)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->update_घड़ी_gatings == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस 0;
	पूर्ण

	वापस hwmgr->hwmgr_func->update_घड़ी_gatings(hwmgr, &msg_id);
पूर्ण

अटल व्योम pp_dpm_en_umd_pstate(काष्ठा pp_hwmgr  *hwmgr,
						क्रमागत amd_dpm_क्रमced_level *level)
अणु
	uपूर्णांक32_t profile_mode_mask = AMD_DPM_FORCED_LEVEL_PROखाता_STANDARD |
					AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK |
					AMD_DPM_FORCED_LEVEL_PROखाता_MIN_MCLK |
					AMD_DPM_FORCED_LEVEL_PROखाता_PEAK;

	अगर (!(hwmgr->dpm_level & profile_mode_mask)) अणु
		/* enter umd pstate, save current level, disable gfx cg*/
		अगर (*level & profile_mode_mask) अणु
			hwmgr->saved_dpm_level = hwmgr->dpm_level;
			hwmgr->en_umd_pstate = true;
			amdgpu_device_ip_set_घातergating_state(hwmgr->adev,
					AMD_IP_BLOCK_TYPE_GFX,
					AMD_PG_STATE_UNGATE);
			amdgpu_device_ip_set_घड़ीgating_state(hwmgr->adev,
						AMD_IP_BLOCK_TYPE_GFX,
						AMD_CG_STATE_UNGATE);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* निकास umd pstate, restore level, enable gfx cg*/
		अगर (!(*level & profile_mode_mask)) अणु
			अगर (*level == AMD_DPM_FORCED_LEVEL_PROखाता_EXIT)
				*level = hwmgr->saved_dpm_level;
			hwmgr->en_umd_pstate = false;
			amdgpu_device_ip_set_घड़ीgating_state(hwmgr->adev,
					AMD_IP_BLOCK_TYPE_GFX,
					AMD_CG_STATE_GATE);
			amdgpu_device_ip_set_घातergating_state(hwmgr->adev,
					AMD_IP_BLOCK_TYPE_GFX,
					AMD_PG_STATE_GATE);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक pp_dpm_क्रमce_perक्रमmance_level(व्योम *handle,
					क्रमागत amd_dpm_क्रमced_level level)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (level == hwmgr->dpm_level)
		वापस 0;

	mutex_lock(&hwmgr->smu_lock);
	pp_dpm_en_umd_pstate(hwmgr, &level);
	hwmgr->request_dpm_level = level;
	hwmgr_handle_task(hwmgr, AMD_PP_TASK_READJUST_POWER_STATE, शून्य);
	mutex_unlock(&hwmgr->smu_lock);

	वापस 0;
पूर्ण

अटल क्रमागत amd_dpm_क्रमced_level pp_dpm_get_perक्रमmance_level(
								व्योम *handle)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	क्रमागत amd_dpm_क्रमced_level level;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	level = hwmgr->dpm_level;
	mutex_unlock(&hwmgr->smu_lock);
	वापस level;
पूर्ण

अटल uपूर्णांक32_t pp_dpm_get_sclk(व्योम *handle, bool low)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	uपूर्णांक32_t clk = 0;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस 0;

	अगर (hwmgr->hwmgr_func->get_sclk == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस 0;
	पूर्ण
	mutex_lock(&hwmgr->smu_lock);
	clk = hwmgr->hwmgr_func->get_sclk(hwmgr, low);
	mutex_unlock(&hwmgr->smu_lock);
	वापस clk;
पूर्ण

अटल uपूर्णांक32_t pp_dpm_get_mclk(व्योम *handle, bool low)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	uपूर्णांक32_t clk = 0;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस 0;

	अगर (hwmgr->hwmgr_func->get_mclk == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस 0;
	पूर्ण
	mutex_lock(&hwmgr->smu_lock);
	clk = hwmgr->hwmgr_func->get_mclk(hwmgr, low);
	mutex_unlock(&hwmgr->smu_lock);
	वापस clk;
पूर्ण

अटल व्योम pp_dpm_घातergate_vce(व्योम *handle, bool gate)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस;

	अगर (hwmgr->hwmgr_func->घातergate_vce == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस;
	पूर्ण
	mutex_lock(&hwmgr->smu_lock);
	hwmgr->hwmgr_func->घातergate_vce(hwmgr, gate);
	mutex_unlock(&hwmgr->smu_lock);
पूर्ण

अटल व्योम pp_dpm_घातergate_uvd(व्योम *handle, bool gate)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस;

	अगर (hwmgr->hwmgr_func->घातergate_uvd == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस;
	पूर्ण
	mutex_lock(&hwmgr->smu_lock);
	hwmgr->hwmgr_func->घातergate_uvd(hwmgr, gate);
	mutex_unlock(&hwmgr->smu_lock);
पूर्ण

अटल पूर्णांक pp_dpm_dispatch_tasks(व्योम *handle, क्रमागत amd_pp_task task_id,
		क्रमागत amd_pm_state_type *user_state)
अणु
	पूर्णांक ret = 0;
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr_handle_task(hwmgr, task_id, user_state);
	mutex_unlock(&hwmgr->smu_lock);

	वापस ret;
पूर्ण

अटल क्रमागत amd_pm_state_type pp_dpm_get_current_घातer_state(व्योम *handle)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	काष्ठा pp_घातer_state *state;
	क्रमागत amd_pm_state_type pm_type;

	अगर (!hwmgr || !hwmgr->pm_en || !hwmgr->current_ps)
		वापस -EINVAL;

	mutex_lock(&hwmgr->smu_lock);

	state = hwmgr->current_ps;

	चयन (state->classअगरication.ui_label) अणु
	हाल PP_StateUILabel_Battery:
		pm_type = POWER_STATE_TYPE_BATTERY;
		अवरोध;
	हाल PP_StateUILabel_Balanced:
		pm_type = POWER_STATE_TYPE_BALANCED;
		अवरोध;
	हाल PP_StateUILabel_Perक्रमmance:
		pm_type = POWER_STATE_TYPE_PERFORMANCE;
		अवरोध;
	शेष:
		अगर (state->classअगरication.flags & PP_StateClassअगरicationFlag_Boot)
			pm_type = POWER_STATE_TYPE_INTERNAL_BOOT;
		अन्यथा
			pm_type = POWER_STATE_TYPE_DEFAULT;
		अवरोध;
	पूर्ण
	mutex_unlock(&hwmgr->smu_lock);

	वापस pm_type;
पूर्ण

अटल व्योम pp_dpm_set_fan_control_mode(व्योम *handle, uपूर्णांक32_t mode)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस;

	अगर (hwmgr->hwmgr_func->set_fan_control_mode == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस;
	पूर्ण
	mutex_lock(&hwmgr->smu_lock);
	hwmgr->hwmgr_func->set_fan_control_mode(hwmgr, mode);
	mutex_unlock(&hwmgr->smu_lock);
पूर्ण

अटल uपूर्णांक32_t pp_dpm_get_fan_control_mode(व्योम *handle)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	uपूर्णांक32_t mode = 0;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस 0;

	अगर (hwmgr->hwmgr_func->get_fan_control_mode == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस 0;
	पूर्ण
	mutex_lock(&hwmgr->smu_lock);
	mode = hwmgr->hwmgr_func->get_fan_control_mode(hwmgr);
	mutex_unlock(&hwmgr->smu_lock);
	वापस mode;
पूर्ण

अटल पूर्णांक pp_dpm_set_fan_speed_percent(व्योम *handle, uपूर्णांक32_t percent)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->set_fan_speed_percent == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस 0;
	पूर्ण
	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->set_fan_speed_percent(hwmgr, percent);
	mutex_unlock(&hwmgr->smu_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pp_dpm_get_fan_speed_percent(व्योम *handle, uपूर्णांक32_t *speed)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->get_fan_speed_percent == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस 0;
	पूर्ण

	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->get_fan_speed_percent(hwmgr, speed);
	mutex_unlock(&hwmgr->smu_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pp_dpm_get_fan_speed_rpm(व्योम *handle, uपूर्णांक32_t *rpm)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->get_fan_speed_rpm == शून्य)
		वापस -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->get_fan_speed_rpm(hwmgr, rpm);
	mutex_unlock(&hwmgr->smu_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pp_dpm_set_fan_speed_rpm(व्योम *handle, uपूर्णांक32_t rpm)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->set_fan_speed_rpm == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस 0;
	पूर्ण
	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->set_fan_speed_rpm(hwmgr, rpm);
	mutex_unlock(&hwmgr->smu_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pp_dpm_get_pp_num_states(व्योम *handle,
		काष्ठा pp_states_info *data)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक i;

	स_रखो(data, 0, माप(*data));

	अगर (!hwmgr || !hwmgr->pm_en ||!hwmgr->ps)
		वापस -EINVAL;

	mutex_lock(&hwmgr->smu_lock);

	data->nums = hwmgr->num_ps;

	क्रम (i = 0; i < hwmgr->num_ps; i++) अणु
		काष्ठा pp_घातer_state *state = (काष्ठा pp_घातer_state *)
				((अचिन्हित दीर्घ)hwmgr->ps + i * hwmgr->ps_size);
		चयन (state->classअगरication.ui_label) अणु
		हाल PP_StateUILabel_Battery:
			data->states[i] = POWER_STATE_TYPE_BATTERY;
			अवरोध;
		हाल PP_StateUILabel_Balanced:
			data->states[i] = POWER_STATE_TYPE_BALANCED;
			अवरोध;
		हाल PP_StateUILabel_Perक्रमmance:
			data->states[i] = POWER_STATE_TYPE_PERFORMANCE;
			अवरोध;
		शेष:
			अगर (state->classअगरication.flags & PP_StateClassअगरicationFlag_Boot)
				data->states[i] = POWER_STATE_TYPE_INTERNAL_BOOT;
			अन्यथा
				data->states[i] = POWER_STATE_TYPE_DEFAULT;
		पूर्ण
	पूर्ण
	mutex_unlock(&hwmgr->smu_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक pp_dpm_get_pp_table(व्योम *handle, अक्षर **table)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक size = 0;

	अगर (!hwmgr || !hwmgr->pm_en ||!hwmgr->soft_pp_table)
		वापस -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	*table = (अक्षर *)hwmgr->soft_pp_table;
	size = hwmgr->soft_pp_table_size;
	mutex_unlock(&hwmgr->smu_lock);
	वापस size;
पूर्ण

अटल पूर्णांक amd_घातerplay_reset(व्योम *handle)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret;

	ret = hwmgr_hw_fini(hwmgr);
	अगर (ret)
		वापस ret;

	ret = hwmgr_hw_init(hwmgr);
	अगर (ret)
		वापस ret;

	वापस hwmgr_handle_task(hwmgr, AMD_PP_TASK_COMPLETE_INIT, शून्य);
पूर्ण

अटल पूर्णांक pp_dpm_set_pp_table(व्योम *handle, स्थिर अक्षर *buf, माप_प्रकार size)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = -ENOMEM;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	अगर (!hwmgr->hardcode_pp_table) अणु
		hwmgr->hardcode_pp_table = kmemdup(hwmgr->soft_pp_table,
						   hwmgr->soft_pp_table_size,
						   GFP_KERNEL);
		अगर (!hwmgr->hardcode_pp_table)
			जाओ err;
	पूर्ण

	स_नकल(hwmgr->hardcode_pp_table, buf, size);

	hwmgr->soft_pp_table = hwmgr->hardcode_pp_table;

	ret = amd_घातerplay_reset(handle);
	अगर (ret)
		जाओ err;

	अगर (hwmgr->hwmgr_func->avfs_control) अणु
		ret = hwmgr->hwmgr_func->avfs_control(hwmgr, false);
		अगर (ret)
			जाओ err;
	पूर्ण
	mutex_unlock(&hwmgr->smu_lock);
	वापस 0;
err:
	mutex_unlock(&hwmgr->smu_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pp_dpm_क्रमce_घड़ी_level(व्योम *handle,
		क्रमागत pp_घड़ी_प्रकारype type, uपूर्णांक32_t mask)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->क्रमce_घड़ी_level == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस 0;
	पूर्ण

	अगर (hwmgr->dpm_level != AMD_DPM_FORCED_LEVEL_MANUAL) अणु
		pr_debug("force clock level is for dpm manual mode only.\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->क्रमce_घड़ी_level(hwmgr, type, mask);
	mutex_unlock(&hwmgr->smu_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pp_dpm_prपूर्णांक_घड़ी_levels(व्योम *handle,
		क्रमागत pp_घड़ी_प्रकारype type, अक्षर *buf)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->prपूर्णांक_घड़ी_levels == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस 0;
	पूर्ण
	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->prपूर्णांक_घड़ी_levels(hwmgr, type, buf);
	mutex_unlock(&hwmgr->smu_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pp_dpm_get_sclk_od(व्योम *handle)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->get_sclk_od == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस 0;
	पूर्ण
	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->get_sclk_od(hwmgr);
	mutex_unlock(&hwmgr->smu_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pp_dpm_set_sclk_od(व्योम *handle, uपूर्णांक32_t value)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->set_sclk_od == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस 0;
	पूर्ण

	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->set_sclk_od(hwmgr, value);
	mutex_unlock(&hwmgr->smu_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pp_dpm_get_mclk_od(व्योम *handle)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->get_mclk_od == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस 0;
	पूर्ण
	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->get_mclk_od(hwmgr);
	mutex_unlock(&hwmgr->smu_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pp_dpm_set_mclk_od(व्योम *handle, uपूर्णांक32_t value)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->set_mclk_od == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस 0;
	पूर्ण
	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->set_mclk_od(hwmgr, value);
	mutex_unlock(&hwmgr->smu_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pp_dpm_पढ़ो_sensor(व्योम *handle, पूर्णांक idx,
			      व्योम *value, पूर्णांक *size)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en || !value)
		वापस -EINVAL;

	चयन (idx) अणु
	हाल AMDGPU_PP_SENSOR_STABLE_PSTATE_SCLK:
		*((uपूर्णांक32_t *)value) = hwmgr->pstate_sclk;
		वापस 0;
	हाल AMDGPU_PP_SENSOR_STABLE_PSTATE_MCLK:
		*((uपूर्णांक32_t *)value) = hwmgr->pstate_mclk;
		वापस 0;
	हाल AMDGPU_PP_SENSOR_MIN_FAN_RPM:
		*((uपूर्णांक32_t *)value) = hwmgr->thermal_controller.fanInfo.ulMinRPM;
		वापस 0;
	हाल AMDGPU_PP_SENSOR_MAX_FAN_RPM:
		*((uपूर्णांक32_t *)value) = hwmgr->thermal_controller.fanInfo.ulMaxRPM;
		वापस 0;
	शेष:
		mutex_lock(&hwmgr->smu_lock);
		ret = hwmgr->hwmgr_func->पढ़ो_sensor(hwmgr, idx, value, size);
		mutex_unlock(&hwmgr->smu_lock);
		वापस ret;
	पूर्ण
पूर्ण

अटल काष्ठा amd_vce_state*
pp_dpm_get_vce_घड़ी_state(व्योम *handle, अचिन्हित idx)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस शून्य;

	अगर (idx < hwmgr->num_vce_state_tables)
		वापस &hwmgr->vce_states[idx];
	वापस शून्य;
पूर्ण

अटल पूर्णांक pp_get_घातer_profile_mode(व्योम *handle, अक्षर *buf)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr || !hwmgr->pm_en || !buf)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->get_घातer_profile_mode == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस snम_लिखो(buf, PAGE_SIZE, "\n");
	पूर्ण

	वापस hwmgr->hwmgr_func->get_घातer_profile_mode(hwmgr, buf);
पूर्ण

अटल पूर्णांक pp_set_घातer_profile_mode(व्योम *handle, दीर्घ *input, uपूर्णांक32_t size)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = -EINVAL;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस ret;

	अगर (hwmgr->hwmgr_func->set_घातer_profile_mode == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस ret;
	पूर्ण

	अगर (hwmgr->dpm_level != AMD_DPM_FORCED_LEVEL_MANUAL) अणु
		pr_debug("power profile setting is for manual dpm mode only.\n");
		वापस ret;
	पूर्ण

	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->set_घातer_profile_mode(hwmgr, input, size);
	mutex_unlock(&hwmgr->smu_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pp_set_fine_grain_clk_vol(व्योम *handle, uपूर्णांक32_t type, दीर्घ *input, uपूर्णांक32_t size)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->set_fine_grain_clk_vol == शून्य)
		वापस 0;

	वापस hwmgr->hwmgr_func->set_fine_grain_clk_vol(hwmgr, type, input, size);
पूर्ण

अटल पूर्णांक pp_odn_edit_dpm_table(व्योम *handle, uपूर्णांक32_t type, दीर्घ *input, uपूर्णांक32_t size)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->odn_edit_dpm_table == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस 0;
	पूर्ण

	वापस hwmgr->hwmgr_func->odn_edit_dpm_table(hwmgr, type, input, size);
पूर्ण

अटल पूर्णांक pp_dpm_set_mp1_state(व्योम *handle, क्रमागत pp_mp1_state mp1_state)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr)
		वापस -EINVAL;

	अगर (!hwmgr->pm_en)
		वापस 0;

	अगर (hwmgr->hwmgr_func->set_mp1_state)
		वापस hwmgr->hwmgr_func->set_mp1_state(hwmgr, mp1_state);

	वापस 0;
पूर्ण

अटल पूर्णांक pp_dpm_चयन_घातer_profile(व्योम *handle,
		क्रमागत PP_SMC_POWER_PROखाता type, bool en)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	दीर्घ workload;
	uपूर्णांक32_t index;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->set_घातer_profile_mode == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (!(type < PP_SMC_POWER_PROखाता_CUSTOM))
		वापस -EINVAL;

	mutex_lock(&hwmgr->smu_lock);

	अगर (!en) अणु
		hwmgr->workload_mask &= ~(1 << hwmgr->workload_prority[type]);
		index = fls(hwmgr->workload_mask);
		index = index > 0 && index <= Workload_Policy_Max ? index - 1 : 0;
		workload = hwmgr->workload_setting[index];
	पूर्ण अन्यथा अणु
		hwmgr->workload_mask |= (1 << hwmgr->workload_prority[type]);
		index = fls(hwmgr->workload_mask);
		index = index <= Workload_Policy_Max ? index - 1 : 0;
		workload = hwmgr->workload_setting[index];
	पूर्ण

	अगर (type == PP_SMC_POWER_PROखाता_COMPUTE &&
		hwmgr->hwmgr_func->disable_घातer_features_क्रम_compute_perक्रमmance) अणु
			अगर (hwmgr->hwmgr_func->disable_घातer_features_क्रम_compute_perक्रमmance(hwmgr, en)) अणु
				mutex_unlock(&hwmgr->smu_lock);
				वापस -EINVAL;
			पूर्ण
	पूर्ण

	अगर (hwmgr->dpm_level != AMD_DPM_FORCED_LEVEL_MANUAL)
		hwmgr->hwmgr_func->set_घातer_profile_mode(hwmgr, &workload, 0);
	mutex_unlock(&hwmgr->smu_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक pp_set_घातer_limit(व्योम *handle, uपूर्णांक32_t limit)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	uपूर्णांक32_t max_घातer_limit;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->set_घातer_limit == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (limit == 0)
		limit = hwmgr->शेष_घातer_limit;

	max_घातer_limit = hwmgr->शेष_घातer_limit;
	अगर (hwmgr->od_enabled) अणु
		max_घातer_limit *= (100 + hwmgr->platक्रमm_descriptor.TDPODLimit);
		max_घातer_limit /= 100;
	पूर्ण

	अगर (limit > max_घातer_limit)
		वापस -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	hwmgr->hwmgr_func->set_घातer_limit(hwmgr, limit);
	hwmgr->घातer_limit = limit;
	mutex_unlock(&hwmgr->smu_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक pp_get_घातer_limit(व्योम *handle, uपूर्णांक32_t *limit,
		uपूर्णांक32_t *max_limit, bool शेष_limit)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr || !hwmgr->pm_en ||!limit)
		वापस -EINVAL;

	mutex_lock(&hwmgr->smu_lock);

	अगर (शेष_limit) अणु
		*limit = hwmgr->शेष_घातer_limit;
		अगर (max_limit) अणु
			*max_limit = *limit;
			अगर (hwmgr->od_enabled) अणु
				*max_limit *= (100 + hwmgr->platक्रमm_descriptor.TDPODLimit);
				*max_limit /= 100;
			पूर्ण
		पूर्ण
	पूर्ण
	अन्यथा
		*limit = hwmgr->घातer_limit;

	mutex_unlock(&hwmgr->smu_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक pp_display_configuration_change(व्योम *handle,
	स्थिर काष्ठा amd_pp_display_configuration *display_config)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	phm_store_dal_configuration_data(hwmgr, display_config);
	mutex_unlock(&hwmgr->smu_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक pp_get_display_घातer_level(व्योम *handle,
		काष्ठा amd_pp_simple_घड़ी_info *output)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en ||!output)
		वापस -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	ret = phm_get_dal_घातer_level(hwmgr, output);
	mutex_unlock(&hwmgr->smu_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pp_get_current_घड़ीs(व्योम *handle,
		काष्ठा amd_pp_घड़ी_info *घड़ीs)
अणु
	काष्ठा amd_pp_simple_घड़ी_info simple_घड़ीs = अणु 0 पूर्ण;
	काष्ठा pp_घड़ी_info hw_घड़ीs;
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	mutex_lock(&hwmgr->smu_lock);

	phm_get_dal_घातer_level(hwmgr, &simple_घड़ीs);

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
					PHM_Platक्रमmCaps_PowerContainment))
		ret = phm_get_घड़ी_info(hwmgr, &hwmgr->current_ps->hardware,
					&hw_घड़ीs, PHM_Perक्रमmanceLevelDesignation_PowerContainment);
	अन्यथा
		ret = phm_get_घड़ी_info(hwmgr, &hwmgr->current_ps->hardware,
					&hw_घड़ीs, PHM_Perक्रमmanceLevelDesignation_Activity);

	अगर (ret) अणु
		pr_debug("Error in phm_get_clock_info \n");
		mutex_unlock(&hwmgr->smu_lock);
		वापस -EINVAL;
	पूर्ण

	घड़ीs->min_engine_घड़ी = hw_घड़ीs.min_eng_clk;
	घड़ीs->max_engine_घड़ी = hw_घड़ीs.max_eng_clk;
	घड़ीs->min_memory_घड़ी = hw_घड़ीs.min_mem_clk;
	घड़ीs->max_memory_घड़ी = hw_घड़ीs.max_mem_clk;
	घड़ीs->min_bus_bandwidth = hw_घड़ीs.min_bus_bandwidth;
	घड़ीs->max_bus_bandwidth = hw_घड़ीs.max_bus_bandwidth;

	घड़ीs->max_engine_घड़ी_in_sr = hw_घड़ीs.max_eng_clk;
	घड़ीs->min_engine_घड़ी_in_sr = hw_घड़ीs.min_eng_clk;

	अगर (simple_घड़ीs.level == 0)
		घड़ीs->max_घड़ीs_state = PP_DAL_POWERLEVEL_7;
	अन्यथा
		घड़ीs->max_घड़ीs_state = simple_घड़ीs.level;

	अगर (0 == phm_get_current_shallow_sleep_घड़ीs(hwmgr, &hwmgr->current_ps->hardware, &hw_घड़ीs)) अणु
		घड़ीs->max_engine_घड़ी_in_sr = hw_घड़ीs.max_eng_clk;
		घड़ीs->min_engine_घड़ी_in_sr = hw_घड़ीs.min_eng_clk;
	पूर्ण
	mutex_unlock(&hwmgr->smu_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक pp_get_घड़ी_by_type(व्योम *handle, क्रमागत amd_pp_घड़ी_प्रकारype type, काष्ठा amd_pp_घड़ीs *घड़ीs)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (घड़ीs == शून्य)
		वापस -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	ret = phm_get_घड़ी_by_type(hwmgr, type, घड़ीs);
	mutex_unlock(&hwmgr->smu_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pp_get_घड़ी_by_type_with_latency(व्योम *handle,
		क्रमागत amd_pp_घड़ी_प्रकारype type,
		काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en ||!घड़ीs)
		वापस -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	ret = phm_get_घड़ी_by_type_with_latency(hwmgr, type, घड़ीs);
	mutex_unlock(&hwmgr->smu_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pp_get_घड़ी_by_type_with_voltage(व्योम *handle,
		क्रमागत amd_pp_घड़ी_प्रकारype type,
		काष्ठा pp_घड़ी_levels_with_voltage *घड़ीs)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en ||!घड़ीs)
		वापस -EINVAL;

	mutex_lock(&hwmgr->smu_lock);

	ret = phm_get_घड़ी_by_type_with_voltage(hwmgr, type, घड़ीs);

	mutex_unlock(&hwmgr->smu_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pp_set_watermarks_क्रम_घड़ीs_ranges(व्योम *handle,
		व्योम *घड़ी_ranges)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en || !घड़ी_ranges)
		वापस -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	ret = phm_set_watermarks_क्रम_घड़ीs_ranges(hwmgr,
			घड़ी_ranges);
	mutex_unlock(&hwmgr->smu_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक pp_display_घड़ी_voltage_request(व्योम *handle,
		काष्ठा pp_display_घड़ी_request *घड़ी)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en ||!घड़ी)
		वापस -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	ret = phm_display_घड़ी_voltage_request(hwmgr, घड़ी);
	mutex_unlock(&hwmgr->smu_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक pp_get_display_mode_validation_घड़ीs(व्योम *handle,
		काष्ठा amd_pp_simple_घड़ी_info *घड़ीs)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en ||!घड़ीs)
		वापस -EINVAL;

	घड़ीs->level = PP_DAL_POWERLEVEL_7;

	mutex_lock(&hwmgr->smu_lock);

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps, PHM_Platक्रमmCaps_DynamicPatchPowerState))
		ret = phm_get_max_high_घड़ीs(hwmgr, घड़ीs);

	mutex_unlock(&hwmgr->smu_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक pp_dpm_घातergate_mmhub(व्योम *handle)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->घातergate_mmhub == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस 0;
	पूर्ण

	वापस hwmgr->hwmgr_func->घातergate_mmhub(hwmgr);
पूर्ण

अटल पूर्णांक pp_dpm_घातergate_gfx(व्योम *handle, bool gate)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस 0;

	अगर (hwmgr->hwmgr_func->घातergate_gfx == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस 0;
	पूर्ण

	वापस hwmgr->hwmgr_func->घातergate_gfx(hwmgr, gate);
पूर्ण

अटल व्योम pp_dpm_घातergate_acp(व्योम *handle, bool gate)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस;

	अगर (hwmgr->hwmgr_func->घातergate_acp == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस;
	पूर्ण

	hwmgr->hwmgr_func->घातergate_acp(hwmgr, gate);
पूर्ण

अटल व्योम pp_dpm_घातergate_sdma(व्योम *handle, bool gate)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr)
		वापस;

	अगर (hwmgr->hwmgr_func->घातergate_sdma == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस;
	पूर्ण

	hwmgr->hwmgr_func->घातergate_sdma(hwmgr, gate);
पूर्ण

अटल पूर्णांक pp_set_घातergating_by_smu(व्योम *handle,
				uपूर्णांक32_t block_type, bool gate)
अणु
	पूर्णांक ret = 0;

	चयन (block_type) अणु
	हाल AMD_IP_BLOCK_TYPE_UVD:
	हाल AMD_IP_BLOCK_TYPE_VCN:
		pp_dpm_घातergate_uvd(handle, gate);
		अवरोध;
	हाल AMD_IP_BLOCK_TYPE_VCE:
		pp_dpm_घातergate_vce(handle, gate);
		अवरोध;
	हाल AMD_IP_BLOCK_TYPE_GMC:
		pp_dpm_घातergate_mmhub(handle);
		अवरोध;
	हाल AMD_IP_BLOCK_TYPE_GFX:
		ret = pp_dpm_घातergate_gfx(handle, gate);
		अवरोध;
	हाल AMD_IP_BLOCK_TYPE_ACP:
		pp_dpm_घातergate_acp(handle, gate);
		अवरोध;
	हाल AMD_IP_BLOCK_TYPE_SDMA:
		pp_dpm_घातergate_sdma(handle, gate);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक pp_notअगरy_smu_enable_pwe(व्योम *handle)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->smus_notअगरy_pwe == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&hwmgr->smu_lock);
	hwmgr->hwmgr_func->smus_notअगरy_pwe(hwmgr);
	mutex_unlock(&hwmgr->smu_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक pp_enable_mgpu_fan_boost(व्योम *handle)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr)
		वापस -EINVAL;

	अगर (!hwmgr->pm_en ||
	     hwmgr->hwmgr_func->enable_mgpu_fan_boost == शून्य)
		वापस 0;

	mutex_lock(&hwmgr->smu_lock);
	hwmgr->hwmgr_func->enable_mgpu_fan_boost(hwmgr);
	mutex_unlock(&hwmgr->smu_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक pp_set_min_deep_sleep_dcefclk(व्योम *handle, uपूर्णांक32_t घड़ी)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->set_min_deep_sleep_dcefclk == शून्य) अणु
		pr_debug("%s was not implemented.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&hwmgr->smu_lock);
	hwmgr->hwmgr_func->set_min_deep_sleep_dcefclk(hwmgr, घड़ी);
	mutex_unlock(&hwmgr->smu_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक pp_set_hard_min_dcefclk_by_freq(व्योम *handle, uपूर्णांक32_t घड़ी)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->set_hard_min_dcefclk_by_freq == शून्य) अणु
		pr_debug("%s was not implemented.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&hwmgr->smu_lock);
	hwmgr->hwmgr_func->set_hard_min_dcefclk_by_freq(hwmgr, घड़ी);
	mutex_unlock(&hwmgr->smu_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक pp_set_hard_min_fclk_by_freq(व्योम *handle, uपूर्णांक32_t घड़ी)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->set_hard_min_fclk_by_freq == शून्य) अणु
		pr_debug("%s was not implemented.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&hwmgr->smu_lock);
	hwmgr->hwmgr_func->set_hard_min_fclk_by_freq(hwmgr, घड़ी);
	mutex_unlock(&hwmgr->smu_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक pp_set_active_display_count(व्योम *handle, uपूर्णांक32_t count)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	mutex_lock(&hwmgr->smu_lock);
	ret = phm_set_active_display_count(hwmgr, count);
	mutex_unlock(&hwmgr->smu_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक pp_get_asic_baco_capability(व्योम *handle, bool *cap)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	*cap = false;
	अगर (!hwmgr)
		वापस -EINVAL;

	अगर (!(hwmgr->not_vf && amdgpu_dpm) ||
		!hwmgr->hwmgr_func->get_asic_baco_capability)
		वापस 0;

	mutex_lock(&hwmgr->smu_lock);
	hwmgr->hwmgr_func->get_asic_baco_capability(hwmgr, cap);
	mutex_unlock(&hwmgr->smu_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक pp_get_asic_baco_state(व्योम *handle, पूर्णांक *state)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr)
		वापस -EINVAL;

	अगर (!hwmgr->pm_en || !hwmgr->hwmgr_func->get_asic_baco_state)
		वापस 0;

	mutex_lock(&hwmgr->smu_lock);
	hwmgr->hwmgr_func->get_asic_baco_state(hwmgr, (क्रमागत BACO_STATE *)state);
	mutex_unlock(&hwmgr->smu_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक pp_set_asic_baco_state(व्योम *handle, पूर्णांक state)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr)
		वापस -EINVAL;

	अगर (!(hwmgr->not_vf && amdgpu_dpm) ||
		!hwmgr->hwmgr_func->set_asic_baco_state)
		वापस 0;

	mutex_lock(&hwmgr->smu_lock);
	hwmgr->hwmgr_func->set_asic_baco_state(hwmgr, (क्रमागत BACO_STATE)state);
	mutex_unlock(&hwmgr->smu_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक pp_get_ppfeature_status(व्योम *handle, अक्षर *buf)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en || !buf)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->get_ppfeature_status == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->get_ppfeature_status(hwmgr, buf);
	mutex_unlock(&hwmgr->smu_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक pp_set_ppfeature_status(व्योम *handle, uपूर्णांक64_t ppfeature_masks)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->set_ppfeature_status == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->set_ppfeature_status(hwmgr, ppfeature_masks);
	mutex_unlock(&hwmgr->smu_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक pp_asic_reset_mode_2(व्योम *handle)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
		पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->asic_reset == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->asic_reset(hwmgr, SMU_ASIC_RESET_MODE_2);
	mutex_unlock(&hwmgr->smu_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक pp_smu_i2c_bus_access(व्योम *handle, bool acquire)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	पूर्णांक ret = 0;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->smu_i2c_bus_access == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&hwmgr->smu_lock);
	ret = hwmgr->hwmgr_func->smu_i2c_bus_access(hwmgr, acquire);
	mutex_unlock(&hwmgr->smu_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक pp_set_df_cstate(व्योम *handle, क्रमागत pp_df_cstate state)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr)
		वापस -EINVAL;

	अगर (!hwmgr->pm_en || !hwmgr->hwmgr_func->set_df_cstate)
		वापस 0;

	mutex_lock(&hwmgr->smu_lock);
	hwmgr->hwmgr_func->set_df_cstate(hwmgr, state);
	mutex_unlock(&hwmgr->smu_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक pp_set_xgmi_pstate(व्योम *handle, uपूर्णांक32_t pstate)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr)
		वापस -EINVAL;

	अगर (!hwmgr->pm_en || !hwmgr->hwmgr_func->set_xgmi_pstate)
		वापस 0;

	mutex_lock(&hwmgr->smu_lock);
	hwmgr->hwmgr_func->set_xgmi_pstate(hwmgr, pstate);
	mutex_unlock(&hwmgr->smu_lock);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार pp_get_gpu_metrics(व्योम *handle, व्योम **table)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;
	sमाप_प्रकार size;

	अगर (!hwmgr)
		वापस -EINVAL;

	अगर (!hwmgr->pm_en || !hwmgr->hwmgr_func->get_gpu_metrics)
		वापस -EOPNOTSUPP;

	mutex_lock(&hwmgr->smu_lock);
	size = hwmgr->hwmgr_func->get_gpu_metrics(hwmgr, table);
	mutex_unlock(&hwmgr->smu_lock);

	वापस size;
पूर्ण

अटल पूर्णांक pp_gfx_state_change_set(व्योम *handle, uपूर्णांक32_t state)
अणु
	काष्ठा pp_hwmgr *hwmgr = handle;

	अगर (!hwmgr || !hwmgr->pm_en)
		वापस -EINVAL;

	अगर (hwmgr->hwmgr_func->gfx_state_change == शून्य) अणु
		pr_info_ratelimited("%s was not implemented.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&hwmgr->smu_lock);
	hwmgr->hwmgr_func->gfx_state_change(hwmgr, state);
	mutex_unlock(&hwmgr->smu_lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा amd_pm_funcs pp_dpm_funcs = अणु
	.load_firmware = pp_dpm_load_fw,
	.रुको_क्रम_fw_loading_complete = pp_dpm_fw_loading_complete,
	.क्रमce_perक्रमmance_level = pp_dpm_क्रमce_perक्रमmance_level,
	.get_perक्रमmance_level = pp_dpm_get_perक्रमmance_level,
	.get_current_घातer_state = pp_dpm_get_current_घातer_state,
	.dispatch_tasks = pp_dpm_dispatch_tasks,
	.set_fan_control_mode = pp_dpm_set_fan_control_mode,
	.get_fan_control_mode = pp_dpm_get_fan_control_mode,
	.set_fan_speed_percent = pp_dpm_set_fan_speed_percent,
	.get_fan_speed_percent = pp_dpm_get_fan_speed_percent,
	.get_fan_speed_rpm = pp_dpm_get_fan_speed_rpm,
	.set_fan_speed_rpm = pp_dpm_set_fan_speed_rpm,
	.get_pp_num_states = pp_dpm_get_pp_num_states,
	.get_pp_table = pp_dpm_get_pp_table,
	.set_pp_table = pp_dpm_set_pp_table,
	.क्रमce_घड़ी_level = pp_dpm_क्रमce_घड़ी_level,
	.prपूर्णांक_घड़ी_levels = pp_dpm_prपूर्णांक_घड़ी_levels,
	.get_sclk_od = pp_dpm_get_sclk_od,
	.set_sclk_od = pp_dpm_set_sclk_od,
	.get_mclk_od = pp_dpm_get_mclk_od,
	.set_mclk_od = pp_dpm_set_mclk_od,
	.पढ़ो_sensor = pp_dpm_पढ़ो_sensor,
	.get_vce_घड़ी_state = pp_dpm_get_vce_घड़ी_state,
	.चयन_घातer_profile = pp_dpm_चयन_घातer_profile,
	.set_घड़ीgating_by_smu = pp_set_घड़ीgating_by_smu,
	.set_घातergating_by_smu = pp_set_घातergating_by_smu,
	.get_घातer_profile_mode = pp_get_घातer_profile_mode,
	.set_घातer_profile_mode = pp_set_घातer_profile_mode,
	.set_fine_grain_clk_vol = pp_set_fine_grain_clk_vol,
	.odn_edit_dpm_table = pp_odn_edit_dpm_table,
	.set_mp1_state = pp_dpm_set_mp1_state,
	.set_घातer_limit = pp_set_घातer_limit,
	.get_घातer_limit = pp_get_घातer_limit,
/* export to DC */
	.get_sclk = pp_dpm_get_sclk,
	.get_mclk = pp_dpm_get_mclk,
	.display_configuration_change = pp_display_configuration_change,
	.get_display_घातer_level = pp_get_display_घातer_level,
	.get_current_घड़ीs = pp_get_current_घड़ीs,
	.get_घड़ी_by_type = pp_get_घड़ी_by_type,
	.get_घड़ी_by_type_with_latency = pp_get_घड़ी_by_type_with_latency,
	.get_घड़ी_by_type_with_voltage = pp_get_घड़ी_by_type_with_voltage,
	.set_watermarks_क्रम_घड़ीs_ranges = pp_set_watermarks_क्रम_घड़ीs_ranges,
	.display_घड़ी_voltage_request = pp_display_घड़ी_voltage_request,
	.get_display_mode_validation_घड़ीs = pp_get_display_mode_validation_घड़ीs,
	.notअगरy_smu_enable_pwe = pp_notअगरy_smu_enable_pwe,
	.enable_mgpu_fan_boost = pp_enable_mgpu_fan_boost,
	.set_active_display_count = pp_set_active_display_count,
	.set_min_deep_sleep_dcefclk = pp_set_min_deep_sleep_dcefclk,
	.set_hard_min_dcefclk_by_freq = pp_set_hard_min_dcefclk_by_freq,
	.set_hard_min_fclk_by_freq = pp_set_hard_min_fclk_by_freq,
	.get_asic_baco_capability = pp_get_asic_baco_capability,
	.get_asic_baco_state = pp_get_asic_baco_state,
	.set_asic_baco_state = pp_set_asic_baco_state,
	.get_ppfeature_status = pp_get_ppfeature_status,
	.set_ppfeature_status = pp_set_ppfeature_status,
	.asic_reset_mode_2 = pp_asic_reset_mode_2,
	.smu_i2c_bus_access = pp_smu_i2c_bus_access,
	.set_df_cstate = pp_set_df_cstate,
	.set_xgmi_pstate = pp_set_xgmi_pstate,
	.get_gpu_metrics = pp_get_gpu_metrics,
	.gfx_state_change_set = pp_gfx_state_change_set,
पूर्ण;
