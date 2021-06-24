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
 */

#घोषणा SWSMU_CODE_LAYER_L1

#समावेश <linux/firmware.h>
#समावेश <linux/pci.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_smu.h"
#समावेश "smu_internal.h"
#समावेश "atom.h"
#समावेश "arcturus_ppt.h"
#समावेश "navi10_ppt.h"
#समावेश "sienna_cichlid_ppt.h"
#समावेश "renoir_ppt.h"
#समावेश "vangogh_ppt.h"
#समावेश "aldebaran_ppt.h"
#समावेश "amd_pcie.h"

/*
 * DO NOT use these क्रम err/warn/info/debug messages.
 * Use dev_err, dev_warn, dev_info and dev_dbg instead.
 * They are more MGPU मित्रly.
 */
#अघोषित pr_err
#अघोषित pr_warn
#अघोषित pr_info
#अघोषित pr_debug

अटल स्थिर काष्ठा amd_pm_funcs swsmu_pm_funcs;
अटल पूर्णांक smu_क्रमce_smuclk_levels(काष्ठा smu_context *smu,
				   क्रमागत smu_clk_type clk_type,
				   uपूर्णांक32_t mask);
अटल पूर्णांक smu_handle_task(काष्ठा smu_context *smu,
			   क्रमागत amd_dpm_क्रमced_level level,
			   क्रमागत amd_pp_task task_id,
			   bool lock_needed);
अटल पूर्णांक smu_reset(काष्ठा smu_context *smu);
अटल पूर्णांक smu_set_fan_speed_percent(व्योम *handle, u32 speed);
अटल पूर्णांक smu_set_fan_control_mode(काष्ठा smu_context *smu, पूर्णांक value);
अटल पूर्णांक smu_set_घातer_limit(व्योम *handle, uपूर्णांक32_t limit);
अटल पूर्णांक smu_set_fan_speed_rpm(व्योम *handle, uपूर्णांक32_t speed);
अटल पूर्णांक smu_set_gfx_cgpg(काष्ठा smu_context *smu, bool enabled);

अटल पूर्णांक smu_sys_get_pp_feature_mask(व्योम *handle,
				       अक्षर *buf)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक size = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	size = smu_get_pp_feature_mask(smu, buf);

	mutex_unlock(&smu->mutex);

	वापस size;
पूर्ण

अटल पूर्णांक smu_sys_set_pp_feature_mask(व्योम *handle,
				       uपूर्णांक64_t new_mask)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	ret = smu_set_pp_feature_mask(smu, new_mask);

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

पूर्णांक smu_get_status_gfxoff(काष्ठा amdgpu_device *adev, uपूर्णांक32_t *value)
अणु
	पूर्णांक ret = 0;
	काष्ठा smu_context *smu = &adev->smu;

	अगर (is_support_sw_smu(adev) && smu->ppt_funcs->get_gfx_off_status)
		*value = smu_get_gfx_off_status(smu);
	अन्यथा
		ret = -EINVAL;

	वापस ret;
पूर्ण

पूर्णांक smu_set_soft_freq_range(काष्ठा smu_context *smu,
			    क्रमागत smu_clk_type clk_type,
			    uपूर्णांक32_t min,
			    uपूर्णांक32_t max)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->set_soft_freq_limited_range)
		ret = smu->ppt_funcs->set_soft_freq_limited_range(smu,
								  clk_type,
								  min,
								  max);

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

पूर्णांक smu_get_dpm_freq_range(काष्ठा smu_context *smu,
			   क्रमागत smu_clk_type clk_type,
			   uपूर्णांक32_t *min,
			   uपूर्णांक32_t *max)
अणु
	पूर्णांक ret = 0;

	अगर (!min && !max)
		वापस -EINVAL;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->get_dpm_ultimate_freq)
		ret = smu->ppt_funcs->get_dpm_ultimate_freq(smu,
							    clk_type,
							    min,
							    max);

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल u32 smu_get_mclk(व्योम *handle, bool low)
अणु
	काष्ठा smu_context *smu = handle;
	uपूर्णांक32_t clk_freq;
	पूर्णांक ret = 0;

	ret = smu_get_dpm_freq_range(smu, SMU_UCLK,
				     low ? &clk_freq : शून्य,
				     !low ? &clk_freq : शून्य);
	अगर (ret)
		वापस 0;
	वापस clk_freq * 100;
पूर्ण

अटल u32 smu_get_sclk(व्योम *handle, bool low)
अणु
	काष्ठा smu_context *smu = handle;
	uपूर्णांक32_t clk_freq;
	पूर्णांक ret = 0;

	ret = smu_get_dpm_freq_range(smu, SMU_GFXCLK,
				     low ? &clk_freq : शून्य,
				     !low ? &clk_freq : शून्य);
	अगर (ret)
		वापस 0;
	वापस clk_freq * 100;
पूर्ण

अटल पूर्णांक smu_dpm_set_vcn_enable_locked(काष्ठा smu_context *smu,
					 bool enable)
अणु
	काष्ठा smu_घातer_context *smu_घातer = &smu->smu_घातer;
	काष्ठा smu_घातer_gate *घातer_gate = &smu_घातer->घातer_gate;
	पूर्णांक ret = 0;

	अगर (!smu->ppt_funcs->dpm_set_vcn_enable)
		वापस 0;

	अगर (atomic_पढ़ो(&घातer_gate->vcn_gated) ^ enable)
		वापस 0;

	ret = smu->ppt_funcs->dpm_set_vcn_enable(smu, enable);
	अगर (!ret)
		atomic_set(&घातer_gate->vcn_gated, !enable);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_dpm_set_vcn_enable(काष्ठा smu_context *smu,
				  bool enable)
अणु
	काष्ठा smu_घातer_context *smu_घातer = &smu->smu_घातer;
	काष्ठा smu_घातer_gate *घातer_gate = &smu_घातer->घातer_gate;
	पूर्णांक ret = 0;

	mutex_lock(&घातer_gate->vcn_gate_lock);

	ret = smu_dpm_set_vcn_enable_locked(smu, enable);

	mutex_unlock(&घातer_gate->vcn_gate_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_dpm_set_jpeg_enable_locked(काष्ठा smu_context *smu,
					  bool enable)
अणु
	काष्ठा smu_घातer_context *smu_घातer = &smu->smu_घातer;
	काष्ठा smu_घातer_gate *घातer_gate = &smu_घातer->घातer_gate;
	पूर्णांक ret = 0;

	अगर (!smu->ppt_funcs->dpm_set_jpeg_enable)
		वापस 0;

	अगर (atomic_पढ़ो(&घातer_gate->jpeg_gated) ^ enable)
		वापस 0;

	ret = smu->ppt_funcs->dpm_set_jpeg_enable(smu, enable);
	अगर (!ret)
		atomic_set(&घातer_gate->jpeg_gated, !enable);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_dpm_set_jpeg_enable(काष्ठा smu_context *smu,
				   bool enable)
अणु
	काष्ठा smu_घातer_context *smu_घातer = &smu->smu_घातer;
	काष्ठा smu_घातer_gate *घातer_gate = &smu_घातer->घातer_gate;
	पूर्णांक ret = 0;

	mutex_lock(&घातer_gate->jpeg_gate_lock);

	ret = smu_dpm_set_jpeg_enable_locked(smu, enable);

	mutex_unlock(&घातer_gate->jpeg_gate_lock);

	वापस ret;
पूर्ण

/**
 * smu_dpm_set_घातer_gate - घातer gate/ungate the specअगरic IP block
 *
 * @handle:        smu_context poपूर्णांकer
 * @block_type: the IP block to घातer gate/ungate
 * @gate:       to घातer gate अगर true, ungate otherwise
 *
 * This API uses no smu->mutex lock protection due to:
 * 1. It is either called by other IP block(gfx/sdma/vcn/uvd/vce).
 *    This is guarded to be race condition मुक्त by the caller.
 * 2. Or get called on user setting request of घातer_dpm_क्रमce_perक्रमmance_level.
 *    Under this हाल, the smu->mutex lock protection is alपढ़ोy enक्रमced on
 *    the parent API smu_क्रमce_perक्रमmance_level of the call path.
 */
अटल पूर्णांक smu_dpm_set_घातer_gate(व्योम *handle,
				  uपूर्णांक32_t block_type,
				  bool gate)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	चयन (block_type) अणु
	/*
	 * Some legacy code of amdgpu_vcn.c and vcn_v2*.c still uses
	 * AMD_IP_BLOCK_TYPE_UVD क्रम VCN. So, here both of them are kept.
	 */
	हाल AMD_IP_BLOCK_TYPE_UVD:
	हाल AMD_IP_BLOCK_TYPE_VCN:
		ret = smu_dpm_set_vcn_enable(smu, !gate);
		अगर (ret)
			dev_err(smu->adev->dev, "Failed to power %s VCN!\n",
				gate ? "gate" : "ungate");
		अवरोध;
	हाल AMD_IP_BLOCK_TYPE_GFX:
		ret = smu_gfx_off_control(smu, gate);
		अगर (ret)
			dev_err(smu->adev->dev, "Failed to %s gfxoff!\n",
				gate ? "enable" : "disable");
		अवरोध;
	हाल AMD_IP_BLOCK_TYPE_SDMA:
		ret = smu_घातergate_sdma(smu, gate);
		अगर (ret)
			dev_err(smu->adev->dev, "Failed to power %s SDMA!\n",
				gate ? "gate" : "ungate");
		अवरोध;
	हाल AMD_IP_BLOCK_TYPE_JPEG:
		ret = smu_dpm_set_jpeg_enable(smu, !gate);
		अगर (ret)
			dev_err(smu->adev->dev, "Failed to power %s JPEG!\n",
				gate ? "gate" : "ungate");
		अवरोध;
	शेष:
		dev_err(smu->adev->dev, "Unsupported block type!\n");
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * smu_set_user_clk_dependencies - set user profile घड़ी dependencies
 *
 * @smu:	smu_context poपूर्णांकer
 * @clk:	क्रमागत smu_clk_type type
 *
 * Enable/Disable the घड़ी dependency क्रम the @clk type.
 */
अटल व्योम smu_set_user_clk_dependencies(काष्ठा smu_context *smu, क्रमागत smu_clk_type clk)
अणु
	अगर (smu->adev->in_suspend)
		वापस;

	अगर (clk == SMU_MCLK) अणु
		smu->user_dpm_profile.clk_dependency = 0;
		smu->user_dpm_profile.clk_dependency = BIT(SMU_FCLK) | BIT(SMU_SOCCLK);
	पूर्ण अन्यथा अगर (clk == SMU_FCLK) अणु
		/* MCLK takes precedence over FCLK */
		अगर (smu->user_dpm_profile.clk_dependency == (BIT(SMU_FCLK) | BIT(SMU_SOCCLK)))
			वापस;

		smu->user_dpm_profile.clk_dependency = 0;
		smu->user_dpm_profile.clk_dependency = BIT(SMU_MCLK) | BIT(SMU_SOCCLK);
	पूर्ण अन्यथा अगर (clk == SMU_SOCCLK) अणु
		/* MCLK takes precedence over SOCCLK */
		अगर (smu->user_dpm_profile.clk_dependency == (BIT(SMU_FCLK) | BIT(SMU_SOCCLK)))
			वापस;

		smu->user_dpm_profile.clk_dependency = 0;
		smu->user_dpm_profile.clk_dependency = BIT(SMU_MCLK) | BIT(SMU_FCLK);
	पूर्ण अन्यथा
		/* Add clk dependencies here, अगर any */
		वापस;
पूर्ण

/**
 * smu_restore_dpm_user_profile - reinstate user dpm profile
 *
 * @smu:	smu_context poपूर्णांकer
 *
 * Restore the saved user घातer configurations include घातer limit,
 * घड़ी frequencies, fan control mode and fan speed.
 */
अटल व्योम smu_restore_dpm_user_profile(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);
	पूर्णांक ret = 0;

	अगर (!smu->adev->in_suspend)
		वापस;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस;

	/* Enable restore flag */
	smu->user_dpm_profile.flags |= SMU_DPM_USER_PROखाता_RESTORE;

	/* set the user dpm घातer limit */
	अगर (smu->user_dpm_profile.घातer_limit) अणु
		ret = smu_set_घातer_limit(smu, smu->user_dpm_profile.घातer_limit);
		अगर (ret)
			dev_err(smu->adev->dev, "Failed to set power limit value\n");
	पूर्ण

	/* set the user dpm घड़ी configurations */
	अगर (smu_dpm_ctx->dpm_level == AMD_DPM_FORCED_LEVEL_MANUAL) अणु
		क्रमागत smu_clk_type clk_type;

		क्रम (clk_type = 0; clk_type < SMU_CLK_COUNT; clk_type++) अणु
			/*
			 * Iterate over smu clk type and क्रमce the saved user clk
			 * configs, skip अगर घड़ी dependency is enabled
			 */
			अगर (!(smu->user_dpm_profile.clk_dependency & BIT(clk_type)) &&
					smu->user_dpm_profile.clk_mask[clk_type]) अणु
				ret = smu_क्रमce_smuclk_levels(smu, clk_type,
						smu->user_dpm_profile.clk_mask[clk_type]);
				अगर (ret)
					dev_err(smu->adev->dev,
						"Failed to set clock type = %d\n", clk_type);
			पूर्ण
		पूर्ण
	पूर्ण

	/* set the user dpm fan configurations */
	अगर (smu->user_dpm_profile.fan_mode == AMD_FAN_CTRL_MANUAL) अणु
		ret = smu_set_fan_control_mode(smu, smu->user_dpm_profile.fan_mode);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Failed to set manual fan control mode\n");
			वापस;
		पूर्ण

		अगर (!ret && smu->user_dpm_profile.fan_speed_percent) अणु
			ret = smu_set_fan_speed_percent(smu, smu->user_dpm_profile.fan_speed_percent);
			अगर (ret)
				dev_err(smu->adev->dev, "Failed to set manual fan speed\n");
		पूर्ण
	पूर्ण

	/* Disable restore flag */
	smu->user_dpm_profile.flags &= ~SMU_DPM_USER_PROखाता_RESTORE;
पूर्ण

अटल पूर्णांक smu_get_घातer_num_states(व्योम *handle,
				    काष्ठा pp_states_info *state_info)
अणु
	अगर (!state_info)
		वापस -EINVAL;

	/* not support घातer state */
	स_रखो(state_info, 0, माप(काष्ठा pp_states_info));
	state_info->nums = 1;
	state_info->states[0] = POWER_STATE_TYPE_DEFAULT;

	वापस 0;
पूर्ण

bool is_support_sw_smu(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->asic_type >= CHIP_ARCTURUS)
		वापस true;

	वापस false;
पूर्ण

bool is_support_cclk_dpm(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा smu_context *smu = &adev->smu;

	अगर (!is_support_sw_smu(adev))
		वापस false;

	अगर (!smu_feature_is_enabled(smu, SMU_FEATURE_CCLK_DPM_BIT))
		वापस false;

	वापस true;
पूर्ण


अटल पूर्णांक smu_sys_get_pp_table(व्योम *handle,
				अक्षर **table)
अणु
	काष्ठा smu_context *smu = handle;
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	uपूर्णांक32_t घातerplay_table_size;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	अगर (!smu_table->घातer_play_table && !smu_table->hardcode_pptable)
		वापस -EINVAL;

	mutex_lock(&smu->mutex);

	अगर (smu_table->hardcode_pptable)
		*table = smu_table->hardcode_pptable;
	अन्यथा
		*table = smu_table->घातer_play_table;

	घातerplay_table_size = smu_table->घातer_play_table_size;

	mutex_unlock(&smu->mutex);

	वापस घातerplay_table_size;
पूर्ण

अटल पूर्णांक smu_sys_set_pp_table(व्योम *handle,
				स्थिर अक्षर *buf,
				माप_प्रकार size)
अणु
	काष्ठा smu_context *smu = handle;
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	ATOM_COMMON_TABLE_HEADER *header = (ATOM_COMMON_TABLE_HEADER *)buf;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	अगर (header->usStructureSize != size) अणु
		dev_err(smu->adev->dev, "pp table size not matched !\n");
		वापस -EIO;
	पूर्ण

	mutex_lock(&smu->mutex);
	अगर (!smu_table->hardcode_pptable)
		smu_table->hardcode_pptable = kzalloc(size, GFP_KERNEL);
	अगर (!smu_table->hardcode_pptable) अणु
		ret = -ENOMEM;
		जाओ failed;
	पूर्ण

	स_नकल(smu_table->hardcode_pptable, buf, size);
	smu_table->घातer_play_table = smu_table->hardcode_pptable;
	smu_table->घातer_play_table_size = size;

	/*
	 * Special hw_fini action(क्रम Navi1x, the DPMs disablement will be
	 * skipped) may be needed क्रम custom pptable uploading.
	 */
	smu->uploading_custom_pp_table = true;

	ret = smu_reset(smu);
	अगर (ret)
		dev_info(smu->adev->dev, "smu reset failed, ret = %d\n", ret);

	smu->uploading_custom_pp_table = false;

failed:
	mutex_unlock(&smu->mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक smu_get_driver_allowed_feature_mask(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_feature *feature = &smu->smu_feature;
	पूर्णांक ret = 0;
	uपूर्णांक32_t allowed_feature_mask[SMU_FEATURE_MAX/32];

	biपंचांगap_zero(feature->allowed, SMU_FEATURE_MAX);

	ret = smu_get_allowed_feature_mask(smu, allowed_feature_mask,
					     SMU_FEATURE_MAX/32);
	अगर (ret)
		वापस ret;

	biपंचांगap_or(feature->allowed, feature->allowed,
		      (अचिन्हित दीर्घ *)allowed_feature_mask,
		      feature->feature_num);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_set_funcs(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा smu_context *smu = &adev->smu;

	अगर (adev->pm.pp_feature & PP_OVERDRIVE_MASK)
		smu->od_enabled = true;

	चयन (adev->asic_type) अणु
	हाल CHIP_NAVI10:
	हाल CHIP_NAVI14:
	हाल CHIP_NAVI12:
		navi10_set_ppt_funcs(smu);
		अवरोध;
	हाल CHIP_ARCTURUS:
		adev->pm.pp_feature &= ~PP_GFXOFF_MASK;
		arcturus_set_ppt_funcs(smu);
		/* OD is not supported on Arcturus */
		smu->od_enabled =false;
		अवरोध;
	हाल CHIP_SIENNA_CICHLID:
	हाल CHIP_NAVY_FLOUNDER:
	हाल CHIP_DIMGREY_CAVEFISH:
		sienna_cichlid_set_ppt_funcs(smu);
		अवरोध;
	हाल CHIP_ALDEBARAN:
		aldebaran_set_ppt_funcs(smu);
		/* Enable pp_od_clk_voltage node */
		smu->od_enabled = true;
		अवरोध;
	हाल CHIP_RENOIR:
		renoir_set_ppt_funcs(smu);
		अवरोध;
	हाल CHIP_VANGOGH:
		vangogh_set_ppt_funcs(smu);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu_early_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा smu_context *smu = &adev->smu;

	smu->adev = adev;
	smu->pm_enabled = !!amdgpu_dpm;
	smu->is_apu = false;
	mutex_init(&smu->mutex);
	mutex_init(&smu->smu_baco.mutex);
	smu->smu_baco.state = SMU_BACO_STATE_EXIT;
	smu->smu_baco.platक्रमm_support = false;

	adev->घातerplay.pp_handle = smu;
	adev->घातerplay.pp_funcs = &swsmu_pm_funcs;

	वापस smu_set_funcs(adev);
पूर्ण

अटल पूर्णांक smu_set_शेष_dpm_table(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_घातer_context *smu_घातer = &smu->smu_घातer;
	काष्ठा smu_घातer_gate *घातer_gate = &smu_घातer->घातer_gate;
	पूर्णांक vcn_gate, jpeg_gate;
	पूर्णांक ret = 0;

	अगर (!smu->ppt_funcs->set_शेष_dpm_table)
		वापस 0;

	mutex_lock(&घातer_gate->vcn_gate_lock);
	mutex_lock(&घातer_gate->jpeg_gate_lock);

	vcn_gate = atomic_पढ़ो(&घातer_gate->vcn_gated);
	jpeg_gate = atomic_पढ़ो(&घातer_gate->jpeg_gated);

	ret = smu_dpm_set_vcn_enable_locked(smu, true);
	अगर (ret)
		जाओ err0_out;

	ret = smu_dpm_set_jpeg_enable_locked(smu, true);
	अगर (ret)
		जाओ err1_out;

	ret = smu->ppt_funcs->set_शेष_dpm_table(smu);
	अगर (ret)
		dev_err(smu->adev->dev,
			"Failed to setup default dpm clock tables!\n");

	smu_dpm_set_jpeg_enable_locked(smu, !jpeg_gate);
err1_out:
	smu_dpm_set_vcn_enable_locked(smu, !vcn_gate);
err0_out:
	mutex_unlock(&घातer_gate->jpeg_gate_lock);
	mutex_unlock(&घातer_gate->vcn_gate_lock);

	वापस ret;
पूर्ण


अटल पूर्णांक smu_late_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा smu_context *smu = &adev->smu;
	पूर्णांक ret = 0;

	smu_set_fine_grain_gfx_freq_parameters(smu);

	अगर (!smu->pm_enabled)
		वापस 0;

	ret = smu_post_init(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to post smu init!\n");
		वापस ret;
	पूर्ण

	अगर (!amdgpu_sriov_vf(adev) || smu->od_enabled) अणु
		ret = smu_set_शेष_od_settings(smu);
		अगर (ret) अणु
			dev_err(adev->dev, "Failed to setup default OD settings!\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = smu_populate_umd_state_clk(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to populate UMD state clocks!\n");
		वापस ret;
	पूर्ण

	ret = smu_get_asic_घातer_limits(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to get asic power limits!\n");
		वापस ret;
	पूर्ण

	smu_get_unique_id(smu);

	smu_get_fan_parameters(smu);

	smu_handle_task(&adev->smu,
			smu->smu_dpm.dpm_level,
			AMD_PP_TASK_COMPLETE_INIT,
			false);

	smu_restore_dpm_user_profile(smu);

	वापस 0;
पूर्ण

अटल पूर्णांक smu_init_fb_allocations(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा smu_table *tables = smu_table->tables;
	काष्ठा smu_table *driver_table = &(smu_table->driver_table);
	uपूर्णांक32_t max_table_size = 0;
	पूर्णांक ret, i;

	/* VRAM allocation क्रम tool table */
	अगर (tables[SMU_TABLE_PMSTATUSLOG].size) अणु
		ret = amdgpu_bo_create_kernel(adev,
					      tables[SMU_TABLE_PMSTATUSLOG].size,
					      tables[SMU_TABLE_PMSTATUSLOG].align,
					      tables[SMU_TABLE_PMSTATUSLOG].करोमुख्य,
					      &tables[SMU_TABLE_PMSTATUSLOG].bo,
					      &tables[SMU_TABLE_PMSTATUSLOG].mc_address,
					      &tables[SMU_TABLE_PMSTATUSLOG].cpu_addr);
		अगर (ret) अणु
			dev_err(adev->dev, "VRAM allocation for tool table failed!\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/* VRAM allocation क्रम driver table */
	क्रम (i = 0; i < SMU_TABLE_COUNT; i++) अणु
		अगर (tables[i].size == 0)
			जारी;

		अगर (i == SMU_TABLE_PMSTATUSLOG)
			जारी;

		अगर (max_table_size < tables[i].size)
			max_table_size = tables[i].size;
	पूर्ण

	driver_table->size = max_table_size;
	driver_table->align = PAGE_SIZE;
	driver_table->करोमुख्य = AMDGPU_GEM_DOMAIN_VRAM;

	ret = amdgpu_bo_create_kernel(adev,
				      driver_table->size,
				      driver_table->align,
				      driver_table->करोमुख्य,
				      &driver_table->bo,
				      &driver_table->mc_address,
				      &driver_table->cpu_addr);
	अगर (ret) अणु
		dev_err(adev->dev, "VRAM allocation for driver table failed!\n");
		अगर (tables[SMU_TABLE_PMSTATUSLOG].mc_address)
			amdgpu_bo_मुक्त_kernel(&tables[SMU_TABLE_PMSTATUSLOG].bo,
					      &tables[SMU_TABLE_PMSTATUSLOG].mc_address,
					      &tables[SMU_TABLE_PMSTATUSLOG].cpu_addr);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक smu_fini_fb_allocations(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा smu_table *tables = smu_table->tables;
	काष्ठा smu_table *driver_table = &(smu_table->driver_table);

	अगर (tables[SMU_TABLE_PMSTATUSLOG].mc_address)
		amdgpu_bo_मुक्त_kernel(&tables[SMU_TABLE_PMSTATUSLOG].bo,
				      &tables[SMU_TABLE_PMSTATUSLOG].mc_address,
				      &tables[SMU_TABLE_PMSTATUSLOG].cpu_addr);

	amdgpu_bo_मुक्त_kernel(&driver_table->bo,
			      &driver_table->mc_address,
			      &driver_table->cpu_addr);

	वापस 0;
पूर्ण

/**
 * smu_alloc_memory_pool - allocate memory pool in the प्रणाली memory
 *
 * @smu: amdgpu_device poपूर्णांकer
 *
 * This memory pool will be used क्रम SMC use and msg SetSystemVirtualDramAddr
 * and DramLogSetDramAddr can notअगरy it changed.
 *
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक smu_alloc_memory_pool(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा smu_table *memory_pool = &smu_table->memory_pool;
	uपूर्णांक64_t pool_size = smu->pool_size;
	पूर्णांक ret = 0;

	अगर (pool_size == SMU_MEMORY_POOL_SIZE_ZERO)
		वापस ret;

	memory_pool->size = pool_size;
	memory_pool->align = PAGE_SIZE;
	memory_pool->करोमुख्य = AMDGPU_GEM_DOMAIN_GTT;

	चयन (pool_size) अणु
	हाल SMU_MEMORY_POOL_SIZE_256_MB:
	हाल SMU_MEMORY_POOL_SIZE_512_MB:
	हाल SMU_MEMORY_POOL_SIZE_1_GB:
	हाल SMU_MEMORY_POOL_SIZE_2_GB:
		ret = amdgpu_bo_create_kernel(adev,
					      memory_pool->size,
					      memory_pool->align,
					      memory_pool->करोमुख्य,
					      &memory_pool->bo,
					      &memory_pool->mc_address,
					      &memory_pool->cpu_addr);
		अगर (ret)
			dev_err(adev->dev, "VRAM allocation for dramlog failed!\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक smu_मुक्त_memory_pool(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा smu_table *memory_pool = &smu_table->memory_pool;

	अगर (memory_pool->size == SMU_MEMORY_POOL_SIZE_ZERO)
		वापस 0;

	amdgpu_bo_मुक्त_kernel(&memory_pool->bo,
			      &memory_pool->mc_address,
			      &memory_pool->cpu_addr);

	स_रखो(memory_pool, 0, माप(काष्ठा smu_table));

	वापस 0;
पूर्ण

अटल पूर्णांक smu_alloc_dummy_पढ़ो_table(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा smu_table *dummy_पढ़ो_1_table =
			&smu_table->dummy_पढ़ो_1_table;
	काष्ठा amdgpu_device *adev = smu->adev;
	पूर्णांक ret = 0;

	dummy_पढ़ो_1_table->size = 0x40000;
	dummy_पढ़ो_1_table->align = PAGE_SIZE;
	dummy_पढ़ो_1_table->करोमुख्य = AMDGPU_GEM_DOMAIN_VRAM;

	ret = amdgpu_bo_create_kernel(adev,
				      dummy_पढ़ो_1_table->size,
				      dummy_पढ़ो_1_table->align,
				      dummy_पढ़ो_1_table->करोमुख्य,
				      &dummy_पढ़ो_1_table->bo,
				      &dummy_पढ़ो_1_table->mc_address,
				      &dummy_पढ़ो_1_table->cpu_addr);
	अगर (ret)
		dev_err(adev->dev, "VRAM allocation for dummy read table failed!\n");

	वापस ret;
पूर्ण

अटल व्योम smu_मुक्त_dummy_पढ़ो_table(काष्ठा smu_context *smu)
अणु
	काष्ठा smu_table_context *smu_table = &smu->smu_table;
	काष्ठा smu_table *dummy_पढ़ो_1_table =
			&smu_table->dummy_पढ़ो_1_table;


	amdgpu_bo_मुक्त_kernel(&dummy_पढ़ो_1_table->bo,
			      &dummy_पढ़ो_1_table->mc_address,
			      &dummy_पढ़ो_1_table->cpu_addr);

	स_रखो(dummy_पढ़ो_1_table, 0, माप(काष्ठा smu_table));
पूर्ण

अटल पूर्णांक smu_smc_table_sw_init(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret;

	/**
	 * Create smu_table काष्ठाure, and init smc tables such as
	 * TABLE_PPTABLE, TABLE_WATERMARKS, TABLE_SMU_METRICS, and etc.
	 */
	ret = smu_init_smc_tables(smu);
	अगर (ret) अणु
		dev_err(smu->adev->dev, "Failed to init smc tables!\n");
		वापस ret;
	पूर्ण

	/**
	 * Create smu_घातer_context काष्ठाure, and allocate smu_dpm_context and
	 * context size to fill the smu_घातer_context data.
	 */
	ret = smu_init_घातer(smu);
	अगर (ret) अणु
		dev_err(smu->adev->dev, "Failed to init smu_init_power!\n");
		वापस ret;
	पूर्ण

	/*
	 * allocate vram bos to store smc table contents.
	 */
	ret = smu_init_fb_allocations(smu);
	अगर (ret)
		वापस ret;

	ret = smu_alloc_memory_pool(smu);
	अगर (ret)
		वापस ret;

	ret = smu_alloc_dummy_पढ़ो_table(smu);
	अगर (ret)
		वापस ret;

	ret = smu_i2c_init(smu, &smu->adev->pm.smu_i2c);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक smu_smc_table_sw_fini(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret;

	smu_i2c_fini(smu, &smu->adev->pm.smu_i2c);

	smu_मुक्त_dummy_पढ़ो_table(smu);

	ret = smu_मुक्त_memory_pool(smu);
	अगर (ret)
		वापस ret;

	ret = smu_fini_fb_allocations(smu);
	अगर (ret)
		वापस ret;

	ret = smu_fini_घातer(smu);
	अगर (ret) अणु
		dev_err(smu->adev->dev, "Failed to init smu_fini_power!\n");
		वापस ret;
	पूर्ण

	ret = smu_fini_smc_tables(smu);
	अगर (ret) अणु
		dev_err(smu->adev->dev, "Failed to smu_fini_smc_tables!\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम smu_throttling_logging_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smu_context *smu = container_of(work, काष्ठा smu_context,
					       throttling_logging_work);

	smu_log_thermal_throttling(smu);
पूर्ण

अटल व्योम smu_पूर्णांकerrupt_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smu_context *smu = container_of(work, काष्ठा smu_context,
					       पूर्णांकerrupt_work);

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs && smu->ppt_funcs->पूर्णांकerrupt_work)
		smu->ppt_funcs->पूर्णांकerrupt_work(smu);

	mutex_unlock(&smu->mutex);
पूर्ण

अटल पूर्णांक smu_sw_init(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा smu_context *smu = &adev->smu;
	पूर्णांक ret;

	smu->pool_size = adev->pm.smu_prv_buffer_size;
	smu->smu_feature.feature_num = SMU_FEATURE_MAX;
	mutex_init(&smu->smu_feature.mutex);
	biपंचांगap_zero(smu->smu_feature.supported, SMU_FEATURE_MAX);
	biपंचांगap_zero(smu->smu_feature.enabled, SMU_FEATURE_MAX);
	biपंचांगap_zero(smu->smu_feature.allowed, SMU_FEATURE_MAX);

	mutex_init(&smu->sensor_lock);
	mutex_init(&smu->metrics_lock);
	mutex_init(&smu->message_lock);

	INIT_WORK(&smu->throttling_logging_work, smu_throttling_logging_work_fn);
	INIT_WORK(&smu->पूर्णांकerrupt_work, smu_पूर्णांकerrupt_work_fn);
	atomic64_set(&smu->throttle_पूर्णांक_counter, 0);
	smu->watermarks_biपंचांगap = 0;
	smu->घातer_profile_mode = PP_SMC_POWER_PROखाता_BOOTUP_DEFAULT;
	smu->शेष_घातer_profile_mode = PP_SMC_POWER_PROखाता_BOOTUP_DEFAULT;

	atomic_set(&smu->smu_घातer.घातer_gate.vcn_gated, 1);
	atomic_set(&smu->smu_घातer.घातer_gate.jpeg_gated, 1);
	mutex_init(&smu->smu_घातer.घातer_gate.vcn_gate_lock);
	mutex_init(&smu->smu_घातer.घातer_gate.jpeg_gate_lock);

	smu->workload_mask = 1 << smu->workload_prority[PP_SMC_POWER_PROखाता_BOOTUP_DEFAULT];
	smu->workload_prority[PP_SMC_POWER_PROखाता_BOOTUP_DEFAULT] = 0;
	smu->workload_prority[PP_SMC_POWER_PROखाता_FULLSCREEN3D] = 1;
	smu->workload_prority[PP_SMC_POWER_PROखाता_POWERSAVING] = 2;
	smu->workload_prority[PP_SMC_POWER_PROखाता_VIDEO] = 3;
	smu->workload_prority[PP_SMC_POWER_PROखाता_VR] = 4;
	smu->workload_prority[PP_SMC_POWER_PROखाता_COMPUTE] = 5;
	smu->workload_prority[PP_SMC_POWER_PROखाता_CUSTOM] = 6;

	smu->workload_setting[0] = PP_SMC_POWER_PROखाता_BOOTUP_DEFAULT;
	smu->workload_setting[1] = PP_SMC_POWER_PROखाता_FULLSCREEN3D;
	smu->workload_setting[2] = PP_SMC_POWER_PROखाता_POWERSAVING;
	smu->workload_setting[3] = PP_SMC_POWER_PROखाता_VIDEO;
	smu->workload_setting[4] = PP_SMC_POWER_PROखाता_VR;
	smu->workload_setting[5] = PP_SMC_POWER_PROखाता_COMPUTE;
	smu->workload_setting[6] = PP_SMC_POWER_PROखाता_CUSTOM;
	smu->display_config = &adev->pm.pm_display_cfg;

	smu->smu_dpm.dpm_level = AMD_DPM_FORCED_LEVEL_AUTO;
	smu->smu_dpm.requested_dpm_level = AMD_DPM_FORCED_LEVEL_AUTO;

	ret = smu_init_microcode(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to load smu firmware!\n");
		वापस ret;
	पूर्ण

	ret = smu_smc_table_sw_init(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to sw init smc table!\n");
		वापस ret;
	पूर्ण

	ret = smu_रेजिस्टर_irq_handler(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to register smc irq handler!\n");
		वापस ret;
	पूर्ण

	/* If there is no way to query fan control mode, fan control is not supported */
	अगर (!smu->ppt_funcs->get_fan_control_mode)
		smu->adev->pm.no_fan = true;

	वापस 0;
पूर्ण

अटल पूर्णांक smu_sw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा smu_context *smu = &adev->smu;
	पूर्णांक ret;

	ret = smu_smc_table_sw_fini(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to sw fini smc table!\n");
		वापस ret;
	पूर्ण

	smu_fini_microcode(smu);

	वापस 0;
पूर्ण

अटल पूर्णांक smu_get_thermal_temperature_range(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	काष्ठा smu_temperature_range *range =
				&smu->thermal_range;
	पूर्णांक ret = 0;

	अगर (!smu->ppt_funcs->get_thermal_temperature_range)
		वापस 0;

	ret = smu->ppt_funcs->get_thermal_temperature_range(smu, range);
	अगर (ret)
		वापस ret;

	adev->pm.dpm.thermal.min_temp = range->min;
	adev->pm.dpm.thermal.max_temp = range->max;
	adev->pm.dpm.thermal.max_edge_emergency_temp = range->edge_emergency_max;
	adev->pm.dpm.thermal.min_hotspot_temp = range->hotspot_min;
	adev->pm.dpm.thermal.max_hotspot_crit_temp = range->hotspot_crit_max;
	adev->pm.dpm.thermal.max_hotspot_emergency_temp = range->hotspot_emergency_max;
	adev->pm.dpm.thermal.min_mem_temp = range->mem_min;
	adev->pm.dpm.thermal.max_mem_crit_temp = range->mem_crit_max;
	adev->pm.dpm.thermal.max_mem_emergency_temp = range->mem_emergency_max;

	वापस ret;
पूर्ण

अटल पूर्णांक smu_smc_hw_setup(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	uपूर्णांक32_t pcie_gen = 0, pcie_width = 0;
	पूर्णांक ret = 0;

	अगर (adev->in_suspend && smu_is_dpm_running(smu)) अणु
		dev_info(adev->dev, "dpm has been enabled\n");
		/* this is needed specअगरically */
		अगर ((adev->asic_type >= CHIP_SIENNA_CICHLID) &&
		    (adev->asic_type <= CHIP_DIMGREY_CAVEFISH))
			ret = smu_प्रणाली_features_control(smu, true);
		वापस ret;
	पूर्ण

	ret = smu_init_display_count(smu, 0);
	अगर (ret) अणु
		dev_info(adev->dev, "Failed to pre-set display count as 0!\n");
		वापस ret;
	पूर्ण

	ret = smu_set_driver_table_location(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to SetDriverDramAddr!\n");
		वापस ret;
	पूर्ण

	/*
	 * Set PMSTATUSLOG table bo address with SetToolsDramAddr MSG क्रम tools.
	 */
	ret = smu_set_tool_table_location(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to SetToolsDramAddr!\n");
		वापस ret;
	पूर्ण

	/*
	 * Use msg SetSystemVirtualDramAddr and DramLogSetDramAddr can notअगरy
	 * pool location.
	 */
	ret = smu_notअगरy_memory_pool_location(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to SetDramLogDramAddr!\n");
		वापस ret;
	पूर्ण

	/* smu_dump_pptable(smu); */
	/*
	 * Copy pptable bo in the vram to smc with SMU MSGs such as
	 * SetDriverDramAddr and TransferTableDram2Smu.
	 */
	ret = smu_ग_लिखो_pptable(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to transfer pptable to SMC!\n");
		वापस ret;
	पूर्ण

	/* issue Run*Btc msg */
	ret = smu_run_btc(smu);
	अगर (ret)
		वापस ret;

	ret = smu_feature_set_allowed_mask(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to set driver allowed features mask!\n");
		वापस ret;
	पूर्ण

	ret = smu_प्रणाली_features_control(smu, true);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to enable requested dpm features!\n");
		वापस ret;
	पूर्ण

	अगर (!smu_is_dpm_running(smu))
		dev_info(adev->dev, "dpm has been disabled\n");

	अगर (adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN4)
		pcie_gen = 3;
	अन्यथा अगर (adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN3)
		pcie_gen = 2;
	अन्यथा अगर (adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN2)
		pcie_gen = 1;
	अन्यथा अगर (adev->pm.pcie_gen_mask & CAIL_PCIE_LINK_SPEED_SUPPORT_GEN1)
		pcie_gen = 0;

	/* Bit 31:16: LCLK DPM level. 0 is DPM0, and 1 is DPM1
	 * Bit 15:8:  PCIE GEN, 0 to 3 corresponds to GEN1 to GEN4
	 * Bit 7:0:   PCIE lane width, 1 to 7 corresponds is x1 to x32
	 */
	अगर (adev->pm.pcie_mlw_mask & CAIL_PCIE_LINK_WIDTH_SUPPORT_X16)
		pcie_width = 6;
	अन्यथा अगर (adev->pm.pcie_mlw_mask & CAIL_PCIE_LINK_WIDTH_SUPPORT_X12)
		pcie_width = 5;
	अन्यथा अगर (adev->pm.pcie_mlw_mask & CAIL_PCIE_LINK_WIDTH_SUPPORT_X8)
		pcie_width = 4;
	अन्यथा अगर (adev->pm.pcie_mlw_mask & CAIL_PCIE_LINK_WIDTH_SUPPORT_X4)
		pcie_width = 3;
	अन्यथा अगर (adev->pm.pcie_mlw_mask & CAIL_PCIE_LINK_WIDTH_SUPPORT_X2)
		pcie_width = 2;
	अन्यथा अगर (adev->pm.pcie_mlw_mask & CAIL_PCIE_LINK_WIDTH_SUPPORT_X1)
		pcie_width = 1;
	ret = smu_update_pcie_parameters(smu, pcie_gen, pcie_width);
	अगर (ret) अणु
		dev_err(adev->dev, "Attempt to override pcie params failed!\n");
		वापस ret;
	पूर्ण

	ret = smu_get_thermal_temperature_range(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to get thermal temperature ranges!\n");
		वापस ret;
	पूर्ण

	ret = smu_enable_thermal_alert(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to enable thermal alert!\n");
		वापस ret;
	पूर्ण

	/*
	 * Set initialized values (get from vbios) to dpm tables context such as
	 * gfxclk, memclk, dcefclk, and etc. And enable the DPM feature क्रम each
	 * type of clks.
	 */
	ret = smu_set_शेष_dpm_table(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to setup default dpm clock tables!\n");
		वापस ret;
	पूर्ण

	ret = smu_notअगरy_display_change(smu);
	अगर (ret)
		वापस ret;

	/*
	 * Set min deep sleep dce fclk with bootup value from vbios via
	 * SetMinDeepSleepDcefclk MSG.
	 */
	ret = smu_set_min_dcef_deep_sleep(smu,
					  smu->smu_table.boot_values.dcefclk / 100);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण

अटल पूर्णांक smu_start_smc_engine(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	पूर्णांक ret = 0;

	अगर (adev->firmware.load_type != AMDGPU_FW_LOAD_PSP) अणु
		अगर (adev->asic_type < CHIP_NAVI10) अणु
			अगर (smu->ppt_funcs->load_microcode) अणु
				ret = smu->ppt_funcs->load_microcode(smu);
				अगर (ret)
					वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (smu->ppt_funcs->check_fw_status) अणु
		ret = smu->ppt_funcs->check_fw_status(smu);
		अगर (ret) अणु
			dev_err(adev->dev, "SMC is not ready\n");
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * Send msg GetDriverIfVersion to check अगर the वापस value is equal
	 * with DRIVER_IF_VERSION of smc header.
	 */
	ret = smu_check_fw_version(smu);
	अगर (ret)
		वापस ret;

	वापस ret;
पूर्ण

अटल पूर्णांक smu_hw_init(व्योम *handle)
अणु
	पूर्णांक ret;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा smu_context *smu = &adev->smu;

	अगर (amdgpu_sriov_vf(adev) && !amdgpu_sriov_is_pp_one_vf(adev)) अणु
		smu->pm_enabled = false;
		वापस 0;
	पूर्ण

	ret = smu_start_smc_engine(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "SMC engine is not correctly up!\n");
		वापस ret;
	पूर्ण

	अगर (smu->is_apu) अणु
		smu_घातergate_sdma(&adev->smu, false);
		smu_dpm_set_vcn_enable(smu, true);
		smu_dpm_set_jpeg_enable(smu, true);
		smu_set_gfx_cgpg(&adev->smu, true);
	पूर्ण

	अगर (!smu->pm_enabled)
		वापस 0;

	/* get boot_values from vbios to set revision, gfxclk, and etc. */
	ret = smu_get_vbios_bootup_values(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to get VBIOS boot clock values!\n");
		वापस ret;
	पूर्ण

	ret = smu_setup_pptable(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to setup pptable!\n");
		वापस ret;
	पूर्ण

	ret = smu_get_driver_allowed_feature_mask(smu);
	अगर (ret)
		वापस ret;

	ret = smu_smc_hw_setup(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to setup smc hw!\n");
		वापस ret;
	पूर्ण

	/*
	 * Move maximum sustainable घड़ी retrieving here considering
	 * 1. It is not needed on resume(from S3).
	 * 2. DAL settings come between .hw_init and .late_init of SMU.
	 *    And DAL needs to know the maximum sustainable घड़ीs. Thus
	 *    it cannot be put in .late_init().
	 */
	ret = smu_init_max_sustainable_घड़ीs(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to init max sustainable clocks!\n");
		वापस ret;
	पूर्ण

	adev->pm.dpm_enabled = true;

	dev_info(adev->dev, "SMU is initialized successfully!\n");

	वापस 0;
पूर्ण

अटल पूर्णांक smu_disable_dpms(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	पूर्णांक ret = 0;
	bool use_baco = !smu->is_apu &&
		((amdgpu_in_reset(adev) &&
		  (amdgpu_asic_reset_method(adev) == AMD_RESET_METHOD_BACO)) ||
		 ((adev->in_runpm || adev->in_s4) && amdgpu_asic_supports_baco(adev)));

	/*
	 * For custom pptable uploading, skip the DPM features
	 * disable process on Navi1x ASICs.
	 *   - As the gfx related features are under control of
	 *     RLC on those ASICs. RLC reinitialization will be
	 *     needed to reenable them. That will cost much more
	 *     efक्रमts.
	 *
	 *   - SMU firmware can handle the DPM reenablement
	 *     properly.
	 */
	अगर (smu->uploading_custom_pp_table &&
	    (adev->asic_type >= CHIP_NAVI10) &&
	    (adev->asic_type <= CHIP_DIMGREY_CAVEFISH))
		वापस 0;

	/*
	 * For Sienna_Cichlid, PMFW will handle the features disablement properly
	 * on BACO in. Driver involvement is unnecessary.
	 */
	अगर ((adev->asic_type == CHIP_SIENNA_CICHLID) &&
	     use_baco)
		वापस 0;

	/*
	 * For gpu reset, runpm and hibernation through BACO,
	 * BACO feature has to be kept enabled.
	 */
	अगर (use_baco && smu_feature_is_enabled(smu, SMU_FEATURE_BACO_BIT)) अणु
		ret = smu_disable_all_features_with_exception(smu,
							      SMU_FEATURE_BACO_BIT);
		अगर (ret)
			dev_err(adev->dev, "Failed to disable smu features except BACO.\n");
	पूर्ण अन्यथा अणु
		ret = smu_प्रणाली_features_control(smu, false);
		अगर (ret)
			dev_err(adev->dev, "Failed to disable smu features.\n");
	पूर्ण

	अगर (adev->asic_type >= CHIP_NAVI10 &&
	    adev->gfx.rlc.funcs->stop)
		adev->gfx.rlc.funcs->stop(adev);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_smc_hw_cleanup(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	पूर्णांक ret = 0;

	cancel_work_sync(&smu->throttling_logging_work);
	cancel_work_sync(&smu->पूर्णांकerrupt_work);

	ret = smu_disable_thermal_alert(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Fail to disable thermal alert!\n");
		वापस ret;
	पूर्ण

	ret = smu_disable_dpms(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Fail to disable dpm features!\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu_hw_fini(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा smu_context *smu = &adev->smu;

	अगर (amdgpu_sriov_vf(adev)&& !amdgpu_sriov_is_pp_one_vf(adev))
		वापस 0;

	अगर (smu->is_apu) अणु
		smu_घातergate_sdma(&adev->smu, true);
		smu_dpm_set_vcn_enable(smu, false);
		smu_dpm_set_jpeg_enable(smu, false);
	पूर्ण

	अगर (!smu->pm_enabled)
		वापस 0;

	adev->pm.dpm_enabled = false;

	वापस smu_smc_hw_cleanup(smu);
पूर्ण

अटल पूर्णांक smu_reset(काष्ठा smu_context *smu)
अणु
	काष्ठा amdgpu_device *adev = smu->adev;
	पूर्णांक ret;

	amdgpu_gfx_off_ctrl(smu->adev, false);

	ret = smu_hw_fini(adev);
	अगर (ret)
		वापस ret;

	ret = smu_hw_init(adev);
	अगर (ret)
		वापस ret;

	ret = smu_late_init(adev);
	अगर (ret)
		वापस ret;

	amdgpu_gfx_off_ctrl(smu->adev, true);

	वापस 0;
पूर्ण

अटल पूर्णांक smu_suspend(व्योम *handle)
अणु
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा smu_context *smu = &adev->smu;
	पूर्णांक ret;

	अगर (amdgpu_sriov_vf(adev)&& !amdgpu_sriov_is_pp_one_vf(adev))
		वापस 0;

	अगर (!smu->pm_enabled)
		वापस 0;

	adev->pm.dpm_enabled = false;

	ret = smu_smc_hw_cleanup(smu);
	अगर (ret)
		वापस ret;

	smu->watermarks_biपंचांगap &= ~(WATERMARKS_LOADED);

	/* skip CGPG when in S0ix */
	अगर (smu->is_apu && !adev->in_s0ix)
		smu_set_gfx_cgpg(&adev->smu, false);

	वापस 0;
पूर्ण

अटल पूर्णांक smu_resume(व्योम *handle)
अणु
	पूर्णांक ret;
	काष्ठा amdgpu_device *adev = (काष्ठा amdgpu_device *)handle;
	काष्ठा smu_context *smu = &adev->smu;

	अगर (amdgpu_sriov_vf(adev)&& !amdgpu_sriov_is_pp_one_vf(adev))
		वापस 0;

	अगर (!smu->pm_enabled)
		वापस 0;

	dev_info(adev->dev, "SMU is resuming...\n");

	ret = smu_start_smc_engine(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "SMC engine is not correctly up!\n");
		वापस ret;
	पूर्ण

	ret = smu_smc_hw_setup(smu);
	अगर (ret) अणु
		dev_err(adev->dev, "Failed to setup smc hw!\n");
		वापस ret;
	पूर्ण

	अगर (smu->is_apu)
		smu_set_gfx_cgpg(&adev->smu, true);

	smu->disable_uclk_चयन = 0;

	adev->pm.dpm_enabled = true;

	dev_info(adev->dev, "SMU is resumed successfully!\n");

	वापस 0;
पूर्ण

अटल पूर्णांक smu_display_configuration_change(व्योम *handle,
					    स्थिर काष्ठा amd_pp_display_configuration *display_config)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक index = 0;
	पूर्णांक num_of_active_display = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	अगर (!display_config)
		वापस -EINVAL;

	mutex_lock(&smu->mutex);

	smu_set_min_dcef_deep_sleep(smu,
				    display_config->min_dcef_deep_sleep_set_clk / 100);

	क्रम (index = 0; index < display_config->num_path_including_non_display; index++) अणु
		अगर (display_config->displays[index].controller_id != 0)
			num_of_active_display++;
	पूर्ण

	mutex_unlock(&smu->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक smu_set_घड़ीgating_state(व्योम *handle,
				     क्रमागत amd_घड़ीgating_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक smu_set_घातergating_state(व्योम *handle,
				     क्रमागत amd_घातergating_state state)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक smu_enable_umd_pstate(व्योम *handle,
		      क्रमागत amd_dpm_क्रमced_level *level)
अणु
	uपूर्णांक32_t profile_mode_mask = AMD_DPM_FORCED_LEVEL_PROखाता_STANDARD |
					AMD_DPM_FORCED_LEVEL_PROखाता_MIN_SCLK |
					AMD_DPM_FORCED_LEVEL_PROखाता_MIN_MCLK |
					AMD_DPM_FORCED_LEVEL_PROखाता_PEAK;

	काष्ठा smu_context *smu = (काष्ठा smu_context*)(handle);
	काष्ठा smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);

	अगर (!smu->is_apu && !smu_dpm_ctx->dpm_context)
		वापस -EINVAL;

	अगर (!(smu_dpm_ctx->dpm_level & profile_mode_mask)) अणु
		/* enter umd pstate, save current level, disable gfx cg*/
		अगर (*level & profile_mode_mask) अणु
			smu_dpm_ctx->saved_dpm_level = smu_dpm_ctx->dpm_level;
			smu_dpm_ctx->enable_umd_pstate = true;
			smu_gpo_control(smu, false);
			amdgpu_device_ip_set_घातergating_state(smu->adev,
							       AMD_IP_BLOCK_TYPE_GFX,
							       AMD_PG_STATE_UNGATE);
			amdgpu_device_ip_set_घड़ीgating_state(smu->adev,
							       AMD_IP_BLOCK_TYPE_GFX,
							       AMD_CG_STATE_UNGATE);
			smu_gfx_ulv_control(smu, false);
			smu_deep_sleep_control(smu, false);
			amdgpu_asic_update_umd_stable_pstate(smu->adev, true);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* निकास umd pstate, restore level, enable gfx cg*/
		अगर (!(*level & profile_mode_mask)) अणु
			अगर (*level == AMD_DPM_FORCED_LEVEL_PROखाता_EXIT)
				*level = smu_dpm_ctx->saved_dpm_level;
			smu_dpm_ctx->enable_umd_pstate = false;
			amdgpu_asic_update_umd_stable_pstate(smu->adev, false);
			smu_deep_sleep_control(smu, true);
			smu_gfx_ulv_control(smu, true);
			amdgpu_device_ip_set_घड़ीgating_state(smu->adev,
							       AMD_IP_BLOCK_TYPE_GFX,
							       AMD_CG_STATE_GATE);
			amdgpu_device_ip_set_घातergating_state(smu->adev,
							       AMD_IP_BLOCK_TYPE_GFX,
							       AMD_PG_STATE_GATE);
			smu_gpo_control(smu, true);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smu_bump_घातer_profile_mode(काष्ठा smu_context *smu,
					   दीर्घ *param,
					   uपूर्णांक32_t param_size)
अणु
	पूर्णांक ret = 0;

	अगर (smu->ppt_funcs->set_घातer_profile_mode)
		ret = smu->ppt_funcs->set_घातer_profile_mode(smu, param, param_size);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_adjust_घातer_state_dynamic(काष्ठा smu_context *smu,
				   क्रमागत amd_dpm_क्रमced_level level,
				   bool skip_display_settings)
अणु
	पूर्णांक ret = 0;
	पूर्णांक index = 0;
	दीर्घ workload;
	काष्ठा smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);

	अगर (!skip_display_settings) अणु
		ret = smu_display_config_changed(smu);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Failed to change display config!");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = smu_apply_घड़ीs_adjust_rules(smu);
	अगर (ret) अणु
		dev_err(smu->adev->dev, "Failed to apply clocks adjust rules!");
		वापस ret;
	पूर्ण

	अगर (!skip_display_settings) अणु
		ret = smu_notअगरy_smc_display_config(smu);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Failed to notify smc display config!");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (smu_dpm_ctx->dpm_level != level) अणु
		ret = smu_asic_set_perक्रमmance_level(smu, level);
		अगर (ret) अणु
			dev_err(smu->adev->dev, "Failed to set performance level!");
			वापस ret;
		पूर्ण

		/* update the saved copy */
		smu_dpm_ctx->dpm_level = level;
	पूर्ण

	अगर (smu_dpm_ctx->dpm_level != AMD_DPM_FORCED_LEVEL_MANUAL &&
		smu_dpm_ctx->dpm_level != AMD_DPM_FORCED_LEVEL_PERF_DETERMINISM) अणु
		index = fls(smu->workload_mask);
		index = index > 0 && index <= WORKLOAD_POLICY_MAX ? index - 1 : 0;
		workload = smu->workload_setting[index];

		अगर (smu->घातer_profile_mode != workload)
			smu_bump_घातer_profile_mode(smu, &workload, 0);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक smu_handle_task(काष्ठा smu_context *smu,
			   क्रमागत amd_dpm_क्रमced_level level,
			   क्रमागत amd_pp_task task_id,
			   bool lock_needed)
अणु
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	अगर (lock_needed)
		mutex_lock(&smu->mutex);

	चयन (task_id) अणु
	हाल AMD_PP_TASK_DISPLAY_CONFIG_CHANGE:
		ret = smu_pre_display_config_changed(smu);
		अगर (ret)
			जाओ out;
		ret = smu_adjust_घातer_state_dynamic(smu, level, false);
		अवरोध;
	हाल AMD_PP_TASK_COMPLETE_INIT:
	हाल AMD_PP_TASK_READJUST_POWER_STATE:
		ret = smu_adjust_घातer_state_dynamic(smu, level, true);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

out:
	अगर (lock_needed)
		mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_handle_dpm_task(व्योम *handle,
			       क्रमागत amd_pp_task task_id,
			       क्रमागत amd_pm_state_type *user_state)
अणु
	काष्ठा smu_context *smu = handle;
	काष्ठा smu_dpm_context *smu_dpm = &smu->smu_dpm;

	वापस smu_handle_task(smu, smu_dpm->dpm_level, task_id, true);

पूर्ण

अटल पूर्णांक smu_चयन_घातer_profile(व्योम *handle,
				    क्रमागत PP_SMC_POWER_PROखाता type,
				    bool en)
अणु
	काष्ठा smu_context *smu = handle;
	काष्ठा smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);
	दीर्घ workload;
	uपूर्णांक32_t index;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	अगर (!(type < PP_SMC_POWER_PROखाता_CUSTOM))
		वापस -EINVAL;

	mutex_lock(&smu->mutex);

	अगर (!en) अणु
		smu->workload_mask &= ~(1 << smu->workload_prority[type]);
		index = fls(smu->workload_mask);
		index = index > 0 && index <= WORKLOAD_POLICY_MAX ? index - 1 : 0;
		workload = smu->workload_setting[index];
	पूर्ण अन्यथा अणु
		smu->workload_mask |= (1 << smu->workload_prority[type]);
		index = fls(smu->workload_mask);
		index = index <= WORKLOAD_POLICY_MAX ? index - 1 : 0;
		workload = smu->workload_setting[index];
	पूर्ण

	अगर (smu_dpm_ctx->dpm_level != AMD_DPM_FORCED_LEVEL_MANUAL &&
		smu_dpm_ctx->dpm_level != AMD_DPM_FORCED_LEVEL_PERF_DETERMINISM)
		smu_bump_घातer_profile_mode(smu, &workload, 0);

	mutex_unlock(&smu->mutex);

	वापस 0;
पूर्ण

अटल क्रमागत amd_dpm_क्रमced_level smu_get_perक्रमmance_level(व्योम *handle)
अणु
	काष्ठा smu_context *smu = handle;
	काष्ठा smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);
	क्रमागत amd_dpm_क्रमced_level level;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	अगर (!smu->is_apu && !smu_dpm_ctx->dpm_context)
		वापस -EINVAL;

	mutex_lock(&(smu->mutex));
	level = smu_dpm_ctx->dpm_level;
	mutex_unlock(&(smu->mutex));

	वापस level;
पूर्ण

अटल पूर्णांक smu_क्रमce_perक्रमmance_level(व्योम *handle,
				       क्रमागत amd_dpm_क्रमced_level level)
अणु
	काष्ठा smu_context *smu = handle;
	काष्ठा smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	अगर (!smu->is_apu && !smu_dpm_ctx->dpm_context)
		वापस -EINVAL;

	mutex_lock(&smu->mutex);

	ret = smu_enable_umd_pstate(smu, &level);
	अगर (ret) अणु
		mutex_unlock(&smu->mutex);
		वापस ret;
	पूर्ण

	ret = smu_handle_task(smu, level,
			      AMD_PP_TASK_READJUST_POWER_STATE,
			      false);

	mutex_unlock(&smu->mutex);

	/* reset user dpm घड़ी state */
	अगर (!ret && smu_dpm_ctx->dpm_level != AMD_DPM_FORCED_LEVEL_MANUAL) अणु
		स_रखो(smu->user_dpm_profile.clk_mask, 0, माप(smu->user_dpm_profile.clk_mask));
		smu->user_dpm_profile.clk_dependency = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक smu_set_display_count(व्योम *handle, uपूर्णांक32_t count)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);
	ret = smu_init_display_count(smu, count);
	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_क्रमce_smuclk_levels(काष्ठा smu_context *smu,
			 क्रमागत smu_clk_type clk_type,
			 uपूर्णांक32_t mask)
अणु
	काष्ठा smu_dpm_context *smu_dpm_ctx = &(smu->smu_dpm);
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	अगर (smu_dpm_ctx->dpm_level != AMD_DPM_FORCED_LEVEL_MANUAL) अणु
		dev_dbg(smu->adev->dev, "force clock level is for dpm manual mode only.\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs && smu->ppt_funcs->क्रमce_clk_levels) अणु
		ret = smu->ppt_funcs->क्रमce_clk_levels(smu, clk_type, mask);
		अगर (!ret && !(smu->user_dpm_profile.flags & SMU_DPM_USER_PROखाता_RESTORE)) अणु
			smu->user_dpm_profile.clk_mask[clk_type] = mask;
			smu_set_user_clk_dependencies(smu, clk_type);
		पूर्ण
	पूर्ण

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_क्रमce_ppclk_levels(व्योम *handle,
				  क्रमागत pp_घड़ी_प्रकारype type,
				  uपूर्णांक32_t mask)
अणु
	काष्ठा smu_context *smu = handle;
	क्रमागत smu_clk_type clk_type;

	चयन (type) अणु
	हाल PP_SCLK:
		clk_type = SMU_SCLK; अवरोध;
	हाल PP_MCLK:
		clk_type = SMU_MCLK; अवरोध;
	हाल PP_PCIE:
		clk_type = SMU_PCIE; अवरोध;
	हाल PP_SOCCLK:
		clk_type = SMU_SOCCLK; अवरोध;
	हाल PP_FCLK:
		clk_type = SMU_FCLK; अवरोध;
	हाल PP_DCEFCLK:
		clk_type = SMU_DCEFCLK; अवरोध;
	हाल PP_VCLK:
		clk_type = SMU_VCLK; अवरोध;
	हाल PP_DCLK:
		clk_type = SMU_DCLK; अवरोध;
	हाल OD_SCLK:
		clk_type = SMU_OD_SCLK; अवरोध;
	हाल OD_MCLK:
		clk_type = SMU_OD_MCLK; अवरोध;
	हाल OD_VDDC_CURVE:
		clk_type = SMU_OD_VDDC_CURVE; अवरोध;
	हाल OD_RANGE:
		clk_type = SMU_OD_RANGE; अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस smu_क्रमce_smuclk_levels(smu, clk_type, mask);
पूर्ण

/*
 * On प्रणाली suspending or resetting, the dpm_enabled
 * flag will be cleared. So that those SMU services which
 * are not supported will be gated.
 * However, the mp1 state setting should still be granted
 * even अगर the dpm_enabled cleared.
 */
अटल पूर्णांक smu_set_mp1_state(व्योम *handle,
			     क्रमागत pp_mp1_state mp1_state)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs &&
	    smu->ppt_funcs->set_mp1_state)
		ret = smu->ppt_funcs->set_mp1_state(smu, mp1_state);

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_set_df_cstate(व्योम *handle,
			     क्रमागत pp_df_cstate state)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	अगर (!smu->ppt_funcs || !smu->ppt_funcs->set_df_cstate)
		वापस 0;

	mutex_lock(&smu->mutex);

	ret = smu->ppt_funcs->set_df_cstate(smu, state);
	अगर (ret)
		dev_err(smu->adev->dev, "[SetDfCstate] failed!\n");

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

पूर्णांक smu_allow_xgmi_घातer_करोwn(काष्ठा smu_context *smu, bool en)
अणु
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	अगर (!smu->ppt_funcs || !smu->ppt_funcs->allow_xgmi_घातer_करोwn)
		वापस 0;

	mutex_lock(&smu->mutex);

	ret = smu->ppt_funcs->allow_xgmi_घातer_करोwn(smu, en);
	अगर (ret)
		dev_err(smu->adev->dev, "[AllowXgmiPowerDown] failed!\n");

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

पूर्णांक smu_ग_लिखो_watermarks_table(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	ret = smu_set_watermarks_table(smu, शून्य);

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_set_watermarks_क्रम_घड़ी_ranges(व्योम *handle,
					       काष्ठा pp_smu_wm_range_sets *घड़ी_ranges)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	अगर (smu->disable_watermark)
		वापस 0;

	mutex_lock(&smu->mutex);

	ret = smu_set_watermarks_table(smu, घड़ी_ranges);

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

पूर्णांक smu_set_ac_dc(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	/* controlled by firmware */
	अगर (smu->dc_controlled_by_gpio)
		वापस 0;

	mutex_lock(&smu->mutex);
	ret = smu_set_घातer_source(smu,
				   smu->adev->pm.ac_घातer ? SMU_POWER_SOURCE_AC :
				   SMU_POWER_SOURCE_DC);
	अगर (ret)
		dev_err(smu->adev->dev, "Failed to switch to %s mode!\n",
		       smu->adev->pm.ac_घातer ? "AC" : "DC");
	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

स्थिर काष्ठा amd_ip_funcs smu_ip_funcs = अणु
	.name = "smu",
	.early_init = smu_early_init,
	.late_init = smu_late_init,
	.sw_init = smu_sw_init,
	.sw_fini = smu_sw_fini,
	.hw_init = smu_hw_init,
	.hw_fini = smu_hw_fini,
	.suspend = smu_suspend,
	.resume = smu_resume,
	.is_idle = शून्य,
	.check_soft_reset = शून्य,
	.रुको_क्रम_idle = शून्य,
	.soft_reset = शून्य,
	.set_घड़ीgating_state = smu_set_घड़ीgating_state,
	.set_घातergating_state = smu_set_घातergating_state,
	.enable_umd_pstate = smu_enable_umd_pstate,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version smu_v11_0_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_SMC,
	.major = 11,
	.minor = 0,
	.rev = 0,
	.funcs = &smu_ip_funcs,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version smu_v12_0_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_SMC,
	.major = 12,
	.minor = 0,
	.rev = 0,
	.funcs = &smu_ip_funcs,
पूर्ण;

स्थिर काष्ठा amdgpu_ip_block_version smu_v13_0_ip_block =
अणु
	.type = AMD_IP_BLOCK_TYPE_SMC,
	.major = 13,
	.minor = 0,
	.rev = 0,
	.funcs = &smu_ip_funcs,
पूर्ण;

अटल पूर्णांक smu_load_microcode(व्योम *handle)
अणु
	काष्ठा smu_context *smu = handle;
	काष्ठा amdgpu_device *adev = smu->adev;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled)
		वापस -EOPNOTSUPP;

	/* This should be used क्रम non PSP loading */
	अगर (adev->firmware.load_type == AMDGPU_FW_LOAD_PSP)
		वापस 0;

	अगर (smu->ppt_funcs->load_microcode) अणु
		ret = smu->ppt_funcs->load_microcode(smu);
		अगर (ret) अणु
			dev_err(adev->dev, "Load microcode failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (smu->ppt_funcs->check_fw_status) अणु
		ret = smu->ppt_funcs->check_fw_status(smu);
		अगर (ret) अणु
			dev_err(adev->dev, "SMC is not ready\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक smu_set_gfx_cgpg(काष्ठा smu_context *smu, bool enabled)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->set_gfx_cgpg)
		ret = smu->ppt_funcs->set_gfx_cgpg(smu, enabled);

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_set_fan_speed_rpm(व्योम *handle, uपूर्णांक32_t speed)
अणु
	काष्ठा smu_context *smu = handle;
	u32 percent;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->set_fan_speed_percent) अणु
		percent = speed * 100 / smu->fan_max_rpm;
		ret = smu->ppt_funcs->set_fan_speed_percent(smu, percent);
		अगर (!ret && !(smu->user_dpm_profile.flags & SMU_DPM_USER_PROखाता_RESTORE))
			smu->user_dpm_profile.fan_speed_percent = percent;
	पूर्ण

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

पूर्णांक smu_get_घातer_limit(काष्ठा smu_context *smu,
			uपूर्णांक32_t *limit,
			क्रमागत smu_ppt_limit_level limit_level)
अणु
	uपूर्णांक32_t limit_type = *limit >> 24;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	अगर (limit_type != SMU_DEFAULT_PPT_LIMIT) अणु
		अगर (smu->ppt_funcs->get_ppt_limit)
			ret = smu->ppt_funcs->get_ppt_limit(smu, limit, limit_type, limit_level);
	पूर्ण अन्यथा अणु
		चयन (limit_level) अणु
		हाल SMU_PPT_LIMIT_CURRENT:
			*limit = smu->current_घातer_limit;
			अवरोध;
		हाल SMU_PPT_LIMIT_DEFAULT:
			*limit = smu->शेष_घातer_limit;
			अवरोध;
		हाल SMU_PPT_LIMIT_MAX:
			*limit = smu->max_घातer_limit;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_set_घातer_limit(व्योम *handle, uपूर्णांक32_t limit)
अणु
	काष्ठा smu_context *smu = handle;
	uपूर्णांक32_t limit_type = limit >> 24;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	अगर (limit_type != SMU_DEFAULT_PPT_LIMIT)
		अगर (smu->ppt_funcs->set_घातer_limit) अणु
			ret = smu->ppt_funcs->set_घातer_limit(smu, limit);
			जाओ out;
		पूर्ण

	अगर (limit > smu->max_घातer_limit) अणु
		dev_err(smu->adev->dev,
			"New power limit (%d) is over the max allowed %d\n",
			limit, smu->max_घातer_limit);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (!limit)
		limit = smu->current_घातer_limit;

	अगर (smu->ppt_funcs->set_घातer_limit) अणु
		ret = smu->ppt_funcs->set_घातer_limit(smu, limit);
		अगर (!ret && !(smu->user_dpm_profile.flags & SMU_DPM_USER_PROखाता_RESTORE))
			smu->user_dpm_profile.घातer_limit = limit;
	पूर्ण

out:
	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_prपूर्णांक_smuclk_levels(काष्ठा smu_context *smu, क्रमागत smu_clk_type clk_type, अक्षर *buf)
अणु
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->prपूर्णांक_clk_levels)
		ret = smu->ppt_funcs->prपूर्णांक_clk_levels(smu, clk_type, buf);

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_prपूर्णांक_ppclk_levels(व्योम *handle,
				  क्रमागत pp_घड़ी_प्रकारype type,
				  अक्षर *buf)
अणु
	काष्ठा smu_context *smu = handle;
	क्रमागत smu_clk_type clk_type;

	चयन (type) अणु
	हाल PP_SCLK:
		clk_type = SMU_SCLK; अवरोध;
	हाल PP_MCLK:
		clk_type = SMU_MCLK; अवरोध;
	हाल PP_PCIE:
		clk_type = SMU_PCIE; अवरोध;
	हाल PP_SOCCLK:
		clk_type = SMU_SOCCLK; अवरोध;
	हाल PP_FCLK:
		clk_type = SMU_FCLK; अवरोध;
	हाल PP_DCEFCLK:
		clk_type = SMU_DCEFCLK; अवरोध;
	हाल PP_VCLK:
		clk_type = SMU_VCLK; अवरोध;
	हाल PP_DCLK:
		clk_type = SMU_DCLK; अवरोध;
	हाल OD_SCLK:
		clk_type = SMU_OD_SCLK; अवरोध;
	हाल OD_MCLK:
		clk_type = SMU_OD_MCLK; अवरोध;
	हाल OD_VDDC_CURVE:
		clk_type = SMU_OD_VDDC_CURVE; अवरोध;
	हाल OD_RANGE:
		clk_type = SMU_OD_RANGE; अवरोध;
	हाल OD_VDDGFX_OFFSET:
		clk_type = SMU_OD_VDDGFX_OFFSET; अवरोध;
	हाल OD_CCLK:
		clk_type = SMU_OD_CCLK; अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस smu_prपूर्णांक_smuclk_levels(smu, clk_type, buf);
पूर्ण

अटल पूर्णांक smu_od_edit_dpm_table(व्योम *handle,
				 क्रमागत PP_OD_DPM_TABLE_COMMAND type,
				 दीर्घ *input, uपूर्णांक32_t size)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->od_edit_dpm_table) अणु
		ret = smu->ppt_funcs->od_edit_dpm_table(smu, type, input, size);
	पूर्ण

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_पढ़ो_sensor(व्योम *handle,
			   पूर्णांक sensor,
			   व्योम *data,
			   पूर्णांक *size_arg)
अणु
	काष्ठा smu_context *smu = handle;
	काष्ठा smu_umd_pstate_table *pstate_table =
				&smu->pstate_table;
	पूर्णांक ret = 0;
	uपूर्णांक32_t *size, size_val;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	अगर (!data || !size_arg)
		वापस -EINVAL;

	size_val = *size_arg;
	size = &size_val;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->पढ़ो_sensor)
		अगर (!smu->ppt_funcs->पढ़ो_sensor(smu, sensor, data, size))
			जाओ unlock;

	चयन (sensor) अणु
	हाल AMDGPU_PP_SENSOR_STABLE_PSTATE_SCLK:
		*((uपूर्णांक32_t *)data) = pstate_table->gfxclk_pstate.standard * 100;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_STABLE_PSTATE_MCLK:
		*((uपूर्णांक32_t *)data) = pstate_table->uclk_pstate.standard * 100;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_ENABLED_SMC_FEATURES_MASK:
		ret = smu_feature_get_enabled_mask(smu, (uपूर्णांक32_t *)data, 2);
		*size = 8;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_UVD_POWER:
		*(uपूर्णांक32_t *)data = smu_feature_is_enabled(smu, SMU_FEATURE_DPM_UVD_BIT) ? 1 : 0;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_VCE_POWER:
		*(uपूर्णांक32_t *)data = smu_feature_is_enabled(smu, SMU_FEATURE_DPM_VCE_BIT) ? 1 : 0;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_VCN_POWER_STATE:
		*(uपूर्णांक32_t *)data = atomic_पढ़ो(&smu->smu_घातer.घातer_gate.vcn_gated) ? 0: 1;
		*size = 4;
		अवरोध;
	हाल AMDGPU_PP_SENSOR_MIN_FAN_RPM:
		*(uपूर्णांक32_t *)data = 0;
		*size = 4;
		अवरोध;
	शेष:
		*size = 0;
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

unlock:
	mutex_unlock(&smu->mutex);

	// assign uपूर्णांक32_t to पूर्णांक
	*size_arg = size_val;

	वापस ret;
पूर्ण

अटल पूर्णांक smu_get_घातer_profile_mode(व्योम *handle, अक्षर *buf)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->get_घातer_profile_mode)
		ret = smu->ppt_funcs->get_घातer_profile_mode(smu, buf);

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_set_घातer_profile_mode(व्योम *handle,
				      दीर्घ *param,
				      uपूर्णांक32_t param_size)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	smu_bump_घातer_profile_mode(smu, param, param_size);

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण


अटल u32 smu_get_fan_control_mode(व्योम *handle)
अणु
	काष्ठा smu_context *smu = handle;
	u32 ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस AMD_FAN_CTRL_NONE;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->get_fan_control_mode)
		ret = smu->ppt_funcs->get_fan_control_mode(smu);

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_set_fan_control_mode(काष्ठा smu_context *smu, पूर्णांक value)
अणु
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस  -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->set_fan_control_mode) अणु
		ret = smu->ppt_funcs->set_fan_control_mode(smu, value);
		अगर (!ret && !(smu->user_dpm_profile.flags & SMU_DPM_USER_PROखाता_RESTORE))
			smu->user_dpm_profile.fan_mode = value;
	पूर्ण

	mutex_unlock(&smu->mutex);

	/* reset user dpm fan speed */
	अगर (!ret && value != AMD_FAN_CTRL_MANUAL &&
			!(smu->user_dpm_profile.flags & SMU_DPM_USER_PROखाता_RESTORE))
		smu->user_dpm_profile.fan_speed_percent = 0;

	वापस ret;
पूर्ण

अटल व्योम smu_pp_set_fan_control_mode(व्योम *handle, u32 value)
अणु
	काष्ठा smu_context *smu = handle;

	smu_set_fan_control_mode(smu, value);
पूर्ण


अटल पूर्णांक smu_get_fan_speed_percent(व्योम *handle, u32 *speed)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;
	uपूर्णांक32_t percent;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->get_fan_speed_percent) अणु
		ret = smu->ppt_funcs->get_fan_speed_percent(smu, &percent);
		अगर (!ret) अणु
			*speed = percent > 100 ? 100 : percent;
		पूर्ण
	पूर्ण

	mutex_unlock(&smu->mutex);


	वापस ret;
पूर्ण

अटल पूर्णांक smu_set_fan_speed_percent(व्योम *handle, u32 speed)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->set_fan_speed_percent) अणु
		अगर (speed > 100)
			speed = 100;
		ret = smu->ppt_funcs->set_fan_speed_percent(smu, speed);
		अगर (!ret && !(smu->user_dpm_profile.flags & SMU_DPM_USER_PROखाता_RESTORE))
			smu->user_dpm_profile.fan_speed_percent = speed;
	पूर्ण

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_get_fan_speed_rpm(व्योम *handle, uपूर्णांक32_t *speed)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;
	u32 percent;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->get_fan_speed_percent) अणु
		ret = smu->ppt_funcs->get_fan_speed_percent(smu, &percent);
		*speed = percent * smu->fan_max_rpm / 100;
	पूर्ण

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_set_deep_sleep_dcefclk(व्योम *handle, uपूर्णांक32_t clk)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	ret = smu_set_min_dcef_deep_sleep(smu, clk);

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_get_घड़ी_by_type_with_latency(व्योम *handle,
					      क्रमागत amd_pp_घड़ी_प्रकारype type,
					      काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	काष्ठा smu_context *smu = handle;
	क्रमागत smu_clk_type clk_type;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->get_घड़ी_by_type_with_latency) अणु
		चयन (type) अणु
		हाल amd_pp_sys_घड़ी:
			clk_type = SMU_GFXCLK;
			अवरोध;
		हाल amd_pp_mem_घड़ी:
			clk_type = SMU_MCLK;
			अवरोध;
		हाल amd_pp_dcef_घड़ी:
			clk_type = SMU_DCEFCLK;
			अवरोध;
		हाल amd_pp_disp_घड़ी:
			clk_type = SMU_DISPCLK;
			अवरोध;
		शेष:
			dev_err(smu->adev->dev, "Invalid clock type!\n");
			mutex_unlock(&smu->mutex);
			वापस -EINVAL;
		पूर्ण

		ret = smu->ppt_funcs->get_घड़ी_by_type_with_latency(smu, clk_type, घड़ीs);
	पूर्ण

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_display_घड़ी_voltage_request(व्योम *handle,
					     काष्ठा pp_display_घड़ी_request *घड़ी_req)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->display_घड़ी_voltage_request)
		ret = smu->ppt_funcs->display_घड़ी_voltage_request(smu, घड़ी_req);

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण


अटल पूर्णांक smu_display_disable_memory_घड़ी_चयन(व्योम *handle,
						   bool disable_memory_घड़ी_चयन)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = -EINVAL;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->display_disable_memory_घड़ी_चयन)
		ret = smu->ppt_funcs->display_disable_memory_घड़ी_चयन(smu, disable_memory_घड़ी_चयन);

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_set_xgmi_pstate(व्योम *handle,
			       uपूर्णांक32_t pstate)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->set_xgmi_pstate)
		ret = smu->ppt_funcs->set_xgmi_pstate(smu, pstate);

	mutex_unlock(&smu->mutex);

	अगर(ret)
		dev_err(smu->adev->dev, "Failed to set XGMI pstate!\n");

	वापस ret;
पूर्ण

अटल पूर्णांक smu_get_baco_capability(व्योम *handle, bool *cap)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;

	*cap = false;

	अगर (!smu->pm_enabled)
		वापस 0;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs && smu->ppt_funcs->baco_is_support)
		*cap = smu->ppt_funcs->baco_is_support(smu);

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_baco_set_state(व्योम *handle, पूर्णांक state)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled)
		वापस -EOPNOTSUPP;

	अगर (state == 0) अणु
		mutex_lock(&smu->mutex);

		अगर (smu->ppt_funcs->baco_निकास)
			ret = smu->ppt_funcs->baco_निकास(smu);

		mutex_unlock(&smu->mutex);
	पूर्ण अन्यथा अगर (state == 1) अणु
		mutex_lock(&smu->mutex);

		अगर (smu->ppt_funcs->baco_enter)
			ret = smu->ppt_funcs->baco_enter(smu);

		mutex_unlock(&smu->mutex);

	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (ret)
		dev_err(smu->adev->dev, "Failed to %s BACO state!\n",
				(state)?"enter":"exit");

	वापस ret;
पूर्ण

bool smu_mode1_reset_is_support(काष्ठा smu_context *smu)
अणु
	bool ret = false;

	अगर (!smu->pm_enabled)
		वापस false;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs && smu->ppt_funcs->mode1_reset_is_support)
		ret = smu->ppt_funcs->mode1_reset_is_support(smu);

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

bool smu_mode2_reset_is_support(काष्ठा smu_context *smu)
अणु
	bool ret = false;

	अगर (!smu->pm_enabled)
		वापस false;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs && smu->ppt_funcs->mode2_reset_is_support)
		ret = smu->ppt_funcs->mode2_reset_is_support(smu);

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

पूर्णांक smu_mode1_reset(काष्ठा smu_context *smu)
अणु
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->mode1_reset)
		ret = smu->ppt_funcs->mode1_reset(smu);

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_mode2_reset(व्योम *handle)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->mode2_reset)
		ret = smu->ppt_funcs->mode2_reset(smu);

	mutex_unlock(&smu->mutex);

	अगर (ret)
		dev_err(smu->adev->dev, "Mode2 reset failed!\n");

	वापस ret;
पूर्ण

अटल पूर्णांक smu_get_max_sustainable_घड़ीs_by_dc(व्योम *handle,
						काष्ठा pp_smu_nv_घड़ी_प्रकारable *max_घड़ीs)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->get_max_sustainable_घड़ीs_by_dc)
		ret = smu->ppt_funcs->get_max_sustainable_घड़ीs_by_dc(smu, max_घड़ीs);

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_get_uclk_dpm_states(व्योम *handle,
				   अचिन्हित पूर्णांक *घड़ी_values_in_khz,
				   अचिन्हित पूर्णांक *num_states)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->get_uclk_dpm_states)
		ret = smu->ppt_funcs->get_uclk_dpm_states(smu, घड़ी_values_in_khz, num_states);

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल क्रमागत amd_pm_state_type smu_get_current_घातer_state(व्योम *handle)
अणु
	काष्ठा smu_context *smu = handle;
	क्रमागत amd_pm_state_type pm_state = POWER_STATE_TYPE_DEFAULT;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->get_current_घातer_state)
		pm_state = smu->ppt_funcs->get_current_घातer_state(smu);

	mutex_unlock(&smu->mutex);

	वापस pm_state;
पूर्ण

अटल पूर्णांक smu_get_dpm_घड़ी_प्रकारable(व्योम *handle,
				   काष्ठा dpm_घड़ीs *घड़ी_प्रकारable)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->get_dpm_घड़ी_प्रकारable)
		ret = smu->ppt_funcs->get_dpm_घड़ी_प्रकारable(smu, घड़ी_प्रकारable);

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार smu_sys_get_gpu_metrics(व्योम *handle, व्योम **table)
अणु
	काष्ठा smu_context *smu = handle;
	sमाप_प्रकार size;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	अगर (!smu->ppt_funcs->get_gpu_metrics)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	size = smu->ppt_funcs->get_gpu_metrics(smu, table);

	mutex_unlock(&smu->mutex);

	वापस size;
पूर्ण

अटल पूर्णांक smu_enable_mgpu_fan_boost(व्योम *handle)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;

	अगर (!smu->pm_enabled || !smu->adev->pm.dpm_enabled)
		वापस -EOPNOTSUPP;

	mutex_lock(&smu->mutex);

	अगर (smu->ppt_funcs->enable_mgpu_fan_boost)
		ret = smu->ppt_funcs->enable_mgpu_fan_boost(smu);

	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक smu_gfx_state_change_set(व्योम *handle,
				    uपूर्णांक32_t state)
अणु
	काष्ठा smu_context *smu = handle;
	पूर्णांक ret = 0;

	mutex_lock(&smu->mutex);
	अगर (smu->ppt_funcs->gfx_state_change_set)
		ret = smu->ppt_funcs->gfx_state_change_set(smu, state);
	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण

पूर्णांक smu_set_light_sbr(काष्ठा smu_context *smu, bool enable)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&smu->mutex);
	अगर (smu->ppt_funcs->set_light_sbr)
		ret = smu->ppt_funcs->set_light_sbr(smu, enable);
	mutex_unlock(&smu->mutex);

	वापस ret;
पूर्ण


अटल स्थिर काष्ठा amd_pm_funcs swsmu_pm_funcs = अणु
	/* export क्रम sysfs */
	.set_fan_control_mode    = smu_pp_set_fan_control_mode,
	.get_fan_control_mode    = smu_get_fan_control_mode,
	.set_fan_speed_percent   = smu_set_fan_speed_percent,
	.get_fan_speed_percent   = smu_get_fan_speed_percent,
	.क्रमce_perक्रमmance_level = smu_क्रमce_perक्रमmance_level,
	.पढ़ो_sensor             = smu_पढ़ो_sensor,
	.get_perक्रमmance_level   = smu_get_perक्रमmance_level,
	.get_current_घातer_state = smu_get_current_घातer_state,
	.get_fan_speed_rpm       = smu_get_fan_speed_rpm,
	.set_fan_speed_rpm       = smu_set_fan_speed_rpm,
	.get_pp_num_states       = smu_get_घातer_num_states,
	.get_pp_table            = smu_sys_get_pp_table,
	.set_pp_table            = smu_sys_set_pp_table,
	.चयन_घातer_profile    = smu_चयन_घातer_profile,
	/* export to amdgpu */
	.dispatch_tasks          = smu_handle_dpm_task,
	.set_घातergating_by_smu  = smu_dpm_set_घातer_gate,
	.set_घातer_limit         = smu_set_घातer_limit,
	.odn_edit_dpm_table      = smu_od_edit_dpm_table,
	.set_mp1_state           = smu_set_mp1_state,
	/* export to DC */
	.get_sclk                = smu_get_sclk,
	.get_mclk                = smu_get_mclk,
	.enable_mgpu_fan_boost   = smu_enable_mgpu_fan_boost,
	.get_asic_baco_capability = smu_get_baco_capability,
	.set_asic_baco_state     = smu_baco_set_state,
	.get_ppfeature_status    = smu_sys_get_pp_feature_mask,
	.set_ppfeature_status    = smu_sys_set_pp_feature_mask,
	.asic_reset_mode_2       = smu_mode2_reset,
	.set_df_cstate           = smu_set_df_cstate,
	.set_xgmi_pstate         = smu_set_xgmi_pstate,
	.get_gpu_metrics         = smu_sys_get_gpu_metrics,
	.set_घातer_profile_mode  = smu_set_घातer_profile_mode,
	.get_घातer_profile_mode  = smu_get_घातer_profile_mode,
	.क्रमce_घड़ी_level       = smu_क्रमce_ppclk_levels,
	.prपूर्णांक_घड़ी_levels      = smu_prपूर्णांक_ppclk_levels,
	.get_uclk_dpm_states     = smu_get_uclk_dpm_states,
	.get_dpm_घड़ी_प्रकारable     = smu_get_dpm_घड़ी_प्रकारable,
	.display_configuration_change        = smu_display_configuration_change,
	.get_घड़ी_by_type_with_latency      = smu_get_घड़ी_by_type_with_latency,
	.display_घड़ी_voltage_request       = smu_display_घड़ी_voltage_request,
	.set_active_display_count            = smu_set_display_count,
	.set_min_deep_sleep_dcefclk          = smu_set_deep_sleep_dcefclk,
	.set_watermarks_क्रम_घड़ी_ranges     = smu_set_watermarks_क्रम_घड़ी_ranges,
	.display_disable_memory_घड़ी_चयन = smu_display_disable_memory_घड़ी_चयन,
	.get_max_sustainable_घड़ीs_by_dc    = smu_get_max_sustainable_घड़ीs_by_dc,
	.load_firmware           = smu_load_microcode,
	.gfx_state_change_set    = smu_gfx_state_change_set,
पूर्ण;

पूर्णांक smu_रुको_क्रम_event(काष्ठा amdgpu_device *adev, क्रमागत smu_event_type event,
		       uपूर्णांक64_t event_arg)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा smu_context *smu = &adev->smu;

	अगर (smu->ppt_funcs->रुको_क्रम_event) अणु
		mutex_lock(&smu->mutex);
		ret = smu->ppt_funcs->रुको_क्रम_event(smu, event, event_arg);
		mutex_unlock(&smu->mutex);
	पूर्ण

	वापस ret;
पूर्ण
