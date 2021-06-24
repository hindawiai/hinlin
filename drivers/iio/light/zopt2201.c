<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * zopt2201.c - Support क्रम IDT ZOPT2201 ambient light and UV B sensor
 *
 * Copyright 2017 Peter Meerwald-Stadler <pmeerw@pmeerw.net>
 *
 * Datasheet: https://www.idt.com/करोcument/dst/zopt2201-datasheet
 * 7-bit I2C slave addresses 0x53 (शेष) or 0x52 (programmed)
 *
 * TODO: पूर्णांकerrupt support, ALS/UVB raw mode
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#समावेश <यंत्र/unaligned.h>

#घोषणा ZOPT2201_DRV_NAME "zopt2201"

/* Registers */
#घोषणा ZOPT2201_MAIN_CTRL		0x00
#घोषणा ZOPT2201_LS_MEAS_RATE		0x04
#घोषणा ZOPT2201_LS_GAIN		0x05
#घोषणा ZOPT2201_PART_ID		0x06
#घोषणा ZOPT2201_MAIN_STATUS		0x07
#घोषणा ZOPT2201_ALS_DATA		0x0d /* LSB first, 13 to 20 bits */
#घोषणा ZOPT2201_UVB_DATA		0x10 /* LSB first, 13 to 20 bits */
#घोषणा ZOPT2201_UV_COMP_DATA		0x13 /* LSB first, 13 to 20 bits */
#घोषणा ZOPT2201_COMP_DATA		0x16 /* LSB first, 13 to 20 bits */
#घोषणा ZOPT2201_INT_CFG		0x19
#घोषणा ZOPT2201_INT_PST		0x1a

#घोषणा ZOPT2201_MAIN_CTRL_LS_MODE	BIT(3) /* 0 .. ALS, 1 .. UV B */
#घोषणा ZOPT2201_MAIN_CTRL_LS_EN	BIT(1)

/* Values क्रम ZOPT2201_LS_MEAS_RATE resolution / bit width */
#घोषणा ZOPT2201_MEAS_RES_20BIT		0 /* takes 400 ms */
#घोषणा ZOPT2201_MEAS_RES_19BIT		1 /* takes 200 ms */
#घोषणा ZOPT2201_MEAS_RES_18BIT		2 /* takes 100 ms, शेष */
#घोषणा ZOPT2201_MEAS_RES_17BIT		3 /* takes 50 ms */
#घोषणा ZOPT2201_MEAS_RES_16BIT		4 /* takes 25 ms */
#घोषणा ZOPT2201_MEAS_RES_13BIT		5 /* takes 3.125 ms */
#घोषणा ZOPT2201_MEAS_RES_SHIFT		4

/* Values क्रम ZOPT2201_LS_MEAS_RATE measurement rate */
#घोषणा ZOPT2201_MEAS_FREQ_25MS		0
#घोषणा ZOPT2201_MEAS_FREQ_50MS		1
#घोषणा ZOPT2201_MEAS_FREQ_100MS	2 /* शेष */
#घोषणा ZOPT2201_MEAS_FREQ_200MS	3
#घोषणा ZOPT2201_MEAS_FREQ_500MS	4
#घोषणा ZOPT2201_MEAS_FREQ_1000MS	5
#घोषणा ZOPT2201_MEAS_FREQ_2000MS	6

/* Values क्रम ZOPT2201_LS_GAIN */
#घोषणा ZOPT2201_LS_GAIN_1		0
#घोषणा ZOPT2201_LS_GAIN_3		1
#घोषणा ZOPT2201_LS_GAIN_6		2
#घोषणा ZOPT2201_LS_GAIN_9		3
#घोषणा ZOPT2201_LS_GAIN_18		4

/* Values क्रम ZOPT2201_MAIN_STATUS */
#घोषणा ZOPT2201_MAIN_STATUS_POWERON	BIT(5)
#घोषणा ZOPT2201_MAIN_STATUS_INT	BIT(4)
#घोषणा ZOPT2201_MAIN_STATUS_DRDY	BIT(3)

#घोषणा ZOPT2201_PART_NUMBER		0xb2

काष्ठा zopt2201_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	u8 gain;
	u8 res;
	u8 rate;
पूर्ण;

अटल स्थिर काष्ठा अणु
	अचिन्हित पूर्णांक gain; /* gain factor */
	अचिन्हित पूर्णांक scale; /* micro lux per count */
पूर्ण zopt2201_gain_als[] = अणु
	अणु  1, 19200000 पूर्ण,
	अणु  3,  6400000 पूर्ण,
	अणु  6,  3200000 पूर्ण,
	अणु  9,  2133333 पूर्ण,
	अणु 18,  1066666 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	अचिन्हित पूर्णांक gain; /* gain factor */
	अचिन्हित पूर्णांक scale; /* micro W/m2 per count */
पूर्ण zopt2201_gain_uvb[] = अणु
	अणु  1, 460800 पूर्ण,
	अणु  3, 153600 पूर्ण,
	अणु  6,  76800 पूर्ण,
	अणु  9,  51200 पूर्ण,
	अणु 18,  25600 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	अचिन्हित पूर्णांक bits; /* sensor resolution in bits */
	अचिन्हित दीर्घ us; /* measurement समय in micro seconds */
पूर्ण zopt2201_resolution[] = अणु
	अणु 20, 400000 पूर्ण,
	अणु 19, 200000 पूर्ण,
	अणु 18, 100000 पूर्ण,
	अणु 17,  50000 पूर्ण,
	अणु 16,  25000 पूर्ण,
	अणु 13,   3125 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	अचिन्हित पूर्णांक scale, uscale; /* scale factor as पूर्णांकeger + micro */
	u8 gain; /* gain रेजिस्टर value */
	u8 res; /* resolution रेजिस्टर value */
पूर्ण zopt2201_scale_als[] = अणु
	अणु 19, 200000, 0, 5 पूर्ण,
	अणु  6, 400000, 1, 5 पूर्ण,
	अणु  3, 200000, 2, 5 पूर्ण,
	अणु  2, 400000, 0, 4 पूर्ण,
	अणु  2, 133333, 3, 5 पूर्ण,
	अणु  1, 200000, 0, 3 पूर्ण,
	अणु  1,  66666, 4, 5 पूर्ण,
	अणु  0, 800000, 1, 4 पूर्ण,
	अणु  0, 600000, 0, 2 पूर्ण,
	अणु  0, 400000, 2, 4 पूर्ण,
	अणु  0, 300000, 0, 1 पूर्ण,
	अणु  0, 266666, 3, 4 पूर्ण,
	अणु  0, 200000, 2, 3 पूर्ण,
	अणु  0, 150000, 0, 0 पूर्ण,
	अणु  0, 133333, 4, 4 पूर्ण,
	अणु  0, 100000, 2, 2 पूर्ण,
	अणु  0,  66666, 4, 3 पूर्ण,
	अणु  0,  50000, 2, 1 पूर्ण,
	अणु  0,  33333, 4, 2 पूर्ण,
	अणु  0,  25000, 2, 0 पूर्ण,
	अणु  0,  16666, 4, 1 पूर्ण,
	अणु  0,   8333, 4, 0 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	अचिन्हित पूर्णांक scale, uscale; /* scale factor as पूर्णांकeger + micro */
	u8 gain; /* gain रेजिस्टर value */
	u8 res; /* resolution रेजिस्टर value */
पूर्ण zopt2201_scale_uvb[] = अणु
	अणु 0, 460800, 0, 5 पूर्ण,
	अणु 0, 153600, 1, 5 पूर्ण,
	अणु 0,  76800, 2, 5 पूर्ण,
	अणु 0,  57600, 0, 4 पूर्ण,
	अणु 0,  51200, 3, 5 पूर्ण,
	अणु 0,  28800, 0, 3 पूर्ण,
	अणु 0,  25600, 4, 5 पूर्ण,
	अणु 0,  19200, 1, 4 पूर्ण,
	अणु 0,  14400, 0, 2 पूर्ण,
	अणु 0,   9600, 2, 4 पूर्ण,
	अणु 0,   7200, 0, 1 पूर्ण,
	अणु 0,   6400, 3, 4 पूर्ण,
	अणु 0,   4800, 2, 3 पूर्ण,
	अणु 0,   3600, 0, 0 पूर्ण,
	अणु 0,   3200, 4, 4 पूर्ण,
	अणु 0,   2400, 2, 2 पूर्ण,
	अणु 0,   1600, 4, 3 पूर्ण,
	अणु 0,   1200, 2, 1 पूर्ण,
	अणु 0,    800, 4, 2 पूर्ण,
	अणु 0,    600, 2, 0 पूर्ण,
	अणु 0,    400, 4, 1 पूर्ण,
	अणु 0,    200, 4, 0 पूर्ण,
पूर्ण;

अटल पूर्णांक zopt2201_enable_mode(काष्ठा zopt2201_data *data, bool uvb_mode)
अणु
	u8 out = ZOPT2201_MAIN_CTRL_LS_EN;

	अगर (uvb_mode)
		out |= ZOPT2201_MAIN_CTRL_LS_MODE;

	वापस i2c_smbus_ग_लिखो_byte_data(data->client, ZOPT2201_MAIN_CTRL, out);
पूर्ण

अटल पूर्णांक zopt2201_पढ़ो(काष्ठा zopt2201_data *data, u8 reg)
अणु
	काष्ठा i2c_client *client = data->client;
	पूर्णांक tries = 10;
	u8 buf[3];
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = zopt2201_enable_mode(data, reg == ZOPT2201_UVB_DATA);
	अगर (ret < 0)
		जाओ fail;

	जबतक (tries--) अणु
		अचिन्हित दीर्घ t = zopt2201_resolution[data->res].us;

		अगर (t <= 20000)
			usleep_range(t, t + 1000);
		अन्यथा
			msleep(t / 1000);
		ret = i2c_smbus_पढ़ो_byte_data(client, ZOPT2201_MAIN_STATUS);
		अगर (ret < 0)
			जाओ fail;
		अगर (ret & ZOPT2201_MAIN_STATUS_DRDY)
			अवरोध;
	पूर्ण

	अगर (tries < 0) अणु
		ret = -ETIMEDOUT;
		जाओ fail;
	पूर्ण

	ret = i2c_smbus_पढ़ो_i2c_block_data(client, reg, माप(buf), buf);
	अगर (ret < 0)
		जाओ fail;

	ret = i2c_smbus_ग_लिखो_byte_data(client, ZOPT2201_MAIN_CTRL, 0x00);
	अगर (ret < 0)
		जाओ fail;
	mutex_unlock(&data->lock);

	वापस get_unaligned_le24(&buf[0]);

fail:
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec zopt2201_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.address = ZOPT2201_ALS_DATA,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_INT_TIME),
	पूर्ण,
	अणु
		.type = IIO_INTENSITY,
		.modअगरied = 1,
		.channel2 = IIO_MOD_LIGHT_UV,
		.address = ZOPT2201_UVB_DATA,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				      BIT(IIO_CHAN_INFO_SCALE),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_INT_TIME),
	पूर्ण,
	अणु
		.type = IIO_UVINDEX,
		.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),
	पूर्ण,
पूर्ण;

अटल पूर्णांक zopt2201_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा zopt2201_data *data = iio_priv(indio_dev);
	u64 पंचांगp;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = zopt2201_पढ़ो(data, chan->address);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_PROCESSED:
		ret = zopt2201_पढ़ो(data, ZOPT2201_UVB_DATA);
		अगर (ret < 0)
			वापस ret;
		*val = ret * 18 *
			(1 << (20 - zopt2201_resolution[data->res].bits)) /
			zopt2201_gain_uvb[data->gain].gain;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->address) अणु
		हाल ZOPT2201_ALS_DATA:
			*val = zopt2201_gain_als[data->gain].scale;
			अवरोध;
		हाल ZOPT2201_UVB_DATA:
			*val = zopt2201_gain_uvb[data->gain].scale;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		*val2 = 1000000;
		*val2 *= (1 << (zopt2201_resolution[data->res].bits - 13));
		पंचांगp = भाग_s64(*val * 1000000ULL, *val2);
		*val = भाग_s64_rem(पंचांगp, 1000000, val2);

		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_INT_TIME:
		*val = 0;
		*val2 = zopt2201_resolution[data->res].us;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक zopt2201_set_resolution(काष्ठा zopt2201_data *data, u8 res)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, ZOPT2201_LS_MEAS_RATE,
					(res << ZOPT2201_MEAS_RES_SHIFT) |
					data->rate);
	अगर (ret < 0)
		वापस ret;

	data->res = res;

	वापस 0;
पूर्ण

अटल पूर्णांक zopt2201_ग_लिखो_resolution(काष्ठा zopt2201_data *data,
				     पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i, ret;

	अगर (val != 0)
		वापस -EINVAL;

	क्रम (i = 0; i < ARRAY_SIZE(zopt2201_resolution); i++)
		अगर (val2 == zopt2201_resolution[i].us) अणु
			mutex_lock(&data->lock);
			ret = zopt2201_set_resolution(data, i);
			mutex_unlock(&data->lock);
			वापस ret;
		पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक zopt2201_set_gain(काष्ठा zopt2201_data *data, u8 gain)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, ZOPT2201_LS_GAIN, gain);
	अगर (ret < 0)
		वापस ret;

	data->gain = gain;

	वापस 0;
पूर्ण

अटल पूर्णांक zopt2201_ग_लिखो_scale_als_by_idx(काष्ठा zopt2201_data *data, पूर्णांक idx)
अणु
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = zopt2201_set_resolution(data, zopt2201_scale_als[idx].res);
	अगर (ret < 0)
		जाओ unlock;

	ret = zopt2201_set_gain(data, zopt2201_scale_als[idx].gain);

unlock:
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक zopt2201_ग_लिखो_scale_als(काष्ठा zopt2201_data *data,
				     पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(zopt2201_scale_als); i++)
		अगर (val == zopt2201_scale_als[i].scale &&
		    val2 == zopt2201_scale_als[i].uscale) अणु
			वापस zopt2201_ग_लिखो_scale_als_by_idx(data, i);
		पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक zopt2201_ग_लिखो_scale_uvb_by_idx(काष्ठा zopt2201_data *data, पूर्णांक idx)
अणु
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = zopt2201_set_resolution(data, zopt2201_scale_als[idx].res);
	अगर (ret < 0)
		जाओ unlock;

	ret = zopt2201_set_gain(data, zopt2201_scale_als[idx].gain);

unlock:
	mutex_unlock(&data->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक zopt2201_ग_लिखो_scale_uvb(काष्ठा zopt2201_data *data,
				     पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(zopt2201_scale_uvb); i++)
		अगर (val == zopt2201_scale_uvb[i].scale &&
		    val2 == zopt2201_scale_uvb[i].uscale)
			वापस zopt2201_ग_लिखो_scale_uvb_by_idx(data, i);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक zopt2201_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा zopt2201_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_INT_TIME:
		वापस zopt2201_ग_लिखो_resolution(data, val, val2);
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->address) अणु
		हाल ZOPT2201_ALS_DATA:
			वापस zopt2201_ग_लिखो_scale_als(data, val, val2);
		हाल ZOPT2201_UVB_DATA:
			वापस zopt2201_ग_लिखो_scale_uvb(data, val, val2);
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार zopt2201_show_पूर्णांक_समय_available(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						अक्षर *buf)
अणु
	माप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(zopt2201_resolution); i++)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "0.%06lu ",
				 zopt2201_resolution[i].us);
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल IIO_DEV_ATTR_INT_TIME_AVAIL(zopt2201_show_पूर्णांक_समय_available);

अटल sमाप_प्रकार zopt2201_show_als_scale_avail(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	sमाप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(zopt2201_scale_als); i++)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%d.%06u ",
				 zopt2201_scale_als[i].scale,
				 zopt2201_scale_als[i].uscale);
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल sमाप_प्रकार zopt2201_show_uvb_scale_avail(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     अक्षर *buf)
अणु
	sमाप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(zopt2201_scale_uvb); i++)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len, "%d.%06u ",
				 zopt2201_scale_uvb[i].scale,
				 zopt2201_scale_uvb[i].uscale);
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(in_illuminance_scale_available, 0444,
		       zopt2201_show_als_scale_avail, शून्य, 0);
अटल IIO_DEVICE_ATTR(in_पूर्णांकensity_uv_scale_available, 0444,
		       zopt2201_show_uvb_scale_avail, शून्य, 0);

अटल काष्ठा attribute *zopt2201_attributes[] = अणु
	&iio_dev_attr_पूर्णांकegration_समय_available.dev_attr.attr,
	&iio_dev_attr_in_illuminance_scale_available.dev_attr.attr,
	&iio_dev_attr_in_पूर्णांकensity_uv_scale_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group zopt2201_attribute_group = अणु
	.attrs = zopt2201_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info zopt2201_info = अणु
	.पढ़ो_raw = zopt2201_पढ़ो_raw,
	.ग_लिखो_raw = zopt2201_ग_लिखो_raw,
	.attrs = &zopt2201_attribute_group,
पूर्ण;

अटल पूर्णांक zopt2201_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा zopt2201_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_I2C_BLOCK))
		वापस -EOPNOTSUPP;

	ret = i2c_smbus_पढ़ो_byte_data(client, ZOPT2201_PART_ID);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != ZOPT2201_PART_NUMBER)
		वापस -ENODEV;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	mutex_init(&data->lock);

	indio_dev->info = &zopt2201_info;
	indio_dev->channels = zopt2201_channels;
	indio_dev->num_channels = ARRAY_SIZE(zopt2201_channels);
	indio_dev->name = ZOPT2201_DRV_NAME;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	data->rate = ZOPT2201_MEAS_FREQ_100MS;
	ret = zopt2201_set_resolution(data, ZOPT2201_MEAS_RES_18BIT);
	अगर (ret < 0)
		वापस ret;

	ret = zopt2201_set_gain(data, ZOPT2201_LS_GAIN_3);
	अगर (ret < 0)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id zopt2201_id[] = अणु
	अणु "zopt2201", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, zopt2201_id);

अटल काष्ठा i2c_driver zopt2201_driver = अणु
	.driver = अणु
		.name   = ZOPT2201_DRV_NAME,
	पूर्ण,
	.probe  = zopt2201_probe,
	.id_table = zopt2201_id,
पूर्ण;

module_i2c_driver(zopt2201_driver);

MODULE_AUTHOR("Peter Meerwald-Stadler <pmeerw@pmeerw.net>");
MODULE_DESCRIPTION("IDT ZOPT2201 ambient light and UV B sensor driver");
MODULE_LICENSE("GPL");
