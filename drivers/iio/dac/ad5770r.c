<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * AD5770R Digital to analog converters driver
 *
 * Copyright 2018 Analog Devices Inc.
 */

#समावेश <linux/bits.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/spi/spi.h>

#घोषणा ADI_SPI_IF_CONFIG_A		0x00
#घोषणा ADI_SPI_IF_CONFIG_B		0x01
#घोषणा ADI_SPI_IF_DEVICE_CONFIG	0x02
#घोषणा ADI_SPI_IF_CHIP_TYPE		0x03
#घोषणा ADI_SPI_IF_PRODUCT_ID_L		0x04
#घोषणा ADI_SPI_IF_PRODUCT_ID_H		0x05
#घोषणा ADI_SPI_IF_CHIP_GRADE		0x06
#घोषणा ADI_SPI_IF_SCRACTH_PAD		0x0A
#घोषणा ADI_SPI_IF_SPI_REVISION		0x0B
#घोषणा ADI_SPI_IF_SPI_VENDOR_L		0x0C
#घोषणा ADI_SPI_IF_SPI_VENDOR_H		0x0D
#घोषणा ADI_SPI_IF_SPI_STREAM_MODE	0x0E
#घोषणा ADI_SPI_IF_CONFIG_C		0x10
#घोषणा ADI_SPI_IF_STATUS_A		0x11

/* ADI_SPI_IF_CONFIG_A */
#घोषणा ADI_SPI_IF_SW_RESET_MSK		(BIT(0) | BIT(7))
#घोषणा ADI_SPI_IF_SW_RESET_SEL(x)	((x) & ADI_SPI_IF_SW_RESET_MSK)
#घोषणा ADI_SPI_IF_ADDR_ASC_MSK		(BIT(2) | BIT(5))
#घोषणा ADI_SPI_IF_ADDR_ASC_SEL(x)	(((x) << 2) & ADI_SPI_IF_ADDR_ASC_MSK)

/* ADI_SPI_IF_CONFIG_B */
#घोषणा ADI_SPI_IF_SINGLE_INS_MSK	BIT(7)
#घोषणा ADI_SPI_IF_SINGLE_INS_SEL(x)	FIELD_PREP(ADI_SPI_IF_SINGLE_INS_MSK, x)
#घोषणा ADI_SPI_IF_SHORT_INS_MSK	BIT(7)
#घोषणा ADI_SPI_IF_SHORT_INS_SEL(x)	FIELD_PREP(ADI_SPI_IF_SINGLE_INS_MSK, x)

/* ADI_SPI_IF_CONFIG_C */
#घोषणा ADI_SPI_IF_STRICT_REG_MSK	BIT(5)
#घोषणा ADI_SPI_IF_STRICT_REG_GET(x)	FIELD_GET(ADI_SPI_IF_STRICT_REG_MSK, x)

/* AD5770R configuration रेजिस्टरs */
#घोषणा AD5770R_CHANNEL_CONFIG		0x14
#घोषणा AD5770R_OUTPUT_RANGE(ch)	(0x15 + (ch))
#घोषणा AD5770R_FILTER_RESISTOR(ch)	(0x1D + (ch))
#घोषणा AD5770R_REFERENCE		0x1B
#घोषणा AD5770R_DAC_LSB(ch)		(0x26 + 2 * (ch))
#घोषणा AD5770R_DAC_MSB(ch)		(0x27 + 2 * (ch))
#घोषणा AD5770R_CH_SELECT		0x34
#घोषणा AD5770R_CH_ENABLE		0x44

/* AD5770R_CHANNEL_CONFIG */
#घोषणा AD5770R_CFG_CH0_SINK_EN(x)		(((x) & 0x1) << 7)
#घोषणा AD5770R_CFG_SHUTDOWN_B(x, ch)		(((x) & 0x1) << (ch))

/* AD5770R_OUTPUT_RANGE */
#घोषणा AD5770R_RANGE_OUTPUT_SCALING(x)		(((x) & GENMASK(5, 0)) << 2)
#घोषणा AD5770R_RANGE_MODE(x)			((x) & GENMASK(1, 0))

/* AD5770R_REFERENCE */
#घोषणा AD5770R_REF_RESISTOR_SEL(x)		(((x) & 0x1) << 2)
#घोषणा AD5770R_REF_SEL(x)			((x) & GENMASK(1, 0))

/* AD5770R_CH_ENABLE */
#घोषणा AD5770R_CH_SET(x, ch)		(((x) & 0x1) << (ch))

#घोषणा AD5770R_MAX_CHANNELS	6
#घोषणा AD5770R_MAX_CH_MODES	14
#घोषणा AD5770R_LOW_VREF_mV	1250
#घोषणा AD5770R_HIGH_VREF_mV	2500

क्रमागत ad5770r_ch0_modes अणु
	AD5770R_CH0_0_300 = 0,
	AD5770R_CH0_NEG_60_0,
	AD5770R_CH0_NEG_60_300
पूर्ण;

क्रमागत ad5770r_ch1_modes अणु
	AD5770R_CH1_0_140_LOW_HEAD = 1,
	AD5770R_CH1_0_140_LOW_NOISE,
	AD5770R_CH1_0_250
पूर्ण;

क्रमागत ad5770r_ch2_5_modes अणु
	AD5770R_CH_LOW_RANGE = 0,
	AD5770R_CH_HIGH_RANGE
पूर्ण;

क्रमागत ad5770r_ref_v अणु
	AD5770R_EXT_2_5_V = 0,
	AD5770R_INT_1_25_V_OUT_ON,
	AD5770R_EXT_1_25_V,
	AD5770R_INT_1_25_V_OUT_OFF
पूर्ण;

क्रमागत ad5770r_output_filter_resistor अणु
	AD5770R_FILTER_60_OHM = 0x0,
	AD5770R_FILTER_5_6_KOHM = 0x5,
	AD5770R_FILTER_11_2_KOHM,
	AD5770R_FILTER_22_2_KOHM,
	AD5770R_FILTER_44_4_KOHM,
	AD5770R_FILTER_104_KOHM,
पूर्ण;

काष्ठा ad5770r_out_range अणु
	u8	out_scale;
	u8	out_range_mode;
पूर्ण;

/**
 * काष्ठा ad5770r_state - driver instance specअगरic data
 * @spi:		spi_device
 * @regmap:		regmap
 * @vref_reg:		fixed regulator क्रम reference configuration
 * @gpio_reset:		gpio descriptor
 * @output_mode:	array contains channels output ranges
 * @vref:		reference value
 * @ch_pwr_करोwn:	घातerकरोwn flags
 * @पूर्णांकernal_ref:	पूर्णांकernal reference flag
 * @बाह्यal_res:	बाह्यal 2.5k resistor flag
 * @transf_buf:		cache aligned buffer क्रम spi पढ़ो/ग_लिखो
 */
काष्ठा ad5770r_state अणु
	काष्ठा spi_device		*spi;
	काष्ठा regmap			*regmap;
	काष्ठा regulator		*vref_reg;
	काष्ठा gpio_desc		*gpio_reset;
	काष्ठा ad5770r_out_range	output_mode[AD5770R_MAX_CHANNELS];
	पूर्णांक				vref;
	bool				ch_pwr_करोwn[AD5770R_MAX_CHANNELS];
	bool				पूर्णांकernal_ref;
	bool				बाह्यal_res;
	u8				transf_buf[2] ____cacheline_aligned;
पूर्ण;

अटल स्थिर काष्ठा regmap_config ad5770r_spi_regmap_config = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.पढ़ो_flag_mask = BIT(7),
पूर्ण;

काष्ठा ad5770r_output_modes अणु
	अचिन्हित पूर्णांक ch;
	u8 mode;
	पूर्णांक min;
	पूर्णांक max;
पूर्ण;

अटल काष्ठा ad5770r_output_modes ad5770r_rng_tbl[] = अणु
	अणु 0, AD5770R_CH0_0_300, 0, 300 पूर्ण,
	अणु 0, AD5770R_CH0_NEG_60_0, -60, 0 पूर्ण,
	अणु 0, AD5770R_CH0_NEG_60_300, -60, 300 पूर्ण,
	अणु 1, AD5770R_CH1_0_140_LOW_HEAD, 0, 140 पूर्ण,
	अणु 1, AD5770R_CH1_0_140_LOW_NOISE, 0, 140 पूर्ण,
	अणु 1, AD5770R_CH1_0_250, 0, 250 पूर्ण,
	अणु 2, AD5770R_CH_LOW_RANGE, 0, 55 पूर्ण,
	अणु 2, AD5770R_CH_HIGH_RANGE, 0, 150 पूर्ण,
	अणु 3, AD5770R_CH_LOW_RANGE, 0, 45 पूर्ण,
	अणु 3, AD5770R_CH_HIGH_RANGE, 0, 100 पूर्ण,
	अणु 4, AD5770R_CH_LOW_RANGE, 0, 45 पूर्ण,
	अणु 4, AD5770R_CH_HIGH_RANGE, 0, 100 पूर्ण,
	अणु 5, AD5770R_CH_LOW_RANGE, 0, 45 पूर्ण,
	अणु 5, AD5770R_CH_HIGH_RANGE, 0, 100 पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ad5770r_filter_freqs[] = अणु
	153, 357, 715, 1400, 2800, 262000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ad5770r_filter_reg_vals[] = अणु
	AD5770R_FILTER_104_KOHM,
	AD5770R_FILTER_44_4_KOHM,
	AD5770R_FILTER_22_2_KOHM,
	AD5770R_FILTER_11_2_KOHM,
	AD5770R_FILTER_5_6_KOHM,
	AD5770R_FILTER_60_OHM
पूर्ण;

अटल पूर्णांक ad5770r_set_output_mode(काष्ठा ad5770r_state *st,
				   स्थिर काष्ठा ad5770r_out_range *out_mode,
				   पूर्णांक channel)
अणु
	अचिन्हित पूर्णांक regval;

	regval = AD5770R_RANGE_OUTPUT_SCALING(out_mode->out_scale) |
		 AD5770R_RANGE_MODE(out_mode->out_range_mode);

	वापस regmap_ग_लिखो(st->regmap,
			    AD5770R_OUTPUT_RANGE(channel), regval);
पूर्ण

अटल पूर्णांक ad5770r_set_reference(काष्ठा ad5770r_state *st)
अणु
	अचिन्हित पूर्णांक regval;

	regval = AD5770R_REF_RESISTOR_SEL(st->बाह्यal_res);

	अगर (st->पूर्णांकernal_ref) अणु
		regval |= AD5770R_REF_SEL(AD5770R_INT_1_25_V_OUT_OFF);
	पूर्ण अन्यथा अणु
		चयन (st->vref) अणु
		हाल AD5770R_LOW_VREF_mV:
			regval |= AD5770R_REF_SEL(AD5770R_EXT_1_25_V);
			अवरोध;
		हाल AD5770R_HIGH_VREF_mV:
			regval |= AD5770R_REF_SEL(AD5770R_EXT_2_5_V);
			अवरोध;
		शेष:
			regval = AD5770R_REF_SEL(AD5770R_INT_1_25_V_OUT_OFF);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस regmap_ग_लिखो(st->regmap, AD5770R_REFERENCE, regval);
पूर्ण

अटल पूर्णांक ad5770r_soft_reset(काष्ठा ad5770r_state *st)
अणु
	वापस regmap_ग_लिखो(st->regmap, ADI_SPI_IF_CONFIG_A,
			    ADI_SPI_IF_SW_RESET_SEL(1));
पूर्ण

अटल पूर्णांक ad5770r_reset(काष्ठा ad5770r_state *st)
अणु
	/* Perक्रमm software reset अगर no GPIO provided */
	अगर (!st->gpio_reset)
		वापस ad5770r_soft_reset(st);

	gpiod_set_value_cansleep(st->gpio_reset, 0);
	usleep_range(10, 20);
	gpiod_set_value_cansleep(st->gpio_reset, 1);

	/* data must not be written during reset समयframe */
	usleep_range(100, 200);

	वापस 0;
पूर्ण

अटल पूर्णांक ad5770r_get_range(काष्ठा ad5770r_state *st,
			     पूर्णांक ch, पूर्णांक *min, पूर्णांक *max)
अणु
	पूर्णांक i;
	u8 tbl_ch, tbl_mode, out_range;

	out_range = st->output_mode[ch].out_range_mode;

	क्रम (i = 0; i < AD5770R_MAX_CH_MODES; i++) अणु
		tbl_ch = ad5770r_rng_tbl[i].ch;
		tbl_mode = ad5770r_rng_tbl[i].mode;
		अगर (tbl_ch == ch && tbl_mode == out_range) अणु
			*min = ad5770r_rng_tbl[i].min;
			*max = ad5770r_rng_tbl[i].max;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad5770r_get_filter_freq(काष्ठा iio_dev *indio_dev,
				   स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक *freq)
अणु
	काष्ठा ad5770r_state *st = iio_priv(indio_dev);
	पूर्णांक ret;
	अचिन्हित पूर्णांक regval, i;

	ret = regmap_पढ़ो(st->regmap,
			  AD5770R_FILTER_RESISTOR(chan->channel), &regval);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(ad5770r_filter_reg_vals); i++)
		अगर (regval == ad5770r_filter_reg_vals[i])
			अवरोध;
	अगर (i == ARRAY_SIZE(ad5770r_filter_reg_vals))
		वापस -EINVAL;

	*freq = ad5770r_filter_freqs[i];

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक ad5770r_set_filter_freq(काष्ठा iio_dev *indio_dev,
				   स्थिर काष्ठा iio_chan_spec *chan,
				   अचिन्हित पूर्णांक freq)
अणु
	काष्ठा ad5770r_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक regval, i;

	क्रम (i = 0; i < ARRAY_SIZE(ad5770r_filter_freqs); i++)
		अगर (ad5770r_filter_freqs[i] >= freq)
			अवरोध;
	अगर (i == ARRAY_SIZE(ad5770r_filter_freqs))
		वापस -EINVAL;

	regval = ad5770r_filter_reg_vals[i];

	वापस regmap_ग_लिखो(st->regmap, AD5770R_FILTER_RESISTOR(chan->channel),
			    regval);
पूर्ण

अटल पूर्णांक ad5770r_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	काष्ठा ad5770r_state *st = iio_priv(indio_dev);
	पूर्णांक max, min, ret;
	u16 buf16;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = regmap_bulk_पढ़ो(st->regmap,
				       chan->address,
				       st->transf_buf, 2);
		अगर (ret)
			वापस 0;

		buf16 = st->transf_buf[0] + (st->transf_buf[1] << 8);
		*val = buf16 >> 2;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		ret = ad5770r_get_range(st, chan->channel, &min, &max);
		अगर (ret < 0)
			वापस ret;
		*val = max - min;
		/* There is no sign bit. (negative current is mapped from 0)
		 * (sourced/sinked) current = raw * scale + offset
		 * where offset in हाल of CH0 can be negative.
		 */
		*val2 = 14;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		वापस ad5770r_get_filter_freq(indio_dev, chan, val);
	हाल IIO_CHAN_INFO_OFFSET:
		ret = ad5770r_get_range(st, chan->channel, &min, &max);
		अगर (ret < 0)
			वापस ret;
		*val = min;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ad5770r_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ info)
अणु
	काष्ठा ad5770r_state *st = iio_priv(indio_dev);

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		st->transf_buf[0] = ((u16)val >> 6);
		st->transf_buf[1] = (val & GENMASK(5, 0)) << 2;
		वापस regmap_bulk_ग_लिखो(st->regmap, chan->address,
					 st->transf_buf, 2);
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		वापस ad5770r_set_filter_freq(indio_dev, chan, val);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ad5770r_पढ़ो_freq_avail(काष्ठा iio_dev *indio_dev,
				   काष्ठा iio_chan_spec स्थिर *chan,
				   स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
				   दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		*type = IIO_VAL_INT;
		*vals = ad5770r_filter_freqs;
		*length = ARRAY_SIZE(ad5770r_filter_freqs);
		वापस IIO_AVAIL_LIST;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad5770r_reg_access(काष्ठा iio_dev *indio_dev,
			      अचिन्हित पूर्णांक reg,
			      अचिन्हित पूर्णांक ग_लिखोval,
			      अचिन्हित पूर्णांक *पढ़ोval)
अणु
	काष्ठा ad5770r_state *st = iio_priv(indio_dev);

	अगर (पढ़ोval)
		वापस regmap_पढ़ो(st->regmap, reg, पढ़ोval);
	अन्यथा
		वापस regmap_ग_लिखो(st->regmap, reg, ग_लिखोval);
पूर्ण

अटल स्थिर काष्ठा iio_info ad5770r_info = अणु
	.पढ़ो_raw = ad5770r_पढ़ो_raw,
	.ग_लिखो_raw = ad5770r_ग_लिखो_raw,
	.पढ़ो_avail = ad5770r_पढ़ो_freq_avail,
	.debugfs_reg_access = &ad5770r_reg_access,
पूर्ण;

अटल पूर्णांक ad5770r_store_output_range(काष्ठा ad5770r_state *st,
				      पूर्णांक min, पूर्णांक max, पूर्णांक index)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < AD5770R_MAX_CH_MODES; i++) अणु
		अगर (ad5770r_rng_tbl[i].ch != index)
			जारी;
		अगर (ad5770r_rng_tbl[i].min != min ||
		    ad5770r_rng_tbl[i].max != max)
			जारी;
		st->output_mode[index].out_range_mode = ad5770r_rng_tbl[i].mode;

		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार ad5770r_पढ़ो_dac_घातerकरोwn(काष्ठा iio_dev *indio_dev,
					  uपूर्णांकptr_t निजी,
					  स्थिर काष्ठा iio_chan_spec *chan,
					  अक्षर *buf)
अणु
	काष्ठा ad5770r_state *st = iio_priv(indio_dev);

	वापस sysfs_emit(buf, "%d\n", st->ch_pwr_करोwn[chan->channel]);
पूर्ण

अटल sमाप_प्रकार ad5770r_ग_लिखो_dac_घातerकरोwn(काष्ठा iio_dev *indio_dev,
					   uपूर्णांकptr_t निजी,
					   स्थिर काष्ठा iio_chan_spec *chan,
					   स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा ad5770r_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक regval;
	अचिन्हित पूर्णांक mask;
	bool पढ़ोin;
	पूर्णांक ret;

	ret = kstrtobool(buf, &पढ़ोin);
	अगर (ret)
		वापस ret;

	पढ़ोin = !पढ़ोin;

	regval = AD5770R_CFG_SHUTDOWN_B(पढ़ोin, chan->channel);
	अगर (chan->channel == 0 &&
	    st->output_mode[0].out_range_mode > AD5770R_CH0_0_300) अणु
		regval |= AD5770R_CFG_CH0_SINK_EN(पढ़ोin);
		mask = BIT(chan->channel) + BIT(7);
	पूर्ण अन्यथा अणु
		mask = BIT(chan->channel);
	पूर्ण
	ret = regmap_update_bits(st->regmap, AD5770R_CHANNEL_CONFIG, mask,
				 regval);
	अगर (ret)
		वापस ret;

	regval = AD5770R_CH_SET(पढ़ोin, chan->channel);
	ret = regmap_update_bits(st->regmap, AD5770R_CH_ENABLE,
				 BIT(chan->channel), regval);
	अगर (ret)
		वापस ret;

	st->ch_pwr_करोwn[chan->channel] = !पढ़ोin;

	वापस len;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info ad5770r_ext_info[] = अणु
	अणु
		.name = "powerdown",
		.पढ़ो = ad5770r_पढ़ो_dac_घातerकरोwn,
		.ग_लिखो = ad5770r_ग_लिखो_dac_घातerकरोwn,
		.shared = IIO_SEPARATE,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

#घोषणा AD5770R_IDAC_CHANNEL(index, reg) अणु				\
	.type = IIO_CURRENT,						\
	.address = reg,							\
	.indexed = 1,							\
	.channel = index,						\
	.output = 1,							\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |			\
		BIT(IIO_CHAN_INFO_SCALE) |				\
		BIT(IIO_CHAN_INFO_OFFSET) |				\
		BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY),	\
	.info_mask_shared_by_type_available =				\
		BIT(IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY),	\
	.ext_info = ad5770r_ext_info,					\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ad5770r_channels[] = अणु
	AD5770R_IDAC_CHANNEL(0, AD5770R_DAC_MSB(0)),
	AD5770R_IDAC_CHANNEL(1, AD5770R_DAC_MSB(1)),
	AD5770R_IDAC_CHANNEL(2, AD5770R_DAC_MSB(2)),
	AD5770R_IDAC_CHANNEL(3, AD5770R_DAC_MSB(3)),
	AD5770R_IDAC_CHANNEL(4, AD5770R_DAC_MSB(4)),
	AD5770R_IDAC_CHANNEL(5, AD5770R_DAC_MSB(5)),
पूर्ण;

अटल पूर्णांक ad5770r_channel_config(काष्ठा ad5770r_state *st)
अणु
	पूर्णांक ret, पंचांगp[2], min, max;
	अचिन्हित पूर्णांक num;
	काष्ठा fwnode_handle *child;

	num = device_get_child_node_count(&st->spi->dev);
	अगर (num != AD5770R_MAX_CHANNELS)
		वापस -EINVAL;

	device_क्रम_each_child_node(&st->spi->dev, child) अणु
		ret = fwnode_property_पढ़ो_u32(child, "num", &num);
		अगर (ret)
			जाओ err_child_out;
		अगर (num >= AD5770R_MAX_CHANNELS) अणु
			ret = -EINVAL;
			जाओ err_child_out;
		पूर्ण

		ret = fwnode_property_पढ़ो_u32_array(child,
						     "adi,range-microamp",
						     पंचांगp, 2);
		अगर (ret)
			जाओ err_child_out;

		min = पंचांगp[0] / 1000;
		max = पंचांगp[1] / 1000;
		ret = ad5770r_store_output_range(st, min, max, num);
		अगर (ret)
			जाओ err_child_out;
	पूर्ण

	वापस 0;

err_child_out:
	fwnode_handle_put(child);
	वापस ret;
पूर्ण

अटल पूर्णांक ad5770r_init(काष्ठा ad5770r_state *st)
अणु
	पूर्णांक ret, i;

	st->gpio_reset = devm_gpiod_get_optional(&st->spi->dev, "reset",
						 GPIOD_OUT_HIGH);
	अगर (IS_ERR(st->gpio_reset))
		वापस PTR_ERR(st->gpio_reset);

	/* Perक्रमm a reset */
	ret = ad5770r_reset(st);
	अगर (ret)
		वापस ret;

	/* Set output range */
	ret = ad5770r_channel_config(st);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < AD5770R_MAX_CHANNELS; i++) अणु
		ret = ad5770r_set_output_mode(st,  &st->output_mode[i], i);
		अगर (ret)
			वापस ret;
	पूर्ण

	st->बाह्यal_res = fwnode_property_पढ़ो_bool(st->spi->dev.fwnode,
						     "adi,external-resistor");

	ret = ad5770r_set_reference(st);
	अगर (ret)
		वापस ret;

	/* Set outमाला_दो off */
	ret = regmap_ग_लिखो(st->regmap, AD5770R_CHANNEL_CONFIG, 0x00);
	अगर (ret)
		वापस ret;

	ret = regmap_ग_लिखो(st->regmap, AD5770R_CH_ENABLE, 0x00);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < AD5770R_MAX_CHANNELS; i++)
		st->ch_pwr_करोwn[i] = true;

	वापस ret;
पूर्ण

अटल व्योम ad5770r_disable_regulator(व्योम *data)
अणु
	काष्ठा ad5770r_state *st = data;

	regulator_disable(st->vref_reg);
पूर्ण

अटल पूर्णांक ad5770r_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad5770r_state *st;
	काष्ठा iio_dev *indio_dev;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);

	st->spi = spi;

	regmap = devm_regmap_init_spi(spi, &ad5770r_spi_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&spi->dev, "Error initializing spi regmap: %ld\n",
			PTR_ERR(regmap));
		वापस PTR_ERR(regmap);
	पूर्ण
	st->regmap = regmap;

	st->vref_reg = devm_regulator_get_optional(&spi->dev, "vref");
	अगर (!IS_ERR(st->vref_reg)) अणु
		ret = regulator_enable(st->vref_reg);
		अगर (ret) अणु
			dev_err(&spi->dev,
				"Failed to enable vref regulators: %d\n", ret);
			वापस ret;
		पूर्ण

		ret = devm_add_action_or_reset(&spi->dev,
					       ad5770r_disable_regulator,
					       st);
		अगर (ret < 0)
			वापस ret;

		ret = regulator_get_voltage(st->vref_reg);
		अगर (ret < 0)
			वापस ret;

		st->vref = ret / 1000;
	पूर्ण अन्यथा अणु
		अगर (PTR_ERR(st->vref_reg) == -ENODEV) अणु
			st->vref = AD5770R_LOW_VREF_mV;
			st->पूर्णांकernal_ref = true;
		पूर्ण अन्यथा अणु
			वापस PTR_ERR(st->vref_reg);
		पूर्ण
	पूर्ण

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad5770r_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = ad5770r_channels;
	indio_dev->num_channels = ARRAY_SIZE(ad5770r_channels);

	ret = ad5770r_init(st);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "AD5770R init failed\n");
		वापस ret;
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&st->spi->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id ad5770r_of_id[] = अणु
	अणु .compatible = "adi,ad5770r", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ad5770r_of_id);

अटल स्थिर काष्ठा spi_device_id ad5770r_id[] = अणु
	अणु "ad5770r", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad5770r_id);

अटल काष्ठा spi_driver ad5770r_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = ad5770r_of_id,
	पूर्ण,
	.probe = ad5770r_probe,
	.id_table = ad5770r_id,
पूर्ण;

module_spi_driver(ad5770r_driver);

MODULE_AUTHOR("Mircea Caprioru <mircea.caprioru@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD5770R IDAC");
MODULE_LICENSE("GPL v2");
