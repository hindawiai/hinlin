<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* पंचांगp421.c
 *
 * Copyright (C) 2009 Andre Prendel <andre.prendel@gmx.de>
 * Preliminary support by:
 * Melvin Rook, Raymond Ng
 */

/*
 * Driver क्रम the Texas Instruments TMP421 SMBus temperature sensor IC.
 * Supported models: TMP421, TMP422, TMP423, TMP441, TMP442
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
#समावेश <linux/of_device.h>
#समावेश <linux/sysfs.h>

/* Addresses to scan */
अटल स्थिर अचिन्हित लघु normal_i2c[] = अणु 0x2a, 0x4c, 0x4d, 0x4e, 0x4f,
					     I2C_CLIENT_END पूर्ण;

क्रमागत chips अणु पंचांगp421, पंचांगp422, पंचांगp423, पंचांगp441, पंचांगp442 पूर्ण;

/* The TMP421 रेजिस्टरs */
#घोषणा TMP421_STATUS_REG			0x08
#घोषणा TMP421_CONFIG_REG_1			0x09
#घोषणा TMP421_CONVERSION_RATE_REG		0x0B
#घोषणा TMP421_MANUFACTURER_ID_REG		0xFE
#घोषणा TMP421_DEVICE_ID_REG			0xFF

अटल स्थिर u8 TMP421_TEMP_MSB[4]		= अणु 0x00, 0x01, 0x02, 0x03 पूर्ण;
अटल स्थिर u8 TMP421_TEMP_LSB[4]		= अणु 0x10, 0x11, 0x12, 0x13 पूर्ण;

/* Flags */
#घोषणा TMP421_CONFIG_SHUTDOWN			0x40
#घोषणा TMP421_CONFIG_RANGE			0x04

/* Manufacturer / Device ID's */
#घोषणा TMP421_MANUFACTURER_ID			0x55
#घोषणा TMP421_DEVICE_ID			0x21
#घोषणा TMP422_DEVICE_ID			0x22
#घोषणा TMP423_DEVICE_ID			0x23
#घोषणा TMP441_DEVICE_ID			0x41
#घोषणा TMP442_DEVICE_ID			0x42

अटल स्थिर काष्ठा i2c_device_id पंचांगp421_id[] = अणु
	अणु "tmp421", 2 पूर्ण,
	अणु "tmp422", 3 पूर्ण,
	अणु "tmp423", 4 पूर्ण,
	अणु "tmp441", 2 पूर्ण,
	अणु "tmp442", 3 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, पंचांगp421_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused पंचांगp421_of_match[] = अणु
	अणु
		.compatible = "ti,tmp421",
		.data = (व्योम *)2
	पूर्ण,
	अणु
		.compatible = "ti,tmp422",
		.data = (व्योम *)3
	पूर्ण,
	अणु
		.compatible = "ti,tmp423",
		.data = (व्योम *)4
	पूर्ण,
	अणु
		.compatible = "ti,tmp441",
		.data = (व्योम *)2
	पूर्ण,
	अणु
		.compatible = "ti,tmp442",
		.data = (व्योम *)3
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, पंचांगp421_of_match);

काष्ठा पंचांगp421_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex update_lock;
	u32 temp_config[5];
	काष्ठा hwmon_channel_info temp_info;
	स्थिर काष्ठा hwmon_channel_info *info[2];
	काष्ठा hwmon_chip_info chip;
	अक्षर valid;
	अचिन्हित दीर्घ last_updated;
	अचिन्हित दीर्घ channels;
	u8 config;
	s16 temp[4];
पूर्ण;

अटल पूर्णांक temp_from_s16(s16 reg)
अणु
	/* Mask out status bits */
	पूर्णांक temp = reg & ~0xf;

	वापस (temp * 1000 + 128) / 256;
पूर्ण

अटल पूर्णांक temp_from_u16(u16 reg)
अणु
	/* Mask out status bits */
	पूर्णांक temp = reg & ~0xf;

	/* Add offset क्रम extended temperature range. */
	temp -= 64 * 256;

	वापस (temp * 1000 + 128) / 256;
पूर्ण

अटल काष्ठा पंचांगp421_data *पंचांगp421_update_device(काष्ठा device *dev)
अणु
	काष्ठा पंचांगp421_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक i;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + (HZ / 2)) ||
	    !data->valid) अणु
		data->config = i2c_smbus_पढ़ो_byte_data(client,
			TMP421_CONFIG_REG_1);

		क्रम (i = 0; i < data->channels; i++) अणु
			data->temp[i] = i2c_smbus_पढ़ो_byte_data(client,
				TMP421_TEMP_MSB[i]) << 8;
			data->temp[i] |= i2c_smbus_पढ़ो_byte_data(client,
				TMP421_TEMP_LSB[i]);
		पूर्ण
		data->last_updated = jअगरfies;
		data->valid = 1;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

अटल पूर्णांक पंचांगp421_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		       u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा पंचांगp421_data *पंचांगp421 = पंचांगp421_update_device(dev);

	चयन (attr) अणु
	हाल hwmon_temp_input:
		अगर (पंचांगp421->config & TMP421_CONFIG_RANGE)
			*val = temp_from_u16(पंचांगp421->temp[channel]);
		अन्यथा
			*val = temp_from_s16(पंचांगp421->temp[channel]);
		वापस 0;
	हाल hwmon_temp_fault:
		/*
		 * The OPEN bit संकेतs a fault. This is bit 0 of the temperature
		 * रेजिस्टर (low byte).
		 */
		*val = पंचांगp421->temp[channel] & 0x01;
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

पूर्ण

अटल umode_t पंचांगp421_is_visible(स्थिर व्योम *data, क्रमागत hwmon_sensor_types type,
				 u32 attr, पूर्णांक channel)
अणु
	चयन (attr) अणु
	हाल hwmon_temp_fault:
		अगर (channel == 0)
			वापस 0;
		वापस 0444;
	हाल hwmon_temp_input:
		वापस 0444;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक पंचांगp421_init_client(काष्ठा i2c_client *client)
अणु
	पूर्णांक config, config_orig;

	/* Set the conversion rate to 2 Hz */
	i2c_smbus_ग_लिखो_byte_data(client, TMP421_CONVERSION_RATE_REG, 0x05);

	/* Start conversions (disable shutकरोwn अगर necessary) */
	config = i2c_smbus_पढ़ो_byte_data(client, TMP421_CONFIG_REG_1);
	अगर (config < 0) अणु
		dev_err(&client->dev,
			"Could not read configuration register (%d)\n", config);
		वापस config;
	पूर्ण

	config_orig = config;
	config &= ~TMP421_CONFIG_SHUTDOWN;

	अगर (config != config_orig) अणु
		dev_info(&client->dev, "Enable monitoring chip\n");
		i2c_smbus_ग_लिखो_byte_data(client, TMP421_CONFIG_REG_1, config);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पंचांगp421_detect(काष्ठा i2c_client *client,
			 काष्ठा i2c_board_info *info)
अणु
	क्रमागत chips kind;
	काष्ठा i2c_adapter *adapter = client->adapter;
	अटल स्थिर अक्षर * स्थिर names[] = अणु
		"TMP421", "TMP422", "TMP423",
		"TMP441", "TMP442"
	पूर्ण;
	पूर्णांक addr = client->addr;
	u8 reg;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	reg = i2c_smbus_पढ़ो_byte_data(client, TMP421_MANUFACTURER_ID_REG);
	अगर (reg != TMP421_MANUFACTURER_ID)
		वापस -ENODEV;

	reg = i2c_smbus_पढ़ो_byte_data(client, TMP421_CONVERSION_RATE_REG);
	अगर (reg & 0xf8)
		वापस -ENODEV;

	reg = i2c_smbus_पढ़ो_byte_data(client, TMP421_STATUS_REG);
	अगर (reg & 0x7f)
		वापस -ENODEV;

	reg = i2c_smbus_पढ़ो_byte_data(client, TMP421_DEVICE_ID_REG);
	चयन (reg) अणु
	हाल TMP421_DEVICE_ID:
		kind = पंचांगp421;
		अवरोध;
	हाल TMP422_DEVICE_ID:
		अगर (addr == 0x2a)
			वापस -ENODEV;
		kind = पंचांगp422;
		अवरोध;
	हाल TMP423_DEVICE_ID:
		अगर (addr != 0x4c && addr != 0x4d)
			वापस -ENODEV;
		kind = पंचांगp423;
		अवरोध;
	हाल TMP441_DEVICE_ID:
		kind = पंचांगp441;
		अवरोध;
	हाल TMP442_DEVICE_ID:
		अगर (addr != 0x4c && addr != 0x4d)
			वापस -ENODEV;
		kind = पंचांगp442;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	strlcpy(info->type, पंचांगp421_id[kind].name, I2C_NAME_SIZE);
	dev_info(&adapter->dev, "Detected TI %s chip at 0x%02x\n",
		 names[kind], client->addr);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_ops पंचांगp421_ops = अणु
	.is_visible = पंचांगp421_is_visible,
	.पढ़ो = पंचांगp421_पढ़ो,
पूर्ण;

अटल पूर्णांक पंचांगp421_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा पंचांगp421_data *data;
	पूर्णांक i, err;

	data = devm_kzalloc(dev, माप(काष्ठा पंचांगp421_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	mutex_init(&data->update_lock);
	अगर (client->dev.of_node)
		data->channels = (अचिन्हित दीर्घ)
			of_device_get_match_data(&client->dev);
	अन्यथा
		data->channels = i2c_match_id(पंचांगp421_id, client)->driver_data;
	data->client = client;

	err = पंचांगp421_init_client(client);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < data->channels; i++)
		data->temp_config[i] = HWMON_T_INPUT | HWMON_T_FAULT;

	data->chip.ops = &पंचांगp421_ops;
	data->chip.info = data->info;

	data->info[0] = &data->temp_info;

	data->temp_info.type = hwmon_temp;
	data->temp_info.config = data->temp_config;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, client->name,
							 data,
							 &data->chip,
							 शून्य);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल काष्ठा i2c_driver पंचांगp421_driver = अणु
	.class = I2C_CLASS_HWMON,
	.driver = अणु
		.name	= "tmp421",
		.of_match_table = of_match_ptr(पंचांगp421_of_match),
	पूर्ण,
	.probe_new = पंचांगp421_probe,
	.id_table = पंचांगp421_id,
	.detect = पंचांगp421_detect,
	.address_list = normal_i2c,
पूर्ण;

module_i2c_driver(पंचांगp421_driver);

MODULE_AUTHOR("Andre Prendel <andre.prendel@gmx.de>");
MODULE_DESCRIPTION("Texas Instruments TMP421/422/423/441/442 temperature sensor driver");
MODULE_LICENSE("GPL");
