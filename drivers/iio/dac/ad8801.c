<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IIO DAC driver क्रम Analog Devices AD8801 DAC
 *
 * Copyright (C) 2016 Gwenhael Goavec-Merou
 */

#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/sysfs.h>

#घोषणा AD8801_CFG_ADDR_OFFSET 8

क्रमागत ad8801_device_ids अणु
	ID_AD8801,
	ID_AD8803,
पूर्ण;

काष्ठा ad8801_state अणु
	काष्ठा spi_device *spi;
	अचिन्हित अक्षर dac_cache[8]; /* Value ग_लिखो on each channel */
	अचिन्हित पूर्णांक vrefh_mv;
	अचिन्हित पूर्णांक vrefl_mv;
	काष्ठा regulator *vrefh_reg;
	काष्ठा regulator *vrefl_reg;

	__be16 data ____cacheline_aligned;
पूर्ण;

अटल पूर्णांक ad8801_spi_ग_लिखो(काष्ठा ad8801_state *state,
	u8 channel, अचिन्हित अक्षर value)
अणु
	state->data = cpu_to_be16((channel << AD8801_CFG_ADDR_OFFSET) | value);
	वापस spi_ग_लिखो(state->spi, &state->data, माप(state->data));
पूर्ण

अटल पूर्णांक ad8801_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा ad8801_state *state = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (val >= 256 || val < 0)
			वापस -EINVAL;

		ret = ad8801_spi_ग_लिखो(state, chan->channel, val);
		अगर (ret == 0)
			state->dac_cache[chan->channel] = val;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ad8801_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	काष्ठा ad8801_state *state = iio_priv(indio_dev);

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		*val = state->dac_cache[chan->channel];
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = state->vrefh_mv - state->vrefl_mv;
		*val2 = 8;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	हाल IIO_CHAN_INFO_OFFSET:
		*val = state->vrefl_mv;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info ad8801_info = अणु
	.पढ़ो_raw = ad8801_पढ़ो_raw,
	.ग_लिखो_raw = ad8801_ग_लिखो_raw,
पूर्ण;

#घोषणा AD8801_CHANNEL(chan) अणु		\
	.type = IIO_VOLTAGE,			\
	.indexed = 1,				\
	.output = 1,				\
	.channel = chan,			\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |	\
		BIT(IIO_CHAN_INFO_OFFSET), \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ad8801_channels[] = अणु
	AD8801_CHANNEL(0),
	AD8801_CHANNEL(1),
	AD8801_CHANNEL(2),
	AD8801_CHANNEL(3),
	AD8801_CHANNEL(4),
	AD8801_CHANNEL(5),
	AD8801_CHANNEL(6),
	AD8801_CHANNEL(7),
पूर्ण;

अटल पूर्णांक ad8801_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा ad8801_state *state;
	स्थिर काष्ठा spi_device_id *id;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*state));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	state = iio_priv(indio_dev);
	state->spi = spi;
	id = spi_get_device_id(spi);

	state->vrefh_reg = devm_regulator_get(&spi->dev, "vrefh");
	अगर (IS_ERR(state->vrefh_reg)) अणु
		dev_err(&spi->dev, "Vrefh regulator not specified\n");
		वापस PTR_ERR(state->vrefh_reg);
	पूर्ण

	ret = regulator_enable(state->vrefh_reg);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to enable vrefh regulator: %d\n",
				ret);
		वापस ret;
	पूर्ण

	ret = regulator_get_voltage(state->vrefh_reg);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "Failed to read vrefh regulator: %d\n",
				ret);
		जाओ error_disable_vrefh_reg;
	पूर्ण
	state->vrefh_mv = ret / 1000;

	अगर (id->driver_data == ID_AD8803) अणु
		state->vrefl_reg = devm_regulator_get(&spi->dev, "vrefl");
		अगर (IS_ERR(state->vrefl_reg)) अणु
			dev_err(&spi->dev, "Vrefl regulator not specified\n");
			ret = PTR_ERR(state->vrefl_reg);
			जाओ error_disable_vrefh_reg;
		पूर्ण

		ret = regulator_enable(state->vrefl_reg);
		अगर (ret) अणु
			dev_err(&spi->dev, "Failed to enable vrefl regulator: %d\n",
					ret);
			जाओ error_disable_vrefh_reg;
		पूर्ण

		ret = regulator_get_voltage(state->vrefl_reg);
		अगर (ret < 0) अणु
			dev_err(&spi->dev, "Failed to read vrefl regulator: %d\n",
					ret);
			जाओ error_disable_vrefl_reg;
		पूर्ण
		state->vrefl_mv = ret / 1000;
	पूर्ण अन्यथा अणु
		state->vrefl_mv = 0;
		state->vrefl_reg = शून्य;
	पूर्ण

	spi_set_drvdata(spi, indio_dev);
	indio_dev->info = &ad8801_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = ad8801_channels;
	indio_dev->num_channels = ARRAY_SIZE(ad8801_channels);
	indio_dev->name = id->name;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to register iio device: %d\n",
				ret);
		जाओ error_disable_vrefl_reg;
	पूर्ण

	वापस 0;

error_disable_vrefl_reg:
	अगर (state->vrefl_reg)
		regulator_disable(state->vrefl_reg);
error_disable_vrefh_reg:
	regulator_disable(state->vrefh_reg);
	वापस ret;
पूर्ण

अटल पूर्णांक ad8801_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ad8801_state *state = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	अगर (state->vrefl_reg)
		regulator_disable(state->vrefl_reg);
	regulator_disable(state->vrefh_reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad8801_ids[] = अणु
	अणु"ad8801", ID_AD8801पूर्ण,
	अणु"ad8803", ID_AD8803पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad8801_ids);

अटल काष्ठा spi_driver ad8801_driver = अणु
	.driver = अणु
		.name	= "ad8801",
	पूर्ण,
	.probe		= ad8801_probe,
	.हटाओ		= ad8801_हटाओ,
	.id_table	= ad8801_ids,
पूर्ण;
module_spi_driver(ad8801_driver);

MODULE_AUTHOR("Gwenhael Goavec-Merou <gwenhael.goavec-merou@trabucayre.com>");
MODULE_DESCRIPTION("Analog Devices AD8801/AD8803 DAC");
MODULE_LICENSE("GPL v2");
