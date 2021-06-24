<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम Lineage Compact Power Line series of घातer entry modules.
 *
 * Copyright (C) 2010, 2011 Ericsson AB.
 *
 * Documentation:
 *  http://www.lineageघातer.com/oem/pdf/CPLI2C.pdf
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/jअगरfies.h>

/*
 * This driver supports various Lineage Compact Power Line DC/DC and AC/DC
 * converters such as CP1800, CP2000AC, CP2000DC, CP2100DC, and others.
 *
 * The devices are nominally PMBus compliant. However, most standard PMBus
 * commands are not supported. Specअगरically, all hardware monitoring and
 * status reporting commands are non-standard. For this reason, a standard
 * PMBus driver can not be used.
 *
 * All Lineage CPL devices have a built-in I2C bus master selector (PCA9541).
 * To ensure device access, this driver should only be used as client driver
 * to the pca9541 I2C master selector driver.
 */

/* Command codes */
#घोषणा PEM_OPERATION		0x01
#घोषणा PEM_CLEAR_INFO_FLAGS	0x03
#घोषणा PEM_VOUT_COMMAND	0x21
#घोषणा PEM_VOUT_OV_FAULT_LIMIT	0x40
#घोषणा PEM_READ_DATA_STRING	0xd0
#घोषणा PEM_READ_INPUT_STRING	0xdc
#घोषणा PEM_READ_FIRMWARE_REV	0xdd
#घोषणा PEM_READ_RUN_TIMER	0xde
#घोषणा PEM_FAN_HI_SPEED	0xdf
#घोषणा PEM_FAN_NORMAL_SPEED	0xe0
#घोषणा PEM_READ_FAN_SPEED	0xe1

/* offsets in data string */
#घोषणा PEM_DATA_STATUS_2	0
#घोषणा PEM_DATA_STATUS_1	1
#घोषणा PEM_DATA_ALARM_2	2
#घोषणा PEM_DATA_ALARM_1	3
#घोषणा PEM_DATA_VOUT_LSB	4
#घोषणा PEM_DATA_VOUT_MSB	5
#घोषणा PEM_DATA_CURRENT	6
#घोषणा PEM_DATA_TEMP		7

/* Virtual entries, to report स्थिरants */
#घोषणा PEM_DATA_TEMP_MAX	10
#घोषणा PEM_DATA_TEMP_CRIT	11

/* offsets in input string */
#घोषणा PEM_INPUT_VOLTAGE	0
#घोषणा PEM_INPUT_POWER_LSB	1
#घोषणा PEM_INPUT_POWER_MSB	2

/* offsets in fan data */
#घोषणा PEM_FAN_ADJUSTMENT	0
#घोषणा PEM_FAN_FAN1		1
#घोषणा PEM_FAN_FAN2		2
#घोषणा PEM_FAN_FAN3		3

/* Status रेजिस्टर bits */
#घोषणा STS1_OUTPUT_ON		(1 << 0)
#घोषणा STS1_LEDS_FLASHING	(1 << 1)
#घोषणा STS1_EXT_FAULT		(1 << 2)
#घोषणा STS1_SERVICE_LED_ON	(1 << 3)
#घोषणा STS1_SHUTDOWN_OCCURRED	(1 << 4)
#घोषणा STS1_INT_FAULT		(1 << 5)
#घोषणा STS1_ISOLATION_TEST_OK	(1 << 6)

#घोषणा STS2_ENABLE_PIN_HI	(1 << 0)
#घोषणा STS2_DATA_OUT_RANGE	(1 << 1)
#घोषणा STS2_RESTARTED_OK	(1 << 1)
#घोषणा STS2_ISOLATION_TEST_FAIL (1 << 3)
#घोषणा STS2_HIGH_POWER_CAP	(1 << 4)
#घोषणा STS2_INVALID_INSTR	(1 << 5)
#घोषणा STS2_WILL_RESTART	(1 << 6)
#घोषणा STS2_PEC_ERR		(1 << 7)

/* Alarm रेजिस्टर bits */
#घोषणा ALRM1_VIN_OUT_LIMIT	(1 << 0)
#घोषणा ALRM1_VOUT_OUT_LIMIT	(1 << 1)
#घोषणा ALRM1_OV_VOLT_SHUTDOWN	(1 << 2)
#घोषणा ALRM1_VIN_OVERCURRENT	(1 << 3)
#घोषणा ALRM1_TEMP_WARNING	(1 << 4)
#घोषणा ALRM1_TEMP_SHUTDOWN	(1 << 5)
#घोषणा ALRM1_PRIMARY_FAULT	(1 << 6)
#घोषणा ALRM1_POWER_LIMIT	(1 << 7)

#घोषणा ALRM2_5V_OUT_LIMIT	(1 << 1)
#घोषणा ALRM2_TEMP_FAULT	(1 << 2)
#घोषणा ALRM2_OV_LOW		(1 << 3)
#घोषणा ALRM2_DCDC_TEMP_HIGH	(1 << 4)
#घोषणा ALRM2_PRI_TEMP_HIGH	(1 << 5)
#घोषणा ALRM2_NO_PRIMARY	(1 << 6)
#घोषणा ALRM2_FAN_FAULT		(1 << 7)

#घोषणा FIRMWARE_REV_LEN	4
#घोषणा DATA_STRING_LEN		9
#घोषणा INPUT_STRING_LEN	5	/* 4 क्रम most devices	*/
#घोषणा FAN_SPEED_LEN		5

काष्ठा pem_data अणु
	काष्ठा i2c_client *client;
	स्थिर काष्ठा attribute_group *groups[4];

	काष्ठा mutex update_lock;
	bool valid;
	bool fans_supported;
	पूर्णांक input_length;
	अचिन्हित दीर्घ last_updated;	/* in jअगरfies */

	u8 firmware_rev[FIRMWARE_REV_LEN];
	u8 data_string[DATA_STRING_LEN];
	u8 input_string[INPUT_STRING_LEN];
	u8 fan_speed[FAN_SPEED_LEN];
पूर्ण;

अटल पूर्णांक pem_पढ़ो_block(काष्ठा i2c_client *client, u8 command, u8 *data,
			  पूर्णांक data_len)
अणु
	u8 block_buffer[I2C_SMBUS_BLOCK_MAX];
	पूर्णांक result;

	result = i2c_smbus_पढ़ो_block_data(client, command, block_buffer);
	अगर (unlikely(result < 0))
		जाओ पात;
	अगर (unlikely(result == 0xff || result != data_len)) अणु
		result = -EIO;
		जाओ पात;
	पूर्ण
	स_नकल(data, block_buffer, data_len);
	result = 0;
पात:
	वापस result;
पूर्ण

अटल काष्ठा pem_data *pem_update_device(काष्ठा device *dev)
अणु
	काष्ठा pem_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	काष्ठा pem_data *ret = data;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ) || !data->valid) अणु
		पूर्णांक result;

		/* Read data string */
		result = pem_पढ़ो_block(client, PEM_READ_DATA_STRING,
					data->data_string,
					माप(data->data_string));
		अगर (unlikely(result < 0)) अणु
			ret = ERR_PTR(result);
			जाओ पात;
		पूर्ण

		/* Read input string */
		अगर (data->input_length) अणु
			result = pem_पढ़ो_block(client, PEM_READ_INPUT_STRING,
						data->input_string,
						data->input_length);
			अगर (unlikely(result < 0)) अणु
				ret = ERR_PTR(result);
				जाओ पात;
			पूर्ण
		पूर्ण

		/* Read fan speeds */
		अगर (data->fans_supported) अणु
			result = pem_पढ़ो_block(client, PEM_READ_FAN_SPEED,
						data->fan_speed,
						माप(data->fan_speed));
			अगर (unlikely(result < 0)) अणु
				ret = ERR_PTR(result);
				जाओ पात;
			पूर्ण
		पूर्ण

		i2c_smbus_ग_लिखो_byte(client, PEM_CLEAR_INFO_FLAGS);

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण
पात:
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल दीर्घ pem_get_data(u8 *data, पूर्णांक len, पूर्णांक index)
अणु
	दीर्घ val;

	चयन (index) अणु
	हाल PEM_DATA_VOUT_LSB:
		val = (data[index] + (data[index+1] << 8)) * 5 / 2;
		अवरोध;
	हाल PEM_DATA_CURRENT:
		val = data[index] * 200;
		अवरोध;
	हाल PEM_DATA_TEMP:
		val = data[index] * 1000;
		अवरोध;
	हाल PEM_DATA_TEMP_MAX:
		val = 97 * 1000;	/* 97 degrees C per datasheet */
		अवरोध;
	हाल PEM_DATA_TEMP_CRIT:
		val = 107 * 1000;	/* 107 degrees C per datasheet */
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		val = 0;
	पूर्ण
	वापस val;
पूर्ण

अटल दीर्घ pem_get_input(u8 *data, पूर्णांक len, पूर्णांक index)
अणु
	दीर्घ val;

	चयन (index) अणु
	हाल PEM_INPUT_VOLTAGE:
		अगर (len == INPUT_STRING_LEN)
			val = (data[index] + (data[index+1] << 8) - 75) * 1000;
		अन्यथा
			val = (data[index] - 75) * 1000;
		अवरोध;
	हाल PEM_INPUT_POWER_LSB:
		अगर (len == INPUT_STRING_LEN)
			index++;
		val = (data[index] + (data[index+1] << 8)) * 1000000L;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		val = 0;
	पूर्ण
	वापस val;
पूर्ण

अटल दीर्घ pem_get_fan(u8 *data, पूर्णांक len, पूर्णांक index)
अणु
	दीर्घ val;

	चयन (index) अणु
	हाल PEM_FAN_FAN1:
	हाल PEM_FAN_FAN2:
	हाल PEM_FAN_FAN3:
		val = data[index] * 100;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		val = 0;
	पूर्ण
	वापस val;
पूर्ण

/*
 * Show boolean, either a fault or an alarm.
 * .nr poपूर्णांकs to the रेजिस्टर, .index is the bit mask to check
 */
अटल sमाप_प्रकार pem_bool_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			     अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(da);
	काष्ठा pem_data *data = pem_update_device(dev);
	u8 status;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	status = data->data_string[attr->nr] & attr->index;
	वापस sysfs_emit(buf, "%d\n", !!status);
पूर्ण

अटल sमाप_प्रकार pem_data_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			     अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा pem_data *data = pem_update_device(dev);
	दीर्घ value;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	value = pem_get_data(data->data_string, माप(data->data_string),
			     attr->index);

	वापस sysfs_emit(buf, "%ld\n", value);
पूर्ण

अटल sमाप_प्रकार pem_input_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			      अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा pem_data *data = pem_update_device(dev);
	दीर्घ value;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	value = pem_get_input(data->input_string, माप(data->input_string),
			      attr->index);

	वापस sysfs_emit(buf, "%ld\n", value);
पूर्ण

अटल sमाप_प्रकार pem_fan_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			    अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा pem_data *data = pem_update_device(dev);
	दीर्घ value;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	value = pem_get_fan(data->fan_speed, माप(data->fan_speed),
			    attr->index);

	वापस sysfs_emit(buf, "%ld\n", value);
पूर्ण

/* Voltages */
अटल SENSOR_DEVICE_ATTR_RO(in1_input, pem_data, PEM_DATA_VOUT_LSB);
अटल SENSOR_DEVICE_ATTR_2_RO(in1_alarm, pem_bool, PEM_DATA_ALARM_1,
			       ALRM1_VOUT_OUT_LIMIT);
अटल SENSOR_DEVICE_ATTR_2_RO(in1_crit_alarm, pem_bool, PEM_DATA_ALARM_1,
			       ALRM1_OV_VOLT_SHUTDOWN);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, pem_input, PEM_INPUT_VOLTAGE);
अटल SENSOR_DEVICE_ATTR_2_RO(in2_alarm, pem_bool, PEM_DATA_ALARM_1,
			       ALRM1_VIN_OUT_LIMIT | ALRM1_PRIMARY_FAULT);

/* Currents */
अटल SENSOR_DEVICE_ATTR_RO(curr1_input, pem_data, PEM_DATA_CURRENT);
अटल SENSOR_DEVICE_ATTR_2_RO(curr1_alarm, pem_bool, PEM_DATA_ALARM_1,
			       ALRM1_VIN_OVERCURRENT);

/* Power */
अटल SENSOR_DEVICE_ATTR_RO(घातer1_input, pem_input, PEM_INPUT_POWER_LSB);
अटल SENSOR_DEVICE_ATTR_2_RO(घातer1_alarm, pem_bool, PEM_DATA_ALARM_1,
			       ALRM1_POWER_LIMIT);

/* Fans */
अटल SENSOR_DEVICE_ATTR_RO(fan1_input, pem_fan, PEM_FAN_FAN1);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, pem_fan, PEM_FAN_FAN2);
अटल SENSOR_DEVICE_ATTR_RO(fan3_input, pem_fan, PEM_FAN_FAN3);
अटल SENSOR_DEVICE_ATTR_2_RO(fan1_alarm, pem_bool, PEM_DATA_ALARM_2,
			       ALRM2_FAN_FAULT);

/* Temperatures */
अटल SENSOR_DEVICE_ATTR_RO(temp1_input, pem_data, PEM_DATA_TEMP);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max, pem_data, PEM_DATA_TEMP_MAX);
अटल SENSOR_DEVICE_ATTR_RO(temp1_crit, pem_data, PEM_DATA_TEMP_CRIT);
अटल SENSOR_DEVICE_ATTR_2_RO(temp1_alarm, pem_bool, PEM_DATA_ALARM_1,
			       ALRM1_TEMP_WARNING);
अटल SENSOR_DEVICE_ATTR_2_RO(temp1_crit_alarm, pem_bool, PEM_DATA_ALARM_1,
			       ALRM1_TEMP_SHUTDOWN);
अटल SENSOR_DEVICE_ATTR_2_RO(temp1_fault, pem_bool, PEM_DATA_ALARM_2,
			       ALRM2_TEMP_FAULT);

अटल काष्ठा attribute *pem_attributes[] = अणु
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_alarm.dev_attr.attr,
	&sensor_dev_attr_in1_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_in2_alarm.dev_attr.attr,

	&sensor_dev_attr_curr1_alarm.dev_attr.attr,

	&sensor_dev_attr_घातer1_alarm.dev_attr.attr,

	&sensor_dev_attr_fan1_alarm.dev_attr.attr,

	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_crit.dev_attr.attr,
	&sensor_dev_attr_temp1_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_fault.dev_attr.attr,

	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group pem_group = अणु
	.attrs = pem_attributes,
पूर्ण;

अटल काष्ठा attribute *pem_input_attributes[] = अणु
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_curr1_input.dev_attr.attr,
	&sensor_dev_attr_घातer1_input.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group pem_input_group = अणु
	.attrs = pem_input_attributes,
पूर्ण;

अटल काष्ठा attribute *pem_fan_attributes[] = अणु
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan3_input.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group pem_fan_group = अणु
	.attrs = pem_fan_attributes,
पूर्ण;

अटल पूर्णांक pem_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा pem_data *data;
	पूर्णांक ret, idx = 0;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BLOCK_DATA
				     | I2C_FUNC_SMBUS_WRITE_BYTE))
		वापस -ENODEV;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	/*
	 * We use the next two commands to determine अगर the device is really
	 * there.
	 */
	ret = pem_पढ़ो_block(client, PEM_READ_FIRMWARE_REV,
			     data->firmware_rev, माप(data->firmware_rev));
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_ग_लिखो_byte(client, PEM_CLEAR_INFO_FLAGS);
	अगर (ret < 0)
		वापस ret;

	dev_info(dev, "Firmware revision %d.%d.%d\n",
		 data->firmware_rev[0], data->firmware_rev[1],
		 data->firmware_rev[2]);

	/* sysfs hooks */
	data->groups[idx++] = &pem_group;

	/*
	 * Check अगर input पढ़ोings are supported.
	 * This is the हाल अगर we can पढ़ो input data,
	 * and अगर the वापसed data is not all zeros.
	 * Note that input alarms are always supported.
	 */
	ret = pem_पढ़ो_block(client, PEM_READ_INPUT_STRING,
			     data->input_string,
			     माप(data->input_string) - 1);
	अगर (!ret && (data->input_string[0] || data->input_string[1] ||
		     data->input_string[2]))
		data->input_length = माप(data->input_string) - 1;
	अन्यथा अगर (ret < 0) अणु
		/* Input string is one byte दीर्घer क्रम some devices */
		ret = pem_पढ़ो_block(client, PEM_READ_INPUT_STRING,
				    data->input_string,
				    माप(data->input_string));
		अगर (!ret && (data->input_string[0] || data->input_string[1] ||
			    data->input_string[2] || data->input_string[3]))
			data->input_length = माप(data->input_string);
	पूर्ण

	अगर (data->input_length)
		data->groups[idx++] = &pem_input_group;

	/*
	 * Check अगर fan speed पढ़ोings are supported.
	 * This is the हाल अगर we can पढ़ो fan speed data,
	 * and अगर the वापसed data is not all zeros.
	 * Note that the fan alarm is always supported.
	 */
	ret = pem_पढ़ो_block(client, PEM_READ_FAN_SPEED,
			     data->fan_speed,
			     माप(data->fan_speed));
	अगर (!ret && (data->fan_speed[0] || data->fan_speed[1] ||
		     data->fan_speed[2] || data->fan_speed[3])) अणु
		data->fans_supported = true;
		data->groups[idx++] = &pem_fan_group;
	पूर्ण

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data, data->groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id pem_id[] = अणु
	अणु"lineage_pem", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, pem_id);

अटल काष्ठा i2c_driver pem_driver = अणु
	.driver = अणु
		   .name = "lineage_pem",
		   पूर्ण,
	.probe_new = pem_probe,
	.id_table = pem_id,
पूर्ण;

module_i2c_driver(pem_driver);

MODULE_AUTHOR("Guenter Roeck <linux@roeck-us.net>");
MODULE_DESCRIPTION("Lineage CPL PEM hardware monitoring driver");
MODULE_LICENSE("GPL");
