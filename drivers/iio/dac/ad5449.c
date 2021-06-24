<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AD5415, AD5426, AD5429, AD5432, AD5439, AD5443, AD5449 Digital to Analog
 * Converter driver.
 *
 * Copyright 2012 Analog Devices Inc.
 *  Author: Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#समावेश <linux/platक्रमm_data/ad5449.h>

#घोषणा AD5449_MAX_CHANNELS		2
#घोषणा AD5449_MAX_VREFS		2

#घोषणा AD5449_CMD_NOOP			0x0
#घोषणा AD5449_CMD_LOAD_AND_UPDATE(x)	(0x1 + (x) * 3)
#घोषणा AD5449_CMD_READ(x)		(0x2 + (x) * 3)
#घोषणा AD5449_CMD_LOAD(x)		(0x3 + (x) * 3)
#घोषणा AD5449_CMD_CTRL			13

#घोषणा AD5449_CTRL_SDO_OFFSET		10
#घोषणा AD5449_CTRL_DAISY_CHAIN		BIT(9)
#घोषणा AD5449_CTRL_HCLR_TO_MIDSCALE	BIT(8)
#घोषणा AD5449_CTRL_SAMPLE_RISING	BIT(7)

/**
 * काष्ठा ad5449_chip_info - chip specअगरic inक्रमmation
 * @channels:		Channel specअगरication
 * @num_channels:	Number of channels
 * @has_ctrl:		Chip has a control रेजिस्टर
 */
काष्ठा ad5449_chip_info अणु
	स्थिर काष्ठा iio_chan_spec *channels;
	अचिन्हित पूर्णांक num_channels;
	bool has_ctrl;
पूर्ण;

/**
 * काष्ठा ad5449 - driver instance specअगरic data
 * @spi:		the SPI device क्रम this driver instance
 * @chip_info:		chip model specअगरic स्थिरants, available modes etc
 * @vref_reg:		vref supply regulators
 * @has_sकरो:		whether the SDO line is connected
 * @dac_cache:		Cache क्रम the DAC values
 * @data:		spi transfer buffers
 * @lock:		lock to protect the data buffer during SPI ops
 */
काष्ठा ad5449 अणु
	काष्ठा spi_device		*spi;
	स्थिर काष्ठा ad5449_chip_info	*chip_info;
	काष्ठा regulator_bulk_data	vref_reg[AD5449_MAX_VREFS];
	काष्ठा mutex			lock;

	bool has_sकरो;
	uपूर्णांक16_t dac_cache[AD5449_MAX_CHANNELS];

	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	__be16 data[2] ____cacheline_aligned;
पूर्ण;

क्रमागत ad5449_type अणु
	ID_AD5426,
	ID_AD5429,
	ID_AD5432,
	ID_AD5439,
	ID_AD5443,
	ID_AD5449,
पूर्ण;

अटल पूर्णांक ad5449_ग_लिखो(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक addr,
	अचिन्हित पूर्णांक val)
अणु
	काष्ठा ad5449 *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);
	st->data[0] = cpu_to_be16((addr << 12) | val);
	ret = spi_ग_लिखो(st->spi, st->data, 2);
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5449_पढ़ो(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक addr,
	अचिन्हित पूर्णांक *val)
अणु
	काष्ठा ad5449 *st = iio_priv(indio_dev);
	पूर्णांक ret;
	काष्ठा spi_transfer t[] = अणु
		अणु
			.tx_buf = &st->data[0],
			.len = 2,
			.cs_change = 1,
		पूर्ण, अणु
			.tx_buf = &st->data[1],
			.rx_buf = &st->data[1],
			.len = 2,
		पूर्ण,
	पूर्ण;

	mutex_lock(&st->lock);
	st->data[0] = cpu_to_be16(addr << 12);
	st->data[1] = cpu_to_be16(AD5449_CMD_NOOP);

	ret = spi_sync_transfer(st->spi, t, ARRAY_SIZE(t));
	अगर (ret < 0)
		जाओ out_unlock;

	*val = be16_to_cpu(st->data[1]);

out_unlock:
	mutex_unlock(&st->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ad5449_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	काष्ठा ad5449 *st = iio_priv(indio_dev);
	काष्ठा regulator_bulk_data *reg;
	पूर्णांक scale_uv;
	पूर्णांक ret;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (st->has_sकरो) अणु
			ret = ad5449_पढ़ो(indio_dev,
				AD5449_CMD_READ(chan->address), val);
			अगर (ret)
				वापस ret;
			*val &= 0xfff;
		पूर्ण अन्यथा अणु
			*val = st->dac_cache[chan->address];
		पूर्ण

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		reg = &st->vref_reg[chan->channel];
		scale_uv = regulator_get_voltage(reg->consumer);
		अगर (scale_uv < 0)
			वापस scale_uv;

		*val = scale_uv / 1000;
		*val2 = chan->scan_type.realbits;

		वापस IIO_VAL_FRACTIONAL_LOG2;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad5449_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val, पूर्णांक val2, दीर्घ info)
अणु
	काष्ठा ad5449 *st = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (val < 0 || val >= (1 << chan->scan_type.realbits))
			वापस -EINVAL;

		ret = ad5449_ग_लिखो(indio_dev,
			AD5449_CMD_LOAD_AND_UPDATE(chan->address),
			val << chan->scan_type.shअगरt);
		अगर (ret == 0)
			st->dac_cache[chan->address] = val;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info ad5449_info = अणु
	.पढ़ो_raw = ad5449_पढ़ो_raw,
	.ग_लिखो_raw = ad5449_ग_लिखो_raw,
पूर्ण;

#घोषणा AD5449_CHANNEL(chan, bits) अणु				\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.output = 1,						\
	.channel = (chan),					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |		\
		BIT(IIO_CHAN_INFO_SCALE),			\
	.address = (chan),					\
	.scan_type = अणु						\
		.sign = 'u',					\
		.realbits = (bits),				\
		.storagebits = 16,				\
		.shअगरt = 12 - (bits),				\
	पूर्ण,							\
पूर्ण

#घोषणा DECLARE_AD5449_CHANNELS(name, bits) \
स्थिर काष्ठा iio_chan_spec name[] = अणु \
	AD5449_CHANNEL(0, bits), \
	AD5449_CHANNEL(1, bits), \
पूर्ण

अटल DECLARE_AD5449_CHANNELS(ad5429_channels, 8);
अटल DECLARE_AD5449_CHANNELS(ad5439_channels, 10);
अटल DECLARE_AD5449_CHANNELS(ad5449_channels, 12);

अटल स्थिर काष्ठा ad5449_chip_info ad5449_chip_info[] = अणु
	[ID_AD5426] = अणु
		.channels = ad5429_channels,
		.num_channels = 1,
		.has_ctrl = false,
	पूर्ण,
	[ID_AD5429] = अणु
		.channels = ad5429_channels,
		.num_channels = 2,
		.has_ctrl = true,
	पूर्ण,
	[ID_AD5432] = अणु
		.channels = ad5439_channels,
		.num_channels = 1,
		.has_ctrl = false,
	पूर्ण,
	[ID_AD5439] = अणु
		.channels = ad5439_channels,
		.num_channels = 2,
		.has_ctrl = true,
	पूर्ण,
	[ID_AD5443] = अणु
		.channels = ad5449_channels,
		.num_channels = 1,
		.has_ctrl = false,
	पूर्ण,
	[ID_AD5449] = अणु
		.channels = ad5449_channels,
		.num_channels = 2,
		.has_ctrl = true,
	पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *ad5449_vref_name(काष्ठा ad5449 *st, पूर्णांक n)
अणु
	अगर (st->chip_info->num_channels == 1)
		वापस "VREF";

	अगर (n == 0)
		वापस "VREFA";
	अन्यथा
		वापस "VREFB";
पूर्ण

अटल पूर्णांक ad5449_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad5449_platक्रमm_data *pdata = spi->dev.platक्रमm_data;
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	काष्ठा iio_dev *indio_dev;
	काष्ठा ad5449 *st;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);

	st->chip_info = &ad5449_chip_info[id->driver_data];
	st->spi = spi;

	क्रम (i = 0; i < st->chip_info->num_channels; ++i)
		st->vref_reg[i].supply = ad5449_vref_name(st, i);

	ret = devm_regulator_bulk_get(&spi->dev, st->chip_info->num_channels,
				st->vref_reg);
	अगर (ret)
		वापस ret;

	ret = regulator_bulk_enable(st->chip_info->num_channels, st->vref_reg);
	अगर (ret)
		वापस ret;

	indio_dev->name = id->name;
	indio_dev->info = &ad5449_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = st->chip_info->channels;
	indio_dev->num_channels = st->chip_info->num_channels;

	mutex_init(&st->lock);

	अगर (st->chip_info->has_ctrl) अणु
		अचिन्हित पूर्णांक ctrl = 0x00;
		अगर (pdata) अणु
			अगर (pdata->hardware_clear_to_midscale)
				ctrl |= AD5449_CTRL_HCLR_TO_MIDSCALE;
			ctrl |= pdata->sकरो_mode << AD5449_CTRL_SDO_OFFSET;
			st->has_sकरो = pdata->sकरो_mode != AD5449_SDO_DISABLED;
		पूर्ण अन्यथा अणु
			st->has_sकरो = true;
		पूर्ण
		ad5449_ग_लिखो(indio_dev, AD5449_CMD_CTRL, ctrl);
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_disable_reg;

	वापस 0;

error_disable_reg:
	regulator_bulk_disable(st->chip_info->num_channels, st->vref_reg);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5449_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ad5449 *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	regulator_bulk_disable(st->chip_info->num_channels, st->vref_reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad5449_spi_ids[] = अणु
	अणु "ad5415", ID_AD5449 पूर्ण,
	अणु "ad5426", ID_AD5426 पूर्ण,
	अणु "ad5429", ID_AD5429 पूर्ण,
	अणु "ad5432", ID_AD5432 पूर्ण,
	अणु "ad5439", ID_AD5439 पूर्ण,
	अणु "ad5443", ID_AD5443 पूर्ण,
	अणु "ad5449", ID_AD5449 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad5449_spi_ids);

अटल काष्ठा spi_driver ad5449_spi_driver = अणु
	.driver = अणु
		.name = "ad5449",
	पूर्ण,
	.probe = ad5449_spi_probe,
	.हटाओ = ad5449_spi_हटाओ,
	.id_table = ad5449_spi_ids,
पूर्ण;
module_spi_driver(ad5449_spi_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Analog Devices AD5449 and similar DACs");
MODULE_LICENSE("GPL v2");
