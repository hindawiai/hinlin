<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MAX1241 low-घातer, 12-bit serial ADC
 *
 * Datasheet: https://datasheets.maximपूर्णांकegrated.com/en/ds/MAX1240-MAX1241.pdf
 */

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

#घोषणा MAX1241_VAL_MASK GENMASK(11, 0)
#घोषणा MAX1241_SHUTDOWN_DELAY_USEC 4

क्रमागत max1241_id अणु
	max1241,
पूर्ण;

काष्ठा max1241 अणु
	काष्ठा spi_device *spi;
	काष्ठा mutex lock;
	काष्ठा regulator *vdd;
	काष्ठा regulator *vref;
	काष्ठा gpio_desc *shutकरोwn;

	__be16 data ____cacheline_aligned;
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec max1241_channels[] = अणु
	अणु
		.type = IIO_VOLTAGE,
		.indexed = 1,
		.channel = 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
पूर्ण;

अटल पूर्णांक max1241_पढ़ो(काष्ठा max1241 *adc)
अणु
	काष्ठा spi_transfer xfers[] = अणु
		/*
		 * Begin conversion by bringing /CS low क्रम at least
		 * tconv us.
		 */
		अणु
			.len = 0,
			.delay.value = 8,
			.delay.unit = SPI_DELAY_UNIT_USECS,
		पूर्ण,
		/*
		 * Then पढ़ो two bytes of data in our RX buffer.
		 */
		अणु
			.rx_buf = &adc->data,
			.len = 2,
		पूर्ण,
	पूर्ण;

	वापस spi_sync_transfer(adc->spi, xfers, ARRAY_SIZE(xfers));
पूर्ण

अटल पूर्णांक max1241_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *chan,
			पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret, vref_uV;
	काष्ठा max1241 *adc = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&adc->lock);

		अगर (adc->shutकरोwn) अणु
			gpiod_set_value(adc->shutकरोwn, 0);
			udelay(MAX1241_SHUTDOWN_DELAY_USEC);
			ret = max1241_पढ़ो(adc);
			gpiod_set_value(adc->shutकरोwn, 1);
		पूर्ण अन्यथा
			ret = max1241_पढ़ो(adc);

		अगर (ret) अणु
			mutex_unlock(&adc->lock);
			वापस ret;
		पूर्ण

		*val = (be16_to_cpu(adc->data) >> 3) & MAX1241_VAL_MASK;

		mutex_unlock(&adc->lock);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		vref_uV = regulator_get_voltage(adc->vref);

		अगर (vref_uV < 0)
			वापस vref_uV;

		*val = vref_uV / 1000;
		*val2 = 12;

		वापस IIO_VAL_FRACTIONAL_LOG2;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info max1241_info = अणु
	.पढ़ो_raw = max1241_पढ़ो_raw,
पूर्ण;

अटल व्योम max1241_disable_vdd_action(व्योम *data)
अणु
	काष्ठा max1241 *adc = data;
	काष्ठा device *dev = &adc->spi->dev;
	पूर्णांक err;

	err = regulator_disable(adc->vdd);
	अगर (err)
		dev_err(dev, "could not disable vdd regulator.\n");
पूर्ण

अटल व्योम max1241_disable_vref_action(व्योम *data)
अणु
	काष्ठा max1241 *adc = data;
	काष्ठा device *dev = &adc->spi->dev;
	पूर्णांक err;

	err = regulator_disable(adc->vref);
	अगर (err)
		dev_err(dev, "could not disable vref regulator.\n");
पूर्ण

अटल पूर्णांक max1241_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा iio_dev *indio_dev;
	काष्ठा max1241 *adc;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*adc));
	अगर (!indio_dev)
		वापस -ENOMEM;

	adc = iio_priv(indio_dev);
	adc->spi = spi;
	mutex_init(&adc->lock);

	spi_set_drvdata(spi, indio_dev);

	adc->vdd = devm_regulator_get(dev, "vdd");
	अगर (IS_ERR(adc->vdd)) अणु
		dev_err(dev, "failed to get vdd regulator\n");
		वापस PTR_ERR(adc->vdd);
	पूर्ण

	ret = regulator_enable(adc->vdd);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(dev, max1241_disable_vdd_action, adc);
	अगर (ret) अणु
		dev_err(dev, "could not set up vdd regulator cleanup action\n");
		वापस ret;
	पूर्ण

	adc->vref = devm_regulator_get(dev, "vref");
	अगर (IS_ERR(adc->vref)) अणु
		dev_err(dev, "failed to get vref regulator\n");
		वापस PTR_ERR(adc->vref);
	पूर्ण

	ret = regulator_enable(adc->vref);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(dev, max1241_disable_vref_action, adc);
	अगर (ret) अणु
		dev_err(dev, "could not set up vref regulator cleanup action\n");
		वापस ret;
	पूर्ण

	adc->shutकरोwn = devm_gpiod_get_optional(dev, "shutdown",
						GPIOD_OUT_HIGH);
	अगर (IS_ERR(adc->shutकरोwn))
		वापस PTR_ERR(adc->shutकरोwn);

	अगर (adc->shutकरोwn)
		dev_dbg(dev, "shutdown pin passed, low-power mode enabled");
	अन्यथा
		dev_dbg(dev, "no shutdown pin passed, low-power mode disabled");

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &max1241_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = max1241_channels;
	indio_dev->num_channels = ARRAY_SIZE(max1241_channels);

	वापस devm_iio_device_रेजिस्टर(dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id max1241_id[] = अणु
	अणु "max1241", max1241 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id max1241_dt_ids[] = अणु
	अणु .compatible = "maxim,max1241" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max1241_dt_ids);

अटल काष्ठा spi_driver max1241_spi_driver = अणु
	.driver = अणु
		.name = "max1241",
		.of_match_table = max1241_dt_ids,
	पूर्ण,
	.probe = max1241_probe,
	.id_table = max1241_id,
पूर्ण;
module_spi_driver(max1241_spi_driver);

MODULE_AUTHOR("Alexandru Lazar <alazar@startmail.com>");
MODULE_DESCRIPTION("MAX1241 ADC driver");
MODULE_LICENSE("GPL v2");
