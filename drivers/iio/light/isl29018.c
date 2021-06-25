<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * A iio driver क्रम the light sensor ISL 29018/29023/29035.
 *
 * IIO driver क्रम monitoring ambient light पूर्णांकensity in luxi, proximity
 * sensing and infrared sensing.
 *
 * Copyright (c) 2010, NVIDIA Corporation.
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश <linux/delay.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/acpi.h>

#घोषणा ISL29018_CONV_TIME_MS		100

#घोषणा ISL29018_REG_ADD_COMMAND1	0x00
#घोषणा ISL29018_CMD1_OPMODE_SHIFT	5
#घोषणा ISL29018_CMD1_OPMODE_MASK	(7 << ISL29018_CMD1_OPMODE_SHIFT)
#घोषणा ISL29018_CMD1_OPMODE_POWER_DOWN	0
#घोषणा ISL29018_CMD1_OPMODE_ALS_ONCE	1
#घोषणा ISL29018_CMD1_OPMODE_IR_ONCE	2
#घोषणा ISL29018_CMD1_OPMODE_PROX_ONCE	3

#घोषणा ISL29018_REG_ADD_COMMAND2	0x01
#घोषणा ISL29018_CMD2_RESOLUTION_SHIFT	2
#घोषणा ISL29018_CMD2_RESOLUTION_MASK	(0x3 << ISL29018_CMD2_RESOLUTION_SHIFT)

#घोषणा ISL29018_CMD2_RANGE_SHIFT	0
#घोषणा ISL29018_CMD2_RANGE_MASK	(0x3 << ISL29018_CMD2_RANGE_SHIFT)

#घोषणा ISL29018_CMD2_SCHEME_SHIFT	7
#घोषणा ISL29018_CMD2_SCHEME_MASK	(0x1 << ISL29018_CMD2_SCHEME_SHIFT)

#घोषणा ISL29018_REG_ADD_DATA_LSB	0x02
#घोषणा ISL29018_REG_ADD_DATA_MSB	0x03

#घोषणा ISL29018_REG_TEST		0x08
#घोषणा ISL29018_TEST_SHIFT		0
#घोषणा ISL29018_TEST_MASK		(0xFF << ISL29018_TEST_SHIFT)

#घोषणा ISL29035_REG_DEVICE_ID		0x0F
#घोषणा ISL29035_DEVICE_ID_SHIFT	0x03
#घोषणा ISL29035_DEVICE_ID_MASK		(0x7 << ISL29035_DEVICE_ID_SHIFT)
#घोषणा ISL29035_DEVICE_ID		0x5
#घोषणा ISL29035_BOUT_SHIFT		0x07
#घोषणा ISL29035_BOUT_MASK		(0x01 << ISL29035_BOUT_SHIFT)

क्रमागत isl29018_पूर्णांक_समय अणु
	ISL29018_INT_TIME_16,
	ISL29018_INT_TIME_12,
	ISL29018_INT_TIME_8,
	ISL29018_INT_TIME_4,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक isl29018_पूर्णांक_uबार[3][4] = अणु
	अणु90000, 5630, 351, 21पूर्ण,
	अणु90000, 5600, 352, 22पूर्ण,
	अणु105000, 6500, 410, 25पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा isl29018_scale अणु
	अचिन्हित पूर्णांक scale;
	अचिन्हित पूर्णांक uscale;
पूर्ण isl29018_scales[4][4] = अणु
	अणु अणु0, 15258पूर्ण, अणु0, 61035पूर्ण, अणु0, 244140पूर्ण, अणु0, 976562पूर्ण पूर्ण,
	अणु अणु0, 244140पूर्ण, अणु0, 976562पूर्ण, अणु3, 906250पूर्ण, अणु15, 625000पूर्ण पूर्ण,
	अणु अणु3, 906250पूर्ण, अणु15, 625000पूर्ण, अणु62, 500000पूर्ण, अणु250, 0पूर्ण पूर्ण,
	अणु अणु62, 500000पूर्ण, अणु250, 0पूर्ण, अणु1000, 0पूर्ण, अणु4000, 0पूर्ण पूर्ण
पूर्ण;

काष्ठा isl29018_chip अणु
	काष्ठा regmap		*regmap;
	काष्ठा mutex		lock;
	पूर्णांक			type;
	अचिन्हित पूर्णांक		calibscale;
	अचिन्हित पूर्णांक		ucalibscale;
	अचिन्हित पूर्णांक		पूर्णांक_समय;
	काष्ठा isl29018_scale	scale;
	पूर्णांक			prox_scheme;
	bool			suspended;
	काष्ठा regulator	*vcc_reg;
पूर्ण;

अटल पूर्णांक isl29018_set_पूर्णांकegration_समय(काष्ठा isl29018_chip *chip,
					 अचिन्हित पूर्णांक uसमय)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;
	अचिन्हित पूर्णांक पूर्णांक_समय, new_पूर्णांक_समय;

	क्रम (i = 0; i < ARRAY_SIZE(isl29018_पूर्णांक_uबार[chip->type]); ++i) अणु
		अगर (uसमय == isl29018_पूर्णांक_uबार[chip->type][i]) अणु
			new_पूर्णांक_समय = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i >= ARRAY_SIZE(isl29018_पूर्णांक_uबार[chip->type]))
		वापस -EINVAL;

	ret = regmap_update_bits(chip->regmap, ISL29018_REG_ADD_COMMAND2,
				 ISL29018_CMD2_RESOLUTION_MASK,
				 i << ISL29018_CMD2_RESOLUTION_SHIFT);
	अगर (ret < 0)
		वापस ret;

	/* Keep the same range when पूर्णांकegration समय changes */
	पूर्णांक_समय = chip->पूर्णांक_समय;
	क्रम (i = 0; i < ARRAY_SIZE(isl29018_scales[पूर्णांक_समय]); ++i) अणु
		अगर (chip->scale.scale == isl29018_scales[पूर्णांक_समय][i].scale &&
		    chip->scale.uscale == isl29018_scales[पूर्णांक_समय][i].uscale) अणु
			chip->scale = isl29018_scales[new_पूर्णांक_समय][i];
			अवरोध;
		पूर्ण
	पूर्ण
	chip->पूर्णांक_समय = new_पूर्णांक_समय;

	वापस 0;
पूर्ण

अटल पूर्णांक isl29018_set_scale(काष्ठा isl29018_chip *chip, पूर्णांक scale, पूर्णांक uscale)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;
	काष्ठा isl29018_scale new_scale;

	क्रम (i = 0; i < ARRAY_SIZE(isl29018_scales[chip->पूर्णांक_समय]); ++i) अणु
		अगर (scale == isl29018_scales[chip->पूर्णांक_समय][i].scale &&
		    uscale == isl29018_scales[chip->पूर्णांक_समय][i].uscale) अणु
			new_scale = isl29018_scales[chip->पूर्णांक_समय][i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (i >= ARRAY_SIZE(isl29018_scales[chip->पूर्णांक_समय]))
		वापस -EINVAL;

	ret = regmap_update_bits(chip->regmap, ISL29018_REG_ADD_COMMAND2,
				 ISL29018_CMD2_RANGE_MASK,
				 i << ISL29018_CMD2_RANGE_SHIFT);
	अगर (ret < 0)
		वापस ret;

	chip->scale = new_scale;

	वापस 0;
पूर्ण

अटल पूर्णांक isl29018_पढ़ो_sensor_input(काष्ठा isl29018_chip *chip, पूर्णांक mode)
अणु
	पूर्णांक status;
	अचिन्हित पूर्णांक lsb;
	अचिन्हित पूर्णांक msb;
	काष्ठा device *dev = regmap_get_device(chip->regmap);

	/* Set mode */
	status = regmap_ग_लिखो(chip->regmap, ISL29018_REG_ADD_COMMAND1,
			      mode << ISL29018_CMD1_OPMODE_SHIFT);
	अगर (status) अणु
		dev_err(dev,
			"Error in setting operating mode err %d\n", status);
		वापस status;
	पूर्ण
	msleep(ISL29018_CONV_TIME_MS);
	status = regmap_पढ़ो(chip->regmap, ISL29018_REG_ADD_DATA_LSB, &lsb);
	अगर (status < 0) अणु
		dev_err(dev,
			"Error in reading LSB DATA with err %d\n", status);
		वापस status;
	पूर्ण

	status = regmap_पढ़ो(chip->regmap, ISL29018_REG_ADD_DATA_MSB, &msb);
	अगर (status < 0) अणु
		dev_err(dev,
			"Error in reading MSB DATA with error %d\n", status);
		वापस status;
	पूर्ण
	dev_vdbg(dev, "MSB 0x%x and LSB 0x%x\n", msb, lsb);

	वापस (msb << 8) | lsb;
पूर्ण

अटल पूर्णांक isl29018_पढ़ो_lux(काष्ठा isl29018_chip *chip, पूर्णांक *lux)
अणु
	पूर्णांक lux_data;
	अचिन्हित पूर्णांक data_x_range;

	lux_data = isl29018_पढ़ो_sensor_input(chip,
					      ISL29018_CMD1_OPMODE_ALS_ONCE);
	अगर (lux_data < 0)
		वापस lux_data;

	data_x_range = lux_data * chip->scale.scale +
		       lux_data * chip->scale.uscale / 1000000;
	*lux = data_x_range * chip->calibscale +
	       data_x_range * chip->ucalibscale / 1000000;

	वापस 0;
पूर्ण

अटल पूर्णांक isl29018_पढ़ो_ir(काष्ठा isl29018_chip *chip, पूर्णांक *ir)
अणु
	पूर्णांक ir_data;

	ir_data = isl29018_पढ़ो_sensor_input(chip,
					     ISL29018_CMD1_OPMODE_IR_ONCE);
	अगर (ir_data < 0)
		वापस ir_data;

	*ir = ir_data;

	वापस 0;
पूर्ण

अटल पूर्णांक isl29018_पढ़ो_proximity_ir(काष्ठा isl29018_chip *chip, पूर्णांक scheme,
				      पूर्णांक *near_ir)
अणु
	पूर्णांक status;
	पूर्णांक prox_data = -1;
	पूर्णांक ir_data = -1;
	काष्ठा device *dev = regmap_get_device(chip->regmap);

	/* Do proximity sensing with required scheme */
	status = regmap_update_bits(chip->regmap, ISL29018_REG_ADD_COMMAND2,
				    ISL29018_CMD2_SCHEME_MASK,
				    scheme << ISL29018_CMD2_SCHEME_SHIFT);
	अगर (status) अणु
		dev_err(dev, "Error in setting operating mode\n");
		वापस status;
	पूर्ण

	prox_data = isl29018_पढ़ो_sensor_input(chip,
					       ISL29018_CMD1_OPMODE_PROX_ONCE);
	अगर (prox_data < 0)
		वापस prox_data;

	अगर (scheme == 1) अणु
		*near_ir = prox_data;
		वापस 0;
	पूर्ण

	ir_data = isl29018_पढ़ो_sensor_input(chip,
					     ISL29018_CMD1_OPMODE_IR_ONCE);
	अगर (ir_data < 0)
		वापस ir_data;

	अगर (prox_data >= ir_data)
		*near_ir = prox_data - ir_data;
	अन्यथा
		*near_ir = 0;

	वापस 0;
पूर्ण

अटल sमाप_प्रकार in_illuminance_scale_available_show
			(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा isl29018_chip *chip = iio_priv(indio_dev);
	अचिन्हित पूर्णांक i;
	पूर्णांक len = 0;

	mutex_lock(&chip->lock);
	क्रम (i = 0; i < ARRAY_SIZE(isl29018_scales[chip->पूर्णांक_समय]); ++i)
		len += प्र_लिखो(buf + len, "%d.%06d ",
			       isl29018_scales[chip->पूर्णांक_समय][i].scale,
			       isl29018_scales[chip->पूर्णांक_समय][i].uscale);
	mutex_unlock(&chip->lock);

	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल sमाप_प्रकार in_illuminance_पूर्णांकegration_समय_available_show
			(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा isl29018_chip *chip = iio_priv(indio_dev);
	अचिन्हित पूर्णांक i;
	पूर्णांक len = 0;

	क्रम (i = 0; i < ARRAY_SIZE(isl29018_पूर्णांक_uबार[chip->type]); ++i)
		len += प्र_लिखो(buf + len, "0.%06d ",
			       isl29018_पूर्णांक_uबार[chip->type][i]);

	buf[len - 1] = '\n';

	वापस len;
पूर्ण

/*
 * From ISL29018 Data Sheet (FN6619.4, Oct 8, 2012) regarding the
 * infrared suppression:
 *
 *   Proximity Sensing Scheme: Bit 7. This bit programs the function
 * of the proximity detection. Logic 0 of this bit, Scheme 0, makes
 * full n (4, 8, 12, 16) bits (अचिन्हित) proximity detection. The range
 * of Scheme 0 proximity count is from 0 to 2^n. Logic 1 of this bit,
 * Scheme 1, makes n-1 (3, 7, 11, 15) bits (2's complementary)
 * proximity_less_ambient detection. The range of Scheme 1
 * proximity count is from -2^(n-1) to 2^(n-1) . The sign bit is extended
 * क्रम resolutions less than 16. While Scheme 0 has wider dynamic
 * range, Scheme 1 proximity detection is less affected by the
 * ambient IR noise variation.
 *
 * 0 Sensing IR from LED and ambient
 * 1 Sensing IR from LED with ambient IR rejection
 */
अटल sमाप_प्रकार proximity_on_chip_ambient_infrared_suppression_show
			(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा isl29018_chip *chip = iio_priv(indio_dev);

	/*
	 * Return the "proximity scheme" i.e. अगर the chip करोes on chip
	 * infrared suppression (1 means perक्रमm on chip suppression)
	 */
	वापस प्र_लिखो(buf, "%d\n", chip->prox_scheme);
पूर्ण

अटल sमाप_प्रकार proximity_on_chip_ambient_infrared_suppression_store
			(काष्ठा device *dev, काष्ठा device_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा isl29018_chip *chip = iio_priv(indio_dev);
	पूर्णांक val;

	अगर (kstrtoपूर्णांक(buf, 10, &val))
		वापस -EINVAL;
	अगर (!(val == 0 || val == 1))
		वापस -EINVAL;

	/*
	 * Get the "proximity scheme" i.e. अगर the chip करोes on chip
	 * infrared suppression (1 means perक्रमm on chip suppression)
	 */
	mutex_lock(&chip->lock);
	chip->prox_scheme = val;
	mutex_unlock(&chip->lock);

	वापस count;
पूर्ण

अटल पूर्णांक isl29018_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *chan,
			      पूर्णांक val,
			      पूर्णांक val2,
			      दीर्घ mask)
अणु
	काष्ठा isl29018_chip *chip = iio_priv(indio_dev);
	पूर्णांक ret = -EINVAL;

	mutex_lock(&chip->lock);
	अगर (chip->suspended) अणु
		ret = -EBUSY;
		जाओ ग_लिखो_करोne;
	पूर्ण
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_CALIBSCALE:
		अगर (chan->type == IIO_LIGHT) अणु
			chip->calibscale = val;
			chip->ucalibscale = val2;
			ret = 0;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_INT_TIME:
		अगर (chan->type == IIO_LIGHT && !val)
			ret = isl29018_set_पूर्णांकegration_समय(chip, val2);
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (chan->type == IIO_LIGHT)
			ret = isl29018_set_scale(chip, val, val2);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

ग_लिखो_करोne:
	mutex_unlock(&chip->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक isl29018_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val,
			     पूर्णांक *val2,
			     दीर्घ mask)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा isl29018_chip *chip = iio_priv(indio_dev);

	mutex_lock(&chip->lock);
	अगर (chip->suspended) अणु
		ret = -EBUSY;
		जाओ पढ़ो_करोne;
	पूर्ण
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
	हाल IIO_CHAN_INFO_PROCESSED:
		चयन (chan->type) अणु
		हाल IIO_LIGHT:
			ret = isl29018_पढ़ो_lux(chip, val);
			अवरोध;
		हाल IIO_INTENSITY:
			ret = isl29018_पढ़ो_ir(chip, val);
			अवरोध;
		हाल IIO_PROXIMITY:
			ret = isl29018_पढ़ो_proximity_ir(chip,
							 chip->prox_scheme,
							 val);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अगर (!ret)
			ret = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_INT_TIME:
		अगर (chan->type == IIO_LIGHT) अणु
			*val = 0;
			*val2 = isl29018_पूर्णांक_uबार[chip->type][chip->पूर्णांक_समय];
			ret = IIO_VAL_INT_PLUS_MICRO;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (chan->type == IIO_LIGHT) अणु
			*val = chip->scale.scale;
			*val2 = chip->scale.uscale;
			ret = IIO_VAL_INT_PLUS_MICRO;
		पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBSCALE:
		अगर (chan->type == IIO_LIGHT) अणु
			*val = chip->calibscale;
			*val2 = chip->ucalibscale;
			ret = IIO_VAL_INT_PLUS_MICRO;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

पढ़ो_करोne:
	mutex_unlock(&chip->lock);

	वापस ret;
पूर्ण

#घोषणा ISL29018_LIGHT_CHANNEL अणु					\
	.type = IIO_LIGHT,						\
	.indexed = 1,							\
	.channel = 0,							\
	.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED) |		\
	BIT(IIO_CHAN_INFO_CALIBSCALE) |					\
	BIT(IIO_CHAN_INFO_SCALE) |					\
	BIT(IIO_CHAN_INFO_INT_TIME),					\
पूर्ण

#घोषणा ISL29018_IR_CHANNEL अणु						\
	.type = IIO_INTENSITY,						\
	.modअगरied = 1,							\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),			\
	.channel2 = IIO_MOD_LIGHT_IR,					\
पूर्ण

#घोषणा ISL29018_PROXIMITY_CHANNEL अणु					\
	.type = IIO_PROXIMITY,						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),			\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec isl29018_channels[] = अणु
	ISL29018_LIGHT_CHANNEL,
	ISL29018_IR_CHANNEL,
	ISL29018_PROXIMITY_CHANNEL,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec isl29023_channels[] = अणु
	ISL29018_LIGHT_CHANNEL,
	ISL29018_IR_CHANNEL,
पूर्ण;

अटल IIO_DEVICE_ATTR_RO(in_illuminance_पूर्णांकegration_समय_available, 0);
अटल IIO_DEVICE_ATTR_RO(in_illuminance_scale_available, 0);
अटल IIO_DEVICE_ATTR_RW(proximity_on_chip_ambient_infrared_suppression, 0);

#घोषणा ISL29018_DEV_ATTR(name) (&iio_dev_attr_##name.dev_attr.attr)

अटल काष्ठा attribute *isl29018_attributes[] = अणु
	ISL29018_DEV_ATTR(in_illuminance_scale_available),
	ISL29018_DEV_ATTR(in_illuminance_पूर्णांकegration_समय_available),
	ISL29018_DEV_ATTR(proximity_on_chip_ambient_infrared_suppression),
	शून्य
पूर्ण;

अटल काष्ठा attribute *isl29023_attributes[] = अणु
	ISL29018_DEV_ATTR(in_illuminance_scale_available),
	ISL29018_DEV_ATTR(in_illuminance_पूर्णांकegration_समय_available),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group isl29018_group = अणु
	.attrs = isl29018_attributes,
पूर्ण;

अटल स्थिर काष्ठा attribute_group isl29023_group = अणु
	.attrs = isl29023_attributes,
पूर्ण;

क्रमागत अणु
	isl29018,
	isl29023,
	isl29035,
पूर्ण;

अटल पूर्णांक isl29018_chip_init(काष्ठा isl29018_chip *chip)
अणु
	पूर्णांक status;
	काष्ठा device *dev = regmap_get_device(chip->regmap);

	अगर (chip->type == isl29035) अणु
		अचिन्हित पूर्णांक id;

		status = regmap_पढ़ो(chip->regmap, ISL29035_REG_DEVICE_ID, &id);
		अगर (status < 0) अणु
			dev_err(dev,
				"Error reading ID register with error %d\n",
				status);
			वापस status;
		पूर्ण

		id = (id & ISL29035_DEVICE_ID_MASK) >> ISL29035_DEVICE_ID_SHIFT;

		अगर (id != ISL29035_DEVICE_ID)
			वापस -ENODEV;

		/* Clear brownout bit */
		status = regmap_update_bits(chip->regmap,
					    ISL29035_REG_DEVICE_ID,
					    ISL29035_BOUT_MASK, 0);
		अगर (status < 0)
			वापस status;
	पूर्ण

	/*
	 * Code added per Intersil Application Note 1534:
	 *     When VDD sinks to approximately 1.8V or below, some of
	 * the part's रेजिस्टरs may change their state. When VDD
	 * recovers to 2.25V (or greater), the part may thus be in an
	 * unknown mode of operation. The user can वापस the part to
	 * a known mode of operation either by (a) setting VDD = 0V क्रम
	 * 1 second or more and then घातering back up with a slew rate
	 * of 0.5V/ms or greater, or (b) via I2C disable all ALS/PROX
	 * conversions, clear the test रेजिस्टरs, and then reग_लिखो all
	 * रेजिस्टरs to the desired values.
	 * ...
	 * For ISL29011, ISL29018, ISL29021, ISL29023
	 * 1. Write 0x00 to रेजिस्टर 0x08 (TEST)
	 * 2. Write 0x00 to रेजिस्टर 0x00 (CMD1)
	 * 3. Reग_लिखो all रेजिस्टरs to the desired values
	 *
	 * ISL29018 Data Sheet (FN6619.1, Feb 11, 2010) essentially says
	 * the same thing EXCEPT the data sheet asks क्रम a 1ms delay after
	 * writing the CMD1 रेजिस्टर.
	 */
	status = regmap_ग_लिखो(chip->regmap, ISL29018_REG_TEST, 0x0);
	अगर (status < 0) अणु
		dev_err(dev, "Failed to clear isl29018 TEST reg.(%d)\n",
			status);
		वापस status;
	पूर्ण

	/*
	 * See Intersil AN1534 comments above.
	 * "Operating Mode" (COMMAND1) रेजिस्टर is reprogrammed when
	 * data is पढ़ो from the device.
	 */
	status = regmap_ग_लिखो(chip->regmap, ISL29018_REG_ADD_COMMAND1, 0);
	अगर (status < 0) अणु
		dev_err(dev, "Failed to clear isl29018 CMD1 reg.(%d)\n",
			status);
		वापस status;
	पूर्ण

	usleep_range(1000, 2000);	/* per data sheet, page 10 */

	/* Set शेषs */
	status = isl29018_set_scale(chip, chip->scale.scale,
				    chip->scale.uscale);
	अगर (status < 0) अणु
		dev_err(dev, "Init of isl29018 fails\n");
		वापस status;
	पूर्ण

	status = isl29018_set_पूर्णांकegration_समय(chip,
			isl29018_पूर्णांक_uबार[chip->type][chip->पूर्णांक_समय]);
	अगर (status < 0)
		dev_err(dev, "Init of isl29018 fails\n");

	वापस status;
पूर्ण

अटल स्थिर काष्ठा iio_info isl29018_info = अणु
	.attrs = &isl29018_group,
	.पढ़ो_raw = isl29018_पढ़ो_raw,
	.ग_लिखो_raw = isl29018_ग_लिखो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_info isl29023_info = अणु
	.attrs = &isl29023_group,
	.पढ़ो_raw = isl29018_पढ़ो_raw,
	.ग_लिखो_raw = isl29018_ग_लिखो_raw,
पूर्ण;

अटल bool isl29018_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ISL29018_REG_ADD_DATA_LSB:
	हाल ISL29018_REG_ADD_DATA_MSB:
	हाल ISL29018_REG_ADD_COMMAND1:
	हाल ISL29018_REG_TEST:
	हाल ISL29035_REG_DEVICE_ID:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config isl29018_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.अस्थिर_reg = isl29018_is_अस्थिर_reg,
	.max_रेजिस्टर = ISL29018_REG_TEST,
	.num_reg_शेषs_raw = ISL29018_REG_TEST + 1,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर काष्ठा regmap_config isl29035_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.अस्थिर_reg = isl29018_is_अस्थिर_reg,
	.max_रेजिस्टर = ISL29035_REG_DEVICE_ID,
	.num_reg_शेषs_raw = ISL29035_REG_DEVICE_ID + 1,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

काष्ठा isl29018_chip_info अणु
	स्थिर काष्ठा iio_chan_spec *channels;
	पूर्णांक num_channels;
	स्थिर काष्ठा iio_info *indio_info;
	स्थिर काष्ठा regmap_config *regmap_cfg;
पूर्ण;

अटल स्थिर काष्ठा isl29018_chip_info isl29018_chip_info_tbl[] = अणु
	[isl29018] = अणु
		.channels = isl29018_channels,
		.num_channels = ARRAY_SIZE(isl29018_channels),
		.indio_info = &isl29018_info,
		.regmap_cfg = &isl29018_regmap_config,
	पूर्ण,
	[isl29023] = अणु
		.channels = isl29023_channels,
		.num_channels = ARRAY_SIZE(isl29023_channels),
		.indio_info = &isl29023_info,
		.regmap_cfg = &isl29018_regmap_config,
	पूर्ण,
	[isl29035] = अणु
		.channels = isl29023_channels,
		.num_channels = ARRAY_SIZE(isl29023_channels),
		.indio_info = &isl29023_info,
		.regmap_cfg = &isl29035_regmap_config,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *isl29018_match_acpi_device(काष्ठा device *dev, पूर्णांक *data)
अणु
	स्थिर काष्ठा acpi_device_id *id;

	id = acpi_match_device(dev->driver->acpi_match_table, dev);

	अगर (!id)
		वापस शून्य;

	*data = (पूर्णांक)id->driver_data;

	वापस dev_name(dev);
पूर्ण

अटल व्योम isl29018_disable_regulator_action(व्योम *_data)
अणु
	काष्ठा isl29018_chip *chip = _data;
	पूर्णांक err;

	err = regulator_disable(chip->vcc_reg);
	अगर (err)
		pr_err("failed to disable isl29018's VCC regulator!\n");
पूर्ण

अटल पूर्णांक isl29018_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा isl29018_chip *chip;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक err;
	स्थिर अक्षर *name = शून्य;
	पूर्णांक dev_id = 0;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*chip));
	अगर (!indio_dev)
		वापस -ENOMEM;

	chip = iio_priv(indio_dev);

	i2c_set_clientdata(client, indio_dev);

	अगर (id) अणु
		name = id->name;
		dev_id = id->driver_data;
	पूर्ण

	अगर (ACPI_HANDLE(&client->dev))
		name = isl29018_match_acpi_device(&client->dev, &dev_id);

	mutex_init(&chip->lock);

	chip->type = dev_id;
	chip->calibscale = 1;
	chip->ucalibscale = 0;
	chip->पूर्णांक_समय = ISL29018_INT_TIME_16;
	chip->scale = isl29018_scales[chip->पूर्णांक_समय][0];
	chip->suspended = false;

	chip->vcc_reg = devm_regulator_get(&client->dev, "vcc");
	अगर (IS_ERR(chip->vcc_reg))
		वापस dev_err_probe(&client->dev, PTR_ERR(chip->vcc_reg),
				     "failed to get VCC regulator!\n");

	err = regulator_enable(chip->vcc_reg);
	अगर (err) अणु
		dev_err(&client->dev, "failed to enable VCC regulator!\n");
		वापस err;
	पूर्ण

	err = devm_add_action_or_reset(&client->dev, isl29018_disable_regulator_action,
				 chip);
	अगर (err) अणु
		dev_err(&client->dev, "failed to setup regulator cleanup action!\n");
		वापस err;
	पूर्ण

	chip->regmap = devm_regmap_init_i2c(client,
				isl29018_chip_info_tbl[dev_id].regmap_cfg);
	अगर (IS_ERR(chip->regmap)) अणु
		err = PTR_ERR(chip->regmap);
		dev_err(&client->dev, "regmap initialization fails: %d\n", err);
		वापस err;
	पूर्ण

	err = isl29018_chip_init(chip);
	अगर (err)
		वापस err;

	indio_dev->info = isl29018_chip_info_tbl[dev_id].indio_info;
	indio_dev->channels = isl29018_chip_info_tbl[dev_id].channels;
	indio_dev->num_channels = isl29018_chip_info_tbl[dev_id].num_channels;
	indio_dev->name = name;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक isl29018_suspend(काष्ठा device *dev)
अणु
	काष्ठा isl29018_chip *chip = iio_priv(dev_get_drvdata(dev));
	पूर्णांक ret;

	mutex_lock(&chip->lock);

	/*
	 * Since this driver uses only polling commands, we are by शेष in
	 * स्वतः shutकरोwn (ie, घातer-करोwn) mode.
	 * So we करो not have much to करो here.
	 */
	chip->suspended = true;
	ret = regulator_disable(chip->vcc_reg);
	अगर (ret)
		dev_err(dev, "failed to disable VCC regulator\n");

	mutex_unlock(&chip->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक isl29018_resume(काष्ठा device *dev)
अणु
	काष्ठा isl29018_chip *chip = iio_priv(dev_get_drvdata(dev));
	पूर्णांक err;

	mutex_lock(&chip->lock);

	err = regulator_enable(chip->vcc_reg);
	अगर (err) अणु
		dev_err(dev, "failed to enable VCC regulator\n");
		mutex_unlock(&chip->lock);
		वापस err;
	पूर्ण

	err = isl29018_chip_init(chip);
	अगर (!err)
		chip->suspended = false;

	mutex_unlock(&chip->lock);

	वापस err;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(isl29018_pm_ops, isl29018_suspend, isl29018_resume);
#घोषणा ISL29018_PM_OPS (&isl29018_pm_ops)
#अन्यथा
#घोषणा ISL29018_PM_OPS शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id isl29018_acpi_match[] = अणु
	अणु"ISL29018", isl29018पूर्ण,
	अणु"ISL29023", isl29023पूर्ण,
	अणु"ISL29035", isl29035पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, isl29018_acpi_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id isl29018_id[] = अणु
	अणु"isl29018", isl29018पूर्ण,
	अणु"isl29023", isl29023पूर्ण,
	अणु"isl29035", isl29035पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, isl29018_id);

अटल स्थिर काष्ठा of_device_id isl29018_of_match[] = अणु
	अणु .compatible = "isil,isl29018", पूर्ण,
	अणु .compatible = "isil,isl29023", पूर्ण,
	अणु .compatible = "isil,isl29035", पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, isl29018_of_match);

अटल काष्ठा i2c_driver isl29018_driver = अणु
	.driver	 = अणु
			.name = "isl29018",
			.acpi_match_table = ACPI_PTR(isl29018_acpi_match),
			.pm = ISL29018_PM_OPS,
			.of_match_table = isl29018_of_match,
		    पूर्ण,
	.probe	 = isl29018_probe,
	.id_table = isl29018_id,
पूर्ण;
module_i2c_driver(isl29018_driver);

MODULE_DESCRIPTION("ISL29018 Ambient Light Sensor driver");
MODULE_LICENSE("GPL");
