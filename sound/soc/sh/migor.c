<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// ALSA SoC driver क्रम Migo-R
//
// Copyright (C) 2009-2010 Guennadi Liakhovetski <g.liakhovetski@gmx.de>

#समावेश <linux/clkdev.h>
#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/घड़ी.h>

#समावेश <cpu/sh7722.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>

#समावेश "../codecs/wm8978.h"
#समावेश "siu.h"

/* Default 8000Hz sampling frequency */
अटल अचिन्हित दीर्घ codec_freq = 8000 * 512;

अटल अचिन्हित पूर्णांक use_count;

/* External घड़ी, sourced from the codec at the SIUMCKB pin */
अटल अचिन्हित दीर्घ siumckb_recalc(काष्ठा clk *clk)
अणु
	वापस codec_freq;
पूर्ण

अटल काष्ठा sh_clk_ops siumckb_clk_ops = अणु
	.recalc = siumckb_recalc,
पूर्ण;

अटल काष्ठा clk siumckb_clk = अणु
	.ops		= &siumckb_clk_ops,
	.rate		= 0, /* initialised at run-समय */
पूर्ण;

अटल काष्ठा clk_lookup *siumckb_lookup;

अटल पूर्णांक migor_hw_params(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;
	अचिन्हित पूर्णांक rate = params_rate(params);

	ret = snd_soc_dai_set_sysclk(codec_dai, WM8978_PLL, 13000000,
				     SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_dai_set_clkभाग(codec_dai, WM8978_OPCLKRATE, rate * 512);
	अगर (ret < 0)
		वापस ret;

	codec_freq = rate * 512;
	/*
	 * This propagates the parent frequency change to children and
	 * recalculates the frequency table
	 */
	clk_set_rate(&siumckb_clk, codec_freq);
	dev_dbg(codec_dai->dev, "%s: configure %luHz\n", __func__, codec_freq);

	ret = snd_soc_dai_set_sysclk(asoc_rtd_to_cpu(rtd, 0), SIU_CLKB_EXT,
				     codec_freq / 2, SND_SOC_CLOCK_IN);

	अगर (!ret)
		use_count++;

	वापस ret;
पूर्ण

अटल पूर्णांक migor_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);

	अगर (use_count) अणु
		use_count--;

		अगर (!use_count)
			snd_soc_dai_set_sysclk(codec_dai, WM8978_PLL, 0,
					       SND_SOC_CLOCK_IN);
	पूर्ण अन्यथा अणु
		dev_dbg(codec_dai->dev, "Unbalanced hw_free!\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops migor_dai_ops = अणु
	.hw_params = migor_hw_params,
	.hw_मुक्त = migor_hw_मुक्त,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget migor_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_MIC("Onboard Microphone", शून्य),
	SND_SOC_DAPM_MIC("External Microphone", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु
	/* Headphone output connected to LHP/RHP, enable OUT4 क्रम VMID */
	अणु "Headphone", शून्य,  "OUT4 VMID" पूर्ण,
	अणु "OUT4 VMID", शून्य,  "LHP" पूर्ण,
	अणु "OUT4 VMID", शून्य,  "RHP" पूर्ण,

	/* On-board microphone */
	अणु "RMICN", शून्य, "Mic Bias" पूर्ण,
	अणु "RMICP", शून्य, "Mic Bias" पूर्ण,
	अणु "Mic Bias", शून्य, "Onboard Microphone" पूर्ण,

	/* External microphone */
	अणु "LMICN", शून्य, "Mic Bias" पूर्ण,
	अणु "LMICP", शून्य, "Mic Bias" पूर्ण,
	अणु "Mic Bias", शून्य, "External Microphone" पूर्ण,
पूर्ण;

/* migor digital audio पूर्णांकerface glue - connects codec <--> CPU */
SND_SOC_DAILINK_DEFS(wm8978,
	DAILINK_COMP_ARRAY(COMP_CPU("siu-pcm-audio")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8978.0-001a", "wm8978-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("siu-pcm-audio")));

अटल काष्ठा snd_soc_dai_link migor_dai = अणु
	.name = "wm8978",
	.stream_name = "WM8978",
	.dai_fmt = SND_SOC_DAIFMT_NB_IF | SND_SOC_DAIFMT_I2S |
		   SND_SOC_DAIFMT_CBS_CFS,
	.ops = &migor_dai_ops,
	SND_SOC_DAILINK_REG(wm8978),
पूर्ण;

/* migor audio machine driver */
अटल काष्ठा snd_soc_card snd_soc_migor = अणु
	.name = "Migo-R",
	.owner = THIS_MODULE,
	.dai_link = &migor_dai,
	.num_links = 1,

	.dapm_widमाला_लो = migor_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(migor_dapm_widमाला_लो),
	.dapm_routes = audio_map,
	.num_dapm_routes = ARRAY_SIZE(audio_map),
पूर्ण;

अटल काष्ठा platक्रमm_device *migor_snd_device;

अटल पूर्णांक __init migor_init(व्योम)
अणु
	पूर्णांक ret;

	ret = clk_रेजिस्टर(&siumckb_clk);
	अगर (ret < 0)
		वापस ret;

	siumckb_lookup = clkdev_create(&siumckb_clk, "siumckb_clk", शून्य);
	अगर (!siumckb_lookup) अणु
		ret = -ENOMEM;
		जाओ eclkdevalloc;
	पूर्ण

	/* Port number used on this machine: port B */
	migor_snd_device = platक्रमm_device_alloc("soc-audio", 1);
	अगर (!migor_snd_device) अणु
		ret = -ENOMEM;
		जाओ epdevalloc;
	पूर्ण

	platक्रमm_set_drvdata(migor_snd_device, &snd_soc_migor);

	ret = platक्रमm_device_add(migor_snd_device);
	अगर (ret)
		जाओ epdevadd;

	वापस 0;

epdevadd:
	platक्रमm_device_put(migor_snd_device);
epdevalloc:
	clkdev_drop(siumckb_lookup);
eclkdevalloc:
	clk_unरेजिस्टर(&siumckb_clk);
	वापस ret;
पूर्ण

अटल व्योम __निकास migor_निकास(व्योम)
अणु
	clkdev_drop(siumckb_lookup);
	clk_unरेजिस्टर(&siumckb_clk);
	platक्रमm_device_unरेजिस्टर(migor_snd_device);
पूर्ण

module_init(migor_init);
module_निकास(migor_निकास);

MODULE_AUTHOR("Guennadi Liakhovetski <g.liakhovetski@gmx.de>");
MODULE_DESCRIPTION("ALSA SoC Migor");
MODULE_LICENSE("GPL v2");
