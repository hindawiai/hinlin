<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ADIS16260/ADIS16265 Programmable Digital Gyroscope Sensor Driver
 *
 * Copyright 2010 Analog Devices Inc.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/module.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/imu/adis.h>

#घोषणा ADIS16260_STARTUP_DELAY	220 /* ms */

#घोषणा ADIS16260_FLASH_CNT  0x00 /* Flash memory ग_लिखो count */
#घोषणा ADIS16260_SUPPLY_OUT 0x02 /* Power supply measurement */
#घोषणा ADIS16260_GYRO_OUT   0x04 /* X-axis gyroscope output */
#घोषणा ADIS16260_AUX_ADC    0x0A /* analog input channel measurement */
#घोषणा ADIS16260_TEMP_OUT   0x0C /* पूर्णांकernal temperature measurement */
#घोषणा ADIS16260_ANGL_OUT   0x0E /* angle displacement */
#घोषणा ADIS16260_GYRO_OFF   0x14 /* Calibration, offset/bias adjusपंचांगent */
#घोषणा ADIS16260_GYRO_SCALE 0x16 /* Calibration, scale adjusपंचांगent */
#घोषणा ADIS16260_ALM_MAG1   0x20 /* Alarm 1 magnitude/polarity setting */
#घोषणा ADIS16260_ALM_MAG2   0x22 /* Alarm 2 magnitude/polarity setting */
#घोषणा ADIS16260_ALM_SMPL1  0x24 /* Alarm 1 dynamic rate of change setting */
#घोषणा ADIS16260_ALM_SMPL2  0x26 /* Alarm 2 dynamic rate of change setting */
#घोषणा ADIS16260_ALM_CTRL   0x28 /* Alarm control */
#घोषणा ADIS16260_AUX_DAC    0x30 /* Auxiliary DAC data */
#घोषणा ADIS16260_GPIO_CTRL  0x32 /* Control, digital I/O line */
#घोषणा ADIS16260_MSC_CTRL   0x34 /* Control, data पढ़ोy, self-test settings */
#घोषणा ADIS16260_SMPL_PRD   0x36 /* Control, पूर्णांकernal sample rate */
#घोषणा ADIS16260_SENS_AVG   0x38 /* Control, dynamic range, filtering */
#घोषणा ADIS16260_SLP_CNT    0x3A /* Control, sleep mode initiation */
#घोषणा ADIS16260_DIAG_STAT  0x3C /* Diagnostic, error flags */
#घोषणा ADIS16260_GLOB_CMD   0x3E /* Control, global commands */
#घोषणा ADIS16260_LOT_ID1    0x52 /* Lot Identअगरication Code 1 */
#घोषणा ADIS16260_LOT_ID2    0x54 /* Lot Identअगरication Code 2 */
#घोषणा ADIS16260_PROD_ID    0x56 /* Product identअगरier;
				   * convert to decimal = 16,265/16,260 */
#घोषणा ADIS16260_SERIAL_NUM 0x58 /* Serial number */

#घोषणा ADIS16260_ERROR_ACTIVE			(1<<14)
#घोषणा ADIS16260_NEW_DATA			(1<<15)

/* MSC_CTRL */
#घोषणा ADIS16260_MSC_CTRL_MEM_TEST		(1<<11)
/* Internal self-test enable */
#घोषणा ADIS16260_MSC_CTRL_INT_SELF_TEST	(1<<10)
#घोषणा ADIS16260_MSC_CTRL_NEG_SELF_TEST	(1<<9)
#घोषणा ADIS16260_MSC_CTRL_POS_SELF_TEST	(1<<8)
#घोषणा ADIS16260_MSC_CTRL_DATA_RDY_EN		(1<<2)
#घोषणा ADIS16260_MSC_CTRL_DATA_RDY_POL_HIGH	(1<<1)
#घोषणा ADIS16260_MSC_CTRL_DATA_RDY_DIO2	(1<<0)

/* SMPL_PRD */
/* Time base (tB): 0 = 1.953 ms, 1 = 60.54 ms */
#घोषणा ADIS16260_SMPL_PRD_TIME_BASE	(1<<7)
#घोषणा ADIS16260_SMPL_PRD_DIV_MASK	0x7F

/* SLP_CNT */
#घोषणा ADIS16260_SLP_CNT_POWER_OFF     0x80

/* DIAG_STAT */
#घोषणा ADIS16260_DIAG_STAT_ALARM2	(1<<9)
#घोषणा ADIS16260_DIAG_STAT_ALARM1	(1<<8)
#घोषणा ADIS16260_DIAG_STAT_FLASH_CHK_BIT	6
#घोषणा ADIS16260_DIAG_STAT_SELF_TEST_BIT	5
#घोषणा ADIS16260_DIAG_STAT_OVERFLOW_BIT	4
#घोषणा ADIS16260_DIAG_STAT_SPI_FAIL_BIT	3
#घोषणा ADIS16260_DIAG_STAT_FLASH_UPT_BIT	2
#घोषणा ADIS16260_DIAG_STAT_POWER_HIGH_BIT	1
#घोषणा ADIS16260_DIAG_STAT_POWER_LOW_BIT	0

/* GLOB_CMD */
#घोषणा ADIS16260_GLOB_CMD_SW_RESET	(1<<7)
#घोषणा ADIS16260_GLOB_CMD_FLASH_UPD	(1<<3)
#घोषणा ADIS16260_GLOB_CMD_DAC_LATCH	(1<<2)
#घोषणा ADIS16260_GLOB_CMD_FAC_CALIB	(1<<1)
#घोषणा ADIS16260_GLOB_CMD_AUTO_शून्य	(1<<0)

#घोषणा ADIS16260_SPI_SLOW	(u32)(300 * 1000)
#घोषणा ADIS16260_SPI_BURST	(u32)(1000 * 1000)
#घोषणा ADIS16260_SPI_FAST	(u32)(2000 * 1000)

/* At the moment triggers are only used क्रम ring buffer
 * filling. This may change!
 */

#घोषणा ADIS16260_SCAN_GYRO	0
#घोषणा ADIS16260_SCAN_SUPPLY	1
#घोषणा ADIS16260_SCAN_AUX_ADC	2
#घोषणा ADIS16260_SCAN_TEMP	3
#घोषणा ADIS16260_SCAN_ANGL	4

काष्ठा adis16260_chip_info अणु
	अचिन्हित पूर्णांक gyro_max_val;
	अचिन्हित पूर्णांक gyro_max_scale;
	स्थिर काष्ठा iio_chan_spec *channels;
	अचिन्हित पूर्णांक num_channels;
पूर्ण;

काष्ठा adis16260 अणु
	स्थिर काष्ठा adis16260_chip_info *info;

	काष्ठा adis adis;
पूर्ण;

क्रमागत adis16260_type अणु
	ADIS16251,
	ADIS16260,
	ADIS16266,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec adis16260_channels[] = अणु
	ADIS_GYRO_CHAN(X, ADIS16260_GYRO_OUT, ADIS16260_SCAN_GYRO,
		BIT(IIO_CHAN_INFO_CALIBBIAS) |
		BIT(IIO_CHAN_INFO_CALIBSCALE),
		BIT(IIO_CHAN_INFO_SAMP_FREQ), 14),
	ADIS_INCLI_CHAN(X, ADIS16260_ANGL_OUT, ADIS16260_SCAN_ANGL, 0,
		BIT(IIO_CHAN_INFO_SAMP_FREQ), 14),
	ADIS_TEMP_CHAN(ADIS16260_TEMP_OUT, ADIS16260_SCAN_TEMP,
		BIT(IIO_CHAN_INFO_SAMP_FREQ), 12),
	ADIS_SUPPLY_CHAN(ADIS16260_SUPPLY_OUT, ADIS16260_SCAN_SUPPLY,
		BIT(IIO_CHAN_INFO_SAMP_FREQ), 12),
	ADIS_AUX_ADC_CHAN(ADIS16260_AUX_ADC, ADIS16260_SCAN_AUX_ADC,
		BIT(IIO_CHAN_INFO_SAMP_FREQ), 12),
	IIO_CHAN_SOFT_TIMESTAMP(5),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec adis16266_channels[] = अणु
	ADIS_GYRO_CHAN(X, ADIS16260_GYRO_OUT, ADIS16260_SCAN_GYRO,
		BIT(IIO_CHAN_INFO_CALIBBIAS) |
		BIT(IIO_CHAN_INFO_CALIBSCALE),
		BIT(IIO_CHAN_INFO_SAMP_FREQ), 14),
	ADIS_TEMP_CHAN(ADIS16260_TEMP_OUT, ADIS16260_SCAN_TEMP,
		BIT(IIO_CHAN_INFO_SAMP_FREQ), 12),
	ADIS_SUPPLY_CHAN(ADIS16260_SUPPLY_OUT, ADIS16260_SCAN_SUPPLY,
		BIT(IIO_CHAN_INFO_SAMP_FREQ), 12),
	ADIS_AUX_ADC_CHAN(ADIS16260_AUX_ADC, ADIS16260_SCAN_AUX_ADC,
		BIT(IIO_CHAN_INFO_SAMP_FREQ), 12),
	IIO_CHAN_SOFT_TIMESTAMP(4),
पूर्ण;

अटल स्थिर काष्ठा adis16260_chip_info adis16260_chip_info_table[] = अणु
	[ADIS16251] = अणु
		.gyro_max_scale = 80,
		.gyro_max_val = IIO_RAD_TO_DEGREE(4368),
		.channels = adis16260_channels,
		.num_channels = ARRAY_SIZE(adis16260_channels),
	पूर्ण,
	[ADIS16260] = अणु
		.gyro_max_scale = 320,
		.gyro_max_val = IIO_RAD_TO_DEGREE(4368),
		.channels = adis16260_channels,
		.num_channels = ARRAY_SIZE(adis16260_channels),
	पूर्ण,
	[ADIS16266] = अणु
		.gyro_max_scale = 14000,
		.gyro_max_val = IIO_RAD_TO_DEGREE(3357),
		.channels = adis16266_channels,
		.num_channels = ARRAY_SIZE(adis16266_channels),
	पूर्ण,
पूर्ण;

/* Power करोwn the device */
अटल पूर्णांक adis16260_stop_device(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा adis16260 *adis16260 = iio_priv(indio_dev);
	पूर्णांक ret;
	u16 val = ADIS16260_SLP_CNT_POWER_OFF;

	ret = adis_ग_लिखो_reg_16(&adis16260->adis, ADIS16260_SLP_CNT, val);
	अगर (ret)
		dev_err(&indio_dev->dev, "problem with turning device off: SLP_CNT");

	वापस ret;
पूर्ण

अटल स्थिर u8 adis16260_addresses[][2] = अणु
	[ADIS16260_SCAN_GYRO] = अणु ADIS16260_GYRO_OFF, ADIS16260_GYRO_SCALE पूर्ण,
पूर्ण;

अटल पूर्णांक adis16260_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक *val, पूर्णांक *val2,
			      दीर्घ mask)
अणु
	काष्ठा adis16260 *adis16260 = iio_priv(indio_dev);
	स्थिर काष्ठा adis16260_chip_info *info = adis16260->info;
	काष्ठा adis *adis = &adis16260->adis;
	पूर्णांक ret;
	u8 addr;
	s16 val16;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस adis_single_conversion(indio_dev, chan,
				ADIS16260_ERROR_ACTIVE, val);
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
			*val = info->gyro_max_scale;
			*val2 = info->gyro_max_val;
			वापस IIO_VAL_FRACTIONAL;
		हाल IIO_INCLI:
			*val = 0;
			*val2 = IIO_DEGREE_TO_RAD(36630);
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_VOLTAGE:
			अगर (chan->channel == 0) अणु
				*val = 1;
				*val2 = 831500; /* 1.8315 mV */
			पूर्ण अन्यथा अणु
				*val = 0;
				*val2 = 610500; /* 610.5 uV */
			पूर्ण
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_TEMP:
			*val = 145;
			*val2 = 300000; /* 0.1453 C */
			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_OFFSET:
		*val = 250000 / 1453; /* 25 C = 0x00 */
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		addr = adis16260_addresses[chan->scan_index][0];
		ret = adis_पढ़ो_reg_16(adis, addr, &val16);
		अगर (ret)
			वापस ret;

		*val = sign_extend32(val16, 11);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_CALIBSCALE:
		addr = adis16260_addresses[chan->scan_index][1];
		ret = adis_पढ़ो_reg_16(adis, addr, &val16);
		अगर (ret)
			वापस ret;

		*val = val16;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret = adis_पढ़ो_reg_16(adis, ADIS16260_SMPL_PRD, &val16);
		अगर (ret)
			वापस ret;

		अगर (spi_get_device_id(adis->spi)->driver_data)
		/* If an adis16251 */
			*val = (val16 & ADIS16260_SMPL_PRD_TIME_BASE) ?
				8 : 256;
		अन्यथा
			*val = (val16 & ADIS16260_SMPL_PRD_TIME_BASE) ?
				66 : 2048;
		*val /= (val16 & ADIS16260_SMPL_PRD_DIV_MASK) + 1;
		वापस IIO_VAL_INT;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक adis16260_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val,
			       पूर्णांक val2,
			       दीर्घ mask)
अणु
	काष्ठा adis16260 *adis16260 = iio_priv(indio_dev);
	काष्ठा adis *adis = &adis16260->adis;
	पूर्णांक ret;
	u8 addr;
	u8 t;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_CALIBBIAS:
		अगर (val < -2048 || val >= 2048)
			वापस -EINVAL;

		addr = adis16260_addresses[chan->scan_index][0];
		वापस adis_ग_लिखो_reg_16(adis, addr, val);
	हाल IIO_CHAN_INFO_CALIBSCALE:
		अगर (val < 0 || val >= 4096)
			वापस -EINVAL;

		addr = adis16260_addresses[chan->scan_index][1];
		वापस adis_ग_लिखो_reg_16(adis, addr, val);
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		mutex_lock(&adis->state_lock);
		अगर (spi_get_device_id(adis->spi)->driver_data)
			t = 256 / val;
		अन्यथा
			t = 2048 / val;

		अगर (t > ADIS16260_SMPL_PRD_DIV_MASK)
			t = ADIS16260_SMPL_PRD_DIV_MASK;
		अन्यथा अगर (t > 0)
			t--;

		अगर (t >= 0x0A)
			adis->spi->max_speed_hz = ADIS16260_SPI_SLOW;
		अन्यथा
			adis->spi->max_speed_hz = ADIS16260_SPI_FAST;
		ret = __adis_ग_लिखो_reg_8(adis, ADIS16260_SMPL_PRD, t);

		mutex_unlock(&adis->state_lock);
		वापस ret;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info adis16260_info = अणु
	.पढ़ो_raw = &adis16260_पढ़ो_raw,
	.ग_लिखो_raw = &adis16260_ग_लिखो_raw,
	.update_scan_mode = adis_update_scan_mode,
पूर्ण;

अटल स्थिर अक्षर * स्थिर adis1620_status_error_msgs[] = अणु
	[ADIS16260_DIAG_STAT_FLASH_CHK_BIT] = "Flash checksum error",
	[ADIS16260_DIAG_STAT_SELF_TEST_BIT] = "Self test error",
	[ADIS16260_DIAG_STAT_OVERFLOW_BIT] = "Sensor overrange",
	[ADIS16260_DIAG_STAT_SPI_FAIL_BIT] = "SPI failure",
	[ADIS16260_DIAG_STAT_FLASH_UPT_BIT] = "Flash update failed",
	[ADIS16260_DIAG_STAT_POWER_HIGH_BIT] = "Power supply above 5.25",
	[ADIS16260_DIAG_STAT_POWER_LOW_BIT] = "Power supply below 4.75",
पूर्ण;

अटल स्थिर काष्ठा adis_समयout adis16260_समयouts = अणु
	.reset_ms = ADIS16260_STARTUP_DELAY,
	.sw_reset_ms = ADIS16260_STARTUP_DELAY,
	.self_test_ms = ADIS16260_STARTUP_DELAY,
पूर्ण;

अटल स्थिर काष्ठा adis_data adis16260_data = अणु
	.ग_लिखो_delay = 30,
	.पढ़ो_delay = 30,
	.msc_ctrl_reg = ADIS16260_MSC_CTRL,
	.glob_cmd_reg = ADIS16260_GLOB_CMD,
	.diag_stat_reg = ADIS16260_DIAG_STAT,

	.self_test_mask = ADIS16260_MSC_CTRL_MEM_TEST,
	.self_test_reg = ADIS16260_MSC_CTRL,
	.समयouts = &adis16260_समयouts,

	.status_error_msgs = adis1620_status_error_msgs,
	.status_error_mask = BIT(ADIS16260_DIAG_STAT_FLASH_CHK_BIT) |
		BIT(ADIS16260_DIAG_STAT_SELF_TEST_BIT) |
		BIT(ADIS16260_DIAG_STAT_OVERFLOW_BIT) |
		BIT(ADIS16260_DIAG_STAT_SPI_FAIL_BIT) |
		BIT(ADIS16260_DIAG_STAT_FLASH_UPT_BIT) |
		BIT(ADIS16260_DIAG_STAT_POWER_HIGH_BIT) |
		BIT(ADIS16260_DIAG_STAT_POWER_LOW_BIT),
पूर्ण;

अटल व्योम adis16260_stop(व्योम *data)
अणु
	adis16260_stop_device(data);
पूर्ण

अटल पूर्णांक adis16260_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id;
	काष्ठा adis16260 *adis16260;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	id = spi_get_device_id(spi);
	अगर (!id)
		वापस -ENODEV;

	/* setup the industrialio driver allocated elements */
	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*adis16260));
	अगर (!indio_dev)
		वापस -ENOMEM;
	adis16260 = iio_priv(indio_dev);
	/* this is only used क्रम removal purposes */
	spi_set_drvdata(spi, indio_dev);

	adis16260->info = &adis16260_chip_info_table[id->driver_data];

	indio_dev->name = id->name;
	indio_dev->info = &adis16260_info;
	indio_dev->channels = adis16260->info->channels;
	indio_dev->num_channels = adis16260->info->num_channels;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = adis_init(&adis16260->adis, indio_dev, spi, &adis16260_data);
	अगर (ret)
		वापस ret;

	ret = devm_adis_setup_buffer_and_trigger(&adis16260->adis, indio_dev, शून्य);
	अगर (ret)
		वापस ret;

	/* Get the device पूर्णांकo a sane initial state */
	ret = adis_initial_startup(&adis16260->adis);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(&spi->dev, adis16260_stop, indio_dev);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

/*
 * These parts करो not need to be dअगरferentiated until someone adds
 * support क्रम the on chip filtering.
 */
अटल स्थिर काष्ठा spi_device_id adis16260_id[] = अणु
	अणु"adis16260", ADIS16260पूर्ण,
	अणु"adis16265", ADIS16260पूर्ण,
	अणु"adis16266", ADIS16266पूर्ण,
	अणु"adis16250", ADIS16260पूर्ण,
	अणु"adis16255", ADIS16260पूर्ण,
	अणु"adis16251", ADIS16251पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, adis16260_id);

अटल काष्ठा spi_driver adis16260_driver = अणु
	.driver = अणु
		.name = "adis16260",
	पूर्ण,
	.probe = adis16260_probe,
	.id_table = adis16260_id,
पूर्ण;
module_spi_driver(adis16260_driver);

MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_DESCRIPTION("Analog Devices ADIS16260/5 Digital Gyroscope Sensor");
MODULE_LICENSE("GPL v2");
