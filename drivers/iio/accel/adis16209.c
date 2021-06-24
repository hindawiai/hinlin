<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ADIS16209 Dual-Axis Digital Inclinometer and Accelerometer
 *
 * Copyright 2010 Analog Devices Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/imu/adis.h>

#घोषणा ADIS16209_STARTUP_DELAY_MS	220
#घोषणा ADIS16209_FLASH_CNT_REG		0x00

/* Data Output Register Definitions */
#घोषणा ADIS16209_SUPPLY_OUT_REG	0x02
#घोषणा ADIS16209_XACCL_OUT_REG		0x04
#घोषणा ADIS16209_YACCL_OUT_REG		0x06
/* Output, auxiliary ADC input */
#घोषणा ADIS16209_AUX_ADC_REG		0x08
/* Output, temperature */
#घोषणा ADIS16209_TEMP_OUT_REG		0x0A
/* Output, +/- 90 degrees X-axis inclination */
#घोषणा ADIS16209_XINCL_OUT_REG		0x0C
#घोषणा ADIS16209_YINCL_OUT_REG		0x0E
/* Output, +/-180 vertical rotational position */
#घोषणा ADIS16209_ROT_OUT_REG		0x10

/*
 * Calibration Register Definitions.
 * Acceleration, inclination or rotation offset null.
 */
#घोषणा ADIS16209_XACCL_शून्य_REG	0x12
#घोषणा ADIS16209_YACCL_शून्य_REG	0x14
#घोषणा ADIS16209_XINCL_शून्य_REG	0x16
#घोषणा ADIS16209_YINCL_शून्य_REG	0x18
#घोषणा ADIS16209_ROT_शून्य_REG		0x1A

/* Alarm Register Definitions */
#घोषणा ADIS16209_ALM_MAG1_REG		0x20
#घोषणा ADIS16209_ALM_MAG2_REG		0x22
#घोषणा ADIS16209_ALM_SMPL1_REG		0x24
#घोषणा ADIS16209_ALM_SMPL2_REG		0x26
#घोषणा ADIS16209_ALM_CTRL_REG		0x28

#घोषणा ADIS16209_AUX_DAC_REG		0x30
#घोषणा ADIS16209_GPIO_CTRL_REG		0x32
#घोषणा ADIS16209_SMPL_PRD_REG		0x36
#घोषणा ADIS16209_AVG_CNT_REG		0x38
#घोषणा ADIS16209_SLP_CNT_REG		0x3A

#घोषणा ADIS16209_MSC_CTRL_REG			0x34
#घोषणा  ADIS16209_MSC_CTRL_PWRUP_SELF_TEST	BIT(10)
#घोषणा  ADIS16209_MSC_CTRL_SELF_TEST_EN	BIT(8)
#घोषणा  ADIS16209_MSC_CTRL_DATA_RDY_EN		BIT(2)
/* Data-पढ़ोy polarity: 1 = active high, 0 = active low */
#घोषणा  ADIS16209_MSC_CTRL_ACTIVE_HIGH		BIT(1)
#घोषणा  ADIS16209_MSC_CTRL_DATA_RDY_DIO2	BIT(0)

#घोषणा ADIS16209_STAT_REG			0x3C
#घोषणा  ADIS16209_STAT_ALARM2			BIT(9)
#घोषणा  ADIS16209_STAT_ALARM1			BIT(8)
#घोषणा  ADIS16209_STAT_SELFTEST_FAIL_BIT	5
#घोषणा  ADIS16209_STAT_SPI_FAIL_BIT		3
#घोषणा  ADIS16209_STAT_FLASH_UPT_FAIL_BIT	2
/* Power supply above 3.625 V */
#घोषणा  ADIS16209_STAT_POWER_HIGH_BIT		1
/* Power supply below 2.975 V */
#घोषणा  ADIS16209_STAT_POWER_LOW_BIT		0

#घोषणा ADIS16209_CMD_REG			0x3E
#घोषणा  ADIS16209_CMD_SW_RESET			BIT(7)
#घोषणा  ADIS16209_CMD_CLEAR_STAT		BIT(4)
#घोषणा  ADIS16209_CMD_FACTORY_CAL		BIT(1)

#घोषणा ADIS16209_ERROR_ACTIVE			BIT(14)

क्रमागत adis16209_scan अणु
	ADIS16209_SCAN_SUPPLY,
	ADIS16209_SCAN_ACC_X,
	ADIS16209_SCAN_ACC_Y,
	ADIS16209_SCAN_AUX_ADC,
	ADIS16209_SCAN_TEMP,
	ADIS16209_SCAN_INCLI_X,
	ADIS16209_SCAN_INCLI_Y,
	ADIS16209_SCAN_ROT,
पूर्ण;

अटल स्थिर u8 adis16209_addresses[8][1] = अणु
	[ADIS16209_SCAN_SUPPLY] = अणु पूर्ण,
	[ADIS16209_SCAN_AUX_ADC] = अणु पूर्ण,
	[ADIS16209_SCAN_ACC_X] = अणु ADIS16209_XACCL_शून्य_REG पूर्ण,
	[ADIS16209_SCAN_ACC_Y] = अणु ADIS16209_YACCL_शून्य_REG पूर्ण,
	[ADIS16209_SCAN_INCLI_X] = अणु ADIS16209_XINCL_शून्य_REG पूर्ण,
	[ADIS16209_SCAN_INCLI_Y] = अणु ADIS16209_YINCL_शून्य_REG पूर्ण,
	[ADIS16209_SCAN_ROT] = अणु पूर्ण,
	[ADIS16209_SCAN_TEMP] = अणु पूर्ण,
पूर्ण;

अटल पूर्णांक adis16209_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val,
			       पूर्णांक val2,
			       दीर्घ mask)
अणु
	काष्ठा adis *st = iio_priv(indio_dev);
	पूर्णांक m;

	अगर (mask != IIO_CHAN_INFO_CALIBBIAS)
		वापस -EINVAL;

	चयन (chan->type) अणु
	हाल IIO_ACCEL:
	हाल IIO_INCLI:
		m = GENMASK(13, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस adis_ग_लिखो_reg_16(st, adis16209_addresses[chan->scan_index][0],
				 val & m);
पूर्ण

अटल पूर्णांक adis16209_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक *val, पूर्णांक *val2,
			      दीर्घ mask)
अणु
	काष्ठा adis *st = iio_priv(indio_dev);
	पूर्णांक ret;
	पूर्णांक bits;
	u8 addr;
	s16 val16;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस adis_single_conversion(indio_dev, chan,
			ADIS16209_ERROR_ACTIVE, val);
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_VOLTAGE:
			*val = 0;
			चयन (chan->channel) अणु
			हाल 0:
				*val2 = 305180; /* 0.30518 mV */
				अवरोध;
			हाल 1:
				*val2 = 610500; /* 0.6105 mV */
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_TEMP:
			*val = -470;
			*val2 = 0;
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_ACCEL:
			/*
			 * IIO base unit क्रम sensitivity of accelerometer
			 * is milli g.
			 * 1 LSB represents 0.244 mg.
			 */
			*val = 0;
			*val2 = IIO_G_TO_M_S_2(244140);
			वापस IIO_VAL_INT_PLUS_न_अंकO;
		हाल IIO_INCLI:
		हाल IIO_ROT:
			/*
			 * IIO base units क्रम rotation are degrees.
			 * 1 LSB represents 0.025 milli degrees.
			 */
			*val = 0;
			*val2 = 25000;
			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_OFFSET:
		/*
		 * The raw ADC value is 0x4FE when the temperature
		 * is 45 degrees and the scale factor per milli
		 * degree celcius is -470.
		 */
		*val = 25000 / -470 - 0x4FE;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		चयन (chan->type) अणु
		हाल IIO_ACCEL:
			bits = 14;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		addr = adis16209_addresses[chan->scan_index][0];
		ret = adis_पढ़ो_reg_16(st, addr, &val16);
		अगर (ret)
			वापस ret;

		*val = sign_extend32(val16, bits - 1);
		वापस IIO_VAL_INT;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec adis16209_channels[] = अणु
	ADIS_SUPPLY_CHAN(ADIS16209_SUPPLY_OUT_REG, ADIS16209_SCAN_SUPPLY,
			 0, 14),
	ADIS_TEMP_CHAN(ADIS16209_TEMP_OUT_REG, ADIS16209_SCAN_TEMP, 0, 12),
	ADIS_ACCEL_CHAN(X, ADIS16209_XACCL_OUT_REG, ADIS16209_SCAN_ACC_X,
			BIT(IIO_CHAN_INFO_CALIBBIAS), 0, 14),
	ADIS_ACCEL_CHAN(Y, ADIS16209_YACCL_OUT_REG, ADIS16209_SCAN_ACC_Y,
			BIT(IIO_CHAN_INFO_CALIBBIAS), 0, 14),
	ADIS_AUX_ADC_CHAN(ADIS16209_AUX_ADC_REG, ADIS16209_SCAN_AUX_ADC, 0, 12),
	ADIS_INCLI_CHAN(X, ADIS16209_XINCL_OUT_REG, ADIS16209_SCAN_INCLI_X,
			0, 0, 14),
	ADIS_INCLI_CHAN(Y, ADIS16209_YINCL_OUT_REG, ADIS16209_SCAN_INCLI_Y,
			0, 0, 14),
	ADIS_ROT_CHAN(X, ADIS16209_ROT_OUT_REG, ADIS16209_SCAN_ROT, 0, 0, 14),
	IIO_CHAN_SOFT_TIMESTAMP(8)
पूर्ण;

अटल स्थिर काष्ठा iio_info adis16209_info = अणु
	.पढ़ो_raw = adis16209_पढ़ो_raw,
	.ग_लिखो_raw = adis16209_ग_लिखो_raw,
	.update_scan_mode = adis_update_scan_mode,
पूर्ण;

अटल स्थिर अक्षर * स्थिर adis16209_status_error_msgs[] = अणु
	[ADIS16209_STAT_SELFTEST_FAIL_BIT] = "Self test failure",
	[ADIS16209_STAT_SPI_FAIL_BIT] = "SPI failure",
	[ADIS16209_STAT_FLASH_UPT_FAIL_BIT] = "Flash update failed",
	[ADIS16209_STAT_POWER_HIGH_BIT] = "Power supply above 3.625V",
	[ADIS16209_STAT_POWER_LOW_BIT] = "Power supply below 2.975V",
पूर्ण;

अटल स्थिर काष्ठा adis_समयout adis16209_समयouts = अणु
	.reset_ms = ADIS16209_STARTUP_DELAY_MS,
	.self_test_ms = ADIS16209_STARTUP_DELAY_MS,
	.sw_reset_ms = ADIS16209_STARTUP_DELAY_MS,
पूर्ण;

अटल स्थिर काष्ठा adis_data adis16209_data = अणु
	.पढ़ो_delay = 30,
	.msc_ctrl_reg = ADIS16209_MSC_CTRL_REG,
	.glob_cmd_reg = ADIS16209_CMD_REG,
	.diag_stat_reg = ADIS16209_STAT_REG,

	.self_test_mask = ADIS16209_MSC_CTRL_SELF_TEST_EN,
	.self_test_reg = ADIS16209_MSC_CTRL_REG,
	.self_test_no_स्वतःclear = true,
	.समयouts = &adis16209_समयouts,

	.status_error_msgs = adis16209_status_error_msgs,
	.status_error_mask = BIT(ADIS16209_STAT_SELFTEST_FAIL_BIT) |
		BIT(ADIS16209_STAT_SPI_FAIL_BIT) |
		BIT(ADIS16209_STAT_FLASH_UPT_FAIL_BIT) |
		BIT(ADIS16209_STAT_POWER_HIGH_BIT) |
		BIT(ADIS16209_STAT_POWER_LOW_BIT),
पूर्ण;

अटल पूर्णांक adis16209_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा adis *st;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);

	indio_dev->name = spi->dev.driver->name;
	indio_dev->info = &adis16209_info;
	indio_dev->channels = adis16209_channels;
	indio_dev->num_channels = ARRAY_SIZE(adis16209_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = adis_init(st, indio_dev, spi, &adis16209_data);
	अगर (ret)
		वापस ret;

	ret = devm_adis_setup_buffer_and_trigger(st, indio_dev, शून्य);
	अगर (ret)
		वापस ret;

	ret = adis_initial_startup(st);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल काष्ठा spi_driver adis16209_driver = अणु
	.driver = अणु
		.name = "adis16209",
	पूर्ण,
	.probe = adis16209_probe,
पूर्ण;
module_spi_driver(adis16209_driver);

MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_DESCRIPTION("Analog Devices ADIS16209 Dual-Axis Digital Inclinometer and Accelerometer");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("spi:adis16209");
