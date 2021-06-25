<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ADC12130/ADC12132/ADC12138 12-bit plus sign ADC driver
 *
 * Copyright (c) 2016 Akinobu Mita <akinobu.mita@gmail.com>
 *
 * Datasheet: http://www.ti.com/lit/ds/symlink/adc12138.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/completion.h>
#समावेश <linux/clk.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा ADC12138_MODE_AUTO_CAL			0x08
#घोषणा ADC12138_MODE_READ_STATUS		0x0c
#घोषणा ADC12138_MODE_ACQUISITION_TIME_6	0x0e
#घोषणा ADC12138_MODE_ACQUISITION_TIME_10	0x4e
#घोषणा ADC12138_MODE_ACQUISITION_TIME_18	0x8e
#घोषणा ADC12138_MODE_ACQUISITION_TIME_34	0xce

#घोषणा ADC12138_STATUS_CAL			BIT(6)

क्रमागत अणु
	adc12130,
	adc12132,
	adc12138,
पूर्ण;

काष्ठा adc12138 अणु
	काष्ठा spi_device *spi;
	अचिन्हित पूर्णांक id;
	/* conversion घड़ी */
	काष्ठा clk *cclk;
	/* positive analog voltage reference */
	काष्ठा regulator *vref_p;
	/* negative analog voltage reference */
	काष्ठा regulator *vref_n;
	काष्ठा mutex lock;
	काष्ठा completion complete;
	/* The number of cclk periods क्रम the S/H's acquisition समय */
	अचिन्हित पूर्णांक acquisition_समय;
	/*
	 * Maximum size needed: 16x 2 bytes ADC data + 8 bytes बारtamp.
	 * Less may be need अगर not all channels are enabled, as दीर्घ as
	 * the 8 byte alignment of the बारtamp is मुख्यtained.
	 */
	__be16 data[20] __aligned(8);

	u8 tx_buf[2] ____cacheline_aligned;
	u8 rx_buf[2];
पूर्ण;

#घोषणा ADC12138_VOLTAGE_CHANNEL(chan)					\
	अणु								\
		.type = IIO_VOLTAGE,					\
		.indexed = 1,						\
		.channel = chan,					\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE)	\
					| BIT(IIO_CHAN_INFO_OFFSET),	\
		.scan_index = chan,					\
		.scan_type = अणु						\
			.sign = 's',					\
			.realbits = 13,					\
			.storagebits = 16,				\
			.shअगरt = 3,					\
			.endianness = IIO_BE,				\
		पूर्ण,							\
	पूर्ण

#घोषणा ADC12138_VOLTAGE_CHANNEL_DIFF(chan1, chan2, si)			\
	अणु								\
		.type = IIO_VOLTAGE,					\
		.indexed = 1,						\
		.channel = (chan1),					\
		.channel2 = (chan2),					\
		.dअगरferential = 1,					\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE)	\
					| BIT(IIO_CHAN_INFO_OFFSET),	\
		.scan_index = si,					\
		.scan_type = अणु						\
			.sign = 's',					\
			.realbits = 13,					\
			.storagebits = 16,				\
			.shअगरt = 3,					\
			.endianness = IIO_BE,				\
		पूर्ण,							\
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec adc12132_channels[] = अणु
	ADC12138_VOLTAGE_CHANNEL(0),
	ADC12138_VOLTAGE_CHANNEL(1),
	ADC12138_VOLTAGE_CHANNEL_DIFF(0, 1, 2),
	ADC12138_VOLTAGE_CHANNEL_DIFF(1, 0, 3),
	IIO_CHAN_SOFT_TIMESTAMP(4),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec adc12138_channels[] = अणु
	ADC12138_VOLTAGE_CHANNEL(0),
	ADC12138_VOLTAGE_CHANNEL(1),
	ADC12138_VOLTAGE_CHANNEL(2),
	ADC12138_VOLTAGE_CHANNEL(3),
	ADC12138_VOLTAGE_CHANNEL(4),
	ADC12138_VOLTAGE_CHANNEL(5),
	ADC12138_VOLTAGE_CHANNEL(6),
	ADC12138_VOLTAGE_CHANNEL(7),
	ADC12138_VOLTAGE_CHANNEL_DIFF(0, 1, 8),
	ADC12138_VOLTAGE_CHANNEL_DIFF(1, 0, 9),
	ADC12138_VOLTAGE_CHANNEL_DIFF(2, 3, 10),
	ADC12138_VOLTAGE_CHANNEL_DIFF(3, 2, 11),
	ADC12138_VOLTAGE_CHANNEL_DIFF(4, 5, 12),
	ADC12138_VOLTAGE_CHANNEL_DIFF(5, 4, 13),
	ADC12138_VOLTAGE_CHANNEL_DIFF(6, 7, 14),
	ADC12138_VOLTAGE_CHANNEL_DIFF(7, 6, 15),
	IIO_CHAN_SOFT_TIMESTAMP(16),
पूर्ण;

अटल पूर्णांक adc12138_mode_programming(काष्ठा adc12138 *adc, u8 mode,
				     व्योम *rx_buf, पूर्णांक len)
अणु
	काष्ठा spi_transfer xfer = अणु
		.tx_buf = adc->tx_buf,
		.rx_buf = adc->rx_buf,
		.len = len,
	पूर्ण;
	पूर्णांक ret;

	/* Skip unused bits क्रम ADC12130 and ADC12132 */
	अगर (adc->id != adc12138)
		mode = (mode & 0xc0) | ((mode & 0x0f) << 2);

	adc->tx_buf[0] = mode;

	ret = spi_sync_transfer(adc->spi, &xfer, 1);
	अगर (ret)
		वापस ret;

	स_नकल(rx_buf, adc->rx_buf, len);

	वापस 0;
पूर्ण

अटल पूर्णांक adc12138_पढ़ो_status(काष्ठा adc12138 *adc)
अणु
	u8 rx_buf[2];
	पूर्णांक ret;

	ret = adc12138_mode_programming(adc, ADC12138_MODE_READ_STATUS,
					rx_buf, 2);
	अगर (ret)
		वापस ret;

	वापस (rx_buf[0] << 1) | (rx_buf[1] >> 7);
पूर्ण

अटल पूर्णांक __adc12138_start_conv(काष्ठा adc12138 *adc,
				 काष्ठा iio_chan_spec स्थिर *channel,
				 व्योम *data, पूर्णांक len)

अणु
	अटल स्थिर u8 ch_to_mux[] = अणु 0, 4, 1, 5, 2, 6, 3, 7 पूर्ण;
	u8 mode = (ch_to_mux[channel->channel] << 4) |
		  (channel->dअगरferential ? 0 : 0x80);

	वापस adc12138_mode_programming(adc, mode, data, len);
पूर्ण

अटल पूर्णांक adc12138_start_conv(काष्ठा adc12138 *adc,
			       काष्ठा iio_chan_spec स्थिर *channel)
अणु
	u8 trash;

	वापस __adc12138_start_conv(adc, channel, &trash, 1);
पूर्ण

अटल पूर्णांक adc12138_start_and_पढ़ो_conv(काष्ठा adc12138 *adc,
					काष्ठा iio_chan_spec स्थिर *channel,
					__be16 *data)
अणु
	वापस __adc12138_start_conv(adc, channel, data, 2);
पूर्ण

अटल पूर्णांक adc12138_पढ़ो_conv_data(काष्ठा adc12138 *adc, __be16 *value)
अणु
	/* Issue a पढ़ो status inकाष्ठाion and पढ़ो previous conversion data */
	वापस adc12138_mode_programming(adc, ADC12138_MODE_READ_STATUS,
					 value, माप(*value));
पूर्ण

अटल पूर्णांक adc12138_रुको_eoc(काष्ठा adc12138 *adc, अचिन्हित दीर्घ समयout)
अणु
	अगर (!रुको_क्रम_completion_समयout(&adc->complete, समयout))
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल पूर्णांक adc12138_adc_conversion(काष्ठा adc12138 *adc,
				   काष्ठा iio_chan_spec स्थिर *channel,
				   __be16 *value)
अणु
	पूर्णांक ret;

	reinit_completion(&adc->complete);

	ret = adc12138_start_conv(adc, channel);
	अगर (ret)
		वापस ret;

	ret = adc12138_रुको_eoc(adc, msecs_to_jअगरfies(100));
	अगर (ret)
		वापस ret;

	वापस adc12138_पढ़ो_conv_data(adc, value);
पूर्ण

अटल पूर्णांक adc12138_पढ़ो_raw(काष्ठा iio_dev *iio,
			     काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *value,
			     पूर्णांक *shअगरt, दीर्घ mask)
अणु
	काष्ठा adc12138 *adc = iio_priv(iio);
	पूर्णांक ret;
	__be16 data;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&adc->lock);
		ret = adc12138_adc_conversion(adc, channel, &data);
		mutex_unlock(&adc->lock);
		अगर (ret)
			वापस ret;

		*value = sign_extend32(be16_to_cpu(data) >> 3, 12);

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		ret = regulator_get_voltage(adc->vref_p);
		अगर (ret < 0)
			वापस ret;
		*value = ret;

		अगर (!IS_ERR(adc->vref_n)) अणु
			ret = regulator_get_voltage(adc->vref_n);
			अगर (ret < 0)
				वापस ret;
			*value -= ret;
		पूर्ण

		/* convert regulator output voltage to mV */
		*value /= 1000;
		*shअगरt = channel->scan_type.realbits - 1;

		वापस IIO_VAL_FRACTIONAL_LOG2;
	हाल IIO_CHAN_INFO_OFFSET:
		अगर (!IS_ERR(adc->vref_n)) अणु
			*value = regulator_get_voltage(adc->vref_n);
			अगर (*value < 0)
				वापस *value;
		पूर्ण अन्यथा अणु
			*value = 0;
		पूर्ण

		/* convert regulator output voltage to mV */
		*value /= 1000;

		वापस IIO_VAL_INT;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info adc12138_info = अणु
	.पढ़ो_raw = adc12138_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक adc12138_init(काष्ठा adc12138 *adc)
अणु
	पूर्णांक ret;
	पूर्णांक status;
	u8 mode;
	u8 trash;

	reinit_completion(&adc->complete);

	ret = adc12138_mode_programming(adc, ADC12138_MODE_AUTO_CAL, &trash, 1);
	अगर (ret)
		वापस ret;

	/* data output at this समय has no signअगरicance */
	status = adc12138_पढ़ो_status(adc);
	अगर (status < 0)
		वापस status;

	adc12138_रुको_eoc(adc, msecs_to_jअगरfies(100));

	status = adc12138_पढ़ो_status(adc);
	अगर (status & ADC12138_STATUS_CAL) अणु
		dev_warn(&adc->spi->dev,
			"Auto Cal sequence is still in progress: %#x\n",
			status);
		वापस -EIO;
	पूर्ण

	चयन (adc->acquisition_समय) अणु
	हाल 6:
		mode = ADC12138_MODE_ACQUISITION_TIME_6;
		अवरोध;
	हाल 10:
		mode = ADC12138_MODE_ACQUISITION_TIME_10;
		अवरोध;
	हाल 18:
		mode = ADC12138_MODE_ACQUISITION_TIME_18;
		अवरोध;
	हाल 34:
		mode = ADC12138_MODE_ACQUISITION_TIME_34;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस adc12138_mode_programming(adc, mode, &trash, 1);
पूर्ण

अटल irqवापस_t adc12138_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा adc12138 *adc = iio_priv(indio_dev);
	__be16 trash;
	पूर्णांक ret;
	पूर्णांक scan_index;
	पूर्णांक i = 0;

	mutex_lock(&adc->lock);

	क्रम_each_set_bit(scan_index, indio_dev->active_scan_mask,
			 indio_dev->masklength) अणु
		स्थिर काष्ठा iio_chan_spec *scan_chan =
				&indio_dev->channels[scan_index];

		reinit_completion(&adc->complete);

		ret = adc12138_start_and_पढ़ो_conv(adc, scan_chan,
					i ? &adc->data[i - 1] : &trash);
		अगर (ret) अणु
			dev_warn(&adc->spi->dev,
				 "failed to start conversion\n");
			जाओ out;
		पूर्ण

		ret = adc12138_रुको_eoc(adc, msecs_to_jअगरfies(100));
		अगर (ret) अणु
			dev_warn(&adc->spi->dev, "wait eoc timeout\n");
			जाओ out;
		पूर्ण

		i++;
	पूर्ण

	अगर (i) अणु
		ret = adc12138_पढ़ो_conv_data(adc, &adc->data[i - 1]);
		अगर (ret) अणु
			dev_warn(&adc->spi->dev,
				 "failed to get conversion data\n");
			जाओ out;
		पूर्ण
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, adc->data,
					   iio_get_समय_ns(indio_dev));
out:
	mutex_unlock(&adc->lock);

	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t adc12138_eoc_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_dev *indio_dev = p;
	काष्ठा adc12138 *adc = iio_priv(indio_dev);

	complete(&adc->complete);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक adc12138_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा adc12138 *adc;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*adc));
	अगर (!indio_dev)
		वापस -ENOMEM;

	adc = iio_priv(indio_dev);
	adc->spi = spi;
	adc->id = spi_get_device_id(spi)->driver_data;
	mutex_init(&adc->lock);
	init_completion(&adc->complete);

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &adc12138_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	चयन (adc->id) अणु
	हाल adc12130:
	हाल adc12132:
		indio_dev->channels = adc12132_channels;
		indio_dev->num_channels = ARRAY_SIZE(adc12132_channels);
		अवरोध;
	हाल adc12138:
		indio_dev->channels = adc12138_channels;
		indio_dev->num_channels = ARRAY_SIZE(adc12138_channels);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32(spi->dev.of_node, "ti,acquisition-time",
				   &adc->acquisition_समय);
	अगर (ret)
		adc->acquisition_समय = 10;

	adc->cclk = devm_clk_get(&spi->dev, शून्य);
	अगर (IS_ERR(adc->cclk))
		वापस PTR_ERR(adc->cclk);

	adc->vref_p = devm_regulator_get(&spi->dev, "vref-p");
	अगर (IS_ERR(adc->vref_p))
		वापस PTR_ERR(adc->vref_p);

	adc->vref_n = devm_regulator_get_optional(&spi->dev, "vref-n");
	अगर (IS_ERR(adc->vref_n)) अणु
		/*
		 * Assume vref_n is 0V अगर an optional regulator is not
		 * specअगरied, otherwise वापस the error code.
		 */
		ret = PTR_ERR(adc->vref_n);
		अगर (ret != -ENODEV)
			वापस ret;
	पूर्ण

	ret = devm_request_irq(&spi->dev, spi->irq, adc12138_eoc_handler,
			       IRQF_TRIGGER_RISING, indio_dev->name, indio_dev);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(adc->cclk);
	अगर (ret)
		वापस ret;

	ret = regulator_enable(adc->vref_p);
	अगर (ret)
		जाओ err_clk_disable;

	अगर (!IS_ERR(adc->vref_n)) अणु
		ret = regulator_enable(adc->vref_n);
		अगर (ret)
			जाओ err_vref_p_disable;
	पूर्ण

	ret = adc12138_init(adc);
	अगर (ret)
		जाओ err_vref_n_disable;

	spi_set_drvdata(spi, indio_dev);

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
					 adc12138_trigger_handler, शून्य);
	अगर (ret)
		जाओ err_vref_n_disable;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ err_buffer_cleanup;

	वापस 0;
err_buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
err_vref_n_disable:
	अगर (!IS_ERR(adc->vref_n))
		regulator_disable(adc->vref_n);
err_vref_p_disable:
	regulator_disable(adc->vref_p);
err_clk_disable:
	clk_disable_unprepare(adc->cclk);

	वापस ret;
पूर्ण

अटल पूर्णांक adc12138_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा adc12138 *adc = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	अगर (!IS_ERR(adc->vref_n))
		regulator_disable(adc->vref_n);
	regulator_disable(adc->vref_p);
	clk_disable_unprepare(adc->cclk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF

अटल स्थिर काष्ठा of_device_id adc12138_dt_ids[] = अणु
	अणु .compatible = "ti,adc12130", पूर्ण,
	अणु .compatible = "ti,adc12132", पूर्ण,
	अणु .compatible = "ti,adc12138", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adc12138_dt_ids);

#पूर्ण_अगर

अटल स्थिर काष्ठा spi_device_id adc12138_id[] = अणु
	अणु "adc12130", adc12130 पूर्ण,
	अणु "adc12132", adc12132 पूर्ण,
	अणु "adc12138", adc12138 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, adc12138_id);

अटल काष्ठा spi_driver adc12138_driver = अणु
	.driver = अणु
		.name = "adc12138",
		.of_match_table = of_match_ptr(adc12138_dt_ids),
	पूर्ण,
	.probe = adc12138_probe,
	.हटाओ = adc12138_हटाओ,
	.id_table = adc12138_id,
पूर्ण;
module_spi_driver(adc12138_driver);

MODULE_AUTHOR("Akinobu Mita <akinobu.mita@gmail.com>");
MODULE_DESCRIPTION("ADC12130/ADC12132/ADC12138 driver");
MODULE_LICENSE("GPL v2");
