<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SoC audio क्रम EDB93xx
 *
 * Copyright (c) 2010 Alexander Sverdlin <subaparts@yandex.ru>
 *
 * This driver support CS4271 codec being master or slave, working
 * in control port mode, connected either via SPI or I2C.
 * The data क्रमmat accepted is I2S or left-justअगरied.
 * DAPM support not implemented.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/soc/cirrus/ep93xx.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <यंत्र/mach-types.h>

अटल पूर्णांक edb93xx_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	पूर्णांक err;
	अचिन्हित पूर्णांक mclk_rate;
	अचिन्हित पूर्णांक rate = params_rate(params);

	/*
	 * According to CS4271 datasheet we use MCLK/LRCK=256 क्रम
	 * rates below 50kHz and 128 क्रम higher sample rates
	 */
	अगर (rate < 50000)
		mclk_rate = rate * 64 * 4;
	अन्यथा
		mclk_rate = rate * 64 * 2;

	err = snd_soc_dai_set_sysclk(codec_dai, 0, mclk_rate,
				     SND_SOC_CLOCK_IN);
	अगर (err)
		वापस err;

	वापस snd_soc_dai_set_sysclk(cpu_dai, 0, mclk_rate,
				      SND_SOC_CLOCK_OUT);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops edb93xx_ops = अणु
	.hw_params	= edb93xx_hw_params,
पूर्ण;

SND_SOC_DAILINK_DEFS(hअगरi,
	DAILINK_COMP_ARRAY(COMP_CPU("ep93xx-i2s")),
	DAILINK_COMP_ARRAY(COMP_CODEC("spi0.0", "cs4271-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("ep93xx-i2s")));

अटल काष्ठा snd_soc_dai_link edb93xx_dai = अणु
	.name		= "CS4271",
	.stream_name	= "CS4271 HiFi",
	.dai_fmt	= SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			  SND_SOC_DAIFMT_CBS_CFS,
	.ops		= &edb93xx_ops,
	SND_SOC_DAILINK_REG(hअगरi),
पूर्ण;

अटल काष्ठा snd_soc_card snd_soc_edb93xx = अणु
	.name		= "EDB93XX",
	.owner		= THIS_MODULE,
	.dai_link	= &edb93xx_dai,
	.num_links	= 1,
पूर्ण;

अटल पूर्णांक edb93xx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &snd_soc_edb93xx;
	पूर्णांक ret;

	ret = ep93xx_i2s_acquire();
	अगर (ret)
		वापस ret;

	card->dev = &pdev->dev;

	ret = snd_soc_रेजिस्टर_card(card);
	अगर (ret) अणु
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n",
			ret);
		ep93xx_i2s_release();
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक edb93xx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);

	snd_soc_unरेजिस्टर_card(card);
	ep93xx_i2s_release();

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver edb93xx_driver = अणु
	.driver		= अणु
		.name	= "edb93xx-audio",
	पूर्ण,
	.probe		= edb93xx_probe,
	.हटाओ		= edb93xx_हटाओ,
पूर्ण;

module_platक्रमm_driver(edb93xx_driver);

MODULE_AUTHOR("Alexander Sverdlin <subaparts@yandex.ru>");
MODULE_DESCRIPTION("ALSA SoC EDB93xx");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:edb93xx-audio");
