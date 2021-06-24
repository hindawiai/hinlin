<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Socionext UniPhier AIO ALSA driver क्रम PXs2.
//
// Copyright (c) 2018 Socionext Inc.

#समावेश <linux/module.h>

#समावेश "aio.h"

अटल स्थिर काष्ठा uniphier_aio_spec uniphier_aio_pxs2[] = अणु
	/* क्रम Line PCM In, Pin:AI1Dx */
	अणु
		.name = AUD_NAME_PCMIN1,
		.gname = AUD_GNAME_LINE,
		.swm = अणु
			.type  = PORT_TYPE_I2S,
			.dir   = PORT_सूची_INPUT,
			.rb    = अणु 16, 11, पूर्ण,
			.ch    = अणु 16, 11, पूर्ण,
			.iअगर   = अणु 0, 0, पूर्ण,
			.iport = अणु 0, AUD_HW_PCMIN1, पूर्ण,
		पूर्ण,
	पूर्ण,

	/* क्रम Speaker/Headphone/Mic PCM In, Pin:AI2Dx */
	अणु
		.name = AUD_NAME_PCMIN2,
		.gname = AUD_GNAME_AUX,
		.swm = अणु
			.type  = PORT_TYPE_I2S,
			.dir   = PORT_सूची_INPUT,
			.rb    = अणु 17, 12, पूर्ण,
			.ch    = अणु 17, 12, पूर्ण,
			.iअगर   = अणु 1, 1, पूर्ण,
			.iport = अणु 1, AUD_HW_PCMIN2, पूर्ण,
		पूर्ण,
	पूर्ण,

	/* क्रम HDMI PCM Out, Pin:AO1Dx (inner) */
	अणु
		.name = AUD_NAME_HPCMOUT1,
		.gname = AUD_GNAME_HDMI,
		.swm = अणु
			.type  = PORT_TYPE_I2S,
			.dir   = PORT_सूची_OUTPUT,
			.rb    = अणु 0, 0, पूर्ण,
			.ch    = अणु 0, 0, पूर्ण,
			.oअगर   = अणु 0, 0, पूर्ण,
			.oport = अणु 3, AUD_HW_HPCMOUT1, पूर्ण,
		पूर्ण,
	पूर्ण,

	/* क्रम Line PCM Out, Pin:AO2Dx */
	अणु
		.name = AUD_NAME_PCMOUT1,
		.gname = AUD_GNAME_LINE,
		.swm = अणु
			.type  = PORT_TYPE_I2S,
			.dir   = PORT_सूची_OUTPUT,
			.rb    = अणु 1, 1, पूर्ण,
			.ch    = अणु 1, 1, पूर्ण,
			.oअगर   = अणु 1, 1, पूर्ण,
			.oport = अणु 0, AUD_HW_PCMOUT1, पूर्ण,
		पूर्ण,
	पूर्ण,

	/* क्रम Speaker/Headphone/Mic PCM Out, Pin:AO3Dx */
	अणु
		.name = AUD_NAME_PCMOUT2,
		.gname = AUD_GNAME_AUX,
		.swm = अणु
			.type  = PORT_TYPE_I2S,
			.dir   = PORT_सूची_OUTPUT,
			.rb    = अणु 2, 2, पूर्ण,
			.ch    = अणु 2, 2, पूर्ण,
			.oअगर   = अणु 2, 2, पूर्ण,
			.oport = अणु 1, AUD_HW_PCMOUT2, पूर्ण,
		पूर्ण,
	पूर्ण,

	/* क्रम HDMI Out, Pin:AO1IEC */
	अणु
		.name = AUD_NAME_HIECOUT1,
		.swm = अणु
			.type  = PORT_TYPE_SPDIF,
			.dir   = PORT_सूची_OUTPUT,
			.rb    = अणु 6, 4, पूर्ण,
			.ch    = अणु 6, 4, पूर्ण,
			.oअगर   = अणु 6, 4, पूर्ण,
			.oport = अणु 12, AUD_HW_HIECOUT1, पूर्ण,
		पूर्ण,
	पूर्ण,

	/* क्रम HDMI Out, Pin:AO1IEC, Compress */
	अणु
		.name = AUD_NAME_HIECCOMPOUT1,
		.swm = अणु
			.type  = PORT_TYPE_SPDIF,
			.dir   = PORT_सूची_OUTPUT,
			.rb    = अणु 6, 4, पूर्ण,
			.ch    = अणु 6, 4, पूर्ण,
			.oअगर   = अणु 6, 4, पूर्ण,
			.oport = अणु 12, AUD_HW_HIECOUT1, पूर्ण,
		पूर्ण,
	पूर्ण,

	/* क्रम S/PDIF Out, Pin:AO2IEC */
	अणु
		.name = AUD_NAME_IECOUT1,
		.swm = अणु
			.type  = PORT_TYPE_SPDIF,
			.dir   = PORT_सूची_OUTPUT,
			.rb    = अणु 7, 5, पूर्ण,
			.ch    = अणु 7, 5, पूर्ण,
			.oअगर   = अणु 7, 5, पूर्ण,
			.oport = अणु 13, AUD_HW_IECOUT1, पूर्ण,
		पूर्ण,
	पूर्ण,

	/* क्रम S/PDIF Out, Pin:AO2IEC */
	अणु
		.name = AUD_NAME_IECCOMPOUT1,
		.swm = अणु
			.type  = PORT_TYPE_SPDIF,
			.dir   = PORT_सूची_OUTPUT,
			.rb    = अणु 7, 5, पूर्ण,
			.ch    = अणु 7, 5, पूर्ण,
			.oअगर   = अणु 7, 5, पूर्ण,
			.oport = अणु 13, AUD_HW_IECOUT1, पूर्ण,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा uniphier_aio_pll uniphier_aio_pll_pxs2[] = अणु
	[AUD_PLL_A1]   = अणु .enable = true, पूर्ण,
	[AUD_PLL_F1]   = अणु .enable = true, पूर्ण,
	[AUD_PLL_A2]   = अणु .enable = true, पूर्ण,
	[AUD_PLL_F2]   = अणु .enable = true, पूर्ण,
	[AUD_PLL_APLL] = अणु .enable = true, पूर्ण,
	[AUD_PLL_HSC0] = अणु .enable = true, पूर्ण,
पूर्ण;

अटल पूर्णांक uniphier_aio_pxs2_probe(काष्ठा snd_soc_dai *dai)
अणु
	पूर्णांक ret;

	ret = uniphier_aio_dai_probe(dai);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_dai_set_pll(dai, AUD_PLL_A1, 0, 0, 36864000);
	अगर (ret < 0)
		वापस ret;
	ret = snd_soc_dai_set_pll(dai, AUD_PLL_F1, 0, 0, 36864000);
	अगर (ret < 0)
		वापस ret;

	ret = snd_soc_dai_set_pll(dai, AUD_PLL_A2, 0, 0, 33868800);
	अगर (ret < 0)
		वापस ret;
	ret = snd_soc_dai_set_pll(dai, AUD_PLL_F2, 0, 0, 33868800);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_dai_driver uniphier_aio_dai_pxs2[] = अणु
	अणु
		.name    = AUD_GNAME_HDMI,
		.probe   = uniphier_aio_pxs2_probe,
		.हटाओ  = uniphier_aio_dai_हटाओ,
		.playback = अणु
			.stream_name = AUD_NAME_HPCMOUT1,
			.क्रमmats     = SNDRV_PCM_FMTBIT_S32_LE,
			.rates       = SNDRV_PCM_RATE_48000,
			.channels_min = 2,
			.channels_max = 2,
		पूर्ण,
		.ops = &uniphier_aio_i2s_ops,
	पूर्ण,
	अणु
		.name    = AUD_GNAME_LINE,
		.probe   = uniphier_aio_pxs2_probe,
		.हटाओ  = uniphier_aio_dai_हटाओ,
		.playback = अणु
			.stream_name = AUD_NAME_PCMOUT1,
			.क्रमmats     = SNDRV_PCM_FMTBIT_S32_LE,
			.rates       = SNDRV_PCM_RATE_48000,
			.channels_min = 2,
			.channels_max = 2,
		पूर्ण,
		.capture = अणु
			.stream_name = AUD_NAME_PCMIN1,
			.क्रमmats     = SNDRV_PCM_FMTBIT_S32_LE,
			.rates       = SNDRV_PCM_RATE_48000,
			.channels_min = 2,
			.channels_max = 2,
		पूर्ण,
		.ops = &uniphier_aio_i2s_ops,
	पूर्ण,
	अणु
		.name    = AUD_GNAME_AUX,
		.probe   = uniphier_aio_pxs2_probe,
		.हटाओ  = uniphier_aio_dai_हटाओ,
		.playback = अणु
			.stream_name = AUD_NAME_PCMOUT2,
			.क्रमmats     = SNDRV_PCM_FMTBIT_S32_LE,
			.rates       = SNDRV_PCM_RATE_48000,
			.channels_min = 2,
			.channels_max = 2,
		पूर्ण,
		.capture = अणु
			.stream_name = AUD_NAME_PCMIN2,
			.क्रमmats     = SNDRV_PCM_FMTBIT_S32_LE,
			.rates       = SNDRV_PCM_RATE_48000,
			.channels_min = 2,
			.channels_max = 2,
		पूर्ण,
		.ops = &uniphier_aio_i2s_ops,
	पूर्ण,
	अणु
		.name    = AUD_NAME_HIECOUT1,
		.probe   = uniphier_aio_pxs2_probe,
		.हटाओ  = uniphier_aio_dai_हटाओ,
		.playback = अणु
			.stream_name = AUD_NAME_HIECOUT1,
			.क्रमmats     = SNDRV_PCM_FMTBIT_S32_LE,
			.rates       = SNDRV_PCM_RATE_48000,
			.channels_min = 2,
			.channels_max = 2,
		पूर्ण,
		.ops = &uniphier_aio_spdअगर_ops,
	पूर्ण,
	अणु
		.name    = AUD_NAME_IECOUT1,
		.probe   = uniphier_aio_pxs2_probe,
		.हटाओ  = uniphier_aio_dai_हटाओ,
		.playback = अणु
			.stream_name = AUD_NAME_IECOUT1,
			.क्रमmats     = SNDRV_PCM_FMTBIT_S32_LE,
			.rates       = SNDRV_PCM_RATE_48000,
			.channels_min = 2,
			.channels_max = 2,
		पूर्ण,
		.ops = &uniphier_aio_spdअगर_ops,
	पूर्ण,
	अणु
		.name    = AUD_NAME_HIECCOMPOUT1,
		.probe   = uniphier_aio_pxs2_probe,
		.हटाओ  = uniphier_aio_dai_हटाओ,
		.compress_new = snd_soc_new_compress,
		.playback = अणु
			.stream_name = AUD_NAME_HIECCOMPOUT1,
			.channels_min = 1,
			.channels_max = 1,
		पूर्ण,
		.ops = &uniphier_aio_spdअगर_ops,
	पूर्ण,
	अणु
		.name    = AUD_NAME_IECCOMPOUT1,
		.probe   = uniphier_aio_pxs2_probe,
		.हटाओ  = uniphier_aio_dai_हटाओ,
		.compress_new = snd_soc_new_compress,
		.playback = अणु
			.stream_name = AUD_NAME_IECCOMPOUT1,
			.channels_min = 1,
			.channels_max = 1,
		पूर्ण,
		.ops = &uniphier_aio_spdअगर_ops,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा uniphier_aio_chip_spec uniphier_aio_pxs2_spec = अणु
	.specs     = uniphier_aio_pxs2,
	.num_specs = ARRAY_SIZE(uniphier_aio_pxs2),
	.dais      = uniphier_aio_dai_pxs2,
	.num_dais  = ARRAY_SIZE(uniphier_aio_dai_pxs2),
	.plls      = uniphier_aio_pll_pxs2,
	.num_plls  = ARRAY_SIZE(uniphier_aio_pll_pxs2),
	.addr_ext  = 0,
पूर्ण;

अटल स्थिर काष्ठा of_device_id uniphier_aio_of_match[] __maybe_unused = अणु
	अणु
		.compatible = "socionext,uniphier-pxs2-aio",
		.data = &uniphier_aio_pxs2_spec,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, uniphier_aio_of_match);

अटल काष्ठा platक्रमm_driver uniphier_aio_driver = अणु
	.driver = अणु
		.name = "snd-uniphier-aio-pxs2",
		.of_match_table = of_match_ptr(uniphier_aio_of_match),
	पूर्ण,
	.probe    = uniphier_aio_probe,
	.हटाओ   = uniphier_aio_हटाओ,
पूर्ण;
module_platक्रमm_driver(uniphier_aio_driver);

MODULE_AUTHOR("Katsuhiro Suzuki <suzuki.katsuhiro@socionext.com>");
MODULE_DESCRIPTION("UniPhier PXs2 AIO driver.");
MODULE_LICENSE("GPL v2");
