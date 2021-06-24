<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2007,2008 Simtec Electronics
//
// Based on sound/soc/pxa/spitz.c
//	Copyright 2005 Wolfson Microelectronics PLC.
//	Copyright 2005 Openedhand Ltd.

#समावेश <linux/module.h>
#समावेश <sound/soc.h>

#समावेश <यंत्र/mach-types.h>

#समावेश "s3c2412-i2s.h"
#समावेश "../codecs/wm8750.h"

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु
	अणु "Headphone Jack", शून्य, "LOUT1" पूर्ण,
	अणु "Headphone Jack", शून्य, "ROUT1" पूर्ण,
	अणु "Internal Speaker", शून्य, "LOUT2" पूर्ण,
	अणु "Internal Speaker", शून्य, "ROUT2" पूर्ण,
	अणु "LINPUT1", शून्य, "Line Input" पूर्ण,
	अणु "RINPUT1", शून्य, "Line Input" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm8750_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_SPK("Internal Speaker", शून्य),
	SND_SOC_DAPM_LINE("Line In", शून्य),
पूर्ण;

अटल पूर्णांक jive_hw_params(काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा s3c_i2sv2_rate_calc भाग;
	अचिन्हित पूर्णांक clk = 0;
	पूर्णांक ret = 0;

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

	s3c_i2sv2_iis_calc_rate(&भाग, शून्य, params_rate(params),
				s3c_i2sv2_get_घड़ी(cpu_dai));

	/* set the codec प्रणाली घड़ी क्रम DAC and ADC */
	ret = snd_soc_dai_set_sysclk(codec_dai, WM8750_SYSCLK, clk,
				     SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_dai_set_clkभाग(cpu_dai, S3C2412_DIV_RCLK, भाग.fs_भाग);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_dai_set_clkभाग(cpu_dai, S3C2412_DIV_PRESCALER,
				     भाग.clk_भाग - 1);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops jive_ops = अणु
	.hw_params	= jive_hw_params,
पूर्ण;

SND_SOC_DAILINK_DEFS(wm8750,
	DAILINK_COMP_ARRAY(COMP_CPU("s3c2412-i2s")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8750.0-001a", "wm8750-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("s3c2412-i2s")));

अटल काष्ठा snd_soc_dai_link jive_dai = अणु
	.name		= "wm8750",
	.stream_name	= "WM8750",
	.dai_fmt	= SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			  SND_SOC_DAIFMT_CBS_CFS,
	.ops		= &jive_ops,
	SND_SOC_DAILINK_REG(wm8750),
पूर्ण;

/* jive audio machine driver */
अटल काष्ठा snd_soc_card snd_soc_machine_jive = अणु
	.name		= "Jive",
	.owner		= THIS_MODULE,
	.dai_link	= &jive_dai,
	.num_links	= 1,

	.dapm_widमाला_लो	= wm8750_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(wm8750_dapm_widमाला_लो),
	.dapm_routes	= audio_map,
	.num_dapm_routes = ARRAY_SIZE(audio_map),
	.fully_routed	= true,
पूर्ण;

अटल काष्ठा platक्रमm_device *jive_snd_device;

अटल पूर्णांक __init jive_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!machine_is_jive())
		वापस 0;

	prपूर्णांकk("JIVE WM8750 Audio support\n");

	jive_snd_device = platक्रमm_device_alloc("soc-audio", -1);
	अगर (!jive_snd_device)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(jive_snd_device, &snd_soc_machine_jive);
	ret = platक्रमm_device_add(jive_snd_device);

	अगर (ret)
		platक्रमm_device_put(jive_snd_device);

	वापस ret;
पूर्ण

अटल व्योम __निकास jive_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(jive_snd_device);
पूर्ण

module_init(jive_init);
module_निकास(jive_निकास);

MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>");
MODULE_DESCRIPTION("ALSA SoC Jive Audio support");
MODULE_LICENSE("GPL");
