<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ADIS16080/100 Yaw Rate Gyroscope with SPI driver
 *
 * Copyright 2010 Analog Devices Inc.
 */
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/module.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा ADIS16080_DIN_GYRO   (0 << 10) /* Gyroscope output */
#घोषणा ADIS16080_DIN_TEMP   (1 << 10) /* Temperature output */
#घोषणा ADIS16080_DIN_AIN1   (2 << 10)
#घोषणा ADIS16080_DIN_AIN2   (3 << 10)

/*
 * 1: Write contents on DIN to control रेजिस्टर.
 * 0: No changes to control रेजिस्टर.
 */

#घोषणा ADIS16080_DIN_WRITE  (1 << 15)

काष्ठा adis16080_chip_info अणु
	पूर्णांक scale_val;
	पूर्णांक scale_val2;
पूर्ण;

/**
 * काष्ठा adis16080_state - device instance specअगरic data
 * @us:			actual spi_device to ग_लिखो data
 * @info:		chip specअगरic parameters
 * @buf:		transmit or receive buffer
 * @lock:		lock to protect buffer during पढ़ोs
 **/
काष्ठा adis16080_state अणु
	काष्ठा spi_device		*us;
	स्थिर काष्ठा adis16080_chip_info *info;
	काष्ठा mutex			lock;

	__be16 buf ____cacheline_aligned;
पूर्ण;

अटल पूर्णांक adis16080_पढ़ो_sample(काष्ठा iio_dev *indio_dev,
		u16 addr, पूर्णांक *val)
अणु
	काष्ठा adis16080_state *st = iio_priv(indio_dev);
	पूर्णांक ret;
	काष्ठा spi_transfer	t[] = अणु
		अणु
			.tx_buf		= &st->buf,
			.len		= 2,
			.cs_change	= 1,
		पूर्ण, अणु
			.rx_buf		= &st->buf,
			.len		= 2,
		पूर्ण,
	पूर्ण;

	st->buf = cpu_to_be16(addr | ADIS16080_DIN_WRITE);

	ret = spi_sync_transfer(st->us, t, ARRAY_SIZE(t));
	अगर (ret == 0)
		*val = sign_extend32(be16_to_cpu(st->buf), 11);

	वापस ret;
पूर्ण

अटल पूर्णांक adis16080_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val,
			     पूर्णांक *val2,
			     दीर्घ mask)
अणु
	काष्ठा adis16080_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&st->lock);
		ret = adis16080_पढ़ो_sample(indio_dev, chan->address, val);
		mutex_unlock(&st->lock);
		वापस ret ? ret : IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
			*val = st->info->scale_val;
			*val2 = st->info->scale_val2;
			वापस IIO_VAL_FRACTIONAL;
		हाल IIO_VOLTAGE:
			/* VREF = 5V, 12 bits */
			*val = 5000;
			*val2 = 12;
			वापस IIO_VAL_FRACTIONAL_LOG2;
		हाल IIO_TEMP:
			/* 85 C = 585, 25 C = 0 */
			*val = 85000 - 25000;
			*val2 = 585;
			वापस IIO_VAL_FRACTIONAL;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_OFFSET:
		चयन (chan->type) अणु
		हाल IIO_VOLTAGE:
			/* 2.5 V = 0 */
			*val = 2048;
			वापस IIO_VAL_INT;
		हाल IIO_TEMP:
			/* 85 C = 585, 25 C = 0 */
			*val = DIV_ROUND_CLOSEST(25 * 585, 85 - 25);
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec adis16080_channels[] = अणु
	अणु
		.type = IIO_ANGL_VEL,
		.modअगरied = 1,
		.channel2 = IIO_MOD_Z,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE),
		.address = ADIS16080_DIN_GYRO,
	पूर्ण, अणु
		.type = IIO_VOLTAGE,
		.indexed = 1,
		.channel = 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.address = ADIS16080_DIN_AIN1,
	पूर्ण, अणु
		.type = IIO_VOLTAGE,
		.indexed = 1,
		.channel = 1,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.address = ADIS16080_DIN_AIN2,
	पूर्ण, अणु
		.type = IIO_TEMP,
		.indexed = 1,
		.channel = 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.address = ADIS16080_DIN_TEMP,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा iio_info adis16080_info = अणु
	.पढ़ो_raw = &adis16080_पढ़ो_raw,
पूर्ण;

क्रमागत अणु
	ID_ADIS16080,
	ID_ADIS16100,
पूर्ण;

अटल स्थिर काष्ठा adis16080_chip_info adis16080_chip_info[] = अणु
	[ID_ADIS16080] = अणु
		/* 80 degree = 819, 819 rad = 46925 degree */
		.scale_val = 80,
		.scale_val2 = 46925,
	पूर्ण,
	[ID_ADIS16100] = अणु
		/* 300 degree = 1230, 1230 rad = 70474 degree */
		.scale_val = 300,
		.scale_val2 = 70474,
	पूर्ण,
पूर्ण;

अटल पूर्णांक adis16080_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	काष्ठा adis16080_state *st;
	काष्ठा iio_dev *indio_dev;

	/* setup the industrialio driver allocated elements */
	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;
	st = iio_priv(indio_dev);
	/* this is only used क्रम removal purposes */
	spi_set_drvdata(spi, indio_dev);

	mutex_init(&st->lock);

	/* Allocate the comms buffers */
	st->us = spi;
	st->info = &adis16080_chip_info[id->driver_data];

	indio_dev->name = spi->dev.driver->name;
	indio_dev->channels = adis16080_channels;
	indio_dev->num_channels = ARRAY_SIZE(adis16080_channels);
	indio_dev->info = &adis16080_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	वापस iio_device_रेजिस्टर(indio_dev);
पूर्ण

अटल पूर्णांक adis16080_हटाओ(काष्ठा spi_device *spi)
अणु
	iio_device_unरेजिस्टर(spi_get_drvdata(spi));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id adis16080_ids[] = अणु
	अणु "adis16080", ID_ADIS16080 पूर्ण,
	अणु "adis16100", ID_ADIS16100 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, adis16080_ids);

अटल काष्ठा spi_driver adis16080_driver = अणु
	.driver = अणु
		.name = "adis16080",
	पूर्ण,
	.probe = adis16080_probe,
	.हटाओ = adis16080_हटाओ,
	.id_table = adis16080_ids,
पूर्ण;
module_spi_driver(adis16080_driver);

MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_DESCRIPTION("Analog Devices ADIS16080/100 Yaw Rate Gyroscope Driver");
MODULE_LICENSE("GPL v2");
