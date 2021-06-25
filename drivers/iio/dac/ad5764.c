<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Analog devices AD5764, AD5764R, AD5744, AD5744R quad-channel
 * Digital to Analog Converters driver
 *
 * Copyright 2011 Analog Devices Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा AD5764_REG_SF_NOP			0x0
#घोषणा AD5764_REG_SF_CONFIG			0x1
#घोषणा AD5764_REG_SF_CLEAR			0x4
#घोषणा AD5764_REG_SF_LOAD			0x5
#घोषणा AD5764_REG_DATA(x)			((2 << 3) | (x))
#घोषणा AD5764_REG_COARSE_GAIN(x)		((3 << 3) | (x))
#घोषणा AD5764_REG_FINE_GAIN(x)			((4 << 3) | (x))
#घोषणा AD5764_REG_OFFSET(x)			((5 << 3) | (x))

#घोषणा AD5764_NUM_CHANNELS 4

/**
 * काष्ठा ad5764_chip_info - chip specअगरic inक्रमmation
 * @पूर्णांक_vref:	Value of the पूर्णांकernal reference voltage in uV - 0 अगर बाह्यal
 *		reference voltage is used
 * @channels:	channel specअगरication
*/
काष्ठा ad5764_chip_info अणु
	अचिन्हित दीर्घ पूर्णांक_vref;
	स्थिर काष्ठा iio_chan_spec *channels;
पूर्ण;

/**
 * काष्ठा ad5764_state - driver instance specअगरic data
 * @spi:		spi_device
 * @chip_info:		chip info
 * @vref_reg:		vref supply regulators
 * @lock:		lock to protect the data buffer during SPI ops
 * @data:		spi transfer buffers
 */

काष्ठा ad5764_state अणु
	काष्ठा spi_device		*spi;
	स्थिर काष्ठा ad5764_chip_info	*chip_info;
	काष्ठा regulator_bulk_data	vref_reg[2];
	काष्ठा mutex			lock;

	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	जोड़ अणु
		__be32 d32;
		u8 d8[4];
	पूर्ण data[2] ____cacheline_aligned;
पूर्ण;

क्रमागत ad5764_type अणु
	ID_AD5744,
	ID_AD5744R,
	ID_AD5764,
	ID_AD5764R,
पूर्ण;

#घोषणा AD5764_CHANNEL(_chan, _bits) अणु				\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.output = 1,						\
	.channel = (_chan),					\
	.address = (_chan),					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |		\
		BIT(IIO_CHAN_INFO_SCALE) |			\
		BIT(IIO_CHAN_INFO_CALIBSCALE) |			\
		BIT(IIO_CHAN_INFO_CALIBBIAS),			\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET),	\
	.scan_type = अणु						\
		.sign = 'u',					\
		.realbits = (_bits),				\
		.storagebits = 16,				\
		.shअगरt = 16 - (_bits),				\
	पूर्ण,							\
पूर्ण

#घोषणा DECLARE_AD5764_CHANNELS(_name, _bits) \
स्थिर काष्ठा iio_chan_spec _name##_channels[] = अणु \
	AD5764_CHANNEL(0, (_bits)), \
	AD5764_CHANNEL(1, (_bits)), \
	AD5764_CHANNEL(2, (_bits)), \
	AD5764_CHANNEL(3, (_bits)), \
पूर्ण;

अटल DECLARE_AD5764_CHANNELS(ad5764, 16);
अटल DECLARE_AD5764_CHANNELS(ad5744, 14);

अटल स्थिर काष्ठा ad5764_chip_info ad5764_chip_infos[] = अणु
	[ID_AD5744] = अणु
		.पूर्णांक_vref = 0,
		.channels = ad5744_channels,
	पूर्ण,
	[ID_AD5744R] = अणु
		.पूर्णांक_vref = 5000000,
		.channels = ad5744_channels,
	पूर्ण,
	[ID_AD5764] = अणु
		.पूर्णांक_vref = 0,
		.channels = ad5764_channels,
	पूर्ण,
	[ID_AD5764R] = अणु
		.पूर्णांक_vref = 5000000,
		.channels = ad5764_channels,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ad5764_ग_लिखो(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक reg,
	अचिन्हित पूर्णांक val)
अणु
	काष्ठा ad5764_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);
	st->data[0].d32 = cpu_to_be32((reg << 16) | val);

	ret = spi_ग_लिखो(st->spi, &st->data[0].d8[1], 3);
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5764_पढ़ो(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक reg,
	अचिन्हित पूर्णांक *val)
अणु
	काष्ठा ad5764_state *st = iio_priv(indio_dev);
	पूर्णांक ret;
	काष्ठा spi_transfer t[] = अणु
		अणु
			.tx_buf = &st->data[0].d8[1],
			.len = 3,
			.cs_change = 1,
		पूर्ण, अणु
			.rx_buf = &st->data[1].d8[1],
			.len = 3,
		पूर्ण,
	पूर्ण;

	mutex_lock(&st->lock);

	st->data[0].d32 = cpu_to_be32((1 << 23) | (reg << 16));

	ret = spi_sync_transfer(st->spi, t, ARRAY_SIZE(t));
	अगर (ret >= 0)
		*val = be32_to_cpu(st->data[1].d32) & 0xffff;

	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5764_chan_info_to_reg(काष्ठा iio_chan_spec स्थिर *chan, दीर्घ info)
अणु
	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस AD5764_REG_DATA(chan->address);
	हाल IIO_CHAN_INFO_CALIBBIAS:
		वापस AD5764_REG_OFFSET(chan->address);
	हाल IIO_CHAN_INFO_CALIBSCALE:
		वापस AD5764_REG_FINE_GAIN(chan->address);
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ad5764_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val, पूर्णांक val2, दीर्घ info)
अणु
	स्थिर पूर्णांक max_val = (1 << chan->scan_type.realbits);
	अचिन्हित पूर्णांक reg;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (val >= max_val || val < 0)
			वापस -EINVAL;
		val <<= chan->scan_type.shअगरt;
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		अगर (val >= 128 || val < -128)
			वापस -EINVAL;
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBSCALE:
		अगर (val >= 32 || val < -32)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	reg = ad5764_chan_info_to_reg(chan, info);
	वापस ad5764_ग_लिखो(indio_dev, reg, (u16)val);
पूर्ण

अटल पूर्णांक ad5764_get_channel_vref(काष्ठा ad5764_state *st,
	अचिन्हित पूर्णांक channel)
अणु
	अगर (st->chip_info->पूर्णांक_vref)
		वापस st->chip_info->पूर्णांक_vref;
	अन्यथा
		वापस regulator_get_voltage(st->vref_reg[channel / 2].consumer);
पूर्ण

अटल पूर्णांक ad5764_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	काष्ठा ad5764_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक reg;
	पूर्णांक vref;
	पूर्णांक ret;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		reg = AD5764_REG_DATA(chan->address);
		ret = ad5764_पढ़ो(indio_dev, reg, val);
		अगर (ret < 0)
			वापस ret;
		*val >>= chan->scan_type.shअगरt;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		reg = AD5764_REG_OFFSET(chan->address);
		ret = ad5764_पढ़ो(indio_dev, reg, val);
		अगर (ret < 0)
			वापस ret;
		*val = sign_extend32(*val, 7);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_CALIBSCALE:
		reg = AD5764_REG_FINE_GAIN(chan->address);
		ret = ad5764_पढ़ो(indio_dev, reg, val);
		अगर (ret < 0)
			वापस ret;
		*val = sign_extend32(*val, 5);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		/* vout = 4 * vref + ((dac_code / 65536) - 0.5) */
		vref = ad5764_get_channel_vref(st, chan->channel);
		अगर (vref < 0)
			वापस vref;

		*val = vref * 4 / 1000;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	हाल IIO_CHAN_INFO_OFFSET:
		*val = -(1 << chan->scan_type.realbits) / 2;
		वापस IIO_VAL_INT;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info ad5764_info = अणु
	.पढ़ो_raw = ad5764_पढ़ो_raw,
	.ग_लिखो_raw = ad5764_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक ad5764_probe(काष्ठा spi_device *spi)
अणु
	क्रमागत ad5764_type type = spi_get_device_id(spi)->driver_data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा ad5764_state *st;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (indio_dev == शून्य) अणु
		dev_err(&spi->dev, "Failed to allocate iio device\n");
		वापस -ENOMEM;
	पूर्ण

	st = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);

	st->spi = spi;
	st->chip_info = &ad5764_chip_infos[type];

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad5764_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->num_channels = AD5764_NUM_CHANNELS;
	indio_dev->channels = st->chip_info->channels;

	mutex_init(&st->lock);

	अगर (st->chip_info->पूर्णांक_vref == 0) अणु
		st->vref_reg[0].supply = "vrefAB";
		st->vref_reg[1].supply = "vrefCD";

		ret = devm_regulator_bulk_get(&st->spi->dev,
			ARRAY_SIZE(st->vref_reg), st->vref_reg);
		अगर (ret) अणु
			dev_err(&spi->dev, "Failed to request vref regulators: %d\n",
				ret);
			वापस ret;
		पूर्ण

		ret = regulator_bulk_enable(ARRAY_SIZE(st->vref_reg),
			st->vref_reg);
		अगर (ret) अणु
			dev_err(&spi->dev, "Failed to enable vref regulators: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to register iio device: %d\n", ret);
		जाओ error_disable_reg;
	पूर्ण

	वापस 0;

error_disable_reg:
	अगर (st->chip_info->पूर्णांक_vref == 0)
		regulator_bulk_disable(ARRAY_SIZE(st->vref_reg), st->vref_reg);
	वापस ret;
पूर्ण

अटल पूर्णांक ad5764_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ad5764_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	अगर (st->chip_info->पूर्णांक_vref == 0)
		regulator_bulk_disable(ARRAY_SIZE(st->vref_reg), st->vref_reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad5764_ids[] = अणु
	अणु "ad5744", ID_AD5744 पूर्ण,
	अणु "ad5744r", ID_AD5744R पूर्ण,
	अणु "ad5764", ID_AD5764 पूर्ण,
	अणु "ad5764r", ID_AD5764R पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad5764_ids);

अटल काष्ठा spi_driver ad5764_driver = अणु
	.driver = अणु
		.name = "ad5764",
	पूर्ण,
	.probe = ad5764_probe,
	.हटाओ = ad5764_हटाओ,
	.id_table = ad5764_ids,
पूर्ण;
module_spi_driver(ad5764_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Analog Devices AD5744/AD5744R/AD5764/AD5764R DAC");
MODULE_LICENSE("GPL v2");
