<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AD5024, AD5025, AD5044, AD5045, AD5064, AD5064-1, AD5065, AD5625, AD5625R,
 * AD5627, AD5627R, AD5628, AD5629R, AD5645R, AD5647R, AD5648, AD5665, AD5665R,
 * AD5666, AD5667, AD5667R, AD5668, AD5669R, LTC2606, LTC2607, LTC2609, LTC2616,
 * LTC2617, LTC2619, LTC2626, LTC2627, LTC2629, LTC2631, LTC2633, LTC2635
 * Digital to analog converters driver
 *
 * Copyright 2011 Analog Devices Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा AD5064_MAX_DAC_CHANNELS			8
#घोषणा AD5064_MAX_VREFS			4

#घोषणा AD5064_ADDR(x)				((x) << 20)
#घोषणा AD5064_CMD(x)				((x) << 24)

#घोषणा AD5064_ADDR_ALL_DAC			0xF

#घोषणा AD5064_CMD_WRITE_INPUT_N		0x0
#घोषणा AD5064_CMD_UPDATE_DAC_N			0x1
#घोषणा AD5064_CMD_WRITE_INPUT_N_UPDATE_ALL	0x2
#घोषणा AD5064_CMD_WRITE_INPUT_N_UPDATE_N	0x3
#घोषणा AD5064_CMD_POWERDOWN_DAC		0x4
#घोषणा AD5064_CMD_CLEAR			0x5
#घोषणा AD5064_CMD_LDAC_MASK			0x6
#घोषणा AD5064_CMD_RESET			0x7
#घोषणा AD5064_CMD_CONFIG			0x8

#घोषणा AD5064_CMD_RESET_V2			0x5
#घोषणा AD5064_CMD_CONFIG_V2			0x7

#घोषणा AD5064_CONFIG_DAISY_CHAIN_ENABLE	BIT(1)
#घोषणा AD5064_CONFIG_INT_VREF_ENABLE		BIT(0)

#घोषणा AD5064_LDAC_PWRDN_NONE			0x0
#घोषणा AD5064_LDAC_PWRDN_1K			0x1
#घोषणा AD5064_LDAC_PWRDN_100K			0x2
#घोषणा AD5064_LDAC_PWRDN_3STATE		0x3

/**
 * क्रमागत ad5064_regmap_type - Register layout variant
 * @AD5064_REGMAP_ADI: Old Analog Devices रेजिस्टर map layout
 * @AD5064_REGMAP_ADI2: New Analog Devices रेजिस्टर map layout
 * @AD5064_REGMAP_LTC: LTC रेजिस्टर map layout
 */
क्रमागत ad5064_regmap_type अणु
	AD5064_REGMAP_ADI,
	AD5064_REGMAP_ADI2,
	AD5064_REGMAP_LTC,
पूर्ण;

/**
 * काष्ठा ad5064_chip_info - chip specअगरic inक्रमmation
 * @shared_vref:	whether the vref supply is shared between channels
 * @पूर्णांकernal_vref:	पूर्णांकernal reference voltage. 0 अगर the chip has no
 *			पूर्णांकernal vref.
 * @channels:		channel specअगरication
 * @num_channels:	number of channels
 * @regmap_type:	रेजिस्टर map layout variant
 */

काष्ठा ad5064_chip_info अणु
	bool shared_vref;
	अचिन्हित दीर्घ पूर्णांकernal_vref;
	स्थिर काष्ठा iio_chan_spec *channels;
	अचिन्हित पूर्णांक num_channels;
	क्रमागत ad5064_regmap_type regmap_type;
पूर्ण;

काष्ठा ad5064_state;

प्रकार पूर्णांक (*ad5064_ग_लिखो_func)(काष्ठा ad5064_state *st, अचिन्हित पूर्णांक cmd,
		अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक val);

/**
 * काष्ठा ad5064_state - driver instance specअगरic data
 * @dev:		the device क्रम this driver instance
 * @chip_info:		chip model specअगरic स्थिरants, available modes etc
 * @vref_reg:		vref supply regulators
 * @pwr_करोwn:		whether channel is घातered करोwn
 * @pwr_करोwn_mode:	channel's current घातer करोwn mode
 * @dac_cache:		current DAC raw value (chip करोes not support पढ़ोback)
 * @use_पूर्णांकernal_vref:	set to true अगर the पूर्णांकernal reference voltage should be
 *			used.
 * @ग_लिखो:		रेजिस्टर ग_लिखो callback
 * @lock:		मुख्यtain consistency between cached and dev state
 * @data:		i2c/spi transfer buffers
 */

काष्ठा ad5064_state अणु
	काष्ठा device			*dev;
	स्थिर काष्ठा ad5064_chip_info	*chip_info;
	काष्ठा regulator_bulk_data	vref_reg[AD5064_MAX_VREFS];
	bool				pwr_करोwn[AD5064_MAX_DAC_CHANNELS];
	u8				pwr_करोwn_mode[AD5064_MAX_DAC_CHANNELS];
	अचिन्हित पूर्णांक			dac_cache[AD5064_MAX_DAC_CHANNELS];
	bool				use_पूर्णांकernal_vref;

	ad5064_ग_लिखो_func		ग_लिखो;
	काष्ठा mutex lock;

	/*
	 * DMA (thus cache coherency मुख्यtenance) requires the
	 * transfer buffers to live in their own cache lines.
	 */
	जोड़ अणु
		u8 i2c[3];
		__be32 spi;
	पूर्ण data ____cacheline_aligned;
पूर्ण;

क्रमागत ad5064_type अणु
	ID_AD5024,
	ID_AD5025,
	ID_AD5044,
	ID_AD5045,
	ID_AD5064,
	ID_AD5064_1,
	ID_AD5065,
	ID_AD5625,
	ID_AD5625R_1V25,
	ID_AD5625R_2V5,
	ID_AD5627,
	ID_AD5627R_1V25,
	ID_AD5627R_2V5,
	ID_AD5628_1,
	ID_AD5628_2,
	ID_AD5629_1,
	ID_AD5629_2,
	ID_AD5645R_1V25,
	ID_AD5645R_2V5,
	ID_AD5647R_1V25,
	ID_AD5647R_2V5,
	ID_AD5648_1,
	ID_AD5648_2,
	ID_AD5665,
	ID_AD5665R_1V25,
	ID_AD5665R_2V5,
	ID_AD5666_1,
	ID_AD5666_2,
	ID_AD5667,
	ID_AD5667R_1V25,
	ID_AD5667R_2V5,
	ID_AD5668_1,
	ID_AD5668_2,
	ID_AD5669_1,
	ID_AD5669_2,
	ID_LTC2606,
	ID_LTC2607,
	ID_LTC2609,
	ID_LTC2616,
	ID_LTC2617,
	ID_LTC2619,
	ID_LTC2626,
	ID_LTC2627,
	ID_LTC2629,
	ID_LTC2631_L12,
	ID_LTC2631_H12,
	ID_LTC2631_L10,
	ID_LTC2631_H10,
	ID_LTC2631_L8,
	ID_LTC2631_H8,
	ID_LTC2633_L12,
	ID_LTC2633_H12,
	ID_LTC2633_L10,
	ID_LTC2633_H10,
	ID_LTC2633_L8,
	ID_LTC2633_H8,
	ID_LTC2635_L12,
	ID_LTC2635_H12,
	ID_LTC2635_L10,
	ID_LTC2635_H10,
	ID_LTC2635_L8,
	ID_LTC2635_H8,
पूर्ण;

अटल पूर्णांक ad5064_ग_लिखो(काष्ठा ad5064_state *st, अचिन्हित पूर्णांक cmd,
	अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक shअगरt)
अणु
	val <<= shअगरt;

	वापस st->ग_लिखो(st, cmd, addr, val);
पूर्ण

अटल पूर्णांक ad5064_sync_घातerकरोwn_mode(काष्ठा ad5064_state *st,
	स्थिर काष्ठा iio_chan_spec *chan)
अणु
	अचिन्हित पूर्णांक val, address;
	अचिन्हित पूर्णांक shअगरt;
	पूर्णांक ret;

	अगर (st->chip_info->regmap_type == AD5064_REGMAP_LTC) अणु
		val = 0;
		address = chan->address;
	पूर्ण अन्यथा अणु
		अगर (st->chip_info->regmap_type == AD5064_REGMAP_ADI2)
			shअगरt = 4;
		अन्यथा
			shअगरt = 8;

		val = (0x1 << chan->address);
		address = 0;

		अगर (st->pwr_करोwn[chan->channel])
			val |= st->pwr_करोwn_mode[chan->channel] << shअगरt;
	पूर्ण

	ret = ad5064_ग_लिखो(st, AD5064_CMD_POWERDOWN_DAC, address, val, 0);

	वापस ret;
पूर्ण

अटल स्थिर अक्षर * स्थिर ad5064_घातerकरोwn_modes[] = अणु
	"1kohm_to_gnd",
	"100kohm_to_gnd",
	"three_state",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ltc2617_घातerकरोwn_modes[] = अणु
	"90kohm_to_gnd",
पूर्ण;

अटल पूर्णांक ad5064_get_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा ad5064_state *st = iio_priv(indio_dev);

	वापस st->pwr_करोwn_mode[chan->channel] - 1;
पूर्ण

अटल पूर्णांक ad5064_set_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा ad5064_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&st->lock);
	st->pwr_करोwn_mode[chan->channel] = mode + 1;

	ret = ad5064_sync_घातerकरोwn_mode(st, chan);
	mutex_unlock(&st->lock);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_क्रमागत ad5064_घातerकरोwn_mode_क्रमागत = अणु
	.items = ad5064_घातerकरोwn_modes,
	.num_items = ARRAY_SIZE(ad5064_घातerकरोwn_modes),
	.get = ad5064_get_घातerकरोwn_mode,
	.set = ad5064_set_घातerकरोwn_mode,
पूर्ण;

अटल स्थिर काष्ठा iio_क्रमागत ltc2617_घातerकरोwn_mode_क्रमागत = अणु
	.items = ltc2617_घातerकरोwn_modes,
	.num_items = ARRAY_SIZE(ltc2617_घातerकरोwn_modes),
	.get = ad5064_get_घातerकरोwn_mode,
	.set = ad5064_set_घातerकरोwn_mode,
पूर्ण;

अटल sमाप_प्रकार ad5064_पढ़ो_dac_घातerकरोwn(काष्ठा iio_dev *indio_dev,
	uपूर्णांकptr_t निजी, स्थिर काष्ठा iio_chan_spec *chan, अक्षर *buf)
अणु
	काष्ठा ad5064_state *st = iio_priv(indio_dev);

	वापस sysfs_emit(buf, "%d\n", st->pwr_करोwn[chan->channel]);
पूर्ण

अटल sमाप_प्रकार ad5064_ग_लिखो_dac_घातerकरोwn(काष्ठा iio_dev *indio_dev,
	 uपूर्णांकptr_t निजी, स्थिर काष्ठा iio_chan_spec *chan, स्थिर अक्षर *buf,
	 माप_प्रकार len)
अणु
	काष्ठा ad5064_state *st = iio_priv(indio_dev);
	bool pwr_करोwn;
	पूर्णांक ret;

	ret = strtobool(buf, &pwr_करोwn);
	अगर (ret)
		वापस ret;

	mutex_lock(&st->lock);
	st->pwr_करोwn[chan->channel] = pwr_करोwn;

	ret = ad5064_sync_घातerकरोwn_mode(st, chan);
	mutex_unlock(&st->lock);
	वापस ret ? ret : len;
पूर्ण

अटल पूर्णांक ad5064_get_vref(काष्ठा ad5064_state *st,
	काष्ठा iio_chan_spec स्थिर *chan)
अणु
	अचिन्हित पूर्णांक i;

	अगर (st->use_पूर्णांकernal_vref)
		वापस st->chip_info->पूर्णांकernal_vref;

	i = st->chip_info->shared_vref ? 0 : chan->channel;
	वापस regulator_get_voltage(st->vref_reg[i].consumer);
पूर्ण

अटल पूर्णांक ad5064_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	काष्ठा ad5064_state *st = iio_priv(indio_dev);
	पूर्णांक scale_uv;

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		*val = st->dac_cache[chan->channel];
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		scale_uv = ad5064_get_vref(st, chan);
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

अटल पूर्णांक ad5064_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा ad5064_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (val >= (1 << chan->scan_type.realbits) || val < 0)
			वापस -EINVAL;

		mutex_lock(&st->lock);
		ret = ad5064_ग_लिखो(st, AD5064_CMD_WRITE_INPUT_N_UPDATE_N,
				chan->address, val, chan->scan_type.shअगरt);
		अगर (ret == 0)
			st->dac_cache[chan->channel] = val;
		mutex_unlock(&st->lock);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info ad5064_info = अणु
	.पढ़ो_raw = ad5064_पढ़ो_raw,
	.ग_लिखो_raw = ad5064_ग_लिखो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info ad5064_ext_info[] = अणु
	अणु
		.name = "powerdown",
		.पढ़ो = ad5064_पढ़ो_dac_घातerकरोwn,
		.ग_लिखो = ad5064_ग_लिखो_dac_घातerकरोwn,
		.shared = IIO_SEPARATE,
	पूर्ण,
	IIO_ENUM("powerdown_mode", IIO_SEPARATE, &ad5064_घातerकरोwn_mode_क्रमागत),
	IIO_ENUM_AVAILABLE("powerdown_mode", &ad5064_घातerकरोwn_mode_क्रमागत),
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info ltc2617_ext_info[] = अणु
	अणु
		.name = "powerdown",
		.पढ़ो = ad5064_पढ़ो_dac_घातerकरोwn,
		.ग_लिखो = ad5064_ग_लिखो_dac_घातerकरोwn,
		.shared = IIO_SEPARATE,
	पूर्ण,
	IIO_ENUM("powerdown_mode", IIO_SEPARATE, &ltc2617_घातerकरोwn_mode_क्रमागत),
	IIO_ENUM_AVAILABLE("powerdown_mode", &ltc2617_घातerकरोwn_mode_क्रमागत),
	अणु पूर्ण,
पूर्ण;

#घोषणा AD5064_CHANNEL(chan, addr, bits, _shअगरt, _ext_info) अणु		\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.output = 1,						\
	.channel = (chan),					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |		\
	BIT(IIO_CHAN_INFO_SCALE),					\
	.address = addr,					\
	.scan_type = अणु						\
		.sign = 'u',					\
		.realbits = (bits),				\
		.storagebits = 16,				\
		.shअगरt = (_shअगरt),				\
	पूर्ण,							\
	.ext_info = (_ext_info),				\
पूर्ण

#घोषणा DECLARE_AD5064_CHANNELS(name, bits, shअगरt, ext_info) \
स्थिर काष्ठा iio_chan_spec name[] = अणु \
	AD5064_CHANNEL(0, 0, bits, shअगरt, ext_info), \
	AD5064_CHANNEL(1, 1, bits, shअगरt, ext_info), \
	AD5064_CHANNEL(2, 2, bits, shअगरt, ext_info), \
	AD5064_CHANNEL(3, 3, bits, shअगरt, ext_info), \
	AD5064_CHANNEL(4, 4, bits, shअगरt, ext_info), \
	AD5064_CHANNEL(5, 5, bits, shअगरt, ext_info), \
	AD5064_CHANNEL(6, 6, bits, shअगरt, ext_info), \
	AD5064_CHANNEL(7, 7, bits, shअगरt, ext_info), \
पूर्ण

#घोषणा DECLARE_AD5065_CHANNELS(name, bits, shअगरt, ext_info) \
स्थिर काष्ठा iio_chan_spec name[] = अणु \
	AD5064_CHANNEL(0, 0, bits, shअगरt, ext_info), \
	AD5064_CHANNEL(1, 3, bits, shअगरt, ext_info), \
पूर्ण

अटल DECLARE_AD5064_CHANNELS(ad5024_channels, 12, 8, ad5064_ext_info);
अटल DECLARE_AD5064_CHANNELS(ad5044_channels, 14, 6, ad5064_ext_info);
अटल DECLARE_AD5064_CHANNELS(ad5064_channels, 16, 4, ad5064_ext_info);

अटल DECLARE_AD5065_CHANNELS(ad5025_channels, 12, 8, ad5064_ext_info);
अटल DECLARE_AD5065_CHANNELS(ad5045_channels, 14, 6, ad5064_ext_info);
अटल DECLARE_AD5065_CHANNELS(ad5065_channels, 16, 4, ad5064_ext_info);

अटल DECLARE_AD5064_CHANNELS(ad5629_channels, 12, 4, ad5064_ext_info);
अटल DECLARE_AD5064_CHANNELS(ad5645_channels, 14, 2, ad5064_ext_info);
अटल DECLARE_AD5064_CHANNELS(ad5669_channels, 16, 0, ad5064_ext_info);

अटल DECLARE_AD5064_CHANNELS(ltc2607_channels, 16, 0, ltc2617_ext_info);
अटल DECLARE_AD5064_CHANNELS(ltc2617_channels, 14, 2, ltc2617_ext_info);
अटल DECLARE_AD5064_CHANNELS(ltc2627_channels, 12, 4, ltc2617_ext_info);
#घोषणा ltc2631_12_channels ltc2627_channels
अटल DECLARE_AD5064_CHANNELS(ltc2631_10_channels, 10, 6, ltc2617_ext_info);
अटल DECLARE_AD5064_CHANNELS(ltc2631_8_channels, 8, 8, ltc2617_ext_info);

#घोषणा LTC2631_INFO(vref, pchannels, nchannels)	\
	अणु						\
		.shared_vref = true,			\
		.पूर्णांकernal_vref = vref,			\
		.channels = pchannels,			\
		.num_channels = nchannels,		\
		.regmap_type = AD5064_REGMAP_LTC,	\
	पूर्ण


अटल स्थिर काष्ठा ad5064_chip_info ad5064_chip_info_tbl[] = अणु
	[ID_AD5024] = अणु
		.shared_vref = false,
		.channels = ad5024_channels,
		.num_channels = 4,
		.regmap_type = AD5064_REGMAP_ADI,
	पूर्ण,
	[ID_AD5025] = अणु
		.shared_vref = false,
		.channels = ad5025_channels,
		.num_channels = 2,
		.regmap_type = AD5064_REGMAP_ADI,
	पूर्ण,
	[ID_AD5044] = अणु
		.shared_vref = false,
		.channels = ad5044_channels,
		.num_channels = 4,
		.regmap_type = AD5064_REGMAP_ADI,
	पूर्ण,
	[ID_AD5045] = अणु
		.shared_vref = false,
		.channels = ad5045_channels,
		.num_channels = 2,
		.regmap_type = AD5064_REGMAP_ADI,
	पूर्ण,
	[ID_AD5064] = अणु
		.shared_vref = false,
		.channels = ad5064_channels,
		.num_channels = 4,
		.regmap_type = AD5064_REGMAP_ADI,
	पूर्ण,
	[ID_AD5064_1] = अणु
		.shared_vref = true,
		.channels = ad5064_channels,
		.num_channels = 4,
		.regmap_type = AD5064_REGMAP_ADI,
	पूर्ण,
	[ID_AD5065] = अणु
		.shared_vref = false,
		.channels = ad5065_channels,
		.num_channels = 2,
		.regmap_type = AD5064_REGMAP_ADI,
	पूर्ण,
	[ID_AD5625] = अणु
		.shared_vref = true,
		.channels = ad5629_channels,
		.num_channels = 4,
		.regmap_type = AD5064_REGMAP_ADI2
	पूर्ण,
	[ID_AD5625R_1V25] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 1250000,
		.channels = ad5629_channels,
		.num_channels = 4,
		.regmap_type = AD5064_REGMAP_ADI2
	पूर्ण,
	[ID_AD5625R_2V5] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 2500000,
		.channels = ad5629_channels,
		.num_channels = 4,
		.regmap_type = AD5064_REGMAP_ADI2
	पूर्ण,
	[ID_AD5627] = अणु
		.shared_vref = true,
		.channels = ad5629_channels,
		.num_channels = 2,
		.regmap_type = AD5064_REGMAP_ADI2
	पूर्ण,
	[ID_AD5627R_1V25] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 1250000,
		.channels = ad5629_channels,
		.num_channels = 2,
		.regmap_type = AD5064_REGMAP_ADI2
	पूर्ण,
	[ID_AD5627R_2V5] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 2500000,
		.channels = ad5629_channels,
		.num_channels = 2,
		.regmap_type = AD5064_REGMAP_ADI2
	पूर्ण,
	[ID_AD5628_1] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 2500000,
		.channels = ad5024_channels,
		.num_channels = 8,
		.regmap_type = AD5064_REGMAP_ADI,
	पूर्ण,
	[ID_AD5628_2] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 5000000,
		.channels = ad5024_channels,
		.num_channels = 8,
		.regmap_type = AD5064_REGMAP_ADI,
	पूर्ण,
	[ID_AD5629_1] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 2500000,
		.channels = ad5629_channels,
		.num_channels = 8,
		.regmap_type = AD5064_REGMAP_ADI,
	पूर्ण,
	[ID_AD5629_2] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 5000000,
		.channels = ad5629_channels,
		.num_channels = 8,
		.regmap_type = AD5064_REGMAP_ADI,
	पूर्ण,
	[ID_AD5645R_1V25] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 1250000,
		.channels = ad5645_channels,
		.num_channels = 4,
		.regmap_type = AD5064_REGMAP_ADI2
	पूर्ण,
	[ID_AD5645R_2V5] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 2500000,
		.channels = ad5645_channels,
		.num_channels = 4,
		.regmap_type = AD5064_REGMAP_ADI2
	पूर्ण,
	[ID_AD5647R_1V25] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 1250000,
		.channels = ad5645_channels,
		.num_channels = 2,
		.regmap_type = AD5064_REGMAP_ADI2
	पूर्ण,
	[ID_AD5647R_2V5] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 2500000,
		.channels = ad5645_channels,
		.num_channels = 2,
		.regmap_type = AD5064_REGMAP_ADI2
	पूर्ण,
	[ID_AD5648_1] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 2500000,
		.channels = ad5044_channels,
		.num_channels = 8,
		.regmap_type = AD5064_REGMAP_ADI,
	पूर्ण,
	[ID_AD5648_2] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 5000000,
		.channels = ad5044_channels,
		.num_channels = 8,
		.regmap_type = AD5064_REGMAP_ADI,
	पूर्ण,
	[ID_AD5665] = अणु
		.shared_vref = true,
		.channels = ad5669_channels,
		.num_channels = 4,
		.regmap_type = AD5064_REGMAP_ADI2
	पूर्ण,
	[ID_AD5665R_1V25] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 1250000,
		.channels = ad5669_channels,
		.num_channels = 4,
		.regmap_type = AD5064_REGMAP_ADI2
	पूर्ण,
	[ID_AD5665R_2V5] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 2500000,
		.channels = ad5669_channels,
		.num_channels = 4,
		.regmap_type = AD5064_REGMAP_ADI2
	पूर्ण,
	[ID_AD5666_1] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 2500000,
		.channels = ad5064_channels,
		.num_channels = 4,
		.regmap_type = AD5064_REGMAP_ADI,
	पूर्ण,
	[ID_AD5666_2] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 5000000,
		.channels = ad5064_channels,
		.num_channels = 4,
		.regmap_type = AD5064_REGMAP_ADI,
	पूर्ण,
	[ID_AD5667] = अणु
		.shared_vref = true,
		.channels = ad5669_channels,
		.num_channels = 2,
		.regmap_type = AD5064_REGMAP_ADI2
	पूर्ण,
	[ID_AD5667R_1V25] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 1250000,
		.channels = ad5669_channels,
		.num_channels = 2,
		.regmap_type = AD5064_REGMAP_ADI2
	पूर्ण,
	[ID_AD5667R_2V5] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 2500000,
		.channels = ad5669_channels,
		.num_channels = 2,
		.regmap_type = AD5064_REGMAP_ADI2
	पूर्ण,
	[ID_AD5668_1] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 2500000,
		.channels = ad5064_channels,
		.num_channels = 8,
		.regmap_type = AD5064_REGMAP_ADI,
	पूर्ण,
	[ID_AD5668_2] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 5000000,
		.channels = ad5064_channels,
		.num_channels = 8,
		.regmap_type = AD5064_REGMAP_ADI,
	पूर्ण,
	[ID_AD5669_1] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 2500000,
		.channels = ad5669_channels,
		.num_channels = 8,
		.regmap_type = AD5064_REGMAP_ADI,
	पूर्ण,
	[ID_AD5669_2] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 5000000,
		.channels = ad5669_channels,
		.num_channels = 8,
		.regmap_type = AD5064_REGMAP_ADI,
	पूर्ण,
	[ID_LTC2606] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 0,
		.channels = ltc2607_channels,
		.num_channels = 1,
		.regmap_type = AD5064_REGMAP_LTC,
	पूर्ण,
	[ID_LTC2607] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 0,
		.channels = ltc2607_channels,
		.num_channels = 2,
		.regmap_type = AD5064_REGMAP_LTC,
	पूर्ण,
	[ID_LTC2609] = अणु
		.shared_vref = false,
		.पूर्णांकernal_vref = 0,
		.channels = ltc2607_channels,
		.num_channels = 4,
		.regmap_type = AD5064_REGMAP_LTC,
	पूर्ण,
	[ID_LTC2616] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 0,
		.channels = ltc2617_channels,
		.num_channels = 1,
		.regmap_type = AD5064_REGMAP_LTC,
	पूर्ण,
	[ID_LTC2617] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 0,
		.channels = ltc2617_channels,
		.num_channels = 2,
		.regmap_type = AD5064_REGMAP_LTC,
	पूर्ण,
	[ID_LTC2619] = अणु
		.shared_vref = false,
		.पूर्णांकernal_vref = 0,
		.channels = ltc2617_channels,
		.num_channels = 4,
		.regmap_type = AD5064_REGMAP_LTC,
	पूर्ण,
	[ID_LTC2626] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 0,
		.channels = ltc2627_channels,
		.num_channels = 1,
		.regmap_type = AD5064_REGMAP_LTC,
	पूर्ण,
	[ID_LTC2627] = अणु
		.shared_vref = true,
		.पूर्णांकernal_vref = 0,
		.channels = ltc2627_channels,
		.num_channels = 2,
		.regmap_type = AD5064_REGMAP_LTC,
	पूर्ण,
	[ID_LTC2629] = अणु
		.shared_vref = false,
		.पूर्णांकernal_vref = 0,
		.channels = ltc2627_channels,
		.num_channels = 4,
		.regmap_type = AD5064_REGMAP_LTC,
	पूर्ण,
	[ID_LTC2631_L12] = LTC2631_INFO(2500000, ltc2631_12_channels, 1),
	[ID_LTC2631_H12] = LTC2631_INFO(4096000, ltc2631_12_channels, 1),
	[ID_LTC2631_L10] = LTC2631_INFO(2500000, ltc2631_10_channels, 1),
	[ID_LTC2631_H10] = LTC2631_INFO(4096000, ltc2631_10_channels, 1),
	[ID_LTC2631_L8] = LTC2631_INFO(2500000, ltc2631_8_channels, 1),
	[ID_LTC2631_H8] = LTC2631_INFO(4096000, ltc2631_8_channels, 1),
	[ID_LTC2633_L12] = LTC2631_INFO(2500000, ltc2631_12_channels, 2),
	[ID_LTC2633_H12] = LTC2631_INFO(4096000, ltc2631_12_channels, 2),
	[ID_LTC2633_L10] = LTC2631_INFO(2500000, ltc2631_10_channels, 2),
	[ID_LTC2633_H10] = LTC2631_INFO(4096000, ltc2631_10_channels, 2),
	[ID_LTC2633_L8] = LTC2631_INFO(2500000, ltc2631_8_channels, 2),
	[ID_LTC2633_H8] = LTC2631_INFO(4096000, ltc2631_8_channels, 2),
	[ID_LTC2635_L12] = LTC2631_INFO(2500000, ltc2631_12_channels, 4),
	[ID_LTC2635_H12] = LTC2631_INFO(4096000, ltc2631_12_channels, 4),
	[ID_LTC2635_L10] = LTC2631_INFO(2500000, ltc2631_10_channels, 4),
	[ID_LTC2635_H10] = LTC2631_INFO(4096000, ltc2631_10_channels, 4),
	[ID_LTC2635_L8] = LTC2631_INFO(2500000, ltc2631_8_channels, 4),
	[ID_LTC2635_H8] = LTC2631_INFO(4096000, ltc2631_8_channels, 4),
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक ad5064_num_vref(काष्ठा ad5064_state *st)
अणु
	वापस st->chip_info->shared_vref ? 1 : st->chip_info->num_channels;
पूर्ण

अटल स्थिर अक्षर * स्थिर ad5064_vref_names[] = अणु
	"vrefA",
	"vrefB",
	"vrefC",
	"vrefD",
पूर्ण;

अटल स्थिर अक्षर *ad5064_vref_name(काष्ठा ad5064_state *st,
	अचिन्हित पूर्णांक vref)
अणु
	वापस st->chip_info->shared_vref ? "vref" : ad5064_vref_names[vref];
पूर्ण

अटल पूर्णांक ad5064_set_config(काष्ठा ad5064_state *st, अचिन्हित पूर्णांक val)
अणु
	अचिन्हित पूर्णांक cmd;

	चयन (st->chip_info->regmap_type) अणु
	हाल AD5064_REGMAP_ADI2:
		cmd = AD5064_CMD_CONFIG_V2;
		अवरोध;
	शेष:
		cmd = AD5064_CMD_CONFIG;
		अवरोध;
	पूर्ण

	वापस ad5064_ग_लिखो(st, cmd, 0, val, 0);
पूर्ण

अटल पूर्णांक ad5064_request_vref(काष्ठा ad5064_state *st, काष्ठा device *dev)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ad5064_num_vref(st); ++i)
		st->vref_reg[i].supply = ad5064_vref_name(st, i);

	अगर (!st->chip_info->पूर्णांकernal_vref)
		वापस devm_regulator_bulk_get(dev, ad5064_num_vref(st),
					       st->vref_reg);

	/*
	 * This assumes that when the regulator has an पूर्णांकernal VREF
	 * there is only one बाह्यal VREF connection, which is
	 * currently the हाल क्रम all supported devices.
	 */
	st->vref_reg[0].consumer = devm_regulator_get_optional(dev, "vref");
	अगर (!IS_ERR(st->vref_reg[0].consumer))
		वापस 0;

	ret = PTR_ERR(st->vref_reg[0].consumer);
	अगर (ret != -ENODEV)
		वापस ret;

	/* If no बाह्यal regulator was supplied use the पूर्णांकernal VREF */
	st->use_पूर्णांकernal_vref = true;
	ret = ad5064_set_config(st, AD5064_CONFIG_INT_VREF_ENABLE);
	अगर (ret)
		dev_err(dev, "Failed to enable internal vref: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5064_probe(काष्ठा device *dev, क्रमागत ad5064_type type,
			स्थिर अक्षर *name, ad5064_ग_लिखो_func ग_लिखो)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा ad5064_state *st;
	अचिन्हित पूर्णांक midscale;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*st));
	अगर (indio_dev == शून्य)
		वापस  -ENOMEM;

	st = iio_priv(indio_dev);
	mutex_init(&st->lock);
	dev_set_drvdata(dev, indio_dev);

	st->chip_info = &ad5064_chip_info_tbl[type];
	st->dev = dev;
	st->ग_लिखो = ग_लिखो;

	ret = ad5064_request_vref(st, dev);
	अगर (ret)
		वापस ret;

	अगर (!st->use_पूर्णांकernal_vref) अणु
		ret = regulator_bulk_enable(ad5064_num_vref(st), st->vref_reg);
		अगर (ret)
			वापस ret;
	पूर्ण

	indio_dev->name = name;
	indio_dev->info = &ad5064_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = st->chip_info->channels;
	indio_dev->num_channels = st->chip_info->num_channels;

	midscale = (1 << indio_dev->channels[0].scan_type.realbits) /  2;

	क्रम (i = 0; i < st->chip_info->num_channels; ++i) अणु
		st->pwr_करोwn_mode[i] = AD5064_LDAC_PWRDN_1K;
		st->dac_cache[i] = midscale;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_disable_reg;

	वापस 0;

error_disable_reg:
	अगर (!st->use_पूर्णांकernal_vref)
		regulator_bulk_disable(ad5064_num_vref(st), st->vref_reg);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5064_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा ad5064_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	अगर (!st->use_पूर्णांकernal_vref)
		regulator_bulk_disable(ad5064_num_vref(st), st->vref_reg);

	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_SPI_MASTER)

अटल पूर्णांक ad5064_spi_ग_लिखो(काष्ठा ad5064_state *st, अचिन्हित पूर्णांक cmd,
	अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक val)
अणु
	काष्ठा spi_device *spi = to_spi_device(st->dev);

	st->data.spi = cpu_to_be32(AD5064_CMD(cmd) | AD5064_ADDR(addr) | val);
	वापस spi_ग_लिखो(spi, &st->data.spi, माप(st->data.spi));
पूर्ण

अटल पूर्णांक ad5064_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);

	वापस ad5064_probe(&spi->dev, id->driver_data, id->name,
				ad5064_spi_ग_लिखो);
पूर्ण

अटल पूर्णांक ad5064_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस ad5064_हटाओ(&spi->dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad5064_spi_ids[] = अणु
	अणु"ad5024", ID_AD5024पूर्ण,
	अणु"ad5025", ID_AD5025पूर्ण,
	अणु"ad5044", ID_AD5044पूर्ण,
	अणु"ad5045", ID_AD5045पूर्ण,
	अणु"ad5064", ID_AD5064पूर्ण,
	अणु"ad5064-1", ID_AD5064_1पूर्ण,
	अणु"ad5065", ID_AD5065पूर्ण,
	अणु"ad5628-1", ID_AD5628_1पूर्ण,
	अणु"ad5628-2", ID_AD5628_2पूर्ण,
	अणु"ad5648-1", ID_AD5648_1पूर्ण,
	अणु"ad5648-2", ID_AD5648_2पूर्ण,
	अणु"ad5666-1", ID_AD5666_1पूर्ण,
	अणु"ad5666-2", ID_AD5666_2पूर्ण,
	अणु"ad5668-1", ID_AD5668_1पूर्ण,
	अणु"ad5668-2", ID_AD5668_2पूर्ण,
	अणु"ad5668-3", ID_AD5668_2पूर्ण, /* similar enough to ad5668-2 */
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad5064_spi_ids);

अटल काष्ठा spi_driver ad5064_spi_driver = अणु
	.driver = अणु
		   .name = "ad5064",
	पूर्ण,
	.probe = ad5064_spi_probe,
	.हटाओ = ad5064_spi_हटाओ,
	.id_table = ad5064_spi_ids,
पूर्ण;

अटल पूर्णांक __init ad5064_spi_रेजिस्टर_driver(व्योम)
अणु
	वापस spi_रेजिस्टर_driver(&ad5064_spi_driver);
पूर्ण

अटल व्योम ad5064_spi_unरेजिस्टर_driver(व्योम)
अणु
	spi_unरेजिस्टर_driver(&ad5064_spi_driver);
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक ad5064_spi_रेजिस्टर_driver(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ad5064_spi_unरेजिस्टर_driver(व्योम) अणु पूर्ण

#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_I2C)

अटल पूर्णांक ad5064_i2c_ग_लिखो(काष्ठा ad5064_state *st, अचिन्हित पूर्णांक cmd,
	अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक val)
अणु
	काष्ठा i2c_client *i2c = to_i2c_client(st->dev);
	अचिन्हित पूर्णांक cmd_shअगरt;
	पूर्णांक ret;

	चयन (st->chip_info->regmap_type) अणु
	हाल AD5064_REGMAP_ADI2:
		cmd_shअगरt = 3;
		अवरोध;
	शेष:
		cmd_shअगरt = 4;
		अवरोध;
	पूर्ण

	st->data.i2c[0] = (cmd << cmd_shअगरt) | addr;
	put_unaligned_be16(val, &st->data.i2c[1]);

	ret = i2c_master_send(i2c, st->data.i2c, 3);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ad5064_i2c_probe(काष्ठा i2c_client *i2c,
	स्थिर काष्ठा i2c_device_id *id)
अणु
	वापस ad5064_probe(&i2c->dev, id->driver_data, id->name,
						ad5064_i2c_ग_लिखो);
पूर्ण

अटल पूर्णांक ad5064_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	वापस ad5064_हटाओ(&i2c->dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ad5064_i2c_ids[] = अणु
	अणु"ad5625", ID_AD5625 पूर्ण,
	अणु"ad5625r-1v25", ID_AD5625R_1V25 पूर्ण,
	अणु"ad5625r-2v5", ID_AD5625R_2V5 पूर्ण,
	अणु"ad5627", ID_AD5627 पूर्ण,
	अणु"ad5627r-1v25", ID_AD5627R_1V25 पूर्ण,
	अणु"ad5627r-2v5", ID_AD5627R_2V5 पूर्ण,
	अणु"ad5629-1", ID_AD5629_1पूर्ण,
	अणु"ad5629-2", ID_AD5629_2पूर्ण,
	अणु"ad5629-3", ID_AD5629_2पूर्ण, /* similar enough to ad5629-2 */
	अणु"ad5645r-1v25", ID_AD5645R_1V25 पूर्ण,
	अणु"ad5645r-2v5", ID_AD5645R_2V5 पूर्ण,
	अणु"ad5665", ID_AD5665 पूर्ण,
	अणु"ad5665r-1v25", ID_AD5665R_1V25 पूर्ण,
	अणु"ad5665r-2v5", ID_AD5665R_2V5 पूर्ण,
	अणु"ad5667", ID_AD5667 पूर्ण,
	अणु"ad5667r-1v25", ID_AD5667R_1V25 पूर्ण,
	अणु"ad5667r-2v5", ID_AD5667R_2V5 पूर्ण,
	अणु"ad5669-1", ID_AD5669_1पूर्ण,
	अणु"ad5669-2", ID_AD5669_2पूर्ण,
	अणु"ad5669-3", ID_AD5669_2पूर्ण, /* similar enough to ad5669-2 */
	अणु"ltc2606", ID_LTC2606पूर्ण,
	अणु"ltc2607", ID_LTC2607पूर्ण,
	अणु"ltc2609", ID_LTC2609पूर्ण,
	अणु"ltc2616", ID_LTC2616पूर्ण,
	अणु"ltc2617", ID_LTC2617पूर्ण,
	अणु"ltc2619", ID_LTC2619पूर्ण,
	अणु"ltc2626", ID_LTC2626पूर्ण,
	अणु"ltc2627", ID_LTC2627पूर्ण,
	अणु"ltc2629", ID_LTC2629पूर्ण,
	अणु"ltc2631-l12", ID_LTC2631_L12पूर्ण,
	अणु"ltc2631-h12", ID_LTC2631_H12पूर्ण,
	अणु"ltc2631-l10", ID_LTC2631_L10पूर्ण,
	अणु"ltc2631-h10", ID_LTC2631_H10पूर्ण,
	अणु"ltc2631-l8", ID_LTC2631_L8पूर्ण,
	अणु"ltc2631-h8", ID_LTC2631_H8पूर्ण,
	अणु"ltc2633-l12", ID_LTC2633_L12पूर्ण,
	अणु"ltc2633-h12", ID_LTC2633_H12पूर्ण,
	अणु"ltc2633-l10", ID_LTC2633_L10पूर्ण,
	अणु"ltc2633-h10", ID_LTC2633_H10पूर्ण,
	अणु"ltc2633-l8", ID_LTC2633_L8पूर्ण,
	अणु"ltc2633-h8", ID_LTC2633_H8पूर्ण,
	अणु"ltc2635-l12", ID_LTC2635_L12पूर्ण,
	अणु"ltc2635-h12", ID_LTC2635_H12पूर्ण,
	अणु"ltc2635-l10", ID_LTC2635_L10पूर्ण,
	अणु"ltc2635-h10", ID_LTC2635_H10पूर्ण,
	अणु"ltc2635-l8", ID_LTC2635_L8पूर्ण,
	अणु"ltc2635-h8", ID_LTC2635_H8पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ad5064_i2c_ids);

अटल काष्ठा i2c_driver ad5064_i2c_driver = अणु
	.driver = अणु
		   .name = "ad5064",
	पूर्ण,
	.probe = ad5064_i2c_probe,
	.हटाओ = ad5064_i2c_हटाओ,
	.id_table = ad5064_i2c_ids,
पूर्ण;

अटल पूर्णांक __init ad5064_i2c_रेजिस्टर_driver(व्योम)
अणु
	वापस i2c_add_driver(&ad5064_i2c_driver);
पूर्ण

अटल व्योम __निकास ad5064_i2c_unरेजिस्टर_driver(व्योम)
अणु
	i2c_del_driver(&ad5064_i2c_driver);
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक ad5064_i2c_रेजिस्टर_driver(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ad5064_i2c_unरेजिस्टर_driver(व्योम) अणु पूर्ण

#पूर्ण_अगर

अटल पूर्णांक __init ad5064_init(व्योम)
अणु
	पूर्णांक ret;

	ret = ad5064_spi_रेजिस्टर_driver();
	अगर (ret)
		वापस ret;

	ret = ad5064_i2c_रेजिस्टर_driver();
	अगर (ret) अणु
		ad5064_spi_unरेजिस्टर_driver();
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
module_init(ad5064_init);

अटल व्योम __निकास ad5064_निकास(व्योम)
अणु
	ad5064_i2c_unरेजिस्टर_driver();
	ad5064_spi_unरेजिस्टर_driver();
पूर्ण
module_निकास(ad5064_निकास);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Analog Devices AD5024 and similar multi-channel DACs");
MODULE_LICENSE("GPL v2");
