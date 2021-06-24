<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  user_space.c - A simple user space Thermal events notअगरier
 *
 *  Copyright (C) 2012 Intel Corp
 *  Copyright (C) 2012 Durgaकरोss R <durgaकरोss.r@पूर्णांकel.com>
 *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/slab.h>
#समावेश <linux/thermal.h>

#समावेश "thermal_core.h"

/**
 * notअगरy_user_space - Notअगरies user space about thermal events
 * @tz: thermal_zone_device
 * @trip: trip poपूर्णांक index
 *
 * This function notअगरies the user space through UEvents.
 */
अटल पूर्णांक notअगरy_user_space(काष्ठा thermal_zone_device *tz, पूर्णांक trip)
अणु
	अक्षर *thermal_prop[5];
	पूर्णांक i;

	mutex_lock(&tz->lock);
	thermal_prop[0] = kaप्र_लिखो(GFP_KERNEL, "NAME=%s", tz->type);
	thermal_prop[1] = kaप्र_लिखो(GFP_KERNEL, "TEMP=%d", tz->temperature);
	thermal_prop[2] = kaप्र_लिखो(GFP_KERNEL, "TRIP=%d", trip);
	thermal_prop[3] = kaप्र_लिखो(GFP_KERNEL, "EVENT=%d", tz->notअगरy_event);
	thermal_prop[4] = शून्य;
	kobject_uevent_env(&tz->device.kobj, KOBJ_CHANGE, thermal_prop);
	क्रम (i = 0; i < 4; ++i)
		kमुक्त(thermal_prop[i]);
	mutex_unlock(&tz->lock);
	वापस 0;
पूर्ण

अटल काष्ठा thermal_governor thermal_gov_user_space = अणु
	.name		= "user_space",
	.throttle	= notअगरy_user_space,
पूर्ण;
THERMAL_GOVERNOR_DECLARE(thermal_gov_user_space);
