<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ad2s90.c simple support क्रम the ADI Resolver to Digital Converters: AD2S90
 *
 * Copyright (c) 2010-2010 Analog Devices Inc.
 */
#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/module.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

/*
 * Although chip's max frequency is 2Mhz, it needs 600ns between CS and the
 * first falling edge of SCLK, so frequency should be at most 1 / (2 * 6e-7)
 */
#घोषणा AD2S90_MAX_SPI_FREQ_HZ  830000

काष्ठा ad2s90_state अणु
	काष्ठा mutex lock; /* lock to protect rx buffer */
	काष्ठा spi_device *sdev;
	u8 rx[2] ____cacheline_aligned;
पूर्ण;

अटल पूर्णांक ad2s90_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	पूर्णांक ret;
	काष्ठा ad2s90_state *st = iio_priv(indio_dev);

	अगर (chan->type != IIO_ANGL)
		वापस -EINVAL;

	चयन (m) अणु
	हाल IIO_CHAN_INFO_SCALE:
		/* 2 * Pi / 2^12 */
		*val = 6283; /* mV */
		*val2 = 12;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&st->lock);
		ret = spi_पढ़ो(st->sdev, st->rx, 2);
		अगर (ret < 0) अणु
			mutex_unlock(&st->lock);
			वापस ret;
		पूर्ण
		*val = (((u16)(st->rx[0])) << 4) | ((st->rx[1] & 0xF0) >> 4);

		mutex_unlock(&st->lock);

		वापस IIO_VAL_INT;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info ad2s90_info = अणु
	.पढ़ो_raw = ad2s90_पढ़ो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ad2s90_chan = अणु
	.type = IIO_ANGL,
	.indexed = 1,
	.channel = 0,
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
पूर्ण;

अटल पूर्णांक ad2s90_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा ad2s90_state *st;

	अगर (spi->max_speed_hz > AD2S90_MAX_SPI_FREQ_HZ) अणु
		dev_err(&spi->dev, "SPI CLK, %d Hz exceeds %d Hz\n",
			spi->max_speed_hz, AD2S90_MAX_SPI_FREQ_HZ);
		वापस -EINVAL;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;
	st = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);

	mutex_init(&st->lock);
	st->sdev = spi;
	indio_dev->info = &ad2s90_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = &ad2s90_chan;
	indio_dev->num_channels = 1;
	indio_dev->name = spi_get_device_id(spi)->name;

	वापस devm_iio_device_रेजिस्टर(indio_dev->dev.parent, indio_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id ad2s90_of_match[] = अणु
	अणु .compatible = "adi,ad2s90", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ad2s90_of_match);

अटल स्थिर काष्ठा spi_device_id ad2s90_id[] = अणु
	अणु "ad2s90" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad2s90_id);

अटल काष्ठा spi_driver ad2s90_driver = अणु
	.driver = अणु
		.name = "ad2s90",
		.of_match_table = ad2s90_of_match,
	पूर्ण,
	.probe = ad2s90_probe,
	.id_table = ad2s90_id,
पूर्ण;
module_spi_driver(ad2s90_driver);

MODULE_AUTHOR("Graff Yang <graff.yang@gmail.com>");
MODULE_DESCRIPTION("Analog Devices AD2S90 Resolver to Digital SPI driver");
MODULE_LICENSE("GPL v2");
