<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम Linear Technology LTC1665/LTC1660, 8 channels DAC
 *
 * Copyright (C) 2018 Marcus Folkesson <marcus.folkesson@gmail.com>
 */
#समावेश <linux/bitops.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>

#घोषणा LTC1660_REG_WAKE	0x0
#घोषणा LTC1660_REG_DAC_A	0x1
#घोषणा LTC1660_REG_DAC_B	0x2
#घोषणा LTC1660_REG_DAC_C	0x3
#घोषणा LTC1660_REG_DAC_D	0x4
#घोषणा LTC1660_REG_DAC_E	0x5
#घोषणा LTC1660_REG_DAC_F	0x6
#घोषणा LTC1660_REG_DAC_G	0x7
#घोषणा LTC1660_REG_DAC_H	0x8
#घोषणा LTC1660_REG_SLEEP	0xe

#घोषणा LTC1660_NUM_CHANNELS	8

अटल स्थिर काष्ठा regmap_config ltc1660_regmap_config = अणु
	.reg_bits = 4,
	.val_bits = 12,
पूर्ण;

क्रमागत ltc1660_supported_device_ids अणु
	ID_LTC1660,
	ID_LTC1665,
पूर्ण;

काष्ठा ltc1660_priv अणु
	काष्ठा spi_device *spi;
	काष्ठा regmap *regmap;
	काष्ठा regulator *vref_reg;
	अचिन्हित पूर्णांक value[LTC1660_NUM_CHANNELS];
	अचिन्हित पूर्णांक vref_mv;
पूर्ण;

अटल पूर्णांक ltc1660_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
		काष्ठा iio_chan_spec स्थिर *chan,
		पूर्णांक *val,
		पूर्णांक *val2,
		दीर्घ mask)
अणु
	काष्ठा ltc1660_priv *priv = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		*val = priv->value[chan->channel];
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = regulator_get_voltage(priv->vref_reg);
		अगर (*val < 0) अणु
			dev_err(&priv->spi->dev, "failed to read vref regulator: %d\n",
					*val);
			वापस *val;
		पूर्ण

		/* Convert to mV */
		*val /= 1000;
		*val2 = chan->scan_type.realbits;
		वापस IIO_VAL_FRACTIONAL_LOG2;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक ltc1660_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
		काष्ठा iio_chan_spec स्थिर *chan,
		पूर्णांक val,
		पूर्णांक val2,
		दीर्घ mask)
अणु
	काष्ठा ltc1660_priv *priv = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (val2 != 0)
			वापस -EINVAL;

		अगर (val < 0 || val > GENMASK(chan->scan_type.realbits - 1, 0))
			वापस -EINVAL;

		ret = regmap_ग_लिखो(priv->regmap, chan->channel,
					(val << chan->scan_type.shअगरt));
		अगर (!ret)
			priv->value[chan->channel] = val;

		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

#घोषणा LTC1660_CHAN(chan, bits) अणु			\
	.type = IIO_VOLTAGE,				\
	.indexed = 1,					\
	.output = 1,					\
	.channel = chan,				\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),	\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
	.scan_type = अणु					\
		.sign = 'u',				\
		.realbits = (bits),			\
		.storagebits = 16,			\
		.shअगरt = 12 - (bits),			\
	पूर्ण,						\
पूर्ण

#घोषणा  LTC1660_OCTAL_CHANNELS(bits) अणु			\
		LTC1660_CHAN(LTC1660_REG_DAC_A, bits),	\
		LTC1660_CHAN(LTC1660_REG_DAC_B, bits),	\
		LTC1660_CHAN(LTC1660_REG_DAC_C, bits),	\
		LTC1660_CHAN(LTC1660_REG_DAC_D, bits),	\
		LTC1660_CHAN(LTC1660_REG_DAC_E, bits),	\
		LTC1660_CHAN(LTC1660_REG_DAC_F, bits),	\
		LTC1660_CHAN(LTC1660_REG_DAC_G, bits),	\
		LTC1660_CHAN(LTC1660_REG_DAC_H, bits),	\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ltc1660_channels[][LTC1660_NUM_CHANNELS] = अणु
	[ID_LTC1660] = LTC1660_OCTAL_CHANNELS(10),
	[ID_LTC1665] = LTC1660_OCTAL_CHANNELS(8),
पूर्ण;

अटल स्थिर काष्ठा iio_info ltc1660_info = अणु
	.पढ़ो_raw = &ltc1660_पढ़ो_raw,
	.ग_लिखो_raw = &ltc1660_ग_लिखो_raw,
पूर्ण;

अटल पूर्णांक __maybe_unused ltc1660_suspend(काष्ठा device *dev)
अणु
	काष्ठा ltc1660_priv *priv = iio_priv(spi_get_drvdata(
						to_spi_device(dev)));
	वापस regmap_ग_लिखो(priv->regmap, LTC1660_REG_SLEEP, 0x00);
पूर्ण

अटल पूर्णांक __maybe_unused ltc1660_resume(काष्ठा device *dev)
अणु
	काष्ठा ltc1660_priv *priv = iio_priv(spi_get_drvdata(
						to_spi_device(dev)));
	वापस regmap_ग_लिखो(priv->regmap, LTC1660_REG_WAKE, 0x00);
पूर्ण
अटल SIMPLE_DEV_PM_OPS(ltc1660_pm_ops, ltc1660_suspend, ltc1660_resume);

अटल पूर्णांक ltc1660_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा ltc1660_priv *priv;
	स्थिर काष्ठा spi_device_id *id = spi_get_device_id(spi);
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*priv));
	अगर (indio_dev == शून्य)
		वापस -ENOMEM;

	priv = iio_priv(indio_dev);
	priv->regmap = devm_regmap_init_spi(spi, &ltc1660_regmap_config);
	अगर (IS_ERR(priv->regmap)) अणु
		dev_err(&spi->dev, "failed to register spi regmap %ld\n",
			PTR_ERR(priv->regmap));
		वापस PTR_ERR(priv->regmap);
	पूर्ण

	priv->vref_reg = devm_regulator_get(&spi->dev, "vref");
	अगर (IS_ERR(priv->vref_reg)) अणु
		dev_err(&spi->dev, "vref regulator not specified\n");
		वापस PTR_ERR(priv->vref_reg);
	पूर्ण

	ret = regulator_enable(priv->vref_reg);
	अगर (ret) अणु
		dev_err(&spi->dev, "failed to enable vref regulator: %d\n",
				ret);
		वापस ret;
	पूर्ण

	priv->spi = spi;
	spi_set_drvdata(spi, indio_dev);
	indio_dev->info = &ltc1660_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = ltc1660_channels[id->driver_data];
	indio_dev->num_channels = LTC1660_NUM_CHANNELS;
	indio_dev->name = id->name;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(&spi->dev, "failed to register iio device: %d\n",
				ret);
		जाओ error_disable_reg;
	पूर्ण

	वापस 0;

error_disable_reg:
	regulator_disable(priv->vref_reg);

	वापस ret;
पूर्ण

अटल पूर्णांक ltc1660_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);
	काष्ठा ltc1660_priv *priv = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	regulator_disable(priv->vref_reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ltc1660_dt_ids[] = अणु
	अणु .compatible = "lltc,ltc1660", .data = (व्योम *)ID_LTC1660 पूर्ण,
	अणु .compatible = "lltc,ltc1665", .data = (व्योम *)ID_LTC1665 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ltc1660_dt_ids);

अटल स्थिर काष्ठा spi_device_id ltc1660_id[] = अणु
	अणु"ltc1660", ID_LTC1660पूर्ण,
	अणु"ltc1665", ID_LTC1665पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ltc1660_id);

अटल काष्ठा spi_driver ltc1660_driver = अणु
	.driver = अणु
		.name = "ltc1660",
		.of_match_table = ltc1660_dt_ids,
		.pm = &ltc1660_pm_ops,
	पूर्ण,
	.probe	= ltc1660_probe,
	.हटाओ = ltc1660_हटाओ,
	.id_table = ltc1660_id,
पूर्ण;
module_spi_driver(ltc1660_driver);

MODULE_AUTHOR("Marcus Folkesson <marcus.folkesson@gmail.com>");
MODULE_DESCRIPTION("Linear Technology LTC1660/LTC1665 DAC");
MODULE_LICENSE("GPL v2");
