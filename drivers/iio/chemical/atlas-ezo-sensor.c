<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * atlas-ezo-sensor.c - Support क्रम Atlas Scientअगरic EZO sensors
 *
 * Copyright (C) 2020 Konsulko Group
 * Author: Matt Ranostay <matt.ranostay@konsulko.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of_device.h>
#समावेश <linux/iio/iपन.स>

#घोषणा ATLAS_EZO_DRV_NAME		"atlas-ezo-sensor"
#घोषणा ATLAS_INT_TIME_IN_MS		950
#घोषणा ATLAS_INT_HUM_TIME_IN_MS	350

क्रमागत अणु
	ATLAS_CO2_EZO,
	ATLAS_O2_EZO,
	ATLAS_HUM_EZO,
पूर्ण;

काष्ठा atlas_ezo_device अणु
	स्थिर काष्ठा iio_chan_spec *channels;
	पूर्णांक num_channels;
	पूर्णांक delay;
पूर्ण;

काष्ठा atlas_ezo_data अणु
	काष्ठा i2c_client *client;
	काष्ठा atlas_ezo_device *chip;

	/* lock to aव्योम multiple concurrent पढ़ो calls */
	काष्ठा mutex lock;

	u8 buffer[8];
पूर्ण;

#घोषणा ATLAS_CONCENTRATION_CHANNEL(_modअगरier) \
	अणु \
		.type = IIO_CONCENTRATION, \
		.modअगरied = 1,\
		.channel2 = _modअगरier, \
		.info_mask_separate = \
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE), \
		.scan_index = 0, \
		.scan_type =  अणु \
			.sign = 'u', \
			.realbits = 32, \
			.storagebits = 32, \
			.endianness = IIO_CPU, \
		पूर्ण, \
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec atlas_co2_ezo_channels[] = अणु
	ATLAS_CONCENTRATION_CHANNEL(IIO_MOD_CO2),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec atlas_o2_ezo_channels[] = अणु
	ATLAS_CONCENTRATION_CHANNEL(IIO_MOD_O2),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec atlas_hum_ezo_channels[] = अणु
	अणु
		.type = IIO_HUMIDITYRELATIVE,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = 0,
		.scan_type =  अणु
			.sign = 'u',
			.realbits = 32,
			.storagebits = 32,
			.endianness = IIO_CPU,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा atlas_ezo_device atlas_ezo_devices[] = अणु
	[ATLAS_CO2_EZO] = अणु
		.channels = atlas_co2_ezo_channels,
		.num_channels = 1,
		.delay = ATLAS_INT_TIME_IN_MS,
	पूर्ण,
	[ATLAS_O2_EZO] = अणु
		.channels = atlas_o2_ezo_channels,
		.num_channels = 1,
		.delay = ATLAS_INT_TIME_IN_MS,
	पूर्ण,
	[ATLAS_HUM_EZO] = अणु
		.channels = atlas_hum_ezo_channels,
		.num_channels = 1,
		.delay = ATLAS_INT_HUM_TIME_IN_MS,
	पूर्ण,
पूर्ण;

अटल व्योम atlas_ezo_sanitize(अक्षर *buf)
अणु
	अक्षर *ptr = म_अक्षर(buf, '.');

	अगर (!ptr)
		वापस;

	स_हटाओ(ptr, ptr + 1, म_माप(ptr));
पूर्ण

अटल पूर्णांक atlas_ezo_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			  काष्ठा iio_chan_spec स्थिर *chan,
			  पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा atlas_ezo_data *data = iio_priv(indio_dev);
	काष्ठा i2c_client *client = data->client;

	अगर (chan->type != IIO_CONCENTRATION)
		वापस -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW: अणु
		पूर्णांक ret;
		दीर्घ पंचांगp;

		mutex_lock(&data->lock);

		पंचांगp = i2c_smbus_ग_लिखो_byte(client, 'R');

		अगर (पंचांगp < 0) अणु
			mutex_unlock(&data->lock);
			वापस पंचांगp;
		पूर्ण

		msleep(data->chip->delay);

		पंचांगp = i2c_master_recv(client, data->buffer, माप(data->buffer));

		अगर (पंचांगp < 0 || data->buffer[0] != 1) अणु
			mutex_unlock(&data->lock);
			वापस -EBUSY;
		पूर्ण

		/* removing भग्नing poपूर्णांक क्रम fixed number representation */
		atlas_ezo_sanitize(data->buffer + 2);

		ret = kम_से_दीर्घ(data->buffer + 1, 10, &पंचांगp);

		*val = पंचांगp;

		mutex_unlock(&data->lock);

		वापस ret ? ret : IIO_VAL_INT;
	पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_HUMIDITYRELATIVE:
			*val = 10;
			वापस IIO_VAL_INT;
		हाल IIO_CONCENTRATION:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		/* IIO_CONCENTRATION modअगरiers */
		चयन (chan->channel2) अणु
		हाल IIO_MOD_CO2:
			*val = 0;
			*val2 = 100; /* 0.0001 */
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_MOD_O2:
			*val = 100;
			वापस IIO_VAL_INT;
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_info atlas_info = अणु
	.पढ़ो_raw = atlas_ezo_पढ़ो_raw,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id atlas_ezo_id[] = अणु
	अणु "atlas-co2-ezo", ATLAS_CO2_EZO पूर्ण,
	अणु "atlas-o2-ezo", ATLAS_O2_EZO पूर्ण,
	अणु "atlas-hum-ezo", ATLAS_HUM_EZO पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, atlas_ezo_id);

अटल स्थिर काष्ठा of_device_id atlas_ezo_dt_ids[] = अणु
	अणु .compatible = "atlas,co2-ezo", .data = (व्योम *)ATLAS_CO2_EZO, पूर्ण,
	अणु .compatible = "atlas,o2-ezo", .data = (व्योम *)ATLAS_O2_EZO, पूर्ण,
	अणु .compatible = "atlas,hum-ezo", .data = (व्योम *)ATLAS_HUM_EZO, पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, atlas_ezo_dt_ids);

अटल पूर्णांक atlas_ezo_probe(काष्ठा i2c_client *client,
		       स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा atlas_ezo_data *data;
	काष्ठा atlas_ezo_device *chip;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	of_id = of_match_device(atlas_ezo_dt_ids, &client->dev);
	अगर (!of_id)
		chip = &atlas_ezo_devices[id->driver_data];
	अन्यथा
		chip = &atlas_ezo_devices[(अचिन्हित दीर्घ)of_id->data];

	indio_dev->info = &atlas_info;
	indio_dev->name = ATLAS_EZO_DRV_NAME;
	indio_dev->channels = chip->channels;
	indio_dev->num_channels = chip->num_channels;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	data = iio_priv(indio_dev);
	data->client = client;
	data->chip = chip;
	mutex_init(&data->lock);

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण;

अटल काष्ठा i2c_driver atlas_ezo_driver = अणु
	.driver = अणु
		.name	= ATLAS_EZO_DRV_NAME,
		.of_match_table	= atlas_ezo_dt_ids,
	पूर्ण,
	.probe		= atlas_ezo_probe,
	.id_table	= atlas_ezo_id,
पूर्ण;
module_i2c_driver(atlas_ezo_driver);

MODULE_AUTHOR("Matt Ranostay <matt.ranostay@konsulko.com>");
MODULE_DESCRIPTION("Atlas Scientific EZO sensors");
MODULE_LICENSE("GPL");
