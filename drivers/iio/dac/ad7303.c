<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AD7303 Digital to analog converters driver
 *
 * Copyright 2013 Analog Devices Inc.
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा AD7303_CFG_EXTERNAL_VREF BIT(15)
#घोषणा AD7303_CFG_POWER_DOWN(ch) BIT(11 + (ch))
#घोषणा AD7303_CFG_ADDR_OFFSET	10

#घोषणा AD7303_CMD_UPDATE_DAC	(0x3 << 8)

/**
 * काष्ठा ad7303_state - driver instance specअगरic data
 * @spi:		the device क्रम this driver instance
 * @config:		cached config रेजिस्टर value
 * @dac_cache:		current DAC raw value (chip करोes not support पढ़ोback)
 * @vdd_reg:		reference to VDD regulator
 * @vref_reg:		reference to VREF regulator
 * @lock:		protect ग_लिखोs and cache updates
 * @data:		spi transfer buffer
 */

काष्ठा ad7303_state अणु
	काष्ठा spi_device *spi;
	uपूर्णांक16_t config;
	uपूर्णांक8_t dac_cache[2];

	काष्ठा regulator *vdd_reg;
	काष्ठा regulator *vref_reg;

	काष्ठा mutex lock;
	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	__be16 data ____cacheline_aligned;
पूर्ण;

अटल पूर्णांक ad7303_ग_लिखो(काष्ठा ad7303_state *st, अचिन्हित पूर्णांक chan,
	uपूर्णांक8_t val)
अणु
	st->data = cpu_to_be16(AD7303_CMD_UPDATE_DAC |
		(chan << AD7303_CFG_ADDR_OFFSET) |
		st->config | val);

	वापस spi_ग_लिखो(st->spi, &st->data, माप(st->data));
पूर्ण

अटल sमाप_प्रकार ad7303_पढ़ो_dac_घातerकरोwn(काष्ठा iio_dev *indio_dev,
	uपूर्णांकptr_t निजी, स्थिर काष्ठा iio_chan_spec *chan, अक्षर *buf)
अणु
	काष्ठा ad7303_state *st = iio_priv(indio_dev);

	वापस sysfs_emit(buf, "%d\n", (bool)(st->config &
		AD7303_CFG_POWER_DOWN(chan->channel)));
पूर्ण

अटल sमाप_प्रकार ad7303_ग_लिखो_dac_घातerकरोwn(काष्ठा iio_dev *indio_dev,
	 uपूर्णांकptr_t निजी, स्थिर काष्ठा iio_chan_spec *chan, स्थिर अक्षर *buf,
	 माप_प्रकार len)
अणु
	काष्ठा ad7303_state *st = iio_priv(indio_dev);
	bool pwr_करोwn;
	पूर्णांक ret;

	ret = strtobool(buf, &pwr_करोwn);
	अगर (ret)
		वापस ret;

	mutex_lock(&st->lock);

	अगर (pwr_करोwn)
		st->config |= AD7303_CFG_POWER_DOWN(chan->channel);
	अन्यथा
		st->config &= ~AD7303_CFG_POWER_DOWN(chan->channel);

	/* There is no noop cmd which allows us to only update the घातerकरोwn
	 * mode, so just ग_लिखो one of the DAC channels again */
	ad7303_ग_लिखो(st, chan->channel, st->dac_cache[chan->channel]);

	mutex_unlock(&st->lock);
	वापस len;
पूर्ण

अटल पूर्णांक ad7303_get_vref(काष्ठा ad7303_state *st,
	काष्ठा iio_chan_spec स्थिर *chan)
अणु
	पूर्णांक ret;

	अगर (st->config & AD7303_CFG_EXTERNAL_VREF)
		वापस regulator_get_voltage(st->vref_reg);

	ret = regulator_get_voltage(st->vdd_reg);
	अगर (ret < 0)
		वापस ret;
	वापस ret / 2;
पूर्ण

अटल पूर्णांक ad7303_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	काष्ठा ad7303_state *st = iio_priv(indio_dev);
	पूर्णांक vref_uv;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&st->lock);
		*val = st->dac_cache[chan->channel];
		mutex_unlock(&st->lock);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		vref_uv = ad7303_get_vref(st, chan);
		अगर (vref_uv < 0)
			वापस vref_uv;

		*val = 2 * vref_uv / 1000;
		*val2 = chan->scan_type.realbits;

		वापस IIO_VAL_FRACTIONAL_LOG2;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad7303_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा ad7303_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (val >= (1 << chan->scan_type.realbits) || val < 0)
			वापस -EINVAL;

		mutex_lock(&st->lock);
		ret = ad7303_ग_लिखो(st, chan->address, val);
		अगर (ret == 0)
			st->dac_cache[chan->channel] = val;
		mutex_unlock(&st->lock);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info ad7303_info = अणु
	.पढ़ो_raw = ad7303_पढ़ो_raw,
	.ग_लिखो_raw = ad7303_ग_लिखो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info ad7303_ext_info[] = अणु
	अणु
		.name = "powerdown",
		.पढ़ो = ad7303_पढ़ो_dac_घातerकरोwn,
		.ग_लिखो = ad7303_ग_लिखो_dac_घातerकरोwn,
		.shared = IIO_SEPARATE,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

#घोषणा AD7303_CHANNEL(chan) अणु					\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.output = 1,						\
	.channel = (chan),					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
	.address = (chan),					\
	.scan_type = अणु						\
		.sign = 'u',					\
		.realbits = 8,					\
		.storagebits = 8,				\
		.shअगरt = 0,					\
	पूर्ण,							\
	.ext_info = ad7303_ext_info,				\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ad7303_channels[] = अणु
	AD7303_CHANNEL(0),
	AD7303_CHANNEL(1),
पूर्ण;

अटल पूर्णांक ad7303_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	काष्ठा iio_dev *indio_dev;
	काष्ठा ad7303_state *st;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);

	st->spi = spi;

	mutex_init(&st->lock);

	st->vdd_reg = devm_regulator_get(&spi->dev, "Vdd");
	अगर (IS_ERR(st->vdd_reg))
		वापस PTR_ERR(st->vdd_reg);

	ret = regulator_enable(st->vdd_reg);
	अगर (ret)
		वापस ret;

	st->vref_reg = devm_regulator_get_optional(&spi->dev, "REF");
	अगर (IS_ERR(st->vref_reg)) अणु
		ret = PTR_ERR(st->vref_reg);
		अगर (ret != -ENODEV)
			जाओ err_disable_vdd_reg;
		st->vref_reg = शून्य;
	पूर्ण

	अगर (st->vref_reg) अणु
		ret = regulator_enable(st->vref_reg);
		अगर (ret)
			जाओ err_disable_vdd_reg;

		st->config |= AD7303_CFG_EXTERNAL_VREF;
	पूर्ण

	indio_dev->name = id->name;
	indio_dev->info = &ad7303_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = ad7303_channels;
	indio_dev->num_channels = ARRAY_SIZE(ad7303_channels);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ err_disable_vref_reg;

	वापस 0;

err_disable_vref_reg:
	अगर (st->vref_reg)
		regulator_disable(st->vref_reg);
err_disable_vdd_reg:
	regulator_disable(st->vdd_reg);
	वापस ret;
पूर्ण

अटल पूर्णांक ad7303_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ad7303_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	अगर (st->vref_reg)
		regulator_disable(st->vref_reg);
	regulator_disable(st->vdd_reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ad7303_spi_of_match[] = अणु
	अणु .compatible = "adi,ad7303", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ad7303_spi_of_match);

अटल स्थिर काष्ठा spi_device_id ad7303_spi_ids[] = अणु
	अणु "ad7303", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad7303_spi_ids);

अटल काष्ठा spi_driver ad7303_driver = अणु
	.driver = अणु
		.name = "ad7303",
		.of_match_table = ad7303_spi_of_match,
	पूर्ण,
	.probe = ad7303_probe,
	.हटाओ = ad7303_हटाओ,
	.id_table = ad7303_spi_ids,
पूर्ण;
module_spi_driver(ad7303_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Analog Devices AD7303 DAC driver");
MODULE_LICENSE("GPL v2");
