<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8523.c  --  WM8523 ALSA SoC Audio driver
 *
 * Copyright 2009 Wolfson Microelectronics plc
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/pm.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/of_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/tlv.h>

#समावेश "wm8523.h"

#घोषणा WM8523_NUM_SUPPLIES 2
अटल स्थिर अक्षर *wm8523_supply_names[WM8523_NUM_SUPPLIES] = अणु
	"AVDD",
	"LINEVDD",
पूर्ण;

#घोषणा WM8523_NUM_RATES 7

/* codec निजी data */
काष्ठा wm8523_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data supplies[WM8523_NUM_SUPPLIES];
	अचिन्हित पूर्णांक sysclk;
	अचिन्हित पूर्णांक rate_स्थिरraपूर्णांक_list[WM8523_NUM_RATES];
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list rate_स्थिरraपूर्णांक;
पूर्ण;

अटल स्थिर काष्ठा reg_शेष wm8523_reg_शेषs[] = अणु
	अणु 2, 0x0000 पूर्ण,     /* R2 - PSCTRL1 */
	अणु 3, 0x1812 पूर्ण,     /* R3 - AIF_CTRL1 */
	अणु 4, 0x0000 पूर्ण,     /* R4 - AIF_CTRL2 */
	अणु 5, 0x0001 पूर्ण,     /* R5 - DAC_CTRL3 */
	अणु 6, 0x0190 पूर्ण,     /* R6 - DAC_GAINL */
	अणु 7, 0x0190 पूर्ण,     /* R7 - DAC_GAINR */
	अणु 8, 0x0000 पूर्ण,     /* R8 - ZERO_DETECT */
पूर्ण;

अटल bool wm8523_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल WM8523_DEVICE_ID:
	हाल WM8523_REVISION:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(dac_tlv, -10000, 25, 0);

अटल स्थिर अक्षर *wm8523_zd_count_text[] = अणु
	"1024",
	"2048",
पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(wm8523_zc_count, WM8523_ZERO_DETECT, 0,
			    wm8523_zd_count_text);

अटल स्थिर काष्ठा snd_kcontrol_new wm8523_controls[] = अणु
SOC_DOUBLE_R_TLV("Playback Volume", WM8523_DAC_GAINL, WM8523_DAC_GAINR,
		 0, 448, 0, dac_tlv),
SOC_SINGLE("ZC Switch", WM8523_DAC_CTRL3, 4, 1, 0),
SOC_SINGLE("Playback Deemphasis Switch", WM8523_AIF_CTRL1, 8, 1, 0),
SOC_DOUBLE("Playback Switch", WM8523_DAC_CTRL3, 2, 3, 1, 1),
SOC_SINGLE("Volume Ramp Up Switch", WM8523_DAC_CTRL3, 1, 1, 0),
SOC_SINGLE("Volume Ramp Down Switch", WM8523_DAC_CTRL3, 0, 1, 0),
SOC_ENUM("Zero Detect Count", wm8523_zc_count),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8523_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_DAC("DAC", "Playback", SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_OUTPUT("LINEVOUTL"),
SND_SOC_DAPM_OUTPUT("LINEVOUTR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8523_dapm_routes[] = अणु
	अणु "LINEVOUTL", शून्य, "DAC" पूर्ण,
	अणु "LINEVOUTR", शून्य, "DAC" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक value;
	पूर्णांक ratio;
पूर्ण lrclk_ratios[WM8523_NUM_RATES] = अणु
	अणु 1, 128 पूर्ण,
	अणु 2, 192 पूर्ण,
	अणु 3, 256 पूर्ण,
	अणु 4, 384 पूर्ण,
	अणु 5, 512 पूर्ण,
	अणु 6, 768 पूर्ण,
	अणु 7, 1152 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक value;
	पूर्णांक ratio;
पूर्ण bclk_ratios[] = अणु
	अणु 2, 32 पूर्ण,
	अणु 3, 64 पूर्ण,
	अणु 4, 128 पूर्ण,
पूर्ण;

अटल पूर्णांक wm8523_startup(काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8523_priv *wm8523 = snd_soc_component_get_drvdata(component);

	/* The set of sample rates that can be supported depends on the
	 * MCLK supplied to the CODEC - enक्रमce this.
	 */
	अगर (!wm8523->sysclk) अणु
		dev_err(component->dev,
			"No MCLK configured, call set_sysclk() on init\n");
		वापस -EINVAL;
	पूर्ण

	snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
				   SNDRV_PCM_HW_PARAM_RATE,
				   &wm8523->rate_स्थिरraपूर्णांक);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8523_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8523_priv *wm8523 = snd_soc_component_get_drvdata(component);
	पूर्णांक i;
	u16 aअगरctrl1 = snd_soc_component_पढ़ो(component, WM8523_AIF_CTRL1);
	u16 aअगरctrl2 = snd_soc_component_पढ़ो(component, WM8523_AIF_CTRL2);

	/* Find a supported LRCLK ratio */
	क्रम (i = 0; i < ARRAY_SIZE(lrclk_ratios); i++) अणु
		अगर (wm8523->sysclk / params_rate(params) ==
		    lrclk_ratios[i].ratio)
			अवरोध;
	पूर्ण

	/* Should never happen, should be handled by स्थिरraपूर्णांकs */
	अगर (i == ARRAY_SIZE(lrclk_ratios)) अणु
		dev_err(component->dev, "MCLK/fs ratio %d unsupported\n",
			wm8523->sysclk / params_rate(params));
		वापस -EINVAL;
	पूर्ण

	aअगरctrl2 &= ~WM8523_SR_MASK;
	aअगरctrl2 |= lrclk_ratios[i].value;

	अगर (aअगरctrl1 & WM8523_AIF_MSTR) अणु
		/* Find a fs->bclk ratio */
		क्रम (i = 0; i < ARRAY_SIZE(bclk_ratios); i++)
			अगर (params_width(params) * 2 <= bclk_ratios[i].ratio)
				अवरोध;

		अगर (i == ARRAY_SIZE(bclk_ratios)) अणु
			dev_err(component->dev,
				"No matching BCLK/fs ratio for word length %d\n",
				params_width(params));
			वापस -EINVAL;
		पूर्ण

		aअगरctrl2 &= ~WM8523_BCLKDIV_MASK;
		aअगरctrl2 |= bclk_ratios[i].value << WM8523_BCLKDIV_SHIFT;
	पूर्ण

	aअगरctrl1 &= ~WM8523_WL_MASK;
	चयन (params_width(params)) अणु
	हाल 16:
		अवरोध;
	हाल 20:
		aअगरctrl1 |= 0x8;
		अवरोध;
	हाल 24:
		aअगरctrl1 |= 0x10;
		अवरोध;
	हाल 32:
		aअगरctrl1 |= 0x18;
		अवरोध;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8523_AIF_CTRL1, aअगरctrl1);
	snd_soc_component_ग_लिखो(component, WM8523_AIF_CTRL2, aअगरctrl2);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8523_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8523_priv *wm8523 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	wm8523->sysclk = freq;

	wm8523->rate_स्थिरraपूर्णांक.count = 0;
	क्रम (i = 0; i < ARRAY_SIZE(lrclk_ratios); i++) अणु
		val = freq / lrclk_ratios[i].ratio;
		/* Check that it's a standard rate since core can't
		 * cope with others and having the odd rates confuses
		 * स्थिरraपूर्णांक matching.
		 */
		चयन (val) अणु
		हाल 8000:
		हाल 11025:
		हाल 16000:
		हाल 22050:
		हाल 32000:
		हाल 44100:
		हाल 48000:
		हाल 64000:
		हाल 88200:
		हाल 96000:
		हाल 176400:
		हाल 192000:
			dev_dbg(component->dev, "Supported sample rate: %dHz\n",
				val);
			wm8523->rate_स्थिरraपूर्णांक_list[i] = val;
			wm8523->rate_स्थिरraपूर्णांक.count++;
			अवरोध;
		शेष:
			dev_dbg(component->dev, "Skipping sample rate: %dHz\n",
				val);
		पूर्ण
	पूर्ण

	/* Need at least one supported rate... */
	अगर (wm8523->rate_स्थिरraपूर्णांक.count == 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण


अटल पूर्णांक wm8523_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u16 aअगरctrl1 = snd_soc_component_पढ़ो(component, WM8523_AIF_CTRL1);

	aअगरctrl1 &= ~(WM8523_BCLK_INV_MASK | WM8523_LRCLK_INV_MASK |
		      WM8523_FMT_MASK | WM8523_AIF_MSTR_MASK);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		aअगरctrl1 |= WM8523_AIF_MSTR;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		aअगरctrl1 |= 0x0002;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		aअगरctrl1 |= 0x0001;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_A:
		aअगरctrl1 |= 0x0003;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		aअगरctrl1 |= 0x0023;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		aअगरctrl1 |= WM8523_BCLK_INV | WM8523_LRCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		aअगरctrl1 |= WM8523_BCLK_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		aअगरctrl1 |= WM8523_LRCLK_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_ग_लिखो(component, WM8523_AIF_CTRL1, aअगरctrl1);

	वापस 0;
पूर्ण

अटल पूर्णांक wm8523_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm8523_priv *wm8523 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;

	हाल SND_SOC_BIAS_PREPARE:
		/* Full घातer on */
		snd_soc_component_update_bits(component, WM8523_PSCTRL1,
				    WM8523_SYS_ENA_MASK, 3);
		अवरोध;

	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			ret = regulator_bulk_enable(ARRAY_SIZE(wm8523->supplies),
						    wm8523->supplies);
			अगर (ret != 0) अणु
				dev_err(component->dev,
					"Failed to enable supplies: %d\n",
					ret);
				वापस ret;
			पूर्ण

			/* Sync back शेष/cached values */
			regcache_sync(wm8523->regmap);

			/* Initial घातer up */
			snd_soc_component_update_bits(component, WM8523_PSCTRL1,
					    WM8523_SYS_ENA_MASK, 1);

			msleep(100);
		पूर्ण

		/* Power up to mute */
		snd_soc_component_update_bits(component, WM8523_PSCTRL1,
				    WM8523_SYS_ENA_MASK, 2);

		अवरोध;

	हाल SND_SOC_BIAS_OFF:
		/* The chip runs through the घातer करोwn sequence क्रम us. */
		snd_soc_component_update_bits(component, WM8523_PSCTRL1,
				    WM8523_SYS_ENA_MASK, 0);
		msleep(100);

		regulator_bulk_disable(ARRAY_SIZE(wm8523->supplies),
				       wm8523->supplies);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा WM8523_RATES SNDRV_PCM_RATE_8000_192000

#घोषणा WM8523_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
			SNDRV_PCM_FMTBIT_S24_LE | SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8523_dai_ops = अणु
	.startup	= wm8523_startup,
	.hw_params	= wm8523_hw_params,
	.set_sysclk	= wm8523_set_dai_sysclk,
	.set_fmt	= wm8523_set_dai_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8523_dai = अणु
	.name = "wm8523-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,  /* Mono modes not yet supported */
		.channels_max = 2,
		.rates = WM8523_RATES,
		.क्रमmats = WM8523_FORMATS,
	पूर्ण,
	.ops = &wm8523_dai_ops,
पूर्ण;

अटल पूर्णांक wm8523_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8523_priv *wm8523 = snd_soc_component_get_drvdata(component);

	wm8523->rate_स्थिरraपूर्णांक.list = &wm8523->rate_स्थिरraपूर्णांक_list[0];
	wm8523->rate_स्थिरraपूर्णांक.count =
		ARRAY_SIZE(wm8523->rate_स्थिरraपूर्णांक_list);

	/* Change some शेष settings - latch VU and enable ZC */
	snd_soc_component_update_bits(component, WM8523_DAC_GAINR,
			    WM8523_DACR_VU, WM8523_DACR_VU);
	snd_soc_component_update_bits(component, WM8523_DAC_CTRL3, WM8523_ZC, WM8523_ZC);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8523 = अणु
	.probe			= wm8523_probe,
	.set_bias_level		= wm8523_set_bias_level,
	.controls		= wm8523_controls,
	.num_controls		= ARRAY_SIZE(wm8523_controls),
	.dapm_widमाला_लो		= wm8523_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8523_dapm_widमाला_लो),
	.dapm_routes		= wm8523_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm8523_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id wm8523_of_match[] = अणु
	अणु .compatible = "wlf,wm8523" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, wm8523_of_match);

अटल स्थिर काष्ठा regmap_config wm8523_regmap = अणु
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = WM8523_ZERO_DETECT,

	.reg_शेषs = wm8523_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(wm8523_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,

	.अस्थिर_reg = wm8523_अस्थिर_रेजिस्टर,
पूर्ण;

अटल पूर्णांक wm8523_i2c_probe(काष्ठा i2c_client *i2c,
			    स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा wm8523_priv *wm8523;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret, i;

	wm8523 = devm_kzalloc(&i2c->dev, माप(काष्ठा wm8523_priv),
			      GFP_KERNEL);
	अगर (wm8523 == शून्य)
		वापस -ENOMEM;

	wm8523->regmap = devm_regmap_init_i2c(i2c, &wm8523_regmap);
	अगर (IS_ERR(wm8523->regmap)) अणु
		ret = PTR_ERR(wm8523->regmap);
		dev_err(&i2c->dev, "Failed to create regmap: %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(wm8523->supplies); i++)
		wm8523->supplies[i].supply = wm8523_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c->dev, ARRAY_SIZE(wm8523->supplies),
				      wm8523->supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regulator_bulk_enable(ARRAY_SIZE(wm8523->supplies),
				    wm8523->supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = regmap_पढ़ो(wm8523->regmap, WM8523_DEVICE_ID, &val);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to read ID register\n");
		जाओ err_enable;
	पूर्ण
	अगर (val != 0x8523) अणु
		dev_err(&i2c->dev, "Device is not a WM8523, ID is %x\n", ret);
		ret = -EINVAL;
		जाओ err_enable;
	पूर्ण

	ret = regmap_पढ़ो(wm8523->regmap, WM8523_REVISION, &val);
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "Failed to read revision register\n");
		जाओ err_enable;
	पूर्ण
	dev_info(&i2c->dev, "revision %c\n",
		 (val & WM8523_CHIP_REV_MASK) + 'A');

	ret = regmap_ग_लिखो(wm8523->regmap, WM8523_DEVICE_ID, 0x8523);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to reset device: %d\n", ret);
		जाओ err_enable;
	पूर्ण

	regulator_bulk_disable(ARRAY_SIZE(wm8523->supplies), wm8523->supplies);

	i2c_set_clientdata(i2c, wm8523);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_wm8523, &wm8523_dai, 1);

	वापस ret;

err_enable:
	regulator_bulk_disable(ARRAY_SIZE(wm8523->supplies), wm8523->supplies);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id wm8523_i2c_id[] = अणु
	अणु "wm8523", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, wm8523_i2c_id);

अटल काष्ठा i2c_driver wm8523_i2c_driver = अणु
	.driver = अणु
		.name = "wm8523",
		.of_match_table = wm8523_of_match,
	पूर्ण,
	.probe =    wm8523_i2c_probe,
	.id_table = wm8523_i2c_id,
पूर्ण;

module_i2c_driver(wm8523_i2c_driver);

MODULE_DESCRIPTION("ASoC WM8523 driver");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
