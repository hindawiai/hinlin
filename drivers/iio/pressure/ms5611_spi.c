<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * MS5611 pressure and temperature sensor driver (SPI bus)
 *
 * Copyright (c) Tomasz Duszynski <tduszyns@gmail.com>
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/mod_devicetable.h>

#समावेश <यंत्र/unaligned.h>

#समावेश "ms5611.h"

अटल पूर्णांक ms5611_spi_reset(काष्ठा device *dev)
अणु
	u8 cmd = MS5611_RESET;
	काष्ठा ms5611_state *st = iio_priv(dev_to_iio_dev(dev));

	वापस spi_ग_लिखो_then_पढ़ो(st->client, &cmd, 1, शून्य, 0);
पूर्ण

अटल पूर्णांक ms5611_spi_पढ़ो_prom_word(काष्ठा device *dev, पूर्णांक index, u16 *word)
अणु
	पूर्णांक ret;
	काष्ठा ms5611_state *st = iio_priv(dev_to_iio_dev(dev));

	ret = spi_w8r16be(st->client, MS5611_READ_PROM_WORD + (index << 1));
	अगर (ret < 0)
		वापस ret;

	*word = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ms5611_spi_पढ़ो_adc(काष्ठा device *dev, s32 *val)
अणु
	पूर्णांक ret;
	u8 buf[3] = अणु MS5611_READ_ADC पूर्ण;
	काष्ठा ms5611_state *st = iio_priv(dev_to_iio_dev(dev));

	ret = spi_ग_लिखो_then_पढ़ो(st->client, buf, 1, buf, 3);
	अगर (ret < 0)
		वापस ret;

	*val = get_unaligned_be24(&buf[0]);

	वापस 0;
पूर्ण

अटल पूर्णांक ms5611_spi_पढ़ो_adc_temp_and_pressure(काष्ठा device *dev,
						 s32 *temp, s32 *pressure)
अणु
	पूर्णांक ret;
	काष्ठा ms5611_state *st = iio_priv(dev_to_iio_dev(dev));
	स्थिर काष्ठा ms5611_osr *osr = st->temp_osr;

	/*
	 * Warning: &osr->cmd MUST be aligned on a word boundary since used as
	 * 2nd argument (व्योम*) of spi_ग_लिखो_then_पढ़ो.
	 */
	ret = spi_ग_लिखो_then_पढ़ो(st->client, &osr->cmd, 1, शून्य, 0);
	अगर (ret < 0)
		वापस ret;

	usleep_range(osr->conv_usec, osr->conv_usec + (osr->conv_usec / 10UL));
	ret = ms5611_spi_पढ़ो_adc(dev, temp);
	अगर (ret < 0)
		वापस ret;

	osr = st->pressure_osr;
	ret = spi_ग_लिखो_then_पढ़ो(st->client, &osr->cmd, 1, शून्य, 0);
	अगर (ret < 0)
		वापस ret;

	usleep_range(osr->conv_usec, osr->conv_usec + (osr->conv_usec / 10UL));
	वापस ms5611_spi_पढ़ो_adc(dev, pressure);
पूर्ण

अटल पूर्णांक ms5611_spi_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
	काष्ठा ms5611_state *st;
	काष्ठा iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	spi_set_drvdata(spi, indio_dev);

	spi->mode = SPI_MODE_0;
	spi->max_speed_hz = 20000000;
	spi->bits_per_word = 8;
	ret = spi_setup(spi);
	अगर (ret < 0)
		वापस ret;

	st = iio_priv(indio_dev);
	st->reset = ms5611_spi_reset;
	st->पढ़ो_prom_word = ms5611_spi_पढ़ो_prom_word;
	st->पढ़ो_adc_temp_and_pressure = ms5611_spi_पढ़ो_adc_temp_and_pressure;
	st->client = spi;

	वापस ms5611_probe(indio_dev, &spi->dev, spi_get_device_id(spi)->name,
			    spi_get_device_id(spi)->driver_data);
पूर्ण

अटल पूर्णांक ms5611_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस ms5611_हटाओ(spi_get_drvdata(spi));
पूर्ण

अटल स्थिर काष्ठा of_device_id ms5611_spi_matches[] = अणु
	अणु .compatible = "meas,ms5611" पूर्ण,
	अणु .compatible = "meas,ms5607" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ms5611_spi_matches);

अटल स्थिर काष्ठा spi_device_id ms5611_id[] = अणु
	अणु "ms5611", MS5611 पूर्ण,
	अणु "ms5607", MS5607 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ms5611_id);

अटल काष्ठा spi_driver ms5611_driver = अणु
	.driver = अणु
		.name = "ms5611",
		.of_match_table = ms5611_spi_matches
	पूर्ण,
	.id_table = ms5611_id,
	.probe = ms5611_spi_probe,
	.हटाओ = ms5611_spi_हटाओ,
पूर्ण;
module_spi_driver(ms5611_driver);

MODULE_AUTHOR("Tomasz Duszynski <tduszyns@gmail.com>");
MODULE_DESCRIPTION("MS5611 spi driver");
MODULE_LICENSE("GPL v2");
