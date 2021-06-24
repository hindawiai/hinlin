<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ADIS16201 Dual-Axis Digital Inclinometer and Accelerometer
 *
 * Copyright 2010 Analog Devices Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/sysfs.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/imu/adis.h>

#घोषणा ADIS16201_STARTUP_DELAY_MS			220
#घोषणा ADIS16201_FLASH_CNT				0x00

/* Data Output Register Inक्रमmation */
#घोषणा ADIS16201_SUPPLY_OUT_REG			0x02
#घोषणा ADIS16201_XACCL_OUT_REG				0x04
#घोषणा ADIS16201_YACCL_OUT_REG				0x06
#घोषणा ADIS16201_AUX_ADC_REG				0x08
#घोषणा ADIS16201_TEMP_OUT_REG				0x0A
#घोषणा ADIS16201_XINCL_OUT_REG				0x0C
#घोषणा ADIS16201_YINCL_OUT_REG				0x0E

/* Calibration Register Definition */
#घोषणा ADIS16201_XACCL_OFFS_REG			0x10
#घोषणा ADIS16201_YACCL_OFFS_REG			0x12
#घोषणा ADIS16201_XACCL_SCALE_REG			0x14
#घोषणा ADIS16201_YACCL_SCALE_REG			0x16
#घोषणा ADIS16201_XINCL_OFFS_REG			0x18
#घोषणा ADIS16201_YINCL_OFFS_REG			0x1A
#घोषणा ADIS16201_XINCL_SCALE_REG			0x1C
#घोषणा ADIS16201_YINCL_SCALE_REG			0x1E

/* Alarm Register Definition */
#घोषणा ADIS16201_ALM_MAG1_REG				0x20
#घोषणा ADIS16201_ALM_MAG2_REG				0x22
#घोषणा ADIS16201_ALM_SMPL1_REG				0x24
#घोषणा ADIS16201_ALM_SMPL2_REG				0x26
#घोषणा ADIS16201_ALM_CTRL_REG				0x28

#घोषणा ADIS16201_AUX_DAC_REG				0x30
#घोषणा ADIS16201_GPIO_CTRL_REG				0x32
#घोषणा ADIS16201_SMPL_PRD_REG				0x36
/* Operation, filter configuration */
#घोषणा ADIS16201_AVG_CNT_REG				0x38
#घोषणा ADIS16201_SLP_CNT_REG				0x3A

/* Miscellaneous Control Register Definition */
#घोषणा ADIS16201_MSC_CTRL_REG				0x34
#घोषणा  ADIS16201_MSC_CTRL_SELF_TEST_EN		BIT(8)
/* Data-पढ़ोy enable: 1 = enabled, 0 = disabled */
#घोषणा  ADIS16201_MSC_CTRL_DATA_RDY_EN			BIT(2)
/* Data-पढ़ोy polarity: 1 = active high, 0 = active low */
#घोषणा  ADIS16201_MSC_CTRL_ACTIVE_DATA_RDY_HIGH	BIT(1)
/* Data-पढ़ोy line selection: 1 = DIO1, 0 = DIO0 */
#घोषणा  ADIS16201_MSC_CTRL_DATA_RDY_DIO1		BIT(0)

/* Diagnostics System Status Register Definition */
#घोषणा ADIS16201_DIAG_STAT_REG				0x3C
#घोषणा  ADIS16201_DIAG_STAT_ALARM2			BIT(9)
#घोषणा  ADIS16201_DIAG_STAT_ALARM1			BIT(8)
#घोषणा  ADIS16201_DIAG_STAT_SPI_FAIL_BIT		3
#घोषणा  ADIS16201_DIAG_STAT_FLASH_UPT_FAIL_BIT		2
/* Power supply above 3.625 V */
#घोषणा  ADIS16201_DIAG_STAT_POWER_HIGH_BIT		1
/* Power supply below 2.975 V */
#घोषणा  ADIS16201_DIAG_STAT_POWER_LOW_BIT		0

/* System Command Register Definition */
#घोषणा ADIS16201_GLOB_CMD_REG				0x3E
#घोषणा  ADIS16201_GLOB_CMD_SW_RESET			BIT(7)
#घोषणा  ADIS16201_GLOB_CMD_FACTORY_RESET		BIT(1)

#घोषणा ADIS16201_ERROR_ACTIVE				BIT(14)

क्रमागत adis16201_scan अणु
	ADIS16201_SCAN_ACC_X,
	ADIS16201_SCAN_ACC_Y,
	ADIS16201_SCAN_INCLI_X,
	ADIS16201_SCAN_INCLI_Y,
	ADIS16201_SCAN_SUPPLY,
	ADIS16201_SCAN_AUX_ADC,
	ADIS16201_SCAN_TEMP,
पूर्ण;

अटल स्थिर u8 adis16201_addresses[] = अणु
	[ADIS16201_SCAN_ACC_X] = ADIS16201_XACCL_OFFS_REG,
	[ADIS16201_SCAN_ACC_Y] = ADIS16201_YACCL_OFFS_REG,
	[ADIS16201_SCAN_INCLI_X] = ADIS16201_XINCL_OFFS_REG,
	[ADIS16201_SCAN_INCLI_Y] = ADIS16201_YINCL_OFFS_REG,
पूर्ण;

अटल पूर्णांक adis16201_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
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
					      ADIS16201_ERROR_ACTIVE, val);
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_VOLTAGE:
			अगर (chan->channel == 0) अणु
			/* Voltage base units are mV hence 1.22 mV */
				*val = 1;
				*val2 = 220000;
			पूर्ण अन्यथा अणु
			/* Voltage base units are mV hence 0.61 mV */
				*val = 0;
				*val2 = 610000;
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
			*val2 = IIO_G_TO_M_S_2(462400);
			वापस IIO_VAL_INT_PLUS_न_अंकO;
		हाल IIO_INCLI:
			*val = 0;
			*val2 = 100000;
			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_OFFSET:
		/*
		 * The raw ADC value is 1278 when the temperature
		 * is 25 degrees and the scale factor per milli
		 * degree celcius is -470.
		 */
		*val = 25000 / -470 - 1278;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		चयन (chan->type) अणु
		हाल IIO_ACCEL:
			bits = 12;
			अवरोध;
		हाल IIO_INCLI:
			bits = 9;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		addr = adis16201_addresses[chan->scan_index];
		ret = adis_पढ़ो_reg_16(st, addr, &val16);
		अगर (ret)
			वापस ret;

		*val = sign_extend32(val16, bits - 1);
		वापस IIO_VAL_INT;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक adis16201_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
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
		m = GENMASK(11, 0);
		अवरोध;
	हाल IIO_INCLI:
		m = GENMASK(8, 0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस adis_ग_लिखो_reg_16(st, adis16201_addresses[chan->scan_index],
				 val & m);
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec adis16201_channels[] = अणु
	ADIS_SUPPLY_CHAN(ADIS16201_SUPPLY_OUT_REG, ADIS16201_SCAN_SUPPLY, 0,
			 12),
	ADIS_TEMP_CHAN(ADIS16201_TEMP_OUT_REG, ADIS16201_SCAN_TEMP, 0, 12),
	ADIS_ACCEL_CHAN(X, ADIS16201_XACCL_OUT_REG, ADIS16201_SCAN_ACC_X,
			BIT(IIO_CHAN_INFO_CALIBBIAS), 0, 14),
	ADIS_ACCEL_CHAN(Y, ADIS16201_YACCL_OUT_REG, ADIS16201_SCAN_ACC_Y,
			BIT(IIO_CHAN_INFO_CALIBBIAS), 0, 14),
	ADIS_AUX_ADC_CHAN(ADIS16201_AUX_ADC_REG, ADIS16201_SCAN_AUX_ADC, 0, 12),
	ADIS_INCLI_CHAN(X, ADIS16201_XINCL_OUT_REG, ADIS16201_SCAN_INCLI_X,
			BIT(IIO_CHAN_INFO_CALIBBIAS), 0, 14),
	ADIS_INCLI_CHAN(Y, ADIS16201_YINCL_OUT_REG, ADIS16201_SCAN_INCLI_Y,
			BIT(IIO_CHAN_INFO_CALIBBIAS), 0, 14),
	IIO_CHAN_SOFT_TIMESTAMP(7)
पूर्ण;

अटल स्थिर काष्ठा iio_info adis16201_info = अणु
	.पढ़ो_raw = adis16201_पढ़ो_raw,
	.ग_लिखो_raw = adis16201_ग_लिखो_raw,
	.update_scan_mode = adis_update_scan_mode,
पूर्ण;

अटल स्थिर अक्षर * स्थिर adis16201_status_error_msgs[] = अणु
	[ADIS16201_DIAG_STAT_SPI_FAIL_BIT] = "SPI failure",
	[ADIS16201_DIAG_STAT_FLASH_UPT_FAIL_BIT] = "Flash update failed",
	[ADIS16201_DIAG_STAT_POWER_HIGH_BIT] = "Power supply above 3.625V",
	[ADIS16201_DIAG_STAT_POWER_LOW_BIT] = "Power supply below 2.975V",
पूर्ण;

अटल स्थिर काष्ठा adis_समयout adis16201_समयouts = अणु
	.reset_ms = ADIS16201_STARTUP_DELAY_MS,
	.sw_reset_ms = ADIS16201_STARTUP_DELAY_MS,
	.self_test_ms = ADIS16201_STARTUP_DELAY_MS,
पूर्ण;

अटल स्थिर काष्ठा adis_data adis16201_data = अणु
	.पढ़ो_delay = 20,
	.msc_ctrl_reg = ADIS16201_MSC_CTRL_REG,
	.glob_cmd_reg = ADIS16201_GLOB_CMD_REG,
	.diag_stat_reg = ADIS16201_DIAG_STAT_REG,

	.self_test_mask = ADIS16201_MSC_CTRL_SELF_TEST_EN,
	.self_test_reg = ADIS16201_MSC_CTRL_REG,
	.self_test_no_स्वतःclear = true,
	.समयouts = &adis16201_समयouts,

	.status_error_msgs = adis16201_status_error_msgs,
	.status_error_mask = BIT(ADIS16201_DIAG_STAT_SPI_FAIL_BIT) |
		BIT(ADIS16201_DIAG_STAT_FLASH_UPT_FAIL_BIT) |
		BIT(ADIS16201_DIAG_STAT_POWER_HIGH_BIT) |
		BIT(ADIS16201_DIAG_STAT_POWER_LOW_BIT),
पूर्ण;

अटल पूर्णांक adis16201_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा adis *st;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);

	indio_dev->name = spi->dev.driver->name;
	indio_dev->info = &adis16201_info;

	indio_dev->channels = adis16201_channels;
	indio_dev->num_channels = ARRAY_SIZE(adis16201_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = adis_init(st, indio_dev, spi, &adis16201_data);
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

अटल काष्ठा spi_driver adis16201_driver = अणु
	.driver = अणु
		.name = "adis16201",
	पूर्ण,
	.probe = adis16201_probe,
पूर्ण;
module_spi_driver(adis16201_driver);

MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_DESCRIPTION("Analog Devices ADIS16201 Dual-Axis Digital Inclinometer and Accelerometer");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("spi:adis16201");
