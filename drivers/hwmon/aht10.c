<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 * aht10.c - Linux hwmon driver क्रम AHT10 Temperature and Humidity sensor
 * Copyright (C) 2020 Johannes Cornelis Draaijer
 */

#समावेश <linux/delay.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/module.h>

#घोषणा AHT10_MEAS_SIZE		6

/*
 * Poll पूर्णांकervals (in milliseconds)
 */
#घोषणा AHT10_DEFAULT_MIN_POLL_INTERVAL	2000
#घोषणा AHT10_MIN_POLL_INTERVAL		2000

/*
 * I2C command delays (in microseconds)
 */
#घोषणा AHT10_MEAS_DELAY	80000
#घोषणा AHT10_CMD_DELAY		350000
#घोषणा AHT10_DELAY_EXTRA	100000

/*
 * Command bytes
 */
#घोषणा AHT10_CMD_INIT	0b11100001
#घोषणा AHT10_CMD_MEAS	0b10101100
#घोषणा AHT10_CMD_RST	0b10111010

/*
 * Flags in the answer byte/command
 */
#घोषणा AHT10_CAL_ENABLED	BIT(3)
#घोषणा AHT10_BUSY		BIT(7)
#घोषणा AHT10_MODE_NOR		(BIT(5) | BIT(6))
#घोषणा AHT10_MODE_CYC		BIT(5)
#घोषणा AHT10_MODE_CMD		BIT(6)

#घोषणा AHT10_MAX_POLL_INTERVAL_LEN	30

/**
 *   काष्ठा aht10_data - All the data required to operate an AHT10 chip
 *   @client: the i2c client associated with the AHT10
 *   @lock: a mutex that is used to prevent parallel access to the
 *          i2c client
 *   @min_poll_पूर्णांकerval: the minimum poll पूर्णांकerval
 *                   While the poll rate limit is not 100% necessary,
 *                   the datasheet recommends that a measurement
 *                   is not perक्रमmed too often to prevent
 *                   the chip from warming up due to the heat it generates.
 *                   If it's unwanted, it can be ignored setting it to
 *                   it to 0. Default value is 2000 ms
 *   @previous_poll_समय: the previous समय that the AHT10
 *                        was polled
 *   @temperature: the latest temperature value received from
 *                 the AHT10
 *   @humidity: the latest humidity value received from the
 *              AHT10
 */

काष्ठा aht10_data अणु
	काष्ठा i2c_client *client;
	/*
	 * Prevent simultaneous access to the i2c
	 * client and previous_poll_समय
	 */
	काष्ठा mutex lock;
	kसमय_प्रकार min_poll_पूर्णांकerval;
	kसमय_प्रकार previous_poll_समय;
	पूर्णांक temperature;
	पूर्णांक humidity;
पूर्ण;

/**
 * aht10_init() - Initialize an AHT10 chip
 * @client: the i2c client associated with the AHT10
 * @data: the data associated with this AHT10 chip
 * Return: 0 अगर succesfull, 1 अगर not
 */
अटल पूर्णांक aht10_init(काष्ठा aht10_data *data)
अणु
	स्थिर u8 cmd_init[] = अणुAHT10_CMD_INIT, AHT10_CAL_ENABLED | AHT10_MODE_CYC,
			       0x00पूर्ण;
	पूर्णांक res;
	u8 status;
	काष्ठा i2c_client *client = data->client;

	res = i2c_master_send(client, cmd_init, 3);
	अगर (res < 0)
		वापस res;

	usleep_range(AHT10_CMD_DELAY, AHT10_CMD_DELAY +
		     AHT10_DELAY_EXTRA);

	res = i2c_master_recv(client, &status, 1);
	अगर (res != 1)
		वापस -ENODATA;

	अगर (status & AHT10_BUSY)
		वापस -EBUSY;

	वापस 0;
पूर्ण

/**
 * aht10_pollसमय_expired() - check अगर the minimum poll पूर्णांकerval has
 *                                  expired
 * @data: the data containing the समय to compare
 * Return: 1 अगर the minimum poll पूर्णांकerval has expired, 0 अगर not
 */
अटल पूर्णांक aht10_pollसमय_expired(काष्ठा aht10_data *data)
अणु
	kसमय_प्रकार current_समय = kसमय_get_bootसमय();
	kसमय_प्रकार dअगरference = kसमय_sub(current_समय, data->previous_poll_समय);

	वापस kसमय_after(dअगरference, data->min_poll_पूर्णांकerval);
पूर्ण

/**
 * aht10_पढ़ो_values() - पढ़ो and parse the raw data from the AHT10
 * @aht10_data: the काष्ठा aht10_data to use क्रम the lock
 * Return: 0 अगर succesfull, 1 अगर not
 */
अटल पूर्णांक aht10_पढ़ो_values(काष्ठा aht10_data *data)
अणु
	स्थिर u8 cmd_meas[] = अणुAHT10_CMD_MEAS, 0x33, 0x00पूर्ण;
	u32 temp, hum;
	पूर्णांक res;
	u8 raw_data[AHT10_MEAS_SIZE];
	काष्ठा i2c_client *client = data->client;

	mutex_lock(&data->lock);
	अगर (aht10_pollसमय_expired(data)) अणु
		res = i2c_master_send(client, cmd_meas, माप(cmd_meas));
		अगर (res < 0) अणु
			mutex_unlock(&data->lock);
			वापस res;
		पूर्ण

		usleep_range(AHT10_MEAS_DELAY,
			     AHT10_MEAS_DELAY + AHT10_DELAY_EXTRA);

		res = i2c_master_recv(client, raw_data, AHT10_MEAS_SIZE);
		अगर (res != AHT10_MEAS_SIZE) अणु
			mutex_unlock(&data->lock);
			अगर (res >= 0)
				वापस -ENODATA;
			अन्यथा
				वापस res;
		पूर्ण

		hum =   ((u32)raw_data[1] << 12u) |
			((u32)raw_data[2] << 4u) |
			((raw_data[3] & 0xF0u) >> 4u);

		temp =  ((u32)(raw_data[3] & 0x0Fu) << 16u) |
			((u32)raw_data[4] << 8u) |
			raw_data[5];

		temp = ((temp * 625) >> 15u) * 10;
		hum = ((hum * 625) >> 16u) * 10;

		data->temperature = (पूर्णांक)temp - 50000;
		data->humidity = hum;
		data->previous_poll_समय = kसमय_get_bootसमय();
	पूर्ण
	mutex_unlock(&data->lock);
	वापस 0;
पूर्ण

/**
 * aht10_पूर्णांकerval_ग_लिखो() - store the given minimum poll पूर्णांकerval.
 * Return: 0 on success, -EINVAL अगर a value lower than the
 *         AHT10_MIN_POLL_INTERVAL is given
 */
अटल sमाप_प्रकार aht10_पूर्णांकerval_ग_लिखो(काष्ठा aht10_data *data,
				    दीर्घ val)
अणु
	data->min_poll_पूर्णांकerval = ms_to_kसमय(clamp_val(val, 2000, दीर्घ_उच्च));
	वापस 0;
पूर्ण

/**
 * aht10_पूर्णांकerval_पढ़ो() - पढ़ो the minimum poll पूर्णांकerval
 *                            in milliseconds
 */
अटल sमाप_प्रकार aht10_पूर्णांकerval_पढ़ो(काष्ठा aht10_data *data,
				   दीर्घ *val)
अणु
	*val = kसमय_प्रकारo_ms(data->min_poll_पूर्णांकerval);
	वापस 0;
पूर्ण

/**
 * aht10_temperature1_पढ़ो() - पढ़ो the temperature in millidegrees
 */
अटल पूर्णांक aht10_temperature1_पढ़ो(काष्ठा aht10_data *data, दीर्घ *val)
अणु
	पूर्णांक res;

	res = aht10_पढ़ो_values(data);
	अगर (res < 0)
		वापस res;

	*val = data->temperature;
	वापस 0;
पूर्ण

/**
 * aht10_humidity1_पढ़ो() - पढ़ो the relative humidity in millipercent
 */
अटल पूर्णांक aht10_humidity1_पढ़ो(काष्ठा aht10_data *data, दीर्घ *val)
अणु
	पूर्णांक res;

	res = aht10_पढ़ो_values(data);
	अगर (res < 0)
		वापस res;

	*val = data->humidity;
	वापस 0;
पूर्ण

अटल umode_t aht10_hwmon_visible(स्थिर व्योम *data, क्रमागत hwmon_sensor_types type,
				   u32 attr, पूर्णांक channel)
अणु
	चयन (type) अणु
	हाल hwmon_temp:
	हाल hwmon_humidity:
		वापस 0444;
	हाल hwmon_chip:
		वापस 0644;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक aht10_hwmon_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			    u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा aht10_data *data = dev_get_drvdata(dev);

	चयन (type) अणु
	हाल hwmon_temp:
		वापस aht10_temperature1_पढ़ो(data, val);
	हाल hwmon_humidity:
		वापस aht10_humidity1_पढ़ो(data, val);
	हाल hwmon_chip:
		वापस aht10_पूर्णांकerval_पढ़ो(data, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक aht10_hwmon_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			     u32 attr, पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा aht10_data *data = dev_get_drvdata(dev);

	चयन (type) अणु
	हाल hwmon_chip:
		वापस aht10_पूर्णांकerval_ग_लिखो(data, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *aht10_info[] = अणु
	HWMON_CHANNEL_INFO(chip, HWMON_C_UPDATE_INTERVAL),
	HWMON_CHANNEL_INFO(temp, HWMON_T_INPUT),
	HWMON_CHANNEL_INFO(humidity, HWMON_H_INPUT),
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops aht10_hwmon_ops = अणु
	.is_visible = aht10_hwmon_visible,
	.पढ़ो = aht10_hwmon_पढ़ो,
	.ग_लिखो = aht10_hwmon_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info aht10_chip_info = अणु
	.ops = &aht10_hwmon_ops,
	.info = aht10_info,
पूर्ण;

अटल पूर्णांक aht10_probe(काष्ठा i2c_client *client,
		       स्थिर काष्ठा i2c_device_id *aht10_id)
अणु
	काष्ठा device *device = &client->dev;
	काष्ठा device *hwmon_dev;
	काष्ठा aht10_data *data;
	पूर्णांक res;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C))
		वापस -ENOENT;

	data = devm_kzalloc(device, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->min_poll_पूर्णांकerval = ms_to_kसमय(AHT10_DEFAULT_MIN_POLL_INTERVAL);
	data->client = client;

	mutex_init(&data->lock);

	res = aht10_init(data);
	अगर (res < 0)
		वापस res;

	res = aht10_पढ़ो_values(data);
	अगर (res < 0)
		वापस res;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(device,
							 client->name,
							 data,
							 &aht10_chip_info,
							 शून्य);

	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id aht10_id[] = अणु
	अणु "aht10", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, aht10_id);

अटल काष्ठा i2c_driver aht10_driver = अणु
	.driver = अणु
		.name = "aht10",
	पूर्ण,
	.probe      = aht10_probe,
	.id_table   = aht10_id,
पूर्ण;

module_i2c_driver(aht10_driver);

MODULE_AUTHOR("Johannes Cornelis Draaijer <jcdra1@gmail.com>");
MODULE_DESCRIPTION("AHT10 Temperature and Humidity sensor driver");
MODULE_VERSION("1.0");
MODULE_LICENSE("GPL v2");
