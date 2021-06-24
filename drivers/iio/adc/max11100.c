<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * iio/adc/max11100.c
 * Maxim max11100 ADC Driver with IIO पूर्णांकerface
 *
 * Copyright (C) 2016-17 Renesas Electronics Corporation
 * Copyright (C) 2016-17 Jacopo Mondi
 */
#समावेश <linux/delay.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/driver.h>

/*
 * LSB is the ADC single digital step
 * 1 LSB = (vref_mv / 2 ^ 16)
 *
 * LSB is used to calculate analog voltage value
 * from the number of ADC steps count
 *
 * Ain = (count * LSB)
 */
#घोषणा MAX11100_LSB_DIV		(1 << 16)

काष्ठा max11100_state अणु
	काष्ठा regulator *vref_reg;
	काष्ठा spi_device *spi;

	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	u8 buffer[3] ____cacheline_aligned;
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec max11100_channels[] = अणु
	अणु /* [0] */
		.type = IIO_VOLTAGE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
पूर्ण;

अटल पूर्णांक max11100_पढ़ो_single(काष्ठा iio_dev *indio_dev, पूर्णांक *val)
अणु
	पूर्णांक ret;
	काष्ठा max11100_state *state = iio_priv(indio_dev);

	ret = spi_पढ़ो(state->spi, state->buffer, माप(state->buffer));
	अगर (ret) अणु
		dev_err(&indio_dev->dev, "SPI transfer failed\n");
		वापस ret;
	पूर्ण

	/* the first 8 bits sent out from ADC must be 0s */
	अगर (state->buffer[0]) अणु
		dev_err(&indio_dev->dev, "Invalid value: buffer[0] != 0\n");
		वापस -EINVAL;
	पूर्ण

	*val = (state->buffer[1] << 8) | state->buffer[2];

	वापस 0;
पूर्ण

अटल पूर्णांक max11100_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	पूर्णांक ret, vref_uv;
	काष्ठा max11100_state *state = iio_priv(indio_dev);

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = max11100_पढ़ो_single(indio_dev, val);
		अगर (ret)
			वापस ret;

		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		vref_uv = regulator_get_voltage(state->vref_reg);
		अगर (vref_uv < 0)
			/* dummy regulator "get_voltage" वापसs -EINVAL */
			वापस -EINVAL;

		*val =  vref_uv / 1000;
		*val2 = MAX11100_LSB_DIV;
		वापस IIO_VAL_FRACTIONAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info max11100_info = अणु
	.पढ़ो_raw = max11100_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक max11100_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev;
	काष्ठा max11100_state *state;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*state));
	अगर (!indio_dev)
		वापस -ENOMEM;

	spi_set_drvdata(spi, indio_dev);

	state = iio_priv(indio_dev);
	state->spi = spi;

	indio_dev->name = "max11100";
	indio_dev->info = &max11100_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = max11100_channels;
	indio_dev->num_channels = ARRAY_SIZE(max11100_channels);

	state->vref_reg = devm_regulator_get(&spi->dev, "vref");
	अगर (IS_ERR(state->vref_reg))
		वापस PTR_ERR(state->vref_reg);

	ret = regulator_enable(state->vref_reg);
	अगर (ret)
		वापस ret;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ disable_regulator;

	वापस 0;

disable_regulator:
	regulator_disable(state->vref_reg);

	वापस ret;
पूर्ण

अटल पूर्णांक max11100_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा max11100_state *state = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	regulator_disable(state->vref_reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id max11100_ids[] = अणु
	अणु.compatible = "maxim,max11100"पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, max11100_ids);

अटल काष्ठा spi_driver max11100_driver = अणु
	.driver = अणु
		.name	= "max11100",
		.of_match_table = max11100_ids,
	पूर्ण,
	.probe		= max11100_probe,
	.हटाओ		= max11100_हटाओ,
पूर्ण;

module_spi_driver(max11100_driver);

MODULE_AUTHOR("Jacopo Mondi <jacopo@jmondi.org>");
MODULE_DESCRIPTION("Maxim max11100 ADC Driver");
MODULE_LICENSE("GPL v2");
