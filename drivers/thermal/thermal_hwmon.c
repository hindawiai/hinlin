<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  thermal_hwmon.c - Generic Thermal Management hwmon support.
 *
 *  Code based on Intel thermal_core.c. Copyrights of the original code:
 *  Copyright (C) 2008 Intel Corp
 *  Copyright (C) 2008 Zhang Rui <rui.zhang@पूर्णांकel.com>
 *  Copyright (C) 2008 Sujith Thomas <sujith.thomas@पूर्णांकel.com>
 *
 *  Copyright (C) 2013 Texas Instruments
 *  Copyright (C) 2013 Eduarकरो Valentin <eduarकरो.valentin@ti.com>
 */
#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/slab.h>
#समावेश <linux/thermal.h>

#समावेश "thermal_hwmon.h"

/* hwmon sys I/F */
/* thermal zone devices with the same type share one hwmon device */
काष्ठा thermal_hwmon_device अणु
	अक्षर type[THERMAL_NAME_LENGTH];
	काष्ठा device *device;
	पूर्णांक count;
	काष्ठा list_head tz_list;
	काष्ठा list_head node;
पूर्ण;

काष्ठा thermal_hwmon_attr अणु
	काष्ठा device_attribute attr;
	अक्षर name[16];
पूर्ण;

/* one temperature input क्रम each thermal zone */
काष्ठा thermal_hwmon_temp अणु
	काष्ठा list_head hwmon_node;
	काष्ठा thermal_zone_device *tz;
	काष्ठा thermal_hwmon_attr temp_input;	/* hwmon sys attr */
	काष्ठा thermal_hwmon_attr temp_crit;	/* hwmon sys attr */
पूर्ण;

अटल LIST_HEAD(thermal_hwmon_list);

अटल DEFINE_MUTEX(thermal_hwmon_list_lock);

अटल sमाप_प्रकार
temp_input_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक temperature;
	पूर्णांक ret;
	काष्ठा thermal_hwmon_attr *hwmon_attr
			= container_of(attr, काष्ठा thermal_hwmon_attr, attr);
	काष्ठा thermal_hwmon_temp *temp
			= container_of(hwmon_attr, काष्ठा thermal_hwmon_temp,
				       temp_input);
	काष्ठा thermal_zone_device *tz = temp->tz;

	ret = thermal_zone_get_temp(tz, &temperature);

	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", temperature);
पूर्ण

अटल sमाप_प्रकार
temp_crit_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा thermal_hwmon_attr *hwmon_attr
			= container_of(attr, काष्ठा thermal_hwmon_attr, attr);
	काष्ठा thermal_hwmon_temp *temp
			= container_of(hwmon_attr, काष्ठा thermal_hwmon_temp,
				       temp_crit);
	काष्ठा thermal_zone_device *tz = temp->tz;
	पूर्णांक temperature;
	पूर्णांक ret;

	ret = tz->ops->get_crit_temp(tz, &temperature);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", temperature);
पूर्ण


अटल काष्ठा thermal_hwmon_device *
thermal_hwmon_lookup_by_type(स्थिर काष्ठा thermal_zone_device *tz)
अणु
	काष्ठा thermal_hwmon_device *hwmon;
	अक्षर type[THERMAL_NAME_LENGTH];

	mutex_lock(&thermal_hwmon_list_lock);
	list_क्रम_each_entry(hwmon, &thermal_hwmon_list, node) अणु
		म_नकल(type, tz->type);
		strreplace(type, '-', '_');
		अगर (!म_भेद(hwmon->type, type)) अणु
			mutex_unlock(&thermal_hwmon_list_lock);
			वापस hwmon;
		पूर्ण
	पूर्ण
	mutex_unlock(&thermal_hwmon_list_lock);

	वापस शून्य;
पूर्ण

/* Find the temperature input matching a given thermal zone */
अटल काष्ठा thermal_hwmon_temp *
thermal_hwmon_lookup_temp(स्थिर काष्ठा thermal_hwmon_device *hwmon,
			  स्थिर काष्ठा thermal_zone_device *tz)
अणु
	काष्ठा thermal_hwmon_temp *temp;

	mutex_lock(&thermal_hwmon_list_lock);
	list_क्रम_each_entry(temp, &hwmon->tz_list, hwmon_node)
		अगर (temp->tz == tz) अणु
			mutex_unlock(&thermal_hwmon_list_lock);
			वापस temp;
		पूर्ण
	mutex_unlock(&thermal_hwmon_list_lock);

	वापस शून्य;
पूर्ण

अटल bool thermal_zone_crit_temp_valid(काष्ठा thermal_zone_device *tz)
अणु
	पूर्णांक temp;
	वापस tz->ops->get_crit_temp && !tz->ops->get_crit_temp(tz, &temp);
पूर्ण

पूर्णांक thermal_add_hwmon_sysfs(काष्ठा thermal_zone_device *tz)
अणु
	काष्ठा thermal_hwmon_device *hwmon;
	काष्ठा thermal_hwmon_temp *temp;
	पूर्णांक new_hwmon_device = 1;
	पूर्णांक result;

	hwmon = thermal_hwmon_lookup_by_type(tz);
	अगर (hwmon) अणु
		new_hwmon_device = 0;
		जाओ रेजिस्टर_sys_पूर्णांकerface;
	पूर्ण

	hwmon = kzalloc(माप(*hwmon), GFP_KERNEL);
	अगर (!hwmon)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&hwmon->tz_list);
	strlcpy(hwmon->type, tz->type, THERMAL_NAME_LENGTH);
	strreplace(hwmon->type, '-', '_');
	hwmon->device = hwmon_device_रेजिस्टर_with_info(&tz->device, hwmon->type,
							hwmon, शून्य, शून्य);
	अगर (IS_ERR(hwmon->device)) अणु
		result = PTR_ERR(hwmon->device);
		जाओ मुक्त_mem;
	पूर्ण

 रेजिस्टर_sys_पूर्णांकerface:
	temp = kzalloc(माप(*temp), GFP_KERNEL);
	अगर (!temp) अणु
		result = -ENOMEM;
		जाओ unरेजिस्टर_name;
	पूर्ण

	temp->tz = tz;
	hwmon->count++;

	snम_लिखो(temp->temp_input.name, माप(temp->temp_input.name),
		 "temp%d_input", hwmon->count);
	temp->temp_input.attr.attr.name = temp->temp_input.name;
	temp->temp_input.attr.attr.mode = 0444;
	temp->temp_input.attr.show = temp_input_show;
	sysfs_attr_init(&temp->temp_input.attr.attr);
	result = device_create_file(hwmon->device, &temp->temp_input.attr);
	अगर (result)
		जाओ मुक्त_temp_mem;

	अगर (thermal_zone_crit_temp_valid(tz)) अणु
		snम_लिखो(temp->temp_crit.name,
				माप(temp->temp_crit.name),
				"temp%d_crit", hwmon->count);
		temp->temp_crit.attr.attr.name = temp->temp_crit.name;
		temp->temp_crit.attr.attr.mode = 0444;
		temp->temp_crit.attr.show = temp_crit_show;
		sysfs_attr_init(&temp->temp_crit.attr.attr);
		result = device_create_file(hwmon->device,
					    &temp->temp_crit.attr);
		अगर (result)
			जाओ unरेजिस्टर_input;
	पूर्ण

	mutex_lock(&thermal_hwmon_list_lock);
	अगर (new_hwmon_device)
		list_add_tail(&hwmon->node, &thermal_hwmon_list);
	list_add_tail(&temp->hwmon_node, &hwmon->tz_list);
	mutex_unlock(&thermal_hwmon_list_lock);

	वापस 0;

 unरेजिस्टर_input:
	device_हटाओ_file(hwmon->device, &temp->temp_input.attr);
 मुक्त_temp_mem:
	kमुक्त(temp);
 unरेजिस्टर_name:
	अगर (new_hwmon_device)
		hwmon_device_unरेजिस्टर(hwmon->device);
 मुक्त_mem:
	kमुक्त(hwmon);

	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(thermal_add_hwmon_sysfs);

व्योम thermal_हटाओ_hwmon_sysfs(काष्ठा thermal_zone_device *tz)
अणु
	काष्ठा thermal_hwmon_device *hwmon;
	काष्ठा thermal_hwmon_temp *temp;

	hwmon = thermal_hwmon_lookup_by_type(tz);
	अगर (unlikely(!hwmon)) अणु
		/* Should never happen... */
		dev_dbg(&tz->device, "hwmon device lookup failed!\n");
		वापस;
	पूर्ण

	temp = thermal_hwmon_lookup_temp(hwmon, tz);
	अगर (unlikely(!temp)) अणु
		/* Should never happen... */
		dev_dbg(&tz->device, "temperature input lookup failed!\n");
		वापस;
	पूर्ण

	device_हटाओ_file(hwmon->device, &temp->temp_input.attr);
	अगर (thermal_zone_crit_temp_valid(tz))
		device_हटाओ_file(hwmon->device, &temp->temp_crit.attr);

	mutex_lock(&thermal_hwmon_list_lock);
	list_del(&temp->hwmon_node);
	kमुक्त(temp);
	अगर (!list_empty(&hwmon->tz_list)) अणु
		mutex_unlock(&thermal_hwmon_list_lock);
		वापस;
	पूर्ण
	list_del(&hwmon->node);
	mutex_unlock(&thermal_hwmon_list_lock);

	hwmon_device_unरेजिस्टर(hwmon->device);
	kमुक्त(hwmon);
पूर्ण
EXPORT_SYMBOL_GPL(thermal_हटाओ_hwmon_sysfs);

अटल व्योम devm_thermal_hwmon_release(काष्ठा device *dev, व्योम *res)
अणु
	thermal_हटाओ_hwmon_sysfs(*(काष्ठा thermal_zone_device **)res);
पूर्ण

पूर्णांक devm_thermal_add_hwmon_sysfs(काष्ठा thermal_zone_device *tz)
अणु
	काष्ठा thermal_zone_device **ptr;
	पूर्णांक ret;

	ptr = devres_alloc(devm_thermal_hwmon_release, माप(*ptr),
			   GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	ret = thermal_add_hwmon_sysfs(tz);
	अगर (ret) अणु
		devres_मुक्त(ptr);
		वापस ret;
	पूर्ण

	*ptr = tz;
	devres_add(&tz->device, ptr);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(devm_thermal_add_hwmon_sysfs);
