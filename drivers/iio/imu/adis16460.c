<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ADIS16460 IMU driver
 *
 * Copyright 2019 Analog Devices Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/imu/adis.h>

#समावेश <linux/debugfs.h>

#घोषणा ADIS16460_REG_FLASH_CNT		0x00
#घोषणा ADIS16460_REG_DIAG_STAT		0x02
#घोषणा ADIS16460_REG_X_GYRO_LOW	0x04
#घोषणा ADIS16460_REG_X_GYRO_OUT	0x06
#घोषणा ADIS16460_REG_Y_GYRO_LOW	0x08
#घोषणा ADIS16460_REG_Y_GYRO_OUT	0x0A
#घोषणा ADIS16460_REG_Z_GYRO_LOW	0x0C
#घोषणा ADIS16460_REG_Z_GYRO_OUT	0x0E
#घोषणा ADIS16460_REG_X_ACCL_LOW	0x10
#घोषणा ADIS16460_REG_X_ACCL_OUT	0x12
#घोषणा ADIS16460_REG_Y_ACCL_LOW	0x14
#घोषणा ADIS16460_REG_Y_ACCL_OUT	0x16
#घोषणा ADIS16460_REG_Z_ACCL_LOW	0x18
#घोषणा ADIS16460_REG_Z_ACCL_OUT	0x1A
#घोषणा ADIS16460_REG_SMPL_CNTR		0x1C
#घोषणा ADIS16460_REG_TEMP_OUT		0x1E
#घोषणा ADIS16460_REG_X_DELT_ANG	0x24
#घोषणा ADIS16460_REG_Y_DELT_ANG	0x26
#घोषणा ADIS16460_REG_Z_DELT_ANG	0x28
#घोषणा ADIS16460_REG_X_DELT_VEL	0x2A
#घोषणा ADIS16460_REG_Y_DELT_VEL	0x2C
#घोषणा ADIS16460_REG_Z_DELT_VEL	0x2E
#घोषणा ADIS16460_REG_MSC_CTRL		0x32
#घोषणा ADIS16460_REG_SYNC_SCAL		0x34
#घोषणा ADIS16460_REG_DEC_RATE		0x36
#घोषणा ADIS16460_REG_FLTR_CTRL		0x38
#घोषणा ADIS16460_REG_GLOB_CMD		0x3E
#घोषणा ADIS16460_REG_X_GYRO_OFF	0x40
#घोषणा ADIS16460_REG_Y_GYRO_OFF	0x42
#घोषणा ADIS16460_REG_Z_GYRO_OFF	0x44
#घोषणा ADIS16460_REG_X_ACCL_OFF	0x46
#घोषणा ADIS16460_REG_Y_ACCL_OFF	0x48
#घोषणा ADIS16460_REG_Z_ACCL_OFF	0x4A
#घोषणा ADIS16460_REG_LOT_ID1		0x52
#घोषणा ADIS16460_REG_LOT_ID2		0x54
#घोषणा ADIS16460_REG_PROD_ID		0x56
#घोषणा ADIS16460_REG_SERIAL_NUM	0x58
#घोषणा ADIS16460_REG_CAL_SGNTR		0x60
#घोषणा ADIS16460_REG_CAL_CRC		0x62
#घोषणा ADIS16460_REG_CODE_SGNTR	0x64
#घोषणा ADIS16460_REG_CODE_CRC		0x66

काष्ठा adis16460_chip_info अणु
	अचिन्हित पूर्णांक num_channels;
	स्थिर काष्ठा iio_chan_spec *channels;
	अचिन्हित पूर्णांक gyro_max_val;
	अचिन्हित पूर्णांक gyro_max_scale;
	अचिन्हित पूर्णांक accel_max_val;
	अचिन्हित पूर्णांक accel_max_scale;
पूर्ण;

काष्ठा adis16460 अणु
	स्थिर काष्ठा adis16460_chip_info *chip_info;
	काष्ठा adis adis;
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS

अटल पूर्णांक adis16460_show_serial_number(व्योम *arg, u64 *val)
अणु
	काष्ठा adis16460 *adis16460 = arg;
	u16 serial;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg_16(&adis16460->adis, ADIS16460_REG_SERIAL_NUM,
		&serial);
	अगर (ret)
		वापस ret;

	*val = serial;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(adis16460_serial_number_fops,
		adis16460_show_serial_number, शून्य, "0x%.4llx\n");

अटल पूर्णांक adis16460_show_product_id(व्योम *arg, u64 *val)
अणु
	काष्ठा adis16460 *adis16460 = arg;
	u16 prod_id;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg_16(&adis16460->adis, ADIS16460_REG_PROD_ID,
		&prod_id);
	अगर (ret)
		वापस ret;

	*val = prod_id;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(adis16460_product_id_fops,
		adis16460_show_product_id, शून्य, "%llu\n");

अटल पूर्णांक adis16460_show_flash_count(व्योम *arg, u64 *val)
अणु
	काष्ठा adis16460 *adis16460 = arg;
	u32 flash_count;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg_32(&adis16460->adis, ADIS16460_REG_FLASH_CNT,
		&flash_count);
	अगर (ret)
		वापस ret;

	*val = flash_count;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(adis16460_flash_count_fops,
		adis16460_show_flash_count, शून्य, "%lld\n");

अटल पूर्णांक adis16460_debugfs_init(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा adis16460 *adis16460 = iio_priv(indio_dev);
	काष्ठा dentry *d = iio_get_debugfs_dentry(indio_dev);

	debugfs_create_file_unsafe("serial_number", 0400,
			d, adis16460, &adis16460_serial_number_fops);
	debugfs_create_file_unsafe("product_id", 0400,
			d, adis16460, &adis16460_product_id_fops);
	debugfs_create_file_unsafe("flash_count", 0400,
			d, adis16460, &adis16460_flash_count_fops);

	वापस 0;
पूर्ण

#अन्यथा

अटल पूर्णांक adis16460_debugfs_init(काष्ठा iio_dev *indio_dev)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक adis16460_set_freq(काष्ठा iio_dev *indio_dev, पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा adis16460 *st = iio_priv(indio_dev);
	पूर्णांक t;

	t =  val * 1000 + val2 / 1000;
	अगर (t <= 0)
		वापस -EINVAL;

	t = 2048000 / t;
	अगर (t > 2048)
		t = 2048;

	अगर (t != 0)
		t--;

	वापस adis_ग_लिखो_reg_16(&st->adis, ADIS16460_REG_DEC_RATE, t);
पूर्ण

अटल पूर्णांक adis16460_get_freq(काष्ठा iio_dev *indio_dev, पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा adis16460 *st = iio_priv(indio_dev);
	uपूर्णांक16_t t;
	पूर्णांक ret;
	अचिन्हित पूर्णांक freq;

	ret = adis_पढ़ो_reg_16(&st->adis, ADIS16460_REG_DEC_RATE, &t);
	अगर (ret)
		वापस ret;

	freq = 2048000 / (t + 1);
	*val = freq / 1000;
	*val2 = (freq % 1000) * 1000;

	वापस IIO_VAL_INT_PLUS_MICRO;
पूर्ण

अटल पूर्णांक adis16460_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	काष्ठा adis16460 *st = iio_priv(indio_dev);

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस adis_single_conversion(indio_dev, chan, 0, val);
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
			*val = st->chip_info->gyro_max_scale;
			*val2 = st->chip_info->gyro_max_val;
			वापस IIO_VAL_FRACTIONAL;
		हाल IIO_ACCEL:
			*val = st->chip_info->accel_max_scale;
			*val2 = st->chip_info->accel_max_val;
			वापस IIO_VAL_FRACTIONAL;
		हाल IIO_TEMP:
			*val = 50; /* 50 milli degrees Celsius/LSB */
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_OFFSET:
		*val = 500; /* 25 degrees Celsius = 0x0000 */
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस adis16460_get_freq(indio_dev, val, val2);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक adis16460_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक val, पूर्णांक val2, दीर्घ info)
अणु
	चयन (info) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस adis16460_set_freq(indio_dev, val, val2);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

क्रमागत अणु
	ADIS16460_SCAN_GYRO_X,
	ADIS16460_SCAN_GYRO_Y,
	ADIS16460_SCAN_GYRO_Z,
	ADIS16460_SCAN_ACCEL_X,
	ADIS16460_SCAN_ACCEL_Y,
	ADIS16460_SCAN_ACCEL_Z,
	ADIS16460_SCAN_TEMP,
पूर्ण;

#घोषणा ADIS16460_MOD_CHANNEL(_type, _mod, _address, _si, _bits) \
	अणु \
		.type = (_type), \
		.modअगरied = 1, \
		.channel2 = (_mod), \
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
		.address = (_address), \
		.scan_index = (_si), \
		.scan_type = अणु \
			.sign = 's', \
			.realbits = (_bits), \
			.storagebits = (_bits), \
			.endianness = IIO_BE, \
		पूर्ण, \
	पूर्ण

#घोषणा ADIS16460_GYRO_CHANNEL(_mod) \
	ADIS16460_MOD_CHANNEL(IIO_ANGL_VEL, IIO_MOD_ ## _mod, \
	ADIS16460_REG_ ## _mod ## _GYRO_LOW, ADIS16460_SCAN_GYRO_ ## _mod, \
	32)

#घोषणा ADIS16460_ACCEL_CHANNEL(_mod) \
	ADIS16460_MOD_CHANNEL(IIO_ACCEL, IIO_MOD_ ## _mod, \
	ADIS16460_REG_ ## _mod ## _ACCL_LOW, ADIS16460_SCAN_ACCEL_ ## _mod, \
	32)

#घोषणा ADIS16460_TEMP_CHANNEL() अणु \
		.type = IIO_TEMP, \
		.indexed = 1, \
		.channel = 0, \
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
			BIT(IIO_CHAN_INFO_SCALE) | \
			BIT(IIO_CHAN_INFO_OFFSET), \
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
		.address = ADIS16460_REG_TEMP_OUT, \
		.scan_index = ADIS16460_SCAN_TEMP, \
		.scan_type = अणु \
			.sign = 's', \
			.realbits = 16, \
			.storagebits = 16, \
			.endianness = IIO_BE, \
		पूर्ण, \
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec adis16460_channels[] = अणु
	ADIS16460_GYRO_CHANNEL(X),
	ADIS16460_GYRO_CHANNEL(Y),
	ADIS16460_GYRO_CHANNEL(Z),
	ADIS16460_ACCEL_CHANNEL(X),
	ADIS16460_ACCEL_CHANNEL(Y),
	ADIS16460_ACCEL_CHANNEL(Z),
	ADIS16460_TEMP_CHANNEL(),
	IIO_CHAN_SOFT_TIMESTAMP(7)
पूर्ण;

अटल स्थिर काष्ठा adis16460_chip_info adis16460_chip_info = अणु
	.channels = adis16460_channels,
	.num_channels = ARRAY_SIZE(adis16460_channels),
	/*
	 * storing the value in rad/degree and the scale in degree
	 * gives us the result in rad and better precession than
	 * storing the scale directly in rad.
	 */
	.gyro_max_val = IIO_RAD_TO_DEGREE(200 << 16),
	.gyro_max_scale = 1,
	.accel_max_val = IIO_M_S_2_TO_G(20000 << 16),
	.accel_max_scale = 5,
पूर्ण;

अटल स्थिर काष्ठा iio_info adis16460_info = अणु
	.पढ़ो_raw = &adis16460_पढ़ो_raw,
	.ग_लिखो_raw = &adis16460_ग_लिखो_raw,
	.update_scan_mode = adis_update_scan_mode,
	.debugfs_reg_access = adis_debugfs_reg_access,
पूर्ण;

अटल पूर्णांक adis16460_enable_irq(काष्ठा adis *adis, bool enable)
अणु
	/*
	 * There is no way to gate the data-पढ़ोy संकेत पूर्णांकernally inside the
	 * ADIS16460 :(
	 */
	अगर (enable)
		enable_irq(adis->spi->irq);
	अन्यथा
		disable_irq(adis->spi->irq);

	वापस 0;
पूर्ण

#घोषणा ADIS16460_DIAG_STAT_IN_CLK_OOS	7
#घोषणा ADIS16460_DIAG_STAT_FLASH_MEM	6
#घोषणा ADIS16460_DIAG_STAT_SELF_TEST	5
#घोषणा ADIS16460_DIAG_STAT_OVERRANGE	4
#घोषणा ADIS16460_DIAG_STAT_SPI_COMM	3
#घोषणा ADIS16460_DIAG_STAT_FLASH_UPT	2

अटल स्थिर अक्षर * स्थिर adis16460_status_error_msgs[] = अणु
	[ADIS16460_DIAG_STAT_IN_CLK_OOS] = "Input clock out of sync",
	[ADIS16460_DIAG_STAT_FLASH_MEM] = "Flash memory failure",
	[ADIS16460_DIAG_STAT_SELF_TEST] = "Self test diagnostic failure",
	[ADIS16460_DIAG_STAT_OVERRANGE] = "Sensor overrange",
	[ADIS16460_DIAG_STAT_SPI_COMM] = "SPI communication failure",
	[ADIS16460_DIAG_STAT_FLASH_UPT] = "Flash update failure",
पूर्ण;

अटल स्थिर काष्ठा adis_समयout adis16460_समयouts = अणु
	.reset_ms = 225,
	.sw_reset_ms = 225,
	.self_test_ms = 10,
पूर्ण;

अटल स्थिर काष्ठा adis_data adis16460_data = अणु
	.diag_stat_reg = ADIS16460_REG_DIAG_STAT,
	.glob_cmd_reg = ADIS16460_REG_GLOB_CMD,
	.prod_id_reg = ADIS16460_REG_PROD_ID,
	.prod_id = 16460,
	.self_test_mask = BIT(2),
	.self_test_reg = ADIS16460_REG_GLOB_CMD,
	.has_paging = false,
	.पढ़ो_delay = 5,
	.ग_लिखो_delay = 5,
	.cs_change_delay = 16,
	.status_error_msgs = adis16460_status_error_msgs,
	.status_error_mask = BIT(ADIS16460_DIAG_STAT_IN_CLK_OOS) |
		BIT(ADIS16460_DIAG_STAT_FLASH_MEM) |
		BIT(ADIS16460_DIAG_STAT_SELF_TEST) |
		BIT(ADIS16460_DIAG_STAT_OVERRANGE) |
		BIT(ADIS16460_DIAG_STAT_SPI_COMM) |
		BIT(ADIS16460_DIAG_STAT_FLASH_UPT),
	.enable_irq = adis16460_enable_irq,
	.समयouts = &adis16460_समयouts,
पूर्ण;

अटल पूर्णांक adis16460_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा adis16460 *st;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	spi_set_drvdata(spi, indio_dev);

	st = iio_priv(indio_dev);

	st->chip_info = &adis16460_chip_info;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->channels = st->chip_info->channels;
	indio_dev->num_channels = st->chip_info->num_channels;
	indio_dev->info = &adis16460_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = adis_init(&st->adis, indio_dev, spi, &adis16460_data);
	अगर (ret)
		वापस ret;

	/* We cannot mask the पूर्णांकerrupt, so ensure it isn't स्वतः enabled */
	st->adis.irq_flag |= IRQF_NO_AUTOEN;
	ret = devm_adis_setup_buffer_and_trigger(&st->adis, indio_dev, शून्य);
	अगर (ret)
		वापस ret;

	ret = __adis_initial_startup(&st->adis);
	अगर (ret)
		वापस ret;

	ret = devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
	अगर (ret)
		वापस ret;

	adis16460_debugfs_init(indio_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id adis16460_ids[] = अणु
	अणु "adis16460", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, adis16460_ids);

अटल स्थिर काष्ठा of_device_id adis16460_of_match[] = अणु
	अणु .compatible = "adi,adis16460" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, adis16460_of_match);

अटल काष्ठा spi_driver adis16460_driver = अणु
	.driver = अणु
		.name = "adis16460",
		.of_match_table = adis16460_of_match,
	पूर्ण,
	.id_table = adis16460_ids,
	.probe = adis16460_probe,
पूर्ण;
module_spi_driver(adis16460_driver);

MODULE_AUTHOR("Dragos Bogdan <dragos.bogdan@analog.com>");
MODULE_DESCRIPTION("Analog Devices ADIS16460 IMU driver");
MODULE_LICENSE("GPL");
