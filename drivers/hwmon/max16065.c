<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम
 *  Maxim MAX16065/MAX16066 12-Channel/8-Channel, Flash-Configurable
 *  System Managers with Nonअस्थिर Fault Registers
 *  Maxim MAX16067/MAX16068 6-Channel, Flash-Configurable System Managers
 *  with Nonअस्थिर Fault Registers
 *  Maxim MAX16070/MAX16071 12-Channel/8-Channel, Flash-Configurable System
 *  Monitors with Nonअस्थिर Fault Registers
 *
 * Copyright (C) 2011 Ericsson AB.
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

क्रमागत chips अणु max16065, max16066, max16067, max16068, max16070, max16071 पूर्ण;

/*
 * Registers
 */
#घोषणा MAX16065_ADC(x)		((x) * 2)

#घोषणा MAX16065_CURR_SENSE	0x18
#घोषणा MAX16065_CSP_ADC	0x19
#घोषणा MAX16065_FAULT(x)	(0x1b + (x))
#घोषणा MAX16065_SCALE(x)	(0x43 + (x))
#घोषणा MAX16065_CURR_CONTROL	0x47
#घोषणा MAX16065_LIMIT(l, x)	(0x48 + (l) + (x) * 3)	/*
							 * l: limit
							 *  0: min/max
							 *  1: crit
							 *  2: lcrit
							 * x: ADC index
							 */

#घोषणा MAX16065_SW_ENABLE	0x73

#घोषणा MAX16065_WARNING_OV	(1 << 3) /* Set अगर secondary threshold is OV
					    warning */

#घोषणा MAX16065_CURR_ENABLE	(1 << 0)

#घोषणा MAX16065_NUM_LIMIT	3
#घोषणा MAX16065_NUM_ADC	12	/* maximum number of ADC channels */

अटल स्थिर पूर्णांक max16065_num_adc[] = अणु
	[max16065] = 12,
	[max16066] = 8,
	[max16067] = 6,
	[max16068] = 6,
	[max16070] = 12,
	[max16071] = 8,
पूर्ण;

अटल स्थिर bool max16065_have_secondary[] = अणु
	[max16065] = true,
	[max16066] = true,
	[max16067] = false,
	[max16068] = false,
	[max16070] = true,
	[max16071] = true,
पूर्ण;

अटल स्थिर bool max16065_have_current[] = अणु
	[max16065] = true,
	[max16066] = true,
	[max16067] = false,
	[max16068] = false,
	[max16070] = true,
	[max16071] = true,
पूर्ण;

काष्ठा max16065_data अणु
	क्रमागत chips type;
	काष्ठा i2c_client *client;
	स्थिर काष्ठा attribute_group *groups[4];
	काष्ठा mutex update_lock;
	bool valid;
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */
	पूर्णांक num_adc;
	bool have_current;
	पूर्णांक curr_gain;
	/* limits are in mV */
	पूर्णांक limit[MAX16065_NUM_LIMIT][MAX16065_NUM_ADC];
	पूर्णांक range[MAX16065_NUM_ADC + 1];/* voltage range */
	पूर्णांक adc[MAX16065_NUM_ADC + 1];	/* adc values (raw) including csp_adc */
	पूर्णांक curr_sense;
	पूर्णांक fault[2];
पूर्ण;

अटल स्थिर पूर्णांक max16065_adc_range[] = अणु 5560, 2780, 1390, 0 पूर्ण;
अटल स्थिर पूर्णांक max16065_csp_adc_range[] = अणु 7000, 14000 पूर्ण;

/* ADC रेजिस्टरs have 10 bit resolution. */
अटल अंतरभूत पूर्णांक ADC_TO_MV(पूर्णांक adc, पूर्णांक range)
अणु
	वापस (adc * range) / 1024;
पूर्ण

/*
 * Limit रेजिस्टरs have 8 bit resolution and match upper 8 bits of ADC
 * रेजिस्टरs.
 */
अटल अंतरभूत पूर्णांक LIMIT_TO_MV(पूर्णांक limit, पूर्णांक range)
अणु
	वापस limit * range / 256;
पूर्ण

अटल अंतरभूत पूर्णांक MV_TO_LIMIT(पूर्णांक mv, पूर्णांक range)
अणु
	वापस clamp_val(DIV_ROUND_CLOSEST(mv * 256, range), 0, 255);
पूर्ण

अटल अंतरभूत पूर्णांक ADC_TO_CURR(पूर्णांक adc, पूर्णांक gain)
अणु
	वापस adc * 1400000 / (gain * 255);
पूर्ण

/*
 * max16065_पढ़ो_adc()
 *
 * Read 16 bit value from <reg>, <reg+1>.
 * Upper 8 bits are in <reg>, lower 2 bits are in bits 7:6 of <reg+1>.
 */
अटल पूर्णांक max16065_पढ़ो_adc(काष्ठा i2c_client *client, पूर्णांक reg)
अणु
	पूर्णांक rv;

	rv = i2c_smbus_पढ़ो_word_swapped(client, reg);
	अगर (unlikely(rv < 0))
		वापस rv;
	वापस rv >> 6;
पूर्ण

अटल काष्ठा max16065_data *max16065_update_device(काष्ठा device *dev)
अणु
	काष्ठा max16065_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;

	mutex_lock(&data->update_lock);
	अगर (समय_after(jअगरfies, data->last_updated + HZ) || !data->valid) अणु
		पूर्णांक i;

		क्रम (i = 0; i < data->num_adc; i++)
			data->adc[i]
			  = max16065_पढ़ो_adc(client, MAX16065_ADC(i));

		अगर (data->have_current) अणु
			data->adc[MAX16065_NUM_ADC]
			  = max16065_पढ़ो_adc(client, MAX16065_CSP_ADC);
			data->curr_sense
			  = i2c_smbus_पढ़ो_byte_data(client,
						     MAX16065_CURR_SENSE);
		पूर्ण

		क्रम (i = 0; i < DIV_ROUND_UP(data->num_adc, 8); i++)
			data->fault[i]
			  = i2c_smbus_पढ़ो_byte_data(client, MAX16065_FAULT(i));

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण
	mutex_unlock(&data->update_lock);
	वापस data;
पूर्ण

अटल sमाप_प्रकार max16065_alarm_show(काष्ठा device *dev,
				   काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *attr2 = to_sensor_dev_attr_2(da);
	काष्ठा max16065_data *data = max16065_update_device(dev);
	पूर्णांक val = data->fault[attr2->nr];

	अगर (val < 0)
		वापस val;

	val &= (1 << attr2->index);
	अगर (val)
		i2c_smbus_ग_लिखो_byte_data(data->client,
					  MAX16065_FAULT(attr2->nr), val);

	वापस sysfs_emit(buf, "%d\n", !!val);
पूर्ण

अटल sमाप_प्रकार max16065_input_show(काष्ठा device *dev,
				   काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा max16065_data *data = max16065_update_device(dev);
	पूर्णांक adc = data->adc[attr->index];

	अगर (unlikely(adc < 0))
		वापस adc;

	वापस sysfs_emit(buf, "%d\n",
			  ADC_TO_MV(adc, data->range[attr->index]));
पूर्ण

अटल sमाप_प्रकार max16065_current_show(काष्ठा device *dev,
				     काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा max16065_data *data = max16065_update_device(dev);

	अगर (unlikely(data->curr_sense < 0))
		वापस data->curr_sense;

	वापस sysfs_emit(buf, "%d\n",
			  ADC_TO_CURR(data->curr_sense, data->curr_gain));
पूर्ण

अटल sमाप_प्रकार max16065_limit_store(काष्ठा device *dev,
				    काष्ठा device_attribute *da,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute_2 *attr2 = to_sensor_dev_attr_2(da);
	काष्ठा max16065_data *data = dev_get_drvdata(dev);
	अचिन्हित दीर्घ val;
	पूर्णांक err;
	पूर्णांक limit;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (unlikely(err < 0))
		वापस err;

	limit = MV_TO_LIMIT(val, data->range[attr2->index]);

	mutex_lock(&data->update_lock);
	data->limit[attr2->nr][attr2->index]
	  = LIMIT_TO_MV(limit, data->range[attr2->index]);
	i2c_smbus_ग_लिखो_byte_data(data->client,
				  MAX16065_LIMIT(attr2->nr, attr2->index),
				  limit);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल sमाप_प्रकार max16065_limit_show(काष्ठा device *dev,
				   काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute_2 *attr2 = to_sensor_dev_attr_2(da);
	काष्ठा max16065_data *data = dev_get_drvdata(dev);

	वापस sysfs_emit(buf, "%d\n",
			  data->limit[attr2->nr][attr2->index]);
पूर्ण

/* Conकाष्ठा a sensor_device_attribute काष्ठाure क्रम each रेजिस्टर */

/* Input voltages */
अटल SENSOR_DEVICE_ATTR_RO(in0_input, max16065_input, 0);
अटल SENSOR_DEVICE_ATTR_RO(in1_input, max16065_input, 1);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, max16065_input, 2);
अटल SENSOR_DEVICE_ATTR_RO(in3_input, max16065_input, 3);
अटल SENSOR_DEVICE_ATTR_RO(in4_input, max16065_input, 4);
अटल SENSOR_DEVICE_ATTR_RO(in5_input, max16065_input, 5);
अटल SENSOR_DEVICE_ATTR_RO(in6_input, max16065_input, 6);
अटल SENSOR_DEVICE_ATTR_RO(in7_input, max16065_input, 7);
अटल SENSOR_DEVICE_ATTR_RO(in8_input, max16065_input, 8);
अटल SENSOR_DEVICE_ATTR_RO(in9_input, max16065_input, 9);
अटल SENSOR_DEVICE_ATTR_RO(in10_input, max16065_input, 10);
अटल SENSOR_DEVICE_ATTR_RO(in11_input, max16065_input, 11);
अटल SENSOR_DEVICE_ATTR_RO(in12_input, max16065_input, 12);

/* Input voltages lcrit */
अटल SENSOR_DEVICE_ATTR_2_RW(in0_lcrit, max16065_limit, 2, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(in1_lcrit, max16065_limit, 2, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(in2_lcrit, max16065_limit, 2, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(in3_lcrit, max16065_limit, 2, 3);
अटल SENSOR_DEVICE_ATTR_2_RW(in4_lcrit, max16065_limit, 2, 4);
अटल SENSOR_DEVICE_ATTR_2_RW(in5_lcrit, max16065_limit, 2, 5);
अटल SENSOR_DEVICE_ATTR_2_RW(in6_lcrit, max16065_limit, 2, 6);
अटल SENSOR_DEVICE_ATTR_2_RW(in7_lcrit, max16065_limit, 2, 7);
अटल SENSOR_DEVICE_ATTR_2_RW(in8_lcrit, max16065_limit, 2, 8);
अटल SENSOR_DEVICE_ATTR_2_RW(in9_lcrit, max16065_limit, 2, 9);
अटल SENSOR_DEVICE_ATTR_2_RW(in10_lcrit, max16065_limit, 2, 10);
अटल SENSOR_DEVICE_ATTR_2_RW(in11_lcrit, max16065_limit, 2, 11);

/* Input voltages crit */
अटल SENSOR_DEVICE_ATTR_2_RW(in0_crit, max16065_limit, 1, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(in1_crit, max16065_limit, 1, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(in2_crit, max16065_limit, 1, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(in3_crit, max16065_limit, 1, 3);
अटल SENSOR_DEVICE_ATTR_2_RW(in4_crit, max16065_limit, 1, 4);
अटल SENSOR_DEVICE_ATTR_2_RW(in5_crit, max16065_limit, 1, 5);
अटल SENSOR_DEVICE_ATTR_2_RW(in6_crit, max16065_limit, 1, 6);
अटल SENSOR_DEVICE_ATTR_2_RW(in7_crit, max16065_limit, 1, 7);
अटल SENSOR_DEVICE_ATTR_2_RW(in8_crit, max16065_limit, 1, 8);
अटल SENSOR_DEVICE_ATTR_2_RW(in9_crit, max16065_limit, 1, 9);
अटल SENSOR_DEVICE_ATTR_2_RW(in10_crit, max16065_limit, 1, 10);
अटल SENSOR_DEVICE_ATTR_2_RW(in11_crit, max16065_limit, 1, 11);

/* Input voltages min */
अटल SENSOR_DEVICE_ATTR_2_RW(in0_min, max16065_limit, 0, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(in1_min, max16065_limit, 0, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(in2_min, max16065_limit, 0, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(in3_min, max16065_limit, 0, 3);
अटल SENSOR_DEVICE_ATTR_2_RW(in4_min, max16065_limit, 0, 4);
अटल SENSOR_DEVICE_ATTR_2_RW(in5_min, max16065_limit, 0, 5);
अटल SENSOR_DEVICE_ATTR_2_RW(in6_min, max16065_limit, 0, 6);
अटल SENSOR_DEVICE_ATTR_2_RW(in7_min, max16065_limit, 0, 7);
अटल SENSOR_DEVICE_ATTR_2_RW(in8_min, max16065_limit, 0, 8);
अटल SENSOR_DEVICE_ATTR_2_RW(in9_min, max16065_limit, 0, 9);
अटल SENSOR_DEVICE_ATTR_2_RW(in10_min, max16065_limit, 0, 10);
अटल SENSOR_DEVICE_ATTR_2_RW(in11_min, max16065_limit, 0, 11);

/* Input voltages max */
अटल SENSOR_DEVICE_ATTR_2_RW(in0_max, max16065_limit, 0, 0);
अटल SENSOR_DEVICE_ATTR_2_RW(in1_max, max16065_limit, 0, 1);
अटल SENSOR_DEVICE_ATTR_2_RW(in2_max, max16065_limit, 0, 2);
अटल SENSOR_DEVICE_ATTR_2_RW(in3_max, max16065_limit, 0, 3);
अटल SENSOR_DEVICE_ATTR_2_RW(in4_max, max16065_limit, 0, 4);
अटल SENSOR_DEVICE_ATTR_2_RW(in5_max, max16065_limit, 0, 5);
अटल SENSOR_DEVICE_ATTR_2_RW(in6_max, max16065_limit, 0, 6);
अटल SENSOR_DEVICE_ATTR_2_RW(in7_max, max16065_limit, 0, 7);
अटल SENSOR_DEVICE_ATTR_2_RW(in8_max, max16065_limit, 0, 8);
अटल SENSOR_DEVICE_ATTR_2_RW(in9_max, max16065_limit, 0, 9);
अटल SENSOR_DEVICE_ATTR_2_RW(in10_max, max16065_limit, 0, 10);
अटल SENSOR_DEVICE_ATTR_2_RW(in11_max, max16065_limit, 0, 11);

/* alarms */
अटल SENSOR_DEVICE_ATTR_2_RO(in0_alarm, max16065_alarm, 0, 0);
अटल SENSOR_DEVICE_ATTR_2_RO(in1_alarm, max16065_alarm, 0, 1);
अटल SENSOR_DEVICE_ATTR_2_RO(in2_alarm, max16065_alarm, 0, 2);
अटल SENSOR_DEVICE_ATTR_2_RO(in3_alarm, max16065_alarm, 0, 3);
अटल SENSOR_DEVICE_ATTR_2_RO(in4_alarm, max16065_alarm, 0, 4);
अटल SENSOR_DEVICE_ATTR_2_RO(in5_alarm, max16065_alarm, 0, 5);
अटल SENSOR_DEVICE_ATTR_2_RO(in6_alarm, max16065_alarm, 0, 6);
अटल SENSOR_DEVICE_ATTR_2_RO(in7_alarm, max16065_alarm, 0, 7);
अटल SENSOR_DEVICE_ATTR_2_RO(in8_alarm, max16065_alarm, 1, 0);
अटल SENSOR_DEVICE_ATTR_2_RO(in9_alarm, max16065_alarm, 1, 1);
अटल SENSOR_DEVICE_ATTR_2_RO(in10_alarm, max16065_alarm, 1, 2);
अटल SENSOR_DEVICE_ATTR_2_RO(in11_alarm, max16065_alarm, 1, 3);

/* Current and alarm */
अटल SENSOR_DEVICE_ATTR_RO(curr1_input, max16065_current, 0);
अटल SENSOR_DEVICE_ATTR_2_RO(curr1_alarm, max16065_alarm, 1, 4);

/*
 * Finally, स्थिरruct an array of poपूर्णांकers to members of the above objects,
 * as required क्रम sysfs_create_group()
 */
अटल काष्ठा attribute *max16065_basic_attributes[] = अणु
	&sensor_dev_attr_in0_input.dev_attr.attr,
	&sensor_dev_attr_in0_lcrit.dev_attr.attr,
	&sensor_dev_attr_in0_crit.dev_attr.attr,
	&sensor_dev_attr_in0_alarm.dev_attr.attr,

	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in1_lcrit.dev_attr.attr,
	&sensor_dev_attr_in1_crit.dev_attr.attr,
	&sensor_dev_attr_in1_alarm.dev_attr.attr,

	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in2_lcrit.dev_attr.attr,
	&sensor_dev_attr_in2_crit.dev_attr.attr,
	&sensor_dev_attr_in2_alarm.dev_attr.attr,

	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in3_lcrit.dev_attr.attr,
	&sensor_dev_attr_in3_crit.dev_attr.attr,
	&sensor_dev_attr_in3_alarm.dev_attr.attr,

	&sensor_dev_attr_in4_input.dev_attr.attr,
	&sensor_dev_attr_in4_lcrit.dev_attr.attr,
	&sensor_dev_attr_in4_crit.dev_attr.attr,
	&sensor_dev_attr_in4_alarm.dev_attr.attr,

	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in5_lcrit.dev_attr.attr,
	&sensor_dev_attr_in5_crit.dev_attr.attr,
	&sensor_dev_attr_in5_alarm.dev_attr.attr,

	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_in6_lcrit.dev_attr.attr,
	&sensor_dev_attr_in6_crit.dev_attr.attr,
	&sensor_dev_attr_in6_alarm.dev_attr.attr,

	&sensor_dev_attr_in7_input.dev_attr.attr,
	&sensor_dev_attr_in7_lcrit.dev_attr.attr,
	&sensor_dev_attr_in7_crit.dev_attr.attr,
	&sensor_dev_attr_in7_alarm.dev_attr.attr,

	&sensor_dev_attr_in8_input.dev_attr.attr,
	&sensor_dev_attr_in8_lcrit.dev_attr.attr,
	&sensor_dev_attr_in8_crit.dev_attr.attr,
	&sensor_dev_attr_in8_alarm.dev_attr.attr,

	&sensor_dev_attr_in9_input.dev_attr.attr,
	&sensor_dev_attr_in9_lcrit.dev_attr.attr,
	&sensor_dev_attr_in9_crit.dev_attr.attr,
	&sensor_dev_attr_in9_alarm.dev_attr.attr,

	&sensor_dev_attr_in10_input.dev_attr.attr,
	&sensor_dev_attr_in10_lcrit.dev_attr.attr,
	&sensor_dev_attr_in10_crit.dev_attr.attr,
	&sensor_dev_attr_in10_alarm.dev_attr.attr,

	&sensor_dev_attr_in11_input.dev_attr.attr,
	&sensor_dev_attr_in11_lcrit.dev_attr.attr,
	&sensor_dev_attr_in11_crit.dev_attr.attr,
	&sensor_dev_attr_in11_alarm.dev_attr.attr,

	शून्य
पूर्ण;

अटल काष्ठा attribute *max16065_current_attributes[] = अणु
	&sensor_dev_attr_in12_input.dev_attr.attr,
	&sensor_dev_attr_curr1_input.dev_attr.attr,
	&sensor_dev_attr_curr1_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *max16065_min_attributes[] = अणु
	&sensor_dev_attr_in0_min.dev_attr.attr,
	&sensor_dev_attr_in1_min.dev_attr.attr,
	&sensor_dev_attr_in2_min.dev_attr.attr,
	&sensor_dev_attr_in3_min.dev_attr.attr,
	&sensor_dev_attr_in4_min.dev_attr.attr,
	&sensor_dev_attr_in5_min.dev_attr.attr,
	&sensor_dev_attr_in6_min.dev_attr.attr,
	&sensor_dev_attr_in7_min.dev_attr.attr,
	&sensor_dev_attr_in8_min.dev_attr.attr,
	&sensor_dev_attr_in9_min.dev_attr.attr,
	&sensor_dev_attr_in10_min.dev_attr.attr,
	&sensor_dev_attr_in11_min.dev_attr.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *max16065_max_attributes[] = अणु
	&sensor_dev_attr_in0_max.dev_attr.attr,
	&sensor_dev_attr_in1_max.dev_attr.attr,
	&sensor_dev_attr_in2_max.dev_attr.attr,
	&sensor_dev_attr_in3_max.dev_attr.attr,
	&sensor_dev_attr_in4_max.dev_attr.attr,
	&sensor_dev_attr_in5_max.dev_attr.attr,
	&sensor_dev_attr_in6_max.dev_attr.attr,
	&sensor_dev_attr_in7_max.dev_attr.attr,
	&sensor_dev_attr_in8_max.dev_attr.attr,
	&sensor_dev_attr_in9_max.dev_attr.attr,
	&sensor_dev_attr_in10_max.dev_attr.attr,
	&sensor_dev_attr_in11_max.dev_attr.attr,
	शून्य
पूर्ण;

अटल umode_t max16065_basic_is_visible(काष्ठा kobject *kobj,
					 काष्ठा attribute *a, पूर्णांक n)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा max16065_data *data = dev_get_drvdata(dev);
	पूर्णांक index = n / 4;

	अगर (index >= data->num_adc || !data->range[index])
		वापस 0;
	वापस a->mode;
पूर्ण

अटल umode_t max16065_secondary_is_visible(काष्ठा kobject *kobj,
					     काष्ठा attribute *a, पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा max16065_data *data = dev_get_drvdata(dev);

	अगर (index >= data->num_adc)
		वापस 0;
	वापस a->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group max16065_basic_group = अणु
	.attrs = max16065_basic_attributes,
	.is_visible = max16065_basic_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group max16065_current_group = अणु
	.attrs = max16065_current_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group max16065_min_group = अणु
	.attrs = max16065_min_attributes,
	.is_visible = max16065_secondary_is_visible,
पूर्ण;

अटल स्थिर काष्ठा attribute_group max16065_max_group = अणु
	.attrs = max16065_max_attributes,
	.is_visible = max16065_secondary_is_visible,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id max16065_id[];

अटल पूर्णांक max16065_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा max16065_data *data;
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	पूर्णांक i, j, val;
	bool have_secondary;		/* true अगर chip has secondary limits */
	bool secondary_is_max = false;	/* secondary limits reflect max */
	पूर्णांक groups = 0;
	स्थिर काष्ठा i2c_device_id *id = i2c_match_id(max16065_id, client);

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA
				     | I2C_FUNC_SMBUS_READ_WORD_DATA))
		वापस -ENODEV;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (unlikely(!data))
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	data->num_adc = max16065_num_adc[id->driver_data];
	data->have_current = max16065_have_current[id->driver_data];
	have_secondary = max16065_have_secondary[id->driver_data];

	अगर (have_secondary) अणु
		val = i2c_smbus_पढ़ो_byte_data(client, MAX16065_SW_ENABLE);
		अगर (unlikely(val < 0))
			वापस val;
		secondary_is_max = val & MAX16065_WARNING_OV;
	पूर्ण

	/* Read scale रेजिस्टरs, convert to range */
	क्रम (i = 0; i < DIV_ROUND_UP(data->num_adc, 4); i++) अणु
		val = i2c_smbus_पढ़ो_byte_data(client, MAX16065_SCALE(i));
		अगर (unlikely(val < 0))
			वापस val;
		क्रम (j = 0; j < 4 && i * 4 + j < data->num_adc; j++) अणु
			data->range[i * 4 + j] =
			  max16065_adc_range[(val >> (j * 2)) & 0x3];
		पूर्ण
	पूर्ण

	/* Read limits */
	क्रम (i = 0; i < MAX16065_NUM_LIMIT; i++) अणु
		अगर (i == 0 && !have_secondary)
			जारी;

		क्रम (j = 0; j < data->num_adc; j++) अणु
			val = i2c_smbus_पढ़ो_byte_data(client,
						       MAX16065_LIMIT(i, j));
			अगर (unlikely(val < 0))
				वापस val;
			data->limit[i][j] = LIMIT_TO_MV(val, data->range[j]);
		पूर्ण
	पूर्ण

	/* sysfs hooks */
	data->groups[groups++] = &max16065_basic_group;
	अगर (have_secondary)
		data->groups[groups++] = secondary_is_max ?
			&max16065_max_group : &max16065_min_group;

	अगर (data->have_current) अणु
		val = i2c_smbus_पढ़ो_byte_data(client, MAX16065_CURR_CONTROL);
		अगर (unlikely(val < 0))
			वापस val;
		अगर (val & MAX16065_CURR_ENABLE) अणु
			/*
			 * Current gain is 6, 12, 24, 48 based on values in
			 * bit 2,3.
			 */
			data->curr_gain = 6 << ((val >> 2) & 0x03);
			data->range[MAX16065_NUM_ADC]
			  = max16065_csp_adc_range[(val >> 1) & 0x01];
			data->groups[groups++] = &max16065_current_group;
		पूर्ण अन्यथा अणु
			data->have_current = false;
		पूर्ण
	पूर्ण

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data, data->groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max16065_id[] = अणु
	अणु "max16065", max16065 पूर्ण,
	अणु "max16066", max16066 पूर्ण,
	अणु "max16067", max16067 पूर्ण,
	अणु "max16068", max16068 पूर्ण,
	अणु "max16070", max16070 पूर्ण,
	अणु "max16071", max16071 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, max16065_id);

/* This is the driver that will be inserted */
अटल काष्ठा i2c_driver max16065_driver = अणु
	.driver = अणु
		.name = "max16065",
	पूर्ण,
	.probe_new = max16065_probe,
	.id_table = max16065_id,
पूर्ण;

module_i2c_driver(max16065_driver);

MODULE_AUTHOR("Guenter Roeck <linux@roeck-us.net>");
MODULE_DESCRIPTION("MAX16065 driver");
MODULE_LICENSE("GPL");
