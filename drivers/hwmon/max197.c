<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Maxim MAX197 A/D Converter driver
 *
 * Copyright (c) 2012 Savoir-faire Linux Inc.
 *          Vivien Didelot <vivien.didelot@savoirfairelinux.com>
 *
 * For further inक्रमmation, see the Documentation/hwmon/max197.rst file.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/max197.h>

#घोषणा MAX199_LIMIT	4000		/* 4V */
#घोषणा MAX197_LIMIT	10000		/* 10V */

#घोषणा MAX197_NUM_CH	8		/* 8 Analog Input Channels */

/* Control byte क्रमmat */
#घोषणा MAX197_BIP	(1 << 3)	/* Bipolarity */
#घोषणा MAX197_RNG	(1 << 4)	/* Full range */

#घोषणा MAX197_SCALE	12207		/* Scale coefficient क्रम raw data */

/* List of supported chips */
क्रमागत max197_chips अणु max197, max199 पूर्ण;

/**
 * काष्ठा max197_data - device instance specअगरic data
 * @pdata:		Platक्रमm data.
 * @hwmon_dev:		The hwmon device.
 * @lock:		Read/Write mutex.
 * @limit:		Max range value (10V क्रम MAX197, 4V क्रम MAX199).
 * @scale:		Need to scale.
 * @ctrl_bytes:		Channels control byte.
 */
काष्ठा max197_data अणु
	काष्ठा max197_platक्रमm_data *pdata;
	काष्ठा device *hwmon_dev;
	काष्ठा mutex lock;
	पूर्णांक limit;
	bool scale;
	u8 ctrl_bytes[MAX197_NUM_CH];
पूर्ण;

अटल अंतरभूत व्योम max197_set_unipolarity(काष्ठा max197_data *data, पूर्णांक channel)
अणु
	data->ctrl_bytes[channel] &= ~MAX197_BIP;
पूर्ण

अटल अंतरभूत व्योम max197_set_bipolarity(काष्ठा max197_data *data, पूर्णांक channel)
अणु
	data->ctrl_bytes[channel] |= MAX197_BIP;
पूर्ण

अटल अंतरभूत व्योम max197_set_half_range(काष्ठा max197_data *data, पूर्णांक channel)
अणु
	data->ctrl_bytes[channel] &= ~MAX197_RNG;
पूर्ण

अटल अंतरभूत व्योम max197_set_full_range(काष्ठा max197_data *data, पूर्णांक channel)
अणु
	data->ctrl_bytes[channel] |= MAX197_RNG;
पूर्ण

अटल अंतरभूत bool max197_is_bipolar(काष्ठा max197_data *data, पूर्णांक channel)
अणु
	वापस data->ctrl_bytes[channel] & MAX197_BIP;
पूर्ण

अटल अंतरभूत bool max197_is_full_range(काष्ठा max197_data *data, पूर्णांक channel)
अणु
	वापस data->ctrl_bytes[channel] & MAX197_RNG;
पूर्ण

/* Function called on पढ़ो access on inअणु0,1,2,3,4,5,6,7पूर्ण_अणुmin,maxपूर्ण */
अटल sमाप_प्रकार max197_show_range(काष्ठा device *dev,
				 काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा max197_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	पूर्णांक channel = attr->index;
	bool is_min = attr->nr;
	पूर्णांक range;

	अगर (mutex_lock_पूर्णांकerruptible(&data->lock))
		वापस -ERESTARTSYS;

	range = max197_is_full_range(data, channel) ?
		data->limit : data->limit / 2;
	अगर (is_min) अणु
		अगर (max197_is_bipolar(data, channel))
			range = -range;
		अन्यथा
			range = 0;
	पूर्ण

	mutex_unlock(&data->lock);

	वापस प्र_लिखो(buf, "%d\n", range);
पूर्ण

/* Function called on ग_लिखो access on inअणु0,1,2,3,4,5,6,7पूर्ण_अणुmin,maxपूर्ण */
अटल sमाप_प्रकार max197_store_range(काष्ठा device *dev,
				  काष्ठा device_attribute *devattr,
				  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा max197_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute_2 *attr = to_sensor_dev_attr_2(devattr);
	पूर्णांक channel = attr->index;
	bool is_min = attr->nr;
	दीर्घ value;
	पूर्णांक half = data->limit / 2;
	पूर्णांक full = data->limit;

	अगर (kम_से_दीर्घ(buf, 10, &value))
		वापस -EINVAL;

	अगर (is_min) अणु
		अगर (value <= -full)
			value = -full;
		अन्यथा अगर (value < 0)
			value = -half;
		अन्यथा
			value = 0;
	पूर्ण अन्यथा अणु
		अगर (value >= full)
			value = full;
		अन्यथा
			value = half;
	पूर्ण

	अगर (mutex_lock_पूर्णांकerruptible(&data->lock))
		वापस -ERESTARTSYS;

	अगर (value == 0) अणु
		/* We can deduce only the polarity */
		max197_set_unipolarity(data, channel);
	पूर्ण अन्यथा अगर (value == -half) अणु
		max197_set_bipolarity(data, channel);
		max197_set_half_range(data, channel);
	पूर्ण अन्यथा अगर (value == -full) अणु
		max197_set_bipolarity(data, channel);
		max197_set_full_range(data, channel);
	पूर्ण अन्यथा अगर (value == half) अणु
		/* We can deduce only the range */
		max197_set_half_range(data, channel);
	पूर्ण अन्यथा अगर (value == full) अणु
		/* We can deduce only the range */
		max197_set_full_range(data, channel);
	पूर्ण

	mutex_unlock(&data->lock);

	वापस count;
पूर्ण

/* Function called on पढ़ो access on inअणु0,1,2,3,4,5,6,7पूर्ण_input */
अटल sमाप_प्रकार max197_show_input(काष्ठा device *dev,
				 काष्ठा device_attribute *devattr,
				 अक्षर *buf)
अणु
	काष्ठा max197_data *data = dev_get_drvdata(dev);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	पूर्णांक channel = attr->index;
	s32 value;
	पूर्णांक ret;

	अगर (mutex_lock_पूर्णांकerruptible(&data->lock))
		वापस -ERESTARTSYS;

	ret = data->pdata->convert(data->ctrl_bytes[channel]);
	अगर (ret < 0) अणु
		dev_err(dev, "conversion failed\n");
		जाओ unlock;
	पूर्ण
	value = ret;

	/*
	 * Coefficient to apply on raw value.
	 * See Table 1. Full Scale and Zero Scale in the MAX197 datasheet.
	 */
	अगर (data->scale) अणु
		value *= MAX197_SCALE;
		अगर (max197_is_full_range(data, channel))
			value *= 2;
		value /= 10000;
	पूर्ण

	ret = प्र_लिखो(buf, "%d\n", value);

unlock:
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	वापस प्र_लिखो(buf, "%s\n", pdev->name);
पूर्ण

#घोषणा MAX197_SENSOR_DEVICE_ATTR_CH(chan)				\
	अटल SENSOR_DEVICE_ATTR(in##chan##_input, S_IRUGO,		\
				  max197_show_input, शून्य, chan);	\
	अटल SENSOR_DEVICE_ATTR_2(in##chan##_min, S_IRUGO | S_IWUSR,	\
				    max197_show_range,			\
				    max197_store_range,			\
				    true, chan);			\
	अटल SENSOR_DEVICE_ATTR_2(in##chan##_max, S_IRUGO | S_IWUSR,	\
				    max197_show_range,			\
				    max197_store_range,			\
				    false, chan)

#घोषणा MAX197_SENSOR_DEV_ATTR_IN(chan)					\
	&sensor_dev_attr_in##chan##_input.dev_attr.attr,		\
	&sensor_dev_attr_in##chan##_max.dev_attr.attr,			\
	&sensor_dev_attr_in##chan##_min.dev_attr.attr

अटल DEVICE_ATTR_RO(name);

MAX197_SENSOR_DEVICE_ATTR_CH(0);
MAX197_SENSOR_DEVICE_ATTR_CH(1);
MAX197_SENSOR_DEVICE_ATTR_CH(2);
MAX197_SENSOR_DEVICE_ATTR_CH(3);
MAX197_SENSOR_DEVICE_ATTR_CH(4);
MAX197_SENSOR_DEVICE_ATTR_CH(5);
MAX197_SENSOR_DEVICE_ATTR_CH(6);
MAX197_SENSOR_DEVICE_ATTR_CH(7);

अटल स्थिर काष्ठा attribute_group max197_sysfs_group = अणु
	.attrs = (काष्ठा attribute *[]) अणु
		&dev_attr_name.attr,
		MAX197_SENSOR_DEV_ATTR_IN(0),
		MAX197_SENSOR_DEV_ATTR_IN(1),
		MAX197_SENSOR_DEV_ATTR_IN(2),
		MAX197_SENSOR_DEV_ATTR_IN(3),
		MAX197_SENSOR_DEV_ATTR_IN(4),
		MAX197_SENSOR_DEV_ATTR_IN(5),
		MAX197_SENSOR_DEV_ATTR_IN(6),
		MAX197_SENSOR_DEV_ATTR_IN(7),
		शून्य
	पूर्ण,
पूर्ण;

अटल पूर्णांक max197_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ch, ret;
	काष्ठा max197_data *data;
	काष्ठा max197_platक्रमm_data *pdata = dev_get_platdata(&pdev->dev);
	क्रमागत max197_chips chip = platक्रमm_get_device_id(pdev)->driver_data;

	अगर (pdata == शून्य) अणु
		dev_err(&pdev->dev, "no platform data supplied\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pdata->convert == शून्य) अणु
		dev_err(&pdev->dev, "no convert function supplied\n");
		वापस -EINVAL;
	पूर्ण

	data = devm_kzalloc(&pdev->dev, माप(काष्ठा max197_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->pdata = pdata;
	mutex_init(&data->lock);

	अगर (chip == max197) अणु
		data->limit = MAX197_LIMIT;
		data->scale = true;
	पूर्ण अन्यथा अणु
		data->limit = MAX199_LIMIT;
		data->scale = false;
	पूर्ण

	क्रम (ch = 0; ch < MAX197_NUM_CH; ch++)
		data->ctrl_bytes[ch] = (u8) ch;

	platक्रमm_set_drvdata(pdev, data);

	ret = sysfs_create_group(&pdev->dev.kobj, &max197_sysfs_group);
	अगर (ret) अणु
		dev_err(&pdev->dev, "sysfs create group failed\n");
		वापस ret;
	पूर्ण

	data->hwmon_dev = hwmon_device_रेजिस्टर(&pdev->dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		ret = PTR_ERR(data->hwmon_dev);
		dev_err(&pdev->dev, "hwmon device register failed\n");
		जाओ error;
	पूर्ण

	वापस 0;

error:
	sysfs_हटाओ_group(&pdev->dev.kobj, &max197_sysfs_group);
	वापस ret;
पूर्ण

अटल पूर्णांक max197_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा max197_data *data = platक्रमm_get_drvdata(pdev);

	hwmon_device_unरेजिस्टर(data->hwmon_dev);
	sysfs_हटाओ_group(&pdev->dev.kobj, &max197_sysfs_group);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id max197_device_ids[] = अणु
	अणु "max197", max197 पूर्ण,
	अणु "max199", max199 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, max197_device_ids);

अटल काष्ठा platक्रमm_driver max197_driver = अणु
	.driver = अणु
		.name = "max197",
	पूर्ण,
	.probe = max197_probe,
	.हटाओ = max197_हटाओ,
	.id_table = max197_device_ids,
पूर्ण;
module_platक्रमm_driver(max197_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Savoir-faire Linux Inc. <kernel@savoirfairelinux.com>");
MODULE_DESCRIPTION("Maxim MAX197 A/D Converter driver");
