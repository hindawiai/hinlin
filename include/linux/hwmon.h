<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
    hwmon.h - part of lm_sensors, Linux kernel modules क्रम hardware monitoring

    This file declares helper functions क्रम the sysfs class "hwmon",
    क्रम use by sensors drivers.

    Copyright (C) 2005 Mark M. Hoffman <mhoffman@lightlink.com>

*/

#अगर_अघोषित _HWMON_H_
#घोषणा _HWMON_H_

#समावेश <linux/bitops.h>

काष्ठा device;
काष्ठा attribute_group;

क्रमागत hwmon_sensor_types अणु
	hwmon_chip,
	hwmon_temp,
	hwmon_in,
	hwmon_curr,
	hwmon_घातer,
	hwmon_energy,
	hwmon_humidity,
	hwmon_fan,
	hwmon_pwm,
	hwmon_पूर्णांकrusion,
	hwmon_max,
पूर्ण;

क्रमागत hwmon_chip_attributes अणु
	hwmon_chip_temp_reset_history,
	hwmon_chip_in_reset_history,
	hwmon_chip_curr_reset_history,
	hwmon_chip_घातer_reset_history,
	hwmon_chip_रेजिस्टर_tz,
	hwmon_chip_update_पूर्णांकerval,
	hwmon_chip_alarms,
	hwmon_chip_samples,
	hwmon_chip_curr_samples,
	hwmon_chip_in_samples,
	hwmon_chip_घातer_samples,
	hwmon_chip_temp_samples,
पूर्ण;

#घोषणा HWMON_C_TEMP_RESET_HISTORY	BIT(hwmon_chip_temp_reset_history)
#घोषणा HWMON_C_IN_RESET_HISTORY	BIT(hwmon_chip_in_reset_history)
#घोषणा HWMON_C_CURR_RESET_HISTORY	BIT(hwmon_chip_curr_reset_history)
#घोषणा HWMON_C_POWER_RESET_HISTORY	BIT(hwmon_chip_घातer_reset_history)
#घोषणा HWMON_C_REGISTER_TZ		BIT(hwmon_chip_रेजिस्टर_tz)
#घोषणा HWMON_C_UPDATE_INTERVAL		BIT(hwmon_chip_update_पूर्णांकerval)
#घोषणा HWMON_C_ALARMS			BIT(hwmon_chip_alarms)
#घोषणा HWMON_C_SAMPLES			BIT(hwmon_chip_samples)
#घोषणा HWMON_C_CURR_SAMPLES		BIT(hwmon_chip_curr_samples)
#घोषणा HWMON_C_IN_SAMPLES		BIT(hwmon_chip_in_samples)
#घोषणा HWMON_C_POWER_SAMPLES		BIT(hwmon_chip_घातer_samples)
#घोषणा HWMON_C_TEMP_SAMPLES		BIT(hwmon_chip_temp_samples)

क्रमागत hwmon_temp_attributes अणु
	hwmon_temp_enable,
	hwmon_temp_input,
	hwmon_temp_type,
	hwmon_temp_lcrit,
	hwmon_temp_lcrit_hyst,
	hwmon_temp_min,
	hwmon_temp_min_hyst,
	hwmon_temp_max,
	hwmon_temp_max_hyst,
	hwmon_temp_crit,
	hwmon_temp_crit_hyst,
	hwmon_temp_emergency,
	hwmon_temp_emergency_hyst,
	hwmon_temp_alarm,
	hwmon_temp_lcrit_alarm,
	hwmon_temp_min_alarm,
	hwmon_temp_max_alarm,
	hwmon_temp_crit_alarm,
	hwmon_temp_emergency_alarm,
	hwmon_temp_fault,
	hwmon_temp_offset,
	hwmon_temp_label,
	hwmon_temp_lowest,
	hwmon_temp_highest,
	hwmon_temp_reset_history,
	hwmon_temp_rated_min,
	hwmon_temp_rated_max,
पूर्ण;

#घोषणा HWMON_T_ENABLE		BIT(hwmon_temp_enable)
#घोषणा HWMON_T_INPUT		BIT(hwmon_temp_input)
#घोषणा HWMON_T_TYPE		BIT(hwmon_temp_type)
#घोषणा HWMON_T_LCRIT		BIT(hwmon_temp_lcrit)
#घोषणा HWMON_T_LCRIT_HYST	BIT(hwmon_temp_lcrit_hyst)
#घोषणा HWMON_T_MIN		BIT(hwmon_temp_min)
#घोषणा HWMON_T_MIN_HYST	BIT(hwmon_temp_min_hyst)
#घोषणा HWMON_T_MAX		BIT(hwmon_temp_max)
#घोषणा HWMON_T_MAX_HYST	BIT(hwmon_temp_max_hyst)
#घोषणा HWMON_T_CRIT		BIT(hwmon_temp_crit)
#घोषणा HWMON_T_CRIT_HYST	BIT(hwmon_temp_crit_hyst)
#घोषणा HWMON_T_EMERGENCY	BIT(hwmon_temp_emergency)
#घोषणा HWMON_T_EMERGENCY_HYST	BIT(hwmon_temp_emergency_hyst)
#घोषणा HWMON_T_ALARM		BIT(hwmon_temp_alarm)
#घोषणा HWMON_T_MIN_ALARM	BIT(hwmon_temp_min_alarm)
#घोषणा HWMON_T_MAX_ALARM	BIT(hwmon_temp_max_alarm)
#घोषणा HWMON_T_CRIT_ALARM	BIT(hwmon_temp_crit_alarm)
#घोषणा HWMON_T_LCRIT_ALARM	BIT(hwmon_temp_lcrit_alarm)
#घोषणा HWMON_T_EMERGENCY_ALARM	BIT(hwmon_temp_emergency_alarm)
#घोषणा HWMON_T_FAULT		BIT(hwmon_temp_fault)
#घोषणा HWMON_T_OFFSET		BIT(hwmon_temp_offset)
#घोषणा HWMON_T_LABEL		BIT(hwmon_temp_label)
#घोषणा HWMON_T_LOWEST		BIT(hwmon_temp_lowest)
#घोषणा HWMON_T_HIGHEST		BIT(hwmon_temp_highest)
#घोषणा HWMON_T_RESET_HISTORY	BIT(hwmon_temp_reset_history)
#घोषणा HWMON_T_RATED_MIN	BIT(hwmon_temp_rated_min)
#घोषणा HWMON_T_RATED_MAX	BIT(hwmon_temp_rated_max)

क्रमागत hwmon_in_attributes अणु
	hwmon_in_enable,
	hwmon_in_input,
	hwmon_in_min,
	hwmon_in_max,
	hwmon_in_lcrit,
	hwmon_in_crit,
	hwmon_in_average,
	hwmon_in_lowest,
	hwmon_in_highest,
	hwmon_in_reset_history,
	hwmon_in_label,
	hwmon_in_alarm,
	hwmon_in_min_alarm,
	hwmon_in_max_alarm,
	hwmon_in_lcrit_alarm,
	hwmon_in_crit_alarm,
	hwmon_in_rated_min,
	hwmon_in_rated_max,
पूर्ण;

#घोषणा HWMON_I_ENABLE		BIT(hwmon_in_enable)
#घोषणा HWMON_I_INPUT		BIT(hwmon_in_input)
#घोषणा HWMON_I_MIN		BIT(hwmon_in_min)
#घोषणा HWMON_I_MAX		BIT(hwmon_in_max)
#घोषणा HWMON_I_LCRIT		BIT(hwmon_in_lcrit)
#घोषणा HWMON_I_CRIT		BIT(hwmon_in_crit)
#घोषणा HWMON_I_AVERAGE		BIT(hwmon_in_average)
#घोषणा HWMON_I_LOWEST		BIT(hwmon_in_lowest)
#घोषणा HWMON_I_HIGHEST		BIT(hwmon_in_highest)
#घोषणा HWMON_I_RESET_HISTORY	BIT(hwmon_in_reset_history)
#घोषणा HWMON_I_LABEL		BIT(hwmon_in_label)
#घोषणा HWMON_I_ALARM		BIT(hwmon_in_alarm)
#घोषणा HWMON_I_MIN_ALARM	BIT(hwmon_in_min_alarm)
#घोषणा HWMON_I_MAX_ALARM	BIT(hwmon_in_max_alarm)
#घोषणा HWMON_I_LCRIT_ALARM	BIT(hwmon_in_lcrit_alarm)
#घोषणा HWMON_I_CRIT_ALARM	BIT(hwmon_in_crit_alarm)
#घोषणा HWMON_I_RATED_MIN	BIT(hwmon_in_rated_min)
#घोषणा HWMON_I_RATED_MAX	BIT(hwmon_in_rated_max)

क्रमागत hwmon_curr_attributes अणु
	hwmon_curr_enable,
	hwmon_curr_input,
	hwmon_curr_min,
	hwmon_curr_max,
	hwmon_curr_lcrit,
	hwmon_curr_crit,
	hwmon_curr_average,
	hwmon_curr_lowest,
	hwmon_curr_highest,
	hwmon_curr_reset_history,
	hwmon_curr_label,
	hwmon_curr_alarm,
	hwmon_curr_min_alarm,
	hwmon_curr_max_alarm,
	hwmon_curr_lcrit_alarm,
	hwmon_curr_crit_alarm,
	hwmon_curr_rated_min,
	hwmon_curr_rated_max,
पूर्ण;

#घोषणा HWMON_C_ENABLE		BIT(hwmon_curr_enable)
#घोषणा HWMON_C_INPUT		BIT(hwmon_curr_input)
#घोषणा HWMON_C_MIN		BIT(hwmon_curr_min)
#घोषणा HWMON_C_MAX		BIT(hwmon_curr_max)
#घोषणा HWMON_C_LCRIT		BIT(hwmon_curr_lcrit)
#घोषणा HWMON_C_CRIT		BIT(hwmon_curr_crit)
#घोषणा HWMON_C_AVERAGE		BIT(hwmon_curr_average)
#घोषणा HWMON_C_LOWEST		BIT(hwmon_curr_lowest)
#घोषणा HWMON_C_HIGHEST		BIT(hwmon_curr_highest)
#घोषणा HWMON_C_RESET_HISTORY	BIT(hwmon_curr_reset_history)
#घोषणा HWMON_C_LABEL		BIT(hwmon_curr_label)
#घोषणा HWMON_C_ALARM		BIT(hwmon_curr_alarm)
#घोषणा HWMON_C_MIN_ALARM	BIT(hwmon_curr_min_alarm)
#घोषणा HWMON_C_MAX_ALARM	BIT(hwmon_curr_max_alarm)
#घोषणा HWMON_C_LCRIT_ALARM	BIT(hwmon_curr_lcrit_alarm)
#घोषणा HWMON_C_CRIT_ALARM	BIT(hwmon_curr_crit_alarm)
#घोषणा HWMON_C_RATED_MIN	BIT(hwmon_curr_rated_min)
#घोषणा HWMON_C_RATED_MAX	BIT(hwmon_curr_rated_max)

क्रमागत hwmon_घातer_attributes अणु
	hwmon_घातer_enable,
	hwmon_घातer_average,
	hwmon_घातer_average_पूर्णांकerval,
	hwmon_घातer_average_पूर्णांकerval_max,
	hwmon_घातer_average_पूर्णांकerval_min,
	hwmon_घातer_average_highest,
	hwmon_घातer_average_lowest,
	hwmon_घातer_average_max,
	hwmon_घातer_average_min,
	hwmon_घातer_input,
	hwmon_घातer_input_highest,
	hwmon_घातer_input_lowest,
	hwmon_घातer_reset_history,
	hwmon_घातer_accuracy,
	hwmon_घातer_cap,
	hwmon_घातer_cap_hyst,
	hwmon_घातer_cap_max,
	hwmon_घातer_cap_min,
	hwmon_घातer_min,
	hwmon_घातer_max,
	hwmon_घातer_crit,
	hwmon_घातer_lcrit,
	hwmon_घातer_label,
	hwmon_घातer_alarm,
	hwmon_घातer_cap_alarm,
	hwmon_घातer_min_alarm,
	hwmon_घातer_max_alarm,
	hwmon_घातer_lcrit_alarm,
	hwmon_घातer_crit_alarm,
	hwmon_घातer_rated_min,
	hwmon_घातer_rated_max,
पूर्ण;

#घोषणा HWMON_P_ENABLE			BIT(hwmon_घातer_enable)
#घोषणा HWMON_P_AVERAGE			BIT(hwmon_घातer_average)
#घोषणा HWMON_P_AVERAGE_INTERVAL	BIT(hwmon_घातer_average_पूर्णांकerval)
#घोषणा HWMON_P_AVERAGE_INTERVAL_MAX	BIT(hwmon_घातer_average_पूर्णांकerval_max)
#घोषणा HWMON_P_AVERAGE_INTERVAL_MIN	BIT(hwmon_घातer_average_पूर्णांकerval_min)
#घोषणा HWMON_P_AVERAGE_HIGHEST		BIT(hwmon_घातer_average_highest)
#घोषणा HWMON_P_AVERAGE_LOWEST		BIT(hwmon_घातer_average_lowest)
#घोषणा HWMON_P_AVERAGE_MAX		BIT(hwmon_घातer_average_max)
#घोषणा HWMON_P_AVERAGE_MIN		BIT(hwmon_घातer_average_min)
#घोषणा HWMON_P_INPUT			BIT(hwmon_घातer_input)
#घोषणा HWMON_P_INPUT_HIGHEST		BIT(hwmon_घातer_input_highest)
#घोषणा HWMON_P_INPUT_LOWEST		BIT(hwmon_घातer_input_lowest)
#घोषणा HWMON_P_RESET_HISTORY		BIT(hwmon_घातer_reset_history)
#घोषणा HWMON_P_ACCURACY		BIT(hwmon_घातer_accuracy)
#घोषणा HWMON_P_CAP			BIT(hwmon_घातer_cap)
#घोषणा HWMON_P_CAP_HYST		BIT(hwmon_घातer_cap_hyst)
#घोषणा HWMON_P_CAP_MAX			BIT(hwmon_घातer_cap_max)
#घोषणा HWMON_P_CAP_MIN			BIT(hwmon_घातer_cap_min)
#घोषणा HWMON_P_MIN			BIT(hwmon_घातer_min)
#घोषणा HWMON_P_MAX			BIT(hwmon_घातer_max)
#घोषणा HWMON_P_LCRIT			BIT(hwmon_घातer_lcrit)
#घोषणा HWMON_P_CRIT			BIT(hwmon_घातer_crit)
#घोषणा HWMON_P_LABEL			BIT(hwmon_घातer_label)
#घोषणा HWMON_P_ALARM			BIT(hwmon_घातer_alarm)
#घोषणा HWMON_P_CAP_ALARM		BIT(hwmon_घातer_cap_alarm)
#घोषणा HWMON_P_MIN_ALARM		BIT(hwmon_घातer_min_alarm)
#घोषणा HWMON_P_MAX_ALARM		BIT(hwmon_घातer_max_alarm)
#घोषणा HWMON_P_LCRIT_ALARM		BIT(hwmon_घातer_lcrit_alarm)
#घोषणा HWMON_P_CRIT_ALARM		BIT(hwmon_घातer_crit_alarm)
#घोषणा HWMON_P_RATED_MIN		BIT(hwmon_घातer_rated_min)
#घोषणा HWMON_P_RATED_MAX		BIT(hwmon_घातer_rated_max)

क्रमागत hwmon_energy_attributes अणु
	hwmon_energy_enable,
	hwmon_energy_input,
	hwmon_energy_label,
पूर्ण;

#घोषणा HWMON_E_ENABLE			BIT(hwmon_energy_enable)
#घोषणा HWMON_E_INPUT			BIT(hwmon_energy_input)
#घोषणा HWMON_E_LABEL			BIT(hwmon_energy_label)

क्रमागत hwmon_humidity_attributes अणु
	hwmon_humidity_enable,
	hwmon_humidity_input,
	hwmon_humidity_label,
	hwmon_humidity_min,
	hwmon_humidity_min_hyst,
	hwmon_humidity_max,
	hwmon_humidity_max_hyst,
	hwmon_humidity_alarm,
	hwmon_humidity_fault,
	hwmon_humidity_rated_min,
	hwmon_humidity_rated_max,
पूर्ण;

#घोषणा HWMON_H_ENABLE			BIT(hwmon_humidity_enable)
#घोषणा HWMON_H_INPUT			BIT(hwmon_humidity_input)
#घोषणा HWMON_H_LABEL			BIT(hwmon_humidity_label)
#घोषणा HWMON_H_MIN			BIT(hwmon_humidity_min)
#घोषणा HWMON_H_MIN_HYST		BIT(hwmon_humidity_min_hyst)
#घोषणा HWMON_H_MAX			BIT(hwmon_humidity_max)
#घोषणा HWMON_H_MAX_HYST		BIT(hwmon_humidity_max_hyst)
#घोषणा HWMON_H_ALARM			BIT(hwmon_humidity_alarm)
#घोषणा HWMON_H_FAULT			BIT(hwmon_humidity_fault)
#घोषणा HWMON_H_RATED_MIN		BIT(hwmon_humidity_rated_min)
#घोषणा HWMON_H_RATED_MAX		BIT(hwmon_humidity_rated_max)

क्रमागत hwmon_fan_attributes अणु
	hwmon_fan_enable,
	hwmon_fan_input,
	hwmon_fan_label,
	hwmon_fan_min,
	hwmon_fan_max,
	hwmon_fan_भाग,
	hwmon_fan_pulses,
	hwmon_fan_target,
	hwmon_fan_alarm,
	hwmon_fan_min_alarm,
	hwmon_fan_max_alarm,
	hwmon_fan_fault,
पूर्ण;

#घोषणा HWMON_F_ENABLE			BIT(hwmon_fan_enable)
#घोषणा HWMON_F_INPUT			BIT(hwmon_fan_input)
#घोषणा HWMON_F_LABEL			BIT(hwmon_fan_label)
#घोषणा HWMON_F_MIN			BIT(hwmon_fan_min)
#घोषणा HWMON_F_MAX			BIT(hwmon_fan_max)
#घोषणा HWMON_F_DIV			BIT(hwmon_fan_भाग)
#घोषणा HWMON_F_PULSES			BIT(hwmon_fan_pulses)
#घोषणा HWMON_F_TARGET			BIT(hwmon_fan_target)
#घोषणा HWMON_F_ALARM			BIT(hwmon_fan_alarm)
#घोषणा HWMON_F_MIN_ALARM		BIT(hwmon_fan_min_alarm)
#घोषणा HWMON_F_MAX_ALARM		BIT(hwmon_fan_max_alarm)
#घोषणा HWMON_F_FAULT			BIT(hwmon_fan_fault)

क्रमागत hwmon_pwm_attributes अणु
	hwmon_pwm_input,
	hwmon_pwm_enable,
	hwmon_pwm_mode,
	hwmon_pwm_freq,
पूर्ण;

#घोषणा HWMON_PWM_INPUT			BIT(hwmon_pwm_input)
#घोषणा HWMON_PWM_ENABLE		BIT(hwmon_pwm_enable)
#घोषणा HWMON_PWM_MODE			BIT(hwmon_pwm_mode)
#घोषणा HWMON_PWM_FREQ			BIT(hwmon_pwm_freq)

क्रमागत hwmon_पूर्णांकrusion_attributes अणु
	hwmon_पूर्णांकrusion_alarm,
	hwmon_पूर्णांकrusion_beep,
पूर्ण;
#घोषणा HWMON_INTRUSION_ALARM		BIT(hwmon_पूर्णांकrusion_alarm)
#घोषणा HWMON_INTRUSION_BEEP		BIT(hwmon_पूर्णांकrusion_beep)

/**
 * काष्ठा hwmon_ops - hwmon device operations
 * @is_visible: Callback to वापस attribute visibility. Mandatory.
 *		Parameters are:
 *		@स्थिर व्योम *drvdata:
 *			Poपूर्णांकer to driver-निजी data काष्ठाure passed
 *			as argument to hwmon_device_रेजिस्टर_with_info().
 *		@type:	Sensor type
 *		@attr:	Sensor attribute
 *		@channel:
 *			Channel number
 *		The function वापसs the file permissions.
 *		If the वापस value is 0, no attribute will be created.
 * @पढ़ो:	Read callback क्रम data attributes. Mandatory अगर पढ़ोable
 *		data attributes are present.
 *		Parameters are:
 *		@dev:	Poपूर्णांकer to hardware monitoring device
 *		@type:	Sensor type
 *		@attr:	Sensor attribute
 *		@channel:
 *			Channel number
 *		@val:	Poपूर्णांकer to वापसed value
 *		The function वापसs 0 on success or a negative error number.
 * @पढ़ो_string:
 *		Read callback क्रम string attributes. Mandatory अगर string
 *		attributes are present.
 *		Parameters are:
 *		@dev:	Poपूर्णांकer to hardware monitoring device
 *		@type:	Sensor type
 *		@attr:	Sensor attribute
 *		@channel:
 *			Channel number
 *		@str:	Poपूर्णांकer to वापसed string
 *		The function वापसs 0 on success or a negative error number.
 * @ग_लिखो:	Write callback क्रम data attributes. Mandatory अगर ग_लिखोable
 *		data attributes are present.
 *		Parameters are:
 *		@dev:	Poपूर्णांकer to hardware monitoring device
 *		@type:	Sensor type
 *		@attr:	Sensor attribute
 *		@channel:
 *			Channel number
 *		@val:	Value to ग_लिखो
 *		The function वापसs 0 on success or a negative error number.
 */
काष्ठा hwmon_ops अणु
	umode_t (*is_visible)(स्थिर व्योम *drvdata, क्रमागत hwmon_sensor_types type,
			      u32 attr, पूर्णांक channel);
	पूर्णांक (*पढ़ो)(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		    u32 attr, पूर्णांक channel, दीर्घ *val);
	पूर्णांक (*पढ़ो_string)(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		    u32 attr, पूर्णांक channel, स्थिर अक्षर **str);
	पूर्णांक (*ग_लिखो)(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		     u32 attr, पूर्णांक channel, दीर्घ val);
पूर्ण;

/**
 * Channel inक्रमmation
 * @type:	Channel type.
 * @config:	Poपूर्णांकer to शून्य-terminated list of channel parameters.
 *		Use क्रम per-channel attributes.
 */
काष्ठा hwmon_channel_info अणु
	क्रमागत hwmon_sensor_types type;
	स्थिर u32 *config;
पूर्ण;

#घोषणा HWMON_CHANNEL_INFO(stype, ...)	\
	(&(काष्ठा hwmon_channel_info) अणु	\
		.type = hwmon_##stype,	\
		.config = (u32 []) अणु	\
			__VA_ARGS__, 0	\
		पूर्ण			\
	पूर्ण)

/**
 * Chip configuration
 * @ops:	Poपूर्णांकer to hwmon operations.
 * @info:	Null-terminated list of channel inक्रमmation.
 */
काष्ठा hwmon_chip_info अणु
	स्थिर काष्ठा hwmon_ops *ops;
	स्थिर काष्ठा hwmon_channel_info **info;
पूर्ण;

/* hwmon_device_रेजिस्टर() is deprecated */
काष्ठा device *hwmon_device_रेजिस्टर(काष्ठा device *dev);

काष्ठा device *
hwmon_device_रेजिस्टर_with_groups(काष्ठा device *dev, स्थिर अक्षर *name,
				  व्योम *drvdata,
				  स्थिर काष्ठा attribute_group **groups);
काष्ठा device *
devm_hwmon_device_रेजिस्टर_with_groups(काष्ठा device *dev, स्थिर अक्षर *name,
				       व्योम *drvdata,
				       स्थिर काष्ठा attribute_group **groups);
काष्ठा device *
hwmon_device_रेजिस्टर_with_info(काष्ठा device *dev,
				स्थिर अक्षर *name, व्योम *drvdata,
				स्थिर काष्ठा hwmon_chip_info *info,
				स्थिर काष्ठा attribute_group **extra_groups);
काष्ठा device *
devm_hwmon_device_रेजिस्टर_with_info(काष्ठा device *dev,
				स्थिर अक्षर *name, व्योम *drvdata,
				स्थिर काष्ठा hwmon_chip_info *info,
				स्थिर काष्ठा attribute_group **extra_groups);

व्योम hwmon_device_unरेजिस्टर(काष्ठा device *dev);
व्योम devm_hwmon_device_unरेजिस्टर(काष्ठा device *dev);

पूर्णांक hwmon_notअगरy_event(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		       u32 attr, पूर्णांक channel);

/**
 * hwmon_is_bad_अक्षर - Is the अक्षर invalid in a hwmon name
 * @ch: the अक्षर to be considered
 *
 * hwmon_is_bad_अक्षर() can be used to determine अगर the given अक्षरacter
 * may not be used in a hwmon name.
 *
 * Returns true अगर the अक्षर is invalid, false otherwise.
 */
अटल अंतरभूत bool hwmon_is_bad_अक्षर(स्थिर अक्षर ch)
अणु
	चयन (ch) अणु
	हाल '-':
	हाल '*':
	हाल ' ':
	हाल '\t':
	हाल '\n':
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

#पूर्ण_अगर
