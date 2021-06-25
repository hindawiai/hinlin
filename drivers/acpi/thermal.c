<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  acpi_thermal.c - ACPI Thermal Zone Driver ($Revision: 41 $)
 *
 *  Copyright (C) 2001, 2002 Andy Grover <andrew.grover@पूर्णांकel.com>
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 *
 *  This driver fully implements the ACPI thermal policy as described in the
 *  ACPI 2.0 Specअगरication.
 *
 *  TBD: 1. Implement passive cooling hysteresis.
 *       2. Enhance passive cooling (CPU) states/limit पूर्णांकerface to support
 *          concepts of 'multiple limiters', upper/lower limits, etc.
 */

#घोषणा pr_fmt(fmt) "ACPI: thermal: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/dmi.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kmod.h>
#समावेश <linux/reboot.h>
#समावेश <linux/device.h>
#समावेश <linux/thermal.h>
#समावेश <linux/acpi.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/units.h>

#घोषणा ACPI_THERMAL_CLASS		"thermal_zone"
#घोषणा ACPI_THERMAL_DEVICE_NAME	"Thermal Zone"
#घोषणा ACPI_THERMAL_NOTIFY_TEMPERATURE	0x80
#घोषणा ACPI_THERMAL_NOTIFY_THRESHOLDS	0x81
#घोषणा ACPI_THERMAL_NOTIFY_DEVICES	0x82
#घोषणा ACPI_THERMAL_NOTIFY_CRITICAL	0xF0
#घोषणा ACPI_THERMAL_NOTIFY_HOT		0xF1
#घोषणा ACPI_THERMAL_MODE_ACTIVE	0x00

#घोषणा ACPI_THERMAL_MAX_ACTIVE	10
#घोषणा ACPI_THERMAL_MAX_LIMIT_STR_LEN 65

MODULE_AUTHOR("Paul Diefenbaugh");
MODULE_DESCRIPTION("ACPI Thermal Zone Driver");
MODULE_LICENSE("GPL");

अटल पूर्णांक act;
module_param(act, पूर्णांक, 0644);
MODULE_PARM_DESC(act, "Disable or override all lowest active trip points.");

अटल पूर्णांक crt;
module_param(crt, पूर्णांक, 0644);
MODULE_PARM_DESC(crt, "Disable or lower all critical trip points.");

अटल पूर्णांक tzp;
module_param(tzp, पूर्णांक, 0444);
MODULE_PARM_DESC(tzp, "Thermal zone polling frequency, in 1/10 seconds.");

अटल पूर्णांक nocrt;
module_param(nocrt, पूर्णांक, 0);
MODULE_PARM_DESC(nocrt, "Set to take no action upon ACPI thermal zone critical trips points.");

अटल पूर्णांक off;
module_param(off, पूर्णांक, 0);
MODULE_PARM_DESC(off, "Set to disable ACPI thermal support.");

अटल पूर्णांक psv;
module_param(psv, पूर्णांक, 0644);
MODULE_PARM_DESC(psv, "Disable or override all passive trip points.");

अटल काष्ठा workqueue_काष्ठा *acpi_thermal_pm_queue;

अटल पूर्णांक acpi_thermal_add(काष्ठा acpi_device *device);
अटल पूर्णांक acpi_thermal_हटाओ(काष्ठा acpi_device *device);
अटल व्योम acpi_thermal_notअगरy(काष्ठा acpi_device *device, u32 event);

अटल स्थिर काष्ठा acpi_device_id  thermal_device_ids[] = अणु
	अणुACPI_THERMAL_HID, 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, thermal_device_ids);

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक acpi_thermal_suspend(काष्ठा device *dev);
अटल पूर्णांक acpi_thermal_resume(काष्ठा device *dev);
#अन्यथा
#घोषणा acpi_thermal_suspend शून्य
#घोषणा acpi_thermal_resume शून्य
#पूर्ण_अगर
अटल SIMPLE_DEV_PM_OPS(acpi_thermal_pm, acpi_thermal_suspend, acpi_thermal_resume);

अटल काष्ठा acpi_driver acpi_thermal_driver = अणु
	.name = "thermal",
	.class = ACPI_THERMAL_CLASS,
	.ids = thermal_device_ids,
	.ops = अणु
		.add = acpi_thermal_add,
		.हटाओ = acpi_thermal_हटाओ,
		.notअगरy = acpi_thermal_notअगरy,
		पूर्ण,
	.drv.pm = &acpi_thermal_pm,
पूर्ण;

काष्ठा acpi_thermal_state अणु
	u8 critical:1;
	u8 hot:1;
	u8 passive:1;
	u8 active:1;
	u8 reserved:4;
	पूर्णांक active_index;
पूर्ण;

काष्ठा acpi_thermal_state_flags अणु
	u8 valid:1;
	u8 enabled:1;
	u8 reserved:6;
पूर्ण;

काष्ठा acpi_thermal_critical अणु
	काष्ठा acpi_thermal_state_flags flags;
	अचिन्हित दीर्घ temperature;
पूर्ण;

काष्ठा acpi_thermal_hot अणु
	काष्ठा acpi_thermal_state_flags flags;
	अचिन्हित दीर्घ temperature;
पूर्ण;

काष्ठा acpi_thermal_passive अणु
	काष्ठा acpi_thermal_state_flags flags;
	अचिन्हित दीर्घ temperature;
	अचिन्हित दीर्घ tc1;
	अचिन्हित दीर्घ tc2;
	अचिन्हित दीर्घ tsp;
	काष्ठा acpi_handle_list devices;
पूर्ण;

काष्ठा acpi_thermal_active अणु
	काष्ठा acpi_thermal_state_flags flags;
	अचिन्हित दीर्घ temperature;
	काष्ठा acpi_handle_list devices;
पूर्ण;

काष्ठा acpi_thermal_trips अणु
	काष्ठा acpi_thermal_critical critical;
	काष्ठा acpi_thermal_hot hot;
	काष्ठा acpi_thermal_passive passive;
	काष्ठा acpi_thermal_active active[ACPI_THERMAL_MAX_ACTIVE];
पूर्ण;

काष्ठा acpi_thermal_flags अणु
	u8 cooling_mode:1;	/* _SCP */
	u8 devices:1;		/* _TZD */
	u8 reserved:6;
पूर्ण;

काष्ठा acpi_thermal अणु
	काष्ठा acpi_device * device;
	acpi_bus_id name;
	अचिन्हित दीर्घ temperature;
	अचिन्हित दीर्घ last_temperature;
	अचिन्हित दीर्घ polling_frequency;
	अस्थिर u8 zombie;
	काष्ठा acpi_thermal_flags flags;
	काष्ठा acpi_thermal_state state;
	काष्ठा acpi_thermal_trips trips;
	काष्ठा acpi_handle_list devices;
	काष्ठा thermal_zone_device *thermal_zone;
	पूर्णांक kelvin_offset;	/* in millidegrees */
	काष्ठा work_काष्ठा thermal_check_work;
	काष्ठा mutex thermal_check_lock;
	refcount_t thermal_check_count;
पूर्ण;

/* --------------------------------------------------------------------------
                             Thermal Zone Management
   -------------------------------------------------------------------------- */

अटल पूर्णांक acpi_thermal_get_temperature(काष्ठा acpi_thermal *tz)
अणु
	acpi_status status = AE_OK;
	अचिन्हित दीर्घ दीर्घ पंचांगp;

	अगर (!tz)
		वापस -EINVAL;

	tz->last_temperature = tz->temperature;

	status = acpi_evaluate_पूर्णांकeger(tz->device->handle, "_TMP", शून्य, &पंचांगp);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	tz->temperature = पंचांगp;

	acpi_handle_debug(tz->device->handle, "Temperature is %lu dK\n",
			  tz->temperature);

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_thermal_get_polling_frequency(काष्ठा acpi_thermal *tz)
अणु
	acpi_status status = AE_OK;
	अचिन्हित दीर्घ दीर्घ पंचांगp;

	अगर (!tz)
		वापस -EINVAL;

	status = acpi_evaluate_पूर्णांकeger(tz->device->handle, "_TZP", शून्य, &पंचांगp);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	tz->polling_frequency = पंचांगp;
	acpi_handle_debug(tz->device->handle, "Polling frequency is %lu dS\n",
			  tz->polling_frequency);

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_thermal_set_cooling_mode(काष्ठा acpi_thermal *tz, पूर्णांक mode)
अणु
	अगर (!tz)
		वापस -EINVAL;

	अगर (ACPI_FAILURE(acpi_execute_simple_method(tz->device->handle,
						    "_SCP", mode)))
		वापस -ENODEV;

	वापस 0;
पूर्ण

#घोषणा ACPI_TRIPS_CRITICAL	0x01
#घोषणा ACPI_TRIPS_HOT		0x02
#घोषणा ACPI_TRIPS_PASSIVE	0x04
#घोषणा ACPI_TRIPS_ACTIVE	0x08
#घोषणा ACPI_TRIPS_DEVICES	0x10

#घोषणा ACPI_TRIPS_REFRESH_THRESHOLDS	(ACPI_TRIPS_PASSIVE | ACPI_TRIPS_ACTIVE)
#घोषणा ACPI_TRIPS_REFRESH_DEVICES	ACPI_TRIPS_DEVICES

#घोषणा ACPI_TRIPS_INIT      (ACPI_TRIPS_CRITICAL | ACPI_TRIPS_HOT |	\
			      ACPI_TRIPS_PASSIVE | ACPI_TRIPS_ACTIVE |	\
			      ACPI_TRIPS_DEVICES)

/*
 * This exception is thrown out in two हालs:
 * 1.An invalid trip poपूर्णांक becomes invalid or a valid trip poपूर्णांक becomes invalid
 *   when re-evaluating the AML code.
 * 2.TODO: Devices listed in _PSL, _ALx, _TZD may change.
 *   We need to re-bind the cooling devices of a thermal zone when this occurs.
 */
#घोषणा ACPI_THERMAL_TRIPS_EXCEPTION(flags, tz, str)	\
करो अणु	\
	अगर (flags != ACPI_TRIPS_INIT)	\
		acpi_handle_info(tz->device->handle,	\
		"ACPI thermal trip point %s changed\n"	\
		"Please report to linux-acpi@vger.kernel.org\n", str); \
पूर्ण जबतक (0)

अटल पूर्णांक acpi_thermal_trips_update(काष्ठा acpi_thermal *tz, पूर्णांक flag)
अणु
	acpi_status status = AE_OK;
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	काष्ठा acpi_handle_list devices;
	पूर्णांक valid = 0;
	पूर्णांक i;

	/* Critical Shutकरोwn */
	अगर (flag & ACPI_TRIPS_CRITICAL) अणु
		status = acpi_evaluate_पूर्णांकeger(tz->device->handle,
				"_CRT", शून्य, &पंचांगp);
		tz->trips.critical.temperature = पंचांगp;
		/*
		 * Treat मुक्तzing temperatures as invalid as well; some
		 * BIOSes वापस really low values and cause reboots at startup.
		 * Below zero (Celsius) values clearly aren't right क्रम sure..
		 * ... so lets discard those as invalid.
		 */
		अगर (ACPI_FAILURE(status)) अणु
			tz->trips.critical.flags.valid = 0;
			acpi_handle_debug(tz->device->handle,
					  "No critical threshold\n");
		पूर्ण अन्यथा अगर (पंचांगp <= 2732) अणु
			pr_info(FW_BUG "Invalid critical threshold (%llu)\n",
				पंचांगp);
			tz->trips.critical.flags.valid = 0;
		पूर्ण अन्यथा अणु
			tz->trips.critical.flags.valid = 1;
			acpi_handle_debug(tz->device->handle,
					  "Found critical threshold [%lu]\n",
					  tz->trips.critical.temperature);
		पूर्ण
		अगर (tz->trips.critical.flags.valid == 1) अणु
			अगर (crt == -1) अणु
				tz->trips.critical.flags.valid = 0;
			पूर्ण अन्यथा अगर (crt > 0) अणु
				अचिन्हित दीर्घ crt_k = celsius_to_deci_kelvin(crt);

				/*
				 * Allow override critical threshold
				 */
				अगर (crt_k > tz->trips.critical.temperature)
					pr_info("Critical threshold %d C\n", crt);

				tz->trips.critical.temperature = crt_k;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Critical Sleep (optional) */
	अगर (flag & ACPI_TRIPS_HOT) अणु
		status = acpi_evaluate_पूर्णांकeger(tz->device->handle,
				"_HOT", शून्य, &पंचांगp);
		अगर (ACPI_FAILURE(status)) अणु
			tz->trips.hot.flags.valid = 0;
			acpi_handle_debug(tz->device->handle,
					  "No hot threshold\n");
		पूर्ण अन्यथा अणु
			tz->trips.hot.temperature = पंचांगp;
			tz->trips.hot.flags.valid = 1;
			acpi_handle_debug(tz->device->handle,
					  "Found hot threshold [%lu]\n",
					  tz->trips.hot.temperature);
		पूर्ण
	पूर्ण

	/* Passive (optional) */
	अगर (((flag & ACPI_TRIPS_PASSIVE) && tz->trips.passive.flags.valid) ||
		(flag == ACPI_TRIPS_INIT)) अणु
		valid = tz->trips.passive.flags.valid;
		अगर (psv == -1) अणु
			status = AE_SUPPORT;
		पूर्ण अन्यथा अगर (psv > 0) अणु
			पंचांगp = celsius_to_deci_kelvin(psv);
			status = AE_OK;
		पूर्ण अन्यथा अणु
			status = acpi_evaluate_पूर्णांकeger(tz->device->handle,
				"_PSV", शून्य, &पंचांगp);
		पूर्ण

		अगर (ACPI_FAILURE(status))
			tz->trips.passive.flags.valid = 0;
		अन्यथा अणु
			tz->trips.passive.temperature = पंचांगp;
			tz->trips.passive.flags.valid = 1;
			अगर (flag == ACPI_TRIPS_INIT) अणु
				status = acpi_evaluate_पूर्णांकeger(
						tz->device->handle, "_TC1",
						शून्य, &पंचांगp);
				अगर (ACPI_FAILURE(status))
					tz->trips.passive.flags.valid = 0;
				अन्यथा
					tz->trips.passive.tc1 = पंचांगp;
				status = acpi_evaluate_पूर्णांकeger(
						tz->device->handle, "_TC2",
						शून्य, &पंचांगp);
				अगर (ACPI_FAILURE(status))
					tz->trips.passive.flags.valid = 0;
				अन्यथा
					tz->trips.passive.tc2 = पंचांगp;
				status = acpi_evaluate_पूर्णांकeger(
						tz->device->handle, "_TSP",
						शून्य, &पंचांगp);
				अगर (ACPI_FAILURE(status))
					tz->trips.passive.flags.valid = 0;
				अन्यथा
					tz->trips.passive.tsp = पंचांगp;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर ((flag & ACPI_TRIPS_DEVICES) && tz->trips.passive.flags.valid) अणु
		स_रखो(&devices, 0, माप(काष्ठा acpi_handle_list));
		status = acpi_evaluate_reference(tz->device->handle, "_PSL",
							शून्य, &devices);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_handle_info(tz->device->handle,
					 "Invalid passive threshold\n");
			tz->trips.passive.flags.valid = 0;
		पूर्ण
		अन्यथा
			tz->trips.passive.flags.valid = 1;

		अगर (स_भेद(&tz->trips.passive.devices, &devices,
				माप(काष्ठा acpi_handle_list))) अणु
			स_नकल(&tz->trips.passive.devices, &devices,
				माप(काष्ठा acpi_handle_list));
			ACPI_THERMAL_TRIPS_EXCEPTION(flag, tz, "device");
		पूर्ण
	पूर्ण
	अगर ((flag & ACPI_TRIPS_PASSIVE) || (flag & ACPI_TRIPS_DEVICES)) अणु
		अगर (valid != tz->trips.passive.flags.valid)
				ACPI_THERMAL_TRIPS_EXCEPTION(flag, tz, "state");
	पूर्ण

	/* Active (optional) */
	क्रम (i = 0; i < ACPI_THERMAL_MAX_ACTIVE; i++) अणु
		अक्षर name[5] = अणु '_', 'A', 'C', ('0' + i), '\0' पूर्ण;
		valid = tz->trips.active[i].flags.valid;

		अगर (act == -1)
			अवरोध; /* disable all active trip poपूर्णांकs */

		अगर ((flag == ACPI_TRIPS_INIT) || ((flag & ACPI_TRIPS_ACTIVE) &&
			tz->trips.active[i].flags.valid)) अणु
			status = acpi_evaluate_पूर्णांकeger(tz->device->handle,
							name, शून्य, &पंचांगp);
			अगर (ACPI_FAILURE(status)) अणु
				tz->trips.active[i].flags.valid = 0;
				अगर (i == 0)
					अवरोध;
				अगर (act <= 0)
					अवरोध;
				अगर (i == 1)
					tz->trips.active[0].temperature =
						celsius_to_deci_kelvin(act);
				अन्यथा
					/*
					 * Don't allow override higher than
					 * the next higher trip poपूर्णांक
					 */
					tz->trips.active[i - 1].temperature =
						(tz->trips.active[i - 2].temperature <
						celsius_to_deci_kelvin(act) ?
						tz->trips.active[i - 2].temperature :
						celsius_to_deci_kelvin(act));
				अवरोध;
			पूर्ण अन्यथा अणु
				tz->trips.active[i].temperature = पंचांगp;
				tz->trips.active[i].flags.valid = 1;
			पूर्ण
		पूर्ण

		name[2] = 'L';
		अगर ((flag & ACPI_TRIPS_DEVICES) && tz->trips.active[i].flags.valid ) अणु
			स_रखो(&devices, 0, माप(काष्ठा acpi_handle_list));
			status = acpi_evaluate_reference(tz->device->handle,
						name, शून्य, &devices);
			अगर (ACPI_FAILURE(status)) अणु
				acpi_handle_info(tz->device->handle,
						 "Invalid active%d threshold\n", i);
				tz->trips.active[i].flags.valid = 0;
			पूर्ण
			अन्यथा
				tz->trips.active[i].flags.valid = 1;

			अगर (स_भेद(&tz->trips.active[i].devices, &devices,
					माप(काष्ठा acpi_handle_list))) अणु
				स_नकल(&tz->trips.active[i].devices, &devices,
					माप(काष्ठा acpi_handle_list));
				ACPI_THERMAL_TRIPS_EXCEPTION(flag, tz, "device");
			पूर्ण
		पूर्ण
		अगर ((flag & ACPI_TRIPS_ACTIVE) || (flag & ACPI_TRIPS_DEVICES))
			अगर (valid != tz->trips.active[i].flags.valid)
				ACPI_THERMAL_TRIPS_EXCEPTION(flag, tz, "state");

		अगर (!tz->trips.active[i].flags.valid)
			अवरोध;
	पूर्ण

	अगर (flag & ACPI_TRIPS_DEVICES) अणु
		स_रखो(&devices, 0, माप(devices));
		status = acpi_evaluate_reference(tz->device->handle, "_TZD",
						शून्य, &devices);
		अगर (ACPI_SUCCESS(status)
		    && स_भेद(&tz->devices, &devices, माप(devices))) अणु
			tz->devices = devices;
			ACPI_THERMAL_TRIPS_EXCEPTION(flag, tz, "device");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_thermal_get_trip_poपूर्णांकs(काष्ठा acpi_thermal *tz)
अणु
	पूर्णांक i, valid, ret = acpi_thermal_trips_update(tz, ACPI_TRIPS_INIT);

	अगर (ret)
		वापस ret;

	valid = tz->trips.critical.flags.valid |
		tz->trips.hot.flags.valid |
		tz->trips.passive.flags.valid;

	क्रम (i = 0; i < ACPI_THERMAL_MAX_ACTIVE; i++)
		valid |= tz->trips.active[i].flags.valid;

	अगर (!valid) अणु
		pr_warn(FW_BUG "No valid trip found\n");
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

/* sys I/F क्रम generic thermal sysfs support */

अटल पूर्णांक thermal_get_temp(काष्ठा thermal_zone_device *thermal, पूर्णांक *temp)
अणु
	काष्ठा acpi_thermal *tz = thermal->devdata;
	पूर्णांक result;

	अगर (!tz)
		वापस -EINVAL;

	result = acpi_thermal_get_temperature(tz);
	अगर (result)
		वापस result;

	*temp = deci_kelvin_to_millicelsius_with_offset(tz->temperature,
							tz->kelvin_offset);
	वापस 0;
पूर्ण

अटल पूर्णांक thermal_get_trip_type(काष्ठा thermal_zone_device *thermal,
				 पूर्णांक trip, क्रमागत thermal_trip_type *type)
अणु
	काष्ठा acpi_thermal *tz = thermal->devdata;
	पूर्णांक i;

	अगर (!tz || trip < 0)
		वापस -EINVAL;

	अगर (tz->trips.critical.flags.valid) अणु
		अगर (!trip) अणु
			*type = THERMAL_TRIP_CRITICAL;
			वापस 0;
		पूर्ण
		trip--;
	पूर्ण

	अगर (tz->trips.hot.flags.valid) अणु
		अगर (!trip) अणु
			*type = THERMAL_TRIP_HOT;
			वापस 0;
		पूर्ण
		trip--;
	पूर्ण

	अगर (tz->trips.passive.flags.valid) अणु
		अगर (!trip) अणु
			*type = THERMAL_TRIP_PASSIVE;
			वापस 0;
		पूर्ण
		trip--;
	पूर्ण

	क्रम (i = 0; i < ACPI_THERMAL_MAX_ACTIVE &&
		tz->trips.active[i].flags.valid; i++) अणु
		अगर (!trip) अणु
			*type = THERMAL_TRIP_ACTIVE;
			वापस 0;
		पूर्ण
		trip--;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक thermal_get_trip_temp(काष्ठा thermal_zone_device *thermal,
				 पूर्णांक trip, पूर्णांक *temp)
अणु
	काष्ठा acpi_thermal *tz = thermal->devdata;
	पूर्णांक i;

	अगर (!tz || trip < 0)
		वापस -EINVAL;

	अगर (tz->trips.critical.flags.valid) अणु
		अगर (!trip) अणु
			*temp = deci_kelvin_to_millicelsius_with_offset(
				tz->trips.critical.temperature,
				tz->kelvin_offset);
			वापस 0;
		पूर्ण
		trip--;
	पूर्ण

	अगर (tz->trips.hot.flags.valid) अणु
		अगर (!trip) अणु
			*temp = deci_kelvin_to_millicelsius_with_offset(
				tz->trips.hot.temperature,
				tz->kelvin_offset);
			वापस 0;
		पूर्ण
		trip--;
	पूर्ण

	अगर (tz->trips.passive.flags.valid) अणु
		अगर (!trip) अणु
			*temp = deci_kelvin_to_millicelsius_with_offset(
				tz->trips.passive.temperature,
				tz->kelvin_offset);
			वापस 0;
		पूर्ण
		trip--;
	पूर्ण

	क्रम (i = 0; i < ACPI_THERMAL_MAX_ACTIVE &&
		tz->trips.active[i].flags.valid; i++) अणु
		अगर (!trip) अणु
			*temp = deci_kelvin_to_millicelsius_with_offset(
				tz->trips.active[i].temperature,
				tz->kelvin_offset);
			वापस 0;
		पूर्ण
		trip--;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक thermal_get_crit_temp(काष्ठा thermal_zone_device *thermal,
				पूर्णांक *temperature)
अणु
	काष्ठा acpi_thermal *tz = thermal->devdata;

	अगर (tz->trips.critical.flags.valid) अणु
		*temperature = deci_kelvin_to_millicelsius_with_offset(
				tz->trips.critical.temperature,
				tz->kelvin_offset);
		वापस 0;
	पूर्ण अन्यथा
		वापस -EINVAL;
पूर्ण

अटल पूर्णांक thermal_get_trend(काष्ठा thermal_zone_device *thermal,
				पूर्णांक trip, क्रमागत thermal_trend *trend)
अणु
	काष्ठा acpi_thermal *tz = thermal->devdata;
	क्रमागत thermal_trip_type type;
	पूर्णांक i;

	अगर (thermal_get_trip_type(thermal, trip, &type))
		वापस -EINVAL;

	अगर (type == THERMAL_TRIP_ACTIVE) अणु
		पूर्णांक trip_temp;
		पूर्णांक temp = deci_kelvin_to_millicelsius_with_offset(
					tz->temperature, tz->kelvin_offset);
		अगर (thermal_get_trip_temp(thermal, trip, &trip_temp))
			वापस -EINVAL;

		अगर (temp > trip_temp) अणु
			*trend = THERMAL_TREND_RAISING;
			वापस 0;
		पूर्ण अन्यथा अणु
			/* Fall back on शेष trend */
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/*
	 * tz->temperature has alपढ़ोy been updated by generic thermal layer,
	 * beक्रमe this callback being invoked
	 */
	i = (tz->trips.passive.tc1 * (tz->temperature - tz->last_temperature))
		+ (tz->trips.passive.tc2
		* (tz->temperature - tz->trips.passive.temperature));

	अगर (i > 0)
		*trend = THERMAL_TREND_RAISING;
	अन्यथा अगर (i < 0)
		*trend = THERMAL_TREND_DROPPING;
	अन्यथा
		*trend = THERMAL_TREND_STABLE;
	वापस 0;
पूर्ण

अटल व्योम acpi_thermal_zone_device_hot(काष्ठा thermal_zone_device *thermal)
अणु
	काष्ठा acpi_thermal *tz = thermal->devdata;

	acpi_bus_generate_netlink_event(tz->device->pnp.device_class,
					dev_name(&tz->device->dev),
					ACPI_THERMAL_NOTIFY_HOT, 1);
पूर्ण

अटल व्योम acpi_thermal_zone_device_critical(काष्ठा thermal_zone_device *thermal)
अणु
	काष्ठा acpi_thermal *tz = thermal->devdata;

	acpi_bus_generate_netlink_event(tz->device->pnp.device_class,
					dev_name(&tz->device->dev),
					ACPI_THERMAL_NOTIFY_CRITICAL, 1);

	thermal_zone_device_critical(thermal);
पूर्ण

अटल पूर्णांक acpi_thermal_cooling_device_cb(काष्ठा thermal_zone_device *thermal,
					काष्ठा thermal_cooling_device *cdev,
					bool bind)
अणु
	काष्ठा acpi_device *device = cdev->devdata;
	काष्ठा acpi_thermal *tz = thermal->devdata;
	काष्ठा acpi_device *dev;
	acpi_status status;
	acpi_handle handle;
	पूर्णांक i;
	पूर्णांक j;
	पूर्णांक trip = -1;
	पूर्णांक result = 0;

	अगर (tz->trips.critical.flags.valid)
		trip++;

	अगर (tz->trips.hot.flags.valid)
		trip++;

	अगर (tz->trips.passive.flags.valid) अणु
		trip++;
		क्रम (i = 0; i < tz->trips.passive.devices.count;
		    i++) अणु
			handle = tz->trips.passive.devices.handles[i];
			status = acpi_bus_get_device(handle, &dev);
			अगर (ACPI_FAILURE(status) || dev != device)
				जारी;
			अगर (bind)
				result =
					thermal_zone_bind_cooling_device
					(thermal, trip, cdev,
					 THERMAL_NO_LIMIT, THERMAL_NO_LIMIT,
					 THERMAL_WEIGHT_DEFAULT);
			अन्यथा
				result =
					thermal_zone_unbind_cooling_device
					(thermal, trip, cdev);
			अगर (result)
				जाओ failed;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < ACPI_THERMAL_MAX_ACTIVE; i++) अणु
		अगर (!tz->trips.active[i].flags.valid)
			अवरोध;
		trip++;
		क्रम (j = 0;
		    j < tz->trips.active[i].devices.count;
		    j++) अणु
			handle = tz->trips.active[i].devices.handles[j];
			status = acpi_bus_get_device(handle, &dev);
			अगर (ACPI_FAILURE(status) || dev != device)
				जारी;
			अगर (bind)
				result = thermal_zone_bind_cooling_device
					(thermal, trip, cdev,
					 THERMAL_NO_LIMIT, THERMAL_NO_LIMIT,
					 THERMAL_WEIGHT_DEFAULT);
			अन्यथा
				result = thermal_zone_unbind_cooling_device
					(thermal, trip, cdev);
			अगर (result)
				जाओ failed;
		पूर्ण
	पूर्ण

failed:
	वापस result;
पूर्ण

अटल पूर्णांक
acpi_thermal_bind_cooling_device(काष्ठा thermal_zone_device *thermal,
					काष्ठा thermal_cooling_device *cdev)
अणु
	वापस acpi_thermal_cooling_device_cb(thermal, cdev, true);
पूर्ण

अटल पूर्णांक
acpi_thermal_unbind_cooling_device(काष्ठा thermal_zone_device *thermal,
					काष्ठा thermal_cooling_device *cdev)
अणु
	वापस acpi_thermal_cooling_device_cb(thermal, cdev, false);
पूर्ण

अटल काष्ठा thermal_zone_device_ops acpi_thermal_zone_ops = अणु
	.bind = acpi_thermal_bind_cooling_device,
	.unbind	= acpi_thermal_unbind_cooling_device,
	.get_temp = thermal_get_temp,
	.get_trip_type = thermal_get_trip_type,
	.get_trip_temp = thermal_get_trip_temp,
	.get_crit_temp = thermal_get_crit_temp,
	.get_trend = thermal_get_trend,
	.hot = acpi_thermal_zone_device_hot,
	.critical = acpi_thermal_zone_device_critical,
पूर्ण;

अटल पूर्णांक acpi_thermal_रेजिस्टर_thermal_zone(काष्ठा acpi_thermal *tz)
अणु
	पूर्णांक trips = 0;
	पूर्णांक result;
	acpi_status status;
	पूर्णांक i;

	अगर (tz->trips.critical.flags.valid)
		trips++;

	अगर (tz->trips.hot.flags.valid)
		trips++;

	अगर (tz->trips.passive.flags.valid)
		trips++;

	क्रम (i = 0; i < ACPI_THERMAL_MAX_ACTIVE &&
			tz->trips.active[i].flags.valid; i++, trips++);

	अगर (tz->trips.passive.flags.valid)
		tz->thermal_zone =
			thermal_zone_device_रेजिस्टर("acpitz", trips, 0, tz,
						&acpi_thermal_zone_ops, शून्य,
						     tz->trips.passive.tsp*100,
						     tz->polling_frequency*100);
	अन्यथा
		tz->thermal_zone =
			thermal_zone_device_रेजिस्टर("acpitz", trips, 0, tz,
						&acpi_thermal_zone_ops, शून्य,
						0, tz->polling_frequency*100);
	अगर (IS_ERR(tz->thermal_zone))
		वापस -ENODEV;

	result = sysfs_create_link(&tz->device->dev.kobj,
				   &tz->thermal_zone->device.kobj, "thermal_zone");
	अगर (result)
		जाओ unरेजिस्टर_tzd;

	result = sysfs_create_link(&tz->thermal_zone->device.kobj,
				   &tz->device->dev.kobj, "device");
	अगर (result)
		जाओ हटाओ_tz_link;

	status =  acpi_bus_attach_निजी_data(tz->device->handle,
					       tz->thermal_zone);
	अगर (ACPI_FAILURE(status)) अणु
		result = -ENODEV;
		जाओ हटाओ_dev_link;
	पूर्ण

	result = thermal_zone_device_enable(tz->thermal_zone);
	अगर (result)
		जाओ acpi_bus_detach;

	dev_info(&tz->device->dev, "registered as thermal_zone%d\n",
		 tz->thermal_zone->id);

	वापस 0;

acpi_bus_detach:
	acpi_bus_detach_निजी_data(tz->device->handle);
हटाओ_dev_link:
	sysfs_हटाओ_link(&tz->thermal_zone->device.kobj, "device");
हटाओ_tz_link:
	sysfs_हटाओ_link(&tz->device->dev.kobj, "thermal_zone");
unरेजिस्टर_tzd:
	thermal_zone_device_unरेजिस्टर(tz->thermal_zone);

	वापस result;
पूर्ण

अटल व्योम acpi_thermal_unरेजिस्टर_thermal_zone(काष्ठा acpi_thermal *tz)
अणु
	sysfs_हटाओ_link(&tz->device->dev.kobj, "thermal_zone");
	sysfs_हटाओ_link(&tz->thermal_zone->device.kobj, "device");
	thermal_zone_device_unरेजिस्टर(tz->thermal_zone);
	tz->thermal_zone = शून्य;
	acpi_bus_detach_निजी_data(tz->device->handle);
पूर्ण


/* --------------------------------------------------------------------------
                                 Driver Interface
   -------------------------------------------------------------------------- */

अटल व्योम acpi_queue_thermal_check(काष्ठा acpi_thermal *tz)
अणु
	अगर (!work_pending(&tz->thermal_check_work))
		queue_work(acpi_thermal_pm_queue, &tz->thermal_check_work);
पूर्ण

अटल व्योम acpi_thermal_notअगरy(काष्ठा acpi_device *device, u32 event)
अणु
	काष्ठा acpi_thermal *tz = acpi_driver_data(device);


	अगर (!tz)
		वापस;

	चयन (event) अणु
	हाल ACPI_THERMAL_NOTIFY_TEMPERATURE:
		acpi_queue_thermal_check(tz);
		अवरोध;
	हाल ACPI_THERMAL_NOTIFY_THRESHOLDS:
		acpi_thermal_trips_update(tz, ACPI_TRIPS_REFRESH_THRESHOLDS);
		acpi_queue_thermal_check(tz);
		acpi_bus_generate_netlink_event(device->pnp.device_class,
						  dev_name(&device->dev), event, 0);
		अवरोध;
	हाल ACPI_THERMAL_NOTIFY_DEVICES:
		acpi_thermal_trips_update(tz, ACPI_TRIPS_REFRESH_DEVICES);
		acpi_queue_thermal_check(tz);
		acpi_bus_generate_netlink_event(device->pnp.device_class,
						  dev_name(&device->dev), event, 0);
		अवरोध;
	शेष:
		acpi_handle_debug(device->handle, "Unsupported event [0x%x]\n",
				  event);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * On some platक्रमms, the AML code has dependency about
 * the evaluating order of _TMP and _CRT/_HOT/_PSV/_ACx.
 * 1. On HP Pavilion G4-1016tx, _TMP must be invoked after
 *    /_CRT/_HOT/_PSV/_ACx, or अन्यथा प्रणाली will be घातer off.
 * 2. On HP Compaq 6715b/6715s, the वापस value of _PSV is 0
 *    अगर _TMP has never been evaluated.
 *
 * As this dependency is totally transparent to OS, evaluate
 * all of them once, in the order of _CRT/_HOT/_PSV/_ACx,
 * _TMP, beक्रमe they are actually used.
 */
अटल व्योम acpi_thermal_aml_dependency_fix(काष्ठा acpi_thermal *tz)
अणु
	acpi_handle handle = tz->device->handle;
	अचिन्हित दीर्घ दीर्घ value;
	पूर्णांक i;

	acpi_evaluate_पूर्णांकeger(handle, "_CRT", शून्य, &value);
	acpi_evaluate_पूर्णांकeger(handle, "_HOT", शून्य, &value);
	acpi_evaluate_पूर्णांकeger(handle, "_PSV", शून्य, &value);
	क्रम (i = 0; i < ACPI_THERMAL_MAX_ACTIVE; i++) अणु
		अक्षर name[5] = अणु '_', 'A', 'C', ('0' + i), '\0' पूर्ण;
		acpi_status status;

		status = acpi_evaluate_पूर्णांकeger(handle, name, शून्य, &value);
		अगर (status == AE_NOT_FOUND)
			अवरोध;
	पूर्ण
	acpi_evaluate_पूर्णांकeger(handle, "_TMP", शून्य, &value);
पूर्ण

अटल पूर्णांक acpi_thermal_get_info(काष्ठा acpi_thermal *tz)
अणु
	पूर्णांक result = 0;


	अगर (!tz)
		वापस -EINVAL;

	acpi_thermal_aml_dependency_fix(tz);

	/* Get trip poपूर्णांकs [_CRT, _PSV, etc.] (required) */
	result = acpi_thermal_get_trip_poपूर्णांकs(tz);
	अगर (result)
		वापस result;

	/* Get temperature [_TMP] (required) */
	result = acpi_thermal_get_temperature(tz);
	अगर (result)
		वापस result;

	/* Set the cooling mode [_SCP] to active cooling (शेष) */
	result = acpi_thermal_set_cooling_mode(tz, ACPI_THERMAL_MODE_ACTIVE);
	अगर (!result)
		tz->flags.cooling_mode = 1;

	/* Get शेष polling frequency [_TZP] (optional) */
	अगर (tzp)
		tz->polling_frequency = tzp;
	अन्यथा
		acpi_thermal_get_polling_frequency(tz);

	वापस 0;
पूर्ण

/*
 * The exact offset between Kelvin and degree Celsius is 273.15. However ACPI
 * handles temperature values with a single decimal place. As a consequence,
 * some implementations use an offset of 273.1 and others use an offset of
 * 273.2. Try to find out which one is being used, to present the most
 * accurate and visually appealing number.
 *
 * The heuristic below should work क्रम all ACPI thermal zones which have a
 * critical trip poपूर्णांक with a value being a multiple of 0.5 degree Celsius.
 */
अटल व्योम acpi_thermal_guess_offset(काष्ठा acpi_thermal *tz)
अणु
	अगर (tz->trips.critical.flags.valid &&
	    (tz->trips.critical.temperature % 5) == 1)
		tz->kelvin_offset = 273100;
	अन्यथा
		tz->kelvin_offset = 273200;
पूर्ण

अटल व्योम acpi_thermal_check_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा acpi_thermal *tz = container_of(work, काष्ठा acpi_thermal,
					       thermal_check_work);

	/*
	 * In general, it is not sufficient to check the pending bit, because
	 * subsequent instances of this function may be queued after one of them
	 * has started running (e.g. अगर _TMP sleeps).  Aव्योम bailing out अगर just
	 * one of them is running, though, because it may have करोne the actual
	 * check some समय ago, so allow at least one of them to block on the
	 * mutex जबतक another one is running the update.
	 */
	अगर (!refcount_dec_not_one(&tz->thermal_check_count))
		वापस;

	mutex_lock(&tz->thermal_check_lock);

	thermal_zone_device_update(tz->thermal_zone, THERMAL_EVENT_UNSPECIFIED);

	refcount_inc(&tz->thermal_check_count);

	mutex_unlock(&tz->thermal_check_lock);
पूर्ण

अटल पूर्णांक acpi_thermal_add(काष्ठा acpi_device *device)
अणु
	पूर्णांक result = 0;
	काष्ठा acpi_thermal *tz = शून्य;


	अगर (!device)
		वापस -EINVAL;

	tz = kzalloc(माप(काष्ठा acpi_thermal), GFP_KERNEL);
	अगर (!tz)
		वापस -ENOMEM;

	tz->device = device;
	म_नकल(tz->name, device->pnp.bus_id);
	म_नकल(acpi_device_name(device), ACPI_THERMAL_DEVICE_NAME);
	म_नकल(acpi_device_class(device), ACPI_THERMAL_CLASS);
	device->driver_data = tz;

	result = acpi_thermal_get_info(tz);
	अगर (result)
		जाओ मुक्त_memory;

	acpi_thermal_guess_offset(tz);

	result = acpi_thermal_रेजिस्टर_thermal_zone(tz);
	अगर (result)
		जाओ मुक्त_memory;

	refcount_set(&tz->thermal_check_count, 3);
	mutex_init(&tz->thermal_check_lock);
	INIT_WORK(&tz->thermal_check_work, acpi_thermal_check_fn);

	pr_info("%s [%s] (%ld C)\n", acpi_device_name(device),
		acpi_device_bid(device), deci_kelvin_to_celsius(tz->temperature));
	जाओ end;

मुक्त_memory:
	kमुक्त(tz);
end:
	वापस result;
पूर्ण

अटल पूर्णांक acpi_thermal_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_thermal *tz = शून्य;

	अगर (!device || !acpi_driver_data(device))
		वापस -EINVAL;

	flush_workqueue(acpi_thermal_pm_queue);
	tz = acpi_driver_data(device);

	acpi_thermal_unरेजिस्टर_thermal_zone(tz);
	kमुक्त(tz);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक acpi_thermal_suspend(काष्ठा device *dev)
अणु
	/* Make sure the previously queued thermal check work has been करोne */
	flush_workqueue(acpi_thermal_pm_queue);
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_thermal_resume(काष्ठा device *dev)
अणु
	काष्ठा acpi_thermal *tz;
	पूर्णांक i, j, घातer_state, result;

	अगर (!dev)
		वापस -EINVAL;

	tz = acpi_driver_data(to_acpi_device(dev));
	अगर (!tz)
		वापस -EINVAL;

	क्रम (i = 0; i < ACPI_THERMAL_MAX_ACTIVE; i++) अणु
		अगर (!(&tz->trips.active[i]))
			अवरोध;
		अगर (!tz->trips.active[i].flags.valid)
			अवरोध;
		tz->trips.active[i].flags.enabled = 1;
		क्रम (j = 0; j < tz->trips.active[i].devices.count; j++) अणु
			result = acpi_bus_update_घातer(
					tz->trips.active[i].devices.handles[j],
					&घातer_state);
			अगर (result || (घातer_state != ACPI_STATE_D0)) अणु
				tz->trips.active[i].flags.enabled = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		tz->state.active |= tz->trips.active[i].flags.enabled;
	पूर्ण

	acpi_queue_thermal_check(tz);

	वापस AE_OK;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक thermal_act(स्थिर काष्ठा dmi_प्रणाली_id *d) अणु

	अगर (act == 0) अणु
		pr_notice("%s detected: disabling all active thermal trip points\n",
			  d->ident);
		act = -1;
	पूर्ण
	वापस 0;
पूर्ण
अटल पूर्णांक thermal_nocrt(स्थिर काष्ठा dmi_प्रणाली_id *d) अणु

	pr_notice("%s detected: disabling all critical thermal trip point actions.\n",
		  d->ident);
	nocrt = 1;
	वापस 0;
पूर्ण
अटल पूर्णांक thermal_tzp(स्थिर काष्ठा dmi_प्रणाली_id *d) अणु

	अगर (tzp == 0) अणु
		pr_notice("%s detected: enabling thermal zone polling\n",
			  d->ident);
		tzp = 300;	/* 300 dS = 30 Seconds */
	पूर्ण
	वापस 0;
पूर्ण
अटल पूर्णांक thermal_psv(स्थिर काष्ठा dmi_प्रणाली_id *d) अणु

	अगर (psv == 0) अणु
		pr_notice("%s detected: disabling all passive thermal trip points\n",
			  d->ident);
		psv = -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id thermal_dmi_table[] __initस्थिर = अणु
	/*
	 * Award BIOS on this AOpen makes thermal control almost worthless.
	 * http://bugzilla.kernel.org/show_bug.cgi?id=8842
	 */
	अणु
	 .callback = thermal_act,
	 .ident = "AOpen i915GMm-HFS",
	 .matches = अणु
		DMI_MATCH(DMI_BOARD_VENDOR, "AOpen"),
		DMI_MATCH(DMI_BOARD_NAME, "i915GMm-HFS"),
		पूर्ण,
	पूर्ण,
	अणु
	 .callback = thermal_psv,
	 .ident = "AOpen i915GMm-HFS",
	 .matches = अणु
		DMI_MATCH(DMI_BOARD_VENDOR, "AOpen"),
		DMI_MATCH(DMI_BOARD_NAME, "i915GMm-HFS"),
		पूर्ण,
	पूर्ण,
	अणु
	 .callback = thermal_tzp,
	 .ident = "AOpen i915GMm-HFS",
	 .matches = अणु
		DMI_MATCH(DMI_BOARD_VENDOR, "AOpen"),
		DMI_MATCH(DMI_BOARD_NAME, "i915GMm-HFS"),
		पूर्ण,
	पूर्ण,
	अणु
	 .callback = thermal_nocrt,
	 .ident = "Gigabyte GA-7ZX",
	 .matches = अणु
		DMI_MATCH(DMI_BOARD_VENDOR, "Gigabyte Technology Co., Ltd."),
		DMI_MATCH(DMI_BOARD_NAME, "7ZX"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक __init acpi_thermal_init(व्योम)
अणु
	पूर्णांक result = 0;

	dmi_check_प्रणाली(thermal_dmi_table);

	अगर (off) अणु
		pr_notice("thermal control disabled\n");
		वापस -ENODEV;
	पूर्ण

	acpi_thermal_pm_queue = alloc_workqueue("acpi_thermal_pm",
						WQ_HIGHPRI | WQ_MEM_RECLAIM, 0);
	अगर (!acpi_thermal_pm_queue)
		वापस -ENODEV;

	result = acpi_bus_रेजिस्टर_driver(&acpi_thermal_driver);
	अगर (result < 0) अणु
		destroy_workqueue(acpi_thermal_pm_queue);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास acpi_thermal_निकास(व्योम)
अणु
	acpi_bus_unरेजिस्टर_driver(&acpi_thermal_driver);
	destroy_workqueue(acpi_thermal_pm_queue);

	वापस;
पूर्ण

module_init(acpi_thermal_init);
module_निकास(acpi_thermal_निकास);
