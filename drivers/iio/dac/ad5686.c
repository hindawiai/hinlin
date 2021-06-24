<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * AD5686R, AD5685R, AD5684R Digital to analog converters  driver
 *
 * Copyright 2011 Analog Devices Inc.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fs.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#समावेश "ad5686.h"

अटल स्थिर अक्षर * स्थिर ad5686_घातerकरोwn_modes[] = अणु
	"1kohm_to_gnd",
	"100kohm_to_gnd",
	"three_state"
पूर्ण;

अटल पूर्णांक ad5686_get_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा ad5686_state *st = iio_priv(indio_dev);

	वापस ((st->pwr_करोwn_mode >> (chan->channel * 2)) & 0x3) - 1;
पूर्ण

अटल पूर्णांक ad5686_set_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     अचिन्हित पूर्णांक mode)
अणु
	काष्ठा ad5686_state *st = iio_priv(indio_dev);

	st->pwr_करोwn_mode &= ~(0x3 << (chan->channel * 2));
	st->pwr_करोwn_mode |= ((mode + 1) << (chan->channel * 2));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_क्रमागत ad5686_घातerकरोwn_mode_क्रमागत = अणु
	.items = ad5686_घातerकरोwn_modes,
	.num_items = ARRAY_SIZE(ad5686_घातerकरोwn_modes),
	.get = ad5686_get_घातerकरोwn_mode,
	.set = ad5686_set_घातerकरोwn_mode,
पूर्ण;

अटल sमाप_प्रकार ad5686_पढ़ो_dac_घातerकरोwn(काष्ठा iio_dev *indio_dev,
		uपूर्णांकptr_t निजी, स्थिर काष्ठा iio_chan_spec *chan, अक्षर *buf)
अणु
	काष्ठा ad5686_state *st = iio_priv(indio_dev);

	वापस sysfs_emit(buf, "%d\n", !!(st->pwr_करोwn_mask &
				       (0x3 << (chan->channel * 2))));
पूर्ण

अटल sमाप_प्रकार ad5686_ग_लिखो_dac_घातerकरोwn(काष्ठा iio_dev *indio_dev,
					  uपूर्णांकptr_t निजी,
					  स्थिर काष्ठा iio_chan_spec *chan,
					  स्थिर अक्षर *buf,
					  माप_प्रकार len)
अणु
	bool पढ़ोin;
	पूर्णांक ret;
	काष्ठा ad5686_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक val, ref_bit_msk;
	u8 shअगरt, address = 0;

	ret = strtobool(buf, &पढ़ोin);
	अगर (ret)
		वापस ret;

	अगर (पढ़ोin)
		st->pwr_करोwn_mask |= (0x3 << (chan->channel * 2));
	अन्यथा
		st->pwr_करोwn_mask &= ~(0x3 << (chan->channel * 2));

	चयन (st->chip_info->regmap_type) अणु
	हाल AD5310_REGMAP:
		shअगरt = 9;
		ref_bit_msk = AD5310_REF_BIT_MSK;
		अवरोध;
	हाल AD5683_REGMAP:
		shअगरt = 13;
		ref_bit_msk = AD5683_REF_BIT_MSK;
		अवरोध;
	हाल AD5686_REGMAP:
		shअगरt = 0;
		ref_bit_msk = 0;
		/* AD5674R/AD5679R have 16 channels and 2 घातerकरोwn रेजिस्टरs */
		अगर (chan->channel > 0x7)
			address = 0x8;
		अवरोध;
	हाल AD5693_REGMAP:
		shअगरt = 13;
		ref_bit_msk = AD5693_REF_BIT_MSK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	val = ((st->pwr_करोwn_mask & st->pwr_करोwn_mode) << shअगरt);
	अगर (!st->use_पूर्णांकernal_vref)
		val |= ref_bit_msk;

	ret = st->ग_लिखो(st, AD5686_CMD_POWERDOWN_DAC,
			address, val >> (address * 2));

	वापस ret ? ret : len;
पूर्ण

अटल पूर्णांक ad5686_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ m)
अणु
	काष्ठा ad5686_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (m) अणु
	हाल IIO_CHAN_INFO_RAW:
		mutex_lock(&st->lock);
		ret = st->पढ़ो(st, chan->address);
		mutex_unlock(&st->lock);
		अगर (ret < 0)
			वापस ret;
		*val = (ret >> chan->scan_type.shअगरt) &
			GENMASK(chan->scan_type.realbits - 1, 0);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = st->vref_mv;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad5686_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val,
			    पूर्णांक val2,
			    दीर्घ mask)
अणु
	काष्ठा ad5686_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (val > (1 << chan->scan_type.realbits) || val < 0)
			वापस -EINVAL;

		mutex_lock(&st->lock);
		ret = st->ग_लिखो(st,
				AD5686_CMD_WRITE_INPUT_N_UPDATE_N,
				chan->address,
				val << chan->scan_type.shअगरt);
		mutex_unlock(&st->lock);
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info ad5686_info = अणु
	.पढ़ो_raw = ad5686_पढ़ो_raw,
	.ग_लिखो_raw = ad5686_ग_लिखो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info ad5686_ext_info[] = अणु
	अणु
		.name = "powerdown",
		.पढ़ो = ad5686_पढ़ो_dac_घातerकरोwn,
		.ग_लिखो = ad5686_ग_लिखो_dac_घातerकरोwn,
		.shared = IIO_SEPARATE,
	पूर्ण,
	IIO_ENUM("powerdown_mode", IIO_SEPARATE, &ad5686_घातerकरोwn_mode_क्रमागत),
	IIO_ENUM_AVAILABLE("powerdown_mode", &ad5686_घातerकरोwn_mode_क्रमागत),
	अणु पूर्ण,
पूर्ण;

#घोषणा AD5868_CHANNEL(chan, addr, bits, _shअगरt) अणु		\
		.type = IIO_VOLTAGE,				\
		.indexed = 1,					\
		.output = 1,					\
		.channel = chan,				\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),\
		.address = addr,				\
		.scan_type = अणु					\
			.sign = 'u',				\
			.realbits = (bits),			\
			.storagebits = 16,			\
			.shअगरt = (_shअगरt),			\
		पूर्ण,						\
		.ext_info = ad5686_ext_info,			\
पूर्ण

#घोषणा DECLARE_AD5693_CHANNELS(name, bits, _shअगरt)		\
अटल स्थिर काष्ठा iio_chan_spec name[] = अणु			\
		AD5868_CHANNEL(0, 0, bits, _shअगरt),		\
पूर्ण

#घोषणा DECLARE_AD5338_CHANNELS(name, bits, _shअगरt)		\
अटल स्थिर काष्ठा iio_chan_spec name[] = अणु			\
		AD5868_CHANNEL(0, 1, bits, _shअगरt),		\
		AD5868_CHANNEL(1, 8, bits, _shअगरt),		\
पूर्ण

#घोषणा DECLARE_AD5686_CHANNELS(name, bits, _shअगरt)		\
अटल स्थिर काष्ठा iio_chan_spec name[] = अणु			\
		AD5868_CHANNEL(0, 1, bits, _shअगरt),		\
		AD5868_CHANNEL(1, 2, bits, _shअगरt),		\
		AD5868_CHANNEL(2, 4, bits, _shअगरt),		\
		AD5868_CHANNEL(3, 8, bits, _shअगरt),		\
पूर्ण

#घोषणा DECLARE_AD5676_CHANNELS(name, bits, _shअगरt)		\
अटल स्थिर काष्ठा iio_chan_spec name[] = अणु			\
		AD5868_CHANNEL(0, 0, bits, _shअगरt),		\
		AD5868_CHANNEL(1, 1, bits, _shअगरt),		\
		AD5868_CHANNEL(2, 2, bits, _shअगरt),		\
		AD5868_CHANNEL(3, 3, bits, _shअगरt),		\
		AD5868_CHANNEL(4, 4, bits, _shअगरt),		\
		AD5868_CHANNEL(5, 5, bits, _shअगरt),		\
		AD5868_CHANNEL(6, 6, bits, _shअगरt),		\
		AD5868_CHANNEL(7, 7, bits, _shअगरt),		\
पूर्ण

#घोषणा DECLARE_AD5679_CHANNELS(name, bits, _shअगरt)		\
अटल स्थिर काष्ठा iio_chan_spec name[] = अणु			\
		AD5868_CHANNEL(0, 0, bits, _shअगरt),		\
		AD5868_CHANNEL(1, 1, bits, _shअगरt),		\
		AD5868_CHANNEL(2, 2, bits, _shअगरt),		\
		AD5868_CHANNEL(3, 3, bits, _shअगरt),		\
		AD5868_CHANNEL(4, 4, bits, _shअगरt),		\
		AD5868_CHANNEL(5, 5, bits, _shअगरt),		\
		AD5868_CHANNEL(6, 6, bits, _shअगरt),		\
		AD5868_CHANNEL(7, 7, bits, _shअगरt),		\
		AD5868_CHANNEL(8, 8, bits, _shअगरt),		\
		AD5868_CHANNEL(9, 9, bits, _shअगरt),		\
		AD5868_CHANNEL(10, 10, bits, _shअगरt),		\
		AD5868_CHANNEL(11, 11, bits, _shअगरt),		\
		AD5868_CHANNEL(12, 12, bits, _shअगरt),		\
		AD5868_CHANNEL(13, 13, bits, _shअगरt),		\
		AD5868_CHANNEL(14, 14, bits, _shअगरt),		\
		AD5868_CHANNEL(15, 15, bits, _shअगरt),		\
पूर्ण

DECLARE_AD5693_CHANNELS(ad5310r_channels, 10, 2);
DECLARE_AD5693_CHANNELS(ad5311r_channels, 10, 6);
DECLARE_AD5338_CHANNELS(ad5338r_channels, 10, 6);
DECLARE_AD5676_CHANNELS(ad5672_channels, 12, 4);
DECLARE_AD5679_CHANNELS(ad5674r_channels, 12, 4);
DECLARE_AD5676_CHANNELS(ad5676_channels, 16, 0);
DECLARE_AD5679_CHANNELS(ad5679r_channels, 16, 0);
DECLARE_AD5686_CHANNELS(ad5684_channels, 12, 4);
DECLARE_AD5686_CHANNELS(ad5685r_channels, 14, 2);
DECLARE_AD5686_CHANNELS(ad5686_channels, 16, 0);
DECLARE_AD5693_CHANNELS(ad5693_channels, 16, 0);
DECLARE_AD5693_CHANNELS(ad5692r_channels, 14, 2);
DECLARE_AD5693_CHANNELS(ad5691r_channels, 12, 4);

अटल स्थिर काष्ठा ad5686_chip_info ad5686_chip_info_tbl[] = अणु
	[ID_AD5310R] = अणु
		.channels = ad5310r_channels,
		.पूर्णांक_vref_mv = 2500,
		.num_channels = 1,
		.regmap_type = AD5310_REGMAP,
	पूर्ण,
	[ID_AD5311R] = अणु
		.channels = ad5311r_channels,
		.पूर्णांक_vref_mv = 2500,
		.num_channels = 1,
		.regmap_type = AD5693_REGMAP,
	पूर्ण,
	[ID_AD5338R] = अणु
		.channels = ad5338r_channels,
		.पूर्णांक_vref_mv = 2500,
		.num_channels = 2,
		.regmap_type = AD5686_REGMAP,
	पूर्ण,
	[ID_AD5671R] = अणु
		.channels = ad5672_channels,
		.पूर्णांक_vref_mv = 2500,
		.num_channels = 8,
		.regmap_type = AD5686_REGMAP,
	पूर्ण,
	[ID_AD5672R] = अणु
		.channels = ad5672_channels,
		.पूर्णांक_vref_mv = 2500,
		.num_channels = 8,
		.regmap_type = AD5686_REGMAP,
	पूर्ण,
	[ID_AD5673R] = अणु
		.channels = ad5674r_channels,
		.पूर्णांक_vref_mv = 2500,
		.num_channels = 16,
		.regmap_type = AD5686_REGMAP,
	पूर्ण,
	[ID_AD5674R] = अणु
		.channels = ad5674r_channels,
		.पूर्णांक_vref_mv = 2500,
		.num_channels = 16,
		.regmap_type = AD5686_REGMAP,
	पूर्ण,
	[ID_AD5675R] = अणु
		.channels = ad5676_channels,
		.पूर्णांक_vref_mv = 2500,
		.num_channels = 8,
		.regmap_type = AD5686_REGMAP,
	पूर्ण,
	[ID_AD5676] = अणु
		.channels = ad5676_channels,
		.num_channels = 8,
		.regmap_type = AD5686_REGMAP,
	पूर्ण,
	[ID_AD5676R] = अणु
		.channels = ad5676_channels,
		.पूर्णांक_vref_mv = 2500,
		.num_channels = 8,
		.regmap_type = AD5686_REGMAP,
	पूर्ण,
	[ID_AD5677R] = अणु
		.channels = ad5679r_channels,
		.पूर्णांक_vref_mv = 2500,
		.num_channels = 16,
		.regmap_type = AD5686_REGMAP,
	पूर्ण,
	[ID_AD5679R] = अणु
		.channels = ad5679r_channels,
		.पूर्णांक_vref_mv = 2500,
		.num_channels = 16,
		.regmap_type = AD5686_REGMAP,
	पूर्ण,
	[ID_AD5681R] = अणु
		.channels = ad5691r_channels,
		.पूर्णांक_vref_mv = 2500,
		.num_channels = 1,
		.regmap_type = AD5683_REGMAP,
	पूर्ण,
	[ID_AD5682R] = अणु
		.channels = ad5692r_channels,
		.पूर्णांक_vref_mv = 2500,
		.num_channels = 1,
		.regmap_type = AD5683_REGMAP,
	पूर्ण,
	[ID_AD5683] = अणु
		.channels = ad5693_channels,
		.num_channels = 1,
		.regmap_type = AD5683_REGMAP,
	पूर्ण,
	[ID_AD5683R] = अणु
		.channels = ad5693_channels,
		.पूर्णांक_vref_mv = 2500,
		.num_channels = 1,
		.regmap_type = AD5683_REGMAP,
	पूर्ण,
	[ID_AD5684] = अणु
		.channels = ad5684_channels,
		.num_channels = 4,
		.regmap_type = AD5686_REGMAP,
	पूर्ण,
	[ID_AD5684R] = अणु
		.channels = ad5684_channels,
		.पूर्णांक_vref_mv = 2500,
		.num_channels = 4,
		.regmap_type = AD5686_REGMAP,
	पूर्ण,
	[ID_AD5685R] = अणु
		.channels = ad5685r_channels,
		.पूर्णांक_vref_mv = 2500,
		.num_channels = 4,
		.regmap_type = AD5686_REGMAP,
	पूर्ण,
	[ID_AD5686] = अणु
		.channels = ad5686_channels,
		.num_channels = 4,
		.regmap_type = AD5686_REGMAP,
	पूर्ण,
	[ID_AD5686R] = अणु
		.channels = ad5686_channels,
		.पूर्णांक_vref_mv = 2500,
		.num_channels = 4,
		.regmap_type = AD5686_REGMAP,
	पूर्ण,
	[ID_AD5691R] = अणु
		.channels = ad5691r_channels,
		.पूर्णांक_vref_mv = 2500,
		.num_channels = 1,
		.regmap_type = AD5693_REGMAP,
	पूर्ण,
	[ID_AD5692R] = अणु
		.channels = ad5692r_channels,
		.पूर्णांक_vref_mv = 2500,
		.num_channels = 1,
		.regmap_type = AD5693_REGMAP,
	पूर्ण,
	[ID_AD5693] = अणु
		.channels = ad5693_channels,
		.num_channels = 1,
		.regmap_type = AD5693_REGMAP,
	पूर्ण,
	[ID_AD5693R] = अणु
		.channels = ad5693_channels,
		.पूर्णांक_vref_mv = 2500,
		.num_channels = 1,
		.regmap_type = AD5693_REGMAP,
	पूर्ण,
	[ID_AD5694] = अणु
		.channels = ad5684_channels,
		.num_channels = 4,
		.regmap_type = AD5686_REGMAP,
	पूर्ण,
	[ID_AD5694R] = अणु
		.channels = ad5684_channels,
		.पूर्णांक_vref_mv = 2500,
		.num_channels = 4,
		.regmap_type = AD5686_REGMAP,
	पूर्ण,
	[ID_AD5696] = अणु
		.channels = ad5686_channels,
		.num_channels = 4,
		.regmap_type = AD5686_REGMAP,
	पूर्ण,
	[ID_AD5696R] = अणु
		.channels = ad5686_channels,
		.पूर्णांक_vref_mv = 2500,
		.num_channels = 4,
		.regmap_type = AD5686_REGMAP,
	पूर्ण,
पूर्ण;

पूर्णांक ad5686_probe(काष्ठा device *dev,
		 क्रमागत ad5686_supported_device_ids chip_type,
		 स्थिर अक्षर *name, ad5686_ग_लिखो_func ग_लिखो,
		 ad5686_पढ़ो_func पढ़ो)
अणु
	काष्ठा ad5686_state *st;
	काष्ठा iio_dev *indio_dev;
	अचिन्हित पूर्णांक val, ref_bit_msk;
	u8 cmd;
	पूर्णांक ret, i, voltage_uv = 0;

	indio_dev = devm_iio_device_alloc(dev, माप(*st));
	अगर (indio_dev == शून्य)
		वापस  -ENOMEM;

	st = iio_priv(indio_dev);
	dev_set_drvdata(dev, indio_dev);

	st->dev = dev;
	st->ग_लिखो = ग_लिखो;
	st->पढ़ो = पढ़ो;

	st->reg = devm_regulator_get_optional(dev, "vcc");
	अगर (!IS_ERR(st->reg)) अणु
		ret = regulator_enable(st->reg);
		अगर (ret)
			वापस ret;

		ret = regulator_get_voltage(st->reg);
		अगर (ret < 0)
			जाओ error_disable_reg;

		voltage_uv = ret;
	पूर्ण

	st->chip_info = &ad5686_chip_info_tbl[chip_type];

	अगर (voltage_uv)
		st->vref_mv = voltage_uv / 1000;
	अन्यथा
		st->vref_mv = st->chip_info->पूर्णांक_vref_mv;

	/* Set all the घातer करोwn mode क्रम all channels to 1K pullकरोwn */
	क्रम (i = 0; i < st->chip_info->num_channels; i++)
		st->pwr_करोwn_mode |= (0x01 << (i * 2));

	indio_dev->name = name;
	indio_dev->info = &ad5686_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = st->chip_info->channels;
	indio_dev->num_channels = st->chip_info->num_channels;

	mutex_init(&st->lock);

	चयन (st->chip_info->regmap_type) अणु
	हाल AD5310_REGMAP:
		cmd = AD5686_CMD_CONTROL_REG;
		ref_bit_msk = AD5310_REF_BIT_MSK;
		st->use_पूर्णांकernal_vref = !voltage_uv;
		अवरोध;
	हाल AD5683_REGMAP:
		cmd = AD5686_CMD_CONTROL_REG;
		ref_bit_msk = AD5683_REF_BIT_MSK;
		st->use_पूर्णांकernal_vref = !voltage_uv;
		अवरोध;
	हाल AD5686_REGMAP:
		cmd = AD5686_CMD_INTERNAL_REFER_SETUP;
		ref_bit_msk = 0;
		अवरोध;
	हाल AD5693_REGMAP:
		cmd = AD5686_CMD_CONTROL_REG;
		ref_bit_msk = AD5693_REF_BIT_MSK;
		st->use_पूर्णांकernal_vref = !voltage_uv;
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ error_disable_reg;
	पूर्ण

	val = (voltage_uv | ref_bit_msk);

	ret = st->ग_लिखो(st, cmd, 0, !!val);
	अगर (ret)
		जाओ error_disable_reg;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_disable_reg;

	वापस 0;

error_disable_reg:
	अगर (!IS_ERR(st->reg))
		regulator_disable(st->reg);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ad5686_probe);

पूर्णांक ad5686_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा ad5686_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	अगर (!IS_ERR(st->reg))
		regulator_disable(st->reg);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ad5686_हटाओ);

MODULE_AUTHOR("Michael Hennerich <michael.hennerich@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD5686/85/84 DAC");
MODULE_LICENSE("GPL v2");
