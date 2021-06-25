<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (c) 2011 Samsung Electronics Co., Ltd
//		http://www.samsung.com

#समावेश <linux/module.h>
#समावेश <sound/soc.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>

#समावेश "../codecs/wm8994.h"
#समावेश "pcm.h"

/*
 * Board Settings:
 *  o '1' means 'ON'
 *  o '0' means 'OFF'
 *  o 'X' means 'Don't care'
 *
 * SMDKC210, SMDKV310: CFG3- 1001, CFG5-1000, CFG7-111111
 */

/*
 * Configure audio route as :-
 * $ amixer sset 'DAC1' on,on
 * $ amixer sset 'Right Headphone Mux' 'DAC'
 * $ amixer sset 'Left Headphone Mux' 'DAC'
 * $ amixer sset 'DAC1R Mixer AIF1.1' on
 * $ amixer sset 'DAC1L Mixer AIF1.1' on
 * $ amixer sset 'IN2L' on
 * $ amixer sset 'IN2L PGA IN2LN' on
 * $ amixer sset 'MIXINL IN2L' on
 * $ amixer sset 'AIF1ADC1L Mixer ADC/DMIC' on
 * $ amixer sset 'IN2R' on
 * $ amixer sset 'IN2R PGA IN2RN' on
 * $ amixer sset 'MIXINR IN2R' on
 * $ amixer sset 'AIF1ADC1R Mixer ADC/DMIC' on
 */

/* SMDK has a 16.9344MHZ crystal attached to WM8994 */
#घोषणा SMDK_WM8994_FREQ 16934400

अटल पूर्णांक smdk_wm8994_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	अचिन्हित दीर्घ mclk_freq;
	पूर्णांक rfs, ret;

	चयन(params_rate(params)) अणु
	हाल 8000:
		rfs = 512;
		अवरोध;
	शेष:
		dev_err(cpu_dai->dev, "%s:%d Sampling Rate %u not supported!\n",
		__func__, __LINE__, params_rate(params));
		वापस -EINVAL;
	पूर्ण

	mclk_freq = params_rate(params) * rfs;

	ret = snd_soc_dai_set_sysclk(codec_dai, WM8994_SYSCLK_FLL1,
					mclk_freq, SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_dai_set_pll(codec_dai, WM8994_FLL1, WM8994_FLL_SRC_MCLK1,
					SMDK_WM8994_FREQ, mclk_freq);
	अगर (ret < 0)
		वापस ret;

	/* Set PCM source घड़ी on CPU */
	ret = snd_soc_dai_set_sysclk(cpu_dai, S3C_PCM_CLKSRC_MUX,
					mclk_freq, SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	/* Set SCLK_DIV क्रम making bclk */
	ret = snd_soc_dai_set_clkभाग(cpu_dai, S3C_PCM_SCLK_PER_FS, rfs);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_ops smdk_wm8994_pcm_ops = अणु
	.hw_params = smdk_wm8994_pcm_hw_params,
पूर्ण;

SND_SOC_DAILINK_DEFS(paअगर_pcm,
	DAILINK_COMP_ARRAY(COMP_CPU("samsung-pcm.0")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8994-codec", "wm8994-aif1")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("samsung-pcm.0")));

अटल काष्ठा snd_soc_dai_link smdk_dai[] = अणु
	अणु
		.name = "WM8994 PAIF PCM",
		.stream_name = "Primary PCM",
		.dai_fmt = SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_IB_NF |
			   SND_SOC_DAIFMT_CBS_CFS,
		.ops = &smdk_wm8994_pcm_ops,
		SND_SOC_DAILINK_REG(paअगर_pcm),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card smdk_pcm = अणु
	.name = "SMDK-PCM",
	.owner = THIS_MODULE,
	.dai_link = smdk_dai,
	.num_links = 1,
पूर्ण;

अटल पूर्णांक snd_smdk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;

	smdk_pcm.dev = &pdev->dev;
	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, &smdk_pcm);
	अगर (ret && ret != -EPROBE_DEFER)
		dev_err(&pdev->dev, "snd_soc_register_card failed %d\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver snd_smdk_driver = अणु
	.driver = अणु
		.name = "samsung-smdk-pcm",
	पूर्ण,
	.probe = snd_smdk_probe,
पूर्ण;

module_platक्रमm_driver(snd_smdk_driver);

MODULE_AUTHOR("Sangbeom Kim, <sbkim73@samsung.com>");
MODULE_DESCRIPTION("ALSA SoC SMDK WM8994 for PCM");
MODULE_LICENSE("GPL");
