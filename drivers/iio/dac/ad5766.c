<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Analog Devices AD5766, AD5767
 * Digital to Analog Converters driver
 * Copyright 2019-2020 Analog Devices Inc.
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <यंत्र/unaligned.h>

#घोषणा AD5766_UPPER_WORD_SPI_MASK		GENMASK(31, 16)
#घोषणा AD5766_LOWER_WORD_SPI_MASK		GENMASK(15, 0)
#घोषणा AD5766_DITHER_SOURCE_MASK(ch)		GENMASK(((2 * ch) + 1), (2 * ch))
#घोषणा AD5766_DITHER_SOURCE(ch, source)	BIT((ch * 2) + source)
#घोषणा AD5766_DITHER_SCALE_MASK(x)		AD5766_DITHER_SOURCE_MASK(x)
#घोषणा AD5766_DITHER_SCALE(ch, scale)		(scale << (ch * 2))
#घोषणा AD5766_DITHER_ENABLE_MASK(ch)		BIT(ch)
#घोषणा AD5766_DITHER_ENABLE(ch, state)		((!state) << ch)
#घोषणा AD5766_DITHER_INVERT_MASK(ch)		BIT(ch)
#घोषणा AD5766_DITHER_INVERT(ch, state)		(state << ch)

#घोषणा AD5766_CMD_NOP_MUX_OUT			0x00
#घोषणा AD5766_CMD_SDO_CNTRL			0x01
#घोषणा AD5766_CMD_WR_IN_REG(x)			(0x10 | ((x) & GENMASK(3, 0)))
#घोषणा AD5766_CMD_WR_DAC_REG(x)		(0x20 | ((x) & GENMASK(3, 0)))
#घोषणा AD5766_CMD_SW_LDAC			0x30
#घोषणा AD5766_CMD_SPAN_REG			0x40
#घोषणा AD5766_CMD_WR_PWR_DITHER		0x51
#घोषणा AD5766_CMD_WR_DAC_REG_ALL		0x60
#घोषणा AD5766_CMD_SW_FULL_RESET		0x70
#घोषणा AD5766_CMD_READBACK_REG(x)		(0x80 | ((x) & GENMASK(3, 0)))
#घोषणा AD5766_CMD_DITHER_SIG_1			0x90
#घोषणा AD5766_CMD_DITHER_SIG_2			0xA0
#घोषणा AD5766_CMD_INV_DITHER			0xB0
#घोषणा AD5766_CMD_DITHER_SCALE_1		0xC0
#घोषणा AD5766_CMD_DITHER_SCALE_2		0xD0

#घोषणा AD5766_FULL_RESET_CODE			0x1234

क्रमागत ad5766_type अणु
	ID_AD5766,
	ID_AD5767,
पूर्ण;

क्रमागत ad5766_voltage_range अणु
	AD5766_VOLTAGE_RANGE_M20V_0V,
	AD5766_VOLTAGE_RANGE_M16V_to_0V,
	AD5766_VOLTAGE_RANGE_M10V_to_0V,
	AD5766_VOLTAGE_RANGE_M12V_to_14V,
	AD5766_VOLTAGE_RANGE_M16V_to_10V,
	AD5766_VOLTAGE_RANGE_M10V_to_6V,
	AD5766_VOLTAGE_RANGE_M5V_to_5V,
	AD5766_VOLTAGE_RANGE_M10V_to_10V,
पूर्ण;

/**
 * काष्ठा ad5766_chip_info - chip specअगरic inक्रमmation
 * @num_channels:	number of channels
 * @channels:	        channel specअगरication
 */
काष्ठा ad5766_chip_info अणु
	अचिन्हित पूर्णांक			num_channels;
	स्थिर काष्ठा iio_chan_spec	*channels;
पूर्ण;

क्रमागत अणु
	AD5766_DITHER_ENABLE,
	AD5766_DITHER_INVERT,
	AD5766_DITHER_SOURCE,
पूर्ण;

/*
 * Dither संकेत can also be scaled.
 * Available dither scale strings corresponding to "dither_scale" field in
 * "struct ad5766_state".
 */
अटल स्थिर अक्षर * स्थिर ad5766_dither_scales[] = अणु
	"1",
	"0.75",
	"0.5",
	"0.25",
पूर्ण;

/**
 * काष्ठा ad5766_state - driver instance specअगरic data
 * @spi:		SPI device
 * @lock:		Lock used to restrict concurrent access to SPI device
 * @chip_info:		Chip model specअगरic स्थिरants
 * @gpio_reset:		Reset GPIO, used to reset the device
 * @crt_range:		Current selected output range
 * @dither_enable:	Power enable bit क्रम each channel dither block (क्रम
 *			example, D15 = DAC 15,D8 = DAC 8, and D0 = DAC 0)
 *			0 - Normal operation, 1 - Power करोwn
 * @dither_invert:	Inverts the dither संकेत applied to the selected DAC
 *			outमाला_दो
 * @dither_source:	Selects between 2 possible sources:
 *			1: N0, 2: N1
 *			Two bits are used क्रम each channel
 * @dither_scale:	Two bits are used क्रम each of the 16 channels:
 *			0: 1 SCALING, 1: 0.75 SCALING, 2: 0.5 SCALING,
 *			3: 0.25 SCALING.
 * @data:		SPI transfer buffers
 */
काष्ठा ad5766_state अणु
	काष्ठा spi_device		*spi;
	काष्ठा mutex			lock;
	स्थिर काष्ठा ad5766_chip_info	*chip_info;
	काष्ठा gpio_desc		*gpio_reset;
	क्रमागत ad5766_voltage_range	crt_range;
	u16		dither_enable;
	u16		dither_invert;
	u32		dither_source;
	u32		dither_scale;
	जोड़ अणु
		u32	d32;
		u16	w16[2];
		u8	b8[4];
	पूर्ण data[3] ____cacheline_aligned;
पूर्ण;

काष्ठा ad5766_span_tbl अणु
	पूर्णांक		min;
	पूर्णांक		max;
पूर्ण;

अटल स्थिर काष्ठा ad5766_span_tbl ad5766_span_tbl[] = अणु
	[AD5766_VOLTAGE_RANGE_M20V_0V] =	अणु-20, 0पूर्ण,
	[AD5766_VOLTAGE_RANGE_M16V_to_0V] =	अणु-16, 0पूर्ण,
	[AD5766_VOLTAGE_RANGE_M10V_to_0V] =	अणु-10, 0पूर्ण,
	[AD5766_VOLTAGE_RANGE_M12V_to_14V] =	अणु-12, 14पूर्ण,
	[AD5766_VOLTAGE_RANGE_M16V_to_10V] =	अणु-16, 10पूर्ण,
	[AD5766_VOLTAGE_RANGE_M10V_to_6V] =	अणु-10, 6पूर्ण,
	[AD5766_VOLTAGE_RANGE_M5V_to_5V] =	अणु-5, 5पूर्ण,
	[AD5766_VOLTAGE_RANGE_M10V_to_10V] =	अणु-10, 10पूर्ण,
पूर्ण;

अटल पूर्णांक __ad5766_spi_पढ़ो(काष्ठा ad5766_state *st, u8 dac, पूर्णांक *val)
अणु
	पूर्णांक ret;
	काष्ठा spi_transfer xfers[] = अणु
		अणु
			.tx_buf = &st->data[0].d32,
			.bits_per_word = 8,
			.len = 3,
			.cs_change = 1,
		पूर्ण, अणु
			.tx_buf = &st->data[1].d32,
			.rx_buf = &st->data[2].d32,
			.bits_per_word = 8,
			.len = 3,
		पूर्ण,
	पूर्ण;

	st->data[0].d32 = AD5766_CMD_READBACK_REG(dac);
	st->data[1].d32 = AD5766_CMD_NOP_MUX_OUT;

	ret = spi_sync_transfer(st->spi, xfers, ARRAY_SIZE(xfers));
	अगर (ret)
		वापस ret;

	*val = st->data[2].w16[1];

	वापस ret;
पूर्ण

अटल पूर्णांक __ad5766_spi_ग_लिखो(काष्ठा ad5766_state *st, u8 command, u16 data)
अणु
	st->data[0].b8[0] = command;
	put_unaligned_be16(data, &st->data[0].b8[1]);

	वापस spi_ग_लिखो(st->spi, &st->data[0].b8[0], 3);
पूर्ण

अटल पूर्णांक ad5766_पढ़ो(काष्ठा iio_dev *indio_dev, u8 dac, पूर्णांक *val)
अणु
	काष्ठा ad5766_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);
	ret = __ad5766_spi_पढ़ो(st, dac, val);
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5766_ग_लिखो(काष्ठा iio_dev *indio_dev, u8 dac, u16 data)
अणु
	काष्ठा ad5766_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);
	ret = __ad5766_spi_ग_लिखो(st, AD5766_CMD_WR_DAC_REG(dac), data);
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5766_reset(काष्ठा ad5766_state *st)
अणु
	पूर्णांक ret;

	अगर (st->gpio_reset) अणु
		gpiod_set_value_cansleep(st->gpio_reset, 1);
		ndelay(100); /* t_reset >= 100ns */
		gpiod_set_value_cansleep(st->gpio_reset, 0);
	पूर्ण अन्यथा अणु
		ret = __ad5766_spi_ग_लिखो(st, AD5766_CMD_SW_FULL_RESET,
					AD5766_FULL_RESET_CODE);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/*
	 * Minimum समय between a reset and the subsequent successful ग_लिखो is
	 * typically 25 ns
	 */
	ndelay(25);

	वापस 0;
पूर्ण

अटल पूर्णांक ad5766_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	काष्ठा ad5766_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = ad5766_पढ़ो(indio_dev, chan->address, val);
		अगर (ret)
			वापस ret;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_OFFSET:
		*val = ad5766_span_tbl[st->crt_range].min;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = ad5766_span_tbl[st->crt_range].max -
		       ad5766_span_tbl[st->crt_range].min;
		*val2 = st->chip_info->channels[0].scan_type.realbits;

		वापस IIO_VAL_FRACTIONAL_LOG2;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ad5766_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val,
			    पूर्णांक val2,
			    दीर्घ info)
अणु
	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
	अणु
		स्थिर पूर्णांक max_val = GENMASK(chan->scan_type.realbits - 1, 0);

		अगर (val > max_val || val < 0)
			वापस -EINVAL;
		val <<= chan->scan_type.shअगरt;
		वापस ad5766_ग_लिखो(indio_dev, chan->address, val);
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info ad5766_info = अणु
	.पढ़ो_raw = ad5766_पढ़ो_raw,
	.ग_लिखो_raw = ad5766_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक ad5766_get_dither_source(काष्ठा iio_dev *dev,
				    स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा ad5766_state *st = iio_priv(dev);
	u32 source;

	source = st->dither_source & AD5766_DITHER_SOURCE_MASK(chan->channel);
	source = source >> (chan->channel * 2);
	source -= 1;

	वापस source;
पूर्ण

अटल पूर्णांक ad5766_set_dither_source(काष्ठा iio_dev *dev,
			  स्थिर काष्ठा iio_chan_spec *chan,
			  अचिन्हित पूर्णांक source)
अणु
	काष्ठा ad5766_state *st = iio_priv(dev);
	uपूर्णांक16_t val;
	पूर्णांक ret;

	st->dither_source &= ~AD5766_DITHER_SOURCE_MASK(chan->channel);
	st->dither_source |= AD5766_DITHER_SOURCE(chan->channel, source);

	val = FIELD_GET(AD5766_LOWER_WORD_SPI_MASK, st->dither_source);
	ret = ad5766_ग_लिखो(dev, AD5766_CMD_DITHER_SIG_1, val);
	अगर (ret)
		वापस ret;

	val = FIELD_GET(AD5766_UPPER_WORD_SPI_MASK, st->dither_source);

	वापस ad5766_ग_लिखो(dev, AD5766_CMD_DITHER_SIG_2, val);
पूर्ण

अटल पूर्णांक ad5766_get_dither_scale(काष्ठा iio_dev *dev,
				   स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा ad5766_state *st = iio_priv(dev);
	u32 scale;

	scale = st->dither_scale & AD5766_DITHER_SCALE_MASK(chan->channel);

	वापस (scale >> (chan->channel * 2));
पूर्ण

अटल पूर्णांक ad5766_set_dither_scale(काष्ठा iio_dev *dev,
			  स्थिर काष्ठा iio_chan_spec *chan,
			  अचिन्हित पूर्णांक scale)
अणु
	पूर्णांक ret;
	काष्ठा ad5766_state *st = iio_priv(dev);
	uपूर्णांक16_t val;

	st->dither_scale &= ~AD5766_DITHER_SCALE_MASK(chan->channel);
	st->dither_scale |= AD5766_DITHER_SCALE(chan->channel, scale);

	val = FIELD_GET(AD5766_LOWER_WORD_SPI_MASK, st->dither_scale);
	ret = ad5766_ग_लिखो(dev, AD5766_CMD_DITHER_SCALE_1, val);
	अगर (ret)
		वापस ret;
	val = FIELD_GET(AD5766_UPPER_WORD_SPI_MASK, st->dither_scale);

	वापस ad5766_ग_लिखो(dev, AD5766_CMD_DITHER_SCALE_2, val);
पूर्ण

अटल स्थिर काष्ठा iio_क्रमागत ad5766_dither_scale_क्रमागत = अणु
	.items = ad5766_dither_scales,
	.num_items = ARRAY_SIZE(ad5766_dither_scales),
	.set = ad5766_set_dither_scale,
	.get = ad5766_get_dither_scale,
पूर्ण;

अटल sमाप_प्रकार ad5766_पढ़ो_ext(काष्ठा iio_dev *indio_dev,
			       uपूर्णांकptr_t निजी,
			       स्थिर काष्ठा iio_chan_spec *chan,
			       अक्षर *buf)
अणु
	काष्ठा ad5766_state *st = iio_priv(indio_dev);

	चयन (निजी) अणु
	हाल AD5766_DITHER_ENABLE:
		वापस प्र_लिखो(buf, "%u\n",
			       !(st->dither_enable & BIT(chan->channel)));
		अवरोध;
	हाल AD5766_DITHER_INVERT:
		वापस प्र_लिखो(buf, "%u\n",
			       !!(st->dither_invert & BIT(chan->channel)));
		अवरोध;
	हाल AD5766_DITHER_SOURCE:
		वापस प्र_लिखो(buf, "%d\n",
			       ad5766_get_dither_source(indio_dev, chan));
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार ad5766_ग_लिखो_ext(काष्ठा iio_dev *indio_dev,
				 uपूर्णांकptr_t निजी,
				 स्थिर काष्ठा iio_chan_spec *chan,
				 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा ad5766_state *st = iio_priv(indio_dev);
	bool पढ़ोin;
	पूर्णांक ret;

	ret = kstrtobool(buf, &पढ़ोin);
	अगर (ret)
		वापस ret;

	चयन (निजी) अणु
	हाल AD5766_DITHER_ENABLE:
		st->dither_enable &= ~AD5766_DITHER_ENABLE_MASK(chan->channel);
		st->dither_enable |= AD5766_DITHER_ENABLE(chan->channel,
							  पढ़ोin);
		ret = ad5766_ग_लिखो(indio_dev, AD5766_CMD_WR_PWR_DITHER,
				   st->dither_enable);
		अवरोध;
	हाल AD5766_DITHER_INVERT:
		st->dither_invert &= ~AD5766_DITHER_INVERT_MASK(chan->channel);
		st->dither_invert |= AD5766_DITHER_INVERT(chan->channel,
							  पढ़ोin);
		ret = ad5766_ग_लिखो(indio_dev, AD5766_CMD_INV_DITHER,
				   st->dither_invert);
		अवरोध;
	हाल AD5766_DITHER_SOURCE:
		ret = ad5766_set_dither_source(indio_dev, chan, पढ़ोin);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस ret ? ret : len;
पूर्ण

#घोषणा _AD5766_CHAN_EXT_INFO(_name, _what, _shared) अणु \
	.name = _name, \
	.पढ़ो = ad5766_पढ़ो_ext, \
	.ग_लिखो = ad5766_ग_लिखो_ext, \
	.निजी = _what, \
	.shared = _shared, \
पूर्ण

#घोषणा IIO_ENUM_AVAILABLE_SHARED(_name, _shared, _e) \
अणु \
	.name = (_name "_available"), \
	.shared = _shared, \
	.पढ़ो = iio_क्रमागत_available_पढ़ो, \
	.निजी = (uपूर्णांकptr_t)(_e), \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info ad5766_ext_info[] = अणु

	_AD5766_CHAN_EXT_INFO("dither_enable", AD5766_DITHER_ENABLE,
			      IIO_SEPARATE),
	_AD5766_CHAN_EXT_INFO("dither_invert", AD5766_DITHER_INVERT,
			      IIO_SEPARATE),
	_AD5766_CHAN_EXT_INFO("dither_source", AD5766_DITHER_SOURCE,
			      IIO_SEPARATE),
	IIO_ENUM("dither_scale", IIO_SEPARATE, &ad5766_dither_scale_क्रमागत),
	IIO_ENUM_AVAILABLE_SHARED("dither_scale",
				  IIO_SEPARATE,
				  &ad5766_dither_scale_क्रमागत),
	अणुपूर्ण
पूर्ण;

#घोषणा AD576x_CHANNEL(_chan, _bits) अणु					\
	.type = IIO_VOLTAGE,						\
	.indexed = 1,							\
	.output = 1,							\
	.channel = (_chan),						\
	.address = (_chan),						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),			\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |		\
		BIT(IIO_CHAN_INFO_SCALE),				\
	.scan_type = अणु							\
		.sign = 'u',						\
		.realbits = (_bits),					\
		.storagebits = 16,					\
		.shअगरt = 16 - (_bits),					\
	पूर्ण,								\
	.ext_info = ad5766_ext_info,					\
पूर्ण

#घोषणा DECLARE_AD576x_CHANNELS(_name, _bits)			\
स्थिर काष्ठा iio_chan_spec _name[] = अणु				\
	AD576x_CHANNEL(0, (_bits)),				\
	AD576x_CHANNEL(1, (_bits)),				\
	AD576x_CHANNEL(2, (_bits)),				\
	AD576x_CHANNEL(3, (_bits)),				\
	AD576x_CHANNEL(4, (_bits)),				\
	AD576x_CHANNEL(5, (_bits)),				\
	AD576x_CHANNEL(6, (_bits)),				\
	AD576x_CHANNEL(7, (_bits)),				\
	AD576x_CHANNEL(8, (_bits)),				\
	AD576x_CHANNEL(9, (_bits)),				\
	AD576x_CHANNEL(10, (_bits)),				\
	AD576x_CHANNEL(11, (_bits)),				\
	AD576x_CHANNEL(12, (_bits)),				\
	AD576x_CHANNEL(13, (_bits)),				\
	AD576x_CHANNEL(14, (_bits)),				\
	AD576x_CHANNEL(15, (_bits)),				\
पूर्ण

अटल DECLARE_AD576x_CHANNELS(ad5766_channels, 16);
अटल DECLARE_AD576x_CHANNELS(ad5767_channels, 12);

अटल स्थिर काष्ठा ad5766_chip_info ad5766_chip_infos[] = अणु
	[ID_AD5766] = अणु
		.num_channels = ARRAY_SIZE(ad5766_channels),
		.channels = ad5766_channels,
	पूर्ण,
	[ID_AD5767] = अणु
		.num_channels = ARRAY_SIZE(ad5767_channels),
		.channels = ad5767_channels,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ad5766_get_output_range(काष्ठा ad5766_state *st)
अणु
	पूर्णांक i, ret, min, max, पंचांगp[2];

	ret = device_property_पढ़ो_u32_array(&st->spi->dev,
					     "output-range-voltage",
					     पंचांगp, 2);
	अगर (ret)
		वापस ret;

	min = पंचांगp[0] / 1000;
	max = पंचांगp[1] / 1000;
	क्रम (i = 0; i < ARRAY_SIZE(ad5766_span_tbl); i++) अणु
		अगर (ad5766_span_tbl[i].min != min ||
		    ad5766_span_tbl[i].max != max)
			जारी;

		st->crt_range = i;

		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad5766_शेष_setup(काष्ठा ad5766_state *st)
अणु
	uपूर्णांक16_t val;
	पूर्णांक ret, i;

	/* Always issue a reset beक्रमe writing to the span रेजिस्टर. */
	ret = ad5766_reset(st);
	अगर (ret)
		वापस ret;

	ret = ad5766_get_output_range(st);
	अगर (ret)
		वापस ret;

	/* Dither घातer करोwn */
	st->dither_enable = GENMASK(15, 0);
	ret = __ad5766_spi_ग_लिखो(st, AD5766_CMD_WR_PWR_DITHER,
			     st->dither_enable);
	अगर (ret)
		वापस ret;

	st->dither_source = 0;
	क्रम (i = 0; i < ARRAY_SIZE(ad5766_channels); i++)
		st->dither_source |= AD5766_DITHER_SOURCE(i, 0);
	val = FIELD_GET(AD5766_LOWER_WORD_SPI_MASK, st->dither_source);
	ret = __ad5766_spi_ग_लिखो(st, AD5766_CMD_DITHER_SIG_1, val);
	अगर (ret)
		वापस ret;

	val = FIELD_GET(AD5766_UPPER_WORD_SPI_MASK, st->dither_source);
	ret = __ad5766_spi_ग_लिखो(st, AD5766_CMD_DITHER_SIG_2, val);
	अगर (ret)
		वापस ret;

	st->dither_scale = 0;
	val = FIELD_GET(AD5766_LOWER_WORD_SPI_MASK, st->dither_scale);
	ret = __ad5766_spi_ग_लिखो(st, AD5766_CMD_DITHER_SCALE_1, val);
	अगर (ret)
		वापस ret;

	val = FIELD_GET(AD5766_UPPER_WORD_SPI_MASK, st->dither_scale);
	ret = __ad5766_spi_ग_लिखो(st, AD5766_CMD_DITHER_SCALE_2, val);
	अगर (ret)
		वापस ret;

	st->dither_invert = 0;
	ret = __ad5766_spi_ग_लिखो(st, AD5766_CMD_INV_DITHER, st->dither_invert);
	अगर (ret)
		वापस ret;

	वापस  __ad5766_spi_ग_लिखो(st, AD5766_CMD_SPAN_REG, st->crt_range);
पूर्ण

अटल पूर्णांक ad5766_probe(काष्ठा spi_device *spi)
अणु
	क्रमागत ad5766_type type;
	काष्ठा iio_dev *indio_dev;
	काष्ठा ad5766_state *st;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	mutex_init(&st->lock);

	st->spi = spi;
	type = spi_get_device_id(spi)->driver_data;
	st->chip_info = &ad5766_chip_infos[type];

	indio_dev->channels = st->chip_info->channels;
	indio_dev->num_channels = st->chip_info->num_channels;
	indio_dev->info = &ad5766_info;
	indio_dev->dev.parent = &spi->dev;
	indio_dev->dev.of_node = spi->dev.of_node;
	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	st->gpio_reset = devm_gpiod_get_optional(&st->spi->dev, "reset",
						GPIOD_OUT_LOW);
	अगर (IS_ERR(st->gpio_reset))
		वापस PTR_ERR(st->gpio_reset);

	ret = ad5766_शेष_setup(st);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id ad5766_dt_match[] = अणु
	अणु .compatible = "adi,ad5766" पूर्ण,
	अणु .compatible = "adi,ad5767" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ad5766_dt_match);

अटल स्थिर काष्ठा spi_device_id ad5766_spi_ids[] = अणु
	अणु "ad5766", ID_AD5766 पूर्ण,
	अणु "ad5767", ID_AD5767 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad5766_spi_ids);

अटल काष्ठा spi_driver ad5766_driver = अणु
	.driver = अणु
		.name = "ad5766",
		.of_match_table = ad5766_dt_match,
	पूर्ण,
	.probe = ad5766_probe,
	.id_table = ad5766_spi_ids,
पूर्ण;
module_spi_driver(ad5766_driver);

MODULE_AUTHOR("Denis-Gabriel Gheorghescu <denis.gheorghescu@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD5766/AD5767 DACs");
MODULE_LICENSE("GPL v2");
