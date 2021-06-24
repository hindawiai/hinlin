<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ADXRS450/ADXRS453 Digital Output Gyroscope Driver
 *
 * Copyright 2011 Analog Devices Inc.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा ADXRS450_STARTUP_DELAY	50 /* ms */

/* The MSB क्रम the spi commands */
#घोषणा ADXRS450_SENSOR_DATA    (0x20 << 24)
#घोषणा ADXRS450_WRITE_DATA	(0x40 << 24)
#घोषणा ADXRS450_READ_DATA	(0x80 << 24)

#घोषणा ADXRS450_RATE1	0x00	/* Rate Registers */
#घोषणा ADXRS450_TEMP1	0x02	/* Temperature Registers */
#घोषणा ADXRS450_LOCST1	0x04	/* Low CST Memory Registers */
#घोषणा ADXRS450_HICST1	0x06	/* High CST Memory Registers */
#घोषणा ADXRS450_QUAD1	0x08	/* Quad Memory Registers */
#घोषणा ADXRS450_FAULT1	0x0A	/* Fault Registers */
#घोषणा ADXRS450_PID1	0x0C	/* Part ID Register 1 */
#घोषणा ADXRS450_SNH	0x0E	/* Serial Number Registers, 4 bytes */
#घोषणा ADXRS450_SNL	0x10
#घोषणा ADXRS450_DNC1	0x12	/* Dynamic Null Correction Registers */
/* Check bits */
#घोषणा ADXRS450_P	0x01
#घोषणा ADXRS450_CHK	0x02
#घोषणा ADXRS450_CST	0x04
#घोषणा ADXRS450_PWR	0x08
#घोषणा ADXRS450_POR	0x10
#घोषणा ADXRS450_NVM	0x20
#घोषणा ADXRS450_Q	0x40
#घोषणा ADXRS450_PLL	0x80
#घोषणा ADXRS450_UV	0x100
#घोषणा ADXRS450_OV	0x200
#घोषणा ADXRS450_AMP	0x400
#घोषणा ADXRS450_FAIL	0x800

#घोषणा ADXRS450_WRERR_MASK	(0x7 << 29)

#घोषणा ADXRS450_MAX_RX 4
#घोषणा ADXRS450_MAX_TX 4

#घोषणा ADXRS450_GET_ST(a)	((a >> 26) & 0x3)

क्रमागत अणु
	ID_ADXRS450,
	ID_ADXRS453,
पूर्ण;

/**
 * काष्ठा adxrs450_state - device instance specअगरic data
 * @us:			actual spi_device
 * @buf_lock:		mutex to protect tx and rx
 * @tx:			transmit buffer
 * @rx:			receive buffer
 **/
काष्ठा adxrs450_state अणु
	काष्ठा spi_device	*us;
	काष्ठा mutex		buf_lock;
	__be32			tx ____cacheline_aligned;
	__be32			rx;

पूर्ण;

/**
 * adxrs450_spi_पढ़ो_reg_16() - पढ़ो 2 bytes from a रेजिस्टर pair
 * @indio_dev: device associated with child of actual iio_dev
 * @reg_address: the address of the lower of the two रेजिस्टरs, which should be
 *	an even address, the second रेजिस्टर's address is reg_address + 1.
 * @val: somewhere to pass back the value पढ़ो
 **/
अटल पूर्णांक adxrs450_spi_पढ़ो_reg_16(काष्ठा iio_dev *indio_dev,
				    u8 reg_address,
				    u16 *val)
अणु
	काष्ठा adxrs450_state *st = iio_priv(indio_dev);
	u32 tx;
	पूर्णांक ret;
	काष्ठा spi_transfer xfers[] = अणु
		अणु
			.tx_buf = &st->tx,
			.bits_per_word = 8,
			.len = माप(st->tx),
			.cs_change = 1,
		पूर्ण, अणु
			.rx_buf = &st->rx,
			.bits_per_word = 8,
			.len = माप(st->rx),
		पूर्ण,
	पूर्ण;

	mutex_lock(&st->buf_lock);
	tx = ADXRS450_READ_DATA | (reg_address << 17);

	अगर (!(hweight32(tx) & 1))
		tx |= ADXRS450_P;

	st->tx = cpu_to_be32(tx);
	ret = spi_sync_transfer(st->us, xfers, ARRAY_SIZE(xfers));
	अगर (ret) अणु
		dev_err(&st->us->dev, "problem while reading 16 bit register 0x%02x\n",
				reg_address);
		जाओ error_ret;
	पूर्ण

	*val = (be32_to_cpu(st->rx) >> 5) & 0xFFFF;

error_ret:
	mutex_unlock(&st->buf_lock);
	वापस ret;
पूर्ण

/**
 * adxrs450_spi_ग_लिखो_reg_16() - ग_लिखो 2 bytes data to a रेजिस्टर pair
 * @indio_dev: device associated with child of actual actual iio_dev
 * @reg_address: the address of the lower of the two रेजिस्टरs,which should be
 *	an even address, the second रेजिस्टर's address is reg_address + 1.
 * @val: value to be written.
 **/
अटल पूर्णांक adxrs450_spi_ग_लिखो_reg_16(काष्ठा iio_dev *indio_dev,
				     u8 reg_address,
				     u16 val)
अणु
	काष्ठा adxrs450_state *st = iio_priv(indio_dev);
	u32 tx;
	पूर्णांक ret;

	mutex_lock(&st->buf_lock);
	tx = ADXRS450_WRITE_DATA | (reg_address << 17) | (val << 1);

	अगर (!(hweight32(tx) & 1))
		tx |= ADXRS450_P;

	st->tx = cpu_to_be32(tx);
	ret = spi_ग_लिखो(st->us, &st->tx, माप(st->tx));
	अगर (ret)
		dev_err(&st->us->dev, "problem while writing 16 bit register 0x%02x\n",
			reg_address);
	usleep_range(100, 1000); /* enक्रमce sequential transfer delay 0.1ms */
	mutex_unlock(&st->buf_lock);
	वापस ret;
पूर्ण

/**
 * adxrs450_spi_sensor_data() - पढ़ो 2 bytes sensor data
 * @indio_dev: device associated with child of actual iio_dev
 * @val: somewhere to pass back the value पढ़ो
 **/
अटल पूर्णांक adxrs450_spi_sensor_data(काष्ठा iio_dev *indio_dev, s16 *val)
अणु
	काष्ठा adxrs450_state *st = iio_priv(indio_dev);
	पूर्णांक ret;
	काष्ठा spi_transfer xfers[] = अणु
		अणु
			.tx_buf = &st->tx,
			.bits_per_word = 8,
			.len = माप(st->tx),
			.cs_change = 1,
		पूर्ण, अणु
			.rx_buf = &st->rx,
			.bits_per_word = 8,
			.len = माप(st->rx),
		पूर्ण,
	पूर्ण;

	mutex_lock(&st->buf_lock);
	st->tx = cpu_to_be32(ADXRS450_SENSOR_DATA);

	ret = spi_sync_transfer(st->us, xfers, ARRAY_SIZE(xfers));
	अगर (ret) अणु
		dev_err(&st->us->dev, "Problem while reading sensor data\n");
		जाओ error_ret;
	पूर्ण

	*val = (be32_to_cpu(st->rx) >> 10) & 0xFFFF;

error_ret:
	mutex_unlock(&st->buf_lock);
	वापस ret;
पूर्ण

/**
 * adxrs450_spi_initial() - use क्रम initializing procedure.
 * @st: device instance specअगरic data
 * @val: somewhere to pass back the value पढ़ो
 * @chk: Whether to perक्रमm fault check
 **/
अटल पूर्णांक adxrs450_spi_initial(काष्ठा adxrs450_state *st,
		u32 *val, अक्षर chk)
अणु
	पूर्णांक ret;
	u32 tx;
	काष्ठा spi_transfer xfers = अणु
		.tx_buf = &st->tx,
		.rx_buf = &st->rx,
		.bits_per_word = 8,
		.len = माप(st->tx),
	पूर्ण;

	mutex_lock(&st->buf_lock);
	tx = ADXRS450_SENSOR_DATA;
	अगर (chk)
		tx |= (ADXRS450_CHK | ADXRS450_P);
	st->tx = cpu_to_be32(tx);
	ret = spi_sync_transfer(st->us, &xfers, 1);
	अगर (ret) अणु
		dev_err(&st->us->dev, "Problem while reading initializing data\n");
		जाओ error_ret;
	पूर्ण

	*val = be32_to_cpu(st->rx);

error_ret:
	mutex_unlock(&st->buf_lock);
	वापस ret;
पूर्ण

/* Recommended Startup Sequence by spec */
अटल पूर्णांक adxrs450_initial_setup(काष्ठा iio_dev *indio_dev)
अणु
	u32 t;
	u16 data;
	पूर्णांक ret;
	काष्ठा adxrs450_state *st = iio_priv(indio_dev);

	msleep(ADXRS450_STARTUP_DELAY*2);
	ret = adxrs450_spi_initial(st, &t, 1);
	अगर (ret)
		वापस ret;
	अगर (t != 0x01)
		dev_warn(&st->us->dev, "The initial power on response is not correct! Restart without reset?\n");

	msleep(ADXRS450_STARTUP_DELAY);
	ret = adxrs450_spi_initial(st, &t, 0);
	अगर (ret)
		वापस ret;

	msleep(ADXRS450_STARTUP_DELAY);
	ret = adxrs450_spi_initial(st, &t, 0);
	अगर (ret)
		वापस ret;
	अगर (((t & 0xff) | 0x01) != 0xff || ADXRS450_GET_ST(t) != 2) अणु
		dev_err(&st->us->dev, "The second response is not correct!\n");
		वापस -EIO;

	पूर्ण
	ret = adxrs450_spi_initial(st, &t, 0);
	अगर (ret)
		वापस ret;
	अगर (((t & 0xff) | 0x01) != 0xff || ADXRS450_GET_ST(t) != 2) अणु
		dev_err(&st->us->dev, "The third response is not correct!\n");
		वापस -EIO;

	पूर्ण
	ret = adxrs450_spi_पढ़ो_reg_16(indio_dev, ADXRS450_FAULT1, &data);
	अगर (ret)
		वापस ret;
	अगर (data & 0x0fff) अणु
		dev_err(&st->us->dev, "The device is not in normal status!\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक adxrs450_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक val,
			      पूर्णांक val2,
			      दीर्घ mask)
अणु
	पूर्णांक ret;
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_CALIBBIAS:
		अगर (val < -0x400 || val >= 0x400)
			वापस -EINVAL;
		ret = adxrs450_spi_ग_लिखो_reg_16(indio_dev,
						ADXRS450_DNC1, val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक adxrs450_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val,
			     पूर्णांक *val2,
			     दीर्घ mask)
अणु
	पूर्णांक ret;
	s16 t;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
			ret = adxrs450_spi_sensor_data(indio_dev, &t);
			अगर (ret)
				अवरोध;
			*val = t;
			ret = IIO_VAL_INT;
			अवरोध;
		हाल IIO_TEMP:
			ret = adxrs450_spi_पढ़ो_reg_16(indio_dev,
						       ADXRS450_TEMP1, &t);
			अगर (ret)
				अवरोध;
			*val = (t >> 6) + 225;
			ret = IIO_VAL_INT;
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
			*val = 0;
			*val2 = 218166;
			वापस IIO_VAL_INT_PLUS_न_अंकO;
		हाल IIO_TEMP:
			*val = 200;
			*val2 = 0;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_QUADRATURE_CORRECTION_RAW:
		ret = adxrs450_spi_पढ़ो_reg_16(indio_dev, ADXRS450_QUAD1, &t);
		अगर (ret)
			अवरोध;
		*val = t;
		ret = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		ret = adxrs450_spi_पढ़ो_reg_16(indio_dev, ADXRS450_DNC1, &t);
		अगर (ret)
			अवरोध;
		*val = sign_extend32(t, 9);
		ret = IIO_VAL_INT;
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec adxrs450_channels[2][2] = अणु
	[ID_ADXRS450] = अणु
		अणु
			.type = IIO_ANGL_VEL,
			.modअगरied = 1,
			.channel2 = IIO_MOD_Z,
			.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_CALIBBIAS) |
			BIT(IIO_CHAN_INFO_QUADRATURE_CORRECTION_RAW) |
			BIT(IIO_CHAN_INFO_SCALE),
		पूर्ण, अणु
			.type = IIO_TEMP,
			.indexed = 1,
			.channel = 0,
			.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE),
		पूर्ण
	पूर्ण,
	[ID_ADXRS453] = अणु
		अणु
			.type = IIO_ANGL_VEL,
			.modअगरied = 1,
			.channel2 = IIO_MOD_Z,
			.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_QUADRATURE_CORRECTION_RAW),
		पूर्ण, अणु
			.type = IIO_TEMP,
			.indexed = 1,
			.channel = 0,
			.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE),
		पूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_info adxrs450_info = अणु
	.पढ़ो_raw = &adxrs450_पढ़ो_raw,
	.ग_लिखो_raw = &adxrs450_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक adxrs450_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
	काष्ठा adxrs450_state *st;
	काष्ठा iio_dev *indio_dev;

	/* setup the industrialio driver allocated elements */
	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;
	st = iio_priv(indio_dev);
	st->us = spi;
	mutex_init(&st->buf_lock);
	/* This is only used क्रम removal purposes */
	spi_set_drvdata(spi, indio_dev);

	indio_dev->info = &adxrs450_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels =
		adxrs450_channels[spi_get_device_id(spi)->driver_data];
	indio_dev->num_channels = ARRAY_SIZE(adxrs450_channels);
	indio_dev->name = spi->dev.driver->name;

	ret = devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
	अगर (ret)
		वापस ret;

	/* Get the device पूर्णांकo a sane initial state */
	ret = adxrs450_initial_setup(indio_dev);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id adxrs450_id[] = अणु
	अणु"adxrs450", ID_ADXRS450पूर्ण,
	अणु"adxrs453", ID_ADXRS453पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, adxrs450_id);

अटल काष्ठा spi_driver adxrs450_driver = अणु
	.driver = अणु
		.name = "adxrs450",
	पूर्ण,
	.probe = adxrs450_probe,
	.id_table	= adxrs450_id,
पूर्ण;
module_spi_driver(adxrs450_driver);

MODULE_AUTHOR("Cliff Cai <cliff.cai@xxxxxxxxxx>");
MODULE_DESCRIPTION("Analog Devices ADXRS450/ADXRS453 Gyroscope SPI driver");
MODULE_LICENSE("GPL v2");
