<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (c) 2009 Samsung Electronics Co. Ltd
// Author: Jaswinder Singh <jassisinghbrar@gmail.com>

#समावेश <linux/module.h>
#समावेश <sound/soc.h>
#समावेश <sound/pcm_params.h>

#समावेश "../codecs/wm8580.h"
#समावेश "i2s.h"

/*
 * Default CFG चयन settings to use this driver:
 *
 *   SMDK6410: Set CFG1 1-3 Off, CFG2 1-4 On
 */

/* SMDK has a 12MHZ crystal attached to WM8580 */
#घोषणा SMDK_WM8580_FREQ 12000000

अटल पूर्णांक smdk_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	अचिन्हित पूर्णांक pll_out;
	पूर्णांक rfs, ret;

	चयन (params_width(params)) अणु
	हाल 8:
	हाल 16:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* The Fvco क्रम WM8580 PLLs must fall within [90,100]MHz.
	 * This criterion can't be met अगर we request PLL output
	 * as अणु8000x256, 64000x256, 11025x256पूर्णHz.
	 * As a wayout, we rather change rfs to a minimum value that
	 * results in (params_rate(params) * rfs), and itself, acceptable
	 * to both - the CODEC and the CPU.
	 */
	चयन (params_rate(params)) अणु
	हाल 16000:
	हाल 22050:
	हाल 32000:
	हाल 44100:
	हाल 48000:
	हाल 88200:
	हाल 96000:
		rfs = 256;
		अवरोध;
	हाल 64000:
		rfs = 384;
		अवरोध;
	हाल 8000:
	हाल 11025:
		rfs = 512;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	pll_out = params_rate(params) * rfs;

	/* Set WM8580 to drive MCLK from its PLLA */
	ret = snd_soc_dai_set_clkभाग(codec_dai, WM8580_MCLK,
					WM8580_CLKSRC_PLLA);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_dai_set_pll(codec_dai, WM8580_PLLA, 0,
					SMDK_WM8580_FREQ, pll_out);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_dai_set_sysclk(codec_dai, WM8580_CLKSRC_PLLA,
				     pll_out, SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/*
 * SMDK WM8580 DAI operations.
 */
अटल काष्ठा snd_soc_ops smdk_ops = अणु
	.hw_params = smdk_hw_params,
पूर्ण;

/* SMDK Playback widमाला_लो */
अटल स्थिर काष्ठा snd_soc_dapm_widget smdk_wm8580_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Front", शून्य),
	SND_SOC_DAPM_HP("Center+Sub", शून्य),
	SND_SOC_DAPM_HP("Rear", शून्य),

	SND_SOC_DAPM_MIC("MicIn", शून्य),
	SND_SOC_DAPM_LINE("LineIn", शून्य),
पूर्ण;

/* SMDK-PAIFTX connections */
अटल स्थिर काष्ठा snd_soc_dapm_route smdk_wm8580_audio_map[] = अणु
	/* MicIn feeds AINL */
	अणु"AINL", शून्य, "MicIn"पूर्ण,

	/* LineIn feeds AINL/R */
	अणु"AINL", शून्य, "LineIn"पूर्ण,
	अणु"AINR", शून्य, "LineIn"पूर्ण,

	/* Front Left/Right are fed VOUT1L/R */
	अणु"Front", शून्य, "VOUT1L"पूर्ण,
	अणु"Front", शून्य, "VOUT1R"पूर्ण,

	/* Center/Sub are fed VOUT2L/R */
	अणु"Center+Sub", शून्य, "VOUT2L"पूर्ण,
	अणु"Center+Sub", शून्य, "VOUT2R"पूर्ण,

	/* Rear Left/Right are fed VOUT3L/R */
	अणु"Rear", शून्य, "VOUT3L"पूर्ण,
	अणु"Rear", शून्य, "VOUT3R"पूर्ण,
पूर्ण;

अटल पूर्णांक smdk_wm8580_init_paअगरtx(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	/* Enabling the microphone requires the fitting of a 0R
	 * resistor to connect the line from the microphone jack.
	 */
	snd_soc_dapm_disable_pin(&rtd->card->dapm, "MicIn");

	वापस 0;
पूर्ण

क्रमागत अणु
	PRI_PLAYBACK = 0,
	PRI_CAPTURE,
पूर्ण;

#घोषणा SMDK_DAI_FMT (SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF | \
	SND_SOC_DAIFMT_CBM_CFM)

SND_SOC_DAILINK_DEFS(paअगर_rx,
	DAILINK_COMP_ARRAY(COMP_CPU("samsung-i2s.2")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8580.0-001b", "wm8580-hifi-playback")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("samsung-i2s.0")));

SND_SOC_DAILINK_DEFS(paअगर_tx,
	DAILINK_COMP_ARRAY(COMP_CPU("samsung-i2s.2")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8580.0-001b", "wm8580-hifi-capture")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("samsung-i2s.0")));

अटल काष्ठा snd_soc_dai_link smdk_dai[] = अणु
	[PRI_PLAYBACK] = अणु /* Primary Playback i/f */
		.name = "WM8580 PAIF RX",
		.stream_name = "Playback",
		.dai_fmt = SMDK_DAI_FMT,
		.ops = &smdk_ops,
		SND_SOC_DAILINK_REG(paअगर_rx),
	पूर्ण,
	[PRI_CAPTURE] = अणु /* Primary Capture i/f */
		.name = "WM8580 PAIF TX",
		.stream_name = "Capture",
		.dai_fmt = SMDK_DAI_FMT,
		.init = smdk_wm8580_init_paअगरtx,
		.ops = &smdk_ops,
		SND_SOC_DAILINK_REG(paअगर_tx),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card smdk = अणु
	.name = "SMDK-I2S",
	.owner = THIS_MODULE,
	.dai_link = smdk_dai,
	.num_links = ARRAY_SIZE(smdk_dai),

	.dapm_widमाला_लो = smdk_wm8580_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(smdk_wm8580_dapm_widमाला_लो),
	.dapm_routes = smdk_wm8580_audio_map,
	.num_dapm_routes = ARRAY_SIZE(smdk_wm8580_audio_map),
पूर्ण;

अटल काष्ठा platक्रमm_device *smdk_snd_device;

अटल पूर्णांक __init smdk_audio_init(व्योम)
अणु
	पूर्णांक ret;

	smdk_snd_device = platक्रमm_device_alloc("soc-audio", -1);
	अगर (!smdk_snd_device)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(smdk_snd_device, &smdk);
	ret = platक्रमm_device_add(smdk_snd_device);

	अगर (ret)
		platक्रमm_device_put(smdk_snd_device);

	वापस ret;
पूर्ण
module_init(smdk_audio_init);

अटल व्योम __निकास smdk_audio_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(smdk_snd_device);
पूर्ण
module_निकास(smdk_audio_निकास);

MODULE_AUTHOR("Jaswinder Singh, jassisinghbrar@gmail.com");
MODULE_DESCRIPTION("ALSA SoC SMDK WM8580");
MODULE_LICENSE("GPL");
