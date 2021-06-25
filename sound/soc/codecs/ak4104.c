<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AK4104 ALSA SoC (ASoC) driver
 *
 * Copyright (c) 2009 Daniel Mack <daniel@caiaq.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/of_device.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/core.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>

/* AK4104 रेजिस्टरs addresses */
#घोषणा AK4104_REG_CONTROL1		0x00
#घोषणा AK4104_REG_RESERVED		0x01
#घोषणा AK4104_REG_CONTROL2		0x02
#घोषणा AK4104_REG_TX			0x03
#घोषणा AK4104_REG_CHN_STATUS(x)	((x) + 0x04)
#घोषणा AK4104_NUM_REGS			10

#घोषणा AK4104_REG_MASK			0x1f
#घोषणा AK4104_READ			0xc0
#घोषणा AK4104_WRITE			0xe0
#घोषणा AK4104_RESERVED_VAL		0x5b

/* Bit masks क्रम AK4104 रेजिस्टरs */
#घोषणा AK4104_CONTROL1_RSTN		(1 << 0)
#घोषणा AK4104_CONTROL1_PW		(1 << 1)
#घोषणा AK4104_CONTROL1_DIF0		(1 << 2)
#घोषणा AK4104_CONTROL1_DIF1		(1 << 3)

#घोषणा AK4104_CONTROL2_SEL0		(1 << 0)
#घोषणा AK4104_CONTROL2_SEL1		(1 << 1)
#घोषणा AK4104_CONTROL2_MODE		(1 << 2)

#घोषणा AK4104_TX_TXE			(1 << 0)
#घोषणा AK4104_TX_V			(1 << 1)

काष्ठा ak4104_निजी अणु
	काष्ठा regmap *regmap;
	काष्ठा regulator *regulator;
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget ak4104_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_PGA("TXE", AK4104_REG_TX, AK4104_TX_TXE, 0, शून्य, 0),

SND_SOC_DAPM_OUTPUT("TX"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ak4104_dapm_routes[] = अणु
	अणु "TXE", शून्य, "Playback" पूर्ण,
	अणु "TX", शून्य, "TXE" पूर्ण,
पूर्ण;

अटल पूर्णांक ak4104_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
			      अचिन्हित पूर्णांक क्रमmat)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा ak4104_निजी *ak4104 = snd_soc_component_get_drvdata(component);
	पूर्णांक val = 0;
	पूर्णांक ret;

	/* set DAI क्रमmat */
	चयन (क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		val |= AK4104_CONTROL1_DIF0;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		val |= AK4104_CONTROL1_DIF0 | AK4104_CONTROL1_DIF1;
		अवरोध;
	शेष:
		dev_err(component->dev, "invalid dai format\n");
		वापस -EINVAL;
	पूर्ण

	/* This device can only be slave */
	अगर ((क्रमmat & SND_SOC_DAIFMT_MASTER_MASK) != SND_SOC_DAIFMT_CBS_CFS)
		वापस -EINVAL;

	ret = regmap_update_bits(ak4104->regmap, AK4104_REG_CONTROL1,
				 AK4104_CONTROL1_DIF0 | AK4104_CONTROL1_DIF1,
				 val);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ak4104_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ak4104_निजी *ak4104 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret, val = 0;

	/* set the IEC958 bits: consumer mode, no copyright bit */
	val |= IEC958_AES0_CON_NOT_COPYRIGHT;
	regmap_ग_लिखो(ak4104->regmap, AK4104_REG_CHN_STATUS(0), val);

	val = 0;

	चयन (params_rate(params)) अणु
	हाल 22050:
		val |= IEC958_AES3_CON_FS_22050;
		अवरोध;
	हाल 24000:
		val |= IEC958_AES3_CON_FS_24000;
		अवरोध;
	हाल 32000:
		val |= IEC958_AES3_CON_FS_32000;
		अवरोध;
	हाल 44100:
		val |= IEC958_AES3_CON_FS_44100;
		अवरोध;
	हाल 48000:
		val |= IEC958_AES3_CON_FS_48000;
		अवरोध;
	हाल 88200:
		val |= IEC958_AES3_CON_FS_88200;
		अवरोध;
	हाल 96000:
		val |= IEC958_AES3_CON_FS_96000;
		अवरोध;
	हाल 176400:
		val |= IEC958_AES3_CON_FS_176400;
		अवरोध;
	हाल 192000:
		val |= IEC958_AES3_CON_FS_192000;
		अवरोध;
	शेष:
		dev_err(component->dev, "unsupported sampling rate\n");
		वापस -EINVAL;
	पूर्ण

	ret = regmap_ग_लिखो(ak4104->regmap, AK4104_REG_CHN_STATUS(3), val);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops ak4101_dai_ops = अणु
	.hw_params = ak4104_hw_params,
	.set_fmt = ak4104_set_dai_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ak4104_dai = अणु
	.name = "ak4104-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_22050 | SNDRV_PCM_RATE_32000 |
			 SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000 |
			 SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000 |
			 SNDRV_PCM_RATE_176400 | SNDRV_PCM_RATE_192000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE  |
			   SNDRV_PCM_FMTBIT_S24_3LE |
			   SNDRV_PCM_FMTBIT_S24_LE
	पूर्ण,
	.ops = &ak4101_dai_ops,
पूर्ण;

अटल पूर्णांक ak4104_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ak4104_निजी *ak4104 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = regulator_enable(ak4104->regulator);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Unable to enable regulator: %d\n", ret);
		वापस ret;
	पूर्ण

	/* set घातer-up and non-reset bits */
	ret = regmap_update_bits(ak4104->regmap, AK4104_REG_CONTROL1,
				 AK4104_CONTROL1_PW | AK4104_CONTROL1_RSTN,
				 AK4104_CONTROL1_PW | AK4104_CONTROL1_RSTN);
	अगर (ret < 0)
		जाओ निकास_disable_regulator;

	/* enable transmitter */
	ret = regmap_update_bits(ak4104->regmap, AK4104_REG_TX,
				 AK4104_TX_TXE, AK4104_TX_TXE);
	अगर (ret < 0)
		जाओ निकास_disable_regulator;

	वापस 0;

निकास_disable_regulator:
	regulator_disable(ak4104->regulator);
	वापस ret;
पूर्ण

अटल व्योम ak4104_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ak4104_निजी *ak4104 = snd_soc_component_get_drvdata(component);

	regmap_update_bits(ak4104->regmap, AK4104_REG_CONTROL1,
			   AK4104_CONTROL1_PW | AK4104_CONTROL1_RSTN, 0);
	regulator_disable(ak4104->regulator);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ak4104_soc_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ak4104_निजी *priv = snd_soc_component_get_drvdata(component);

	regulator_disable(priv->regulator);

	वापस 0;
पूर्ण

अटल पूर्णांक ak4104_soc_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ak4104_निजी *priv = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = regulator_enable(priv->regulator);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा ak4104_soc_suspend	शून्य
#घोषणा ak4104_soc_resume	शून्य
#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_device_ak4104 = अणु
	.probe			= ak4104_probe,
	.हटाओ			= ak4104_हटाओ,
	.suspend		= ak4104_soc_suspend,
	.resume			= ak4104_soc_resume,
	.dapm_widमाला_लो		= ak4104_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ak4104_dapm_widमाला_लो),
	.dapm_routes		= ak4104_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(ak4104_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ak4104_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = AK4104_NUM_REGS - 1,
	.पढ़ो_flag_mask = AK4104_READ,
	.ग_लिखो_flag_mask = AK4104_WRITE,

	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक ak4104_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ak4104_निजी *ak4104;
	काष्ठा gpio_desc *reset_gpiod;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	spi->bits_per_word = 8;
	spi->mode = SPI_MODE_0;
	ret = spi_setup(spi);
	अगर (ret < 0)
		वापस ret;

	ak4104 = devm_kzalloc(&spi->dev, माप(काष्ठा ak4104_निजी),
			      GFP_KERNEL);
	अगर (ak4104 == शून्य)
		वापस -ENOMEM;

	ak4104->regulator = devm_regulator_get(&spi->dev, "vdd");
	अगर (IS_ERR(ak4104->regulator)) अणु
		ret = PTR_ERR(ak4104->regulator);
		dev_err(&spi->dev, "Unable to get Vdd regulator: %d\n", ret);
		वापस ret;
	पूर्ण

	ak4104->regmap = devm_regmap_init_spi(spi, &ak4104_regmap);
	अगर (IS_ERR(ak4104->regmap)) अणु
		ret = PTR_ERR(ak4104->regmap);
		वापस ret;
	पूर्ण

	reset_gpiod = devm_gpiod_get_optional(&spi->dev, "reset",
					      GPIOD_OUT_HIGH);
	अगर (PTR_ERR(reset_gpiod) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	/* पढ़ो the 'reserved' रेजिस्टर - according to the datasheet, it
	 * should contain 0x5b. Not a good way to verअगरy the presence of
	 * the device, but there is no hardware ID रेजिस्टर. */
	ret = regmap_पढ़ो(ak4104->regmap, AK4104_REG_RESERVED, &val);
	अगर (ret != 0)
		वापस ret;
	अगर (val != AK4104_RESERVED_VAL)
		वापस -ENODEV;

	spi_set_drvdata(spi, ak4104);

	ret = devm_snd_soc_रेजिस्टर_component(&spi->dev,
			&soc_component_device_ak4104, &ak4104_dai, 1);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id ak4104_of_match[] = अणु
	अणु .compatible = "asahi-kasei,ak4104", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ak4104_of_match);

अटल स्थिर काष्ठा spi_device_id ak4104_id_table[] = अणु
	अणु "ak4104", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, ak4104_id_table);

अटल काष्ठा spi_driver ak4104_spi_driver = अणु
	.driver  = अणु
		.name   = "ak4104",
		.of_match_table = ak4104_of_match,
	पूर्ण,
	.id_table = ak4104_id_table,
	.probe  = ak4104_spi_probe,
पूर्ण;

module_spi_driver(ak4104_spi_driver);

MODULE_AUTHOR("Daniel Mack <daniel@caiaq.de>");
MODULE_DESCRIPTION("Asahi Kasei AK4104 ALSA SoC driver");
MODULE_LICENSE("GPL");

