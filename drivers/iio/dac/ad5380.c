<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Analog devices AD5380, AD5381, AD5382, AD5383, AD5390, AD5391, AD5392
 * multi-channel Digital to Analog Converters driver
 *
 * Copyright 2011 Analog Devices Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा AD5380_REG_DATA(x)	(((x) << 2) | 3)
#घोषणा AD5380_REG_OFFSET(x)	(((x) << 2) | 2)
#घोषणा AD5380_REG_GAIN(x)	(((x) << 2) | 1)
#घोषणा AD5380_REG_SF_PWR_DOWN	(8 << 2)
#घोषणा AD5380_REG_SF_PWR_UP	(9 << 2)
#घोषणा AD5380_REG_SF_CTRL	(12 << 2)

#घोषणा AD5380_CTRL_PWR_DOWN_MODE_OFFSET	13
#घोषणा AD5380_CTRL_INT_VREF_2V5		BIT(12)
#घोषणा AD5380_CTRL_INT_VREF_EN			BIT(10)

/**
 * काष्ठा ad5380_chip_info - chip specअगरic inक्रमmation
 * @channel_ढाँचा:	channel specअगरication ढाँचा
 * @num_channels:	number of channels
 * @पूर्णांक_vref:		पूर्णांकernal vref in uV
*/

काष्ठा ad5380_chip_info अणु
	काष्ठा iio_chan_spec	channel_ढाँचा;
	अचिन्हित पूर्णांक		num_channels;
	अचिन्हित पूर्णांक		पूर्णांक_vref;
पूर्ण;

/**
 * काष्ठा ad5380_state - driver instance specअगरic data
 * @regmap:		regmap instance used by the device
 * @chip_info:		chip model specअगरic स्थिरants, available modes etc
 * @vref_reg:		vref supply regulator
 * @vref:		actual reference voltage used in uA
 * @pwr_करोwn:		whether the chip is currently in घातer करोwn mode
 * @lock:		lock to protect the data buffer during regmap ops
 */

काष्ठा ad5380_state अणु
	काष्ठा regmap			*regmap;
	स्थिर काष्ठा ad5380_chip_info	*chip_info;
	काष्ठा regulator		*vref_reg;
	पूर्णांक				vref;
	bool				pwr_करोwn;
	काष्ठा mutex			lock;
पूर्ण;

क्रमागत ad5380_type अणु
	ID_AD5380_3,
	ID_AD5380_5,
	ID_AD5381_3,
	ID_AD5381_5,
	ID_AD5382_3,
	ID_AD5382_5,
	ID_AD5383_3,
	ID_AD5383_5,
	ID_AD5390_3,
	ID_AD5390_5,
	ID_AD5391_3,
	ID_AD5391_5,
	ID_AD5392_3,
	ID_AD5392_5,
पूर्ण;

अटल sमाप_प्रकार ad5380_पढ़ो_dac_घातerकरोwn(काष्ठा iio_dev *indio_dev,
	uपूर्णांकptr_t निजी, स्थिर काष्ठा iio_chan_spec *chan, अक्षर *buf)
अणु
	काष्ठा ad5380_state *st = iio_priv(indio_dev);

	वापस sysfs_emit(buf, "%d\n", st->pwr_करोwn);
पूर्ण

अटल sमाप_प्रकार ad5380_ग_लिखो_dac_घातerकरोwn(काष्ठा iio_dev *indio_dev,
	 uपूर्णांकptr_t निजी, स्थिर काष्ठा iio_chan_spec *chan, स्थिर अक्षर *buf,
	 माप_प्रकार len)
अणु
	काष्ठा ad5380_state *st = iio_priv(indio_dev);
	bool pwr_करोwn;
	पूर्णांक ret;

	ret = strtobool(buf, &pwr_करोwn);
	अगर (ret)
		वापस ret;

	mutex_lock(&st->lock);

	अगर (pwr_करोwn)
		ret = regmap_ग_लिखो(st->regmap, AD5380_REG_SF_PWR_DOWN, 0);
	अन्यथा
		ret = regmap_ग_लिखो(st->regmap, AD5380_REG_SF_PWR_UP, 0);

	st->pwr_करोwn = pwr_करोwn;

	mutex_unlock(&st->lock);

	वापस ret ? ret : len;
पूर्ण

अटल स्थिर अक्षर * स्थिर ad5380_घातerकरोwn_modes[] = अणु
	"100kohm_to_gnd",
	"three_state",
पूर्ण;

अटल पूर्णांक ad5380_get_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा ad5380_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक mode;
	पूर्णांक ret;

	ret = regmap_पढ़ो(st->regmap, AD5380_REG_SF_CTRL, &mode);
	अगर (ret)
		वापस ret;

	mode = (mode >> AD5380_CTRL_PWR_DOWN_MODE_OFFSET) & 1;

	वापस mode;
पूर्ण

अटल पूर्णांक ad5380_set_घातerकरोwn_mode(काष्ठा iio_dev *indio_dev,
	स्थिर काष्ठा iio_chan_spec *chan, अचिन्हित पूर्णांक mode)
अणु
	काष्ठा ad5380_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = regmap_update_bits(st->regmap, AD5380_REG_SF_CTRL,
		1 << AD5380_CTRL_PWR_DOWN_MODE_OFFSET,
		mode << AD5380_CTRL_PWR_DOWN_MODE_OFFSET);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_क्रमागत ad5380_घातerकरोwn_mode_क्रमागत = अणु
	.items = ad5380_घातerकरोwn_modes,
	.num_items = ARRAY_SIZE(ad5380_घातerकरोwn_modes),
	.get = ad5380_get_घातerकरोwn_mode,
	.set = ad5380_set_घातerकरोwn_mode,
पूर्ण;

अटल अचिन्हित पूर्णांक ad5380_info_to_reg(काष्ठा iio_chan_spec स्थिर *chan,
	दीर्घ info)
अणु
	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		वापस AD5380_REG_DATA(chan->address);
	हाल IIO_CHAN_INFO_CALIBBIAS:
		वापस AD5380_REG_OFFSET(chan->address);
	हाल IIO_CHAN_INFO_CALIBSCALE:
		वापस AD5380_REG_GAIN(chan->address);
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ad5380_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val, पूर्णांक val2, दीर्घ info)
अणु
	स्थिर अचिन्हित पूर्णांक max_val = (1 << chan->scan_type.realbits);
	काष्ठा ad5380_state *st = iio_priv(indio_dev);

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
	हाल IIO_CHAN_INFO_CALIBSCALE:
		अगर (val >= max_val || val < 0)
			वापस -EINVAL;

		वापस regmap_ग_लिखो(st->regmap,
			ad5380_info_to_reg(chan, info),
			val << chan->scan_type.shअगरt);
	हाल IIO_CHAN_INFO_CALIBBIAS:
		val += (1 << chan->scan_type.realbits) / 2;
		अगर (val >= max_val || val < 0)
			वापस -EINVAL;

		वापस regmap_ग_लिखो(st->regmap,
			AD5380_REG_OFFSET(chan->address),
			val << chan->scan_type.shअगरt);
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ad5380_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
	काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	काष्ठा ad5380_state *st = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
	हाल IIO_CHAN_INFO_CALIBSCALE:
		ret = regmap_पढ़ो(st->regmap, ad5380_info_to_reg(chan, info),
					val);
		अगर (ret)
			वापस ret;
		*val >>= chan->scan_type.shअगरt;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_CALIBBIAS:
		ret = regmap_पढ़ो(st->regmap, AD5380_REG_OFFSET(chan->address),
					val);
		अगर (ret)
			वापस ret;
		*val >>= chan->scan_type.shअगरt;
		*val -= (1 << chan->scan_type.realbits) / 2;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 2 * st->vref;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info ad5380_info = अणु
	.पढ़ो_raw = ad5380_पढ़ो_raw,
	.ग_लिखो_raw = ad5380_ग_लिखो_raw,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec_ext_info ad5380_ext_info[] = अणु
	अणु
		.name = "powerdown",
		.पढ़ो = ad5380_पढ़ो_dac_घातerकरोwn,
		.ग_लिखो = ad5380_ग_लिखो_dac_घातerकरोwn,
		.shared = IIO_SEPARATE,
	पूर्ण,
	IIO_ENUM("powerdown_mode", IIO_SHARED_BY_TYPE,
		 &ad5380_घातerकरोwn_mode_क्रमागत),
	IIO_ENUM_AVAILABLE("powerdown_mode", &ad5380_घातerकरोwn_mode_क्रमागत),
	अणु पूर्ण,
पूर्ण;

#घोषणा AD5380_CHANNEL(_bits) अणु					\
	.type = IIO_VOLTAGE,					\
	.indexed = 1,						\
	.output = 1,						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |		\
		BIT(IIO_CHAN_INFO_CALIBSCALE) |			\
		BIT(IIO_CHAN_INFO_CALIBBIAS),			\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
	.scan_type = अणु						\
		.sign = 'u',					\
		.realbits = (_bits),				\
		.storagebits =  16,				\
		.shअगरt = 14 - (_bits),				\
	पूर्ण,							\
	.ext_info = ad5380_ext_info,				\
पूर्ण

अटल स्थिर काष्ठा ad5380_chip_info ad5380_chip_info_tbl[] = अणु
	[ID_AD5380_3] = अणु
		.channel_ढाँचा = AD5380_CHANNEL(14),
		.num_channels = 40,
		.पूर्णांक_vref = 1250,
	पूर्ण,
	[ID_AD5380_5] = अणु
		.channel_ढाँचा = AD5380_CHANNEL(14),
		.num_channels = 40,
		.पूर्णांक_vref = 2500,
	पूर्ण,
	[ID_AD5381_3] = अणु
		.channel_ढाँचा = AD5380_CHANNEL(12),
		.num_channels = 16,
		.पूर्णांक_vref = 1250,
	पूर्ण,
	[ID_AD5381_5] = अणु
		.channel_ढाँचा = AD5380_CHANNEL(12),
		.num_channels = 16,
		.पूर्णांक_vref = 2500,
	पूर्ण,
	[ID_AD5382_3] = अणु
		.channel_ढाँचा = AD5380_CHANNEL(14),
		.num_channels = 32,
		.पूर्णांक_vref = 1250,
	पूर्ण,
	[ID_AD5382_5] = अणु
		.channel_ढाँचा = AD5380_CHANNEL(14),
		.num_channels = 32,
		.पूर्णांक_vref = 2500,
	पूर्ण,
	[ID_AD5383_3] = अणु
		.channel_ढाँचा = AD5380_CHANNEL(12),
		.num_channels = 32,
		.पूर्णांक_vref = 1250,
	पूर्ण,
	[ID_AD5383_5] = अणु
		.channel_ढाँचा = AD5380_CHANNEL(12),
		.num_channels = 32,
		.पूर्णांक_vref = 2500,
	पूर्ण,
	[ID_AD5390_3] = अणु
		.channel_ढाँचा = AD5380_CHANNEL(14),
		.num_channels = 16,
		.पूर्णांक_vref = 1250,
	पूर्ण,
	[ID_AD5390_5] = अणु
		.channel_ढाँचा = AD5380_CHANNEL(14),
		.num_channels = 16,
		.पूर्णांक_vref = 2500,
	पूर्ण,
	[ID_AD5391_3] = अणु
		.channel_ढाँचा = AD5380_CHANNEL(12),
		.num_channels = 16,
		.पूर्णांक_vref = 1250,
	पूर्ण,
	[ID_AD5391_5] = अणु
		.channel_ढाँचा = AD5380_CHANNEL(12),
		.num_channels = 16,
		.पूर्णांक_vref = 2500,
	पूर्ण,
	[ID_AD5392_3] = अणु
		.channel_ढाँचा = AD5380_CHANNEL(14),
		.num_channels = 8,
		.पूर्णांक_vref = 1250,
	पूर्ण,
	[ID_AD5392_5] = अणु
		.channel_ढाँचा = AD5380_CHANNEL(14),
		.num_channels = 8,
		.पूर्णांक_vref = 2500,
	पूर्ण,
पूर्ण;

अटल पूर्णांक ad5380_alloc_channels(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा ad5380_state *st = iio_priv(indio_dev);
	काष्ठा iio_chan_spec *channels;
	अचिन्हित पूर्णांक i;

	channels = kसुस्मृति(st->chip_info->num_channels,
			   माप(काष्ठा iio_chan_spec), GFP_KERNEL);

	अगर (!channels)
		वापस -ENOMEM;

	क्रम (i = 0; i < st->chip_info->num_channels; ++i) अणु
		channels[i] = st->chip_info->channel_ढाँचा;
		channels[i].channel = i;
		channels[i].address = i;
	पूर्ण

	indio_dev->channels = channels;

	वापस 0;
पूर्ण

अटल पूर्णांक ad5380_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
			क्रमागत ad5380_type type, स्थिर अक्षर *name)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा ad5380_state *st;
	अचिन्हित पूर्णांक ctrl = 0;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*st));
	अगर (indio_dev == शून्य) अणु
		dev_err(dev, "Failed to allocate iio device\n");
		वापस -ENOMEM;
	पूर्ण

	st = iio_priv(indio_dev);
	dev_set_drvdata(dev, indio_dev);

	st->chip_info = &ad5380_chip_info_tbl[type];
	st->regmap = regmap;

	indio_dev->name = name;
	indio_dev->info = &ad5380_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->num_channels = st->chip_info->num_channels;

	mutex_init(&st->lock);

	ret = ad5380_alloc_channels(indio_dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to allocate channel spec: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (st->chip_info->पूर्णांक_vref == 2500)
		ctrl |= AD5380_CTRL_INT_VREF_2V5;

	st->vref_reg = devm_regulator_get(dev, "vref");
	अगर (!IS_ERR(st->vref_reg)) अणु
		ret = regulator_enable(st->vref_reg);
		अगर (ret) अणु
			dev_err(dev, "Failed to enable vref regulators: %d\n",
				ret);
			जाओ error_मुक्त_reg;
		पूर्ण

		ret = regulator_get_voltage(st->vref_reg);
		अगर (ret < 0)
			जाओ error_disable_reg;

		st->vref = ret / 1000;
	पूर्ण अन्यथा अणु
		st->vref = st->chip_info->पूर्णांक_vref;
		ctrl |= AD5380_CTRL_INT_VREF_EN;
	पूर्ण

	ret = regmap_ग_लिखो(st->regmap, AD5380_REG_SF_CTRL, ctrl);
	अगर (ret) अणु
		dev_err(dev, "Failed to write to device: %d\n", ret);
		जाओ error_disable_reg;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(dev, "Failed to register iio device: %d\n", ret);
		जाओ error_disable_reg;
	पूर्ण

	वापस 0;

error_disable_reg:
	अगर (!IS_ERR(st->vref_reg))
		regulator_disable(st->vref_reg);
error_मुक्त_reg:
	kमुक्त(indio_dev->channels);

	वापस ret;
पूर्ण

अटल पूर्णांक ad5380_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा ad5380_state *st = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	kमुक्त(indio_dev->channels);

	अगर (!IS_ERR(st->vref_reg)) अणु
		regulator_disable(st->vref_reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool ad5380_reg_false(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस false;
पूर्ण

अटल स्थिर काष्ठा regmap_config ad5380_regmap_config = अणु
	.reg_bits = 10,
	.val_bits = 14,

	.max_रेजिस्टर = AD5380_REG_DATA(40),
	.cache_type = REGCACHE_RBTREE,

	.अस्थिर_reg = ad5380_reg_false,
	.पढ़ोable_reg = ad5380_reg_false,
पूर्ण;

#अगर IS_ENABLED(CONFIG_SPI_MASTER)

अटल पूर्णांक ad5380_spi_probe(काष्ठा spi_device *spi)
अणु
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_spi(spi, &ad5380_regmap_config);

	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस ad5380_probe(&spi->dev, regmap, id->driver_data, id->name);
पूर्ण

अटल पूर्णांक ad5380_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	वापस ad5380_हटाओ(&spi->dev);
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad5380_spi_ids[] = अणु
	अणु "ad5380-3", ID_AD5380_3 पूर्ण,
	अणु "ad5380-5", ID_AD5380_5 पूर्ण,
	अणु "ad5381-3", ID_AD5381_3 पूर्ण,
	अणु "ad5381-5", ID_AD5381_5 पूर्ण,
	अणु "ad5382-3", ID_AD5382_3 पूर्ण,
	अणु "ad5382-5", ID_AD5382_5 पूर्ण,
	अणु "ad5383-3", ID_AD5383_3 पूर्ण,
	अणु "ad5383-5", ID_AD5383_5 पूर्ण,
	अणु "ad5384-3", ID_AD5380_3 पूर्ण,
	अणु "ad5384-5", ID_AD5380_5 पूर्ण,
	अणु "ad5390-3", ID_AD5390_3 पूर्ण,
	अणु "ad5390-5", ID_AD5390_5 पूर्ण,
	अणु "ad5391-3", ID_AD5391_3 पूर्ण,
	अणु "ad5391-5", ID_AD5391_5 पूर्ण,
	अणु "ad5392-3", ID_AD5392_3 पूर्ण,
	अणु "ad5392-5", ID_AD5392_5 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad5380_spi_ids);

अटल काष्ठा spi_driver ad5380_spi_driver = अणु
	.driver = अणु
		   .name = "ad5380",
	पूर्ण,
	.probe = ad5380_spi_probe,
	.हटाओ = ad5380_spi_हटाओ,
	.id_table = ad5380_spi_ids,
पूर्ण;

अटल अंतरभूत पूर्णांक ad5380_spi_रेजिस्टर_driver(व्योम)
अणु
	वापस spi_रेजिस्टर_driver(&ad5380_spi_driver);
पूर्ण

अटल अंतरभूत व्योम ad5380_spi_unरेजिस्टर_driver(व्योम)
अणु
	spi_unरेजिस्टर_driver(&ad5380_spi_driver);
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक ad5380_spi_रेजिस्टर_driver(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ad5380_spi_unरेजिस्टर_driver(व्योम)
अणु
पूर्ण

#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_I2C)

अटल पूर्णांक ad5380_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा regmap *regmap;

	regmap = devm_regmap_init_i2c(i2c, &ad5380_regmap_config);

	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	वापस ad5380_probe(&i2c->dev, regmap, id->driver_data, id->name);
पूर्ण

अटल पूर्णांक ad5380_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	वापस ad5380_हटाओ(&i2c->dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ad5380_i2c_ids[] = अणु
	अणु "ad5380-3", ID_AD5380_3 पूर्ण,
	अणु "ad5380-5", ID_AD5380_5 पूर्ण,
	अणु "ad5381-3", ID_AD5381_3 पूर्ण,
	अणु "ad5381-5", ID_AD5381_5 पूर्ण,
	अणु "ad5382-3", ID_AD5382_3 पूर्ण,
	अणु "ad5382-5", ID_AD5382_5 पूर्ण,
	अणु "ad5383-3", ID_AD5383_3 पूर्ण,
	अणु "ad5383-5", ID_AD5383_5 पूर्ण,
	अणु "ad5384-3", ID_AD5380_3 पूर्ण,
	अणु "ad5384-5", ID_AD5380_5 पूर्ण,
	अणु "ad5390-3", ID_AD5390_3 पूर्ण,
	अणु "ad5390-5", ID_AD5390_5 पूर्ण,
	अणु "ad5391-3", ID_AD5391_3 पूर्ण,
	अणु "ad5391-5", ID_AD5391_5 पूर्ण,
	अणु "ad5392-3", ID_AD5392_3 पूर्ण,
	अणु "ad5392-5", ID_AD5392_5 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ad5380_i2c_ids);

अटल काष्ठा i2c_driver ad5380_i2c_driver = अणु
	.driver = अणु
		   .name = "ad5380",
	पूर्ण,
	.probe = ad5380_i2c_probe,
	.हटाओ = ad5380_i2c_हटाओ,
	.id_table = ad5380_i2c_ids,
पूर्ण;

अटल अंतरभूत पूर्णांक ad5380_i2c_रेजिस्टर_driver(व्योम)
अणु
	वापस i2c_add_driver(&ad5380_i2c_driver);
पूर्ण

अटल अंतरभूत व्योम ad5380_i2c_unरेजिस्टर_driver(व्योम)
अणु
	i2c_del_driver(&ad5380_i2c_driver);
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक ad5380_i2c_रेजिस्टर_driver(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम ad5380_i2c_unरेजिस्टर_driver(व्योम)
अणु
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक __init ad5380_spi_init(व्योम)
अणु
	पूर्णांक ret;

	ret = ad5380_spi_रेजिस्टर_driver();
	अगर (ret)
		वापस ret;

	ret = ad5380_i2c_रेजिस्टर_driver();
	अगर (ret) अणु
		ad5380_spi_unरेजिस्टर_driver();
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
module_init(ad5380_spi_init);

अटल व्योम __निकास ad5380_spi_निकास(व्योम)
अणु
	ad5380_i2c_unरेजिस्टर_driver();
	ad5380_spi_unरेजिस्टर_driver();

पूर्ण
module_निकास(ad5380_spi_निकास);

MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_DESCRIPTION("Analog Devices AD5380/81/82/83/84/90/91/92 DAC");
MODULE_LICENSE("GPL v2");
