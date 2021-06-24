<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * si7020.c - Silicon Lअसल Si7013/20/21 Relative Humidity and Temp Sensors
 * Copyright (c) 2013,2014  Uplogix, Inc.
 * David Barksdale <dbarksdale@uplogix.com>
 */

/*
 * The Silicon Lअसल Si7013/20/21 Relative Humidity and Temperature Sensors
 * are i2c devices which have an identical programming पूर्णांकerface क्रम
 * measuring relative humidity and temperature. The Si7013 has an additional
 * temperature input which this driver करोes not support.
 *
 * Data Sheets:
 *   Si7013: http://www.siद_असल.com/Support%20Documents/TechnicalDocs/Si7013.pdf
 *   Si7020: http://www.siद_असल.com/Support%20Documents/TechnicalDocs/Si7020.pdf
 *   Si7021: http://www.siद_असल.com/Support%20Documents/TechnicalDocs/Si7021.pdf
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

/* Measure Relative Humidity, Hold Master Mode */
#घोषणा SI7020CMD_RH_HOLD	0xE5
/* Measure Temperature, Hold Master Mode */
#घोषणा SI7020CMD_TEMP_HOLD	0xE3
/* Software Reset */
#घोषणा SI7020CMD_RESET		0xFE

अटल पूर्णांक si7020_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			   पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा i2c_client **client = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = i2c_smbus_पढ़ो_word_swapped(*client,
						  chan->type == IIO_TEMP ?
						  SI7020CMD_TEMP_HOLD :
						  SI7020CMD_RH_HOLD);
		अगर (ret < 0)
			वापस ret;
		*val = ret >> 2;
		/*
		 * Humidity values can slightly exceed the 0-100%RH
		 * range and should be corrected by software
		 */
		अगर (chan->type == IIO_HUMIDITYRELATIVE)
			*val = clamp_val(*val, 786, 13893);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (chan->type == IIO_TEMP)
			*val = 175720; /* = 175.72 * 1000 */
		अन्यथा
			*val = 125 * 1000;
		*val2 = 65536 >> 2;
		वापस IIO_VAL_FRACTIONAL;
	हाल IIO_CHAN_INFO_OFFSET:
		/*
		 * Since iio_convert_raw_to_processed_unlocked assumes offset
		 * is an पूर्णांकeger we have to round these values and lose
		 * accuracy.
		 * Relative humidity will be 0.0032959% too high and
		 * temperature will be 0.00277344 degrees too high.
		 * This is no big deal because it's within the accuracy of the
		 * sensor.
		 */
		अगर (chan->type == IIO_TEMP)
			*val = -4368; /* = -46.85 * (65536 >> 2) / 175.72 */
		अन्यथा
			*val = -786; /* = -6 * (65536 >> 2) / 125 */
		वापस IIO_VAL_INT;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec si7020_channels[] = अणु
	अणु
		.type = IIO_HUMIDITYRELATIVE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE) | BIT(IIO_CHAN_INFO_OFFSET),
	पूर्ण,
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE) | BIT(IIO_CHAN_INFO_OFFSET),
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा iio_info si7020_info = अणु
	.पढ़ो_raw = si7020_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक si7020_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा i2c_client **data;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WRITE_BYTE |
				     I2C_FUNC_SMBUS_READ_WORD_DATA))
		वापस -EOPNOTSUPP;

	/* Reset device, loads शेष settings. */
	ret = i2c_smbus_ग_लिखो_byte(client, SI7020CMD_RESET);
	अगर (ret < 0)
		वापस ret;
	/* Wait the maximum घातer-up समय after software reset. */
	msleep(15);

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	*data = client;

	indio_dev->name = dev_name(&client->dev);
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &si7020_info;
	indio_dev->channels = si7020_channels;
	indio_dev->num_channels = ARRAY_SIZE(si7020_channels);

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id si7020_id[] = अणु
	अणु "si7020", 0 पूर्ण,
	अणु "th06", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, si7020_id);

अटल स्थिर काष्ठा of_device_id si7020_dt_ids[] = अणु
	अणु .compatible = "silabs,si7020" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, si7020_dt_ids);

अटल काष्ठा i2c_driver si7020_driver = अणु
	.driver = अणु
		.name = "si7020",
		.of_match_table = si7020_dt_ids,
	पूर्ण,
	.probe		= si7020_probe,
	.id_table	= si7020_id,
पूर्ण;

module_i2c_driver(si7020_driver);
MODULE_DESCRIPTION("Silicon Labs Si7013/20/21 Relative Humidity and Temperature Sensors");
MODULE_AUTHOR("David Barksdale <dbarksdale@uplogix.com>");
MODULE_LICENSE("GPL");
