<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AD8366 and similar Gain Amplअगरiers
 * This driver supports the following gain amplअगरiers:
 *   AD8366 Dual-Digital Variable Gain Amplअगरier (VGA)
 *   ADA4961 BiCMOS RF Digital Gain Amplअगरier (DGA)
 *   ADL5240 Digitally controlled variable gain amplअगरier (VGA)
 *   HMC1119 0.25 dB LSB, 7-Bit, Silicon Digital Attenuator
 *
 * Copyright 2012-2019 Analog Devices Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/bitrev.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

क्रमागत ad8366_type अणु
	ID_AD8366,
	ID_ADA4961,
	ID_ADL5240,
	ID_HMC1119,
पूर्ण;

काष्ठा ad8366_info अणु
	पूर्णांक gain_min;
	पूर्णांक gain_max;
पूर्ण;

काष्ठा ad8366_state अणु
	काष्ठा spi_device	*spi;
	काष्ठा regulator	*reg;
	काष्ठा mutex            lock; /* protect sensor state */
	काष्ठा gpio_desc	*reset_gpio;
	अचिन्हित अक्षर		ch[2];
	क्रमागत ad8366_type	type;
	काष्ठा ad8366_info	*info;
	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	अचिन्हित अक्षर		data[2] ____cacheline_aligned;
पूर्ण;

अटल काष्ठा ad8366_info ad8366_infos[] = अणु
	[ID_AD8366] = अणु
		.gain_min = 4500,
		.gain_max = 20500,
	पूर्ण,
	[ID_ADA4961] = अणु
		.gain_min = -6000,
		.gain_max = 15000,
	पूर्ण,
	[ID_ADL5240] = अणु
		.gain_min = -11500,
		.gain_max = 20000,
	पूर्ण,
	[ID_HMC1119] = अणु
		.gain_min = -31750,
		.gain_max = 0,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ad8366_ग_लिखो(काष्ठा iio_dev *indio_dev,
			अचिन्हित अक्षर ch_a, अचिन्हित अक्षर ch_b)
अणु
	काष्ठा ad8366_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (st->type) अणु
	हाल ID_AD8366:
		ch_a = bitrev8(ch_a & 0x3F);
		ch_b = bitrev8(ch_b & 0x3F);

		st->data[0] = ch_b >> 4;
		st->data[1] = (ch_b << 4) | (ch_a >> 2);
		अवरोध;
	हाल ID_ADA4961:
		st->data[0] = ch_a & 0x1F;
		अवरोध;
	हाल ID_ADL5240:
		st->data[0] = (ch_a & 0x3F);
		अवरोध;
	हाल ID_HMC1119:
		st->data[0] = ch_a;
		अवरोध;
	पूर्ण

	ret = spi_ग_लिखो(st->spi, st->data, indio_dev->num_channels);
	अगर (ret < 0)
		dev_err(&indio_dev->dev, "write failed (%d)", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ad8366_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	काष्ठा ad8366_state *st = iio_priv(indio_dev);
	पूर्णांक ret;
	पूर्णांक code, gain = 0;

	mutex_lock(&st->lock);
	चयन (m) अणु
	हाल IIO_CHAN_INFO_HARDWAREGAIN:
		code = st->ch[chan->channel];

		चयन (st->type) अणु
		हाल ID_AD8366:
			gain = code * 253 + 4500;
			अवरोध;
		हाल ID_ADA4961:
			gain = 15000 - code * 1000;
			अवरोध;
		हाल ID_ADL5240:
			gain = 20000 - 31500 + code * 500;
			अवरोध;
		हाल ID_HMC1119:
			gain = -1 * code * 250;
			अवरोध;
		पूर्ण

		/* Values in dB */
		*val = gain / 1000;
		*val2 = (gain % 1000) * 1000;

		ret = IIO_VAL_INT_PLUS_MICRO_DB;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण;

अटल पूर्णांक ad8366_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val,
			    पूर्णांक val2,
			    दीर्घ mask)
अणु
	काष्ठा ad8366_state *st = iio_priv(indio_dev);
	काष्ठा ad8366_info *inf = st->info;
	पूर्णांक code = 0, gain;
	पूर्णांक ret;

	/* Values in dB */
	अगर (val < 0)
		gain = (val * 1000) - (val2 / 1000);
	अन्यथा
		gain = (val * 1000) + (val2 / 1000);

	अगर (gain > inf->gain_max || gain < inf->gain_min)
		वापस -EINVAL;

	चयन (st->type) अणु
	हाल ID_AD8366:
		code = (gain - 4500) / 253;
		अवरोध;
	हाल ID_ADA4961:
		code = (15000 - gain) / 1000;
		अवरोध;
	हाल ID_ADL5240:
		code = ((gain - 500 - 20000) / 500) & 0x3F;
		अवरोध;
	हाल ID_HMC1119:
		code = (असल(gain) / 250) & 0x7F;
		अवरोध;
	पूर्ण

	mutex_lock(&st->lock);
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_HARDWAREGAIN:
		st->ch[chan->channel] = code;
		ret = ad8366_ग_लिखो(indio_dev, st->ch[0], st->ch[1]);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ad8366_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev,
				    काष्ठा iio_chan_spec स्थिर *chan,
				    दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_HARDWAREGAIN:
		वापस IIO_VAL_INT_PLUS_MICRO_DB;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info ad8366_info = अणु
	.पढ़ो_raw = &ad8366_पढ़ो_raw,
	.ग_लिखो_raw = &ad8366_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt = &ad8366_ग_लिखो_raw_get_fmt,
पूर्ण;

#घोषणा AD8366_CHAN(_channel) अणु				\
	.type = IIO_VOLTAGE,				\
	.output = 1,					\
	.indexed = 1,					\
	.channel = _channel,				\
	.info_mask_separate = BIT(IIO_CHAN_INFO_HARDWAREGAIN),\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ad8366_channels[] = अणु
	AD8366_CHAN(0),
	AD8366_CHAN(1),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ada4961_channels[] = अणु
	AD8366_CHAN(0),
पूर्ण;

अटल पूर्णांक ad8366_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा ad8366_state *st;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);

	st->reg = devm_regulator_get(&spi->dev, "vcc");
	अगर (!IS_ERR(st->reg)) अणु
		ret = regulator_enable(st->reg);
		अगर (ret)
			वापस ret;
	पूर्ण

	spi_set_drvdata(spi, indio_dev);
	mutex_init(&st->lock);
	st->spi = spi;
	st->type = spi_get_device_id(spi)->driver_data;

	चयन (st->type) अणु
	हाल ID_AD8366:
		indio_dev->channels = ad8366_channels;
		indio_dev->num_channels = ARRAY_SIZE(ad8366_channels);
		अवरोध;
	हाल ID_ADA4961:
	हाल ID_ADL5240:
	हाल ID_HMC1119:
		st->reset_gpio = devm_gpiod_get_optional(&spi->dev, "reset", GPIOD_OUT_HIGH);
		अगर (IS_ERR(st->reset_gpio)) अणु
			ret = PTR_ERR(st->reset_gpio);
			जाओ error_disable_reg;
		पूर्ण
		indio_dev->channels = ada4961_channels;
		indio_dev->num_channels = ARRAY_SIZE(ada4961_channels);
		अवरोध;
	शेष:
		dev_err(&spi->dev, "Invalid device ID\n");
		ret = -EINVAL;
		जाओ error_disable_reg;
	पूर्ण

	st->info = &ad8366_infos[st->type];
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad8366_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = ad8366_ग_लिखो(indio_dev, 0 , 0);
	अगर (ret < 0)
		जाओ error_disable_reg;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_disable_reg;

	वापस 0;

error_disable_reg:
	अगर (!IS_ERR(st->reg))
		regulator_disable(st->reg);

	वापस ret;
पूर्ण

अटल पूर्णांक ad8366_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ad8366_state *st = iio_priv(indio_dev);
	काष्ठा regulator *reg = st->reg;

	iio_device_unरेजिस्टर(indio_dev);

	अगर (!IS_ERR(reg))
		regulator_disable(reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad8366_id[] = अणु
	अणु"ad8366",  ID_AD8366पूर्ण,
	अणु"ada4961", ID_ADA4961पूर्ण,
	अणु"adl5240", ID_ADL5240पूर्ण,
	अणु"hmc1119", ID_HMC1119पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad8366_id);

अटल काष्ठा spi_driver ad8366_driver = अणु
	.driver = अणु
		.name	= KBUILD_MODNAME,
	पूर्ण,
	.probe		= ad8366_probe,
	.हटाओ		= ad8366_हटाओ,
	.id_table	= ad8366_id,
पूर्ण;

module_spi_driver(ad8366_driver);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD8366 and similar Gain Amplifiers");
MODULE_LICENSE("GPL v2");
