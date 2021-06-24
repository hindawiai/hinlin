<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 Axis Communications AB
 *
 * Driver क्रम Texas Instruments' ADC084S021 ADC chip.
 * Datasheets can be found here:
 * https://www.ti.com/lit/ds/symlink/adc084s021.pdf
 */

#समावेश <linux/err.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/regulator/consumer.h>

#घोषणा ADC084S021_DRIVER_NAME "adc084s021"

काष्ठा adc084s021 अणु
	काष्ठा spi_device *spi;
	काष्ठा spi_message message;
	काष्ठा spi_transfer spi_trans;
	काष्ठा regulator *reg;
	काष्ठा mutex lock;
	/* Buffer used to align data */
	काष्ठा अणु
		__be16 channels[4];
		s64 ts __aligned(8);
	पूर्ण scan;
	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache line.
	 */
	u16 tx_buf[4] ____cacheline_aligned;
	__be16 rx_buf[5]; /* First 16-bits are trash */
पूर्ण;

#घोषणा ADC084S021_VOLTAGE_CHANNEL(num)                  \
	अणु                                                      \
		.type = IIO_VOLTAGE,                                 \
		.channel = (num),                                    \
		.indexed = 1,                                        \
		.scan_index = (num),                                 \
		.scan_type = अणु                                       \
			.sign = 'u',                                       \
			.realbits = 8,                                     \
			.storagebits = 16,                                 \
			.shअगरt = 4,                                        \
			.endianness = IIO_BE,                              \
		पूर्ण,                                                   \
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),        \
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),\
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec adc084s021_channels[] = अणु
	ADC084S021_VOLTAGE_CHANNEL(0),
	ADC084S021_VOLTAGE_CHANNEL(1),
	ADC084S021_VOLTAGE_CHANNEL(2),
	ADC084S021_VOLTAGE_CHANNEL(3),
	IIO_CHAN_SOFT_TIMESTAMP(4),
पूर्ण;

/**
 * adc084s021_adc_conversion() - Read an ADC channel and वापस its value.
 *
 * @adc: The ADC SPI data.
 * @data: Buffer क्रम converted data.
 */
अटल पूर्णांक adc084s021_adc_conversion(काष्ठा adc084s021 *adc, __be16 *data)
अणु
	पूर्णांक n_words = (adc->spi_trans.len >> 1) - 1; /* Discard first word */
	पूर्णांक ret, i = 0;

	/* Do the transfer */
	ret = spi_sync(adc->spi, &adc->message);
	अगर (ret < 0)
		वापस ret;

	क्रम (; i < n_words; i++)
		*(data + i) = adc->rx_buf[i + 1];

	वापस ret;
पूर्ण

अटल पूर्णांक adc084s021_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *channel, पूर्णांक *val,
			   पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा adc084s021 *adc = iio_priv(indio_dev);
	पूर्णांक ret;
	__be16 be_val;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret < 0)
			वापस ret;

		ret = regulator_enable(adc->reg);
		अगर (ret) अणु
			iio_device_release_direct_mode(indio_dev);
			वापस ret;
		पूर्ण

		adc->tx_buf[0] = channel->channel << 3;
		ret = adc084s021_adc_conversion(adc, &be_val);
		iio_device_release_direct_mode(indio_dev);
		regulator_disable(adc->reg);
		अगर (ret < 0)
			वापस ret;

		*val = be16_to_cpu(be_val);
		*val = (*val >> channel->scan_type.shअगरt) & 0xff;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		ret = regulator_enable(adc->reg);
		अगर (ret)
			वापस ret;

		ret = regulator_get_voltage(adc->reg);
		regulator_disable(adc->reg);
		अगर (ret < 0)
			वापस ret;

		*val = ret / 1000;

		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * adc084s021_buffer_trigger_handler() - Read ADC channels and push to buffer.
 *
 * @irq: The पूर्णांकerrupt number (not used).
 * @pollfunc: Poपूर्णांकer to the poll func.
 */
अटल irqवापस_t adc084s021_buffer_trigger_handler(पूर्णांक irq, व्योम *pollfunc)
अणु
	काष्ठा iio_poll_func *pf = pollfunc;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा adc084s021 *adc = iio_priv(indio_dev);

	mutex_lock(&adc->lock);

	अगर (adc084s021_adc_conversion(adc, adc->scan.channels) < 0)
		dev_err(&adc->spi->dev, "Failed to read data\n");

	iio_push_to_buffers_with_बारtamp(indio_dev, &adc->scan,
					   iio_get_समय_ns(indio_dev));
	mutex_unlock(&adc->lock);
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक adc084s021_buffer_preenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा adc084s021 *adc = iio_priv(indio_dev);
	पूर्णांक scan_index;
	पूर्णांक i = 0;

	क्रम_each_set_bit(scan_index, indio_dev->active_scan_mask,
			 indio_dev->masklength) अणु
		स्थिर काष्ठा iio_chan_spec *channel =
			&indio_dev->channels[scan_index];
		adc->tx_buf[i++] = channel->channel << 3;
	पूर्ण
	adc->spi_trans.len = 2 + (i * माप(__be16)); /* Trash + channels */

	वापस regulator_enable(adc->reg);
पूर्ण

अटल पूर्णांक adc084s021_buffer_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा adc084s021 *adc = iio_priv(indio_dev);

	adc->spi_trans.len = 4; /* Trash + single channel */

	वापस regulator_disable(adc->reg);
पूर्ण

अटल स्थिर काष्ठा iio_info adc084s021_info = अणु
	.पढ़ो_raw = adc084s021_पढ़ो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_buffer_setup_ops adc084s021_buffer_setup_ops = अणु
	.preenable = adc084s021_buffer_preenable,
	.postdisable = adc084s021_buffer_postdisable,
पूर्ण;

अटल पूर्णांक adc084s021_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा adc084s021 *adc;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*adc));
	अगर (!indio_dev) अणु
		dev_err(&spi->dev, "Failed to allocate IIO device\n");
		वापस -ENOMEM;
	पूर्ण

	adc = iio_priv(indio_dev);
	adc->spi = spi;

	/* Connect the SPI device and the iio dev */
	spi_set_drvdata(spi, indio_dev);

	/* Initiate the Industrial I/O device */
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &adc084s021_info;
	indio_dev->channels = adc084s021_channels;
	indio_dev->num_channels = ARRAY_SIZE(adc084s021_channels);

	/* Create SPI transfer क्रम channel पढ़ोs */
	adc->spi_trans.tx_buf = adc->tx_buf;
	adc->spi_trans.rx_buf = adc->rx_buf;
	adc->spi_trans.len = 4; /* Trash + single channel */
	spi_message_init_with_transfers(&adc->message, &adc->spi_trans, 1);

	adc->reg = devm_regulator_get(&spi->dev, "vref");
	अगर (IS_ERR(adc->reg))
		वापस PTR_ERR(adc->reg);

	mutex_init(&adc->lock);

	/* Setup triggered buffer with pollfunction */
	ret = devm_iio_triggered_buffer_setup(&spi->dev, indio_dev, शून्य,
					    adc084s021_buffer_trigger_handler,
					    &adc084s021_buffer_setup_ops);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to setup triggered buffer\n");
		वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id adc084s021_of_match[] = अणु
	अणु .compatible = "ti,adc084s021", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, adc084s021_of_match);

अटल स्थिर काष्ठा spi_device_id adc084s021_id[] = अणु
	अणु ADC084S021_DRIVER_NAME, 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, adc084s021_id);

अटल काष्ठा spi_driver adc084s021_driver = अणु
	.driver = अणु
		.name = ADC084S021_DRIVER_NAME,
		.of_match_table = adc084s021_of_match,
	पूर्ण,
	.probe = adc084s021_probe,
	.id_table = adc084s021_id,
पूर्ण;
module_spi_driver(adc084s021_driver);

MODULE_AUTHOR("Mथआrten Lindahl <martenli@axis.com>");
MODULE_DESCRIPTION("Texas Instruments ADC084S021");
MODULE_LICENSE("GPL v2");
MODULE_VERSION("1.0");
