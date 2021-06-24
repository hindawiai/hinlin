<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Device driver क्रम the the HMC5843 multi-chip module deचिन्हित
 * क्रम low field magnetic sensing.
 *
 * Copyright (C) 2010 Texas Instruments
 *
 * Author: Shubhrajyoti Datta <shubhrajyoti@ti.com>
 * Acknowledgment: Jonathan Cameron <jic23@kernel.org> क्रम valuable inमाला_दो.
 * Support क्रम HMC5883 and HMC5883L by Peter Meerwald <pmeerw@pmeerw.net>.
 * Split to multiple files by Josef Gajdusek <atx@atx.name> - 2014
 */

#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/delay.h>

#समावेश "hmc5843.h"

/*
 * Range gain settings in (+-)Ga
 * Beware: HMC5843 and HMC5883 have dअगरferent recommended sensor field
 * ranges; शेष corresponds to +-1.0 Ga and +-1.3 Ga, respectively
 */
#घोषणा HMC5843_RANGE_GAIN_OFFSET		0x05
#घोषणा HMC5843_RANGE_GAIN_DEFAULT		0x01
#घोषणा HMC5843_RANGE_GAIN_MASK		0xe0

/* Device status */
#घोषणा HMC5843_DATA_READY			0x01
#घोषणा HMC5843_DATA_OUTPUT_LOCK		0x02

/* Mode रेजिस्टर configuration */
#घोषणा HMC5843_MODE_CONVERSION_CONTINUOUS	0x00
#घोषणा HMC5843_MODE_CONVERSION_SINGLE		0x01
#घोषणा HMC5843_MODE_IDLE			0x02
#घोषणा HMC5843_MODE_SLEEP			0x03
#घोषणा HMC5843_MODE_MASK			0x03

/*
 * HMC5843: Minimum data output rate
 * HMC5883: Typical data output rate
 */
#घोषणा HMC5843_RATE_OFFSET			0x02
#घोषणा HMC5843_RATE_DEFAULT			0x04
#घोषणा HMC5843_RATE_MASK		0x1c

/* Device measurement configuration */
#घोषणा HMC5843_MEAS_CONF_NORMAL		0x00
#घोषणा HMC5843_MEAS_CONF_POSITIVE_BIAS		0x01
#घोषणा HMC5843_MEAS_CONF_NEGATIVE_BIAS		0x02
#घोषणा HMC5843_MEAS_CONF_MASK			0x03

/*
 * API क्रम setting the measurement configuration to
 * Normal, Positive bias and Negative bias
 *
 * From the datasheet:
 * 0 - Normal measurement configuration (शेष): In normal measurement
 *     configuration the device follows normal measurement flow. Pins BP
 *     and BN are left भग्नing and high impedance.
 *
 * 1 - Positive bias configuration: In positive bias configuration, a
 *     positive current is क्रमced across the resistive load on pins BP
 *     and BN.
 *
 * 2 - Negative bias configuration. In negative bias configuration, a
 *     negative current is क्रमced across the resistive load on pins BP
 *     and BN.
 *
 * 3 - Only available on HMC5983. Magnetic sensor is disabled.
 *     Temperature sensor is enabled.
 */

अटल स्थिर अक्षर *स्थिर hmc5843_meas_conf_modes[] = अणु"normal", "positivebias",
						      "negativebias"पूर्ण;

अटल स्थिर अक्षर *स्थिर hmc5983_meas_conf_modes[] = अणु"normal", "positivebias",
						      "negativebias",
						      "disabled"पूर्ण;
/* Scaling factors: 10000000/Gain */
अटल स्थिर पूर्णांक hmc5843_regval_to_nanoscale[] = अणु
	6173, 7692, 10309, 12821, 18868, 21739, 25641, 35714
पूर्ण;

अटल स्थिर पूर्णांक hmc5883_regval_to_nanoscale[] = अणु
	7812, 9766, 13021, 16287, 24096, 27701, 32573, 45662
पूर्ण;

अटल स्थिर पूर्णांक hmc5883l_regval_to_nanoscale[] = अणु
	7299, 9174, 12195, 15152, 22727, 25641, 30303, 43478
पूर्ण;

/*
 * From the datasheet:
 * Value	| HMC5843		| HMC5883/HMC5883L
 *		| Data output rate (Hz)	| Data output rate (Hz)
 * 0		| 0.5			| 0.75
 * 1		| 1			| 1.5
 * 2		| 2			| 3
 * 3		| 5			| 7.5
 * 4		| 10 (शेष)		| 15
 * 5		| 20			| 30
 * 6		| 50			| 75
 * 7		| Not used		| Not used
 */
अटल स्थिर पूर्णांक hmc5843_regval_to_samp_freq[][2] = अणु
	अणु0, 500000पूर्ण, अणु1, 0पूर्ण, अणु2, 0पूर्ण, अणु5, 0पूर्ण, अणु10, 0पूर्ण, अणु20, 0पूर्ण, अणु50, 0पूर्ण
पूर्ण;

अटल स्थिर पूर्णांक hmc5883_regval_to_samp_freq[][2] = अणु
	अणु0, 750000पूर्ण, अणु1, 500000पूर्ण, अणु3, 0पूर्ण, अणु7, 500000पूर्ण, अणु15, 0पूर्ण, अणु30, 0पूर्ण,
	अणु75, 0पूर्ण
पूर्ण;

अटल स्थिर पूर्णांक hmc5983_regval_to_samp_freq[][2] = अणु
	अणु0, 750000पूर्ण, अणु1, 500000पूर्ण, अणु3, 0पूर्ण, अणु7, 500000पूर्ण, अणु15, 0पूर्ण, अणु30, 0पूर्ण,
	अणु75, 0पूर्ण, अणु220, 0पूर्ण
पूर्ण;

/* Describe chip variants */
काष्ठा hmc5843_chip_info अणु
	स्थिर काष्ठा iio_chan_spec *channels;
	स्थिर पूर्णांक (*regval_to_samp_freq)[2];
	स्थिर पूर्णांक n_regval_to_samp_freq;
	स्थिर पूर्णांक *regval_to_nanoscale;
	स्थिर पूर्णांक n_regval_to_nanoscale;
पूर्ण;

/* The lower two bits contain the current conversion mode */
अटल s32 hmc5843_set_mode(काष्ठा hmc5843_data *data, u8 operating_mode)
अणु
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = regmap_update_bits(data->regmap, HMC5843_MODE_REG,
				 HMC5843_MODE_MASK, operating_mode);
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक hmc5843_रुको_measurement(काष्ठा hmc5843_data *data)
अणु
	पूर्णांक tries = 150;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	जबतक (tries-- > 0) अणु
		ret = regmap_पढ़ो(data->regmap, HMC5843_STATUS_REG, &val);
		अगर (ret < 0)
			वापस ret;
		अगर (val & HMC5843_DATA_READY)
			अवरोध;
		msleep(20);
	पूर्ण

	अगर (tries < 0) अणु
		dev_err(data->dev, "data not ready\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/* Return the measurement value from the specअगरied channel */
अटल पूर्णांक hmc5843_पढ़ो_measurement(काष्ठा hmc5843_data *data,
				    पूर्णांक idx, पूर्णांक *val)
अणु
	__be16 values[3];
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = hmc5843_रुको_measurement(data);
	अगर (ret < 0) अणु
		mutex_unlock(&data->lock);
		वापस ret;
	पूर्ण
	ret = regmap_bulk_पढ़ो(data->regmap, HMC5843_DATA_OUT_MSB_REGS,
			       values, माप(values));
	mutex_unlock(&data->lock);
	अगर (ret < 0)
		वापस ret;

	*val = sign_extend32(be16_to_cpu(values[idx]), 15);
	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक hmc5843_set_meas_conf(काष्ठा hmc5843_data *data, u8 meas_conf)
अणु
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = regmap_update_bits(data->regmap, HMC5843_CONFIG_REG_A,
				 HMC5843_MEAS_CONF_MASK, meas_conf);
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल
पूर्णांक hmc5843_show_measurement_configuration(काष्ठा iio_dev *indio_dev,
					   स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा hmc5843_data *data = iio_priv(indio_dev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, HMC5843_CONFIG_REG_A, &val);
	अगर (ret)
		वापस ret;

	वापस val & HMC5843_MEAS_CONF_MASK;
पूर्ण

अटल
पूर्णांक hmc5843_set_measurement_configuration(काष्ठा iio_dev *indio_dev,
					  स्थिर काष्ठा iio_chan_spec *chan,
					  अचिन्हित पूर्णांक meas_conf)
अणु
	काष्ठा hmc5843_data *data = iio_priv(indio_dev);

	वापस hmc5843_set_meas_conf(data, meas_conf);
पूर्ण

अटल स्थिर काष्ठा iio_mount_matrix *
hmc5843_get_mount_matrix(स्थिर काष्ठा iio_dev *indio_dev,
			  स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा hmc5843_data *data = iio_priv(indio_dev);

	वापस &data->orientation;
पूर्ण

अटल स्थिर काष्ठा iio_क्रमागत hmc5843_meas_conf_क्रमागत = अणु
	.items = hmc5843_meas_conf_modes,
	.num_items = ARRAY_SIZE(hmc5843_meas_conf_modes),
	.get = hmc5843_show_measurement_configuration,
	.set = hmc5843_set_measurement_configuration,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info hmc5843_ext_info[] = अणु
	IIO_ENUM("meas_conf", IIO_SHARED_BY_TYPE, &hmc5843_meas_conf_क्रमागत),
	IIO_ENUM_AVAILABLE("meas_conf", &hmc5843_meas_conf_क्रमागत),
	IIO_MOUNT_MATRIX(IIO_SHARED_BY_सूची, hmc5843_get_mount_matrix),
	अणु पूर्ण
पूर्ण;

अटल स्थिर काष्ठा iio_क्रमागत hmc5983_meas_conf_क्रमागत = अणु
	.items = hmc5983_meas_conf_modes,
	.num_items = ARRAY_SIZE(hmc5983_meas_conf_modes),
	.get = hmc5843_show_measurement_configuration,
	.set = hmc5843_set_measurement_configuration,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info hmc5983_ext_info[] = अणु
	IIO_ENUM("meas_conf", IIO_SHARED_BY_TYPE, &hmc5983_meas_conf_क्रमागत),
	IIO_ENUM_AVAILABLE("meas_conf", &hmc5983_meas_conf_क्रमागत),
	IIO_MOUNT_MATRIX(IIO_SHARED_BY_सूची, hmc5843_get_mount_matrix),
	अणु पूर्ण
पूर्ण;

अटल
sमाप_प्रकार hmc5843_show_samp_freq_avail(काष्ठा device *dev,
				     काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा hmc5843_data *data = iio_priv(dev_to_iio_dev(dev));
	माप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < data->variant->n_regval_to_samp_freq; i++)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len,
			"%d.%d ", data->variant->regval_to_samp_freq[i][0],
			data->variant->regval_to_samp_freq[i][1]);

	/* replace trailing space by newline */
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल IIO_DEV_ATTR_SAMP_FREQ_AVAIL(hmc5843_show_samp_freq_avail);

अटल पूर्णांक hmc5843_set_samp_freq(काष्ठा hmc5843_data *data, u8 rate)
अणु
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = regmap_update_bits(data->regmap, HMC5843_CONFIG_REG_A,
				 HMC5843_RATE_MASK,
				 rate << HMC5843_RATE_OFFSET);
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक hmc5843_get_samp_freq_index(काष्ठा hmc5843_data *data,
				       पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < data->variant->n_regval_to_samp_freq; i++)
		अगर (val == data->variant->regval_to_samp_freq[i][0] &&
		    val2 == data->variant->regval_to_samp_freq[i][1])
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hmc5843_set_range_gain(काष्ठा hmc5843_data *data, u8 range)
अणु
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = regmap_update_bits(data->regmap, HMC5843_CONFIG_REG_B,
				 HMC5843_RANGE_GAIN_MASK,
				 range << HMC5843_RANGE_GAIN_OFFSET);
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार hmc5843_show_scale_avail(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा hmc5843_data *data = iio_priv(dev_to_iio_dev(dev));

	माप_प्रकार len = 0;
	पूर्णांक i;

	क्रम (i = 0; i < data->variant->n_regval_to_nanoscale; i++)
		len += scnम_लिखो(buf + len, PAGE_SIZE - len,
			"0.%09d ", data->variant->regval_to_nanoscale[i]);

	/* replace trailing space by newline */
	buf[len - 1] = '\n';

	वापस len;
पूर्ण

अटल IIO_DEVICE_ATTR(scale_available, S_IRUGO,
	hmc5843_show_scale_avail, शून्य, 0);

अटल पूर्णांक hmc5843_get_scale_index(काष्ठा hmc5843_data *data, पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i;

	अगर (val)
		वापस -EINVAL;

	क्रम (i = 0; i < data->variant->n_regval_to_nanoscale; i++)
		अगर (val2 == data->variant->regval_to_nanoscale[i])
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hmc5843_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा hmc5843_data *data = iio_priv(indio_dev);
	अचिन्हित पूर्णांक rval;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस hmc5843_पढ़ो_measurement(data, chan->scan_index, val);
	हाल IIO_CHAN_INFO_SCALE:
		ret = regmap_पढ़ो(data->regmap, HMC5843_CONFIG_REG_B, &rval);
		अगर (ret < 0)
			वापस ret;
		rval >>= HMC5843_RANGE_GAIN_OFFSET;
		*val = 0;
		*val2 = data->variant->regval_to_nanoscale[rval];
		वापस IIO_VAL_INT_PLUS_न_अंकO;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret = regmap_पढ़ो(data->regmap, HMC5843_CONFIG_REG_A, &rval);
		अगर (ret < 0)
			वापस ret;
		rval >>= HMC5843_RATE_OFFSET;
		*val = data->variant->regval_to_samp_freq[rval][0];
		*val2 = data->variant->regval_to_samp_freq[rval][1];
		वापस IIO_VAL_INT_PLUS_MICRO;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक hmc5843_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा hmc5843_data *data = iio_priv(indio_dev);
	पूर्णांक rate, range;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		rate = hmc5843_get_samp_freq_index(data, val, val2);
		अगर (rate < 0)
			वापस -EINVAL;

		वापस hmc5843_set_samp_freq(data, rate);
	हाल IIO_CHAN_INFO_SCALE:
		range = hmc5843_get_scale_index(data, val, val2);
		अगर (range < 0)
			वापस -EINVAL;

		वापस hmc5843_set_range_gain(data, range);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक hmc5843_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev,
				     काष्ठा iio_chan_spec स्थिर *chan,
				     दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_SCALE:
		वापस IIO_VAL_INT_PLUS_न_अंकO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल irqवापस_t hmc5843_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा hmc5843_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->lock);
	ret = hmc5843_रुको_measurement(data);
	अगर (ret < 0) अणु
		mutex_unlock(&data->lock);
		जाओ करोne;
	पूर्ण

	ret = regmap_bulk_पढ़ो(data->regmap, HMC5843_DATA_OUT_MSB_REGS,
			       data->buffer, 3 * माप(__be16));

	mutex_unlock(&data->lock);
	अगर (ret < 0)
		जाओ करोne;

	iio_push_to_buffers_with_बारtamp(indio_dev, data->buffer,
					   iio_get_समय_ns(indio_dev));

करोne:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

#घोषणा HMC5843_CHANNEL(axis, idx)					\
	अणु								\
		.type = IIO_MAGN,					\
		.modअगरied = 1,						\
		.channel2 = IIO_MOD_##axis,				\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |	\
			BIT(IIO_CHAN_INFO_SAMP_FREQ),			\
		.scan_index = idx,					\
		.scan_type = अणु						\
			.sign = 's',					\
			.realbits = 16,					\
			.storagebits = 16,				\
			.endianness = IIO_BE,				\
		पूर्ण,							\
		.ext_info = hmc5843_ext_info,	\
	पूर्ण

#घोषणा HMC5983_CHANNEL(axis, idx)					\
	अणु								\
		.type = IIO_MAGN,					\
		.modअगरied = 1,						\
		.channel2 = IIO_MOD_##axis,				\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |	\
			BIT(IIO_CHAN_INFO_SAMP_FREQ),			\
		.scan_index = idx,					\
		.scan_type = अणु						\
			.sign = 's',					\
			.realbits = 16,					\
			.storagebits = 16,				\
			.endianness = IIO_BE,				\
		पूर्ण,							\
		.ext_info = hmc5983_ext_info,	\
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec hmc5843_channels[] = अणु
	HMC5843_CHANNEL(X, 0),
	HMC5843_CHANNEL(Y, 1),
	HMC5843_CHANNEL(Z, 2),
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

/* Beware: Y and Z are exchanged on HMC5883 and 5983 */
अटल स्थिर काष्ठा iio_chan_spec hmc5883_channels[] = अणु
	HMC5843_CHANNEL(X, 0),
	HMC5843_CHANNEL(Z, 1),
	HMC5843_CHANNEL(Y, 2),
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec hmc5983_channels[] = अणु
	HMC5983_CHANNEL(X, 0),
	HMC5983_CHANNEL(Z, 1),
	HMC5983_CHANNEL(Y, 2),
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

अटल काष्ठा attribute *hmc5843_attributes[] = अणु
	&iio_dev_attr_scale_available.dev_attr.attr,
	&iio_dev_attr_sampling_frequency_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group hmc5843_group = अणु
	.attrs = hmc5843_attributes,
पूर्ण;

अटल स्थिर काष्ठा hmc5843_chip_info hmc5843_chip_info_tbl[] = अणु
	[HMC5843_ID] = अणु
		.channels = hmc5843_channels,
		.regval_to_samp_freq = hmc5843_regval_to_samp_freq,
		.n_regval_to_samp_freq =
				ARRAY_SIZE(hmc5843_regval_to_samp_freq),
		.regval_to_nanoscale = hmc5843_regval_to_nanoscale,
		.n_regval_to_nanoscale =
				ARRAY_SIZE(hmc5843_regval_to_nanoscale),
	पूर्ण,
	[HMC5883_ID] = अणु
		.channels = hmc5883_channels,
		.regval_to_samp_freq = hmc5883_regval_to_samp_freq,
		.n_regval_to_samp_freq =
				ARRAY_SIZE(hmc5883_regval_to_samp_freq),
		.regval_to_nanoscale = hmc5883_regval_to_nanoscale,
		.n_regval_to_nanoscale =
				ARRAY_SIZE(hmc5883_regval_to_nanoscale),
	पूर्ण,
	[HMC5883L_ID] = अणु
		.channels = hmc5883_channels,
		.regval_to_samp_freq = hmc5883_regval_to_samp_freq,
		.n_regval_to_samp_freq =
				ARRAY_SIZE(hmc5883_regval_to_samp_freq),
		.regval_to_nanoscale = hmc5883l_regval_to_nanoscale,
		.n_regval_to_nanoscale =
				ARRAY_SIZE(hmc5883l_regval_to_nanoscale),
	पूर्ण,
	[HMC5983_ID] = अणु
		.channels = hmc5983_channels,
		.regval_to_samp_freq = hmc5983_regval_to_samp_freq,
		.n_regval_to_samp_freq =
				ARRAY_SIZE(hmc5983_regval_to_samp_freq),
		.regval_to_nanoscale = hmc5883l_regval_to_nanoscale,
		.n_regval_to_nanoscale =
				ARRAY_SIZE(hmc5883l_regval_to_nanoscale),
	पूर्ण
पूर्ण;

अटल पूर्णांक hmc5843_init(काष्ठा hmc5843_data *data)
अणु
	पूर्णांक ret;
	u8 id[3];

	ret = regmap_bulk_पढ़ो(data->regmap, HMC5843_ID_REG,
			       id, ARRAY_SIZE(id));
	अगर (ret < 0)
		वापस ret;
	अगर (id[0] != 'H' || id[1] != '4' || id[2] != '3') अणु
		dev_err(data->dev, "no HMC5843/5883/5883L/5983 sensor\n");
		वापस -ENODEV;
	पूर्ण

	ret = hmc5843_set_meas_conf(data, HMC5843_MEAS_CONF_NORMAL);
	अगर (ret < 0)
		वापस ret;
	ret = hmc5843_set_samp_freq(data, HMC5843_RATE_DEFAULT);
	अगर (ret < 0)
		वापस ret;
	ret = hmc5843_set_range_gain(data, HMC5843_RANGE_GAIN_DEFAULT);
	अगर (ret < 0)
		वापस ret;
	वापस hmc5843_set_mode(data, HMC5843_MODE_CONVERSION_CONTINUOUS);
पूर्ण

अटल स्थिर काष्ठा iio_info hmc5843_info = अणु
	.attrs = &hmc5843_group,
	.पढ़ो_raw = &hmc5843_पढ़ो_raw,
	.ग_लिखो_raw = &hmc5843_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt = &hmc5843_ग_लिखो_raw_get_fmt,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ hmc5843_scan_masks[] = अणु0x7, 0पूर्ण;

पूर्णांक hmc5843_common_suspend(काष्ठा device *dev)
अणु
	वापस hmc5843_set_mode(iio_priv(dev_get_drvdata(dev)),
				HMC5843_MODE_SLEEP);
पूर्ण
EXPORT_SYMBOL(hmc5843_common_suspend);

पूर्णांक hmc5843_common_resume(काष्ठा device *dev)
अणु
	वापस hmc5843_set_mode(iio_priv(dev_get_drvdata(dev)),
		HMC5843_MODE_CONVERSION_CONTINUOUS);
पूर्ण
EXPORT_SYMBOL(hmc5843_common_resume);

पूर्णांक hmc5843_common_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
			 क्रमागत hmc5843_ids id, स्थिर अक्षर *name)
अणु
	काष्ठा hmc5843_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	dev_set_drvdata(dev, indio_dev);

	/* शेष settings at probe */
	data = iio_priv(indio_dev);
	data->dev = dev;
	data->regmap = regmap;
	data->variant = &hmc5843_chip_info_tbl[id];
	mutex_init(&data->lock);

	ret = iio_पढ़ो_mount_matrix(dev, "mount-matrix",
				&data->orientation);
	अगर (ret)
		वापस ret;

	indio_dev->name = name;
	indio_dev->info = &hmc5843_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = data->variant->channels;
	indio_dev->num_channels = 4;
	indio_dev->available_scan_masks = hmc5843_scan_masks;

	ret = hmc5843_init(data);
	अगर (ret < 0)
		वापस ret;

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
					 hmc5843_trigger_handler, शून्य);
	अगर (ret < 0)
		जाओ buffer_setup_err;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ buffer_cleanup;

	वापस 0;

buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);
buffer_setup_err:
	hmc5843_set_mode(iio_priv(indio_dev), HMC5843_MODE_SLEEP);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(hmc5843_common_probe);

पूर्णांक hmc5843_common_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);

	/*  sleep mode to save घातer */
	hmc5843_set_mode(iio_priv(indio_dev), HMC5843_MODE_SLEEP);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(hmc5843_common_हटाओ);

MODULE_AUTHOR("Shubhrajyoti Datta <shubhrajyoti@ti.com>");
MODULE_DESCRIPTION("HMC5843/5883/5883L/5983 core driver");
MODULE_LICENSE("GPL");
