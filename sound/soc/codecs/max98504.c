<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MAX98504 ALSA SoC Audio driver
 *
 * Copyright 2013 - 2014 Maxim Integrated Products
 * Copyright 2016 Samsung Electronics Co., Ltd.
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <sound/soc.h>

#समावेश "max98504.h"

अटल स्थिर अक्षर * स्थिर max98504_supply_names[] = अणु
	"DVDD",
	"DIOVDD",
	"PVDD",
पूर्ण;
#घोषणा MAX98504_NUM_SUPPLIES ARRAY_SIZE(max98504_supply_names)

काष्ठा max98504_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा regulator_bulk_data supplies[MAX98504_NUM_SUPPLIES];
	अचिन्हित पूर्णांक pcm_rx_channels;
	bool brownout_enable;
	अचिन्हित पूर्णांक brownout_threshold;
	अचिन्हित पूर्णांक brownout_attenuation;
	अचिन्हित पूर्णांक brownout_attack_hold;
	अचिन्हित पूर्णांक brownout_समयd_hold;
	अचिन्हित पूर्णांक brownout_release_rate;
पूर्ण;

अटल काष्ठा reg_शेष max98504_reg_शेषs[] = अणु
	अणु 0x01,	0पूर्ण,
	अणु 0x02,	0पूर्ण,
	अणु 0x03,	0पूर्ण,
	अणु 0x04,	0पूर्ण,
	अणु 0x10, 0पूर्ण,
	अणु 0x11, 0पूर्ण,
	अणु 0x12, 0पूर्ण,
	अणु 0x13, 0पूर्ण,
	अणु 0x14, 0पूर्ण,
	अणु 0x15, 0पूर्ण,
	अणु 0x16, 0पूर्ण,
	अणु 0x17, 0पूर्ण,
	अणु 0x18, 0पूर्ण,
	अणु 0x19, 0पूर्ण,
	अणु 0x1A, 0पूर्ण,
	अणु 0x20, 0पूर्ण,
	अणु 0x21, 0पूर्ण,
	अणु 0x22, 0पूर्ण,
	अणु 0x23, 0पूर्ण,
	अणु 0x24, 0पूर्ण,
	अणु 0x25, 0पूर्ण,
	अणु 0x26, 0पूर्ण,
	अणु 0x27, 0पूर्ण,
	अणु 0x28, 0पूर्ण,
	अणु 0x30, 0पूर्ण,
	अणु 0x31, 0पूर्ण,
	अणु 0x32, 0पूर्ण,
	अणु 0x33, 0पूर्ण,
	अणु 0x34, 0पूर्ण,
	अणु 0x35, 0पूर्ण,
	अणु 0x36, 0पूर्ण,
	अणु 0x37, 0पूर्ण,
	अणु 0x38, 0पूर्ण,
	अणु 0x39, 0पूर्ण,
	अणु 0x40, 0पूर्ण,
	अणु 0x41, 0पूर्ण,
पूर्ण;

अटल bool max98504_अस्थिर_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX98504_INTERRUPT_STATUS:
	हाल MAX98504_INTERRUPT_FLAGS:
	हाल MAX98504_INTERRUPT_FLAG_CLEARS:
	हाल MAX98504_WATCHDOG_CLEAR:
	हाल MAX98504_GLOBAL_ENABLE:
	हाल MAX98504_SOFTWARE_RESET:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool max98504_पढ़ोable_रेजिस्टर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MAX98504_SOFTWARE_RESET:
	हाल MAX98504_WATCHDOG_CLEAR:
	हाल MAX98504_INTERRUPT_FLAG_CLEARS:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल पूर्णांक max98504_pcm_rx_ev(काष्ठा snd_soc_dapm_widget *w,
			      काष्ठा snd_kcontrol *kcontrol, पूर्णांक event)
अणु
	काष्ठा snd_soc_component *c = snd_soc_dapm_to_component(w->dapm);
	काष्ठा max98504_priv *max98504 = snd_soc_component_get_drvdata(c);

	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		regmap_ग_लिखो(max98504->regmap, MAX98504_PCM_RX_ENABLE,
			     max98504->pcm_rx_channels);
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		regmap_ग_लिखो(max98504->regmap, MAX98504_PCM_RX_ENABLE, 0);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max98504_component_probe(काष्ठा snd_soc_component *c)
अणु
	काष्ठा max98504_priv *max98504 = snd_soc_component_get_drvdata(c);
	काष्ठा regmap *map = max98504->regmap;
	पूर्णांक ret;

	ret = regulator_bulk_enable(MAX98504_NUM_SUPPLIES, max98504->supplies);
	अगर (ret < 0)
		वापस ret;

	regmap_ग_लिखो(map, MAX98504_SOFTWARE_RESET, 0x1);
	msleep(20);

	अगर (!max98504->brownout_enable)
		वापस 0;

	regmap_ग_लिखो(map, MAX98504_PVDD_BROWNOUT_ENABLE, 0x1);

	regmap_ग_लिखो(map, MAX98504_PVDD_BROWNOUT_CONFIG_1,
		     (max98504->brownout_threshold & 0x1f) << 3 |
		     (max98504->brownout_attenuation & 0x3));

	regmap_ग_लिखो(map, MAX98504_PVDD_BROWNOUT_CONFIG_2,
		     max98504->brownout_attack_hold & 0xff);

	regmap_ग_लिखो(map, MAX98504_PVDD_BROWNOUT_CONFIG_3,
		     max98504->brownout_समयd_hold & 0xff);

	regmap_ग_लिखो(map, MAX98504_PVDD_BROWNOUT_CONFIG_4,
		     max98504->brownout_release_rate & 0xff);

	वापस 0;
पूर्ण

अटल व्योम max98504_component_हटाओ(काष्ठा snd_soc_component *c)
अणु
	काष्ठा max98504_priv *max98504 = snd_soc_component_get_drvdata(c);

	regulator_bulk_disable(MAX98504_NUM_SUPPLIES, max98504->supplies);
पूर्ण

अटल स्थिर अक्षर *spk_source_mux_text[] = अणु
	"PCM Monomix", "Analog In", "PDM Left", "PDM Right"
पूर्ण;

अटल स्थिर काष्ठा soc_क्रमागत spk_source_mux_क्रमागत =
	SOC_ENUM_SINGLE(MAX98504_SPEAKER_SOURCE_SELECT,
			0, ARRAY_SIZE(spk_source_mux_text),
			spk_source_mux_text);

अटल स्थिर काष्ठा snd_kcontrol_new spk_source_mux =
	SOC_DAPM_ENUM("SPK Source", spk_source_mux_क्रमागत);

अटल स्थिर काष्ठा snd_soc_dapm_route max98504_dapm_routes[] = अणु
	अणु "SPKOUT", शून्य, "Global Enable" पूर्ण,
	अणु "SPK Source", "PCM Monomix", "DAC PCM" पूर्ण,
	अणु "SPK Source", "Analog In", "AIN" पूर्ण,
	अणु "SPK Source", "PDM Left", "DAC PDM" पूर्ण,
	अणु "SPK Source", "PDM Right", "DAC PDM" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget max98504_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SUPPLY("Global Enable", MAX98504_GLOBAL_ENABLE,
		0, 0, शून्य, 0),
	SND_SOC_DAPM_INPUT("AIN"),
	SND_SOC_DAPM_AIF_OUT("AIF2OUTL", "AIF2 Capture", 0, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_AIF_OUT("AIF2OUTR", "AIF2 Capture", 1, SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_DAC_E("DAC PCM", शून्य, SND_SOC_NOPM, 0, 0,
		max98504_pcm_rx_ev,
		SND_SOC_DAPM_POST_PMU | SND_SOC_DAPM_PRE_PMD),
	SND_SOC_DAPM_DAC("DAC PDM", शून्य, MAX98504_PDM_RX_ENABLE, 0, 0),
	SND_SOC_DAPM_MUX("SPK Source", SND_SOC_NOPM, 0, 0, &spk_source_mux),
	SND_SOC_DAPM_REG(snd_soc_dapm_spk, "SPKOUT",
		MAX98504_SPEAKER_ENABLE, 0, 1, 1, 0),
पूर्ण;

अटल पूर्णांक max98504_set_tdm_slot(काष्ठा snd_soc_dai *dai,
		अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask,
		पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा max98504_priv *max98504 = snd_soc_dai_get_drvdata(dai);
	काष्ठा regmap *map = max98504->regmap;


	चयन (dai->id) अणु
	हाल MAX98504_DAI_ID_PCM:
		regmap_ग_लिखो(map, MAX98504_PCM_TX_ENABLE, tx_mask);
		max98504->pcm_rx_channels = rx_mask;
		अवरोध;

	हाल MAX98504_DAI_ID_PDM:
		regmap_ग_लिखो(map, MAX98504_PDM_TX_ENABLE, tx_mask);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	वापस 0;
पूर्ण
अटल पूर्णांक max98504_set_channel_map(काष्ठा snd_soc_dai *dai,
		अचिन्हित पूर्णांक tx_num, अचिन्हित पूर्णांक *tx_slot,
		अचिन्हित पूर्णांक rx_num, अचिन्हित पूर्णांक *rx_slot)
अणु
	काष्ठा max98504_priv *max98504 = snd_soc_dai_get_drvdata(dai);
	काष्ठा regmap *map = max98504->regmap;
	अचिन्हित पूर्णांक i, sources = 0;

	क्रम (i = 0; i < tx_num; i++)
		अगर (tx_slot[i])
			sources |= (1 << i);

	चयन (dai->id) अणु
	हाल MAX98504_DAI_ID_PCM:
		regmap_ग_लिखो(map, MAX98504_PCM_TX_CHANNEL_SOURCES,
			     sources);
		अवरोध;

	हाल MAX98504_DAI_ID_PDM:
		regmap_ग_लिखो(map, MAX98504_PDM_TX_CONTROL, sources);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	regmap_ग_लिखो(map, MAX98504_MEASUREMENT_ENABLE, sources ? 0x3 : 0x01);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops max98504_dai_ops = अणु
	.set_tdm_slot		= max98504_set_tdm_slot,
	.set_channel_map	= max98504_set_channel_map,
पूर्ण;

#घोषणा MAX98504_FORMATS	(SNDRV_PCM_FMTBIT_S8|SNDRV_PCM_FMTBIT_S16_LE|\
				SNDRV_PCM_FMTBIT_S24_LE|SNDRV_PCM_FMTBIT_S32_LE)
#घोषणा MAX98504_PDM_RATES	(SNDRV_PCM_RATE_8000|SNDRV_PCM_RATE_16000|\
				SNDRV_PCM_RATE_32000|SNDRV_PCM_RATE_44100|\
				SNDRV_PCM_RATE_48000|SNDRV_PCM_RATE_88200|\
				SNDRV_PCM_RATE_96000)

अटल काष्ठा snd_soc_dai_driver max98504_dai[] = अणु
	/* TODO: Add the PCM पूर्णांकerface definitions */
	अणु
		.name = "max98504-aif2",
		.id = MAX98504_DAI_ID_PDM,
		.playback = अणु
			.stream_name	= "AIF2 Playback",
			.channels_min	= 1,
			.channels_max	= 2,
			.rates		= MAX98504_PDM_RATES,
			.क्रमmats	= MAX98504_FORMATS,
		पूर्ण,
		.capture = अणु
			.stream_name	= "AIF2 Capture",
			.channels_min	= 1,
			.channels_max	= 2,
			.rates		= MAX98504_PDM_RATES,
			.क्रमmats	= MAX98504_FORMATS,
		पूर्ण,
		.ops = &max98504_dai_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver max98504_component_driver = अणु
	.probe			= max98504_component_probe,
	.हटाओ			= max98504_component_हटाओ,
	.dapm_widमाला_लो		= max98504_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(max98504_dapm_widमाला_लो),
	.dapm_routes		= max98504_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(max98504_dapm_routes),
पूर्ण;

अटल स्थिर काष्ठा regmap_config max98504_regmap = अणु
	.reg_bits		= 16,
	.val_bits		= 8,
	.max_रेजिस्टर		= MAX98504_MAX_REGISTER,
	.reg_शेषs		= max98504_reg_शेषs,
	.num_reg_शेषs	= ARRAY_SIZE(max98504_reg_शेषs),
	.अस्थिर_reg		= max98504_अस्थिर_रेजिस्टर,
	.पढ़ोable_reg		= max98504_पढ़ोable_रेजिस्टर,
	.cache_type		= REGCACHE_RBTREE,
पूर्ण;

अटल पूर्णांक max98504_i2c_probe(काष्ठा i2c_client *client,
			      स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा max98504_priv *max98504;
	पूर्णांक i, ret;

	max98504 = devm_kzalloc(dev, माप(*max98504), GFP_KERNEL);
	अगर (!max98504)
		वापस -ENOMEM;

	अगर (node) अणु
		अगर (!of_property_पढ़ो_u32(node, "maxim,brownout-threshold",
					&max98504->brownout_threshold))
			max98504->brownout_enable = true;

		of_property_पढ़ो_u32(node, "maxim,brownout-attenuation",
					&max98504->brownout_attenuation);
		of_property_पढ़ो_u32(node, "maxim,brownout-attack-hold-ms",
					&max98504->brownout_attack_hold);
		of_property_पढ़ो_u32(node, "maxim,brownout-timed-hold-ms",
					&max98504->brownout_समयd_hold);
		of_property_पढ़ो_u32(node, "maxim,brownout-release-rate-ms",
					&max98504->brownout_release_rate);
	पूर्ण

	max98504->regmap = devm_regmap_init_i2c(client, &max98504_regmap);
	अगर (IS_ERR(max98504->regmap)) अणु
		ret = PTR_ERR(max98504->regmap);
		dev_err(&client->dev, "regmap initialization failed: %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < MAX98504_NUM_SUPPLIES; i++)
		max98504->supplies[i].supply = max98504_supply_names[i];

	ret = devm_regulator_bulk_get(dev, MAX98504_NUM_SUPPLIES,
				      max98504->supplies);
	अगर (ret < 0)
		वापस ret;

	i2c_set_clientdata(client, max98504);

	वापस devm_snd_soc_रेजिस्टर_component(dev, &max98504_component_driver,
				max98504_dai, ARRAY_SIZE(max98504_dai));
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id max98504_of_match[] = अणु
	अणु .compatible = "maxim,max98504" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, max98504_of_match);
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id max98504_i2c_id[] = अणु
	अणु "max98504" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max98504_i2c_id);

अटल काष्ठा i2c_driver max98504_i2c_driver = अणु
	.driver = अणु
		.name = "max98504",
		.of_match_table = of_match_ptr(max98504_of_match),
	पूर्ण,
	.probe = max98504_i2c_probe,
	.id_table = max98504_i2c_id,
पूर्ण;
module_i2c_driver(max98504_i2c_driver);

MODULE_DESCRIPTION("ASoC MAX98504 driver");
MODULE_LICENSE("GPL");
