<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AD7887 SPI ADC driver
 *
 * Copyright 2010-2011 Analog Devices Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/bitops.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>

#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#समावेश <linux/platक्रमm_data/ad7887.h>

#घोषणा AD7887_REF_DIS		BIT(5)	/* on-chip reference disable */
#घोषणा AD7887_DUAL		BIT(4)	/* dual-channel mode */
#घोषणा AD7887_CH_AIN1		BIT(3)	/* convert on channel 1, DUAL=1 */
#घोषणा AD7887_CH_AIN0		0	/* convert on channel 0, DUAL=0,1 */
#घोषणा AD7887_PM_MODE1		0	/* CS based shutकरोwn */
#घोषणा AD7887_PM_MODE2		1	/* full on */
#घोषणा AD7887_PM_MODE3		2	/* स्वतः shutकरोwn after conversion */
#घोषणा AD7887_PM_MODE4		3	/* standby mode */

क्रमागत ad7887_channels अणु
	AD7887_CH0,
	AD7887_CH0_CH1,
	AD7887_CH1,
पूर्ण;

/**
 * काष्ठा ad7887_chip_info - chip specअगरc inक्रमmation
 * @पूर्णांक_vref_mv:	the पूर्णांकernal reference voltage
 * @channels:		channels specअगरication
 * @num_channels:	number of channels
 * @dual_channels:	channels specअगरication in dual mode
 * @num_dual_channels:	number of channels in dual mode
 */
काष्ठा ad7887_chip_info अणु
	u16				पूर्णांक_vref_mv;
	स्थिर काष्ठा iio_chan_spec	*channels;
	अचिन्हित पूर्णांक			num_channels;
	स्थिर काष्ठा iio_chan_spec	*dual_channels;
	अचिन्हित पूर्णांक			num_dual_channels;
पूर्ण;

काष्ठा ad7887_state अणु
	काष्ठा spi_device		*spi;
	स्थिर काष्ठा ad7887_chip_info	*chip_info;
	काष्ठा regulator		*reg;
	काष्ठा spi_transfer		xfer[4];
	काष्ठा spi_message		msg[3];
	काष्ठा spi_message		*ring_msg;
	अचिन्हित अक्षर			tx_cmd_buf[4];

	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 * Buffer needs to be large enough to hold two 16 bit samples and a
	 * 64 bit aligned 64 bit बारtamp.
	 */
	अचिन्हित अक्षर data[ALIGN(4, माप(s64)) + माप(s64)]
		____cacheline_aligned;
पूर्ण;

क्रमागत ad7887_supported_device_ids अणु
	ID_AD7887
पूर्ण;

अटल पूर्णांक ad7887_ring_preenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad7887_state *st = iio_priv(indio_dev);

	/* We know this is a single दीर्घ so can 'cheat' */
	चयन (*indio_dev->active_scan_mask) अणु
	हाल (1 << 0):
		st->ring_msg = &st->msg[AD7887_CH0];
		अवरोध;
	हाल (1 << 1):
		st->ring_msg = &st->msg[AD7887_CH1];
		/* Dummy पढ़ो: push CH1 setting करोwn to hardware */
		spi_sync(st->spi, st->ring_msg);
		अवरोध;
	हाल ((1 << 1) | (1 << 0)):
		st->ring_msg = &st->msg[AD7887_CH0_CH1];
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ad7887_ring_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad7887_state *st = iio_priv(indio_dev);

	/* dummy पढ़ो: restore शेष CH0 settin */
	वापस spi_sync(st->spi, &st->msg[AD7887_CH0]);
पूर्ण

अटल irqवापस_t ad7887_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा ad7887_state *st = iio_priv(indio_dev);
	पूर्णांक b_sent;

	b_sent = spi_sync(st->spi, st->ring_msg);
	अगर (b_sent)
		जाओ करोne;

	iio_push_to_buffers_with_बारtamp(indio_dev, st->data,
		iio_get_समय_ns(indio_dev));
करोne:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops ad7887_ring_setup_ops = अणु
	.preenable = &ad7887_ring_preenable,
	.postdisable = &ad7887_ring_postdisable,
पूर्ण;

अटल पूर्णांक ad7887_scan_direct(काष्ठा ad7887_state *st, अचिन्हित ch)
अणु
	पूर्णांक ret = spi_sync(st->spi, &st->msg[ch]);
	अगर (ret)
		वापस ret;

	वापस (st->data[(ch * 2)] << 8) | st->data[(ch * 2) + 1];
पूर्ण

अटल पूर्णांक ad7887_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	पूर्णांक ret;
	काष्ठा ad7887_state *st = iio_priv(indio_dev);

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		ret = ad7887_scan_direct(st, chan->address);
		iio_device_release_direct_mode(indio_dev);

		अगर (ret < 0)
			वापस ret;
		*val = ret >> chan->scan_type.shअगरt;
		*val &= GENMASK(chan->scan_type.realbits - 1, 0);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (st->reg) अणु
			*val = regulator_get_voltage(st->reg);
			अगर (*val < 0)
				वापस *val;
			*val /= 1000;
		पूर्ण अन्यथा अणु
			*val = st->chip_info->पूर्णांक_vref_mv;
		पूर्ण

		*val2 = chan->scan_type.realbits;

		वापस IIO_VAL_FRACTIONAL_LOG2;
	पूर्ण
	वापस -EINVAL;
पूर्ण

#घोषणा AD7887_CHANNEL(x) अणु \
	.type = IIO_VOLTAGE, \
	.indexed = 1, \
	.channel = (x), \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
	.address = (x), \
	.scan_index = (x), \
	.scan_type = अणु \
		.sign = 'u', \
		.realbits = 12, \
		.storagebits = 16, \
		.shअगरt = 0, \
		.endianness = IIO_BE, \
	पूर्ण, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ad7887_channels[] = अणु
	AD7887_CHANNEL(0),
	IIO_CHAN_SOFT_TIMESTAMP(1),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ad7887_dual_channels[] = अणु
	AD7887_CHANNEL(0),
	AD7887_CHANNEL(1),
	IIO_CHAN_SOFT_TIMESTAMP(2),
पूर्ण;

अटल स्थिर काष्ठा ad7887_chip_info ad7887_chip_info_tbl[] = अणु
	/*
	 * More devices added in future
	 */
	[ID_AD7887] = अणु
		.channels = ad7887_channels,
		.num_channels = ARRAY_SIZE(ad7887_channels),
		.dual_channels = ad7887_dual_channels,
		.num_dual_channels = ARRAY_SIZE(ad7887_dual_channels),
		.पूर्णांक_vref_mv = 2500,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_info ad7887_info = अणु
	.पढ़ो_raw = &ad7887_पढ़ो_raw,
पूर्ण;

अटल व्योम ad7887_reg_disable(व्योम *data)
अणु
	काष्ठा regulator *reg = data;

	regulator_disable(reg);
पूर्ण

अटल पूर्णांक ad7887_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad7887_platक्रमm_data *pdata = spi->dev.platक्रमm_data;
	काष्ठा ad7887_state *st;
	काष्ठा iio_dev *indio_dev;
	uपूर्णांक8_t mode;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);

	st->reg = devm_regulator_get_optional(&spi->dev, "vref");
	अगर (IS_ERR(st->reg)) अणु
		अगर (PTR_ERR(st->reg) != -ENODEV)
			वापस PTR_ERR(st->reg);

		st->reg = शून्य;
	पूर्ण

	अगर (st->reg) अणु
		ret = regulator_enable(st->reg);
		अगर (ret)
			वापस ret;

		ret = devm_add_action_or_reset(&spi->dev, ad7887_reg_disable, st->reg);
		अगर (ret)
			वापस ret;
	पूर्ण

	st->chip_info =
		&ad7887_chip_info_tbl[spi_get_device_id(spi)->driver_data];

	spi_set_drvdata(spi, indio_dev);
	st->spi = spi;

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad7887_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	/* Setup शेष message */

	mode = AD7887_PM_MODE4;
	अगर (!st->reg)
		mode |= AD7887_REF_DIS;
	अगर (pdata && pdata->en_dual)
		mode |= AD7887_DUAL;

	st->tx_cmd_buf[0] = AD7887_CH_AIN0 | mode;

	st->xfer[0].rx_buf = &st->data[0];
	st->xfer[0].tx_buf = &st->tx_cmd_buf[0];
	st->xfer[0].len = 2;

	spi_message_init(&st->msg[AD7887_CH0]);
	spi_message_add_tail(&st->xfer[0], &st->msg[AD7887_CH0]);

	अगर (pdata && pdata->en_dual) अणु
		st->tx_cmd_buf[2] = AD7887_CH_AIN1 | mode;

		st->xfer[1].rx_buf = &st->data[0];
		st->xfer[1].tx_buf = &st->tx_cmd_buf[2];
		st->xfer[1].len = 2;

		st->xfer[2].rx_buf = &st->data[2];
		st->xfer[2].tx_buf = &st->tx_cmd_buf[0];
		st->xfer[2].len = 2;

		spi_message_init(&st->msg[AD7887_CH0_CH1]);
		spi_message_add_tail(&st->xfer[1], &st->msg[AD7887_CH0_CH1]);
		spi_message_add_tail(&st->xfer[2], &st->msg[AD7887_CH0_CH1]);

		st->xfer[3].rx_buf = &st->data[2];
		st->xfer[3].tx_buf = &st->tx_cmd_buf[2];
		st->xfer[3].len = 2;

		spi_message_init(&st->msg[AD7887_CH1]);
		spi_message_add_tail(&st->xfer[3], &st->msg[AD7887_CH1]);

		indio_dev->channels = st->chip_info->dual_channels;
		indio_dev->num_channels = st->chip_info->num_dual_channels;
	पूर्ण अन्यथा अणु
		indio_dev->channels = st->chip_info->channels;
		indio_dev->num_channels = st->chip_info->num_channels;
	पूर्ण

	ret = devm_iio_triggered_buffer_setup(&spi->dev, indio_dev,
			&iio_pollfunc_store_समय,
			&ad7887_trigger_handler, &ad7887_ring_setup_ops);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad7887_id[] = अणु
	अणु"ad7887", ID_AD7887पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad7887_id);

अटल काष्ठा spi_driver ad7887_driver = अणु
	.driver = अणु
		.name	= "ad7887",
	पूर्ण,
	.probe		= ad7887_probe,
	.id_table	= ad7887_id,
पूर्ण;
module_spi_driver(ad7887_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD7887 ADC");
MODULE_LICENSE("GPL v2");
