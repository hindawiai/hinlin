<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 IBM Corp.
 *
 * Driver क्रम the Nuvoton W83773G SMBus temperature sensor IC.
 * Supported models: W83773G
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>

/* W83773 has 3 channels */
#घोषणा W83773_CHANNELS				3

/* The W83773 रेजिस्टरs */
#घोषणा W83773_CONVERSION_RATE_REG_READ		0x04
#घोषणा W83773_CONVERSION_RATE_REG_WRITE	0x0A
#घोषणा W83773_MANUFACTURER_ID_REG		0xFE
#घोषणा W83773_LOCAL_TEMP			0x00

अटल स्थिर u8 W83773_STATUS[2] = अणु 0x02, 0x17 पूर्ण;

अटल स्थिर u8 W83773_TEMP_LSB[2] = अणु 0x10, 0x25 पूर्ण;
अटल स्थिर u8 W83773_TEMP_MSB[2] = अणु 0x01, 0x24 पूर्ण;

अटल स्थिर u8 W83773_OFFSET_LSB[2] = अणु 0x12, 0x16 पूर्ण;
अटल स्थिर u8 W83773_OFFSET_MSB[2] = अणु 0x11, 0x15 पूर्ण;

/* this is the number of sensors in the device */
अटल स्थिर काष्ठा i2c_device_id w83773_id[] = अणु
	अणु "w83773g" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, w83773_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused w83773_of_match[] = अणु
	अणु
		.compatible = "nuvoton,w83773g"
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, w83773_of_match);

अटल अंतरभूत दीर्घ temp_of_local(s8 reg)
अणु
	वापस reg * 1000;
पूर्ण

अटल अंतरभूत दीर्घ temp_of_remote(s8 hb, u8 lb)
अणु
	वापस (hb << 3 | lb >> 5) * 125;
पूर्ण

अटल पूर्णांक get_local_temp(काष्ठा regmap *regmap, दीर्घ *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, W83773_LOCAL_TEMP, &regval);
	अगर (ret < 0)
		वापस ret;

	*val = temp_of_local(regval);
	वापस 0;
पूर्ण

अटल पूर्णांक get_remote_temp(काष्ठा regmap *regmap, पूर्णांक index, दीर्घ *val)
अणु
	अचिन्हित पूर्णांक regval_high;
	अचिन्हित पूर्णांक regval_low;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, W83773_TEMP_MSB[index], &regval_high);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(regmap, W83773_TEMP_LSB[index], &regval_low);
	अगर (ret < 0)
		वापस ret;

	*val = temp_of_remote(regval_high, regval_low);
	वापस 0;
पूर्ण

अटल पूर्णांक get_fault(काष्ठा regmap *regmap, पूर्णांक index, दीर्घ *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, W83773_STATUS[index], &regval);
	अगर (ret < 0)
		वापस ret;

	*val = (regval & 0x04) >> 2;
	वापस 0;
पूर्ण

अटल पूर्णांक get_offset(काष्ठा regmap *regmap, पूर्णांक index, दीर्घ *val)
अणु
	अचिन्हित पूर्णांक regval_high;
	अचिन्हित पूर्णांक regval_low;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, W83773_OFFSET_MSB[index], &regval_high);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_पढ़ो(regmap, W83773_OFFSET_LSB[index], &regval_low);
	अगर (ret < 0)
		वापस ret;

	*val = temp_of_remote(regval_high, regval_low);
	वापस 0;
पूर्ण

अटल पूर्णांक set_offset(काष्ठा regmap *regmap, पूर्णांक index, दीर्घ val)
अणु
	पूर्णांक ret;
	u8 high_byte;
	u8 low_byte;

	val = clamp_val(val, -127825, 127825);
	/* offset value equals to (high_byte << 3 | low_byte >> 5) * 125 */
	val /= 125;
	high_byte = val >> 3;
	low_byte = (val & 0x07) << 5;

	ret = regmap_ग_लिखो(regmap, W83773_OFFSET_MSB[index], high_byte);
	अगर (ret < 0)
		वापस ret;

	वापस regmap_ग_लिखो(regmap, W83773_OFFSET_LSB[index], low_byte);
पूर्ण

अटल पूर्णांक get_update_पूर्णांकerval(काष्ठा regmap *regmap, दीर्घ *val)
अणु
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, W83773_CONVERSION_RATE_REG_READ, &regval);
	अगर (ret < 0)
		वापस ret;

	*val = 16000 >> regval;
	वापस 0;
पूर्ण

अटल पूर्णांक set_update_पूर्णांकerval(काष्ठा regmap *regmap, दीर्घ val)
अणु
	पूर्णांक rate;

	/*
	 * For valid rates, पूर्णांकerval can be calculated as
	 *	पूर्णांकerval = (1 << (8 - rate)) * 62.5;
	 * Rounded rate is thereक्रमe
	 *	rate = 8 - __fls(पूर्णांकerval * 8 / (62.5 * 7));
	 * Use clamp_val() to aव्योम overflows, and to ensure valid input
	 * क्रम __fls.
	 */
	val = clamp_val(val, 62, 16000) * 10;
	rate = 8 - __fls((val * 8 / (625 * 7)));
	वापस regmap_ग_लिखो(regmap, W83773_CONVERSION_RATE_REG_WRITE, rate);
पूर्ण

अटल पूर्णांक w83773_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		       u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा regmap *regmap = dev_get_drvdata(dev);

	अगर (type == hwmon_chip) अणु
		अगर (attr == hwmon_chip_update_पूर्णांकerval)
			वापस get_update_पूर्णांकerval(regmap, val);
		वापस -EOPNOTSUPP;
	पूर्ण

	चयन (attr) अणु
	हाल hwmon_temp_input:
		अगर (channel == 0)
			वापस get_local_temp(regmap, val);
		वापस get_remote_temp(regmap, channel - 1, val);
	हाल hwmon_temp_fault:
		वापस get_fault(regmap, channel - 1, val);
	हाल hwmon_temp_offset:
		वापस get_offset(regmap, channel - 1, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक w83773_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा regmap *regmap = dev_get_drvdata(dev);

	अगर (type == hwmon_chip && attr == hwmon_chip_update_पूर्णांकerval)
		वापस set_update_पूर्णांकerval(regmap, val);

	अगर (type == hwmon_temp && attr == hwmon_temp_offset)
		वापस set_offset(regmap, channel - 1, val);

	वापस -EOPNOTSUPP;
पूर्ण

अटल umode_t w83773_is_visible(स्थिर व्योम *data, क्रमागत hwmon_sensor_types type,
				 u32 attr, पूर्णांक channel)
अणु
	चयन (type) अणु
	हाल hwmon_chip:
		चयन (attr) अणु
		हाल hwmon_chip_update_पूर्णांकerval:
			वापस 0644;
		पूर्ण
		अवरोध;
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_input:
		हाल hwmon_temp_fault:
			वापस 0444;
		हाल hwmon_temp_offset:
			वापस 0644;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *w83773_info[] = अणु
	HWMON_CHANNEL_INFO(chip,
			   HWMON_C_REGISTER_TZ | HWMON_C_UPDATE_INTERVAL),
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT | HWMON_T_FAULT | HWMON_T_OFFSET,
			   HWMON_T_INPUT | HWMON_T_FAULT | HWMON_T_OFFSET),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops w83773_ops = अणु
	.is_visible = w83773_is_visible,
	.पढ़ो = w83773_पढ़ो,
	.ग_लिखो = w83773_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info w83773_chip_info = अणु
	.ops = &w83773_ops,
	.info = w83773_info,
पूर्ण;

अटल स्थिर काष्ठा regmap_config w83773_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल पूर्णांक w83773_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	regmap = devm_regmap_init_i2c(client, &w83773_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(dev, "failed to allocate register map\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	/* Set the conversion rate to 2 Hz */
	ret = regmap_ग_लिखो(regmap, W83773_CONVERSION_RATE_REG_WRITE, 0x05);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "error writing config rate register\n");
		वापस ret;
	पूर्ण

	i2c_set_clientdata(client, regmap);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev,
							 client->name,
							 regmap,
							 &w83773_chip_info,
							 शून्य);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल काष्ठा i2c_driver w83773_driver = अणु
	.class = I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "w83773g",
		.of_match_table = of_match_ptr(w83773_of_match),
	पूर्ण,
	.probe_new = w83773_probe,
	.id_table = w83773_id,
पूर्ण;

module_i2c_driver(w83773_driver);

MODULE_AUTHOR("Lei YU <mine260309@gmail.com>");
MODULE_DESCRIPTION("W83773G temperature sensor driver");
MODULE_LICENSE("GPL");
