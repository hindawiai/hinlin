<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम MAX31730 3-Channel Remote Temperature Sensor
 *
 * Copyright (c) 2019 Guenter Roeck <linux@roeck-us.net>
 */

#समावेश <linux/bits.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

/* Addresses scanned */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x1c, 0x1d, 0x1e, 0x1f, 0x4c,
					     0x4d, 0x4e, 0x4f, I2C_CLIENT_END पूर्ण;

/* The MAX31730 रेजिस्टरs */
#घोषणा MAX31730_REG_TEMP		0x00
#घोषणा MAX31730_REG_CONF		0x13
#घोषणा  MAX31730_STOP			BIT(7)
#घोषणा  MAX31730_EXTRANGE		BIT(1)
#घोषणा MAX31730_REG_TEMP_OFFSET	0x16
#घोषणा  MAX31730_TEMP_OFFSET_BASELINE	0x77
#घोषणा MAX31730_REG_OFFSET_ENABLE	0x17
#घोषणा MAX31730_REG_TEMP_MAX		0x20
#घोषणा MAX31730_REG_TEMP_MIN		0x30
#घोषणा MAX31730_REG_STATUS_HIGH	0x32
#घोषणा MAX31730_REG_STATUS_LOW		0x33
#घोषणा MAX31730_REG_CHANNEL_ENABLE	0x35
#घोषणा MAX31730_REG_TEMP_FAULT		0x36

#घोषणा MAX31730_REG_MFG_ID		0x50
#घोषणा  MAX31730_MFG_ID		0x4d
#घोषणा MAX31730_REG_MFG_REV		0x51
#घोषणा  MAX31730_MFG_REV		0x01

#घोषणा MAX31730_TEMP_MIN		(-128000)
#घोषणा MAX31730_TEMP_MAX		127937

/* Each client has this additional data */
काष्ठा max31730_data अणु
	काष्ठा i2c_client	*client;
	u8			orig_conf;
	u8			current_conf;
	u8			offset_enable;
	u8			channel_enable;
पूर्ण;

/*-----------------------------------------------------------------------*/

अटल अंतरभूत दीर्घ max31730_reg_to_mc(s16 temp)
अणु
	वापस DIV_ROUND_CLOSEST((temp >> 4) * 1000, 16);
पूर्ण

अटल पूर्णांक max31730_ग_लिखो_config(काष्ठा max31730_data *data, u8 set_mask,
				 u8 clr_mask)
अणु
	u8 value;

	clr_mask |= MAX31730_EXTRANGE;
	value = data->current_conf & ~clr_mask;
	value |= set_mask;

	अगर (data->current_conf != value) अणु
		s32 err;

		err = i2c_smbus_ग_लिखो_byte_data(data->client, MAX31730_REG_CONF,
						value);
		अगर (err)
			वापस err;
		data->current_conf = value;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक max31730_set_enable(काष्ठा i2c_client *client, पूर्णांक reg,
			       u8 *confdata, पूर्णांक channel, bool enable)
अणु
	u8 regval = *confdata;
	पूर्णांक err;

	अगर (enable)
		regval |= BIT(channel);
	अन्यथा
		regval &= ~BIT(channel);

	अगर (regval != *confdata) अणु
		err = i2c_smbus_ग_लिखो_byte_data(client, reg, regval);
		अगर (err)
			वापस err;
		*confdata = regval;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक max31730_set_offset_enable(काष्ठा max31730_data *data, पूर्णांक channel,
				      bool enable)
अणु
	वापस max31730_set_enable(data->client, MAX31730_REG_OFFSET_ENABLE,
				   &data->offset_enable, channel, enable);
पूर्ण

अटल पूर्णांक max31730_set_channel_enable(काष्ठा max31730_data *data, पूर्णांक channel,
				       bool enable)
अणु
	वापस max31730_set_enable(data->client, MAX31730_REG_CHANNEL_ENABLE,
				   &data->channel_enable, channel, enable);
पूर्ण

अटल पूर्णांक max31730_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			 u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा max31730_data *data = dev_get_drvdata(dev);
	पूर्णांक regval, reg, offset;

	अगर (type != hwmon_temp)
		वापस -EINVAL;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		अगर (!(data->channel_enable & BIT(channel)))
			वापस -ENODATA;
		reg = MAX31730_REG_TEMP + (channel * 2);
		अवरोध;
	हाल hwmon_temp_max:
		reg = MAX31730_REG_TEMP_MAX + (channel * 2);
		अवरोध;
	हाल hwmon_temp_min:
		reg = MAX31730_REG_TEMP_MIN;
		अवरोध;
	हाल hwmon_temp_enable:
		*val = !!(data->channel_enable & BIT(channel));
		वापस 0;
	हाल hwmon_temp_offset:
		अगर (!channel)
			वापस -EINVAL;
		अगर (!(data->offset_enable & BIT(channel))) अणु
			*val = 0;
			वापस 0;
		पूर्ण
		offset = i2c_smbus_पढ़ो_byte_data(data->client,
						  MAX31730_REG_TEMP_OFFSET);
		अगर (offset < 0)
			वापस offset;
		*val = (offset - MAX31730_TEMP_OFFSET_BASELINE) * 125;
		वापस 0;
	हाल hwmon_temp_fault:
		regval = i2c_smbus_पढ़ो_byte_data(data->client,
						  MAX31730_REG_TEMP_FAULT);
		अगर (regval < 0)
			वापस regval;
		*val = !!(regval & BIT(channel));
		वापस 0;
	हाल hwmon_temp_min_alarm:
		regval = i2c_smbus_पढ़ो_byte_data(data->client,
						  MAX31730_REG_STATUS_LOW);
		अगर (regval < 0)
			वापस regval;
		*val = !!(regval & BIT(channel));
		वापस 0;
	हाल hwmon_temp_max_alarm:
		regval = i2c_smbus_पढ़ो_byte_data(data->client,
						  MAX31730_REG_STATUS_HIGH);
		अगर (regval < 0)
			वापस regval;
		*val = !!(regval & BIT(channel));
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
	regval = i2c_smbus_पढ़ो_word_swapped(data->client, reg);
	अगर (regval < 0)
		वापस regval;

	*val = max31730_reg_to_mc(regval);

	वापस 0;
पूर्ण

अटल पूर्णांक max31730_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			  u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा max31730_data *data = dev_get_drvdata(dev);
	पूर्णांक reg, err;

	अगर (type != hwmon_temp)
		वापस -EINVAL;

	चयन (attr) अणु
	हाल hwmon_temp_max:
		reg = MAX31730_REG_TEMP_MAX + channel * 2;
		अवरोध;
	हाल hwmon_temp_min:
		reg = MAX31730_REG_TEMP_MIN;
		अवरोध;
	हाल hwmon_temp_enable:
		अगर (val != 0 && val != 1)
			वापस -EINVAL;
		वापस max31730_set_channel_enable(data, channel, val);
	हाल hwmon_temp_offset:
		val = clamp_val(val, -14875, 17000) + 14875;
		val = DIV_ROUND_CLOSEST(val, 125);
		err = max31730_set_offset_enable(data, channel,
					val != MAX31730_TEMP_OFFSET_BASELINE);
		अगर (err)
			वापस err;
		वापस i2c_smbus_ग_लिखो_byte_data(data->client,
						 MAX31730_REG_TEMP_OFFSET, val);
	शेष:
		वापस -EINVAL;
	पूर्ण

	val = clamp_val(val, MAX31730_TEMP_MIN, MAX31730_TEMP_MAX);
	val = DIV_ROUND_CLOSEST(val << 4, 1000) << 4;

	वापस i2c_smbus_ग_लिखो_word_swapped(data->client, reg, (u16)val);
पूर्ण

अटल umode_t max31730_is_visible(स्थिर व्योम *data,
				   क्रमागत hwmon_sensor_types type,
				   u32 attr, पूर्णांक channel)
अणु
	चयन (type) अणु
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_input:
		हाल hwmon_temp_min_alarm:
		हाल hwmon_temp_max_alarm:
		हाल hwmon_temp_fault:
			वापस 0444;
		हाल hwmon_temp_min:
			वापस channel ? 0444 : 0644;
		हाल hwmon_temp_offset:
		हाल hwmon_temp_enable:
		हाल hwmon_temp_max:
			वापस 0644;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *max31730_info[] = अणु
	HWMON_CHANNEL_INFO(chip,
			   HWMON_C_REGISTER_TZ),
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MIN | HWMON_T_MAX |
			   HWMON_T_ENABLE |
			   HWMON_T_MIN_ALARM | HWMON_T_MAX_ALARM,
			   HWMON_T_INPUT | HWMON_T_MIN | HWMON_T_MAX |
			   HWMON_T_OFFSET | HWMON_T_ENABLE |
			   HWMON_T_MIN_ALARM | HWMON_T_MAX_ALARM |
			   HWMON_T_FAULT,
			   HWMON_T_INPUT | HWMON_T_MIN | HWMON_T_MAX |
			   HWMON_T_OFFSET | HWMON_T_ENABLE |
			   HWMON_T_MIN_ALARM | HWMON_T_MAX_ALARM |
			   HWMON_T_FAULT,
			   HWMON_T_INPUT | HWMON_T_MIN | HWMON_T_MAX |
			   HWMON_T_OFFSET | HWMON_T_ENABLE |
			   HWMON_T_MIN_ALARM | HWMON_T_MAX_ALARM |
			   HWMON_T_FAULT
			   ),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops max31730_hwmon_ops = अणु
	.is_visible = max31730_is_visible,
	.पढ़ो = max31730_पढ़ो,
	.ग_लिखो = max31730_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info max31730_chip_info = अणु
	.ops = &max31730_hwmon_ops,
	.info = max31730_info,
पूर्ण;

अटल व्योम max31730_हटाओ(व्योम *data)
अणु
	काष्ठा max31730_data *max31730 = data;
	काष्ठा i2c_client *client = max31730->client;

	i2c_smbus_ग_लिखो_byte_data(client, MAX31730_REG_CONF,
				  max31730->orig_conf);
पूर्ण

अटल पूर्णांक
max31730_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा max31730_data *data;
	पूर्णांक status, err;

	अगर (!i2c_check_functionality(client->adapter,
			I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA))
		वापस -EIO;

	data = devm_kzalloc(dev, माप(काष्ठा max31730_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;

	/* Cache original configuration and enable status */
	status = i2c_smbus_पढ़ो_byte_data(client, MAX31730_REG_CHANNEL_ENABLE);
	अगर (status < 0)
		वापस status;
	data->channel_enable = status;

	status = i2c_smbus_पढ़ो_byte_data(client, MAX31730_REG_OFFSET_ENABLE);
	अगर (status < 0)
		वापस status;
	data->offset_enable = status;

	status = i2c_smbus_पढ़ो_byte_data(client, MAX31730_REG_CONF);
	अगर (status < 0)
		वापस status;
	data->orig_conf = status;
	data->current_conf = status;

	err = max31730_ग_लिखो_config(data,
				    data->channel_enable ? 0 : MAX31730_STOP,
				    data->channel_enable ? MAX31730_STOP : 0);
	अगर (err)
		वापस err;

	dev_set_drvdata(dev, data);

	err = devm_add_action_or_reset(dev, max31730_हटाओ, data);
	अगर (err)
		वापस err;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, client->name,
							 data,
							 &max31730_chip_info,
							 शून्य);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max31730_ids[] = अणु
	अणु "max31730", 0, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max31730_ids);

अटल स्थिर काष्ठा of_device_id __maybe_unused max31730_of_match[] = अणु
	अणु
		.compatible = "maxim,max31730",
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, max31730_of_match);

अटल bool max31730_check_reg_temp(काष्ठा i2c_client *client,
				    पूर्णांक reg)
अणु
	पूर्णांक regval;

	regval = i2c_smbus_पढ़ो_byte_data(client, reg + 1);
	वापस regval < 0 || (regval & 0x0f);
पूर्ण

/* Return 0 अगर detection is successful, -ENODEV otherwise */
अटल पूर्णांक max31730_detect(काष्ठा i2c_client *client,
			   काष्ठा i2c_board_info *info)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	पूर्णांक regval;
	पूर्णांक i;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WORD_DATA))
		वापस -ENODEV;

	regval = i2c_smbus_पढ़ो_byte_data(client, MAX31730_REG_MFG_ID);
	अगर (regval != MAX31730_MFG_ID)
		वापस -ENODEV;
	regval = i2c_smbus_पढ़ो_byte_data(client, MAX31730_REG_MFG_REV);
	अगर (regval != MAX31730_MFG_REV)
		वापस -ENODEV;

	/* lower 4 bit of temperature and limit रेजिस्टरs must be 0 */
	अगर (max31730_check_reg_temp(client, MAX31730_REG_TEMP_MIN))
		वापस -ENODEV;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (max31730_check_reg_temp(client, MAX31730_REG_TEMP + i * 2))
			वापस -ENODEV;
		अगर (max31730_check_reg_temp(client,
					    MAX31730_REG_TEMP_MAX + i * 2))
			वापस -ENODEV;
	पूर्ण

	strlcpy(info->type, "max31730", I2C_NAME_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused max31730_suspend(काष्ठा device *dev)
अणु
	काष्ठा max31730_data *data = dev_get_drvdata(dev);

	वापस max31730_ग_लिखो_config(data, MAX31730_STOP, 0);
पूर्ण

अटल पूर्णांक __maybe_unused max31730_resume(काष्ठा device *dev)
अणु
	काष्ठा max31730_data *data = dev_get_drvdata(dev);

	वापस max31730_ग_लिखो_config(data, 0, MAX31730_STOP);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(max31730_pm_ops, max31730_suspend, max31730_resume);

अटल काष्ठा i2c_driver max31730_driver = अणु
	.class		= I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "max31730",
		.of_match_table = of_match_ptr(max31730_of_match),
		.pm	= &max31730_pm_ops,
	पूर्ण,
	.probe_new	= max31730_probe,
	.id_table	= max31730_ids,
	.detect		= max31730_detect,
	.address_list	= normal_i2c,
पूर्ण;

module_i2c_driver(max31730_driver);

MODULE_AUTHOR("Guenter Roeck <linux@roeck-us.net>");
MODULE_DESCRIPTION("MAX31730 driver");
MODULE_LICENSE("GPL");
