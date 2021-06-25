<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * hmc6352.c - Honeywell Compass Driver
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
#समावेश <linux/sysfs.h>
#समावेश <linux/nospec.h>

अटल DEFINE_MUTEX(compass_mutex);

अटल पूर्णांक compass_command(काष्ठा i2c_client *c, u8 cmd)
अणु
	पूर्णांक ret = i2c_master_send(c, &cmd, 1);
	अगर (ret < 0)
		dev_warn(&c->dev, "command '%c' failed.\n", cmd);
	वापस ret;
पूर्ण

अटल पूर्णांक compass_store(काष्ठा device *dev, स्थिर अक्षर *buf, माप_प्रकार count,
			स्थिर अक्षर *map)
अणु
	काष्ठा i2c_client *c = to_i2c_client(dev);
	पूर्णांक ret;
	अचिन्हित दीर्घ val;

	ret = kम_से_अदीर्घ(buf, 10, &val);
	अगर (ret)
		वापस ret;
	अगर (val >= म_माप(map))
		वापस -EINVAL;
	val = array_index_nospec(val, म_माप(map));
	mutex_lock(&compass_mutex);
	ret = compass_command(c, map[val]);
	mutex_unlock(&compass_mutex);
	अगर (ret < 0)
		वापस ret;
	वापस count;
पूर्ण

अटल sमाप_प्रकार compass_calibration_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	वापस compass_store(dev, buf, count, "EC");
पूर्ण

अटल sमाप_प्रकार compass_घातer_mode_store(काष्ठा device *dev,
		काष्ठा device_attribute *attr, स्थिर  अक्षर *buf, माप_प्रकार count)
अणु
	वापस compass_store(dev, buf, count, "SW");
पूर्ण

अटल sमाप_प्रकार compass_heading_data_show(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	अचिन्हित अक्षर i2c_data[2];
	पूर्णांक ret;

	mutex_lock(&compass_mutex);
	ret = compass_command(client, 'A');
	अगर (ret != 1) अणु
		mutex_unlock(&compass_mutex);
		वापस ret;
	पूर्ण
	msleep(10); /* sending 'A' cmd we need to रुको क्रम 7-10 millisecs */
	ret = i2c_master_recv(client, i2c_data, 2);
	mutex_unlock(&compass_mutex);
	अगर (ret < 0) अणु
		dev_warn(dev, "i2c read data cmd failed\n");
		वापस ret;
	पूर्ण
	ret = (i2c_data[0] << 8) | i2c_data[1];
	वापस प्र_लिखो(buf, "%d.%d\n", ret/10, ret%10);
पूर्ण


अटल DEVICE_ATTR(heading0_input, S_IRUGO, compass_heading_data_show, शून्य);
अटल DEVICE_ATTR(calibration, S_IWUSR, शून्य, compass_calibration_store);
अटल DEVICE_ATTR(घातer_state, S_IWUSR, शून्य, compass_घातer_mode_store);

अटल काष्ठा attribute *mid_att_compass[] = अणु
	&dev_attr_heading0_input.attr,
	&dev_attr_calibration.attr,
	&dev_attr_घातer_state.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group m_compass_gr = अणु
	.name = "hmc6352",
	.attrs = mid_att_compass
पूर्ण;

अटल पूर्णांक hmc6352_probe(काष्ठा i2c_client *client,
					स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक res;

	res = sysfs_create_group(&client->dev.kobj, &m_compass_gr);
	अगर (res) अणु
		dev_err(&client->dev, "device_create_file failed\n");
		वापस res;
	पूर्ण
	dev_info(&client->dev, "%s HMC6352 compass chip found\n",
							client->name);
	वापस 0;
पूर्ण

अटल पूर्णांक hmc6352_हटाओ(काष्ठा i2c_client *client)
अणु
	sysfs_हटाओ_group(&client->dev.kobj, &m_compass_gr);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id hmc6352_id[] = अणु
	अणु "hmc6352", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, hmc6352_id);

अटल काष्ठा i2c_driver hmc6352_driver = अणु
	.driver = अणु
		.name = "hmc6352",
	पूर्ण,
	.probe = hmc6352_probe,
	.हटाओ = hmc6352_हटाओ,
	.id_table = hmc6352_id,
पूर्ण;

module_i2c_driver(hmc6352_driver);

MODULE_AUTHOR("Kalhan Trisal <kalhan.trisal@intel.com");
MODULE_DESCRIPTION("hmc6352 Compass Driver");
MODULE_LICENSE("GPL v2");
