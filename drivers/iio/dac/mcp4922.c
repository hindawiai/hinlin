<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * mcp4922.c
 *
 * Driver क्रम Microchip Digital to Analog Converters.
 * Supports MCP4902, MCP4912, and MCP4922.
 *
 * Copyright (c) 2014 EMAC Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/bitops.h>

#घोषणा MCP4922_NUM_CHANNELS	2

क्रमागत mcp4922_supported_device_ids अणु
	ID_MCP4902,
	ID_MCP4912,
	ID_MCP4922,
पूर्ण;

काष्ठा mcp4922_state अणु
	काष्ठा spi_device *spi;
	अचिन्हित पूर्णांक value[MCP4922_NUM_CHANNELS];
	अचिन्हित पूर्णांक vref_mv;
	काष्ठा regulator *vref_reg;
	u8 mosi[2] ____cacheline_aligned;
पूर्ण;

#घोषणा MCP4922_CHAN(chan, bits) अणु			\
	.type = IIO_VOLTAGE,				\
	.output = 1,					\
	.indexed = 1,					\
	.channel = chan,				\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
	.scan_type = अणु					\
		.sign = 'u',				\
		.realbits = (bits),			\
		.storagebits = 16,			\
		.shअगरt = 12 - (bits),			\
	पूर्ण,						\
पूर्ण

अटल पूर्णांक mcp4922_spi_ग_लिखो(काष्ठा mcp4922_state *state, u8 addr, u32 val)
अणु
	state->mosi[1] = val & 0xff;
	state->mosi[0] = (addr == 0) ? 0x00 : 0x80;
	state->mosi[0] |= 0x30 | ((val >> 8) & 0x0f);

	वापस spi_ग_लिखो(state->spi, state->mosi, 2);
पूर्ण

अटल पूर्णांक mcp4922_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
		काष्ठा iio_chan_spec स्थिर *chan,
		पूर्णांक *val,
		पूर्णांक *val2,
		दीर्घ mask)
अणु
	काष्ठा mcp4922_state *state = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		*val = state->value[chan->channel];
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = state->vref_mv;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mcp4922_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
		काष्ठा iio_chan_spec स्थिर *chan,
		पूर्णांक val,
		पूर्णांक val2,
		दीर्घ mask)
अणु
	काष्ठा mcp4922_state *state = iio_priv(indio_dev);
	पूर्णांक ret;

	अगर (val2 != 0)
		वापस -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (val < 0 || val > GENMASK(chan->scan_type.realbits - 1, 0))
			वापस -EINVAL;
		val <<= chan->scan_type.shअगरt;

		ret = mcp4922_spi_ग_लिखो(state, chan->channel, val);
		अगर (!ret)
			state->value[chan->channel] = val;
		वापस ret;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mcp4922_channels[3][MCP4922_NUM_CHANNELS] = अणु
	[ID_MCP4902] = अणु MCP4922_CHAN(0, 8),	MCP4922_CHAN(1, 8) पूर्ण,
	[ID_MCP4912] = अणु MCP4922_CHAN(0, 10),	MCP4922_CHAN(1, 10) पूर्ण,
	[ID_MCP4922] = अणु MCP4922_CHAN(0, 12),	MCP4922_CHAN(1, 12) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_info mcp4922_info = अणु
	.पढ़ो_raw = &mcp4922_पढ़ो_raw,
	.ग_लिखो_raw = &mcp4922_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक mcp4922_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा mcp4922_state *state;
	स्थिर काष्ठा spi_device_id *id;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*state));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	state = iio_priv(indio_dev);
	state->spi = spi;
	state->vref_reg = devm_regulator_get(&spi->dev, "vref");
	अगर (IS_ERR(state->vref_reg)) अणु
		dev_err(&spi->dev, "Vref regulator not specified\n");
		वापस PTR_ERR(state->vref_reg);
	पूर्ण

	ret = regulator_enable(state->vref_reg);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to enable vref regulator: %d\n",
				ret);
		वापस ret;
	पूर्ण

	ret = regulator_get_voltage(state->vref_reg);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "Failed to read vref regulator: %d\n",
				ret);
		जाओ error_disable_reg;
	पूर्ण
	state->vref_mv = ret / 1000;

	spi_set_drvdata(spi, indio_dev);
	id = spi_get_device_id(spi);
	indio_dev->info = &mcp4922_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = mcp4922_channels[id->driver_data];
	indio_dev->num_channels = MCP4922_NUM_CHANNELS;
	indio_dev->name = id->name;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to register iio device: %d\n",
				ret);
		जाओ error_disable_reg;
	पूर्ण

	वापस 0;

error_disable_reg:
	regulator_disable(state->vref_reg);

	वापस ret;
पूर्ण

अटल पूर्णांक mcp4922_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा mcp4922_state *state;

	iio_device_unरेजिस्टर(indio_dev);
	state = iio_priv(indio_dev);
	regulator_disable(state->vref_reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id mcp4922_id[] = अणु
	अणु"mcp4902", ID_MCP4902पूर्ण,
	अणु"mcp4912", ID_MCP4912पूर्ण,
	अणु"mcp4922", ID_MCP4922पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, mcp4922_id);

अटल काष्ठा spi_driver mcp4922_driver = अणु
	.driver = अणु
		   .name = "mcp4922",
		   पूर्ण,
	.probe = mcp4922_probe,
	.हटाओ = mcp4922_हटाओ,
	.id_table = mcp4922_id,
पूर्ण;
module_spi_driver(mcp4922_driver);

MODULE_AUTHOR("Michael Welling <mwelling@ieee.org>");
MODULE_DESCRIPTION("Microchip MCP4902, MCP4912, MCP4922 DAC");
MODULE_LICENSE("GPL v2");
