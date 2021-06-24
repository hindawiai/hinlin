<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  fair_share.c - A simple weight based Thermal governor
 *
 *  Copyright (C) 2012 Intel Corp
 *  Copyright (C) 2012 Durgaकरोss R <durgaकरोss.r@पूर्णांकel.com>
 *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/thermal.h>
#समावेश <trace/events/thermal.h>

#समावेश "thermal_core.h"

/**
 * get_trip_level: - obtains the current trip level क्रम a zone
 * @tz:		thermal zone device
 */
अटल पूर्णांक get_trip_level(काष्ठा thermal_zone_device *tz)
अणु
	पूर्णांक count = 0;
	पूर्णांक trip_temp;
	क्रमागत thermal_trip_type trip_type;

	अगर (tz->trips == 0 || !tz->ops->get_trip_temp)
		वापस 0;

	क्रम (count = 0; count < tz->trips; count++) अणु
		tz->ops->get_trip_temp(tz, count, &trip_temp);
		अगर (tz->temperature < trip_temp)
			अवरोध;
	पूर्ण

	/*
	 * count > 0 only अगर temperature is greater than first trip
	 * poपूर्णांक, in which हाल, trip_poपूर्णांक = count - 1
	 */
	अगर (count > 0) अणु
		tz->ops->get_trip_type(tz, count - 1, &trip_type);
		trace_thermal_zone_trip(tz, count - 1, trip_type);
	पूर्ण

	वापस count;
पूर्ण

अटल दीर्घ get_target_state(काष्ठा thermal_zone_device *tz,
		काष्ठा thermal_cooling_device *cdev, पूर्णांक percentage, पूर्णांक level)
अणु
	अचिन्हित दीर्घ max_state;

	cdev->ops->get_max_state(cdev, &max_state);

	वापस (दीर्घ)(percentage * level * max_state) / (100 * tz->trips);
पूर्ण

/**
 * fair_share_throttle - throttles devices associated with the given zone
 * @tz: thermal_zone_device
 * @trip: trip poपूर्णांक index
 *
 * Throttling Logic: This uses three parameters to calculate the new
 * throttle state of the cooling devices associated with the given zone.
 *
 * Parameters used क्रम Throttling:
 * P1. max_state: Maximum throttle state exposed by the cooling device.
 * P2. percentage[i]/100:
 *	How 'effective' the 'i'th device is, in cooling the given zone.
 * P3. cur_trip_level/max_no_of_trips:
 *	This describes the extent to which the devices should be throttled.
 *	We करो not want to throttle too much when we trip a lower temperature,
 *	whereas the throttling is at full swing अगर we trip critical levels.
 *	(Heavily assumes the trip poपूर्णांकs are in ascending order)
 * new_state of cooling device = P3 * P2 * P1
 */
अटल पूर्णांक fair_share_throttle(काष्ठा thermal_zone_device *tz, पूर्णांक trip)
अणु
	काष्ठा thermal_instance *instance;
	पूर्णांक total_weight = 0;
	पूर्णांक total_instance = 0;
	पूर्णांक cur_trip_level = get_trip_level(tz);

	mutex_lock(&tz->lock);

	list_क्रम_each_entry(instance, &tz->thermal_instances, tz_node) अणु
		अगर (instance->trip != trip)
			जारी;

		total_weight += instance->weight;
		total_instance++;
	पूर्ण

	list_क्रम_each_entry(instance, &tz->thermal_instances, tz_node) अणु
		पूर्णांक percentage;
		काष्ठा thermal_cooling_device *cdev = instance->cdev;

		अगर (instance->trip != trip)
			जारी;

		अगर (!total_weight)
			percentage = 100 / total_instance;
		अन्यथा
			percentage = (instance->weight * 100) / total_weight;

		instance->target = get_target_state(tz, cdev, percentage,
						    cur_trip_level);

		mutex_lock(&cdev->lock);
		__thermal_cdev_update(cdev);
		mutex_unlock(&cdev->lock);
	पूर्ण

	mutex_unlock(&tz->lock);
	वापस 0;
पूर्ण

अटल काष्ठा thermal_governor thermal_gov_fair_share = अणु
	.name		= "fair_share",
	.throttle	= fair_share_throttle,
पूर्ण;
THERMAL_GOVERNOR_DECLARE(thermal_gov_fair_share);
