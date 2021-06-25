<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cs4349.c  --  CS4349 ALSA Soc Audio driver
 *
 * Copyright 2015 Cirrus Logic, Inc.
 *
 * Authors: Tim Howe <Tim.Howe@cirrus.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/of_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>
#समावेश "cs4349.h"


अटल स्थिर काष्ठा reg_शेष cs4349_reg_शेषs[] = अणु
	अणु 2, 0x00 पूर्ण,	/* r02	- Mode Control */
	अणु 3, 0x09 पूर्ण,	/* r03	- Volume, Mixing and Inversion Control */
	अणु 4, 0x81 पूर्ण,	/* r04	- Mute Control */
	अणु 5, 0x00 पूर्ण,	/* r05	- Channel A Volume Control */
	अणु 6, 0x00 पूर्ण,	/* r06	- Channel B Volume Control */
	अणु 7, 0xB1 पूर्ण,	/* r07	- Ramp and Filter Control */
	अणु 8, 0x1C पूर्ण,	/* r08	- Misc. Control */
पूर्ण;

/* Private data क्रम the CS4349 */
काष्ठा  cs4349_निजी अणु
	काष्ठा regmap			*regmap;
	काष्ठा gpio_desc		*reset_gpio;
	अचिन्हित पूर्णांक			mode;
	पूर्णांक				rate;
पूर्ण;

अटल bool cs4349_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS4349_CHIPID ... CS4349_MISC:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool cs4349_ग_लिखोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल CS4349_MODE ...  CS4349_MISC:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक cs4349_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
			      अचिन्हित पूर्णांक क्रमmat)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा cs4349_निजी *cs4349 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक fmt;

	fmt = क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK;

	चयन (fmt) अणु
	हाल SND_SOC_DAIFMT_I2S:
	हाल SND_SOC_DAIFMT_LEFT_J:
	हाल SND_SOC_DAIFMT_RIGHT_J:
		cs4349->mode = क्रमmat & SND_SOC_DAIFMT_FORMAT_MASK;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cs4349_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा cs4349_निजी *cs4349 = snd_soc_component_get_drvdata(component);
	पूर्णांक fmt, ret;

	cs4349->rate = params_rate(params);

	चयन (cs4349->mode) अणु
	हाल SND_SOC_DAIFMT_I2S:
		fmt = DIF_I2S;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		fmt = DIF_LEFT_JST;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		चयन (params_width(params)) अणु
		हाल 16:
			fmt = DIF_RGHT_JST16;
			अवरोध;
		हाल 24:
			fmt = DIF_RGHT_JST24;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_component_update_bits(component, CS4349_MODE, DIF_MASK,
				  MODE_FORMAT(fmt));
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक cs4349_mute(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक direction)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक reg;

	reg = 0;
	अगर (mute)
		reg = MUTE_AB_MASK;

	वापस snd_soc_component_update_bits(component, CS4349_MUTE, MUTE_AB_MASK, reg);
पूर्ण

अटल DECLARE_TLV_DB_SCALE(dig_tlv, -12750, 50, 0);

अटल स्थिर अक्षर * स्थिर chan_mix_texts[] = अणु
	"Mute", "MuteA", "MuteA SwapB", "MuteA MonoB", "SwapA MuteB",
	"BothR", "Swap", "SwapA MonoB", "MuteB", "Normal", "BothL",
	"MonoB", "MonoA MuteB", "MonoA", "MonoA SwapB", "Mono",
	/*Normal == Channel A = Left, Channel B = Right*/
पूर्ण;

अटल स्थिर अक्षर * स्थिर fm_texts[] = अणु
	"Auto", "Single", "Double", "Quad",
पूर्ण;

अटल स्थिर अक्षर * स्थिर deemph_texts[] = अणु
	"None", "44.1k", "48k", "32k",
पूर्ण;

अटल स्थिर अक्षर * स्थिर softr_zeroc_texts[] = अणु
	"Immediate", "Zero Cross", "Soft Ramp", "SR on ZC",
पूर्ण;

अटल पूर्णांक deemph_values[] = अणु
	0, 4, 8, 12,
पूर्ण;

अटल पूर्णांक softr_zeroc_values[] = अणु
	0, 64, 128, 192,
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत chan_mix_क्रमागत =
	SOC_ENUM_SINGLE(CS4349_VMI, 0,
			ARRAY_SIZE(chan_mix_texts),
			chan_mix_texts);

अटल स्थिर काष्ठा soc_क्रमागत fm_mode_क्रमागत =
	SOC_ENUM_SINGLE(CS4349_MODE, 0,
			ARRAY_SIZE(fm_texts),
			fm_texts);

अटल SOC_VALUE_ENUM_SINGLE_DECL(deemph_क्रमागत, CS4349_MODE, 0, DEM_MASK,
				deemph_texts, deemph_values);

अटल SOC_VALUE_ENUM_SINGLE_DECL(softr_zeroc_क्रमागत, CS4349_RMPFLT, 0,
				SR_ZC_MASK, softr_zeroc_texts,
				softr_zeroc_values);

अटल स्थिर काष्ठा snd_kcontrol_new cs4349_snd_controls[] = अणु
	SOC_DOUBLE_R_TLV("Master Playback Volume",
			 CS4349_VOLA, CS4349_VOLB, 0, 0xFF, 1, dig_tlv),
	SOC_ENUM("Functional Mode", fm_mode_क्रमागत),
	SOC_ENUM("De-Emphasis Control", deemph_क्रमागत),
	SOC_ENUM("Soft Ramp Zero Cross Control", softr_zeroc_क्रमागत),
	SOC_ENUM("Channel Mixer", chan_mix_क्रमागत),
	SOC_SINGLE("VolA = VolB Switch", CS4349_VMI, 7, 1, 0),
	SOC_SINGLE("InvertA Switch", CS4349_VMI, 6, 1, 0),
	SOC_SINGLE("InvertB Switch", CS4349_VMI, 5, 1, 0),
	SOC_SINGLE("Auto-Mute Switch", CS4349_MUTE, 7, 1, 0),
	SOC_SINGLE("MUTEC A = B Switch", CS4349_MUTE, 5, 1, 0),
	SOC_SINGLE("Soft Ramp Up Switch", CS4349_RMPFLT, 5, 1, 0),
	SOC_SINGLE("Soft Ramp Down Switch", CS4349_RMPFLT, 4, 1, 0),
	SOC_SINGLE("Slow Roll Off Filter Switch", CS4349_RMPFLT, 2, 1, 0),
	SOC_SINGLE("Freeze Switch", CS4349_MISC, 5, 1, 0),
	SOC_SINGLE("Popguard Switch", CS4349_MISC, 4, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget cs4349_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("HiFi DAC", शून्य, SND_SOC_NOPM, 0, 0),

	SND_SOC_DAPM_OUTPUT("OutputA"),
	SND_SOC_DAPM_OUTPUT("OutputB"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cs4349_routes[] = अणु
	अणु"DAC Playback", शून्य, "OutputA"पूर्ण,
	अणु"DAC Playback", शून्य, "OutputB"पूर्ण,

	अणु"OutputA", शून्य, "HiFi DAC"पूर्ण,
	अणु"OutputB", शून्य, "HiFi DAC"पूर्ण,
पूर्ण;

#घोषणा CS4349_PCM_FORMATS (SNDRV_PCM_FMTBIT_S8  | \
			SNDRV_PCM_FMTBIT_S16_LE  | SNDRV_PCM_FMTBIT_S16_BE  | \
			SNDRV_PCM_FMTBIT_S18_3LE | SNDRV_PCM_FMTBIT_S18_3BE | \
			SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S20_3BE | \
			SNDRV_PCM_FMTBIT_S24_3LE | SNDRV_PCM_FMTBIT_S24_3BE | \
			SNDRV_PCM_FMTBIT_S24_LE  | SNDRV_PCM_FMTBIT_S24_BE  | \
			SNDRV_PCM_FMTBIT_S32_LE)

#घोषणा CS4349_PCM_RATES SNDRV_PCM_RATE_8000_192000

अटल स्थिर काष्ठा snd_soc_dai_ops cs4349_dai_ops = अणु
	.hw_params	= cs4349_pcm_hw_params,
	.set_fmt	= cs4349_set_dai_fmt,
	.mute_stream	= cs4349_mute,
	.no_capture_mute = 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver cs4349_dai = अणु
	.name = "cs4349_hifi",
	.playback = अणु
		.stream_name	= "DAC Playback",
		.channels_min	= 1,
		.channels_max	= 2,
		.rates		= CS4349_PCM_RATES,
		.क्रमmats	= CS4349_PCM_FORMATS,
	पूर्ण,
	.ops = &cs4349_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_cs4349 = अणु
	.controls		= cs4349_snd_controls,
	.num_controls		= ARRAY_SIZE(cs4349_snd_controls),
	.dapm_widमाला_लो		= cs4349_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(cs4349_dapm_widमाला_लो),
	.dapm_routes		= cs4349_routes,
	.num_dapm_routes	= ARRAY_SIZE(cs4349_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config cs4349_regmap = अणु
	.reg_bits		= 8,
	.val_bits		= 8,

	.max_रेजिस्टर		= CS4349_MISC,
	.reg_शेषs		= cs4349_reg_शेषs,
	.num_reg_शेषs	= ARRAY_SIZE(cs4349_reg_शेषs),
	.पढ़ोable_reg		= cs4349_पढ़ोable_रेजिस्टर,
	.ग_लिखोable_reg		= cs4349_ग_लिखोable_रेजिस्टर,
	.cache_type		= REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक cs4349_i2c_probe(काष्ठा i2c_client *client,
				      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा cs4349_निजी *cs4349;
	पूर्णांक ret;

	cs4349 = devm_kzalloc(&client->dev, माप(*cs4349), GFP_KERNEL);
	अगर (!cs4349)
		वापस -ENOMEM;

	cs4349->regmap = devm_regmap_init_i2c(client, &cs4349_regmap);
	अगर (IS_ERR(cs4349->regmap)) अणु
		ret = PTR_ERR(cs4349->regmap);
		dev_err(&client->dev, "regmap_init() failed: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Reset the Device */
	cs4349->reset_gpio = devm_gpiod_get_optional(&client->dev,
		"reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(cs4349->reset_gpio))
		वापस PTR_ERR(cs4349->reset_gpio);

	gpiod_set_value_cansleep(cs4349->reset_gpio, 1);

	i2c_set_clientdata(client, cs4349);

	वापस devm_snd_soc_रेजिस्टर_component(&client->dev,
		&soc_component_dev_cs4349,
		&cs4349_dai, 1);
पूर्ण

अटल पूर्णांक cs4349_i2c_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा cs4349_निजी *cs4349 = i2c_get_clientdata(client);

	/* Hold करोwn reset */
	gpiod_set_value_cansleep(cs4349->reset_gpio, 0);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक cs4349_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा cs4349_निजी *cs4349 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regmap_update_bits(cs4349->regmap, CS4349_MISC, PWR_DWN, PWR_DWN);
	अगर (ret < 0)
		वापस ret;

	regcache_cache_only(cs4349->regmap, true);

	/* Hold करोwn reset */
	gpiod_set_value_cansleep(cs4349->reset_gpio, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक cs4349_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा cs4349_निजी *cs4349 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regmap_update_bits(cs4349->regmap, CS4349_MISC, PWR_DWN, 0);
	अगर (ret < 0)
		वापस ret;

	gpiod_set_value_cansleep(cs4349->reset_gpio, 1);

	regcache_cache_only(cs4349->regmap, false);
	regcache_sync(cs4349->regmap);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops cs4349_runसमय_pm = अणु
	SET_RUNTIME_PM_OPS(cs4349_runसमय_suspend, cs4349_runसमय_resume,
			   शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id cs4349_of_match[] = अणु
	अणु .compatible = "cirrus,cs4349", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, cs4349_of_match);

अटल स्थिर काष्ठा i2c_device_id cs4349_i2c_id[] = अणु
	अणु"cs4349", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, cs4349_i2c_id);

अटल काष्ठा i2c_driver cs4349_i2c_driver = अणु
	.driver = अणु
		.name		= "cs4349",
		.of_match_table	= cs4349_of_match,
		.pm = &cs4349_runसमय_pm,
	पूर्ण,
	.id_table	= cs4349_i2c_id,
	.probe		= cs4349_i2c_probe,
	.हटाओ		= cs4349_i2c_हटाओ,
पूर्ण;

module_i2c_driver(cs4349_i2c_driver);

MODULE_AUTHOR("Tim Howe <tim.howe@cirrus.com>");
MODULE_DESCRIPTION("Cirrus Logic CS4349 ALSA SoC Codec Driver");
MODULE_LICENSE("GPL");
