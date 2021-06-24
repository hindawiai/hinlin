<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AD7170/AD7171 and AD7780/AD7781 SPI ADC driver
 *
 * Copyright 2011 Analog Devices Inc.
 * Copyright 2019 Renato Lui Geh
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
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/bits.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/adc/ad_sigma_delta.h>

#घोषणा AD7780_RDY		BIT(7)
#घोषणा AD7780_FILTER		BIT(6)
#घोषणा AD7780_ERR		BIT(5)
#घोषणा AD7780_ID1		BIT(4)
#घोषणा AD7780_ID0		BIT(3)
#घोषणा AD7780_GAIN		BIT(2)

#घोषणा AD7170_ID		0
#घोषणा AD7171_ID		1
#घोषणा AD7780_ID		1
#घोषणा AD7781_ID		0

#घोषणा AD7780_ID_MASK		(AD7780_ID0 | AD7780_ID1)

#घोषणा AD7780_PATTERN_GOOD	1
#घोषणा AD7780_PATTERN_MASK	GENMASK(1, 0)

#घोषणा AD7170_PATTERN_GOOD	5
#घोषणा AD7170_PATTERN_MASK	GENMASK(2, 0)

#घोषणा AD7780_GAIN_MIDPOINT	64
#घोषणा AD7780_FILTER_MIDPOINT	13350

अटल स्थिर अचिन्हित पूर्णांक ad778x_gain[2]      = अणु 1, 128 पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक ad778x_odr_avail[2] = अणु 10000, 16700 पूर्ण;

काष्ठा ad7780_chip_info अणु
	काष्ठा iio_chan_spec	channel;
	अचिन्हित पूर्णांक		pattern_mask;
	अचिन्हित पूर्णांक		pattern;
	bool			is_ad778x;
पूर्ण;

काष्ठा ad7780_state अणु
	स्थिर काष्ठा ad7780_chip_info	*chip_info;
	काष्ठा regulator		*reg;
	काष्ठा gpio_desc		*घातerकरोwn_gpio;
	काष्ठा gpio_desc		*gain_gpio;
	काष्ठा gpio_desc		*filter_gpio;
	अचिन्हित पूर्णांक			gain;
	अचिन्हित पूर्णांक			odr;
	अचिन्हित पूर्णांक			पूर्णांक_vref_mv;

	काष्ठा ad_sigma_delta sd;
पूर्ण;

क्रमागत ad7780_supported_device_ids अणु
	ID_AD7170,
	ID_AD7171,
	ID_AD7780,
	ID_AD7781,
पूर्ण;

अटल काष्ठा ad7780_state *ad_sigma_delta_to_ad7780(काष्ठा ad_sigma_delta *sd)
अणु
	वापस container_of(sd, काष्ठा ad7780_state, sd);
पूर्ण

अटल पूर्णांक ad7780_set_mode(काष्ठा ad_sigma_delta *sigma_delta,
			   क्रमागत ad_sigma_delta_mode mode)
अणु
	काष्ठा ad7780_state *st = ad_sigma_delta_to_ad7780(sigma_delta);
	अचिन्हित पूर्णांक val;

	चयन (mode) अणु
	हाल AD_SD_MODE_SINGLE:
	हाल AD_SD_MODE_CONTINUOUS:
		val = 1;
		अवरोध;
	शेष:
		val = 0;
		अवरोध;
	पूर्ण

	gpiod_set_value(st->घातerकरोwn_gpio, val);

	वापस 0;
पूर्ण

अटल पूर्णांक ad7780_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	काष्ठा ad7780_state *st = iio_priv(indio_dev);
	पूर्णांक voltage_uv;

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस ad_sigma_delta_single_conversion(indio_dev, chan, val);
	हाल IIO_CHAN_INFO_SCALE:
		voltage_uv = regulator_get_voltage(st->reg);
		अगर (voltage_uv < 0)
			वापस voltage_uv;
		voltage_uv /= 1000;
		*val = voltage_uv * st->gain;
		*val2 = chan->scan_type.realbits - 1;
		st->पूर्णांक_vref_mv = voltage_uv;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	हाल IIO_CHAN_INFO_OFFSET:
		*val = -(1 << (chan->scan_type.realbits - 1));
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = st->odr;
		वापस IIO_VAL_INT;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad7780_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val,
			    पूर्णांक val2,
			    दीर्घ m)
अणु
	काष्ठा ad7780_state *st = iio_priv(indio_dev);
	स्थिर काष्ठा ad7780_chip_info *chip_info = st->chip_info;
	अचिन्हित दीर्घ दीर्घ vref;
	अचिन्हित पूर्णांक full_scale, gain;

	अगर (!chip_info->is_ad778x)
		वापस -EINVAL;

	चयन (m) अणु
	हाल IIO_CHAN_INFO_SCALE:
		अगर (val != 0)
			वापस -EINVAL;

		vref = st->पूर्णांक_vref_mv * 1000000LL;
		full_scale = 1 << (chip_info->channel.scan_type.realbits - 1);
		gain = DIV_ROUND_CLOSEST_ULL(vref, full_scale);
		gain = DIV_ROUND_CLOSEST(gain, val2);
		st->gain = gain;
		अगर (gain < AD7780_GAIN_MIDPOINT)
			gain = 0;
		अन्यथा
			gain = 1;
		gpiod_set_value(st->gain_gpio, gain);
		अवरोध;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		अगर (1000*val + val2/1000 < AD7780_FILTER_MIDPOINT)
			val = 0;
		अन्यथा
			val = 1;
		st->odr = ad778x_odr_avail[val];
		gpiod_set_value(st->filter_gpio, val);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ad7780_postprocess_sample(काष्ठा ad_sigma_delta *sigma_delta,
				     अचिन्हित पूर्णांक raw_sample)
अणु
	काष्ठा ad7780_state *st = ad_sigma_delta_to_ad7780(sigma_delta);
	स्थिर काष्ठा ad7780_chip_info *chip_info = st->chip_info;

	अगर ((raw_sample & AD7780_ERR) ||
	    ((raw_sample & chip_info->pattern_mask) != chip_info->pattern))
		वापस -EIO;

	अगर (chip_info->is_ad778x) अणु
		st->gain = ad778x_gain[raw_sample & AD7780_GAIN];
		st->odr = ad778x_odr_avail[raw_sample & AD7780_FILTER];
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ad_sigma_delta_info ad7780_sigma_delta_info = अणु
	.set_mode = ad7780_set_mode,
	.postprocess_sample = ad7780_postprocess_sample,
	.has_रेजिस्टरs = false,
	.irq_flags = IRQF_TRIGGER_LOW,
पूर्ण;

#घोषणा _AD7780_CHANNEL(_bits, _wordsize, _mask_all)		\
अणु								\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.channel = 0,						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |		\
		BIT(IIO_CHAN_INFO_OFFSET),			\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
	.info_mask_shared_by_all = _mask_all,			\
	.scan_index = 1,					\
	.scan_type = अणु						\
		.sign = 'u',					\
		.realbits = (_bits),				\
		.storagebits = 32,				\
		.shअगरt = (_wordsize) - (_bits),			\
		.endianness = IIO_BE,				\
	पूर्ण,							\
पूर्ण

#घोषणा AD7780_CHANNEL(_bits, _wordsize)	\
	_AD7780_CHANNEL(_bits, _wordsize, BIT(IIO_CHAN_INFO_SAMP_FREQ))
#घोषणा AD7170_CHANNEL(_bits, _wordsize)	\
	_AD7780_CHANNEL(_bits, _wordsize, 0)

अटल स्थिर काष्ठा ad7780_chip_info ad7780_chip_info_tbl[] = अणु
	[ID_AD7170] = अणु
		.channel = AD7170_CHANNEL(12, 24),
		.pattern = AD7170_PATTERN_GOOD,
		.pattern_mask = AD7170_PATTERN_MASK,
		.is_ad778x = false,
	पूर्ण,
	[ID_AD7171] = अणु
		.channel = AD7170_CHANNEL(16, 24),
		.pattern = AD7170_PATTERN_GOOD,
		.pattern_mask = AD7170_PATTERN_MASK,
		.is_ad778x = false,
	पूर्ण,
	[ID_AD7780] = अणु
		.channel = AD7780_CHANNEL(24, 32),
		.pattern = AD7780_PATTERN_GOOD,
		.pattern_mask = AD7780_PATTERN_MASK,
		.is_ad778x = true,
	पूर्ण,
	[ID_AD7781] = अणु
		.channel = AD7780_CHANNEL(20, 32),
		.pattern = AD7780_PATTERN_GOOD,
		.pattern_mask = AD7780_PATTERN_MASK,
		.is_ad778x = true,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_info ad7780_info = अणु
	.पढ़ो_raw = ad7780_पढ़ो_raw,
	.ग_लिखो_raw = ad7780_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक ad7780_init_gpios(काष्ठा device *dev, काष्ठा ad7780_state *st)
अणु
	पूर्णांक ret;

	st->घातerकरोwn_gpio = devm_gpiod_get_optional(dev,
						     "powerdown",
						     GPIOD_OUT_LOW);
	अगर (IS_ERR(st->घातerकरोwn_gpio)) अणु
		ret = PTR_ERR(st->घातerकरोwn_gpio);
		dev_err(dev, "Failed to request powerdown GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (!st->chip_info->is_ad778x)
		वापस 0;


	st->gain_gpio = devm_gpiod_get_optional(dev,
						"adi,gain",
						GPIOD_OUT_HIGH);
	अगर (IS_ERR(st->gain_gpio)) अणु
		ret = PTR_ERR(st->gain_gpio);
		dev_err(dev, "Failed to request gain GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	st->filter_gpio = devm_gpiod_get_optional(dev,
						  "adi,filter",
						  GPIOD_OUT_HIGH);
	अगर (IS_ERR(st->filter_gpio)) अणु
		ret = PTR_ERR(st->filter_gpio);
		dev_err(dev, "Failed to request filter GPIO: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ad7780_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad7780_state *st;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	st->gain = 1;

	ad_sd_init(&st->sd, indio_dev, spi, &ad7780_sigma_delta_info);

	st->chip_info =
		&ad7780_chip_info_tbl[spi_get_device_id(spi)->driver_data];

	spi_set_drvdata(spi, indio_dev);

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = &st->chip_info->channel;
	indio_dev->num_channels = 1;
	indio_dev->info = &ad7780_info;

	ret = ad7780_init_gpios(&spi->dev, st);
	अगर (ret)
		वापस ret;

	st->reg = devm_regulator_get(&spi->dev, "avdd");
	अगर (IS_ERR(st->reg))
		वापस PTR_ERR(st->reg);

	ret = regulator_enable(st->reg);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to enable specified AVdd supply\n");
		वापस ret;
	पूर्ण

	ret = ad_sd_setup_buffer_and_trigger(indio_dev);
	अगर (ret)
		जाओ error_disable_reg;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_cleanup_buffer_and_trigger;

	वापस 0;

error_cleanup_buffer_and_trigger:
	ad_sd_cleanup_buffer_and_trigger(indio_dev);
error_disable_reg:
	regulator_disable(st->reg);

	वापस ret;
पूर्ण

अटल पूर्णांक ad7780_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ad7780_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	ad_sd_cleanup_buffer_and_trigger(indio_dev);

	regulator_disable(st->reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad7780_id[] = अणु
	अणु"ad7170", ID_AD7170पूर्ण,
	अणु"ad7171", ID_AD7171पूर्ण,
	अणु"ad7780", ID_AD7780पूर्ण,
	अणु"ad7781", ID_AD7781पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad7780_id);

अटल काष्ठा spi_driver ad7780_driver = अणु
	.driver = अणु
		.name	= "ad7780",
	पूर्ण,
	.probe		= ad7780_probe,
	.हटाओ		= ad7780_हटाओ,
	.id_table	= ad7780_id,
पूर्ण;
module_spi_driver(ad7780_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD7780 and similar ADCs");
MODULE_LICENSE("GPL v2");
