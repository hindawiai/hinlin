<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MMC35240 - MEMSIC 3-axis Magnetic Sensor
 *
 * Copyright (c) 2015, Intel Corporation.
 *
 * IIO driver क्रम MMC35240 (7-bit I2C slave address 0x30).
 *
 * TODO: offset, ACPI, continuous measurement mode, PM
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/delay.h>
#समावेश <linux/regmap.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pm.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा MMC35240_DRV_NAME "mmc35240"
#घोषणा MMC35240_REGMAP_NAME "mmc35240_regmap"

#घोषणा MMC35240_REG_XOUT_L	0x00
#घोषणा MMC35240_REG_XOUT_H	0x01
#घोषणा MMC35240_REG_YOUT_L	0x02
#घोषणा MMC35240_REG_YOUT_H	0x03
#घोषणा MMC35240_REG_ZOUT_L	0x04
#घोषणा MMC35240_REG_ZOUT_H	0x05

#घोषणा MMC35240_REG_STATUS	0x06
#घोषणा MMC35240_REG_CTRL0	0x07
#घोषणा MMC35240_REG_CTRL1	0x08

#घोषणा MMC35240_REG_ID		0x20

#घोषणा MMC35240_STATUS_MEAS_DONE_BIT	BIT(0)

#घोषणा MMC35240_CTRL0_REFILL_BIT	BIT(7)
#घोषणा MMC35240_CTRL0_RESET_BIT	BIT(6)
#घोषणा MMC35240_CTRL0_SET_BIT		BIT(5)
#घोषणा MMC35240_CTRL0_CMM_BIT		BIT(1)
#घोषणा MMC35240_CTRL0_TM_BIT		BIT(0)

/* output resolution bits */
#घोषणा MMC35240_CTRL1_BW0_BIT		BIT(0)
#घोषणा MMC35240_CTRL1_BW1_BIT		BIT(1)

#घोषणा MMC35240_CTRL1_BW_MASK	 (MMC35240_CTRL1_BW0_BIT | \
		 MMC35240_CTRL1_BW1_BIT)
#घोषणा MMC35240_CTRL1_BW_SHIFT		0

#घोषणा MMC35240_WAIT_CHARGE_PUMP	50000	/* us */
#घोषणा MMC35240_WAIT_SET_RESET		1000	/* us */

/*
 * Memsic OTP process code piece is put here क्रम reference:
 *
 * #घोषणा OTP_CONVERT(REG)  ((भग्न)((REG) >=32 ? (32 - (REG)) : (REG)) * 0.006
 * 1) For X axis, the COEFFICIENT is always 1.
 * 2) For Y axis, the COEFFICIENT is as below:
 *    f_OTP_matrix[4] = OTP_CONVERT(((reg_data[1] & 0x03) << 4) |
 *                                   (reg_data[2] >> 4)) + 1.0;
 * 3) For Z axis, the COEFFICIENT is as below:
 *    f_OTP_matrix[8] = (OTP_CONVERT(reg_data[3] & 0x3f) + 1) * 1.35;
 * We implemented the OTP logic पूर्णांकo driver.
 */

/* scale = 1000 here क्रम Y otp */
#घोषणा MMC35240_OTP_CONVERT_Y(REG) (((REG) >= 32 ? (32 - (REG)) : (REG)) * 6)

/* 0.6 * 1.35 = 0.81, scale 10000 क्रम Z otp */
#घोषणा MMC35240_OTP_CONVERT_Z(REG) (((REG) >= 32 ? (32 - (REG)) : (REG)) * 81)

#घोषणा MMC35240_X_COEFF(x)	(x)
#घोषणा MMC35240_Y_COEFF(y)	(y + 1000)
#घोषणा MMC35240_Z_COEFF(z)	(z + 13500)

#घोषणा MMC35240_OTP_START_ADDR		0x1B

क्रमागत mmc35240_resolution अणु
	MMC35240_16_BITS_SLOW = 0, /* 7.92 ms */
	MMC35240_16_BITS_FAST,     /* 4.08 ms */
	MMC35240_14_BITS,          /* 2.16 ms */
	MMC35240_12_BITS,          /* 1.20 ms */
पूर्ण;

क्रमागत mmc35240_axis अणु
	AXIS_X = 0,
	AXIS_Y,
	AXIS_Z,
पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक sens[3]; /* sensitivity per X, Y, Z axis */
	पूर्णांक nfo; /* null field output */
पूर्ण mmc35240_props_table[] = अणु
	/* 16 bits, 125Hz ODR */
	अणु
		अणु1024, 1024, 1024पूर्ण,
		32768,
	पूर्ण,
	/* 16 bits, 250Hz ODR */
	अणु
		अणु1024, 1024, 770पूर्ण,
		32768,
	पूर्ण,
	/* 14 bits, 450Hz ODR */
	अणु
		अणु256, 256, 193पूर्ण,
		8192,
	पूर्ण,
	/* 12 bits, 800Hz ODR */
	अणु
		अणु64, 64, 48पूर्ण,
		2048,
	पूर्ण,
पूर्ण;

काष्ठा mmc35240_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex mutex;
	काष्ठा regmap *regmap;
	क्रमागत mmc35240_resolution res;

	/* OTP compensation */
	पूर्णांक axis_coef[3];
	पूर्णांक axis_scale[3];
पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक val;
	पूर्णांक val2;
पूर्ण mmc35240_samp_freq[] = अणु अणु1, 500000पूर्ण,
			   अणु13, 0पूर्ण,
			   अणु25, 0पूर्ण,
			   अणु50, 0पूर्ण पूर्ण;

अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL("1.5 13 25 50");

#घोषणा MMC35240_CHANNEL(_axis) अणु \
	.type = IIO_MAGN, \
	.modअगरied = 1, \
	.channel2 = IIO_MOD_ ## _axis, \
	.address = AXIS_ ## _axis, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SAMP_FREQ) | \
			BIT(IIO_CHAN_INFO_SCALE), \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mmc35240_channels[] = अणु
	MMC35240_CHANNEL(X),
	MMC35240_CHANNEL(Y),
	MMC35240_CHANNEL(Z),
पूर्ण;

अटल काष्ठा attribute *mmc35240_attributes[] = अणु
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group mmc35240_attribute_group = अणु
	.attrs = mmc35240_attributes,
पूर्ण;

अटल पूर्णांक mmc35240_get_samp_freq_index(काष्ठा mmc35240_data *data,
					पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(mmc35240_samp_freq); i++)
		अगर (mmc35240_samp_freq[i].val == val &&
		    mmc35240_samp_freq[i].val2 == val2)
			वापस i;
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mmc35240_hw_set(काष्ठा mmc35240_data *data, bool set)
अणु
	पूर्णांक ret;
	u8 coil_bit;

	/*
	 * Reअक्षरge the capacitor at VCAP pin, requested to be issued
	 * beक्रमe a SET/RESET command.
	 */
	ret = regmap_update_bits(data->regmap, MMC35240_REG_CTRL0,
				 MMC35240_CTRL0_REFILL_BIT,
				 MMC35240_CTRL0_REFILL_BIT);
	अगर (ret < 0)
		वापस ret;
	usleep_range(MMC35240_WAIT_CHARGE_PUMP, MMC35240_WAIT_CHARGE_PUMP + 1);

	अगर (set)
		coil_bit = MMC35240_CTRL0_SET_BIT;
	अन्यथा
		coil_bit = MMC35240_CTRL0_RESET_BIT;

	वापस regmap_update_bits(data->regmap, MMC35240_REG_CTRL0,
				  coil_bit, coil_bit);

पूर्ण

अटल पूर्णांक mmc35240_init(काष्ठा mmc35240_data *data)
अणु
	पूर्णांक ret, y_convert, z_convert;
	अचिन्हित पूर्णांक reg_id;
	u8 otp_data[6];

	ret = regmap_पढ़ो(data->regmap, MMC35240_REG_ID, &reg_id);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading product id\n");
		वापस ret;
	पूर्ण

	dev_dbg(&data->client->dev, "MMC35240 chip id %x\n", reg_id);

	/*
	 * make sure we restore sensor अक्षरacteristics, by करोing
	 * a SET/RESET sequence, the axis polarity being naturally
	 * aligned after RESET
	 */
	ret = mmc35240_hw_set(data, true);
	अगर (ret < 0)
		वापस ret;
	usleep_range(MMC35240_WAIT_SET_RESET, MMC35240_WAIT_SET_RESET + 1);

	ret = mmc35240_hw_set(data, false);
	अगर (ret < 0)
		वापस ret;

	/* set शेष sampling frequency */
	ret = regmap_update_bits(data->regmap, MMC35240_REG_CTRL1,
				 MMC35240_CTRL1_BW_MASK,
				 data->res << MMC35240_CTRL1_BW_SHIFT);
	अगर (ret < 0)
		वापस ret;

	ret = regmap_bulk_पढ़ो(data->regmap, MMC35240_OTP_START_ADDR,
			       otp_data, माप(otp_data));
	अगर (ret < 0)
		वापस ret;

	y_convert = MMC35240_OTP_CONVERT_Y(((otp_data[1] & 0x03) << 4) |
					   (otp_data[2] >> 4));
	z_convert = MMC35240_OTP_CONVERT_Z(otp_data[3] & 0x3f);

	data->axis_coef[0] = MMC35240_X_COEFF(1);
	data->axis_coef[1] = MMC35240_Y_COEFF(y_convert);
	data->axis_coef[2] = MMC35240_Z_COEFF(z_convert);

	data->axis_scale[0] = 1;
	data->axis_scale[1] = 1000;
	data->axis_scale[2] = 10000;

	वापस 0;
पूर्ण

अटल पूर्णांक mmc35240_take_measurement(काष्ठा mmc35240_data *data)
अणु
	पूर्णांक ret, tries = 100;
	अचिन्हित पूर्णांक reg_status;

	ret = regmap_ग_लिखो(data->regmap, MMC35240_REG_CTRL0,
			   MMC35240_CTRL0_TM_BIT);
	अगर (ret < 0)
		वापस ret;

	जबतक (tries-- > 0) अणु
		ret = regmap_पढ़ो(data->regmap, MMC35240_REG_STATUS,
				  &reg_status);
		अगर (ret < 0)
			वापस ret;
		अगर (reg_status & MMC35240_STATUS_MEAS_DONE_BIT)
			अवरोध;
		/* minimum रुको समय to complete measurement is 10 ms */
		usleep_range(10000, 11000);
	पूर्ण

	अगर (tries < 0) अणु
		dev_err(&data->client->dev, "data not ready\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mmc35240_पढ़ो_measurement(काष्ठा mmc35240_data *data, __le16 buf[3])
अणु
	पूर्णांक ret;

	ret = mmc35240_take_measurement(data);
	अगर (ret < 0)
		वापस ret;

	वापस regmap_bulk_पढ़ो(data->regmap, MMC35240_REG_XOUT_L, buf,
				3 * माप(__le16));
पूर्ण

/**
 * mmc35240_raw_to_mgauss - convert raw पढ़ोings to milli gauss. Also apply
 *			    compensation क्रम output value.
 *
 * @data: device निजी data
 * @index: axis index क्रम which we want the conversion
 * @buf: raw data to be converted, 2 bytes in little endian क्रमmat
 * @val: compensated output पढ़ोing (unit is milli gauss)
 *
 * Returns: 0 in हाल of success, -EINVAL when @index is not valid
 */
अटल पूर्णांक mmc35240_raw_to_mgauss(काष्ठा mmc35240_data *data, पूर्णांक index,
				  __le16 buf[], पूर्णांक *val)
अणु
	पूर्णांक raw[3];
	पूर्णांक sens[3];
	पूर्णांक nfo;

	raw[AXIS_X] = le16_to_cpu(buf[AXIS_X]);
	raw[AXIS_Y] = le16_to_cpu(buf[AXIS_Y]);
	raw[AXIS_Z] = le16_to_cpu(buf[AXIS_Z]);

	sens[AXIS_X] = mmc35240_props_table[data->res].sens[AXIS_X];
	sens[AXIS_Y] = mmc35240_props_table[data->res].sens[AXIS_Y];
	sens[AXIS_Z] = mmc35240_props_table[data->res].sens[AXIS_Z];

	nfo = mmc35240_props_table[data->res].nfo;

	चयन (index) अणु
	हाल AXIS_X:
		*val = (raw[AXIS_X] - nfo) * 1000 / sens[AXIS_X];
		अवरोध;
	हाल AXIS_Y:
		*val = (raw[AXIS_Y] - nfo) * 1000 / sens[AXIS_Y] -
			(raw[AXIS_Z] - nfo)  * 1000 / sens[AXIS_Z];
		अवरोध;
	हाल AXIS_Z:
		*val = (raw[AXIS_Y] - nfo) * 1000 / sens[AXIS_Y] +
			(raw[AXIS_Z] - nfo) * 1000 / sens[AXIS_Z];
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	/* apply OTP compensation */
	*val = (*val) * data->axis_coef[index] / data->axis_scale[index];

	वापस 0;
पूर्ण

अटल पूर्णांक mmc35240_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			     पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mmc35240_data *data = iio_priv(indio_dev);
	पूर्णांक ret, i;
	अचिन्हित पूर्णांक reg;
	__le16 buf[3];

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&data->mutex);
		ret = mmc35240_पढ़ो_measurement(data, buf);
		mutex_unlock(&data->mutex);
		अगर (ret < 0)
			वापस ret;
		ret = mmc35240_raw_to_mgauss(data, chan->address, buf, val);
		अगर (ret < 0)
			वापस ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = 1000;
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		mutex_lock(&data->mutex);
		ret = regmap_पढ़ो(data->regmap, MMC35240_REG_CTRL1, &reg);
		mutex_unlock(&data->mutex);
		अगर (ret < 0)
			वापस ret;

		i = (reg & MMC35240_CTRL1_BW_MASK) >> MMC35240_CTRL1_BW_SHIFT;
		अगर (i < 0 || i >= ARRAY_SIZE(mmc35240_samp_freq))
			वापस -EINVAL;

		*val = mmc35240_samp_freq[i].val;
		*val2 = mmc35240_samp_freq[i].val2;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mmc35240_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val,
			      पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा mmc35240_data *data = iio_priv(indio_dev);
	पूर्णांक i, ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		i = mmc35240_get_samp_freq_index(data, val, val2);
		अगर (i < 0)
			वापस -EINVAL;
		mutex_lock(&data->mutex);
		ret = regmap_update_bits(data->regmap, MMC35240_REG_CTRL1,
					 MMC35240_CTRL1_BW_MASK,
					 i << MMC35240_CTRL1_BW_SHIFT);
		mutex_unlock(&data->mutex);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info mmc35240_info = अणु
	.पढ़ो_raw	= mmc35240_पढ़ो_raw,
	.ग_लिखो_raw	= mmc35240_ग_लिखो_raw,
	.attrs		= &mmc35240_attribute_group,
पूर्ण;

अटल bool mmc35240_is_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MMC35240_REG_CTRL0:
	हाल MMC35240_REG_CTRL1:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool mmc35240_is_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MMC35240_REG_XOUT_L:
	हाल MMC35240_REG_XOUT_H:
	हाल MMC35240_REG_YOUT_L:
	हाल MMC35240_REG_YOUT_H:
	हाल MMC35240_REG_ZOUT_L:
	हाल MMC35240_REG_ZOUT_H:
	हाल MMC35240_REG_STATUS:
	हाल MMC35240_REG_ID:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool mmc35240_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MMC35240_REG_CTRL0:
	हाल MMC35240_REG_CTRL1:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा reg_शेष mmc35240_reg_शेषs[] = अणु
	अणु MMC35240_REG_CTRL0,  0x00 पूर्ण,
	अणु MMC35240_REG_CTRL1,  0x00 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config mmc35240_regmap_config = अणु
	.name = MMC35240_REGMAP_NAME,

	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = MMC35240_REG_ID,
	.cache_type = REGCACHE_FLAT,

	.ग_लिखोable_reg = mmc35240_is_ग_लिखोable_reg,
	.पढ़ोable_reg = mmc35240_is_पढ़ोable_reg,
	.अस्थिर_reg = mmc35240_is_अस्थिर_reg,

	.reg_शेषs = mmc35240_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(mmc35240_reg_शेषs),
पूर्ण;

अटल पूर्णांक mmc35240_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा mmc35240_data *data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	regmap = devm_regmap_init_i2c(client, &mmc35240_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "regmap initialization failed\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	data->regmap = regmap;
	data->res = MMC35240_16_BITS_SLOW;

	mutex_init(&data->mutex);

	indio_dev->info = &mmc35240_info;
	indio_dev->name = MMC35240_DRV_NAME;
	indio_dev->channels = mmc35240_channels;
	indio_dev->num_channels = ARRAY_SIZE(mmc35240_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = mmc35240_init(data);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "mmc35240 chip init failed\n");
		वापस ret;
	पूर्ण
	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mmc35240_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा mmc35240_data *data = iio_priv(indio_dev);

	regcache_cache_only(data->regmap, true);

	वापस 0;
पूर्ण

अटल पूर्णांक mmc35240_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा mmc35240_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	regcache_mark_dirty(data->regmap);
	ret = regcache_sync_region(data->regmap, MMC35240_REG_CTRL0,
				   MMC35240_REG_CTRL1);
	अगर (ret < 0)
		dev_err(dev, "Failed to restore control registers\n");

	regcache_cache_only(data->regmap, false);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops mmc35240_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(mmc35240_suspend, mmc35240_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id mmc35240_of_match[] = अणु
	अणु .compatible = "memsic,mmc35240", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mmc35240_of_match);

अटल स्थिर काष्ठा acpi_device_id mmc35240_acpi_match[] = अणु
	अणु"MMC35240", 0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, mmc35240_acpi_match);

अटल स्थिर काष्ठा i2c_device_id mmc35240_id[] = अणु
	अणु"mmc35240", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mmc35240_id);

अटल काष्ठा i2c_driver mmc35240_driver = अणु
	.driver = अणु
		.name = MMC35240_DRV_NAME,
		.of_match_table = mmc35240_of_match,
		.pm = &mmc35240_pm_ops,
		.acpi_match_table = ACPI_PTR(mmc35240_acpi_match),
	पूर्ण,
	.probe		= mmc35240_probe,
	.id_table	= mmc35240_id,
पूर्ण;

module_i2c_driver(mmc35240_driver);

MODULE_AUTHOR("Daniel Baluta <daniel.baluta@intel.com>");
MODULE_DESCRIPTION("MEMSIC MMC35240 magnetic sensor driver");
MODULE_LICENSE("GPL v2");
