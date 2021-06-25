<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * emc1403.c - SMSC Thermal Driver
 *
 * Copyright (C) 2008 Intel Corp
 *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regmap.h>

#घोषणा THERMAL_PID_REG		0xfd
#घोषणा THERMAL_SMSC_ID_REG	0xfe
#घोषणा THERMAL_REVISION_REG	0xff

क्रमागत emc1403_chip अणु emc1402, emc1403, emc1404 पूर्ण;

काष्ठा thermal_data अणु
	काष्ठा regmap *regmap;
	काष्ठा mutex mutex;
	स्थिर काष्ठा attribute_group *groups[4];
पूर्ण;

अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *sda = to_sensor_dev_attr(attr);
	काष्ठा thermal_data *data = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक retval;

	retval = regmap_पढ़ो(data->regmap, sda->index, &val);
	अगर (retval < 0)
		वापस retval;
	वापस प्र_लिखो(buf, "%d000\n", val);
पूर्ण

अटल sमाप_प्रकार bit_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *sda = to_sensor_dev_attr_2(attr);
	काष्ठा thermal_data *data = dev_get_drvdata(dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक retval;

	retval = regmap_पढ़ो(data->regmap, sda->nr, &val);
	अगर (retval < 0)
		वापस retval;
	वापस प्र_लिखो(buf, "%d\n", !!(val & sda->index));
पूर्ण

अटल sमाप_प्रकार temp_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sda = to_sensor_dev_attr(attr);
	काष्ठा thermal_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक retval;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;
	retval = regmap_ग_लिखो(data->regmap, sda->index,
			      DIV_ROUND_CLOSEST(val, 1000));
	अगर (retval < 0)
		वापस retval;
	वापस count;
पूर्ण

अटल sमाप_प्रकार bit_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *sda = to_sensor_dev_attr_2(attr);
	काष्ठा thermal_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक retval;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;

	retval = regmap_update_bits(data->regmap, sda->nr, sda->index,
				    val ? sda->index : 0);
	अगर (retval < 0)
		वापस retval;
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_hyst_common(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf,
				bool is_min)
अणु
	काष्ठा sensor_device_attribute *sda = to_sensor_dev_attr(attr);
	काष्ठा thermal_data *data = dev_get_drvdata(dev);
	काष्ठा regmap *regmap = data->regmap;
	अचिन्हित पूर्णांक limit;
	अचिन्हित पूर्णांक hyst;
	पूर्णांक retval;

	retval = regmap_पढ़ो(regmap, sda->index, &limit);
	अगर (retval < 0)
		वापस retval;

	retval = regmap_पढ़ो(regmap, 0x21, &hyst);
	अगर (retval < 0)
		वापस retval;

	वापस प्र_लिखो(buf, "%d000\n", is_min ? limit + hyst : limit - hyst);
पूर्ण

अटल sमाप_प्रकार hyst_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	वापस show_hyst_common(dev, attr, buf, false);
पूर्ण

अटल sमाप_प्रकार min_hyst_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस show_hyst_common(dev, attr, buf, true);
पूर्ण

अटल sमाप_प्रकार hyst_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *sda = to_sensor_dev_attr(attr);
	काष्ठा thermal_data *data = dev_get_drvdata(dev);
	काष्ठा regmap *regmap = data->regmap;
	अचिन्हित पूर्णांक limit;
	पूर्णांक retval;
	पूर्णांक hyst;
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;

	mutex_lock(&data->mutex);
	retval = regmap_पढ़ो(regmap, sda->index, &limit);
	अगर (retval < 0)
		जाओ fail;

	hyst = limit * 1000 - val;
	hyst = clamp_val(DIV_ROUND_CLOSEST(hyst, 1000), 0, 255);
	retval = regmap_ग_लिखो(regmap, 0x21, hyst);
	अगर (retval == 0)
		retval = count;
fail:
	mutex_unlock(&data->mutex);
	वापस retval;
पूर्ण

/*
 *	Sensors. We pass the actual i2c रेजिस्टर to the methods.
 */

अटल SENSOR_DEVICE_ATTR_RW(temp1_min, temp, 0x06);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp, 0x05);
अटल SENSOR_DEVICE_ATTR_RW(temp1_crit, temp, 0x20);
अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, 0x00);
अटल SENSOR_DEVICE_ATTR_2_RO(temp1_min_alarm, bit, 0x36, 0x01);
अटल SENSOR_DEVICE_ATTR_2_RO(temp1_max_alarm, bit, 0x35, 0x01);
अटल SENSOR_DEVICE_ATTR_2_RO(temp1_crit_alarm, bit, 0x37, 0x01);
अटल SENSOR_DEVICE_ATTR_RO(temp1_min_hyst, min_hyst, 0x06);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max_hyst, hyst, 0x05);
अटल SENSOR_DEVICE_ATTR_RW(temp1_crit_hyst, hyst, 0x20);

अटल SENSOR_DEVICE_ATTR_RW(temp2_min, temp, 0x08);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max, temp, 0x07);
अटल SENSOR_DEVICE_ATTR_RW(temp2_crit, temp, 0x19);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp, 0x01);
अटल SENSOR_DEVICE_ATTR_2_RO(temp2_fault, bit, 0x1b, 0x02);
अटल SENSOR_DEVICE_ATTR_2_RO(temp2_min_alarm, bit, 0x36, 0x02);
अटल SENSOR_DEVICE_ATTR_2_RO(temp2_max_alarm, bit, 0x35, 0x02);
अटल SENSOR_DEVICE_ATTR_2_RO(temp2_crit_alarm, bit, 0x37, 0x02);
अटल SENSOR_DEVICE_ATTR_RO(temp2_min_hyst, min_hyst, 0x08);
अटल SENSOR_DEVICE_ATTR_RO(temp2_max_hyst, hyst, 0x07);
अटल SENSOR_DEVICE_ATTR_RO(temp2_crit_hyst, hyst, 0x19);

अटल SENSOR_DEVICE_ATTR_RW(temp3_min, temp, 0x16);
अटल SENSOR_DEVICE_ATTR_RW(temp3_max, temp, 0x15);
अटल SENSOR_DEVICE_ATTR_RW(temp3_crit, temp, 0x1A);
अटल SENSOR_DEVICE_ATTR_RO(temp3_input, temp, 0x23);
अटल SENSOR_DEVICE_ATTR_2_RO(temp3_fault, bit, 0x1b, 0x04);
अटल SENSOR_DEVICE_ATTR_2_RO(temp3_min_alarm, bit, 0x36, 0x04);
अटल SENSOR_DEVICE_ATTR_2_RO(temp3_max_alarm, bit, 0x35, 0x04);
अटल SENSOR_DEVICE_ATTR_2_RO(temp3_crit_alarm, bit, 0x37, 0x04);
अटल SENSOR_DEVICE_ATTR_RO(temp3_min_hyst, min_hyst, 0x16);
अटल SENSOR_DEVICE_ATTR_RO(temp3_max_hyst, hyst, 0x15);
अटल SENSOR_DEVICE_ATTR_RO(temp3_crit_hyst, hyst, 0x1A);

अटल SENSOR_DEVICE_ATTR_RW(temp4_min, temp, 0x2D);
अटल SENSOR_DEVICE_ATTR_RW(temp4_max, temp, 0x2C);
अटल SENSOR_DEVICE_ATTR_RW(temp4_crit, temp, 0x30);
अटल SENSOR_DEVICE_ATTR_RO(temp4_input, temp, 0x2A);
अटल SENSOR_DEVICE_ATTR_2_RO(temp4_fault, bit, 0x1b, 0x08);
अटल SENSOR_DEVICE_ATTR_2_RO(temp4_min_alarm, bit, 0x36, 0x08);
अटल SENSOR_DEVICE_ATTR_2_RO(temp4_max_alarm, bit, 0x35, 0x08);
अटल SENSOR_DEVICE_ATTR_2_RO(temp4_crit_alarm, bit, 0x37, 0x08);
अटल SENSOR_DEVICE_ATTR_RO(temp4_min_hyst, min_hyst, 0x2D);
अटल SENSOR_DEVICE_ATTR_RO(temp4_max_hyst, hyst, 0x2C);
अटल SENSOR_DEVICE_ATTR_RO(temp4_crit_hyst, hyst, 0x30);

अटल SENSOR_DEVICE_ATTR_2_RW(घातer_state, bit, 0x03, 0x40);

अटल काष्ठा attribute *emc1402_attrs[] = अणु
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_crit.dev_attr.attr,
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_min_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_hyst.dev_attr.attr,

	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_crit.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_min_hyst.dev_attr.attr,
	&sensor_dev_attr_temp2_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp2_crit_hyst.dev_attr.attr,

	&sensor_dev_attr_घातer_state.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group emc1402_group = अणु
		.attrs = emc1402_attrs,
पूर्ण;

अटल काष्ठा attribute *emc1403_attrs[] = अणु
	&sensor_dev_attr_temp1_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_alarm.dev_attr.attr,

	&sensor_dev_attr_temp2_fault.dev_attr.attr,
	&sensor_dev_attr_temp2_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_crit_alarm.dev_attr.attr,

	&sensor_dev_attr_temp3_min.dev_attr.attr,
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp3_crit.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp3_fault.dev_attr.attr,
	&sensor_dev_attr_temp3_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_min_hyst.dev_attr.attr,
	&sensor_dev_attr_temp3_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp3_crit_hyst.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group emc1403_group = अणु
	.attrs = emc1403_attrs,
पूर्ण;

अटल काष्ठा attribute *emc1404_attrs[] = अणु
	&sensor_dev_attr_temp4_min.dev_attr.attr,
	&sensor_dev_attr_temp4_max.dev_attr.attr,
	&sensor_dev_attr_temp4_crit.dev_attr.attr,
	&sensor_dev_attr_temp4_input.dev_attr.attr,
	&sensor_dev_attr_temp4_fault.dev_attr.attr,
	&sensor_dev_attr_temp4_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp4_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp4_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp4_min_hyst.dev_attr.attr,
	&sensor_dev_attr_temp4_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp4_crit_hyst.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group emc1404_group = अणु
	.attrs = emc1404_attrs,
पूर्ण;

/*
 * EMC14x2 uses a dअगरferent रेजिस्टर and dअगरferent bits to report alarm and
 * fault status. For simplicity, provide a separate attribute group क्रम this
 * chip series.
 * Since we can not re-use the same attribute names, create a separate attribute
 * array.
 */
अटल काष्ठा sensor_device_attribute_2 emc1402_alarms[] = अणु
	SENSOR_ATTR_2_RO(temp1_min_alarm, bit, 0x02, 0x20),
	SENSOR_ATTR_2_RO(temp1_max_alarm, bit, 0x02, 0x40),
	SENSOR_ATTR_2_RO(temp1_crit_alarm, bit, 0x02, 0x01),

	SENSOR_ATTR_2_RO(temp2_fault, bit, 0x02, 0x04),
	SENSOR_ATTR_2_RO(temp2_min_alarm, bit, 0x02, 0x08),
	SENSOR_ATTR_2_RO(temp2_max_alarm, bit, 0x02, 0x10),
	SENSOR_ATTR_2_RO(temp2_crit_alarm, bit, 0x02, 0x02),
पूर्ण;

अटल काष्ठा attribute *emc1402_alarm_attrs[] = अणु
	&emc1402_alarms[0].dev_attr.attr,
	&emc1402_alarms[1].dev_attr.attr,
	&emc1402_alarms[2].dev_attr.attr,
	&emc1402_alarms[3].dev_attr.attr,
	&emc1402_alarms[4].dev_attr.attr,
	&emc1402_alarms[5].dev_attr.attr,
	&emc1402_alarms[6].dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group emc1402_alarm_group = अणु
	.attrs = emc1402_alarm_attrs,
पूर्ण;

अटल पूर्णांक emc1403_detect(काष्ठा i2c_client *client,
			काष्ठा i2c_board_info *info)
अणु
	पूर्णांक id;
	/* Check अगर thermal chip is SMSC and EMC1403 or EMC1423 */

	id = i2c_smbus_पढ़ो_byte_data(client, THERMAL_SMSC_ID_REG);
	अगर (id != 0x5d)
		वापस -ENODEV;

	id = i2c_smbus_पढ़ो_byte_data(client, THERMAL_PID_REG);
	चयन (id) अणु
	हाल 0x20:
		strlcpy(info->type, "emc1402", I2C_NAME_SIZE);
		अवरोध;
	हाल 0x21:
		strlcpy(info->type, "emc1403", I2C_NAME_SIZE);
		अवरोध;
	हाल 0x22:
		strlcpy(info->type, "emc1422", I2C_NAME_SIZE);
		अवरोध;
	हाल 0x23:
		strlcpy(info->type, "emc1423", I2C_NAME_SIZE);
		अवरोध;
	हाल 0x25:
		strlcpy(info->type, "emc1404", I2C_NAME_SIZE);
		अवरोध;
	हाल 0x27:
		strlcpy(info->type, "emc1424", I2C_NAME_SIZE);
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	id = i2c_smbus_पढ़ो_byte_data(client, THERMAL_REVISION_REG);
	अगर (id < 0x01 || id > 0x04)
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल bool emc1403_regmap_is_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल 0x00:	/* पूर्णांकernal diode high byte */
	हाल 0x01:	/* बाह्यal diode 1 high byte */
	हाल 0x02:	/* status */
	हाल 0x10:	/* बाह्यal diode 1 low byte */
	हाल 0x1b:	/* बाह्यal diode fault */
	हाल 0x23:	/* बाह्यal diode 2 high byte */
	हाल 0x24:	/* बाह्यal diode 2 low byte */
	हाल 0x29:	/* पूर्णांकernal diode low byte */
	हाल 0x2a:	/* बाह्यl diode 3 high byte */
	हाल 0x2b:	/* बाह्यal diode 3 low byte */
	हाल 0x35:	/* high limit status */
	हाल 0x36:	/* low limit status */
	हाल 0x37:	/* therm limit status */
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config emc1403_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_reg = emc1403_regmap_is_अस्थिर,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id emc1403_idtable[];

अटल पूर्णांक emc1403_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा thermal_data *data;
	काष्ठा device *hwmon_dev;
	स्थिर काष्ठा i2c_device_id *id = i2c_match_id(emc1403_idtable, client);

	data = devm_kzalloc(&client->dev, माप(काष्ठा thermal_data),
			    GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;

	data->regmap = devm_regmap_init_i2c(client, &emc1403_regmap_config);
	अगर (IS_ERR(data->regmap))
		वापस PTR_ERR(data->regmap);

	mutex_init(&data->mutex);

	चयन (id->driver_data) अणु
	हाल emc1404:
		data->groups[2] = &emc1404_group;
		fallthrough;
	हाल emc1403:
		data->groups[1] = &emc1403_group;
		fallthrough;
	हाल emc1402:
		data->groups[0] = &emc1402_group;
	पूर्ण

	अगर (id->driver_data == emc1402)
		data->groups[1] = &emc1402_alarm_group;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&client->dev,
							   client->name, data,
							   data->groups);
	अगर (IS_ERR(hwmon_dev))
		वापस PTR_ERR(hwmon_dev);

	dev_info(&client->dev, "%s Thermal chip found\n", id->name);
	वापस 0;
पूर्ण

अटल स्थिर अचिन्हित लघु emc1403_address_list[] = अणु
	0x18, 0x1c, 0x29, 0x4c, 0x4d, 0x5c, I2C_CLIENT_END
पूर्ण;

/* Last digit of chip name indicates number of channels */
अटल स्थिर काष्ठा i2c_device_id emc1403_idtable[] = अणु
	अणु "emc1402", emc1402 पूर्ण,
	अणु "emc1403", emc1403 पूर्ण,
	अणु "emc1404", emc1404 पूर्ण,
	अणु "emc1412", emc1402 पूर्ण,
	अणु "emc1413", emc1403 पूर्ण,
	अणु "emc1414", emc1404 पूर्ण,
	अणु "emc1422", emc1402 पूर्ण,
	अणु "emc1423", emc1403 पूर्ण,
	अणु "emc1424", emc1404 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, emc1403_idtable);

अटल काष्ठा i2c_driver sensor_emc1403 = अणु
	.class = I2C_CLASS_HWMON,
	.driver = अणु
		.name = "emc1403",
	पूर्ण,
	.detect = emc1403_detect,
	.probe_new = emc1403_probe,
	.id_table = emc1403_idtable,
	.address_list = emc1403_address_list,
पूर्ण;

module_i2c_driver(sensor_emc1403);

MODULE_AUTHOR("Kalhan Trisal <kalhan.trisal@intel.com");
MODULE_DESCRIPTION("emc1403 Thermal Driver");
MODULE_LICENSE("GPL v2");
