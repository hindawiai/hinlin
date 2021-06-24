<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8776.c  --  WM8776 ALSA SoC Audio driver
 *
 * Copyright 2009-12 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 *
 * TODO: Input ALC/limiter support
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "wm8776.h"

क्रमागत wm8776_chip_type अणु
	WM8775 = 1,
	WM8776,
पूर्ण;

/* codec निजी data */
काष्ठा wm8776_priv अणु
	काष्ठा regmap *regmap;
	पूर्णांक sysclk[2];
पूर्ण;

अटल स्थिर काष्ठा reg_शेष wm8776_reg_शेषs[] = अणु
	अणु  0, 0x79 पूर्ण,
	अणु  1, 0x79 पूर्ण,
	अणु  2, 0x79 पूर्ण,
	अणु  3, 0xff पूर्ण,
	अणु  4, 0xff पूर्ण,
	अणु  5, 0xff पूर्ण,
	अणु  6, 0x00 पूर्ण,
	अणु  7, 0x90 पूर्ण,
	अणु  8, 0x00 पूर्ण,
	अणु  9, 0x00 पूर्ण,
	अणु 10, 0x22 पूर्ण,
	अणु 11, 0x22 पूर्ण,
	अणु 12, 0x22 पूर्ण,
	अणु 13, 0x08 पूर्ण,
	अणु 14, 0xcf पूर्ण,
	अणु 15, 0xcf पूर्ण,
	अणु 16, 0x7b पूर्ण,
	अणु 17, 0x00 पूर्ण,
	अणु 18, 0x32 पूर्ण,
	अणु 19, 0x00 पूर्ण,
	अणु 20, 0xa6 पूर्ण,
	अणु 21, 0x01 पूर्ण,
	अणु 22, 0x01 पूर्ण,
पूर्ण;

अटल bool wm8776_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8776_RESET:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक wm8776_reset(काष्ठा snd_soc_component *component)
अणु
	वापस snd_soc_component_ग_लिखो(component, WM8776_RESET, 0);
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(hp_tlv, -12100, 100, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(dac_tlv, -12750, 50, 1);
अटल स्थिर DECLARE_TLV_DB_SCALE(adc_tlv, -10350, 50, 1);

अटल स्थिर काष्ठा snd_kcontrol_new wm8776_snd_controls[] = अणु
SOC_DOUBLE_R_TLV("Headphone Playback Volume", WM8776_HPLVOL, WM8776_HPRVOL,
		 0, 127, 0, hp_tlv),
SOC_DOUBLE_R_TLV("Digital Playback Volume", WM8776_DACLVOL, WM8776_DACRVOL,
		 0, 255, 0, dac_tlv),
SOC_SINGLE("Digital Playback ZC Switch", WM8776_DACCTRL1, 0, 1, 0),

SOC_SINGLE("Deemphasis Switch", WM8776_DACCTRL2, 0, 1, 0),

SOC_DOUBLE_R_TLV("Capture Volume", WM8776_ADCLVOL, WM8776_ADCRVOL,
		 0, 255, 0, adc_tlv),
SOC_DOUBLE("Capture Switch", WM8776_ADCMUX, 7, 6, 1, 1),
SOC_DOUBLE_R("Capture ZC Switch", WM8776_ADCLVOL, WM8776_ADCRVOL, 8, 1, 0),
SOC_SINGLE("Capture HPF Switch", WM8776_ADCIFCTRL, 8, 1, 1),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new inmix_controls[] = अणु
SOC_DAPM_SINGLE("AIN1 Switch", WM8776_ADCMUX, 0, 1, 0),
SOC_DAPM_SINGLE("AIN2 Switch", WM8776_ADCMUX, 1, 1, 0),
SOC_DAPM_SINGLE("AIN3 Switch", WM8776_ADCMUX, 2, 1, 0),
SOC_DAPM_SINGLE("AIN4 Switch", WM8776_ADCMUX, 3, 1, 0),
SOC_DAPM_SINGLE("AIN5 Switch", WM8776_ADCMUX, 4, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new ouपंचांगix_controls[] = अणु
SOC_DAPM_SINGLE("DAC Switch", WM8776_OUTMUX, 0, 1, 0),
SOC_DAPM_SINGLE("AUX Switch", WM8776_OUTMUX, 1, 1, 0),
SOC_DAPM_SINGLE("Bypass Switch", WM8776_OUTMUX, 2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8776_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("AUX"),

SND_SOC_DAPM_INPUT("AIN1"),
SND_SOC_DAPM_INPUT("AIN2"),
SND_SOC_DAPM_INPUT("AIN3"),
SND_SOC_DAPM_INPUT("AIN4"),
SND_SOC_DAPM_INPUT("AIN5"),

SND_SOC_DAPM_MIXER("Input Mixer", WM8776_PWRDOWN, 6, 1,
		   inmix_controls, ARRAY_SIZE(inmix_controls)),

SND_SOC_DAPM_ADC("ADC", "Capture", WM8776_PWRDOWN, 1, 1),
SND_SOC_DAPM_DAC("DAC", "Playback", WM8776_PWRDOWN, 2, 1),

SND_SOC_DAPM_MIXER("Output Mixer", SND_SOC_NOPM, 0, 0,
		   ouपंचांगix_controls, ARRAY_SIZE(ouपंचांगix_controls)),

SND_SOC_DAPM_PGA("Headphone PGA", WM8776_PWRDOWN, 3, 1, शून्य, 0),

SND_SOC_DAPM_OUTPUT("VOUT"),

SND_SOC_DAPM_OUTPUT("HPOUTL"),
SND_SOC_DAPM_OUTPUT("HPOUTR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route routes[] = अणु
	अणु "Input Mixer", "AIN1 Switch", "AIN1" पूर्ण,
	अणु "Input Mixer", "AIN2 Switch", "AIN2" पूर्ण,
	अणु "Input Mixer", "AIN3 Switch", "AIN3" पूर्ण,
	अणु "Input Mixer", "AIN4 Switch", "AIN4" पूर्ण,
	अणु "Input Mixer", "AIN5 Switch", "AIN5" पूर्ण,

	अणु "ADC", शून्य, "Input Mixer" पूर्ण,

	अणु "Output Mixer", "DAC Switch", "DAC" पूर्ण,
	अणु "Output Mixer", "AUX Switch", "AUX" पूर्ण,
	अणु "Output Mixer", "Bypass Switch", "Input Mixer" पूर्ण,

	अणु "VOUT", शून्य, "Output Mixer" पूर्ण,

	अणु "Headphone PGA", शून्य, "Output Mixer" पूर्ण,

	अणु "HPOUTL", शून्य, "Headphone PGA" पूर्ण,
	अणु "HPOUTR", शून्य, "Headphone PGA" पूर्ण,
पूर्ण;

अटल पूर्णांक wm8776_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक reg, अगरace, master;

	चयन (dai->driver->id) अणु
	हाल WM8776_DAI_DAC:
		reg = WM8776_DACIFCTRL;
		master = 0x80;
		अवरोध;
	हाल WM8776_DAI_ADC:
		reg = WM8776_ADCIFCTRL;
		master = 0x100;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगरace = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		master = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरace |= 0x0002;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरace |= 0x0001;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		अगरace |= 0x00c;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		अगरace |= 0x008;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		अगरace |= 0x004;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Finally, ग_लिखो out the values */
	snd_soc_component_update_bits(component, reg, 0xf, अगरace);
	snd_soc_component_update_bits(component, WM8776_MSTRCTRL, 0x180, master);

	वापस 0;
पूर्ण

अटल पूर्णांक mclk_ratios[] = अणु
	128,
	192,
	256,
	384,
	512,
	768,
पूर्ण;

अटल पूर्णांक wm8776_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8776_priv *wm8776 = snd_soc_component_get_drvdata(component);
	पूर्णांक अगरace_reg, अगरace;
	पूर्णांक ratio_shअगरt, master;
	पूर्णांक i;

	चयन (dai->driver->id) अणु
	हाल WM8776_DAI_DAC:
		अगरace_reg = WM8776_DACIFCTRL;
		master = 0x80;
		ratio_shअगरt = 4;
		अवरोध;
	हाल WM8776_DAI_ADC:
		अगरace_reg = WM8776_ADCIFCTRL;
		master = 0x100;
		ratio_shअगरt = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Set word length */
	चयन (params_width(params)) अणु
	हाल 16:
		अगरace = 0;
		अवरोध;
	हाल 20:
		अगरace = 0x10;
		अवरोध;
	हाल 24:
		अगरace = 0x20;
		अवरोध;
	हाल 32:
		अगरace = 0x30;
		अवरोध;
	शेष:
		dev_err(component->dev, "Unsupported sample size: %i\n",
			params_width(params));
		वापस -EINVAL;
	पूर्ण

	/* Only need to set MCLK/LRCLK ratio अगर we're master */
	अगर (snd_soc_component_पढ़ो(component, WM8776_MSTRCTRL) & master) अणु
		क्रम (i = 0; i < ARRAY_SIZE(mclk_ratios); i++) अणु
			अगर (wm8776->sysclk[dai->driver->id] / params_rate(params)
			    == mclk_ratios[i])
				अवरोध;
		पूर्ण

		अगर (i == ARRAY_SIZE(mclk_ratios)) अणु
			dev_err(component->dev,
				"Unable to configure MCLK ratio %d/%d\n",
				wm8776->sysclk[dai->driver->id], params_rate(params));
			वापस -EINVAL;
		पूर्ण

		dev_dbg(component->dev, "MCLK is %dfs\n", mclk_ratios[i]);

		snd_soc_component_update_bits(component, WM8776_MSTRCTRL,
				    0x7 << ratio_shअगरt, i << ratio_shअगरt);
	पूर्ण अन्यथा अणु
		dev_dbg(component->dev, "DAI in slave mode\n");
	पूर्ण

	snd_soc_component_update_bits(component, अगरace_reg, 0x30, अगरace);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8776_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	वापस snd_soc_component_ग_लिखो(component, WM8776_DACMUTE, !!mute);
पूर्ण

अटल पूर्णांक wm8776_set_sysclk(काष्ठा snd_soc_dai *dai,
			     पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8776_priv *wm8776 = snd_soc_component_get_drvdata(component);

	अगर (WARN_ON(dai->driver->id >= ARRAY_SIZE(wm8776->sysclk)))
		वापस -EINVAL;

	wm8776->sysclk[dai->driver->id] = freq;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8776_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8776_priv *wm8776 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			regcache_sync(wm8776->regmap);

			/* Disable the global घातerकरोwn; DAPM करोes the rest */
			snd_soc_component_update_bits(component, WM8776_PWRDOWN, 1, 0);
		पूर्ण

		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		snd_soc_component_update_bits(component, WM8776_PWRDOWN, 1, 1);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा WM8776_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8776_dac_ops = अणु
	.mute_stream	= wm8776_mute,
	.hw_params      = wm8776_hw_params,
	.set_fmt        = wm8776_set_fmt,
	.set_sysclk     = wm8776_set_sysclk,
	.no_capture_mute = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops wm8776_adc_ops = अणु
	.hw_params      = wm8776_hw_params,
	.set_fmt        = wm8776_set_fmt,
	.set_sysclk     = wm8776_set_sysclk,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8776_dai[] = अणु
	अणु
		.name = "wm8776-hifi-playback",
		.id	= WM8776_DAI_DAC,
		.playback = अणु
			.stream_name = "Playback",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_CONTINUOUS,
			.rate_min = 32000,
			.rate_max = 192000,
			.क्रमmats = WM8776_FORMATS,
		पूर्ण,
		.ops = &wm8776_dac_ops,
	पूर्ण,
	अणु
		.name = "wm8776-hifi-capture",
		.id	= WM8776_DAI_ADC,
		.capture = अणु
			.stream_name = "Capture",
			.channels_min = 2,
			.channels_max = 2,
			.rates = SNDRV_PCM_RATE_CONTINUOUS,
			.rate_min = 32000,
			.rate_max = 96000,
			.क्रमmats = WM8776_FORMATS,
		पूर्ण,
		.ops = &wm8776_adc_ops,
	पूर्ण,
पूर्ण;

अटल पूर्णांक wm8776_probe(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret = 0;

	ret = wm8776_reset(component);
	अगर (ret < 0) अणु
		dev_err(component->dev, "Failed to issue reset: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Latch the update bits; right channel only since we always
	 * update both. */
	snd_soc_component_update_bits(component, WM8776_HPRVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8776_DACRVOL, 0x100, 0x100);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8776 = अणु
	.probe			= wm8776_probe,
	.set_bias_level		= wm8776_set_bias_level,
	.controls		= wm8776_snd_controls,
	.num_controls		= ARRAY_SIZE(wm8776_snd_controls),
	.dapm_widमाला_लो		= wm8776_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8776_dapm_widमाला_लो),
	.dapm_routes		= routes,
	.num_dapm_routes	= ARRAY_SIZE(routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id wm8776_of_match[] = अणु
	अणु .compatible = "wlf,wm8776", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wm8776_of_match);

अटल स्थिर काष्ठा regmap_config wm8776_regmap = अणु
	.reg_bits = 7,
	.val_bits = 9,
	.max_रेजिस्टर = WM8776_RESET,

	.reg_शेषs = wm8776_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8776_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,

	.अस्थिर_reg = wm8776_अस्थिर,
पूर्ण;

#अगर defined(CONFIG_SPI_MASTER)
अटल पूर्णांक wm8776_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा wm8776_priv *wm8776;
	पूर्णांक ret;

	wm8776 = devm_kzalloc(&spi->dev, माप(काष्ठा wm8776_priv),
			      GFP_KERNEL);
	अगर (wm8776 == शून्य)
		वापस -ENOMEM;

	wm8776->regmap = devm_regmap_init_spi(spi, &wm8776_regmap);
	अगर (IS_ERR(wm8776->regmap))
		वापस PTR_ERR(wm8776->regmap);

	spi_set_drvdata(spi, wm8776);

	ret = devm_snd_soc_रेजिस्टर_component(&spi->dev,
			&soc_component_dev_wm8776, wm8776_dai, ARRAY_SIZE(wm8776_dai));

	वापस ret;
पूर्ण

अटल काष्ठा spi_driver wm8776_spi_driver = अणु
	.driver = अणु
		.name	= "wm8776",
		.of_match_table = wm8776_of_match,
	पूर्ण,
	.probe		= wm8776_spi_probe,
पूर्ण;
#पूर्ण_अगर /* CONFIG_SPI_MASTER */

#अगर IS_ENABLED(CONFIG_I2C)
अटल पूर्णांक wm8776_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8776_priv *wm8776;
	पूर्णांक ret;

	wm8776 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8776_priv),
			      GFP_KERNEL);
	अगर (wm8776 == शून्य)
		वापस -ENOMEM;

	wm8776->regmap = devm_regmap_init_i2c(i2c, &wm8776_regmap);
	अगर (IS_ERR(wm8776->regmap))
		वापस PTR_ERR(wm8776->regmap);

	i2c_set_clientdata(i2c, wm8776);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_wm8776, wm8776_dai, ARRAY_SIZE(wm8776_dai));

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8776_i2c_id[] = अणु
	अणु "wm8775", WM8775 पूर्ण,
	अणु "wm8776", WM8776 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8776_i2c_id);

अटल काष्ठा i2c_driver wm8776_i2c_driver = अणु
	.driver = अणु
		.name = "wm8776",
		.of_match_table = wm8776_of_match,
	पूर्ण,
	.probe =    wm8776_i2c_probe,
	.id_table = wm8776_i2c_id,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init wm8776_modinit(व्योम)
अणु
	पूर्णांक ret = 0;
#अगर IS_ENABLED(CONFIG_I2C)
	ret = i2c_add_driver(&wm8776_i2c_driver);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register wm8776 I2C driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	ret = spi_रेजिस्टर_driver(&wm8776_spi_driver);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to register wm8776 SPI driver: %d\n",
		       ret);
	पूर्ण
#पूर्ण_अगर
	वापस ret;
पूर्ण
module_init(wm8776_modinit);

अटल व्योम __निकास wm8776_निकास(व्योम)
अणु
#अगर IS_ENABLED(CONFIG_I2C)
	i2c_del_driver(&wm8776_i2c_driver);
#पूर्ण_अगर
#अगर defined(CONFIG_SPI_MASTER)
	spi_unरेजिस्टर_driver(&wm8776_spi_driver);
#पूर्ण_अगर
पूर्ण
module_निकास(wm8776_निकास);

MODULE_DESCRIPTION("ASoC WM8776 driver");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
