<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Maxim Integrated
 * 7-bit, Multi-Channel Sink/Source Current DAC Driver
 * Copyright (C) 2017 Maxim Integrated
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/driver.h>
#समावेश <linux/iio/machine.h>
#समावेश <linux/iio/consumer.h>

#घोषणा DS4422_MAX_DAC_CHANNELS		2
#घोषणा DS4424_MAX_DAC_CHANNELS		4

#घोषणा DS4424_DAC_ADDR(chan)   ((chan) + 0xf8)
#घोषणा DS4424_SOURCE_I		1
#घोषणा DS4424_SINK_I		0

#घोषणा DS4424_CHANNEL(chan) अणु \
	.type = IIO_CURRENT, \
	.indexed = 1, \
	.output = 1, \
	.channel = chan, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
पूर्ण

/*
 * DS4424 DAC control रेजिस्टर 8 bits
 * [7]		0: to sink; 1: to source
 * [6:0]	steps to sink/source
 * bit[7] looks like a sign bit, but the value of the रेजिस्टर is
 * not a two's complement code considering the bit[6:0] is a असलolute
 * distance from the zero poपूर्णांक.
 */
जोड़ ds4424_raw_data अणु
	काष्ठा अणु
		u8 dx:7;
		u8 source_bit:1;
	पूर्ण;
	u8 bits;
पूर्ण;

क्रमागत ds4424_device_ids अणु
	ID_DS4422,
	ID_DS4424,
पूर्ण;

काष्ठा ds4424_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	uपूर्णांक8_t save[DS4424_MAX_DAC_CHANNELS];
	काष्ठा regulator *vcc_reg;
	uपूर्णांक8_t raw[DS4424_MAX_DAC_CHANNELS];
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ds4424_channels[] = अणु
	DS4424_CHANNEL(0),
	DS4424_CHANNEL(1),
	DS4424_CHANNEL(2),
	DS4424_CHANNEL(3),
पूर्ण;

अटल पूर्णांक ds4424_get_value(काष्ठा iio_dev *indio_dev,
			     पूर्णांक *val, पूर्णांक channel)
अणु
	काष्ठा ds4424_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = i2c_smbus_पढ़ो_byte_data(data->client, DS4424_DAC_ADDR(channel));
	अगर (ret < 0)
		जाओ fail;

	*val = ret;

fail:
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ds4424_set_value(काष्ठा iio_dev *indio_dev,
			     पूर्णांक val, काष्ठा iio_chan_spec स्थिर *chan)
अणु
	काष्ठा ds4424_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = i2c_smbus_ग_लिखो_byte_data(data->client,
			DS4424_DAC_ADDR(chan->channel), val);
	अगर (ret < 0)
		जाओ fail;

	data->raw[chan->channel] = val;

fail:
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ds4424_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	जोड़ ds4424_raw_data raw;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = ds4424_get_value(indio_dev, val, chan->channel);
		अगर (ret < 0) अणु
			pr_err("%s : ds4424_get_value returned %d\n",
							__func__, ret);
			वापस ret;
		पूर्ण
		raw.bits = *val;
		*val = raw.dx;
		अगर (raw.source_bit == DS4424_SINK_I)
			*val = -*val;
		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ds4424_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	जोड़ ds4424_raw_data raw;

	अगर (val2 != 0)
		वापस -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (val < S8_MIN || val > S8_MAX)
			वापस -EINVAL;

		अगर (val > 0) अणु
			raw.source_bit = DS4424_SOURCE_I;
			raw.dx = val;
		पूर्ण अन्यथा अणु
			raw.source_bit = DS4424_SINK_I;
			raw.dx = -val;
		पूर्ण

		वापस ds4424_set_value(indio_dev, raw.bits, chan);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ds4424_verअगरy_chip(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret, val;

	ret = ds4424_get_value(indio_dev, &val, 0);
	अगर (ret < 0)
		dev_err(&indio_dev->dev,
				"%s failed. ret: %d\n", __func__, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused ds4424_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा ds4424_data *data = iio_priv(indio_dev);
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < indio_dev->num_channels; i++) अणु
		data->save[i] = data->raw[i];
		ret = ds4424_set_value(indio_dev, 0,
				&indio_dev->channels[i]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused ds4424_resume(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा ds4424_data *data = iio_priv(indio_dev);
	पूर्णांक ret = 0;
	पूर्णांक i;

	क्रम (i = 0; i < indio_dev->num_channels; i++) अणु
		ret = ds4424_set_value(indio_dev, data->save[i],
				&indio_dev->channels[i]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ds4424_pm_ops, ds4424_suspend, ds4424_resume);

अटल स्थिर काष्ठा iio_info ds4424_info = अणु
	.पढ़ो_raw = ds4424_पढ़ो_raw,
	.ग_लिखो_raw = ds4424_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक ds4424_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ds4424_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev) अणु
		dev_err(&client->dev, "iio dev alloc failed.\n");
		वापस -ENOMEM;
	पूर्ण

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	indio_dev->name = id->name;

	data->vcc_reg = devm_regulator_get(&client->dev, "vcc");
	अगर (IS_ERR(data->vcc_reg)) अणु
		dev_err(&client->dev,
			"Failed to get vcc-supply regulator. err: %ld\n",
				PTR_ERR(data->vcc_reg));
		वापस PTR_ERR(data->vcc_reg);
	पूर्ण

	mutex_init(&data->lock);
	ret = regulator_enable(data->vcc_reg);
	अगर (ret < 0) अणु
		dev_err(&client->dev,
				"Unable to enable the regulator.\n");
		वापस ret;
	पूर्ण

	usleep_range(1000, 1200);
	ret = ds4424_verअगरy_chip(indio_dev);
	अगर (ret < 0)
		जाओ fail;

	चयन (id->driver_data) अणु
	हाल ID_DS4422:
		indio_dev->num_channels = DS4422_MAX_DAC_CHANNELS;
		अवरोध;
	हाल ID_DS4424:
		indio_dev->num_channels = DS4424_MAX_DAC_CHANNELS;
		अवरोध;
	शेष:
		dev_err(&client->dev,
				"ds4424: Invalid chip id.\n");
		ret = -ENXIO;
		जाओ fail;
	पूर्ण

	indio_dev->channels = ds4424_channels;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &ds4424_info;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&client->dev,
				"iio_device_register failed. ret: %d\n", ret);
		जाओ fail;
	पूर्ण

	वापस ret;

fail:
	regulator_disable(data->vcc_reg);
	वापस ret;
पूर्ण

अटल पूर्णांक ds4424_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा ds4424_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	regulator_disable(data->vcc_reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ds4424_id[] = अणु
	अणु "ds4422", ID_DS4422 पूर्ण,
	अणु "ds4424", ID_DS4424 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, ds4424_id);

अटल स्थिर काष्ठा of_device_id ds4424_of_match[] = अणु
	अणु .compatible = "maxim,ds4422" पूर्ण,
	अणु .compatible = "maxim,ds4424" पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, ds4424_of_match);

अटल काष्ठा i2c_driver ds4424_driver = अणु
	.driver = अणु
		.name	= "ds4424",
		.of_match_table = ds4424_of_match,
		.pm     = &ds4424_pm_ops,
	पूर्ण,
	.probe		= ds4424_probe,
	.हटाओ		= ds4424_हटाओ,
	.id_table	= ds4424_id,
पूर्ण;
module_i2c_driver(ds4424_driver);

MODULE_DESCRIPTION("Maxim DS4424 DAC Driver");
MODULE_AUTHOR("Ismail H. Kose <ismail.kose@maximintegrated.com>");
MODULE_AUTHOR("Vishal Sood <vishal.sood@maximintegrated.com>");
MODULE_AUTHOR("David Jung <david.jung@maximintegrated.com>");
MODULE_LICENSE("GPL v2");
