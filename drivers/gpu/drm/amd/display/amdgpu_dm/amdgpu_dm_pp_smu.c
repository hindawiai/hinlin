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
 * Authors: AMD
 */
#समावेश <linux/माला.स>
#समावेश <linux/acpi.h>

#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/amdgpu_drm.h>
#समावेश "dm_services.h"
#समावेश "amdgpu.h"
#समावेश "amdgpu_dm.h"
#समावेश "amdgpu_dm_irq.h"
#समावेश "amdgpu_pm.h"
#समावेश "dm_pp_smu.h"

bool dm_pp_apply_display_requirements(
		स्थिर काष्ठा dc_context *ctx,
		स्थिर काष्ठा dm_pp_display_configuration *pp_display_cfg)
अणु
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	पूर्णांक i;

	अगर (adev->pm.dpm_enabled) अणु

		स_रखो(&adev->pm.pm_display_cfg, 0,
				माप(adev->pm.pm_display_cfg));

		adev->pm.pm_display_cfg.cpu_cc6_disable =
			pp_display_cfg->cpu_cc6_disable;

		adev->pm.pm_display_cfg.cpu_pstate_disable =
			pp_display_cfg->cpu_pstate_disable;

		adev->pm.pm_display_cfg.cpu_pstate_separation_समय =
			pp_display_cfg->cpu_pstate_separation_समय;

		adev->pm.pm_display_cfg.nb_pstate_चयन_disable =
			pp_display_cfg->nb_pstate_चयन_disable;

		adev->pm.pm_display_cfg.num_display =
				pp_display_cfg->display_count;
		adev->pm.pm_display_cfg.num_path_including_non_display =
				pp_display_cfg->display_count;

		adev->pm.pm_display_cfg.min_core_set_घड़ी =
				pp_display_cfg->min_engine_घड़ी_khz/10;
		adev->pm.pm_display_cfg.min_core_set_घड़ी_in_sr =
				pp_display_cfg->min_engine_घड़ी_deep_sleep_khz/10;
		adev->pm.pm_display_cfg.min_mem_set_घड़ी =
				pp_display_cfg->min_memory_घड़ी_khz/10;

		adev->pm.pm_display_cfg.min_dcef_deep_sleep_set_clk =
				pp_display_cfg->min_engine_घड़ी_deep_sleep_khz/10;
		adev->pm.pm_display_cfg.min_dcef_set_clk =
				pp_display_cfg->min_dcfघड़ी_khz/10;

		adev->pm.pm_display_cfg.multi_monitor_in_sync =
				pp_display_cfg->all_displays_in_sync;
		adev->pm.pm_display_cfg.min_vblank_समय =
				pp_display_cfg->avail_mclk_चयन_समय_us;

		adev->pm.pm_display_cfg.display_clk =
				pp_display_cfg->disp_clk_khz/10;

		adev->pm.pm_display_cfg.dce_tolerable_mclk_in_active_latency =
				pp_display_cfg->avail_mclk_चयन_समय_in_disp_active_us;

		adev->pm.pm_display_cfg.crtc_index = pp_display_cfg->crtc_index;
		adev->pm.pm_display_cfg.line_समय_in_us =
				pp_display_cfg->line_समय_in_us;

		adev->pm.pm_display_cfg.vrefresh = pp_display_cfg->disp_configs[0].v_refresh;
		adev->pm.pm_display_cfg.crossfire_display_index = -1;
		adev->pm.pm_display_cfg.min_bus_bandwidth = 0;

		क्रम (i = 0; i < pp_display_cfg->display_count; i++) अणु
			स्थिर काष्ठा dm_pp_single_disp_config *dc_cfg =
						&pp_display_cfg->disp_configs[i];
			adev->pm.pm_display_cfg.displays[i].controller_id = dc_cfg->pipe_idx + 1;
		पूर्ण

		अगर (adev->घातerplay.pp_funcs && adev->घातerplay.pp_funcs->display_configuration_change)
			adev->घातerplay.pp_funcs->display_configuration_change(
				adev->घातerplay.pp_handle,
				&adev->pm.pm_display_cfg);

		amdgpu_pm_compute_घड़ीs(adev);
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम get_शेष_घड़ी_levels(
		क्रमागत dm_pp_घड़ी_प्रकारype clk_type,
		काष्ठा dm_pp_घड़ी_levels *clks)
अणु
	uपूर्णांक32_t disp_clks_in_khz[6] = अणु
			300000, 400000, 496560, 626090, 685720, 757900 पूर्ण;
	uपूर्णांक32_t sclks_in_khz[6] = अणु
			300000, 360000, 423530, 514290, 626090, 720000 पूर्ण;
	uपूर्णांक32_t mclks_in_khz[2] = अणु 333000, 800000 पूर्ण;

	चयन (clk_type) अणु
	हाल DM_PP_CLOCK_TYPE_DISPLAY_CLK:
		clks->num_levels = 6;
		स_हटाओ(clks->घड़ीs_in_khz, disp_clks_in_khz,
				माप(disp_clks_in_khz));
		अवरोध;
	हाल DM_PP_CLOCK_TYPE_ENGINE_CLK:
		clks->num_levels = 6;
		स_हटाओ(clks->घड़ीs_in_khz, sclks_in_khz,
				माप(sclks_in_khz));
		अवरोध;
	हाल DM_PP_CLOCK_TYPE_MEMORY_CLK:
		clks->num_levels = 2;
		स_हटाओ(clks->घड़ीs_in_khz, mclks_in_khz,
				माप(mclks_in_khz));
		अवरोध;
	शेष:
		clks->num_levels = 0;
		अवरोध;
	पूर्ण
पूर्ण

अटल क्रमागत amd_pp_घड़ी_प्रकारype dc_to_pp_घड़ी_प्रकारype(
		क्रमागत dm_pp_घड़ी_प्रकारype dm_pp_clk_type)
अणु
	क्रमागत amd_pp_घड़ी_प्रकारype amd_pp_clk_type = 0;

	चयन (dm_pp_clk_type) अणु
	हाल DM_PP_CLOCK_TYPE_DISPLAY_CLK:
		amd_pp_clk_type = amd_pp_disp_घड़ी;
		अवरोध;
	हाल DM_PP_CLOCK_TYPE_ENGINE_CLK:
		amd_pp_clk_type = amd_pp_sys_घड़ी;
		अवरोध;
	हाल DM_PP_CLOCK_TYPE_MEMORY_CLK:
		amd_pp_clk_type = amd_pp_mem_घड़ी;
		अवरोध;
	हाल DM_PP_CLOCK_TYPE_DCEFCLK:
		amd_pp_clk_type  = amd_pp_dcef_घड़ी;
		अवरोध;
	हाल DM_PP_CLOCK_TYPE_DCFCLK:
		amd_pp_clk_type = amd_pp_dcf_घड़ी;
		अवरोध;
	हाल DM_PP_CLOCK_TYPE_PIXELCLK:
		amd_pp_clk_type = amd_pp_pixel_घड़ी;
		अवरोध;
	हाल DM_PP_CLOCK_TYPE_FCLK:
		amd_pp_clk_type = amd_pp_f_घड़ी;
		अवरोध;
	हाल DM_PP_CLOCK_TYPE_DISPLAYPHYCLK:
		amd_pp_clk_type = amd_pp_phy_घड़ी;
		अवरोध;
	हाल DM_PP_CLOCK_TYPE_DPPCLK:
		amd_pp_clk_type = amd_pp_dpp_घड़ी;
		अवरोध;
	शेष:
		DRM_ERROR("DM_PPLIB: invalid clock type: %d!\n",
				dm_pp_clk_type);
		अवरोध;
	पूर्ण

	वापस amd_pp_clk_type;
पूर्ण

अटल क्रमागत dm_pp_घड़ीs_state pp_to_dc_घातerlevel_state(
			क्रमागत PP_DAL_POWERLEVEL max_घड़ीs_state)
अणु
	चयन (max_घड़ीs_state) अणु
	हाल PP_DAL_POWERLEVEL_0:
		वापस DM_PP_CLOCKS_DPM_STATE_LEVEL_0;
	हाल PP_DAL_POWERLEVEL_1:
		वापस DM_PP_CLOCKS_DPM_STATE_LEVEL_1;
	हाल PP_DAL_POWERLEVEL_2:
		वापस DM_PP_CLOCKS_DPM_STATE_LEVEL_2;
	हाल PP_DAL_POWERLEVEL_3:
		वापस DM_PP_CLOCKS_DPM_STATE_LEVEL_3;
	हाल PP_DAL_POWERLEVEL_4:
		वापस DM_PP_CLOCKS_DPM_STATE_LEVEL_4;
	हाल PP_DAL_POWERLEVEL_5:
		वापस DM_PP_CLOCKS_DPM_STATE_LEVEL_5;
	हाल PP_DAL_POWERLEVEL_6:
		वापस DM_PP_CLOCKS_DPM_STATE_LEVEL_6;
	हाल PP_DAL_POWERLEVEL_7:
		वापस DM_PP_CLOCKS_DPM_STATE_LEVEL_7;
	शेष:
		DRM_ERROR("DM_PPLIB: invalid powerlevel state: %d!\n",
				max_घड़ीs_state);
		वापस DM_PP_CLOCKS_STATE_INVALID;
	पूर्ण
पूर्ण

अटल व्योम pp_to_dc_घड़ी_levels(
		स्थिर काष्ठा amd_pp_घड़ीs *pp_clks,
		काष्ठा dm_pp_घड़ी_levels *dc_clks,
		क्रमागत dm_pp_घड़ी_प्रकारype dc_clk_type)
अणु
	uपूर्णांक32_t i;

	अगर (pp_clks->count > DM_PP_MAX_CLOCK_LEVELS) अणु
		DRM_INFO("DM_PPLIB: Warning: %s clock: number of levels %d exceeds maximum of %d!\n",
				DC_DECODE_PP_CLOCK_TYPE(dc_clk_type),
				pp_clks->count,
				DM_PP_MAX_CLOCK_LEVELS);

		dc_clks->num_levels = DM_PP_MAX_CLOCK_LEVELS;
	पूर्ण अन्यथा
		dc_clks->num_levels = pp_clks->count;

	DRM_INFO("DM_PPLIB: values for %s clock\n",
			DC_DECODE_PP_CLOCK_TYPE(dc_clk_type));

	क्रम (i = 0; i < dc_clks->num_levels; i++) अणु
		DRM_INFO("DM_PPLIB:\t %d\n", pp_clks->घड़ी[i]);
		dc_clks->घड़ीs_in_khz[i] = pp_clks->घड़ी[i];
	पूर्ण
पूर्ण

अटल व्योम pp_to_dc_घड़ी_levels_with_latency(
		स्थिर काष्ठा pp_घड़ी_levels_with_latency *pp_clks,
		काष्ठा dm_pp_घड़ी_levels_with_latency *clk_level_info,
		क्रमागत dm_pp_घड़ी_प्रकारype dc_clk_type)
अणु
	uपूर्णांक32_t i;

	अगर (pp_clks->num_levels > DM_PP_MAX_CLOCK_LEVELS) अणु
		DRM_INFO("DM_PPLIB: Warning: %s clock: number of levels %d exceeds maximum of %d!\n",
				DC_DECODE_PP_CLOCK_TYPE(dc_clk_type),
				pp_clks->num_levels,
				DM_PP_MAX_CLOCK_LEVELS);

		clk_level_info->num_levels = DM_PP_MAX_CLOCK_LEVELS;
	पूर्ण अन्यथा
		clk_level_info->num_levels = pp_clks->num_levels;

	DRM_DEBUG("DM_PPLIB: values for %s clock\n",
			DC_DECODE_PP_CLOCK_TYPE(dc_clk_type));

	क्रम (i = 0; i < clk_level_info->num_levels; i++) अणु
		DRM_DEBUG("DM_PPLIB:\t %d in kHz\n", pp_clks->data[i].घड़ीs_in_khz);
		clk_level_info->data[i].घड़ीs_in_khz = pp_clks->data[i].घड़ीs_in_khz;
		clk_level_info->data[i].latency_in_us = pp_clks->data[i].latency_in_us;
	पूर्ण
पूर्ण

अटल व्योम pp_to_dc_घड़ी_levels_with_voltage(
		स्थिर काष्ठा pp_घड़ी_levels_with_voltage *pp_clks,
		काष्ठा dm_pp_घड़ी_levels_with_voltage *clk_level_info,
		क्रमागत dm_pp_घड़ी_प्रकारype dc_clk_type)
अणु
	uपूर्णांक32_t i;

	अगर (pp_clks->num_levels > DM_PP_MAX_CLOCK_LEVELS) अणु
		DRM_INFO("DM_PPLIB: Warning: %s clock: number of levels %d exceeds maximum of %d!\n",
				DC_DECODE_PP_CLOCK_TYPE(dc_clk_type),
				pp_clks->num_levels,
				DM_PP_MAX_CLOCK_LEVELS);

		clk_level_info->num_levels = DM_PP_MAX_CLOCK_LEVELS;
	पूर्ण अन्यथा
		clk_level_info->num_levels = pp_clks->num_levels;

	DRM_INFO("DM_PPLIB: values for %s clock\n",
			DC_DECODE_PP_CLOCK_TYPE(dc_clk_type));

	क्रम (i = 0; i < clk_level_info->num_levels; i++) अणु
		DRM_INFO("DM_PPLIB:\t %d in kHz, %d in mV\n", pp_clks->data[i].घड़ीs_in_khz,
			 pp_clks->data[i].voltage_in_mv);
		clk_level_info->data[i].घड़ीs_in_khz = pp_clks->data[i].घड़ीs_in_khz;
		clk_level_info->data[i].voltage_in_mv = pp_clks->data[i].voltage_in_mv;
	पूर्ण
पूर्ण

bool dm_pp_get_घड़ी_levels_by_type(
		स्थिर काष्ठा dc_context *ctx,
		क्रमागत dm_pp_घड़ी_प्रकारype clk_type,
		काष्ठा dm_pp_घड़ी_levels *dc_clks)
अणु
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	काष्ठा amd_pp_घड़ीs pp_clks = अणु 0 पूर्ण;
	काष्ठा amd_pp_simple_घड़ी_info validation_clks = अणु 0 पूर्ण;
	uपूर्णांक32_t i;

	अगर (adev->घातerplay.pp_funcs && adev->घातerplay.pp_funcs->get_घड़ी_by_type) अणु
		अगर (adev->घातerplay.pp_funcs->get_घड़ी_by_type(pp_handle,
			dc_to_pp_घड़ी_प्रकारype(clk_type), &pp_clks)) अणु
			/* Error in pplib. Provide शेष values. */
			get_शेष_घड़ी_levels(clk_type, dc_clks);
			वापस true;
		पूर्ण
	पूर्ण

	pp_to_dc_घड़ी_levels(&pp_clks, dc_clks, clk_type);

	अगर (adev->घातerplay.pp_funcs && adev->घातerplay.pp_funcs->get_display_mode_validation_घड़ीs) अणु
		अगर (adev->घातerplay.pp_funcs->get_display_mode_validation_घड़ीs(
						pp_handle, &validation_clks)) अणु
			/* Error in pplib. Provide शेष values. */
			DRM_INFO("DM_PPLIB: Warning: using default validation clocks!\n");
			validation_clks.engine_max_घड़ी = 72000;
			validation_clks.memory_max_घड़ी = 80000;
			validation_clks.level = 0;
		पूर्ण
	पूर्ण

	DRM_INFO("DM_PPLIB: Validation clocks:\n");
	DRM_INFO("DM_PPLIB:    engine_max_clock: %d\n",
			validation_clks.engine_max_घड़ी);
	DRM_INFO("DM_PPLIB:    memory_max_clock: %d\n",
			validation_clks.memory_max_घड़ी);
	DRM_INFO("DM_PPLIB:    level           : %d\n",
			validation_clks.level);

	/* Translate 10 kHz to kHz. */
	validation_clks.engine_max_घड़ी *= 10;
	validation_clks.memory_max_घड़ी *= 10;

	/* Determine the highest non-boosted level from the Validation Clocks */
	अगर (clk_type == DM_PP_CLOCK_TYPE_ENGINE_CLK) अणु
		क्रम (i = 0; i < dc_clks->num_levels; i++) अणु
			अगर (dc_clks->घड़ीs_in_khz[i] > validation_clks.engine_max_घड़ी) अणु
				/* This घड़ी is higher the validation घड़ी.
				 * Than means the previous one is the highest
				 * non-boosted one. */
				DRM_INFO("DM_PPLIB: reducing engine clock level from %d to %d\n",
						dc_clks->num_levels, i);
				dc_clks->num_levels = i > 0 ? i : 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (clk_type == DM_PP_CLOCK_TYPE_MEMORY_CLK) अणु
		क्रम (i = 0; i < dc_clks->num_levels; i++) अणु
			अगर (dc_clks->घड़ीs_in_khz[i] > validation_clks.memory_max_घड़ी) अणु
				DRM_INFO("DM_PPLIB: reducing memory clock level from %d to %d\n",
						dc_clks->num_levels, i);
				dc_clks->num_levels = i > 0 ? i : 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

bool dm_pp_get_घड़ी_levels_by_type_with_latency(
	स्थिर काष्ठा dc_context *ctx,
	क्रमागत dm_pp_घड़ी_प्रकारype clk_type,
	काष्ठा dm_pp_घड़ी_levels_with_latency *clk_level_info)
अणु
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	काष्ठा pp_घड़ी_levels_with_latency pp_clks = अणु 0 पूर्ण;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	पूर्णांक ret;

	अगर (pp_funcs && pp_funcs->get_घड़ी_by_type_with_latency) अणु
		ret = pp_funcs->get_घड़ी_by_type_with_latency(pp_handle,
						dc_to_pp_घड़ी_प्रकारype(clk_type),
						&pp_clks);
		अगर (ret)
			वापस false;
	पूर्ण

	pp_to_dc_घड़ी_levels_with_latency(&pp_clks, clk_level_info, clk_type);

	वापस true;
पूर्ण

bool dm_pp_get_घड़ी_levels_by_type_with_voltage(
	स्थिर काष्ठा dc_context *ctx,
	क्रमागत dm_pp_घड़ी_प्रकारype clk_type,
	काष्ठा dm_pp_घड़ी_levels_with_voltage *clk_level_info)
अणु
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	काष्ठा pp_घड़ी_levels_with_voltage pp_clk_info = अणु0पूर्ण;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	पूर्णांक ret;

	अगर (pp_funcs && pp_funcs->get_घड़ी_by_type_with_voltage) अणु
		ret = pp_funcs->get_घड़ी_by_type_with_voltage(pp_handle,
						dc_to_pp_घड़ी_प्रकारype(clk_type),
						&pp_clk_info);
		अगर (ret)
			वापस false;
	पूर्ण

	pp_to_dc_घड़ी_levels_with_voltage(&pp_clk_info, clk_level_info, clk_type);

	वापस true;
पूर्ण

bool dm_pp_notअगरy_wm_घड़ी_changes(
	स्थिर काष्ठा dc_context *ctx,
	काष्ठा dm_pp_wm_sets_with_घड़ी_ranges *wm_with_घड़ी_ranges)
अणु
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;

	/*
	 * Limit this watermark setting क्रम Polaris क्रम now
	 * TODO: expand this to other ASICs
	 */
	अगर ((adev->asic_type >= CHIP_POLARIS10) && (adev->asic_type <= CHIP_VEGAM)
	     && pp_funcs && pp_funcs->set_watermarks_क्रम_घड़ीs_ranges) अणु
		अगर (!pp_funcs->set_watermarks_क्रम_घड़ीs_ranges(pp_handle,
						(व्योम *)wm_with_घड़ी_ranges))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

bool dm_pp_apply_घातer_level_change_request(
	स्थिर काष्ठा dc_context *ctx,
	काष्ठा dm_pp_घातer_level_change_request *level_change_req)
अणु
	/* TODO: to be implemented */
	वापस false;
पूर्ण

bool dm_pp_apply_घड़ी_क्रम_voltage_request(
	स्थिर काष्ठा dc_context *ctx,
	काष्ठा dm_pp_घड़ी_क्रम_voltage_req *घड़ी_क्रम_voltage_req)
अणु
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	काष्ठा pp_display_घड़ी_request pp_घड़ी_request = अणु0पूर्ण;
	पूर्णांक ret = 0;

	pp_घड़ी_request.घड़ी_प्रकारype = dc_to_pp_घड़ी_प्रकारype(घड़ी_क्रम_voltage_req->clk_type);
	pp_घड़ी_request.घड़ी_freq_in_khz = घड़ी_क्रम_voltage_req->घड़ीs_in_khz;

	अगर (!pp_घड़ी_request.घड़ी_प्रकारype)
		वापस false;

	अगर (adev->घातerplay.pp_funcs && adev->घातerplay.pp_funcs->display_घड़ी_voltage_request)
		ret = adev->घातerplay.pp_funcs->display_घड़ी_voltage_request(
			adev->घातerplay.pp_handle,
			&pp_घड़ी_request);
	अगर (ret)
		वापस false;
	वापस true;
पूर्ण

bool dm_pp_get_अटल_घड़ीs(
	स्थिर काष्ठा dc_context *ctx,
	काष्ठा dm_pp_अटल_घड़ी_info *अटल_clk_info)
अणु
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	काष्ठा amd_pp_घड़ी_info pp_clk_info = अणु0पूर्ण;
	पूर्णांक ret = 0;

	अगर (adev->घातerplay.pp_funcs && adev->घातerplay.pp_funcs->get_current_घड़ीs)
		ret = adev->घातerplay.pp_funcs->get_current_घड़ीs(
			adev->घातerplay.pp_handle,
			&pp_clk_info);
	अन्यथा
		वापस false;
	अगर (ret)
		वापस false;

	अटल_clk_info->max_घड़ीs_state = pp_to_dc_घातerlevel_state(pp_clk_info.max_घड़ीs_state);
	अटल_clk_info->max_mclk_khz = pp_clk_info.max_memory_घड़ी * 10;
	अटल_clk_info->max_sclk_khz = pp_clk_info.max_engine_घड़ी * 10;

	वापस true;
पूर्ण

अटल व्योम pp_rv_set_wm_ranges(काष्ठा pp_smu *pp,
		काष्ठा pp_smu_wm_range_sets *ranges)
अणु
	स्थिर काष्ठा dc_context *ctx = pp->dm;
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	काष्ठा dm_pp_wm_sets_with_घड़ी_ranges_soc15 wm_with_घड़ी_ranges;
	काष्ठा dm_pp_घड़ी_range_क्रम_dmअगर_wm_set_soc15 *wm_dce_घड़ीs = wm_with_घड़ी_ranges.wm_dmअगर_घड़ीs_ranges;
	काष्ठा dm_pp_घड़ी_range_क्रम_mcअगर_wm_set_soc15 *wm_soc_घड़ीs = wm_with_घड़ी_ranges.wm_mcअगर_घड़ीs_ranges;
	पूर्णांक32_t i;

	wm_with_घड़ी_ranges.num_wm_dmअगर_sets = ranges->num_पढ़ोer_wm_sets;
	wm_with_घड़ी_ranges.num_wm_mcअगर_sets = ranges->num_ग_लिखोr_wm_sets;

	क्रम (i = 0; i < wm_with_घड़ी_ranges.num_wm_dmअगर_sets; i++) अणु
		अगर (ranges->पढ़ोer_wm_sets[i].wm_inst > 3)
			wm_dce_घड़ीs[i].wm_set_id = WM_SET_A;
		अन्यथा
			wm_dce_घड़ीs[i].wm_set_id =
					ranges->पढ़ोer_wm_sets[i].wm_inst;
		wm_dce_घड़ीs[i].wm_max_dcfclk_clk_in_khz =
				ranges->पढ़ोer_wm_sets[i].max_drain_clk_mhz * 1000;
		wm_dce_घड़ीs[i].wm_min_dcfclk_clk_in_khz =
				ranges->पढ़ोer_wm_sets[i].min_drain_clk_mhz * 1000;
		wm_dce_घड़ीs[i].wm_max_mem_clk_in_khz =
				ranges->पढ़ोer_wm_sets[i].max_fill_clk_mhz * 1000;
		wm_dce_घड़ीs[i].wm_min_mem_clk_in_khz =
				ranges->पढ़ोer_wm_sets[i].min_fill_clk_mhz * 1000;
	पूर्ण

	क्रम (i = 0; i < wm_with_घड़ी_ranges.num_wm_mcअगर_sets; i++) अणु
		अगर (ranges->ग_लिखोr_wm_sets[i].wm_inst > 3)
			wm_soc_घड़ीs[i].wm_set_id = WM_SET_A;
		अन्यथा
			wm_soc_घड़ीs[i].wm_set_id =
					ranges->ग_लिखोr_wm_sets[i].wm_inst;
		wm_soc_घड़ीs[i].wm_max_socclk_clk_in_khz =
				ranges->ग_लिखोr_wm_sets[i].max_fill_clk_mhz * 1000;
		wm_soc_घड़ीs[i].wm_min_socclk_clk_in_khz =
				ranges->ग_लिखोr_wm_sets[i].min_fill_clk_mhz * 1000;
		wm_soc_घड़ीs[i].wm_max_mem_clk_in_khz =
				ranges->ग_लिखोr_wm_sets[i].max_drain_clk_mhz * 1000;
		wm_soc_घड़ीs[i].wm_min_mem_clk_in_khz =
				ranges->ग_लिखोr_wm_sets[i].min_drain_clk_mhz * 1000;
	पूर्ण

	अगर (pp_funcs && pp_funcs->set_watermarks_क्रम_घड़ीs_ranges)
		pp_funcs->set_watermarks_क्रम_घड़ीs_ranges(pp_handle,
							   &wm_with_घड़ी_ranges);
पूर्ण

अटल व्योम pp_rv_set_pme_wa_enable(काष्ठा pp_smu *pp)
अणु
	स्थिर काष्ठा dc_context *ctx = pp->dm;
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;

	अगर (pp_funcs && pp_funcs->notअगरy_smu_enable_pwe)
		pp_funcs->notअगरy_smu_enable_pwe(pp_handle);
पूर्ण

अटल व्योम pp_rv_set_active_display_count(काष्ठा pp_smu *pp, पूर्णांक count)
अणु
	स्थिर काष्ठा dc_context *ctx = pp->dm;
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;

	अगर (!pp_funcs || !pp_funcs->set_active_display_count)
		वापस;

	pp_funcs->set_active_display_count(pp_handle, count);
पूर्ण

अटल व्योम pp_rv_set_min_deep_sleep_dcfclk(काष्ठा pp_smu *pp, पूर्णांक घड़ी)
अणु
	स्थिर काष्ठा dc_context *ctx = pp->dm;
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;

	अगर (!pp_funcs || !pp_funcs->set_min_deep_sleep_dcefclk)
		वापस;

	pp_funcs->set_min_deep_sleep_dcefclk(pp_handle, घड़ी);
पूर्ण

अटल व्योम pp_rv_set_hard_min_dcefclk_by_freq(काष्ठा pp_smu *pp, पूर्णांक घड़ी)
अणु
	स्थिर काष्ठा dc_context *ctx = pp->dm;
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;

	अगर (!pp_funcs || !pp_funcs->set_hard_min_dcefclk_by_freq)
		वापस;

	pp_funcs->set_hard_min_dcefclk_by_freq(pp_handle, घड़ी);
पूर्ण

अटल व्योम pp_rv_set_hard_min_fclk_by_freq(काष्ठा pp_smu *pp, पूर्णांक mhz)
अणु
	स्थिर काष्ठा dc_context *ctx = pp->dm;
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;

	अगर (!pp_funcs || !pp_funcs->set_hard_min_fclk_by_freq)
		वापस;

	pp_funcs->set_hard_min_fclk_by_freq(pp_handle, mhz);
पूर्ण

अटल क्रमागत pp_smu_status pp_nv_set_wm_ranges(काष्ठा pp_smu *pp,
		काष्ठा pp_smu_wm_range_sets *ranges)
अणु
	स्थिर काष्ठा dc_context *ctx = pp->dm;
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;

	अगर (pp_funcs && pp_funcs->set_watermarks_क्रम_घड़ीs_ranges)
		pp_funcs->set_watermarks_क्रम_घड़ीs_ranges(pp_handle, ranges);

	वापस PP_SMU_RESULT_OK;
पूर्ण

अटल क्रमागत pp_smu_status pp_nv_set_display_count(काष्ठा pp_smu *pp, पूर्णांक count)
अणु
	स्थिर काष्ठा dc_context *ctx = pp->dm;
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;

	अगर (!pp_funcs || !pp_funcs->set_active_display_count)
		वापस PP_SMU_RESULT_UNSUPPORTED;

	/* 0: successful or smu.ppt_funcs->set_display_count = शून्य;  1: fail */
	अगर (pp_funcs->set_active_display_count(pp_handle, count))
		वापस PP_SMU_RESULT_FAIL;

	वापस PP_SMU_RESULT_OK;
पूर्ण

अटल क्रमागत pp_smu_status
pp_nv_set_min_deep_sleep_dcfclk(काष्ठा pp_smu *pp, पूर्णांक mhz)
अणु
	स्थिर काष्ठा dc_context *ctx = pp->dm;
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;

	अगर (!pp_funcs || !pp_funcs->set_min_deep_sleep_dcefclk)
		वापस PP_SMU_RESULT_UNSUPPORTED;

	/* 0: successful or smu.ppt_funcs->set_deep_sleep_dcefclk = शून्य;1: fail */
	अगर (pp_funcs->set_min_deep_sleep_dcefclk(pp_handle, mhz))
		वापस PP_SMU_RESULT_FAIL;

	वापस PP_SMU_RESULT_OK;
पूर्ण

अटल क्रमागत pp_smu_status pp_nv_set_hard_min_dcefclk_by_freq(
		काष्ठा pp_smu *pp, पूर्णांक mhz)
अणु
	स्थिर काष्ठा dc_context *ctx = pp->dm;
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	काष्ठा pp_display_घड़ी_request घड़ी_req;

	अगर (!pp_funcs || !pp_funcs->display_घड़ी_voltage_request)
		वापस PP_SMU_RESULT_UNSUPPORTED;

	घड़ी_req.घड़ी_प्रकारype = amd_pp_dcef_घड़ी;
	घड़ी_req.घड़ी_freq_in_khz = mhz * 1000;

	/* 0: successful or smu.ppt_funcs->display_घड़ी_voltage_request = शून्य
	 * 1: fail
	 */
	अगर (pp_funcs->display_घड़ी_voltage_request(pp_handle, &घड़ी_req))
		वापस PP_SMU_RESULT_FAIL;

	वापस PP_SMU_RESULT_OK;
पूर्ण

अटल क्रमागत pp_smu_status
pp_nv_set_hard_min_uclk_by_freq(काष्ठा pp_smu *pp, पूर्णांक mhz)
अणु
	स्थिर काष्ठा dc_context *ctx = pp->dm;
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	काष्ठा pp_display_घड़ी_request घड़ी_req;

	अगर (!pp_funcs || !pp_funcs->display_घड़ी_voltage_request)
		वापस PP_SMU_RESULT_UNSUPPORTED;

	घड़ी_req.घड़ी_प्रकारype = amd_pp_mem_घड़ी;
	घड़ी_req.घड़ी_freq_in_khz = mhz * 1000;

	/* 0: successful or smu.ppt_funcs->display_घड़ी_voltage_request = शून्य
	 * 1: fail
	 */
	अगर (pp_funcs->display_घड़ी_voltage_request(pp_handle, &घड़ी_req))
		वापस PP_SMU_RESULT_FAIL;

	वापस PP_SMU_RESULT_OK;
पूर्ण

अटल क्रमागत pp_smu_status pp_nv_set_pstate_handshake_support(
	काष्ठा pp_smu *pp, bool pstate_handshake_supported)
अणु
	स्थिर काष्ठा dc_context *ctx = pp->dm;
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;

	अगर (pp_funcs && pp_funcs->display_disable_memory_घड़ी_चयन) अणु
		अगर (pp_funcs->display_disable_memory_घड़ी_चयन(pp_handle,
								  !pstate_handshake_supported))
			वापस PP_SMU_RESULT_FAIL;
	पूर्ण

	वापस PP_SMU_RESULT_OK;
पूर्ण

अटल क्रमागत pp_smu_status pp_nv_set_voltage_by_freq(काष्ठा pp_smu *pp,
		क्रमागत pp_smu_nv_घड़ी_id घड़ी_id, पूर्णांक mhz)
अणु
	स्थिर काष्ठा dc_context *ctx = pp->dm;
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;
	काष्ठा pp_display_घड़ी_request घड़ी_req;

	अगर (!pp_funcs || !pp_funcs->display_घड़ी_voltage_request)
		वापस PP_SMU_RESULT_UNSUPPORTED;

	चयन (घड़ी_id) अणु
	हाल PP_SMU_NV_DISPCLK:
		घड़ी_req.घड़ी_प्रकारype = amd_pp_disp_घड़ी;
		अवरोध;
	हाल PP_SMU_NV_PHYCLK:
		घड़ी_req.घड़ी_प्रकारype = amd_pp_phy_घड़ी;
		अवरोध;
	हाल PP_SMU_NV_PIXELCLK:
		घड़ी_req.घड़ी_प्रकारype = amd_pp_pixel_घड़ी;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	घड़ी_req.घड़ी_freq_in_khz = mhz * 1000;

	/* 0: successful or smu.ppt_funcs->display_घड़ी_voltage_request = शून्य
	 * 1: fail
	 */
	अगर (pp_funcs->display_घड़ी_voltage_request(pp_handle, &घड़ी_req))
		वापस PP_SMU_RESULT_FAIL;

	वापस PP_SMU_RESULT_OK;
पूर्ण

अटल क्रमागत pp_smu_status pp_nv_get_maximum_sustainable_घड़ीs(
		काष्ठा pp_smu *pp, काष्ठा pp_smu_nv_घड़ी_प्रकारable *max_घड़ीs)
अणु
	स्थिर काष्ठा dc_context *ctx = pp->dm;
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;

	अगर (!pp_funcs || !pp_funcs->get_max_sustainable_घड़ीs_by_dc)
		वापस PP_SMU_RESULT_UNSUPPORTED;

	अगर (!pp_funcs->get_max_sustainable_घड़ीs_by_dc(pp_handle, max_घड़ीs))
		वापस PP_SMU_RESULT_OK;

	वापस PP_SMU_RESULT_FAIL;
पूर्ण

अटल क्रमागत pp_smu_status pp_nv_get_uclk_dpm_states(काष्ठा pp_smu *pp,
		अचिन्हित पूर्णांक *घड़ी_values_in_khz, अचिन्हित पूर्णांक *num_states)
अणु
	स्थिर काष्ठा dc_context *ctx = pp->dm;
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;

	अगर (!pp_funcs || !pp_funcs->get_uclk_dpm_states)
		वापस PP_SMU_RESULT_UNSUPPORTED;

	अगर (!pp_funcs->get_uclk_dpm_states(pp_handle,
					   घड़ी_values_in_khz,
					   num_states))
		वापस PP_SMU_RESULT_OK;

	वापस PP_SMU_RESULT_FAIL;
पूर्ण

अटल क्रमागत pp_smu_status pp_rn_get_dpm_घड़ी_प्रकारable(
		काष्ठा pp_smu *pp, काष्ठा dpm_घड़ीs *घड़ी_प्रकारable)
अणु
	स्थिर काष्ठा dc_context *ctx = pp->dm;
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;

	अगर (!pp_funcs || !pp_funcs->get_dpm_घड़ी_प्रकारable)
		वापस PP_SMU_RESULT_UNSUPPORTED;

	अगर (!pp_funcs->get_dpm_घड़ी_प्रकारable(pp_handle, घड़ी_प्रकारable))
		वापस PP_SMU_RESULT_OK;

	वापस PP_SMU_RESULT_FAIL;
पूर्ण

अटल क्रमागत pp_smu_status pp_rn_set_wm_ranges(काष्ठा pp_smu *pp,
		काष्ठा pp_smu_wm_range_sets *ranges)
अणु
	स्थिर काष्ठा dc_context *ctx = pp->dm;
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	व्योम *pp_handle = adev->घातerplay.pp_handle;
	स्थिर काष्ठा amd_pm_funcs *pp_funcs = adev->घातerplay.pp_funcs;

	अगर (pp_funcs && pp_funcs->set_watermarks_क्रम_घड़ीs_ranges)
		pp_funcs->set_watermarks_क्रम_घड़ीs_ranges(pp_handle, ranges);

	वापस PP_SMU_RESULT_OK;
पूर्ण

व्योम dm_pp_get_funcs(
		काष्ठा dc_context *ctx,
		काष्ठा pp_smu_funcs *funcs)
अणु
	चयन (ctx->dce_version) अणु
	हाल DCN_VERSION_1_0:
	हाल DCN_VERSION_1_01:
		funcs->ctx.ver = PP_SMU_VER_RV;
		funcs->rv_funcs.pp_smu.dm = ctx;
		funcs->rv_funcs.set_wm_ranges = pp_rv_set_wm_ranges;
		funcs->rv_funcs.set_pme_wa_enable = pp_rv_set_pme_wa_enable;
		funcs->rv_funcs.set_display_count =
				pp_rv_set_active_display_count;
		funcs->rv_funcs.set_min_deep_sleep_dcfclk =
				pp_rv_set_min_deep_sleep_dcfclk;
		funcs->rv_funcs.set_hard_min_dcfclk_by_freq =
				pp_rv_set_hard_min_dcefclk_by_freq;
		funcs->rv_funcs.set_hard_min_fclk_by_freq =
				pp_rv_set_hard_min_fclk_by_freq;
		अवरोध;
	हाल DCN_VERSION_2_0:
		funcs->ctx.ver = PP_SMU_VER_NV;
		funcs->nv_funcs.pp_smu.dm = ctx;
		funcs->nv_funcs.set_display_count = pp_nv_set_display_count;
		funcs->nv_funcs.set_hard_min_dcfclk_by_freq =
				pp_nv_set_hard_min_dcefclk_by_freq;
		funcs->nv_funcs.set_min_deep_sleep_dcfclk =
				pp_nv_set_min_deep_sleep_dcfclk;
		funcs->nv_funcs.set_voltage_by_freq =
				pp_nv_set_voltage_by_freq;
		funcs->nv_funcs.set_wm_ranges = pp_nv_set_wm_ranges;

		/* toकरो set_pme_wa_enable cause 4k@6ohz display not light up */
		funcs->nv_funcs.set_pme_wa_enable = शून्य;
		/* toकरो debug waring message */
		funcs->nv_funcs.set_hard_min_uclk_by_freq = pp_nv_set_hard_min_uclk_by_freq;
		/* toकरो  compare data with winकरोw driver*/
		funcs->nv_funcs.get_maximum_sustainable_घड़ीs = pp_nv_get_maximum_sustainable_घड़ीs;
		/*toकरो  compare data with winकरोw driver */
		funcs->nv_funcs.get_uclk_dpm_states = pp_nv_get_uclk_dpm_states;
		funcs->nv_funcs.set_pstate_handshake_support = pp_nv_set_pstate_handshake_support;
		अवरोध;

	हाल DCN_VERSION_2_1:
		funcs->ctx.ver = PP_SMU_VER_RN;
		funcs->rn_funcs.pp_smu.dm = ctx;
		funcs->rn_funcs.set_wm_ranges = pp_rn_set_wm_ranges;
		funcs->rn_funcs.get_dpm_घड़ी_प्रकारable = pp_rn_get_dpm_घड़ी_प्रकारable;
		अवरोध;
	शेष:
		DRM_ERROR("smu version is not supported !\n");
		अवरोध;
	पूर्ण
पूर्ण
