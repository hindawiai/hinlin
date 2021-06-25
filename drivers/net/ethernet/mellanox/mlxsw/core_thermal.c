<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2016-2018 Mellanox Technologies. All rights reserved
 * Copyright (c) 2016 Ivan Vecera <cera@cera.cz>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/thermal.h>
#समावेश <linux/err.h>
#समावेश <linux/sfp.h>

#समावेश "core.h"
#समावेश "core_env.h"

#घोषणा MLXSW_THERMAL_POLL_INT	1000	/* ms */
#घोषणा MLXSW_THERMAL_SLOW_POLL_INT	20000	/* ms */
#घोषणा MLXSW_THERMAL_ASIC_TEMP_NORM	75000	/* 75C */
#घोषणा MLXSW_THERMAL_ASIC_TEMP_HIGH	85000	/* 85C */
#घोषणा MLXSW_THERMAL_ASIC_TEMP_HOT	105000	/* 105C */
#घोषणा MLXSW_THERMAL_HYSTERESIS_TEMP	5000	/* 5C */
#घोषणा MLXSW_THERMAL_MODULE_TEMP_SHIFT	(MLXSW_THERMAL_HYSTERESIS_TEMP * 2)
#घोषणा MLXSW_THERMAL_ZONE_MAX_NAME	16
#घोषणा MLXSW_THERMAL_TEMP_SCORE_MAX	GENMASK(31, 0)
#घोषणा MLXSW_THERMAL_MAX_STATE	10
#घोषणा MLXSW_THERMAL_MAX_DUTY	255
/* Minimum and maximum fan allowed speed in percent: from 20% to 100%. Values
 * MLXSW_THERMAL_MAX_STATE + x, where x is between 2 and 10 are used क्रम
 * setting fan speed dynamic minimum. For example, अगर value is set to 14 (40%)
 * cooling levels vector will be set to 4, 4, 4, 4, 4, 5, 6, 7, 8, 9, 10 to
 * पूर्णांकroduce PWM speed in percent: 40, 40, 40, 40, 40, 50, 60. 70, 80, 90, 100.
 */
#घोषणा MLXSW_THERMAL_SPEED_MIN		(MLXSW_THERMAL_MAX_STATE + 2)
#घोषणा MLXSW_THERMAL_SPEED_MAX		(MLXSW_THERMAL_MAX_STATE * 2)
#घोषणा MLXSW_THERMAL_SPEED_MIN_LEVEL	2		/* 20% */

/* External cooling devices, allowed क्रम binding to mlxsw thermal zones. */
अटल अक्षर * स्थिर mlxsw_thermal_बाह्यal_allowed_cdev[] = अणु
	"mlxreg_fan",
पूर्ण;

क्रमागत mlxsw_thermal_trips अणु
	MLXSW_THERMAL_TEMP_TRIP_NORM,
	MLXSW_THERMAL_TEMP_TRIP_HIGH,
	MLXSW_THERMAL_TEMP_TRIP_HOT,
पूर्ण;

काष्ठा mlxsw_thermal_trip अणु
	पूर्णांक	type;
	पूर्णांक	temp;
	पूर्णांक	hyst;
	पूर्णांक	min_state;
	पूर्णांक	max_state;
पूर्ण;

अटल स्थिर काष्ठा mlxsw_thermal_trip शेष_thermal_trips[] = अणु
	अणु	/* In range - 0-40% PWM */
		.type		= THERMAL_TRIP_ACTIVE,
		.temp		= MLXSW_THERMAL_ASIC_TEMP_NORM,
		.hyst		= MLXSW_THERMAL_HYSTERESIS_TEMP,
		.min_state	= 0,
		.max_state	= (4 * MLXSW_THERMAL_MAX_STATE) / 10,
	पूर्ण,
	अणु
		/* In range - 40-100% PWM */
		.type		= THERMAL_TRIP_ACTIVE,
		.temp		= MLXSW_THERMAL_ASIC_TEMP_HIGH,
		.hyst		= MLXSW_THERMAL_HYSTERESIS_TEMP,
		.min_state	= (4 * MLXSW_THERMAL_MAX_STATE) / 10,
		.max_state	= MLXSW_THERMAL_MAX_STATE,
	पूर्ण,
	अणु	/* Warning */
		.type		= THERMAL_TRIP_HOT,
		.temp		= MLXSW_THERMAL_ASIC_TEMP_HOT,
		.min_state	= MLXSW_THERMAL_MAX_STATE,
		.max_state	= MLXSW_THERMAL_MAX_STATE,
	पूर्ण,
पूर्ण;

#घोषणा MLXSW_THERMAL_NUM_TRIPS	ARRAY_SIZE(शेष_thermal_trips)

/* Make sure all trips are writable */
#घोषणा MLXSW_THERMAL_TRIP_MASK	(BIT(MLXSW_THERMAL_NUM_TRIPS) - 1)

काष्ठा mlxsw_thermal;

काष्ठा mlxsw_thermal_module अणु
	काष्ठा mlxsw_thermal *parent;
	काष्ठा thermal_zone_device *tzdev;
	काष्ठा mlxsw_thermal_trip trips[MLXSW_THERMAL_NUM_TRIPS];
	पूर्णांक module; /* Module or gearbox number */
पूर्ण;

काष्ठा mlxsw_thermal अणु
	काष्ठा mlxsw_core *core;
	स्थिर काष्ठा mlxsw_bus_info *bus_info;
	काष्ठा thermal_zone_device *tzdev;
	पूर्णांक polling_delay;
	काष्ठा thermal_cooling_device *cdevs[MLXSW_MFCR_PWMS_MAX];
	u8 cooling_levels[MLXSW_THERMAL_MAX_STATE + 1];
	काष्ठा mlxsw_thermal_trip trips[MLXSW_THERMAL_NUM_TRIPS];
	काष्ठा mlxsw_thermal_module *tz_module_arr;
	u8 tz_module_num;
	काष्ठा mlxsw_thermal_module *tz_gearbox_arr;
	u8 tz_gearbox_num;
	अचिन्हित पूर्णांक tz_highest_score;
	काष्ठा thermal_zone_device *tz_highest_dev;
पूर्ण;

अटल अंतरभूत u8 mlxsw_state_to_duty(पूर्णांक state)
अणु
	वापस DIV_ROUND_CLOSEST(state * MLXSW_THERMAL_MAX_DUTY,
				 MLXSW_THERMAL_MAX_STATE);
पूर्ण

अटल अंतरभूत पूर्णांक mlxsw_duty_to_state(u8 duty)
अणु
	वापस DIV_ROUND_CLOSEST(duty * MLXSW_THERMAL_MAX_STATE,
				 MLXSW_THERMAL_MAX_DUTY);
पूर्ण

अटल पूर्णांक mlxsw_get_cooling_device_idx(काष्ठा mlxsw_thermal *thermal,
					काष्ठा thermal_cooling_device *cdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MLXSW_MFCR_PWMS_MAX; i++)
		अगर (thermal->cdevs[i] == cdev)
			वापस i;

	/* Allow mlxsw thermal zone binding to an बाह्यal cooling device */
	क्रम (i = 0; i < ARRAY_SIZE(mlxsw_thermal_बाह्यal_allowed_cdev); i++) अणु
		अगर (strnstr(cdev->type, mlxsw_thermal_बाह्यal_allowed_cdev[i],
			    म_माप(cdev->type)))
			वापस 0;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल व्योम
mlxsw_thermal_module_trips_reset(काष्ठा mlxsw_thermal_module *tz)
अणु
	tz->trips[MLXSW_THERMAL_TEMP_TRIP_NORM].temp = 0;
	tz->trips[MLXSW_THERMAL_TEMP_TRIP_HIGH].temp = 0;
	tz->trips[MLXSW_THERMAL_TEMP_TRIP_HOT].temp = 0;
पूर्ण

अटल पूर्णांक
mlxsw_thermal_module_trips_update(काष्ठा device *dev, काष्ठा mlxsw_core *core,
				  काष्ठा mlxsw_thermal_module *tz)
अणु
	पूर्णांक crit_temp, emerg_temp;
	पूर्णांक err;

	err = mlxsw_env_module_temp_thresholds_get(core, tz->module,
						   SFP_TEMP_HIGH_WARN,
						   &crit_temp);
	अगर (err)
		वापस err;

	err = mlxsw_env_module_temp_thresholds_get(core, tz->module,
						   SFP_TEMP_HIGH_ALARM,
						   &emerg_temp);
	अगर (err)
		वापस err;

	अगर (crit_temp > emerg_temp) अणु
		dev_warn(dev, "%s : Critical threshold %d is above emergency threshold %d\n",
			 tz->tzdev->type, crit_temp, emerg_temp);
		वापस 0;
	पूर्ण

	/* According to the प्रणाली thermal requirements, the thermal zones are
	 * defined with three trip poपूर्णांकs. The critical and emergency
	 * temperature thresholds, provided by QSFP module are set as "active"
	 * and "hot" trip poपूर्णांकs, "normal" trip poपूर्णांक is derived from "active"
	 * by subtracting द्विगुन hysteresis value.
	 */
	अगर (crit_temp >= MLXSW_THERMAL_MODULE_TEMP_SHIFT)
		tz->trips[MLXSW_THERMAL_TEMP_TRIP_NORM].temp = crit_temp -
					MLXSW_THERMAL_MODULE_TEMP_SHIFT;
	अन्यथा
		tz->trips[MLXSW_THERMAL_TEMP_TRIP_NORM].temp = crit_temp;
	tz->trips[MLXSW_THERMAL_TEMP_TRIP_HIGH].temp = crit_temp;
	tz->trips[MLXSW_THERMAL_TEMP_TRIP_HOT].temp = emerg_temp;

	वापस 0;
पूर्ण

अटल व्योम mlxsw_thermal_tz_score_update(काष्ठा mlxsw_thermal *thermal,
					  काष्ठा thermal_zone_device *tzdev,
					  काष्ठा mlxsw_thermal_trip *trips,
					  पूर्णांक temp)
अणु
	काष्ठा mlxsw_thermal_trip *trip = trips;
	अचिन्हित पूर्णांक score, delta, i, shअगरt = 1;

	/* Calculate thermal zone score, अगर temperature is above the hot
	 * threshold score is set to MLXSW_THERMAL_TEMP_SCORE_MAX.
	 */
	score = MLXSW_THERMAL_TEMP_SCORE_MAX;
	क्रम (i = MLXSW_THERMAL_TEMP_TRIP_NORM; i < MLXSW_THERMAL_NUM_TRIPS;
	     i++, trip++) अणु
		अगर (temp < trip->temp) अणु
			delta = DIV_ROUND_CLOSEST(temp, trip->temp - temp);
			score = delta * shअगरt;
			अवरोध;
		पूर्ण
		shअगरt *= 256;
	पूर्ण

	अगर (score > thermal->tz_highest_score) अणु
		thermal->tz_highest_score = score;
		thermal->tz_highest_dev = tzdev;
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_thermal_bind(काष्ठा thermal_zone_device *tzdev,
			      काष्ठा thermal_cooling_device *cdev)
अणु
	काष्ठा mlxsw_thermal *thermal = tzdev->devdata;
	काष्ठा device *dev = thermal->bus_info->dev;
	पूर्णांक i, err;

	/* If the cooling device is one of ours bind it */
	अगर (mlxsw_get_cooling_device_idx(thermal, cdev) < 0)
		वापस 0;

	क्रम (i = 0; i < MLXSW_THERMAL_NUM_TRIPS; i++) अणु
		स्थिर काष्ठा mlxsw_thermal_trip *trip = &thermal->trips[i];

		err = thermal_zone_bind_cooling_device(tzdev, i, cdev,
						       trip->max_state,
						       trip->min_state,
						       THERMAL_WEIGHT_DEFAULT);
		अगर (err < 0) अणु
			dev_err(dev, "Failed to bind cooling device to trip %d\n", i);
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_thermal_unbind(काष्ठा thermal_zone_device *tzdev,
				काष्ठा thermal_cooling_device *cdev)
अणु
	काष्ठा mlxsw_thermal *thermal = tzdev->devdata;
	काष्ठा device *dev = thermal->bus_info->dev;
	पूर्णांक i;
	पूर्णांक err;

	/* If the cooling device is our one unbind it */
	अगर (mlxsw_get_cooling_device_idx(thermal, cdev) < 0)
		वापस 0;

	क्रम (i = 0; i < MLXSW_THERMAL_NUM_TRIPS; i++) अणु
		err = thermal_zone_unbind_cooling_device(tzdev, i, cdev);
		अगर (err < 0) अणु
			dev_err(dev, "Failed to unbind cooling device\n");
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_thermal_get_temp(काष्ठा thermal_zone_device *tzdev,
				  पूर्णांक *p_temp)
अणु
	काष्ठा mlxsw_thermal *thermal = tzdev->devdata;
	काष्ठा device *dev = thermal->bus_info->dev;
	अक्षर mपंचांगp_pl[MLXSW_REG_MTMP_LEN];
	पूर्णांक temp;
	पूर्णांक err;

	mlxsw_reg_mपंचांगp_pack(mपंचांगp_pl, 0, false, false);

	err = mlxsw_reg_query(thermal->core, MLXSW_REG(mपंचांगp), mपंचांगp_pl);
	अगर (err) अणु
		dev_err(dev, "Failed to query temp sensor\n");
		वापस err;
	पूर्ण
	mlxsw_reg_mपंचांगp_unpack(mपंचांगp_pl, &temp, शून्य, शून्य);
	अगर (temp > 0)
		mlxsw_thermal_tz_score_update(thermal, tzdev, thermal->trips,
					      temp);

	*p_temp = temp;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_thermal_get_trip_type(काष्ठा thermal_zone_device *tzdev,
				       पूर्णांक trip,
				       क्रमागत thermal_trip_type *p_type)
अणु
	काष्ठा mlxsw_thermal *thermal = tzdev->devdata;

	अगर (trip < 0 || trip >= MLXSW_THERMAL_NUM_TRIPS)
		वापस -EINVAL;

	*p_type = thermal->trips[trip].type;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_thermal_get_trip_temp(काष्ठा thermal_zone_device *tzdev,
				       पूर्णांक trip, पूर्णांक *p_temp)
अणु
	काष्ठा mlxsw_thermal *thermal = tzdev->devdata;

	अगर (trip < 0 || trip >= MLXSW_THERMAL_NUM_TRIPS)
		वापस -EINVAL;

	*p_temp = thermal->trips[trip].temp;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_thermal_set_trip_temp(काष्ठा thermal_zone_device *tzdev,
				       पूर्णांक trip, पूर्णांक temp)
अणु
	काष्ठा mlxsw_thermal *thermal = tzdev->devdata;

	अगर (trip < 0 || trip >= MLXSW_THERMAL_NUM_TRIPS)
		वापस -EINVAL;

	thermal->trips[trip].temp = temp;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_thermal_get_trip_hyst(काष्ठा thermal_zone_device *tzdev,
				       पूर्णांक trip, पूर्णांक *p_hyst)
अणु
	काष्ठा mlxsw_thermal *thermal = tzdev->devdata;

	*p_hyst = thermal->trips[trip].hyst;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_thermal_set_trip_hyst(काष्ठा thermal_zone_device *tzdev,
				       पूर्णांक trip, पूर्णांक hyst)
अणु
	काष्ठा mlxsw_thermal *thermal = tzdev->devdata;

	thermal->trips[trip].hyst = hyst;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_thermal_trend_get(काष्ठा thermal_zone_device *tzdev,
				   पूर्णांक trip, क्रमागत thermal_trend *trend)
अणु
	काष्ठा mlxsw_thermal *thermal = tzdev->devdata;

	अगर (trip < 0 || trip >= MLXSW_THERMAL_NUM_TRIPS)
		वापस -EINVAL;

	अगर (tzdev == thermal->tz_highest_dev)
		वापस 1;

	*trend = THERMAL_TREND_STABLE;
	वापस 0;
पूर्ण

अटल काष्ठा thermal_zone_device_ops mlxsw_thermal_ops = अणु
	.bind = mlxsw_thermal_bind,
	.unbind = mlxsw_thermal_unbind,
	.get_temp = mlxsw_thermal_get_temp,
	.get_trip_type	= mlxsw_thermal_get_trip_type,
	.get_trip_temp	= mlxsw_thermal_get_trip_temp,
	.set_trip_temp	= mlxsw_thermal_set_trip_temp,
	.get_trip_hyst	= mlxsw_thermal_get_trip_hyst,
	.set_trip_hyst	= mlxsw_thermal_set_trip_hyst,
	.get_trend	= mlxsw_thermal_trend_get,
पूर्ण;

अटल पूर्णांक mlxsw_thermal_module_bind(काष्ठा thermal_zone_device *tzdev,
				     काष्ठा thermal_cooling_device *cdev)
अणु
	काष्ठा mlxsw_thermal_module *tz = tzdev->devdata;
	काष्ठा mlxsw_thermal *thermal = tz->parent;
	पूर्णांक i, j, err;

	/* If the cooling device is one of ours bind it */
	अगर (mlxsw_get_cooling_device_idx(thermal, cdev) < 0)
		वापस 0;

	क्रम (i = 0; i < MLXSW_THERMAL_NUM_TRIPS; i++) अणु
		स्थिर काष्ठा mlxsw_thermal_trip *trip = &tz->trips[i];

		err = thermal_zone_bind_cooling_device(tzdev, i, cdev,
						       trip->max_state,
						       trip->min_state,
						       THERMAL_WEIGHT_DEFAULT);
		अगर (err < 0)
			जाओ err_bind_cooling_device;
	पूर्ण
	वापस 0;

err_bind_cooling_device:
	क्रम (j = i - 1; j >= 0; j--)
		thermal_zone_unbind_cooling_device(tzdev, j, cdev);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_thermal_module_unbind(काष्ठा thermal_zone_device *tzdev,
				       काष्ठा thermal_cooling_device *cdev)
अणु
	काष्ठा mlxsw_thermal_module *tz = tzdev->devdata;
	काष्ठा mlxsw_thermal *thermal = tz->parent;
	पूर्णांक i;
	पूर्णांक err;

	/* If the cooling device is one of ours unbind it */
	अगर (mlxsw_get_cooling_device_idx(thermal, cdev) < 0)
		वापस 0;

	क्रम (i = 0; i < MLXSW_THERMAL_NUM_TRIPS; i++) अणु
		err = thermal_zone_unbind_cooling_device(tzdev, i, cdev);
		WARN_ON(err);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_thermal_module_temp_get(काष्ठा thermal_zone_device *tzdev,
					 पूर्णांक *p_temp)
अणु
	काष्ठा mlxsw_thermal_module *tz = tzdev->devdata;
	काष्ठा mlxsw_thermal *thermal = tz->parent;
	काष्ठा device *dev = thermal->bus_info->dev;
	अक्षर mपंचांगp_pl[MLXSW_REG_MTMP_LEN];
	पूर्णांक temp;
	पूर्णांक err;

	/* Read module temperature. */
	mlxsw_reg_mपंचांगp_pack(mपंचांगp_pl, MLXSW_REG_MTMP_MODULE_INDEX_MIN +
			    tz->module, false, false);
	err = mlxsw_reg_query(thermal->core, MLXSW_REG(mपंचांगp), mपंचांगp_pl);
	अगर (err) अणु
		/* Do not वापस error - in हाल of broken module's sensor
		 * it will cause error message flooding.
		 */
		temp = 0;
		*p_temp = (पूर्णांक) temp;
		वापस 0;
	पूर्ण
	mlxsw_reg_mपंचांगp_unpack(mपंचांगp_pl, &temp, शून्य, शून्य);
	*p_temp = temp;

	अगर (!temp)
		वापस 0;

	/* Update trip poपूर्णांकs. */
	err = mlxsw_thermal_module_trips_update(dev, thermal->core, tz);
	अगर (!err && temp > 0)
		mlxsw_thermal_tz_score_update(thermal, tzdev, tz->trips, temp);

	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_thermal_module_trip_type_get(काष्ठा thermal_zone_device *tzdev, पूर्णांक trip,
				   क्रमागत thermal_trip_type *p_type)
अणु
	काष्ठा mlxsw_thermal_module *tz = tzdev->devdata;

	अगर (trip < 0 || trip >= MLXSW_THERMAL_NUM_TRIPS)
		वापस -EINVAL;

	*p_type = tz->trips[trip].type;
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_thermal_module_trip_temp_get(काष्ठा thermal_zone_device *tzdev,
				   पूर्णांक trip, पूर्णांक *p_temp)
अणु
	काष्ठा mlxsw_thermal_module *tz = tzdev->devdata;

	अगर (trip < 0 || trip >= MLXSW_THERMAL_NUM_TRIPS)
		वापस -EINVAL;

	*p_temp = tz->trips[trip].temp;
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_thermal_module_trip_temp_set(काष्ठा thermal_zone_device *tzdev,
				   पूर्णांक trip, पूर्णांक temp)
अणु
	काष्ठा mlxsw_thermal_module *tz = tzdev->devdata;

	अगर (trip < 0 || trip >= MLXSW_THERMAL_NUM_TRIPS)
		वापस -EINVAL;

	tz->trips[trip].temp = temp;
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_thermal_module_trip_hyst_get(काष्ठा thermal_zone_device *tzdev, पूर्णांक trip,
				   पूर्णांक *p_hyst)
अणु
	काष्ठा mlxsw_thermal_module *tz = tzdev->devdata;

	*p_hyst = tz->trips[trip].hyst;
	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_thermal_module_trip_hyst_set(काष्ठा thermal_zone_device *tzdev, पूर्णांक trip,
				   पूर्णांक hyst)
अणु
	काष्ठा mlxsw_thermal_module *tz = tzdev->devdata;

	tz->trips[trip].hyst = hyst;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_thermal_module_trend_get(काष्ठा thermal_zone_device *tzdev,
					  पूर्णांक trip, क्रमागत thermal_trend *trend)
अणु
	काष्ठा mlxsw_thermal_module *tz = tzdev->devdata;
	काष्ठा mlxsw_thermal *thermal = tz->parent;

	अगर (trip < 0 || trip >= MLXSW_THERMAL_NUM_TRIPS)
		वापस -EINVAL;

	अगर (tzdev == thermal->tz_highest_dev)
		वापस 1;

	*trend = THERMAL_TREND_STABLE;
	वापस 0;
पूर्ण

अटल काष्ठा thermal_zone_device_ops mlxsw_thermal_module_ops = अणु
	.bind		= mlxsw_thermal_module_bind,
	.unbind		= mlxsw_thermal_module_unbind,
	.get_temp	= mlxsw_thermal_module_temp_get,
	.get_trip_type	= mlxsw_thermal_module_trip_type_get,
	.get_trip_temp	= mlxsw_thermal_module_trip_temp_get,
	.set_trip_temp	= mlxsw_thermal_module_trip_temp_set,
	.get_trip_hyst	= mlxsw_thermal_module_trip_hyst_get,
	.set_trip_hyst	= mlxsw_thermal_module_trip_hyst_set,
	.get_trend	= mlxsw_thermal_module_trend_get,
पूर्ण;

अटल पूर्णांक mlxsw_thermal_gearbox_temp_get(काष्ठा thermal_zone_device *tzdev,
					  पूर्णांक *p_temp)
अणु
	काष्ठा mlxsw_thermal_module *tz = tzdev->devdata;
	काष्ठा mlxsw_thermal *thermal = tz->parent;
	अक्षर mपंचांगp_pl[MLXSW_REG_MTMP_LEN];
	u16 index;
	पूर्णांक temp;
	पूर्णांक err;

	index = MLXSW_REG_MTMP_GBOX_INDEX_MIN + tz->module;
	mlxsw_reg_mपंचांगp_pack(mपंचांगp_pl, index, false, false);

	err = mlxsw_reg_query(thermal->core, MLXSW_REG(mपंचांगp), mपंचांगp_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_mपंचांगp_unpack(mपंचांगp_pl, &temp, शून्य, शून्य);
	अगर (temp > 0)
		mlxsw_thermal_tz_score_update(thermal, tzdev, tz->trips, temp);

	*p_temp = temp;
	वापस 0;
पूर्ण

अटल काष्ठा thermal_zone_device_ops mlxsw_thermal_gearbox_ops = अणु
	.bind		= mlxsw_thermal_module_bind,
	.unbind		= mlxsw_thermal_module_unbind,
	.get_temp	= mlxsw_thermal_gearbox_temp_get,
	.get_trip_type	= mlxsw_thermal_module_trip_type_get,
	.get_trip_temp	= mlxsw_thermal_module_trip_temp_get,
	.set_trip_temp	= mlxsw_thermal_module_trip_temp_set,
	.get_trip_hyst	= mlxsw_thermal_module_trip_hyst_get,
	.set_trip_hyst	= mlxsw_thermal_module_trip_hyst_set,
	.get_trend	= mlxsw_thermal_module_trend_get,
पूर्ण;

अटल पूर्णांक mlxsw_thermal_get_max_state(काष्ठा thermal_cooling_device *cdev,
				       अचिन्हित दीर्घ *p_state)
अणु
	*p_state = MLXSW_THERMAL_MAX_STATE;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_thermal_get_cur_state(काष्ठा thermal_cooling_device *cdev,
				       अचिन्हित दीर्घ *p_state)

अणु
	काष्ठा mlxsw_thermal *thermal = cdev->devdata;
	काष्ठा device *dev = thermal->bus_info->dev;
	अक्षर mfsc_pl[MLXSW_REG_MFSC_LEN];
	पूर्णांक err, idx;
	u8 duty;

	idx = mlxsw_get_cooling_device_idx(thermal, cdev);
	अगर (idx < 0)
		वापस idx;

	mlxsw_reg_mfsc_pack(mfsc_pl, idx, 0);
	err = mlxsw_reg_query(thermal->core, MLXSW_REG(mfsc), mfsc_pl);
	अगर (err) अणु
		dev_err(dev, "Failed to query PWM duty\n");
		वापस err;
	पूर्ण

	duty = mlxsw_reg_mfsc_pwm_duty_cycle_get(mfsc_pl);
	*p_state = mlxsw_duty_to_state(duty);
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_thermal_set_cur_state(काष्ठा thermal_cooling_device *cdev,
				       अचिन्हित दीर्घ state)

अणु
	काष्ठा mlxsw_thermal *thermal = cdev->devdata;
	काष्ठा device *dev = thermal->bus_info->dev;
	अक्षर mfsc_pl[MLXSW_REG_MFSC_LEN];
	अचिन्हित दीर्घ cur_state, i;
	पूर्णांक idx;
	u8 duty;
	पूर्णांक err;

	idx = mlxsw_get_cooling_device_idx(thermal, cdev);
	अगर (idx < 0)
		वापस idx;

	/* Verअगरy अगर this request is क्रम changing allowed fan dynamical
	 * minimum. If it is - update cooling levels accordingly and update
	 * state, अगर current state is below the newly requested minimum state.
	 * For example, अगर current state is 5, and minimal state is to be
	 * changed from 4 to 6, thermal->cooling_levels[0 to 5] will be changed
	 * all from 4 to 6. And state 5 (thermal->cooling_levels[4]) should be
	 * overwritten.
	 */
	अगर (state >= MLXSW_THERMAL_SPEED_MIN &&
	    state <= MLXSW_THERMAL_SPEED_MAX) अणु
		state -= MLXSW_THERMAL_MAX_STATE;
		क्रम (i = 0; i <= MLXSW_THERMAL_MAX_STATE; i++)
			thermal->cooling_levels[i] = max(state, i);

		mlxsw_reg_mfsc_pack(mfsc_pl, idx, 0);
		err = mlxsw_reg_query(thermal->core, MLXSW_REG(mfsc), mfsc_pl);
		अगर (err)
			वापस err;

		duty = mlxsw_reg_mfsc_pwm_duty_cycle_get(mfsc_pl);
		cur_state = mlxsw_duty_to_state(duty);

		/* If current fan state is lower than requested dynamical
		 * minimum, increase fan speed up to dynamical minimum.
		 */
		अगर (state < cur_state)
			वापस 0;

		state = cur_state;
	पूर्ण

	अगर (state > MLXSW_THERMAL_MAX_STATE)
		वापस -EINVAL;

	/* Normalize the state to the valid speed range. */
	state = thermal->cooling_levels[state];
	mlxsw_reg_mfsc_pack(mfsc_pl, idx, mlxsw_state_to_duty(state));
	err = mlxsw_reg_ग_लिखो(thermal->core, MLXSW_REG(mfsc), mfsc_pl);
	अगर (err) अणु
		dev_err(dev, "Failed to write PWM duty\n");
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_cooling_device_ops mlxsw_cooling_ops = अणु
	.get_max_state	= mlxsw_thermal_get_max_state,
	.get_cur_state	= mlxsw_thermal_get_cur_state,
	.set_cur_state	= mlxsw_thermal_set_cur_state,
पूर्ण;

अटल पूर्णांक
mlxsw_thermal_module_tz_init(काष्ठा mlxsw_thermal_module *module_tz)
अणु
	अक्षर tz_name[MLXSW_THERMAL_ZONE_MAX_NAME];
	पूर्णांक err;

	snम_लिखो(tz_name, माप(tz_name), "mlxsw-module%d",
		 module_tz->module + 1);
	module_tz->tzdev = thermal_zone_device_रेजिस्टर(tz_name,
							MLXSW_THERMAL_NUM_TRIPS,
							MLXSW_THERMAL_TRIP_MASK,
							module_tz,
							&mlxsw_thermal_module_ops,
							शून्य, 0,
							module_tz->parent->polling_delay);
	अगर (IS_ERR(module_tz->tzdev)) अणु
		err = PTR_ERR(module_tz->tzdev);
		वापस err;
	पूर्ण

	err = thermal_zone_device_enable(module_tz->tzdev);
	अगर (err)
		thermal_zone_device_unरेजिस्टर(module_tz->tzdev);

	वापस err;
पूर्ण

अटल व्योम mlxsw_thermal_module_tz_fini(काष्ठा thermal_zone_device *tzdev)
अणु
	thermal_zone_device_unरेजिस्टर(tzdev);
पूर्ण

अटल पूर्णांक
mlxsw_thermal_module_init(काष्ठा device *dev, काष्ठा mlxsw_core *core,
			  काष्ठा mlxsw_thermal *thermal, u8 module)
अणु
	काष्ठा mlxsw_thermal_module *module_tz;

	module_tz = &thermal->tz_module_arr[module];
	/* Skip अगर parent is alपढ़ोy set (हाल of port split). */
	अगर (module_tz->parent)
		वापस 0;
	module_tz->module = module;
	module_tz->parent = thermal;
	स_नकल(module_tz->trips, शेष_thermal_trips,
	       माप(thermal->trips));
	/* Initialize all trip poपूर्णांक. */
	mlxsw_thermal_module_trips_reset(module_tz);
	/* Update trip poपूर्णांक according to the module data. */
	वापस mlxsw_thermal_module_trips_update(dev, core, module_tz);
पूर्ण

अटल व्योम mlxsw_thermal_module_fini(काष्ठा mlxsw_thermal_module *module_tz)
अणु
	अगर (module_tz && module_tz->tzdev) अणु
		mlxsw_thermal_module_tz_fini(module_tz->tzdev);
		module_tz->tzdev = शून्य;
		module_tz->parent = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक
mlxsw_thermal_modules_init(काष्ठा device *dev, काष्ठा mlxsw_core *core,
			   काष्ठा mlxsw_thermal *thermal)
अणु
	काष्ठा mlxsw_thermal_module *module_tz;
	अक्षर mgpir_pl[MLXSW_REG_MGPIR_LEN];
	पूर्णांक i, err;

	अगर (!mlxsw_core_res_query_enabled(core))
		वापस 0;

	mlxsw_reg_mgpir_pack(mgpir_pl);
	err = mlxsw_reg_query(core, MLXSW_REG(mgpir), mgpir_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_mgpir_unpack(mgpir_pl, शून्य, शून्य, शून्य,
			       &thermal->tz_module_num);

	thermal->tz_module_arr = kसुस्मृति(thermal->tz_module_num,
					 माप(*thermal->tz_module_arr),
					 GFP_KERNEL);
	अगर (!thermal->tz_module_arr)
		वापस -ENOMEM;

	क्रम (i = 0; i < thermal->tz_module_num; i++) अणु
		err = mlxsw_thermal_module_init(dev, core, thermal, i);
		अगर (err)
			जाओ err_unreg_tz_module_arr;
	पूर्ण

	क्रम (i = 0; i < thermal->tz_module_num; i++) अणु
		module_tz = &thermal->tz_module_arr[i];
		अगर (!module_tz->parent)
			जारी;
		err = mlxsw_thermal_module_tz_init(module_tz);
		अगर (err)
			जाओ err_unreg_tz_module_arr;
	पूर्ण

	वापस 0;

err_unreg_tz_module_arr:
	क्रम (i = thermal->tz_module_num - 1; i >= 0; i--)
		mlxsw_thermal_module_fini(&thermal->tz_module_arr[i]);
	kमुक्त(thermal->tz_module_arr);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_thermal_modules_fini(काष्ठा mlxsw_thermal *thermal)
अणु
	पूर्णांक i;

	अगर (!mlxsw_core_res_query_enabled(thermal->core))
		वापस;

	क्रम (i = thermal->tz_module_num - 1; i >= 0; i--)
		mlxsw_thermal_module_fini(&thermal->tz_module_arr[i]);
	kमुक्त(thermal->tz_module_arr);
पूर्ण

अटल पूर्णांक
mlxsw_thermal_gearbox_tz_init(काष्ठा mlxsw_thermal_module *gearbox_tz)
अणु
	अक्षर tz_name[MLXSW_THERMAL_ZONE_MAX_NAME];
	पूर्णांक ret;

	snम_लिखो(tz_name, माप(tz_name), "mlxsw-gearbox%d",
		 gearbox_tz->module + 1);
	gearbox_tz->tzdev = thermal_zone_device_रेजिस्टर(tz_name,
						MLXSW_THERMAL_NUM_TRIPS,
						MLXSW_THERMAL_TRIP_MASK,
						gearbox_tz,
						&mlxsw_thermal_gearbox_ops,
						शून्य, 0,
						gearbox_tz->parent->polling_delay);
	अगर (IS_ERR(gearbox_tz->tzdev))
		वापस PTR_ERR(gearbox_tz->tzdev);

	ret = thermal_zone_device_enable(gearbox_tz->tzdev);
	अगर (ret)
		thermal_zone_device_unरेजिस्टर(gearbox_tz->tzdev);

	वापस ret;
पूर्ण

अटल व्योम
mlxsw_thermal_gearbox_tz_fini(काष्ठा mlxsw_thermal_module *gearbox_tz)
अणु
	thermal_zone_device_unरेजिस्टर(gearbox_tz->tzdev);
पूर्ण

अटल पूर्णांक
mlxsw_thermal_gearboxes_init(काष्ठा device *dev, काष्ठा mlxsw_core *core,
			     काष्ठा mlxsw_thermal *thermal)
अणु
	क्रमागत mlxsw_reg_mgpir_device_type device_type;
	काष्ठा mlxsw_thermal_module *gearbox_tz;
	अक्षर mgpir_pl[MLXSW_REG_MGPIR_LEN];
	u8 gbox_num;
	पूर्णांक i;
	पूर्णांक err;

	अगर (!mlxsw_core_res_query_enabled(core))
		वापस 0;

	mlxsw_reg_mgpir_pack(mgpir_pl);
	err = mlxsw_reg_query(core, MLXSW_REG(mgpir), mgpir_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_mgpir_unpack(mgpir_pl, &gbox_num, &device_type, शून्य,
			       शून्य);
	अगर (device_type != MLXSW_REG_MGPIR_DEVICE_TYPE_GEARBOX_DIE ||
	    !gbox_num)
		वापस 0;

	thermal->tz_gearbox_num = gbox_num;
	thermal->tz_gearbox_arr = kसुस्मृति(thermal->tz_gearbox_num,
					  माप(*thermal->tz_gearbox_arr),
					  GFP_KERNEL);
	अगर (!thermal->tz_gearbox_arr)
		वापस -ENOMEM;

	क्रम (i = 0; i < thermal->tz_gearbox_num; i++) अणु
		gearbox_tz = &thermal->tz_gearbox_arr[i];
		स_नकल(gearbox_tz->trips, शेष_thermal_trips,
		       माप(thermal->trips));
		gearbox_tz->module = i;
		gearbox_tz->parent = thermal;
		err = mlxsw_thermal_gearbox_tz_init(gearbox_tz);
		अगर (err)
			जाओ err_unreg_tz_gearbox;
	पूर्ण

	वापस 0;

err_unreg_tz_gearbox:
	क्रम (i--; i >= 0; i--)
		mlxsw_thermal_gearbox_tz_fini(&thermal->tz_gearbox_arr[i]);
	kमुक्त(thermal->tz_gearbox_arr);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_thermal_gearboxes_fini(काष्ठा mlxsw_thermal *thermal)
अणु
	पूर्णांक i;

	अगर (!mlxsw_core_res_query_enabled(thermal->core))
		वापस;

	क्रम (i = thermal->tz_gearbox_num - 1; i >= 0; i--)
		mlxsw_thermal_gearbox_tz_fini(&thermal->tz_gearbox_arr[i]);
	kमुक्त(thermal->tz_gearbox_arr);
पूर्ण

पूर्णांक mlxsw_thermal_init(काष्ठा mlxsw_core *core,
		       स्थिर काष्ठा mlxsw_bus_info *bus_info,
		       काष्ठा mlxsw_thermal **p_thermal)
अणु
	अक्षर mfcr_pl[MLXSW_REG_MFCR_LEN] = अणु 0 पूर्ण;
	क्रमागत mlxsw_reg_mfcr_pwm_frequency freq;
	काष्ठा device *dev = bus_info->dev;
	काष्ठा mlxsw_thermal *thermal;
	u16 tacho_active;
	u8 pwm_active;
	पूर्णांक err, i;

	thermal = devm_kzalloc(dev, माप(*thermal),
			       GFP_KERNEL);
	अगर (!thermal)
		वापस -ENOMEM;

	thermal->core = core;
	thermal->bus_info = bus_info;
	स_नकल(thermal->trips, शेष_thermal_trips, माप(thermal->trips));

	err = mlxsw_reg_query(thermal->core, MLXSW_REG(mfcr), mfcr_pl);
	अगर (err) अणु
		dev_err(dev, "Failed to probe PWMs\n");
		जाओ err_मुक्त_thermal;
	पूर्ण
	mlxsw_reg_mfcr_unpack(mfcr_pl, &freq, &tacho_active, &pwm_active);

	क्रम (i = 0; i < MLXSW_MFCR_TACHOS_MAX; i++) अणु
		अगर (tacho_active & BIT(i)) अणु
			अक्षर mfsl_pl[MLXSW_REG_MFSL_LEN];

			mlxsw_reg_mfsl_pack(mfsl_pl, i, 0, 0);

			/* We need to query the रेजिस्टर to preserve maximum */
			err = mlxsw_reg_query(thermal->core, MLXSW_REG(mfsl),
					      mfsl_pl);
			अगर (err)
				जाओ err_मुक्त_thermal;

			/* set the minimal RPMs to 0 */
			mlxsw_reg_mfsl_tach_min_set(mfsl_pl, 0);
			err = mlxsw_reg_ग_लिखो(thermal->core, MLXSW_REG(mfsl),
					      mfsl_pl);
			अगर (err)
				जाओ err_मुक्त_thermal;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < MLXSW_MFCR_PWMS_MAX; i++) अणु
		अगर (pwm_active & BIT(i)) अणु
			काष्ठा thermal_cooling_device *cdev;

			cdev = thermal_cooling_device_रेजिस्टर("mlxsw_fan",
							       thermal,
							       &mlxsw_cooling_ops);
			अगर (IS_ERR(cdev)) अणु
				err = PTR_ERR(cdev);
				dev_err(dev, "Failed to register cooling device\n");
				जाओ err_unreg_cdevs;
			पूर्ण
			thermal->cdevs[i] = cdev;
		पूर्ण
	पूर्ण

	/* Initialize cooling levels per PWM state. */
	क्रम (i = 0; i < MLXSW_THERMAL_MAX_STATE; i++)
		thermal->cooling_levels[i] = max(MLXSW_THERMAL_SPEED_MIN_LEVEL,
						 i);

	thermal->polling_delay = bus_info->low_frequency ?
				 MLXSW_THERMAL_SLOW_POLL_INT :
				 MLXSW_THERMAL_POLL_INT;

	thermal->tzdev = thermal_zone_device_रेजिस्टर("mlxsw",
						      MLXSW_THERMAL_NUM_TRIPS,
						      MLXSW_THERMAL_TRIP_MASK,
						      thermal,
						      &mlxsw_thermal_ops,
						      शून्य, 0,
						      thermal->polling_delay);
	अगर (IS_ERR(thermal->tzdev)) अणु
		err = PTR_ERR(thermal->tzdev);
		dev_err(dev, "Failed to register thermal zone\n");
		जाओ err_unreg_cdevs;
	पूर्ण

	err = mlxsw_thermal_modules_init(dev, core, thermal);
	अगर (err)
		जाओ err_unreg_tzdev;

	err = mlxsw_thermal_gearboxes_init(dev, core, thermal);
	अगर (err)
		जाओ err_unreg_modules_tzdev;

	err = thermal_zone_device_enable(thermal->tzdev);
	अगर (err)
		जाओ err_unreg_gearboxes;

	*p_thermal = thermal;
	वापस 0;

err_unreg_gearboxes:
	mlxsw_thermal_gearboxes_fini(thermal);
err_unreg_modules_tzdev:
	mlxsw_thermal_modules_fini(thermal);
err_unreg_tzdev:
	अगर (thermal->tzdev) अणु
		thermal_zone_device_unरेजिस्टर(thermal->tzdev);
		thermal->tzdev = शून्य;
	पूर्ण
err_unreg_cdevs:
	क्रम (i = 0; i < MLXSW_MFCR_PWMS_MAX; i++)
		अगर (thermal->cdevs[i])
			thermal_cooling_device_unरेजिस्टर(thermal->cdevs[i]);
err_मुक्त_thermal:
	devm_kमुक्त(dev, thermal);
	वापस err;
पूर्ण

व्योम mlxsw_thermal_fini(काष्ठा mlxsw_thermal *thermal)
अणु
	पूर्णांक i;

	mlxsw_thermal_gearboxes_fini(thermal);
	mlxsw_thermal_modules_fini(thermal);
	अगर (thermal->tzdev) अणु
		thermal_zone_device_unरेजिस्टर(thermal->tzdev);
		thermal->tzdev = शून्य;
	पूर्ण

	क्रम (i = 0; i < MLXSW_MFCR_PWMS_MAX; i++) अणु
		अगर (thermal->cdevs[i]) अणु
			thermal_cooling_device_unरेजिस्टर(thermal->cdevs[i]);
			thermal->cdevs[i] = शून्य;
		पूर्ण
	पूर्ण

	devm_kमुक्त(thermal->bus_info->dev, thermal);
पूर्ण
