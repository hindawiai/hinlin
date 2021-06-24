<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Sensirion SHT3x-DIS humidity and temperature sensor driver.
 * The SHT3x comes in many dअगरferent versions, this driver is क्रम the
 * I2C version only.
 *
 * Copyright (C) 2016 Sensirion AG, Switzerland
 * Author: David Frey <david.frey@sensirion.com>
 * Author: Pascal Sachs <pascal.sachs@sensirion.com>
 */

#समावेश <यंत्र/page.h>
#समावेश <linux/crc8.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/platक्रमm_data/sht3x.h>

/* commands (high precision mode) */
अटल स्थिर अचिन्हित अक्षर sht3x_cmd_measure_blocking_hpm[]    = अणु 0x2c, 0x06 पूर्ण;
अटल स्थिर अचिन्हित अक्षर sht3x_cmd_measure_nonblocking_hpm[] = अणु 0x24, 0x00 पूर्ण;

/* commands (low घातer mode) */
अटल स्थिर अचिन्हित अक्षर sht3x_cmd_measure_blocking_lpm[]    = अणु 0x2c, 0x10 पूर्ण;
अटल स्थिर अचिन्हित अक्षर sht3x_cmd_measure_nonblocking_lpm[] = अणु 0x24, 0x16 पूर्ण;

/* commands क्रम periodic mode */
अटल स्थिर अचिन्हित अक्षर sht3x_cmd_measure_periodic_mode[]   = अणु 0xe0, 0x00 पूर्ण;
अटल स्थिर अचिन्हित अक्षर sht3x_cmd_अवरोध[]                   = अणु 0x30, 0x93 पूर्ण;

/* commands क्रम heater control */
अटल स्थिर अचिन्हित अक्षर sht3x_cmd_heater_on[]               = अणु 0x30, 0x6d पूर्ण;
अटल स्थिर अचिन्हित अक्षर sht3x_cmd_heater_off[]              = अणु 0x30, 0x66 पूर्ण;

/* other commands */
अटल स्थिर अचिन्हित अक्षर sht3x_cmd_पढ़ो_status_reg[]         = अणु 0xf3, 0x2d पूर्ण;
अटल स्थिर अचिन्हित अक्षर sht3x_cmd_clear_status_reg[]        = अणु 0x30, 0x41 पूर्ण;

/* delays क्रम non-blocking i2c commands, both in us */
#घोषणा SHT3X_NONBLOCKING_WAIT_TIME_HPM  15000
#घोषणा SHT3X_NONBLOCKING_WAIT_TIME_LPM   4000

#घोषणा SHT3X_WORD_LEN         2
#घोषणा SHT3X_CMD_LENGTH       2
#घोषणा SHT3X_CRC8_LEN         1
#घोषणा SHT3X_RESPONSE_LENGTH  6
#घोषणा SHT3X_CRC8_POLYNOMIAL  0x31
#घोषणा SHT3X_CRC8_INIT        0xFF
#घोषणा SHT3X_MIN_TEMPERATURE  -45000
#घोषणा SHT3X_MAX_TEMPERATURE  130000
#घोषणा SHT3X_MIN_HUMIDITY     0
#घोषणा SHT3X_MAX_HUMIDITY     100000

क्रमागत sht3x_chips अणु
	sht3x,
	sts3x,
पूर्ण;

क्रमागत sht3x_limits अणु
	limit_max = 0,
	limit_max_hyst,
	limit_min,
	limit_min_hyst,
पूर्ण;

DECLARE_CRC8_TABLE(sht3x_crc8_table);

/* periodic measure commands (high precision mode) */
अटल स्थिर अक्षर periodic_measure_commands_hpm[][SHT3X_CMD_LENGTH] = अणु
	/* 0.5 measurements per second */
	अणु0x20, 0x32पूर्ण,
	/* 1 measurements per second */
	अणु0x21, 0x30पूर्ण,
	/* 2 measurements per second */
	अणु0x22, 0x36पूर्ण,
	/* 4 measurements per second */
	अणु0x23, 0x34पूर्ण,
	/* 10 measurements per second */
	अणु0x27, 0x37पूर्ण,
पूर्ण;

/* periodic measure commands (low घातer mode) */
अटल स्थिर अक्षर periodic_measure_commands_lpm[][SHT3X_CMD_LENGTH] = अणु
	/* 0.5 measurements per second */
	अणु0x20, 0x2fपूर्ण,
	/* 1 measurements per second */
	अणु0x21, 0x2dपूर्ण,
	/* 2 measurements per second */
	अणु0x22, 0x2bपूर्ण,
	/* 4 measurements per second */
	अणु0x23, 0x29पूर्ण,
	/* 10 measurements per second */
	अणु0x27, 0x2aपूर्ण,
पूर्ण;

काष्ठा sht3x_limit_commands अणु
	स्थिर अक्षर पढ़ो_command[SHT3X_CMD_LENGTH];
	स्थिर अक्षर ग_लिखो_command[SHT3X_CMD_LENGTH];
पूर्ण;

अटल स्थिर काष्ठा sht3x_limit_commands limit_commands[] = अणु
	/* temp1_max, humidity1_max */
	[limit_max] = अणु अणु0xe1, 0x1fपूर्ण, अणु0x61, 0x1dपूर्ण पूर्ण,
	/* temp_1_max_hyst, humidity1_max_hyst */
	[limit_max_hyst] = अणु अणु0xe1, 0x14पूर्ण, अणु0x61, 0x16पूर्ण पूर्ण,
	/* temp1_min, humidity1_min */
	[limit_min] = अणु अणु0xe1, 0x02पूर्ण, अणु0x61, 0x00पूर्ण पूर्ण,
	/* temp_1_min_hyst, humidity1_min_hyst */
	[limit_min_hyst] = अणु अणु0xe1, 0x09पूर्ण, अणु0x61, 0x0Bपूर्ण पूर्ण,
पूर्ण;

#घोषणा SHT3X_NUM_LIMIT_CMD  ARRAY_SIZE(limit_commands)

अटल स्थिर u16 mode_to_update_पूर्णांकerval[] = अणु
	   0,
	2000,
	1000,
	 500,
	 250,
	 100,
पूर्ण;

काष्ठा sht3x_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex i2c_lock; /* lock क्रम sending i2c commands */
	काष्ठा mutex data_lock; /* lock क्रम updating driver data */

	u8 mode;
	स्थिर अचिन्हित अक्षर *command;
	u32 रुको_समय;			/* in us*/
	अचिन्हित दीर्घ last_update;	/* last update in periodic mode*/

	काष्ठा sht3x_platक्रमm_data setup;

	/*
	 * cached values क्रम temperature and humidity and limits
	 * the limits arrays have the following order:
	 * max, max_hyst, min, min_hyst
	 */
	पूर्णांक temperature;
	पूर्णांक temperature_limits[SHT3X_NUM_LIMIT_CMD];
	u32 humidity;
	u32 humidity_limits[SHT3X_NUM_LIMIT_CMD];
पूर्ण;

अटल u8 get_mode_from_update_पूर्णांकerval(u16 value)
अणु
	माप_प्रकार index;
	u8 number_of_modes = ARRAY_SIZE(mode_to_update_पूर्णांकerval);

	अगर (value == 0)
		वापस 0;

	/* find next faster update पूर्णांकerval */
	क्रम (index = 1; index < number_of_modes; index++) अणु
		अगर (mode_to_update_पूर्णांकerval[index] <= value)
			वापस index;
	पूर्ण

	वापस number_of_modes - 1;
पूर्ण

अटल पूर्णांक sht3x_पढ़ो_from_command(काष्ठा i2c_client *client,
				   काष्ठा sht3x_data *data,
				   स्थिर अक्षर *command,
				   अक्षर *buf, पूर्णांक length, u32 रुको_समय)
अणु
	पूर्णांक ret;

	mutex_lock(&data->i2c_lock);
	ret = i2c_master_send(client, command, SHT3X_CMD_LENGTH);

	अगर (ret != SHT3X_CMD_LENGTH) अणु
		ret = ret < 0 ? ret : -EIO;
		जाओ out;
	पूर्ण

	अगर (रुको_समय)
		usleep_range(रुको_समय, रुको_समय + 1000);

	ret = i2c_master_recv(client, buf, length);
	अगर (ret != length) अणु
		ret = ret < 0 ? ret : -EIO;
		जाओ out;
	पूर्ण

	ret = 0;
out:
	mutex_unlock(&data->i2c_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक sht3x_extract_temperature(u16 raw)
अणु
	/*
	 * From datasheet:
	 * T = -45 + 175 * ST / 2^16
	 * Adapted क्रम पूर्णांकeger fixed poपूर्णांक (3 digit) arithmetic.
	 */
	वापस ((21875 * (पूर्णांक)raw) >> 13) - 45000;
पूर्ण

अटल u32 sht3x_extract_humidity(u16 raw)
अणु
	/*
	 * From datasheet:
	 * RH = 100 * SRH / 2^16
	 * Adapted क्रम पूर्णांकeger fixed poपूर्णांक (3 digit) arithmetic.
	 */
	वापस (12500 * (u32)raw) >> 13;
पूर्ण

अटल काष्ठा sht3x_data *sht3x_update_client(काष्ठा device *dev)
अणु
	काष्ठा sht3x_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u16 पूर्णांकerval_ms = mode_to_update_पूर्णांकerval[data->mode];
	अचिन्हित दीर्घ पूर्णांकerval_jअगरfies = msecs_to_jअगरfies(पूर्णांकerval_ms);
	अचिन्हित अक्षर buf[SHT3X_RESPONSE_LENGTH];
	u16 val;
	पूर्णांक ret = 0;

	mutex_lock(&data->data_lock);
	/*
	 * Only update cached पढ़ोings once per update पूर्णांकerval in periodic
	 * mode. In single shot mode the sensor measures values on demand, so
	 * every समय the sysfs पूर्णांकerface is called, a measurement is triggered.
	 * In periodic mode however, the measurement process is handled
	 * पूर्णांकernally by the sensor and पढ़ोing out sensor values only makes
	 * sense अगर a new पढ़ोing is available.
	 */
	अगर (समय_after(jअगरfies, data->last_update + पूर्णांकerval_jअगरfies)) अणु
		ret = sht3x_पढ़ो_from_command(client, data, data->command, buf,
					      माप(buf), data->रुको_समय);
		अगर (ret)
			जाओ out;

		val = be16_to_cpup((__be16 *)buf);
		data->temperature = sht3x_extract_temperature(val);
		val = be16_to_cpup((__be16 *)(buf + 3));
		data->humidity = sht3x_extract_humidity(val);
		data->last_update = jअगरfies;
	पूर्ण

out:
	mutex_unlock(&data->data_lock);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस data;
पूर्ण

/* sysfs attributes */
अटल sमाप_प्रकार temp1_input_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sht3x_data *data = sht3x_update_client(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%d\n", data->temperature);
पूर्ण

अटल sमाप_प्रकार humidity1_input_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा sht3x_data *data = sht3x_update_client(dev);

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	वापस प्र_लिखो(buf, "%u\n", data->humidity);
पूर्ण

/*
 * limits_update must only be called from probe or with data_lock held
 */
अटल पूर्णांक limits_update(काष्ठा sht3x_data *data)
अणु
	पूर्णांक ret;
	u8 index;
	पूर्णांक temperature;
	u32 humidity;
	u16 raw;
	अक्षर buffer[SHT3X_RESPONSE_LENGTH];
	स्थिर काष्ठा sht3x_limit_commands *commands;
	काष्ठा i2c_client *client = data->client;

	क्रम (index = 0; index < SHT3X_NUM_LIMIT_CMD; index++) अणु
		commands = &limit_commands[index];
		ret = sht3x_पढ़ो_from_command(client, data,
					      commands->पढ़ो_command, buffer,
					      SHT3X_RESPONSE_LENGTH, 0);

		अगर (ret)
			वापस ret;

		raw = be16_to_cpup((__be16 *)buffer);
		temperature = sht3x_extract_temperature((raw & 0x01ff) << 7);
		humidity = sht3x_extract_humidity(raw & 0xfe00);
		data->temperature_limits[index] = temperature;
		data->humidity_limits[index] = humidity;
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार temp1_limit_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा sht3x_data *data = dev_get_drvdata(dev);
	u8 index = to_sensor_dev_attr(attr)->index;
	पूर्णांक temperature_limit = data->temperature_limits[index];

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", temperature_limit);
पूर्ण

अटल sमाप_प्रकार humidity1_limit_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा sht3x_data *data = dev_get_drvdata(dev);
	u8 index = to_sensor_dev_attr(attr)->index;
	u32 humidity_limit = data->humidity_limits[index];

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n", humidity_limit);
पूर्ण

/*
 * limit_store must only be called with data_lock held
 */
अटल माप_प्रकार limit_store(काष्ठा device *dev,
			  माप_प्रकार count,
			  u8 index,
			  पूर्णांक temperature,
			  u32 humidity)
अणु
	अक्षर buffer[SHT3X_CMD_LENGTH + SHT3X_WORD_LEN + SHT3X_CRC8_LEN];
	अक्षर *position = buffer;
	पूर्णांक ret;
	u16 raw;
	काष्ठा sht3x_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	स्थिर काष्ठा sht3x_limit_commands *commands;

	commands = &limit_commands[index];

	स_नकल(position, commands->ग_लिखो_command, SHT3X_CMD_LENGTH);
	position += SHT3X_CMD_LENGTH;
	/*
	 * ST = (T + 45) / 175 * 2^16
	 * SRH = RH / 100 * 2^16
	 * adapted क्रम fixed poपूर्णांक arithmetic and packed the same as
	 * in limit_show()
	 */
	raw = ((u32)(temperature + 45000) * 24543) >> (16 + 7);
	raw |= ((humidity * 42950) >> 16) & 0xfe00;

	*((__be16 *)position) = cpu_to_be16(raw);
	position += SHT3X_WORD_LEN;
	*position = crc8(sht3x_crc8_table,
			 position - SHT3X_WORD_LEN,
			 SHT3X_WORD_LEN,
			 SHT3X_CRC8_INIT);

	mutex_lock(&data->i2c_lock);
	ret = i2c_master_send(client, buffer, माप(buffer));
	mutex_unlock(&data->i2c_lock);

	अगर (ret != माप(buffer))
		वापस ret < 0 ? ret : -EIO;

	data->temperature_limits[index] = temperature;
	data->humidity_limits[index] = humidity;
	वापस count;
पूर्ण

अटल sमाप_प्रकार temp1_limit_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf,
				 माप_प्रकार count)
अणु
	पूर्णांक temperature;
	पूर्णांक ret;
	काष्ठा sht3x_data *data = dev_get_drvdata(dev);
	u8 index = to_sensor_dev_attr(attr)->index;

	ret = kstrtoपूर्णांक(buf, 0, &temperature);
	अगर (ret)
		वापस ret;

	temperature = clamp_val(temperature, SHT3X_MIN_TEMPERATURE,
				SHT3X_MAX_TEMPERATURE);
	mutex_lock(&data->data_lock);
	ret = limit_store(dev, count, index, temperature,
			  data->humidity_limits[index]);
	mutex_unlock(&data->data_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार humidity1_limit_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf,
				     माप_प्रकार count)
अणु
	u32 humidity;
	पूर्णांक ret;
	काष्ठा sht3x_data *data = dev_get_drvdata(dev);
	u8 index = to_sensor_dev_attr(attr)->index;

	ret = kstrtou32(buf, 0, &humidity);
	अगर (ret)
		वापस ret;

	humidity = clamp_val(humidity, SHT3X_MIN_HUMIDITY, SHT3X_MAX_HUMIDITY);
	mutex_lock(&data->data_lock);
	ret = limit_store(dev, count, index, data->temperature_limits[index],
			  humidity);
	mutex_unlock(&data->data_lock);

	वापस ret;
पूर्ण

अटल व्योम sht3x_select_command(काष्ठा sht3x_data *data)
अणु
	/*
	 * In blocking mode (घड़ी stretching mode) the I2C bus
	 * is blocked क्रम other traffic, thus the call to i2c_master_recv()
	 * will रुको until the data is पढ़ोy. For non blocking mode, we
	 * have to रुको ourselves.
	 */
	अगर (data->mode > 0) अणु
		data->command = sht3x_cmd_measure_periodic_mode;
		data->रुको_समय = 0;
	पूर्ण अन्यथा अगर (data->setup.blocking_io) अणु
		data->command = data->setup.high_precision ?
				sht3x_cmd_measure_blocking_hpm :
				sht3x_cmd_measure_blocking_lpm;
		data->रुको_समय = 0;
	पूर्ण अन्यथा अणु
		अगर (data->setup.high_precision) अणु
			data->command = sht3x_cmd_measure_nonblocking_hpm;
			data->रुको_समय = SHT3X_NONBLOCKING_WAIT_TIME_HPM;
		पूर्ण अन्यथा अणु
			data->command = sht3x_cmd_measure_nonblocking_lpm;
			data->रुको_समय = SHT3X_NONBLOCKING_WAIT_TIME_LPM;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक status_रेजिस्टर_पढ़ो(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buffer, पूर्णांक length)
अणु
	पूर्णांक ret;
	काष्ठा sht3x_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;

	ret = sht3x_पढ़ो_from_command(client, data, sht3x_cmd_पढ़ो_status_reg,
				      buffer, length, 0);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार temp1_alarm_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	अक्षर buffer[SHT3X_WORD_LEN + SHT3X_CRC8_LEN];
	पूर्णांक ret;

	ret = status_रेजिस्टर_पढ़ो(dev, attr, buffer,
				   SHT3X_WORD_LEN + SHT3X_CRC8_LEN);
	अगर (ret)
		वापस ret;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", !!(buffer[0] & 0x04));
पूर्ण

अटल sमाप_प्रकार humidity1_alarm_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	अक्षर buffer[SHT3X_WORD_LEN + SHT3X_CRC8_LEN];
	पूर्णांक ret;

	ret = status_रेजिस्टर_पढ़ो(dev, attr, buffer,
				   SHT3X_WORD_LEN + SHT3X_CRC8_LEN);
	अगर (ret)
		वापस ret;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", !!(buffer[0] & 0x08));
पूर्ण

अटल sमाप_प्रकार heater_enable_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	अक्षर buffer[SHT3X_WORD_LEN + SHT3X_CRC8_LEN];
	पूर्णांक ret;

	ret = status_रेजिस्टर_पढ़ो(dev, attr, buffer,
				   SHT3X_WORD_LEN + SHT3X_CRC8_LEN);
	अगर (ret)
		वापस ret;

	वापस scnम_लिखो(buf, PAGE_SIZE, "%d\n", !!(buffer[0] & 0x20));
पूर्ण

अटल sमाप_प्रकार heater_enable_store(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   स्थिर अक्षर *buf,
				   माप_प्रकार count)
अणु
	काष्ठा sht3x_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret;
	bool status;

	ret = kstrtobool(buf, &status);
	अगर (ret)
		वापस ret;

	mutex_lock(&data->i2c_lock);

	अगर (status)
		ret = i2c_master_send(client, (अक्षर *)&sht3x_cmd_heater_on,
				      SHT3X_CMD_LENGTH);
	अन्यथा
		ret = i2c_master_send(client, (अक्षर *)&sht3x_cmd_heater_off,
				      SHT3X_CMD_LENGTH);

	mutex_unlock(&data->i2c_lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार update_पूर्णांकerval_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा sht3x_data *data = dev_get_drvdata(dev);

	वापस scnम_लिखो(buf, PAGE_SIZE, "%u\n",
			 mode_to_update_पूर्णांकerval[data->mode]);
पूर्ण

अटल sमाप_प्रकार update_पूर्णांकerval_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf,
				     माप_प्रकार count)
अणु
	u16 update_पूर्णांकerval;
	u8 mode;
	पूर्णांक ret;
	स्थिर अक्षर *command;
	काष्ठा sht3x_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;

	ret = kstrtou16(buf, 0, &update_पूर्णांकerval);
	अगर (ret)
		वापस ret;

	mode = get_mode_from_update_पूर्णांकerval(update_पूर्णांकerval);

	mutex_lock(&data->data_lock);
	/* mode did not change */
	अगर (mode == data->mode) अणु
		mutex_unlock(&data->data_lock);
		वापस count;
	पूर्ण

	mutex_lock(&data->i2c_lock);
	/*
	 * Abort periodic measure mode.
	 * To करो any changes to the configuration जबतक in periodic mode, we
	 * have to send a अवरोध command to the sensor, which then falls back
	 * to single shot (mode = 0).
	 */
	अगर (data->mode > 0) अणु
		ret = i2c_master_send(client, sht3x_cmd_अवरोध,
				      SHT3X_CMD_LENGTH);
		अगर (ret != SHT3X_CMD_LENGTH)
			जाओ out;
		data->mode = 0;
	पूर्ण

	अगर (mode > 0) अणु
		अगर (data->setup.high_precision)
			command = periodic_measure_commands_hpm[mode - 1];
		अन्यथा
			command = periodic_measure_commands_lpm[mode - 1];

		/* select mode */
		ret = i2c_master_send(client, command, SHT3X_CMD_LENGTH);
		अगर (ret != SHT3X_CMD_LENGTH)
			जाओ out;
	पूर्ण

	/* select mode and command */
	data->mode = mode;
	sht3x_select_command(data);

out:
	mutex_unlock(&data->i2c_lock);
	mutex_unlock(&data->data_lock);
	अगर (ret != SHT3X_CMD_LENGTH)
		वापस ret < 0 ? ret : -EIO;

	वापस count;
पूर्ण

अटल SENSOR_DEVICE_ATTR_RO(temp1_input, temp1_input, 0);
अटल SENSOR_DEVICE_ATTR_RO(humidity1_input, humidity1_input, 0);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max, temp1_limit, limit_max);
अटल SENSOR_DEVICE_ATTR_RW(humidity1_max, humidity1_limit, limit_max);
अटल SENSOR_DEVICE_ATTR_RW(temp1_max_hyst, temp1_limit, limit_max_hyst);
अटल SENSOR_DEVICE_ATTR_RW(humidity1_max_hyst, humidity1_limit,
			     limit_max_hyst);
अटल SENSOR_DEVICE_ATTR_RW(temp1_min, temp1_limit, limit_min);
अटल SENSOR_DEVICE_ATTR_RW(humidity1_min, humidity1_limit, limit_min);
अटल SENSOR_DEVICE_ATTR_RW(temp1_min_hyst, temp1_limit, limit_min_hyst);
अटल SENSOR_DEVICE_ATTR_RW(humidity1_min_hyst, humidity1_limit,
			     limit_min_hyst);
अटल SENSOR_DEVICE_ATTR_RO(temp1_alarm, temp1_alarm, 0);
अटल SENSOR_DEVICE_ATTR_RO(humidity1_alarm, humidity1_alarm, 0);
अटल SENSOR_DEVICE_ATTR_RW(heater_enable, heater_enable, 0);
अटल SENSOR_DEVICE_ATTR_RW(update_पूर्णांकerval, update_पूर्णांकerval, 0);

अटल काष्ठा attribute *sht3x_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	&sensor_dev_attr_humidity1_input.dev_attr.attr,
	&sensor_dev_attr_temp1_max.dev_attr.attr,
	&sensor_dev_attr_temp1_max_hyst.dev_attr.attr,
	&sensor_dev_attr_humidity1_max.dev_attr.attr,
	&sensor_dev_attr_humidity1_max_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_min.dev_attr.attr,
	&sensor_dev_attr_temp1_min_hyst.dev_attr.attr,
	&sensor_dev_attr_humidity1_min.dev_attr.attr,
	&sensor_dev_attr_humidity1_min_hyst.dev_attr.attr,
	&sensor_dev_attr_temp1_alarm.dev_attr.attr,
	&sensor_dev_attr_humidity1_alarm.dev_attr.attr,
	&sensor_dev_attr_heater_enable.dev_attr.attr,
	&sensor_dev_attr_update_पूर्णांकerval.dev_attr.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute *sts3x_attrs[] = अणु
	&sensor_dev_attr_temp1_input.dev_attr.attr,
	शून्य
पूर्ण;

ATTRIBUTE_GROUPS(sht3x);
ATTRIBUTE_GROUPS(sts3x);

अटल स्थिर काष्ठा i2c_device_id sht3x_ids[];

अटल पूर्णांक sht3x_probe(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;
	काष्ठा sht3x_data *data;
	काष्ठा device *hwmon_dev;
	काष्ठा i2c_adapter *adap = client->adapter;
	काष्ठा device *dev = &client->dev;
	स्थिर काष्ठा attribute_group **attribute_groups;

	/*
	 * we require full i2c support since the sht3x uses multi-byte पढ़ो and
	 * ग_लिखोs as well as multi-byte commands which are not supported by
	 * the smbus protocol
	 */
	अगर (!i2c_check_functionality(adap, I2C_FUNC_I2C))
		वापस -ENODEV;

	ret = i2c_master_send(client, sht3x_cmd_clear_status_reg,
			      SHT3X_CMD_LENGTH);
	अगर (ret != SHT3X_CMD_LENGTH)
		वापस ret < 0 ? ret : -ENODEV;

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->setup.blocking_io = false;
	data->setup.high_precision = true;
	data->mode = 0;
	data->last_update = jअगरfies - msecs_to_jअगरfies(3000);
	data->client = client;
	crc8_populate_msb(sht3x_crc8_table, SHT3X_CRC8_POLYNOMIAL);

	अगर (client->dev.platक्रमm_data)
		data->setup = *(काष्ठा sht3x_platक्रमm_data *)dev->platक्रमm_data;

	sht3x_select_command(data);

	mutex_init(&data->i2c_lock);
	mutex_init(&data->data_lock);

	/*
	 * An attempt to पढ़ो limits रेजिस्टर too early
	 * causes a NACK response from the chip.
	 * Waiting क्रम an empirical delay of 500 us solves the issue.
	 */
	usleep_range(500, 600);

	ret = limits_update(data);
	अगर (ret)
		वापस ret;

	अगर (i2c_match_id(sht3x_ids, client)->driver_data == sts3x)
		attribute_groups = sts3x_groups;
	अन्यथा
		attribute_groups = sht3x_groups;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_groups(dev,
							   client->name,
							   data,
							   attribute_groups);

	अगर (IS_ERR(hwmon_dev))
		dev_dbg(dev, "unable to register hwmon device\n");

	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

/* device ID table */
अटल स्थिर काष्ठा i2c_device_id sht3x_ids[] = अणु
	अणु"sht3x", sht3xपूर्ण,
	अणु"sts3x", sts3xपूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, sht3x_ids);

अटल काष्ठा i2c_driver sht3x_i2c_driver = अणु
	.driver.name = "sht3x",
	.probe_new   = sht3x_probe,
	.id_table    = sht3x_ids,
पूर्ण;

module_i2c_driver(sht3x_i2c_driver);

MODULE_AUTHOR("David Frey <david.frey@sensirion.com>");
MODULE_AUTHOR("Pascal Sachs <pascal.sachs@sensirion.com>");
MODULE_DESCRIPTION("Sensirion SHT3x humidity and temperature sensor driver");
MODULE_LICENSE("GPL");
