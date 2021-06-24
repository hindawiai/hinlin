<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ti-adc161s626.c - Texas Instruments ADC161S626 1-channel dअगरferential ADC
 *
 * ADC Devices Supported:
 *  adc141s626 - 14-bit ADC
 *  adc161s626 - 16-bit ADC
 *
 * Copyright (C) 2016-2018
 * Author: Matt Ranostay <matt.ranostay@konsulko.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा TI_ADC_DRV_NAME	"ti-adc161s626"

क्रमागत अणु
	TI_ADC141S626,
	TI_ADC161S626,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ti_adc141s626_channels[] = अणु
	अणु
		.type = IIO_VOLTAGE,
		.channel = 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE) |
				      BIT(IIO_CHAN_INFO_OFFSET),
		.scan_index = 0,
		.scan_type = अणु
			.sign = 's',
			.realbits = 14,
			.storagebits = 16,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(1),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ti_adc161s626_channels[] = अणु
	अणु
		.type = IIO_VOLTAGE,
		.channel = 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE) |
				      BIT(IIO_CHAN_INFO_OFFSET),
		.scan_index = 0,
		.scan_type = अणु
			.sign = 's',
			.realbits = 16,
			.storagebits = 16,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(1),
पूर्ण;

काष्ठा ti_adc_data अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा spi_device *spi;
	काष्ठा regulator *ref;

	u8 पढ़ो_size;
	u8 shअगरt;

	u8 buffer[16] ____cacheline_aligned;
पूर्ण;

अटल पूर्णांक ti_adc_पढ़ो_measurement(काष्ठा ti_adc_data *data,
				   काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val)
अणु
	पूर्णांक ret;

	चयन (data->पढ़ो_size) अणु
	हाल 2: अणु
		__be16 buf;

		ret = spi_पढ़ो(data->spi, (व्योम *) &buf, 2);
		अगर (ret)
			वापस ret;

		*val = be16_to_cpu(buf);
		अवरोध;
	पूर्ण
	हाल 3: अणु
		__be32 buf;

		ret = spi_पढ़ो(data->spi, (व्योम *) &buf, 3);
		अगर (ret)
			वापस ret;

		*val = be32_to_cpu(buf) >> 8;
		अवरोध;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण

	*val = sign_extend32(*val >> data->shअगरt, chan->scan_type.realbits - 1);

	वापस 0;
पूर्ण

अटल irqवापस_t ti_adc_trigger_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_poll_func *pf = निजी;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा ti_adc_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = ti_adc_पढ़ो_measurement(data, &indio_dev->channels[0],
				     (पूर्णांक *) &data->buffer);
	अगर (!ret)
		iio_push_to_buffers_with_बारtamp(indio_dev,
					data->buffer,
					iio_get_समय_ns(indio_dev));

	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ti_adc_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा ti_adc_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		ret = ti_adc_पढ़ो_measurement(data, chan, val);
		iio_device_release_direct_mode(indio_dev);

		अगर (ret)
			वापस ret;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		ret = regulator_get_voltage(data->ref);
		अगर (ret < 0)
			वापस ret;

		*val = ret / 1000;
		*val2 = chan->scan_type.realbits;

		वापस IIO_VAL_FRACTIONAL_LOG2;
	हाल IIO_CHAN_INFO_OFFSET:
		*val = 1 << (chan->scan_type.realbits - 1);
		वापस IIO_VAL_INT;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_info ti_adc_info = अणु
	.पढ़ो_raw = ti_adc_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक ti_adc_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा ti_adc_data *data;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	indio_dev->info = &ti_adc_info;
	indio_dev->name = TI_ADC_DRV_NAME;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	spi_set_drvdata(spi, indio_dev);

	data = iio_priv(indio_dev);
	data->spi = spi;

	चयन (spi_get_device_id(spi)->driver_data) अणु
	हाल TI_ADC141S626:
		indio_dev->channels = ti_adc141s626_channels;
		indio_dev->num_channels = ARRAY_SIZE(ti_adc141s626_channels);
		data->shअगरt = 0;
		data->पढ़ो_size = 2;
		अवरोध;
	हाल TI_ADC161S626:
		indio_dev->channels = ti_adc161s626_channels;
		indio_dev->num_channels = ARRAY_SIZE(ti_adc161s626_channels);
		data->shअगरt = 6;
		data->पढ़ो_size = 3;
		अवरोध;
	पूर्ण

	data->ref = devm_regulator_get(&spi->dev, "vdda");
	अगर (!IS_ERR(data->ref)) अणु
		ret = regulator_enable(data->ref);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
					 ti_adc_trigger_handler, शून्य);
	अगर (ret)
		जाओ error_regulator_disable;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_unreg_buffer;

	वापस 0;

error_unreg_buffer:
	iio_triggered_buffer_cleanup(indio_dev);

error_regulator_disable:
	regulator_disable(data->ref);

	वापस ret;
पूर्ण

अटल पूर्णांक ti_adc_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ti_adc_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	regulator_disable(data->ref);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ti_adc_dt_ids[] = अणु
	अणु .compatible = "ti,adc141s626", पूर्ण,
	अणु .compatible = "ti,adc161s626", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ti_adc_dt_ids);

अटल स्थिर काष्ठा spi_device_id ti_adc_id[] = अणु
	अणु"adc141s626", TI_ADC141S626पूर्ण,
	अणु"adc161s626", TI_ADC161S626पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, ti_adc_id);

अटल काष्ठा spi_driver ti_adc_driver = अणु
	.driver = अणु
		.name	= TI_ADC_DRV_NAME,
		.of_match_table = ti_adc_dt_ids,
	पूर्ण,
	.probe		= ti_adc_probe,
	.हटाओ		= ti_adc_हटाओ,
	.id_table	= ti_adc_id,
पूर्ण;
module_spi_driver(ti_adc_driver);

MODULE_AUTHOR("Matt Ranostay <matt.ranostay@konsulko.com>");
MODULE_DESCRIPTION("Texas Instruments ADC1x1S 1-channel differential ADC");
MODULE_LICENSE("GPL");
