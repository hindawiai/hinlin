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

#समावेश <यंत्र/भाग64.h>
#समावेश "smu7_thermal.h"
#समावेश "smu7_hwmgr.h"
#समावेश "smu7_common.h"

पूर्णांक smu7_fan_ctrl_get_fan_speed_info(काष्ठा pp_hwmgr *hwmgr,
		काष्ठा phm_fan_speed_info *fan_speed_info)
अणु
	अगर (hwmgr->thermal_controller.fanInfo.bNoFan)
		वापस -ENODEV;

	fan_speed_info->supports_percent_पढ़ो = true;
	fan_speed_info->supports_percent_ग_लिखो = true;
	fan_speed_info->min_percent = 0;
	fan_speed_info->max_percent = 100;

	अगर (PP_CAP(PHM_Platक्रमmCaps_FanSpeedInTableIsRPM) &&
	    hwmgr->thermal_controller.fanInfo.ucTachometerPulsesPerRevolution) अणु
		fan_speed_info->supports_rpm_पढ़ो = true;
		fan_speed_info->supports_rpm_ग_लिखो = true;
		fan_speed_info->min_rpm = hwmgr->thermal_controller.fanInfo.ulMinRPM;
		fan_speed_info->max_rpm = hwmgr->thermal_controller.fanInfo.ulMaxRPM;
	पूर्ण अन्यथा अणु
		fan_speed_info->min_rpm = 0;
		fan_speed_info->max_rpm = 0;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक smu7_fan_ctrl_get_fan_speed_percent(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t *speed)
अणु
	uपूर्णांक32_t duty100;
	uपूर्णांक32_t duty;
	uपूर्णांक64_t पंचांगp64;

	अगर (hwmgr->thermal_controller.fanInfo.bNoFan)
		वापस -ENODEV;

	duty100 = PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_FDO_CTRL1, FMAX_DUTY100);
	duty = PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_THERMAL_STATUS, FDO_PWM_DUTY);

	अगर (duty100 == 0)
		वापस -EINVAL;


	पंचांगp64 = (uपूर्णांक64_t)duty * 100;
	करो_भाग(पंचांगp64, duty100);
	*speed = (uपूर्णांक32_t)पंचांगp64;

	अगर (*speed > 100)
		*speed = 100;

	वापस 0;
पूर्ण

पूर्णांक smu7_fan_ctrl_get_fan_speed_rpm(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t *speed)
अणु
	uपूर्णांक32_t tach_period;
	uपूर्णांक32_t crystal_घड़ी_freq;

	अगर (hwmgr->thermal_controller.fanInfo.bNoFan ||
	    !hwmgr->thermal_controller.fanInfo.ucTachometerPulsesPerRevolution)
		वापस -ENODEV;

	tach_period = PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_TACH_STATUS, TACH_PERIOD);

	अगर (tach_period == 0)
		वापस -EINVAL;

	crystal_घड़ी_freq = amdgpu_asic_get_xclk((काष्ठा amdgpu_device *)hwmgr->adev);

	*speed = 60 * crystal_घड़ी_freq * 10000 / tach_period;

	वापस 0;
पूर्ण

/**
 * smu7_fan_ctrl_set_अटल_mode - Set Fan Speed Control to अटल mode, so that the user can decide what speed to use.
 * @hwmgr:  the address of the घातerplay hardware manager.
 * @mode:   the fan control mode, 0 शेष, 1 by percent, 5, by RPM
 * Exception: Should always succeed.
 */
पूर्णांक smu7_fan_ctrl_set_अटल_mode(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t mode)
अणु
	अगर (hwmgr->fan_ctrl_is_in_शेष_mode) अणु
		hwmgr->fan_ctrl_शेष_mode =
				PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
						CG_FDO_CTRL2, FDO_PWM_MODE);
		hwmgr->पंचांगin =
				PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
						CG_FDO_CTRL2, TMIN);
		hwmgr->fan_ctrl_is_in_शेष_mode = false;
	पूर्ण

	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_FDO_CTRL2, TMIN, 0);
	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_FDO_CTRL2, FDO_PWM_MODE, mode);

	वापस 0;
पूर्ण

/**
* Reset Fan Speed Control to शेष mode.
* @hwmgr:  the address of the घातerplay hardware manager.
* Exception: Should always succeed.
*/
पूर्णांक smu7_fan_ctrl_set_शेष_mode(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (!hwmgr->fan_ctrl_is_in_शेष_mode) अणु
		PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
				CG_FDO_CTRL2, FDO_PWM_MODE, hwmgr->fan_ctrl_शेष_mode);
		PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
				CG_FDO_CTRL2, TMIN, hwmgr->पंचांगin);
		hwmgr->fan_ctrl_is_in_शेष_mode = true;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक smu7_fan_ctrl_start_smc_fan_control(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;

	अगर (PP_CAP(PHM_Platक्रमmCaps_ODFuzzyFanControlSupport)) अणु
		result = smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_StartFanControl,
					FAN_CONTROL_FUZZY, शून्य);

		अगर (PP_CAP(PHM_Platक्रमmCaps_FanSpeedInTableIsRPM))
			hwmgr->hwmgr_func->set_max_fan_rpm_output(hwmgr,
					hwmgr->thermal_controller.
					advanceFanControlParameters.usMaxFanRPM);
		अन्यथा
			hwmgr->hwmgr_func->set_max_fan_pwm_output(hwmgr,
					hwmgr->thermal_controller.
					advanceFanControlParameters.usMaxFanPWM);

	पूर्ण अन्यथा अणु
		result = smum_send_msg_to_smc_with_parameter(hwmgr, PPSMC_StartFanControl,
					FAN_CONTROL_TABLE, शून्य);
	पूर्ण

	अगर (!result && hwmgr->thermal_controller.
			advanceFanControlParameters.ucTargetTemperature)
		result = smum_send_msg_to_smc_with_parameter(hwmgr,
				PPSMC_MSG_SetFanTemperatureTarget,
				hwmgr->thermal_controller.
				advanceFanControlParameters.ucTargetTemperature,
				शून्य);

	अगर (!result &&
	    (hwmgr->chip_id == CHIP_POLARIS10 ||
	    hwmgr->chip_id == CHIP_POLARIS11 ||
	    hwmgr->chip_id == CHIP_POLARIS12) &&
	    hwmgr->thermal_controller.advanceFanControlParameters.ucEnableZeroRPM &&
	    !PP_CAP(PHM_Platक्रमmCaps_customThermalManagement))
		result = smum_send_msg_to_smc(hwmgr,
				PPSMC_MSG_EnableZeroRpm,
				शून्य);

	hwmgr->fan_ctrl_enabled = true;

	वापस result;
पूर्ण


पूर्णांक smu7_fan_ctrl_stop_smc_fan_control(काष्ठा pp_hwmgr *hwmgr)
अणु
	hwmgr->fan_ctrl_enabled = false;
	वापस smum_send_msg_to_smc(hwmgr, PPSMC_StopFanControl, शून्य);
पूर्ण

/**
 * smu7_fan_ctrl_set_fan_speed_percent - Set Fan Speed in percent.
 * @hwmgr: the address of the घातerplay hardware manager.
 * @speed: is the percentage value (0% - 100%) to be set.
 * Exception: Fails is the 100% setting appears to be 0.
 */
पूर्णांक smu7_fan_ctrl_set_fan_speed_percent(काष्ठा pp_hwmgr *hwmgr,
		uपूर्णांक32_t speed)
अणु
	uपूर्णांक32_t duty100;
	uपूर्णांक32_t duty;
	uपूर्णांक64_t पंचांगp64;

	अगर (hwmgr->thermal_controller.fanInfo.bNoFan)
		वापस 0;

	अगर (speed > 100)
		speed = 100;

	अगर (PP_CAP(PHM_Platक्रमmCaps_MicrocodeFanControl))
		smu7_fan_ctrl_stop_smc_fan_control(hwmgr);

	duty100 = PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_FDO_CTRL1, FMAX_DUTY100);

	अगर (duty100 == 0)
		वापस -EINVAL;

	पंचांगp64 = (uपूर्णांक64_t)speed * duty100;
	करो_भाग(पंचांगp64, 100);
	duty = (uपूर्णांक32_t)पंचांगp64;

	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_FDO_CTRL0, FDO_STATIC_DUTY, duty);

	वापस smu7_fan_ctrl_set_अटल_mode(hwmgr, FDO_PWM_MODE_STATIC);
पूर्ण

/**
* smu7_fan_ctrl_reset_fan_speed_to_शेष - Reset Fan Speed to शेष.
* @hwmgr:  the address of the घातerplay hardware manager.
* Exception: Always succeeds.
*/
पूर्णांक smu7_fan_ctrl_reset_fan_speed_to_शेष(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result;

	अगर (hwmgr->thermal_controller.fanInfo.bNoFan)
		वापस 0;

	अगर (PP_CAP(PHM_Platक्रमmCaps_MicrocodeFanControl)) अणु
		result = smu7_fan_ctrl_set_अटल_mode(hwmgr, FDO_PWM_MODE_STATIC);
		अगर (!result)
			result = smu7_fan_ctrl_start_smc_fan_control(hwmgr);
	पूर्ण अन्यथा
		result = smu7_fan_ctrl_set_शेष_mode(hwmgr);

	वापस result;
पूर्ण

/**
 * smu7_fan_ctrl_set_fan_speed_rpm - Set Fan Speed in RPM.
 * @hwmgr: the address of the घातerplay hardware manager.
 * @speed: is the percentage value (min - max) to be set.
 * Exception: Fails is the speed not lie between min and max.
 */
पूर्णांक smu7_fan_ctrl_set_fan_speed_rpm(काष्ठा pp_hwmgr *hwmgr, uपूर्णांक32_t speed)
अणु
	uपूर्णांक32_t tach_period;
	uपूर्णांक32_t crystal_घड़ी_freq;

	अगर (hwmgr->thermal_controller.fanInfo.bNoFan ||
			(hwmgr->thermal_controller.fanInfo.
			ucTachometerPulsesPerRevolution == 0) ||
			speed == 0 ||
			(speed < hwmgr->thermal_controller.fanInfo.ulMinRPM) ||
			(speed > hwmgr->thermal_controller.fanInfo.ulMaxRPM))
		वापस 0;

	अगर (PP_CAP(PHM_Platक्रमmCaps_MicrocodeFanControl))
		smu7_fan_ctrl_stop_smc_fan_control(hwmgr);

	crystal_घड़ी_freq = amdgpu_asic_get_xclk((काष्ठा amdgpu_device *)hwmgr->adev);

	tach_period = 60 * crystal_घड़ी_freq * 10000 / (8 * speed);

	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
				CG_TACH_CTRL, TARGET_PERIOD, tach_period);

	वापस smu7_fan_ctrl_set_अटल_mode(hwmgr, FDO_PWM_MODE_STATIC_RPM);
पूर्ण

/**
 * smu7_thermal_get_temperature - Reads the remote temperature from the SIslands thermal controller.
 *
 * @hwmgr: The address of the hardware manager.
 */
पूर्णांक smu7_thermal_get_temperature(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक temp;

	temp = PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_MULT_THERMAL_STATUS, CTF_TEMP);

	/* Bit 9 means the पढ़ोing is lower than the lowest usable value. */
	अगर (temp & 0x200)
		temp = SMU7_THERMAL_MAXIMUM_TEMP_READING;
	अन्यथा
		temp = temp & 0x1ff;

	temp *= PP_TEMPERATURE_UNITS_PER_CENTIGRADES;

	वापस temp;
पूर्ण

/**
 * smu7_thermal_set_temperature_range - Set the requested temperature range क्रम high and low alert संकेतs
 *
 * @hwmgr: The address of the hardware manager.
 * @low_temp: Temperature to be programmed क्रम high alert संकेतs
 * @high_temp: Temperature to be programmed क्रम low alert संकेतs
 * Exception: PP_Result_BadInput अगर the input data is not valid.
 */
अटल पूर्णांक smu7_thermal_set_temperature_range(काष्ठा pp_hwmgr *hwmgr,
		पूर्णांक low_temp, पूर्णांक high_temp)
अणु
	पूर्णांक low = SMU7_THERMAL_MINIMUM_ALERT_TEMP *
			PP_TEMPERATURE_UNITS_PER_CENTIGRADES;
	पूर्णांक high = SMU7_THERMAL_MAXIMUM_ALERT_TEMP *
			PP_TEMPERATURE_UNITS_PER_CENTIGRADES;

	अगर (low < low_temp)
		low = low_temp;
	अगर (high > high_temp)
		high = high_temp;

	अगर (low > high)
		वापस -EINVAL;

	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_THERMAL_INT, DIG_THERM_INTH,
			(high / PP_TEMPERATURE_UNITS_PER_CENTIGRADES));
	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_THERMAL_INT, DIG_THERM_INTL,
			(low / PP_TEMPERATURE_UNITS_PER_CENTIGRADES));
	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_THERMAL_CTRL, DIG_THERM_DPM,
			(high / PP_TEMPERATURE_UNITS_PER_CENTIGRADES));

	वापस 0;
पूर्ण

/**
 * smu7_thermal_initialize - Programs thermal controller one-समय setting रेजिस्टरs
 *
 * @hwmgr: The address of the hardware manager.
 */
अटल पूर्णांक smu7_thermal_initialize(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (hwmgr->thermal_controller.fanInfo.ucTachometerPulsesPerRevolution)
		PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
				CG_TACH_CTRL, EDGE_PER_REV,
				hwmgr->thermal_controller.fanInfo.
				ucTachometerPulsesPerRevolution - 1);

	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_FDO_CTRL2, TACH_PWM_RESP_RATE, 0x28);

	वापस 0;
पूर्ण

/**
 * smu7_thermal_enable_alert - Enable thermal alerts on the RV770 thermal controller.
 *
 * @hwmgr: The address of the hardware manager.
 */
अटल व्योम smu7_thermal_enable_alert(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t alert;

	alert = PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_THERMAL_INT, THERM_INT_MASK);
	alert &= ~(SMU7_THERMAL_HIGH_ALERT_MASK | SMU7_THERMAL_LOW_ALERT_MASK);
	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_THERMAL_INT, THERM_INT_MASK, alert);

	/* send message to SMU to enable पूर्णांकernal thermal पूर्णांकerrupts */
	smum_send_msg_to_smc(hwmgr, PPSMC_MSG_Thermal_Cntl_Enable, शून्य);
पूर्ण

/**
 * smu7_thermal_disable_alert - Disable thermal alerts on the RV770 thermal controller.
 * @hwmgr: The address of the hardware manager.
 */
पूर्णांक smu7_thermal_disable_alert(काष्ठा pp_hwmgr *hwmgr)
अणु
	uपूर्णांक32_t alert;

	alert = PHM_READ_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_THERMAL_INT, THERM_INT_MASK);
	alert |= (SMU7_THERMAL_HIGH_ALERT_MASK | SMU7_THERMAL_LOW_ALERT_MASK);
	PHM_WRITE_VFPF_INसूचीECT_FIELD(hwmgr->device, CGS_IND_REG__SMC,
			CG_THERMAL_INT, THERM_INT_MASK, alert);

	/* send message to SMU to disable पूर्णांकernal thermal पूर्णांकerrupts */
	वापस smum_send_msg_to_smc(hwmgr, PPSMC_MSG_Thermal_Cntl_Disable, शून्य);
पूर्ण

/**
 * smu7_thermal_stop_thermal_controller - Uninitialize the thermal controller.
 * Currently just disables alerts.
 * @hwmgr: The address of the hardware manager.
 */
पूर्णांक smu7_thermal_stop_thermal_controller(काष्ठा pp_hwmgr *hwmgr)
अणु
	पूर्णांक result = smu7_thermal_disable_alert(hwmgr);

	अगर (!hwmgr->thermal_controller.fanInfo.bNoFan)
		smu7_fan_ctrl_set_शेष_mode(hwmgr);

	वापस result;
पूर्ण

/**
 * smu7_thermal_start_smc_fan_control - Start the fan control on the SMC.
 * @hwmgr:  the address of the घातerplay hardware manager.
 * Return:   result from set temperature range routine
 */
अटल पूर्णांक smu7_thermal_start_smc_fan_control(काष्ठा pp_hwmgr *hwmgr)
अणु
/* If the fantable setup has failed we could have disabled
 * PHM_Platक्रमmCaps_MicrocodeFanControl even after
 * this function was included in the table.
 * Make sure that we still think controlling the fan is OK.
*/
	अगर (PP_CAP(PHM_Platक्रमmCaps_MicrocodeFanControl)) अणु
		smu7_fan_ctrl_start_smc_fan_control(hwmgr);
		smu7_fan_ctrl_set_अटल_mode(hwmgr, FDO_PWM_MODE_STATIC);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक smu7_start_thermal_controller(काष्ठा pp_hwmgr *hwmgr,
				काष्ठा PP_TemperatureRange *range)
अणु
	पूर्णांक ret = 0;

	अगर (range == शून्य)
		वापस -EINVAL;

	smu7_thermal_initialize(hwmgr);
	ret = smu7_thermal_set_temperature_range(hwmgr, range->min, range->max);
	अगर (ret)
		वापस -EINVAL;
	smu7_thermal_enable_alert(hwmgr);
	ret = smum_thermal_avfs_enable(hwmgr);
	अगर (ret)
		वापस -EINVAL;

/* We should restrict perक्रमmance levels to low beक्रमe we halt the SMC.
 * On the other hand we are still in boot state when we करो this
 * so it would be poपूर्णांकless.
 * If this assumption changes we have to revisit this table.
 */
	smum_thermal_setup_fan_table(hwmgr);
	smu7_thermal_start_smc_fan_control(hwmgr);
	वापस 0;
पूर्ण



पूर्णांक smu7_thermal_ctrl_uninitialize_thermal_controller(काष्ठा pp_hwmgr *hwmgr)
अणु
	अगर (!hwmgr->thermal_controller.fanInfo.bNoFan)
		smu7_fan_ctrl_set_शेष_mode(hwmgr);
	वापस 0;
पूर्ण

