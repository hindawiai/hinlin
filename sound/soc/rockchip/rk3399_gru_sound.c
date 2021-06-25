<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Rockchip machine ASoC driver क्रम boards using MAX98357A/RT5514/DA7219
 *
 * Copyright (c) 2016, ROCKCHIP CORPORATION.  All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/input.h>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश "rockchip_i2s.h"
#समावेश "../codecs/da7219.h"
#समावेश "../codecs/da7219-aad.h"
#समावेश "../codecs/rt5514.h"

#घोषणा DRV_NAME "rk3399-gru-sound"

#घोषणा SOUND_FS	256

अटल अचिन्हित पूर्णांक dmic_wakeup_delay;

अटल काष्ठा snd_soc_jack rockchip_sound_jack;

/* Headset jack detection DAPM pins */
अटल काष्ठा snd_soc_jack_pin rockchip_sound_jack_pins[] = अणु
	अणु
		.pin = "Headphones",
		.mask = SND_JACK_HEADPHONE,
	पूर्ण,
	अणु
		.pin = "Headset Mic",
		.mask = SND_JACK_MICROPHONE,
	पूर्ण,

पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget rockchip_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphones", शून्य),
	SND_SOC_DAPM_SPK("Speakers", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Int Mic", शून्य),
	SND_SOC_DAPM_LINE("HDMI", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rockchip_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphones"),
	SOC_DAPM_PIN_SWITCH("Speakers"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Int Mic"),
	SOC_DAPM_PIN_SWITCH("HDMI"),
पूर्ण;

अटल पूर्णांक rockchip_sound_max98357a_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	अचिन्हित पूर्णांक mclk;
	पूर्णांक ret;

	mclk = params_rate(params) * SOUND_FS;

	ret = snd_soc_dai_set_sysclk(asoc_rtd_to_cpu(rtd, 0), 0, mclk, 0);
	अगर (ret) अणु
		dev_err(rtd->card->dev, "%s() error setting sysclk to %u: %d\n",
				__func__, mclk, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_sound_rt5514_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	अचिन्हित पूर्णांक mclk;
	पूर्णांक ret;

	mclk = params_rate(params) * SOUND_FS;

	ret = snd_soc_dai_set_sysclk(cpu_dai, 0, mclk,
				     SND_SOC_CLOCK_OUT);
	अगर (ret < 0) अणु
		dev_err(rtd->card->dev, "Can't set cpu clock out %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(codec_dai, RT5514_SCLK_S_MCLK,
				     mclk, SND_SOC_CLOCK_IN);
	अगर (ret) अणु
		dev_err(rtd->card->dev, "%s() error setting sysclk to %u: %d\n",
				__func__, params_rate(params) * 512, ret);
		वापस ret;
	पूर्ण

	/* Wait क्रम DMIC stable */
	msleep(dmic_wakeup_delay);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_sound_da7219_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक mclk, ret;

	/* in bypass mode, the mclk has to be one of the frequencies below */
	चयन (params_rate(params)) अणु
	हाल 8000:
	हाल 16000:
	हाल 24000:
	हाल 32000:
	हाल 48000:
	हाल 64000:
	हाल 96000:
		mclk = 12288000;
		अवरोध;
	हाल 11025:
	हाल 22050:
	हाल 44100:
	हाल 88200:
		mclk = 11289600;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(cpu_dai, 0, mclk,
				     SND_SOC_CLOCK_OUT);
	अगर (ret < 0) अणु
		dev_err(codec_dai->dev, "Can't set cpu clock out %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(codec_dai, 0, mclk,
				     SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(codec_dai->dev, "Can't set codec clock in %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_pll(codec_dai, 0, DA7219_SYSCLK_MCLK, 0, 0);
	अगर (ret < 0) अणु
		dev_err(codec_dai->dev, "Can't set pll sysclk mclk %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_sound_da7219_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	/* We need शेष MCLK and PLL settings क्रम the accessory detection */
	ret = snd_soc_dai_set_sysclk(codec_dai, 0, 12288000,
				     SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(codec_dai->dev, "Init can't set codec clock in %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_pll(codec_dai, 0, DA7219_SYSCLK_MCLK, 0, 0);
	अगर (ret < 0) अणु
		dev_err(codec_dai->dev, "Init can't set pll sysclk mclk %d\n", ret);
		वापस ret;
	पूर्ण

	/* Enable Headset and 4 Buttons Jack detection */
	ret = snd_soc_card_jack_new(rtd->card, "Headset Jack",
				    SND_JACK_HEADSET | SND_JACK_LINEOUT |
				    SND_JACK_BTN_0 | SND_JACK_BTN_1 |
				    SND_JACK_BTN_2 | SND_JACK_BTN_3,
				    &rockchip_sound_jack,
				    rockchip_sound_jack_pins,
				    ARRAY_SIZE(rockchip_sound_jack_pins));

	अगर (ret) अणु
		dev_err(rtd->card->dev, "New Headset Jack failed! (%d)\n", ret);
		वापस ret;
	पूर्ण

	snd_jack_set_key(
		rockchip_sound_jack.jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_jack_set_key(
		rockchip_sound_jack.jack, SND_JACK_BTN_1, KEY_VOLUMEUP);
	snd_jack_set_key(
		rockchip_sound_jack.jack, SND_JACK_BTN_2, KEY_VOLUMEDOWN);
	snd_jack_set_key(
		rockchip_sound_jack.jack, SND_JACK_BTN_3, KEY_VOICECOMMAND);

	da7219_aad_jack_det(component, &rockchip_sound_jack);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_sound_dmic_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	अचिन्हित पूर्णांक mclk;
	पूर्णांक ret;

	mclk = params_rate(params) * SOUND_FS;

	ret = snd_soc_dai_set_sysclk(asoc_rtd_to_cpu(rtd, 0), 0, mclk, 0);
	अगर (ret) अणु
		dev_err(rtd->card->dev, "%s() error setting sysclk to %u: %d\n",
				__func__, mclk, ret);
		वापस ret;
	पूर्ण

	/* Wait क्रम DMIC stable */
	msleep(dmic_wakeup_delay);

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_sound_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE;
	वापस snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_RATE,
			8000, 96000);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops rockchip_sound_max98357a_ops = अणु
	.startup = rockchip_sound_startup,
	.hw_params = rockchip_sound_max98357a_hw_params,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops rockchip_sound_rt5514_ops = अणु
	.startup = rockchip_sound_startup,
	.hw_params = rockchip_sound_rt5514_hw_params,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops rockchip_sound_da7219_ops = अणु
	.startup = rockchip_sound_startup,
	.hw_params = rockchip_sound_da7219_hw_params,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops rockchip_sound_dmic_ops = अणु
	.startup = rockchip_sound_startup,
	.hw_params = rockchip_sound_dmic_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_card rockchip_sound_card = अणु
	.name = "rk3399-gru-sound",
	.owner = THIS_MODULE,
	.dapm_widमाला_लो = rockchip_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(rockchip_dapm_widमाला_लो),
	.controls = rockchip_controls,
	.num_controls = ARRAY_SIZE(rockchip_controls),
पूर्ण;

क्रमागत अणु
	DAILINK_CDNDP,
	DAILINK_DA7219,
	DAILINK_DMIC,
	DAILINK_MAX98357A,
	DAILINK_RT5514,
	DAILINK_RT5514_DSP,
पूर्ण;

SND_SOC_DAILINK_DEFS(cdndp,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "spdif-hifi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(da7219,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "da7219-hifi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(dmic,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "dmic-hifi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(max98357a,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "HiFi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(rt5514,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "rt5514-aif1")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(rt5514_dsp,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल स्थिर काष्ठा snd_soc_dai_link rockchip_dais[] = अणु
	[DAILINK_CDNDP] = अणु
		.name = "DP",
		.stream_name = "DP PCM",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		SND_SOC_DAILINK_REG(cdndp),
	पूर्ण,
	[DAILINK_DA7219] = अणु
		.name = "DA7219",
		.stream_name = "DA7219 PCM",
		.init = rockchip_sound_da7219_init,
		.ops = &rockchip_sound_da7219_ops,
		/* set da7219 as slave */
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		SND_SOC_DAILINK_REG(da7219),
	पूर्ण,
	[DAILINK_DMIC] = अणु
		.name = "DMIC",
		.stream_name = "DMIC PCM",
		.ops = &rockchip_sound_dmic_ops,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		SND_SOC_DAILINK_REG(dmic),
	पूर्ण,
	[DAILINK_MAX98357A] = अणु
		.name = "MAX98357A",
		.stream_name = "MAX98357A PCM",
		.ops = &rockchip_sound_max98357a_ops,
		/* set max98357a as slave */
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		SND_SOC_DAILINK_REG(max98357a),
	पूर्ण,
	[DAILINK_RT5514] = अणु
		.name = "RT5514",
		.stream_name = "RT5514 PCM",
		.ops = &rockchip_sound_rt5514_ops,
		/* set rt5514 as slave */
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		SND_SOC_DAILINK_REG(rt5514),
	पूर्ण,
	/* RT5514 DSP क्रम voice wakeup via spi bus */
	[DAILINK_RT5514_DSP] = अणु
		.name = "RT5514 DSP",
		.stream_name = "Wake on Voice",
		SND_SOC_DAILINK_REG(rt5514_dsp),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rockchip_sound_cdndp_routes[] = अणु
	/* Output */
	अणु"HDMI", शून्य, "TX"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rockchip_sound_da7219_routes[] = अणु
	/* Output */
	अणु"Headphones", शून्य, "HPL"पूर्ण,
	अणु"Headphones", शून्य, "HPR"पूर्ण,

	/* Input */
	अणु"MIC", शून्य, "Headset Mic"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rockchip_sound_dmic_routes[] = अणु
	/* Input */
	अणु"DMic", शून्य, "Int Mic"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rockchip_sound_max98357a_routes[] = अणु
	/* Output */
	अणु"Speakers", शून्य, "Speaker"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rockchip_sound_rt5514_routes[] = अणु
	/* Input */
	अणु"DMIC1L", शून्य, "Int Mic"पूर्ण,
	अणु"DMIC1R", शून्य, "Int Mic"पूर्ण,
पूर्ण;

काष्ठा rockchip_sound_route अणु
	स्थिर काष्ठा snd_soc_dapm_route *routes;
	पूर्णांक num_routes;
पूर्ण;

अटल स्थिर काष्ठा rockchip_sound_route rockchip_routes[] = अणु
	[DAILINK_CDNDP] = अणु
		.routes = rockchip_sound_cdndp_routes,
		.num_routes = ARRAY_SIZE(rockchip_sound_cdndp_routes),
	पूर्ण,
	[DAILINK_DA7219] = अणु
		.routes = rockchip_sound_da7219_routes,
		.num_routes = ARRAY_SIZE(rockchip_sound_da7219_routes),
	पूर्ण,
	[DAILINK_DMIC] = अणु
		.routes = rockchip_sound_dmic_routes,
		.num_routes = ARRAY_SIZE(rockchip_sound_dmic_routes),
	पूर्ण,
	[DAILINK_MAX98357A] = अणु
		.routes = rockchip_sound_max98357a_routes,
		.num_routes = ARRAY_SIZE(rockchip_sound_max98357a_routes),
	पूर्ण,
	[DAILINK_RT5514] = अणु
		.routes = rockchip_sound_rt5514_routes,
		.num_routes = ARRAY_SIZE(rockchip_sound_rt5514_routes),
	पूर्ण,
	[DAILINK_RT5514_DSP] = अणुपूर्ण,
पूर्ण;

काष्ठा dailink_match_data अणु
	स्थिर अक्षर *compatible;
	काष्ठा bus_type *bus_type;
पूर्ण;

अटल स्थिर काष्ठा dailink_match_data dailink_match[] = अणु
	[DAILINK_CDNDP] = अणु
		.compatible = "rockchip,rk3399-cdn-dp",
	पूर्ण,
	[DAILINK_DA7219] = अणु
		.compatible = "dlg,da7219",
	पूर्ण,
	[DAILINK_DMIC] = अणु
		.compatible = "dmic-codec",
	पूर्ण,
	[DAILINK_MAX98357A] = अणु
		.compatible = "maxim,max98357a",
	पूर्ण,
	[DAILINK_RT5514] = अणु
		.compatible = "realtek,rt5514",
		.bus_type = &i2c_bus_type,
	पूर्ण,
	[DAILINK_RT5514_DSP] = अणु
		.compatible = "realtek,rt5514",
		.bus_type = &spi_bus_type,
	पूर्ण,
पूर्ण;

अटल पूर्णांक rockchip_sound_codec_node_match(काष्ठा device_node *np_codec)
अणु
	काष्ठा device *dev;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dailink_match); i++) अणु
		अगर (!of_device_is_compatible(np_codec,
					     dailink_match[i].compatible))
			जारी;

		अगर (dailink_match[i].bus_type) अणु
			dev = bus_find_device_by_of_node(dailink_match[i].bus_type,
							 np_codec);
			अगर (!dev)
				जारी;
			put_device(dev);
		पूर्ण

		वापस i;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक rockchip_sound_of_parse_dais(काष्ठा device *dev,
					काष्ठा snd_soc_card *card)
अणु
	काष्ठा device_node *np_cpu, *np_cpu0, *np_cpu1;
	काष्ठा device_node *np_codec;
	काष्ठा snd_soc_dai_link *dai;
	काष्ठा snd_soc_dapm_route *routes;
	पूर्णांक i, index;
	पूर्णांक num_routes;

	card->dai_link = devm_kzalloc(dev, माप(rockchip_dais),
				      GFP_KERNEL);
	अगर (!card->dai_link)
		वापस -ENOMEM;

	num_routes = 0;
	क्रम (i = 0; i < ARRAY_SIZE(rockchip_routes); i++)
		num_routes += rockchip_routes[i].num_routes;
	routes = devm_kसुस्मृति(dev, num_routes, माप(*routes),
			      GFP_KERNEL);
	अगर (!routes)
		वापस -ENOMEM;
	card->dapm_routes = routes;

	np_cpu0 = of_parse_phandle(dev->of_node, "rockchip,cpu", 0);
	np_cpu1 = of_parse_phandle(dev->of_node, "rockchip,cpu", 1);

	card->num_dapm_routes = 0;
	card->num_links = 0;
	क्रम (i = 0; i < ARRAY_SIZE(rockchip_dais); i++) अणु
		np_codec = of_parse_phandle(dev->of_node,
					    "rockchip,codec", i);
		अगर (!np_codec)
			अवरोध;

		अगर (!of_device_is_available(np_codec))
			जारी;

		index = rockchip_sound_codec_node_match(np_codec);
		अगर (index < 0)
			जारी;

		चयन (index) अणु
		हाल DAILINK_CDNDP:
			np_cpu = np_cpu1;
			अवरोध;
		हाल DAILINK_RT5514_DSP:
			np_cpu = np_codec;
			अवरोध;
		शेष:
			np_cpu = np_cpu0;
			अवरोध;
		पूर्ण

		अगर (!np_cpu) अणु
			dev_err(dev, "Missing 'rockchip,cpu' for %s\n",
				rockchip_dais[index].name);
			वापस -EINVAL;
		पूर्ण

		dai = &card->dai_link[card->num_links++];
		*dai = rockchip_dais[index];

		अगर (!dai->codecs->name)
			dai->codecs->of_node = np_codec;
		dai->platक्रमms->of_node = np_cpu;
		dai->cpus->of_node = np_cpu;

		अगर (card->num_dapm_routes + rockchip_routes[index].num_routes >
		    num_routes) अणु
			dev_err(dev, "Too many routes\n");
			वापस -EINVAL;
		पूर्ण

		स_नकल(routes + card->num_dapm_routes,
		       rockchip_routes[index].routes,
		       rockchip_routes[index].num_routes * माप(*routes));
		card->num_dapm_routes += rockchip_routes[index].num_routes;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक rockchip_sound_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &rockchip_sound_card;
	पूर्णांक ret;

	ret = rockchip_sound_of_parse_dais(&pdev->dev, card);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "Failed to parse dais: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Set DMIC wakeup delay */
	ret = device_property_पढ़ो_u32(&pdev->dev, "dmic-wakeup-delay-ms",
					&dmic_wakeup_delay);
	अगर (ret) अणु
		dmic_wakeup_delay = 0;
		dev_dbg(&pdev->dev,
			"no optional property 'dmic-wakeup-delay-ms' found, default: no delay\n");
	पूर्ण

	card->dev = &pdev->dev;
	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
पूर्ण

अटल स्थिर काष्ठा of_device_id rockchip_sound_of_match[] = अणु
	अणु .compatible = "rockchip,rk3399-gru-sound", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver rockchip_sound_driver = अणु
	.probe = rockchip_sound_probe,
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = rockchip_sound_of_match,
#अगर_घोषित CONFIG_PM
		.pm = &snd_soc_pm_ops,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(rockchip_sound_driver);

MODULE_AUTHOR("Xing Zheng <zhengxing@rock-chips.com>");
MODULE_DESCRIPTION("Rockchip ASoC Machine Driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
MODULE_DEVICE_TABLE(of, rockchip_sound_of_match);
