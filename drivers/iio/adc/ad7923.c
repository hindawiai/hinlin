<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AD7904/AD7914/AD7923/AD7924/AD7908/AD7918/AD7928 SPI ADC driver
 *
 * Copyright 2011 Analog Devices Inc (from AD7923 Driver)
 * Copyright 2012 CS Systemes d'Inक्रमmation
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#घोषणा AD7923_WRITE_CR		BIT(11)		/* ग_लिखो control रेजिस्टर */
#घोषणा AD7923_RANGE		BIT(1)		/* range to REFin */
#घोषणा AD7923_CODING		BIT(0)		/* coding is straight binary */
#घोषणा AD7923_PM_MODE_AS	(1)		/* स्वतः shutकरोwn */
#घोषणा AD7923_PM_MODE_FS	(2)		/* full shutकरोwn */
#घोषणा AD7923_PM_MODE_OPS	(3)		/* normal operation */
#घोषणा AD7923_SEQUENCE_OFF	(0)		/* no sequence fonction */
#घोषणा AD7923_SEQUENCE_PROTECT	(2)		/* no पूर्णांकerrupt ग_लिखो cycle */
#घोषणा AD7923_SEQUENCE_ON	(3)		/* continuous sequence */


#घोषणा AD7923_PM_MODE_WRITE(mode)	((mode) << 4)	 /* ग_लिखो mode */
#घोषणा AD7923_CHANNEL_WRITE(channel)	((channel) << 6) /* ग_लिखो channel */
#घोषणा AD7923_SEQUENCE_WRITE(sequence)	((((sequence) & 1) << 3) \
					+ (((sequence) & 2) << 9))
						/* ग_लिखो sequence fonction */
/* left shअगरt क्रम CR : bit 11 transmit in first */
#घोषणा AD7923_SHIFT_REGISTER	4

/* val = value, dec = left shअगरt, bits = number of bits of the mask */
#घोषणा EXTRACT(val, dec, bits)		(((val) >> (dec)) & ((1 << (bits)) - 1))

काष्ठा ad7923_state अणु
	काष्ठा spi_device		*spi;
	काष्ठा spi_transfer		ring_xfer[5];
	काष्ठा spi_transfer		scan_single_xfer[2];
	काष्ठा spi_message		ring_msg;
	काष्ठा spi_message		scan_single_msg;

	काष्ठा regulator		*reg;

	अचिन्हित पूर्णांक			settings;

	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 * Ensure rx_buf can be directly used in iio_push_to_buffers_with_समयtamp
	 * Length = 8 channels + 4 extra क्रम 8 byte बारtamp
	 */
	__be16				rx_buf[12] ____cacheline_aligned;
	__be16				tx_buf[4];
पूर्ण;

काष्ठा ad7923_chip_info अणु
	स्थिर काष्ठा iio_chan_spec *channels;
	अचिन्हित पूर्णांक num_channels;
पूर्ण;

क्रमागत ad7923_id अणु
	AD7904,
	AD7914,
	AD7924,
	AD7908,
	AD7918,
	AD7928
पूर्ण;

#घोषणा AD7923_V_CHAN(index, bits)					\
	अणु								\
		.type = IIO_VOLTAGE,					\
		.indexed = 1,						\
		.channel = index,					\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
		.address = index,					\
		.scan_index = index,					\
		.scan_type = अणु						\
			.sign = 'u',					\
			.realbits = (bits),				\
			.storagebits = 16,				\
			.endianness = IIO_BE,				\
		पूर्ण,							\
	पूर्ण

#घोषणा DECLARE_AD7923_CHANNELS(name, bits) \
स्थिर काष्ठा iio_chan_spec name ## _channels[] = अणु \
	AD7923_V_CHAN(0, bits), \
	AD7923_V_CHAN(1, bits), \
	AD7923_V_CHAN(2, bits), \
	AD7923_V_CHAN(3, bits), \
	IIO_CHAN_SOFT_TIMESTAMP(4), \
पूर्ण

#घोषणा DECLARE_AD7908_CHANNELS(name, bits) \
स्थिर काष्ठा iio_chan_spec name ## _channels[] = अणु \
	AD7923_V_CHAN(0, bits), \
	AD7923_V_CHAN(1, bits), \
	AD7923_V_CHAN(2, bits), \
	AD7923_V_CHAN(3, bits), \
	AD7923_V_CHAN(4, bits), \
	AD7923_V_CHAN(5, bits), \
	AD7923_V_CHAN(6, bits), \
	AD7923_V_CHAN(7, bits), \
	IIO_CHAN_SOFT_TIMESTAMP(8), \
पूर्ण

अटल DECLARE_AD7923_CHANNELS(ad7904, 8);
अटल DECLARE_AD7923_CHANNELS(ad7914, 10);
अटल DECLARE_AD7923_CHANNELS(ad7924, 12);
अटल DECLARE_AD7908_CHANNELS(ad7908, 8);
अटल DECLARE_AD7908_CHANNELS(ad7918, 10);
अटल DECLARE_AD7908_CHANNELS(ad7928, 12);

अटल स्थिर काष्ठा ad7923_chip_info ad7923_chip_info[] = अणु
	[AD7904] = अणु
		.channels = ad7904_channels,
		.num_channels = ARRAY_SIZE(ad7904_channels),
	पूर्ण,
	[AD7914] = अणु
		.channels = ad7914_channels,
		.num_channels = ARRAY_SIZE(ad7914_channels),
	पूर्ण,
	[AD7924] = अणु
		.channels = ad7924_channels,
		.num_channels = ARRAY_SIZE(ad7924_channels),
	पूर्ण,
	[AD7908] = अणु
		.channels = ad7908_channels,
		.num_channels = ARRAY_SIZE(ad7908_channels),
	पूर्ण,
	[AD7918] = अणु
		.channels = ad7918_channels,
		.num_channels = ARRAY_SIZE(ad7918_channels),
	पूर्ण,
	[AD7928] = अणु
		.channels = ad7928_channels,
		.num_channels = ARRAY_SIZE(ad7928_channels),
	पूर्ण,
पूर्ण;

/*
 * ad7923_update_scan_mode() setup the spi transfer buffer क्रम the new scan mask
 */
अटल पूर्णांक ad7923_update_scan_mode(काष्ठा iio_dev *indio_dev,
				   स्थिर अचिन्हित दीर्घ *active_scan_mask)
अणु
	काष्ठा ad7923_state *st = iio_priv(indio_dev);
	पूर्णांक i, cmd, len;

	len = 0;
	/*
	 * For this driver the last channel is always the software बारtamp so
	 * skip that one.
	 */
	क्रम_each_set_bit(i, active_scan_mask, indio_dev->num_channels - 1) अणु
		cmd = AD7923_WRITE_CR | AD7923_CHANNEL_WRITE(i) |
			AD7923_SEQUENCE_WRITE(AD7923_SEQUENCE_OFF) |
			st->settings;
		cmd <<= AD7923_SHIFT_REGISTER;
		st->tx_buf[len++] = cpu_to_be16(cmd);
	पूर्ण
	/* build spi ring message */
	st->ring_xfer[0].tx_buf = &st->tx_buf[0];
	st->ring_xfer[0].len = len;
	st->ring_xfer[0].cs_change = 1;

	spi_message_init(&st->ring_msg);
	spi_message_add_tail(&st->ring_xfer[0], &st->ring_msg);

	क्रम (i = 0; i < len; i++) अणु
		st->ring_xfer[i + 1].rx_buf = &st->rx_buf[i];
		st->ring_xfer[i + 1].len = 2;
		st->ring_xfer[i + 1].cs_change = 1;
		spi_message_add_tail(&st->ring_xfer[i + 1], &st->ring_msg);
	पूर्ण
	/* make sure last transfer cs_change is not set */
	st->ring_xfer[i + 1].cs_change = 0;

	वापस 0;
पूर्ण

अटल irqवापस_t ad7923_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा ad7923_state *st = iio_priv(indio_dev);
	पूर्णांक b_sent;

	b_sent = spi_sync(st->spi, &st->ring_msg);
	अगर (b_sent)
		जाओ करोne;

	iio_push_to_buffers_with_बारtamp(indio_dev, st->rx_buf,
					   iio_get_समय_ns(indio_dev));

करोne:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ad7923_scan_direct(काष्ठा ad7923_state *st, अचिन्हित पूर्णांक ch)
अणु
	पूर्णांक ret, cmd;

	cmd = AD7923_WRITE_CR | AD7923_CHANNEL_WRITE(ch) |
		AD7923_SEQUENCE_WRITE(AD7923_SEQUENCE_OFF) |
		st->settings;
	cmd <<= AD7923_SHIFT_REGISTER;
	st->tx_buf[0] = cpu_to_be16(cmd);

	ret = spi_sync(st->spi, &st->scan_single_msg);
	अगर (ret)
		वापस ret;

	वापस be16_to_cpu(st->rx_buf[0]);
पूर्ण

अटल पूर्णांक ad7923_get_range(काष्ठा ad7923_state *st)
अणु
	पूर्णांक vref;

	vref = regulator_get_voltage(st->reg);
	अगर (vref < 0)
		वापस vref;

	vref /= 1000;

	अगर (!(st->settings & AD7923_RANGE))
		vref *= 2;

	वापस vref;
पूर्ण

अटल पूर्णांक ad7923_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	पूर्णांक ret;
	काष्ठा ad7923_state *st = iio_priv(indio_dev);

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		ret = ad7923_scan_direct(st, chan->address);
		iio_device_release_direct_mode(indio_dev);

		अगर (ret < 0)
			वापस ret;

		अगर (chan->address == EXTRACT(ret, 12, 4))
			*val = EXTRACT(ret, 0, 12);
		अन्यथा
			वापस -EIO;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		ret = ad7923_get_range(st);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info ad7923_info = अणु
	.पढ़ो_raw = &ad7923_पढ़ो_raw,
	.update_scan_mode = ad7923_update_scan_mode,
पूर्ण;

अटल व्योम ad7923_regulator_disable(व्योम *data)
अणु
	काष्ठा ad7923_state *st = data;

	regulator_disable(st->reg);
पूर्ण

अटल पूर्णांक ad7923_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad7923_state *st;
	काष्ठा iio_dev *indio_dev;
	स्थिर काष्ठा ad7923_chip_info *info;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);

	st->spi = spi;
	st->settings = AD7923_CODING | AD7923_RANGE |
			AD7923_PM_MODE_WRITE(AD7923_PM_MODE_OPS);

	info = &ad7923_chip_info[spi_get_device_id(spi)->driver_data];

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = info->channels;
	indio_dev->num_channels = info->num_channels;
	indio_dev->info = &ad7923_info;

	/* Setup शेष message */

	st->scan_single_xfer[0].tx_buf = &st->tx_buf[0];
	st->scan_single_xfer[0].len = 2;
	st->scan_single_xfer[0].cs_change = 1;
	st->scan_single_xfer[1].rx_buf = &st->rx_buf[0];
	st->scan_single_xfer[1].len = 2;

	spi_message_init(&st->scan_single_msg);
	spi_message_add_tail(&st->scan_single_xfer[0], &st->scan_single_msg);
	spi_message_add_tail(&st->scan_single_xfer[1], &st->scan_single_msg);

	st->reg = devm_regulator_get(&spi->dev, "refin");
	अगर (IS_ERR(st->reg))
		वापस PTR_ERR(st->reg);

	ret = regulator_enable(st->reg);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(&spi->dev, ad7923_regulator_disable, st);
	अगर (ret)
		वापस ret;

	ret = devm_iio_triggered_buffer_setup(&spi->dev, indio_dev, शून्य,
					      &ad7923_trigger_handler, शून्य);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad7923_id[] = अणु
	अणु"ad7904", AD7904पूर्ण,
	अणु"ad7914", AD7914पूर्ण,
	अणु"ad7923", AD7924पूर्ण,
	अणु"ad7924", AD7924पूर्ण,
	अणु"ad7908", AD7908पूर्ण,
	अणु"ad7918", AD7918पूर्ण,
	अणु"ad7928", AD7928पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad7923_id);

अटल स्थिर काष्ठा of_device_id ad7923_of_match[] = अणु
	अणु .compatible = "adi,ad7904", पूर्ण,
	अणु .compatible = "adi,ad7914", पूर्ण,
	अणु .compatible = "adi,ad7923", पूर्ण,
	अणु .compatible = "adi,ad7924", पूर्ण,
	अणु .compatible = "adi,ad7908", पूर्ण,
	अणु .compatible = "adi,ad7918", पूर्ण,
	अणु .compatible = "adi,ad7928", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ad7923_of_match);

अटल काष्ठा spi_driver ad7923_driver = अणु
	.driver = अणु
		.name	= "ad7923",
		.of_match_table = ad7923_of_match,
	पूर्ण,
	.probe		= ad7923_probe,
	.id_table	= ad7923_id,
पूर्ण;
module_spi_driver(ad7923_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_AUTHOR("Patrick Vasseur <patrick.vasseur@c-s.fr>");
MODULE_DESCRIPTION("Analog Devices AD7923 and similar ADC");
MODULE_LICENSE("GPL v2");
