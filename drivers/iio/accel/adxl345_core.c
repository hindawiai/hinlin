<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ADXL345 3-Axis Digital Accelerometer IIO core driver
 *
 * Copyright (c) 2017 Eva Rachel Retuya <eraretuya@gmail.com>
 *
 * Datasheet: https://www.analog.com/media/en/technical-करोcumentation/data-sheets/ADXL345.pdf
 */

#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#समावेश "adxl345.h"

#घोषणा ADXL345_REG_DEVID		0x00
#घोषणा ADXL345_REG_OFSX		0x1e
#घोषणा ADXL345_REG_OFSY		0x1f
#घोषणा ADXL345_REG_OFSZ		0x20
#घोषणा ADXL345_REG_OFS_AXIS(index)	(ADXL345_REG_OFSX + (index))
#घोषणा ADXL345_REG_BW_RATE		0x2C
#घोषणा ADXL345_REG_POWER_CTL		0x2D
#घोषणा ADXL345_REG_DATA_FORMAT		0x31
#घोषणा ADXL345_REG_DATAX0		0x32
#घोषणा ADXL345_REG_DATAY0		0x34
#घोषणा ADXL345_REG_DATAZ0		0x36
#घोषणा ADXL345_REG_DATA_AXIS(index)	\
	(ADXL345_REG_DATAX0 + (index) * माप(__le16))

#घोषणा ADXL345_BW_RATE			GENMASK(3, 0)
#घोषणा ADXL345_BASE_RATE_न_अंकO_HZ	97656250LL
#घोषणा NHZ_PER_HZ			1000000000LL

#घोषणा ADXL345_POWER_CTL_MEASURE	BIT(3)
#घोषणा ADXL345_POWER_CTL_STANDBY	0x00

#घोषणा ADXL345_DATA_FORMAT_FULL_RES	BIT(3) /* Up to 13-bits resolution */
#घोषणा ADXL345_DATA_FORMAT_2G		0
#घोषणा ADXL345_DATA_FORMAT_4G		1
#घोषणा ADXL345_DATA_FORMAT_8G		2
#घोषणा ADXL345_DATA_FORMAT_16G		3

#घोषणा ADXL345_DEVID			0xE5

/*
 * In full-resolution mode, scale factor is मुख्यtained at ~4 mg/LSB
 * in all g ranges.
 *
 * At +/- 16g with 13-bit resolution, scale is computed as:
 * (16 + 16) * 9.81 / (2^13 - 1) = 0.0383
 */
अटल स्थिर पूर्णांक adxl345_uscale = 38300;

/*
 * The Datasheet lists a resolution of Resolution is ~49 mg per LSB. That's
 * ~480mm/s**2 per LSB.
 */
अटल स्थिर पूर्णांक adxl375_uscale = 480000;

काष्ठा adxl345_data अणु
	काष्ठा regmap *regmap;
	u8 data_range;
	क्रमागत adxl345_device_type type;
पूर्ण;

#घोषणा ADXL345_CHANNEL(index, axis) अणु					\
	.type = IIO_ACCEL,						\
	.modअगरied = 1,							\
	.channel2 = IIO_MOD_##axis,					\
	.address = index,						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |			\
		BIT(IIO_CHAN_INFO_CALIBBIAS),				\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |		\
		BIT(IIO_CHAN_INFO_SAMP_FREQ),				\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec adxl345_channels[] = अणु
	ADXL345_CHANNEL(0, X),
	ADXL345_CHANNEL(1, Y),
	ADXL345_CHANNEL(2, Z),
पूर्ण;

अटल पूर्णांक adxl345_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा adxl345_data *data = iio_priv(indio_dev);
	__le16 accel;
	दीर्घ दीर्घ samp_freq_nhz;
	अचिन्हित पूर्णांक regval;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		/*
		 * Data is stored in adjacent रेजिस्टरs:
		 * ADXL345_REG_DATA(X0/Y0/Z0) contain the least signअगरicant byte
		 * and ADXL345_REG_DATA(X0/Y0/Z0) + 1 the most signअगरicant byte
		 */
		ret = regmap_bulk_पढ़ो(data->regmap,
				       ADXL345_REG_DATA_AXIS(chan->address),
				       &accel, माप(accel));
		अगर (ret < 0)
			वापस ret;

		*val = sign_extend32(le16_to_cpu(accel), 12);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		चयन (data->type) अणु
		हाल ADXL345:
			*val2 = adxl345_uscale;
			अवरोध;
		हाल ADXL375:
			*val2 = adxl375_uscale;
			अवरोध;
		पूर्ण

		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		ret = regmap_पढ़ो(data->regmap,
				  ADXL345_REG_OFS_AXIS(chan->address), &regval);
		अगर (ret < 0)
			वापस ret;
		/*
		 * 8-bit resolution at +/- 2g, that is 4x accel data scale
		 * factor
		 */
		*val = sign_extend32(regval, 7) * 4;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret = regmap_पढ़ो(data->regmap, ADXL345_REG_BW_RATE, &regval);
		अगर (ret < 0)
			वापस ret;

		samp_freq_nhz = ADXL345_BASE_RATE_न_अंकO_HZ <<
				(regval & ADXL345_BW_RATE);
		*val = भाग_s64_rem(samp_freq_nhz, NHZ_PER_HZ, val2);

		वापस IIO_VAL_INT_PLUS_न_अंकO;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक adxl345_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा adxl345_data *data = iio_priv(indio_dev);
	s64 n;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_CALIBBIAS:
		/*
		 * 8-bit resolution at +/- 2g, that is 4x accel data scale
		 * factor
		 */
		वापस regmap_ग_लिखो(data->regmap,
				    ADXL345_REG_OFS_AXIS(chan->address),
				    val / 4);
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		n = भाग_s64(val * NHZ_PER_HZ + val2, ADXL345_BASE_RATE_न_अंकO_HZ);

		वापस regmap_update_bits(data->regmap, ADXL345_REG_BW_RATE,
					  ADXL345_BW_RATE,
					  clamp_val(ilog2(n), 0,
						    ADXL345_BW_RATE));
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक adxl345_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev,
				     काष्ठा iio_chan_spec स्थिर *chan,
				     दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_CALIBBIAS:
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस IIO_VAL_INT_PLUS_न_अंकO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL(
"0.09765625 0.1953125 0.390625 0.78125 1.5625 3.125 6.25 12.5 25 50 100 200 400 800 1600 3200"
);

अटल काष्ठा attribute *adxl345_attrs[] = अणु
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group adxl345_attrs_group = अणु
	.attrs = adxl345_attrs,
पूर्ण;

अटल स्थिर काष्ठा iio_info adxl345_info = अणु
	.attrs		= &adxl345_attrs_group,
	.पढ़ो_raw	= adxl345_पढ़ो_raw,
	.ग_लिखो_raw	= adxl345_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt	= adxl345_ग_लिखो_raw_get_fmt,
पूर्ण;

पूर्णांक adxl345_core_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
		       क्रमागत adxl345_device_type type, स्थिर अक्षर *name)
अणु
	काष्ठा adxl345_data *data;
	काष्ठा iio_dev *indio_dev;
	u32 regval;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, ADXL345_REG_DEVID, &regval);
	अगर (ret < 0) अणु
		dev_err(dev, "Error reading device ID: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (regval != ADXL345_DEVID) अणु
		dev_err(dev, "Invalid device ID: %x, expected %x\n",
			regval, ADXL345_DEVID);
		वापस -ENODEV;
	पूर्ण

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	dev_set_drvdata(dev, indio_dev);
	data->regmap = regmap;
	data->type = type;
	/* Enable full-resolution mode */
	data->data_range = ADXL345_DATA_FORMAT_FULL_RES;

	ret = regmap_ग_लिखो(data->regmap, ADXL345_REG_DATA_FORMAT,
			   data->data_range);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to set data range: %d\n", ret);
		वापस ret;
	पूर्ण

	indio_dev->name = name;
	indio_dev->info = &adxl345_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = adxl345_channels;
	indio_dev->num_channels = ARRAY_SIZE(adxl345_channels);

	/* Enable measurement mode */
	ret = regmap_ग_लिखो(data->regmap, ADXL345_REG_POWER_CTL,
			   ADXL345_POWER_CTL_MEASURE);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to enable measurement mode: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(dev, "iio_device_register failed: %d\n", ret);
		regmap_ग_लिखो(data->regmap, ADXL345_REG_POWER_CTL,
			     ADXL345_POWER_CTL_STANDBY);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(adxl345_core_probe);

पूर्णांक adxl345_core_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा adxl345_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	वापस regmap_ग_लिखो(data->regmap, ADXL345_REG_POWER_CTL,
			    ADXL345_POWER_CTL_STANDBY);
पूर्ण
EXPORT_SYMBOL_GPL(adxl345_core_हटाओ);

MODULE_AUTHOR("Eva Rachel Retuya <eraretuya@gmail.com>");
MODULE_DESCRIPTION("ADXL345 3-Axis Digital Accelerometer core driver");
MODULE_LICENSE("GPL v2");
