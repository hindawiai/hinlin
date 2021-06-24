<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Analog devices AD5360, AD5361, AD5362, AD5363, AD5370, AD5371, AD5373
 * multi-channel Digital to Analog Converters driver
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

#घोषणा AD5360_CMD(x)				((x) << 22)
#घोषणा AD5360_ADDR(x)				((x) << 16)

#घोषणा AD5360_READBACK_TYPE(x)			((x) << 13)
#घोषणा AD5360_READBACK_ADDR(x)			((x) << 7)

#घोषणा AD5360_CHAN_ADDR(chan)			((chan) + 0x8)

#घोषणा AD5360_CMD_WRITE_DATA			0x3
#घोषणा AD5360_CMD_WRITE_OFFSET			0x2
#घोषणा AD5360_CMD_WRITE_GAIN			0x1
#घोषणा AD5360_CMD_SPECIAL_FUNCTION		0x0

/* Special function रेजिस्टर addresses */
#घोषणा AD5360_REG_SF_NOP			0x0
#घोषणा AD5360_REG_SF_CTRL			0x1
#घोषणा AD5360_REG_SF_OFS(x)			(0x2 + (x))
#घोषणा AD5360_REG_SF_READBACK			0x5

#घोषणा AD5360_SF_CTRL_PWR_DOWN			BIT(0)

#घोषणा AD5360_READBACK_X1A			0x0
#घोषणा AD5360_READBACK_X1B			0x1
#घोषणा AD5360_READBACK_OFFSET			0x2
#घोषणा AD5360_READBACK_GAIN			0x3
#घोषणा AD5360_READBACK_SF			0x4


/**
 * काष्ठा ad5360_chip_info - chip specअगरic inक्रमmation
 * @channel_ढाँचा:	channel specअगरication ढाँचा
 * @num_channels:	number of channels
 * @channels_per_group:	number of channels per group
 * @num_vrefs:		number of vref supplies क्रम the chip
*/

काष्ठा ad5360_chip_info अणु
	काष्ठा iio_chan_spec	channel_ढाँचा;
	अचिन्हित पूर्णांक		num_channels;
	अचिन्हित पूर्णांक		channels_per_group;
	अचिन्हित पूर्णांक		num_vrefs;
पूर्ण;

/**
 * काष्ठा ad5360_state - driver instance specअगरic data
 * @spi:		spi_device
 * @chip_info:		chip model specअगरic स्थिरants, available modes etc
 * @vref_reg:		vref supply regulators
 * @ctrl:		control रेजिस्टर cache
 * @lock:		lock to protect the data buffer during SPI ops
 * @data:		spi transfer buffers
 */

काष्ठा ad5360_state अणु
	काष्ठा spi_device		*spi;
	स्थिर काष्ठा ad5360_chip_info	*chip_info;
	काष्ठा regulator_bulk_data	vref_reg[3];
	अचिन्हित पूर्णांक			ctrl;
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

क्रमागत ad5360_type अणु
	ID_AD5360,
	ID_AD5361,
	ID_AD5362,
	ID_AD5363,
	ID_AD5370,
	ID_AD5371,
	ID_AD5372,
	ID_AD5373,
पूर्ण;

#घोषणा AD5360_CHANNEL(bits) अणु					\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.output = 1,						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |		\
		BIT(IIO_CHAN_INFO_SCALE) |				\
		BIT(IIO_CHAN_INFO_OFFSET) |				\
		BIT(IIO_CHAN_INFO_CALIBSCALE) |			\
		BIT(IIO_CHAN_INFO_CALIBBIAS),			\
	.scan_type = अणु						\
		.sign = 'u',					\
		.realbits = (bits),				\
		.storagebits = 16,				\
		.shअगरt = 16 - (bits),				\
	पूर्ण,							\
पूर्ण

अटल स्थिर काष्ठा ad5360_chip_info ad5360_chip_info_tbl[] = अणु
	[ID_AD5360] = अणु
		.channel_ढाँचा = AD5360_CHANNEL(16),
		.num_channels = 16,
		.channels_per_group = 8,
		.num_vrefs = 2,
	पूर्ण,
	[ID_AD5361] = अणु
		.channel_ढाँचा = AD5360_CHANNEL(14),
		.num_channels = 16,
		.channels_per_group = 8,
		.num_vrefs = 2,
	पूर्ण,
	[ID_AD5362] = अणु
		.channel_ढाँचा = AD5360_CHANNEL(16),
		.num_channels = 8,
		.channels_per_group = 4,
		.num_vrefs = 2,
	पूर्ण,
	[ID_AD5363] = अणु
		.channel_ढाँचा = AD5360_CHANNEL(14),
		.num_channels = 8,
		.channels_per_group = 4,
		.num_vrefs = 2,
	पूर्ण,
	[ID_AD5370] = अणु
		.channel_ढाँचा = AD5360_CHANNEL(16),
		.num_channels = 40,
		.channels_per_group = 8,
		.num_vrefs = 2,
	पूर्ण,
	[ID_AD5371] = अणु
		.channel_ढाँचा = AD5360_CHANNEL(14),
		.num_channels = 40,
		.channels_per_group = 8,
		.num_vrefs = 3,
	पूर्ण,
	[ID_AD5372] = अणु
		.channel_ढाँचा = AD5360_CHANNEL(16),
		.num_channels = 32,
		.channels_per_group = 8,
		.num_vrefs = 2,
	पूर्ण,
	[ID_AD5373] = अणु
		.channel_ढाँचा = AD5360_CHANNEL(14),
		.num_channels = 32,
		.channels_per_group = 8,
		.num_vrefs = 2,
	पूर्ण,
पूर्ण;

अटल अचिन्हित पूर्णांक ad5360_get_channel_vref_index(काष्ठा ad5360_state *st,
	अचिन्हित पूर्णांक channel)
अणु
	अचिन्हित पूर्णांक i;

	/* The first groups have their own vref, जबतक the reमुख्यing groups
	 * share the last vref */
	i = channel / st->chip_info->channels_per_group;
	अगर (i >= st->chip_info->num_vrefs)
		i = st->chip_info->num_vrefs - 1;

	वापस i;
पूर्ण

अटल पूर्णांक ad5360_get_channel_vref(काष्ठा ad5360_state *st,
	अचिन्हित पूर्णांक channel)
अणु
	अचिन्हित पूर्णांक i = ad5360_get_channel_vref_index(st, channel);

	वापस regulator_get_voltage(st->vref_reg[i].consumer);
पूर्ण


अटल पूर्णांक ad5360_ग_लिखो_unlocked(काष्ठा iio_dev *indio_dev,
	अचिन्हित पूर्णांक cmd, अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक val,
	अचिन्हित पूर्णांक shअगरt)
अणु
	काष्ठा ad5360_state *st = iio_priv(indio_dev);

	val <<= shअगरt;
	val |= AD5360_CMD(cmd) | AD5360_ADDR(addr);
	st->data[0].d32 = cpu_to_be32(val);

	वापस spi_ग_लिखो(st->spi, &st->data[0].d8[1], 3);
पूर्ण

अटल पूर्णांक ad5360_ग_लिखो(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक cmd,
	अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक shअगरt)
अणु
	पूर्णांक ret;
	काष्ठा ad5360_state *st = iio_priv(indio_dev);

	mutex_lock(&st->lock);
	ret = ad5360_ग_लिखो_unlocked(indio_dev, cmd, addr, val, shअगरt);
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5360_पढ़ो(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक type,
	अचिन्हित पूर्णांक addr)
अणु
	काष्ठा ad5360_state *st = iio_priv(indio_dev);
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

	st->data[0].d32 = cpu_to_be32(AD5360_CMD(AD5360_CMD_SPECIAL_FUNCTION) |
		AD5360_ADDR(AD5360_REG_SF_READBACK) |
		AD5360_READBACK_TYPE(type) |
		AD5360_READBACK_ADDR(addr));

	ret = spi_sync_transfer(st->spi, t, ARRAY_SIZE(t));
	अगर (ret >= 0)
		ret = be32_to_cpu(st->data[1].d32) & 0xffff;

	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ad5360_पढ़ो_dac_घातerकरोwn(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	काष्ठा ad5360_state *st = iio_priv(indio_dev);

	वापस sysfs_emit(buf, "%d\n", (bool)(st->ctrl & AD5360_SF_CTRL_PWR_DOWN));
पूर्ण

अटल पूर्णांक ad5360_update_ctrl(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक set,
	अचिन्हित पूर्णांक clr)
अणु
	काष्ठा ad5360_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक ret;

	mutex_lock(&st->lock);

	st->ctrl |= set;
	st->ctrl &= ~clr;

	ret = ad5360_ग_लिखो_unlocked(indio_dev, AD5360_CMD_SPECIAL_FUNCTION,
			AD5360_REG_SF_CTRL, st->ctrl, 0);

	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार ad5360_ग_लिखो_dac_घातerकरोwn(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा iio_dev *indio_dev = dev_to_iio_dev(dev);
	bool pwr_करोwn;
	पूर्णांक ret;

	ret = strtobool(buf, &pwr_करोwn);
	अगर (ret)
		वापस ret;

	अगर (pwr_करोwn)
		ret = ad5360_update_ctrl(indio_dev, AD5360_SF_CTRL_PWR_DOWN, 0);
	अन्यथा
		ret = ad5360_update_ctrl(indio_dev, 0, AD5360_SF_CTRL_PWR_DOWN);

	वापस ret ? ret : len;
पूर्ण

अटल IIO_DEVICE_ATTR(out_voltage_घातerकरोwn,
			S_IRUGO | S_IWUSR,
			ad5360_पढ़ो_dac_घातerकरोwn,
			ad5360_ग_लिखो_dac_घातerकरोwn, 0);

अटल काष्ठा attribute *ad5360_attributes[] = अणु
	&iio_dev_attr_out_voltage_घातerकरोwn.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ad5360_attribute_group = अणु
	.attrs = ad5360_attributes,
पूर्ण;

अटल पूर्णांक ad5360_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			       काष्ठा iio_chan_spec स्थिर *chan,
			       पूर्णांक val,
			       पूर्णांक val2,
			       दीर्घ mask)
अणु
	काष्ठा ad5360_state *st = iio_priv(indio_dev);
	पूर्णांक max_val = (1 << chan->scan_type.realbits);
	अचिन्हित पूर्णांक ofs_index;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (val >= max_val || val < 0)
			वापस -EINVAL;

		वापस ad5360_ग_लिखो(indio_dev, AD5360_CMD_WRITE_DATA,
				 chan->address, val, chan->scan_type.shअगरt);

	हाल IIO_CHAN_INFO_CALIBBIAS:
		अगर (val >= max_val || val < 0)
			वापस -EINVAL;

		वापस ad5360_ग_लिखो(indio_dev, AD5360_CMD_WRITE_OFFSET,
				 chan->address, val, chan->scan_type.shअगरt);

	हाल IIO_CHAN_INFO_CALIBSCALE:
		अगर (val >= max_val || val < 0)
			वापस -EINVAL;

		वापस ad5360_ग_लिखो(indio_dev, AD5360_CMD_WRITE_GAIN,
				 chan->address, val, chan->scan_type.shअगरt);

	हाल IIO_CHAN_INFO_OFFSET:
		अगर (val <= -max_val || val > 0)
			वापस -EINVAL;

		val = -val;

		/* offset is supposed to have the same scale as raw, but it
		 * is always 14bits wide, so on a chip where the raw value has
		 * more bits, we need to shअगरt offset. */
		val >>= (chan->scan_type.realbits - 14);

		/* There is one DAC offset रेजिस्टर per vref. Changing one
		 * channels offset will also change the offset क्रम all other
		 * channels which share the same vref supply. */
		ofs_index = ad5360_get_channel_vref_index(st, chan->channel);
		वापस ad5360_ग_लिखो(indio_dev, AD5360_CMD_SPECIAL_FUNCTION,
				 AD5360_REG_SF_OFS(ofs_index), val, 0);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad5360_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	काष्ठा ad5360_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक ofs_index;
	पूर्णांक scale_uv;
	पूर्णांक ret;

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = ad5360_पढ़ो(indio_dev, AD5360_READBACK_X1A,
			chan->address);
		अगर (ret < 0)
			वापस ret;
		*val = ret >> chan->scan_type.shअगरt;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		scale_uv = ad5360_get_channel_vref(st, chan->channel);
		अगर (scale_uv < 0)
			वापस scale_uv;

		/* vout = 4 * vref * dac_code */
		*val = scale_uv * 4 / 1000;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		ret = ad5360_पढ़ो(indio_dev, AD5360_READBACK_OFFSET,
			chan->address);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_CALIBSCALE:
		ret = ad5360_पढ़ो(indio_dev, AD5360_READBACK_GAIN,
			chan->address);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_OFFSET:
		ofs_index = ad5360_get_channel_vref_index(st, chan->channel);
		ret = ad5360_पढ़ो(indio_dev, AD5360_READBACK_SF,
			AD5360_REG_SF_OFS(ofs_index));
		अगर (ret < 0)
			वापस ret;

		ret <<= (chan->scan_type.realbits - 14);
		*val = -ret;
		वापस IIO_VAL_INT;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info ad5360_info = अणु
	.पढ़ो_raw = ad5360_पढ़ो_raw,
	.ग_लिखो_raw = ad5360_ग_लिखो_raw,
	.attrs = &ad5360_attribute_group,
पूर्ण;

अटल स्थिर अक्षर * स्थिर ad5360_vref_name[] = अणु
	 "vref0", "vref1", "vref2"
पूर्ण;

अटल पूर्णांक ad5360_alloc_channels(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad5360_state *st = iio_priv(indio_dev);
	काष्ठा iio_chan_spec *channels;
	अचिन्हित पूर्णांक i;

	channels = kसुस्मृति(st->chip_info->num_channels,
			   माप(काष्ठा iio_chan_spec), GFP_KERNEL);

	अगर (!channels)
		वापस -ENOMEM;

	क्रम (i = 0; i < st->chip_info->num_channels; ++i) अणु
		channels[i] = st->chip_info->channel_ढाँचा;
		channels[i].channel = i;
		channels[i].address = AD5360_CHAN_ADDR(i);
	पूर्ण

	indio_dev->channels = channels;

	वापस 0;
पूर्ण

अटल पूर्णांक ad5360_probe(काष्ठा spi_device *spi)
अणु
	क्रमागत ad5360_type type = spi_get_device_id(spi)->driver_data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा ad5360_state *st;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (indio_dev == शून्य) अणु
		dev_err(&spi->dev, "Failed to allocate iio device\n");
		वापस  -ENOMEM;
	पूर्ण

	st = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);

	st->chip_info = &ad5360_chip_info_tbl[type];
	st->spi = spi;

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad5360_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->num_channels = st->chip_info->num_channels;

	mutex_init(&st->lock);

	ret = ad5360_alloc_channels(indio_dev);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to allocate channel spec: %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < st->chip_info->num_vrefs; ++i)
		st->vref_reg[i].supply = ad5360_vref_name[i];

	ret = devm_regulator_bulk_get(&st->spi->dev, st->chip_info->num_vrefs,
		st->vref_reg);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to request vref regulators: %d\n", ret);
		जाओ error_मुक्त_channels;
	पूर्ण

	ret = regulator_bulk_enable(st->chip_info->num_vrefs, st->vref_reg);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to enable vref regulators: %d\n", ret);
		जाओ error_मुक्त_channels;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&spi->dev, "Failed to register iio device: %d\n", ret);
		जाओ error_disable_reg;
	पूर्ण

	वापस 0;

error_disable_reg:
	regulator_bulk_disable(st->chip_info->num_vrefs, st->vref_reg);
error_मुक्त_channels:
	kमुक्त(indio_dev->channels);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5360_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ad5360_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	kमुक्त(indio_dev->channels);

	regulator_bulk_disable(st->chip_info->num_vrefs, st->vref_reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad5360_ids[] = अणु
	अणु "ad5360", ID_AD5360 पूर्ण,
	अणु "ad5361", ID_AD5361 पूर्ण,
	अणु "ad5362", ID_AD5362 पूर्ण,
	अणु "ad5363", ID_AD5363 पूर्ण,
	अणु "ad5370", ID_AD5370 पूर्ण,
	अणु "ad5371", ID_AD5371 पूर्ण,
	अणु "ad5372", ID_AD5372 पूर्ण,
	अणु "ad5373", ID_AD5373 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad5360_ids);

अटल काष्ठा spi_driver ad5360_driver = अणु
	.driver = अणु
		   .name = "ad5360",
	पूर्ण,
	.probe = ad5360_probe,
	.हटाओ = ad5360_हटाओ,
	.id_table = ad5360_ids,
पूर्ण;
module_spi_driver(ad5360_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Analog Devices AD5360/61/62/63/70/71/72/73 DAC");
MODULE_LICENSE("GPL v2");
