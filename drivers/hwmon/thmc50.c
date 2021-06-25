<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * thmc50.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *	      monitoring
 * Copyright (C) 2007 Krzysztof Helt <krzysztof.h1@wp.pl>
 * Based on 2.4 driver by Froकरो Looijaard <froकरोl@dds.nl> and
 * Philip Edelbrock <phil@netroedge.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/jअगरfies.h>

MODULE_LICENSE("GPL");

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2c, 0x2d, 0x2e, I2C_CLIENT_END पूर्ण;

/* Insmod parameters */
क्रमागत chips अणु thmc50, adm1022 पूर्ण;

अटल अचिन्हित लघु adm1022_temp3[16];
अटल अचिन्हित पूर्णांक adm1022_temp3_num;
module_param_array(adm1022_temp3, uलघु, &adm1022_temp3_num, 0);
MODULE_PARM_DESC(adm1022_temp3,
		 "List of adapter,address pairs to enable 3rd temperature (ADM1022 only)");

/* Many THMC50 स्थिरants specअगरied below */

/* The THMC50 रेजिस्टरs */
#घोषणा THMC50_REG_CONF				0x40
#घोषणा THMC50_REG_COMPANY_ID			0x3E
#घोषणा THMC50_REG_DIE_CODE			0x3F
#घोषणा THMC50_REG_ANALOG_OUT			0x19
/*
 * The mirror status रेजिस्टर cannot be used as
 * पढ़ोing it करोes not clear alarms.
 */
#घोषणा THMC50_REG_INTR				0x41

अटल स्थिर u8 THMC50_REG_TEMP[] = अणु 0x27, 0x26, 0x20 पूर्ण;
अटल स्थिर u8 THMC50_REG_TEMP_MIN[] = अणु 0x3A, 0x38, 0x2C पूर्ण;
अटल स्थिर u8 THMC50_REG_TEMP_MAX[] = अणु 0x39, 0x37, 0x2B पूर्ण;
अटल स्थिर u8 THMC50_REG_TEMP_CRITICAL[] = अणु 0x13, 0x14, 0x14 पूर्ण;
अटल स्थिर u8 THMC50_REG_TEMP_DEFAULT[] = अणु 0x17, 0x18, 0x18 पूर्ण;

#घोषणा THMC50_REG_CONF_nFANOFF			0x20
#घोषणा THMC50_REG_CONF_PROGRAMMED		0x08

/* Each client has this additional data */
काष्ठा thmc50_data अणु
	काष्ठा i2c_client *client;
	स्थिर काष्ठा attribute_group *groups[3];

	काष्ठा mutex update_lock;
	क्रमागत chips type;
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */
	अक्षर has_temp3;		/* !=0 अगर it is ADM1022 in temp3 mode */
	अक्षर valid;		/* !=0 अगर following fields are valid */

	/* Register values */
	s8 temp_input[3];
	s8 temp_max[3];
	s8 temp_min[3];
	s8 temp_critical[3];
	u8 analog_out;
	u8 alarms;
पूर्ण;

अटल काष्ठा thmc50_data *thmc50_update_device(काष्ठा device *dev)
अणु
	काष्ठा thmc50_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक समयout = HZ / 5 + (data->type == thmc50 ? HZ : 0);

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + समयout)
	    || !data->valid) अणु

		पूर्णांक temps = data->has_temp3 ? 3 : 2;
		पूर्णांक i;
		पूर्णांक prog = i2c_smbus_पढ़ो_byte_data(client, THMC50_REG_CONF);

		prog &= THMC50_REG_CONF_PROGRAMMED;

		क्रम (i = 0; i < temps; i++) अणु
			data->temp_input[i] = i2c_smbus_पढ़ो_byte_data(client,
						THMC50_REG_TEMP[i]);
			data->temp_max[i] = i2c_smbus_पढ़ो_byte_data(client,
						THMC50_REG_TEMP_MAX[i]);
			data->temp_min[i] = i2c_smbus_पढ़ो_byte_data(client,
						THMC50_REG_TEMP_MIN[i]);
			data->temp_critical[i] =
				i2c_smbus_पढ़ो_byte_data(client,
					prog ? THMC50_REG_TEMP_CRITICAL[i]
					     : THMC50_REG_TEMP_DEFAULT[i]);
		पूर्ण
		data->analog_out =
		    i2c_smbus_पढ़ो_byte_data(client, THMC50_REG_ANALOG_OUT);
		data->alarms =
		    i2c_smbus_पढ़ो_byte_data(client, THMC50_REG_INTR);
		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

अटल sमाप_प्रकार analog_out_show(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा thmc50_data *data = thmc50_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->analog_out);
पूर्ण

अटल sमाप_प्रकार analog_out_store(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा thmc50_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक config;
	अचिन्हित दीर्घ पंचांगp;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &पंचांगp);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->analog_out = clamp_val(पंचांगp, 0, 255);
	i2c_smbus_ग_लिखो_byte_data(client, THMC50_REG_ANALOG_OUT,
				  data->analog_out);

	config = i2c_smbus_पढ़ो_byte_data(client, THMC50_REG_CONF);
	अगर (data->analog_out == 0)
		config &= ~THMC50_REG_CONF_nFANOFF;
	अन्यथा
		config |= THMC50_REG_CONF_nFANOFF;
	i2c_smbus_ग_लिखो_byte_data(client, THMC50_REG_CONF, config);

	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

/* There is only one PWM mode = DC */
अटल sमाप_प्रकार pwm_mode_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "0\n");
पूर्ण

/* Temperatures */
अटल sमाप_प्रकार temp_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा thmc50_data *data = thmc50_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->temp_input[nr] * 1000);
पूर्ण

अटल sमाप_प्रकार temp_min_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा thmc50_data *data = thmc50_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->temp_min[nr] * 1000);
पूर्ण

अटल sमाप_प्रकार temp_min_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा thmc50_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_min[nr] = clamp_val(val / 1000, -128, 127);
	i2c_smbus_ग_लिखो_byte_data(client, THMC50_REG_TEMP_MIN[nr],
				  data->temp_min[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_max_show(काष्ठा device *dev,
			     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा thmc50_data *data = thmc50_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->temp_max[nr] * 1000);
पूर्ण

अटल sमाप_प्रकार temp_max_store(काष्ठा device *dev,
			      काष्ठा device_attribute *attr, स्थिर अक्षर *buf,
			      माप_प्रकार count)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा thmc50_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	दीर्घ val;
	पूर्णांक err;

	err = kम_से_दीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;

	mutex_lock(&data->update_lock);
	data->temp_max[nr] = clamp_val(val / 1000, -128, 127);
	i2c_smbus_ग_लिखो_byte_data(client, THMC50_REG_TEMP_MAX[nr],
				  data->temp_max[nr]);
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp_critical_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nr = to_sensor_dev_attr(attr)->index;
	काष्ठा thmc50_data *data = thmc50_update_device(dev);
	वापस प्र_लिखो(buf, "%d\n", data->temp_critical[nr] * 1000);
पूर्ण

अटल sमाप_प्रकार alarm_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			  अक्षर *buf)
अणु
	पूर्णांक index = to_sensor_dev_attr(attr)->index;
	काष्ठा thmc50_data *data = thmc50_update_device(dev);

	वापस प्र_लिखो(buf, "%u\n", (data->alarms >> index) & 1);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_min, temp_min, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp_max, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp1_crit, temp_critical, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_min, temp_min, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp2_max, temp_max, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp2_crit, temp_critical, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_input, temp, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_min, temp_min, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp3_max, temp_max, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp3_crit, temp_critical, 2);

अटल SENSOR_DEVICE_ATTR_RO(temp1_alarm, alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_alarm, alarm, 5);
अटल SENSOR_DEVICE_ATTR_RO(temp3_alarm, alarm, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp2_fault, alarm, 7);
अटल SENSOR_DEVICE_ATTR_RO(temp3_fault, alarm, 2);

अटल SENSOR_DEVICE_ATTR_RW(pwm1, analog_out, 0);
अटल SENSOR_DEVICE_ATTR_RO(pwm1_mode, pwm_mode, 0);

अटल काष्ठा attribute *thmc50_attributes[] = अणु
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_crit.dev_attr.attr,
	&sensor_dev_attr_temp1_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_max.dev_attr.attr,
	&sensor_dev_attr_temp2_min.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp2_crit.dev_attr.attr,
	&sensor_dev_attr_temp2_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_fault.dev_attr.attr,
	&sensor_dev_attr_pwm1.dev_attr.attr,
	&sensor_dev_attr_pwm1_mode.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group thmc50_group = अणु
	.attrs = thmc50_attributes,
पूर्ण;

/* क्रम ADM1022 3rd temperature mode */
अटल काष्ठा attribute *temp3_attributes[] = अणु
	&sensor_dev_attr_temp3_max.dev_attr.attr,
	&sensor_dev_attr_temp3_min.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp3_crit.dev_attr.attr,
	&sensor_dev_attr_temp3_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_fault.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group temp3_group = अणु
	.attrs = temp3_attributes,
पूर्ण;

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक thmc50_detect(काष्ठा i2c_client *client,
			 काष्ठा i2c_board_info *info)
अणु
	अचिन्हित company;
	अचिन्हित revision;
	अचिन्हित config;
	काष्ठा i2c_adapter *adapter = client->adapter;
	स्थिर अक्षर *type_name;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) अणु
		pr_debug("thmc50: detect failed, smbus byte data not supported!\n");
		वापस -ENODEV;
	पूर्ण

	pr_debug("thmc50: Probing for THMC50 at 0x%2X on bus %d\n",
		 client->addr, i2c_adapter_id(client->adapter));

	company = i2c_smbus_पढ़ो_byte_data(client, THMC50_REG_COMPANY_ID);
	revision = i2c_smbus_पढ़ो_byte_data(client, THMC50_REG_DIE_CODE);
	config = i2c_smbus_पढ़ो_byte_data(client, THMC50_REG_CONF);
	अगर (revision < 0xc0 || (config & 0x10))
		वापस -ENODEV;

	अगर (company == 0x41) अणु
		पूर्णांक id = i2c_adapter_id(client->adapter);
		पूर्णांक i;

		type_name = "adm1022";
		क्रम (i = 0; i + 1 < adm1022_temp3_num; i += 2)
			अगर (adm1022_temp3[i] == id &&
			    adm1022_temp3[i + 1] == client->addr) अणु
				/* enable 2nd remote temp */
				config |= (1 << 7);
				i2c_smbus_ग_लिखो_byte_data(client,
							  THMC50_REG_CONF,
							  config);
				अवरोध;
			पूर्ण
	पूर्ण अन्यथा अगर (company == 0x49) अणु
		type_name = "thmc50";
	पूर्ण अन्यथा अणु
		pr_debug("thmc50: Detection of THMC50/ADM1022 failed\n");
		वापस -ENODEV;
	पूर्ण

	pr_debug("thmc50: Detected %s (version %x, revision %x)\n",
		 type_name, (revision >> 4) - 0xc, revision & 0xf);

	strlcpy(info->type, type_name, I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल व्योम thmc50_init_client(काष्ठा thmc50_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक config;

	data->analog_out = i2c_smbus_पढ़ो_byte_data(client,
						    THMC50_REG_ANALOG_OUT);
	/* set up to at least 1 */
	अगर (data->analog_out == 0) अणु
		data->analog_out = 1;
		i2c_smbus_ग_लिखो_byte_data(client, THMC50_REG_ANALOG_OUT,
					  data->analog_out);
	पूर्ण
	config = i2c_smbus_पढ़ो_byte_data(client, THMC50_REG_CONF);
	config |= 0x1;	/* start the chip अगर it is in standby mode */
	अगर (data->type == adm1022 && (config & (1 << 7)))
		data->has_temp3 = 1;
	i2c_smbus_ग_लिखो_byte_data(client, THMC50_REG_CONF, config);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id thmc50_id[];

अटल पूर्णांक thmc50_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा thmc50_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक idx = 0;

	data = devm_kzalloc(dev, माप(काष्ठा thmc50_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	data->type = i2c_match_id(thmc50_id, client)->driver_data;
	mutex_init(&data->update_lock);

	thmc50_init_client(data);

	/* sysfs hooks */
	data->groups[idx++] = &thmc50_group;

	/* Register additional ADM1022 sysfs hooks */
	अगर (data->has_temp3)
		data->groups[idx++] = &temp3_group;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data, data->groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id thmc50_id[] = अणु
	अणु "adm1022", adm1022 पूर्ण,
	अणु "thmc50", thmc50 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, thmc50_id);

अटल काष्ठा i2c_driver thmc50_driver = अणु
	.class = I2C_CLASS_HWMON,
	.driver = अणु
		.name = "thmc50",
	पूर्ण,
	.probe_new = thmc50_probe,
	.id_table = thmc50_id,
	.detect = thmc50_detect,
	.address_list = normal_i2c,
पूर्ण;

module_i2c_driver(thmc50_driver);

MODULE_AUTHOR("Krzysztof Helt <krzysztof.h1@wp.pl>");
MODULE_DESCRIPTION("THMC50 driver");
