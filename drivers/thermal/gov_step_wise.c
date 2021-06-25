<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  step_wise.c - A step-by-step Thermal throttling governor
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

/*
 * If the temperature is higher than a trip poपूर्णांक,
 *    a. अगर the trend is THERMAL_TREND_RAISING, use higher cooling
 *       state क्रम this trip poपूर्णांक
 *    b. अगर the trend is THERMAL_TREND_DROPPING, करो nothing
 *    c. अगर the trend is THERMAL_TREND_RAISE_FULL, use upper limit
 *       क्रम this trip poपूर्णांक
 *    d. अगर the trend is THERMAL_TREND_DROP_FULL, use lower limit
 *       क्रम this trip poपूर्णांक
 * If the temperature is lower than a trip poपूर्णांक,
 *    a. अगर the trend is THERMAL_TREND_RAISING, करो nothing
 *    b. अगर the trend is THERMAL_TREND_DROPPING, use lower cooling
 *       state क्रम this trip poपूर्णांक, अगर the cooling state alपढ़ोy
 *       equals lower limit, deactivate the thermal instance
 *    c. अगर the trend is THERMAL_TREND_RAISE_FULL, करो nothing
 *    d. अगर the trend is THERMAL_TREND_DROP_FULL, use lower limit,
 *       अगर the cooling state alपढ़ोy equals lower limit,
 *       deactivate the thermal instance
 */
अटल अचिन्हित दीर्घ get_target_state(काष्ठा thermal_instance *instance,
				क्रमागत thermal_trend trend, bool throttle)
अणु
	काष्ठा thermal_cooling_device *cdev = instance->cdev;
	अचिन्हित दीर्घ cur_state;
	अचिन्हित दीर्घ next_target;

	/*
	 * We keep this instance the way it is by शेष.
	 * Otherwise, we use the current state of the
	 * cdev in use to determine the next_target.
	 */
	cdev->ops->get_cur_state(cdev, &cur_state);
	next_target = instance->target;
	dev_dbg(&cdev->device, "cur_state=%ld\n", cur_state);

	अगर (!instance->initialized) अणु
		अगर (throttle) अणु
			next_target = (cur_state + 1) >= instance->upper ?
					instance->upper :
					((cur_state + 1) < instance->lower ?
					instance->lower : (cur_state + 1));
		पूर्ण अन्यथा अणु
			next_target = THERMAL_NO_TARGET;
		पूर्ण

		वापस next_target;
	पूर्ण

	चयन (trend) अणु
	हाल THERMAL_TREND_RAISING:
		अगर (throttle) अणु
			next_target = cur_state < instance->upper ?
				    (cur_state + 1) : instance->upper;
			अगर (next_target < instance->lower)
				next_target = instance->lower;
		पूर्ण
		अवरोध;
	हाल THERMAL_TREND_RAISE_FULL:
		अगर (throttle)
			next_target = instance->upper;
		अवरोध;
	हाल THERMAL_TREND_DROPPING:
		अगर (cur_state <= instance->lower) अणु
			अगर (!throttle)
				next_target = THERMAL_NO_TARGET;
		पूर्ण अन्यथा अणु
			अगर (!throttle) अणु
				next_target = cur_state - 1;
				अगर (next_target > instance->upper)
					next_target = instance->upper;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल THERMAL_TREND_DROP_FULL:
		अगर (cur_state == instance->lower) अणु
			अगर (!throttle)
				next_target = THERMAL_NO_TARGET;
		पूर्ण अन्यथा
			next_target = instance->lower;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस next_target;
पूर्ण

अटल व्योम update_passive_instance(काष्ठा thermal_zone_device *tz,
				क्रमागत thermal_trip_type type, पूर्णांक value)
अणु
	/*
	 * If value is +1, activate a passive instance.
	 * If value is -1, deactivate a passive instance.
	 */
	अगर (type == THERMAL_TRIP_PASSIVE)
		tz->passive += value;
पूर्ण

अटल व्योम thermal_zone_trip_update(काष्ठा thermal_zone_device *tz, पूर्णांक trip)
अणु
	पूर्णांक trip_temp;
	क्रमागत thermal_trip_type trip_type;
	क्रमागत thermal_trend trend;
	काष्ठा thermal_instance *instance;
	bool throttle = false;
	पूर्णांक old_target;

	tz->ops->get_trip_temp(tz, trip, &trip_temp);
	tz->ops->get_trip_type(tz, trip, &trip_type);

	trend = get_tz_trend(tz, trip);

	अगर (tz->temperature >= trip_temp) अणु
		throttle = true;
		trace_thermal_zone_trip(tz, trip, trip_type);
	पूर्ण

	dev_dbg(&tz->device, "Trip%d[type=%d,temp=%d]:trend=%d,throttle=%d\n",
				trip, trip_type, trip_temp, trend, throttle);

	mutex_lock(&tz->lock);

	list_क्रम_each_entry(instance, &tz->thermal_instances, tz_node) अणु
		अगर (instance->trip != trip)
			जारी;

		old_target = instance->target;
		instance->target = get_target_state(instance, trend, throttle);
		dev_dbg(&instance->cdev->device, "old_target=%d, target=%d\n",
					old_target, (पूर्णांक)instance->target);

		अगर (instance->initialized && old_target == instance->target)
			जारी;

		/* Activate a passive thermal instance */
		अगर (old_target == THERMAL_NO_TARGET &&
			instance->target != THERMAL_NO_TARGET)
			update_passive_instance(tz, trip_type, 1);
		/* Deactivate a passive thermal instance */
		अन्यथा अगर (old_target != THERMAL_NO_TARGET &&
			instance->target == THERMAL_NO_TARGET)
			update_passive_instance(tz, trip_type, -1);

		instance->initialized = true;
		mutex_lock(&instance->cdev->lock);
		instance->cdev->updated = false; /* cdev needs update */
		mutex_unlock(&instance->cdev->lock);
	पूर्ण

	mutex_unlock(&tz->lock);
पूर्ण

/**
 * step_wise_throttle - throttles devices associated with the given zone
 * @tz: thermal_zone_device
 * @trip: trip poपूर्णांक index
 *
 * Throttling Logic: This uses the trend of the thermal zone to throttle.
 * If the thermal zone is 'heating up' this throttles all the cooling
 * devices associated with the zone and its particular trip poपूर्णांक, by one
 * step. If the zone is 'cooling down' it brings back the perक्रमmance of
 * the devices by one step.
 */
अटल पूर्णांक step_wise_throttle(काष्ठा thermal_zone_device *tz, पूर्णांक trip)
अणु
	काष्ठा thermal_instance *instance;

	thermal_zone_trip_update(tz, trip);

	mutex_lock(&tz->lock);

	list_क्रम_each_entry(instance, &tz->thermal_instances, tz_node)
		thermal_cdev_update(instance->cdev);

	mutex_unlock(&tz->lock);

	वापस 0;
पूर्ण

अटल काष्ठा thermal_governor thermal_gov_step_wise = अणु
	.name		= "step_wise",
	.throttle	= step_wise_throttle,
पूर्ण;
THERMAL_GOVERNOR_DECLARE(thermal_gov_step_wise);
