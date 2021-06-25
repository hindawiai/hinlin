<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * apds9802als.c - apds9802  ALS Driver
 *
 * Copyright (C) 2009 Intel Corp
 *
 *  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा ALS_MIN_RANGE_VAL 1
#घोषणा ALS_MAX_RANGE_VAL 2
#घोषणा POWER_STA_ENABLE 1
#घोषणा POWER_STA_DISABLE 0

#घोषणा DRIVER_NAME "apds9802als"

काष्ठा als_data अणु
	काष्ठा mutex mutex;
पूर्ण;

अटल sमाप_प्रकार als_sensing_range_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr,  अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक  val;

	val = i2c_smbus_पढ़ो_byte_data(client, 0x81);
	अगर (val < 0)
		वापस val;
	अगर (val & 1)
		वापस प्र_लिखो(buf, "4095\n");
	अन्यथा
		वापस प्र_लिखो(buf, "65535\n");
पूर्ण

अटल पूर्णांक als_रुको_क्रम_data_पढ़ोy(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	पूर्णांक ret;
	पूर्णांक retry = 10;

	करो अणु
		msleep(30);
		ret = i2c_smbus_पढ़ो_byte_data(client, 0x86);
	पूर्ण जबतक (!(ret & 0x80) && retry--);

	अगर (retry < 0) अणु
		dev_warn(dev, "timeout waiting for data ready\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार als_lux0_input_data_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा als_data *data = i2c_get_clientdata(client);
	पूर्णांक ret_val;
	पूर्णांक temp;

	/* Protect against parallel पढ़ोs */
	pm_runसमय_get_sync(dev);
	mutex_lock(&data->mutex);

	/* clear EOC पूर्णांकerrupt status */
	i2c_smbus_ग_लिखो_byte(client, 0x40);
	/* start measurement */
	temp = i2c_smbus_पढ़ो_byte_data(client, 0x81);
	i2c_smbus_ग_लिखो_byte_data(client, 0x81, temp | 0x08);

	ret_val = als_रुको_क्रम_data_पढ़ोy(dev);
	अगर (ret_val < 0)
		जाओ failed;

	temp = i2c_smbus_पढ़ो_byte_data(client, 0x8C); /* LSB data */
	अगर (temp < 0) अणु
		ret_val = temp;
		जाओ failed;
	पूर्ण
	ret_val = i2c_smbus_पढ़ो_byte_data(client, 0x8D); /* MSB data */
	अगर (ret_val < 0)
		जाओ failed;

	mutex_unlock(&data->mutex);
	pm_runसमय_put_sync(dev);

	temp = (ret_val << 8) | temp;
	वापस प्र_लिखो(buf, "%d\n", temp);
failed:
	mutex_unlock(&data->mutex);
	pm_runसमय_put_sync(dev);
	वापस ret_val;
पूर्ण

अटल sमाप_प्रकार als_sensing_range_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर  अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा als_data *data = i2c_get_clientdata(client);
	पूर्णांक ret_val;
	अचिन्हित दीर्घ val;

	ret_val = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret_val)
		वापस ret_val;

	अगर (val < 4096)
		val = 1;
	अन्यथा अगर (val < 65536)
		val = 2;
	अन्यथा
		वापस -दुस्फल;

	pm_runसमय_get_sync(dev);

	/* Make sure nobody अन्यथा पढ़ोs/modअगरies/ग_लिखोs 0x81 जबतक we
	   are active */
	mutex_lock(&data->mutex);

	ret_val = i2c_smbus_पढ़ो_byte_data(client, 0x81);
	अगर (ret_val < 0)
		जाओ fail;

	/* Reset the bits beक्रमe setting them */
	ret_val = ret_val & 0xFA;

	अगर (val == 1) /* Setting detection range up to 4k LUX */
		ret_val = (ret_val | 0x01);
	अन्यथा /* Setting detection range up to 64k LUX*/
		ret_val = (ret_val | 0x00);

	ret_val = i2c_smbus_ग_लिखो_byte_data(client, 0x81, ret_val);

	अगर (ret_val >= 0) अणु
		/* All OK */
		mutex_unlock(&data->mutex);
		pm_runसमय_put_sync(dev);
		वापस count;
	पूर्ण
fail:
	mutex_unlock(&data->mutex);
	pm_runसमय_put_sync(dev);
	वापस ret_val;
पूर्ण

अटल पूर्णांक als_set_घातer_state(काष्ठा i2c_client *client, bool on_off)
अणु
	पूर्णांक ret_val;
	काष्ठा als_data *data = i2c_get_clientdata(client);

	mutex_lock(&data->mutex);
	ret_val = i2c_smbus_पढ़ो_byte_data(client, 0x80);
	अगर (ret_val < 0)
		जाओ fail;
	अगर (on_off)
		ret_val = ret_val | 0x01;
	अन्यथा
		ret_val = ret_val & 0xFE;
	ret_val = i2c_smbus_ग_लिखो_byte_data(client, 0x80, ret_val);
fail:
	mutex_unlock(&data->mutex);
	वापस ret_val;
पूर्ण

अटल DEVICE_ATTR(lux0_sensor_range, S_IRUGO | S_IWUSR,
	als_sensing_range_show, als_sensing_range_store);
अटल DEVICE_ATTR(lux0_input, S_IRUGO, als_lux0_input_data_show, शून्य);

अटल काष्ठा attribute *mid_att_als[] = अणु
	&dev_attr_lux0_sensor_range.attr,
	&dev_attr_lux0_input.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group m_als_gr = अणु
	.name = "apds9802als",
	.attrs = mid_att_als
पूर्ण;

अटल पूर्णांक als_set_शेष_config(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret_val;
	/* Write the command and then चयन on */
	ret_val = i2c_smbus_ग_लिखो_byte_data(client, 0x80, 0x01);
	अगर (ret_val < 0) अणु
		dev_err(&client->dev, "failed default switch on write\n");
		वापस ret_val;
	पूर्ण
	/* detection range: 1~64K Lux, maunal measurement */
	ret_val = i2c_smbus_ग_लिखो_byte_data(client, 0x81, 0x08);
	अगर (ret_val < 0)
		dev_err(&client->dev, "failed default LUX on write\n");

	/*  We always get 0 क्रम the 1st measurement after प्रणाली घातer on,
	 *  so make sure it is finished beक्रमe user asks क्रम data.
	 */
	als_रुको_क्रम_data_पढ़ोy(&client->dev);

	वापस ret_val;
पूर्ण

अटल पूर्णांक apds9802als_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक res;
	काष्ठा als_data *data;

	data = kzalloc(माप(काष्ठा als_data), GFP_KERNEL);
	अगर (data == शून्य) अणु
		dev_err(&client->dev, "Memory allocation failed\n");
		वापस -ENOMEM;
	पूर्ण
	i2c_set_clientdata(client, data);
	res = sysfs_create_group(&client->dev.kobj, &m_als_gr);
	अगर (res) अणु
		dev_err(&client->dev, "device create file failed\n");
		जाओ als_error1;
	पूर्ण
	dev_info(&client->dev, "ALS chip found\n");
	als_set_शेष_config(client);
	mutex_init(&data->mutex);

	pm_runसमय_set_active(&client->dev);
	pm_runसमय_enable(&client->dev);

	वापस res;
als_error1:
	kमुक्त(data);
	वापस res;
पूर्ण

अटल पूर्णांक apds9802als_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा als_data *data = i2c_get_clientdata(client);

	pm_runसमय_get_sync(&client->dev);

	als_set_घातer_state(client, false);
	sysfs_हटाओ_group(&client->dev.kobj, &m_als_gr);

	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);
	pm_runसमय_put_noidle(&client->dev);

	kमुक्त(data);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक apds9802als_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	als_set_घातer_state(client, false);
	वापस 0;
पूर्ण

अटल पूर्णांक apds9802als_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);

	als_set_घातer_state(client, true);
	वापस 0;
पूर्ण

अटल UNIVERSAL_DEV_PM_OPS(apds9802als_pm_ops, apds9802als_suspend,
	apds9802als_resume, शून्य);

#घोषणा APDS9802ALS_PM_OPS (&apds9802als_pm_ops)

#अन्यथा	/* CONFIG_PM */
#घोषणा APDS9802ALS_PM_OPS शून्य
#पूर्ण_अगर	/* CONFIG_PM */

अटल स्थिर काष्ठा i2c_device_id apds9802als_id[] = अणु
	अणु DRIVER_NAME, 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, apds9802als_id);

अटल काष्ठा i2c_driver apds9802als_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.pm = APDS9802ALS_PM_OPS,
	पूर्ण,
	.probe = apds9802als_probe,
	.हटाओ = apds9802als_हटाओ,
	.id_table = apds9802als_id,
पूर्ण;

module_i2c_driver(apds9802als_driver);

MODULE_AUTHOR("Anantha Narayanan <Anantha.Narayanan@intel.com");
MODULE_DESCRIPTION("Avago apds9802als ALS Driver");
MODULE_LICENSE("GPL v2");
