<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// uda1334.c  --  UDA1334 ALSA SoC Audio driver
//
// Based on WM8523 ALSA SoC Audio driver written by Mark Brown

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/of_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>

#घोषणा UDA1334_NUM_RATES 6

/* codec निजी data */
काष्ठा uda1334_priv अणु
	काष्ठा gpio_desc *mute;
	काष्ठा gpio_desc *deemph;
	अचिन्हित पूर्णांक sysclk;
	अचिन्हित पूर्णांक rate_स्थिरraपूर्णांक_list[UDA1334_NUM_RATES];
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list rate_स्थिरraपूर्णांक;
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget uda1334_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_DAC("DAC", "Playback", SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_OUTPUT("LINEVOUTL"),
SND_SOC_DAPM_OUTPUT("LINEVOUTR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route uda1334_dapm_routes[] = अणु
	अणु "LINEVOUTL", शून्य, "DAC" पूर्ण,
	अणु "LINEVOUTR", शून्य, "DAC" पूर्ण,
पूर्ण;

अटल पूर्णांक uda1334_put_deemph(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा uda1334_priv *uda1334 = snd_soc_component_get_drvdata(component);
	पूर्णांक deemph = ucontrol->value.पूर्णांकeger.value[0];

	अगर (deemph > 1)
		वापस -EINVAL;

	gpiod_set_value_cansleep(uda1334->deemph, deemph);

	वापस 0;
पूर्ण;

अटल पूर्णांक uda1334_get_deemph(काष्ठा snd_kcontrol *kcontrol,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_component *component = snd_soc_kcontrol_component(kcontrol);
	काष्ठा uda1334_priv *uda1334 = snd_soc_component_get_drvdata(component);
	पूर्णांक ret;

	ret = gpiod_get_value_cansleep(uda1334->deemph);
	अगर (ret < 0)
		वापस -EINVAL;

	ucontrol->value.पूर्णांकeger.value[0] = ret;

	वापस 0;
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new uda1334_snd_controls[] = अणु
	SOC_SINGLE_BOOL_EXT("Playback Deemphasis Switch", 0,
			    uda1334_get_deemph, uda1334_put_deemph),
पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक value;
	पूर्णांक ratio;
पूर्ण lrclk_ratios[UDA1334_NUM_RATES] = अणु
	अणु 1, 128 पूर्ण,
	अणु 2, 192 पूर्ण,
	अणु 3, 256 पूर्ण,
	अणु 4, 384 पूर्ण,
	अणु 5, 512 पूर्ण,
	अणु 6, 768 पूर्ण,
पूर्ण;

अटल पूर्णांक uda1334_startup(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा uda1334_priv *uda1334 = snd_soc_component_get_drvdata(component);

	/*
	 * The set of sample rates that can be supported depends on the
	 * MCLK supplied to the CODEC - enक्रमce this.
	 */
	अगर (!uda1334->sysclk) अणु
		dev_err(component->dev,
			"No MCLK configured, call set_sysclk() on init\n");
		वापस -EINVAL;
	पूर्ण

	snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
				   SNDRV_PCM_HW_PARAM_RATE,
				   &uda1334->rate_स्थिरraपूर्णांक);

	gpiod_set_value_cansleep(uda1334->mute, 1);

	वापस 0;
पूर्ण

अटल व्योम uda1334_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा uda1334_priv *uda1334 = snd_soc_component_get_drvdata(component);

	gpiod_set_value_cansleep(uda1334->mute, 0);
पूर्ण

अटल पूर्णांक uda1334_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
				  पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा uda1334_priv *uda1334 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val;
	पूर्णांक i, j = 0;

	uda1334->sysclk = freq;

	uda1334->rate_स्थिरraपूर्णांक.count = 0;
	क्रम (i = 0; i < ARRAY_SIZE(lrclk_ratios); i++) अणु
		val = freq / lrclk_ratios[i].ratio;
		/*
		 * Check that it's a standard rate since core can't
		 * cope with others and having the odd rates confuses
		 * स्थिरraपूर्णांक matching.
		 */

		चयन (val) अणु
		हाल 8000:
		हाल 32000:
		हाल 44100:
		हाल 48000:
		हाल 64000:
		हाल 88200:
		हाल 96000:
			dev_dbg(component->dev, "Supported sample rate: %dHz\n",
				val);
			uda1334->rate_स्थिरraपूर्णांक_list[j++] = val;
			uda1334->rate_स्थिरraपूर्णांक.count++;
			अवरोध;
		शेष:
			dev_dbg(component->dev, "Skipping sample rate: %dHz\n",
				val);
		पूर्ण
	पूर्ण

	/* Need at least one supported rate... */
	अगर (uda1334->rate_स्थिरraपूर्णांक.count == 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक uda1334_set_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
अणु
	fmt &= (SND_SOC_DAIFMT_FORMAT_MASK | SND_SOC_DAIFMT_INV_MASK |
		SND_SOC_DAIFMT_MASTER_MASK);

	अगर (fmt != (SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
		    SND_SOC_DAIFMT_CBS_CFS)) अणु
		dev_err(codec_dai->dev, "Invalid DAI format\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक uda1334_mute_stream(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक stream)
अणु
	काष्ठा uda1334_priv *uda1334 = snd_soc_component_get_drvdata(dai->component);

	अगर (uda1334->mute)
		gpiod_set_value_cansleep(uda1334->mute, mute);

	वापस 0;
पूर्ण

#घोषणा UDA1334_RATES SNDRV_PCM_RATE_8000_96000

#घोषणा UDA1334_FORMATS (SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops uda1334_dai_ops = अणु
	.startup	= uda1334_startup,
	.shutकरोwn	= uda1334_shutकरोwn,
	.set_sysclk	= uda1334_set_dai_sysclk,
	.set_fmt	= uda1334_set_fmt,
	.mute_stream	= uda1334_mute_stream,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver uda1334_dai = अणु
	.name = "uda1334-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = UDA1334_RATES,
		.क्रमmats = UDA1334_FORMATS,
	पूर्ण,
	.ops = &uda1334_dai_ops,
पूर्ण;

अटल पूर्णांक uda1334_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा uda1334_priv *uda1334 = snd_soc_component_get_drvdata(component);

	uda1334->rate_स्थिरraपूर्णांक.list = &uda1334->rate_स्थिरraपूर्णांक_list[0];
	uda1334->rate_स्थिरraपूर्णांक.count =
		ARRAY_SIZE(uda1334->rate_स्थिरraपूर्णांक_list);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_uda1334 = अणु
	.probe			= uda1334_probe,
	.controls		= uda1334_snd_controls,
	.num_controls		= ARRAY_SIZE(uda1334_snd_controls),
	.dapm_widमाला_लो		= uda1334_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(uda1334_dapm_widमाला_लो),
	.dapm_routes		= uda1334_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(uda1334_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id uda1334_of_match[] = अणु
	अणु .compatible = "nxp,uda1334" पूर्ण,
	अणु /* sentinel*/ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, uda1334_of_match);

अटल पूर्णांक uda1334_codec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uda1334_priv *uda1334;
	पूर्णांक ret;

	uda1334 = devm_kzalloc(&pdev->dev, माप(काष्ठा uda1334_priv),
			       GFP_KERNEL);
	अगर (!uda1334)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, uda1334);

	uda1334->mute = devm_gpiod_get(&pdev->dev, "nxp,mute", GPIOD_OUT_LOW);
	अगर (IS_ERR(uda1334->mute)) अणु
		ret = PTR_ERR(uda1334->mute);
		dev_err(&pdev->dev, "Failed to get mute line: %d\n", ret);
		वापस ret;
	पूर्ण

	uda1334->deemph = devm_gpiod_get(&pdev->dev, "nxp,deemph", GPIOD_OUT_LOW);
	अगर (IS_ERR(uda1334->deemph)) अणु
		ret = PTR_ERR(uda1334->deemph);
		dev_err(&pdev->dev, "Failed to get deemph line: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &soc_component_dev_uda1334,
					      &uda1334_dai, 1);
	अगर (ret < 0)
		dev_err(&pdev->dev, "Failed to register component: %d\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver uda1334_codec_driver = अणु
	.probe		= uda1334_codec_probe,
	.driver		= अणु
		.name	= "uda1334-codec",
		.of_match_table = uda1334_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(uda1334_codec_driver);

MODULE_DESCRIPTION("ASoC UDA1334 driver");
MODULE_AUTHOR("Andra Danciu <andradanciu1997@gmail.com>");
MODULE_ALIAS("platform:uda1334-codec");
MODULE_LICENSE("GPL v2");
