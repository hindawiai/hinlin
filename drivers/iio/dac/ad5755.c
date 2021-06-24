<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AD5755, AD5755-1, AD5757, AD5735, AD5737 Digital to analog converters driver
 *
 * Copyright 2012 Analog Devices Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/of.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/platक्रमm_data/ad5755.h>

#घोषणा AD5755_NUM_CHANNELS 4

#घोषणा AD5755_ADDR(x)			((x) << 16)

#घोषणा AD5755_WRITE_REG_DATA(chan)	(chan)
#घोषणा AD5755_WRITE_REG_GAIN(chan)	(0x08 | (chan))
#घोषणा AD5755_WRITE_REG_OFFSET(chan)	(0x10 | (chan))
#घोषणा AD5755_WRITE_REG_CTRL(chan)	(0x1c | (chan))

#घोषणा AD5755_READ_REG_DATA(chan)	(chan)
#घोषणा AD5755_READ_REG_CTRL(chan)	(0x4 | (chan))
#घोषणा AD5755_READ_REG_GAIN(chan)	(0x8 | (chan))
#घोषणा AD5755_READ_REG_OFFSET(chan)	(0xc | (chan))
#घोषणा AD5755_READ_REG_CLEAR(chan)	(0x10 | (chan))
#घोषणा AD5755_READ_REG_SLEW(chan)	(0x14 | (chan))
#घोषणा AD5755_READ_REG_STATUS		0x18
#घोषणा AD5755_READ_REG_MAIN		0x19
#घोषणा AD5755_READ_REG_DC_DC		0x1a

#घोषणा AD5755_CTRL_REG_SLEW	0x0
#घोषणा AD5755_CTRL_REG_MAIN	0x1
#घोषणा AD5755_CTRL_REG_DAC	0x2
#घोषणा AD5755_CTRL_REG_DC_DC	0x3
#घोषणा AD5755_CTRL_REG_SW	0x4

#घोषणा AD5755_READ_FLAG 0x800000

#घोषणा AD5755_NOOP 0x1CE000

#घोषणा AD5755_DAC_INT_EN			BIT(8)
#घोषणा AD5755_DAC_CLR_EN			BIT(7)
#घोषणा AD5755_DAC_OUT_EN			BIT(6)
#घोषणा AD5755_DAC_INT_CURRENT_SENSE_RESISTOR	BIT(5)
#घोषणा AD5755_DAC_DC_DC_EN			BIT(4)
#घोषणा AD5755_DAC_VOLTAGE_OVERRANGE_EN		BIT(3)

#घोषणा AD5755_DC_DC_MAXV			0
#घोषणा AD5755_DC_DC_FREQ_SHIFT			2
#घोषणा AD5755_DC_DC_PHASE_SHIFT		4
#घोषणा AD5755_EXT_DC_DC_COMP_RES		BIT(6)

#घोषणा AD5755_SLEW_STEP_SIZE_SHIFT		0
#घोषणा AD5755_SLEW_RATE_SHIFT			3
#घोषणा AD5755_SLEW_ENABLE			BIT(12)

/**
 * काष्ठा ad5755_chip_info - chip specअगरic inक्रमmation
 * @channel_ढाँचा:	channel specअगरication
 * @calib_shअगरt:	shअगरt क्रम the calibration data रेजिस्टरs
 * @has_voltage_out:	whether the chip has voltage outमाला_दो
 */
काष्ठा ad5755_chip_info अणु
	स्थिर काष्ठा iio_chan_spec channel_ढाँचा;
	अचिन्हित पूर्णांक calib_shअगरt;
	bool has_voltage_out;
पूर्ण;

/**
 * काष्ठा ad5755_state - driver instance specअगरic data
 * @spi:	spi device the driver is attached to
 * @chip_info:	chip model specअगरic स्थिरants, available modes etc
 * @pwr_करोwn:	biपंचांगask which contains  hether a channel is घातered करोwn or not
 * @ctrl:	software shaकरोw of the channel ctrl रेजिस्टरs
 * @channels:	iio channel spec क्रम the device
 * @lock:	lock to protect the data buffer during SPI ops
 * @data:	spi transfer buffers
 */
काष्ठा ad5755_state अणु
	काष्ठा spi_device		*spi;
	स्थिर काष्ठा ad5755_chip_info	*chip_info;
	अचिन्हित पूर्णांक			pwr_करोwn;
	अचिन्हित पूर्णांक			ctrl[AD5755_NUM_CHANNELS];
	काष्ठा iio_chan_spec		channels[AD5755_NUM_CHANNELS];
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

क्रमागत ad5755_type अणु
	ID_AD5755,
	ID_AD5757,
	ID_AD5735,
	ID_AD5737,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल स्थिर पूर्णांक ad5755_dcdc_freq_table[][2] = अणु
	अणु 250000, AD5755_DC_DC_FREQ_250kHZ पूर्ण,
	अणु 410000, AD5755_DC_DC_FREQ_410kHZ पूर्ण,
	अणु 650000, AD5755_DC_DC_FREQ_650kHZ पूर्ण
पूर्ण;

अटल स्थिर पूर्णांक ad5755_dcdc_maxv_table[][2] = अणु
	अणु 23000000, AD5755_DC_DC_MAXV_23V पूर्ण,
	अणु 24500000, AD5755_DC_DC_MAXV_24V5 पूर्ण,
	अणु 27000000, AD5755_DC_DC_MAXV_27V पूर्ण,
	अणु 29500000, AD5755_DC_DC_MAXV_29V5 पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक ad5755_slew_rate_table[][2] = अणु
	अणु 64000, AD5755_SLEW_RATE_64k पूर्ण,
	अणु 32000, AD5755_SLEW_RATE_32k पूर्ण,
	अणु 16000, AD5755_SLEW_RATE_16k पूर्ण,
	अणु 8000, AD5755_SLEW_RATE_8k पूर्ण,
	अणु 4000, AD5755_SLEW_RATE_4k पूर्ण,
	अणु 2000, AD5755_SLEW_RATE_2k पूर्ण,
	अणु 1000, AD5755_SLEW_RATE_1k पूर्ण,
	अणु 500, AD5755_SLEW_RATE_500 पूर्ण,
	अणु 250, AD5755_SLEW_RATE_250 पूर्ण,
	अणु 125, AD5755_SLEW_RATE_125 पूर्ण,
	अणु 64, AD5755_SLEW_RATE_64 पूर्ण,
	अणु 32, AD5755_SLEW_RATE_32 पूर्ण,
	अणु 16, AD5755_SLEW_RATE_16 पूर्ण,
	अणु 8, AD5755_SLEW_RATE_8 पूर्ण,
	अणु 4, AD5755_SLEW_RATE_4 पूर्ण,
	अणु 0, AD5755_SLEW_RATE_0_5 पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक ad5755_slew_step_table[][2] = अणु
	अणु 256, AD5755_SLEW_STEP_SIZE_256 पूर्ण,
	अणु 128, AD5755_SLEW_STEP_SIZE_128 पूर्ण,
	अणु 64, AD5755_SLEW_STEP_SIZE_64 पूर्ण,
	अणु 32, AD5755_SLEW_STEP_SIZE_32 पूर्ण,
	अणु 16, AD5755_SLEW_STEP_SIZE_16 पूर्ण,
	अणु 4, AD5755_SLEW_STEP_SIZE_4 पूर्ण,
	अणु 2, AD5755_SLEW_STEP_SIZE_2 पूर्ण,
	अणु 1, AD5755_SLEW_STEP_SIZE_1 पूर्ण,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक ad5755_ग_लिखो_unlocked(काष्ठा iio_dev *indio_dev,
	अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा ad5755_state *st = iio_priv(indio_dev);

	st->data[0].d32 = cpu_to_be32((reg << 16) | val);

	वापस spi_ग_लिखो(st->spi, &st->data[0].d8[1], 3);
पूर्ण

अटल पूर्णांक ad5755_ग_लिखो_ctrl_unlocked(काष्ठा iio_dev *indio_dev,
	अचिन्हित पूर्णांक channel, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	वापस ad5755_ग_लिखो_unlocked(indio_dev,
		AD5755_WRITE_REG_CTRL(channel), (reg << 13) | val);
पूर्ण

अटल पूर्णांक ad5755_ग_लिखो(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक reg,
	अचिन्हित पूर्णांक val)
अणु
	काष्ठा ad5755_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);
	ret = ad5755_ग_लिखो_unlocked(indio_dev, reg, val);
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5755_ग_लिखो_ctrl(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक channel,
	अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	काष्ठा ad5755_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);
	ret = ad5755_ग_लिखो_ctrl_unlocked(indio_dev, channel, reg, val);
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5755_पढ़ो(काष्ठा iio_dev *indio_dev, अचिन्हित पूर्णांक addr)
अणु
	काष्ठा ad5755_state *st = iio_priv(indio_dev);
	पूर्णांक ret;
	काष्ठा spi_transfer t[] = अणु
		अणु
			.tx_buf = &st->data[0].d8[1],
			.len = 3,
			.cs_change = 1,
		पूर्ण, अणु
			.tx_buf = &st->data[1].d8[1],
			.rx_buf = &st->data[1].d8[1],
			.len = 3,
		पूर्ण,
	पूर्ण;

	mutex_lock(&st->lock);

	st->data[0].d32 = cpu_to_be32(AD5755_READ_FLAG | (addr << 16));
	st->data[1].d32 = cpu_to_be32(AD5755_NOOP);

	ret = spi_sync_transfer(st->spi, t, ARRAY_SIZE(t));
	अगर (ret >= 0)
		ret = be32_to_cpu(st->data[1].d32) & 0xffff;

	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5755_update_dac_ctrl(काष्ठा iio_dev *indio_dev,
	अचिन्हित पूर्णांक channel, अचिन्हित पूर्णांक set, अचिन्हित पूर्णांक clr)
अणु
	काष्ठा ad5755_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	st->ctrl[channel] |= set;
	st->ctrl[channel] &= ~clr;

	ret = ad5755_ग_लिखो_ctrl_unlocked(indio_dev, channel,
		AD5755_CTRL_REG_DAC, st->ctrl[channel]);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5755_set_channel_pwr_करोwn(काष्ठा iio_dev *indio_dev,
	अचिन्हित पूर्णांक channel, bool pwr_करोwn)
अणु
	काष्ठा ad5755_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक mask = BIT(channel);

	mutex_lock(&st->lock);

	अगर ((bool)(st->pwr_करोwn & mask) == pwr_करोwn)
		जाओ out_unlock;

	अगर (!pwr_करोwn) अणु
		st->pwr_करोwn &= ~mask;
		ad5755_update_dac_ctrl(indio_dev, channel,
			AD5755_DAC_INT_EN | AD5755_DAC_DC_DC_EN, 0);
		udelay(200);
		ad5755_update_dac_ctrl(indio_dev, channel,
			AD5755_DAC_OUT_EN, 0);
	पूर्ण अन्यथा अणु
		st->pwr_करोwn |= mask;
		ad5755_update_dac_ctrl(indio_dev, channel,
			0, AD5755_DAC_INT_EN | AD5755_DAC_OUT_EN |
				AD5755_DAC_DC_DC_EN);
	पूर्ण

out_unlock:
	mutex_unlock(&st->lock);

	वापस 0;
पूर्ण

अटल स्थिर पूर्णांक ad5755_min_max_table[][2] = अणु
	[AD5755_MODE_VOLTAGE_0V_5V] = अणु 0, 5000 पूर्ण,
	[AD5755_MODE_VOLTAGE_0V_10V] = अणु 0, 10000 पूर्ण,
	[AD5755_MODE_VOLTAGE_PLUSMINUS_5V] = अणु -5000, 5000 पूर्ण,
	[AD5755_MODE_VOLTAGE_PLUSMINUS_10V] = अणु -10000, 10000 पूर्ण,
	[AD5755_MODE_CURRENT_4mA_20mA] = अणु 4, 20 पूर्ण,
	[AD5755_MODE_CURRENT_0mA_20mA] = अणु 0, 20 पूर्ण,
	[AD5755_MODE_CURRENT_0mA_24mA] = अणु 0, 24 पूर्ण,
पूर्ण;

अटल व्योम ad5755_get_min_max(काष्ठा ad5755_state *st,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *min, पूर्णांक *max)
अणु
	क्रमागत ad5755_mode mode = st->ctrl[chan->channel] & 7;
	*min = ad5755_min_max_table[mode][0];
	*max = ad5755_min_max_table[mode][1];
पूर्ण

अटल अंतरभूत पूर्णांक ad5755_get_offset(काष्ठा ad5755_state *st,
	काष्ठा iio_chan_spec स्थिर *chan)
अणु
	पूर्णांक min, max;

	ad5755_get_min_max(st, chan, &min, &max);
	वापस (min * (1 << chan->scan_type.realbits)) / (max - min);
पूर्ण

अटल पूर्णांक ad5755_chan_reg_info(काष्ठा ad5755_state *st,
	काष्ठा iio_chan_spec स्थिर *chan, दीर्घ info, bool ग_लिखो,
	अचिन्हित पूर्णांक *reg, अचिन्हित पूर्णांक *shअगरt, अचिन्हित पूर्णांक *offset)
अणु
	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (ग_लिखो)
			*reg = AD5755_WRITE_REG_DATA(chan->address);
		अन्यथा
			*reg = AD5755_READ_REG_DATA(chan->address);
		*shअगरt = chan->scan_type.shअगरt;
		*offset = 0;
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		अगर (ग_लिखो)
			*reg = AD5755_WRITE_REG_OFFSET(chan->address);
		अन्यथा
			*reg = AD5755_READ_REG_OFFSET(chan->address);
		*shअगरt = st->chip_info->calib_shअगरt;
		*offset = 32768;
		अवरोध;
	हाल IIO_CHAN_INFO_CALIBSCALE:
		अगर (ग_लिखो)
			*reg =  AD5755_WRITE_REG_GAIN(chan->address);
		अन्यथा
			*reg =  AD5755_READ_REG_GAIN(chan->address);
		*shअगरt = st->chip_info->calib_shअगरt;
		*offset = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ad5755_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	काष्ठा ad5755_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक reg, shअगरt, offset;
	पूर्णांक min, max;
	पूर्णांक ret;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_SCALE:
		ad5755_get_min_max(st, chan, &min, &max);
		*val = max - min;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	हाल IIO_CHAN_INFO_OFFSET:
		*val = ad5755_get_offset(st, chan);
		वापस IIO_VAL_INT;
	शेष:
		ret = ad5755_chan_reg_info(st, chan, info, false,
						&reg, &shअगरt, &offset);
		अगर (ret)
			वापस ret;

		ret = ad5755_पढ़ो(indio_dev, reg);
		अगर (ret < 0)
			वापस ret;

		*val = (ret - offset) >> shअगरt;

		वापस IIO_VAL_INT;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad5755_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, पूर्णांक val, पूर्णांक val2, दीर्घ info)
अणु
	काष्ठा ad5755_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक shअगरt, reg, offset;
	पूर्णांक ret;

	ret = ad5755_chan_reg_info(st, chan, info, true,
					&reg, &shअगरt, &offset);
	अगर (ret)
		वापस ret;

	val <<= shअगरt;
	val += offset;

	अगर (val < 0 || val > 0xffff)
		वापस -EINVAL;

	वापस ad5755_ग_लिखो(indio_dev, reg, val);
पूर्ण

अटल sमाप_प्रकार ad5755_पढ़ो_घातerकरोwn(काष्ठा iio_dev *indio_dev, uपूर्णांकptr_t priv,
	स्थिर काष्ठा iio_chan_spec *chan, अक्षर *buf)
अणु
	काष्ठा ad5755_state *st = iio_priv(indio_dev);

	वापस sysfs_emit(buf, "%d\n",
			  (bool)(st->pwr_करोwn & (1 << chan->channel)));
पूर्ण

अटल sमाप_प्रकार ad5755_ग_लिखो_घातerकरोwn(काष्ठा iio_dev *indio_dev, uपूर्णांकptr_t priv,
	काष्ठा iio_chan_spec स्थिर *chan, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	bool pwr_करोwn;
	पूर्णांक ret;

	ret = strtobool(buf, &pwr_करोwn);
	अगर (ret)
		वापस ret;

	ret = ad5755_set_channel_pwr_करोwn(indio_dev, chan->channel, pwr_करोwn);
	वापस ret ? ret : len;
पूर्ण

अटल स्थिर काष्ठा iio_info ad5755_info = अणु
	.पढ़ो_raw = ad5755_पढ़ो_raw,
	.ग_लिखो_raw = ad5755_ग_लिखो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info ad5755_ext_info[] = अणु
	अणु
		.name = "powerdown",
		.पढ़ो = ad5755_पढ़ो_घातerकरोwn,
		.ग_लिखो = ad5755_ग_लिखो_घातerकरोwn,
		.shared = IIO_SEPARATE,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

#घोषणा AD5755_CHANNEL(_bits) अणु					\
	.indexed = 1,						\
	.output = 1,						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |		\
		BIT(IIO_CHAN_INFO_SCALE) |			\
		BIT(IIO_CHAN_INFO_OFFSET) |			\
		BIT(IIO_CHAN_INFO_CALIBSCALE) |			\
		BIT(IIO_CHAN_INFO_CALIBBIAS),			\
	.scan_type = अणु						\
		.sign = 'u',					\
		.realbits = (_bits),				\
		.storagebits = 16,				\
		.shअगरt = 16 - (_bits),				\
	पूर्ण,							\
	.ext_info = ad5755_ext_info,				\
पूर्ण

अटल स्थिर काष्ठा ad5755_chip_info ad5755_chip_info_tbl[] = अणु
	[ID_AD5735] = अणु
		.channel_ढाँचा = AD5755_CHANNEL(14),
		.has_voltage_out = true,
		.calib_shअगरt = 4,
	पूर्ण,
	[ID_AD5737] = अणु
		.channel_ढाँचा = AD5755_CHANNEL(14),
		.has_voltage_out = false,
		.calib_shअगरt = 4,
	पूर्ण,
	[ID_AD5755] = अणु
		.channel_ढाँचा = AD5755_CHANNEL(16),
		.has_voltage_out = true,
		.calib_shअगरt = 0,
	पूर्ण,
	[ID_AD5757] = अणु
		.channel_ढाँचा = AD5755_CHANNEL(16),
		.has_voltage_out = false,
		.calib_shअगरt = 0,
	पूर्ण,
पूर्ण;

अटल bool ad5755_is_valid_mode(काष्ठा ad5755_state *st, क्रमागत ad5755_mode mode)
अणु
	चयन (mode) अणु
	हाल AD5755_MODE_VOLTAGE_0V_5V:
	हाल AD5755_MODE_VOLTAGE_0V_10V:
	हाल AD5755_MODE_VOLTAGE_PLUSMINUS_5V:
	हाल AD5755_MODE_VOLTAGE_PLUSMINUS_10V:
		वापस st->chip_info->has_voltage_out;
	हाल AD5755_MODE_CURRENT_4mA_20mA:
	हाल AD5755_MODE_CURRENT_0mA_20mA:
	हाल AD5755_MODE_CURRENT_0mA_24mA:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक ad5755_setup_pdata(काष्ठा iio_dev *indio_dev,
			      स्थिर काष्ठा ad5755_platक्रमm_data *pdata)
अणु
	काष्ठा ad5755_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक val;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (pdata->dc_dc_phase > AD5755_DC_DC_PHASE_90_DEGREE ||
		pdata->dc_dc_freq > AD5755_DC_DC_FREQ_650kHZ ||
		pdata->dc_dc_maxv > AD5755_DC_DC_MAXV_29V5)
		वापस -EINVAL;

	val = pdata->dc_dc_maxv << AD5755_DC_DC_MAXV;
	val |= pdata->dc_dc_freq << AD5755_DC_DC_FREQ_SHIFT;
	val |= pdata->dc_dc_phase << AD5755_DC_DC_PHASE_SHIFT;
	अगर (pdata->ext_dc_dc_compenstation_resistor)
		val |= AD5755_EXT_DC_DC_COMP_RES;

	ret = ad5755_ग_लिखो_ctrl(indio_dev, 0, AD5755_CTRL_REG_DC_DC, val);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(pdata->dac); ++i) अणु
		val = pdata->dac[i].slew.step_size <<
			AD5755_SLEW_STEP_SIZE_SHIFT;
		val |= pdata->dac[i].slew.rate <<
			AD5755_SLEW_RATE_SHIFT;
		अगर (pdata->dac[i].slew.enable)
			val |= AD5755_SLEW_ENABLE;

		ret = ad5755_ग_लिखो_ctrl(indio_dev, i,
					AD5755_CTRL_REG_SLEW, val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(pdata->dac); ++i) अणु
		अगर (!ad5755_is_valid_mode(st, pdata->dac[i].mode))
			वापस -EINVAL;

		val = 0;
		अगर (!pdata->dac[i].ext_current_sense_resistor)
			val |= AD5755_DAC_INT_CURRENT_SENSE_RESISTOR;
		अगर (pdata->dac[i].enable_voltage_overrange)
			val |= AD5755_DAC_VOLTAGE_OVERRANGE_EN;
		val |= pdata->dac[i].mode;

		ret = ad5755_update_dac_ctrl(indio_dev, i, val, 0);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool ad5755_is_voltage_mode(क्रमागत ad5755_mode mode)
अणु
	चयन (mode) अणु
	हाल AD5755_MODE_VOLTAGE_0V_5V:
	हाल AD5755_MODE_VOLTAGE_0V_10V:
	हाल AD5755_MODE_VOLTAGE_PLUSMINUS_5V:
	हाल AD5755_MODE_VOLTAGE_PLUSMINUS_10V:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक ad5755_init_channels(काष्ठा iio_dev *indio_dev,
				स्थिर काष्ठा ad5755_platक्रमm_data *pdata)
अणु
	काष्ठा ad5755_state *st = iio_priv(indio_dev);
	काष्ठा iio_chan_spec *channels = st->channels;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < AD5755_NUM_CHANNELS; ++i) अणु
		channels[i] = st->chip_info->channel_ढाँचा;
		channels[i].channel = i;
		channels[i].address = i;
		अगर (pdata && ad5755_is_voltage_mode(pdata->dac[i].mode))
			channels[i].type = IIO_VOLTAGE;
		अन्यथा
			channels[i].type = IIO_CURRENT;
	पूर्ण

	indio_dev->channels = channels;

	वापस 0;
पूर्ण

#घोषणा AD5755_DEFAULT_DAC_PDATA अणु \
		.mode = AD5755_MODE_CURRENT_4mA_20mA, \
		.ext_current_sense_resistor = true, \
		.enable_voltage_overrange = false, \
		.slew = अणु \
			.enable = false, \
			.rate = AD5755_SLEW_RATE_64k, \
			.step_size = AD5755_SLEW_STEP_SIZE_1, \
		पूर्ण, \
	पूर्ण

अटल स्थिर काष्ठा ad5755_platक्रमm_data ad5755_शेष_pdata = अणु
	.ext_dc_dc_compenstation_resistor = false,
	.dc_dc_phase = AD5755_DC_DC_PHASE_ALL_SAME_EDGE,
	.dc_dc_freq = AD5755_DC_DC_FREQ_410kHZ,
	.dc_dc_maxv = AD5755_DC_DC_MAXV_23V,
	.dac = अणु
		[0] = AD5755_DEFAULT_DAC_PDATA,
		[1] = AD5755_DEFAULT_DAC_PDATA,
		[2] = AD5755_DEFAULT_DAC_PDATA,
		[3] = AD5755_DEFAULT_DAC_PDATA,
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_OF
अटल काष्ठा ad5755_platक्रमm_data *ad5755_parse_dt(काष्ठा device *dev)
अणु
	काष्ठा device_node *np = dev->of_node;
	काष्ठा device_node *pp;
	काष्ठा ad5755_platक्रमm_data *pdata;
	अचिन्हित पूर्णांक पंचांगp;
	अचिन्हित पूर्णांक पंचांगparray[3];
	पूर्णांक devnr, i;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस शून्य;

	pdata->ext_dc_dc_compenstation_resistor =
	    of_property_पढ़ो_bool(np, "adi,ext-dc-dc-compenstation-resistor");

	अगर (!of_property_पढ़ो_u32(np, "adi,dc-dc-phase", &पंचांगp))
		pdata->dc_dc_phase = पंचांगp;
	अन्यथा
		pdata->dc_dc_phase = AD5755_DC_DC_PHASE_ALL_SAME_EDGE;

	pdata->dc_dc_freq = AD5755_DC_DC_FREQ_410kHZ;
	अगर (!of_property_पढ़ो_u32(np, "adi,dc-dc-freq-hz", &पंचांगp)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(ad5755_dcdc_freq_table); i++) अणु
			अगर (पंचांगp == ad5755_dcdc_freq_table[i][0]) अणु
				pdata->dc_dc_freq = ad5755_dcdc_freq_table[i][1];
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (i == ARRAY_SIZE(ad5755_dcdc_freq_table))
			dev_err(dev,
				"adi,dc-dc-freq out of range selecting 410kHz\n");
	पूर्ण

	pdata->dc_dc_maxv = AD5755_DC_DC_MAXV_23V;
	अगर (!of_property_पढ़ो_u32(np, "adi,dc-dc-max-microvolt", &पंचांगp)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(ad5755_dcdc_maxv_table); i++) अणु
			अगर (पंचांगp == ad5755_dcdc_maxv_table[i][0]) अणु
				pdata->dc_dc_maxv = ad5755_dcdc_maxv_table[i][1];
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (i == ARRAY_SIZE(ad5755_dcdc_maxv_table))
				dev_err(dev,
					"adi,dc-dc-maxv out of range selecting 23V\n");
	पूर्ण

	devnr = 0;
	क्रम_each_child_of_node(np, pp) अणु
		अगर (devnr >= AD5755_NUM_CHANNELS) अणु
			dev_err(dev,
				"There are too many channels defined in DT\n");
			जाओ error_out;
		पूर्ण

		अगर (!of_property_पढ़ो_u32(pp, "adi,mode", &पंचांगp))
			pdata->dac[devnr].mode = पंचांगp;
		अन्यथा
			pdata->dac[devnr].mode = AD5755_MODE_CURRENT_4mA_20mA;

		pdata->dac[devnr].ext_current_sense_resistor =
		    of_property_पढ़ो_bool(pp, "adi,ext-current-sense-resistor");

		pdata->dac[devnr].enable_voltage_overrange =
		    of_property_पढ़ो_bool(pp, "adi,enable-voltage-overrange");

		अगर (!of_property_पढ़ो_u32_array(pp, "adi,slew", पंचांगparray, 3)) अणु
			pdata->dac[devnr].slew.enable = पंचांगparray[0];

			pdata->dac[devnr].slew.rate = AD5755_SLEW_RATE_64k;
			क्रम (i = 0; i < ARRAY_SIZE(ad5755_slew_rate_table); i++) अणु
				अगर (पंचांगparray[1] == ad5755_slew_rate_table[i][0]) अणु
					pdata->dac[devnr].slew.rate =
						ad5755_slew_rate_table[i][1];
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (i == ARRAY_SIZE(ad5755_slew_rate_table))
				dev_err(dev,
					"channel %d slew rate out of range selecting 64kHz\n",
					devnr);

			pdata->dac[devnr].slew.step_size = AD5755_SLEW_STEP_SIZE_1;
			क्रम (i = 0; i < ARRAY_SIZE(ad5755_slew_step_table); i++) अणु
				अगर (पंचांगparray[2] == ad5755_slew_step_table[i][0]) अणु
					pdata->dac[devnr].slew.step_size =
						ad5755_slew_step_table[i][1];
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (i == ARRAY_SIZE(ad5755_slew_step_table))
				dev_err(dev,
					"channel %d slew step size out of range selecting 1 LSB\n",
					devnr);
		पूर्ण अन्यथा अणु
			pdata->dac[devnr].slew.enable = false;
			pdata->dac[devnr].slew.rate = AD5755_SLEW_RATE_64k;
			pdata->dac[devnr].slew.step_size =
			    AD5755_SLEW_STEP_SIZE_1;
		पूर्ण
		devnr++;
	पूर्ण

	वापस pdata;

 error_out:
	devm_kमुक्त(dev, pdata);
	वापस शून्य;
पूर्ण
#अन्यथा
अटल
काष्ठा ad5755_platक्रमm_data *ad5755_parse_dt(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ad5755_probe(काष्ठा spi_device *spi)
अणु
	क्रमागत ad5755_type type = spi_get_device_id(spi)->driver_data;
	स्थिर काष्ठा ad5755_platक्रमm_data *pdata = dev_get_platdata(&spi->dev);
	काष्ठा iio_dev *indio_dev;
	काष्ठा ad5755_state *st;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*st));
	अगर (indio_dev == शून्य) अणु
		dev_err(&spi->dev, "Failed to allocate iio device\n");
		वापस  -ENOMEM;
	पूर्ण

	st = iio_priv(indio_dev);
	spi_set_drvdata(spi, indio_dev);

	st->chip_info = &ad5755_chip_info_tbl[type];
	st->spi = spi;
	st->pwr_करोwn = 0xf;

	indio_dev->name = spi_get_device_id(spi)->name;
	indio_dev->info = &ad5755_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->num_channels = AD5755_NUM_CHANNELS;

	mutex_init(&st->lock);

	अगर (spi->dev.of_node)
		pdata = ad5755_parse_dt(&spi->dev);
	अन्यथा
		pdata = spi->dev.platक्रमm_data;

	अगर (!pdata) अणु
		dev_warn(&spi->dev, "no platform data? using default\n");
		pdata = &ad5755_शेष_pdata;
	पूर्ण

	ret = ad5755_init_channels(indio_dev, pdata);
	अगर (ret)
		वापस ret;

	ret = ad5755_setup_pdata(indio_dev, pdata);
	अगर (ret)
		वापस ret;

	वापस devm_iio_device_रेजिस्टर(&spi->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad5755_id[] = अणु
	अणु "ad5755", ID_AD5755 पूर्ण,
	अणु "ad5755-1", ID_AD5755 पूर्ण,
	अणु "ad5757", ID_AD5757 पूर्ण,
	अणु "ad5735", ID_AD5735 पूर्ण,
	अणु "ad5737", ID_AD5737 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad5755_id);

अटल स्थिर काष्ठा of_device_id ad5755_of_match[] = अणु
	अणु .compatible = "adi,ad5755" पूर्ण,
	अणु .compatible = "adi,ad5755-1" पूर्ण,
	अणु .compatible = "adi,ad5757" पूर्ण,
	अणु .compatible = "adi,ad5735" पूर्ण,
	अणु .compatible = "adi,ad5737" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ad5755_of_match);

अटल काष्ठा spi_driver ad5755_driver = अणु
	.driver = अणु
		.name = "ad5755",
	पूर्ण,
	.probe = ad5755_probe,
	.id_table = ad5755_id,
पूर्ण;
module_spi_driver(ad5755_driver);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Analog Devices AD5755/55-1/57/35/37 DAC");
MODULE_LICENSE("GPL v2");
