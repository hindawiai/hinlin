<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * g760a - Driver क्रम the Global Mixed-mode Technology Inc. G760A
 *	   fan speed PWM controller chip
 *
 * Copyright (C) 2007  Herbert Valerio Riedel <hvr@gnu.org>
 *
 * Complete datasheet is available at GMT's website:
 * http://www.gmt.com.tw/product/datasheet/EDS-760A.pdf
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
#समावेश <linux/sysfs.h>

क्रमागत g760a_regs अणु
	G760A_REG_SET_CNT = 0x00,
	G760A_REG_ACT_CNT = 0x01,
	G760A_REG_FAN_STA = 0x02
पूर्ण;

#घोषणा G760A_REG_FAN_STA_RPM_OFF 0x1 /* +/-20% off */
#घोषणा G760A_REG_FAN_STA_RPM_LOW 0x2 /* below 1920rpm */

/* रेजिस्टर data is पढ़ो (and cached) at most once per second */
#घोषणा G760A_UPDATE_INTERVAL (HZ)

काष्ठा g760a_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex update_lock;

	/* board specअगरic parameters */
	u32 clk; /* शेष 32kHz */
	u16 fan_भाग; /* शेष P=2 */

	/* g760a रेजिस्टर cache */
	अचिन्हित पूर्णांक valid:1;
	अचिन्हित दीर्घ last_updated; /* In jअगरfies */

	u8 set_cnt; /* PWM (period) count number; 0xff stops fan */
	u8 act_cnt; /*   क्रमmula: cnt = (CLK * 30)/(rpm * P) */
	u8 fan_sta; /* bit 0: set when actual fan speed more than 20%
		     *   outside requested fan speed
		     * bit 1: set when fan speed below 1920 rpm
		     */
पूर्ण;

#घोषणा G760A_DEFAULT_CLK 32768
#घोषणा G760A_DEFAULT_FAN_DIV 2

#घोषणा PWM_FROM_CNT(cnt)	(0xff-(cnt))
#घोषणा PWM_TO_CNT(pwm)		(0xff-(pwm))

अटल अंतरभूत अचिन्हित पूर्णांक rpm_from_cnt(u8 val, u32 clk, u16 भाग)
अणु
	वापस ((val == 0x00) ? 0 : ((clk*30)/(val*भाग)));
पूर्ण

/* पढ़ो/ग_लिखो wrappers */
अटल पूर्णांक g760a_पढ़ो_value(काष्ठा i2c_client *client, क्रमागत g760a_regs reg)
अणु
	वापस i2c_smbus_पढ़ो_byte_data(client, reg);
पूर्ण

अटल पूर्णांक g760a_ग_लिखो_value(काष्ठा i2c_client *client, क्रमागत g760a_regs reg,
			     u16 value)
अणु
	वापस i2c_smbus_ग_लिखो_byte_data(client, reg, value);
पूर्ण

/*
 * sysfs attributes
 */

अटल काष्ठा g760a_data *g760a_update_client(काष्ठा device *dev)
अणु
	काष्ठा g760a_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + G760A_UPDATE_INTERVAL)
	    || !data->valid) अणु
		dev_dbg(&client->dev, "Starting g760a update\n");

		data->set_cnt = g760a_पढ़ो_value(client, G760A_REG_SET_CNT);
		data->act_cnt = g760a_पढ़ो_value(client, G760A_REG_ACT_CNT);
		data->fan_sta = g760a_पढ़ो_value(client, G760A_REG_FAN_STA);

		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

अटल sमाप_प्रकार fan1_input_show(काष्ठा device *dev,
			       काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा g760a_data *data = g760a_update_client(dev);
	अचिन्हित पूर्णांक rpm = 0;

	mutex_lock(&data->update_lock);
	अगर (!(data->fan_sta & G760A_REG_FAN_STA_RPM_LOW))
		rpm = rpm_from_cnt(data->act_cnt, data->clk, data->fan_भाग);
	mutex_unlock(&data->update_lock);

	वापस प्र_लिखो(buf, "%d\n", rpm);
पूर्ण

अटल sमाप_प्रकार fan1_alarm_show(काष्ठा device *dev,
			       काष्ठा device_attribute *da, अक्षर *buf)
अणु
	काष्ठा g760a_data *data = g760a_update_client(dev);

	पूर्णांक fan_alarm = (data->fan_sta & G760A_REG_FAN_STA_RPM_OFF) ? 1 : 0;

	वापस प्र_लिखो(buf, "%d\n", fan_alarm);
पूर्ण

अटल sमाप_प्रकार pwm1_show(काष्ठा device *dev, काष्ठा device_attribute *da,
			 अक्षर *buf)
अणु
	काष्ठा g760a_data *data = g760a_update_client(dev);

	वापस प्र_लिखो(buf, "%d\n", PWM_FROM_CNT(data->set_cnt));
पूर्ण

अटल sमाप_प्रकार pwm1_store(काष्ठा device *dev, काष्ठा device_attribute *da,
			  स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा g760a_data *data = g760a_update_client(dev);
	काष्ठा i2c_client *client = data->client;
	अचिन्हित दीर्घ val;

	अगर (kम_से_अदीर्घ(buf, 10, &val))
		वापस -EINVAL;

	mutex_lock(&data->update_lock);
	data->set_cnt = PWM_TO_CNT(clamp_val(val, 0, 255));
	g760a_ग_लिखो_value(client, G760A_REG_SET_CNT, data->set_cnt);
	mutex_unlock(&data->update_lock);

	वापस count;
पूर्ण

अटल DEVICE_ATTR_RW(pwm1);
अटल DEVICE_ATTR_RO(fan1_input);
अटल DEVICE_ATTR_RO(fan1_alarm);

अटल काष्ठा attribute *g760a_attrs[] = अणु
	&dev_attr_pwm1.attr,
	&dev_attr_fan1_input.attr,
	&dev_attr_fan1_alarm.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(g760a);

/*
 * new-style driver model code
 */

अटल पूर्णांक g760a_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा g760a_data *data;
	काष्ठा device *hwmon_dev;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -EIO;

	data = devm_kzalloc(dev, माप(काष्ठा g760a_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);

	/* setup शेष configuration क्रम now */
	data->fan_भाग = G760A_DEFAULT_FAN_DIV;
	data->clk = G760A_DEFAULT_CLK;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev, client->name,
							   data,
							   g760a_groups);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id g760a_id[] = अणु
	अणु "g760a", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, g760a_id);

अटल काष्ठा i2c_driver g760a_driver = अणु
	.driver = अणु
		.name	= "g760a",
	पूर्ण,
	.probe_new = g760a_probe,
	.id_table = g760a_id,
पूर्ण;

module_i2c_driver(g760a_driver);

MODULE_AUTHOR("Herbert Valerio Riedel <hvr@gnu.org>");
MODULE_DESCRIPTION("GMT G760A driver");
MODULE_LICENSE("GPL");
