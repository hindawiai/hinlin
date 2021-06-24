<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Support क्रम the FTS Systemmonitoring Chip "Teutates"
 *
 * Copyright (C) 2016 Fujitsu Technology Solutions GmbH,
 *		  Thilo Cestonaro <thilo.cestonaro@ts.fujitsu.com>
 */
#समावेश <linux/err.h>
#समावेश <linux/fs.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/watchकरोg.h>

#घोषणा FTS_DEVICE_ID_REG		0x0000
#घोषणा FTS_DEVICE_REVISION_REG		0x0001
#घोषणा FTS_DEVICE_STATUS_REG		0x0004
#घोषणा FTS_SATELLITE_STATUS_REG	0x0005
#घोषणा FTS_EVENT_STATUS_REG		0x0006
#घोषणा FTS_GLOBAL_CONTROL_REG		0x0007

#घोषणा FTS_DEVICE_DETECT_REG_1		0x0C
#घोषणा FTS_DEVICE_DETECT_REG_2		0x0D
#घोषणा FTS_DEVICE_DETECT_REG_3		0x0E

#घोषणा FTS_SENSOR_EVENT_REG		0x0010

#घोषणा FTS_FAN_EVENT_REG		0x0014
#घोषणा FTS_FAN_PRESENT_REG		0x0015

#घोषणा FTS_POWER_ON_TIME_COUNTER_A	0x007A
#घोषणा FTS_POWER_ON_TIME_COUNTER_B	0x007B
#घोषणा FTS_POWER_ON_TIME_COUNTER_C	0x007C

#घोषणा FTS_PAGE_SELECT_REG		0x007F

#घोषणा FTS_WATCHDOG_TIME_PRESET	0x000B
#घोषणा FTS_WATCHDOG_CONTROL		0x5081

#घोषणा FTS_NO_FAN_SENSORS		0x08
#घोषणा FTS_NO_TEMP_SENSORS		0x10
#घोषणा FTS_NO_VOLT_SENSORS		0x04

अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x73, I2C_CLIENT_END पूर्ण;

अटल स्थिर काष्ठा i2c_device_id fts_id[] = अणु
	अणु "ftsteutates", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, fts_id);

क्रमागत WATCHDOG_RESOLUTION अणु
	seconds = 1,
	minutes = 60
पूर्ण;

काष्ठा fts_data अणु
	काष्ठा i2c_client *client;
	/* update sensor data lock */
	काष्ठा mutex update_lock;
	/* पढ़ो/ग_लिखो रेजिस्टर lock */
	काष्ठा mutex access_lock;
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */
	काष्ठा watchकरोg_device wdd;
	क्रमागत WATCHDOG_RESOLUTION resolution;
	bool valid; /* false until following fields are valid */

	u8 volt[FTS_NO_VOLT_SENSORS];

	u8 temp_input[FTS_NO_TEMP_SENSORS];
	u8 temp_alarm;

	u8 fan_present;
	u8 fan_input[FTS_NO_FAN_SENSORS]; /* in rps */
	u8 fan_source[FTS_NO_FAN_SENSORS];
	u8 fan_alarm;
पूर्ण;

#घोषणा FTS_REG_FAN_INPUT(idx) ((idx) + 0x20)
#घोषणा FTS_REG_FAN_SOURCE(idx) ((idx) + 0x30)
#घोषणा FTS_REG_FAN_CONTROL(idx) (((idx) << 16) + 0x4881)

#घोषणा FTS_REG_TEMP_INPUT(idx) ((idx) + 0x40)
#घोषणा FTS_REG_TEMP_CONTROL(idx) (((idx) << 16) + 0x0681)

#घोषणा FTS_REG_VOLT(idx) ((idx) + 0x18)

/*****************************************************************************/
/* I2C Helper functions							     */
/*****************************************************************************/
अटल पूर्णांक fts_पढ़ो_byte(काष्ठा i2c_client *client, अचिन्हित लघु reg)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर page = reg >> 8;
	काष्ठा fts_data *data = dev_get_drvdata(&client->dev);

	mutex_lock(&data->access_lock);

	dev_dbg(&client->dev, "page select - page: 0x%.02x\n", page);
	ret = i2c_smbus_ग_लिखो_byte_data(client, FTS_PAGE_SELECT_REG, page);
	अगर (ret < 0)
		जाओ error;

	reg &= 0xFF;
	ret = i2c_smbus_पढ़ो_byte_data(client, reg);
	dev_dbg(&client->dev, "read - reg: 0x%.02x: val: 0x%.02x\n", reg, ret);

error:
	mutex_unlock(&data->access_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक fts_ग_लिखो_byte(काष्ठा i2c_client *client, अचिन्हित लघु reg,
			  अचिन्हित अक्षर value)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर page = reg >> 8;
	काष्ठा fts_data *data = dev_get_drvdata(&client->dev);

	mutex_lock(&data->access_lock);

	dev_dbg(&client->dev, "page select - page: 0x%.02x\n", page);
	ret = i2c_smbus_ग_लिखो_byte_data(client, FTS_PAGE_SELECT_REG, page);
	अगर (ret < 0)
		जाओ error;

	reg &= 0xFF;
	dev_dbg(&client->dev,
		"write - reg: 0x%.02x: val: 0x%.02x\n", reg, value);
	ret = i2c_smbus_ग_लिखो_byte_data(client, reg, value);

error:
	mutex_unlock(&data->access_lock);
	वापस ret;
पूर्ण

/*****************************************************************************/
/* Data Updater Helper function						     */
/*****************************************************************************/
अटल पूर्णांक fts_update_device(काष्ठा fts_data *data)
अणु
	पूर्णांक i;
	पूर्णांक err = 0;

	mutex_lock(&data->update_lock);
	अगर (!समय_after(jअगरfies, data->last_updated + 2 * HZ) && data->valid)
		जाओ निकास;

	err = fts_पढ़ो_byte(data->client, FTS_DEVICE_STATUS_REG);
	अगर (err < 0)
		जाओ निकास;

	data->valid = !!(err & 0x02); /* Data not पढ़ोy yet */
	अगर (unlikely(!data->valid)) अणु
		err = -EAGAIN;
		जाओ निकास;
	पूर्ण

	err = fts_पढ़ो_byte(data->client, FTS_FAN_PRESENT_REG);
	अगर (err < 0)
		जाओ निकास;
	data->fan_present = err;

	err = fts_पढ़ो_byte(data->client, FTS_FAN_EVENT_REG);
	अगर (err < 0)
		जाओ निकास;
	data->fan_alarm = err;

	क्रम (i = 0; i < FTS_NO_FAN_SENSORS; i++) अणु
		अगर (data->fan_present & BIT(i)) अणु
			err = fts_पढ़ो_byte(data->client, FTS_REG_FAN_INPUT(i));
			अगर (err < 0)
				जाओ निकास;
			data->fan_input[i] = err;

			err = fts_पढ़ो_byte(data->client,
					    FTS_REG_FAN_SOURCE(i));
			अगर (err < 0)
				जाओ निकास;
			data->fan_source[i] = err;
		पूर्ण अन्यथा अणु
			data->fan_input[i] = 0;
			data->fan_source[i] = 0;
		पूर्ण
	पूर्ण

	err = fts_पढ़ो_byte(data->client, FTS_SENSOR_EVENT_REG);
	अगर (err < 0)
		जाओ निकास;
	data->temp_alarm = err;

	क्रम (i = 0; i < FTS_NO_TEMP_SENSORS; i++) अणु
		err = fts_पढ़ो_byte(data->client, FTS_REG_TEMP_INPUT(i));
		अगर (err < 0)
			जाओ निकास;
		data->temp_input[i] = err;
	पूर्ण

	क्रम (i = 0; i < FTS_NO_VOLT_SENSORS; i++) अणु
		err = fts_पढ़ो_byte(data->client, FTS_REG_VOLT(i));
		अगर (err < 0)
			जाओ निकास;
		data->volt[i] = err;
	पूर्ण
	data->last_updated = jअगरfies;
	err = 0;
निकास:
	mutex_unlock(&data->update_lock);
	वापस err;
पूर्ण

/*****************************************************************************/
/* Watchकरोg functions							     */
/*****************************************************************************/
अटल पूर्णांक fts_wd_set_resolution(काष्ठा fts_data *data,
				 क्रमागत WATCHDOG_RESOLUTION resolution)
अणु
	पूर्णांक ret;

	अगर (data->resolution == resolution)
		वापस 0;

	ret = fts_पढ़ो_byte(data->client, FTS_WATCHDOG_CONTROL);
	अगर (ret < 0)
		वापस ret;

	अगर ((resolution == seconds && ret & BIT(1)) ||
	    (resolution == minutes && (ret & BIT(1)) == 0)) अणु
		data->resolution = resolution;
		वापस 0;
	पूर्ण

	अगर (resolution == seconds)
		ret |= BIT(1);
	अन्यथा
		ret &= ~BIT(1);

	ret = fts_ग_लिखो_byte(data->client, FTS_WATCHDOG_CONTROL, ret);
	अगर (ret < 0)
		वापस ret;

	data->resolution = resolution;
	वापस ret;
पूर्ण

अटल पूर्णांक fts_wd_set_समयout(काष्ठा watchकरोg_device *wdd, अचिन्हित पूर्णांक समयout)
अणु
	काष्ठा fts_data *data;
	क्रमागत WATCHDOG_RESOLUTION resolution = seconds;
	पूर्णांक ret;

	data = watchकरोg_get_drvdata(wdd);
	/* चयन watchकरोg resolution to minutes अगर समयout करोes not fit
	 * पूर्णांकo a byte
	 */
	अगर (समयout > 0xFF) अणु
		समयout = DIV_ROUND_UP(समयout, 60) * 60;
		resolution = minutes;
	पूर्ण

	ret = fts_wd_set_resolution(data, resolution);
	अगर (ret < 0)
		वापस ret;

	wdd->समयout = समयout;
	वापस 0;
पूर्ण

अटल पूर्णांक fts_wd_start(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा fts_data *data = watchकरोg_get_drvdata(wdd);

	वापस fts_ग_लिखो_byte(data->client, FTS_WATCHDOG_TIME_PRESET,
			      wdd->समयout / (u8)data->resolution);
पूर्ण

अटल पूर्णांक fts_wd_stop(काष्ठा watchकरोg_device *wdd)
अणु
	काष्ठा fts_data *data;

	data = watchकरोg_get_drvdata(wdd);
	वापस fts_ग_लिखो_byte(data->client, FTS_WATCHDOG_TIME_PRESET, 0);
पूर्ण

अटल स्थिर काष्ठा watchकरोg_info fts_wd_info = अणु
	.options = WDIOF_SETTIMEOUT | WDIOF_KEEPALIVEPING | WDIOF_MAGICCLOSE,
	.identity = "FTS Teutates Hardware Watchdog",
पूर्ण;

अटल स्थिर काष्ठा watchकरोg_ops fts_wd_ops = अणु
	.owner = THIS_MODULE,
	.start = fts_wd_start,
	.stop = fts_wd_stop,
	.set_समयout = fts_wd_set_समयout,
पूर्ण;

अटल पूर्णांक fts_watchकरोg_init(काष्ठा fts_data *data)
अणु
	पूर्णांक समयout, ret;

	watchकरोg_set_drvdata(&data->wdd, data);

	समयout = fts_पढ़ो_byte(data->client, FTS_WATCHDOG_TIME_PRESET);
	अगर (समयout < 0)
		वापस समयout;

	/* watchकरोg not running, set समयout to a शेष of 60 sec. */
	अगर (समयout == 0) अणु
		ret = fts_wd_set_resolution(data, seconds);
		अगर (ret < 0)
			वापस ret;
		data->wdd.समयout = 60;
	पूर्ण अन्यथा अणु
		ret = fts_पढ़ो_byte(data->client, FTS_WATCHDOG_CONTROL);
		अगर (ret < 0)
			वापस ret;

		data->resolution = ret & BIT(1) ? seconds : minutes;
		data->wdd.समयout = समयout * (u8)data->resolution;
		set_bit(WDOG_HW_RUNNING, &data->wdd.status);
	पूर्ण

	/* Register our watchकरोg part */
	data->wdd.info = &fts_wd_info;
	data->wdd.ops = &fts_wd_ops;
	data->wdd.parent = &data->client->dev;
	data->wdd.min_समयout = 1;

	/* max समयout 255 minutes. */
	data->wdd.max_hw_heartbeat_ms = 0xFF * 60 * MSEC_PER_SEC;

	वापस watchकरोg_रेजिस्टर_device(&data->wdd);
पूर्ण

/*****************************************************************************/
/* SysFS handler functions						     */
/*****************************************************************************/
अटल sमाप_प्रकार in_value_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा fts_data *data = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	पूर्णांक err;

	err = fts_update_device(data);
	अगर (err < 0)
		वापस err;

	वापस प्र_लिखो(buf, "%u\n", data->volt[index]);
पूर्ण

अटल sमाप_प्रकार temp_value_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा fts_data *data = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	पूर्णांक err;

	err = fts_update_device(data);
	अगर (err < 0)
		वापस err;

	वापस प्र_लिखो(buf, "%u\n", data->temp_input[index]);
पूर्ण

अटल sमाप_प्रकार temp_fault_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा fts_data *data = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	पूर्णांक err;

	err = fts_update_device(data);
	अगर (err < 0)
		वापस err;

	/* 00h Temperature = Sensor Error */
	वापस प्र_लिखो(buf, "%d\n", data->temp_input[index] == 0);
पूर्ण

अटल sमाप_प्रकार temp_alarm_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा fts_data *data = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	पूर्णांक err;

	err = fts_update_device(data);
	अगर (err < 0)
		वापस err;

	वापस प्र_लिखो(buf, "%u\n", !!(data->temp_alarm & BIT(index)));
पूर्ण

अटल sमाप_प्रकार
temp_alarm_store(काष्ठा device *dev, काष्ठा device_attribute *devattr,
		 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fts_data *data = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	दीर्घ ret;

	ret = fts_update_device(data);
	अगर (ret < 0)
		वापस ret;

	अगर (kम_से_अदीर्घ(buf, 10, &ret) || ret != 0)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	ret = fts_पढ़ो_byte(data->client, FTS_REG_TEMP_CONTROL(index));
	अगर (ret < 0)
		जाओ error;

	ret = fts_ग_लिखो_byte(data->client, FTS_REG_TEMP_CONTROL(index),
			     ret | 0x1);
	अगर (ret < 0)
		जाओ error;

	data->valid = false;
	ret = count;
error:
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार fan_value_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा fts_data *data = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	पूर्णांक err;

	err = fts_update_device(data);
	अगर (err < 0)
		वापस err;

	वापस प्र_लिखो(buf, "%u\n", data->fan_input[index]);
पूर्ण

अटल sमाप_प्रकार fan_source_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा fts_data *data = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	पूर्णांक err;

	err = fts_update_device(data);
	अगर (err < 0)
		वापस err;

	वापस प्र_लिखो(buf, "%u\n", data->fan_source[index]);
पूर्ण

अटल sमाप_प्रकार fan_alarm_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा fts_data *data = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	पूर्णांक err;

	err = fts_update_device(data);
	अगर (err < 0)
		वापस err;

	वापस प्र_लिखो(buf, "%d\n", !!(data->fan_alarm & BIT(index)));
पूर्ण

अटल sमाप_प्रकार
fan_alarm_store(काष्ठा device *dev, काष्ठा device_attribute *devattr,
		स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fts_data *data = dev_get_drvdata(dev);
	पूर्णांक index = to_sensor_dev_attr(devattr)->index;
	दीर्घ ret;

	ret = fts_update_device(data);
	अगर (ret < 0)
		वापस ret;

	अगर (kम_से_अदीर्घ(buf, 10, &ret) || ret != 0)
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	ret = fts_पढ़ो_byte(data->client, FTS_REG_FAN_CONTROL(index));
	अगर (ret < 0)
		जाओ error;

	ret = fts_ग_लिखो_byte(data->client, FTS_REG_FAN_CONTROL(index),
			     ret | 0x1);
	अगर (ret < 0)
		जाओ error;

	data->valid = false;
	ret = count;
error:
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

/*****************************************************************************/
/* SysFS काष्ठाs							     */
/*****************************************************************************/

/* Temperature sensors */
अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp_value, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_input, temp_value, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_input, temp_value, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp4_input, temp_value, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp5_input, temp_value, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp6_input, temp_value, 5);
अटल SENSOR_DEVICE_ATTR_RO(temp7_input, temp_value, 6);
अटल SENSOR_DEVICE_ATTR_RO(temp8_input, temp_value, 7);
अटल SENSOR_DEVICE_ATTR_RO(temp9_input, temp_value, 8);
अटल SENSOR_DEVICE_ATTR_RO(temp10_input, temp_value, 9);
अटल SENSOR_DEVICE_ATTR_RO(temp11_input, temp_value, 10);
अटल SENSOR_DEVICE_ATTR_RO(temp12_input, temp_value, 11);
अटल SENSOR_DEVICE_ATTR_RO(temp13_input, temp_value, 12);
अटल SENSOR_DEVICE_ATTR_RO(temp14_input, temp_value, 13);
अटल SENSOR_DEVICE_ATTR_RO(temp15_input, temp_value, 14);
अटल SENSOR_DEVICE_ATTR_RO(temp16_input, temp_value, 15);

अटल SENSOR_DEVICE_ATTR_RO(temp1_fault, temp_fault, 0);
अटल SENSOR_DEVICE_ATTR_RO(temp2_fault, temp_fault, 1);
अटल SENSOR_DEVICE_ATTR_RO(temp3_fault, temp_fault, 2);
अटल SENSOR_DEVICE_ATTR_RO(temp4_fault, temp_fault, 3);
अटल SENSOR_DEVICE_ATTR_RO(temp5_fault, temp_fault, 4);
अटल SENSOR_DEVICE_ATTR_RO(temp6_fault, temp_fault, 5);
अटल SENSOR_DEVICE_ATTR_RO(temp7_fault, temp_fault, 6);
अटल SENSOR_DEVICE_ATTR_RO(temp8_fault, temp_fault, 7);
अटल SENSOR_DEVICE_ATTR_RO(temp9_fault, temp_fault, 8);
अटल SENSOR_DEVICE_ATTR_RO(temp10_fault, temp_fault, 9);
अटल SENSOR_DEVICE_ATTR_RO(temp11_fault, temp_fault, 10);
अटल SENSOR_DEVICE_ATTR_RO(temp12_fault, temp_fault, 11);
अटल SENSOR_DEVICE_ATTR_RO(temp13_fault, temp_fault, 12);
अटल SENSOR_DEVICE_ATTR_RO(temp14_fault, temp_fault, 13);
अटल SENSOR_DEVICE_ATTR_RO(temp15_fault, temp_fault, 14);
अटल SENSOR_DEVICE_ATTR_RO(temp16_fault, temp_fault, 15);

अटल SENSOR_DEVICE_ATTR_RW(temp1_alarm, temp_alarm, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp2_alarm, temp_alarm, 1);
अटल SENSOR_DEVICE_ATTR_RW(temp3_alarm, temp_alarm, 2);
अटल SENSOR_DEVICE_ATTR_RW(temp4_alarm, temp_alarm, 3);
अटल SENSOR_DEVICE_ATTR_RW(temp5_alarm, temp_alarm, 4);
अटल SENSOR_DEVICE_ATTR_RW(temp6_alarm, temp_alarm, 5);
अटल SENSOR_DEVICE_ATTR_RW(temp7_alarm, temp_alarm, 6);
अटल SENSOR_DEVICE_ATTR_RW(temp8_alarm, temp_alarm, 7);
अटल SENSOR_DEVICE_ATTR_RW(temp9_alarm, temp_alarm, 8);
अटल SENSOR_DEVICE_ATTR_RW(temp10_alarm, temp_alarm, 9);
अटल SENSOR_DEVICE_ATTR_RW(temp11_alarm, temp_alarm, 10);
अटल SENSOR_DEVICE_ATTR_RW(temp12_alarm, temp_alarm, 11);
अटल SENSOR_DEVICE_ATTR_RW(temp13_alarm, temp_alarm, 12);
अटल SENSOR_DEVICE_ATTR_RW(temp14_alarm, temp_alarm, 13);
अटल SENSOR_DEVICE_ATTR_RW(temp15_alarm, temp_alarm, 14);
अटल SENSOR_DEVICE_ATTR_RW(temp16_alarm, temp_alarm, 15);

अटल काष्ठा attribute *fts_temp_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_temp2_input.dev_attr.attr,
	&sensor_dev_attr_temp3_input.dev_attr.attr,
	&sensor_dev_attr_temp4_input.dev_attr.attr,
	&sensor_dev_attr_temp5_input.dev_attr.attr,
	&sensor_dev_attr_temp6_input.dev_attr.attr,
	&sensor_dev_attr_temp7_input.dev_attr.attr,
	&sensor_dev_attr_temp8_input.dev_attr.attr,
	&sensor_dev_attr_temp9_input.dev_attr.attr,
	&sensor_dev_attr_temp10_input.dev_attr.attr,
	&sensor_dev_attr_temp11_input.dev_attr.attr,
	&sensor_dev_attr_temp12_input.dev_attr.attr,
	&sensor_dev_attr_temp13_input.dev_attr.attr,
	&sensor_dev_attr_temp14_input.dev_attr.attr,
	&sensor_dev_attr_temp15_input.dev_attr.attr,
	&sensor_dev_attr_temp16_input.dev_attr.attr,

	&sensor_dev_attr_temp1_fault.dev_attr.attr,
	&sensor_dev_attr_temp2_fault.dev_attr.attr,
	&sensor_dev_attr_temp3_fault.dev_attr.attr,
	&sensor_dev_attr_temp4_fault.dev_attr.attr,
	&sensor_dev_attr_temp5_fault.dev_attr.attr,
	&sensor_dev_attr_temp6_fault.dev_attr.attr,
	&sensor_dev_attr_temp7_fault.dev_attr.attr,
	&sensor_dev_attr_temp8_fault.dev_attr.attr,
	&sensor_dev_attr_temp9_fault.dev_attr.attr,
	&sensor_dev_attr_temp10_fault.dev_attr.attr,
	&sensor_dev_attr_temp11_fault.dev_attr.attr,
	&sensor_dev_attr_temp12_fault.dev_attr.attr,
	&sensor_dev_attr_temp13_fault.dev_attr.attr,
	&sensor_dev_attr_temp14_fault.dev_attr.attr,
	&sensor_dev_attr_temp15_fault.dev_attr.attr,
	&sensor_dev_attr_temp16_fault.dev_attr.attr,

	&sensor_dev_attr_temp1_alarm.dev_attr.attr,
	&sensor_dev_attr_temp2_alarm.dev_attr.attr,
	&sensor_dev_attr_temp3_alarm.dev_attr.attr,
	&sensor_dev_attr_temp4_alarm.dev_attr.attr,
	&sensor_dev_attr_temp5_alarm.dev_attr.attr,
	&sensor_dev_attr_temp6_alarm.dev_attr.attr,
	&sensor_dev_attr_temp7_alarm.dev_attr.attr,
	&sensor_dev_attr_temp8_alarm.dev_attr.attr,
	&sensor_dev_attr_temp9_alarm.dev_attr.attr,
	&sensor_dev_attr_temp10_alarm.dev_attr.attr,
	&sensor_dev_attr_temp11_alarm.dev_attr.attr,
	&sensor_dev_attr_temp12_alarm.dev_attr.attr,
	&sensor_dev_attr_temp13_alarm.dev_attr.attr,
	&sensor_dev_attr_temp14_alarm.dev_attr.attr,
	&sensor_dev_attr_temp15_alarm.dev_attr.attr,
	&sensor_dev_attr_temp16_alarm.dev_attr.attr,
	शून्य
पूर्ण;

/* Fans */
अटल SENSOR_DEVICE_ATTR_RO(fan1_input, fan_value, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_input, fan_value, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan3_input, fan_value, 2);
अटल SENSOR_DEVICE_ATTR_RO(fan4_input, fan_value, 3);
अटल SENSOR_DEVICE_ATTR_RO(fan5_input, fan_value, 4);
अटल SENSOR_DEVICE_ATTR_RO(fan6_input, fan_value, 5);
अटल SENSOR_DEVICE_ATTR_RO(fan7_input, fan_value, 6);
अटल SENSOR_DEVICE_ATTR_RO(fan8_input, fan_value, 7);

अटल SENSOR_DEVICE_ATTR_RO(fan1_source, fan_source, 0);
अटल SENSOR_DEVICE_ATTR_RO(fan2_source, fan_source, 1);
अटल SENSOR_DEVICE_ATTR_RO(fan3_source, fan_source, 2);
अटल SENSOR_DEVICE_ATTR_RO(fan4_source, fan_source, 3);
अटल SENSOR_DEVICE_ATTR_RO(fan5_source, fan_source, 4);
अटल SENSOR_DEVICE_ATTR_RO(fan6_source, fan_source, 5);
अटल SENSOR_DEVICE_ATTR_RO(fan7_source, fan_source, 6);
अटल SENSOR_DEVICE_ATTR_RO(fan8_source, fan_source, 7);

अटल SENSOR_DEVICE_ATTR_RW(fan1_alarm, fan_alarm, 0);
अटल SENSOR_DEVICE_ATTR_RW(fan2_alarm, fan_alarm, 1);
अटल SENSOR_DEVICE_ATTR_RW(fan3_alarm, fan_alarm, 2);
अटल SENSOR_DEVICE_ATTR_RW(fan4_alarm, fan_alarm, 3);
अटल SENSOR_DEVICE_ATTR_RW(fan5_alarm, fan_alarm, 4);
अटल SENSOR_DEVICE_ATTR_RW(fan6_alarm, fan_alarm, 5);
अटल SENSOR_DEVICE_ATTR_RW(fan7_alarm, fan_alarm, 6);
अटल SENSOR_DEVICE_ATTR_RW(fan8_alarm, fan_alarm, 7);

अटल काष्ठा attribute *fts_fan_attrs[] = अणु
	&sensor_dev_attr_fan1_input.dev_attr.attr,
	&sensor_dev_attr_fan2_input.dev_attr.attr,
	&sensor_dev_attr_fan3_input.dev_attr.attr,
	&sensor_dev_attr_fan4_input.dev_attr.attr,
	&sensor_dev_attr_fan5_input.dev_attr.attr,
	&sensor_dev_attr_fan6_input.dev_attr.attr,
	&sensor_dev_attr_fan7_input.dev_attr.attr,
	&sensor_dev_attr_fan8_input.dev_attr.attr,

	&sensor_dev_attr_fan1_source.dev_attr.attr,
	&sensor_dev_attr_fan2_source.dev_attr.attr,
	&sensor_dev_attr_fan3_source.dev_attr.attr,
	&sensor_dev_attr_fan4_source.dev_attr.attr,
	&sensor_dev_attr_fan5_source.dev_attr.attr,
	&sensor_dev_attr_fan6_source.dev_attr.attr,
	&sensor_dev_attr_fan7_source.dev_attr.attr,
	&sensor_dev_attr_fan8_source.dev_attr.attr,

	&sensor_dev_attr_fan1_alarm.dev_attr.attr,
	&sensor_dev_attr_fan2_alarm.dev_attr.attr,
	&sensor_dev_attr_fan3_alarm.dev_attr.attr,
	&sensor_dev_attr_fan4_alarm.dev_attr.attr,
	&sensor_dev_attr_fan5_alarm.dev_attr.attr,
	&sensor_dev_attr_fan6_alarm.dev_attr.attr,
	&sensor_dev_attr_fan7_alarm.dev_attr.attr,
	&sensor_dev_attr_fan8_alarm.dev_attr.attr,
	शून्य
पूर्ण;

/* Voltages */
अटल SENSOR_DEVICE_ATTR_RO(in1_input, in_value, 0);
अटल SENSOR_DEVICE_ATTR_RO(in2_input, in_value, 1);
अटल SENSOR_DEVICE_ATTR_RO(in3_input, in_value, 2);
अटल SENSOR_DEVICE_ATTR_RO(in4_input, in_value, 3);
अटल काष्ठा attribute *fts_voltage_attrs[] = अणु
	&sensor_dev_attr_in1_input.dev_attr.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in3_input.dev_attr.attr,
	&sensor_dev_attr_in4_input.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group fts_voltage_attr_group = अणु
	.attrs = fts_voltage_attrs
पूर्ण;

अटल स्थिर काष्ठा attribute_group fts_temp_attr_group = अणु
	.attrs = fts_temp_attrs
पूर्ण;

अटल स्थिर काष्ठा attribute_group fts_fan_attr_group = अणु
	.attrs = fts_fan_attrs
पूर्ण;

अटल स्थिर काष्ठा attribute_group *fts_attr_groups[] = अणु
	&fts_voltage_attr_group,
	&fts_temp_attr_group,
	&fts_fan_attr_group,
	शून्य
पूर्ण;

/*****************************************************************************/
/* Module initialization / हटाओ functions				     */
/*****************************************************************************/
अटल पूर्णांक fts_detect(काष्ठा i2c_client *client,
		      काष्ठा i2c_board_info *info)
अणु
	पूर्णांक val;

	/* detection works with revision greater or equal to 0x2b */
	val = i2c_smbus_पढ़ो_byte_data(client, FTS_DEVICE_REVISION_REG);
	अगर (val < 0x2b)
		वापस -ENODEV;

	/* Device Detect Regs must have 0x17 0x34 and 0x54 */
	val = i2c_smbus_पढ़ो_byte_data(client, FTS_DEVICE_DETECT_REG_1);
	अगर (val != 0x17)
		वापस -ENODEV;

	val = i2c_smbus_पढ़ो_byte_data(client, FTS_DEVICE_DETECT_REG_2);
	अगर (val != 0x34)
		वापस -ENODEV;

	val = i2c_smbus_पढ़ो_byte_data(client, FTS_DEVICE_DETECT_REG_3);
	अगर (val != 0x54)
		वापस -ENODEV;

	/*
	 * 0x10 == Baseboard Management Controller, 0x01 == Teutates
	 * Device ID Reg needs to be 0x11
	 */
	val = i2c_smbus_पढ़ो_byte_data(client, FTS_DEVICE_ID_REG);
	अगर (val != 0x11)
		वापस -ENODEV;

	strlcpy(info->type, fts_id[0].name, I2C_NAME_SIZE);
	info->flags = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक fts_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा fts_data *data = dev_get_drvdata(&client->dev);

	watchकरोg_unरेजिस्टर_device(&data->wdd);
	वापस 0;
पूर्ण

अटल पूर्णांक fts_probe(काष्ठा i2c_client *client)
अणु
	u8 revision;
	काष्ठा fts_data *data;
	पूर्णांक err;
	s8 deviceid;
	काष्ठा device *hwmon_dev;

	अगर (client->addr != 0x73)
		वापस -ENODEV;

	/* Baseboard Management Controller check */
	deviceid = i2c_smbus_पढ़ो_byte_data(client, FTS_DEVICE_ID_REG);
	अगर (deviceid > 0 && (deviceid & 0xF0) == 0x10) अणु
		चयन (deviceid & 0x0F) अणु
		हाल 0x01:
			अवरोध;
		शेष:
			dev_dbg(&client->dev,
				"No Baseboard Management Controller\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_dbg(&client->dev, "No fujitsu board\n");
		वापस -ENODEV;
	पूर्ण

	data = devm_kzalloc(&client->dev, माप(काष्ठा fts_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	mutex_init(&data->update_lock);
	mutex_init(&data->access_lock);
	data->client = client;
	dev_set_drvdata(&client->dev, data);

	err = i2c_smbus_पढ़ो_byte_data(client, FTS_DEVICE_REVISION_REG);
	अगर (err < 0)
		वापस err;
	revision = err;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(&client->dev,
							   "ftsteutates",
							   data,
							   fts_attr_groups);
	अगर (IS_ERR(hwmon_dev))
		वापस PTR_ERR(hwmon_dev);

	err = fts_watchकरोg_init(data);
	अगर (err)
		वापस err;

	dev_info(&client->dev, "Detected FTS Teutates chip, revision: %d.%d\n",
		 (revision & 0xF0) >> 4, revision & 0x0F);
	वापस 0;
पूर्ण

/*****************************************************************************/
/* Module Details							     */
/*****************************************************************************/
अटल काष्ठा i2c_driver fts_driver = अणु
	.class = I2C_CLASS_HWMON,
	.driver = अणु
		.name = "ftsteutates",
	पूर्ण,
	.id_table = fts_id,
	.probe_new = fts_probe,
	.हटाओ = fts_हटाओ,
	.detect = fts_detect,
	.address_list = normal_i2c,
पूर्ण;

module_i2c_driver(fts_driver);

MODULE_AUTHOR("Thilo Cestonaro <thilo.cestonaro@ts.fujitsu.com>");
MODULE_DESCRIPTION("FTS Teutates driver");
MODULE_LICENSE("GPL");
