<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * TI tlc4541 ADC Driver
 *
 * Copyright (C) 2017 Phil Reid
 *
 * Datasheets can be found here:
 * https://www.ti.com/lit/gpn/tlc3541
 * https://www.ti.com/lit/gpn/tlc4541
 *
 * The tlc4541 requires 24 घड़ी cycles to start a transfer.
 * Conversion then takes 2.94us to complete beक्रमe data is पढ़ोy
 * Data is वापसed MSB first.
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/sysfs.h>

काष्ठा tlc4541_state अणु
	काष्ठा spi_device               *spi;
	काष्ठा regulator                *reg;
	काष्ठा spi_transfer             scan_single_xfer[3];
	काष्ठा spi_message              scan_single_msg;

	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 * 2 bytes data + 6 bytes padding + 8 bytes बारtamp when
	 * call iio_push_to_buffers_with_बारtamp.
	 */
	__be16                          rx_buf[8] ____cacheline_aligned;
पूर्ण;

काष्ठा tlc4541_chip_info अणु
	स्थिर काष्ठा iio_chan_spec *channels;
	अचिन्हित पूर्णांक num_channels;
पूर्ण;

क्रमागत tlc4541_id अणु
	TLC3541,
	TLC4541,
पूर्ण;

#घोषणा TLC4541_V_CHAN(bits, bitshअगरt) अणु                              \
		.type = IIO_VOLTAGE,                                  \
		.info_mask_separate       = BIT(IIO_CHAN_INFO_RAW),   \
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
		.scan_type = अणु                                        \
			.sign = 'u',                                  \
			.realbits = (bits),                           \
			.storagebits = 16,                            \
			.shअगरt = (bitshअगरt),                          \
			.endianness = IIO_BE,                         \
		पूर्ण,                                                    \
	पूर्ण

#घोषणा DECLARE_TLC4541_CHANNELS(name, bits, bitshअगरt) \
स्थिर काष्ठा iio_chan_spec name ## _channels[] = अणु \
	TLC4541_V_CHAN(bits, bitshअगरt), \
	IIO_CHAN_SOFT_TIMESTAMP(1), \
पूर्ण

अटल DECLARE_TLC4541_CHANNELS(tlc3541, 14, 2);
अटल DECLARE_TLC4541_CHANNELS(tlc4541, 16, 0);

अटल स्थिर काष्ठा tlc4541_chip_info tlc4541_chip_info[] = अणु
	[TLC3541] = अणु
		.channels = tlc3541_channels,
		.num_channels = ARRAY_SIZE(tlc3541_channels),
	पूर्ण,
	[TLC4541] = अणु
		.channels = tlc4541_channels,
		.num_channels = ARRAY_SIZE(tlc4541_channels),
	पूर्ण,
पूर्ण;

अटल irqवापस_t tlc4541_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा tlc4541_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = spi_sync(st->spi, &st->scan_single_msg);
	अगर (ret < 0)
		जाओ करोne;

	iio_push_to_buffers_with_बारtamp(indio_dev, st->rx_buf,
					   iio_get_समय_ns(indio_dev));

करोne:
	iio_trigger_notअगरy_करोne(indio_dev->trig);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक tlc4541_get_range(काष्ठा tlc4541_state *st)
अणु
	पूर्णांक vref;

	vref = regulator_get_voltage(st->reg);
	अगर (vref < 0)
		वापस vref;

	vref /= 1000;

	वापस vref;
पूर्ण

अटल पूर्णांक tlc4541_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val,
			    पूर्णांक *val2,
			    दीर्घ m)
अणु
	पूर्णांक ret = 0;
	काष्ठा tlc4541_state *st = iio_priv(indio_dev);

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;
		ret = spi_sync(st->spi, &st->scan_single_msg);
		iio_device_release_direct_mode(indio_dev);
		अगर (ret < 0)
			वापस ret;
		*val = be16_to_cpu(st->rx_buf[0]);
		*val = *val >> chan->scan_type.shअगरt;
		*val &= GENMASK(chan->scan_type.realbits - 1, 0);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		ret = tlc4541_get_range(st);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info tlc4541_info = अणु
	.पढ़ो_raw = &tlc4541_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक tlc4541_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा tlc4541_state *st;
	काष्ठा iio_dev *indio_dev;
	स्थिर काष्ठा tlc4541_chip_info *info;
	पूर्णांक ret;
	पूर्णांक8_t device_init = 0;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);

	spi_set_drvdata(spi, indio_dev);

	st->spi = spi;

	info = &tlc4541_chip_info[spi_get_device_id(spi)->driver_data];

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = info->channels;
	indio_dev->num_channels = info->num_channels;
	indio_dev->info = &tlc4541_info;

	/* perक्रमm reset */
	spi_ग_लिखो(spi, &device_init, 1);

	/* Setup शेष message */
	st->scan_single_xfer[0].rx_buf = &st->rx_buf[0];
	st->scan_single_xfer[0].len = 3;
	st->scan_single_xfer[1].delay.value = 3;
	st->scan_single_xfer[1].delay.unit = SPI_DELAY_UNIT_NSECS;
	st->scan_single_xfer[2].rx_buf = &st->rx_buf[0];
	st->scan_single_xfer[2].len = 2;

	spi_message_init_with_transfers(&st->scan_single_msg,
					st->scan_single_xfer, 3);

	st->reg = devm_regulator_get(&spi->dev, "vref");
	अगर (IS_ERR(st->reg))
		वापस PTR_ERR(st->reg);

	ret = regulator_enable(st->reg);
	अगर (ret)
		वापस ret;

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
			&tlc4541_trigger_handler, शून्य);
	अगर (ret)
		जाओ error_disable_reg;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_cleanup_buffer;

	वापस 0;

error_cleanup_buffer:
	iio_triggered_buffer_cleanup(indio_dev);
error_disable_reg:
	regulator_disable(st->reg);

	वापस ret;
पूर्ण

अटल पूर्णांक tlc4541_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा tlc4541_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	regulator_disable(st->reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tlc4541_dt_ids[] = अणु
	अणु .compatible = "ti,tlc3541", पूर्ण,
	अणु .compatible = "ti,tlc4541", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tlc4541_dt_ids);

अटल स्थिर काष्ठा spi_device_id tlc4541_id[] = अणु
	अणु"tlc3541", TLC3541पूर्ण,
	अणु"tlc4541", TLC4541पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, tlc4541_id);

अटल काष्ठा spi_driver tlc4541_driver = अणु
	.driver = अणु
		.name   = "tlc4541",
		.of_match_table = tlc4541_dt_ids,
	पूर्ण,
	.probe          = tlc4541_probe,
	.हटाओ         = tlc4541_हटाओ,
	.id_table       = tlc4541_id,
पूर्ण;
module_spi_driver(tlc4541_driver);

MODULE_AUTHOR("Phil Reid <preid@electromag.com.au>");
MODULE_DESCRIPTION("Texas Instruments TLC4541 ADC");
MODULE_LICENSE("GPL v2");
