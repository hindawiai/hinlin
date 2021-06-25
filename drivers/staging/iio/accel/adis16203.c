<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ADIS16203 Programmable 360 Degrees Inclinometer
 *
 * Copyright 2010 Analog Devices Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>

#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/imu/adis.h>
#समावेश <linux/iio/sysfs.h>

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/sysfs.h>

#घोषणा ADIS16203_STARTUP_DELAY 220 /* ms */

/* Flash memory ग_लिखो count */
#घोषणा ADIS16203_FLASH_CNT      0x00

/* Output, घातer supply */
#घोषणा ADIS16203_SUPPLY_OUT     0x02

/* Output, auxiliary ADC input */
#घोषणा ADIS16203_AUX_ADC        0x08

/* Output, temperature */
#घोषणा ADIS16203_TEMP_OUT       0x0A

/* Output, x-axis inclination */
#घोषणा ADIS16203_XINCL_OUT      0x0C

/* Output, y-axis inclination */
#घोषणा ADIS16203_YINCL_OUT      0x0E

/* Incline null calibration */
#घोषणा ADIS16203_INCL_शून्य      0x18

/* Alarm 1 amplitude threshold */
#घोषणा ADIS16203_ALM_MAG1       0x20

/* Alarm 2 amplitude threshold */
#घोषणा ADIS16203_ALM_MAG2       0x22

/* Alarm 1, sample period */
#घोषणा ADIS16203_ALM_SMPL1      0x24

/* Alarm 2, sample period */
#घोषणा ADIS16203_ALM_SMPL2      0x26

/* Alarm control */
#घोषणा ADIS16203_ALM_CTRL       0x28

/* Auxiliary DAC data */
#घोषणा ADIS16203_AUX_DAC        0x30

/* General-purpose digital input/output control */
#घोषणा ADIS16203_GPIO_CTRL      0x32

/* Miscellaneous control */
#घोषणा ADIS16203_MSC_CTRL       0x34

/* Internal sample period (rate) control */
#घोषणा ADIS16203_SMPL_PRD       0x36

/* Operation, filter configuration */
#घोषणा ADIS16203_AVG_CNT        0x38

/* Operation, sleep mode control */
#घोषणा ADIS16203_SLP_CNT        0x3A

/* Diagnostics, प्रणाली status रेजिस्टर */
#घोषणा ADIS16203_DIAG_STAT      0x3C

/* Operation, प्रणाली command रेजिस्टर */
#घोषणा ADIS16203_GLOB_CMD       0x3E

/* MSC_CTRL */

/* Self-test at घातer-on: 1 = disabled, 0 = enabled */
#घोषणा ADIS16203_MSC_CTRL_PWRUP_SELF_TEST      BIT(10)

/* Reverses rotation of both inclination outमाला_दो */
#घोषणा ADIS16203_MSC_CTRL_REVERSE_ROT_EN       BIT(9)

/* Self-test enable */
#घोषणा ADIS16203_MSC_CTRL_SELF_TEST_EN         BIT(8)

/* Data-पढ़ोy enable: 1 = enabled, 0 = disabled */
#घोषणा ADIS16203_MSC_CTRL_DATA_RDY_EN          BIT(2)

/* Data-पढ़ोy polarity: 1 = active high, 0 = active low */
#घोषणा ADIS16203_MSC_CTRL_ACTIVE_HIGH          BIT(1)

/* Data-पढ़ोy line selection: 1 = DIO1, 0 = DIO0 */
#घोषणा ADIS16203_MSC_CTRL_DATA_RDY_DIO1        BIT(0)

/* DIAG_STAT */

/* Alarm 2 status: 1 = alarm active, 0 = alarm inactive */
#घोषणा ADIS16203_DIAG_STAT_ALARM2        BIT(9)

/* Alarm 1 status: 1 = alarm active, 0 = alarm inactive */
#घोषणा ADIS16203_DIAG_STAT_ALARM1        BIT(8)

/* Self-test diagnostic error flag */
#घोषणा ADIS16203_DIAG_STAT_SELFTEST_FAIL_BIT 5

/* SPI communications failure */
#घोषणा ADIS16203_DIAG_STAT_SPI_FAIL_BIT      3

/* Flash update failure */
#घोषणा ADIS16203_DIAG_STAT_FLASH_UPT_BIT     2

/* Power supply above 3.625 V */
#घोषणा ADIS16203_DIAG_STAT_POWER_HIGH_BIT    1

/* Power supply below 2.975 V */
#घोषणा ADIS16203_DIAG_STAT_POWER_LOW_BIT     0

/* GLOB_CMD */

#घोषणा ADIS16203_GLOB_CMD_SW_RESET     BIT(7)
#घोषणा ADIS16203_GLOB_CMD_CLEAR_STAT   BIT(4)
#घोषणा ADIS16203_GLOB_CMD_FACTORY_CAL  BIT(1)

#घोषणा ADIS16203_ERROR_ACTIVE          BIT(14)

क्रमागत adis16203_scan अणु
	 ADIS16203_SCAN_INCLI_X,
	 ADIS16203_SCAN_INCLI_Y,
	 ADIS16203_SCAN_SUPPLY,
	 ADIS16203_SCAN_AUX_ADC,
	 ADIS16203_SCAN_TEMP,
पूर्ण;

#घोषणा DRIVER_NAME		"adis16203"

अटल स्थिर u8 adis16203_addresses[] = अणु
	[ADIS16203_SCAN_INCLI_X] = ADIS16203_INCL_शून्य,
पूर्ण;

अटल पूर्णांक adis16203_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val,
			       पूर्णांक val2,
			       दीर्घ mask)
अणु
	काष्ठा adis *st = iio_priv(indio_dev);
	/* currently only one writable parameter which keeps this simple */
	u8 addr = adis16203_addresses[chan->scan_index];

	वापस adis_ग_लिखो_reg_16(st, addr, val & 0x3FFF);
पूर्ण

अटल पूर्णांक adis16203_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक *val, पूर्णांक *val2,
			      दीर्घ mask)
अणु
	काष्ठा adis *st = iio_priv(indio_dev);
	पूर्णांक ret;
	u8 addr;
	s16 val16;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस adis_single_conversion(indio_dev, chan,
				ADIS16203_ERROR_ACTIVE, val);
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_VOLTAGE:
			अगर (chan->channel == 0) अणु
				*val = 1;
				*val2 = 220000; /* 1.22 mV */
			पूर्ण अन्यथा अणु
				*val = 0;
				*val2 = 610000; /* 0.61 mV */
			पूर्ण
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_TEMP:
			*val = -470; /* -0.47 C */
			*val2 = 0;
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_INCLI:
			*val = 0;
			*val2 = 25000; /* 0.025 degree */
			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_OFFSET:
		*val = 25000 / -470 - 1278; /* 25 C = 1278 */
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		addr = adis16203_addresses[chan->scan_index];
		ret = adis_पढ़ो_reg_16(st, addr, &val16);
		अगर (ret)
			वापस ret;
		*val = sign_extend32(val16, 13);
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec adis16203_channels[] = अणु
	ADIS_SUPPLY_CHAN(ADIS16203_SUPPLY_OUT, ADIS16203_SCAN_SUPPLY, 0, 12),
	ADIS_AUX_ADC_CHAN(ADIS16203_AUX_ADC, ADIS16203_SCAN_AUX_ADC, 0, 12),
	ADIS_INCLI_CHAN(X, ADIS16203_XINCL_OUT, ADIS16203_SCAN_INCLI_X,
			BIT(IIO_CHAN_INFO_CALIBBIAS), 0, 14),
	/* Fixme: Not what it appears to be - see data sheet */
	ADIS_INCLI_CHAN(Y, ADIS16203_YINCL_OUT, ADIS16203_SCAN_INCLI_Y,
			0, 0, 14),
	ADIS_TEMP_CHAN(ADIS16203_TEMP_OUT, ADIS16203_SCAN_TEMP, 0, 12),
	IIO_CHAN_SOFT_TIMESTAMP(5),
पूर्ण;

अटल स्थिर काष्ठा iio_info adis16203_info = अणु
	.पढ़ो_raw = adis16203_पढ़ो_raw,
	.ग_लिखो_raw = adis16203_ग_लिखो_raw,
	.update_scan_mode = adis_update_scan_mode,
पूर्ण;

अटल स्थिर अक्षर * स्थिर adis16203_status_error_msgs[] = अणु
	[ADIS16203_DIAG_STAT_SELFTEST_FAIL_BIT] = "Self test failure",
	[ADIS16203_DIAG_STAT_SPI_FAIL_BIT] = "SPI failure",
	[ADIS16203_DIAG_STAT_FLASH_UPT_BIT] = "Flash update failed",
	[ADIS16203_DIAG_STAT_POWER_HIGH_BIT] = "Power supply above 3.625V",
	[ADIS16203_DIAG_STAT_POWER_LOW_BIT] = "Power supply below 2.975V",
पूर्ण;

अटल स्थिर काष्ठा adis_समयout adis16203_समयouts = अणु
	.reset_ms = ADIS16203_STARTUP_DELAY,
	.sw_reset_ms = ADIS16203_STARTUP_DELAY,
	.self_test_ms = ADIS16203_STARTUP_DELAY
पूर्ण;

अटल स्थिर काष्ठा adis_data adis16203_data = अणु
	.पढ़ो_delay = 20,
	.msc_ctrl_reg = ADIS16203_MSC_CTRL,
	.glob_cmd_reg = ADIS16203_GLOB_CMD,
	.diag_stat_reg = ADIS16203_DIAG_STAT,

	.self_test_mask = ADIS16203_MSC_CTRL_SELF_TEST_EN,
	.self_test_reg = ADIS16203_MSC_CTRL,
	.self_test_no_स्वतःclear = true,
	.समयouts = &adis16203_समयouts,

	.status_error_msgs = adis16203_status_error_msgs,
	.status_error_mask = BIT(ADIS16203_DIAG_STAT_SELFTEST_FAIL_BIT) |
		BIT(ADIS16203_DIAG_STAT_SPI_FAIL_BIT) |
		BIT(ADIS16203_DIAG_STAT_FLASH_UPT_BIT) |
		BIT(ADIS16203_DIAG_STAT_POWER_HIGH_BIT) |
		BIT(ADIS16203_DIAG_STAT_POWER_LOW_BIT),
पूर्ण;

अटल पूर्णांक adis16203_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev;
	काष्ठा adis *st;

	/* setup the industrialio driver allocated elements */
	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;
	st = iio_priv(indio_dev);
	/* this is only used क्रम removal purposes */
	spi_set_drvdata(spi, indio_dev);

	indio_dev->name = spi->dev.driver->name;
	indio_dev->channels = adis16203_channels;
	indio_dev->num_channels = ARRAY_SIZE(adis16203_channels);
	indio_dev->info = &adis16203_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = adis_init(st, indio_dev, spi, &adis16203_data);
	अगर (ret)
		वापस ret;

	ret = devm_adis_setup_buffer_and_trigger(st, indio_dev, शून्य);
	अगर (ret)
		वापस ret;

	/* Get the device पूर्णांकo a sane initial state */
	ret = adis_initial_startup(st);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id adis16203_of_match[] = अणु
	अणु .compatible = "adi,adis16203" पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, adis16203_of_match);

अटल काष्ठा spi_driver adis16203_driver = अणु
	.driver = अणु
		.name = "adis16203",
		.of_match_table = adis16203_of_match,
	पूर्ण,
	.probe = adis16203_probe,
पूर्ण;
module_spi_driver(adis16203_driver);

MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_DESCRIPTION("Analog Devices ADIS16203 Programmable 360 Degrees Inclinometer");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("spi:adis16203");
