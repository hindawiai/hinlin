<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MAX1117/MAX1118/MAX1119 8-bit, dual-channel ADCs driver
 *
 * Copyright (c) 2017 Akinobu Mita <akinobu.mita@gmail.com>
 *
 * Datasheet: https://datasheets.maximपूर्णांकegrated.com/en/ds/MAX1117-MAX1119.pdf
 *
 * SPI पूर्णांकerface connections
 *
 * SPI                MAXIM
 * Master  Direction  MAX1117/8/9
 * ------  ---------  -----------
 * nCS        -->     CNVST
 * SCK        -->     SCLK
 * MISO       <--     DOUT
 * ------  ---------  -----------
 */

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/regulator/consumer.h>

क्रमागत max1118_id अणु
	max1117,
	max1118,
	max1119,
पूर्ण;

काष्ठा max1118 अणु
	काष्ठा spi_device *spi;
	काष्ठा mutex lock;
	काष्ठा regulator *reg;
	/* Ensure natural alignment of buffer elements */
	काष्ठा अणु
		u8 channels[2];
		s64 ts __aligned(8);
	पूर्ण scan;

	u8 data ____cacheline_aligned;
पूर्ण;

#घोषणा MAX1118_CHANNEL(ch)						\
	अणु								\
		.type = IIO_VOLTAGE,					\
		.indexed = 1,						\
		.channel = (ch),					\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
		.scan_index = ch,					\
		.scan_type = अणु						\
			.sign = 'u',					\
			.realbits = 8,					\
			.storagebits = 8,				\
		पूर्ण,							\
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec max1118_channels[] = अणु
	MAX1118_CHANNEL(0),
	MAX1118_CHANNEL(1),
	IIO_CHAN_SOFT_TIMESTAMP(2),
पूर्ण;

अटल पूर्णांक max1118_पढ़ो(काष्ठा spi_device *spi, पूर्णांक channel)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा max1118 *adc = iio_priv(indio_dev);
	काष्ठा spi_transfer xfers[] = अणु
		/*
		 * To select CH1 क्रम conversion, CNVST pin must be brought high
		 * and low क्रम a second समय.
		 */
		अणु
			.len = 0,
			.delay = अणु	/* > CNVST Low Time 100 ns */
				.value = 1,
				.unit = SPI_DELAY_UNIT_USECS
			पूर्ण,
			.cs_change = 1,
		पूर्ण,
		/*
		 * The acquisition पूर्णांकerval begins with the falling edge of
		 * CNVST.  The total acquisition and conversion process takes
		 * <7.5us.
		 */
		अणु
			.len = 0,
			.delay = अणु
				.value = 8,
				.unit = SPI_DELAY_UNIT_USECS
			पूर्ण,
		पूर्ण,
		अणु
			.rx_buf = &adc->data,
			.len = 1,
		पूर्ण,
	पूर्ण;
	पूर्णांक ret;

	अगर (channel == 0)
		ret = spi_sync_transfer(spi, xfers + 1, 2);
	अन्यथा
		ret = spi_sync_transfer(spi, xfers, 3);

	अगर (ret)
		वापस ret;

	वापस adc->data;
पूर्ण

अटल पूर्णांक max1118_get_vref_mV(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा max1118 *adc = iio_priv(indio_dev);
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	पूर्णांक vref_uV;

	चयन (id->driver_data) अणु
	हाल max1117:
		वापस 2048;
	हाल max1119:
		वापस 4096;
	हाल max1118:
		vref_uV = regulator_get_voltage(adc->reg);
		अगर (vref_uV < 0)
			वापस vref_uV;
		वापस vref_uV / 1000;
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक max1118_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *chan,
			पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा max1118 *adc = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&adc->lock);
		*val = max1118_पढ़ो(adc->spi, chan->channel);
		mutex_unlock(&adc->lock);
		अगर (*val < 0)
			वापस *val;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = max1118_get_vref_mV(adc->spi);
		अगर (*val < 0)
			वापस *val;
		*val2 = 8;

		वापस IIO_VAL_FRACTIONAL_LOG2;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info max1118_info = अणु
	.पढ़ो_raw = max1118_पढ़ो_raw,
पूर्ण;

अटल irqवापस_t max1118_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा max1118 *adc = iio_priv(indio_dev);
	पूर्णांक scan_index;
	पूर्णांक i = 0;

	mutex_lock(&adc->lock);

	क्रम_each_set_bit(scan_index, indio_dev->active_scan_mask,
			indio_dev->masklength) अणु
		स्थिर काष्ठा iio_chan_spec *scan_chan =
				&indio_dev->channels[scan_index];
		पूर्णांक ret = max1118_पढ़ो(adc->spi, scan_chan->channel);

		अगर (ret < 0) अणु
			dev_warn(&adc->spi->dev,
				"failed to get conversion data\n");
			जाओ out;
		पूर्ण

		adc->scan.channels[i] = ret;
		i++;
	पूर्ण
	iio_push_to_buffers_with_बारtamp(indio_dev, &adc->scan,
					   iio_get_समय_ns(indio_dev));
out:
	mutex_unlock(&adc->lock);

	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक max1118_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा max1118 *adc;
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*adc));
	अगर (!indio_dev)
		वापस -ENOMEM;

	adc = iio_priv(indio_dev);
	adc->spi = spi;
	mutex_init(&adc->lock);

	अगर (id->driver_data == max1118) अणु
		adc->reg = devm_regulator_get(&spi->dev, "vref");
		अगर (IS_ERR(adc->reg)) अणु
			dev_err(&spi->dev, "failed to get vref regulator\n");
			वापस PTR_ERR(adc->reg);
		पूर्ण
		ret = regulator_enable(adc->reg);
		अगर (ret)
			वापस ret;
	पूर्ण

	spi_set_drvdata(spi, indio_dev);

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &max1118_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = max1118_channels;
	indio_dev->num_channels = ARRAY_SIZE(max1118_channels);

	/*
	 * To reinitiate a conversion on CH0, it is necessary to allow क्रम a
	 * conversion to be complete and all of the data to be पढ़ो out.  Once
	 * a conversion has been completed, the MAX1117/MAX1118/MAX1119 will go
	 * पूर्णांकo AutoShutकरोwn mode until the next conversion is initiated.
	 */
	max1118_पढ़ो(spi, 0);

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
					max1118_trigger_handler, शून्य);
	अगर (ret)
		जाओ err_reg_disable;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ err_buffer_cleanup;

	वापस 0;

err_buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
err_reg_disable:
	अगर (id->driver_data == max1118)
		regulator_disable(adc->reg);

	वापस ret;
पूर्ण

अटल पूर्णांक max1118_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा max1118 *adc = iio_priv(indio_dev);
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	अगर (id->driver_data == max1118)
		वापस regulator_disable(adc->reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id max1118_id[] = अणु
	अणु "max1117", max1117 पूर्ण,
	अणु "max1118", max1118 पूर्ण,
	अणु "max1119", max1119 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, max1118_id);

अटल स्थिर काष्ठा of_device_id max1118_dt_ids[] = अणु
	अणु .compatible = "maxim,max1117" पूर्ण,
	अणु .compatible = "maxim,max1118" पूर्ण,
	अणु .compatible = "maxim,max1119" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, max1118_dt_ids);

अटल काष्ठा spi_driver max1118_spi_driver = अणु
	.driver = अणु
		.name = "max1118",
		.of_match_table = max1118_dt_ids,
	पूर्ण,
	.probe = max1118_probe,
	.हटाओ = max1118_हटाओ,
	.id_table = max1118_id,
पूर्ण;
module_spi_driver(max1118_spi_driver);

MODULE_AUTHOR("Akinobu Mita <akinobu.mita@gmail.com>");
MODULE_DESCRIPTION("MAXIM MAX1117/MAX1118/MAX1119 ADCs driver");
MODULE_LICENSE("GPL v2");
