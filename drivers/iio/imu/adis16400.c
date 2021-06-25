<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * adis16400.c	support Analog Devices ADIS16400/5
 *		3d 2g Linear Accelerometers,
 *		3d Gyroscopes,
 *		3d Magnetometers via SPI
 *
 * Copyright (c) 2009 Manuel Stahl <manuel.stahl@iis.fraunhofer.de>
 * Copyright (c) 2007 Jonathan Cameron <jic23@kernel.org>
 * Copyright (c) 2011 Analog Devices Inc.
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
#समावेश <linux/debugfs.h>
#समावेश <linux/bitops.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/imu/adis.h>

#घोषणा ADIS16400_STARTUP_DELAY	290 /* ms */
#घोषणा ADIS16400_MTEST_DELAY 90 /* ms */

#घोषणा ADIS16400_FLASH_CNT  0x00 /* Flash memory ग_लिखो count */
#घोषणा ADIS16400_SUPPLY_OUT 0x02 /* Power supply measurement */
#घोषणा ADIS16400_XGYRO_OUT 0x04 /* X-axis gyroscope output */
#घोषणा ADIS16400_YGYRO_OUT 0x06 /* Y-axis gyroscope output */
#घोषणा ADIS16400_ZGYRO_OUT 0x08 /* Z-axis gyroscope output */
#घोषणा ADIS16400_XACCL_OUT 0x0A /* X-axis accelerometer output */
#घोषणा ADIS16400_YACCL_OUT 0x0C /* Y-axis accelerometer output */
#घोषणा ADIS16400_ZACCL_OUT 0x0E /* Z-axis accelerometer output */
#घोषणा ADIS16400_XMAGN_OUT 0x10 /* X-axis magnetometer measurement */
#घोषणा ADIS16400_YMAGN_OUT 0x12 /* Y-axis magnetometer measurement */
#घोषणा ADIS16400_ZMAGN_OUT 0x14 /* Z-axis magnetometer measurement */
#घोषणा ADIS16400_TEMP_OUT  0x16 /* Temperature output */
#घोषणा ADIS16400_AUX_ADC   0x18 /* Auxiliary ADC measurement */

#घोषणा ADIS16350_XTEMP_OUT 0x10 /* X-axis gyroscope temperature measurement */
#घोषणा ADIS16350_YTEMP_OUT 0x12 /* Y-axis gyroscope temperature measurement */
#घोषणा ADIS16350_ZTEMP_OUT 0x14 /* Z-axis gyroscope temperature measurement */

#घोषणा ADIS16300_PITCH_OUT 0x12 /* X axis inclinometer output measurement */
#घोषणा ADIS16300_ROLL_OUT  0x14 /* Y axis inclinometer output measurement */
#घोषणा ADIS16300_AUX_ADC   0x16 /* Auxiliary ADC measurement */

#घोषणा ADIS16448_BARO_OUT	0x16 /* Barometric pressure output */
#घोषणा ADIS16448_TEMP_OUT  0x18 /* Temperature output */

/* Calibration parameters */
#घोषणा ADIS16400_XGYRO_OFF 0x1A /* X-axis gyroscope bias offset factor */
#घोषणा ADIS16400_YGYRO_OFF 0x1C /* Y-axis gyroscope bias offset factor */
#घोषणा ADIS16400_ZGYRO_OFF 0x1E /* Z-axis gyroscope bias offset factor */
#घोषणा ADIS16400_XACCL_OFF 0x20 /* X-axis acceleration bias offset factor */
#घोषणा ADIS16400_YACCL_OFF 0x22 /* Y-axis acceleration bias offset factor */
#घोषणा ADIS16400_ZACCL_OFF 0x24 /* Z-axis acceleration bias offset factor */
#घोषणा ADIS16400_XMAGN_HIF 0x26 /* X-axis magnetometer, hard-iron factor */
#घोषणा ADIS16400_YMAGN_HIF 0x28 /* Y-axis magnetometer, hard-iron factor */
#घोषणा ADIS16400_ZMAGN_HIF 0x2A /* Z-axis magnetometer, hard-iron factor */
#घोषणा ADIS16400_XMAGN_SIF 0x2C /* X-axis magnetometer, soft-iron factor */
#घोषणा ADIS16400_YMAGN_SIF 0x2E /* Y-axis magnetometer, soft-iron factor */
#घोषणा ADIS16400_ZMAGN_SIF 0x30 /* Z-axis magnetometer, soft-iron factor */

#घोषणा ADIS16400_GPIO_CTRL 0x32 /* Auxiliary digital input/output control */
#घोषणा ADIS16400_MSC_CTRL  0x34 /* Miscellaneous control */
#घोषणा ADIS16400_SMPL_PRD  0x36 /* Internal sample period (rate) control */
#घोषणा ADIS16400_SENS_AVG  0x38 /* Dynamic range and digital filter control */
#घोषणा ADIS16400_SLP_CNT   0x3A /* Sleep mode control */
#घोषणा ADIS16400_DIAG_STAT 0x3C /* System status */

/* Alarm functions */
#घोषणा ADIS16400_GLOB_CMD  0x3E /* System command */
#घोषणा ADIS16400_ALM_MAG1  0x40 /* Alarm 1 amplitude threshold */
#घोषणा ADIS16400_ALM_MAG2  0x42 /* Alarm 2 amplitude threshold */
#घोषणा ADIS16400_ALM_SMPL1 0x44 /* Alarm 1 sample size */
#घोषणा ADIS16400_ALM_SMPL2 0x46 /* Alarm 2 sample size */
#घोषणा ADIS16400_ALM_CTRL  0x48 /* Alarm control */
#घोषणा ADIS16400_AUX_DAC   0x4A /* Auxiliary DAC data */

#घोषणा ADIS16334_LOT_ID1   0x52 /* Lot identअगरication code 1 */
#घोषणा ADIS16334_LOT_ID2   0x54 /* Lot identअगरication code 2 */
#घोषणा ADIS16400_PRODUCT_ID 0x56 /* Product identअगरier */
#घोषणा ADIS16334_SERIAL_NUMBER 0x58 /* Serial number, lot specअगरic */

#घोषणा ADIS16400_ERROR_ACTIVE			(1<<14)
#घोषणा ADIS16400_NEW_DATA			(1<<14)

/* MSC_CTRL */
#घोषणा ADIS16400_MSC_CTRL_MEM_TEST		(1<<11)
#घोषणा ADIS16400_MSC_CTRL_INT_SELF_TEST	(1<<10)
#घोषणा ADIS16400_MSC_CTRL_NEG_SELF_TEST	(1<<9)
#घोषणा ADIS16400_MSC_CTRL_POS_SELF_TEST	(1<<8)
#घोषणा ADIS16400_MSC_CTRL_GYRO_BIAS		(1<<7)
#घोषणा ADIS16400_MSC_CTRL_ACCL_ALIGN		(1<<6)
#घोषणा ADIS16400_MSC_CTRL_DATA_RDY_EN		(1<<2)
#घोषणा ADIS16400_MSC_CTRL_DATA_RDY_POL_HIGH	(1<<1)
#घोषणा ADIS16400_MSC_CTRL_DATA_RDY_DIO2	(1<<0)

/* SMPL_PRD */
#घोषणा ADIS16400_SMPL_PRD_TIME_BASE	(1<<7)
#घोषणा ADIS16400_SMPL_PRD_DIV_MASK	0x7F

/* DIAG_STAT */
#घोषणा ADIS16400_DIAG_STAT_ZACCL_FAIL	15
#घोषणा ADIS16400_DIAG_STAT_YACCL_FAIL	14
#घोषणा ADIS16400_DIAG_STAT_XACCL_FAIL	13
#घोषणा ADIS16400_DIAG_STAT_XGYRO_FAIL	12
#घोषणा ADIS16400_DIAG_STAT_YGYRO_FAIL	11
#घोषणा ADIS16400_DIAG_STAT_ZGYRO_FAIL	10
#घोषणा ADIS16400_DIAG_STAT_ALARM2	9
#घोषणा ADIS16400_DIAG_STAT_ALARM1	8
#घोषणा ADIS16400_DIAG_STAT_FLASH_CHK	6
#घोषणा ADIS16400_DIAG_STAT_SELF_TEST	5
#घोषणा ADIS16400_DIAG_STAT_OVERFLOW	4
#घोषणा ADIS16400_DIAG_STAT_SPI_FAIL	3
#घोषणा ADIS16400_DIAG_STAT_FLASH_UPT	2
#घोषणा ADIS16400_DIAG_STAT_POWER_HIGH	1
#घोषणा ADIS16400_DIAG_STAT_POWER_LOW	0

/* GLOB_CMD */
#घोषणा ADIS16400_GLOB_CMD_SW_RESET	(1<<7)
#घोषणा ADIS16400_GLOB_CMD_P_AUTO_शून्य	(1<<4)
#घोषणा ADIS16400_GLOB_CMD_FLASH_UPD	(1<<3)
#घोषणा ADIS16400_GLOB_CMD_DAC_LATCH	(1<<2)
#घोषणा ADIS16400_GLOB_CMD_FAC_CALIB	(1<<1)
#घोषणा ADIS16400_GLOB_CMD_AUTO_शून्य	(1<<0)

/* SLP_CNT */
#घोषणा ADIS16400_SLP_CNT_POWER_OFF	(1<<8)

#घोषणा ADIS16334_RATE_DIV_SHIFT 8
#घोषणा ADIS16334_RATE_INT_CLK BIT(0)

#घोषणा ADIS16400_SPI_SLOW	(u32)(300 * 1000)
#घोषणा ADIS16400_SPI_BURST	(u32)(1000 * 1000)
#घोषणा ADIS16400_SPI_FAST	(u32)(2000 * 1000)

#घोषणा ADIS16400_HAS_PROD_ID		BIT(0)
#घोषणा ADIS16400_NO_BURST		BIT(1)
#घोषणा ADIS16400_HAS_SLOW_MODE		BIT(2)
#घोषणा ADIS16400_HAS_SERIAL_NUMBER	BIT(3)
#घोषणा ADIS16400_BURST_DIAG_STAT	BIT(4)

काष्ठा adis16400_state;

काष्ठा adis16400_chip_info अणु
	स्थिर काष्ठा iio_chan_spec *channels;
	स्थिर काष्ठा adis_data adis_data;
	स्थिर पूर्णांक num_channels;
	स्थिर दीर्घ flags;
	अचिन्हित पूर्णांक gyro_scale_micro;
	अचिन्हित पूर्णांक accel_scale_micro;
	पूर्णांक temp_scale_nano;
	पूर्णांक temp_offset;
	/* set_freq() & get_freq() need to aव्योम using ADIS lib's state lock */
	पूर्णांक (*set_freq)(काष्ठा adis16400_state *st, अचिन्हित पूर्णांक freq);
	पूर्णांक (*get_freq)(काष्ठा adis16400_state *st);
पूर्ण;

/**
 * काष्ठा adis16400_state - device instance specअगरic data
 * @variant:	chip variant info
 * @filt_पूर्णांक:	पूर्णांकeger part of requested filter frequency
 * @adis:	adis device
 * @avail_scan_mask:	शून्य terminated array of biपंचांगaps of channels
 *			that must be enabled together
 **/
काष्ठा adis16400_state अणु
	काष्ठा adis16400_chip_info	*variant;
	पूर्णांक				filt_पूर्णांक;

	काष्ठा adis adis;
	अचिन्हित दीर्घ avail_scan_mask[2];
पूर्ण;

/* At the moment triggers are only used क्रम ring buffer
 * filling. This may change!
 */

क्रमागत अणु
	ADIS16400_SCAN_SUPPLY,
	ADIS16400_SCAN_GYRO_X,
	ADIS16400_SCAN_GYRO_Y,
	ADIS16400_SCAN_GYRO_Z,
	ADIS16400_SCAN_ACC_X,
	ADIS16400_SCAN_ACC_Y,
	ADIS16400_SCAN_ACC_Z,
	ADIS16400_SCAN_MAGN_X,
	ADIS16400_SCAN_MAGN_Y,
	ADIS16400_SCAN_MAGN_Z,
	ADIS16400_SCAN_BARO,
	ADIS16350_SCAN_TEMP_X,
	ADIS16350_SCAN_TEMP_Y,
	ADIS16350_SCAN_TEMP_Z,
	ADIS16300_SCAN_INCLI_X,
	ADIS16300_SCAN_INCLI_Y,
	ADIS16400_SCAN_ADC,
	ADIS16400_SCAN_TIMESTAMP,
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS

अटल sमाप_प्रकार adis16400_show_serial_number(काष्ठा file *file,
		अक्षर __user *userbuf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा adis16400_state *st = file->निजी_data;
	u16 lot1, lot2, serial_number;
	अक्षर buf[16];
	माप_प्रकार len;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg_16(&st->adis, ADIS16334_LOT_ID1, &lot1);
	अगर (ret)
		वापस ret;

	ret = adis_पढ़ो_reg_16(&st->adis, ADIS16334_LOT_ID2, &lot2);
	अगर (ret)
		वापस ret;

	ret = adis_पढ़ो_reg_16(&st->adis, ADIS16334_SERIAL_NUMBER,
			&serial_number);
	अगर (ret)
		वापस ret;

	len = snम_लिखो(buf, माप(buf), "%.4x-%.4x-%.4x\n", lot1, lot2,
			serial_number);

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations adis16400_serial_number_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = adis16400_show_serial_number,
	.llseek = शेष_llseek,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक adis16400_show_product_id(व्योम *arg, u64 *val)
अणु
	काष्ठा adis16400_state *st = arg;
	uपूर्णांक16_t prod_id;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg_16(&st->adis, ADIS16400_PRODUCT_ID, &prod_id);
	अगर (ret)
		वापस ret;

	*val = prod_id;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(adis16400_product_id_fops,
	adis16400_show_product_id, शून्य, "%lld\n");

अटल पूर्णांक adis16400_show_flash_count(व्योम *arg, u64 *val)
अणु
	काष्ठा adis16400_state *st = arg;
	uपूर्णांक16_t flash_count;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg_16(&st->adis, ADIS16400_FLASH_CNT, &flash_count);
	अगर (ret)
		वापस ret;

	*val = flash_count;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(adis16400_flash_count_fops,
	adis16400_show_flash_count, शून्य, "%lld\n");

अटल पूर्णांक adis16400_debugfs_init(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा adis16400_state *st = iio_priv(indio_dev);
	काष्ठा dentry *d = iio_get_debugfs_dentry(indio_dev);

	अगर (st->variant->flags & ADIS16400_HAS_SERIAL_NUMBER)
		debugfs_create_file_unsafe("serial_number", 0400,
				d, st, &adis16400_serial_number_fops);
	अगर (st->variant->flags & ADIS16400_HAS_PROD_ID)
		debugfs_create_file_unsafe("product_id", 0400,
				d, st, &adis16400_product_id_fops);
	debugfs_create_file_unsafe("flash_count", 0400,
			d, st, &adis16400_flash_count_fops);

	वापस 0;
पूर्ण

#अन्यथा

अटल पूर्णांक adis16400_debugfs_init(काष्ठा iio_dev *indio_dev)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

क्रमागत adis16400_chip_variant अणु
	ADIS16300,
	ADIS16334,
	ADIS16350,
	ADIS16360,
	ADIS16362,
	ADIS16364,
	ADIS16367,
	ADIS16400,
	ADIS16445,
	ADIS16448,
पूर्ण;

अटल पूर्णांक adis16334_get_freq(काष्ठा adis16400_state *st)
अणु
	पूर्णांक ret;
	uपूर्णांक16_t t;

	ret = __adis_पढ़ो_reg_16(&st->adis, ADIS16400_SMPL_PRD, &t);
	अगर (ret)
		वापस ret;

	t >>= ADIS16334_RATE_DIV_SHIFT;

	वापस 819200 >> t;
पूर्ण

अटल पूर्णांक adis16334_set_freq(काष्ठा adis16400_state *st, अचिन्हित पूर्णांक freq)
अणु
	अचिन्हित पूर्णांक t;

	अगर (freq < 819200)
		t = ilog2(819200 / freq);
	अन्यथा
		t = 0;

	अगर (t > 0x31)
		t = 0x31;

	t <<= ADIS16334_RATE_DIV_SHIFT;
	t |= ADIS16334_RATE_INT_CLK;

	वापस __adis_ग_लिखो_reg_16(&st->adis, ADIS16400_SMPL_PRD, t);
पूर्ण

अटल पूर्णांक adis16400_get_freq(काष्ठा adis16400_state *st)
अणु
	पूर्णांक sps, ret;
	uपूर्णांक16_t t;

	ret = __adis_पढ़ो_reg_16(&st->adis, ADIS16400_SMPL_PRD, &t);
	अगर (ret)
		वापस ret;

	sps = (t & ADIS16400_SMPL_PRD_TIME_BASE) ? 52851 : 1638404;
	sps /= (t & ADIS16400_SMPL_PRD_DIV_MASK) + 1;

	वापस sps;
पूर्ण

अटल पूर्णांक adis16400_set_freq(काष्ठा adis16400_state *st, अचिन्हित पूर्णांक freq)
अणु
	अचिन्हित पूर्णांक t;
	uपूर्णांक8_t val = 0;

	t = 1638404 / freq;
	अगर (t >= 128) अणु
		val |= ADIS16400_SMPL_PRD_TIME_BASE;
		t = 52851 / freq;
		अगर (t >= 128)
			t = 127;
	पूर्ण अन्यथा अगर (t != 0) अणु
		t--;
	पूर्ण

	val |= t;

	अगर (t >= 0x0A || (val & ADIS16400_SMPL_PRD_TIME_BASE))
		st->adis.spi->max_speed_hz = ADIS16400_SPI_SLOW;
	अन्यथा
		st->adis.spi->max_speed_hz = ADIS16400_SPI_FAST;

	वापस __adis_ग_लिखो_reg_8(&st->adis, ADIS16400_SMPL_PRD, val);
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक adis16400_3db_भागisors[] = अणु
	[0] = 2, /* Special हाल */
	[1] = 6,
	[2] = 12,
	[3] = 25,
	[4] = 50,
	[5] = 100,
	[6] = 200,
	[7] = 200, /* Not a valid setting */
पूर्ण;

अटल पूर्णांक __adis16400_set_filter(काष्ठा iio_dev *indio_dev, पूर्णांक sps, पूर्णांक val)
अणु
	काष्ठा adis16400_state *st = iio_priv(indio_dev);
	uपूर्णांक16_t val16;
	पूर्णांक i, ret;

	क्रम (i = ARRAY_SIZE(adis16400_3db_भागisors) - 1; i >= 1; i--) अणु
		अगर (sps / adis16400_3db_भागisors[i] >= val)
			अवरोध;
	पूर्ण

	ret = __adis_पढ़ो_reg_16(&st->adis, ADIS16400_SENS_AVG, &val16);
	अगर (ret)
		वापस ret;

	ret = __adis_ग_लिखो_reg_16(&st->adis, ADIS16400_SENS_AVG,
					 (val16 & ~0x07) | i);
	वापस ret;
पूर्ण

/* Power करोwn the device */
अटल पूर्णांक adis16400_stop_device(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा adis16400_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = adis_ग_लिखो_reg_16(&st->adis, ADIS16400_SLP_CNT,
			ADIS16400_SLP_CNT_POWER_OFF);
	अगर (ret)
		dev_err(&indio_dev->dev,
			"problem with turning device off: SLP_CNT");

	वापस ret;
पूर्ण

अटल पूर्णांक adis16400_initial_setup(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा adis16400_state *st = iio_priv(indio_dev);
	uपूर्णांक16_t prod_id, smp_prd;
	अचिन्हित पूर्णांक device_id;
	पूर्णांक ret;

	/* use low spi speed क्रम init अगर the device has a slow mode */
	अगर (st->variant->flags & ADIS16400_HAS_SLOW_MODE)
		st->adis.spi->max_speed_hz = ADIS16400_SPI_SLOW;
	अन्यथा
		st->adis.spi->max_speed_hz = ADIS16400_SPI_FAST;
	st->adis.spi->mode = SPI_MODE_3;
	spi_setup(st->adis.spi);

	ret = adis_initial_startup(&st->adis);
	अगर (ret)
		वापस ret;

	अगर (st->variant->flags & ADIS16400_HAS_PROD_ID) अणु
		ret = adis_पढ़ो_reg_16(&st->adis,
						ADIS16400_PRODUCT_ID, &prod_id);
		अगर (ret)
			जाओ err_ret;

		अगर (माला_पूछो(indio_dev->name, "adis%u\n", &device_id) != 1) अणु
			ret = -EINVAL;
			जाओ err_ret;
		पूर्ण

		अगर (prod_id != device_id)
			dev_warn(&indio_dev->dev, "Device ID(%u) and product ID(%u) do not match.",
					device_id, prod_id);

		dev_info(&indio_dev->dev, "%s: prod_id 0x%04x at CS%d (irq %d)\n",
			indio_dev->name, prod_id,
			st->adis.spi->chip_select, st->adis.spi->irq);
	पूर्ण
	/* use high spi speed अगर possible */
	अगर (st->variant->flags & ADIS16400_HAS_SLOW_MODE) अणु
		ret = adis_पढ़ो_reg_16(&st->adis, ADIS16400_SMPL_PRD, &smp_prd);
		अगर (ret)
			जाओ err_ret;

		अगर ((smp_prd & ADIS16400_SMPL_PRD_DIV_MASK) < 0x0A) अणु
			st->adis.spi->max_speed_hz = ADIS16400_SPI_FAST;
			spi_setup(st->adis.spi);
		पूर्ण
	पूर्ण

err_ret:
	वापस ret;
पूर्ण

अटल स्थिर uपूर्णांक8_t adis16400_addresses[] = अणु
	[ADIS16400_SCAN_GYRO_X] = ADIS16400_XGYRO_OFF,
	[ADIS16400_SCAN_GYRO_Y] = ADIS16400_YGYRO_OFF,
	[ADIS16400_SCAN_GYRO_Z] = ADIS16400_ZGYRO_OFF,
	[ADIS16400_SCAN_ACC_X] = ADIS16400_XACCL_OFF,
	[ADIS16400_SCAN_ACC_Y] = ADIS16400_YACCL_OFF,
	[ADIS16400_SCAN_ACC_Z] = ADIS16400_ZACCL_OFF,
पूर्ण;

अटल पूर्णांक adis16400_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val, पूर्णांक val2, दीर्घ info)
अणु
	काष्ठा adis16400_state *st = iio_priv(indio_dev);
	पूर्णांक ret, sps;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_CALIBBIAS:
		ret = adis_ग_लिखो_reg_16(&st->adis,
				adis16400_addresses[chan->scan_index], val);
		वापस ret;
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		/*
		 * Need to cache values so we can update अगर the frequency
		 * changes.
		 */
		adis_dev_lock(&st->adis);
		st->filt_पूर्णांक = val;
		/* Work out update to current value */
		sps = st->variant->get_freq(st);
		अगर (sps < 0) अणु
			adis_dev_unlock(&st->adis);
			वापस sps;
		पूर्ण

		ret = __adis16400_set_filter(indio_dev, sps,
			val * 1000 + val2 / 1000);
		adis_dev_unlock(&st->adis);
		वापस ret;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		sps = val * 1000 + val2 / 1000;

		अगर (sps <= 0)
			वापस -EINVAL;

		adis_dev_lock(&st->adis);
		ret = st->variant->set_freq(st, sps);
		adis_dev_unlock(&st->adis);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक adis16400_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	काष्ठा adis16400_state *st = iio_priv(indio_dev);
	पूर्णांक16_t val16;
	पूर्णांक ret;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस adis_single_conversion(indio_dev, chan, 0, val);
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
			*val = 0;
			*val2 = st->variant->gyro_scale_micro;
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_VOLTAGE:
			*val = 0;
			अगर (chan->channel == 0) अणु
				*val = 2;
				*val2 = 418000; /* 2.418 mV */
			पूर्ण अन्यथा अणु
				*val = 0;
				*val2 = 805800; /* 805.8 uV */
			पूर्ण
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_ACCEL:
			*val = 0;
			*val2 = st->variant->accel_scale_micro;
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_MAGN:
			*val = 0;
			*val2 = 500; /* 0.5 mgauss */
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_TEMP:
			*val = st->variant->temp_scale_nano / 1000000;
			*val2 = (st->variant->temp_scale_nano % 1000000);
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_PRESSURE:
			/* 20 uBar = 0.002kPascal */
			*val = 0;
			*val2 = 2000;
			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_CALIBBIAS:
		ret = adis_पढ़ो_reg_16(&st->adis,
				adis16400_addresses[chan->scan_index], &val16);
		अगर (ret)
			वापस ret;
		val16 = sign_extend32(val16, 11);
		*val = val16;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_OFFSET:
		/* currently only temperature */
		*val = st->variant->temp_offset;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		adis_dev_lock(&st->adis);
		/* Need both the number of taps and the sampling frequency */
		ret = __adis_पढ़ो_reg_16(&st->adis,
						ADIS16400_SENS_AVG,
						&val16);
		अगर (ret) अणु
			adis_dev_unlock(&st->adis);
			वापस ret;
		पूर्ण
		ret = st->variant->get_freq(st);
		adis_dev_unlock(&st->adis);
		अगर (ret)
			वापस ret;
		ret /= adis16400_3db_भागisors[val16 & 0x07];
		*val = ret / 1000;
		*val2 = (ret % 1000) * 1000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		adis_dev_lock(&st->adis);
		ret = st->variant->get_freq(st);
		adis_dev_unlock(&st->adis);
		अगर (ret)
			वापस ret;
		*val = ret / 1000;
		*val2 = (ret % 1000) * 1000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

#अगर IS_ENABLED(CONFIG_IIO_BUFFER)
अटल irqवापस_t adis16400_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा adis16400_state *st = iio_priv(indio_dev);
	काष्ठा adis *adis = &st->adis;
	u32 old_speed_hz = st->adis.spi->max_speed_hz;
	व्योम *buffer;
	पूर्णांक ret;

	अगर (!adis->buffer)
		वापस -ENOMEM;

	अगर (!(st->variant->flags & ADIS16400_NO_BURST) &&
		st->adis.spi->max_speed_hz > ADIS16400_SPI_BURST) अणु
		st->adis.spi->max_speed_hz = ADIS16400_SPI_BURST;
		spi_setup(st->adis.spi);
	पूर्ण

	ret = spi_sync(adis->spi, &adis->msg);
	अगर (ret)
		dev_err(&adis->spi->dev, "Failed to read data: %d\n", ret);

	अगर (!(st->variant->flags & ADIS16400_NO_BURST)) अणु
		st->adis.spi->max_speed_hz = old_speed_hz;
		spi_setup(st->adis.spi);
	पूर्ण

	अगर (st->variant->flags & ADIS16400_BURST_DIAG_STAT)
		buffer = adis->buffer + माप(u16);
	अन्यथा
		buffer = adis->buffer;

	iio_push_to_buffers_with_बारtamp(indio_dev, buffer,
		pf->बारtamp);

	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण
#अन्यथा
#घोषणा adis16400_trigger_handler	शून्य
#पूर्ण_अगर /* IS_ENABLED(CONFIG_IIO_BUFFER) */

#घोषणा ADIS16400_VOLTAGE_CHAN(addr, bits, name, si, chn) अणु \
	.type = IIO_VOLTAGE, \
	.indexed = 1, \
	.channel = chn, \
	.extend_name = name, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
		BIT(IIO_CHAN_INFO_SCALE), \
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.address = (addr), \
	.scan_index = (si), \
	.scan_type = अणु \
		.sign = 'u', \
		.realbits = (bits), \
		.storagebits = 16, \
		.shअगरt = 0, \
		.endianness = IIO_BE, \
	पूर्ण, \
पूर्ण

#घोषणा ADIS16400_SUPPLY_CHAN(addr, bits) \
	ADIS16400_VOLTAGE_CHAN(addr, bits, "supply", ADIS16400_SCAN_SUPPLY, 0)

#घोषणा ADIS16400_AUX_ADC_CHAN(addr, bits) \
	ADIS16400_VOLTAGE_CHAN(addr, bits, शून्य, ADIS16400_SCAN_ADC, 1)

#घोषणा ADIS16400_GYRO_CHAN(mod, addr, bits) अणु \
	.type = IIO_ANGL_VEL, \
	.modअगरied = 1, \
	.channel2 = IIO_MOD_ ## mod, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
		BIT(IIO_CHAN_INFO_CALIBBIAS),		  \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) | \
		BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY), \
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.address = addr, \
	.scan_index = ADIS16400_SCAN_GYRO_ ## mod, \
	.scan_type = अणु \
		.sign = 's', \
		.realbits = (bits), \
		.storagebits = 16, \
		.shअगरt = 0, \
		.endianness = IIO_BE, \
	पूर्ण, \
पूर्ण

#घोषणा ADIS16400_ACCEL_CHAN(mod, addr, bits) अणु \
	.type = IIO_ACCEL, \
	.modअगरied = 1, \
	.channel2 = IIO_MOD_ ## mod, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
		BIT(IIO_CHAN_INFO_CALIBBIAS), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) | \
		BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY), \
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.address = (addr), \
	.scan_index = ADIS16400_SCAN_ACC_ ## mod, \
	.scan_type = अणु \
		.sign = 's', \
		.realbits = (bits), \
		.storagebits = 16, \
		.shअगरt = 0, \
		.endianness = IIO_BE, \
	पूर्ण, \
पूर्ण

#घोषणा ADIS16400_MAGN_CHAN(mod, addr, bits) अणु \
	.type = IIO_MAGN, \
	.modअगरied = 1, \
	.channel2 = IIO_MOD_ ## mod, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) | \
		BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY), \
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.address = (addr), \
	.scan_index = ADIS16400_SCAN_MAGN_ ## mod, \
	.scan_type = अणु \
		.sign = 's', \
		.realbits = (bits), \
		.storagebits = 16, \
		.shअगरt = 0, \
		.endianness = IIO_BE, \
	पूर्ण, \
पूर्ण

#घोषणा ADIS16400_MOD_TEMP_NAME_X "x"
#घोषणा ADIS16400_MOD_TEMP_NAME_Y "y"
#घोषणा ADIS16400_MOD_TEMP_NAME_Z "z"

#घोषणा ADIS16400_MOD_TEMP_CHAN(mod, addr, bits) अणु \
	.type = IIO_TEMP, \
	.indexed = 1, \
	.channel = 0, \
	.extend_name = ADIS16400_MOD_TEMP_NAME_ ## mod, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
		BIT(IIO_CHAN_INFO_OFFSET) | \
		BIT(IIO_CHAN_INFO_SCALE), \
	.info_mask_shared_by_type = \
		BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY), \
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.address = (addr), \
	.scan_index = ADIS16350_SCAN_TEMP_ ## mod, \
	.scan_type = अणु \
		.sign = 's', \
		.realbits = (bits), \
		.storagebits = 16, \
		.shअगरt = 0, \
		.endianness = IIO_BE, \
	पूर्ण, \
पूर्ण

#घोषणा ADIS16400_TEMP_CHAN(addr, bits) अणु \
	.type = IIO_TEMP, \
	.indexed = 1, \
	.channel = 0, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
		BIT(IIO_CHAN_INFO_OFFSET) | \
		BIT(IIO_CHAN_INFO_SCALE), \
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.address = (addr), \
	.scan_index = ADIS16350_SCAN_TEMP_X, \
	.scan_type = अणु \
		.sign = 's', \
		.realbits = (bits), \
		.storagebits = 16, \
		.shअगरt = 0, \
		.endianness = IIO_BE, \
	पूर्ण, \
पूर्ण

#घोषणा ADIS16400_INCLI_CHAN(mod, addr, bits) अणु \
	.type = IIO_INCLI, \
	.modअगरied = 1, \
	.channel2 = IIO_MOD_ ## mod, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.address = (addr), \
	.scan_index = ADIS16300_SCAN_INCLI_ ## mod, \
	.scan_type = अणु \
		.sign = 's', \
		.realbits = (bits), \
		.storagebits = 16, \
		.shअगरt = 0, \
		.endianness = IIO_BE, \
	पूर्ण, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec adis16400_channels[] = अणु
	ADIS16400_SUPPLY_CHAN(ADIS16400_SUPPLY_OUT, 14),
	ADIS16400_GYRO_CHAN(X, ADIS16400_XGYRO_OUT, 14),
	ADIS16400_GYRO_CHAN(Y, ADIS16400_YGYRO_OUT, 14),
	ADIS16400_GYRO_CHAN(Z, ADIS16400_ZGYRO_OUT, 14),
	ADIS16400_ACCEL_CHAN(X, ADIS16400_XACCL_OUT, 14),
	ADIS16400_ACCEL_CHAN(Y, ADIS16400_YACCL_OUT, 14),
	ADIS16400_ACCEL_CHAN(Z, ADIS16400_ZACCL_OUT, 14),
	ADIS16400_MAGN_CHAN(X, ADIS16400_XMAGN_OUT, 14),
	ADIS16400_MAGN_CHAN(Y, ADIS16400_YMAGN_OUT, 14),
	ADIS16400_MAGN_CHAN(Z, ADIS16400_ZMAGN_OUT, 14),
	ADIS16400_TEMP_CHAN(ADIS16400_TEMP_OUT, 12),
	ADIS16400_AUX_ADC_CHAN(ADIS16400_AUX_ADC, 12),
	IIO_CHAN_SOFT_TIMESTAMP(ADIS16400_SCAN_TIMESTAMP),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec adis16445_channels[] = अणु
	ADIS16400_GYRO_CHAN(X, ADIS16400_XGYRO_OUT, 16),
	ADIS16400_GYRO_CHAN(Y, ADIS16400_YGYRO_OUT, 16),
	ADIS16400_GYRO_CHAN(Z, ADIS16400_ZGYRO_OUT, 16),
	ADIS16400_ACCEL_CHAN(X, ADIS16400_XACCL_OUT, 16),
	ADIS16400_ACCEL_CHAN(Y, ADIS16400_YACCL_OUT, 16),
	ADIS16400_ACCEL_CHAN(Z, ADIS16400_ZACCL_OUT, 16),
	ADIS16400_TEMP_CHAN(ADIS16448_TEMP_OUT, 12),
	IIO_CHAN_SOFT_TIMESTAMP(ADIS16400_SCAN_TIMESTAMP),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec adis16448_channels[] = अणु
	ADIS16400_GYRO_CHAN(X, ADIS16400_XGYRO_OUT, 16),
	ADIS16400_GYRO_CHAN(Y, ADIS16400_YGYRO_OUT, 16),
	ADIS16400_GYRO_CHAN(Z, ADIS16400_ZGYRO_OUT, 16),
	ADIS16400_ACCEL_CHAN(X, ADIS16400_XACCL_OUT, 16),
	ADIS16400_ACCEL_CHAN(Y, ADIS16400_YACCL_OUT, 16),
	ADIS16400_ACCEL_CHAN(Z, ADIS16400_ZACCL_OUT, 16),
	ADIS16400_MAGN_CHAN(X, ADIS16400_XMAGN_OUT, 16),
	ADIS16400_MAGN_CHAN(Y, ADIS16400_YMAGN_OUT, 16),
	ADIS16400_MAGN_CHAN(Z, ADIS16400_ZMAGN_OUT, 16),
	अणु
		.type = IIO_PRESSURE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.address = ADIS16448_BARO_OUT,
		.scan_index = ADIS16400_SCAN_BARO,
		.scan_type = अणु
			.sign = 's',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण,
	ADIS16400_TEMP_CHAN(ADIS16448_TEMP_OUT, 12),
	IIO_CHAN_SOFT_TIMESTAMP(ADIS16400_SCAN_TIMESTAMP),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec adis16350_channels[] = अणु
	ADIS16400_SUPPLY_CHAN(ADIS16400_SUPPLY_OUT, 12),
	ADIS16400_GYRO_CHAN(X, ADIS16400_XGYRO_OUT, 14),
	ADIS16400_GYRO_CHAN(Y, ADIS16400_YGYRO_OUT, 14),
	ADIS16400_GYRO_CHAN(Z, ADIS16400_ZGYRO_OUT, 14),
	ADIS16400_ACCEL_CHAN(X, ADIS16400_XACCL_OUT, 14),
	ADIS16400_ACCEL_CHAN(Y, ADIS16400_YACCL_OUT, 14),
	ADIS16400_ACCEL_CHAN(Z, ADIS16400_ZACCL_OUT, 14),
	ADIS16400_MAGN_CHAN(X, ADIS16400_XMAGN_OUT, 14),
	ADIS16400_MAGN_CHAN(Y, ADIS16400_YMAGN_OUT, 14),
	ADIS16400_MAGN_CHAN(Z, ADIS16400_ZMAGN_OUT, 14),
	ADIS16400_AUX_ADC_CHAN(ADIS16300_AUX_ADC, 12),
	ADIS16400_MOD_TEMP_CHAN(X, ADIS16350_XTEMP_OUT, 12),
	ADIS16400_MOD_TEMP_CHAN(Y, ADIS16350_YTEMP_OUT, 12),
	ADIS16400_MOD_TEMP_CHAN(Z, ADIS16350_ZTEMP_OUT, 12),
	IIO_CHAN_SOFT_TIMESTAMP(ADIS16400_SCAN_TIMESTAMP),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec adis16300_channels[] = अणु
	ADIS16400_SUPPLY_CHAN(ADIS16400_SUPPLY_OUT, 12),
	ADIS16400_GYRO_CHAN(X, ADIS16400_XGYRO_OUT, 14),
	ADIS16400_ACCEL_CHAN(X, ADIS16400_XACCL_OUT, 14),
	ADIS16400_ACCEL_CHAN(Y, ADIS16400_YACCL_OUT, 14),
	ADIS16400_ACCEL_CHAN(Z, ADIS16400_ZACCL_OUT, 14),
	ADIS16400_TEMP_CHAN(ADIS16350_XTEMP_OUT, 12),
	ADIS16400_AUX_ADC_CHAN(ADIS16300_AUX_ADC, 12),
	ADIS16400_INCLI_CHAN(X, ADIS16300_PITCH_OUT, 13),
	ADIS16400_INCLI_CHAN(Y, ADIS16300_ROLL_OUT, 13),
	IIO_CHAN_SOFT_TIMESTAMP(ADIS16400_SCAN_TIMESTAMP),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec adis16334_channels[] = अणु
	ADIS16400_GYRO_CHAN(X, ADIS16400_XGYRO_OUT, 14),
	ADIS16400_GYRO_CHAN(Y, ADIS16400_YGYRO_OUT, 14),
	ADIS16400_GYRO_CHAN(Z, ADIS16400_ZGYRO_OUT, 14),
	ADIS16400_ACCEL_CHAN(X, ADIS16400_XACCL_OUT, 14),
	ADIS16400_ACCEL_CHAN(Y, ADIS16400_YACCL_OUT, 14),
	ADIS16400_ACCEL_CHAN(Z, ADIS16400_ZACCL_OUT, 14),
	ADIS16400_TEMP_CHAN(ADIS16350_XTEMP_OUT, 12),
	IIO_CHAN_SOFT_TIMESTAMP(ADIS16400_SCAN_TIMESTAMP),
पूर्ण;

अटल स्थिर अक्षर * स्थिर adis16400_status_error_msgs[] = अणु
	[ADIS16400_DIAG_STAT_ZACCL_FAIL] = "Z-axis accelerometer self-test failure",
	[ADIS16400_DIAG_STAT_YACCL_FAIL] = "Y-axis accelerometer self-test failure",
	[ADIS16400_DIAG_STAT_XACCL_FAIL] = "X-axis accelerometer self-test failure",
	[ADIS16400_DIAG_STAT_XGYRO_FAIL] = "X-axis gyroscope self-test failure",
	[ADIS16400_DIAG_STAT_YGYRO_FAIL] = "Y-axis gyroscope self-test failure",
	[ADIS16400_DIAG_STAT_ZGYRO_FAIL] = "Z-axis gyroscope self-test failure",
	[ADIS16400_DIAG_STAT_ALARM2] = "Alarm 2 active",
	[ADIS16400_DIAG_STAT_ALARM1] = "Alarm 1 active",
	[ADIS16400_DIAG_STAT_FLASH_CHK] = "Flash checksum error",
	[ADIS16400_DIAG_STAT_SELF_TEST] = "Self test error",
	[ADIS16400_DIAG_STAT_OVERFLOW] = "Sensor overrange",
	[ADIS16400_DIAG_STAT_SPI_FAIL] = "SPI failure",
	[ADIS16400_DIAG_STAT_FLASH_UPT] = "Flash update failed",
	[ADIS16400_DIAG_STAT_POWER_HIGH] = "Power supply above 5.25V",
	[ADIS16400_DIAG_STAT_POWER_LOW] = "Power supply below 4.75V",
पूर्ण;

#घोषणा ADIS16400_DATA(_समयouts, _burst_len)				\
अणु									\
	.msc_ctrl_reg = ADIS16400_MSC_CTRL,				\
	.glob_cmd_reg = ADIS16400_GLOB_CMD,				\
	.diag_stat_reg = ADIS16400_DIAG_STAT,				\
	.पढ़ो_delay = 50,						\
	.ग_लिखो_delay = 50,						\
	.self_test_mask = ADIS16400_MSC_CTRL_MEM_TEST,			\
	.self_test_reg = ADIS16400_MSC_CTRL,				\
	.status_error_msgs = adis16400_status_error_msgs,		\
	.status_error_mask = BIT(ADIS16400_DIAG_STAT_ZACCL_FAIL) |	\
		BIT(ADIS16400_DIAG_STAT_YACCL_FAIL) |			\
		BIT(ADIS16400_DIAG_STAT_XACCL_FAIL) |			\
		BIT(ADIS16400_DIAG_STAT_XGYRO_FAIL) |			\
		BIT(ADIS16400_DIAG_STAT_YGYRO_FAIL) |			\
		BIT(ADIS16400_DIAG_STAT_ZGYRO_FAIL) |			\
		BIT(ADIS16400_DIAG_STAT_ALARM2) |			\
		BIT(ADIS16400_DIAG_STAT_ALARM1) |			\
		BIT(ADIS16400_DIAG_STAT_FLASH_CHK) |			\
		BIT(ADIS16400_DIAG_STAT_SELF_TEST) |			\
		BIT(ADIS16400_DIAG_STAT_OVERFLOW) |			\
		BIT(ADIS16400_DIAG_STAT_SPI_FAIL) |			\
		BIT(ADIS16400_DIAG_STAT_FLASH_UPT) |			\
		BIT(ADIS16400_DIAG_STAT_POWER_HIGH) |			\
		BIT(ADIS16400_DIAG_STAT_POWER_LOW),			\
	.समयouts = (_समयouts),					\
	.burst_reg_cmd = ADIS16400_GLOB_CMD,				\
	.burst_len = (_burst_len)					\
पूर्ण

अटल स्थिर काष्ठा adis_समयout adis16300_समयouts = अणु
	.reset_ms = ADIS16400_STARTUP_DELAY,
	.sw_reset_ms = ADIS16400_STARTUP_DELAY,
	.self_test_ms = ADIS16400_STARTUP_DELAY,
पूर्ण;

अटल स्थिर काष्ठा adis_समयout adis16334_समयouts = अणु
	.reset_ms = 60,
	.sw_reset_ms = 60,
	.self_test_ms = 14,
पूर्ण;

अटल स्थिर काष्ठा adis_समयout adis16362_समयouts = अणु
	.reset_ms = 130,
	.sw_reset_ms = 130,
	.self_test_ms = 12,
पूर्ण;

अटल स्थिर काष्ठा adis_समयout adis16400_समयouts = अणु
	.reset_ms = 170,
	.sw_reset_ms = 170,
	.self_test_ms = 12,
पूर्ण;

अटल स्थिर काष्ठा adis_समयout adis16445_समयouts = अणु
	.reset_ms = 55,
	.sw_reset_ms = 55,
	.self_test_ms = 16,
पूर्ण;

अटल स्थिर काष्ठा adis_समयout adis16448_समयouts = अणु
	.reset_ms = 90,
	.sw_reset_ms = 90,
	.self_test_ms = 45,
पूर्ण;

अटल काष्ठा adis16400_chip_info adis16400_chips[] = अणु
	[ADIS16300] = अणु
		.channels = adis16300_channels,
		.num_channels = ARRAY_SIZE(adis16300_channels),
		.flags = ADIS16400_HAS_PROD_ID | ADIS16400_HAS_SLOW_MODE |
				ADIS16400_HAS_SERIAL_NUMBER,
		.gyro_scale_micro = IIO_DEGREE_TO_RAD(50000), /* 0.05 deg/s */
		.accel_scale_micro = 5884,
		.temp_scale_nano = 140000000, /* 0.14 C */
		.temp_offset = 25000000 / 140000, /* 25 C = 0x00 */
		.set_freq = adis16400_set_freq,
		.get_freq = adis16400_get_freq,
		.adis_data = ADIS16400_DATA(&adis16300_समयouts, 18),
	पूर्ण,
	[ADIS16334] = अणु
		.channels = adis16334_channels,
		.num_channels = ARRAY_SIZE(adis16334_channels),
		.flags = ADIS16400_HAS_PROD_ID | ADIS16400_NO_BURST |
				ADIS16400_HAS_SERIAL_NUMBER,
		.gyro_scale_micro = IIO_DEGREE_TO_RAD(50000), /* 0.05 deg/s */
		.accel_scale_micro = IIO_G_TO_M_S_2(1000), /* 1 mg */
		.temp_scale_nano = 67850000, /* 0.06785 C */
		.temp_offset = 25000000 / 67850, /* 25 C = 0x00 */
		.set_freq = adis16334_set_freq,
		.get_freq = adis16334_get_freq,
		.adis_data = ADIS16400_DATA(&adis16334_समयouts, 0),
	पूर्ण,
	[ADIS16350] = अणु
		.channels = adis16350_channels,
		.num_channels = ARRAY_SIZE(adis16350_channels),
		.gyro_scale_micro = IIO_DEGREE_TO_RAD(73260), /* 0.07326 deg/s */
		.accel_scale_micro = IIO_G_TO_M_S_2(2522), /* 0.002522 g */
		.temp_scale_nano = 145300000, /* 0.1453 C */
		.temp_offset = 25000000 / 145300, /* 25 C = 0x00 */
		.flags = ADIS16400_NO_BURST | ADIS16400_HAS_SLOW_MODE,
		.set_freq = adis16400_set_freq,
		.get_freq = adis16400_get_freq,
		.adis_data = ADIS16400_DATA(&adis16300_समयouts, 0),
	पूर्ण,
	[ADIS16360] = अणु
		.channels = adis16350_channels,
		.num_channels = ARRAY_SIZE(adis16350_channels),
		.flags = ADIS16400_HAS_PROD_ID | ADIS16400_HAS_SLOW_MODE |
				ADIS16400_HAS_SERIAL_NUMBER,
		.gyro_scale_micro = IIO_DEGREE_TO_RAD(50000), /* 0.05 deg/s */
		.accel_scale_micro = IIO_G_TO_M_S_2(3333), /* 3.333 mg */
		.temp_scale_nano = 136000000, /* 0.136 C */
		.temp_offset = 25000000 / 136000, /* 25 C = 0x00 */
		.set_freq = adis16400_set_freq,
		.get_freq = adis16400_get_freq,
		.adis_data = ADIS16400_DATA(&adis16300_समयouts, 28),
	पूर्ण,
	[ADIS16362] = अणु
		.channels = adis16350_channels,
		.num_channels = ARRAY_SIZE(adis16350_channels),
		.flags = ADIS16400_HAS_PROD_ID | ADIS16400_HAS_SLOW_MODE |
				ADIS16400_HAS_SERIAL_NUMBER,
		.gyro_scale_micro = IIO_DEGREE_TO_RAD(50000), /* 0.05 deg/s */
		.accel_scale_micro = IIO_G_TO_M_S_2(333), /* 0.333 mg */
		.temp_scale_nano = 136000000, /* 0.136 C */
		.temp_offset = 25000000 / 136000, /* 25 C = 0x00 */
		.set_freq = adis16400_set_freq,
		.get_freq = adis16400_get_freq,
		.adis_data = ADIS16400_DATA(&adis16362_समयouts, 28),
	पूर्ण,
	[ADIS16364] = अणु
		.channels = adis16350_channels,
		.num_channels = ARRAY_SIZE(adis16350_channels),
		.flags = ADIS16400_HAS_PROD_ID | ADIS16400_HAS_SLOW_MODE |
				ADIS16400_HAS_SERIAL_NUMBER,
		.gyro_scale_micro = IIO_DEGREE_TO_RAD(50000), /* 0.05 deg/s */
		.accel_scale_micro = IIO_G_TO_M_S_2(1000), /* 1 mg */
		.temp_scale_nano = 136000000, /* 0.136 C */
		.temp_offset = 25000000 / 136000, /* 25 C = 0x00 */
		.set_freq = adis16400_set_freq,
		.get_freq = adis16400_get_freq,
		.adis_data = ADIS16400_DATA(&adis16362_समयouts, 28),
	पूर्ण,
	[ADIS16367] = अणु
		.channels = adis16350_channels,
		.num_channels = ARRAY_SIZE(adis16350_channels),
		.flags = ADIS16400_HAS_PROD_ID | ADIS16400_HAS_SLOW_MODE |
				ADIS16400_HAS_SERIAL_NUMBER,
		.gyro_scale_micro = IIO_DEGREE_TO_RAD(2000), /* 0.2 deg/s */
		.accel_scale_micro = IIO_G_TO_M_S_2(3333), /* 3.333 mg */
		.temp_scale_nano = 136000000, /* 0.136 C */
		.temp_offset = 25000000 / 136000, /* 25 C = 0x00 */
		.set_freq = adis16400_set_freq,
		.get_freq = adis16400_get_freq,
		.adis_data = ADIS16400_DATA(&adis16300_समयouts, 28),
	पूर्ण,
	[ADIS16400] = अणु
		.channels = adis16400_channels,
		.num_channels = ARRAY_SIZE(adis16400_channels),
		.flags = ADIS16400_HAS_PROD_ID | ADIS16400_HAS_SLOW_MODE,
		.gyro_scale_micro = IIO_DEGREE_TO_RAD(50000), /* 0.05 deg/s */
		.accel_scale_micro = IIO_G_TO_M_S_2(3333), /* 3.333 mg */
		.temp_scale_nano = 140000000, /* 0.14 C */
		.temp_offset = 25000000 / 140000, /* 25 C = 0x00 */
		.set_freq = adis16400_set_freq,
		.get_freq = adis16400_get_freq,
		.adis_data = ADIS16400_DATA(&adis16400_समयouts, 24),
	पूर्ण,
	[ADIS16445] = अणु
		.channels = adis16445_channels,
		.num_channels = ARRAY_SIZE(adis16445_channels),
		.flags = ADIS16400_HAS_PROD_ID |
				ADIS16400_HAS_SERIAL_NUMBER |
				ADIS16400_BURST_DIAG_STAT,
		.gyro_scale_micro = IIO_DEGREE_TO_RAD(10000), /* 0.01 deg/s */
		.accel_scale_micro = IIO_G_TO_M_S_2(250), /* 1/4000 g */
		.temp_scale_nano = 73860000, /* 0.07386 C */
		.temp_offset = 31000000 / 73860, /* 31 C = 0x00 */
		.set_freq = adis16334_set_freq,
		.get_freq = adis16334_get_freq,
		.adis_data = ADIS16400_DATA(&adis16445_समयouts, 16),
	पूर्ण,
	[ADIS16448] = अणु
		.channels = adis16448_channels,
		.num_channels = ARRAY_SIZE(adis16448_channels),
		.flags = ADIS16400_HAS_PROD_ID |
				ADIS16400_HAS_SERIAL_NUMBER |
				ADIS16400_BURST_DIAG_STAT,
		.gyro_scale_micro = IIO_DEGREE_TO_RAD(40000), /* 0.04 deg/s */
		.accel_scale_micro = IIO_G_TO_M_S_2(833), /* 1/1200 g */
		.temp_scale_nano = 73860000, /* 0.07386 C */
		.temp_offset = 31000000 / 73860, /* 31 C = 0x00 */
		.set_freq = adis16334_set_freq,
		.get_freq = adis16334_get_freq,
		.adis_data = ADIS16400_DATA(&adis16448_समयouts, 24),
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा iio_info adis16400_info = अणु
	.पढ़ो_raw = &adis16400_पढ़ो_raw,
	.ग_लिखो_raw = &adis16400_ग_लिखो_raw,
	.update_scan_mode = adis_update_scan_mode,
	.debugfs_reg_access = adis_debugfs_reg_access,
पूर्ण;

अटल व्योम adis16400_setup_chan_mask(काष्ठा adis16400_state *st)
अणु
	स्थिर काष्ठा adis16400_chip_info *chip_info = st->variant;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < chip_info->num_channels; i++) अणु
		स्थिर काष्ठा iio_chan_spec *ch = &chip_info->channels[i];

		अगर (ch->scan_index >= 0 &&
		    ch->scan_index != ADIS16400_SCAN_TIMESTAMP)
			st->avail_scan_mask[0] |= BIT(ch->scan_index);
	पूर्ण
पूर्ण

अटल व्योम adis16400_stop(व्योम *data)
अणु
	adis16400_stop_device(data);
पूर्ण

अटल पूर्णांक adis16400_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा adis16400_state *st;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;
	स्थिर काष्ठा adis_data *adis16400_data;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	/* this is only used क्रम removal purposes */
	spi_set_drvdata(spi, indio_dev);

	/* setup the industrialio driver allocated elements */
	st->variant = &adis16400_chips[spi_get_device_id(spi)->driver_data];
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->channels = st->variant->channels;
	indio_dev->num_channels = st->variant->num_channels;
	indio_dev->info = &adis16400_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	अगर (!(st->variant->flags & ADIS16400_NO_BURST)) अणु
		adis16400_setup_chan_mask(st);
		indio_dev->available_scan_masks = st->avail_scan_mask;
	पूर्ण

	adis16400_data = &st->variant->adis_data;

	ret = adis_init(&st->adis, indio_dev, spi, adis16400_data);
	अगर (ret)
		वापस ret;

	ret = devm_adis_setup_buffer_and_trigger(&st->adis, indio_dev, adis16400_trigger_handler);
	अगर (ret)
		वापस ret;

	/* Get the device पूर्णांकo a sane initial state */
	ret = adis16400_initial_setup(indio_dev);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(&spi->dev, adis16400_stop, indio_dev);
	अगर (ret)
		वापस ret;

	ret = devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
	अगर (ret)
		वापस ret;

	adis16400_debugfs_init(indio_dev);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id adis16400_id[] = अणु
	अणु"adis16300", ADIS16300पूर्ण,
	अणु"adis16305", ADIS16300पूर्ण,
	अणु"adis16334", ADIS16334पूर्ण,
	अणु"adis16350", ADIS16350पूर्ण,
	अणु"adis16354", ADIS16350पूर्ण,
	अणु"adis16355", ADIS16350पूर्ण,
	अणु"adis16360", ADIS16360पूर्ण,
	अणु"adis16362", ADIS16362पूर्ण,
	अणु"adis16364", ADIS16364पूर्ण,
	अणु"adis16365", ADIS16360पूर्ण,
	अणु"adis16367", ADIS16367पूर्ण,
	अणु"adis16400", ADIS16400पूर्ण,
	अणु"adis16405", ADIS16400पूर्ण,
	अणु"adis16445", ADIS16445पूर्ण,
	अणु"adis16448", ADIS16448पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, adis16400_id);

अटल काष्ठा spi_driver adis16400_driver = अणु
	.driver = अणु
		.name = "adis16400",
	पूर्ण,
	.id_table = adis16400_id,
	.probe = adis16400_probe,
पूर्ण;
module_spi_driver(adis16400_driver);

MODULE_AUTHOR("Manuel Stahl <manuel.stahl@iis.fraunhofer.de>");
MODULE_DESCRIPTION("Analog Devices ADIS16400/5 IMU SPI driver");
MODULE_LICENSE("GPL v2");
