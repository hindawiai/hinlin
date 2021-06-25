<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AD7787/AD7788/AD7789/AD7790/AD7791 SPI ADC driver
 *
 * Copyright 2012 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/err.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/adc/ad_sigma_delta.h>

#समावेश <linux/platक्रमm_data/ad7791.h>

#घोषणा AD7791_REG_COMM			0x0 /* For ग_लिखोs */
#घोषणा AD7791_REG_STATUS		0x0 /* For पढ़ोs */
#घोषणा AD7791_REG_MODE			0x1
#घोषणा AD7791_REG_FILTER		0x2
#घोषणा AD7791_REG_DATA			0x3

#घोषणा AD7791_MODE_CONTINUOUS		0x00
#घोषणा AD7791_MODE_SINGLE		0x02
#घोषणा AD7791_MODE_POWERDOWN		0x03

#घोषणा AD7791_CH_AIN1P_AIN1N		0x00
#घोषणा AD7791_CH_AIN2			0x01
#घोषणा AD7791_CH_AIN1N_AIN1N		0x02
#घोषणा AD7791_CH_AVDD_MONITOR		0x03

#घोषणा AD7791_FILTER_CLK_DIV_1		(0x0 << 4)
#घोषणा AD7791_FILTER_CLK_DIV_2		(0x1 << 4)
#घोषणा AD7791_FILTER_CLK_DIV_4		(0x2 << 4)
#घोषणा AD7791_FILTER_CLK_DIV_8		(0x3 << 4)
#घोषणा AD7791_FILTER_CLK_MASK		(0x3 << 4)
#घोषणा AD7791_FILTER_RATE_120		0x0
#घोषणा AD7791_FILTER_RATE_100		0x1
#घोषणा AD7791_FILTER_RATE_33_3		0x2
#घोषणा AD7791_FILTER_RATE_20		0x3
#घोषणा AD7791_FILTER_RATE_16_6		0x4
#घोषणा AD7791_FILTER_RATE_16_7		0x5
#घोषणा AD7791_FILTER_RATE_13_3		0x6
#घोषणा AD7791_FILTER_RATE_9_5		0x7
#घोषणा AD7791_FILTER_RATE_MASK		0x7

#घोषणा AD7791_MODE_BUFFER		BIT(1)
#घोषणा AD7791_MODE_UNIPOLAR		BIT(2)
#घोषणा AD7791_MODE_BURNOUT		BIT(3)
#घोषणा AD7791_MODE_SEL_MASK		(0x3 << 6)
#घोषणा AD7791_MODE_SEL(x)		((x) << 6)

#घोषणा __AD7991_CHANNEL(_si, _channel1, _channel2, _address, _bits, \
	_storagebits, _shअगरt, _extend_name, _type, _mask_all) \
	अणु \
		.type = (_type), \
		.dअगरferential = (_channel2 == -1 ? 0 : 1), \
		.indexed = 1, \
		.channel = (_channel1), \
		.channel2 = (_channel2), \
		.address = (_address), \
		.extend_name = (_extend_name), \
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) | \
			BIT(IIO_CHAN_INFO_OFFSET), \
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
		.info_mask_shared_by_all = _mask_all, \
		.scan_index = (_si), \
		.scan_type = अणु \
			.sign = 'u', \
			.realbits = (_bits), \
			.storagebits = (_storagebits), \
			.shअगरt = (_shअगरt), \
			.endianness = IIO_BE, \
		पूर्ण, \
	पूर्ण

#घोषणा AD7991_SHORTED_CHANNEL(_si, _channel, _address, _bits, \
	_storagebits, _shअगरt) \
	__AD7991_CHANNEL(_si, _channel, _channel, _address, _bits, \
		_storagebits, _shअगरt, "shorted", IIO_VOLTAGE, \
		BIT(IIO_CHAN_INFO_SAMP_FREQ))

#घोषणा AD7991_CHANNEL(_si, _channel, _address, _bits, \
	_storagebits, _shअगरt) \
	__AD7991_CHANNEL(_si, _channel, -1, _address, _bits, \
		_storagebits, _shअगरt, शून्य, IIO_VOLTAGE, \
		 BIT(IIO_CHAN_INFO_SAMP_FREQ))

#घोषणा AD7991_DIFF_CHANNEL(_si, _channel1, _channel2, _address, _bits, \
	_storagebits, _shअगरt) \
	__AD7991_CHANNEL(_si, _channel1, _channel2, _address, _bits, \
		_storagebits, _shअगरt, शून्य, IIO_VOLTAGE, \
		BIT(IIO_CHAN_INFO_SAMP_FREQ))

#घोषणा AD7991_SUPPLY_CHANNEL(_si, _channel, _address, _bits, _storagebits, \
	_shअगरt) \
	__AD7991_CHANNEL(_si, _channel, -1, _address, _bits, \
		_storagebits, _shअगरt, "supply", IIO_VOLTAGE, \
		BIT(IIO_CHAN_INFO_SAMP_FREQ))

#घोषणा DECLARE_AD7787_CHANNELS(name, bits, storagebits) \
स्थिर काष्ठा iio_chan_spec name[] = अणु \
	AD7991_DIFF_CHANNEL(0, 0, 0, AD7791_CH_AIN1P_AIN1N, \
		(bits), (storagebits), 0), \
	AD7991_CHANNEL(1, 1, AD7791_CH_AIN2, (bits), (storagebits), 0), \
	AD7991_SHORTED_CHANNEL(2, 0, AD7791_CH_AIN1N_AIN1N, \
		(bits), (storagebits), 0), \
	AD7991_SUPPLY_CHANNEL(3, 2, AD7791_CH_AVDD_MONITOR,  \
		(bits), (storagebits), 0), \
	IIO_CHAN_SOFT_TIMESTAMP(4), \
पूर्ण

#घोषणा DECLARE_AD7791_CHANNELS(name, bits, storagebits) \
स्थिर काष्ठा iio_chan_spec name[] = अणु \
	AD7991_DIFF_CHANNEL(0, 0, 0, AD7791_CH_AIN1P_AIN1N, \
		(bits), (storagebits), 0), \
	AD7991_SHORTED_CHANNEL(1, 0, AD7791_CH_AIN1N_AIN1N, \
		(bits), (storagebits), 0), \
	AD7991_SUPPLY_CHANNEL(2, 1, AD7791_CH_AVDD_MONITOR, \
		(bits), (storagebits), 0), \
	IIO_CHAN_SOFT_TIMESTAMP(3), \
पूर्ण

अटल DECLARE_AD7787_CHANNELS(ad7787_channels, 24, 32);
अटल DECLARE_AD7791_CHANNELS(ad7790_channels, 16, 16);
अटल DECLARE_AD7791_CHANNELS(ad7791_channels, 24, 32);

क्रमागत अणु
	AD7787,
	AD7788,
	AD7789,
	AD7790,
	AD7791,
पूर्ण;

क्रमागत ad7791_chip_info_flags अणु
	AD7791_FLAG_HAS_FILTER		= (1 << 0),
	AD7791_FLAG_HAS_BUFFER		= (1 << 1),
	AD7791_FLAG_HAS_UNIPOLAR	= (1 << 2),
	AD7791_FLAG_HAS_BURNOUT		= (1 << 3),
पूर्ण;

काष्ठा ad7791_chip_info अणु
	स्थिर काष्ठा iio_chan_spec *channels;
	अचिन्हित पूर्णांक num_channels;
	क्रमागत ad7791_chip_info_flags flags;
पूर्ण;

अटल स्थिर काष्ठा ad7791_chip_info ad7791_chip_infos[] = अणु
	[AD7787] = अणु
		.channels = ad7787_channels,
		.num_channels = ARRAY_SIZE(ad7787_channels),
		.flags = AD7791_FLAG_HAS_FILTER | AD7791_FLAG_HAS_BUFFER |
			AD7791_FLAG_HAS_UNIPOLAR | AD7791_FLAG_HAS_BURNOUT,
	पूर्ण,
	[AD7788] = अणु
		.channels = ad7790_channels,
		.num_channels = ARRAY_SIZE(ad7790_channels),
		.flags = AD7791_FLAG_HAS_UNIPOLAR,
	पूर्ण,
	[AD7789] = अणु
		.channels = ad7791_channels,
		.num_channels = ARRAY_SIZE(ad7791_channels),
		.flags = AD7791_FLAG_HAS_UNIPOLAR,
	पूर्ण,
	[AD7790] = अणु
		.channels = ad7790_channels,
		.num_channels = ARRAY_SIZE(ad7790_channels),
		.flags = AD7791_FLAG_HAS_FILTER | AD7791_FLAG_HAS_BUFFER |
			AD7791_FLAG_HAS_BURNOUT,
	पूर्ण,
	[AD7791] = अणु
		.channels = ad7791_channels,
		.num_channels = ARRAY_SIZE(ad7791_channels),
		.flags = AD7791_FLAG_HAS_FILTER | AD7791_FLAG_HAS_BUFFER |
			AD7791_FLAG_HAS_UNIPOLAR | AD7791_FLAG_HAS_BURNOUT,
	पूर्ण,
पूर्ण;

काष्ठा ad7791_state अणु
	काष्ठा ad_sigma_delta sd;
	uपूर्णांक8_t mode;
	uपूर्णांक8_t filter;

	काष्ठा regulator *reg;
	स्थिर काष्ठा ad7791_chip_info *info;
पूर्ण;

अटल स्थिर पूर्णांक ad7791_sample_freq_avail[8][2] = अणु
	[AD7791_FILTER_RATE_120] =  अणु 120, 0 पूर्ण,
	[AD7791_FILTER_RATE_100] =  अणु 100, 0 पूर्ण,
	[AD7791_FILTER_RATE_33_3] = अणु 33,  300000 पूर्ण,
	[AD7791_FILTER_RATE_20] =   अणु 20,  0 पूर्ण,
	[AD7791_FILTER_RATE_16_6] = अणु 16,  600000 पूर्ण,
	[AD7791_FILTER_RATE_16_7] = अणु 16,  700000 पूर्ण,
	[AD7791_FILTER_RATE_13_3] = अणु 13,  300000 पूर्ण,
	[AD7791_FILTER_RATE_9_5] =  अणु 9,   500000 पूर्ण,
पूर्ण;

अटल काष्ठा ad7791_state *ad_sigma_delta_to_ad7791(काष्ठा ad_sigma_delta *sd)
अणु
	वापस container_of(sd, काष्ठा ad7791_state, sd);
पूर्ण

अटल पूर्णांक ad7791_set_channel(काष्ठा ad_sigma_delta *sd, अचिन्हित पूर्णांक channel)
अणु
	ad_sd_set_comm(sd, channel);

	वापस 0;
पूर्ण

अटल पूर्णांक ad7791_set_mode(काष्ठा ad_sigma_delta *sd,
	क्रमागत ad_sigma_delta_mode mode)
अणु
	काष्ठा ad7791_state *st = ad_sigma_delta_to_ad7791(sd);

	चयन (mode) अणु
	हाल AD_SD_MODE_CONTINUOUS:
		mode = AD7791_MODE_CONTINUOUS;
		अवरोध;
	हाल AD_SD_MODE_SINGLE:
		mode = AD7791_MODE_SINGLE;
		अवरोध;
	हाल AD_SD_MODE_IDLE:
	हाल AD_SD_MODE_POWERDOWN:
		mode = AD7791_MODE_POWERDOWN;
		अवरोध;
	पूर्ण

	st->mode &= ~AD7791_MODE_SEL_MASK;
	st->mode |= AD7791_MODE_SEL(mode);

	वापस ad_sd_ग_लिखो_reg(sd, AD7791_REG_MODE, माप(st->mode), st->mode);
पूर्ण

अटल स्थिर काष्ठा ad_sigma_delta_info ad7791_sigma_delta_info = अणु
	.set_channel = ad7791_set_channel,
	.set_mode = ad7791_set_mode,
	.has_रेजिस्टरs = true,
	.addr_shअगरt = 4,
	.पढ़ो_mask = BIT(3),
	.irq_flags = IRQF_TRIGGER_LOW,
पूर्ण;

अटल पूर्णांक ad7791_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	काष्ठा ad7791_state *st = iio_priv(indio_dev);
	bool unipolar = !!(st->mode & AD7791_MODE_UNIPOLAR);
	अचिन्हित पूर्णांक rate;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस ad_sigma_delta_single_conversion(indio_dev, chan, val);
	हाल IIO_CHAN_INFO_OFFSET:
		/**
		 * Unipolar: 0 to VREF
		 * Bipolar -VREF to VREF
		 **/
		अगर (unipolar)
			*val = 0;
		अन्यथा
			*val = -(1 << (chan->scan_type.realbits - 1));
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		/* The monitor channel uses an पूर्णांकernal reference. */
		अगर (chan->address == AD7791_CH_AVDD_MONITOR) अणु
			/*
			 * The संकेत is attenuated by a factor of 5 and
			 * compared against a 1.17V पूर्णांकernal reference.
			 */
			*val = 1170 * 5;
		पूर्ण अन्यथा अणु
			पूर्णांक voltage_uv;

			voltage_uv = regulator_get_voltage(st->reg);
			अगर (voltage_uv < 0)
				वापस voltage_uv;

			*val = voltage_uv / 1000;
		पूर्ण
		अगर (unipolar)
			*val2 = chan->scan_type.realbits;
		अन्यथा
			*val2 = chan->scan_type.realbits - 1;

		वापस IIO_VAL_FRACTIONAL_LOG2;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		rate = st->filter & AD7791_FILTER_RATE_MASK;
		*val = ad7791_sample_freq_avail[rate][0];
		*val2 = ad7791_sample_freq_avail[rate][1];
		वापस IIO_VAL_INT_PLUS_MICRO;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad7791_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा ad7791_state *st = iio_priv(indio_dev);
	पूर्णांक ret, i;

	ret = iio_device_claim_direct_mode(indio_dev);
	अगर (ret)
		वापस ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		क्रम (i = 0; i < ARRAY_SIZE(ad7791_sample_freq_avail); i++) अणु
			अगर (ad7791_sample_freq_avail[i][0] == val &&
			    ad7791_sample_freq_avail[i][1] == val2)
				अवरोध;
		पूर्ण

		अगर (i == ARRAY_SIZE(ad7791_sample_freq_avail)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		st->filter &= ~AD7791_FILTER_RATE_MASK;
		st->filter |= i;
		ad_sd_ग_लिखो_reg(&st->sd, AD7791_REG_FILTER,
				माप(st->filter),
				st->filter);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	iio_device_release_direct_mode(indio_dev);
	वापस ret;
पूर्ण

अटल IIO_CONST_ATTR_SAMP_FREQ_AVAIL("120 100 33.3 20 16.7 16.6 13.3 9.5");

अटल काष्ठा attribute *ad7791_attributes[] = अणु
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad7791_attribute_group = अणु
	.attrs = ad7791_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info ad7791_info = अणु
	.पढ़ो_raw = &ad7791_पढ़ो_raw,
	.ग_लिखो_raw = &ad7791_ग_लिखो_raw,
	.attrs = &ad7791_attribute_group,
	.validate_trigger = ad_sd_validate_trigger,
पूर्ण;

अटल स्थिर काष्ठा iio_info ad7791_no_filter_info = अणु
	.पढ़ो_raw = &ad7791_पढ़ो_raw,
	.ग_लिखो_raw = &ad7791_ग_लिखो_raw,
	.validate_trigger = ad_sd_validate_trigger,
पूर्ण;

अटल पूर्णांक ad7791_setup(काष्ठा ad7791_state *st,
			काष्ठा ad7791_platक्रमm_data *pdata)
अणु
	/* Set to घातeron-reset शेष values */
	st->mode = AD7791_MODE_BUFFER;
	st->filter = AD7791_FILTER_RATE_16_6;

	अगर (!pdata)
		वापस 0;

	अगर ((st->info->flags & AD7791_FLAG_HAS_BUFFER) && !pdata->buffered)
		st->mode &= ~AD7791_MODE_BUFFER;

	अगर ((st->info->flags & AD7791_FLAG_HAS_BURNOUT) &&
		pdata->burnout_current)
		st->mode |= AD7791_MODE_BURNOUT;

	अगर ((st->info->flags & AD7791_FLAG_HAS_UNIPOLAR) && pdata->unipolar)
		st->mode |= AD7791_MODE_UNIPOLAR;

	वापस ad_sd_ग_लिखो_reg(&st->sd, AD7791_REG_MODE, माप(st->mode),
		st->mode);
पूर्ण

अटल पूर्णांक ad7791_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad7791_platक्रमm_data *pdata = spi->dev.platक्रमm_data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा ad7791_state *st;
	पूर्णांक ret;

	अगर (!spi->irq) अणु
		dev_err(&spi->dev, "Missing IRQ.\n");
		वापस -ENXIO;
	पूर्ण

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);

	st->reg = devm_regulator_get(&spi->dev, "refin");
	अगर (IS_ERR(st->reg))
		वापस PTR_ERR(st->reg);

	ret = regulator_enable(st->reg);
	अगर (ret)
		वापस ret;

	st->info = &ad7791_chip_infos[spi_get_device_id(spi)->driver_data];
	ad_sd_init(&st->sd, indio_dev, spi, &ad7791_sigma_delta_info);

	spi_set_drvdata(spi, indio_dev);

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = st->info->channels;
	indio_dev->num_channels = st->info->num_channels;
	अगर (st->info->flags & AD7791_FLAG_HAS_FILTER)
		indio_dev->info = &ad7791_info;
	अन्यथा
		indio_dev->info = &ad7791_no_filter_info;

	ret = ad_sd_setup_buffer_and_trigger(indio_dev);
	अगर (ret)
		जाओ error_disable_reg;

	ret = ad7791_setup(st, pdata);
	अगर (ret)
		जाओ error_हटाओ_trigger;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_हटाओ_trigger;

	वापस 0;

error_हटाओ_trigger:
	ad_sd_cleanup_buffer_and_trigger(indio_dev);
error_disable_reg:
	regulator_disable(st->reg);

	वापस ret;
पूर्ण

अटल पूर्णांक ad7791_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ad7791_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	ad_sd_cleanup_buffer_and_trigger(indio_dev);

	regulator_disable(st->reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad7791_spi_ids[] = अणु
	अणु "ad7787", AD7787 पूर्ण,
	अणु "ad7788", AD7788 पूर्ण,
	अणु "ad7789", AD7789 पूर्ण,
	अणु "ad7790", AD7790 पूर्ण,
	अणु "ad7791", AD7791 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad7791_spi_ids);

अटल काष्ठा spi_driver ad7791_driver = अणु
	.driver = अणु
		.name	= "ad7791",
	पूर्ण,
	.probe		= ad7791_probe,
	.हटाओ		= ad7791_हटाओ,
	.id_table	= ad7791_spi_ids,
पूर्ण;
module_spi_driver(ad7791_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Analog Devices AD7787/AD7788/AD7789/AD7790/AD7791 ADC driver");
MODULE_LICENSE("GPL v2");
