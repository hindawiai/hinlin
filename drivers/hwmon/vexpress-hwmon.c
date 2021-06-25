<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2012 ARM Limited
 */

#घोषणा DRVNAME "vexpress-hwmon"
#घोषणा pr_fmt(fmt) DRVNAME ": " fmt

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/vexpress.h>

काष्ठा vexpress_hwmon_data अणु
	काष्ठा device *hwmon_dev;
	काष्ठा regmap *reg;
पूर्ण;

अटल sमाप_प्रकार vexpress_hwmon_label_show(काष्ठा device *dev,
		काष्ठा device_attribute *dev_attr, अक्षर *buffer)
अणु
	स्थिर अक्षर *label = of_get_property(dev->of_node, "label", शून्य);

	वापस sysfs_emit(buffer, "%s\n", label);
पूर्ण

अटल sमाप_प्रकार vexpress_hwmon_u32_show(काष्ठा device *dev,
		काष्ठा device_attribute *dev_attr, अक्षर *buffer)
अणु
	काष्ठा vexpress_hwmon_data *data = dev_get_drvdata(dev);
	पूर्णांक err;
	u32 value;

	err = regmap_पढ़ो(data->reg, 0, &value);
	अगर (err)
		वापस err;

	वापस sysfs_emit(buffer, "%u\n", value /
			  to_sensor_dev_attr(dev_attr)->index);
पूर्ण

अटल sमाप_प्रकार vexpress_hwmon_u64_show(काष्ठा device *dev,
		काष्ठा device_attribute *dev_attr, अक्षर *buffer)
अणु
	काष्ठा vexpress_hwmon_data *data = dev_get_drvdata(dev);
	पूर्णांक err;
	u32 value_hi, value_lo;

	err = regmap_पढ़ो(data->reg, 0, &value_lo);
	अगर (err)
		वापस err;

	err = regmap_पढ़ो(data->reg, 1, &value_hi);
	अगर (err)
		वापस err;

	वापस sysfs_emit(buffer, "%llu\n",
			  भाग_u64(((u64)value_hi << 32) | value_lo,
				  to_sensor_dev_attr(dev_attr)->index));
पूर्ण

अटल umode_t vexpress_hwmon_attr_is_visible(काष्ठा kobject *kobj,
		काष्ठा attribute *attr, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा device_attribute *dev_attr = container_of(attr,
				काष्ठा device_attribute, attr);

	अगर (dev_attr->show == vexpress_hwmon_label_show &&
			!of_get_property(dev->of_node, "label", शून्य))
		वापस 0;

	वापस attr->mode;
पूर्ण

काष्ठा vexpress_hwmon_type अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा attribute_group **attr_groups;
पूर्ण;

#अगर !defined(CONFIG_REGULATOR_VEXPRESS)
अटल DEVICE_ATTR(in1_label, 0444, vexpress_hwmon_label_show, शून्य);
अटल SENSOR_DEVICE_ATTR_RO(in1_input, vexpress_hwmon_u32, 1000);
अटल काष्ठा attribute *vexpress_hwmon_attrs_volt[] = अणु
	&dev_attr_in1_label.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	शून्य
पूर्ण;
अटल काष्ठा attribute_group vexpress_hwmon_group_volt = अणु
	.is_visible = vexpress_hwmon_attr_is_visible,
	.attrs = vexpress_hwmon_attrs_volt,
पूर्ण;
अटल काष्ठा vexpress_hwmon_type vexpress_hwmon_volt = अणु
	.name = "vexpress_volt",
	.attr_groups = (स्थिर काष्ठा attribute_group *[]) अणु
		&vexpress_hwmon_group_volt,
		शून्य,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल DEVICE_ATTR(curr1_label, 0444, vexpress_hwmon_label_show, शून्य);
अटल SENSOR_DEVICE_ATTR_RO(curr1_input, vexpress_hwmon_u32, 1000);
अटल काष्ठा attribute *vexpress_hwmon_attrs_amp[] = अणु
	&dev_attr_curr1_label.attr,
	&sensor_dev_attr_curr1_input.dev_attr.attr,
	शून्य
पूर्ण;
अटल काष्ठा attribute_group vexpress_hwmon_group_amp = अणु
	.is_visible = vexpress_hwmon_attr_is_visible,
	.attrs = vexpress_hwmon_attrs_amp,
पूर्ण;
अटल काष्ठा vexpress_hwmon_type vexpress_hwmon_amp = अणु
	.name = "vexpress_amp",
	.attr_groups = (स्थिर काष्ठा attribute_group *[]) अणु
		&vexpress_hwmon_group_amp,
		शून्य
	पूर्ण,
पूर्ण;

अटल DEVICE_ATTR(temp1_label, 0444, vexpress_hwmon_label_show, शून्य);
अटल SENSOR_DEVICE_ATTR_RO(temp1_input, vexpress_hwmon_u32, 1000);
अटल काष्ठा attribute *vexpress_hwmon_attrs_temp[] = अणु
	&dev_attr_temp1_label.attr,
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	शून्य
पूर्ण;
अटल काष्ठा attribute_group vexpress_hwmon_group_temp = अणु
	.is_visible = vexpress_hwmon_attr_is_visible,
	.attrs = vexpress_hwmon_attrs_temp,
पूर्ण;
अटल काष्ठा vexpress_hwmon_type vexpress_hwmon_temp = अणु
	.name = "vexpress_temp",
	.attr_groups = (स्थिर काष्ठा attribute_group *[]) अणु
		&vexpress_hwmon_group_temp,
		शून्य
	पूर्ण,
पूर्ण;

अटल DEVICE_ATTR(घातer1_label, 0444, vexpress_hwmon_label_show, शून्य);
अटल SENSOR_DEVICE_ATTR_RO(घातer1_input, vexpress_hwmon_u32, 1);
अटल काष्ठा attribute *vexpress_hwmon_attrs_घातer[] = अणु
	&dev_attr_घातer1_label.attr,
	&sensor_dev_attr_घातer1_input.dev_attr.attr,
	शून्य
पूर्ण;
अटल काष्ठा attribute_group vexpress_hwmon_group_घातer = अणु
	.is_visible = vexpress_hwmon_attr_is_visible,
	.attrs = vexpress_hwmon_attrs_घातer,
पूर्ण;
अटल काष्ठा vexpress_hwmon_type vexpress_hwmon_घातer = अणु
	.name = "vexpress_power",
	.attr_groups = (स्थिर काष्ठा attribute_group *[]) अणु
		&vexpress_hwmon_group_घातer,
		शून्य
	पूर्ण,
पूर्ण;

अटल DEVICE_ATTR(energy1_label, 0444, vexpress_hwmon_label_show, शून्य);
अटल SENSOR_DEVICE_ATTR_RO(energy1_input, vexpress_hwmon_u64, 1);
अटल काष्ठा attribute *vexpress_hwmon_attrs_energy[] = अणु
	&dev_attr_energy1_label.attr,
	&sensor_dev_attr_energy1_input.dev_attr.attr,
	शून्य
पूर्ण;
अटल काष्ठा attribute_group vexpress_hwmon_group_energy = अणु
	.is_visible = vexpress_hwmon_attr_is_visible,
	.attrs = vexpress_hwmon_attrs_energy,
पूर्ण;
अटल काष्ठा vexpress_hwmon_type vexpress_hwmon_energy = अणु
	.name = "vexpress_energy",
	.attr_groups = (स्थिर काष्ठा attribute_group *[]) अणु
		&vexpress_hwmon_group_energy,
		शून्य
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id vexpress_hwmon_of_match[] = अणु
#अगर !defined(CONFIG_REGULATOR_VEXPRESS)
	अणु
		.compatible = "arm,vexpress-volt",
		.data = &vexpress_hwmon_volt,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.compatible = "arm,vexpress-amp",
		.data = &vexpress_hwmon_amp,
	पूर्ण, अणु
		.compatible = "arm,vexpress-temp",
		.data = &vexpress_hwmon_temp,
	पूर्ण, अणु
		.compatible = "arm,vexpress-power",
		.data = &vexpress_hwmon_घातer,
	पूर्ण, अणु
		.compatible = "arm,vexpress-energy",
		.data = &vexpress_hwmon_energy,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, vexpress_hwmon_of_match);

अटल पूर्णांक vexpress_hwmon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा of_device_id *match;
	काष्ठा vexpress_hwmon_data *data;
	स्थिर काष्ठा vexpress_hwmon_type *type;

	data = devm_kzalloc(&pdev->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;
	platक्रमm_set_drvdata(pdev, data);

	match = of_match_device(vexpress_hwmon_of_match, &pdev->dev);
	अगर (!match)
		वापस -ENODEV;
	type = match->data;

	data->reg = devm_regmap_init_vexpress_config(&pdev->dev);
	अगर (IS_ERR(data->reg))
		वापस PTR_ERR(data->reg);

	data->hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&pdev->dev,
			type->name, data, type->attr_groups);

	वापस PTR_ERR_OR_ZERO(data->hwmon_dev);
पूर्ण

अटल काष्ठा platक्रमm_driver vexpress_hwmon_driver = अणु
	.probe = vexpress_hwmon_probe,
	.driver	= अणु
		.name = DRVNAME,
		.of_match_table = vexpress_hwmon_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(vexpress_hwmon_driver);

MODULE_AUTHOR("Pawel Moll <pawel.moll@arm.com>");
MODULE_DESCRIPTION("Versatile Express hwmon sensors driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:vexpress-hwmon");
