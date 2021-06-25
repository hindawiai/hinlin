<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/sound/soc/pxa/brownstone.c
 *
 * Copyright (C) 2011 Marvell International Ltd.
 */

#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/jack.h>

#समावेश "../codecs/wm8994.h"
#समावेश "mmp-sspa.h"

अटल स्थिर काष्ठा snd_kcontrol_new brownstone_dapm_control[] = अणु
	SOC_DAPM_PIN_SWITCH("Ext Spk"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget brownstone_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Ext Spk", शून्य),
	SND_SOC_DAPM_HP("Headset Stereophone", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Main Mic", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route brownstone_audio_map[] = अणु
	अणु"Ext Spk", शून्य, "SPKOUTLP"पूर्ण,
	अणु"Ext Spk", शून्य, "SPKOUTLN"पूर्ण,
	अणु"Ext Spk", शून्य, "SPKOUTRP"पूर्ण,
	अणु"Ext Spk", शून्य, "SPKOUTRN"पूर्ण,

	अणु"Headset Stereophone", शून्य, "HPOUT1L"पूर्ण,
	अणु"Headset Stereophone", शून्य, "HPOUT1R"पूर्ण,

	अणु"IN1RN", शून्य, "Headset Mic"पूर्ण,

	अणु"DMIC1DAT", शून्य, "MICBIAS1"पूर्ण,
	अणु"MICBIAS1", शून्य, "Main Mic"पूर्ण,
पूर्ण;

अटल पूर्णांक brownstone_wm8994_hw_params(काष्ठा snd_pcm_substream *substream,
				       काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	पूर्णांक freq_out, sspa_mclk, sysclk;

	अगर (params_rate(params) > 11025) अणु
		freq_out  = params_rate(params) * 512;
		sysclk    = params_rate(params) * 256;
		sspa_mclk = params_rate(params) * 64;
	पूर्ण अन्यथा अणु
		freq_out  = params_rate(params) * 1024;
		sysclk    = params_rate(params) * 512;
		sspa_mclk = params_rate(params) * 64;
	पूर्ण

	snd_soc_dai_set_sysclk(cpu_dai, MMP_SSPA_CLK_AUDIO, freq_out, 0);
	snd_soc_dai_set_pll(cpu_dai, MMP_SYSCLK, 0, freq_out, sysclk);
	snd_soc_dai_set_pll(cpu_dai, MMP_SSPA_CLK, 0, freq_out, sspa_mclk);

	/* set wm8994 sysclk */
	snd_soc_dai_set_sysclk(codec_dai, WM8994_SYSCLK_MCLK1, sysclk, 0);

	वापस 0;
पूर्ण

/* machine stream operations */
अटल स्थिर काष्ठा snd_soc_ops brownstone_ops = अणु
	.hw_params = brownstone_wm8994_hw_params,
पूर्ण;

SND_SOC_DAILINK_DEFS(wm8994,
	DAILINK_COMP_ARRAY(COMP_CPU("mmp-sspa-dai.0")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8994-codec", "wm8994-aif1")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("mmp-pcm-audio")));

अटल काष्ठा snd_soc_dai_link brownstone_wm8994_dai[] = अणु
अणु
	.name		= "WM8994",
	.stream_name	= "WM8994 HiFi",
	.dai_fmt	= SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
				SND_SOC_DAIFMT_CBS_CFS,
	.ops		= &brownstone_ops,
	SND_SOC_DAILINK_REG(wm8994),
पूर्ण,
पूर्ण;

/* audio machine driver */
अटल काष्ठा snd_soc_card brownstone = अणु
	.name         = "brownstone",
	.owner        = THIS_MODULE,
	.dai_link     = brownstone_wm8994_dai,
	.num_links    = ARRAY_SIZE(brownstone_wm8994_dai),

	.controls = brownstone_dapm_control,
	.num_controls = ARRAY_SIZE(brownstone_dapm_control),
	.dapm_widमाला_लो = brownstone_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(brownstone_dapm_widमाला_लो),
	.dapm_routes = brownstone_audio_map,
	.num_dapm_routes = ARRAY_SIZE(brownstone_audio_map),
	.fully_routed = true,
पूर्ण;

अटल पूर्णांक brownstone_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	brownstone.dev = &pdev->dev;
	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, &brownstone);
	अगर (ret)
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n",
				ret);
	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver mmp_driver = अणु
	.driver		= अणु
		.name	= "brownstone-audio",
		.pm     = &snd_soc_pm_ops,
	पूर्ण,
	.probe		= brownstone_probe,
पूर्ण;

module_platक्रमm_driver(mmp_driver);

MODULE_AUTHOR("Leo Yan <leoy@marvell.com>");
MODULE_DESCRIPTION("ALSA SoC Brownstone");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:brownstone-audio");
