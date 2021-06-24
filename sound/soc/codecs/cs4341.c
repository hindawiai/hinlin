<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 *  Cirrus Logic CS4341A ALSA SoC Codec Driver
 *  Author: Alexander Shiyan <shc_work@mail.ru>
 */

#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>

#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#घोषणा CS4341_REG_MODE1	0x00
#घोषणा CS4341_REG_MODE2	0x01
#घोषणा CS4341_REG_MIX		0x02
#घोषणा CS4341_REG_VOLA		0x03
#घोषणा CS4341_REG_VOLB		0x04

#घोषणा CS4341_MODE2_DIF	(7 << 4)
#घोषणा CS4341_MODE2_DIF_I2S_24	(0 << 4)
#घोषणा CS4341_MODE2_DIF_I2S_16	(1 << 4)
#घोषणा CS4341_MODE2_DIF_LJ_24	(2 << 4)
#घोषणा CS4341_MODE2_DIF_RJ_24	(3 << 4)
#घोषणा CS4341_MODE2_DIF_RJ_16	(5 << 4)
#घोषणा CS4341_VOLX_MUTE	(1 << 7)

काष्ठा cs4341_priv अणु
	अचिन्हित पूर्णांक		fmt;
	काष्ठा regmap		*regmap;
	काष्ठा regmap_config	regcfg;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष cs4341_reg_शेषs[] = अणु
	अणु CS4341_REG_MODE1,	0x00 पूर्ण,
	अणु CS4341_REG_MODE2,	0x82 पूर्ण,
	अणु CS4341_REG_MIX,	0x49 पूर्ण,
	अणु CS4341_REG_VOLA,	0x80 पूर्ण,
	अणु CS4341_REG_VOLB,	0x80 पूर्ण,
पूर्ण;

अटल पूर्णांक cs4341_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक क्रमmat)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs4341_priv *cs4341 = snd_soc_component_get_drvdata(component);

	चयन (क्रमmat & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (क्रमmat & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_LEFT_J:
	हाल SND_SOC_DAIFMT_RIGHT_J:
		cs4341->fmt = क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs4341_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs4341_priv *cs4341 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक mode = 0;
	पूर्णांक b24 = 0;

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S24_LE:
		b24 = 1;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16_LE:
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported PCM format 0x%08x.\n",
			params_क्रमmat(params));
		वापस -EINVAL;
	पूर्ण

	चयन (cs4341->fmt) अणु
	हाल SND_SOC_DAIFMT_I2S:
		mode = b24 ? CS4341_MODE2_DIF_I2S_24 : CS4341_MODE2_DIF_I2S_16;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		mode = CS4341_MODE2_DIF_LJ_24;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		mode = b24 ? CS4341_MODE2_DIF_RJ_24 : CS4341_MODE2_DIF_RJ_16;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported DAI format 0x%08x.\n",
			cs4341->fmt);
		वापस -EINVAL;
	पूर्ण

	वापस snd_soc_component_update_bits(component, CS4341_REG_MODE2,
					     CS4341_MODE2_DIF, mode);
पूर्ण

अटल पूर्णांक cs4341_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक ret;

	ret = snd_soc_component_update_bits(component, CS4341_REG_VOLA,
					    CS4341_VOLX_MUTE,
					    mute ? CS4341_VOLX_MUTE : 0);
	अगर (ret < 0)
		वापस ret;

	वापस snd_soc_component_update_bits(component, CS4341_REG_VOLB,
					     CS4341_VOLX_MUTE,
					     mute ? CS4341_VOLX_MUTE : 0);
पूर्ण

अटल DECLARE_TLV_DB_SCALE(out_tlv, -9000, 100, 0);

अटल स्थिर अक्षर * स्थिर deemph[] = अणु
	"None", "44.1k", "48k", "32k",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत deemph_क्रमागत =
	SOC_ENUM_SINGLE(CS4341_REG_MODE2, 2, 4, deemph);

अटल स्थिर अक्षर * स्थिर srzc[] = अणु
	"Immediate", "Zero Cross", "Soft Ramp", "SR on ZC",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत srzc_क्रमागत =
	SOC_ENUM_SINGLE(CS4341_REG_MIX, 5, 4, srzc);


अटल स्थिर काष्ठा snd_soc_dapm_widget cs4341_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("HiFi DAC", शून्य, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_OUTPUT("OutA"),
	SND_SOC_DAPM_OUTPUT("OutB"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cs4341_routes[] = अणु
	अणु "OutA", शून्य, "HiFi DAC" पूर्ण,
	अणु "OutB", शून्य, "HiFi DAC" पूर्ण,
	अणु "DAC Playback", शून्य, "OutA" पूर्ण,
	अणु "DAC Playback", शून्य, "OutB" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new cs4341_controls[] = अणु
	SOC_DOUBLE_R_TLV("Master Playback Volume",
			 CS4341_REG_VOLA, CS4341_REG_VOLB, 0, 90, 1, out_tlv),
	SOC_ENUM("De-Emphasis Control", deemph_क्रमागत),
	SOC_ENUM("Soft Ramp Zero Cross Control", srzc_क्रमागत),
	SOC_SINGLE("Auto-Mute Switch", CS4341_REG_MODE2, 7, 1, 0),
	SOC_SINGLE("Popguard Transient Switch", CS4341_REG_MODE2, 1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops cs4341_dai_ops = अणु
	.set_fmt	= cs4341_set_fmt,
	.hw_params	= cs4341_hw_params,
	.mute_stream	= cs4341_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver cs4341_dai = अणु
	.name			= "cs4341a-hifi",
	.playback		= अणु
		.stream_name	= "DAC Playback",
		.channels_min	= 1,
		.channels_max	= 2,
		.rates		= SNDRV_PCM_RATE_8000_96000,
		.क्रमmats	= SNDRV_PCM_FMTBIT_S16_LE |
				  SNDRV_PCM_FMTBIT_S24_LE,
	पूर्ण,
	.ops			= &cs4341_dai_ops,
	.symmetric_rate		= 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_cs4341 = अणु
	.controls		= cs4341_controls,
	.num_controls		= ARRAY_SIZE(cs4341_controls),
	.dapm_widमाला_लो		= cs4341_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(cs4341_dapm_widमाला_लो),
	.dapm_routes		= cs4341_routes,
	.num_dapm_routes	= ARRAY_SIZE(cs4341_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id __maybe_unused cs4341_dt_ids[] = अणु
	अणु .compatible = "cirrus,cs4341a", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, cs4341_dt_ids);

अटल पूर्णांक cs4341_probe(काष्ठा device *dev)
अणु
	काष्ठा cs4341_priv *cs4341 = dev_get_drvdata(dev);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(cs4341_reg_शेषs); i++)
		regmap_ग_लिखो(cs4341->regmap, cs4341_reg_शेषs[i].reg,
			     cs4341_reg_शेषs[i].def);

	वापस devm_snd_soc_रेजिस्टर_component(dev, &soc_component_cs4341,
					       &cs4341_dai, 1);
पूर्ण

#अगर IS_ENABLED(CONFIG_I2C)
अटल पूर्णांक cs4341_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cs4341_priv *cs4341;

	cs4341 = devm_kzalloc(&i2c->dev, माप(*cs4341), GFP_KERNEL);
	अगर (!cs4341)
		वापस -ENOMEM;

	i2c_set_clientdata(i2c, cs4341);

	cs4341->regcfg.reg_bits		= 8;
	cs4341->regcfg.val_bits		= 8;
	cs4341->regcfg.max_रेजिस्टर	= CS4341_REG_VOLB;
	cs4341->regcfg.cache_type	= REGCACHE_FLAT;
	cs4341->regcfg.reg_शेषs	= cs4341_reg_शेषs;
	cs4341->regcfg.num_reg_शेषs	= ARRAY_SIZE(cs4341_reg_शेषs);
	cs4341->regmap = devm_regmap_init_i2c(i2c, &cs4341->regcfg);
	अगर (IS_ERR(cs4341->regmap))
		वापस PTR_ERR(cs4341->regmap);

	वापस cs4341_probe(&i2c->dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id cs4341_i2c_id[] = अणु
	अणु "cs4341", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, cs4341_i2c_id);

अटल काष्ठा i2c_driver cs4341_i2c_driver = अणु
	.driver = अणु
		.name = "cs4341-i2c",
		.of_match_table = of_match_ptr(cs4341_dt_ids),
	पूर्ण,
	.probe = cs4341_i2c_probe,
	.id_table = cs4341_i2c_id,
पूर्ण;
#पूर्ण_अगर

#अगर defined(CONFIG_SPI_MASTER)
अटल bool cs4341_reg_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	वापस false;
पूर्ण

अटल पूर्णांक cs4341_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा cs4341_priv *cs4341;
	पूर्णांक ret;

	cs4341 = devm_kzalloc(&spi->dev, माप(*cs4341), GFP_KERNEL);
	अगर (!cs4341)
		वापस -ENOMEM;

	अगर (!spi->bits_per_word)
		spi->bits_per_word = 8;
	अगर (!spi->max_speed_hz)
		spi->max_speed_hz = 6000000;
	ret = spi_setup(spi);
	अगर (ret)
		वापस ret;

	spi_set_drvdata(spi, cs4341);

	cs4341->regcfg.reg_bits		= 16;
	cs4341->regcfg.val_bits		= 8;
	cs4341->regcfg.ग_लिखो_flag_mask	= 0x20;
	cs4341->regcfg.max_रेजिस्टर	= CS4341_REG_VOLB;
	cs4341->regcfg.cache_type	= REGCACHE_FLAT;
	cs4341->regcfg.पढ़ोable_reg	= cs4341_reg_पढ़ोable;
	cs4341->regcfg.reg_शेषs	= cs4341_reg_शेषs;
	cs4341->regcfg.num_reg_शेषs	= ARRAY_SIZE(cs4341_reg_शेषs);
	cs4341->regmap = devm_regmap_init_spi(spi, &cs4341->regcfg);
	अगर (IS_ERR(cs4341->regmap))
		वापस PTR_ERR(cs4341->regmap);

	वापस cs4341_probe(&spi->dev);
पूर्ण

अटल काष्ठा spi_driver cs4341_spi_driver = अणु
	.driver = अणु
		.name = "cs4341-spi",
		.of_match_table = of_match_ptr(cs4341_dt_ids),
	पूर्ण,
	.probe = cs4341_spi_probe,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init cs4341_init(व्योम)
अणु
	पूर्णांक ret = 0;

#अगर IS_ENABLED(CONFIG_I2C)
	ret = i2c_add_driver(&cs4341_i2c_driver);
	अगर (ret)
		वापस ret;
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	ret = spi_रेजिस्टर_driver(&cs4341_spi_driver);
#पूर्ण_अगर

	वापस ret;
पूर्ण
module_init(cs4341_init);

अटल व्योम __निकास cs4341_निकास(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_I2C)
	i2c_del_driver(&cs4341_i2c_driver);
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	spi_unरेजिस्टर_driver(&cs4341_spi_driver);
#पूर्ण_अगर
पूर्ण
module_निकास(cs4341_निकास);

MODULE_AUTHOR("Alexander Shiyan <shc_work@mail.ru>");
MODULE_DESCRIPTION("Cirrus Logic CS4341 ALSA SoC Codec Driver");
MODULE_LICENSE("GPL");
