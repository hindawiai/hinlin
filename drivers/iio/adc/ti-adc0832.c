<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ADC0831/ADC0832/ADC0834/ADC0838 8-bit ADC driver
 *
 * Copyright (c) 2016 Akinobu Mita <akinobu.mita@gmail.com>
 *
 * Datasheet: https://www.ti.com/lit/ds/symlink/adc0832-n.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>

क्रमागत अणु
	adc0831,
	adc0832,
	adc0834,
	adc0838,
पूर्ण;

काष्ठा adc0832 अणु
	काष्ठा spi_device *spi;
	काष्ठा regulator *reg;
	काष्ठा mutex lock;
	u8 mux_bits;
	/*
	 * Max size needed: 16x 1 byte ADC data + 8 bytes बारtamp
	 * May be लघुer अगर not all channels are enabled subject
	 * to the बारtamp reमुख्यing 8 byte aligned.
	 */
	u8 data[24] __aligned(8);

	u8 tx_buf[2] ____cacheline_aligned;
	u8 rx_buf[2];
पूर्ण;

#घोषणा ADC0832_VOLTAGE_CHANNEL(chan)					\
	अणु								\
		.type = IIO_VOLTAGE,					\
		.indexed = 1,						\
		.channel = chan,					\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
		.scan_index = chan,					\
		.scan_type = अणु						\
			.sign = 'u',					\
			.realbits = 8,					\
			.storagebits = 8,				\
		पूर्ण,							\
	पूर्ण

#घोषणा ADC0832_VOLTAGE_CHANNEL_DIFF(chan1, chan2, si)			\
	अणु								\
		.type = IIO_VOLTAGE,					\
		.indexed = 1,						\
		.channel = (chan1),					\
		.channel2 = (chan2),					\
		.dअगरferential = 1,					\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
		.scan_index = si,					\
		.scan_type = अणु						\
			.sign = 'u',					\
			.realbits = 8,					\
			.storagebits = 8,				\
		पूर्ण,							\
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec adc0831_channels[] = अणु
	ADC0832_VOLTAGE_CHANNEL_DIFF(0, 1, 0),
	IIO_CHAN_SOFT_TIMESTAMP(1),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec adc0832_channels[] = अणु
	ADC0832_VOLTAGE_CHANNEL(0),
	ADC0832_VOLTAGE_CHANNEL(1),
	ADC0832_VOLTAGE_CHANNEL_DIFF(0, 1, 2),
	ADC0832_VOLTAGE_CHANNEL_DIFF(1, 0, 3),
	IIO_CHAN_SOFT_TIMESTAMP(4),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec adc0834_channels[] = अणु
	ADC0832_VOLTAGE_CHANNEL(0),
	ADC0832_VOLTAGE_CHANNEL(1),
	ADC0832_VOLTAGE_CHANNEL(2),
	ADC0832_VOLTAGE_CHANNEL(3),
	ADC0832_VOLTAGE_CHANNEL_DIFF(0, 1, 4),
	ADC0832_VOLTAGE_CHANNEL_DIFF(1, 0, 5),
	ADC0832_VOLTAGE_CHANNEL_DIFF(2, 3, 6),
	ADC0832_VOLTAGE_CHANNEL_DIFF(3, 2, 7),
	IIO_CHAN_SOFT_TIMESTAMP(8),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec adc0838_channels[] = अणु
	ADC0832_VOLTAGE_CHANNEL(0),
	ADC0832_VOLTAGE_CHANNEL(1),
	ADC0832_VOLTAGE_CHANNEL(2),
	ADC0832_VOLTAGE_CHANNEL(3),
	ADC0832_VOLTAGE_CHANNEL(4),
	ADC0832_VOLTAGE_CHANNEL(5),
	ADC0832_VOLTAGE_CHANNEL(6),
	ADC0832_VOLTAGE_CHANNEL(7),
	ADC0832_VOLTAGE_CHANNEL_DIFF(0, 1, 8),
	ADC0832_VOLTAGE_CHANNEL_DIFF(1, 0, 9),
	ADC0832_VOLTAGE_CHANNEL_DIFF(2, 3, 10),
	ADC0832_VOLTAGE_CHANNEL_DIFF(3, 2, 11),
	ADC0832_VOLTAGE_CHANNEL_DIFF(4, 5, 12),
	ADC0832_VOLTAGE_CHANNEL_DIFF(5, 4, 13),
	ADC0832_VOLTAGE_CHANNEL_DIFF(6, 7, 14),
	ADC0832_VOLTAGE_CHANNEL_DIFF(7, 6, 15),
	IIO_CHAN_SOFT_TIMESTAMP(16),
पूर्ण;

अटल पूर्णांक adc0831_adc_conversion(काष्ठा adc0832 *adc)
अणु
	काष्ठा spi_device *spi = adc->spi;
	पूर्णांक ret;

	ret = spi_पढ़ो(spi, &adc->rx_buf, 2);
	अगर (ret)
		वापस ret;

	/*
	 * Skip TRI-STATE and a leading zero
	 */
	वापस (adc->rx_buf[0] << 2 & 0xff) | (adc->rx_buf[1] >> 6);
पूर्ण

अटल पूर्णांक adc0832_adc_conversion(काष्ठा adc0832 *adc, पूर्णांक channel,
				bool dअगरferential)
अणु
	काष्ठा spi_device *spi = adc->spi;
	काष्ठा spi_transfer xfer = अणु
		.tx_buf = adc->tx_buf,
		.rx_buf = adc->rx_buf,
		.len = 2,
	पूर्ण;
	पूर्णांक ret;

	अगर (!adc->mux_bits)
		वापस adc0831_adc_conversion(adc);

	/* start bit */
	adc->tx_buf[0] = 1 << (adc->mux_bits + 1);
	/* single-ended or dअगरferential */
	adc->tx_buf[0] |= dअगरferential ? 0 : (1 << adc->mux_bits);
	/* odd / sign */
	adc->tx_buf[0] |= (channel % 2) << (adc->mux_bits - 1);
	/* select */
	अगर (adc->mux_bits > 1)
		adc->tx_buf[0] |= channel / 2;

	/* align Data output BIT7 (MSB) to 8-bit boundary */
	adc->tx_buf[0] <<= 1;

	ret = spi_sync_transfer(spi, &xfer, 1);
	अगर (ret)
		वापस ret;

	वापस adc->rx_buf[1];
पूर्ण

अटल पूर्णांक adc0832_पढ़ो_raw(काष्ठा iio_dev *iio,
			काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *value,
			पूर्णांक *shअगरt, दीर्घ mask)
अणु
	काष्ठा adc0832 *adc = iio_priv(iio);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&adc->lock);
		*value = adc0832_adc_conversion(adc, channel->channel,
						channel->dअगरferential);
		mutex_unlock(&adc->lock);
		अगर (*value < 0)
			वापस *value;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*value = regulator_get_voltage(adc->reg);
		अगर (*value < 0)
			वापस *value;

		/* convert regulator output voltage to mV */
		*value /= 1000;
		*shअगरt = 8;

		वापस IIO_VAL_FRACTIONAL_LOG2;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info adc0832_info = अणु
	.पढ़ो_raw = adc0832_पढ़ो_raw,
पूर्ण;

अटल irqवापस_t adc0832_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा adc0832 *adc = iio_priv(indio_dev);
	पूर्णांक scan_index;
	पूर्णांक i = 0;

	mutex_lock(&adc->lock);

	क्रम_each_set_bit(scan_index, indio_dev->active_scan_mask,
			 indio_dev->masklength) अणु
		स्थिर काष्ठा iio_chan_spec *scan_chan =
				&indio_dev->channels[scan_index];
		पूर्णांक ret = adc0832_adc_conversion(adc, scan_chan->channel,
						 scan_chan->dअगरferential);
		अगर (ret < 0) अणु
			dev_warn(&adc->spi->dev,
				 "failed to get conversion data\n");
			जाओ out;
		पूर्ण

		adc->data[i] = ret;
		i++;
	पूर्ण
	iio_push_to_buffers_with_बारtamp(indio_dev, adc->data,
					   iio_get_समय_ns(indio_dev));
out:
	mutex_unlock(&adc->lock);

	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक adc0832_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा adc0832 *adc;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*adc));
	अगर (!indio_dev)
		वापस -ENOMEM;

	adc = iio_priv(indio_dev);
	adc->spi = spi;
	mutex_init(&adc->lock);

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &adc0832_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	चयन (spi_get_device_id(spi)->driver_data) अणु
	हाल adc0831:
		adc->mux_bits = 0;
		indio_dev->channels = adc0831_channels;
		indio_dev->num_channels = ARRAY_SIZE(adc0831_channels);
		अवरोध;
	हाल adc0832:
		adc->mux_bits = 1;
		indio_dev->channels = adc0832_channels;
		indio_dev->num_channels = ARRAY_SIZE(adc0832_channels);
		अवरोध;
	हाल adc0834:
		adc->mux_bits = 2;
		indio_dev->channels = adc0834_channels;
		indio_dev->num_channels = ARRAY_SIZE(adc0834_channels);
		अवरोध;
	हाल adc0838:
		adc->mux_bits = 3;
		indio_dev->channels = adc0838_channels;
		indio_dev->num_channels = ARRAY_SIZE(adc0838_channels);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	adc->reg = devm_regulator_get(&spi->dev, "vref");
	अगर (IS_ERR(adc->reg))
		वापस PTR_ERR(adc->reg);

	ret = regulator_enable(adc->reg);
	अगर (ret)
		वापस ret;

	spi_set_drvdata(spi, indio_dev);

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
					 adc0832_trigger_handler, शून्य);
	अगर (ret)
		जाओ err_reg_disable;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ err_buffer_cleanup;

	वापस 0;
err_buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
err_reg_disable:
	regulator_disable(adc->reg);

	वापस ret;
पूर्ण

अटल पूर्णांक adc0832_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा adc0832 *adc = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	regulator_disable(adc->reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id adc0832_dt_ids[] = अणु
	अणु .compatible = "ti,adc0831", पूर्ण,
	अणु .compatible = "ti,adc0832", पूर्ण,
	अणु .compatible = "ti,adc0834", पूर्ण,
	अणु .compatible = "ti,adc0838", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adc0832_dt_ids);

अटल स्थिर काष्ठा spi_device_id adc0832_id[] = अणु
	अणु "adc0831", adc0831 पूर्ण,
	अणु "adc0832", adc0832 पूर्ण,
	अणु "adc0834", adc0834 पूर्ण,
	अणु "adc0838", adc0838 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, adc0832_id);

अटल काष्ठा spi_driver adc0832_driver = अणु
	.driver = अणु
		.name = "adc0832",
		.of_match_table = adc0832_dt_ids,
	पूर्ण,
	.probe = adc0832_probe,
	.हटाओ = adc0832_हटाओ,
	.id_table = adc0832_id,
पूर्ण;
module_spi_driver(adc0832_driver);

MODULE_AUTHOR("Akinobu Mita <akinobu.mita@gmail.com>");
MODULE_DESCRIPTION("ADC0831/ADC0832/ADC0834/ADC0838 driver");
MODULE_LICENSE("GPL v2");
