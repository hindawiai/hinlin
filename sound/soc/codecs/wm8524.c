<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm8524.c  --  WM8524 ALSA SoC Audio driver
 *
 * Copyright 2009 Wolfson Microelectronics plc
 * Copyright 2017 NXP
 *
 * Based on WM8523 ALSA SoC Audio driver written by Mark Brown
 */

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

#घोषणा WM8524_NUM_RATES 7

/* codec निजी data */
काष्ठा wm8524_priv अणु
	काष्ठा gpio_desc *mute;
	अचिन्हित पूर्णांक sysclk;
	अचिन्हित पूर्णांक rate_स्थिरraपूर्णांक_list[WM8524_NUM_RATES];
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list rate_स्थिरraपूर्णांक;
पूर्ण;


अटल स्थिर काष्ठा snd_soc_dapm_widget wm8524_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_DAC("DAC", "Playback", SND_SOC_NOPM, 0, 0),
SND_SOC_DAPM_OUTPUT("LINEVOUTL"),
SND_SOC_DAPM_OUTPUT("LINEVOUTR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm8524_dapm_routes[] = अणु
	अणु "LINEVOUTL", शून्य, "DAC" पूर्ण,
	अणु "LINEVOUTR", शून्य, "DAC" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	पूर्णांक value;
	पूर्णांक ratio;
पूर्ण lrclk_ratios[WM8524_NUM_RATES] = अणु
	अणु 1, 128 पूर्ण,
	अणु 2, 192 पूर्ण,
	अणु 3, 256 पूर्ण,
	अणु 4, 384 पूर्ण,
	अणु 5, 512 पूर्ण,
	अणु 6, 768 पूर्ण,
	अणु 7, 1152 पूर्ण,
पूर्ण;

अटल पूर्णांक wm8524_startup(काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8524_priv *wm8524 = snd_soc_component_get_drvdata(component);

	/* The set of sample rates that can be supported depends on the
	 * MCLK supplied to the CODEC - enक्रमce this.
	 */
	अगर (!wm8524->sysclk) अणु
		dev_err(component->dev,
			"No MCLK configured, call set_sysclk() on init\n");
		वापस -EINVAL;
	पूर्ण

	snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
				   SNDRV_PCM_HW_PARAM_RATE,
				   &wm8524->rate_स्थिरraपूर्णांक);

	gpiod_set_value_cansleep(wm8524->mute, 1);

	वापस 0;
पूर्ण

अटल व्योम wm8524_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा wm8524_priv *wm8524 = snd_soc_component_get_drvdata(component);

	gpiod_set_value_cansleep(wm8524->mute, 0);
पूर्ण

अटल पूर्णांक wm8524_set_dai_sysclk(काष्ठा snd_soc_dai *codec_dai,
		पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा wm8524_priv *wm8524 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val;
	पूर्णांक i, j = 0;

	wm8524->sysclk = freq;

	wm8524->rate_स्थिरraपूर्णांक.count = 0;
	क्रम (i = 0; i < ARRAY_SIZE(lrclk_ratios); i++) अणु
		val = freq / lrclk_ratios[i].ratio;
		/* Check that it's a standard rate since core can't
		 * cope with others and having the odd rates confuses
		 * स्थिरraपूर्णांक matching.
		 */
		चयन (val) अणु
		हाल 8000:
		हाल 32000:
		हाल 44100:
		हाल 48000:
		हाल 88200:
		हाल 96000:
		हाल 176400:
		हाल 192000:
			dev_dbg(component->dev, "Supported sample rate: %dHz\n",
				val);
			wm8524->rate_स्थिरraपूर्णांक_list[j++] = val;
			wm8524->rate_स्थिरraपूर्णांक.count++;
			अवरोध;
		शेष:
			dev_dbg(component->dev, "Skipping sample rate: %dHz\n",
				val);
		पूर्ण
	पूर्ण

	/* Need at least one supported rate... */
	अगर (wm8524->rate_स्थिरraपूर्णांक.count == 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक wm8524_set_fmt(काष्ठा snd_soc_dai *codec_dai, अचिन्हित पूर्णांक fmt)
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

अटल पूर्णांक wm8524_mute_stream(काष्ठा snd_soc_dai *dai, पूर्णांक mute, पूर्णांक stream)
अणु
	काष्ठा wm8524_priv *wm8524 = snd_soc_component_get_drvdata(dai->component);

	अगर (wm8524->mute)
		gpiod_set_value_cansleep(wm8524->mute, mute);

	वापस 0;
पूर्ण

#घोषणा WM8524_RATES SNDRV_PCM_RATE_8000_192000

#घोषणा WM8524_FORMATS (SNDRV_PCM_FMTBIT_S16_LE |\
			SNDRV_PCM_FMTBIT_S24_LE |\
			SNDRV_PCM_FMTBIT_S32_LE)

अटल स्थिर काष्ठा snd_soc_dai_ops wm8524_dai_ops = अणु
	.startup	= wm8524_startup,
	.shutकरोwn	= wm8524_shutकरोwn,
	.set_sysclk	= wm8524_set_dai_sysclk,
	.set_fmt	= wm8524_set_fmt,
	.mute_stream	= wm8524_mute_stream,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver wm8524_dai = अणु
	.name = "wm8524-hifi",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = WM8524_RATES,
		.क्रमmats = WM8524_FORMATS,
	पूर्ण,
	.ops = &wm8524_dai_ops,
पूर्ण;

अटल पूर्णांक wm8524_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm8524_priv *wm8524 = snd_soc_component_get_drvdata(component);

	wm8524->rate_स्थिरraपूर्णांक.list = &wm8524->rate_स्थिरraपूर्णांक_list[0];
	wm8524->rate_स्थिरraपूर्णांक.count =
		ARRAY_SIZE(wm8524->rate_स्थिरraपूर्णांक_list);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm8524 = अणु
	.probe			= wm8524_probe,
	.dapm_widमाला_लो		= wm8524_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm8524_dapm_widमाला_लो),
	.dapm_routes		= wm8524_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm8524_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल स्थिर काष्ठा of_device_id wm8524_of_match[] = अणु
	अणु .compatible = "wlf,wm8524" पूर्ण,
	अणु /* sentinel*/ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wm8524_of_match);

अटल पूर्णांक wm8524_codec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wm8524_priv *wm8524;
	पूर्णांक ret;

	wm8524 = devm_kzalloc(&pdev->dev, माप(काष्ठा wm8524_priv),
						  GFP_KERNEL);
	अगर (wm8524 == शून्य)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, wm8524);

	wm8524->mute = devm_gpiod_get(&pdev->dev, "wlf,mute", GPIOD_OUT_LOW);
	अगर (IS_ERR(wm8524->mute)) अणु
		ret = PTR_ERR(wm8524->mute);
		dev_err_probe(&pdev->dev, ret, "Failed to get mute line\n");
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&soc_component_dev_wm8524, &wm8524_dai, 1);
	अगर (ret < 0)
		dev_err(&pdev->dev, "Failed to register component: %d\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver wm8524_codec_driver = अणु
	.probe		= wm8524_codec_probe,
	.driver		= अणु
		.name	= "wm8524-codec",
		.of_match_table = wm8524_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(wm8524_codec_driver);

MODULE_DESCRIPTION("ASoC WM8524 driver");
MODULE_AUTHOR("Mihai Serban <mihai.serban@nxp.com>");
MODULE_ALIAS("platform:wm8524-codec");
MODULE_LICENSE("GPL");
