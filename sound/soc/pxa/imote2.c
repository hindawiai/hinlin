<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/module.h>
#समावेश <sound/soc.h>

#समावेश <यंत्र/mach-types.h>

#समावेश "../codecs/wm8940.h"
#समावेश "pxa2xx-i2s.h"

अटल पूर्णांक imote2_asoc_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	अचिन्हित पूर्णांक clk = 0;
	पूर्णांक ret;

	चयन (params_rate(params)) अणु
	हाल 8000:
	हाल 16000:
	हाल 48000:
	हाल 96000:
		clk = 12288000;
		अवरोध;
	हाल 11025:
	हाल 22050:
	हाल 44100:
		clk = 11289600;
		अवरोध;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(codec_dai, 0, clk,
				     SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	/* set the I2S प्रणाली घड़ी as input (unused) */
	ret = snd_soc_dai_set_sysclk(cpu_dai, PXA2XX_I2S_SYSCLK, clk,
		SND_SOC_CLOCK_OUT);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops imote2_asoc_ops = अणु
	.hw_params = imote2_asoc_hw_params,
पूर्ण;

SND_SOC_DAILINK_DEFS(wm8940,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa2xx-i2s")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8940-codec.0-0034",
				      "wm8940-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

अटल काष्ठा snd_soc_dai_link imote2_dai = अणु
	.name = "WM8940",
	.stream_name = "WM8940",
	.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
		   SND_SOC_DAIFMT_CBS_CFS,
	.ops = &imote2_asoc_ops,
	SND_SOC_DAILINK_REG(wm8940),
पूर्ण;

अटल काष्ठा snd_soc_card imote2 = अणु
	.name = "Imote2",
	.owner = THIS_MODULE,
	.dai_link = &imote2_dai,
	.num_links = 1,
पूर्ण;

अटल पूर्णांक imote2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &imote2;
	पूर्णांक ret;

	card->dev = &pdev->dev;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret)
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n",
			ret);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver imote2_driver = अणु
	.driver		= अणु
		.name	= "imote2-audio",
		.pm     = &snd_soc_pm_ops,
	पूर्ण,
	.probe		= imote2_probe,
पूर्ण;

module_platक्रमm_driver(imote2_driver);

MODULE_AUTHOR("Jonathan Cameron");
MODULE_DESCRIPTION("ALSA SoC Imote 2");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:imote2-audio");
