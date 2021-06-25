<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tsys01.c - Support क्रम Measurement-Specialties tsys01 temperature sensor
 *
 * Copyright (c) 2015 Measurement-Specialties
 *
 * Datasheet:
 *  http://www.meas-spec.com/करोwnloads/TSYS01_Digital_Temperature_Sensor.pdf
 */

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/स्थिति.स>
#समावेश "../common/ms_sensors/ms_sensors_i2c.h"

/* TSYS01 Commands */
#घोषणा TSYS01_RESET				0x1E
#घोषणा TSYS01_CONVERSION_START			0x48
#घोषणा TSYS01_ADC_READ				0x00
#घोषणा TSYS01_PROM_READ			0xA0

#घोषणा TSYS01_PROM_WORDS_NB			8

काष्ठा tsys01_dev अणु
	व्योम *client;
	काष्ठा mutex lock; /* lock during conversion */

	पूर्णांक (*reset)(व्योम *cli, u8 cmd, अचिन्हित पूर्णांक delay);
	पूर्णांक (*convert_and_पढ़ो)(व्योम *cli, u8 conv, u8 rd,
				अचिन्हित पूर्णांक delay, u32 *adc);
	पूर्णांक (*पढ़ो_prom_word)(व्योम *cli, पूर्णांक cmd, u16 *word);

	u16 prom[TSYS01_PROM_WORDS_NB];
पूर्ण;

/* Multiplication coefficients क्रम temperature computation */
अटल स्थिर पूर्णांक coeff_mul[] = अणु -1500000, 1000000, -2000000,
				 4000000, -2000000 पूर्ण;

अटल पूर्णांक tsys01_पढ़ो_temperature(काष्ठा iio_dev *indio_dev,
				   s32 *temperature)
अणु
	पूर्णांक ret, i;
	u32 adc;
	s64 temp = 0;
	काष्ठा tsys01_dev *dev_data = iio_priv(indio_dev);

	mutex_lock(&dev_data->lock);
	ret = dev_data->convert_and_पढ़ो(dev_data->client,
					 TSYS01_CONVERSION_START,
					 TSYS01_ADC_READ, 9000, &adc);
	mutex_unlock(&dev_data->lock);
	अगर (ret)
		वापस ret;

	adc >>= 8;

	/* Temperature algorithm */
	क्रम (i = 4; i > 0; i--) अणु
		temp += coeff_mul[i] *
			(s64)dev_data->prom[5 - i];
		temp *= (s64)adc;
		temp = भाग64_s64(temp, 100000);
	पूर्ण
	temp *= 10;
	temp += coeff_mul[0] * (s64)dev_data->prom[5];
	temp = भाग64_s64(temp, 100000);

	*temperature = temp;

	वापस 0;
पूर्ण

अटल पूर्णांक tsys01_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *val,
			   पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	s32 temperature;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		चयन (channel->type) अणु
		हाल IIO_TEMP:	/* in milli तओC */
			ret = tsys01_पढ़ो_temperature(indio_dev, &temperature);
			अगर (ret)
				वापस ret;
			*val = temperature;

			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec tsys01_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_PROCESSED),
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा iio_info tsys01_info = अणु
	.पढ़ो_raw = tsys01_पढ़ो_raw,
पूर्ण;

अटल bool tsys01_crc_valid(u16 *n_prom)
अणु
	u8 cnt;
	u8 sum = 0;

	क्रम (cnt = 0; cnt < TSYS01_PROM_WORDS_NB; cnt++)
		sum += ((n_prom[0] >> 8) + (n_prom[0] & 0xFF));

	वापस (sum == 0);
पूर्ण

अटल पूर्णांक tsys01_पढ़ो_prom(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक i, ret;
	काष्ठा tsys01_dev *dev_data = iio_priv(indio_dev);
	अक्षर buf[7 * TSYS01_PROM_WORDS_NB + 1];
	अक्षर *ptr = buf;

	क्रम (i = 0; i < TSYS01_PROM_WORDS_NB; i++) अणु
		ret = dev_data->पढ़ो_prom_word(dev_data->client,
					       TSYS01_PROM_READ + (i << 1),
					       &dev_data->prom[i]);
		अगर (ret)
			वापस ret;

		ret = प्र_लिखो(ptr, "0x%04x ", dev_data->prom[i]);
		ptr += ret;
	पूर्ण

	अगर (!tsys01_crc_valid(dev_data->prom)) अणु
		dev_err(&indio_dev->dev, "prom crc check error\n");
		वापस -ENODEV;
	पूर्ण
	*ptr = 0;
	dev_info(&indio_dev->dev, "PROM coefficients : %s\n", buf);

	वापस 0;
पूर्ण

अटल पूर्णांक tsys01_probe(काष्ठा iio_dev *indio_dev, काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा tsys01_dev *dev_data = iio_priv(indio_dev);

	mutex_init(&dev_data->lock);

	indio_dev->info = &tsys01_info;
	indio_dev->name = dev->driver->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = tsys01_channels;
	indio_dev->num_channels = ARRAY_SIZE(tsys01_channels);

	ret = dev_data->reset(dev_data->client, TSYS01_RESET, 3000);
	अगर (ret)
		वापस ret;

	ret = tsys01_पढ़ो_prom(indio_dev);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल पूर्णांक tsys01_i2c_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा tsys01_dev *dev_data;
	काष्ठा iio_dev *indio_dev;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WORD_DATA |
				     I2C_FUNC_SMBUS_WRITE_BYTE |
				     I2C_FUNC_SMBUS_READ_I2C_BLOCK)) अणु
		dev_err(&client->dev,
			"Adapter does not support some i2c transaction\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*dev_data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	dev_data = iio_priv(indio_dev);
	dev_data->client = client;
	dev_data->reset = ms_sensors_reset;
	dev_data->पढ़ो_prom_word = ms_sensors_पढ़ो_prom_word;
	dev_data->convert_and_पढ़ो = ms_sensors_convert_and_पढ़ो;

	i2c_set_clientdata(client, indio_dev);

	वापस tsys01_probe(indio_dev, &client->dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tsys01_id[] = अणु
	अणु"tsys01", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, tsys01_id);

अटल स्थिर काष्ठा of_device_id tsys01_of_match[] = अणु
	अणु .compatible = "meas,tsys01", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, tsys01_of_match);

अटल काष्ठा i2c_driver tsys01_driver = अणु
	.probe = tsys01_i2c_probe,
	.id_table = tsys01_id,
	.driver = अणु
		   .name = "tsys01",
		   .of_match_table = tsys01_of_match,
		   पूर्ण,
पूर्ण;

module_i2c_driver(tsys01_driver);

MODULE_DESCRIPTION("Measurement-Specialties tsys01 temperature driver");
MODULE_AUTHOR("William Markezana <william.markezana@meas-spec.com>");
MODULE_AUTHOR("Ludovic Tancerel <ludovic.tancerel@maplehightech.com>");
MODULE_LICENSE("GPL v2");
