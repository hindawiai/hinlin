<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8728.c  --  WM8728 ALSA SoC Audio driver
 *
 * Copyright 2008 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "wm8728.h"

/*
 * We can't पढ़ो the WM8728 रेजिस्टर space so we cache them instead.
 * Note that the शेषs here aren't the physical शेषs, we latch
 * the volume update bits, mute the output and enable infinite zero
 * detect.
 */
अटल स्थिर काष्ठा reg_शेष wm8728_reg_शेषs[] = अणु
	अणु 0, 0x1ff पूर्ण,
	अणु 1, 0x1ff पूर्ण,
	अणु 2, 0x001 पूर्ण,
	अणु 3, 0x100 पूर्ण,
पूर्ण;

/* codec निजी data */
काष्ठा wm8728_priv अणु
	काष्ठा regmap *regmap;
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(wm8728_tlv, -12750, 50, 1);

अटल स्थिर काष्ठा snd_kcontrol_new wm8728_snd_controls[] = अणु

SOC_DOUBLE_R_TLV("Digital Playback Volume", WM8728_DACLVOL, WM8728_DACRVOL,
		 0, 255, 0, wm8728_tlv),

SOC_SINGLE("Deemphasis", WM8728_DACCTL, 1, 1, 0),
पूर्ण;

/*
 * DAPM controls.
 */
अटल स्थिर काष्ठा snd_soc_dapm_widget wm8728_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_DAC("DAC", "HiFi Playback", SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_OUTPUT("VOUTL"),
SND_SOC_DAPM_OUTPUT("VOUTR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8728_पूर्णांकercon[] = अणु
	अणु"VOUTL", शून्य, "DAC"पूर्ण,
	अणु"VOUTR", शून्य, "DAC"पूर्ण,
पूर्ण;

अटल पूर्णांक wm8728_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 mute_reg = snd_soc_component_पढ़ो(component, WM8728_DACCTL);

	अगर (mute)
		snd_soc_component_ग_लिखो(component, WM8728_DACCTL, mute_reg | 1);
	अन्यथा
		snd_soc_component_ग_लिखो(component, WM8728_DACCTL, mute_reg & ~1);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8728_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 dac = snd_soc_component_पढ़ो(component, WM8728_DACCTL);

	dac &= ~0x18;

	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		dac |= 0x10;
		अवरोध;
	हाल 24:
		dac |= 0x08;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8728_DACCTL, dac);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8728_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 अगरace = snd_soc_component_पढ़ो(component, WM8728_IFCTL);

	/* Currently only I2S is supported by the driver, though the
	 * hardware is more flexible.
	 */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरace |= 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* The hardware only support full slave mode */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अगरace &= ~0x22;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		अगरace |=  0x20;
		अगरace &= ~0x02;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		अगरace |= 0x02;
		अगरace &= ~0x20;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		अगरace |= 0x22;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8728_IFCTL, अगरace);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8728_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8728_priv *wm8728 = snd_soc_component_get_drvdata(component);
	u16 reg;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
	हाल SND_SOC_BIAS_PREPARE:
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			/* Power everything up... */
			reg = snd_soc_component_पढ़ो(component, WM8728_DACCTL);
			snd_soc_component_ग_लिखो(component, WM8728_DACCTL, reg & ~0x4);

			/* ..then sync in the रेजिस्टर cache. */
			regcache_sync(wm8728->regmap);
		पूर्ण
		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		reg = snd_soc_component_पढ़ो(component, WM8728_DACCTL);
		snd_soc_component_ग_लिखो(component, WM8728_DACCTL, reg | 0x4);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा WM8728_RATES (SNDRV_PCM_RATE_8000_192000)

#घोषणा WM8728_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
	SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8728_dai_ops = अणु
	.hw_params	= wm8728_hw_params,
	.mute_stream	= wm8728_mute,
	.set_fmt	= wm8728_set_dai_fmt,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8728_dai = अणु
	.name = "wm8728-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = WM8728_RATES,
		.क्रमmats = WM8728_FORMATS,
	पूर्ण,
	.ops = &wm8728_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8728 = अणु
	.set_bias_level		= wm8728_set_bias_level,
	.controls		= wm8728_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8728_snd_controls),
	.dapm_widमाला_लो		= wm8728_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8728_dapm_widमाला_लो),
	.dapm_routes		= wm8728_पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(wm8728_पूर्णांकercon),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id wm8728_of_match[] = अणु
	अणु .compatible = "wlf,wm8728", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wm8728_of_match);

अटल स्थिर काष्ठा regmap_config wm8728_regmap = अणु
	.reg_bits = 7,
	.val_bits = 9,
	.max_रेजिस्टर = WM8728_IFCTL,

	.reg_शेषs = wm8728_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8728_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

#अगर defined(CONFIG_SPI_MASTER)
अटल पूर्णांक wm8728_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा wm8728_priv *wm8728;
	पूर्णांक ret;

	wm8728 = devm_kzalloc(&spi->dev, माप(काष्ठा wm8728_priv),
			      GFP_KERNEL);
	अगर (wm8728 == शून्य)
		वापस -ENOMEM;

	wm8728->regmap = devm_regmap_init_spi(spi, &wm8728_regmap);
	अगर (IS_ERR(wm8728->regmap))
		वापस PTR_ERR(wm8728->regmap);

	spi_set_drvdata(spi, wm8728);

	ret = devm_snd_soc_रेजिस्टर_component(&spi->dev,
			&soc_component_dev_wm8728, &wm8728_dai, 1);

	वापस ret;
पूर्ण

अटल काष्ठा spi_driver wm8728_spi_driver = अणु
	.driver = अणु
		.name	= "wm8728",
		.of_match_table = wm8728_of_match,
	पूर्ण,
	.probe		= wm8728_spi_probe,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SPI_MASTER */

#अगर IS_ENABLED(CONFIG_I2C)
अटल पूर्णांक wm8728_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8728_priv *wm8728;
	पूर्णांक ret;

	wm8728 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8728_priv),
			      GFP_KERNEL);
	अगर (wm8728 == शून्य)
		वापस -ENOMEM;

	wm8728->regmap = devm_regmap_init_i2c(i2c, &wm8728_regmap);
	अगर (IS_ERR(wm8728->regmap))
		वापस PTR_ERR(wm8728->regmap);

	i2c_set_clientdata(i2c, wm8728);

	ret =  devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_wm8728, &wm8728_dai, 1);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8728_i2c_id[] = अणु
	अणु "wm8728", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8728_i2c_id);

अटल काष्ठा i2c_driver wm8728_i2c_driver = अणु
	.driver = अणु
		.name = "wm8728",
		.of_match_table = wm8728_of_match,
	पूर्ण,
	.probe =    wm8728_i2c_probe,
	.id_table = wm8728_i2c_id,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init wm8728_modinit(व्योम)
अणु
	पूर्णांक ret = 0;
#अगर IS_ENABLED(CONFIG_I2C)
	ret = i2c_add_driver(&wm8728_i2c_driver);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register wm8728 I2C driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	ret = spi_रेजिस्टर_driver(&wm8728_spi_driver);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register wm8728 SPI driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
	वापस ret;
पूर्ण
module_init(wm8728_modinit);

अटल व्योम __निकास wm8728_निकास(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_I2C)
	i2c_del_driver(&wm8728_i2c_driver);
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	spi_unरेजिस्टर_driver(&wm8728_spi_driver);
#पूर्ण_अगर
पूर्ण
module_निकास(wm8728_निकास);

MODULE_DESCRIPTION("ASoC WM8728 driver");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
