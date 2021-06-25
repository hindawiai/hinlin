<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * A hwmon driver क्रम ACPI 4.0 घातer meters
 * Copyright (C) 2009 IBM
 *
 * Author: Darrick J. Wong <darrick.wong@oracle.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mutex.h>
#समावेश <linux/dmi.h>
#समावेश <linux/slab.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/sched.h>
#समावेश <linux/समय.स>
#समावेश <linux/err.h>
#समावेश <linux/acpi.h>

#घोषणा ACPI_POWER_METER_NAME		"power_meter"
#घोषणा ACPI_POWER_METER_DEVICE_NAME	"Power Meter"
#घोषणा ACPI_POWER_METER_CLASS		"pwr_meter_resource"

#घोषणा NUM_SENSORS			17

#घोषणा POWER_METER_CAN_MEASURE	(1 << 0)
#घोषणा POWER_METER_CAN_TRIP	(1 << 1)
#घोषणा POWER_METER_CAN_CAP	(1 << 2)
#घोषणा POWER_METER_CAN_NOTIFY	(1 << 3)
#घोषणा POWER_METER_IS_BATTERY	(1 << 8)
#घोषणा UNKNOWN_HYSTERESIS	0xFFFFFFFF

#घोषणा METER_NOTIFY_CONFIG	0x80
#घोषणा METER_NOTIFY_TRIP	0x81
#घोषणा METER_NOTIFY_CAP	0x82
#घोषणा METER_NOTIFY_CAPPING	0x83
#घोषणा METER_NOTIFY_INTERVAL	0x84

#घोषणा POWER_AVERAGE_NAME	"power1_average"
#घोषणा POWER_CAP_NAME		"power1_cap"
#घोषणा POWER_AVG_INTERVAL_NAME	"power1_average_interval"
#घोषणा POWER_ALARM_NAME	"power1_alarm"

अटल पूर्णांक cap_in_hardware;
अटल bool क्रमce_cap_on;

अटल पूर्णांक can_cap_in_hardware(व्योम)
अणु
	वापस क्रमce_cap_on || cap_in_hardware;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id घातer_meter_ids[] = अणु
	अणु"ACPI000D", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, घातer_meter_ids);

काष्ठा acpi_घातer_meter_capabilities अणु
	u64		flags;
	u64		units;
	u64		type;
	u64		accuracy;
	u64		sampling_समय;
	u64		min_avg_पूर्णांकerval;
	u64		max_avg_पूर्णांकerval;
	u64		hysteresis;
	u64		configurable_cap;
	u64		min_cap;
	u64		max_cap;
पूर्ण;

काष्ठा acpi_घातer_meter_resource अणु
	काष्ठा acpi_device	*acpi_dev;
	acpi_bus_id		name;
	काष्ठा mutex		lock;
	काष्ठा device		*hwmon_dev;
	काष्ठा acpi_घातer_meter_capabilities	caps;
	acpi_string		model_number;
	acpi_string		serial_number;
	acpi_string		oem_info;
	u64		घातer;
	u64		cap;
	u64		avg_पूर्णांकerval;
	पूर्णांक			sensors_valid;
	अचिन्हित दीर्घ		sensors_last_updated;
	काष्ठा sensor_device_attribute	sensors[NUM_SENSORS];
	पूर्णांक			num_sensors;
	s64			trip[2];
	पूर्णांक			num_करोमुख्य_devices;
	काष्ठा acpi_device	**करोमुख्य_devices;
	काष्ठा kobject		*holders_dir;
पूर्ण;

काष्ठा sensor_ढाँचा अणु
	अक्षर *label;
	sमाप_प्रकार (*show)(काष्ठा device *dev,
			काष्ठा device_attribute *devattr,
			अक्षर *buf);
	sमाप_प्रकार (*set)(काष्ठा device *dev,
		       काष्ठा device_attribute *devattr,
		       स्थिर अक्षर *buf, माप_प्रकार count);
	पूर्णांक index;
पूर्ण;

/* Averaging पूर्णांकerval */
अटल पूर्णांक update_avg_पूर्णांकerval(काष्ठा acpi_घातer_meter_resource *resource)
अणु
	अचिन्हित दीर्घ दीर्घ data;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(resource->acpi_dev->handle, "_GAI",
				       शून्य, &data);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_evaluation_failure_warn(resource->acpi_dev->handle, "_GAI",
					     status);
		वापस -ENODEV;
	पूर्ण

	resource->avg_पूर्णांकerval = data;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार show_avg_पूर्णांकerval(काष्ठा device *dev,
				 काष्ठा device_attribute *devattr,
				 अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi_dev = to_acpi_device(dev);
	काष्ठा acpi_घातer_meter_resource *resource = acpi_dev->driver_data;

	mutex_lock(&resource->lock);
	update_avg_पूर्णांकerval(resource);
	mutex_unlock(&resource->lock);

	वापस प्र_लिखो(buf, "%llu\n", resource->avg_पूर्णांकerval);
पूर्ण

अटल sमाप_प्रकार set_avg_पूर्णांकerval(काष्ठा device *dev,
				काष्ठा device_attribute *devattr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा acpi_device *acpi_dev = to_acpi_device(dev);
	काष्ठा acpi_घातer_meter_resource *resource = acpi_dev->driver_data;
	जोड़ acpi_object arg0 = अणु ACPI_TYPE_INTEGER पूर्ण;
	काष्ठा acpi_object_list args = अणु 1, &arg0 पूर्ण;
	पूर्णांक res;
	अचिन्हित दीर्घ temp;
	अचिन्हित दीर्घ दीर्घ data;
	acpi_status status;

	res = kम_से_अदीर्घ(buf, 10, &temp);
	अगर (res)
		वापस res;

	अगर (temp > resource->caps.max_avg_पूर्णांकerval ||
	    temp < resource->caps.min_avg_पूर्णांकerval)
		वापस -EINVAL;
	arg0.पूर्णांकeger.value = temp;

	mutex_lock(&resource->lock);
	status = acpi_evaluate_पूर्णांकeger(resource->acpi_dev->handle, "_PAI",
				       &args, &data);
	अगर (ACPI_SUCCESS(status))
		resource->avg_पूर्णांकerval = temp;
	mutex_unlock(&resource->lock);

	अगर (ACPI_FAILURE(status)) अणु
		acpi_evaluation_failure_warn(resource->acpi_dev->handle, "_PAI",
					     status);
		वापस -EINVAL;
	पूर्ण

	/* _PAI वापसs 0 on success, nonzero otherwise */
	अगर (data)
		वापस -EINVAL;

	वापस count;
पूर्ण

/* Cap functions */
अटल पूर्णांक update_cap(काष्ठा acpi_घातer_meter_resource *resource)
अणु
	अचिन्हित दीर्घ दीर्घ data;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(resource->acpi_dev->handle, "_GHL",
				       शून्य, &data);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_evaluation_failure_warn(resource->acpi_dev->handle, "_GHL",
					     status);
		वापस -ENODEV;
	पूर्ण

	resource->cap = data;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार show_cap(काष्ठा device *dev,
			काष्ठा device_attribute *devattr,
			अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi_dev = to_acpi_device(dev);
	काष्ठा acpi_घातer_meter_resource *resource = acpi_dev->driver_data;

	mutex_lock(&resource->lock);
	update_cap(resource);
	mutex_unlock(&resource->lock);

	वापस प्र_लिखो(buf, "%llu\n", resource->cap * 1000);
पूर्ण

अटल sमाप_प्रकार set_cap(काष्ठा device *dev, काष्ठा device_attribute *devattr,
		       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा acpi_device *acpi_dev = to_acpi_device(dev);
	काष्ठा acpi_घातer_meter_resource *resource = acpi_dev->driver_data;
	जोड़ acpi_object arg0 = अणु ACPI_TYPE_INTEGER पूर्ण;
	काष्ठा acpi_object_list args = अणु 1, &arg0 पूर्ण;
	पूर्णांक res;
	अचिन्हित दीर्घ temp;
	अचिन्हित दीर्घ दीर्घ data;
	acpi_status status;

	res = kम_से_अदीर्घ(buf, 10, &temp);
	अगर (res)
		वापस res;

	temp = DIV_ROUND_CLOSEST(temp, 1000);
	अगर (temp > resource->caps.max_cap || temp < resource->caps.min_cap)
		वापस -EINVAL;
	arg0.पूर्णांकeger.value = temp;

	mutex_lock(&resource->lock);
	status = acpi_evaluate_पूर्णांकeger(resource->acpi_dev->handle, "_SHL",
				       &args, &data);
	अगर (ACPI_SUCCESS(status))
		resource->cap = temp;
	mutex_unlock(&resource->lock);

	अगर (ACPI_FAILURE(status)) अणु
		acpi_evaluation_failure_warn(resource->acpi_dev->handle, "_SHL",
					     status);
		वापस -EINVAL;
	पूर्ण

	/* _SHL वापसs 0 on success, nonzero otherwise */
	अगर (data)
		वापस -EINVAL;

	वापस count;
पूर्ण

/* Power meter trip poपूर्णांकs */
अटल पूर्णांक set_acpi_trip(काष्ठा acpi_घातer_meter_resource *resource)
अणु
	जोड़ acpi_object arg_objs[] = अणु
		अणुACPI_TYPE_INTEGERपूर्ण,
		अणुACPI_TYPE_INTEGERपूर्ण
	पूर्ण;
	काष्ठा acpi_object_list args = अणु 2, arg_objs पूर्ण;
	अचिन्हित दीर्घ दीर्घ data;
	acpi_status status;

	/* Both trip levels must be set */
	अगर (resource->trip[0] < 0 || resource->trip[1] < 0)
		वापस 0;

	/* This driver stores min, max; ACPI wants max, min. */
	arg_objs[0].पूर्णांकeger.value = resource->trip[1];
	arg_objs[1].पूर्णांकeger.value = resource->trip[0];

	status = acpi_evaluate_पूर्णांकeger(resource->acpi_dev->handle, "_PTP",
				       &args, &data);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_evaluation_failure_warn(resource->acpi_dev->handle, "_PTP",
					     status);
		वापस -EINVAL;
	पूर्ण

	/* _PTP वापसs 0 on success, nonzero otherwise */
	अगर (data)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार set_trip(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा acpi_device *acpi_dev = to_acpi_device(dev);
	काष्ठा acpi_घातer_meter_resource *resource = acpi_dev->driver_data;
	पूर्णांक res;
	अचिन्हित दीर्घ temp;

	res = kम_से_अदीर्घ(buf, 10, &temp);
	अगर (res)
		वापस res;

	temp = DIV_ROUND_CLOSEST(temp, 1000);

	mutex_lock(&resource->lock);
	resource->trip[attr->index - 7] = temp;
	res = set_acpi_trip(resource);
	mutex_unlock(&resource->lock);

	अगर (res)
		वापस res;

	वापस count;
पूर्ण

/* Power meter */
अटल पूर्णांक update_meter(काष्ठा acpi_घातer_meter_resource *resource)
अणु
	अचिन्हित दीर्घ दीर्घ data;
	acpi_status status;
	अचिन्हित दीर्घ local_jअगरfies = jअगरfies;

	अगर (समय_beक्रमe(local_jअगरfies, resource->sensors_last_updated +
			msecs_to_jअगरfies(resource->caps.sampling_समय)) &&
			resource->sensors_valid)
		वापस 0;

	status = acpi_evaluate_पूर्णांकeger(resource->acpi_dev->handle, "_PMM",
				       शून्य, &data);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_evaluation_failure_warn(resource->acpi_dev->handle, "_PMM",
					     status);
		वापस -ENODEV;
	पूर्ण

	resource->घातer = data;
	resource->sensors_valid = 1;
	resource->sensors_last_updated = jअगरfies;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार show_घातer(काष्ठा device *dev,
			  काष्ठा device_attribute *devattr,
			  अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi_dev = to_acpi_device(dev);
	काष्ठा acpi_घातer_meter_resource *resource = acpi_dev->driver_data;

	mutex_lock(&resource->lock);
	update_meter(resource);
	mutex_unlock(&resource->lock);

	वापस प्र_लिखो(buf, "%llu\n", resource->घातer * 1000);
पूर्ण

/* Miscellaneous */
अटल sमाप_प्रकार show_str(काष्ठा device *dev,
			काष्ठा device_attribute *devattr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा acpi_device *acpi_dev = to_acpi_device(dev);
	काष्ठा acpi_घातer_meter_resource *resource = acpi_dev->driver_data;
	acpi_string val;
	पूर्णांक ret;

	mutex_lock(&resource->lock);
	चयन (attr->index) अणु
	हाल 0:
		val = resource->model_number;
		अवरोध;
	हाल 1:
		val = resource->serial_number;
		अवरोध;
	हाल 2:
		val = resource->oem_info;
		अवरोध;
	शेष:
		WARN(1, "Implementation error: unexpected attribute index %d\n",
		     attr->index);
		val = "";
		अवरोध;
	पूर्ण
	ret = प्र_लिखो(buf, "%s\n", val);
	mutex_unlock(&resource->lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार show_val(काष्ठा device *dev,
			काष्ठा device_attribute *devattr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा acpi_device *acpi_dev = to_acpi_device(dev);
	काष्ठा acpi_घातer_meter_resource *resource = acpi_dev->driver_data;
	u64 val = 0;

	चयन (attr->index) अणु
	हाल 0:
		val = resource->caps.min_avg_पूर्णांकerval;
		अवरोध;
	हाल 1:
		val = resource->caps.max_avg_पूर्णांकerval;
		अवरोध;
	हाल 2:
		val = resource->caps.min_cap * 1000;
		अवरोध;
	हाल 3:
		val = resource->caps.max_cap * 1000;
		अवरोध;
	हाल 4:
		अगर (resource->caps.hysteresis == UNKNOWN_HYSTERESIS)
			वापस प्र_लिखो(buf, "unknown\n");

		val = resource->caps.hysteresis * 1000;
		अवरोध;
	हाल 5:
		अगर (resource->caps.flags & POWER_METER_IS_BATTERY)
			val = 1;
		अन्यथा
			val = 0;
		अवरोध;
	हाल 6:
		अगर (resource->घातer > resource->cap)
			val = 1;
		अन्यथा
			val = 0;
		अवरोध;
	हाल 7:
	हाल 8:
		अगर (resource->trip[attr->index - 7] < 0)
			वापस प्र_लिखो(buf, "unknown\n");

		val = resource->trip[attr->index - 7] * 1000;
		अवरोध;
	शेष:
		WARN(1, "Implementation error: unexpected attribute index %d\n",
		     attr->index);
		अवरोध;
	पूर्ण

	वापस प्र_लिखो(buf, "%llu\n", val);
पूर्ण

अटल sमाप_प्रकार show_accuracy(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr,
			     अक्षर *buf)
अणु
	काष्ठा acpi_device *acpi_dev = to_acpi_device(dev);
	काष्ठा acpi_घातer_meter_resource *resource = acpi_dev->driver_data;
	अचिन्हित पूर्णांक acc = resource->caps.accuracy;

	वापस प्र_लिखो(buf, "%u.%u%%\n", acc / 1000, acc % 1000);
पूर्ण

अटल sमाप_प्रकार show_name(काष्ठा device *dev,
			 काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", ACPI_POWER_METER_NAME);
पूर्ण

#घोषणा RO_SENSOR_TEMPLATE(_label, _show, _index)	\
	अणु						\
		.label = _label,			\
		.show  = _show,				\
		.index = _index,			\
	पूर्ण

#घोषणा RW_SENSOR_TEMPLATE(_label, _show, _set, _index)	\
	अणु						\
		.label = _label,			\
		.show  = _show,				\
		.set   = _set,				\
		.index = _index,			\
	पूर्ण

/* Sensor descriptions.  If you add a sensor, update NUM_SENSORS above! */
अटल काष्ठा sensor_ढाँचा meter_attrs[] = अणु
	RO_SENSOR_TEMPLATE(POWER_AVERAGE_NAME, show_घातer, 0),
	RO_SENSOR_TEMPLATE("power1_accuracy", show_accuracy, 0),
	RO_SENSOR_TEMPLATE("power1_average_interval_min", show_val, 0),
	RO_SENSOR_TEMPLATE("power1_average_interval_max", show_val, 1),
	RO_SENSOR_TEMPLATE("power1_is_battery", show_val, 5),
	RW_SENSOR_TEMPLATE(POWER_AVG_INTERVAL_NAME, show_avg_पूर्णांकerval,
		set_avg_पूर्णांकerval, 0),
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा sensor_ढाँचा misc_cap_attrs[] = अणु
	RO_SENSOR_TEMPLATE("power1_cap_min", show_val, 2),
	RO_SENSOR_TEMPLATE("power1_cap_max", show_val, 3),
	RO_SENSOR_TEMPLATE("power1_cap_hyst", show_val, 4),
	RO_SENSOR_TEMPLATE(POWER_ALARM_NAME, show_val, 6),
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा sensor_ढाँचा ro_cap_attrs[] = अणु
	RO_SENSOR_TEMPLATE(POWER_CAP_NAME, show_cap, 0),
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा sensor_ढाँचा rw_cap_attrs[] = अणु
	RW_SENSOR_TEMPLATE(POWER_CAP_NAME, show_cap, set_cap, 0),
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा sensor_ढाँचा trip_attrs[] = अणु
	RW_SENSOR_TEMPLATE("power1_average_min", show_val, set_trip, 7),
	RW_SENSOR_TEMPLATE("power1_average_max", show_val, set_trip, 8),
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा sensor_ढाँचा misc_attrs[] = अणु
	RO_SENSOR_TEMPLATE("name", show_name, 0),
	RO_SENSOR_TEMPLATE("power1_model_number", show_str, 0),
	RO_SENSOR_TEMPLATE("power1_oem_info", show_str, 2),
	RO_SENSOR_TEMPLATE("power1_serial_number", show_str, 1),
	अणुपूर्ण,
पूर्ण;

#अघोषित RO_SENSOR_TEMPLATE
#अघोषित RW_SENSOR_TEMPLATE

/* Read घातer करोमुख्य data */
अटल व्योम हटाओ_करोमुख्य_devices(काष्ठा acpi_घातer_meter_resource *resource)
अणु
	पूर्णांक i;

	अगर (!resource->num_करोमुख्य_devices)
		वापस;

	क्रम (i = 0; i < resource->num_करोमुख्य_devices; i++) अणु
		काष्ठा acpi_device *obj = resource->करोमुख्य_devices[i];
		अगर (!obj)
			जारी;

		sysfs_हटाओ_link(resource->holders_dir,
				  kobject_name(&obj->dev.kobj));
		put_device(&obj->dev);
	पूर्ण

	kमुक्त(resource->करोमुख्य_devices);
	kobject_put(resource->holders_dir);
	resource->num_करोमुख्य_devices = 0;
पूर्ण

अटल पूर्णांक पढ़ो_करोमुख्य_devices(काष्ठा acpi_घातer_meter_resource *resource)
अणु
	पूर्णांक res = 0;
	पूर्णांक i;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	जोड़ acpi_object *pss;
	acpi_status status;

	status = acpi_evaluate_object(resource->acpi_dev->handle, "_PMD", शून्य,
				      &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_evaluation_failure_warn(resource->acpi_dev->handle, "_PMD",
					     status);
		वापस -ENODEV;
	पूर्ण

	pss = buffer.poपूर्णांकer;
	अगर (!pss ||
	    pss->type != ACPI_TYPE_PACKAGE) अणु
		dev_err(&resource->acpi_dev->dev, ACPI_POWER_METER_NAME
			"Invalid _PMD data\n");
		res = -EFAULT;
		जाओ end;
	पूर्ण

	अगर (!pss->package.count)
		जाओ end;

	resource->करोमुख्य_devices = kसुस्मृति(pss->package.count,
					   माप(काष्ठा acpi_device *),
					   GFP_KERNEL);
	अगर (!resource->करोमुख्य_devices) अणु
		res = -ENOMEM;
		जाओ end;
	पूर्ण

	resource->holders_dir = kobject_create_and_add("measures",
					&resource->acpi_dev->dev.kobj);
	अगर (!resource->holders_dir) अणु
		res = -ENOMEM;
		जाओ निकास_मुक्त;
	पूर्ण

	resource->num_करोमुख्य_devices = pss->package.count;

	क्रम (i = 0; i < pss->package.count; i++) अणु
		काष्ठा acpi_device *obj;
		जोड़ acpi_object *element = &(pss->package.elements[i]);

		/* Refuse non-references */
		अगर (element->type != ACPI_TYPE_LOCAL_REFERENCE)
			जारी;

		/* Create a symlink to करोमुख्य objects */
		resource->करोमुख्य_devices[i] = शून्य;
		अगर (acpi_bus_get_device(element->reference.handle,
					&resource->करोमुख्य_devices[i]))
			जारी;

		obj = resource->करोमुख्य_devices[i];
		get_device(&obj->dev);

		res = sysfs_create_link(resource->holders_dir, &obj->dev.kobj,
				      kobject_name(&obj->dev.kobj));
		अगर (res) अणु
			put_device(&obj->dev);
			resource->करोमुख्य_devices[i] = शून्य;
		पूर्ण
	पूर्ण

	res = 0;
	जाओ end;

निकास_मुक्त:
	kमुक्त(resource->करोमुख्य_devices);
end:
	kमुक्त(buffer.poपूर्णांकer);
	वापस res;
पूर्ण

/* Registration and deregistration */
अटल पूर्णांक रेजिस्टर_attrs(काष्ठा acpi_घातer_meter_resource *resource,
			  काष्ठा sensor_ढाँचा *attrs)
अणु
	काष्ठा device *dev = &resource->acpi_dev->dev;
	काष्ठा sensor_device_attribute *sensors =
		&resource->sensors[resource->num_sensors];
	पूर्णांक res = 0;

	जबतक (attrs->label) अणु
		sensors->dev_attr.attr.name = attrs->label;
		sensors->dev_attr.attr.mode = 0444;
		sensors->dev_attr.show = attrs->show;
		sensors->index = attrs->index;

		अगर (attrs->set) अणु
			sensors->dev_attr.attr.mode |= 0200;
			sensors->dev_attr.store = attrs->set;
		पूर्ण

		sysfs_attr_init(&sensors->dev_attr.attr);
		res = device_create_file(dev, &sensors->dev_attr);
		अगर (res) अणु
			sensors->dev_attr.attr.name = शून्य;
			जाओ error;
		पूर्ण
		sensors++;
		resource->num_sensors++;
		attrs++;
	पूर्ण

error:
	वापस res;
पूर्ण

अटल व्योम हटाओ_attrs(काष्ठा acpi_घातer_meter_resource *resource)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < resource->num_sensors; i++) अणु
		अगर (!resource->sensors[i].dev_attr.attr.name)
			जारी;
		device_हटाओ_file(&resource->acpi_dev->dev,
				   &resource->sensors[i].dev_attr);
	पूर्ण

	हटाओ_करोमुख्य_devices(resource);

	resource->num_sensors = 0;
पूर्ण

अटल पूर्णांक setup_attrs(काष्ठा acpi_घातer_meter_resource *resource)
अणु
	पूर्णांक res = 0;

	res = पढ़ो_करोमुख्य_devices(resource);
	अगर (res)
		वापस res;

	अगर (resource->caps.flags & POWER_METER_CAN_MEASURE) अणु
		res = रेजिस्टर_attrs(resource, meter_attrs);
		अगर (res)
			जाओ error;
	पूर्ण

	अगर (resource->caps.flags & POWER_METER_CAN_CAP) अणु
		अगर (!can_cap_in_hardware()) अणु
			dev_warn(&resource->acpi_dev->dev,
				 "Ignoring unsafe software power cap!\n");
			जाओ skip_unsafe_cap;
		पूर्ण

		अगर (resource->caps.configurable_cap)
			res = रेजिस्टर_attrs(resource, rw_cap_attrs);
		अन्यथा
			res = रेजिस्टर_attrs(resource, ro_cap_attrs);

		अगर (res)
			जाओ error;

		res = रेजिस्टर_attrs(resource, misc_cap_attrs);
		अगर (res)
			जाओ error;
	पूर्ण

skip_unsafe_cap:
	अगर (resource->caps.flags & POWER_METER_CAN_TRIP) अणु
		res = रेजिस्टर_attrs(resource, trip_attrs);
		अगर (res)
			जाओ error;
	पूर्ण

	res = रेजिस्टर_attrs(resource, misc_attrs);
	अगर (res)
		जाओ error;

	वापस res;
error:
	हटाओ_attrs(resource);
	वापस res;
पूर्ण

अटल व्योम मुक्त_capabilities(काष्ठा acpi_घातer_meter_resource *resource)
अणु
	acpi_string *str;
	पूर्णांक i;

	str = &resource->model_number;
	क्रम (i = 0; i < 3; i++, str++) अणु
		kमुक्त(*str);
		*str = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक पढ़ो_capabilities(काष्ठा acpi_घातer_meter_resource *resource)
अणु
	पूर्णांक res = 0;
	पूर्णांक i;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;
	काष्ठा acpi_buffer state = अणु 0, शून्य पूर्ण;
	काष्ठा acpi_buffer क्रमmat = अणु माप("NNNNNNNNNNN"), "NNNNNNNNNNN" पूर्ण;
	जोड़ acpi_object *pss;
	acpi_string *str;
	acpi_status status;

	status = acpi_evaluate_object(resource->acpi_dev->handle, "_PMC", शून्य,
				      &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_evaluation_failure_warn(resource->acpi_dev->handle, "_PMC",
					     status);
		वापस -ENODEV;
	पूर्ण

	pss = buffer.poपूर्णांकer;
	अगर (!pss ||
	    pss->type != ACPI_TYPE_PACKAGE ||
	    pss->package.count != 14) अणु
		dev_err(&resource->acpi_dev->dev, ACPI_POWER_METER_NAME
			"Invalid _PMC data\n");
		res = -EFAULT;
		जाओ end;
	पूर्ण

	/* Grab all the पूर्णांकeger data at once */
	state.length = माप(काष्ठा acpi_घातer_meter_capabilities);
	state.poपूर्णांकer = &resource->caps;

	status = acpi_extract_package(pss, &क्रमmat, &state);
	अगर (ACPI_FAILURE(status)) अणु
		dev_err(&resource->acpi_dev->dev, ACPI_POWER_METER_NAME
			"_PMC package parsing failed: %s\n",
			acpi_क्रमmat_exception(status));
		res = -EFAULT;
		जाओ end;
	पूर्ण

	अगर (resource->caps.units) अणु
		dev_err(&resource->acpi_dev->dev, ACPI_POWER_METER_NAME
			"Unknown units %llu.\n",
			resource->caps.units);
		res = -EINVAL;
		जाओ end;
	पूर्ण

	/* Grab the string data */
	str = &resource->model_number;

	क्रम (i = 11; i < 14; i++) अणु
		जोड़ acpi_object *element = &(pss->package.elements[i]);

		अगर (element->type != ACPI_TYPE_STRING) अणु
			res = -EINVAL;
			जाओ error;
		पूर्ण

		*str = kसुस्मृति(element->string.length + 1, माप(u8),
			       GFP_KERNEL);
		अगर (!*str) अणु
			res = -ENOMEM;
			जाओ error;
		पूर्ण

		म_नकलन(*str, element->string.poपूर्णांकer, element->string.length);
		str++;
	पूर्ण

	dev_info(&resource->acpi_dev->dev, "Found ACPI power meter.\n");
	जाओ end;
error:
	मुक्त_capabilities(resource);
end:
	kमुक्त(buffer.poपूर्णांकer);
	वापस res;
पूर्ण

/* Handle ACPI event notअगरications */
अटल व्योम acpi_घातer_meter_notअगरy(काष्ठा acpi_device *device, u32 event)
अणु
	काष्ठा acpi_घातer_meter_resource *resource;
	पूर्णांक res;

	अगर (!device || !acpi_driver_data(device))
		वापस;

	resource = acpi_driver_data(device);

	चयन (event) अणु
	हाल METER_NOTIFY_CONFIG:
		mutex_lock(&resource->lock);
		मुक्त_capabilities(resource);
		res = पढ़ो_capabilities(resource);
		mutex_unlock(&resource->lock);
		अगर (res)
			अवरोध;

		हटाओ_attrs(resource);
		setup_attrs(resource);
		अवरोध;
	हाल METER_NOTIFY_TRIP:
		sysfs_notअगरy(&device->dev.kobj, शून्य, POWER_AVERAGE_NAME);
		अवरोध;
	हाल METER_NOTIFY_CAP:
		sysfs_notअगरy(&device->dev.kobj, शून्य, POWER_CAP_NAME);
		अवरोध;
	हाल METER_NOTIFY_INTERVAL:
		sysfs_notअगरy(&device->dev.kobj, शून्य, POWER_AVG_INTERVAL_NAME);
		अवरोध;
	हाल METER_NOTIFY_CAPPING:
		sysfs_notअगरy(&device->dev.kobj, शून्य, POWER_ALARM_NAME);
		dev_info(&device->dev, "Capping in progress.\n");
		अवरोध;
	शेष:
		WARN(1, "Unexpected event %d\n", event);
		अवरोध;
	पूर्ण

	acpi_bus_generate_netlink_event(ACPI_POWER_METER_CLASS,
					dev_name(&device->dev), event, 0);
पूर्ण

अटल पूर्णांक acpi_घातer_meter_add(काष्ठा acpi_device *device)
अणु
	पूर्णांक res;
	काष्ठा acpi_घातer_meter_resource *resource;

	अगर (!device)
		वापस -EINVAL;

	resource = kzalloc(माप(काष्ठा acpi_घातer_meter_resource),
			   GFP_KERNEL);
	अगर (!resource)
		वापस -ENOMEM;

	resource->sensors_valid = 0;
	resource->acpi_dev = device;
	mutex_init(&resource->lock);
	म_नकल(acpi_device_name(device), ACPI_POWER_METER_DEVICE_NAME);
	म_नकल(acpi_device_class(device), ACPI_POWER_METER_CLASS);
	device->driver_data = resource;

	res = पढ़ो_capabilities(resource);
	अगर (res)
		जाओ निकास_मुक्त;

	resource->trip[0] = resource->trip[1] = -1;

	res = setup_attrs(resource);
	अगर (res)
		जाओ निकास_मुक्त_capability;

	resource->hwmon_dev = hwmon_device_रेजिस्टर(&device->dev);
	अगर (IS_ERR(resource->hwmon_dev)) अणु
		res = PTR_ERR(resource->hwmon_dev);
		जाओ निकास_हटाओ;
	पूर्ण

	res = 0;
	जाओ निकास;

निकास_हटाओ:
	हटाओ_attrs(resource);
निकास_मुक्त_capability:
	मुक्त_capabilities(resource);
निकास_मुक्त:
	kमुक्त(resource);
निकास:
	वापस res;
पूर्ण

अटल पूर्णांक acpi_घातer_meter_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा acpi_घातer_meter_resource *resource;

	अगर (!device || !acpi_driver_data(device))
		वापस -EINVAL;

	resource = acpi_driver_data(device);
	hwmon_device_unरेजिस्टर(resource->hwmon_dev);

	हटाओ_attrs(resource);
	मुक्त_capabilities(resource);

	kमुक्त(resource);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक acpi_घातer_meter_resume(काष्ठा device *dev)
अणु
	काष्ठा acpi_घातer_meter_resource *resource;

	अगर (!dev)
		वापस -EINVAL;

	resource = acpi_driver_data(to_acpi_device(dev));
	अगर (!resource)
		वापस -EINVAL;

	मुक्त_capabilities(resource);
	पढ़ो_capabilities(resource);

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल SIMPLE_DEV_PM_OPS(acpi_घातer_meter_pm, शून्य, acpi_घातer_meter_resume);

अटल काष्ठा acpi_driver acpi_घातer_meter_driver = अणु
	.name = "power_meter",
	.class = ACPI_POWER_METER_CLASS,
	.ids = घातer_meter_ids,
	.ops = अणु
		.add = acpi_घातer_meter_add,
		.हटाओ = acpi_घातer_meter_हटाओ,
		.notअगरy = acpi_घातer_meter_notअगरy,
		पूर्ण,
	.drv.pm = &acpi_घातer_meter_pm,
पूर्ण;

/* Module init/निकास routines */
अटल पूर्णांक __init enable_cap_knobs(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	cap_in_hardware = 1;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id pm_dmi_table[] __initस्थिर = अणु
	अणु
		enable_cap_knobs, "IBM Active Energy Manager",
		अणु
			DMI_MATCH(DMI_SYS_VENDOR, "IBM")
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक __init acpi_घातer_meter_init(व्योम)
अणु
	पूर्णांक result;

	अगर (acpi_disabled)
		वापस -ENODEV;

	dmi_check_प्रणाली(pm_dmi_table);

	result = acpi_bus_रेजिस्टर_driver(&acpi_घातer_meter_driver);
	अगर (result < 0)
		वापस result;

	वापस 0;
पूर्ण

अटल व्योम __निकास acpi_घातer_meter_निकास(व्योम)
अणु
	acpi_bus_unरेजिस्टर_driver(&acpi_घातer_meter_driver);
पूर्ण

MODULE_AUTHOR("Darrick J. Wong <darrick.wong@oracle.com>");
MODULE_DESCRIPTION("ACPI 4.0 power meter driver");
MODULE_LICENSE("GPL");

module_param(क्रमce_cap_on, bool, 0644);
MODULE_PARM_DESC(क्रमce_cap_on, "Enable power cap even it is unsafe to do so.");

module_init(acpi_घातer_meter_init);
module_निकास(acpi_घातer_meter_निकास);
