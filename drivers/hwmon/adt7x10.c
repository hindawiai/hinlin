<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * adt7x10.c - Part of lm_sensors, Linux kernel modules क्रम hardware
 *	 monitoring
 * This driver handles the ADT7410 and compatible digital temperature sensors.
 * Harपंचांगut Knaack <knaack.h@gmx.de> 2012-07-22
 * based on lm75.c by Froकरो Looijaard <froकरोl@dds.nl>
 * and adt7410.c from iio-staging by Sonic Zhang <sonic.zhang@analog.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "adt7x10.h"

/*
 * ADT7X10 status
 */
#घोषणा ADT7X10_STAT_T_LOW		(1 << 4)
#घोषणा ADT7X10_STAT_T_HIGH		(1 << 5)
#घोषणा ADT7X10_STAT_T_CRIT		(1 << 6)
#घोषणा ADT7X10_STAT_NOT_RDY		(1 << 7)

/*
 * ADT7X10 config
 */
#घोषणा ADT7X10_FAULT_QUEUE_MASK	(1 << 0 | 1 << 1)
#घोषणा ADT7X10_CT_POLARITY		(1 << 2)
#घोषणा ADT7X10_INT_POLARITY		(1 << 3)
#घोषणा ADT7X10_EVENT_MODE		(1 << 4)
#घोषणा ADT7X10_MODE_MASK		(1 << 5 | 1 << 6)
#घोषणा ADT7X10_FULL			(0 << 5 | 0 << 6)
#घोषणा ADT7X10_PD			(1 << 5 | 1 << 6)
#घोषणा ADT7X10_RESOLUTION		(1 << 7)

/*
 * ADT7X10 masks
 */
#घोषणा ADT7X10_T13_VALUE_MASK		0xFFF8
#घोषणा ADT7X10_T_HYST_MASK		0xF

/* straight from the datasheet */
#घोषणा ADT7X10_TEMP_MIN (-55000)
#घोषणा ADT7X10_TEMP_MAX 150000

/* Each client has this additional data */
काष्ठा adt7x10_data अणु
	स्थिर काष्ठा adt7x10_ops *ops;
	स्थिर अक्षर		*name;
	काष्ठा device		*hwmon_dev;
	काष्ठा mutex		update_lock;
	u8			config;
	u8			oldconfig;
	bool			valid;		/* true अगर रेजिस्टरs valid */
	अचिन्हित दीर्घ		last_updated;	/* In jअगरfies */
	s16			temp[4];	/* Register values,
						   0 = input
						   1 = high
						   2 = low
						   3 = critical */
	u8			hyst;		/* hysteresis offset */
पूर्ण;

अटल पूर्णांक adt7x10_पढ़ो_byte(काष्ठा device *dev, u8 reg)
अणु
	काष्ठा adt7x10_data *d = dev_get_drvdata(dev);
	वापस d->ops->पढ़ो_byte(dev, reg);
पूर्ण

अटल पूर्णांक adt7x10_ग_लिखो_byte(काष्ठा device *dev, u8 reg, u8 data)
अणु
	काष्ठा adt7x10_data *d = dev_get_drvdata(dev);
	वापस d->ops->ग_लिखो_byte(dev, reg, data);
पूर्ण

अटल पूर्णांक adt7x10_पढ़ो_word(काष्ठा device *dev, u8 reg)
अणु
	काष्ठा adt7x10_data *d = dev_get_drvdata(dev);
	वापस d->ops->पढ़ो_word(dev, reg);
पूर्ण

अटल पूर्णांक adt7x10_ग_लिखो_word(काष्ठा device *dev, u8 reg, u16 data)
अणु
	काष्ठा adt7x10_data *d = dev_get_drvdata(dev);
	वापस d->ops->ग_लिखो_word(dev, reg, data);
पूर्ण

अटल स्थिर u8 ADT7X10_REG_TEMP[4] = अणु
	ADT7X10_TEMPERATURE,		/* input */
	ADT7X10_T_ALARM_HIGH,		/* high */
	ADT7X10_T_ALARM_LOW,		/* low */
	ADT7X10_T_CRIT,			/* critical */
पूर्ण;

अटल irqवापस_t adt7x10_irq_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा device *dev = निजी;
	पूर्णांक status;

	status = adt7x10_पढ़ो_byte(dev, ADT7X10_STATUS);
	अगर (status < 0)
		वापस IRQ_HANDLED;

	अगर (status & ADT7X10_STAT_T_HIGH)
		sysfs_notअगरy(&dev->kobj, शून्य, "temp1_max_alarm");
	अगर (status & ADT7X10_STAT_T_LOW)
		sysfs_notअगरy(&dev->kobj, शून्य, "temp1_min_alarm");
	अगर (status & ADT7X10_STAT_T_CRIT)
		sysfs_notअगरy(&dev->kobj, शून्य, "temp1_crit_alarm");

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक adt7x10_temp_पढ़ोy(काष्ठा device *dev)
अणु
	पूर्णांक i, status;

	क्रम (i = 0; i < 6; i++) अणु
		status = adt7x10_पढ़ो_byte(dev, ADT7X10_STATUS);
		अगर (status < 0)
			वापस status;
		अगर (!(status & ADT7X10_STAT_NOT_RDY))
			वापस 0;
		msleep(60);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक adt7x10_update_temp(काष्ठा device *dev)
अणु
	काष्ठा adt7x10_data *data = dev_get_drvdata(dev);
	पूर्णांक ret = 0;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ + HZ / 2)
	    || !data->valid) अणु
		पूर्णांक temp;

		dev_dbg(dev, "Starting update\n");

		ret = adt7x10_temp_पढ़ोy(dev); /* check क्रम new value */
		अगर (ret)
			जाओ पात;

		temp = adt7x10_पढ़ो_word(dev, ADT7X10_REG_TEMP[0]);
		अगर (temp < 0) अणु
			ret = temp;
			dev_dbg(dev, "Failed to read value: reg %d, error %d\n",
				ADT7X10_REG_TEMP[0], ret);
			जाओ पात;
		पूर्ण
		data->temp[0] = temp;
		data->last_updated = jअगरfies;
		data->valid = true;
	पूर्ण

पात:
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक adt7x10_fill_cache(काष्ठा device *dev)
अणु
	काष्ठा adt7x10_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 1; i < ARRAY_SIZE(data->temp); i++) अणु
		ret = adt7x10_पढ़ो_word(dev, ADT7X10_REG_TEMP[i]);
		अगर (ret < 0) अणु
			dev_dbg(dev, "Failed to read value: reg %d, error %d\n",
				ADT7X10_REG_TEMP[i], ret);
			वापस ret;
		पूर्ण
		data->temp[i] = ret;
	पूर्ण

	ret = adt7x10_पढ़ो_byte(dev, ADT7X10_T_HYST);
	अगर (ret < 0) अणु
		dev_dbg(dev, "Failed to read value: reg %d, error %d\n",
				ADT7X10_T_HYST, ret);
		वापस ret;
	पूर्ण
	data->hyst = ret;

	वापस 0;
पूर्ण

अटल s16 ADT7X10_TEMP_TO_REG(दीर्घ temp)
अणु
	वापस DIV_ROUND_CLOSEST(clamp_val(temp, ADT7X10_TEMP_MIN,
					       ADT7X10_TEMP_MAX) * 128, 1000);
पूर्ण

अटल पूर्णांक ADT7X10_REG_TO_TEMP(काष्ठा adt7x10_data *data, s16 reg)
अणु
	/* in 13 bit mode, bits 0-2 are status flags - mask them out */
	अगर (!(data->config & ADT7X10_RESOLUTION))
		reg &= ADT7X10_T13_VALUE_MASK;
	/*
	 * temperature is stored in twos complement क्रमmat, in steps of
	 * 1/128तओC
	 */
	वापस DIV_ROUND_CLOSEST(reg * 1000, 128);
पूर्ण

/*-----------------------------------------------------------------------*/

/* sysfs attributes क्रम hwmon */

अटल sमाप_प्रकार adt7x10_temp_show(काष्ठा device *dev,
				 काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा adt7x10_data *data = dev_get_drvdata(dev);


	अगर (attr->index == 0) अणु
		पूर्णांक ret;

		ret = adt7x10_update_temp(dev);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस प्र_लिखो(buf, "%d\n", ADT7X10_REG_TO_TEMP(data,
		       data->temp[attr->index]));
पूर्ण

अटल sमाप_प्रकार adt7x10_temp_store(काष्ठा device *dev,
				  काष्ठा device_attribute *da,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा adt7x10_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = attr->index;
	दीर्घ temp;
	पूर्णांक ret;

	ret = kम_से_दीर्घ(buf, 10, &temp);
	अगर (ret)
		वापस ret;

	mutex_lock(&data->update_lock);
	data->temp[nr] = ADT7X10_TEMP_TO_REG(temp);
	ret = adt7x10_ग_लिखो_word(dev, ADT7X10_REG_TEMP[nr], data->temp[nr]);
	अगर (ret)
		count = ret;
	mutex_unlock(&data->update_lock);
	वापस count;
पूर्ण

अटल sमाप_प्रकार adt7x10_t_hyst_show(काष्ठा device *dev,
				   काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	काष्ठा adt7x10_data *data = dev_get_drvdata(dev);
	पूर्णांक nr = attr->index;
	पूर्णांक hyst;

	hyst = (data->hyst & ADT7X10_T_HYST_MASK) * 1000;

	/*
	 * hysteresis is stored as a 4 bit offset in the device, convert it
	 * to an असलolute value
	 */
	अगर (nr == 2)	/* min has positive offset, others have negative */
		hyst = -hyst;
	वापस प्र_लिखो(buf, "%d\n",
		       ADT7X10_REG_TO_TEMP(data, data->temp[nr]) - hyst);
पूर्ण

अटल sमाप_प्रकार adt7x10_t_hyst_store(काष्ठा device *dev,
				    काष्ठा device_attribute *da,
				    स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा adt7x10_data *data = dev_get_drvdata(dev);
	पूर्णांक limit, ret;
	दीर्घ hyst;

	ret = kम_से_दीर्घ(buf, 10, &hyst);
	अगर (ret)
		वापस ret;
	/* convert असलolute hysteresis value to a 4 bit delta value */
	limit = ADT7X10_REG_TO_TEMP(data, data->temp[1]);
	hyst = clamp_val(hyst, ADT7X10_TEMP_MIN, ADT7X10_TEMP_MAX);
	data->hyst = clamp_val(DIV_ROUND_CLOSEST(limit - hyst, 1000),
				   0, ADT7X10_T_HYST_MASK);
	ret = adt7x10_ग_लिखो_byte(dev, ADT7X10_T_HYST, data->hyst);
	अगर (ret)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार adt7x10_alarm_show(काष्ठा device *dev,
				  काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(da);
	पूर्णांक ret;

	ret = adt7x10_पढ़ो_byte(dev, ADT7X10_STATUS);
	अगर (ret < 0)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", !!(ret & attr->index));
पूर्ण

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			 अक्षर *buf)
अणु
	काष्ठा adt7x10_data *data = dev_get_drvdata(dev);

	वापस प्र_लिखो(buf, "%s\n", data->name);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, adt7x10_temp, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, adt7x10_temp, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp1_min, adt7x10_temp, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp1_crit, adt7x10_temp, 3);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max_hyst, adt7x10_t_hyst, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp1_min_hyst, adt7x10_t_hyst, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp1_crit_hyst, adt7x10_t_hyst, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp1_min_alarm, adt7x10_alarm,
			     ADT7X10_STAT_T_LOW);
अटल SENSOR_DEVICE_ATTR_RO(temp1_max_alarm, adt7x10_alarm,
			     ADT7X10_STAT_T_HIGH);
अटल SENSOR_DEVICE_ATTR_RO(temp1_crit_alarm, adt7x10_alarm,
			     ADT7X10_STAT_T_CRIT);
अटल DEVICE_ATTR_RO(name);

अटल काष्ठा attribute *adt7x10_attributes[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_crit.dev_attr.attr,
	&sensor_dev_attr_temp1_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_min_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_min_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_max_alarm.dev_attr.attr,
	&sensor_dev_attr_temp1_crit_alarm.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group adt7x10_group = अणु
	.attrs = adt7x10_attributes,
पूर्ण;

पूर्णांक adt7x10_probe(काष्ठा device *dev, स्थिर अक्षर *name, पूर्णांक irq,
		  स्थिर काष्ठा adt7x10_ops *ops)
अणु
	काष्ठा adt7x10_data *data;
	पूर्णांक ret;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->ops = ops;
	data->name = name;

	dev_set_drvdata(dev, data);
	mutex_init(&data->update_lock);

	/* configure as specअगरied */
	ret = adt7x10_पढ़ो_byte(dev, ADT7X10_CONFIG);
	अगर (ret < 0) अणु
		dev_dbg(dev, "Can't read config? %d\n", ret);
		वापस ret;
	पूर्ण
	data->oldconfig = ret;

	/*
	 * Set to 16 bit resolution, continous conversion and comparator mode.
	 */
	data->config = data->oldconfig;
	data->config &= ~(ADT7X10_MODE_MASK | ADT7X10_CT_POLARITY |
			ADT7X10_INT_POLARITY);
	data->config |= ADT7X10_FULL | ADT7X10_RESOLUTION | ADT7X10_EVENT_MODE;

	अगर (data->config != data->oldconfig) अणु
		ret = adt7x10_ग_लिखो_byte(dev, ADT7X10_CONFIG, data->config);
		अगर (ret)
			वापस ret;
	पूर्ण
	dev_dbg(dev, "Config %02x\n", data->config);

	ret = adt7x10_fill_cache(dev);
	अगर (ret)
		जाओ निकास_restore;

	/* Register sysfs hooks */
	ret = sysfs_create_group(&dev->kobj, &adt7x10_group);
	अगर (ret)
		जाओ निकास_restore;

	/*
	 * The I2C device will alपढ़ोy have it's own 'name' attribute, but क्रम
	 * the SPI device we need to रेजिस्टर it. name will only be non शून्य अगर
	 * the device करोesn't register the 'name' attribute on its own.
	 */
	अगर (name) अणु
		ret = device_create_file(dev, &dev_attr_name);
		अगर (ret)
			जाओ निकास_हटाओ;
	पूर्ण

	data->hwmon_dev = hwmon_device_रेजिस्टर(dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		ret = PTR_ERR(data->hwmon_dev);
		जाओ निकास_हटाओ_name;
	पूर्ण

	अगर (irq > 0) अणु
		ret = request_thपढ़ोed_irq(irq, शून्य, adt7x10_irq_handler,
				IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
				dev_name(dev), dev);
		अगर (ret)
			जाओ निकास_hwmon_device_unरेजिस्टर;
	पूर्ण

	वापस 0;

निकास_hwmon_device_unरेजिस्टर:
	hwmon_device_unरेजिस्टर(data->hwmon_dev);
निकास_हटाओ_name:
	अगर (name)
		device_हटाओ_file(dev, &dev_attr_name);
निकास_हटाओ:
	sysfs_हटाओ_group(&dev->kobj, &adt7x10_group);
निकास_restore:
	adt7x10_ग_लिखो_byte(dev, ADT7X10_CONFIG, data->oldconfig);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(adt7x10_probe);

पूर्णांक adt7x10_हटाओ(काष्ठा device *dev, पूर्णांक irq)
अणु
	काष्ठा adt7x10_data *data = dev_get_drvdata(dev);

	अगर (irq > 0)
		मुक्त_irq(irq, dev);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	अगर (data->name)
		device_हटाओ_file(dev, &dev_attr_name);
	sysfs_हटाओ_group(&dev->kobj, &adt7x10_group);
	अगर (data->oldconfig != data->config)
		adt7x10_ग_लिखो_byte(dev, ADT7X10_CONFIG, data->oldconfig);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(adt7x10_हटाओ);

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक adt7x10_suspend(काष्ठा device *dev)
अणु
	काष्ठा adt7x10_data *data = dev_get_drvdata(dev);

	वापस adt7x10_ग_लिखो_byte(dev, ADT7X10_CONFIG,
		data->config | ADT7X10_PD);
पूर्ण

अटल पूर्णांक adt7x10_resume(काष्ठा device *dev)
अणु
	काष्ठा adt7x10_data *data = dev_get_drvdata(dev);

	वापस adt7x10_ग_लिखो_byte(dev, ADT7X10_CONFIG, data->config);
पूर्ण

SIMPLE_DEV_PM_OPS(adt7x10_dev_pm_ops, adt7x10_suspend, adt7x10_resume);
EXPORT_SYMBOL_GPL(adt7x10_dev_pm_ops);

#पूर्ण_अगर /* CONFIG_PM_SLEEP */

MODULE_AUTHOR("Hartmut Knaack");
MODULE_DESCRIPTION("ADT7410/ADT7420, ADT7310/ADT7320 common code");
MODULE_LICENSE("GPL");
