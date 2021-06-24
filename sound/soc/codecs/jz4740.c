<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// JZ4740 CODEC driver
//
// Copyright (C) 2009-2010, Lars-Peter Clausen <lars@metafoo.de>

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/regmap.h>

#समावेश <linux/delay.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>

#घोषणा JZ4740_REG_CODEC_1 0x0
#घोषणा JZ4740_REG_CODEC_2 0x4

#घोषणा JZ4740_CODEC_1_LINE_ENABLE BIT(29)
#घोषणा JZ4740_CODEC_1_MIC_ENABLE BIT(28)
#घोषणा JZ4740_CODEC_1_SW1_ENABLE BIT(27)
#घोषणा JZ4740_CODEC_1_ADC_ENABLE BIT(26)
#घोषणा JZ4740_CODEC_1_SW2_ENABLE BIT(25)
#घोषणा JZ4740_CODEC_1_DAC_ENABLE BIT(24)
#घोषणा JZ4740_CODEC_1_VREF_DISABLE BIT(20)
#घोषणा JZ4740_CODEC_1_VREF_AMP_DISABLE BIT(19)
#घोषणा JZ4740_CODEC_1_VREF_PULLDOWN BIT(18)
#घोषणा JZ4740_CODEC_1_VREF_LOW_CURRENT BIT(17)
#घोषणा JZ4740_CODEC_1_VREF_HIGH_CURRENT BIT(16)
#घोषणा JZ4740_CODEC_1_HEADPHONE_DISABLE BIT(14)
#घोषणा JZ4740_CODEC_1_HEADPHONE_AMP_CHANGE_ANY BIT(13)
#घोषणा JZ4740_CODEC_1_HEADPHONE_CHARGE BIT(12)
#घोषणा JZ4740_CODEC_1_HEADPHONE_PULLDOWN (BIT(11) | BIT(10))
#घोषणा JZ4740_CODEC_1_HEADPHONE_POWERDOWN_M BIT(9)
#घोषणा JZ4740_CODEC_1_HEADPHONE_POWERDOWN BIT(8)
#घोषणा JZ4740_CODEC_1_SUSPEND BIT(1)
#घोषणा JZ4740_CODEC_1_RESET BIT(0)

#घोषणा JZ4740_CODEC_1_LINE_ENABLE_OFFSET 29
#घोषणा JZ4740_CODEC_1_MIC_ENABLE_OFFSET 28
#घोषणा JZ4740_CODEC_1_SW1_ENABLE_OFFSET 27
#घोषणा JZ4740_CODEC_1_ADC_ENABLE_OFFSET 26
#घोषणा JZ4740_CODEC_1_SW2_ENABLE_OFFSET 25
#घोषणा JZ4740_CODEC_1_DAC_ENABLE_OFFSET 24
#घोषणा JZ4740_CODEC_1_HEADPHONE_DISABLE_OFFSET 14
#घोषणा JZ4740_CODEC_1_HEADPHONE_POWERDOWN_OFFSET 8

#घोषणा JZ4740_CODEC_2_INPUT_VOLUME_MASK		0x1f0000
#घोषणा JZ4740_CODEC_2_SAMPLE_RATE_MASK			0x000f00
#घोषणा JZ4740_CODEC_2_MIC_BOOST_GAIN_MASK		0x000030
#घोषणा JZ4740_CODEC_2_HEADPHONE_VOLUME_MASK	0x000003

#घोषणा JZ4740_CODEC_2_INPUT_VOLUME_OFFSET		16
#घोषणा JZ4740_CODEC_2_SAMPLE_RATE_OFFSET		 8
#घोषणा JZ4740_CODEC_2_MIC_BOOST_GAIN_OFFSET	 4
#घोषणा JZ4740_CODEC_2_HEADPHONE_VOLUME_OFFSET	 0

अटल स्थिर काष्ठा reg_शेष jz4740_codec_reg_शेषs[] = अणु
	अणु JZ4740_REG_CODEC_1, 0x021b2302 पूर्ण,
	अणु JZ4740_REG_CODEC_2, 0x00170803 पूर्ण,
पूर्ण;

काष्ठा jz4740_codec अणु
	काष्ठा regmap *regmap;
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_RANGE(jz4740_mic_tlv,
	0, 2, TLV_DB_SCALE_ITEM(0, 600, 0),
	3, 3, TLV_DB_SCALE_ITEM(2000, 0, 0)
);

अटल स्थिर DECLARE_TLV_DB_SCALE(jz4740_out_tlv, 0, 200, 0);
अटल स्थिर DECLARE_TLV_DB_SCALE(jz4740_in_tlv, -3450, 150, 0);

अटल स्थिर काष्ठा snd_kcontrol_new jz4740_codec_controls[] = अणु
	SOC_SINGLE_TLV("Master Playback Volume", JZ4740_REG_CODEC_2,
			JZ4740_CODEC_2_HEADPHONE_VOLUME_OFFSET, 3, 0,
			jz4740_out_tlv),
	SOC_SINGLE_TLV("Master Capture Volume", JZ4740_REG_CODEC_2,
			JZ4740_CODEC_2_INPUT_VOLUME_OFFSET, 31, 0,
			jz4740_in_tlv),
	SOC_SINGLE("Master Playback Switch", JZ4740_REG_CODEC_1,
			JZ4740_CODEC_1_HEADPHONE_DISABLE_OFFSET, 1, 1),
	SOC_SINGLE_TLV("Mic Capture Volume", JZ4740_REG_CODEC_2,
			JZ4740_CODEC_2_MIC_BOOST_GAIN_OFFSET, 3, 0,
			jz4740_mic_tlv),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new jz4740_codec_output_controls[] = अणु
	SOC_DAPM_SINGLE("Bypass Switch", JZ4740_REG_CODEC_1,
			JZ4740_CODEC_1_SW1_ENABLE_OFFSET, 1, 0),
	SOC_DAPM_SINGLE("DAC Switch", JZ4740_REG_CODEC_1,
			JZ4740_CODEC_1_SW2_ENABLE_OFFSET, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new jz4740_codec_input_controls[] = अणु
	SOC_DAPM_SINGLE("Line Capture Switch", JZ4740_REG_CODEC_1,
			JZ4740_CODEC_1_LINE_ENABLE_OFFSET, 1, 0),
	SOC_DAPM_SINGLE("Mic Capture Switch", JZ4740_REG_CODEC_1,
			JZ4740_CODEC_1_MIC_ENABLE_OFFSET, 1, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget jz4740_codec_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_ADC("ADC", "Capture", JZ4740_REG_CODEC_1,
			JZ4740_CODEC_1_ADC_ENABLE_OFFSET, 0),
	SND_SOC_DAPM_DAC("DAC", "Playback", JZ4740_REG_CODEC_1,
			JZ4740_CODEC_1_DAC_ENABLE_OFFSET, 0),

	SND_SOC_DAPM_MIXER("Output Mixer", JZ4740_REG_CODEC_1,
			JZ4740_CODEC_1_HEADPHONE_POWERDOWN_OFFSET, 1,
			jz4740_codec_output_controls,
			ARRAY_SIZE(jz4740_codec_output_controls)),

	SND_SOC_DAPM_MIXER_NAMED_CTL("Input Mixer", SND_SOC_NOPM, 0, 0,
			jz4740_codec_input_controls,
			ARRAY_SIZE(jz4740_codec_input_controls)),
	SND_SOC_DAPM_MIXER("Line Input", SND_SOC_NOPM, 0, 0, शून्य, 0),

	SND_SOC_DAPM_OUTPUT("LOUT"),
	SND_SOC_DAPM_OUTPUT("ROUT"),

	SND_SOC_DAPM_INPUT("MIC"),
	SND_SOC_DAPM_INPUT("LIN"),
	SND_SOC_DAPM_INPUT("RIN"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route jz4740_codec_dapm_routes[] = अणु
	अणु"Line Input", शून्य, "LIN"पूर्ण,
	अणु"Line Input", शून्य, "RIN"पूर्ण,

	अणु"Input Mixer", "Line Capture Switch", "Line Input"पूर्ण,
	अणु"Input Mixer", "Mic Capture Switch", "MIC"पूर्ण,

	अणु"ADC", शून्य, "Input Mixer"पूर्ण,

	अणु"Output Mixer", "Bypass Switch", "Input Mixer"पूर्ण,
	अणु"Output Mixer", "DAC Switch", "DAC"पूर्ण,

	अणु"LOUT", शून्य, "Output Mixer"पूर्ण,
	अणु"ROUT", शून्य, "Output Mixer"पूर्ण,
पूर्ण;

अटल पूर्णांक jz4740_codec_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा jz4740_codec *jz4740_codec = snd_soc_component_get_drvdata(dai->component);
	uपूर्णांक32_t val;

	चयन (params_rate(params)) अणु
	हाल 8000:
		val = 0;
		अवरोध;
	हाल 11025:
		val = 1;
		अवरोध;
	हाल 12000:
		val = 2;
		अवरोध;
	हाल 16000:
		val = 3;
		अवरोध;
	हाल 22050:
		val = 4;
		अवरोध;
	हाल 24000:
		val = 5;
		अवरोध;
	हाल 32000:
		val = 6;
		अवरोध;
	हाल 44100:
		val = 7;
		अवरोध;
	हाल 48000:
		val = 8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	val <<= JZ4740_CODEC_2_SAMPLE_RATE_OFFSET;

	regmap_update_bits(jz4740_codec->regmap, JZ4740_REG_CODEC_2,
				JZ4740_CODEC_2_SAMPLE_RATE_MASK, val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops jz4740_codec_dai_ops = अणु
	.hw_params = jz4740_codec_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver jz4740_codec_dai = अणु
	.name = "jz4740-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S8,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S8,
	पूर्ण,
	.ops = &jz4740_codec_dai_ops,
	.symmetric_rate = 1,
पूर्ण;

अटल व्योम jz4740_codec_wakeup(काष्ठा regmap *regmap)
अणु
	regmap_set_bits(regmap, JZ4740_REG_CODEC_1, JZ4740_CODEC_1_RESET);
	udelay(2);

	regmap_clear_bits(regmap, JZ4740_REG_CODEC_1,
			  JZ4740_CODEC_1_SUSPEND | JZ4740_CODEC_1_RESET);

	regcache_sync(regmap);
पूर्ण

अटल पूर्णांक jz4740_codec_set_bias_level(काष्ठा snd_soc_component *component,
	क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा jz4740_codec *jz4740_codec = snd_soc_component_get_drvdata(component);
	काष्ठा regmap *regmap = jz4740_codec->regmap;
	अचिन्हित पूर्णांक mask;

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		mask = JZ4740_CODEC_1_VREF_DISABLE |
				JZ4740_CODEC_1_VREF_AMP_DISABLE |
				JZ4740_CODEC_1_HEADPHONE_POWERDOWN_M;

		regmap_clear_bits(regmap, JZ4740_REG_CODEC_1, mask);
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		/* The only way to clear the suspend flag is to reset the codec */
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF)
			jz4740_codec_wakeup(regmap);

		mask = JZ4740_CODEC_1_VREF_DISABLE |
			JZ4740_CODEC_1_VREF_AMP_DISABLE |
			JZ4740_CODEC_1_HEADPHONE_POWERDOWN_M;

		regmap_set_bits(regmap, JZ4740_REG_CODEC_1, mask);
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		mask = JZ4740_CODEC_1_SUSPEND;
		regmap_set_bits(regmap, JZ4740_REG_CODEC_1, mask);
		regcache_mark_dirty(regmap);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jz4740_codec_dev_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा jz4740_codec *jz4740_codec = snd_soc_component_get_drvdata(component);

	regmap_update_bits(jz4740_codec->regmap, JZ4740_REG_CODEC_1,
			JZ4740_CODEC_1_SW2_ENABLE, JZ4740_CODEC_1_SW2_ENABLE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_codec_dev_jz4740_codec = अणु
	.probe			= jz4740_codec_dev_probe,
	.set_bias_level		= jz4740_codec_set_bias_level,
	.controls		= jz4740_codec_controls,
	.num_controls		= ARRAY_SIZE(jz4740_codec_controls),
	.dapm_widमाला_लो		= jz4740_codec_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(jz4740_codec_dapm_widमाला_लो),
	.dapm_routes		= jz4740_codec_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(jz4740_codec_dapm_routes),
	.suspend_bias_off	= 1,
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,

पूर्ण;

अटल स्थिर काष्ठा regmap_config jz4740_codec_regmap_config = अणु
	.reg_bits = 32,
	.reg_stride = 4,
	.val_bits = 32,
	.max_रेजिस्टर = JZ4740_REG_CODEC_2,

	.reg_शेषs = jz4740_codec_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(jz4740_codec_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक jz4740_codec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा jz4740_codec *jz4740_codec;
	व्योम __iomem *base;

	jz4740_codec = devm_kzalloc(&pdev->dev, माप(*jz4740_codec),
				    GFP_KERNEL);
	अगर (!jz4740_codec)
		वापस -ENOMEM;

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	jz4740_codec->regmap = devm_regmap_init_mmio(&pdev->dev, base,
					    &jz4740_codec_regmap_config);
	अगर (IS_ERR(jz4740_codec->regmap))
		वापस PTR_ERR(jz4740_codec->regmap);

	platक्रमm_set_drvdata(pdev, jz4740_codec);

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&soc_codec_dev_jz4740_codec, &jz4740_codec_dai, 1);
	अगर (ret)
		dev_err(&pdev->dev, "Failed to register codec\n");

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id jz4740_codec_of_matches[] = अणु
	अणु .compatible = "ingenic,jz4740-codec", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, jz4740_codec_of_matches);

अटल काष्ठा platक्रमm_driver jz4740_codec_driver = अणु
	.probe = jz4740_codec_probe,
	.driver = अणु
		.name = "jz4740-codec",
		.of_match_table = jz4740_codec_of_matches,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(jz4740_codec_driver);

MODULE_DESCRIPTION("JZ4740 SoC internal codec driver");
MODULE_AUTHOR("Lars-Peter Clausen <lars@metafoo.de>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:jz4740-codec");
