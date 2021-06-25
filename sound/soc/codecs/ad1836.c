<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
 /*
 * Audio Codec driver supporting:
 *  AD1835A, AD1836, AD1837A, AD1838A, AD1839A
 *
 * Copyright 2009-2011 Analog Devices Inc.
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>
#समावेश <sound/tlv.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regmap.h>

#समावेश "ad1836.h"

क्रमागत ad1836_type अणु
	AD1835,
	AD1836,
	AD1838,
पूर्ण;

/* codec निजी data */
काष्ठा ad1836_priv अणु
	क्रमागत ad1836_type type;
	काष्ठा regmap *regmap;
पूर्ण;

/*
 * AD1836 volume/mute/de-emphasis etc. controls
 */
अटल स्थिर अक्षर *ad1836_deemp[] = अणु"None", "44.1kHz", "32kHz", "48kHz"पूर्ण;

अटल SOC_ENUM_SINGLE_DECL(ad1836_deemp_क्रमागत,
			    AD1836_DAC_CTRL1, 8, ad1836_deemp);

#घोषणा AD1836_DAC_VOLUME(x) \
	SOC_DOUBLE_R("DAC" #x " Playback Volume", AD1836_DAC_L_VOL(x), \
			AD1836_DAC_R_VOL(x), 0, 0x3FF, 0)

#घोषणा AD1836_DAC_SWITCH(x) \
	SOC_DOUBLE("DAC" #x " Playback Switch", AD1836_DAC_CTRL2, \
			AD1836_MUTE_LEFT(x), AD1836_MUTE_RIGHT(x), 1, 1)

#घोषणा AD1836_ADC_SWITCH(x) \
	SOC_DOUBLE("ADC" #x " Capture Switch", AD1836_ADC_CTRL2, \
		AD1836_MUTE_LEFT(x), AD1836_MUTE_RIGHT(x), 1, 1)

अटल स्थिर काष्ठा snd_kcontrol_new ad183x_dac_controls[] = अणु
	AD1836_DAC_VOLUME(1),
	AD1836_DAC_SWITCH(1),
	AD1836_DAC_VOLUME(2),
	AD1836_DAC_SWITCH(2),
	AD1836_DAC_VOLUME(3),
	AD1836_DAC_SWITCH(3),
	AD1836_DAC_VOLUME(4),
	AD1836_DAC_SWITCH(4),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget ad183x_dac_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_OUTPUT("DAC1OUT"),
	SND_SOC_DAPM_OUTPUT("DAC2OUT"),
	SND_SOC_DAPM_OUTPUT("DAC3OUT"),
	SND_SOC_DAPM_OUTPUT("DAC4OUT"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ad183x_dac_routes[] = अणु
	अणु "DAC1OUT", शून्य, "DAC" पूर्ण,
	अणु "DAC2OUT", शून्य, "DAC" पूर्ण,
	अणु "DAC3OUT", शून्य, "DAC" पूर्ण,
	अणु "DAC4OUT", शून्य, "DAC" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new ad183x_adc_controls[] = अणु
	AD1836_ADC_SWITCH(1),
	AD1836_ADC_SWITCH(2),
	AD1836_ADC_SWITCH(3),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget ad183x_adc_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_INPUT("ADC1IN"),
	SND_SOC_DAPM_INPUT("ADC2IN"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ad183x_adc_routes[] = अणु
	अणु "ADC", शून्य, "ADC1IN" पूर्ण,
	अणु "ADC", शून्य, "ADC2IN" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new ad183x_controls[] = अणु
	/* ADC high-pass filter */
	SOC_SINGLE("ADC High Pass Filter Switch", AD1836_ADC_CTRL1,
			AD1836_ADC_HIGHPASS_FILTER, 1, 0),

	/* DAC de-emphasis */
	SOC_ENUM("Playback Deemphasis", ad1836_deemp_क्रमागत),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget ad183x_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("DAC", "Playback", AD1836_DAC_CTRL1,
				AD1836_DAC_POWERDOWN, 1),
	SND_SOC_DAPM_ADC("ADC", "Capture", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_SUPPLY("ADC_PWR", AD1836_ADC_CTRL1,
				AD1836_ADC_POWERDOWN, 1, शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route ad183x_dapm_routes[] = अणु
	अणु "DAC", शून्य, "ADC_PWR" पूर्ण,
	अणु "ADC", शून्य, "ADC_PWR" पूर्ण,
पूर्ण;

अटल स्थिर DECLARE_TLV_DB_SCALE(ad1836_in_tlv, 0, 300, 0);

अटल स्थिर काष्ठा snd_kcontrol_new ad1836_controls[] = अणु
	SOC_DOUBLE_TLV("ADC2 Capture Volume", AD1836_ADC_CTRL1, 3, 0, 4, 0,
	    ad1836_in_tlv),
पूर्ण;

/*
 * DAI ops entries
 */

अटल पूर्णांक ad1836_set_dai_fmt(काष्ठा snd_soc_dai *codec_dai,
		अचिन्हित पूर्णांक fmt)
अणु
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	/* at present, we support adc aux mode to पूर्णांकerface with
	 * blackfin sport tdm mode
	 */
	हाल SND_SOC_DAIFMT_DSP_A:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_IB_IF:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	/* ALCLK,ABCLK are both output, AD1836 can only be master */
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ad1836_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params,
		काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा ad1836_priv *ad1836 = snd_soc_component_get_drvdata(dai->component);
	पूर्णांक word_len = 0;

	/* bit size */
	चयन (params_width(params)) अणु
	हाल 16:
		word_len = AD1836_WORD_LEN_16;
		अवरोध;
	हाल 20:
		word_len = AD1836_WORD_LEN_20;
		अवरोध;
	हाल 24:
	हाल 32:
		word_len = AD1836_WORD_LEN_24;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(ad1836->regmap, AD1836_DAC_CTRL1,
		AD1836_DAC_WORD_LEN_MASK,
		word_len << AD1836_DAC_WORD_LEN_OFFSET);

	regmap_update_bits(ad1836->regmap, AD1836_ADC_CTRL2,
		AD1836_ADC_WORD_LEN_MASK,
		word_len << AD1836_ADC_WORD_OFFSET);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops ad1836_dai_ops = अणु
	.hw_params = ad1836_hw_params,
	.set_fmt = ad1836_set_dai_fmt,
पूर्ण;

#घोषणा AD183X_DAI(_name, num_dacs, num_adcs) \
अणु \
	.name = _name "-hifi", \
	.playback = अणु \
		.stream_name = "Playback", \
		.channels_min = 2, \
		.channels_max = (num_dacs) * 2, \
		.rates = SNDRV_PCM_RATE_48000,  \
		.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S16_LE | \
			SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S24_LE, \
	पूर्ण, \
	.capture = अणु \
		.stream_name = "Capture", \
		.channels_min = 2, \
		.channels_max = (num_adcs) * 2, \
		.rates = SNDRV_PCM_RATE_48000, \
		.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S16_LE | \
			SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S24_LE, \
	पूर्ण, \
	.ops = &ad1836_dai_ops, \
पूर्ण

अटल काष्ठा snd_soc_dai_driver ad183x_dais[] = अणु
	[AD1835] = AD183X_DAI("ad1835", 4, 1),
	[AD1836] = AD183X_DAI("ad1836", 3, 2),
	[AD1838] = AD183X_DAI("ad1838", 3, 1),
पूर्ण;

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ad1836_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ad1836_priv *ad1836 = snd_soc_component_get_drvdata(component);
	/* reset घड़ी control mode */
	वापस regmap_update_bits(ad1836->regmap, AD1836_ADC_CTRL2,
		AD1836_ADC_SERFMT_MASK, 0);
पूर्ण

अटल पूर्णांक ad1836_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ad1836_priv *ad1836 = snd_soc_component_get_drvdata(component);
	/* restore घड़ी control mode */
	वापस regmap_update_bits(ad1836->regmap, AD1836_ADC_CTRL2,
		AD1836_ADC_SERFMT_MASK, AD1836_ADC_AUX);
पूर्ण
#अन्यथा
#घोषणा ad1836_suspend शून्य
#घोषणा ad1836_resume  शून्य
#पूर्ण_अगर

अटल पूर्णांक ad1836_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ad1836_priv *ad1836 = snd_soc_component_get_drvdata(component);
	काष्ठा snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);
	पूर्णांक num_dacs, num_adcs;
	पूर्णांक ret = 0;
	पूर्णांक i;

	num_dacs = ad183x_dais[ad1836->type].playback.channels_max / 2;
	num_adcs = ad183x_dais[ad1836->type].capture.channels_max / 2;

	/* शेष setting क्रम ad1836 */
	/* de-emphasis: 48kHz, घातer-on dac */
	regmap_ग_लिखो(ad1836->regmap, AD1836_DAC_CTRL1, 0x300);
	/* unmute dac channels */
	regmap_ग_लिखो(ad1836->regmap, AD1836_DAC_CTRL2, 0x0);
	/* high-pass filter enable, घातer-on adc */
	regmap_ग_लिखो(ad1836->regmap, AD1836_ADC_CTRL1, 0x100);
	/* unmute adc channles, adc aux mode */
	regmap_ग_लिखो(ad1836->regmap, AD1836_ADC_CTRL2, 0x180);
	/* volume */
	क्रम (i = 1; i <= num_dacs; ++i) अणु
		regmap_ग_लिखो(ad1836->regmap, AD1836_DAC_L_VOL(i), 0x3FF);
		regmap_ग_लिखो(ad1836->regmap, AD1836_DAC_R_VOL(i), 0x3FF);
	पूर्ण

	अगर (ad1836->type == AD1836) अणु
		/* left/right dअगरf:PGA/MUX */
		regmap_ग_लिखो(ad1836->regmap, AD1836_ADC_CTRL3, 0x3A);
		ret = snd_soc_add_component_controls(component, ad1836_controls,
				ARRAY_SIZE(ad1836_controls));
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		regmap_ग_लिखो(ad1836->regmap, AD1836_ADC_CTRL3, 0x00);
	पूर्ण

	ret = snd_soc_add_component_controls(component, ad183x_dac_controls, num_dacs * 2);
	अगर (ret)
		वापस ret;

	ret = snd_soc_add_component_controls(component, ad183x_adc_controls, num_adcs);
	अगर (ret)
		वापस ret;

	ret = snd_soc_dapm_new_controls(dapm, ad183x_dac_dapm_widमाला_लो, num_dacs);
	अगर (ret)
		वापस ret;

	ret = snd_soc_dapm_new_controls(dapm, ad183x_adc_dapm_widमाला_लो, num_adcs);
	अगर (ret)
		वापस ret;

	ret = snd_soc_dapm_add_routes(dapm, ad183x_dac_routes, num_dacs);
	अगर (ret)
		वापस ret;

	ret = snd_soc_dapm_add_routes(dapm, ad183x_adc_routes, num_adcs);

	वापस ret;
पूर्ण

/* घातer करोwn chip */
अटल व्योम ad1836_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा ad1836_priv *ad1836 = snd_soc_component_get_drvdata(component);
	/* reset घड़ी control mode */
	regmap_update_bits(ad1836->regmap, AD1836_ADC_CTRL2,
		AD1836_ADC_SERFMT_MASK, 0);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_ad1836 = अणु
	.probe			= ad1836_probe,
	.हटाओ			= ad1836_हटाओ,
	.suspend		= ad1836_suspend,
	.resume			= ad1836_resume,
	.controls		= ad183x_controls,
	.num_controls		= ARRAY_SIZE(ad183x_controls),
	.dapm_widमाला_लो		= ad183x_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(ad183x_dapm_widमाला_लो),
	.dapm_routes		= ad183x_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(ad183x_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा reg_शेष ad1836_reg_शेषs[] = अणु
	अणु AD1836_DAC_CTRL1, 0x0000 पूर्ण,
	अणु AD1836_DAC_CTRL2, 0x0000 पूर्ण,
	अणु AD1836_DAC_L_VOL(0), 0x0000 पूर्ण,
	अणु AD1836_DAC_R_VOL(0), 0x0000 पूर्ण,
	अणु AD1836_DAC_L_VOL(1), 0x0000 पूर्ण,
	अणु AD1836_DAC_R_VOL(1), 0x0000 पूर्ण,
	अणु AD1836_DAC_L_VOL(2), 0x0000 पूर्ण,
	अणु AD1836_DAC_R_VOL(2), 0x0000 पूर्ण,
	अणु AD1836_DAC_L_VOL(3), 0x0000 पूर्ण,
	अणु AD1836_DAC_R_VOL(3), 0x0000 पूर्ण,
	अणु AD1836_ADC_CTRL1, 0x0000 पूर्ण,
	अणु AD1836_ADC_CTRL2, 0x0000 पूर्ण,
	अणु AD1836_ADC_CTRL3, 0x0000 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_config ad1836_regmap_config = अणु
	.val_bits = 12,
	.reg_bits = 4,
	.पढ़ो_flag_mask = 0x08,

	.max_रेजिस्टर = AD1836_ADC_CTRL3,
	.reg_शेषs = ad1836_reg_शेषs,
	.num_reg_शेषs = ARRAY_SIZE(ad1836_reg_शेषs),
	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक ad1836_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा ad1836_priv *ad1836;
	पूर्णांक ret;

	ad1836 = devm_kzalloc(&spi->dev, माप(काष्ठा ad1836_priv),
			      GFP_KERNEL);
	अगर (ad1836 == शून्य)
		वापस -ENOMEM;

	ad1836->regmap = devm_regmap_init_spi(spi, &ad1836_regmap_config);
	अगर (IS_ERR(ad1836->regmap))
		वापस PTR_ERR(ad1836->regmap);

	ad1836->type = spi_get_device_id(spi)->driver_data;

	spi_set_drvdata(spi, ad1836);

	ret = devm_snd_soc_रेजिस्टर_component(&spi->dev,
			&soc_component_dev_ad1836, &ad183x_dais[ad1836->type], 1);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा spi_device_id ad1836_ids[] = अणु
	अणु "ad1835", AD1835 पूर्ण,
	अणु "ad1836", AD1836 पूर्ण,
	अणु "ad1837", AD1835 पूर्ण,
	अणु "ad1838", AD1838 पूर्ण,
	अणु "ad1839", AD1838 पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, ad1836_ids);

अटल काष्ठा spi_driver ad1836_spi_driver = अणु
	.driver = अणु
		.name	= "ad1836",
	पूर्ण,
	.probe		= ad1836_spi_probe,
	.id_table	= ad1836_ids,
पूर्ण;

module_spi_driver(ad1836_spi_driver);

MODULE_DESCRIPTION("ASoC ad1836 driver");
MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_LICENSE("GPL");
