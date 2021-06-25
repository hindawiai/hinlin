<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * max9850.c  --  codec driver क्रम max9850
 *
 * Copyright (C) 2011 taskit GmbH
 *
 * Author: Christian Glindkamp <christian.glindkamp@taskit.de>
 *
 * Initial development of this code was funded by
 * MICRONIC Computer Systeme GmbH, https://www.mcsberlin.de/
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#समावेश "max9850.h"

काष्ठा max9850_priv अणु
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक sysclk;
पूर्ण;

/* these रेजिस्टरs are not used at the moment but provided क्रम the sake of
 * completeness */
अटल bool max9850_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX9850_STATUSA:
	हाल MAX9850_STATUSB:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config max9850_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = MAX9850_DIGITAL_AUDIO,
	.अस्थिर_reg = max9850_अस्थिर_रेजिस्टर,
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_RANGE(max9850_tlv,
	0x18, 0x1f, TLV_DB_SCALE_ITEM(-7450, 400, 0),
	0x20, 0x33, TLV_DB_SCALE_ITEM(-4150, 200, 0),
	0x34, 0x37, TLV_DB_SCALE_ITEM(-150, 100, 0),
	0x38, 0x3f, TLV_DB_SCALE_ITEM(250, 50, 0)
);

अटल स्थिर काष्ठा snd_kcontrol_new max9850_controls[] = अणु
SOC_SINGLE_TLV("Headphone Volume", MAX9850_VOLUME, 0, 0x3f, 1, max9850_tlv),
SOC_SINGLE("Headphone Switch", MAX9850_VOLUME, 7, 1, 1),
SOC_SINGLE("Mono Switch", MAX9850_GENERAL_PURPOSE, 2, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new max9850_mixer_controls[] = अणु
	SOC_DAPM_SINGLE("Line In Switch", MAX9850_ENABLE, 1, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget max9850_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_SUPPLY("Charge Pump 1", MAX9850_ENABLE, 4, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("Charge Pump 2", MAX9850_ENABLE, 5, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("MCLK", MAX9850_ENABLE, 6, 0, शून्य, 0),
SND_SOC_DAPM_SUPPLY("SHDN", MAX9850_ENABLE, 7, 0, शून्य, 0),
SND_SOC_DAPM_MIXER_NAMED_CTL("Output Mixer", MAX9850_ENABLE, 2, 0,
		&max9850_mixer_controls[0],
		ARRAY_SIZE(max9850_mixer_controls)),
SND_SOC_DAPM_PGA("Headphone Output", MAX9850_ENABLE, 3, 0, शून्य, 0),
SND_SOC_DAPM_DAC("DAC", "HiFi Playback", MAX9850_ENABLE, 0, 0),
SND_SOC_DAPM_OUTPUT("OUTL"),
SND_SOC_DAPM_OUTPUT("HPL"),
SND_SOC_DAPM_OUTPUT("OUTR"),
SND_SOC_DAPM_OUTPUT("HPR"),
SND_SOC_DAPM_MIXER("Line Input", SND_SOC_NOPM, 0, 0, शून्य, 0),
SND_SOC_DAPM_INPUT("INL"),
SND_SOC_DAPM_INPUT("INR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route max9850_dapm_routes[] = अणु
	/* output mixer */
	अणु"Output Mixer", शून्य, "DAC"पूर्ण,
	अणु"Output Mixer", "Line In Switch", "Line Input"पूर्ण,

	/* outमाला_दो */
	अणु"Headphone Output", शून्य, "Output Mixer"पूर्ण,
	अणु"HPL", शून्य, "Headphone Output"पूर्ण,
	अणु"HPR", शून्य, "Headphone Output"पूर्ण,
	अणु"OUTL", शून्य, "Output Mixer"पूर्ण,
	अणु"OUTR", शून्य, "Output Mixer"पूर्ण,

	/* inमाला_दो */
	अणु"Line Input", शून्य, "INL"पूर्ण,
	अणु"Line Input", शून्य, "INR"पूर्ण,

	/* supplies */
	अणु"Output Mixer", शून्य, "Charge Pump 1"पूर्ण,
	अणु"Output Mixer", शून्य, "Charge Pump 2"पूर्ण,
	अणु"Output Mixer", शून्य, "SHDN"पूर्ण,
	अणु"DAC", शून्य, "MCLK"पूर्ण,
पूर्ण;

अटल पूर्णांक max9850_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा max9850_priv *max9850 = snd_soc_component_get_drvdata(component);
	u64 lrclk_भाग;
	u8 sf, da;

	अगर (!max9850->sysclk)
		वापस -EINVAL;

	/* lrclk_भाग = 2^22 * rate / iclk with iclk = mclk / sf */
	sf = (snd_soc_component_पढ़ो(component, MAX9850_CLOCK) >> 2) + 1;
	lrclk_भाग = (1 << 22);
	lrclk_भाग *= params_rate(params);
	lrclk_भाग *= sf;
	करो_भाग(lrclk_भाग, max9850->sysclk);

	snd_soc_component_ग_लिखो(component, MAX9850_LRCLK_MSB, (lrclk_भाग >> 8) & 0x7f);
	snd_soc_component_ग_लिखो(component, MAX9850_LRCLK_LSB, lrclk_भाग & 0xff);

	चयन (params_width(params)) अणु
	हाल 16:
		da = 0;
		अवरोध;
	हाल 20:
		da = 0x2;
		अवरोध;
	हाल 24:
		da = 0x3;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	snd_soc_component_update_bits(component, MAX9850_DIGITAL_AUDIO, 0x3, da);

	वापस 0;
पूर्ण

अटल पूर्णांक max9850_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा max9850_priv *max9850 = snd_soc_component_get_drvdata(component);

	/* calculate mclk -> iclk भागider */
	अगर (freq <= 13000000)
		snd_soc_component_ग_लिखो(component, MAX9850_CLOCK, 0x0);
	अन्यथा अगर (freq <= 26000000)
		snd_soc_component_ग_लिखो(component, MAX9850_CLOCK, 0x4);
	अन्यथा अगर (freq <= 40000000)
		snd_soc_component_ग_लिखो(component, MAX9850_CLOCK, 0x8);
	अन्यथा
		वापस -EINVAL;

	max9850->sysclk = freq;
	वापस 0;
पूर्ण

अटल पूर्णांक max9850_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	u8 da = 0;

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		da |= MAX9850_MASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* पूर्णांकerface क्रमmat */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		da |= MAX9850_DLY;
		अवरोध;
	हाल SND_SOC_DAIFMT_RIGHT_J:
		da |= MAX9850_RTJ;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* घड़ी inversion */
	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_IF:
		da |= MAX9850_BCINV | MAX9850_INV;
		अवरोध;
	हाल SND_SOC_DAIFMT_IB_NF:
		da |= MAX9850_BCINV;
		अवरोध;
	हाल SND_SOC_DAIFMT_NB_IF:
		da |= MAX9850_INV;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* set da */
	snd_soc_component_ग_लिखो(component, MAX9850_DIGITAL_AUDIO, da);

	वापस 0;
पूर्ण

अटल पूर्णांक max9850_set_bias_level(काष्ठा snd_soc_component *component,
				  क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा max9850_priv *max9850 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) अणु
			ret = regcache_sync(max9850->regmap);
			अगर (ret) अणु
				dev_err(component->dev,
					"Failed to sync cache: %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

#घोषणा MAX9850_RATES SNDRV_PCM_RATE_8000_48000

#घोषणा MAX9850_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S20_3LE |\
	SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops max9850_dai_ops = अणु
	.hw_params	= max9850_hw_params,
	.set_sysclk	= max9850_set_dai_sysclk,
	.set_fmt	= max9850_set_dai_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver max9850_dai = अणु
	.name = "max9850-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = MAX9850_RATES,
		.क्रमmats = MAX9850_FORMATS
	पूर्ण,
	.ops = &max9850_dai_ops,
पूर्ण;

अटल पूर्णांक max9850_probe(काष्ठा snd_soc_component *component)
अणु
	/* enable zero-detect */
	snd_soc_component_update_bits(component, MAX9850_GENERAL_PURPOSE, 1, 1);
	/* enable slew-rate control */
	snd_soc_component_update_bits(component, MAX9850_VOLUME, 0x40, 0x40);
	/* set slew-rate 125ms */
	snd_soc_component_update_bits(component, MAX9850_CHARGE_PUMP, 0xff, 0xc0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_max9850 = अणु
	.probe			= max9850_probe,
	.set_bias_level		= max9850_set_bias_level,
	.controls		= max9850_controls,
	.num_controls		= ARRAY_SIZE(max9850_controls),
	.dapm_widमाला_लो		= max9850_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(max9850_dapm_widमाला_लो),
	.dapm_routes		= max9850_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(max9850_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक max9850_i2c_probe(काष्ठा i2c_client *i2c,
			     स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max9850_priv *max9850;
	पूर्णांक ret;

	max9850 = devm_kzalloc(&i2c->dev, माप(काष्ठा max9850_priv),
			       GFP_KERNEL);
	अगर (max9850 == शून्य)
		वापस -ENOMEM;

	max9850->regmap = devm_regmap_init_i2c(i2c, &max9850_regmap);
	अगर (IS_ERR(max9850->regmap))
		वापस PTR_ERR(max9850->regmap);

	i2c_set_clientdata(i2c, max9850);

	ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
			&soc_component_dev_max9850, &max9850_dai, 1);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max9850_i2c_id[] = अणु
	अणु "max9850", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max9850_i2c_id);

अटल काष्ठा i2c_driver max9850_i2c_driver = अणु
	.driver = अणु
		.name = "max9850",
	पूर्ण,
	.probe = max9850_i2c_probe,
	.id_table = max9850_i2c_id,
पूर्ण;

module_i2c_driver(max9850_i2c_driver);

MODULE_AUTHOR("Christian Glindkamp <christian.glindkamp@taskit.de>");
MODULE_DESCRIPTION("ASoC MAX9850 codec driver");
MODULE_LICENSE("GPL");
