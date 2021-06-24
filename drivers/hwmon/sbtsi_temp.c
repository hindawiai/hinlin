<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * sbtsi_temp.c - hwmon driver क्रम a SBI Temperature Sensor Interface (SB-TSI)
 *                compliant AMD SoC temperature device.
 *
 * Copyright (c) 2020, Google Inc.
 * Copyright (c) 2020, Kun Yi <kunyi@google.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>

/*
 * SB-TSI रेजिस्टरs only support SMBus byte data access. "_INT" रेजिस्टरs are
 * the पूर्णांकeger part of a temperature value or limit, and "_DEC" रेजिस्टरs are
 * corresponding decimal parts.
 */
#घोषणा SBTSI_REG_TEMP_INT		0x01 /* RO */
#घोषणा SBTSI_REG_STATUS		0x02 /* RO */
#घोषणा SBTSI_REG_CONFIG		0x03 /* RO */
#घोषणा SBTSI_REG_TEMP_HIGH_INT		0x07 /* RW */
#घोषणा SBTSI_REG_TEMP_LOW_INT		0x08 /* RW */
#घोषणा SBTSI_REG_TEMP_DEC		0x10 /* RW */
#घोषणा SBTSI_REG_TEMP_HIGH_DEC		0x13 /* RW */
#घोषणा SBTSI_REG_TEMP_LOW_DEC		0x14 /* RW */

#घोषणा SBTSI_CONFIG_READ_ORDER_SHIFT	5

#घोषणा SBTSI_TEMP_MIN	0
#घोषणा SBTSI_TEMP_MAX	255875

/* Each client has this additional data */
काष्ठा sbtsi_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
पूर्ण;

/*
 * From SB-TSI spec: CPU temperature पढ़ोings and limit रेजिस्टरs encode the
 * temperature in increments of 0.125 from 0 to 255.875. The "high byte"
 * रेजिस्टर encodes the base-2 of the पूर्णांकeger portion, and the upper 3 bits of
 * the "low byte" encode in base-2 the decimal portion.
 *
 * e.g. INT=0x19, DEC=0x20 represents 25.125 degrees Celsius
 *
 * Thereक्रमe temperature in millidegree Celsius =
 *   (INT + DEC / 256) * 1000 = (INT * 8 + DEC / 32) * 125
 */
अटल अंतरभूत पूर्णांक sbtsi_reg_to_mc(s32 पूर्णांकeger, s32 decimal)
अणु
	वापस ((पूर्णांकeger << 3) + (decimal >> 5)) * 125;
पूर्ण

/*
 * Inversely, given temperature in millidegree Celsius
 *   INT = (TEMP / 125) / 8
 *   DEC = ((TEMP / 125) % 8) * 32
 * Caller have to make sure temp करोesn't exceed 255875, the max valid value.
 */
अटल अंतरभूत व्योम sbtsi_mc_to_reg(s32 temp, u8 *पूर्णांकeger, u8 *decimal)
अणु
	temp /= 125;
	*पूर्णांकeger = temp >> 3;
	*decimal = (temp & 0x7) << 5;
पूर्ण

अटल पूर्णांक sbtsi_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		      u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा sbtsi_data *data = dev_get_drvdata(dev);
	s32 temp_पूर्णांक, temp_dec;
	पूर्णांक err;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		/*
		 * ReadOrder bit specअगरies the पढ़ोing order of पूर्णांकeger and
		 * decimal part of CPU temp क्रम atomic पढ़ोs. If bit == 0,
		 * पढ़ोing पूर्णांकeger part triggers latching of the decimal part,
		 * so पूर्णांकeger part should be पढ़ो first. If bit == 1, पढ़ो
		 * order should be reversed.
		 */
		err = i2c_smbus_पढ़ो_byte_data(data->client, SBTSI_REG_CONFIG);
		अगर (err < 0)
			वापस err;

		mutex_lock(&data->lock);
		अगर (err & BIT(SBTSI_CONFIG_READ_ORDER_SHIFT)) अणु
			temp_dec = i2c_smbus_पढ़ो_byte_data(data->client, SBTSI_REG_TEMP_DEC);
			temp_पूर्णांक = i2c_smbus_पढ़ो_byte_data(data->client, SBTSI_REG_TEMP_INT);
		पूर्ण अन्यथा अणु
			temp_पूर्णांक = i2c_smbus_पढ़ो_byte_data(data->client, SBTSI_REG_TEMP_INT);
			temp_dec = i2c_smbus_पढ़ो_byte_data(data->client, SBTSI_REG_TEMP_DEC);
		पूर्ण
		mutex_unlock(&data->lock);
		अवरोध;
	हाल hwmon_temp_max:
		mutex_lock(&data->lock);
		temp_पूर्णांक = i2c_smbus_पढ़ो_byte_data(data->client, SBTSI_REG_TEMP_HIGH_INT);
		temp_dec = i2c_smbus_पढ़ो_byte_data(data->client, SBTSI_REG_TEMP_HIGH_DEC);
		mutex_unlock(&data->lock);
		अवरोध;
	हाल hwmon_temp_min:
		mutex_lock(&data->lock);
		temp_पूर्णांक = i2c_smbus_पढ़ो_byte_data(data->client, SBTSI_REG_TEMP_LOW_INT);
		temp_dec = i2c_smbus_पढ़ो_byte_data(data->client, SBTSI_REG_TEMP_LOW_DEC);
		mutex_unlock(&data->lock);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण


	अगर (temp_पूर्णांक < 0)
		वापस temp_पूर्णांक;
	अगर (temp_dec < 0)
		वापस temp_dec;

	*val = sbtsi_reg_to_mc(temp_पूर्णांक, temp_dec);

	वापस 0;
पूर्ण

अटल पूर्णांक sbtsi_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		       u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा sbtsi_data *data = dev_get_drvdata(dev);
	पूर्णांक reg_पूर्णांक, reg_dec, err;
	u8 temp_पूर्णांक, temp_dec;

	चयन (attr) अणु
	हाल hwmon_temp_max:
		reg_पूर्णांक = SBTSI_REG_TEMP_HIGH_INT;
		reg_dec = SBTSI_REG_TEMP_HIGH_DEC;
		अवरोध;
	हाल hwmon_temp_min:
		reg_पूर्णांक = SBTSI_REG_TEMP_LOW_INT;
		reg_dec = SBTSI_REG_TEMP_LOW_DEC;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	val = clamp_val(val, SBTSI_TEMP_MIN, SBTSI_TEMP_MAX);
	sbtsi_mc_to_reg(val, &temp_पूर्णांक, &temp_dec);

	mutex_lock(&data->lock);
	err = i2c_smbus_ग_लिखो_byte_data(data->client, reg_पूर्णांक, temp_पूर्णांक);
	अगर (err)
		जाओ निकास;

	err = i2c_smbus_ग_लिखो_byte_data(data->client, reg_dec, temp_dec);
निकास:
	mutex_unlock(&data->lock);
	वापस err;
पूर्ण

अटल umode_t sbtsi_is_visible(स्थिर व्योम *data,
				क्रमागत hwmon_sensor_types type,
				u32 attr, पूर्णांक channel)
अणु
	चयन (type) अणु
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_input:
			वापस 0444;
		हाल hwmon_temp_min:
			वापस 0644;
		हाल hwmon_temp_max:
			वापस 0644;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *sbtsi_info[] = अणु
	HWMON_CHANNEL_INFO(chip, HWMON_C_REGISTER_TZ),
	HWMON_CHANNEL_INFO(temp, HWMON_T_INPUT | HWMON_T_MIN | HWMON_T_MAX),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops sbtsi_hwmon_ops = अणु
	.is_visible = sbtsi_is_visible,
	.पढ़ो = sbtsi_पढ़ो,
	.ग_लिखो = sbtsi_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info sbtsi_chip_info = अणु
	.ops = &sbtsi_hwmon_ops,
	.info = sbtsi_info,
पूर्ण;

अटल पूर्णांक sbtsi_probe(काष्ठा i2c_client *client,
		       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा sbtsi_data *data;

	data = devm_kzalloc(dev, माप(काष्ठा sbtsi_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->lock);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, client->name, data, &sbtsi_chip_info,
							 शून्य);

	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id sbtsi_id[] = अणु
	अणु"sbtsi", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sbtsi_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused sbtsi_of_match[] = अणु
	अणु
		.compatible = "amd,sbtsi",
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sbtsi_of_match);

अटल काष्ठा i2c_driver sbtsi_driver = अणु
	.class = I2C_CLASS_HWMON,
	.driver = अणु
		.name = "sbtsi",
		.of_match_table = of_match_ptr(sbtsi_of_match),
	पूर्ण,
	.probe = sbtsi_probe,
	.id_table = sbtsi_id,
पूर्ण;

module_i2c_driver(sbtsi_driver);

MODULE_AUTHOR("Kun Yi <kunyi@google.com>");
MODULE_DESCRIPTION("Hwmon driver for AMD SB-TSI emulated sensor");
MODULE_LICENSE("GPL");
