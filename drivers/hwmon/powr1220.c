<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * घातr1220.c - Driver क्रम the Lattice POWR1220 programmable घातer supply
 * and monitor. Users can पढ़ो all ADC inमाला_दो aदीर्घ with their labels
 * using the sysfs nodes.
 *
 * Copyright (c) 2014 Echo360 https://www.echo360.com
 * Scott Kanowitz <skanowitz@echo360.com> <scott.kanowitz@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>

#घोषणा ADC_STEP_MV			2
#घोषणा ADC_MAX_LOW_MEASUREMENT_MV	2000

क्रमागत घातr1220_regs अणु
	VMON_STATUS0,
	VMON_STATUS1,
	VMON_STATUS2,
	OUTPUT_STATUS0,
	OUTPUT_STATUS1,
	OUTPUT_STATUS2,
	INPUT_STATUS,
	ADC_VALUE_LOW,
	ADC_VALUE_HIGH,
	ADC_MUX,
	UES_BYTE0,
	UES_BYTE1,
	UES_BYTE2,
	UES_BYTE3,
	GP_OUTPUT1,
	GP_OUTPUT2,
	GP_OUTPUT3,
	INPUT_VALUE,
	RESET,
	TRIM1_TRIM,
	TRIM2_TRIM,
	TRIM3_TRIM,
	TRIM4_TRIM,
	TRIM5_TRIM,
	TRIM6_TRIM,
	TRIM7_TRIM,
	TRIM8_TRIM,
	MAX_POWR1220_REGS
पूर्ण;

क्रमागत घातr1220_adc_values अणु
	VMON1,
	VMON2,
	VMON3,
	VMON4,
	VMON5,
	VMON6,
	VMON7,
	VMON8,
	VMON9,
	VMON10,
	VMON11,
	VMON12,
	VCCA,
	VCCINP,
	MAX_POWR1220_ADC_VALUES
पूर्ण;

काष्ठा घातr1220_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex update_lock;
	bool adc_valid[MAX_POWR1220_ADC_VALUES];
	 /* the next value is in jअगरfies */
	अचिन्हित दीर्घ adc_last_updated[MAX_POWR1220_ADC_VALUES];

	/* values */
	पूर्णांक adc_maxes[MAX_POWR1220_ADC_VALUES];
	पूर्णांक adc_values[MAX_POWR1220_ADC_VALUES];
पूर्ण;

अटल स्थिर अक्षर * स्थिर input_names[] = अणु
	[VMON1]    = "vmon1",
	[VMON2]    = "vmon2",
	[VMON3]    = "vmon3",
	[VMON4]    = "vmon4",
	[VMON5]    = "vmon5",
	[VMON6]    = "vmon6",
	[VMON7]    = "vmon7",
	[VMON8]    = "vmon8",
	[VMON9]    = "vmon9",
	[VMON10]   = "vmon10",
	[VMON11]   = "vmon11",
	[VMON12]   = "vmon12",
	[VCCA]     = "vcca",
	[VCCINP]   = "vccinp",
पूर्ण;

/* Reads the specअगरied ADC channel */
अटल पूर्णांक घातr1220_पढ़ो_adc(काष्ठा device *dev, पूर्णांक ch_num)
अणु
	काष्ठा घातr1220_data *data = dev_get_drvdata(dev);
	पूर्णांक पढ़ोing;
	पूर्णांक result;
	पूर्णांक adc_range = 0;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->adc_last_updated[ch_num] + HZ) ||
			!data->adc_valid[ch_num]) अणु
		/*
		 * figure out अगर we need to use the attenuator क्रम
		 * high inमाला_दो or inमाला_दो that we करोn't yet have a measurement
		 * क्रम. We dynamically set the attenuator depending on the
		 * max पढ़ोing.
		 */
		अगर (data->adc_maxes[ch_num] > ADC_MAX_LOW_MEASUREMENT_MV ||
				data->adc_maxes[ch_num] == 0)
			adc_range = 1 << 4;

		/* set the attenuator and mux */
		result = i2c_smbus_ग_लिखो_byte_data(data->client, ADC_MUX,
				adc_range | ch_num);
		अगर (result)
			जाओ निकास;

		/*
		 * रुको at least Tconvert समय (200 us) क्रम the
		 * conversion to complete
		 */
		udelay(200);

		/* get the ADC पढ़ोing */
		result = i2c_smbus_पढ़ो_byte_data(data->client, ADC_VALUE_LOW);
		अगर (result < 0)
			जाओ निकास;

		पढ़ोing = result >> 4;

		/* get the upper half of the पढ़ोing */
		result = i2c_smbus_पढ़ो_byte_data(data->client, ADC_VALUE_HIGH);
		अगर (result < 0)
			जाओ निकास;

		पढ़ोing |= result << 4;

		/* now convert the पढ़ोing to a voltage */
		पढ़ोing *= ADC_STEP_MV;
		data->adc_values[ch_num] = पढ़ोing;
		data->adc_valid[ch_num] = true;
		data->adc_last_updated[ch_num] = jअगरfies;
		result = पढ़ोing;

		अगर (पढ़ोing > data->adc_maxes[ch_num])
			data->adc_maxes[ch_num] = पढ़ोing;
	पूर्ण अन्यथा अणु
		result = data->adc_values[ch_num];
	पूर्ण

निकास:
	mutex_unlock(&data->update_lock);

	वापस result;
पूर्ण

/* Shows the voltage associated with the specअगरied ADC channel */
अटल sमाप_प्रकार घातr1220_voltage_show(काष्ठा device *dev,
				     काष्ठा device_attribute *dev_attr,
				     अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(dev_attr);
	पूर्णांक adc_val = घातr1220_पढ़ो_adc(dev, attr->index);

	अगर (adc_val < 0)
		वापस adc_val;

	वापस प्र_लिखो(buf, "%d\n", adc_val);
पूर्ण

/* Shows the maximum setting associated with the specअगरied ADC channel */
अटल sमाप_प्रकार घातr1220_max_show(काष्ठा device *dev,
				 काष्ठा device_attribute *dev_attr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(dev_attr);
	काष्ठा घातr1220_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%d\n", data->adc_maxes[attr->index]);
पूर्ण

/* Shows the label associated with the specअगरied ADC channel */
अटल sमाप_प्रकार घातr1220_label_show(काष्ठा device *dev,
				   काष्ठा device_attribute *dev_attr,
				   अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(dev_attr);

	वापस प्र_लिखो(buf, "%s\n", input_names[attr->index]);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(in0_input, घातr1220_voltage, VMON1);
अटल SENSOR_DEVICE_ATTR_RO(in1_input, घातr1220_voltage, VMON2);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, घातr1220_voltage, VMON3);
अटल SENSOR_DEVICE_ATTR_RO(in3_input, घातr1220_voltage, VMON4);
अटल SENSOR_DEVICE_ATTR_RO(in4_input, घातr1220_voltage, VMON5);
अटल SENSOR_DEVICE_ATTR_RO(in5_input, घातr1220_voltage, VMON6);
अटल SENSOR_DEVICE_ATTR_RO(in6_input, घातr1220_voltage, VMON7);
अटल SENSOR_DEVICE_ATTR_RO(in7_input, घातr1220_voltage, VMON8);
अटल SENSOR_DEVICE_ATTR_RO(in8_input, घातr1220_voltage, VMON9);
अटल SENSOR_DEVICE_ATTR_RO(in9_input, घातr1220_voltage, VMON10);
अटल SENSOR_DEVICE_ATTR_RO(in10_input, घातr1220_voltage, VMON11);
अटल SENSOR_DEVICE_ATTR_RO(in11_input, घातr1220_voltage, VMON12);
अटल SENSOR_DEVICE_ATTR_RO(in12_input, घातr1220_voltage, VCCA);
अटल SENSOR_DEVICE_ATTR_RO(in13_input, घातr1220_voltage, VCCINP);

अटल SENSOR_DEVICE_ATTR_RO(in0_highest, घातr1220_max, VMON1);
अटल SENSOR_DEVICE_ATTR_RO(in1_highest, घातr1220_max, VMON2);
अटल SENSOR_DEVICE_ATTR_RO(in2_highest, घातr1220_max, VMON3);
अटल SENSOR_DEVICE_ATTR_RO(in3_highest, घातr1220_max, VMON4);
अटल SENSOR_DEVICE_ATTR_RO(in4_highest, घातr1220_max, VMON5);
अटल SENSOR_DEVICE_ATTR_RO(in5_highest, घातr1220_max, VMON6);
अटल SENSOR_DEVICE_ATTR_RO(in6_highest, घातr1220_max, VMON7);
अटल SENSOR_DEVICE_ATTR_RO(in7_highest, घातr1220_max, VMON8);
अटल SENSOR_DEVICE_ATTR_RO(in8_highest, घातr1220_max, VMON9);
अटल SENSOR_DEVICE_ATTR_RO(in9_highest, घातr1220_max, VMON10);
अटल SENSOR_DEVICE_ATTR_RO(in10_highest, घातr1220_max, VMON11);
अटल SENSOR_DEVICE_ATTR_RO(in11_highest, घातr1220_max, VMON12);
अटल SENSOR_DEVICE_ATTR_RO(in12_highest, घातr1220_max, VCCA);
अटल SENSOR_DEVICE_ATTR_RO(in13_highest, घातr1220_max, VCCINP);

अटल SENSOR_DEVICE_ATTR_RO(in0_label, घातr1220_label, VMON1);
अटल SENSOR_DEVICE_ATTR_RO(in1_label, घातr1220_label, VMON2);
अटल SENSOR_DEVICE_ATTR_RO(in2_label, घातr1220_label, VMON3);
अटल SENSOR_DEVICE_ATTR_RO(in3_label, घातr1220_label, VMON4);
अटल SENSOR_DEVICE_ATTR_RO(in4_label, घातr1220_label, VMON5);
अटल SENSOR_DEVICE_ATTR_RO(in5_label, घातr1220_label, VMON6);
अटल SENSOR_DEVICE_ATTR_RO(in6_label, घातr1220_label, VMON7);
अटल SENSOR_DEVICE_ATTR_RO(in7_label, घातr1220_label, VMON8);
अटल SENSOR_DEVICE_ATTR_RO(in8_label, घातr1220_label, VMON9);
अटल SENSOR_DEVICE_ATTR_RO(in9_label, घातr1220_label, VMON10);
अटल SENSOR_DEVICE_ATTR_RO(in10_label, घातr1220_label, VMON11);
अटल SENSOR_DEVICE_ATTR_RO(in11_label, घातr1220_label, VMON12);
अटल SENSOR_DEVICE_ATTR_RO(in12_label, घातr1220_label, VCCA);
अटल SENSOR_DEVICE_ATTR_RO(in13_label, घातr1220_label, VCCINP);

अटल काष्ठा attribute *घातr1220_attrs[] = अणु
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_in7_input.dev_attr.attr,
	&sensor_dev_attr_in8_input.dev_attr.attr,
	&sensor_dev_attr_in9_input.dev_attr.attr,
	&sensor_dev_attr_in10_input.dev_attr.attr,
	&sensor_dev_attr_in11_input.dev_attr.attr,
	&sensor_dev_attr_in12_input.dev_attr.attr,
	&sensor_dev_attr_in13_input.dev_attr.attr,

	&sensor_dev_attr_in0_highest.dev_attr.attr,
	&sensor_dev_attr_in1_highest.dev_attr.attr,
	&sensor_dev_attr_in2_highest.dev_attr.attr,
	&sensor_dev_attr_in3_highest.dev_attr.attr,
	&sensor_dev_attr_in4_highest.dev_attr.attr,
	&sensor_dev_attr_in5_highest.dev_attr.attr,
	&sensor_dev_attr_in6_highest.dev_attr.attr,
	&sensor_dev_attr_in7_highest.dev_attr.attr,
	&sensor_dev_attr_in8_highest.dev_attr.attr,
	&sensor_dev_attr_in9_highest.dev_attr.attr,
	&sensor_dev_attr_in10_highest.dev_attr.attr,
	&sensor_dev_attr_in11_highest.dev_attr.attr,
	&sensor_dev_attr_in12_highest.dev_attr.attr,
	&sensor_dev_attr_in13_highest.dev_attr.attr,

	&sensor_dev_attr_in0_label.dev_attr.attr,
	&sensor_dev_attr_in1_label.dev_attr.attr,
	&sensor_dev_attr_in2_label.dev_attr.attr,
	&sensor_dev_attr_in3_label.dev_attr.attr,
	&sensor_dev_attr_in4_label.dev_attr.attr,
	&sensor_dev_attr_in5_label.dev_attr.attr,
	&sensor_dev_attr_in6_label.dev_attr.attr,
	&sensor_dev_attr_in7_label.dev_attr.attr,
	&sensor_dev_attr_in8_label.dev_attr.attr,
	&sensor_dev_attr_in9_label.dev_attr.attr,
	&sensor_dev_attr_in10_label.dev_attr.attr,
	&sensor_dev_attr_in11_label.dev_attr.attr,
	&sensor_dev_attr_in12_label.dev_attr.attr,
	&sensor_dev_attr_in13_label.dev_attr.attr,

	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(घातr1220);

अटल पूर्णांक घातr1220_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा घातr1220_data *data;
	काष्ठा device *hwmon_dev;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	data = devm_kzalloc(&client->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	mutex_init(&data->update_lock);
	data->client = client;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&client->dev,
			client->name, data, घातr1220_groups);

	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id घातr1220_ids[] = अणु
	अणु "powr1220", 0, पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, घातr1220_ids);

अटल काष्ठा i2c_driver घातr1220_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "powr1220",
	पूर्ण,
	.probe_new	= घातr1220_probe,
	.id_table	= घातr1220_ids,
पूर्ण;

module_i2c_driver(घातr1220_driver);

MODULE_AUTHOR("Scott Kanowitz");
MODULE_DESCRIPTION("POWR1220 driver");
MODULE_LICENSE("GPL");
