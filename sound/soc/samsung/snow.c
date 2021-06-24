<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// ASoC machine driver क्रम Snow boards

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश "i2s.h"

#घोषणा FIN_PLL_RATE		24000000

SND_SOC_DAILINK_DEFS(links,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

काष्ठा snow_priv अणु
	काष्ठा snd_soc_dai_link dai_link;
	काष्ठा clk *clk_i2s_bus;
पूर्ण;

अटल पूर्णांक snow_card_hw_params(काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_pcm_hw_params *params)
अणु
	अटल स्थिर अचिन्हित पूर्णांक pll_rate[] = अणु
		73728000U, 67737602U, 49152000U, 45158401U, 32768001U
	पूर्ण;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snow_priv *priv = snd_soc_card_get_drvdata(rtd->card);
	पूर्णांक bfs, psr, rfs, bitwidth;
	अचिन्हित दीर्घ पूर्णांक rclk;
	दीर्घ पूर्णांक freq = -EINVAL;
	पूर्णांक ret, i;

	bitwidth = snd_pcm_क्रमmat_width(params_क्रमmat(params));
	अगर (bitwidth < 0) अणु
		dev_err(rtd->card->dev, "Invalid bit-width: %d\n", bitwidth);
		वापस bitwidth;
	पूर्ण

	अगर (bitwidth != 16 && bitwidth != 24) अणु
		dev_err(rtd->card->dev, "Unsupported bit-width: %d\n", bitwidth);
		वापस -EINVAL;
	पूर्ण

	bfs = 2 * bitwidth;

	चयन (params_rate(params)) अणु
	हाल 16000:
	हाल 22050:
	हाल 24000:
	हाल 32000:
	हाल 44100:
	हाल 48000:
	हाल 88200:
	हाल 96000:
		rfs = 8 * bfs;
		अवरोध;
	हाल 64000:
		rfs = 384;
		अवरोध;
	हाल 8000:
	हाल 11025:
	हाल 12000:
		rfs = 16 * bfs;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rclk = params_rate(params) * rfs;

	क्रम (psr = 8; psr > 0; psr /= 2) अणु
		क्रम (i = 0; i < ARRAY_SIZE(pll_rate); i++) अणु
			अगर ((pll_rate[i] - rclk * psr) <= 2) अणु
				freq = pll_rate[i];
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (freq < 0) अणु
		dev_err(rtd->card->dev, "Unsupported RCLK rate: %lu\n", rclk);
		वापस -EINVAL;
	पूर्ण

	ret = clk_set_rate(priv->clk_i2s_bus, freq);
	अगर (ret < 0) अणु
		dev_err(rtd->card->dev, "I2S bus clock rate set failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops snow_card_ops = अणु
	.hw_params = snow_card_hw_params,
पूर्ण;

अटल पूर्णांक snow_late_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd;
	काष्ठा snd_soc_dai *codec_dai;

	rtd = snd_soc_get_pcm_runसमय(card, &card->dai_link[0]);

	/* In the multi-codec हाल codec_dais 0 is MAX98095 and 1 is HDMI. */
	codec_dai = asoc_rtd_to_codec(rtd, 0);

	/* Set the MCLK rate क्रम the codec */
	वापस snd_soc_dai_set_sysclk(codec_dai, 0,
				FIN_PLL_RATE, SND_SOC_CLOCK_IN);
पूर्ण

अटल काष्ठा snd_soc_card snow_snd = अणु
	.name = "Snow-I2S",
	.owner = THIS_MODULE,
	.late_probe = snow_late_probe,
पूर्ण;

अटल पूर्णांक snow_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा snd_soc_card *card = &snow_snd;
	काष्ठा device_node *cpu, *codec;
	काष्ठा snd_soc_dai_link *link;
	काष्ठा snow_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	link = &priv->dai_link;

	link->dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS;

	link->name = "Primary";
	link->stream_name = link->name;

	link->cpus = links_cpus;
	link->num_cpus = ARRAY_SIZE(links_cpus);
	link->codecs = links_codecs;
	link->num_codecs = ARRAY_SIZE(links_codecs);
	link->platक्रमms = links_platक्रमms;
	link->num_platक्रमms = ARRAY_SIZE(links_platक्रमms);

	card->dai_link = link;
	card->num_links = 1;
	card->dev = dev;

	/* Try new DT bindings with HDMI support first. */
	cpu = of_get_child_by_name(dev->of_node, "cpu");

	अगर (cpu) अणु
		link->ops = &snow_card_ops;

		link->cpus->of_node = of_parse_phandle(cpu, "sound-dai", 0);
		of_node_put(cpu);

		अगर (!link->cpus->of_node) अणु
			dev_err(dev, "Failed parsing cpu/sound-dai property\n");
			वापस -EINVAL;
		पूर्ण

		codec = of_get_child_by_name(dev->of_node, "codec");
		ret = snd_soc_of_get_dai_link_codecs(dev, codec, link);
		of_node_put(codec);

		अगर (ret < 0) अणु
			of_node_put(link->cpus->of_node);
			dev_err(dev, "Failed parsing codec node\n");
			वापस ret;
		पूर्ण

		priv->clk_i2s_bus = of_clk_get_by_name(link->cpus->of_node,
						       "i2s_opclk0");
		अगर (IS_ERR(priv->clk_i2s_bus)) अणु
			snd_soc_of_put_dai_link_codecs(link);
			of_node_put(link->cpus->of_node);
			वापस PTR_ERR(priv->clk_i2s_bus);
		पूर्ण
	पूर्ण अन्यथा अणु
		link->codecs->dai_name = "HiFi";

		link->cpus->of_node = of_parse_phandle(dev->of_node,
						"samsung,i2s-controller", 0);
		अगर (!link->cpus->of_node) अणु
			dev_err(dev, "i2s-controller property parse error\n");
			वापस -EINVAL;
		पूर्ण

		link->codecs->of_node = of_parse_phandle(dev->of_node,
						"samsung,audio-codec", 0);
		अगर (!link->codecs->of_node) अणु
			of_node_put(link->cpus->of_node);
			dev_err(dev, "audio-codec property parse error\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	link->platक्रमms->of_node = link->cpus->of_node;

	/* Update card-name अगर provided through DT, अन्यथा use शेष name */
	snd_soc_of_parse_card_name(card, "samsung,model");

	snd_soc_card_set_drvdata(card, priv);

	ret = devm_snd_soc_रेजिस्टर_card(dev, card);
	अगर (ret) अणु
		अगर (ret != -EPROBE_DEFER)
			dev_err(&pdev->dev,
				"snd_soc_register_card failed (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक snow_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snow_priv *priv = platक्रमm_get_drvdata(pdev);
	काष्ठा snd_soc_dai_link *link = &priv->dai_link;

	of_node_put(link->cpus->of_node);
	of_node_put(link->codecs->of_node);
	snd_soc_of_put_dai_link_codecs(link);

	clk_put(priv->clk_i2s_bus);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id snow_of_match[] = अणु
	अणु .compatible = "google,snow-audio-max98090", पूर्ण,
	अणु .compatible = "google,snow-audio-max98091", पूर्ण,
	अणु .compatible = "google,snow-audio-max98095", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, snow_of_match);

अटल काष्ठा platक्रमm_driver snow_driver = अणु
	.driver = अणु
		.name = "snow-audio",
		.pm = &snd_soc_pm_ops,
		.of_match_table = snow_of_match,
	पूर्ण,
	.probe = snow_probe,
	.हटाओ = snow_हटाओ,
पूर्ण;

module_platक्रमm_driver(snow_driver);

MODULE_DESCRIPTION("ALSA SoC Audio machine driver for Snow");
MODULE_LICENSE("GPL");
