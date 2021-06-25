<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2015 Prevas A/S
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/sysfs.h>

#घोषणा ADS8688_CMD_REG(x)		(x << 8)
#घोषणा ADS8688_CMD_REG_NOOP		0x00
#घोषणा ADS8688_CMD_REG_RST		0x85
#घोषणा ADS8688_CMD_REG_MAN_CH(chan)	(0xC0 | (4 * chan))
#घोषणा ADS8688_CMD_DONT_CARE_BITS	16

#घोषणा ADS8688_PROG_REG(x)		(x << 9)
#घोषणा ADS8688_PROG_REG_RANGE_CH(chan)	(0x05 + chan)
#घोषणा ADS8688_PROG_WR_BIT		BIT(8)
#घोषणा ADS8688_PROG_DONT_CARE_BITS	8

#घोषणा ADS8688_REG_PLUSMINUS25VREF	0
#घोषणा ADS8688_REG_PLUSMINUS125VREF	1
#घोषणा ADS8688_REG_PLUSMINUS0625VREF	2
#घोषणा ADS8688_REG_PLUS25VREF		5
#घोषणा ADS8688_REG_PLUS125VREF		6

#घोषणा ADS8688_VREF_MV			4096
#घोषणा ADS8688_REALBITS		16
#घोषणा ADS8688_MAX_CHANNELS		8

/*
 * क्रमागत ads8688_range - ADS8688 reference voltage range
 * @ADS8688_PLUSMINUS25VREF: Device is configured क्रम input range तऔ2.5 * VREF
 * @ADS8688_PLUSMINUS125VREF: Device is configured क्रम input range तऔ1.25 * VREF
 * @ADS8688_PLUSMINUS0625VREF: Device is configured क्रम input range तऔ0.625 * VREF
 * @ADS8688_PLUS25VREF: Device is configured क्रम input range 0 - 2.5 * VREF
 * @ADS8688_PLUS125VREF: Device is configured क्रम input range 0 - 1.25 * VREF
 */
क्रमागत ads8688_range अणु
	ADS8688_PLUSMINUS25VREF,
	ADS8688_PLUSMINUS125VREF,
	ADS8688_PLUSMINUS0625VREF,
	ADS8688_PLUS25VREF,
	ADS8688_PLUS125VREF,
पूर्ण;

काष्ठा ads8688_chip_info अणु
	स्थिर काष्ठा iio_chan_spec *channels;
	अचिन्हित पूर्णांक num_channels;
पूर्ण;

काष्ठा ads8688_state अणु
	काष्ठा mutex			lock;
	स्थिर काष्ठा ads8688_chip_info	*chip_info;
	काष्ठा spi_device		*spi;
	काष्ठा regulator		*reg;
	अचिन्हित पूर्णांक			vref_mv;
	क्रमागत ads8688_range		range[8];
	जोड़ अणु
		__be32 d32;
		u8 d8[4];
	पूर्ण data[2] ____cacheline_aligned;
पूर्ण;

क्रमागत ads8688_id अणु
	ID_ADS8684,
	ID_ADS8688,
पूर्ण;

काष्ठा ads8688_ranges अणु
	क्रमागत ads8688_range range;
	अचिन्हित पूर्णांक scale;
	पूर्णांक offset;
	u8 reg;
पूर्ण;

अटल स्थिर काष्ठा ads8688_ranges ads8688_range_def[5] = अणु
	अणु
		.range = ADS8688_PLUSMINUS25VREF,
		.scale = 76295,
		.offset = -(1 << (ADS8688_REALBITS - 1)),
		.reg = ADS8688_REG_PLUSMINUS25VREF,
	पूर्ण, अणु
		.range = ADS8688_PLUSMINUS125VREF,
		.scale = 38148,
		.offset = -(1 << (ADS8688_REALBITS - 1)),
		.reg = ADS8688_REG_PLUSMINUS125VREF,
	पूर्ण, अणु
		.range = ADS8688_PLUSMINUS0625VREF,
		.scale = 19074,
		.offset = -(1 << (ADS8688_REALBITS - 1)),
		.reg = ADS8688_REG_PLUSMINUS0625VREF,
	पूर्ण, अणु
		.range = ADS8688_PLUS25VREF,
		.scale = 38148,
		.offset = 0,
		.reg = ADS8688_REG_PLUS25VREF,
	पूर्ण, अणु
		.range = ADS8688_PLUS125VREF,
		.scale = 19074,
		.offset = 0,
		.reg = ADS8688_REG_PLUS125VREF,
	पूर्ण
पूर्ण;

अटल sमाप_प्रकार ads8688_show_scales(काष्ठा device *dev,
				   काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा ads8688_state *st = iio_priv(dev_to_iio_dev(dev));

	वापस प्र_लिखो(buf, "0.%09u 0.%09u 0.%09u\n",
		       ads8688_range_def[0].scale * st->vref_mv,
		       ads8688_range_def[1].scale * st->vref_mv,
		       ads8688_range_def[2].scale * st->vref_mv);
पूर्ण

अटल sमाप_प्रकार ads8688_show_offsets(काष्ठा device *dev,
				    काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस प्र_लिखो(buf, "%d %d\n", ads8688_range_def[0].offset,
		       ads8688_range_def[3].offset);
पूर्ण

अटल IIO_DEVICE_ATTR(in_voltage_scale_available, S_IRUGO,
		       ads8688_show_scales, शून्य, 0);
अटल IIO_DEVICE_ATTR(in_voltage_offset_available, S_IRUGO,
		       ads8688_show_offsets, शून्य, 0);

अटल काष्ठा attribute *ads8688_attributes[] = अणु
	&iio_dev_attr_in_voltage_scale_available.dev_attr.attr,
	&iio_dev_attr_in_voltage_offset_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group ads8688_attribute_group = अणु
	.attrs = ads8688_attributes,
पूर्ण;

#घोषणा ADS8688_CHAN(index)					\
अणु								\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.channel = index,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW)		\
			      | BIT(IIO_CHAN_INFO_SCALE)	\
			      | BIT(IIO_CHAN_INFO_OFFSET),	\
	.scan_index = index,					\
	.scan_type = अणु						\
		.sign = 'u',					\
		.realbits = 16,					\
		.storagebits = 16,				\
		.endianness = IIO_BE,				\
	पूर्ण,							\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ads8684_channels[] = अणु
	ADS8688_CHAN(0),
	ADS8688_CHAN(1),
	ADS8688_CHAN(2),
	ADS8688_CHAN(3),
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec ads8688_channels[] = अणु
	ADS8688_CHAN(0),
	ADS8688_CHAN(1),
	ADS8688_CHAN(2),
	ADS8688_CHAN(3),
	ADS8688_CHAN(4),
	ADS8688_CHAN(5),
	ADS8688_CHAN(6),
	ADS8688_CHAN(7),
पूर्ण;

अटल पूर्णांक ads8688_prog_ग_लिखो(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक addr,
			      अचिन्हित पूर्णांक val)
अणु
	काष्ठा ads8688_state *st = iio_priv(indio_dev);
	u32 पंचांगp;

	पंचांगp = ADS8688_PROG_REG(addr) | ADS8688_PROG_WR_BIT | val;
	पंचांगp <<= ADS8688_PROG_DONT_CARE_BITS;
	st->data[0].d32 = cpu_to_be32(पंचांगp);

	वापस spi_ग_लिखो(st->spi, &st->data[0].d8[1], 3);
पूर्ण

अटल पूर्णांक ads8688_reset(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ads8688_state *st = iio_priv(indio_dev);
	u32 पंचांगp;

	पंचांगp = ADS8688_CMD_REG(ADS8688_CMD_REG_RST);
	पंचांगp <<= ADS8688_CMD_DONT_CARE_BITS;
	st->data[0].d32 = cpu_to_be32(पंचांगp);

	वापस spi_ग_लिखो(st->spi, &st->data[0].d8[0], 4);
पूर्ण

अटल पूर्णांक ads8688_पढ़ो(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक chan)
अणु
	काष्ठा ads8688_state *st = iio_priv(indio_dev);
	पूर्णांक ret;
	u32 पंचांगp;
	काष्ठा spi_transfer t[] = अणु
		अणु
			.tx_buf = &st->data[0].d8[0],
			.len = 4,
			.cs_change = 1,
		पूर्ण, अणु
			.tx_buf = &st->data[1].d8[0],
			.rx_buf = &st->data[1].d8[0],
			.len = 4,
		पूर्ण,
	पूर्ण;

	पंचांगp = ADS8688_CMD_REG(ADS8688_CMD_REG_MAN_CH(chan));
	पंचांगp <<= ADS8688_CMD_DONT_CARE_BITS;
	st->data[0].d32 = cpu_to_be32(पंचांगp);

	पंचांगp = ADS8688_CMD_REG(ADS8688_CMD_REG_NOOP);
	पंचांगp <<= ADS8688_CMD_DONT_CARE_BITS;
	st->data[1].d32 = cpu_to_be32(पंचांगp);

	ret = spi_sync_transfer(st->spi, t, ARRAY_SIZE(t));
	अगर (ret < 0)
		वापस ret;

	वापस be32_to_cpu(st->data[1].d32) & 0xffff;
पूर्ण

अटल पूर्णांक ads8688_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ m)
अणु
	पूर्णांक ret, offset;
	अचिन्हित दीर्घ scale_mv;

	काष्ठा ads8688_state *st = iio_priv(indio_dev);

	mutex_lock(&st->lock);
	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = ads8688_पढ़ो(indio_dev, chan->channel);
		mutex_unlock(&st->lock);
		अगर (ret < 0)
			वापस ret;
		*val = ret;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		scale_mv = st->vref_mv;
		scale_mv *= ads8688_range_def[st->range[chan->channel]].scale;
		*val = 0;
		*val2 = scale_mv;
		mutex_unlock(&st->lock);
		वापस IIO_VAL_INT_PLUS_न_अंकO;
	हाल IIO_CHAN_INFO_OFFSET:
		offset = ads8688_range_def[st->range[chan->channel]].offset;
		*val = offset;
		mutex_unlock(&st->lock);
		वापस IIO_VAL_INT;
	पूर्ण
	mutex_unlock(&st->lock);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ads8688_ग_लिखो_reg_range(काष्ठा iio_dev *indio_dev,
				   काष्ठा iio_chan_spec स्थिर *chan,
				   क्रमागत ads8688_range range)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक ret;

	पंचांगp = ADS8688_PROG_REG_RANGE_CH(chan->channel);
	ret = ads8688_prog_ग_लिखो(indio_dev, पंचांगp, range);

	वापस ret;
पूर्ण

अटल पूर्णांक ads8688_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा ads8688_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक scale = 0;
	पूर्णांक ret = -EINVAL, i, offset = 0;

	mutex_lock(&st->lock);
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		/* If the offset is 0 the तऔ2.5 * VREF mode is not available */
		offset = ads8688_range_def[st->range[chan->channel]].offset;
		अगर (offset == 0 && val2 == ads8688_range_def[0].scale * st->vref_mv) अणु
			mutex_unlock(&st->lock);
			वापस -EINVAL;
		पूर्ण

		/* Lookup new mode */
		क्रम (i = 0; i < ARRAY_SIZE(ads8688_range_def); i++)
			अगर (val2 == ads8688_range_def[i].scale * st->vref_mv &&
			    offset == ads8688_range_def[i].offset) अणु
				ret = ads8688_ग_लिखो_reg_range(indio_dev, chan,
					ads8688_range_def[i].reg);
				अवरोध;
			पूर्ण
		अवरोध;
	हाल IIO_CHAN_INFO_OFFSET:
		/*
		 * There are only two available offsets:
		 * 0 and -(1 << (ADS8688_REALBITS - 1))
		 */
		अगर (!(ads8688_range_def[0].offset == val ||
		    ads8688_range_def[3].offset == val)) अणु
			mutex_unlock(&st->lock);
			वापस -EINVAL;
		पूर्ण

		/*
		 * If the device are in तऔ2.5 * VREF mode, it's not allowed to
		 * चयन to a mode where the offset is 0
		 */
		अगर (val == 0 &&
		    st->range[chan->channel] == ADS8688_PLUSMINUS25VREF) अणु
			mutex_unlock(&st->lock);
			वापस -EINVAL;
		पूर्ण

		scale = ads8688_range_def[st->range[chan->channel]].scale;

		/* Lookup new mode */
		क्रम (i = 0; i < ARRAY_SIZE(ads8688_range_def); i++)
			अगर (val == ads8688_range_def[i].offset &&
			    scale == ads8688_range_def[i].scale) अणु
				ret = ads8688_ग_लिखो_reg_range(indio_dev, chan,
					ads8688_range_def[i].reg);
				अवरोध;
			पूर्ण
		अवरोध;
	पूर्ण

	अगर (!ret)
		st->range[chan->channel] = ads8688_range_def[i].range;

	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ads8688_ग_लिखो_raw_get_fmt(काष्ठा iio_dev *indio_dev,
				     काष्ठा iio_chan_spec स्थिर *chan,
				     दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		वापस IIO_VAL_INT_PLUS_न_अंकO;
	हाल IIO_CHAN_INFO_OFFSET:
		वापस IIO_VAL_INT;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info ads8688_info = अणु
	.पढ़ो_raw = &ads8688_पढ़ो_raw,
	.ग_लिखो_raw = &ads8688_ग_लिखो_raw,
	.ग_लिखो_raw_get_fmt = &ads8688_ग_लिखो_raw_get_fmt,
	.attrs = &ads8688_attribute_group,
पूर्ण;

अटल irqवापस_t ads8688_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	u16 buffer[ADS8688_MAX_CHANNELS + माप(s64)/माप(u16)];
	पूर्णांक i, j = 0;

	क्रम (i = 0; i < indio_dev->masklength; i++) अणु
		अगर (!test_bit(i, indio_dev->active_scan_mask))
			जारी;
		buffer[j] = ads8688_पढ़ो(indio_dev, i);
		j++;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev, buffer,
			iio_get_समय_ns(indio_dev));

	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा ads8688_chip_info ads8688_chip_info_tbl[] = अणु
	[ID_ADS8684] = अणु
		.channels = ads8684_channels,
		.num_channels = ARRAY_SIZE(ads8684_channels),
	पूर्ण,
	[ID_ADS8688] = अणु
		.channels = ads8688_channels,
		.num_channels = ARRAY_SIZE(ads8688_channels),
	पूर्ण,
पूर्ण;

अटल पूर्णांक ads8688_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ads8688_state *st;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);

	st->reg = devm_regulator_get_optional(&spi->dev, "vref");
	अगर (!IS_ERR(st->reg)) अणु
		ret = regulator_enable(st->reg);
		अगर (ret)
			वापस ret;

		ret = regulator_get_voltage(st->reg);
		अगर (ret < 0)
			जाओ err_regulator_disable;

		st->vref_mv = ret / 1000;
	पूर्ण अन्यथा अणु
		/* Use पूर्णांकernal reference */
		st->vref_mv = ADS8688_VREF_MV;
	पूर्ण

	st->chip_info =	&ads8688_chip_info_tbl[spi_get_device_id(spi)->driver_data];

	spi->mode = SPI_MODE_1;

	spi_set_drvdata(spi, indio_dev);

	st->spi = spi;

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = st->chip_info->channels;
	indio_dev->num_channels = st->chip_info->num_channels;
	indio_dev->info = &ads8688_info;

	ads8688_reset(indio_dev);

	mutex_init(&st->lock);

	ret = iio_triggered_buffer_setup(indio_dev, शून्य, ads8688_trigger_handler, शून्य);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "iio triggered buffer setup failed\n");
		जाओ err_regulator_disable;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ err_buffer_cleanup;

	वापस 0;

err_buffer_cleanup:
	iio_triggered_buffer_cleanup(indio_dev);

err_regulator_disable:
	अगर (!IS_ERR(st->reg))
		regulator_disable(st->reg);

	वापस ret;
पूर्ण

अटल पूर्णांक ads8688_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ads8688_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);

	अगर (!IS_ERR(st->reg))
		regulator_disable(st->reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id ads8688_id[] = अणु
	अणु"ads8684", ID_ADS8684पूर्ण,
	अणु"ads8688", ID_ADS8688पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ads8688_id);

अटल स्थिर काष्ठा of_device_id ads8688_of_match[] = अणु
	अणु .compatible = "ti,ads8684" पूर्ण,
	अणु .compatible = "ti,ads8688" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ads8688_of_match);

अटल काष्ठा spi_driver ads8688_driver = अणु
	.driver = अणु
		.name	= "ads8688",
	पूर्ण,
	.probe		= ads8688_probe,
	.हटाओ		= ads8688_हटाओ,
	.id_table	= ads8688_id,
पूर्ण;
module_spi_driver(ads8688_driver);

MODULE_AUTHOR("Sean Nyekjaer <sean@geanix.dk>");
MODULE_DESCRIPTION("Texas Instruments ADS8688 driver");
MODULE_LICENSE("GPL v2");
