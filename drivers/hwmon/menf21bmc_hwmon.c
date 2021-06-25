<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  MEN 14F021P00 Board Management Controller (BMC) hwmon driver.
 *
 *  This is the core hwmon driver of the MEN 14F021P00 BMC.
 *  The BMC monitors the board voltages which can be access with this
 *  driver through sysfs.
 *
 *  Copyright (C) 2014 MEN Mikro Elektronik Nuernberg GmbH
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>

#घोषणा DRV_NAME  "menf21bmc_hwmon"

#घोषणा BMC_VOLT_COUNT	5
#घोषणा MENF21BMC_V33	0
#घोषणा MENF21BMC_V5	1
#घोषणा MENF21BMC_V12	2
#घोषणा MENF21BMC_V5_SB	3
#घोषणा MENF21BMC_VBAT	4

#घोषणा IDX_TO_VOLT_MIN_CMD(idx) (0x40 + idx)
#घोषणा IDX_TO_VOLT_MAX_CMD(idx) (0x50 + idx)
#घोषणा IDX_TO_VOLT_INP_CMD(idx) (0x60 + idx)

काष्ठा menf21bmc_hwmon अणु
	bool valid;
	काष्ठा i2c_client *i2c_client;
	अचिन्हित दीर्घ last_update;
	पूर्णांक in_val[BMC_VOLT_COUNT];
	पूर्णांक in_min[BMC_VOLT_COUNT];
	पूर्णांक in_max[BMC_VOLT_COUNT];
पूर्ण;

अटल स्थिर अक्षर *स्थिर input_names[] = अणु
	[MENF21BMC_V33]		= "MON_3_3V",
	[MENF21BMC_V5]		= "MON_5V",
	[MENF21BMC_V12]		= "MON_12V",
	[MENF21BMC_V5_SB]	= "5V_STANDBY",
	[MENF21BMC_VBAT]	= "VBAT"
पूर्ण;

अटल काष्ठा menf21bmc_hwmon *menf21bmc_hwmon_update(काष्ठा device *dev)
अणु
	पूर्णांक i;
	पूर्णांक val;
	काष्ठा menf21bmc_hwmon *drv_data = dev_get_drvdata(dev);
	काष्ठा menf21bmc_hwmon *data_ret = drv_data;

	अगर (समय_after(jअगरfies, drv_data->last_update + HZ)
	    || !drv_data->valid) अणु
		क्रम (i = 0; i < BMC_VOLT_COUNT; i++) अणु
			val = i2c_smbus_पढ़ो_word_data(drv_data->i2c_client,
						       IDX_TO_VOLT_INP_CMD(i));
			अगर (val < 0) अणु
				data_ret = ERR_PTR(val);
				जाओ पात;
			पूर्ण
			drv_data->in_val[i] = val;
		पूर्ण
		drv_data->last_update = jअगरfies;
		drv_data->valid = true;
	पूर्ण
पात:
	वापस data_ret;
पूर्ण

अटल पूर्णांक menf21bmc_hwmon_get_volt_limits(काष्ठा menf21bmc_hwmon *drv_data)
अणु
	पूर्णांक i, val;

	क्रम (i = 0; i < BMC_VOLT_COUNT; i++) अणु
		val = i2c_smbus_पढ़ो_word_data(drv_data->i2c_client,
					       IDX_TO_VOLT_MIN_CMD(i));
		अगर (val < 0)
			वापस val;

		drv_data->in_min[i] = val;

		val = i2c_smbus_पढ़ो_word_data(drv_data->i2c_client,
					       IDX_TO_VOLT_MAX_CMD(i));
		अगर (val < 0)
			वापस val;

		drv_data->in_max[i] = val;
	पूर्ण
	वापस 0;
पूर्ण

अटल sमाप_प्रकार
label_show(काष्ठा device *dev, काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);

	वापस प्र_लिखो(buf, "%s\n", input_names[attr->index]);
पूर्ण

अटल sमाप_प्रकार
in_show(काष्ठा device *dev, काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा menf21bmc_hwmon *drv_data = menf21bmc_hwmon_update(dev);

	अगर (IS_ERR(drv_data))
		वापस PTR_ERR(drv_data);

	वापस प्र_लिखो(buf, "%d\n", drv_data->in_val[attr->index]);
पूर्ण

अटल sमाप_प्रकार
min_show(काष्ठा device *dev, काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा menf21bmc_hwmon *drv_data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", drv_data->in_min[attr->index]);
पूर्ण

अटल sमाप_प्रकार
max_show(काष्ठा device *dev, काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा menf21bmc_hwmon *drv_data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", drv_data->in_max[attr->index]);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(in0_input, in, 0);
अटल SENSOR_DEVICE_ATTR_RO(in0_min, min, 0);
अटल SENSOR_DEVICE_ATTR_RO(in0_max, max, 0);
अटल SENSOR_DEVICE_ATTR_RO(in0_label, label, 0);
अटल SENSOR_DEVICE_ATTR_RO(in1_input, in, 1);
अटल SENSOR_DEVICE_ATTR_RO(in1_min, min, 1);
अटल SENSOR_DEVICE_ATTR_RO(in1_max, max, 1);
अटल SENSOR_DEVICE_ATTR_RO(in1_label, label, 1);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, in, 2);
अटल SENSOR_DEVICE_ATTR_RO(in2_min, min, 2);
अटल SENSOR_DEVICE_ATTR_RO(in2_max, max, 2);
अटल SENSOR_DEVICE_ATTR_RO(in2_label, label, 2);
अटल SENSOR_DEVICE_ATTR_RO(in3_input, in, 3);
अटल SENSOR_DEVICE_ATTR_RO(in3_min, min, 3);
अटल SENSOR_DEVICE_ATTR_RO(in3_max, max, 3);
अटल SENSOR_DEVICE_ATTR_RO(in3_label, label, 3);
अटल SENSOR_DEVICE_ATTR_RO(in4_input, in, 4);
अटल SENSOR_DEVICE_ATTR_RO(in4_min, min, 4);
अटल SENSOR_DEVICE_ATTR_RO(in4_max, max, 4);
अटल SENSOR_DEVICE_ATTR_RO(in4_label, label, 4);

अटल काष्ठा attribute *menf21bmc_hwmon_attrs[] = अणु
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in0_min.dev_attr.attr,
	&sensor_dev_attr_in0_max.dev_attr.attr,
	&sensor_dev_attr_in0_label.dev_attr.attr,

	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_min.dev_attr.attr,
	&sensor_dev_attr_in1_max.dev_attr.attr,
	&sensor_dev_attr_in1_label.dev_attr.attr,

	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in2_min.dev_attr.attr,
	&sensor_dev_attr_in2_max.dev_attr.attr,
	&sensor_dev_attr_in2_label.dev_attr.attr,

	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in3_min.dev_attr.attr,
	&sensor_dev_attr_in3_max.dev_attr.attr,
	&sensor_dev_attr_in3_label.dev_attr.attr,

	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in4_min.dev_attr.attr,
	&sensor_dev_attr_in4_max.dev_attr.attr,
	&sensor_dev_attr_in4_label.dev_attr.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(menf21bmc_hwmon);

अटल पूर्णांक menf21bmc_hwmon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा menf21bmc_hwmon *drv_data;
	काष्ठा i2c_client *i2c_client = to_i2c_client(pdev->dev.parent);
	काष्ठा device *hwmon_dev;

	drv_data = devm_kzalloc(&pdev->dev, माप(काष्ठा menf21bmc_hwmon),
				GFP_KERNEL);
	अगर (!drv_data)
		वापस -ENOMEM;

	drv_data->i2c_client = i2c_client;

	ret = menf21bmc_hwmon_get_volt_limits(drv_data);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to read sensor limits");
		वापस ret;
	पूर्ण

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&pdev->dev,
						   "menf21bmc", drv_data,
						   menf21bmc_hwmon_groups);
	अगर (IS_ERR(hwmon_dev))
		वापस PTR_ERR(hwmon_dev);

	dev_info(&pdev->dev, "MEN 14F021P00 BMC hwmon device enabled");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver menf21bmc_hwmon = अणु
	.probe		= menf21bmc_hwmon_probe,
	.driver		= अणु
		.name		= DRV_NAME,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(menf21bmc_hwmon);

MODULE_AUTHOR("Andreas Werner <andreas.werner@men.de>");
MODULE_DESCRIPTION("MEN 14F021P00 BMC hwmon");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:menf21bmc_hwmon");
