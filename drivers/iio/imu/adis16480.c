<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ADIS16480 and similar IMUs driver
 *
 * Copyright 2012 Analog Devices Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/गणित.स>
#समावेश <linux/mutex.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/module.h>
#समावेश <linux/lcm.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/imu/adis.h>

#समावेश <linux/debugfs.h>

#घोषणा ADIS16480_PAGE_SIZE 0x80

#घोषणा ADIS16480_REG(page, reg) ((page) * ADIS16480_PAGE_SIZE + (reg))

#घोषणा ADIS16480_REG_PAGE_ID 0x00 /* Same address on each page */
#घोषणा ADIS16480_REG_SEQ_CNT			ADIS16480_REG(0x00, 0x06)
#घोषणा ADIS16480_REG_SYS_E_FLA			ADIS16480_REG(0x00, 0x08)
#घोषणा ADIS16480_REG_DIAG_STS			ADIS16480_REG(0x00, 0x0A)
#घोषणा ADIS16480_REG_ALM_STS			ADIS16480_REG(0x00, 0x0C)
#घोषणा ADIS16480_REG_TEMP_OUT			ADIS16480_REG(0x00, 0x0E)
#घोषणा ADIS16480_REG_X_GYRO_OUT		ADIS16480_REG(0x00, 0x10)
#घोषणा ADIS16480_REG_Y_GYRO_OUT		ADIS16480_REG(0x00, 0x14)
#घोषणा ADIS16480_REG_Z_GYRO_OUT		ADIS16480_REG(0x00, 0x18)
#घोषणा ADIS16480_REG_X_ACCEL_OUT		ADIS16480_REG(0x00, 0x1C)
#घोषणा ADIS16480_REG_Y_ACCEL_OUT		ADIS16480_REG(0x00, 0x20)
#घोषणा ADIS16480_REG_Z_ACCEL_OUT		ADIS16480_REG(0x00, 0x24)
#घोषणा ADIS16480_REG_X_MAGN_OUT		ADIS16480_REG(0x00, 0x28)
#घोषणा ADIS16480_REG_Y_MAGN_OUT		ADIS16480_REG(0x00, 0x2A)
#घोषणा ADIS16480_REG_Z_MAGN_OUT		ADIS16480_REG(0x00, 0x2C)
#घोषणा ADIS16480_REG_BAROM_OUT			ADIS16480_REG(0x00, 0x2E)
#घोषणा ADIS16480_REG_X_DELTAANG_OUT		ADIS16480_REG(0x00, 0x40)
#घोषणा ADIS16480_REG_Y_DELTAANG_OUT		ADIS16480_REG(0x00, 0x44)
#घोषणा ADIS16480_REG_Z_DELTAANG_OUT		ADIS16480_REG(0x00, 0x48)
#घोषणा ADIS16480_REG_X_DELTAVEL_OUT		ADIS16480_REG(0x00, 0x4C)
#घोषणा ADIS16480_REG_Y_DELTAVEL_OUT		ADIS16480_REG(0x00, 0x50)
#घोषणा ADIS16480_REG_Z_DELTAVEL_OUT		ADIS16480_REG(0x00, 0x54)
#घोषणा ADIS16480_REG_PROD_ID			ADIS16480_REG(0x00, 0x7E)

#घोषणा ADIS16480_REG_X_GYRO_SCALE		ADIS16480_REG(0x02, 0x04)
#घोषणा ADIS16480_REG_Y_GYRO_SCALE		ADIS16480_REG(0x02, 0x06)
#घोषणा ADIS16480_REG_Z_GYRO_SCALE		ADIS16480_REG(0x02, 0x08)
#घोषणा ADIS16480_REG_X_ACCEL_SCALE		ADIS16480_REG(0x02, 0x0A)
#घोषणा ADIS16480_REG_Y_ACCEL_SCALE		ADIS16480_REG(0x02, 0x0C)
#घोषणा ADIS16480_REG_Z_ACCEL_SCALE		ADIS16480_REG(0x02, 0x0E)
#घोषणा ADIS16480_REG_X_GYRO_BIAS		ADIS16480_REG(0x02, 0x10)
#घोषणा ADIS16480_REG_Y_GYRO_BIAS		ADIS16480_REG(0x02, 0x14)
#घोषणा ADIS16480_REG_Z_GYRO_BIAS		ADIS16480_REG(0x02, 0x18)
#घोषणा ADIS16480_REG_X_ACCEL_BIAS		ADIS16480_REG(0x02, 0x1C)
#घोषणा ADIS16480_REG_Y_ACCEL_BIAS		ADIS16480_REG(0x02, 0x20)
#घोषणा ADIS16480_REG_Z_ACCEL_BIAS		ADIS16480_REG(0x02, 0x24)
#घोषणा ADIS16480_REG_X_HARD_IRON		ADIS16480_REG(0x02, 0x28)
#घोषणा ADIS16480_REG_Y_HARD_IRON		ADIS16480_REG(0x02, 0x2A)
#घोषणा ADIS16480_REG_Z_HARD_IRON		ADIS16480_REG(0x02, 0x2C)
#घोषणा ADIS16480_REG_BAROM_BIAS		ADIS16480_REG(0x02, 0x40)
#घोषणा ADIS16480_REG_FLASH_CNT			ADIS16480_REG(0x02, 0x7C)

#घोषणा ADIS16480_REG_GLOB_CMD			ADIS16480_REG(0x03, 0x02)
#घोषणा ADIS16480_REG_FNCTIO_CTRL		ADIS16480_REG(0x03, 0x06)
#घोषणा ADIS16480_REG_GPIO_CTRL			ADIS16480_REG(0x03, 0x08)
#घोषणा ADIS16480_REG_CONFIG			ADIS16480_REG(0x03, 0x0A)
#घोषणा ADIS16480_REG_DEC_RATE			ADIS16480_REG(0x03, 0x0C)
#घोषणा ADIS16480_REG_SLP_CNT			ADIS16480_REG(0x03, 0x10)
#घोषणा ADIS16480_REG_FILTER_BNK0		ADIS16480_REG(0x03, 0x16)
#घोषणा ADIS16480_REG_FILTER_BNK1		ADIS16480_REG(0x03, 0x18)
#घोषणा ADIS16480_REG_ALM_CNFG0			ADIS16480_REG(0x03, 0x20)
#घोषणा ADIS16480_REG_ALM_CNFG1			ADIS16480_REG(0x03, 0x22)
#घोषणा ADIS16480_REG_ALM_CNFG2			ADIS16480_REG(0x03, 0x24)
#घोषणा ADIS16480_REG_XG_ALM_MAGN		ADIS16480_REG(0x03, 0x28)
#घोषणा ADIS16480_REG_YG_ALM_MAGN		ADIS16480_REG(0x03, 0x2A)
#घोषणा ADIS16480_REG_ZG_ALM_MAGN		ADIS16480_REG(0x03, 0x2C)
#घोषणा ADIS16480_REG_XA_ALM_MAGN		ADIS16480_REG(0x03, 0x2E)
#घोषणा ADIS16480_REG_YA_ALM_MAGN		ADIS16480_REG(0x03, 0x30)
#घोषणा ADIS16480_REG_ZA_ALM_MAGN		ADIS16480_REG(0x03, 0x32)
#घोषणा ADIS16480_REG_XM_ALM_MAGN		ADIS16480_REG(0x03, 0x34)
#घोषणा ADIS16480_REG_YM_ALM_MAGN		ADIS16480_REG(0x03, 0x36)
#घोषणा ADIS16480_REG_ZM_ALM_MAGN		ADIS16480_REG(0x03, 0x38)
#घोषणा ADIS16480_REG_BR_ALM_MAGN		ADIS16480_REG(0x03, 0x3A)
#घोषणा ADIS16480_REG_FIRM_REV			ADIS16480_REG(0x03, 0x78)
#घोषणा ADIS16480_REG_FIRM_DM			ADIS16480_REG(0x03, 0x7A)
#घोषणा ADIS16480_REG_FIRM_Y			ADIS16480_REG(0x03, 0x7C)

/*
 * External घड़ी scaling in PPS mode.
 * Available only क्रम ADIS1649x devices
 */
#घोषणा ADIS16495_REG_SYNC_SCALE		ADIS16480_REG(0x03, 0x10)

#घोषणा ADIS16480_REG_SERIAL_NUM		ADIS16480_REG(0x04, 0x20)

/* Each filter coefficent bank spans two pages */
#घोषणा ADIS16480_FIR_COEF(page) (x < 60 ? ADIS16480_REG(page, (x) + 8) : \
		ADIS16480_REG((page) + 1, (x) - 60 + 8))
#घोषणा ADIS16480_FIR_COEF_A(x)			ADIS16480_FIR_COEF(0x05, (x))
#घोषणा ADIS16480_FIR_COEF_B(x)			ADIS16480_FIR_COEF(0x07, (x))
#घोषणा ADIS16480_FIR_COEF_C(x)			ADIS16480_FIR_COEF(0x09, (x))
#घोषणा ADIS16480_FIR_COEF_D(x)			ADIS16480_FIR_COEF(0x0B, (x))

/* ADIS16480_REG_FNCTIO_CTRL */
#घोषणा ADIS16480_DRDY_SEL_MSK		GENMASK(1, 0)
#घोषणा ADIS16480_DRDY_SEL(x)		FIELD_PREP(ADIS16480_DRDY_SEL_MSK, x)
#घोषणा ADIS16480_DRDY_POL_MSK		BIT(2)
#घोषणा ADIS16480_DRDY_POL(x)		FIELD_PREP(ADIS16480_DRDY_POL_MSK, x)
#घोषणा ADIS16480_DRDY_EN_MSK		BIT(3)
#घोषणा ADIS16480_DRDY_EN(x)		FIELD_PREP(ADIS16480_DRDY_EN_MSK, x)
#घोषणा ADIS16480_SYNC_SEL_MSK		GENMASK(5, 4)
#घोषणा ADIS16480_SYNC_SEL(x)		FIELD_PREP(ADIS16480_SYNC_SEL_MSK, x)
#घोषणा ADIS16480_SYNC_EN_MSK		BIT(7)
#घोषणा ADIS16480_SYNC_EN(x)		FIELD_PREP(ADIS16480_SYNC_EN_MSK, x)
#घोषणा ADIS16480_SYNC_MODE_MSK		BIT(8)
#घोषणा ADIS16480_SYNC_MODE(x)		FIELD_PREP(ADIS16480_SYNC_MODE_MSK, x)

काष्ठा adis16480_chip_info अणु
	अचिन्हित पूर्णांक num_channels;
	स्थिर काष्ठा iio_chan_spec *channels;
	अचिन्हित पूर्णांक gyro_max_val;
	अचिन्हित पूर्णांक gyro_max_scale;
	अचिन्हित पूर्णांक accel_max_val;
	अचिन्हित पूर्णांक accel_max_scale;
	अचिन्हित पूर्णांक temp_scale;
	अचिन्हित पूर्णांक पूर्णांक_clk;
	अचिन्हित पूर्णांक max_dec_rate;
	स्थिर अचिन्हित पूर्णांक *filter_freqs;
	bool has_pps_clk_mode;
	स्थिर काष्ठा adis_data adis_data;
पूर्ण;

क्रमागत adis16480_पूर्णांक_pin अणु
	ADIS16480_PIN_DIO1,
	ADIS16480_PIN_DIO2,
	ADIS16480_PIN_DIO3,
	ADIS16480_PIN_DIO4
पूर्ण;

क्रमागत adis16480_घड़ी_mode अणु
	ADIS16480_CLK_SYNC,
	ADIS16480_CLK_PPS,
	ADIS16480_CLK_INT
पूर्ण;

काष्ठा adis16480 अणु
	स्थिर काष्ठा adis16480_chip_info *chip_info;

	काष्ठा adis adis;
	काष्ठा clk *ext_clk;
	क्रमागत adis16480_घड़ी_mode clk_mode;
	अचिन्हित पूर्णांक clk_freq;
पूर्ण;

अटल स्थिर अक्षर * स्थिर adis16480_पूर्णांक_pin_names[4] = अणु
	[ADIS16480_PIN_DIO1] = "DIO1",
	[ADIS16480_PIN_DIO2] = "DIO2",
	[ADIS16480_PIN_DIO3] = "DIO3",
	[ADIS16480_PIN_DIO4] = "DIO4",
पूर्ण;

अटल bool low_rate_allow;
module_param(low_rate_allow, bool, 0444);
MODULE_PARM_DESC(low_rate_allow,
		 "Allow IMU rates below the minimum advisable when external clk is used in PPS mode (default: N)");

#अगर_घोषित CONFIG_DEBUG_FS

अटल sमाप_प्रकार adis16480_show_firmware_revision(काष्ठा file *file,
		अक्षर __user *userbuf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा adis16480 *adis16480 = file->निजी_data;
	अक्षर buf[7];
	माप_प्रकार len;
	u16 rev;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg_16(&adis16480->adis, ADIS16480_REG_FIRM_REV, &rev);
	अगर (ret)
		वापस ret;

	len = scnम_लिखो(buf, माप(buf), "%x.%x\n", rev >> 8, rev & 0xff);

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations adis16480_firmware_revision_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = adis16480_show_firmware_revision,
	.llseek = शेष_llseek,
	.owner = THIS_MODULE,
पूर्ण;

अटल sमाप_प्रकार adis16480_show_firmware_date(काष्ठा file *file,
		अक्षर __user *userbuf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा adis16480 *adis16480 = file->निजी_data;
	u16 md, year;
	अक्षर buf[12];
	माप_प्रकार len;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg_16(&adis16480->adis, ADIS16480_REG_FIRM_Y, &year);
	अगर (ret)
		वापस ret;

	ret = adis_पढ़ो_reg_16(&adis16480->adis, ADIS16480_REG_FIRM_DM, &md);
	अगर (ret)
		वापस ret;

	len = snम_लिखो(buf, माप(buf), "%.2x-%.2x-%.4x\n",
			md >> 8, md & 0xff, year);

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations adis16480_firmware_date_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = adis16480_show_firmware_date,
	.llseek = शेष_llseek,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक adis16480_show_serial_number(व्योम *arg, u64 *val)
अणु
	काष्ठा adis16480 *adis16480 = arg;
	u16 serial;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg_16(&adis16480->adis, ADIS16480_REG_SERIAL_NUM,
		&serial);
	अगर (ret)
		वापस ret;

	*val = serial;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(adis16480_serial_number_fops,
	adis16480_show_serial_number, शून्य, "0x%.4llx\n");

अटल पूर्णांक adis16480_show_product_id(व्योम *arg, u64 *val)
अणु
	काष्ठा adis16480 *adis16480 = arg;
	u16 prod_id;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg_16(&adis16480->adis, ADIS16480_REG_PROD_ID,
		&prod_id);
	अगर (ret)
		वापस ret;

	*val = prod_id;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(adis16480_product_id_fops,
	adis16480_show_product_id, शून्य, "%llu\n");

अटल पूर्णांक adis16480_show_flash_count(व्योम *arg, u64 *val)
अणु
	काष्ठा adis16480 *adis16480 = arg;
	u32 flash_count;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg_32(&adis16480->adis, ADIS16480_REG_FLASH_CNT,
		&flash_count);
	अगर (ret)
		वापस ret;

	*val = flash_count;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(adis16480_flash_count_fops,
	adis16480_show_flash_count, शून्य, "%lld\n");

अटल पूर्णांक adis16480_debugfs_init(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा adis16480 *adis16480 = iio_priv(indio_dev);
	काष्ठा dentry *d = iio_get_debugfs_dentry(indio_dev);

	debugfs_create_file_unsafe("firmware_revision", 0400,
		d, adis16480, &adis16480_firmware_revision_fops);
	debugfs_create_file_unsafe("firmware_date", 0400,
		d, adis16480, &adis16480_firmware_date_fops);
	debugfs_create_file_unsafe("serial_number", 0400,
		d, adis16480, &adis16480_serial_number_fops);
	debugfs_create_file_unsafe("product_id", 0400,
		d, adis16480, &adis16480_product_id_fops);
	debugfs_create_file_unsafe("flash_count", 0400,
		d, adis16480, &adis16480_flash_count_fops);

	वापस 0;
पूर्ण

#अन्यथा

अटल पूर्णांक adis16480_debugfs_init(काष्ठा iio_dev *indio_dev)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक adis16480_set_freq(काष्ठा iio_dev *indio_dev, पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा adis16480 *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक t, sample_rate = st->clk_freq;
	पूर्णांक ret;

	अगर (val < 0 || val2 < 0)
		वापस -EINVAL;

	t =  val * 1000 + val2 / 1000;
	अगर (t == 0)
		वापस -EINVAL;

	adis_dev_lock(&st->adis);
	/*
	 * When using PPS mode, the input घड़ी needs to be scaled so that we have an IMU
	 * sample rate between (optimally) 4000 and 4250. After this, we can use the
	 * decimation filter to lower the sampling rate in order to get what the user wants.
	 * Optimally, the user sample rate is a multiple of both the IMU sample rate and
	 * the input घड़ी. Hence, calculating the sync_scale dynamically gives us better
	 * chances of achieving a perfect/पूर्णांकeger value क्रम DEC_RATE. The math here is:
	 *	1. lcm of the input घड़ी and the desired output rate.
	 *	2. get the highest multiple of the previous result lower than the adis max rate.
	 *	3. The last result becomes the IMU sample rate. Use that to calculate SYNC_SCALE
	 *	   and DEC_RATE (to get the user output rate)
	 */
	अगर (st->clk_mode == ADIS16480_CLK_PPS) अणु
		अचिन्हित दीर्घ scaled_rate = lcm(st->clk_freq, t);
		पूर्णांक sync_scale;

		/*
		 * If lcm is bigger than the IMU maximum sampling rate there's no perfect
		 * solution. In this हाल, we get the highest multiple of the input घड़ी
		 * lower than the IMU max sample rate.
		 */
		अगर (scaled_rate > st->chip_info->पूर्णांक_clk)
			scaled_rate = st->chip_info->पूर्णांक_clk / st->clk_freq * st->clk_freq;
		अन्यथा
			scaled_rate = st->chip_info->पूर्णांक_clk / scaled_rate * scaled_rate;

		/*
		 * This is not an hard requirement but it's not advised to run the IMU
		 * with a sample rate lower than 4000Hz due to possible undersampling
		 * issues. However, there are users that might really want to take the risk.
		 * Hence, we provide a module parameter क्रम them. If set, we allow sample
		 * rates lower than 4KHz. By शेष, we won't allow this and we just roundup
		 * the rate to the next multiple of the input घड़ी bigger than 4KHz. This
		 * is करोne like this as in some हालs (when DEC_RATE is 0) might give
		 * us the बंदst value to the one desired by the user...
		 */
		अगर (scaled_rate < 4000000 && !low_rate_allow)
			scaled_rate = roundup(4000000, st->clk_freq);

		sync_scale = scaled_rate / st->clk_freq;
		ret = __adis_ग_लिखो_reg_16(&st->adis, ADIS16495_REG_SYNC_SCALE, sync_scale);
		अगर (ret)
			जाओ error;

		sample_rate = scaled_rate;
	पूर्ण

	t = DIV_ROUND_CLOSEST(sample_rate, t);
	अगर (t)
		t--;

	अगर (t > st->chip_info->max_dec_rate)
		t = st->chip_info->max_dec_rate;

	ret = __adis_ग_लिखो_reg_16(&st->adis, ADIS16480_REG_DEC_RATE, t);
error:
	adis_dev_unlock(&st->adis);
	वापस ret;
पूर्ण

अटल पूर्णांक adis16480_get_freq(काष्ठा iio_dev *indio_dev, पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा adis16480 *st = iio_priv(indio_dev);
	uपूर्णांक16_t t;
	पूर्णांक ret;
	अचिन्हित पूर्णांक freq, sample_rate = st->clk_freq;

	adis_dev_lock(&st->adis);

	अगर (st->clk_mode == ADIS16480_CLK_PPS) अणु
		u16 sync_scale;

		ret = __adis_पढ़ो_reg_16(&st->adis, ADIS16495_REG_SYNC_SCALE, &sync_scale);
		अगर (ret)
			जाओ error;

		sample_rate = st->clk_freq * sync_scale;
	पूर्ण

	ret = __adis_पढ़ो_reg_16(&st->adis, ADIS16480_REG_DEC_RATE, &t);
	अगर (ret)
		जाओ error;

	adis_dev_unlock(&st->adis);

	freq = DIV_ROUND_CLOSEST(sample_rate, (t + 1));

	*val = freq / 1000;
	*val2 = (freq % 1000) * 1000;

	वापस IIO_VAL_INT_PLUS_MICRO;
error:
	adis_dev_unlock(&st->adis);
	वापस ret;
पूर्ण

क्रमागत अणु
	ADIS16480_SCAN_GYRO_X,
	ADIS16480_SCAN_GYRO_Y,
	ADIS16480_SCAN_GYRO_Z,
	ADIS16480_SCAN_ACCEL_X,
	ADIS16480_SCAN_ACCEL_Y,
	ADIS16480_SCAN_ACCEL_Z,
	ADIS16480_SCAN_MAGN_X,
	ADIS16480_SCAN_MAGN_Y,
	ADIS16480_SCAN_MAGN_Z,
	ADIS16480_SCAN_BARO,
	ADIS16480_SCAN_TEMP,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक adis16480_calibbias_regs[] = अणु
	[ADIS16480_SCAN_GYRO_X] = ADIS16480_REG_X_GYRO_BIAS,
	[ADIS16480_SCAN_GYRO_Y] = ADIS16480_REG_Y_GYRO_BIAS,
	[ADIS16480_SCAN_GYRO_Z] = ADIS16480_REG_Z_GYRO_BIAS,
	[ADIS16480_SCAN_ACCEL_X] = ADIS16480_REG_X_ACCEL_BIAS,
	[ADIS16480_SCAN_ACCEL_Y] = ADIS16480_REG_Y_ACCEL_BIAS,
	[ADIS16480_SCAN_ACCEL_Z] = ADIS16480_REG_Z_ACCEL_BIAS,
	[ADIS16480_SCAN_MAGN_X] = ADIS16480_REG_X_HARD_IRON,
	[ADIS16480_SCAN_MAGN_Y] = ADIS16480_REG_Y_HARD_IRON,
	[ADIS16480_SCAN_MAGN_Z] = ADIS16480_REG_Z_HARD_IRON,
	[ADIS16480_SCAN_BARO] = ADIS16480_REG_BAROM_BIAS,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक adis16480_calibscale_regs[] = अणु
	[ADIS16480_SCAN_GYRO_X] = ADIS16480_REG_X_GYRO_SCALE,
	[ADIS16480_SCAN_GYRO_Y] = ADIS16480_REG_Y_GYRO_SCALE,
	[ADIS16480_SCAN_GYRO_Z] = ADIS16480_REG_Z_GYRO_SCALE,
	[ADIS16480_SCAN_ACCEL_X] = ADIS16480_REG_X_ACCEL_SCALE,
	[ADIS16480_SCAN_ACCEL_Y] = ADIS16480_REG_Y_ACCEL_SCALE,
	[ADIS16480_SCAN_ACCEL_Z] = ADIS16480_REG_Z_ACCEL_SCALE,
पूर्ण;

अटल पूर्णांक adis16480_set_calibbias(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक bias)
अणु
	अचिन्हित पूर्णांक reg = adis16480_calibbias_regs[chan->scan_index];
	काष्ठा adis16480 *st = iio_priv(indio_dev);

	चयन (chan->type) अणु
	हाल IIO_MAGN:
	हाल IIO_PRESSURE:
		अगर (bias < -0x8000 || bias >= 0x8000)
			वापस -EINVAL;
		वापस adis_ग_लिखो_reg_16(&st->adis, reg, bias);
	हाल IIO_ANGL_VEL:
	हाल IIO_ACCEL:
		वापस adis_ग_लिखो_reg_32(&st->adis, reg, bias);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक adis16480_get_calibbias(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक *bias)
अणु
	अचिन्हित पूर्णांक reg = adis16480_calibbias_regs[chan->scan_index];
	काष्ठा adis16480 *st = iio_priv(indio_dev);
	uपूर्णांक16_t val16;
	uपूर्णांक32_t val32;
	पूर्णांक ret;

	चयन (chan->type) अणु
	हाल IIO_MAGN:
	हाल IIO_PRESSURE:
		ret = adis_पढ़ो_reg_16(&st->adis, reg, &val16);
		अगर (ret == 0)
			*bias = sign_extend32(val16, 15);
		अवरोध;
	हाल IIO_ANGL_VEL:
	हाल IIO_ACCEL:
		ret = adis_पढ़ो_reg_32(&st->adis, reg, &val32);
		अगर (ret == 0)
			*bias = sign_extend32(val32, 31);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	अगर (ret)
		वापस ret;

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक adis16480_set_calibscale(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक scale)
अणु
	अचिन्हित पूर्णांक reg = adis16480_calibscale_regs[chan->scan_index];
	काष्ठा adis16480 *st = iio_priv(indio_dev);

	अगर (scale < -0x8000 || scale >= 0x8000)
		वापस -EINVAL;

	वापस adis_ग_लिखो_reg_16(&st->adis, reg, scale);
पूर्ण

अटल पूर्णांक adis16480_get_calibscale(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक *scale)
अणु
	अचिन्हित पूर्णांक reg = adis16480_calibscale_regs[chan->scan_index];
	काष्ठा adis16480 *st = iio_priv(indio_dev);
	uपूर्णांक16_t val16;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg_16(&st->adis, reg, &val16);
	अगर (ret)
		वापस ret;

	*scale = sign_extend32(val16, 15);
	वापस IIO_VAL_INT;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक adis16480_def_filter_freqs[] = अणु
	310,
	55,
	275,
	63,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक adis16495_def_filter_freqs[] = अणु
	300,
	100,
	300,
	100,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ad16480_filter_data[][2] = अणु
	[ADIS16480_SCAN_GYRO_X]		= अणु ADIS16480_REG_FILTER_BNK0, 0 पूर्ण,
	[ADIS16480_SCAN_GYRO_Y]		= अणु ADIS16480_REG_FILTER_BNK0, 3 पूर्ण,
	[ADIS16480_SCAN_GYRO_Z]		= अणु ADIS16480_REG_FILTER_BNK0, 6 पूर्ण,
	[ADIS16480_SCAN_ACCEL_X]	= अणु ADIS16480_REG_FILTER_BNK0, 9 पूर्ण,
	[ADIS16480_SCAN_ACCEL_Y]	= अणु ADIS16480_REG_FILTER_BNK0, 12 पूर्ण,
	[ADIS16480_SCAN_ACCEL_Z]	= अणु ADIS16480_REG_FILTER_BNK1, 0 पूर्ण,
	[ADIS16480_SCAN_MAGN_X]		= अणु ADIS16480_REG_FILTER_BNK1, 3 पूर्ण,
	[ADIS16480_SCAN_MAGN_Y]		= अणु ADIS16480_REG_FILTER_BNK1, 6 पूर्ण,
	[ADIS16480_SCAN_MAGN_Z]		= अणु ADIS16480_REG_FILTER_BNK1, 9 पूर्ण,
पूर्ण;

अटल पूर्णांक adis16480_get_filter_freq(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक *freq)
अणु
	काष्ठा adis16480 *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक enable_mask, offset, reg;
	uपूर्णांक16_t val;
	पूर्णांक ret;

	reg = ad16480_filter_data[chan->scan_index][0];
	offset = ad16480_filter_data[chan->scan_index][1];
	enable_mask = BIT(offset + 2);

	ret = adis_पढ़ो_reg_16(&st->adis, reg, &val);
	अगर (ret)
		वापस ret;

	अगर (!(val & enable_mask))
		*freq = 0;
	अन्यथा
		*freq = st->chip_info->filter_freqs[(val >> offset) & 0x3];

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक adis16480_set_filter_freq(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, अचिन्हित पूर्णांक freq)
अणु
	काष्ठा adis16480 *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक enable_mask, offset, reg;
	अचिन्हित पूर्णांक dअगरf, best_dअगरf;
	अचिन्हित पूर्णांक i, best_freq;
	uपूर्णांक16_t val;
	पूर्णांक ret;

	reg = ad16480_filter_data[chan->scan_index][0];
	offset = ad16480_filter_data[chan->scan_index][1];
	enable_mask = BIT(offset + 2);

	adis_dev_lock(&st->adis);

	ret = __adis_पढ़ो_reg_16(&st->adis, reg, &val);
	अगर (ret)
		जाओ out_unlock;

	अगर (freq == 0) अणु
		val &= ~enable_mask;
	पूर्ण अन्यथा अणु
		best_freq = 0;
		best_dअगरf = st->chip_info->filter_freqs[0];
		क्रम (i = 0; i < ARRAY_SIZE(adis16480_def_filter_freqs); i++) अणु
			अगर (st->chip_info->filter_freqs[i] >= freq) अणु
				dअगरf = st->chip_info->filter_freqs[i] - freq;
				अगर (dअगरf < best_dअगरf) अणु
					best_dअगरf = dअगरf;
					best_freq = i;
				पूर्ण
			पूर्ण
		पूर्ण

		val &= ~(0x3 << offset);
		val |= best_freq << offset;
		val |= enable_mask;
	पूर्ण

	ret = __adis_ग_लिखो_reg_16(&st->adis, reg, val);
out_unlock:
	adis_dev_unlock(&st->adis);

	वापस ret;
पूर्ण

अटल पूर्णांक adis16480_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	काष्ठा adis16480 *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक temp;

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
		हाल IIO_MAGN:
			*val = 0;
			*val2 = 100; /* 0.0001 gauss */
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_TEMP:
			/*
			 * +85 degrees Celsius = temp_max_scale
			 * +25 degrees Celsius = 0
			 * LSB, 25 degrees Celsius  = 60 / temp_max_scale
			 */
			*val = st->chip_info->temp_scale / 1000;
			*val2 = (st->chip_info->temp_scale % 1000) * 1000;
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_PRESSURE:
			/*
			 * max scale is 1310 mbar
			 * max raw value is 32767 shअगरted क्रम 32bits
			 */
			*val = 131; /* 1310mbar = 131 kPa */
			*val2 = 32767 << 16;
			वापस IIO_VAL_FRACTIONAL;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_OFFSET:
		/* Only the temperature channel has a offset */
		temp = 25 * 1000000LL; /* 25 degree Celsius = 0x0000 */
		*val = DIV_ROUND_CLOSEST_ULL(temp, st->chip_info->temp_scale);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		वापस adis16480_get_calibbias(indio_dev, chan, val);
	हाल IIO_CHAN_INFO_CALIBSCALE:
		वापस adis16480_get_calibscale(indio_dev, chan, val);
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		वापस adis16480_get_filter_freq(indio_dev, chan, val);
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस adis16480_get_freq(indio_dev, val, val2);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक adis16480_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक val, पूर्णांक val2, दीर्घ info)
अणु
	चयन (info) अणु
	हाल IIO_CHAN_INFO_CALIBBIAS:
		वापस adis16480_set_calibbias(indio_dev, chan, val);
	हाल IIO_CHAN_INFO_CALIBSCALE:
		वापस adis16480_set_calibscale(indio_dev, chan, val);
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		वापस adis16480_set_filter_freq(indio_dev, chan, val);
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस adis16480_set_freq(indio_dev, val, val2);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

#घोषणा ADIS16480_MOD_CHANNEL(_type, _mod, _address, _si, _info_sep, _bits) \
	अणु \
		.type = (_type), \
		.modअगरied = 1, \
		.channel2 = (_mod), \
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
			BIT(IIO_CHAN_INFO_CALIBBIAS) | \
			_info_sep, \
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

#घोषणा ADIS16480_GYRO_CHANNEL(_mod) \
	ADIS16480_MOD_CHANNEL(IIO_ANGL_VEL, IIO_MOD_ ## _mod, \
	ADIS16480_REG_ ## _mod ## _GYRO_OUT, ADIS16480_SCAN_GYRO_ ## _mod, \
	BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY) | \
	BIT(IIO_CHAN_INFO_CALIBSCALE), \
	32)

#घोषणा ADIS16480_ACCEL_CHANNEL(_mod) \
	ADIS16480_MOD_CHANNEL(IIO_ACCEL, IIO_MOD_ ## _mod, \
	ADIS16480_REG_ ## _mod ## _ACCEL_OUT, ADIS16480_SCAN_ACCEL_ ## _mod, \
	BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY) | \
	BIT(IIO_CHAN_INFO_CALIBSCALE), \
	32)

#घोषणा ADIS16480_MAGN_CHANNEL(_mod) \
	ADIS16480_MOD_CHANNEL(IIO_MAGN, IIO_MOD_ ## _mod, \
	ADIS16480_REG_ ## _mod ## _MAGN_OUT, ADIS16480_SCAN_MAGN_ ## _mod, \
	BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY), \
	16)

#घोषणा ADIS16480_PRESSURE_CHANNEL() \
	अणु \
		.type = IIO_PRESSURE, \
		.indexed = 1, \
		.channel = 0, \
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
			BIT(IIO_CHAN_INFO_CALIBBIAS) | \
			BIT(IIO_CHAN_INFO_SCALE), \
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
		.address = ADIS16480_REG_BAROM_OUT, \
		.scan_index = ADIS16480_SCAN_BARO, \
		.scan_type = अणु \
			.sign = 's', \
			.realbits = 32, \
			.storagebits = 32, \
			.endianness = IIO_BE, \
		पूर्ण, \
	पूर्ण

#घोषणा ADIS16480_TEMP_CHANNEL() अणु \
		.type = IIO_TEMP, \
		.indexed = 1, \
		.channel = 0, \
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
			BIT(IIO_CHAN_INFO_SCALE) | \
			BIT(IIO_CHAN_INFO_OFFSET), \
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
		.address = ADIS16480_REG_TEMP_OUT, \
		.scan_index = ADIS16480_SCAN_TEMP, \
		.scan_type = अणु \
			.sign = 's', \
			.realbits = 16, \
			.storagebits = 16, \
			.endianness = IIO_BE, \
		पूर्ण, \
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec adis16480_channels[] = अणु
	ADIS16480_GYRO_CHANNEL(X),
	ADIS16480_GYRO_CHANNEL(Y),
	ADIS16480_GYRO_CHANNEL(Z),
	ADIS16480_ACCEL_CHANNEL(X),
	ADIS16480_ACCEL_CHANNEL(Y),
	ADIS16480_ACCEL_CHANNEL(Z),
	ADIS16480_MAGN_CHANNEL(X),
	ADIS16480_MAGN_CHANNEL(Y),
	ADIS16480_MAGN_CHANNEL(Z),
	ADIS16480_PRESSURE_CHANNEL(),
	ADIS16480_TEMP_CHANNEL(),
	IIO_CHAN_SOFT_TIMESTAMP(11)
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec adis16485_channels[] = अणु
	ADIS16480_GYRO_CHANNEL(X),
	ADIS16480_GYRO_CHANNEL(Y),
	ADIS16480_GYRO_CHANNEL(Z),
	ADIS16480_ACCEL_CHANNEL(X),
	ADIS16480_ACCEL_CHANNEL(Y),
	ADIS16480_ACCEL_CHANNEL(Z),
	ADIS16480_TEMP_CHANNEL(),
	IIO_CHAN_SOFT_TIMESTAMP(7)
पूर्ण;

क्रमागत adis16480_variant अणु
	ADIS16375,
	ADIS16480,
	ADIS16485,
	ADIS16488,
	ADIS16490,
	ADIS16495_1,
	ADIS16495_2,
	ADIS16495_3,
	ADIS16497_1,
	ADIS16497_2,
	ADIS16497_3,
पूर्ण;

#घोषणा ADIS16480_DIAG_STAT_XGYRO_FAIL 0
#घोषणा ADIS16480_DIAG_STAT_YGYRO_FAIL 1
#घोषणा ADIS16480_DIAG_STAT_ZGYRO_FAIL 2
#घोषणा ADIS16480_DIAG_STAT_XACCL_FAIL 3
#घोषणा ADIS16480_DIAG_STAT_YACCL_FAIL 4
#घोषणा ADIS16480_DIAG_STAT_ZACCL_FAIL 5
#घोषणा ADIS16480_DIAG_STAT_XMAGN_FAIL 8
#घोषणा ADIS16480_DIAG_STAT_YMAGN_FAIL 9
#घोषणा ADIS16480_DIAG_STAT_ZMAGN_FAIL 10
#घोषणा ADIS16480_DIAG_STAT_BARO_FAIL 11

अटल स्थिर अक्षर * स्थिर adis16480_status_error_msgs[] = अणु
	[ADIS16480_DIAG_STAT_XGYRO_FAIL] = "X-axis gyroscope self-test failure",
	[ADIS16480_DIAG_STAT_YGYRO_FAIL] = "Y-axis gyroscope self-test failure",
	[ADIS16480_DIAG_STAT_ZGYRO_FAIL] = "Z-axis gyroscope self-test failure",
	[ADIS16480_DIAG_STAT_XACCL_FAIL] = "X-axis accelerometer self-test failure",
	[ADIS16480_DIAG_STAT_YACCL_FAIL] = "Y-axis accelerometer self-test failure",
	[ADIS16480_DIAG_STAT_ZACCL_FAIL] = "Z-axis accelerometer self-test failure",
	[ADIS16480_DIAG_STAT_XMAGN_FAIL] = "X-axis magnetometer self-test failure",
	[ADIS16480_DIAG_STAT_YMAGN_FAIL] = "Y-axis magnetometer self-test failure",
	[ADIS16480_DIAG_STAT_ZMAGN_FAIL] = "Z-axis magnetometer self-test failure",
	[ADIS16480_DIAG_STAT_BARO_FAIL] = "Barometer self-test failure",
पूर्ण;

अटल पूर्णांक adis16480_enable_irq(काष्ठा adis *adis, bool enable);

#घोषणा ADIS16480_DATA(_prod_id, _समयouts)				\
अणु									\
	.diag_stat_reg = ADIS16480_REG_DIAG_STS,			\
	.glob_cmd_reg = ADIS16480_REG_GLOB_CMD,				\
	.prod_id_reg = ADIS16480_REG_PROD_ID,				\
	.prod_id = (_prod_id),						\
	.has_paging = true,						\
	.पढ़ो_delay = 5,						\
	.ग_लिखो_delay = 5,						\
	.self_test_mask = BIT(1),					\
	.self_test_reg = ADIS16480_REG_GLOB_CMD,			\
	.status_error_msgs = adis16480_status_error_msgs,		\
	.status_error_mask = BIT(ADIS16480_DIAG_STAT_XGYRO_FAIL) |	\
		BIT(ADIS16480_DIAG_STAT_YGYRO_FAIL) |			\
		BIT(ADIS16480_DIAG_STAT_ZGYRO_FAIL) |			\
		BIT(ADIS16480_DIAG_STAT_XACCL_FAIL) |			\
		BIT(ADIS16480_DIAG_STAT_YACCL_FAIL) |			\
		BIT(ADIS16480_DIAG_STAT_ZACCL_FAIL) |			\
		BIT(ADIS16480_DIAG_STAT_XMAGN_FAIL) |			\
		BIT(ADIS16480_DIAG_STAT_YMAGN_FAIL) |			\
		BIT(ADIS16480_DIAG_STAT_ZMAGN_FAIL) |			\
		BIT(ADIS16480_DIAG_STAT_BARO_FAIL),			\
	.enable_irq = adis16480_enable_irq,				\
	.समयouts = (_समयouts),					\
पूर्ण

अटल स्थिर काष्ठा adis_समयout adis16485_समयouts = अणु
	.reset_ms = 560,
	.sw_reset_ms = 120,
	.self_test_ms = 12,
पूर्ण;

अटल स्थिर काष्ठा adis_समयout adis16480_समयouts = अणु
	.reset_ms = 560,
	.sw_reset_ms = 560,
	.self_test_ms = 12,
पूर्ण;

अटल स्थिर काष्ठा adis_समयout adis16495_समयouts = अणु
	.reset_ms = 170,
	.sw_reset_ms = 130,
	.self_test_ms = 40,
पूर्ण;

अटल स्थिर काष्ठा adis_समयout adis16495_1_समयouts = अणु
	.reset_ms = 250,
	.sw_reset_ms = 210,
	.self_test_ms = 20,
पूर्ण;

अटल स्थिर काष्ठा adis16480_chip_info adis16480_chip_info[] = अणु
	[ADIS16375] = अणु
		.channels = adis16485_channels,
		.num_channels = ARRAY_SIZE(adis16485_channels),
		/*
		 * Typically we करो IIO_RAD_TO_DEGREE in the denominator, which
		 * is exactly the same as IIO_DEGREE_TO_RAD in numerator, since
		 * it gives better approximation. However, in this हाल we
		 * cannot करो it since it would not fit in a 32bit variable.
		 */
		.gyro_max_val = 22887 << 16,
		.gyro_max_scale = IIO_DEGREE_TO_RAD(300),
		.accel_max_val = IIO_M_S_2_TO_G(21973 << 16),
		.accel_max_scale = 18,
		.temp_scale = 5650, /* 5.65 milli degree Celsius */
		.पूर्णांक_clk = 2460000,
		.max_dec_rate = 2048,
		.filter_freqs = adis16480_def_filter_freqs,
		.adis_data = ADIS16480_DATA(16375, &adis16485_समयouts),
	पूर्ण,
	[ADIS16480] = अणु
		.channels = adis16480_channels,
		.num_channels = ARRAY_SIZE(adis16480_channels),
		.gyro_max_val = 22500 << 16,
		.gyro_max_scale = IIO_DEGREE_TO_RAD(450),
		.accel_max_val = IIO_M_S_2_TO_G(12500 << 16),
		.accel_max_scale = 10,
		.temp_scale = 5650, /* 5.65 milli degree Celsius */
		.पूर्णांक_clk = 2460000,
		.max_dec_rate = 2048,
		.filter_freqs = adis16480_def_filter_freqs,
		.adis_data = ADIS16480_DATA(16480, &adis16480_समयouts),
	पूर्ण,
	[ADIS16485] = अणु
		.channels = adis16485_channels,
		.num_channels = ARRAY_SIZE(adis16485_channels),
		.gyro_max_val = 22500 << 16,
		.gyro_max_scale = IIO_DEGREE_TO_RAD(450),
		.accel_max_val = IIO_M_S_2_TO_G(20000 << 16),
		.accel_max_scale = 5,
		.temp_scale = 5650, /* 5.65 milli degree Celsius */
		.पूर्णांक_clk = 2460000,
		.max_dec_rate = 2048,
		.filter_freqs = adis16480_def_filter_freqs,
		.adis_data = ADIS16480_DATA(16485, &adis16485_समयouts),
	पूर्ण,
	[ADIS16488] = अणु
		.channels = adis16480_channels,
		.num_channels = ARRAY_SIZE(adis16480_channels),
		.gyro_max_val = 22500 << 16,
		.gyro_max_scale = IIO_DEGREE_TO_RAD(450),
		.accel_max_val = IIO_M_S_2_TO_G(22500 << 16),
		.accel_max_scale = 18,
		.temp_scale = 5650, /* 5.65 milli degree Celsius */
		.पूर्णांक_clk = 2460000,
		.max_dec_rate = 2048,
		.filter_freqs = adis16480_def_filter_freqs,
		.adis_data = ADIS16480_DATA(16488, &adis16485_समयouts),
	पूर्ण,
	[ADIS16490] = अणु
		.channels = adis16485_channels,
		.num_channels = ARRAY_SIZE(adis16485_channels),
		.gyro_max_val = 20000 << 16,
		.gyro_max_scale = IIO_DEGREE_TO_RAD(100),
		.accel_max_val = IIO_M_S_2_TO_G(16000 << 16),
		.accel_max_scale = 8,
		.temp_scale = 14285, /* 14.285 milli degree Celsius */
		.पूर्णांक_clk = 4250000,
		.max_dec_rate = 4250,
		.filter_freqs = adis16495_def_filter_freqs,
		.has_pps_clk_mode = true,
		.adis_data = ADIS16480_DATA(16490, &adis16495_समयouts),
	पूर्ण,
	[ADIS16495_1] = अणु
		.channels = adis16485_channels,
		.num_channels = ARRAY_SIZE(adis16485_channels),
		.gyro_max_val = 20000 << 16,
		.gyro_max_scale = IIO_DEGREE_TO_RAD(125),
		.accel_max_val = IIO_M_S_2_TO_G(32000 << 16),
		.accel_max_scale = 8,
		.temp_scale = 12500, /* 12.5 milli degree Celsius */
		.पूर्णांक_clk = 4250000,
		.max_dec_rate = 4250,
		.filter_freqs = adis16495_def_filter_freqs,
		.has_pps_clk_mode = true,
		.adis_data = ADIS16480_DATA(16495, &adis16495_1_समयouts),
	पूर्ण,
	[ADIS16495_2] = अणु
		.channels = adis16485_channels,
		.num_channels = ARRAY_SIZE(adis16485_channels),
		.gyro_max_val = 18000 << 16,
		.gyro_max_scale = IIO_DEGREE_TO_RAD(450),
		.accel_max_val = IIO_M_S_2_TO_G(32000 << 16),
		.accel_max_scale = 8,
		.temp_scale = 12500, /* 12.5 milli degree Celsius */
		.पूर्णांक_clk = 4250000,
		.max_dec_rate = 4250,
		.filter_freqs = adis16495_def_filter_freqs,
		.has_pps_clk_mode = true,
		.adis_data = ADIS16480_DATA(16495, &adis16495_1_समयouts),
	पूर्ण,
	[ADIS16495_3] = अणु
		.channels = adis16485_channels,
		.num_channels = ARRAY_SIZE(adis16485_channels),
		.gyro_max_val = 20000 << 16,
		.gyro_max_scale = IIO_DEGREE_TO_RAD(2000),
		.accel_max_val = IIO_M_S_2_TO_G(32000 << 16),
		.accel_max_scale = 8,
		.temp_scale = 12500, /* 12.5 milli degree Celsius */
		.पूर्णांक_clk = 4250000,
		.max_dec_rate = 4250,
		.filter_freqs = adis16495_def_filter_freqs,
		.has_pps_clk_mode = true,
		.adis_data = ADIS16480_DATA(16495, &adis16495_1_समयouts),
	पूर्ण,
	[ADIS16497_1] = अणु
		.channels = adis16485_channels,
		.num_channels = ARRAY_SIZE(adis16485_channels),
		.gyro_max_val = 20000 << 16,
		.gyro_max_scale = IIO_DEGREE_TO_RAD(125),
		.accel_max_val = IIO_M_S_2_TO_G(32000 << 16),
		.accel_max_scale = 40,
		.temp_scale = 12500, /* 12.5 milli degree Celsius */
		.पूर्णांक_clk = 4250000,
		.max_dec_rate = 4250,
		.filter_freqs = adis16495_def_filter_freqs,
		.has_pps_clk_mode = true,
		.adis_data = ADIS16480_DATA(16497, &adis16495_1_समयouts),
	पूर्ण,
	[ADIS16497_2] = अणु
		.channels = adis16485_channels,
		.num_channels = ARRAY_SIZE(adis16485_channels),
		.gyro_max_val = 18000 << 16,
		.gyro_max_scale = IIO_DEGREE_TO_RAD(450),
		.accel_max_val = IIO_M_S_2_TO_G(32000 << 16),
		.accel_max_scale = 40,
		.temp_scale = 12500, /* 12.5 milli degree Celsius */
		.पूर्णांक_clk = 4250000,
		.max_dec_rate = 4250,
		.filter_freqs = adis16495_def_filter_freqs,
		.has_pps_clk_mode = true,
		.adis_data = ADIS16480_DATA(16497, &adis16495_1_समयouts),
	पूर्ण,
	[ADIS16497_3] = अणु
		.channels = adis16485_channels,
		.num_channels = ARRAY_SIZE(adis16485_channels),
		.gyro_max_val = 20000 << 16,
		.gyro_max_scale = IIO_DEGREE_TO_RAD(2000),
		.accel_max_val = IIO_M_S_2_TO_G(32000 << 16),
		.accel_max_scale = 40,
		.temp_scale = 12500, /* 12.5 milli degree Celsius */
		.पूर्णांक_clk = 4250000,
		.max_dec_rate = 4250,
		.filter_freqs = adis16495_def_filter_freqs,
		.has_pps_clk_mode = true,
		.adis_data = ADIS16480_DATA(16497, &adis16495_1_समयouts),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_info adis16480_info = अणु
	.पढ़ो_raw = &adis16480_पढ़ो_raw,
	.ग_लिखो_raw = &adis16480_ग_लिखो_raw,
	.update_scan_mode = adis_update_scan_mode,
	.debugfs_reg_access = adis_debugfs_reg_access,
पूर्ण;

अटल पूर्णांक adis16480_stop_device(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा adis16480 *st = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = adis_ग_लिखो_reg_16(&st->adis, ADIS16480_REG_SLP_CNT, BIT(9));
	अगर (ret)
		dev_err(&indio_dev->dev,
			"Could not power down device: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक adis16480_enable_irq(काष्ठा adis *adis, bool enable)
अणु
	uपूर्णांक16_t val;
	पूर्णांक ret;

	ret = __adis_पढ़ो_reg_16(adis, ADIS16480_REG_FNCTIO_CTRL, &val);
	अगर (ret)
		वापस ret;

	val &= ~ADIS16480_DRDY_EN_MSK;
	val |= ADIS16480_DRDY_EN(enable);

	वापस __adis_ग_लिखो_reg_16(adis, ADIS16480_REG_FNCTIO_CTRL, val);
पूर्ण

अटल पूर्णांक adis16480_config_irq_pin(काष्ठा device_node *of_node,
				    काष्ठा adis16480 *st)
अणु
	काष्ठा irq_data *desc;
	क्रमागत adis16480_पूर्णांक_pin pin;
	अचिन्हित पूर्णांक irq_type;
	uपूर्णांक16_t val;
	पूर्णांक i, irq = 0;

	desc = irq_get_irq_data(st->adis.spi->irq);
	अगर (!desc) अणु
		dev_err(&st->adis.spi->dev, "Could not find IRQ %d\n", irq);
		वापस -EINVAL;
	पूर्ण

	/* Disable data पढ़ोy since the शेष after reset is on */
	val = ADIS16480_DRDY_EN(0);

	/*
	 * Get the पूर्णांकerrupt from the devicetre by पढ़ोing the पूर्णांकerrupt-names
	 * property. If it is not specअगरied, use DIO1 pin as शेष.
	 * According to the datasheet, the factory शेष assigns DIO2 as data
	 * पढ़ोy संकेत. However, in the previous versions of the driver, DIO1
	 * pin was used. So, we should leave it as is since some devices might
	 * be expecting the पूर्णांकerrupt on the wrong physical pin.
	 */
	pin = ADIS16480_PIN_DIO1;
	क्रम (i = 0; i < ARRAY_SIZE(adis16480_पूर्णांक_pin_names); i++) अणु
		irq = of_irq_get_byname(of_node, adis16480_पूर्णांक_pin_names[i]);
		अगर (irq > 0) अणु
			pin = i;
			अवरोध;
		पूर्ण
	पूर्ण

	val |= ADIS16480_DRDY_SEL(pin);

	/*
	 * Get the पूर्णांकerrupt line behaviour. The data पढ़ोy polarity can be
	 * configured as positive or negative, corresponding to
	 * IRQ_TYPE_EDGE_RISING or IRQ_TYPE_EDGE_FALLING respectively.
	 */
	irq_type = irqd_get_trigger_type(desc);
	अगर (irq_type == IRQ_TYPE_EDGE_RISING) अणु /* Default */
		val |= ADIS16480_DRDY_POL(1);
	पूर्ण अन्यथा अगर (irq_type == IRQ_TYPE_EDGE_FALLING) अणु
		val |= ADIS16480_DRDY_POL(0);
	पूर्ण अन्यथा अणु
		dev_err(&st->adis.spi->dev,
			"Invalid interrupt type 0x%x specified\n", irq_type);
		वापस -EINVAL;
	पूर्ण
	/* Write the data पढ़ोy configuration to the FNCTIO_CTRL रेजिस्टर */
	वापस adis_ग_लिखो_reg_16(&st->adis, ADIS16480_REG_FNCTIO_CTRL, val);
पूर्ण

अटल पूर्णांक adis16480_of_get_ext_clk_pin(काष्ठा adis16480 *st,
					काष्ठा device_node *of_node)
अणु
	स्थिर अक्षर *ext_clk_pin;
	क्रमागत adis16480_पूर्णांक_pin pin;
	पूर्णांक i;

	pin = ADIS16480_PIN_DIO2;
	अगर (of_property_पढ़ो_string(of_node, "adi,ext-clk-pin", &ext_clk_pin))
		जाओ clk_input_not_found;

	क्रम (i = 0; i < ARRAY_SIZE(adis16480_पूर्णांक_pin_names); i++) अणु
		अगर (strहालcmp(ext_clk_pin, adis16480_पूर्णांक_pin_names[i]) == 0)
			वापस i;
	पूर्ण

clk_input_not_found:
	dev_info(&st->adis.spi->dev,
		"clk input line not specified, using DIO2\n");
	वापस pin;
पूर्ण

अटल पूर्णांक adis16480_ext_clk_config(काष्ठा adis16480 *st,
				    काष्ठा device_node *of_node,
				    bool enable)
अणु
	अचिन्हित पूर्णांक mode, mask;
	क्रमागत adis16480_पूर्णांक_pin pin;
	uपूर्णांक16_t val;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg_16(&st->adis, ADIS16480_REG_FNCTIO_CTRL, &val);
	अगर (ret)
		वापस ret;

	pin = adis16480_of_get_ext_clk_pin(st, of_node);
	/*
	 * Each DIOx pin supports only one function at a समय. When a single pin
	 * has two assignments, the enable bit क्रम a lower priority function
	 * स्वतःmatically resets to zero (disabling the lower priority function).
	 */
	अगर (pin == ADIS16480_DRDY_SEL(val))
		dev_warn(&st->adis.spi->dev,
			"DIO%x pin supports only one function at a time\n",
			pin + 1);

	mode = ADIS16480_SYNC_EN(enable) | ADIS16480_SYNC_SEL(pin);
	mask = ADIS16480_SYNC_EN_MSK | ADIS16480_SYNC_SEL_MSK;
	/* Only ADIS1649x devices support pps ext घड़ी mode */
	अगर (st->chip_info->has_pps_clk_mode) अणु
		mode |= ADIS16480_SYNC_MODE(st->clk_mode);
		mask |= ADIS16480_SYNC_MODE_MSK;
	पूर्ण

	val &= ~mask;
	val |= mode;

	ret = adis_ग_लिखो_reg_16(&st->adis, ADIS16480_REG_FNCTIO_CTRL, val);
	अगर (ret)
		वापस ret;

	वापस clk_prepare_enable(st->ext_clk);
पूर्ण

अटल पूर्णांक adis16480_get_ext_घड़ीs(काष्ठा adis16480 *st)
अणु
	st->clk_mode = ADIS16480_CLK_INT;
	st->ext_clk = devm_clk_get(&st->adis.spi->dev, "sync");
	अगर (!IS_ERR_OR_शून्य(st->ext_clk)) अणु
		st->clk_mode = ADIS16480_CLK_SYNC;
		वापस 0;
	पूर्ण

	अगर (PTR_ERR(st->ext_clk) != -ENOENT) अणु
		dev_err(&st->adis.spi->dev, "failed to get ext clk\n");
		वापस PTR_ERR(st->ext_clk);
	पूर्ण

	अगर (st->chip_info->has_pps_clk_mode) अणु
		st->ext_clk = devm_clk_get(&st->adis.spi->dev, "pps");
		अगर (!IS_ERR_OR_शून्य(st->ext_clk)) अणु
			st->clk_mode = ADIS16480_CLK_PPS;
			वापस 0;
		पूर्ण

		अगर (PTR_ERR(st->ext_clk) != -ENOENT) अणु
			dev_err(&st->adis.spi->dev, "failed to get ext clk\n");
			वापस PTR_ERR(st->ext_clk);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम adis16480_stop(व्योम *data)
अणु
	adis16480_stop_device(data);
पूर्ण

अटल व्योम adis16480_clk_disable(व्योम *data)
अणु
	clk_disable_unprepare(data);
पूर्ण

अटल पूर्णांक adis16480_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	स्थिर काष्ठा adis_data *adis16480_data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा adis16480 *st;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	spi_set_drvdata(spi, indio_dev);

	st = iio_priv(indio_dev);

	st->chip_info = &adis16480_chip_info[id->driver_data];
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->channels = st->chip_info->channels;
	indio_dev->num_channels = st->chip_info->num_channels;
	indio_dev->info = &adis16480_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	adis16480_data = &st->chip_info->adis_data;

	ret = adis_init(&st->adis, indio_dev, spi, adis16480_data);
	अगर (ret)
		वापस ret;

	ret = __adis_initial_startup(&st->adis);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(&spi->dev, adis16480_stop, indio_dev);
	अगर (ret)
		वापस ret;

	ret = adis16480_config_irq_pin(spi->dev.of_node, st);
	अगर (ret)
		वापस ret;

	ret = adis16480_get_ext_घड़ीs(st);
	अगर (ret)
		वापस ret;

	अगर (!IS_ERR_OR_शून्य(st->ext_clk)) अणु
		ret = adis16480_ext_clk_config(st, spi->dev.of_node, true);
		अगर (ret)
			वापस ret;

		ret = devm_add_action_or_reset(&spi->dev, adis16480_clk_disable, st->ext_clk);
		अगर (ret)
			वापस ret;

		st->clk_freq = clk_get_rate(st->ext_clk);
		st->clk_freq *= 1000; /* micro */
		अगर (st->clk_mode == ADIS16480_CLK_PPS) अणु
			u16 sync_scale;

			/*
			 * In PPS mode, the IMU sample rate is the clk_freq * sync_scale. Hence,
			 * शेष the IMU sample rate to the highest multiple of the input घड़ी
			 * lower than the IMU max sample rate. The पूर्णांकernal sample rate is the
			 * max...
			 */
			sync_scale = st->chip_info->पूर्णांक_clk / st->clk_freq;
			ret = __adis_ग_लिखो_reg_16(&st->adis, ADIS16495_REG_SYNC_SCALE, sync_scale);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		st->clk_freq = st->chip_info->पूर्णांक_clk;
	पूर्ण

	ret = devm_adis_setup_buffer_and_trigger(&st->adis, indio_dev, शून्य);
	अगर (ret)
		वापस ret;

	ret = devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
	अगर (ret)
		वापस ret;

	adis16480_debugfs_init(indio_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id adis16480_ids[] = अणु
	अणु "adis16375", ADIS16375 पूर्ण,
	अणु "adis16480", ADIS16480 पूर्ण,
	अणु "adis16485", ADIS16485 पूर्ण,
	अणु "adis16488", ADIS16488 पूर्ण,
	अणु "adis16490", ADIS16490 पूर्ण,
	अणु "adis16495-1", ADIS16495_1 पूर्ण,
	अणु "adis16495-2", ADIS16495_2 पूर्ण,
	अणु "adis16495-3", ADIS16495_3 पूर्ण,
	अणु "adis16497-1", ADIS16497_1 पूर्ण,
	अणु "adis16497-2", ADIS16497_2 पूर्ण,
	अणु "adis16497-3", ADIS16497_3 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, adis16480_ids);

अटल स्थिर काष्ठा of_device_id adis16480_of_match[] = अणु
	अणु .compatible = "adi,adis16375" पूर्ण,
	अणु .compatible = "adi,adis16480" पूर्ण,
	अणु .compatible = "adi,adis16485" पूर्ण,
	अणु .compatible = "adi,adis16488" पूर्ण,
	अणु .compatible = "adi,adis16490" पूर्ण,
	अणु .compatible = "adi,adis16495-1" पूर्ण,
	अणु .compatible = "adi,adis16495-2" पूर्ण,
	अणु .compatible = "adi,adis16495-3" पूर्ण,
	अणु .compatible = "adi,adis16497-1" पूर्ण,
	अणु .compatible = "adi,adis16497-2" पूर्ण,
	अणु .compatible = "adi,adis16497-3" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, adis16480_of_match);

अटल काष्ठा spi_driver adis16480_driver = अणु
	.driver = अणु
		.name = "adis16480",
		.of_match_table = adis16480_of_match,
	पूर्ण,
	.id_table = adis16480_ids,
	.probe = adis16480_probe,
पूर्ण;
module_spi_driver(adis16480_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Analog Devices ADIS16480 IMU driver");
MODULE_LICENSE("GPL v2");
