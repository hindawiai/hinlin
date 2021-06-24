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

#समावेश "vega10_thermal.h"
#समावेश "vega10_hwmgr.h"
#समावेश "vega10_smumgr.h"
#समावेश "vega10_ppsmc.h"
#समावेश "vega10_inc.h"
#समावेश "soc15_common.h"
#समावेश "pp_debug.h"

अटल पूर्णांक vega10_get_current_rpm(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t *current_rpm)
अणु
	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_GetCurrentRpm, current_rpm);
	वापस 0;
पूर्ण

पूर्णांक vega10_fan_ctrl_get_fan_speed_info(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा phm_fan_speed_info *fan_speed_info)
अणु

	अगर (hwmgr->thermal_controller.fanInfo.bNoFan)
		वापस 0;

	fan_speed_info->supports_percent_पढ़ो = true;
	fan_speed_info->supports_percent_ग_लिखो = true;
	fan_speed_info->min_percent = 0;
	fan_speed_info->max_percent = 100;

	अगर (PP_CAP(PHM_Platक्रमmCaps_FanSpeedInTableIsRPM) &&
		hwmgr->thermal_controller.fanInfo.
		ucTachometerPulsesPerRevolution) अणु
		fan_speed_info->supports_rpm_पढ़ो = true;
		fan_speed_info->supports_rpm_ग_लिखो = true;
		fan_speed_info->min_rpm =
				hwmgr->thermal_controller.fanInfo.ulMinRPM;
		fan_speed_info->max_rpm =
				hwmgr->thermal_controller.fanInfo.ulMaxRPM;
	पूर्ण अन्यथा अणु
		fan_speed_info->min_rpm = 0;
		fan_speed_info->max_rpm = 0;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vega10_fan_ctrl_get_fan_speed_percent(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t *speed)
अणु
	uपूर्णांक32_t current_rpm;
	uपूर्णांक32_t percent = 0;

	अगर (hwmgr->thermal_controller.fanInfo.bNoFan)
		वापस 0;

	अगर (vega10_get_current_rpm(hwmgr, &current_rpm))
		वापस -1;

	अगर (hwmgr->thermal_controller.
			advanceFanControlParameters.usMaxFanRPM != 0)
		percent = current_rpm * 100 /
			hwmgr->thermal_controller.
			advanceFanControlParameters.usMaxFanRPM;

	*speed = percent > 100 ? 100 : percent;

	वापस 0;
पूर्ण

पूर्णांक vega10_fan_ctrl_get_fan_speed_rpm(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t *speed)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	uपूर्णांक32_t tach_period;
	uपूर्णांक32_t crystal_घड़ी_freq;
	पूर्णांक result = 0;

	अगर (hwmgr->thermal_controller.fanInfo.bNoFan)
		वापस -1;

	अगर (data->smu_features[GNLD_FAN_CONTROL].supported) अणु
		result = vega10_get_current_rpm(hwmgr, speed);
	पूर्ण अन्यथा अणु
		tach_period =
			REG_GET_FIELD(RREG32_SOC15(THM, 0, mmCG_TACH_STATUS),
					  CG_TACH_STATUS,
					  TACH_PERIOD);

		अगर (tach_period == 0)
			वापस -EINVAL;

		crystal_घड़ी_freq = amdgpu_asic_get_xclk((काष्ठा amdgpu_device *)hwmgr->adev);

		*speed = 60 * crystal_घड़ी_freq * 10000 / tach_period;
	पूर्ण

	वापस result;
पूर्ण

/**
 * vega10_fan_ctrl_set_अटल_mode - Set Fan Speed Control to अटल mode,
 * so that the user can decide what speed to use.
 * @hwmgr:  the address of the घातerplay hardware manager.
 * @mode: the fan control mode, 0 शेष, 1 by percent, 5, by RPM
 * Exception: Should always succeed.
 */
पूर्णांक vega10_fan_ctrl_set_अटल_mode(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t mode)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	अगर (hwmgr->fan_ctrl_is_in_शेष_mode) अणु
		hwmgr->fan_ctrl_शेष_mode =
			REG_GET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL2),
				CG_FDO_CTRL2, FDO_PWM_MODE);
		hwmgr->पंचांगin =
			REG_GET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL2),
				CG_FDO_CTRL2, TMIN);
		hwmgr->fan_ctrl_is_in_शेष_mode = false;
	पूर्ण

	WREG32_SOC15(THM, 0, mmCG_FDO_CTRL2,
			REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL2),
				CG_FDO_CTRL2, TMIN, 0));
	WREG32_SOC15(THM, 0, mmCG_FDO_CTRL2,
			REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL2),
				CG_FDO_CTRL2, FDO_PWM_MODE, mode));

	वापस 0;
पूर्ण

/**
 * vega10_fan_ctrl_set_शेष_mode - Reset Fan Speed Control to शेष mode.
 * @hwmgr:  the address of the घातerplay hardware manager.
 * Exception: Should always succeed.
 */
पूर्णांक vega10_fan_ctrl_set_शेष_mode(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	अगर (!hwmgr->fan_ctrl_is_in_शेष_mode) अणु
		WREG32_SOC15(THM, 0, mmCG_FDO_CTRL2,
			REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL2),
				CG_FDO_CTRL2, FDO_PWM_MODE,
				hwmgr->fan_ctrl_शेष_mode));
		WREG32_SOC15(THM, 0, mmCG_FDO_CTRL2,
			REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL2),
				CG_FDO_CTRL2, TMIN,
				hwmgr->पंचांगin << CG_FDO_CTRL2__TMIN__SHIFT));
		hwmgr->fan_ctrl_is_in_शेष_mode = true;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vega10_enable_fan_control_feature - Enables the SMC Fan Control Feature.
 *
 * @hwmgr: the address of the घातerplay hardware manager.
 * Return:   0 on success. -1 otherwise.
 */
अटल पूर्णांक vega10_enable_fan_control_feature(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	अगर (data->smu_features[GNLD_FAN_CONTROL].supported) अणु
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(
				hwmgr, true,
				data->smu_features[GNLD_FAN_CONTROL].
				smu_feature_biपंचांगap),
				"Attempt to Enable FAN CONTROL feature Failed!",
				वापस -1);
		data->smu_features[GNLD_FAN_CONTROL].enabled = true;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vega10_disable_fan_control_feature(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	अगर (data->smu_features[GNLD_FAN_CONTROL].supported) अणु
		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(
				hwmgr, false,
				data->smu_features[GNLD_FAN_CONTROL].
				smu_feature_biपंचांगap),
				"Attempt to Enable FAN CONTROL feature Failed!",
				वापस -1);
		data->smu_features[GNLD_FAN_CONTROL].enabled = false;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक vega10_fan_ctrl_start_smc_fan_control(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (hwmgr->thermal_controller.fanInfo.bNoFan)
		वापस -1;

	PP_ASSERT_WITH_CODE(!vega10_enable_fan_control_feature(hwmgr),
			"Attempt to Enable SMC FAN CONTROL Feature Failed!",
			वापस -1);

	वापस 0;
पूर्ण


पूर्णांक vega10_fan_ctrl_stop_smc_fan_control(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	अगर (hwmgr->thermal_controller.fanInfo.bNoFan)
		वापस -1;

	अगर (data->smu_features[GNLD_FAN_CONTROL].supported) अणु
		PP_ASSERT_WITH_CODE(!vega10_disable_fan_control_feature(hwmgr),
				"Attempt to Disable SMC FAN CONTROL Feature Failed!",
				वापस -1);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * vega10_fan_ctrl_set_fan_speed_percent - Set Fan Speed in percent.
 * @hwmgr:  the address of the घातerplay hardware manager.
 * @speed: is the percentage value (0% - 100%) to be set.
 * Exception: Fails is the 100% setting appears to be 0.
 */
पूर्णांक vega10_fan_ctrl_set_fan_speed_percent(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t speed)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t duty100;
	uपूर्णांक32_t duty;
	uपूर्णांक64_t पंचांगp64;

	अगर (hwmgr->thermal_controller.fanInfo.bNoFan)
		वापस 0;

	अगर (speed > 100)
		speed = 100;

	अगर (PP_CAP(PHM_Platक्रमmCaps_MicrocodeFanControl))
		vega10_fan_ctrl_stop_smc_fan_control(hwmgr);

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

	वापस vega10_fan_ctrl_set_अटल_mode(hwmgr, FDO_PWM_MODE_STATIC);
पूर्ण

/**
 * vega10_fan_ctrl_reset_fan_speed_to_शेष - Reset Fan Speed to शेष.
 * @hwmgr:  the address of the घातerplay hardware manager.
 * Exception: Always succeeds.
 */
पूर्णांक vega10_fan_ctrl_reset_fan_speed_to_शेष(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (hwmgr->thermal_controller.fanInfo.bNoFan)
		वापस 0;

	अगर (PP_CAP(PHM_Platक्रमmCaps_MicrocodeFanControl))
		वापस vega10_fan_ctrl_start_smc_fan_control(hwmgr);
	अन्यथा
		वापस vega10_fan_ctrl_set_शेष_mode(hwmgr);
पूर्ण

/**
 * vega10_fan_ctrl_set_fan_speed_rpm - Set Fan Speed in RPM.
 * @hwmgr:  the address of the घातerplay hardware manager.
 * @speed: is the percentage value (min - max) to be set.
 * Exception: Fails is the speed not lie between min and max.
 */
पूर्णांक vega10_fan_ctrl_set_fan_speed_rpm(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t speed)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	uपूर्णांक32_t tach_period;
	uपूर्णांक32_t crystal_घड़ी_freq;
	पूर्णांक result = 0;

	अगर (hwmgr->thermal_controller.fanInfo.bNoFan ||
	    speed == 0 ||
	    (speed < hwmgr->thermal_controller.fanInfo.ulMinRPM) ||
	    (speed > hwmgr->thermal_controller.fanInfo.ulMaxRPM))
		वापस -1;

	अगर (PP_CAP(PHM_Platक्रमmCaps_MicrocodeFanControl))
		result = vega10_fan_ctrl_stop_smc_fan_control(hwmgr);

	अगर (!result) अणु
		crystal_घड़ी_freq = amdgpu_asic_get_xclk((काष्ठा amdgpu_device *)hwmgr->adev);
		tach_period = 60 * crystal_घड़ी_freq * 10000 / (8 * speed);
		WREG32_SOC15(THM, 0, mmCG_TACH_CTRL,
				REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_TACH_CTRL),
					CG_TACH_CTRL, TARGET_PERIOD,
					tach_period));
	पूर्ण
	वापस vega10_fan_ctrl_set_अटल_mode(hwmgr, FDO_PWM_MODE_STATIC_RPM);
पूर्ण

/**
 * vega10_thermal_get_temperature - Reads the remote temperature from the SIslands thermal controller.
 *
 * @hwmgr: The address of the hardware manager.
 */
पूर्णांक vega10_thermal_get_temperature(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	पूर्णांक temp;

	temp = RREG32_SOC15(THM, 0, mmCG_MULT_THERMAL_STATUS);

	temp = (temp & CG_MULT_THERMAL_STATUS__CTF_TEMP_MASK) >>
			CG_MULT_THERMAL_STATUS__CTF_TEMP__SHIFT;

	temp = temp & 0x1ff;

	temp *= PP_TEMPERATURE_UNITS_PER_CENTIGRADES;

	वापस temp;
पूर्ण

/**
 * vega10_thermal_set_temperature_range - Set the requested temperature range क्रम high and low alert संकेतs
 *
 * @hwmgr: The address of the hardware manager.
 * @range: Temperature range to be programmed क्रम
 *           high and low alert संकेतs
 * Exception: PP_Result_BadInput अगर the input data is not valid.
 */
अटल पूर्णांक vega10_thermal_set_temperature_range(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा PP_TemperatureRange *range)
अणु
	काष्ठा phm_ppt_v2_inक्रमmation *pp_table_info =
		(काष्ठा phm_ppt_v2_inक्रमmation *)(hwmgr->pptable);
	काष्ठा phm_tdp_table *tdp_table = pp_table_info->tdp_table;
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	पूर्णांक low = VEGA10_THERMAL_MINIMUM_ALERT_TEMP;
	पूर्णांक high = VEGA10_THERMAL_MAXIMUM_ALERT_TEMP;
	uपूर्णांक32_t val;

	/* compare them in unit celsius degree */
	अगर (low < range->min / PP_TEMPERATURE_UNITS_PER_CENTIGRADES)
		low = range->min / PP_TEMPERATURE_UNITS_PER_CENTIGRADES;

	/*
	 * As a common sense, usSoftwareShutकरोwnTemp should be bigger
	 * than ThotspotLimit. For any invalid usSoftwareShutकरोwnTemp,
	 * we will just use the max possible setting VEGA10_THERMAL_MAXIMUM_ALERT_TEMP
	 * to aव्योम false alarms.
	 */
	अगर ((tdp_table->usSoftwareShutकरोwnTemp >
	     range->hotspot_crit_max / PP_TEMPERATURE_UNITS_PER_CENTIGRADES)) अणु
		अगर (high > tdp_table->usSoftwareShutकरोwnTemp)
			high = tdp_table->usSoftwareShutकरोwnTemp;
	पूर्ण

	अगर (low > high)
		वापस -EINVAL;

	val = RREG32_SOC15(THM, 0, mmTHM_THERMAL_INT_CTRL);

	val = REG_SET_FIELD(val, THM_THERMAL_INT_CTRL, MAX_IH_CREDIT, 5);
	val = REG_SET_FIELD(val, THM_THERMAL_INT_CTRL, THERM_IH_HW_ENA, 1);
	val = REG_SET_FIELD(val, THM_THERMAL_INT_CTRL, DIG_THERM_INTH, high);
	val = REG_SET_FIELD(val, THM_THERMAL_INT_CTRL, DIG_THERM_INTL, low);
	val &= (~THM_THERMAL_INT_CTRL__THERM_TRIGGER_MASK_MASK) &
			(~THM_THERMAL_INT_CTRL__THERM_INTH_MASK_MASK) &
			(~THM_THERMAL_INT_CTRL__THERM_INTL_MASK_MASK);

	WREG32_SOC15(THM, 0, mmTHM_THERMAL_INT_CTRL, val);

	वापस 0;
पूर्ण

/**
 * vega10_thermal_initialize - Programs thermal controller one-समय setting रेजिस्टरs
 *
 * @hwmgr: The address of the hardware manager.
 */
अटल पूर्णांक vega10_thermal_initialize(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;

	अगर (hwmgr->thermal_controller.fanInfo.ucTachometerPulsesPerRevolution) अणु
		WREG32_SOC15(THM, 0, mmCG_TACH_CTRL,
			REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_TACH_CTRL),
				CG_TACH_CTRL, EDGE_PER_REV,
				hwmgr->thermal_controller.fanInfo.ucTachometerPulsesPerRevolution - 1));
	पूर्ण

	WREG32_SOC15(THM, 0, mmCG_FDO_CTRL2,
		REG_SET_FIELD(RREG32_SOC15(THM, 0, mmCG_FDO_CTRL2),
			CG_FDO_CTRL2, TACH_PWM_RESP_RATE, 0x28));

	वापस 0;
पूर्ण

/**
 * vega10_thermal_enable_alert - Enable thermal alerts on the RV770 thermal controller.
 *
 * @hwmgr: The address of the hardware manager.
 */
अटल पूर्णांक vega10_thermal_enable_alert(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	uपूर्णांक32_t val = 0;

	अगर (data->smu_features[GNLD_FW_CTF].supported) अणु
		अगर (data->smu_features[GNLD_FW_CTF].enabled)
			prपूर्णांकk("[Thermal_EnableAlert] FW CTF Already Enabled!\n");

		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
				true,
				data->smu_features[GNLD_FW_CTF].smu_feature_biपंचांगap),
				"Attempt to Enable FW CTF feature Failed!",
				वापस -1);
		data->smu_features[GNLD_FW_CTF].enabled = true;
	पूर्ण

	val |= (1 << THM_THERMAL_INT_ENA__THERM_INTH_CLR__SHIFT);
	val |= (1 << THM_THERMAL_INT_ENA__THERM_INTL_CLR__SHIFT);
	val |= (1 << THM_THERMAL_INT_ENA__THERM_TRIGGER_CLR__SHIFT);

	WREG32_SOC15(THM, 0, mmTHM_THERMAL_INT_ENA, val);

	वापस 0;
पूर्ण

/**
 * vega10_thermal_disable_alert - Disable thermal alerts on the RV770 thermal controller.
 * @hwmgr: The address of the hardware manager.
 */
पूर्णांक vega10_thermal_disable_alert(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा amdgpu_device *adev = hwmgr->adev;
	काष्ठा vega10_hwmgr *data = hwmgr->backend;

	अगर (data->smu_features[GNLD_FW_CTF].supported) अणु
		अगर (!data->smu_features[GNLD_FW_CTF].enabled)
			prपूर्णांकk("[Thermal_EnableAlert] FW CTF Already disabled!\n");


		PP_ASSERT_WITH_CODE(!vega10_enable_smc_features(hwmgr,
			false,
			data->smu_features[GNLD_FW_CTF].smu_feature_biपंचांगap),
			"Attempt to disable FW CTF feature Failed!",
			वापस -1);
		data->smu_features[GNLD_FW_CTF].enabled = false;
	पूर्ण

	WREG32_SOC15(THM, 0, mmTHM_THERMAL_INT_ENA, 0);

	वापस 0;
पूर्ण

/**
 * vega10_thermal_stop_thermal_controller - Uninitialize the thermal controller.
 * Currently just disables alerts.
 * @hwmgr: The address of the hardware manager.
 */
पूर्णांक vega10_thermal_stop_thermal_controller(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = vega10_thermal_disable_alert(hwmgr);

	अगर (!hwmgr->thermal_controller.fanInfo.bNoFan)
		vega10_fan_ctrl_set_शेष_mode(hwmgr);

	वापस result;
पूर्ण

/**
 * vega10_thermal_setup_fan_table - Set up the fan table to control the fan using the SMC.
 * @hwmgr:  the address of the घातerplay hardware manager.
 * Return:   result from set temperature range routine
 */
अटल पूर्णांक vega10_thermal_setup_fan_table(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक ret;
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	PPTable_t *table = &(data->smc_state_table.pp_table);

	अगर (!data->smu_features[GNLD_FAN_CONTROL].supported)
		वापस 0;

	table->FanMaximumRpm = (uपूर्णांक16_t)hwmgr->thermal_controller.
			advanceFanControlParameters.usMaxFanRPM;
	table->FanThrottlingRpm = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanRPMMaxLimit;
	table->FanAcousticLimitRpm = (uपूर्णांक16_t)(hwmgr->thermal_controller.
			advanceFanControlParameters.ulMinFanSCLKAcousticLimit);
	table->FanTargetTemperature = hwmgr->thermal_controller.
			advanceFanControlParameters.usTMax;

	smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetFanTemperatureTarget,
				(uपूर्णांक32_t)table->FanTargetTemperature,
				शून्य);

	table->FanPwmMin = hwmgr->thermal_controller.
			advanceFanControlParameters.usPWMMin * 255 / 100;
	table->FanTargetGfxclk = (uपूर्णांक16_t)(hwmgr->thermal_controller.
			advanceFanControlParameters.ulTargetGfxClk);
	table->FanGainEdge = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanGainEdge;
	table->FanGainHotspot = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanGainHotspot;
	table->FanGainLiquid = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanGainLiquid;
	table->FanGainVrVddc = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanGainVrVddc;
	table->FanGainVrMvdd = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanGainVrMvdd;
	table->FanGainPlx = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanGainPlx;
	table->FanGainHbm = hwmgr->thermal_controller.
			advanceFanControlParameters.usFanGainHbm;
	table->FanZeroRpmEnable = hwmgr->thermal_controller.
			advanceFanControlParameters.ucEnableZeroRPM;
	table->FanStopTemp = hwmgr->thermal_controller.
			advanceFanControlParameters.usZeroRPMStopTemperature;
	table->FanStartTemp = hwmgr->thermal_controller.
			advanceFanControlParameters.usZeroRPMStartTemperature;

	ret = smum_smc_table_manager(hwmgr,
				(uपूर्णांक8_t *)(&(data->smc_state_table.pp_table)),
				PPTABLE, false);
	अगर (ret)
		pr_info("Failed to update Fan Control Table in PPTable!");

	वापस ret;
पूर्ण

पूर्णांक vega10_enable_mgpu_fan_boost(काष्ठा pp_hwmgr *hwmgr)
अणु
	काष्ठा vega10_hwmgr *data = hwmgr->backend;
	PPTable_t *table = &(data->smc_state_table.pp_table);
	पूर्णांक ret;

	अगर (!data->smu_features[GNLD_FAN_CONTROL].supported)
		वापस 0;

	अगर (!hwmgr->thermal_controller.advanceFanControlParameters.
			usMGpuThrottlingRPMLimit)
		वापस 0;

	table->FanThrottlingRpm = hwmgr->thermal_controller.
			advanceFanControlParameters.usMGpuThrottlingRPMLimit;

	ret = smum_smc_table_manager(hwmgr,
				(uपूर्णांक8_t *)(&(data->smc_state_table.pp_table)),
				PPTABLE, false);
	अगर (ret) अणु
		pr_info("Failed to update fan control table in pptable!");
		वापस ret;
	पूर्ण

	ret = vega10_disable_fan_control_feature(hwmgr);
	अगर (ret) अणु
		pr_info("Attempt to disable SMC fan control feature failed!");
		वापस ret;
	पूर्ण

	ret = vega10_enable_fan_control_feature(hwmgr);
	अगर (ret)
		pr_info("Attempt to enable SMC fan control feature failed!");

	वापस ret;
पूर्ण

/**
 * vega10_thermal_start_smc_fan_control - Start the fan control on the SMC.
 * @hwmgr:  the address of the घातerplay hardware manager.
 * Return:   result from set temperature range routine
 */
अटल पूर्णांक vega10_thermal_start_smc_fan_control(काष्ठा pp_hwmgr *hwmgr)
अणु
/* If the fantable setup has failed we could have disabled
 * PHM_Platक्रमmCaps_MicrocodeFanControl even after
 * this function was included in the table.
 * Make sure that we still think controlling the fan is OK.
*/
	अगर (PP_CAP(PHM_Platक्रमmCaps_MicrocodeFanControl))
		vega10_fan_ctrl_start_smc_fan_control(hwmgr);

	वापस 0;
पूर्ण


पूर्णांक vega10_start_thermal_controller(काष्ठा pp_hwmgr *hwmgr,
				काष्ठा PP_TemperatureRange *range)
अणु
	पूर्णांक ret = 0;

	अगर (range == शून्य)
		वापस -EINVAL;

	vega10_thermal_initialize(hwmgr);
	ret = vega10_thermal_set_temperature_range(hwmgr, range);
	अगर (ret)
		वापस -EINVAL;

	vega10_thermal_enable_alert(hwmgr);
/* We should restrict perक्रमmance levels to low beक्रमe we halt the SMC.
 * On the other hand we are still in boot state when we करो this
 * so it would be poपूर्णांकless.
 * If this assumption changes we have to revisit this table.
 */
	ret = vega10_thermal_setup_fan_table(hwmgr);
	अगर (ret)
		वापस -EINVAL;

	vega10_thermal_start_smc_fan_control(hwmgr);

	वापस 0;
पूर्ण;




पूर्णांक vega10_thermal_ctrl_uninitialize_thermal_controller(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (!hwmgr->thermal_controller.fanInfo.bNoFan) अणु
		vega10_fan_ctrl_set_शेष_mode(hwmgr);
		vega10_fan_ctrl_stop_smc_fan_control(hwmgr);
	पूर्ण
	वापस 0;
पूर्ण
