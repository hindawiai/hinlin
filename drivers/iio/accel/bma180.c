<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * bma180.c - IIO driver क्रम Bosch BMA180 triaxial acceleration sensor
 *
 * Copyright 2013 Oleksandr Kravchenko <x0199363@ti.com>
 *
 * Support क्रम BMA250 (c) Peter Meerwald <pmeerw@pmeerw.net>
 *
 * SPI is not supported by driver
 * BMA023/BMA150/SMB380: 7-bit I2C slave address 0x38
 * BMA180: 7-bit I2C slave address 0x40 or 0x41
 * BMA250: 7-bit I2C slave address 0x18 or 0x19
 * BMA254: 7-bit I2C slave address 0x18 or 0x19
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of.h>
#समावेश <linux/bitops.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#घोषणा BMA180_DRV_NAME "bma180"
#घोषणा BMA180_IRQ_NAME "bma180_event"

क्रमागत chip_ids अणु
	BMA023,
	BMA150,
	BMA180,
	BMA250,
	BMA254,
पूर्ण;

काष्ठा bma180_data;

काष्ठा bma180_part_info अणु
	u8 chip_id;
	स्थिर काष्ठा iio_chan_spec *channels;
	अचिन्हित पूर्णांक num_channels;
	स्थिर पूर्णांक *scale_table;
	अचिन्हित पूर्णांक num_scales;
	स्थिर पूर्णांक *bw_table;
	अचिन्हित पूर्णांक num_bw;
	पूर्णांक temp_offset;

	u8 पूर्णांक_reset_reg, पूर्णांक_reset_mask;
	u8 sleep_reg, sleep_mask;
	u8 bw_reg, bw_mask;
	u8 scale_reg, scale_mask;
	u8 घातer_reg, घातer_mask, lowघातer_val;
	u8 पूर्णांक_enable_reg, पूर्णांक_enable_mask;
	u8 पूर्णांक_map_reg, पूर्णांक_enable_dataपढ़ोy_पूर्णांक1_mask;
	u8 softreset_reg, softreset_val;

	पूर्णांक (*chip_config)(काष्ठा bma180_data *data);
	व्योम (*chip_disable)(काष्ठा bma180_data *data);
पूर्ण;

/* Register set */
#घोषणा BMA023_CTRL_REG0	0x0a
#घोषणा BMA023_CTRL_REG1	0x0b
#घोषणा BMA023_CTRL_REG2	0x14
#घोषणा BMA023_CTRL_REG3	0x15

#घोषणा BMA023_RANGE_MASK	GENMASK(4, 3) /* Range of accel values */
#घोषणा BMA023_BW_MASK		GENMASK(2, 0) /* Accel bandwidth */
#घोषणा BMA023_SLEEP		BIT(0)
#घोषणा BMA023_INT_RESET_MASK	BIT(6)
#घोषणा BMA023_NEW_DATA_INT	BIT(5) /* Intr every new accel data is पढ़ोy */
#घोषणा BMA023_RESET_VAL	BIT(1)

#घोषणा BMA180_CHIP_ID		0x00 /* Need to distinguish BMA180 from other */
#घोषणा BMA180_ACC_X_LSB	0x02 /* First of 6 रेजिस्टरs of accel data */
#घोषणा BMA180_TEMP		0x08
#घोषणा BMA180_CTRL_REG0	0x0d
#घोषणा BMA180_RESET		0x10
#घोषणा BMA180_BW_TCS		0x20
#घोषणा BMA180_CTRL_REG3	0x21
#घोषणा BMA180_TCO_Z		0x30
#घोषणा BMA180_OFFSET_LSB1	0x35

/* BMA180_CTRL_REG0 bits */
#घोषणा BMA180_DIS_WAKE_UP	BIT(0) /* Disable wake up mode */
#घोषणा BMA180_SLEEP		BIT(1) /* 1 - chip will sleep */
#घोषणा BMA180_EE_W		BIT(4) /* Unlock writing to addr from 0x20 */
#घोषणा BMA180_RESET_INT	BIT(6) /* Reset pending पूर्णांकerrupts */

/* BMA180_CTRL_REG3 bits */
#घोषणा BMA180_NEW_DATA_INT	BIT(1) /* Intr every new accel data is पढ़ोy */

/* BMA180_OFFSET_LSB1 skipping mode bit */
#घोषणा BMA180_SMP_SKIP		BIT(0)

/* Bit masks क्रम रेजिस्टरs bit fields */
#घोषणा BMA180_RANGE		0x0e /* Range of measured accel values */
#घोषणा BMA180_BW		0xf0 /* Accel bandwidth */
#घोषणा BMA180_MODE_CONFIG	0x03 /* Config operation modes */

/* We have to ग_लिखो this value in reset रेजिस्टर to करो soft reset */
#घोषणा BMA180_RESET_VAL	0xb6

#घोषणा BMA023_ID_REG_VAL	0x02
#घोषणा BMA180_ID_REG_VAL	0x03
#घोषणा BMA250_ID_REG_VAL	0x03
#घोषणा BMA254_ID_REG_VAL	0xfa /* 250 decimal */

/* Chip घातer modes */
#घोषणा BMA180_LOW_POWER	0x03

#घोषणा BMA250_RANGE_REG	0x0f
#घोषणा BMA250_BW_REG		0x10
#घोषणा BMA250_POWER_REG	0x11
#घोषणा BMA250_RESET_REG	0x14
#घोषणा BMA250_INT_ENABLE_REG	0x17
#घोषणा BMA250_INT_MAP_REG	0x1a
#घोषणा BMA250_INT_RESET_REG	0x21

#घोषणा BMA250_RANGE_MASK	GENMASK(3, 0) /* Range of accel values */
#घोषणा BMA250_BW_MASK		GENMASK(4, 0) /* Accel bandwidth */
#घोषणा BMA250_SUSPEND_MASK	BIT(7) /* chip will sleep */
#घोषणा BMA250_LOWPOWER_MASK	BIT(6)
#घोषणा BMA250_DATA_INTEN_MASK	BIT(4)
#घोषणा BMA250_INT1_DATA_MASK	BIT(0)
#घोषणा BMA250_INT_RESET_MASK	BIT(7) /* Reset pending पूर्णांकerrupts */

#घोषणा BMA254_RANGE_REG	0x0f
#घोषणा BMA254_BW_REG		0x10
#घोषणा BMA254_POWER_REG	0x11
#घोषणा BMA254_RESET_REG	0x14
#घोषणा BMA254_INT_ENABLE_REG	0x17
#घोषणा BMA254_INT_MAP_REG	0x1a
#घोषणा BMA254_INT_RESET_REG	0x21

#घोषणा BMA254_RANGE_MASK	GENMASK(3, 0) /* Range of accel values */
#घोषणा BMA254_BW_MASK		GENMASK(4, 0) /* Accel bandwidth */
#घोषणा BMA254_SUSPEND_MASK	BIT(7) /* chip will sleep */
#घोषणा BMA254_LOWPOWER_MASK	BIT(6)
#घोषणा BMA254_DATA_INTEN_MASK	BIT(4)
#घोषणा BMA254_INT2_DATA_MASK	BIT(7)
#घोषणा BMA254_INT1_DATA_MASK	BIT(0)
#घोषणा BMA254_INT_RESET_MASK	BIT(7) /* Reset pending पूर्णांकerrupts */

काष्ठा bma180_data अणु
	काष्ठा regulator *vdd_supply;
	काष्ठा regulator *vddio_supply;
	काष्ठा i2c_client *client;
	काष्ठा iio_trigger *trig;
	स्थिर काष्ठा bma180_part_info *part_info;
	काष्ठा iio_mount_matrix orientation;
	काष्ठा mutex mutex;
	bool sleep_state;
	पूर्णांक scale;
	पूर्णांक bw;
	bool pmode;
	u8 buff[16]; /* 3x 16-bit + 8-bit + padding + बारtamp */
पूर्ण;

क्रमागत bma180_chan अणु
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
	TEMP
पूर्ण;

अटल पूर्णांक bma023_bw_table[] = अणु 25, 50, 100, 190, 375, 750, 1500 पूर्ण; /* Hz */
अटल पूर्णांक bma023_scale_table[] = अणु 2452, 4903, 9709, पूर्ण;

अटल पूर्णांक bma180_bw_table[] = अणु 10, 20, 40, 75, 150, 300 पूर्ण; /* Hz */
अटल पूर्णांक bma180_scale_table[] = अणु 1275, 1863, 2452, 3727, 4903, 9709, 19417 पूर्ण;

अटल पूर्णांक bma25x_bw_table[] = अणु 8, 16, 31, 63, 125, 250 पूर्ण; /* Hz */
अटल पूर्णांक bma25x_scale_table[] = अणु 0, 0, 0, 38344, 0, 76590, 0, 0, 153180, 0,
	0, 0, 306458 पूर्ण;

अटल पूर्णांक bma180_get_data_reg(काष्ठा bma180_data *data, क्रमागत bma180_chan chan)
अणु
	पूर्णांक ret;

	अगर (data->sleep_state)
		वापस -EBUSY;

	चयन (chan) अणु
	हाल TEMP:
		ret = i2c_smbus_पढ़ो_byte_data(data->client, BMA180_TEMP);
		अगर (ret < 0)
			dev_err(&data->client->dev, "failed to read temp register\n");
		अवरोध;
	शेष:
		ret = i2c_smbus_पढ़ो_word_data(data->client,
			BMA180_ACC_X_LSB + chan * 2);
		अगर (ret < 0)
			dev_err(&data->client->dev,
				"failed to read accel_%c register\n",
				'x' + chan);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bma180_set_bits(काष्ठा bma180_data *data, u8 reg, u8 mask, u8 val)
अणु
	पूर्णांक ret = i2c_smbus_पढ़ो_byte_data(data->client, reg);
	u8 reg_val = (ret & ~mask) | (val << (ffs(mask) - 1));

	अगर (ret < 0)
		वापस ret;

	वापस i2c_smbus_ग_लिखो_byte_data(data->client, reg, reg_val);
पूर्ण

अटल पूर्णांक bma180_reset_पूर्णांकr(काष्ठा bma180_data *data)
अणु
	पूर्णांक ret = bma180_set_bits(data, data->part_info->पूर्णांक_reset_reg,
		data->part_info->पूर्णांक_reset_mask, 1);

	अगर (ret)
		dev_err(&data->client->dev, "failed to reset interrupt\n");

	वापस ret;
पूर्ण

अटल पूर्णांक bma180_set_new_data_पूर्णांकr_state(काष्ठा bma180_data *data, bool state)
अणु
	पूर्णांक ret = bma180_set_bits(data, data->part_info->पूर्णांक_enable_reg,
			data->part_info->पूर्णांक_enable_mask, state);
	अगर (ret)
		जाओ err;
	ret = bma180_reset_पूर्णांकr(data);
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	dev_err(&data->client->dev,
		"failed to set new data interrupt state %d\n", state);
	वापस ret;
पूर्ण

अटल पूर्णांक bma180_set_sleep_state(काष्ठा bma180_data *data, bool state)
अणु
	पूर्णांक ret = bma180_set_bits(data, data->part_info->sleep_reg,
		data->part_info->sleep_mask, state);

	अगर (ret) अणु
		dev_err(&data->client->dev,
			"failed to set sleep state %d\n", state);
		वापस ret;
	पूर्ण
	data->sleep_state = state;

	वापस 0;
पूर्ण

अटल पूर्णांक bma180_set_ee_writing_state(काष्ठा bma180_data *data, bool state)
अणु
	पूर्णांक ret = bma180_set_bits(data, BMA180_CTRL_REG0, BMA180_EE_W, state);

	अगर (ret)
		dev_err(&data->client->dev,
			"failed to set ee writing state %d\n", state);

	वापस ret;
पूर्ण

अटल पूर्णांक bma180_set_bw(काष्ठा bma180_data *data, पूर्णांक val)
अणु
	पूर्णांक ret, i;

	अगर (data->sleep_state)
		वापस -EBUSY;

	क्रम (i = 0; i < data->part_info->num_bw; ++i) अणु
		अगर (data->part_info->bw_table[i] == val) अणु
			ret = bma180_set_bits(data, data->part_info->bw_reg,
				data->part_info->bw_mask, i);
			अगर (ret) अणु
				dev_err(&data->client->dev,
					"failed to set bandwidth\n");
				वापस ret;
			पूर्ण
			data->bw = val;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bma180_set_scale(काष्ठा bma180_data *data, पूर्णांक val)
अणु
	पूर्णांक ret, i;

	अगर (data->sleep_state)
		वापस -EBUSY;

	क्रम (i = 0; i < data->part_info->num_scales; ++i)
		अगर (data->part_info->scale_table[i] == val) अणु
			ret = bma180_set_bits(data, data->part_info->scale_reg,
				data->part_info->scale_mask, i);
			अगर (ret) अणु
				dev_err(&data->client->dev,
					"failed to set scale\n");
				वापस ret;
			पूर्ण
			data->scale = val;
			वापस 0;
		पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bma180_set_pmode(काष्ठा bma180_data *data, bool mode)
अणु
	u8 reg_val = mode ? data->part_info->lowघातer_val : 0;
	पूर्णांक ret = bma180_set_bits(data, data->part_info->घातer_reg,
		data->part_info->घातer_mask, reg_val);

	अगर (ret) अणु
		dev_err(&data->client->dev, "failed to set power mode\n");
		वापस ret;
	पूर्ण
	data->pmode = mode;

	वापस 0;
पूर्ण

अटल पूर्णांक bma180_soft_reset(काष्ठा bma180_data *data)
अणु
	पूर्णांक ret = i2c_smbus_ग_लिखो_byte_data(data->client,
		data->part_info->softreset_reg,
		data->part_info->softreset_val);

	अगर (ret)
		dev_err(&data->client->dev, "failed to reset the chip\n");

	वापस ret;
पूर्ण

अटल पूर्णांक bma180_chip_init(काष्ठा bma180_data *data)
अणु
	/* Try to पढ़ो chip_id रेजिस्टर. It must वापस 0x03. */
	पूर्णांक ret = i2c_smbus_पढ़ो_byte_data(data->client, BMA180_CHIP_ID);

	अगर (ret < 0)
		वापस ret;
	अगर (ret != data->part_info->chip_id) अणु
		dev_err(&data->client->dev, "wrong chip ID %d expected %d\n",
			ret, data->part_info->chip_id);
		वापस -ENODEV;
	पूर्ण

	ret = bma180_soft_reset(data);
	अगर (ret)
		वापस ret;
	/*
	 * No serial transaction should occur within minimum 10 us
	 * after soft_reset command
	 */
	msleep(20);

	वापस bma180_set_new_data_पूर्णांकr_state(data, false);
पूर्ण

अटल पूर्णांक bma023_chip_config(काष्ठा bma180_data *data)
अणु
	पूर्णांक ret = bma180_chip_init(data);

	अगर (ret)
		जाओ err;

	ret = bma180_set_bw(data, 50); /* 50 Hz */
	अगर (ret)
		जाओ err;
	ret = bma180_set_scale(data, 2452); /* 2 G */
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	dev_err(&data->client->dev, "failed to config the chip\n");
	वापस ret;
पूर्ण

अटल पूर्णांक bma180_chip_config(काष्ठा bma180_data *data)
अणु
	पूर्णांक ret = bma180_chip_init(data);

	अगर (ret)
		जाओ err;
	ret = bma180_set_pmode(data, false);
	अगर (ret)
		जाओ err;
	ret = bma180_set_bits(data, BMA180_CTRL_REG0, BMA180_DIS_WAKE_UP, 1);
	अगर (ret)
		जाओ err;
	ret = bma180_set_ee_writing_state(data, true);
	अगर (ret)
		जाओ err;
	ret = bma180_set_bits(data, BMA180_OFFSET_LSB1, BMA180_SMP_SKIP, 1);
	अगर (ret)
		जाओ err;
	ret = bma180_set_bw(data, 20); /* 20 Hz */
	अगर (ret)
		जाओ err;
	ret = bma180_set_scale(data, 2452); /* 2 G */
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	dev_err(&data->client->dev, "failed to config the chip\n");
	वापस ret;
पूर्ण

अटल पूर्णांक bma25x_chip_config(काष्ठा bma180_data *data)
अणु
	पूर्णांक ret = bma180_chip_init(data);

	अगर (ret)
		जाओ err;
	ret = bma180_set_pmode(data, false);
	अगर (ret)
		जाओ err;
	ret = bma180_set_bw(data, 16); /* 16 Hz */
	अगर (ret)
		जाओ err;
	ret = bma180_set_scale(data, 38344); /* 2 G */
	अगर (ret)
		जाओ err;
	/*
	 * This enables dataपढ़ोy पूर्णांकerrupt on the INT1 pin
	 * FIXME: support using the INT2 pin
	 */
	ret = bma180_set_bits(data, data->part_info->पूर्णांक_map_reg,
		data->part_info->पूर्णांक_enable_dataपढ़ोy_पूर्णांक1_mask, 1);
	अगर (ret)
		जाओ err;

	वापस 0;

err:
	dev_err(&data->client->dev, "failed to config the chip\n");
	वापस ret;
पूर्ण

अटल व्योम bma023_chip_disable(काष्ठा bma180_data *data)
अणु
	अगर (bma180_set_sleep_state(data, true))
		जाओ err;

	वापस;

err:
	dev_err(&data->client->dev, "failed to disable the chip\n");
पूर्ण

अटल व्योम bma180_chip_disable(काष्ठा bma180_data *data)
अणु
	अगर (bma180_set_new_data_पूर्णांकr_state(data, false))
		जाओ err;
	अगर (bma180_set_ee_writing_state(data, false))
		जाओ err;
	अगर (bma180_set_sleep_state(data, true))
		जाओ err;

	वापस;

err:
	dev_err(&data->client->dev, "failed to disable the chip\n");
पूर्ण

अटल व्योम bma25x_chip_disable(काष्ठा bma180_data *data)
अणु
	अगर (bma180_set_new_data_पूर्णांकr_state(data, false))
		जाओ err;
	अगर (bma180_set_sleep_state(data, true))
		जाओ err;

	वापस;

err:
	dev_err(&data->client->dev, "failed to disable the chip\n");
पूर्ण

अटल sमाप_प्रकार bma180_show_avail(अक्षर *buf, स्थिर पूर्णांक *vals, अचिन्हित पूर्णांक n,
				 bool micros)
अणु
	माप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < n; i++) अणु
		अगर (!vals[i])
			जारी;
		len += scnम_लिखो(buf + len, PAGE_SIZE - len,
			micros ? "0.%06d " : "%d ", vals[i]);
	पूर्ण
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल sमाप_प्रकार bma180_show_filter_freq_avail(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bma180_data *data = iio_priv(dev_to_iio_dev(dev));

	वापस bma180_show_avail(buf, data->part_info->bw_table,
		data->part_info->num_bw, false);
पूर्ण

अटल sमाप_प्रकार bma180_show_scale_avail(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा bma180_data *data = iio_priv(dev_to_iio_dev(dev));

	वापस bma180_show_avail(buf, data->part_info->scale_table,
		data->part_info->num_scales, true);
पूर्ण

अटल IIO_DEVICE_ATTR(in_accel_filter_low_pass_3db_frequency_available,
	S_IRUGO, bma180_show_filter_freq_avail, शून्य, 0);

अटल IIO_DEVICE_ATTR(in_accel_scale_available,
	S_IRUGO, bma180_show_scale_avail, शून्य, 0);

अटल काष्ठा attribute *bma180_attributes[] = अणु
	&iio_dev_attr_in_accel_filter_low_pass_3db_frequency_available.
		dev_attr.attr,
	&iio_dev_attr_in_accel_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group bma180_attrs_group = अणु
	.attrs = bma180_attributes,
पूर्ण;

अटल पूर्णांक bma180_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
		काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val, पूर्णांक *val2,
		दीर्घ mask)
अणु
	काष्ठा bma180_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (ret)
			वापस ret;

		mutex_lock(&data->mutex);
		ret = bma180_get_data_reg(data, chan->scan_index);
		mutex_unlock(&data->mutex);
		iio_device_release_direct_mode(indio_dev);
		अगर (ret < 0)
			वापस ret;
		अगर (chan->scan_type.sign == 's') अणु
			*val = sign_extend32(ret >> chan->scan_type.shअगरt,
				chan->scan_type.realbits - 1);
		पूर्ण अन्यथा अणु
			*val = ret;
		पूर्ण
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		*val = data->bw;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_ACCEL:
			*val = 0;
			*val2 = data->scale;
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_TEMP:
			*val = 500;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_OFFSET:
		*val = data->part_info->temp_offset;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक bma180_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
		काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा bma180_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		अगर (val)
			वापस -EINVAL;
		mutex_lock(&data->mutex);
		ret = bma180_set_scale(data, val2);
		mutex_unlock(&data->mutex);
		वापस ret;
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		अगर (val2)
			वापस -EINVAL;
		mutex_lock(&data->mutex);
		ret = bma180_set_bw(data, val);
		mutex_unlock(&data->mutex);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info bma180_info = अणु
	.attrs			= &bma180_attrs_group,
	.पढ़ो_raw		= bma180_पढ़ो_raw,
	.ग_लिखो_raw		= bma180_ग_लिखो_raw,
पूर्ण;

अटल स्थिर अक्षर * स्थिर bma180_घातer_modes[] = अणु "low_noise", "low_power" पूर्ण;

अटल पूर्णांक bma180_get_घातer_mode(काष्ठा iio_dev *indio_dev,
		स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा bma180_data *data = iio_priv(indio_dev);

	वापस data->pmode;
पूर्ण

अटल पूर्णांक bma180_set_घातer_mode(काष्ठा iio_dev *indio_dev,
		स्थिर काष्ठा iio_chan_spec *chan, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा bma180_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = bma180_set_pmode(data, mode);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_mount_matrix *
bma180_accel_get_mount_matrix(स्थिर काष्ठा iio_dev *indio_dev,
				स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा bma180_data *data = iio_priv(indio_dev);

	वापस &data->orientation;
पूर्ण

अटल स्थिर काष्ठा iio_क्रमागत bma180_घातer_mode_क्रमागत = अणु
	.items = bma180_घातer_modes,
	.num_items = ARRAY_SIZE(bma180_घातer_modes),
	.get = bma180_get_घातer_mode,
	.set = bma180_set_घातer_mode,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info bma023_ext_info[] = अणु
	IIO_MOUNT_MATRIX(IIO_SHARED_BY_सूची, bma180_accel_get_mount_matrix),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info bma180_ext_info[] = अणु
	IIO_ENUM("power_mode", IIO_SHARED_BY_TYPE, &bma180_घातer_mode_क्रमागत),
	IIO_ENUM_AVAILABLE("power_mode", &bma180_घातer_mode_क्रमागत),
	IIO_MOUNT_MATRIX(IIO_SHARED_BY_सूची, bma180_accel_get_mount_matrix),
	अणु पूर्ण
पूर्ण;

#घोषणा BMA023_ACC_CHANNEL(_axis, _bits) अणु				\
	.type = IIO_ACCEL,						\
	.modअगरied = 1,							\
	.channel2 = IIO_MOD_##_axis,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),			\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |		\
		BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY),	\
	.scan_index = AXIS_##_axis,					\
	.scan_type = अणु							\
		.sign = 's',						\
		.realbits = _bits,					\
		.storagebits = 16,					\
		.shअगरt = 16 - _bits,					\
	पूर्ण,								\
	.ext_info = bma023_ext_info,					\
पूर्ण

#घोषणा BMA150_TEMP_CHANNEL अणु						\
	.type = IIO_TEMP,						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |			\
		BIT(IIO_CHAN_INFO_SCALE) | BIT(IIO_CHAN_INFO_OFFSET),	\
	.scan_index = TEMP,						\
	.scan_type = अणु							\
		.sign = 'u',						\
		.realbits = 8,						\
		.storagebits = 16,					\
	पूर्ण,								\
पूर्ण

#घोषणा BMA180_ACC_CHANNEL(_axis, _bits) अणु				\
	.type = IIO_ACCEL,						\
	.modअगरied = 1,							\
	.channel2 = IIO_MOD_##_axis,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),			\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |		\
		BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY),	\
	.scan_index = AXIS_##_axis,					\
	.scan_type = अणु							\
		.sign = 's',						\
		.realbits = _bits,					\
		.storagebits = 16,					\
		.shअगरt = 16 - _bits,					\
	पूर्ण,								\
	.ext_info = bma180_ext_info,					\
पूर्ण

#घोषणा BMA180_TEMP_CHANNEL अणु						\
	.type = IIO_TEMP,						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |			\
		BIT(IIO_CHAN_INFO_SCALE) | BIT(IIO_CHAN_INFO_OFFSET),	\
	.scan_index = TEMP,						\
	.scan_type = अणु							\
		.sign = 's',						\
		.realbits = 8,						\
		.storagebits = 16,					\
	पूर्ण,								\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec bma023_channels[] = अणु
	BMA023_ACC_CHANNEL(X, 10),
	BMA023_ACC_CHANNEL(Y, 10),
	BMA023_ACC_CHANNEL(Z, 10),
	IIO_CHAN_SOFT_TIMESTAMP(4),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec bma150_channels[] = अणु
	BMA023_ACC_CHANNEL(X, 10),
	BMA023_ACC_CHANNEL(Y, 10),
	BMA023_ACC_CHANNEL(Z, 10),
	BMA150_TEMP_CHANNEL,
	IIO_CHAN_SOFT_TIMESTAMP(4),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec bma180_channels[] = अणु
	BMA180_ACC_CHANNEL(X, 14),
	BMA180_ACC_CHANNEL(Y, 14),
	BMA180_ACC_CHANNEL(Z, 14),
	BMA180_TEMP_CHANNEL,
	IIO_CHAN_SOFT_TIMESTAMP(4),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec bma250_channels[] = अणु
	BMA180_ACC_CHANNEL(X, 10),
	BMA180_ACC_CHANNEL(Y, 10),
	BMA180_ACC_CHANNEL(Z, 10),
	BMA180_TEMP_CHANNEL,
	IIO_CHAN_SOFT_TIMESTAMP(4),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec bma254_channels[] = अणु
	BMA180_ACC_CHANNEL(X, 12),
	BMA180_ACC_CHANNEL(Y, 12),
	BMA180_ACC_CHANNEL(Z, 12),
	BMA180_TEMP_CHANNEL,
	IIO_CHAN_SOFT_TIMESTAMP(4),
पूर्ण;

अटल स्थिर काष्ठा bma180_part_info bma180_part_info[] = अणु
	[BMA023] = अणु
		.chip_id = BMA023_ID_REG_VAL,
		.channels = bma023_channels,
		.num_channels = ARRAY_SIZE(bma023_channels),
		.scale_table = bma023_scale_table,
		.num_scales = ARRAY_SIZE(bma023_scale_table),
		.bw_table = bma023_bw_table,
		.num_bw = ARRAY_SIZE(bma023_bw_table),
		/* No temperature channel */
		.temp_offset = 0,
		.पूर्णांक_reset_reg = BMA023_CTRL_REG0,
		.पूर्णांक_reset_mask = BMA023_INT_RESET_MASK,
		.sleep_reg = BMA023_CTRL_REG0,
		.sleep_mask = BMA023_SLEEP,
		.bw_reg = BMA023_CTRL_REG2,
		.bw_mask = BMA023_BW_MASK,
		.scale_reg = BMA023_CTRL_REG2,
		.scale_mask = BMA023_RANGE_MASK,
		/* No घातer mode on bma023 */
		.घातer_reg = 0,
		.घातer_mask = 0,
		.lowघातer_val = 0,
		.पूर्णांक_enable_reg = BMA023_CTRL_REG3,
		.पूर्णांक_enable_mask = BMA023_NEW_DATA_INT,
		.softreset_reg = BMA023_CTRL_REG0,
		.softreset_val = BMA023_RESET_VAL,
		.chip_config = bma023_chip_config,
		.chip_disable = bma023_chip_disable,
	पूर्ण,
	[BMA150] = अणु
		.chip_id = BMA023_ID_REG_VAL,
		.channels = bma150_channels,
		.num_channels = ARRAY_SIZE(bma150_channels),
		.scale_table = bma023_scale_table,
		.num_scales = ARRAY_SIZE(bma023_scale_table),
		.bw_table = bma023_bw_table,
		.num_bw = ARRAY_SIZE(bma023_bw_table),
		.temp_offset = -60, /* 0 LSB @ -30 degree C */
		.पूर्णांक_reset_reg = BMA023_CTRL_REG0,
		.पूर्णांक_reset_mask = BMA023_INT_RESET_MASK,
		.sleep_reg = BMA023_CTRL_REG0,
		.sleep_mask = BMA023_SLEEP,
		.bw_reg = BMA023_CTRL_REG2,
		.bw_mask = BMA023_BW_MASK,
		.scale_reg = BMA023_CTRL_REG2,
		.scale_mask = BMA023_RANGE_MASK,
		/* No घातer mode on bma150 */
		.घातer_reg = 0,
		.घातer_mask = 0,
		.lowघातer_val = 0,
		.पूर्णांक_enable_reg = BMA023_CTRL_REG3,
		.पूर्णांक_enable_mask = BMA023_NEW_DATA_INT,
		.softreset_reg = BMA023_CTRL_REG0,
		.softreset_val = BMA023_RESET_VAL,
		.chip_config = bma023_chip_config,
		.chip_disable = bma023_chip_disable,
	पूर्ण,
	[BMA180] = अणु
		.chip_id = BMA180_ID_REG_VAL,
		.channels = bma180_channels,
		.num_channels = ARRAY_SIZE(bma180_channels),
		.scale_table = bma180_scale_table,
		.num_scales = ARRAY_SIZE(bma180_scale_table),
		.bw_table = bma180_bw_table,
		.num_bw = ARRAY_SIZE(bma180_bw_table),
		.temp_offset = 48, /* 0 LSB @ 24 degree C */
		.पूर्णांक_reset_reg = BMA180_CTRL_REG0,
		.पूर्णांक_reset_mask = BMA180_RESET_INT,
		.sleep_reg = BMA180_CTRL_REG0,
		.sleep_mask = BMA180_SLEEP,
		.bw_reg = BMA180_BW_TCS,
		.bw_mask = BMA180_BW,
		.scale_reg = BMA180_OFFSET_LSB1,
		.scale_mask = BMA180_RANGE,
		.घातer_reg = BMA180_TCO_Z,
		.घातer_mask = BMA180_MODE_CONFIG,
		.lowघातer_val = BMA180_LOW_POWER,
		.पूर्णांक_enable_reg = BMA180_CTRL_REG3,
		.पूर्णांक_enable_mask = BMA180_NEW_DATA_INT,
		.softreset_reg = BMA180_RESET,
		.softreset_val = BMA180_RESET_VAL,
		.chip_config = bma180_chip_config,
		.chip_disable = bma180_chip_disable,
	पूर्ण,
	[BMA250] = अणु
		.chip_id = BMA250_ID_REG_VAL,
		.channels = bma250_channels,
		.num_channels = ARRAY_SIZE(bma250_channels),
		.scale_table = bma25x_scale_table,
		.num_scales = ARRAY_SIZE(bma25x_scale_table),
		.bw_table = bma25x_bw_table,
		.num_bw = ARRAY_SIZE(bma25x_bw_table),
		.temp_offset = 48, /* 0 LSB @ 24 degree C */
		.पूर्णांक_reset_reg = BMA250_INT_RESET_REG,
		.पूर्णांक_reset_mask = BMA250_INT_RESET_MASK,
		.sleep_reg = BMA250_POWER_REG,
		.sleep_mask = BMA250_SUSPEND_MASK,
		.bw_reg = BMA250_BW_REG,
		.bw_mask = BMA250_BW_MASK,
		.scale_reg = BMA250_RANGE_REG,
		.scale_mask = BMA250_RANGE_MASK,
		.घातer_reg = BMA250_POWER_REG,
		.घातer_mask = BMA250_LOWPOWER_MASK,
		.lowघातer_val = 1,
		.पूर्णांक_enable_reg = BMA250_INT_ENABLE_REG,
		.पूर्णांक_enable_mask = BMA250_DATA_INTEN_MASK,
		.पूर्णांक_map_reg = BMA250_INT_MAP_REG,
		.पूर्णांक_enable_dataपढ़ोy_पूर्णांक1_mask = BMA250_INT1_DATA_MASK,
		.softreset_reg = BMA250_RESET_REG,
		.softreset_val = BMA180_RESET_VAL,
		.chip_config = bma25x_chip_config,
		.chip_disable = bma25x_chip_disable,
	पूर्ण,
	[BMA254] = अणु
		.chip_id = BMA254_ID_REG_VAL,
		.channels = bma254_channels,
		.num_channels = ARRAY_SIZE(bma254_channels),
		.scale_table = bma25x_scale_table,
		.num_scales = ARRAY_SIZE(bma25x_scale_table),
		.bw_table = bma25x_bw_table,
		.num_bw = ARRAY_SIZE(bma25x_bw_table),
		.temp_offset = 46, /* 0 LSB @ 23 degree C */
		.पूर्णांक_reset_reg = BMA254_INT_RESET_REG,
		.पूर्णांक_reset_mask = BMA254_INT_RESET_MASK,
		.sleep_reg = BMA254_POWER_REG,
		.sleep_mask = BMA254_SUSPEND_MASK,
		.bw_reg = BMA254_BW_REG,
		.bw_mask = BMA254_BW_MASK,
		.scale_reg = BMA254_RANGE_REG,
		.scale_mask = BMA254_RANGE_MASK,
		.घातer_reg = BMA254_POWER_REG,
		.घातer_mask = BMA254_LOWPOWER_MASK,
		.lowघातer_val = 1,
		.पूर्णांक_enable_reg = BMA254_INT_ENABLE_REG,
		.पूर्णांक_enable_mask = BMA254_DATA_INTEN_MASK,
		.पूर्णांक_map_reg = BMA254_INT_MAP_REG,
		.पूर्णांक_enable_dataपढ़ोy_पूर्णांक1_mask = BMA254_INT1_DATA_MASK,
		.softreset_reg = BMA254_RESET_REG,
		.softreset_val = BMA180_RESET_VAL,
		.chip_config = bma25x_chip_config,
		.chip_disable = bma25x_chip_disable,
	पूर्ण,
पूर्ण;

अटल irqवापस_t bma180_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा bma180_data *data = iio_priv(indio_dev);
	s64 समय_ns = iio_get_समय_ns(indio_dev);
	पूर्णांक bit, ret, i = 0;

	mutex_lock(&data->mutex);

	क्रम_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->masklength) अणु
		ret = bma180_get_data_reg(data, bit);
		अगर (ret < 0) अणु
			mutex_unlock(&data->mutex);
			जाओ err;
		पूर्ण
		((s16 *)data->buff)[i++] = ret;
	पूर्ण

	mutex_unlock(&data->mutex);

	iio_push_to_buffers_with_बारtamp(indio_dev, data->buff, समय_ns);
err:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bma180_data_rdy_trigger_set_state(काष्ठा iio_trigger *trig,
		bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा bma180_data *data = iio_priv(indio_dev);

	वापस bma180_set_new_data_पूर्णांकr_state(data, state);
पूर्ण

अटल व्योम bma180_trig_reen(काष्ठा iio_trigger *trig)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा bma180_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = bma180_reset_पूर्णांकr(data);
	अगर (ret)
		dev_err(&data->client->dev, "failed to reset interrupt\n");
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops bma180_trigger_ops = अणु
	.set_trigger_state = bma180_data_rdy_trigger_set_state,
	.reenable = bma180_trig_reen,
पूर्ण;

अटल पूर्णांक bma180_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा bma180_data *data;
	काष्ठा iio_dev *indio_dev;
	क्रमागत chip_ids chip;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	अगर (client->dev.of_node)
		chip = (क्रमागत chip_ids)of_device_get_match_data(dev);
	अन्यथा
		chip = id->driver_data;
	data->part_info = &bma180_part_info[chip];

	ret = iio_पढ़ो_mount_matrix(dev, "mount-matrix",
				&data->orientation);
	अगर (ret)
		वापस ret;

	data->vdd_supply = devm_regulator_get(dev, "vdd");
	अगर (IS_ERR(data->vdd_supply))
		वापस dev_err_probe(dev, PTR_ERR(data->vdd_supply),
				     "Failed to get vdd regulator\n");

	data->vddio_supply = devm_regulator_get(dev, "vddio");
	अगर (IS_ERR(data->vddio_supply))
		वापस dev_err_probe(dev, PTR_ERR(data->vddio_supply),
				     "Failed to get vddio regulator\n");

	/* Typical voltage 2.4V these are min and max */
	ret = regulator_set_voltage(data->vdd_supply, 1620000, 3600000);
	अगर (ret)
		वापस ret;
	ret = regulator_set_voltage(data->vddio_supply, 1200000, 3600000);
	अगर (ret)
		वापस ret;
	ret = regulator_enable(data->vdd_supply);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable vdd regulator: %d\n", ret);
		वापस ret;
	पूर्ण
	ret = regulator_enable(data->vddio_supply);
	अगर (ret) अणु
		dev_err(dev, "Failed to enable vddio regulator: %d\n", ret);
		जाओ err_disable_vdd;
	पूर्ण
	/* Wait to make sure we started up properly (3 ms at least) */
	usleep_range(3000, 5000);

	ret = data->part_info->chip_config(data);
	अगर (ret < 0)
		जाओ err_chip_disable;

	mutex_init(&data->mutex);
	indio_dev->channels = data->part_info->channels;
	indio_dev->num_channels = data->part_info->num_channels;
	indio_dev->name = id->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &bma180_info;

	अगर (client->irq > 0) अणु
		data->trig = iio_trigger_alloc(dev, "%s-dev%d", indio_dev->name,
			indio_dev->id);
		अगर (!data->trig) अणु
			ret = -ENOMEM;
			जाओ err_chip_disable;
		पूर्ण

		ret = devm_request_irq(dev, client->irq,
			iio_trigger_generic_data_rdy_poll, IRQF_TRIGGER_RISING,
			"bma180_event", data->trig);
		अगर (ret) अणु
			dev_err(dev, "unable to request IRQ\n");
			जाओ err_trigger_मुक्त;
		पूर्ण

		data->trig->ops = &bma180_trigger_ops;
		iio_trigger_set_drvdata(data->trig, indio_dev);
		indio_dev->trig = iio_trigger_get(data->trig);

		ret = iio_trigger_रेजिस्टर(data->trig);
		अगर (ret)
			जाओ err_trigger_मुक्त;
	पूर्ण

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
			bma180_trigger_handler, शून्य);
	अगर (ret < 0) अणु
		dev_err(dev, "unable to setup iio triggered buffer\n");
		जाओ err_trigger_unरेजिस्टर;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(dev, "unable to register iio device\n");
		जाओ err_buffer_cleanup;
	पूर्ण

	वापस 0;

err_buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
err_trigger_unरेजिस्टर:
	अगर (data->trig)
		iio_trigger_unरेजिस्टर(data->trig);
err_trigger_मुक्त:
	iio_trigger_मुक्त(data->trig);
err_chip_disable:
	data->part_info->chip_disable(data);
	regulator_disable(data->vddio_supply);
err_disable_vdd:
	regulator_disable(data->vdd_supply);

	वापस ret;
पूर्ण

अटल पूर्णांक bma180_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा bma180_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);
	अगर (data->trig) अणु
		iio_trigger_unरेजिस्टर(data->trig);
		iio_trigger_मुक्त(data->trig);
	पूर्ण

	mutex_lock(&data->mutex);
	data->part_info->chip_disable(data);
	mutex_unlock(&data->mutex);
	regulator_disable(data->vddio_supply);
	regulator_disable(data->vdd_supply);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक bma180_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा bma180_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = bma180_set_sleep_state(data, true);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक bma180_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा bma180_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = bma180_set_sleep_state(data, false);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(bma180_pm_ops, bma180_suspend, bma180_resume);
#घोषणा BMA180_PM_OPS (&bma180_pm_ops)
#अन्यथा
#घोषणा BMA180_PM_OPS शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id bma180_ids[] = अणु
	अणु "bma023", BMA023 पूर्ण,
	अणु "bma150", BMA150 पूर्ण,
	अणु "bma180", BMA180 पूर्ण,
	अणु "bma250", BMA250 पूर्ण,
	अणु "bma254", BMA254 पूर्ण,
	अणु "smb380", BMA150 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, bma180_ids);

अटल स्थिर काष्ठा of_device_id bma180_of_match[] = अणु
	अणु
		.compatible = "bosch,bma023",
		.data = (व्योम *)BMA023
	पूर्ण,
	अणु
		.compatible = "bosch,bma150",
		.data = (व्योम *)BMA150
	पूर्ण,
	अणु
		.compatible = "bosch,bma180",
		.data = (व्योम *)BMA180
	पूर्ण,
	अणु
		.compatible = "bosch,bma250",
		.data = (व्योम *)BMA250
	पूर्ण,
	अणु
		.compatible = "bosch,bma254",
		.data = (व्योम *)BMA254
	पूर्ण,
	अणु
		.compatible = "bosch,smb380",
		.data = (व्योम *)BMA150
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bma180_of_match);

अटल काष्ठा i2c_driver bma180_driver = अणु
	.driver = अणु
		.name	= "bma180",
		.pm	= BMA180_PM_OPS,
		.of_match_table = bma180_of_match,
	पूर्ण,
	.probe		= bma180_probe,
	.हटाओ		= bma180_हटाओ,
	.id_table	= bma180_ids,
पूर्ण;

module_i2c_driver(bma180_driver);

MODULE_AUTHOR("Kravchenko Oleksandr <x0199363@ti.com>");
MODULE_AUTHOR("Texas Instruments, Inc.");
MODULE_DESCRIPTION("Bosch BMA023/BMA1x0/BMA25x triaxial acceleration sensor");
MODULE_LICENSE("GPL");
