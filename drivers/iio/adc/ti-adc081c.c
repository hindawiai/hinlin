<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI ADC081C/ADC101C/ADC121C 8/10/12-bit ADC driver
 *
 * Copyright (C) 2012 Avionic Design GmbH
 * Copyright (C) 2016 Intel
 *
 * Datasheets:
 *	https://www.ti.com/lit/ds/symlink/adc081c021.pdf
 *	https://www.ti.com/lit/ds/symlink/adc101c021.pdf
 *	https://www.ti.com/lit/ds/symlink/adc121c021.pdf
 *
 * The devices have a very similar पूर्णांकerface and dअगरfer mostly in the number of
 * bits handled. For the 8-bit and 10-bit models the least-signअगरicant 4 or 2
 * bits of value रेजिस्टरs are reserved.
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/regulator/consumer.h>

काष्ठा adc081c अणु
	काष्ठा i2c_client *i2c;
	काष्ठा regulator *ref;

	/* 8, 10 or 12 */
	पूर्णांक bits;

	/* Ensure natural alignment of buffer elements */
	काष्ठा अणु
		u16 channel;
		s64 ts __aligned(8);
	पूर्ण scan;
पूर्ण;

#घोषणा REG_CONV_RES 0x00

अटल पूर्णांक adc081c_पढ़ो_raw(काष्ठा iio_dev *iio,
			    काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *value,
			    पूर्णांक *shअगरt, दीर्घ mask)
अणु
	काष्ठा adc081c *adc = iio_priv(iio);
	पूर्णांक err;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		err = i2c_smbus_पढ़ो_word_swapped(adc->i2c, REG_CONV_RES);
		अगर (err < 0)
			वापस err;

		*value = (err & 0xFFF) >> (12 - adc->bits);
		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		err = regulator_get_voltage(adc->ref);
		अगर (err < 0)
			वापस err;

		*value = err / 1000;
		*shअगरt = adc->bits;

		वापस IIO_VAL_FRACTIONAL_LOG2;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

#घोषणा ADCxx1C_CHAN(_bits) अणु					\
	.type = IIO_VOLTAGE,					\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.scan_type = अणु						\
		.sign = 'u',					\
		.realbits = (_bits),				\
		.storagebits = 16,				\
		.shअगरt = 12 - (_bits),				\
		.endianness = IIO_CPU,				\
	पूर्ण,							\
पूर्ण

#घोषणा DEFINE_ADCxx1C_CHANNELS(_name, _bits)				\
	अटल स्थिर काष्ठा iio_chan_spec _name ## _channels[] = अणु	\
		ADCxx1C_CHAN((_bits)),					\
		IIO_CHAN_SOFT_TIMESTAMP(1),				\
	पूर्ण;								\

#घोषणा ADC081C_NUM_CHANNELS 2

काष्ठा adcxx1c_model अणु
	स्थिर काष्ठा iio_chan_spec* channels;
	पूर्णांक bits;
पूर्ण;

#घोषणा ADCxx1C_MODEL(_name, _bits)					\
	अणु								\
		.channels = _name ## _channels,				\
		.bits = (_bits),					\
	पूर्ण

DEFINE_ADCxx1C_CHANNELS(adc081c,  8);
DEFINE_ADCxx1C_CHANNELS(adc101c, 10);
DEFINE_ADCxx1C_CHANNELS(adc121c, 12);

/* Model ids are indexes in _models array */
क्रमागत adcxx1c_model_id अणु
	ADC081C = 0,
	ADC101C = 1,
	ADC121C = 2,
पूर्ण;

अटल काष्ठा adcxx1c_model adcxx1c_models[] = अणु
	ADCxx1C_MODEL(adc081c,  8),
	ADCxx1C_MODEL(adc101c, 10),
	ADCxx1C_MODEL(adc121c, 12),
पूर्ण;

अटल स्थिर काष्ठा iio_info adc081c_info = अणु
	.पढ़ो_raw = adc081c_पढ़ो_raw,
पूर्ण;

अटल irqवापस_t adc081c_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा adc081c *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_word_swapped(data->i2c, REG_CONV_RES);
	अगर (ret < 0)
		जाओ out;
	data->scan.channel = ret;
	iio_push_to_buffers_with_बारtamp(indio_dev, &data->scan,
					   iio_get_समय_ns(indio_dev));
out:
	iio_trigger_notअगरy_करोne(indio_dev->trig);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक adc081c_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा iio_dev *iio;
	काष्ठा adc081c *adc;
	काष्ठा adcxx1c_model *model;
	पूर्णांक err;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_WORD_DATA))
		वापस -EOPNOTSUPP;

	model = &adcxx1c_models[id->driver_data];

	iio = devm_iio_device_alloc(&client->dev, माप(*adc));
	अगर (!iio)
		वापस -ENOMEM;

	adc = iio_priv(iio);
	adc->i2c = client;
	adc->bits = model->bits;

	adc->ref = devm_regulator_get(&client->dev, "vref");
	अगर (IS_ERR(adc->ref))
		वापस PTR_ERR(adc->ref);

	err = regulator_enable(adc->ref);
	अगर (err < 0)
		वापस err;

	iio->name = dev_name(&client->dev);
	iio->modes = INDIO_सूचीECT_MODE;
	iio->info = &adc081c_info;

	iio->channels = model->channels;
	iio->num_channels = ADC081C_NUM_CHANNELS;

	err = iio_triggered_buffer_setup(iio, शून्य, adc081c_trigger_handler, शून्य);
	अगर (err < 0) अणु
		dev_err(&client->dev, "iio triggered buffer setup failed\n");
		जाओ err_regulator_disable;
	पूर्ण

	err = iio_device_रेजिस्टर(iio);
	अगर (err < 0)
		जाओ err_buffer_cleanup;

	i2c_set_clientdata(client, iio);

	वापस 0;

err_buffer_cleanup:
	iio_triggered_buffer_cleanup(iio);
err_regulator_disable:
	regulator_disable(adc->ref);

	वापस err;
पूर्ण

अटल पूर्णांक adc081c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *iio = i2c_get_clientdata(client);
	काष्ठा adc081c *adc = iio_priv(iio);

	iio_device_unरेजिस्टर(iio);
	iio_triggered_buffer_cleanup(iio);
	regulator_disable(adc->ref);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id adc081c_id[] = अणु
	अणु "adc081c", ADC081C पूर्ण,
	अणु "adc101c", ADC101C पूर्ण,
	अणु "adc121c", ADC121C पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, adc081c_id);

अटल स्थिर काष्ठा of_device_id adc081c_of_match[] = अणु
	अणु .compatible = "ti,adc081c" पूर्ण,
	अणु .compatible = "ti,adc101c" पूर्ण,
	अणु .compatible = "ti,adc121c" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adc081c_of_match);

अटल काष्ठा i2c_driver adc081c_driver = अणु
	.driver = अणु
		.name = "adc081c",
		.of_match_table = adc081c_of_match,
	पूर्ण,
	.probe = adc081c_probe,
	.हटाओ = adc081c_हटाओ,
	.id_table = adc081c_id,
पूर्ण;
module_i2c_driver(adc081c_driver);

MODULE_AUTHOR("Thierry Reding <thierry.reding@avionic-design.de>");
MODULE_DESCRIPTION("Texas Instruments ADC081C/ADC101C/ADC121C driver");
MODULE_LICENSE("GPL v2");
