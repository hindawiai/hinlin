<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// soc-util.c  --  ALSA SoC Audio Layer utility functions
//
// Copyright 2009 Wolfson Microelectronics PLC.
//
// Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
//         Liam Girdwood <lrg@slimlogic.co.uk>

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/export.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

पूर्णांक snd_soc_calc_frame_size(पूर्णांक sample_size, पूर्णांक channels, पूर्णांक tdm_slots)
अणु
	वापस sample_size * channels * tdm_slots;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_calc_frame_size);

पूर्णांक snd_soc_params_to_frame_size(काष्ठा snd_pcm_hw_params *params)
अणु
	पूर्णांक sample_size;

	sample_size = snd_pcm_क्रमmat_width(params_क्रमmat(params));
	अगर (sample_size < 0)
		वापस sample_size;

	वापस snd_soc_calc_frame_size(sample_size, params_channels(params),
				       1);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_params_to_frame_size);

पूर्णांक snd_soc_calc_bclk(पूर्णांक fs, पूर्णांक sample_size, पूर्णांक channels, पूर्णांक tdm_slots)
अणु
	वापस fs * snd_soc_calc_frame_size(sample_size, channels, tdm_slots);
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_calc_bclk);

पूर्णांक snd_soc_params_to_bclk(काष्ठा snd_pcm_hw_params *params)
अणु
	पूर्णांक ret;

	ret = snd_soc_params_to_frame_size(params);

	अगर (ret > 0)
		वापस ret * params_rate(params);
	अन्यथा
		वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(snd_soc_params_to_bclk);

अटल स्थिर काष्ठा snd_pcm_hardware dummy_dma_hardware = अणु
	/* Ranकरोm values to keep userspace happy when checking स्थिरraपूर्णांकs */
	.info			= SNDRV_PCM_INFO_INTERLEAVED |
				  SNDRV_PCM_INFO_BLOCK_TRANSFER,
	.buffer_bytes_max	= 128*1024,
	.period_bytes_min	= PAGE_SIZE,
	.period_bytes_max	= PAGE_SIZE*2,
	.periods_min		= 2,
	.periods_max		= 128,
पूर्ण;

अटल पूर्णांक dummy_dma_खोलो(काष्ठा snd_soc_component *component,
			  काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);

	/* BE's करोnt need dummy params */
	अगर (!rtd->dai_link->no_pcm)
		snd_soc_set_runसमय_hwparams(substream, &dummy_dma_hardware);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver dummy_platक्रमm = अणु
	.खोलो		= dummy_dma_खोलो,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver dummy_codec = अणु
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

#घोषणा STUB_RATES	SNDRV_PCM_RATE_8000_384000
#घोषणा STUB_FORMATS	(SNDRV_PCM_FMTBIT_S8 | \
			SNDRV_PCM_FMTBIT_U8 | \
			SNDRV_PCM_FMTBIT_S16_LE | \
			SNDRV_PCM_FMTBIT_U16_LE | \
			SNDRV_PCM_FMTBIT_S24_LE | \
			SNDRV_PCM_FMTBIT_S24_3LE | \
			SNDRV_PCM_FMTBIT_U24_LE | \
			SNDRV_PCM_FMTBIT_S32_LE | \
			SNDRV_PCM_FMTBIT_U32_LE | \
			SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE)
/*
 * The dummy CODEC is only meant to be used in situations where there is no
 * actual hardware.
 *
 * If there is actual hardware even अगर it करोes not have a control bus
 * the hardware will still have स्थिरraपूर्णांकs like supported samplerates, etc.
 * which should be modelled. And the data flow graph also should be modelled
 * using DAPM.
 */
अटल काष्ठा snd_soc_dai_driver dummy_dai = अणु
	.name = "snd-soc-dummy-dai",
	.playback = अणु
		.stream_name	= "Playback",
		.channels_min	= 1,
		.channels_max	= 384,
		.rates		= STUB_RATES,
		.क्रमmats	= STUB_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name	= "Capture",
		.channels_min	= 1,
		.channels_max	= 384,
		.rates = STUB_RATES,
		.क्रमmats = STUB_FORMATS,
	 पूर्ण,
पूर्ण;

पूर्णांक snd_soc_dai_is_dummy(काष्ठा snd_soc_dai *dai)
अणु
	अगर (dai->driver == &dummy_dai)
		वापस 1;
	वापस 0;
पूर्ण

पूर्णांक snd_soc_component_is_dummy(काष्ठा snd_soc_component *component)
अणु
	वापस ((component->driver == &dummy_platक्रमm) ||
		(component->driver == &dummy_codec));
पूर्ण

अटल पूर्णांक snd_soc_dummy_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev,
					      &dummy_codec, &dummy_dai, 1);
	अगर (ret < 0)
		वापस ret;

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &dummy_platक्रमm,
					      शून्य, 0);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver soc_dummy_driver = अणु
	.driver = अणु
		.name = "snd-soc-dummy",
	पूर्ण,
	.probe = snd_soc_dummy_probe,
पूर्ण;

अटल काष्ठा platक्रमm_device *soc_dummy_dev;

पूर्णांक __init snd_soc_util_init(व्योम)
अणु
	पूर्णांक ret;

	soc_dummy_dev =
		platक्रमm_device_रेजिस्टर_simple("snd-soc-dummy", -1, शून्य, 0);
	अगर (IS_ERR(soc_dummy_dev))
		वापस PTR_ERR(soc_dummy_dev);

	ret = platक्रमm_driver_रेजिस्टर(&soc_dummy_driver);
	अगर (ret != 0)
		platक्रमm_device_unरेजिस्टर(soc_dummy_dev);

	वापस ret;
पूर्ण

व्योम __निकास snd_soc_util_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&soc_dummy_driver);
	platक्रमm_device_unरेजिस्टर(soc_dummy_dev);
पूर्ण
