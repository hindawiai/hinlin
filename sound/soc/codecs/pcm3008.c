<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ALSA Soc PCM3008 codec support
 *
 * Author:	Hugo Villeneuve
 * Copyright (C) 2008 Lyrtech inc
 *
 * Based on AC97 Soc codec, original copyright follow:
 * Copyright 2005 Wolfson Microelectronics PLC.
 *
 * Generic PCM3008 support.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>

#समावेश "pcm3008.h"

अटल पूर्णांक pcm3008_dac_ev(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *kcontrol,
			  पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा pcm3008_setup_data *setup = component->dev->platक्रमm_data;

	gpio_set_value_cansleep(setup->pdda_pin,
				SND_SOC_DAPM_EVENT_ON(event));

	वापस 0;
पूर्ण

अटल पूर्णांक pcm3008_adc_ev(काष्ठा snd_soc_dapm_widget *w,
			  काष्ठा snd_kcontrol *kcontrol,
			  पूर्णांक event)
अणु
	काष्ठा snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	काष्ठा pcm3008_setup_data *setup = component->dev->platक्रमm_data;

	gpio_set_value_cansleep(setup->pdad_pin,
				SND_SOC_DAPM_EVENT_ON(event));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget pcm3008_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_INPUT("VINL"),
SND_SOC_DAPM_INPUT("VINR"),

SND_SOC_DAPM_DAC_E("DAC", शून्य, SND_SOC_NOPM, 0, 0, pcm3008_dac_ev,
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),
SND_SOC_DAPM_ADC_E("ADC", शून्य, SND_SOC_NOPM, 0, 0, pcm3008_adc_ev,
		   SND_SOC_DAPM_PRE_PMU | SND_SOC_DAPM_POST_PMD),

SND_SOC_DAPM_OUTPUT("VOUTL"),
SND_SOC_DAPM_OUTPUT("VOUTR"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route pcm3008_dapm_routes[] = अणु
	अणु "PCM3008 Capture", शून्य, "ADC" पूर्ण,
	अणु "ADC", शून्य, "VINL" पूर्ण,
	अणु "ADC", शून्य, "VINR" पूर्ण,

	अणु "DAC", शून्य, "PCM3008 Playback" पूर्ण,
	अणु "VOUTL", शून्य, "DAC" पूर्ण,
	अणु "VOUTR", शून्य, "DAC" पूर्ण,
पूर्ण;

#घोषणा PCM3008_RATES (SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |	\
		       SNDRV_PCM_RATE_48000)

अटल काष्ठा snd_soc_dai_driver pcm3008_dai = अणु
	.name = "pcm3008-hifi",
	.playback = अणु
		.stream_name = "PCM3008 Playback",
		.channels_min = 1,
		.channels_max = 2,
		.rates = PCM3008_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
	.capture = अणु
		.stream_name = "PCM3008 Capture",
		.channels_min = 1,
		.channels_max = 2,
		.rates = PCM3008_RATES,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_pcm3008 = अणु
	.dapm_widमाला_लो		= pcm3008_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(pcm3008_dapm_widमाला_लो),
	.dapm_routes		= pcm3008_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(pcm3008_dapm_routes),
	.idle_bias_on		= 1,
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल पूर्णांक pcm3008_codec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pcm3008_setup_data *setup = pdev->dev.platक्रमm_data;
	पूर्णांक ret;

	अगर (!setup)
		वापस -EINVAL;

	/* DEM1  DEM0  DE-EMPHASIS_MODE
	 * Low   Low   De-emphasis 44.1 kHz ON
	 * Low   High  De-emphasis OFF
	 * High  Low   De-emphasis 48 kHz ON
	 * High  High  De-emphasis 32 kHz ON
	 */

	/* Configure DEM0 GPIO (turning OFF DAC De-emphasis). */
	ret = devm_gpio_request_one(&pdev->dev, setup->dem0_pin,
				    GPIOF_OUT_INIT_HIGH, "codec_dem0");
	अगर (ret != 0)
		वापस ret;

	/* Configure DEM1 GPIO (turning OFF DAC De-emphasis). */
	ret = devm_gpio_request_one(&pdev->dev, setup->dem1_pin,
				    GPIOF_OUT_INIT_LOW, "codec_dem1");
	अगर (ret != 0)
		वापस ret;

	/* Configure PDAD GPIO. */
	ret = devm_gpio_request_one(&pdev->dev, setup->pdad_pin,
				    GPIOF_OUT_INIT_LOW, "codec_pdad");
	अगर (ret != 0)
		वापस ret;

	/* Configure PDDA GPIO. */
	ret = devm_gpio_request_one(&pdev->dev, setup->pdda_pin,
				    GPIOF_OUT_INIT_LOW, "codec_pdda");
	अगर (ret != 0)
		वापस ret;

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev,
			&soc_component_dev_pcm3008, &pcm3008_dai, 1);
पूर्ण

MODULE_ALIAS("platform:pcm3008-codec");

अटल काष्ठा platक्रमm_driver pcm3008_codec_driver = अणु
	.probe		= pcm3008_codec_probe,
	.driver		= अणु
		.name	= "pcm3008-codec",
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(pcm3008_codec_driver);

MODULE_DESCRIPTION("Soc PCM3008 driver");
MODULE_AUTHOR("Hugo Villeneuve");
MODULE_LICENSE("GPL");
