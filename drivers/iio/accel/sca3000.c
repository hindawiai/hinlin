<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sca3000_core.c -- support VTI sca3000 series accelerometers via SPI
 *
 * Copyright (c) 2009 Jonathan Cameron <jic23@kernel.org>
 *
 * See industrialio/accels/sca3000.h क्रम comments.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fs.h>
#समावेश <linux/device.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/kfअगरo_buf.h>

#घोषणा SCA3000_WRITE_REG(a) (((a) << 2) | 0x02)
#घोषणा SCA3000_READ_REG(a) ((a) << 2)

#घोषणा SCA3000_REG_REVID_ADDR				0x00
#घोषणा   SCA3000_REG_REVID_MAJOR_MASK			GENMASK(8, 4)
#घोषणा   SCA3000_REG_REVID_MINOR_MASK			GENMASK(3, 0)

#घोषणा SCA3000_REG_STATUS_ADDR				0x02
#घोषणा   SCA3000_LOCKED				BIT(5)
#घोषणा   SCA3000_EEPROM_CS_ERROR			BIT(1)
#घोषणा   SCA3000_SPI_FRAME_ERROR			BIT(0)

/* All पढ़ोs करोne using रेजिस्टर decrement so no need to directly access LSBs */
#घोषणा SCA3000_REG_X_MSB_ADDR				0x05
#घोषणा SCA3000_REG_Y_MSB_ADDR				0x07
#घोषणा SCA3000_REG_Z_MSB_ADDR				0x09

#घोषणा SCA3000_REG_RING_OUT_ADDR			0x0f

/* Temp पढ़ो untested - the e05 करोesn't have the sensor */
#घोषणा SCA3000_REG_TEMP_MSB_ADDR			0x13

#घोषणा SCA3000_REG_MODE_ADDR				0x14
#घोषणा SCA3000_MODE_PROT_MASK				0x28
#घोषणा   SCA3000_REG_MODE_RING_BUF_ENABLE		BIT(7)
#घोषणा   SCA3000_REG_MODE_RING_BUF_8BIT		BIT(6)

/*
 * Free fall detection triggers an पूर्णांकerrupt अगर the acceleration
 * is below a threshold क्रम equivalent of 25cm drop
 */
#घोषणा   SCA3000_REG_MODE_FREE_FALL_DETECT		BIT(4)
#घोषणा   SCA3000_REG_MODE_MEAS_MODE_NORMAL		0x00
#घोषणा   SCA3000_REG_MODE_MEAS_MODE_OP_1		0x01
#घोषणा   SCA3000_REG_MODE_MEAS_MODE_OP_2		0x02

/*
 * In motion detection mode the accelerations are band pass filtered
 * (approx 1 - 25Hz) and then a programmable threshold used to trigger
 * and पूर्णांकerrupt.
 */
#घोषणा   SCA3000_REG_MODE_MEAS_MODE_MOT_DET		0x03
#घोषणा   SCA3000_REG_MODE_MODE_MASK			0x03

#घोषणा SCA3000_REG_BUF_COUNT_ADDR			0x15

#घोषणा SCA3000_REG_INT_STATUS_ADDR			0x16
#घोषणा   SCA3000_REG_INT_STATUS_THREE_QUARTERS		BIT(7)
#घोषणा   SCA3000_REG_INT_STATUS_HALF			BIT(6)

#घोषणा SCA3000_INT_STATUS_FREE_FALL			BIT(3)
#घोषणा SCA3000_INT_STATUS_Y_TRIGGER			BIT(2)
#घोषणा SCA3000_INT_STATUS_X_TRIGGER			BIT(1)
#घोषणा SCA3000_INT_STATUS_Z_TRIGGER			BIT(0)

/* Used to allow access to multiplexed रेजिस्टरs */
#घोषणा SCA3000_REG_CTRL_SEL_ADDR			0x18
/* Only available क्रम SCA3000-D03 and SCA3000-D01 */
#घोषणा   SCA3000_REG_CTRL_SEL_I2C_DISABLE		0x01
#घोषणा   SCA3000_REG_CTRL_SEL_MD_CTRL			0x02
#घोषणा   SCA3000_REG_CTRL_SEL_MD_Y_TH			0x03
#घोषणा   SCA3000_REG_CTRL_SEL_MD_X_TH			0x04
#घोषणा   SCA3000_REG_CTRL_SEL_MD_Z_TH			0x05
/*
 * BE VERY CAREFUL WITH THIS, IF 3 BITS ARE NOT SET the device
 * will not function
 */
#घोषणा   SCA3000_REG_CTRL_SEL_OUT_CTRL			0x0B

#घोषणा     SCA3000_REG_OUT_CTRL_PROT_MASK		0xE0
#घोषणा     SCA3000_REG_OUT_CTRL_BUF_X_EN		0x10
#घोषणा     SCA3000_REG_OUT_CTRL_BUF_Y_EN		0x08
#घोषणा     SCA3000_REG_OUT_CTRL_BUF_Z_EN		0x04
#घोषणा     SCA3000_REG_OUT_CTRL_BUF_DIV_MASK		0x03
#घोषणा     SCA3000_REG_OUT_CTRL_BUF_DIV_4		0x02
#घोषणा     SCA3000_REG_OUT_CTRL_BUF_DIV_2		0x01


/*
 * Control which motion detector पूर्णांकerrupts are on.
 * For now only OR combinations are supported.
 */
#घोषणा SCA3000_MD_CTRL_PROT_MASK			0xC0
#घोषणा SCA3000_MD_CTRL_OR_Y				BIT(0)
#घोषणा SCA3000_MD_CTRL_OR_X				BIT(1)
#घोषणा SCA3000_MD_CTRL_OR_Z				BIT(2)
/* Currently unsupported */
#घोषणा SCA3000_MD_CTRL_AND_Y				BIT(3)
#घोषणा SCA3000_MD_CTRL_AND_X				BIT(4)
#घोषणा SCA3000_MD_CTRL_AND_Z				BIT(5)

/*
 * Some control रेजिस्टरs of complex access methods requiring this रेजिस्टर to
 * be used to हटाओ a lock.
 */
#घोषणा SCA3000_REG_UNLOCK_ADDR				0x1e

#घोषणा SCA3000_REG_INT_MASK_ADDR			0x21
#घोषणा   SCA3000_REG_INT_MASK_PROT_MASK		0x1C

#घोषणा   SCA3000_REG_INT_MASK_RING_THREE_QUARTER	BIT(7)
#घोषणा   SCA3000_REG_INT_MASK_RING_HALF		BIT(6)

#घोषणा SCA3000_REG_INT_MASK_ALL_INTS			0x02
#घोषणा SCA3000_REG_INT_MASK_ACTIVE_HIGH		0x01
#घोषणा SCA3000_REG_INT_MASK_ACTIVE_LOW			0x00
/* Values of multiplexed रेजिस्टरs (ग_लिखो to ctrl_data after select) */
#घोषणा SCA3000_REG_CTRL_DATA_ADDR			0x22

/*
 * Measurement modes available on some sca3000 series chips. Code assumes others
 * may become available in the future.
 *
 * Bypass - Bypass the low-pass filter in the संकेत channel so as to increase
 *          संकेत bandwidth.
 *
 * Narrow - Narrow low-pass filtering of the संकेत channel and half output
 *          data rate by decimation.
 *
 * Wide - Widen low-pass filtering of संकेत channel to increase bandwidth
 */
#घोषणा SCA3000_OP_MODE_BYPASS				0x01
#घोषणा SCA3000_OP_MODE_NARROW				0x02
#घोषणा SCA3000_OP_MODE_WIDE				0x04
#घोषणा SCA3000_MAX_TX 6
#घोषणा SCA3000_MAX_RX 2

/**
 * काष्ठा sca3000_state - device instance state inक्रमmation
 * @us:			the associated spi device
 * @info:			chip variant inक्रमmation
 * @last_बारtamp:		the बारtamp of the last event
 * @mo_det_use_count:		reference counter क्रम the motion detection unit
 * @lock:			lock used to protect elements of sca3000_state
 *				and the underlying device state.
 * @tx:			dma-able transmit buffer
 * @rx:			dma-able receive buffer
 **/
काष्ठा sca3000_state अणु
	काष्ठा spi_device		*us;
	स्थिर काष्ठा sca3000_chip_info	*info;
	s64				last_बारtamp;
	पूर्णांक				mo_det_use_count;
	काष्ठा mutex			lock;
	/* Can these share a cacheline ? */
	u8				rx[384] ____cacheline_aligned;
	u8				tx[6] ____cacheline_aligned;
पूर्ण;

/**
 * काष्ठा sca3000_chip_info - model dependent parameters
 * @scale:			scale * 10^-6
 * @temp_output:		some devices have temperature sensors.
 * @measurement_mode_freq:	normal mode sampling frequency
 * @measurement_mode_3db_freq:	3db cutoff frequency of the low pass filter क्रम
 * the normal measurement mode.
 * @option_mode_1:		first optional mode. Not all models have one
 * @option_mode_1_freq:		option mode 1 sampling frequency
 * @option_mode_1_3db_freq:	3db cutoff frequency of the low pass filter क्रम
 * the first option mode.
 * @option_mode_2:		second optional mode. Not all chips have one
 * @option_mode_2_freq:		option mode 2 sampling frequency
 * @option_mode_2_3db_freq:	3db cutoff frequency of the low pass filter क्रम
 * the second option mode.
 * @mot_det_mult_xz:		Bit wise multipliers to calculate the threshold
 * क्रम motion detection in the x and z axis.
 * @mot_det_mult_y:		Bit wise multipliers to calculate the threshold
 * क्रम motion detection in the y axis.
 *
 * This काष्ठाure is used to hold inक्रमmation about the functionality of a given
 * sca3000 variant.
 **/
काष्ठा sca3000_chip_info अणु
	अचिन्हित पूर्णांक		scale;
	bool			temp_output;
	पूर्णांक			measurement_mode_freq;
	पूर्णांक			measurement_mode_3db_freq;
	पूर्णांक			option_mode_1;
	पूर्णांक			option_mode_1_freq;
	पूर्णांक			option_mode_1_3db_freq;
	पूर्णांक			option_mode_2;
	पूर्णांक			option_mode_2_freq;
	पूर्णांक			option_mode_2_3db_freq;
	पूर्णांक			mot_det_mult_xz[6];
	पूर्णांक			mot_det_mult_y[7];
पूर्ण;

क्रमागत sca3000_variant अणु
	d01,
	e02,
	e04,
	e05,
पूर्ण;

/*
 * Note where option modes are not defined, the chip simply करोes not
 * support any.
 * Other chips in the sca3000 series use i2c and are not included here.
 *
 * Some of these devices are only listed in the family data sheet and
 * करो not actually appear to be available.
 */
अटल स्थिर काष्ठा sca3000_chip_info sca3000_spi_chip_info_tbl[] = अणु
	[d01] = अणु
		.scale = 7357,
		.temp_output = true,
		.measurement_mode_freq = 250,
		.measurement_mode_3db_freq = 45,
		.option_mode_1 = SCA3000_OP_MODE_BYPASS,
		.option_mode_1_freq = 250,
		.option_mode_1_3db_freq = 70,
		.mot_det_mult_xz = अणु50, 100, 200, 350, 650, 1300पूर्ण,
		.mot_det_mult_y = अणु50, 100, 150, 250, 450, 850, 1750पूर्ण,
	पूर्ण,
	[e02] = अणु
		.scale = 9810,
		.measurement_mode_freq = 125,
		.measurement_mode_3db_freq = 40,
		.option_mode_1 = SCA3000_OP_MODE_NARROW,
		.option_mode_1_freq = 63,
		.option_mode_1_3db_freq = 11,
		.mot_det_mult_xz = अणु100, 150, 300, 550, 1050, 2050पूर्ण,
		.mot_det_mult_y = अणु50, 100, 200, 350, 700, 1350, 2700पूर्ण,
	पूर्ण,
	[e04] = अणु
		.scale = 19620,
		.measurement_mode_freq = 100,
		.measurement_mode_3db_freq = 38,
		.option_mode_1 = SCA3000_OP_MODE_NARROW,
		.option_mode_1_freq = 50,
		.option_mode_1_3db_freq = 9,
		.option_mode_2 = SCA3000_OP_MODE_WIDE,
		.option_mode_2_freq = 400,
		.option_mode_2_3db_freq = 70,
		.mot_det_mult_xz = अणु200, 300, 600, 1100, 2100, 4100पूर्ण,
		.mot_det_mult_y = अणु100, 200, 400, 7000, 1400, 2700, 54000पूर्ण,
	पूर्ण,
	[e05] = अणु
		.scale = 61313,
		.measurement_mode_freq = 200,
		.measurement_mode_3db_freq = 60,
		.option_mode_1 = SCA3000_OP_MODE_NARROW,
		.option_mode_1_freq = 50,
		.option_mode_1_3db_freq = 9,
		.option_mode_2 = SCA3000_OP_MODE_WIDE,
		.option_mode_2_freq = 400,
		.option_mode_2_3db_freq = 75,
		.mot_det_mult_xz = अणु600, 900, 1700, 3200, 6100, 11900पूर्ण,
		.mot_det_mult_y = अणु300, 600, 1200, 2000, 4100, 7800, 15600पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक sca3000_ग_लिखो_reg(काष्ठा sca3000_state *st, u8 address, u8 val)
अणु
	st->tx[0] = SCA3000_WRITE_REG(address);
	st->tx[1] = val;
	वापस spi_ग_लिखो(st->us, st->tx, 2);
पूर्ण

अटल पूर्णांक sca3000_पढ़ो_data_लघु(काष्ठा sca3000_state *st,
				   u8 reg_address_high,
				   पूर्णांक len)
अणु
	काष्ठा spi_transfer xfer[2] = अणु
		अणु
			.len = 1,
			.tx_buf = st->tx,
		पूर्ण, अणु
			.len = len,
			.rx_buf = st->rx,
		पूर्ण
	पूर्ण;
	st->tx[0] = SCA3000_READ_REG(reg_address_high);

	वापस spi_sync_transfer(st->us, xfer, ARRAY_SIZE(xfer));
पूर्ण

/**
 * sca3000_reg_lock_on() - test अगर the ctrl रेजिस्टर lock is on
 * @st: Driver specअगरic device instance data.
 *
 * Lock must be held.
 **/
अटल पूर्णांक sca3000_reg_lock_on(काष्ठा sca3000_state *st)
अणु
	पूर्णांक ret;

	ret = sca3000_पढ़ो_data_लघु(st, SCA3000_REG_STATUS_ADDR, 1);
	अगर (ret < 0)
		वापस ret;

	वापस !(st->rx[0] & SCA3000_LOCKED);
पूर्ण

/**
 * __sca3000_unlock_reg_lock() - unlock the control रेजिस्टरs
 * @st: Driver specअगरic device instance data.
 *
 * Note the device करोes not appear to support करोing this in a single transfer.
 * This should only ever be used as part of ctrl reg पढ़ो.
 * Lock must be held beक्रमe calling this
 */
अटल पूर्णांक __sca3000_unlock_reg_lock(काष्ठा sca3000_state *st)
अणु
	काष्ठा spi_transfer xfer[3] = अणु
		अणु
			.len = 2,
			.cs_change = 1,
			.tx_buf = st->tx,
		पूर्ण, अणु
			.len = 2,
			.cs_change = 1,
			.tx_buf = st->tx + 2,
		पूर्ण, अणु
			.len = 2,
			.tx_buf = st->tx + 4,
		पूर्ण,
	पूर्ण;
	st->tx[0] = SCA3000_WRITE_REG(SCA3000_REG_UNLOCK_ADDR);
	st->tx[1] = 0x00;
	st->tx[2] = SCA3000_WRITE_REG(SCA3000_REG_UNLOCK_ADDR);
	st->tx[3] = 0x50;
	st->tx[4] = SCA3000_WRITE_REG(SCA3000_REG_UNLOCK_ADDR);
	st->tx[5] = 0xA0;

	वापस spi_sync_transfer(st->us, xfer, ARRAY_SIZE(xfer));
पूर्ण

/**
 * sca3000_ग_लिखो_ctrl_reg() - ग_लिखो to a lock protect ctrl रेजिस्टर
 * @st: Driver specअगरic device instance data.
 * @sel: selects which रेजिस्टरs we wish to ग_लिखो to
 * @val: the value to be written
 *
 * Certain control रेजिस्टरs are रक्षित against overwriting by the lock
 * रेजिस्टर and use a shared ग_लिखो address. This function allows writing of
 * these रेजिस्टरs.
 * Lock must be held.
 */
अटल पूर्णांक sca3000_ग_लिखो_ctrl_reg(काष्ठा sca3000_state *st,
				  u8 sel,
				  uपूर्णांक8_t val)
अणु
	पूर्णांक ret;

	ret = sca3000_reg_lock_on(st);
	अगर (ret < 0)
		जाओ error_ret;
	अगर (ret) अणु
		ret = __sca3000_unlock_reg_lock(st);
		अगर (ret)
			जाओ error_ret;
	पूर्ण

	/* Set the control select रेजिस्टर */
	ret = sca3000_ग_लिखो_reg(st, SCA3000_REG_CTRL_SEL_ADDR, sel);
	अगर (ret)
		जाओ error_ret;

	/* Write the actual value पूर्णांकo the रेजिस्टर */
	ret = sca3000_ग_लिखो_reg(st, SCA3000_REG_CTRL_DATA_ADDR, val);

error_ret:
	वापस ret;
पूर्ण

/**
 * sca3000_पढ़ो_ctrl_reg() - पढ़ो from lock रक्षित control रेजिस्टर.
 * @st: Driver specअगरic device instance data.
 * @ctrl_reg: Which ctrl रेजिस्टर करो we want to पढ़ो.
 *
 * Lock must be held.
 */
अटल पूर्णांक sca3000_पढ़ो_ctrl_reg(काष्ठा sca3000_state *st,
				 u8 ctrl_reg)
अणु
	पूर्णांक ret;

	ret = sca3000_reg_lock_on(st);
	अगर (ret < 0)
		जाओ error_ret;
	अगर (ret) अणु
		ret = __sca3000_unlock_reg_lock(st);
		अगर (ret)
			जाओ error_ret;
	पूर्ण
	/* Set the control select रेजिस्टर */
	ret = sca3000_ग_लिखो_reg(st, SCA3000_REG_CTRL_SEL_ADDR, ctrl_reg);
	अगर (ret)
		जाओ error_ret;
	ret = sca3000_पढ़ो_data_लघु(st, SCA3000_REG_CTRL_DATA_ADDR, 1);
	अगर (ret)
		जाओ error_ret;
	वापस st->rx[0];
error_ret:
	वापस ret;
पूर्ण

/**
 * sca3000_prपूर्णांक_rev() - sysfs पूर्णांकerface to पढ़ो the chip revision number
 * @indio_dev: Device instance specअगरic generic IIO data.
 * Driver specअगरic device instance data can be obtained via
 * via iio_priv(indio_dev)
 */
अटल पूर्णांक sca3000_prपूर्णांक_rev(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret;
	काष्ठा sca3000_state *st = iio_priv(indio_dev);

	mutex_lock(&st->lock);
	ret = sca3000_पढ़ो_data_लघु(st, SCA3000_REG_REVID_ADDR, 1);
	अगर (ret < 0)
		जाओ error_ret;
	dev_info(&indio_dev->dev,
		 "sca3000 revision major=%lu, minor=%lu\n",
		 st->rx[0] & SCA3000_REG_REVID_MAJOR_MASK,
		 st->rx[0] & SCA3000_REG_REVID_MINOR_MASK);
error_ret:
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार
sca3000_show_available_3db_freqs(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा sca3000_state *st = iio_priv(indio_dev);
	पूर्णांक len;

	len = प्र_लिखो(buf, "%d", st->info->measurement_mode_3db_freq);
	अगर (st->info->option_mode_1)
		len += प्र_लिखो(buf + len, " %d",
			       st->info->option_mode_1_3db_freq);
	अगर (st->info->option_mode_2)
		len += प्र_लिखो(buf + len, " %d",
			       st->info->option_mode_2_3db_freq);
	len += प्र_लिखो(buf + len, "\n");

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(in_accel_filter_low_pass_3db_frequency_available,
		       S_IRUGO, sca3000_show_available_3db_freqs,
		       शून्य, 0);

अटल स्थिर काष्ठा iio_event_spec sca3000_event = अणु
	.type = IIO_EV_TYPE_MAG,
	.dir = IIO_EV_सूची_RISING,
	.mask_separate = BIT(IIO_EV_INFO_VALUE) | BIT(IIO_EV_INFO_ENABLE),
पूर्ण;

/*
 * Note the hack in the number of bits to pretend we have 2 more than
 * we करो in the fअगरo.
 */
#घोषणा SCA3000_CHAN(index, mod)				\
	अणु							\
		.type = IIO_ACCEL,				\
		.modअगरied = 1,					\
		.channel2 = mod,				\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |\
			BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY),\
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),\
		.address = index,				\
		.scan_index = index,				\
		.scan_type = अणु					\
			.sign = 's',				\
			.realbits = 13,				\
			.storagebits = 16,			\
			.shअगरt = 3,				\
			.endianness = IIO_BE,			\
		पूर्ण,						\
		.event_spec = &sca3000_event,			\
		.num_event_specs = 1,				\
	पूर्ण

अटल स्थिर काष्ठा iio_event_spec sca3000_मुक्तfall_event_spec = अणु
	.type = IIO_EV_TYPE_MAG,
	.dir = IIO_EV_सूची_FALLING,
	.mask_separate = BIT(IIO_EV_INFO_ENABLE) |
		BIT(IIO_EV_INFO_PERIOD),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec sca3000_channels[] = अणु
	SCA3000_CHAN(0, IIO_MOD_X),
	SCA3000_CHAN(1, IIO_MOD_Y),
	SCA3000_CHAN(2, IIO_MOD_Z),
	अणु
		.type = IIO_ACCEL,
		.modअगरied = 1,
		.channel2 = IIO_MOD_X_AND_Y_AND_Z,
		.scan_index = -1, /* Fake channel */
		.event_spec = &sca3000_मुक्तfall_event_spec,
		.num_event_specs = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec sca3000_channels_with_temp[] = अणु
	SCA3000_CHAN(0, IIO_MOD_X),
	SCA3000_CHAN(1, IIO_MOD_Y),
	SCA3000_CHAN(2, IIO_MOD_Z),
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		/* No buffer support */
		.scan_index = -1,
	पूर्ण,
	अणु
		.type = IIO_ACCEL,
		.modअगरied = 1,
		.channel2 = IIO_MOD_X_AND_Y_AND_Z,
		.scan_index = -1, /* Fake channel */
		.event_spec = &sca3000_मुक्तfall_event_spec,
		.num_event_specs = 1,
	पूर्ण,
पूर्ण;

अटल u8 sca3000_addresses[3][3] = अणु
	[0] = अणुSCA3000_REG_X_MSB_ADDR, SCA3000_REG_CTRL_SEL_MD_X_TH,
	       SCA3000_MD_CTRL_OR_Xपूर्ण,
	[1] = अणुSCA3000_REG_Y_MSB_ADDR, SCA3000_REG_CTRL_SEL_MD_Y_TH,
	       SCA3000_MD_CTRL_OR_Yपूर्ण,
	[2] = अणुSCA3000_REG_Z_MSB_ADDR, SCA3000_REG_CTRL_SEL_MD_Z_TH,
	       SCA3000_MD_CTRL_OR_Zपूर्ण,
पूर्ण;

/**
 * __sca3000_get_base_freq() - obtain mode specअगरic base frequency
 * @st: Private driver specअगरic device instance specअगरic state.
 * @info: chip type specअगरic inक्रमmation.
 * @base_freq: Base frequency क्रम the current measurement mode.
 *
 * lock must be held
 */
अटल अंतरभूत पूर्णांक __sca3000_get_base_freq(काष्ठा sca3000_state *st,
					  स्थिर काष्ठा sca3000_chip_info *info,
					  पूर्णांक *base_freq)
अणु
	पूर्णांक ret;

	ret = sca3000_पढ़ो_data_लघु(st, SCA3000_REG_MODE_ADDR, 1);
	अगर (ret)
		जाओ error_ret;
	चयन (SCA3000_REG_MODE_MODE_MASK & st->rx[0]) अणु
	हाल SCA3000_REG_MODE_MEAS_MODE_NORMAL:
		*base_freq = info->measurement_mode_freq;
		अवरोध;
	हाल SCA3000_REG_MODE_MEAS_MODE_OP_1:
		*base_freq = info->option_mode_1_freq;
		अवरोध;
	हाल SCA3000_REG_MODE_MEAS_MODE_OP_2:
		*base_freq = info->option_mode_2_freq;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
error_ret:
	वापस ret;
पूर्ण

/**
 * sca3000_पढ़ो_raw_samp_freq() - पढ़ो_raw handler क्रम IIO_CHAN_INFO_SAMP_FREQ
 * @st: Private driver specअगरic device instance specअगरic state.
 * @val: The frequency पढ़ो back.
 *
 * lock must be held
 **/
अटल पूर्णांक sca3000_पढ़ो_raw_samp_freq(काष्ठा sca3000_state *st, पूर्णांक *val)
अणु
	पूर्णांक ret;

	ret = __sca3000_get_base_freq(st, st->info, val);
	अगर (ret)
		वापस ret;

	ret = sca3000_पढ़ो_ctrl_reg(st, SCA3000_REG_CTRL_SEL_OUT_CTRL);
	अगर (ret < 0)
		वापस ret;

	अगर (*val > 0) अणु
		ret &= SCA3000_REG_OUT_CTRL_BUF_DIV_MASK;
		चयन (ret) अणु
		हाल SCA3000_REG_OUT_CTRL_BUF_DIV_2:
			*val /= 2;
			अवरोध;
		हाल SCA3000_REG_OUT_CTRL_BUF_DIV_4:
			*val /= 4;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sca3000_ग_लिखो_raw_samp_freq() - ग_लिखो_raw handler क्रम IIO_CHAN_INFO_SAMP_FREQ
 * @st: Private driver specअगरic device instance specअगरic state.
 * @val: The frequency desired.
 *
 * lock must be held
 */
अटल पूर्णांक sca3000_ग_लिखो_raw_samp_freq(काष्ठा sca3000_state *st, पूर्णांक val)
अणु
	पूर्णांक ret, base_freq, ctrlval;

	ret = __sca3000_get_base_freq(st, st->info, &base_freq);
	अगर (ret)
		वापस ret;

	ret = sca3000_पढ़ो_ctrl_reg(st, SCA3000_REG_CTRL_SEL_OUT_CTRL);
	अगर (ret < 0)
		वापस ret;

	ctrlval = ret & ~SCA3000_REG_OUT_CTRL_BUF_DIV_MASK;

	अगर (val == base_freq / 2)
		ctrlval |= SCA3000_REG_OUT_CTRL_BUF_DIV_2;
	अगर (val == base_freq / 4)
		ctrlval |= SCA3000_REG_OUT_CTRL_BUF_DIV_4;
	अन्यथा अगर (val != base_freq)
		वापस -EINVAL;

	वापस sca3000_ग_लिखो_ctrl_reg(st, SCA3000_REG_CTRL_SEL_OUT_CTRL,
				     ctrlval);
पूर्ण

अटल पूर्णांक sca3000_पढ़ो_3db_freq(काष्ठा sca3000_state *st, पूर्णांक *val)
अणु
	पूर्णांक ret;

	ret = sca3000_पढ़ो_data_लघु(st, SCA3000_REG_MODE_ADDR, 1);
	अगर (ret)
		वापस ret;

	/* mask bottom 2 bits - only ones that are relevant */
	st->rx[0] &= SCA3000_REG_MODE_MODE_MASK;
	चयन (st->rx[0]) अणु
	हाल SCA3000_REG_MODE_MEAS_MODE_NORMAL:
		*val = st->info->measurement_mode_3db_freq;
		वापस IIO_VAL_INT;
	हाल SCA3000_REG_MODE_MEAS_MODE_MOT_DET:
		वापस -EBUSY;
	हाल SCA3000_REG_MODE_MEAS_MODE_OP_1:
		*val = st->info->option_mode_1_3db_freq;
		वापस IIO_VAL_INT;
	हाल SCA3000_REG_MODE_MEAS_MODE_OP_2:
		*val = st->info->option_mode_2_3db_freq;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक sca3000_ग_लिखो_3db_freq(काष्ठा sca3000_state *st, पूर्णांक val)
अणु
	पूर्णांक ret;
	पूर्णांक mode;

	अगर (val == st->info->measurement_mode_3db_freq)
		mode = SCA3000_REG_MODE_MEAS_MODE_NORMAL;
	अन्यथा अगर (st->info->option_mode_1 &&
		 (val == st->info->option_mode_1_3db_freq))
		mode = SCA3000_REG_MODE_MEAS_MODE_OP_1;
	अन्यथा अगर (st->info->option_mode_2 &&
		 (val == st->info->option_mode_2_3db_freq))
		mode = SCA3000_REG_MODE_MEAS_MODE_OP_2;
	अन्यथा
		वापस -EINVAL;
	ret = sca3000_पढ़ो_data_लघु(st, SCA3000_REG_MODE_ADDR, 1);
	अगर (ret)
		वापस ret;

	st->rx[0] &= ~SCA3000_REG_MODE_MODE_MASK;
	st->rx[0] |= (mode & SCA3000_REG_MODE_MODE_MASK);

	वापस sca3000_ग_लिखो_reg(st, SCA3000_REG_MODE_ADDR, st->rx[0]);
पूर्ण

अटल पूर्णांक sca3000_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val,
			    पूर्णांक *val2,
			    दीर्घ mask)
अणु
	काष्ठा sca3000_state *st = iio_priv(indio_dev);
	पूर्णांक ret;
	u8 address;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&st->lock);
		अगर (chan->type == IIO_ACCEL) अणु
			अगर (st->mo_det_use_count) अणु
				mutex_unlock(&st->lock);
				वापस -EBUSY;
			पूर्ण
			address = sca3000_addresses[chan->address][0];
			ret = sca3000_पढ़ो_data_लघु(st, address, 2);
			अगर (ret < 0) अणु
				mutex_unlock(&st->lock);
				वापस ret;
			पूर्ण
			*val = (be16_to_cpup((__be16 *)st->rx) >> 3) & 0x1FFF;
			*val = ((*val) << (माप(*val) * 8 - 13)) >>
				(माप(*val) * 8 - 13);
		पूर्ण अन्यथा अणु
			/* get the temperature when available */
			ret = sca3000_पढ़ो_data_लघु(st,
						      SCA3000_REG_TEMP_MSB_ADDR,
						      2);
			अगर (ret < 0) अणु
				mutex_unlock(&st->lock);
				वापस ret;
			पूर्ण
			*val = ((st->rx[0] & 0x3F) << 3) |
			       ((st->rx[1] & 0xE0) >> 5);
		पूर्ण
		mutex_unlock(&st->lock);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		अगर (chan->type == IIO_ACCEL)
			*val2 = st->info->scale;
		अन्यथा /* temperature */
			*val2 = 555556;
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_OFFSET:
		*val = -214;
		*val2 = 600000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		mutex_lock(&st->lock);
		ret = sca3000_पढ़ो_raw_samp_freq(st, val);
		mutex_unlock(&st->lock);
		वापस ret ? ret : IIO_VAL_INT;
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		mutex_lock(&st->lock);
		ret = sca3000_पढ़ो_3db_freq(st, val);
		mutex_unlock(&st->lock);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक sca3000_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा sca3000_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		अगर (val2)
			वापस -EINVAL;
		mutex_lock(&st->lock);
		ret = sca3000_ग_लिखो_raw_samp_freq(st, val);
		mutex_unlock(&st->lock);
		वापस ret;
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		अगर (val2)
			वापस -EINVAL;
		mutex_lock(&st->lock);
		ret = sca3000_ग_लिखो_3db_freq(st, val);
		mutex_unlock(&st->lock);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * sca3000_पढ़ो_av_freq() - sysfs function to get available frequencies
 * @dev: Device काष्ठाure क्रम this device.
 * @attr: Description of the attribute.
 * @buf: Incoming string
 *
 * The later modes are only relevant to the ring buffer - and depend on current
 * mode. Note that data sheet gives rather wide tolerances क्रम these so पूर्णांकeger
 * भागision will give good enough answer and not all chips have them specअगरied
 * at all.
 **/
अटल sमाप_प्रकार sca3000_पढ़ो_av_freq(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा sca3000_state *st = iio_priv(indio_dev);
	पूर्णांक len = 0, ret, val;

	mutex_lock(&st->lock);
	ret = sca3000_पढ़ो_data_लघु(st, SCA3000_REG_MODE_ADDR, 1);
	val = st->rx[0];
	mutex_unlock(&st->lock);
	अगर (ret)
		जाओ error_ret;

	चयन (val & SCA3000_REG_MODE_MODE_MASK) अणु
	हाल SCA3000_REG_MODE_MEAS_MODE_NORMAL:
		len += प्र_लिखो(buf + len, "%d %d %d\n",
			       st->info->measurement_mode_freq,
			       st->info->measurement_mode_freq / 2,
			       st->info->measurement_mode_freq / 4);
		अवरोध;
	हाल SCA3000_REG_MODE_MEAS_MODE_OP_1:
		len += प्र_लिखो(buf + len, "%d %d %d\n",
			       st->info->option_mode_1_freq,
			       st->info->option_mode_1_freq / 2,
			       st->info->option_mode_1_freq / 4);
		अवरोध;
	हाल SCA3000_REG_MODE_MEAS_MODE_OP_2:
		len += प्र_लिखो(buf + len, "%d %d %d\n",
			       st->info->option_mode_2_freq,
			       st->info->option_mode_2_freq / 2,
			       st->info->option_mode_2_freq / 4);
		अवरोध;
	पूर्ण
	वापस len;
error_ret:
	वापस ret;
पूर्ण

/*
 * Should only really be रेजिस्टरed अगर ring buffer support is compiled in.
 * Does no harm however and करोing it right would add a fair bit of complनिकासy
 */
अटल IIO_DEV_ATTR_SAMP_FREQ_AVAIL(sca3000_पढ़ो_av_freq);

/*
 * sca3000_पढ़ो_event_value() - query of a threshold or period
 */
अटल पूर्णांक sca3000_पढ़ो_event_value(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत iio_event_type type,
				    क्रमागत iio_event_direction dir,
				    क्रमागत iio_event_info info,
				    पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा sca3000_state *st = iio_priv(indio_dev);
	दीर्घ ret;
	पूर्णांक i;

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		mutex_lock(&st->lock);
		ret = sca3000_पढ़ो_ctrl_reg(st,
					    sca3000_addresses[chan->address][1]);
		mutex_unlock(&st->lock);
		अगर (ret < 0)
			वापस ret;
		*val = 0;
		अगर (chan->channel2 == IIO_MOD_Y)
			क्रम_each_set_bit(i, &ret,
					 ARRAY_SIZE(st->info->mot_det_mult_y))
				*val += st->info->mot_det_mult_y[i];
		अन्यथा
			क्रम_each_set_bit(i, &ret,
					 ARRAY_SIZE(st->info->mot_det_mult_xz))
				*val += st->info->mot_det_mult_xz[i];

		वापस IIO_VAL_INT;
	हाल IIO_EV_INFO_PERIOD:
		*val = 0;
		*val2 = 226000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * sca3000_ग_लिखो_event_value() - control of threshold and period
 * @indio_dev: Device instance specअगरic IIO inक्रमmation.
 * @chan: Description of the channel क्रम which the event is being
 * configured.
 * @type: The type of event being configured, here magnitude rising
 * as everything अन्यथा is पढ़ो only.
 * @dir: Direction of the event (here rising)
 * @info: What inक्रमmation about the event are we configuring.
 * Here the threshold only.
 * @val: Integer part of the value being written..
 * @val2: Non पूर्णांकeger part of the value being written. Here always 0.
 */
अटल पूर्णांक sca3000_ग_लिखो_event_value(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     क्रमागत iio_event_type type,
				     क्रमागत iio_event_direction dir,
				     क्रमागत iio_event_info info,
				     पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा sca3000_state *st = iio_priv(indio_dev);
	पूर्णांक ret;
	पूर्णांक i;
	u8 nonlinear = 0;

	अगर (chan->channel2 == IIO_MOD_Y) अणु
		i = ARRAY_SIZE(st->info->mot_det_mult_y);
		जबतक (i > 0)
			अगर (val >= st->info->mot_det_mult_y[--i]) अणु
				nonlinear |= (1 << i);
				val -= st->info->mot_det_mult_y[i];
			पूर्ण
	पूर्ण अन्यथा अणु
		i = ARRAY_SIZE(st->info->mot_det_mult_xz);
		जबतक (i > 0)
			अगर (val >= st->info->mot_det_mult_xz[--i]) अणु
				nonlinear |= (1 << i);
				val -= st->info->mot_det_mult_xz[i];
			पूर्ण
	पूर्ण

	mutex_lock(&st->lock);
	ret = sca3000_ग_लिखो_ctrl_reg(st,
				     sca3000_addresses[chan->address][1],
				     nonlinear);
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल काष्ठा attribute *sca3000_attributes[] = अणु
	&iio_dev_attr_in_accel_filter_low_pass_3db_frequency_available.dev_attr.attr,
	&iio_dev_attr_sampling_frequency_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group sca3000_attribute_group = अणु
	.attrs = sca3000_attributes,
पूर्ण;

अटल पूर्णांक sca3000_पढ़ो_data(काष्ठा sca3000_state *st,
			     u8 reg_address_high,
			     u8 *rx,
			     पूर्णांक len)
अणु
	पूर्णांक ret;
	काष्ठा spi_transfer xfer[2] = अणु
		अणु
			.len = 1,
			.tx_buf = st->tx,
		पूर्ण, अणु
			.len = len,
			.rx_buf = rx,
		पूर्ण
	पूर्ण;

	st->tx[0] = SCA3000_READ_REG(reg_address_high);
	ret = spi_sync_transfer(st->us, xfer, ARRAY_SIZE(xfer));
	अगर (ret) अणु
		dev_err(&st->us->dev, "problem reading register\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sca3000_ring_पूर्णांक_process() - ring specअगरic पूर्णांकerrupt handling.
 * @val: Value of the पूर्णांकerrupt status रेजिस्टर.
 * @indio_dev: Device instance specअगरic IIO device काष्ठाure.
 */
अटल व्योम sca3000_ring_पूर्णांक_process(u8 val, काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा sca3000_state *st = iio_priv(indio_dev);
	पूर्णांक ret, i, num_available;

	mutex_lock(&st->lock);

	अगर (val & SCA3000_REG_INT_STATUS_HALF) अणु
		ret = sca3000_पढ़ो_data_लघु(st, SCA3000_REG_BUF_COUNT_ADDR,
					      1);
		अगर (ret)
			जाओ error_ret;
		num_available = st->rx[0];
		/*
		 * num_available is the total number of samples available
		 * i.e. number of समय poपूर्णांकs * number of channels.
		 */
		ret = sca3000_पढ़ो_data(st, SCA3000_REG_RING_OUT_ADDR, st->rx,
					num_available * 2);
		अगर (ret)
			जाओ error_ret;
		क्रम (i = 0; i < num_available / 3; i++) अणु
			/*
			 * Dirty hack to cover क्रम 11 bit in fअगरo, 13 bit
			 * direct पढ़ोing.
			 *
			 * In theory the bottom two bits are undefined.
			 * In reality they appear to always be 0.
			 */
			iio_push_to_buffers(indio_dev, st->rx + i * 3 * 2);
		पूर्ण
	पूर्ण
error_ret:
	mutex_unlock(&st->lock);
पूर्ण

/**
 * sca3000_event_handler() - handling ring and non ring events
 * @irq: The irq being handled.
 * @निजी: काष्ठा iio_device poपूर्णांकer क्रम the device.
 *
 * Ring related पूर्णांकerrupt handler. Depending on event, push to
 * the ring buffer event chrdev or the event one.
 *
 * This function is complicated by the fact that the devices can signअगरy ring
 * and non ring events via the same पूर्णांकerrupt line and they can only
 * be distinguished via a पढ़ो of the relevant status रेजिस्टर.
 */
अटल irqवापस_t sca3000_event_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा sca3000_state *st = iio_priv(indio_dev);
	पूर्णांक ret, val;
	s64 last_बारtamp = iio_get_समय_ns(indio_dev);

	/*
	 * Could lead अगर badly समयd to an extra पढ़ो of status reg,
	 * but ensures no पूर्णांकerrupt is missed.
	 */
	mutex_lock(&st->lock);
	ret = sca3000_पढ़ो_data_लघु(st, SCA3000_REG_INT_STATUS_ADDR, 1);
	val = st->rx[0];
	mutex_unlock(&st->lock);
	अगर (ret)
		जाओ करोne;

	sca3000_ring_पूर्णांक_process(val, indio_dev);

	अगर (val & SCA3000_INT_STATUS_FREE_FALL)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEL,
						  0,
						  IIO_MOD_X_AND_Y_AND_Z,
						  IIO_EV_TYPE_MAG,
						  IIO_EV_सूची_FALLING),
			       last_बारtamp);

	अगर (val & SCA3000_INT_STATUS_Y_TRIGGER)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEL,
						  0,
						  IIO_MOD_Y,
						  IIO_EV_TYPE_MAG,
						  IIO_EV_सूची_RISING),
			       last_बारtamp);

	अगर (val & SCA3000_INT_STATUS_X_TRIGGER)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEL,
						  0,
						  IIO_MOD_X,
						  IIO_EV_TYPE_MAG,
						  IIO_EV_सूची_RISING),
			       last_बारtamp);

	अगर (val & SCA3000_INT_STATUS_Z_TRIGGER)
		iio_push_event(indio_dev,
			       IIO_MOD_EVENT_CODE(IIO_ACCEL,
						  0,
						  IIO_MOD_Z,
						  IIO_EV_TYPE_MAG,
						  IIO_EV_सूची_RISING),
			       last_बारtamp);

करोne:
	वापस IRQ_HANDLED;
पूर्ण

/*
 * sca3000_पढ़ो_event_config() what events are enabled
 */
अटल पूर्णांक sca3000_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     क्रमागत iio_event_type type,
				     क्रमागत iio_event_direction dir)
अणु
	काष्ठा sca3000_state *st = iio_priv(indio_dev);
	पूर्णांक ret;
	/* पढ़ो current value of mode रेजिस्टर */
	mutex_lock(&st->lock);

	ret = sca3000_पढ़ो_data_लघु(st, SCA3000_REG_MODE_ADDR, 1);
	अगर (ret)
		जाओ error_ret;

	चयन (chan->channel2) अणु
	हाल IIO_MOD_X_AND_Y_AND_Z:
		ret = !!(st->rx[0] & SCA3000_REG_MODE_FREE_FALL_DETECT);
		अवरोध;
	हाल IIO_MOD_X:
	हाल IIO_MOD_Y:
	हाल IIO_MOD_Z:
		/*
		 * Motion detection mode cannot run at the same समय as
		 * acceleration data being पढ़ो.
		 */
		अगर ((st->rx[0] & SCA3000_REG_MODE_MODE_MASK)
		    != SCA3000_REG_MODE_MEAS_MODE_MOT_DET) अणु
			ret = 0;
		पूर्ण अन्यथा अणु
			ret = sca3000_पढ़ो_ctrl_reg(st,
						SCA3000_REG_CTRL_SEL_MD_CTRL);
			अगर (ret < 0)
				जाओ error_ret;
			/* only supporting logical or's क्रम now */
			ret = !!(ret & sca3000_addresses[chan->address][2]);
		पूर्ण
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

error_ret:
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक sca3000_मुक्तfall_set_state(काष्ठा iio_dev *indio_dev, पूर्णांक state)
अणु
	काष्ठा sca3000_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	/* पढ़ो current value of mode रेजिस्टर */
	ret = sca3000_पढ़ो_data_लघु(st, SCA3000_REG_MODE_ADDR, 1);
	अगर (ret)
		वापस ret;

	/* अगर off and should be on */
	अगर (state && !(st->rx[0] & SCA3000_REG_MODE_FREE_FALL_DETECT))
		वापस sca3000_ग_लिखो_reg(st, SCA3000_REG_MODE_ADDR,
					 st->rx[0] | SCA3000_REG_MODE_FREE_FALL_DETECT);
	/* अगर on and should be off */
	अन्यथा अगर (!state && (st->rx[0] & SCA3000_REG_MODE_FREE_FALL_DETECT))
		वापस sca3000_ग_लिखो_reg(st, SCA3000_REG_MODE_ADDR,
					 st->rx[0] & ~SCA3000_REG_MODE_FREE_FALL_DETECT);
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक sca3000_motion_detect_set_state(काष्ठा iio_dev *indio_dev, पूर्णांक axis,
					   पूर्णांक state)
अणु
	काष्ठा sca3000_state *st = iio_priv(indio_dev);
	पूर्णांक ret, ctrlval;

	/*
	 * First पढ़ो the motion detector config to find out अगर
	 * this axis is on
	 */
	ret = sca3000_पढ़ो_ctrl_reg(st, SCA3000_REG_CTRL_SEL_MD_CTRL);
	अगर (ret < 0)
		वापस ret;
	ctrlval = ret;
	/* अगर off and should be on */
	अगर (state && !(ctrlval & sca3000_addresses[axis][2])) अणु
		ret = sca3000_ग_लिखो_ctrl_reg(st,
					     SCA3000_REG_CTRL_SEL_MD_CTRL,
					     ctrlval |
					     sca3000_addresses[axis][2]);
		अगर (ret)
			वापस ret;
		st->mo_det_use_count++;
	पूर्ण अन्यथा अगर (!state && (ctrlval & sca3000_addresses[axis][2])) अणु
		ret = sca3000_ग_लिखो_ctrl_reg(st,
					     SCA3000_REG_CTRL_SEL_MD_CTRL,
					     ctrlval &
					     ~(sca3000_addresses[axis][2]));
		अगर (ret)
			वापस ret;
		st->mo_det_use_count--;
	पूर्ण

	/* पढ़ो current value of mode रेजिस्टर */
	ret = sca3000_पढ़ो_data_लघु(st, SCA3000_REG_MODE_ADDR, 1);
	अगर (ret)
		वापस ret;
	/* अगर off and should be on */
	अगर ((st->mo_det_use_count) &&
	    ((st->rx[0] & SCA3000_REG_MODE_MODE_MASK)
	     != SCA3000_REG_MODE_MEAS_MODE_MOT_DET))
		वापस sca3000_ग_लिखो_reg(st, SCA3000_REG_MODE_ADDR,
			(st->rx[0] & ~SCA3000_REG_MODE_MODE_MASK)
			| SCA3000_REG_MODE_MEAS_MODE_MOT_DET);
	/* अगर on and should be off */
	अन्यथा अगर (!(st->mo_det_use_count) &&
		 ((st->rx[0] & SCA3000_REG_MODE_MODE_MASK)
		  == SCA3000_REG_MODE_MEAS_MODE_MOT_DET))
		वापस sca3000_ग_लिखो_reg(st, SCA3000_REG_MODE_ADDR,
			st->rx[0] & SCA3000_REG_MODE_MODE_MASK);
	अन्यथा
		वापस 0;
पूर्ण

/**
 * sca3000_ग_लिखो_event_config() - simple on off control क्रम motion detector
 * @indio_dev: IIO device instance specअगरic काष्ठाure. Data specअगरic to this
 * particular driver may be accessed via iio_priv(indio_dev).
 * @chan: Description of the channel whose event we are configuring.
 * @type: The type of event.
 * @dir: The direction of the event.
 * @state: Desired state of event being configured.
 *
 * This is a per axis control, but enabling any will result in the
 * motion detector unit being enabled.
 * N.B. enabling motion detector stops normal data acquisition.
 * There is a complनिकासy in knowing which mode to वापस to when
 * this mode is disabled.  Currently normal mode is assumed.
 **/
अटल पूर्णांक sca3000_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
				      स्थिर काष्ठा iio_chan_spec *chan,
				      क्रमागत iio_event_type type,
				      क्रमागत iio_event_direction dir,
				      पूर्णांक state)
अणु
	काष्ठा sca3000_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);
	चयन (chan->channel2) अणु
	हाल IIO_MOD_X_AND_Y_AND_Z:
		ret = sca3000_मुक्तfall_set_state(indio_dev, state);
		अवरोध;

	हाल IIO_MOD_X:
	हाल IIO_MOD_Y:
	हाल IIO_MOD_Z:
		ret = sca3000_motion_detect_set_state(indio_dev,
						      chan->address,
						      state);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल अंतरभूत
पूर्णांक __sca3000_hw_ring_state_set(काष्ठा iio_dev *indio_dev, bool state)
अणु
	काष्ठा sca3000_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);
	ret = sca3000_पढ़ो_data_लघु(st, SCA3000_REG_MODE_ADDR, 1);
	अगर (ret)
		जाओ error_ret;
	अगर (state) अणु
		dev_info(&indio_dev->dev, "supposedly enabling ring buffer\n");
		ret = sca3000_ग_लिखो_reg(st,
			SCA3000_REG_MODE_ADDR,
			(st->rx[0] | SCA3000_REG_MODE_RING_BUF_ENABLE));
	पूर्ण अन्यथा
		ret = sca3000_ग_लिखो_reg(st,
			SCA3000_REG_MODE_ADDR,
			(st->rx[0] & ~SCA3000_REG_MODE_RING_BUF_ENABLE));
error_ret:
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

/**
 * sca3000_hw_ring_preenable() - hw ring buffer preenable function
 * @indio_dev: काष्ठाure representing the IIO device. Device instance
 * specअगरic state can be accessed via iio_priv(indio_dev).
 *
 * Very simple enable function as the chip will allows normal पढ़ोs
 * during ring buffer operation so as दीर्घ as it is indeed running
 * beक्रमe we notअगरy the core, the precise ordering करोes not matter.
 */
अटल पूर्णांक sca3000_hw_ring_preenable(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret;
	काष्ठा sca3000_state *st = iio_priv(indio_dev);

	mutex_lock(&st->lock);

	/* Enable the 50% full पूर्णांकerrupt */
	ret = sca3000_पढ़ो_data_लघु(st, SCA3000_REG_INT_MASK_ADDR, 1);
	अगर (ret)
		जाओ error_unlock;
	ret = sca3000_ग_लिखो_reg(st,
				SCA3000_REG_INT_MASK_ADDR,
				st->rx[0] | SCA3000_REG_INT_MASK_RING_HALF);
	अगर (ret)
		जाओ error_unlock;

	mutex_unlock(&st->lock);

	वापस __sca3000_hw_ring_state_set(indio_dev, 1);

error_unlock:
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक sca3000_hw_ring_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret;
	काष्ठा sca3000_state *st = iio_priv(indio_dev);

	ret = __sca3000_hw_ring_state_set(indio_dev, 0);
	अगर (ret)
		वापस ret;

	/* Disable the 50% full पूर्णांकerrupt */
	mutex_lock(&st->lock);

	ret = sca3000_पढ़ो_data_लघु(st, SCA3000_REG_INT_MASK_ADDR, 1);
	अगर (ret)
		जाओ unlock;
	ret = sca3000_ग_लिखो_reg(st,
				SCA3000_REG_INT_MASK_ADDR,
				st->rx[0] & ~SCA3000_REG_INT_MASK_RING_HALF);
unlock:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops sca3000_ring_setup_ops = अणु
	.preenable = &sca3000_hw_ring_preenable,
	.postdisable = &sca3000_hw_ring_postdisable,
पूर्ण;

/**
 * sca3000_clean_setup() - get the device पूर्णांकo a predictable state
 * @st: Device instance specअगरic निजी data काष्ठाure
 *
 * Devices use flash memory to store many of the रेजिस्टर values
 * and hence can come up in somewhat unpredictable states.
 * Hence reset everything on driver load.
 */
अटल पूर्णांक sca3000_clean_setup(काष्ठा sca3000_state *st)
अणु
	पूर्णांक ret;

	mutex_lock(&st->lock);
	/* Ensure all पूर्णांकerrupts have been acknowledged */
	ret = sca3000_पढ़ो_data_लघु(st, SCA3000_REG_INT_STATUS_ADDR, 1);
	अगर (ret)
		जाओ error_ret;

	/* Turn off all motion detection channels */
	ret = sca3000_पढ़ो_ctrl_reg(st, SCA3000_REG_CTRL_SEL_MD_CTRL);
	अगर (ret < 0)
		जाओ error_ret;
	ret = sca3000_ग_लिखो_ctrl_reg(st, SCA3000_REG_CTRL_SEL_MD_CTRL,
				     ret & SCA3000_MD_CTRL_PROT_MASK);
	अगर (ret)
		जाओ error_ret;

	/* Disable ring buffer */
	ret = sca3000_पढ़ो_ctrl_reg(st, SCA3000_REG_CTRL_SEL_OUT_CTRL);
	अगर (ret < 0)
		जाओ error_ret;
	ret = sca3000_ग_लिखो_ctrl_reg(st, SCA3000_REG_CTRL_SEL_OUT_CTRL,
				     (ret & SCA3000_REG_OUT_CTRL_PROT_MASK)
				     | SCA3000_REG_OUT_CTRL_BUF_X_EN
				     | SCA3000_REG_OUT_CTRL_BUF_Y_EN
				     | SCA3000_REG_OUT_CTRL_BUF_Z_EN
				     | SCA3000_REG_OUT_CTRL_BUF_DIV_4);
	अगर (ret)
		जाओ error_ret;
	/* Enable पूर्णांकerrupts, relevant to mode and set up as active low */
	ret = sca3000_पढ़ो_data_लघु(st, SCA3000_REG_INT_MASK_ADDR, 1);
	अगर (ret)
		जाओ error_ret;
	ret = sca3000_ग_लिखो_reg(st,
				SCA3000_REG_INT_MASK_ADDR,
				(ret & SCA3000_REG_INT_MASK_PROT_MASK)
				| SCA3000_REG_INT_MASK_ACTIVE_LOW);
	अगर (ret)
		जाओ error_ret;
	/*
	 * Select normal measurement mode, मुक्त fall off, ring off
	 * Ring in 12 bit mode - it is fine to overग_लिखो reserved bits 3,5
	 * as that occurs in one of the example on the datasheet
	 */
	ret = sca3000_पढ़ो_data_लघु(st, SCA3000_REG_MODE_ADDR, 1);
	अगर (ret)
		जाओ error_ret;
	ret = sca3000_ग_लिखो_reg(st, SCA3000_REG_MODE_ADDR,
				(st->rx[0] & SCA3000_MODE_PROT_MASK));

error_ret:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info sca3000_info = अणु
	.attrs = &sca3000_attribute_group,
	.पढ़ो_raw = &sca3000_पढ़ो_raw,
	.ग_लिखो_raw = &sca3000_ग_लिखो_raw,
	.पढ़ो_event_value = &sca3000_पढ़ो_event_value,
	.ग_लिखो_event_value = &sca3000_ग_लिखो_event_value,
	.पढ़ो_event_config = &sca3000_पढ़ो_event_config,
	.ग_लिखो_event_config = &sca3000_ग_लिखो_event_config,
पूर्ण;

अटल पूर्णांक sca3000_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
	काष्ठा sca3000_state *st;
	काष्ठा iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);
	st->us = spi;
	mutex_init(&st->lock);
	st->info = &sca3000_spi_chip_info_tbl[spi_get_device_id(spi)
					      ->driver_data];

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &sca3000_info;
	अगर (st->info->temp_output) अणु
		indio_dev->channels = sca3000_channels_with_temp;
		indio_dev->num_channels =
			ARRAY_SIZE(sca3000_channels_with_temp);
	पूर्ण अन्यथा अणु
		indio_dev->channels = sca3000_channels;
		indio_dev->num_channels = ARRAY_SIZE(sca3000_channels);
	पूर्ण
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = devm_iio_kfअगरo_buffer_setup(&spi->dev, indio_dev,
					  INDIO_BUFFER_SOFTWARE,
					  &sca3000_ring_setup_ops);
	अगर (ret)
		वापस ret;

	अगर (spi->irq) अणु
		ret = request_thपढ़ोed_irq(spi->irq,
					   शून्य,
					   &sca3000_event_handler,
					   IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					   "sca3000",
					   indio_dev);
		अगर (ret)
			वापस ret;
	पूर्ण
	ret = sca3000_clean_setup(st);
	अगर (ret)
		जाओ error_मुक्त_irq;

	ret = sca3000_prपूर्णांक_rev(indio_dev);
	अगर (ret)
		जाओ error_मुक्त_irq;

	वापस iio_device_रेजिस्टर(indio_dev);

error_मुक्त_irq:
	अगर (spi->irq)
		मुक्त_irq(spi->irq, indio_dev);

	वापस ret;
पूर्ण

अटल पूर्णांक sca3000_stop_all_पूर्णांकerrupts(काष्ठा sca3000_state *st)
अणु
	पूर्णांक ret;

	mutex_lock(&st->lock);
	ret = sca3000_पढ़ो_data_लघु(st, SCA3000_REG_INT_MASK_ADDR, 1);
	अगर (ret)
		जाओ error_ret;
	ret = sca3000_ग_लिखो_reg(st, SCA3000_REG_INT_MASK_ADDR,
				(st->rx[0] &
				 ~(SCA3000_REG_INT_MASK_RING_THREE_QUARTER |
				   SCA3000_REG_INT_MASK_RING_HALF |
				   SCA3000_REG_INT_MASK_ALL_INTS)));
error_ret:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक sca3000_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा sca3000_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	/* Must ensure no पूर्णांकerrupts can be generated after this! */
	sca3000_stop_all_पूर्णांकerrupts(st);
	अगर (spi->irq)
		मुक्त_irq(spi->irq, indio_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id sca3000_id[] = अणु
	अणु"sca3000_d01", d01पूर्ण,
	अणु"sca3000_e02", e02पूर्ण,
	अणु"sca3000_e04", e04पूर्ण,
	अणु"sca3000_e05", e05पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, sca3000_id);

अटल काष्ठा spi_driver sca3000_driver = अणु
	.driver = अणु
		.name = "sca3000",
	पूर्ण,
	.probe = sca3000_probe,
	.हटाओ = sca3000_हटाओ,
	.id_table = sca3000_id,
पूर्ण;
module_spi_driver(sca3000_driver);

MODULE_AUTHOR("Jonathan Cameron <jic23@kernel.org>");
MODULE_DESCRIPTION("VTI SCA3000 Series Accelerometers SPI driver");
MODULE_LICENSE("GPL v2");
