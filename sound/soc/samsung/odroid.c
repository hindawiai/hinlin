<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2017 Samsung Electronics Co., Ltd.

#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/module.h>
#समावेश <sound/soc.h>
#समावेश <sound/pcm_params.h>
#समावेश "i2s.h"
#समावेश "i2s-regs.h"

काष्ठा odroid_priv अणु
	काष्ठा snd_soc_card card;
	काष्ठा clk *clk_i2s_bus;
	काष्ठा clk *sclk_i2s;

	/* Spinlock protecting fields below */
	spinlock_t lock;
	अचिन्हित पूर्णांक be_sample_rate;
	bool be_active;
पूर्ण;

अटल पूर्णांक odroid_card_fe_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	snd_pcm_hw_स्थिरraपूर्णांक_single(runसमय, SNDRV_PCM_HW_PARAM_CHANNELS, 2);

	वापस 0;
पूर्ण

अटल पूर्णांक odroid_card_fe_hw_params(काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा odroid_priv *priv = snd_soc_card_get_drvdata(rtd->card);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	spin_lock_irqsave(&priv->lock, flags);
	अगर (priv->be_active && priv->be_sample_rate != params_rate(params))
		ret = -EINVAL;
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops odroid_card_fe_ops = अणु
	.startup = odroid_card_fe_startup,
	.hw_params = odroid_card_fe_hw_params,
पूर्ण;

अटल पूर्णांक odroid_card_be_hw_params(काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा odroid_priv *priv = snd_soc_card_get_drvdata(rtd->card);
	अचिन्हित पूर्णांक pll_freq, rclk_freq, rfs;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	चयन (params_rate(params)) अणु
	हाल 64000:
		pll_freq = 196608001U;
		rfs = 384;
		अवरोध;
	हाल 44100:
	हाल 88200:
		pll_freq = 180633609U;
		rfs = 512;
		अवरोध;
	हाल 32000:
	हाल 48000:
	हाल 96000:
		pll_freq = 196608001U;
		rfs = 512;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = clk_set_rate(priv->clk_i2s_bus, pll_freq / 2 + 1);
	अगर (ret < 0)
		वापस ret;

	/*
	 *  We add 2 to the rclk_freq value in order to aव्योम too low घड़ी
	 *  frequency values due to the EPLL output frequency not being exact
	 *  multiple of the audio sampling rate.
	 */
	rclk_freq = params_rate(params) * rfs + 2;

	ret = clk_set_rate(priv->sclk_i2s, rclk_freq);
	अगर (ret < 0)
		वापस ret;

	अगर (rtd->num_codecs > 1) अणु
		काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 1);

		ret = snd_soc_dai_set_sysclk(codec_dai, 0, rclk_freq,
					     SND_SOC_CLOCK_IN);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	spin_lock_irqsave(&priv->lock, flags);
	priv->be_sample_rate = params_rate(params);
	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक odroid_card_be_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा odroid_priv *priv = snd_soc_card_get_drvdata(rtd->card);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&priv->lock, flags);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		priv->be_active = true;
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		priv->be_active = false;
		अवरोध;
	पूर्ण

	spin_unlock_irqrestore(&priv->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops odroid_card_be_ops = अणु
	.hw_params = odroid_card_be_hw_params,
	.trigger = odroid_card_be_trigger,
पूर्ण;

/* DAPM routes क्रम backward compatibility with old DTS */
अटल स्थिर काष्ठा snd_soc_dapm_route odroid_dapm_routes[] = अणु
	अणु "I2S Playback", शून्य, "Mixer DAI TX" पूर्ण,
	अणु "HiFi Playback", शून्य, "Mixer DAI TX" पूर्ण,
पूर्ण;

SND_SOC_DAILINK_DEFS(primary,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("3830000.i2s")));

SND_SOC_DAILINK_DEFS(mixer,
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_DUMMY()));

SND_SOC_DAILINK_DEFS(secondary,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("3830000.i2s-sec")));

अटल काष्ठा snd_soc_dai_link odroid_card_dais[] = अणु
	अणु
		/* Primary FE <-> BE link */
		.ops = &odroid_card_fe_ops,
		.name = "Primary",
		.stream_name = "Primary",
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(primary),
	पूर्ण, अणु
		/* BE <-> CODECs link */
		.name = "I2S Mixer",
		.ops = &odroid_card_be_ops,
		.no_pcm = 1,
		.dpcm_playback = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
				SND_SOC_DAIFMT_CBS_CFS,
		SND_SOC_DAILINK_REG(mixer),
	पूर्ण, अणु
		/* Secondary FE <-> BE link */
		.playback_only = 1,
		.ops = &odroid_card_fe_ops,
		.name = "Secondary",
		.stream_name = "Secondary",
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(secondary),
	पूर्ण
पूर्ण;

अटल पूर्णांक odroid_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *cpu_dai = शून्य;
	काष्ठा device_node *cpu, *codec;
	काष्ठा odroid_priv *priv;
	काष्ठा snd_soc_card *card;
	काष्ठा snd_soc_dai_link *link, *codec_link;
	पूर्णांक num_pcms, ret, i;
	काष्ठा of_phandle_args args = अणुपूर्ण;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	card = &priv->card;
	card->dev = dev;

	card->owner = THIS_MODULE;
	card->fully_routed = true;

	spin_lock_init(&priv->lock);
	snd_soc_card_set_drvdata(card, priv);

	ret = snd_soc_of_parse_card_name(card, "model");
	अगर (ret < 0)
		वापस ret;

	अगर (of_property_पढ़ो_bool(dev->of_node, "samsung,audio-widgets")) अणु
		ret = snd_soc_of_parse_audio_simple_widमाला_लो(card,
						"samsung,audio-widgets");
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (of_property_पढ़ो_bool(dev->of_node, "samsung,audio-routing")) अणु
		ret = snd_soc_of_parse_audio_routing(card,
						"samsung,audio-routing");
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	card->dai_link = odroid_card_dais;
	card->num_links = ARRAY_SIZE(odroid_card_dais);

	cpu = of_get_child_by_name(dev->of_node, "cpu");
	codec = of_get_child_by_name(dev->of_node, "codec");
	link = card->dai_link;
	codec_link = &card->dai_link[1];

	/*
	 * For backwards compatibility create the secondary CPU DAI link only
	 * अगर there are 2 CPU DAI entries in the cpu sound-dai property in DT.
	 * Also add required DAPM routes not available in old DTS.
	 */
	num_pcms = of_count_phandle_with_args(cpu, "sound-dai",
					      "#sound-dai-cells");
	अगर (num_pcms == 1) अणु
		card->dapm_routes = odroid_dapm_routes;
		card->num_dapm_routes = ARRAY_SIZE(odroid_dapm_routes);
		card->num_links--;
	पूर्ण

	क्रम (i = 0; i < num_pcms; i++, link += 2) अणु
		ret = of_parse_phandle_with_args(cpu, "sound-dai",
						 "#sound-dai-cells", i, &args);
		अगर (ret < 0)
			अवरोध;

		अगर (!args.np) अणु
			dev_err(dev, "sound-dai property parse error: %d\n", ret);
			ret = -EINVAL;
			अवरोध;
		पूर्ण

		ret = snd_soc_get_dai_name(&args, &link->cpus->dai_name);
		of_node_put(args.np);

		अगर (ret < 0)
			अवरोध;
	पूर्ण
	अगर (ret == 0) अणु
		cpu_dai = of_parse_phandle(cpu, "sound-dai", 0);
		अगर (!cpu_dai)
			ret = -EINVAL;
	पूर्ण

	of_node_put(cpu);
	अगर (ret < 0)
		जाओ err_put_node;

	ret = snd_soc_of_get_dai_link_codecs(dev, codec, codec_link);
	अगर (ret < 0)
		जाओ err_put_cpu_dai;

	/* Set capture capability only क्रम boards with the MAX98090 CODEC */
	अगर (codec_link->num_codecs > 1) अणु
		card->dai_link[0].dpcm_capture = 1;
		card->dai_link[1].dpcm_capture = 1;
	पूर्ण

	priv->sclk_i2s = of_clk_get_by_name(cpu_dai, "i2s_opclk1");
	अगर (IS_ERR(priv->sclk_i2s)) अणु
		ret = PTR_ERR(priv->sclk_i2s);
		जाओ err_put_cpu_dai;
	पूर्ण

	priv->clk_i2s_bus = of_clk_get_by_name(cpu_dai, "iis");
	अगर (IS_ERR(priv->clk_i2s_bus)) अणु
		ret = PTR_ERR(priv->clk_i2s_bus);
		जाओ err_put_sclk;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_card(dev, card);
	अगर (ret < 0) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "snd_soc_register_card() failed: %d\n",
				ret);
		जाओ err_put_clk_i2s;
	पूर्ण

	of_node_put(cpu_dai);
	of_node_put(codec);
	वापस 0;

err_put_clk_i2s:
	clk_put(priv->clk_i2s_bus);
err_put_sclk:
	clk_put(priv->sclk_i2s);
err_put_cpu_dai:
	of_node_put(cpu_dai);
	snd_soc_of_put_dai_link_codecs(codec_link);
err_put_node:
	of_node_put(codec);
	वापस ret;
पूर्ण

अटल पूर्णांक odroid_audio_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा odroid_priv *priv = platक्रमm_get_drvdata(pdev);

	snd_soc_of_put_dai_link_codecs(&priv->card.dai_link[1]);
	clk_put(priv->sclk_i2s);
	clk_put(priv->clk_i2s_bus);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id odroid_audio_of_match[] = अणु
	अणु .compatible	= "hardkernel,odroid-xu3-audio" पूर्ण,
	अणु .compatible	= "hardkernel,odroid-xu4-audio" पूर्ण,
	अणु .compatible	= "samsung,odroid-xu3-audio" पूर्ण,
	अणु .compatible	= "samsung,odroid-xu4-audio" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, odroid_audio_of_match);

अटल काष्ठा platक्रमm_driver odroid_audio_driver = अणु
	.driver = अणु
		.name		= "odroid-audio",
		.of_match_table	= odroid_audio_of_match,
		.pm		= &snd_soc_pm_ops,
	पूर्ण,
	.probe	= odroid_audio_probe,
	.हटाओ	= odroid_audio_हटाओ,
पूर्ण;
module_platक्रमm_driver(odroid_audio_driver);

MODULE_AUTHOR("Sylwester Nawrocki <s.nawrocki@samsung.com>");
MODULE_DESCRIPTION("Odroid XU3/XU4 audio support");
MODULE_LICENSE("GPL v2");
