<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Audio driver क्रम AK5558 ADC
//
// Copyright (C) 2015 Asahi Kasei Microdevices Corporation
// Copyright 2018 NXP

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>

#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/tlv.h>

#समावेश "ak5558.h"

क्रमागत ak555x_type अणु
	AK5558,
	AK5552,
पूर्ण;

#घोषणा AK5558_NUM_SUPPLIES 2
अटल स्थिर अक्षर *ak5558_supply_names[AK5558_NUM_SUPPLIES] = अणु
	"DVDD",
	"AVDD",
पूर्ण;

/* AK5558 Codec Private Data */
काष्ठा ak5558_priv अणु
	काष्ठा regulator_bulk_data supplies[AK5558_NUM_SUPPLIES];
	काष्ठा snd_soc_component component;
	काष्ठा regmap *regmap;
	काष्ठा i2c_client *i2c;
	काष्ठा gpio_desc *reset_gpiod; /* Reset & Power करोwn GPIO */
	पूर्णांक slots;
	पूर्णांक slot_width;
पूर्ण;

/* ak5558 रेजिस्टर cache & शेष रेजिस्टर settings */
अटल स्थिर काष्ठा reg_शेष ak5558_reg[] = अणु
	अणु 0x0, 0xFF पूर्ण,	/*	0x00	AK5558_00_POWER_MANAGEMENT1	*/
	अणु 0x1, 0x01 पूर्ण,	/*	0x01	AK5558_01_POWER_MANAGEMENT2	*/
	अणु 0x2, 0x01 पूर्ण,	/*	0x02	AK5558_02_CONTROL1		*/
	अणु 0x3, 0x00 पूर्ण,	/*	0x03	AK5558_03_CONTROL2		*/
	अणु 0x4, 0x00 पूर्ण,	/*	0x04	AK5558_04_CONTROL3		*/
	अणु 0x5, 0x00 पूर्ण	/*	0x05	AK5558_05_DSD			*/
पूर्ण;

अटल स्थिर अक्षर * स्थिर mono_texts[] = अणु
	"8 Slot", "2 Slot", "4 Slot", "1 Slot",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत ak5558_mono_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(AK5558_01_POWER_MANAGEMENT2, 1,
			ARRAY_SIZE(mono_texts), mono_texts),
पूर्ण;

अटल स्थिर अक्षर * स्थिर mono_5552_texts[] = अणु
	"2 Slot", "1 Slot (Fixed)", "2 Slot", "1 Slot (Optimal)",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत ak5552_mono_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(AK5558_01_POWER_MANAGEMENT2, 1,
			ARRAY_SIZE(mono_5552_texts), mono_5552_texts),
पूर्ण;

अटल स्थिर अक्षर * स्थिर digfil_texts[] = अणु
	"Sharp Roll-Off", "Slow Roll-Off",
	"Short Delay Sharp Roll-Off", "Short Delay Slow Roll-Off",
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत ak5558_adcset_क्रमागत[] = अणु
	SOC_ENUM_SINGLE(AK5558_04_CONTROL3, 0,
			ARRAY_SIZE(digfil_texts), digfil_texts),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new ak5558_snd_controls[] = अणु
	SOC_ENUM("Monaural Mode", ak5558_mono_क्रमागत[0]),
	SOC_ENUM("Digital Filter", ak5558_adcset_क्रमागत[0]),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new ak5552_snd_controls[] = अणु
	SOC_ENUM("Monaural Mode", ak5552_mono_क्रमागत[0]),
	SOC_ENUM("Digital Filter", ak5558_adcset_क्रमागत[0]),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget ak5558_dapm_widमाला_लो[] = अणु
	/* Analog Input */
	SND_SOC_DAPM_INPUT("AIN1"),
	SND_SOC_DAPM_INPUT("AIN2"),
	SND_SOC_DAPM_INPUT("AIN3"),
	SND_SOC_DAPM_INPUT("AIN4"),
	SND_SOC_DAPM_INPUT("AIN5"),
	SND_SOC_DAPM_INPUT("AIN6"),
	SND_SOC_DAPM_INPUT("AIN7"),
	SND_SOC_DAPM_INPUT("AIN8"),

	SND_SOC_DAPM_ADC("ADC Ch1", शून्य, AK5558_00_POWER_MANAGEMENT1, 0, 0),
	SND_SOC_DAPM_ADC("ADC Ch2", शून्य, AK5558_00_POWER_MANAGEMENT1, 1, 0),
	SND_SOC_DAPM_ADC("ADC Ch3", शून्य, AK5558_00_POWER_MANAGEMENT1, 2, 0),
	SND_SOC_DAPM_ADC("ADC Ch4", शून्य, AK5558_00_POWER_MANAGEMENT1, 3, 0),
	SND_SOC_DAPM_ADC("ADC Ch5", शून्य, AK5558_00_POWER_MANAGEMENT1, 4, 0),
	SND_SOC_DAPM_ADC("ADC Ch6", शून्य, AK5558_00_POWER_MANAGEMENT1, 5, 0),
	SND_SOC_DAPM_ADC("ADC Ch7", शून्य, AK5558_00_POWER_MANAGEMENT1, 6, 0),
	SND_SOC_DAPM_ADC("ADC Ch8", शून्य, AK5558_00_POWER_MANAGEMENT1, 7, 0),

	SND_SOC_DAPM_AIF_OUT("SDTO", "Capture", 0, SND_SOC_NOPM, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget ak5552_dapm_widमाला_लो[] = अणु
	/* Analog Input */
	SND_SOC_DAPM_INPUT("AIN1"),
	SND_SOC_DAPM_INPUT("AIN2"),

	SND_SOC_DAPM_ADC("ADC Ch1", शून्य, AK5558_00_POWER_MANAGEMENT1, 0, 0),
	SND_SOC_DAPM_ADC("ADC Ch2", शून्य, AK5558_00_POWER_MANAGEMENT1, 1, 0),

	SND_SOC_DAPM_AIF_OUT("SDTO", "Capture", 0, SND_SOC_NOPM, 0, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ak5558_पूर्णांकercon[] = अणु
	अणु"ADC Ch1", शून्य, "AIN1"पूर्ण,
	अणु"SDTO", शून्य, "ADC Ch1"पूर्ण,

	अणु"ADC Ch2", शून्य, "AIN2"पूर्ण,
	अणु"SDTO", शून्य, "ADC Ch2"पूर्ण,

	अणु"ADC Ch3", शून्य, "AIN3"पूर्ण,
	अणु"SDTO", शून्य, "ADC Ch3"पूर्ण,

	अणु"ADC Ch4", शून्य, "AIN4"पूर्ण,
	अणु"SDTO", शून्य, "ADC Ch4"पूर्ण,

	अणु"ADC Ch5", शून्य, "AIN5"पूर्ण,
	अणु"SDTO", शून्य, "ADC Ch5"पूर्ण,

	अणु"ADC Ch6", शून्य, "AIN6"पूर्ण,
	अणु"SDTO", शून्य, "ADC Ch6"पूर्ण,

	अणु"ADC Ch7", शून्य, "AIN7"पूर्ण,
	अणु"SDTO", शून्य, "ADC Ch7"पूर्ण,

	अणु"ADC Ch8", शून्य, "AIN8"पूर्ण,
	अणु"SDTO", शून्य, "ADC Ch8"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ak5552_पूर्णांकercon[] = अणु
	अणु"ADC Ch1", शून्य, "AIN1"पूर्ण,
	अणु"SDTO", शून्य, "ADC Ch1"पूर्ण,

	अणु"ADC Ch2", शून्य, "AIN2"पूर्ण,
	अणु"SDTO", शून्य, "ADC Ch2"पूर्ण,
पूर्ण;

अटल पूर्णांक ak5558_set_mcki(काष्ठा snd_soc_component *component)
अणु
	वापस snd_soc_component_update_bits(component, AK5558_02_CONTROL1, AK5558_CKS,
				   AK5558_CKS_AUTO);
पूर्ण

अटल पूर्णांक ak5558_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ak5558_priv *ak5558 = snd_soc_component_get_drvdata(component);
	u8 bits;
	पूर्णांक pcm_width = max(params_physical_width(params), ak5558->slot_width);

	चयन (pcm_width) अणु
	हाल 16:
		bits = AK5558_DIF_24BIT_MODE;
		अवरोध;
	हाल 32:
		bits = AK5558_DIF_32BIT_MODE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, AK5558_02_CONTROL1, AK5558_BITS, bits);

	वापस 0;
पूर्ण

अटल पूर्णांक ak5558_set_dai_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	u8 क्रमmat;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
	हाल SND_SOC_DAIFMT_CBM_CFS:
	शेष:
		dev_err(dai->dev, "Clock mode unsupported");
		वापस -EINVAL;
	पूर्ण

	/* set master/slave audio पूर्णांकerface */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		क्रमmat = AK5558_DIF_I2S_MODE;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		क्रमmat = AK5558_DIF_MSB_MODE;
		अवरोध;
	हाल SND_SOC_DAIFMT_DSP_B:
		क्रमmat = AK5558_DIF_MSB_MODE;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, AK5558_02_CONTROL1, AK5558_DIF, क्रमmat);

	वापस 0;
पूर्ण

अटल पूर्णांक ak5558_set_tdm_slot(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक tx_mask,
			       अचिन्हित पूर्णांक rx_mask, पूर्णांक slots,
			       पूर्णांक slot_width)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा ak5558_priv *ak5558 = snd_soc_component_get_drvdata(component);
	पूर्णांक tdm_mode;

	ak5558->slots = slots;
	ak5558->slot_width = slot_width;

	चयन (slots * slot_width) अणु
	हाल 128:
		tdm_mode = AK5558_MODE_TDM128;
		अवरोध;
	हाल 256:
		tdm_mode = AK5558_MODE_TDM256;
		अवरोध;
	हाल 512:
		tdm_mode = AK5558_MODE_TDM512;
		अवरोध;
	शेष:
		tdm_mode = AK5558_MODE_NORMAL;
		अवरोध;
	पूर्ण

	snd_soc_component_update_bits(component, AK5558_03_CONTROL2, AK5558_MODE_BITS,
			    tdm_mode);
	वापस 0;
पूर्ण

#घोषणा AK5558_FORMATS	(SNDRV_PCM_FMTBIT_S16_LE |\
			 SNDRV_PCM_FMTBIT_S24_LE |\
			 SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर अचिन्हित पूर्णांक ak5558_rates[] = अणु
	8000, 11025,  16000, 22050,
	32000, 44100, 48000, 88200,
	96000, 176400, 192000, 352800,
	384000, 705600, 768000, 1411200,
	2822400,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list ak5558_rate_स्थिरraपूर्णांकs = अणु
	.count = ARRAY_SIZE(ak5558_rates),
	.list = ak5558_rates,
पूर्ण;

अटल पूर्णांक ak5558_startup(काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_soc_dai *dai)
अणु
	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
					  SNDRV_PCM_HW_PARAM_RATE,
					  &ak5558_rate_स्थिरraपूर्णांकs);
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops ak5558_dai_ops = अणु
	.startup        = ak5558_startup,
	.hw_params	= ak5558_hw_params,

	.set_fmt	= ak5558_set_dai_fmt,
	.set_tdm_slot   = ak5558_set_tdm_slot,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ak5558_dai = अणु
	.name = "ak5558-aif",
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 8,
		.rates = SNDRV_PCM_RATE_KNOT,
		.क्रमmats = AK5558_FORMATS,
	पूर्ण,
	.ops = &ak5558_dai_ops,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver ak5552_dai = अणु
	.name = "ak5552-aif",
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_KNOT,
		.क्रमmats = AK5558_FORMATS,
	पूर्ण,
	.ops = &ak5558_dai_ops,
पूर्ण;

अटल व्योम ak5558_reset(काष्ठा ak5558_priv *ak5558, bool active)
अणु
	अगर (!ak5558->reset_gpiod)
		वापस;

	gpiod_set_value_cansleep(ak5558->reset_gpiod, active);
	usleep_range(1000, 2000);
पूर्ण

अटल पूर्णांक ak5558_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ak5558_priv *ak5558 = snd_soc_component_get_drvdata(component);

	ak5558_reset(ak5558, false);
	वापस ak5558_set_mcki(component);
पूर्ण

अटल व्योम ak5558_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ak5558_priv *ak5558 = snd_soc_component_get_drvdata(component);

	ak5558_reset(ak5558, true);
पूर्ण

अटल पूर्णांक __maybe_unused ak5558_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा ak5558_priv *ak5558 = dev_get_drvdata(dev);

	regcache_cache_only(ak5558->regmap, true);
	ak5558_reset(ak5558, true);

	regulator_bulk_disable(ARRAY_SIZE(ak5558->supplies),
			       ak5558->supplies);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused ak5558_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा ak5558_priv *ak5558 = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(ak5558->supplies),
				    ak5558->supplies);
	अगर (ret != 0) अणु
		dev_err(dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	ak5558_reset(ak5558, true);
	ak5558_reset(ak5558, false);

	regcache_cache_only(ak5558->regmap, false);
	regcache_mark_dirty(ak5558->regmap);

	वापस regcache_sync(ak5558->regmap);
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops ak5558_pm = अणु
	SET_RUNTIME_PM_OPS(ak5558_runसमय_suspend, ak5558_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_codec_dev_ak5558 = अणु
	.probe			= ak5558_probe,
	.हटाओ			= ak5558_हटाओ,
	.controls		= ak5558_snd_controls,
	.num_controls		= ARRAY_SIZE(ak5558_snd_controls),
	.dapm_widमाला_लो		= ak5558_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ak5558_dapm_widमाला_लो),
	.dapm_routes		= ak5558_पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(ak5558_पूर्णांकercon),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_codec_dev_ak5552 = अणु
	.probe			= ak5558_probe,
	.हटाओ			= ak5558_हटाओ,
	.controls		= ak5552_snd_controls,
	.num_controls		= ARRAY_SIZE(ak5552_snd_controls),
	.dapm_widमाला_लो		= ak5552_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ak5552_dapm_widमाला_लो),
	.dapm_routes		= ak5552_पूर्णांकercon,
	.num_dapm_routes	= ARRAY_SIZE(ak5552_पूर्णांकercon),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ak5558_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = AK5558_05_DSD,
	.reg_शेषs = ak5558_reg,
	.num_reg_शेषs = ARRAY_SIZE(ak5558_reg),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक ak5558_i2c_probe(काष्ठा i2c_client *i2c)
अणु
	काष्ठा ak5558_priv *ak5558;
	पूर्णांक ret = 0;
	पूर्णांक dev_id;
	पूर्णांक i;

	ak5558 = devm_kzalloc(&i2c->dev, माप(*ak5558), GFP_KERNEL);
	अगर (!ak5558)
		वापस -ENOMEM;

	ak5558->regmap = devm_regmap_init_i2c(i2c, &ak5558_regmap);
	अगर (IS_ERR(ak5558->regmap))
		वापस PTR_ERR(ak5558->regmap);

	i2c_set_clientdata(i2c, ak5558);
	ak5558->i2c = i2c;

	ak5558->reset_gpiod = devm_gpiod_get_optional(&i2c->dev, "reset",
						      GPIOD_OUT_LOW);
	अगर (IS_ERR(ak5558->reset_gpiod))
		वापस PTR_ERR(ak5558->reset_gpiod);

	क्रम (i = 0; i < ARRAY_SIZE(ak5558->supplies); i++)
		ak5558->supplies[i].supply = ak5558_supply_names[i];

	ret = devm_regulator_bulk_get(&i2c->dev, ARRAY_SIZE(ak5558->supplies),
				      ak5558->supplies);
	अगर (ret != 0) अणु
		dev_err(&i2c->dev, "Failed to request supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	dev_id = (uपूर्णांकptr_t)of_device_get_match_data(&i2c->dev);
	चयन (dev_id) अणु
	हाल AK5552:
		ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
						      &soc_codec_dev_ak5552,
						      &ak5552_dai, 1);
		अवरोध;
	हाल AK5558:
		ret = devm_snd_soc_रेजिस्टर_component(&i2c->dev,
						      &soc_codec_dev_ak5558,
						      &ak5558_dai, 1);
		अवरोध;
	शेष:
		dev_err(&i2c->dev, "unexpected device type\n");
		वापस -EINVAL;
	पूर्ण
	अगर (ret < 0) अणु
		dev_err(&i2c->dev, "failed to register component: %d\n", ret);
		वापस ret;
	पूर्ण

	pm_runसमय_enable(&i2c->dev);
	regcache_cache_only(ak5558->regmap, true);

	वापस 0;
पूर्ण

अटल पूर्णांक ak5558_i2c_हटाओ(काष्ठा i2c_client *i2c)
अणु
	pm_runसमय_disable(&i2c->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ak5558_i2c_dt_ids[] __maybe_unused = अणु
	अणु .compatible = "asahi-kasei,ak5558", .data = (व्योम *) AK5558 पूर्ण,
	अणु .compatible = "asahi-kasei,ak5552", .data = (व्योम *) AK5552 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ak5558_i2c_dt_ids);

अटल काष्ठा i2c_driver ak5558_i2c_driver = अणु
	.driver = अणु
		.name = "ak5558",
		.of_match_table = of_match_ptr(ak5558_i2c_dt_ids),
		.pm = &ak5558_pm,
	पूर्ण,
	.probe_new = ak5558_i2c_probe,
	.हटाओ = ak5558_i2c_हटाओ,
पूर्ण;

module_i2c_driver(ak5558_i2c_driver);

MODULE_AUTHOR("Junichi Wakasugi <wakasugi.jb@om.asahi-kasei.co.jp>");
MODULE_AUTHOR("Mihai Serban <mihai.serban@nxp.com>");
MODULE_DESCRIPTION("ASoC AK5558 ADC driver");
MODULE_LICENSE("GPL v2");
