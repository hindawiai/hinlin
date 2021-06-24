<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ad2s1200.c simple support क्रम the ADI Resolver to Digital Converters:
 * AD2S1200/1205
 *
 * Copyright (c) 2018-2018 David Veenstra <davidjulianveenstra@gmail.com>
 * Copyright (c) 2010-2010 Analog Devices Inc.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/mutex.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/types.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा DRV_NAME "ad2s1200"

/* input घड़ी on serial पूर्णांकerface */
#घोषणा AD2S1200_HZ	8192000
/* घड़ी period in nano second */
#घोषणा AD2S1200_TSCLK	(1000000000 / AD2S1200_HZ)

/**
 * काष्ठा ad2s1200_state - driver instance specअगरic data.
 * @lock:	protects both the GPIO pins and the rx buffer.
 * @sdev:	spi device.
 * @sample:	GPIO pin SAMPLE.
 * @rdvel:	GPIO pin RDVEL.
 * @rx:		buffer क्रम spi transfers.
 */
काष्ठा ad2s1200_state अणु
	काष्ठा mutex lock;
	काष्ठा spi_device *sdev;
	काष्ठा gpio_desc *sample;
	काष्ठा gpio_desc *rdvel;
	__be16 rx ____cacheline_aligned;
पूर्ण;

अटल पूर्णांक ad2s1200_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val,
			     पूर्णांक *val2,
			     दीर्घ m)
अणु
	काष्ठा ad2s1200_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (m) अणु
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_ANGL:
			/* 2 * Pi / (2^12 - 1) ~= 0.001534355 */
			*val = 0;
			*val2 = 1534355;
			वापस IIO_VAL_INT_PLUS_न_अंकO;
		हाल IIO_ANGL_VEL:
			/* 2 * Pi ~= 6.283185 */
			*val = 6;
			*val2 = 283185;
			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&st->lock);
		gpiod_set_value(st->sample, 0);

		/* delay (6 * AD2S1200_TSCLK + 20) nano seconds */
		udelay(1);
		gpiod_set_value(st->sample, 1);
		gpiod_set_value(st->rdvel, !!(chan->type == IIO_ANGL));

		ret = spi_पढ़ो(st->sdev, &st->rx, 2);
		अगर (ret < 0) अणु
			mutex_unlock(&st->lock);
			वापस ret;
		पूर्ण

		चयन (chan->type) अणु
		हाल IIO_ANGL:
			*val = be16_to_cpup(&st->rx) >> 4;
			अवरोध;
		हाल IIO_ANGL_VEL:
			*val = sign_extend32(be16_to_cpup(&st->rx) >> 4, 11);
			अवरोध;
		शेष:
			mutex_unlock(&st->lock);
			वापस -EINVAL;
		पूर्ण

		/* delay (2 * AD2S1200_TSCLK + 20) ns क्रम sample pulse */
		udelay(1);
		mutex_unlock(&st->lock);

		वापस IIO_VAL_INT;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ad2s1200_channels[] = अणु
	अणु
		.type = IIO_ANGL,
		.indexed = 1,
		.channel = 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण, अणु
		.type = IIO_ANGL_VEL,
		.indexed = 1,
		.channel = 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा iio_info ad2s1200_info = अणु
	.पढ़ो_raw = ad2s1200_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक ad2s1200_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad2s1200_state *st;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	spi_set_drvdata(spi, indio_dev);
	st = iio_priv(indio_dev);
	mutex_init(&st->lock);
	st->sdev = spi;

	st->sample = devm_gpiod_get(&spi->dev, "adi,sample", GPIOD_OUT_LOW);
	अगर (IS_ERR(st->sample)) अणु
		dev_err(&spi->dev, "Failed to claim SAMPLE gpio: err=%ld\n",
			PTR_ERR(st->sample));
		वापस PTR_ERR(st->sample);
	पूर्ण

	st->rdvel = devm_gpiod_get(&spi->dev, "adi,rdvel", GPIOD_OUT_LOW);
	अगर (IS_ERR(st->rdvel)) अणु
		dev_err(&spi->dev, "Failed to claim RDVEL gpio: err=%ld\n",
			PTR_ERR(st->rdvel));
		वापस PTR_ERR(st->rdvel);
	पूर्ण

	indio_dev->info = &ad2s1200_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = ad2s1200_channels;
	indio_dev->num_channels = ARRAY_SIZE(ad2s1200_channels);
	indio_dev->name = spi_get_device_id(spi)->name;

	spi->max_speed_hz = AD2S1200_HZ;
	spi->mode = SPI_MODE_3;
	ret = spi_setup(spi);

	अगर (ret < 0) अणु
		dev_err(&spi->dev, "spi_setup failed!\n");
		वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id ad2s1200_of_match[] = अणु
	अणु .compatible = "adi,ad2s1200", पूर्ण,
	अणु .compatible = "adi,ad2s1205", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ad2s1200_of_match);

अटल स्थिर काष्ठा spi_device_id ad2s1200_id[] = अणु
	अणु "ad2s1200" पूर्ण,
	अणु "ad2s1205" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad2s1200_id);

अटल काष्ठा spi_driver ad2s1200_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = ad2s1200_of_match,
	पूर्ण,
	.probe = ad2s1200_probe,
	.id_table = ad2s1200_id,
पूर्ण;
module_spi_driver(ad2s1200_driver);

MODULE_AUTHOR("David Veenstra <davidjulianveenstra@gmail.com>");
MODULE_AUTHOR("Graff Yang <graff.yang@gmail.com>");
MODULE_DESCRIPTION("Analog Devices AD2S1200/1205 Resolver to Digital SPI driver");
MODULE_LICENSE("GPL v2");
