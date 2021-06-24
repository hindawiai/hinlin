<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Measurements Specialties driver common i2c functions
 *
 * Copyright (c) 2015 Measurement-Specialties
 */

#समावेश <linux/module.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>

#समावेश "ms_sensors_i2c.h"

/* Conversion बार in us */
अटल स्थिर u16 ms_sensors_ht_t_conversion_समय[] = अणु 50000, 25000,
						       13000, 7000 पूर्ण;
अटल स्थिर u16 ms_sensors_ht_h_conversion_समय[] = अणु 16000, 3000,
						       5000, 8000 पूर्ण;
अटल स्थिर u16 ms_sensors_tp_conversion_समय[] = अणु 500, 1100, 2100,
						     4100, 8220, 16440 पूर्ण;

#घोषणा MS_SENSORS_SERIAL_READ_MSB		0xFA0F
#घोषणा MS_SENSORS_SERIAL_READ_LSB		0xFCC9
#घोषणा MS_SENSORS_CONFIG_REG_WRITE		0xE6
#घोषणा MS_SENSORS_CONFIG_REG_READ		0xE7
#घोषणा MS_SENSORS_HT_T_CONVERSION_START	0xF3
#घोषणा MS_SENSORS_HT_H_CONVERSION_START	0xF5

#घोषणा MS_SENSORS_TP_PROM_READ			0xA0
#घोषणा MS_SENSORS_TP_T_CONVERSION_START	0x50
#घोषणा MS_SENSORS_TP_P_CONVERSION_START	0x40
#घोषणा MS_SENSORS_TP_ADC_READ			0x00

#घोषणा MS_SENSORS_NO_READ_CMD			0xFF

/**
 * ms_sensors_reset() - Reset function
 * @cli:	poपूर्णांकer to device client
 * @cmd:	reset cmd. Depends on device in use
 * @delay:	usleep minimal delay after reset command is issued
 *
 * Generic I2C reset function क्रम Measurement Specialties devices.
 *
 * Return: 0 on success, negative त्रुटि_सं otherwise.
 */
पूर्णांक ms_sensors_reset(व्योम *cli, u8 cmd, अचिन्हित पूर्णांक delay)
अणु
	पूर्णांक ret;
	काष्ठा i2c_client *client = cli;

	ret = i2c_smbus_ग_लिखो_byte(client, cmd);
	अगर (ret) अणु
		dev_err(&client->dev, "Failed to reset device\n");
		वापस ret;
	पूर्ण
	usleep_range(delay, delay + 1000);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ms_sensors_reset);

/**
 * ms_sensors_पढ़ो_prom_word() - PROM word पढ़ो function
 * @cli:	poपूर्णांकer to device client
 * @cmd:	PROM पढ़ो cmd. Depends on device and prom id
 * @word:	poपूर्णांकer to word destination value
 *
 * Generic i2c prom word पढ़ो function क्रम Measurement Specialties devices.
 *
 * Return: 0 on success, negative त्रुटि_सं otherwise.
 */
पूर्णांक ms_sensors_पढ़ो_prom_word(व्योम *cli, पूर्णांक cmd, u16 *word)
अणु
	पूर्णांक ret;
	काष्ठा i2c_client *client = cli;

	ret = i2c_smbus_पढ़ो_word_swapped(client, cmd);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to read prom word\n");
		वापस ret;
	पूर्ण
	*word = ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ms_sensors_पढ़ो_prom_word);

/**
 * ms_sensors_convert_and_पढ़ो() - ADC conversion & पढ़ो function
 * @cli:	poपूर्णांकer to device client
 * @conv:	ADC conversion command. Depends on device in use
 * @rd:		ADC पढ़ो command. Depends on device in use
 * @delay:	usleep minimal delay after conversion command is issued
 * @adc:	poपूर्णांकer to ADC destination value
 *
 * Generic ADC conversion & पढ़ो function क्रम Measurement Specialties
 * devices.
 * The function will issue conversion command, sleep appopriate delay, and
 * issue command to पढ़ो ADC.
 *
 * Return: 0 on success, negative त्रुटि_सं otherwise.
 */
पूर्णांक ms_sensors_convert_and_पढ़ो(व्योम *cli, u8 conv, u8 rd,
				अचिन्हित पूर्णांक delay, u32 *adc)
अणु
	पूर्णांक ret;
	__be32 buf = 0;
	काष्ठा i2c_client *client = cli;

	/* Trigger conversion */
	ret = i2c_smbus_ग_लिखो_byte(client, conv);
	अगर (ret)
		जाओ err;
	usleep_range(delay, delay + 1000);

	/* Retrieve ADC value */
	अगर (rd != MS_SENSORS_NO_READ_CMD)
		ret = i2c_smbus_पढ़ो_i2c_block_data(client, rd, 3, (u8 *)&buf);
	अन्यथा
		ret = i2c_master_recv(client, (u8 *)&buf, 3);
	अगर (ret < 0)
		जाओ err;

	dev_dbg(&client->dev, "ADC raw value : %x\n", be32_to_cpu(buf) >> 8);
	*adc = be32_to_cpu(buf) >> 8;

	वापस 0;
err:
	dev_err(&client->dev, "Unable to make sensor adc conversion\n");
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ms_sensors_convert_and_पढ़ो);

/**
 * ms_sensors_crc_valid() - CRC check function
 * @value:	input and CRC compare value
 *
 * Cyclic Redundancy Check function used in TSYS02D, HTU21, MS8607.
 * This function perक्रमms a x^8 + x^5 + x^4 + 1 polynomial CRC.
 * The argument contains CRC value in LSB byte जबतक the bytes 1 and 2
 * are used क्रम CRC computation.
 *
 * Return: 1 अगर CRC is valid, 0 otherwise.
 */
अटल bool ms_sensors_crc_valid(u32 value)
अणु
	u32 polynom = 0x988000;	/* x^8 + x^5 + x^4 + 1 */
	u32 msb = 0x800000;
	u32 mask = 0xFF8000;
	u32 result = value & 0xFFFF00;
	u8 crc = value & 0xFF;

	जबतक (msb != 0x80) अणु
		अगर (result & msb)
			result = ((result ^ polynom) & mask)
				| (result & ~mask);
		msb >>= 1;
		mask >>= 1;
		polynom >>= 1;
	पूर्ण

	वापस result == crc;
पूर्ण

/**
 * ms_sensors_पढ़ो_serial() - Serial number पढ़ो function
 * @client:	poपूर्णांकer to i2c client
 * @sn:		poपूर्णांकer to 64-bits destination value
 *
 * Generic i2c serial number पढ़ो function क्रम Measurement Specialties devices.
 * This function is used क्रम TSYS02d, HTU21, MS8607 chipset.
 * Refer to datasheet:
 *	http://www.meas-spec.com/करोwnloads/HTU2X_Serial_Number_Reading.pdf
 *
 * Sensor raw MSB serial number क्रमmat is the following :
 *	[ SNB3, CRC, SNB2, CRC, SNB1, CRC, SNB0, CRC]
 * Sensor raw LSB serial number क्रमmat is the following :
 *	[ X, X, SNC1, SNC0, CRC, SNA1, SNA0, CRC]
 * The resulting serial number is following :
 *	[ SNA1, SNA0, SNB3, SNB2, SNB1, SNB0, SNC1, SNC0]
 *
 * Return: 0 on success, negative त्रुटि_सं otherwise.
 */
पूर्णांक ms_sensors_पढ़ो_serial(काष्ठा i2c_client *client, u64 *sn)
अणु
	u8 i;
	__be64 rcv_buf = 0;
	u64 rcv_val;
	__be16 send_buf;
	पूर्णांक ret;

	काष्ठा i2c_msg msg[2] = अणु
		अणु
		 .addr = client->addr,
		 .flags = client->flags,
		 .len = 2,
		 .buf = (__u8 *)&send_buf,
		 पूर्ण,
		अणु
		 .addr = client->addr,
		 .flags = client->flags | I2C_M_RD,
		 .buf = (__u8 *)&rcv_buf,
		 पूर्ण,
	पूर्ण;

	/* Read MSB part of serial number */
	send_buf = cpu_to_be16(MS_SENSORS_SERIAL_READ_MSB);
	msg[1].len = 8;
	ret = i2c_transfer(client->adapter, msg, 2);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Unable to read device serial number");
		वापस ret;
	पूर्ण

	rcv_val = be64_to_cpu(rcv_buf);
	dev_dbg(&client->dev, "Serial MSB raw : %llx\n", rcv_val);

	क्रम (i = 0; i < 64; i += 16) अणु
		अगर (!ms_sensors_crc_valid((rcv_val >> i) & 0xFFFF))
			वापस -ENODEV;
	पूर्ण

	*sn = (((rcv_val >> 32) & 0xFF000000) |
	       ((rcv_val >> 24) & 0x00FF0000) |
	       ((rcv_val >> 16) & 0x0000FF00) |
	       ((rcv_val >> 8) & 0x000000FF)) << 16;

	/* Read LSB part of serial number */
	send_buf = cpu_to_be16(MS_SENSORS_SERIAL_READ_LSB);
	msg[1].len = 6;
	rcv_buf = 0;
	ret = i2c_transfer(client->adapter, msg, 2);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Unable to read device serial number");
		वापस ret;
	पूर्ण

	rcv_val = be64_to_cpu(rcv_buf) >> 16;
	dev_dbg(&client->dev, "Serial MSB raw : %llx\n", rcv_val);

	क्रम (i = 0; i < 48; i += 24) अणु
		अगर (!ms_sensors_crc_valid((rcv_val >> i) & 0xFFFFFF))
			वापस -ENODEV;
	पूर्ण

	*sn |= (rcv_val & 0xFFFF00) << 40 | (rcv_val >> 32);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ms_sensors_पढ़ो_serial);

अटल पूर्णांक ms_sensors_पढ़ो_config_reg(काष्ठा i2c_client *client,
				      u8 *config_reg)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte(client, MS_SENSORS_CONFIG_REG_READ);
	अगर (ret) अणु
		dev_err(&client->dev, "Unable to read config register");
		वापस ret;
	पूर्ण

	ret = i2c_master_recv(client, config_reg, 1);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Unable to read config register");
		वापस ret;
	पूर्ण
	dev_dbg(&client->dev, "Config register :%x\n", *config_reg);

	वापस 0;
पूर्ण

/**
 * ms_sensors_ग_लिखो_resolution() - Set resolution function
 * @dev_data:	poपूर्णांकer to temperature/humidity device data
 * @i:		resolution index to set
 *
 * This function will program the appropriate resolution based on the index
 * provided when user space will set samp_freq channel.
 * This function is used क्रम TSYS02D, HTU21 and MS8607 chipsets.
 *
 * Return: 0 on success, negative त्रुटि_सं otherwise.
 */
sमाप_प्रकार ms_sensors_ग_लिखो_resolution(काष्ठा ms_ht_dev *dev_data,
				    u8 i)
अणु
	u8 config_reg;
	पूर्णांक ret;

	ret = ms_sensors_पढ़ो_config_reg(dev_data->client, &config_reg);
	अगर (ret)
		वापस ret;

	config_reg &= 0x7E;
	config_reg |= ((i & 1) << 7) + ((i & 2) >> 1);

	वापस i2c_smbus_ग_लिखो_byte_data(dev_data->client,
					 MS_SENSORS_CONFIG_REG_WRITE,
					 config_reg);
पूर्ण
EXPORT_SYMBOL(ms_sensors_ग_लिखो_resolution);

/**
 * ms_sensors_show_battery_low() - Show device battery low indicator
 * @dev_data:	poपूर्णांकer to temperature/humidity device data
 * @buf:	poपूर्णांकer to अक्षर buffer to ग_लिखो result
 *
 * This function will पढ़ो battery indicator value in the device and
 * वापस 1 अगर the device voltage is below 2.25V.
 * This function is used क्रम TSYS02D, HTU21 and MS8607 chipsets.
 *
 * Return: length of प्र_लिखो on success, negative त्रुटि_सं otherwise.
 */
sमाप_प्रकार ms_sensors_show_battery_low(काष्ठा ms_ht_dev *dev_data,
				    अक्षर *buf)
अणु
	पूर्णांक ret;
	u8 config_reg;

	mutex_lock(&dev_data->lock);
	ret = ms_sensors_पढ़ो_config_reg(dev_data->client, &config_reg);
	mutex_unlock(&dev_data->lock);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", (config_reg & 0x40) >> 6);
पूर्ण
EXPORT_SYMBOL(ms_sensors_show_battery_low);

/**
 * ms_sensors_show_heater() - Show device heater
 * @dev_data:	poपूर्णांकer to temperature/humidity device data
 * @buf:	poपूर्णांकer to अक्षर buffer to ग_लिखो result
 *
 * This function will पढ़ो heater enable value in the device and
 * वापस 1 अगर the heater is enabled.
 * This function is used क्रम HTU21 and MS8607 chipsets.
 *
 * Return: length of प्र_लिखो on success, negative त्रुटि_सं otherwise.
 */
sमाप_प्रकार ms_sensors_show_heater(काष्ठा ms_ht_dev *dev_data,
			       अक्षर *buf)
अणु
	u8 config_reg;
	पूर्णांक ret;

	mutex_lock(&dev_data->lock);
	ret = ms_sensors_पढ़ो_config_reg(dev_data->client, &config_reg);
	mutex_unlock(&dev_data->lock);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", (config_reg & 0x4) >> 2);
पूर्ण
EXPORT_SYMBOL(ms_sensors_show_heater);

/**
 * ms_sensors_ग_लिखो_heater() - Write device heater
 * @dev_data:	poपूर्णांकer to temperature/humidity device data
 * @buf:	poपूर्णांकer to अक्षर buffer from user space
 * @len:	length of buf
 *
 * This function will ग_लिखो 1 or 0 value in the device
 * to enable or disable heater.
 * This function is used क्रम HTU21 and MS8607 chipsets.
 *
 * Return: length of buffer, negative त्रुटि_सं otherwise.
 */
sमाप_प्रकार ms_sensors_ग_लिखो_heater(काष्ठा ms_ht_dev *dev_data,
				स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	u8 val, config_reg;
	पूर्णांक ret;

	ret = kstrtou8(buf, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (val > 1)
		वापस -EINVAL;

	mutex_lock(&dev_data->lock);
	ret = ms_sensors_पढ़ो_config_reg(dev_data->client, &config_reg);
	अगर (ret) अणु
		mutex_unlock(&dev_data->lock);
		वापस ret;
	पूर्ण

	config_reg &= 0xFB;
	config_reg |= val << 2;

	ret = i2c_smbus_ग_लिखो_byte_data(dev_data->client,
					MS_SENSORS_CONFIG_REG_WRITE,
					config_reg);
	mutex_unlock(&dev_data->lock);
	अगर (ret) अणु
		dev_err(&dev_data->client->dev, "Unable to write config register\n");
		वापस ret;
	पूर्ण

	वापस len;
पूर्ण
EXPORT_SYMBOL(ms_sensors_ग_लिखो_heater);

/**
 * ms_sensors_ht_पढ़ो_temperature() - Read temperature
 * @dev_data:	poपूर्णांकer to temperature/humidity device data
 * @temperature:poपूर्णांकer to temperature destination value
 *
 * This function will get temperature ADC value from the device,
 * check the CRC and compute the temperature value.
 * This function is used क्रम TSYS02D, HTU21 and MS8607 chipsets.
 *
 * Return: 0 on success, negative त्रुटि_सं otherwise.
 */
पूर्णांक ms_sensors_ht_पढ़ो_temperature(काष्ठा ms_ht_dev *dev_data,
				   s32 *temperature)
अणु
	पूर्णांक ret;
	u32 adc;
	u16 delay;

	mutex_lock(&dev_data->lock);
	delay = ms_sensors_ht_t_conversion_समय[dev_data->res_index];
	ret = ms_sensors_convert_and_पढ़ो(dev_data->client,
					  MS_SENSORS_HT_T_CONVERSION_START,
					  MS_SENSORS_NO_READ_CMD,
					  delay, &adc);
	mutex_unlock(&dev_data->lock);
	अगर (ret)
		वापस ret;

	अगर (!ms_sensors_crc_valid(adc)) अणु
		dev_err(&dev_data->client->dev,
			"Temperature read crc check error\n");
		वापस -ENODEV;
	पूर्ण

	/* Temperature algorithm */
	*temperature = (((s64)(adc >> 8) * 175720) >> 16) - 46850;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ms_sensors_ht_पढ़ो_temperature);

/**
 * ms_sensors_ht_पढ़ो_humidity() - Read humidity
 * @dev_data:	poपूर्णांकer to temperature/humidity device data
 * @humidity:	poपूर्णांकer to humidity destination value
 *
 * This function will get humidity ADC value from the device,
 * check the CRC and compute the temperature value.
 * This function is used क्रम HTU21 and MS8607 chipsets.
 *
 * Return: 0 on success, negative त्रुटि_सं otherwise.
 */
पूर्णांक ms_sensors_ht_पढ़ो_humidity(काष्ठा ms_ht_dev *dev_data,
				u32 *humidity)
अणु
	पूर्णांक ret;
	u32 adc;
	u16 delay;

	mutex_lock(&dev_data->lock);
	delay = ms_sensors_ht_h_conversion_समय[dev_data->res_index];
	ret = ms_sensors_convert_and_पढ़ो(dev_data->client,
					  MS_SENSORS_HT_H_CONVERSION_START,
					  MS_SENSORS_NO_READ_CMD,
					  delay, &adc);
	mutex_unlock(&dev_data->lock);
	अगर (ret)
		वापस ret;

	अगर (!ms_sensors_crc_valid(adc)) अणु
		dev_err(&dev_data->client->dev,
			"Humidity read crc check error\n");
		वापस -ENODEV;
	पूर्ण

	/* Humidity algorithm */
	*humidity = (((s32)(adc >> 8) * 12500) >> 16) * 10 - 6000;
	अगर (*humidity >= 100000)
		*humidity = 100000;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ms_sensors_ht_पढ़ो_humidity);

/**
 * ms_sensors_tp_crc4() - Calculate PROM CRC क्रम
 *     Temperature and pressure devices.
 *     This function is only used when पढ़ोing PROM coefficients
 *
 * @prom:	poपूर्णांकer to PROM coefficients array
 *
 * Return: CRC.
 */
अटल u8 ms_sensors_tp_crc4(u16 *prom)
अणु
	अचिन्हित पूर्णांक cnt, n_bit;
	u16 n_rem = 0x0000;

	क्रम (cnt = 0; cnt < MS_SENSORS_TP_PROM_WORDS_NB * 2; cnt++) अणु
		अगर (cnt % 2 == 1)
			n_rem ^= prom[cnt >> 1] & 0x00FF;
		अन्यथा
			n_rem ^= prom[cnt >> 1] >> 8;

		क्रम (n_bit = 8; n_bit > 0; n_bit--) अणु
			अगर (n_rem & 0x8000)
				n_rem = (n_rem << 1) ^ 0x3000;
			अन्यथा
				n_rem <<= 1;
		पूर्ण
	पूर्ण

	वापस n_rem >> 12;
पूर्ण

/**
 * ms_sensors_tp_crc_valid_112() - CRC check function क्रम
 *     Temperature and pressure devices क्रम 112bit PROM.
 *     This function is only used when पढ़ोing PROM coefficients
 *
 * @prom:	poपूर्णांकer to PROM coefficients array
 *
 * Return: True अगर CRC is ok.
 */
अटल bool ms_sensors_tp_crc_valid_112(u16 *prom)
अणु
	u16 w0 = prom[0], crc_पढ़ो = (w0 & 0xF000) >> 12;
	u8 crc;

	prom[0] &= 0x0FFF;      /* Clear the CRC computation part */
	prom[MS_SENSORS_TP_PROM_WORDS_NB - 1] = 0;

	crc = ms_sensors_tp_crc4(prom);

	prom[0] = w0;

	वापस crc == crc_पढ़ो;
पूर्ण

/**
 * ms_sensors_tp_crc_valid_128() - CRC check function क्रम
 *     Temperature and pressure devices क्रम 128bit PROM.
 *     This function is only used when पढ़ोing PROM coefficients
 *
 * @prom:	poपूर्णांकer to PROM coefficients array
 *
 * Return: True अगर CRC is ok.
 */
अटल bool ms_sensors_tp_crc_valid_128(u16 *prom)
अणु
	u16 w7 = prom[7], crc_पढ़ो = w7 & 0x000F;
	u8 crc;

	prom[7] &= 0xFF00;      /* Clear the CRC and LSB part */

	crc = ms_sensors_tp_crc4(prom);

	prom[7] = w7;

	वापस crc == crc_पढ़ो;
पूर्ण

/**
 * ms_sensors_tp_पढ़ो_prom() - prom coeff पढ़ो function
 * @dev_data:	poपूर्णांकer to temperature/pressure device data
 *
 * This function will पढ़ो prom coefficients and check CRC.
 * This function is used क्रम MS5637 and MS8607 chipsets.
 *
 * Return: 0 on success, negative त्रुटि_सं otherwise.
 */
पूर्णांक ms_sensors_tp_पढ़ो_prom(काष्ठा ms_tp_dev *dev_data)
अणु
	पूर्णांक i, ret;
	bool valid;

	क्रम (i = 0; i < dev_data->hw->prom_len; i++) अणु
		ret = ms_sensors_पढ़ो_prom_word(
			dev_data->client,
			MS_SENSORS_TP_PROM_READ + (i << 1),
			&dev_data->prom[i]);

		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (dev_data->hw->prom_len == 8)
		valid = ms_sensors_tp_crc_valid_128(dev_data->prom);
	अन्यथा
		valid = ms_sensors_tp_crc_valid_112(dev_data->prom);

	अगर (!valid) अणु
		dev_err(&dev_data->client->dev,
			"Calibration coefficients crc check error\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ms_sensors_tp_पढ़ो_prom);

/**
 * ms_sensors_पढ़ो_temp_and_pressure() - पढ़ो temp and pressure
 * @dev_data:	poपूर्णांकer to temperature/pressure device data
 * @temperature:poपूर्णांकer to temperature destination value
 * @pressure:	poपूर्णांकer to pressure destination value
 *
 * This function will पढ़ो ADC and compute pressure and temperature value.
 * This function is used क्रम MS5637 and MS8607 chipsets.
 *
 * Return: 0 on success, negative त्रुटि_सं otherwise.
 */
पूर्णांक ms_sensors_पढ़ो_temp_and_pressure(काष्ठा ms_tp_dev *dev_data,
				      पूर्णांक *temperature,
				      अचिन्हित पूर्णांक *pressure)
अणु
	पूर्णांक ret;
	u32 t_adc, p_adc;
	s32 dt, temp;
	s64 off, sens, t2, off2, sens2;
	u16 *prom = dev_data->prom, delay;

	mutex_lock(&dev_data->lock);
	delay = ms_sensors_tp_conversion_समय[dev_data->res_index];

	ret = ms_sensors_convert_and_पढ़ो(
					dev_data->client,
					MS_SENSORS_TP_T_CONVERSION_START +
						dev_data->res_index * 2,
					MS_SENSORS_TP_ADC_READ,
					delay, &t_adc);
	अगर (ret) अणु
		mutex_unlock(&dev_data->lock);
		वापस ret;
	पूर्ण

	ret = ms_sensors_convert_and_पढ़ो(
					dev_data->client,
					MS_SENSORS_TP_P_CONVERSION_START +
						dev_data->res_index * 2,
					MS_SENSORS_TP_ADC_READ,
					delay, &p_adc);
	mutex_unlock(&dev_data->lock);
	अगर (ret)
		वापस ret;

	dt = (s32)t_adc - (prom[5] << 8);

	/* Actual temperature = 2000 + dT * TEMPSENS */
	temp = 2000 + (((s64)dt * prom[6]) >> 23);

	/* Second order temperature compensation */
	अगर (temp < 2000) अणु
		s64 पंचांगp = (s64)temp - 2000;

		t2 = (3 * ((s64)dt * (s64)dt)) >> 33;
		off2 = (61 * पंचांगp * पंचांगp) >> 4;
		sens2 = (29 * पंचांगp * पंचांगp) >> 4;

		अगर (temp < -1500) अणु
			s64 पंचांगp = (s64)temp + 1500;

			off2 += 17 * पंचांगp * पंचांगp;
			sens2 += 9 * पंचांगp * पंचांगp;
		पूर्ण
	पूर्ण अन्यथा अणु
		t2 = (5 * ((s64)dt * (s64)dt)) >> 38;
		off2 = 0;
		sens2 = 0;
	पूर्ण

	/* OFF = OFF_T1 + TCO * dT */
	off = (((s64)prom[2]) << 17) + ((((s64)prom[4]) * (s64)dt) >> 6);
	off -= off2;

	/* Sensitivity at actual temperature = SENS_T1 + TCS * dT */
	sens = (((s64)prom[1]) << 16) + (((s64)prom[3] * dt) >> 7);
	sens -= sens2;

	/* Temperature compensated pressure = D1 * SENS - OFF */
	*temperature = (temp - t2) * 10;
	*pressure = (u32)(((((s64)p_adc * sens) >> 21) - off) >> 15);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ms_sensors_पढ़ो_temp_and_pressure);

MODULE_DESCRIPTION("Measurement-Specialties common i2c driver");
MODULE_AUTHOR("William Markezana <william.markezana@meas-spec.com>");
MODULE_AUTHOR("Ludovic Tancerel <ludovic.tancerel@maplehightech.com>");
MODULE_LICENSE("GPL v2");

