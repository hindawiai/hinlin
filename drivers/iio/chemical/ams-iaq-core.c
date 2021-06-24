<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ams-iaq-core.c - Support क्रम AMS iAQ-Core VOC sensors
 *
 * Copyright (C) 2015, 2018
 * Author: Matt Ranostay <matt.ranostay@konsulko.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/mutex.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>

#घोषणा AMS_IAQCORE_DATA_SIZE		9

#घोषणा AMS_IAQCORE_VOC_CO2_IDX		0
#घोषणा AMS_IAQCORE_VOC_RESISTANCE_IDX	1
#घोषणा AMS_IAQCORE_VOC_TVOC_IDX	2

काष्ठा ams_iaqcore_पढ़ोing अणु
	__be16 co2_ppm;
	u8 status;
	__be32 resistance;
	__be16 voc_ppb;
पूर्ण __attribute__((__packed__));

काष्ठा ams_iaqcore_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	अचिन्हित दीर्घ last_update;

	काष्ठा ams_iaqcore_पढ़ोing buffer;
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ams_iaqcore_channels[] = अणु
	अणु
		.type = IIO_CONCENTRATION,
		.channel2 = IIO_MOD_CO2,
		.modअगरied = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.address = AMS_IAQCORE_VOC_CO2_IDX,
	पूर्ण,
	अणु
		.type = IIO_RESISTANCE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.address = AMS_IAQCORE_VOC_RESISTANCE_IDX,
	पूर्ण,
	अणु
		.type = IIO_CONCENTRATION,
		.channel2 = IIO_MOD_VOC,
		.modअगरied = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
		.address = AMS_IAQCORE_VOC_TVOC_IDX,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ams_iaqcore_पढ़ो_measurement(काष्ठा ams_iaqcore_data *data)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक ret;

	काष्ठा i2c_msg msg = अणु
		.addr = client->addr,
		.flags = client->flags | I2C_M_RD,
		.len = AMS_IAQCORE_DATA_SIZE,
		.buf = (अक्षर *) &data->buffer,
	पूर्ण;

	ret = i2c_transfer(client->adapter, &msg, 1);

	वापस (ret == AMS_IAQCORE_DATA_SIZE) ? 0 : ret;
पूर्ण

अटल पूर्णांक ams_iaqcore_get_measurement(काष्ठा ams_iaqcore_data *data)
अणु
	पूर्णांक ret;

	/* sensor can only be polled once a second max per datasheet */
	अगर (!समय_after(jअगरfies, data->last_update + HZ))
		वापस 0;

	ret = ams_iaqcore_पढ़ो_measurement(data);
	अगर (ret < 0)
		वापस ret;

	data->last_update = jअगरfies;

	वापस 0;
पूर्ण

अटल पूर्णांक ams_iaqcore_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
				पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा ams_iaqcore_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (mask != IIO_CHAN_INFO_PROCESSED)
		वापस -EINVAL;

	mutex_lock(&data->lock);
	ret = ams_iaqcore_get_measurement(data);

	अगर (ret)
		जाओ err_out;

	चयन (chan->address) अणु
	हाल AMS_IAQCORE_VOC_CO2_IDX:
		*val = 0;
		*val2 = be16_to_cpu(data->buffer.co2_ppm);
		ret = IIO_VAL_INT_PLUS_MICRO;
		अवरोध;
	हाल AMS_IAQCORE_VOC_RESISTANCE_IDX:
		*val = be32_to_cpu(data->buffer.resistance);
		ret = IIO_VAL_INT;
		अवरोध;
	हाल AMS_IAQCORE_VOC_TVOC_IDX:
		*val = 0;
		*val2 = be16_to_cpu(data->buffer.voc_ppb);
		ret = IIO_VAL_INT_PLUS_न_अंकO;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

err_out:
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info ams_iaqcore_info = अणु
	.पढ़ो_raw	= ams_iaqcore_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक ams_iaqcore_probe(काष्ठा i2c_client *client,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा ams_iaqcore_data *data;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	/* so initial पढ़ोing will complete */
	data->last_update = jअगरfies - HZ;
	mutex_init(&data->lock);

	indio_dev->info = &ams_iaqcore_info;
	indio_dev->name = dev_name(&client->dev);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	indio_dev->channels = ams_iaqcore_channels;
	indio_dev->num_channels = ARRAY_SIZE(ams_iaqcore_channels);

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ams_iaqcore_id[] = अणु
	अणु "ams-iaq-core", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ams_iaqcore_id);

अटल स्थिर काष्ठा of_device_id ams_iaqcore_dt_ids[] = अणु
	अणु .compatible = "ams,iaq-core" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ams_iaqcore_dt_ids);

अटल काष्ठा i2c_driver ams_iaqcore_driver = अणु
	.driver = अणु
		.name	= "ams-iaq-core",
		.of_match_table = ams_iaqcore_dt_ids,
	पूर्ण,
	.probe = ams_iaqcore_probe,
	.id_table = ams_iaqcore_id,
पूर्ण;
module_i2c_driver(ams_iaqcore_driver);

MODULE_AUTHOR("Matt Ranostay <matt.ranostay@konsulko.com>");
MODULE_DESCRIPTION("AMS iAQ-Core VOC sensors");
MODULE_LICENSE("GPL v2");
