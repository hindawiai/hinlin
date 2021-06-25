<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Analog Devices AD7466/7/8 AD7476/5/7/8 (A) SPI ADC driver
 * TI ADC081S/ADC101S/ADC121S 8/10/12-bit SPI ADC driver
 *
 * Copyright 2010 Analog Devices Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

काष्ठा ad7476_state;

काष्ठा ad7476_chip_info अणु
	अचिन्हित पूर्णांक			पूर्णांक_vref_uv;
	काष्ठा iio_chan_spec		channel[2];
	/* channels used when convst gpio is defined */
	काष्ठा iio_chan_spec		convst_channel[2];
	व्योम (*reset)(काष्ठा ad7476_state *);
पूर्ण;

काष्ठा ad7476_state अणु
	काष्ठा spi_device		*spi;
	स्थिर काष्ठा ad7476_chip_info	*chip_info;
	काष्ठा regulator		*reg;
	काष्ठा gpio_desc		*convst_gpio;
	काष्ठा spi_transfer		xfer;
	काष्ठा spi_message		msg;
	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 * Make the buffer large enough क्रम one 16 bit sample and one 64 bit
	 * aligned 64 bit बारtamp.
	 */
	अचिन्हित अक्षर data[ALIGN(2, माप(s64)) + माप(s64)]
			____cacheline_aligned;
पूर्ण;

क्रमागत ad7476_supported_device_ids अणु
	ID_AD7091R,
	ID_AD7276,
	ID_AD7277,
	ID_AD7278,
	ID_AD7466,
	ID_AD7467,
	ID_AD7468,
	ID_AD7495,
	ID_AD7940,
	ID_ADC081S,
	ID_ADC101S,
	ID_ADC121S,
	ID_ADS7866,
	ID_ADS7867,
	ID_ADS7868,
	ID_LTC2314_14,
पूर्ण;

अटल व्योम ad7091_convst(काष्ठा ad7476_state *st)
अणु
	अगर (!st->convst_gpio)
		वापस;

	gpiod_set_value(st->convst_gpio, 0);
	udelay(1); /* CONVST pulse width: 10 ns min */
	gpiod_set_value(st->convst_gpio, 1);
	udelay(1); /* Conversion समय: 650 ns max */
पूर्ण

अटल irqवापस_t ad7476_trigger_handler(पूर्णांक irq, व्योम  *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा ad7476_state *st = iio_priv(indio_dev);
	पूर्णांक b_sent;

	ad7091_convst(st);

	b_sent = spi_sync(st->spi, &st->msg);
	अगर (b_sent < 0)
		जाओ करोne;

	iio_push_to_buffers_with_बारtamp(indio_dev, st->data,
		iio_get_समय_ns(indio_dev));
करोne:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ad7091_reset(काष्ठा ad7476_state *st)
अणु
	/* Any transfers with 8 scl cycles will reset the device */
	spi_पढ़ो(st->spi, st->data, 1);
पूर्ण

अटल पूर्णांक ad7476_scan_direct(काष्ठा ad7476_state *st)
अणु
	पूर्णांक ret;

	ad7091_convst(st);

	ret = spi_sync(st->spi, &st->msg);
	अगर (ret)
		वापस ret;

	वापस be16_to_cpup((__be16 *)st->data);
पूर्ण

अटल पूर्णांक ad7476_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	पूर्णांक ret;
	काष्ठा ad7476_state *st = iio_priv(indio_dev);
	पूर्णांक scale_uv;

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		ret = ad7476_scan_direct(st);
		iio_device_release_direct_mode(indio_dev);

		अगर (ret < 0)
			वापस ret;
		*val = (ret >> st->chip_info->channel[0].scan_type.shअगरt) &
			GENMASK(st->chip_info->channel[0].scan_type.realbits - 1, 0);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (!st->chip_info->पूर्णांक_vref_uv) अणु
			scale_uv = regulator_get_voltage(st->reg);
			अगर (scale_uv < 0)
				वापस scale_uv;
		पूर्ण अन्यथा अणु
			scale_uv = st->chip_info->पूर्णांक_vref_uv;
		पूर्ण
		*val = scale_uv / 1000;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	पूर्ण
	वापस -EINVAL;
पूर्ण

#घोषणा _AD7476_CHAN(bits, _shअगरt, _info_mask_sep)		\
	अणु							\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.info_mask_separate = _info_mask_sep,			\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
	.scan_type = अणु						\
		.sign = 'u',					\
		.realbits = (bits),				\
		.storagebits = 16,				\
		.shअगरt = (_shअगरt),				\
		.endianness = IIO_BE,				\
	पूर्ण,							\
पूर्ण

#घोषणा ADC081S_CHAN(bits) _AD7476_CHAN((bits), 12 - (bits), \
		BIT(IIO_CHAN_INFO_RAW))
#घोषणा AD7476_CHAN(bits) _AD7476_CHAN((bits), 13 - (bits), \
		BIT(IIO_CHAN_INFO_RAW))
#घोषणा AD7940_CHAN(bits) _AD7476_CHAN((bits), 15 - (bits), \
		BIT(IIO_CHAN_INFO_RAW))
#घोषणा AD7091R_CHAN(bits) _AD7476_CHAN((bits), 16 - (bits), 0)
#घोषणा AD7091R_CONVST_CHAN(bits) _AD7476_CHAN((bits), 16 - (bits), \
		BIT(IIO_CHAN_INFO_RAW))
#घोषणा ADS786X_CHAN(bits) _AD7476_CHAN((bits), 12 - (bits), \
		BIT(IIO_CHAN_INFO_RAW))

अटल स्थिर काष्ठा ad7476_chip_info ad7476_chip_info_tbl[] = अणु
	[ID_AD7091R] = अणु
		.channel[0] = AD7091R_CHAN(12),
		.channel[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
		.convst_channel[0] = AD7091R_CONVST_CHAN(12),
		.convst_channel[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
		.reset = ad7091_reset,
	पूर्ण,
	[ID_AD7276] = अणु
		.channel[0] = AD7940_CHAN(12),
		.channel[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	पूर्ण,
	[ID_AD7277] = अणु
		.channel[0] = AD7940_CHAN(10),
		.channel[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	पूर्ण,
	[ID_AD7278] = अणु
		.channel[0] = AD7940_CHAN(8),
		.channel[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	पूर्ण,
	[ID_AD7466] = अणु
		.channel[0] = AD7476_CHAN(12),
		.channel[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	पूर्ण,
	[ID_AD7467] = अणु
		.channel[0] = AD7476_CHAN(10),
		.channel[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	पूर्ण,
	[ID_AD7468] = अणु
		.channel[0] = AD7476_CHAN(8),
		.channel[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	पूर्ण,
	[ID_AD7495] = अणु
		.channel[0] = AD7476_CHAN(12),
		.channel[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
		.पूर्णांक_vref_uv = 2500000,
	पूर्ण,
	[ID_AD7940] = अणु
		.channel[0] = AD7940_CHAN(14),
		.channel[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	पूर्ण,
	[ID_ADC081S] = अणु
		.channel[0] = ADC081S_CHAN(8),
		.channel[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	पूर्ण,
	[ID_ADC101S] = अणु
		.channel[0] = ADC081S_CHAN(10),
		.channel[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	पूर्ण,
	[ID_ADC121S] = अणु
		.channel[0] = ADC081S_CHAN(12),
		.channel[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	पूर्ण,
	[ID_ADS7866] = अणु
		.channel[0] = ADS786X_CHAN(12),
		.channel[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	पूर्ण,
	[ID_ADS7867] = अणु
		.channel[0] = ADS786X_CHAN(10),
		.channel[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	पूर्ण,
	[ID_ADS7868] = अणु
		.channel[0] = ADS786X_CHAN(8),
		.channel[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	पूर्ण,
	[ID_LTC2314_14] = अणु
		.channel[0] = AD7940_CHAN(14),
		.channel[1] = IIO_CHAN_SOFT_TIMESTAMP(1),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_info ad7476_info = अणु
	.पढ़ो_raw = &ad7476_पढ़ो_raw,
पूर्ण;

अटल व्योम ad7476_reg_disable(व्योम *data)
अणु
	काष्ठा ad7476_state *st = data;

	regulator_disable(st->reg);
पूर्ण

अटल पूर्णांक ad7476_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad7476_state *st;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	st->chip_info =
		&ad7476_chip_info_tbl[spi_get_device_id(spi)->driver_data];

	st->reg = devm_regulator_get(&spi->dev, "vcc");
	अगर (IS_ERR(st->reg))
		वापस PTR_ERR(st->reg);

	ret = regulator_enable(st->reg);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(&spi->dev, ad7476_reg_disable,
				       st);
	अगर (ret)
		वापस ret;

	st->convst_gpio = devm_gpiod_get_optional(&spi->dev,
						  "adi,conversion-start",
						  GPIOD_OUT_LOW);
	अगर (IS_ERR(st->convst_gpio))
		वापस PTR_ERR(st->convst_gpio);

	spi_set_drvdata(spi, indio_dev);

	st->spi = spi;

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = st->chip_info->channel;
	indio_dev->num_channels = 2;
	indio_dev->info = &ad7476_info;

	अगर (st->convst_gpio)
		indio_dev->channels = st->chip_info->convst_channel;
	/* Setup शेष message */

	st->xfer.rx_buf = &st->data;
	st->xfer.len = st->chip_info->channel[0].scan_type.storagebits / 8;

	spi_message_init(&st->msg);
	spi_message_add_tail(&st->xfer, &st->msg);

	ret = devm_iio_triggered_buffer_setup(&spi->dev, indio_dev, शून्य,
					      &ad7476_trigger_handler, शून्य);
	अगर (ret)
		वापस ret;

	अगर (st->chip_info->reset)
		st->chip_info->reset(st);

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad7476_id[] = अणु
	अणु"ad7091", ID_AD7091Rपूर्ण,
	अणु"ad7091r", ID_AD7091Rपूर्ण,
	अणु"ad7273", ID_AD7277पूर्ण,
	अणु"ad7274", ID_AD7276पूर्ण,
	अणु"ad7276", ID_AD7276पूर्ण,
	अणु"ad7277", ID_AD7277पूर्ण,
	अणु"ad7278", ID_AD7278पूर्ण,
	अणु"ad7466", ID_AD7466पूर्ण,
	अणु"ad7467", ID_AD7467पूर्ण,
	अणु"ad7468", ID_AD7468पूर्ण,
	अणु"ad7475", ID_AD7466पूर्ण,
	अणु"ad7476", ID_AD7466पूर्ण,
	अणु"ad7476a", ID_AD7466पूर्ण,
	अणु"ad7477", ID_AD7467पूर्ण,
	अणु"ad7477a", ID_AD7467पूर्ण,
	अणु"ad7478", ID_AD7468पूर्ण,
	अणु"ad7478a", ID_AD7468पूर्ण,
	अणु"ad7495", ID_AD7495पूर्ण,
	अणु"ad7910", ID_AD7467पूर्ण,
	अणु"ad7920", ID_AD7466पूर्ण,
	अणु"ad7940", ID_AD7940पूर्ण,
	अणु"adc081s", ID_ADC081Sपूर्ण,
	अणु"adc101s", ID_ADC101Sपूर्ण,
	अणु"adc121s", ID_ADC121Sपूर्ण,
	अणु"ads7866", ID_ADS7866पूर्ण,
	अणु"ads7867", ID_ADS7867पूर्ण,
	अणु"ads7868", ID_ADS7868पूर्ण,
	अणु"ltc2314-14", ID_LTC2314_14पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad7476_id);

अटल काष्ठा spi_driver ad7476_driver = अणु
	.driver = अणु
		.name	= "ad7476",
	पूर्ण,
	.probe		= ad7476_probe,
	.id_table	= ad7476_id,
पूर्ण;
module_spi_driver(ad7476_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD7476 and similar 1-channel ADCs");
MODULE_LICENSE("GPL v2");
