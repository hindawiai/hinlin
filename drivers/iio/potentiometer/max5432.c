<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Maxim Integrated MAX5432-MAX5435 digital potentiometer driver
 * Copyright (C) 2019 Martin Kaiser <martin@kaiser.cx>
 *
 * Datasheet:
 * https://datasheets.maximपूर्णांकegrated.com/en/ds/MAX5432-MAX5435.pdf
 */

#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/सीमा.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/property.h>

/* All chip variants have 32 wiper positions. */
#घोषणा MAX5432_MAX_POS 31

#घोषणा MAX5432_OHM_50K   (50  * 1000)
#घोषणा MAX5432_OHM_100K  (100 * 1000)

/* Update the अस्थिर (currently active) setting. */
#घोषणा MAX5432_CMD_VREG  0x11

काष्ठा max5432_data अणु
	काष्ठा i2c_client *client;
	अचिन्हित दीर्घ ohm;
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec max5432_channels[] = अणु
	अणु
		.type = IIO_RESISTANCE,
		.indexed = 1,
		.output = 1,
		.channel = 0,
		.address = MAX5432_CMD_VREG,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण
पूर्ण;

अटल पूर्णांक max5432_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *chan,
			पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा max5432_data *data = iio_priv(indio_dev);

	अगर (mask != IIO_CHAN_INFO_SCALE)
		वापस -EINVAL;

	अगर (unlikely(data->ohm > पूर्णांक_उच्च))
		वापस -दुस्फल;

	*val = data->ohm;
	*val2 = MAX5432_MAX_POS;

	वापस IIO_VAL_FRACTIONAL;
पूर्ण

अटल पूर्णांक max5432_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *chan,
			पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा max5432_data *data = iio_priv(indio_dev);
	u8 data_byte;

	अगर (mask != IIO_CHAN_INFO_RAW)
		वापस -EINVAL;

	अगर (val < 0 || val > MAX5432_MAX_POS)
		वापस -EINVAL;

	अगर (val2 != 0)
		वापस -EINVAL;

	/* Wiper position is in bits D7-D3. (D2-D0 are करोn't care bits.) */
	data_byte = val << 3;
	वापस i2c_smbus_ग_लिखो_byte_data(data->client, chan->address,
			data_byte);
पूर्ण

अटल स्थिर काष्ठा iio_info max5432_info = अणु
	.पढ़ो_raw = max5432_पढ़ो_raw,
	.ग_लिखो_raw = max5432_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक max5432_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा iio_dev *indio_dev;
	काष्ठा max5432_data *data;

	indio_dev = devm_iio_device_alloc(dev, माप(काष्ठा max5432_data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	i2c_set_clientdata(client, indio_dev);

	data = iio_priv(indio_dev);
	data->client = client;
	data->ohm = (अचिन्हित दीर्घ)device_get_match_data(dev);

	indio_dev->info = &max5432_info;
	indio_dev->channels = max5432_channels;
	indio_dev->num_channels = ARRAY_SIZE(max5432_channels);
	indio_dev->name = client->name;

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id max5432_dt_ids[] = अणु
	अणु .compatible = "maxim,max5432", .data = (व्योम *)MAX5432_OHM_50K  पूर्ण,
	अणु .compatible = "maxim,max5433", .data = (व्योम *)MAX5432_OHM_100K पूर्ण,
	अणु .compatible = "maxim,max5434", .data = (व्योम *)MAX5432_OHM_50K  पूर्ण,
	अणु .compatible = "maxim,max5435", .data = (व्योम *)MAX5432_OHM_100K पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max5432_dt_ids);

अटल काष्ठा i2c_driver max5432_driver = अणु
	.driver = अणु
		.name = "max5432",
		.of_match_table = max5432_dt_ids,
	पूर्ण,
	.probe = max5432_probe,
पूर्ण;

module_i2c_driver(max5432_driver);

MODULE_AUTHOR("Martin Kaiser <martin@kaiser.cx>");
MODULE_DESCRIPTION("max5432-max5435 digital potentiometers");
MODULE_LICENSE("GPL v2");
