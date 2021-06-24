<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * KMX61 - Kionix 6-axis Accelerometer/Magnetometer
 *
 * Copyright (c) 2014, Intel Corporation.
 *
 * IIO driver क्रम KMX61 (7-bit I2C slave address 0x0E or 0x0F).
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/acpi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>

#घोषणा KMX61_DRV_NAME "kmx61"
#घोषणा KMX61_IRQ_NAME "kmx61_event"

#घोषणा KMX61_REG_WHO_AM_I	0x00
#घोषणा KMX61_REG_INS1		0x01
#घोषणा KMX61_REG_INS2		0x02

/*
 * three 16-bit accelerometer output रेजिस्टरs क्रम X/Y/Z axis
 * we use only XOUT_L as a base रेजिस्टर, all other addresses
 * can be obtained by applying an offset and are provided here
 * only क्रम clarity.
 */
#घोषणा KMX61_ACC_XOUT_L	0x0A
#घोषणा KMX61_ACC_XOUT_H	0x0B
#घोषणा KMX61_ACC_YOUT_L	0x0C
#घोषणा KMX61_ACC_YOUT_H	0x0D
#घोषणा KMX61_ACC_ZOUT_L	0x0E
#घोषणा KMX61_ACC_ZOUT_H	0x0F

/*
 * one 16-bit temperature output रेजिस्टर
 */
#घोषणा KMX61_TEMP_L		0x10
#घोषणा KMX61_TEMP_H		0x11

/*
 * three 16-bit magnetometer output रेजिस्टरs क्रम X/Y/Z axis
 */
#घोषणा KMX61_MAG_XOUT_L	0x12
#घोषणा KMX61_MAG_XOUT_H	0x13
#घोषणा KMX61_MAG_YOUT_L	0x14
#घोषणा KMX61_MAG_YOUT_H	0x15
#घोषणा KMX61_MAG_ZOUT_L	0x16
#घोषणा KMX61_MAG_ZOUT_H	0x17

#घोषणा KMX61_REG_INL		0x28
#घोषणा KMX61_REG_STBY		0x29
#घोषणा KMX61_REG_CTRL1		0x2A
#घोषणा KMX61_REG_CTRL2		0x2B
#घोषणा KMX61_REG_ODCNTL	0x2C
#घोषणा KMX61_REG_INC1		0x2D

#घोषणा KMX61_REG_WUF_THRESH	0x3D
#घोषणा KMX61_REG_WUF_TIMER	0x3E

#घोषणा KMX61_ACC_STBY_BIT	BIT(0)
#घोषणा KMX61_MAG_STBY_BIT	BIT(1)
#घोषणा KMX61_ACT_STBY_BIT	BIT(7)

#घोषणा KMX61_ALL_STBY		(KMX61_ACC_STBY_BIT | KMX61_MAG_STBY_BIT)

#घोषणा KMX61_REG_INS1_BIT_WUFS		BIT(1)

#घोषणा KMX61_REG_INS2_BIT_ZP		BIT(0)
#घोषणा KMX61_REG_INS2_BIT_ZN		BIT(1)
#घोषणा KMX61_REG_INS2_BIT_YP		BIT(2)
#घोषणा KMX61_REG_INS2_BIT_YN		BIT(3)
#घोषणा KMX61_REG_INS2_BIT_XP		BIT(4)
#घोषणा KMX61_REG_INS2_BIT_XN		BIT(5)

#घोषणा KMX61_REG_CTRL1_GSEL_MASK	0x03

#घोषणा KMX61_REG_CTRL1_BIT_RES		BIT(4)
#घोषणा KMX61_REG_CTRL1_BIT_DRDYE	BIT(5)
#घोषणा KMX61_REG_CTRL1_BIT_WUFE	BIT(6)
#घोषणा KMX61_REG_CTRL1_BIT_BTSE	BIT(7)

#घोषणा KMX61_REG_INC1_BIT_WUFS		BIT(0)
#घोषणा KMX61_REG_INC1_BIT_DRDYM	BIT(1)
#घोषणा KMX61_REG_INC1_BIT_DRDYA	BIT(2)
#घोषणा KMX61_REG_INC1_BIT_IEN		BIT(5)

#घोषणा KMX61_ACC_ODR_SHIFT	0
#घोषणा KMX61_MAG_ODR_SHIFT	4
#घोषणा KMX61_ACC_ODR_MASK	0x0F
#घोषणा KMX61_MAG_ODR_MASK	0xF0

#घोषणा KMX61_OWUF_MASK		0x7

#घोषणा KMX61_DEFAULT_WAKE_THRESH	1
#घोषणा KMX61_DEFAULT_WAKE_DURATION	1

#घोषणा KMX61_SLEEP_DELAY_MS	2000

#घोषणा KMX61_CHIP_ID		0x12

/* KMX61 devices */
#घोषणा KMX61_ACC	0x01
#घोषणा KMX61_MAG	0x02

काष्ठा kmx61_data अणु
	काष्ठा i2c_client *client;

	/* serialize access to non-atomic ops, e.g set_mode */
	काष्ठा mutex lock;

	/* standby state */
	bool acc_stby;
	bool mag_stby;

	/* घातer state */
	bool acc_ps;
	bool mag_ps;

	/* config bits */
	u8 range;
	u8 odr_bits;
	u8 wake_thresh;
	u8 wake_duration;

	/* accelerometer specअगरic data */
	काष्ठा iio_dev *acc_indio_dev;
	काष्ठा iio_trigger *acc_dपढ़ोy_trig;
	काष्ठा iio_trigger *motion_trig;
	bool acc_dपढ़ोy_trig_on;
	bool motion_trig_on;
	bool ev_enable_state;

	/* magnetometer specअगरic data */
	काष्ठा iio_dev *mag_indio_dev;
	काष्ठा iio_trigger *mag_dपढ़ोy_trig;
	bool mag_dपढ़ोy_trig_on;
पूर्ण;

क्रमागत kmx61_range अणु
	KMX61_RANGE_2G,
	KMX61_RANGE_4G,
	KMX61_RANGE_8G,
पूर्ण;

क्रमागत kmx61_axis अणु
	KMX61_AXIS_X,
	KMX61_AXIS_Y,
	KMX61_AXIS_Z,
पूर्ण;

अटल स्थिर u16 kmx61_uscale_table[] = अणु9582, 19163, 38326पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक val;
	पूर्णांक val2;
पूर्ण kmx61_samp_freq_table[] = अणु अणु12, 500000पूर्ण,
			अणु25, 0पूर्ण,
			अणु50, 0पूर्ण,
			अणु100, 0पूर्ण,
			अणु200, 0पूर्ण,
			अणु400, 0पूर्ण,
			अणु800, 0पूर्ण,
			अणु1600, 0पूर्ण,
			अणु0, 781000पूर्ण,
			अणु1, 563000पूर्ण,
			अणु3, 125000पूर्ण,
			अणु6, 250000पूर्ण पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक val;
	पूर्णांक val2;
	पूर्णांक odr_bits;
पूर्ण kmx61_wake_up_odr_table[] = अणु अणु0, 781000, 0x00पूर्ण,
				 अणु1, 563000, 0x01पूर्ण,
				 अणु3, 125000, 0x02पूर्ण,
				 अणु6, 250000, 0x03पूर्ण,
				 अणु12, 500000, 0x04पूर्ण,
				 अणु25, 0, 0x05पूर्ण,
				 अणु50, 0, 0x06पूर्ण,
				 अणु100, 0, 0x06पूर्ण,
				 अणु200, 0, 0x06पूर्ण,
				 अणु400, 0, 0x06पूर्ण,
				 अणु800, 0, 0x06पूर्ण,
				 अणु1600, 0, 0x06पूर्ण पूर्ण;

अटल IIO_CONST_ATTR(accel_scale_available, "0.009582 0.019163 0.038326");
अटल IIO_CONST_ATTR(magn_scale_available, "0.001465");
अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL(
	"0.781000 1.563000 3.125000 6.250000 12.500000 25 50 100 200 400 800");

अटल काष्ठा attribute *kmx61_acc_attributes[] = अणु
	&iio_स्थिर_attr_accel_scale_available.dev_attr.attr,
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute *kmx61_mag_attributes[] = अणु
	&iio_स्थिर_attr_magn_scale_available.dev_attr.attr,
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group kmx61_acc_attribute_group = अणु
	.attrs = kmx61_acc_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group kmx61_mag_attribute_group = अणु
	.attrs = kmx61_mag_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec kmx61_event = अणु
	.type = IIO_EV_TYPE_THRESH,
	.dir = IIO_EV_सूची_EITHER,
	.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			 BIT(IIO_EV_INFO_ENABLE) |
			 BIT(IIO_EV_INFO_PERIOD),
पूर्ण;

#घोषणा KMX61_ACC_CHAN(_axis) अणु \
	.type = IIO_ACCEL, \
	.modअगरied = 1, \
	.channel2 = IIO_MOD_ ## _axis, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) | \
				BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.address = KMX61_ACC, \
	.scan_index = KMX61_AXIS_ ## _axis, \
	.scan_type = अणु \
		.sign = 's', \
		.realbits = 12, \
		.storagebits = 16, \
		.shअगरt = 4, \
		.endianness = IIO_LE, \
	पूर्ण, \
	.event_spec = &kmx61_event, \
	.num_event_specs = 1 \
पूर्ण

#घोषणा KMX61_MAG_CHAN(_axis) अणु \
	.type = IIO_MAGN, \
	.modअगरied = 1, \
	.channel2 = IIO_MOD_ ## _axis, \
	.address = KMX61_MAG, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) | \
				BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.scan_index = KMX61_AXIS_ ## _axis, \
	.scan_type = अणु \
		.sign = 's', \
		.realbits = 14, \
		.storagebits = 16, \
		.shअगरt = 2, \
		.endianness = IIO_LE, \
	पूर्ण, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec kmx61_acc_channels[] = अणु
	KMX61_ACC_CHAN(X),
	KMX61_ACC_CHAN(Y),
	KMX61_ACC_CHAN(Z),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec kmx61_mag_channels[] = अणु
	KMX61_MAG_CHAN(X),
	KMX61_MAG_CHAN(Y),
	KMX61_MAG_CHAN(Z),
पूर्ण;

अटल व्योम kmx61_set_data(काष्ठा iio_dev *indio_dev, काष्ठा kmx61_data *data)
अणु
	काष्ठा kmx61_data **priv = iio_priv(indio_dev);

	*priv = data;
पूर्ण

अटल काष्ठा kmx61_data *kmx61_get_data(काष्ठा iio_dev *indio_dev)
अणु
	वापस *(काष्ठा kmx61_data **)iio_priv(indio_dev);
पूर्ण

अटल पूर्णांक kmx61_convert_freq_to_bit(पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(kmx61_samp_freq_table); i++)
		अगर (val == kmx61_samp_freq_table[i].val &&
		    val2 == kmx61_samp_freq_table[i].val2)
			वापस i;
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक kmx61_convert_wake_up_odr_to_bit(पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(kmx61_wake_up_odr_table); ++i)
		अगर (kmx61_wake_up_odr_table[i].val == val &&
			kmx61_wake_up_odr_table[i].val2 == val2)
				वापस kmx61_wake_up_odr_table[i].odr_bits;
	वापस -EINVAL;
पूर्ण

/**
 * kmx61_set_mode() - set KMX61 device operating mode
 * @data: kmx61 device निजी data poपूर्णांकer
 * @mode: biपंचांगask, indicating operating mode क्रम @device
 * @device: biपंचांगask, indicating device क्रम which @mode needs to be set
 * @update: update stby bits stored in device's निजी  @data
 *
 * For each sensor (accelerometer/magnetometer) there are two operating modes
 * STANDBY and OPERATION. Neither accel nor magn can be disabled independently
 * अगर they are both enabled. Internal sensors state is saved in acc_stby and
 * mag_stby members of driver's निजी @data.
 */
अटल पूर्णांक kmx61_set_mode(काष्ठा kmx61_data *data, u8 mode, u8 device,
			  bool update)
अणु
	पूर्णांक ret;
	पूर्णांक acc_stby = -1, mag_stby = -1;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KMX61_REG_STBY);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_stby\n");
		वापस ret;
	पूर्ण
	अगर (device & KMX61_ACC) अणु
		अगर (mode & KMX61_ACC_STBY_BIT) अणु
			ret |= KMX61_ACC_STBY_BIT;
			acc_stby = 1;
		पूर्ण अन्यथा अणु
			ret &= ~KMX61_ACC_STBY_BIT;
			acc_stby = 0;
		पूर्ण
	पूर्ण

	अगर (device & KMX61_MAG) अणु
		अगर (mode & KMX61_MAG_STBY_BIT) अणु
			ret |= KMX61_MAG_STBY_BIT;
			mag_stby = 1;
		पूर्ण अन्यथा अणु
			ret &= ~KMX61_MAG_STBY_BIT;
			mag_stby = 0;
		पूर्ण
	पूर्ण

	अगर (mode & KMX61_ACT_STBY_BIT)
		ret |= KMX61_ACT_STBY_BIT;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, KMX61_REG_STBY, ret);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error writing reg_stby\n");
		वापस ret;
	पूर्ण

	अगर (acc_stby != -1 && update)
		data->acc_stby = acc_stby;
	अगर (mag_stby != -1 && update)
		data->mag_stby = mag_stby;

	वापस 0;
पूर्ण

अटल पूर्णांक kmx61_get_mode(काष्ठा kmx61_data *data, u8 *mode, u8 device)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KMX61_REG_STBY);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_stby\n");
		वापस ret;
	पूर्ण
	*mode = 0;

	अगर (device & KMX61_ACC) अणु
		अगर (ret & KMX61_ACC_STBY_BIT)
			*mode |= KMX61_ACC_STBY_BIT;
		अन्यथा
			*mode &= ~KMX61_ACC_STBY_BIT;
	पूर्ण

	अगर (device & KMX61_MAG) अणु
		अगर (ret & KMX61_MAG_STBY_BIT)
			*mode |= KMX61_MAG_STBY_BIT;
		अन्यथा
			*mode &= ~KMX61_MAG_STBY_BIT;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kmx61_set_wake_up_odr(काष्ठा kmx61_data *data, पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक ret, odr_bits;

	odr_bits = kmx61_convert_wake_up_odr_to_bit(val, val2);
	अगर (odr_bits < 0)
		वापस odr_bits;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, KMX61_REG_CTRL2,
					odr_bits);
	अगर (ret < 0)
		dev_err(&data->client->dev, "Error writing reg_ctrl2\n");
	वापस ret;
पूर्ण

अटल पूर्णांक kmx61_set_odr(काष्ठा kmx61_data *data, पूर्णांक val, पूर्णांक val2, u8 device)
अणु
	पूर्णांक ret;
	u8 mode;
	पूर्णांक lodr_bits, odr_bits;

	ret = kmx61_get_mode(data, &mode, KMX61_ACC | KMX61_MAG);
	अगर (ret < 0)
		वापस ret;

	lodr_bits = kmx61_convert_freq_to_bit(val, val2);
	अगर (lodr_bits < 0)
		वापस lodr_bits;

	/* To change ODR, accel and magn must be in STDBY */
	ret = kmx61_set_mode(data, KMX61_ALL_STBY, KMX61_ACC | KMX61_MAG,
			     true);
	अगर (ret < 0)
		वापस ret;

	odr_bits = 0;
	अगर (device & KMX61_ACC)
		odr_bits |= lodr_bits << KMX61_ACC_ODR_SHIFT;
	अगर (device & KMX61_MAG)
		odr_bits |= lodr_bits << KMX61_MAG_ODR_SHIFT;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, KMX61_REG_ODCNTL,
					odr_bits);
	अगर (ret < 0)
		वापस ret;

	data->odr_bits = odr_bits;

	अगर (device & KMX61_ACC) अणु
		ret = kmx61_set_wake_up_odr(data, val, val2);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस kmx61_set_mode(data, mode, KMX61_ACC | KMX61_MAG, true);
पूर्ण

अटल पूर्णांक kmx61_get_odr(काष्ठा kmx61_data *data, पूर्णांक *val, पूर्णांक *val2,
			 u8 device)
अणु
	u8 lodr_bits;

	अगर (device & KMX61_ACC)
		lodr_bits = (data->odr_bits >> KMX61_ACC_ODR_SHIFT) &
			     KMX61_ACC_ODR_MASK;
	अन्यथा अगर (device & KMX61_MAG)
		lodr_bits = (data->odr_bits >> KMX61_MAG_ODR_SHIFT) &
			     KMX61_MAG_ODR_MASK;
	अन्यथा
		वापस -EINVAL;

	अगर (lodr_bits >= ARRAY_SIZE(kmx61_samp_freq_table))
		वापस -EINVAL;

	*val = kmx61_samp_freq_table[lodr_bits].val;
	*val2 = kmx61_samp_freq_table[lodr_bits].val2;

	वापस 0;
पूर्ण

अटल पूर्णांक kmx61_set_range(काष्ठा kmx61_data *data, u8 range)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KMX61_REG_CTRL1);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_ctrl1\n");
		वापस ret;
	पूर्ण

	ret &= ~KMX61_REG_CTRL1_GSEL_MASK;
	ret |= range & KMX61_REG_CTRL1_GSEL_MASK;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, KMX61_REG_CTRL1, ret);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error writing reg_ctrl1\n");
		वापस ret;
	पूर्ण

	data->range = range;

	वापस 0;
पूर्ण

अटल पूर्णांक kmx61_set_scale(काष्ठा kmx61_data *data, u16 uscale)
अणु
	पूर्णांक ret, i;
	u8  mode;

	क्रम (i = 0; i < ARRAY_SIZE(kmx61_uscale_table); i++) अणु
		अगर (kmx61_uscale_table[i] == uscale) अणु
			ret = kmx61_get_mode(data, &mode,
					     KMX61_ACC | KMX61_MAG);
			अगर (ret < 0)
				वापस ret;

			ret = kmx61_set_mode(data, KMX61_ALL_STBY,
					     KMX61_ACC | KMX61_MAG, true);
			अगर (ret < 0)
				वापस ret;

			ret = kmx61_set_range(data, i);
			अगर (ret < 0)
				वापस ret;

			वापस  kmx61_set_mode(data, mode,
					       KMX61_ACC | KMX61_MAG, true);
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक kmx61_chip_init(काष्ठा kmx61_data *data)
अणु
	पूर्णांक ret, val, val2;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KMX61_REG_WHO_AM_I);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading who_am_i\n");
		वापस ret;
	पूर्ण

	अगर (ret != KMX61_CHIP_ID) अणु
		dev_err(&data->client->dev,
			"Wrong chip id, got %x expected %x\n",
			 ret, KMX61_CHIP_ID);
		वापस -EINVAL;
	पूर्ण

	/* set accel 12bit, 4g range */
	ret = kmx61_set_range(data, KMX61_RANGE_4G);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KMX61_REG_ODCNTL);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_odcntl\n");
		वापस ret;
	पूर्ण
	data->odr_bits = ret;

	/*
	 * set output data rate क्रम wake up (motion detection) function
	 * to match data rate क्रम accelerometer sampling
	 */
	ret = kmx61_get_odr(data, &val, &val2, KMX61_ACC);
	अगर (ret < 0)
		वापस ret;

	ret = kmx61_set_wake_up_odr(data, val, val2);
	अगर (ret < 0)
		वापस ret;

	/* set acc/magn to OPERATION mode */
	ret = kmx61_set_mode(data, 0, KMX61_ACC | KMX61_MAG, true);
	अगर (ret < 0)
		वापस ret;

	data->wake_thresh = KMX61_DEFAULT_WAKE_THRESH;
	data->wake_duration = KMX61_DEFAULT_WAKE_DURATION;

	वापस 0;
पूर्ण

अटल पूर्णांक kmx61_setup_new_data_पूर्णांकerrupt(काष्ठा kmx61_data *data,
					  bool status, u8 device)
अणु
	u8 mode;
	पूर्णांक ret;

	ret = kmx61_get_mode(data, &mode, KMX61_ACC | KMX61_MAG);
	अगर (ret < 0)
		वापस ret;

	ret = kmx61_set_mode(data, KMX61_ALL_STBY, KMX61_ACC | KMX61_MAG, true);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KMX61_REG_INC1);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_ctrl1\n");
		वापस ret;
	पूर्ण

	अगर (status) अणु
		ret |= KMX61_REG_INC1_BIT_IEN;
		अगर (device & KMX61_ACC)
			ret |= KMX61_REG_INC1_BIT_DRDYA;
		अगर (device & KMX61_MAG)
			ret |=  KMX61_REG_INC1_BIT_DRDYM;
	पूर्ण अन्यथा अणु
		ret &= ~KMX61_REG_INC1_BIT_IEN;
		अगर (device & KMX61_ACC)
			ret &= ~KMX61_REG_INC1_BIT_DRDYA;
		अगर (device & KMX61_MAG)
			ret &= ~KMX61_REG_INC1_BIT_DRDYM;
	पूर्ण
	ret = i2c_smbus_ग_लिखो_byte_data(data->client, KMX61_REG_INC1, ret);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error writing reg_int_ctrl1\n");
		वापस ret;
	पूर्ण

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KMX61_REG_CTRL1);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_ctrl1\n");
		वापस ret;
	पूर्ण

	अगर (status)
		ret |= KMX61_REG_CTRL1_BIT_DRDYE;
	अन्यथा
		ret &= ~KMX61_REG_CTRL1_BIT_DRDYE;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, KMX61_REG_CTRL1, ret);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error writing reg_ctrl1\n");
		वापस ret;
	पूर्ण

	वापस kmx61_set_mode(data, mode, KMX61_ACC | KMX61_MAG, true);
पूर्ण

अटल पूर्णांक kmx61_chip_update_thresholds(काष्ठा kmx61_data *data)
अणु
	पूर्णांक ret;

	ret = i2c_smbus_ग_लिखो_byte_data(data->client,
					KMX61_REG_WUF_TIMER,
					data->wake_duration);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Errow writing reg_wuf_timer\n");
		वापस ret;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte_data(data->client,
					KMX61_REG_WUF_THRESH,
					data->wake_thresh);
	अगर (ret < 0)
		dev_err(&data->client->dev, "Error writing reg_wuf_thresh\n");

	वापस ret;
पूर्ण

अटल पूर्णांक kmx61_setup_any_motion_पूर्णांकerrupt(काष्ठा kmx61_data *data,
					    bool status)
अणु
	u8 mode;
	पूर्णांक ret;

	ret = kmx61_get_mode(data, &mode, KMX61_ACC | KMX61_MAG);
	अगर (ret < 0)
		वापस ret;

	ret = kmx61_set_mode(data, KMX61_ALL_STBY, KMX61_ACC | KMX61_MAG, true);
	अगर (ret < 0)
		वापस ret;

	ret = kmx61_chip_update_thresholds(data);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KMX61_REG_INC1);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_inc1\n");
		वापस ret;
	पूर्ण
	अगर (status)
		ret |= (KMX61_REG_INC1_BIT_IEN | KMX61_REG_INC1_BIT_WUFS);
	अन्यथा
		ret &= ~(KMX61_REG_INC1_BIT_IEN | KMX61_REG_INC1_BIT_WUFS);

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, KMX61_REG_INC1, ret);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error writing reg_inc1\n");
		वापस ret;
	पूर्ण

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KMX61_REG_CTRL1);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_ctrl1\n");
		वापस ret;
	पूर्ण

	अगर (status)
		ret |= KMX61_REG_CTRL1_BIT_WUFE | KMX61_REG_CTRL1_BIT_BTSE;
	अन्यथा
		ret &= ~(KMX61_REG_CTRL1_BIT_WUFE | KMX61_REG_CTRL1_BIT_BTSE);

	ret = i2c_smbus_ग_लिखो_byte_data(data->client, KMX61_REG_CTRL1, ret);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error writing reg_ctrl1\n");
		वापस ret;
	पूर्ण
	mode |= KMX61_ACT_STBY_BIT;
	वापस kmx61_set_mode(data, mode, KMX61_ACC | KMX61_MAG, true);
पूर्ण

/**
 * kmx61_set_घातer_state() - set घातer state क्रम kmx61 @device
 * @data: kmx61 device निजी poपूर्णांकer
 * @on: घातer state to be set क्रम @device
 * @device: biपंचांगask indicating device क्रम which @on state needs to be set
 *
 * Notice that when ACC घातer state needs to be set to ON and MAG is in
 * OPERATION then we know that kmx61_runसमय_resume was alपढ़ोy called
 * so we must set ACC OPERATION mode here. The same happens when MAG घातer
 * state needs to be set to ON and ACC is in OPERATION.
 */
अटल पूर्णांक kmx61_set_घातer_state(काष्ठा kmx61_data *data, bool on, u8 device)
अणु
#अगर_घोषित CONFIG_PM
	पूर्णांक ret;

	अगर (device & KMX61_ACC) अणु
		अगर (on && !data->acc_ps && !data->mag_stby) अणु
			ret = kmx61_set_mode(data, 0, KMX61_ACC, true);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		data->acc_ps = on;
	पूर्ण
	अगर (device & KMX61_MAG) अणु
		अगर (on && !data->mag_ps && !data->acc_stby) अणु
			ret = kmx61_set_mode(data, 0, KMX61_MAG, true);
			अगर (ret < 0)
				वापस ret;
		पूर्ण
		data->mag_ps = on;
	पूर्ण

	अगर (on) अणु
		ret = pm_runसमय_get_sync(&data->client->dev);
	पूर्ण अन्यथा अणु
		pm_runसमय_mark_last_busy(&data->client->dev);
		ret = pm_runसमय_put_स्वतःsuspend(&data->client->dev);
	पूर्ण
	अगर (ret < 0) अणु
		dev_err(&data->client->dev,
			"Failed: kmx61_set_power_state for %d, ret %d\n",
			on, ret);
		अगर (on)
			pm_runसमय_put_noidle(&data->client->dev);

		वापस ret;
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक kmx61_पढ़ो_measurement(काष्ठा kmx61_data *data, u8 base, u8 offset)
अणु
	पूर्णांक ret;
	u8 reg = base + offset * 2;

	ret = i2c_smbus_पढ़ो_word_data(data->client, reg);
	अगर (ret < 0)
		dev_err(&data->client->dev, "failed to read reg at %x\n", reg);

	वापस ret;
पूर्ण

अटल पूर्णांक kmx61_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			  काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			  पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	u8 base_reg;
	काष्ठा kmx61_data *data = kmx61_get_data(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_ACCEL:
			base_reg = KMX61_ACC_XOUT_L;
			अवरोध;
		हाल IIO_MAGN:
			base_reg = KMX61_MAG_XOUT_L;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		mutex_lock(&data->lock);

		ret = kmx61_set_घातer_state(data, true, chan->address);
		अगर (ret) अणु
			mutex_unlock(&data->lock);
			वापस ret;
		पूर्ण

		ret = kmx61_पढ़ो_measurement(data, base_reg, chan->scan_index);
		अगर (ret < 0) अणु
			kmx61_set_घातer_state(data, false, chan->address);
			mutex_unlock(&data->lock);
			वापस ret;
		पूर्ण
		*val = sign_extend32(ret >> chan->scan_type.shअगरt,
				     chan->scan_type.realbits - 1);
		ret = kmx61_set_घातer_state(data, false, chan->address);

		mutex_unlock(&data->lock);
		अगर (ret)
			वापस ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_ACCEL:
			*val = 0;
			*val2 = kmx61_uscale_table[data->range];
			वापस IIO_VAL_INT_PLUS_MICRO;
		हाल IIO_MAGN:
			/* 14 bits res, 1465 microGauss per magn count */
			*val = 0;
			*val2 = 1465;
			वापस IIO_VAL_INT_PLUS_MICRO;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		अगर (chan->type != IIO_ACCEL && chan->type != IIO_MAGN)
			वापस -EINVAL;

		mutex_lock(&data->lock);
		ret = kmx61_get_odr(data, val, val2, chan->address);
		mutex_unlock(&data->lock);
		अगर (ret)
			वापस -EINVAL;
		वापस IIO_VAL_INT_PLUS_MICRO;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक kmx61_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val,
			   पूर्णांक val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	काष्ठा kmx61_data *data = kmx61_get_data(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		अगर (chan->type != IIO_ACCEL && chan->type != IIO_MAGN)
			वापस -EINVAL;

		mutex_lock(&data->lock);
		ret = kmx61_set_odr(data, val, val2, chan->address);
		mutex_unlock(&data->lock);
		वापस ret;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_ACCEL:
			अगर (val != 0)
				वापस -EINVAL;
			mutex_lock(&data->lock);
			ret = kmx61_set_scale(data, val2);
			mutex_unlock(&data->lock);
			वापस ret;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक kmx61_पढ़ो_event(काष्ठा iio_dev *indio_dev,
			    स्थिर काष्ठा iio_chan_spec *chan,
			    क्रमागत iio_event_type type,
			    क्रमागत iio_event_direction dir,
			    क्रमागत iio_event_info info,
			    पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा kmx61_data *data = kmx61_get_data(indio_dev);

	*val2 = 0;
	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		*val = data->wake_thresh;
		वापस IIO_VAL_INT;
	हाल IIO_EV_INFO_PERIOD:
		*val = data->wake_duration;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक kmx61_ग_लिखो_event(काष्ठा iio_dev *indio_dev,
			     स्थिर काष्ठा iio_chan_spec *chan,
			     क्रमागत iio_event_type type,
			     क्रमागत iio_event_direction dir,
			     क्रमागत iio_event_info info,
			     पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा kmx61_data *data = kmx61_get_data(indio_dev);

	अगर (data->ev_enable_state)
		वापस -EBUSY;

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		data->wake_thresh = val;
		वापस IIO_VAL_INT;
	हाल IIO_EV_INFO_PERIOD:
		data->wake_duration = val;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक kmx61_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
				   स्थिर काष्ठा iio_chan_spec *chan,
				   क्रमागत iio_event_type type,
				   क्रमागत iio_event_direction dir)
अणु
	काष्ठा kmx61_data *data = kmx61_get_data(indio_dev);

	वापस data->ev_enable_state;
पूर्ण

अटल पूर्णांक kmx61_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत iio_event_type type,
				    क्रमागत iio_event_direction dir,
				    पूर्णांक state)
अणु
	काष्ठा kmx61_data *data = kmx61_get_data(indio_dev);
	पूर्णांक ret = 0;

	अगर (state && data->ev_enable_state)
		वापस 0;

	mutex_lock(&data->lock);

	अगर (!state && data->motion_trig_on) अणु
		data->ev_enable_state = false;
		जाओ err_unlock;
	पूर्ण

	ret = kmx61_set_घातer_state(data, state, KMX61_ACC);
	अगर (ret < 0)
		जाओ err_unlock;

	ret = kmx61_setup_any_motion_पूर्णांकerrupt(data, state);
	अगर (ret < 0) अणु
		kmx61_set_घातer_state(data, false, KMX61_ACC);
		जाओ err_unlock;
	पूर्ण

	data->ev_enable_state = state;

err_unlock:
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक kmx61_acc_validate_trigger(काष्ठा iio_dev *indio_dev,
				      काष्ठा iio_trigger *trig)
अणु
	काष्ठा kmx61_data *data = kmx61_get_data(indio_dev);

	अगर (data->acc_dपढ़ोy_trig != trig && data->motion_trig != trig)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक kmx61_mag_validate_trigger(काष्ठा iio_dev *indio_dev,
				      काष्ठा iio_trigger *trig)
अणु
	काष्ठा kmx61_data *data = kmx61_get_data(indio_dev);

	अगर (data->mag_dपढ़ोy_trig != trig)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_info kmx61_acc_info = अणु
	.पढ़ो_raw		= kmx61_पढ़ो_raw,
	.ग_लिखो_raw		= kmx61_ग_लिखो_raw,
	.attrs			= &kmx61_acc_attribute_group,
	.पढ़ो_event_value	= kmx61_पढ़ो_event,
	.ग_लिखो_event_value	= kmx61_ग_लिखो_event,
	.पढ़ो_event_config	= kmx61_पढ़ो_event_config,
	.ग_लिखो_event_config	= kmx61_ग_लिखो_event_config,
	.validate_trigger	= kmx61_acc_validate_trigger,
पूर्ण;

अटल स्थिर काष्ठा iio_info kmx61_mag_info = अणु
	.पढ़ो_raw		= kmx61_पढ़ो_raw,
	.ग_लिखो_raw		= kmx61_ग_लिखो_raw,
	.attrs			= &kmx61_mag_attribute_group,
	.validate_trigger	= kmx61_mag_validate_trigger,
पूर्ण;


अटल पूर्णांक kmx61_data_rdy_trigger_set_state(काष्ठा iio_trigger *trig,
					    bool state)
अणु
	पूर्णांक ret = 0;
	u8 device;

	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा kmx61_data *data = kmx61_get_data(indio_dev);

	mutex_lock(&data->lock);

	अगर (!state && data->ev_enable_state && data->motion_trig_on) अणु
		data->motion_trig_on = false;
		जाओ err_unlock;
	पूर्ण

	अगर (data->acc_dपढ़ोy_trig == trig || data->motion_trig == trig)
		device = KMX61_ACC;
	अन्यथा
		device = KMX61_MAG;

	ret = kmx61_set_घातer_state(data, state, device);
	अगर (ret < 0)
		जाओ err_unlock;

	अगर (data->acc_dपढ़ोy_trig == trig || data->mag_dपढ़ोy_trig == trig)
		ret = kmx61_setup_new_data_पूर्णांकerrupt(data, state, device);
	अन्यथा
		ret = kmx61_setup_any_motion_पूर्णांकerrupt(data, state);
	अगर (ret < 0) अणु
		kmx61_set_घातer_state(data, false, device);
		जाओ err_unlock;
	पूर्ण

	अगर (data->acc_dपढ़ोy_trig == trig)
		data->acc_dपढ़ोy_trig_on = state;
	अन्यथा अगर (data->mag_dपढ़ोy_trig == trig)
		data->mag_dपढ़ोy_trig_on = state;
	अन्यथा
		data->motion_trig_on = state;
err_unlock:
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल व्योम kmx61_trig_reenable(काष्ठा iio_trigger *trig)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा kmx61_data *data = kmx61_get_data(indio_dev);
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KMX61_REG_INL);
	अगर (ret < 0)
		dev_err(&data->client->dev, "Error reading reg_inl\n");
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops kmx61_trigger_ops = अणु
	.set_trigger_state = kmx61_data_rdy_trigger_set_state,
	.reenable = kmx61_trig_reenable,
पूर्ण;

अटल irqवापस_t kmx61_event_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा kmx61_data *data = निजी;
	काष्ठा iio_dev *indio_dev = data->acc_indio_dev;
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KMX61_REG_INS1);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Error reading reg_ins1\n");
		जाओ ack_पूर्णांकr;
	पूर्ण

	अगर (ret & KMX61_REG_INS1_BIT_WUFS) अणु
		ret = i2c_smbus_पढ़ो_byte_data(data->client, KMX61_REG_INS2);
		अगर (ret < 0) अणु
			dev_err(&data->client->dev, "Error reading reg_ins2\n");
			जाओ ack_पूर्णांकr;
		पूर्ण

		अगर (ret & KMX61_REG_INS2_BIT_XN)
			iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(IIO_ACCEL,
				       0,
				       IIO_MOD_X,
				       IIO_EV_TYPE_THRESH,
				       IIO_EV_सूची_FALLING),
				       0);

		अगर (ret & KMX61_REG_INS2_BIT_XP)
			iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(IIO_ACCEL,
				       0,
				       IIO_MOD_X,
				       IIO_EV_TYPE_THRESH,
				       IIO_EV_सूची_RISING),
				       0);

		अगर (ret & KMX61_REG_INS2_BIT_YN)
			iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(IIO_ACCEL,
				       0,
				       IIO_MOD_Y,
				       IIO_EV_TYPE_THRESH,
				       IIO_EV_सूची_FALLING),
				       0);

		अगर (ret & KMX61_REG_INS2_BIT_YP)
			iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(IIO_ACCEL,
				       0,
				       IIO_MOD_Y,
				       IIO_EV_TYPE_THRESH,
				       IIO_EV_सूची_RISING),
				       0);

		अगर (ret & KMX61_REG_INS2_BIT_ZN)
			iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(IIO_ACCEL,
				       0,
				       IIO_MOD_Z,
				       IIO_EV_TYPE_THRESH,
				       IIO_EV_सूची_FALLING),
				       0);

		अगर (ret & KMX61_REG_INS2_BIT_ZP)
			iio_push_event(indio_dev,
				       IIO_MOD_EVENT_CODE(IIO_ACCEL,
				       0,
				       IIO_MOD_Z,
				       IIO_EV_TYPE_THRESH,
				       IIO_EV_सूची_RISING),
				       0);
	पूर्ण

ack_पूर्णांकr:
	ret = i2c_smbus_पढ़ो_byte_data(data->client, KMX61_REG_CTRL1);
	अगर (ret < 0)
		dev_err(&data->client->dev, "Error reading reg_ctrl1\n");

	ret |= KMX61_REG_CTRL1_BIT_RES;
	ret = i2c_smbus_ग_लिखो_byte_data(data->client, KMX61_REG_CTRL1, ret);
	अगर (ret < 0)
		dev_err(&data->client->dev, "Error writing reg_ctrl1\n");

	ret = i2c_smbus_पढ़ो_byte_data(data->client, KMX61_REG_INL);
	अगर (ret < 0)
		dev_err(&data->client->dev, "Error reading reg_inl\n");

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t kmx61_data_rdy_trig_poll(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा kmx61_data *data = निजी;

	अगर (data->acc_dपढ़ोy_trig_on)
		iio_trigger_poll(data->acc_dपढ़ोy_trig);
	अगर (data->mag_dपढ़ोy_trig_on)
		iio_trigger_poll(data->mag_dपढ़ोy_trig);

	अगर (data->motion_trig_on)
		iio_trigger_poll(data->motion_trig);

	अगर (data->ev_enable_state)
		वापस IRQ_WAKE_THREAD;
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t kmx61_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा kmx61_data *data = kmx61_get_data(indio_dev);
	पूर्णांक bit, ret, i = 0;
	u8 base;
	s16 buffer[8];

	अगर (indio_dev == data->acc_indio_dev)
		base = KMX61_ACC_XOUT_L;
	अन्यथा
		base = KMX61_MAG_XOUT_L;

	mutex_lock(&data->lock);
	क्रम_each_set_bit(bit, indio_dev->active_scan_mask,
			 indio_dev->masklength) अणु
		ret = kmx61_पढ़ो_measurement(data, base, bit);
		अगर (ret < 0) अणु
			mutex_unlock(&data->lock);
			जाओ err;
		पूर्ण
		buffer[i++] = ret;
	पूर्ण
	mutex_unlock(&data->lock);

	iio_push_to_buffers(indio_dev, buffer);
err:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर अक्षर *kmx61_match_acpi_device(काष्ठा device *dev)
अणु
	स्थिर काष्ठा acpi_device_id *id;

	id = acpi_match_device(dev->driver->acpi_match_table, dev);
	अगर (!id)
		वापस शून्य;
	वापस dev_name(dev);
पूर्ण

अटल काष्ठा iio_dev *kmx61_indiodev_setup(काष्ठा kmx61_data *data,
					    स्थिर काष्ठा iio_info *info,
					    स्थिर काष्ठा iio_chan_spec *chan,
					    पूर्णांक num_channels,
					    स्थिर अक्षर *name)
अणु
	काष्ठा iio_dev *indio_dev;

	indio_dev = devm_iio_device_alloc(&data->client->dev, माप(data));
	अगर (!indio_dev)
		वापस ERR_PTR(-ENOMEM);

	kmx61_set_data(indio_dev, data);

	indio_dev->channels = chan;
	indio_dev->num_channels = num_channels;
	indio_dev->name = name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = info;

	वापस indio_dev;
पूर्ण

अटल काष्ठा iio_trigger *kmx61_trigger_setup(काष्ठा kmx61_data *data,
					       काष्ठा iio_dev *indio_dev,
					       स्थिर अक्षर *tag)
अणु
	काष्ठा iio_trigger *trig;
	पूर्णांक ret;

	trig = devm_iio_trigger_alloc(&data->client->dev,
				      "%s-%s-dev%d",
				      indio_dev->name,
				      tag,
				      indio_dev->id);
	अगर (!trig)
		वापस ERR_PTR(-ENOMEM);

	trig->ops = &kmx61_trigger_ops;
	iio_trigger_set_drvdata(trig, indio_dev);

	ret = iio_trigger_रेजिस्टर(trig);
	अगर (ret)
		वापस ERR_PTR(ret);

	वापस trig;
पूर्ण

अटल पूर्णांक kmx61_probe(काष्ठा i2c_client *client,
		       स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा kmx61_data *data;
	स्थिर अक्षर *name = शून्य;

	data = devm_kzalloc(&client->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	i2c_set_clientdata(client, data);
	data->client = client;

	mutex_init(&data->lock);

	अगर (id)
		name = id->name;
	अन्यथा अगर (ACPI_HANDLE(&client->dev))
		name = kmx61_match_acpi_device(&client->dev);
	अन्यथा
		वापस -ENODEV;

	data->acc_indio_dev =
		kmx61_indiodev_setup(data, &kmx61_acc_info,
				     kmx61_acc_channels,
				     ARRAY_SIZE(kmx61_acc_channels),
				     name);
	अगर (IS_ERR(data->acc_indio_dev))
		वापस PTR_ERR(data->acc_indio_dev);

	data->mag_indio_dev =
		kmx61_indiodev_setup(data, &kmx61_mag_info,
				     kmx61_mag_channels,
				     ARRAY_SIZE(kmx61_mag_channels),
				     name);
	अगर (IS_ERR(data->mag_indio_dev))
		वापस PTR_ERR(data->mag_indio_dev);

	ret = kmx61_chip_init(data);
	अगर (ret < 0)
		वापस ret;

	अगर (client->irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
						kmx61_data_rdy_trig_poll,
						kmx61_event_handler,
						IRQF_TRIGGER_RISING,
						KMX61_IRQ_NAME,
						data);
		अगर (ret)
			जाओ err_chip_uninit;

		data->acc_dपढ़ोy_trig =
			kmx61_trigger_setup(data, data->acc_indio_dev,
					    "dready");
		अगर (IS_ERR(data->acc_dपढ़ोy_trig)) अणु
			ret = PTR_ERR(data->acc_dपढ़ोy_trig);
			जाओ err_chip_uninit;
		पूर्ण

		data->mag_dपढ़ोy_trig =
			kmx61_trigger_setup(data, data->mag_indio_dev,
					    "dready");
		अगर (IS_ERR(data->mag_dपढ़ोy_trig)) अणु
			ret = PTR_ERR(data->mag_dपढ़ोy_trig);
			जाओ err_trigger_unरेजिस्टर_acc_dपढ़ोy;
		पूर्ण

		data->motion_trig =
			kmx61_trigger_setup(data, data->acc_indio_dev,
					    "any-motion");
		अगर (IS_ERR(data->motion_trig)) अणु
			ret = PTR_ERR(data->motion_trig);
			जाओ err_trigger_unरेजिस्टर_mag_dपढ़ोy;
		पूर्ण

		ret = iio_triggered_buffer_setup(data->acc_indio_dev,
						 &iio_pollfunc_store_समय,
						 kmx61_trigger_handler,
						 शून्य);
		अगर (ret < 0) अणु
			dev_err(&data->client->dev,
				"Failed to setup acc triggered buffer\n");
			जाओ err_trigger_unरेजिस्टर_motion;
		पूर्ण

		ret = iio_triggered_buffer_setup(data->mag_indio_dev,
						 &iio_pollfunc_store_समय,
						 kmx61_trigger_handler,
						 शून्य);
		अगर (ret < 0) अणु
			dev_err(&data->client->dev,
				"Failed to setup mag triggered buffer\n");
			जाओ err_buffer_cleanup_acc;
		पूर्ण
	पूर्ण

	ret = pm_runसमय_set_active(&client->dev);
	अगर (ret < 0)
		जाओ err_buffer_cleanup_mag;

	pm_runसमय_enable(&client->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&client->dev, KMX61_SLEEP_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(&client->dev);

	ret = iio_device_रेजिस्टर(data->acc_indio_dev);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to register acc iio device\n");
		जाओ err_buffer_cleanup_mag;
	पूर्ण

	ret = iio_device_रेजिस्टर(data->mag_indio_dev);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to register mag iio device\n");
		जाओ err_iio_unरेजिस्टर_acc;
	पूर्ण

	वापस 0;

err_iio_unरेजिस्टर_acc:
	iio_device_unरेजिस्टर(data->acc_indio_dev);
err_buffer_cleanup_mag:
	अगर (client->irq > 0)
		iio_triggered_buffer_cleanup(data->mag_indio_dev);
err_buffer_cleanup_acc:
	अगर (client->irq > 0)
		iio_triggered_buffer_cleanup(data->acc_indio_dev);
err_trigger_unरेजिस्टर_motion:
	iio_trigger_unरेजिस्टर(data->motion_trig);
err_trigger_unरेजिस्टर_mag_dपढ़ोy:
	iio_trigger_unरेजिस्टर(data->mag_dपढ़ोy_trig);
err_trigger_unरेजिस्टर_acc_dपढ़ोy:
	iio_trigger_unरेजिस्टर(data->acc_dपढ़ोy_trig);
err_chip_uninit:
	kmx61_set_mode(data, KMX61_ALL_STBY, KMX61_ACC | KMX61_MAG, true);
	वापस ret;
पूर्ण

अटल पूर्णांक kmx61_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा kmx61_data *data = i2c_get_clientdata(client);

	iio_device_unरेजिस्टर(data->acc_indio_dev);
	iio_device_unरेजिस्टर(data->mag_indio_dev);

	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);
	pm_runसमय_put_noidle(&client->dev);

	अगर (client->irq > 0) अणु
		iio_triggered_buffer_cleanup(data->acc_indio_dev);
		iio_triggered_buffer_cleanup(data->mag_indio_dev);
		iio_trigger_unरेजिस्टर(data->acc_dपढ़ोy_trig);
		iio_trigger_unरेजिस्टर(data->mag_dपढ़ोy_trig);
		iio_trigger_unरेजिस्टर(data->motion_trig);
	पूर्ण

	mutex_lock(&data->lock);
	kmx61_set_mode(data, KMX61_ALL_STBY, KMX61_ACC | KMX61_MAG, true);
	mutex_unlock(&data->lock);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक kmx61_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret;
	काष्ठा kmx61_data *data = i2c_get_clientdata(to_i2c_client(dev));

	mutex_lock(&data->lock);
	ret = kmx61_set_mode(data, KMX61_ALL_STBY, KMX61_ACC | KMX61_MAG,
			     false);
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक kmx61_resume(काष्ठा device *dev)
अणु
	u8 stby = 0;
	काष्ठा kmx61_data *data = i2c_get_clientdata(to_i2c_client(dev));

	अगर (data->acc_stby)
		stby |= KMX61_ACC_STBY_BIT;
	अगर (data->mag_stby)
		stby |= KMX61_MAG_STBY_BIT;

	वापस kmx61_set_mode(data, stby, KMX61_ACC | KMX61_MAG, true);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल पूर्णांक kmx61_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा kmx61_data *data = i2c_get_clientdata(to_i2c_client(dev));
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = kmx61_set_mode(data, KMX61_ALL_STBY, KMX61_ACC | KMX61_MAG, true);
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक kmx61_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा kmx61_data *data = i2c_get_clientdata(to_i2c_client(dev));
	u8 stby = 0;

	अगर (!data->acc_ps)
		stby |= KMX61_ACC_STBY_BIT;
	अगर (!data->mag_ps)
		stby |= KMX61_MAG_STBY_BIT;

	वापस kmx61_set_mode(data, stby, KMX61_ACC | KMX61_MAG, true);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops kmx61_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(kmx61_suspend, kmx61_resume)
	SET_RUNTIME_PM_OPS(kmx61_runसमय_suspend, kmx61_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id kmx61_acpi_match[] = अणु
	अणु"KMX61021", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, kmx61_acpi_match);

अटल स्थिर काष्ठा i2c_device_id kmx61_id[] = अणु
	अणु"kmx611021", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, kmx61_id);

अटल काष्ठा i2c_driver kmx61_driver = अणु
	.driver = अणु
		.name = KMX61_DRV_NAME,
		.acpi_match_table = ACPI_PTR(kmx61_acpi_match),
		.pm = &kmx61_pm_ops,
	पूर्ण,
	.probe		= kmx61_probe,
	.हटाओ		= kmx61_हटाओ,
	.id_table	= kmx61_id,
पूर्ण;

module_i2c_driver(kmx61_driver);

MODULE_AUTHOR("Daniel Baluta <daniel.baluta@intel.com>");
MODULE_DESCRIPTION("KMX61 accelerometer/magnetometer driver");
MODULE_LICENSE("GPL v2");
