<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * isl29020.c - Intersil  ALS Driver
 *
 * Copyright (C) 2008 Intel Corp
 *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Data sheet at: http://www.पूर्णांकersil.com/data/fn/fn6505.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/pm_runसमय.स>

अटल DEFINE_MUTEX(mutex);

अटल sमाप_प्रकार als_sensing_range_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr,  अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक  val;

	val = i2c_smbus_पढ़ो_byte_data(client, 0x00);

	अगर (val < 0)
		वापस val;
	वापस प्र_लिखो(buf, "%d000\n", 1 << (2 * (val & 3)));

पूर्ण

अटल sमाप_प्रकार als_lux_input_data_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक ret_val, val;
	अचिन्हित दीर्घ पूर्णांक lux;
	पूर्णांक temp;

	pm_runसमय_get_sync(dev);
	msleep(100);

	mutex_lock(&mutex);
	temp = i2c_smbus_पढ़ो_byte_data(client, 0x02); /* MSB data */
	अगर (temp < 0) अणु
		pm_runसमय_put_sync(dev);
		mutex_unlock(&mutex);
		वापस temp;
	पूर्ण

	ret_val = i2c_smbus_पढ़ो_byte_data(client, 0x01); /* LSB data */
	mutex_unlock(&mutex);

	अगर (ret_val < 0) अणु
		pm_runसमय_put_sync(dev);
		वापस ret_val;
	पूर्ण

	ret_val |= temp << 8;
	val = i2c_smbus_पढ़ो_byte_data(client, 0x00);
	pm_runसमय_put_sync(dev);
	अगर (val < 0)
		वापस val;
	lux = ((((1 << (2 * (val & 3))))*1000) * ret_val) / 65536;
	वापस प्र_लिखो(buf, "%ld\n", lux);
पूर्ण

अटल sमाप_प्रकार als_sensing_range_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर  अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक ret_val;
	अचिन्हित दीर्घ val;

	ret_val = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret_val)
		वापस ret_val;

	अगर (val < 1 || val > 64000)
		वापस -EINVAL;

	/* Pick the smallest sensor range that will meet our requirements */
	अगर (val <= 1000)
		val = 1;
	अन्यथा अगर (val <= 4000)
		val = 2;
	अन्यथा अगर (val <= 16000)
		val = 3;
	अन्यथा
		val = 4;

	ret_val = i2c_smbus_पढ़ो_byte_data(client, 0x00);
	अगर (ret_val < 0)
		वापस ret_val;

	ret_val &= 0xFC; /*reset the bit beक्रमe setting them */
	ret_val |= val - 1;
	ret_val = i2c_smbus_ग_लिखो_byte_data(client, 0x00, ret_val);

	अगर (ret_val < 0)
		वापस ret_val;
	वापस count;
पूर्ण

अटल व्योम als_set_घातer_state(काष्ठा i2c_client *client, पूर्णांक enable)
अणु
	पूर्णांक ret_val;

	ret_val = i2c_smbus_पढ़ो_byte_data(client, 0x00);
	अगर (ret_val < 0)
		वापस;

	अगर (enable)
		ret_val |= 0x80;
	अन्यथा
		ret_val &= 0x7F;

	i2c_smbus_ग_लिखो_byte_data(client, 0x00, ret_val);
पूर्ण

अटल DEVICE_ATTR(lux0_sensor_range, S_IRUGO | S_IWUSR,
	als_sensing_range_show, als_sensing_range_store);
अटल DEVICE_ATTR(lux0_input, S_IRUGO, als_lux_input_data_show, शून्य);

अटल काष्ठा attribute *mid_att_als[] = अणु
	&dev_attr_lux0_sensor_range.attr,
	&dev_attr_lux0_input.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group m_als_gr = अणु
	.name = "isl29020",
	.attrs = mid_att_als
पूर्ण;

अटल पूर्णांक als_set_शेष_config(काष्ठा i2c_client *client)
अणु
	पूर्णांक retval;

	retval = i2c_smbus_ग_लिखो_byte_data(client, 0x00, 0xc0);
	अगर (retval < 0) अणु
		dev_err(&client->dev, "default write failed.");
		वापस retval;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक  isl29020_probe(काष्ठा i2c_client *client,
					स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक res;

	res = als_set_शेष_config(client);
	अगर (res <  0)
		वापस res;

	res = sysfs_create_group(&client->dev.kobj, &m_als_gr);
	अगर (res) अणु
		dev_err(&client->dev, "isl29020: device create file failed\n");
		वापस res;
	पूर्ण
	dev_info(&client->dev, "%s isl29020: ALS chip found\n", client->name);
	als_set_घातer_state(client, 0);
	pm_runसमय_enable(&client->dev);
	वापस res;
पूर्ण

अटल पूर्णांक isl29020_हटाओ(काष्ठा i2c_client *client)
अणु
	pm_runसमय_disable(&client->dev);
	sysfs_हटाओ_group(&client->dev.kobj, &m_als_gr);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id isl29020_id[] = अणु
	अणु "isl29020", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, isl29020_id);

#अगर_घोषित CONFIG_PM

अटल पूर्णांक isl29020_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	als_set_घातer_state(client, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक isl29020_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	als_set_घातer_state(client, 1);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops isl29020_pm_ops = अणु
	.runसमय_suspend = isl29020_runसमय_suspend,
	.runसमय_resume = isl29020_runसमय_resume,
पूर्ण;

#घोषणा ISL29020_PM_OPS (&isl29020_pm_ops)
#अन्यथा	/* CONFIG_PM */
#घोषणा ISL29020_PM_OPS शून्य
#पूर्ण_अगर	/* CONFIG_PM */

अटल काष्ठा i2c_driver isl29020_driver = अणु
	.driver = अणु
		.name = "isl29020",
		.pm = ISL29020_PM_OPS,
	पूर्ण,
	.probe = isl29020_probe,
	.हटाओ = isl29020_हटाओ,
	.id_table = isl29020_id,
पूर्ण;

module_i2c_driver(isl29020_driver);

MODULE_AUTHOR("Kalhan Trisal <kalhan.trisal@intel.com>");
MODULE_DESCRIPTION("Intersil isl29020 ALS Driver");
MODULE_LICENSE("GPL v2");
