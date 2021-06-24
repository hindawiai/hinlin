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

#समावेश "vega20_thermal.h"
#समावेश "vega20_hwmgr.h"
#समावेश "vega20_smumgr.h"
#समावेश "vega20_ppsmc.h"
#समावेश "vega20_inc.h"
#समावेश "soc15_common.h"
#समावेश "pp_debug.h"

अटल पूर्णांक vega20_disable_fan_control_feature(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data = hwmgr->backend;
	पूर्णांक ret = 0;

	अगर (data->smu_features[GNLD_FAN_CONTROL].supported) अणु
		ret = vega20_enable_smc_features(
				hwmgr, false,
				data->smu_features[GNLD_FAN_CONTROL].
				smu_feature_biपंचांगap);
		PP_ASSERT_WITH_CODE(!ret,
				"Disable FAN CONTROL feature Failed!",
				वापस ret);
		data->smu_features[GNLD_FAN_CONTROL].enabled = false;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक vega20_fan_ctrl_stop_smc_fan_control(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data = hwmgr->backend;

	अगर (data->smu_features[GNLD_FAN_CONTROL].supported)
		वापस vega20_disable_fan_control_feature(hwmgr);

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_enable_fan_control_feature(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data = hwmgr->backend;
	पूर्णांक ret = 0;

	अगर (data->smu_features[GNLD_FAN_CONTROL].supported) अणु
		ret = vega20_enable_smc_features(
				hwmgr, true,
				data->smu_features[GNLD_FAN_CONTROL].
				smu_feature_biपंचांगap);
		PP_ASSERT_WITH_CODE(!ret,
				"Enable FAN CONTROL feature Failed!",
				वापस ret);
		data->smu_features[GNLD_FAN_CONTROL].enabled = true;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक vega20_fan_ctrl_start_smc_fan_control(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega20_hwmgr *data = hwmgr->backend;

	अगर (data->smu_features[GNLD_FAN_CONTROL].supported)
		वापस vega20_enable_fan_control_feature(hwmgr);

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_fan_ctrl_set_अटल_mode(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t mode)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	WREG32_SOC15(THM, 0, mmCG_FDO_CTRL2,
			REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL2),
				CG_FDO_CTRL2, TMIN, 0));
	WREG32_SOC15(THM, 0, mmCG_FDO_CTRL2,
			REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL2),
				CG_FDO_CTRL2, FDO_PWM_MODE, mode));

	वापस 0;
पूर्ण

अटल पूर्णांक vega20_get_current_rpm(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t *current_rpm)
अणु
	पूर्णांक ret = 0;

	PP_ASSERT_WITH_CODE((ret = smum_send_msg_to_smc(hwmgr,
				PPSMC_MSG_GetCurrentRpm,
				current_rpm)) == 0,
			"Attempt to get current RPM from SMC Failed!",
			वापस ret);

	वापस 0;
पूर्ण

पूर्णांक vega20_fan_ctrl_get_fan_speed_percent(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t *speed)
अणु
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
	PPTable_t *pp_table = &(data->smc_state_table.pp_table);
	uपूर्णांक32_t current_rpm, percent = 0;
	पूर्णांक ret = 0;

	ret = vega20_get_current_rpm(hwmgr, &current_rpm);
	अगर (ret)
		वापस ret;

	percent = current_rpm * 100 / pp_table->FanMaximumRpm;

	*speed = percent > 100 ? 100 : percent;

	वापस 0;
पूर्ण

पूर्णांक vega20_fan_ctrl_set_fan_speed_percent(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t speed)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t duty100;
	uपूर्णांक32_t duty;
	uपूर्णांक64_t पंचांगp64;

	अगर (speed > 100)
		speed = 100;

	अगर (PP_CAP(PHM_Platक्रमmCaps_MicrocodeFanControl))
		vega20_fan_ctrl_stop_smc_fan_control(hwmgr);

	duty100 = REG_GET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL1),
				    CG_FDO_CTRL1, FMAX_DUTY100);

	अगर (duty100 == 0)
		वापस -EINVAL;

	पंचांगp64 = (uपूर्णांक64_t)speed * duty100;
	करो_भाग(पंचांगp64, 100);
	duty = (uपूर्णांक32_t)पंचांगp64;

	WREG32_SOC15(THM, 0, mmCG_FDO_CTRL0,
		REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL0),
			CG_FDO_CTRL0, FDO_STATIC_DUTY, duty));

	वापस vega20_fan_ctrl_set_अटल_mode(hwmgr, FDO_PWM_MODE_STATIC);
पूर्ण

पूर्णांक vega20_fan_ctrl_get_fan_speed_info(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा phm_fan_speed_info *fan_speed_info)
अणु
	स_रखो(fan_speed_info, 0, माप(*fan_speed_info));
	fan_speed_info->supports_percent_पढ़ो = true;
	fan_speed_info->supports_percent_ग_लिखो = true;
	fan_speed_info->supports_rpm_पढ़ो = true;
	fan_speed_info->supports_rpm_ग_लिखो = true;

	वापस 0;
पूर्ण

पूर्णांक vega20_fan_ctrl_get_fan_speed_rpm(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t *speed)
अणु
	*speed = 0;

	वापस vega20_get_current_rpm(hwmgr, speed);
पूर्ण

पूर्णांक vega20_fan_ctrl_set_fan_speed_rpm(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t speed)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t tach_period, crystal_घड़ी_freq;
	पूर्णांक result = 0;

	अगर (!speed)
		वापस -EINVAL;

	अगर (PP_CAP(PHM_Platक्रमmCaps_MicrocodeFanControl)) अणु
		result = vega20_fan_ctrl_stop_smc_fan_control(hwmgr);
		अगर (result)
			वापस result;
	पूर्ण

	crystal_घड़ी_freq = amdgpu_asic_get_xclk((काष्ठा amdgpu_device *)hwmgr->adev);
	tach_period = 60 * crystal_घड़ी_freq * 10000 / (8 * speed);
	WREG32_SOC15(THM, 0, mmCG_TACH_CTRL,
			REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_TACH_CTRL),
				CG_TACH_CTRL, TARGET_PERIOD,
				tach_period));

	वापस vega20_fan_ctrl_set_अटल_mode(hwmgr, FDO_PWM_MODE_STATIC_RPM);
पूर्ण

/**
 * vega20_thermal_get_temperature - Reads the remote temperature from the SIslands thermal controller.
 *
 * @hwmgr: The address of the hardware manager.
 */
पूर्णांक vega20_thermal_get_temperature(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	पूर्णांक temp = 0;

	temp = RREG32_SOC15(THM, 0, mmCG_MULT_THERMAL_STATUS);

	temp = (temp & CG_MULT_THERMAL_STATUS__CTF_TEMP_MASK) >>
			CG_MULT_THERMAL_STATUS__CTF_TEMP__SHIFT;

	temp = temp & 0x1ff;

	temp *= PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
	वापस temp;
पूर्ण

/**
 * vega20_thermal_set_temperature_range - Set the requested temperature range क्रम high and low alert संकेतs
 *
 * @hwmgr: The address of the hardware manager.
 * @range: Temperature range to be programmed क्रम high and low alert संकेतs
 * Exception: PP_Result_BadInput अगर the input data is not valid.
 */
अटल पूर्णांक vega20_thermal_set_temperature_range(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा PP_TemperatureRange *range)
अणु
	काष्ठा phm_ppt_v3_inक्रमmation *pptable_inक्रमmation =
		(काष्ठा phm_ppt_v3_inक्रमmation *)hwmgr->pptable;
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	पूर्णांक low = VEGA20_THERMAL_MINIMUM_ALERT_TEMP;
	पूर्णांक high = VEGA20_THERMAL_MAXIMUM_ALERT_TEMP;
	uपूर्णांक32_t val;

	/* compare them in unit celsius degree */
	अगर (low < range->min / PP_TEMPERATURE_UNITS_PER_CENTIGRADES)
		low = range->min / PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
	अगर (high > pptable_inक्रमmation->us_software_shutकरोwn_temp)
		high = pptable_inक्रमmation->us_software_shutकरोwn_temp;

	अगर (low > high)
		वापस -EINVAL;

	val = RREG32_SOC15(THM, 0, mmTHM_THERMAL_INT_CTRL);

	val = CGS_REG_SET_FIELD(val, THM_THERMAL_INT_CTRL, MAX_IH_CREDIT, 5);
	val = CGS_REG_SET_FIELD(val, THM_THERMAL_INT_CTRL, THERM_IH_HW_ENA, 1);
	val = CGS_REG_SET_FIELD(val, THM_THERMAL_INT_CTRL, DIG_THERM_INTH, high);
	val = CGS_REG_SET_FIELD(val, THM_THERMAL_INT_CTRL, DIG_THERM_INTL, low);
	val = val & (~THM_THERMAL_INT_CTRL__THERM_TRIGGER_MASK_MASK);

	WREG32_SOC15(THM, 0, mmTHM_THERMAL_INT_CTRL, val);

	वापस 0;
पूर्ण

/**
 * vega20_thermal_enable_alert - Enable thermal alerts on the RV770 thermal controller.
 *
 * @hwmgr: The address of the hardware manager.
 */
अटल पूर्णांक vega20_thermal_enable_alert(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t val = 0;

	val |= (1 << THM_THERMAL_INT_ENA__THERM_INTH_CLR__SHIFT);
	val |= (1 << THM_THERMAL_INT_ENA__THERM_INTL_CLR__SHIFT);
	val |= (1 << THM_THERMAL_INT_ENA__THERM_TRIGGER_CLR__SHIFT);

	WREG32_SOC15(THM, 0, mmTHM_THERMAL_INT_ENA, val);

	वापस 0;
पूर्ण

/**
 * vega20_thermal_disable_alert - Disable thermal alerts on the RV770 thermal controller.
 * @hwmgr: The address of the hardware manager.
 */
पूर्णांक vega20_thermal_disable_alert(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	WREG32_SOC15(THM, 0, mmTHM_THERMAL_INT_ENA, 0);

	वापस 0;
पूर्ण

/**
 * vega20_thermal_stop_thermal_controller - Uninitialize the thermal controller.
 * Currently just disables alerts.
 * @hwmgr: The address of the hardware manager.
 */
पूर्णांक vega20_thermal_stop_thermal_controller(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = vega20_thermal_disable_alert(hwmgr);

	वापस result;
पूर्ण

/**
 * vega20_thermal_setup_fan_table - Set up the fan table to control the fan using the SMC.
 * @hwmgr:  the address of the घातerplay hardware manager.
 */
अटल पूर्णांक vega20_thermal_setup_fan_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक ret;
	काष्ठा vega20_hwmgr *data = (काष्ठा vega20_hwmgr *)(hwmgr->backend);
	PPTable_t *table = &(data->smc_state_table.pp_table);

	ret = smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetFanTemperatureTarget,
				(uपूर्णांक32_t)table->FanTargetTemperature,
				शून्य);

	वापस ret;
पूर्ण

पूर्णांक vega20_start_thermal_controller(काष्ठा pp_hwmgr *hwmgr,
				काष्ठा PP_TemperatureRange *range)
अणु
	पूर्णांक ret = 0;

	अगर (range == शून्य)
		वापस -EINVAL;

	ret = vega20_thermal_set_temperature_range(hwmgr, range);
	अगर (ret)
		वापस ret;

	ret = vega20_thermal_enable_alert(hwmgr);
	अगर (ret)
		वापस ret;

	ret = vega20_thermal_setup_fan_table(hwmgr);

	वापस ret;
पूर्ण;
