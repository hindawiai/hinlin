<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * ADIS16475 IMU driver
 *
 * Copyright 2019 Analog Devices Inc.
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/imu/adis.h>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/irq.h>
#समावेश <linux/lcm.h>
#समावेश <linux/गणित.स>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/property.h>
#समावेश <linux/spi/spi.h>

#घोषणा ADIS16475_REG_DIAG_STAT		0x02
#घोषणा ADIS16475_REG_X_GYRO_L		0x04
#घोषणा ADIS16475_REG_Y_GYRO_L		0x08
#घोषणा ADIS16475_REG_Z_GYRO_L		0x0C
#घोषणा ADIS16475_REG_X_ACCEL_L		0x10
#घोषणा ADIS16475_REG_Y_ACCEL_L		0x14
#घोषणा ADIS16475_REG_Z_ACCEL_L		0x18
#घोषणा ADIS16475_REG_TEMP_OUT		0x1c
#घोषणा ADIS16475_REG_X_GYRO_BIAS_L	0x40
#घोषणा ADIS16475_REG_Y_GYRO_BIAS_L	0x44
#घोषणा ADIS16475_REG_Z_GYRO_BIAS_L	0x48
#घोषणा ADIS16475_REG_X_ACCEL_BIAS_L	0x4c
#घोषणा ADIS16475_REG_Y_ACCEL_BIAS_L	0x50
#घोषणा ADIS16475_REG_Z_ACCEL_BIAS_L	0x54
#घोषणा ADIS16475_REG_FILT_CTRL		0x5c
#घोषणा ADIS16475_FILT_CTRL_MASK	GENMASK(2, 0)
#घोषणा ADIS16475_FILT_CTRL(x)		FIELD_PREP(ADIS16475_FILT_CTRL_MASK, x)
#घोषणा ADIS16475_REG_MSG_CTRL		0x60
#घोषणा ADIS16475_MSG_CTRL_DR_POL_MASK	BIT(0)
#घोषणा ADIS16475_MSG_CTRL_DR_POL(x) \
				FIELD_PREP(ADIS16475_MSG_CTRL_DR_POL_MASK, x)
#घोषणा ADIS16475_SYNC_MODE_MASK	GENMASK(4, 2)
#घोषणा ADIS16475_SYNC_MODE(x)		FIELD_PREP(ADIS16475_SYNC_MODE_MASK, x)
#घोषणा ADIS16475_REG_UP_SCALE		0x62
#घोषणा ADIS16475_REG_DEC_RATE		0x64
#घोषणा ADIS16475_REG_GLOB_CMD		0x68
#घोषणा ADIS16475_REG_FIRM_REV		0x6c
#घोषणा ADIS16475_REG_FIRM_DM		0x6e
#घोषणा ADIS16475_REG_FIRM_Y		0x70
#घोषणा ADIS16475_REG_PROD_ID		0x72
#घोषणा ADIS16475_REG_SERIAL_NUM	0x74
#घोषणा ADIS16475_REG_FLASH_CNT		0x7c
#घोषणा ADIS16500_BURST32_MASK		BIT(9)
#घोषणा ADIS16500_BURST32(x)		FIELD_PREP(ADIS16500_BURST32_MASK, x)
/* number of data elements in burst mode */
#घोषणा ADIS16475_BURST32_MAX_DATA	32
#घोषणा ADIS16475_BURST_MAX_DATA	20
#घोषणा ADIS16475_MAX_SCAN_DATA		20
/* spi max speed in brust mode */
#घोषणा ADIS16475_BURST_MAX_SPEED	1000000
#घोषणा ADIS16475_LSB_DEC_MASK		BIT(0)
#घोषणा ADIS16475_LSB_FIR_MASK		BIT(1)

क्रमागत अणु
	ADIS16475_SYNC_सूचीECT = 1,
	ADIS16475_SYNC_SCALED,
	ADIS16475_SYNC_OUTPUT,
	ADIS16475_SYNC_PULSE = 5,
पूर्ण;

काष्ठा adis16475_sync अणु
	u16 sync_mode;
	u16 min_rate;
	u16 max_rate;
पूर्ण;

काष्ठा adis16475_chip_info अणु
	स्थिर काष्ठा iio_chan_spec *channels;
	स्थिर काष्ठा adis16475_sync *sync;
	स्थिर काष्ठा adis_data adis_data;
	स्थिर अक्षर *name;
	u32 num_channels;
	u32 gyro_max_val;
	u32 gyro_max_scale;
	u32 accel_max_val;
	u32 accel_max_scale;
	u32 temp_scale;
	u32 पूर्णांक_clk;
	u16 max_dec;
	u8 num_sync;
	bool has_burst32;
पूर्ण;

काष्ठा adis16475 अणु
	स्थिर काष्ठा adis16475_chip_info *info;
	काष्ठा adis adis;
	u32 clk_freq;
	bool burst32;
	अचिन्हित दीर्घ lsb_flag;
	u16 sync_mode;
	/* Alignment needed क्रम the बारtamp */
	__be16 data[ADIS16475_MAX_SCAN_DATA] __aligned(8);
पूर्ण;

क्रमागत अणु
	ADIS16475_SCAN_GYRO_X,
	ADIS16475_SCAN_GYRO_Y,
	ADIS16475_SCAN_GYRO_Z,
	ADIS16475_SCAN_ACCEL_X,
	ADIS16475_SCAN_ACCEL_Y,
	ADIS16475_SCAN_ACCEL_Z,
	ADIS16475_SCAN_TEMP,
	ADIS16475_SCAN_DIAG_S_FLAGS,
	ADIS16475_SCAN_CRC_FAILURE,
पूर्ण;

अटल bool low_rate_allow;
module_param(low_rate_allow, bool, 0444);
MODULE_PARM_DESC(low_rate_allow,
		 "Allow IMU rates below the minimum advisable when external clk is used in SCALED mode (default: N)");

#अगर_घोषित CONFIG_DEBUG_FS
अटल sमाप_प्रकार adis16475_show_firmware_revision(काष्ठा file *file,
						अक्षर __user *userbuf,
						माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा adis16475 *st = file->निजी_data;
	अक्षर buf[7];
	माप_प्रकार len;
	u16 rev;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg_16(&st->adis, ADIS16475_REG_FIRM_REV, &rev);
	अगर (ret)
		वापस ret;

	len = scnम_लिखो(buf, माप(buf), "%x.%x\n", rev >> 8, rev & 0xff);

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations adis16475_firmware_revision_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = adis16475_show_firmware_revision,
	.llseek = शेष_llseek,
	.owner = THIS_MODULE,
पूर्ण;

अटल sमाप_प्रकार adis16475_show_firmware_date(काष्ठा file *file,
					    अक्षर __user *userbuf,
					    माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा adis16475 *st = file->निजी_data;
	u16 md, year;
	अक्षर buf[12];
	माप_प्रकार len;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg_16(&st->adis, ADIS16475_REG_FIRM_Y, &year);
	अगर (ret)
		वापस ret;

	ret = adis_पढ़ो_reg_16(&st->adis, ADIS16475_REG_FIRM_DM, &md);
	अगर (ret)
		वापस ret;

	len = snम_लिखो(buf, माप(buf), "%.2x-%.2x-%.4x\n", md >> 8, md & 0xff,
		       year);

	वापस simple_पढ़ो_from_buffer(userbuf, count, ppos, buf, len);
पूर्ण

अटल स्थिर काष्ठा file_operations adis16475_firmware_date_fops = अणु
	.खोलो = simple_खोलो,
	.पढ़ो = adis16475_show_firmware_date,
	.llseek = शेष_llseek,
	.owner = THIS_MODULE,
पूर्ण;

अटल पूर्णांक adis16475_show_serial_number(व्योम *arg, u64 *val)
अणु
	काष्ठा adis16475 *st = arg;
	u16 serial;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg_16(&st->adis, ADIS16475_REG_SERIAL_NUM, &serial);
	अगर (ret)
		वापस ret;

	*val = serial;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(adis16475_serial_number_fops,
			 adis16475_show_serial_number, शून्य, "0x%.4llx\n");

अटल पूर्णांक adis16475_show_product_id(व्योम *arg, u64 *val)
अणु
	काष्ठा adis16475 *st = arg;
	u16 prod_id;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg_16(&st->adis, ADIS16475_REG_PROD_ID, &prod_id);
	अगर (ret)
		वापस ret;

	*val = prod_id;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(adis16475_product_id_fops,
			 adis16475_show_product_id, शून्य, "%llu\n");

अटल पूर्णांक adis16475_show_flash_count(व्योम *arg, u64 *val)
अणु
	काष्ठा adis16475 *st = arg;
	u32 flash_count;
	पूर्णांक ret;

	ret = adis_पढ़ो_reg_32(&st->adis, ADIS16475_REG_FLASH_CNT,
			       &flash_count);
	अगर (ret)
		वापस ret;

	*val = flash_count;

	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(adis16475_flash_count_fops,
			 adis16475_show_flash_count, शून्य, "%lld\n");

अटल व्योम adis16475_debugfs_init(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा adis16475 *st = iio_priv(indio_dev);
	काष्ठा dentry *d = iio_get_debugfs_dentry(indio_dev);

	debugfs_create_file_unsafe("serial_number", 0400,
				   d, st, &adis16475_serial_number_fops);
	debugfs_create_file_unsafe("product_id", 0400,
				   d, st, &adis16475_product_id_fops);
	debugfs_create_file_unsafe("flash_count", 0400,
				   d, st, &adis16475_flash_count_fops);
	debugfs_create_file("firmware_revision", 0400,
			    d, st, &adis16475_firmware_revision_fops);
	debugfs_create_file("firmware_date", 0400, d,
			    st, &adis16475_firmware_date_fops);
पूर्ण
#अन्यथा
अटल व्योम adis16475_debugfs_init(काष्ठा iio_dev *indio_dev)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक adis16475_get_freq(काष्ठा adis16475 *st, u32 *freq)
अणु
	पूर्णांक ret;
	u16 dec;
	u32 sample_rate = st->clk_freq;

	adis_dev_lock(&st->adis);

	अगर (st->sync_mode == ADIS16475_SYNC_SCALED) अणु
		u16 sync_scale;

		ret = __adis_पढ़ो_reg_16(&st->adis, ADIS16475_REG_UP_SCALE, &sync_scale);
		अगर (ret)
			जाओ error;

		sample_rate = st->clk_freq * sync_scale;
	पूर्ण

	ret = __adis_पढ़ो_reg_16(&st->adis, ADIS16475_REG_DEC_RATE, &dec);
	अगर (ret)
		जाओ error;

	adis_dev_unlock(&st->adis);

	*freq = DIV_ROUND_CLOSEST(sample_rate, dec + 1);

	वापस 0;
error:
	adis_dev_unlock(&st->adis);
	वापस ret;
पूर्ण

अटल पूर्णांक adis16475_set_freq(काष्ठा adis16475 *st, स्थिर u32 freq)
अणु
	u16 dec;
	पूर्णांक ret;
	u32 sample_rate = st->clk_freq;

	अगर (!freq)
		वापस -EINVAL;

	adis_dev_lock(&st->adis);
	/*
	 * When using sync scaled mode, the input घड़ी needs to be scaled so that we have
	 * an IMU sample rate between (optimally) 1900 and 2100. After this, we can use the
	 * decimation filter to lower the sampling rate in order to get what the user wants.
	 * Optimally, the user sample rate is a multiple of both the IMU sample rate and
	 * the input घड़ी. Hence, calculating the sync_scale dynamically gives us better
	 * chances of achieving a perfect/पूर्णांकeger value क्रम DEC_RATE. The math here is:
	 *	1. lcm of the input घड़ी and the desired output rate.
	 *	2. get the highest multiple of the previous result lower than the adis max rate.
	 *	3. The last result becomes the IMU sample rate. Use that to calculate SYNC_SCALE
	 *	   and DEC_RATE (to get the user output rate)
	 */
	अगर (st->sync_mode == ADIS16475_SYNC_SCALED) अणु
		अचिन्हित दीर्घ scaled_rate = lcm(st->clk_freq, freq);
		पूर्णांक sync_scale;

		/*
		 * If lcm is bigger than the IMU maximum sampling rate there's no perfect
		 * solution. In this हाल, we get the highest multiple of the input घड़ी
		 * lower than the IMU max sample rate.
		 */
		अगर (scaled_rate > 2100000)
			scaled_rate = 2100000 / st->clk_freq * st->clk_freq;
		अन्यथा
			scaled_rate = 2100000 / scaled_rate * scaled_rate;

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
		अगर (scaled_rate < 1900000 && !low_rate_allow)
			scaled_rate = roundup(1900000, st->clk_freq);

		sync_scale = scaled_rate / st->clk_freq;
		ret = __adis_ग_लिखो_reg_16(&st->adis, ADIS16475_REG_UP_SCALE, sync_scale);
		अगर (ret)
			जाओ error;

		sample_rate = scaled_rate;
	पूर्ण

	dec = DIV_ROUND_CLOSEST(sample_rate, freq);

	अगर (dec)
		dec--;

	अगर (dec > st->info->max_dec)
		dec = st->info->max_dec;

	ret = adis_ग_लिखो_reg_16(&st->adis, ADIS16475_REG_DEC_RATE, dec);
	अगर (ret)
		जाओ error;

	/*
	 * If decimation is used, then gyro and accel data will have meaningful
	 * bits on the LSB रेजिस्टरs. This info is used on the trigger handler.
	 */
	assign_bit(ADIS16475_LSB_DEC_MASK, &st->lsb_flag, dec);

	वापस 0;
error:
	adis_dev_unlock(&st->adis);
	वापस ret;
पूर्ण

/* The values are approximated. */
अटल स्थिर u32 adis16475_3db_freqs[] = अणु
	[0] = 720, /* Filter disabled, full BW (~720Hz) */
	[1] = 360,
	[2] = 164,
	[3] = 80,
	[4] = 40,
	[5] = 20,
	[6] = 10,
पूर्ण;

अटल पूर्णांक adis16475_get_filter(काष्ठा adis16475 *st, u32 *filter)
अणु
	u16 filter_sz;
	पूर्णांक ret;
	स्थिर पूर्णांक mask = ADIS16475_FILT_CTRL_MASK;

	ret = adis_पढ़ो_reg_16(&st->adis, ADIS16475_REG_FILT_CTRL, &filter_sz);
	अगर (ret)
		वापस ret;

	*filter = adis16475_3db_freqs[filter_sz & mask];

	वापस 0;
पूर्ण

अटल पूर्णांक adis16475_set_filter(काष्ठा adis16475 *st, स्थिर u32 filter)
अणु
	पूर्णांक i = ARRAY_SIZE(adis16475_3db_freqs);
	पूर्णांक ret;

	जबतक (--i) अणु
		अगर (adis16475_3db_freqs[i] >= filter)
			अवरोध;
	पूर्ण

	ret = adis_ग_लिखो_reg_16(&st->adis, ADIS16475_REG_FILT_CTRL,
				ADIS16475_FILT_CTRL(i));
	अगर (ret)
		वापस ret;

	/*
	 * If FIR is used, then gyro and accel data will have meaningful
	 * bits on the LSB रेजिस्टरs. This info is used on the trigger handler.
	 */
	assign_bit(ADIS16475_LSB_FIR_MASK, &st->lsb_flag, i);

	वापस 0;
पूर्ण

अटल स्थिर u32 adis16475_calib_regs[] = अणु
	[ADIS16475_SCAN_GYRO_X] = ADIS16475_REG_X_GYRO_BIAS_L,
	[ADIS16475_SCAN_GYRO_Y] = ADIS16475_REG_Y_GYRO_BIAS_L,
	[ADIS16475_SCAN_GYRO_Z] = ADIS16475_REG_Z_GYRO_BIAS_L,
	[ADIS16475_SCAN_ACCEL_X] = ADIS16475_REG_X_ACCEL_BIAS_L,
	[ADIS16475_SCAN_ACCEL_Y] = ADIS16475_REG_Y_ACCEL_BIAS_L,
	[ADIS16475_SCAN_ACCEL_Z] = ADIS16475_REG_Z_ACCEL_BIAS_L,
पूर्ण;

अटल पूर्णांक adis16475_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			      स्थिर काष्ठा iio_chan_spec *chan,
			      पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	काष्ठा adis16475 *st = iio_priv(indio_dev);
	पूर्णांक ret;
	u32 पंचांगp;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस adis_single_conversion(indio_dev, chan, 0, val);
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_ANGL_VEL:
			*val = st->info->gyro_max_val;
			*val2 = st->info->gyro_max_scale;
			वापस IIO_VAL_FRACTIONAL;
		हाल IIO_ACCEL:
			*val = st->info->accel_max_val;
			*val2 = st->info->accel_max_scale;
			वापस IIO_VAL_FRACTIONAL;
		हाल IIO_TEMP:
			*val = st->info->temp_scale;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_CALIBBIAS:
		ret = adis_पढ़ो_reg_32(&st->adis,
				       adis16475_calib_regs[chan->scan_index],
				       val);
		अगर (ret)
			वापस ret;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		ret = adis16475_get_filter(st, val);
		अगर (ret)
			वापस ret;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret = adis16475_get_freq(st, &पंचांगp);
		अगर (ret)
			वापस ret;

		*val = पंचांगp / 1000;
		*val2 = (पंचांगp % 1000) * 1000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक adis16475_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       स्थिर काष्ठा iio_chan_spec *chan,
			       पूर्णांक val, पूर्णांक val2, दीर्घ info)
अणु
	काष्ठा adis16475 *st = iio_priv(indio_dev);
	u32 पंचांगp;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		पंचांगp = val * 1000 + val2 / 1000;
		वापस adis16475_set_freq(st, पंचांगp);
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		वापस adis16475_set_filter(st, val);
	हाल IIO_CHAN_INFO_CALIBBIAS:
		वापस adis_ग_लिखो_reg_32(&st->adis,
					 adis16475_calib_regs[chan->scan_index],
					 val);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

#घोषणा ADIS16475_MOD_CHAN(_type, _mod, _address, _si, _r_bits, _s_bits) \
	अणु \
		.type = (_type), \
		.modअगरied = 1, \
		.channel2 = (_mod), \
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
			BIT(IIO_CHAN_INFO_CALIBBIAS), \
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ) | \
			BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY), \
		.address = (_address), \
		.scan_index = (_si), \
		.scan_type = अणु \
			.sign = 's', \
			.realbits = (_r_bits), \
			.storagebits = (_s_bits), \
			.endianness = IIO_BE, \
		पूर्ण, \
	पूर्ण

#घोषणा ADIS16475_GYRO_CHANNEL(_mod) \
	ADIS16475_MOD_CHAN(IIO_ANGL_VEL, IIO_MOD_ ## _mod, \
			   ADIS16475_REG_ ## _mod ## _GYRO_L, \
			   ADIS16475_SCAN_GYRO_ ## _mod, 32, 32)

#घोषणा ADIS16475_ACCEL_CHANNEL(_mod) \
	ADIS16475_MOD_CHAN(IIO_ACCEL, IIO_MOD_ ## _mod, \
			   ADIS16475_REG_ ## _mod ## _ACCEL_L, \
			   ADIS16475_SCAN_ACCEL_ ## _mod, 32, 32)

#घोषणा ADIS16475_TEMP_CHANNEL() अणु \
		.type = IIO_TEMP, \
		.indexed = 1, \
		.channel = 0, \
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
			BIT(IIO_CHAN_INFO_SCALE), \
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ) | \
			BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY), \
		.address = ADIS16475_REG_TEMP_OUT, \
		.scan_index = ADIS16475_SCAN_TEMP, \
		.scan_type = अणु \
			.sign = 's', \
			.realbits = 16, \
			.storagebits = 16, \
			.endianness = IIO_BE, \
		पूर्ण, \
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec adis16475_channels[] = अणु
	ADIS16475_GYRO_CHANNEL(X),
	ADIS16475_GYRO_CHANNEL(Y),
	ADIS16475_GYRO_CHANNEL(Z),
	ADIS16475_ACCEL_CHANNEL(X),
	ADIS16475_ACCEL_CHANNEL(Y),
	ADIS16475_ACCEL_CHANNEL(Z),
	ADIS16475_TEMP_CHANNEL(),
	IIO_CHAN_SOFT_TIMESTAMP(7)
पूर्ण;

क्रमागत adis16475_variant अणु
	ADIS16470,
	ADIS16475_1,
	ADIS16475_2,
	ADIS16475_3,
	ADIS16477_1,
	ADIS16477_2,
	ADIS16477_3,
	ADIS16465_1,
	ADIS16465_2,
	ADIS16465_3,
	ADIS16467_1,
	ADIS16467_2,
	ADIS16467_3,
	ADIS16500,
	ADIS16505_1,
	ADIS16505_2,
	ADIS16505_3,
	ADIS16507_1,
	ADIS16507_2,
	ADIS16507_3,
पूर्ण;

क्रमागत अणु
	ADIS16475_DIAG_STAT_DATA_PATH = 1,
	ADIS16475_DIAG_STAT_FLASH_MEM,
	ADIS16475_DIAG_STAT_SPI,
	ADIS16475_DIAG_STAT_STANDBY,
	ADIS16475_DIAG_STAT_SENSOR,
	ADIS16475_DIAG_STAT_MEMORY,
	ADIS16475_DIAG_STAT_CLK,
पूर्ण;

अटल स्थिर अक्षर * स्थिर adis16475_status_error_msgs[] = अणु
	[ADIS16475_DIAG_STAT_DATA_PATH] = "Data Path Overrun",
	[ADIS16475_DIAG_STAT_FLASH_MEM] = "Flash memory update failure",
	[ADIS16475_DIAG_STAT_SPI] = "SPI communication error",
	[ADIS16475_DIAG_STAT_STANDBY] = "Standby mode",
	[ADIS16475_DIAG_STAT_SENSOR] = "Sensor failure",
	[ADIS16475_DIAG_STAT_MEMORY] = "Memory failure",
	[ADIS16475_DIAG_STAT_CLK] = "Clock error",
पूर्ण;

अटल पूर्णांक adis16475_enable_irq(काष्ठा adis *adis, bool enable)
अणु
	/*
	 * There is no way to gate the data-पढ़ोy संकेत पूर्णांकernally inside the
	 * ADIS16475. We can only control it's polarity...
	 */
	अगर (enable)
		enable_irq(adis->spi->irq);
	अन्यथा
		disable_irq(adis->spi->irq);

	वापस 0;
पूर्ण

#घोषणा ADIS16475_DATA(_prod_id, _समयouts)				\
अणु									\
	.msc_ctrl_reg = ADIS16475_REG_MSG_CTRL,				\
	.glob_cmd_reg = ADIS16475_REG_GLOB_CMD,				\
	.diag_stat_reg = ADIS16475_REG_DIAG_STAT,			\
	.prod_id_reg = ADIS16475_REG_PROD_ID,				\
	.prod_id = (_prod_id),						\
	.self_test_mask = BIT(2),					\
	.self_test_reg = ADIS16475_REG_GLOB_CMD,			\
	.cs_change_delay = 16,						\
	.पढ़ो_delay = 5,						\
	.ग_लिखो_delay = 5,						\
	.status_error_msgs = adis16475_status_error_msgs,		\
	.status_error_mask = BIT(ADIS16475_DIAG_STAT_DATA_PATH) |	\
		BIT(ADIS16475_DIAG_STAT_FLASH_MEM) |			\
		BIT(ADIS16475_DIAG_STAT_SPI) |				\
		BIT(ADIS16475_DIAG_STAT_STANDBY) |			\
		BIT(ADIS16475_DIAG_STAT_SENSOR) |			\
		BIT(ADIS16475_DIAG_STAT_MEMORY) |			\
		BIT(ADIS16475_DIAG_STAT_CLK),				\
	.enable_irq = adis16475_enable_irq,				\
	.समयouts = (_समयouts),					\
	.burst_reg_cmd = ADIS16475_REG_GLOB_CMD,			\
	.burst_len = ADIS16475_BURST_MAX_DATA,				\
	.burst_max_len = ADIS16475_BURST32_MAX_DATA			\
पूर्ण

अटल स्थिर काष्ठा adis16475_sync adis16475_sync_mode[] = अणु
	अणु ADIS16475_SYNC_OUTPUT पूर्ण,
	अणु ADIS16475_SYNC_सूचीECT, 1900, 2100 पूर्ण,
	अणु ADIS16475_SYNC_SCALED, 1, 128 पूर्ण,
	अणु ADIS16475_SYNC_PULSE, 1000, 2100 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा adis_समयout adis16475_समयouts = अणु
	.reset_ms = 200,
	.sw_reset_ms = 200,
	.self_test_ms = 20,
पूर्ण;

अटल स्थिर काष्ठा adis_समयout adis1650x_समयouts = अणु
	.reset_ms = 260,
	.sw_reset_ms = 260,
	.self_test_ms = 30,
पूर्ण;

अटल स्थिर काष्ठा adis16475_chip_info adis16475_chip_info[] = अणु
	[ADIS16470] = अणु
		.name = "adis16470",
		.num_channels = ARRAY_SIZE(adis16475_channels),
		.channels = adis16475_channels,
		.gyro_max_val = 1,
		.gyro_max_scale = IIO_RAD_TO_DEGREE(10 << 16),
		.accel_max_val = 1,
		.accel_max_scale = IIO_M_S_2_TO_G(800 << 16),
		.temp_scale = 100,
		.पूर्णांक_clk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = ARRAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16470, &adis16475_समयouts),
	पूर्ण,
	[ADIS16475_1] = अणु
		.name = "adis16475-1",
		.num_channels = ARRAY_SIZE(adis16475_channels),
		.channels = adis16475_channels,
		.gyro_max_val = 1,
		.gyro_max_scale = IIO_RAD_TO_DEGREE(160 << 16),
		.accel_max_val = 1,
		.accel_max_scale = IIO_M_S_2_TO_G(4000 << 16),
		.temp_scale = 100,
		.पूर्णांक_clk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = ARRAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16475, &adis16475_समयouts),
	पूर्ण,
	[ADIS16475_2] = अणु
		.name = "adis16475-2",
		.num_channels = ARRAY_SIZE(adis16475_channels),
		.channels = adis16475_channels,
		.gyro_max_val = 1,
		.gyro_max_scale = IIO_RAD_TO_DEGREE(40 << 16),
		.accel_max_val = 1,
		.accel_max_scale = IIO_M_S_2_TO_G(4000 << 16),
		.temp_scale = 100,
		.पूर्णांक_clk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = ARRAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16475, &adis16475_समयouts),
	पूर्ण,
	[ADIS16475_3] = अणु
		.name = "adis16475-3",
		.num_channels = ARRAY_SIZE(adis16475_channels),
		.channels = adis16475_channels,
		.gyro_max_val = 1,
		.gyro_max_scale = IIO_RAD_TO_DEGREE(10 << 16),
		.accel_max_val = 1,
		.accel_max_scale = IIO_M_S_2_TO_G(4000 << 16),
		.temp_scale = 100,
		.पूर्णांक_clk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = ARRAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16475, &adis16475_समयouts),
	पूर्ण,
	[ADIS16477_1] = अणु
		.name = "adis16477-1",
		.num_channels = ARRAY_SIZE(adis16475_channels),
		.channels = adis16475_channels,
		.gyro_max_val = 1,
		.gyro_max_scale = IIO_RAD_TO_DEGREE(160 << 16),
		.accel_max_val = 1,
		.accel_max_scale = IIO_M_S_2_TO_G(800 << 16),
		.temp_scale = 100,
		.पूर्णांक_clk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = ARRAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16477, &adis16475_समयouts),
	पूर्ण,
	[ADIS16477_2] = अणु
		.name = "adis16477-2",
		.num_channels = ARRAY_SIZE(adis16475_channels),
		.channels = adis16475_channels,
		.gyro_max_val = 1,
		.gyro_max_scale = IIO_RAD_TO_DEGREE(40 << 16),
		.accel_max_val = 1,
		.accel_max_scale = IIO_M_S_2_TO_G(800 << 16),
		.temp_scale = 100,
		.पूर्णांक_clk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = ARRAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16477, &adis16475_समयouts),
	पूर्ण,
	[ADIS16477_3] = अणु
		.name = "adis16477-3",
		.num_channels = ARRAY_SIZE(adis16475_channels),
		.channels = adis16475_channels,
		.gyro_max_val = 1,
		.gyro_max_scale = IIO_RAD_TO_DEGREE(10 << 16),
		.accel_max_val = 1,
		.accel_max_scale = IIO_M_S_2_TO_G(800 << 16),
		.temp_scale = 100,
		.पूर्णांक_clk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = ARRAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16477, &adis16475_समयouts),
	पूर्ण,
	[ADIS16465_1] = अणु
		.name = "adis16465-1",
		.num_channels = ARRAY_SIZE(adis16475_channels),
		.channels = adis16475_channels,
		.gyro_max_val = 1,
		.gyro_max_scale = IIO_RAD_TO_DEGREE(160 << 16),
		.accel_max_val = 1,
		.accel_max_scale = IIO_M_S_2_TO_G(4000 << 16),
		.temp_scale = 100,
		.पूर्णांक_clk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = ARRAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16465, &adis16475_समयouts),
	पूर्ण,
	[ADIS16465_2] = अणु
		.name = "adis16465-2",
		.num_channels = ARRAY_SIZE(adis16475_channels),
		.channels = adis16475_channels,
		.gyro_max_val = 1,
		.gyro_max_scale = IIO_RAD_TO_DEGREE(40 << 16),
		.accel_max_val = 1,
		.accel_max_scale = IIO_M_S_2_TO_G(4000 << 16),
		.temp_scale = 100,
		.पूर्णांक_clk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = ARRAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16465, &adis16475_समयouts),
	पूर्ण,
	[ADIS16465_3] = अणु
		.name = "adis16465-3",
		.num_channels = ARRAY_SIZE(adis16475_channels),
		.channels = adis16475_channels,
		.gyro_max_val = 1,
		.gyro_max_scale = IIO_RAD_TO_DEGREE(10 << 16),
		.accel_max_val = 1,
		.accel_max_scale = IIO_M_S_2_TO_G(4000 << 16),
		.temp_scale = 100,
		.पूर्णांक_clk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = ARRAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16465, &adis16475_समयouts),
	पूर्ण,
	[ADIS16467_1] = अणु
		.name = "adis16467-1",
		.num_channels = ARRAY_SIZE(adis16475_channels),
		.channels = adis16475_channels,
		.gyro_max_val = 1,
		.gyro_max_scale = IIO_RAD_TO_DEGREE(160 << 16),
		.accel_max_val = 1,
		.accel_max_scale = IIO_M_S_2_TO_G(800 << 16),
		.temp_scale = 100,
		.पूर्णांक_clk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = ARRAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16467, &adis16475_समयouts),
	पूर्ण,
	[ADIS16467_2] = अणु
		.name = "adis16467-2",
		.num_channels = ARRAY_SIZE(adis16475_channels),
		.channels = adis16475_channels,
		.gyro_max_val = 1,
		.gyro_max_scale = IIO_RAD_TO_DEGREE(40 << 16),
		.accel_max_val = 1,
		.accel_max_scale = IIO_M_S_2_TO_G(800 << 16),
		.temp_scale = 100,
		.पूर्णांक_clk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = ARRAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16467, &adis16475_समयouts),
	पूर्ण,
	[ADIS16467_3] = अणु
		.name = "adis16467-3",
		.num_channels = ARRAY_SIZE(adis16475_channels),
		.channels = adis16475_channels,
		.gyro_max_val = 1,
		.gyro_max_scale = IIO_RAD_TO_DEGREE(10 << 16),
		.accel_max_val = 1,
		.accel_max_scale = IIO_M_S_2_TO_G(800 << 16),
		.temp_scale = 100,
		.पूर्णांक_clk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		.num_sync = ARRAY_SIZE(adis16475_sync_mode),
		.adis_data = ADIS16475_DATA(16467, &adis16475_समयouts),
	पूर्ण,
	[ADIS16500] = अणु
		.name = "adis16500",
		.num_channels = ARRAY_SIZE(adis16475_channels),
		.channels = adis16475_channels,
		.gyro_max_val = 1,
		.gyro_max_scale = IIO_RAD_TO_DEGREE(10 << 16),
		.accel_max_val = 392,
		.accel_max_scale = 32000 << 16,
		.temp_scale = 100,
		.पूर्णांक_clk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		/* pulse sync not supported */
		.num_sync = ARRAY_SIZE(adis16475_sync_mode) - 1,
		.has_burst32 = true,
		.adis_data = ADIS16475_DATA(16500, &adis1650x_समयouts),
	पूर्ण,
	[ADIS16505_1] = अणु
		.name = "adis16505-1",
		.num_channels = ARRAY_SIZE(adis16475_channels),
		.channels = adis16475_channels,
		.gyro_max_val = 1,
		.gyro_max_scale = IIO_RAD_TO_DEGREE(160 << 16),
		.accel_max_val = 78,
		.accel_max_scale = 32000 << 16,
		.temp_scale = 100,
		.पूर्णांक_clk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		/* pulse sync not supported */
		.num_sync = ARRAY_SIZE(adis16475_sync_mode) - 1,
		.has_burst32 = true,
		.adis_data = ADIS16475_DATA(16505, &adis1650x_समयouts),
	पूर्ण,
	[ADIS16505_2] = अणु
		.name = "adis16505-2",
		.num_channels = ARRAY_SIZE(adis16475_channels),
		.channels = adis16475_channels,
		.gyro_max_val = 1,
		.gyro_max_scale = IIO_RAD_TO_DEGREE(40 << 16),
		.accel_max_val = 78,
		.accel_max_scale = 32000 << 16,
		.temp_scale = 100,
		.पूर्णांक_clk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		/* pulse sync not supported */
		.num_sync = ARRAY_SIZE(adis16475_sync_mode) - 1,
		.has_burst32 = true,
		.adis_data = ADIS16475_DATA(16505, &adis1650x_समयouts),
	पूर्ण,
	[ADIS16505_3] = अणु
		.name = "adis16505-3",
		.num_channels = ARRAY_SIZE(adis16475_channels),
		.channels = adis16475_channels,
		.gyro_max_val = 1,
		.gyro_max_scale = IIO_RAD_TO_DEGREE(10 << 16),
		.accel_max_val = 78,
		.accel_max_scale = 32000 << 16,
		.temp_scale = 100,
		.पूर्णांक_clk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		/* pulse sync not supported */
		.num_sync = ARRAY_SIZE(adis16475_sync_mode) - 1,
		.has_burst32 = true,
		.adis_data = ADIS16475_DATA(16505, &adis1650x_समयouts),
	पूर्ण,
	[ADIS16507_1] = अणु
		.name = "adis16507-1",
		.num_channels = ARRAY_SIZE(adis16475_channels),
		.channels = adis16475_channels,
		.gyro_max_val = 1,
		.gyro_max_scale = IIO_RAD_TO_DEGREE(160 << 16),
		.accel_max_val = 392,
		.accel_max_scale = 32000 << 16,
		.temp_scale = 100,
		.पूर्णांक_clk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		/* pulse sync not supported */
		.num_sync = ARRAY_SIZE(adis16475_sync_mode) - 1,
		.has_burst32 = true,
		.adis_data = ADIS16475_DATA(16507, &adis1650x_समयouts),
	पूर्ण,
	[ADIS16507_2] = अणु
		.name = "adis16507-2",
		.num_channels = ARRAY_SIZE(adis16475_channels),
		.channels = adis16475_channels,
		.gyro_max_val = 1,
		.gyro_max_scale = IIO_RAD_TO_DEGREE(40 << 16),
		.accel_max_val = 392,
		.accel_max_scale = 32000 << 16,
		.temp_scale = 100,
		.पूर्णांक_clk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		/* pulse sync not supported */
		.num_sync = ARRAY_SIZE(adis16475_sync_mode) - 1,
		.has_burst32 = true,
		.adis_data = ADIS16475_DATA(16507, &adis1650x_समयouts),
	पूर्ण,
	[ADIS16507_3] = अणु
		.name = "adis16507-3",
		.num_channels = ARRAY_SIZE(adis16475_channels),
		.channels = adis16475_channels,
		.gyro_max_val = 1,
		.gyro_max_scale = IIO_RAD_TO_DEGREE(10 << 16),
		.accel_max_val = 392,
		.accel_max_scale = 32000 << 16,
		.temp_scale = 100,
		.पूर्णांक_clk = 2000,
		.max_dec = 1999,
		.sync = adis16475_sync_mode,
		/* pulse sync not supported */
		.num_sync = ARRAY_SIZE(adis16475_sync_mode) - 1,
		.has_burst32 = true,
		.adis_data = ADIS16475_DATA(16507, &adis1650x_समयouts),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_info adis16475_info = अणु
	.पढ़ो_raw = &adis16475_पढ़ो_raw,
	.ग_लिखो_raw = &adis16475_ग_लिखो_raw,
	.update_scan_mode = adis_update_scan_mode,
	.debugfs_reg_access = adis_debugfs_reg_access,
पूर्ण;

अटल bool adis16475_validate_crc(स्थिर u8 *buffer, u16 crc,
				   स्थिर bool burst32)
अणु
	पूर्णांक i;
	/* extra 6 elements क्रम low gyro and accel */
	स्थिर u16 sz = burst32 ? ADIS16475_BURST32_MAX_DATA :
		ADIS16475_BURST_MAX_DATA;

	क्रम (i = 0; i < sz - 2; i++)
		crc -= buffer[i];

	वापस crc == 0;
पूर्ण

अटल व्योम adis16475_burst32_check(काष्ठा adis16475 *st)
अणु
	पूर्णांक ret;
	काष्ठा adis *adis = &st->adis;

	अगर (!st->info->has_burst32)
		वापस;

	अगर (st->lsb_flag && !st->burst32) अणु
		स्थिर u16 en = ADIS16500_BURST32(1);

		ret = __adis_update_bits(&st->adis, ADIS16475_REG_MSG_CTRL,
					 ADIS16500_BURST32_MASK, en);
		अगर (ret)
			वापस;

		st->burst32 = true;

		/*
		 * In 32-bit mode we need extra 2 bytes क्रम all gyro
		 * and accel channels.
		 */
		adis->burst_extra_len = 6 * माप(u16);
		adis->xfer[1].len += 6 * माप(u16);
		dev_dbg(&adis->spi->dev, "Enable burst32 mode, xfer:%d",
			adis->xfer[1].len);

	पूर्ण अन्यथा अगर (!st->lsb_flag && st->burst32) अणु
		स्थिर u16 en = ADIS16500_BURST32(0);

		ret = __adis_update_bits(&st->adis, ADIS16475_REG_MSG_CTRL,
					 ADIS16500_BURST32_MASK, en);
		अगर (ret)
			वापस;

		st->burst32 = false;

		/* Remove the extra bits */
		adis->burst_extra_len = 0;
		adis->xfer[1].len -= 6 * माप(u16);
		dev_dbg(&adis->spi->dev, "Disable burst32 mode, xfer:%d\n",
			adis->xfer[1].len);
	पूर्ण
पूर्ण

अटल irqवापस_t adis16475_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा adis16475 *st = iio_priv(indio_dev);
	काष्ठा adis *adis = &st->adis;
	पूर्णांक ret, bit, i = 0;
	__be16 *buffer;
	u16 crc;
	bool valid;
	/* offset until the first element after gyro and accel */
	स्थिर u8 offset = st->burst32 ? 13 : 7;
	स्थिर u32 cached_spi_speed_hz = adis->spi->max_speed_hz;

	adis->spi->max_speed_hz = ADIS16475_BURST_MAX_SPEED;

	ret = spi_sync(adis->spi, &adis->msg);
	अगर (ret)
		वापस ret;

	adis->spi->max_speed_hz = cached_spi_speed_hz;
	buffer = adis->buffer;

	crc = be16_to_cpu(buffer[offset + 2]);
	valid = adis16475_validate_crc(adis->buffer, crc, st->burst32);
	अगर (!valid) अणु
		dev_err(&adis->spi->dev, "Invalid crc\n");
		जाओ check_burst32;
	पूर्ण

	क्रम_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->masklength) अणु
		/*
		 * When burst mode is used, प्रणाली flags is the first data
		 * channel in the sequence, but the scan index is 7.
		 */
		चयन (bit) अणु
		हाल ADIS16475_SCAN_TEMP:
			st->data[i++] = buffer[offset];
			अवरोध;
		हाल ADIS16475_SCAN_GYRO_X ... ADIS16475_SCAN_ACCEL_Z:
			/*
			 * The first 2 bytes on the received data are the
			 * DIAG_STAT reg, hence the +1 offset here...
			 */
			अगर (st->burst32) अणु
				/* upper 16 */
				st->data[i++] = buffer[bit * 2 + 2];
				/* lower 16 */
				st->data[i++] = buffer[bit * 2 + 1];
			पूर्ण अन्यथा अणु
				st->data[i++] = buffer[bit + 1];
				/*
				 * Don't bother in करोing the manual पढ़ो अगर the
				 * device supports burst32. burst32 will be
				 * enabled in the next call to
				 * adis16475_burst32_check()...
				 */
				अगर (st->lsb_flag && !st->info->has_burst32) अणु
					u16 val = 0;
					स्थिर u32 reg = ADIS16475_REG_X_GYRO_L +
						bit * 4;

					adis_पढ़ो_reg_16(adis, reg, &val);
					st->data[i++] = cpu_to_be16(val);
				पूर्ण अन्यथा अणु
					/* lower not used */
					st->data[i++] = 0;
				पूर्ण
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, st->data, pf->बारtamp);
check_burst32:
	/*
	 * We only check the burst mode at the end of the current capture since
	 * it takes a full data पढ़ोy cycle क्रम the device to update the burst
	 * array.
	 */
	adis16475_burst32_check(st);
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम adis16475_disable_clk(व्योम *data)
अणु
	clk_disable_unprepare((काष्ठा clk *)data);
पूर्ण

अटल पूर्णांक adis16475_config_sync_mode(काष्ठा adis16475 *st)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = &st->adis.spi->dev;
	स्थिर काष्ठा adis16475_sync *sync;
	u32 sync_mode;

	/* शेष to पूर्णांकernal clk */
	st->clk_freq = st->info->पूर्णांक_clk * 1000;

	ret = device_property_पढ़ो_u32(dev, "adi,sync-mode", &sync_mode);
	अगर (ret)
		वापस 0;

	अगर (sync_mode >= st->info->num_sync) अणु
		dev_err(dev, "Invalid sync mode: %u for %s\n", sync_mode,
			st->info->name);
		वापस -EINVAL;
	पूर्ण

	sync = &st->info->sync[sync_mode];
	st->sync_mode = sync->sync_mode;

	/* All the other modes require बाह्यal input संकेत */
	अगर (sync->sync_mode != ADIS16475_SYNC_OUTPUT) अणु
		काष्ठा clk *clk = devm_clk_get(dev, शून्य);

		अगर (IS_ERR(clk))
			वापस PTR_ERR(clk);

		ret = clk_prepare_enable(clk);
		अगर (ret)
			वापस ret;

		ret = devm_add_action_or_reset(dev, adis16475_disable_clk, clk);
		अगर (ret)
			वापस ret;

		st->clk_freq = clk_get_rate(clk);
		अगर (st->clk_freq < sync->min_rate ||
		    st->clk_freq > sync->max_rate) अणु
			dev_err(dev,
				"Clk rate:%u not in a valid range:[%u %u]\n",
				st->clk_freq, sync->min_rate, sync->max_rate);
			वापस -EINVAL;
		पूर्ण

		अगर (sync->sync_mode == ADIS16475_SYNC_SCALED) अणु
			u16 up_scale;

			/*
			 * In sync scaled mode, the IMU sample rate is the clk_freq * sync_scale.
			 * Hence, शेष the IMU sample rate to the highest multiple of the input
			 * घड़ी lower than the IMU max sample rate. The optimal range is
			 * 1900-2100 sps...
			 */
			up_scale = 2100 / st->clk_freq;

			ret = __adis_ग_लिखो_reg_16(&st->adis,
						  ADIS16475_REG_UP_SCALE,
						  up_scale);
			अगर (ret)
				वापस ret;
		पूर्ण

		st->clk_freq *= 1000;
	पूर्ण
	/*
	 * Keep in mind that the mask क्रम the clk modes in adis1650*
	 * chips is dअगरferent (1100 instead of 11100). However, we
	 * are not configuring BIT(4) in these chips and the शेष
	 * value is 0, so we are fine in करोing the below operations.
	 * I'm keeping this क्रम simplicity and aव्योमing extra variables
	 * in chip_info.
	 */
	ret = __adis_update_bits(&st->adis, ADIS16475_REG_MSG_CTRL,
				 ADIS16475_SYNC_MODE_MASK, sync->sync_mode);
	अगर (ret)
		वापस ret;

	usleep_range(250, 260);

	वापस 0;
पूर्ण

अटल पूर्णांक adis16475_config_irq_pin(काष्ठा adis16475 *st)
अणु
	पूर्णांक ret;
	काष्ठा irq_data *desc;
	u32 irq_type;
	u16 val = 0;
	u8 polarity;
	काष्ठा spi_device *spi = st->adis.spi;

	desc = irq_get_irq_data(spi->irq);
	अगर (!desc) अणु
		dev_err(&spi->dev, "Could not find IRQ %d\n", spi->irq);
		वापस -EINVAL;
	पूर्ण
	/*
	 * It is possible to configure the data पढ़ोy polarity. Furthermore, we
	 * need to update the adis काष्ठा अगर we want data पढ़ोy as active low.
	 */
	irq_type = irqd_get_trigger_type(desc);
	अगर (irq_type == IRQ_TYPE_EDGE_RISING) अणु
		polarity = 1;
		st->adis.irq_flag = IRQF_TRIGGER_RISING;
	पूर्ण अन्यथा अगर (irq_type == IRQ_TYPE_EDGE_FALLING) अणु
		polarity = 0;
		st->adis.irq_flag = IRQF_TRIGGER_FALLING;
	पूर्ण अन्यथा अणु
		dev_err(&spi->dev, "Invalid interrupt type 0x%x specified\n",
			irq_type);
		वापस -EINVAL;
	पूर्ण

	/* We cannot mask the पूर्णांकerrupt so ensure it's not enabled at request */
	st->adis.irq_flag |= IRQF_NO_AUTOEN;

	val = ADIS16475_MSG_CTRL_DR_POL(polarity);
	ret = __adis_update_bits(&st->adis, ADIS16475_REG_MSG_CTRL,
				 ADIS16475_MSG_CTRL_DR_POL_MASK, val);
	अगर (ret)
		वापस ret;
	/*
	 * There is a delay writing to any bits written to the MSC_CTRL
	 * रेजिस्टर. It should not be bigger than 200us, so 250 should be more
	 * than enough!
	 */
	usleep_range(250, 260);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id adis16475_of_match[] = अणु
	अणु .compatible = "adi,adis16470",
		.data = &adis16475_chip_info[ADIS16470] पूर्ण,
	अणु .compatible = "adi,adis16475-1",
		.data = &adis16475_chip_info[ADIS16475_1] पूर्ण,
	अणु .compatible = "adi,adis16475-2",
		.data = &adis16475_chip_info[ADIS16475_2] पूर्ण,
	अणु .compatible = "adi,adis16475-3",
		.data = &adis16475_chip_info[ADIS16475_3] पूर्ण,
	अणु .compatible = "adi,adis16477-1",
		.data = &adis16475_chip_info[ADIS16477_1] पूर्ण,
	अणु .compatible = "adi,adis16477-2",
		.data = &adis16475_chip_info[ADIS16477_2] पूर्ण,
	अणु .compatible = "adi,adis16477-3",
		.data = &adis16475_chip_info[ADIS16477_3] पूर्ण,
	अणु .compatible = "adi,adis16465-1",
		.data = &adis16475_chip_info[ADIS16465_1] पूर्ण,
	अणु .compatible = "adi,adis16465-2",
		.data = &adis16475_chip_info[ADIS16465_2] पूर्ण,
	अणु .compatible = "adi,adis16465-3",
		.data = &adis16475_chip_info[ADIS16465_3] पूर्ण,
	अणु .compatible = "adi,adis16467-1",
		.data = &adis16475_chip_info[ADIS16467_1] पूर्ण,
	अणु .compatible = "adi,adis16467-2",
		.data = &adis16475_chip_info[ADIS16467_2] पूर्ण,
	अणु .compatible = "adi,adis16467-3",
		.data = &adis16475_chip_info[ADIS16467_3] पूर्ण,
	अणु .compatible = "adi,adis16500",
		.data = &adis16475_chip_info[ADIS16500] पूर्ण,
	अणु .compatible = "adi,adis16505-1",
		.data = &adis16475_chip_info[ADIS16505_1] पूर्ण,
	अणु .compatible = "adi,adis16505-2",
		.data = &adis16475_chip_info[ADIS16505_2] पूर्ण,
	अणु .compatible = "adi,adis16505-3",
		.data = &adis16475_chip_info[ADIS16505_3] पूर्ण,
	अणु .compatible = "adi,adis16507-1",
		.data = &adis16475_chip_info[ADIS16507_1] पूर्ण,
	अणु .compatible = "adi,adis16507-2",
		.data = &adis16475_chip_info[ADIS16507_2] पूर्ण,
	अणु .compatible = "adi,adis16507-3",
		.data = &adis16475_chip_info[ADIS16507_3] पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, adis16475_of_match);

अटल पूर्णांक adis16475_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा adis16475 *st;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);

	st->info = device_get_match_data(&spi->dev);
	अगर (!st->info)
		वापस -EINVAL;

	ret = adis_init(&st->adis, indio_dev, spi, &st->info->adis_data);
	अगर (ret)
		वापस ret;

	indio_dev->name = st->info->name;
	indio_dev->channels = st->info->channels;
	indio_dev->num_channels = st->info->num_channels;
	indio_dev->info = &adis16475_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = __adis_initial_startup(&st->adis);
	अगर (ret)
		वापस ret;

	ret = adis16475_config_irq_pin(st);
	अगर (ret)
		वापस ret;

	ret = adis16475_config_sync_mode(st);
	अगर (ret)
		वापस ret;

	ret = devm_adis_setup_buffer_and_trigger(&st->adis, indio_dev,
						 adis16475_trigger_handler);
	अगर (ret)
		वापस ret;

	ret = devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
	अगर (ret)
		वापस ret;

	adis16475_debugfs_init(indio_dev);

	वापस 0;
पूर्ण

अटल काष्ठा spi_driver adis16475_driver = अणु
	.driver = अणु
		.name = "adis16475",
		.of_match_table = adis16475_of_match,
	पूर्ण,
	.probe = adis16475_probe,
पूर्ण;
module_spi_driver(adis16475_driver);

MODULE_AUTHOR("Nuno Sa <nuno.sa@analog.com>");
MODULE_DESCRIPTION("Analog Devices ADIS16475 IMU driver");
MODULE_LICENSE("GPL");
