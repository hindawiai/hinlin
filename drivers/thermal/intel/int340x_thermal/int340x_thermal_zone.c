<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * पूर्णांक340x_thermal_zone.c
 * Copyright (c) 2015, Intel Corporation.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/acpi.h>
#समावेश <linux/thermal.h>
#समावेश <linux/units.h>
#समावेश "int340x_thermal_zone.h"

अटल पूर्णांक पूर्णांक340x_thermal_get_zone_temp(काष्ठा thermal_zone_device *zone,
					 पूर्णांक *temp)
अणु
	काष्ठा पूर्णांक34x_thermal_zone *d = zone->devdata;
	अचिन्हित दीर्घ दीर्घ पंचांगp;
	acpi_status status;

	अगर (d->override_ops && d->override_ops->get_temp)
		वापस d->override_ops->get_temp(zone, temp);

	status = acpi_evaluate_पूर्णांकeger(d->adev->handle, "_TMP", शून्य, &पंचांगp);
	अगर (ACPI_FAILURE(status))
		वापस -EIO;

	अगर (d->lpat_table) अणु
		पूर्णांक conv_temp;

		conv_temp = acpi_lpat_raw_to_temp(d->lpat_table, (पूर्णांक)पंचांगp);
		अगर (conv_temp < 0)
			वापस conv_temp;

		*temp = (अचिन्हित दीर्घ)conv_temp * 10;
	पूर्ण अन्यथा
		/* _TMP वापसs the temperature in tenths of degrees Kelvin */
		*temp = deci_kelvin_to_millicelsius(पंचांगp);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांक340x_thermal_get_trip_temp(काष्ठा thermal_zone_device *zone,
					 पूर्णांक trip, पूर्णांक *temp)
अणु
	काष्ठा पूर्णांक34x_thermal_zone *d = zone->devdata;
	पूर्णांक i;

	अगर (d->override_ops && d->override_ops->get_trip_temp)
		वापस d->override_ops->get_trip_temp(zone, trip, temp);

	अगर (trip < d->aux_trip_nr)
		*temp = d->aux_trips[trip];
	अन्यथा अगर (trip == d->crt_trip_id)
		*temp = d->crt_temp;
	अन्यथा अगर (trip == d->psv_trip_id)
		*temp = d->psv_temp;
	अन्यथा अगर (trip == d->hot_trip_id)
		*temp = d->hot_temp;
	अन्यथा अणु
		क्रम (i = 0; i < INT340X_THERMAL_MAX_ACT_TRIP_COUNT; i++) अणु
			अगर (d->act_trips[i].valid &&
			    d->act_trips[i].id == trip) अणु
				*temp = d->act_trips[i].temp;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == INT340X_THERMAL_MAX_ACT_TRIP_COUNT)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांक340x_thermal_get_trip_type(काष्ठा thermal_zone_device *zone,
					 पूर्णांक trip,
					 क्रमागत thermal_trip_type *type)
अणु
	काष्ठा पूर्णांक34x_thermal_zone *d = zone->devdata;
	पूर्णांक i;

	अगर (d->override_ops && d->override_ops->get_trip_type)
		वापस d->override_ops->get_trip_type(zone, trip, type);

	अगर (trip < d->aux_trip_nr)
		*type = THERMAL_TRIP_PASSIVE;
	अन्यथा अगर (trip == d->crt_trip_id)
		*type = THERMAL_TRIP_CRITICAL;
	अन्यथा अगर (trip == d->hot_trip_id)
		*type = THERMAL_TRIP_HOT;
	अन्यथा अगर (trip == d->psv_trip_id)
		*type = THERMAL_TRIP_PASSIVE;
	अन्यथा अणु
		क्रम (i = 0; i < INT340X_THERMAL_MAX_ACT_TRIP_COUNT; i++) अणु
			अगर (d->act_trips[i].valid &&
			    d->act_trips[i].id == trip) अणु
				*type = THERMAL_TRIP_ACTIVE;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == INT340X_THERMAL_MAX_ACT_TRIP_COUNT)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांक340x_thermal_set_trip_temp(काष्ठा thermal_zone_device *zone,
				      पूर्णांक trip, पूर्णांक temp)
अणु
	काष्ठा पूर्णांक34x_thermal_zone *d = zone->devdata;
	acpi_status status;
	अक्षर name[10];

	अगर (d->override_ops && d->override_ops->set_trip_temp)
		वापस d->override_ops->set_trip_temp(zone, trip, temp);

	snम_लिखो(name, माप(name), "PAT%d", trip);
	status = acpi_execute_simple_method(d->adev->handle, name,
			millicelsius_to_deci_kelvin(temp));
	अगर (ACPI_FAILURE(status))
		वापस -EIO;

	d->aux_trips[trip] = temp;

	वापस 0;
पूर्ण


अटल पूर्णांक पूर्णांक340x_thermal_get_trip_hyst(काष्ठा thermal_zone_device *zone,
		पूर्णांक trip, पूर्णांक *temp)
अणु
	काष्ठा पूर्णांक34x_thermal_zone *d = zone->devdata;
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ hyst;

	अगर (d->override_ops && d->override_ops->get_trip_hyst)
		वापस d->override_ops->get_trip_hyst(zone, trip, temp);

	status = acpi_evaluate_पूर्णांकeger(d->adev->handle, "GTSH", शून्य, &hyst);
	अगर (ACPI_FAILURE(status))
		*temp = 0;
	अन्यथा
		*temp = hyst * 100;

	वापस 0;
पूर्ण

अटल व्योम पूर्णांक340x_thermal_critical(काष्ठा thermal_zone_device *zone)
अणु
	dev_dbg(&zone->device, "%s: critical temperature reached\n", zone->type);
पूर्ण

अटल काष्ठा thermal_zone_device_ops पूर्णांक340x_thermal_zone_ops = अणु
	.get_temp       = पूर्णांक340x_thermal_get_zone_temp,
	.get_trip_temp	= पूर्णांक340x_thermal_get_trip_temp,
	.get_trip_type	= पूर्णांक340x_thermal_get_trip_type,
	.set_trip_temp	= पूर्णांक340x_thermal_set_trip_temp,
	.get_trip_hyst =  पूर्णांक340x_thermal_get_trip_hyst,
	.critical	= पूर्णांक340x_thermal_critical,
पूर्ण;

अटल पूर्णांक पूर्णांक340x_thermal_get_trip_config(acpi_handle handle, अक्षर *name,
				      पूर्णांक *temp)
अणु
	अचिन्हित दीर्घ दीर्घ r;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(handle, name, शून्य, &r);
	अगर (ACPI_FAILURE(status))
		वापस -EIO;

	*temp = deci_kelvin_to_millicelsius(r);

	वापस 0;
पूर्ण

पूर्णांक पूर्णांक340x_thermal_पढ़ो_trips(काष्ठा पूर्णांक34x_thermal_zone *पूर्णांक34x_zone)
अणु
	पूर्णांक trip_cnt = पूर्णांक34x_zone->aux_trip_nr;
	पूर्णांक i;

	पूर्णांक34x_zone->crt_trip_id = -1;
	अगर (!पूर्णांक340x_thermal_get_trip_config(पूर्णांक34x_zone->adev->handle, "_CRT",
					     &पूर्णांक34x_zone->crt_temp))
		पूर्णांक34x_zone->crt_trip_id = trip_cnt++;

	पूर्णांक34x_zone->hot_trip_id = -1;
	अगर (!पूर्णांक340x_thermal_get_trip_config(पूर्णांक34x_zone->adev->handle, "_HOT",
					     &पूर्णांक34x_zone->hot_temp))
		पूर्णांक34x_zone->hot_trip_id = trip_cnt++;

	पूर्णांक34x_zone->psv_trip_id = -1;
	अगर (!पूर्णांक340x_thermal_get_trip_config(पूर्णांक34x_zone->adev->handle, "_PSV",
					     &पूर्णांक34x_zone->psv_temp))
		पूर्णांक34x_zone->psv_trip_id = trip_cnt++;

	क्रम (i = 0; i < INT340X_THERMAL_MAX_ACT_TRIP_COUNT; i++) अणु
		अक्षर name[5] = अणु '_', 'A', 'C', '0' + i, '\0' पूर्ण;

		अगर (पूर्णांक340x_thermal_get_trip_config(पूर्णांक34x_zone->adev->handle,
					name,
					&पूर्णांक34x_zone->act_trips[i].temp))
			अवरोध;

		पूर्णांक34x_zone->act_trips[i].id = trip_cnt++;
		पूर्णांक34x_zone->act_trips[i].valid = true;
	पूर्ण

	वापस trip_cnt;
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांक340x_thermal_पढ़ो_trips);

अटल काष्ठा thermal_zone_params पूर्णांक340x_thermal_params = अणु
	.governor_name = "user_space",
	.no_hwmon = true,
पूर्ण;

काष्ठा पूर्णांक34x_thermal_zone *पूर्णांक340x_thermal_zone_add(काष्ठा acpi_device *adev,
				काष्ठा thermal_zone_device_ops *override_ops)
अणु
	काष्ठा पूर्णांक34x_thermal_zone *पूर्णांक34x_thermal_zone;
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ trip_cnt;
	पूर्णांक trip_mask = 0;
	पूर्णांक ret;

	पूर्णांक34x_thermal_zone = kzalloc(माप(*पूर्णांक34x_thermal_zone),
				      GFP_KERNEL);
	अगर (!पूर्णांक34x_thermal_zone)
		वापस ERR_PTR(-ENOMEM);

	पूर्णांक34x_thermal_zone->adev = adev;
	पूर्णांक34x_thermal_zone->override_ops = override_ops;

	status = acpi_evaluate_पूर्णांकeger(adev->handle, "PATC", शून्य, &trip_cnt);
	अगर (ACPI_FAILURE(status))
		trip_cnt = 0;
	अन्यथा अणु
		पूर्णांक i;

		पूर्णांक34x_thermal_zone->aux_trips =
			kसुस्मृति(trip_cnt,
				माप(*पूर्णांक34x_thermal_zone->aux_trips),
				GFP_KERNEL);
		अगर (!पूर्णांक34x_thermal_zone->aux_trips) अणु
			ret = -ENOMEM;
			जाओ err_trip_alloc;
		पूर्ण
		trip_mask = BIT(trip_cnt) - 1;
		पूर्णांक34x_thermal_zone->aux_trip_nr = trip_cnt;
		क्रम (i = 0; i < trip_cnt; ++i)
			पूर्णांक34x_thermal_zone->aux_trips[i] = THERMAL_TEMP_INVALID;
	पूर्ण

	trip_cnt = पूर्णांक340x_thermal_पढ़ो_trips(पूर्णांक34x_thermal_zone);

	पूर्णांक34x_thermal_zone->lpat_table = acpi_lpat_get_conversion_table(
								adev->handle);

	पूर्णांक34x_thermal_zone->zone = thermal_zone_device_रेजिस्टर(
						acpi_device_bid(adev),
						trip_cnt,
						trip_mask, पूर्णांक34x_thermal_zone,
						&पूर्णांक340x_thermal_zone_ops,
						&पूर्णांक340x_thermal_params,
						0, 0);
	अगर (IS_ERR(पूर्णांक34x_thermal_zone->zone)) अणु
		ret = PTR_ERR(पूर्णांक34x_thermal_zone->zone);
		जाओ err_thermal_zone;
	पूर्ण
	ret = thermal_zone_device_enable(पूर्णांक34x_thermal_zone->zone);
	अगर (ret)
		जाओ err_enable;

	वापस पूर्णांक34x_thermal_zone;

err_enable:
	thermal_zone_device_unरेजिस्टर(पूर्णांक34x_thermal_zone->zone);
err_thermal_zone:
	acpi_lpat_मुक्त_conversion_table(पूर्णांक34x_thermal_zone->lpat_table);
	kमुक्त(पूर्णांक34x_thermal_zone->aux_trips);
err_trip_alloc:
	kमुक्त(पूर्णांक34x_thermal_zone);
	वापस ERR_PTR(ret);
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांक340x_thermal_zone_add);

व्योम पूर्णांक340x_thermal_zone_हटाओ(काष्ठा पूर्णांक34x_thermal_zone
				 *पूर्णांक34x_thermal_zone)
अणु
	thermal_zone_device_unरेजिस्टर(पूर्णांक34x_thermal_zone->zone);
	acpi_lpat_मुक्त_conversion_table(पूर्णांक34x_thermal_zone->lpat_table);
	kमुक्त(पूर्णांक34x_thermal_zone->aux_trips);
	kमुक्त(पूर्णांक34x_thermal_zone);
पूर्ण
EXPORT_SYMBOL_GPL(पूर्णांक340x_thermal_zone_हटाओ);

MODULE_AUTHOR("Aaron Lu <aaron.lu@intel.com>");
MODULE_AUTHOR("Srinivas Pandruvada <srinivas.pandruvada@linux.intel.com>");
MODULE_DESCRIPTION("Intel INT340x common thermal zone handler");
MODULE_LICENSE("GPL v2");
