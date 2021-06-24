<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * hwmon.c - part of lm_sensors, Linux kernel modules क्रम hardware monitoring
 *
 * This file defines the sysfs class "hwmon", क्रम use by sensors drivers.
 *
 * Copyright (C) 2005 Mark M. Hoffman <mhoffman@lightlink.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/bitops.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/gfp.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/idr.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/thermal.h>

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/hwmon.h>

#घोषणा HWMON_ID_PREFIX "hwmon"
#घोषणा HWMON_ID_FORMAT HWMON_ID_PREFIX "%d"

काष्ठा hwmon_device अणु
	स्थिर अक्षर *name;
	काष्ठा device dev;
	स्थिर काष्ठा hwmon_chip_info *chip;
	काष्ठा list_head tzdata;
	काष्ठा attribute_group group;
	स्थिर काष्ठा attribute_group **groups;
पूर्ण;

#घोषणा to_hwmon_device(d) container_of(d, काष्ठा hwmon_device, dev)

#घोषणा MAX_SYSFS_ATTR_NAME_LENGTH	32

काष्ठा hwmon_device_attribute अणु
	काष्ठा device_attribute dev_attr;
	स्थिर काष्ठा hwmon_ops *ops;
	क्रमागत hwmon_sensor_types type;
	u32 attr;
	पूर्णांक index;
	अक्षर name[MAX_SYSFS_ATTR_NAME_LENGTH];
पूर्ण;

#घोषणा to_hwmon_attr(d) \
	container_of(d, काष्ठा hwmon_device_attribute, dev_attr)
#घोषणा to_dev_attr(a) container_of(a, काष्ठा device_attribute, attr)

/*
 * Thermal zone inक्रमmation
 */
काष्ठा hwmon_thermal_data अणु
	काष्ठा list_head node;		/* hwmon tzdata list entry */
	काष्ठा device *dev;		/* Reference to hwmon device */
	पूर्णांक index;			/* sensor index */
	काष्ठा thermal_zone_device *tzd;/* thermal zone device */
पूर्ण;

अटल sमाप_प्रकार
name_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%s\n", to_hwmon_device(dev)->name);
पूर्ण
अटल DEVICE_ATTR_RO(name);

अटल काष्ठा attribute *hwmon_dev_attrs[] = अणु
	&dev_attr_name.attr,
	शून्य
पूर्ण;

अटल umode_t hwmon_dev_name_is_visible(काष्ठा kobject *kobj,
					 काष्ठा attribute *attr, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);

	अगर (to_hwmon_device(dev)->name == शून्य)
		वापस 0;

	वापस attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group hwmon_dev_attr_group = अणु
	.attrs		= hwmon_dev_attrs,
	.is_visible	= hwmon_dev_name_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *hwmon_dev_attr_groups[] = अणु
	&hwmon_dev_attr_group,
	शून्य
पूर्ण;

अटल व्योम hwmon_मुक्त_attrs(काष्ठा attribute **attrs)
अणु
	पूर्णांक i;

	क्रम (i = 0; attrs[i]; i++) अणु
		काष्ठा device_attribute *dattr = to_dev_attr(attrs[i]);
		काष्ठा hwmon_device_attribute *hattr = to_hwmon_attr(dattr);

		kमुक्त(hattr);
	पूर्ण
	kमुक्त(attrs);
पूर्ण

अटल व्योम hwmon_dev_release(काष्ठा device *dev)
अणु
	काष्ठा hwmon_device *hwdev = to_hwmon_device(dev);

	अगर (hwdev->group.attrs)
		hwmon_मुक्त_attrs(hwdev->group.attrs);
	kमुक्त(hwdev->groups);
	kमुक्त(hwdev);
पूर्ण

अटल काष्ठा class hwmon_class = अणु
	.name = "hwmon",
	.owner = THIS_MODULE,
	.dev_groups = hwmon_dev_attr_groups,
	.dev_release = hwmon_dev_release,
पूर्ण;

अटल DEFINE_IDA(hwmon_ida);

/* Thermal zone handling */

/*
 * The complex conditional is necessary to aव्योम a cyclic dependency
 * between hwmon and thermal_sys modules.
 */
#अगर_घोषित CONFIG_THERMAL_OF
अटल पूर्णांक hwmon_thermal_get_temp(व्योम *data, पूर्णांक *temp)
अणु
	काष्ठा hwmon_thermal_data *tdata = data;
	काष्ठा hwmon_device *hwdev = to_hwmon_device(tdata->dev);
	पूर्णांक ret;
	दीर्घ t;

	ret = hwdev->chip->ops->पढ़ो(tdata->dev, hwmon_temp, hwmon_temp_input,
				     tdata->index, &t);
	अगर (ret < 0)
		वापस ret;

	*temp = t;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा thermal_zone_of_device_ops hwmon_thermal_ops = अणु
	.get_temp = hwmon_thermal_get_temp,
पूर्ण;

अटल व्योम hwmon_thermal_हटाओ_sensor(व्योम *data)
अणु
	list_del(data);
पूर्ण

अटल पूर्णांक hwmon_thermal_add_sensor(काष्ठा device *dev, पूर्णांक index)
अणु
	काष्ठा hwmon_device *hwdev = to_hwmon_device(dev);
	काष्ठा hwmon_thermal_data *tdata;
	काष्ठा thermal_zone_device *tzd;
	पूर्णांक err;

	tdata = devm_kzalloc(dev, माप(*tdata), GFP_KERNEL);
	अगर (!tdata)
		वापस -ENOMEM;

	tdata->dev = dev;
	tdata->index = index;

	tzd = devm_thermal_zone_of_sensor_रेजिस्टर(dev, index, tdata,
						   &hwmon_thermal_ops);
	/*
	 * If CONFIG_THERMAL_OF is disabled, this वापसs -ENODEV,
	 * so ignore that error but क्रमward any other error.
	 */
	अगर (IS_ERR(tzd) && (PTR_ERR(tzd) != -ENODEV))
		वापस PTR_ERR(tzd);

	err = devm_add_action(dev, hwmon_thermal_हटाओ_sensor, &tdata->node);
	अगर (err)
		वापस err;

	tdata->tzd = tzd;
	list_add(&tdata->node, &hwdev->tzdata);

	वापस 0;
पूर्ण

अटल पूर्णांक hwmon_thermal_रेजिस्टर_sensors(काष्ठा device *dev)
अणु
	काष्ठा hwmon_device *hwdev = to_hwmon_device(dev);
	स्थिर काष्ठा hwmon_chip_info *chip = hwdev->chip;
	स्थिर काष्ठा hwmon_channel_info **info = chip->info;
	व्योम *drvdata = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 1; info[i]; i++) अणु
		पूर्णांक j;

		अगर (info[i]->type != hwmon_temp)
			जारी;

		क्रम (j = 0; info[i]->config[j]; j++) अणु
			पूर्णांक err;

			अगर (!(info[i]->config[j] & HWMON_T_INPUT) ||
			    !chip->ops->is_visible(drvdata, hwmon_temp,
						   hwmon_temp_input, j))
				जारी;

			err = hwmon_thermal_add_sensor(dev, j);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hwmon_thermal_notअगरy(काष्ठा device *dev, पूर्णांक index)
अणु
	काष्ठा hwmon_device *hwdev = to_hwmon_device(dev);
	काष्ठा hwmon_thermal_data *tzdata;

	list_क्रम_each_entry(tzdata, &hwdev->tzdata, node) अणु
		अगर (tzdata->index == index) अणु
			thermal_zone_device_update(tzdata->tzd,
						   THERMAL_EVENT_UNSPECIFIED);
		पूर्ण
	पूर्ण
पूर्ण

#अन्यथा
अटल पूर्णांक hwmon_thermal_रेजिस्टर_sensors(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल व्योम hwmon_thermal_notअगरy(काष्ठा device *dev, पूर्णांक index) अणु पूर्ण

#पूर्ण_अगर /* IS_REACHABLE(CONFIG_THERMAL) && ... */

अटल पूर्णांक hwmon_attr_base(क्रमागत hwmon_sensor_types type)
अणु
	अगर (type == hwmon_in || type == hwmon_पूर्णांकrusion)
		वापस 0;
	वापस 1;
पूर्ण

/* sysfs attribute management */

अटल sमाप_प्रकार hwmon_attr_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा hwmon_device_attribute *hattr = to_hwmon_attr(devattr);
	दीर्घ val;
	पूर्णांक ret;

	ret = hattr->ops->पढ़ो(dev, hattr->type, hattr->attr, hattr->index,
			       &val);
	अगर (ret < 0)
		वापस ret;

	trace_hwmon_attr_show(hattr->index + hwmon_attr_base(hattr->type),
			      hattr->name, val);

	वापस प्र_लिखो(buf, "%ld\n", val);
पूर्ण

अटल sमाप_प्रकार hwmon_attr_show_string(काष्ठा device *dev,
				      काष्ठा device_attribute *devattr,
				      अक्षर *buf)
अणु
	काष्ठा hwmon_device_attribute *hattr = to_hwmon_attr(devattr);
	क्रमागत hwmon_sensor_types type = hattr->type;
	स्थिर अक्षर *s;
	पूर्णांक ret;

	ret = hattr->ops->पढ़ो_string(dev, hattr->type, hattr->attr,
				      hattr->index, &s);
	अगर (ret < 0)
		वापस ret;

	trace_hwmon_attr_show_string(hattr->index + hwmon_attr_base(type),
				     hattr->name, s);

	वापस प्र_लिखो(buf, "%s\n", s);
पूर्ण

अटल sमाप_प्रकार hwmon_attr_store(काष्ठा device *dev,
				काष्ठा device_attribute *devattr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा hwmon_device_attribute *hattr = to_hwmon_attr(devattr);
	दीर्घ val;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 10, &val);
	अगर (ret < 0)
		वापस ret;

	ret = hattr->ops->ग_लिखो(dev, hattr->type, hattr->attr, hattr->index,
				val);
	अगर (ret < 0)
		वापस ret;

	trace_hwmon_attr_store(hattr->index + hwmon_attr_base(hattr->type),
			       hattr->name, val);

	वापस count;
पूर्ण

अटल bool is_string_attr(क्रमागत hwmon_sensor_types type, u32 attr)
अणु
	वापस (type == hwmon_temp && attr == hwmon_temp_label) ||
	       (type == hwmon_in && attr == hwmon_in_label) ||
	       (type == hwmon_curr && attr == hwmon_curr_label) ||
	       (type == hwmon_घातer && attr == hwmon_घातer_label) ||
	       (type == hwmon_energy && attr == hwmon_energy_label) ||
	       (type == hwmon_humidity && attr == hwmon_humidity_label) ||
	       (type == hwmon_fan && attr == hwmon_fan_label);
पूर्ण

अटल काष्ठा attribute *hwmon_genattr(स्थिर व्योम *drvdata,
				       क्रमागत hwmon_sensor_types type,
				       u32 attr,
				       पूर्णांक index,
				       स्थिर अक्षर *ढाँचा,
				       स्थिर काष्ठा hwmon_ops *ops)
अणु
	काष्ठा hwmon_device_attribute *hattr;
	काष्ठा device_attribute *dattr;
	काष्ठा attribute *a;
	umode_t mode;
	स्थिर अक्षर *name;
	bool is_string = is_string_attr(type, attr);

	/* The attribute is invisible अगर there is no ढाँचा string */
	अगर (!ढाँचा)
		वापस ERR_PTR(-ENOENT);

	mode = ops->is_visible(drvdata, type, attr, index);
	अगर (!mode)
		वापस ERR_PTR(-ENOENT);

	अगर ((mode & 0444) && ((is_string && !ops->पढ़ो_string) ||
				 (!is_string && !ops->पढ़ो)))
		वापस ERR_PTR(-EINVAL);
	अगर ((mode & 0222) && !ops->ग_लिखो)
		वापस ERR_PTR(-EINVAL);

	hattr = kzalloc(माप(*hattr), GFP_KERNEL);
	अगर (!hattr)
		वापस ERR_PTR(-ENOMEM);

	अगर (type == hwmon_chip) अणु
		name = ढाँचा;
	पूर्ण अन्यथा अणु
		scnम_लिखो(hattr->name, माप(hattr->name), ढाँचा,
			  index + hwmon_attr_base(type));
		name = hattr->name;
	पूर्ण

	hattr->type = type;
	hattr->attr = attr;
	hattr->index = index;
	hattr->ops = ops;

	dattr = &hattr->dev_attr;
	dattr->show = is_string ? hwmon_attr_show_string : hwmon_attr_show;
	dattr->store = hwmon_attr_store;

	a = &dattr->attr;
	sysfs_attr_init(a);
	a->name = name;
	a->mode = mode;

	वापस a;
पूर्ण

/*
 * Chip attributes are not attribute ढाँचाs but actual sysfs attributes.
 * See hwmon_genattr() क्रम special handling.
 */
अटल स्थिर अक्षर * स्थिर hwmon_chip_attrs[] = अणु
	[hwmon_chip_temp_reset_history] = "temp_reset_history",
	[hwmon_chip_in_reset_history] = "in_reset_history",
	[hwmon_chip_curr_reset_history] = "curr_reset_history",
	[hwmon_chip_घातer_reset_history] = "power_reset_history",
	[hwmon_chip_update_पूर्णांकerval] = "update_interval",
	[hwmon_chip_alarms] = "alarms",
	[hwmon_chip_samples] = "samples",
	[hwmon_chip_curr_samples] = "curr_samples",
	[hwmon_chip_in_samples] = "in_samples",
	[hwmon_chip_घातer_samples] = "power_samples",
	[hwmon_chip_temp_samples] = "temp_samples",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hwmon_temp_attr_ढाँचाs[] = अणु
	[hwmon_temp_enable] = "temp%d_enable",
	[hwmon_temp_input] = "temp%d_input",
	[hwmon_temp_type] = "temp%d_type",
	[hwmon_temp_lcrit] = "temp%d_lcrit",
	[hwmon_temp_lcrit_hyst] = "temp%d_lcrit_hyst",
	[hwmon_temp_min] = "temp%d_min",
	[hwmon_temp_min_hyst] = "temp%d_min_hyst",
	[hwmon_temp_max] = "temp%d_max",
	[hwmon_temp_max_hyst] = "temp%d_max_hyst",
	[hwmon_temp_crit] = "temp%d_crit",
	[hwmon_temp_crit_hyst] = "temp%d_crit_hyst",
	[hwmon_temp_emergency] = "temp%d_emergency",
	[hwmon_temp_emergency_hyst] = "temp%d_emergency_hyst",
	[hwmon_temp_alarm] = "temp%d_alarm",
	[hwmon_temp_lcrit_alarm] = "temp%d_lcrit_alarm",
	[hwmon_temp_min_alarm] = "temp%d_min_alarm",
	[hwmon_temp_max_alarm] = "temp%d_max_alarm",
	[hwmon_temp_crit_alarm] = "temp%d_crit_alarm",
	[hwmon_temp_emergency_alarm] = "temp%d_emergency_alarm",
	[hwmon_temp_fault] = "temp%d_fault",
	[hwmon_temp_offset] = "temp%d_offset",
	[hwmon_temp_label] = "temp%d_label",
	[hwmon_temp_lowest] = "temp%d_lowest",
	[hwmon_temp_highest] = "temp%d_highest",
	[hwmon_temp_reset_history] = "temp%d_reset_history",
	[hwmon_temp_rated_min] = "temp%d_rated_min",
	[hwmon_temp_rated_max] = "temp%d_rated_max",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hwmon_in_attr_ढाँचाs[] = अणु
	[hwmon_in_enable] = "in%d_enable",
	[hwmon_in_input] = "in%d_input",
	[hwmon_in_min] = "in%d_min",
	[hwmon_in_max] = "in%d_max",
	[hwmon_in_lcrit] = "in%d_lcrit",
	[hwmon_in_crit] = "in%d_crit",
	[hwmon_in_average] = "in%d_average",
	[hwmon_in_lowest] = "in%d_lowest",
	[hwmon_in_highest] = "in%d_highest",
	[hwmon_in_reset_history] = "in%d_reset_history",
	[hwmon_in_label] = "in%d_label",
	[hwmon_in_alarm] = "in%d_alarm",
	[hwmon_in_min_alarm] = "in%d_min_alarm",
	[hwmon_in_max_alarm] = "in%d_max_alarm",
	[hwmon_in_lcrit_alarm] = "in%d_lcrit_alarm",
	[hwmon_in_crit_alarm] = "in%d_crit_alarm",
	[hwmon_in_rated_min] = "in%d_rated_min",
	[hwmon_in_rated_max] = "in%d_rated_max",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hwmon_curr_attr_ढाँचाs[] = अणु
	[hwmon_curr_enable] = "curr%d_enable",
	[hwmon_curr_input] = "curr%d_input",
	[hwmon_curr_min] = "curr%d_min",
	[hwmon_curr_max] = "curr%d_max",
	[hwmon_curr_lcrit] = "curr%d_lcrit",
	[hwmon_curr_crit] = "curr%d_crit",
	[hwmon_curr_average] = "curr%d_average",
	[hwmon_curr_lowest] = "curr%d_lowest",
	[hwmon_curr_highest] = "curr%d_highest",
	[hwmon_curr_reset_history] = "curr%d_reset_history",
	[hwmon_curr_label] = "curr%d_label",
	[hwmon_curr_alarm] = "curr%d_alarm",
	[hwmon_curr_min_alarm] = "curr%d_min_alarm",
	[hwmon_curr_max_alarm] = "curr%d_max_alarm",
	[hwmon_curr_lcrit_alarm] = "curr%d_lcrit_alarm",
	[hwmon_curr_crit_alarm] = "curr%d_crit_alarm",
	[hwmon_curr_rated_min] = "curr%d_rated_min",
	[hwmon_curr_rated_max] = "curr%d_rated_max",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hwmon_घातer_attr_ढाँचाs[] = अणु
	[hwmon_घातer_enable] = "power%d_enable",
	[hwmon_घातer_average] = "power%d_average",
	[hwmon_घातer_average_पूर्णांकerval] = "power%d_average_interval",
	[hwmon_घातer_average_पूर्णांकerval_max] = "power%d_interval_max",
	[hwmon_घातer_average_पूर्णांकerval_min] = "power%d_interval_min",
	[hwmon_घातer_average_highest] = "power%d_average_highest",
	[hwmon_घातer_average_lowest] = "power%d_average_lowest",
	[hwmon_घातer_average_max] = "power%d_average_max",
	[hwmon_घातer_average_min] = "power%d_average_min",
	[hwmon_घातer_input] = "power%d_input",
	[hwmon_घातer_input_highest] = "power%d_input_highest",
	[hwmon_घातer_input_lowest] = "power%d_input_lowest",
	[hwmon_घातer_reset_history] = "power%d_reset_history",
	[hwmon_घातer_accuracy] = "power%d_accuracy",
	[hwmon_घातer_cap] = "power%d_cap",
	[hwmon_घातer_cap_hyst] = "power%d_cap_hyst",
	[hwmon_घातer_cap_max] = "power%d_cap_max",
	[hwmon_घातer_cap_min] = "power%d_cap_min",
	[hwmon_घातer_min] = "power%d_min",
	[hwmon_घातer_max] = "power%d_max",
	[hwmon_घातer_lcrit] = "power%d_lcrit",
	[hwmon_घातer_crit] = "power%d_crit",
	[hwmon_घातer_label] = "power%d_label",
	[hwmon_घातer_alarm] = "power%d_alarm",
	[hwmon_घातer_cap_alarm] = "power%d_cap_alarm",
	[hwmon_घातer_min_alarm] = "power%d_min_alarm",
	[hwmon_घातer_max_alarm] = "power%d_max_alarm",
	[hwmon_घातer_lcrit_alarm] = "power%d_lcrit_alarm",
	[hwmon_घातer_crit_alarm] = "power%d_crit_alarm",
	[hwmon_घातer_rated_min] = "power%d_rated_min",
	[hwmon_घातer_rated_max] = "power%d_rated_max",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hwmon_energy_attr_ढाँचाs[] = अणु
	[hwmon_energy_enable] = "energy%d_enable",
	[hwmon_energy_input] = "energy%d_input",
	[hwmon_energy_label] = "energy%d_label",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hwmon_humidity_attr_ढाँचाs[] = अणु
	[hwmon_humidity_enable] = "humidity%d_enable",
	[hwmon_humidity_input] = "humidity%d_input",
	[hwmon_humidity_label] = "humidity%d_label",
	[hwmon_humidity_min] = "humidity%d_min",
	[hwmon_humidity_min_hyst] = "humidity%d_min_hyst",
	[hwmon_humidity_max] = "humidity%d_max",
	[hwmon_humidity_max_hyst] = "humidity%d_max_hyst",
	[hwmon_humidity_alarm] = "humidity%d_alarm",
	[hwmon_humidity_fault] = "humidity%d_fault",
	[hwmon_humidity_rated_min] = "humidity%d_rated_min",
	[hwmon_humidity_rated_max] = "humidity%d_rated_max",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hwmon_fan_attr_ढाँचाs[] = अणु
	[hwmon_fan_enable] = "fan%d_enable",
	[hwmon_fan_input] = "fan%d_input",
	[hwmon_fan_label] = "fan%d_label",
	[hwmon_fan_min] = "fan%d_min",
	[hwmon_fan_max] = "fan%d_max",
	[hwmon_fan_भाग] = "fan%d_div",
	[hwmon_fan_pulses] = "fan%d_pulses",
	[hwmon_fan_target] = "fan%d_target",
	[hwmon_fan_alarm] = "fan%d_alarm",
	[hwmon_fan_min_alarm] = "fan%d_min_alarm",
	[hwmon_fan_max_alarm] = "fan%d_max_alarm",
	[hwmon_fan_fault] = "fan%d_fault",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hwmon_pwm_attr_ढाँचाs[] = अणु
	[hwmon_pwm_input] = "pwm%d",
	[hwmon_pwm_enable] = "pwm%d_enable",
	[hwmon_pwm_mode] = "pwm%d_mode",
	[hwmon_pwm_freq] = "pwm%d_freq",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hwmon_पूर्णांकrusion_attr_ढाँचाs[] = अणु
	[hwmon_पूर्णांकrusion_alarm] = "intrusion%d_alarm",
	[hwmon_पूर्णांकrusion_beep]  = "intrusion%d_beep",
पूर्ण;

अटल स्थिर अक्षर * स्थिर *__ढाँचाs[] = अणु
	[hwmon_chip] = hwmon_chip_attrs,
	[hwmon_temp] = hwmon_temp_attr_ढाँचाs,
	[hwmon_in] = hwmon_in_attr_ढाँचाs,
	[hwmon_curr] = hwmon_curr_attr_ढाँचाs,
	[hwmon_घातer] = hwmon_घातer_attr_ढाँचाs,
	[hwmon_energy] = hwmon_energy_attr_ढाँचाs,
	[hwmon_humidity] = hwmon_humidity_attr_ढाँचाs,
	[hwmon_fan] = hwmon_fan_attr_ढाँचाs,
	[hwmon_pwm] = hwmon_pwm_attr_ढाँचाs,
	[hwmon_पूर्णांकrusion] = hwmon_पूर्णांकrusion_attr_ढाँचाs,
पूर्ण;

अटल स्थिर पूर्णांक __ढाँचाs_size[] = अणु
	[hwmon_chip] = ARRAY_SIZE(hwmon_chip_attrs),
	[hwmon_temp] = ARRAY_SIZE(hwmon_temp_attr_ढाँचाs),
	[hwmon_in] = ARRAY_SIZE(hwmon_in_attr_ढाँचाs),
	[hwmon_curr] = ARRAY_SIZE(hwmon_curr_attr_ढाँचाs),
	[hwmon_घातer] = ARRAY_SIZE(hwmon_घातer_attr_ढाँचाs),
	[hwmon_energy] = ARRAY_SIZE(hwmon_energy_attr_ढाँचाs),
	[hwmon_humidity] = ARRAY_SIZE(hwmon_humidity_attr_ढाँचाs),
	[hwmon_fan] = ARRAY_SIZE(hwmon_fan_attr_ढाँचाs),
	[hwmon_pwm] = ARRAY_SIZE(hwmon_pwm_attr_ढाँचाs),
	[hwmon_पूर्णांकrusion] = ARRAY_SIZE(hwmon_पूर्णांकrusion_attr_ढाँचाs),
पूर्ण;

पूर्णांक hwmon_notअगरy_event(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		       u32 attr, पूर्णांक channel)
अणु
	अक्षर sattr[MAX_SYSFS_ATTR_NAME_LENGTH];
	स्थिर अक्षर * स्थिर *ढाँचाs;
	स्थिर अक्षर *ढाँचा;
	पूर्णांक base;

	अगर (type >= ARRAY_SIZE(__ढाँचाs))
		वापस -EINVAL;
	अगर (attr >= __ढाँचाs_size[type])
		वापस -EINVAL;

	ढाँचाs = __ढाँचाs[type];
	ढाँचा = ढाँचाs[attr];

	base = hwmon_attr_base(type);

	scnम_लिखो(sattr, MAX_SYSFS_ATTR_NAME_LENGTH, ढाँचा, base + channel);
	sysfs_notअगरy(&dev->kobj, शून्य, sattr);
	kobject_uevent(&dev->kobj, KOBJ_CHANGE);

	अगर (type == hwmon_temp)
		hwmon_thermal_notअगरy(dev, channel);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hwmon_notअगरy_event);

अटल पूर्णांक hwmon_num_channel_attrs(स्थिर काष्ठा hwmon_channel_info *info)
अणु
	पूर्णांक i, n;

	क्रम (i = n = 0; info->config[i]; i++)
		n += hweight32(info->config[i]);

	वापस n;
पूर्ण

अटल पूर्णांक hwmon_genattrs(स्थिर व्योम *drvdata,
			  काष्ठा attribute **attrs,
			  स्थिर काष्ठा hwmon_ops *ops,
			  स्थिर काष्ठा hwmon_channel_info *info)
अणु
	स्थिर अक्षर * स्थिर *ढाँचाs;
	पूर्णांक ढाँचा_size;
	पूर्णांक i, aindex = 0;

	अगर (info->type >= ARRAY_SIZE(__ढाँचाs))
		वापस -EINVAL;

	ढाँचाs = __ढाँचाs[info->type];
	ढाँचा_size = __ढाँचाs_size[info->type];

	क्रम (i = 0; info->config[i]; i++) अणु
		u32 attr_mask = info->config[i];
		u32 attr;

		जबतक (attr_mask) अणु
			काष्ठा attribute *a;

			attr = __ffs(attr_mask);
			attr_mask &= ~BIT(attr);
			अगर (attr >= ढाँचा_size)
				वापस -EINVAL;
			a = hwmon_genattr(drvdata, info->type, attr, i,
					  ढाँचाs[attr], ops);
			अगर (IS_ERR(a)) अणु
				अगर (PTR_ERR(a) != -ENOENT)
					वापस PTR_ERR(a);
				जारी;
			पूर्ण
			attrs[aindex++] = a;
		पूर्ण
	पूर्ण
	वापस aindex;
पूर्ण

अटल काष्ठा attribute **
__hwmon_create_attrs(स्थिर व्योम *drvdata, स्थिर काष्ठा hwmon_chip_info *chip)
अणु
	पूर्णांक ret, i, aindex = 0, nattrs = 0;
	काष्ठा attribute **attrs;

	क्रम (i = 0; chip->info[i]; i++)
		nattrs += hwmon_num_channel_attrs(chip->info[i]);

	अगर (nattrs == 0)
		वापस ERR_PTR(-EINVAL);

	attrs = kसुस्मृति(nattrs + 1, माप(*attrs), GFP_KERNEL);
	अगर (!attrs)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; chip->info[i]; i++) अणु
		ret = hwmon_genattrs(drvdata, &attrs[aindex], chip->ops,
				     chip->info[i]);
		अगर (ret < 0) अणु
			hwmon_मुक्त_attrs(attrs);
			वापस ERR_PTR(ret);
		पूर्ण
		aindex += ret;
	पूर्ण

	वापस attrs;
पूर्ण

अटल काष्ठा device *
__hwmon_device_रेजिस्टर(काष्ठा device *dev, स्थिर अक्षर *name, व्योम *drvdata,
			स्थिर काष्ठा hwmon_chip_info *chip,
			स्थिर काष्ठा attribute_group **groups)
अणु
	काष्ठा hwmon_device *hwdev;
	काष्ठा device *hdev;
	पूर्णांक i, err, id;

	/* Complain about invalid अक्षरacters in hwmon name attribute */
	अगर (name && (!म_माप(name) || strpbrk(name, "-* \t\n")))
		dev_warn(dev,
			 "hwmon: '%s' is not a valid name attribute, please fix\n",
			 name);

	id = ida_simple_get(&hwmon_ida, 0, 0, GFP_KERNEL);
	अगर (id < 0)
		वापस ERR_PTR(id);

	hwdev = kzalloc(माप(*hwdev), GFP_KERNEL);
	अगर (hwdev == शून्य) अणु
		err = -ENOMEM;
		जाओ ida_हटाओ;
	पूर्ण

	hdev = &hwdev->dev;

	अगर (chip) अणु
		काष्ठा attribute **attrs;
		पूर्णांक ngroups = 2; /* terminating शून्य plus &hwdev->groups */

		अगर (groups)
			क्रम (i = 0; groups[i]; i++)
				ngroups++;

		hwdev->groups = kसुस्मृति(ngroups, माप(*groups), GFP_KERNEL);
		अगर (!hwdev->groups) अणु
			err = -ENOMEM;
			जाओ मुक्त_hwmon;
		पूर्ण

		attrs = __hwmon_create_attrs(drvdata, chip);
		अगर (IS_ERR(attrs)) अणु
			err = PTR_ERR(attrs);
			जाओ मुक्त_hwmon;
		पूर्ण

		hwdev->group.attrs = attrs;
		ngroups = 0;
		hwdev->groups[ngroups++] = &hwdev->group;

		अगर (groups) अणु
			क्रम (i = 0; groups[i]; i++)
				hwdev->groups[ngroups++] = groups[i];
		पूर्ण

		hdev->groups = hwdev->groups;
	पूर्ण अन्यथा अणु
		hdev->groups = groups;
	पूर्ण

	hwdev->name = name;
	hdev->class = &hwmon_class;
	hdev->parent = dev;
	hdev->of_node = dev ? dev->of_node : शून्य;
	hwdev->chip = chip;
	dev_set_drvdata(hdev, drvdata);
	dev_set_name(hdev, HWMON_ID_FORMAT, id);
	err = device_रेजिस्टर(hdev);
	अगर (err)
		जाओ मुक्त_hwmon;

	INIT_LIST_HEAD(&hwdev->tzdata);

	अगर (dev && dev->of_node && chip && chip->ops->पढ़ो &&
	    chip->info[0]->type == hwmon_chip &&
	    (chip->info[0]->config[0] & HWMON_C_REGISTER_TZ)) अणु
		err = hwmon_thermal_रेजिस्टर_sensors(hdev);
		अगर (err) अणु
			device_unरेजिस्टर(hdev);
			/*
			 * Don't worry about hwdev; hwmon_dev_release(), called
			 * from device_unरेजिस्टर(), will मुक्त it.
			 */
			जाओ ida_हटाओ;
		पूर्ण
	पूर्ण

	वापस hdev;

मुक्त_hwmon:
	hwmon_dev_release(hdev);
ida_हटाओ:
	ida_simple_हटाओ(&hwmon_ida, id);
	वापस ERR_PTR(err);
पूर्ण

/**
 * hwmon_device_रेजिस्टर_with_groups - रेजिस्टर w/ hwmon
 * @dev: the parent device
 * @name: hwmon name attribute
 * @drvdata: driver data to attach to created device
 * @groups: List of attribute groups to create
 *
 * hwmon_device_unरेजिस्टर() must be called when the device is no
 * दीर्घer needed.
 *
 * Returns the poपूर्णांकer to the new device.
 */
काष्ठा device *
hwmon_device_रेजिस्टर_with_groups(काष्ठा device *dev, स्थिर अक्षर *name,
				  व्योम *drvdata,
				  स्थिर काष्ठा attribute_group **groups)
अणु
	अगर (!name)
		वापस ERR_PTR(-EINVAL);

	वापस __hwmon_device_रेजिस्टर(dev, name, drvdata, शून्य, groups);
पूर्ण
EXPORT_SYMBOL_GPL(hwmon_device_रेजिस्टर_with_groups);

/**
 * hwmon_device_रेजिस्टर_with_info - रेजिस्टर w/ hwmon
 * @dev: the parent device
 * @name: hwmon name attribute
 * @drvdata: driver data to attach to created device
 * @chip: poपूर्णांकer to hwmon chip inक्रमmation
 * @extra_groups: poपूर्णांकer to list of additional non-standard attribute groups
 *
 * hwmon_device_unरेजिस्टर() must be called when the device is no
 * दीर्घer needed.
 *
 * Returns the poपूर्णांकer to the new device.
 */
काष्ठा device *
hwmon_device_रेजिस्टर_with_info(काष्ठा device *dev, स्थिर अक्षर *name,
				व्योम *drvdata,
				स्थिर काष्ठा hwmon_chip_info *chip,
				स्थिर काष्ठा attribute_group **extra_groups)
अणु
	अगर (!name)
		वापस ERR_PTR(-EINVAL);

	अगर (chip && (!chip->ops || !chip->ops->is_visible || !chip->info))
		वापस ERR_PTR(-EINVAL);

	अगर (chip && !dev)
		वापस ERR_PTR(-EINVAL);

	वापस __hwmon_device_रेजिस्टर(dev, name, drvdata, chip, extra_groups);
पूर्ण
EXPORT_SYMBOL_GPL(hwmon_device_रेजिस्टर_with_info);

/**
 * hwmon_device_रेजिस्टर - रेजिस्टर w/ hwmon
 * @dev: the device to रेजिस्टर
 *
 * hwmon_device_unरेजिस्टर() must be called when the device is no
 * दीर्घer needed.
 *
 * Returns the poपूर्णांकer to the new device.
 */
काष्ठा device *hwmon_device_रेजिस्टर(काष्ठा device *dev)
अणु
	dev_warn(dev,
		 "hwmon_device_register() is deprecated. Please convert the driver to use hwmon_device_register_with_info().\n");

	वापस __hwmon_device_रेजिस्टर(dev, शून्य, शून्य, शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(hwmon_device_रेजिस्टर);

/**
 * hwmon_device_unरेजिस्टर - हटाओs the previously रेजिस्टरed class device
 *
 * @dev: the class device to destroy
 */
व्योम hwmon_device_unरेजिस्टर(काष्ठा device *dev)
अणु
	पूर्णांक id;

	अगर (likely(माला_पूछो(dev_name(dev), HWMON_ID_FORMAT, &id) == 1)) अणु
		device_unरेजिस्टर(dev);
		ida_simple_हटाओ(&hwmon_ida, id);
	पूर्ण अन्यथा
		dev_dbg(dev->parent,
			"hwmon_device_unregister() failed: bad class ID!\n");
पूर्ण
EXPORT_SYMBOL_GPL(hwmon_device_unरेजिस्टर);

अटल व्योम devm_hwmon_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा device *hwdev = *(काष्ठा device **)res;

	hwmon_device_unरेजिस्टर(hwdev);
पूर्ण

/**
 * devm_hwmon_device_रेजिस्टर_with_groups - रेजिस्टर w/ hwmon
 * @dev: the parent device
 * @name: hwmon name attribute
 * @drvdata: driver data to attach to created device
 * @groups: List of attribute groups to create
 *
 * Returns the poपूर्णांकer to the new device. The new device is स्वतःmatically
 * unरेजिस्टरed with the parent device.
 */
काष्ठा device *
devm_hwmon_device_रेजिस्टर_with_groups(काष्ठा device *dev, स्थिर अक्षर *name,
				       व्योम *drvdata,
				       स्थिर काष्ठा attribute_group **groups)
अणु
	काष्ठा device **ptr, *hwdev;

	अगर (!dev)
		वापस ERR_PTR(-EINVAL);

	ptr = devres_alloc(devm_hwmon_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	hwdev = hwmon_device_रेजिस्टर_with_groups(dev, name, drvdata, groups);
	अगर (IS_ERR(hwdev))
		जाओ error;

	*ptr = hwdev;
	devres_add(dev, ptr);
	वापस hwdev;

error:
	devres_मुक्त(ptr);
	वापस hwdev;
पूर्ण
EXPORT_SYMBOL_GPL(devm_hwmon_device_रेजिस्टर_with_groups);

/**
 * devm_hwmon_device_रेजिस्टर_with_info - रेजिस्टर w/ hwmon
 * @dev:	the parent device
 * @name:	hwmon name attribute
 * @drvdata:	driver data to attach to created device
 * @chip:	poपूर्णांकer to hwmon chip inक्रमmation
 * @groups:	poपूर्णांकer to list of driver specअगरic attribute groups
 *
 * Returns the poपूर्णांकer to the new device. The new device is स्वतःmatically
 * unरेजिस्टरed with the parent device.
 */
काष्ठा device *
devm_hwmon_device_रेजिस्टर_with_info(काष्ठा device *dev, स्थिर अक्षर *name,
				     व्योम *drvdata,
				     स्थिर काष्ठा hwmon_chip_info *chip,
				     स्थिर काष्ठा attribute_group **groups)
अणु
	काष्ठा device **ptr, *hwdev;

	अगर (!dev)
		वापस ERR_PTR(-EINVAL);

	ptr = devres_alloc(devm_hwmon_release, माप(*ptr), GFP_KERNEL);
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	hwdev = hwmon_device_रेजिस्टर_with_info(dev, name, drvdata, chip,
						groups);
	अगर (IS_ERR(hwdev))
		जाओ error;

	*ptr = hwdev;
	devres_add(dev, ptr);

	वापस hwdev;

error:
	devres_मुक्त(ptr);
	वापस hwdev;
पूर्ण
EXPORT_SYMBOL_GPL(devm_hwmon_device_रेजिस्टर_with_info);

अटल पूर्णांक devm_hwmon_match(काष्ठा device *dev, व्योम *res, व्योम *data)
अणु
	काष्ठा device **hwdev = res;

	वापस *hwdev == data;
पूर्ण

/**
 * devm_hwmon_device_unरेजिस्टर - हटाओs a previously रेजिस्टरed hwmon device
 *
 * @dev: the parent device of the device to unरेजिस्टर
 */
व्योम devm_hwmon_device_unरेजिस्टर(काष्ठा device *dev)
अणु
	WARN_ON(devres_release(dev, devm_hwmon_release, devm_hwmon_match, dev));
पूर्ण
EXPORT_SYMBOL_GPL(devm_hwmon_device_unरेजिस्टर);

अटल व्योम __init hwmon_pci_quirks(व्योम)
अणु
#अगर defined CONFIG_X86 && defined CONFIG_PCI
	काष्ठा pci_dev *sb;
	u16 base;
	u8 enable;

	/* Open access to 0x295-0x296 on MSI MS-7031 */
	sb = pci_get_device(PCI_VENDOR_ID_ATI, 0x436c, शून्य);
	अगर (sb) अणु
		अगर (sb->subप्रणाली_venकरोr == 0x1462 &&	/* MSI */
		    sb->subप्रणाली_device == 0x0031) अणु	/* MS-7031 */
			pci_पढ़ो_config_byte(sb, 0x48, &enable);
			pci_पढ़ो_config_word(sb, 0x64, &base);

			अगर (base == 0 && !(enable & BIT(2))) अणु
				dev_info(&sb->dev,
					 "Opening wide generic port at 0x295\n");
				pci_ग_लिखो_config_word(sb, 0x64, 0x295);
				pci_ग_लिखो_config_byte(sb, 0x48,
						      enable | BIT(2));
			पूर्ण
		पूर्ण
		pci_dev_put(sb);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __init hwmon_init(व्योम)
अणु
	पूर्णांक err;

	hwmon_pci_quirks();

	err = class_रेजिस्टर(&hwmon_class);
	अगर (err) अणु
		pr_err("couldn't register hwmon sysfs class\n");
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास hwmon_निकास(व्योम)
अणु
	class_unरेजिस्टर(&hwmon_class);
पूर्ण

subsys_initcall(hwmon_init);
module_निकास(hwmon_निकास);

MODULE_AUTHOR("Mark M. Hoffman <mhoffman@lightlink.com>");
MODULE_DESCRIPTION("hardware monitoring sysfs/class support");
MODULE_LICENSE("GPL");

