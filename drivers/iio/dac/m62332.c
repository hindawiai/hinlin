<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  m62332.c - Support क्रम Mitsubishi m62332 DAC
 *
 *  Copyright (c) 2014 Dmitry Eremin-Solenikov
 *
 *  Based on max517 driver:
 *  Copyright (C) 2010, 2011 Roland Stigge <stigge@antcom.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/driver.h>

#समावेश <linux/regulator/consumer.h>

#घोषणा M62332_CHANNELS 2

काष्ठा m62332_data अणु
	काष्ठा i2c_client	*client;
	काष्ठा regulator	*vcc;
	काष्ठा mutex		mutex;
	u8			raw[M62332_CHANNELS];
#अगर_घोषित CONFIG_PM_SLEEP
	u8			save[M62332_CHANNELS];
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक m62332_set_value(काष्ठा iio_dev *indio_dev, u8 val, पूर्णांक channel)
अणु
	काष्ठा m62332_data *data = iio_priv(indio_dev);
	काष्ठा i2c_client *client = data->client;
	u8 outbuf[2];
	पूर्णांक res;

	अगर (val == data->raw[channel])
		वापस 0;

	outbuf[0] = channel;
	outbuf[1] = val;

	mutex_lock(&data->mutex);

	अगर (val) अणु
		res = regulator_enable(data->vcc);
		अगर (res)
			जाओ out;
	पूर्ण

	res = i2c_master_send(client, outbuf, ARRAY_SIZE(outbuf));
	अगर (res >= 0 && res != ARRAY_SIZE(outbuf))
		res = -EIO;
	अगर (res < 0)
		जाओ out;

	data->raw[channel] = val;

	अगर (!val)
		regulator_disable(data->vcc);

	mutex_unlock(&data->mutex);

	वापस 0;

out:
	mutex_unlock(&data->mutex);

	वापस res;
पूर्ण

अटल पूर्णांक m62332_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ mask)
अणु
	काष्ठा m62332_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		/* Corresponds to Vref / 2^(bits) */
		ret = regulator_get_voltage(data->vcc);
		अगर (ret < 0)
			वापस ret;

		*val = ret / 1000; /* mV */
		*val2 = 8;

		वापस IIO_VAL_FRACTIONAL_LOG2;
	हाल IIO_CHAN_INFO_RAW:
		*val = data->raw[chan->channel];

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_OFFSET:
		*val = 1;

		वापस IIO_VAL_INT;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक m62332_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val, पूर्णांक val2,
			    दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (val < 0 || val > 255)
			वापस -EINVAL;

		वापस m62332_set_value(indio_dev, val, chan->channel);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक m62332_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा m62332_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	data->save[0] = data->raw[0];
	data->save[1] = data->raw[1];

	ret = m62332_set_value(indio_dev, 0, 0);
	अगर (ret < 0)
		वापस ret;

	वापस m62332_set_value(indio_dev, 0, 1);
पूर्ण

अटल पूर्णांक m62332_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा m62332_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = m62332_set_value(indio_dev, data->save[0], 0);
	अगर (ret < 0)
		वापस ret;

	वापस m62332_set_value(indio_dev, data->save[1], 1);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(m62332_pm_ops, m62332_suspend, m62332_resume);
#घोषणा M62332_PM_OPS (&m62332_pm_ops)
#अन्यथा
#घोषणा M62332_PM_OPS शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा iio_info m62332_info = अणु
	.पढ़ो_raw = m62332_पढ़ो_raw,
	.ग_लिखो_raw = m62332_ग_लिखो_raw,
पूर्ण;

#घोषणा M62332_CHANNEL(chan) अणु					\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.output = 1,						\
	.channel = (chan),					\
	.datasheet_name = "CH" #chan,				\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |	\
				    BIT(IIO_CHAN_INFO_OFFSET),	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec m62332_channels[M62332_CHANNELS] = अणु
	M62332_CHANNEL(0),
	M62332_CHANNEL(1)
पूर्ण;

अटल पूर्णांक m62332_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा m62332_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	mutex_init(&data->mutex);

	data->vcc = devm_regulator_get(&client->dev, "VCC");
	अगर (IS_ERR(data->vcc))
		वापस PTR_ERR(data->vcc);

	indio_dev->num_channels = ARRAY_SIZE(m62332_channels);
	indio_dev->channels = m62332_channels;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &m62332_info;

	ret = iio_map_array_रेजिस्टर(indio_dev, client->dev.platक्रमm_data);
	अगर (ret < 0)
		वापस ret;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ err;

	वापस 0;

err:
	iio_map_array_unरेजिस्टर(indio_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक m62332_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);

	iio_device_unरेजिस्टर(indio_dev);
	iio_map_array_unरेजिस्टर(indio_dev);
	m62332_set_value(indio_dev, 0, 0);
	m62332_set_value(indio_dev, 0, 1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id m62332_id[] = अणु
	अणु "m62332", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, m62332_id);

अटल काष्ठा i2c_driver m62332_driver = अणु
	.driver = अणु
		.name	= "m62332",
		.pm	= M62332_PM_OPS,
	पूर्ण,
	.probe		= m62332_probe,
	.हटाओ		= m62332_हटाओ,
	.id_table	= m62332_id,
पूर्ण;
module_i2c_driver(m62332_driver);

MODULE_AUTHOR("Dmitry Eremin-Solenikov");
MODULE_DESCRIPTION("M62332 8-bit DAC");
MODULE_LICENSE("GPL v2");
