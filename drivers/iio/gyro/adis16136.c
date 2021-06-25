<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ADIS16133/ADIS16135/ADIS16136 gyroscope driver
 *
 * Copyright 2012 Analog Devices Inc.
 *   Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/module.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/imu/adis.h>

#समावेश <linux/debugfs.h>

#घोषणा ADIS16136_REG_FLASH_CNT		0x00
#घोषणा ADIS16136_REG_TEMP_OUT		0x02
#घोषणा ADIS16136_REG_GYRO_OUT2		0x04
#घोषणा ADIS16136_REG_GYRO_OUT		0x06
#घोषणा ADIS16136_REG_GYRO_OFF2		0x08
#घोषणा ADIS16136_REG_GYRO_OFF		0x0A
#घोषणा ADIS16136_REG_ALM_MAG1		0x10
#घोषणा ADIS16136_REG_ALM_MAG2		0x12
#घोषणा ADIS16136_REG_ALM_SAMPL1	0x14
#घोषणा ADIS16136_REG_ALM_SAMPL2	0x16
#घोषणा ADIS16136_REG_ALM_CTRL		0x18
#घोषणा ADIS16136_REG_GPIO_CTRL		0x1A
#घोषणा ADIS16136_REG_MSC_CTRL		0x1C
#घोषणा ADIS16136_REG_SMPL_PRD		0x1E
#घोषणा ADIS16136_REG_AVG_CNT		0x20
#घोषणा ADIS16136_REG_DEC_RATE		0x22
#घोषणा ADIS16136_REG_SLP_CTRL		0x24
#घोषणा ADIS16136_REG_DIAG_STAT		0x26
#घोषणा ADIS16136_REG_GLOB_CMD		0x28
#घोषणा ADIS16136_REG_LOT1		0x32
#घोषणा ADIS16136_REG_LOT2		0x34
#घोषणा ADIS16136_REG_LOT3		0x36
#घोषणा ADIS16136_REG_PROD_ID		0x38
#घोषणा ADIS16136_REG_SERIAL_NUM	0x3A

#घोषणा ADIS16136_DIAG_STAT_FLASH_UPDATE_FAIL	2
#घोषणा ADIS16136_DIAG_STAT_SPI_FAIL		3
#घोषणा ADIS16136_DIAG_STAT_SELF_TEST_FAIL	5
#घोषणा ADIS16136_DIAG_STAT_FLASH_CHKSUM_FAIL	6

#घोषणा ADIS16136_MSC_CTRL_MEMORY_TEST BIT(11)
#घोषणा ADIS16136_MSC_CTRL_SELF_TEST BIT(10)

काष्ठा adis16136_chip_info अणु
	अचिन्हित पूर्णांक precision;
	अचिन्हित पूर्णांक fullscale;
	स्थिर काष्ठा adis_data adis_data;
पूर्ण;

काष्ठा adis16136 अणु
	स्थिर काष्ठा adis16136_chip_info *chip_info;

	काष्ठा adis adis;
पूर्ण;

#अगर_घोषित CONFIG_DEBUG_FS

अटल sमाप_प्रकार adis16136_show_serial(काष्ठा file *file,
		अक्षर __user *userbuf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा adis16136 *adis16136 = file->निजी_data;
	uपूर्णांक16_t lot1, lot2, lot3, serial;
	अक्षर buf[20];
	माप_प्रकार len;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg_16(&adis16136->adis, ADIS16136_REG_SERIAL_NUM,
		&serial);
	अगर (ret)
		वापस ret;

	ret = adis_पढ़ो_reg_16(&adis16136->adis, ADIS16136_REG_LOT1, &lot1);
	अगर (ret)
		वापस ret;

	ret = adis_पढ़ो_reg_16(&adis16136->adis, ADIS16136_REG_LOT2, &lot2);
	अगर (ret)
		वापस ret;

	ret = adis_पढ़ो_reg_16(&adis16136->adis, ADIS16136_REG_LOT3, &lot3);
	अगर (ret)
		वापस ret;

	len = snम_लिखो(buf, माप(buf), "%.4x%.4x%.4x-%.4x\n", lot1, lot2,
		lot3, serial);

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations adis16136_serial_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = adis16136_show_serial,
	.llseek = शेष_llseek,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक adis16136_show_product_id(व्योम *arg, u64 *val)
अणु
	काष्ठा adis16136 *adis16136 = arg;
	u16 prod_id;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg_16(&adis16136->adis, ADIS16136_REG_PROD_ID,
		&prod_id);
	अगर (ret)
		वापस ret;

	*val = prod_id;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(adis16136_product_id_fops,
	adis16136_show_product_id, शून्य, "%llu\n");

अटल पूर्णांक adis16136_show_flash_count(व्योम *arg, u64 *val)
अणु
	काष्ठा adis16136 *adis16136 = arg;
	uपूर्णांक16_t flash_count;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg_16(&adis16136->adis, ADIS16136_REG_FLASH_CNT,
		&flash_count);
	अगर (ret)
		वापस ret;

	*val = flash_count;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(adis16136_flash_count_fops,
	adis16136_show_flash_count, शून्य, "%lld\n");

अटल पूर्णांक adis16136_debugfs_init(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा adis16136 *adis16136 = iio_priv(indio_dev);
	काष्ठा dentry *d = iio_get_debugfs_dentry(indio_dev);

	debugfs_create_file_unsafe("serial_number", 0400,
		d, adis16136, &adis16136_serial_fops);
	debugfs_create_file_unsafe("product_id", 0400,
		d, adis16136, &adis16136_product_id_fops);
	debugfs_create_file_unsafe("flash_count", 0400,
		d, adis16136, &adis16136_flash_count_fops);

	वापस 0;
पूर्ण

#अन्यथा

अटल पूर्णांक adis16136_debugfs_init(काष्ठा iio_dev *indio_dev)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक adis16136_set_freq(काष्ठा adis16136 *adis16136, अचिन्हित पूर्णांक freq)
अणु
	अचिन्हित पूर्णांक t;

	t = 32768 / freq;
	अगर (t < 0xf)
		t = 0xf;
	अन्यथा अगर (t > 0xffff)
		t = 0xffff;
	अन्यथा
		t--;

	वापस adis_ग_लिखो_reg_16(&adis16136->adis, ADIS16136_REG_SMPL_PRD, t);
पूर्ण

अटल पूर्णांक __adis16136_get_freq(काष्ठा adis16136 *adis16136, अचिन्हित पूर्णांक *freq)
अणु
	uपूर्णांक16_t t;
	पूर्णांक ret;

	ret = __adis_पढ़ो_reg_16(&adis16136->adis, ADIS16136_REG_SMPL_PRD, &t);
	अगर (ret)
		वापस ret;

	*freq = 32768 / (t + 1);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार adis16136_ग_लिखो_frequency(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा adis16136 *adis16136 = iio_priv(indio_dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 10, &val);
	अगर (ret)
		वापस ret;

	अगर (val == 0)
		वापस -EINVAL;

	ret = adis16136_set_freq(adis16136, val);

	वापस ret ? ret : len;
पूर्ण

अटल sमाप_प्रकार adis16136_पढ़ो_frequency(काष्ठा device *dev,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा adis16136 *adis16136 = iio_priv(indio_dev);
	काष्ठा mutex *slock = &adis16136->adis.state_lock;
	अचिन्हित पूर्णांक freq;
	पूर्णांक ret;

	mutex_lock(slock);
	ret = __adis16136_get_freq(adis16136, &freq);
	mutex_unlock(slock);
	अगर (ret)
		वापस ret;

	वापस प्र_लिखो(buf, "%d\n", freq);
पूर्ण

अटल IIO_DEV_ATTR_SAMP_FREQ(S_IWUSR | S_IRUGO,
				  adis16136_पढ़ो_frequency,
				  adis16136_ग_लिखो_frequency);

अटल स्थिर अचिन्हित adis16136_3db_भागisors[] = अणु
	[0] = 2, /* Special हाल */
	[1] = 6,
	[2] = 12,
	[3] = 25,
	[4] = 50,
	[5] = 100,
	[6] = 200,
	[7] = 200, /* Not a valid setting */
पूर्ण;

अटल पूर्णांक adis16136_set_filter(काष्ठा iio_dev *indio_dev, पूर्णांक val)
अणु
	काष्ठा adis16136 *adis16136 = iio_priv(indio_dev);
	काष्ठा mutex *slock = &adis16136->adis.state_lock;
	अचिन्हित पूर्णांक freq;
	पूर्णांक i, ret;

	mutex_lock(slock);
	ret = __adis16136_get_freq(adis16136, &freq);
	अगर (ret)
		जाओ out_unlock;

	क्रम (i = ARRAY_SIZE(adis16136_3db_भागisors) - 1; i >= 1; i--) अणु
		अगर (freq / adis16136_3db_भागisors[i] >= val)
			अवरोध;
	पूर्ण

	ret = __adis_ग_लिखो_reg_16(&adis16136->adis, ADIS16136_REG_AVG_CNT, i);
out_unlock:
	mutex_unlock(slock);

	वापस ret;
पूर्ण

अटल पूर्णांक adis16136_get_filter(काष्ठा iio_dev *indio_dev, पूर्णांक *val)
अणु
	काष्ठा adis16136 *adis16136 = iio_priv(indio_dev);
	काष्ठा mutex *slock = &adis16136->adis.state_lock;
	अचिन्हित पूर्णांक freq;
	uपूर्णांक16_t val16;
	पूर्णांक ret;

	mutex_lock(slock);

	ret = __adis_पढ़ो_reg_16(&adis16136->adis, ADIS16136_REG_AVG_CNT,
				 &val16);
	अगर (ret)
		जाओ err_unlock;

	ret = __adis16136_get_freq(adis16136, &freq);
	अगर (ret)
		जाओ err_unlock;

	*val = freq / adis16136_3db_भागisors[val16 & 0x07];

err_unlock:
	mutex_unlock(slock);

	वापस ret ? ret : IIO_VAL_INT;
पूर्ण

अटल पूर्णांक adis16136_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	काष्ठा adis16136 *adis16136 = iio_priv(indio_dev);
	uपूर्णांक32_t val32;
	पूर्णांक ret;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस adis_single_conversion(indio_dev, chan, 0, val);
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
			*val = adis16136->chip_info->precision;
			*val2 = (adis16136->chip_info->fullscale << 16);
			वापस IIO_VAL_FRACTIONAL;
		हाल IIO_TEMP:
			*val = 10;
			*val2 = 697000; /* 0.010697 degree Celsius */
			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_CALIBBIAS:
		ret = adis_पढ़ो_reg_32(&adis16136->adis,
			ADIS16136_REG_GYRO_OFF2, &val32);
		अगर (ret)
			वापस ret;

		*val = sign_extend32(val32, 31);

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		वापस adis16136_get_filter(indio_dev, val);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक adis16136_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक val, पूर्णांक val2, दीर्घ info)
अणु
	काष्ठा adis16136 *adis16136 = iio_priv(indio_dev);

	चयन (info) अणु
	हाल IIO_CHAN_INFO_CALIBBIAS:
		वापस adis_ग_लिखो_reg_32(&adis16136->adis,
			ADIS16136_REG_GYRO_OFF2, val);
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		वापस adis16136_set_filter(indio_dev, val);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

क्रमागत अणु
	ADIS16136_SCAN_GYRO,
	ADIS16136_SCAN_TEMP,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec adis16136_channels[] = अणु
	अणु
		.type = IIO_ANGL_VEL,
		.modअगरied = 1,
		.channel2 = IIO_MOD_X,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_CALIBBIAS) |
			BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),

		.address = ADIS16136_REG_GYRO_OUT2,
		.scan_index = ADIS16136_SCAN_GYRO,
		.scan_type = अणु
			.sign = 's',
			.realbits = 32,
			.storagebits = 32,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण, अणु
		.type = IIO_TEMP,
		.indexed = 1,
		.channel = 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE),
		.address = ADIS16136_REG_TEMP_OUT,
		.scan_index = ADIS16136_SCAN_TEMP,
		.scan_type = अणु
			.sign = 's',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(2),
पूर्ण;

अटल काष्ठा attribute *adis16136_attributes[] = अणु
	&iio_dev_attr_sampling_frequency.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group adis16136_attribute_group = अणु
	.attrs = adis16136_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info adis16136_info = अणु
	.attrs = &adis16136_attribute_group,
	.पढ़ो_raw = &adis16136_पढ़ो_raw,
	.ग_लिखो_raw = &adis16136_ग_लिखो_raw,
	.update_scan_mode = adis_update_scan_mode,
	.debugfs_reg_access = adis_debugfs_reg_access,
पूर्ण;

अटल पूर्णांक adis16136_stop_device(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा adis16136 *adis16136 = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = adis_ग_लिखो_reg_16(&adis16136->adis, ADIS16136_REG_SLP_CTRL, 0xff);
	अगर (ret)
		dev_err(&indio_dev->dev,
			"Could not power down device: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक adis16136_initial_setup(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा adis16136 *adis16136 = iio_priv(indio_dev);
	अचिन्हित पूर्णांक device_id;
	uपूर्णांक16_t prod_id;
	पूर्णांक ret;

	ret = adis_initial_startup(&adis16136->adis);
	अगर (ret)
		वापस ret;

	ret = adis_पढ़ो_reg_16(&adis16136->adis, ADIS16136_REG_PROD_ID,
		&prod_id);
	अगर (ret)
		वापस ret;

	ret = माला_पूछो(indio_dev->name, "adis%u\n", &device_id);
	अगर (ret != 1)
		वापस -EINVAL;

	अगर (prod_id != device_id)
		dev_warn(&indio_dev->dev, "Device ID(%u) and product ID(%u) do not match.",
				device_id, prod_id);

	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर adis16136_status_error_msgs[] = अणु
	[ADIS16136_DIAG_STAT_FLASH_UPDATE_FAIL] = "Flash update failed",
	[ADIS16136_DIAG_STAT_SPI_FAIL] = "SPI failure",
	[ADIS16136_DIAG_STAT_SELF_TEST_FAIL] = "Self test error",
	[ADIS16136_DIAG_STAT_FLASH_CHKSUM_FAIL] = "Flash checksum error",
पूर्ण;

#घोषणा ADIS16136_DATA(_समयouts)					\
अणु									\
	.diag_stat_reg = ADIS16136_REG_DIAG_STAT,			\
	.glob_cmd_reg = ADIS16136_REG_GLOB_CMD,				\
	.msc_ctrl_reg = ADIS16136_REG_MSC_CTRL,				\
	.self_test_reg = ADIS16136_REG_MSC_CTRL,			\
	.self_test_mask = ADIS16136_MSC_CTRL_SELF_TEST,			\
	.पढ़ो_delay = 10,						\
	.ग_लिखो_delay = 10,						\
	.status_error_msgs = adis16136_status_error_msgs,		\
	.status_error_mask = BIT(ADIS16136_DIAG_STAT_FLASH_UPDATE_FAIL) |	\
		BIT(ADIS16136_DIAG_STAT_SPI_FAIL) |			\
		BIT(ADIS16136_DIAG_STAT_SELF_TEST_FAIL) |		\
		BIT(ADIS16136_DIAG_STAT_FLASH_CHKSUM_FAIL),		\
	.समयouts = (_समयouts),					\
पूर्ण

क्रमागत adis16136_id अणु
	ID_ADIS16133,
	ID_ADIS16135,
	ID_ADIS16136,
	ID_ADIS16137,
पूर्ण;

अटल स्थिर काष्ठा adis_समयout adis16133_समयouts = अणु
	.reset_ms = 75,
	.sw_reset_ms = 75,
	.self_test_ms = 50,
पूर्ण;

अटल स्थिर काष्ठा adis_समयout adis16136_समयouts = अणु
	.reset_ms = 128,
	.sw_reset_ms = 75,
	.self_test_ms = 245,
पूर्ण;

अटल स्थिर काष्ठा adis16136_chip_info adis16136_chip_info[] = अणु
	[ID_ADIS16133] = अणु
		.precision = IIO_DEGREE_TO_RAD(1200),
		.fullscale = 24000,
		.adis_data = ADIS16136_DATA(&adis16133_समयouts),
	पूर्ण,
	[ID_ADIS16135] = अणु
		.precision = IIO_DEGREE_TO_RAD(300),
		.fullscale = 24000,
		.adis_data = ADIS16136_DATA(&adis16133_समयouts),
	पूर्ण,
	[ID_ADIS16136] = अणु
		.precision = IIO_DEGREE_TO_RAD(450),
		.fullscale = 24623,
		.adis_data = ADIS16136_DATA(&adis16136_समयouts),
	पूर्ण,
	[ID_ADIS16137] = अणु
		.precision = IIO_DEGREE_TO_RAD(1000),
		.fullscale = 24609,
		.adis_data = ADIS16136_DATA(&adis16136_समयouts),
	पूर्ण,
पूर्ण;

अटल व्योम adis16136_stop(व्योम *data)
अणु
	adis16136_stop_device(data);
पूर्ण

अटल पूर्णांक adis16136_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	काष्ठा adis16136 *adis16136;
	काष्ठा iio_dev *indio_dev;
	स्थिर काष्ठा adis_data *adis16136_data;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*adis16136));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	spi_set_drvdata(spi, indio_dev);

	adis16136 = iio_priv(indio_dev);

	adis16136->chip_info = &adis16136_chip_info[id->driver_data];
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->channels = adis16136_channels;
	indio_dev->num_channels = ARRAY_SIZE(adis16136_channels);
	indio_dev->info = &adis16136_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	adis16136_data = &adis16136->chip_info->adis_data;

	ret = adis_init(&adis16136->adis, indio_dev, spi, adis16136_data);
	अगर (ret)
		वापस ret;

	ret = devm_adis_setup_buffer_and_trigger(&adis16136->adis, indio_dev, शून्य);
	अगर (ret)
		वापस ret;

	ret = adis16136_initial_setup(indio_dev);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(&spi->dev, adis16136_stop, indio_dev);
	अगर (ret)
		वापस ret;

	ret = devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
	अगर (ret)
		वापस ret;

	adis16136_debugfs_init(indio_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id adis16136_ids[] = अणु
	अणु "adis16133", ID_ADIS16133 पूर्ण,
	अणु "adis16135", ID_ADIS16135 पूर्ण,
	अणु "adis16136", ID_ADIS16136 पूर्ण,
	अणु "adis16137", ID_ADIS16137 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, adis16136_ids);

अटल काष्ठा spi_driver adis16136_driver = अणु
	.driver = अणु
		.name = "adis16136",
	पूर्ण,
	.id_table = adis16136_ids,
	.probe = adis16136_probe,
पूर्ण;
module_spi_driver(adis16136_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Analog Devices ADIS16133/ADIS16135/ADIS16136 gyroscope driver");
MODULE_LICENSE("GPL v2");
