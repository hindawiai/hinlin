<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AD7298 SPI ADC driver
 *
 * Copyright 2011 Analog Devices Inc.
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
#समावेश <linux/bitops.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#घोषणा AD7298_WRITE	BIT(15) /* ग_लिखो to the control रेजिस्टर */
#घोषणा AD7298_REPEAT	BIT(14) /* repeated conversion enable */
#घोषणा AD7298_CH(x)	BIT(13 - (x)) /* channel select */
#घोषणा AD7298_TSENSE	BIT(5) /* temperature conversion enable */
#घोषणा AD7298_EXTREF	BIT(2) /* बाह्यal reference enable */
#घोषणा AD7298_TAVG	BIT(1) /* temperature sensor averaging enable */
#घोषणा AD7298_PDD	BIT(0) /* partial घातer करोwn enable */

#घोषणा AD7298_MAX_CHAN		8
#घोषणा AD7298_INTREF_mV	2500

#घोषणा AD7298_CH_TEMP		9

काष्ठा ad7298_state अणु
	काष्ठा spi_device		*spi;
	काष्ठा regulator		*reg;
	अचिन्हित			ext_ref;
	काष्ठा spi_transfer		ring_xfer[10];
	काष्ठा spi_transfer		scan_single_xfer[3];
	काष्ठा spi_message		ring_msg;
	काष्ठा spi_message		scan_single_msg;
	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	__be16				rx_buf[12] ____cacheline_aligned;
	__be16				tx_buf[2];
पूर्ण;

#घोषणा AD7298_V_CHAN(index)						\
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
			.realbits = 12,					\
			.storagebits = 16,				\
			.endianness = IIO_BE,				\
		पूर्ण,							\
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ad7298_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.indexed = 1,
		.channel = 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.address = AD7298_CH_TEMP,
		.scan_index = -1,
		.scan_type = अणु
			.sign = 's',
			.realbits = 32,
			.storagebits = 32,
		पूर्ण,
	पूर्ण,
	AD7298_V_CHAN(0),
	AD7298_V_CHAN(1),
	AD7298_V_CHAN(2),
	AD7298_V_CHAN(3),
	AD7298_V_CHAN(4),
	AD7298_V_CHAN(5),
	AD7298_V_CHAN(6),
	AD7298_V_CHAN(7),
	IIO_CHAN_SOFT_TIMESTAMP(8),
पूर्ण;

/*
 * ad7298_update_scan_mode() setup the spi transfer buffer क्रम the new scan mask
 */
अटल पूर्णांक ad7298_update_scan_mode(काष्ठा iio_dev *indio_dev,
	स्थिर अचिन्हित दीर्घ *active_scan_mask)
अणु
	काष्ठा ad7298_state *st = iio_priv(indio_dev);
	पूर्णांक i, m;
	अचिन्हित लघु command;
	पूर्णांक scan_count;

	/* Now compute overall size */
	scan_count = biपंचांगap_weight(active_scan_mask, indio_dev->masklength);

	command = AD7298_WRITE | st->ext_ref;

	क्रम (i = 0, m = AD7298_CH(0); i < AD7298_MAX_CHAN; i++, m >>= 1)
		अगर (test_bit(i, active_scan_mask))
			command |= m;

	st->tx_buf[0] = cpu_to_be16(command);

	/* build spi ring message */
	st->ring_xfer[0].tx_buf = &st->tx_buf[0];
	st->ring_xfer[0].len = 2;
	st->ring_xfer[0].cs_change = 1;
	st->ring_xfer[1].tx_buf = &st->tx_buf[1];
	st->ring_xfer[1].len = 2;
	st->ring_xfer[1].cs_change = 1;

	spi_message_init(&st->ring_msg);
	spi_message_add_tail(&st->ring_xfer[0], &st->ring_msg);
	spi_message_add_tail(&st->ring_xfer[1], &st->ring_msg);

	क्रम (i = 0; i < scan_count; i++) अणु
		st->ring_xfer[i + 2].rx_buf = &st->rx_buf[i];
		st->ring_xfer[i + 2].len = 2;
		st->ring_xfer[i + 2].cs_change = 1;
		spi_message_add_tail(&st->ring_xfer[i + 2], &st->ring_msg);
	पूर्ण
	/* make sure last transfer cs_change is not set */
	st->ring_xfer[i + 1].cs_change = 0;

	वापस 0;
पूर्ण

अटल irqवापस_t ad7298_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा ad7298_state *st = iio_priv(indio_dev);
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

अटल पूर्णांक ad7298_scan_direct(काष्ठा ad7298_state *st, अचिन्हित ch)
अणु
	पूर्णांक ret;
	st->tx_buf[0] = cpu_to_be16(AD7298_WRITE | st->ext_ref |
				   (AD7298_CH(0) >> ch));

	ret = spi_sync(st->spi, &st->scan_single_msg);
	अगर (ret)
		वापस ret;

	वापस be16_to_cpu(st->rx_buf[0]);
पूर्ण

अटल पूर्णांक ad7298_scan_temp(काष्ठा ad7298_state *st, पूर्णांक *val)
अणु
	पूर्णांक ret;
	__be16 buf;

	buf = cpu_to_be16(AD7298_WRITE | AD7298_TSENSE |
			  AD7298_TAVG | st->ext_ref);

	ret = spi_ग_लिखो(st->spi, (u8 *)&buf, 2);
	अगर (ret)
		वापस ret;

	buf = cpu_to_be16(0);

	ret = spi_ग_लिखो(st->spi, (u8 *)&buf, 2);
	अगर (ret)
		वापस ret;

	usleep_range(101, 1000); /* sleep > 100us */

	ret = spi_पढ़ो(st->spi, (u8 *)&buf, 2);
	अगर (ret)
		वापस ret;

	*val = sign_extend32(be16_to_cpu(buf), 11);

	वापस 0;
पूर्ण

अटल पूर्णांक ad7298_get_ref_voltage(काष्ठा ad7298_state *st)
अणु
	पूर्णांक vref;

	अगर (st->reg) अणु
		vref = regulator_get_voltage(st->reg);
		अगर (vref < 0)
			वापस vref;

		वापस vref / 1000;
	पूर्ण अन्यथा अणु
		वापस AD7298_INTREF_mV;
	पूर्ण
पूर्ण

अटल पूर्णांक ad7298_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	पूर्णांक ret;
	काष्ठा ad7298_state *st = iio_priv(indio_dev);

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		अगर (chan->address == AD7298_CH_TEMP)
			ret = ad7298_scan_temp(st, val);
		अन्यथा
			ret = ad7298_scan_direct(st, chan->address);

		iio_device_release_direct_mode(indio_dev);

		अगर (ret < 0)
			वापस ret;

		अगर (chan->address != AD7298_CH_TEMP)
			*val = ret & GENMASK(chan->scan_type.realbits - 1, 0);

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_VOLTAGE:
			*val = ad7298_get_ref_voltage(st);
			*val2 = chan->scan_type.realbits;
			वापस IIO_VAL_FRACTIONAL_LOG2;
		हाल IIO_TEMP:
			*val = ad7298_get_ref_voltage(st);
			*val2 = 10;
			वापस IIO_VAL_FRACTIONAL;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_OFFSET:
		*val = 1093 - 2732500 / ad7298_get_ref_voltage(st);
		वापस IIO_VAL_INT;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info ad7298_info = अणु
	.पढ़ो_raw = &ad7298_पढ़ो_raw,
	.update_scan_mode = ad7298_update_scan_mode,
पूर्ण;

अटल व्योम ad7298_reg_disable(व्योम *data)
अणु
	काष्ठा regulator *reg = data;

	regulator_disable(reg);
पूर्ण

अटल पूर्णांक ad7298_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad7298_state *st;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);

	st->reg = devm_regulator_get_optional(&spi->dev, "vref");
	अगर (!IS_ERR(st->reg)) अणु
		st->ext_ref = AD7298_EXTREF;
	पूर्ण अन्यथा अणु
		ret = PTR_ERR(st->reg);
		अगर (ret != -ENODEV)
			वापस ret;

		st->reg = शून्य;
	पूर्ण

	अगर (st->reg) अणु
		ret = regulator_enable(st->reg);
		अगर (ret)
			वापस ret;

		ret = devm_add_action_or_reset(&spi->dev, ad7298_reg_disable,
					       st->reg);
		अगर (ret)
			वापस ret;
	पूर्ण

	st->spi = spi;

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = ad7298_channels;
	indio_dev->num_channels = ARRAY_SIZE(ad7298_channels);
	indio_dev->info = &ad7298_info;

	/* Setup शेष message */

	st->scan_single_xfer[0].tx_buf = &st->tx_buf[0];
	st->scan_single_xfer[0].len = 2;
	st->scan_single_xfer[0].cs_change = 1;
	st->scan_single_xfer[1].tx_buf = &st->tx_buf[1];
	st->scan_single_xfer[1].len = 2;
	st->scan_single_xfer[1].cs_change = 1;
	st->scan_single_xfer[2].rx_buf = &st->rx_buf[0];
	st->scan_single_xfer[2].len = 2;

	spi_message_init(&st->scan_single_msg);
	spi_message_add_tail(&st->scan_single_xfer[0], &st->scan_single_msg);
	spi_message_add_tail(&st->scan_single_xfer[1], &st->scan_single_msg);
	spi_message_add_tail(&st->scan_single_xfer[2], &st->scan_single_msg);

	ret = devm_iio_triggered_buffer_setup(&spi->dev, indio_dev, शून्य,
			&ad7298_trigger_handler, शून्य);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad7298_id[] = अणु
	अणु"ad7298", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad7298_id);

अटल काष्ठा spi_driver ad7298_driver = अणु
	.driver = अणु
		.name	= "ad7298",
	पूर्ण,
	.probe		= ad7298_probe,
	.id_table	= ad7298_id,
पूर्ण;
module_spi_driver(ad7298_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD7298 ADC");
MODULE_LICENSE("GPL v2");
