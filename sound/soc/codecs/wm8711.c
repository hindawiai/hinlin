<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8711.c  --  WM8711 ALSA SoC Audio driver
 *
 * Copyright 2006 Wolfson Microelectronics
 *
 * Author: Mike Arthur <Mike.Arthur@wolfsonmicro.com>
 *
 * Based on wm8731.c by Riअक्षरd Purdie
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <sound/initval.h>

#समावेश "wm8711.h"

/* codec निजी data */
काष्ठा wm8711_priv अणु
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक sysclk;
पूर्ण;

/*
 * wm8711 रेजिस्टर cache
 * We can't पढ़ो the WM8711 रेजिस्टर space when we are
 * using 2 wire क्रम device control, so we cache them instead.
 * There is no poपूर्णांक in caching the reset रेजिस्टर
 */
अटल स्थिर काष्ठा reg_शेष wm8711_reg_शेषs[] = अणु
	अणु 0, 0x0079 पूर्ण, अणु 1, 0x0079 पूर्ण, अणु 2, 0x000a पूर्ण, अणु 3, 0x0008 पूर्ण,
	अणु 4, 0x009f पूर्ण, अणु 5, 0x000a पूर्ण, अणु 6, 0x0000 पूर्ण, अणु 7, 0x0000 पूर्ण,
पूर्ण;

अटल bool wm8711_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8711_RESET:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

#घोषणा wm8711_reset(c)	snd_soc_component_ग_लिखो(c, WM8711_RESET, 0)

अटल स्थिर DECLARE_TLV_DB_SCALE(out_tlv, -12100, 100, 1);

अटल स्थिर काष्ठा snd_kcontrol_new wm8711_snd_controls[] = अणु

SOC_DOUBLE_R_TLV("Master Playback Volume", WM8711_LOUT1V, WM8711_ROUT1V,
		 0, 127, 0, out_tlv),
SOC_DOUBLE_R("Master Playback ZC Switch", WM8711_LOUT1V, WM8711_ROUT1V,
	7, 1, 0),

पूर्ण;

/* Output Mixer */
अटल स्थिर काष्ठा snd_kcontrol_new wm8711_output_mixer_controls[] = अणु
SOC_DAPM_SINGLE("Line Bypass Switch", WM8711_APANA, 3, 1, 0),
SOC_DAPM_SINGLE("HiFi Playback Switch", WM8711_APANA, 4, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8711_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_MIXER("Output Mixer", WM8711_PWR, 4, 1,
	&wm8711_output_mixer_controls[0],
	ARRAY_SIZE(wm8711_output_mixer_controls)),
SND_SOC_DAPM_DAC("DAC", "HiFi Playback", WM8711_PWR, 3, 1),
SND_SOC_DAPM_OUTPUT("LOUT"),
SND_SOC_DAPM_OUTPUT("LHPOUT"),
SND_SOC_DAPM_OUTPUT("ROUT"),
SND_SOC_DAPM_OUTPUT("RHPOUT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8711_पूर्णांकercon[] = अणु
	/* output mixer */
	अणु"Output Mixer", "Line Bypass Switch", "Line Input"पूर्ण,
	अणु"Output Mixer", "HiFi Playback Switch", "DAC"पूर्ण,

	/* outमाला_दो */
	अणु"RHPOUT", शून्य, "Output Mixer"पूर्ण,
	अणु"ROUT", शून्य, "Output Mixer"पूर्ण,
	अणु"LHPOUT", शून्य, "Output Mixer"पूर्ण,
	अणु"LOUT", शून्य, "Output Mixer"पूर्ण,
पूर्ण;

काष्ठा _coeff_भाग अणु
	u32 mclk;
	u32 rate;
	u16 fs;
	u8 sr:4;
	u8 bosr:1;
	u8 usb:1;
पूर्ण;

/* codec mclk घड़ी भागider coefficients */
अटल स्थिर काष्ठा _coeff_भाग coeff_भाग[] = अणु
	/* 48k */
	अणु12288000, 48000, 256, 0x0, 0x0, 0x0पूर्ण,
	अणु18432000, 48000, 384, 0x0, 0x1, 0x0पूर्ण,
	अणु12000000, 48000, 250, 0x0, 0x0, 0x1पूर्ण,

	/* 32k */
	अणु12288000, 32000, 384, 0x6, 0x0, 0x0पूर्ण,
	अणु18432000, 32000, 576, 0x6, 0x1, 0x0पूर्ण,
	अणु12000000, 32000, 375, 0x6, 0x0, 0x1पूर्ण,

	/* 8k */
	अणु12288000, 8000, 1536, 0x3, 0x0, 0x0पूर्ण,
	अणु18432000, 8000, 2304, 0x3, 0x1, 0x0पूर्ण,
	अणु11289600, 8000, 1408, 0xb, 0x0, 0x0पूर्ण,
	अणु16934400, 8000, 2112, 0xb, 0x1, 0x0पूर्ण,
	अणु12000000, 8000, 1500, 0x3, 0x0, 0x1पूर्ण,

	/* 96k */
	अणु12288000, 96000, 128, 0x7, 0x0, 0x0पूर्ण,
	अणु18432000, 96000, 192, 0x7, 0x1, 0x0पूर्ण,
	अणु12000000, 96000, 125, 0x7, 0x0, 0x1पूर्ण,

	/* 44.1k */
	अणु11289600, 44100, 256, 0x8, 0x0, 0x0पूर्ण,
	अणु16934400, 44100, 384, 0x8, 0x1, 0x0पूर्ण,
	अणु12000000, 44100, 272, 0x8, 0x1, 0x1पूर्ण,

	/* 88.2k */
	अणु11289600, 88200, 128, 0xf, 0x0, 0x0पूर्ण,
	अणु16934400, 88200, 192, 0xf, 0x1, 0x0पूर्ण,
	अणु12000000, 88200, 136, 0xf, 0x1, 0x1पूर्ण,
पूर्ण;

अटल अंतरभूत पूर्णांक get_coeff(पूर्णांक mclk, पूर्णांक rate)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(coeff_भाग); i++) अणु
		अगर (coeff_भाग[i].rate == rate && coeff_भाग[i].mclk == mclk)
			वापस i;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wm8711_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8711_priv *wm8711 =  snd_soc_component_get_drvdata(component);
	u16 अगरace = snd_soc_component_पढ़ो(component, WM8711_IFACE) & 0xfff3;
	पूर्णांक i = get_coeff(wm8711->sysclk, params_rate(params));
	u16 srate = (coeff_भाग[i].sr << 2) |
		(coeff_भाग[i].bosr << 1) | coeff_भाग[i].usb;

	snd_soc_component_ग_लिखो(component, WM8711_SRATE, srate);

	/* bit size */
	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		अगरace |= 0x0004;
		अवरोध;
	हाल 24:
		अगरace |= 0x0008;
		अवरोध;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8711_IFACE, अगरace);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8711_pcm_prepare(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	/* set active */
	snd_soc_component_ग_लिखो(component, WM8711_ACTIVE, 0x0001);

	वापस 0;
पूर्ण

अटल व्योम wm8711_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	/* deactivate */
	अगर (!snd_soc_component_active(component)) अणु
		udelay(50);
		snd_soc_component_ग_लिखो(component, WM8711_ACTIVE, 0x0);
	पूर्ण
पूर्ण

अटल पूर्णांक wm8711_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u16 mute_reg = snd_soc_component_पढ़ो(component, WM8711_APDIGI) & 0xfff7;

	अगर (mute)
		snd_soc_component_ग_लिखो(component, WM8711_APDIGI, mute_reg | 0x8);
	अन्यथा
		snd_soc_component_ग_लिखो(component, WM8711_APDIGI, mute_reg);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8711_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8711_priv *wm8711 =  snd_soc_component_get_drvdata(component);

	चयन (freq) अणु
	हाल 11289600:
	हाल 12000000:
	हाल 12288000:
	हाल 16934400:
	हाल 18432000:
		wm8711->sysclk = freq;
		वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wm8711_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 अगरace = snd_soc_component_पढ़ो(component, WM8711_IFACE) & 0x000c;

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अगरace |= 0x0040;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरace |= 0x0002;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरace |= 0x0001;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		अगरace |= 0x0003;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		अगरace |= 0x0013;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		अगरace |= 0x0090;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		अगरace |= 0x0080;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		अगरace |= 0x0010;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* set अगरace */
	snd_soc_component_ग_लिखो(component, WM8711_IFACE, अगरace);
	वापस 0;
पूर्ण

अटल पूर्णांक wm8711_set_bias_level(काष्ठा snd_soc_component *component,
	क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8711_priv *wm8711 = snd_soc_component_get_drvdata(component);
	u16 reg = snd_soc_component_पढ़ो(component, WM8711_PWR) & 0xff7f;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		snd_soc_component_ग_लिखो(component, WM8711_PWR, reg);
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			regcache_sync(wm8711->regmap);

		snd_soc_component_ग_लिखो(component, WM8711_PWR, reg | 0x0040);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_ग_लिखो(component, WM8711_ACTIVE, 0x0);
		snd_soc_component_ग_लिखो(component, WM8711_PWR, 0xffff);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा WM8711_RATES SNDRV_PCM_RATE_8000_96000

#घोषणा WM8711_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
	SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8711_ops = अणु
	.prepare = wm8711_pcm_prepare,
	.hw_params = wm8711_hw_params,
	.shutकरोwn = wm8711_shutकरोwn,
	.mute_stream = wm8711_mute,
	.set_sysclk = wm8711_set_dai_sysclk,
	.set_fmt = wm8711_set_dai_fmt,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8711_dai = अणु
	.name = "wm8711-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = WM8711_RATES,
		.क्रमmats = WM8711_FORMATS,
	पूर्ण,
	.ops = &wm8711_ops,
पूर्ण;

अटल पूर्णांक wm8711_probe(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret;

	ret = wm8711_reset(component);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to issue reset\n");
		वापस ret;
	पूर्ण

	/* Latch the update bits */
	snd_soc_component_update_bits(component, WM8711_LOUT1V, 0x0100, 0x0100);
	snd_soc_component_update_bits(component, WM8711_ROUT1V, 0x0100, 0x0100);

	वापस ret;

पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8711 = अणु
	.probe			= wm8711_probe,
	.set_bias_level		= wm8711_set_bias_level,
	.controls		= wm8711_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8711_snd_controls),
	.dapm_widमाला_लो		= wm8711_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8711_dapm_widमाला_लो),
	.dapm_routes		= wm8711_पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(wm8711_पूर्णांकercon),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id wm8711_of_match[] = अणु
	अणु .compatible = "wlf,wm8711", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wm8711_of_match);

अटल स्थिर काष्ठा regmap_config wm8711_regmap = अणु
	.reg_bits = 7,
	.val_bits = 9,
	.max_रेजिस्टर = WM8711_RESET,

	.reg_शेषs = wm8711_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8711_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,

	.अस्थिर_reg = wm8711_अस्थिर,
पूर्ण;

#अगर defined(CONFIG_SPI_MASTER)
अटल पूर्णांक wm8711_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा wm8711_priv *wm8711;
	पूर्णांक ret;

	wm8711 = devm_kzalloc(&spi->dev, माप(काष्ठा wm8711_priv),
			      GFP_KERNEL);
	अगर (wm8711 == शून्य)
		वापस -ENOMEM;

	wm8711->regmap = devm_regmap_init_spi(spi, &wm8711_regmap);
	अगर (IS_ERR(wm8711->regmap))
		वापस PTR_ERR(wm8711->regmap);

	spi_set_drvdata(spi, wm8711);

	ret = devm_snd_soc_रेजिस्टर_component(&spi->dev,
			&soc_component_dev_wm8711, &wm8711_dai, 1);

	वापस ret;
पूर्ण

अटल काष्ठा spi_driver wm8711_spi_driver = अणु
	.driver = अणु
		.name	= "wm8711",
		.of_match_table = wm8711_of_match,
	पूर्ण,
	.probe		= wm8711_spi_probe,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SPI_MASTER */

#अगर IS_ENABLED(CONFIG_I2C)
अटल पूर्णांक wm8711_i2c_probe(काष्ठा i2c_client *client,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8711_priv *wm8711;
	पूर्णांक ret;

	wm8711 = devm_kzalloc(&client->dev, माप(काष्ठा wm8711_priv),
			      GFP_KERNEL);
	अगर (wm8711 == शून्य)
		वापस -ENOMEM;

	wm8711->regmap = devm_regmap_init_i2c(client, &wm8711_regmap);
	अगर (IS_ERR(wm8711->regmap))
		वापस PTR_ERR(wm8711->regmap);

	i2c_set_clientdata(client, wm8711);

	ret = devm_snd_soc_रेजिस्टर_component(&client->dev,
			&soc_component_dev_wm8711, &wm8711_dai, 1);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8711_i2c_id[] = अणु
	अणु "wm8711", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8711_i2c_id);

अटल काष्ठा i2c_driver wm8711_i2c_driver = अणु
	.driver = अणु
		.name = "wm8711",
		.of_match_table = wm8711_of_match,
	पूर्ण,
	.probe =    wm8711_i2c_probe,
	.id_table = wm8711_i2c_id,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init wm8711_modinit(व्योम)
अणु
	पूर्णांक ret;
#अगर IS_ENABLED(CONFIG_I2C)
	ret = i2c_add_driver(&wm8711_i2c_driver);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register WM8711 I2C driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	ret = spi_रेजिस्टर_driver(&wm8711_spi_driver);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register WM8711 SPI driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण
module_init(wm8711_modinit);

अटल व्योम __निकास wm8711_निकास(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_I2C)
	i2c_del_driver(&wm8711_i2c_driver);
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	spi_unरेजिस्टर_driver(&wm8711_spi_driver);
#पूर्ण_अगर
पूर्ण
module_निकास(wm8711_निकास);

MODULE_DESCRIPTION("ASoC WM8711 driver");
MODULE_AUTHOR("Mike Arthur");
MODULE_LICENSE("GPL");
