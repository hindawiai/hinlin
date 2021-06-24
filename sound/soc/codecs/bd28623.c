<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// ROHM BD28623MUV class D speaker amplअगरier codec driver.
//
// Copyright (c) 2018 Socionext Inc.

#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>

#घोषणा BD28623_NUM_SUPPLIES    3

अटल स्थिर अक्षर *स्थिर bd28623_supply_names[BD28623_NUM_SUPPLIES] = अणु
	"VCCA",
	"VCCP1",
	"VCCP2",
पूर्ण;

काष्ठा bd28623_priv अणु
	काष्ठा device *dev;
	काष्ठा regulator_bulk_data supplies[BD28623_NUM_SUPPLIES];
	काष्ठा gpio_desc *reset_gpio;
	काष्ठा gpio_desc *mute_gpio;

	पूर्णांक चयन_spk;
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget bd28623_widमाला_लो[] = अणु
	SND_SOC_DAPM_DAC("DAC", "Playback", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_OUTPUT("OUT1P"),
	SND_SOC_DAPM_OUTPUT("OUT1N"),
	SND_SOC_DAPM_OUTPUT("OUT2P"),
	SND_SOC_DAPM_OUTPUT("OUT2N"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route bd28623_routes[] = अणु
	अणु "OUT1P", शून्य, "DAC" पूर्ण,
	अणु "OUT1N", शून्य, "DAC" पूर्ण,
	अणु "OUT2P", शून्य, "DAC" पूर्ण,
	अणु "OUT2N", शून्य, "DAC" पूर्ण,
पूर्ण;

अटल पूर्णांक bd28623_घातer_on(काष्ठा bd28623_priv *bd)
अणु
	पूर्णांक ret;

	ret = regulator_bulk_enable(ARRAY_SIZE(bd->supplies), bd->supplies);
	अगर (ret) अणु
		dev_err(bd->dev, "Failed to enable supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	gpiod_set_value_cansleep(bd->reset_gpio, 0);
	usleep_range(300000, 400000);

	वापस 0;
पूर्ण

अटल व्योम bd28623_घातer_off(काष्ठा bd28623_priv *bd)
अणु
	gpiod_set_value_cansleep(bd->reset_gpio, 1);

	regulator_bulk_disable(ARRAY_SIZE(bd->supplies), bd->supplies);
पूर्ण

अटल पूर्णांक bd28623_get_चयन_spk(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा bd28623_priv *bd = snd_soc_component_get_drvdata(component);

	ucontrol->value.पूर्णांकeger.value[0] = bd->चयन_spk;

	वापस 0;
पूर्ण

अटल पूर्णांक bd28623_set_चयन_spk(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component =
		snd_soc_kcontrol_component(kcontrol);
	काष्ठा bd28623_priv *bd = snd_soc_component_get_drvdata(component);

	अगर (bd->चयन_spk == ucontrol->value.पूर्णांकeger.value[0])
		वापस 0;

	bd->चयन_spk = ucontrol->value.पूर्णांकeger.value[0];

	gpiod_set_value_cansleep(bd->mute_gpio, bd->चयन_spk ? 0 : 1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new bd28623_controls[] = अणु
	SOC_SINGLE_BOOL_EXT("Speaker Switch", 0,
			    bd28623_get_चयन_spk, bd28623_set_चयन_spk),
पूर्ण;

अटल पूर्णांक bd28623_codec_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा bd28623_priv *bd = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	bd->चयन_spk = 1;

	ret = bd28623_घातer_on(bd);
	अगर (ret)
		वापस ret;

	gpiod_set_value_cansleep(bd->mute_gpio, bd->चयन_spk ? 0 : 1);

	वापस 0;
पूर्ण

अटल व्योम bd28623_codec_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा bd28623_priv *bd = snd_soc_component_get_drvdata(component);

	bd28623_घातer_off(bd);
पूर्ण

अटल पूर्णांक bd28623_codec_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा bd28623_priv *bd = snd_soc_component_get_drvdata(component);

	bd28623_घातer_off(bd);

	वापस 0;
पूर्ण

अटल पूर्णांक bd28623_codec_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा bd28623_priv *bd = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = bd28623_घातer_on(bd);
	अगर (ret)
		वापस ret;

	gpiod_set_value_cansleep(bd->mute_gpio, bd->चयन_spk ? 0 : 1);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_codec_bd = अणु
	.probe			= bd28623_codec_probe,
	.हटाओ			= bd28623_codec_हटाओ,
	.suspend		= bd28623_codec_suspend,
	.resume			= bd28623_codec_resume,
	.dapm_widमाला_लो		= bd28623_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(bd28623_widमाला_लो),
	.dapm_routes		= bd28623_routes,
	.num_dapm_routes	= ARRAY_SIZE(bd28623_routes),
	.controls		= bd28623_controls,
	.num_controls		= ARRAY_SIZE(bd28623_controls),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver soc_dai_bd = अणु
	.name     = "bd28623-speaker",
	.playback = अणु
		.stream_name  = "Playback",
		.क्रमmats      = SNDRV_PCM_FMTBIT_S32_LE |
				SNDRV_PCM_FMTBIT_S24_LE |
				SNDRV_PCM_FMTBIT_S16_LE,
		.rates        = SNDRV_PCM_RATE_48000 |
				SNDRV_PCM_RATE_44100 |
				SNDRV_PCM_RATE_32000,
		.channels_min = 2,
		.channels_max = 2,
	पूर्ण,
पूर्ण;

अटल पूर्णांक bd28623_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bd28623_priv *bd;
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक i, ret;

	bd = devm_kzalloc(&pdev->dev, माप(काष्ठा bd28623_priv), GFP_KERNEL);
	अगर (!bd)
		वापस -ENOMEM;

	क्रम (i = 0; i < ARRAY_SIZE(bd->supplies); i++)
		bd->supplies[i].supply = bd28623_supply_names[i];

	ret = devm_regulator_bulk_get(dev, ARRAY_SIZE(bd->supplies),
				      bd->supplies);
	अगर (ret) अणु
		dev_err(dev, "Failed to get supplies: %d\n", ret);
		वापस ret;
	पूर्ण

	bd->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						 GPIOD_OUT_HIGH);
	अगर (IS_ERR(bd->reset_gpio)) अणु
		dev_err(dev, "Failed to request reset_gpio: %ld\n",
			PTR_ERR(bd->reset_gpio));
		वापस PTR_ERR(bd->reset_gpio);
	पूर्ण

	bd->mute_gpio = devm_gpiod_get_optional(dev, "mute",
						GPIOD_OUT_HIGH);
	अगर (IS_ERR(bd->mute_gpio)) अणु
		dev_err(dev, "Failed to request mute_gpio: %ld\n",
			PTR_ERR(bd->mute_gpio));
		वापस PTR_ERR(bd->mute_gpio);
	पूर्ण

	platक्रमm_set_drvdata(pdev, bd);
	bd->dev = dev;

	वापस devm_snd_soc_रेजिस्टर_component(dev, &soc_codec_bd,
					       &soc_dai_bd, 1);
पूर्ण

अटल स्थिर काष्ठा of_device_id bd28623_of_match[] __maybe_unused = अणु
	अणु .compatible = "rohm,bd28623", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, bd28623_of_match);

अटल काष्ठा platक्रमm_driver bd28623_codec_driver = अणु
	.driver = अणु
		.name = "bd28623",
		.of_match_table = of_match_ptr(bd28623_of_match),
	पूर्ण,
	.probe  = bd28623_probe,
पूर्ण;
module_platक्रमm_driver(bd28623_codec_driver);

MODULE_AUTHOR("Katsuhiro Suzuki <suzuki.katsuhiro@socionext.com>");
MODULE_DESCRIPTION("ROHM BD28623 speaker amplifier driver");
MODULE_LICENSE("GPL v2");
