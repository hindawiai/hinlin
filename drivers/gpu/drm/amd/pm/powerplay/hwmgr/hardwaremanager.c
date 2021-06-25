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
#समावेश <linux/त्रुटिसं.स>
#समावेश "hwmgr.h"
#समावेश "hardwaremanager.h"
#समावेश "power_state.h"


#घोषणा TEMP_RANGE_MIN (0)
#घोषणा TEMP_RANGE_MAX (80 * 1000)

#घोषणा PHM_FUNC_CHECK(hw) \
	करो अणु							\
		अगर ((hw) == शून्य || (hw)->hwmgr_func == शून्य)	\
			वापस -EINVAL;				\
	पूर्ण जबतक (0)

पूर्णांक phm_setup_asic(काष्ठा pp_hwmgr *hwmgr)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (शून्य != hwmgr->hwmgr_func->asic_setup)
		वापस hwmgr->hwmgr_func->asic_setup(hwmgr);

	वापस 0;
पूर्ण

पूर्णांक phm_घातer_करोwn_asic(काष्ठा pp_hwmgr *hwmgr)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (शून्य != hwmgr->hwmgr_func->घातer_off_asic)
		वापस hwmgr->hwmgr_func->घातer_off_asic(hwmgr);

	वापस 0;
पूर्ण

पूर्णांक phm_set_घातer_state(काष्ठा pp_hwmgr *hwmgr,
		    स्थिर काष्ठा pp_hw_घातer_state *pcurrent_state,
		    स्थिर काष्ठा pp_hw_घातer_state *pnew_घातer_state)
अणु
	काष्ठा phm_set_घातer_state_input states;

	PHM_FUNC_CHECK(hwmgr);

	states.pcurrent_state = pcurrent_state;
	states.pnew_state = pnew_घातer_state;

	अगर (शून्य != hwmgr->hwmgr_func->घातer_state_set)
		वापस hwmgr->hwmgr_func->घातer_state_set(hwmgr, &states);

	वापस 0;
पूर्ण

पूर्णांक phm_enable_dynamic_state_management(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = शून्य;
	पूर्णांक ret = -EINVAL;
	PHM_FUNC_CHECK(hwmgr);
	adev = hwmgr->adev;

	/* Skip क्रम suspend/resume हाल */
	अगर (!hwmgr->pp_one_vf && smum_is_dpm_running(hwmgr)
	    && !amdgpu_passthrough(adev) && adev->in_suspend) अणु
		pr_info("dpm has been enabled\n");
		वापस 0;
	पूर्ण

	अगर (शून्य != hwmgr->hwmgr_func->dynamic_state_management_enable)
		ret = hwmgr->hwmgr_func->dynamic_state_management_enable(hwmgr);

	वापस ret;
पूर्ण

पूर्णांक phm_disable_dynamic_state_management(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक ret = -EINVAL;

	PHM_FUNC_CHECK(hwmgr);

	अगर (!hwmgr->not_vf)
		वापस 0;

	अगर (!smum_is_dpm_running(hwmgr)) अणु
		pr_info("dpm has been disabled\n");
		वापस 0;
	पूर्ण

	अगर (hwmgr->hwmgr_func->dynamic_state_management_disable)
		ret = hwmgr->hwmgr_func->dynamic_state_management_disable(hwmgr);

	वापस ret;
पूर्ण

पूर्णांक phm_क्रमce_dpm_levels(काष्ठा pp_hwmgr *hwmgr, क्रमागत amd_dpm_क्रमced_level level)
अणु
	पूर्णांक ret = 0;

	PHM_FUNC_CHECK(hwmgr);

	अगर (hwmgr->hwmgr_func->क्रमce_dpm_level != शून्य)
		ret = hwmgr->hwmgr_func->क्रमce_dpm_level(hwmgr, level);

	वापस ret;
पूर्ण

पूर्णांक phm_apply_state_adjust_rules(काष्ठा pp_hwmgr *hwmgr,
				   काष्ठा pp_घातer_state *adjusted_ps,
			     स्थिर काष्ठा pp_घातer_state *current_ps)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (hwmgr->hwmgr_func->apply_state_adjust_rules != शून्य)
		वापस hwmgr->hwmgr_func->apply_state_adjust_rules(
									hwmgr,
								 adjusted_ps,
								 current_ps);
	वापस 0;
पूर्ण

पूर्णांक phm_apply_घड़ी_adjust_rules(काष्ठा pp_hwmgr *hwmgr)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (hwmgr->hwmgr_func->apply_घड़ीs_adjust_rules != शून्य)
		वापस hwmgr->hwmgr_func->apply_घड़ीs_adjust_rules(hwmgr);
	वापस 0;
पूर्ण

पूर्णांक phm_घातerकरोwn_uvd(काष्ठा pp_hwmgr *hwmgr)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (hwmgr->hwmgr_func->घातerकरोwn_uvd != शून्य)
		वापस hwmgr->hwmgr_func->घातerकरोwn_uvd(hwmgr);
	वापस 0;
पूर्ण


पूर्णांक phm_disable_घड़ी_घातer_gatings(काष्ठा pp_hwmgr *hwmgr)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (शून्य != hwmgr->hwmgr_func->disable_घड़ी_घातer_gating)
		वापस hwmgr->hwmgr_func->disable_घड़ी_घातer_gating(hwmgr);

	वापस 0;
पूर्ण

पूर्णांक phm_pre_display_configuration_changed(काष्ठा pp_hwmgr *hwmgr)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (शून्य != hwmgr->hwmgr_func->pre_display_config_changed)
		hwmgr->hwmgr_func->pre_display_config_changed(hwmgr);

	वापस 0;

पूर्ण

पूर्णांक phm_display_configuration_changed(काष्ठा pp_hwmgr *hwmgr)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (शून्य != hwmgr->hwmgr_func->display_config_changed)
		hwmgr->hwmgr_func->display_config_changed(hwmgr);

	वापस 0;
पूर्ण

पूर्णांक phm_notअगरy_smc_display_config_after_ps_adjusपंचांगent(काष्ठा pp_hwmgr *hwmgr)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (शून्य != hwmgr->hwmgr_func->notअगरy_smc_display_config_after_ps_adjusपंचांगent)
			hwmgr->hwmgr_func->notअगरy_smc_display_config_after_ps_adjusपंचांगent(hwmgr);

	वापस 0;
पूर्ण

पूर्णांक phm_stop_thermal_controller(काष्ठा pp_hwmgr *hwmgr)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (!hwmgr->not_vf)
		वापस 0;

	अगर (hwmgr->hwmgr_func->stop_thermal_controller == शून्य)
		वापस -EINVAL;

	वापस hwmgr->hwmgr_func->stop_thermal_controller(hwmgr);
पूर्ण

पूर्णांक phm_रेजिस्टर_irq_handlers(काष्ठा pp_hwmgr *hwmgr)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (hwmgr->hwmgr_func->रेजिस्टर_irq_handlers != शून्य)
		वापस hwmgr->hwmgr_func->रेजिस्टर_irq_handlers(hwmgr);

	वापस 0;
पूर्ण

/**
 * phm_start_thermal_controller - Initializes the thermal controller subप्रणाली.
 *
 * @hwmgr:   the address of the घातerplay hardware manager.
 * Exception PP_Result_Failed अगर any of the paramters is शून्य, otherwise the वापस value from the dispatcher.
 */
पूर्णांक phm_start_thermal_controller(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक ret = 0;
	काष्ठा PP_TemperatureRange range = अणु
		TEMP_RANGE_MIN,
		TEMP_RANGE_MAX,
		TEMP_RANGE_MAX,
		TEMP_RANGE_MIN,
		TEMP_RANGE_MAX,
		TEMP_RANGE_MAX,
		TEMP_RANGE_MIN,
		TEMP_RANGE_MAX,
		TEMP_RANGE_MAXपूर्ण;
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	अगर (!hwmgr->not_vf)
		वापस 0;

	अगर (hwmgr->hwmgr_func->get_thermal_temperature_range)
		hwmgr->hwmgr_func->get_thermal_temperature_range(
				hwmgr, &range);

	अगर (phm_cap_enabled(hwmgr->platक्रमm_descriptor.platक्रमmCaps,
			PHM_Platक्रमmCaps_ThermalController)
			&& hwmgr->hwmgr_func->start_thermal_controller != शून्य)
		ret = hwmgr->hwmgr_func->start_thermal_controller(hwmgr, &range);

	adev->pm.dpm.thermal.min_temp = range.min;
	adev->pm.dpm.thermal.max_temp = range.max;
	adev->pm.dpm.thermal.max_edge_emergency_temp = range.edge_emergency_max;
	adev->pm.dpm.thermal.min_hotspot_temp = range.hotspot_min;
	adev->pm.dpm.thermal.max_hotspot_crit_temp = range.hotspot_crit_max;
	adev->pm.dpm.thermal.max_hotspot_emergency_temp = range.hotspot_emergency_max;
	adev->pm.dpm.thermal.min_mem_temp = range.mem_min;
	adev->pm.dpm.thermal.max_mem_crit_temp = range.mem_crit_max;
	adev->pm.dpm.thermal.max_mem_emergency_temp = range.mem_emergency_max;

	वापस ret;
पूर्ण


bool phm_check_smc_update_required_क्रम_display_configuration(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (hwmgr == शून्य ||
	    hwmgr->hwmgr_func == शून्य)
		वापस false;

	अगर (hwmgr->pp_one_vf)
		वापस false;

	अगर (hwmgr->hwmgr_func->check_smc_update_required_क्रम_display_configuration == शून्य)
		वापस false;

	वापस hwmgr->hwmgr_func->check_smc_update_required_क्रम_display_configuration(hwmgr);
पूर्ण


पूर्णांक phm_check_states_equal(काष्ठा pp_hwmgr *hwmgr,
				 स्थिर काष्ठा pp_hw_घातer_state *pstate1,
				 स्थिर काष्ठा pp_hw_घातer_state *pstate2,
				 bool *equal)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (hwmgr->hwmgr_func->check_states_equal == शून्य)
		वापस -EINVAL;

	वापस hwmgr->hwmgr_func->check_states_equal(hwmgr, pstate1, pstate2, equal);
पूर्ण

पूर्णांक phm_store_dal_configuration_data(काष्ठा pp_hwmgr *hwmgr,
		    स्थिर काष्ठा amd_pp_display_configuration *display_config)
अणु
	पूर्णांक index = 0;
	पूर्णांक number_of_active_display = 0;

	PHM_FUNC_CHECK(hwmgr);

	अगर (display_config == शून्य)
		वापस -EINVAL;

	अगर (शून्य != hwmgr->hwmgr_func->set_min_deep_sleep_dcefclk)
		hwmgr->hwmgr_func->set_min_deep_sleep_dcefclk(hwmgr, display_config->min_dcef_deep_sleep_set_clk);

	क्रम (index = 0; index < display_config->num_path_including_non_display; index++) अणु
		अगर (display_config->displays[index].controller_id != 0)
			number_of_active_display++;
	पूर्ण

	अगर (शून्य != hwmgr->hwmgr_func->set_active_display_count)
		hwmgr->hwmgr_func->set_active_display_count(hwmgr, number_of_active_display);

	अगर (hwmgr->hwmgr_func->store_cc6_data == शून्य)
		वापस -EINVAL;

	/* TODO: pass other display configuration in the future */

	अगर (hwmgr->hwmgr_func->store_cc6_data)
		hwmgr->hwmgr_func->store_cc6_data(hwmgr,
				display_config->cpu_pstate_separation_समय,
				display_config->cpu_cc6_disable,
				display_config->cpu_pstate_disable,
				display_config->nb_pstate_चयन_disable);

	वापस 0;
पूर्ण

पूर्णांक phm_get_dal_घातer_level(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा amd_pp_simple_घड़ी_info *info)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (info == शून्य || hwmgr->hwmgr_func->get_dal_घातer_level == शून्य)
		वापस -EINVAL;
	वापस hwmgr->hwmgr_func->get_dal_घातer_level(hwmgr, info);
पूर्ण

पूर्णांक phm_set_cpu_घातer_state(काष्ठा pp_hwmgr *hwmgr)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (hwmgr->hwmgr_func->set_cpu_घातer_state != शून्य)
		वापस hwmgr->hwmgr_func->set_cpu_घातer_state(hwmgr);

	वापस 0;
पूर्ण


पूर्णांक phm_get_perक्रमmance_level(काष्ठा pp_hwmgr *hwmgr, स्थिर काष्ठा pp_hw_घातer_state *state,
				PHM_Perक्रमmanceLevelDesignation designation, uपूर्णांक32_t index,
				PHM_Perक्रमmanceLevel *level)
अणु
	PHM_FUNC_CHECK(hwmgr);
	अगर (hwmgr->hwmgr_func->get_perक्रमmance_level == शून्य)
		वापस -EINVAL;

	वापस hwmgr->hwmgr_func->get_perक्रमmance_level(hwmgr, state, designation, index, level);


पूर्ण


/**
 * phm_get_घड़ी_info
 *
 * @hwmgr:  the address of the घातerplay hardware manager.
 * @state: the address of the Power State काष्ठाure.
 * @pघड़ी_info: the address of PP_ClockInfo काष्ठाure where the result will be वापसed.
 * @designation: PHM perक्रमmance level designation
 * Exception PP_Result_Failed अगर any of the paramters is शून्य, otherwise the वापस value from the back-end.
 */
पूर्णांक phm_get_घड़ी_info(काष्ठा pp_hwmgr *hwmgr, स्थिर काष्ठा pp_hw_घातer_state *state, काष्ठा pp_घड़ी_info *pघड़ी_info,
			PHM_Perक्रमmanceLevelDesignation designation)
अणु
	पूर्णांक result;
	PHM_Perक्रमmanceLevel perक्रमmance_level = अणु0पूर्ण;

	PHM_FUNC_CHECK(hwmgr);

	PP_ASSERT_WITH_CODE((शून्य != state), "Invalid Input!", वापस -EINVAL);
	PP_ASSERT_WITH_CODE((शून्य != pघड़ी_info), "Invalid Input!", वापस -EINVAL);

	result = phm_get_perक्रमmance_level(hwmgr, state, PHM_Perक्रमmanceLevelDesignation_Activity, 0, &perक्रमmance_level);

	PP_ASSERT_WITH_CODE((0 == result), "Failed to retrieve minimum clocks.", वापस result);


	pघड़ी_info->min_mem_clk = perक्रमmance_level.memory_घड़ी;
	pघड़ी_info->min_eng_clk = perक्रमmance_level.coreClock;
	pघड़ी_info->min_bus_bandwidth = perक्रमmance_level.nonLocalMemoryFreq * perक्रमmance_level.nonLocalMemoryWidth;


	result = phm_get_perक्रमmance_level(hwmgr, state, designation,
					(hwmgr->platक्रमm_descriptor.hardwareActivityPerक्रमmanceLevels - 1), &perक्रमmance_level);

	PP_ASSERT_WITH_CODE((0 == result), "Failed to retrieve maximum clocks.", वापस result);

	pघड़ी_info->max_mem_clk = perक्रमmance_level.memory_घड़ी;
	pघड़ी_info->max_eng_clk = perक्रमmance_level.coreClock;
	pघड़ी_info->max_bus_bandwidth = perक्रमmance_level.nonLocalMemoryFreq * perक्रमmance_level.nonLocalMemoryWidth;

	वापस 0;
पूर्ण

पूर्णांक phm_get_current_shallow_sleep_घड़ीs(काष्ठा pp_hwmgr *hwmgr, स्थिर काष्ठा pp_hw_घातer_state *state, काष्ठा pp_घड़ी_info *घड़ी_info)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (hwmgr->hwmgr_func->get_current_shallow_sleep_घड़ीs == शून्य)
		वापस -EINVAL;

	वापस hwmgr->hwmgr_func->get_current_shallow_sleep_घड़ीs(hwmgr, state, घड़ी_info);

पूर्ण

पूर्णांक phm_get_घड़ी_by_type(काष्ठा pp_hwmgr *hwmgr, क्रमागत amd_pp_घड़ी_प्रकारype type, काष्ठा amd_pp_घड़ीs *घड़ीs)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (hwmgr->hwmgr_func->get_घड़ी_by_type == शून्य)
		वापस -EINVAL;

	वापस hwmgr->hwmgr_func->get_घड़ी_by_type(hwmgr, type, घड़ीs);

पूर्ण

पूर्णांक phm_get_घड़ी_by_type_with_latency(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत amd_pp_घड़ी_प्रकारype type,
		काष्ठा pp_घड़ी_levels_with_latency *घड़ीs)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (hwmgr->hwmgr_func->get_घड़ी_by_type_with_latency == शून्य)
		वापस -EINVAL;

	वापस hwmgr->hwmgr_func->get_घड़ी_by_type_with_latency(hwmgr, type, घड़ीs);

पूर्ण

पूर्णांक phm_get_घड़ी_by_type_with_voltage(काष्ठा pp_hwmgr *hwmgr,
		क्रमागत amd_pp_घड़ी_प्रकारype type,
		काष्ठा pp_घड़ी_levels_with_voltage *घड़ीs)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (hwmgr->hwmgr_func->get_घड़ी_by_type_with_voltage == शून्य)
		वापस -EINVAL;

	वापस hwmgr->hwmgr_func->get_घड़ी_by_type_with_voltage(hwmgr, type, घड़ीs);

पूर्ण

पूर्णांक phm_set_watermarks_क्रम_घड़ीs_ranges(काष्ठा pp_hwmgr *hwmgr,
					व्योम *घड़ी_ranges)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (!hwmgr->hwmgr_func->set_watermarks_क्रम_घड़ीs_ranges)
		वापस -EINVAL;

	वापस hwmgr->hwmgr_func->set_watermarks_क्रम_घड़ीs_ranges(hwmgr,
								घड़ी_ranges);
पूर्ण

पूर्णांक phm_display_घड़ी_voltage_request(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा pp_display_घड़ी_request *घड़ी)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (!hwmgr->hwmgr_func->display_घड़ी_voltage_request)
		वापस -EINVAL;

	वापस hwmgr->hwmgr_func->display_घड़ी_voltage_request(hwmgr, घड़ी);
पूर्ण

पूर्णांक phm_get_max_high_घड़ीs(काष्ठा pp_hwmgr *hwmgr, काष्ठा amd_pp_simple_घड़ी_info *घड़ीs)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (hwmgr->hwmgr_func->get_max_high_घड़ीs == शून्य)
		वापस -EINVAL;

	वापस hwmgr->hwmgr_func->get_max_high_घड़ीs(hwmgr, घड़ीs);
पूर्ण

पूर्णांक phm_disable_smc_firmware_ctf(काष्ठा pp_hwmgr *hwmgr)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (!hwmgr->not_vf)
		वापस 0;

	अगर (hwmgr->hwmgr_func->disable_smc_firmware_ctf == शून्य)
		वापस -EINVAL;

	वापस hwmgr->hwmgr_func->disable_smc_firmware_ctf(hwmgr);
पूर्ण

पूर्णांक phm_set_active_display_count(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t count)
अणु
	PHM_FUNC_CHECK(hwmgr);

	अगर (!hwmgr->hwmgr_func->set_active_display_count)
		वापस -EINVAL;

	वापस hwmgr->hwmgr_func->set_active_display_count(hwmgr, count);
पूर्ण
