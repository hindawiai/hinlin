<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  thermal.c - Generic Thermal Management Sysfs support.
 *
 *  Copyright (C) 2008 Intel Corp
 *  Copyright (C) 2008 Zhang Rui <rui.zhang@पूर्णांकel.com>
 *  Copyright (C) 2008 Sujith Thomas <sujith.thomas@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/idr.h>
#समावेश <linux/thermal.h>
#समावेश <linux/reboot.h>
#समावेश <linux/माला.स>
#समावेश <linux/of.h>
#समावेश <linux/suspend.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/thermal.h>

#समावेश "thermal_core.h"
#समावेश "thermal_hwmon.h"

अटल DEFINE_IDA(thermal_tz_ida);
अटल DEFINE_IDA(thermal_cdev_ida);

अटल LIST_HEAD(thermal_tz_list);
अटल LIST_HEAD(thermal_cdev_list);
अटल LIST_HEAD(thermal_governor_list);

अटल DEFINE_MUTEX(thermal_list_lock);
अटल DEFINE_MUTEX(thermal_governor_lock);
अटल DEFINE_MUTEX(घातeroff_lock);

अटल atomic_t in_suspend;
अटल bool घातer_off_triggered;

अटल काष्ठा thermal_governor *def_governor;

/*
 * Governor section: set of functions to handle thermal governors
 *
 * Functions to help in the lअगरe cycle of thermal governors within
 * the thermal core and by the thermal governor code.
 */

अटल काष्ठा thermal_governor *__find_governor(स्थिर अक्षर *name)
अणु
	काष्ठा thermal_governor *pos;

	अगर (!name || !name[0])
		वापस def_governor;

	list_क्रम_each_entry(pos, &thermal_governor_list, governor_list)
		अगर (!strnहालcmp(name, pos->name, THERMAL_NAME_LENGTH))
			वापस pos;

	वापस शून्य;
पूर्ण

/**
 * bind_previous_governor() - bind the previous governor of the thermal zone
 * @tz:		a valid poपूर्णांकer to a काष्ठा thermal_zone_device
 * @failed_gov_name:	the name of the governor that failed to रेजिस्टर
 *
 * Register the previous governor of the thermal zone after a new
 * governor has failed to be bound.
 */
अटल व्योम bind_previous_governor(काष्ठा thermal_zone_device *tz,
				   स्थिर अक्षर *failed_gov_name)
अणु
	अगर (tz->governor && tz->governor->bind_to_tz) अणु
		अगर (tz->governor->bind_to_tz(tz)) अणु
			dev_err(&tz->device,
				"governor %s failed to bind and the previous one (%s) failed to bind again, thermal zone %s has no governor\n",
				failed_gov_name, tz->governor->name, tz->type);
			tz->governor = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * thermal_set_governor() - Switch to another governor
 * @tz:		a valid poपूर्णांकer to a काष्ठा thermal_zone_device
 * @new_gov:	poपूर्णांकer to the new governor
 *
 * Change the governor of thermal zone @tz.
 *
 * Return: 0 on success, an error अगर the new governor's bind_to_tz() failed.
 */
अटल पूर्णांक thermal_set_governor(काष्ठा thermal_zone_device *tz,
				काष्ठा thermal_governor *new_gov)
अणु
	पूर्णांक ret = 0;

	अगर (tz->governor && tz->governor->unbind_from_tz)
		tz->governor->unbind_from_tz(tz);

	अगर (new_gov && new_gov->bind_to_tz) अणु
		ret = new_gov->bind_to_tz(tz);
		अगर (ret) अणु
			bind_previous_governor(tz, new_gov->name);

			वापस ret;
		पूर्ण
	पूर्ण

	tz->governor = new_gov;

	वापस ret;
पूर्ण

पूर्णांक thermal_रेजिस्टर_governor(काष्ठा thermal_governor *governor)
अणु
	पूर्णांक err;
	स्थिर अक्षर *name;
	काष्ठा thermal_zone_device *pos;

	अगर (!governor)
		वापस -EINVAL;

	mutex_lock(&thermal_governor_lock);

	err = -EBUSY;
	अगर (!__find_governor(governor->name)) अणु
		bool match_शेष;

		err = 0;
		list_add(&governor->governor_list, &thermal_governor_list);
		match_शेष = !म_भेदन(governor->name,
					 DEFAULT_THERMAL_GOVERNOR,
					 THERMAL_NAME_LENGTH);

		अगर (!def_governor && match_शेष)
			def_governor = governor;
	पूर्ण

	mutex_lock(&thermal_list_lock);

	list_क्रम_each_entry(pos, &thermal_tz_list, node) अणु
		/*
		 * only thermal zones with specअगरied tz->tzp->governor_name
		 * may run with tz->govenor unset
		 */
		अगर (pos->governor)
			जारी;

		name = pos->tzp->governor_name;

		अगर (!strnहालcmp(name, governor->name, THERMAL_NAME_LENGTH)) अणु
			पूर्णांक ret;

			ret = thermal_set_governor(pos, governor);
			अगर (ret)
				dev_err(&pos->device,
					"Failed to set governor %s for thermal zone %s: %d\n",
					governor->name, pos->type, ret);
		पूर्ण
	पूर्ण

	mutex_unlock(&thermal_list_lock);
	mutex_unlock(&thermal_governor_lock);

	वापस err;
पूर्ण

व्योम thermal_unरेजिस्टर_governor(काष्ठा thermal_governor *governor)
अणु
	काष्ठा thermal_zone_device *pos;

	अगर (!governor)
		वापस;

	mutex_lock(&thermal_governor_lock);

	अगर (!__find_governor(governor->name))
		जाओ निकास;

	mutex_lock(&thermal_list_lock);

	list_क्रम_each_entry(pos, &thermal_tz_list, node) अणु
		अगर (!strnहालcmp(pos->governor->name, governor->name,
				 THERMAL_NAME_LENGTH))
			thermal_set_governor(pos, शून्य);
	पूर्ण

	mutex_unlock(&thermal_list_lock);
	list_del(&governor->governor_list);
निकास:
	mutex_unlock(&thermal_governor_lock);
पूर्ण

पूर्णांक thermal_zone_device_set_policy(काष्ठा thermal_zone_device *tz,
				   अक्षर *policy)
अणु
	काष्ठा thermal_governor *gov;
	पूर्णांक ret = -EINVAL;

	mutex_lock(&thermal_governor_lock);
	mutex_lock(&tz->lock);

	gov = __find_governor(strim(policy));
	अगर (!gov)
		जाओ निकास;

	ret = thermal_set_governor(tz, gov);

निकास:
	mutex_unlock(&tz->lock);
	mutex_unlock(&thermal_governor_lock);

	thermal_notअगरy_tz_gov_change(tz->id, policy);

	वापस ret;
पूर्ण

पूर्णांक thermal_build_list_of_policies(अक्षर *buf)
अणु
	काष्ठा thermal_governor *pos;
	sमाप_प्रकार count = 0;
	sमाप_प्रकार size = PAGE_SIZE;

	mutex_lock(&thermal_governor_lock);

	list_क्रम_each_entry(pos, &thermal_governor_list, governor_list) अणु
		size = PAGE_SIZE - count;
		count += scnम_लिखो(buf + count, size, "%s ", pos->name);
	पूर्ण
	count += scnम_लिखो(buf + count, size, "\n");

	mutex_unlock(&thermal_governor_lock);

	वापस count;
पूर्ण

अटल व्योम __init thermal_unरेजिस्टर_governors(व्योम)
अणु
	काष्ठा thermal_governor **governor;

	क्रम_each_governor_table(governor)
		thermal_unरेजिस्टर_governor(*governor);
पूर्ण

अटल पूर्णांक __init thermal_रेजिस्टर_governors(व्योम)
अणु
	पूर्णांक ret = 0;
	काष्ठा thermal_governor **governor;

	क्रम_each_governor_table(governor) अणु
		ret = thermal_रेजिस्टर_governor(*governor);
		अगर (ret) अणु
			pr_err("Failed to register governor: '%s'",
			       (*governor)->name);
			अवरोध;
		पूर्ण

		pr_info("Registered thermal governor '%s'",
			(*governor)->name);
	पूर्ण

	अगर (ret) अणु
		काष्ठा thermal_governor **gov;

		क्रम_each_governor_table(gov) अणु
			अगर (gov == governor)
				अवरोध;
			thermal_unरेजिस्टर_governor(*gov);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Zone update section: मुख्य control loop applied to each zone जबतक monitoring
 *
 * in polling mode. The monitoring is करोne using a workqueue.
 * Same update may be करोne on a zone by calling thermal_zone_device_update().
 *
 * An update means:
 * - Non-critical trips will invoke the governor responsible क्रम that zone;
 * - Hot trips will produce a notअगरication to userspace;
 * - Critical trip poपूर्णांक will cause a प्रणाली shutकरोwn.
 */
अटल व्योम thermal_zone_device_set_polling(काष्ठा thermal_zone_device *tz,
					    अचिन्हित दीर्घ delay)
अणु
	अगर (delay)
		mod_delayed_work(प्रणाली_मुक्तzable_घातer_efficient_wq,
				 &tz->poll_queue, delay);
	अन्यथा
		cancel_delayed_work(&tz->poll_queue);
पूर्ण

अटल अंतरभूत bool should_stop_polling(काष्ठा thermal_zone_device *tz)
अणु
	वापस !thermal_zone_device_is_enabled(tz);
पूर्ण

अटल व्योम monitor_thermal_zone(काष्ठा thermal_zone_device *tz)
अणु
	bool stop;

	stop = should_stop_polling(tz);

	mutex_lock(&tz->lock);

	अगर (!stop && tz->passive)
		thermal_zone_device_set_polling(tz, tz->passive_delay_jअगरfies);
	अन्यथा अगर (!stop && tz->polling_delay_jअगरfies)
		thermal_zone_device_set_polling(tz, tz->polling_delay_jअगरfies);
	अन्यथा
		thermal_zone_device_set_polling(tz, 0);

	mutex_unlock(&tz->lock);
पूर्ण

अटल व्योम handle_non_critical_trips(काष्ठा thermal_zone_device *tz, पूर्णांक trip)
अणु
	tz->governor ? tz->governor->throttle(tz, trip) :
		       def_governor->throttle(tz, trip);
पूर्ण

/**
 * thermal_emergency_घातeroff_func - emergency घातeroff work after a known delay
 * @work: work_काष्ठा associated with the emergency घातeroff function
 *
 * This function is called in very critical situations to क्रमce
 * a kernel घातeroff after a configurable समयout value.
 */
अटल व्योम thermal_emergency_घातeroff_func(काष्ठा work_काष्ठा *work)
अणु
	/*
	 * We have reached here after the emergency thermal shutकरोwn
	 * Waiting period has expired. This means orderly_घातeroff has
	 * not been able to shut off the प्रणाली क्रम some reason.
	 * Try to shut करोwn the प्रणाली immediately using kernel_घातer_off
	 * अगर populated
	 */
	WARN(1, "Attempting kernel_power_off: Temperature too high\n");
	kernel_घातer_off();

	/*
	 * Worst of the worst हाल trigger emergency restart
	 */
	WARN(1, "Attempting emergency_restart: Temperature too high\n");
	emergency_restart();
पूर्ण

अटल DECLARE_DELAYED_WORK(thermal_emergency_घातeroff_work,
			    thermal_emergency_घातeroff_func);

/**
 * thermal_emergency_घातeroff - Trigger an emergency प्रणाली घातeroff
 *
 * This may be called from any critical situation to trigger a प्रणाली shutकरोwn
 * after a known period of समय. By शेष this is not scheduled.
 */
अटल व्योम thermal_emergency_घातeroff(व्योम)
अणु
	पूर्णांक घातeroff_delay_ms = CONFIG_THERMAL_EMERGENCY_POWEROFF_DELAY_MS;
	/*
	 * घातeroff_delay_ms must be a carefully profiled positive value.
	 * Its a must क्रम thermal_emergency_घातeroff_work to be scheduled
	 */
	अगर (घातeroff_delay_ms <= 0)
		वापस;
	schedule_delayed_work(&thermal_emergency_घातeroff_work,
			      msecs_to_jअगरfies(घातeroff_delay_ms));
पूर्ण

व्योम thermal_zone_device_critical(काष्ठा thermal_zone_device *tz)
अणु
	dev_emerg(&tz->device, "%s: critical temperature reached, "
		  "shutting down\n", tz->type);

	mutex_lock(&घातeroff_lock);
	अगर (!घातer_off_triggered) अणु
		/*
		 * Queue a backup emergency shutकरोwn in the event of
		 * orderly_घातeroff failure
		 */
		thermal_emergency_घातeroff();
		orderly_घातeroff(true);
		घातer_off_triggered = true;
	पूर्ण
	mutex_unlock(&घातeroff_lock);
पूर्ण
EXPORT_SYMBOL(thermal_zone_device_critical);

अटल व्योम handle_critical_trips(काष्ठा thermal_zone_device *tz,
				  पूर्णांक trip, क्रमागत thermal_trip_type trip_type)
अणु
	पूर्णांक trip_temp;

	tz->ops->get_trip_temp(tz, trip, &trip_temp);

	/* If we have not crossed the trip_temp, we करो not care. */
	अगर (trip_temp <= 0 || tz->temperature < trip_temp)
		वापस;

	trace_thermal_zone_trip(tz, trip, trip_type);

	अगर (trip_type == THERMAL_TRIP_HOT && tz->ops->hot)
		tz->ops->hot(tz);
	अन्यथा अगर (trip_type == THERMAL_TRIP_CRITICAL)
		tz->ops->critical(tz);
पूर्ण

अटल व्योम handle_thermal_trip(काष्ठा thermal_zone_device *tz, पूर्णांक trip)
अणु
	क्रमागत thermal_trip_type type;
	पूर्णांक trip_temp, hyst = 0;

	/* Ignore disabled trip poपूर्णांकs */
	अगर (test_bit(trip, &tz->trips_disabled))
		वापस;

	tz->ops->get_trip_temp(tz, trip, &trip_temp);
	tz->ops->get_trip_type(tz, trip, &type);
	अगर (tz->ops->get_trip_hyst)
		tz->ops->get_trip_hyst(tz, trip, &hyst);

	अगर (tz->last_temperature != THERMAL_TEMP_INVALID) अणु
		अगर (tz->last_temperature < trip_temp &&
		    tz->temperature >= trip_temp)
			thermal_notअगरy_tz_trip_up(tz->id, trip);
		अगर (tz->last_temperature >= trip_temp &&
		    tz->temperature < (trip_temp - hyst))
			thermal_notअगरy_tz_trip_करोwn(tz->id, trip);
	पूर्ण

	अगर (type == THERMAL_TRIP_CRITICAL || type == THERMAL_TRIP_HOT)
		handle_critical_trips(tz, trip, type);
	अन्यथा
		handle_non_critical_trips(tz, trip);
	/*
	 * Alright, we handled this trip successfully.
	 * So, start monitoring again.
	 */
	monitor_thermal_zone(tz);
पूर्ण

अटल व्योम update_temperature(काष्ठा thermal_zone_device *tz)
अणु
	पूर्णांक temp, ret;

	ret = thermal_zone_get_temp(tz, &temp);
	अगर (ret) अणु
		अगर (ret != -EAGAIN)
			dev_warn(&tz->device,
				 "failed to read out thermal zone (%d)\n",
				 ret);
		वापस;
	पूर्ण

	mutex_lock(&tz->lock);
	tz->last_temperature = tz->temperature;
	tz->temperature = temp;
	mutex_unlock(&tz->lock);

	trace_thermal_temperature(tz);

	thermal_genl_sampling_temp(tz->id, temp);
पूर्ण

अटल व्योम thermal_zone_device_init(काष्ठा thermal_zone_device *tz)
अणु
	काष्ठा thermal_instance *pos;
	tz->temperature = THERMAL_TEMP_INVALID;
	list_क्रम_each_entry(pos, &tz->thermal_instances, tz_node)
		pos->initialized = false;
पूर्ण

अटल पूर्णांक thermal_zone_device_set_mode(काष्ठा thermal_zone_device *tz,
					क्रमागत thermal_device_mode mode)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&tz->lock);

	/* करो nothing अगर mode isn't changing */
	अगर (mode == tz->mode) अणु
		mutex_unlock(&tz->lock);

		वापस ret;
	पूर्ण

	अगर (tz->ops->change_mode)
		ret = tz->ops->change_mode(tz, mode);

	अगर (!ret)
		tz->mode = mode;

	mutex_unlock(&tz->lock);

	thermal_zone_device_update(tz, THERMAL_EVENT_UNSPECIFIED);

	अगर (mode == THERMAL_DEVICE_ENABLED)
		thermal_notअगरy_tz_enable(tz->id);
	अन्यथा
		thermal_notअगरy_tz_disable(tz->id);

	वापस ret;
पूर्ण

पूर्णांक thermal_zone_device_enable(काष्ठा thermal_zone_device *tz)
अणु
	वापस thermal_zone_device_set_mode(tz, THERMAL_DEVICE_ENABLED);
पूर्ण
EXPORT_SYMBOL_GPL(thermal_zone_device_enable);

पूर्णांक thermal_zone_device_disable(काष्ठा thermal_zone_device *tz)
अणु
	वापस thermal_zone_device_set_mode(tz, THERMAL_DEVICE_DISABLED);
पूर्ण
EXPORT_SYMBOL_GPL(thermal_zone_device_disable);

पूर्णांक thermal_zone_device_is_enabled(काष्ठा thermal_zone_device *tz)
अणु
	क्रमागत thermal_device_mode mode;

	mutex_lock(&tz->lock);

	mode = tz->mode;

	mutex_unlock(&tz->lock);

	वापस mode == THERMAL_DEVICE_ENABLED;
पूर्ण

व्योम thermal_zone_device_update(काष्ठा thermal_zone_device *tz,
				क्रमागत thermal_notअगरy_event event)
अणु
	पूर्णांक count;

	अगर (should_stop_polling(tz))
		वापस;

	अगर (atomic_पढ़ो(&in_suspend))
		वापस;

	अगर (WARN_ONCE(!tz->ops->get_temp, "'%s' must not be called without "
		      "'get_temp' ops set\n", __func__))
		वापस;

	update_temperature(tz);

	thermal_zone_set_trips(tz);

	tz->notअगरy_event = event;

	क्रम (count = 0; count < tz->trips; count++)
		handle_thermal_trip(tz, count);
पूर्ण
EXPORT_SYMBOL_GPL(thermal_zone_device_update);

अटल व्योम thermal_zone_device_check(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा thermal_zone_device *tz = container_of(work, काष्ठा
						      thermal_zone_device,
						      poll_queue.work);
	thermal_zone_device_update(tz, THERMAL_EVENT_UNSPECIFIED);
पूर्ण

पूर्णांक क्रम_each_thermal_governor(पूर्णांक (*cb)(काष्ठा thermal_governor *, व्योम *),
			      व्योम *data)
अणु
	काष्ठा thermal_governor *gov;
	पूर्णांक ret = 0;

	mutex_lock(&thermal_governor_lock);
	list_क्रम_each_entry(gov, &thermal_governor_list, governor_list) अणु
		ret = cb(gov, data);
		अगर (ret)
			अवरोध;
	पूर्ण
	mutex_unlock(&thermal_governor_lock);

	वापस ret;
पूर्ण

पूर्णांक क्रम_each_thermal_cooling_device(पूर्णांक (*cb)(काष्ठा thermal_cooling_device *,
					      व्योम *), व्योम *data)
अणु
	काष्ठा thermal_cooling_device *cdev;
	पूर्णांक ret = 0;

	mutex_lock(&thermal_list_lock);
	list_क्रम_each_entry(cdev, &thermal_cdev_list, node) अणु
		ret = cb(cdev, data);
		अगर (ret)
			अवरोध;
	पूर्ण
	mutex_unlock(&thermal_list_lock);

	वापस ret;
पूर्ण

पूर्णांक क्रम_each_thermal_zone(पूर्णांक (*cb)(काष्ठा thermal_zone_device *, व्योम *),
			  व्योम *data)
अणु
	काष्ठा thermal_zone_device *tz;
	पूर्णांक ret = 0;

	mutex_lock(&thermal_list_lock);
	list_क्रम_each_entry(tz, &thermal_tz_list, node) अणु
		ret = cb(tz, data);
		अगर (ret)
			अवरोध;
	पूर्ण
	mutex_unlock(&thermal_list_lock);

	वापस ret;
पूर्ण

काष्ठा thermal_zone_device *thermal_zone_get_by_id(पूर्णांक id)
अणु
	काष्ठा thermal_zone_device *tz, *match = शून्य;

	mutex_lock(&thermal_list_lock);
	list_क्रम_each_entry(tz, &thermal_tz_list, node) अणु
		अगर (tz->id == id) अणु
			match = tz;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&thermal_list_lock);

	वापस match;
पूर्ण

/*
 * Device management section: cooling devices, zones devices, and binding
 *
 * Set of functions provided by the thermal core क्रम:
 * - cooling devices lअगरecycle: registration, unregistration,
 *				binding, and unbinding.
 * - thermal zone devices lअगरecycle: registration, unregistration,
 *				     binding, and unbinding.
 */

/**
 * thermal_zone_bind_cooling_device() - bind a cooling device to a thermal zone
 * @tz:		poपूर्णांकer to काष्ठा thermal_zone_device
 * @trip:	indicates which trip poपूर्णांक the cooling devices is
 *		associated with in this thermal zone.
 * @cdev:	poपूर्णांकer to काष्ठा thermal_cooling_device
 * @upper:	the Maximum cooling state क्रम this trip poपूर्णांक.
 *		THERMAL_NO_LIMIT means no upper limit,
 *		and the cooling device can be in max_state.
 * @lower:	the Minimum cooling state can be used क्रम this trip poपूर्णांक.
 *		THERMAL_NO_LIMIT means no lower limit,
 *		and the cooling device can be in cooling state 0.
 * @weight:	The weight of the cooling device to be bound to the
 *		thermal zone. Use THERMAL_WEIGHT_DEFAULT क्रम the
 *		शेष value
 *
 * This पूर्णांकerface function bind a thermal cooling device to the certain trip
 * poपूर्णांक of a thermal zone device.
 * This function is usually called in the thermal zone device .bind callback.
 *
 * Return: 0 on success, the proper error value otherwise.
 */
पूर्णांक thermal_zone_bind_cooling_device(काष्ठा thermal_zone_device *tz,
				     पूर्णांक trip,
				     काष्ठा thermal_cooling_device *cdev,
				     अचिन्हित दीर्घ upper, अचिन्हित दीर्घ lower,
				     अचिन्हित पूर्णांक weight)
अणु
	काष्ठा thermal_instance *dev;
	काष्ठा thermal_instance *pos;
	काष्ठा thermal_zone_device *pos1;
	काष्ठा thermal_cooling_device *pos2;
	अचिन्हित दीर्घ max_state;
	पूर्णांक result, ret;

	अगर (trip >= tz->trips || trip < 0)
		वापस -EINVAL;

	list_क्रम_each_entry(pos1, &thermal_tz_list, node) अणु
		अगर (pos1 == tz)
			अवरोध;
	पूर्ण
	list_क्रम_each_entry(pos2, &thermal_cdev_list, node) अणु
		अगर (pos2 == cdev)
			अवरोध;
	पूर्ण

	अगर (tz != pos1 || cdev != pos2)
		वापस -EINVAL;

	ret = cdev->ops->get_max_state(cdev, &max_state);
	अगर (ret)
		वापस ret;

	/* lower शेष 0, upper शेष max_state */
	lower = lower == THERMAL_NO_LIMIT ? 0 : lower;
	upper = upper == THERMAL_NO_LIMIT ? max_state : upper;

	अगर (lower > upper || upper > max_state)
		वापस -EINVAL;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस -ENOMEM;
	dev->tz = tz;
	dev->cdev = cdev;
	dev->trip = trip;
	dev->upper = upper;
	dev->lower = lower;
	dev->target = THERMAL_NO_TARGET;
	dev->weight = weight;

	result = ida_simple_get(&tz->ida, 0, 0, GFP_KERNEL);
	अगर (result < 0)
		जाओ मुक्त_mem;

	dev->id = result;
	प्र_लिखो(dev->name, "cdev%d", dev->id);
	result =
	    sysfs_create_link(&tz->device.kobj, &cdev->device.kobj, dev->name);
	अगर (result)
		जाओ release_ida;

	प्र_लिखो(dev->attr_name, "cdev%d_trip_point", dev->id);
	sysfs_attr_init(&dev->attr.attr);
	dev->attr.attr.name = dev->attr_name;
	dev->attr.attr.mode = 0444;
	dev->attr.show = trip_poपूर्णांक_show;
	result = device_create_file(&tz->device, &dev->attr);
	अगर (result)
		जाओ हटाओ_symbol_link;

	प्र_लिखो(dev->weight_attr_name, "cdev%d_weight", dev->id);
	sysfs_attr_init(&dev->weight_attr.attr);
	dev->weight_attr.attr.name = dev->weight_attr_name;
	dev->weight_attr.attr.mode = S_IWUSR | S_IRUGO;
	dev->weight_attr.show = weight_show;
	dev->weight_attr.store = weight_store;
	result = device_create_file(&tz->device, &dev->weight_attr);
	अगर (result)
		जाओ हटाओ_trip_file;

	mutex_lock(&tz->lock);
	mutex_lock(&cdev->lock);
	list_क्रम_each_entry(pos, &tz->thermal_instances, tz_node)
		अगर (pos->tz == tz && pos->trip == trip && pos->cdev == cdev) अणु
			result = -EEXIST;
			अवरोध;
		पूर्ण
	अगर (!result) अणु
		list_add_tail(&dev->tz_node, &tz->thermal_instances);
		list_add_tail(&dev->cdev_node, &cdev->thermal_instances);
		atomic_set(&tz->need_update, 1);
	पूर्ण
	mutex_unlock(&cdev->lock);
	mutex_unlock(&tz->lock);

	अगर (!result)
		वापस 0;

	device_हटाओ_file(&tz->device, &dev->weight_attr);
हटाओ_trip_file:
	device_हटाओ_file(&tz->device, &dev->attr);
हटाओ_symbol_link:
	sysfs_हटाओ_link(&tz->device.kobj, dev->name);
release_ida:
	ida_simple_हटाओ(&tz->ida, dev->id);
मुक्त_mem:
	kमुक्त(dev);
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(thermal_zone_bind_cooling_device);

/**
 * thermal_zone_unbind_cooling_device() - unbind a cooling device from a
 *					  thermal zone.
 * @tz:		poपूर्णांकer to a काष्ठा thermal_zone_device.
 * @trip:	indicates which trip poपूर्णांक the cooling devices is
 *		associated with in this thermal zone.
 * @cdev:	poपूर्णांकer to a काष्ठा thermal_cooling_device.
 *
 * This पूर्णांकerface function unbind a thermal cooling device from the certain
 * trip poपूर्णांक of a thermal zone device.
 * This function is usually called in the thermal zone device .unbind callback.
 *
 * Return: 0 on success, the proper error value otherwise.
 */
पूर्णांक thermal_zone_unbind_cooling_device(काष्ठा thermal_zone_device *tz,
				       पूर्णांक trip,
				       काष्ठा thermal_cooling_device *cdev)
अणु
	काष्ठा thermal_instance *pos, *next;

	mutex_lock(&tz->lock);
	mutex_lock(&cdev->lock);
	list_क्रम_each_entry_safe(pos, next, &tz->thermal_instances, tz_node) अणु
		अगर (pos->tz == tz && pos->trip == trip && pos->cdev == cdev) अणु
			list_del(&pos->tz_node);
			list_del(&pos->cdev_node);
			mutex_unlock(&cdev->lock);
			mutex_unlock(&tz->lock);
			जाओ unbind;
		पूर्ण
	पूर्ण
	mutex_unlock(&cdev->lock);
	mutex_unlock(&tz->lock);

	वापस -ENODEV;

unbind:
	device_हटाओ_file(&tz->device, &pos->weight_attr);
	device_हटाओ_file(&tz->device, &pos->attr);
	sysfs_हटाओ_link(&tz->device.kobj, pos->name);
	ida_simple_हटाओ(&tz->ida, pos->id);
	kमुक्त(pos);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(thermal_zone_unbind_cooling_device);

अटल व्योम thermal_release(काष्ठा device *dev)
अणु
	काष्ठा thermal_zone_device *tz;
	काष्ठा thermal_cooling_device *cdev;

	अगर (!म_भेदन(dev_name(dev), "thermal_zone",
		     माप("thermal_zone") - 1)) अणु
		tz = to_thermal_zone(dev);
		thermal_zone_destroy_device_groups(tz);
		kमुक्त(tz);
	पूर्ण अन्यथा अगर (!म_भेदन(dev_name(dev), "cooling_device",
			    माप("cooling_device") - 1)) अणु
		cdev = to_cooling_device(dev);
		kमुक्त(cdev);
	पूर्ण
पूर्ण

अटल काष्ठा class thermal_class = अणु
	.name = "thermal",
	.dev_release = thermal_release,
पूर्ण;

अटल अंतरभूत
व्योम prपूर्णांक_bind_err_msg(काष्ठा thermal_zone_device *tz,
			काष्ठा thermal_cooling_device *cdev, पूर्णांक ret)
अणु
	dev_err(&tz->device, "binding zone %s with cdev %s failed:%d\n",
		tz->type, cdev->type, ret);
पूर्ण

अटल व्योम __bind(काष्ठा thermal_zone_device *tz, पूर्णांक mask,
		   काष्ठा thermal_cooling_device *cdev,
		   अचिन्हित दीर्घ *limits,
		   अचिन्हित पूर्णांक weight)
अणु
	पूर्णांक i, ret;

	क्रम (i = 0; i < tz->trips; i++) अणु
		अगर (mask & (1 << i)) अणु
			अचिन्हित दीर्घ upper, lower;

			upper = THERMAL_NO_LIMIT;
			lower = THERMAL_NO_LIMIT;
			अगर (limits) अणु
				lower = limits[i * 2];
				upper = limits[i * 2 + 1];
			पूर्ण
			ret = thermal_zone_bind_cooling_device(tz, i, cdev,
							       upper, lower,
							       weight);
			अगर (ret)
				prपूर्णांक_bind_err_msg(tz, cdev, ret);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bind_cdev(काष्ठा thermal_cooling_device *cdev)
अणु
	पूर्णांक i, ret;
	स्थिर काष्ठा thermal_zone_params *tzp;
	काष्ठा thermal_zone_device *pos = शून्य;

	mutex_lock(&thermal_list_lock);

	list_क्रम_each_entry(pos, &thermal_tz_list, node) अणु
		अगर (!pos->tzp && !pos->ops->bind)
			जारी;

		अगर (pos->ops->bind) अणु
			ret = pos->ops->bind(pos, cdev);
			अगर (ret)
				prपूर्णांक_bind_err_msg(pos, cdev, ret);
			जारी;
		पूर्ण

		tzp = pos->tzp;
		अगर (!tzp || !tzp->tbp)
			जारी;

		क्रम (i = 0; i < tzp->num_tbps; i++) अणु
			अगर (tzp->tbp[i].cdev || !tzp->tbp[i].match)
				जारी;
			अगर (tzp->tbp[i].match(pos, cdev))
				जारी;
			tzp->tbp[i].cdev = cdev;
			__bind(pos, tzp->tbp[i].trip_mask, cdev,
			       tzp->tbp[i].binding_limits,
			       tzp->tbp[i].weight);
		पूर्ण
	पूर्ण

	mutex_unlock(&thermal_list_lock);
पूर्ण

/**
 * __thermal_cooling_device_रेजिस्टर() - रेजिस्टर a new thermal cooling device
 * @np:		a poपूर्णांकer to a device tree node.
 * @type:	the thermal cooling device type.
 * @devdata:	device निजी data.
 * @ops:		standard thermal cooling devices callbacks.
 *
 * This पूर्णांकerface function adds a new thermal cooling device (fan/processor/...)
 * to /sys/class/thermal/ folder as cooling_device[0-*]. It tries to bind itself
 * to all the thermal zone devices रेजिस्टरed at the same समय.
 * It also gives the opportunity to link the cooling device to a device tree
 * node, so that it can be bound to a thermal zone created out of device tree.
 *
 * Return: a poपूर्णांकer to the created काष्ठा thermal_cooling_device or an
 * ERR_PTR. Caller must check वापस value with IS_ERR*() helpers.
 */
अटल काष्ठा thermal_cooling_device *
__thermal_cooling_device_रेजिस्टर(काष्ठा device_node *np,
				  स्थिर अक्षर *type, व्योम *devdata,
				  स्थिर काष्ठा thermal_cooling_device_ops *ops)
अणु
	काष्ठा thermal_cooling_device *cdev;
	काष्ठा thermal_zone_device *pos = शून्य;
	पूर्णांक ret;

	अगर (!ops || !ops->get_max_state || !ops->get_cur_state ||
	    !ops->set_cur_state)
		वापस ERR_PTR(-EINVAL);

	cdev = kzalloc(माप(*cdev), GFP_KERNEL);
	अगर (!cdev)
		वापस ERR_PTR(-ENOMEM);

	ret = ida_simple_get(&thermal_cdev_ida, 0, 0, GFP_KERNEL);
	अगर (ret < 0)
		जाओ out_kमुक्त_cdev;
	cdev->id = ret;

	cdev->type = kstrdup(type ? type : "", GFP_KERNEL);
	अगर (!cdev->type) अणु
		ret = -ENOMEM;
		जाओ out_ida_हटाओ;
	पूर्ण

	mutex_init(&cdev->lock);
	INIT_LIST_HEAD(&cdev->thermal_instances);
	cdev->np = np;
	cdev->ops = ops;
	cdev->updated = false;
	cdev->device.class = &thermal_class;
	cdev->devdata = devdata;
	thermal_cooling_device_setup_sysfs(cdev);
	dev_set_name(&cdev->device, "cooling_device%d", cdev->id);
	ret = device_रेजिस्टर(&cdev->device);
	अगर (ret)
		जाओ out_kमुक्त_type;

	/* Add 'this' new cdev to the global cdev list */
	mutex_lock(&thermal_list_lock);
	list_add(&cdev->node, &thermal_cdev_list);
	mutex_unlock(&thermal_list_lock);

	/* Update binding inक्रमmation क्रम 'this' new cdev */
	bind_cdev(cdev);

	mutex_lock(&thermal_list_lock);
	list_क्रम_each_entry(pos, &thermal_tz_list, node)
		अगर (atomic_cmpxchg(&pos->need_update, 1, 0))
			thermal_zone_device_update(pos,
						   THERMAL_EVENT_UNSPECIFIED);
	mutex_unlock(&thermal_list_lock);

	वापस cdev;

out_kमुक्त_type:
	kमुक्त(cdev->type);
	put_device(&cdev->device);
out_ida_हटाओ:
	ida_simple_हटाओ(&thermal_cdev_ida, cdev->id);
out_kमुक्त_cdev:
	kमुक्त(cdev);
	वापस ERR_PTR(ret);
पूर्ण

/**
 * thermal_cooling_device_रेजिस्टर() - रेजिस्टर a new thermal cooling device
 * @type:	the thermal cooling device type.
 * @devdata:	device निजी data.
 * @ops:		standard thermal cooling devices callbacks.
 *
 * This पूर्णांकerface function adds a new thermal cooling device (fan/processor/...)
 * to /sys/class/thermal/ folder as cooling_device[0-*]. It tries to bind itself
 * to all the thermal zone devices रेजिस्टरed at the same समय.
 *
 * Return: a poपूर्णांकer to the created काष्ठा thermal_cooling_device or an
 * ERR_PTR. Caller must check वापस value with IS_ERR*() helpers.
 */
काष्ठा thermal_cooling_device *
thermal_cooling_device_रेजिस्टर(स्थिर अक्षर *type, व्योम *devdata,
				स्थिर काष्ठा thermal_cooling_device_ops *ops)
अणु
	वापस __thermal_cooling_device_रेजिस्टर(शून्य, type, devdata, ops);
पूर्ण
EXPORT_SYMBOL_GPL(thermal_cooling_device_रेजिस्टर);

/**
 * thermal_of_cooling_device_रेजिस्टर() - रेजिस्टर an OF thermal cooling device
 * @np:		a poपूर्णांकer to a device tree node.
 * @type:	the thermal cooling device type.
 * @devdata:	device निजी data.
 * @ops:		standard thermal cooling devices callbacks.
 *
 * This function will रेजिस्टर a cooling device with device tree node reference.
 * This पूर्णांकerface function adds a new thermal cooling device (fan/processor/...)
 * to /sys/class/thermal/ folder as cooling_device[0-*]. It tries to bind itself
 * to all the thermal zone devices रेजिस्टरed at the same समय.
 *
 * Return: a poपूर्णांकer to the created काष्ठा thermal_cooling_device or an
 * ERR_PTR. Caller must check वापस value with IS_ERR*() helpers.
 */
काष्ठा thermal_cooling_device *
thermal_of_cooling_device_रेजिस्टर(काष्ठा device_node *np,
				   स्थिर अक्षर *type, व्योम *devdata,
				   स्थिर काष्ठा thermal_cooling_device_ops *ops)
अणु
	वापस __thermal_cooling_device_रेजिस्टर(np, type, devdata, ops);
पूर्ण
EXPORT_SYMBOL_GPL(thermal_of_cooling_device_रेजिस्टर);

अटल व्योम thermal_cooling_device_release(काष्ठा device *dev, व्योम *res)
अणु
	thermal_cooling_device_unरेजिस्टर(
				*(काष्ठा thermal_cooling_device **)res);
पूर्ण

/**
 * devm_thermal_of_cooling_device_रेजिस्टर() - रेजिस्टर an OF thermal cooling
 *					       device
 * @dev:	a valid काष्ठा device poपूर्णांकer of a sensor device.
 * @np:		a poपूर्णांकer to a device tree node.
 * @type:	the thermal cooling device type.
 * @devdata:	device निजी data.
 * @ops:	standard thermal cooling devices callbacks.
 *
 * This function will रेजिस्टर a cooling device with device tree node reference.
 * This पूर्णांकerface function adds a new thermal cooling device (fan/processor/...)
 * to /sys/class/thermal/ folder as cooling_device[0-*]. It tries to bind itself
 * to all the thermal zone devices रेजिस्टरed at the same समय.
 *
 * Return: a poपूर्णांकer to the created काष्ठा thermal_cooling_device or an
 * ERR_PTR. Caller must check वापस value with IS_ERR*() helpers.
 */
काष्ठा thermal_cooling_device *
devm_thermal_of_cooling_device_रेजिस्टर(काष्ठा device *dev,
				काष्ठा device_node *np,
				अक्षर *type, व्योम *devdata,
				स्थिर काष्ठा thermal_cooling_device_ops *ops)
अणु
	काष्ठा thermal_cooling_device **ptr, *tcd;

	ptr = devres_alloc(thermal_cooling_device_release, माप(*ptr),
			   GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	tcd = __thermal_cooling_device_रेजिस्टर(np, type, devdata, ops);
	अगर (IS_ERR(tcd)) अणु
		devres_मुक्त(ptr);
		वापस tcd;
	पूर्ण

	*ptr = tcd;
	devres_add(dev, ptr);

	वापस tcd;
पूर्ण
EXPORT_SYMBOL_GPL(devm_thermal_of_cooling_device_रेजिस्टर);

अटल व्योम __unbind(काष्ठा thermal_zone_device *tz, पूर्णांक mask,
		     काष्ठा thermal_cooling_device *cdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < tz->trips; i++)
		अगर (mask & (1 << i))
			thermal_zone_unbind_cooling_device(tz, i, cdev);
पूर्ण

/**
 * thermal_cooling_device_unरेजिस्टर - हटाओs a thermal cooling device
 * @cdev:	the thermal cooling device to हटाओ.
 *
 * thermal_cooling_device_unरेजिस्टर() must be called when a रेजिस्टरed
 * thermal cooling device is no दीर्घer needed.
 */
व्योम thermal_cooling_device_unरेजिस्टर(काष्ठा thermal_cooling_device *cdev)
अणु
	पूर्णांक i;
	स्थिर काष्ठा thermal_zone_params *tzp;
	काष्ठा thermal_zone_device *tz;
	काष्ठा thermal_cooling_device *pos = शून्य;

	अगर (!cdev)
		वापस;

	mutex_lock(&thermal_list_lock);
	list_क्रम_each_entry(pos, &thermal_cdev_list, node)
		अगर (pos == cdev)
			अवरोध;
	अगर (pos != cdev) अणु
		/* thermal cooling device not found */
		mutex_unlock(&thermal_list_lock);
		वापस;
	पूर्ण
	list_del(&cdev->node);

	/* Unbind all thermal zones associated with 'this' cdev */
	list_क्रम_each_entry(tz, &thermal_tz_list, node) अणु
		अगर (tz->ops->unbind) अणु
			tz->ops->unbind(tz, cdev);
			जारी;
		पूर्ण

		अगर (!tz->tzp || !tz->tzp->tbp)
			जारी;

		tzp = tz->tzp;
		क्रम (i = 0; i < tzp->num_tbps; i++) अणु
			अगर (tzp->tbp[i].cdev == cdev) अणु
				__unbind(tz, tzp->tbp[i].trip_mask, cdev);
				tzp->tbp[i].cdev = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&thermal_list_lock);

	ida_simple_हटाओ(&thermal_cdev_ida, cdev->id);
	device_del(&cdev->device);
	thermal_cooling_device_destroy_sysfs(cdev);
	kमुक्त(cdev->type);
	put_device(&cdev->device);
पूर्ण
EXPORT_SYMBOL_GPL(thermal_cooling_device_unरेजिस्टर);

अटल व्योम bind_tz(काष्ठा thermal_zone_device *tz)
अणु
	पूर्णांक i, ret;
	काष्ठा thermal_cooling_device *pos = शून्य;
	स्थिर काष्ठा thermal_zone_params *tzp = tz->tzp;

	अगर (!tzp && !tz->ops->bind)
		वापस;

	mutex_lock(&thermal_list_lock);

	/* If there is ops->bind, try to use ops->bind */
	अगर (tz->ops->bind) अणु
		list_क्रम_each_entry(pos, &thermal_cdev_list, node) अणु
			ret = tz->ops->bind(tz, pos);
			अगर (ret)
				prपूर्णांक_bind_err_msg(tz, pos, ret);
		पूर्ण
		जाओ निकास;
	पूर्ण

	अगर (!tzp || !tzp->tbp)
		जाओ निकास;

	list_क्रम_each_entry(pos, &thermal_cdev_list, node) अणु
		क्रम (i = 0; i < tzp->num_tbps; i++) अणु
			अगर (tzp->tbp[i].cdev || !tzp->tbp[i].match)
				जारी;
			अगर (tzp->tbp[i].match(tz, pos))
				जारी;
			tzp->tbp[i].cdev = pos;
			__bind(tz, tzp->tbp[i].trip_mask, pos,
			       tzp->tbp[i].binding_limits,
			       tzp->tbp[i].weight);
		पूर्ण
	पूर्ण
निकास:
	mutex_unlock(&thermal_list_lock);
पूर्ण

/**
 * thermal_zone_device_रेजिस्टर() - रेजिस्टर a new thermal zone device
 * @type:	the thermal zone device type
 * @trips:	the number of trip poपूर्णांकs the thermal zone support
 * @mask:	a bit string indicating the ग_लिखोablility of trip poपूर्णांकs
 * @devdata:	निजी device data
 * @ops:	standard thermal zone device callbacks
 * @tzp:	thermal zone platक्रमm parameters
 * @passive_delay: number of milliseconds to रुको between polls when
 *		   perक्रमming passive cooling
 * @polling_delay: number of milliseconds to रुको between polls when checking
 *		   whether trip poपूर्णांकs have been crossed (0 क्रम पूर्णांकerrupt
 *		   driven प्रणालीs)
 *
 * This पूर्णांकerface function adds a new thermal zone device (sensor) to
 * /sys/class/thermal folder as thermal_zone[0-*]. It tries to bind all the
 * thermal cooling devices रेजिस्टरed at the same समय.
 * thermal_zone_device_unरेजिस्टर() must be called when the device is no
 * दीर्घer needed. The passive cooling depends on the .get_trend() वापस value.
 *
 * Return: a poपूर्णांकer to the created काष्ठा thermal_zone_device or an
 * in हाल of error, an ERR_PTR. Caller must check वापस value with
 * IS_ERR*() helpers.
 */
काष्ठा thermal_zone_device *
thermal_zone_device_रेजिस्टर(स्थिर अक्षर *type, पूर्णांक trips, पूर्णांक mask,
			     व्योम *devdata, काष्ठा thermal_zone_device_ops *ops,
			     काष्ठा thermal_zone_params *tzp, पूर्णांक passive_delay,
			     पूर्णांक polling_delay)
अणु
	काष्ठा thermal_zone_device *tz;
	क्रमागत thermal_trip_type trip_type;
	पूर्णांक trip_temp;
	पूर्णांक id;
	पूर्णांक result;
	पूर्णांक count;
	काष्ठा thermal_governor *governor;

	अगर (!type || म_माप(type) == 0) अणु
		pr_err("Error: No thermal zone type defined\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (type && म_माप(type) >= THERMAL_NAME_LENGTH) अणु
		pr_err("Error: Thermal zone name (%s) too long, should be under %d chars\n",
		       type, THERMAL_NAME_LENGTH);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (trips > THERMAL_MAX_TRIPS || trips < 0 || mask >> trips) अणु
		pr_err("Error: Incorrect number of thermal trips\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (!ops) अणु
		pr_err("Error: Thermal zone device ops not defined\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	अगर (trips > 0 && (!ops->get_trip_type || !ops->get_trip_temp))
		वापस ERR_PTR(-EINVAL);

	tz = kzalloc(माप(*tz), GFP_KERNEL);
	अगर (!tz)
		वापस ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&tz->thermal_instances);
	ida_init(&tz->ida);
	mutex_init(&tz->lock);
	id = ida_simple_get(&thermal_tz_ida, 0, 0, GFP_KERNEL);
	अगर (id < 0) अणु
		result = id;
		जाओ मुक्त_tz;
	पूर्ण

	tz->id = id;
	strlcpy(tz->type, type, माप(tz->type));

	अगर (!ops->critical)
		ops->critical = thermal_zone_device_critical;

	tz->ops = ops;
	tz->tzp = tzp;
	tz->device.class = &thermal_class;
	tz->devdata = devdata;
	tz->trips = trips;

	thermal_set_delay_jअगरfies(&tz->passive_delay_jअगरfies, passive_delay);
	thermal_set_delay_jअगरfies(&tz->polling_delay_jअगरfies, polling_delay);

	/* sys I/F */
	/* Add nodes that are always present via .groups */
	result = thermal_zone_create_device_groups(tz, mask);
	अगर (result)
		जाओ हटाओ_id;

	/* A new thermal zone needs to be updated anyway. */
	atomic_set(&tz->need_update, 1);

	dev_set_name(&tz->device, "thermal_zone%d", tz->id);
	result = device_रेजिस्टर(&tz->device);
	अगर (result)
		जाओ release_device;

	क्रम (count = 0; count < trips; count++) अणु
		अगर (tz->ops->get_trip_type(tz, count, &trip_type) ||
		    tz->ops->get_trip_temp(tz, count, &trip_temp) ||
		    !trip_temp)
			set_bit(count, &tz->trips_disabled);
	पूर्ण

	/* Update 'this' zone's governor inक्रमmation */
	mutex_lock(&thermal_governor_lock);

	अगर (tz->tzp)
		governor = __find_governor(tz->tzp->governor_name);
	अन्यथा
		governor = def_governor;

	result = thermal_set_governor(tz, governor);
	अगर (result) अणु
		mutex_unlock(&thermal_governor_lock);
		जाओ unरेजिस्टर;
	पूर्ण

	mutex_unlock(&thermal_governor_lock);

	अगर (!tz->tzp || !tz->tzp->no_hwmon) अणु
		result = thermal_add_hwmon_sysfs(tz);
		अगर (result)
			जाओ unरेजिस्टर;
	पूर्ण

	mutex_lock(&thermal_list_lock);
	list_add_tail(&tz->node, &thermal_tz_list);
	mutex_unlock(&thermal_list_lock);

	/* Bind cooling devices क्रम this zone */
	bind_tz(tz);

	INIT_DELAYED_WORK(&tz->poll_queue, thermal_zone_device_check);

	thermal_zone_device_init(tz);
	/* Update the new thermal zone and mark it as alपढ़ोy updated. */
	अगर (atomic_cmpxchg(&tz->need_update, 1, 0))
		thermal_zone_device_update(tz, THERMAL_EVENT_UNSPECIFIED);

	thermal_notअगरy_tz_create(tz->id, tz->type);

	वापस tz;

unरेजिस्टर:
	device_del(&tz->device);
release_device:
	put_device(&tz->device);
	tz = शून्य;
हटाओ_id:
	ida_simple_हटाओ(&thermal_tz_ida, id);
मुक्त_tz:
	kमुक्त(tz);
	वापस ERR_PTR(result);
पूर्ण
EXPORT_SYMBOL_GPL(thermal_zone_device_रेजिस्टर);

/**
 * thermal_device_unरेजिस्टर - हटाओs the रेजिस्टरed thermal zone device
 * @tz: the thermal zone device to हटाओ
 */
व्योम thermal_zone_device_unरेजिस्टर(काष्ठा thermal_zone_device *tz)
अणु
	पूर्णांक i, tz_id;
	स्थिर काष्ठा thermal_zone_params *tzp;
	काष्ठा thermal_cooling_device *cdev;
	काष्ठा thermal_zone_device *pos = शून्य;

	अगर (!tz)
		वापस;

	tzp = tz->tzp;
	tz_id = tz->id;

	mutex_lock(&thermal_list_lock);
	list_क्रम_each_entry(pos, &thermal_tz_list, node)
		अगर (pos == tz)
			अवरोध;
	अगर (pos != tz) अणु
		/* thermal zone device not found */
		mutex_unlock(&thermal_list_lock);
		वापस;
	पूर्ण
	list_del(&tz->node);

	/* Unbind all cdevs associated with 'this' thermal zone */
	list_क्रम_each_entry(cdev, &thermal_cdev_list, node) अणु
		अगर (tz->ops->unbind) अणु
			tz->ops->unbind(tz, cdev);
			जारी;
		पूर्ण

		अगर (!tzp || !tzp->tbp)
			अवरोध;

		क्रम (i = 0; i < tzp->num_tbps; i++) अणु
			अगर (tzp->tbp[i].cdev == cdev) अणु
				__unbind(tz, tzp->tbp[i].trip_mask, cdev);
				tzp->tbp[i].cdev = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	mutex_unlock(&thermal_list_lock);

	cancel_delayed_work_sync(&tz->poll_queue);

	thermal_set_governor(tz, शून्य);

	thermal_हटाओ_hwmon_sysfs(tz);
	ida_simple_हटाओ(&thermal_tz_ida, tz->id);
	ida_destroy(&tz->ida);
	mutex_destroy(&tz->lock);
	device_unरेजिस्टर(&tz->device);

	thermal_notअगरy_tz_delete(tz_id);
पूर्ण
EXPORT_SYMBOL_GPL(thermal_zone_device_unरेजिस्टर);

/**
 * thermal_zone_get_zone_by_name() - search क्रम a zone and वापसs its ref
 * @name: thermal zone name to fetch the temperature
 *
 * When only one zone is found with the passed name, वापसs a reference to it.
 *
 * Return: On success वापसs a reference to an unique thermal zone with
 * matching name equals to @name, an ERR_PTR otherwise (-EINVAL क्रम invalid
 * paramenters, -ENODEV क्रम not found and -EEXIST क्रम multiple matches).
 */
काष्ठा thermal_zone_device *thermal_zone_get_zone_by_name(स्थिर अक्षर *name)
अणु
	काष्ठा thermal_zone_device *pos = शून्य, *ref = ERR_PTR(-EINVAL);
	अचिन्हित पूर्णांक found = 0;

	अगर (!name)
		जाओ निकास;

	mutex_lock(&thermal_list_lock);
	list_क्रम_each_entry(pos, &thermal_tz_list, node)
		अगर (!strnहालcmp(name, pos->type, THERMAL_NAME_LENGTH)) अणु
			found++;
			ref = pos;
		पूर्ण
	mutex_unlock(&thermal_list_lock);

	/* nothing has been found, thus an error code क्रम it */
	अगर (found == 0)
		ref = ERR_PTR(-ENODEV);
	अन्यथा अगर (found > 1)
	/* Success only when an unique zone is found */
		ref = ERR_PTR(-EEXIST);

निकास:
	वापस ref;
पूर्ण
EXPORT_SYMBOL_GPL(thermal_zone_get_zone_by_name);

अटल पूर्णांक thermal_pm_notअगरy(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ mode, व्योम *_unused)
अणु
	काष्ठा thermal_zone_device *tz;

	चयन (mode) अणु
	हाल PM_HIBERNATION_PREPARE:
	हाल PM_RESTORE_PREPARE:
	हाल PM_SUSPEND_PREPARE:
		atomic_set(&in_suspend, 1);
		अवरोध;
	हाल PM_POST_HIBERNATION:
	हाल PM_POST_RESTORE:
	हाल PM_POST_SUSPEND:
		atomic_set(&in_suspend, 0);
		list_क्रम_each_entry(tz, &thermal_tz_list, node) अणु
			अगर (!thermal_zone_device_is_enabled(tz))
				जारी;

			thermal_zone_device_init(tz);
			thermal_zone_device_update(tz,
						   THERMAL_EVENT_UNSPECIFIED);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block thermal_pm_nb = अणु
	.notअगरier_call = thermal_pm_notअगरy,
पूर्ण;

अटल पूर्णांक __init thermal_init(व्योम)
अणु
	पूर्णांक result;

	result = thermal_netlink_init();
	अगर (result)
		जाओ error;

	result = thermal_रेजिस्टर_governors();
	अगर (result)
		जाओ error;

	result = class_रेजिस्टर(&thermal_class);
	अगर (result)
		जाओ unरेजिस्टर_governors;

	result = of_parse_thermal_zones();
	अगर (result)
		जाओ unरेजिस्टर_class;

	result = रेजिस्टर_pm_notअगरier(&thermal_pm_nb);
	अगर (result)
		pr_warn("Thermal: Can not register suspend notifier, return %d\n",
			result);

	वापस 0;

unरेजिस्टर_class:
	class_unरेजिस्टर(&thermal_class);
unरेजिस्टर_governors:
	thermal_unरेजिस्टर_governors();
error:
	ida_destroy(&thermal_tz_ida);
	ida_destroy(&thermal_cdev_ida);
	mutex_destroy(&thermal_list_lock);
	mutex_destroy(&thermal_governor_lock);
	mutex_destroy(&घातeroff_lock);
	वापस result;
पूर्ण
postcore_initcall(thermal_init);
