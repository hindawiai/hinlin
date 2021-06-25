<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MS5611 pressure and temperature sensor driver (I2C bus)
 *
 * Copyright (c) Tomasz Duszynski <tduszyns@gmail.com>
 *
 * 7-bit I2C slave addresses:
 *
 * 0x77 (CSB pin low)
 * 0x76 (CSB pin high)
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>

#समावेश <यंत्र/unaligned.h>

#समावेश "ms5611.h"

अटल पूर्णांक ms5611_i2c_reset(काष्ठा device *dev)
अणु
	काष्ठा ms5611_state *st = iio_priv(dev_to_iio_dev(dev));

	वापस i2c_smbus_ग_लिखो_byte(st->client, MS5611_RESET);
पूर्ण

अटल पूर्णांक ms5611_i2c_पढ़ो_prom_word(काष्ठा device *dev, पूर्णांक index, u16 *word)
अणु
	पूर्णांक ret;
	काष्ठा ms5611_state *st = iio_priv(dev_to_iio_dev(dev));

	ret = i2c_smbus_पढ़ो_word_swapped(st->client,
			MS5611_READ_PROM_WORD + (index << 1));
	अगर (ret < 0)
		वापस ret;

	*word = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ms5611_i2c_पढ़ो_adc(काष्ठा ms5611_state *st, s32 *val)
अणु
	पूर्णांक ret;
	u8 buf[3];

	ret = i2c_smbus_पढ़ो_i2c_block_data(st->client, MS5611_READ_ADC,
					    3, buf);
	अगर (ret < 0)
		वापस ret;

	*val = get_unaligned_be24(&buf[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक ms5611_i2c_पढ़ो_adc_temp_and_pressure(काष्ठा device *dev,
						 s32 *temp, s32 *pressure)
अणु
	पूर्णांक ret;
	काष्ठा ms5611_state *st = iio_priv(dev_to_iio_dev(dev));
	स्थिर काष्ठा ms5611_osr *osr = st->temp_osr;

	ret = i2c_smbus_ग_लिखो_byte(st->client, osr->cmd);
	अगर (ret < 0)
		वापस ret;

	usleep_range(osr->conv_usec, osr->conv_usec + (osr->conv_usec / 10UL));
	ret = ms5611_i2c_पढ़ो_adc(st, temp);
	अगर (ret < 0)
		वापस ret;

	osr = st->pressure_osr;
	ret = i2c_smbus_ग_लिखो_byte(st->client, osr->cmd);
	अगर (ret < 0)
		वापस ret;

	usleep_range(osr->conv_usec, osr->conv_usec + (osr->conv_usec / 10UL));
	वापस ms5611_i2c_पढ़ो_adc(st, pressure);
पूर्ण

अटल पूर्णांक ms5611_i2c_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ms5611_state *st;
	काष्ठा iio_dev *indio_dev;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WRITE_BYTE |
				     I2C_FUNC_SMBUS_READ_WORD_DATA |
				     I2C_FUNC_SMBUS_READ_I2C_BLOCK))
		वापस -EOPNOTSUPP;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	st->reset = ms5611_i2c_reset;
	st->पढ़ो_prom_word = ms5611_i2c_पढ़ो_prom_word;
	st->पढ़ो_adc_temp_and_pressure = ms5611_i2c_पढ़ो_adc_temp_and_pressure;
	st->client = client;

	वापस ms5611_probe(indio_dev, &client->dev, id->name, id->driver_data);
पूर्ण

अटल पूर्णांक ms5611_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	वापस ms5611_हटाओ(i2c_get_clientdata(client));
पूर्ण

अटल स्थिर काष्ठा of_device_id ms5611_i2c_matches[] = अणु
	अणु .compatible = "meas,ms5611" पूर्ण,
	अणु .compatible = "meas,ms5607" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ms5611_i2c_matches);

अटल स्थिर काष्ठा i2c_device_id ms5611_id[] = अणु
	अणु "ms5611", MS5611 पूर्ण,
	अणु "ms5607", MS5607 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ms5611_id);

अटल काष्ठा i2c_driver ms5611_driver = अणु
	.driver = अणु
		.name = "ms5611",
		.of_match_table = ms5611_i2c_matches,
	पूर्ण,
	.id_table = ms5611_id,
	.probe = ms5611_i2c_probe,
	.हटाओ = ms5611_i2c_हटाओ,
पूर्ण;
module_i2c_driver(ms5611_driver);

MODULE_AUTHOR("Tomasz Duszynski <tduszyns@gmail.com>");
MODULE_DESCRIPTION("MS5611 i2c driver");
MODULE_LICENSE("GPL v2");
