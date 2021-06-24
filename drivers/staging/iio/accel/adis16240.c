<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ADIS16240 Programmable Impact Sensor and Recorder driver
 *
 * Copyright 2010 Analog Devices Inc.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/imu/adis.h>

#घोषणा ADIS16240_STARTUP_DELAY	220 /* ms */

/* Flash memory ग_लिखो count */
#घोषणा ADIS16240_FLASH_CNT      0x00

/* Output, घातer supply */
#घोषणा ADIS16240_SUPPLY_OUT     0x02

/* Output, x-axis accelerometer */
#घोषणा ADIS16240_XACCL_OUT      0x04

/* Output, y-axis accelerometer */
#घोषणा ADIS16240_YACCL_OUT      0x06

/* Output, z-axis accelerometer */
#घोषणा ADIS16240_ZACCL_OUT      0x08

/* Output, auxiliary ADC input */
#घोषणा ADIS16240_AUX_ADC        0x0A

/* Output, temperature */
#घोषणा ADIS16240_TEMP_OUT       0x0C

/* Output, x-axis acceleration peak */
#घोषणा ADIS16240_XPEAK_OUT      0x0E

/* Output, y-axis acceleration peak */
#घोषणा ADIS16240_YPEAK_OUT      0x10

/* Output, z-axis acceleration peak */
#घोषणा ADIS16240_ZPEAK_OUT      0x12

/* Output, sum-of-squares acceleration peak */
#घोषणा ADIS16240_XYZPEAK_OUT    0x14

/* Output, Capture Buffer 1, X and Y acceleration */
#घोषणा ADIS16240_CAPT_BUF1      0x16

/* Output, Capture Buffer 2, Z acceleration */
#घोषणा ADIS16240_CAPT_BUF2      0x18

/* Diagnostic, error flags */
#घोषणा ADIS16240_DIAG_STAT      0x1A

/* Diagnostic, event counter */
#घोषणा ADIS16240_EVNT_CNTR      0x1C

/* Diagnostic, check sum value from firmware test */
#घोषणा ADIS16240_CHK_SUM        0x1E

/* Calibration, x-axis acceleration offset adjusपंचांगent */
#घोषणा ADIS16240_XACCL_OFF      0x20

/* Calibration, y-axis acceleration offset adjusपंचांगent */
#घोषणा ADIS16240_YACCL_OFF      0x22

/* Calibration, z-axis acceleration offset adjusपंचांगent */
#घोषणा ADIS16240_ZACCL_OFF      0x24

/* Clock, hour and minute */
#घोषणा ADIS16240_CLK_TIME       0x2E

/* Clock, month and day */
#घोषणा ADIS16240_CLK_DATE       0x30

/* Clock, year */
#घोषणा ADIS16240_CLK_YEAR       0x32

/* Wake-up setting, hour and minute */
#घोषणा ADIS16240_WAKE_TIME      0x34

/* Wake-up setting, month and day */
#घोषणा ADIS16240_WAKE_DATE      0x36

/* Alarm 1 amplitude threshold */
#घोषणा ADIS16240_ALM_MAG1       0x38

/* Alarm 2 amplitude threshold */
#घोषणा ADIS16240_ALM_MAG2       0x3A

/* Alarm control */
#घोषणा ADIS16240_ALM_CTRL       0x3C

/* Capture, बाह्यal trigger control */
#घोषणा ADIS16240_XTRIG_CTRL     0x3E

/* Capture, address poपूर्णांकer */
#घोषणा ADIS16240_CAPT_PNTR      0x40

/* Capture, configuration and control */
#घोषणा ADIS16240_CAPT_CTRL      0x42

/* General-purpose digital input/output control */
#घोषणा ADIS16240_GPIO_CTRL      0x44

/* Miscellaneous control */
#घोषणा ADIS16240_MSC_CTRL       0x46

/* Internal sample period (rate) control */
#घोषणा ADIS16240_SMPL_PRD       0x48

/* System command */
#घोषणा ADIS16240_GLOB_CMD       0x4A

/* MSC_CTRL */

/* Enables sum-of-squares output (XYZPEAK_OUT) */
#घोषणा ADIS16240_MSC_CTRL_XYZPEAK_OUT_EN	BIT(15)

/* Enables peak tracking output (XPEAK_OUT, YPEAK_OUT, and ZPEAK_OUT) */
#घोषणा ADIS16240_MSC_CTRL_X_Y_ZPEAK_OUT_EN	BIT(14)

/* Self-test enable: 1 = apply electroअटल क्रमce, 0 = disabled */
#घोषणा ADIS16240_MSC_CTRL_SELF_TEST_EN	        BIT(8)

/* Data-पढ़ोy enable: 1 = enabled, 0 = disabled */
#घोषणा ADIS16240_MSC_CTRL_DATA_RDY_EN	        BIT(2)

/* Data-पढ़ोy polarity: 1 = active high, 0 = active low */
#घोषणा ADIS16240_MSC_CTRL_ACTIVE_HIGH	        BIT(1)

/* Data-पढ़ोy line selection: 1 = DIO2, 0 = DIO1 */
#घोषणा ADIS16240_MSC_CTRL_DATA_RDY_DIO2	BIT(0)

/* DIAG_STAT */

/* Alarm 2 status: 1 = alarm active, 0 = alarm inactive */
#घोषणा ADIS16240_DIAG_STAT_ALARM2      BIT(9)

/* Alarm 1 status: 1 = alarm active, 0 = alarm inactive */
#घोषणा ADIS16240_DIAG_STAT_ALARM1      BIT(8)

/* Capture buffer full: 1 = capture buffer is full */
#घोषणा ADIS16240_DIAG_STAT_CPT_BUF_FUL BIT(7)

/* Flash test, checksum flag: 1 = mismatch, 0 = match */
#घोषणा ADIS16240_DIAG_STAT_CHKSUM      BIT(6)

/* Power-on, self-test flag: 1 = failure, 0 = pass */
#घोषणा ADIS16240_DIAG_STAT_PWRON_FAIL_BIT  5

/* Power-on self-test: 1 = in-progress, 0 = complete */
#घोषणा ADIS16240_DIAG_STAT_PWRON_BUSY  BIT(4)

/* SPI communications failure */
#घोषणा ADIS16240_DIAG_STAT_SPI_FAIL_BIT	3

/* Flash update failure */
#घोषणा ADIS16240_DIAG_STAT_FLASH_UPT_BIT	2

/* Power supply above 3.625 V */
#घोषणा ADIS16240_DIAG_STAT_POWER_HIGH_BIT	1

 /* Power supply below 2.225 V */
#घोषणा ADIS16240_DIAG_STAT_POWER_LOW_BIT	0

/* GLOB_CMD */

#घोषणा ADIS16240_GLOB_CMD_RESUME	BIT(8)
#घोषणा ADIS16240_GLOB_CMD_SW_RESET	BIT(7)
#घोषणा ADIS16240_GLOB_CMD_STANDBY	BIT(2)

#घोषणा ADIS16240_ERROR_ACTIVE          BIT(14)

/* At the moment triggers are only used क्रम ring buffer
 * filling. This may change!
 */

क्रमागत adis16240_scan अणु
	ADIS16240_SCAN_ACC_X,
	ADIS16240_SCAN_ACC_Y,
	ADIS16240_SCAN_ACC_Z,
	ADIS16240_SCAN_SUPPLY,
	ADIS16240_SCAN_AUX_ADC,
	ADIS16240_SCAN_TEMP,
पूर्ण;

अटल sमाप_प्रकार adis16240_spi_पढ़ो_चिन्हित(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf,
					 अचिन्हित पूर्णांक bits)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा adis *st = iio_priv(indio_dev);
	पूर्णांक ret;
	s16 val = 0;
	अचिन्हित पूर्णांक shअगरt = 16 - bits;
	काष्ठा iio_dev_attr *this_attr = to_iio_dev_attr(attr);

	ret = adis_पढ़ो_reg_16(st,
			       this_attr->address, (u16 *)&val);
	अगर (ret)
		वापस ret;

	अगर (val & ADIS16240_ERROR_ACTIVE)
		adis_check_status(st);

	val = (s16)(val << shअगरt) >> shअगरt;
	वापस प्र_लिखो(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार adis16240_पढ़ो_12bit_चिन्हित(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	वापस adis16240_spi_पढ़ो_चिन्हित(dev, attr, buf, 12);
पूर्ण

अटल IIO_DEVICE_ATTR(in_accel_xyz_squared_peak_raw, 0444,
		       adis16240_पढ़ो_12bit_चिन्हित, शून्य,
		       ADIS16240_XYZPEAK_OUT);

अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL("4096");

अटल स्थिर u8 adis16240_addresses[][2] = अणु
	[ADIS16240_SCAN_ACC_X] = अणु ADIS16240_XACCL_OFF, ADIS16240_XPEAK_OUT पूर्ण,
	[ADIS16240_SCAN_ACC_Y] = अणु ADIS16240_YACCL_OFF, ADIS16240_YPEAK_OUT पूर्ण,
	[ADIS16240_SCAN_ACC_Z] = अणु ADIS16240_ZACCL_OFF, ADIS16240_ZPEAK_OUT पूर्ण,
पूर्ण;

अटल पूर्णांक adis16240_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
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
				ADIS16240_ERROR_ACTIVE, val);
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_VOLTAGE:
			अगर (chan->channel == 0) अणु
				*val = 4;
				*val2 = 880000; /* 4.88 mV */
				वापस IIO_VAL_INT_PLUS_MICRO;
			पूर्ण
			वापस -EINVAL;
		हाल IIO_TEMP:
			*val = 244; /* 0.244 C */
			*val2 = 0;
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_ACCEL:
			*val = 0;
			*val2 = IIO_G_TO_M_S_2(51400); /* 51.4 mg */
			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_PEAK_SCALE:
		*val = 0;
		*val2 = IIO_G_TO_M_S_2(51400); /* 51.4 mg */
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_OFFSET:
		*val = 25000 / 244 - 0x133; /* 25 C = 0x133 */
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		addr = adis16240_addresses[chan->scan_index][0];
		ret = adis_पढ़ो_reg_16(st, addr, &val16);
		अगर (ret)
			वापस ret;
		*val = sign_extend32(val16, 9);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_PEAK:
		addr = adis16240_addresses[chan->scan_index][1];
		ret = adis_पढ़ो_reg_16(st, addr, &val16);
		अगर (ret)
			वापस ret;
		*val = sign_extend32(val16, 9);
		वापस IIO_VAL_INT;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक adis16240_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val,
			       पूर्णांक val2,
			       दीर्घ mask)
अणु
	काष्ठा adis *st = iio_priv(indio_dev);
	u8 addr;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_CALIBBIAS:
		addr = adis16240_addresses[chan->scan_index][0];
		वापस adis_ग_लिखो_reg_16(st, addr, val & GENMASK(9, 0));
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec adis16240_channels[] = अणु
	ADIS_SUPPLY_CHAN(ADIS16240_SUPPLY_OUT, ADIS16240_SCAN_SUPPLY, 0, 10),
	ADIS_AUX_ADC_CHAN(ADIS16240_AUX_ADC, ADIS16240_SCAN_AUX_ADC, 0, 10),
	ADIS_ACCEL_CHAN(X, ADIS16240_XACCL_OUT, ADIS16240_SCAN_ACC_X,
			BIT(IIO_CHAN_INFO_CALIBBIAS) | BIT(IIO_CHAN_INFO_PEAK),
			0, 10),
	ADIS_ACCEL_CHAN(Y, ADIS16240_YACCL_OUT, ADIS16240_SCAN_ACC_Y,
			BIT(IIO_CHAN_INFO_CALIBBIAS) | BIT(IIO_CHAN_INFO_PEAK),
			0, 10),
	ADIS_ACCEL_CHAN(Z, ADIS16240_ZACCL_OUT, ADIS16240_SCAN_ACC_Z,
			BIT(IIO_CHAN_INFO_CALIBBIAS) | BIT(IIO_CHAN_INFO_PEAK),
			0, 10),
	ADIS_TEMP_CHAN(ADIS16240_TEMP_OUT, ADIS16240_SCAN_TEMP, 0, 10),
	IIO_CHAN_SOFT_TIMESTAMP(6)
पूर्ण;

अटल काष्ठा attribute *adis16240_attributes[] = अणु
	&iio_dev_attr_in_accel_xyz_squared_peak_raw.dev_attr.attr,
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group adis16240_attribute_group = अणु
	.attrs = adis16240_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info adis16240_info = अणु
	.attrs = &adis16240_attribute_group,
	.पढ़ो_raw = adis16240_पढ़ो_raw,
	.ग_लिखो_raw = adis16240_ग_लिखो_raw,
	.update_scan_mode = adis_update_scan_mode,
पूर्ण;

अटल स्थिर अक्षर * स्थिर adis16240_status_error_msgs[] = अणु
	[ADIS16240_DIAG_STAT_PWRON_FAIL_BIT] = "Power on, self-test failed",
	[ADIS16240_DIAG_STAT_SPI_FAIL_BIT] = "SPI failure",
	[ADIS16240_DIAG_STAT_FLASH_UPT_BIT] = "Flash update failed",
	[ADIS16240_DIAG_STAT_POWER_HIGH_BIT] = "Power supply above 3.625V",
	[ADIS16240_DIAG_STAT_POWER_LOW_BIT] = "Power supply below 2.225V",
पूर्ण;

अटल स्थिर काष्ठा adis_समयout adis16240_समयouts = अणु
	.reset_ms = ADIS16240_STARTUP_DELAY,
	.sw_reset_ms = ADIS16240_STARTUP_DELAY,
	.self_test_ms = ADIS16240_STARTUP_DELAY,
पूर्ण;

अटल स्थिर काष्ठा adis_data adis16240_data = अणु
	.ग_लिखो_delay = 35,
	.पढ़ो_delay = 35,
	.msc_ctrl_reg = ADIS16240_MSC_CTRL,
	.glob_cmd_reg = ADIS16240_GLOB_CMD,
	.diag_stat_reg = ADIS16240_DIAG_STAT,

	.self_test_mask = ADIS16240_MSC_CTRL_SELF_TEST_EN,
	.self_test_reg = ADIS16240_MSC_CTRL,
	.self_test_no_स्वतःclear = true,
	.समयouts = &adis16240_समयouts,

	.status_error_msgs = adis16240_status_error_msgs,
	.status_error_mask = BIT(ADIS16240_DIAG_STAT_PWRON_FAIL_BIT) |
		BIT(ADIS16240_DIAG_STAT_SPI_FAIL_BIT) |
		BIT(ADIS16240_DIAG_STAT_FLASH_UPT_BIT) |
		BIT(ADIS16240_DIAG_STAT_POWER_HIGH_BIT) |
		BIT(ADIS16240_DIAG_STAT_POWER_LOW_BIT),
पूर्ण;

अटल पूर्णांक adis16240_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
	काष्ठा adis *st;
	काष्ठा iio_dev *indio_dev;

	/* setup the industrialio driver allocated elements */
	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;
	st = iio_priv(indio_dev);
	/* this is only used क्रम removal purposes */
	spi_set_drvdata(spi, indio_dev);

	indio_dev->name = spi->dev.driver->name;
	indio_dev->info = &adis16240_info;
	indio_dev->channels = adis16240_channels;
	indio_dev->num_channels = ARRAY_SIZE(adis16240_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	spi->mode = SPI_MODE_3;
	ret = spi_setup(spi);
	अगर (ret) अणु
		dev_err(&spi->dev, "spi_setup failed!\n");
		वापस ret;
	पूर्ण

	ret = adis_init(st, indio_dev, spi, &adis16240_data);
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

अटल स्थिर काष्ठा of_device_id adis16240_of_match[] = अणु
	अणु .compatible = "adi,adis16240" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, adis16240_of_match);

अटल काष्ठा spi_driver adis16240_driver = अणु
	.driver = अणु
		.name = "adis16240",
		.of_match_table = adis16240_of_match,
	पूर्ण,
	.probe = adis16240_probe,
पूर्ण;
module_spi_driver(adis16240_driver);

MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_DESCRIPTION("Analog Devices Programmable Impact Sensor and Recorder");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("spi:adis16240");
