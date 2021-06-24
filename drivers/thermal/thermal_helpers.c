<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  thermal_helpers.c - helper functions to handle thermal devices
 *
 *  Copyright (C) 2016 Eduarकरो Valentin <edubezval@gmail.com>
 *
 *  Highly based on original thermal_core.c
 *  Copyright (C) 2008 Intel Corp
 *  Copyright (C) 2008 Zhang Rui <rui.zhang@पूर्णांकel.com>
 *  Copyright (C) 2008 Sujith Thomas <sujith.thomas@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/sysfs.h>

#समावेश <trace/events/thermal.h>

#समावेश "thermal_core.h"

पूर्णांक get_tz_trend(काष्ठा thermal_zone_device *tz, पूर्णांक trip)
अणु
	क्रमागत thermal_trend trend;

	अगर (tz->emul_temperature || !tz->ops->get_trend ||
	    tz->ops->get_trend(tz, trip, &trend)) अणु
		अगर (tz->temperature > tz->last_temperature)
			trend = THERMAL_TREND_RAISING;
		अन्यथा अगर (tz->temperature < tz->last_temperature)
			trend = THERMAL_TREND_DROPPING;
		अन्यथा
			trend = THERMAL_TREND_STABLE;
	पूर्ण

	वापस trend;
पूर्ण
EXPORT_SYMBOL(get_tz_trend);

काष्ठा thermal_instance *
get_thermal_instance(काष्ठा thermal_zone_device *tz,
		     काष्ठा thermal_cooling_device *cdev, पूर्णांक trip)
अणु
	काष्ठा thermal_instance *pos = शून्य;
	काष्ठा thermal_instance *target_instance = शून्य;

	mutex_lock(&tz->lock);
	mutex_lock(&cdev->lock);

	list_क्रम_each_entry(pos, &tz->thermal_instances, tz_node) अणु
		अगर (pos->tz == tz && pos->trip == trip && pos->cdev == cdev) अणु
			target_instance = pos;
			अवरोध;
		पूर्ण
	पूर्ण

	mutex_unlock(&cdev->lock);
	mutex_unlock(&tz->lock);

	वापस target_instance;
पूर्ण
EXPORT_SYMBOL(get_thermal_instance);

/**
 * thermal_zone_get_temp() - वापसs the temperature of a thermal zone
 * @tz: a valid poपूर्णांकer to a काष्ठा thermal_zone_device
 * @temp: a valid poपूर्णांकer to where to store the resulting temperature.
 *
 * When a valid thermal zone reference is passed, it will fetch its
 * temperature and fill @temp.
 *
 * Return: On success वापसs 0, an error code otherwise
 */
पूर्णांक thermal_zone_get_temp(काष्ठा thermal_zone_device *tz, पूर्णांक *temp)
अणु
	पूर्णांक ret = -EINVAL;
	पूर्णांक count;
	पूर्णांक crit_temp = पूर्णांक_उच्च;
	क्रमागत thermal_trip_type type;

	अगर (!tz || IS_ERR(tz) || !tz->ops->get_temp)
		जाओ निकास;

	mutex_lock(&tz->lock);

	ret = tz->ops->get_temp(tz, temp);

	अगर (IS_ENABLED(CONFIG_THERMAL_EMULATION) && tz->emul_temperature) अणु
		क्रम (count = 0; count < tz->trips; count++) अणु
			ret = tz->ops->get_trip_type(tz, count, &type);
			अगर (!ret && type == THERMAL_TRIP_CRITICAL) अणु
				ret = tz->ops->get_trip_temp(tz, count,
						&crit_temp);
				अवरोध;
			पूर्ण
		पूर्ण

		/*
		 * Only allow emulating a temperature when the real temperature
		 * is below the critical temperature so that the emulation code
		 * cannot hide critical conditions.
		 */
		अगर (!ret && *temp < crit_temp)
			*temp = tz->emul_temperature;
	पूर्ण

	mutex_unlock(&tz->lock);
निकास:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(thermal_zone_get_temp);

/**
 * thermal_zone_set_trips - Computes the next trip poपूर्णांकs क्रम the driver
 * @tz: a poपूर्णांकer to a thermal zone device काष्ठाure
 *
 * The function computes the next temperature boundaries by browsing
 * the trip poपूर्णांकs. The result is the बंदr low and high trip poपूर्णांकs
 * to the current temperature. These values are passed to the backend
 * driver to let it set its own notअगरication mechanism (usually an
 * पूर्णांकerrupt).
 *
 * It करोes not वापस a value
 */
व्योम thermal_zone_set_trips(काष्ठा thermal_zone_device *tz)
अणु
	पूर्णांक low = -पूर्णांक_उच्च;
	पूर्णांक high = पूर्णांक_उच्च;
	पूर्णांक trip_temp, hysteresis;
	पूर्णांक i, ret;

	mutex_lock(&tz->lock);

	अगर (!tz->ops->set_trips || !tz->ops->get_trip_hyst)
		जाओ निकास;

	क्रम (i = 0; i < tz->trips; i++) अणु
		पूर्णांक trip_low;

		tz->ops->get_trip_temp(tz, i, &trip_temp);
		tz->ops->get_trip_hyst(tz, i, &hysteresis);

		trip_low = trip_temp - hysteresis;

		अगर (trip_low < tz->temperature && trip_low > low)
			low = trip_low;

		अगर (trip_temp > tz->temperature && trip_temp < high)
			high = trip_temp;
	पूर्ण

	/* No need to change trip poपूर्णांकs */
	अगर (tz->prev_low_trip == low && tz->prev_high_trip == high)
		जाओ निकास;

	tz->prev_low_trip = low;
	tz->prev_high_trip = high;

	dev_dbg(&tz->device,
		"new temperature boundaries: %d < x < %d\n", low, high);

	/*
	 * Set a temperature winकरोw. When this winकरोw is left the driver
	 * must inक्रमm the thermal core via thermal_zone_device_update.
	 */
	ret = tz->ops->set_trips(tz, low, high);
	अगर (ret)
		dev_err(&tz->device, "Failed to set trips: %d\n", ret);

निकास:
	mutex_unlock(&tz->lock);
पूर्ण

व्योम thermal_set_delay_jअगरfies(अचिन्हित दीर्घ *delay_jअगरfies, पूर्णांक delay_ms)
अणु
	*delay_jअगरfies = msecs_to_jअगरfies(delay_ms);
	अगर (delay_ms > 1000)
		*delay_jअगरfies = round_jअगरfies(*delay_jअगरfies);
पूर्ण

अटल व्योम thermal_cdev_set_cur_state(काष्ठा thermal_cooling_device *cdev,
				       पूर्णांक target)
अणु
	अगर (cdev->ops->set_cur_state(cdev, target))
		वापस;

	thermal_notअगरy_cdev_state_update(cdev->id, target);
	thermal_cooling_device_stats_update(cdev, target);
पूर्ण

व्योम __thermal_cdev_update(काष्ठा thermal_cooling_device *cdev)
अणु
	काष्ठा thermal_instance *instance;
	अचिन्हित दीर्घ target = 0;

	/* Make sure cdev enters the deepest cooling state */
	list_क्रम_each_entry(instance, &cdev->thermal_instances, cdev_node) अणु
		dev_dbg(&cdev->device, "zone%d->target=%lu\n",
			instance->tz->id, instance->target);
		अगर (instance->target == THERMAL_NO_TARGET)
			जारी;
		अगर (instance->target > target)
			target = instance->target;
	पूर्ण

	thermal_cdev_set_cur_state(cdev, target);

	trace_cdev_update(cdev, target);
	dev_dbg(&cdev->device, "set to state %lu\n", target);
पूर्ण

/**
 * thermal_cdev_update - update cooling device state अगर needed
 * @cdev:	poपूर्णांकer to काष्ठा thermal_cooling_device
 *
 * Update the cooling device state अगर there is a need.
 */
व्योम thermal_cdev_update(काष्ठा thermal_cooling_device *cdev)
अणु
	mutex_lock(&cdev->lock);
	अगर (!cdev->updated) अणु
		__thermal_cdev_update(cdev);
		cdev->updated = true;
	पूर्ण
	mutex_unlock(&cdev->lock);
पूर्ण
EXPORT_SYMBOL(thermal_cdev_update);

/**
 * thermal_zone_get_slope - वापस the slope attribute of the thermal zone
 * @tz: thermal zone device with the slope attribute
 *
 * Return: If the thermal zone device has a slope attribute, वापस it, अन्यथा
 * वापस 1.
 */
पूर्णांक thermal_zone_get_slope(काष्ठा thermal_zone_device *tz)
अणु
	अगर (tz && tz->tzp)
		वापस tz->tzp->slope;
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(thermal_zone_get_slope);

/**
 * thermal_zone_get_offset - वापस the offset attribute of the thermal zone
 * @tz: thermal zone device with the offset attribute
 *
 * Return: If the thermal zone device has a offset attribute, वापस it, अन्यथा
 * वापस 0.
 */
पूर्णांक thermal_zone_get_offset(काष्ठा thermal_zone_device *tz)
अणु
	अगर (tz && tz->tzp)
		वापस tz->tzp->offset;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(thermal_zone_get_offset);
