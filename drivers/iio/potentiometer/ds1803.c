<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Maxim Integrated DS1803 digital potentiometer driver
 * Copyright (c) 2016 Slawomir Stepien
 *
 * Datasheet: https://datasheets.maximपूर्णांकegrated.com/en/ds/DS1803.pdf
 *
 * DEVID	#Wipers	#Positions	Resistor Opts (kOhm)	i2c address
 * ds1803	2	256		10, 50, 100		0101xxx
 */

#समावेश <linux/err.h>
#समावेश <linux/export.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>

#घोषणा DS1803_MAX_POS		255
#घोषणा DS1803_WRITE(chan)	(0xa8 | ((chan) + 1))

क्रमागत ds1803_type अणु
	DS1803_010,
	DS1803_050,
	DS1803_100,
पूर्ण;

काष्ठा ds1803_cfg अणु
	पूर्णांक kohms;
पूर्ण;

अटल स्थिर काष्ठा ds1803_cfg ds1803_cfg[] = अणु
	[DS1803_010] = अणु .kohms =  10, पूर्ण,
	[DS1803_050] = अणु .kohms =  50, पूर्ण,
	[DS1803_100] = अणु .kohms = 100, पूर्ण,
पूर्ण;

काष्ठा ds1803_data अणु
	काष्ठा i2c_client *client;
	स्थिर काष्ठा ds1803_cfg *cfg;
पूर्ण;

#घोषणा DS1803_CHANNEL(ch) अणु					\
	.type = IIO_RESISTANCE,					\
	.indexed = 1,						\
	.output = 1,						\
	.channel = (ch),					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ds1803_channels[] = अणु
	DS1803_CHANNEL(0),
	DS1803_CHANNEL(1),
पूर्ण;

अटल पूर्णांक ds1803_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा ds1803_data *data = iio_priv(indio_dev);
	पूर्णांक pot = chan->channel;
	पूर्णांक ret;
	u8 result[ARRAY_SIZE(ds1803_channels)];

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = i2c_master_recv(data->client, result,
				indio_dev->num_channels);
		अगर (ret < 0)
			वापस ret;

		*val = result[pot];
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		*val = 1000 * data->cfg->kohms;
		*val2 = DS1803_MAX_POS;
		वापस IIO_VAL_FRACTIONAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ds1803_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा ds1803_data *data = iio_priv(indio_dev);
	पूर्णांक pot = chan->channel;

	अगर (val2 != 0)
		वापस -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (val > DS1803_MAX_POS || val < 0)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस i2c_smbus_ग_लिखो_byte_data(data->client, DS1803_WRITE(pot), val);
पूर्ण

अटल स्थिर काष्ठा iio_info ds1803_info = अणु
	.पढ़ो_raw = ds1803_पढ़ो_raw,
	.ग_लिखो_raw = ds1803_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक ds1803_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा ds1803_data *data;
	काष्ठा iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	i2c_set_clientdata(client, indio_dev);

	data = iio_priv(indio_dev);
	data->client = client;
	data->cfg = &ds1803_cfg[id->driver_data];

	indio_dev->info = &ds1803_info;
	indio_dev->channels = ds1803_channels;
	indio_dev->num_channels = ARRAY_SIZE(ds1803_channels);
	indio_dev->name = client->name;

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id ds1803_dt_ids[] = अणु
	अणु .compatible = "maxim,ds1803-010", .data = &ds1803_cfg[DS1803_010] पूर्ण,
	अणु .compatible = "maxim,ds1803-050", .data = &ds1803_cfg[DS1803_050] पूर्ण,
	अणु .compatible = "maxim,ds1803-100", .data = &ds1803_cfg[DS1803_100] पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ds1803_dt_ids);

अटल स्थिर काष्ठा i2c_device_id ds1803_id[] = अणु
	अणु "ds1803-010", DS1803_010 पूर्ण,
	अणु "ds1803-050", DS1803_050 पूर्ण,
	अणु "ds1803-100", DS1803_100 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ds1803_id);

अटल काष्ठा i2c_driver ds1803_driver = अणु
	.driver = अणु
		.name	= "ds1803",
		.of_match_table = ds1803_dt_ids,
	पूर्ण,
	.probe		= ds1803_probe,
	.id_table	= ds1803_id,
पूर्ण;

module_i2c_driver(ds1803_driver);

MODULE_AUTHOR("Slawomir Stepien <sst@poczta.fm>");
MODULE_DESCRIPTION("DS1803 digital potentiometer");
MODULE_LICENSE("GPL v2");
