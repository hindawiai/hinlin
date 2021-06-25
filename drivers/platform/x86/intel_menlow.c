<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Intel menlow Driver क्रम thermal management extension
 *
 *  Copyright (C) 2008 Intel Corp
 *  Copyright (C) 2008 Sujith Thomas <sujith.thomas@पूर्णांकel.com>
 *  Copyright (C) 2008 Zhang Rui <rui.zhang@पूर्णांकel.com>
 *
 *  This driver creates the sys I/F क्रम programming the sensors.
 *  It also implements the driver क्रम पूर्णांकel menlow memory controller (hardware
 *  id is INT0002) which makes use of the platक्रमm specअगरic ACPI methods
 *  to get/set bandwidth.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm.h>
#समावेश <linux/slab.h>
#समावेश <linux/thermal.h>
#समावेश <linux/types.h>
#समावेश <linux/units.h>

MODULE_AUTHOR("Thomas Sujith");
MODULE_AUTHOR("Zhang Rui");
MODULE_DESCRIPTION("Intel Menlow platform specific driver");
MODULE_LICENSE("GPL v2");

/*
 * Memory controller device control
 */

#घोषणा MEMORY_GET_BANDWIDTH "GTHS"
#घोषणा MEMORY_SET_BANDWIDTH "STHS"
#घोषणा MEMORY_ARG_CUR_BANDWIDTH 1
#घोषणा MEMORY_ARG_MAX_BANDWIDTH 0

अटल व्योम पूर्णांकel_menlow_unरेजिस्टर_sensor(व्योम);

/*
 * GTHS वापसing 'n' would mean that [0,n-1] states are supported
 * In that हाल max_cstate would be n-1
 * GTHS वापसing '0' would mean that no bandwidth control states are supported
 */
अटल पूर्णांक memory_get_max_bandwidth(काष्ठा thermal_cooling_device *cdev,
				    अचिन्हित दीर्घ *max_state)
अणु
	काष्ठा acpi_device *device = cdev->devdata;
	acpi_handle handle = device->handle;
	अचिन्हित दीर्घ दीर्घ value;
	काष्ठा acpi_object_list arg_list;
	जोड़ acpi_object arg;
	acpi_status status = AE_OK;

	arg_list.count = 1;
	arg_list.poपूर्णांकer = &arg;
	arg.type = ACPI_TYPE_INTEGER;
	arg.पूर्णांकeger.value = MEMORY_ARG_MAX_BANDWIDTH;
	status = acpi_evaluate_पूर्णांकeger(handle, MEMORY_GET_BANDWIDTH,
				       &arg_list, &value);
	अगर (ACPI_FAILURE(status))
		वापस -EFAULT;

	अगर (!value)
		वापस -EINVAL;

	*max_state = value - 1;
	वापस 0;
पूर्ण

अटल पूर्णांक memory_get_cur_bandwidth(काष्ठा thermal_cooling_device *cdev,
				    अचिन्हित दीर्घ *value)
अणु
	काष्ठा acpi_device *device = cdev->devdata;
	acpi_handle handle = device->handle;
	अचिन्हित दीर्घ दीर्घ result;
	काष्ठा acpi_object_list arg_list;
	जोड़ acpi_object arg;
	acpi_status status = AE_OK;

	arg_list.count = 1;
	arg_list.poपूर्णांकer = &arg;
	arg.type = ACPI_TYPE_INTEGER;
	arg.पूर्णांकeger.value = MEMORY_ARG_CUR_BANDWIDTH;
	status = acpi_evaluate_पूर्णांकeger(handle, MEMORY_GET_BANDWIDTH,
				       &arg_list, &result);
	अगर (ACPI_FAILURE(status))
		वापस -EFAULT;

	*value = result;
	वापस 0;
पूर्ण

अटल पूर्णांक memory_set_cur_bandwidth(काष्ठा thermal_cooling_device *cdev,
				    अचिन्हित दीर्घ state)
अणु
	काष्ठा acpi_device *device = cdev->devdata;
	acpi_handle handle = device->handle;
	काष्ठा acpi_object_list arg_list;
	जोड़ acpi_object arg;
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ temp;
	अचिन्हित दीर्घ max_state;

	अगर (memory_get_max_bandwidth(cdev, &max_state))
		वापस -EFAULT;

	अगर (state > max_state)
		वापस -EINVAL;

	arg_list.count = 1;
	arg_list.poपूर्णांकer = &arg;
	arg.type = ACPI_TYPE_INTEGER;
	arg.पूर्णांकeger.value = state;

	status =
	    acpi_evaluate_पूर्णांकeger(handle, MEMORY_SET_BANDWIDTH, &arg_list,
				  &temp);

	pr_info("Bandwidth value was %ld: status is %d\n", state, status);
	अगर (ACPI_FAILURE(status))
		वापस -EFAULT;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_cooling_device_ops memory_cooling_ops = अणु
	.get_max_state = memory_get_max_bandwidth,
	.get_cur_state = memory_get_cur_bandwidth,
	.set_cur_state = memory_set_cur_bandwidth,
पूर्ण;

/*
 * Memory Device Management
 */
अटल पूर्णांक पूर्णांकel_menlow_memory_add(काष्ठा acpi_device *device)
अणु
	पूर्णांक result = -ENODEV;
	काष्ठा thermal_cooling_device *cdev;

	अगर (!device)
		वापस -EINVAL;

	अगर (!acpi_has_method(device->handle, MEMORY_GET_BANDWIDTH))
		जाओ end;

	अगर (!acpi_has_method(device->handle, MEMORY_SET_BANDWIDTH))
		जाओ end;

	cdev = thermal_cooling_device_रेजिस्टर("Memory controller", device,
					       &memory_cooling_ops);
	अगर (IS_ERR(cdev)) अणु
		result = PTR_ERR(cdev);
		जाओ end;
	पूर्ण

	device->driver_data = cdev;
	result = sysfs_create_link(&device->dev.kobj,
				&cdev->device.kobj, "thermal_cooling");
	अगर (result)
		जाओ unरेजिस्टर;

	result = sysfs_create_link(&cdev->device.kobj,
				&device->dev.kobj, "device");
	अगर (result) अणु
		sysfs_हटाओ_link(&device->dev.kobj, "thermal_cooling");
		जाओ unरेजिस्टर;
	पूर्ण

 end:
	वापस result;

 unरेजिस्टर:
	thermal_cooling_device_unरेजिस्टर(cdev);
	वापस result;

पूर्ण

अटल पूर्णांक पूर्णांकel_menlow_memory_हटाओ(काष्ठा acpi_device *device)
अणु
	काष्ठा thermal_cooling_device *cdev;

	अगर (!device)
		वापस -EINVAL;

	cdev = acpi_driver_data(device);
	अगर (!cdev)
		वापस -EINVAL;

	sysfs_हटाओ_link(&device->dev.kobj, "thermal_cooling");
	sysfs_हटाओ_link(&cdev->device.kobj, "device");
	thermal_cooling_device_unरेजिस्टर(cdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा acpi_device_id पूर्णांकel_menlow_memory_ids[] = अणु
	अणु"INT0002", 0पूर्ण,
	अणु"", 0पूर्ण,
पूर्ण;

अटल काष्ठा acpi_driver पूर्णांकel_menlow_memory_driver = अणु
	.name = "intel_menlow_thermal_control",
	.ids = पूर्णांकel_menlow_memory_ids,
	.ops = अणु
		.add = पूर्णांकel_menlow_memory_add,
		.हटाओ = पूर्णांकel_menlow_memory_हटाओ,
		पूर्ण,
पूर्ण;

/*
 * Sensor control on menlow platक्रमm
 */

#घोषणा THERMAL_AUX0 0
#घोषणा THERMAL_AUX1 1
#घोषणा GET_AUX0 "GAX0"
#घोषणा GET_AUX1 "GAX1"
#घोषणा SET_AUX0 "SAX0"
#घोषणा SET_AUX1 "SAX1"

काष्ठा पूर्णांकel_menlow_attribute अणु
	काष्ठा device_attribute attr;
	काष्ठा device *device;
	acpi_handle handle;
	काष्ठा list_head node;
पूर्ण;

अटल LIST_HEAD(पूर्णांकel_menlow_attr_list);
अटल DEFINE_MUTEX(पूर्णांकel_menlow_attr_lock);

/*
 * sensor_get_auxtrip - get the current auxtrip value from sensor
 * @name: Thermalzone name
 * @auxtype : AUX0/AUX1
 * @buf: syfs buffer
 */
अटल पूर्णांक sensor_get_auxtrip(acpi_handle handle, पूर्णांक index,
							अचिन्हित दीर्घ दीर्घ *value)
अणु
	acpi_status status;

	अगर ((index != 0 && index != 1) || !value)
		वापस -EINVAL;

	status = acpi_evaluate_पूर्णांकeger(handle, index ? GET_AUX1 : GET_AUX0,
				       शून्य, value);
	अगर (ACPI_FAILURE(status))
		वापस -EIO;

	वापस 0;
पूर्ण

/*
 * sensor_set_auxtrip - set the new auxtrip value to sensor
 * @name: Thermalzone name
 * @auxtype : AUX0/AUX1
 * @buf: syfs buffer
 */
अटल पूर्णांक sensor_set_auxtrip(acpi_handle handle, पूर्णांक index, पूर्णांक value)
अणु
	acpi_status status;
	जोड़ acpi_object arg = अणु
		ACPI_TYPE_INTEGER
	पूर्ण;
	काष्ठा acpi_object_list args = अणु
		1, &arg
	पूर्ण;
	अचिन्हित दीर्घ दीर्घ temp;

	अगर (index != 0 && index != 1)
		वापस -EINVAL;

	status = acpi_evaluate_पूर्णांकeger(handle, index ? GET_AUX0 : GET_AUX1,
				       शून्य, &temp);
	अगर (ACPI_FAILURE(status))
		वापस -EIO;
	अगर ((index && value < temp) || (!index && value > temp))
		वापस -EINVAL;

	arg.पूर्णांकeger.value = value;
	status = acpi_evaluate_पूर्णांकeger(handle, index ? SET_AUX1 : SET_AUX0,
				       &args, &temp);
	अगर (ACPI_FAILURE(status))
		वापस -EIO;

	/* करो we need to check the वापस value of SAX0/SAX1 ? */

	वापस 0;
पूर्ण

#घोषणा to_पूर्णांकel_menlow_attr(_attr)	\
	container_of(_attr, काष्ठा पूर्णांकel_menlow_attribute, attr)

अटल sमाप_प्रकार aux_show(काष्ठा device *dev, काष्ठा device_attribute *dev_attr,
			अक्षर *buf, पूर्णांक idx)
अणु
	काष्ठा पूर्णांकel_menlow_attribute *attr = to_पूर्णांकel_menlow_attr(dev_attr);
	अचिन्हित दीर्घ दीर्घ value;
	पूर्णांक result;

	result = sensor_get_auxtrip(attr->handle, idx, &value);
	अगर (result)
		वापस result;

	वापस प्र_लिखो(buf, "%lu", deci_kelvin_to_celsius(value));
पूर्ण

अटल sमाप_प्रकार aux0_show(काष्ठा device *dev,
			 काष्ठा device_attribute *dev_attr, अक्षर *buf)
अणु
	वापस aux_show(dev, dev_attr, buf, 0);
पूर्ण

अटल sमाप_प्रकार aux1_show(काष्ठा device *dev,
			 काष्ठा device_attribute *dev_attr, अक्षर *buf)
अणु
	वापस aux_show(dev, dev_attr, buf, 1);
पूर्ण

अटल sमाप_प्रकार aux_store(काष्ठा device *dev, काष्ठा device_attribute *dev_attr,
			 स्थिर अक्षर *buf, माप_प्रकार count, पूर्णांक idx)
अणु
	काष्ठा पूर्णांकel_menlow_attribute *attr = to_पूर्णांकel_menlow_attr(dev_attr);
	पूर्णांक value;
	पूर्णांक result;

	/*Sanity check; should be a positive पूर्णांकeger */
	अगर (!माला_पूछो(buf, "%d", &value))
		वापस -EINVAL;

	अगर (value < 0)
		वापस -EINVAL;

	result = sensor_set_auxtrip(attr->handle, idx,
				    celsius_to_deci_kelvin(value));
	वापस result ? result : count;
पूर्ण

अटल sमाप_प्रकार aux0_store(काष्ठा device *dev,
			  काष्ठा device_attribute *dev_attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस aux_store(dev, dev_attr, buf, count, 0);
पूर्ण

अटल sमाप_प्रकार aux1_store(काष्ठा device *dev,
			  काष्ठा device_attribute *dev_attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस aux_store(dev, dev_attr, buf, count, 1);
पूर्ण

/* BIOS can enable/disable the thermal user application in dabney platक्रमm */
#घोषणा BIOS_ENABLED "\\_TZ.GSTS"
अटल sमाप_प्रकार bios_enabled_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ bios_enabled;

	status = acpi_evaluate_पूर्णांकeger(शून्य, BIOS_ENABLED, शून्य, &bios_enabled);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "%s\n", bios_enabled ? "enabled" : "disabled");
पूर्ण

अटल पूर्णांक पूर्णांकel_menlow_add_one_attribute(अक्षर *name, umode_t mode, व्योम *show,
					  व्योम *store, काष्ठा device *dev,
					  acpi_handle handle)
अणु
	काष्ठा पूर्णांकel_menlow_attribute *attr;
	पूर्णांक result;

	attr = kzalloc(माप(काष्ठा पूर्णांकel_menlow_attribute), GFP_KERNEL);
	अगर (!attr)
		वापस -ENOMEM;

	sysfs_attr_init(&attr->attr.attr); /* That is consistent naming :D */
	attr->attr.attr.name = name;
	attr->attr.attr.mode = mode;
	attr->attr.show = show;
	attr->attr.store = store;
	attr->device = dev;
	attr->handle = handle;

	result = device_create_file(dev, &attr->attr);
	अगर (result) अणु
		kमुक्त(attr);
		वापस result;
	पूर्ण

	mutex_lock(&पूर्णांकel_menlow_attr_lock);
	list_add_tail(&attr->node, &पूर्णांकel_menlow_attr_list);
	mutex_unlock(&पूर्णांकel_menlow_attr_lock);

	वापस 0;
पूर्ण

अटल acpi_status पूर्णांकel_menlow_रेजिस्टर_sensor(acpi_handle handle, u32 lvl,
						व्योम *context, व्योम **rv)
अणु
	acpi_status status;
	acpi_handle dummy;
	काष्ठा thermal_zone_device *thermal;
	पूर्णांक result;

	result = acpi_bus_get_निजी_data(handle, (व्योम **)&thermal);
	अगर (result)
		वापस 0;

	/* _TZ must have the AUX0/1 methods */
	status = acpi_get_handle(handle, GET_AUX0, &dummy);
	अगर (ACPI_FAILURE(status))
		वापस (status == AE_NOT_FOUND) ? AE_OK : status;

	status = acpi_get_handle(handle, SET_AUX0, &dummy);
	अगर (ACPI_FAILURE(status))
		वापस (status == AE_NOT_FOUND) ? AE_OK : status;

	result = पूर्णांकel_menlow_add_one_attribute("aux0", 0644,
						aux0_show, aux0_store,
						&thermal->device, handle);
	अगर (result)
		वापस AE_ERROR;

	status = acpi_get_handle(handle, GET_AUX1, &dummy);
	अगर (ACPI_FAILURE(status))
		जाओ aux1_not_found;

	status = acpi_get_handle(handle, SET_AUX1, &dummy);
	अगर (ACPI_FAILURE(status))
		जाओ aux1_not_found;

	result = पूर्णांकel_menlow_add_one_attribute("aux1", 0644,
						aux1_show, aux1_store,
						&thermal->device, handle);
	अगर (result) अणु
		पूर्णांकel_menlow_unरेजिस्टर_sensor();
		वापस AE_ERROR;
	पूर्ण

	/*
	 * create the "dabney_enabled" attribute which means the user app
	 * should be loaded or not
	 */

	result = पूर्णांकel_menlow_add_one_attribute("bios_enabled", 0444,
						bios_enabled_show, शून्य,
						&thermal->device, handle);
	अगर (result) अणु
		पूर्णांकel_menlow_unरेजिस्टर_sensor();
		वापस AE_ERROR;
	पूर्ण

	वापस AE_OK;

 aux1_not_found:
	अगर (status == AE_NOT_FOUND)
		वापस AE_OK;

	पूर्णांकel_menlow_unरेजिस्टर_sensor();
	वापस status;
पूर्ण

अटल व्योम पूर्णांकel_menlow_unरेजिस्टर_sensor(व्योम)
अणु
	काष्ठा पूर्णांकel_menlow_attribute *pos, *next;

	mutex_lock(&पूर्णांकel_menlow_attr_lock);
	list_क्रम_each_entry_safe(pos, next, &पूर्णांकel_menlow_attr_list, node) अणु
		list_del(&pos->node);
		device_हटाओ_file(pos->device, &pos->attr);
		kमुक्त(pos);
	पूर्ण
	mutex_unlock(&पूर्णांकel_menlow_attr_lock);

	वापस;
पूर्ण

अटल पूर्णांक __init पूर्णांकel_menlow_module_init(व्योम)
अणु
	पूर्णांक result = -ENODEV;
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ enable;

	अगर (acpi_disabled)
		वापस result;

	/* Looking क्रम the \_TZ.GSTS method */
	status = acpi_evaluate_पूर्णांकeger(शून्य, BIOS_ENABLED, शून्य, &enable);
	अगर (ACPI_FAILURE(status) || !enable)
		वापस -ENODEV;

	/* Looking क्रम ACPI device MEM0 with hardware id INT0002 */
	result = acpi_bus_रेजिस्टर_driver(&पूर्णांकel_menlow_memory_driver);
	अगर (result)
		वापस result;

	/* Looking क्रम sensors in each ACPI thermal zone */
	status = acpi_walk_namespace(ACPI_TYPE_THERMAL, ACPI_ROOT_OBJECT,
				     ACPI_UINT32_MAX,
				     पूर्णांकel_menlow_रेजिस्टर_sensor, शून्य, शून्य, शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_bus_unरेजिस्टर_driver(&पूर्णांकel_menlow_memory_driver);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास पूर्णांकel_menlow_module_निकास(व्योम)
अणु
	acpi_bus_unरेजिस्टर_driver(&पूर्णांकel_menlow_memory_driver);
	पूर्णांकel_menlow_unरेजिस्टर_sensor();
पूर्ण

module_init(पूर्णांकel_menlow_module_init);
module_निकास(पूर्णांकel_menlow_module_निकास);
