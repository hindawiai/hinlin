<शैली गुरु>
/*
 * Copyright 2017 Advanced Micro Devices, Inc.
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
 * Authors: Rafaध Miधecki <zajec5@gmail.com>
 *          Alex Deucher <alexdeucher@gmail.com>
 */

#समावेश "amdgpu.h"
#समावेश "amdgpu_drv.h"
#समावेश "amdgpu_pm.h"
#समावेश "amdgpu_dpm.h"
#समावेश "atom.h"
#समावेश <linux/pci.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/nospec.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <यंत्र/processor.h>
#समावेश "hwmgr.h"

अटल स्थिर काष्ठा cg_flag_name घड़ीs[] = अणु
	अणुAMD_CG_SUPPORT_GFX_FGCG, "Graphics Fine Grain Clock Gating"पूर्ण,
	अणुAMD_CG_SUPPORT_GFX_MGCG, "Graphics Medium Grain Clock Gating"पूर्ण,
	अणुAMD_CG_SUPPORT_GFX_MGLS, "Graphics Medium Grain memory Light Sleep"पूर्ण,
	अणुAMD_CG_SUPPORT_GFX_CGCG, "Graphics Coarse Grain Clock Gating"पूर्ण,
	अणुAMD_CG_SUPPORT_GFX_CGLS, "Graphics Coarse Grain memory Light Sleep"पूर्ण,
	अणुAMD_CG_SUPPORT_GFX_CGTS, "Graphics Coarse Grain Tree Shader Clock Gating"पूर्ण,
	अणुAMD_CG_SUPPORT_GFX_CGTS_LS, "Graphics Coarse Grain Tree Shader Light Sleep"पूर्ण,
	अणुAMD_CG_SUPPORT_GFX_CP_LS, "Graphics Command Processor Light Sleep"पूर्ण,
	अणुAMD_CG_SUPPORT_GFX_RLC_LS, "Graphics Run List Controller Light Sleep"पूर्ण,
	अणुAMD_CG_SUPPORT_GFX_3D_CGCG, "Graphics 3D Coarse Grain Clock Gating"पूर्ण,
	अणुAMD_CG_SUPPORT_GFX_3D_CGLS, "Graphics 3D Coarse Grain memory Light Sleep"पूर्ण,
	अणुAMD_CG_SUPPORT_MC_LS, "Memory Controller Light Sleep"पूर्ण,
	अणुAMD_CG_SUPPORT_MC_MGCG, "Memory Controller Medium Grain Clock Gating"पूर्ण,
	अणुAMD_CG_SUPPORT_SDMA_LS, "System Direct Memory Access Light Sleep"पूर्ण,
	अणुAMD_CG_SUPPORT_SDMA_MGCG, "System Direct Memory Access Medium Grain Clock Gating"पूर्ण,
	अणुAMD_CG_SUPPORT_BIF_MGCG, "Bus Interface Medium Grain Clock Gating"पूर्ण,
	अणुAMD_CG_SUPPORT_BIF_LS, "Bus Interface Light Sleep"पूर्ण,
	अणुAMD_CG_SUPPORT_UVD_MGCG, "Unified Video Decoder Medium Grain Clock Gating"पूर्ण,
	अणुAMD_CG_SUPPORT_VCE_MGCG, "Video Compression Engine Medium Grain Clock Gating"पूर्ण,
	अणुAMD_CG_SUPPORT_HDP_LS, "Host Data Path Light Sleep"पूर्ण,
	अणुAMD_CG_SUPPORT_HDP_MGCG, "Host Data Path Medium Grain Clock Gating"पूर्ण,
	अणुAMD_CG_SUPPORT_DRM_MGCG, "Digital Right Management Medium Grain Clock Gating"पूर्ण,
	अणुAMD_CG_SUPPORT_DRM_LS, "Digital Right Management Light Sleep"पूर्ण,
	अणुAMD_CG_SUPPORT_ROM_MGCG, "Rom Medium Grain Clock Gating"पूर्ण,
	अणुAMD_CG_SUPPORT_DF_MGCG, "Data Fabric Medium Grain Clock Gating"पूर्ण,
	अणुAMD_CG_SUPPORT_VCN_MGCG, "VCN Medium Grain Clock Gating"पूर्ण,
	अणुAMD_CG_SUPPORT_HDP_DS, "Host Data Path Deep Sleep"पूर्ण,
	अणुAMD_CG_SUPPORT_HDP_SD, "Host Data Path Shutdown"पूर्ण,
	अणुAMD_CG_SUPPORT_IH_CG, "Interrupt Handler Clock Gating"पूर्ण,
	अणुAMD_CG_SUPPORT_JPEG_MGCG, "JPEG Medium Grain Clock Gating"पूर्ण,

	अणुAMD_CG_SUPPORT_ATHUB_MGCG, "Address Translation Hub Medium Grain Clock Gating"पूर्ण,
	अणुAMD_CG_SUPPORT_ATHUB_LS, "Address Translation Hub Light Sleep"पूर्ण,
	अणु0, शून्यपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा hwmon_temp_label अणु
	क्रमागत PP_HWMON_TEMP channel;
	स्थिर अक्षर *label;
पूर्ण temp_label[] = अणु
	अणुPP_TEMP_EDGE, "edge"पूर्ण,
	अणुPP_TEMP_JUNCTION, "junction"पूर्ण,
	अणुPP_TEMP_MEM, "mem"पूर्ण,
पूर्ण;

/**
 * DOC: घातer_dpm_state
 *
 * The घातer_dpm_state file is a legacy पूर्णांकerface and is only provided क्रम
 * backwards compatibility. The amdgpu driver provides a sysfs API क्रम adjusting
 * certain घातer related parameters.  The file घातer_dpm_state is used क्रम this.
 * It accepts the following arguments:
 *
 * - battery
 *
 * - balanced
 *
 * - perक्रमmance
 *
 * battery
 *
 * On older GPUs, the vbios provided a special घातer state क्रम battery
 * operation.  Selecting battery चयनed to this state.  This is no
 * दीर्घer provided on newer GPUs so the option करोes nothing in that हाल.
 *
 * balanced
 *
 * On older GPUs, the vbios provided a special घातer state क्रम balanced
 * operation.  Selecting balanced चयनed to this state.  This is no
 * दीर्घer provided on newer GPUs so the option करोes nothing in that हाल.
 *
 * perक्रमmance
 *
 * On older GPUs, the vbios provided a special घातer state क्रम perक्रमmance
 * operation.  Selecting perक्रमmance चयनed to this state.  This is no
 * दीर्घer provided on newer GPUs so the option करोes nothing in that हाल.
 *
 */

अटल sमाप_प्रकार amdgpu_get_घातer_dpm_state(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	क्रमागत amd_pm_state_type pm;
	पूर्णांक ret;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	ret = pm_runसमय_get_sync(ddev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	अगर (pp_funcs->get_current_घातer_state) अणु
		pm = amdgpu_dpm_get_current_घातer_state(adev);
	पूर्ण अन्यथा अणु
		pm = adev->pm.dpm.user_state;
	पूर्ण

	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	वापस sysfs_emit(buf, "%s\n",
			  (pm == POWER_STATE_TYPE_BATTERY) ? "battery" :
			  (pm == POWER_STATE_TYPE_BALANCED) ? "balanced" : "performance");
पूर्ण

अटल sमाप_प्रकार amdgpu_set_घातer_dpm_state(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buf,
					  माप_प्रकार count)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	क्रमागत amd_pm_state_type  state;
	पूर्णांक ret;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	अगर (म_भेदन("battery", buf, म_माप("battery")) == 0)
		state = POWER_STATE_TYPE_BATTERY;
	अन्यथा अगर (म_भेदन("balanced", buf, म_माप("balanced")) == 0)
		state = POWER_STATE_TYPE_BALANCED;
	अन्यथा अगर (म_भेदन("performance", buf, म_माप("performance")) == 0)
		state = POWER_STATE_TYPE_PERFORMANCE;
	अन्यथा
		वापस -EINVAL;

	ret = pm_runसमय_get_sync(ddev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	अगर (is_support_sw_smu(adev)) अणु
		mutex_lock(&adev->pm.mutex);
		adev->pm.dpm.user_state = state;
		mutex_unlock(&adev->pm.mutex);
	पूर्ण अन्यथा अगर (adev->घातerplay.pp_funcs->dispatch_tasks) अणु
		amdgpu_dpm_dispatch_task(adev, AMD_PP_TASK_ENABLE_USER_STATE, &state);
	पूर्ण अन्यथा अणु
		mutex_lock(&adev->pm.mutex);
		adev->pm.dpm.user_state = state;
		mutex_unlock(&adev->pm.mutex);

		amdgpu_pm_compute_घड़ीs(adev);
	पूर्ण
	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	वापस count;
पूर्ण


/**
 * DOC: घातer_dpm_क्रमce_perक्रमmance_level
 *
 * The amdgpu driver provides a sysfs API क्रम adjusting certain घातer
 * related parameters.  The file घातer_dpm_क्रमce_perक्रमmance_level is
 * used क्रम this.  It accepts the following arguments:
 *
 * - स्वतः
 *
 * - low
 *
 * - high
 *
 * - manual
 *
 * - profile_standard
 *
 * - profile_min_sclk
 *
 * - profile_min_mclk
 *
 * - profile_peak
 *
 * स्वतः
 *
 * When स्वतः is selected, the driver will attempt to dynamically select
 * the optimal घातer profile क्रम current conditions in the driver.
 *
 * low
 *
 * When low is selected, the घड़ीs are क्रमced to the lowest घातer state.
 *
 * high
 *
 * When high is selected, the घड़ीs are क्रमced to the highest घातer state.
 *
 * manual
 *
 * When manual is selected, the user can manually adjust which घातer states
 * are enabled क्रम each घड़ी करोमुख्य via the sysfs pp_dpm_mclk, pp_dpm_sclk,
 * and pp_dpm_pcie files and adjust the घातer state transition heuristics
 * via the pp_घातer_profile_mode sysfs file.
 *
 * profile_standard
 * profile_min_sclk
 * profile_min_mclk
 * profile_peak
 *
 * When the profiling modes are selected, घड़ी and घातer gating are
 * disabled and the घड़ीs are set क्रम dअगरferent profiling हालs. This
 * mode is recommended क्रम profiling specअगरic work loads where you करो
 * not want घड़ी or घातer gating क्रम घड़ी fluctuation to पूर्णांकerfere
 * with your results. profile_standard sets the घड़ीs to a fixed घड़ी
 * level which varies from asic to asic.  profile_min_sclk क्रमces the sclk
 * to the lowest level.  profile_min_mclk क्रमces the mclk to the lowest level.
 * profile_peak sets all घड़ीs (mclk, sclk, pcie) to the highest levels.
 *
 */

अटल sमाप_प्रकार amdgpu_get_घातer_dpm_क्रमce_perक्रमmance_level(काष्ठा device *dev,
							    काष्ठा device_attribute *attr,
							    अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	क्रमागत amd_dpm_क्रमced_level level = 0xff;
	पूर्णांक ret;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	ret = pm_runसमय_get_sync(ddev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	अगर (adev->घातerplay.pp_funcs->get_perक्रमmance_level)
		level = amdgpu_dpm_get_perक्रमmance_level(adev);
	अन्यथा
		level = adev->pm.dpm.क्रमced_level;

	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	वापस sysfs_emit(buf, "%s\n",
			  (level == AMD_DPM_FORCED_LEVEL_AUTO) ? "auto" :
			  (level == AMD_DPM_FORCED_LEVEL_LOW) ? "low" :
			  (level == AMD_DPM_FORCED_LEVEL_HIGH) ? "high" :
			  (level == AMD_DPM_FORCED_LEVEL_MANUAL) ? "manual" :
			  (level == AMD_DPM_FORCED_LEVEL_PROखाता_STANDARD) ? "profile_standard" :
			  (level == AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK) ? "profile_min_sclk" :
			  (level == AMD_DPM_FORCED_LEVEL_PROखाता_MIN_MCLK) ? "profile_min_mclk" :
			  (level == AMD_DPM_FORCED_LEVEL_PROखाता_PEAK) ? "profile_peak" :
			  (level == AMD_DPM_FORCED_LEVEL_PERF_DETERMINISM) ? "perf_determinism" :
			  "unknown");
पूर्ण

अटल sमाप_प्रकार amdgpu_set_घातer_dpm_क्रमce_perक्रमmance_level(काष्ठा device *dev,
							    काष्ठा device_attribute *attr,
							    स्थिर अक्षर *buf,
							    माप_प्रकार count)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	क्रमागत amd_dpm_क्रमced_level level;
	क्रमागत amd_dpm_क्रमced_level current_level = 0xff;
	पूर्णांक ret = 0;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	अगर (म_भेदन("low", buf, म_माप("low")) == 0) अणु
		level = AMD_DPM_FORCED_LEVEL_LOW;
	पूर्ण अन्यथा अगर (म_भेदन("high", buf, म_माप("high")) == 0) अणु
		level = AMD_DPM_FORCED_LEVEL_HIGH;
	पूर्ण अन्यथा अगर (म_भेदन("auto", buf, म_माप("auto")) == 0) अणु
		level = AMD_DPM_FORCED_LEVEL_AUTO;
	पूर्ण अन्यथा अगर (म_भेदन("manual", buf, म_माप("manual")) == 0) अणु
		level = AMD_DPM_FORCED_LEVEL_MANUAL;
	पूर्ण अन्यथा अगर (म_भेदन("profile_exit", buf, म_माप("profile_exit")) == 0) अणु
		level = AMD_DPM_FORCED_LEVEL_PROखाता_EXIT;
	पूर्ण अन्यथा अगर (म_भेदन("profile_standard", buf, म_माप("profile_standard")) == 0) अणु
		level = AMD_DPM_FORCED_LEVEL_PROखाता_STANDARD;
	पूर्ण अन्यथा अगर (म_भेदन("profile_min_sclk", buf, म_माप("profile_min_sclk")) == 0) अणु
		level = AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK;
	पूर्ण अन्यथा अगर (म_भेदन("profile_min_mclk", buf, म_माप("profile_min_mclk")) == 0) अणु
		level = AMD_DPM_FORCED_LEVEL_PROखाता_MIN_MCLK;
	पूर्ण अन्यथा अगर (म_भेदन("profile_peak", buf, म_माप("profile_peak")) == 0) अणु
		level = AMD_DPM_FORCED_LEVEL_PROखाता_PEAK;
	पूर्ण अन्यथा अगर (म_भेदन("perf_determinism", buf, म_माप("perf_determinism")) == 0) अणु
		level = AMD_DPM_FORCED_LEVEL_PERF_DETERMINISM;
	पूर्ण  अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	ret = pm_runसमय_get_sync(ddev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	अगर (pp_funcs->get_perक्रमmance_level)
		current_level = amdgpu_dpm_get_perक्रमmance_level(adev);

	अगर (current_level == level) अणु
		pm_runसमय_mark_last_busy(ddev->dev);
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस count;
	पूर्ण

	अगर (adev->asic_type == CHIP_RAVEN) अणु
		अगर (!(adev->apu_flags & AMD_APU_IS_RAVEN2)) अणु
			अगर (current_level != AMD_DPM_FORCED_LEVEL_MANUAL && level == AMD_DPM_FORCED_LEVEL_MANUAL)
				amdgpu_gfx_off_ctrl(adev, false);
			अन्यथा अगर (current_level == AMD_DPM_FORCED_LEVEL_MANUAL && level != AMD_DPM_FORCED_LEVEL_MANUAL)
				amdgpu_gfx_off_ctrl(adev, true);
		पूर्ण
	पूर्ण

	/* profile_निकास setting is valid only when current mode is in profile mode */
	अगर (!(current_level & (AMD_DPM_FORCED_LEVEL_PROखाता_STANDARD |
	    AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK |
	    AMD_DPM_FORCED_LEVEL_PROखाता_MIN_MCLK |
	    AMD_DPM_FORCED_LEVEL_PROखाता_PEAK)) &&
	    (level == AMD_DPM_FORCED_LEVEL_PROखाता_EXIT)) अणु
		pr_err("Currently not in any profile mode!\n");
		pm_runसमय_mark_last_busy(ddev->dev);
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस -EINVAL;
	पूर्ण

	अगर (pp_funcs->क्रमce_perक्रमmance_level) अणु
		mutex_lock(&adev->pm.mutex);
		अगर (adev->pm.dpm.thermal_active) अणु
			mutex_unlock(&adev->pm.mutex);
			pm_runसमय_mark_last_busy(ddev->dev);
			pm_runसमय_put_स्वतःsuspend(ddev->dev);
			वापस -EINVAL;
		पूर्ण
		ret = amdgpu_dpm_क्रमce_perक्रमmance_level(adev, level);
		अगर (ret) अणु
			mutex_unlock(&adev->pm.mutex);
			pm_runसमय_mark_last_busy(ddev->dev);
			pm_runसमय_put_स्वतःsuspend(ddev->dev);
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			adev->pm.dpm.क्रमced_level = level;
		पूर्ण
		mutex_unlock(&adev->pm.mutex);
	पूर्ण
	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	वापस count;
पूर्ण

अटल sमाप_प्रकार amdgpu_get_pp_num_states(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	काष्ठा pp_states_info data;
	पूर्णांक i, buf_len, ret;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	ret = pm_runसमय_get_sync(ddev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	अगर (pp_funcs->get_pp_num_states) अणु
		amdgpu_dpm_get_pp_num_states(adev, &data);
	पूर्ण अन्यथा अणु
		स_रखो(&data, 0, माप(data));
	पूर्ण

	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	buf_len = snम_लिखो(buf, PAGE_SIZE, "states: %d\n", data.nums);
	क्रम (i = 0; i < data.nums; i++)
		buf_len += snम_लिखो(buf + buf_len, PAGE_SIZE, "%d %s\n", i,
				(data.states[i] == POWER_STATE_TYPE_INTERNAL_BOOT) ? "boot" :
				(data.states[i] == POWER_STATE_TYPE_BATTERY) ? "battery" :
				(data.states[i] == POWER_STATE_TYPE_BALANCED) ? "balanced" :
				(data.states[i] == POWER_STATE_TYPE_PERFORMANCE) ? "performance" : "default");

	वापस buf_len;
पूर्ण

अटल sमाप_प्रकार amdgpu_get_pp_cur_state(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	काष्ठा pp_states_info data = अणु0पूर्ण;
	क्रमागत amd_pm_state_type pm = 0;
	पूर्णांक i = 0, ret = 0;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	ret = pm_runसमय_get_sync(ddev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	अगर (pp_funcs->get_current_घातer_state
		 && pp_funcs->get_pp_num_states) अणु
		pm = amdgpu_dpm_get_current_घातer_state(adev);
		amdgpu_dpm_get_pp_num_states(adev, &data);
	पूर्ण

	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	क्रम (i = 0; i < data.nums; i++) अणु
		अगर (pm == data.states[i])
			अवरोध;
	पूर्ण

	अगर (i == data.nums)
		i = -EINVAL;

	वापस sysfs_emit(buf, "%d\n", i);
पूर्ण

अटल sमाप_प्रकार amdgpu_get_pp_क्रमce_state(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	अगर (adev->pp_क्रमce_state_enabled)
		वापस amdgpu_get_pp_cur_state(dev, attr, buf);
	अन्यथा
		वापस sysfs_emit(buf, "\n");
पूर्ण

अटल sमाप_प्रकार amdgpu_set_pp_क्रमce_state(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	क्रमागत amd_pm_state_type state = 0;
	अचिन्हित दीर्घ idx;
	पूर्णांक ret;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	अगर (म_माप(buf) == 1)
		adev->pp_क्रमce_state_enabled = false;
	अन्यथा अगर (is_support_sw_smu(adev))
		adev->pp_क्रमce_state_enabled = false;
	अन्यथा अगर (adev->घातerplay.pp_funcs->dispatch_tasks &&
			adev->घातerplay.pp_funcs->get_pp_num_states) अणु
		काष्ठा pp_states_info data;

		ret = kम_से_अदीर्घ(buf, 0, &idx);
		अगर (ret || idx >= ARRAY_SIZE(data.states))
			वापस -EINVAL;

		idx = array_index_nospec(idx, ARRAY_SIZE(data.states));

		amdgpu_dpm_get_pp_num_states(adev, &data);
		state = data.states[idx];

		ret = pm_runसमय_get_sync(ddev->dev);
		अगर (ret < 0) अणु
			pm_runसमय_put_स्वतःsuspend(ddev->dev);
			वापस ret;
		पूर्ण

		/* only set user selected घातer states */
		अगर (state != POWER_STATE_TYPE_INTERNAL_BOOT &&
		    state != POWER_STATE_TYPE_DEFAULT) अणु
			amdgpu_dpm_dispatch_task(adev,
					AMD_PP_TASK_ENABLE_USER_STATE, &state);
			adev->pp_क्रमce_state_enabled = true;
		पूर्ण
		pm_runसमय_mark_last_busy(ddev->dev);
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
	पूर्ण

	वापस count;
पूर्ण

/**
 * DOC: pp_table
 *
 * The amdgpu driver provides a sysfs API क्रम uploading new घातerplay
 * tables.  The file pp_table is used क्रम this.  Reading the file
 * will dump the current घातer play table.  Writing to the file
 * will attempt to upload a new घातerplay table and re-initialize
 * घातerplay using that new table.
 *
 */

अटल sमाप_प्रकार amdgpu_get_pp_table(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	अक्षर *table = शून्य;
	पूर्णांक size, ret;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	ret = pm_runसमय_get_sync(ddev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	अगर (adev->घातerplay.pp_funcs->get_pp_table) अणु
		size = amdgpu_dpm_get_pp_table(adev, &table);
		pm_runसमय_mark_last_busy(ddev->dev);
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		अगर (size < 0)
			वापस size;
	पूर्ण अन्यथा अणु
		pm_runसमय_mark_last_busy(ddev->dev);
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस 0;
	पूर्ण

	अगर (size >= PAGE_SIZE)
		size = PAGE_SIZE - 1;

	स_नकल(buf, table, size);

	वापस size;
पूर्ण

अटल sमाप_प्रकार amdgpu_set_pp_table(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	पूर्णांक ret = 0;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	ret = pm_runसमय_get_sync(ddev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	ret = amdgpu_dpm_set_pp_table(adev, buf, count);
	अगर (ret) अणु
		pm_runसमय_mark_last_busy(ddev->dev);
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	वापस count;
पूर्ण

/**
 * DOC: pp_od_clk_voltage
 *
 * The amdgpu driver provides a sysfs API क्रम adjusting the घड़ीs and voltages
 * in each घातer level within a घातer state.  The pp_od_clk_voltage is used क्रम
 * this.
 *
 * Note that the actual memory controller घड़ी rate are exposed, not
 * the effective memory घड़ी of the DRAMs. To translate it, use the
 * following क्रमmula:
 *
 * Clock conversion (Mhz):
 *
 * HBM: effective_memory_घड़ी = memory_controller_घड़ी * 1
 *
 * G5: effective_memory_घड़ी = memory_controller_घड़ी * 1
 *
 * G6: effective_memory_घड़ी = memory_controller_घड़ी * 2
 *
 * DRAM data rate (MT/s):
 *
 * HBM: effective_memory_घड़ी * 2 = data_rate
 *
 * G5: effective_memory_घड़ी * 4 = data_rate
 *
 * G6: effective_memory_घड़ी * 8 = data_rate
 *
 * Bandwidth (MB/s):
 *
 * data_rate * vram_bit_width / 8 = memory_bandwidth
 *
 * Some examples:
 *
 * G5 on RX460:
 *
 * memory_controller_घड़ी = 1750 Mhz
 *
 * effective_memory_घड़ी = 1750 Mhz * 1 = 1750 Mhz
 *
 * data rate = 1750 * 4 = 7000 MT/s
 *
 * memory_bandwidth = 7000 * 128 bits / 8 = 112000 MB/s
 *
 * G6 on RX5700:
 *
 * memory_controller_घड़ी = 875 Mhz
 *
 * effective_memory_घड़ी = 875 Mhz * 2 = 1750 Mhz
 *
 * data rate = 1750 * 8 = 14000 MT/s
 *
 * memory_bandwidth = 14000 * 256 bits / 8 = 448000 MB/s
 *
 * < For Vega10 and previous ASICs >
 *
 * Reading the file will display:
 *
 * - a list of engine घड़ी levels and voltages labeled OD_SCLK
 *
 * - a list of memory घड़ी levels and voltages labeled OD_MCLK
 *
 * - a list of valid ranges क्रम sclk, mclk, and voltage labeled OD_RANGE
 *
 * To manually adjust these settings, first select manual using
 * घातer_dpm_क्रमce_perक्रमmance_level. Enter a new value क्रम each
 * level by writing a string that contains "s/m level clock voltage" to
 * the file.  E.g., "s 1 500 820" will update sclk level 1 to be 500 MHz
 * at 820 mV; "m 0 350 810" will update mclk level 0 to be 350 MHz at
 * 810 mV.  When you have edited all of the states as needed, ग_लिखो
 * "c" (commit) to the file to commit your changes.  If you want to reset to the
 * शेष घातer levels, ग_लिखो "r" (reset) to the file to reset them.
 *
 *
 * < For Vega20 and newer ASICs >
 *
 * Reading the file will display:
 *
 * - minimum and maximum engine घड़ी labeled OD_SCLK
 *
 * - minimum(not available क्रम Vega20 and Navi1x) and maximum memory
 *   घड़ी labeled OD_MCLK
 *
 * - three <frequency, voltage> poपूर्णांकs labeled OD_VDDC_CURVE.
 *   They can be used to calibrate the sclk voltage curve.
 *
 * - voltage offset(in mV) applied on target voltage calculation.
 *   This is available क्रम Sienna Cichlid, Navy Flounder and Dimgrey
 *   Cavefish. For these ASICs, the target voltage calculation can be
 *   illustrated by "voltage = voltage calculated from v/f curve +
 *   overdrive vddgfx offset"
 *
 * - a list of valid ranges क्रम sclk, mclk, and voltage curve poपूर्णांकs
 *   labeled OD_RANGE
 *
 * To manually adjust these settings:
 *
 * - First select manual using घातer_dpm_क्रमce_perक्रमmance_level
 *
 * - For घड़ी frequency setting, enter a new value by writing a
 *   string that contains "s/m index clock" to the file. The index
 *   should be 0 अगर to set minimum घड़ी. And 1 अगर to set maximum
 *   घड़ी. E.g., "s 0 500" will update minimum sclk to be 500 MHz.
 *   "m 1 800" will update maximum mclk to be 800Mhz.
 *
 *   For sclk voltage curve, enter the new values by writing a
 *   string that contains "vc point clock voltage" to the file. The
 *   poपूर्णांकs are indexed by 0, 1 and 2. E.g., "vc 0 300 600" will
 *   update poपूर्णांक1 with घड़ी set as 300Mhz and voltage as
 *   600mV. "vc 2 1000 1000" will update poपूर्णांक3 with घड़ी set
 *   as 1000Mhz and voltage 1000mV.
 *
 *   To update the voltage offset applied क्रम gfxclk/voltage calculation,
 *   enter the new value by writing a string that contains "vo offset".
 *   This is supported by Sienna Cichlid, Navy Flounder and Dimgrey Cavefish.
 *   And the offset can be a positive or negative value.
 *
 * - When you have edited all of the states as needed, ग_लिखो "c" (commit)
 *   to the file to commit your changes
 *
 * - If you want to reset to the शेष घातer levels, ग_लिखो "r" (reset)
 *   to the file to reset them
 *
 */

अटल sमाप_प्रकार amdgpu_set_pp_od_clk_voltage(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	पूर्णांक ret;
	uपूर्णांक32_t parameter_size = 0;
	दीर्घ parameter[64];
	अक्षर buf_cpy[128];
	अक्षर *पंचांगp_str;
	अक्षर *sub_str;
	स्थिर अक्षर delimiter[3] = अणु' ', '\n', '\0'पूर्ण;
	uपूर्णांक32_t type;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	अगर (count > 127)
		वापस -EINVAL;

	अगर (*buf == 's')
		type = PP_OD_EDIT_SCLK_VDDC_TABLE;
	अन्यथा अगर (*buf == 'p')
		type = PP_OD_EDIT_CCLK_VDDC_TABLE;
	अन्यथा अगर (*buf == 'm')
		type = PP_OD_EDIT_MCLK_VDDC_TABLE;
	अन्यथा अगर(*buf == 'r')
		type = PP_OD_RESTORE_DEFAULT_TABLE;
	अन्यथा अगर (*buf == 'c')
		type = PP_OD_COMMIT_DPM_TABLE;
	अन्यथा अगर (!म_भेदन(buf, "vc", 2))
		type = PP_OD_EDIT_VDDC_CURVE;
	अन्यथा अगर (!म_भेदन(buf, "vo", 2))
		type = PP_OD_EDIT_VDDGFX_OFFSET;
	अन्यथा
		वापस -EINVAL;

	स_नकल(buf_cpy, buf, count+1);

	पंचांगp_str = buf_cpy;

	अगर ((type == PP_OD_EDIT_VDDC_CURVE) ||
	     (type == PP_OD_EDIT_VDDGFX_OFFSET))
		पंचांगp_str++;
	जबतक (है_खाली(*++पंचांगp_str));

	जबतक ((sub_str = strsep(&पंचांगp_str, delimiter)) != शून्य) अणु
		अगर (म_माप(sub_str) == 0)
			जारी;
		ret = kम_से_दीर्घ(sub_str, 0, &parameter[parameter_size]);
		अगर (ret)
			वापस -EINVAL;
		parameter_size++;

		जबतक (है_खाली(*पंचांगp_str))
			पंचांगp_str++;
	पूर्ण

	ret = pm_runसमय_get_sync(ddev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	अगर (adev->घातerplay.pp_funcs->set_fine_grain_clk_vol) अणु
		ret = amdgpu_dpm_set_fine_grain_clk_vol(adev, type,
							parameter,
							parameter_size);
		अगर (ret) अणु
			pm_runसमय_mark_last_busy(ddev->dev);
			pm_runसमय_put_स्वतःsuspend(ddev->dev);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (adev->घातerplay.pp_funcs->odn_edit_dpm_table) अणु
		ret = amdgpu_dpm_odn_edit_dpm_table(adev, type,
						    parameter, parameter_size);
		अगर (ret) अणु
			pm_runसमय_mark_last_busy(ddev->dev);
			pm_runसमय_put_स्वतःsuspend(ddev->dev);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (type == PP_OD_COMMIT_DPM_TABLE) अणु
		अगर (adev->घातerplay.pp_funcs->dispatch_tasks) अणु
			amdgpu_dpm_dispatch_task(adev,
						 AMD_PP_TASK_READJUST_POWER_STATE,
						 शून्य);
			pm_runसमय_mark_last_busy(ddev->dev);
			pm_runसमय_put_स्वतःsuspend(ddev->dev);
			वापस count;
		पूर्ण अन्यथा अणु
			pm_runसमय_mark_last_busy(ddev->dev);
			pm_runसमय_put_स्वतःsuspend(ddev->dev);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	वापस count;
पूर्ण

अटल sमाप_प्रकार amdgpu_get_pp_od_clk_voltage(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	sमाप_प्रकार size;
	पूर्णांक ret;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	ret = pm_runसमय_get_sync(ddev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	अगर (adev->घातerplay.pp_funcs->prपूर्णांक_घड़ी_levels) अणु
		size = amdgpu_dpm_prपूर्णांक_घड़ी_levels(adev, OD_SCLK, buf);
		size += amdgpu_dpm_prपूर्णांक_घड़ी_levels(adev, OD_MCLK, buf+size);
		size += amdgpu_dpm_prपूर्णांक_घड़ी_levels(adev, OD_VDDC_CURVE, buf+size);
		size += amdgpu_dpm_prपूर्णांक_घड़ी_levels(adev, OD_VDDGFX_OFFSET, buf+size);
		size += amdgpu_dpm_prपूर्णांक_घड़ी_levels(adev, OD_RANGE, buf+size);
		size += amdgpu_dpm_prपूर्णांक_घड़ी_levels(adev, OD_CCLK, buf+size);
	पूर्ण अन्यथा अणु
		size = snम_लिखो(buf, PAGE_SIZE, "\n");
	पूर्ण
	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	वापस size;
पूर्ण

/**
 * DOC: pp_features
 *
 * The amdgpu driver provides a sysfs API क्रम adjusting what घातerplay
 * features to be enabled. The file pp_features is used क्रम this. And
 * this is only available क्रम Vega10 and later dGPUs.
 *
 * Reading back the file will show you the followings:
 * - Current ppfeature masks
 * - List of the all supported घातerplay features with their naming,
 *   biपंचांगasks and enablement status('Y'/'N' means "enabled"/"disabled").
 *
 * To manually enable or disable a specअगरic feature, just set or clear
 * the corresponding bit from original ppfeature masks and input the
 * new ppfeature masks.
 */
अटल sमाप_प्रकार amdgpu_set_pp_features(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      स्थिर अक्षर *buf,
				      माप_प्रकार count)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	uपूर्णांक64_t featuremask;
	पूर्णांक ret;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	ret = kstrtou64(buf, 0, &featuremask);
	अगर (ret)
		वापस -EINVAL;

	ret = pm_runसमय_get_sync(ddev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	अगर (adev->घातerplay.pp_funcs->set_ppfeature_status) अणु
		ret = amdgpu_dpm_set_ppfeature_status(adev, featuremask);
		अगर (ret) अणु
			pm_runसमय_mark_last_busy(ddev->dev);
			pm_runसमय_put_स्वतःsuspend(ddev->dev);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	वापस count;
पूर्ण

अटल sमाप_प्रकार amdgpu_get_pp_features(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	sमाप_प्रकार size;
	पूर्णांक ret;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	ret = pm_runसमय_get_sync(ddev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	अगर (adev->घातerplay.pp_funcs->get_ppfeature_status)
		size = amdgpu_dpm_get_ppfeature_status(adev, buf);
	अन्यथा
		size = snम_लिखो(buf, PAGE_SIZE, "\n");

	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	वापस size;
पूर्ण

/**
 * DOC: pp_dpm_sclk pp_dpm_mclk pp_dpm_socclk pp_dpm_fclk pp_dpm_dcefclk pp_dpm_pcie
 *
 * The amdgpu driver provides a sysfs API क्रम adjusting what घातer levels
 * are enabled क्रम a given घातer state.  The files pp_dpm_sclk, pp_dpm_mclk,
 * pp_dpm_socclk, pp_dpm_fclk, pp_dpm_dcefclk and pp_dpm_pcie are used क्रम
 * this.
 *
 * pp_dpm_socclk and pp_dpm_dcefclk पूर्णांकerfaces are only available क्रम
 * Vega10 and later ASICs.
 * pp_dpm_fclk पूर्णांकerface is only available क्रम Vega20 and later ASICs.
 *
 * Reading back the files will show you the available घातer levels within
 * the घातer state and the घड़ी inक्रमmation क्रम those levels.
 *
 * To manually adjust these states, first select manual using
 * घातer_dpm_क्रमce_perक्रमmance_level.
 * Secondly, enter a new value क्रम each level by inputing a string that
 * contains " echo xx xx xx > pp_dpm_sclk/mclk/pcie"
 * E.g.,
 *
 * .. code-block:: bash
 *
 *	echo "4 5 6" > pp_dpm_sclk
 *
 * will enable sclk levels 4, 5, and 6.
 *
 * NOTE: change to the dcefclk max dpm level is not supported now
 */

अटल sमाप_प्रकार amdgpu_get_pp_dpm_घड़ी(काष्ठा device *dev,
		क्रमागत pp_घड़ी_प्रकारype type,
		अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	sमाप_प्रकार size;
	पूर्णांक ret;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	ret = pm_runसमय_get_sync(ddev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	अगर (adev->घातerplay.pp_funcs->prपूर्णांक_घड़ी_levels)
		size = amdgpu_dpm_prपूर्णांक_घड़ी_levels(adev, type, buf);
	अन्यथा
		size = snम_लिखो(buf, PAGE_SIZE, "\n");

	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	वापस size;
पूर्ण

/*
 * Worst हाल: 32 bits inभागidually specअगरied, in octal at 12 अक्षरacters
 * per line (+1 क्रम \न).
 */
#घोषणा AMDGPU_MASK_BUF_MAX	(32 * 13)

अटल sमाप_प्रकार amdgpu_पढ़ो_mask(स्थिर अक्षर *buf, माप_प्रकार count, uपूर्णांक32_t *mask)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ level;
	अक्षर *sub_str = शून्य;
	अक्षर *पंचांगp;
	अक्षर buf_cpy[AMDGPU_MASK_BUF_MAX + 1];
	स्थिर अक्षर delimiter[3] = अणु' ', '\n', '\0'पूर्ण;
	माप_प्रकार bytes;

	*mask = 0;

	bytes = min(count, माप(buf_cpy) - 1);
	स_नकल(buf_cpy, buf, bytes);
	buf_cpy[bytes] = '\0';
	पंचांगp = buf_cpy;
	जबतक ((sub_str = strsep(&पंचांगp, delimiter)) != शून्य) अणु
		अगर (म_माप(sub_str)) अणु
			ret = kम_से_अदीर्घ(sub_str, 0, &level);
			अगर (ret || level > 31)
				वापस -EINVAL;
			*mask |= 1 << level;
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार amdgpu_set_pp_dpm_घड़ी(काष्ठा device *dev,
		क्रमागत pp_घड़ी_प्रकारype type,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	पूर्णांक ret;
	uपूर्णांक32_t mask = 0;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	ret = amdgpu_पढ़ो_mask(buf, count, &mask);
	अगर (ret)
		वापस ret;

	ret = pm_runसमय_get_sync(ddev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	अगर (adev->घातerplay.pp_funcs->क्रमce_घड़ी_level)
		ret = amdgpu_dpm_क्रमce_घड़ी_level(adev, type, mask);
	अन्यथा
		ret = 0;

	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	अगर (ret)
		वापस -EINVAL;

	वापस count;
पूर्ण

अटल sमाप_प्रकार amdgpu_get_pp_dpm_sclk(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	वापस amdgpu_get_pp_dpm_घड़ी(dev, PP_SCLK, buf);
पूर्ण

अटल sमाप_प्रकार amdgpu_set_pp_dpm_sclk(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	वापस amdgpu_set_pp_dpm_घड़ी(dev, PP_SCLK, buf, count);
पूर्ण

अटल sमाप_प्रकार amdgpu_get_pp_dpm_mclk(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	वापस amdgpu_get_pp_dpm_घड़ी(dev, PP_MCLK, buf);
पूर्ण

अटल sमाप_प्रकार amdgpu_set_pp_dpm_mclk(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	वापस amdgpu_set_pp_dpm_घड़ी(dev, PP_MCLK, buf, count);
पूर्ण

अटल sमाप_प्रकार amdgpu_get_pp_dpm_socclk(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	वापस amdgpu_get_pp_dpm_घड़ी(dev, PP_SOCCLK, buf);
पूर्ण

अटल sमाप_प्रकार amdgpu_set_pp_dpm_socclk(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	वापस amdgpu_set_pp_dpm_घड़ी(dev, PP_SOCCLK, buf, count);
पूर्ण

अटल sमाप_प्रकार amdgpu_get_pp_dpm_fclk(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	वापस amdgpu_get_pp_dpm_घड़ी(dev, PP_FCLK, buf);
पूर्ण

अटल sमाप_प्रकार amdgpu_set_pp_dpm_fclk(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	वापस amdgpu_set_pp_dpm_घड़ी(dev, PP_FCLK, buf, count);
पूर्ण

अटल sमाप_प्रकार amdgpu_get_pp_dpm_vclk(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	वापस amdgpu_get_pp_dpm_घड़ी(dev, PP_VCLK, buf);
पूर्ण

अटल sमाप_प्रकार amdgpu_set_pp_dpm_vclk(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	वापस amdgpu_set_pp_dpm_घड़ी(dev, PP_VCLK, buf, count);
पूर्ण

अटल sमाप_प्रकार amdgpu_get_pp_dpm_dclk(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	वापस amdgpu_get_pp_dpm_घड़ी(dev, PP_DCLK, buf);
पूर्ण

अटल sमाप_प्रकार amdgpu_set_pp_dpm_dclk(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	वापस amdgpu_set_pp_dpm_घड़ी(dev, PP_DCLK, buf, count);
पूर्ण

अटल sमाप_प्रकार amdgpu_get_pp_dpm_dcefclk(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	वापस amdgpu_get_pp_dpm_घड़ी(dev, PP_DCEFCLK, buf);
पूर्ण

अटल sमाप_प्रकार amdgpu_set_pp_dpm_dcefclk(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	वापस amdgpu_set_pp_dpm_घड़ी(dev, PP_DCEFCLK, buf, count);
पूर्ण

अटल sमाप_प्रकार amdgpu_get_pp_dpm_pcie(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	वापस amdgpu_get_pp_dpm_घड़ी(dev, PP_PCIE, buf);
पूर्ण

अटल sमाप_प्रकार amdgpu_set_pp_dpm_pcie(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	वापस amdgpu_set_pp_dpm_घड़ी(dev, PP_PCIE, buf, count);
पूर्ण

अटल sमाप_प्रकार amdgpu_get_pp_sclk_od(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	uपूर्णांक32_t value = 0;
	पूर्णांक ret;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	ret = pm_runसमय_get_sync(ddev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	अगर (is_support_sw_smu(adev))
		value = 0;
	अन्यथा अगर (adev->घातerplay.pp_funcs->get_sclk_od)
		value = amdgpu_dpm_get_sclk_od(adev);

	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	वापस sysfs_emit(buf, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार amdgpu_set_pp_sclk_od(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	पूर्णांक ret;
	दीर्घ पूर्णांक value;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	ret = kम_से_दीर्घ(buf, 0, &value);

	अगर (ret)
		वापस -EINVAL;

	ret = pm_runसमय_get_sync(ddev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	अगर (is_support_sw_smu(adev)) अणु
		value = 0;
	पूर्ण अन्यथा अणु
		अगर (adev->घातerplay.pp_funcs->set_sclk_od)
			amdgpu_dpm_set_sclk_od(adev, (uपूर्णांक32_t)value);

		अगर (adev->घातerplay.pp_funcs->dispatch_tasks) अणु
			amdgpu_dpm_dispatch_task(adev, AMD_PP_TASK_READJUST_POWER_STATE, शून्य);
		पूर्ण अन्यथा अणु
			adev->pm.dpm.current_ps = adev->pm.dpm.boot_ps;
			amdgpu_pm_compute_घड़ीs(adev);
		पूर्ण
	पूर्ण

	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	वापस count;
पूर्ण

अटल sमाप_प्रकार amdgpu_get_pp_mclk_od(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	uपूर्णांक32_t value = 0;
	पूर्णांक ret;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	ret = pm_runसमय_get_sync(ddev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	अगर (is_support_sw_smu(adev))
		value = 0;
	अन्यथा अगर (adev->घातerplay.pp_funcs->get_mclk_od)
		value = amdgpu_dpm_get_mclk_od(adev);

	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	वापस sysfs_emit(buf, "%d\n", value);
पूर्ण

अटल sमाप_प्रकार amdgpu_set_pp_mclk_od(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	पूर्णांक ret;
	दीर्घ पूर्णांक value;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	ret = kम_से_दीर्घ(buf, 0, &value);

	अगर (ret)
		वापस -EINVAL;

	ret = pm_runसमय_get_sync(ddev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	अगर (is_support_sw_smu(adev)) अणु
		value = 0;
	पूर्ण अन्यथा अणु
		अगर (adev->घातerplay.pp_funcs->set_mclk_od)
			amdgpu_dpm_set_mclk_od(adev, (uपूर्णांक32_t)value);

		अगर (adev->घातerplay.pp_funcs->dispatch_tasks) अणु
			amdgpu_dpm_dispatch_task(adev, AMD_PP_TASK_READJUST_POWER_STATE, शून्य);
		पूर्ण अन्यथा अणु
			adev->pm.dpm.current_ps = adev->pm.dpm.boot_ps;
			amdgpu_pm_compute_घड़ीs(adev);
		पूर्ण
	पूर्ण

	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	वापस count;
पूर्ण

/**
 * DOC: pp_घातer_profile_mode
 *
 * The amdgpu driver provides a sysfs API क्रम adjusting the heuristics
 * related to चयनing between घातer levels in a घातer state.  The file
 * pp_घातer_profile_mode is used क्रम this.
 *
 * Reading this file outमाला_दो a list of all of the predefined घातer profiles
 * and the relevant heuristics settings क्रम that profile.
 *
 * To select a profile or create a custom profile, first select manual using
 * घातer_dpm_क्रमce_perक्रमmance_level.  Writing the number of a predefined
 * profile to pp_घातer_profile_mode will enable those heuristics.  To
 * create a custom set of heuristics, ग_लिखो a string of numbers to the file
 * starting with the number of the custom profile aदीर्घ with a setting
 * क्रम each heuristic parameter.  Due to dअगरferences across asic families
 * the heuristic parameters vary from family to family.
 *
 */

अटल sमाप_प्रकार amdgpu_get_pp_घातer_profile_mode(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	sमाप_प्रकार size;
	पूर्णांक ret;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	ret = pm_runसमय_get_sync(ddev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	अगर (adev->घातerplay.pp_funcs->get_घातer_profile_mode)
		size = amdgpu_dpm_get_घातer_profile_mode(adev, buf);
	अन्यथा
		size = snम_लिखो(buf, PAGE_SIZE, "\n");

	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	वापस size;
पूर्ण


अटल sमाप_प्रकार amdgpu_set_pp_घातer_profile_mode(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	पूर्णांक ret;
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	uपूर्णांक32_t parameter_size = 0;
	दीर्घ parameter[64];
	अक्षर *sub_str, buf_cpy[128];
	अक्षर *पंचांगp_str;
	uपूर्णांक32_t i = 0;
	अक्षर पंचांगp[2];
	दीर्घ पूर्णांक profile_mode = 0;
	स्थिर अक्षर delimiter[3] = अणु' ', '\n', '\0'पूर्ण;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	पंचांगp[0] = *(buf);
	पंचांगp[1] = '\0';
	ret = kम_से_दीर्घ(पंचांगp, 0, &profile_mode);
	अगर (ret)
		वापस -EINVAL;

	अगर (profile_mode == PP_SMC_POWER_PROखाता_CUSTOM) अणु
		अगर (count < 2 || count > 127)
			वापस -EINVAL;
		जबतक (है_खाली(*++buf))
			i++;
		स_नकल(buf_cpy, buf, count-i);
		पंचांगp_str = buf_cpy;
		जबतक ((sub_str = strsep(&पंचांगp_str, delimiter)) != शून्य) अणु
			अगर (म_माप(sub_str) == 0)
				जारी;
			ret = kम_से_दीर्घ(sub_str, 0, &parameter[parameter_size]);
			अगर (ret)
				वापस -EINVAL;
			parameter_size++;
			जबतक (है_खाली(*पंचांगp_str))
				पंचांगp_str++;
		पूर्ण
	पूर्ण
	parameter[parameter_size] = profile_mode;

	ret = pm_runसमय_get_sync(ddev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	अगर (adev->घातerplay.pp_funcs->set_घातer_profile_mode)
		ret = amdgpu_dpm_set_घातer_profile_mode(adev, parameter, parameter_size);

	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	अगर (!ret)
		वापस count;

	वापस -EINVAL;
पूर्ण

/**
 * DOC: gpu_busy_percent
 *
 * The amdgpu driver provides a sysfs API क्रम पढ़ोing how busy the GPU
 * is as a percentage.  The file gpu_busy_percent is used क्रम this.
 * The SMU firmware computes a percentage of load based on the
 * aggregate activity level in the IP cores.
 */
अटल sमाप_प्रकार amdgpu_get_gpu_busy_percent(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	पूर्णांक r, value, size = माप(value);

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	r = pm_runसमय_get_sync(ddev->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस r;
	पूर्ण

	/* पढ़ो the IP busy sensor */
	r = amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_GPU_LOAD,
				   (व्योम *)&value, &size);

	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	अगर (r)
		वापस r;

	वापस sysfs_emit(buf, "%d\n", value);
पूर्ण

/**
 * DOC: mem_busy_percent
 *
 * The amdgpu driver provides a sysfs API क्रम पढ़ोing how busy the VRAM
 * is as a percentage.  The file mem_busy_percent is used क्रम this.
 * The SMU firmware computes a percentage of load based on the
 * aggregate activity level in the IP cores.
 */
अटल sमाप_प्रकार amdgpu_get_mem_busy_percent(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	पूर्णांक r, value, size = माप(value);

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	r = pm_runसमय_get_sync(ddev->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस r;
	पूर्ण

	/* पढ़ो the IP busy sensor */
	r = amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_MEM_LOAD,
				   (व्योम *)&value, &size);

	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	अगर (r)
		वापस r;

	वापस sysfs_emit(buf, "%d\n", value);
पूर्ण

/**
 * DOC: pcie_bw
 *
 * The amdgpu driver provides a sysfs API क्रम estimating how much data
 * has been received and sent by the GPU in the last second through PCIe.
 * The file pcie_bw is used क्रम this.
 * The Perf counters count the number of received and sent messages and वापस
 * those values, as well as the maximum payload size of a PCIe packet (mps).
 * Note that it is not possible to easily and quickly obtain the size of each
 * packet transmitted, so we output the max payload size (mps) to allow क्रम
 * quick estimation of the PCIe bandwidth usage
 */
अटल sमाप_प्रकार amdgpu_get_pcie_bw(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	uपूर्णांक64_t count0 = 0, count1 = 0;
	पूर्णांक ret;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	अगर (adev->flags & AMD_IS_APU)
		वापस -ENODATA;

	अगर (!adev->asic_funcs->get_pcie_usage)
		वापस -ENODATA;

	ret = pm_runसमय_get_sync(ddev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	amdgpu_asic_get_pcie_usage(adev, &count0, &count1);

	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	वापस sysfs_emit(buf, "%llu %llu %i\n",
			  count0, count1, pcie_get_mps(adev->pdev));
पूर्ण

/**
 * DOC: unique_id
 *
 * The amdgpu driver provides a sysfs API क्रम providing a unique ID क्रम the GPU
 * The file unique_id is used क्रम this.
 * This will provide a Unique ID that will persist from machine to machine
 *
 * NOTE: This will only work क्रम GFX9 and newer. This file will be असलent
 * on unsupported ASICs (GFX8 and older)
 */
अटल sमाप_प्रकार amdgpu_get_unique_id(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	अगर (adev->unique_id)
		वापस sysfs_emit(buf, "%016llx\n", adev->unique_id);

	वापस 0;
पूर्ण

/**
 * DOC: thermal_throttling_logging
 *
 * Thermal throttling pulls करोwn the घड़ी frequency and thus the perक्रमmance.
 * It's an useful mechanism to protect the chip from overheating. Since it
 * impacts perक्रमmance, the user controls whether it is enabled and अगर so,
 * the log frequency.
 *
 * Reading back the file shows you the status(enabled or disabled) and
 * the पूर्णांकerval(in seconds) between each thermal logging.
 *
 * Writing an पूर्णांकeger to the file, sets a new logging पूर्णांकerval, in seconds.
 * The value should be between 1 and 3600. If the value is less than 1,
 * thermal logging is disabled. Values greater than 3600 are ignored.
 */
अटल sमाप_प्रकार amdgpu_get_thermal_throttling_logging(काष्ठा device *dev,
						     काष्ठा device_attribute *attr,
						     अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);

	वापस sysfs_emit(buf, "%s: thermal throttling logging %s, with interval %d seconds\n",
			  adev_to_drm(adev)->unique,
			  atomic_पढ़ो(&adev->throttling_logging_enabled) ? "enabled" : "disabled",
			  adev->throttling_logging_rs.पूर्णांकerval / HZ + 1);
पूर्ण

अटल sमाप_प्रकार amdgpu_set_thermal_throttling_logging(काष्ठा device *dev,
						     काष्ठा device_attribute *attr,
						     स्थिर अक्षर *buf,
						     माप_प्रकार count)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	दीर्घ throttling_logging_पूर्णांकerval;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	ret = kम_से_दीर्घ(buf, 0, &throttling_logging_पूर्णांकerval);
	अगर (ret)
		वापस ret;

	अगर (throttling_logging_पूर्णांकerval > 3600)
		वापस -EINVAL;

	अगर (throttling_logging_पूर्णांकerval > 0) अणु
		raw_spin_lock_irqsave(&adev->throttling_logging_rs.lock, flags);
		/*
		 * Reset the ratelimit समयr पूर्णांकernals.
		 * This can effectively restart the समयr.
		 */
		adev->throttling_logging_rs.पूर्णांकerval =
			(throttling_logging_पूर्णांकerval - 1) * HZ;
		adev->throttling_logging_rs.begin = 0;
		adev->throttling_logging_rs.prपूर्णांकed = 0;
		adev->throttling_logging_rs.missed = 0;
		raw_spin_unlock_irqrestore(&adev->throttling_logging_rs.lock, flags);

		atomic_set(&adev->throttling_logging_enabled, 1);
	पूर्ण अन्यथा अणु
		atomic_set(&adev->throttling_logging_enabled, 0);
	पूर्ण

	वापस count;
पूर्ण

/**
 * DOC: gpu_metrics
 *
 * The amdgpu driver provides a sysfs API क्रम retrieving current gpu
 * metrics data. The file gpu_metrics is used क्रम this. Reading the
 * file will dump all the current gpu metrics data.
 *
 * These data include temperature, frequency, engines utilization,
 * घातer consume, throttler status, fan speed and cpu core statistics(
 * available क्रम APU only). That's it will give a snapshot of all sensors
 * at the same समय.
 */
अटल sमाप_प्रकार amdgpu_get_gpu_metrics(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा drm_device *ddev = dev_get_drvdata(dev);
	काष्ठा amdgpu_device *adev = drm_to_adev(ddev);
	व्योम *gpu_metrics;
	sमाप_प्रकार size = 0;
	पूर्णांक ret;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	ret = pm_runसमय_get_sync(ddev->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(ddev->dev);
		वापस ret;
	पूर्ण

	अगर (adev->घातerplay.pp_funcs->get_gpu_metrics)
		size = amdgpu_dpm_get_gpu_metrics(adev, &gpu_metrics);

	अगर (size <= 0)
		जाओ out;

	अगर (size >= PAGE_SIZE)
		size = PAGE_SIZE - 1;

	स_नकल(buf, gpu_metrics, size);

out:
	pm_runसमय_mark_last_busy(ddev->dev);
	pm_runसमय_put_स्वतःsuspend(ddev->dev);

	वापस size;
पूर्ण

अटल काष्ठा amdgpu_device_attr amdgpu_device_attrs[] = अणु
	AMDGPU_DEVICE_ATTR_RW(घातer_dpm_state,				ATTR_FLAG_BASIC|ATTR_FLAG_ONEVF),
	AMDGPU_DEVICE_ATTR_RW(घातer_dpm_क्रमce_perक्रमmance_level,	ATTR_FLAG_BASIC|ATTR_FLAG_ONEVF),
	AMDGPU_DEVICE_ATTR_RO(pp_num_states,				ATTR_FLAG_BASIC),
	AMDGPU_DEVICE_ATTR_RO(pp_cur_state,				ATTR_FLAG_BASIC),
	AMDGPU_DEVICE_ATTR_RW(pp_क्रमce_state,				ATTR_FLAG_BASIC),
	AMDGPU_DEVICE_ATTR_RW(pp_table,					ATTR_FLAG_BASIC),
	AMDGPU_DEVICE_ATTR_RW(pp_dpm_sclk,				ATTR_FLAG_BASIC|ATTR_FLAG_ONEVF),
	AMDGPU_DEVICE_ATTR_RW(pp_dpm_mclk,				ATTR_FLAG_BASIC|ATTR_FLAG_ONEVF),
	AMDGPU_DEVICE_ATTR_RW(pp_dpm_socclk,				ATTR_FLAG_BASIC|ATTR_FLAG_ONEVF),
	AMDGPU_DEVICE_ATTR_RW(pp_dpm_fclk,				ATTR_FLAG_BASIC|ATTR_FLAG_ONEVF),
	AMDGPU_DEVICE_ATTR_RW(pp_dpm_vclk,				ATTR_FLAG_BASIC|ATTR_FLAG_ONEVF),
	AMDGPU_DEVICE_ATTR_RW(pp_dpm_dclk,				ATTR_FLAG_BASIC|ATTR_FLAG_ONEVF),
	AMDGPU_DEVICE_ATTR_RW(pp_dpm_dcefclk,				ATTR_FLAG_BASIC),
	AMDGPU_DEVICE_ATTR_RW(pp_dpm_pcie,				ATTR_FLAG_BASIC),
	AMDGPU_DEVICE_ATTR_RW(pp_sclk_od,				ATTR_FLAG_BASIC),
	AMDGPU_DEVICE_ATTR_RW(pp_mclk_od,				ATTR_FLAG_BASIC),
	AMDGPU_DEVICE_ATTR_RW(pp_घातer_profile_mode,			ATTR_FLAG_BASIC),
	AMDGPU_DEVICE_ATTR_RW(pp_od_clk_voltage,			ATTR_FLAG_BASIC),
	AMDGPU_DEVICE_ATTR_RO(gpu_busy_percent,				ATTR_FLAG_BASIC),
	AMDGPU_DEVICE_ATTR_RO(mem_busy_percent,				ATTR_FLAG_BASIC),
	AMDGPU_DEVICE_ATTR_RO(pcie_bw,					ATTR_FLAG_BASIC),
	AMDGPU_DEVICE_ATTR_RW(pp_features,				ATTR_FLAG_BASIC),
	AMDGPU_DEVICE_ATTR_RO(unique_id,				ATTR_FLAG_BASIC),
	AMDGPU_DEVICE_ATTR_RW(thermal_throttling_logging,		ATTR_FLAG_BASIC),
	AMDGPU_DEVICE_ATTR_RO(gpu_metrics,				ATTR_FLAG_BASIC),
पूर्ण;

अटल पूर्णांक शेष_attr_update(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_device_attr *attr,
			       uपूर्णांक32_t mask, क्रमागत amdgpu_device_attr_states *states)
अणु
	काष्ठा device_attribute *dev_attr = &attr->dev_attr;
	स्थिर अक्षर *attr_name = dev_attr->attr.name;
	काष्ठा pp_hwmgr *hwmgr = adev->घातerplay.pp_handle;
	क्रमागत amd_asic_type asic_type = adev->asic_type;

	अगर (!(attr->flags & mask)) अणु
		*states = ATTR_STATE_UNSUPPORTED;
		वापस 0;
	पूर्ण

#घोषणा DEVICE_ATTR_IS(_name)	(!म_भेद(attr_name, #_name))

	अगर (DEVICE_ATTR_IS(pp_dpm_socclk)) अणु
		अगर (asic_type < CHIP_VEGA10)
			*states = ATTR_STATE_UNSUPPORTED;
	पूर्ण अन्यथा अगर (DEVICE_ATTR_IS(pp_dpm_dcefclk)) अणु
		अगर (asic_type < CHIP_VEGA10 ||
		    asic_type == CHIP_ARCTURUS ||
		    asic_type == CHIP_ALDEBARAN)
			*states = ATTR_STATE_UNSUPPORTED;
	पूर्ण अन्यथा अगर (DEVICE_ATTR_IS(pp_dpm_fclk)) अणु
		अगर (asic_type < CHIP_VEGA20)
			*states = ATTR_STATE_UNSUPPORTED;
	पूर्ण अन्यथा अगर (DEVICE_ATTR_IS(pp_od_clk_voltage)) अणु
		*states = ATTR_STATE_UNSUPPORTED;
		अगर ((is_support_sw_smu(adev) && adev->smu.od_enabled) ||
		    (is_support_sw_smu(adev) && adev->smu.is_apu) ||
			(!is_support_sw_smu(adev) && hwmgr->od_enabled))
			*states = ATTR_STATE_SUPPORTED;
	पूर्ण अन्यथा अगर (DEVICE_ATTR_IS(mem_busy_percent)) अणु
		अगर (adev->flags & AMD_IS_APU || asic_type == CHIP_VEGA10)
			*states = ATTR_STATE_UNSUPPORTED;
	पूर्ण अन्यथा अगर (DEVICE_ATTR_IS(pcie_bw)) अणु
		/* PCIe Perf counters won't work on APU nodes */
		अगर (adev->flags & AMD_IS_APU)
			*states = ATTR_STATE_UNSUPPORTED;
	पूर्ण अन्यथा अगर (DEVICE_ATTR_IS(unique_id)) अणु
		अगर (asic_type != CHIP_VEGA10 &&
		    asic_type != CHIP_VEGA20 &&
		    asic_type != CHIP_ARCTURUS)
			*states = ATTR_STATE_UNSUPPORTED;
	पूर्ण अन्यथा अगर (DEVICE_ATTR_IS(pp_features)) अणु
		अगर (adev->flags & AMD_IS_APU || asic_type < CHIP_VEGA10)
			*states = ATTR_STATE_UNSUPPORTED;
	पूर्ण अन्यथा अगर (DEVICE_ATTR_IS(gpu_metrics)) अणु
		अगर (asic_type < CHIP_VEGA12)
			*states = ATTR_STATE_UNSUPPORTED;
	पूर्ण अन्यथा अगर (DEVICE_ATTR_IS(pp_dpm_vclk)) अणु
		अगर (!(asic_type == CHIP_VANGOGH))
			*states = ATTR_STATE_UNSUPPORTED;
	पूर्ण अन्यथा अगर (DEVICE_ATTR_IS(pp_dpm_dclk)) अणु
		अगर (!(asic_type == CHIP_VANGOGH))
			*states = ATTR_STATE_UNSUPPORTED;
	पूर्ण

	अगर (asic_type == CHIP_ARCTURUS) अणु
		/* Arcturus करोes not support standalone mclk/socclk/fclk level setting */
		अगर (DEVICE_ATTR_IS(pp_dpm_mclk) ||
		    DEVICE_ATTR_IS(pp_dpm_socclk) ||
		    DEVICE_ATTR_IS(pp_dpm_fclk)) अणु
			dev_attr->attr.mode &= ~S_IWUGO;
			dev_attr->store = शून्य;
		पूर्ण
	पूर्ण

	अगर (DEVICE_ATTR_IS(pp_dpm_dcefclk)) अणु
		/* SMU MP1 करोes not support dcefclk level setting */
		अगर (asic_type >= CHIP_NAVI10) अणु
			dev_attr->attr.mode &= ~S_IWUGO;
			dev_attr->store = शून्य;
		पूर्ण
	पूर्ण

#अघोषित DEVICE_ATTR_IS

	वापस 0;
पूर्ण


अटल पूर्णांक amdgpu_device_attr_create(काष्ठा amdgpu_device *adev,
				     काष्ठा amdgpu_device_attr *attr,
				     uपूर्णांक32_t mask, काष्ठा list_head *attr_list)
अणु
	पूर्णांक ret = 0;
	काष्ठा device_attribute *dev_attr = &attr->dev_attr;
	स्थिर अक्षर *name = dev_attr->attr.name;
	क्रमागत amdgpu_device_attr_states attr_states = ATTR_STATE_SUPPORTED;
	काष्ठा amdgpu_device_attr_entry *attr_entry;

	पूर्णांक (*attr_update)(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_device_attr *attr,
			   uपूर्णांक32_t mask, क्रमागत amdgpu_device_attr_states *states) = शेष_attr_update;

	BUG_ON(!attr);

	attr_update = attr->attr_update ? attr_update : शेष_attr_update;

	ret = attr_update(adev, attr, mask, &attr_states);
	अगर (ret) अणु
		dev_err(adev->dev, "failed to update device file %s, ret = %d\n",
			name, ret);
		वापस ret;
	पूर्ण

	अगर (attr_states == ATTR_STATE_UNSUPPORTED)
		वापस 0;

	ret = device_create_file(adev->dev, dev_attr);
	अगर (ret) अणु
		dev_err(adev->dev, "failed to create device file %s, ret = %d\n",
			name, ret);
	पूर्ण

	attr_entry = kदो_स्मृति(माप(*attr_entry), GFP_KERNEL);
	अगर (!attr_entry)
		वापस -ENOMEM;

	attr_entry->attr = attr;
	INIT_LIST_HEAD(&attr_entry->entry);

	list_add_tail(&attr_entry->entry, attr_list);

	वापस ret;
पूर्ण

अटल व्योम amdgpu_device_attr_हटाओ(काष्ठा amdgpu_device *adev, काष्ठा amdgpu_device_attr *attr)
अणु
	काष्ठा device_attribute *dev_attr = &attr->dev_attr;

	device_हटाओ_file(adev->dev, dev_attr);
पूर्ण

अटल व्योम amdgpu_device_attr_हटाओ_groups(काष्ठा amdgpu_device *adev,
					     काष्ठा list_head *attr_list);

अटल पूर्णांक amdgpu_device_attr_create_groups(काष्ठा amdgpu_device *adev,
					    काष्ठा amdgpu_device_attr *attrs,
					    uपूर्णांक32_t counts,
					    uपूर्णांक32_t mask,
					    काष्ठा list_head *attr_list)
अणु
	पूर्णांक ret = 0;
	uपूर्णांक32_t i = 0;

	क्रम (i = 0; i < counts; i++) अणु
		ret = amdgpu_device_attr_create(adev, &attrs[i], mask, attr_list);
		अगर (ret)
			जाओ failed;
	पूर्ण

	वापस 0;

failed:
	amdgpu_device_attr_हटाओ_groups(adev, attr_list);

	वापस ret;
पूर्ण

अटल व्योम amdgpu_device_attr_हटाओ_groups(काष्ठा amdgpu_device *adev,
					     काष्ठा list_head *attr_list)
अणु
	काष्ठा amdgpu_device_attr_entry *entry, *entry_पंचांगp;

	अगर (list_empty(attr_list))
		वापस ;

	list_क्रम_each_entry_safe(entry, entry_पंचांगp, attr_list, entry) अणु
		amdgpu_device_attr_हटाओ(adev, entry->attr);
		list_del(&entry->entry);
		kमुक्त(entry);
	पूर्ण
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_show_temp(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	पूर्णांक channel = to_sensor_dev_attr(attr)->index;
	पूर्णांक r, temp = 0, size = माप(temp);

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	अगर (channel >= PP_TEMP_MAX)
		वापस -EINVAL;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	चयन (channel) अणु
	हाल PP_TEMP_JUNCTION:
		/* get current junction temperature */
		r = amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_HOTSPOT_TEMP,
					   (व्योम *)&temp, &size);
		अवरोध;
	हाल PP_TEMP_EDGE:
		/* get current edge temperature */
		r = amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_EDGE_TEMP,
					   (व्योम *)&temp, &size);
		अवरोध;
	हाल PP_TEMP_MEM:
		/* get current memory temperature */
		r = amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_MEM_TEMP,
					   (व्योम *)&temp, &size);
		अवरोध;
	शेष:
		r = -EINVAL;
		अवरोध;
	पूर्ण

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	अगर (r)
		वापस r;

	वापस sysfs_emit(buf, "%d\n", temp);
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_show_temp_thresh(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	पूर्णांक hyst = to_sensor_dev_attr(attr)->index;
	पूर्णांक temp;

	अगर (hyst)
		temp = adev->pm.dpm.thermal.min_temp;
	अन्यथा
		temp = adev->pm.dpm.thermal.max_temp;

	वापस sysfs_emit(buf, "%d\n", temp);
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_show_hotspot_temp_thresh(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	पूर्णांक hyst = to_sensor_dev_attr(attr)->index;
	पूर्णांक temp;

	अगर (hyst)
		temp = adev->pm.dpm.thermal.min_hotspot_temp;
	अन्यथा
		temp = adev->pm.dpm.thermal.max_hotspot_crit_temp;

	वापस sysfs_emit(buf, "%d\n", temp);
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_show_mem_temp_thresh(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	पूर्णांक hyst = to_sensor_dev_attr(attr)->index;
	पूर्णांक temp;

	अगर (hyst)
		temp = adev->pm.dpm.thermal.min_mem_temp;
	अन्यथा
		temp = adev->pm.dpm.thermal.max_mem_crit_temp;

	वापस sysfs_emit(buf, "%d\n", temp);
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_show_temp_label(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	पूर्णांक channel = to_sensor_dev_attr(attr)->index;

	अगर (channel >= PP_TEMP_MAX)
		वापस -EINVAL;

	वापस sysfs_emit(buf, "%s\n", temp_label[channel].label);
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_show_temp_emergency(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	पूर्णांक channel = to_sensor_dev_attr(attr)->index;
	पूर्णांक temp = 0;

	अगर (channel >= PP_TEMP_MAX)
		वापस -EINVAL;

	चयन (channel) अणु
	हाल PP_TEMP_JUNCTION:
		temp = adev->pm.dpm.thermal.max_hotspot_emergency_temp;
		अवरोध;
	हाल PP_TEMP_EDGE:
		temp = adev->pm.dpm.thermal.max_edge_emergency_temp;
		अवरोध;
	हाल PP_TEMP_MEM:
		temp = adev->pm.dpm.thermal.max_mem_emergency_temp;
		अवरोध;
	पूर्ण

	वापस sysfs_emit(buf, "%d\n", temp);
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_get_pwm1_enable(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	u32 pwm_mode = 0;
	पूर्णांक ret;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	ret = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस ret;
	पूर्ण

	अगर (!adev->घातerplay.pp_funcs->get_fan_control_mode) अणु
		pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस -EINVAL;
	पूर्ण

	pwm_mode = amdgpu_dpm_get_fan_control_mode(adev);

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	वापस प्र_लिखो(buf, "%u\n", pwm_mode);
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_set_pwm1_enable(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf,
					    माप_प्रकार count)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	पूर्णांक err, ret;
	पूर्णांक value;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	err = kstrtoपूर्णांक(buf, 10, &value);
	अगर (err)
		वापस err;

	ret = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस ret;
	पूर्ण

	अगर (!adev->घातerplay.pp_funcs->set_fan_control_mode) अणु
		pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस -EINVAL;
	पूर्ण

	amdgpu_dpm_set_fan_control_mode(adev, value);

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	वापस count;
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_get_pwm1_min(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%i\n", 0);
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_get_pwm1_max(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%i\n", 255);
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_set_pwm1(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	पूर्णांक err;
	u32 value;
	u32 pwm_mode;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	err = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (err < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस err;
	पूर्ण

	pwm_mode = amdgpu_dpm_get_fan_control_mode(adev);
	अगर (pwm_mode != AMD_FAN_CTRL_MANUAL) अणु
		pr_info("manual fan speed control should be enabled first\n");
		pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस -EINVAL;
	पूर्ण

	err = kstrtou32(buf, 10, &value);
	अगर (err) अणु
		pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस err;
	पूर्ण

	value = (value * 100) / 255;

	अगर (adev->घातerplay.pp_funcs->set_fan_speed_percent)
		err = amdgpu_dpm_set_fan_speed_percent(adev, value);
	अन्यथा
		err = -EINVAL;

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	अगर (err)
		वापस err;

	वापस count;
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_get_pwm1(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	पूर्णांक err;
	u32 speed = 0;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	err = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (err < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस err;
	पूर्ण

	अगर (adev->घातerplay.pp_funcs->get_fan_speed_percent)
		err = amdgpu_dpm_get_fan_speed_percent(adev, &speed);
	अन्यथा
		err = -EINVAL;

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	अगर (err)
		वापस err;

	speed = (speed * 255) / 100;

	वापस प्र_लिखो(buf, "%i\n", speed);
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_get_fan1_input(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	पूर्णांक err;
	u32 speed = 0;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	err = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (err < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस err;
	पूर्ण

	अगर (adev->घातerplay.pp_funcs->get_fan_speed_rpm)
		err = amdgpu_dpm_get_fan_speed_rpm(adev, &speed);
	अन्यथा
		err = -EINVAL;

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	अगर (err)
		वापस err;

	वापस प्र_लिखो(buf, "%i\n", speed);
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_get_fan1_min(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	u32 min_rpm = 0;
	u32 size = माप(min_rpm);
	पूर्णांक r;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	r = amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_MIN_FAN_RPM,
				   (व्योम *)&min_rpm, &size);

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	अगर (r)
		वापस r;

	वापस sysfs_emit(buf, "%d\n", min_rpm);
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_get_fan1_max(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	u32 max_rpm = 0;
	u32 size = माप(max_rpm);
	पूर्णांक r;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	r = amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_MAX_FAN_RPM,
				   (व्योम *)&max_rpm, &size);

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	अगर (r)
		वापस r;

	वापस sysfs_emit(buf, "%d\n", max_rpm);
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_get_fan1_target(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	पूर्णांक err;
	u32 rpm = 0;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	err = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (err < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस err;
	पूर्ण

	अगर (adev->घातerplay.pp_funcs->get_fan_speed_rpm)
		err = amdgpu_dpm_get_fan_speed_rpm(adev, &rpm);
	अन्यथा
		err = -EINVAL;

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	अगर (err)
		वापस err;

	वापस प्र_लिखो(buf, "%i\n", rpm);
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_set_fan1_target(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	पूर्णांक err;
	u32 value;
	u32 pwm_mode;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	err = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (err < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस err;
	पूर्ण

	pwm_mode = amdgpu_dpm_get_fan_control_mode(adev);

	अगर (pwm_mode != AMD_FAN_CTRL_MANUAL) अणु
		pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस -ENODATA;
	पूर्ण

	err = kstrtou32(buf, 10, &value);
	अगर (err) अणु
		pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस err;
	पूर्ण

	अगर (adev->घातerplay.pp_funcs->set_fan_speed_rpm)
		err = amdgpu_dpm_set_fan_speed_rpm(adev, value);
	अन्यथा
		err = -EINVAL;

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	अगर (err)
		वापस err;

	वापस count;
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_get_fan1_enable(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	u32 pwm_mode = 0;
	पूर्णांक ret;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	ret = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस ret;
	पूर्ण

	अगर (!adev->घातerplay.pp_funcs->get_fan_control_mode) अणु
		pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस -EINVAL;
	पूर्ण

	pwm_mode = amdgpu_dpm_get_fan_control_mode(adev);

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	वापस प्र_लिखो(buf, "%i\n", pwm_mode == AMD_FAN_CTRL_AUTO ? 0 : 1);
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_set_fan1_enable(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    स्थिर अक्षर *buf,
					    माप_प्रकार count)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	पूर्णांक err;
	पूर्णांक value;
	u32 pwm_mode;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	err = kstrtoपूर्णांक(buf, 10, &value);
	अगर (err)
		वापस err;

	अगर (value == 0)
		pwm_mode = AMD_FAN_CTRL_AUTO;
	अन्यथा अगर (value == 1)
		pwm_mode = AMD_FAN_CTRL_MANUAL;
	अन्यथा
		वापस -EINVAL;

	err = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (err < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस err;
	पूर्ण

	अगर (!adev->घातerplay.pp_funcs->set_fan_control_mode) अणु
		pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस -EINVAL;
	पूर्ण
	amdgpu_dpm_set_fan_control_mode(adev, pwm_mode);

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	वापस count;
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_show_vddgfx(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	u32 vddgfx;
	पूर्णांक r, size = माप(vddgfx);

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	/* get the voltage */
	r = amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_VDDGFX,
				   (व्योम *)&vddgfx, &size);

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	अगर (r)
		वापस r;

	वापस sysfs_emit(buf, "%d\n", vddgfx);
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_show_vddgfx_label(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "vddgfx\n");
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_show_vddnb(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	u32 vddnb;
	पूर्णांक r, size = माप(vddnb);

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	/* only APUs have vddnb */
	अगर  (!(adev->flags & AMD_IS_APU))
		वापस -EINVAL;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	/* get the voltage */
	r = amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_VDDNB,
				   (व्योम *)&vddnb, &size);

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	अगर (r)
		वापस r;

	वापस sysfs_emit(buf, "%d\n", vddnb);
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_show_vddnb_label(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "vddnb\n");
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_show_घातer_avg(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	u32 query = 0;
	पूर्णांक r, size = माप(u32);
	अचिन्हित uw;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	/* get the voltage */
	r = amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_GPU_POWER,
				   (व्योम *)&query, &size);

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	अगर (r)
		वापस r;

	/* convert to microwatts */
	uw = (query >> 8) * 1000000 + (query & 0xff) * 1000;

	वापस sysfs_emit(buf, "%u\n", uw);
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_show_घातer_cap_min(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%i\n", 0);
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_show_घातer_cap_max(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	पूर्णांक limit_type = to_sensor_dev_attr(attr)->index;
	uपूर्णांक32_t limit = limit_type << 24;
	uपूर्णांक32_t max_limit = 0;
	sमाप_प्रकार size;
	पूर्णांक r;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	अगर (is_support_sw_smu(adev)) अणु
		smu_get_घातer_limit(&adev->smu, &limit, SMU_PPT_LIMIT_MAX);
		size = snम_लिखो(buf, PAGE_SIZE, "%u\n", limit * 1000000);
	पूर्ण अन्यथा अगर (pp_funcs && pp_funcs->get_घातer_limit) अणु
		pp_funcs->get_घातer_limit(adev->घातerplay.pp_handle,
				&limit, &max_limit, true);
		size = snम_लिखो(buf, PAGE_SIZE, "%u\n", max_limit * 1000000);
	पूर्ण अन्यथा अणु
		size = snम_लिखो(buf, PAGE_SIZE, "\n");
	पूर्ण

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	वापस size;
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_show_घातer_cap(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	पूर्णांक limit_type = to_sensor_dev_attr(attr)->index;
	uपूर्णांक32_t limit = limit_type << 24;
	sमाप_प्रकार size;
	पूर्णांक r;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	अगर (is_support_sw_smu(adev)) अणु
		smu_get_घातer_limit(&adev->smu, &limit, SMU_PPT_LIMIT_CURRENT);
		size = snम_लिखो(buf, PAGE_SIZE, "%u\n", limit * 1000000);
	पूर्ण अन्यथा अगर (pp_funcs && pp_funcs->get_घातer_limit) अणु
		pp_funcs->get_घातer_limit(adev->घातerplay.pp_handle,
				&limit, शून्य, false);
		size = snम_लिखो(buf, PAGE_SIZE, "%u\n", limit * 1000000);
	पूर्ण अन्यथा अणु
		size = snम_लिखो(buf, PAGE_SIZE, "\n");
	पूर्ण

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	वापस size;
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_show_घातer_cap_शेष(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	पूर्णांक limit_type = to_sensor_dev_attr(attr)->index;
	uपूर्णांक32_t limit = limit_type << 24;
	sमाप_प्रकार size;
	पूर्णांक r;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	अगर (is_support_sw_smu(adev)) अणु
		smu_get_घातer_limit(&adev->smu, &limit, SMU_PPT_LIMIT_DEFAULT);
		size = snम_लिखो(buf, PAGE_SIZE, "%u\n", limit * 1000000);
	पूर्ण अन्यथा अगर (pp_funcs && pp_funcs->get_घातer_limit) अणु
		pp_funcs->get_घातer_limit(adev->घातerplay.pp_handle,
				&limit, शून्य, true);
		size = snम_लिखो(buf, PAGE_SIZE, "%u\n", limit * 1000000);
	पूर्ण अन्यथा अणु
		size = snम_लिखो(buf, PAGE_SIZE, "\n");
	पूर्ण

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	वापस size;
पूर्ण
अटल sमाप_प्रकार amdgpu_hwmon_show_घातer_label(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	पूर्णांक limit_type = to_sensor_dev_attr(attr)->index;

	वापस sysfs_emit(buf, "%s\n",
		limit_type == SMU_FAST_PPT_LIMIT ? "fastPPT" : "slowPPT");
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_set_घातer_cap(काष्ठा device *dev,
		काष्ठा device_attribute *attr,
		स्थिर अक्षर *buf,
		माप_प्रकार count)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	पूर्णांक limit_type = to_sensor_dev_attr(attr)->index;
	पूर्णांक err;
	u32 value;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	अगर (amdgpu_sriov_vf(adev))
		वापस -EINVAL;

	err = kstrtou32(buf, 10, &value);
	अगर (err)
		वापस err;

	value = value / 1000000; /* convert to Watt */
	value |= limit_type << 24;

	err = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (err < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस err;
	पूर्ण

	अगर (pp_funcs && pp_funcs->set_घातer_limit)
		err = pp_funcs->set_घातer_limit(adev->घातerplay.pp_handle, value);
	अन्यथा
		err = -EINVAL;

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	अगर (err)
		वापस err;

	वापस count;
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_show_sclk(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	uपूर्णांक32_t sclk;
	पूर्णांक r, size = माप(sclk);

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	/* get the sclk */
	r = amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_GFX_SCLK,
				   (व्योम *)&sclk, &size);

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	अगर (r)
		वापस r;

	वापस sysfs_emit(buf, "%u\n", sclk * 10 * 1000);
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_show_sclk_label(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "sclk\n");
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_show_mclk(काष्ठा device *dev,
				      काष्ठा device_attribute *attr,
				      अक्षर *buf)
अणु
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	uपूर्णांक32_t mclk;
	पूर्णांक r, size = माप(mclk);

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	r = pm_runसमय_get_sync(adev_to_drm(adev)->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
		वापस r;
	पूर्ण

	/* get the sclk */
	r = amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_GFX_MCLK,
				   (व्योम *)&mclk, &size);

	pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
	pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);

	अगर (r)
		वापस r;

	वापस sysfs_emit(buf, "%u\n", mclk * 10 * 1000);
पूर्ण

अटल sमाप_प्रकार amdgpu_hwmon_show_mclk_label(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "mclk\n");
पूर्ण

/**
 * DOC: hwmon
 *
 * The amdgpu driver exposes the following sensor पूर्णांकerfaces:
 *
 * - GPU temperature (via the on-die sensor)
 *
 * - GPU voltage
 *
 * - Northbridge voltage (APUs only)
 *
 * - GPU घातer
 *
 * - GPU fan
 *
 * - GPU gfx/compute engine घड़ी
 *
 * - GPU memory घड़ी (dGPU only)
 *
 * hwmon पूर्णांकerfaces क्रम GPU temperature:
 *
 * - temp[1-3]_input: the on die GPU temperature in millidegrees Celsius
 *   - temp2_input and temp3_input are supported on SOC15 dGPUs only
 *
 * - temp[1-3]_label: temperature channel label
 *   - temp2_label and temp3_label are supported on SOC15 dGPUs only
 *
 * - temp[1-3]_crit: temperature critical max value in millidegrees Celsius
 *   - temp2_crit and temp3_crit are supported on SOC15 dGPUs only
 *
 * - temp[1-3]_crit_hyst: temperature hysteresis क्रम critical limit in millidegrees Celsius
 *   - temp2_crit_hyst and temp3_crit_hyst are supported on SOC15 dGPUs only
 *
 * - temp[1-3]_emergency: temperature emergency max value(asic shutकरोwn) in millidegrees Celsius
 *   - these are supported on SOC15 dGPUs only
 *
 * hwmon पूर्णांकerfaces क्रम GPU voltage:
 *
 * - in0_input: the voltage on the GPU in millivolts
 *
 * - in1_input: the voltage on the Northbridge in millivolts
 *
 * hwmon पूर्णांकerfaces क्रम GPU घातer:
 *
 * - घातer1_average: average घातer used by the GPU in microWatts
 *
 * - घातer1_cap_min: minimum cap supported in microWatts
 *
 * - घातer1_cap_max: maximum cap supported in microWatts
 *
 * - घातer1_cap: selected घातer cap in microWatts
 *
 * hwmon पूर्णांकerfaces क्रम GPU fan:
 *
 * - pwm1: pulse width modulation fan level (0-255)
 *
 * - pwm1_enable: pulse width modulation fan control method (0: no fan speed control, 1: manual fan speed control using pwm पूर्णांकerface, 2: स्वतःmatic fan speed control)
 *
 * - pwm1_min: pulse width modulation fan control minimum level (0)
 *
 * - pwm1_max: pulse width modulation fan control maximum level (255)
 *
 * - fan1_min: a minimum value Unit: revolution/min (RPM)
 *
 * - fan1_max: a maximum value Unit: revolution/max (RPM)
 *
 * - fan1_input: fan speed in RPM
 *
 * - fan[1-\*]_target: Desired fan speed Unit: revolution/min (RPM)
 *
 * - fan[1-\*]_enable: Enable or disable the sensors.1: Enable 0: Disable
 *
 * hwmon पूर्णांकerfaces क्रम GPU घड़ीs:
 *
 * - freq1_input: the gfx/compute घड़ी in hertz
 *
 * - freq2_input: the memory घड़ी in hertz
 *
 * You can use hwmon tools like sensors to view this inक्रमmation on your प्रणाली.
 *
 */

अटल SENSOR_DEVICE_ATTR(temp1_input, S_IRUGO, amdgpu_hwmon_show_temp, शून्य, PP_TEMP_EDGE);
अटल SENSOR_DEVICE_ATTR(temp1_crit, S_IRUGO, amdgpu_hwmon_show_temp_thresh, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(temp1_crit_hyst, S_IRUGO, amdgpu_hwmon_show_temp_thresh, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(temp1_emergency, S_IRUGO, amdgpu_hwmon_show_temp_emergency, शून्य, PP_TEMP_EDGE);
अटल SENSOR_DEVICE_ATTR(temp2_input, S_IRUGO, amdgpu_hwmon_show_temp, शून्य, PP_TEMP_JUNCTION);
अटल SENSOR_DEVICE_ATTR(temp2_crit, S_IRUGO, amdgpu_hwmon_show_hotspot_temp_thresh, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(temp2_crit_hyst, S_IRUGO, amdgpu_hwmon_show_hotspot_temp_thresh, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(temp2_emergency, S_IRUGO, amdgpu_hwmon_show_temp_emergency, शून्य, PP_TEMP_JUNCTION);
अटल SENSOR_DEVICE_ATTR(temp3_input, S_IRUGO, amdgpu_hwmon_show_temp, शून्य, PP_TEMP_MEM);
अटल SENSOR_DEVICE_ATTR(temp3_crit, S_IRUGO, amdgpu_hwmon_show_mem_temp_thresh, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(temp3_crit_hyst, S_IRUGO, amdgpu_hwmon_show_mem_temp_thresh, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(temp3_emergency, S_IRUGO, amdgpu_hwmon_show_temp_emergency, शून्य, PP_TEMP_MEM);
अटल SENSOR_DEVICE_ATTR(temp1_label, S_IRUGO, amdgpu_hwmon_show_temp_label, शून्य, PP_TEMP_EDGE);
अटल SENSOR_DEVICE_ATTR(temp2_label, S_IRUGO, amdgpu_hwmon_show_temp_label, शून्य, PP_TEMP_JUNCTION);
अटल SENSOR_DEVICE_ATTR(temp3_label, S_IRUGO, amdgpu_hwmon_show_temp_label, शून्य, PP_TEMP_MEM);
अटल SENSOR_DEVICE_ATTR(pwm1, S_IRUGO | S_IWUSR, amdgpu_hwmon_get_pwm1, amdgpu_hwmon_set_pwm1, 0);
अटल SENSOR_DEVICE_ATTR(pwm1_enable, S_IRUGO | S_IWUSR, amdgpu_hwmon_get_pwm1_enable, amdgpu_hwmon_set_pwm1_enable, 0);
अटल SENSOR_DEVICE_ATTR(pwm1_min, S_IRUGO, amdgpu_hwmon_get_pwm1_min, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(pwm1_max, S_IRUGO, amdgpu_hwmon_get_pwm1_max, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(fan1_input, S_IRUGO, amdgpu_hwmon_get_fan1_input, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(fan1_min, S_IRUGO, amdgpu_hwmon_get_fan1_min, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(fan1_max, S_IRUGO, amdgpu_hwmon_get_fan1_max, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(fan1_target, S_IRUGO | S_IWUSR, amdgpu_hwmon_get_fan1_target, amdgpu_hwmon_set_fan1_target, 0);
अटल SENSOR_DEVICE_ATTR(fan1_enable, S_IRUGO | S_IWUSR, amdgpu_hwmon_get_fan1_enable, amdgpu_hwmon_set_fan1_enable, 0);
अटल SENSOR_DEVICE_ATTR(in0_input, S_IRUGO, amdgpu_hwmon_show_vddgfx, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(in0_label, S_IRUGO, amdgpu_hwmon_show_vddgfx_label, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(in1_input, S_IRUGO, amdgpu_hwmon_show_vddnb, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(in1_label, S_IRUGO, amdgpu_hwmon_show_vddnb_label, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(घातer1_average, S_IRUGO, amdgpu_hwmon_show_घातer_avg, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(घातer1_cap_max, S_IRUGO, amdgpu_hwmon_show_घातer_cap_max, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(घातer1_cap_min, S_IRUGO, amdgpu_hwmon_show_घातer_cap_min, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(घातer1_cap, S_IRUGO | S_IWUSR, amdgpu_hwmon_show_घातer_cap, amdgpu_hwmon_set_घातer_cap, 0);
अटल SENSOR_DEVICE_ATTR(घातer1_cap_शेष, S_IRUGO, amdgpu_hwmon_show_घातer_cap_शेष, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(घातer1_label, S_IRUGO, amdgpu_hwmon_show_घातer_label, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(घातer2_average, S_IRUGO, amdgpu_hwmon_show_घातer_avg, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(घातer2_cap_max, S_IRUGO, amdgpu_hwmon_show_घातer_cap_max, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(घातer2_cap_min, S_IRUGO, amdgpu_hwmon_show_घातer_cap_min, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(घातer2_cap, S_IRUGO | S_IWUSR, amdgpu_hwmon_show_घातer_cap, amdgpu_hwmon_set_घातer_cap, 1);
अटल SENSOR_DEVICE_ATTR(घातer2_cap_शेष, S_IRUGO, amdgpu_hwmon_show_घातer_cap_शेष, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(घातer2_label, S_IRUGO, amdgpu_hwmon_show_घातer_label, शून्य, 1);
अटल SENSOR_DEVICE_ATTR(freq1_input, S_IRUGO, amdgpu_hwmon_show_sclk, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(freq1_label, S_IRUGO, amdgpu_hwmon_show_sclk_label, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(freq2_input, S_IRUGO, amdgpu_hwmon_show_mclk, शून्य, 0);
अटल SENSOR_DEVICE_ATTR(freq2_label, S_IRUGO, amdgpu_hwmon_show_mclk_label, शून्य, 0);

अटल काष्ठा attribute *hwmon_attributes[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_crit.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_hyst.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_crit.dev_attr.attr,
	&sensor_dev_attr_temp2_crit_hyst.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp3_crit.dev_attr.attr,
	&sensor_dev_attr_temp3_crit_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_emergency.dev_attr.attr,
	&sensor_dev_attr_temp2_emergency.dev_attr.attr,
	&sensor_dev_attr_temp3_emergency.dev_attr.attr,
	&sensor_dev_attr_temp1_label.dev_attr.attr,
	&sensor_dev_attr_temp2_label.dev_attr.attr,
	&sensor_dev_attr_temp3_label.dev_attr.attr,
	&sensor_dev_attr_pwm1.dev_attr.attr,
	&sensor_dev_attr_pwm1_enable.dev_attr.attr,
	&sensor_dev_attr_pwm1_min.dev_attr.attr,
	&sensor_dev_attr_pwm1_max.dev_attr.attr,
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan1_min.dev_attr.attr,
	&sensor_dev_attr_fan1_max.dev_attr.attr,
	&sensor_dev_attr_fan1_target.dev_attr.attr,
	&sensor_dev_attr_fan1_enable.dev_attr.attr,
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in0_label.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_label.dev_attr.attr,
	&sensor_dev_attr_घातer1_average.dev_attr.attr,
	&sensor_dev_attr_घातer1_cap_max.dev_attr.attr,
	&sensor_dev_attr_घातer1_cap_min.dev_attr.attr,
	&sensor_dev_attr_घातer1_cap.dev_attr.attr,
	&sensor_dev_attr_घातer1_cap_शेष.dev_attr.attr,
	&sensor_dev_attr_घातer1_label.dev_attr.attr,
	&sensor_dev_attr_घातer2_average.dev_attr.attr,
	&sensor_dev_attr_घातer2_cap_max.dev_attr.attr,
	&sensor_dev_attr_घातer2_cap_min.dev_attr.attr,
	&sensor_dev_attr_घातer2_cap.dev_attr.attr,
	&sensor_dev_attr_घातer2_cap_शेष.dev_attr.attr,
	&sensor_dev_attr_घातer2_label.dev_attr.attr,
	&sensor_dev_attr_freq1_input.dev_attr.attr,
	&sensor_dev_attr_freq1_label.dev_attr.attr,
	&sensor_dev_attr_freq2_input.dev_attr.attr,
	&sensor_dev_attr_freq2_label.dev_attr.attr,
	शून्य
पूर्ण;

अटल umode_t hwmon_attributes_visible(काष्ठा kobject *kobj,
					काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा amdgpu_device *adev = dev_get_drvdata(dev);
	umode_t effective_mode = attr->mode;

	/* under multi-vf mode, the hwmon attributes are all not supported */
	अगर (amdgpu_sriov_vf(adev) && !amdgpu_sriov_is_pp_one_vf(adev))
		वापस 0;

	/* there is no fan under pp one vf mode */
	अगर (amdgpu_sriov_is_pp_one_vf(adev) &&
	    (attr == &sensor_dev_attr_pwm1.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_enable.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_max.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_min.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_input.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_min.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_max.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_target.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_enable.dev_attr.attr))
		वापस 0;

	/* Skip fan attributes अगर fan is not present */
	अगर (adev->pm.no_fan && (attr == &sensor_dev_attr_pwm1.dev_attr.attr ||
	    attr == &sensor_dev_attr_pwm1_enable.dev_attr.attr ||
	    attr == &sensor_dev_attr_pwm1_max.dev_attr.attr ||
	    attr == &sensor_dev_attr_pwm1_min.dev_attr.attr ||
	    attr == &sensor_dev_attr_fan1_input.dev_attr.attr ||
	    attr == &sensor_dev_attr_fan1_min.dev_attr.attr ||
	    attr == &sensor_dev_attr_fan1_max.dev_attr.attr ||
	    attr == &sensor_dev_attr_fan1_target.dev_attr.attr ||
	    attr == &sensor_dev_attr_fan1_enable.dev_attr.attr))
		वापस 0;

	/* Skip fan attributes on APU */
	अगर ((adev->flags & AMD_IS_APU) &&
	    (attr == &sensor_dev_attr_pwm1.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_enable.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_max.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_min.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_input.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_min.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_max.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_target.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_enable.dev_attr.attr))
		वापस 0;

	/* Skip crit temp on APU */
	अगर ((adev->flags & AMD_IS_APU) && (adev->family >= AMDGPU_FAMILY_CZ) &&
	    (attr == &sensor_dev_attr_temp1_crit.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp1_crit_hyst.dev_attr.attr))
		वापस 0;

	/* Skip limit attributes अगर DPM is not enabled */
	अगर (!adev->pm.dpm_enabled &&
	    (attr == &sensor_dev_attr_temp1_crit.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp1_crit_hyst.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_enable.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_max.dev_attr.attr ||
	     attr == &sensor_dev_attr_pwm1_min.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_input.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_min.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_max.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_target.dev_attr.attr ||
	     attr == &sensor_dev_attr_fan1_enable.dev_attr.attr))
		वापस 0;

	अगर (!is_support_sw_smu(adev)) अणु
		/* mask fan attributes अगर we have no bindings क्रम this asic to expose */
		अगर ((!adev->घातerplay.pp_funcs->get_fan_speed_percent &&
		     attr == &sensor_dev_attr_pwm1.dev_attr.attr) || /* can't query fan */
		    (!adev->घातerplay.pp_funcs->get_fan_control_mode &&
		     attr == &sensor_dev_attr_pwm1_enable.dev_attr.attr)) /* can't query state */
			effective_mode &= ~S_IRUGO;

		अगर ((!adev->घातerplay.pp_funcs->set_fan_speed_percent &&
		     attr == &sensor_dev_attr_pwm1.dev_attr.attr) || /* can't manage fan */
		    (!adev->घातerplay.pp_funcs->set_fan_control_mode &&
		     attr == &sensor_dev_attr_pwm1_enable.dev_attr.attr)) /* can't manage state */
			effective_mode &= ~S_IWUSR;
	पूर्ण

	अगर (((adev->family == AMDGPU_FAMILY_SI) ||
		 ((adev->flags & AMD_IS_APU) &&
	      (adev->asic_type != CHIP_VANGOGH))) &&	/* not implemented yet */
	    (attr == &sensor_dev_attr_घातer1_cap_max.dev_attr.attr ||
	     attr == &sensor_dev_attr_घातer1_cap_min.dev_attr.attr||
	     attr == &sensor_dev_attr_घातer1_cap.dev_attr.attr ||
	     attr == &sensor_dev_attr_घातer1_cap_शेष.dev_attr.attr))
		वापस 0;

	अगर (((adev->family == AMDGPU_FAMILY_SI) ||
	     ((adev->flags & AMD_IS_APU) &&
	      (adev->asic_type < CHIP_RENOIR))) &&	/* not implemented yet */
	    (attr == &sensor_dev_attr_घातer1_average.dev_attr.attr))
		वापस 0;

	अगर (!is_support_sw_smu(adev)) अणु
		/* hide max/min values अगर we can't both query and manage the fan */
		अगर ((!adev->घातerplay.pp_funcs->set_fan_speed_percent &&
		     !adev->घातerplay.pp_funcs->get_fan_speed_percent) &&
		     (!adev->घातerplay.pp_funcs->set_fan_speed_rpm &&
		     !adev->घातerplay.pp_funcs->get_fan_speed_rpm) &&
		    (attr == &sensor_dev_attr_pwm1_max.dev_attr.attr ||
		     attr == &sensor_dev_attr_pwm1_min.dev_attr.attr))
			वापस 0;

		अगर ((!adev->घातerplay.pp_funcs->set_fan_speed_rpm &&
		     !adev->घातerplay.pp_funcs->get_fan_speed_rpm) &&
		    (attr == &sensor_dev_attr_fan1_max.dev_attr.attr ||
		     attr == &sensor_dev_attr_fan1_min.dev_attr.attr))
			वापस 0;
	पूर्ण

	अगर ((adev->family == AMDGPU_FAMILY_SI ||	/* not implemented yet */
	     adev->family == AMDGPU_FAMILY_KV) &&	/* not implemented yet */
	    (attr == &sensor_dev_attr_in0_input.dev_attr.attr ||
	     attr == &sensor_dev_attr_in0_label.dev_attr.attr))
		वापस 0;

	/* only APUs have vddnb */
	अगर (!(adev->flags & AMD_IS_APU) &&
	    (attr == &sensor_dev_attr_in1_input.dev_attr.attr ||
	     attr == &sensor_dev_attr_in1_label.dev_attr.attr))
		वापस 0;

	/* no mclk on APUs */
	अगर ((adev->flags & AMD_IS_APU) &&
	    (attr == &sensor_dev_attr_freq2_input.dev_attr.attr ||
	     attr == &sensor_dev_attr_freq2_label.dev_attr.attr))
		वापस 0;

	/* only SOC15 dGPUs support hotspot and mem temperatures */
	अगर (((adev->flags & AMD_IS_APU) ||
	     adev->asic_type < CHIP_VEGA10) &&
	    (attr == &sensor_dev_attr_temp2_crit.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp2_crit_hyst.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp3_crit.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp3_crit_hyst.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp1_emergency.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp2_emergency.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp3_emergency.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp2_input.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp3_input.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp2_label.dev_attr.attr ||
	     attr == &sensor_dev_attr_temp3_label.dev_attr.attr))
		वापस 0;

	/* only Vangogh has fast PPT limit and घातer labels */
	अगर (!(adev->asic_type == CHIP_VANGOGH) &&
	    (attr == &sensor_dev_attr_घातer2_average.dev_attr.attr ||
		 attr == &sensor_dev_attr_घातer2_cap_max.dev_attr.attr ||
	     attr == &sensor_dev_attr_घातer2_cap_min.dev_attr.attr ||
		 attr == &sensor_dev_attr_घातer2_cap.dev_attr.attr ||
		 attr == &sensor_dev_attr_घातer2_cap_शेष.dev_attr.attr ||
		 attr == &sensor_dev_attr_घातer2_label.dev_attr.attr ||
		 attr == &sensor_dev_attr_घातer1_label.dev_attr.attr))
		वापस 0;

	वापस effective_mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group hwmon_attrgroup = अणु
	.attrs = hwmon_attributes,
	.is_visible = hwmon_attributes_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *hwmon_groups[] = अणु
	&hwmon_attrgroup,
	शून्य
पूर्ण;

पूर्णांक amdgpu_pm_sysfs_init(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक ret;
	uपूर्णांक32_t mask = 0;

	अगर (adev->pm.sysfs_initialized)
		वापस 0;

	अगर (adev->pm.dpm_enabled == 0)
		वापस 0;

	INIT_LIST_HEAD(&adev->pm.pm_attr_list);

	adev->pm.पूर्णांक_hwmon_dev = hwmon_device_रेजिस्टर_with_groups(adev->dev,
								   DRIVER_NAME, adev,
								   hwmon_groups);
	अगर (IS_ERR(adev->pm.पूर्णांक_hwmon_dev)) अणु
		ret = PTR_ERR(adev->pm.पूर्णांक_hwmon_dev);
		dev_err(adev->dev,
			"Unable to register hwmon device: %d\n", ret);
		वापस ret;
	पूर्ण

	चयन (amdgpu_virt_get_sriov_vf_mode(adev)) अणु
	हाल SRIOV_VF_MODE_ONE_VF:
		mask = ATTR_FLAG_ONEVF;
		अवरोध;
	हाल SRIOV_VF_MODE_MULTI_VF:
		mask = 0;
		अवरोध;
	हाल SRIOV_VF_MODE_BARE_METAL:
	शेष:
		mask = ATTR_FLAG_MASK_ALL;
		अवरोध;
	पूर्ण

	ret = amdgpu_device_attr_create_groups(adev,
					       amdgpu_device_attrs,
					       ARRAY_SIZE(amdgpu_device_attrs),
					       mask,
					       &adev->pm.pm_attr_list);
	अगर (ret)
		वापस ret;

	adev->pm.sysfs_initialized = true;

	वापस 0;
पूर्ण

व्योम amdgpu_pm_sysfs_fini(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->pm.dpm_enabled == 0)
		वापस;

	अगर (adev->pm.पूर्णांक_hwmon_dev)
		hwmon_device_unरेजिस्टर(adev->pm.पूर्णांक_hwmon_dev);

	amdgpu_device_attr_हटाओ_groups(adev, &adev->pm.pm_attr_list);
पूर्ण

/*
 * Debugfs info
 */
#अगर defined(CONFIG_DEBUG_FS)

अटल व्योम amdgpu_debugfs_prपूर्णांकs_cpu_info(काष्ठा seq_file *m,
					   काष्ठा amdgpu_device *adev) अणु
	uपूर्णांक16_t *p_val;
	uपूर्णांक32_t size;
	पूर्णांक i;

	अगर (is_support_cclk_dpm(adev)) अणु
		p_val = kसुस्मृति(adev->smu.cpu_core_num, माप(uपूर्णांक16_t),
				GFP_KERNEL);

		अगर (!amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_CPU_CLK,
					    (व्योम *)p_val, &size)) अणु
			क्रम (i = 0; i < adev->smu.cpu_core_num; i++)
				seq_म_लिखो(m, "\t%u MHz (CPU%d)\n",
					   *(p_val + i), i);
		पूर्ण

		kमुक्त(p_val);
	पूर्ण
पूर्ण

अटल पूर्णांक amdgpu_debugfs_pm_info_pp(काष्ठा seq_file *m, काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक32_t value;
	uपूर्णांक64_t value64 = 0;
	uपूर्णांक32_t query = 0;
	पूर्णांक size;

	/* GPU Clocks */
	size = माप(value);
	seq_म_लिखो(m, "GFX Clocks and Power:\n");

	amdgpu_debugfs_prपूर्णांकs_cpu_info(m, adev);

	अगर (!amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_GFX_MCLK, (व्योम *)&value, &size))
		seq_म_लिखो(m, "\t%u MHz (MCLK)\n", value/100);
	अगर (!amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_GFX_SCLK, (व्योम *)&value, &size))
		seq_म_लिखो(m, "\t%u MHz (SCLK)\n", value/100);
	अगर (!amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_STABLE_PSTATE_SCLK, (व्योम *)&value, &size))
		seq_म_लिखो(m, "\t%u MHz (PSTATE_SCLK)\n", value/100);
	अगर (!amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_STABLE_PSTATE_MCLK, (व्योम *)&value, &size))
		seq_म_लिखो(m, "\t%u MHz (PSTATE_MCLK)\n", value/100);
	अगर (!amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_VDDGFX, (व्योम *)&value, &size))
		seq_म_लिखो(m, "\t%u mV (VDDGFX)\n", value);
	अगर (!amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_VDDNB, (व्योम *)&value, &size))
		seq_म_लिखो(m, "\t%u mV (VDDNB)\n", value);
	size = माप(uपूर्णांक32_t);
	अगर (!amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_GPU_POWER, (व्योम *)&query, &size))
		seq_म_लिखो(m, "\t%u.%u W (average GPU)\n", query >> 8, query & 0xff);
	size = माप(value);
	seq_म_लिखो(m, "\n");

	/* GPU Temp */
	अगर (!amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_GPU_TEMP, (व्योम *)&value, &size))
		seq_म_लिखो(m, "GPU Temperature: %u C\n", value/1000);

	/* GPU Load */
	अगर (!amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_GPU_LOAD, (व्योम *)&value, &size))
		seq_म_लिखो(m, "GPU Load: %u %%\n", value);
	/* MEM Load */
	अगर (!amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_MEM_LOAD, (व्योम *)&value, &size))
		seq_म_लिखो(m, "MEM Load: %u %%\n", value);

	seq_म_लिखो(m, "\n");

	/* SMC feature mask */
	अगर (!amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_ENABLED_SMC_FEATURES_MASK, (व्योम *)&value64, &size))
		seq_म_लिखो(m, "SMC Feature Mask: 0x%016llx\n", value64);

	अगर (adev->asic_type > CHIP_VEGA20) अणु
		/* VCN घड़ीs */
		अगर (!amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_VCN_POWER_STATE, (व्योम *)&value, &size)) अणु
			अगर (!value) अणु
				seq_म_लिखो(m, "VCN: Disabled\n");
			पूर्ण अन्यथा अणु
				seq_म_लिखो(m, "VCN: Enabled\n");
				अगर (!amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_UVD_DCLK, (व्योम *)&value, &size))
					seq_म_लिखो(m, "\t%u MHz (DCLK)\n", value/100);
				अगर (!amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_UVD_VCLK, (व्योम *)&value, &size))
					seq_म_लिखो(m, "\t%u MHz (VCLK)\n", value/100);
			पूर्ण
		पूर्ण
		seq_म_लिखो(m, "\n");
	पूर्ण अन्यथा अणु
		/* UVD घड़ीs */
		अगर (!amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_UVD_POWER, (व्योम *)&value, &size)) अणु
			अगर (!value) अणु
				seq_म_लिखो(m, "UVD: Disabled\n");
			पूर्ण अन्यथा अणु
				seq_म_लिखो(m, "UVD: Enabled\n");
				अगर (!amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_UVD_DCLK, (व्योम *)&value, &size))
					seq_म_लिखो(m, "\t%u MHz (DCLK)\n", value/100);
				अगर (!amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_UVD_VCLK, (व्योम *)&value, &size))
					seq_म_लिखो(m, "\t%u MHz (VCLK)\n", value/100);
			पूर्ण
		पूर्ण
		seq_म_लिखो(m, "\n");

		/* VCE घड़ीs */
		अगर (!amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_VCE_POWER, (व्योम *)&value, &size)) अणु
			अगर (!value) अणु
				seq_म_लिखो(m, "VCE: Disabled\n");
			पूर्ण अन्यथा अणु
				seq_म_लिखो(m, "VCE: Enabled\n");
				अगर (!amdgpu_dpm_पढ़ो_sensor(adev, AMDGPU_PP_SENSOR_VCE_ECCLK, (व्योम *)&value, &size))
					seq_म_लिखो(m, "\t%u MHz (ECCLK)\n", value/100);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम amdgpu_parse_cg_state(काष्ठा seq_file *m, u32 flags)
अणु
	पूर्णांक i;

	क्रम (i = 0; घड़ीs[i].flag; i++)
		seq_म_लिखो(m, "\t%s: %s\n", घड़ीs[i].name,
			   (flags & घड़ीs[i].flag) ? "On" : "Off");
पूर्ण

अटल पूर्णांक amdgpu_debugfs_pm_info_show(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)m->निजी;
	काष्ठा drm_device *dev = adev_to_drm(adev);
	u32 flags = 0;
	पूर्णांक r;

	अगर (amdgpu_in_reset(adev))
		वापस -EPERM;
	अगर (adev->in_suspend && !adev->in_runpm)
		वापस -EPERM;

	r = pm_runसमय_get_sync(dev->dev);
	अगर (r < 0) अणु
		pm_runसमय_put_स्वतःsuspend(dev->dev);
		वापस r;
	पूर्ण

	अगर (!adev->pm.dpm_enabled) अणु
		seq_म_लिखो(m, "dpm not enabled\n");
		pm_runसमय_mark_last_busy(dev->dev);
		pm_runसमय_put_स्वतःsuspend(dev->dev);
		वापस 0;
	पूर्ण

	अगर (!is_support_sw_smu(adev) &&
	    adev->घातerplay.pp_funcs->debugfs_prपूर्णांक_current_perक्रमmance_level) अणु
		mutex_lock(&adev->pm.mutex);
		अगर (adev->घातerplay.pp_funcs->debugfs_prपूर्णांक_current_perक्रमmance_level)
			adev->घातerplay.pp_funcs->debugfs_prपूर्णांक_current_perक्रमmance_level(adev, m);
		अन्यथा
			seq_म_लिखो(m, "Debugfs support not implemented for this asic\n");
		mutex_unlock(&adev->pm.mutex);
		r = 0;
	पूर्ण अन्यथा अणु
		r = amdgpu_debugfs_pm_info_pp(m, adev);
	पूर्ण
	अगर (r)
		जाओ out;

	amdgpu_device_ip_get_घड़ीgating_state(adev, &flags);

	seq_म_लिखो(m, "Clock Gating Flags Mask: 0x%x\n", flags);
	amdgpu_parse_cg_state(m, flags);
	seq_म_लिखो(m, "\n");

out:
	pm_runसमय_mark_last_busy(dev->dev);
	pm_runसमय_put_स्वतःsuspend(dev->dev);

	वापस r;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(amdgpu_debugfs_pm_info);

#पूर्ण_अगर

व्योम amdgpu_debugfs_pm_init(काष्ठा amdgpu_device *adev)
अणु
#अगर defined(CONFIG_DEBUG_FS)
	काष्ठा drm_minor *minor = adev_to_drm(adev)->primary;
	काष्ठा dentry *root = minor->debugfs_root;

	debugfs_create_file("amdgpu_pm_info", 0444, root, adev,
			    &amdgpu_debugfs_pm_info_fops);

#पूर्ण_अगर
पूर्ण
