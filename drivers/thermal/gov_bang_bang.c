<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  gov_bang_bang.c - A simple thermal throttling governor using hysteresis
 *
 *  Copyright (C) 2014 Peter Kaestle <peter@piie.net>
 *
 *  Based on step_wise.c with following Copyrights:
 *  Copyright (C) 2012 Intel Corp
 *  Copyright (C) 2012 Durgaकरोss R <durgaकरोss.r@पूर्णांकel.com>
 */

#समावेश <linux/thermal.h>

#समावेश "thermal_core.h"

अटल व्योम thermal_zone_trip_update(काष्ठा thermal_zone_device *tz, पूर्णांक trip)
अणु
	पूर्णांक trip_temp, trip_hyst;
	काष्ठा thermal_instance *instance;

	tz->ops->get_trip_temp(tz, trip, &trip_temp);

	अगर (!tz->ops->get_trip_hyst) अणु
		pr_warn_once("Undefined get_trip_hyst for thermal zone %s - "
				"running with default hysteresis zero\n", tz->type);
		trip_hyst = 0;
	पूर्ण अन्यथा
		tz->ops->get_trip_hyst(tz, trip, &trip_hyst);

	dev_dbg(&tz->device, "Trip%d[temp=%d]:temp=%d:hyst=%d\n",
				trip, trip_temp, tz->temperature,
				trip_hyst);

	mutex_lock(&tz->lock);

	list_क्रम_each_entry(instance, &tz->thermal_instances, tz_node) अणु
		अगर (instance->trip != trip)
			जारी;

		/* in हाल fan is in initial state, चयन the fan off */
		अगर (instance->target == THERMAL_NO_TARGET)
			instance->target = 0;

		/* in हाल fan is neither on nor off set the fan to active */
		अगर (instance->target != 0 && instance->target != 1) अणु
			pr_warn("Thermal instance %s controlled by bang-bang has unexpected state: %ld\n",
					instance->name, instance->target);
			instance->target = 1;
		पूर्ण

		/*
		 * enable fan when temperature exceeds trip_temp and disable
		 * the fan in हाल it falls below trip_temp minus hysteresis
		 */
		अगर (instance->target == 0 && tz->temperature >= trip_temp)
			instance->target = 1;
		अन्यथा अगर (instance->target == 1 &&
				tz->temperature <= trip_temp - trip_hyst)
			instance->target = 0;

		dev_dbg(&instance->cdev->device, "target=%d\n",
					(पूर्णांक)instance->target);

		mutex_lock(&instance->cdev->lock);
		instance->cdev->updated = false; /* cdev needs update */
		mutex_unlock(&instance->cdev->lock);
	पूर्ण

	mutex_unlock(&tz->lock);
पूर्ण

/**
 * bang_bang_control - controls devices associated with the given zone
 * @tz: thermal_zone_device
 * @trip: the trip poपूर्णांक
 *
 * Regulation Logic: a two poपूर्णांक regulation, deliver cooling state depending
 * on the previous state shown in this diagram:
 *
 *                Fan:   OFF    ON
 *
 *                              |
 *                              |
 *          trip_temp:    +---->+
 *                        |     |        ^
 *                        |     |        |
 *                        |     |   Temperature
 * (trip_temp - hyst):    +<----+
 *                        |
 *                        |
 *                        |
 *
 *   * If the fan is not running and temperature exceeds trip_temp, the fan
 *     माला_लो turned on.
 *   * In हाल the fan is running, temperature must fall below
 *     (trip_temp - hyst) so that the fan माला_लो turned off again.
 *
 */
अटल पूर्णांक bang_bang_control(काष्ठा thermal_zone_device *tz, पूर्णांक trip)
अणु
	काष्ठा thermal_instance *instance;

	thermal_zone_trip_update(tz, trip);

	mutex_lock(&tz->lock);

	list_क्रम_each_entry(instance, &tz->thermal_instances, tz_node)
		thermal_cdev_update(instance->cdev);

	mutex_unlock(&tz->lock);

	वापस 0;
पूर्ण

अटल काष्ठा thermal_governor thermal_gov_bang_bang = अणु
	.name		= "bang_bang",
	.throttle	= bang_bang_control,
पूर्ण;
THERMAL_GOVERNOR_DECLARE(thermal_gov_bang_bang);
