<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ADIS16130 Digital Output, High Precision Angular Rate Sensor driver
 *
 * Copyright 2010 Analog Devices Inc.
 */

#समावेश <linux/mutex.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/module.h>

#समावेश <linux/iio/iपन.स>

#समावेश <यंत्र/unaligned.h>

#घोषणा ADIS16130_CON         0x0
#घोषणा ADIS16130_CON_RD      (1 << 6)
#घोषणा ADIS16130_IOP         0x1

/* 1 = data-पढ़ोy संकेत low when unपढ़ो data on all channels; */
#घोषणा ADIS16130_IOP_ALL_RDY (1 << 3)
#घोषणा ADIS16130_IOP_SYNC    (1 << 0) /* 1 = synchronization enabled */
#घोषणा ADIS16130_RATEDATA    0x8 /* Gyroscope output, rate of rotation */
#घोषणा ADIS16130_TEMPDATA    0xA /* Temperature output */
#घोषणा ADIS16130_RATECS      0x28 /* Gyroscope channel setup */
#घोषणा ADIS16130_RATECS_EN   (1 << 3) /* 1 = channel enable; */
#घोषणा ADIS16130_TEMPCS      0x2A /* Temperature channel setup */
#घोषणा ADIS16130_TEMPCS_EN   (1 << 3)
#घोषणा ADIS16130_RATECONV    0x30
#घोषणा ADIS16130_TEMPCONV    0x32
#घोषणा ADIS16130_MODE        0x38
#घोषणा ADIS16130_MODE_24BIT  (1 << 1) /* 1 = 24-bit resolution; */

/**
 * काष्ठा adis16130_state - device instance specअगरic data
 * @us:			actual spi_device to ग_लिखो data
 * @buf_lock:		mutex to protect tx and rx
 * @buf:		unअगरied tx/rx buffer
 **/
काष्ठा adis16130_state अणु
	काष्ठा spi_device		*us;
	काष्ठा mutex			buf_lock;
	u8				buf[4] ____cacheline_aligned;
पूर्ण;

अटल पूर्णांक adis16130_spi_पढ़ो(काष्ठा iio_dev *indio_dev, u8 reg_addr, u32 *val)
अणु
	पूर्णांक ret;
	काष्ठा adis16130_state *st = iio_priv(indio_dev);
	काष्ठा spi_transfer xfer = अणु
		.tx_buf = st->buf,
		.rx_buf = st->buf,
		.len = 4,
	पूर्ण;

	mutex_lock(&st->buf_lock);

	st->buf[0] = ADIS16130_CON_RD | reg_addr;
	st->buf[1] = st->buf[2] = st->buf[3] = 0;

	ret = spi_sync_transfer(st->us, &xfer, 1);
	अगर (ret == 0)
		*val = get_unaligned_be24(&st->buf[1]);
	mutex_unlock(&st->buf_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक adis16130_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक *val, पूर्णांक *val2,
			      दीर्घ mask)
अणु
	पूर्णांक ret;
	u32 temp;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		/* Take the iio_dev status lock */
		ret = adis16130_spi_पढ़ो(indio_dev, chan->address, &temp);
		अगर (ret)
			वापस ret;
		*val = temp;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
			/* 0 degree = 838860, 250 degree = 14260608 */
			*val = 250;
			*val2 = 336440817; /* RAD_TO_DEGREE(14260608 - 8388608) */
			वापस IIO_VAL_FRACTIONAL;
		हाल IIO_TEMP:
			/* 0C = 8036283, 105C = 9516048 */
			*val = 105000;
			*val2 = 9516048 - 8036283;
			वापस IIO_VAL_FRACTIONAL;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_OFFSET:
		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
			*val = -8388608;
			वापस IIO_VAL_INT;
		हाल IIO_TEMP:
			*val = -8036283;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec adis16130_channels[] = अणु
	अणु
		.type = IIO_ANGL_VEL,
		.modअगरied = 1,
		.channel2 = IIO_MOD_Z,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.address = ADIS16130_RATEDATA,
	पूर्ण, अणु
		.type = IIO_TEMP,
		.indexed = 1,
		.channel = 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.address = ADIS16130_TEMPDATA,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा iio_info adis16130_info = अणु
	.पढ़ो_raw = &adis16130_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक adis16130_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा adis16130_state *st;
	काष्ठा iio_dev *indio_dev;

	/* setup the industrialio driver allocated elements */
	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;
	st = iio_priv(indio_dev);
	/* this is only used क्रम removal purposes */
	spi_set_drvdata(spi, indio_dev);
	st->us = spi;
	mutex_init(&st->buf_lock);
	indio_dev->name = spi->dev.driver->name;
	indio_dev->channels = adis16130_channels;
	indio_dev->num_channels = ARRAY_SIZE(adis16130_channels);
	indio_dev->info = &adis16130_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल काष्ठा spi_driver adis16130_driver = अणु
	.driver = अणु
		.name = "adis16130",
	पूर्ण,
	.probe = adis16130_probe,
पूर्ण;
module_spi_driver(adis16130_driver);

MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_DESCRIPTION("Analog Devices ADIS16130 High Precision Angular Rate");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("spi:adis16130");
